#include "Pixel.hpp"

Pixel::Pixel() : R(0), G(0), B(0) {}

Pixel::Pixel(Byte R, Byte G, Byte B) : R(R), G(G), B(B) {}

Pixel::Pixel(Pixel &&pixel) : R(pixel.R), G(pixel.G), B(pixel.B) {}

Pixel::Pixel(const Pixel &pixel) : R(pixel.R), G(pixel.G), B(pixel.B) {}

Pixel &Pixel::operator=(Pixel &&pixel) {
    if (this != &pixel) {
        this->R = pixel.R;
        this->G = pixel.G;
        this->B = pixel.B;
    }

    return *this;
}

Pixel &Pixel::operator=(const Pixel &pixel) {
    if (this != &pixel) {
        this->R = pixel.R;
        this->G = pixel.G;
        this->B = pixel.B;
    }

    return *this;
}

Byte Pixel::getR() const {
    return this->R;
}

void Pixel::setR(Byte R) {
    this->R = R;
}

Byte Pixel::getG() const {
    return this->G;
}

void Pixel::setG(Byte G){
    this->G = G;
}

Byte Pixel::getB() const {
    return this->B;
}

void Pixel::setB(Byte B) {
    this->B = B;
}
