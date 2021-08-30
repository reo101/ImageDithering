#ifndef PIXEL_HPP_GUARD
#define PIXEL_HPP_GUARD

#include <ostream>

typedef bool u1;  // not actually 1 bit (padding)
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

enum class PixelType {
    Bit  = 1,
    Gray = 2,
    Pix  = 3,
};

class Pixel {
    private:
    union {
        u1 isWhite;
        u8 grayness;
        struct {
            u8 R;
            u8 G;
            u8 B;
        } rgb;
    };
    PixelType pixelType;

    public:
    Pixel(PixelType tag = PixelType::Bit);
    Pixel(u1 isWhite);
    Pixel(int grayness); // int to prevent ambiguity
    Pixel(u8 R, u8 G, u8 B);
    Pixel(Pixel &&);
    Pixel(const Pixel &);
    Pixel &operator=(Pixel &&);
    Pixel &operator=(const Pixel &);

    virtual ~Pixel() = default;

    PixelType getPixelType() const;

    friend std::ostream &operator<<(std::ostream &os, const Pixel &pixel);
};

#endif  // !PIXEL_HPP_GUARD
