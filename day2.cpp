#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <climits>
#include <fstream>
#include <cstring>
#include <cctype>
#include <cmath>
using namespace std;

const int MAXROWS = 100;
const int MAXCOLS = 100;
const int MAXLINELEN = 10000;
const int MAXNUMLEN = 10;

int parseNum(const char* c, int len)
{
    int num = 0;
    for (int i = 0; i < len; i++)
    {
        num += (c[i] - '0') * pow(10, len - 1 - i);
    }
    return num;
}

int checksum(const int spreadsheet[][MAXCOLS], int nRows)
{
    int checksum = 0;
    for (int i = 0; i < nRows; i++)
    {
        int min = spreadsheet[i][0]; // no empty rows plz
        int max = spreadsheet[i][0];
        for (int k = 1; spreadsheet[i][k] != -1; k++)
        {
            if (spreadsheet[i][k] > max)
                max = spreadsheet[i][k];
            if (spreadsheet[i][k] < min)
                min = spreadsheet[i][k];
        }
        checksum += (max - min);
    }
    return checksum;
}

int divSum(const int spreadsheet[][MAXCOLS], int nRows)
{
    int sum = 0;

    // for each row
    for (int i = 0; i < nRows; i++)
    {
        // for each number
        for (int j = 0; spreadsheet[i][j] != -1; j++)
        {
            int div = 0;

            // numbers before
            for (int k = 0; k < j; k++)
            {
                if (spreadsheet[i][j] % spreadsheet[i][k] == 0)
                {
                    div = spreadsheet[i][j] / spreadsheet[i][k];
                    break;
                }
            }

            // numbers after
            for (int k = j + 1; div == 0 && spreadsheet[i][k] != -1; k++)
            {
                if (spreadsheet[i][j] % spreadsheet[i][k] == 0)
                {
                    div = spreadsheet[i][j] / spreadsheet[i][k];
                    break;
                }
            }

            if (div)
            {
                sum += div;
                break;
            }
        }
    }
    return sum;
}

int getSpreadsheet(int spreadsheet[][MAXCOLS], const char filename[])
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Cannot open " << filename << "!" << endl;
        return -1;
    }
    char line[MAXLINELEN];
    int nRows = 0;
    while (file.getline(line, MAXLINELEN))
    {
        int nCols = 0;
        int numLength = 0;
        for (int i = 0; ; i++)
        {
            if (isdigit(line[i]))
                numLength++;
            if (isspace(line[i]) || line[i] == '\0')
            {
                if (numLength > 0 && numLength < MAXNUMLEN)
                {
                    char c[MAXNUMLEN];
                    strncpy(c, &line[i - numLength], numLength);
                    c[numLength] = '\0';
                    spreadsheet[nRows][nCols] = parseNum(c, numLength);
                    nCols++;
                }
                numLength = 0;
                if (line[i] == '\0')
                {
                    spreadsheet[nRows][nCols] = -1;
                    nRows++;
                    break;
                }
            }
            
        }
    }
    return nRows;
}

int main()
{
    int spreadsheet[MAXROWS][MAXCOLS];
    char filename[] = "input.txt";
    int nRows = getSpreadsheet(spreadsheet, filename);
    cout << checksum(spreadsheet, nRows) << endl;
    cout << divSum(spreadsheet, nRows) << endl;
}