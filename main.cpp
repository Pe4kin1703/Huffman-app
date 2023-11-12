//#include "mainwindow.h"

//#include <QApplication>


//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//}


#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Это стилизация, которая может быть добавлена в начало вашего main.cpp файла
    // или в конструктор вашего главного окна.

    // Устанавливаем стиль для всего приложения
    app.setStyleSheet(R"(
    QWidget {
        font-family: 'Roboto', 'Arial', sans-serif;
        font-size: 14px;
    }


    QPushButton {
        color: #333;
        background-color: #EEE;
        border: 1px solid #CCC;
        padding: 5px 10px;
        border-radius: 2px;
    }

    QPushButton:hover {
        border-color: #AAA;
        background-color: #DDD;
    }

    QPushButton:pressed {
        background-color: #CCC;
    }

    QLabel {
        color: #555;
    }

    QTextEdit {
        background-color: #FFF;
        border: 1px solid #DDD;
        padding: 5px;
    }

    QRadioButton {
        spacing: 5px;
    }

    QRadioButton::indicator {
        width: 13px;
        height: 13px;
    }

    QRadioButton::indicator:checked {
        background-color: #5CACEE;
    }

    QRadioButton::indicator:unchecked {
        background-color: #FFF;
    }

    QStackedLayout {
        background-color: #F5F5F5;
    }
)");


    TextEntryApp textEntryApp;
    textEntryApp.show();

    return app.exec();
}

