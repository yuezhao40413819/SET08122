// Tic Tac Toe game

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void displayInstructions();
void displayBoard(char [3][3]);
int setCPLevel();
int selectLocation(int , char [3][3], char , int* , int);
int getAILocation(char , int , char [3][3], int*);
int checkLocation(int* , int );
void setTurn(int, int, char [3][3]);
char checkForWin(char [3][3]);

char initArr[3][3] = {{'1', '2', '3'},{'4', '5', '6'},{'7', '8', '9'}}; 

int main(){
	char boardArr[3][3];
	char winner, gameType, choice;
	int i, j;
	int turn, location, cpLevel = 1;
	int usedLocation[9];
	
		
	while(1){
		
		MENU:
		displayInstructions();
		
		while(1){ 
			
			printf("\nSelect a game type:\n\t1-P1 Vs P2\n\t2-P1 Vs CP\n");
			printf("\nPress Q to quit\n\n");
			printf("\nPress C to set CPlevel\n\n");
			scanf("\n%c", &gameType); 
			
			BEGIN: 
			
			
			for(i = 0; i < 3; ++i){
				for(j = 0; j < 3; ++j){
				boardArr[i][j] = initArr[i][j];
				}
			}
			
			for(i = 0; i < 9; ++i){
				usedLocation[i] = 0;
			}
			
			turn = 0;
			
			
			
			if((gameType == '1') || (gameType == '2')) {
				break;
			}
			else if((gameType == 'Q') || (gameType == 'q')){
				printf("Thank you for playing!");
				exit(0);
			}
			else if((gameType == 'C') || (gameType == 'c')){
				cpLevel = setCPLevel();
				goto MENU;
			}
			else{
				printf("invalid selection..Please try again\n");
			continue;	
			}	
		}
	
	
		while(1){

			++turn;
		
			displayBoard(boardArr);
		
			location = selectLocation(turn, boardArr, gameType, usedLocation, cpLevel);
	
			setTurn(location, turn, boardArr);
		
			winner = checkForWin(boardArr);
		
			if((winner == 'X') || (winner == 'O') || (winner == 't')){
				break;
			}
		}
	
		displayBoard(boardArr);
	
		
		if(winner == 'X'){
			printf("Player 1 won!\n");
		}
		else if(winner == 'O'){
			if(gameType == '2'){
				printf("CP won!\n");
			}
			else{
				printf("Player 2 won!\n");
			}
		}
		else{
			printf("Cat game\n");
		}
	
		
		while(1){         
			printf("\nWould you like to play again? (Y/N)\n");
			scanf("\n%c", &choice);
			if(choice == 'Y' || choice == 'y'){
				goto BEGIN;
			}
			else if(choice == 'N' || choice == 'n'){
				break;
			}
			else{
				printf("Invalid selection..Please, try again\n");
			}	
		}
	}
	
	return 0;
}


void displayInstructions(){
	printf("\nINSTRUCTIONS:\n");
	printf("The object of Tic Tac Toe is to get three in a row. You play on a\n");
	printf("three by three game board. The first player is known as X and the\n");
	printf("second is O. Players alternate placing Xs and Os on the game     \n");
	printf("board until either oppent has three in a row or all nine squares \n");
	printf("are filled. X always goes first, and in the event that no one has\n");
	printf("three in a row, the stalemate is called a cat game.\n");
}



int setCPLevel(){
	int cpLevel;
	
	do{
		printf("Choose CP Level:\n\t1.Level 1\n\t2.Level 2\n");
		scanf("%d", &cpLevel);
	}while((cpLevel < 1) || (cpLevel > 2));
	
	
	return cpLevel;
}



void displayBoard(char board[3][3]){
	int i, j;
	
	for(i = 0; i < 3; i++){
		printf("\n\t");
		for(j = 0; j < 3; j++){
				printf(" %c ", board[i][j]);
			if(j < 2){
			printf("|");
			}
		}
		if(i < 2){
			printf("\n\t___|___|___\n");
		}
	}
	printf("\n\n");
}




int selectLocation(int turn, char boardArr[3][3], char gameType, int* usedLocation, int cpLevel){
	int location, i, j, temp;
	char letter;
	
	
	while(1){
		
		
		if(turn % 2 != 0){
			printf("Player 1, enter your move: ");
			scanf("\n%d", &location); // Player 1 enter a location
		}
		
		
		else{
			
			
			if(gameType == '1'){
				printf("Player 2, enter your move: ");
				scanf("\n%d", &location); // user2 enter a location
			}
			
			
			else{
				
				location = 0;
				
				if(cpLevel == 1){
					
					
					if(location == 0){
						letter = 'O';
						location = getAILocation(letter, location , boardArr, usedLocation);
					}
				
					
					if(location == 0){
						srand((int)time(0));
						location = ((rand() % 9) + 1);
					}	
				}
				
				else if(cpLevel == 2){
					
					
					if(location == 0){
						letter = 'O';
						location = getAILocation(letter, location , boardArr, usedLocation);
					}
				
					
					if(location == 0){
						letter = 'X';
						location = getAILocation(letter, location , boardArr, usedLocation);
					}
				
					
					if(location == 0){
						srand((int)time(0));
						location = ((rand() % 9) + 1);
					}
				}
					
			}
		}
			
			
		for(i = 0; i < 9; ++i){
			for(j = 0; j < 9; ++j){
				if(usedLocation[i] > usedLocation[j]){
					temp = usedLocation[i];
					usedLocation[i] = usedLocation[j];
					usedLocation[j] = temp;
				}
			}		
		}
		
		
		
		if((location < 1) || (location > 9)){
			printf("Invalid location..Please choose a location between 1 and 9\n");
			continue;
		}
		
		else{
			
			
			for(i = 0; i < 9; ++i){
				
				if(location == usedLocation[i]){
					break;
				}
				
				if((usedLocation[i] == 0)){
					usedLocation[i] = location;
					break;
				}
			}
			
			
			
			if((boardArr[(location - 1)/3][(location - 1) % 3] == 'O') || (boardArr[(location - 1)/3][(location - 1) % 3] == 'X')){
			
				
				if((gameType == '2') && (turn % 2 == 0)){
					continue;
				}
				else{
					
				
					printf("This location is already used..Please try another one\n");
					continue;
				}		
			}		
		}
		
		break;
		
	}			
	
	if((gameType == '2') && (turn % 2 == 0)){
		printf("CP..\n");
	}
	
	return location;
}




