macro_line|#ifndef _ASM_PARISC_ATOMIC_H_
DECL|macro|_ASM_PARISC_ATOMIC_H_
mdefine_line|#define _ASM_PARISC_ATOMIC_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/* Copyright (C) 2000 Philipp Rumpf &lt;prumpf@tux.org&gt;.  */
multiline_comment|/*&n; * Atomic operations that C can&squot;t guarantee us.  Useful for&n; * resource counting etc..&n; *&n; * And probably incredibly slow on parisc.  OTOH, we don&squot;t&n; * have to write any serious assembly.   prumpf&n; */
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;asm/spinlock.h&gt;
macro_line|#include &lt;asm/cache.h&gt;&t;&t;/* we use L1_CACHE_BYTES */
multiline_comment|/* Use an array of spinlocks for our atomic_ts.&n; * Hash function to index into a different SPINLOCK.&n; * Since &quot;a&quot; is usually an address, use one spinlock per cacheline.&n; */
DECL|macro|ATOMIC_HASH_SIZE
macro_line|#  define ATOMIC_HASH_SIZE 4
DECL|macro|ATOMIC_HASH
macro_line|#  define ATOMIC_HASH(a) (&amp;(__atomic_hash[ (((unsigned long) a)/L1_CACHE_BYTES) &amp; (ATOMIC_HASH_SIZE-1) ]))
r_extern
id|spinlock_t
id|__atomic_hash
(braket
id|ATOMIC_HASH_SIZE
)braket
id|__lock_aligned
suffix:semicolon
multiline_comment|/* Can&squot;t use _raw_spin_lock_irq because of #include problems, so&n; * this is the substitute */
DECL|macro|_atomic_spin_lock_irqsave
mdefine_line|#define _atomic_spin_lock_irqsave(l,f) do {&t;&bslash;&n;&t;spinlock_t *s = ATOMIC_HASH(l);&t;&t;&bslash;&n;&t;local_irq_save(f);&t;&t;&t;&bslash;&n;&t;_raw_spin_lock(s);&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|_atomic_spin_unlock_irqrestore
mdefine_line|#define _atomic_spin_unlock_irqrestore(l,f) do {&t;&bslash;&n;&t;spinlock_t *s = ATOMIC_HASH(l);&t;&t;&t;&bslash;&n;&t;_raw_spin_unlock(s);&t;&t;&t;&t;&bslash;&n;&t;local_irq_restore(f);&t;&t;&t;&t;&bslash;&n;} while(0)
macro_line|#else
DECL|macro|_atomic_spin_lock_irqsave
macro_line|#  define _atomic_spin_lock_irqsave(l,f) do { local_irq_save(f); } while (0)
DECL|macro|_atomic_spin_unlock_irqrestore
macro_line|#  define _atomic_spin_unlock_irqrestore(l,f) do { local_irq_restore(f); } while (0)
macro_line|#endif
multiline_comment|/* Note that we need not lock read accesses - aligned word writes/reads&n; * are atomic, so a reader never sees unconsistent values.&n; *&n; * Cache-line alignment would conflict with, for example, linux/module.h&n; */
DECL|member|counter
DECL|typedef|atomic_t
r_typedef
r_struct
(brace
r_volatile
r_int
id|counter
suffix:semicolon
)brace
id|atomic_t
suffix:semicolon
multiline_comment|/* This should get optimized out since it&squot;s never called.&n;** Or get a link error if xchg is used &quot;wrong&quot;.&n;*/
r_extern
r_void
id|__xchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* __xchg32/64 defined in arch/parisc/lib/bitops.c */
r_extern
r_int
r_int
id|__xchg8
c_func
(paren
r_char
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__xchg32
c_func
(paren
r_int
comma
r_int
op_star
)paren
suffix:semicolon
macro_line|#ifdef __LP64__
r_extern
r_int
r_int
id|__xchg64
c_func
(paren
r_int
r_int
comma
r_int
r_int
op_star
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* optimizer better get rid of switch since size is a constant */
DECL|function|__xchg
r_static
id|__inline__
r_int
r_int
id|__xchg
c_func
(paren
r_int
r_int
id|x
comma
id|__volatile__
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_switch
c_cond
(paren
id|size
)paren
(brace
macro_line|#ifdef __LP64__
r_case
l_int|8
suffix:colon
r_return
id|__xchg64
c_func
(paren
id|x
comma
(paren
r_int
r_int
op_star
)paren
id|ptr
)paren
suffix:semicolon
macro_line|#endif
r_case
l_int|4
suffix:colon
r_return
id|__xchg32
c_func
(paren
(paren
r_int
)paren
id|x
comma
(paren
r_int
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
id|__xchg8
c_func
(paren
(paren
r_char
)paren
id|x
comma
(paren
r_char
op_star
)paren
id|ptr
)paren
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
multiline_comment|/*&n;** REVISIT - Abandoned use of LDCW in xchg() for now:&n;** o need to test sizeof(*ptr) to avoid clearing adjacent bytes&n;** o and while we are at it, could __LP64__ code use LDCD too?&n;**&n;**&t;if (__builtin_constant_p(x) &amp;&amp; (x == NULL))&n;**&t;&t;if (((unsigned long)p &amp; 0xf) == 0)&n;**&t;&t;&t;return __ldcw(p);&n;*/
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) &bslash;&n;&t;((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
DECL|macro|__HAVE_ARCH_CMPXCHG
mdefine_line|#define __HAVE_ARCH_CMPXCHG&t;1
multiline_comment|/* bug catcher for when unsupported size is used - won&squot;t link */
r_extern
r_void
id|__cmpxchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* __cmpxchg_u32/u64 defined in arch/parisc/lib/bitops.c */
r_extern
r_int
r_int
id|__cmpxchg_u32
c_func
(paren
r_volatile
r_int
r_int
op_star
id|m
comma
r_int
r_int
id|old
comma
r_int
r_int
id|new_
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__cmpxchg_u64
c_func
(paren
r_volatile
r_int
r_int
op_star
id|ptr
comma
r_int
r_int
id|old
comma
r_int
r_int
id|new_
)paren
suffix:semicolon
multiline_comment|/* don&squot;t worry...optimizer will get rid of most of this */
r_static
id|__inline__
r_int
r_int
DECL|function|__cmpxchg
id|__cmpxchg
c_func
(paren
r_volatile
r_void
op_star
id|ptr
comma
r_int
r_int
id|old
comma
r_int
r_int
id|new_
comma
r_int
id|size
)paren
(brace
r_switch
c_cond
(paren
id|size
)paren
(brace
macro_line|#ifdef __LP64__
r_case
l_int|8
suffix:colon
r_return
id|__cmpxchg_u64
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|ptr
comma
id|old
comma
id|new_
)paren
suffix:semicolon
macro_line|#endif
r_case
l_int|4
suffix:colon
r_return
id|__cmpxchg_u32
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|ptr
comma
(paren
r_int
r_int
)paren
id|old
comma
(paren
r_int
r_int
)paren
id|new_
)paren
suffix:semicolon
)brace
id|__cmpxchg_called_with_bad_pointer
c_func
(paren
)paren
suffix:semicolon
r_return
id|old
suffix:semicolon
)brace
DECL|macro|cmpxchg
mdefine_line|#define cmpxchg(ptr,o,n)&t;&t;&t;&t;&t;&t; &bslash;&n;  ({&t;&t;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;     __typeof__(*(ptr)) _o_ = (o);&t;&t;&t;&t;&t; &bslash;&n;     __typeof__(*(ptr)) _n_ = (n);&t;&t;&t;&t;&t; &bslash;&n;     (__typeof__(*(ptr))) __cmpxchg((ptr), (unsigned long)_o_,&t;&t; &bslash;&n;&t;&t;&t;&t;    (unsigned long)_n_, sizeof(*(ptr))); &bslash;&n;  })
multiline_comment|/* It&squot;s possible to reduce all atomic operations to either&n; * __atomic_add_return, atomic_set and atomic_read (the latter&n; * is there only for consistency).&n; */
DECL|function|__atomic_add_return
r_static
id|__inline__
r_int
id|__atomic_add_return
c_func
(paren
r_int
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_int
id|ret
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|_atomic_spin_lock_irqsave
c_func
(paren
id|v
comma
id|flags
)paren
suffix:semicolon
id|ret
op_assign
(paren
id|v-&gt;counter
op_add_assign
id|i
)paren
suffix:semicolon
id|_atomic_spin_unlock_irqrestore
c_func
(paren
id|v
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|atomic_set
r_static
id|__inline__
r_void
id|atomic_set
c_func
(paren
id|atomic_t
op_star
id|v
comma
r_int
id|i
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|_atomic_spin_lock_irqsave
c_func
(paren
id|v
comma
id|flags
)paren
suffix:semicolon
id|v-&gt;counter
op_assign
id|i
suffix:semicolon
id|_atomic_spin_unlock_irqrestore
c_func
(paren
id|v
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|atomic_read
r_static
id|__inline__
r_int
id|atomic_read
c_func
(paren
r_const
id|atomic_t
op_star
id|v
)paren
(brace
r_return
id|v-&gt;counter
suffix:semicolon
)brace
multiline_comment|/* exported interface */
DECL|macro|atomic_add
mdefine_line|#define atomic_add(i,v)&t;((void)(__atomic_add_return( ((int)i),(v))))
DECL|macro|atomic_sub
mdefine_line|#define atomic_sub(i,v)&t;((void)(__atomic_add_return(-((int)i),(v))))
DECL|macro|atomic_inc
mdefine_line|#define atomic_inc(v)&t;((void)(__atomic_add_return(   1,(v))))
DECL|macro|atomic_dec
mdefine_line|#define atomic_dec(v)&t;((void)(__atomic_add_return(  -1,(v))))
DECL|macro|atomic_add_return
mdefine_line|#define atomic_add_return(i,v)&t;(__atomic_add_return( ((int)i),(v)))
DECL|macro|atomic_sub_return
mdefine_line|#define atomic_sub_return(i,v)&t;(__atomic_add_return(-((int)i),(v)))
DECL|macro|atomic_inc_return
mdefine_line|#define atomic_inc_return(v)&t;(__atomic_add_return(   1,(v)))
DECL|macro|atomic_dec_return
mdefine_line|#define atomic_dec_return(v)&t;(__atomic_add_return(  -1,(v)))
DECL|macro|atomic_add_negative
mdefine_line|#define atomic_add_negative(a, v)&t;(atomic_add_return((a), (v)) &lt; 0)
multiline_comment|/*&n; * atomic_inc_and_test - increment and test&n; * @v: pointer of type atomic_t&n; *&n; * Atomically increments @v by 1&n; * and returns true if the result is zero, or false for all&n; * other cases.&n; */
DECL|macro|atomic_inc_and_test
mdefine_line|#define atomic_inc_and_test(v) (atomic_inc_return(v) == 0)
DECL|macro|atomic_dec_and_test
mdefine_line|#define atomic_dec_and_test(v)&t;(atomic_dec_return(v) == 0)
DECL|macro|ATOMIC_INIT
mdefine_line|#define ATOMIC_INIT(i)&t;{ (i) }
DECL|macro|smp_mb__before_atomic_dec
mdefine_line|#define smp_mb__before_atomic_dec()&t;smp_mb()
DECL|macro|smp_mb__after_atomic_dec
mdefine_line|#define smp_mb__after_atomic_dec()&t;smp_mb()
DECL|macro|smp_mb__before_atomic_inc
mdefine_line|#define smp_mb__before_atomic_inc()&t;smp_mb()
DECL|macro|smp_mb__after_atomic_inc
mdefine_line|#define smp_mb__after_atomic_inc()&t;smp_mb()
macro_line|#endif
eof
