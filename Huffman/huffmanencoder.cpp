// В huffmanencoder.cpp:

#include "huffmanencoder.h"
#include <QDebug>
#include <QVector>
#include <QPair>
#include <queue>

struct HuffmanEncoder::HuffmanNode {
    QString data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(QString ngram, int freq) : data(ngram), frequency(freq), left(nullptr), right(nullptr) {}
};

struct HuffmanEncoder::CompareNodes {
    bool operator()(const HuffmanNode* lhs, const HuffmanNode* rhs) const {
        return lhs->frequency > rhs->frequency;
    }
};

HuffmanEncoder::HuffmanEncoder() : root(nullptr), ngramSize(1) {}

HuffmanEncoder::~HuffmanEncoder() {
    clearTree(root);
}

void HuffmanEncoder::buildHuffmanTree(const QString& text, int ngramSize) {
    this->ngramSize = ngramSize;

    QStringList ngrams = createNGrams(text);

    // Подсчитываем частоты нграмм
    QHash<QString, int> frequencies;
    for (QString ngram : ngrams) {
        frequencies[ngram]++;
    }

    // Создаем узлы для нграмм и помещаем их в приоритетную очередь
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> pq;
    for (auto it = frequencies.begin(); it != frequencies.end(); ++it) {
        pq.push(new HuffmanNode(it.key(), it.value()));
    }

    // Строим дерево Хаффмана
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* internalNode = new HuffmanNode("", left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        pq.push(internalNode);
    }

    root = pq.top();
    generateHuffmanCodes(root, QString());
}

QMap<QString, QString> HuffmanEncoder::generateHuffmanCodes() {
    return codesMap;
}

QString HuffmanEncoder::encryptText(const QString& text) {
    QStringList ngrams = createNGrams(text);
    QString encryptedText;

    for (QString ngram : ngrams) {
        encryptedText += codesMap[ngram];
    }

    return encryptedText;
}

QString HuffmanEncoder::decryptText(const QString& encryptedText) {
    QString decryptedText;
    QString currentCode;

    for (int i = 0; i < encryptedText.length(); ++i) {
        currentCode += encryptedText[i];

        // Проверяем, существует ли текущий код в отображении
        if (codesMap.values().contains(currentCode)) {
            QString ngram = codesMap.key(currentCode);
            decryptedText += ngram;
            currentCode.clear();
        }
    }

    return decryptedText;
}

void HuffmanEncoder::clearTree(HuffmanNode* node) {
    if (!node)
        return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

void HuffmanEncoder::generateHuffmanCodes(HuffmanNode* node, const QString& code) {
    if (!node)
        return;

    if (node->data != "") {
        codesMap[node->data] = code;
    }

    generateHuffmanCodes(node->left, code + "0");
    generateHuffmanCodes(node->right, code + "1");
}

QStringList HuffmanEncoder::createNGrams(const QString& text) {
    QStringList ngrams;
    int textLength = text.length();

    for (int i = 0; i < textLength; i += ngramSize) {
        QString ngram;
        for (int j = 0; j < ngramSize && i + j < textLength; ++j) {
            ngram += text[i + j];
        }
        ngrams.append(ngram);
    }

    return ngrams;
}

QMap<QChar, int> HuffmanEncoder::calculateCharacterFrequencies(const QString& text) const {
    QMap<QChar, int> frequencies;

    for (QChar ch : text) {
        frequencies[ch]++;
    }

    return frequencies;
}

