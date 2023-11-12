// infopage.cpp
#include "infopage.h"

InfoPage::InfoPage(QWidget *parent, QStackedLayout *stackedLayout) : QWidget(parent)
                                                                     , stackedLayout_(stackedLayout)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton * mainPageButton = new QPushButton("На головну");

    QLabel *infoLabel = new QLabel("Інформація про розробника");
    QLabel *developerNameLabel = new QLabel("Ім'я: Спіцин Данило");
    QLabel *developerEmailLabel = new QLabel("Email: example@example.com");


    QPixmap developerImage(":/image.jpeg");

    int desiredWidth = 300;
    int desiredHeight = 200;

    QPixmap scaledDeveloperImage = developerImage.scaled(desiredWidth, desiredHeight, Qt::KeepAspectRatio);


    QLabel *developerImageLabel = new QLabel();
    developerImageLabel->setPixmap(scaledDeveloperImage);

    layout->addWidget(mainPageButton);
    layout->addWidget(infoLabel);
    layout->addWidget(developerImageLabel);
    layout->addWidget(developerNameLabel);
    layout->addWidget(developerEmailLabel);

    connect(mainPageButton, &QPushButton::clicked, this, &InfoPage::onMainPageButton);

    setLayout(layout);
}

void InfoPage::onMainPageButton(){
    stackedLayout_->setCurrentIndex(0);
}
