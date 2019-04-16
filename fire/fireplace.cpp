#include "fireplace.hpp"
#include <globaldata.hpp>

firePlace::firePlace()
{
}
//------------------------------------------------------------------------------
void firePlace::setPos(int aX, int aY, eFireType aType /* = eFireType::Type1 */ )
{
  m_x = aX;
  m_y = aY;
  m_type = aType;
}
//------------------------------------------------------------------------------
void firePlace::tick()
{
  if(m_value <= 0)
    return;

  switch(m_type)
  {
    case eFireType::Type1:
    {
      _set_data_type_1();
      break;
    }
    case eFireType::Type2:
    {
      _set_data_type_2();
      break;
    }
    case eFireType::Type3:
    {
      _set_data_type_3();
      break;
    }
  }
  m_float_value -= m_decrease_life_value;
  m_value = m_float_value;
}
//------------------------------------------------------------------------------
void firePlace::setLifeTime(int aTickCount)
{
  m_decrease_life_value = 255.f / aTickCount;
}
//------------------------------------------------------------------------------
void firePlace::_set_data_type_1()
{
  auto &gd{globalData::instance()};
  gd.setFireIndex(m_x, m_y, m_value);
}
//------------------------------------------------------------------------------
void firePlace::_set_data_type_2()
{
  auto &gd{globalData::instance()};

  gd.setFireIndex(m_x, m_y, m_value);
  gd.setFireIndex(m_x-1, m_y, m_value);
  gd.setFireIndex(m_x+1, m_y, m_value);
  gd.setFireIndex(m_x+1, m_y-1, m_value);
}
//------------------------------------------------------------------------------
void firePlace::_set_data_type_3()
{
  auto &gd{globalData::instance()};

  gd.setFireIndex(m_x, m_y, m_value);
  gd.setFireIndex(m_x-1, m_y, m_value);
  gd.setFireIndex(m_x-2, m_y, m_value);
  gd.setFireIndex(m_x+1, m_y, m_value);
  gd.setFireIndex(m_x+2, m_y, m_value);

  gd.setFireIndex(m_x, m_y, m_value);
  gd.setFireIndex(m_x-1, m_y-1, m_value);
  gd.setFireIndex(m_x+1, m_y-1, m_value);

  gd.setFireIndex(m_x, m_y-2, m_value);
}
