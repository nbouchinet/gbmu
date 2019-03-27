#include "gbmuscreen.h"

#include "mainwindow.h"
#include "src/sound/APU.hpp"
#include "src/sound/SoundChannel.hpp"

#include <stdlib.h>
#include <time.h>

GbmuScreen::GbmuScreen(QWidget *parent)
    : QGraphicsView(parent), _parent(parent) {
  // srand(time(NULL));
  setAutoFillBackground(false);
  move(FIT_VIEW_W, FIT_VIEW_H);
  resize(parent->width(), parent->height());

  _scene = std::make_unique<QGraphicsScene>(this);

  setScene(_scene.get());
}

void GbmuScreen::updateGbScreen(void) {
  static int colors[4][3] = {
    {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, { 0, 127, 127}
  };
  if (_parent->width() != width() || _parent->height() != height())
    resize(_parent->width(), _parent->height() - SKIP_TOOLBAR * 2);

  QImage image = QImage(GB_WIDTH, GB_HEIGTH, QImage::Format_RGBA8888);
  for (int j = 0; j < GB_HEIGTH; j++) {
    for (int i = 0; i < GB_WIDTH; i++) {
      uint32_t rgba = g_gameboy->get_pixel(j, i);

      uint8_t r = (rgba & 0xFF000000) >> (3 * 8);
      uint8_t g = (rgba & 0x00FF0000) >> (2 * 8);
      uint8_t b = (rgba & 0x0000FF00) >> (1 * 8);
      uint8_t a = (rgba & 0x000000FF) >> (0 * 8);

      image.setPixel(i, j, qRgba(r, g, b, a));
    }
  }
  for (auto i = 0u; i < g_gameboy->components().apu->channels().size(); ++i ) {
    if (g_gameboy->components().apu->channels()[i].channel->get_raw_volume())
      image.setPixel(i, 0, qRgb(colors[i][0], colors[i][1], colors[i][2]));
    else 
      image.setPixel(i, 0, qRgb(0,0,0));
  }
  QPixmap p =
      QPixmap::fromImage(image.scaled(width(), height() - SKIP_TOOLBAR));
  _scene->clear();
  _scene->addPixmap(p);
}
