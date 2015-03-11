#include "cartesianwidget1.h"
#include <QtGui/QFont>
#include <QtGui/QFontMetrics>
#include <QtGui/QFontMetricsF>
#include <QtCore/QDebug>

#include "math.h"

/**
 * @brief CartesianWidget::CartesianWidget
 * @param parent
 */
CartesianWidget1::CartesianWidget1(QWidget *parent) : CartesianWidget(parent)
{
    setScale(100, 100);
    setOffset(0,0);
    zoom = 1.0;
}

/**
 * @brief CartesianWidget::~CartesianWidget
 */
CartesianWidget1::~CartesianWidget1()
{
}

/**
 * @brief CartesianWidget::resizeEvent
 * @param e
 */
void CartesianWidget1::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}

/**
 * @brief CartesianWidget::paintEvent
 * @param e
 */
void CartesianWidget1::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    int w = width();
    int h = height();

    QFont font1;
    font1.setFamily("Consolas");
    font1.setPointSize(10);
    setFont(font1);

    QPainter painter(this);
    painter.translate(w/2 + offsetX(), h/2 + offsetY());

    drawGridLines(painter);
    drawGridLabel(painter);
    drawR1Graphic(painter);

    painter.end();
}

/**
 * @brief CartesianWidget::wheelEvent
 * @param e
 */
void CartesianWidget1::wheelEvent(QWheelEvent* e)
{
    e->delta() > 0 ? zoom /= 2.0 : zoom *= 2.0;
    update();
}

/**
 * @brief CartesianWidget::mousePressEvent
 * @param e
 */
void CartesianWidget1::mousePressEvent(QMouseEvent* e)
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
void CartesianWidget1::mouseReleaseEvent(QMouseEvent* e)
{
    Q_UNUSED(e)

    leftButtonPressed = false;
}

/**
 * @brief CartesianWidget::mouseMoveEvent
 * @param e
 */
void CartesianWidget1::mouseMoveEvent(QMouseEvent* e)
{
    if (leftButtonPressed) setOffset(offsetX() + (e->pos().x() - last.x()), offsetY() + (e->pos().y() - last.y()));
    last = e->pos();
    update();
}

/**
 * @brief drawGrid
 * @param painter
 */
void CartesianWidget1::drawGridLines(QPainter& painter)
{
    painter.save();

    int w = width();
    int h = height();

    painter.setPen(QPen(QColor(0xE0E0D1),1.0, Qt::DashLine));
    for (int i=-w/2-offsetX(); i<w/2-offsetX(); i++) if ((i % 20) == 0) painter.drawLine(i, -h/2-offsetY(), i, h/2-offsetY());
    for (int i=-h/2-offsetY(); i<h/2-offsetY(); i++) if ((i % 20) == 0) painter.drawLine(-w/2-offsetX(), i, w/2-offsetX(), i);

    painter.setPen(QPen(QColor(0xCACABC)));
    for (int i=-w/2-offsetX(); i<w/2-offsetX(); i++) if ((i % 100) == 0) painter.drawLine(i, -h/2-offsetY(), i, h/2-offsetY());
    for (int i=-h/2-offsetY(); i<h/2-offsetY(); i++) if ((i % 100) == 0) painter.drawLine(-w/2-offsetX(), i, w/2-offsetX(), i);

    //Drawin main axis (absis and ordinate arrow)
    painter.setPen(QPen(Qt::black));
    painter.drawLine(-w/2-offsetX(), 0, w/2-offsetX(), 0);
    painter.drawLine(0, -h/2-offsetY(), 0, h/2-offsetY());

    painter.restore();
}

void CartesianWidget1::drawGridLabel(QPainter& painter)
{
    painter.save();

    QFontMetrics fm = painter.fontMetrics();

    int w = width();
    int h = height();

    // draw absis scale numbers
    for (int i=-w/2-offsetX(); i<w/2-offsetX(); i++)
    {
        if (i % 100 == 0 && i != 0)
        {
            double number = (double)(i) * zoom / scaleX();
            int precition = 0;
            if (zoom < 1) precition = log2((2/zoom)/2);
            QString s = QString::number(number, 'f', precition);
            while(s.endsWith('0') || s.endsWith('.')) s.chop(1);
            painter.drawText(i-fm.width(s)/2, fm.height(), s);
        }
    }

    // draw ordinate scale numbers
    for (int i=-h/2-offsetY(); i<h/2-offsetY(); i++)
    {
        if (i % 100 == 0 && i != 0)
        {
            double number = (double)(i) * zoom / scaleX();
            int precition = 0;
            if (zoom < 1) precition = log2((2/zoom)/2);
            QString s = QString::number(-number, 'f', precition);
            while(s.endsWith('0') || s.endsWith('.')) s.chop(1);
            painter.drawText(-fm.width(s)-4, i+fm.height()/2-3, s);
        }
    }

    // draw zero number
    painter.drawText(-fm.width("0")-4, fm.height(), "0");

    painter.restore();
}

void CartesianWidget1::drawR1Graphic(QPainter& painter)
{
    painter.save();

    painter.setPen(QPen(Qt::blue));
    painter.setRenderHint(QPainter::Antialiasing, true);

    for (int i=0; i<fcs.size(); i++)
    {
        FunctionConfig fc = fcs.at(i);
        painter.setPen(fc.penColor);

        int min = (fc.a / zoom) * scaleX();
        int max = (fc.b / zoom) * scaleX();

        for (int i=min; i<max; i++)
        {
            double x1 = ((double)(i+0)/scaleX()) * zoom;
            double x2 = ((double)(i+1)/scaleX()) * zoom;

            double y1 = -fc.f(x1);
            double y2 = -fc.f(x2);

            painter.drawLine(i, y1*scaleY()/zoom, i+1, y2*scaleY()/zoom);
        }
    }

    painter.restore();
}
