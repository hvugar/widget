#include "cartesianwidget2d_1.h"
#include <QtGui/QFont>
#include <QtGui/QFontMetrics>
#include <QtGui/QFontMetricsF>
#include <QtCore/QDebug>
#include <math.h>

Cartesian2DWidget1::Cartesian2DWidget1(QWidget *parent) : CartesianWidget(parent)
{
    setScale(100, 100);
    setCenter(0.0, 0.0);
    setOffset(0, 0);
}

Cartesian2DWidget1::~Cartesian2DWidget1()
{
}

void Cartesian2DWidget1::resizeEvent(QResizeEvent *e)
{
    CartesianWidget::resizeEvent(e);
}

void Cartesian2DWidget1::paintEvent(QPaintEvent *e)
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

    //qDebug() << "void Cartesian2DWidget::paintEvent(QPaintEvent *e) [" << dx << ", " << dy << "]";
    //qDebug() << "void Cartesian2DWidget::paintEvent(QPaintEvent *e) [" << cx << ", " << cy << "]";

    painter.translate(dx, dy);
    painter.translate(cx, cy);

    QFontMetrics fm = painter.fontMetrics();

    //setCenter(0.024, 0.0);
    //setZoom(0.01);
    int x1 = xmin() * (double(scaleX())/zoom());
    int x2 = xmax() * (double(scaleX())/zoom());
    int y1 = ymin() * (double(scaleY())/zoom());
    int y2 = ymax() * (double(scaleY())/zoom());

    qDebug() << x1 << x2 << y1 << y2;

    for (int i=x1; i<=x2; i++)
    {

        if ( i % ( scaleX()/5 ) == 0)
        {
            painter.setPen(QPen(QColor(0xE0E0D1),1.0, Qt::DashLine));
            painter.drawLine(i, -y1, i, -y2);
            painter.drawLine(-i, -y1, -i, -y2);
        }
        painter.setPen(QPen(QColor(0xCACABC)));
        if ( i % scaleX() == 0)
        {
            painter.drawLine(i, -y1, i, -y2);
            painter.drawLine(-i, -y1, -i, -y2);

            if (i != 0)
            {
                painter.setPen(QPen(Qt::black));
                double number = ( i / scaleX() ) * zoom();
                QString s1 = axisNumber(number, zoomLevel());
                QString s2 = axisNumber(-number, zoomLevel());
                painter.drawText(i-fm.width(s1)/2, fm.height(), s1);
                painter.drawText(-i-fm.width(s2)/2, fm.height(), s2);
            }
        }
    }

    for (int i=y1; i<y2; i++)
    {
        painter.setPen(QPen(QColor(0xE0E0D1),1.0, Qt::DashLine));
        if ( i % (scaleY() / 5 ) == 0)
        {
            painter.drawLine(x1, i, x2, i);
            painter.drawLine(x1, -i, x2, -i);
        }
        painter.setPen(QPen(QColor(0xCACABC)));
        if ( i % scaleY() == 0)
        {
            painter.drawLine(x1, i, x2, i);
            painter.drawLine(x1, -i, x2, -i);

            if ( i != 0 ) {
                painter.setPen(QPen(Qt::black));
                double number = ( i / scaleY() ) * zoom();
                QString s1 = axisNumber(-number, zoomLevel());
                QString s2 = axisNumber(number, zoomLevel());
                painter.drawText(-fm.width(s1)-4, i+fm.height()/2-3, s1);
                painter.drawText(-fm.width(s2)-4, -i+fm.height()/2-3, s2);
            }
        }
    }

        painter.setPen(Qt::black);
        painter.drawLine(x1, 0, x2, 0);
        painter.drawLine(0, -y1, 0, -y2);


//    if ((dx + cx) >= 0 && (dx + cx) <= w && (dy+cy) >=0 && (dy+cy) <= h) {
//        for (int i=0; i<width(); i++) {
//            painter.setPen(QPen(QColor(0xE0E0D1),1.0, Qt::DashLine));
//            if ( i % ( scaleX()/5 ) == 0) {
//                painter.drawLine(i, height(), i, -height());
//                painter.drawLine(-i, height(), -i, -height());
//            }
//            painter.setPen(QPen(QColor(0xCACABC)));
//            if ( i % scaleX() == 0) {
//                painter.drawLine(i, height(), i, -height());
//                painter.drawLine(-i, height(), -i, -height());
//            }
//            if ( i % scaleX() == 0 && i != 0 ) {
//                painter.setPen(QPen(Qt::black));
//                double number = ( i / scaleX() ) * zoom();
//                QString s1 = axisNumber(number, zoomLevel());
//                QString s2 = axisNumber(-number, zoomLevel());
//                painter.drawText(i-fm.width(s1)/2, fm.height(), s1);
//                painter.drawText(-i-fm.width(s2)/2, fm.height(), s2);
//            }
//        }
//        for (int i=0; i<height(); i++) {
//            painter.setPen(QPen(QColor(0xE0E0D1),1.0, Qt::DashLine));
//            if ( i % (scaleY() / 5 ) == 0) {
//                painter.drawLine(-width(), i, width(), i);
//                painter.drawLine(-width(), -i, width(), -i);
//            }
//            painter.setPen(QPen(QColor(0xCACABC)));
//            if ( i % scaleY() == 0) {
//                painter.drawLine(-width(), i, width(), i);
//                painter.drawLine(-width(), -i, width(), -i);
//            }
//            if ( i % scaleY() == 0 && i != 0 ) {
//                painter.setPen(QPen(Qt::black));
//                double number = ( i / scaleY() ) * zoom();
//                QString s1 = axisNumber(-number, zoomLevel());
//                QString s2 = axisNumber(number, zoomLevel());
//                painter.drawText(-fm.width(s1)-4, i+fm.height()/2-3, s1);
//                painter.drawText(-fm.width(s2)-4, -i+fm.height()/2-3, s2);
//            }
//        }
//        qDebug() << "out" << xmin() << ymin() << xmax() << ymax() << zoom() << floor(xmin()) << ceil(xmin()) << floor(xmax()) << ceil(xmax()) ;
//    } else {
//        qDebug() << "out" << xmin() << ymin() << xmax() << ymax() << zoom() << floor(xmin()) << ceil(xmin()) << floor(xmax()) << ceil(xmax()) ;
//    }

