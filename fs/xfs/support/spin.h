multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; * Portions Copyright (c) 2002 Christoph Hellwig.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_SUPPORT_SPIN_H__
DECL|macro|__XFS_SUPPORT_SPIN_H__
mdefine_line|#define __XFS_SUPPORT_SPIN_H__
macro_line|#include &lt;linux/sched.h&gt;&t;/* preempt needs this */
macro_line|#include &lt;linux/spinlock.h&gt;
multiline_comment|/*&n; * Map lock_t from IRIX to Linux spinlocks.&n; *&n; * Note that linux turns on/off spinlocks depending on CONFIG_SMP.&n; * We don&squot;t need to worry about SMP or not here.&n; */
DECL|typedef|lock_t
r_typedef
id|spinlock_t
id|lock_t
suffix:semicolon
DECL|macro|spinlock_init
mdefine_line|#define spinlock_init(lock, name)&t;spin_lock_init(lock)
DECL|macro|init_spinlock
mdefine_line|#define init_spinlock(lock, name, ll)&t;spin_lock_init(lock)
DECL|macro|spinlock_destroy
mdefine_line|#define spinlock_destroy(lock)
DECL|function|mutex_spinlock
r_static
r_inline
r_int
r_int
id|mutex_spinlock
c_func
(paren
id|lock_t
op_star
id|lock
)paren
(brace
id|spin_lock
c_func
(paren
id|lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*ARGSUSED*/
DECL|function|mutex_spinunlock
r_static
r_inline
r_void
id|mutex_spinunlock
c_func
(paren
id|lock_t
op_star
id|lock
comma
r_int
r_int
id|s
)paren
(brace
id|spin_unlock
c_func
(paren
id|lock
)paren
suffix:semicolon
)brace
DECL|function|nested_spinlock
r_static
r_inline
r_void
id|nested_spinlock
c_func
(paren
id|lock_t
op_star
id|lock
)paren
(brace
id|spin_lock
c_func
(paren
id|lock
)paren
suffix:semicolon
)brace
DECL|function|nested_spinunlock
r_static
r_inline
r_void
id|nested_spinunlock
c_func
(paren
id|lock_t
op_star
id|lock
)paren
(brace
id|spin_unlock
c_func
(paren
id|lock
)paren
suffix:semicolon
)brace
macro_line|#endif /* __XFS_SUPPORT_SPIN_H__ */
eof
