multiline_comment|/*&n; *  include/asm-s390/spinlock.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Derived from &quot;include/asm-i386/spinlock.h&quot;&n; */
macro_line|#ifndef __ASM_SPINLOCK_H
DECL|macro|__ASM_SPINLOCK_H
mdefine_line|#define __ASM_SPINLOCK_H
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
DECL|typedef|spinlock_t
)brace
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
r_int
r_int
id|reg1
comma
id|reg2
suffix:semicolon
id|__asm__
id|__volatile
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
l_string|&quot;+m&quot;
(paren
id|lp-&gt;lock
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|lp-&gt;lock
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
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
id|result
comma
id|reg
suffix:semicolon
id|__asm__
id|__volatile
c_func
(paren
l_string|&quot;    slr   %0,%0&bslash;n&quot;
l_string|&quot;    basr  %1,0&bslash;n&quot;
l_string|&quot;0:  cs    %0,%1,0(%3)&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|result
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|reg
)paren
comma
l_string|&quot;+m&quot;
(paren
id|lp-&gt;lock
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|lp-&gt;lock
)paren
suffix:colon
l_string|&quot;cc&quot;
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
id|__asm__
id|__volatile
c_func
(paren
l_string|&quot;    xc 0(4,%1),0(%1)&bslash;n&quot;
l_string|&quot;    bcr 15,0&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
id|lp-&gt;lock
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|lp-&gt;lock
)paren
suffix:colon
l_string|&quot;cc&quot;
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
DECL|macro|_raw_read_lock
mdefine_line|#define _raw_read_lock(rw)   &bslash;&n;        asm volatile(&quot;   l     2,0(%1)&bslash;n&quot;   &bslash;&n;                     &quot;   j     1f&bslash;n&quot;     &bslash;&n;                     &quot;0: diag  0,0,68&bslash;n&quot; &bslash;&n;                     &quot;1: la    2,0(2)&bslash;n&quot;     /* clear high (=write) bit */ &bslash;&n;                     &quot;   la    3,1(2)&bslash;n&quot;     /* one more reader */ &bslash;&n;                     &quot;   cs    2,3,0(%1)&bslash;n&quot;  /* try to write new value */ &bslash;&n;                     &quot;   jl    0b&quot;       &bslash;&n;                     : &quot;+m&quot; ((rw)-&gt;lock) : &quot;a&quot; (&amp;(rw)-&gt;lock) &bslash;&n;&t;&t;     : &quot;2&quot;, &quot;3&quot;, &quot;cc&quot; )
DECL|macro|_raw_read_unlock
mdefine_line|#define _raw_read_unlock(rw) &bslash;&n;        asm volatile(&quot;   l     2,0(%1)&bslash;n&quot;   &bslash;&n;                     &quot;   j     1f&bslash;n&quot;     &bslash;&n;                     &quot;0: diag  0,0,68&bslash;n&quot; &bslash;&n;                     &quot;1: lr    3,2&bslash;n&quot;    &bslash;&n;                     &quot;   ahi   3,-1&bslash;n&quot;    /* one less reader */ &bslash;&n;                     &quot;   cs    2,3,0(%1)&bslash;n&quot; &bslash;&n;                     &quot;   jl    0b&quot;       &bslash;&n;                     : &quot;+m&quot; ((rw)-&gt;lock) : &quot;a&quot; (&amp;(rw)-&gt;lock) &bslash;&n;&t;&t;     : &quot;2&quot;, &quot;3&quot;, &quot;cc&quot; )
DECL|macro|_raw_write_lock
mdefine_line|#define _raw_write_lock(rw) &bslash;&n;        asm volatile(&quot;   lhi   3,1&bslash;n&quot;    &bslash;&n;                     &quot;   sll   3,31&bslash;n&quot;    /* new lock value = 0x80000000 */ &bslash;&n;                     &quot;   j     1f&bslash;n&quot;     &bslash;&n;                     &quot;0: diag  0,0,68&bslash;n&quot; &bslash;&n;                     &quot;1: slr   2,2&bslash;n&quot;     /* old lock value must be 0 */ &bslash;&n;                     &quot;   cs    2,3,0(%1)&bslash;n&quot; &bslash;&n;                     &quot;   jl    0b&quot;       &bslash;&n;                     : &quot;+m&quot; ((rw)-&gt;lock) : &quot;a&quot; (&amp;(rw)-&gt;lock) &bslash;&n;&t;&t;     : &quot;2&quot;, &quot;3&quot;, &quot;cc&quot; )
DECL|macro|_raw_write_unlock
mdefine_line|#define _raw_write_unlock(rw) &bslash;&n;        asm volatile(&quot;   slr   3,3&bslash;n&quot;     /* new lock value = 0 */ &bslash;&n;                     &quot;   j     1f&bslash;n&quot;     &bslash;&n;                     &quot;0: diag  0,0,68&bslash;n&quot; &bslash;&n;                     &quot;1: lhi   2,1&bslash;n&quot;    &bslash;&n;                     &quot;   sll   2,31&bslash;n&quot;    /* old lock value must be 0x80000000 */ &bslash;&n;                     &quot;   cs    2,3,0(%1)&bslash;n&quot; &bslash;&n;                     &quot;   jl    0b&quot;       &bslash;&n;                     : &quot;+m&quot; ((rw)-&gt;lock) : &quot;a&quot; (&amp;(rw)-&gt;lock) &bslash;&n;&t;&t;     : &quot;2&quot;, &quot;3&quot;, &quot;cc&quot; )
macro_line|#endif /* __ASM_SPINLOCK_H */
eof
