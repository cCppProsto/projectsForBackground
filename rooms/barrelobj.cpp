#include <SOIL/SOIL.h>
#include <GL/gl.h>

#include "appsettings.hpp"
#include "barrelobj.hpp"

static const char *file_opened_texture = "pics/room_objects/barrel/barrel_opened.png";
static const char *file_closed_texture = "pics/room_objects/barrel/barrel_closed.png";

//------------------------------------------------------------------------------
barrelObj::barrelObj() : roomObjects(eTypeRoomObject::Barrel)
{
  _load_textures();
}
//------------------------------------------------------------------------------
void barrelObj::draw () const
{
  auto &app_stg{appSettings::instance()};

  glEnable(GL_TEXTURE_2D);

  if(m_is_opened)
    glBindTexture(GL_TEXTURE_2D, m_opened_texture);
  else
    glBindTexture(GL_TEXTURE_2D, m_closed_texture);

  glBegin(GL_QUADS);
    glTexCoord2i(0, 0); glVertex2i(m_x, m_y);
    glTexCoord2i(1, 0); glVertex2i(m_x + m_width * app_stg.drawObjPtSize(), m_y);
    glTexCoord2i(1, 1); glVertex2i(m_x + m_width * app_stg.drawObjPtSize(), m_y + m_height * app_stg.drawObjPtSize());
    glTexCoord2i(0, 1); glVertex2i(m_x, m_y + m_height * app_stg.drawObjPtSize());
  glEnd();
  glDisable(GL_TEXTURE_2D);
}
//------------------------------------------------------------------------------
void barrelObj::open()
{
  m_is_opened = true;
}
//------------------------------------------------------------------------------
void barrelObj::close()
{
  m_is_opened = false;
}
//------------------------------------------------------------------------------
void barrelObj::_load_textures()
{
  m_opened_texture = SOIL_load_OGL_texture(file_opened_texture,
                                           SOIL_LOAD_AUTO,
                                           SOIL_CREATE_NEW_ID,
                                           SOIL_FLAG_POWER_OF_TWO);

  m_closed_texture = SOIL_load_OGL_texture(file_closed_texture,
                                           SOIL_LOAD_AUTO,
                                           SOIL_CREATE_NEW_ID,
                                           SOIL_FLAG_POWER_OF_TWO);

  glBindTexture(GL_TEXTURE_2D, m_closed_texture);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &m_width);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &m_height);
  glBindTexture(GL_TEXTURE_2D, 0);
}













