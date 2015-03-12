#include "cartesianwidget2.h"
#include <QtGui/QFont>
#include <QtGui/QFontMetrics>
#include <QtGui/QFontMetricsF>
#include <QtCore/QDebug>

#include "math.h"

CartesianWidget2::CartesianWidget2(QWidget *parent) : CartesianWidget(parent)
{
    setScale(100, 100);
    setCenter(0.0, 0.0);
    setOffset(0, 0);
    i = 1;
}

CartesianWidget2::~CartesianWidget2()
{
}

void CartesianWidget2::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    update();
}

void CartesianWidget2::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    int w = width();
    int h = height();

    QFont font1;
    font1.setFamily("Consolas");
    font1.setPointSize(10);
    setFont(font1);

    QPainter painter(this);
    painter.save();

    double dx = w/2.0 - centerX() * scaleX();
    double dy = h/2.0 + centerY() * scaleY();
    painter.translate(dx, dy);

    drawGridLines(painter);
    drawGridLabel(painter);
    //drawR1Graphic(painter);

    painter.restore();

    painter.setPen(Qt::red);
    painter.drawLine(w/2-2,h/2,w/2+2,h/2);
    painter.drawLine(w/2,h/2-2,w/2,h/2+2);

    painter.end();
}

void CartesianWidget2::wheelEvent(QWheelEvent* e)
{
//    e->delta() > 0 ? setScale(scaleX()*2.0, scaleY()*2.0) : setScale(scaleX()/2.0, scaleY()/2.0);
    int min = 80;
    int max = 150;

    int delta = e->delta();
    if (delta > 0)
    {
        qDebug() << i;
        setScale(scaleX() + 10, scaleY() + 10);
        if (scaleX() > max)
        {
            setScale(min, min);

            if (i % 3 == 1)
            {
                setZoom(zoom()/2.0);
            }
            if (i % 3 == 2)
            {
                setZoom(zoom()/2.5);
            }
            if (i % 3 == 0)
            {
                setZoom(zoom()/2.0);
            }
            i++;
        }
    }
    else
    {
        setScale(scaleX() - 10, scaleY() - 10);
        if (scaleX() < min)
        {
            setScale(max, max);

            if (i % 3 == 1)
            {
                setZoom(zoom()*2.0);
            }
            if (i % 3 == 2)
            {
                setZoom(zoom()*2.5);
            }
            if (i % 3 == 0)
            {
                setZoom(zoom()*2.0);
            }
            i++;
        }
    }

    update();
}

void CartesianWidget2::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton)
    {
        leftButtonPressed = true;
        last = e->pos();
        setCursor(QCursor(Qt::ClosedHandCursor));
    }
}

void CartesianWidget2::mouseReleaseEvent(QMouseEvent* e)
{
    Q_UNUSED(e)
    setCursor(QCursor(Qt::ArrowCursor));
    leftButtonPressed = false;
}

void CartesianWidget2::mouseMoveEvent(QMouseEvent* e)
{
    if (leftButtonPressed) setCenterX(centerX() - ((double)(e->pos().x() - last.x())/(double)scaleX()));
    if (leftButtonPressed) setCenterY(centerY() + ((double)(e->pos().y() - last.y())/(double)scaleY()));

    last = e->pos();
    update();
}

