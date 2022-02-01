#include <cstdint>
#include <cstddef>
#include <algorithm>

#define VOPI_VVV_REF_DEF(op, code) \
template<typename TypeRet, typename TypeSrc2, typename TypeSrc1> \
void op ## _vv_ref(TypeRet* vd, TypeSrc2* vs2, TypeSrc1* vs1, size_t n) { \
  {code;} \
} \

#define VOPI_VXV_REF_DEF(op, code) \
template<typename TypeRet, typename TypeSrc2, typename TypeSrc1> \
void op ## _vx_ref(TypeRet* vd, TypeSrc2* vs2, TypeSrc1* rs1, size_t n) { \
  {code;} \
} \

#define VOPI_VVV_M_REF_DEF(op, code) \
template<typename TypeRet, typename TypeSrc2, typename TypeSrc1> \
void op ## _vv_m_ref( \
  TypeRet* vd, TypeSrc2* vs2, TypeSrc1* vs1, \
  const uint8_t* vmask, size_t n) { \
  {code;} \
} \

#define VOPI_VXV_M_REF_DEF(op, code) \
template<typename TypeRet, typename TypeSrc2, typename TypeSrc1> \
void op ## _vx_m_ref( \
  TypeRet* vd, TypeSrc2* vs2, TypeSrc1* rs1, \
  const uint8_t* vmask, size_t n) { \
  {code;} \
} \

#define VOPI_VV_REF_DEF(op, code) \
template<typename Type> \
void op ## _v_v_ref(Type* vd, Type* vs, size_t n) { \
  {code;} \
} \

#define VOPF_VVV_REF_DEF(op, code)   VOPI_VVV_REF_DEF(op, code)
#define VOPF_VVV_M_REF_DEF(op, code) VOPI_VVV_M_REF_DEF(op, code)

#define FORLOOP(i, code) \
for (size_t i = 0; i < n; i++) { \
  {code;} \
} \

#define FORLOOPIF(i, condition, code) \
for (size_t i = 0; i < n; i++) { \
  if (condition) {code;} \
} \

#define VMASK(i) (vmask[i/8] >> (i%8)) & 0x1 

VOPI_VVV_REF_DEF(vadd,           FORLOOP(i, vd[i] = vs2[i]+vs1[i]))
VOPI_VVV_REF_DEF(vsub,           FORLOOP(i, vd[i] = vs2[i]-vs1[i]))
VOPI_VVV_REF_DEF(vmin,           FORLOOP(i, vd[i] = std::min(vs2[i], vs1[i])))
VOPI_VVV_REF_DEF(vminu,          FORLOOP(i, vd[i] = std::min(vs2[i], vs1[i])))
VOPI_VVV_REF_DEF(vmax,           FORLOOP(i, vd[i] = std::max(vs2[i], vs1[i])))
VOPI_VVV_REF_DEF(vmaxu,          FORLOOP(i, vd[i] = std::max(vs2[i], vs1[i])))
VOPI_VVV_REF_DEF(vand,           FORLOOP(i, vd[i] = vs2[i]&vs1[i]))
VOPI_VVV_REF_DEF(vor ,           FORLOOP(i, vd[i] = vs2[i]|vs1[i]))
VOPI_VVV_REF_DEF(vxor,           FORLOOP(i, vd[i] = vs2[i]^vs1[i]))
VOPI_VVV_REF_DEF(vrgather,       FORLOOP(i, vd[i] = vs2[vs1[i]]))
VOPI_VVV_REF_DEF(vsll,           FORLOOP(i, vd[i] = vs2[i]<<(vs1[i] & (sizeof(vs2[i])*8-1))))
VOPI_VVV_REF_DEF(vsrl,           FORLOOP(i, vd[i] = vs2[i]>>(vs1[i] & (sizeof(vs2[i])*8-1))))
VOPI_VVV_REF_DEF(vsra,           FORLOOP(i, vd[i] = vs2[i]>>(vs1[i] & (sizeof(vs2[i])*8-1))))

