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

void printBoard(const Board& board)
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

bool isNumeric(const string& str)
{
    return (all_of(str.begin(), str.end(), ::isdigit));
}

void expandBoard(bool bExpandRight, Board& board)
{

}

bool takeInput(BoardMarks in_turn, Board& board)
{
    Board::size_type boardSize = board.size();
    bool bInvalidInput = true;
    string x;
    string y;

    while (bInvalidInput)
    {
        cout << "For " << (char)in_turn <<", enter coordinates: x y> ";
        cin >> x;

        // Quit-komento
        if (x == "q" or x == "Q")
        {
            cout << "Why on earth you are giving up the game?" << endl;
            return true;
        }

        cin >> y;

        // Tyhjentää cin-bufferin, jolloin käyttäjän syöttämät ylimääräiset
        // tiedot eivät jää häiritsemään myöhempiä suorituskertoja.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Testaa, voiko syötteen muuntaa numeroiksi
        if (not isNumeric(x) or not isNumeric(y))
        {
            cout << "Coordinate outside the board" << endl;
            continue;
        }

        Board::size_type xInt = stoi(x);
        Board::size_type yInt = stoi(y);

        // Enemmän kuin 1 yli laitojen
        if (xInt < 0 or yInt < 0 or xInt > boardSize+1 or yInt > boardSize+1)
        {
            cout << "Coordinate outside the board" << endl;
            continue;
        }
        // Sekä yli että ali samaan aikaan
        else if ((xInt == 0 and yInt == boardSize+1) or (xInt == boardSize+1 and yInt == 0))
        {
            cout << "Coordinate outside the board" << endl;
            continue;
        }
    }
    return false;
}

int main()
{
    // Pelialueen luominen.
    Board board = initBoard();

    bool bGameOver = false;
    BoardMarks in_turn;
    int turn = 0;

    cout << "Start game:" << endl;

    while (not bGameOver)
    {
        if (turn % 2 == 0)
        {
            in_turn = CROSS;
        }
        else
        {
            in_turn = NOUGHT;
        }

        printBoard(board);
        bGameOver = takeInput(in_turn, board);
        ++turn;
    }
    return EXIT_SUCCESS;
}
