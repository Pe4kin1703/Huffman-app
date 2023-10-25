#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Huffman/huffmanencoder.h"



#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChart>
#include <QChartView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    HuffmanEncoder encoder;
private slots:
    void onCloseButtonClicked() {
        // Закрыть текущее окно или вернуться к предыдущему экрану,
        // в зависимости от ваших потребностей.
        this->close(); // Закрыть текущее окно.
        // Или
        // this->hide(); // Скрыть текущее окно (можно показать его снова позже).
    }
    void onConvertBtnCliked();

};
#endif // MAINWINDOW_H
