/*
 * File:   QSFMLCanvas.cpp
 * Author: buchse_a
 *
 * Created on April 21, 2015, 10:33 AM
 */

#include "QSFMLCanvas.hpp"

QSFMLCanvas::QSFMLCanvas(QWidget* parent, const QPoint& position, const QSize& size, size_t frameTime)
	: QWidget(parent), _initialized(false)
{
	this->setAttribute(Qt::WA_PaintOnScreen);
	this->setAttribute(Qt::WA_OpaquePaintEvent);
	this->setAttribute(Qt::WA_NoSystemBackground);

	setFocusPolicy(Qt::StrongFocus);

	move(position);
	resize(size);

	_timer.setInterval(frameTime);
}

QSFMLCanvas::~QSFMLCanvas()
{
}

void QSFMLCanvas::showEvent(QShowEvent* e)
{
	(void)e;

	if (!_initialized)
	{
		this->sf::Window::create(winId());

		onInit();

		connect(&_timer, SIGNAL(timeout()), this, SLOT(repaint()));
		_timer.start();

		_initialized = true;
	}
}

QPaintEngine* QSFMLCanvas::paintEngine(void) const
{
	return (NULL);
}

void QSFMLCanvas::paintEvent(QPaintEvent* e)
{
	(void)e;

	this->onUpdate();

	this->display();
}

