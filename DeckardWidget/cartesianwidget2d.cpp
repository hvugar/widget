#include "cartesianwidget2d.h"
#include <QtGui/QFont>
#include <QtGui/QFontMetrics>
#include <QtGui/QFontMetricsF>
#include <QtCore/QDebug>
#include <math.h>

Cartesian2DWidget::Cartesian2DWidget(QWidget *parent) : CartesianWidget(parent)
{
    setScale(100, 100);
    setCenter(0.0, 0.0);
    setOffset(0, 0);
}

Cartesian2DWidget::~Cartesian2DWidget()
{
}

void Cartesian2DWidget::resizeEvent(QResizeEvent *e)
{
    CartesianWidget::resizeEvent(e);
}

void Cartesian2DWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    double w = (double)width();
    double h = (double)height();

    QFont font1;
    font1.setFamily("Consolas");
    font1.setPointSize(8);
    setFont(font1);

    QPainter painter(this);
    painter.save();

    double dx = w/2.0;
    double dy = h/2.0;

    double cx = - centerX() * ((double)scaleX() / zoom());
    double cy = + centerY() * ((double)scaleY() / zoom());

    painter.translate(dx, dy);
    painter.translate(cx, cy);

    drawGridLines(painter);
    drawGridLabel(painter);
    drawR1Graphic(painter);

    painter.setPen(Qt::blue);
    painter.setRenderHint(QPainter::Antialiasing, true);
    for (int i=0; i<lines.size(); i++)
    {
        QLineF line1 = lines.at(i);
        QLineF line2;
        line2.setP1(toDisplayPoint(line1.p1().x(), line1.p1().y()));
        line2.setP2(toDisplayPoint(line1.p2().x(), line1.p2().y()));
        painter.drawLine(line2);
    }

    painter.setPen(Qt::blue);
    painter.setBrush(Qt::red);
    for (int i=0; i<points.size(); i++)
    {
        QPointF point1 = points.at(i);
        QPointF point2(toDisplayPoint(point1.x(), point1.y()));
        painter.drawEllipse(point2, 2, 2);
    }

    painter.restore();

    painter.setPen(Qt::red);
    painter.drawLine(w/2.0-2.0, h/2.0,     w/2.0+2.0, h/2.0);
    painter.drawLine(w/2.0,     h/2.0-2.0, w/2.0,     h/2.0+2.0);

    painter.end();
}

void Cartesian2DWidget::wheelEvent(QWheelEvent* e)
{
    if (e->delta() > 0) zoomIn(); else zoomOut();
    update();
}

void Cartesian2DWidget::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton)
    {
        leftButtonPressed = true;
        last = e->pos();
        setCursor(QCursor(Qt::ClosedHandCursor));
    }
}

void Cartesian2DWidget::mouseReleaseEvent(QMouseEvent* e)
{
    Q_UNUSED(e)
    setCursor(QCursor(Qt::ArrowCursor));
    leftButtonPressed = false;
}

void Cartesian2DWidget::mouseMoveEvent(QMouseEvent* e)
{
    if (leftButtonPressed) setCenterX(centerX() - ((double)(e->pos().x() - last.x())/(double)scaleX()*zoom()));
    if (leftButtonPressed) setCenterY(centerY() + ((double)(e->pos().y() - last.y())/(double)scaleY()*zoom()));

    last = e->pos();
    update();
}

void Cartesian2DWidget::drawGridLines(QPainter& painter)
{
    painter.save();

    int w = width();
    int h = height();

    int dx = centerX() * ((double)scaleX()/zoom());
    int dy = centerY() * ((double)scaleY()/zoom());

    int leftX   = -w/2 + dx;
    int rightX  = +w/2 + dx;
    int topY    = +h/2 - dy;
    int bottomY = -h/2 - dy;

    int a=1;
    if (scaleX() % 5 == 0) {a = 5;} else
        if (scaleX() % 4 == 0) {a = 4;} else
            if (scaleX() % 2 == 0) {a = 2;}

    painter.setPen(QPen(QColor(0xE0E0D1),1.0, Qt::DashLine));
    for (int i=leftX; i<rightX; i++) if ((i % (scaleX()/a)) == 0) painter.drawLine(i, bottomY, i, topY);
    for (int i=bottomY; i<topY; i++) if ((i % (scaleY()/a)) == 0) painter.drawLine(leftX, i, rightX, i);

    painter.setPen(QPen(QColor(0xCACABC)));
    for (int i=leftX; i<rightX; i++) if ((i % scaleX()) == 0) painter.drawLine(i, bottomY, i, topY);
    for (int i=bottomY; i<topY; i++) if ((i % scaleY()) == 0) painter.drawLine(leftX, i, rightX, i);

    painter.setPen(QPen(Qt::black));
    painter.drawLine(leftX, 0, rightX, 0);
    painter.drawLine(0, bottomY, 0, topY);

    painter.restore();
}

