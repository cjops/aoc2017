#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

const int MAXWORDS = 20;
const int MAXWORDLEN = 20;
const int MAXLINELEN = 1000;
const char filename[] = "input.txt";

bool isAnagram(const char* word1, const char* word2)
{
    char w1[MAXWORDLEN], w2[MAXWORDLEN];
    strcpy(w1, word1);
    strcpy(w2, word2);
    int len = strlen(w1);
    if (len != strlen(w2))
        return false;
    bool match = false;
    for (int i = 0; i < len; i++)
    {
        match = false;
        for (int j = 0; j < len; j++)
        {
            if (w1[i] == w2[j])
            {
                match = true;
                w2[j] = '\0';
                break;
            }
        }
        if (!match)
            break;
    }
    return match;
}

bool isValidPhrase(char* phrase)
{
    bool validPhrase = true;
    char words[MAXWORDS][MAXWORDLEN];
    int nWords = 0;
    char* word = strtok(phrase, " ");
    while (word)
    {
        for (int i = 0; i < nWords; i++)
            if (strcmp(word, words[i]) == 0 || isAnagram(word, words[i]))
            {
                validPhrase = false;
                break;
            }
        if (validPhrase)
        {
            strcpy(words[nWords], word);
            nWords++;
        }
        else
            break;
        word = strtok(nullptr, " ");
    }
    return validPhrase;
}

int main()
{
    ifstream stream;
    stream.open(filename);
    if (stream.fail())
    {
        cout << "Couldn't open file" << endl;
        exit(1);
    }
    char l[MAXLINELEN];
    int nValidLines = 0;
    while (stream.getline(l, MAXLINELEN))
        if (isValidPhrase(l))
            nValidLines++;
    stream.close();
    cout << nValidLines << endl;
}