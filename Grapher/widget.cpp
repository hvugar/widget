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
    QPixmap pixmap(300, 200);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    QFont font;
    font.setFamily("Courier New");
    font.setBold(true);
    font.setPixelSize(14);
    painter.setFont(font);

    QFontMetrics fm(font);

    painter.drawLine(0, 180, 300, 180);
    painter.drawLine(150, 180, 150, 10);
    for (int i=30; i<=270; i+=40) painter.drawLine(i, 177, i, 183);
    for (int i=10; i<=290; i+=40) painter.drawLine(i, 178, i, 182);

    painter.drawPixmap(283, 171, QPixmap("images/arrow_left.png", "PNG"));
    painter.drawPixmap(140, 6,  QPixmap("images/arrow_up.png", "PNG"));
    painter.drawPixmap(283, 155, QPixmap("images/x.png", "PNG"));
    painter.drawPixmap(160, 0,  QPixmap("images/delta.png", "PNG"));

    painter.setBrush(Qt::white);
    painter.drawEllipse(147, 177, 6, 6);

    painter.drawText(30-fm.width("-3")/2, 198, "-3");
    painter.drawText(70-fm.width("-2")/2, 198, "-2");
    painter.drawText(110-fm.width("-1")/2, 198, "-1");
    painter.drawText(150-fm.width("0")/2, 198, "0");
    painter.drawText(190-fm.width("1")/2, 198, "1");
    painter.drawText(230-fm.width("2")/2, 198, "2");
    painter.drawText(270-fm.width("3")/2, 198, "3");

    painter.end();

    pixmap.save("images/image11.png", "PNG");
    painter1.drawPixmap(0, 0, pixmap);
}

