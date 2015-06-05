#include "selecttheme.h"
#include "ui_selecttheme.h"

SelectTheme::SelectTheme(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectTheme)
{
    ui->setupUi(this);

    /* zavrsi
    connect(this, SIGNAL(on_buttonBox_accepted()),
            (Game*)parent, SLOT(themeSelected("proba")));
    */

    // Create model
    themeList = new QStringListModel(this);

    // Make data
    QStringList List;
    List << "default" << "1" ;

    // Populate our model
    themeList->setStringList(List);

    // Glue model and view together
    ui->listView->setModel(themeList);
}

SelectTheme::~SelectTheme() { delete ui; }

/* zavrsi
void SelectTheme::on_buttonBox_accepted()
{
    QModelIndexList list = ui->listView->
            selectionModel()->selectedIndexes();

    foreach(const QModelIndex &index, list){
        selectedTheme.append( index.data(Qt::DisplayRole ).toString());
    }
}
*/
