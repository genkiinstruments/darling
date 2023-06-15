#include <vDSP/vDSP.h>

//======================================================================================================================
// Binary operations
template <typename FloatType, typename BinaryOp>
void binary_impl(const FloatType *__A, vDSP_Stride __IA, const FloatType *__B, vDSP_Stride __IB, FloatType *__C, vDSP_Stride __IC, vDSP_Length __N, BinaryOp op)
{
    #pragma clang loop vectorize(enable)
    for (vDSP_Length n = 0; n < __N; ++n)
        __C[n * __IC] = op(__A[n * __IA], __B[n * __IA]);
}

constexpr auto add = [](auto a, auto b) { return a + b; };
constexpr auto sub = [](auto a, auto b) { return a - b; };
constexpr auto mul = [](auto a, auto b) { return a * b; };
constexpr auto div = [](auto a, auto b) { return a / b; };

void vDSP_vadd(const float *__A, vDSP_Stride __IA, const float *__B, vDSP_Stride __IB, float *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    binary_impl(__A, __IA, __B, __IB, __C, __IC, __N, add);
}

void vDSP_vaddD(const double *__A, vDSP_Stride __IA, const double *__B, vDSP_Stride __IB, double *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    binary_impl(__A, __IA, __B, __IB, __C, __IC, __N, add);
}

void vDSP_vsub(const float *__B, vDSP_Stride __IB, const float *__A, vDSP_Stride __IA, float *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    binary_impl(__A, __IA, __B, __IB, __C, __IC, __N, sub);
}

void vDSP_vsubD(const double *__B, vDSP_Stride __IB, const double *__A, vDSP_Stride __IA, double *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    binary_impl(__A, __IA, __B, __IB, __C, __IC, __N, sub);
}

void vDSP_vmul(const float *__A, vDSP_Stride __IA, const float *__B, vDSP_Stride __IB, float *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    binary_impl(__A, __IA, __B, __IB, __C, __IC, __N, mul);
}

void vDSP_vmulD(const double *__A, vDSP_Stride __IA, const double *__B, vDSP_Stride __IB, double *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    binary_impl(__A, __IA, __B, __IB, __C, __IC, __N, mul);
}

void vDSP_vdiv(const float *__B, vDSP_Stride __IB, const float *__A, vDSP_Stride __IA, float *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    binary_impl(__A, __IA, __B, __IB, __C, __IC, __N, div);
}

void vDSP_vdivD(const double *__B, vDSP_Stride __IB, const double *__A, vDSP_Stride __IA, double *__C, vDSP_Stride __IC, vDSP_Length __N)
{
    binary_impl(__A, __IA, __B, __IB, __C, __IC, __N, div);
}

//======================================================================================================================
// Ternary operations
template <typename FloatType, typename TernaryOp>
void ternary_impl(const FloatType *__A, vDSP_Stride __IA, const FloatType *__B, vDSP_Stride __IB, const FloatType *__C, vDSP_Stride __IC, FloatType *__D, vDSP_Stride __ID, vDSP_Length __N, TernaryOp op)
{
    #pragma clang loop vectorize(enable)
    for (vDSP_Length n = 0; n < __N; ++n)
        __D[n * __ID] = op(__A[n * __IA], __B[n * __IA], __C[n * __IC]);
}

constexpr auto add_multiply = [](auto a, auto b, auto c) { return (a + b) * c; };
constexpr auto sub_multiply = [](auto a, auto b, auto c) { return (a - b) * c; };
constexpr auto multiply_add = [](auto a, auto b, auto c) { return a * b + c; };
constexpr auto multiply_sub = [](auto a, auto b, auto c) { return a * b - c; };

void vDSP_vam(const float *__A, vDSP_Stride __IA, const float *__B, vDSP_Stride __IB, const float *__C, vDSP_Stride __IC, float *__D, vDSP_Stride __ID, vDSP_Length __N)
{
    ternary_impl(__A, __IA, __B, __IB, __C, __IC, __D, __ID, __N, add_multiply);
}

void vDSP_vamD(const double *__A, vDSP_Stride __IA, const double *__B, vDSP_Stride __IB, const double *__C, vDSP_Stride __IC, double *__D, vDSP_Stride __ID, vDSP_Length __N)
{
    ternary_impl(__A, __IA, __B, __IB, __C, __IC, __D, __ID, __N, add_multiply);
}

