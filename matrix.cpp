//
//  matrix.cpp
//  Battleship++
//
//  Created by Patrick Tumulty on 10/23/19.
//  Copyright © 2019 Patrick Tumulty. All rights reserved.
//

#include "matrix.hpp"
#include <iostream>

int** sqMatrix(const int size)
{
    int** m = new int*[size];
    for (int i = 0; i < size; i++)
    {
        m[i] = new int[size];
    }
    return m;
}

void fillMatrix(int** matrix, int matrixSize, int ships)
{
    int r1;
    int r2;
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < ships; i++)
    {
        while(1)
        {
            r1 = rand() % (matrixSize - 1);
            r2 = rand() % (matrixSize - 1);
            if (matrix[r1][r2] == 0)
            {
                matrix[r1][r2] = 1;
                break;
            }
        }
    }
}
