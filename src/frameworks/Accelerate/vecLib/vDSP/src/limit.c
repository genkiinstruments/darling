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

void vDSP_vclip(const float *__A, vDSP_Stride __IA, const float *__B, const float *__C, float *__D, vDSP_Stride __ID, vDSP_Length __N)
{
    #pragma clang loop vectorize(enable)
    for (int n = 0; n < __N; ++n)
    {
        if (__A[n * __IA] < *__B)
            __D[n * __ID] = *__B;
        else if (__A[n * __IA] > *__C)
            __D[n * __ID] = *__C;
        else
            __D[n * __ID] = __A[n * __IA];
    }
}

void vDSP_vclipD(const double *__A, vDSP_Stride __IA, const double *__B, const double *__C, double *__D, vDSP_Stride __ID, vDSP_Length __N)
{
    #pragma clang loop vectorize(enable)
    for (int n = 0; n < __N; ++n)
    {
        if (__A[n * __IA] < *__B)
            __D[n * __ID] = *__B;
        else if (__A[n * __IA] > *__C)
            __D[n * __ID] = *__C;
        else
            __D[n * __ID] = __A[n * __IA];
    }
}

void vDSP_vclr(float *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    #pragma clang loop vectorize(enable)
    for (int n = 0; n < __N; ++n)
        __C[n * __IC] = 0.0f;
}

void vDSP_vclrD(double *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    #pragma clang loop vectorize(enable)
    for (int n = 0; n < __N; ++n)
        __C[n * __IC] = 0.0;
}

