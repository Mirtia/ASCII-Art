#ifndef ASCII_CONVERTER_HPP
#define ASCII_CONVERTER_HPP
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/freetype.hpp>

namespace ASCII
{
    const std::string ASCII_characters = "@#&!*+=-_.   ";
    std::string convert_pixel_intensity_to_ASCII(int intensity);
    void convert_video_to_ASCII(std::vector<cv::Mat> frames, int fps, int frame_count, const std::string &font_path, const std::string &output_path);
    cv::Mat convert_image_to_ASCII(const cv::Mat &image, const std::string &font_path, const std::string &output_path = {}, bool save = false);
    cv::Mat render_image(std::vector<std::string> ASCII_strs, cv::Size size, const std::string &font_path, int font_height = 15);
    void resize_image(const cv::Mat &input_array, cv::Mat &output_array, int resize_width);
    void convert_mp4_to_GIF(const std::string &input_path, const std::string &output_path);
};

#endif /*ASCII_CONVERTER_HPP*/