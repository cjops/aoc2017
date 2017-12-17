#include <iostream>
#include <cmath>
using namespace std;

const int MAXSQUARES = 1000000;

struct Square
{
    int x;
    int y;
    int key;
    int value;
    Square(int x_, int y_, int key_, int value_);
};

Square::Square(int x_, int y_, int key_, int value_ = 0)
{
    x = x_;
    y = y_;
    key = key_;
    value = value_;
}

class Spiral
{
public:
    Spiral(int nSquares);
    ~Spiral();
    void addSquares(int nSquares);
    Square* square(int key);
    void display();
private:
    Square* m_spiral[MAXSQUARES];
    int m_nSquares;
    int m_radius;
    bool existsSquare(int x, int y);
    bool withinBounds(int x, int y);
};

Spiral::Spiral(int nSquares = 0)
{
    m_nSquares = 0;
    m_radius = 0;
    addSquares(nSquares);
}

Spiral::~Spiral()
{
    for (int i = 0; i < m_nSquares; i++)
        delete m_spiral[i];
}

bool Spiral::existsSquare(int x, int y)
{
    for (int i = 0; i < m_nSquares; i++)
        if (m_spiral[i]->x == x && m_spiral[i]->y == y)
            return true;
    return false;
}

bool Spiral::withinBounds(int x, int y)
{
    return abs(x) <= m_radius && abs(y) <= m_radius;
}

Square* Spiral::square(int key)
{
    for (int i = 0; i < m_nSquares; i++)
        if (m_spiral[i]->key == key)
            return m_spiral[i];
    return nullptr;
}

void Spiral::addSquares(int nSquares)
{
    int wantedSquares = m_nSquares + nSquares;
    while (m_nSquares < wantedSquares)
    {
        if (m_nSquares == 0)
        {
            m_spiral[0] = new Square(0, 0, 1);
            m_nSquares++;
            m_radius = 1;
            continue;
        }

        int X = m_spiral[m_nSquares - 1]->x;
        int Y = m_spiral[m_nSquares - 1]->y;
        int K = m_spiral[m_nSquares - 1]->key;
        
        // counter-clockwise spiral

        if (!existsSquare(X + 1, Y) && withinBounds(X + 1, Y))
        {
            m_spiral[m_nSquares] = new Square(X + 1, Y, K + 1);
            m_nSquares++;
            continue;
        }
        else if (!existsSquare(X, Y + 1) && withinBounds(X, Y + 1))
        {
            m_spiral[m_nSquares] = new Square(X, Y + 1, K + 1);
            m_nSquares++;
            continue;
        }
        else if (!existsSquare(X - 1, Y) && withinBounds(X - 1, Y))
        {
            m_spiral[m_nSquares] = new Square(X - 1, Y, K + 1);
            m_nSquares++;
            continue;
        }
        else if (!existsSquare(X, Y - 1) && withinBounds(X, Y - 1))
        {
            m_spiral[m_nSquares] = new Square(X, Y - 1, K + 1);
            m_nSquares++;
            continue;
        }
        else if (!existsSquare(X + 1, Y))
        {
            m_radius++;
            m_spiral[m_nSquares] = new Square(X + 1, Y, K + 1);
            m_nSquares++;
            continue;
        }
        
    }
}

// todo: rewrite without storing objects and by only keeping track of the last move

void Spiral::display()
{
    for (int i = 0; i < m_nSquares; i++)
    {
        cout << "[" << m_spiral[i]->x << ", " << m_spiral[i]->y << "] " << m_spiral[i]->key << endl;
    }
}

int main()
{
    Spiral* sp = new Spiral(500);
    sp->display();

}