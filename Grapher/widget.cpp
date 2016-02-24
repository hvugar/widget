#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    setBackgroundRole(QPalette::Base);
    resize(600, 400);
    setMinimumSize(600, 400);
    setMaximumSize(600, 400);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *evt)
{
    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), Qt::gray);
    drawGraph18(painter);
}

void Widget::drawGraph11(QPainter &painter1)
{
    QPixmap pixmap(600, 400);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    QFont font;
    font.setFamily("Courier New");
    font.setBold(true);
    font.setPixelSize(16);
    painter.setFont(font);

    QFontMetrics fm(font);

    QPoint p1(50, 350);
    QPoint p2(550, 350);
    painter.drawLine(p1, p2);
    QPoint p3(300, 350);
    QPoint p4(300, 50);
    painter.drawLine(p3, p4);

    painter.drawLine(300, 340, 300, 350);
    painter.drawLine(200, 340, 200, 350);
    painter.drawLine(100, 340, 100, 350);
    painter.drawLine(400, 340, 400, 350);
    painter.drawLine(500, 340, 500, 350);

    for (int i=60; i<550; i+=20) painter.drawLine(i, 345, i, 350);

    painter.drawText(100-fm.width("-2")/2, 366, "-2");
    painter.drawText(200-fm.width("-1")/2, 366, "-1");
    painter.drawText(300-fm.width("0")/2, 366, "0");
    painter.drawText(400-fm.width("1")/2, 366, "1");
    painter.drawText(500-fm.width("2")/2, 366, "2");

    painter.drawPixmap(320, 30,  QPixmap("images/delta.png", "PNG"));
    painter.drawPixmap(545, 340, QPixmap("images/arrow_left.png", "PNG"));
    painter.drawPixmap(290, 40,  QPixmap("images/arrow_up.png", "PNG"));
    painter.drawPixmap(550, 320, QPixmap("images/x.png", "PNG"));

    painter.setBrush(Qt::white);
    painter.drawEllipse(297, 346, 6, 6);

    painter.end();

    pixmap.save("images/image11.png", "PNG");
    painter1.drawPixmap(0, 0, pixmap);
}

void Widget::drawGraph12(QPainter &painter1)
{
    QPixmap pixmap(600, 400);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    QFont font;
    font.setFamily("Courier New");
    font.setBold(true);
    font.setPixelSize(16);
    painter.setFont(font);

    QFontMetrics fm(font);

    QPoint p1(50, 330);
    QPoint p2(550, 330);
    painter.drawLine(p1, p2);
    QPoint p3(100, 370);
    QPoint p4(100, 50);
    painter.drawLine(p3, p4);
    painter.drawPixmap(545, 320, QPixmap("images/arrow_left.png", "PNG"));
    painter.drawPixmap(90, 40, QPixmap("images/arrow_up.png", "PNG"));
    painter.drawPixmap(550, 305, QPixmap("images/x.png", "PNG"));
    painter.drawPixmap(110, 30, QPixmap("images/t.png", "PNG"));

    painter.drawText(90-fm.width("0")/2, 345, "0");

    painter.setPen(QPen(Qt::black, 2.0, Qt::SolidLine));
    painter.drawLine(101, 330, 500, 330);
    painter.drawLine(101, 330, 101, 90);
    painter.drawLine(500, 330, 500, 90);
    painter.drawLine(101, 90, 500, 90);

    painter.setPen(QPen(Qt::black, 1.0, Qt::DotLine));
    for (int j=90; j<=330; j+=40)
    {
        painter.drawLine(101, j, 500, j);
    }
    for (int i=100; i<=500; i+=40)
    {
        painter.drawLine(i, 90, i, 330);
    }

    painter.drawPixmap(497, 340, QPixmap("images/l.png", "PNG"));
    painter.drawPixmap(80, 80, QPixmap("images/T1.png", "PNG"));

    pixmap.save("images/image12.png", "PNG");
    painter1.drawPixmap(0, 0, pixmap);
}