//    painter.setPen(Qt::black);
//    painter.drawLine(0, 0, width()*1.5, 0);
//    painter.drawLine(0, 0, -width()*1.5, 0);
//    painter.drawLine(0, 0, 0, height()*1.5);
//    painter.drawLine(0, 0, 0, -height()*1.5);


//    drawGridLines(painter);
//    drawGridLabel(painter);
//    drawR1Graphic(painter);

//    painter.setBrush(Qt::red);
//    painter.setPen(Qt::blue);
//    painter.drawEllipse(+100,-100,5,5);

    painter.restore();

    painter.setPen(Qt::red);
    painter.drawLine(w/2.0-2.0, h/2.0,     w/2.0+2.0, h/2.0);
    painter.drawLine(w/2.0,     h/2.0-2.0, w/2.0,     h/2.0+2.0);

//     50000399 -49999699  100 2e-07 5e+07 5e+07 0.1 0.1
//    painter.translate(dx, dy);
//    painter.translate(-33554431, 0);
//    painter.drawText( +33554431, 0, "aaaaaaa");

    painter.end();
}

void Cartesian2DWidget1::wheelEvent(QWheelEvent* e)
{
    if (e->delta() > 0) zoomIn(); else zoomOut();
    update();
}

void Cartesian2DWidget1::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton)
    {
        leftButtonPressed = true;
        last = e->pos();
        setCursor(QCursor(Qt::ClosedHandCursor));
    }
}

void Cartesian2DWidget1::mouseReleaseEvent(QMouseEvent* e)
{
    Q_UNUSED(e)
    setCursor(QCursor(Qt::ArrowCursor));
    leftButtonPressed = false;
}

void Cartesian2DWidget1::mouseMoveEvent(QMouseEvent* e)
{
    if (leftButtonPressed) setCenterX(centerX() - ((double)(e->pos().x() - last.x())/(double)scaleX()*zoom()));
    if (leftButtonPressed) setCenterY(centerY() + ((double)(e->pos().y() - last.y())/(double)scaleY()*zoom()));

    last = e->pos();
    update();
}

void Cartesian2DWidget1::drawGridLines(QPainter& painter)
{
    painter.save();

    int w = width();
    int h = height();


//    int dx = centerX() * ((double)scaleX()/zoom());
//    int dy = centerY() * ((double)scaleY()/zoom());

//    int leftX   = -w/2 + dx;
//    int rightX  = +w/2 + dx;
//    int topY    = +h/2 - dy;
//    int bottomY = -h/2 - dy;

//    qDebug() << "void Cartesian2DWidget::drawGridLines(QPainter& painter) [" << leftX << ", " << rightX << "] [" << bottomY << ", " << topY << "]";

//    int a=1;
//    if (scaleX() % 5 == 0) {a = 5;} else
//        if (scaleX() % 4 == 0) {a = 4;} else
//            if (scaleX() % 2 == 0) {a = 2;}
//    a=5;

//    painter.setPen(QPen(QColor(0xE0E0D1),1.0, Qt::DashLine));
//    for (int i=leftX; i<rightX; i++) if ((i % (scaleX()/a)) == 0) painter.drawLine(i, bottomY, i, topY);
//    for (int i=bottomY; i<topY; i++) if ((i % (scaleY()/a)) == 0) painter.drawLine(leftX, i, rightX, i);

//    painter.setPen(QPen(QColor(0xCACABC)));
//    for (int i=leftX; i<rightX; i++) if ((i % scaleX()) == 0) painter.drawLine(i, bottomY, i, topY);
//    for (int i=bottomY; i<topY; i++) if ((i % scaleY()) == 0) painter.drawLine(leftX, i, rightX, i);

//    painter.setPen(QPen(Qt::black));
//    painter.drawLine(leftX, 0, rightX, 0);
//    painter.drawLine(0, bottomY, 0, topY);

    painter.restore();
}

void Cartesian2DWidget1::drawGridLabel(QPainter& painter)
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

    qDebug()  << leftX << rightX << topY << bottomY << scaleX() << zoom() << dx << dy << centerX() << centerY();

    // draw absis scale numbers
    for (int i=leftX; i<rightX; i++)
    {
        if (i % scaleX() == 0 && i != 0)
        {
            double number = ( i / scaleX() ) * zoom();
            QString s = axisNumber(number, zoomLevel());

            //qDebug() << topY << bottomY << leftX << rightX << scaleX() << i;

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

void Cartesian2DWidget1::drawR1Graphic(QPainter& painter)
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

void Cartesian2DWidget1::setXRange(double a, double b)
{
    double z = (double)width() / ((double)scaleX() * (b-a));
    setZoom(z);
    setCenter(0.5*(a+b), centerY());
    update();
}
