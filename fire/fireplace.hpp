#ifndef FIREPLACE_HPP
#define FIREPLACE_HPP


class firePlace
{
public:

//  type 1
//     x

//  type 2
//     x
//    xxx

//  type 3
//     x
//    xxx
//   xxxxx

  enum class eFireType
  {
    Type1
   ,Type2
   ,Type3
  };

public:
  firePlace();

  void setPos(int aX, int aY, eFireType aType = eFireType::Type1);
  void tick();

  void setLifeTime(int aTickCount);

private:
  void _set_data_type_1();
  void _set_data_type_2();
  void _set_data_type_3();

private:
  int m_x{0};
  int m_y{0};
  eFireType m_type{eFireType::Type1};

  unsigned int m_value{255};

  float m_float_value{255.f};
  float m_decrease_life_value{0.f};
};


#endif // FIREPLACE_HPP
