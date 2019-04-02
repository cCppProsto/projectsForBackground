#ifndef APPSETTINGS_HPP
#define APPSETTINGS_HPP


class appSettings
{
public:
  static appSettings &instance();

  const int &windowWidth()const;
  const int &windowHeight()const;
  const int &drawObjPtSize()const;

private:
  appSettings();

private:
  int m_window_width{800};
  int m_window_heigth{800};
  int m_draw_objects_pt_size{50};
};

#endif // APPSETTINGS_HPP
