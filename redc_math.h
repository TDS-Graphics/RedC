#pragma once

#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <ntsecapi.h>

typedef struct vec2f {
    float x, y;
} vec2f;

typedef struct vec3f {
    float x, y, z;
} vec3f;

typedef struct vec4f {
    float x, y, z, w;
} vec4f;

typedef struct vec2i {
    int x, y;
} vec2i;

typedef struct vec3i {
    int x, y, z;
} vec3i;

typedef struct vec4i {
    int x, y, z, w;
} vec4i;

/*
 *  ---------------- Vec2 Calculate ----------------
 */

static vec2f add_vec2f(vec2f v1, vec2f v2) {
    const vec2f result = {
        .x = v1.x + v2.x,
        .y = v1.y + v2.y
    };
    return result;
}

static vec2f sub_vec2f(vec2f v1, vec2f v2) {
    const vec2f result = {
        .x = v1.x - v2.x,
        .y = v1.y - v2.y
    };
    return result;
}

static vec2f mul_vec2f(vec2f v1, vec2f v2) {
    const vec2f result = {
        .x = v1.x * v2.x,
        .y = v1.y * v2.y
    };
    return result;
}

static vec2f div_vec2f(vec2f v1, vec2f v2) {
    const vec2f result = {
        .x = v1.x / v2.x,
        .y = v1.y / v2.y
    };
    return result;
}

static vec2f add_vec2f_scaler(vec2f v1, float v2) {
    const vec2f result = {
        .x = v1.x + v2,
        .y = v1.y + v2
    };
    return result;
}

static vec2f sub_vec2f_scaler(vec2f v1, float v2) {
    const vec2f result = {
        .x = v1.x - v2,
        .y = v1.y - v2
    };
    return result;
}

static vec2f mul_vec2f_scaler(vec2f v1, float v2) {
    const vec2f result = {
        .x = v1.x * v2,
        .y = v1.y * v2
    };
    return result;
}

static vec2f div_vec2f_scaler(vec2f v1, float v2) {
    const vec2f result = {
        .x = v1.x / v2,
        .y = v1.y / v2
    };
    return result;
}

/*
 *  ---------------- Random ----------------
 */

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
