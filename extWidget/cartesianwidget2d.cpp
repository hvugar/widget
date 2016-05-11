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

    QFont font1;
    font1.setFamily("Consolas");
    font1.setPointSize(8);
    setFont(font1);

    QPainter painter(this);

    drawGridLines(painter);
    drawGridLabel(painter);
    drawR1Graphic(painter);
    drawLines(painter);
    drawPoints(painter);

    painter.setPen(Qt::red);
    painter.drawLine(width()/2.0-2.0, height()/2.0,     width()/2.0+2.0, height()/2.0);
    painter.drawLine(width()/2.0,     height()/2.0-2.0, width()/2.0,     height()/2.0+2.0);

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
    double w = (double)width();
    double h = (double)height();
    //    double dx = w/2.0;
    //    double dy = h/2.0;
    //    double cx = - centerX() * ((double)scaleX() / zoom());
    //    double cy = + centerY() * ((double)scaleY() / zoom());

    double xmz = xmin() / zoom();
    double fx = xmz - trunc(xmz);
    double x = fx * scaleX();

    double ymz = ymin() / zoom();
    double fy = ymz - trunc(ymz);
    double y = fy * scaleY();

    double numberX, numberY;

    numberX = (ceil(xmin()/zoom()))*zoom();
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

    numberY = (ceil(ymin()/zoom()))*zoom();
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

    numberX = (ceil(xmin()/zoom()))*zoom();
    for (int i=x; i<w+x; i++)
    {
        int x1 = i-x;
        if (i % scaleX() == 0)
        {
            if (-zoom()/2.0 < numberX && numberX < zoom()/2.0)
            {
                painter.setPen(Qt::black);
                painter.drawLine(x1, 0, x1, h);
            }
            numberX+=zoom();
        }
    }

    numberY = (ceil(ymin()/zoom()))*zoom();
    for (int i=y; i<h+y; i++)
    {
        if (i % scaleY() == 0)
        {
            if (-zoom()/2.0 < numberY && numberY < zoom()/2.0)
            {
                painter.setPen(Qt::black);
                painter.drawLine(0, h-(i-y), w, h-(i-y));
            }
            numberY+=zoom();
        }
    }

    painter.restore();
}

void Cartesian2DWidget::drawGridLabel(QPainter& painter)
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
    double x = fx * scaleX();

    for (int i=x; i<width()+x; i++)
    {
        if (i % scaleX() == 0)
        {
            QString s = axisNumber(numberX, zoomLevel());
            double x1 = i-x-fm.width(s)/2;
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
    double y = fy * scaleY();
    for (int i=y; i<height()+y; i++)
    {
        if (i % scaleY() == 0)
        {
            QString s = axisNumber(numberY, zoomLevel());
            double y1 = height()-(i-y)+fm.height()/3-1;
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

    QString s = "0";
    double y1 = cy+dy+fm.height();
    double x1 = cx+dx-fm.width(s)-5;
    if (cx > w/2.0)
    {
        painter.setPen(QPen(QColor(0x6B6B47)));
        painter.drawText(width()-fm.width(s)-5, y1, s);
    }
    else if (cx < -w/2.0)
    {
        painter.setPen(QPen(QColor(0x6B6B47)));
        painter.drawText(5, y1, s);
    }
    else if (cy > h/2.0)
    {
        painter.setPen(QPen(QColor(0x6B6B47)));
        painter.drawText(x1, h-fm.height()/2-3, s);
    }
    else if (cy < -h/2.0)
    {
        painter.setPen(QPen(QColor(0x6B6B47)));
        painter.drawText(x1, fm.height()-1, s);
    }
    else
    {
        painter.setPen(Qt::black);
        painter.drawText(x1, y1, s);
    }

    painter.restore();
}

void Cartesian2DWidget::drawR1Graphic(QPainter& painter)
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

        double a = (min - xmin())/(xmax()-xmin()) * width();
        double b = (max - xmin())/(xmax()-xmin()) * width();

        QPainterPath path;
        for (double i=a; i<=b; i++)
        {
            double x = i*(xmax()-xmin())/width() + xmin();
            double y = fc.f->fx(x);
            double j = height()-(y - ymin())/(ymax()-ymin()) * height();
            painter.drawPoint(i,j);

            if(!isnan(j) && !isinf(j))
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

void Cartesian2DWidget::drawLines(QPainter& painter)
{
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::blue);
    for (int i=0; i<mlines.size(); i++)
    {
        const QLineF &line = mlines.at(i);
        QPointF p1 = toDisplayPoint(line.p1().x(), line.p1().y());
        QPointF p2 = toDisplayPoint(line.p2().x(), line.p2().y());
        painter.drawLine(QLineF(p1, p2));
    }

    painter.restore();
}

void Cartesian2DWidget::drawPoints(QPainter& painter)
{
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(Qt::red);
    painter.setPen(Qt::blue);
    for (int i=0; i<mpoints.size(); i++)
    {
        const QPointF &point = mpoints.at(i);
        QPointF p = toDisplayPoint(point.x(), point.y());
        painter.drawEllipse(p.x()-1, p.y()-1, 3, 3);
    }

    painter.restore();
}

QPointF Cartesian2DWidget::toDisplayPoint(double x, double y)
{
    QPointF point;
    double dx = (x - xmin())/(xmax()-xmin()) * width();
    double dy = height()-(y - ymin())/(ymax()-ymin()) * height();
    point.setX(dx);
    point.setY(dy);
    return point;
}

QPointF Cartesian2DWidget::fromDisplayPoint(double x, double y)
{
    QPointF point;
    double dx  = +(x / scaleX()) * zoom();
    double dy  = -(y / scaleY()) * zoom();
    point.setX(dx);
    point.setY(dy);
    return point;
}
