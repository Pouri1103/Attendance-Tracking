#include "winsize.h"
#include "ui_winsize.h"

winsize::winsize(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::winsize)
{
    ui->setupUi(this);

    /////////////////////////////////////////////////////////////////

    connect(ui->PbCancel,&QAbstractButton::clicked,this,&winsize::close);

    /////////////////////////////////////////////////////////////////

}

winsize::~winsize()
{
    delete ui;
}

void winsize::on_PbSave_clicked()
{
//    QString vertical = ui->LeVer->text();
//    QString Horizontal = ui->LeHor->text();

//    QString ver1 = vertical.mid(0,2);
//    QString ver2 = vertical.mid(3);
//    QString hor1 = Horizontal.mid(0,2);
//    QString hor2 = Horizontal.mid(3);

    this->close();
}

