multiline_comment|/*&n;  * iSeries_proc.c&n;  * Copyright (C) 2001  Kyle A. Lucke IBM Corporation&n;  * &n;  * This program is free software; you can redistribute it and/or modify&n;  * it under the terms of the GNU General Public License as published by&n;  * the Free Software Foundation; either version 2 of the License, or&n;  * (at your option) any later version.&n;  * &n;  * This program is distributed in the hope that it will be useful,&n;  * but WITHOUT ANY WARRANTY; without even the implied warranty of&n;  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;  * GNU General Public License for more details.&n;  * &n;  * You should have received a copy of the GNU General Public License&n;  * along with this program; if not, write to the Free Software&n;  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n;  */
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/iSeries/iSeries_proc.h&gt;
DECL|variable|iSeries_proc_root
r_static
r_struct
id|proc_dir_entry
op_star
id|iSeries_proc_root
suffix:semicolon
DECL|variable|iSeries_proc_initializationDone
r_static
r_int
id|iSeries_proc_initializationDone
suffix:semicolon
DECL|variable|iSeries_proc_lock
r_static
id|spinlock_t
id|iSeries_proc_lock
suffix:semicolon
DECL|struct|iSeries_proc_registration
r_struct
id|iSeries_proc_registration
(brace
DECL|member|next
r_struct
id|iSeries_proc_registration
op_star
id|next
suffix:semicolon
DECL|member|functionMember
id|iSeriesProcFunction
id|functionMember
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|preallocated
r_struct
id|iSeries_proc_registration
id|preallocated
(braket
l_int|16
)braket
suffix:semicolon
DECL|macro|MYQUEUETYPE
mdefine_line|#define MYQUEUETYPE(T) struct MYQueue##T
DECL|macro|MYQUEUE
mdefine_line|#define MYQUEUE(T) &bslash;&n;MYQUEUETYPE(T) &bslash;&n;{ &bslash;&n;&t;struct T *head; &bslash;&n;&t;struct T *tail; &bslash;&n;}
DECL|macro|MYQUEUECTOR
mdefine_line|#define MYQUEUECTOR(q) do { (q)-&gt;head = NULL; (q)-&gt;tail = NULL; } while(0)
DECL|macro|MYQUEUEENQ
mdefine_line|#define MYQUEUEENQ(q, p) &bslash;&n;do { &bslash;&n;&t;(p)-&gt;next = NULL; &bslash;&n;&t;if ((q)-&gt;head != NULL) { &bslash;&n;&t;&t;(q)-&gt;head-&gt;next = (p); &bslash;&n;&t;&t;(q)-&gt;head = (p); &bslash;&n;&t;} else { &bslash;&n;&t;&t;(q)-&gt;tail = (q)-&gt;head = (p); &bslash;&n;&t;} &bslash;&n;} while(0)
DECL|macro|MYQUEUEDEQ
mdefine_line|#define MYQUEUEDEQ(q,p) &bslash;&n;do { &bslash;&n;&t;(p) = (q)-&gt;tail; &bslash;&n;&t;if ((p) != NULL) { &bslash;&n;&t;&t;(q)-&gt;tail = (p)-&gt;next; &bslash;&n;&t;&t;(p)-&gt;next = NULL; &bslash;&n;&t;} &bslash;&n;&t;if ((q)-&gt;tail == NULL) &bslash;&n;&t;&t;(q)-&gt;head = NULL; &bslash;&n;} while(0)
DECL|variable|iSeries_proc_registration
id|MYQUEUE
c_func
(paren
id|iSeries_proc_registration
)paren
suffix:semicolon
DECL|typedef|aQueue
r_typedef
id|MYQUEUETYPE
c_func
(paren
id|iSeries_proc_registration
)paren
id|aQueue
suffix:semicolon
DECL|variable|iSeries_free
r_static
id|aQueue
id|iSeries_free
suffix:semicolon
DECL|variable|iSeries_queued
r_static
id|aQueue
id|iSeries_queued
suffix:semicolon
DECL|function|iSeries_proc_early_init
r_void
id|iSeries_proc_early_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|iSeries_proc_initializationDone
op_assign
l_int|0
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|iSeries_proc_lock
)paren
suffix:semicolon
id|MYQUEUECTOR
c_func
(paren
op_amp
id|iSeries_free
)paren
suffix:semicolon
id|MYQUEUECTOR
c_func
(paren
op_amp
id|iSeries_queued
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iSeries_proc_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
op_increment
id|i
)paren
id|MYQUEUEENQ
c_func
(paren
op_amp
id|iSeries_free
comma
id|preallocated
op_plus
id|i
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iSeries_proc_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|iSeries_proc_create
r_static
r_int
id|iSeries_proc_create
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|iSeries_proc_registration
op_star
id|reg
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;iSeries_proc: Creating /proc/iSeries&bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iSeries_proc_lock
comma
id|flags
)paren
suffix:semicolon
id|iSeries_proc_root
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;iSeries&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iSeries_proc_root
)paren
r_goto
id|out
suffix:semicolon
id|MYQUEUEDEQ
c_func
(paren
op_amp
id|iSeries_queued
comma
id|reg
)paren
suffix:semicolon
r_while
c_loop
(paren
id|reg
op_ne
l_int|NULL
)paren
(brace
(paren
op_star
(paren
id|reg-&gt;functionMember
)paren
)paren
(paren
id|iSeries_proc_root
)paren
suffix:semicolon
id|MYQUEUEDEQ
c_func
(paren
op_amp
id|iSeries_queued
comma
id|reg
)paren
suffix:semicolon
)brace
id|iSeries_proc_initializationDone
op_assign
l_int|1
suffix:semicolon
id|out
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iSeries_proc_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|iSeries_proc_create
id|arch_initcall
c_func
(paren
id|iSeries_proc_create
)paren
suffix:semicolon
DECL|function|iSeries_proc_callback
r_void
id|iSeries_proc_callback
c_func
(paren
id|iSeriesProcFunction
id|initFunction
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iSeries_proc_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iSeries_proc_initializationDone
)paren
(paren
op_star
id|initFunction
)paren
(paren
id|iSeries_proc_root
)paren
suffix:semicolon
r_else
(brace
r_struct
id|iSeries_proc_registration
op_star
id|reg
op_assign
l_int|NULL
suffix:semicolon
id|MYQUEUEDEQ
c_func
(paren
op_amp
id|iSeries_free
comma
id|reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_ne
l_int|NULL
)paren
(brace
id|reg-&gt;functionMember
op_assign
id|initFunction
suffix:semicolon
id|MYQUEUEENQ
c_func
(paren
op_amp
id|iSeries_queued
comma
id|reg
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;Couldn&squot;t get a queue entry&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iSeries_proc_lock
comma
id|flags
)paren
suffix:semicolon
)brace
eof
