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

#include <stdlib.h>
#include "linalg.h"

static float heap[HEAPSIZE];
static float* heap_ptr; 

int mat_malloc_init()
{
	static int init = 0;
	if(init==0)
	{
		init = 1;
		heap_ptr = heap;
	} else 
	{
		return MAT_WARNING; // Already called
	}
	return 0;
}

int mat_release()
{
	heap_ptr = &heap[0];
	return 0;
}

float* mat_malloc(unsigned int length)
{
	float* ptr = heap_ptr;
	ptr += length;
	if (ptr >= heap + HEAPSIZE)
	{
		return NULL;
	}
	heap_ptr += length;
	return ptr;
}

int mat_init(const Index nrows, const Index ncolumns, Matrix* matrix, float val)
{
	matrix->rows = nrows;
	matrix->columns = ncolumns;
	matrix->data = mat_malloc(nrows*ncolumns*sizeof(float));

	if (matrix->data == NULL)
	{
		return MAT_ERR_MALLOC;
	}

	Index i;
	Index j;
	for (i = matrix->rows; i > 0; i--)
	{
		for (j = matrix->columns; j > 0; j--)
		{
			matrix->data[(matrix->rows-i+1)*matrix->columns-j] = val;
		}
	}

	return MAT_SUCCESS;
}


int mat_add(const Matrix* lhs, const Matrix* rhs, Matrix *res)
{
	if ((lhs->rows != rhs->rows) || (lhs->columns != rhs->columns))
	{
		return MAT_ERR_DIM;
	}

	if ((lhs->rows != res->rows) || (lhs->columns != res->columns))
	{
		return MAT_ERR_DIM;
	}

	Index i;
	Index j;
	for (i = res->rows; i > 0; i--)
	{
		for (j = res->columns; j > 0; j--)
		{
			Index idx = (res->rows-i+1)*res->columns-j;
			res->data[idx] = lhs->data[idx] + rhs->data[idx];
		}
	}
	
	return MAT_SUCCESS;
}

int mat_multiply(const Matrix* lhs, const Matrix* rhs, Matrix* res)
{
	if (lhs->columns != rhs->rows)
	{
		return MAT_ERR_DIM;
	}

	if ((lhs->rows != res->rows) || (rhs->columns != res->columns))
	{
		return MAT_ERR_DIM;
	}

	Index i, j;
	for (i = res->rows; i > 0; i--)
	{
		for (j = res->columns; j > 0; j--)
		{
			Index k;
			float retval = 0;
			for(k = lhs->columns; k>0; k--)
			{
				float prod = lhs->data[(lhs->rows-i)*lhs->columns + (lhs->columns - k)] * rhs->data[(rhs->columns-j)+rhs->rows - k];
				retval += prod;
			}
			res->data[(res->rows-i+1)*res->columns-j] = retval;
		}
	}

	return MAT_SUCCESS;
}

int mat_transpose(const Matrix* m, Matrix* res)
{
	if ( (m->rows != res->columns) || (m->columns != res->rows) )
	{
		return MAT_ERR_DIM;
	}

	Index i,j;
	for ( i = m->rows; i>0; i--)
	{
		for ( j = m->columns; j>0; j--)
		{
			res->data[(m->columns-j+1)*m->rows-i] = m->data[(m->rows-i+1)*m->columns-j];
		}
	}

	return MAT_SUCCESS;
}

int mat_inverse(const Matrix* m, Matrix* res)
{

	if (m->rows != m->columns)
	{
		return MAT_ERR_DIM;
	}

	if (m->rows > 2)
	{
		return MAT_NOT_IMPLEMENTED;
	}

	if ( (m->rows != res->rows) || (m->columns != res->columns))
	{
		return MAT_ERR_DIM;
	}

	float det = ( (m->data[0]*m->data[3]) - (m->data[2]*m->data[1]) );

	if (det == 0)
	{
		return MAT_ERR_DIV0;
	}

	res->data[0] = m->data[3]/det;
	res->data[1] = -1*(m->data[1]/det);
	res->data[2] = -1*(m->data[2]/det);
	res->data[3] = m->data[0]/det;

	return MAT_SUCCESS;
}