#ifndef APPSETTINGS_HPP
#define APPSETTINGS_HPP


class appSettings
{
public:
  static appSettings &instance();

  const int &windowWidth()const;
  const int &windowHeight()const;
  const float &drawObjPtSize()const;

  void increaseDrawPointSize();
  void decreaseDrawPointSize();

private:
  appSettings();

private:
  int m_window_width{800};
  int m_window_heigth{800};
  float m_draw_objects_pt_size{40};
};

#endif // APPSETTINGS_HPP
