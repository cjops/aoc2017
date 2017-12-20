#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

const char FILENAME[] = "input.txt";
const int MAX_INSTRUCTIONS = 1000;

int main()
{
    ifstream stream;
    stream.open(FILENAME);
    if (stream.fail())
    {
        cout << "Couldn't open file" << endl;
        exit(1);
    }
    int instructions[MAX_INSTRUCTIONS];
    int nInstructions = 0;
    int i;
    while (stream >> i)
    {
        if (nInstructions <= MAX_INSTRUCTIONS)
            instructions[nInstructions] = i;
        nInstructions++;
    }
    stream.close();

    int steps = 0;
    int n = 0;
    while (n < nInstructions)
    {
        int oldN = n;
        n += instructions[n];
        if (instructions[oldN] >= 3)
            instructions[oldN]--;
        else
            instructions[oldN]++;
        steps++;
    }
    cout << steps << endl;
}