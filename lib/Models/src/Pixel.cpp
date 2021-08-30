#include "Pixel.hpp"

#include <ostream>

Pixel::Pixel(PixelType pixelType) : pixelType(pixelType) {
    switch (pixelType) {
        case PixelType::Bit:
            this->isWhite = 0;
            break;
        case PixelType::Gray:
            this->grayness = 0;
            break;
        case PixelType::Pix:
            this->rgb = {0, 0, 0};
            break;
    }
}

Pixel::Pixel(u1 isWhite) : pixelType(PixelType::Bit), isWhite(isWhite) {}

Pixel::Pixel(int grayness) : pixelType(PixelType::Gray), grayness(grayness) {}

Pixel::Pixel(u8 R, u8 G, u8 B) : pixelType(PixelType::Pix), rgb({R, G, B}) {}

Pixel::Pixel(Pixel &&pixel) : pixelType(pixel.pixelType) {
    switch (pixel.pixelType) {
        case PixelType::Bit:
            this->isWhite = pixel.isWhite;
            break;
        case PixelType::Gray:
            this->grayness = pixel.grayness;
            break;
        case PixelType::Pix:
            this->rgb = pixel.rgb;
            break;
    }
}

Pixel::Pixel(const Pixel &pixel) : pixelType(pixel.pixelType) {
    switch (pixel.pixelType) {
        case PixelType::Bit:
            this->isWhite = pixel.isWhite;
            break;
        case PixelType::Gray:
            this->grayness = pixel.grayness;
            break;
        case PixelType::Pix:
            this->rgb = pixel.rgb;
            break;
    }
}

Pixel &Pixel::operator=(Pixel &&pixel) {
    if (this != &pixel) {
        this->pixelType = pixel.pixelType;
        switch (pixel.pixelType) {
            case PixelType::Bit:
                this->isWhite = pixel.isWhite;
                break;
            case PixelType::Gray:
                this->grayness = pixel.grayness;
                break;
            case PixelType::Pix:
                this->rgb = pixel.rgb;
                break;
        }
    }

    return *this;
}

Pixel &Pixel::operator=(const Pixel &pixel) {
    if (this != &pixel) {
        this->pixelType = pixel.pixelType;
        switch (pixel.pixelType) {
            case PixelType::Bit:
                this->isWhite = pixel.isWhite;
                break;
            case PixelType::Gray:
                this->grayness = pixel.grayness;
                break;
            case PixelType::Pix:
                this->rgb = pixel.rgb;
                break;
        }
    }

    return *this;
}

PixelType Pixel::getPixelType() const {
    return this->pixelType;
}

std::ostream &operator<<(std::ostream &os, const Pixel &pixel) {

    switch (pixel.pixelType) {
        case PixelType::Bit:
            os << static_cast<int>(pixel.isWhite) << '\n';
            break;
        case PixelType::Gray:
            os << static_cast<int>(pixel.grayness) << '\n';
            break;
        case PixelType::Pix:
            os << static_cast<int>(pixel.rgb.R) << '\t'
               << static_cast<int>(pixel.rgb.G) << '\t'
               << static_cast<int>(pixel.rgb.B) << '\n';
            break;
    }

    return os;
}
