#include "encryptionpage.h"
#include "Huffman/huffmanencoder.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChart>
#include <QChartView>

EncryptionPage::EncryptionPage(QWidget *parent, QStackedLayout *stackedLayout)
    : QWidget(parent),
    encryptionPageLayout(new QVBoxLayout()),
    stackedLayout_(stackedLayout)
{
    setupUi();
}

void EncryptionPage::setupUi()
{
    inputTextEdit = new QTextEdit();
    encryptedTextEdit = new QTextEdit();
    encryptedTextEdit->setReadOnly(true);

    codesTextEdit = new QTextEdit();
    codesTextEdit->setReadOnly(true);

    QHBoxLayout hLayout;

    backToMainButton = new QPushButton("На головну");
    encryptionPageLayout->addWidget(backToMainButton);

    encryptButton = new QPushButton("Зашифрувати");

    // Создайте виджет, содержащий encryptedTextEdit и secondTextEdit
    QWidget *textEditContainer1 = new QWidget();
    QVBoxLayout *textEditContainerLayout1 = new QVBoxLayout();
    label1 = new QLabel("Зашифрований текст:");
    textEditContainerLayout1->addWidget(label1);
    textEditContainerLayout1->addWidget(encryptedTextEdit);
    textEditContainer1->setLayout(textEditContainerLayout1);

    QWidget *textEditContainer2 = new QWidget();
    QVBoxLayout *textEditContainerLayout2 = new QVBoxLayout();
    label2 = new QLabel("Таблиця кодів");
    textEditContainerLayout2->addWidget(label2);
    textEditContainerLayout2->addWidget(codesTextEdit);
    textEditContainer2->setLayout(textEditContainerLayout2);



    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->addWidget(textEditContainer1);
    horizontalLayout->addWidget(textEditContainer2); // Добавляем secondTextEdit горизонтально

    labelInput = new QLabel("Ведіть текст:");

    encryptionPageLayout->addWidget(labelInput);
    encryptionPageLayout->addWidget(inputTextEdit);
    encryptionPageLayout->addLayout(horizontalLayout);

    saveButton = new QPushButton("Зберегти");
    saveButton->hide(); // Скрываем кнопку по умолчанию
    encryptionPageLayout->addWidget(saveButton);

    showHistogramButton = new QPushButton("Показати гістограму");
    showHistogramButton->hide();
    encryptionPageLayout->addWidget(showHistogramButton);

    closeHistogramButton = new QPushButton("Закрити гістограму");
    closeHistogramButton->hide();

    encryptionPageLayout->addWidget(encryptButton);
    setLayout(encryptionPageLayout);

    connect(encryptButton, &QPushButton::clicked, this, &EncryptionPage::onEncryptButtonClicked);
    connect(backToMainButton, &QPushButton::clicked, this, &EncryptionPage::onBackToMainButtonClicked);
    connect(inputTextEdit, &QTextEdit::textChanged, this, &EncryptionPage::onInputTextChanged);
    connect(saveButton, &QPushButton::clicked, this, &EncryptionPage::onSaveButtonClicked);
    connect(showHistogramButton, &QPushButton::clicked, this, &EncryptionPage::onShowHistogramButtonClicked);
    connect(saveButton, &QPushButton::clicked, this, &EncryptionPage::onSaveButtonClicked);
    connect(closeHistogramButton, &QPushButton::clicked, this, &EncryptionPage::onCloseButtonClicked);



}

void EncryptionPage::onSaveButtonClicked()
{
    QString encryptedText = encryptedTextEdit->toPlainText();
    QString codesText = codesTextEdit->toPlainText();

    QString fileName = QFileDialog::getSaveFileName(this, "Оберіть файл із текстом", QDir::homePath(), "Текстові файли (*.txt)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);

        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);

            stream << "Зашифрований текст:\n" << encryptedText << "\n\n";
                          stream << "Таблиця кодів:\n" << codesText;

                file.close();

            // Уведомление о успешном сохранении
            QMessageBox::information(nullptr, "Успіх", "Дані було збережено у файлі");
        } else {
            QMessageBox::critical(nullptr, "Помилка", "Не вдалося відкрити файл ");
        }
    }
}


void EncryptionPage::setInputText(const QString &text)
{
    inputTextEdit->setPlainText(text);
}



void EncryptionPage::onInputTextChanged()
{

    saveButton->hide();
    showHistogramButton->hide();
    encryptButton->show();
}

void EncryptionPage::onEncryptButtonClicked()
{



    HuffmanEncoder encoder;

    QString textToEncrypt = inputTextEdit->toPlainText();

    if(!textToEncrypt.isEmpty()){
        encryptButton->hide(); // Скрываем кнопку "Шифровать"
        showHistogramButton->show();
        saveButton->show();

        int ngramSize = 2;
        encoder.buildHuffmanTree(textToEncrypt, ngramSize);

        QMap<QString, QString> huffmanCodes = encoder.generateHuffmanCodes();
        QString encryptedText = encoder.encryptText(textToEncrypt);

        encryptedTextEdit->setPlainText(encryptedText);

        QString tableText = "";
            for (auto it = huffmanCodes.begin(); it != huffmanCodes.end(); ++it) {
                tableText += it.key() + ": " + it.value() + "\n";
            }

            codesTextEdit->setPlainText(tableText);
    }
}

void EncryptionPage::onShowHistogramButtonClicked(){
    HuffmanEncoder encoder;

    QString textToEncrypt = inputTextEdit->toPlainText();

    QMap<QChar, int> frequencies = encoder.calculateCharacterFrequencies(textToEncrypt);

    // Создание гистограммы и отображение ее в QChartView
    QBarSet *set = new QBarSet("Частота символів");
    QStringList categories;

    for (auto it = frequencies.begin(); it != frequencies.end(); ++it) {
        set->append(it.value());
        categories << it.key();
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Гістограма частот символів");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartView = new QChartView();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);



    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    layout->addWidget(closeHistogramButton);

    hideAll();

    // Создайте виджет для размещения гистограммы и кнопки
    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);
    encryptionPageLayout->addWidget(widget);

    hideAll();
    chartView->show();
    closeHistogramButton->show();

}

void EncryptionPage::onCloseButtonClicked(){
        if (chartView)
        {
            chartView->close();
        closeHistogramButton->hide();
            showAll();
        }
}

void EncryptionPage::hideAll(){
        inputTextEdit->hide();
        encryptedTextEdit->hide();
        codesTextEdit->hide();
        encryptButton->hide();
        saveButton->hide();
        backToMainButton->hide();
        showHistogramButton->hide();
        label1->hide();
        label2->hide();
        labelInput->hide();
}

void EncryptionPage::showAll(){


        inputTextEdit->show();
        encryptedTextEdit->show();
        codesTextEdit->show();
        encryptButton->show();
        saveButton->show();
        backToMainButton->show();
        showHistogramButton->show();
        label1->show();
        label2->show();
        labelInput->show();
}


void EncryptionPage::onBackToMainButtonClicked()
{
    stackedLayout_->setCurrentIndex(0);
}