void Widget::drawGraph12(QPainter &painter1)
{
    QPixmap pixmap(300, 200);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    QFont font;
    font.setFamily("Courier New");
    font.setBold(true);
    font.setPointSize(12);
    painter.setFont(font);

    QFontMetrics fm(font);

    painter.drawLine(0, 180, 300, 180);
    painter.drawLine(20, 200, 20, 0);
    painter.drawPixmap(284, 170, QPixmap("images/arrow_left.png", "PNG"));
    painter.drawPixmap(10, -4, QPixmap("images/arrow_up.png", "PNG"));
    painter.drawPixmap(550, 305, QPixmap("images/x.png", "PNG"));
    //painter.drawPixmap(30, 0, QPixmap("images/t.png", "PNG"));

    font.setFamily("Times New Roman");
    painter.drawText(12-fm.width("0")/2, 196, "0");
    font.setItalic(true);
    font.setBold(false);
    font.setPointSize(16);
    painter.setFont(font);
    painter.drawText(260-fm.width("l")/2, 198, "l");
    painter.drawText(8-fm.width("T")/2, 45, "T");
    painter.drawText(30+fm.width("t")/2, 16, "t");
    painter.drawText(300-fm.width("x"), 168, "x");

    painter.setPen(QPen(Qt::black, 2.0, Qt::SolidLine));
    painter.drawLine(21, 180, 260, 180);
    painter.drawLine(21, 30, 260, 30);
    painter.drawLine(260, 30, 260, 180);
    painter.drawLine(21, 30, 21, 180);

    painter.setPen(QPen(Qt::black, 1.0, Qt::DotLine));
    for (int j=30; j<=180; j+=30)
    {
        painter.drawLine(21, j, 260, j);
    }
    for (int i=20; i<=260; i+=30)
    {
        painter.drawLine(i, 30, i, 180);
    }

    painter.setPen(QPen(Qt::black, 1.0, Qt::SolidLine));
    painter.drawLine(110, 90, 170, 90);
    painter.drawLine(140, 90, 140, 120);
    painter.setPen(QPen(Qt::black, 1.0, Qt::SolidLine));
    painter.setBrush(Qt::black);
    painter.drawEllipse(108, 88, 4, 4);
    painter.drawEllipse(138, 88, 4, 4);
    painter.drawEllipse(168, 88, 4, 4);
    painter.drawEllipse(138, 118, 4, 4);

    font.setFamily("Times New Roman");
    font.setItalic(true);
    font.setBold(true);
    font.setPointSize(12);
    painter.setFont(font);
    painter.drawText(112-fm.width("i-1, j")/2, 80, "i-1, j");
    painter.drawText(172, 80, "i+1, j");
    painter.drawText(150-fm.width("i, j")/2, 80, "i, j");
    painter.drawText(160-fm.width("i, j-1")/2, 140, "i, j-1");

    //painter.drawPixmap(260, 184, QPixmap("images/l.png", "PNG"));
    //painter.drawPixmap(80, 80, QPixmap("images/T1.png", "PNG"));

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
    QPixmap pixmap(400, 280);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    QFont font;
    font.setFamily("Courier New");
    font.setBold(true);
    font.setPixelSize(16);
    painter.setFont(font);

    QFontMetrics fm(font);

    painter.drawLine(0, 230, 400, 230);
    painter.drawLine(30, 250, 30, 0);

    painter.drawPixmap(385, 220, QPixmap("images/arrow_left.png", "PNG"));
    painter.drawPixmap(20, -4, QPixmap("images/arrow_up.png", "PNG"));
    painter.drawText(22-fm.width("0")/2, 245, "0");

    painter.drawLine(200, 227, 200, 233);
    painter.drawLine(27, 50, 33, 50);

    painter.setPen(QPen(Qt::black, 2.0));
    painter.drawLine(0, 230, 150, 230);
    painter.drawLine(151, 50, 250, 50);
    painter.drawLine(251, 230, 400, 230);
    painter.setPen(QPen(Qt::black, 1.0, Qt::DashLine));
    painter.drawLine(150, 230, 150, 50);
    painter.drawLine(250, 230, 250, 50);

    painter.drawPixmap(195, 235, QPixmap("images/xi.png", "PNG"));
    painter.drawPixmap(100, 235, QPixmap("images/xi_minus_epsilon.png", "PNG"));
    painter.drawPixmap(250, 235, QPixmap("images/xi_plus_epsilon.png", "PNG"));
    painter.drawPixmap(384, 200, QPixmap("images/x.png", "PNG"));
    painter.drawPixmap(50, 0, QPixmap("images/delta_epsilon.png", "PNG"));
    painter.drawPixmap(10, 20, QPixmap("images/inverse_epsilon.png", "PNG"));

    pixmap.save("images/image14.png", "PNG");

    painter1.drawPixmap(0, 0, pixmap);
}

