#include <iostream>
#include <GL/glut.h>
#include <chrono>
#include <thread>
#include <vector>

#include "globaldata.hpp"
#include "fireplace.hpp"

//------------------------------------------------------------------------------
static void gl_init(void);
static void gl_idle_func(void);
static void gl_draw_func(void);
static void gl_key_func(unsigned char aKey, int aX, int aY);
static void gl_mouse_func(int aButton, int aState, int aX, int aY);
//------------------------------------------------------------------------------

static unsigned int summa_3_point(int x, int y, int &count);
static unsigned int summa_4_point(int x, int y, int &count);
static unsigned int summa_5_point(int x, int y, int &count);
static unsigned int summa_6_point(int x, int y, int &count);


static bool is_reinit_start_pos{true};
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

firePlace p1;
firePlace p2;
firePlace p3;

static std::vector<firePlace> g_fire_places;

int main()
{
  auto &gd{globalData::instance()};

  int i{1};
  char *ch = "";

  gd.setWindowSize(800, 800);

  glutInit(&i, &ch);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(gd.windowWidth(), gd.windowHeight());
  glutCreateWindow("fire");

  p1.setPos(100,390);
  p2.setPos(200,390, firePlace::eFireType::Type2);

  p3.setLifeTime(50);
  p3.setPos(300,390, firePlace::eFireType::Type3);

  gl_init();

  glutMainLoop();

  return 0;
}
//------------------------------------------------------------------------------
void gl_init(void)
{
  auto &gd{globalData::instance()};

  glViewport(0, 0, gd.windowWidth(), gd.windowHeight());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, gd.windowWidth(), gd.windowHeight(), 0, 0, 1);

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
  auto &gd{globalData::instance()};

  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);

  //if(is_reinit_start_pos)
  {
    for(int x = 0; x < gd.windowWidth(); x++)
    {
      gd.setFireIndex(x, gd.windowHeight()/2 , abs(32768 + rand()) % 256 );
    }
    is_reinit_start_pos = false;
  }

  for(auto &fp : g_fire_places)
    fp.tick();
  /*
  p1.tick();
  p2.tick();
  p3.tick();
  */

  glBegin(GL_POINTS);
  for(int y = 0; y < gd.windowHeight() - 1; ++y)
  {
    for(int x = 0; x < gd.windowWidth(); ++x)
    {
      int count{0};
      int value{0};

      //value = summa_3_point(x, y, count);
      //value = summa_4_point(x, y, count);
      //value = summa_5_point(x, y, count);
      value = summa_6_point(x, y, count);
      value /= count;
      value /= 1.0005;

      gd.setFireIndex(x, y, value);
      int index{value};
      auto &color{gd.palette()[index]};
      glColor3ub(color.r(), color.g(),color.b());
      glVertex2i(x, y);
    }
  }
  glEnd();

  glutSwapBuffers();

  //std::this_thread::sleep_for(std::chrono::milliseconds(16));
}
//------------------------------------------------------------------------------
void gl_key_func(unsigned char aKey, int aX, int aY)
{
  switch (aKey)
  {
    case 27:
    {
      exit(0);
    }
  }
}
//------------------------------------------------------------------------------
void gl_mouse_func(int aButton, int aState, int aX, int aY)
{
  switch(aButton)
  {
    case GLUT_LEFT_BUTTON:
    {
      if(aState == 1)
      {
        firePlace pl;

        if(rand()%2)
          pl.setLifeTime(40 + (rand() % 200));
        switch(rand() % 3)
        {
          case 0:
          {
            pl.setPos(aX, aY);
            break;
          }
          case 1:
          {
            pl.setPos(aX, aY, firePlace::eFireType::Type2);
            break;
          }
          case 2:
          {
            pl.setPos(aX, aY, firePlace::eFireType::Type3);
            break;
          }
        }
        g_fire_places.push_back(pl);
      }
      break;
    }
  }
}

//------------------------------------------------------------------------------
//
//    x*x
//     x
//
//------------------------------------------------------------------------------
unsigned int summa_3_point(int x, int y, int &count)
{
  auto &gd{globalData::instance()};
  unsigned int value{0};
  count = 0;

  int pos = y + 1;
  if( pos < gd.windowHeight())
  {
    value += gd.fireMapValue(x, pos);
    count++;
  }

  if(x > 0)
  {
    value += gd.fireMapValue(x - 1, y);
    count++;
  }

  if(x + 1 < gd.windowWidth())
  {
    value += gd.fireMapValue(x + 1, y);
    count++;
  }

  if(count == 0)
    count = 1;

  return value;
}
//------------------------------------------------------------------------------
//
//     *
//    xxx
//     x
//
//------------------------------------------------------------------------------
unsigned int summa_4_point(int x, int y, int &count)
{
  auto &gd{globalData::instance()};
  unsigned int value{0};
  count = 0;


  int pos = y + 2;
  if( pos < gd.windowHeight())
  {
    value += gd.fireMapValue(x, pos);
    count++;
  }

  pos = y + 1;
  if( pos < gd.windowHeight())
  {
    value += gd.fireMapValue(x, pos);
    count++;

    if(x > 0)
    {
      value += gd.fireMapValue(x - 1, pos);
      count++;
    }

    if(x + 1 < gd.windowWidth())
    {
      value += gd.fireMapValue(x + 1, pos);
      count++;
    }
  }

  if(count == 0)
    count = 1;

  return value;
}
//------------------------------------------------------------------------------
//
//    x*x
//    xxx
//
//------------------------------------------------------------------------------
unsigned int summa_5_point(int x, int y, int &count)
{
  auto &gd{globalData::instance()};
  unsigned int value{0};
  count = 0;

  int pos = y + 1;
  if( pos < gd.windowHeight())
  {
    value += gd.fireMapValue(x, pos);
    count++;
    if(x > 0)
    {
      value += gd.fireMapValue(x - 1, pos);
      count++;
    }

    if(x + 1 < gd.windowWidth())
    {
      value += gd.fireMapValue(x + 1, pos);
      count++;
    }
  }

  if(x > 0)
  {
    value += gd.fireMapValue(x - 1, y);
    count++;
  }

  if(x + 1 < gd.windowWidth())
  {
    value += gd.fireMapValue(x + 1, y);
    count++;
  }

  if(count == 0)
    count = 1;

  return value;
}
//------------------------------------------------------------------------------
//
//    x*x
//    xxx
//     x
//
//------------------------------------------------------------------------------
unsigned int summa_6_point(int x, int y, int &count)
{
  auto &gd{globalData::instance()};
  unsigned int value{0};
  count = 0;

  int pos = y + 2;
  if(pos < gd.windowHeight())
  {
    value += gd.fireMapValue(x, pos);
    count++;
  }

  pos = y + 1;
  if( pos < gd.windowHeight())
  {
    value += gd.fireMapValue(x, pos);
    count++;
    if(x > 0)
    {
      value += gd.fireMapValue(x - 1, pos);
      count++;
    }

    if(x + 1 < gd.windowWidth())
    {
      value += gd.fireMapValue(x + 1, pos);
      count++;
    }
  }

  if(x > 0)
  {
    value += gd.fireMapValue(x - 1, y);
    count++;
  }

  if(x + 1 < gd.windowWidth())
  {
    value += gd.fireMapValue(x + 1, y);
    count++;
  }

  if(count == 0)
    count = 1;

  return value;
}


