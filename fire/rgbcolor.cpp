#include "rgbcolor.hpp"

//------------------------------------------------------------------------------
rgbColor::rgbColor()
{
}
//------------------------------------------------------------------------------
rgbColor::rgbColor(unsigned char aRed, unsigned char aGreen, unsigned char aBlue)
  :m_red{aRed}
  ,m_green{aGreen}
  ,m_blue{aBlue}
{
}
//------------------------------------------------------------------------------
void rgbColor::setRed(unsigned char aValue)
{
  m_red = aValue;
}
//------------------------------------------------------------------------------
void rgbColor::setGreen(unsigned char aValue)
{
  m_green = aValue;
}
//------------------------------------------------------------------------------
void rgbColor::setBlue(unsigned char aValue)
{
  m_blue = aValue;
}
//------------------------------------------------------------------------------
const unsigned char &rgbColor::r()const
{
  return m_red;
}
//------------------------------------------------------------------------------
const unsigned char &rgbColor::g()const
{
  return m_green;
}
//------------------------------------------------------------------------------
const unsigned char &rgbColor::b()const
{
  return m_blue;
}
