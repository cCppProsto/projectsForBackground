#include "roomobjects.hpp"

roomObjects::roomObjects(eTypeRoomObject aType)
  :m_type{aType}
{
  static int id{0};

  m_id = id++;
}
//------------------------------------------------------------------------------
roomObjects::~roomObjects()
{
}
//------------------------------------------------------------------------------
void roomObjects::setRoomPos(int aX, int aY)
{
  m_room_x = aX;
  m_room_y = aY;
}
//------------------------------------------------------------------------------
void roomObjects::setPos(int aX, int aY)
{
  m_x = aX;
  m_y = aY;
}
//------------------------------------------------------------------------------
const int &roomObjects::width()const
{
  return m_width;
}
//------------------------------------------------------------------------------
const int &roomObjects::height()const
{
  return m_height;
}
//------------------------------------------------------------------------------
const int &roomObjects::x()const
{
  return m_x;
}
//------------------------------------------------------------------------------
const int &roomObjects::y()const
{
  return m_y;
}
//------------------------------------------------------------------------------
const int &roomObjects::room_x()const
{
  return m_room_x;
}
//------------------------------------------------------------------------------
const int &roomObjects::room_y()const
{
  return m_room_y;
}














