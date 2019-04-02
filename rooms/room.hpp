#ifndef ROOM_HPP
#define ROOM_HPP

#include <vector>

class room
{
  struct sLine
  {
    int x1;
    int y1;
    int x2;
    int y2;
  };

  struct sDoor
  {
    sDoor(int aX1,
          int aY1,
          int aX2,
          int aY2,
          bool aIsOpened,
          bool aIsPresent)
      :x1{aX1}
      ,y1{aY1}
      ,x2{aX2}
      ,y2{aY2}
      ,is_opened{aIsOpened}
      ,is_present{aIsPresent}
    {
    }

    int x1{0};
    int y1{0};
    int x2{0};
    int y2{0};
    bool is_opened{false};
    bool is_present{false};
  };

public:
  room();

  void setPosition(int aX, int aY);
  void setSize(int aWidth, int aHeight);

  void addDoor(int aX1, int aY1,
               int aX2, int aY2,
               bool aIsOpened = false,
               bool aIsPresent = true);

  void draw()const;

private:
  void _draw_border()const;
  void _draw_doors()const;

  void _calc_top_border_lines();
  void _calc_bottom_border_lines();
  void _calc_right_border_lines();
  void _calc_left_border_lines();

private:
  int m_x{0};
  int m_y{0};
  int m_width{0};
  int m_height{0};

  std::vector<sLine> mv_border_lines;
  std::vector<sDoor> mv_doors;
};

#endif // ROOM_HPP
