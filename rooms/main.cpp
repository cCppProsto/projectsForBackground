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

  g_room_a.setPosition(100,100);
  g_room_a.setSize(10, 10);

  g_room_a.addDoor(5, 0, 8, 0, true);
  g_room_a.addDoor(1, 0, 2, 0, false);

  g_room_a.addDoor(5, 9, 8, 9, false);
  g_room_a.addDoor(1, 9, 2, 9, true);
  g_room_a.addDoor(3, 9, 4, 9, true, false);

  g_room_a.addDoor(0, 2, 0, 4, true);
  g_room_a.addDoor(0, 7, 0, 9, false);

  g_room_a.addDoor(9, 2, 9, 4, false);
  g_room_a.addDoor(9, 7, 9, 9, true);


  g_room_b.setPosition(200,100);
  g_room_b.setSize(10, 10);

  g_room_b.addDoor(5, 0, 8, 0, true);
  g_room_b.addDoor(1, 0, 2, 0, false);

  g_room_b.addDoor(5, 9, 8, 9, false);
  g_room_b.addDoor(1, 9, 2, 9, true);
  g_room_b.addDoor(3, 9, 4, 9, true, false);

  g_room_b.addDoor(0, 2, 0, 4, true);
  g_room_b.addDoor(0, 7, 0, 9, false);

  g_room_b.addDoor(9, 2, 9, 4, false);
  g_room_b.addDoor(9, 7, 9, 9, true);

  gl_init();

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
