#include "tdef/opi_vvv.h"
#include "tdef/opi_vxv.h"
#include "tdef/opi_vv.h"
#include "tdef/opi_vvmv.h"
#include "tdef/opi_vvm.h"
#include "tdef/opf_vvv.h"
#include "tdef/opf_vfv.h"
#include "tdef/test_template.h"

#define TEST_OPI_VV_ALL() \
TEST_OPI_VV_GROUP(vmv) \

#define TEST_OPI_VVV_ALL() \
TEST_OPI_VVV_GROUP(vadd) \
TEST_OPI_VVV_GROUP(vsub) \
TEST_OPI_VVV_III_GROUP(vmin) \
TEST_OPI_VVV_III_GROUP(vmax) \
TEST_OPI_VVV_UUU_GROUP(vminu) \
TEST_OPI_VVV_UUU_GROUP(vmaxu) \
TEST_OPI_VVV_GROUP(vand) \
TEST_OPI_VVV_GROUP(vor) \
TEST_OPI_VVV_GROUP(vxor) \
/*TEST_OPI_VVV_GROUP(vrgather)*/ \
TEST_OPI_VVV_IUI_GROUP(vsll) \
TEST_OPI_VVV_UUU_GROUP(vsll) \
TEST_OPI_VVV_UUU_GROUP(vsrl) \
TEST_OPI_VVV_IUI_GROUP(vsra) \

#define TEST_OPI_VVV_M_ALL() \
TEST_OPI_VVV_M_GROUP(vadd)\
TEST_OPI_VVV_M_GROUP(vsub)\
TEST_OPI_VVV_III_M_GROUP(vmin)\
TEST_OPI_VVV_III_M_GROUP(vmax)\
TEST_OPI_VVV_UUU_M_GROUP(vminu)\
TEST_OPI_VVV_UUU_M_GROUP(vmaxu)\
TEST_OPI_VVV_M_GROUP(vand)\
TEST_OPI_VVV_M_GROUP(vor)\
TEST_OPI_VVV_M_GROUP(vxor)\
/*TEST_OPI_VVV_M_GROUP(vrgather)*/\
TEST_OPI_VVV_IUI_M_GROUP(vsll)\
TEST_OPI_VVV_UUU_M_GROUP(vsll)\
TEST_OPI_VVV_UUU_M_GROUP(vsrl)\
TEST_OPI_VVV_IUI_M_GROUP(vsra)\

#define TEST_OPI_VXV_ALL() \
TEST_OPI_VXV_GROUP(vadd) \
TEST_OPI_VXV_GROUP(vsub) \
TEST_OPI_VXV_GROUP(vrsub) \
TEST_OPI_VXV_III_GROUP(vmin) \
TEST_OPI_VXV_III_GROUP(vmax) \
TEST_OPI_VXV_UUU_GROUP(vminu) \
TEST_OPI_VXV_UUU_GROUP(vmaxu) \
TEST_OPI_VXV_GROUP(vand) \
TEST_OPI_VXV_GROUP(vor) \
TEST_OPI_VXV_GROUP(vxor) \
TEST_OPI_VXV_IUI_GROUP(vsll) \
TEST_OPI_VXV_UUU_GROUP(vsll) \
TEST_OPI_VXV_UUU_GROUP(vsrl) \
TEST_OPI_VXV_IUI_GROUP(vsra) \

#define TEST_OPI_VXV_M_ALL()\
TEST_OPI_VXV_M_GROUP(vadd)\
TEST_OPI_VXV_M_GROUP(vsub)\
TEST_OPI_VXV_M_GROUP(vrsub)\
TEST_OPI_VXV_III_M_GROUP(vmin)\
TEST_OPI_VXV_III_M_GROUP(vmax)\
TEST_OPI_VXV_UUU_M_GROUP(vminu)\
TEST_OPI_VXV_UUU_M_GROUP(vmaxu)\
TEST_OPI_VXV_M_GROUP(vand)\
TEST_OPI_VXV_M_GROUP(vor)\
TEST_OPI_VXV_M_GROUP(vxor)\
TEST_OPI_VXV_IUI_M_GROUP(vsll)\
TEST_OPI_VXV_UUU_M_GROUP(vsll)\
TEST_OPI_VXV_UUU_M_GROUP(vsrl)\
TEST_OPI_VXV_IUI_M_GROUP(vsra)\

