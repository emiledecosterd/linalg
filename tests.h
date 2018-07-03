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

#define PASS 0
#define FAIL 1

void mat_print(const Matrix *m);

int test_mat_init();
int test_mat_add();
int test_mat_multiply();
int test_mat_transpose();
int test_mat_inverse();