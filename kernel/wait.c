multiline_comment|/*&n; * Generic waiting primitives.&n; *&n; * (C) 2004 William Irwin, Oracle&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/hash.h&gt;
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
DECL|function|wake_bit_function
r_int
id|wake_bit_function
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
id|arg
)paren
(brace
r_struct
id|wait_bit_key
op_star
id|key
op_assign
id|arg
suffix:semicolon
r_struct
id|wait_bit_queue
op_star
id|wait_bit
op_assign
id|container_of
c_func
(paren
id|wait
comma
r_struct
id|wait_bit_queue
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait_bit-&gt;key.flags
op_ne
id|key-&gt;flags
op_logical_or
id|wait_bit-&gt;key.bit_nr
op_ne
id|key-&gt;bit_nr
op_logical_or
id|test_bit
c_func
(paren
id|key-&gt;bit_nr
comma
id|key-&gt;flags
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
id|autoremove_wake_function
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
)brace
DECL|variable|wake_bit_function
id|EXPORT_SYMBOL
c_func
(paren
id|wake_bit_function
)paren
suffix:semicolon
multiline_comment|/*&n; * To allow interruptible waiting and asynchronous (i.e. nonblocking)&n; * waiting, the actions of __wait_on_bit() and __wait_on_bit_lock() are&n; * permitted return codes. Nonzero return codes halt waiting and return.&n; */
r_int
id|__sched
id|fastcall
DECL|function|__wait_on_bit
id|__wait_on_bit
c_func
(paren
id|wait_queue_head_t
op_star
id|wq
comma
r_struct
id|wait_bit_queue
op_star
id|q
comma
r_void
op_star
id|word
comma
r_int
id|bit
comma
r_int
(paren
op_star
id|action
)paren
(paren
r_void
op_star
)paren
comma
r_int
id|mode
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|prepare_to_wait
c_func
(paren
id|wq
comma
op_amp
id|q-&gt;wait
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|bit
comma
id|word
)paren
)paren
id|ret
op_assign
(paren
op_star
id|action
)paren
(paren
id|word
)paren
suffix:semicolon
id|finish_wait
c_func
(paren
id|wq
comma
op_amp
id|q-&gt;wait
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|__wait_on_bit
id|EXPORT_SYMBOL
c_func
(paren
id|__wait_on_bit
)paren
suffix:semicolon
r_int
id|__sched
id|fastcall
DECL|function|__wait_on_bit_lock
id|__wait_on_bit_lock
c_func
(paren
id|wait_queue_head_t
op_star
id|wq
comma
r_struct
id|wait_bit_queue
op_star
id|q
comma
r_void
op_star
id|word
comma
r_int
id|bit
comma
r_int
(paren
op_star
id|action
)paren
(paren
r_void
op_star
)paren
comma
r_int
id|mode
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|test_and_set_bit
c_func
(paren
id|bit
comma
id|word
)paren
)paren
(brace
id|prepare_to_wait_exclusive
c_func
(paren
id|wq
comma
op_amp
id|q-&gt;wait
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|bit
comma
id|word
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|ret
op_assign
(paren
op_star
id|action
)paren
(paren
id|word
)paren
)paren
)paren
r_break
suffix:semicolon
)brace
)brace
id|finish_wait
c_func
(paren
id|wq
comma
op_amp
id|q-&gt;wait
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|__wait_on_bit_lock
id|EXPORT_SYMBOL
c_func
(paren
id|__wait_on_bit_lock
)paren
suffix:semicolon
DECL|function|__wake_up_bit
r_void
id|fastcall
id|__wake_up_bit
c_func
(paren
id|wait_queue_head_t
op_star
id|wq
comma
r_void
op_star
id|word
comma
r_int
id|bit
)paren
(brace
r_struct
id|wait_bit_key
id|key
op_assign
id|__WAIT_BIT_KEY_INITIALIZER
c_func
(paren
id|word
comma
id|bit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|waitqueue_active
c_func
(paren
id|wq
)paren
)paren
id|__wake_up
c_func
(paren
id|wq
comma
id|TASK_INTERRUPTIBLE
op_or
id|TASK_UNINTERRUPTIBLE
comma
l_int|1
comma
op_amp
id|key
)paren
suffix:semicolon
)brace
DECL|variable|__wake_up_bit
id|EXPORT_SYMBOL
c_func
(paren
id|__wake_up_bit
)paren
suffix:semicolon
DECL|function|bit_waitqueue
id|fastcall
id|wait_queue_head_t
op_star
id|bit_waitqueue
c_func
(paren
r_void
op_star
id|word
comma
r_int
id|bit
)paren
(brace
r_const
r_int
id|shift
op_assign
id|BITS_PER_LONG
op_eq
l_int|32
ques
c_cond
l_int|5
suffix:colon
l_int|6
suffix:semicolon
r_const
r_struct
id|zone
op_star
id|zone
op_assign
id|page_zone
c_func
(paren
id|virt_to_page
c_func
(paren
id|word
)paren
)paren
suffix:semicolon
r_int
r_int
id|val
op_assign
(paren
r_int
r_int
)paren
id|word
op_lshift
id|shift
op_or
id|bit
suffix:semicolon
r_return
op_amp
id|zone-&gt;wait_table
(braket
id|hash_long
c_func
(paren
id|val
comma
id|zone-&gt;wait_table_bits
)paren
)braket
suffix:semicolon
)brace
DECL|variable|bit_waitqueue
id|EXPORT_SYMBOL
c_func
(paren
id|bit_waitqueue
)paren
suffix:semicolon
eof
