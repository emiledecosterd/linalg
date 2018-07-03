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

#include <stdio.h>
#include "linalg.h"
#include "tests.h"

void print_test_status(const char* test, int result);

int main()
{

	mat_malloc_init();

	int status = PASS;
	
	// Matrix initialization
	status = test_mat_init();
	print_test_status("mat_init",status);

	// Matrix addition
	status = test_mat_add();
	print_test_status("mat_add",status);

	// Matrix multiplication
	status = test_mat_multiply();
	print_test_status("mat_multiply",status);

	// Matrix transpose
	status = test_mat_transpose();
	print_test_status("mat_transpose",status);

	// Matrix inversion
	status = test_mat_inverse();
	print_test_status("mat_inverse",status);

	mat_release();

	return 0;
}

void print_test_status(const char* test, int result)
{
	char* status = "PASS";
	if(result != 0)
	{
		status = "FAIL";
	}

	printf("Test status for %s: %s\r\n", test, status);

}