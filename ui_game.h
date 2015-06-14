/********************************************************************************
** Form generated from reading UI file 'game.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_H
#define UI_GAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Game
{
public:
    QAction *menuBarRestartGame;
    QAction *actionSelect_theme;
    QAction *actionChoose_cards;
    QWidget *centralWidget;
    QLabel *label;
    QLabel *onMoveLabel;
    QPushButton *throwGroup;
    QLabel *errorLogger;
    QLabel *groupValue;
    QPushButton *undoGroup;
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QLabel *player_2;
    QPushButton *undoTookTalonCard;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Game)
    {
        if (Game->objectName().isEmpty())
            Game->setObjectName(QStringLiteral("Game"));
        Game->resize(1000, 600);
        Game->setStyleSheet(QLatin1String("Game #centralWidget{\n"
"	border-image: url(\"./slike/Teme/2_background.jpg\");\n"
"}"));
        menuBarRestartGame = new QAction(Game);
        menuBarRestartGame->setObjectName(QStringLiteral("menuBarRestartGame"));
        actionSelect_theme = new QAction(Game);
        actionSelect_theme->setObjectName(QStringLiteral("actionSelect_theme"));
        actionChoose_cards = new QAction(Game);
        actionChoose_cards->setObjectName(QStringLiteral("actionChoose_cards"));
        centralWidget = new QWidget(Game);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(740, 20, 201, 21));
        label->setStyleSheet(QLatin1String("#label {\n"
"\n"
"}"));
        onMoveLabel = new QLabel(centralWidget);
        onMoveLabel->setObjectName(QStringLiteral("onMoveLabel"));
        onMoveLabel->setGeometry(QRect(740, 50, 201, 21));
        onMoveLabel->setStyleSheet(QLatin1String("#onMoveLabel {\n"
"	border: 1px solid black;\n"
"	border-image: url(\"./slike/Teme/2_chat.jpg\");\n"
"}"));
        throwGroup = new QPushButton(centralWidget);
        throwGroup->setObjectName(QStringLiteral("throwGroup"));
        throwGroup->setGeometry(QRect(740, 420, 201, 41));
        throwGroup->setStyleSheet(QLatin1String("#throwGroup {\n"
"	border: 1px solid back;\n"
"	border-image: url(\"./slike/Teme/2_izbacigrupu.jpg\");\n"
"}"));
        throwGroup->setAutoDefault(false);
        throwGroup->setDefault(false);
        throwGroup->setFlat(false);
        errorLogger = new QLabel(centralWidget);
        errorLogger->setObjectName(QStringLiteral("errorLogger"));
        errorLogger->setGeometry(QRect(740, 80, 201, 21));
        errorLogger->setStyleSheet(QLatin1String("#errorLogger {\n"
"	border: 1px solid black;\n"
"	border-image: url(\"./slike/Teme/2_chat.jpg\");\n"
"}"));
        groupValue = new QLabel(centralWidget);
        groupValue->setObjectName(QStringLiteral("groupValue"));
        groupValue->setGeometry(QRect(740, 110, 201, 21));
        groupValue->setStyleSheet(QLatin1String("#groupValue {\n"
"	border: 1px solid black;\n"
"	border-image: url(\"./slike/Teme/2_chat.jpg\");\n"
"}\n"
""));
        undoGroup = new QPushButton(centralWidget);
        undoGroup->setObjectName(QStringLiteral("undoGroup"));
        undoGroup->setGeometry(QRect(740, 480, 201, 41));
        undoGroup->setStyleSheet(QLatin1String("#undoGroup {\n"
"	border: 1px solid back;\n"
"	border-image: url(\"./slike/Teme/2_vratigrupu.jpg\");\n"
"}"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setEnabled(false);
        textEdit->setGeometry(QRect(760, 210, 161, 111));
        QFont font;
        font.setFamily(QStringLiteral("Century Schoolbook"));
        font.setPointSize(10);
        font.setItalic(true);
        textEdit->setFont(font);
        textEdit->setStyleSheet(QLatin1String("#textEdit{\n"
"	border: 1px solid black;\n"
"	border-image: url(\"./slike/Teme/2_chat.jpg\")\n"
"}"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(780, 330, 121, 21));
        lineEdit->setFont(font);
        lineEdit->setStyleSheet(QLatin1String("#lineEdit{\n"
"\n"
"}"));
        player_2 = new QLabel(centralWidget);
        player_2->setObjectName(QStringLiteral("player_2"));
        player_2->setGeometry(QRect(310, 40, 311, 101));
        player_2->setStyleSheet(QLatin1String("#player_2 {\n"
"	border: 1px solid black;\n"
"	border-image: url(\"./slike/Teme/2_back_player2.jpg\");\n"
"}"));
        undoTookTalonCard = new QPushButton(centralWidget);
        undoTookTalonCard->setObjectName(QStringLiteral("undoTookTalonCard"));
        undoTookTalonCard->setGeometry(QRect(10, 470, 201, 41));
        undoTookTalonCard->setStyleSheet(QLatin1String("#throwGroup {\n"
"	border: 1px solid back;\n"
"	border-image: url(\"./slike/Teme/2_izbacigrupu.jpg\");\n"
"}"));
        undoTookTalonCard->setAutoDefault(false);
        undoTookTalonCard->setDefault(false);
        undoTookTalonCard->setFlat(false);
        Game->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Game);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 20));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        Game->setMenuBar(menuBar);
        statusBar = new QStatusBar(Game);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Game->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(menuBarRestartGame);
        menuFile->addAction(actionChoose_cards);

        retranslateUi(Game);

        QMetaObject::connectSlotsByName(Game);
    } // setupUi

    void retranslateUi(QMainWindow *Game)
    {
        Game->setWindowTitle(QApplication::translate("Game", "Remi", 0));
        menuBarRestartGame->setText(QApplication::translate("Game", "Restart game", 0));
        actionSelect_theme->setText(QApplication::translate("Game", "Select theme", 0));
        actionChoose_cards->setText(QApplication::translate("Game", "Choose cards", 0));
        label->setText(QApplication::translate("Game", "   Player1 : tempCardPosition : ", 0));
        onMoveLabel->setText(QApplication::translate("Game", "   Na potezu: Player 1", 0));
        throwGroup->setText(QString());
        errorLogger->setText(QApplication::translate("Game", "   errorLogger", 0));
        groupValue->setText(QApplication::translate("Game", "   Vrednost grupe: 0", 0));
        undoGroup->setText(QString());
        player_2->setText(QString());
        undoTookTalonCard->setText(QApplication::translate("Game", "vrati kartu sa talona", 0));
        menuFile->setTitle(QApplication::translate("Game", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class Game: public Ui_Game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_H
