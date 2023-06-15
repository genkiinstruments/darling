/*
 This file is part of Darling.

 Copyright (C) 2019 Lubos Dolezel

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


#ifndef _vDSP_H_
#define _vDSP_H_

typedef unsigned long vDSP_Length;
typedef long vDSP_Stride;

#ifdef __cplusplus
#define VDSP_EXPORT extern "C"
#else
#define VDSP_EXPORT extern
#endif

void* vDSP_DCT_CreateSetup(void);
void* vDSP_DCT_Execute(void);
void* vDSP_DFT_CreateSetup(void);
void* vDSP_DFT_DestroySetup(void);
void* vDSP_DFT_DestroySetupD(void);
void* vDSP_DFT_Execute(void);
void* vDSP_DFT_ExecuteD(void);
void* vDSP_DFT_zop(void);
void* vDSP_DFT_zop_CreateSetup(void);
void* vDSP_DFT_zop_CreateSetupD(void);
void* vDSP_DFT_zrop_CreateSetup(void);
void* vDSP_DFT_zrop_CreateSetupD(void);
void* vDSP_FFT16_copv(void);
void* vDSP_FFT16_zopv(void);
void* vDSP_FFT32_copv(void);
void* vDSP_FFT32_zopv(void);
void* vDSP_biquad(void);
void* vDSP_biquadD(void);
void* vDSP_biquad_CreateSetup(void);
void* vDSP_biquad_CreateSetupD(void);
void* vDSP_biquad_DestroySetup(void);
void* vDSP_biquad_DestroySetupD(void);
void* vDSP_biquadm(void);
void* vDSP_biquadmD(void);
void* vDSP_biquadm_CopyState(void);
void* vDSP_biquadm_CopyStateD(void);
void* vDSP_biquadm_CreateSetup(void);
void* vDSP_biquadm_CreateSetupD(void);
void* vDSP_biquadm_DestroySetup(void);
void* vDSP_biquadm_DestroySetupD(void);
void* vDSP_biquadm_ResetState(void);
void* vDSP_biquadm_ResetStateD(void);
void* vDSP_biquadm_SetActiveFilters(void);
void* vDSP_biquadm_SetCoefficientsDouble(void);
void* vDSP_biquadm_SetCoefficientsSingle(void);
void* vDSP_biquadm_SetTargetsDouble(void);
void* vDSP_biquadm_SetTargetsSingle(void);
void* vDSP_blkman_window(void);
void* vDSP_blkman_windowD(void);
void* vDSP_conv(void);
void* vDSP_convD(void);
void* vDSP_create_fftsetup(void);
void* vDSP_create_fftsetupD(void);
void* vDSP_ctoz(void);
void* vDSP_ctozD(void);
void* vDSP_deq22(void);
void* vDSP_deq22D(void);
void* vDSP_desamp(void);
void* vDSP_desampD(void);
void* vDSP_destroy_fftsetup(void);
void* vDSP_destroy_fftsetupD(void);
void* vDSP_distancesq(void);
void* vDSP_distancesqD(void);
void* vDSP_dotpr(void);
void* vDSP_dotpr2(void);
void* vDSP_dotpr2D(void);
void* vDSP_dotpr2_s1_15(void);
void* vDSP_dotpr2_s8_24(void);
void* vDSP_dotprD(void);
void* vDSP_dotpr_s1_15(void);
void* vDSP_dotpr_s8_24(void);
void* vDSP_f3x3(void);
void* vDSP_f3x3D(void);
void* vDSP_f5x5(void);
void* vDSP_f5x5D(void);
void* vDSP_fft2d_zip(void);
void* vDSP_fft2d_zipD(void);
void* vDSP_fft2d_zipt(void);
void* vDSP_fft2d_ziptD(void);
void* vDSP_fft2d_zop(void);
void* vDSP_fft2d_zopD(void);
void* vDSP_fft2d_zopt(void);
void* vDSP_fft2d_zoptD(void);
void* vDSP_fft2d_zrip(void);
void* vDSP_fft2d_zripD(void);
void* vDSP_fft2d_zript(void);
void* vDSP_fft2d_zriptD(void);
void* vDSP_fft2d_zrop(void);
void* vDSP_fft2d_zropD(void);
void* vDSP_fft2d_zropt(void);
void* vDSP_fft2d_zroptD(void);
void* vDSP_fft3_zop(void);
void* vDSP_fft3_zopD(void);
void* vDSP_fft5_zop(void);
void* vDSP_fft5_zopD(void);
void* vDSP_fft_zip(void);
void* vDSP_fft_zipD(void);
void* vDSP_fft_zipt(void);
void* vDSP_fft_ziptD(void);
void* vDSP_fft_zop(void);
void* vDSP_fft_zopD(void);
void* vDSP_fft_zopt(void);
void* vDSP_fft_zoptD(void);
void* vDSP_fft_zrip(void);
void* vDSP_fft_zripD(void);
void* vDSP_fft_zript(void);
void* vDSP_fft_zriptD(void);
void* vDSP_fft_zrop(void);
void* vDSP_fft_zropD(void);
void* vDSP_fft_zropt(void);
void* vDSP_fft_zroptD(void);
void* vDSP_fftm_zip(void);
void* vDSP_fftm_zipD(void);
void* vDSP_fftm_zipt(void);
void* vDSP_fftm_ziptD(void);
void* vDSP_fftm_zop(void);
void* vDSP_fftm_zopD(void);
void* vDSP_fftm_zopt(void);
void* vDSP_fftm_zoptD(void);
void* vDSP_fftm_zrip(void);
void* vDSP_fftm_zripD(void);
void* vDSP_fftm_zript(void);
void* vDSP_fftm_zriptD(void);
void* vDSP_fftm_zrop(void);
void* vDSP_fftm_zropD(void);
void* vDSP_fftm_zropt(void);
void* vDSP_fftm_zroptD(void);
void* vDSP_hamm_window(void);
void* vDSP_hamm_windowD(void);
void* vDSP_hann_window(void);
void* vDSP_hann_windowD(void);
void* vDSP_imgfir(void);
void* vDSP_imgfirD(void);
void* vDSP_maxmgvD(void);
void* vDSP_maxmgvi(void);
void* vDSP_maxmgviD(void);
void* vDSP_maxv(void);
void* vDSP_maxvD(void);
void* vDSP_maxvi(void);
void* vDSP_maxviD(void);
void* vDSP_meamgv(void);
void* vDSP_meamgvD(void);
void* vDSP_meanv(void);
void* vDSP_meanvD(void);
void* vDSP_measqv(void);
void* vDSP_measqvD(void);
void* vDSP_minmgv(void);
void* vDSP_minmgvD(void);
void* vDSP_minmgvi(void);
void* vDSP_minmgviD(void);
void* vDSP_minv(void);
void* vDSP_minvD(void);
void* vDSP_minvi(void);
void* vDSP_minviD(void);

VDSP_EXPORT void vDSP_mmov(
        const float *__A,
        float *__C,
        vDSP_Length __M,
        vDSP_Length __N,
        vDSP_Length __TA,
        vDSP_Length __TC);

VDSP_EXPORT void vDSP_mmovD(
        const double *__A,
        double *__C,
        vDSP_Length __M,
        vDSP_Length __N,
        vDSP_Length __TA,
        vDSP_Length __TC);

void* vDSP_mmul(void);
void* vDSP_mmulD(void);
void* vDSP_mtrans(void);
void* vDSP_mtransD(void);
void* vDSP_mvessq(void);
void* vDSP_mvessqD(void);
void* vDSP_normalize(void);
void* vDSP_normalizeD(void);
void* vDSP_nzcros(void);
void* vDSP_nzcrosD(void);
void* vDSP_polar(void);
void* vDSP_polarD(void);
void* vDSP_rect(void);
void* vDSP_rectD(void);
void* vDSP_rmsqv(void);
void* vDSP_rmsqvD(void);
void* vDSP_svdiv(void);
void* vDSP_svdivD(void);
void* vDSP_sve(void);
void* vDSP_sveD(void);
void* vDSP_sve_svesq(void);
void* vDSP_sve_svesqD(void);
void* vDSP_svemg(void);
void* vDSP_svemgD(void);
void* vDSP_svesq(void);
void* vDSP_svesqD(void);
void* vDSP_svs(void);
void* vDSP_svsD(void);

VDSP_EXPORT void vDSP_vaam(
        const float *__A,
        vDSP_Stride __IA,
        const float *__B,
        vDSP_Stride __IB,
        const float *__C,
        vDSP_Stride __IC,
        const float *__D,
        vDSP_Stride __ID,
        float *__E,
        vDSP_Stride __IE,
        vDSP_Length __N);

VDSP_EXPORT void vDSP_vaamD(
        const double *__A,
        vDSP_Stride __IA,
        const double *__B,
        vDSP_Stride __IB,
        const double *__C,
        vDSP_Stride __IC,
        const double *__D,
        vDSP_Stride __ID,
        double *__E,
        vDSP_Stride __IE,
        vDSP_Length __N);

void* vDSP_vabs(void);
void* vDSP_vabsD(void);
void* vDSP_vabsi(void);

VDSP_EXPORT void vDSP_vadd(const float *__A, vDSP_Stride __IA, const float *__B, vDSP_Stride __IB, float *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vaddD(const double *__A, vDSP_Stride __IA, const double *__B, vDSP_Stride __IB, double *__C, vDSP_Stride __IC, vDSP_Length __N);

void* vDSP_vaddi(void);

VDSP_EXPORT void vDSP_vaddsub(
        const float *__I0,
        vDSP_Stride __I0S,
        const float *__I1,
        vDSP_Stride __I1S,
        float *__O0,
        vDSP_Stride __O0S,
        float *__O1,
        vDSP_Stride __O1S,
        vDSP_Length __N);

VDSP_EXPORT void vDSP_vaddsubD(
        const double *__I0,
        vDSP_Stride __I0S,
        const double *__I1,
        vDSP_Stride __I1S,
        double *__O0,
        vDSP_Stride __O0S,
        float *__O1,
        vDSP_Stride __O1S,
        vDSP_Length __N);

VDSP_EXPORT void vDSP_vam(
        const float *__A,
        vDSP_Stride __IA,
        const float *__B,
        vDSP_Stride __IB,
        const float *__C,
        vDSP_Stride __IC,
        float *__D,
        vDSP_Stride __ID,
        vDSP_Length __N);

VDSP_EXPORT void vDSP_vamD(
        const double *__A,
        vDSP_Stride __IA,
        const double *__B,
        vDSP_Stride __IB,
        const double *__C,
        vDSP_Stride __IC,
        float *__D,
        vDSP_Stride __ID,
        vDSP_Length __N);

VDSP_EXPORT void vDSP_vasbm(
        const float *__A,
        vDSP_Stride __IA,
        const float *__B,
        vDSP_Stride __IB,
        const float *__C,
        vDSP_Stride __IC,
        const float *__D,
        vDSP_Stride __ID,
        float *__E,
        vDSP_Stride __IE,
        vDSP_Length __N);

VDSP_EXPORT void vDSP_vasbmD(
        const double *__A,
        vDSP_Stride __IA,
        const double *__B,
        vDSP_Stride __IB,
        const double *__C,
        vDSP_Stride __IC,
        const double *__D,
        vDSP_Stride __ID,
        double *__E,
        vDSP_Stride __IE,
        vDSP_Length __N);

void* vDSP_vasm(void);
void* vDSP_vasmD(void);
void* vDSP_vavlin(void);
void* vDSP_vavlinD(void);

VDSP_EXPORT void vDSP_vclip(
        const float *__A,
        vDSP_Stride __IA,
        const float *__B,
        const float *__C,
        float *__D,
        vDSP_Stride __ID,
        vDSP_Length __N);

VDSP_EXPORT void vDSP_vclipD(
        const double *__A,
        vDSP_Stride __IA,
        const double *__B,
        const double *__C,
        double *__D,
        vDSP_Stride __ID,
        vDSP_Length __N);

void* vDSP_vclipc(void);
void* vDSP_vclipcD(void);

VDSP_EXPORT void vDSP_vclr(float *__C, vDSP_Stride __IC, vDSP_Length __N);

void* vDSP_vcmprs(void);
void* vDSP_vcmprsD(void);
void* vDSP_vdbcon(void);
void* vDSP_vdbconD(void);
void* vDSP_vdist(void);
void* vDSP_vdistD(void);

VDSP_EXPORT void vDSP_vdiv(const float *__B, vDSP_Stride __IB, const float *__A, vDSP_Stride __IA, float *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vdivD(const double *__B, vDSP_Stride __IB, const double *__A, vDSP_Stride __IA, double *__C, vDSP_Stride __IC, vDSP_Length __N);

void* vDSP_vdivi(void);
void* vDSP_vdpsp(void);
void* vDSP_venvlp(void);
void* vDSP_venvlpD(void);
void* vDSP_veqvi(void);
void* vDSP_vfill(void);
void* vDSP_vfillD(void);
void* vDSP_vfilli(void);

VDSP_EXPORT void vDSP_vfix16(const float *__A, vDSP_Stride __IA, short *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfix16D(const double *__A, vDSP_Stride __IA, short *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfix32( const float *__A, vDSP_Stride __IA, int *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfix32D( const double *__A, vDSP_Stride __IA, int *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfix8(const float *__A, vDSP_Stride __IA, char *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfix8D(const double *__A, vDSP_Stride __IA, char *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfixr16(const float *__A, vDSP_Stride __IA, short *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfixr16D(const double *__A, vDSP_Stride __IA, short *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfixr32(const float *__A, vDSP_Stride __IA, int *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfixr32D(const double *__A, vDSP_Stride __IA, int *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfixr8(const float *__A, vDSP_Stride __IA, char *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfixr8D(const double *__A, vDSP_Stride __IA, char *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfixru16(const float *__A, vDSP_Stride __IA, unsigned short *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfixru16D(const float *__A, vDSP_Stride __IA, unsigned short *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfixru32(const float *__A, vDSP_Stride __IA, unsigned int *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfixru32D(const double *__A, vDSP_Stride __IA, unsigned int *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfixru8(const float *__A, vDSP_Stride __IA, unsigned char *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfixru8D(const double *__A, vDSP_Stride __IA, unsigned char *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfixu16(const float *__A, vDSP_Stride __IA, unsigned short *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfixu16D(const float *__A, vDSP_Stride __IA, unsigned short *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfixu32(const float *__A, vDSP_Stride __IA, unsigned int *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfixu32D(const double *__A, vDSP_Stride __IA, unsigned int *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfixu8(const float *__A, vDSP_Stride __IA, unsigned char *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfixu8D(const double *__A, vDSP_Stride __IA, unsigned char *__C, vDSP_Stride __IC, vDSP_Length __N);

void* vDSP_vflt16(void);
void* vDSP_vflt16D(void);
void* vDSP_vflt24(void);
void* vDSP_vflt32(void);
void* vDSP_vflt32D(void);
void* vDSP_vflt8(void);
void* vDSP_vflt8D(void);
void* vDSP_vfltsm24(void);
void* vDSP_vfltsmu24(void);
void* vDSP_vfltu16(void);
void* vDSP_vfltu16D(void);
void* vDSP_vfltu24(void);
void* vDSP_vfltu32(void);
void* vDSP_vfltu32D(void);
void* vDSP_vfltu8(void);
void* vDSP_vfltu8D(void);

VDSP_EXPORT void vDSP_vfrac( const float *__A, vDSP_Stride __IA, float *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vfracD( const double *__A, vDSP_Stride __IA, double *__C, vDSP_Stride __IC, vDSP_Length __N);

void* vDSP_vgathr(void);
void* vDSP_vgathrD(void);
void* vDSP_vgathra(void);
void* vDSP_vgathraD(void);
void* vDSP_vgen(void);
void* vDSP_vgenD(void);
void* vDSP_vgenp(void);
void* vDSP_vgenpD(void);
void* vDSP_viclip(void);
void* vDSP_viclipD(void);
void* vDSP_vindex(void);
void* vDSP_vindexD(void);
void* vDSP_vintb(void);
void* vDSP_vintbD(void);
void* vDSP_vlim(void);
void* vDSP_vlimD(void);
void* vDSP_vlint(void);
void* vDSP_vlintD(void);

VDSP_EXPORT void vDSP_vma(
        const float *__A,
        vDSP_Stride __IA,
        const float *__B,
        vDSP_Stride __IB,
        const float *__C,
        vDSP_Stride __IC,
        float *__D,
        vDSP_Stride __ID,
        vDSP_Length __N);

VDSP_EXPORT void vDSP_vmaD(
        const double *__A,
        vDSP_Stride __IA,
        const double *__B,
        vDSP_Stride __IB,
        const double *__C,
        vDSP_Stride __IC,
        double *__D,
        vDSP_Stride __ID,
        vDSP_Length __N);

void* vDSP_vmax(void);
void* vDSP_vmaxD(void);
void* vDSP_vmaxmg(void);
void* vDSP_vmaxmgD(void);
void* vDSP_vmin(void);
void* vDSP_vminD(void);
void* vDSP_vminmg(void);
void* vDSP_vminmgD(void);
void* vDSP_vmma(void);
void* vDSP_vmmaD(void);

VDSP_EXPORT void vDSP_vmmsb(
        const float *__A,
        vDSP_Stride __IA,
        const float *__B,
        vDSP_Stride __IB,
        const float *__C,
        vDSP_Stride __IC,
        const float *__D,
        vDSP_Stride __ID,
        float *__E,
        vDSP_Stride __IE,
        vDSP_Length __N);

VDSP_EXPORT void vDSP_vmmsbD(
        const double *__A,
        vDSP_Stride __IA,
        const double *__B,
        vDSP_Stride __IB,
        const double *__C,
        vDSP_Stride __IC,
        const double *__D,
        vDSP_Stride __ID,
        double *__E,
        vDSP_Stride __IE,
        vDSP_Length __N);

void* vDSP_vmsa(void);
void* vDSP_vmsaD(void);

VDSP_EXPORT void vDSP_vmsb(
        const float *__A,
        vDSP_Stride __IA,
        const float *__B,
        vDSP_Stride __IB,
        const float *__C,
        vDSP_Stride __IC,
        float *__D,
        vDSP_Stride __ID,
        vDSP_Length __N);

VDSP_EXPORT void vDSP_vmsbD(
        const double *__A,
        vDSP_Stride __IA,
        const double *__B,
        vDSP_Stride __IB,
        const double *__C,
        vDSP_Stride __IC,
        double *__D,
        vDSP_Stride __ID,
        vDSP_Length __N);

VDSP_EXPORT void vDSP_vmul(const float *__A, vDSP_Stride __IA, const float *__B, vDSP_Stride __IB, float *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vmulD(const double *__A, vDSP_Stride __IA, const double *__B, vDSP_Stride __IB, double *__C, vDSP_Stride __IC, vDSP_Length __N);

void* vDSP_vnabs(void);
void* vDSP_vnabsD(void);
void* vDSP_vneg(void);
void* vDSP_vnegD(void);
void* vDSP_vpoly(void);
void* vDSP_vpolyD(void);
void* vDSP_vpythg(void);
void* vDSP_vpythgD(void);
void* vDSP_vqint(void);
void* vDSP_vqintD(void);
void* vDSP_vramp(void);
void* vDSP_vrampD(void);
void* vDSP_vrampmul(void);
void* vDSP_vrampmul2(void);
void* vDSP_vrampmul2D(void);
void* vDSP_vrampmul2_s1_15(void);
void* vDSP_vrampmul2_s8_24(void);
void* vDSP_vrampmulD(void);
void* vDSP_vrampmul_s1_15(void);
void* vDSP_vrampmul_s8_24(void);
void* vDSP_vrampmuladd(void);
void* vDSP_vrampmuladd2(void);
void* vDSP_vrampmuladd2D(void);
void* vDSP_vrampmuladd2_s1_15(void);
void* vDSP_vrampmuladd2_s8_24(void);
void* vDSP_vrampmuladdD(void);
void* vDSP_vrampmuladd_s1_15(void);
void* vDSP_vrampmuladd_s8_24(void);
void* vDSP_vrsum(void);
void* vDSP_vrsumD(void);
void* vDSP_vrvrs(void);
void* vDSP_vrvrsD(void);

VDSP_EXPORT void vDSP_vsadd(
        const float *__A,
        vDSP_Stride __IA,
        const float *__B,
        float *__C,
        vDSP_Stride __IC,
        vDSP_Length __N);

void* vDSP_vsaddD(void);
void* vDSP_vsaddi(void);

VDSP_EXPORT void vDSP_vsbm(
        const float *__A,
        vDSP_Stride __IA,
        const float *__B,
        vDSP_Stride __IB,
        const float *__C,
        vDSP_Stride __IC,
        float *__D,
        vDSP_Stride __ID,
        vDSP_Length __N);

VDSP_EXPORT void vDSP_vsbmD(
        const double *__A,
        vDSP_Stride __IA,
        const double *__B,
        vDSP_Stride __IB,
        const double *__C,
        vDSP_Stride __IC,
        double *__D,
        vDSP_Stride __ID,
        vDSP_Length __N);

VDSP_EXPORT void vDSP_vsbsbm(
        const float *__A,
        vDSP_Stride __IA,
        const float *__B,
        vDSP_Stride __IB,
        const float *__C,
        vDSP_Stride __IC,
        const float *__D,
        vDSP_Stride __ID,
        float *__E,
        vDSP_Stride __IE,
        vDSP_Length __N);

VDSP_EXPORT void vDSP_vsbsbmD(
        const double *__A,
        vDSP_Stride __IA,
        const double *__B,
        vDSP_Stride __IB,
        const double *__C,
        vDSP_Stride __IC,
        const double *__D,
        vDSP_Stride __ID,
        double *__E,
        vDSP_Stride __IE,
        vDSP_Length __N);

void* vDSP_vsbsm(void);
void* vDSP_vsbsmD(void);
void* vDSP_vsdiv(void);
void* vDSP_vsdivD(void);
void* vDSP_vsdivi(void);
void* vDSP_vsimps(void);
void* vDSP_vsimpsD(void);

VDSP_EXPORT void vDSP_vsma(
        const float *__A,
        vDSP_Stride __IA,
        const float *__B,
        const float *__C,
        vDSP_Stride __IC,
        float *__D,
        vDSP_Stride __ID,
        vDSP_Length __N);

void* vDSP_vsmaD(void);
void* vDSP_vsmfix24(void);
void* vDSP_vsmfixu24(void);
void* vDSP_vsmsa(void);
void* vDSP_vsmsaD(void);
void* vDSP_vsmsb(void);
void* vDSP_vsmsbD(void);
void* vDSP_vsmsma(void);
void* vDSP_vsmsmaD(void);

VDSP_EXPORT void vDSP_vsmul(
        const float *__A,
        vDSP_Stride __IA,
        const float *__B,
        float *__C,
        vDSP_Stride __IC,
        vDSP_Length __N);

VDSP_EXPORT void vDSP_vsmulD(
        const double *__A,
        vDSP_Stride __IA,
        const double *__B,
        double *__C,
        vDSP_Stride __IC,
        vDSP_Length __N);

void* vDSP_vsort(void);
void* vDSP_vsortD(void);
void* vDSP_vsorti(void);
void* vDSP_vsortiD(void);
void* vDSP_vspdp(void);
void* vDSP_vsq(void);
void* vDSP_vsqD(void);
void* vDSP_vssq(void);
void* vDSP_vssqD(void);

VDSP_EXPORT void vDSP_vsub(const float *__B, vDSP_Stride __IB, const float *__A, vDSP_Stride __IA, float *__C, vDSP_Stride __IC, vDSP_Length __N);

VDSP_EXPORT void vDSP_vsubD(const double *__B, vDSP_Stride __IB, const double *__A, vDSP_Stride __IA, double *__C, vDSP_Stride __IC, vDSP_Length __N);

void* vDSP_vswap(void);
void* vDSP_vswapD(void);
void* vDSP_vswmax(void);
void* vDSP_vswmaxD(void);
void* vDSP_vswsum(void);
void* vDSP_vswsumD(void);
void* vDSP_vtabi(void);
void* vDSP_vtabiD(void);
void* vDSP_vthr(void);
void* vDSP_vthrD(void);
void* vDSP_vthres(void);
void* vDSP_vthresD(void);
void* vDSP_vthrsc(void);
void* vDSP_vthrscD(void);
void* vDSP_vtmerg(void);
void* vDSP_vtmergD(void);
void* vDSP_vtrapz(void);
void* vDSP_vtrapzD(void);
void* vDSP_wiener(void);
void* vDSP_wienerD(void);
void* vDSP_zaspec(void);
void* vDSP_zaspecD(void);
void* vDSP_zcoher(void);
void* vDSP_zcoherD(void);
void* vDSP_zconv(void);
void* vDSP_zconvD(void);
void* vDSP_zcspec(void);
void* vDSP_zcspecD(void);
void* vDSP_zdotpr(void);
void* vDSP_zdotprD(void);
void* vDSP_zidotpr(void);
void* vDSP_zidotprD(void);
void* vDSP_zmma(void);
void* vDSP_zmmaD(void);
void* vDSP_zmms(void);
void* vDSP_zmmsD(void);
void* vDSP_zmmul(void);
void* vDSP_zmmulD(void);
void* vDSP_zmsm(void);
void* vDSP_zmsmD(void);
void* vDSP_zrdesamp(void);
void* vDSP_zrdesampD(void);
void* vDSP_zrdotpr(void);
void* vDSP_zrdotprD(void);
void* vDSP_zrvadd(void);
void* vDSP_zrvaddD(void);
void* vDSP_zrvdiv(void);
void* vDSP_zrvdivD(void);
void* vDSP_zrvmul(void);
void* vDSP_zrvmulD(void);
void* vDSP_zrvsub(void);
void* vDSP_zrvsubD(void);
void* vDSP_ztoc(void);
void* vDSP_ztocD(void);
void* vDSP_ztrans(void);
void* vDSP_ztransD(void);
void* vDSP_zvabs(void);
void* vDSP_zvabsD(void);
void* vDSP_zvadd(void);
void* vDSP_zvaddD(void);
void* vDSP_zvcma(void);
void* vDSP_zvcmaD(void);
void* vDSP_zvcmul(void);
void* vDSP_zvcmulD(void);
void* vDSP_zvconj(void);
void* vDSP_zvconjD(void);
void* vDSP_zvdiv(void);
void* vDSP_zvdivD(void);
void* vDSP_zvfill(void);
void* vDSP_zvfillD(void);
void* vDSP_zvma(void);
void* vDSP_zvmaD(void);
void* vDSP_zvmags(void);
void* vDSP_zvmagsD(void);
void* vDSP_zvmgsa(void);
void* vDSP_zvmgsaD(void);
void* vDSP_zvmmaa(void);
void* vDSP_zvmmaaD(void);
void* vDSP_zvmov(void);
void* vDSP_zvmovD(void);
void* vDSP_zvmul(void);
void* vDSP_zvmulD(void);
void* vDSP_zvneg(void);
void* vDSP_zvnegD(void);
void* vDSP_zvphas(void);
void* vDSP_zvphasD(void);
void* vDSP_zvsma(void);
void* vDSP_zvsmaD(void);
void* vDSP_zvsub(void);
void* vDSP_zvsubD(void);
void* vDSP_zvzsml(void);
void* vDSP_zvzsmlD(void);

#endif
