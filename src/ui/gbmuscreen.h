#ifndef GBMUSCREEN_H
# define GBMUSCREEN_H

#include <QImage>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
#include <memory>

# define GB_WIDTH 160
# define GB_HEIGTH 144
# define FIT_VIEW_W 0
# define FIT_VIEW_H 27
# define SKIP_TOOLBAR 18

class Helper;

class GbmuScreen : public QGraphicsView
{
	Q_OBJECT

	private:
        QWidget *_parent;
		std::unique_ptr<QGraphicsScene> _scene;
	public slots:
        void updateGbScreen(void);
	public:
        GbmuScreen(QWidget *parent);
};

#endif
