/*
 This file is part of Darling.

 Copyright (C) 2020 Lubos Dolezel

 Darling is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Darling is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Darling.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <vDSP/vDSP.h>

void vDSP_vsadd(const float *__A, vDSP_Stride __IA, const float *__B, float *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    #pragma clang loop vectorize(enable)
    for (vDSP_Length i = 0; i < __N; i++)
        __C[i * __IC] = __A[i * __IA] + __B[0];
}

void vDSP_vsmul(const float *__A, vDSP_Stride __IA, const float *__B, float *__C, vDSP_Stride __IC, vDSP_Length __N)
{
	#pragma clang loop vectorize(enable)
    for (int n = 0; n < __N; ++n)
        __C[n] = __A[n] * __B[0];
}

void vDSP_vsmulD(const double *__A, vDSP_Stride  __IA, const double *__B, double *__C, vDSP_Stride  __IC, vDSP_Length  __N)
{
	#pragma clang loop vectorize(enable)
    for (int n = 0; n < __N; ++n)
        __C[n * __IC] = __A[n * __IA] * __B[0];
}

