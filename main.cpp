#include "ASCIIConverter.hpp"
#include "util.hpp"

int main(int argc, char const *argv[])
{
    const std::string keys = {
        "{input i   |   |   Path to input file}"
        "{font f    |   |   Path to font file}"
        "{output o  |   |   Path to output file}"
        "{help h usage ? |  |   See usage}"};

    cv::CommandLineParser parser(argc, argv, keys);

    // My example usage (cries in Windows):
    // "D:/ASCII-Art/build/Debug/ascii-art.exe" --input=input/osaka.jpg
    // --font=fonts/Consolas.ttf --output=output/osaka_ascii.jpg
    // "D:/ASCII-Art/build/Debug/ascii-art.exe" --input=input/lain.gif
    //  --font=fonts/Consolas.ttf --output=output/lain_ascii.mp4
        
    if (parser.has("help"))
        parser.printMessage();

    else if (parser.has("input") && parser.has("font") && parser.has("output"))
    {
        const std::string input_path = parser.get<std::string>("input");
        const std::string font_path = parser.get<std::string>("font");
        const std::string output_path = parser.get<std::string>("output");

        if (is_image(input_path))
        {
            cv::Mat image = cv::imread(input_path, cv::IMREAD_GRAYSCALE);
            if (image.empty())
            {
                std::cerr << "Error: Cannot open image " << input_path << " for reading." << std::endl;
                exit(EXIT_FAILURE);
            }

            ASCII::convert_image_to_ASCII(image, font_path, output_path, true);
        }
        else if (is_video(input_path))
        {
            cv::VideoCapture video_capture(input_path);
            if (!video_capture.isOpened())
            {
                std::cerr << "Error: Cannot open capture " << input_path << "." << std::endl;
                exit(EXIT_FAILURE);
            }

            std::vector<cv::Mat> frames;
            while (true)
            {
                cv::Mat frame;
                cv::Mat grayscale_frame;
                video_capture.read(frame);
                if (frame.empty())
                    break;
                cv::cvtColor(frame, grayscale_frame, cv::COLOR_RGB2GRAY);
                frames.push_back(grayscale_frame);
            }

            int frame_count = static_cast<int>(video_capture.get(cv::CAP_PROP_FRAME_COUNT));
            int fps = static_cast<int>(video_capture.get(cv::CAP_PROP_FPS));

            ASCII::convert_video_to_ASCII(frames, fps, frame_count, font_path, output_path);
        }
        else
            std::cout << "Log: Not supported file types." << std::endl
                      << "Supported types are .gif, .mp4, .jpg, .jpeg, .png." << std::endl;
    }
    else 
    {
        std::cerr << "Error: Please provide the necessary arguments." << std::endl;
        parser.printMessage();
        exit(EXIT_FAILURE);
    }

    return 0;
}
