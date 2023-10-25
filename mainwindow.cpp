#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEditInput->setPlaceholderText("ABOBA");
    ui->textEditInput->setLineWrapMode(QTextEdit::WidgetWidth);

    ui->textEditOutput->setReadOnly(true);
//    ui->lineEditInput->autoFillBackground();

    connect(ui->convertTextBtn, &QPushButton::clicked, this, &MainWindow::onConvertBtnCliked);


}

// Ваш обработчик нажатия на кнопку для открытия меню
//void MainWindow::onMenuButtonClicked() {
//    // Откройте меню в координатах кнопки
//    ui->menuButton->menu()->popup(ui->menuButton->mapToGlobal(QPoint(0, ui->menuButton->height())));
//}


void MainWindow::onConvertBtnCliked(){
    QString textToEncrypt = ui->textEditInput->toPlainText();

    // Устанавливаем размер n-грамм, например, 2 для биграмм
    int ngramSize = 1;
    encoder.buildHuffmanTree(textToEncrypt, ngramSize);

    QMap<QString, QString> huffmanCodes = encoder.generateHuffmanCodes();
    QString encryptedText = encoder.encryptText(textToEncrypt);

    ui->textEditOutput->setPlainText(encryptedText);

    // Генерируем текст для таблицы символов и их кодов
    QString tableText = "Таблица символов и их кодов:\n";
    for (auto it = huffmanCodes.begin(); it != huffmanCodes.end(); ++it) {
        tableText += it.key() + ": " + it.value() + "\n";
    }

    ui->textEditTable->setPlainText(tableText);

    QMap<QChar, int> frequencies = encoder.calculateCharacterFrequencies(textToEncrypt);

    // Создание гистограммы и отображение ее в QChartView
    QBarSet *set = new QBarSet("Частота символов");
    QStringList categories;

    for (auto it = frequencies.begin(); it != frequencies.end(); ++it) {
        set->append(it.value());
        categories << it.key();
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Гистограмма частот символов");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QPushButton *closeButton = new QPushButton("Закрыть", this);
    connect(closeButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);

    chartView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}




