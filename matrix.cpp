//
//  matrix.cpp
//  PersonalMinesweeper
//
//  Created by Harvir Singh on 12/24/19.
//  Copyright © 2019 Harvir Singh. All rights reserved.
//

#include "matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <cassert>

using namespace std;

const int size = 10000;
template<typename T>
class Matrix{
public:
    //constructor for the Matrix
    Matrix(int height_in, int width_in):height(height_in),width(width_in){}
    
    //Fill the matrix with all zeros
    void fillMatZ(){
        for(int x = 0; x<(height*width);++x){
            matArray[x]=0;
        }
    }
    //Fill the matrix will all Ones
    void fillMatOne(){
        for(int x = 0; x<(height*width);++x){
            matArray[x]=1;
        }
    }
    
    void fillMatO(){
        for(int x = 0; x<(height*width);++x){
            matArray[x]="O";
        }
    }
    
    // Randomly distribute the specified number of mines across the matrix
    void getMines(int numMin){
        if(numMin==(width*height)){
            fillMatOne();
        }
        else{
            fillMatZ();
            srand(time(NULL));
        for(int x = 0; x<numMin;++x){
            int widMine = rand()%width;
            int heightMine = rand()%height;
            int minloc = widMine + heightMine*width;
            while(matArray[minloc]==1){
                widMine = rand()%width;
                heightMine = rand()%height;
                minloc = widMine + heightMine*width;
            }
            matArray[minloc]=1;
            //cout<<"WIDTHMINE: " << widMine << " HEIGHTMINE: "<< heightMine<<endl;
        }
        }
    }
    //Determines if the given location is a mine
    bool isMine(int heightind, int widthind){
        int loc = widthind + heightind*width;
        return matArray[loc]==1;
    }
    //RETURNS THE address of the location of the height and width
    //Dereferencing this allows changing the value at that matrix
    T* changeMatVal(int heightind, int widthind){
        int loc = widthind + heightind*width;
        return &matArray[loc];
    }
    //Determined the number of mines around a given location
    int checksurroundings(int heightind, int widthind , Matrix<int> dup){
        int counter=0;
        if(heightind>0 && heightind<height && widthind>0 && widthind<width){
        for(int x = -1 ; x<2 ; ++x){
        if(dup.isMine(heightind+x,widthind-1)){
            counter ++;
        }
        if(dup.isMine(heightind+x,widthind)){
            counter ++;
        }
        if(dup.isMine(heightind+x,widthind+1)){
            counter ++;
        }
        }
        }
        else if(heightind==0 && widthind>0 && widthind<width){
            for(int x = 0 ; x<2 ; ++x){
                if(dup.isMine(heightind+x,widthind-1)){
                    counter ++;
                }
                if(dup.isMine(heightind+x,widthind)){
                    counter ++;
                }
                if(dup.isMine(heightind+x,widthind+1)){
                    counter ++;
                }
            }
        }
        else if(heightind==height-1 && widthind>0 && widthind<width){
            for(int x = -1 ; x<1 ; ++x){
                if(dup.isMine(heightind+x,widthind-1)){
                    counter ++;
                }
                if(dup.isMine(heightind+x,widthind)){
                    counter ++;
                }
                if(dup.isMine(heightind+x,widthind+1)){
                    counter ++;
                }
            }
        }
        else if(heightind>0 && heightind<height && widthind==0){
            for(int x = -1 ; x<2 ; ++x){
                if(dup.isMine(heightind+x,widthind)){
                    counter ++;
                }
                if(dup.isMine(heightind+x,widthind+1)){
                    counter ++;
                }
            }
        }
        else if(heightind>0 && heightind<height && widthind==width-1){
            for(int x = -1 ; x<2 ; ++x){
                if(dup.isMine(heightind+x,widthind)){
                    counter ++;
                }
                if(dup.isMine(heightind+x,widthind-1)){
                    counter ++;
                }
            }
        }
        else if(heightind==0 && widthind==0){
            for(int x = 0 ; x<2 ; ++x){
                if(dup.isMine(heightind+x,widthind)){
                    counter ++;
                }
                if(dup.isMine(heightind+x,widthind+1)){
                    counter ++;
                }
            }
        }
        else if(heightind==0 && widthind==width-1){
            for(int x = 0 ; x<2 ; ++x){
                if(dup.isMine(heightind+x,widthind)){
                    counter ++;
                }
                if(dup.isMine(heightind+x,widthind-1)){
                    counter ++;
                }
            }
        }
        else if(heightind==height-1 && widthind==0){
            for(int x = -1 ; x<1 ; ++x){
                if(dup.isMine(heightind+x,widthind)){
                    counter ++;
                }
                if(dup.isMine(heightind+x,widthind+1)){
                    counter ++;
                }
            }
        }
        else if(heightind==height-1 && widthind==width-1){
            for(int x = -1 ; x<1 ; ++x){
                if(dup.isMine(heightind+x,widthind)){
                    counter ++;
                }
                if(dup.isMine(heightind+x,widthind-1)){
                    counter ++;
                }
            }
        }
        
        return counter;
    }
    //Prints the matrix to the terminal(COUT)
    void printMat(){
        cout<< "    ";
        if(width<10 && width>0 && height<10 && height >0){
            for(int x = 0; x < width;++x){
                cout<< " "<<x;
            }
            cout<<endl<<endl<<endl;
            for(int x = 0 ; x<height; ++x){
                cout<< x<< "   ";
                for(int y = 0 ; y<width; ++y){
                    cout<< " "<<matArray[(x*width)+y];
                }
                cout<<endl;
            }
        }
        if(width>=10 && width<100 && height>=10 && height <100){
        for(int x = 0; x < 10;++x){
            cout<< "  "<<x;
        }
        for(int x = 10; x < width;++x){
                cout<< " "<<x;
            }
            cout<<endl<<endl<<endl;
            for(int x = 0 ; x<10; ++x){
                cout<< x<< "   ";
                for(int y = 0 ; y<width; ++y){
                    cout<< "  "<<matArray[(x*width)+y];
                }
                cout<<endl;
            }
            for(int x = 10 ; x<width; ++x){
                cout<< x<< "  ";
                for(int y = 0 ; y<width; ++y){
                    cout<< "  "<<matArray[(x*width)+y];
                }
                cout<<endl;
            }
        }
    }
    
    
private:
    int height;
    int width;
    T matArray[size];
};

