#ifndef ENCRYPTIONPAGE_H
#define ENCRYPTIONPAGE_H

#include <QWidget>
#include <QLabel>
#include <QStackedLayout>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QChartView>

class QVBoxLayout;
class QTextEdit;
class QPushButton;

class EncryptionPage : public QWidget
{
    Q_OBJECT

public:
    EncryptionPage(QWidget *parent = nullptr, QStackedLayout *stackedLayout = nullptr );
    void setInputText(const QString &text);

    void hideAll();
    void showAll();

    QVBoxLayout *encryptionPageLayout;
    QTextEdit *inputTextEdit;
    QTextEdit *encryptedTextEdit;
    QTextEdit* codesTextEdit;

    QPushButton *encryptButton;
    QPushButton *saveButton;
    QPushButton *showHistogramButton;
    QPushButton *closeHistogramButton;

    QLabel *label1;
    QLabel *label2;
    QLabel *labelInput;

    QPushButton *backToMainButton;

    QChartView *chartView;

private slots:
    void onEncryptButtonClicked();
    void onBackToMainButtonClicked();
    void onInputTextChanged();
    void onSaveButtonClicked();
    void onCloseButtonClicked();
    void onShowHistogramButtonClicked();

private:
    void setupUi();

    QStackedLayout *stackedLayout_;

};

#endif // ENCRYPTIONPAGE_H
