#include "appalgorithms.h"


int AppAlgorithms::levenshteinDistance(const QString &word1, const QString &word2)
{
    int size1 = word1.size();
    int size2 = word2.size();

    if (size1 == 0)
        return size2;
    if (size2 == 0)
        return size1;

    // Toujours utiliser la plus petite chaîne en colonne pour minimiser la mémoire
    if (size1 < size2)
        return levenshteinDistance(word2, word1);

    std::vector<int> previous(size2 + 1);
    std::vector<int> current(size2 + 1);

    // Remplir la première ligne
    for (int j = 0; j <= size2; j++)
        previous[j] = j;

    for (int i = 1; i <= size1; i++) {
        current[0] = i;
        for (int j = 1; j <= size2; j++) {
            int cost = (word1[i - 1] == word2[j - 1]) ? 0 : 1;
            current[j] = std::min({
                previous[j] + 1,     // suppression
                current[j - 1] + 1,  // insertion
                previous[j - 1] + cost // substitution
            });
        }
        std::swap(previous, current);
    }

    return previous[size2];
}
