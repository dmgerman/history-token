multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_SUPPORT_SEMA_H__
DECL|macro|__XFS_SUPPORT_SEMA_H__
mdefine_line|#define __XFS_SUPPORT_SEMA_H__
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
multiline_comment|/*&n; * sema_t structure just maps to struct semaphore in Linux kernel.&n; */
DECL|typedef|sema_t
r_typedef
r_struct
id|semaphore
id|sema_t
suffix:semicolon
DECL|macro|init_sema
mdefine_line|#define init_sema(sp, val, c, d)&t;sema_init(sp, val)
DECL|macro|initsema
mdefine_line|#define initsema(sp, val)&t;&t;sema_init(sp, val)
DECL|macro|initnsema
mdefine_line|#define initnsema(sp, val, name)&t;sema_init(sp, val)
DECL|macro|psema
mdefine_line|#define psema(sp, b)&t;&t;&t;down(sp)
DECL|macro|vsema
mdefine_line|#define vsema(sp)&t;&t;&t;up(sp)
DECL|macro|valusema
mdefine_line|#define valusema(sp)&t;&t;&t;(atomic_read(&amp;(sp)-&gt;count))
DECL|macro|freesema
mdefine_line|#define freesema(sema)
multiline_comment|/*&n; * Map cpsema (try to get the sema) to down_trylock. We need to switch&n; * the return values since cpsema returns 1 (acquired) 0 (failed) and&n; * down_trylock returns the reverse 0 (acquired) 1 (failed).&n; */
DECL|macro|cpsema
mdefine_line|#define cpsema(sp)&t;&t;&t;(down_trylock(sp) ? 0 : 1)
multiline_comment|/*&n; * Didn&squot;t do cvsema(sp). Not sure how to map this to up/down/...&n; * It does a vsema if the values is &lt; 0 other wise nothing.&n; */
macro_line|#endif /* __XFS_SUPPORT_SEMA_H__ */
eof
