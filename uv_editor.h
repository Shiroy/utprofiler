#ifndef UV_EDITOR_H
#define UV_EDITOR_H

#include <QDialog>

namespace Ui {
class UV_Editor;
}

class UV_Editor : public QDialog
{
    Q_OBJECT
    
public:
    explicit UV_Editor(QWidget *parent = 0);
    ~UV_Editor();
    
private:
    Ui::UV_Editor *ui;
};

#endif // UV_EDITOR_H
