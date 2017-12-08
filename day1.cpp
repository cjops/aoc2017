#include <iostream>
#include <cstring>
using namespace std;

const int MAXLENGTH = 10000;

int captcha(char* s)
{
    int sum = 0;
    char* p = s;
    while (*p != '\0')
    {
        if (*p == *(p+1))
            sum += *p - '0';
        if (*(p+1) == '\0' && *p == *s)
            sum += *p - '0';
        p++;
    }
    return sum;
}

int captcha2(char* s)
{
    int sum = 0;
    char* p = s;
    int halfway = strlen(s) / 2;
    while (*p != '\0')
    {
        char* q = p;
        for (int i = 0; i < halfway; i++)
        {
            if (*(q + 1) != '\0')
                q++;
            else
                q = s;
        }
        if (*p == *q)
            sum += *p - '0';
        p++;
    }
    return sum;
}

int main()
{
    for (;;)
    {
        char s[MAXLENGTH];
        cout << "Input some numbers:" << endl;
        cin.getline(s, MAXLENGTH);
        cout << "The sum is " << captcha2(s) << "." << endl << endl;
    }
}