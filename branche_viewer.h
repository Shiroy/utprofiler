#ifndef BRANCHE_VIEWER_H
#define BRANCHE_VIEWER_H

#include <QDialog>

namespace Ui {
class Branche_Viewer;
}

class Branche_Viewer : public QDialog
{
    Q_OBJECT
    
public:
    explicit Branche_Viewer(QWidget *parent = 0);
    ~Branche_Viewer();
    
private:
    Ui::Branche_Viewer *ui;
};

#endif // BRANCHE_VIEWER_H