void Cartesian2DWidget::drawGridLabel(QPainter& painter)
{
    painter.save();

    QFontMetrics fm = painter.fontMetrics();

    double w = width();
    double h = height();

    double dx = centerX() * ((double)scaleX()/zoom());
    double dy = centerY() * ((double)scaleY()/zoom());

    int leftX   = -w/2.0 + dx;
    int rightX  = +w/2.0 + dx;
    int topY    = +h/2.0 - dy;
    int bottomY = -h/2.0 - dy;

    // draw absis scale numbers
    for (int i=leftX; i<rightX; i++)
    {
        if (i % scaleX() == 0 && i != 0)
        {
            double number = ( i / scaleX() ) * zoom();
            QString s = axisNumber(number, zoomLevel());

            if (topY <= 0)
            {
                painter.setPen(QPen(QColor(0x6B6B47)));
                painter.translate(+i, topY);
//                painter.drawText(i-fm.width(s)/2, topY - fm.height()/3, s);
                painter.drawText(-fm.width(s)/2, -fm.height()/3, s);
//                painter.setPen(QPen(QColor(0xff0000)));
//                painter.drawEllipse(-fm.width(s)/2, -fm.height()/3, 5, 5);
//                painter.drawText(-fm.width(s)/2, -fm.height()/3, s);
                painter.translate(-i, -topY);
            }
            else if (bottomY >= 0)
            {
                painter.setPen(QPen(QColor(0x6B6B47)));
                painter.translate(+i, +bottomY);
//                painter.drawText(i-fm.width(s)/2, bottomY + fm.height(), s);
                painter.drawText(-fm.width(s)/2, fm.height(), s);
                painter.translate(-i, -bottomY);
            }
            else
            {
                painter.setPen(QPen(Qt::black));
                painter.drawText(i-fm.width(s)/2, fm.height(), s);
            }
        }
    }

    // draw ordinate scale numbers
    for (int i=bottomY; i<topY; i++)
    {
        if (i % scaleY() == 0 && i != 0)
        {
            double number = -( i / scaleY() ) * zoom();
            QString s = axisNumber(number, zoomLevel());
            if (leftX >= 0)
            {
                painter.setPen(QPen(QColor(0x6B6B47)));
                painter.drawText(leftX + 6, i+fm.height()/2-3, s);
            }
            else if (rightX <= 0)
            {
                painter.setPen(QPen(QColor(0x6B6B47)));
                painter.drawText(rightX - fm.width(s)-4, i+fm.height()/2-3, s);
            }
            else
            {
                painter.setPen(QPen(Qt::black));
                painter.drawText(-fm.width(s)-4, i+fm.height()/2-3, s);
            }
        }
    }

    // draw zero number
    painter.drawText(-fm.width("0")-4, fm.height(), "0");

    painter.restore();
}

void Cartesian2DWidget::drawR1Graphic(QPainter& painter)
{
    painter.save();

    painter.setRenderHint(QPainter::Antialiasing, true);

    for (int i=0; i<fcs.size(); i++)
    {
        FunctionConfig fc = fcs.at(i);
        painter.setPen(QPen(QColor(fc.penColor), 1.0));

        int min = fc.a * ((double)scaleX() / zoom());
        int max = fc.b * ((double)scaleX() / zoom());

        if (fc.a < xmin()) min = xmin() * ((double)scaleX() / zoom());
        if (fc.b > xmax()) max = xmax() * ((double)scaleX() / zoom());

        QPainterPath path;
        for (int i=min; i<max; i++)
        {
            double x1 = (double)(i)/(double)scaleX()*zoom();
            //double x2 = (double)(i+1)/(double)scaleX()*zoom();

            double y1 = -fc.f(x1);
            //double y2 = -fc.f(x2);

            int y11 = y1*scaleY()/zoom();
            //int y12 = y2*scaleY()/zoom();

            //painter.drawLine(i, y11, i+1, y12);

            if(!isnan(y1))
            {
                if (path.elementCount()==0) {
                    path.moveTo(i, y11);
                } else {
                    path.lineTo(i, y11);
                }
            }
        }
        painter.drawPath(path);
    }

    painter.restore();
}

QPoint Cartesian2DWidget::toDisplayPoint(double x, double y)
{
    QPoint point;
    int dx = x * ((double)scaleX() / zoom());
    int dy = -y * ((double)scaleY() / zoom());
    point.setX(dx);
    point.setY(dy);
    return point;
}

QPointF Cartesian2DWidget::fromDisplayPoint(int x, int y)
{
    QPointF point;
    double dx  = (x / scaleX()) * zoom();
    double dy  = -(y / scaleY()) * zoom();
    point.setX(dx);
    point.setY(dy);
    return point;
}


void Cartesian2DWidget::setXRange(double a, double b)
{
    setCenter((a+b)/2.0, centerY());
    if (xmax()-xmin() > (b-a))
    {
        while ( xmax()-xmin() > (b-a) )
        {
            setZoomLevel(zoomLevel()-1);
        }
    }
    else
    {
        while ( xmax()-xmin() < (b-a) )
        {
            setZoomLevel(zoomLevel()+1);
        }
    }
    update();
}
