multiline_comment|/*&n; * elevator noop&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/elevator.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * See if we can find a request that this buffer can be coalesced with.&n; */
DECL|function|elevator_noop_merge
r_int
id|elevator_noop_merge
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|list_head
op_star
op_star
id|insert
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
r_struct
id|list_head
op_star
id|entry
op_assign
op_amp
id|q-&gt;queue_head
suffix:semicolon
r_struct
id|request
op_star
id|__rq
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|elv_try_last_merge
c_func
(paren
id|q
comma
id|bio
)paren
)paren
)paren
(brace
op_star
id|insert
op_assign
id|q-&gt;last_merge
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|entry
op_assign
id|entry-&gt;prev
)paren
op_ne
op_amp
id|q-&gt;queue_head
)paren
(brace
id|__rq
op_assign
id|list_entry_rq
c_func
(paren
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__rq-&gt;flags
op_amp
(paren
id|REQ_SOFTBARRIER
op_or
id|REQ_HARDBARRIER
)paren
)paren
r_break
suffix:semicolon
r_else
r_if
c_cond
(paren
id|__rq-&gt;flags
op_amp
id|REQ_STARTED
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|blk_fs_request
c_func
(paren
id|__rq
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|elv_try_merge
c_func
(paren
id|__rq
comma
id|bio
)paren
)paren
)paren
(brace
op_star
id|insert
op_assign
op_amp
id|__rq-&gt;queuelist
suffix:semicolon
id|q-&gt;last_merge
op_assign
op_amp
id|__rq-&gt;queuelist
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
r_return
id|ELEVATOR_NO_MERGE
suffix:semicolon
)brace
DECL|function|elevator_noop_merge_requests
r_void
id|elevator_noop_merge_requests
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|request
op_star
id|req
comma
r_struct
id|request
op_star
id|next
)paren
(brace
id|list_del_init
c_func
(paren
op_amp
id|next-&gt;queuelist
)paren
suffix:semicolon
)brace
DECL|function|elevator_noop_add_request
r_void
id|elevator_noop_add_request
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|request
op_star
id|rq
comma
r_struct
id|list_head
op_star
id|insert_here
)paren
(brace
id|list_add_tail
c_func
(paren
op_amp
id|rq-&gt;queuelist
comma
op_amp
id|q-&gt;queue_head
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * new merges must not precede this barrier&n;&t; */
r_if
c_cond
(paren
id|rq-&gt;flags
op_amp
id|REQ_HARDBARRIER
)paren
id|q-&gt;last_merge
op_assign
l_int|NULL
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|q-&gt;last_merge
)paren
id|q-&gt;last_merge
op_assign
op_amp
id|rq-&gt;queuelist
suffix:semicolon
)brace
DECL|function|elevator_noop_next_request
r_struct
id|request
op_star
id|elevator_noop_next_request
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|q-&gt;queue_head
)paren
)paren
r_return
id|list_entry_rq
c_func
(paren
id|q-&gt;queue_head.next
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|elevator_noop
id|elevator_t
id|elevator_noop
op_assign
(brace
dot
id|elevator_merge_fn
op_assign
id|elevator_noop_merge
comma
dot
id|elevator_merge_req_fn
op_assign
id|elevator_noop_merge_requests
comma
dot
id|elevator_next_req_fn
op_assign
id|elevator_noop_next_request
comma
dot
id|elevator_add_req_fn
op_assign
id|elevator_noop_add_request
comma
dot
id|elevator_name
op_assign
l_string|&quot;noop&quot;
comma
)brace
suffix:semicolon
DECL|variable|elevator_noop
id|EXPORT_SYMBOL
c_func
(paren
id|elevator_noop
)paren
suffix:semicolon
eof
