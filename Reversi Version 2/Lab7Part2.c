#include <stdio.h>
#include <stdbool.h>

void printBoard (char board[][26], int dim);
void initialBoard(char board[][26], int dim);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);
bool isValid (char board[][26], int dim, int i , int j , char piece);
int placePiece (char board[][26], int dim, char row, char col, char colour);
int scoreInDirection(char board[][26], int scoreTable[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);
int scoring (char board[][26], int scoreTable[][26], int dim, char piece, int i, int j);
void tileScoring (int scoreTable[][26], int dim);
int tileScore (int scoreTable[][26], int i, int j);

int main(int argc, char **argv)
{
	int dim;
    char board [26][26];
    char piece, cpu, p1;
    bool pmove = true, cmove = true; 
    int scoreTable [26][26];
    //getting size of board and computer side 
    printf("Enter the board dimension: ");
    scanf("%d", &dim);
    
    printf("Computer plays (B/W) : ");
    scanf(" %c", &cpu);
    if(cpu == 'W'){
        p1 = 'B';
    } else{
        p1 = 'W';
    }
    //initializing the game board and the scoring board
    initialBoard(board, dim);
    printBoard(board, dim);
    tileScoring(scoreTable, dim);
    
    //while both players have valid moves, game continues
    while(pmove && cmove){

        int c;
        int row, col;
        char pRow, pCol;
        if(cpu == 'W'){
            piece = p1;
            //check if the first player has moves
            pmove = false;
            for(int i = 0; i < dim; i++){
                for(int j = 0; j < dim; j++){
                    if(isValid(board, dim, i, j, piece)){
                        pmove = true;
                    } 
                }
            }
            //executing TA program
            if (pmove){
                printf("Enter move for colour B (RowCol): ");
                scanf(" %c%c", &pRow, &pCol);
                row = pRow - 'a';
                col = pCol - 'a';
                //place the piece on the board and flip all the pieces affected
                c = placePiece(board, dim, row, col, piece);
                if(c == 1){
                    board[row][col] = piece;
                } else{
                    printf("Invalid move.\n");
                    printf("%c player wins.\n", cpu);
                    return 0;
                }
                printBoard(board, dim);
                
            } else{
                printf("%c player has no valid move.\n", p1);
            }
            //checking for best move for computer            
            int max = 0;
            int cpuRow, cpuCol;
            for(int i = 0; i < dim; i++){
                for(int j = 0; j < dim; j++){
                    int score = scoring(board, scoreTable, dim, cpu, i, j);
                    if(isValid(board, dim, i, j, cpu)){
                        if(score > max){
                            max = score; 
                            cpuRow = i; 
                            cpuCol = j;
                        }
                        
                    } 
                }
            }
            //place the computer piece and flip all the pieces affected 
            c = placePiece(board, dim, cpuRow, cpuCol, cpu);
            if(c == 1){
                printf("Computer places W at %c%c. \n", (char)(cpuRow + 'a'), (char)(cpuCol + 'a'));
                board[cpuRow][cpuCol] = cpu;
                printBoard(board, dim);
            } else{
                printf("%c player has no valid move.\n", cpu);
                cmove = false;
            }
        } 
        //if computer has no moves left and TA program has a move left, place one more piece
        if(cmove == false && pmove){
            printf("Enter move for colour B (RowCol): ");
            scanf(" %c%c", &pRow, &pCol);
            row = pRow - 'a';
            col = pCol - 'a';
            //place the piece on the board and flip all the pieces affected
            c = placePiece(board, dim, row, col, piece);
            if(c == 1){
                board[row][col] = piece;
            } else{
                printf("Invalid move.\n");
                printf("%c player wins.\n", cpu);
                return 0;
            }
            printBoard(board, dim);
        }
        
        //same process as first part but turns are flipped
        if (cpu == 'B'){
            int max = 0;
            int cpuRow, cpuCol;
            for(int i = 0; i < dim; i++){
                for(int j = 0; j < dim; j++){
                    int score = scoring(board, scoreTable, dim, cpu, i, j);
                    if(isValid(board, dim, i, j, cpu)){
                        if(score > max){
                            max = score; 
                            cpuRow = i; 
                            cpuCol = j;
                        }
                        
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
                printf("Enter move for colour W (RowCol): ");
                scanf(" %c%c", &pRow, &pCol);
                row = pRow - 'a';
                col = pCol - 'a';
                //place the piece on the board and flip all the pieces affected
                c = placePiece(board, dim, row, col, piece);
                if(c == 1){
                    board[row][col] = piece;
                } else{
                    printf("Invalid move.\n");
                    printf("%c player wins.\n", cpu);
                    return 0;
                }
                printBoard(board, dim);
            } else{
                printf("%c player has no valid move.\n", p1);
            }
        }
        //if TA program has no moves but computer has one, computer plays one more turn
        if(pmove == false && cmove){
            int max = 0;
            int cpuRow, cpuCol;
            for(int i = 0; i < dim; i++){
                for(int j = 0; j < dim; j++){
                    int score = scoring(board, scoreTable, dim, cpu, i, j);
                    if(isValid(board, dim, i, j, cpu)){
                        if(score > max){
                            max = score; 
                            cpuRow = i; 
                            cpuCol = j;
                        }
                        
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
    //check the score for the entire board 
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
    //output the result
    if(cpuScore > pScore){
        printf("%c player wins.\n", cpu);
    } else if(pScore > cpuScore){
        printf("%c player wins.\n", p1);
    } else{
        printf("Draw!\n");
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
bool positionInBounds(int n, int row, int col){
    //checks to see if the position specified lies within the bounds of the board
    if(row >= 0 && row < n && col >=0 && col < n){
        return true;
    }
    return false;
}
bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol){
    //check if the direction specified has a legal move 
    int nRow = row + deltaRow;
    int nCol = col + deltaCol;
    char nColour;

    if (colour == 'W'){
        nColour = 'B';
    } else if (colour == 'B'){
        nColour = 'W';
    }
    //check for opposite coloured piece
    if(board[nRow][nCol] == nColour && positionInBounds(n, nRow, nCol)){
        for(int i = 2; i <= n; i++){
            nRow = row + deltaRow*i;
            nCol = col + deltaCol*i;
            //continue down the direction if an opposite piece is found
            if(positionInBounds(n, nRow, nCol)){
                //if no opposite colour is found, return false if opposite piece found, direction is valid
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
    //check if move is valid in all directions
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
    //flip all the pieces affected in all directions when move is made 
    int c = 0;
    int tRow = row;
    int tCol = col;
    char piece = colour;
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, -1, 0) && board[tRow][tCol] == 'U'){
        c = 1;
        for(int i = 1; i < dim; i++){
            if(board[tRow - i][tCol] != 'U' && positionInBounds(dim,tRow - i, tCol)){
                board[tRow - i][tCol] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, -1, 1) && board[tRow][tCol] == 'U'){
        c = 1;
        for(int i = 1; i < dim; i++){
            if(board[tRow - i][tCol + i] != 'U' && positionInBounds(dim,tRow - i, tCol + i)){
                board[tRow - i][tCol + i] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, 0, 1) && board[tRow][tCol] == 'U'){
        c = 1;
        for(int i = 1; i < dim; i++){
            if(board[tRow][tCol + i] != 'U' && positionInBounds(dim,tRow, tCol + i)){
                board[tRow][tCol + i] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, 1, 1) && board[tRow][tCol] == 'U'){
        c = 1;
        for(int i = 1; i < dim; i++){
            if(board[tRow + i][tCol + i] != 'U' && positionInBounds(dim,tRow + i, tCol + i)){
                board[tRow + i][tCol + i] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, 1, 0) && board[tRow][tCol] == 'U'){
        c = 1;
        for(int i = 1; i < dim; i++){
            if(board[tRow + i][tCol] != 'U' && positionInBounds(dim,tRow + i, tCol)){
                board[tRow + i][tCol] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, 1, -1) && board[tRow][tCol] == 'U'){
        c = 1;
        for(int i = 1; i < dim; i++){
            if(board[tRow + i][tCol - i] != 'U' && positionInBounds(dim,tRow + i, tCol - i)){
                board[tRow + i][tCol - i] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, 0, -1) && board[tRow][tCol] == 'U'){
        c = 1;
        for(int i = 1; i < dim; i++){
            if(board[tRow][tCol - i] != 'U' && positionInBounds(dim,tRow, tCol - i)){
                board[tRow][tCol - i] = piece;
            }
        }
    }
    if(checkLegalInDirection(board, dim, tRow, tCol, piece, -1, -1) && board[tRow][tCol] == 'U'){
        c = 1;
        for(int i = 1; i < dim; i++){
            if(board[tRow - i][tCol - i] != 'U' && positionInBounds(dim,tRow - i, tCol - i)){
                board[tRow - i][tCol - i] = piece;
            }
        }
    }
    return c;
}    
void tileScoring (int scoreTable[][26], int dim){
    //manually score each tile so that corners are prioritized and the edges are prioritized
    //set all cells to 0 first 
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            scoreTable[i][j] = 0;
        }
    }
    if(dim == 4){
        //corner values 
        scoreTable[0][0] = 10;
        scoreTable[0][3] = 10;
        scoreTable[3][3] = 10;
        scoreTable[3][0] = 10;
        //all the remaining values are the same 
        for(int i = 0; i < dim; i++){
            for(int j = 0; j < dim; j++){
                if(scoreTable[i][j] == 0){
                    scoreTable[i][j] == 2;
                }
            }
        }
    } else{
        //corner values
        scoreTable[0][0] = 150;
        scoreTable[0][dim-1] = 150;
        scoreTable[dim-1][0] = 150;
        scoreTable[dim-1][dim-1] = 150;
        
        int start = dim/2 - 1;
        //center of the board values 
        scoreTable [start][start] = 10;
        scoreTable [start][start+1] = 10;
        scoreTable [start+1][start] = 10;
        scoreTable [start+1][start+1] = 10;
        
        //top left  
        scoreTable[1][0] = 1;
        scoreTable[1][1] = 3;
        scoreTable[0][1] = 1;
        //top right 
        scoreTable[0][dim-2] = 1;
        scoreTable[1][dim-2] = 3;
        scoreTable[1][dim-1] = 1;
        //bottom left  
        scoreTable[dim-2][0] = 1;
        scoreTable[dim-2][1] = 3;
        scoreTable[dim-1][1] = 1;
        //bottom right 
        scoreTable[dim-2][dim-1] = 1;
        scoreTable[dim-2][dim-2] = 3;
        scoreTable[dim-1][dim-2] = 1;
        
        //edge values 
        for(int i = 2; i < dim-2; i++){
            scoreTable[0][i] = 30;
            scoreTable[dim-1][i] = 30;
            scoreTable[i][0] = 30;
            scoreTable[i][dim-1] = 30;
        }
        //one row before edge values
        for(int i = 2; i < dim-2; i++){
            scoreTable[1][i] = 3;
            scoreTable[dim-2][i] = 3;
            scoreTable[i][1] = 3;
            scoreTable[i][dim-2] = 3;
        }
        //every remaining cell
        for(int i = 0; i < dim; i++){
            for(int j = 0; j < dim; j++){
                if(scoreTable[i][j] == 0){
                    scoreTable[i][j] = 8;;
                }
            }
        }
    }
    
}
int tileScore (int scoreTable[][26], int i, int j){
    //returns the score at the specified value
    return scoreTable[i][j];
}
int scoring (char board[][26], int scoreTable[][26], int dim, char piece, int i, int j){
    //calculate the score of the position by multiplying the number of pieces flipped by their individual value
    int tScore = 0;
    if(scoreInDirection(board, scoreTable, dim, i, j, piece, -1, 0) != 0 && board[i][j] == 'U'){
        tScore = tScore + scoreInDirection(board, scoreTable, dim, i, j, piece, -1, 0);
    }
    if(scoreInDirection(board, scoreTable, dim, i, j, piece, -1, 1) != 0 && board[i][j] == 'U'){
        tScore = tScore + scoreInDirection(board, scoreTable, dim, i, j, piece, -1, 1);
    }
    if(scoreInDirection(board, scoreTable, dim, i, j, piece, 0, 1) != 0 && board[i][j] == 'U'){
        tScore = tScore + scoreInDirection(board, scoreTable, dim, i, j, piece, 0, 1);
    }
    if(scoreInDirection(board, scoreTable, dim, i, j, piece, 1, 1) != 0 && board[i][j] == 'U'){
        tScore = tScore + scoreInDirection(board, scoreTable, dim, i, j, piece, 1, 1);
    }
    if(scoreInDirection(board, scoreTable, dim, i, j, piece, 1, 0) != 0 && board[i][j] == 'U'){
        tScore = tScore + scoreInDirection(board, scoreTable, dim, i, j, piece, 1, 0);
    }
    if(scoreInDirection(board, scoreTable, dim, i, j, piece, 1, -1) != 0 && board[i][j] == 'U'){
        tScore = tScore + scoreInDirection(board, scoreTable, dim, i, j, piece, 1, -1);
    }
    if(scoreInDirection(board, scoreTable, dim, i, j, piece, 0, -1) != 0 && board[i][j] == 'U'){
        tScore = tScore + scoreInDirection(board, scoreTable, dim, i, j, piece, 0, -1);
    }
    if(scoreInDirection(board, scoreTable, dim, i, j, piece, -1, -1) != 0 && board[i][j] == 'U'){
        tScore = tScore + scoreInDirection(board, scoreTable, dim, i, j, piece, -1, -1);
    }
    return tScore;
}
int scoreInDirection(char board[][26], int scoreTable[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol){
    //calculate the score in the direction specified
    int nRow = row + deltaRow;
    int nCol = col + deltaCol;
    int counter = 0;
    char nColour;

    if (colour == 'W'){
        nColour = 'B';
    } else if (colour == 'B'){
        nColour = 'W';
    }
    //if the move is within bounds, add the value of the piece
    if(board[nRow][nCol] == nColour && positionInBounds(n, nRow, nCol)){
        counter = counter + tileScore(scoreTable, nRow, nCol);
        //continue down the direction adding all the values of the pieces
        for(int i = 2; i <= n; i++){
            nRow = row + deltaRow*i;
            nCol = col + deltaCol*i;
            //if the move is invalid, return a value of 0
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
                counter = counter + tileScore(scoreTable, nRow, nCol);
            }
        }
    }
}