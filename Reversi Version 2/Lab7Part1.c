#include <stdio.h>
#include <stdbool.h>

void printBoard (char board[][26], int dim);
void initialBoard(char board[][26], int dim);
void configureBoard(char board[][26], char piece, char pRow, char pCol);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);
bool isValid (char board[][26], int dim, int i , int j , char piece);
int placePiece (char board[][26], int dim, char row, char col, char colour);
int scoreInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);
int scoring (char board[][26], int dim, char colour, int i, int j);

int main(int argc, char **argv)
{
	int dim;
    char board [26][26];
    char piece, pRow, pCol, cpu, p1;
    bool pmove = true, cmove = true; 
    //get user input 
    printf("Enter the board dimension: ");
    scanf("%d", &dim);
    //initialize colours for computer and player 
    printf("Computer plays (B/W) : ");
    scanf(" %c", &cpu);
    //initialize players and board
    if(cpu == 'W'){
        p1 = 'B';
    } else{
        p1 = 'W';
    }
    initialBoard(board, dim);
    printBoard(board, dim);
    
    //while both players have valid moves, the program continues 
    while(pmove && cmove){
        int c;
        //this is for the case that the cpu is white and the player is black 
        if(cpu == 'W'){
            //set the piece colour to the player colour and assume that there are no possible moves for the player
            piece = p1;
            pmove = false;
            //check to see if the player has any moves left 
            for(int i = 0; i < dim; i++){
                for(int j = 0; j < dim; j++){
                    if(isValid(board, dim, i, j, piece)){
                        //if player has any possible moves left, pmove becomes true
                        pmove = true;
                    } 
                }
            }
            
            //if player has a move then ask for the move 
            if (pmove){
                printf("Enter move for colour B (RowCol): ");
                scanf(" %c%c", &pRow, &pCol);
                int tRow = pRow - 'a';
                int tCol = pCol - 'a';
                //check to see if the move can be made and which pieces are affected 
                c = placePiece(board, dim, tRow, tCol, piece);
                //if the move is valid then the piece is placed and flipped 
                if(c == 1){
                    board[tRow][tCol] = piece;
                } else{
                    printf("Invalid move.");
                    printf("%c player wins.", cpu);
                    return 0;
                }
                printBoard(board, dim);
            } else{
                printf("%c player has no valid move.", p1);
            }
            
            //use the strategy specified from the assignment guide 
            int max = 0;
            int cpuRow, cpuCol;
            for(int i = 0; i < dim; i++){
                for(int j = 0; j < dim; j++){
                    int score = scoring(board, dim, cpu, i, j);
                    if(score > max){
                        max = score;
                        cpuRow = i;
                        cpuCol = j;
                    }
                }
            }
            
            //check to see if the move can be made and which pieces are affected 
            c = placePiece(board, dim, cpuRow, cpuCol, cpu);
            if(c == 1){
                //place the piece and flip all afected pieces 
                printf("Computer places W at %c%c. \n", (char)(cpuRow + 'a'), (char)(cpuCol + 'a'));
                board[cpuRow][cpuCol] = cpu;
                printBoard(board, dim);
            } else{
                printf("%c player has no valid move.\n", cpu);
                cmove = false;
            }
        }
        //since the player goes first and the cpu goes second, if the player runs out of moves first 
        //the computer gets one extra chance to place a piece 
        if(cmove == false && pmove){
            printf("Enter move for colour B (RowCol): ");
            scanf(" %c%c", &pRow, &pCol);
            int tRow = pRow - 'a';
            int tCol = pCol - 'a';
        
            c = placePiece(board, dim, tRow, tCol, piece);
            if(c == 1){
                board[tRow][tCol] = piece;
            }
            printBoard(board, dim);
        }
        
        //same as the first case except the computer goes first and the player goes second 
        if (cpu == 'B'){
            int max = 0;
            int cpuRow, cpuCol;
            for(int i = 0; i < dim; i++){
                for(int j = 0; j < dim; j++){
                    int score = scoring(board, dim, cpu, i, j);
                    if(score > max){
                        max = score;
                        cpuRow = i;
                        cpuCol = j;
                    }
                }
            }

            c = placePiece(board, dim, cpuRow, cpuCol, cpu);
            if(c == 1){
                printf("Computer places %c at %c%c. \n", cpu, (char)(cpuRow + 'a'), (char)(cpuCol + 'a'));
                board[cpuRow][cpuCol] = cpu;
                printBoard(board, dim);
            } else{
                printf("%c player has no valid move.\n", cpu);
                cmove = false;
            }
            
            piece = p1;
            pmove = false;
            for(int i = 0; i < dim; i++){
                for(int j = 0; j < dim; j++){
                    if(isValid(board, dim, i, j, piece)){
                        pmove = true;
                    } 
                }
            }
            
            if (pmove){
                printf("Enter move for colour %c (RowCol): ", p1);
                scanf(" %c%c", &pRow, &pCol);
                int tRow = pRow - 'a';
                int tCol = pCol - 'a';
                
                c = placePiece(board, dim, tRow, tCol, piece);
                if(c == 1){
                    board[tRow][tCol] = piece;
                } else{
                    printf("Invalid move.");
                    printf("%c player wins.", cpu);
                    return 0;
                }
                printBoard(board, dim);
            } else{
                printf("%c player has no valid move.", p1);
            }
        }
        if(pmove == false && cmove){
            int max = 0;
            int cpuRow, cpuCol;
            for(int i = 0; i < dim; i++){
                for(int j = 0; j < dim; j++){
                    int score = scoring(board, dim, cpu, i, j);
                    if(score > max){
                        max = score;
                        cpuRow = i;
                        cpuCol = j;
                    }
                }
            }

            c = placePiece(board, dim, cpuRow, cpuCol, cpu);
            if(c == 1){
                printf("Computer places %c at %c%c. \n", cpu, (char)(cpuRow + 'a'), (char)(cpuCol + 'a'));
                board[cpuRow][cpuCol] = cpu;
                printBoard(board, dim);
            }
        }
        
    }
    //go through each cell in the board and calculate the score for each player 
    int cpuScore = 0;
    int pScore = 0;
    for(int row = 0; row < dim; row++){
        for(int col = 0; col < dim; col++){
            if(board[row][col] == cpu){
                cpuScore = cpuScore + 1;
            } else if(board[row][col] == p1){
                pScore = pScore + 1;
            }
        }
    }
    //print who wins based on the score
    if(cpuScore > pScore){
        printf("%c player wins.", cpu);
    } else if(pScore > cpuScore){
        printf("%c player wins.", p1);
    } else{
        printf("Draw!");
    }
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
    int nRow = row + deltaRow;
    int nCol = col + deltaCol;
    char nColour;

    if (colour == 'W'){
        nColour = 'B';
    } else if (colour == 'B'){
        nColour = 'W';
    }
    //check the pieces in the direction specified 
    if(positionInBounds(n, nRow, nCol) && board[nRow][nCol] == nColour){
        for(int i = 2; i <= n; i++){
            nRow = row + deltaRow*i;
            nCol = col + deltaCol*i;
            //if the position is in bounds and is unoccupied, it is an invalid move
            //if the position is in bounds and is the same colour as the starting piece then the move is valid
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
        return false;
    }
    return false;
}

bool isValid (char board[][26], int dim, int i , int j , char piece){
    //check legality in all directions for only pieces that are currently unoccupied 
    if(checkLegalInDirection(board, dim, i, j, piece, -1, 0) && board[i][j] == 'U'){
        return true;
    }
    if(checkLegalInDirection(board, dim, i, j, piece, -1, 1) && board[i][j] == 'U'){
        return true;
    }
    if(checkLegalInDirection(board, dim, i, j, piece, 0, 1) && board[i][j] == 'U'){
        return true;
    }
    if(checkLegalInDirection(board, dim, i, j, piece, 1, 1) && board[i][j] == 'U'){
        return true;
    }
    if(checkLegalInDirection(board, dim, i, j, piece, 1, 0) && board[i][j] == 'U'){
        return true;
    }
    if(checkLegalInDirection(board, dim, i, j, piece, 1, -1) && board[i][j] == 'U'){
        return true;
    }
    if(checkLegalInDirection(board, dim, i, j, piece, 0, -1) && board[i][j] == 'U'){
        return true;
    }
    if(checkLegalInDirection(board, dim, i, j, piece, -1, -1) && board[i][j] == 'U'){
        return true;
    }
    return false;
}

int placePiece(char board[][26], int dim, char row, char col, char colour){
    int c = 0;
    int tRow = row;
    int tCol = col;
    char piece = colour;
    //if the move is valid, flip all the pieces in all directions that are affected by the move 
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, -1, 0) && board[tRow][tCol] == 'U'){
        c = 1;
        for(int i = 1; i < dim; i++){
            if((positionInBounds(dim,tRow - i, tCol)) && board[tRow - i][tCol] != 'U'){
                board[tRow - i][tCol] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, -1, 1) && board[tRow][tCol] == 'U'){
        c = 1;
        for(int i = 1; i < dim; i++){
            if(positionInBounds(dim,tRow - i, tCol + i) && board[tRow - i][tCol + i] != 'U'){
                board[tRow - i][tCol + i] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, 0, 1) && board[tRow][tCol] == 'U'){
        c = 1;
        for(int i = 1; i < dim; i++){
            if(positionInBounds(dim,tRow, tCol + i) && board[tRow][tCol + i] != 'U'){
                board[tRow][tCol + i] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, 1, 1) && board[tRow][tCol] == 'U'){
        c = 1;
        for(int i = 1; i < dim; i++){
            if(positionInBounds(dim,tRow + i, tCol + i) && board[tRow + i][tCol + i] != 'U'){
                board[tRow + i][tCol + i] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, 1, 0) && board[tRow][tCol] == 'U'){
        c = 1;
        for(int i = 1; i < dim; i++){
            if(positionInBounds(dim,tRow + i, tCol) && board[tRow + i][tCol] != 'U'){
                board[tRow + i][tCol] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, 1, -1) && board[tRow][tCol] == 'U'){
        c = 1;
        for(int i = 1; i < dim; i++){
            if(positionInBounds(dim,tRow + i, tCol - i) && board[tRow + i][tCol - i] != 'U'){
                board[tRow + i][tCol - i] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, 0, -1) && board[tRow][tCol] == 'U'){
        c = 1;
        for(int i = 1; i < dim; i++){
            if(positionInBounds(dim,tRow, tCol - i) && board[tRow][tCol - i] != 'U'){
                board[tRow][tCol - i] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, -1, -1) && board[tRow][tCol] == 'U'){
        c = 1;
        for(int i = 1; i < dim; i++){
            if(positionInBounds(dim,tRow - i, tCol - i) && board[tRow - i][tCol - i] != 'U'){
                board[tRow - i][tCol - i] = piece;
            }
        }
    }
    return c;
}

int scoring (char board[][26], int dim, char piece, int i, int j){
    int tScore = 0;
    //calculate the score for each direction to get the total score of the cell 
    if(scoreInDirection(board, dim, i, j, piece, -1, 0) != 0 && board[i][j] == 'U'){
        tScore = tScore + scoreInDirection(board, dim, i, j, piece, -1, 0);
    }
    if(scoreInDirection(board, dim, i, j, piece, -1, 1) != 0 && board[i][j] == 'U'){
        tScore = tScore + scoreInDirection(board, dim, i, j, piece, -1, 1);
    }
    if(scoreInDirection(board, dim, i, j, piece, 0, 1) != 0 && board[i][j] == 'U'){
        tScore = tScore + scoreInDirection(board, dim, i, j, piece, 0, 1);
    }
    if(scoreInDirection(board, dim, i, j, piece, 1, 1) != 0 && board[i][j] == 'U'){
        tScore = tScore + scoreInDirection(board, dim, i, j, piece, 1, 1);
    }
    if(scoreInDirection(board, dim, i, j, piece, 1, 0) != 0 && board[i][j] == 'U'){
        tScore = tScore + scoreInDirection(board, dim, i, j, piece, 1, 0);
    }
    if(scoreInDirection(board, dim, i, j, piece, 1, -1) != 0 && board[i][j] == 'U'){
        tScore = tScore + scoreInDirection(board, dim, i, j, piece, 1, -1);
    }
    if(scoreInDirection(board, dim, i, j, piece, 0, -1) != 0 && board[i][j] == 'U'){
        tScore = tScore + scoreInDirection(board, dim, i, j, piece, 0, -1);
    }
    if(scoreInDirection(board, dim, i, j, piece, -1, -1) != 0 && board[i][j] == 'U'){
        tScore = tScore + scoreInDirection(board, dim, i, j, piece, -1, -1);
    }
    return tScore;
}

int scoreInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol){
    int nRow = row + deltaRow;
    int nCol = col + deltaCol;
    int counter = 0;
    char nColour;

    if (colour == 'W'){
        nColour = 'B';
    } else if (colour == 'B'){
        nColour = 'W';
    }
    //the score in the direction specified is just how many pieces can be flipped 
    if(positionInBounds(n, nRow, nCol) && board[nRow][nCol] == nColour){
        counter = counter + 1;
        for(int i = 2; i <= n; i++){
            nRow = row + deltaRow*i;
            nCol = col + deltaCol*i;
            counter = counter + 1;
            //if the move is invalid in any way, the counter is reset to 0
            if(positionInBounds(n, nRow, nCol)){
                if(board[nRow][nCol] == 'U'){
                    counter = 0;
                    return counter;
                    break;
                }
                if(board[nRow][nCol] == colour){
                    return counter;
                    break;
                }
            }
        }
        counter = 0;
        return counter;
    }
    return counter;
}
