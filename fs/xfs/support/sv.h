multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; * Portions Copyright (c) 2002 Christoph Hellwig.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_SUPPORT_SV_H__
DECL|macro|__XFS_SUPPORT_SV_H__
mdefine_line|#define __XFS_SUPPORT_SV_H__
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
multiline_comment|/*&n; * Synchronisation variables.&n; *&n; * (Parameters &quot;pri&quot;, &quot;svf&quot; and &quot;rts&quot; are not implemented)&n; */
DECL|struct|sv_s
r_typedef
r_struct
id|sv_s
(brace
DECL|member|waiters
id|wait_queue_head_t
id|waiters
suffix:semicolon
DECL|typedef|sv_t
)brace
id|sv_t
suffix:semicolon
DECL|macro|SV_FIFO
mdefine_line|#define SV_FIFO&t;&t;0x0&t;&t;/* sv_t is FIFO type */
DECL|macro|SV_LIFO
mdefine_line|#define SV_LIFO&t;&t;0x2&t;&t;/* sv_t is LIFO type */
DECL|macro|SV_PRIO
mdefine_line|#define SV_PRIO&t;&t;0x4&t;&t;/* sv_t is PRIO type */
DECL|macro|SV_KEYED
mdefine_line|#define SV_KEYED&t;0x6&t;&t;/* sv_t is KEYED type */
DECL|macro|SV_DEFAULT
mdefine_line|#define SV_DEFAULT&t;SV_FIFO
DECL|function|_sv_wait
r_static
r_inline
r_void
id|_sv_wait
c_func
(paren
id|sv_t
op_star
id|sv
comma
id|spinlock_t
op_star
id|lock
comma
r_int
id|state
comma
r_int
r_int
id|timeout
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|add_wait_queue_exclusive
c_func
(paren
op_amp
id|sv-&gt;waiters
comma
op_amp
id|wait
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|state
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
id|lock
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|timeout
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|sv-&gt;waiters
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
DECL|macro|init_sv
mdefine_line|#define init_sv(sv,type,name,flag) &bslash;&n;&t;init_waitqueue_head(&amp;(sv)-&gt;waiters)
DECL|macro|sv_init
mdefine_line|#define sv_init(sv,flag,name) &bslash;&n;&t;init_waitqueue_head(&amp;(sv)-&gt;waiters)
DECL|macro|sv_destroy
mdefine_line|#define sv_destroy(sv) &bslash;&n;&t;/*NOTHING*/
DECL|macro|sv_wait
mdefine_line|#define sv_wait(sv, pri, lock, s) &bslash;&n;&t;_sv_wait(sv, lock, TASK_UNINTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT)
DECL|macro|sv_wait_sig
mdefine_line|#define sv_wait_sig(sv, pri, lock, s)&t;&bslash;&n;&t;_sv_wait(sv, lock, TASK_INTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT)
DECL|macro|sv_timedwait
mdefine_line|#define sv_timedwait(sv, pri, lock, s, svf, ts, rts) &bslash;&n;&t;_sv_wait(sv, lock, TASK_UNINTERRUPTIBLE, timespec_to_jiffies(ts))
DECL|macro|sv_timedwait_sig
mdefine_line|#define sv_timedwait_sig(sv, pri, lock, s, svf, ts, rts) &bslash;&n;&t;_sv_wait(sv, lock, TASK_INTERRUPTIBLE, timespec_to_jiffies(ts))
DECL|macro|sv_signal
mdefine_line|#define sv_signal(sv) &bslash;&n;&t;wake_up(&amp;(sv)-&gt;waiters)
DECL|macro|sv_broadcast
mdefine_line|#define sv_broadcast(sv) &bslash;&n;&t;wake_up_all(&amp;(sv)-&gt;waiters)
macro_line|#endif /* __XFS_SUPPORT_SV_H__ */
eof
