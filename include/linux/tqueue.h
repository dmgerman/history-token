multiline_comment|/*&n; * tqueue.h --- task queue handling for Linux.&n; *&n; * Modified version of previous incarnations of task-queues,&n; * written by:&n; *&n; * (C) 1994 Kai Petzke, wpp@marie.physik.tu-berlin.de&n; * Modified for use in the Linux kernel by Theodore Ts&squot;o,&n; * tytso@mit.edu.&n; */
macro_line|#ifndef _LINUX_TQUEUE_H
DECL|macro|_LINUX_TQUEUE_H
mdefine_line|#define _LINUX_TQUEUE_H
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|struct|tq_struct
r_struct
id|tq_struct
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* linked list of active tq&squot;s */
DECL|member|sync
r_int
r_int
id|sync
suffix:semicolon
multiline_comment|/* must be initialized to zero */
DECL|member|routine
r_void
(paren
op_star
id|routine
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* function to call */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* argument to function */
)brace
suffix:semicolon
multiline_comment|/*&n; * Emit code to initialise a tq_struct&squot;s routine and data pointers&n; */
DECL|macro|PREPARE_TQUEUE
mdefine_line|#define PREPARE_TQUEUE(_tq, _routine, _data)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(_tq)-&gt;routine = _routine;&t;&t;&t;&bslash;&n;&t;&t;(_tq)-&gt;data = _data;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/*&n; * Emit code to initialise all of a tq_struct&n; */
DECL|macro|INIT_TQUEUE
mdefine_line|#define INIT_TQUEUE(_tq, _routine, _data)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;INIT_LIST_HEAD(&amp;(_tq)-&gt;list);&t;&t;&t;&bslash;&n;&t;&t;(_tq)-&gt;sync = 0;&t;&t;&t;&t;&bslash;&n;&t;&t;PREPARE_TQUEUE((_tq), (_routine), (_data));&t;&bslash;&n;&t;} while (0)
DECL|macro|DECLARE_TASK_QUEUE
mdefine_line|#define DECLARE_TASK_QUEUE(q)&t;LIST_HEAD(q)
multiline_comment|/* Schedule a tq to run in process context */
r_extern
r_int
id|schedule_task
c_func
(paren
r_struct
id|tq_struct
op_star
id|task
)paren
suffix:semicolon
multiline_comment|/* finish all currently pending tasks - do not call from irq context */
r_extern
r_void
id|flush_scheduled_tasks
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
