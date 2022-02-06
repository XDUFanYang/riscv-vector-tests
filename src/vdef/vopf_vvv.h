#include "common.h"

#define VOPF_VVV_DEF(op, type, lmul) \
void op##_vv_ ## type ## lmul ## _vec ( \
type*vd, type*vs2, type*vs1, uint64_t n) \
{ \
  size_t i; \
  size_t vl = VSETVL(type, lmul, n); \
  for (i = 0; i < n;) { \
    vl = VSETVL(type, lmul, n); \
    VTYPE(type, lmul) v_vs1 = VLE(type, lmul, &vs1[i], vl); \
    VTYPE(type, lmul) v_vs2 = VLE(type, lmul, &vs2[i], vl); \
    VTYPE(type, lmul) v_res = op##_vv_##type##lmul(v_vs2, v_vs1, vl); \
    VSE(type, lmul, &vd[i], v_res, vl); \
    i += vl; \
  } \
} \

#define VOPF_VVV_M_DEF(op, type, lmul) \
void op##_vv_ ## type ## lmul ## _m_vec( \
type*d, type*s2, type*s1, const u8* mask, u64 n) \
{ \
  size_t i=0; \
  size_t vlmax = VSETVLMAX(type, lmul); \
  for (i = 0; i < n;) { \
    size_t vl = VSETVL(type, lmul, n); \
    auto vmask = VLM(VTYPEM(type, lmul), &mask[i/8], vl); \
    auto offset = i % 8; \
    __asm__("vsrl.vx %0, %1, %2;" : "=vm"(vmask) : "vm"(vmask), "r"(offset)); \
    auto vs1 = vle_v_ ## type(vmask, VUNDEF(type, lmul), &s1[i], vl); \
    auto vs2 = vle_v_ ## type(vmask, VUNDEF(type, lmul), &s2[i], vl); \
    auto vres = op(vmask, VUNDEF(type, lmul), vs2, vs1, vl); \
    vse_v_ ## type(vmask, &d[i], vres, vl); \
    i += vl; \
  } \
} \

#define VOPF_VVV_DEF_GROUP_IMPL(op) \
op (f32, mf2) \
op (f32, m1) \
op (f32, m2) \
op (f32, m4) \
op (f32, m8) \
op (f64, m1) \
op (f64, m2) \
op (f64, m4) \
op (f64, m8)

#define VOPF_VVV_DEF_GROUP(op) VOPF_VVV_DEF_GROUP_IMPL(op ## _VV_DEF)
#define VOPF_VVV_M_DEF_GROUP(op) VOPF_VVV_DEF_GROUP_IMPL(op ## _VV_M_DEF)
