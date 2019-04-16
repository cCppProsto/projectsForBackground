#include <algorithm>

#include "globaldata.hpp"
#include "hsvcolor.hpp"

static rgbColor g_palette[256];

//------------------------------------------------------------------------------
globalData::globalData()
{
  _init_palette();
}
//------------------------------------------------------------------------------
globalData &globalData::instance()
{
  static globalData res;
  return res;
}
//------------------------------------------------------------------------------
void globalData::setWindowSize(int aWidth, int aHeight)
{
  m_width = aWidth;
  m_height = aHeight;

  if(mp_fire != nullptr)
  {
    for(int i = 0; i < aWidth + 1; ++i)
      delete [] mp_fire[i];
    delete [] mp_fire;
  }

  mp_fire = new unsigned int*[aHeight + 1];
  for(int i = 0; i < aWidth + 1; ++i)
     mp_fire[i] = new unsigned int[aWidth + 1];
}
//------------------------------------------------------------------------------
const int &globalData::windowWidth()const
{
  return m_width;
}
//------------------------------------------------------------------------------
const int &globalData::windowHeight()const
{
  return m_height;
}
//------------------------------------------------------------------------------
rgbColor *globalData::palette()
{
  return g_palette;
}
//------------------------------------------------------------------------------
void globalData::_init_palette()
{
  for(unsigned char x = 0; x != 255; ++x)
  {
    hsvColor hsv{ static_cast<unsigned char>(x / 5),
                  255,
                  static_cast<unsigned char>(std::min(255, x * 2)) };
    g_palette[x] = hsv.toRGB();
  }
}
//------------------------------------------------------------------------------
void globalData::setFireIndex(int aX, int aY, unsigned int aValue)
{
  if(aX >=0 && aX < m_width)
    if(aY >=0 && aY < m_height)
      mp_fire[aX][aY] = aValue;
}
//------------------------------------------------------------------------------
unsigned int globalData::fireMapValue(int aX, int aY)
{
  if(aX >=0 && aX < m_width)
    if(aY >=0 && aY < m_height)
      return mp_fire[aX][aY];
  return 0;
}