void Widget::drawGraph15(QPainter &painter1)
{
    QPixmap pixmap(400, 260);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    QFont font;
    font.setFamily("Courier New");
    font.setBold(true);
    font.setPixelSize(16);
    painter.setFont(font);

    QFontMetrics fm(font);

    painter.drawLine(0, 230, 400, 230);
    painter.drawLine(30, 250, 30, 0);
    painter.drawPixmap(385, 220, QPixmap("images/arrow_left.png", "PNG"));
    painter.drawPixmap(20, -4, QPixmap("images/arrow_up.png", "PNG"));
    painter.drawText(22-fm.width("0")/2, 245, "0");

    painter.drawLine(200, 227, 200, 233);
    //painter.drawLine(27, 50, 33, 50);

//    painter.drawPixmap(545, 320, QPixmap("images/arrow_left.png", "PNG"));
//    painter.drawPixmap(90, 40, QPixmap("images/arrow_up.png", "PNG"));
//    painter.drawText(90-fm.width("0")/2, 345, "0");

    painter.drawLine(200, 227, 200, 233);
    painter.drawPixmap(195, 235, QPixmap("images/xi.png", "PNG"));
//    painter.drawPixmap(293, 340, QPixmap("images/xi.png", "PNG"));
    painter.drawLine(200, 227, 200, 233);
    painter.drawPixmap(139, 235, QPixmap("images/x_i.png", "PNG"));
    painter.drawPixmap(244, 235, QPixmap("images/x_i1.png", "PNG"));
    //painter.drawLine(97, 100, 103, 100);

    painter.setPen(QPen(Qt::black, 2.0));
    painter.drawLine(50, 330, 260, 330);
    painter.drawLine(371, 330, 550, 330);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawLine(151, 50, 270, 100);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(QPen(Qt::black, 1.0, Qt::DashLine));
    painter.drawLine(150, 230, 150, 50);
    painter.drawLine(270, 230, 270, 100);

    painter.drawPixmap(384, 200, QPixmap("images/x.png", "PNG"));
//    painter.drawPixmap(120, 30, QPixmap("images/delta_epsilon.png", "PNG"));
    painter.drawPixmap(50, 0, QPixmap("images/delta_epsilon.png", "PNG"));
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
    QPixmap pixmap(400, 260);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    QFont font;
    font.setFamily("Courier New");
    font.setBold(true);
    font.setPixelSize(16);
    painter.setFont(font);

    QFontMetrics fm(font);

    painter.drawLine(0, 230, 400, 230);
    painter.drawLine(30, 250, 30, 0);
    painter.drawPixmap(384, 220, QPixmap("images/arrow_left.png", "PNG"));
    painter.drawPixmap(20, -4, QPixmap("images/arrow_up.png", "PNG"));
    painter.drawText(22-fm.width("0")/2, 245, "0");

//    QPoint p1(50, 330);
//    QPoint p2(550, 330);
//    painter.drawLine(p1, p2);
//    QPoint p3(100, 370);
//    QPoint p4(100, 50);
//    painter.drawLine(p3, p4);
//    painter.drawPixmap(545, 320, QPixmap("images/arrow_left.png", "PNG"));
//    painter.drawPixmap(90, 40, QPixmap("images/arrow_up.png", "PNG"));

    painter.drawText(90-fm.width("0")/2, 345, "0");
    //    painter.drawLine(160, 327, 160, 333);
    //    painter.drawPixmap(144, 345, QPixmap("images/x_im1.png", "PNG"));

    painter.drawLine(200, 227, 200, 233);
    painter.drawPixmap(193, 235, QPixmap("images/xi.png", "PNG"));

    painter.drawLine(160, 227, 160, 233);
    painter.drawPixmap(149, 240, QPixmap("images/x_i.png", "PNG"));

    painter.drawLine(260, 227, 260, 233);
    painter.drawPixmap(244, 240, QPixmap("images/x_i1.png", "PNG"));


    //    painter.drawLine(460, 327, 460, 333);
    //    painter.drawPixmap(444, 345, QPixmap("images/x_i2.png", "PNG"));



    //    painter.setPen(QPen(Qt::black, 2.0));
    //    painter.drawLine(50, 330, 260, 330);
    //    painter.drawLine(371, 330, 550, 330);

    //    painter.drawLine(261, 100, 370, 150);
    //    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(QPen(Qt::black, 1.0, Qt::DashLine));


    //painter.drawPixmap(550, 305, QPixmap("images/x.png", "PNG"));
    painter.drawPixmap(384, 200, QPixmap("images/x.png", "PNG"));
    //painter.drawPixmap(120, 30, QPixmap("images/delta_epsilon.png", "PNG"));
    painter.drawPixmap(50, 0, QPixmap("images/delta_epsilon.png", "PNG"));

    painter.setPen(QPen(Qt::black, 1.0, Qt::DotLine));
    painter.drawLine(200, 30, 200, 230);
    painter.drawLine(160, 109, 160, 230);
    painter.drawLine(260, 165, 260, 230);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 1.0, Qt::SolidLine));
    QPointF p_1(0, 230);
    for (unsigned int i=50; i<400; i++)
    {
        double sigma = 40;
        double b = 1.0/(sigma*sqrt(2.0*M_PI));
        double d = 2.0*sigma*sigma;
        double c = exp(-((i-200.0)*(i-200.0))/d);
        double a = b * c;
        QPointF p_2(i, height()-70-100-a*20000);
        painter.drawLine(p_1, p_2);
        p_1 = p_2;
    }

    pixmap.save("images/image16.png", "PNG");

    painter1.drawPixmap(0, 0, pixmap);
}

