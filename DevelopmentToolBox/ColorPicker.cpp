#include "ColorPicker.h"
#include "ui_ColorPicker.h"

ColorPicker::ColorPicker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorPicker)
{
    ui->setupUi(this);
}

ColorPicker::~ColorPicker()
{
    delete ui;
}
