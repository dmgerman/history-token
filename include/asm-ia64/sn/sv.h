multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2001 Silicon Graphics, Inc.  All rights reserved&n; *&n; * This implemenation of synchronization variables is heavily based on&n; * one done by Steve Lord &lt;lord@sgi.com&gt;&n; *&n; * Paul Cassella &lt;pwc@sgi.com&gt;&n; */
macro_line|#ifndef _ASM_IA64_SN_SV_H
DECL|macro|_ASM_IA64_SN_SV_H
mdefine_line|#define _ASM_IA64_SN_SV_H
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#ifndef ASSERT
DECL|macro|ASSERT
mdefine_line|#define ASSERT(x) do {&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;                    if(!(x)) {&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;&t;      printk(KERN_ERR &quot;%s&bslash;n&quot;, &quot;Assertion failed: &quot; # x);  &bslash;&n;&t;&t;      BUG();&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;&t;    }&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;                  } while(0)
DECL|macro|_SV_ASSERT
mdefine_line|#define _SV_ASSERT
macro_line|#endif
DECL|typedef|sv_mon_lock_t
r_typedef
r_void
id|sv_mon_lock_t
suffix:semicolon
DECL|typedef|sv_mon_unlock_func_t
r_typedef
r_void
(paren
op_star
id|sv_mon_unlock_func_t
)paren
(paren
id|sv_mon_lock_t
op_star
id|lock
)paren
suffix:semicolon
multiline_comment|/* sv_flags values: */
DECL|macro|SV_ORDER_FIFO
mdefine_line|#define SV_ORDER_FIFO        0x001
DECL|macro|SV_ORDER_FILO
mdefine_line|#define SV_ORDER_FILO        0x002
DECL|macro|SV_ORDER_LIFO
mdefine_line|#define SV_ORDER_LIFO        SV_ORDER_FILO
multiline_comment|/* If at some point one order becomes preferable to others, we can&n;   switch to it if the caller of sv_init doesn&squot;t specify. */
DECL|macro|SV_ORDER_DEFAULT
mdefine_line|#define SV_ORDER_DEFAULT     SV_ORDER_FIFO
DECL|macro|SV_ORDER_MASK
mdefine_line|#define SV_ORDER_MASK        0x00f
DECL|macro|SV_MON_SEMA
mdefine_line|#define SV_MON_SEMA          0x010
DECL|macro|SV_MON_SPIN
mdefine_line|#define SV_MON_SPIN          0x020
DECL|macro|SV_MON_MASK
mdefine_line|#define SV_MON_MASK          0x0f0
multiline_comment|/*&n;   If the monitor lock can be aquired from interrupts.  Note that this&n;   is a superset of the cases in which the sv can be touched from&n;   interrupts.&n;&n;   This is currently only valid when the monitor lock is a spinlock.&n;&n;   If this is used, sv_wait, sv_signal, and sv_broadcast must all be&n;   called with interrupts disabled, which has to happen anyway to have&n;   acquired the monitor spinlock. &n; */
DECL|macro|SV_INTS
mdefine_line|#define SV_INTS              0x100
multiline_comment|/* ditto for bottom halves */
DECL|macro|SV_BHS
mdefine_line|#define SV_BHS               0x200
multiline_comment|/* sv_wait_flag values: */
DECL|macro|SV_WAIT_SIG
mdefine_line|#define SV_WAIT_SIG          0x001 /* Allow sv_wait to be interrupted by a signal */
DECL|struct|sv_s
r_typedef
r_struct
id|sv_s
(brace
DECL|member|sv_waiters
id|wait_queue_head_t
id|sv_waiters
suffix:semicolon
DECL|member|sv_mon_lock
id|sv_mon_lock_t
op_star
id|sv_mon_lock
suffix:semicolon
multiline_comment|/* Lock held for exclusive access to monitor. */
DECL|member|sv_mon_unlock_func
id|sv_mon_unlock_func_t
id|sv_mon_unlock_func
suffix:semicolon
DECL|member|sv_lock
id|spinlock_t
id|sv_lock
suffix:semicolon
multiline_comment|/* Spinlock protecting the sv itself. */
DECL|member|sv_flags
r_int
id|sv_flags
suffix:semicolon
DECL|typedef|sv_t
)brace
id|sv_t
suffix:semicolon
DECL|macro|DECLARE_SYNC_VARIABLE
mdefine_line|#define DECLARE_SYNC_VARIABLE(sv, l, f) sv_t sv = sv_init(&amp;sv, l, f)
multiline_comment|/* &n; * @sv the sync variable to initialize&n; * @monitor_lock the lock enforcing exclusive running in the monitor&n; * @flags one of&n; *   SV_MON_SEMA monitor_lock is a semaphore&n; *   SV_MON_SPIN monitor_lock is a spinlock&n; * and a bitwise or of some subset of&n; *   SV_INTS - the monitor lock can be acquired from interrupts (and&n; *             hence, whenever we hold it, interrupts are disabled or&n; *             we&squot;re in an interrupt.)  This is only valid when&n; *             SV_MON_SPIN is set.&n; */
r_void
id|sv_init
c_func
(paren
id|sv_t
op_star
id|sv
comma
id|sv_mon_lock_t
op_star
id|monitor_lock
comma
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n; * Set SV_WAIT_SIG in sv_wait_flags to let the sv_wait be interrupted by signals.&n; *&n; * timeout is how long to wait before giving up, or 0 to wait&n; * indefinately.  It is given in jiffies, and is relative.&n; *&n; * The associated lock must be locked on entry.  It is unlocked on return.&n; *&n; * Return values:&n; *&n; * n &lt; 0 : interrupted,  -n jiffies remaining on timeout, or -1 if timeout == 0&n; * n = 0 : timeout expired&n; * n &gt; 0 : sv_signal()&squot;d, n jiffies remaining on timeout, or 1 if timeout == 0&n; */
r_extern
r_int
r_int
id|sv_wait
c_func
(paren
id|sv_t
op_star
id|sv
comma
r_int
id|sv_wait_flags
comma
r_int
r_int
id|timeout
multiline_comment|/* relative jiffies */
)paren
suffix:semicolon
DECL|function|sv_wait_compat
r_static
r_inline
r_int
id|sv_wait_compat
c_func
(paren
id|sv_t
op_star
id|sv
comma
id|sv_mon_lock_t
op_star
id|lock
comma
r_int
id|sv_wait_flags
comma
r_int
r_int
id|timeout
comma
r_int
id|sv_mon_type
)paren
(brace
id|ASSERT
c_func
(paren
id|sv_mon_type
op_eq
(paren
id|sv-&gt;sv_flags
op_amp
id|SV_MON_MASK
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sv-&gt;sv_mon_lock
)paren
(brace
id|ASSERT
c_func
(paren
id|lock
op_eq
id|sv-&gt;sv_mon_lock
)paren
suffix:semicolon
)brace
r_else
id|sv-&gt;sv_mon_lock
op_assign
id|lock
suffix:semicolon
r_return
id|sv_wait
c_func
(paren
id|sv
comma
id|sv_wait_flags
comma
id|timeout
)paren
suffix:semicolon
)brace
multiline_comment|/* These work like Irix&squot;s sv_wait() and sv_wait_sig(), except the&n;   caller must call the one correpsonding to the type of the monitor&n;   lock. */
DECL|macro|sv_spin_wait
mdefine_line|#define sv_spin_wait(sv, lock)                              &bslash;&n;        sv_wait_compat(sv, lock, 0, 0, SV_MON_SPIN)
DECL|macro|sv_spin_wait_sig
mdefine_line|#define sv_spin_wait_sig(sv, lock)                          &bslash;&n;        sv_wait_compat(sv, lock, SV_WAIT_SIG, 0, SV_MON_SPIN)
DECL|macro|sv_sema_wait
mdefine_line|#define sv_sema_wait(sv, lock)                              &bslash;&n;        sv_wait_compat(sv, lock, 0, 0, SV_MON_SEMA)
DECL|macro|sv_sema_wait_sig
mdefine_line|#define sv_sema_wait_sig(sv, lock)                          &bslash;&n;        sv_wait_compat(sv, lock, SV_WAIT_SIG, 0, SV_MON_SEMA)
multiline_comment|/* These work as in Irix. */
r_void
id|sv_signal
c_func
(paren
id|sv_t
op_star
id|sv
)paren
suffix:semicolon
r_void
id|sv_broadcast
c_func
(paren
id|sv_t
op_star
id|sv
)paren
suffix:semicolon
multiline_comment|/* This works as in Irix. */
r_void
id|sv_destroy
c_func
(paren
id|sv_t
op_star
id|sv
)paren
suffix:semicolon
macro_line|#ifdef _SV_ASSERT
DECL|macro|ASSERT
macro_line|#undef ASSERT
DECL|macro|_SV_ASSERT
macro_line|#undef _SV_ASSERT
macro_line|#endif
macro_line|#endif /* _ASM_IA64_SN_SV_H */
eof
