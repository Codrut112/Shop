#include "draw.h"

void Desen::paintEvent(QPaintEvent* ev)
{
	
		QPainter p{ this };
		int x = 0;
		int y = 0;
		for (const auto& prod : mag.get_all_cos()) {

			x = rand() % 400 + 1;
			y = rand() % 400 + 1;
			qDebug() << x << " " << y;
			QRectF target(x, y, 500, 380);
			QRectF source(0, 0, 732, 720);

			if (x % 2 == 0 and y % 2 == 0)p.drawImage(target, QImage("paine"), source);
			if (x % 2 == 1 and y % 2 == 1)p.drawImage(target, QImage("laptop.jpg"), source);
			if (x % 2 == 1 and y % 2 == 0)p.drawImage(target, QImage("lapte.jpg"), source);
			if (x % 2 == 0 and y % 2 == 1)p.drawImage(target, QImage("apa.jpg"), source);
			x += 40;

		}
	}

