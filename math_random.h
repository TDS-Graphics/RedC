#pragma once

#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <ntsecapi.h>


static float gen_random_float() {
    unsigned int r = 0;
    if (RtlGenRandom(&r, sizeof(r)) == FALSE) {
        fprintf(stderr, "RtlGenRandom failed\n");
        return -1.0f;
    }
    return (float) r / (float) UINT32_MAX;
}

static float gen_random_float_range(float min, float max) {
    if (max <= min) {
        fprintf(stderr, "gen_random_float_range: invalid range\n");
        return min;
    }
    unsigned int r = 0;
    if (RtlGenRandom(&r, sizeof(r)) == FALSE) {
        fprintf(stderr, "RtlGenRandom failed\n");
        return min;
    }
    float normalized = (float) r / (float) UINT32_MAX;
    return min + normalized * (max - min);
}

static int gen_random_int() {
    unsigned int r = 0;
    if (RtlGenRandom(&r, sizeof(r)) == FALSE) {
        fprintf(stderr, "RtlGenRandom failed\n");
        return -1;
    }

    return (int) ((float) r / (float) UINT32_MAX * (float) INT_MAX);
}

static int gen_random_int_range(int min, int max) {
    if (max <= min) {
        fprintf(stderr, "gen_random_int_range: invalid range\n");
        return min;
    }
    unsigned int r = 0;
    if (RtlGenRandom(&r, sizeof(r)) == FALSE) {
        fprintf(stderr, "RtlGenRandom failed\n");
        return min;
    }
    float normalized = (float) r / (float) UINT32_MAX;
    int range = max - min;
    return min + (int) (normalized * (float) range);
}
