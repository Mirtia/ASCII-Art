#ifndef UTIL_HPP
#define UTIL_HPP
#include <stdio.h>

bool string_ends_with(const std::string &str, const std::string &suffix)
{
    if (str.length() < suffix.length())
        return false;
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

bool is_image(const std::string &str)
{
    return string_ends_with(str, ".jpg") || string_ends_with(str, ".jpeg") || string_ends_with(str, ".png");
}

bool is_video(const std::string &str)
{
    return string_ends_with(str, ".gif") || string_ends_with(str, ".mp4");
}

#endif /*UTIL_HPP*/