#ifndef OC_SIMD_H
#define OC_SIMD_H

#define OC_ALIGN __attribute__((aligned (16)))

#ifdef OC_SIMD
#include <xmmintrin.h>
#include <pmmintrin.h>
#include <simd.hpp>
#endif

#endif
