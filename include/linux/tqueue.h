multiline_comment|/*&n; * tqueue.h --- task queue handling for Linux.&n; *&n; * Mostly based on a proposed bottom-half replacement code written by&n; * Kai Petzke, wpp@marie.physik.tu-berlin.de.&n; *&n; * Modified for use in the Linux kernel by Theodore Ts&squot;o,&n; * tytso@mit.edu.  Any bugs are my fault, not Kai&squot;s.&n; *&n; * The original comment follows below.&n; */
macro_line|#ifndef _LINUX_TQUEUE_H
DECL|macro|_LINUX_TQUEUE_H
mdefine_line|#define _LINUX_TQUEUE_H
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * New proposed &quot;bottom half&quot; handlers:&n; * (C) 1994 Kai Petzke, wpp@marie.physik.tu-berlin.de&n; *&n; * Advantages:&n; * - Bottom halfs are implemented as a linked list.  You can have as many&n; *   of them, as you want.&n; * - No more scanning of a bit field is required upon call of a bottom half.&n; * - Support for chained bottom half lists.  The run_task_queue() function can be&n; *   used as a bottom half handler.  This is for example useful for bottom&n; *   halfs, which want to be delayed until the next clock tick.&n; *&n; * Notes:&n; * - Bottom halfs are called in the reverse order that they were linked into&n; *   the list.&n; */
DECL|struct|tq_struct
r_struct
id|tq_struct
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* linked list of active bh&squot;s */
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
DECL|typedef|task_queue
r_typedef
r_struct
id|list_head
id|task_queue
suffix:semicolon
DECL|macro|DECLARE_TASK_QUEUE
mdefine_line|#define DECLARE_TASK_QUEUE(q)&t;LIST_HEAD(q)
DECL|macro|TQ_ACTIVE
mdefine_line|#define TQ_ACTIVE(q)&t;&t;(!list_empty(&amp;q))
r_extern
id|task_queue
id|tq_timer
comma
id|tq_immediate
comma
id|tq_disk
suffix:semicolon
multiline_comment|/*&n; * To implement your own list of active bottom halfs, use the following&n; * two definitions:&n; *&n; * DECLARE_TASK_QUEUE(my_tqueue);&n; * struct tq_struct my_task = {&n; * &t;routine: (void (*)(void *)) my_routine,&n; *&t;data: &amp;my_data&n; * };&n; *&n; * To activate a bottom half on a list, use:&n; *&n; *&t;queue_task(&amp;my_task, &amp;my_tqueue);&n; *&n; * To later run the queued tasks use&n; *&n; *&t;run_task_queue(&amp;my_tqueue);&n; *&n; * This allows you to do deferred processing.  For example, you could&n; * have a task queue called tq_timer, which is executed within the timer&n; * interrupt.&n; */
r_extern
id|spinlock_t
id|tqueue_lock
suffix:semicolon
multiline_comment|/*&n; * Queue a task on a tq.  Return non-zero if it was successfully&n; * added.&n; */
DECL|function|queue_task
r_static
r_inline
r_int
id|queue_task
c_func
(paren
r_struct
id|tq_struct
op_star
id|bh_pointer
comma
id|task_queue
op_star
id|bh_list
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|bh_pointer-&gt;sync
)paren
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
id|tqueue_lock
comma
id|flags
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|bh_pointer-&gt;list
comma
id|bh_list
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|tqueue_lock
comma
id|flags
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Call all &quot;bottom halfs&quot; on a given list.&n; */
r_extern
r_void
id|__run_task_queue
c_func
(paren
id|task_queue
op_star
id|list
)paren
suffix:semicolon
DECL|function|run_task_queue
r_static
r_inline
r_void
id|run_task_queue
c_func
(paren
id|task_queue
op_star
id|list
)paren
(brace
r_if
c_cond
(paren
id|TQ_ACTIVE
c_func
(paren
op_star
id|list
)paren
)paren
id|__run_task_queue
c_func
(paren
id|list
)paren
suffix:semicolon
)brace
macro_line|#endif /* _LINUX_TQUEUE_H */
eof
