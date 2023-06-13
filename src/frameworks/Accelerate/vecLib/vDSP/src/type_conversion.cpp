#include <vDSP/vDSP.h>
#include <numeric>

//======================================================================================================================
template <typename FloatType, typename ResultType>
void impl(const FloatType *__A, vDSP_Stride __IA, ResultType *__C, vDSP_Stride __IC, vDSP_Length __N, FloatType (*conv)(FloatType))
{
    #pragma clang loop vectorize(enable)
    for (vDSP_Length n = 0; n < __N; ++n)
        __C[n * __IC] = static_cast<ResultType>(conv(__A[n * __IA]));
}

//======================================================================================================================
// 8-bit results
void vDSP_vfix8(const float *__A, vDSP_Stride __IA, char *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::floor);
}

void vDSP_vfix8D(const double *__A, vDSP_Stride __IA, char *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::floor);
}

void vDSP_vfixr8(const float *__A, vDSP_Stride __IA, char *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::round);
}

void vDSP_vfixr8D(const double *__A, vDSP_Stride __IA, char *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::round);
}

void vDSP_vfixu8(const float *__A, vDSP_Stride __IA, unsigned char *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::floor);
}

void vDSP_vfixu8D(const double *__A, vDSP_Stride __IA, unsigned char *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::floor);
}

void vDSP_vfixru8(const float *__A, vDSP_Stride __IA, unsigned char *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::round);
}

void vDSP_vfixru8D(const double *__A, vDSP_Stride __IA, unsigned char *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::round);
}

//======================================================================================================================
// 16-bit results
void vDSP_vfix16(const float *__A, vDSP_Stride __IA, short *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::floor);
}

void vDSP_vfix16D(const double *__A, vDSP_Stride __IA, short *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::floor);
}

void vDSP_vfixr16(const float *__A, vDSP_Stride __IA, short *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::round);
}

void vDSP_vfixr16D(const double *__A, vDSP_Stride __IA, short *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::round);
}

void vDSP_vfixu16(const float *__A, vDSP_Stride __IA, unsigned short *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::floor);
}

void vDSP_vfixu16D(const float *__A, vDSP_Stride __IA, unsigned short *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::floor);
}

void vDSP_vfixru16(const float *__A, vDSP_Stride __IA, unsigned short *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::round);
}

void vDSP_vfixru16D(const float *__A, vDSP_Stride __IA, unsigned short *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::round);
}

//======================================================================================================================
// 32-bit results
void vDSP_vfix32(const float *__A, vDSP_Stride __IA, int *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::floor);
}

void vDSP_vfix32D(const double *__A, vDSP_Stride __IA, int *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::floor);
}

void vDSP_vfixr32(const float *__A, vDSP_Stride __IA, int *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::round);
}

void vDSP_vfixr32D(const double *__A, vDSP_Stride __IA, int *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::round);
}

void vDSP_vfixu32(const float *__A, vDSP_Stride __IA, unsigned int *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::floor);
}

void vDSP_vfixu32D(const double *__A, vDSP_Stride __IA, unsigned int *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::floor);
}

void vDSP_vfixru32(const float *__A, vDSP_Stride __IA, unsigned int *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::round);
}

void vDSP_vfixru32D(const double *__A, vDSP_Stride __IA, unsigned int *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N, std::round);
}
