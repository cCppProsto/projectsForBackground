#ifndef GLOBALDATA_HPP
#define GLOBALDATA_HPP

#include "rgbcolor.hpp"


class globalData
{
public:
  static globalData &instance();

  void setWindowSize(int aWidth, int aHeight);

  const int &windowWidth()const;
  const int &windowHeight()const;

  rgbColor *palette();

  void setFireIndex(int aX, int aY, unsigned int aValue);
  unsigned int fireMapValue(int aX, int aY);

private:
  globalData();
  void _init_palette();

private:
  int m_width{0};
  int m_height{0};

  unsigned int **mp_fire{nullptr};
};

#endif // GLOBALDATA_HPP
