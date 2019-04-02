#include <GL/gl.h>

#include "room.hpp"
#include "appsettings.hpp"

//------------------------------------------------------------------------------
room::room()
{
}
//------------------------------------------------------------------------------
void room::setPosition(int aX, int aY)
{
  m_x = aX;
  m_y = aY;
}
//------------------------------------------------------------------------------
void room::draw()const
{
  auto &app_stg{appSettings::instance()};

  glPointSize(app_stg.drawObjPtSize());
  float offset {(float)app_stg.drawObjPtSize() / 2.f};
  glColor3ub(254, 254, 254);
  glBegin(GL_POINTS);
    glVertex2f((float)m_x + offset, (float)m_y + offset);
    //glVertex2i(m_x + offset + (app_stg.drawObjPtSize()), m_y + offset + (app_stg.drawObjPtSize()));
    //glVertex2i(m_x + (2 * app_stg.drawObjPtSize()), m_y + (2 * app_stg.drawObjPtSize()));
  glEnd();

  glColor3ub(254, 0, 0);
  glLineWidth(1);
  glBegin(GL_LINE_LOOP);
    glVertex2i(m_x, m_y);
    glVertex2i(m_x + app_stg.drawObjPtSize(), m_y);
    glVertex2i(m_x + app_stg.drawObjPtSize(), m_y + app_stg.drawObjPtSize());
    glVertex2i(m_x, m_y + app_stg.drawObjPtSize());
  glEnd();
}