int getAILocation(char letter, int location, char boardArr[3][3], int* usedLocation){
	int i, j;
	
	
	
	for(i = 0; i < 3; ++i){
		if(location == 0){
			
			
			if((boardArr[i][0] == boardArr[i][1]) && (boardArr[i][1] == letter)){ 
				location = (i * 3) + 3;
				location = checkLocation(usedLocation, location);
			}
			else if((boardArr[i][1] == boardArr[i][2]) && (boardArr[i][2] == letter)){ 
				location = (i * 3) + 1;
				location = checkLocation(usedLocation, location);
			}
			
			
			else if((boardArr[i][0] == boardArr[i][2]) && (boardArr[i][2] == letter)){
				location = (i * 3) + 2;
				location = checkLocation(usedLocation, location);
			}
			
			
			else if((boardArr[0][i] == boardArr[1][i]) && (boardArr[1][i] == letter)){ 
				location = i + 7;
				location = checkLocation(usedLocation, location);
			}
			else if((boardArr[1][i] == boardArr[2][i]) && (boardArr[2][i] == letter)){ 
				location = i + 1;
				location = checkLocation(usedLocation, location);
			}
			
			
			else if((boardArr[0][i] == boardArr[2][i]) && (boardArr[2][i] == letter)){
				location = i + 4;
				location = checkLocation(usedLocation, location);
			}
			
		}
		else{
			break;
		}
	}

	for(i = 0; i < 2; ++i){
		if(location == 0){
			
			
			if((boardArr[i][i] == boardArr[i + 1][i + 1]) && (boardArr[i + 1][i + 1] == letter)){ 
				location = 9 - (i * 8);
				location = checkLocation(usedLocation, location);
			}
			if((boardArr[2 - i][i] == boardArr[1 - i][1 + i]) && (boardArr[1 - i][1 + i] == letter)){ 
				location = 3 + (i * 4);
				location = checkLocation(usedLocation, location);
			}
			
			
			if((boardArr[0][i * 2] == boardArr[2][(1 - i) * 2]) && (boardArr[2][(1 - i) * 2] == letter)){
				location = 5;
				location = checkLocation(usedLocation, location);
			}
		}
		else{
			break;
		}
	}
							
	return location;
}


int checkLocation(int* usedLocation, int location){
	int i, test = 0;
	
	
	for(i = 0; i < 9; ++i){
		if(location == usedLocation[i]){
			test = 1;
			break;
		}
	}
	
	if(test == 1){
		location = 0;
	}
	
	return location;
}




void setTurn(int loc, int turn, char boardArr[3][3]){
	int i, j;
	
	for(i = 0; i < 3; ++i){
		for(j = 0; j <3; ++j){
				
			if(loc + 48 == boardArr[i][j]){ 
					
				if(turn % 2 != 0){
					boardArr[i][j] = 'X';
				}
				else{
					boardArr[i][j] = 'O';
				}
				goto FIN; 
			}
		}
	}
	FIN:;
	
}




char checkForWin(char boardArr[3][3]){
	char winner;
	int x, i, j;
	
	
	x = 0;
	winner = '\0';
	
	
	
	for(i = 0; i < 3; ++i){
		
		if(winner == '\0'){
			
			if((boardArr[i][0] == boardArr[i][1]) && (boardArr[i][1] == boardArr[i][2])){ 
				winner = boardArr[i][0];
			}
			
			else if((boardArr[0][i] == boardArr[1][i]) && (boardArr[1][i] == boardArr[2][i])){ 
				winner = boardArr[0][i];
			}
			
			else if((boardArr[0][0] == boardArr[1][1]) && (boardArr[1][1] == boardArr[2][2])){ 
				winner = boardArr[0][0];
			}
			else if((boardArr[2][0] == boardArr[1][1]) && (boardArr[1][1] == boardArr[0][2])){ 
				winner = boardArr[2][0];
			}
		}
		else{
			break;
		}	
	}
	
	
	if(winner == '\0'){
		for(i = 0; i < 3; ++i){
			for(j = 0; j < 3; ++j){
				if(boardArr[i][j] != initArr[i][j]){
					++x;
				}
			}
		}
		
		if(x == 9){
			winner = 't';
		}	
	}
	
	return winner;
}