void CartesianWidget2::drawGridLines(QPainter& painter)
{
    painter.save();

    int w = width();
    int h = height();

    int dx = centerX() * scaleX();
    int dy = centerY() * scaleY();

    int leftX   = -w/2+dx;
    int rightX  = w/2+dx;
    int topY    = h/2-dy;
    int bottomY = -h/2-dy;

//    int hx = w / scaleX();
//    int hy = h / scaleY();
//    int mx = w % scaleX();
//    int my = h % scaleY();

//    qDebug() << hx << hy << mx << my;

    int a=1;
    if (scaleX() % 5 == 0) {a = 5;} else
    if (scaleX() % 4 == 0) {a = 4;} else
    if (scaleX() % 2 == 0) {a = 2;} else
    a = 1;

    painter.setPen(QPen(QColor(0xE0E0D1),1.0, Qt::DashLine));
    for (int i=leftX; i<rightX; i++) if ((i % (scaleX()/a)) == 0) painter.drawLine(i, bottomY, i, topY);
    for (int i=bottomY; i<topY; i++) if ((i % (scaleY()/a)) == 0) painter.drawLine(leftX, i, rightX, i);

    painter.setPen(QPen(QColor(0xCACABC)));
    for (int i=leftX; i<rightX; i++) if ((i % scaleX()) == 0) painter.drawLine(i, bottomY, i, topY);
    for (int i=bottomY; i<topY; i++) if ((i % scaleY()) == 0) painter.drawLine(leftX, i, rightX, i);

    painter.setPen(QPen(Qt::black));
    painter.drawLine(leftX, 0, rightX, 0);
    painter.drawLine(0, bottomY, 0, topY);

 /*
    int dx = centerX() * scaleX();
    int dy = centerY() * scaleY();

    int leftX   = -w/2+dx;
    int rightX  = w/2+dx;
    int topY    = h/2-dy;
    int bottomY = -h/2-dy;

    painter.setPen(QPen(QColor(0xE0E0D1),1.0, Qt::DashLine));
    for (int i=leftX; i<rightX; i++) if ((i % 20) == 0) painter.drawLine(i, bottomY, i, topY);
    for (int i=bottomY; i<topY; i++) if ((i % 20) == 0) painter.drawLine(leftX, i, rightX, i);

    painter.setPen(QPen(QColor(0xCACABC)));
    for (int i=leftX; i<rightX; i++) if ((i % 100) == 0) painter.drawLine(i, bottomY, i, topY);
    for (int i=bottomY; i<topY; i++) if ((i % 100) == 0) painter.drawLine(leftX, i, rightX, i);

    //Drawin main axis (absis and ordinate arrow)
    painter.setPen(QPen(Qt::black));
    painter.drawLine(leftX, 0, rightX, 0);
    painter.drawLine(0, bottomY, 0, topY);
*/


    painter.restore();
}

void CartesianWidget2::drawGridLabel(QPainter& painter)
{
    painter.save();

    QFontMetrics fm = painter.fontMetrics();

    int w = width();
    int h = height();

    int dx = centerX() * scaleX();
    int dy = centerY() * scaleY();

    int leftX   = -w/2+dx;
    int rightX  = w/2+dx;
    int topY    = h/2-dy;
    int bottomY = -h/2-dy;

    // draw absis scale numbers
    for (int i=leftX; i<rightX; i++)
    {
        if (i % scaleX() == 0 && i != 0)
        {
            double number = ((double)(i) / scaleX())*zoom();
            int precition = 8;
            QString s = QString::number(number, 'f', precition);
            while(s.endsWith('0') || s.endsWith('.')) s.chop(1);
            painter.drawText(i-fm.width(s)/2, fm.height(), s);
        }
    }

    // draw ordinate scale numbers
    for (int i=bottomY; i<topY; i++)
    {
        if (i % scaleY() == 0 && i != 0)
        {
            double number = ((double)(i) / scaleY())*zoom();
            int precition = 8;
            QString s = QString::number(number, 'f', precition);
            while(s.endsWith('0') || s.endsWith('.')) s.chop(1);
            painter.drawText(-fm.width(s)-4, i+fm.height()/2-3, s);
        }
    }

    // draw zero number
    painter.drawText(-fm.width("0")-4, fm.height(), "0");

    painter.restore();
}

void CartesianWidget2::drawR1Graphic(QPainter& painter)
{
    painter.save();

    painter.setRenderHint(QPainter::Antialiasing, true);

    for (int i=0; i<fcs.size(); i++)
    {
        FunctionConfig fc = fcs.at(i);
        painter.setPen(QPen(QColor(fc.penColor), 1.0));

        int min = fc.a * scaleX();
        int max = fc.b * scaleX();

        if (fc.a < xmin()) min = xmin() * scaleX();
        if (fc.b > xmax()) max = xmax() * scaleX();

        for (int i=min; i<max; i++)
        {
            double x1 = (double)(i+0)/(double)scaleX();
            double x2 = (double)(i+1)/(double)scaleX();

            double y1 = -fc.f(x1);
            double y2 = -fc.f(x2);

            int y11 = y1*scaleY();
            int y12 = y2*scaleY();
            //qDebug() << min << max << i << i+1 << x1 << x2 << y11 << y12;

            painter.drawLine(i, y11, i+1, y12);
        }
    }

    painter.restore();
}
