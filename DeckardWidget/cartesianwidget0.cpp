#include "cartesianwidget0.h"
#include <QtGui/QFont>
#include <QtGui/QFontMetrics>
#include <QtGui/QFontMetricsF>
#include <QtCore/QDebug>

/**
 * @brief CartesianWidget::CartesianWidget
 * @param parent
 */
CartesianWidget0::CartesianWidget0(QWidget *parent) : CartesianWidget(parent)
{
    setScale(100, 100);
    setOffset(0, 0);
}

/**
 * @brief CartesianWidget::~CartesianWidget
 */
CartesianWidget0::~CartesianWidget0()
{
}

/**
 * @brief CartesianWidget::resizeEvent
 * @param e
 */
void CartesianWidget0::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}

/**
 * @brief CartesianWidget::paintEvent
 * @param e
 */
void CartesianWidget0::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    int w = width();
    int h = height();

    QFont font1;
    font1.setFamily("Consolas");
    font1.setPointSize(10);
    setFont(font1);
    QFontMetrics fm = QFontMetrics(font());

    QPainter painter(this);

    painter.translate(w/2 + offsetX(), h/2 + offsetY());

    if (scaleX() >= 50 && scaleY() >= 50)
    {
        QPen pen1;
        pen1.setColor(0xE0E0D1);
        pen1.setStyle(Qt::DashLine);
        painter.setPen(pen1);
        for (int i=-w/2-offsetX(); i<w/2-offsetX(); i++) if ((i % (scaleX()/5)) == 0) painter.drawLine(i, -h/2-offsetY(), i, h/2-offsetY());
        for (int i=-h/2-offsetY(); i<h/2-offsetY(); i++) if ((i % (scaleY()/5)) == 0) painter.drawLine(-w/2-offsetX(), i, w/2-offsetX(), i);
    }

    QPen pen2;
    pen2.setColor(0xCACABC);
    if (scaleX() < 50 || scaleY() < 50) pen2.setStyle(Qt::DashLine);
    painter.setPen(pen2);
    for (int i=-w/2-offsetX(); i<w/2-offsetX(); i++) if ((i % scaleX()) == 0) painter.drawLine(i, -h/2-offsetY(), i, h/2-offsetY());
    for (int i=-h/2-offsetY(); i<h/2-offsetY(); i++) if ((i % scaleY()) == 0) painter.drawLine(-w/2-offsetX(), i, w/2-offsetX(), i);

    painter.setPen(Qt::black);
    painter.drawLine(-w/2-offsetX(), 0, w/2-offsetX(), 0);
    painter.drawLine(0, -h/2-offsetY(), 0, h/2-offsetY());

    // draw absis scale numbers
    for (int i=-w/2-offsetX(); i<w/2-offsetX(); i++)
    {
        if ((i % scaleX()) == 0 && i != 0)
        {
            QString s = QString::number(i/scaleX());
            painter.drawText(i-fm.width(s)/2, fm.height(), s);
        }
    }

    // draw ordinate scale numbers
    for (int i=-h/2-offsetY(); i<h/2-offsetY(); i++)
    {
        if ((i % scaleY()) == 0 && i != 0)
        {
            QString s = QString::number(-i/scaleY());
            painter.drawText(-fm.width(s)-4, i+fm.height()/2-3, s);
        }
    }

    // draw zero number
    painter.drawText(-fm.width("0")-4, fm.height(), "0");

    drawFunction(0, painter);

    QPen pen3;
    pen3.setColor(Qt::blue);
    painter.setPen(pen3);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.end();
}

/**
 * @brief CartesianWidget::wheelEvent
 * @param e
 */
void CartesianWidget0::wheelEvent(QWheelEvent* e)
{
    e->delta() > 0 ? setScale(scaleX()+10, scaleY()+10) : setScale(scaleX()-10, scaleY()-10);
}

/**
 * @brief CartesianWidget::mousePressEvent
 * @param e
 */
void CartesianWidget0::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton)
    {
        leftButtonPressed = true;
        last = e->pos();
    }
}

/**
 * @brief CartesianWidget::mouseReleaseEvent
 * @param e
 */
void CartesianWidget0::mouseReleaseEvent(QMouseEvent* e)
{
    Q_UNUSED(e)

    leftButtonPressed = false;
}

/**
 * @brief CartesianWidget::mouseMoveEvent
 * @param e
 */
void CartesianWidget0::mouseMoveEvent(QMouseEvent* e)
{
    if (leftButtonPressed) setOffset(offsetX() + (e->pos().x() - last.x()) , offsetY() + (e->pos().y() - last.y()));
    last = e->pos();
    update();
}

/**
 * @brief CartesianWidget::setScale
 * @param scaleX
 * @param scaleY
 */
void CartesianWidget0::setScale(int scaleX, int scaleY)
{
    if (scaleX < 20) return;
    if (scaleY < 20) return;
    CartesianWidget::setScale(scaleX, scaleY);
}

/**
 * @brief CartesianWidget::drawFunction
 * @param f
 * @param painter
 */
void CartesianWidget0::drawFunction(R1Function f, QPainter& painter)
{
    Q_UNUSED(f)

    QPen pen = painter.pen();

    for (int i=0; i<fcs.size(); i++)
    {
        FunctionConfig fc = fcs.at(i);
        painter.setPen(QPen(fc.penColor));

        int min = fc.a * scaleX();
        int max = fc.b * scaleX();

        for (int i=min; i<max; i++)
        {
            double x1 = (double)(i+0)/scaleX();
            double x2 = (double)(i+1)/scaleX();
            double y1 = -fc.f(x1);
            double y2 = -fc.f(x2);

            painter.drawLine(i, y1*scaleY(), i+1, y2*scaleY());
            painter.setPen(pen);
        }
    }

    painter.setPen(pen);
}