#define TEST_OPF_VVV_ALL() \
TEST_OPF_VVV_GROUP(vfadd) \
TEST_OPF_VVV_GROUP(vfsub) \
TEST_OPF_VVV_GROUP(vfmul) \
TEST_OPF_VVV_GROUP(vfdiv) \
TEST_OPF_VVV_GROUP(vfmax) \
TEST_OPF_VVV_GROUP(vfmin) \
TEST_OPF_VVV_GROUP(vfsgnj) \
TEST_OPF_VVV_GROUP(vfsgnjn) \
TEST_OPF_VVV_GROUP(vfsgnjx) \

#define TEST_OPF_VVV_M_ALL() \
TEST_OPF_VVV_M_GROUP(vfadd) \
TEST_OPF_VVV_M_GROUP(vfsub) \
TEST_OPF_VVV_M_GROUP(vfmul) \
TEST_OPF_VVV_M_GROUP(vfdiv) \
TEST_OPF_VVV_M_GROUP(vfmax) \
TEST_OPF_VVV_M_GROUP(vfmin) \
TEST_OPF_VVV_M_GROUP(vfsgnj) \
TEST_OPF_VVV_M_GROUP(vfsgnjn) \
TEST_OPF_VVV_M_GROUP(vfsgnjx) \

#define TEST_OPI_VVMV_ALL() \
TEST_OPI_VVMV_GROUP(vmerge) \
TEST_OPI_VVMV_GROUP(vadc) \
TEST_OPI_VVMV_GROUP(vsbc) \

#define TEST_OPF_VFV_ALL() \
TEST_OPF_VFV_GROUP(vfadd) \
TEST_OPF_VFV_GROUP(vfsub) \
TEST_OPF_VFV_GROUP(vfrsub) \
TEST_OPF_VFV_GROUP(vfmul) \
TEST_OPF_VFV_GROUP(vfdiv) \
TEST_OPF_VFV_GROUP(vfrdiv) \
TEST_OPF_VFV_GROUP(vfmax) \
TEST_OPF_VFV_GROUP(vfmin) \
TEST_OPF_VFV_GROUP(vfsgnj) \
TEST_OPF_VFV_GROUP(vfsgnjn) \
TEST_OPF_VFV_GROUP(vfsgnjx) \

#define TEST_OPF_VFV_M_ALL() \
TEST_OPF_VFV_M_GROUP(vfadd) \
TEST_OPF_VFV_M_GROUP(vfsub) \
TEST_OPF_VFV_M_GROUP(vfrsub) \
TEST_OPF_VFV_M_GROUP(vfmul) \
TEST_OPF_VFV_M_GROUP(vfdiv) \
TEST_OPF_VFV_M_GROUP(vfrdiv) \
TEST_OPF_VFV_M_GROUP(vfmax) \
TEST_OPF_VFV_M_GROUP(vfmin) \
TEST_OPF_VFV_M_GROUP(vfsgnj) \
TEST_OPF_VFV_M_GROUP(vfsgnjn) \
TEST_OPF_VFV_M_GROUP(vfsgnjx) \

#define TEST_OPI_VVM_ALL() \
TEST_OPI_VVM_GROUP(vmseq) \
TEST_OPI_VVM_GROUP(vmsne) \
TEST_OPI_VVM_UU_GROUP(vmsltu) \
TEST_OPI_VVM_II_GROUP(vmslt) \
TEST_OPI_VVM_UU_GROUP(vmsleu) \
TEST_OPI_VVM_II_GROUP(vmsle) \
TEST_OPI_VVM_GROUP(vmadc) \
TEST_OPI_VVM_GROUP(vmsbc) \
