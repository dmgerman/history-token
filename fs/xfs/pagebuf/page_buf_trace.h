multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __PAGEBUF_TRACE__
DECL|macro|__PAGEBUF_TRACE__
mdefine_line|#define __PAGEBUF_TRACE__
macro_line|#ifdef PB_DEFINE_TRACES
DECL|macro|PB_TRACE_START
mdefine_line|#define PB_TRACE_START&t;typedef enum {
DECL|macro|PB_TRACE_REC
mdefine_line|#define PB_TRACE_REC(x) pb_trace_point_##x
DECL|macro|PB_TRACE_END
mdefine_line|#define PB_TRACE_END&t;} pb_trace_var_t;
macro_line|#else
DECL|macro|PB_TRACE_START
mdefine_line|#define PB_TRACE_START&t;static char&t;*event_names[] = {
DECL|macro|PB_TRACE_REC
mdefine_line|#define PB_TRACE_REC(x) #x
DECL|macro|PB_TRACE_END
mdefine_line|#define PB_TRACE_END&t;};
macro_line|#endif
id|PB_TRACE_START
id|PB_TRACE_REC
c_func
(paren
id|get
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|get_obj
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|free_obj
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|look_pg
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|get_read
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|no_daddr
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|hold
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|rele
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|done
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|ioerror
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|iostart
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|end_io
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|do_io
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|ioreq
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|iowait
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|iowaited
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|free_lk
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|freed_l
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|cmp
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|get_lk
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|got_lk
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|skip
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|lock
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|locked
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|unlock
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|avl_ret
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|condlck
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|avl_ins
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|walkq1
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|walkq2
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|walkq3
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|delwri_q
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|delwri_uq
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|pin
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|unpin
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|file_write
)paren
comma
id|PB_TRACE_REC
c_func
(paren
id|external
)paren
comma
id|PB_TRACE_END
r_extern
r_void
id|pb_trace_func
c_func
(paren
id|page_buf_t
op_star
comma
r_int
comma
r_void
op_star
comma
r_void
op_star
)paren
suffix:semicolon
macro_line|#ifdef PAGEBUF_TRACE
DECL|macro|PB_TRACE
macro_line|# define PB_TRACE(pb, event, misc)&t;&t;&bslash;&n;&t;pb_trace_func(pb, event, (void *) misc, &bslash;&n;&t;&t;&t;(void *)__builtin_return_address(0))
macro_line|#else
DECL|macro|PB_TRACE
macro_line|# define PB_TRACE(pb, event, misc)&t;do { } while (0)
macro_line|#endif
macro_line|#endif&t;/* __PAGEBUF_TRACE__ */
eof
