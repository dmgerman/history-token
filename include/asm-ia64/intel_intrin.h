macro_line|#ifndef _ASM_IA64_INTEL_INTRIN_H
DECL|macro|_ASM_IA64_INTEL_INTRIN_H
mdefine_line|#define _ASM_IA64_INTEL_INTRIN_H
multiline_comment|/*&n; * Intel Compiler Intrinsics&n; *&n; * Copyright (C) 2002,2003 Jun Nakajima &lt;jun.nakajima@intel.com&gt;&n; * Copyright (C) 2002,2003 Suresh Siddha &lt;suresh.b.siddha@intel.com&gt;&n; *&n; */
macro_line|#include &lt;asm/types.h&gt;
r_void
id|__lfetch
c_func
(paren
r_int
id|lfhint
comma
r_void
op_star
id|y
)paren
suffix:semicolon
r_void
id|__lfetch_excl
c_func
(paren
r_int
id|lfhint
comma
r_void
op_star
id|y
)paren
suffix:semicolon
r_void
id|__lfetch_fault
c_func
(paren
r_int
id|lfhint
comma
r_void
op_star
id|y
)paren
suffix:semicolon
r_void
id|__lfetch_fault_excl
c_func
(paren
r_int
id|lfhint
comma
r_void
op_star
id|y
)paren
suffix:semicolon
multiline_comment|/* In the following, whichFloatReg should be an integer from 0-127 */
r_void
id|__ldfs
c_func
(paren
r_const
r_int
id|whichFloatReg
comma
r_void
op_star
id|src
)paren
suffix:semicolon
r_void
id|__ldfd
c_func
(paren
r_const
r_int
id|whichFloatReg
comma
r_void
op_star
id|src
)paren
suffix:semicolon
r_void
id|__ldfe
c_func
(paren
r_const
r_int
id|whichFloatReg
comma
r_void
op_star
id|src
)paren
suffix:semicolon
r_void
id|__ldf8
c_func
(paren
r_const
r_int
id|whichFloatReg
comma
r_void
op_star
id|src
)paren
suffix:semicolon
r_void
id|__ldf_fill
c_func
(paren
r_const
r_int
id|whichFloatReg
comma
r_void
op_star
id|src
)paren
suffix:semicolon
r_void
id|__stfs
c_func
(paren
r_void
op_star
id|dst
comma
r_const
r_int
id|whichFloatReg
)paren
suffix:semicolon
r_void
id|__stfd
c_func
(paren
r_void
op_star
id|dst
comma
r_const
r_int
id|whichFloatReg
)paren
suffix:semicolon
r_void
id|__stfe
c_func
(paren
r_void
op_star
id|dst
comma
r_const
r_int
id|whichFloatReg
)paren
suffix:semicolon
r_void
id|__stf8
c_func
(paren
r_void
op_star
id|dst
comma
r_const
r_int
id|whichFloatReg
)paren
suffix:semicolon
r_void
id|__stf_spill
c_func
(paren
r_void
op_star
id|dst
comma
r_const
r_int
id|whichFloatReg
)paren
suffix:semicolon
r_void
id|__st1_rel
c_func
(paren
r_void
op_star
id|dst
comma
r_const
id|__s8
id|value
)paren
suffix:semicolon
r_void
id|__st2_rel
c_func
(paren
r_void
op_star
id|dst
comma
r_const
id|__s16
id|value
)paren
suffix:semicolon
r_void
id|__st4_rel
c_func
(paren
r_void
op_star
id|dst
comma
r_const
id|__s32
id|value
)paren
suffix:semicolon
r_void
id|__st8_rel
c_func
(paren
r_void
op_star
id|dst
comma
r_const
id|__s64
id|value
)paren
suffix:semicolon
id|__u8
id|__ld1_acq
c_func
(paren
r_void
op_star
id|src
)paren
suffix:semicolon
id|__u16
id|__ld2_acq
c_func
(paren
r_void
op_star
id|src
)paren
suffix:semicolon
id|__u32
id|__ld4_acq
c_func
(paren
r_void
op_star
id|src
)paren
suffix:semicolon
id|__u64
id|__ld8_acq
c_func
(paren
r_void
op_star
id|src
)paren
suffix:semicolon
id|__u64
id|__fetchadd4_acq
c_func
(paren
id|__u32
op_star
id|addend
comma
r_const
r_int
id|increment
)paren
suffix:semicolon
id|__u64
id|__fetchadd4_rel
c_func
(paren
id|__u32
op_star
id|addend
comma
r_const
r_int
id|increment
)paren
suffix:semicolon
id|__u64
id|__fetchadd8_acq
c_func
(paren
id|__u64
op_star
id|addend
comma
r_const
r_int
id|increment
)paren
suffix:semicolon
id|__u64
id|__fetchadd8_rel
c_func
(paren
id|__u64
op_star
id|addend
comma
r_const
r_int
id|increment
)paren
suffix:semicolon
id|__u64
id|__getf_exp
c_func
(paren
r_float
id|d
)paren
suffix:semicolon
multiline_comment|/* OS Related Itanium(R) Intrinsics  */
multiline_comment|/* The names to use for whichReg and whichIndReg below come from&n;   the include file asm/ia64regs.h */
id|__u64
id|__getIndReg
c_func
(paren
r_const
r_int
id|whichIndReg
comma
id|__s64
id|index
)paren
suffix:semicolon
id|__u64
id|__getReg
c_func
(paren
r_const
r_int
id|whichReg
)paren
suffix:semicolon
r_void
id|__setIndReg
c_func
(paren
r_const
r_int
id|whichIndReg
comma
id|__s64
id|index
comma
id|__u64
id|value
)paren
suffix:semicolon
r_void
id|__setReg
c_func
(paren
r_const
r_int
id|whichReg
comma
id|__u64
id|value
)paren
suffix:semicolon
r_void
id|__mf
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|__mfa
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|__synci
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|__itcd
c_func
(paren
id|__s64
id|pa
)paren
suffix:semicolon
r_void
id|__itci
c_func
(paren
id|__s64
id|pa
)paren
suffix:semicolon
r_void
id|__itrd
c_func
(paren
id|__s64
id|whichTransReg
comma
id|__s64
id|pa
)paren
suffix:semicolon
r_void
id|__itri
c_func
(paren
id|__s64
id|whichTransReg
comma
id|__s64
id|pa
)paren
suffix:semicolon
r_void
id|__ptce
c_func
(paren
id|__s64
id|va
)paren
suffix:semicolon
r_void
id|__ptcl
c_func
(paren
id|__s64
id|va
comma
id|__s64
id|pagesz
)paren
suffix:semicolon
r_void
id|__ptcg
c_func
(paren
id|__s64
id|va
comma
id|__s64
id|pagesz
)paren
suffix:semicolon
r_void
id|__ptcga
c_func
(paren
id|__s64
id|va
comma
id|__s64
id|pagesz
)paren
suffix:semicolon
r_void
id|__ptri
c_func
(paren
id|__s64
id|va
comma
id|__s64
id|pagesz
)paren
suffix:semicolon
r_void
id|__ptrd
c_func
(paren
id|__s64
id|va
comma
id|__s64
id|pagesz
)paren
suffix:semicolon
r_void
id|__invala
(paren
r_void
)paren
suffix:semicolon
r_void
id|__invala_gr
c_func
(paren
r_const
r_int
id|whichGeneralReg
multiline_comment|/* 0-127 */
)paren
suffix:semicolon
r_void
id|__invala_fr
c_func
(paren
r_const
r_int
id|whichFloatReg
multiline_comment|/* 0-127 */
)paren
suffix:semicolon
r_void
id|__nop
c_func
(paren
r_const
r_int
)paren
suffix:semicolon
r_void
id|__fc
c_func
(paren
id|__u64
op_star
id|addr
)paren
suffix:semicolon
r_void
id|__sum
c_func
(paren
r_int
id|mask
)paren
suffix:semicolon
r_void
id|__rum
c_func
(paren
r_int
id|mask
)paren
suffix:semicolon
r_void
id|__ssm
c_func
(paren
r_int
id|mask
)paren
suffix:semicolon
r_void
id|__rsm
c_func
(paren
r_int
id|mask
)paren
suffix:semicolon
id|__u64
id|__thash
c_func
(paren
id|__s64
)paren
suffix:semicolon
id|__u64
id|__ttag
c_func
(paren
id|__s64
)paren
suffix:semicolon
id|__s64
id|__tpa
c_func
(paren
id|__s64
)paren
suffix:semicolon
multiline_comment|/* Intrinsics for implementing get/put_user macros */
r_void
id|__st_user
c_func
(paren
r_const
r_char
op_star
id|tableName
comma
id|__u64
id|addr
comma
r_char
id|size
comma
r_char
id|relocType
comma
id|__u64
id|val
)paren
suffix:semicolon
r_void
id|__ld_user
c_func
(paren
r_const
r_char
op_star
id|tableName
comma
id|__u64
id|addr
comma
r_char
id|size
comma
r_char
id|relocType
)paren
suffix:semicolon
multiline_comment|/* This intrinsic does not generate code, it creates a barrier across which&n; * the compiler will not schedule data access instructions.&n; */
r_void
id|__memory_barrier
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|__isrlz
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|__dsrlz
c_func
(paren
r_void
)paren
suffix:semicolon
id|__u64
id|_m64_mux1
c_func
(paren
id|__u64
id|a
comma
r_const
r_int
id|n
)paren
suffix:semicolon
id|__u64
id|__thash
c_func
(paren
id|__u64
)paren
suffix:semicolon
multiline_comment|/* Lock and Atomic Operation Related Intrinsics */
id|__u64
id|_InterlockedExchange8
c_func
(paren
r_volatile
id|__u8
op_star
id|trgt
comma
id|__u8
id|value
)paren
suffix:semicolon
id|__u64
id|_InterlockedExchange16
c_func
(paren
r_volatile
id|__u16
op_star
id|trgt
comma
id|__u16
id|value
)paren
suffix:semicolon
id|__s64
id|_InterlockedExchange
c_func
(paren
r_volatile
id|__u32
op_star
id|trgt
comma
id|__u32
id|value
)paren
suffix:semicolon
id|__s64
id|_InterlockedExchange64
c_func
(paren
r_volatile
id|__u64
op_star
id|trgt
comma
id|__u64
id|value
)paren
suffix:semicolon
id|__u64
id|_InterlockedCompareExchange8_rel
c_func
(paren
r_volatile
id|__u8
op_star
id|dest
comma
id|__u64
id|xchg
comma
id|__u64
id|comp
)paren
suffix:semicolon
id|__u64
id|_InterlockedCompareExchange8_acq
c_func
(paren
r_volatile
id|__u8
op_star
id|dest
comma
id|__u64
id|xchg
comma
id|__u64
id|comp
)paren
suffix:semicolon
id|__u64
id|_InterlockedCompareExchange16_rel
c_func
(paren
r_volatile
id|__u16
op_star
id|dest
comma
id|__u64
id|xchg
comma
id|__u64
id|comp
)paren
suffix:semicolon
id|__u64
id|_InterlockedCompareExchange16_acq
c_func
(paren
r_volatile
id|__u16
op_star
id|dest
comma
id|__u64
id|xchg
comma
id|__u64
id|comp
)paren
suffix:semicolon
id|__u64
id|_InterlockedCompareExchange_rel
c_func
(paren
r_volatile
id|__u32
op_star
id|dest
comma
id|__u64
id|xchg
comma
id|__u64
id|comp
)paren
suffix:semicolon
id|__u64
id|_InterlockedCompareExchange_acq
c_func
(paren
r_volatile
id|__u32
op_star
id|dest
comma
id|__u64
id|xchg
comma
id|__u64
id|comp
)paren
suffix:semicolon
id|__u64
id|_InterlockedCompareExchange64_rel
c_func
(paren
r_volatile
id|__u64
op_star
id|dest
comma
id|__u64
id|xchg
comma
id|__u64
id|comp
)paren
suffix:semicolon
id|__u64
id|_InterlockedCompareExchange64_acq
c_func
(paren
r_volatile
id|__u64
op_star
id|dest
comma
id|__u64
id|xchg
comma
id|__u64
id|comp
)paren
suffix:semicolon
id|__s64
id|_m64_dep_mi
c_func
(paren
r_const
r_int
id|v
comma
id|__s64
id|s
comma
r_const
r_int
id|p
comma
r_const
r_int
id|len
)paren
suffix:semicolon
id|__s64
id|_m64_shrp
c_func
(paren
id|__s64
id|a
comma
id|__s64
id|b
comma
r_const
r_int
id|count
)paren
suffix:semicolon
id|__s64
id|_m64_popcnt
c_func
(paren
id|__s64
id|a
)paren
suffix:semicolon
DECL|macro|ia64_barrier
mdefine_line|#define ia64_barrier()&t;&t;__memory_barrier()
DECL|macro|ia64_stop
mdefine_line|#define ia64_stop()&t;/* Nothing: As of now stop bit is generated for each&n;&t;&t; &t; * intrinsic&n;&t;&t; &t; */
DECL|macro|ia64_getreg
mdefine_line|#define ia64_getreg&t;&t;__getReg
DECL|macro|ia64_setreg
mdefine_line|#define ia64_setreg&t;&t;__setReg
DECL|macro|ia64_hint
mdefine_line|#define ia64_hint(x)
DECL|macro|ia64_mux1_brcst
mdefine_line|#define ia64_mux1_brcst&t; 0
DECL|macro|ia64_mux1_mix
mdefine_line|#define ia64_mux1_mix&t;&t; 8
DECL|macro|ia64_mux1_shuf
mdefine_line|#define ia64_mux1_shuf&t;&t; 9
DECL|macro|ia64_mux1_alt
mdefine_line|#define ia64_mux1_alt&t;&t;10
DECL|macro|ia64_mux1_rev
mdefine_line|#define ia64_mux1_rev&t;&t;11
DECL|macro|ia64_mux1
mdefine_line|#define ia64_mux1&t;&t;_m64_mux1
DECL|macro|ia64_popcnt
mdefine_line|#define ia64_popcnt&t;&t;_m64_popcnt
DECL|macro|ia64_getf_exp
mdefine_line|#define ia64_getf_exp&t;&t;__getf_exp
DECL|macro|ia64_shrp
mdefine_line|#define ia64_shrp&t;&t;_m64_shrp
DECL|macro|ia64_tpa
mdefine_line|#define ia64_tpa&t;&t;__tpa
DECL|macro|ia64_invala
mdefine_line|#define ia64_invala&t;&t;__invala
DECL|macro|ia64_invala_gr
mdefine_line|#define ia64_invala_gr&t;&t;__invala_gr
DECL|macro|ia64_invala_fr
mdefine_line|#define ia64_invala_fr&t;&t;__invala_fr
DECL|macro|ia64_nop
mdefine_line|#define ia64_nop&t;&t;__nop
DECL|macro|ia64_sum
mdefine_line|#define ia64_sum&t;&t;__sum
DECL|macro|ia64_ssm
mdefine_line|#define ia64_ssm&t;&t;__ssm
DECL|macro|ia64_rum
mdefine_line|#define ia64_rum&t;&t;__rum
DECL|macro|ia64_rsm
mdefine_line|#define ia64_rsm&t;&t;__rsm
DECL|macro|ia64_fc
mdefine_line|#define ia64_fc &t;&t;__fc
DECL|macro|ia64_ldfs
mdefine_line|#define ia64_ldfs&t;&t;__ldfs
DECL|macro|ia64_ldfd
mdefine_line|#define ia64_ldfd&t;&t;__ldfd
DECL|macro|ia64_ldfe
mdefine_line|#define ia64_ldfe&t;&t;__ldfe
DECL|macro|ia64_ldf8
mdefine_line|#define ia64_ldf8&t;&t;__ldf8
DECL|macro|ia64_ldf_fill
mdefine_line|#define ia64_ldf_fill&t;&t;__ldf_fill
DECL|macro|ia64_stfs
mdefine_line|#define ia64_stfs&t;&t;__stfs
DECL|macro|ia64_stfd
mdefine_line|#define ia64_stfd&t;&t;__stfd
DECL|macro|ia64_stfe
mdefine_line|#define ia64_stfe&t;&t;__stfe
DECL|macro|ia64_stf8
mdefine_line|#define ia64_stf8&t;&t;__stf8
DECL|macro|ia64_stf_spill
mdefine_line|#define ia64_stf_spill&t;&t;__stf_spill
DECL|macro|ia64_mf
mdefine_line|#define ia64_mf&t;&t;__mf
DECL|macro|ia64_mfa
mdefine_line|#define ia64_mfa&t;&t;__mfa
DECL|macro|ia64_fetchadd4_acq
mdefine_line|#define ia64_fetchadd4_acq&t;__fetchadd4_acq
DECL|macro|ia64_fetchadd4_rel
mdefine_line|#define ia64_fetchadd4_rel&t;__fetchadd4_rel
DECL|macro|ia64_fetchadd8_acq
mdefine_line|#define ia64_fetchadd8_acq&t;__fetchadd8_acq
DECL|macro|ia64_fetchadd8_rel
mdefine_line|#define ia64_fetchadd8_rel&t;__fetchadd8_rel
DECL|macro|ia64_xchg1
mdefine_line|#define ia64_xchg1&t;&t;_InterlockedExchange8
DECL|macro|ia64_xchg2
mdefine_line|#define ia64_xchg2&t;&t;_InterlockedExchange16
DECL|macro|ia64_xchg4
mdefine_line|#define ia64_xchg4&t;&t;_InterlockedExchange
DECL|macro|ia64_xchg8
mdefine_line|#define ia64_xchg8&t;&t;_InterlockedExchange64
DECL|macro|ia64_cmpxchg1_rel
mdefine_line|#define ia64_cmpxchg1_rel&t;_InterlockedCompareExchange8_rel
DECL|macro|ia64_cmpxchg1_acq
mdefine_line|#define ia64_cmpxchg1_acq&t;_InterlockedCompareExchange8_acq
DECL|macro|ia64_cmpxchg2_rel
mdefine_line|#define ia64_cmpxchg2_rel&t;_InterlockedCompareExchange16_rel
DECL|macro|ia64_cmpxchg2_acq
mdefine_line|#define ia64_cmpxchg2_acq&t;_InterlockedCompareExchange16_acq
DECL|macro|ia64_cmpxchg4_rel
mdefine_line|#define ia64_cmpxchg4_rel&t;_InterlockedCompareExchange_rel
DECL|macro|ia64_cmpxchg4_acq
mdefine_line|#define ia64_cmpxchg4_acq&t;_InterlockedCompareExchange_acq
DECL|macro|ia64_cmpxchg8_rel
mdefine_line|#define ia64_cmpxchg8_rel&t;_InterlockedCompareExchange64_rel
DECL|macro|ia64_cmpxchg8_acq
mdefine_line|#define ia64_cmpxchg8_acq&t;_InterlockedCompareExchange64_acq
DECL|macro|__ia64_set_dbr
mdefine_line|#define __ia64_set_dbr(index, val)&t;&bslash;&n;&t;&t;__setIndReg(_IA64_REG_INDR_DBR, index, val)
DECL|macro|ia64_set_ibr
mdefine_line|#define ia64_set_ibr(index, val)&t;&bslash;&n;&t;&t;__setIndReg(_IA64_REG_INDR_IBR, index, val)
DECL|macro|ia64_set_pkr
mdefine_line|#define ia64_set_pkr(index, val)&t;&bslash;&n;&t;&t;__setIndReg(_IA64_REG_INDR_PKR, index, val)
DECL|macro|ia64_set_pmc
mdefine_line|#define ia64_set_pmc(index, val)&t;&bslash;&n;&t;&t;__setIndReg(_IA64_REG_INDR_PMC, index, val)
DECL|macro|ia64_set_pmd
mdefine_line|#define ia64_set_pmd(index, val)&t;&bslash;&n;&t;&t;__setIndReg(_IA64_REG_INDR_PMD, index, val)
DECL|macro|ia64_set_rr
mdefine_line|#define ia64_set_rr(index, val)&t;&bslash;&n;&t;&t;__setIndReg(_IA64_REG_INDR_RR, index, val)
DECL|macro|ia64_get_cpuid
mdefine_line|#define ia64_get_cpuid(index) &t;__getIndReg(_IA64_REG_INDR_CPUID, index)
DECL|macro|__ia64_get_dbr
mdefine_line|#define __ia64_get_dbr(index) &t;__getIndReg(_IA64_REG_INDR_DBR, index)
DECL|macro|ia64_get_ibr
mdefine_line|#define ia64_get_ibr(index) &t;__getIndReg(_IA64_REG_INDR_IBR, index)
DECL|macro|ia64_get_pkr
mdefine_line|#define ia64_get_pkr(index) &t;__getIndReg(_IA64_REG_INDR_PKR, index)
DECL|macro|ia64_get_pmc
mdefine_line|#define ia64_get_pmc(index) &t;__getIndReg(_IA64_REG_INDR_PMC, index)
DECL|macro|ia64_get_pmd
mdefine_line|#define ia64_get_pmd(index)  &t;__getIndReg(_IA64_REG_INDR_PMD, index)
DECL|macro|ia64_get_rr
mdefine_line|#define ia64_get_rr(index) &t;__getIndReg(_IA64_REG_INDR_RR, index)
DECL|macro|ia64_srlz_d
mdefine_line|#define ia64_srlz_d&t;&t;__dsrlz
DECL|macro|ia64_srlz_i
mdefine_line|#define ia64_srlz_i&t;&t;__isrlz
DECL|macro|ia64_st1_rel
mdefine_line|#define ia64_st1_rel&t;&t;__st1_rel
DECL|macro|ia64_st2_rel
mdefine_line|#define ia64_st2_rel&t;&t;__st2_rel
DECL|macro|ia64_st4_rel
mdefine_line|#define ia64_st4_rel&t;&t;__st4_rel
DECL|macro|ia64_st8_rel
mdefine_line|#define ia64_st8_rel&t;&t;__st8_rel
DECL|macro|ia64_ld1_acq
mdefine_line|#define ia64_ld1_acq&t;&t;__ld1_acq
DECL|macro|ia64_ld2_acq
mdefine_line|#define ia64_ld2_acq&t;&t;__ld2_acq
DECL|macro|ia64_ld4_acq
mdefine_line|#define ia64_ld4_acq&t;&t;__ld4_acq
DECL|macro|ia64_ld8_acq
mdefine_line|#define ia64_ld8_acq&t;&t;__ld8_acq
DECL|macro|ia64_sync_i
mdefine_line|#define ia64_sync_i&t;&t;__synci
DECL|macro|ia64_thash
mdefine_line|#define ia64_thash&t;&t;__thash
DECL|macro|ia64_ttag
mdefine_line|#define ia64_ttag&t;&t;__ttag
DECL|macro|ia64_itcd
mdefine_line|#define ia64_itcd&t;&t;__itcd
DECL|macro|ia64_itci
mdefine_line|#define ia64_itci&t;&t;__itci
DECL|macro|ia64_itrd
mdefine_line|#define ia64_itrd&t;&t;__itrd
DECL|macro|ia64_itri
mdefine_line|#define ia64_itri&t;&t;__itri
DECL|macro|ia64_ptce
mdefine_line|#define ia64_ptce&t;&t;__ptce
DECL|macro|ia64_ptcl
mdefine_line|#define ia64_ptcl&t;&t;__ptcl
DECL|macro|ia64_ptcg
mdefine_line|#define ia64_ptcg&t;&t;__ptcg
DECL|macro|ia64_ptcga
mdefine_line|#define ia64_ptcga&t;&t;__ptcga
DECL|macro|ia64_ptri
mdefine_line|#define ia64_ptri&t;&t;__ptri
DECL|macro|ia64_ptrd
mdefine_line|#define ia64_ptrd&t;&t;__ptrd
DECL|macro|ia64_dep_mi
mdefine_line|#define ia64_dep_mi&t;&t;_m64_dep_mi
multiline_comment|/* Values for lfhint in __lfetch and __lfetch_fault */
DECL|macro|ia64_lfhint_none
mdefine_line|#define ia64_lfhint_none   &t;0
DECL|macro|ia64_lfhint_nt1
mdefine_line|#define ia64_lfhint_nt1    &t;1
DECL|macro|ia64_lfhint_nt2
mdefine_line|#define ia64_lfhint_nt2    &t;2
DECL|macro|ia64_lfhint_nta
mdefine_line|#define ia64_lfhint_nta    &t;3
DECL|macro|ia64_lfetch
mdefine_line|#define ia64_lfetch&t;&t;__lfetch
DECL|macro|ia64_lfetch_excl
mdefine_line|#define ia64_lfetch_excl&t;__lfetch_excl
DECL|macro|ia64_lfetch_fault
mdefine_line|#define ia64_lfetch_fault&t;__lfetch_fault
DECL|macro|ia64_lfetch_fault_excl
mdefine_line|#define ia64_lfetch_fault_excl&t;__lfetch_fault_excl
DECL|macro|ia64_intrin_local_irq_restore
mdefine_line|#define ia64_intrin_local_irq_restore(x)&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((x) != 0) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ia64_ssm(IA64_PSR_I);&t;&t;&t;&bslash;&n;&t;&t;ia64_srlz_d();&t;&t;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ia64_rsm(IA64_PSR_I);&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* _ASM_IA64_INTEL_INTRIN_H */
eof
