#include "settingwidget.h"

#define DECIMALS   6
#define SINGLE_STP 1.0
#define CENTER_MIN -1000000000.0
#define CENTER_MAX +1000000000.0

SettingWidget::SettingWidget(QWidget *parent) : QDialog(parent)
{
    radioButton1 = new QRadioButton;
    radioButton2 = new QRadioButton;
    radioButton1->setChecked(true);

    doubleSpinBox1 = new QDoubleSpinBox;
    doubleSpinBox1->setDecimals(DECIMALS);
    doubleSpinBox1->setSingleStep(SINGLE_STP);
    doubleSpinBox1->setRange(CENTER_MIN, CENTER_MAX);

    doubleSpinBox2 = new QDoubleSpinBox;
    doubleSpinBox2->setDecimals(DECIMALS);
    doubleSpinBox2->setSingleStep(SINGLE_STP);
    doubleSpinBox2->setRange(CENTER_MIN, CENTER_MAX);

    doubleSpinBox3 = new QDoubleSpinBox;
    doubleSpinBox3->setDecimals(DECIMALS);
    doubleSpinBox3->setSingleStep(SINGLE_STP);
    doubleSpinBox3->setRange(CENTER_MIN, CENTER_MAX);

    doubleSpinBox4 = new QDoubleSpinBox;
    doubleSpinBox4->setDecimals(DECIMALS);
    doubleSpinBox4->setSingleStep(SINGLE_STP);
    doubleSpinBox4->setRange(CENTER_MIN, CENTER_MAX);

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(radioButton1);
    hlayout1->addWidget(doubleSpinBox1);
    hlayout1->addWidget(doubleSpinBox2);

    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->addWidget(radioButton2);
    hlayout2->addWidget(doubleSpinBox3);
    hlayout2->addWidget(doubleSpinBox4);

    button1 = new QPushButton(tr("&Apply"));
    connect(button1, SIGNAL(clicked()), this, SLOT(close()));
    button2 = new QPushButton(tr("&Close"));
    connect(button2, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *hlayout3 = new QHBoxLayout;
    hlayout3->addStretch();
    hlayout3->addWidget(button1);
    hlayout3->addWidget(button2);

    QFormLayout *form1 = new QFormLayout;
    form1->setRowWrapPolicy(QFormLayout::DontWrapRows);
    form1->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
    form1->setLabelAlignment(Qt::AlignLeft);
    form1->addRow("Center (X/Y):", hlayout1);
    form1->addRow("Range X:", hlayout2);
    form1->addRow(hlayout3);

    setLayout(form1);
   // resize(320, 240);
    setMinimumWidth(320);
    setMaximumWidth(320);
}

SettingWidget::~SettingWidget()
{

}

void SettingWidget::setCenter(double x, double y)
{
    doubleSpinBox1->setValue(x);
    doubleSpinBox2->setValue(y);
}

QPointF SettingWidget::center() const
{
    QPointF c;
    c.setX(doubleSpinBox1->value());
    c.setY(doubleSpinBox2->value());
    return c;
}

void SettingWidget::setXRange(double a, double b)
{
    doubleSpinBox3->setValue(a);
    doubleSpinBox4->setValue(b);
}

QPointF SettingWidget::xrange() const
{
    QPointF c;
    c.setX(doubleSpinBox3->value());
    c.setY(doubleSpinBox4->value());
    return c;
}
