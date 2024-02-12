#include "ray_tracing/image.h"

#define STB_IMAGE_IMPLEMENTATION
// Could not be included in image.h. Causes likner error.
#include "stb_image.h"

Image::Image(const char * img_filename)
{
    auto filename = std::string(img_filename);
    auto img_dir = getenv("RTW_IMAGES");

    if(img_dir && load(std::string(img_dir) + "/" + img_filename)) return;
    if(load(filename)) return;
    if(load("images/" + filename)) return;
    if(load("../images/" + filename)) return;
    if(load("../../images/" + filename)) return;
    if(load("../../images/" + filename)) return;
    if(load("../../../images/" + filename)) return;
    if(load("../../../../images/" + filename)) return;

    std::cerr << "ERROR: Could not load image file '" << img_filename << "'.\n";
}

Image::~Image()
{
    STBI_FREE(data);
}

bool Image::load(const std::string filename)
{
    auto n = bytes_per_pixel;
    data = stbi_load(filename.c_str(), &image_width, &image_height, &n, bytes_per_pixel);
    bytes_per_scanline = image_width * bytes_per_pixel;

    return data != nullptr;
    
}

int Image::width() const
{
    return (data == nullptr) ? 0 : image_width;
}

int Image::height() const
{
    return (data == nullptr) ? 0 : image_height;
}

const unsigned char * Image::pixel_data(int x, int y) const
{
    static unsigned char magenta[] = {255, 0, 255};

    if(data == nullptr)
        return magenta;

    x = clamp(x, 0, image_width);
    y = clamp(y, 0, image_height);

    return data + y * bytes_per_scanline + x * bytes_per_pixel;
}

int Image::clamp(int x, int low, int high)
{
    if(x < low)
        return low;
    
    if(x > high)
        return high - 1;
    
    return x;
}