void Widget::drawGraph17(QPainter &painter1)
{
    QPixmap pixmap(350, 250);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    QFont font;
    font.setFamily("Courier New");
    font.setBold(true);
    font.setPixelSize(16);
    painter.setFont(font);

    QFontMetrics fm(font);

    painter.drawLine(0, 230, 350, 230);
    painter.drawLine(30, 250, 30, 0);
//    painter.drawPixmap(545, 320, QPixmap("images/arrow_left.png", "PNG"));
//    painter.drawPixmap(90, 40, QPixmap("images/arrow_up.png", "PNG"));
    painter.drawPixmap(334, 220, QPixmap("images/arrow_left.png", "PNG"));
    painter.drawPixmap(20, -4, QPixmap("images/arrow_up.png", "PNG"));
    painter.drawText(22-fm.width("0")/2, 245, "0");
    painter.drawPixmap(40,55,250,175,QPixmap("images/convex_polygon1.png", "PNG"));

    painter.setPen(QPen(Qt::black, 1.0, Qt::DotLine));
    for (int i=30; i<330; i+=25) painter.drawLine(i, 55, i, 230);
    for (int j=55; j<230; j+=25) painter.drawLine(30, j, 305, j);

    painter.drawPixmap(320, 205, QPixmap("images/x1.png", "PNG"));
    painter.drawPixmap(40, 0, QPixmap("images/x2.png", "PNG"));
    //painter.drawText(90-fm.width("0")/2, 345, "0");
    painter.drawPixmap(230, 100, QPixmap("images/Omega.png", "PNG"));
//    font.setBold(false);
    font.setPointSize(18);
    painter.setFont(font);
    painter.drawText(60, 80, QString(QChar(0x0393)));
//    font.setPointSize(20);
//    painter.setFont(font);
//    painter.drawText(240, 140, QString(QChar(0x03A9)));


    pixmap.save("images/image17.png", "PNG");

    painter1.drawPixmap(0, 0, pixmap);
}

void Widget::drawGraph18(QPainter &painter1)
{
    QPixmap pixmap(350, 250);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    QFont font;
    font.setFamily("Courier New");
    //font.setBold(true);
    font.setPixelSize(16);
    painter.setFont(font);

    QFontMetrics fm(font);

    painter.drawPixmap(80, 32, QPixmap("images/arc.png", "PNG"));

    painter.drawLine(0, 230, 350, 230);
    painter.drawLine(30, 250, 30, 0);
//    painter.drawPixmap(545, 320, QPixmap("images/arrow_left.png", "PNG"));
//    painter.drawPixmap(90, 40, QPixmap("images/arrow_up.png", "PNG"));
    painter.drawPixmap(334, 220, QPixmap("images/arrow_left.png", "PNG"));
    painter.drawPixmap(20, -4, QPixmap("images/arrow_up.png", "PNG"));
    painter.drawText(22-fm.width("0")/2, 245, "0");
    //painter.drawPixmap(40,55,250,175,QPixmap("images/convex_polygon1.png", "PNG"));

    painter.setPen(QPen(Qt::black, 1.0, Qt::DotLine));
    for (int i=30; i<330; i+=30) painter.drawLine(i, 50, i, 230);
    for (int j=50; j<230; j+=30) painter.drawLine(30, j, 300, j);

    painter.drawPixmap(320, 205, QPixmap("images/x1.png", "PNG"));
    painter.drawPixmap(40, 0, QPixmap("images/x2.png", "PNG"));

//    QPoint p1(50, 330);
//    QPoint p2(550, 330);
//    painter.drawLine(p1, p2);
//    QPoint p3(100, 370);
//    QPoint p4(100, 50);
//    painter.drawLine(p3, p4);
//    painter.drawPixmap(545, 320, QPixmap("images/arrow_left.png", "PNG"));
//    painter.drawPixmap(90, 40, QPixmap("images/arrow_up.png", "PNG"));

//    painter.setPen(QPen(Qt::black, 1.0, Qt::DotLine));
//    for (int i=100; i<450; i+=50) painter.drawLine(i, 80, i, 330);
//    for (int j=330; j>=105; j-=50) painter.drawLine(100, j, 450, j);

//    painter.drawPixmap(550, 305, QPixmap("images/x1.png", "PNG"));
//    painter.drawPixmap(110,  30, QPixmap("images/x2.png", "PNG"));
//    painter.drawText(90-fm.width("0")/2, 345, "0");

    font.setFamily("Arial");
    font.setBold(true);
    font.setPixelSize(16);
    painter.setFont(font);

    painter.setBrush(Qt::black);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawText(182, 138, "A");
    painter.drawText(212, 138, "C");
    painter.drawText(142, 138, "B");
    painter.drawEllipse(160, 138, 4, 4);
    painter.drawEllipse(178, 138, 4, 4);
    painter.drawEllipse(208, 138, 4, 4);

    pixmap.save("images/image18.png", "PNG");

    painter1.drawPixmap(0, 0, pixmap);
}

