multiline_comment|/*&n; *  linux/drivers/block/elevator.c&n; *&n; *  Block device elevator/IO-scheduler.&n; *&n; *  Copyright (C) 2000 Andrea Arcangeli &lt;andrea@suse.de&gt; SuSE&n; *&n; * 30042000 Jens Axboe &lt;axboe@suse.de&gt; :&n; *&n; * Split the elevator a bit so that it is possible to choose a different&n; * one or even write a new &quot;plug in&quot;. There are three pieces:&n; * - elevator_fn, inserts a new request in the queue list&n; * - elevator_merge_fn, decides whether a new buffer can be merged with&n; *   an existing request&n; * - elevator_dequeue_fn, called when a request is taken off the active list&n; *&n; * 20082000 Dave Jones &lt;davej@suse.de&gt; :&n; * Removed tests for max-bomb-segments, which was breaking elvtune&n; *  when run without -bN&n; *&n; * Jens:&n; * - Rework again to work with bio instead of buffer_heads&n; * - loose bi_dev comparisons, partition handling is right now&n; * - completely modularize elevator setup and teardown&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/elevator.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
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
id|unlikely
c_func
(paren
id|next
op_eq
id|head
)paren
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
multiline_comment|/*&n;&t; * not a sector based request&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|next_rq-&gt;flags
op_amp
id|REQ_CMD
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * if the device is different (not a normal case) just check if&n;&t; * bio is after rq&n;&t; */
r_if
c_cond
(paren
id|next_rq-&gt;rq_disk
op_ne
id|rq-&gt;rq_disk
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
r_if
c_cond
(paren
op_logical_neg
id|rq_mergeable
c_func
(paren
id|rq
)paren
)paren
r_return
l_int|0
suffix:semicolon
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
multiline_comment|/*&n;&t; * same device and no special stuff set, merge is ok&n;&t; */
r_if
c_cond
(paren
id|rq-&gt;rq_disk
op_eq
id|bio-&gt;bi_bdev-&gt;bd_disk
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
DECL|function|elv_try_merge
r_inline
r_int
id|elv_try_merge
c_func
(paren
r_struct
id|request
op_star
id|__rq
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
r_int
id|ret
op_assign
id|ELEVATOR_NO_MERGE
suffix:semicolon
multiline_comment|/*&n;&t; * we can merge and sequence is ok, check if it&squot;s possible&n;&t; */
r_if
c_cond
(paren
id|elv_rq_merge_ok
c_func
(paren
id|__rq
comma
id|bio
)paren
)paren
(brace
r_if
c_cond
(paren
id|__rq-&gt;sector
op_plus
id|__rq-&gt;nr_sectors
op_eq
id|bio-&gt;bi_sector
)paren
id|ret
op_assign
id|ELEVATOR_BACK_MERGE
suffix:semicolon
r_else
r_if
c_cond
(paren
id|__rq-&gt;sector
op_minus
id|bio_sectors
c_func
(paren
id|bio
)paren
op_eq
id|bio-&gt;bi_sector
)paren
id|ret
op_assign
id|ELEVATOR_FRONT_MERGE
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|elv_try_last_merge
r_inline
r_int
id|elv_try_last_merge
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
r_int
id|ret
op_assign
id|ELEVATOR_NO_MERGE
suffix:semicolon
multiline_comment|/*&n;&t; * give a one-shot try to merging with the last touched&n;&t; * request&n;&t; */
r_if
c_cond
(paren
id|q-&gt;last_merge
)paren
(brace
r_struct
id|request
op_star
id|__rq
op_assign
id|list_entry_rq
c_func
(paren
id|q-&gt;last_merge
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rq_mergeable
c_func
(paren
id|__rq
)paren
)paren
id|q-&gt;last_merge
op_assign
l_int|NULL
suffix:semicolon
r_else
id|ret
op_assign
id|elv_try_merge
c_func
(paren
id|__rq
comma
id|bio
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * elevator noop&n; *&n; * See if we can find a request that this buffer can be coalesced with.&n; */
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
(paren
id|__rq-&gt;flags
op_amp
id|REQ_CMD
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
multiline_comment|/*&n; * general block -&gt; elevator interface starts here&n; */
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
id|type
)paren
(brace
id|elevator_t
op_star
id|e
op_assign
op_amp
id|q-&gt;elevator
suffix:semicolon
id|memcpy
c_func
(paren
id|e
comma
id|type
comma
r_sizeof
(paren
op_star
id|e
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|q-&gt;queue_head
)paren
suffix:semicolon
id|q-&gt;last_merge
op_assign
l_int|NULL
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
)paren
(brace
id|elevator_t
op_star
id|e
op_assign
op_amp
id|q-&gt;elevator
suffix:semicolon
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
DECL|function|elv_merge
r_int
id|elv_merge
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
id|entry
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
id|elevator_t
op_star
id|e
op_assign
op_amp
id|q-&gt;elevator
suffix:semicolon
r_if
c_cond
(paren
id|e-&gt;elevator_merge_fn
)paren
r_return
id|e
op_member_access_from_pointer
id|elevator_merge_fn
c_func
(paren
id|q
comma
id|entry
comma
id|bio
)paren
suffix:semicolon
r_return
id|ELEVATOR_NO_MERGE
suffix:semicolon
)brace
DECL|function|elv_merged_request
r_void
id|elv_merged_request
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
)paren
(brace
id|elevator_t
op_star
id|e
op_assign
op_amp
id|q-&gt;elevator
suffix:semicolon
r_if
c_cond
(paren
id|e-&gt;elevator_merged_fn
)paren
id|e
op_member_access_from_pointer
id|elevator_merged_fn
c_func
(paren
id|q
comma
id|rq
)paren
suffix:semicolon
)brace
DECL|function|elv_merge_requests
r_void
id|elv_merge_requests
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
id|request
op_star
id|next
)paren
(brace
id|elevator_t
op_star
id|e
op_assign
op_amp
id|q-&gt;elevator
suffix:semicolon
r_if
c_cond
(paren
id|e-&gt;elevator_merge_req_fn
)paren
id|e
op_member_access_from_pointer
id|elevator_merge_req_fn
c_func
(paren
id|q
comma
id|rq
comma
id|next
)paren
suffix:semicolon
)brace
DECL|function|__elv_add_request
r_void
id|__elv_add_request
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
r_int
id|at_end
comma
r_int
id|plug
)paren
(brace
r_struct
id|list_head
op_star
id|insert
op_assign
op_amp
id|q-&gt;queue_head
suffix:semicolon
r_if
c_cond
(paren
id|at_end
)paren
id|insert
op_assign
id|insert-&gt;prev
suffix:semicolon
r_if
c_cond
(paren
id|plug
)paren
id|blk_plug_device
c_func
(paren
id|q
)paren
suffix:semicolon
id|q-&gt;elevator
dot
id|elevator_add_req_fn
c_func
(paren
id|q
comma
id|rq
comma
id|insert
)paren
suffix:semicolon
)brace
DECL|function|elv_add_request
r_void
id|elv_add_request
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
r_int
id|at_end
comma
r_int
id|plug
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
id|q-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
id|__elv_add_request
c_func
(paren
id|q
comma
id|rq
comma
id|at_end
comma
id|plug
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|q-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|__elv_next_request
r_static
r_inline
r_struct
id|request
op_star
id|__elv_next_request
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
(brace
r_return
id|q-&gt;elevator
dot
id|elevator_next_req_fn
c_func
(paren
id|q
)paren
suffix:semicolon
)brace
DECL|function|elv_next_request
r_struct
id|request
op_star
id|elv_next_request
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
(brace
r_struct
id|request
op_star
id|rq
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_while
c_loop
(paren
(paren
id|rq
op_assign
id|__elv_next_request
c_func
(paren
id|q
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * just mark as started even if we don&squot;t start it, a request&n;&t;&t; * that has been delayed should not be passed by new incoming&n;&t;&t; * requests&n;&t;&t; */
id|rq-&gt;flags
op_or_assign
id|REQ_STARTED
suffix:semicolon
r_if
c_cond
(paren
op_amp
id|rq-&gt;queuelist
op_eq
id|q-&gt;last_merge
)paren
id|q-&gt;last_merge
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rq-&gt;flags
op_amp
id|REQ_DONTPREP
)paren
op_logical_or
op_logical_neg
id|q-&gt;prep_rq_fn
)paren
r_break
suffix:semicolon
id|ret
op_assign
id|q
op_member_access_from_pointer
id|prep_rq_fn
c_func
(paren
id|q
comma
id|rq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|BLKPREP_OK
)paren
(brace
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ret
op_eq
id|BLKPREP_DEFER
)paren
(brace
id|rq
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ret
op_eq
id|BLKPREP_KILL
)paren
(brace
id|blkdev_dequeue_request
c_func
(paren
id|rq
)paren
suffix:semicolon
id|rq-&gt;flags
op_or_assign
id|REQ_QUIET
suffix:semicolon
r_while
c_loop
(paren
id|end_that_request_first
c_func
(paren
id|rq
comma
l_int|0
comma
id|rq-&gt;nr_sectors
)paren
)paren
suffix:semicolon
id|end_that_request_last
c_func
(paren
id|rq
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;%s: bad return=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ret
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|rq
suffix:semicolon
)brace
DECL|function|elv_remove_request
r_void
id|elv_remove_request
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
)paren
(brace
id|elevator_t
op_star
id|e
op_assign
op_amp
id|q-&gt;elevator
suffix:semicolon
multiline_comment|/*&n;&t; * the main clearing point for q-&gt;last_merge is on retrieval of&n;&t; * request by driver (it calls elv_next_request()), but it _can_&n;&t; * also happen here if a request is added to the queue but later&n;&t; * deleted without ever being given to driver (merged with another&n;&t; * request).&n;&t; */
r_if
c_cond
(paren
op_amp
id|rq-&gt;queuelist
op_eq
id|q-&gt;last_merge
)paren
id|q-&gt;last_merge
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|e-&gt;elevator_remove_req_fn
)paren
id|e
op_member_access_from_pointer
id|elevator_remove_req_fn
c_func
(paren
id|q
comma
id|rq
)paren
suffix:semicolon
)brace
DECL|function|elv_queue_empty
r_int
id|elv_queue_empty
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
(brace
id|elevator_t
op_star
id|e
op_assign
op_amp
id|q-&gt;elevator
suffix:semicolon
r_if
c_cond
(paren
id|e-&gt;elevator_queue_empty_fn
)paren
r_return
id|e
op_member_access_from_pointer
id|elevator_queue_empty_fn
c_func
(paren
id|q
)paren
suffix:semicolon
r_return
id|list_empty
c_func
(paren
op_amp
id|q-&gt;queue_head
)paren
suffix:semicolon
)brace
DECL|function|elv_get_sort_head
r_inline
r_struct
id|list_head
op_star
id|elv_get_sort_head
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
)paren
(brace
id|elevator_t
op_star
id|e
op_assign
op_amp
id|q-&gt;elevator
suffix:semicolon
r_if
c_cond
(paren
id|e-&gt;elevator_get_sort_head_fn
)paren
r_return
id|e
op_member_access_from_pointer
id|elevator_get_sort_head_fn
c_func
(paren
id|q
comma
id|rq
)paren
suffix:semicolon
r_return
op_amp
id|q-&gt;queue_head
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
id|elevator_next_req_fn
op_assign
id|elevator_noop_next_request
comma
dot
id|elevator_add_req_fn
op_assign
id|elevator_noop_add_request
comma
)brace
suffix:semicolon
DECL|variable|elevator_global_init
id|module_init
c_func
(paren
id|elevator_global_init
)paren
suffix:semicolon
DECL|variable|elevator_noop
id|EXPORT_SYMBOL
c_func
(paren
id|elevator_noop
)paren
suffix:semicolon
DECL|variable|elv_add_request
id|EXPORT_SYMBOL
c_func
(paren
id|elv_add_request
)paren
suffix:semicolon
DECL|variable|__elv_add_request
id|EXPORT_SYMBOL
c_func
(paren
id|__elv_add_request
)paren
suffix:semicolon
DECL|variable|elv_next_request
id|EXPORT_SYMBOL
c_func
(paren
id|elv_next_request
)paren
suffix:semicolon
DECL|variable|elv_remove_request
id|EXPORT_SYMBOL
c_func
(paren
id|elv_remove_request
)paren
suffix:semicolon
DECL|variable|elv_queue_empty
id|EXPORT_SYMBOL
c_func
(paren
id|elv_queue_empty
)paren
suffix:semicolon
DECL|variable|elevator_exit
id|EXPORT_SYMBOL
c_func
(paren
id|elevator_exit
)paren
suffix:semicolon
DECL|variable|elevator_init
id|EXPORT_SYMBOL
c_func
(paren
id|elevator_init
)paren
suffix:semicolon
eof
