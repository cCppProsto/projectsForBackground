#include <GL/glut.h>
#include <cstddef>

#include "appsettings.hpp"
#include "room.hpp"

//------------------------------------------------------------------------------
static const int g_window_width{1000};
static const int g_window_height{1000};
static const char *g_window_title = "rooms";

//------------------------------------------------------------------------------
static void gl_init(void);
static void gl_idle_func(void);
static void gl_draw_func(void);
static void gl_key_func(unsigned char aKey, int aX, int aY);
static void gl_mouse_func(int aButton, int aState, int aX, int aY);

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

room g_room;

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

  g_room.setPosition(1,1);

  gl_init();

  glutMainLoop();

  return 0;
}
//------------------------------------------------------------------------------
void gl_init(void)
{
  glViewport(0, 0, static_cast<int>(g_window_width), static_cast<int>(g_window_height));
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, g_window_width, g_window_height, 0, 0, 1);

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

  g_room.draw();

  glutSwapBuffers();
}
//------------------------------------------------------------------------------
void gl_key_func(unsigned char aKey, int aX, int aY)
{

}
//------------------------------------------------------------------------------
void gl_mouse_func(int aButton, int aState, int aX, int aY)
{

}
