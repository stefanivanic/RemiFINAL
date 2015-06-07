#ifndef INITWINDOW_H
#define INITWINDOW_H

#include <QDialog>

namespace Ui {
class InitWindow;
}

class InitWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InitWindow(QWidget *parent = 0);
    ~InitWindow();

private:
    Ui::InitWindow *ui;
};

#endif // INITWINDOW_H
