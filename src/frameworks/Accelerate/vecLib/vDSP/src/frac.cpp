#include <vDSP/vDSP.h>
#include <numeric>

template <typename FloatType>
void impl(const FloatType *__A, vDSP_Stride __IA, FloatType *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    #pragma clang loop vectorize(enable)
    for (vDSP_Length n = 0; n < __N; ++n)
        __C[n * __IC] = __A[n * __IA] - std::trunc(__A[n * __IA]);
}

void vDSP_vfrac(const float *__A, vDSP_Stride __IA, float *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N);
}

void vDSP_vfracD(const double *__A, vDSP_Stride __IA, double *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    impl(__A, __IA, __C, __IC, __N);
}
