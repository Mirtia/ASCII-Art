#include "ASCIIConverter.hpp"

cv::Scalar ASCII::convert_hex_to_BGR(const std::string &hex)
{
    int red = std::stoi(hex.substr(1, 2), nullptr, 16);
    int green = std::stoi(hex.substr(3, 2), nullptr, 16);
    int blue = std::stoi(hex.substr(5, 2), nullptr, 16);
    return cv::Scalar(blue, green, red);
}

std::string ASCII::convert_pixel_intensity_to_ASCII(int intensity)
{
    size_t length = ASCII::ASCII_characters.length();
    // I put 2 characters per pixel to make the ASCII art more clear
    std::string value = std::string(2, ASCII::ASCII_characters[intensity * ASCII::ASCII_characters.length() / 256]);
    return value;
}

cv::Mat ASCII::render_image(std::vector<std::string> ASCII_strs, cv::Size size, const std::string &font_path, cv::Scalar font_color, cv::Scalar background_color, int font_height)
{
    cv::Ptr<cv::freetype::FreeType2> ft2;
    ft2 = cv::freetype::createFreeType2();
    ft2->loadFontData(font_path, 0);

    const int width = ft2->getTextSize(ASCII_strs[0], font_height, 1, nullptr).width;
    // std::cout << "Log: ASCII image width: " << width << ", height: " << size.height * font_height << std::endl;
    cv::Mat ASCII_text_image(cv::Size(width, (size.height - 1) * font_height), CV_8UC3, background_color);
    cv::Point start_point = cv::Point(0, 0);
    for (const std::string &ASCII_str : ASCII_strs)
    {
        ft2->putText(ASCII_text_image, ASCII_str, start_point, font_height, font_color, 1, cv::LINE_AA, true);
        start_point.y += font_height;
    }
    return ASCII_text_image;
}

void ASCII::convert_mp4_to_GIF(const std::string &input_path, const std::string &output_path)
{
    // Stupid way to convert from .mp4 to .gif, always override file, just use it from command prompt
    const std::string command = "ffmpeg -y -i " + input_path + " " + output_path;
    // std::cout << "Log: " << command << std::endl;
    std::system(command.c_str());
}

void ASCII::resize_image(const cv::Mat &input_array, cv::Mat &output_array, const int resize_width)
{
    if (input_array.empty())
    {
        std::cerr << "Error: Frame is empty!" << std::endl;
        exit(EXIT_FAILURE);
    }

    const int width = input_array.cols;
    const int height = input_array.rows;

    float aspect_ratio = static_cast<float>(width) / height;
    cv::resize(input_array, output_array, cv::Size(resize_width, static_cast<int>(resize_width / aspect_ratio)), 0, 0, cv::INTER_LINEAR_EXACT);
}

void ASCII::convert_video_to_ASCII(std::vector<cv::Mat> frames, int fps, int frame_count, const std::string &font_path, const std::string &output_path, cv::Scalar font_color, cv::Scalar background_color)
{
    std::vector<cv::Mat> ASCII_frames;
    for (cv::Mat &frame : frames)
        ASCII_frames.push_back(ASCII::convert_image_to_ASCII(frame, font_path, font_color, background_color));

    const size_t length = ASCII_frames.size();
    cv::VideoWriter oVideoWriter(output_path, cv::VideoWriter::fourcc('a', 'v', 'c', '1'), fps, ASCII_frames[0].size(), true);

    for (size_t i = 0; i < length; i++)
        oVideoWriter.write(ASCII_frames[i]);

    oVideoWriter.release();
}

cv::Mat ASCII::convert_image_to_ASCII(const cv::Mat &frame, const std::string &font_path, cv::Scalar font_color, cv::Scalar background_color, const std::string &output_path, bool save)
{
    if (frame.empty())
    {
        std::cerr << "Error: Frame is empty!" << std::endl;
        exit(EXIT_FAILURE);
    }

    cv::Mat resized_frame;
    // Larger size results to more detail (error at big dimensions)
    ASCII::resize_image(frame, resized_frame, 100);

    std::vector<std::string> ASCII_strs;
    for (int i = 0; i < resized_frame.rows; ++i)
    {
        std::string ASCII_str;
        for (int j = 0; j < resized_frame.cols; ++j)
        {
            ASCII_str += ASCII::convert_pixel_intensity_to_ASCII(resized_frame.at<uchar>(i, j));
        }
        ASCII_strs.push_back(ASCII_str);
    }

    cv::Mat rendered_image = ASCII::render_image(ASCII_strs, resized_frame.size(), font_path, font_color, background_color);

    if (save && !output_path.empty())
        cv::imwrite(output_path, rendered_image);

    return rendered_image;
}