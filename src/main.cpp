#include <Models/Image.hpp>
#include <Models/Pixel.hpp>
#include <iostream>

int main() {

    size_t width = 70, height = 70;

    Image img(ImageType::BitMap, EncodingType::Ascii, width, height);

    for (int row = 0; row < width / 2; ++row) {
        for (int col = 0; col < height / 2; ++col) {
            img[row * 2][col * 2] = {true};
        }
    }

    Image::writeToFile(img, "res/test");

    return 0;
}
