#ifndef BRANCHE_EDITOR_H
#define BRANCHE_EDITOR_H

#include <QDialog>

namespace Ui {
class Branche_Editor;
}

class Branche_Editor : public QDialog
{
    Q_OBJECT
    
public:
    explicit Branche_Editor(QWidget *parent = 0);
    ~Branche_Editor();
    
private:
    Ui::Branche_Editor *ui;
};

#endif // BRANCHE_EDITOR_H
