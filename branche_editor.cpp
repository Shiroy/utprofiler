#include "branche_editor.h"
#include "ui_branche_editor.h"

Branche_Editor::Branche_Editor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Branche_Editor)
{
    ui->setupUi(this);
}

Branche_Editor::~Branche_Editor()
{
    delete ui;
}
