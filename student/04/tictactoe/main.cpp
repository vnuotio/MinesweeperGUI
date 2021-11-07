#include <iostream>
#include <vector>
#include <algorithm>

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

void printBoard(Board board)
{
    /* Tulostaa laudan konsoliin.
     * Parametrit:
     *  <Board> board, pelilauta. Board on muotoa vector<vector<char>>.
     * */

    Board::size_type boardSize = board.size();

    // Ylärivi (sarakkeen numerointi)
    cout << " ";
    for (Board::size_type i=1; i <= boardSize; ++i)
    {
        cout << " " << i % 10;
    }
    cout << endl;

    // Laudan rivit
    for (Board::size_type i=0; i < boardSize; ++i)
    {
        cout << (i+1) % 10;
        for (Board::size_type j=0; j < boardSize; ++j)
        {
            cout << " " << board.at(i).at(j);
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    // Pelialueen luominen.
    Board board = initBoard();

    printBoard(board);
    return 0;
}