void vDSP_vma(const float *__A, vDSP_Stride __IA, const float *__B, vDSP_Stride __IB, const float *__C, vDSP_Stride __IC, float *__D, vDSP_Stride __ID, vDSP_Length __N)
{
    ternary_impl(__A, __IA, __B, __IB, __C, __IC, __D, __ID, __N, multiply_add);
}

void vDSP_vmaD(const double *__A, vDSP_Stride __IA, const double *__B, vDSP_Stride __IB, const double *__C, vDSP_Stride __IC, double *__D, vDSP_Stride __ID, vDSP_Length __N)
{
    ternary_impl(__A, __IA, __B, __IB, __C, __IC, __D, __ID, __N, multiply_add);
}

void vDSP_vmsb(const float *__A, vDSP_Stride __IA, const float *__B, vDSP_Stride __IB, const float *__C, vDSP_Stride __IC, float *__D, vDSP_Stride __ID, vDSP_Length __N)
{
    ternary_impl(__A, __IA, __B, __IB, __C, __IC, __D, __ID, __N, multiply_sub);
}

void vDSP_vmsbD(const double *__A, vDSP_Stride __IA, const double *__B, vDSP_Stride __IB, const double *__C, vDSP_Stride __IC, double *__D, vDSP_Stride __ID, vDSP_Length __N)
{
    ternary_impl(__A, __IA, __B, __IB, __C, __IC, __D, __ID, __N, multiply_sub);
}

void vDSP_vsbm(const float *__A, vDSP_Stride __IA, const float *__B, vDSP_Stride __IB, const float *__C, vDSP_Stride __IC, float *__D, vDSP_Stride __ID, vDSP_Length __N)
{
    ternary_impl(__A, __IA, __B, __IB, __C, __IC, __D, __ID, __N, sub_multiply);
}

void vDSP_vsbmD(const double *__A, vDSP_Stride __IA, const double *__B, vDSP_Stride __IB, const double *__C, vDSP_Stride __IC, double *__D, vDSP_Stride __ID, vDSP_Length __N)
{
    ternary_impl(__A, __IA, __B, __IB, __C, __IC, __D, __ID, __N, sub_multiply);
}

//======================================================================================================================
// Quaternary operations
template <typename FloatType, typename QuaternaryOp>
void quaternary_impl(const FloatType *__A, vDSP_Stride __IA, const FloatType *__B, vDSP_Stride __IB, const FloatType *__C, vDSP_Stride __IC, const FloatType *__D, vDSP_Stride __ID, FloatType *__E, vDSP_Stride __IE, vDSP_Length __N, QuaternaryOp op)
{
    #pragma clang loop vectorize(enable)
    for (vDSP_Length n = 0; n < __N; ++n)
        __E[n * __IE] = op(__A[n * __IA], __B[n * __IA], __C[n * __IC], __D[n * __ID]);
}

constexpr auto mul_mul_sub = [](auto a, auto b, auto c, auto d) { return a * b - c * d; };
constexpr auto add_add_mul = [](auto a, auto b, auto c, auto d) { return (a + b) * (c + d); };
constexpr auto sub_sub_mul = [](auto a, auto b, auto c, auto d) { return (a - b) * (c - d); };
constexpr auto add_sub_mul = [](auto a, auto b, auto c, auto d) { return (a + b) * (c - d); };

void vDSP_vmmsb(const float *__A, vDSP_Stride __IA, const float *__B, vDSP_Stride __IB, const float *__C, vDSP_Stride __IC, const float *__D, vDSP_Stride __ID, float *__E, vDSP_Stride __IE, vDSP_Length __N)
{
    quaternary_impl(__A, __IA, __B, __IB, __C, __IC, __D, __ID, __E, __IE, __N, mul_mul_sub);
}

void vDSP_vmmsbD(const double *__A, vDSP_Stride __IA, const double *__B, vDSP_Stride __IB, const double *__C, vDSP_Stride __IC, const double *__D, vDSP_Stride __ID, double *__E, vDSP_Stride __IE, vDSP_Length __N)
{
    quaternary_impl(__A, __IA, __B, __IB, __C, __IC, __D, __ID, __E, __IE, __N, mul_mul_sub);
}

