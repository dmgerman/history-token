macro_line|#ifndef _ASM_PARISC_ATOMIC_H_
DECL|macro|_ASM_PARISC_ATOMIC_H_
mdefine_line|#define _ASM_PARISC_ATOMIC_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/* Copyright (C) 2000 Philipp Rumpf &lt;prumpf@tux.org&gt;.  */
multiline_comment|/*&n; * Atomic operations that C can&squot;t guarantee us.  Useful for&n; * resource counting etc..&n; *&n; * And probably incredibly slow on parisc.  OTOH, we don&squot;t&n; * have to write any serious assembly.   prumpf&n; */
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* we have an array of spinlocks for our atomic_ts, and a hash function&n; * to get the right index */
DECL|macro|ATOMIC_HASH_SIZE
macro_line|#  define ATOMIC_HASH_SIZE 1
DECL|macro|ATOMIC_HASH
macro_line|#  define ATOMIC_HASH(a) (&amp;__atomic_hash[0])
r_extern
id|spinlock_t
id|__atomic_hash
(braket
id|ATOMIC_HASH_SIZE
)braket
suffix:semicolon
multiline_comment|/* copied from &lt;asm/spinlock.h&gt; and modified */
DECL|macro|SPIN_LOCK
macro_line|#  define SPIN_LOCK(x) &bslash;&n;&t;do { while(__ldcw(&amp;(x)-&gt;lock) == 0); } while(0)
DECL|macro|SPIN_UNLOCK
macro_line|#  define SPIN_UNLOCK(x) &bslash;&n;&t;do { (x)-&gt;lock = 1; } while(0)
macro_line|#else
DECL|macro|ATOMIC_HASH_SIZE
macro_line|#  define ATOMIC_HASH_SIZE 1
DECL|macro|ATOMIC_HASH
macro_line|#  define ATOMIC_HASH(a)&t;(0)
multiline_comment|/* copied from &lt;linux/spinlock.h&gt; and modified */
DECL|macro|SPIN_LOCK
macro_line|#  define SPIN_LOCK(x) (void)(x)
DECL|macro|SPIN_UNLOCK
macro_line|#  define SPIN_UNLOCK(x) do { } while(0)
macro_line|#endif
multiline_comment|/* copied from &lt;linux/spinlock.h&gt; and modified */
DECL|macro|SPIN_LOCK_IRQSAVE
mdefine_line|#define SPIN_LOCK_IRQSAVE(lock, flags)&t;&t;do { local_irq_save(flags);       SPIN_LOCK(lock); } while (0)
DECL|macro|SPIN_UNLOCK_IRQRESTORE
mdefine_line|#define SPIN_UNLOCK_IRQRESTORE(lock, flags)&t;do { SPIN_UNLOCK(lock);  local_irq_restore(flags); } while (0)
multiline_comment|/* Note that we need not lock read accesses - aligned word writes/reads&n; * are atomic, so a reader never sees unconsistent values.&n; *&n; * Cache-line alignment would conflict with, for example, linux/module.h */
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
id|atomic_t
suffix:semicolon
multiline_comment|/* It&squot;s possible to reduce all atomic operations to either&n; * __atomic_add_return, __atomic_set and __atomic_ret (the latter&n; * is there only for consistency). */
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
id|SPIN_LOCK_IRQSAVE
c_func
(paren
id|ATOMIC_HASH
c_func
(paren
id|v
)paren
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
id|SPIN_UNLOCK_IRQRESTORE
c_func
(paren
id|ATOMIC_HASH
c_func
(paren
id|v
)paren
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|__atomic_set
r_static
id|__inline__
r_void
id|__atomic_set
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
id|SPIN_LOCK_IRQSAVE
c_func
(paren
id|ATOMIC_HASH
c_func
(paren
id|v
)paren
comma
id|flags
)paren
suffix:semicolon
id|v-&gt;counter
op_assign
id|i
suffix:semicolon
id|SPIN_UNLOCK_IRQRESTORE
c_func
(paren
id|ATOMIC_HASH
c_func
(paren
id|v
)paren
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|__atomic_read
r_static
id|__inline__
r_int
id|__atomic_read
c_func
(paren
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
mdefine_line|#define atomic_add(i,v)&t;&t;((void)(__atomic_add_return( (i),(v))))
DECL|macro|atomic_sub
mdefine_line|#define atomic_sub(i,v)&t;&t;((void)(__atomic_add_return(-(i),(v))))
DECL|macro|atomic_inc
mdefine_line|#define atomic_inc(v)&t;&t;((void)(__atomic_add_return(   1,(v))))
DECL|macro|atomic_dec
mdefine_line|#define atomic_dec(v)&t;&t;((void)(__atomic_add_return(  -1,(v))))
DECL|macro|atomic_add_return
mdefine_line|#define atomic_add_return(i,v)&t;(__atomic_add_return( (i),(v)))
DECL|macro|atomic_sub_return
mdefine_line|#define atomic_sub_return(i,v)&t;(__atomic_add_return(-(i),(v)))
DECL|macro|atomic_inc_return
mdefine_line|#define atomic_inc_return(v)&t;(__atomic_add_return(   1,(v)))
DECL|macro|atomic_dec_return
mdefine_line|#define atomic_dec_return(v)&t;(__atomic_add_return(  -1,(v)))
DECL|macro|atomic_dec_and_test
mdefine_line|#define atomic_dec_and_test(v)&t;(atomic_dec_return(v) == 0)
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v,i)&t;&t;(__atomic_set((v),i))
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)&t;&t;(__atomic_read(v))
DECL|macro|ATOMIC_INIT
mdefine_line|#define ATOMIC_INIT(i)&t;{ (i) }
macro_line|#endif
eof
