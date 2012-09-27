#ifndef HADES_H
#define HADES_H

#include <QtGui/QMainWindow>
#include <QTimer>
#include "ui_hades.h"

#define MAP_WIDTH 128

class Hades : public QMainWindow
{
	Q_OBJECT

public:
	Hades(QWidget *parent = 0, Qt::WFlags flags = 0);

	void _init();

	void _clear();
	~Hades();

	void paintEvent(QPaintEvent *pEvent);
	void keyPressEvent(QKeyEvent *pEvent);
	void mousePressEvent(QMouseEvent *pEvent);

public slots:
	void on_timer_timeout();

private:
	Ui::HadesClass ui;

	static int m_map[MAP_WIDTH][MAP_WIDTH];
	static int m_nextmap[MAP_WIDTH][MAP_WIDTH];
	uint envolution;
	bool m_bShowGrid;
	QTimer m_timer;
};

#endif // HADES_H
