#include <iostream>
#include <cmath>
using namespace std;

const int MAX_SQUARES = 1000;

void getSpiralCoords(const int& n, int& x, int& y)
{
    int N = 1;
    //cout << "N=" << N << " [" << x << ", " << y << "]" << endl;

    // counter-clockwise spiral
    while (N < n)
    {
        if (abs(x) <= abs(y) && !(x == -y && x < 0)) // moving horizontally
        {
            if (y > 0) // upper
                x--;
            else // lower
                x++;
        }
        else // moving vertically
        {
            if (x > 0) // right
                y++;
            else // left
                y--;
        }
        N++;
        //cout << "N=" << N << " [" << x << ", " << y << "]" << endl;
    }
}

int dist(int x, int y)
{
    return abs(x) + abs(y);
}

struct Square
{
    int x;
    int y;
    int value;
};

class Spiral
{
public:
    Spiral();
    ~Spiral();
    int addSquare();
    void display();
private:
    Square* squares[MAX_SQUARES];
    int nSquares;
    int lastX;
    int lastY;
    int sumAdjacentSquares(const int& x, const int& y);
};

Spiral::Spiral()
{
    nSquares = 1;
    lastX = 0;
    lastY = 0;
    squares[0] = new Square;
    squares[0]->x = 0;
    squares[0]->y = 0;
    squares[0]->value = 1;
}

Spiral::~Spiral()
{
    for (int i = 0; i < nSquares; i++)
        delete squares[i];
}

int Spiral::sumAdjacentSquares(const int& x, const int& y)
{
    int sum = 0;
    for (int i = 0; i < nSquares; i++)
    {
        int X = squares[i]->x;
        int Y = squares[i]->y;
        if ((x + 1 == X && y == Y)
            || (x + 1 == X && y + 1 == Y)
            || (x == X && y + 1 == Y)
            || (x - 1 == X && y + 1 == Y)
            || (x - 1 == X && y == Y)
            || (x - 1 == X && y - 1 == Y)
            || (x == X && y - 1 == Y)
            || (x + 1 == X && y - 1 == Y))
        {
            sum += squares[i]->value;
        }
    }
    return sum;
}

int Spiral::addSquare()
{
    getSpiralCoords(2, lastX, lastY);
    squares[nSquares] = new Square;
    squares[nSquares]->x = lastX;
    squares[nSquares]->y = lastY;
    squares[nSquares]->value = sumAdjacentSquares(lastX, lastY);
    nSquares++;
    return squares[nSquares - 1]->value;
}

void Spiral::display()
{
    for (int i = 0; i < nSquares; i++)
        cout << "n=" << i << " [" << squares[i]->x << ", " << squares[i]->y << "]" << endl;
}

int main()
{
    int n = 265149;
    int x = 0, y = 0;
    getSpiralCoords(n, x, y);
    cout << "n=" << n << " [" << x << ", " << y << "]" << endl;
    cout << "Taxicab distance: " << dist(x, y) << endl;

    Spiral sp;
    int value = 0;
    while (value < n)
        value = sp.addSquare();
    cout << value << endl;
}