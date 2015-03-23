#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QDialog>
#include <QTextLine>
#include <QLabel>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QRadioButton>
#include <QPointF>
#include <QDebug>

class SettingWidget : public QDialog
{
    Q_OBJECT
public:
    explicit SettingWidget(QWidget *parent = 0);
    ~SettingWidget();

    void setCenter(double x, double y);
    QPointF center() const;
    void setXRange(double a, double b);
    QPointF xrange() const;

    QRadioButton *radioButton1;
    QRadioButton *radioButton2;

private:
    QDoubleSpinBox *doubleSpinBox1;
    QDoubleSpinBox *doubleSpinBox2;

    QDoubleSpinBox *doubleSpinBox3;
    QDoubleSpinBox *doubleSpinBox4;

    QPushButton *button1;
    QPushButton *button2;

signals:

public slots:
};

#endif // SETTINGWIDGET_H
