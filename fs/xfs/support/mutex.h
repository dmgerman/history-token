multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; * Portions Copyright (c) 2002 Christoph Hellwig.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_SUPPORT_MUTEX_H__
DECL|macro|__XFS_SUPPORT_MUTEX_H__
mdefine_line|#define __XFS_SUPPORT_MUTEX_H__
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
multiline_comment|/*&n; * Map the mutex&squot;es from IRIX to Linux semaphores.&n; *&n; * Destroy just simply initializes to -99 which should block all other&n; * callers.&n; */
DECL|macro|MUTEX_DEFAULT
mdefine_line|#define MUTEX_DEFAULT&t;&t;0x0
DECL|typedef|mutex_t
r_typedef
r_struct
id|semaphore
id|mutex_t
suffix:semicolon
DECL|macro|mutex_init
mdefine_line|#define mutex_init(lock, type, name)&t;&t;sema_init(lock, 1)
DECL|macro|init_mutex
mdefine_line|#define init_mutex(ptr, type, name, sequence)&t;sema_init(lock, 1)
DECL|macro|mutex_destroy
mdefine_line|#define mutex_destroy(lock)&t;&t;&t;sema_init(lock, -99)
DECL|macro|mutex_lock
mdefine_line|#define mutex_lock(lock, num)&t;&t;&t;down(lock)
DECL|macro|mutex_trylock
mdefine_line|#define mutex_trylock(lock)&t;&t;&t;(down_trylock(lock) ? 0 : 1)
DECL|macro|mutex_unlock
mdefine_line|#define mutex_unlock(lock)&t;&t;&t;up(lock)
macro_line|#endif /* __XFS_SUPPORT_MUTEX_H__ */
eof
