#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstddef>
#include <cstring>
#include <chrono>
#include <thread>

using namespace std;

//------------------------------------------------------------------------------
static const int g_window_width { 1000 };
static const int g_window_height { 1000 };
static const int g_point_size {1};
static const char *g_window_title {"Life"};
//------------------------------------------------------------------------------

static int g_field_w{0};
static int g_field_h{0};
static uint8_t *g_p_field_1 {nullptr};
static uint8_t *g_p_field_2 {nullptr};
static int g_start_x{0};
static int g_start_y{0};

static bool g_is_pause{true};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
static void gl_init();
static void gl_mouse_func(int aButton, int aState, int aX, int aY);
static void gl_idle_func(void);
static void gl_key_func(unsigned char aKey, int aX, int aY);
static void gl_draw_func(void);
//------------------------------------------------------------------------------
static void init_data();
static void draw_points();
static void draw_border();
static void calc_next_field_data();
static void test_field_init();
//------------------------------------------------------------------------------



int main()
{
  int i = 1;
  char *ch ="";

  glutInit(&i, &ch);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(g_window_width, g_window_height);
  glutCreateWindow(g_window_title);

  gl_init();

  init_data();

  // for test
  test_field_init();

  glutMainLoop();

  cout << "Hello World!" << endl;
  return 0;
}


