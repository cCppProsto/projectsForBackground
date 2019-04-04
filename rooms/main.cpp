#include <GL/glut.h>
#include <cstddef>

#include "appsettings.hpp"
#include "room.hpp"

//------------------------------------------------------------------------------
static const char *g_window_title = "rooms";

//------------------------------------------------------------------------------
static void gl_init(void);
static void gl_idle_func(void);
static void gl_draw_func(void);
static void gl_key_func(unsigned char aKey, int aX, int aY);
static void gl_mouse_func(int aButton, int aState, int aX, int aY);

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

room g_room_a;
room g_room_b;

static void init_room_a()
{
  g_room_a.setPosition(1, 1);
  g_room_a.setSize(256, 256);
  g_room_a.setGroundType(eGroundType::GroundType_1);

  g_room_a.addDoor(256, 32*3, 256, 32*5, true);

  g_room_a.addRoomObject(eTypeRoomObject::Barrel, 0, 0);
  g_room_a.addRoomObject(eTypeRoomObject::Barrel, 224, 0);
}

//------------------------------------------------------------------------------
int main()
{
  auto &app_stg{appSettings::instance()};

  int i{1};
  char *ch="";

  glutInit(&i, &ch);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(app_stg.windowWidth(), app_stg.windowHeight());
  glutCreateWindow(g_window_title);

  gl_init();

  init_room_a();

  glutMainLoop();

  return 0;
}
//------------------------------------------------------------------------------
void gl_init(void)
{
  auto &app_stg{appSettings::instance()};

  glViewport(0, 0, static_cast<int>(app_stg.windowWidth()), static_cast<int>(app_stg.windowHeight()));
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, app_stg.windowWidth(), app_stg.windowHeight(), 0, 0, 1);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  glutKeyboardFunc(gl_key_func);
  glutMouseFunc(gl_mouse_func);
  glutIdleFunc(gl_idle_func);
  glutDisplayFunc(gl_draw_func);
}
//------------------------------------------------------------------------------
void gl_idle_func(void)
{
  glutPostRedisplay();
}
//------------------------------------------------------------------------------
void gl_draw_func(void)
{
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);

  g_room_a.draw();
  g_room_b.draw();

  glutSwapBuffers();
}
//------------------------------------------------------------------------------
void gl_key_func(unsigned char aKey, int aX, int aY)
{
  auto &app_stg{appSettings::instance()};

  switch(aKey)
  {
    case 43:  // +
    {
      app_stg.increaseDrawPointSize();
      break;
    }
    case 45:  // -
    {
      app_stg.decreaseDrawPointSize();
      break;
    }
    case 27:
    {
      exit(0);
    }
  }
}
//------------------------------------------------------------------------------
void gl_mouse_func(int aButton, int aState, int aX, int aY)
{

}
