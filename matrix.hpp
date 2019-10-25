//
//  matrix.hpp
//  Battleship++
//
//  Created by Patrick Tumulty on 10/23/19.
//  Copyright © 2019 Patrick Tumulty. All rights reserved.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <stdio.h>

int** sqMatrix(const int size);

void fillMatrix(int** matrix, int matrixSize, int ships);

#endif /* matrix_hpp */
