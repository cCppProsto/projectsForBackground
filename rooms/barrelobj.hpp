#ifndef BARRELOBJ_HPP
#define BARRELOBJ_HPP

#include "roomobjects.hpp"

class barrelObj final : public roomObjects
{
public:
  barrelObj();

  void draw () const;

  void open();
  void close();

private:
  void _load_textures();

private:
  bool m_is_opened {false};

  unsigned int m_opened_texture{0};
  unsigned int m_closed_texture{0};
};

#endif // BARRELOBJ_HPP
