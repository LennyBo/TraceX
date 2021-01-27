
#include "viewserver.h"
#include "widgetplayer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet("ViewServer, QLineEdit, QPushButton, QLabel, QComboBox, QMessageBox, QGraphicsView { background-color: rgb(20,20,20); color: lightgrey; margin: 10px; }"
                    "QPushButton { background-color: rgb(50,50,50); font-size: 28px; height: 50px ;margin : 2px; padding: 0px; }"
                    "QPushButton:hover { background-color: lightgrey; color: rgb(50,50,50); }"
                    "#h1 { font-size: 50px; text-align: center;}"
                    "#help { width : 70px; min-width : 70px; max-width : 70px; }");
    ViewServer w;
    w.show();
    return a.exec();
}
