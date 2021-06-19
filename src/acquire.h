#pragma once

#include <complex.h>
#include <fftw3.h>
#include "firdecim_q15.h"

typedef struct fft_plan_t
{
    fftwf_plan fft_plan;
    float complex fftin[FFT_FM];
    float complex fftout[FFT_FM];

    int mode;
    struct fft_plan_t *next;
} fft_plan_t;

typedef struct
{
    struct input_t *input;
    firdecim_q15 filter_fm;
    firdecim_q15 filter_am;
    cint16_t in_buffer[FFTCP_FM * (ACQUIRE_SYMBOLS + 1)];
    float complex buffer[FFTCP_FM * (ACQUIRE_SYMBOLS + 1)];
    float complex sums[FFTCP_FM];
    float complex *fftin;
    float complex *fftout;
    float *shape;
    float shape_fm[FFTCP_FM];
    float shape_am[FFTCP_AM];
    fft_plan_t *fft_plan_fm;
    fft_plan_t *fft_plan_am;

    unsigned int idx;
    float prev_angle;
    float complex phase;
    int cfo;

    int mode;
    int fft;
    int fftcp;
    int cp;
} acquire_t;

void acquire_process(acquire_t *st);
void acquire_cfo_adjust(acquire_t *st, int cfo);
unsigned int acquire_push(acquire_t *st, cint16_t *buf, unsigned int length);
void acquire_reset(acquire_t *st);
void acquire_init(acquire_t *st, struct input_t *input);
void acquire_set_mode(acquire_t *st, int mode);
void acquire_free(acquire_t *st);
fft_plan_t *acquire_alloc_fft_plan(int mode);
void acquire_free_fft_plan(fft_plan_t *plan);
