
class HSLAPixel
{
public:
    double h, s, l, a;
    HSLAPixel(double hue, double sat, double lum, double alpha = 1.0);
};

HSLAPixel::HSLAPixel(double hue, double sat, double lum, double alpha = 1.0)
    : h(hue), s(sat), l(lum), a(alpha)
{
}
