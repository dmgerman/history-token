multiline_comment|/*&n; *  linux/drivers/block/elevator.c&n; *&n; *  Block device elevator/IO-scheduler.&n; *&n; *  Copyright (C) 2000 Andrea Arcangeli &lt;andrea@suse.de&gt; SuSE&n; *&n; * 30042000 Jens Axboe &lt;axboe@suse.de&gt; :&n; *&n; * Split the elevator a bit so that it is possible to choose a different&n; * one or even write a new &quot;plug in&quot;. There are three pieces:&n; * - elevator_fn, inserts a new request in the queue list&n; * - elevator_merge_fn, decides whether a new buffer can be merged with&n; *   an existing request&n; * - elevator_dequeue_fn, called when a request is taken off the active list&n; *&n; * 20082000 Dave Jones &lt;davej@suse.de&gt; :&n; * Removed tests for max-bomb-segments, which was breaking elvtune&n; *  when run without -bN&n; *&n; * Jens:&n; * - Rework again to work with bio instead of buffer_heads&n; * - loose bi_dev comparisons, partition handling is right now&n; * - completely modularize elevator setup and teardown&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/elevator.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * This is a bit tricky. It&squot;s given that bio and rq are for the same&n; * device, but the next request might of course not be. Run through&n; * the tests below to check if we want to insert here if we can&squot;t merge&n; * bio into an existing request&n; */
DECL|function|bio_rq_in_between
r_inline
r_int
id|bio_rq_in_between
c_func
(paren
r_struct
id|bio
op_star
id|bio
comma
r_struct
id|request
op_star
id|rq
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_struct
id|list_head
op_star
id|next
suffix:semicolon
r_struct
id|request
op_star
id|next_rq
suffix:semicolon
multiline_comment|/*&n;&t; * if .next is a valid request&n;&t; */
id|next
op_assign
id|rq-&gt;queuelist.next
suffix:semicolon
r_if
c_cond
(paren
id|next
op_eq
id|head
)paren
r_return
l_int|0
suffix:semicolon
id|next_rq
op_assign
id|list_entry
c_func
(paren
id|next
comma
r_struct
id|request
comma
id|queuelist
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|next_rq-&gt;flags
op_amp
id|REQ_STARTED
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * if the device is different (not a normal case) just check if&n;&t; * bio is after rq&n;&t; */
r_if
c_cond
(paren
id|next_rq-&gt;rq_dev
op_ne
id|rq-&gt;rq_dev
)paren
r_return
id|bio-&gt;bi_sector
OG
id|rq-&gt;sector
suffix:semicolon
multiline_comment|/*&n;&t; * ok, rq, next_rq and bio are on the same device. if bio is in between&n;&t; * the two, this is the sweet spot&n;&t; */
r_if
c_cond
(paren
id|bio-&gt;bi_sector
template_param
id|rq-&gt;sector
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * next_rq is ordered wrt rq, but bio is not in between the two&n;&t; */
r_if
c_cond
(paren
id|next_rq-&gt;sector
OG
id|rq-&gt;sector
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * next_rq and rq not ordered, if we happen to be either before&n;&t; * next_rq or after rq insert here anyway&n;&t; */
r_if
c_cond
(paren
id|bio-&gt;bi_sector
OG
id|rq-&gt;sector
op_logical_or
id|bio-&gt;bi_sector
OL
id|next_rq-&gt;sector
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * can we safely merge with this request?&n; */
DECL|function|elv_rq_merge_ok
r_inline
r_int
id|elv_rq_merge_ok
c_func
(paren
r_struct
id|request
op_star
id|rq
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
multiline_comment|/*&n;&t; * different data direction or already started, don&squot;t merge&n;&t; */
r_if
c_cond
(paren
id|bio_data_dir
c_func
(paren
id|bio
)paren
op_ne
id|rq_data_dir
c_func
(paren
id|rq
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|rq-&gt;flags
op_amp
id|REQ_NOMERGE
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * same device and no special stuff set, merge is ok&n;&t; */
r_if
c_cond
(paren
id|rq-&gt;rq_dev
op_eq
id|bio-&gt;bi_dev
op_logical_and
op_logical_neg
id|rq-&gt;waiting
op_logical_and
op_logical_neg
id|rq-&gt;special
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|elevator_linus_merge
r_int
id|elevator_linus_merge
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|request
op_star
op_star
id|req
comma
r_struct
id|list_head
op_star
id|head
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
r_int
r_int
id|count
op_assign
id|bio_sectors
c_func
(paren
id|bio
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
op_assign
op_amp
id|q-&gt;queue_head
suffix:semicolon
r_int
id|ret
op_assign
id|ELEVATOR_NO_MERGE
suffix:semicolon
r_struct
id|request
op_star
id|__rq
suffix:semicolon
id|entry
op_assign
op_amp
id|q-&gt;queue_head
suffix:semicolon
r_while
c_loop
(paren
(paren
id|entry
op_assign
id|entry-&gt;prev
)paren
op_ne
id|head
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
id|prefetch
c_func
(paren
id|list_entry_rq
c_func
(paren
id|entry-&gt;prev
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * simply &quot;aging&quot; of requests in queue&n;&t;&t; */
r_if
c_cond
(paren
id|__rq-&gt;elevator_sequence
op_decrement
op_le
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|__rq-&gt;flags
op_amp
(paren
id|REQ_BARRIER
op_or
id|REQ_STARTED
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|req
op_logical_and
id|bio_rq_in_between
c_func
(paren
id|bio
comma
id|__rq
comma
op_amp
id|q-&gt;queue_head
)paren
)paren
op_star
id|req
op_assign
id|__rq
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|elv_rq_merge_ok
c_func
(paren
id|__rq
comma
id|bio
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|__rq-&gt;elevator_sequence
OL
id|count
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * we can merge and sequence is ok, check if it&squot;s possible&n;&t;&t; */
r_if
c_cond
(paren
id|__rq-&gt;sector
op_plus
id|__rq-&gt;nr_sectors
op_eq
id|bio-&gt;bi_sector
)paren
(brace
id|ret
op_assign
id|ELEVATOR_BACK_MERGE
suffix:semicolon
op_star
id|req
op_assign
id|__rq
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|__rq-&gt;sector
op_minus
id|count
op_eq
id|bio-&gt;bi_sector
)paren
(brace
id|ret
op_assign
id|ELEVATOR_FRONT_MERGE
suffix:semicolon
id|__rq-&gt;elevator_sequence
op_sub_assign
id|count
suffix:semicolon
op_star
id|req
op_assign
id|__rq
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|elevator_linus_merge_cleanup
r_void
id|elevator_linus_merge_cleanup
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
r_int
id|count
)paren
(brace
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
id|BUG_ON
c_func
(paren
id|req-&gt;q
op_ne
id|q
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * second pass scan of requests that got passed over, if any&n;&t; */
id|entry
op_assign
op_amp
id|req-&gt;queuelist
suffix:semicolon
r_while
c_loop
(paren
(paren
id|entry
op_assign
id|entry-&gt;next
)paren
op_ne
op_amp
id|q-&gt;queue_head
)paren
(brace
r_struct
id|request
op_star
id|tmp
suffix:semicolon
id|prefetch
c_func
(paren
id|list_entry_rq
c_func
(paren
id|entry-&gt;next
)paren
)paren
suffix:semicolon
id|tmp
op_assign
id|list_entry_rq
c_func
(paren
id|entry
)paren
suffix:semicolon
id|tmp-&gt;elevator_sequence
op_sub_assign
id|count
suffix:semicolon
)brace
)brace
DECL|function|elevator_linus_merge_req
r_void
id|elevator_linus_merge_req
c_func
(paren
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
r_if
c_cond
(paren
id|next-&gt;elevator_sequence
OL
id|req-&gt;elevator_sequence
)paren
id|req-&gt;elevator_sequence
op_assign
id|next-&gt;elevator_sequence
suffix:semicolon
)brace
DECL|function|elv_add_request_fn
r_void
id|elv_add_request_fn
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
id|list_add
c_func
(paren
op_amp
id|rq-&gt;queuelist
comma
id|insert_here
)paren
suffix:semicolon
)brace
DECL|function|elv_next_request_fn
r_struct
id|request
op_star
id|elv_next_request_fn
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
id|blk_queue_empty
c_func
(paren
id|q
)paren
)paren
r_return
id|list_entry
c_func
(paren
id|q-&gt;queue_head.next
comma
r_struct
id|request
comma
id|queuelist
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|elv_linus_init
r_int
id|elv_linus_init
c_func
(paren
id|request_queue_t
op_star
id|q
comma
id|elevator_t
op_star
id|e
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|elv_linus_exit
r_void
id|elv_linus_exit
c_func
(paren
id|request_queue_t
op_star
id|q
comma
id|elevator_t
op_star
id|e
)paren
(brace
)brace
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
id|request
op_star
op_star
id|req
comma
r_struct
id|list_head
op_star
id|head
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
r_int
r_int
id|count
op_assign
id|bio_sectors
c_func
(paren
id|bio
)paren
suffix:semicolon
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
id|entry
op_assign
op_amp
id|q-&gt;queue_head
suffix:semicolon
r_while
c_loop
(paren
(paren
id|entry
op_assign
id|entry-&gt;prev
)paren
op_ne
id|head
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
id|prefetch
c_func
(paren
id|list_entry_rq
c_func
(paren
id|entry-&gt;prev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__rq-&gt;flags
op_amp
(paren
id|REQ_BARRIER
op_or
id|REQ_STARTED
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|elv_rq_merge_ok
c_func
(paren
id|__rq
comma
id|bio
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * we can merge and sequence is ok, check if it&squot;s possible&n;&t;&t; */
r_if
c_cond
(paren
id|__rq-&gt;sector
op_plus
id|__rq-&gt;nr_sectors
op_eq
id|bio-&gt;bi_sector
)paren
(brace
op_star
id|req
op_assign
id|__rq
suffix:semicolon
r_return
id|ELEVATOR_BACK_MERGE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|__rq-&gt;sector
op_minus
id|count
op_eq
id|bio-&gt;bi_sector
)paren
(brace
op_star
id|req
op_assign
id|__rq
suffix:semicolon
r_return
id|ELEVATOR_FRONT_MERGE
suffix:semicolon
)brace
)brace
r_return
id|ELEVATOR_NO_MERGE
suffix:semicolon
)brace
DECL|function|elevator_noop_merge_cleanup
r_void
id|elevator_noop_merge_cleanup
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
r_int
id|count
)paren
(brace
)brace
DECL|function|elevator_noop_merge_req
r_void
id|elevator_noop_merge_req
c_func
(paren
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
)brace
DECL|function|elevator_init
r_int
id|elevator_init
c_func
(paren
id|request_queue_t
op_star
id|q
comma
id|elevator_t
op_star
id|e
comma
id|elevator_t
id|type
)paren
(brace
op_star
id|e
op_assign
id|type
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|q-&gt;queue_head
)paren
suffix:semicolon
r_if
c_cond
(paren
id|e-&gt;elevator_init_fn
)paren
r_return
id|e
op_member_access_from_pointer
id|elevator_init_fn
c_func
(paren
id|q
comma
id|e
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|elevator_exit
r_void
id|elevator_exit
c_func
(paren
id|request_queue_t
op_star
id|q
comma
id|elevator_t
op_star
id|e
)paren
(brace
r_if
c_cond
(paren
id|e-&gt;elevator_exit_fn
)paren
id|e
op_member_access_from_pointer
id|elevator_exit_fn
c_func
(paren
id|q
comma
id|e
)paren
suffix:semicolon
)brace
DECL|function|elevator_global_init
r_int
id|elevator_global_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|elevator_global_init
id|module_init
c_func
(paren
id|elevator_global_init
)paren
suffix:semicolon
eof
