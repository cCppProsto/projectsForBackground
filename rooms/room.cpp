#include <algorithm>
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
void room::setSize(int aWidth, int aHeight)
{
  // size in points
  m_width = aWidth;
  m_height = aHeight;

  mv_border_lines.push_back( {0, 0, m_width - 1, 0} ); // top
  mv_border_lines.push_back( {m_width - 1, 0, m_width - 1, m_height - 1} ); // rigth
  mv_border_lines.push_back( {m_width - 1, m_height - 1, 0, m_height - 1} ); // bottom
  mv_border_lines.push_back( {0, m_height - 1, 0, 0} ); // left
}
//------------------------------------------------------------------------------
void room::addDoor(int aX1, int aY1,
                   int aX2, int aY2,
                   bool aIsOpened  /* = false */,
                   bool aIsPresent /* = true  */ )
{
  mv_doors.push_back({aX1, aY1, aX2, aY2, aIsOpened, aIsPresent});

  mv_border_lines.clear();

  _calc_top_border_lines();
  _calc_bottom_border_lines();
  _calc_right_border_lines();
  _calc_left_border_lines();
}
//------------------------------------------------------------------------------
void room::draw()const
{
  _draw_border();
  _draw_doors();
}
//------------------------------------------------------------------------------
void room::_draw_border()const
{
  auto &app_stg{appSettings::instance()};

  float pt_sz {app_stg.drawObjPtSize()};

  glColor3ub(0, 0, 254);
  glLineWidth(1.f);
  for(auto &l : mv_border_lines)
  {
    glBegin(GL_LINES);
    glVertex2i(m_x + static_cast<int>(l.x1 * pt_sz), m_y + static_cast<int>(l.y1 * pt_sz));
    glVertex2i(m_x + static_cast<int>(l.x2 * pt_sz), m_y + static_cast<int>(l.y2 * pt_sz));
    glEnd();
  }
}
//------------------------------------------------------------------------------
void room::_draw_doors()const
{
  auto &app_stg{appSettings::instance()};

  float pt_sz {app_stg.drawObjPtSize()};

  glLineWidth(4.f);
  for(auto &d : mv_doors)
  {
    if(d.is_present)
    {
      if(d.is_opened)
        glColor3ub(0, 254, 0);
      else
        glColor3ub(254, 0, 0);

      glBegin(GL_LINES);
        glVertex2i(m_x + d.x1 * pt_sz, m_y + d.y1 * pt_sz);
        glVertex2i(m_x + d.x2 * pt_sz, m_y + d.y2 * pt_sz);
      glEnd();
    }
  }
}
//------------------------------------------------------------------------------
void room::_calc_top_border_lines()
{
  std::vector<sDoor> tmp;

  for(auto &d : mv_doors)
  {
    if( (d.y1 == 0) && (d.y2 == 0) )
      tmp.push_back(d);
  }

  int x1{0};
  int y1{0};
  int x2{ m_width - 1};
  int y2{0};

  if(!tmp.empty())
  {
    std::sort(tmp.begin(), tmp.end(), [](const sDoor &d1, const sDoor &d2) -> bool
                                      {
                                        return d1.x1 < d2.x2;
                                      });

    for(auto &d : tmp)
    {
      x2 = d.x1;
      y2 = d.y1;

      mv_border_lines.push_back({x1, y1, x2, y2});

      x1 = d.x2;
      y1 = d.y2;
    }

    if(tmp.back().x2 < (m_width - 1))
      mv_border_lines.push_back({x1, y1, m_width - 1, 0});
  }
  else
  {
    mv_border_lines.push_back({x1, y1, x2, y2});
  }
}
//------------------------------------------------------------------------------
void room::_calc_bottom_border_lines()
{
  std::vector<sDoor> tmp;

  for(auto &d : mv_doors)
  {
    if( (d.y1 == (m_height - 1)) && (d.y2 == (m_height - 1)) )
      tmp.push_back(d);
  }

  int x1{0};
  int y1{ m_height - 1};
  int x2{ m_width - 1};
  int y2{ m_height - 1};

  if(!tmp.empty())
  {
    std::sort(tmp.begin(), tmp.end(), [](const sDoor &d1, const sDoor &d2) -> bool
                                      {
                                        return d1.x1 < d2.x2;
                                      });

    for(auto &d : tmp)
    {
      x2 = d.x1;
      y2 = d.y1;

      mv_border_lines.push_back({x1, y1, x2, y2});

      x1 = d.x2;
      y1 = d.y2;
    }

    if(tmp.back().x2 < (m_width - 1))
      mv_border_lines.push_back({x1, y1, m_width - 1, m_height - 1});
  }
  else
  {
    mv_border_lines.push_back({x1, y1, x2, y2});
  }
}
//------------------------------------------------------------------------------
void room::_calc_right_border_lines()
{
  std::vector<sDoor> tmp;

  for(auto &d : mv_doors)
  {
    if( (d.x1 == (m_width - 1) ) && (d.x2 == (m_width - 1) ) )
      tmp.push_back(d);
  }

  int x1{m_width - 1};
  int y1{0};
  int x2{ m_width - 1};
  int y2{m_height - 1};

  if(!tmp.empty())
  {
    std::sort(tmp.begin(), tmp.end(), [](const sDoor &d1, const sDoor &d2) -> bool
                                      {
                                        return d1.y1 < d2.y2;
                                      });

    for(auto &d : tmp)
    {
      x2 = d.x1;
      y2 = d.y1;

      mv_border_lines.push_back({x1, y1, x2, y2});

      x1 = d.x2;
      y1 = d.y2;
    }

    if(tmp.back().y2 < (m_height - 1))
      mv_border_lines.push_back({x1, y1, m_width - 1, m_height - 1});
  }
  else
  {
    mv_border_lines.push_back({x1, y1, x2, y2});
  }
}
//------------------------------------------------------------------------------
void room::_calc_left_border_lines()
{
  std::vector<sDoor> tmp;

  for(auto &d : mv_doors)
  {
    if( (d.x1 == 0 ) && (d.x2 == 0 ) )
      tmp.push_back(d);
  }

  int x1{0};
  int y1{0};
  int x2{0};
  int y2{m_height - 1};

  if(!tmp.empty())
  {
    std::sort(tmp.begin(), tmp.end(), [](const sDoor &d1, const sDoor &d2) -> bool
                                      {
                                        return d1.y1 < d2.y2;
                                      });

    for(auto &d : tmp)
    {
      x2 = d.x1;
      y2 = d.y1;

      mv_border_lines.push_back({x1, y1, x2, y2});

      x1 = d.x2;
      y1 = d.y2;
    }

    if(tmp.back().y2 < (m_height - 1))
      mv_border_lines.push_back({x1, y1, 0, m_height - 1});
  }
  else
  {
    mv_border_lines.push_back({x1, y1, x2, y2});
  }
}





















