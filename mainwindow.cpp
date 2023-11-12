#include "mainwindow.h"

#include <QVBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QStackedLayout>

#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QMessageBox>

TextEntryApp::TextEntryApp(QWidget *parent)
    : QWidget(parent), stackedLayout(new QStackedLayout(this))
{
    QWidget *startPage = new QWidget;
    setupUi(startPage);
    stackedLayout->addWidget(startPage);

    encryptionPage = new EncryptionPage(this, stackedLayout);
    stackedLayout->addWidget(encryptionPage);

    infoPage = new InfoPage(this, stackedLayout);
    stackedLayout->addWidget(infoPage);

    setLayout(stackedLayout);
    setWindowTitle("Huffman app");
}

void TextEntryApp::setupUi(QWidget *parentWidget)
{
    QVBoxLayout *layout = new QVBoxLayout(parentWidget); // используем переданный виджет

    showDevInfo = new QPushButton("Інформація про розробника");

    QLabel *instructionLabel = new QLabel("Оберіть спосіб вводу текста:");
    fileInputCheckBox = new QRadioButton("Із файла");
    manualInputCheckBox = new QRadioButton("Ручками");

    layout->addWidget(showDevInfo);

    QButtonGroup *buttonGroup = new QButtonGroup(this);


    nextButton = new QPushButton("Далі");

    layout->addWidget(instructionLabel);
    QHBoxLayout *checkboxLayout = new QHBoxLayout;
    checkboxLayout->addWidget(fileInputCheckBox);
    checkboxLayout->addWidget(manualInputCheckBox);
    layout->addLayout(checkboxLayout);
    layout->addWidget(nextButton);

    developerPhotoLabel = new QLabel();
    layout->addWidget(developerPhotoLabel);

    connect(nextButton, &QPushButton::clicked, this, &TextEntryApp::onNextButtonClicked);
    connect(showDevInfo, &QPushButton::clicked, this, &TextEntryApp::onAboutDeveloperButtonClicked);

}

void TextEntryApp::onAboutDeveloperButtonClicked() {

    stackedLayout->setCurrentIndex(2);
}


void TextEntryApp::onNextButtonClicked()
{
    qDebug() << __FUNCTION__ << ": Called manualInputCheckBox->isChecked(): " << manualInputCheckBox->isChecked() << " stackedLayout->count(): " << stackedLayout->count();

    if (manualInputCheckBox->isChecked()) {
        stackedLayout->setCurrentIndex(1); // устанавливаем индекс страницы шифрования
    }
    else if (fileInputCheckBox->isChecked()) {
        QString fileName = QFileDialog::getOpenFileName(this, "Оберіть файл із текстом", QDir::homePath(), "Текстовий файл (*.txt)");

        if (!fileName.isEmpty()) {
            QFile file(fileName);

            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                QString fileText = in.readAll();
                file.close();

                // Передайте считанный текст на страницу шифрования (encryptionPage)
                encryptionPage->setInputText(fileText);
                encryptionPage->saveButton->hide();
                encryptionPage->encryptButton->show();

                stackedLayout->setCurrentIndex(1); // устанавливаем индекс страницы шифрования
            } else {
                QMessageBox::critical(this, "Помилка", "Не вдалося відкритий обраний файл");
            }
        }
    }
    // TODO: Handle the file input case
}

