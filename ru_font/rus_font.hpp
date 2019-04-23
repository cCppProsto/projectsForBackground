#ifndef RUS_FONT_H
#define RUS_FONT_H


#include  <utility>
#include <stdint.h>


class rusFont
{
public:
  static rusFont &instance();

  const uint8_t *getBorderBitmap(char16_t ch);
  const uint8_t *getCharBitmap(char16_t ch);

  const std::pair<int, int> getCharSize(char16_t ch);

private:
  rusFont();
};

#endif // RUS_FONT_H
