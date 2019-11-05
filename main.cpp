//
//  main.cpp
//  Battleship++
//
//  Created by Patrick Tumulty on 10/23/19.
//  Copyright © 2019 Patrick Tumulty. All rights reserved.
//

#include <iostream>
#include <string>
#include "matrix.hpp"
#include <unistd.h>

// 0 = no ship
// 1 = ship
// 2 = miss
// 3 = direct hit

void printRadar(int** matrix, int size);
void printWater(int** matrix, int size);
void ClearScreen();
void printMessage(std::string message, int size);
int alphIndex(std::string character);
int * coordinates(std::string row, std::string col);
int * userInput(int size);
void updateScreen(std::string message, int** player1, int** player2, int p1Score, int p2Score, int size);
void updateBoard(int** board, int row, int col, int size);
void printScore(int p1Score, int p2Score, int size);
int * AIcoordinates(int ** board, int size, std::string message);

// globals // =====================================

int p1 = 0;
int p2 = 0;

int AIr = 888;
int AIc = 888;


bool turn = true;

std::string alph[26] = {"A", "B", "C", "D", "E", "F", "G",
                        "H", "I", "J", "K", "L", "M", "N",
                        "O", "P", "Q", "R", "S", "T", "U",
                        "V", "W", "X", "Y", "Z" };

std::string gMessage = "Welcome to Battleship++";
std::string gMessage2 = "";

std::string Name1;
std::string Name2;

std::string RandName[] = {"Santa", "Durden", "Morty", "Rick", "Marty F", "Luke", "Richard Head" };




int * c;
int * AI;
int * AI2;

int autoRow = 0;
int autoCol = 0;

// =====================================

int main(int argc, const char * argv[]) {
    
    srand((unsigned int)time(0));
    
    int boardSize;
    int numberShips;
    
    std::cout<<"Enter Your Name : ";
    std::cin >> Name1;
    Name2 = RandName[rand() % 6];
    std::cout<<"Battlefield size should be less than or equal to 26"<<std::endl;
    std::cout<<"Enter size of battlefield : ";
    std::cin >> boardSize;
    std::cout<<"Enter number of ships : ";
    std::cin >> numberShips;
    
    int** player1 = sqMatrix(boardSize);
    int** player2 = sqMatrix(boardSize);
    
    fillMatrix(player1, (int)boardSize, (int)numberShips);
    fillMatrix(player2, (int)boardSize, (int)numberShips);
    
    updateScreen(gMessage, player1, player2, p1, p2, boardSize);
    
    while(1)
    {
//        while (1)
//        {
//            c = userInput(boardSize);
//            if (c[0] <= boardSize - 1 && c[1] <= boardSize - 1)
//            {
//                break;
//            }
//            else if (c[0] == 999 || c[1] == 999)
//            {
//                gMessage = "Invalid Entry";
//                updateScreen(gMessage, player1, player2, p1, p2, boardSize);
//            }
//            else if (player2[c[0]][c[1]] == 2 || player2[c[0]][c[1]] == 3)
//            {
//                gMessage = "Space Already Played";
//                updateScreen(gMessage, player1, player2, p1, p2, boardSize);
//            }
//            else
//            {
//                gMessage = "Out of Bounds. Try Again.";
//                updateScreen(gMessage, player1, player2, p1, p2, boardSize);
//            }
//        }
        c = new int[2];

        c[0] = autoRow;
        c[1] = autoCol;

        autoCol++;
        if (autoCol == boardSize)
        {
            autoRow++;
        }
        autoCol %= boardSize;

        usleep(0.1 * 1000000);

        turn = true;
        updateBoard(player2, c[0], c[1], boardSize);
        updateScreen(gMessage, player1, player2, p1, p2, boardSize);
        AI = AIcoordinates(player1, boardSize, gMessage2);
        turn = false;
        updateBoard(player1, AI[0], AI[1], boardSize);
//        gMessage2 = std::to_string(AIr) + " " + std::to_string(AIc);
//        usleep(0.5 * 1000000);
        updateScreen(gMessage, player1, player2, p1, p2, boardSize);
        
        if (p1 == numberShips )
        {
            ClearScreen();
            std::cout << Name1 + " Won!!! Everyone laugh at " + Name2 + "."<< std::endl;

            break;
        }
        else if (p2 == numberShips)
        {
            ClearScreen();
            std::cout << Name2 + " Won!!! I guess Elon was right..." << std::endl;
            break;
        }
    }
    return 0;
}

