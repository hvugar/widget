#include "cartesianwidget2d_2.h"
#include <QtGui/QFont>
#include <QtGui/QFontMetrics>
#include <QtGui/QFontMetricsF>
#include <QtCore/QDebug>
#include <math.h>

Cartesian2DWidget2::Cartesian2DWidget2(QWidget *parent) : CartesianWidget(parent)
{
    setScale(100, 100);
    setCenter(0.0, 0.0);
    setOffset(0, 0);
}

Cartesian2DWidget2::~Cartesian2DWidget2()
{
}

void Cartesian2DWidget2::resizeEvent(QResizeEvent *e)
{
    CartesianWidget::resizeEvent(e);
}

void Cartesian2DWidget2::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QFont font1;
    font1.setFamily("Consolas");
    font1.setPointSize(8);
    setFont(font1);

    QPainter painter(this);

    drawGridLines(painter);
    drawGridLabel(painter);
    drawR1Graphic(painter);

    painter.setPen(Qt::red);
    painter.drawLine(width()/2.0-2.0, height()/2.0,     width()/2.0+2.0, height()/2.0);
    painter.drawLine(width()/2.0,     height()/2.0-2.0, width()/2.0,     height()/2.0+2.0);

    painter.end();
}

void Cartesian2DWidget2::wheelEvent(QWheelEvent* e)
{
    if (e->delta() > 0) zoomIn(); else zoomOut();
    update();
}

void Cartesian2DWidget2::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton)
    {
        leftButtonPressed = true;
        last = e->pos();
        setCursor(QCursor(Qt::ClosedHandCursor));
    }
}

void Cartesian2DWidget2::mouseReleaseEvent(QMouseEvent* e)
{
    Q_UNUSED(e)
    setCursor(QCursor(Qt::ArrowCursor));
    leftButtonPressed = false;
}

void Cartesian2DWidget2::mouseMoveEvent(QMouseEvent* e)
{
    if (leftButtonPressed) setCenterX(centerX() - ((double)(e->pos().x() - last.x())/(double)scaleX()*zoom()));
    if (leftButtonPressed) setCenterY(centerY() + ((double)(e->pos().y() - last.y())/(double)scaleY()*zoom()));

    last = e->pos();
    update();
}

void Cartesian2DWidget2::drawGridLines(QPainter& painter)
{
    painter.save();
    double w = (double)width();
    double h = (double)height();
    //    double dx = w/2.0;
    //    double dy = h/2.0;
    //    double cx = - centerX() * ((double)scaleX() / zoom());
    //    double cy = + centerY() * ((double)scaleY() / zoom());

    double xmz = xmin() / zoom();
    double fx = xmz - trunc(xmz);
    double numberX = (ceil(xmin()/zoom()))*zoom();
    int x = fx * scaleX();
    for (int i=x; i<w+x; i++)
    {
        int x1 = i-x;
        if (i%(scaleX()/5) == 0)
        {
            painter.setPen(QPen(QColor(0xE0E0D1),1.0, Qt::DashLine));
            painter.drawLine(x1, 0, x1, height());
        }

        if (i % scaleX() == 0)
        {
            if (-zoom()/2.0 < numberX && numberX < zoom()/2.0)
            {
                painter.setPen(Qt::black);
            }
            else
            {
                painter.setPen(QPen(QColor(0xCACABC)));
            }
            painter.drawLine(x1, 0, x1, h);
            numberX+=zoom();
        }
    }

    double ymz = ymin() / zoom();
    double fy = ymz - trunc(ymz);
    double numberY = (ceil(ymin()/zoom()))*zoom();
    int y = fy * scaleY();
    for (int i=y; i<h+y; i++)
    {
        if (i%(scaleY()/5) == 0)
        {
            painter.setPen(QPen(QColor(0xE0E0D1),1.0, Qt::DashLine));
            painter.drawLine(0, h-(i-y), w, h-(i-y));
        }

        if (i % scaleY() == 0)
        {
            if (-zoom()/2.0 < numberY && numberY < zoom()/2.0)
            {
                painter.setPen(Qt::black);
            }
            else
            {
                painter.setPen(QPen(QColor(0xCACABC)));
            }
            painter.drawLine(0, h-(i-y), w, h-(i-y));
            numberY+=zoom();
        }
    }
    painter.restore();
}

