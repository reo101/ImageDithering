#ifndef PIXEL_HPP_GUARD
#define PIXEL_HPP_GUARD

typedef unsigned char Byte;

class Pixel {
    private:
    Byte R, G, B;

    public:
    Pixel();
    Pixel(Byte R, Byte G, Byte B);
    Pixel(Pixel &&);
    Pixel(const Pixel &);
    Pixel &operator=(Pixel &&);
    Pixel &operator=(const Pixel &);
    virtual ~Pixel() = default;

    Byte getR() const;
    void setR(Byte);
    Byte getG() const;
    void setG(Byte);
    Byte getB() const;
    void setB(Byte);
};

#endif  // !PIXEL_HPP_GUARD
