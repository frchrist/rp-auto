#ifndef APPALGORITHMS_H
#define APPALGORITHMS_H
#include <QString>
class AppAlgorithms
{
public:
    AppAlgorithms() = delete;
    static int levenshteinDistance(const QString& word1, const QString& word2);

};

#endif // APPALGORITHMS_H
