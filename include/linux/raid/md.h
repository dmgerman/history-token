multiline_comment|/*&n;   md.h : Multiple Devices driver for Linux&n;          Copyright (C) 1996-98 Ingo Molnar, Gadi Oxman&n;          Copyright (C) 1994-96 Marc ZYNGIER&n;&t;  &lt;zyngier@ufr-info-p7.ibp.fr&gt; or&n;&t;  &lt;maz@gloups.fdn.fr&gt;&n;&t;  &n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2, or (at your option)&n;   any later version.&n;   &n;   You should have received a copy of the GNU General Public License&n;   (for example /usr/src/linux/COPYING); if not, write to the Free&n;   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  &n;*/
macro_line|#ifndef _MD_H
DECL|macro|_MD_H
mdefine_line|#define _MD_H
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/mempool.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
multiline_comment|/*&n; * &squot;md_p.h&squot; holds the &squot;physical&squot; layout of RAID devices&n; * &squot;md_u.h&squot; holds the user &lt;=&gt; kernel API&n; *&n; * &squot;md_k.h&squot; holds kernel internal definitions&n; */
macro_line|#include &lt;linux/raid/md_p.h&gt;
macro_line|#include &lt;linux/raid/md_u.h&gt;
macro_line|#include &lt;linux/raid/md_k.h&gt;
multiline_comment|/*&n; * Different major versions are not compatible.&n; * Different minor versions are only downward compatible.&n; * Different patchlevel versions are downward and upward compatible.&n; */
DECL|macro|MD_MAJOR_VERSION
mdefine_line|#define MD_MAJOR_VERSION                0
DECL|macro|MD_MINOR_VERSION
mdefine_line|#define MD_MINOR_VERSION                90
DECL|macro|MD_PATCHLEVEL_VERSION
mdefine_line|#define MD_PATCHLEVEL_VERSION           0
multiline_comment|/*&n; * XXX(hch): This function is broken.  Someone who understands the md&n; * code needs to go through all callers, check whether bdev could&n; * be NULL and replace it with direct calls to bdevmame.&n; *&n; * This would also fix the returns buffer on stack issue nicely :)&n; */
DECL|function|bdev_partition_name
r_static
r_inline
r_const
r_char
op_star
id|bdev_partition_name
(paren
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
r_char
id|b
(braket
id|BDEVNAME_SIZE
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev
)paren
r_return
id|__bdevname
c_func
(paren
l_int|0
comma
id|b
)paren
suffix:semicolon
r_return
id|bdevname
c_func
(paren
id|bdev
comma
id|b
)paren
suffix:semicolon
)brace
r_extern
r_int
id|register_md_personality
(paren
r_int
id|p_num
comma
id|mdk_personality_t
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|unregister_md_personality
(paren
r_int
id|p_num
)paren
suffix:semicolon
r_extern
id|mdk_thread_t
op_star
id|md_register_thread
(paren
r_void
(paren
op_star
id|run
)paren
(paren
id|mddev_t
op_star
id|mddev
)paren
comma
id|mddev_t
op_star
id|mddev
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|md_unregister_thread
(paren
id|mdk_thread_t
op_star
id|thread
)paren
suffix:semicolon
r_extern
r_void
id|md_wakeup_thread
c_func
(paren
id|mdk_thread_t
op_star
id|thread
)paren
suffix:semicolon
r_extern
r_void
id|md_check_recovery
c_func
(paren
id|mddev_t
op_star
id|mddev
)paren
suffix:semicolon
r_extern
r_void
id|md_interrupt_thread
(paren
id|mdk_thread_t
op_star
id|thread
)paren
suffix:semicolon
r_extern
r_void
id|md_write_start
c_func
(paren
id|mddev_t
op_star
id|mddev
)paren
suffix:semicolon
r_extern
r_void
id|md_write_end
c_func
(paren
id|mddev_t
op_star
id|mddev
)paren
suffix:semicolon
r_extern
r_void
id|md_handle_safemode
c_func
(paren
id|mddev_t
op_star
id|mddev
)paren
suffix:semicolon
r_extern
r_void
id|md_done_sync
c_func
(paren
id|mddev_t
op_star
id|mddev
comma
r_int
id|blocks
comma
r_int
id|ok
)paren
suffix:semicolon
r_extern
r_void
id|md_sync_acct
c_func
(paren
id|mdk_rdev_t
op_star
id|rdev
comma
r_int
r_int
id|nr_sectors
)paren
suffix:semicolon
r_extern
r_void
id|md_error
(paren
id|mddev_t
op_star
id|mddev
comma
id|mdk_rdev_t
op_star
id|rdev
)paren
suffix:semicolon
r_extern
r_void
id|md_print_devices
(paren
r_void
)paren
suffix:semicolon
DECL|macro|MD_BUG
mdefine_line|#define MD_BUG(x...) { printk(&quot;md: bug in file %s, line %d&bslash;n&quot;, __FILE__, __LINE__); md_print_devices(); }
macro_line|#endif 
eof
