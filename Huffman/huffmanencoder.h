#ifndef HUFFMANENCODER_H
#define HUFFMANENCODER_H

#include <QString>
#include <QHash>
#include <QMap>
#include <QPair>
#include <QStringList>

class HuffmanEncoder {
public:
    HuffmanEncoder();
    ~HuffmanEncoder();

    void buildHuffmanTree(const QString& text, int ngramSize);
    QMap<QString, QString> generateHuffmanCodes();
    QString encryptText(const QString& text);
    QString decryptText(const QString& encryptedText);

    QMap<QChar, int> calculateCharacterFrequencies(const QString& text) const;

private:
    struct HuffmanNode;
    struct CompareNodes;

    HuffmanNode* root;
    int ngramSize;
    QMap<QString, QString> codesMap; // Добавим отображение символов к кодам

    QHash<QChar, int> characterFrequencies;

    void clearTree(HuffmanNode* node);
    void generateHuffmanCodes(HuffmanNode* node, const QString& code);
    QStringList createNGrams(const QString& text);
};

#endif // HUFFMANENCODER_H
