multiline_comment|/*&n;   md.h : Multiple Devices driver compatibility layer for Linux 2.0/2.2&n;          Copyright (C) 1998 Ingo Molnar&n;&t;  &n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2, or (at your option)&n;   any later version.&n;   &n;   You should have received a copy of the GNU General Public License&n;   (for example /usr/src/linux/COPYING); if not, write to the Free&n;   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  &n;*/
macro_line|#include &lt;linux/version.h&gt;
macro_line|#ifndef _MD_COMPATIBLE_H
DECL|macro|_MD_COMPATIBLE_H
mdefine_line|#define _MD_COMPATIBLE_H
multiline_comment|/** 2.3/2.4 stuff: **/
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/blkpg.h&gt;
multiline_comment|/* 000 */
DECL|macro|md__get_free_pages
mdefine_line|#define md__get_free_pages(x,y) __get_free_pages(x,y)
macro_line|#ifdef __i386__
multiline_comment|/* 001 */
DECL|function|md_cpu_has_mmx
r_extern
id|__inline__
r_int
id|md_cpu_has_mmx
c_func
(paren
r_void
)paren
(brace
r_return
id|test_bit
c_func
(paren
id|X86_FEATURE_MMX
comma
op_amp
id|boot_cpu_data.x86_capability
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* 002 */
DECL|macro|md_clear_page
mdefine_line|#define md_clear_page(page)        clear_page(page)
multiline_comment|/* 003 */
DECL|macro|MD_EXPORT_SYMBOL
mdefine_line|#define MD_EXPORT_SYMBOL(x) EXPORT_SYMBOL(x)
multiline_comment|/* 004 */
DECL|macro|md_copy_to_user
mdefine_line|#define md_copy_to_user(x,y,z) copy_to_user(x,y,z)
multiline_comment|/* 005 */
DECL|macro|md_copy_from_user
mdefine_line|#define md_copy_from_user(x,y,z) copy_from_user(x,y,z)
multiline_comment|/* 006 */
DECL|macro|md_put_user
mdefine_line|#define md_put_user put_user
multiline_comment|/* 007 */
DECL|function|md_capable_admin
r_extern
r_inline
r_int
id|md_capable_admin
c_func
(paren
r_void
)paren
(brace
r_return
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
suffix:semicolon
)brace
multiline_comment|/* 008 */
DECL|macro|MD_FILE_TO_INODE
mdefine_line|#define MD_FILE_TO_INODE(file) ((file)-&gt;f_dentry-&gt;d_inode)
multiline_comment|/* 009 */
DECL|function|md_flush_signals
r_extern
r_inline
r_void
id|md_flush_signals
(paren
r_void
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|flush_signals
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* 010 */
DECL|function|md_init_signals
r_extern
r_inline
r_void
id|md_init_signals
(paren
r_void
)paren
(brace
id|current-&gt;exit_signal
op_assign
id|SIGCHLD
suffix:semicolon
id|siginitsetinv
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|sigmask
c_func
(paren
id|SIGKILL
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* 011 */
DECL|macro|md_signal_pending
mdefine_line|#define md_signal_pending signal_pending
multiline_comment|/* 012 - md_set_global_readahead - nowhere used */
multiline_comment|/* 013 */
DECL|macro|md_mdelay
mdefine_line|#define md_mdelay(x) mdelay(x)
multiline_comment|/* 014 */
DECL|macro|MD_SYS_DOWN
mdefine_line|#define MD_SYS_DOWN SYS_DOWN
DECL|macro|MD_SYS_HALT
mdefine_line|#define MD_SYS_HALT SYS_HALT
DECL|macro|MD_SYS_POWER_OFF
mdefine_line|#define MD_SYS_POWER_OFF SYS_POWER_OFF
multiline_comment|/* 015 */
DECL|macro|md_register_reboot_notifier
mdefine_line|#define md_register_reboot_notifier register_reboot_notifier
multiline_comment|/* 016 */
DECL|macro|md_test_and_set_bit
mdefine_line|#define md_test_and_set_bit test_and_set_bit
multiline_comment|/* 017 */
DECL|macro|md_test_and_clear_bit
mdefine_line|#define md_test_and_clear_bit test_and_clear_bit
multiline_comment|/* 018 */
DECL|macro|md_atomic_read
mdefine_line|#define md_atomic_read atomic_read
DECL|macro|md_atomic_set
mdefine_line|#define md_atomic_set atomic_set
multiline_comment|/* 019 */
DECL|macro|md_lock_kernel
mdefine_line|#define md_lock_kernel lock_kernel
DECL|macro|md_unlock_kernel
mdefine_line|#define md_unlock_kernel unlock_kernel
multiline_comment|/* 020 */
macro_line|#include &lt;linux/init.h&gt;
DECL|macro|md__init
mdefine_line|#define md__init __init
DECL|macro|md__initdata
mdefine_line|#define md__initdata __initdata
DECL|macro|md__initfunc
mdefine_line|#define md__initfunc(__arginit) __initfunc(__arginit)
multiline_comment|/* 021 */
multiline_comment|/* 022 */
DECL|macro|md_list_head
mdefine_line|#define md_list_head list_head
DECL|macro|MD_LIST_HEAD
mdefine_line|#define MD_LIST_HEAD(name) LIST_HEAD(name)
DECL|macro|MD_INIT_LIST_HEAD
mdefine_line|#define MD_INIT_LIST_HEAD(ptr) INIT_LIST_HEAD(ptr)
DECL|macro|md_list_add
mdefine_line|#define md_list_add list_add
DECL|macro|md_list_del
mdefine_line|#define md_list_del list_del
DECL|macro|md_list_empty
mdefine_line|#define md_list_empty list_empty
DECL|macro|md_list_entry
mdefine_line|#define md_list_entry(ptr, type, member) list_entry(ptr, type, member)
multiline_comment|/* 023 */
DECL|macro|md_schedule_timeout
mdefine_line|#define md_schedule_timeout schedule_timeout
multiline_comment|/* 024 */
DECL|macro|md_need_resched
mdefine_line|#define md_need_resched(tsk) ((tsk)-&gt;need_resched)
multiline_comment|/* 025 */
DECL|macro|md_spinlock_t
mdefine_line|#define md_spinlock_t spinlock_t
DECL|macro|MD_SPIN_LOCK_UNLOCKED
mdefine_line|#define MD_SPIN_LOCK_UNLOCKED SPIN_LOCK_UNLOCKED
DECL|macro|md_spin_lock
mdefine_line|#define md_spin_lock spin_lock
DECL|macro|md_spin_unlock
mdefine_line|#define md_spin_unlock spin_unlock
DECL|macro|md_spin_lock_irq
mdefine_line|#define md_spin_lock_irq spin_lock_irq
DECL|macro|md_spin_unlock_irq
mdefine_line|#define md_spin_unlock_irq spin_unlock_irq
DECL|macro|md_spin_unlock_irqrestore
mdefine_line|#define md_spin_unlock_irqrestore spin_unlock_irqrestore
DECL|macro|md_spin_lock_irqsave
mdefine_line|#define md_spin_lock_irqsave spin_lock_irqsave
multiline_comment|/* 026 */
DECL|typedef|md_wait_queue_head_t
r_typedef
id|wait_queue_head_t
id|md_wait_queue_head_t
suffix:semicolon
DECL|macro|MD_DECLARE_WAITQUEUE
mdefine_line|#define MD_DECLARE_WAITQUEUE(w,t) DECLARE_WAITQUEUE((w),(t))
DECL|macro|MD_DECLARE_WAIT_QUEUE_HEAD
mdefine_line|#define MD_DECLARE_WAIT_QUEUE_HEAD(x) DECLARE_WAIT_QUEUE_HEAD(x)
DECL|macro|md_init_waitqueue_head
mdefine_line|#define md_init_waitqueue_head init_waitqueue_head
multiline_comment|/* END */
macro_line|#endif 
eof
