multiline_comment|/*&n; * Copyright (c) 2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
multiline_comment|/*&n; * Written by Steve Lord at SGI&n; */
macro_line|#ifndef __PAGE_BUF_PRIVATE_H__
DECL|macro|__PAGE_BUF_PRIVATE_H__
mdefine_line|#define __PAGE_BUF_PRIVATE_H__
macro_line|#include &quot;page_buf.h&quot;
DECL|macro|_PAGE_BUF_INTERNAL_
mdefine_line|#define _PAGE_BUF_INTERNAL_
DECL|macro|PB_DEFINE_TRACES
mdefine_line|#define PB_DEFINE_TRACES
macro_line|#include &quot;page_buf_trace.h&quot;
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,9)
DECL|macro|page_buffers
mdefine_line|#define page_buffers(page)&t;((page)-&gt;buffers)
DECL|macro|page_has_buffers
mdefine_line|#define page_has_buffers(page)&t;((page)-&gt;buffers)
macro_line|#endif
DECL|struct|page_buf_private_s
r_typedef
r_struct
id|page_buf_private_s
(brace
DECL|member|pb_common
id|page_buf_t
id|pb_common
suffix:semicolon
multiline_comment|/* public part of structure */
DECL|member|pb_sema
r_struct
id|semaphore
id|pb_sema
suffix:semicolon
multiline_comment|/* semaphore for lockables  */
DECL|member|pb_flushtime
r_int
r_int
id|pb_flushtime
suffix:semicolon
multiline_comment|/* time to flush pagebuf    */
DECL|member|pb_io_remaining
id|atomic_t
id|pb_io_remaining
suffix:semicolon
multiline_comment|/* #outstanding I/O requests */
DECL|member|pb_pin_count
id|atomic_t
id|pb_pin_count
suffix:semicolon
multiline_comment|/* pin count&t;&t;    */
DECL|member|pb_waiters
id|wait_queue_head_t
id|pb_waiters
suffix:semicolon
multiline_comment|/* unpin waiters&t;    */
macro_line|#ifdef PAGEBUF_LOCK_TRACKING
DECL|member|pb_last_holder
r_int
id|pb_last_holder
suffix:semicolon
macro_line|#endif
DECL|typedef|page_buf_private_t
)brace
id|page_buf_private_t
suffix:semicolon
DECL|macro|PBC
mdefine_line|#define PBC(pb) (&amp;((pb)-&gt;pb_common))
DECL|macro|PBP
mdefine_line|#define PBP(pb) ((page_buf_private_t *) (pb))
macro_line|#ifdef PAGEBUF_LOCK_TRACKING
DECL|macro|PB_SET_OWNER
mdefine_line|#define PB_SET_OWNER(pb)&t;(PBP(pb)-&gt;pb_last_holder = current-&gt;pid)
DECL|macro|PB_CLEAR_OWNER
mdefine_line|#define PB_CLEAR_OWNER(pb)&t;(PBP(pb)-&gt;pb_last_holder = -1)
DECL|macro|PB_GET_OWNER
mdefine_line|#define PB_GET_OWNER(pb)&t;(PBP(pb)-&gt;pb_last_holder)
macro_line|#else
DECL|macro|PB_SET_OWNER
mdefine_line|#define PB_SET_OWNER(pb)
DECL|macro|PB_CLEAR_OWNER
mdefine_line|#define PB_CLEAR_OWNER(pb)
DECL|macro|PB_GET_OWNER
mdefine_line|#define PB_GET_OWNER(pb)
macro_line|#endif /* PAGEBUF_LOCK_TRACKING */
multiline_comment|/* Tracing utilities for pagebuf */
r_typedef
r_struct
(brace
DECL|member|event
r_int
id|event
suffix:semicolon
DECL|member|pb
r_int
r_int
id|pb
suffix:semicolon
DECL|member|flags
id|page_buf_flags_t
id|flags
suffix:semicolon
DECL|member|hold
r_int
r_int
id|hold
suffix:semicolon
DECL|member|lock_value
r_int
r_int
id|lock_value
suffix:semicolon
DECL|member|task
r_void
op_star
id|task
suffix:semicolon
DECL|member|misc
r_void
op_star
id|misc
suffix:semicolon
DECL|member|ra
r_void
op_star
id|ra
suffix:semicolon
DECL|member|offset
id|loff_t
id|offset
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|typedef|pagebuf_trace_t
)brace
id|pagebuf_trace_t
suffix:semicolon
DECL|struct|pagebuf_trace_buf
r_struct
id|pagebuf_trace_buf
(brace
DECL|member|buf
id|pagebuf_trace_t
op_star
id|buf
suffix:semicolon
DECL|member|start
r_volatile
r_int
id|start
suffix:semicolon
DECL|member|end
r_volatile
r_int
id|end
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PB_TRACE_BUFSIZE
mdefine_line|#define PB_TRACE_BUFSIZE&t;1024
DECL|macro|CIRC_INC
mdefine_line|#define CIRC_INC(i)&t;(((i) + 1) &amp; (PB_TRACE_BUFSIZE - 1))
DECL|struct|pagebuf_daemon
r_typedef
r_struct
id|pagebuf_daemon
(brace
DECL|member|active
r_int
id|active
suffix:semicolon
DECL|member|io_active
r_int
id|io_active
suffix:semicolon
DECL|member|pb_delwrite_lock
id|spinlock_t
id|pb_delwrite_lock
suffix:semicolon
DECL|member|pb_delwrite_l
r_struct
id|list_head
id|pb_delwrite_l
suffix:semicolon
DECL|member|pb_delwri_cnt
r_int
id|pb_delwri_cnt
suffix:semicolon
DECL|typedef|pagebuf_daemon_t
)brace
id|pagebuf_daemon_t
suffix:semicolon
multiline_comment|/*&n; * Tunable pagebuf parameters&n; */
DECL|macro|P_PARAM
mdefine_line|#define P_PARAM 4
DECL|union|pagebuf_param
r_typedef
r_union
id|pagebuf_param
(brace
r_struct
(brace
DECL|member|flush_interval
id|ulong
id|flush_interval
suffix:semicolon
multiline_comment|/* interval between runs of the&n;&t;&t;&t;&t;&t; * delwri flush daemon.&t; */
DECL|member|age_buffer
id|ulong
id|age_buffer
suffix:semicolon
multiline_comment|/* time for buffer to age before&n;&t;&t;&t;&t;&t; * we flush it.&t; */
DECL|member|debug
id|ulong
id|debug
suffix:semicolon
multiline_comment|/* debug tracing on or off */
DECL|member|stats_clear
id|ulong
id|stats_clear
suffix:semicolon
multiline_comment|/* clear the pagebuf stats */
DECL|member|p_un
)brace
id|p_un
suffix:semicolon
DECL|member|data
id|ulong
id|data
(braket
id|P_PARAM
)braket
suffix:semicolon
DECL|typedef|pagebuf_param_t
)brace
id|pagebuf_param_t
suffix:semicolon
r_enum
(brace
DECL|enumerator|PB_FLUSH_INT
id|PB_FLUSH_INT
op_assign
l_int|1
comma
DECL|enumerator|PB_FLUSH_AGE
id|PB_FLUSH_AGE
op_assign
l_int|2
comma
DECL|enumerator|PB_STATS_CLEAR
id|PB_STATS_CLEAR
op_assign
l_int|3
comma
DECL|enumerator|PB_DEBUG
id|PB_DEBUG
op_assign
l_int|4
)brace
suffix:semicolon
r_extern
id|pagebuf_param_t
id|pb_params
suffix:semicolon
multiline_comment|/*&n; * Pagebuf statistics&n; */
DECL|struct|pbstats
r_struct
id|pbstats
(brace
DECL|member|pb_get
id|u_int32_t
id|pb_get
suffix:semicolon
DECL|member|pb_create
id|u_int32_t
id|pb_create
suffix:semicolon
DECL|member|pb_get_locked
id|u_int32_t
id|pb_get_locked
suffix:semicolon
DECL|member|pb_get_locked_waited
id|u_int32_t
id|pb_get_locked_waited
suffix:semicolon
DECL|member|pb_busy_locked
id|u_int32_t
id|pb_busy_locked
suffix:semicolon
DECL|member|pb_miss_locked
id|u_int32_t
id|pb_miss_locked
suffix:semicolon
DECL|member|pb_page_retries
id|u_int32_t
id|pb_page_retries
suffix:semicolon
DECL|member|pb_page_found
id|u_int32_t
id|pb_page_found
suffix:semicolon
DECL|member|pb_get_read
id|u_int32_t
id|pb_get_read
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|pbstats
id|pbstats
suffix:semicolon
DECL|macro|PB_STATS_INC
mdefine_line|#define PB_STATS_INC(count)&t;( count ++ )
DECL|macro|assert
macro_line|#undef assert
macro_line|#ifdef PAGEBUF_DEBUG
DECL|macro|assert
macro_line|# define assert(expr) &bslash;&n;&t;if (!(expr)) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;printk(&quot;Assertion failed: %s&bslash;n%s::%s line %d&bslash;n&quot;,&bslash;&n;&t;&t;#expr,__FILE__,__FUNCTION__,__LINE__);&t;&t;&bslash;&n;&t;&t;BUG();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}
macro_line|#else
DECL|macro|assert
macro_line|# define assert(x)&t;do { } while (0)
macro_line|#endif
macro_line|#ifndef STATIC
DECL|macro|STATIC
macro_line|# define STATIC static
macro_line|#endif
macro_line|#endif /* __PAGE_BUF_PRIVATE_H__ */
eof