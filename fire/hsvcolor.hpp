#ifndef HSVCOLOR_HPP
#define HSVCOLOR_HPP

#include <rgbcolor.hpp>

class hsvColor
{
public:
  hsvColor(unsigned char aHue, unsigned char aSaturation, unsigned char aValue);

  const unsigned char &h()const;
  const unsigned char &s()const;
  const unsigned char &v()const;

  rgbColor toRGB();

private:
  unsigned char m_hue{0};
  unsigned char m_saturation{0};
  unsigned char m_value{0};
};

#endif // HSVCOLOR_HPP
