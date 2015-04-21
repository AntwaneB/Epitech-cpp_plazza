/*
 * File:   QSFMLCanvas.hpp
 * Author: buchse_a
 *
 * Created on April 21, 2015, 10:33 AM
 */

#ifndef QSFMLCANVAS_HPP
#define	QSFMLCANVAS_HPP

#include <SFML/Graphics.hpp>
#include <QWidget>
#include <QTimer>

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
public:
	QSFMLCanvas(QWidget* parent, const QPoint& position, const QSize& size, size_t frameTime = 0);
	virtual ~QSFMLCanvas();

private:
	virtual void onInit() = 0;
	virtual void onUpdate() = 0;
	virtual QPaintEngine* paintEngine() const;
	virtual void showEvent(QShowEvent*);
	virtual void paintEvent(QPaintEvent*);

protected:
	QTimer	_timer;

private:
	bool		_initialized;
};

#endif	/* QSFMLCANVAS_HPP */
