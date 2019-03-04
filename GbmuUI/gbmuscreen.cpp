#include "gbmuscreen.h"

#include "mainwindow.h"

#include <time.h>
#include <stdlib.h>

GbmuScreen::GbmuScreen(QWidget *parent)
    : QGraphicsView (parent)
{
    srand(time(NULL));
    _ptrParent = parent;
	setAutoFillBackground(false);
    move(FIT_VIEW_W, FIT_VIEW_H);
    resize(parent->width(), parent->height());
}

void GbmuScreen::updateGbScreen(void)
{
    resize(_ptrParent->width(), _ptrParent->height());
    QImage image = QImage(GB_WIDTH, GB_HEIGTH, QImage::Format_RGBA8888);
    for (int i = 0; i < GB_WIDTH; i++){
        for (int j = 0; j < GB_HEIGTH; j++){
           //to get cancer please try this image.setPixel(i, j, qRgba(rand() % 255 , rand() % 255, rand() % 255, 255));
			image.setPixel(i, j, g_gameboy.get_pixel(j, i));
        }
    }
    QGraphicsScene *scene = new QGraphicsScene(this);
    QPixmap p = QPixmap::fromImage(image.scaled(width(), height() - SKIP_TOOLBAR));
    scene->addPixmap(p);
    setScene(scene);
}
