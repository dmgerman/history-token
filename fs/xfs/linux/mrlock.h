multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_SUPPORT_MRLOCK_H__
DECL|macro|__XFS_SUPPORT_MRLOCK_H__
mdefine_line|#define __XFS_SUPPORT_MRLOCK_H__
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
multiline_comment|/*&n; * Implement mrlocks on Linux that work for XFS.&n; *&n; * These are sleep locks and not spinlocks. If one wants read/write spinlocks,&n; * use read_lock, write_lock, ... see spinlock.h.&n; */
DECL|struct|mrlock_s
r_typedef
r_struct
id|mrlock_s
(brace
DECL|member|mr_count
r_int
id|mr_count
suffix:semicolon
DECL|member|mr_reads_waiting
r_int
r_int
id|mr_reads_waiting
suffix:semicolon
DECL|member|mr_writes_waiting
r_int
r_int
id|mr_writes_waiting
suffix:semicolon
DECL|member|mr_readerq
id|wait_queue_head_t
id|mr_readerq
suffix:semicolon
DECL|member|mr_writerq
id|wait_queue_head_t
id|mr_writerq
suffix:semicolon
DECL|member|mr_lock
id|spinlock_t
id|mr_lock
suffix:semicolon
DECL|typedef|mrlock_t
)brace
id|mrlock_t
suffix:semicolon
DECL|macro|MR_ACCESS
mdefine_line|#define MR_ACCESS&t;1
DECL|macro|MR_UPDATE
mdefine_line|#define MR_UPDATE&t;2
DECL|macro|MRLOCK_BARRIER
mdefine_line|#define MRLOCK_BARRIER&t;&t;0x1
DECL|macro|MRLOCK_ALLOW_EQUAL_PRI
mdefine_line|#define MRLOCK_ALLOW_EQUAL_PRI&t;0x8
multiline_comment|/*&n; * mraccessf/mrupdatef take flags to be passed in while sleeping;&n; * only PLTWAIT is currently supported.&n; */
r_extern
r_void
id|mraccessf
c_func
(paren
id|mrlock_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|mrupdatef
c_func
(paren
id|mrlock_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|mrlock
c_func
(paren
id|mrlock_t
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|mrunlock
c_func
(paren
id|mrlock_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|mraccunlock
c_func
(paren
id|mrlock_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|mrtryupdate
c_func
(paren
id|mrlock_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|mrtryaccess
c_func
(paren
id|mrlock_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|mrtrypromote
c_func
(paren
id|mrlock_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|mrdemote
c_func
(paren
id|mrlock_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ismrlocked
c_func
(paren
id|mrlock_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|mrlock_init
c_func
(paren
id|mrlock_t
op_star
comma
r_int
id|type
comma
r_char
op_star
id|name
comma
r_int
id|sequence
)paren
suffix:semicolon
r_extern
r_void
id|mrfree
c_func
(paren
id|mrlock_t
op_star
)paren
suffix:semicolon
DECL|macro|mrinit
mdefine_line|#define mrinit(mrp, name)&t;mrlock_init(mrp, MRLOCK_BARRIER, name, -1)
DECL|macro|mraccess
mdefine_line|#define mraccess(mrp)&t;&t;mraccessf(mrp, 0) /* grab for READ/ACCESS */
DECL|macro|mrupdate
mdefine_line|#define mrupdate(mrp)&t;&t;mrupdatef(mrp, 0) /* grab for WRITE/UPDATE */
DECL|macro|mrislocked_access
mdefine_line|#define mrislocked_access(mrp)&t;((mrp)-&gt;mr_count &gt; 0)
DECL|macro|mrislocked_update
mdefine_line|#define mrislocked_update(mrp)&t;((mrp)-&gt;mr_count &lt; 0)
macro_line|#endif /* __XFS_SUPPORT_MRLOCK_H__ */
eof
