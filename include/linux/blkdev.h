macro_line|#ifndef _LINUX_BLKDEV_H
DECL|macro|_LINUX_BLKDEV_H
mdefine_line|#define _LINUX_BLKDEV_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/backing-dev.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/mempool.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
r_struct
id|request_queue
suffix:semicolon
DECL|typedef|request_queue_t
r_typedef
r_struct
id|request_queue
id|request_queue_t
suffix:semicolon
r_struct
id|elevator_s
suffix:semicolon
DECL|typedef|elevator_t
r_typedef
r_struct
id|elevator_s
id|elevator_t
suffix:semicolon
r_struct
id|request_pm_state
suffix:semicolon
DECL|macro|BLKDEV_MIN_RQ
mdefine_line|#define BLKDEV_MIN_RQ&t;4
DECL|macro|BLKDEV_MAX_RQ
mdefine_line|#define BLKDEV_MAX_RQ&t;128
DECL|struct|request_list
r_struct
id|request_list
(brace
DECL|member|count
r_int
id|count
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|rq_pool
id|mempool_t
op_star
id|rq_pool
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * try to put the fields that are referenced together in the same cacheline&n; */
DECL|struct|request
r_struct
id|request
(brace
DECL|member|queuelist
r_struct
id|list_head
id|queuelist
suffix:semicolon
multiline_comment|/* looking for -&gt;queue? you must _not_&n;&t;&t;&t;&t;     * access it directly, use&n;&t;&t;&t;&t;     * blkdev_dequeue_request! */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* see REQ_ bits below */
multiline_comment|/* Maintain bio traversal state for part by part I/O submission.&n;&t; * hard_* are block layer internals, no driver should touch them!&n;&t; */
DECL|member|sector
id|sector_t
id|sector
suffix:semicolon
multiline_comment|/* next sector to submit */
DECL|member|nr_sectors
r_int
r_int
id|nr_sectors
suffix:semicolon
multiline_comment|/* no. of sectors left to submit */
multiline_comment|/* no. of sectors left to submit in the current segment */
DECL|member|current_nr_sectors
r_int
r_int
id|current_nr_sectors
suffix:semicolon
DECL|member|hard_sector
id|sector_t
id|hard_sector
suffix:semicolon
multiline_comment|/* next sector to complete */
DECL|member|hard_nr_sectors
r_int
r_int
id|hard_nr_sectors
suffix:semicolon
multiline_comment|/* no. of sectors left to complete */
multiline_comment|/* no. of sectors left to complete in the current segment */
DECL|member|hard_cur_sectors
r_int
r_int
id|hard_cur_sectors
suffix:semicolon
multiline_comment|/* no. of segments left to submit in the current bio */
DECL|member|nr_cbio_segments
r_int
r_int
id|nr_cbio_segments
suffix:semicolon
multiline_comment|/* no. of sectors left to submit in the current bio */
DECL|member|nr_cbio_sectors
r_int
r_int
id|nr_cbio_sectors
suffix:semicolon
DECL|member|cbio
r_struct
id|bio
op_star
id|cbio
suffix:semicolon
multiline_comment|/* next bio to submit */
DECL|member|bio
r_struct
id|bio
op_star
id|bio
suffix:semicolon
multiline_comment|/* next unfinished bio to complete */
DECL|member|biotail
r_struct
id|bio
op_star
id|biotail
suffix:semicolon
DECL|member|elevator_private
r_void
op_star
id|elevator_private
suffix:semicolon
DECL|member|rq_status
r_int
id|rq_status
suffix:semicolon
multiline_comment|/* should split this into a few status bits */
DECL|member|rq_disk
r_struct
id|gendisk
op_star
id|rq_disk
suffix:semicolon
DECL|member|errors
r_int
id|errors
suffix:semicolon
DECL|member|start_time
r_int
r_int
id|start_time
suffix:semicolon
multiline_comment|/* Number of scatter-gather DMA addr+len pairs after&n;&t; * physical address coalescing is performed.&n;&t; */
DECL|member|nr_phys_segments
r_int
r_int
id|nr_phys_segments
suffix:semicolon
multiline_comment|/* Number of scatter-gather addr+len pairs after&n;&t; * physical and DMA remapping hardware coalescing is performed.&n;&t; * This is the number of scatter-gather entries the driver&n;&t; * will actually have to deal with after DMA mapping is done.&n;&t; */
DECL|member|nr_hw_segments
r_int
r_int
id|nr_hw_segments
suffix:semicolon
DECL|member|tag
r_int
id|tag
suffix:semicolon
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
DECL|member|ref_count
r_int
id|ref_count
suffix:semicolon
DECL|member|q
id|request_queue_t
op_star
id|q
suffix:semicolon
DECL|member|rl
r_struct
id|request_list
op_star
id|rl
suffix:semicolon
DECL|member|waiting
r_struct
id|completion
op_star
id|waiting
suffix:semicolon
DECL|member|special
r_void
op_star
id|special
suffix:semicolon
multiline_comment|/*&n;&t; * when request is used as a packet command carrier&n;&t; */
DECL|member|cmd_len
r_int
r_int
id|cmd_len
suffix:semicolon
DECL|member|cmd
r_int
r_char
id|cmd
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|data_len
r_int
r_int
id|data_len
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|sense_len
r_int
r_int
id|sense_len
suffix:semicolon
DECL|member|sense
r_void
op_star
id|sense
suffix:semicolon
DECL|member|timeout
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/*&n;&t; * For Power Management requests&n;&t; */
DECL|member|pm
r_struct
id|request_pm_state
op_star
id|pm
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * first three bits match BIO_RW* bits, important&n; */
DECL|enum|rq_flag_bits
r_enum
id|rq_flag_bits
(brace
DECL|enumerator|__REQ_RW
id|__REQ_RW
comma
multiline_comment|/* not set, read. set, write */
DECL|enumerator|__REQ_RW_AHEAD
id|__REQ_RW_AHEAD
comma
multiline_comment|/* READA */
DECL|enumerator|__REQ_SOFTBARRIER
id|__REQ_SOFTBARRIER
comma
multiline_comment|/* may not be passed by ioscheduler */
DECL|enumerator|__REQ_HARDBARRIER
id|__REQ_HARDBARRIER
comma
multiline_comment|/* may not be passed by drive either */
DECL|enumerator|__REQ_CMD
id|__REQ_CMD
comma
multiline_comment|/* is a regular fs rw request */
DECL|enumerator|__REQ_NOMERGE
id|__REQ_NOMERGE
comma
multiline_comment|/* don&squot;t touch this for merging */
DECL|enumerator|__REQ_STARTED
id|__REQ_STARTED
comma
multiline_comment|/* drive already may have started this one */
DECL|enumerator|__REQ_DONTPREP
id|__REQ_DONTPREP
comma
multiline_comment|/* don&squot;t call prep for this one */
DECL|enumerator|__REQ_QUEUED
id|__REQ_QUEUED
comma
multiline_comment|/* uses queueing */
multiline_comment|/*&n;&t; * for ATA/ATAPI devices&n;&t; */
DECL|enumerator|__REQ_PC
id|__REQ_PC
comma
multiline_comment|/* packet command (special) */
DECL|enumerator|__REQ_BLOCK_PC
id|__REQ_BLOCK_PC
comma
multiline_comment|/* queued down pc from block layer */
DECL|enumerator|__REQ_SENSE
id|__REQ_SENSE
comma
multiline_comment|/* sense retrival */
DECL|enumerator|__REQ_FAILED
id|__REQ_FAILED
comma
multiline_comment|/* set if the request failed */
DECL|enumerator|__REQ_QUIET
id|__REQ_QUIET
comma
multiline_comment|/* don&squot;t worry about errors */
DECL|enumerator|__REQ_SPECIAL
id|__REQ_SPECIAL
comma
multiline_comment|/* driver suplied command */
DECL|enumerator|__REQ_DRIVE_CMD
id|__REQ_DRIVE_CMD
comma
DECL|enumerator|__REQ_DRIVE_TASK
id|__REQ_DRIVE_TASK
comma
DECL|enumerator|__REQ_DRIVE_TASKFILE
id|__REQ_DRIVE_TASKFILE
comma
DECL|enumerator|__REQ_PREEMPT
id|__REQ_PREEMPT
comma
multiline_comment|/* set for &quot;ide_preempt&quot; requests */
DECL|enumerator|__REQ_PM_SUSPEND
id|__REQ_PM_SUSPEND
comma
multiline_comment|/* suspend request */
DECL|enumerator|__REQ_PM_RESUME
id|__REQ_PM_RESUME
comma
multiline_comment|/* resume request */
DECL|enumerator|__REQ_PM_SHUTDOWN
id|__REQ_PM_SHUTDOWN
comma
multiline_comment|/* shutdown request */
DECL|enumerator|__REQ_NR_BITS
id|__REQ_NR_BITS
comma
multiline_comment|/* stops here */
)brace
suffix:semicolon
DECL|macro|REQ_RW
mdefine_line|#define REQ_RW&t;&t;(1 &lt;&lt; __REQ_RW)
DECL|macro|REQ_RW_AHEAD
mdefine_line|#define REQ_RW_AHEAD&t;(1 &lt;&lt; __REQ_RW_AHEAD)
DECL|macro|REQ_SOFTBARRIER
mdefine_line|#define REQ_SOFTBARRIER&t;(1 &lt;&lt; __REQ_SOFTBARRIER)
DECL|macro|REQ_HARDBARRIER
mdefine_line|#define REQ_HARDBARRIER&t;(1 &lt;&lt; __REQ_HARDBARRIER)
DECL|macro|REQ_CMD
mdefine_line|#define REQ_CMD&t;&t;(1 &lt;&lt; __REQ_CMD)
DECL|macro|REQ_NOMERGE
mdefine_line|#define REQ_NOMERGE&t;(1 &lt;&lt; __REQ_NOMERGE)
DECL|macro|REQ_STARTED
mdefine_line|#define REQ_STARTED&t;(1 &lt;&lt; __REQ_STARTED)
DECL|macro|REQ_DONTPREP
mdefine_line|#define REQ_DONTPREP&t;(1 &lt;&lt; __REQ_DONTPREP)
DECL|macro|REQ_QUEUED
mdefine_line|#define REQ_QUEUED&t;(1 &lt;&lt; __REQ_QUEUED)
DECL|macro|REQ_PC
mdefine_line|#define REQ_PC&t;&t;(1 &lt;&lt; __REQ_PC)
DECL|macro|REQ_BLOCK_PC
mdefine_line|#define REQ_BLOCK_PC&t;(1 &lt;&lt; __REQ_BLOCK_PC)
DECL|macro|REQ_SENSE
mdefine_line|#define REQ_SENSE&t;(1 &lt;&lt; __REQ_SENSE)
DECL|macro|REQ_FAILED
mdefine_line|#define REQ_FAILED&t;(1 &lt;&lt; __REQ_FAILED)
DECL|macro|REQ_QUIET
mdefine_line|#define REQ_QUIET&t;(1 &lt;&lt; __REQ_QUIET)
DECL|macro|REQ_SPECIAL
mdefine_line|#define REQ_SPECIAL&t;(1 &lt;&lt; __REQ_SPECIAL)
DECL|macro|REQ_DRIVE_CMD
mdefine_line|#define REQ_DRIVE_CMD&t;(1 &lt;&lt; __REQ_DRIVE_CMD)
DECL|macro|REQ_DRIVE_TASK
mdefine_line|#define REQ_DRIVE_TASK&t;(1 &lt;&lt; __REQ_DRIVE_TASK)
DECL|macro|REQ_DRIVE_TASKFILE
mdefine_line|#define REQ_DRIVE_TASKFILE&t;(1 &lt;&lt; __REQ_DRIVE_TASKFILE)
DECL|macro|REQ_PREEMPT
mdefine_line|#define REQ_PREEMPT&t;(1 &lt;&lt; __REQ_PREEMPT)
DECL|macro|REQ_PM_SUSPEND
mdefine_line|#define REQ_PM_SUSPEND&t;(1 &lt;&lt; __REQ_PM_SUSPEND)
DECL|macro|REQ_PM_RESUME
mdefine_line|#define REQ_PM_RESUME&t;(1 &lt;&lt; __REQ_PM_RESUME)
DECL|macro|REQ_PM_SHUTDOWN
mdefine_line|#define REQ_PM_SHUTDOWN&t;(1 &lt;&lt; __REQ_PM_SHUTDOWN)
multiline_comment|/*&n; * State information carried for REQ_PM_SUSPEND and REQ_PM_RESUME&n; * requests. Some step values could eventually be made generic.&n; */
DECL|struct|request_pm_state
r_struct
id|request_pm_state
(brace
multiline_comment|/* PM state machine step value, currently driver specific */
DECL|member|pm_step
r_int
id|pm_step
suffix:semicolon
multiline_comment|/* requested PM state value (S1, S2, S3, S4, ...) */
DECL|member|pm_state
id|u32
id|pm_state
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* for driver use */
)brace
suffix:semicolon
macro_line|#include &lt;linux/elevator.h&gt;
DECL|typedef|merge_request_fn
r_typedef
r_int
(paren
id|merge_request_fn
)paren
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
comma
r_struct
id|bio
op_star
)paren
suffix:semicolon
DECL|typedef|merge_requests_fn
r_typedef
r_int
(paren
id|merge_requests_fn
)paren
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
DECL|typedef|request_fn_proc
r_typedef
r_void
(paren
id|request_fn_proc
)paren
(paren
id|request_queue_t
op_star
id|q
)paren
suffix:semicolon
DECL|typedef|make_request_fn
r_typedef
r_int
(paren
id|make_request_fn
)paren
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
suffix:semicolon
DECL|typedef|prep_rq_fn
r_typedef
r_int
(paren
id|prep_rq_fn
)paren
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
DECL|typedef|unplug_fn
r_typedef
r_void
(paren
id|unplug_fn
)paren
(paren
r_void
op_star
id|q
)paren
suffix:semicolon
r_struct
id|bio_vec
suffix:semicolon
DECL|typedef|merge_bvec_fn
r_typedef
r_int
(paren
id|merge_bvec_fn
)paren
(paren
id|request_queue_t
op_star
comma
r_struct
id|bio
op_star
comma
r_struct
id|bio_vec
op_star
)paren
suffix:semicolon
DECL|enum|blk_queue_state
r_enum
id|blk_queue_state
(brace
DECL|enumerator|Queue_down
id|Queue_down
comma
DECL|enumerator|Queue_up
id|Queue_up
comma
)brace
suffix:semicolon
DECL|macro|BLK_TAGS_PER_LONG
mdefine_line|#define BLK_TAGS_PER_LONG&t;(sizeof(unsigned long) * 8)
DECL|macro|BLK_TAGS_MASK
mdefine_line|#define BLK_TAGS_MASK&t;&t;(BLK_TAGS_PER_LONG - 1)
DECL|struct|blk_queue_tag
r_struct
id|blk_queue_tag
(brace
DECL|member|tag_index
r_struct
id|request
op_star
op_star
id|tag_index
suffix:semicolon
multiline_comment|/* map of busy tags */
DECL|member|tag_map
r_int
r_int
op_star
id|tag_map
suffix:semicolon
multiline_comment|/* bit map of free/busy tags */
DECL|member|busy_list
r_struct
id|list_head
id|busy_list
suffix:semicolon
multiline_comment|/* fifo list of busy tags */
DECL|member|busy
r_int
id|busy
suffix:semicolon
multiline_comment|/* current depth */
DECL|member|max_depth
r_int
id|max_depth
suffix:semicolon
multiline_comment|/* what we will send to device */
DECL|member|real_max_depth
r_int
id|real_max_depth
suffix:semicolon
multiline_comment|/* what the array can hold */
)brace
suffix:semicolon
DECL|struct|request_queue
r_struct
id|request_queue
(brace
multiline_comment|/*&n;&t; * Together with queue_head for cacheline sharing&n;&t; */
DECL|member|queue_head
r_struct
id|list_head
id|queue_head
suffix:semicolon
DECL|member|last_merge
r_struct
id|list_head
op_star
id|last_merge
suffix:semicolon
DECL|member|elevator
id|elevator_t
id|elevator
suffix:semicolon
multiline_comment|/*&n;&t; * the queue request freelist, one for reads and one for writes&n;&t; */
DECL|member|rq
r_struct
id|request_list
id|rq
suffix:semicolon
DECL|member|request_fn
id|request_fn_proc
op_star
id|request_fn
suffix:semicolon
DECL|member|back_merge_fn
id|merge_request_fn
op_star
id|back_merge_fn
suffix:semicolon
DECL|member|front_merge_fn
id|merge_request_fn
op_star
id|front_merge_fn
suffix:semicolon
DECL|member|merge_requests_fn
id|merge_requests_fn
op_star
id|merge_requests_fn
suffix:semicolon
DECL|member|make_request_fn
id|make_request_fn
op_star
id|make_request_fn
suffix:semicolon
DECL|member|prep_rq_fn
id|prep_rq_fn
op_star
id|prep_rq_fn
suffix:semicolon
DECL|member|unplug_fn
id|unplug_fn
op_star
id|unplug_fn
suffix:semicolon
DECL|member|merge_bvec_fn
id|merge_bvec_fn
op_star
id|merge_bvec_fn
suffix:semicolon
multiline_comment|/*&n;&t; * Auto-unplugging state&n;&t; */
DECL|member|unplug_timer
r_struct
id|timer_list
id|unplug_timer
suffix:semicolon
DECL|member|unplug_thresh
r_int
id|unplug_thresh
suffix:semicolon
multiline_comment|/* After this many requests */
DECL|member|unplug_delay
r_int
r_int
id|unplug_delay
suffix:semicolon
multiline_comment|/* After this many jiffies */
DECL|member|unplug_work
r_struct
id|work_struct
id|unplug_work
suffix:semicolon
DECL|member|backing_dev_info
r_struct
id|backing_dev_info
id|backing_dev_info
suffix:semicolon
multiline_comment|/*&n;&t; * The queue owner gets to use this for whatever they like.&n;&t; * ll_rw_blk doesn&squot;t touch it.&n;&t; */
DECL|member|queuedata
r_void
op_star
id|queuedata
suffix:semicolon
multiline_comment|/*&n;&t; * queue needs bounce pages for pages above this limit&n;&t; */
DECL|member|bounce_pfn
r_int
r_int
id|bounce_pfn
suffix:semicolon
DECL|member|bounce_gfp
r_int
id|bounce_gfp
suffix:semicolon
DECL|member|plug_list
r_struct
id|list_head
id|plug_list
suffix:semicolon
multiline_comment|/*&n;&t; * various queue flags, see QUEUE_* below&n;&t; */
DECL|member|queue_flags
r_int
r_int
id|queue_flags
suffix:semicolon
multiline_comment|/*&n;&t; * protects queue structures from reentrancy&n;&t; */
DECL|member|queue_lock
id|spinlock_t
op_star
id|queue_lock
suffix:semicolon
multiline_comment|/*&n;&t; * queue settings&n;&t; */
DECL|member|max_sectors
r_int
r_int
id|max_sectors
suffix:semicolon
DECL|member|max_phys_segments
r_int
r_int
id|max_phys_segments
suffix:semicolon
DECL|member|max_hw_segments
r_int
r_int
id|max_hw_segments
suffix:semicolon
DECL|member|hardsect_size
r_int
r_int
id|hardsect_size
suffix:semicolon
DECL|member|max_segment_size
r_int
r_int
id|max_segment_size
suffix:semicolon
DECL|member|seg_boundary_mask
r_int
r_int
id|seg_boundary_mask
suffix:semicolon
DECL|member|dma_alignment
r_int
r_int
id|dma_alignment
suffix:semicolon
DECL|member|queue_wait
id|wait_queue_head_t
id|queue_wait
suffix:semicolon
DECL|member|queue_tags
r_struct
id|blk_queue_tag
op_star
id|queue_tags
suffix:semicolon
multiline_comment|/*&n;&t; * sg stuff&n;&t; */
DECL|member|sg_timeout
r_int
r_int
id|sg_timeout
suffix:semicolon
DECL|member|sg_reserved_size
r_int
r_int
id|sg_reserved_size
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RQ_INACTIVE
mdefine_line|#define RQ_INACTIVE&t;&t;(-1)
DECL|macro|RQ_ACTIVE
mdefine_line|#define RQ_ACTIVE&t;&t;1
DECL|macro|RQ_SCSI_BUSY
mdefine_line|#define RQ_SCSI_BUSY&t;&t;0xffff
DECL|macro|RQ_SCSI_DONE
mdefine_line|#define RQ_SCSI_DONE&t;&t;0xfffe
DECL|macro|RQ_SCSI_DISCONNECTING
mdefine_line|#define RQ_SCSI_DISCONNECTING&t;0xffe0
DECL|macro|QUEUE_FLAG_CLUSTER
mdefine_line|#define QUEUE_FLAG_CLUSTER&t;0&t;/* cluster several segments into 1 */
DECL|macro|QUEUE_FLAG_QUEUED
mdefine_line|#define QUEUE_FLAG_QUEUED&t;1&t;/* uses generic tag queueing */
DECL|macro|QUEUE_FLAG_STOPPED
mdefine_line|#define QUEUE_FLAG_STOPPED&t;2&t;/* queue is stopped */
DECL|macro|blk_queue_plugged
mdefine_line|#define blk_queue_plugged(q)&t;!list_empty(&amp;(q)-&gt;plug_list)
DECL|macro|blk_queue_tagged
mdefine_line|#define blk_queue_tagged(q)&t;test_bit(QUEUE_FLAG_QUEUED, &amp;(q)-&gt;queue_flags)
DECL|macro|blk_fs_request
mdefine_line|#define blk_fs_request(rq)&t;((rq)-&gt;flags &amp; REQ_CMD)
DECL|macro|blk_pc_request
mdefine_line|#define blk_pc_request(rq)&t;((rq)-&gt;flags &amp; REQ_BLOCK_PC)
DECL|macro|blk_pm_suspend_request
mdefine_line|#define blk_pm_suspend_request(rq)&t;((rq)-&gt;flags &amp; REQ_PM_SUSPEND)
DECL|macro|blk_pm_resume_request
mdefine_line|#define blk_pm_resume_request(rq)&t;((rq)-&gt;flags &amp; REQ_PM_RESUME)
DECL|macro|blk_pm_request
mdefine_line|#define blk_pm_request(rq)&t;&bslash;&n;&t;((rq)-&gt;flags &amp; (REQ_PM_SUSPEND | REQ_PM_RESUME))
DECL|macro|list_entry_rq
mdefine_line|#define list_entry_rq(ptr)&t;list_entry((ptr), struct request, queuelist)
DECL|macro|rq_data_dir
mdefine_line|#define rq_data_dir(rq)&t;&t;((rq)-&gt;flags &amp; 1)
multiline_comment|/*&n; * mergeable request must not have _NOMERGE or _BARRIER bit set, nor may&n; * it already be started by driver.&n; */
DECL|macro|RQ_NOMERGE_FLAGS
mdefine_line|#define RQ_NOMERGE_FLAGS&t;&bslash;&n;&t;(REQ_NOMERGE | REQ_STARTED | REQ_HARDBARRIER | REQ_SOFTBARRIER)
DECL|macro|rq_mergeable
mdefine_line|#define rq_mergeable(rq)&t;&bslash;&n;&t;(!((rq)-&gt;flags &amp; RQ_NOMERGE_FLAGS) &amp;&amp; blk_fs_request((rq)))
multiline_comment|/*&n; * noop, requests are automagically marked as active/inactive by I/O&n; * scheduler -- see elv_next_request&n; */
DECL|macro|blk_queue_headactive
mdefine_line|#define blk_queue_headactive(q, head_active)
multiline_comment|/* current index into bio being processed for submission */
DECL|macro|blk_rq_idx
mdefine_line|#define blk_rq_idx(rq)&t;((rq)-&gt;cbio-&gt;bi_vcnt - (rq)-&gt;nr_cbio_segments)
multiline_comment|/* current bio vector being processed */
DECL|macro|blk_rq_vec
mdefine_line|#define blk_rq_vec(rq)&t;(bio_iovec_idx((rq)-&gt;cbio, blk_rq_idx(rq)))
multiline_comment|/* current offset with respect to start of the segment being submitted */
DECL|macro|blk_rq_offset
mdefine_line|#define blk_rq_offset(rq) &bslash;&n;&t;(((rq)-&gt;hard_cur_sectors - (rq)-&gt;current_nr_sectors) &lt;&lt; 9)
multiline_comment|/*&n; * temporarily mapping a (possible) highmem bio (typically for PIO transfer)&n; */
multiline_comment|/* Assumes rq-&gt;cbio != NULL */
DECL|function|rq_map_buffer
r_static
r_inline
r_char
op_star
id|rq_map_buffer
c_func
(paren
r_struct
id|request
op_star
id|rq
comma
r_int
r_int
op_star
id|flags
)paren
(brace
r_return
(paren
id|__bio_kmap_irq
c_func
(paren
id|rq-&gt;cbio
comma
id|blk_rq_idx
c_func
(paren
id|rq
)paren
comma
id|flags
)paren
op_plus
id|blk_rq_offset
c_func
(paren
id|rq
)paren
)paren
suffix:semicolon
)brace
DECL|function|rq_unmap_buffer
r_static
r_inline
r_void
id|rq_unmap_buffer
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
r_int
op_star
id|flags
)paren
(brace
id|__bio_kunmap_irq
c_func
(paren
id|buffer
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * q-&gt;prep_rq_fn return values&n; */
DECL|macro|BLKPREP_OK
mdefine_line|#define BLKPREP_OK&t;&t;0&t;/* serve it */
DECL|macro|BLKPREP_KILL
mdefine_line|#define BLKPREP_KILL&t;&t;1&t;/* fatal error, kill */
DECL|macro|BLKPREP_DEFER
mdefine_line|#define BLKPREP_DEFER&t;&t;2&t;/* leave on queue */
r_extern
r_int
r_int
id|blk_max_low_pfn
comma
id|blk_max_pfn
suffix:semicolon
multiline_comment|/*&n; * standard bounce addresses:&n; *&n; * BLK_BOUNCE_HIGH&t;: bounce all highmem pages&n; * BLK_BOUNCE_ANY&t;: don&squot;t bounce anything&n; * BLK_BOUNCE_ISA&t;: bounce pages above ISA DMA boundary&n; */
DECL|macro|BLK_BOUNCE_HIGH
mdefine_line|#define BLK_BOUNCE_HIGH&t;&t;((u64)blk_max_low_pfn &lt;&lt; PAGE_SHIFT)
DECL|macro|BLK_BOUNCE_ANY
mdefine_line|#define BLK_BOUNCE_ANY&t;&t;((u64)blk_max_pfn &lt;&lt; PAGE_SHIFT)
DECL|macro|BLK_BOUNCE_ISA
mdefine_line|#define BLK_BOUNCE_ISA&t;&t;(ISA_DMA_THRESHOLD)
macro_line|#ifdef CONFIG_MMU
r_extern
r_int
id|init_emergency_isa_pool
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_bounce
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|bio
op_star
op_star
id|bio
)paren
suffix:semicolon
macro_line|#else
DECL|function|init_emergency_isa_pool
r_static
r_inline
r_int
id|init_emergency_isa_pool
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|blk_queue_bounce
r_static
r_inline
r_void
id|blk_queue_bounce
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|bio
op_star
op_star
id|bio
)paren
(brace
)brace
macro_line|#endif /* CONFIG_MMU */
DECL|macro|rq_for_each_bio
mdefine_line|#define rq_for_each_bio(bio, rq)&t;&bslash;&n;&t;if ((rq-&gt;bio))&t;&t;&t;&bslash;&n;&t;&t;for (bio = (rq)-&gt;bio; bio; bio = bio-&gt;bi_next)
DECL|struct|sec_size
r_struct
id|sec_size
(brace
DECL|member|block_size
r_int
id|block_size
suffix:semicolon
DECL|member|block_size_bits
r_int
id|block_size_bits
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|register_disk
c_func
(paren
r_struct
id|gendisk
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|generic_make_request
c_func
(paren
r_struct
id|bio
op_star
id|bio
)paren
suffix:semicolon
r_extern
r_void
id|blk_put_request
c_func
(paren
r_struct
id|request
op_star
)paren
suffix:semicolon
r_extern
r_void
id|blk_attempt_remerge
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__blk_attempt_remerge
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|request
op_star
id|blk_get_request
c_func
(paren
id|request_queue_t
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|blk_put_request
c_func
(paren
r_struct
id|request
op_star
)paren
suffix:semicolon
r_extern
r_void
id|blk_insert_request
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
comma
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|blk_plug_device
c_func
(paren
id|request_queue_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|blk_remove_plug
c_func
(paren
id|request_queue_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|blk_recount_segments
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|bio
op_star
)paren
suffix:semicolon
r_extern
r_inline
r_int
id|blk_phys_contig_segment
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|bio
op_star
comma
r_struct
id|bio
op_star
)paren
suffix:semicolon
r_extern
r_inline
r_int
id|blk_hw_contig_segment
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|bio
op_star
comma
r_struct
id|bio
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_cmd_ioctl
c_func
(paren
r_struct
id|block_device
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|blk_start_queue
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
suffix:semicolon
r_extern
r_void
id|blk_stop_queue
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
suffix:semicolon
r_extern
r_void
id|__blk_stop_queue
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
suffix:semicolon
r_extern
r_void
id|blk_run_queue
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
suffix:semicolon
DECL|function|bdev_get_queue
r_static
r_inline
id|request_queue_t
op_star
id|bdev_get_queue
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
r_return
id|bdev-&gt;bd_disk-&gt;queue
suffix:semicolon
)brace
multiline_comment|/*&n; * end_request() and friends. Must be called with the request queue spinlock&n; * acquired. All functions called within end_request() _must_be_ atomic.&n; *&n; * Several drivers define their own end_request and call&n; * end_that_request_first() and end_that_request_last()&n; * for parts of the original function. This prevents&n; * code duplication in drivers.&n; */
r_extern
r_int
id|end_that_request_first
c_func
(paren
r_struct
id|request
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|end_that_request_chunk
c_func
(paren
r_struct
id|request
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|end_that_request_last
c_func
(paren
r_struct
id|request
op_star
)paren
suffix:semicolon
r_extern
r_int
id|process_that_request_first
c_func
(paren
r_struct
id|request
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|end_request
c_func
(paren
r_struct
id|request
op_star
id|req
comma
r_int
id|uptodate
)paren
suffix:semicolon
DECL|function|blkdev_dequeue_request
r_static
r_inline
r_void
id|blkdev_dequeue_request
c_func
(paren
r_struct
id|request
op_star
id|req
)paren
(brace
id|BUG_ON
c_func
(paren
id|list_empty
c_func
(paren
op_amp
id|req-&gt;queuelist
)paren
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|req-&gt;queuelist
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;q
)paren
id|elv_remove_request
c_func
(paren
id|req-&gt;q
comma
id|req
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * get ready for proper ref counting&n; */
DECL|macro|blk_put_queue
mdefine_line|#define blk_put_queue(q)&t;do { } while (0)
multiline_comment|/*&n; * Access functions for manipulating queue properties&n; */
r_extern
r_int
id|blk_init_queue
c_func
(paren
id|request_queue_t
op_star
comma
id|request_fn_proc
op_star
comma
id|spinlock_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|blk_cleanup_queue
c_func
(paren
id|request_queue_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_make_request
c_func
(paren
id|request_queue_t
op_star
comma
id|make_request_fn
op_star
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_bounce_limit
c_func
(paren
id|request_queue_t
op_star
comma
id|u64
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_max_sectors
c_func
(paren
id|request_queue_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_max_phys_segments
c_func
(paren
id|request_queue_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_max_hw_segments
c_func
(paren
id|request_queue_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_max_segment_size
c_func
(paren
id|request_queue_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_hardsect_size
c_func
(paren
id|request_queue_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_segment_boundary
c_func
(paren
id|request_queue_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_prep_rq
c_func
(paren
id|request_queue_t
op_star
comma
id|prep_rq_fn
op_star
id|pfn
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_merge_bvec
c_func
(paren
id|request_queue_t
op_star
comma
id|merge_bvec_fn
op_star
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_dma_alignment
c_func
(paren
id|request_queue_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|backing_dev_info
op_star
id|blk_get_backing_dev_info
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
)paren
suffix:semicolon
r_extern
r_int
id|blk_rq_map_sg
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
comma
r_struct
id|scatterlist
op_star
)paren
suffix:semicolon
r_extern
r_void
id|blk_dump_rq_flags
c_func
(paren
r_struct
id|request
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|generic_unplug_device
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|nr_blockdev_pages
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * tag stuff&n; */
DECL|macro|blk_queue_tag_depth
mdefine_line|#define blk_queue_tag_depth(q)&t;&t;((q)-&gt;queue_tags-&gt;busy)
DECL|macro|blk_queue_tag_queue
mdefine_line|#define blk_queue_tag_queue(q)&t;&t;((q)-&gt;queue_tags-&gt;busy &lt; (q)-&gt;queue_tags-&gt;max_depth)
DECL|macro|blk_rq_tagged
mdefine_line|#define blk_rq_tagged(rq)&t;&t;((rq)-&gt;flags &amp; REQ_QUEUED)
r_extern
r_int
id|blk_queue_start_tag
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|request
op_star
id|blk_queue_find_tag
c_func
(paren
id|request_queue_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_end_tag
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
r_extern
r_int
id|blk_queue_init_tags
c_func
(paren
id|request_queue_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_free_tags
c_func
(paren
id|request_queue_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|blk_queue_resize_tags
c_func
(paren
id|request_queue_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_invalidate_tags
c_func
(paren
id|request_queue_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|blk_congestion_wait
c_func
(paren
r_int
id|rw
comma
r_int
id|timeout
)paren
suffix:semicolon
r_extern
r_void
id|blk_rq_bio_prep
c_func
(paren
id|request_queue_t
op_star
comma
r_struct
id|request
op_star
comma
r_struct
id|bio
op_star
)paren
suffix:semicolon
r_extern
r_void
id|blk_rq_prep_restart
c_func
(paren
r_struct
id|request
op_star
)paren
suffix:semicolon
DECL|macro|MAX_PHYS_SEGMENTS
mdefine_line|#define MAX_PHYS_SEGMENTS 128
DECL|macro|MAX_HW_SEGMENTS
mdefine_line|#define MAX_HW_SEGMENTS 128
DECL|macro|MAX_SECTORS
mdefine_line|#define MAX_SECTORS 255
DECL|macro|MAX_SEGMENT_SIZE
mdefine_line|#define MAX_SEGMENT_SIZE&t;65536
DECL|macro|blkdev_entry_to_request
mdefine_line|#define blkdev_entry_to_request(entry) list_entry((entry), struct request, queuelist)
r_extern
r_void
id|drive_stat_acct
c_func
(paren
r_struct
id|request
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|function|queue_hardsect_size
r_static
r_inline
r_int
id|queue_hardsect_size
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
(brace
r_int
id|retval
op_assign
l_int|512
suffix:semicolon
r_if
c_cond
(paren
id|q
op_logical_and
id|q-&gt;hardsect_size
)paren
id|retval
op_assign
id|q-&gt;hardsect_size
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|bdev_hardsect_size
r_static
r_inline
r_int
id|bdev_hardsect_size
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
r_return
id|queue_hardsect_size
c_func
(paren
id|bdev_get_queue
c_func
(paren
id|bdev
)paren
)paren
suffix:semicolon
)brace
DECL|function|queue_dma_alignment
r_static
r_inline
r_int
id|queue_dma_alignment
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
(brace
r_int
id|retval
op_assign
l_int|511
suffix:semicolon
r_if
c_cond
(paren
id|q
op_logical_and
id|q-&gt;dma_alignment
)paren
id|retval
op_assign
id|q-&gt;dma_alignment
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|bdev_dma_aligment
r_static
r_inline
r_int
id|bdev_dma_aligment
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
r_return
id|queue_dma_alignment
c_func
(paren
id|bdev_get_queue
c_func
(paren
id|bdev
)paren
)paren
suffix:semicolon
)brace
DECL|macro|blk_finished_io
mdefine_line|#define blk_finished_io(nsects)&t;do { } while (0)
DECL|macro|blk_started_io
mdefine_line|#define blk_started_io(nsects)&t;do { } while (0)
multiline_comment|/* assumes size &gt; 256 */
DECL|function|blksize_bits
r_static
r_inline
r_int
r_int
id|blksize_bits
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|bits
op_assign
l_int|8
suffix:semicolon
r_do
(brace
id|bits
op_increment
suffix:semicolon
id|size
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
OG
l_int|256
)paren
suffix:semicolon
r_return
id|bits
suffix:semicolon
)brace
DECL|function|block_size
r_extern
r_inline
r_int
r_int
id|block_size
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
r_return
id|bdev-&gt;bd_block_size
suffix:semicolon
)brace
DECL|member|v
DECL|typedef|Sector
r_typedef
r_struct
(brace
r_struct
id|page
op_star
id|v
suffix:semicolon
)brace
id|Sector
suffix:semicolon
r_int
r_char
op_star
id|read_dev_sector
c_func
(paren
r_struct
id|block_device
op_star
comma
id|sector_t
comma
id|Sector
op_star
)paren
suffix:semicolon
DECL|function|put_dev_sector
r_static
r_inline
r_void
id|put_dev_sector
c_func
(paren
id|Sector
id|p
)paren
(brace
id|page_cache_release
c_func
(paren
id|p.v
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_LBD
macro_line|# include &lt;asm/div64.h&gt;
DECL|macro|sector_div
macro_line|# define sector_div(a, b) do_div(a, b)
macro_line|#else
DECL|macro|sector_div
macro_line|# define sector_div(n, b)( &bslash;&n;{ &bslash;&n;&t;int _res; &bslash;&n;&t;_res = (n) % (b); &bslash;&n;&t;(n) /= (b); &bslash;&n;&t;_res; &bslash;&n;} &bslash;&n;)
macro_line|#endif 
macro_line|#endif
eof
