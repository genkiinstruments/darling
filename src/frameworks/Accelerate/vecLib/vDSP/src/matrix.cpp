#include <vDSP/vDSP.h>
#include <cstring>

template <typename FloatType>
void impl(const FloatType *__A, FloatType *__C, vDSP_Length __M, vDSP_Length __N, vDSP_Length __TA, vDSP_Length __TC)
{
    #pragma clang loop vectorize(enable)
    for (vDSP_Length n = 0; n < __N; ++n)
        std::memcpy(&__C[n], &__A[n], __M);
}

void vDSP_mmov(const float *__A, float *__C, vDSP_Length __M, vDSP_Length __N, vDSP_Length __TA, vDSP_Length __TC)
{
    impl<float>(__A, __C, __M, __N, __TA, __TC);
}

void vDSP_mmovD(const double *__A, double *__C, vDSP_Length __M, vDSP_Length __N, vDSP_Length __TA, vDSP_Length __TC)
{
    impl<double>(__A, __C, __M, __N, __TA, __TC);
}
