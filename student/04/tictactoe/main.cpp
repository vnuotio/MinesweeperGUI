#include <iostream>
#include <vector>

using namespace std;
using Board = vector<vector<char>>;

int BOARD_INITIAL_SIZE = 3;

enum BoardMarks
{
    EMPTY = '.',
    CROSS = 'X',
    NOUGHT = '0'
};

Board initBoard()
{
    /* Luo pelialueen, jonka koko on BOARD_INITIAL_SIZE * BOARD_INITIAL_SIZE,
     * ja jonka kaikki pisteet ovat tyhjiä (BoardMarks.EMPTY).
     *
     * Palauttaa tämän pelialueen muodossa vector<vector<char>>.
     * */
    Board newBoard;
    for (int i = 0; i < BOARD_INITIAL_SIZE; ++i)
    {
        vector<char> row;
        for (int j = 0; j < BOARD_INITIAL_SIZE; ++j)
        {
            row.push_back(EMPTY);
        }
        newBoard.push_back(row);
    }
    return newBoard;
}

int main()
{
    // Pelialueen luominen.
    Board board = initBoard();

    return 0;
}