//------------------------------------------------------------------------------
void gl_init()
{
  glViewport(0, 0, static_cast<GLsizei>(g_window_width), static_cast<GLsizei>(g_window_height));
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, g_window_width, g_window_height, 0, 0, 1);

  glutKeyboardFunc(gl_key_func);
  glutMouseFunc(gl_mouse_func);
  glutDisplayFunc(gl_draw_func);
  glutIdleFunc(gl_idle_func);
}
//------------------------------------------------------------------------------
void gl_mouse_func(int aButton,
                   int aState,
                   int aX,
                   int aY)
{
  switch(aButton)
  {
    case GLUT_LEFT_BUTTON:
    {
      if(aState == 1) // left button released
      {
        if(aX < g_start_x)
          return;

        if(aX >= g_start_x + (g_field_w*g_point_size))
          return;

        if(aY + g_point_size < g_start_y)
          return;

        if((aY + g_point_size) >= g_start_y + (g_field_h*g_point_size) )
          return;

        int x = aX - g_start_x + g_point_size / 2;
        int y = aY - g_start_y + g_point_size;

        int point_x { x / g_point_size };
        int point_y { y / g_point_size };

        if(g_p_field_1[point_y * g_field_w + point_x] == 1)
          g_p_field_1[point_y * g_field_w + point_x] = 0;
        else
          g_p_field_1[point_y * g_field_w + point_x] = 1;
      }
      break;
    }
  }
}
//------------------------------------------------------------------------------
void gl_idle_func(void)
{
  glutPostRedisplay();
}
//------------------------------------------------------------------------------
void gl_key_func(unsigned char aKey,
                 int /*aX*/,
                 int /*aY*/
                 )
{
  switch (aKey)
  {
    case 32:
    {
      g_is_pause = !g_is_pause;
      break;
    }
    case 27:
    {
      exit(0);
    }
  }
}
//------------------------------------------------------------------------------
void gl_draw_func(void)
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  draw_points();
  draw_border();

  if(!g_is_pause)
  {
    calc_next_field_data();
    std::this_thread::sleep_for(std::chrono::milliseconds(33));
  }

  glutSwapBuffers();
}
//------------------------------------------------------------------------------
void init_data()
{
  g_field_w = (g_window_width - 200) / g_point_size;
  g_field_h = (g_window_height - 200) / g_point_size;

  g_start_x = 100;
  g_start_y = 100;

  int array_size {g_field_w * g_field_h};
  g_p_field_1 = new uint8_t[array_size];
  g_p_field_2 = new uint8_t[array_size];

  std::memset(g_p_field_1, 0, sizeof(uint8_t) * array_size);
  std::memset(g_p_field_2, 0, sizeof(uint8_t) * array_size);
}
//------------------------------------------------------------------------------
void draw_points()
{
  glPointSize(g_point_size);
  glBegin(GL_POINTS);
  int offset{0};
  for(int l = 0; l < g_field_h; ++l)
  {
    for(int c = 0; c < g_field_w; ++c)
    {
      offset = l*g_field_w + c;
      if(g_p_field_1[offset] == 1)
      {
        glVertex2i(g_start_x + static_cast<int>(c * g_point_size),
                   g_start_y + static_cast<int>(l * g_point_size));
      }
    }
  }
  glEnd();
}
//------------------------------------------------------------------------------
void draw_border()
{
  glPointSize(1);
  glBegin(GL_LINE_LOOP);
    glVertex2i(g_start_x - g_point_size / 2, g_start_y - g_point_size / 2);
    glVertex2i(g_start_x + g_field_w * g_point_size - g_point_size / 2, g_start_y- g_point_size / 2);
    glVertex2i(g_start_x + g_field_w * g_point_size- g_point_size / 2, g_start_y + g_field_w * g_point_size- g_point_size / 2);
    glVertex2i(g_start_x- g_point_size / 2, g_start_y + g_field_w * g_point_size- g_point_size / 2);
  glEnd();
}
//------------------------------------------------------------------------------
void calc_next_field_data()
{
  int offset{0};
  for(int l = 0; l < g_field_h; ++l)
  {
    for(int c = 0; c < g_field_w; ++c)
    {
      /*
       *  lt  t  rt
       *   l  X   r
       *  lb  b  rb
      */
      int lt_x = (c - 1) > 0 ? c - 1 : g_field_w - 1;
      int lt_y = (l - 1) > 0 ? l - 1 : g_field_h - 1;
      int lt_offset = lt_y*g_field_w + lt_x;

      int t_x = c;
      int t_y = (l - 1) > 0 ? l - 1 : g_field_h - 1;
      int t_offset = t_y*g_field_w + t_x;

      int rt_x = ((c + 1) >= g_field_w) ? 0 : c + 1 ;
      int rt_y = ((l - 1) > 0) ? l - 1 : g_field_h - 1 ;
      int rt_offset = rt_y*g_field_w + rt_x;

      int l_x = (c - 1) > 0 ? c - 1 : g_field_w - 1;
      int l_y = l;
      int l_offset = l_y*g_field_w + l_x;

      int r_x = ((c + 1) >= g_field_w) ? 0 : c + 1;
      int r_y = l;
      int r_offset = r_y*g_field_w + r_x;

      int b_x = c;
      int b_y = ((l + 1) >= g_field_h) ? 0 : l + 1;
      int b_offset = b_y*g_field_w + b_x;

      int lb_x = (c - 1) > 0 ? c - 1 : g_field_w - 1;
      int lb_y = ((l + 1) >= g_field_h) ? 0 : l + 1;
      int lb_offset = lb_y*g_field_w + lb_x;

      int rb_x = ((c + 1) >= g_field_w) ? 0 : c + 1;
      int rb_y = ((l + 1) >= g_field_h) ? 0 : l + 1;
      int rb_offset = rb_y*g_field_w + rb_x;

      int count { 0 };
      if(g_p_field_1[lt_offset] == 1) ++count;
      if(g_p_field_1[rt_offset] == 1) ++count;
      if(g_p_field_1[l_offset] == 1)  ++count;
      if(g_p_field_1[r_offset] == 1)  ++count;
      if(g_p_field_1[lb_offset] == 1) ++count;
      if(g_p_field_1[rb_offset] == 1) ++count;
      if(g_p_field_1[t_offset] == 1)  ++count;
      if(g_p_field_1[b_offset] == 1)  ++count;

      offset = l*g_field_w + c;
      if(count == 3)
        g_p_field_2[offset] = 1;
      if(count == 2)
        g_p_field_2[offset] = g_p_field_1[offset];

      if(count < 2)
        g_p_field_2[offset] = 0;
      if(count > 3)
        g_p_field_2[offset] = 0;
    }
  }
  std::memcpy(g_p_field_1, g_p_field_2, sizeof(uint8_t) * (g_field_w * g_field_h));

  std::memset(g_p_field_2, 0, sizeof(uint8_t) * (g_field_w * g_field_h));
}
//------------------------------------------------------------------------------
void test_field_init()
{
  int offset{0};
  for(int l = 0; l < g_field_h; ++l)
  {
    for(int c = 0; c < g_field_w; ++c)
    {
      if(std::rand() % 4)
      {
        offset = l*g_field_w + c;
        g_p_field_1[offset] = 1;
      }
    }
  }
}


















