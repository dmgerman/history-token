macro_line|#ifndef _ASM_IA64_INTRINSICS_H
DECL|macro|_ASM_IA64_INTRINSICS_H
mdefine_line|#define _ASM_IA64_INTRINSICS_H
multiline_comment|/*&n; * Compiler-dependent intrinsics.&n; *&n; * Copyright (C) 2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;kernel/config.h&gt;
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
mdefine_line|#define IA64_FETCHADD(tmp,v,n,sz)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (sz) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 4:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__ (&quot;fetchadd4.rel %0=[%1],%2&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;      : &quot;=r&quot;(tmp) : &quot;r&quot;(v), &quot;i&quot;(n) : &quot;memory&quot;);&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 8:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__ (&quot;fetchadd8.rel %0=[%1],%2&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;      : &quot;=r&quot;(tmp) : &quot;r&quot;(v), &quot;i&quot;(n) : &quot;memory&quot;);&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      default:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__bad_size_for_ia64_fetch_and_add();&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_fetch_and_add
mdefine_line|#define ia64_fetch_and_add(i,v)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 _tmp;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;volatile __typeof__(*(v)) *_v = (v);&t;&t;&t;&t;&t;&bslash;&n;&t;switch (i) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case -16:&t;IA64_FETCHADD(_tmp, _v, -16, sizeof(*(v))); break;&t;&bslash;&n;&t;      case  -8:&t;IA64_FETCHADD(_tmp, _v,  -8, sizeof(*(v))); break;&t;&bslash;&n;&t;      case  -4:&t;IA64_FETCHADD(_tmp, _v,  -4, sizeof(*(v))); break;&t;&bslash;&n;&t;      case  -1:&t;IA64_FETCHADD(_tmp, _v,  -1, sizeof(*(v))); break;&t;&bslash;&n;&t;      case   1:&t;IA64_FETCHADD(_tmp, _v,   1, sizeof(*(v))); break;&t;&bslash;&n;&t;      case   4:&t;IA64_FETCHADD(_tmp, _v,   4, sizeof(*(v))); break;&t;&bslash;&n;&t;      case   8:&t;IA64_FETCHADD(_tmp, _v,   8, sizeof(*(v))); break;&t;&bslash;&n;&t;      case  16:&t;IA64_FETCHADD(_tmp, _v,  16, sizeof(*(v))); break;&t;&bslash;&n;&t;      default:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_tmp = __bad_increment_for_ia64_fetch_and_add();&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(__typeof__(*(v))) (_tmp + (i));&t;/* return new value */&t;&t;&bslash;&n;})
multiline_comment|/*&n; * This function doesn&squot;t exist, so you&squot;ll get a linker error if&n; * something tries to do an invalid xchg().&n; */
r_extern
r_void
id|__xchg_called_with_bad_pointer
(paren
r_void
)paren
suffix:semicolon
r_static
id|__inline__
r_int
r_int
DECL|function|__xchg
id|__xchg
(paren
r_int
r_int
id|x
comma
r_volatile
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|result
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|__asm__
id|__volatile
(paren
l_string|&quot;xchg1 %0=[%1],%2&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm__
id|__volatile
(paren
l_string|&quot;xchg2 %0=[%1],%2&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__asm__
id|__volatile
(paren
l_string|&quot;xchg4 %0=[%1],%2&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
r_case
l_int|8
suffix:colon
id|__asm__
id|__volatile
(paren
l_string|&quot;xchg8 %0=[%1],%2&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|__xchg_called_with_bad_pointer
c_func
(paren
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x)&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;  ((__typeof__(*(ptr))) __xchg ((unsigned long) (x), (ptr), sizeof(*(ptr))))
multiline_comment|/*&n; * Atomic compare and exchange.  Compare OLD with MEM, if identical,&n; * store NEW in MEM.  Return the initial value in MEM.  Success is&n; * indicated by comparing RETURN with OLD.&n; */
DECL|macro|__HAVE_ARCH_CMPXCHG
mdefine_line|#define __HAVE_ARCH_CMPXCHG 1
multiline_comment|/*&n; * This function doesn&squot;t exist, so you&squot;ll get a linker error&n; * if something tries to do an invalid cmpxchg().&n; */
r_extern
r_int
id|__cmpxchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|ia64_cmpxchg
mdefine_line|#define ia64_cmpxchg(sem,ptr,old,new,size)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof__(ptr) _p_ = (ptr);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof__(new) _n_ = (new);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 _o_, _r_;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 1: _o_ = (__u8 ) (long) (old); break;&t;&t;&t;&t;&bslash;&n;&t;      case 2: _o_ = (__u16) (long) (old); break;&t;&t;&t;&t;&bslash;&n;&t;      case 4: _o_ = (__u32) (long) (old); break;&t;&t;&t;&t;&bslash;&n;&t;      case 8: _o_ = (__u64) (long) (old); break;&t;&t;&t;&t;&bslash;&n;&t;      default: break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; __asm__ __volatile__ (&quot;mov ar.ccv=%0;;&quot; :: &quot;rO&quot;(_o_));&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 1:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__ (&quot;cmpxchg1.&quot;sem&quot; %0=[%1],%2,ar.ccv&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;      : &quot;=r&quot;(_r_) : &quot;r&quot;(_p_), &quot;r&quot;(_n_) : &quot;memory&quot;);&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 2:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__ (&quot;cmpxchg2.&quot;sem&quot; %0=[%1],%2,ar.ccv&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;      : &quot;=r&quot;(_r_) : &quot;r&quot;(_p_), &quot;r&quot;(_n_) : &quot;memory&quot;);&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 4:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__ (&quot;cmpxchg4.&quot;sem&quot; %0=[%1],%2,ar.ccv&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;      : &quot;=r&quot;(_r_) : &quot;r&quot;(_p_), &quot;r&quot;(_n_) : &quot;memory&quot;);&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      case 8:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__ (&quot;cmpxchg8.&quot;sem&quot; %0=[%1],%2,ar.ccv&quot;&t;&t;&bslash;&n;&t;&t;&t;&t;      : &quot;=r&quot;(_r_) : &quot;r&quot;(_p_), &quot;r&quot;(_n_) : &quot;memory&quot;);&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      default:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_r_ = __cmpxchg_called_with_bad_pointer();&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(__typeof__(old)) _r_;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|cmpxchg_acq
mdefine_line|#define cmpxchg_acq(ptr,o,n)&t;ia64_cmpxchg(&quot;acq&quot;, (ptr), (o), (n), sizeof(*(ptr)))
DECL|macro|cmpxchg_rel
mdefine_line|#define cmpxchg_rel(ptr,o,n)&t;ia64_cmpxchg(&quot;rel&quot;, (ptr), (o), (n), sizeof(*(ptr)))
multiline_comment|/* for compatibility with other platforms: */
DECL|macro|cmpxchg
mdefine_line|#define cmpxchg(ptr,o,n)&t;cmpxchg_acq(ptr,o,n)
macro_line|#ifdef CONFIG_IA64_DEBUG_CMPXCHG
DECL|macro|CMPXCHG_BUGCHECK_DECL
macro_line|# define CMPXCHG_BUGCHECK_DECL&t;int _cmpxchg_bugcheck_count = 128;
DECL|macro|CMPXCHG_BUGCHECK
macro_line|# define CMPXCHG_BUGCHECK(v)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (_cmpxchg_bugcheck_count-- &lt;= 0) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;void *ip;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;extern int printk(const char *fmt, ...);&t;&t;&t;&bslash;&n;&t;&t;asm (&quot;mov %0=ip&quot; : &quot;=r&quot;(ip));&t;&t;&t;&t;&t;&bslash;&n;&t;&t;printk(&quot;CMPXCHG_BUGCHECK: stuck at %p on word %p&bslash;n&quot;, ip, (v));&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
macro_line|#else /* !CONFIG_IA64_DEBUG_CMPXCHG */
DECL|macro|CMPXCHG_BUGCHECK_DECL
macro_line|# define CMPXCHG_BUGCHECK_DECL
DECL|macro|CMPXCHG_BUGCHECK
macro_line|# define CMPXCHG_BUGCHECK(v)
macro_line|#endif /* !CONFIG_IA64_DEBUG_CMPXCHG */
macro_line|#endif /* _ASM_IA64_INTRINSICS_H */
eof