void vDSP_vaam(const float *__A, vDSP_Stride __IA, const float *__B, vDSP_Stride __IB, const float *__C, vDSP_Stride __IC, const float *__D, vDSP_Stride __ID, float *__E, vDSP_Stride __IE, vDSP_Length __N)
{
    quaternary_impl(__A, __IA, __B, __IB, __C, __IC, __D, __ID, __E, __IE, __N, add_add_mul);
}

void vDSP_vaamD(const double *__A, vDSP_Stride __IA, const double *__B, vDSP_Stride __IB, const double *__C, vDSP_Stride __IC, const double *__D, vDSP_Stride __ID, double *__E, vDSP_Stride __IE, vDSP_Length __N)
{
    quaternary_impl(__A, __IA, __B, __IB, __C, __IC, __D, __ID, __E, __IE, __N, add_add_mul);
}

void vDSP_vsbsbm(const float *__A, vDSP_Stride __IA, const float *__B, vDSP_Stride __IB, const float *__C, vDSP_Stride __IC, const float *__D, vDSP_Stride __ID, float *__E, vDSP_Stride __IE, vDSP_Length __N)
{
    quaternary_impl(__A, __IA, __B, __IB, __C, __IC, __D, __ID, __E, __IE, __N, sub_sub_mul);
}

void vDSP_vsbsbmD(const double *__A, vDSP_Stride __IA, const double *__B, vDSP_Stride __IB, const double *__C, vDSP_Stride __IC, const double *__D, vDSP_Stride __ID, double *__E, vDSP_Stride __IE, vDSP_Length __N)
{
    quaternary_impl(__A, __IA, __B, __IB, __C, __IC, __D, __ID, __E, __IE, __N, sub_sub_mul);
}

void vDSP_vasbm(const float *__A, vDSP_Stride __IA, const float *__B, vDSP_Stride __IB, const float *__C, vDSP_Stride __IC, const float *__D, vDSP_Stride __ID, float *__E, vDSP_Stride __IE, vDSP_Length __N)
{
    quaternary_impl(__A, __IA, __B, __IB, __C, __IC, __D, __ID, __E, __IE, __N, add_sub_mul);
}

void vDSP_vasbmD(const double *__A, vDSP_Stride __IA, const double *__B, vDSP_Stride __IB, const double *__C, vDSP_Stride __IC, const double *__D, vDSP_Stride __ID, double *__E, vDSP_Stride __IE, vDSP_Length __N)
{
    quaternary_impl(__A, __IA, __B, __IB, __C, __IC, __D, __ID, __E, __IE, __N, add_sub_mul);
}

//======================================================================================================================
template <typename FloatType>
void vaddsub_impl(const FloatType *__I0, vDSP_Stride __I0S, const FloatType *__I1, vDSP_Stride __I1S, FloatType *__O0, vDSP_Stride __O0S, FloatType *__O1, vDSP_Stride __O1S, vDSP_Length __N)
{
#pragma clang loop vectorize(enable)
    for (vDSP_Length n = 0; n < __N; ++n)
    {
        const auto i0 = __I0[n * __I0S];
        const auto i1 = __I1[n * __I1S];

        __O0[n * __O0S] = i1  + i0;
        __O1[n * __O1S] = i1  - i0;
    }
}

void vDSP_vaddsub(const float *__I0, vDSP_Stride __I0S, const float *__I1, vDSP_Stride __I1S, float *__O0, vDSP_Stride __O0S, float *__O1, vDSP_Stride __O1S, vDSP_Length __N)
{
    vaddsub_impl(__I0, __I0S, __I1, __I1S, __O0, __O0S, __O1, __O1S, __N);
}

void vDSP_vaddsubD(const double *__I0, vDSP_Stride __I0S, const double *__I1, vDSP_Stride __I1S, double *__O0, vDSP_Stride __O0S, double *__O1, vDSP_Stride __O1S, vDSP_Length __N)
{
    vaddsub_impl(__I0, __I0S, __I1, __I1S, __O0, __O0S, __O1, __O1S, __N);
}
