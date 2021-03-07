#include <vector>
#include <array>
#include <iostream>

enum PlayerPiece
{
    Empty = 0,
    PlayerOne = 1,
    PlayerTwo = 2,
};

using namespace std;
struct Board
{
    array<PlayerPiece, 42> Board = {Empty}; // Board as a 1d array
    array<short int, 7> BoardTop = {5,5,5,5,5,5,5};
    
    //Insert Piece. Return True if success. Else return false
    bool drop_piece(int x, PlayerPiece player)     
    {
        if(BoardTop[x]!= -1){
            Board[flatten(x, BoardTop[x])] = player;
            BoardTop[x]--;
            return true;
        }
        else return false;
    } 

    int flatten(int x, int y)
    {
        return x + y*7 ; 
    }

    bool check_win(int xPos, PlayerPiece player)
    {
        int yPos = BoardTop[xPos]+1;

        // horizontal
        for(int i = xPos>=4?xPos-3:0; i< 4 && i<= xPos; ++i )
        {
            //cout << "horiz" << endl;
            //cout << Board[flatten(i,yPos)] << Board[flatten(i+1,yPos)] << Board[flatten(i+2,yPos)] << Board[flatten(i+3,yPos)]  << endl;

            if(Board[flatten(i,yPos)] == Board[flatten(i+1,yPos)] 
            && Board[flatten(i+1,yPos)] == Board[flatten(i+2,yPos)] 
            && Board[flatten(i+2,yPos)] == Board[flatten(i+3,yPos)] )
            {
                
                return true;
            } 
        }

        // verticle
        if(yPos <=2) //if smaller than 2, than it cant be a complete verticle line of 4
        {
            //cout << "vert" << endl;
            //cout << Board[flatten(xPos,yPos)] << Board[flatten(xPos,yPos+1)] << Board[flatten(xPos,yPos+2)] << Board[flatten(xPos,yPos+3)];

            if(Board[flatten(xPos,yPos)] == Board[flatten(xPos,yPos+1)] 
            && Board[flatten(xPos,yPos+1)] == Board[flatten(xPos,yPos+2)] 
            && Board[flatten(xPos,yPos+2)] ==Board[flatten(xPos,yPos+3)])
            {
                return true;
            }
        }

        int pos = flatten(xPos, yPos);

        // diag downwards
        int i;
        if (xPos >=3 and yPos >=3) i = pos - 24;
        else i = pos - 8*((xPos <= yPos)? xPos: yPos);
        
        do 
        {
            if(Board[i] == Board[i + 8] 
            && Board[i+8] == Board[i+16]
            && Board[i+16] == Board[i+24])
            {
                return true;
            }
            i+=8;
        }
        while (i%7!=0 and i<=17 and i<=pos );


        // diag upwards

        if (xPos >=3 and yPos <=2) i = pos +6*3;
        else i = pos + 6*((xPos <= 5-yPos)? xPos: yPos);
        
        do 
        {
            if(Board[i] == Board[i - 6] 
            && Board[i-6 ] == Board[i-12]
            && Board[i-12] == Board[i-18])
            {
                return true;
            }
            i-=6;
        }
        while (i%7!=0 and i>=21 and (i%7) <=3 and i>=pos );



        return false;
    }

    void display_board()
    {
        for (int y = 0; y != 6; ++y)
        {
            for (int x = 0; x != 7; x++)
            {
                cout << Board[flatten(x,y)] << " ";
            }
            cout << endl;
        }
    }


};

int main()
{

    Board game = Board();
    bool win = false;
    int pos;
    while (true)
    {
        game.display_board();
        cout << "player 1" << endl;
        cin >> pos; 
        game.drop_piece(pos, PlayerOne);

        if (game.check_win(pos, PlayerOne))
        {
            game.display_board();
            cout << "p1 wins";
            break;
        }
        game.display_board();
        cout << "player 2" << endl;
        cin >> pos; 
        game.drop_piece(pos, PlayerTwo);

        if (game.check_win(pos, PlayerTwo))
        {
            game.display_board();
            cout << "p2 wins";
            break;
        }

    }
    return 0;
}