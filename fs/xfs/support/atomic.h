multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_SUPPORT_ATOMIC_H__
DECL|macro|__XFS_SUPPORT_ATOMIC_H__
mdefine_line|#define __XFS_SUPPORT_ATOMIC_H__
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
multiline_comment|/*&n; * This is used for two variables in XFS, one of which is a debug trace&n; * buffer index. They are not accessed via any other atomic operations&n; * so this is safe. All other atomic increments and decrements in XFS&n; * now use the linux built in functions.&n; */
r_extern
id|spinlock_t
id|Atomic_spin
suffix:semicolon
DECL|function|atomicIncWithWrap
r_static
id|__inline__
r_int
id|atomicIncWithWrap
c_func
(paren
r_int
op_star
id|ip
comma
r_int
id|val
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|Atomic_spin
comma
id|flags
)paren
suffix:semicolon
id|ret
op_assign
op_star
id|ip
suffix:semicolon
(paren
op_star
id|ip
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ip
op_eq
id|val
)paren
op_star
id|ip
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|Atomic_spin
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif /* __XFS_SUPPORT_ATOMIC_H__ */
eof