void Widget::drawGraph19(QPainter &painter1)
{
    QPixmap pixmap(300, 400);
    resize(300, 400);
    setMinimumSize(300, 400);
    setMaximumSize(300, 400);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    QFont font;
    font.setFamily("Arial");
    font.setBold(true);
    font.setPixelSize(16);
    painter.setFont(font);

    QFontMetrics fm(font);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawLine(50, 30, 250, 120);
    painter.drawLine(50, 120, 250, 30);

    painter.drawLine(50, 150, 250, 240);
    painter.drawLine(50, 240, 250, 150);

    painter.drawLine(50, 270, 250, 360);
    painter.drawLine(50, 360, 250, 270);

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(QPen(Qt::black, 1.0, Qt::DashLine));
    painter.drawLine(150, 75, 230, 75);
    painter.drawLine(150, 195, 230, 195);
    painter.drawLine(150, 315, 230, 315);

    painter.setPen(QPen(Qt::black, 1.0, Qt::DashLine));
    painter.drawLine(150, 75, 150, 315);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 1.0, Qt::SolidLine));
    painter.setBrush(Qt::white);
    painter.drawEllipse(146, 71, 8, 8);
    painter.drawEllipse(46, 26, 8, 8);
    painter.drawEllipse(246, 116, 8, 8);
    painter.drawEllipse(146, 191, 8, 8);
    painter.drawEllipse(246, 146, 8, 8);
    painter.drawEllipse(46, 236, 8, 8);
    painter.drawEllipse(146, 311, 8, 8);
    painter.drawEllipse(46, 266, 8, 8);
    painter.drawEllipse(246, 356, 8, 8);

    painter.drawPixmap(260, 110, QPixmap("images/x1.png", "PNG"));
    painter.drawPixmap(10, 110, QPixmap("images/x2.png", "PNG"));
    painter.drawPixmap(260, 230, QPixmap("images/x1.png", "PNG"));
    painter.drawPixmap(10, 230, QPixmap("images/x2.png", "PNG"));
    painter.drawPixmap(260, 350, QPixmap("images/x1.png", "PNG"));
    painter.drawPixmap(10, 350, QPixmap("images/x2.png", "PNG"));
    painter.drawPixmap(240, 70, QPixmap("images/k.png", "PNG"));
    painter.drawPixmap(240, 175, QPixmap("images/k12.png", "PNG"));
    painter.drawPixmap(240, 310, QPixmap("images/k1.png", "PNG"));

    pixmap.save("images/image19.png", "PNG");
    painter1.drawPixmap(0, 0, pixmap);
}
