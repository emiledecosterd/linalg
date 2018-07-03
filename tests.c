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

#include "tests.h"

void mat_print(const Matrix *m)
{
	Index i;
	Index j;

	printf("[\r\n");
	for (i = m->rows; i>0; i--)
	{
		for (j = m->columns; j>0; j--)
		{
			printf("%0.2f ",m->data[(m->rows-i+1)*m->columns-j]);
		}
		printf("\r\n");
	}
	printf("]\r\n");

}

int test_mat_init()
{
	Matrix m;
	int res = mat_init(2,2,&m,2);

	mat_print(&m);

	if (res != MAT_SUCCESS)
	{
		return FAIL;
	}

	if( m.data[0] != 2 )
	{
		return FAIL;
	}

	return PASS;

}

int test_mat_add()
{
	Matrix m;
	mat_init(2,2,&m,0);

	Matrix m1;
	mat_init(2,2,&m1,1);

	Matrix m2;
	mat_init(2,2,&m2,2);

	int res = mat_add(&m1,&m2,&m);

	printf("A  = ");
	mat_print(&m1);
	printf("B  = ");
	mat_print(&m2);

	if (res != MAT_SUCCESS)
	{
		return FAIL;
	}

	if( m.data[0] != 3 )
	{
		return FAIL;
	}

	printf("A + B = ");
	mat_print(&m);

	return PASS;
}

int test_mat_multiply()
{
	Matrix m;
	mat_init(2,2,&m,0);

	Matrix m1;
	mat_init(2,3,&m1,1);

	Matrix m2;
	mat_init(3,2,&m2,2);

	int res = mat_multiply(&m1,&m2,&m);

	printf("A  = ");
	mat_print(&m1);
	printf("B  = ");
	mat_print(&m2);

	if (res != MAT_SUCCESS)
	{
		return FAIL;
	}

	if( m.data[0] != 6.0 )
	{
		printf("%0.2f",m.data[0]);
		return FAIL;
	}

	printf("A * B = ");
	mat_print(&m);

	return PASS;
}

int test_mat_transpose()
{
	Matrix m;
	mat_init(3,2,&m,0);

	Index i,j;
	for(i=0;i<m.rows*m.columns;i++)
	{
		m.data[i] = (float)i;
	}

	Matrix mt;
	mat_init(2,3,&mt,1);

	int res = mat_transpose(&m,&mt);

	printf("A  = ");
	mat_print(&m);
	printf("A^T  = ");
	mat_print(&mt);

	if (res != MAT_SUCCESS)
	{
		return FAIL;
	}
	
	for(i=0;i<m.rows;i++)
	{
		for(j=0;j<m.columns;j++)
		{
			if( m.data[i*m.columns+j] != mt.data[j*m.rows+i] )
			{
				return FAIL;
			}
		}
	}	

	printf("A^T = ");
	mat_print(&mt);

	return PASS;
}

int test_mat_inverse()
{
	Matrix m;
	mat_init(2,2,&m,0);

	Index i;
	for(i=0;i<m.rows*m.columns;i++)
	{
		m.data[i] = (float)i;
	}
	//m.data[2] = 0;

	Matrix inv;
	mat_init(2,2,&inv,1);

	int res = mat_inverse(&m,&inv);

	Matrix invinv;
	mat_init(2,2,&invinv,0);

	mat_inverse(&inv,&invinv);

	printf("A  = ");
	mat_print(&m);
	printf("inv(A)  = ");
	mat_print(&inv);
	printf("inv(inv(A)) = ");
	mat_print(&invinv);

	if (res != MAT_SUCCESS)
	{
		if (res == MAT_ERR_DIM)
		{
			printf("Dimensions error!\r\n");
		} else if (res == MAT_NOT_IMPLEMENTED)
		{
			printf("Inversion for matrices > 2x2 not yet implemented\r\n");
		} else if (res == MAT_ERR_DIV0)
		{
			printf("Determinant is zero!!\r\n");
		}
		return FAIL;
	}	

	return PASS;
}