void ClearScreen()
{
    for (int i = 0; i < 100; i++)
    {
        std::cout<<"\n"<<std::endl;
    }
}


void printRadar(int** matrix, int size)
{
    std::string display = "";
    for (int i = 0; i < size + 1; i++)
    {
        for (int j = 0; j < size + 1; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    display += "   ";
                }
                else
                {
                   if (j < 10)
                   {
                      display += " " + std::to_string(j) + " ";
                   }
                   else
                   {
                       display += std::to_string(j) + " ";
                   }
                }
                
            }
            else if (j == 0)
            {
                display += " " + alph[i - 1] + " ";
            }
            else
            {
                if (matrix[i-1][j-1] == 0)
                {
                    display += " + ";
                }
                else if (matrix[i-1][j-1] == 1)
                {
                    display += " + ";
                    
                }
                else if (matrix[i-1][j-1] == 2)
                {
                    display += "[0]";
                }
                else if (matrix[i-1][j-1] == 3)
                {
                    display += "[X]";
                }
            }
        }
        display += "\n";
    }
    std::cout<<display<<std::endl;
}


void printWater(int** matrix, int size)
{
    std::string display = "";
    
    for (int i = 0; i < size + 1; i++)
    {
        for (int j = 0; j < size + 1; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    display += "   ";
                }
                else
                {
                    if (j < 10)
                    {
                       display += " " + std::to_string(j) + " ";
                    }
                    else
                    {
                        display += std::to_string(j) + " ";
                    }
                }
            }
            else if (j == 0)
            {
                display += " " + alph[i - 1] + " ";
            }
            else
            {
                if (matrix[i-1][j-1] == 0)
                {
                    display += " _ ";
                }
                else if (matrix[i-1][j-1] == 1)
                {
                    display += "{ }";
                }
                else if (matrix[i-1][j-1] == 2)
                {
                    display += "[0]";
                }
                else if (matrix[i-1][j-1] == 3)
                {
                    display += "{X}";
                }
            }
        }
        display += "\n";
    }
    std::cout<<display<<std::endl;
}

void printMessage(std::string message, int size)
{
    int num = (size - (int)message.length()) / 2;
    std::string tab = "";
    for (int i = 0; i < num - 1; i++)
    {
        tab += "=";
    }
    std::string m = tab + " " + message + " " + tab;
    std::cout << m << std::endl;
}

int alphIndex(std::string character)
{
    for (int i = 0; i < 26; i++)
    {
        if (alph[i] == character)
        {
            return i;
        }
    }
    return 27;
}

int * coordinates(std::string row, std::string col)
{
    int r;
    int c;
    if (std::isalpha(row[0]) == false)
    {
        r = 999;
        c = 999;
    }
    else if (std::isalpha(col[0]) == true)
    {
        r = 999;
        c = 999;
    }
    else
    {
        row = std::toupper(row[0]);
        r = alphIndex(row);
        c = std::stoi(col) - 1;
    }
    int* actual = new int[2] { r, c };
    return actual;
}

int * userInput(int size)
{
    std::string row;
    std::string col;
    int * c;
    std::cout<<"Enter Row : ";
    std::cin >> row;
    std::cout<<"Enter Column : ";
    std::cin >> col;
    c = coordinates(row, col);
    return c;
}

void printScore(int p1Score, int p2Score, int size)
{
    std::string score =  Name1 + " [ " + std::to_string(p1Score) + " ] : " + Name2 + " [ " + std::to_string(p2Score) + " ]";
    int num = (int)(size - score.length()) / 2;
    std::string tab = "";
    for (int i = 0; i < num - 1; i++)
    {
        tab += "=";
    }
    std::string m = tab + " " + score + " " + tab;
    std::cout << m << std::endl;
    
}