void Widget::drawGraph13(QPainter &painter1)
{
    QPixmap pixmap(300, 200);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    painter.setPen(QPen(Qt::black, 2.0, Qt::SolidLine));
    painter.drawLine(50, 50, 250, 50);
    painter.drawLine(150, 50, 150, 150);
    painter.setPen(QPen(Qt::black, 1.0, Qt::SolidLine));
    painter.setBrush(Qt::white);
    painter.drawEllipse(46, 46, 7, 7);
    painter.drawEllipse(146, 46, 7, 7);
    painter.drawEllipse(246, 46, 7, 7);
    painter.drawEllipse(146, 146, 7, 7);

    painter.drawPixmap(138, 25, QPixmap("images/ij.png", "PNG"));
    painter.drawPixmap(20, 25, QPixmap("images/im1j.png", "PNG"));
    painter.drawPixmap(220, 25, QPixmap("images/ip1j.png", "PNG"));
    painter.drawPixmap(120, 155, QPixmap("images/ijm1.png", "PNG"));

    painter.end();

    pixmap.save("images/image13.png", "PNG");

    painter1.drawPixmap(0, 0, pixmap);
}

void Widget::drawGraph14(QPainter &painter1)
{
    QPixmap pixmap(600, 400);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    QFont font;
    font.setFamily("Courier New");
    font.setBold(true);
    font.setPixelSize(16);
    painter.setFont(font);

    QFontMetrics fm(font);

    QPoint p1(50, 330);
    QPoint p2(550, 330);
    painter.drawLine(p1, p2);
    QPoint p3(100, 370);
    QPoint p4(100, 50);
    painter.drawLine(p3, p4);

    painter.drawPixmap(545, 320, QPixmap("images/arrow_left.png", "PNG"));
    painter.drawPixmap(90, 40, QPixmap("images/arrow_up.png", "PNG"));
    painter.drawText(90-fm.width("0")/2, 345, "0");

    painter.drawLine(300, 327, 300, 333);
    painter.drawLine(97, 100, 103, 100);

    painter.setPen(QPen(Qt::black, 2.0));
    painter.drawLine(50, 330, 250, 330);
    painter.drawLine(251, 100, 350, 100);
    painter.drawLine(351, 330, 550, 330);
    painter.setPen(QPen(Qt::black, 1.0, Qt::DashLine));
    painter.drawLine(250, 330, 250, 100);
    painter.drawLine(350, 330, 350, 100);

    painter.drawPixmap(293, 350, QPixmap("images/xi.png", "PNG"));
    painter.drawPixmap(224, 340, QPixmap("images/xi_minus_epsilon.png", "PNG"));
    painter.drawPixmap(326, 340, QPixmap("images/xi_plus_epsilon.png", "PNG"));
    painter.drawPixmap(550, 305, QPixmap("images/x.png", "PNG"));
    painter.drawPixmap(120, 30, QPixmap("images/delta_epsilon.png", "PNG"));
    painter.drawPixmap(80, 69, QPixmap("images/inverse_epsilon.png", "PNG"));

    pixmap.save("images/image14.png", "PNG");

    painter1.drawPixmap(0, 0, pixmap);
}

