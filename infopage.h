// infopage.h
#ifndef DEVELOPERPAGE_H
#define DEVELOPERPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedLayout>

class InfoPage : public QWidget
{
    Q_OBJECT

public:
    explicit InfoPage(QWidget *parent = nullptr);
    InfoPage(QWidget *parent = nullptr, QStackedLayout *stackedLayout = nullptr );


private slots:
    void onMainPageButton();

private:
    QStackedLayout *stackedLayout_;

         // Здесь вы можете добавить виджеты, текст и изображение для страницы разработчика.
};

#endif // DEVELOPERPAGE_H
