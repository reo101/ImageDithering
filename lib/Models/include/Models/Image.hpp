#ifndef IMAGE_HPP_GUARD
#define IMAGE_HPP_GUARD

#include <initializer_list>
#include <ostream>

#include "Pixel.hpp"

enum class ImageType : unsigned char {
    BitMap  = 1,
    GrayMap = 2,
    PixMap  = 3,
};
enum class EncodingType : unsigned char {
    Ascii  = 0,
    Binary = 3,
};

class Image {
    private:
    ImageType imageType;
    EncodingType encodingType;
    size_t width, height;
    Pixel **data;

    public:
    Image();
    Image(ImageType,
          EncodingType,
          size_t width,
          size_t height,
          Pixel **data = nullptr);
    Image(Image &&);
    Image(const Image &);
    Image &operator=(Image &&);
    Image &operator=(const Image &);
    virtual ~Image();

    ImageType getImageType() const;
    void setImageType(ImageType);
    EncodingType getEncodingType() const;
    void setEncodingType(EncodingType);

    friend std::ostream &operator<<(std::ostream &os, const Image &);
    static bool writeToFile(const Image &image, const char *);

    // Proxy structure to allow [][] indexing
    struct Proxy {
        private:
        friend class Image;
        Image *image;
        size_t row;
        Proxy(Image *image, size_t row);

        public:
        Pixel &operator[](size_t col);
        const Pixel &operator[](size_t col) const;
    };

    Proxy operator[](int row);
    const Proxy operator[](int row) const;
};

#endif  // !IMAGE_HPP_GUARD
