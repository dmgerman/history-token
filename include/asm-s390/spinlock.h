multiline_comment|/*&n; *  include/asm-s390/spinlock.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Derived from &quot;include/asm-i386/spinlock.h&quot;&n; */
macro_line|#ifndef __ASM_SPINLOCK_H
DECL|macro|__ASM_SPINLOCK_H
mdefine_line|#define __ASM_SPINLOCK_H
macro_line|#ifdef __s390x__
multiline_comment|/*&n; * Grmph, take care of %&amp;#! user space programs that include&n; * asm/spinlock.h. The diagnose is only available in kernel&n; * context.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/lowcore.h&gt;
DECL|macro|__DIAG44_INSN
mdefine_line|#define __DIAG44_INSN &quot;ex&quot;
DECL|macro|__DIAG44_OPERAND
mdefine_line|#define __DIAG44_OPERAND __LC_DIAG44_OPCODE
macro_line|#else
DECL|macro|__DIAG44_INSN
mdefine_line|#define __DIAG44_INSN &quot;#&quot;
DECL|macro|__DIAG44_OPERAND
mdefine_line|#define __DIAG44_OPERAND 0
macro_line|#endif
macro_line|#endif /* __s390x__ */
multiline_comment|/*&n; * Simple spin lock operations.  There are two variants, one clears IRQ&squot;s&n; * on the local processor, one does not.&n; *&n; * We make no fairness assumptions. They have a cost.&n; */
r_typedef
r_struct
(brace
DECL|member|lock
r_volatile
r_int
r_int
id|lock
suffix:semicolon
macro_line|#ifdef CONFIG_PREEMPT
DECL|member|break_lock
r_int
r_int
id|break_lock
suffix:semicolon
macro_line|#endif
DECL|typedef|spinlock_t
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
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED (spinlock_t) { 0 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(lp) do { (lp)-&gt;lock = 0; } while(0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(lp)&t;do { barrier(); } while(((volatile spinlock_t *)(lp))-&gt;lock)
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(x) ((x)-&gt;lock != 0)
DECL|macro|_raw_spin_lock_flags
mdefine_line|#define _raw_spin_lock_flags(lock, flags) _raw_spin_lock(lock)
DECL|function|_raw_spin_lock
r_extern
r_inline
r_void
id|_raw_spin_lock
c_func
(paren
id|spinlock_t
op_star
id|lp
)paren
(brace
macro_line|#ifndef __s390x__
r_int
r_int
id|reg1
comma
id|reg2
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;    bras  %0,1f&bslash;n&quot;
l_string|&quot;0:  diag  0,0,68&bslash;n&quot;
l_string|&quot;1:  slr   %1,%1&bslash;n&quot;
l_string|&quot;    cs    %1,%0,0(%3)&bslash;n&quot;
l_string|&quot;    jl    0b&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|reg1
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|reg2
)paren
comma
l_string|&quot;=m&quot;
(paren
id|lp-&gt;lock
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|lp-&gt;lock
)paren
comma
l_string|&quot;m&quot;
(paren
id|lp-&gt;lock
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
macro_line|#else /* __s390x__ */
r_int
r_int
id|reg1
comma
id|reg2
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;    bras  %1,1f&bslash;n&quot;
l_string|&quot;0:  &quot;
id|__DIAG44_INSN
l_string|&quot; 0,%4&bslash;n&quot;
l_string|&quot;1:  slr   %0,%0&bslash;n&quot;
l_string|&quot;    cs    %0,%1,0(%3)&bslash;n&quot;
l_string|&quot;    jl    0b&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|reg1
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|reg2
)paren
comma
l_string|&quot;=m&quot;
(paren
id|lp-&gt;lock
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|lp-&gt;lock
)paren
comma
l_string|&quot;i&quot;
(paren
id|__DIAG44_OPERAND
)paren
comma
l_string|&quot;m&quot;
(paren
id|lp-&gt;lock
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
macro_line|#endif /* __s390x__ */
)brace
DECL|function|_raw_spin_trylock
r_extern
r_inline
r_int
id|_raw_spin_trylock
c_func
(paren
id|spinlock_t
op_star
id|lp
)paren
(brace
r_int
r_int
id|reg
suffix:semicolon
r_int
r_int
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;    basr  %1,0&bslash;n&quot;
l_string|&quot;0:  cs    %0,%1,0(%3)&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|result
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|reg
)paren
comma
l_string|&quot;=m&quot;
(paren
id|lp-&gt;lock
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|lp-&gt;lock
)paren
comma
l_string|&quot;m&quot;
(paren
id|lp-&gt;lock
)paren
comma
l_string|&quot;0&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
op_logical_neg
id|result
suffix:semicolon
)brace
DECL|function|_raw_spin_unlock
r_extern
r_inline
r_void
id|_raw_spin_unlock
c_func
(paren
id|spinlock_t
op_star
id|lp
)paren
(brace
r_int
r_int
id|old
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cs %0,%3,0(%4)&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|old
)paren
comma
l_string|&quot;=m&quot;
(paren
id|lp-&gt;lock
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|lp-&gt;lock
)paren
comma
l_string|&quot;d&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;a&quot;
(paren
id|lp
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read-write spinlocks, allowing multiple readers&n; * but only one writer.&n; *&n; * NOTE! it is quite common to have readers in interrupts&n; * but no interrupt writers. For those circumstances we&n; * can &quot;mix&quot; irq-safe locks - any writer needs to get a&n; * irq-safe write-lock, but readers can get non-irqsafe&n; * read-locks.&n; */
r_typedef
r_struct
(brace
DECL|member|lock
r_volatile
r_int
r_int
id|lock
suffix:semicolon
DECL|member|owner_pc
r_volatile
r_int
r_int
id|owner_pc
suffix:semicolon
macro_line|#ifdef CONFIG_PREEMPT
DECL|member|break_lock
r_int
r_int
id|break_lock
suffix:semicolon
macro_line|#endif
DECL|typedef|rwlock_t
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { 0, 0 }
DECL|macro|rwlock_init
mdefine_line|#define rwlock_init(x)&t;do { *(x) = RW_LOCK_UNLOCKED; } while(0)
DECL|macro|rwlock_is_locked
mdefine_line|#define rwlock_is_locked(x) ((x)-&gt;lock != 0)
macro_line|#ifndef __s390x__
DECL|macro|_raw_read_lock
mdefine_line|#define _raw_read_lock(rw)   &bslash;&n;        asm volatile(&quot;   l     2,0(%1)&bslash;n&quot;   &bslash;&n;                     &quot;   j     1f&bslash;n&quot;     &bslash;&n;                     &quot;0: diag  0,0,68&bslash;n&quot; &bslash;&n;                     &quot;1: la    2,0(2)&bslash;n&quot;     /* clear high (=write) bit */ &bslash;&n;                     &quot;   la    3,1(2)&bslash;n&quot;     /* one more reader */ &bslash;&n;                     &quot;   cs    2,3,0(%1)&bslash;n&quot;  /* try to write new value */ &bslash;&n;                     &quot;   jl    0b&quot;       &bslash;&n;                     : &quot;=m&quot; ((rw)-&gt;lock) : &quot;a&quot; (&amp;(rw)-&gt;lock), &bslash;&n;&t;&t;       &quot;m&quot; ((rw)-&gt;lock) : &quot;2&quot;, &quot;3&quot;, &quot;cc&quot;, &quot;memory&quot; )
macro_line|#else /* __s390x__ */
DECL|macro|_raw_read_lock
mdefine_line|#define _raw_read_lock(rw)   &bslash;&n;        asm volatile(&quot;   lg    2,0(%1)&bslash;n&quot;   &bslash;&n;                     &quot;   j     1f&bslash;n&quot;     &bslash;&n;                     &quot;0: &quot; __DIAG44_INSN &quot; 0,%2&bslash;n&quot; &bslash;&n;                     &quot;1: nihh  2,0x7fff&bslash;n&quot; /* clear high (=write) bit */ &bslash;&n;                     &quot;   la    3,1(2)&bslash;n&quot;   /* one more reader */  &bslash;&n;                     &quot;   csg   2,3,0(%1)&bslash;n&quot; /* try to write new value */ &bslash;&n;                     &quot;   jl    0b&quot;       &bslash;&n;                     : &quot;=m&quot; ((rw)-&gt;lock) &bslash;&n;&t;&t;     : &quot;a&quot; (&amp;(rw)-&gt;lock), &quot;i&quot; (__DIAG44_OPERAND), &bslash;&n;&t;&t;       &quot;m&quot; ((rw)-&gt;lock) : &quot;2&quot;, &quot;3&quot;, &quot;cc&quot;, &quot;memory&quot; )
macro_line|#endif /* __s390x__ */
macro_line|#ifndef __s390x__
DECL|macro|_raw_read_unlock
mdefine_line|#define _raw_read_unlock(rw) &bslash;&n;        asm volatile(&quot;   l     2,0(%1)&bslash;n&quot;   &bslash;&n;                     &quot;   j     1f&bslash;n&quot;     &bslash;&n;                     &quot;0: diag  0,0,68&bslash;n&quot; &bslash;&n;                     &quot;1: lr    3,2&bslash;n&quot;    &bslash;&n;                     &quot;   ahi   3,-1&bslash;n&quot;    /* one less reader */ &bslash;&n;                     &quot;   cs    2,3,0(%1)&bslash;n&quot; &bslash;&n;                     &quot;   jl    0b&quot;       &bslash;&n;                     : &quot;=m&quot; ((rw)-&gt;lock) : &quot;a&quot; (&amp;(rw)-&gt;lock), &bslash;&n;&t;&t;       &quot;m&quot; ((rw)-&gt;lock) : &quot;2&quot;, &quot;3&quot;, &quot;cc&quot;, &quot;memory&quot; )
macro_line|#else /* __s390x__ */
DECL|macro|_raw_read_unlock
mdefine_line|#define _raw_read_unlock(rw) &bslash;&n;        asm volatile(&quot;   lg    2,0(%1)&bslash;n&quot;   &bslash;&n;                     &quot;   j     1f&bslash;n&quot;     &bslash;&n;                     &quot;0: &quot; __DIAG44_INSN &quot; 0,%2&bslash;n&quot; &bslash;&n;                     &quot;1: lgr   3,2&bslash;n&quot;    &bslash;&n;                     &quot;   bctgr 3,0&bslash;n&quot;    /* one less reader */ &bslash;&n;                     &quot;   csg   2,3,0(%1)&bslash;n&quot; &bslash;&n;                     &quot;   jl    0b&quot;       &bslash;&n;                     : &quot;=m&quot; ((rw)-&gt;lock) &bslash;&n;&t;&t;     : &quot;a&quot; (&amp;(rw)-&gt;lock), &quot;i&quot; (__DIAG44_OPERAND), &bslash;&n;&t;&t;       &quot;m&quot; ((rw)-&gt;lock) : &quot;2&quot;, &quot;3&quot;, &quot;cc&quot;, &quot;memory&quot; )
macro_line|#endif /* __s390x__ */
macro_line|#ifndef __s390x__
DECL|macro|_raw_write_lock
mdefine_line|#define _raw_write_lock(rw) &bslash;&n;        asm volatile(&quot;   lhi   3,1&bslash;n&quot;    &bslash;&n;                     &quot;   sll   3,31&bslash;n&quot;    /* new lock value = 0x80000000 */ &bslash;&n;                     &quot;   j     1f&bslash;n&quot;     &bslash;&n;                     &quot;0: diag  0,0,68&bslash;n&quot; &bslash;&n;                     &quot;1: slr   2,2&bslash;n&quot;     /* old lock value must be 0 */ &bslash;&n;                     &quot;   cs    2,3,0(%1)&bslash;n&quot; &bslash;&n;                     &quot;   jl    0b&quot;       &bslash;&n;                     : &quot;=m&quot; ((rw)-&gt;lock) : &quot;a&quot; (&amp;(rw)-&gt;lock), &bslash;&n;&t;&t;       &quot;m&quot; ((rw)-&gt;lock) : &quot;2&quot;, &quot;3&quot;, &quot;cc&quot;, &quot;memory&quot; )
macro_line|#else /* __s390x__ */
DECL|macro|_raw_write_lock
mdefine_line|#define _raw_write_lock(rw) &bslash;&n;        asm volatile(&quot;   llihh 3,0x8000&bslash;n&quot; /* new lock value = 0x80...0 */ &bslash;&n;                     &quot;   j     1f&bslash;n&quot;       &bslash;&n;                     &quot;0: &quot; __DIAG44_INSN &quot; 0,%2&bslash;n&quot;   &bslash;&n;                     &quot;1: slgr  2,2&bslash;n&quot;      /* old lock value must be 0 */ &bslash;&n;                     &quot;   csg   2,3,0(%1)&bslash;n&quot; &bslash;&n;                     &quot;   jl    0b&quot;         &bslash;&n;                     : &quot;=m&quot; ((rw)-&gt;lock) &bslash;&n;&t;&t;     : &quot;a&quot; (&amp;(rw)-&gt;lock), &quot;i&quot; (__DIAG44_OPERAND), &bslash;&n;&t;&t;       &quot;m&quot; ((rw)-&gt;lock) : &quot;2&quot;, &quot;3&quot;, &quot;cc&quot;, &quot;memory&quot; )
macro_line|#endif /* __s390x__ */
macro_line|#ifndef __s390x__
DECL|macro|_raw_write_unlock
mdefine_line|#define _raw_write_unlock(rw) &bslash;&n;        asm volatile(&quot;   slr   3,3&bslash;n&quot;     /* new lock value = 0 */ &bslash;&n;                     &quot;   j     1f&bslash;n&quot;     &bslash;&n;                     &quot;0: diag  0,0,68&bslash;n&quot; &bslash;&n;                     &quot;1: lhi   2,1&bslash;n&quot;    &bslash;&n;                     &quot;   sll   2,31&bslash;n&quot;    /* old lock value must be 0x80000000 */ &bslash;&n;                     &quot;   cs    2,3,0(%1)&bslash;n&quot; &bslash;&n;                     &quot;   jl    0b&quot;       &bslash;&n;                     : &quot;=m&quot; ((rw)-&gt;lock) : &quot;a&quot; (&amp;(rw)-&gt;lock), &bslash;&n;&t;&t;       &quot;m&quot; ((rw)-&gt;lock) : &quot;2&quot;, &quot;3&quot;, &quot;cc&quot;, &quot;memory&quot; )
macro_line|#else /* __s390x__ */
DECL|macro|_raw_write_unlock
mdefine_line|#define _raw_write_unlock(rw) &bslash;&n;        asm volatile(&quot;   slgr  3,3&bslash;n&quot;      /* new lock value = 0 */ &bslash;&n;                     &quot;   j     1f&bslash;n&quot;       &bslash;&n;                     &quot;0: &quot; __DIAG44_INSN &quot; 0,%2&bslash;n&quot;   &bslash;&n;                     &quot;1: llihh 2,0x8000&bslash;n&quot; /* old lock value must be 0x8..0 */&bslash;&n;                     &quot;   csg   2,3,0(%1)&bslash;n&quot;   &bslash;&n;                     &quot;   jl    0b&quot;         &bslash;&n;                     : &quot;=m&quot; ((rw)-&gt;lock) &bslash;&n;&t;&t;     : &quot;a&quot; (&amp;(rw)-&gt;lock), &quot;i&quot; (__DIAG44_OPERAND), &bslash;&n;&t;&t;       &quot;m&quot; ((rw)-&gt;lock) : &quot;2&quot;, &quot;3&quot;, &quot;cc&quot;, &quot;memory&quot; )
macro_line|#endif /* __s390x__ */
DECL|macro|_raw_read_trylock
mdefine_line|#define _raw_read_trylock(lock) generic_raw_read_trylock(lock)
DECL|function|_raw_write_trylock
r_extern
r_inline
r_int
id|_raw_write_trylock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_int
r_int
id|result
comma
id|reg
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
macro_line|#ifndef __s390x__
l_string|&quot;   lhi  %1,1&bslash;n&quot;
l_string|&quot;   sll  %1,31&bslash;n&quot;
l_string|&quot;   cs   %0,%1,0(%3)&quot;
macro_line|#else /* __s390x__ */
l_string|&quot;   llihh %1,0x8000&bslash;n&quot;
l_string|&quot;0: csg %0,%1,0(%3)&bslash;n&quot;
macro_line|#endif /* __s390x__ */
suffix:colon
l_string|&quot;=d&quot;
(paren
id|result
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|reg
)paren
comma
l_string|&quot;=m&quot;
(paren
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|rw-&gt;lock
)paren
comma
l_string|&quot;m&quot;
(paren
id|rw-&gt;lock
)paren
comma
l_string|&quot;0&quot;
(paren
l_int|0UL
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
op_eq
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* __ASM_SPINLOCK_H */
eof
