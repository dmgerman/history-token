multiline_comment|/*&n; * Generic waiting primitives.&n; *&n; * (C) 2004 William Irwin, Oracle&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
DECL|function|add_wait_queue
r_void
id|fastcall
id|add_wait_queue
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
id|wait_queue_t
op_star
id|wait
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|wait-&gt;flags
op_and_assign
op_complement
id|WQ_FLAG_EXCLUSIVE
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|__add_wait_queue
c_func
(paren
id|q
comma
id|wait
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|add_wait_queue
id|EXPORT_SYMBOL
c_func
(paren
id|add_wait_queue
)paren
suffix:semicolon
DECL|function|add_wait_queue_exclusive
r_void
id|fastcall
id|add_wait_queue_exclusive
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
id|wait_queue_t
op_star
id|wait
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|wait-&gt;flags
op_or_assign
id|WQ_FLAG_EXCLUSIVE
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|__add_wait_queue_tail
c_func
(paren
id|q
comma
id|wait
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|add_wait_queue_exclusive
id|EXPORT_SYMBOL
c_func
(paren
id|add_wait_queue_exclusive
)paren
suffix:semicolon
DECL|function|remove_wait_queue
r_void
id|fastcall
id|remove_wait_queue
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
id|wait_queue_t
op_star
id|wait
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
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|__remove_wait_queue
c_func
(paren
id|q
comma
id|wait
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|remove_wait_queue
id|EXPORT_SYMBOL
c_func
(paren
id|remove_wait_queue
)paren
suffix:semicolon
multiline_comment|/*&n; * Note: we use &quot;set_current_state()&quot; _after_ the wait-queue add,&n; * because we need a memory barrier there on SMP, so that any&n; * wake-function that tests for the wait-queue being active&n; * will be guaranteed to see waitqueue addition _or_ subsequent&n; * tests in this thread will see the wakeup having taken place.&n; *&n; * The spin_unlock() itself is semi-permeable and only protects&n; * one way (it only protects stuff inside the critical region and&n; * stops them from bleeding out - it would still allow subsequent&n; * loads to move into the the critical region).&n; */
r_void
id|fastcall
DECL|function|prepare_to_wait
id|prepare_to_wait
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
id|wait_queue_t
op_star
id|wait
comma
r_int
id|state
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|wait-&gt;flags
op_and_assign
op_complement
id|WQ_FLAG_EXCLUSIVE
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|wait-&gt;task_list
)paren
)paren
id|__add_wait_queue
c_func
(paren
id|q
comma
id|wait
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * don&squot;t alter the task state if this is just going to&n;&t; * queue an async wait queue callback&n;&t; */
r_if
c_cond
(paren
id|is_sync_wait
c_func
(paren
id|wait
)paren
)paren
id|set_current_state
c_func
(paren
id|state
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|prepare_to_wait
id|EXPORT_SYMBOL
c_func
(paren
id|prepare_to_wait
)paren
suffix:semicolon
r_void
id|fastcall
DECL|function|prepare_to_wait_exclusive
id|prepare_to_wait_exclusive
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
id|wait_queue_t
op_star
id|wait
comma
r_int
id|state
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|wait-&gt;flags
op_or_assign
id|WQ_FLAG_EXCLUSIVE
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|wait-&gt;task_list
)paren
)paren
id|__add_wait_queue_tail
c_func
(paren
id|q
comma
id|wait
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * don&squot;t alter the task state if this is just going to&n; &t; * queue an async wait queue callback&n;&t; */
r_if
c_cond
(paren
id|is_sync_wait
c_func
(paren
id|wait
)paren
)paren
id|set_current_state
c_func
(paren
id|state
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|prepare_to_wait_exclusive
id|EXPORT_SYMBOL
c_func
(paren
id|prepare_to_wait_exclusive
)paren
suffix:semicolon
DECL|function|finish_wait
r_void
id|fastcall
id|finish_wait
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
id|wait_queue_t
op_star
id|wait
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|__set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We can check for list emptiness outside the lock&n;&t; * IFF:&n;&t; *  - we use the &quot;careful&quot; check that verifies both&n;&t; *    the next and prev pointers, so that there cannot&n;&t; *    be any half-pending updates in progress on other&n;&t; *    CPU&squot;s that we haven&squot;t seen yet (and that might&n;&t; *    still change the stack area.&n;&t; * and&n;&t; *  - all other users take the lock (ie we can only&n;&t; *    have _one_ other CPU that looks at or modifies&n;&t; *    the list).&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|list_empty_careful
c_func
(paren
op_amp
id|wait-&gt;task_list
)paren
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|wait-&gt;task_list
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
DECL|variable|finish_wait
id|EXPORT_SYMBOL
c_func
(paren
id|finish_wait
)paren
suffix:semicolon
DECL|function|autoremove_wake_function
r_int
id|autoremove_wake_function
c_func
(paren
id|wait_queue_t
op_star
id|wait
comma
r_int
id|mode
comma
r_int
id|sync
comma
r_void
op_star
id|key
)paren
(brace
r_int
id|ret
op_assign
id|default_wake_function
c_func
(paren
id|wait
comma
id|mode
comma
id|sync
comma
id|key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|list_del_init
c_func
(paren
op_amp
id|wait-&gt;task_list
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|autoremove_wake_function
id|EXPORT_SYMBOL
c_func
(paren
id|autoremove_wake_function
)paren
suffix:semicolon
eof