void Widget::drawGraph15(QPainter &painter1)
{
    QPixmap pixmap(600, 400);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    QFont font;
    font.setFamily("Courier New");
    font.setBold(true);
    font.setPixelSize(16);
    painter.setFont(font);

    QFontMetrics fm(font);

    QPoint p1(50, 330);
    QPoint p2(550, 330);
    painter.drawLine(p1, p2);
    QPoint p3(100, 370);
    QPoint p4(100, 50);
    painter.drawLine(p3, p4);
    painter.drawPixmap(545, 320, QPixmap("images/arrow_left.png", "PNG"));
    painter.drawPixmap(90, 40, QPixmap("images/arrow_up.png", "PNG"));
    painter.drawText(90-fm.width("0")/2, 345, "0");

    painter.drawLine(300, 327, 300, 333);
    painter.drawPixmap(293, 340, QPixmap("images/xi.png", "PNG"));
    painter.drawLine(300, 327, 300, 333);
    painter.drawPixmap(249, 345, QPixmap("images/x_i.png", "PNG"));
    painter.drawPixmap(344, 345, QPixmap("images/x_i1.png", "PNG"));
    //painter.drawLine(97, 100, 103, 100);

    painter.setPen(QPen(Qt::black, 2.0));
    painter.drawLine(50, 330, 260, 330);
    painter.drawLine(371, 330, 550, 330);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawLine(261, 100, 370, 150);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(QPen(Qt::black, 1.0, Qt::DashLine));
    painter.drawLine(260, 330, 260, 100);
    painter.drawLine(370, 330, 370, 150);

    painter.drawPixmap(550, 305, QPixmap("images/x.png", "PNG"));
    painter.drawPixmap(120, 30, QPixmap("images/delta_epsilon.png", "PNG"));
    //painter.drawPixmap(20, 85, QPixmap("images/inverse_epsilon_1.png", "PNG"));
    //painter.drawPixmap(20, 85, QPixmap("images/inverse_epsilon_1.png", "PNG"));
    //painter.drawPixmap(10, 135, QPixmap("images/inverse_epsilon_2.png", "PNG"));
    //painter.drawPixmap(10, 135, QPixmap("images/inverse_epsilon_2.png", "PNG"));

    //painter.setPen(QPen(Qt::black, 1.0, Qt::DotLine));
    //painter.drawLine(100, 100, 260, 100);
    //painter.drawLine(100, 150, 370, 150);

    pixmap.save("images/image15.png", "PNG");

    painter1.drawPixmap(0, 0, pixmap);
}

void Widget::drawGraph16(QPainter &painter1)
{
    QPixmap pixmap(600, 400);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    QFont font;
    font.setFamily("Courier New");
    font.setBold(true);
    font.setPixelSize(16);
    painter.setFont(font);

    QFontMetrics fm(font);

    QPoint p1(50, 330);
    QPoint p2(550, 330);
    painter.drawLine(p1, p2);
    QPoint p3(100, 370);
    QPoint p4(100, 50);
    painter.drawLine(p3, p4);
    painter.drawPixmap(545, 320, QPixmap("images/arrow_left.png", "PNG"));
    painter.drawPixmap(90, 40, QPixmap("images/arrow_up.png", "PNG"));

    painter.drawText(90-fm.width("0")/2, 345, "0");
    //    painter.drawLine(160, 327, 160, 333);
    //    painter.drawPixmap(144, 345, QPixmap("images/x_im1.png", "PNG"));

    painter.drawLine(300, 327, 300, 333);
    painter.drawPixmap(293, 340, QPixmap("images/xi.png", "PNG"));

    painter.drawLine(260, 327, 260, 333);
    painter.drawPixmap(249, 345, QPixmap("images/x_i.png", "PNG"));

    painter.drawLine(360, 327, 360, 333);
    painter.drawPixmap(344, 345, QPixmap("images/x_i1.png", "PNG"));


    //    painter.drawLine(460, 327, 460, 333);
    //    painter.drawPixmap(444, 345, QPixmap("images/x_i2.png", "PNG"));



    //    painter.setPen(QPen(Qt::black, 2.0));
    //    painter.drawLine(50, 330, 260, 330);
    //    painter.drawLine(371, 330, 550, 330);

    //    painter.drawLine(261, 100, 370, 150);
    //    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(QPen(Qt::black, 1.0, Qt::DashLine));


    painter.drawPixmap(550, 305, QPixmap("images/x.png", "PNG"));
    painter.drawPixmap(120, 30, QPixmap("images/delta_epsilon.png", "PNG"));

    painter.setPen(QPen(Qt::black, 1.0, Qt::DotLine));
    painter.drawLine(300, 130, 300, 330);
    painter.drawLine(260, 209, 260, 330);
    painter.drawLine(360, 265, 360, 330);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 1.0, Qt::SolidLine));
    QPointF p_1(100, 330);
    for (unsigned int i=50; i<550; i++)
    {
        double sigma = 40;
        double b = 1.0/(sigma*sqrt(2.0*M_PI));
        double d = 2.0*sigma*sigma;
        double c = exp(-((i-300.0)*(i-300.0))/d);
        double a = b * c;
        QPointF p_2(i, height()-70-a*20000);
        painter.drawLine(p_1, p_2);
        p_1 = p_2;
    }

    pixmap.save("images/image16.png", "PNG");

    painter1.drawPixmap(0, 0, pixmap);
}

