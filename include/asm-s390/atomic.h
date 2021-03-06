macro_line|#ifndef __ARCH_S390_ATOMIC__
DECL|macro|__ARCH_S390_ATOMIC__
mdefine_line|#define __ARCH_S390_ATOMIC__
multiline_comment|/*&n; *  include/asm-s390/atomic.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999-2003 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *               Denis Joseph Barrow,&n; *&t;&t; Arnd Bergmann (arndb@de.ibm.com)&n; *&n; *  Derived from &quot;include/asm-i386/bitops.h&quot;&n; *    Copyright (C) 1992, Linus Torvalds&n; *&n; */
multiline_comment|/*&n; * Atomic operations that C can&squot;t guarantee us.  Useful for&n; * resource counting etc..&n; * S390 uses &squot;Compare And Swap&squot; for atomicity in SMP enviroment&n; */
r_typedef
r_struct
(brace
DECL|member|counter
r_volatile
r_int
id|counter
suffix:semicolon
DECL|typedef|atomic_t
)brace
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|4
)paren
)paren
)paren
id|atomic_t
suffix:semicolon
DECL|macro|ATOMIC_INIT
mdefine_line|#define ATOMIC_INIT(i)  { (i) }
macro_line|#ifdef __KERNEL__
DECL|macro|__CS_LOOP
mdefine_line|#define __CS_LOOP(ptr, op_val, op_string) ({&t;&t;&t;&t;&bslash;&n;&t;typeof(ptr-&gt;counter) old_val, new_val;&t;&t;&t;&t;&bslash;&n;        __asm__ __volatile__(&quot;   l     %0,0(%3)&bslash;n&quot;&t;&t;&t;&bslash;&n;                             &quot;0: lr    %1,%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;                             op_string &quot;  %1,%4&bslash;n&quot;&t;&t;&t;&bslash;&n;                             &quot;   cs    %0,%1,0(%3)&bslash;n&quot;&t;&t;&t;&bslash;&n;                             &quot;   jl    0b&quot;&t;&t;&t;&t;&bslash;&n;                             : &quot;=&amp;d&quot; (old_val), &quot;=&amp;d&quot; (new_val),&t;&bslash;&n;&t;&t;&t;       &quot;=m&quot; (((atomic_t *)(ptr))-&gt;counter)&t;&bslash;&n;&t;&t;&t;     : &quot;a&quot; (ptr), &quot;d&quot; (op_val),&t;&t;&t;&bslash;&n;&t;&t;&t;       &quot;m&quot; (((atomic_t *)(ptr))-&gt;counter)&t;&bslash;&n;&t;&t;&t;     : &quot;cc&quot;, &quot;memory&quot; );&t;&t;&t;&bslash;&n;&t;new_val;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)          ((v)-&gt;counter)
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v,i)         (((v)-&gt;counter) = (i))
DECL|function|atomic_add
r_static
id|__inline__
r_void
id|atomic_add
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
id|__CS_LOOP
c_func
(paren
id|v
comma
id|i
comma
l_string|&quot;ar&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic_add_return
r_static
id|__inline__
r_int
id|atomic_add_return
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
r_return
id|__CS_LOOP
c_func
(paren
id|v
comma
id|i
comma
l_string|&quot;ar&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic_add_negative
r_static
id|__inline__
r_int
id|atomic_add_negative
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
r_return
id|__CS_LOOP
c_func
(paren
id|v
comma
id|i
comma
l_string|&quot;ar&quot;
)paren
OL
l_int|0
suffix:semicolon
)brace
DECL|function|atomic_sub
r_static
id|__inline__
r_void
id|atomic_sub
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
id|__CS_LOOP
c_func
(paren
id|v
comma
id|i
comma
l_string|&quot;sr&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic_sub_return
r_static
id|__inline__
r_int
id|atomic_sub_return
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
r_return
id|__CS_LOOP
c_func
(paren
id|v
comma
id|i
comma
l_string|&quot;sr&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic_inc
r_static
id|__inline__
r_void
id|atomic_inc
c_func
(paren
r_volatile
id|atomic_t
op_star
id|v
)paren
(brace
id|__CS_LOOP
c_func
(paren
id|v
comma
l_int|1
comma
l_string|&quot;ar&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic_inc_return
r_static
id|__inline__
r_int
id|atomic_inc_return
c_func
(paren
r_volatile
id|atomic_t
op_star
id|v
)paren
(brace
r_return
id|__CS_LOOP
c_func
(paren
id|v
comma
l_int|1
comma
l_string|&quot;ar&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic_inc_and_test
r_static
id|__inline__
r_int
id|atomic_inc_and_test
c_func
(paren
r_volatile
id|atomic_t
op_star
id|v
)paren
(brace
r_return
id|__CS_LOOP
c_func
(paren
id|v
comma
l_int|1
comma
l_string|&quot;ar&quot;
)paren
op_eq
l_int|0
suffix:semicolon
)brace
DECL|function|atomic_dec
r_static
id|__inline__
r_void
id|atomic_dec
c_func
(paren
r_volatile
id|atomic_t
op_star
id|v
)paren
(brace
id|__CS_LOOP
c_func
(paren
id|v
comma
l_int|1
comma
l_string|&quot;sr&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic_dec_return
r_static
id|__inline__
r_int
id|atomic_dec_return
c_func
(paren
r_volatile
id|atomic_t
op_star
id|v
)paren
(brace
r_return
id|__CS_LOOP
c_func
(paren
id|v
comma
l_int|1
comma
l_string|&quot;sr&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic_dec_and_test
r_static
id|__inline__
r_int
id|atomic_dec_and_test
c_func
(paren
r_volatile
id|atomic_t
op_star
id|v
)paren
(brace
r_return
id|__CS_LOOP
c_func
(paren
id|v
comma
l_int|1
comma
l_string|&quot;sr&quot;
)paren
op_eq
l_int|0
suffix:semicolon
)brace
DECL|function|atomic_clear_mask
r_static
id|__inline__
r_void
id|atomic_clear_mask
c_func
(paren
r_int
r_int
id|mask
comma
id|atomic_t
op_star
id|v
)paren
(brace
id|__CS_LOOP
c_func
(paren
id|v
comma
op_complement
id|mask
comma
l_string|&quot;nr&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic_set_mask
r_static
id|__inline__
r_void
id|atomic_set_mask
c_func
(paren
r_int
r_int
id|mask
comma
id|atomic_t
op_star
id|v
)paren
(brace
id|__CS_LOOP
c_func
(paren
id|v
comma
id|mask
comma
l_string|&quot;or&quot;
)paren
suffix:semicolon
)brace
DECL|macro|__CS_LOOP
macro_line|#undef __CS_LOOP
macro_line|#ifdef __s390x__
r_typedef
r_struct
(brace
DECL|member|counter
r_volatile
r_int
r_int
id|counter
suffix:semicolon
DECL|typedef|atomic64_t
)brace
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|8
)paren
)paren
)paren
id|atomic64_t
suffix:semicolon
DECL|macro|ATOMIC64_INIT
mdefine_line|#define ATOMIC64_INIT(i)  { (i) }
DECL|macro|__CSG_LOOP
mdefine_line|#define __CSG_LOOP(ptr, op_val, op_string) ({&t;&t;&t;&t;&bslash;&n;&t;typeof(ptr-&gt;counter) old_val, new_val;&t;&t;&t;&t;&bslash;&n;        __asm__ __volatile__(&quot;   lg    %0,0(%3)&bslash;n&quot;&t;&t;&t;&bslash;&n;                             &quot;0: lgr   %1,%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;                             op_string &quot;  %1,%4&bslash;n&quot;&t;&t;&t;&bslash;&n;                             &quot;   csg   %0,%1,0(%3)&bslash;n&quot;&t;&t;&t;&bslash;&n;                             &quot;   jl    0b&quot;&t;&t;&t;&t;&bslash;&n;                             : &quot;=&amp;d&quot; (old_val), &quot;=&amp;d&quot; (new_val),&t;&bslash;&n;&t;&t;&t;       &quot;=m&quot; (((atomic_t *)(ptr))-&gt;counter)&t;&bslash;&n;&t;&t;&t;     : &quot;a&quot; (ptr), &quot;d&quot; (op_val),&t;&t;&t;&bslash;&n;&t;&t;&t;       &quot;m&quot; (((atomic_t *)(ptr))-&gt;counter)&t;&bslash;&n;&t;&t;&t;     : &quot;cc&quot;, &quot;memory&quot; );&t;&t;&t;&bslash;&n;&t;new_val;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|atomic64_read
mdefine_line|#define atomic64_read(v)          ((v)-&gt;counter)
DECL|macro|atomic64_set
mdefine_line|#define atomic64_set(v,i)         (((v)-&gt;counter) = (i))
DECL|function|atomic64_add
r_static
id|__inline__
r_void
id|atomic64_add
c_func
(paren
r_int
id|i
comma
id|atomic64_t
op_star
id|v
)paren
(brace
id|__CSG_LOOP
c_func
(paren
id|v
comma
id|i
comma
l_string|&quot;agr&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic64_add_return
r_static
id|__inline__
r_int
r_int
id|atomic64_add_return
c_func
(paren
r_int
id|i
comma
id|atomic64_t
op_star
id|v
)paren
(brace
r_return
id|__CSG_LOOP
c_func
(paren
id|v
comma
id|i
comma
l_string|&quot;agr&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic64_add_negative
r_static
id|__inline__
r_int
r_int
id|atomic64_add_negative
c_func
(paren
r_int
id|i
comma
id|atomic64_t
op_star
id|v
)paren
(brace
r_return
id|__CSG_LOOP
c_func
(paren
id|v
comma
id|i
comma
l_string|&quot;agr&quot;
)paren
OL
l_int|0
suffix:semicolon
)brace
DECL|function|atomic64_sub
r_static
id|__inline__
r_void
id|atomic64_sub
c_func
(paren
r_int
id|i
comma
id|atomic64_t
op_star
id|v
)paren
(brace
id|__CSG_LOOP
c_func
(paren
id|v
comma
id|i
comma
l_string|&quot;sgr&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic64_inc
r_static
id|__inline__
r_void
id|atomic64_inc
c_func
(paren
r_volatile
id|atomic64_t
op_star
id|v
)paren
(brace
id|__CSG_LOOP
c_func
(paren
id|v
comma
l_int|1
comma
l_string|&quot;agr&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic64_inc_return
r_static
id|__inline__
r_int
r_int
id|atomic64_inc_return
c_func
(paren
r_volatile
id|atomic64_t
op_star
id|v
)paren
(brace
r_return
id|__CSG_LOOP
c_func
(paren
id|v
comma
l_int|1
comma
l_string|&quot;agr&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic64_inc_and_test
r_static
id|__inline__
r_int
r_int
id|atomic64_inc_and_test
c_func
(paren
r_volatile
id|atomic64_t
op_star
id|v
)paren
(brace
r_return
id|__CSG_LOOP
c_func
(paren
id|v
comma
l_int|1
comma
l_string|&quot;agr&quot;
)paren
op_eq
l_int|0
suffix:semicolon
)brace
DECL|function|atomic64_dec
r_static
id|__inline__
r_void
id|atomic64_dec
c_func
(paren
r_volatile
id|atomic64_t
op_star
id|v
)paren
(brace
id|__CSG_LOOP
c_func
(paren
id|v
comma
l_int|1
comma
l_string|&quot;sgr&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic64_dec_return
r_static
id|__inline__
r_int
r_int
id|atomic64_dec_return
c_func
(paren
r_volatile
id|atomic64_t
op_star
id|v
)paren
(brace
r_return
id|__CSG_LOOP
c_func
(paren
id|v
comma
l_int|1
comma
l_string|&quot;sgr&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic64_dec_and_test
r_static
id|__inline__
r_int
r_int
id|atomic64_dec_and_test
c_func
(paren
r_volatile
id|atomic64_t
op_star
id|v
)paren
(brace
r_return
id|__CSG_LOOP
c_func
(paren
id|v
comma
l_int|1
comma
l_string|&quot;sgr&quot;
)paren
op_eq
l_int|0
suffix:semicolon
)brace
DECL|function|atomic64_clear_mask
r_static
id|__inline__
r_void
id|atomic64_clear_mask
c_func
(paren
r_int
r_int
id|mask
comma
id|atomic64_t
op_star
id|v
)paren
(brace
id|__CSG_LOOP
c_func
(paren
id|v
comma
op_complement
id|mask
comma
l_string|&quot;ngr&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic64_set_mask
r_static
id|__inline__
r_void
id|atomic64_set_mask
c_func
(paren
r_int
r_int
id|mask
comma
id|atomic64_t
op_star
id|v
)paren
(brace
id|__CSG_LOOP
c_func
(paren
id|v
comma
id|mask
comma
l_string|&quot;ogr&quot;
)paren
suffix:semicolon
)brace
DECL|macro|__CSG_LOOP
macro_line|#undef __CSG_LOOP
macro_line|#endif
multiline_comment|/*&n;  returns 0  if expected_oldval==value in *v ( swap was successful )&n;  returns 1  if unsuccessful.&n;&n;  This is non-portable, use bitops or spinlocks instead!&n;*/
r_static
id|__inline__
r_int
DECL|function|atomic_compare_and_swap
id|atomic_compare_and_swap
c_func
(paren
r_int
id|expected_oldval
comma
r_int
id|new_val
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;  lr   %0,%3&bslash;n&quot;
l_string|&quot;  cs   %0,%4,0(%2)&bslash;n&quot;
l_string|&quot;  ipm  %0&bslash;n&quot;
l_string|&quot;  srl  %0,28&bslash;n&quot;
l_string|&quot;0:&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|v
)paren
comma
l_string|&quot;d&quot;
(paren
id|expected_oldval
)paren
comma
l_string|&quot;d&quot;
(paren
id|new_val
)paren
comma
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|macro|smp_mb__before_atomic_dec
mdefine_line|#define smp_mb__before_atomic_dec()&t;smp_mb()
DECL|macro|smp_mb__after_atomic_dec
mdefine_line|#define smp_mb__after_atomic_dec()&t;smp_mb()
DECL|macro|smp_mb__before_atomic_inc
mdefine_line|#define smp_mb__before_atomic_inc()&t;smp_mb()
DECL|macro|smp_mb__after_atomic_inc
mdefine_line|#define smp_mb__after_atomic_inc()&t;smp_mb()
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ARCH_S390_ATOMIC__  */
eof