VOPI_VVV_M_REF_DEF(vadd,         FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]+vs1[i]))
VOPI_VVV_M_REF_DEF(vsub,         FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]-vs1[i]))
VOPI_VVV_M_REF_DEF(vmin,         FORLOOPIF(i, VMASK(i), vd[i] = std::min(vs2[i], vs1[i])))
VOPI_VVV_M_REF_DEF(vminu,        FORLOOPIF(i, VMASK(i), vd[i] = std::min(vs2[i], vs1[i])))
VOPI_VVV_M_REF_DEF(vmax,         FORLOOPIF(i, VMASK(i), vd[i] = std::max(vs2[i], vs1[i])))
VOPI_VVV_M_REF_DEF(vmaxu,        FORLOOPIF(i, VMASK(i), vd[i] = std::max(vs2[i], vs1[i])))
VOPI_VVV_M_REF_DEF(vand,         FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]&vs1[i]))
VOPI_VVV_M_REF_DEF(vor ,         FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]|vs1[i]))
VOPI_VVV_M_REF_DEF(vxor,         FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]^vs1[i]))
VOPI_VVV_M_REF_DEF(vrgather,     FORLOOPIF(i, VMASK(i), vd[i] = vs2[vs1[i]]))
VOPI_VVV_M_REF_DEF(vsll,         FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]<<(vs1[i] & (sizeof(vs2[i])*8-1))))
VOPI_VVV_M_REF_DEF(vsrl,         FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]>>(vs1[i] & (sizeof(vs2[i])*8-1))))
VOPI_VVV_M_REF_DEF(vsra,         FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]>>(vs1[i] & (sizeof(vs2[i])*8-1))))

VOPI_VXV_REF_DEF(vadd,           FORLOOP(i, vd[i] = vs2[i]+rs1[0]))
VOPI_VXV_REF_DEF(vsub,           FORLOOP(i, vd[i] = vs2[i]-rs1[0]))
VOPI_VXV_REF_DEF(vrsub,          FORLOOP(i, vd[i] = rs1[0]-vs2[i]))
VOPI_VXV_REF_DEF(vmin,           FORLOOP(i, vd[i] = std::min(vs2[i], rs1[0])))
VOPI_VXV_REF_DEF(vminu,          FORLOOP(i, vd[i] = std::min(vs2[i], rs1[0])))
VOPI_VXV_REF_DEF(vmax,           FORLOOP(i, vd[i] = std::max(vs2[i], rs1[0])))
VOPI_VXV_REF_DEF(vmaxu,          FORLOOP(i, vd[i] = std::max(vs2[i], rs1[0])))
VOPI_VXV_REF_DEF(vand,           FORLOOP(i, vd[i] = vs2[i]&rs1[0]))
VOPI_VXV_REF_DEF(vor ,           FORLOOP(i, vd[i] = vs2[i]|rs1[0]))
VOPI_VXV_REF_DEF(vxor,           FORLOOP(i, vd[i] = vs2[i]^rs1[0]))
VOPI_VXV_REF_DEF(vrgather,       FORLOOP(i, vd[i] = vs2[rs1[0]]))
VOPI_VXV_REF_DEF(vsll,           FORLOOP(i, vd[i] = vs2[i]<<(rs1[0] & (sizeof(vs2[i])*8-1))))
VOPI_VXV_REF_DEF(vsrl,           FORLOOP(i, vd[i] = vs2[i]>>(rs1[0] & (sizeof(vs2[i])*8-1))))
VOPI_VXV_REF_DEF(vsra,           FORLOOP(i, vd[i] = vs2[i]>>(rs1[0] & (sizeof(vs2[i])*8-1))))

