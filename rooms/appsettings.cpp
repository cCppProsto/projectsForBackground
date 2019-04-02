#include "appsettings.hpp"


//------------------------------------------------------------------------------
appSettings &appSettings::instance()
{
  static appSettings res;
  return res;
}
//------------------------------------------------------------------------------
appSettings::appSettings()
{
}
//------------------------------------------------------------------------------
const int &appSettings::windowWidth()const
{
  return m_window_width;
}
//------------------------------------------------------------------------------
const int &appSettings::windowHeight()const
{
  return m_window_heigth;
}
//------------------------------------------------------------------------------
const int &appSettings::drawObjPtSize()const
{
  return m_draw_objects_pt_size;
}

