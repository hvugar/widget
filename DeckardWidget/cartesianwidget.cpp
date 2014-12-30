#include "cartesianwidget.h"
#include <QtGui/QFont>
#include <QtGui/QFontMetrics>
#include <QtGui/QFontMetricsF>
#include <QtCore/QDebug>

CartesianWidget::CartesianWidget(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);
    setBackgroundRole(QPalette::Base);

    setScale(100);
    offsetX = 0;
    offsetY = 0;
    pressed = false;
}

void CartesianWidget::resizeEvent(QResizeEvent *e)
{}

double f(double x)
{
    return x*x-x*x*x*x+0.5;
}

void CartesianWidget::paintEvent(QPaintEvent *e)
{
    int w = width();
    int h = height();

    QFont font1;
    font1.setFamily("Consolas");
    font1.setPointSize(10);
    setFont(font1);
    QFontMetrics fm = QFontMetrics(font());

    QPainter painter(this);

    painter.translate(w/2 + offsetX, h/2 + offsetY);

    if (scale() >= 50)
    {
        QPen pen1;
        pen1.setColor(0xE0E0D1);
        pen1.setStyle(Qt::DashLine);
        painter.setPen(pen1);
        for (int i=-w/2-offsetX; i<w/2-offsetX; i++) if ((i % (scale()/5)) == 0) painter.drawLine(i, -h/2-offsetY, i, h/2-offsetY);
        for (int i=-h/2-offsetY; i<h/2-offsetY; i++) if ((i % (scale()/5)) == 0) painter.drawLine(-w/2-offsetX, i, w/2-offsetX, i);
    }

    QPen pen2;
    pen2.setColor(0xCACABC);
    if (scale() < 50) pen2.setStyle(Qt::DashLine);
    painter.setPen(pen2);
    for (int i=-w/2-offsetX; i<w/2-offsetX; i++) if ((i % scale()) == 0) painter.drawLine(i, -h/2-offsetY, i, h/2-offsetY);
    for (int i=-h/2-offsetY; i<h/2-offsetY; i++) if ((i % scale()) == 0) painter.drawLine(-w/2-offsetX, i, w/2-offsetX, i);

    painter.setPen(Qt::black);
    painter.drawLine(-w/2-offsetX, 0, w/2-offsetX, 0);
    painter.drawLine(0, -h/2-offsetY, 0, h/2-offsetY);

    // draw absis scale numbers
    for (int i=-w/2-offsetX; i<w/2-offsetX; i++)
    {
        if ((i % scale()) == 0 && i != 0)
        {
            QString s = QString::number(i/scale());
            painter.drawText(i-fm.width(s)/2, fm.height(), s);
        }
    }

    // draw ordinate scale numbers
    for (int i=-h/2-offsetY; i<h/2-offsetY; i++)
    {
        if ((i % scale()) == 0 && i != 0)
        {
            QString s = QString::number(-i/scale());
            painter.drawText(-fm.width(s)-4, i+fm.height()/2-3, s);
        }
    }

    // draw zero number
    painter.drawText(-fm.width("0")-4, fm.height(), "0");

    QPen pen3;
    pen3.setColor(Qt::blue);
    painter.setPen(pen3);
    painter.setRenderHint(QPainter::Antialiasing, true);

    drawFunction(f, painter);

    painter.end();
}

void CartesianWidget::wheelEvent(QWheelEvent* e)
{
    e->delta() > 0 ? setScale(scale()+10) : setScale(scale()-10);
    update();
}

void CartesianWidget::mousePressEvent(QMouseEvent* e)
{
    pressed = true;
    last = e->pos();
}

void CartesianWidget::mouseReleaseEvent(QMouseEvent* e)
{
    pressed = false;
}

void CartesianWidget::mouseMoveEvent(QMouseEvent* e)
{
    if (pressed) offsetX += e->pos().x() - last.x();
    if (pressed) offsetY += e->pos().y() - last.y();
    last = e->pos();
    update();
}

void CartesianWidget::drawFunction(R1Function f, QPainter& painter)
{
    int min = -1.2 * scale();
    int max = +1.2 * scale();

    for (int i=min; i<max; i++)
    {
        double x1 = (double)(i+0)/scale();
        double x2 = (double)(i+1)/scale();
        double y1 = -f(x1);
        double y2 = -f(x2);
        painter.drawLine(i, y1*scale(), i+1, y2*scale());
    }
}

void CartesianWidget::setScale(int s)
{
    if (s < 20)
        return;
    m_scale = s;
    update();
}

int CartesianWidget::scale()
{
    return m_scale;
}
