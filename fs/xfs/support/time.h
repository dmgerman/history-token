multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_SUPPORT_TIME_H__
DECL|macro|__XFS_SUPPORT_TIME_H__
mdefine_line|#define __XFS_SUPPORT_TIME_H__
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/time.h&gt;
DECL|function|delay
r_static
r_inline
r_void
id|delay
c_func
(paren
r_int
id|ticks
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|ticks
)paren
suffix:semicolon
)brace
DECL|function|nanotime
r_static
r_inline
r_void
id|nanotime
c_func
(paren
r_struct
id|timespec
op_star
id|tvp
)paren
(brace
r_struct
id|timeval
id|tv
suffix:semicolon
id|do_gettimeofday
c_func
(paren
op_amp
id|tv
)paren
suffix:semicolon
id|tvp-&gt;tv_sec
op_assign
id|tv.tv_sec
suffix:semicolon
id|tvp-&gt;tv_nsec
op_assign
id|tv.tv_usec
op_star
l_int|1000
suffix:semicolon
)brace
macro_line|#endif /* __XFS_SUPPORT_TIME_H__ */
eof
