#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
using namespace std;

const char FILENAME[] = "input.txt";
const int NUM_BANKS = 16;
const int MAX_DEPTH = 32000;

void getInitialConfig(short int banks[])
{
    ifstream stream;
    stream.open(FILENAME);
    if (stream.fail())
    {
        cout << "Couldn't open file" << endl;
        exit(1);
    }
    int nBanks = 0;
    int blocks;
    while (stream >> blocks)
    {
        if (nBanks > NUM_BANKS)
        {
            cout << "More banks than expected" << endl;
            exit(1);
        }
        banks[nBanks] = blocks;
        nBanks++;
    }
    stream.close();
    if (nBanks < NUM_BANKS)
    {
        cout << "Fewer banks than expected" << endl;
        exit(1);
    }
}

void recordForPosterity(const short int banks[], short int history[][NUM_BANKS], const int cycles)
{
    for (int i = 0; i < NUM_BANKS; i++)
        history[cycles][i] = banks[i];
}


void redistributeBlocks(short int banks[], short int history[][NUM_BANKS])
{
    int maxBlocks = banks[0];
    for (int i = 1; i < NUM_BANKS; i++)
        if (banks[i] > maxBlocks)
            maxBlocks = banks[i];
    int X;
    for (int i = 0; i < NUM_BANKS; i++)
        if (banks[i] == maxBlocks)
        {
            X = i;
            banks[X] = 0;
            break;
        }
    for (int blocks = maxBlocks; blocks > 0; blocks--)
    {
        X++;
        if (X == NUM_BANKS)
            X = 0;
        banks[X]++;
    }
}

bool duplicateStates(const short int history[][NUM_BANKS], const int cycles, int& diff)
{
    bool duplicate = false;
    for (int i = 0; i < cycles; i++)
    {
        duplicate = true;
        for (int j = 0; j < NUM_BANKS; j++)
        {
            if (history[cycles][j] != history[i][j])
            {
                duplicate = false;
                break;
            }
        }
        if (duplicate)
        {
            diff = cycles - i;
            break;
        }
    }
    return duplicate;
}

int main()
{
    short int banks[NUM_BANKS];
    int cycles = 0;
    short int history[MAX_DEPTH][NUM_BANKS];
    int diff;

    getInitialConfig(banks);
    auto start = chrono::high_resolution_clock::now();
    recordForPosterity(banks, history, cycles);

    while (!duplicateStates(history, cycles, diff))
    {
        redistributeBlocks(banks, history);
        cycles++;
        recordForPosterity(banks, history, cycles);
    }

    auto finish = chrono::high_resolution_clock::now();
    cout << cycles << endl;
    cout << diff << endl;
    chrono::duration<double> elapsed = finish - start;
    cout << elapsed.count() << endl;
    for (int j = 0; j < NUM_BANKS; j++)
        cout << history[cycles][j] << ' ';
    cout << endl;
}