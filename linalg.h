/*
 *	Basic Linear Algebra Library for Embedded Applications
 *	Copyright (C) 2018  Emile Décosterd
 *
 *	This file is part of linalg
 *
 *	linalg is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	linalg is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef _LINALG_H_
#define _LINALG_H_

#define MAT_NUMBER 25
#define MAT_NELEM 4
#define MAT_SIZE 32
#define HEAPSIZE MAT_NUMBER*MAT_NELEM*MAT_SIZE

#define MAT_SUCCESS		0
#define MAT_WARNING		1
#define MAT_ERR_MALLOC	-1
#define MAT_ERR_DIM		-2
#define MAT_ERR_DIV0	-3
#define MAT_NOT_IMPLEMENTED -100

typedef unsigned int Index;

typedef struct {
	Index rows;
	Index columns;
	float *data;
} Matrix;

/**
 * 	@brief	initializes the matrix heap pointer: run only one time.
 *	@return status of the operation.
 */
int mat_malloc_init();

/**
 * 	@brief	releases the memory: sets the heap pointer to the beginning of the heap.
 */
int mat_release();

/**
 * 	@brief			allocates memory for a matrix data.
 *	@param	length	the length of the memory to be allocated.
 *	@return			a pointer to the first memory location allocated. 
 */
float* mat_malloc(unsigned int length);

/**
 * 	@brief				initializes a matrix.
 *	@param	nrows		number of rows in the matrix,
 *	@param	ncolumns	number of columns in the matrix,
 *	@param	matrix		an empty matrix structure.
 *	@param	val			the initial value.
 *	@return				status of the operation
 */
int mat_init(const Index nrows, const Index ncolumns, Matrix* matrix, float val);


/**
 * 	@brief			matrix addition, element by element.
 *	@param	lhs		left hand side operand,
 *	@param	rhs		right hand side operand,
 *	@param	res		an empty matrix structure.
 *	@return			status of the operation
 */
int mat_add(const Matrix* lhs, const Matrix* rhs, Matrix* res);

/**
 * 	@brief			matrix multiplication.
 *	@param	lhs		left hand side operand,
 *	@param	rhs		right hand side operand,
 *	@param	res		an empty matrix structure.
 *	@return			status of the operation
 */
int mat_multiply(const Matrix* lhs, const Matrix* rhs, Matrix* res);

/**
 * 	@brief			matrix transpose.
 *	@param	m		matrix to transpose
 *	@param	res		an empty matrix structure.
 *	@return			status of the operation
 */
int mat_transpose(const Matrix* m, Matrix* res);

/**
 * 	@brief			matrix inversion. For now only for 2x2 matrices!!.
 *	@param	m		matrix to inverse
 *	@param	res		an empty matrix structure.
 *	@return			status of the operation
 */
int mat_inverse(const Matrix *m, Matrix* res);

#endif