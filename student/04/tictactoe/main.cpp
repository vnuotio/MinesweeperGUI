#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using Board = vector<vector<char>>;

int BOARD_INITIAL_SIZE = 3;

enum BoardMark
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
    for (size_t i=1; i <= boardSize; ++i)
    {
        cout << " " << i % 10;
    }
    cout << endl;

    // Laudan rivit
    for (size_t i=0; i < boardSize; ++i)
    {
        cout << (i+1) % 10;
        for (size_t j=0; j < boardSize; ++j)
        {
            cout << " " << board.at(i).at(j);
        }
        cout << endl;
    }
    cout << endl;
}

bool isPosNum(const string& str)
{
    // Tarkistaa, voiko syötteen muuntaa positiiviseksi kokonaisluvuksi.
    return (all_of(str.begin(), str.end(), ::isdigit));
}

void expandBoard(bool bExpandRight, Board& board)
{
    /* Laajentaa lautaa joko alaoikealle tai ylävasemmalle.
     * Muokkaa alkuperäistä lautaa, muttei palauta sitä.
     *
     * Parametrit:
     *  <bool> bExpandRight - laajennetaanko lautaa alaoikealle:
     *      true tarkoittaa kyllä, falsella laajennetaan ylävasemmalle.
     *  <Board> board - viite alkuperäiseen lautaan, jotta sitä voidaan muokata.
     **/

    // Laajentaa oikealle ja alas
    if (bExpandRight)
    {
        for (vector<char>& row : board)
        {
            row.push_back(EMPTY);
        }

        vector<char> newRow;
        for (size_t i=0; i < board.front().size(); ++i)
        {
            newRow.push_back(EMPTY);
        }
        board.push_back(newRow);
    }
    // Laajentaa vasemmalle ja ylös
    else
    {
        Board newBoard;
        // Luo uuden laudan, joka on yhden vanhaa suurempi x- ja y-suunnissa
        for (size_t i=0; i < board.size() + 1; ++i)
        {
            vector<char> newRow;
            for (size_t j=0; j < board.size() + 1; ++j)
            {
                newRow.push_back(EMPTY);
            }
            newBoard.push_back(newRow);
        }

        // Kopioi vanhan laudan uuteen.
        for (size_t row=0; row < board.size(); ++row)
        {
            for (size_t col=0; col < board.size(); ++col)
            {
                newBoard.at(row+1).at(col+1) = board.at(row).at(col);
            }
        }
        board = newBoard;
    }
}

void printGameOver(char mark=EMPTY, string dir="");

bool checkVictory(const Board& board);

bool takeInput(BoardMark in_turn, Board& board)
{
    /* Lukee ja tutkii käyttäjän syötettä niin kauan, kunnes vastaan tulee
     * poistumiskomento "q"/"Q" tai käypä koordinaatti. Koordinaatista tutkitaan
     * myös, onko se jo varattu tai laudan ulkopuolella. Lautaa laajennetaan
     * tarvittaessa, ja kaiken tämän jälkeen koordinaatteihin merkitään vuorossa
     * oleva merkki.
     *
     * Parametrit:
     *  <BoardMark> in_turn - merkki, joka on vuorossa. Muotoa CROSS tai NOUGHT.
     *  <Board> board - pelilaudan viite. Lautaa muokataan, joten vakioviite ei riitä.
     **/

    // board.size() + 1, sillä käyttäjälle näkyy 1...n, eikä 0...(n-1) paikkaa
    size_t boardSize = board.size() + 1;
    bool bInvalidInput = true;

    // Kerättävät syötteet.
    string x;
    string y;

    // Syötteet muutettuna size_t- tyyppiin. Syötteitä tarvitaan alla olevan while-loopin
    // ulkopuolella, joten muuttujat pitää luoda jo nyt.
    size_t xInt;
    size_t yInt;

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

        // Testaa, voiko syötteen muuntaa positiivisiksi numeroiksi
        if (not isPosNum(x) or not isPosNum(y))
        {
            cout << "Coordinate outside the board" << endl;
            continue;
        }

        // Muuntaa syötteen luvuksi.
        xInt = stoull(x);
        yInt = stoull(y);

        // Enemmän kuin 1 yli laitojen
        if (xInt > boardSize or yInt > boardSize)
        {
            cout << "Coordinate outside the board" << endl;
            continue;
        }

        // Sekä yli että ali samaan aikaan
        if ((xInt == 0 and yInt == boardSize) or (xInt == boardSize and yInt == 0))
        {
            cout << "Coordinate outside the board" << endl;
            continue;
        }

        // Tässä vaiheessa tiedetään, että syöte on käypä sijainti laudalla
        else
        {
            // Laajennetaan pelialuella, mikäli sille on tarvetta, jonka jälkeen merkitään
            // risti / nolla oikealle paikalle, mikäli sijainnissa ei ole vielä merkkiä.
            if (xInt == 0 or yInt == 0)
            {
                expandBoard(false, board);
            }
            else if (xInt == boardSize or yInt == boardSize)
            {
                expandBoard(true, board);
            }

            xInt = (xInt == 0)? xInt : xInt - 1;
            yInt = (yInt == 0)? yInt : yInt - 1;

            if (board.at(yInt).at(xInt) != EMPTY)
            {
                cout << "The given place is already occupied" << endl;
                continue;
            }

            // Vaihdetaan pisteen merkki
            board.at(yInt).at(xInt) = in_turn;
            bInvalidInput = false;
        }
    }
    printBoard(board);
    return checkVictory(board);
}

int main()
{
    // Pelialueen luominen.
    Board board = initBoard();

    bool bGameOver = false;
    BoardMark in_turn;
    int turn = 0;

    cout << "Start game:" << endl;
    printBoard(board);

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

        bGameOver = takeInput(in_turn, board);
        ++turn;
    }
    return EXIT_SUCCESS;
}
