macro_line|#ifndef __ASM_SPINLOCK_H
DECL|macro|__ASM_SPINLOCK_H
mdefine_line|#define __ASM_SPINLOCK_H
multiline_comment|/*&n; * Simple spin lock operations.  &n; *&n; * Copyright (C) 2001 Paul Mackerras &lt;paulus@au.ibm.com&gt;, IBM&n; * Copyright (C) 2001 Anton Blanchard &lt;anton@au.ibm.com&gt;, IBM&n; *&n; * Type of int is used as a full 64b word is not necessary.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
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
macro_line|#ifdef __KERNEL__
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED&t;(spinlock_t) { 0 }
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(x)&t;((x)-&gt;lock != 0)
DECL|function|_raw_spin_trylock
r_static
id|__inline__
r_int
id|_raw_spin_trylock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;lwarx&t;&t;%0,0,%1&t;&t;# spin_trylock&bslash;n&bslash;&n;&t;cmpwi&t;&t;0,%0,0&bslash;n&bslash;&n;&t;li&t;&t;%0,0&bslash;n&bslash;&n;&t;bne-&t;&t;2f&bslash;n&bslash;&n;&t;li&t;&t;%0,1&bslash;n&bslash;&n;&t;stwcx.&t;&t;%0,0,%1&bslash;n&bslash;&n;&t;bne-&t;&t;1b&bslash;n&bslash;&n;&t;isync&bslash;n&bslash;&n;2:&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|lock-&gt;lock
)paren
suffix:colon
l_string|&quot;cr0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
DECL|function|_raw_spin_lock
r_static
id|__inline__
r_void
id|_raw_spin_lock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;b&t;&t;2f&t;&t;# spin_lock&bslash;n&bslash;&n;1:&t;or&t;&t;1,1,1&t;&t;# spin at low priority&bslash;n&bslash;&n;&t;lwzx&t;&t;%0,0,%1&bslash;n&bslash;&n;&t;cmpwi&t;&t;0,%0,0&bslash;n&bslash;&n;&t;bne+&t;&t;1b&bslash;n&bslash;&n;&t;or&t;&t;2,2,2&t;&t;# back to medium priority&bslash;n&bslash;&n;2:&t;lwarx&t;&t;%0,0,%1&bslash;n&bslash;&n;&t;cmpwi&t;&t;0,%0,0&bslash;n&bslash;&n;&t;bne-&t;&t;1b&bslash;n&bslash;&n;&t;stwcx.&t;&t;%2,0,%1&bslash;n&bslash;&n;&t;bne-&t;&t;2b&bslash;n&bslash;&n;&t;isync&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|lock-&gt;lock
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|1
)paren
suffix:colon
l_string|&quot;cr0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|_raw_spin_unlock
r_static
id|__inline__
r_void
id|_raw_spin_unlock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;eieio&t;# spin_unlock&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|lock-&gt;lock
op_assign
l_int|0
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
DECL|typedef|rwlock_t
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { 0 }
DECL|function|_raw_read_trylock
r_static
id|__inline__
r_int
id|_raw_read_trylock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;lwarx&t;&t;%0,0,%2&t;&t;# read_trylock&bslash;n&bslash;&n;&t;li&t;&t;%1,0&bslash;n&bslash;&n;&t;extsw&t;&t;%0,%0&bslash;n&bslash;&n;&t;addic.&t;&t;%0,%0,1&bslash;n&bslash;&n;&t;ble-&t;&t;2f&bslash;n&bslash;&n;&t;stwcx.&t;&t;%0,0,%2&bslash;n&bslash;&n;&t;bne-&t;&t;1b&bslash;n&bslash;&n;&t;li&t;&t;%1,1&bslash;n&bslash;&n;&t;isync&bslash;n&bslash;&n;2:&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;cr0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|_raw_read_lock
r_static
id|__inline__
r_void
id|_raw_read_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;b&t;&t;2f&t;&t;# read_lock&bslash;n&bslash;&n;1:&t;or&t;&t;1,1,1&t;&t;# spin at low priority&bslash;n&bslash;&n;&t;lwax&t;&t;%0,0,%1&bslash;n&bslash;&n;&t;cmpwi&t;&t;0,%0,0&bslash;n&bslash;&n;&t;blt+&t;&t;1b&bslash;n&bslash;&n;&t;or&t;&t;2,2,2&t;&t;# back to medium priority&bslash;n&bslash;&n;2:&t;lwarx&t;&t;%0,0,%1&bslash;n&bslash;&n;&t;extsw&t;&t;%0,%0&bslash;n&bslash;&n;&t;addic.&t;&t;%0,%0,1&bslash;n&bslash;&n;&t;ble-&t;&t;1b&bslash;n&bslash;&n;&t;stwcx.&t;&t;%0,0,%1&bslash;n&bslash;&n;&t;bne-&t;&t;2b&bslash;n&bslash;&n;&t;isync&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;cr0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|_raw_read_unlock
r_static
id|__inline__
r_void
id|_raw_read_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;eieio&t;&t;&t;&t;# read_unlock&bslash;n&bslash;&n;1:&t;lwarx&t;&t;%0,0,%1&bslash;n&bslash;&n;&t;addic&t;&t;%0,%0,-1&bslash;n&bslash;&n;&t;stwcx.&t;&t;%0,0,%1&bslash;n&bslash;&n;&t;bne-&t;&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;cr0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|_raw_write_trylock
r_static
id|__inline__
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
id|tmp
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;lwarx&t;&t;%0,0,%2&t;&t;# write_trylock&bslash;n&bslash;&n;&t;cmpwi&t;&t;0,%0,0&bslash;n&bslash;&n;&t;li&t;&t;%1,0&bslash;n&bslash;&n;&t;bne-&t;&t;2f&bslash;n&bslash;&n;&t;stwcx.&t;&t;%3,0,%2&bslash;n&bslash;&n;&t;bne-&t;&t;1b&bslash;n&bslash;&n;&t;li&t;&t;%1,1&bslash;n&bslash;&n;&t;isync&bslash;n&bslash;&n;2:&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|rw-&gt;lock
)paren
comma
l_string|&quot;r&quot;
(paren
op_minus
l_int|1
)paren
suffix:colon
l_string|&quot;cr0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|_raw_write_lock
r_static
id|__inline__
r_void
id|_raw_write_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;b&t;&t;2f&t;&t;# write_lock&bslash;n&bslash;&n;1:&t;or&t;&t;1,1,1&t;&t;# spin at low priority&bslash;n&bslash;&n;&t;lwax&t;&t;%0,0,%1&bslash;n&bslash;&n;&t;cmpwi&t;&t;0,%0,0&bslash;n&bslash;&n;&t;bne+&t;&t;1b&bslash;n&bslash;&n;&t;or&t;&t;2,2,2&t;&t;# back to medium priority&bslash;n&bslash;&n;2:&t;lwarx&t;&t;%0,0,%1&bslash;n&bslash;&n;&t;cmpwi&t;&t;0,%0,0&bslash;n&bslash;&n;&t;bne-&t;&t;1b&bslash;n&bslash;&n;&t;stwcx.&t;&t;%2,0,%1&bslash;n&bslash;&n;&t;bne-&t;&t;2b&bslash;n&bslash;&n;&t;isync&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|rw-&gt;lock
)paren
comma
l_string|&quot;r&quot;
(paren
op_minus
l_int|1
)paren
suffix:colon
l_string|&quot;cr0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|_raw_write_unlock
r_static
id|__inline__
r_void
id|_raw_write_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;eieio&t;&t;# write_unlock&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|rw-&gt;lock
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|is_read_locked
r_static
id|__inline__
r_int
id|is_read_locked
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_return
id|rw-&gt;lock
OG
l_int|0
suffix:semicolon
)brace
DECL|function|is_write_locked
r_static
id|__inline__
r_int
id|is_write_locked
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_return
id|rw-&gt;lock
OL
l_int|0
suffix:semicolon
)brace
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x)      do { *(x) = SPIN_LOCK_UNLOCKED; } while(0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(x)    do { barrier(); } while(spin_is_locked(x))
DECL|macro|rwlock_init
mdefine_line|#define rwlock_init(x)         do { *(x) = RW_LOCK_UNLOCKED; } while(0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_SPINLOCK_H */
eof
