#ifndef RGBCOLOR_HPP
#define RGBCOLOR_HPP


class rgbColor
{
public:
  rgbColor();
  rgbColor(unsigned char aRed, unsigned char aGreen, unsigned char aBlue);

  void setRed(unsigned char aValue);
  void setGreen(unsigned char aValue);
  void setBlue(unsigned char aValue);

  const unsigned char &r()const;
  const unsigned char &g()const;
  const unsigned char &b()const;

private:
  unsigned char m_red{0};
  unsigned char m_green{0};
  unsigned char m_blue{0};
};

#endif // RGBCOLOR_HPP