void updateScreen(std::string message, int** player1, int** player2, int p1Score, int p2Score, int size)
{
    ClearScreen();
    printScore(p1Score, p2Score, (size * 3) + 3);
    printRadar(player2, size);
    printMessage(message, (size * 3) + 3);
    printWater(player1, size);
}

void updateBoard(int** board, int row, int col, int size) // need to add sides
{
    if (board[row][col] == 0)
    {
        board[row][col] = 2;
        if (row >= 1 && row <= (size - 2) && col >= 1 && col <= (size - 2))
        {
            if (
                board[row][col+1]   == 1 ||
                board[row][col-1]   == 1 ||
                board[row-1][col-1] == 1 ||
                board[row-1][col+1] == 1 ||
                board[row-1][col]   == 1 ||
                board[row+1][col-1] == 1 ||
                board[row+1][col+1] == 1 ||
                board[row+1][col]   == 1
                )
            {
                if (turn == true)
                {
                    gMessage = "Near Miss";
                }
                else if (turn == false)
                {
                    gMessage2 = "Near Miss";
                }
            }
            else
            {
                if (turn == true)
                {
                    gMessage = "Miss";
                }
                else if (turn == false)
                {
                    gMessage2 = "Miss";
                }
            }
        }
        else if (row == 0 && col == 0)
        {
            if (
                board[row][col+1] == 1 ||
                board[row+1][col] == 1 ||
                board[row+1][col+1] == 1
                )
            {
                if (turn == true)
                {
                    gMessage = "Near Miss";
                }
                else if (turn == false)
                {
                    gMessage2 = "Near Miss";
                }
            }
            else
            {
                if (turn == true)
                {
                    gMessage = "Miss";
                }
                else if (turn == false)
                {
                    gMessage2 = "Miss";
                }
            }
        }
        else if (row == (size - 1) && col == 0)
        {
            if (
                board[row][col+1] == 1||
                board[row-1][col+1] == 1||
                board[row-1][col] == 1
                )
            {
                if (turn == true)
                {
                    gMessage = "Near Miss";
                }
                else if (turn == false)
                {
                    gMessage2 = "Near Miss";
                }
            }
            else
            {
                if (turn == true)
                {
                    gMessage = "Miss";
                }
                else if (turn == false)
                {
                    gMessage2 = "Miss";
                }
            }
        }
        else if (row == 0 && col == (size - 1))
        {
            if (
                board[row][col-1] == 1||
                board[row+1][col] == 1||
                board[row+1][col-1] == 1
                )
            {
                if (turn == true)
                {
                    gMessage = "Near Miss";
                }
                else if (turn == false)
                {
                    gMessage2 = "Near Miss";
                }
            }
            else
            {
                if (turn == true)
                {
                    gMessage = "Miss";
                }
                else if (turn == false)
                {
                    gMessage2 = "Miss";
                }
            }
        }
        else if (row == (size - 1) && col == (size - 1))
        {
            if (
                board[row][col-1] == 1 ||
                board[row-1][col] == 1||
                board[row-1][col-1] == 1
                )
            {
                if (turn == true)
                {
                    gMessage = "Near Miss";
                }
                else if (turn == false)
                {
                    gMessage2 = "Near Miss";
                }
            }
            else
            {
                if (turn == true)
                {
                    gMessage = "Miss";
                }
                else if (turn == false)
                {
                    gMessage2 = "Miss";
                }
            }
        }
        else if (row == 0 && col != 0 && col != (size - 1))
        {
            if (
                board[row][col-1] == 1 ||
                board[row][col+1] == 1 ||
                board[row+1][col-1] == 1||
                board[row+1][col] == 1 ||
                board[row+1][col+1] == 1
                )
            {
                if (turn == true)
                {
                    gMessage = "Near Miss";
                }
                else if (turn == false)
                {
                    gMessage2 = "Near Miss";
                }
            }
            else
            {
                if (turn == true)
                {
                    gMessage = "Miss";
                }
                else if (turn == false)
                {
                    gMessage2 = "Miss";
                }
            }
        }
        else if (row == (size - 1) && col != 0 && col != (size - 1))
        {
            if (
                board[row][col-1] == 1 ||
                board[row][col+1] == 1 ||
                board[row-1][col-1] == 1||
                board[row-1][col] == 1 ||
                board[row-1][col+1] == 1
                )
            {
                if (turn == true)
                {
                    gMessage = "Near Miss";
                }
                else if (turn == false)
                {
                    gMessage2 = "Near Miss";
                }
            }
            else
            {
                if (turn == true)
                {
                    gMessage = "Miss";
                }
                else if (turn == false)
                {
                    gMessage2 = "Miss";
                }
            }
        }
        else if (col == 0 && row != 0 && row != (size - 1))
        {
            if (
                board[row-1][col] == 1 ||
                board[row+1][col] == 1 ||
                board[row-1][col+1] == 1||
                board[row][col+1] == 1 ||
                board[row+1][col+1] == 1
                )
            {
                if (turn == true)
                {
                    gMessage = "Near Miss";
                }
                else if (turn == false)
                {
                    gMessage2 = "Near Miss";
                }
            }
            else
            {
                if (turn == true)
                {
                    gMessage = "Miss";
                }
                else if (turn == false)
                {
                    gMessage2 = "Miss";
                }
            }
        }
        else if (col == (size - 1) && row != 0 && row != (size - 1))
        {
            if (
                board[row-1][col] == 1 ||
                board[row+1][col] == 1 ||
                board[row-1][col-1] == 1||
                board[row][col-1] == 1 ||
                board[row+1][col-1] == 1
                )
            {
                if (turn == true)
                {
                    gMessage = "Near Miss";
                }
                else if (turn == false)
                {
                    gMessage2 = "Near Miss";
                }
            }
            else
            {
                if (turn == true)
                {
                    gMessage = "Miss";
                }
                else if (turn == false)
                {
                    gMessage2 = "Miss";
                }
            }
        }
    }
    else if (board[row][col] == 1)
    {
        board[row][col] = 3;
        if (turn == true)
        {
            gMessage = "Direct Hit!!";
            p1++;
        }
        else if (turn == false)
        {
            gMessage2 = "Direct Hit!!";
            p2++;
        }
    }
}

