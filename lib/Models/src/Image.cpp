#include <Image.hpp>
#include <cstring>
#include <fstream>
#include <ios>

#include "Pixel.hpp"

Image::Image()
    : imageType(ImageType::PixMap),
      encodingType(EncodingType::Ascii),
      width(1),
      height(1),
      data(new Pixel *[height] {
          new Pixel[width] {
              { 255, 255, 255 }
          }
      }) {}

Image::Image(ImageType imageType,
             EncodingType encodingType,
             size_t width,
             size_t height,
             Pixel **data)
    : imageType(imageType),
      encodingType(encodingType),
      width(width),
      height(height) {

    Pixel placeholder;
    if (!data) {
        switch (this->imageType) {
            case ImageType::BitMap:
                placeholder = Pixel(PixelType::Bit);
                break;
            case ImageType::GrayMap:
                placeholder = Pixel(PixelType::Gray);
                break;
            case ImageType::PixMap:
                placeholder = Pixel(PixelType::Pix);
                break;
        }
    }

    this->data = new Pixel *[this->height];
    for (size_t row = 0; row < height; ++row) {
        this->data[row] = new Pixel[width];
        for (size_t col = 0; col < width; ++col) {
            this->data[row][col] = (data ? data[row][col] : placeholder);
        }
    }
}

Image::Image(Image &&image)
    : imageType(image.imageType),
      encodingType(image.encodingType),
      width(image.width),
      height(image.height) {
    this->data = new Pixel *[this->height];
    for (size_t row = 0; row < height; ++row) {
        this->data[row] = new Pixel[width];
        for (size_t col = 0; col < width; ++col) {
            this->data[row][col] = image[row][col];
        }
    }
}

Image::Image(const Image &image)
    : imageType(image.imageType),
      encodingType(image.encodingType),
      width(image.width),
      height(image.height) {
    this->data = new Pixel *[this->height];
    for (size_t row = 0; row < height; ++row) {
        this->data[row] = new Pixel[width];
        for (size_t col = 0; col < width; ++col) {
            this->data[row][col] = image[row][col];
        }
    }
}

Image &Image::operator=(Image &&image) {
    if (this != &image) {
        imageType    = image.imageType;
        encodingType = image.encodingType;
        width        = image.width;
        height       = image.height;
        this->data   = new Pixel *[this->height];
        for (size_t row = 0; row < height; ++row) {
            this->data[row] = new Pixel[width];
            for (size_t col = 0; col < width; ++col) {
                this->data[row][col] = image[row][col];
            }
        }
    }

    return *this;
}

Image &Image::operator=(const Image &image) {
    if (this != &image) {
        imageType    = image.imageType;
        encodingType = image.encodingType;
        width        = image.width;
        height       = image.height;
        this->data   = new Pixel *[this->height];
        for (size_t row = 0; row < height; ++row) {
            this->data[row] = new Pixel[width];
            for (size_t col = 0; col < width; ++col) {
                this->data[row][col] = image[row][col];
            }
        }
    }

    return *this;
}

Image::~Image() {
    for (size_t row = 0; row < this->height; ++row) {
        delete[] this->data[row];
    }
    delete[] this->data;
}

ImageType Image::getImageType() const {
    return this->imageType;
}

void Image::setImageType(ImageType imageType) {
    this->imageType = imageType;
}

EncodingType Image::getEncodingType() const {
    return this->encodingType;
}

void Image::setEncodingType(EncodingType encodingType) {
    this->encodingType = encodingType;
}

std::ostream &operator<<(std::ostream &os, const Image &image) {
    os << 'P'
       << (static_cast<int>(image.imageType) +
           static_cast<int>(image.encodingType))
       << '\n';
    os << image.width << ' ' << image.height << '\n';

    switch (image.imageType) {
        case ImageType::BitMap:
            for (size_t row = 0; row < image.height; ++row) {
                for (size_t col = 0; col < image.width; ++col) {
                    os << image[row][col];
                }
            }
            break;
        case ImageType::GrayMap:
        case ImageType::PixMap:
            os << "255" << '\n';

            for (size_t row = 0; row < image.height; ++row) {
                for (size_t col = 0; col < image.width; ++col) {
                    os << image[row][col];
                }
            }
            break;
    }

    return os;
}

bool Image::writeToFile(const Image &image, const char *path) {
    std::ofstream of;
    std::ios_base::open_mode flags = std::ios::out;

    if (image.encodingType == EncodingType::Binary) {
        flags |= std::ios::binary;
    }

    const char *extension;

    switch (image.imageType) {
        case ImageType::BitMap:
            extension = ".pbm";
            break;
        case ImageType::GrayMap:
            extension = ".pgm";
            break;
        case ImageType::PixMap:
            extension = ".ppm";
            break;
    }

    char *fullPath = new char[std::strlen(path) + std::strlen(extension)];
    std::strcpy(fullPath, path);
    std::strcat(fullPath, extension);

    of.open(fullPath, flags);

    if (!of.is_open()) {
        return false;
    }

    of << image;

    of.close();
    delete[] fullPath;

    return true;
}

Image::Proxy::Proxy(Image *image, size_t row) : image(image), row(row) {}

Pixel &Image::Proxy::operator[](size_t col) {
    return image->data[row][col];
}
const Pixel &Image::Proxy::operator[](size_t col) const {
    return image->data[row][col];
}

Image::Proxy Image::operator[](int row) {
    return Image::Proxy(this, row);
}

const Image::Proxy Image::operator[](int row) const {
    return Proxy(const_cast<Image *>(this), row);
}
