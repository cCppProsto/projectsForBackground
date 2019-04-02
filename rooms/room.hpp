#ifndef ROOM_HPP
#define ROOM_HPP


class room
{
public:
  room();

  void setPosition(int aX, int aY);
  void draw()const;

private:
  int m_x{0};
  int m_y{0};
};

#endif // ROOM_HPP
