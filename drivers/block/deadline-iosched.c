multiline_comment|/*&n; *  linux/drivers/block/deadline-iosched.c&n; *&n; *  Deadline i/o scheduler.&n; *&n; *  Copyright (C) 2002 Jens Axboe &lt;axboe@suse.de&gt;&n; */
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
macro_line|#include &lt;linux/hash.h&gt;
multiline_comment|/*&n; * feel free to try other values :-). read_expire value is the timeout for&n; * reads, our goal is to start a request &quot;around&quot; the time when it expires.&n; * fifo_batch is how many steps along the sorted list we will take when the&n; * front fifo request expires.&n; */
DECL|variable|read_expire
r_static
r_int
id|read_expire
op_assign
id|HZ
op_div
l_int|2
suffix:semicolon
multiline_comment|/* 500ms start timeout */
DECL|variable|fifo_batch
r_static
r_int
id|fifo_batch
op_assign
l_int|32
suffix:semicolon
multiline_comment|/* 4 seeks, or 64 contig */
DECL|variable|seek_cost
r_static
r_int
id|seek_cost
op_assign
l_int|16
suffix:semicolon
multiline_comment|/* seek is 16 times more expensive */
multiline_comment|/*&n; * how many times reads are allowed to starve writes&n; */
DECL|variable|writes_starved
r_static
r_int
id|writes_starved
op_assign
l_int|2
suffix:semicolon
DECL|variable|deadline_hash_shift
r_static
r_const
r_int
id|deadline_hash_shift
op_assign
l_int|8
suffix:semicolon
DECL|macro|DL_HASH_BLOCK
mdefine_line|#define DL_HASH_BLOCK(sec)&t;((sec) &gt;&gt; 3)
DECL|macro|DL_HASH_FN
mdefine_line|#define DL_HASH_FN(sec)&t;&t;(hash_long(DL_HASH_BLOCK((sec)), deadline_hash_shift))
DECL|macro|DL_HASH_ENTRIES
mdefine_line|#define DL_HASH_ENTRIES&t;&t;(1 &lt;&lt; deadline_hash_shift)
DECL|macro|DL_INVALIDATE_HASH
mdefine_line|#define DL_INVALIDATE_HASH(dd)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (!++(dd)-&gt;hash_valid_count)&t;&t;&bslash;&n;&t;&t;&t;(dd)-&gt;hash_valid_count = 1;&t;&bslash;&n;&t;} while (0)
DECL|struct|deadline_data
r_struct
id|deadline_data
(brace
multiline_comment|/*&n;&t; * run time data&n;&t; */
DECL|member|sort_list
r_struct
id|list_head
id|sort_list
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* sorted listed */
DECL|member|read_fifo
r_struct
id|list_head
id|read_fifo
suffix:semicolon
multiline_comment|/* fifo list */
DECL|member|dispatch
r_struct
id|list_head
op_star
id|dispatch
suffix:semicolon
multiline_comment|/* driver dispatch queue */
DECL|member|hash
r_struct
id|list_head
op_star
id|hash
suffix:semicolon
multiline_comment|/* request hash */
DECL|member|last_sector
id|sector_t
id|last_sector
suffix:semicolon
multiline_comment|/* last sector sent to drive */
DECL|member|hash_valid_count
r_int
r_int
id|hash_valid_count
suffix:semicolon
multiline_comment|/* barrier hash count */
DECL|member|starved
r_int
r_int
id|starved
suffix:semicolon
multiline_comment|/* writes starved */
multiline_comment|/*&n;&t; * settings that change how the i/o scheduler behaves&n;&t; */
DECL|member|fifo_batch
r_int
r_int
id|fifo_batch
suffix:semicolon
DECL|member|read_expire
r_int
r_int
id|read_expire
suffix:semicolon
DECL|member|seek_cost
r_int
r_int
id|seek_cost
suffix:semicolon
DECL|member|writes_starved
r_int
r_int
id|writes_starved
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * pre-request data.&n; */
DECL|struct|deadline_rq
r_struct
id|deadline_rq
(brace
DECL|member|fifo
r_struct
id|list_head
id|fifo
suffix:semicolon
DECL|member|hash
r_struct
id|list_head
id|hash
suffix:semicolon
DECL|member|hash_valid_count
r_int
r_int
id|hash_valid_count
suffix:semicolon
DECL|member|request
r_struct
id|request
op_star
id|request
suffix:semicolon
DECL|member|expires
r_int
r_int
id|expires
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|drq_pool
r_static
id|kmem_cache_t
op_star
id|drq_pool
suffix:semicolon
DECL|macro|RQ_DATA
mdefine_line|#define RQ_DATA(rq)&t;((struct deadline_rq *) (rq)-&gt;elevator_private)
multiline_comment|/*&n; * rq hash&n; */
DECL|function|__deadline_del_rq_hash
r_static
r_inline
r_void
id|__deadline_del_rq_hash
c_func
(paren
r_struct
id|deadline_rq
op_star
id|drq
)paren
(brace
id|drq-&gt;hash_valid_count
op_assign
l_int|0
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|drq-&gt;hash
)paren
suffix:semicolon
)brace
DECL|macro|ON_HASH
mdefine_line|#define ON_HASH(drq)&t;(drq)-&gt;hash_valid_count
DECL|function|deadline_del_rq_hash
r_static
r_inline
r_void
id|deadline_del_rq_hash
c_func
(paren
r_struct
id|deadline_rq
op_star
id|drq
)paren
(brace
r_if
c_cond
(paren
id|ON_HASH
c_func
(paren
id|drq
)paren
)paren
id|__deadline_del_rq_hash
c_func
(paren
id|drq
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|deadline_add_rq_hash
id|deadline_add_rq_hash
c_func
(paren
r_struct
id|deadline_data
op_star
id|dd
comma
r_struct
id|deadline_rq
op_star
id|drq
)paren
(brace
r_struct
id|request
op_star
id|rq
op_assign
id|drq-&gt;request
suffix:semicolon
id|BUG_ON
c_func
(paren
id|ON_HASH
c_func
(paren
id|drq
)paren
)paren
suffix:semicolon
id|drq-&gt;hash_valid_count
op_assign
id|dd-&gt;hash_valid_count
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|drq-&gt;hash
comma
op_amp
id|dd-&gt;hash
(braket
id|DL_HASH_FN
c_func
(paren
id|rq-&gt;sector
op_plus
id|rq-&gt;nr_sectors
)paren
)braket
)paren
suffix:semicolon
)brace
DECL|macro|list_entry_hash
mdefine_line|#define list_entry_hash(ptr)&t;list_entry((ptr), struct deadline_rq, hash)
r_static
r_struct
id|request
op_star
DECL|function|deadline_find_hash
id|deadline_find_hash
c_func
(paren
r_struct
id|deadline_data
op_star
id|dd
comma
id|sector_t
id|offset
)paren
(brace
r_struct
id|list_head
op_star
id|hash_list
op_assign
op_amp
id|dd-&gt;hash
(braket
id|DL_HASH_FN
c_func
(paren
id|offset
)paren
)braket
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
comma
op_star
id|next
op_assign
id|hash_list-&gt;next
suffix:semicolon
r_struct
id|deadline_rq
op_star
id|drq
suffix:semicolon
r_struct
id|request
op_star
id|rq
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
(paren
id|entry
op_assign
id|next
)paren
op_ne
id|hash_list
)paren
(brace
id|next
op_assign
id|entry-&gt;next
suffix:semicolon
id|drq
op_assign
id|list_entry_hash
c_func
(paren
id|entry
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|drq-&gt;hash_valid_count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rq_mergeable
c_func
(paren
id|drq-&gt;request
)paren
op_logical_or
id|drq-&gt;hash_valid_count
op_ne
id|dd-&gt;hash_valid_count
)paren
(brace
id|__deadline_del_rq_hash
c_func
(paren
id|drq
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|drq-&gt;request-&gt;sector
op_plus
id|drq-&gt;request-&gt;nr_sectors
op_eq
id|offset
)paren
(brace
id|rq
op_assign
id|drq-&gt;request
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|rq
suffix:semicolon
)brace
DECL|function|deadline_get_last_sector
r_static
id|sector_t
id|deadline_get_last_sector
c_func
(paren
r_struct
id|deadline_data
op_star
id|dd
)paren
(brace
id|sector_t
id|last_sec
op_assign
id|dd-&gt;last_sector
suffix:semicolon
multiline_comment|/*&n;&t; * if dispatch is non-empty, disregard last_sector and check last one&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|dd-&gt;dispatch
)paren
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
id|dd-&gt;dispatch-&gt;prev
)paren
suffix:semicolon
id|last_sec
op_assign
id|__rq-&gt;sector
op_plus
id|__rq-&gt;nr_sectors
suffix:semicolon
)brace
r_return
id|last_sec
suffix:semicolon
)brace
r_static
r_int
DECL|function|deadline_merge
id|deadline_merge
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
id|deadline_data
op_star
id|dd
op_assign
id|q-&gt;elevator.elevator_data
suffix:semicolon
r_const
r_int
id|data_dir
op_assign
id|bio_data_dir
c_func
(paren
id|bio
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
comma
op_star
id|sort_list
suffix:semicolon
r_struct
id|request
op_star
id|__rq
suffix:semicolon
r_int
id|ret
op_assign
id|ELEVATOR_NO_MERGE
suffix:semicolon
multiline_comment|/*&n;&t; * try last_merge to avoid going to hash&n;&t; */
id|ret
op_assign
id|elv_try_last_merge
c_func
(paren
id|q
comma
id|bio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|ELEVATOR_NO_MERGE
)paren
(brace
op_star
id|insert
op_assign
id|q-&gt;last_merge
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * see if the merge hash can satisfy a back merge&n;&t; */
r_if
c_cond
(paren
(paren
id|__rq
op_assign
id|deadline_find_hash
c_func
(paren
id|dd
comma
id|bio-&gt;bi_sector
)paren
)paren
)paren
(brace
id|BUG_ON
c_func
(paren
id|__rq-&gt;sector
op_plus
id|__rq-&gt;nr_sectors
op_ne
id|bio-&gt;bi_sector
)paren
suffix:semicolon
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
op_star
id|insert
op_assign
op_amp
id|__rq-&gt;queuelist
suffix:semicolon
id|ret
op_assign
id|ELEVATOR_BACK_MERGE
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * scan list from back to find insertion point.&n;&t; */
id|entry
op_assign
id|sort_list
op_assign
op_amp
id|dd-&gt;sort_list
(braket
id|data_dir
)braket
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
id|sort_list
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
id|BUG_ON
c_func
(paren
id|__rq-&gt;flags
op_amp
id|REQ_STARTED
)paren
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
multiline_comment|/*&n;&t;&t; * it&squot;s not necessary to break here, and in fact it could make&n;&t;&t; * us loose a front merge. emperical evidence shows this to&n;&t;&t; * be a big waste of cycles though, so quit scanning&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
op_star
id|insert
op_logical_and
id|bio_rq_in_between
c_func
(paren
id|bio
comma
id|__rq
comma
id|sort_list
)paren
)paren
(brace
op_star
id|insert
op_assign
op_amp
id|__rq-&gt;queuelist
suffix:semicolon
r_break
suffix:semicolon
)brace
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
multiline_comment|/*&n;&t;&t; * checking for a front merge, hash will miss those&n;&t;&t; */
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
(brace
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
r_if
c_cond
(paren
id|ret
op_ne
id|ELEVATOR_NO_MERGE
)paren
(brace
op_star
id|insert
op_assign
op_amp
id|__rq-&gt;queuelist
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n;&t; * no insertion point found, check the very front&n;&t; */
r_if
c_cond
(paren
op_logical_neg
op_star
id|insert
op_logical_and
op_logical_neg
id|list_empty
c_func
(paren
id|sort_list
)paren
)paren
(brace
id|__rq
op_assign
id|list_entry_rq
c_func
(paren
id|sort_list-&gt;next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bio-&gt;bi_sector
op_plus
id|bio_sectors
c_func
(paren
id|bio
)paren
template_param
id|deadline_get_last_sector
c_func
(paren
id|dd
)paren
)paren
op_star
id|insert
op_assign
id|sort_list
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|deadline_merged_request
r_static
r_void
id|deadline_merged_request
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
)paren
(brace
r_struct
id|deadline_data
op_star
id|dd
op_assign
id|q-&gt;elevator.elevator_data
suffix:semicolon
r_struct
id|deadline_rq
op_star
id|drq
op_assign
id|RQ_DATA
c_func
(paren
id|req
)paren
suffix:semicolon
id|deadline_del_rq_hash
c_func
(paren
id|drq
)paren
suffix:semicolon
id|deadline_add_rq_hash
c_func
(paren
id|dd
comma
id|drq
)paren
suffix:semicolon
id|q-&gt;last_merge
op_assign
op_amp
id|req-&gt;queuelist
suffix:semicolon
)brace
r_static
r_void
DECL|function|deadline_merge_request
id|deadline_merge_request
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
r_struct
id|deadline_data
op_star
id|dd
op_assign
id|q-&gt;elevator.elevator_data
suffix:semicolon
r_struct
id|deadline_rq
op_star
id|drq
op_assign
id|RQ_DATA
c_func
(paren
id|req
)paren
suffix:semicolon
r_struct
id|deadline_rq
op_star
id|dnext
op_assign
id|RQ_DATA
c_func
(paren
id|next
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|drq
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|dnext
)paren
suffix:semicolon
id|deadline_del_rq_hash
c_func
(paren
id|drq
)paren
suffix:semicolon
id|deadline_add_rq_hash
c_func
(paren
id|dd
comma
id|drq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * if dnext expires before drq, assign it&squot;s expire time to drq&n;&t; * and move into dnext position (dnext will be deleted) in fifo&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|drq-&gt;fifo
)paren
op_logical_and
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dnext-&gt;fifo
)paren
)paren
(brace
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|dnext-&gt;expires
comma
id|drq-&gt;expires
)paren
)paren
(brace
id|list_move
c_func
(paren
op_amp
id|drq-&gt;fifo
comma
op_amp
id|dnext-&gt;fifo
)paren
suffix:semicolon
id|drq-&gt;expires
op_assign
id|dnext-&gt;expires
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * move request from sort list to dispatch queue. maybe remove from rq hash&n; * here too?&n; */
r_static
r_inline
r_void
DECL|function|deadline_move_to_dispatch
id|deadline_move_to_dispatch
c_func
(paren
r_struct
id|deadline_data
op_star
id|dd
comma
r_struct
id|request
op_star
id|rq
)paren
(brace
r_struct
id|deadline_rq
op_star
id|drq
op_assign
id|RQ_DATA
c_func
(paren
id|rq
)paren
suffix:semicolon
id|list_move_tail
c_func
(paren
op_amp
id|rq-&gt;queuelist
comma
id|dd-&gt;dispatch
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|drq-&gt;fifo
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * move along sort list and move entries to dispatch queue, starting from rq&n; */
DECL|function|deadline_move_requests
r_static
r_void
id|deadline_move_requests
c_func
(paren
r_struct
id|deadline_data
op_star
id|dd
comma
r_struct
id|request
op_star
id|rq
)paren
(brace
r_struct
id|list_head
op_star
id|sort_head
op_assign
op_amp
id|dd-&gt;sort_list
(braket
id|rq_data_dir
c_func
(paren
id|rq
)paren
)braket
suffix:semicolon
id|sector_t
id|last_sec
op_assign
id|deadline_get_last_sector
c_func
(paren
id|dd
)paren
suffix:semicolon
r_int
id|batch_count
op_assign
id|dd-&gt;fifo_batch
suffix:semicolon
r_do
(brace
r_struct
id|list_head
op_star
id|nxt
op_assign
id|rq-&gt;queuelist.next
suffix:semicolon
r_int
id|this_rq_cost
suffix:semicolon
multiline_comment|/*&n;&t;&t; * take it off the sort and fifo list, move&n;&t;&t; * to dispatch queue&n;&t;&t; */
id|deadline_move_to_dispatch
c_func
(paren
id|dd
comma
id|rq
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * if this is the last entry, don&squot;t bother doing accounting&n;&t;&t; */
r_if
c_cond
(paren
id|nxt
op_eq
id|sort_head
)paren
r_break
suffix:semicolon
id|this_rq_cost
op_assign
id|dd-&gt;seek_cost
suffix:semicolon
r_if
c_cond
(paren
id|rq-&gt;sector
op_eq
id|last_sec
)paren
id|this_rq_cost
op_assign
(paren
id|rq-&gt;nr_sectors
op_plus
l_int|255
)paren
op_rshift
l_int|8
suffix:semicolon
id|batch_count
op_sub_assign
id|this_rq_cost
suffix:semicolon
r_if
c_cond
(paren
id|batch_count
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|last_sec
op_assign
id|rq-&gt;sector
op_plus
id|rq-&gt;nr_sectors
suffix:semicolon
id|rq
op_assign
id|list_entry_rq
c_func
(paren
id|nxt
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * returns 0 if there are no expired reads on the fifo, 1 otherwise&n; */
DECL|macro|list_entry_fifo
mdefine_line|#define list_entry_fifo(ptr)&t;list_entry((ptr), struct deadline_rq, fifo)
DECL|function|deadline_check_fifo
r_static
r_inline
r_int
id|deadline_check_fifo
c_func
(paren
r_struct
id|deadline_data
op_star
id|dd
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
id|dd-&gt;read_fifo
)paren
)paren
(brace
r_struct
id|deadline_rq
op_star
id|drq
op_assign
id|list_entry_fifo
c_func
(paren
id|dd-&gt;read_fifo.next
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * drq is expired!&n;&t;&t; */
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|drq-&gt;expires
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|deadline_next_request
r_static
r_struct
id|request
op_star
id|deadline_next_request
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
(brace
r_struct
id|deadline_data
op_star
id|dd
op_assign
id|q-&gt;elevator.elevator_data
suffix:semicolon
r_struct
id|deadline_rq
op_star
id|drq
suffix:semicolon
r_struct
id|list_head
op_star
id|nxt
suffix:semicolon
r_struct
id|request
op_star
id|rq
suffix:semicolon
r_int
id|writes
suffix:semicolon
multiline_comment|/*&n;&t; * if still requests on the dispatch queue, just grab the first one&n;&t; */
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
(brace
id|dispatch
suffix:colon
id|rq
op_assign
id|list_entry_rq
c_func
(paren
id|q-&gt;queue_head.next
)paren
suffix:semicolon
id|dd-&gt;last_sector
op_assign
id|rq-&gt;sector
op_plus
id|rq-&gt;nr_sectors
suffix:semicolon
r_return
id|rq
suffix:semicolon
)brace
id|writes
op_assign
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dd-&gt;sort_list
(braket
id|WRITE
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * if we have expired entries on the fifo list, move some to dispatch&n;&t; */
r_if
c_cond
(paren
id|deadline_check_fifo
c_func
(paren
id|dd
)paren
)paren
(brace
r_if
c_cond
(paren
id|writes
op_logical_and
(paren
id|dd-&gt;starved
op_increment
op_ge
id|dd-&gt;writes_starved
)paren
)paren
r_goto
id|dispatch_writes
suffix:semicolon
id|nxt
op_assign
id|dd-&gt;read_fifo.next
suffix:semicolon
id|drq
op_assign
id|list_entry_fifo
c_func
(paren
id|nxt
)paren
suffix:semicolon
id|deadline_move_requests
c_func
(paren
id|dd
comma
id|drq-&gt;request
)paren
suffix:semicolon
r_goto
id|dispatch
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dd-&gt;sort_list
(braket
id|READ
)braket
)paren
)paren
(brace
r_if
c_cond
(paren
id|writes
op_logical_and
(paren
id|dd-&gt;starved
op_increment
op_ge
id|dd-&gt;writes_starved
)paren
)paren
r_goto
id|dispatch_writes
suffix:semicolon
id|nxt
op_assign
id|dd-&gt;sort_list
(braket
id|READ
)braket
dot
id|next
suffix:semicolon
id|deadline_move_requests
c_func
(paren
id|dd
comma
id|list_entry_rq
c_func
(paren
id|nxt
)paren
)paren
suffix:semicolon
r_goto
id|dispatch
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * either there are no reads expired or on sort list, or the reads&n;&t; * have starved writes for too long. dispatch some writes&n;&t; */
r_if
c_cond
(paren
id|writes
)paren
(brace
id|dispatch_writes
suffix:colon
id|nxt
op_assign
id|dd-&gt;sort_list
(braket
id|WRITE
)braket
dot
id|next
suffix:semicolon
id|deadline_move_requests
c_func
(paren
id|dd
comma
id|list_entry_rq
c_func
(paren
id|nxt
)paren
)paren
suffix:semicolon
id|dd-&gt;starved
op_assign
l_int|0
suffix:semicolon
r_goto
id|dispatch
suffix:semicolon
)brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dd-&gt;sort_list
(braket
id|READ
)braket
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|writes
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_void
DECL|function|deadline_add_request
id|deadline_add_request
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
r_struct
id|deadline_data
op_star
id|dd
op_assign
id|q-&gt;elevator.elevator_data
suffix:semicolon
r_struct
id|deadline_rq
op_star
id|drq
op_assign
id|RQ_DATA
c_func
(paren
id|rq
)paren
suffix:semicolon
r_const
r_int
id|data_dir
op_assign
id|rq_data_dir
c_func
(paren
id|rq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * flush hash on barrier insert, as not to allow merges before a&n;&t; * barrier.&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|rq-&gt;flags
op_amp
id|REQ_HARDBARRIER
)paren
)paren
(brace
id|DL_INVALIDATE_HASH
c_func
(paren
id|dd
)paren
suffix:semicolon
id|q-&gt;last_merge
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * add to sort list&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|insert_here
)paren
id|insert_here
op_assign
id|dd-&gt;sort_list
(braket
id|data_dir
)braket
dot
id|prev
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|rq-&gt;queuelist
comma
id|insert_here
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
(paren
id|rq-&gt;flags
op_amp
id|REQ_CMD
)paren
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|rq_mergeable
c_func
(paren
id|rq
)paren
)paren
(brace
id|deadline_add_rq_hash
c_func
(paren
id|dd
comma
id|drq
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|data_dir
op_eq
id|READ
)paren
(brace
multiline_comment|/*&n;&t;&t; * set expire time and add to fifo list&n;&t;&t; */
id|drq-&gt;expires
op_assign
id|jiffies
op_plus
id|dd-&gt;read_expire
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|drq-&gt;fifo
comma
op_amp
id|dd-&gt;read_fifo
)paren
suffix:semicolon
)brace
)brace
DECL|function|deadline_remove_request
r_static
r_void
id|deadline_remove_request
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
r_struct
id|deadline_rq
op_star
id|drq
op_assign
id|RQ_DATA
c_func
(paren
id|rq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drq
)paren
(brace
id|list_del_init
c_func
(paren
op_amp
id|drq-&gt;fifo
)paren
suffix:semicolon
id|deadline_del_rq_hash
c_func
(paren
id|drq
)paren
suffix:semicolon
)brace
)brace
DECL|function|deadline_queue_empty
r_static
r_int
id|deadline_queue_empty
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
(brace
r_struct
id|deadline_data
op_star
id|dd
op_assign
id|q-&gt;elevator.elevator_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dd-&gt;sort_list
(braket
id|WRITE
)braket
)paren
op_logical_or
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dd-&gt;sort_list
(braket
id|READ
)braket
)paren
op_logical_or
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|q-&gt;queue_head
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dd-&gt;read_fifo
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_struct
id|list_head
op_star
DECL|function|deadline_get_sort_head
id|deadline_get_sort_head
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
r_struct
id|deadline_data
op_star
id|dd
op_assign
id|q-&gt;elevator.elevator_data
suffix:semicolon
r_return
op_amp
id|dd-&gt;sort_list
(braket
id|rq_data_dir
c_func
(paren
id|rq
)paren
)braket
suffix:semicolon
)brace
DECL|function|deadline_exit
r_static
r_void
id|deadline_exit
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
r_struct
id|deadline_data
op_star
id|dd
op_assign
id|e-&gt;elevator_data
suffix:semicolon
r_struct
id|deadline_rq
op_star
id|drq
suffix:semicolon
r_struct
id|request
op_star
id|rq
suffix:semicolon
r_int
id|i
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dd-&gt;read_fifo
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dd-&gt;sort_list
(braket
id|READ
)braket
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dd-&gt;sort_list
(braket
id|WRITE
)braket
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|READ
suffix:semicolon
id|i
op_le
id|WRITE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|request_list
op_star
id|rl
op_assign
op_amp
id|q-&gt;rq
(braket
id|i
)braket
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
op_assign
op_amp
id|rl-&gt;free
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|rl-&gt;free
)paren
)paren
r_continue
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
id|rl-&gt;free
)paren
(brace
id|rq
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
(paren
id|drq
op_assign
id|RQ_DATA
c_func
(paren
id|rq
)paren
)paren
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|rq-&gt;elevator_private
op_assign
l_int|NULL
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|drq_pool
comma
id|drq
)paren
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|dd-&gt;hash
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dd
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * initialize elevator private data (deadline_data), and alloc a drq for&n; * each request on the free lists&n; */
DECL|function|deadline_init
r_static
r_int
id|deadline_init
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
r_struct
id|deadline_data
op_star
id|dd
suffix:semicolon
r_struct
id|deadline_rq
op_star
id|drq
suffix:semicolon
r_struct
id|request
op_star
id|rq
suffix:semicolon
r_int
id|i
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drq_pool
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|dd
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|dd
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dd
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|dd
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|dd
)paren
)paren
suffix:semicolon
id|dd-&gt;hash
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|list_head
)paren
op_star
id|DL_HASH_ENTRIES
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dd-&gt;hash
)paren
(brace
id|kfree
c_func
(paren
id|dd
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|DL_HASH_ENTRIES
suffix:semicolon
id|i
op_increment
)paren
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dd-&gt;hash
(braket
id|i
)braket
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dd-&gt;read_fifo
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dd-&gt;sort_list
(braket
id|READ
)braket
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dd-&gt;sort_list
(braket
id|WRITE
)braket
)paren
suffix:semicolon
id|dd-&gt;dispatch
op_assign
op_amp
id|q-&gt;queue_head
suffix:semicolon
id|dd-&gt;fifo_batch
op_assign
id|fifo_batch
suffix:semicolon
id|dd-&gt;read_expire
op_assign
id|read_expire
suffix:semicolon
id|dd-&gt;seek_cost
op_assign
id|seek_cost
suffix:semicolon
id|dd-&gt;hash_valid_count
op_assign
l_int|1
suffix:semicolon
id|dd-&gt;writes_starved
op_assign
id|writes_starved
suffix:semicolon
id|e-&gt;elevator_data
op_assign
id|dd
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|READ
suffix:semicolon
id|i
op_le
id|WRITE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|request_list
op_star
id|rl
op_assign
op_amp
id|q-&gt;rq
(braket
id|i
)braket
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
op_assign
op_amp
id|rl-&gt;free
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|rl-&gt;free
)paren
)paren
r_continue
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
id|rl-&gt;free
)paren
(brace
id|rq
op_assign
id|list_entry_rq
c_func
(paren
id|entry
)paren
suffix:semicolon
id|drq
op_assign
id|kmem_cache_alloc
c_func
(paren
id|drq_pool
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drq
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_break
suffix:semicolon
)brace
id|memset
c_func
(paren
id|drq
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|drq
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|drq-&gt;fifo
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|drq-&gt;hash
)paren
suffix:semicolon
id|drq-&gt;request
op_assign
id|rq
suffix:semicolon
id|rq-&gt;elevator_private
op_assign
id|drq
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ret
)paren
id|deadline_exit
c_func
(paren
id|q
comma
id|e
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|deadline_slab_setup
r_static
r_int
id|__init
id|deadline_slab_setup
c_func
(paren
r_void
)paren
(brace
id|drq_pool
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;deadline_drq&quot;
comma
r_sizeof
(paren
r_struct
id|deadline_rq
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drq_pool
)paren
id|panic
c_func
(paren
l_string|&quot;deadline: can&squot;t init slab pool&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|deadline_slab_setup
id|subsys_initcall
c_func
(paren
id|deadline_slab_setup
)paren
suffix:semicolon
DECL|variable|iosched_deadline
id|elevator_t
id|iosched_deadline
op_assign
(brace
dot
id|elevator_merge_fn
op_assign
id|deadline_merge
comma
dot
id|elevator_merged_fn
op_assign
id|deadline_merged_request
comma
dot
id|elevator_merge_req_fn
op_assign
id|deadline_merge_request
comma
dot
id|elevator_next_req_fn
op_assign
id|deadline_next_request
comma
dot
id|elevator_add_req_fn
op_assign
id|deadline_add_request
comma
dot
id|elevator_remove_req_fn
op_assign
id|deadline_remove_request
comma
dot
id|elevator_queue_empty_fn
op_assign
id|deadline_queue_empty
comma
dot
id|elevator_get_sort_head_fn
op_assign
id|deadline_get_sort_head
comma
dot
id|elevator_init_fn
op_assign
id|deadline_init
comma
dot
id|elevator_exit_fn
op_assign
id|deadline_exit
comma
)brace
suffix:semicolon
DECL|variable|iosched_deadline
id|EXPORT_SYMBOL
c_func
(paren
id|iosched_deadline
)paren
suffix:semicolon
eof
