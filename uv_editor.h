#ifndef UV_EDITOR_H
#define UV_EDITOR_H

#include <QDialog>
#include "uv.h"

namespace Ui {
class UV_Editor;
}

class UV_Editor : public QDialog
{
    Q_OBJECT
    
public:
    explicit UV_Editor(QWidget *parent = 0);
    UV_Editor(UV* ptUV);

    ~UV_Editor();

public slots :
    void on_buttonBox_accepted();
    
private:
    Ui::UV_Editor *ui;
};

#endif // UV_EDITOR_H
