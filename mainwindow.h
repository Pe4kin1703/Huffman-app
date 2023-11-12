//#ifndef MAINWINDOW_H
//#define MAINWINDOW_H

//#include "Huffman/huffmanencoder.h"



//#include <QMainWindow>
//#include <QVBoxLayout>
//#include <QWidget>
//#include <QLineEdit>
//#include <QBarSet>
//#include <QBarSeries>
//#include <QBarCategoryAxis>
//#include <QValueAxis>
//#include <QChart>
//#include <QChartView>

//QT_BEGIN_NAMESPACE
//namespace Ui { class MainWindow; }
//QT_END_NAMESPACE

//class MainWindow : public QMainWindow
//{
//    Q_OBJECT

//public:
//    MainWindow(QWidget *parent = nullptr);
//    ~MainWindow();

//private:
//    Ui::MainWindow *ui;
//    HuffmanEncoder encoder;
//private slots:
//    void onCloseButtonClicked() {
//        // Закрыть текущее окно или вернуться к предыдущему экрану,
//        // в зависимости от ваших потребностей.
//        this->close(); // Закрыть текущее окно.
//        // Или
//        // this->hide(); // Скрыть текущее окно (можно показать его снова позже).
//    }
//    void onConvertBtnCliked();

//};
//#endif // MAINWINDOW_H

#ifndef TEXTENTRYAPP_H
#define TEXTENTRYAPP_H

#include <QWidget>
#include <QStackedLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include "encryptionpage.h"
#include "infopage.h"


class QRadioButton;
class QTextEdit;
class QVBoxLayout;

class TextEntryApp : public QWidget
{
    Q_OBJECT

public:
    TextEntryApp(QWidget *parent = nullptr);

private slots:
    void onNextButtonClicked();
    void onAboutDeveloperButtonClicked();

//    void processText(const QString &text);

private:
    void setupUi(QWidget *parentWidget);
    void setCurrentPage(int page);

    EncryptionPage *encryptionPage;
    InfoPage* infoPage;

    QStackedLayout *stackedLayout;

    QVBoxLayout *mainLayout;
   // QVBoxLayout *encryptionPageLayout;
    QRadioButton *fileInputCheckBox;
    QRadioButton *manualInputCheckBox;
    QTextEdit *textEdit;

    QLabel*developerPhotoLabel;

    QPushButton * nextButton;
    QPushButton * showDevInfo;
};

#endif // TEXTENTRYAPP_H
