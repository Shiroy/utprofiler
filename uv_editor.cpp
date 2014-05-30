#include "uv_editor.h"
#include "ui_uv_editor.h"

UV_Editor::UV_Editor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UV_Editor)
{
    ui->setupUi(this);
}

UV_Editor::~UV_Editor()
{
    delete ui;
}