class onAMine{};
class winner{};

class Minesweeper{
public:
    //Constructor for minesweeper
    Minesweeper(int height_in, int width_in, int numMines_in, bool cheat_in):moves( int(0) ), height(height_in), width(width_in), numMines(numMines_in),minesMap(height_in, width_in),minesweep(height_in, width_in),game(true), cheat(cheat_in){
        //Matrix<string> minesweep(height_in, width_in),Matrix<int> minesMap(height_in, width_in)
        //Matrix<int> minesMap();
        //Matrix<string> minesweep();
        minesMap.getMines(numMines);
        minesweep.fillMatO();
        if(cheat){
            minesMap.printMat();
            cout << endl;
        }
    }
    //Checks if a picked location by a player is a mine and if not, then makes the apprioprate changes
    //checks the surrcoundings and prints the number of mines around a picked location
    void pickLoc(int height_in, int width_in){
        if(minesMap.isMine(height_in, width_in)){
            throw onAMine();
        }
        else{
            moves++;
            if(moves == height*width - numMines){
                throw winner();
            }
            if(minesweep.checksurroundings(height_in,width_in,minesMap) != 0){
                *(minesweep.changeMatVal(height_in, width_in)) = to_string(minesweep.checksurroundings(height_in,width_in,minesMap));
            }
            else{
                *(minesweep.changeMatVal(height_in, width_in)) = " ";
                if(minesweep.checksurroundings(height_in,width_in,minesMap) != 0){
                    *(minesweep.changeMatVal(height_in, width_in)) = to_string(minesweep.checksurroundings(height_in,width_in,minesMap));
                }
                
            }
            
        }
        
    }
    
    void makeMoves(){
        minesweep.printMat();
        int widthchosen;
        int heightchosen;
        cout<<"Pick the width index of your desired location: ";
        cin >>widthchosen;
        cout<<"Pick the height index of your desired location: ";
        cin >>heightchosen;
        while(heightchosen>height-1 || heightchosen < 0 || widthchosen>width-1 || widthchosen<0){
            cout<< "INVALID LOCATION PICKED"<<endl;
            cout<<"Pick the width index of your desired location again: ";
            cin >>widthchosen;
            cout<<"Pick the height index of your desired location again: ";
            cin >>heightchosen;
        }
        while(*(minesweep.changeMatVal(heightchosen,widthchosen))!= "O" ){
            cout<< "INVALID LOCATION PICKED"<<endl;
            cout<<"Pick the width index of your desired location again: ";
            cin >>widthchosen;
            cout<<"Pick the height index of your desired location again: ";
            cin >>heightchosen;
        }
        try{
            pickLoc(heightchosen, widthchosen);
        }catch(onAMine){
            cout << "GAME OVER, YOU MADE "<< moves << " MOVES"<<endl;
            game = false;
        }catch (winner){
            cout<< "YOU HAVE WON MINESWEEPER!"<<endl;
            game = false;
        }
        if(game){
        return makeMoves();
        }
    }
private:
    int moves;
    int height;
    int width;
    int numMines;
    Matrix<int> minesMap;
    Matrix<string> minesweep;
    bool game;
    bool cheat;
};

int main(){
    cout<<"WELCOME TO HARVIR'S MINESWEEPER"<<endl;
    string name;
    cout<< "PLEASE ENTER THE HEIGHT OF YOUR DESIRED GRID:";
    int height_in;
    cin>> height_in;
    cout <<"PLEASE ENTER THE WIDTH OF YOUR DESIRED GRID:";
    int width_in;
    cin >> width_in;
    cout <<"PLEASE ENTER THE NUMBER OF MINES ON YOUR GRID:";
    int mines_in;
    cin >> mines_in;
    while(mines_in > (height_in * width_in)){
        cout<< "INVALID NUMBER OF MINES, PLEASE ENTER A VALID NUMBER OF MINES:";
        cin >> mines_in;
    }
    cout << "ARE YOU A CHEATER? (YES/NO)"<< endl;
    string cheatYN;
    cin >> cheatYN;
    bool cheat = false;
    if(cheatYN == "YES" || cheatYN == "Yes" || cheatYN == "YEs" || cheatYN == "yEs" || cheatYN== "yES" || cheatYN == "YeS" || cheatYN== "yes" || cheatYN == "yeS"){
        cheat = true;
    }
    else if(cheatYN == "NO" || cheatYN == "No" || cheatYN == "no" || cheatYN == "nO"){
        cheat = false;
    }
    Minesweeper game(height_in, width_in, mines_in, cheat);
    game.makeMoves();
}
