#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#ifdef _MSC_VER
    #pragma warning (push, 0)
#endif

#include <cstdlib>
#include <iostream>

class Image
{
    public:
        Image() : data(nullptr) {}

        Image(const char * img_filename);

        ~Image();

        bool load(const std::string filename);

        int width() const;

        int height() const;

        const unsigned char * pixel_data(int x, int y) const;
    private:
        const int bytes_per_pixel = 3;
        unsigned char * data;
        int image_width, image_height;
        int bytes_per_scanline;

        static int clamp(int x, int low, int high);
};

#ifdef _MSC_VER
    #pragma warning (pop)
#endif

#endif