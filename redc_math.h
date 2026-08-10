#pragma once

#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <ntsecapi.h>

struct vec2f {
    float x, y;
};

struct vec3f {
    float x, y, z;
};

struct vec4f {
    float x, y, z, w;
};

struct vec2i {
    int x, y;
};

struct vec3i {
    int x, y, z;
};

struct vec4i {
    int x, y, z, w;
};

/*
 *  ---------------- Vec2 Calculate ----------------
 */

inline static struct vec2f add_vec2f(struct vec2f v1, struct vec2f v2) {
    struct vec2f result = {
        .x = v1.x + v2.x,
        .y = v1.y + v2.y
    };
    return result;
}

inline static struct vec2f sub_vec2f(struct vec2f v1, struct vec2f v2) {
    struct vec2f result = {
        .x = v1.x - v2.x,
        .y = v1.y - v2.y
    };
    return result;
}

inline static struct vec2f mul_vec2f(struct vec2f v1, struct vec2f v2) {
    struct vec2f result = {
        .x = v1.x * v2.x,
        .y = v1.y * v2.y
    };
    return result;
}

inline static struct vec2f div_vec2f(struct vec2f v1, struct vec2f v2) {
    struct vec2f result = {
        .x = v1.x / v2.x,
        .y = v1.y / v2.y
    };
    return result;
}

inline static struct vec2f add_vec2f_scaler(struct vec2f v1, float v2) {
    struct vec2f result = {
        .x = v1.x + v2,
        .y = v1.y + v2
    };
    return result;
}

inline static struct vec2f sub_vec2f_scaler(struct vec2f v1, float v2) {
    struct vec2f result = {
        .x = v1.x - v2,
        .y = v1.y - v2
    };
    return result;
}

inline static struct vec2f mul_vec2f_scaler(struct vec2f v1, float v2) {
    struct vec2f result = {
        .x = v1.x * v2,
        .y = v1.y * v2
    };
    return result;
}

inline static struct vec2f div_vec2f_scaler(struct vec2f v1, float v2) {
    struct vec2f result = {
        .x = v1.x / v2,
        .y = v1.y / v2
    };
    return result;
}

/*
 *  ---------------- Random ----------------
 */

static inline float gen_random_float(void) {
    unsigned int r = 0;
    if (RtlGenRandom(&r, sizeof(r)) == FALSE) {
        fprintf(stderr, "RtlGenRandom failed\n");
        return -1.0f;
    }
    return (float) r / (float) UINT32_MAX;
}

static inline float gen_random_float_range(float min, float max) {
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

static inline int gen_random_int(void) {
    unsigned int r = 0;
    if (RtlGenRandom(&r, sizeof(r)) == FALSE) {
        fprintf(stderr, "RtlGenRandom failed\n");
        return -1;
    }

    return (int) ((float) r / (float) UINT32_MAX * (float) INT_MAX);
}

static inline int gen_random_int_range(int min, int max) {
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
    return min + (int) (normalized * range);
}