int * AIcoordinates(int ** board, int size, std::string message)
{
    int count = 0;
    if (AIr == 888 && AIc == 888)
    {
        AIr = rand() % size;
        AIc = rand() % size;
    }
    while(1)
    {
        count = 0;
        if (message == "Near Miss")
        {
            if (AIr >= 1 && AIr <= (size - 2) && AIc >= 1 && AIc <= (size - 2))
            {
                count = 0;
                while(1)
                {
                    std::cout<<"1 " + std::to_string(AIr) + " " + std::to_string(AIc)<<std::endl;
                    AIr = rand() % 3 + (AIr-1);
                    AIc = rand() % 3 + (AIc-1);
                    if (board[AIr][AIc] == 0 || board[AIr][AIc] == 1)
                    {
                        break;
                    }
                    else if (count == 9)
                    {
                        break;
                    }
                    else
                    {
                        count++;
                    }
                }
                            }
            else if (AIr == 0 && AIc == 0)
            {
                count = 0;
                while(1)
                {
                    AIr = rand() % 2 + AIr;
                    AIc = rand() % 2 + AIc;
                    if (board[AIr][AIc] == 0 || board[AIr][AIc] == 1)
                    {
                        break;
                    }
                    else if (count == 4)
                    {
                        break;
                    }
                    else
                    {
                        count++;
                    }
                    std::cout<<"2 " + std::to_string(AIr) + " " + std::to_string(AIc)<<std::endl;
                }
            }
            else if (AIr == (size - 1) && AIc == 0)
            {
                count = 0;
                while(1)
                {
                    AIr = rand() % 2 + (AIr-1);
                    AIc = rand() % 2 + (AIc);
                    if (board[AIr][AIc] == 0 || board[AIr][AIc] == 1)
                    {
                        break;
                    }
                    else if (count == 4)
                    {
                        break;
                    }
                    else
                    {
                        count++;
                    }
                    std::cout<<"3 " + std::to_string(AIr) + " " + std::to_string(AIc)<<std::endl;
                }
            }
            else if (AIr == 0 && AIc == (size - 1))
            {
                count = 0;
                while(1)
                {
                    AIr = rand() % 2 + AIr;
                    AIc = rand() % 2 + (AIc-1);
                    if (board[AIr][AIc] == 0 || board[AIr][AIc] == 1)
                    {
                        break;
                    }
                    else if (count == 4)
                    {
                        break;
                    }
                    else
                    {
                        count++;
                    }
                    std::cout<<"4 " + std::to_string(AIr) + " " + std::to_string(AIc)<<std::endl;
                }
            }
            else if (AIr == (size - 1) && AIc == (size - 1))
            {
                count = 0;
                while(1)
                {
                    AIr = rand() % 2 + (AIr-1);
                    AIc = rand() % 2 + (AIc-1);
                    if (board[AIr][AIc] == 0 || board[AIr][AIc] == 1)
                    {
                        break;
                    }
                    else if (count == 4)
                    {
                        count = 0;
                        break;
                    }
                    else
                    {
                        count++;
                    }
                    std::cout<<"5 " + std::to_string(AIr) + " " + std::to_string(AIc)<<std::endl;
                }
            }
            else if (AIr == 0 && AIc != 0 && AIc != (size - 1)) // rows top and bottom
            {
                count = 0;
                while(1)
                {
                    
                    AIr = rand() % 2 + AIr;
                    AIc = rand() % 3 + (AIc - 1);
                    if (board[AIr][AIc] == 0 || board[AIr][AIc] == 1)
                    {
                        break;
                    }
                    else if (count == 6)
                    {
                        break;
                    }
                    else
                    {
                        count++;
                    }
                    std::cout<<"6 " + std::to_string(AIr) + " " + std::to_string(AIc)<<std::endl;
                }
            }
            else if (AIr == (size - 1) && AIc != 0 && AIc != (size - 1))
            {
                count = 0;
                while(1)
                {
                    
                    AIr = rand() % 2 + (AIr-1);
                    AIc = rand() % 3 + (AIc-1);
                    if (board[AIr][AIc] == 0 || board[AIr][AIc] == 1)
                    {
                        break;
                    }
                    else if (count == 6)
                    {
                        break;
                    }
                    else
                    {
                        count++;
                    }
                    std::cout<<"7 " + std::to_string(AIr) + " " + std::to_string(AIc)<<std::endl;
                }
            }
            else if (AIc == 0 && AIr != 0 && AIc != (size - 1))
            {
                count = 0;
                while(1)
                {
                    AIr = rand() % 3 + (AIr-1);
                    AIc = rand() % 2 + (AIc);
                    if (board[AIr][AIc] == 0 || board[AIr][AIc] == 1)
                    {
                        break;
                    }
                    else if (count == 6)
                    {
                        break;
                    }
                    else
                    {
                        count++;
                    }
                    std::cout<<"8 " + std::to_string(AIr) + " " + std::to_string(AIc)<<std::endl;
                }
            }
            else if (AIc == (size - 1) && AIr != 0 && AIc != (size - 1))
            {
                count = 0;
                while(1)
                {
                    
                    AIr = rand() % 3 + (AIr-1);
                    AIc = rand() % 2 + (AIc-1);
                    if (board[AIr][AIc] == 0 || board[AIr][AIc] == 1)
                    {
                        break;
                    }
                    else if (count == 6)
                    {
                        break;
                    }
                    else
                    {
                        count++;
                    }
                    std::cout<<"9 " + std::to_string(AIr) + " " + std::to_string(AIc)<<std::endl;
                }
            }
        }
        else
        {
            AIr = rand() % (size-1);
            AIc = rand() % (size-1);
            std::cout<<"Else " + std::to_string(AIr) + " " + std::to_string(AIc)<<std::endl;
        }
        if (board[AIr][AIc] == 0 || board[AIr][AIc] == 1)
        {
            break;
        }
        std::cout<<"endless " + std::to_string(AIr) + " " + std::to_string(AIc)<<std::endl;
        count++;
        if (count == 1)
        {
            AIr = rand() % (size-1);
            AIc = rand() % (size-1);
        }
    }
    int* AIC = new int[2] { AIr, AIc };
    return AIC;
}


