multiline_comment|/*&n; *      Copyright (C) 1996, 1997 Claus-Justus Heine.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; *      This file contains the code that registers the zftape frontend &n; *      to the ftape floppy tape driver for Linux&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#ifdef CONFIG_KMOD
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/wrapper.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/zftape.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;../zftape/zftape-init.h&quot;
macro_line|#include &quot;../zftape/zftape-read.h&quot;
macro_line|#include &quot;../zftape/zftape-write.h&quot;
macro_line|#include &quot;../zftape/zftape-ctl.h&quot;
macro_line|#include &quot;../zftape/zftape-buffers.h&quot;
macro_line|#include &quot;../zftape/zftape_syms.h&quot;
DECL|variable|__initdata
r_char
id|zft_src
(braket
)braket
id|__initdata
op_assign
l_string|&quot;$Source: /homes/cvs/ftape-stacked/ftape/zftape/zftape-init.c,v $&quot;
suffix:semicolon
DECL|variable|__initdata
r_char
id|zft_rev
(braket
)braket
id|__initdata
op_assign
l_string|&quot;$Revision: 1.8 $&quot;
suffix:semicolon
DECL|variable|__initdata
r_char
id|zft_dat
(braket
)braket
id|__initdata
op_assign
l_string|&quot;$Date: 1997/11/06 00:48:56 $&quot;
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;(c) 1996, 1997 Claus-Justus Heine &quot;
l_string|&quot;(claus@momo.math.rwth-aachen.de)&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
id|ZFTAPE_VERSION
l_string|&quot; - &quot;
l_string|&quot;VFS interface for the Linux floppy tape driver. &quot;
l_string|&quot;Support for QIC-113 compatible volume table &quot;
l_string|&quot;and builtin compression (lzrw3 algorithm)&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;char-major-27&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*      Global vars.&n; */
DECL|variable|zft_cmpr_ops
r_struct
id|zft_cmpr_ops
op_star
id|zft_cmpr_ops
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|zft_status
r_const
id|ftape_info
op_star
id|zft_status
suffix:semicolon
multiline_comment|/*      Local vars.&n; */
DECL|variable|busy_flag
r_static
r_int
r_int
id|busy_flag
suffix:semicolon
DECL|variable|orig_sigmask
r_static
id|sigset_t
id|orig_sigmask
suffix:semicolon
multiline_comment|/*  the interface to the kernel vfs layer&n; */
multiline_comment|/* Note about llseek():&n; *&n; * st.c and tpqic.c update fp-&gt;f_pos but don&squot;t implment llseek() and&n; * initialize the llseek component of the file_ops struct with NULL.&n; * This means that the user will get the default seek, but the tape&n; * device will not respect the new position, but happily read from the&n; * old position. Think a zftape specific llseek() function would be&n; * better, returning -ESPIPE. TODO.&n; */
r_static
r_int
id|zft_open
(paren
r_struct
id|inode
op_star
id|ino
comma
r_struct
id|file
op_star
id|filep
)paren
suffix:semicolon
r_static
r_int
id|zft_close
c_func
(paren
r_struct
id|inode
op_star
id|ino
comma
r_struct
id|file
op_star
id|filep
)paren
suffix:semicolon
r_static
r_int
id|zft_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|ino
comma
r_struct
id|file
op_star
id|filep
comma
r_int
r_int
id|command
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_static
r_int
id|zft_mmap
c_func
(paren
r_struct
id|file
op_star
id|filep
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
suffix:semicolon
r_static
id|ssize_t
id|zft_read
(paren
r_struct
id|file
op_star
id|fp
comma
r_char
op_star
id|buff
comma
r_int
id|req_len
comma
id|loff_t
op_star
id|ppos
)paren
suffix:semicolon
r_static
id|ssize_t
id|zft_write
c_func
(paren
r_struct
id|file
op_star
id|fp
comma
r_const
r_char
op_star
id|buff
comma
r_int
id|req_len
comma
id|loff_t
op_star
id|ppos
)paren
suffix:semicolon
DECL|variable|zft_cdev
r_static
r_struct
id|file_operations
id|zft_cdev
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|read
suffix:colon
id|zft_read
comma
id|write
suffix:colon
id|zft_write
comma
id|ioctl
suffix:colon
id|zft_ioctl
comma
id|mmap
suffix:colon
id|zft_mmap
comma
id|open
suffix:colon
id|zft_open
comma
id|release
suffix:colon
id|zft_close
comma
)brace
suffix:semicolon
multiline_comment|/*      Open floppy tape device&n; */
DECL|function|zft_open
r_static
r_int
id|zft_open
c_func
(paren
r_struct
id|inode
op_star
id|ino
comma
r_struct
id|file
op_star
id|filep
)paren
(brace
r_int
id|result
suffix:semicolon
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
id|TRACE
c_func
(paren
id|ft_t_flow
comma
l_string|&quot;called for minor %d&quot;
comma
id|minor
c_func
(paren
id|ino-&gt;i_rdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|busy_flag
)paren
)paren
(brace
id|TRACE_ABORT
c_func
(paren
op_minus
id|EBUSY
comma
id|ft_t_warn
comma
l_string|&quot;failed: already busy&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|minor
c_func
(paren
id|ino-&gt;i_rdev
)paren
op_amp
op_complement
(paren
id|ZFT_MINOR_OP_MASK
op_or
id|FTAPE_NO_REWIND
)paren
)paren
OG
id|FTAPE_SEL_D
)paren
(brace
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|busy_flag
)paren
suffix:semicolon
id|TRACE_ABORT
c_func
(paren
op_minus
id|ENXIO
comma
id|ft_t_err
comma
l_string|&quot;failed: illegal unit nr&quot;
)paren
suffix:semicolon
)brace
id|orig_sigmask
op_assign
id|current-&gt;blocked
suffix:semicolon
id|sigfillset
c_func
(paren
op_amp
id|current-&gt;blocked
)paren
suffix:semicolon
id|result
op_assign
id|_zft_open
c_func
(paren
id|minor
c_func
(paren
id|ino-&gt;i_rdev
)paren
comma
id|filep-&gt;f_flags
op_amp
id|O_ACCMODE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|current-&gt;blocked
op_assign
id|orig_sigmask
suffix:semicolon
multiline_comment|/* restore mask */
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|busy_flag
)paren
suffix:semicolon
id|TRACE_ABORT
c_func
(paren
id|result
comma
id|ft_t_err
comma
l_string|&quot;_ftape_open failed&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Mask signals that will disturb proper operation of the&n;&t;&t; * program that is calling.&n;&t;&t; */
id|current-&gt;blocked
op_assign
id|orig_sigmask
suffix:semicolon
id|sigaddsetmask
(paren
op_amp
id|current-&gt;blocked
comma
id|_DO_BLOCK
)paren
suffix:semicolon
id|TRACE_EXIT
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*      Close floppy tape device&n; */
DECL|function|zft_close
r_static
r_int
id|zft_close
c_func
(paren
r_struct
id|inode
op_star
id|ino
comma
r_struct
id|file
op_star
id|filep
)paren
(brace
r_int
id|result
suffix:semicolon
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|busy_flag
)paren
op_logical_or
id|minor
c_func
(paren
id|ino-&gt;i_rdev
)paren
op_ne
id|zft_unit
)paren
(brace
id|TRACE
c_func
(paren
id|ft_t_err
comma
l_string|&quot;failed: not busy or wrong unit&quot;
)paren
suffix:semicolon
id|TRACE_EXIT
l_int|0
suffix:semicolon
)brace
id|sigfillset
c_func
(paren
op_amp
id|current-&gt;blocked
)paren
suffix:semicolon
id|result
op_assign
id|_zft_close
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|TRACE
c_func
(paren
id|ft_t_err
comma
l_string|&quot;_zft_close failed&quot;
)paren
suffix:semicolon
)brace
id|current-&gt;blocked
op_assign
id|orig_sigmask
suffix:semicolon
multiline_comment|/* restore before open state */
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|busy_flag
)paren
suffix:semicolon
id|TRACE_EXIT
l_int|0
suffix:semicolon
)brace
multiline_comment|/*      Ioctl for floppy tape device&n; */
DECL|function|zft_ioctl
r_static
r_int
id|zft_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|ino
comma
r_struct
id|file
op_star
id|filep
comma
r_int
r_int
id|command
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
id|sigset_t
id|old_sigmask
suffix:semicolon
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|busy_flag
)paren
op_logical_or
id|minor
c_func
(paren
id|ino-&gt;i_rdev
)paren
op_ne
id|zft_unit
op_logical_or
id|ft_failure
)paren
(brace
id|TRACE_ABORT
c_func
(paren
op_minus
id|EIO
comma
id|ft_t_err
comma
l_string|&quot;failed: not busy, failure or wrong unit&quot;
)paren
suffix:semicolon
)brace
id|old_sigmask
op_assign
id|current-&gt;blocked
suffix:semicolon
multiline_comment|/* save mask */
id|sigfillset
c_func
(paren
op_amp
id|current-&gt;blocked
)paren
suffix:semicolon
multiline_comment|/* This will work as long as sizeof(void *) == sizeof(long) */
id|result
op_assign
id|_zft_ioctl
c_func
(paren
id|command
comma
(paren
r_void
op_star
)paren
id|arg
)paren
suffix:semicolon
id|current-&gt;blocked
op_assign
id|old_sigmask
suffix:semicolon
multiline_comment|/* restore mask */
id|TRACE_EXIT
id|result
suffix:semicolon
)brace
multiline_comment|/*      Ioctl for floppy tape device&n; */
DECL|function|zft_mmap
r_static
r_int
id|zft_mmap
c_func
(paren
r_struct
id|file
op_star
id|filep
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_int
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
id|sigset_t
id|old_sigmask
suffix:semicolon
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|busy_flag
)paren
op_logical_or
id|minor
c_func
(paren
id|filep-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
op_ne
id|zft_unit
op_logical_or
id|ft_failure
)paren
(brace
id|TRACE_ABORT
c_func
(paren
op_minus
id|EIO
comma
id|ft_t_err
comma
l_string|&quot;failed: not busy, failure or wrong unit&quot;
)paren
suffix:semicolon
)brace
id|old_sigmask
op_assign
id|current-&gt;blocked
suffix:semicolon
multiline_comment|/* save mask */
id|sigfillset
c_func
(paren
op_amp
id|current-&gt;blocked
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|ftape_mmap
c_func
(paren
id|vma
)paren
)paren
op_ge
l_int|0
)paren
(brace
macro_line|#ifndef MSYNC_BUG_WAS_FIXED
r_static
r_struct
id|vm_operations_struct
id|dummy
op_assign
(brace
l_int|NULL
comma
)brace
suffix:semicolon
id|vma-&gt;vm_ops
op_assign
op_amp
id|dummy
suffix:semicolon
macro_line|#endif
)brace
id|current-&gt;blocked
op_assign
id|old_sigmask
suffix:semicolon
multiline_comment|/* restore mask */
id|TRACE_EXIT
id|result
suffix:semicolon
)brace
multiline_comment|/*      Read from floppy tape device&n; */
DECL|function|zft_read
r_static
id|ssize_t
id|zft_read
c_func
(paren
r_struct
id|file
op_star
id|fp
comma
r_char
op_star
id|buff
comma
r_int
id|req_len
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
id|sigset_t
id|old_sigmask
suffix:semicolon
r_struct
id|inode
op_star
id|ino
op_assign
id|fp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
id|TRACE
c_func
(paren
id|ft_t_data_flow
comma
l_string|&quot;called with count: %ld&quot;
comma
(paren
r_int
r_int
)paren
id|req_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|busy_flag
)paren
op_logical_or
id|minor
c_func
(paren
id|ino-&gt;i_rdev
)paren
op_ne
id|zft_unit
op_logical_or
id|ft_failure
)paren
(brace
id|TRACE_ABORT
c_func
(paren
op_minus
id|EIO
comma
id|ft_t_err
comma
l_string|&quot;failed: not busy, failure or wrong unit&quot;
)paren
suffix:semicolon
)brace
id|old_sigmask
op_assign
id|current-&gt;blocked
suffix:semicolon
multiline_comment|/* save mask */
id|sigfillset
c_func
(paren
op_amp
id|current-&gt;blocked
)paren
suffix:semicolon
id|result
op_assign
id|_zft_read
c_func
(paren
id|buff
comma
id|req_len
)paren
suffix:semicolon
id|current-&gt;blocked
op_assign
id|old_sigmask
suffix:semicolon
multiline_comment|/* restore mask */
id|TRACE
c_func
(paren
id|ft_t_data_flow
comma
l_string|&quot;return with count: %d&quot;
comma
id|result
)paren
suffix:semicolon
id|TRACE_EXIT
id|result
suffix:semicolon
)brace
multiline_comment|/*      Write to tape device&n; */
DECL|function|zft_write
r_static
id|ssize_t
id|zft_write
c_func
(paren
r_struct
id|file
op_star
id|fp
comma
r_const
r_char
op_star
id|buff
comma
r_int
id|req_len
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
id|sigset_t
id|old_sigmask
suffix:semicolon
r_struct
id|inode
op_star
id|ino
op_assign
id|fp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
id|TRACE
c_func
(paren
id|ft_t_flow
comma
l_string|&quot;called with count: %ld&quot;
comma
(paren
r_int
r_int
)paren
id|req_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|busy_flag
)paren
op_logical_or
id|minor
c_func
(paren
id|ino-&gt;i_rdev
)paren
op_ne
id|zft_unit
op_logical_or
id|ft_failure
)paren
(brace
id|TRACE_ABORT
c_func
(paren
op_minus
id|EIO
comma
id|ft_t_err
comma
l_string|&quot;failed: not busy, failure or wrong unit&quot;
)paren
suffix:semicolon
)brace
id|old_sigmask
op_assign
id|current-&gt;blocked
suffix:semicolon
multiline_comment|/* save mask */
id|sigfillset
c_func
(paren
op_amp
id|current-&gt;blocked
)paren
suffix:semicolon
id|result
op_assign
id|_zft_write
c_func
(paren
id|buff
comma
id|req_len
)paren
suffix:semicolon
id|current-&gt;blocked
op_assign
id|old_sigmask
suffix:semicolon
multiline_comment|/* restore mask */
id|TRACE
c_func
(paren
id|ft_t_data_flow
comma
l_string|&quot;return with count: %d&quot;
comma
id|result
)paren
suffix:semicolon
id|TRACE_EXIT
id|result
suffix:semicolon
)brace
multiline_comment|/*                    END OF VFS INTERFACE &n; *          &n; *****************************************************************************/
multiline_comment|/*  driver/module initialization&n; */
multiline_comment|/*  the compression module has to call this function to hook into the zftape &n; *  code&n; */
DECL|function|zft_cmpr_register
r_int
id|zft_cmpr_register
c_func
(paren
r_struct
id|zft_cmpr_ops
op_star
id|new_ops
)paren
(brace
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
r_if
c_cond
(paren
id|zft_cmpr_ops
op_ne
l_int|NULL
)paren
(brace
id|TRACE_EXIT
op_minus
id|EBUSY
suffix:semicolon
)brace
r_else
(brace
id|zft_cmpr_ops
op_assign
id|new_ops
suffix:semicolon
id|TRACE_EXIT
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|zft_cmpr_unregister
r_struct
id|zft_cmpr_ops
op_star
id|zft_cmpr_unregister
c_func
(paren
r_void
)paren
(brace
r_struct
id|zft_cmpr_ops
op_star
id|old_ops
op_assign
id|zft_cmpr_ops
suffix:semicolon
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
id|zft_cmpr_ops
op_assign
l_int|NULL
suffix:semicolon
id|TRACE_EXIT
id|old_ops
suffix:semicolon
)brace
multiline_comment|/*  lock the zft-compressor() module.&n; */
DECL|function|zft_cmpr_lock
r_int
id|zft_cmpr_lock
c_func
(paren
r_int
id|try_to_load
)paren
(brace
r_if
c_cond
(paren
id|zft_cmpr_ops
op_eq
l_int|NULL
)paren
(brace
macro_line|#ifdef CONFIG_KMOD
r_if
c_cond
(paren
id|try_to_load
)paren
(brace
id|request_module
c_func
(paren
l_string|&quot;zft-compressor&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|zft_cmpr_ops
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
)brace
r_else
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
macro_line|#else
r_return
op_minus
id|ENOSYS
suffix:semicolon
macro_line|#endif
)brace
(paren
op_star
id|zft_cmpr_ops-&gt;lock
)paren
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ZFT_COMPRESSOR
r_extern
r_int
id|zft_compressor_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*  Called by modules package when installing the driver or by kernel&n; *  during the initialization phase&n; */
DECL|function|zft_init
r_int
id|__init
id|zft_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
macro_line|#ifdef MODULE
id|printk
c_func
(paren
id|KERN_INFO
id|ZFTAPE_VERSION
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|TRACE_LEVEL
op_ge
id|ft_t_info
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;(c) 1996, 1997 Claus-Justus Heine (claus@momo.math.rwth-aachen.de)&bslash;n&quot;
id|KERN_INFO
l_string|&quot;vfs interface for ftape floppy tape driver.&bslash;n&quot;
id|KERN_INFO
l_string|&quot;Support for QIC-113 compatible volume table, dynamic memory allocation&bslash;n&quot;
id|KERN_INFO
l_string|&quot;and builtin compression (lzrw3 algorithm).&bslash;n&quot;
id|KERN_INFO
l_string|&quot;Compiled for Linux version %s&quot;
macro_line|#ifdef MODVERSIONS
l_string|&quot; with versioned symbols&quot;
macro_line|#endif
l_string|&quot;&bslash;n&quot;
comma
id|UTS_RELEASE
)paren
suffix:semicolon
)brace
macro_line|#else /* !MODULE */
multiline_comment|/* print a short no-nonsense boot message */
id|printk
c_func
(paren
id|KERN_INFO
id|ZFTAPE_VERSION
l_string|&quot; for Linux &quot;
id|UTS_RELEASE
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif /* MODULE */
id|TRACE
c_func
(paren
id|ft_t_info
comma
l_string|&quot;zft_init @ 0x%p&quot;
comma
id|zft_init
)paren
suffix:semicolon
id|TRACE
c_func
(paren
id|ft_t_info
comma
l_string|&quot;installing zftape VFS interface for ftape driver ...&quot;
)paren
suffix:semicolon
id|TRACE_CATCH
c_func
(paren
id|register_chrdev
c_func
(paren
id|QIC117_TAPE_MAJOR
comma
l_string|&quot;zft&quot;
comma
op_amp
id|zft_cdev
)paren
comma
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
id|devname
(braket
l_int|9
)braket
suffix:semicolon
id|sprintf
(paren
id|devname
comma
l_string|&quot;qft%i&quot;
comma
id|i
)paren
suffix:semicolon
id|devfs_register
(paren
l_int|NULL
comma
id|devname
comma
id|DEVFS_FL_DEFAULT
comma
id|QIC117_TAPE_MAJOR
comma
id|i
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
op_amp
id|zft_cdev
comma
l_int|NULL
)paren
suffix:semicolon
id|sprintf
(paren
id|devname
comma
l_string|&quot;nqft%i&quot;
comma
id|i
)paren
suffix:semicolon
id|devfs_register
(paren
l_int|NULL
comma
id|devname
comma
id|DEVFS_FL_DEFAULT
comma
id|QIC117_TAPE_MAJOR
comma
id|i
op_plus
l_int|4
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
op_amp
id|zft_cdev
comma
l_int|NULL
)paren
suffix:semicolon
id|sprintf
(paren
id|devname
comma
l_string|&quot;zqft%i&quot;
comma
id|i
)paren
suffix:semicolon
id|devfs_register
(paren
l_int|NULL
comma
id|devname
comma
id|DEVFS_FL_DEFAULT
comma
id|QIC117_TAPE_MAJOR
comma
id|i
op_plus
l_int|16
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
op_amp
id|zft_cdev
comma
l_int|NULL
)paren
suffix:semicolon
id|sprintf
(paren
id|devname
comma
l_string|&quot;nzqft%i&quot;
comma
id|i
)paren
suffix:semicolon
id|devfs_register
(paren
l_int|NULL
comma
id|devname
comma
id|DEVFS_FL_DEFAULT
comma
id|QIC117_TAPE_MAJOR
comma
id|i
op_plus
l_int|20
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
op_amp
id|zft_cdev
comma
l_int|NULL
)paren
suffix:semicolon
id|sprintf
(paren
id|devname
comma
l_string|&quot;rawqft%i&quot;
comma
id|i
)paren
suffix:semicolon
id|devfs_register
(paren
l_int|NULL
comma
id|devname
comma
id|DEVFS_FL_DEFAULT
comma
id|QIC117_TAPE_MAJOR
comma
id|i
op_plus
l_int|32
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
op_amp
id|zft_cdev
comma
l_int|NULL
)paren
suffix:semicolon
id|sprintf
(paren
id|devname
comma
l_string|&quot;nrawqft%i&quot;
comma
id|i
)paren
suffix:semicolon
id|devfs_register
(paren
l_int|NULL
comma
id|devname
comma
id|DEVFS_FL_DEFAULT
comma
id|QIC117_TAPE_MAJOR
comma
id|i
op_plus
l_int|36
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
op_amp
id|zft_cdev
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ZFT_COMPRESSOR
(paren
r_void
)paren
id|zft_compressor_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|zft_status
op_assign
id|ftape_get_status
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*  fetch global data of ftape &n;&t;&t;&t;&t;&t;  *  hardware driver &n;&t;&t;&t;&t;&t;  */
id|TRACE_EXIT
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Called by modules package when removing the driver &n; */
DECL|function|zft_exit
r_static
r_void
id|zft_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unregister_chrdev
c_func
(paren
id|QIC117_TAPE_MAJOR
comma
l_string|&quot;zft&quot;
)paren
op_ne
l_int|0
)paren
(brace
id|TRACE
c_func
(paren
id|ft_t_warn
comma
l_string|&quot;failed&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|TRACE
c_func
(paren
id|ft_t_info
comma
l_string|&quot;successful&quot;
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|devfs_remove
c_func
(paren
l_string|&quot;qft%i&quot;
comma
id|i
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;nqft%i&quot;
comma
id|i
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;zqft%i&quot;
comma
id|i
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;nzqft%i&quot;
comma
id|i
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;rawqft%i&quot;
comma
id|i
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;nrawqft%i&quot;
comma
id|i
)paren
suffix:semicolon
)brace
id|zft_uninit_mem
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* release remaining memory, if any */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;zftape successfully unloaded.&bslash;n&quot;
)paren
suffix:semicolon
id|TRACE_EXIT
suffix:semicolon
)brace
DECL|variable|zft_init
id|module_init
c_func
(paren
id|zft_init
)paren
suffix:semicolon
DECL|variable|zft_exit
id|module_exit
c_func
(paren
id|zft_exit
)paren
suffix:semicolon
eof
