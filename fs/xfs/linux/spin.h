multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_SUPPORT_SPIN_H__
DECL|macro|__XFS_SUPPORT_SPIN_H__
mdefine_line|#define __XFS_SUPPORT_SPIN_H__
macro_line|#include &lt;linux/sched.h&gt;&t;/* preempt needs this */
macro_line|#include &lt;linux/spinlock.h&gt;
multiline_comment|/*&n; * Map lock_t from IRIX to Linux spinlocks.&n; *&n; * We do not make use of lock_t from interrupt context, so we do not&n; * have to worry about disabling interrupts at all (unlike IRIX).&n; */
DECL|typedef|lock_t
r_typedef
id|spinlock_t
id|lock_t
suffix:semicolon
DECL|macro|SPLDECL
mdefine_line|#define SPLDECL(s)&t;&t;&t;unsigned long s
DECL|macro|spinlock_init
mdefine_line|#define spinlock_init(lock, name)&t;spin_lock_init(lock)
DECL|macro|spinlock_destroy
mdefine_line|#define&t;spinlock_destroy(lock)
DECL|macro|mutex_spinlock
mdefine_line|#define mutex_spinlock(lock)&t;&t;({ spin_lock(lock); 0; })
DECL|macro|mutex_spinunlock
mdefine_line|#define mutex_spinunlock(lock, s)&t;spin_unlock(lock)
DECL|macro|nested_spinlock
mdefine_line|#define nested_spinlock(lock)&t;&t;spin_lock(lock)
DECL|macro|nested_spinunlock
mdefine_line|#define nested_spinunlock(lock)&t;&t;spin_unlock(lock)
macro_line|#endif /* __XFS_SUPPORT_SPIN_H__ */
eof
