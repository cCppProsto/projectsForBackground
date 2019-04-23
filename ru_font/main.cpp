#include <iostream>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <string>

#include "rus_font.hpp"

using namespace std;

//------------------------------------------------------------------------------
#define SCREEN_WIDTH        600
#define SCREEN_HEIGHT       600
#define IS_FULL_SCREEN      0
//------------------------------------------------------------------------------
GLFWwindow* window;

int    scr_width     = 0;
int    scr_height    = 0;
float  w_ratio       = 0.f;
float  h_ratio       = 0.f;
double cursor_x      = 0.;
double cursor_y      = 0.;

//------------------------------------------------------------------------------
void resize_clb     (GLFWwindow*, int, int);
void key_click_clb  (GLFWwindow*, int, int, int, int);
void mouse_click_clb(GLFWwindow*, int, int, int);

void draw_symbol()
{
  static std::u16string str = u"АаБбВвГгДдЕе";

  static auto &font {rusFont::instance()};

  int x = 100;
  int y = 100;
  int w = 12;
  for(const auto &ch : str)
  {
    glRasterPos2d(x, y);
    glColor3ub(0, 0, 0);
    const auto &sz{font.getCharSize(ch)};
    glBitmap(sz.first, sz.second, 0, 0, 0, 0, font.getBorderBitmap(ch));

    glRasterPos2d(x, y);
    glColor3ub(254, 254, 254);
    glBitmap(sz.first, sz.second, 0, 0, w, 0, font.getCharBitmap(ch));
    x += sz.first;
  }

  //glBitmap(8, 8, 0, 0, 8, 0, a.l);
  //glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
  //glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
  //glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
  /*
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


  // Вывод битового массива
  glBitmap(8, 8, 0, 0, 0, 0, a.l);


  //glDrawPixels()
  */
}
//------------------------------------------------------------------------------
int gl_init()
{
  if (!glfwInit())
    return -1;


  window = glfwCreateWindow(SCREEN_WIDTH,
                            SCREEN_HEIGHT,
                            "snow",
                            IS_FULL_SCREEN ? glfwGetPrimaryMonitor() : NULL,
                            NULL);

  glfwSetWindowPos(window,0,20);

  glfwGetWindowSize(window, &scr_width, &scr_height);

  w_ratio = (float)scr_width  / (float)SCREEN_WIDTH;
  h_ratio = (float)scr_height / (float)SCREEN_HEIGHT;


  if (!window)
  {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  glfwSetKeyCallback        (window, key_click_clb);
  glfwSetWindowSizeCallback (window, resize_clb);
  glfwSetMouseButtonCallback(window, mouse_click_clb);


  glViewport(0, 0, (GLsizei)SCREEN_WIDTH, (GLsizei)SCREEN_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1);
  glfwSwapInterval(1);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);

  glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
  glClearColor (0.0, 0.0, 0.0, 0.0);

  return 1;
}
int main()
{
  if(gl_init() == -1)
      return 0;

  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //glClearColor(100,100,100, 0);
    draw_symbol();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);
    /* Poll for and process events */
    glfwPollEvents();
  }
  glfwTerminate();
}

//------------------------------------------------------------------------------
void resize_clb(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);

  glfwGetWindowSize(window, &scr_width, &scr_height);
  w_ratio = (float)scr_width  / (float)SCREEN_WIDTH;
  h_ratio = (float)scr_height / (float)SCREEN_HEIGHT;
}
//------------------------------------------------------------------------------
void key_click_clb(GLFWwindow *pWindow, int aKey, int aScanCode, int aAction, int aMods)
{
  if(aKey == GLFW_KEY_ESCAPE && aAction == GLFW_PRESS)
    glfwSetWindowShouldClose(pWindow, GL_TRUE);
}
//------------------------------------------------------------------------------
void mouse_click_clb(GLFWwindow *pWindow, int aBtn, int aAction, int aMods)
{
  if(aBtn == GLFW_MOUSE_BUTTON_1)
  {
    switch(aAction)
    {
      case GLFW_PRESS:
      {
        glfwGetCursorPos(pWindow, &cursor_x, &cursor_y);
        break;
      }
    }
  }
}
