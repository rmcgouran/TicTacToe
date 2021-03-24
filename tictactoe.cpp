
/*
Created by N0799130 using X-Code
Any resources I have used(Also included in declaration):
YouTuber - The Coding Train:
https://www.youtube.com/watch?v=GTWrWM1UsnA
https://www.youtube.com/watch?v=trKjYdBASyQ

http://www.cplusplus.com/reference/cstdlib/rand/

rand() function doing same thing everytime fixed by:
https://stackoverflow.com/questions/17618264/srand-time-null-causes-compiler-warning-implicit-conversion-loses-integer-p
https://stackoverflow.com/questions/4736485/srandtime0-and-random-number-generation
 
*/
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;


class Container{

//Access specifier
public:
    
    //Matrix to store characters
    char board[3][3];
    int numb = 1;
    string endGame = "The game has ended.";

    /* Function to check if the user is correctly entering a grid location or if the location has been taken already */
    void user(){
        string enter;
        while(true) {
            printf("\nWhere do you want to place your marker?");
            getline(cin, enter);
            
            //Places the marker and if one is already present in the position it alerts the user to choose another
            if(enter != ""){
                char input = enter.c_str()[0];
                //Makes sure the user has not entered unneed characters such as letters, spaces or symbols
                if(input >= '1' && input <= '9'){
                    int entered = input - '0';
                    int index = entered - 1;
                    int diagLine = index / 3;
                    int vertLine = index % 3;
                
                    char position = board[diagLine][vertLine];
                
                    if(position == 'X' || position == 'O'){
                        printf("This space has been used.");
                    } else {
                        board[diagLine][vertLine] = 'X';
                        break;
                    }
                } else {
                    printf("You must chose a location from 1-9");
                }
        
            }
        }
    }

    //Two functions to build then print the board using loops
    //builds the board
    void build(){
    
        for (int x = 0; x < 3; x++){
            for (int y = 0; y < 3; y++){
                board[x][y] = to_string(numb).c_str()[0];
                numb += 1;
            }
        }
    }
    //Prints the board with walls to create a more realistic game board
    void display(){
    
        printf(" ~~~~~~~~~~~\n");
        for (int x = 0; x < 3; x++){
            for (int y = 0; y < 3; y++){
                printf(" %c |", board[x][y]);
            }
            printf("\n ~~~~~~~~~~~\n");
        }
    }
    
    void bot(){
        //srand line of code taken from Stackoverflow
        srand( static_cast<unsigned int>(time(nullptr)));
        while(true){
            int botplay= (rand()%9) + 1;
            int diagLine = (botplay - 1) / 3;
            int vertLine = (botplay - 1) % 3;
            char position = board[diagLine][vertLine];
            
            /*Position is taken so try another position until it places a marker in a free spot, then once a
            spot is found loop is exited*/
            if(position == 'X' || position == 'O'){
                continue;
            } else {
                board[diagLine][vertLine] = 'O';
                break;
            }
        }}

    //Loop through to check if each location has the same chacter - this allows win checking if each location does
    void winCheck(){
        //Various
        const char* winSet[8] = {"132", "645", "789", "147", "258", "789", "357", "159"};
    
        for(int i = 0; i < 8; i++){
            bool win = true;
            char prevBoard = '0';
            const char* winMove = winSet[i];
            
            //For loop to check which character is in each board position - this checks both player and computer moves
            for(int index = 0; index < 3; index++){
                char character = winMove[index];
                int entered = character - '0';
                int boardLoc = entered - 1;
                int diagLine = boardLoc / 3;
                int vertLine = boardLoc % 3;
                char boardCharacter = board[diagLine][vertLine];
                
                //If statement checks which player(or bot) has won by comparing it to the winSets stated in the constant
                if(prevBoard == '0'){
                    prevBoard = boardCharacter;
                } else if(prevBoard == boardCharacter){
                    continue;
                } else {
                    win= false;
                    break;
                }
            }
            //Prints which player has won and then exits the program
            if(win){
                printf("Player %c has won!\n", prevBoard);
                cout << endGame << endl;
                exit(0);
                break;
            }
        }
    }
    //Allows each function to be called using one container instead of calling them individually
    Container(){
        build();
        while(true){
            display();
            winCheck();
            user();
            bot();
        }
    }

};

//Calls the class and each individual function to load/run the game
int main() {
    Container();
    Container Container;
    
    return (0);
}
