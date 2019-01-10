#include <stdio.h>
#include <stdbool.h>
void printBoard (char board[][26], int dim);
void initialBoard(char board[][26], int dim);
void configureBoard(char board[][26], char piece, char pRow, char pCol);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);
 
int main(int argc, char **argv)
{
    int dim;
    char board [26][26];
    char piece, pRow, pCol; 
	//Get board dimensions
    printf("Enter the board dimension: ");
    scanf("%d", &dim);
    //print the initial board 
    initialBoard(board, dim);
    printBoard(board, dim);
    //get the user configurations
    printf("Enter board configuration: \n");
    scanf(" %c%c%c", &piece, &pRow, &pCol);
    while(piece != '!'){
        configureBoard(board, piece, pRow, pCol);
        scanf(" %c%c%c", &piece, &pRow, &pCol);
    }
    //print the new board after the configurations
    printBoard(board, dim);
    
    //print the current moves for White
    printf("Available moves for W: \n");
    //check every cell for possible moves
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            //each one of these checks a possible direction using x and y coordinates only if that cell is currently unoccupied(8 possible directions)
            if(checkLegalInDirection(board, dim, i, j, 'W', -1, 0) && board[i][j] == 'U'){
                //if it is a valid move in that direction, print out the coordinates for it
                printf("%c%c \n", i+'a', j+'a');
            }
            if(checkLegalInDirection(board, dim, i, j, 'W', -1, 1) && board[i][j] == 'U'){
                printf("%c%c \n", i+'a', j+'a');
            }
            if(checkLegalInDirection(board, dim, i, j, 'W', 0, 1) && board[i][j] == 'U'){
                printf("%c%c \n", i+'a', j+'a');
            }
            if(checkLegalInDirection(board, dim, i, j, 'W', 1, 1) && board[i][j] == 'U'){
                printf("%c%c \n", i+'a', j+'a');
            }
            if(checkLegalInDirection(board, dim, i, j, 'W', 1, 0) && board[i][j] == 'U'){
                printf("%c%c \n", i+'a', j+'a');
            }
            if(checkLegalInDirection(board, dim, i, j, 'W', 1, -1) && board[i][j] == 'U'){
                printf("%c%c \n", i+'a', j+'a');
            }
            if(checkLegalInDirection(board, dim, i, j, 'W', 0, -1) && board[i][j] == 'U'){
                printf("%c%c \n", i+'a', j+'a');
            }
            if(checkLegalInDirection(board, dim, i, j, 'W', -1, -1) && board[i][j] == 'U'){
                printf("%c%c \n", i+'a', j+'a');
            }
        }
    }
    //print the current moves for Black
    printf("Available moves for B: \n");
    //same process as checking moves for White
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            if(checkLegalInDirection(board, dim, i, j, 'B', -1, 0) && board[i][j] == 'U'){
                printf("%c%c \n", i+'a', j+'a');
            }
            if(checkLegalInDirection(board, dim, i, j, 'B', -1, 1) && board[i][j] == 'U'){
                printf("%c%c \n", i+'a', j+'a');
            }
            if(checkLegalInDirection(board, dim, i, j, 'B', 0, 1) && board[i][j] == 'U'){
                printf("%c%c \n", i+'a', j+'a');
            }
            if(checkLegalInDirection(board, dim, i, j, 'B', 1, 1) && board[i][j] == 'U'){
                printf("%c%c \n", i+'a', j+'a');
            }
            if(checkLegalInDirection(board, dim, i, j, 'B', 1, 0) && board[i][j] == 'U'){
                printf("%c%c \n", i+'a', j+'a');
            }
            if(checkLegalInDirection(board, dim, i, j, 'B', 1, -1) && board[i][j] == 'U'){
                printf("%c%c \n", i+'a', j+'a');
            }
            if(checkLegalInDirection(board, dim, i, j, 'B', 0, -1) && board[i][j] == 'U'){
                printf("%c%c \n", i+'a', j+'a');
            }
            if(checkLegalInDirection(board, dim, i, j, 'B', -1, -1) && board[i][j] == 'U'){
                printf("%c%c \n", i+'a', j+'a');
            }

        }
    }
    
    //get the user move
    printf("Enter a move: \n");
    scanf(" %c%c%c", &piece, &pRow, &pCol);
    //convert the character input into a numerical value for the array
    int tRow = pRow - 'a';
    int tCol = pCol - 'a';
    int c = 0;
    //check all directions for possible moves, if any of these are true, then the counter (c) is set to 1
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, -1, 0) && board[tRow][tCol] == 'U'){
        printf("Valid move.");
        c = 1;
        for(int i = 1; i < dim; i++){
            //if the piece next to the user placed piece is of the opposite colour and within the bounds of the board then the program
            //continues looking down that same direction until the same user piece colour is found
            //this checking process is repeated for all the 7 other directions
            if(board[tRow - i][tCol] != 'U' && positionInBounds(dim,tRow - i, tCol)){
                board[tRow - i][tCol] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, -1, 1) && board[tRow][tCol] == 'U'){
        printf("Valid move.");
        c = 1;
        for(int i = 1; i < dim; i++){
            if(board[tRow - i][tCol + i] != 'U' && positionInBounds(dim,tRow - i, tCol + i)){
                board[tRow - i][tCol + i] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, 0, 1) && board[tRow][tCol] == 'U'){
        printf("Valid move.");
        c = 1;
        for(int i = 1; i < dim; i++){
            if(board[tRow][tCol + i] != 'U' && positionInBounds(dim,tRow, tCol + i)){
                board[tRow][tCol + i] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, 1, 1) && board[tRow][tCol] == 'U'){
        printf("Valid move.");
        c = 1;
        for(int i = 1; i < dim; i++){
            if(board[tRow + i][tCol + i] != 'U' && positionInBounds(dim,tRow + i, tCol + i)){
                board[tRow + i][tCol + i] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, 1, 0) && board[tRow][tCol] == 'U'){
        printf("Valid move.");
        c = 1;
        for(int i = 1; i < dim; i++){
            if(board[tRow + i][tCol] != 'U' && positionInBounds(dim,tRow + i, tCol)){
                board[tRow + i][tCol] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, 1, -1) && board[tRow][tCol] == 'U'){
        printf("Valid move.");
        c = 1;
        for(int i = 1; i < dim; i++){
            if(board[tRow + i][tCol - i] != 'U' && positionInBounds(dim,tRow + i, tCol - i)){
                board[tRow + i][tCol - i] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, 0, -1) && board[tRow][tCol] == 'U'){
        printf("Valid move.");
        c = 1;
        for(int i = 1; i < dim; i++){
            if(board[tRow][tCol - i] != 'U' && positionInBounds(dim,tRow, tCol - i)){
                board[tRow][tCol - i] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, -1, -1) && board[tRow][tCol] == 'U'){
        printf("Valid move.");
        c = 1;
        for(int i = 1; i < dim; i++){
            if(board[tRow - i][tCol - i] != 'U' && positionInBounds(dim,tRow - i, tCol - i)){
                board[tRow - i][tCol - i] = piece;
            }
        }
    }
    //if any of the above are true then the piece is set and it is a valid move, if none of the above are true then the invalid message is ouputted
    if(c == 1){
        board[tRow][tCol] = piece;
    } else{
        printf("Invalid move.");
    }
    //print the final board with the pieces flipped
    printf("\n");
    printBoard(board, dim);
    
	return 0;
}

void printBoard (char board[][26], int dim){
    //prints the first row of the board
    char L = 'a';
    printf("  ");
    for(int fRow = 0; fRow < dim; fRow++){
        printf("%c", L);
        L = L + 1;
    }
    printf("\n");
    L = 'a';
    //prints the subsequent rows of the board that actually contain the pieces
    for(int row = 0; row < dim; row++){
        printf("%c ", L);
        for(int col = 0; col < dim; col++){
            printf("%c", board[row][col]);
        }
        L = L + 1;
        printf("\n");
    }
}

void initialBoard(char board[][26], int dim){
    //gives the initial settings for the board
    for(int row = 0; row < dim; row++){
        for(int col = 0; col < dim; col++){
            board [row][col] = 'U';
        }
    }
    int initial = dim/2 - 1;

    board [initial][initial] = 'W';
    board [initial][initial+1] = 'B';
    board [initial+1][initial] = 'B';
    board [initial+1][initial+1] = 'W';
}

void configureBoard(char board[][26], char piece, char pRow, char pCol){
    //configures the board according to the user
    int row = (int)(pRow - 'a');
    int col = (int)(pCol - 'a');
    board[row][col] = piece;
}

bool positionInBounds(int n, int row, int col){
    //checks to see if the position specified lies within the bounds of the board
    if(row >= 0 && row < n && col >=0 && col < n){
        return true;
    }
    return false;
}

bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol){
    //converts the position of the user piece into numerical coordinates
    int nRow = row + deltaRow;
    int nCol = col + deltaCol;
    char nColour;
    //if the placed piece is white then the program looks for black pieces and vice versa
    if (colour == 'W'){
        nColour = 'B';
    } else if (colour == 'B'){
        nColour = 'W';
    }
    //checks to see if the piece next to the user piece is the opposite colour and is within the bounds
    if(positionInBounds(n, nRow, nCol) && board[nRow][nCol] == nColour){
        for(int i = 2; i <= n; i++){
            nRow = row + deltaRow*i;
            nCol = col + deltaCol*i;
            //if both conditions are met then the program searches the next pieces until it reaches an unoccupied space or a piece
            //the same colour as the user piece. If the first condition is met, then the program returns false and the direction is
            //not valid. If the second condition is met, then the program returns true and the direction is valid. 
            if(positionInBounds(n, nRow, nCol)){
                if(board[nRow][nCol] == 'U'){
                    return false;
                }
                if(board[nRow][nCol] == colour){
                    return true;
                    break;
                }
            }
        }
        //if none of these conditions are met, then the program returns false.
        return false;
    }
    return false;
}