void Cartesian2DWidget2::drawGridLabel(QPainter& painter)
{
    painter.save();
    QFontMetrics fm = painter.fontMetrics();
    double w = (double)width();
    double h = (double)height();
    double dx = w/2.0;
    double dy = h/2.0;
    double cx = - centerX() * ((double)scaleX() / zoom());
    double cy = + centerY() * ((double)scaleY() / zoom());

    double xmz = xmin() / zoom();
    double fx = xmz - trunc(xmz);
    double numberX = (ceil(xmin()/zoom()))*zoom();
    int x = fx * scaleX();
    for (int i=x; i<width()+x; i++)
    {
        if (i % scaleX() == 0)
        {
            QString s = axisNumber(numberX, zoomLevel());
            int x1 = i-x-fm.width(s)/2;
            if (-zoom()/2.0 >= numberX || numberX >= zoom()/2.0)
            {
                if (cy < -h/2.0)
                {
                    painter.setPen(QPen(QColor(0x6B6B47)));
                    painter.drawText(x1, fm.height()-1, s);
                }
                else if (cy > h/2.0)
                {
                    painter.setPen(QPen(QColor(0x6B6B47)));
                    painter.drawText(x1, h-fm.height()/2-3, s);
                }
                else
                {
                    painter.setPen(Qt::black);
                    painter.drawText(x1, cy+dy+fm.height(), s);
                }
            }
            numberX+=zoom();
        }
    }

    double ymz = ymin() / zoom();
    double fy = ymz - trunc(ymz);
    double numberY = (ceil(ymin()/zoom()))*zoom();
    int y = fy * scaleY();
    for (int i=y; i<height()+y; i++)
    {
        if (i % scaleY() == 0)
        {
            QString s = axisNumber(numberY, zoomLevel());
            int y1 = height()-(i-y)+fm.height()/3-1;
            if (-zoom()/2.0 >= numberY || numberY >= zoom()/2.0)
            {
                if (cx < -w/2.0)
                {
                    painter.setPen(QPen(QColor(0x6B6B47)));
                    painter.drawText(5, y1, s);
                }
                else if (cx > w/2.0)
                {
                    painter.setPen(QPen(QColor(0x6B6B47)));
                    painter.drawText(width()-fm.width(s)-5, y1, s);
                }
                else
                {
                    painter.setPen(Qt::black);
                    painter.drawText(cx+dx-fm.width(s)-3, y1, s);
                }
            }
            numberY+=zoom();
        }
    }
    painter.restore();
}

void Cartesian2DWidget2::drawR1Graphic(QPainter& painter)
{
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing, true);
    for (int i=0; i<fcs.size(); i++)
    {
        FunctionConfig fc = fcs.at(i);
        painter.setPen(QColor(fc.penColor));

        double min = fc.a;
        double max = fc.b;
        if (min < xmin()) min = xmin();
        if (max > xmax()) max = xmax();

        int a = (min - xmin())/(xmax()-xmin()) * width();
        int b = (max - xmin())/(xmax()-xmin()) * width();

        QPainterPath path;
        for (int i=a; i<=b; i++)
        {
            double x = i*(xmax()-xmin())/width() + xmin();
            double y = fc.f(x);
            int j = height()-(y - ymin())/(ymax()-ymin()) * height();
            painter.drawPoint(i,j);

            if(!isnan(y))
            {
                if (path.elementCount()==0) {
                    path.moveTo(i, j);
                } else {
                    path.lineTo(i, j);
                }
            }
        }
        painter.drawPath(path);
    }
    painter.restore();
}

QPoint Cartesian2DWidget2::toDisplayPoint(double x, double y)
{
    QPoint point;
    int dx = +x * ((double)scaleX() / zoom());
    int dy = -y * ((double)scaleY() / zoom());
    point.setX(dx);
    point.setY(dy);
    return point;
}

QPointF Cartesian2DWidget2::fromDisplayPoint(int x, int y)
{
    QPointF point;
    double dx  = +(x / scaleX()) * zoom();
    double dy  = -(y / scaleY()) * zoom();
    point.setX(dx);
    point.setY(dy);
    return point;
}

void Cartesian2DWidget2::setXRange(double a, double b)
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
