#include "hades.h"
#include <QPainter>
#include <QDateTime>
#include <QKeyEvent>

#define CELL_WIDTH		10
#define TIME_INTERVAL	1000

int Hades::m_map[MAP_WIDTH][MAP_WIDTH];
int Hades::m_nextmap[MAP_WIDTH][MAP_WIDTH];


Hades::Hades(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	qsrand(QDateTime::currentDateTime().toTime_t());

	_init();

	m_bShowGrid = false;

	connect(&m_timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
	m_timer.start(TIME_INTERVAL);
}

Hades::~Hades()
{
	
}

void Hades::paintEvent( QPaintEvent *pEvent )
{
	QPainter painter(this);
	
	QBrush blackBrush(QColor(0,0,0));

	painter.fillRect(this->rect(),blackBrush);

	QBrush whiteBrush(QColor(255,255,255));

	for (int i = 0;i < MAP_WIDTH;i ++)
	{
		for (int j = 0;j < MAP_WIDTH;j ++)
		{
			if (m_map[i][j] == 1)
			{
				painter.fillRect(
					i * CELL_WIDTH,
					j * CELL_WIDTH,
					CELL_WIDTH,
					CELL_WIDTH,
					whiteBrush);
			}
		}
	}

	if (m_bShowGrid)
	{
		QPen grayPen(QColor(50,50,50));
		painter.setPen(grayPen);
		QVector<QLine> lstGrid;
		for (int i = 0;i < this->width();i +=10)
		{
			lstGrid.append(QLine(i,0,i,this->height()));
		}
		for (int i = 0;i < this->height();i +=10)
		{
			lstGrid.append(QLine(0,i,this->width(),i));
		}
		painter.drawLines(lstGrid);
	}
}

void Hades::on_timer_timeout()
{
	int alive = 0;

	for (int i = 0;i < MAP_WIDTH;i ++)
	{
		for (int j = 0;j < MAP_WIDTH;j ++)
		{
			int nNeighbor = 0;
			
			#pragma region Compare
			// ¡ü
			if (i > 0)
			{
				if (m_map[i - 1][j] == 1)
				{
					nNeighbor ++;
				}
			}
			// ¡ý
			if (i < MAP_WIDTH - 1)
			{
				if (m_map[i + 1][j] == 1)
				{
					nNeighbor ++;
				}
			}
			// ¡û
			if (j > 0)
			{
				if (m_map[i][j - 1] == 1)
				{
					nNeighbor ++;
				}
			}
			// ¡ú
			if (j < MAP_WIDTH - 1)
			{
				if (m_map[i][j + 1] == 1)
				{
					nNeighbor ++;
				}
			}
			// ¨I
			if (i > 0 && j > 0)
			{
				if (m_map[i - 1][j - 1] == 1)
				{
					nNeighbor ++;
				}
			}
			// ¨J
			if (i > 0 && j < MAP_WIDTH - 1)
			{
				if (m_map[i - 1][j + 1] == 1)
				{
					nNeighbor ++;
				}
			}
			// ¨L
			if (i < MAP_WIDTH - 1 && j > 0)
			{
				if (m_map[i + 1][j - 1] == 1)
				{
					nNeighbor ++;
				}
			}
			// ¨K
			if (i < MAP_WIDTH - 1 && j < MAP_WIDTH - 1)
			{
				if (m_map[i + 1][j + 1] == 1)
				{
					nNeighbor ++;
				}
			}
			#pragma endregion Compare

			if (nNeighbor == 3)
			{
				m_nextmap[i][j] = 1;
			}
			else if (nNeighbor == 2)
			{
				m_nextmap[i][j] = m_map[i][j];
			}
			else
			{
				m_nextmap[i][j] = 0;
			}

			if (m_nextmap[i][j] == 1)
			{
				alive ++;
			}
		}
	}

	for (int i = 0;i < MAP_WIDTH;i ++)
	{
		for (int j = 0;j < MAP_WIDTH;j ++)
		{
			m_map[i][j] = m_nextmap[i][j];
		}
	}

	QString strTitle;
	strTitle.sprintf("Hades:%d:%d:%d",m_timer.interval(),envolution,alive);
	this->setWindowTitle(strTitle);

	envolution ++;

	this->repaint();
}

void Hades::_init()
{
	_clear();


	envolution = 0;
	int nInitCount = qrand() % (MAP_WIDTH * MAP_WIDTH);
	for (int i = 0;i < nInitCount;i ++)
	{
		int x = qrand() % MAP_WIDTH;
		int y = qrand() % MAP_WIDTH;
		m_map[x][y] = 1;
	}

	this->repaint();
}

void Hades::keyPressEvent( QKeyEvent *pEvent )
{
	if (pEvent->key() == Qt::Key_R)
	{
		_init();
	}
	else if (pEvent->key() == Qt::Key_Space)
	{
		m_timer.isActive() ? m_timer.stop() : m_timer.start();
	}
	else if (pEvent->key() == Qt::Key_C)
	{
		_clear();
		this->repaint();
	}
	else if (pEvent->key() == Qt::Key_U)
	{
		int nInterval = m_timer.interval();
		if (nInterval > 100)
		{
			nInterval -= 100;
		}

		m_timer.setInterval(nInterval);
	}
	else if (pEvent->key() == Qt::Key_I)
	{
		int nInterval = m_timer.interval();
		
		nInterval += 100;

		m_timer.setInterval(nInterval);
	}
	else if (pEvent->key() == Qt::Key_O)
	{
		m_timer.setInterval(TIME_INTERVAL);
	}
	else if (pEvent->key() == Qt::Key_G)
	{
		m_bShowGrid = !m_bShowGrid;
		this->repaint();
	}
}

void Hades::mousePressEvent( QMouseEvent *pEvent )
{
	if (pEvent->button() == Qt::LeftButton)
	{
		m_map[pEvent->x() / 10][pEvent->y() / 10] = 1;
	}
	else if(pEvent->button() == Qt::RightButton)
	{
		m_map[pEvent->x() / 10][pEvent->y() / 10] = 0;
	}
	repaint();
}

void Hades::_clear()
{
	for(int i = 0;i < MAP_WIDTH;i ++)
	{
		for (int j = 0;j < MAP_WIDTH;j ++)
		{
			m_map[i][j] = 0;
		}
	}
}