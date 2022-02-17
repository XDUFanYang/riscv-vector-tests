#ifndef __VDEF_OPF_VWW_H__
#define __VDEF_OPF_VWW_H__

#include "common.h"

#define VOPF_VWW_DEF(op, type_arg, lmul_arg, type_ret, lmul_ret) \
void op##_wv_ ## type_ret ## lmul_ret ## _vec(type_ret*d, type_ret*s2, type_arg*s1, u64 n) \
{ \
  size_t i; \
  size_t vl = VSETVL(type_arg, lmul_arg, n); \
  VTYPE(type_ret, lmul_ret) vd; \
  for (i = 0; i < n;) { \
    vl = VSETVL(type_arg, lmul_arg, n - i); \
    VTYPE(type_arg, lmul_arg) vs1 = VLE(type_arg, lmul_arg, &s1[i], vl); \
    VTYPE(type_ret, lmul_ret) vs2 = VLE(type_ret, lmul_ret, &s2[i], vl); \
    vd = op ## _wv(vs2, vs1, vl); \
    /*__asm__(#op ".vv %0, %1, %2;" : "=&vr"(vd) : "vr"(vs2), "vr"(vs1)); */\
    VSE(type_ret, lmul_ret, &d[i], vd, vl); \
    i += vl; \
  } \
} \

#define VOPF_VWW_M_DEF(op, type_arg, lmul_arg, type_ret, lmul_ret) \
void op##_wv_ ## type_ret ## lmul_ret ## _m_vec( \
  type_ret*d, type_ret*s2, type_arg*s1, const u8* mask, u64 n) \
{ \
  size_t i; \
  size_t vlmax = VSETVLMAX(type_arg, lmul_arg); \
  VTYPE(type_ret, lmul_ret) vd; \
  for (i = 0; i < n;) { \
    size_t vl = VSETVL(type_arg, lmul_arg, n - i); \
    auto vmask = VLM(VTYPEM(type_arg, lmul_arg), &mask[i/8], vl); \
    auto offset = i % 8; \
    __asm__("vsrl.vx %0, %1, %2;" : "=vm"(vmask) : "vm"(vmask), "r"(offset)); \
    VTYPE(type_arg, lmul_arg) vs1 = VLE(type_arg, lmul_arg, &s1[i], vl); \
    VTYPE(type_ret, lmul_ret) vs2 = VLE(type_ret, lmul_ret, &s2[i], vl); \
    vd = op ## _wv(vmask, VUNDEF(type_ret, lmul_ret), vs2, vs1, vl); \
    /*__asm__(#op ".vv %0, %1, %2, %3.t;" : "=&vr"(vd) : "vr"(vs2), "vr"(vs1), "vm"(vmask));*/ \
    vse_v_ ## type_ret(vmask, &d[i], vd, vl); \
    i += vl; \
  } \
} \

#define VOPF_VWW_DEF_GROUP_IMPL(op) \
op (f32,  mf2,  f64,  m1) \
op (f32,  m1,   f64,  m2) \
op (f32,  m2,   f64,  m4) \
op (f32,  m4,   f64,  m8) \

#define VOPF_VWW_DEF_GROUP(op)    VOPF_VWW_DEF_GROUP_IMPL(op ## _WV_DEF)
#define VOPF_VWW_M_DEF_GROUP(op)  VOPF_VWW_DEF_GROUP_IMPL(op ## _WV_M_DEF)

/**
 * @brief defination of opf_vww: (v, v)->wv
 * 
 */

#define VFWADD_WV_DEF(type_arg, lmul_arg, type_ret, lmul_ret)  VOPF_VWW_DEF(vfwadd, type_arg, lmul_arg, type_ret, lmul_ret)
#define VFWSUB_WV_DEF(type_arg, lmul_arg, type_ret, lmul_ret)  VOPF_VWW_DEF(vfwsub, type_arg, lmul_arg, type_ret, lmul_ret)
VOPF_VWW_DEF_GROUP(VFWADD)
VOPF_VWW_DEF_GROUP(VFWSUB)

/**
 * @brief defination of opf_vww_m: (v, v)->wv
 * 
 */

#define VFWADD_WV_M_DEF(type_arg, lmul_arg, type_ret, lmul_ret)  VOPF_VWW_M_DEF(vfwadd, type_arg, lmul_arg, type_ret, lmul_ret)
#define VFWSUB_WV_M_DEF(type_arg, lmul_arg, type_ret, lmul_ret)  VOPF_VWW_M_DEF(vfwsub, type_arg, lmul_arg, type_ret, lmul_ret)
VOPF_VWW_M_DEF_GROUP(VFWADD)
VOPF_VWW_M_DEF_GROUP(VFWSUB)

#endif
