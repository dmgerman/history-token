macro_line|#ifndef _ASM_IA64_INTRINSICS_H
DECL|macro|_ASM_IA64_INTRINSICS_H
mdefine_line|#define _ASM_IA64_INTRINSICS_H
multiline_comment|/*&n; * Compiler-dependent intrinsics.&n; *&n; * Copyright (C) 2002-2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* include compiler specific intrinsics */
macro_line|#include &lt;asm/ia64regs.h&gt;
macro_line|#ifdef __INTEL_COMPILER
macro_line|#include &lt;asm/intel_intrin.h&gt;
macro_line|#else
macro_line|#include &lt;asm/gcc_intrin.h&gt;
macro_line|#endif
multiline_comment|/*&n; * Force an unresolved reference if someone tries to use&n; * ia64_fetch_and_add() with a bad value.&n; */
r_extern
r_int
r_int
id|__bad_size_for_ia64_fetch_and_add
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__bad_increment_for_ia64_fetch_and_add
(paren
r_void
)paren
suffix:semicolon
DECL|macro|IA64_FETCHADD
mdefine_line|#define IA64_FETCHADD(tmp,v,n,sz,sem)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (sz) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 4:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;        tmp = ia64_fetchadd4_##sem((unsigned int *) v, n);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 8:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;        tmp = ia64_fetchadd8_##sem((unsigned long *) v, n);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      default:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__bad_size_for_ia64_fetch_and_add();&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_fetchadd
mdefine_line|#define ia64_fetchadd(i,v,sem)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 _tmp;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;volatile __typeof__(*(v)) *_v = (v);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* Can&squot;t use a switch () here: gcc isn&squot;t always smart enough for that... */&t;&bslash;&n;&t;if ((i) == -16)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;IA64_FETCHADD(_tmp, _v, -16, sizeof(*(v)), sem);&t;&t;&t;&bslash;&n;&t;else if ((i) == -8)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;IA64_FETCHADD(_tmp, _v, -8, sizeof(*(v)), sem);&t;&t;&t;&t;&bslash;&n;&t;else if ((i) == -4)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;IA64_FETCHADD(_tmp, _v, -4, sizeof(*(v)), sem);&t;&t;&t;&t;&bslash;&n;&t;else if ((i) == -1)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;IA64_FETCHADD(_tmp, _v, -1, sizeof(*(v)), sem);&t;&t;&t;&t;&bslash;&n;&t;else if ((i) == 1)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;IA64_FETCHADD(_tmp, _v, 1, sizeof(*(v)), sem);&t;&t;&t;&t;&bslash;&n;&t;else if ((i) == 4)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;IA64_FETCHADD(_tmp, _v, 4, sizeof(*(v)), sem);&t;&t;&t;&t;&bslash;&n;&t;else if ((i) == 8)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;IA64_FETCHADD(_tmp, _v, 8, sizeof(*(v)), sem);&t;&t;&t;&t;&bslash;&n;&t;else if ((i) == 16)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;IA64_FETCHADD(_tmp, _v, 16, sizeof(*(v)), sem);&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_tmp = __bad_increment_for_ia64_fetch_and_add();&t;&t;&t;&bslash;&n;&t;(__typeof__(*(v))) (_tmp);&t;/* return old value */&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_fetch_and_add
mdefine_line|#define ia64_fetch_and_add(i,v)&t;(ia64_fetchadd(i, v, rel) + (i)) /* return new value */
multiline_comment|/*&n; * This function doesn&squot;t exist, so you&squot;ll get a linker error if&n; * something tries to do an invalid xchg().&n; */
r_extern
r_void
id|ia64_xchg_called_with_bad_pointer
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__xchg
mdefine_line|#define __xchg(x,ptr,size)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __xchg_result;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 1:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__xchg_result = ia64_xchg1((__u8 *)ptr, x);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 2:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__xchg_result = ia64_xchg2((__u16 *)ptr, x);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 4:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__xchg_result = ia64_xchg4((__u32 *)ptr, x);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 8:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__xchg_result = ia64_xchg8((__u64 *)ptr, x);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      default:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ia64_xchg_called_with_bad_pointer();&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__xchg_result;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x)&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;  ((__typeof__(*(ptr))) __xchg ((unsigned long) (x), (ptr), sizeof(*(ptr))))
multiline_comment|/*&n; * Atomic compare and exchange.  Compare OLD with MEM, if identical,&n; * store NEW in MEM.  Return the initial value in MEM.  Success is&n; * indicated by comparing RETURN with OLD.&n; */
DECL|macro|__HAVE_ARCH_CMPXCHG
mdefine_line|#define __HAVE_ARCH_CMPXCHG 1
multiline_comment|/*&n; * This function doesn&squot;t exist, so you&squot;ll get a linker error&n; * if something tries to do an invalid cmpxchg().&n; */
r_extern
r_int
id|ia64_cmpxchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|ia64_cmpxchg
mdefine_line|#define ia64_cmpxchg(sem,ptr,old,new,size)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 _o_, _r_;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 1: _o_ = (__u8 ) (long) (old); break;&t;&t;&t;&t;&bslash;&n;&t;      case 2: _o_ = (__u16) (long) (old); break;&t;&t;&t;&t;&bslash;&n;&t;      case 4: _o_ = (__u32) (long) (old); break;&t;&t;&t;&t;&bslash;&n;&t;      case 8: _o_ = (__u64) (long) (old); break;&t;&t;&t;&t;&bslash;&n;&t;      default: break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 1:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      &t;_r_ = ia64_cmpxchg1_##sem((__u8 *) ptr, new, _o_);&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 2:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;       _r_ = ia64_cmpxchg2_##sem((__u16 *) ptr, new, _o_);&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 4:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      &t;_r_ = ia64_cmpxchg4_##sem((__u32 *) ptr, new, _o_);&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 8:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_r_ = ia64_cmpxchg8_##sem((__u64 *) ptr, new, _o_);&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      default:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_r_ = ia64_cmpxchg_called_with_bad_pointer();&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(__typeof__(old)) _r_;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|cmpxchg_acq
mdefine_line|#define cmpxchg_acq(ptr,o,n)&t;ia64_cmpxchg(acq, (ptr), (o), (n), sizeof(*(ptr)))
DECL|macro|cmpxchg_rel
mdefine_line|#define cmpxchg_rel(ptr,o,n)&t;ia64_cmpxchg(rel, (ptr), (o), (n), sizeof(*(ptr)))
multiline_comment|/* for compatibility with other platforms: */
DECL|macro|cmpxchg
mdefine_line|#define cmpxchg(ptr,o,n)&t;cmpxchg_acq(ptr,o,n)
macro_line|#ifdef CONFIG_IA64_DEBUG_CMPXCHG
DECL|macro|CMPXCHG_BUGCHECK_DECL
macro_line|# define CMPXCHG_BUGCHECK_DECL&t;int _cmpxchg_bugcheck_count = 128;
DECL|macro|CMPXCHG_BUGCHECK
macro_line|# define CMPXCHG_BUGCHECK(v)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (_cmpxchg_bugcheck_count-- &lt;= 0) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;void *ip;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;extern int printk(const char *fmt, ...);&t;&t;&t;&bslash;&n;&t;&t;ip = ia64_getreg(_IA64_REG_IP);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;printk(&quot;CMPXCHG_BUGCHECK: stuck at %p on word %p&bslash;n&quot;, ip, (v));&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
macro_line|#else /* !CONFIG_IA64_DEBUG_CMPXCHG */
DECL|macro|CMPXCHG_BUGCHECK_DECL
macro_line|# define CMPXCHG_BUGCHECK_DECL
DECL|macro|CMPXCHG_BUGCHECK
macro_line|# define CMPXCHG_BUGCHECK(v)
macro_line|#endif /* !CONFIG_IA64_DEBUG_CMPXCHG */
macro_line|#endif
macro_line|#endif /* _ASM_IA64_INTRINSICS_H */
eof