void Widget::drawGraph17(QPainter &painter1)
{
    QPixmap pixmap(600, 400);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    QFont font;
    font.setFamily("Courier New");
    font.setBold(true);
    font.setPixelSize(16);
    painter.setFont(font);

    QFontMetrics fm(font);

    QPoint p1(50, 330);
    QPoint p2(550, 330);
    painter.drawLine(p1, p2);
    QPoint p3(100, 370);
    QPoint p4(100, 50);
    painter.drawLine(p3, p4);
    painter.drawPixmap(545, 320, QPixmap("images/arrow_left.png", "PNG"));
    painter.drawPixmap(90, 40, QPixmap("images/arrow_up.png", "PNG"));

    painter.drawPixmap(120,105,QPixmap("images/convex_polygon1.png", "PNG"));

    painter.setPen(QPen(Qt::black, 1.0, Qt::DotLine));
    for (int i=100; i<450; i+=25) painter.drawLine(i, 80, i, 330);
    for (int j=330; j>=105; j-=25) painter.drawLine(100, j, 450, j);

    painter.drawPixmap(550, 305, QPixmap("images/x1.png", "PNG"));
    painter.drawPixmap(110,  30, QPixmap("images/x2.png", "PNG"));
    painter.drawText(90-fm.width("0")/2, 345, "0");
    painter.drawPixmap(330, 183, QPixmap("images/Omega.png", "PNG"));

    pixmap.save("images/image17.png", "PNG");

    painter1.drawPixmap(0, 0, pixmap);
}

void Widget::drawGraph18(QPainter &painter1)
{
    QPixmap pixmap(600, 400);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    QFont font;
    font.setFamily("Arial");
    font.setBold(true);
    font.setPixelSize(16);
    painter.setFont(font);

    QFontMetrics fm(font);

    painter.drawPixmap(170, 132, QPixmap("images/arc.png", "PNG"));

    QPoint p1(50, 330);
    QPoint p2(550, 330);
    painter.drawLine(p1, p2);
    QPoint p3(100, 370);
    QPoint p4(100, 50);
    painter.drawLine(p3, p4);
    painter.drawPixmap(545, 320, QPixmap("images/arrow_left.png", "PNG"));
    painter.drawPixmap(90, 40, QPixmap("images/arrow_up.png", "PNG"));

    painter.setPen(QPen(Qt::black, 1.0, Qt::DotLine));
    for (int i=100; i<450; i+=50) painter.drawLine(i, 80, i, 330);
    for (int j=330; j>=105; j-=50) painter.drawLine(100, j, 450, j);

    painter.drawPixmap(550, 305, QPixmap("images/x1.png", "PNG"));
    painter.drawPixmap(110,  30, QPixmap("images/x2.png", "PNG"));
    painter.drawText(90-fm.width("0")/2, 345, "0");

    painter.setBrush(Qt::black);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawText(302, 228, "A");
    painter.drawText(352, 228, "C");
    painter.drawText(242, 228, "B");
    painter.drawEllipse(298, 228, 4, 4);
    painter.drawEllipse(348, 228, 4, 4);
    painter.drawEllipse(256, 228, 4, 4);

    pixmap.save("images/image18.png", "PNG");

    painter1.drawPixmap(0, 0, pixmap);
}
