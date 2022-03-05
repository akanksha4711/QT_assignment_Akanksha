#include "aboutme.h"
#include "ui_aboutme.h"
#include <QPixmap>

AboutMe::AboutMe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutMe)
{
    ui->setupUi(this);
    this->resize(900,800);
    int w=ui->label_pic->width();
    int h=ui->label_pic->height();
    QPixmap pix("/home/trinity/Desktop/qpad/aboutme.png");
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

AboutMe::~AboutMe()
{
    delete ui;
}
