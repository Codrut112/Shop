#pragma once
#include "service.h"
#include <QWidget>
#include <QPainter>
class Desen :public QWidget, public Observer {
private:
	Magazin& mag;
	void paintEvent(QPaintEvent* ev) override;

	void update() override {
		repaint();
	};
	~Desen() {
		mag.unregister_observer(this);
	}

public:
	Desen(Magazin& mag) :mag{ mag } {
		mag.register_observer(this);
	};

};