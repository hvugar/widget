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
    QPixmap screenshot;
    screenshot = QPixmap::grabWidget(this, rect());
    screenshot.save("images/ok/image2.png","PNG");
}

void Widget::paintEvent(QPaintEvent *evt)
{
    image2(evt);
}

void Widget::image1(QPaintEvent *evt)
{
    QPainter painter(this);

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
}

void Widget::image3(QPaintEvent *evt)
{
    QPainter painter(this);

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
}

void Widget::image2(QPaintEvent *evt)
{
    QPainter painter(this);

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

    painter.drawLine(300, 327, 300, 333);
//    painter.drawLine(250, 325, 250, 335);
//    painter.drawLine(350, 325, 350, 335);
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
}
