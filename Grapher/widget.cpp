#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    setBackgroundRole(QPalette::Base);
    resize(600, 400);
}

Widget::~Widget()
{
    QPixmap screenshot;
    screenshot = QPixmap::grabWidget(this, rect());
    screenshot.save("image/ok/image1.png","PNG");

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
    painter.drawText(400-fm.width("2")/2, 366, "2");
    painter.drawText(500-fm.width("1")/2, 366, "1");

    QImage image1("images/delta.png", "PNG");
    painter.drawImage(320, 30, image1);

    QImage image2("images/arrow_left.png", "PNG");
    painter.drawImage(545, 340, image2);

    QImage image3("images/arrow_up.png", "PNG");
    painter.drawImage(300-10, 40, image3);

    QImage image4("images/x.png", "PNG");
    painter.drawImage(550, 320, image4);

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

    QImage image1("images/arrow_left.png", "PNG");
    painter.drawImage(545, 320, image1);

    QImage image2("images/arrow_up.png", "PNG");
    painter.drawImage(90, 40, image2);


    painter.drawLine(300, 325, 300, 335);
    painter.drawLine(250, 325, 250, 335);
    painter.drawLine(350, 325, 350, 335);

    QImage image3("images/xi.png", "PNG");
    painter.drawImage(300-image3.width()/2, 350, image3);

    QImage image4("images/xi_minus_epsilon.png", "PNG");
    painter.drawImage(240-image4.width()/2, 340, image4);

    QImage image5("images/xi_plus_epsilon.png", "PNG");
    painter.drawImage(320+image5.width()/2, 340, image5);


}
