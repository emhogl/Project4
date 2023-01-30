
#include "Matrix.h"
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
using namespace std;

Matrix::Matrix(){
 rowsNum=3;
 colsNum=3;
 matrixData=NULL;
 matrixData = (int**)malloc(rowsNum*sizeof(int*));

    // Allocate rows for fake "2D array":
    for (int i = 0 ; i < rowsNum ; ++i )
    {
       matrixData[i] = (int*) malloc(colsNum*sizeof(int));
    }

    for (int i = 0 ; i < rowsNum ; ++i )
    	for (int j = 0 ; j < colsNum ; ++j )
    		matrixData[i][j]=0;
}

Matrix::Matrix( int row, int col ){

	/*
	* constructs a row-by-col matrix with
	* all elements equal to 0; if row ≤ 0, the number of rows of the matrix is set to
	* 3; likewise, if col ≤ 0 the number of columns of the matrix is set to 3.
	*/

    rowsNum = row; //define number of rows
    colsNum = col; //define number of columns
    matrixData = NULL; //set data to null

    if (row<=0) {
        rowsNum = 3; // if rows are 0 or below 0, set to 3
    }

    if (col<=0) {
        colsNum = 3; // if columns are 0 or below 0, set to 3
    }

    matrixData = (int**) malloc(rowsNum*sizeof(int*)); //allocate memory for the rows
    for (int i=0; i < rowsNum; i++) { //i is the index for the for loop, running from 0 up until the number of rows
        matrixData[i] = (int*) malloc(colsNum*sizeof(int)); //allocate memory for the columns
    }

    for (int i = 0; i < rowsNum; i++) { //i is the index for the for loop, running from 0 up until the number of rows
        for (int j= 0; j < colsNum; j++) { //j is the index for the for loop, running from 0 up until the number of columns
            matrixData[i][j] = 0; //set that entry to 0

        }
    }

}


Matrix::Matrix(int row, int col, int** table){

	/*
	* constructs a matrix out of the two dimensional array table, with the same number of rows, columns, and the same
	* element in each position as array table.
	*/

	rowsNum = row; //define number of rows
	colsNum = col; //define number of columns
	matrixData = NULL; //set data to null

    matrixData = (int**) malloc(rowsNum*sizeof(int*)); //allocate memory for the rows
    for (int i=0; i < rowsNum; i++) { //i is the index for the for loop, running from 0 up until the number of rows
        matrixData[i] = (int*) malloc(colsNum*sizeof(int)); //allocate memory for the columns
    }

    for (int i = 0; i < rowsNum; i++) { //i is the index for the for loop, running from 0 up until the number of rows
        for (int j= 0; j < colsNum; j++) { //j is the index for the for loop, running from 0 up until the number of columns
            matrixData[i][j] = table[i][j]; //set that entry to the corresponding entry from table
        }
    }
}

int Matrix::getElement(int i, int j){

    if (i > rowsNum || j > colsNum) { //if i and j are invalid index, give error message
        throw std::out_of_range ("Invalid indexes.");
    }

    else {
        return matrixData[i][j]; //return the element at that entry
    }

}

bool Matrix::setElement(int x, int i, int j){

    if (i > rowsNum || j > colsNum) { //if i and j are invalid index, return false and do not change matrix
        return false;
    }

    else {
        matrixData[i][j] = x; //set entry at row i and column j to x
        return true;
    }
}




Matrix Matrix::copy(){

	/* fix the code and write your implementation below */

    Matrix copy =  Matrix(rowsNum, colsNum); //copy is an instance with number of rows and columns given by input variables

    for(int i = 0; i < rowsNum; i++) { //i is the index for the for loop, running from 0 up until the number of rows
        for(int j = 0; j < colsNum; j++) { //j is the index for the for loop, running from 0 up until the number of columns
            copy.matrixData[i][j]  = matrixData[i][j]; //enter the element from matrix Data into the deep copy matrix
        }
    }

    return  copy; //return an instance in the method


}





void Matrix::addTo( Matrix m ){

    if (m.rowsNum == rowsNum && m.colsNum == colsNum) { //only add if number of rows and columns of both matrices match
	    for (int i = 0; i < rowsNum; i++) { //i is the index for the for loop, running from 0 up until the number of rows
	        for (int j = 0; j < colsNum; j++) { //j is the index for the for loop, running from 0 up until the number of columns
	            matrixData[i][j] += m.matrixData[i][j]; //add the data from matrix m to this matrix
	        }
	    }
	}

	else {
	    throw std::invalid_argument ("Invalid operation"); //if the number of rows and columns do not match then give error
	}

	
}


Matrix Matrix::subMatrix(int i, int j){

	/* The exception detail message should read: "Submatrix not defined"*/

	/* fix the code and write your implementation below */
	Matrix subM = Matrix ((i+1),(j+1)); //i and j correspond to index, so number of rows is one greater; create submatrix

    if ((i+1) > rowsNum || (j+1) > colsNum) { //if the entered values are not defined within the range of this matrix, then return error message
        throw std::out_of_range("Submatrix not defined");
    }

    for (int ii=0; ii<(i+1); ii++) { //ii is the index for the for loop, running from 0 up until the number of rows
        for (int jj=0; jj<(j+1); jj++) { //jj is the index for the for loop, running from 0 up until the number of columns
            subM.matrixData[ii][jj] = matrixData[ii][jj]; //enter the matrixData value into the submatrix
        }
    }
    
    return  subM; //return the instance
}


int Matrix::getsizeofrows(){

	
	/* update below return */
	return rowsNum; //simply return the number of rows
}


int Matrix::getsizeofcols(){



	/* update below return */
    return colsNum; //simply return the number of columns
}


bool Matrix::isUpperTr(){

	/* write your implementation here and update return accordingly */
	
	for (int i = 1; i < rowsNum; i++) { //i is the index for the for loop, running from 1 up until the number of rows
	    for (int j = 0; j < colsNum; j++) { //j is the index for the for loop, running from 0 up until the number of columns
	        if (j<i && matrixData[i][j] != 0) { //if the number of columns is less than the number of rows and the entry is not 0, then the matrix is not upper triangular
	            return false;
	        }
	    }
	}

	return true; //otherwise, the matrix is upper triangular; therefore, return true
}


string Matrix::toString(){

	string output=""; //initialize output

	for (int i=0; i < rowsNum; i++) { //i is the index for the for loop, running from 0 up until the number of rows
	    for(int j=0; j < colsNum; j++) { //j is the index for the for loop, running from 0 up until the number of columns
	        output += to_string(matrixData[i][j]) + " "; //add the element as a string as well as a space to output
	    }
	    output += "\n"; //conclude with a new line
	}

	//return output
	 return output;
}

