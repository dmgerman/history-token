multiline_comment|/*&n; *&n; * dvb_ringbuffer.c: ring buffer implementation for the dvb driver&n; *&n; * Copyright (C) 2003 Oliver Endriss &n; * &n; * based on code originally found in av7110.c:&n; * Copyright (C) 1999-2002 Ralph  Metzler &n; *                       &amp; Marcus Metzler for convergence integrated media GmbH&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; * &n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; * Or, point your browser to http://www.gnu.org/copyleft/gpl.html&n; * &n; *&n; * the project&squot;s page is at http://www.linuxtv.org/dvb/&n; */
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;dvb_ringbuffer.h&quot;
DECL|function|dvb_ringbuffer_init
r_void
id|dvb_ringbuffer_init
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
comma
r_void
op_star
id|data
comma
r_int
id|len
)paren
(brace
id|rbuf-&gt;pread
op_assign
id|rbuf-&gt;pwrite
op_assign
l_int|0
suffix:semicolon
id|rbuf-&gt;data
op_assign
id|data
suffix:semicolon
id|rbuf-&gt;size
op_assign
id|len
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|rbuf-&gt;queue
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
(paren
id|rbuf-&gt;lock
)paren
)paren
suffix:semicolon
)brace
DECL|function|dvb_ringbuffer_empty
r_int
id|dvb_ringbuffer_empty
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
)paren
(brace
r_return
(paren
id|rbuf-&gt;pread
op_eq
id|rbuf-&gt;pwrite
)paren
suffix:semicolon
)brace
DECL|function|dvb_ringbuffer_free
id|ssize_t
id|dvb_ringbuffer_free
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
)paren
(brace
id|ssize_t
id|free
suffix:semicolon
id|free
op_assign
id|rbuf-&gt;pread
op_minus
id|rbuf-&gt;pwrite
suffix:semicolon
r_if
c_cond
(paren
id|free
op_le
l_int|0
)paren
id|free
op_add_assign
id|rbuf-&gt;size
suffix:semicolon
r_return
id|free
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|dvb_ringbuffer_avail
id|ssize_t
id|dvb_ringbuffer_avail
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
)paren
(brace
id|ssize_t
id|avail
suffix:semicolon
id|avail
op_assign
id|rbuf-&gt;pwrite
op_minus
id|rbuf-&gt;pread
suffix:semicolon
r_if
c_cond
(paren
id|avail
OL
l_int|0
)paren
id|avail
op_add_assign
id|rbuf-&gt;size
suffix:semicolon
r_return
id|avail
suffix:semicolon
)brace
DECL|function|dvb_ringbuffer_flush
r_void
id|dvb_ringbuffer_flush
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
)paren
(brace
id|rbuf-&gt;pread
op_assign
id|rbuf-&gt;pwrite
suffix:semicolon
)brace
DECL|function|dvb_ringbuffer_flush_spinlock_wakeup
r_void
id|dvb_ringbuffer_flush_spinlock_wakeup
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rbuf-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|dvb_ringbuffer_flush
c_func
(paren
id|rbuf
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rbuf-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|rbuf-&gt;queue
)paren
suffix:semicolon
)brace
DECL|function|dvb_ringbuffer_read
id|ssize_t
id|dvb_ringbuffer_read
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
comma
id|u8
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|usermem
)paren
(brace
r_int
id|todo
op_assign
id|len
suffix:semicolon
r_int
id|split
suffix:semicolon
id|split
op_assign
(paren
id|rbuf-&gt;pread
op_plus
id|len
OG
id|rbuf-&gt;size
)paren
ques
c_cond
id|rbuf-&gt;size
op_minus
id|rbuf-&gt;pread
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|split
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|usermem
)paren
id|memcpy
c_func
(paren
id|buf
comma
id|rbuf-&gt;data
op_plus
id|rbuf-&gt;pread
comma
id|split
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|rbuf-&gt;data
op_plus
id|rbuf-&gt;pread
comma
id|split
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|buf
op_add_assign
id|split
suffix:semicolon
id|todo
op_sub_assign
id|split
suffix:semicolon
id|rbuf-&gt;pread
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|usermem
)paren
id|memcpy
c_func
(paren
id|buf
comma
id|rbuf-&gt;data
op_plus
id|rbuf-&gt;pread
comma
id|todo
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|rbuf-&gt;data
op_plus
id|rbuf-&gt;pread
comma
id|todo
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|rbuf-&gt;pread
op_assign
(paren
id|rbuf-&gt;pread
op_plus
id|len
)paren
op_mod
id|rbuf-&gt;size
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|dvb_ringbuffer_write
id|ssize_t
id|dvb_ringbuffer_write
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
comma
r_const
id|u8
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|usermem
)paren
(brace
r_int
id|todo
op_assign
id|len
suffix:semicolon
r_int
id|split
suffix:semicolon
id|split
op_assign
(paren
id|rbuf-&gt;pwrite
op_plus
id|len
OG
id|rbuf-&gt;size
)paren
ques
c_cond
id|rbuf-&gt;size
op_minus
id|rbuf-&gt;pwrite
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|split
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|usermem
)paren
id|memcpy
c_func
(paren
id|rbuf-&gt;data
op_plus
id|rbuf-&gt;pwrite
comma
id|buf
comma
id|split
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|rbuf-&gt;data
op_plus
id|rbuf-&gt;pwrite
comma
id|buf
comma
id|split
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|buf
op_add_assign
id|split
suffix:semicolon
id|todo
op_sub_assign
id|split
suffix:semicolon
id|rbuf-&gt;pwrite
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|usermem
)paren
id|memcpy
c_func
(paren
id|rbuf-&gt;data
op_plus
id|rbuf-&gt;pwrite
comma
id|buf
comma
id|todo
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|rbuf-&gt;data
op_plus
id|rbuf-&gt;pwrite
comma
id|buf
comma
id|todo
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|rbuf-&gt;pwrite
op_assign
(paren
id|rbuf-&gt;pwrite
op_plus
id|len
)paren
op_mod
id|rbuf-&gt;size
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|variable|dvb_ringbuffer_init
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|dvb_ringbuffer_init
)paren
suffix:semicolon
DECL|variable|dvb_ringbuffer_empty
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|dvb_ringbuffer_empty
)paren
suffix:semicolon
DECL|variable|dvb_ringbuffer_free
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|dvb_ringbuffer_free
)paren
suffix:semicolon
DECL|variable|dvb_ringbuffer_avail
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|dvb_ringbuffer_avail
)paren
suffix:semicolon
DECL|variable|dvb_ringbuffer_flush
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|dvb_ringbuffer_flush
)paren
suffix:semicolon
DECL|variable|dvb_ringbuffer_flush_spinlock_wakeup
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|dvb_ringbuffer_flush_spinlock_wakeup
)paren
suffix:semicolon
DECL|variable|dvb_ringbuffer_read
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|dvb_ringbuffer_read
)paren
suffix:semicolon
DECL|variable|dvb_ringbuffer_write
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|dvb_ringbuffer_write
)paren
suffix:semicolon
eof
