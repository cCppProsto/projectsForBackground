#ifndef ROOMOBJECTS_HPP
#define ROOMOBJECTS_HPP


enum class eTypeRoomObject
{
  Barrel
};


class roomObjects
{
public:
  roomObjects(eTypeRoomObject aType);

  virtual ~roomObjects();

  virtual void draw() const = 0;

  void setRoomPos(int aX, int aY);
  void setPos(int aX, int aY);

  const int &width()const;
  const int &height()const;

  const int &x()const;
  const int &y()const;
  const int &room_x()const;
  const int &room_y()const;

protected:
  int m_x{0};
  int m_y{0};
  int m_room_x{0};
  int m_room_y{0};
  int m_width{0};
  int m_height{0};

  eTypeRoomObject m_type;


private:
  int m_id{0};
};

#endif // ROOMOBJECTS_HPP
