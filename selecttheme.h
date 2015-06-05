#ifndef SELECTTHEME_H
#define SELECTTHEME_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class SelectTheme;
}

class SelectTheme : public QDialog
{
    Q_OBJECT

public:
    explicit SelectTheme(QWidget *parent = 0);
    ~SelectTheme();

private slots:/*
    void on_buttonBox_accepted();
*/
private:
    Ui::SelectTheme *ui;

    QStringListModel *themeList;
};

#endif // SELECTTHEME_H
