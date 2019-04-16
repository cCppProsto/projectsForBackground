#include "hsvcolor.hpp"
//------------------------------------------------------------------------------
hsvColor::hsvColor(unsigned char aHue, unsigned char aSaturation, unsigned char aValue)
  :m_hue{aHue}
  ,m_saturation{aSaturation}
  ,m_value{aValue}
{
}
//------------------------------------------------------------------------------
const unsigned char &hsvColor::h()const
{
  return m_hue;
}
//------------------------------------------------------------------------------
const unsigned char &hsvColor::s()const
{
  return m_saturation;
}
//------------------------------------------------------------------------------
const unsigned char &hsvColor::v()const
{
  return m_value;
}
//------------------------------------------------------------------------------
rgbColor hsvColor::toRGB()
{
  rgbColor res{0,0,0};

  unsigned char region;
  unsigned char remainder;
  unsigned char p;
  unsigned char q;
  unsigned char t;

  if(m_saturation == 0)
  {
    res.setRed(m_value);
    res.setGreen(m_value);
    res.setBlue(m_value);
    return res;
  }

  region = m_hue / 43;
  remainder = (m_hue - (region * 43) * 6);

  p = (m_value * (255 - m_saturation)) >> 8;
  q = (m_value * (255 - ((m_saturation * remainder) >> 8))) >> 8;
  t = (m_value * (255 - ((m_saturation * (255 - remainder)) >> 8 ))) >> 8;

  switch(region)
  {
    case 0:
    {
      res.setRed(m_value);
      res.setGreen(t);
      res.setBlue(p);
      break;
    }
    case 1:
    {
      res.setRed(q);
      res.setGreen(m_value);
      res.setBlue(p);
      break;
    }
    case 2:
    {
      res.setRed(p);
      res.setGreen(m_value);
      res.setBlue(t);
      break;
    }
    case 3:
    {
      res.setRed(p);
      res.setGreen(q);
      res.setBlue(m_value);
      break;
    }
    case 4:
    {
      res.setRed(t);
      res.setGreen(p);
      res.setBlue(m_value);
      break;
    }
    default:
    {
      res.setRed(m_value);
      res.setGreen(p);
      res.setBlue(q);
      break;
    }
  }

  return res;
}




