VOPI_VXV_M_REF_DEF(vadd,         FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]+rs1[0]))
VOPI_VXV_M_REF_DEF(vsub,         FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]-rs1[0]))
VOPI_VXV_M_REF_DEF(vrsub,        FORLOOPIF(i, VMASK(i), vd[i] = rs1[0]-vs2[i]))
VOPI_VXV_M_REF_DEF(vmin,         FORLOOPIF(i, VMASK(i), vd[i] = std::min(vs2[i], rs1[0])))
VOPI_VXV_M_REF_DEF(vminu,        FORLOOPIF(i, VMASK(i), vd[i] = std::min(vs2[i], rs1[0])))
VOPI_VXV_M_REF_DEF(vmax,         FORLOOPIF(i, VMASK(i), vd[i] = std::max(vs2[i], rs1[0])))
VOPI_VXV_M_REF_DEF(vmaxu,        FORLOOPIF(i, VMASK(i), vd[i] = std::max(vs2[i], rs1[0])))
VOPI_VXV_M_REF_DEF(vand,         FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]&rs1[0]))
VOPI_VXV_M_REF_DEF(vor ,         FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]|rs1[0]))
VOPI_VXV_M_REF_DEF(vxor,         FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]^rs1[0]))
VOPI_VXV_M_REF_DEF(vrgather,     FORLOOPIF(i, VMASK(i), vd[i] = vs2[rs1[0]]))
VOPI_VXV_M_REF_DEF(vsll,         FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]<<(rs1[0] & (sizeof(vs2[i])*8-1))))
VOPI_VXV_M_REF_DEF(vsrl,         FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]>>(rs1[0] & (sizeof(vs2[i])*8-1))))
VOPI_VXV_M_REF_DEF(vsra,         FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]>>(rs1[0] & (sizeof(vs2[i])*8-1))))

VOPI_VV_REF_DEF(vmv,             FORLOOP(i, vd[i] = vs[i]))

VOPF_VVV_REF_DEF(vfadd,          FORLOOP(i, vd[i] = vs2[i]+vs1[i]))
VOPF_VVV_REF_DEF(vfsub,          FORLOOP(i, vd[i] = vs2[i]-vs1[i]))
VOPF_VVV_REF_DEF(vfmul,          FORLOOP(i, vd[i] = vs2[i]*vs1[i]))
VOPF_VVV_REF_DEF(vfdiv,          FORLOOP(i, vd[i] = vs2[i]/vs1[i]))
VOPF_VVV_REF_DEF(vfmax,          FORLOOP(i, vd[i] = std::max(vs2[i],vs1[i])))
VOPF_VVV_REF_DEF(vfmin,          FORLOOP(i, vd[i] = std::min(vs2[i],vs1[i])))
VOPF_VVV_REF_DEF(vfsgnj,         FORLOOP(i, vd[i] = vs1[i]>0 ? fabs(vs2[i]) : -fabs(vs2[i])))
VOPF_VVV_REF_DEF(vfsgnjn,        FORLOOP(i, vd[i] = vs1[i]<0 ? fabs(vs2[i]) : -fabs(vs2[i])))
VOPF_VVV_REF_DEF(vfsgnjx,        FORLOOP(i, vd[i] = vs1[i]>0 ? vs2[i] : -vs2[i]))

VOPI_VVV_M_REF_DEF(vfadd,        FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]+vs1[i]))
VOPI_VVV_M_REF_DEF(vfsub,        FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]-vs1[i]))
VOPI_VVV_M_REF_DEF(vfmul,        FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]*vs1[i]))
VOPI_VVV_M_REF_DEF(vfdiv,        FORLOOPIF(i, VMASK(i), vd[i] = vs2[i]/vs1[i]))
VOPI_VVV_M_REF_DEF(vfmax,        FORLOOPIF(i, VMASK(i), vd[i] = std::max(vs2[i],vs1[i])))
VOPI_VVV_M_REF_DEF(vfmin,        FORLOOPIF(i, VMASK(i), vd[i] = std::min(vs2[i],vs1[i])))
VOPI_VVV_M_REF_DEF(vfsgnj,       FORLOOPIF(i, VMASK(i), vd[i] = vs1[i]>0 ? fabs(vs2[i]) : -fabs(vs2[i])))
VOPI_VVV_M_REF_DEF(vfsgnjn,      FORLOOPIF(i, VMASK(i), vd[i] = vs1[i]<0 ? fabs(vs2[i]) : -fabs(vs2[i])))
VOPI_VVV_M_REF_DEF(vfsgnjx,      FORLOOPIF(i, VMASK(i), vd[i] = vs1[i]>0 ? vs2[i] : -vs2[i]))
