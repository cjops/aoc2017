#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <chrono>
using namespace std;

const int MAX_PROGRAMS = 1500;
const int MAX_CHILDREN = 10;
const int MAX_LINE_LENGTH = 1000;
const int MAX_PROGRAM_LENGTH = 20;
const char FILENAME[] = "input.txt";

int parseNum(const char* s)
{
    size_t len = strlen(s);
    int num = 0;
    for (size_t i = 0; i < len; i++)
    {
        num += (s[i] - '0') * static_cast<int>(pow(10, len - 1 - i));
    }
    return num;
}

int getProgramByName(const char programs[][MAX_PROGRAM_LENGTH], const int nPrograms, const char name[])
{
    for (int i = 0; i < nPrograms; i++)
        if (strcmp(programs[i], name) == 0)
            return i;
    return -1;
}

int main()
{
    auto start = chrono::high_resolution_clock::now();

    fstream stream;
    stream.open(FILENAME);
    if (stream.fail())
    {
        cout << "Couldn't open file" << endl;
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char* token;
    const char delimiters[] = " ()->,";
    int tokenCount;
    int nPrograms = 0;
    char programs[MAX_PROGRAMS][MAX_PROGRAM_LENGTH];
    int programWeights[MAX_PROGRAMS];
    bool programHasParent[MAX_PROGRAMS];

    while (stream.getline(line, MAX_LINE_LENGTH))
    {
        programHasParent[nPrograms] = false;
        tokenCount = 0;
        token = strtok(line, delimiters);
        while (token != nullptr)
        {
            if (tokenCount == 0)
                strcpy(programs[nPrograms], token);
            else if (tokenCount == 1)
                programWeights[nPrograms] = parseNum(token);
            else
                break;

            token = strtok(nullptr, delimiters);
            tokenCount++;
        }
        nPrograms++;
    }

    stream.clear();
    stream.seekg(0, ios::beg);

    int programChildCounts[MAX_PROGRAMS];
    int programChildren[MAX_PROGRAMS][MAX_CHILDREN];
    int i = 0;

    while (stream.getline(line, MAX_LINE_LENGTH))
    {
        programChildCounts[i] = 0;
        tokenCount = 0;
        token = strtok(line, delimiters);
        while (token != nullptr)
        {
            if (tokenCount > 1)
            {
                programChildCounts[i]++;
                int childKey = getProgramByName(programs, nPrograms, token);
                programChildren[i][tokenCount - 2] = childKey;
                programHasParent[childKey] = true;
            }

            token = strtok(nullptr, delimiters);
            tokenCount++;
        }
        i++;
    }

    stream.close();

    /*for (int i = 0; i < nPrograms; i++)
    {
        cout << programs[i] << ": " << programWeights[i] << endl;
        if (programChildCounts[i] > 0)
            for (int j = 0; j < programChildCounts[i]; j++)
                cout << '\t' << programs[programChildren[i][j]] << endl;
    }*/
    cout << "Parentless:" << endl;
    for (int i = 0; i < nPrograms; i++)
        if (!programHasParent[i])
            cout << programs[i] << endl;

    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout << elapsed.count() << endl;
}