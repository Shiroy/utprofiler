#include "branche_viewer.h"
#include "ui_branche_viewer.h"

Branche_Viewer::Branche_Viewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Branche_Viewer)
{
    ui->setupUi(this);
}

Branche_Viewer::~Branche_Viewer()
{
    delete ui;
}
