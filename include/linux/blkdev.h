macro_line|#ifndef _LINUX_BLKDEV_H
DECL|macro|_LINUX_BLKDEV_H
mdefine_line|#define _LINUX_BLKDEV_H
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
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
DECL|struct|request_list
r_struct
id|request_list
(brace
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|free
r_struct
id|list_head
id|free
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
)brace
suffix:semicolon
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
DECL|member|elevator_private
r_void
op_star
id|elevator_private
suffix:semicolon
DECL|member|cmd
r_int
r_char
id|cmd
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* see REQ_ bits below */
DECL|member|rq_status
r_int
id|rq_status
suffix:semicolon
multiline_comment|/* should split this into a few status bits */
DECL|member|rq_dev
id|kdev_t
id|rq_dev
suffix:semicolon
DECL|member|errors
r_int
id|errors
suffix:semicolon
DECL|member|sector
id|sector_t
id|sector
suffix:semicolon
DECL|member|nr_sectors
r_int
r_int
id|nr_sectors
suffix:semicolon
DECL|member|hard_sector
r_int
r_int
id|hard_sector
suffix:semicolon
multiline_comment|/* the hard_* are block layer&n;&t;&t;&t;&t;&t; * internals, no driver should&n;&t;&t;&t;&t;&t; * touch them&n;&t;&t;&t;&t;&t; */
DECL|member|hard_nr_sectors
r_int
r_int
id|hard_nr_sectors
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
DECL|member|current_nr_sectors
r_int
r_int
id|current_nr_sectors
suffix:semicolon
DECL|member|hard_cur_sectors
r_int
r_int
id|hard_cur_sectors
suffix:semicolon
DECL|member|special
r_void
op_star
id|special
suffix:semicolon
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
DECL|member|waiting
r_struct
id|completion
op_star
id|waiting
suffix:semicolon
DECL|member|bio
DECL|member|biotail
r_struct
id|bio
op_star
id|bio
comma
op_star
id|biotail
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
DECL|enumerator|__REQ_BARRIER
id|__REQ_BARRIER
comma
multiline_comment|/* may not be passed */
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
multiline_comment|/*&n;&t; * for IDE&n; &t;*/
DECL|enumerator|__REQ_DRIVE_CMD
id|__REQ_DRIVE_CMD
comma
DECL|enumerator|__REQ_DRIVE_TASK
id|__REQ_DRIVE_TASK
comma
DECL|enumerator|__REQ_DRIVE_ACB
id|__REQ_DRIVE_ACB
comma
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
DECL|enumerator|__REQ_SPECIAL
id|__REQ_SPECIAL
comma
multiline_comment|/* driver special command */
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
DECL|macro|REQ_BARRIER
mdefine_line|#define REQ_BARRIER&t;(1 &lt;&lt; __REQ_BARRIER)
DECL|macro|REQ_CMD
mdefine_line|#define REQ_CMD&t;&t;(1 &lt;&lt; __REQ_CMD)
DECL|macro|REQ_NOMERGE
mdefine_line|#define REQ_NOMERGE&t;(1 &lt;&lt; __REQ_NOMERGE)
DECL|macro|REQ_STARTED
mdefine_line|#define REQ_STARTED&t;(1 &lt;&lt; __REQ_STARTED)
DECL|macro|REQ_DONTPREP
mdefine_line|#define REQ_DONTPREP&t;(1 &lt;&lt; __REQ_DONTPREP)
DECL|macro|REQ_DRIVE_CMD
mdefine_line|#define REQ_DRIVE_CMD&t;(1 &lt;&lt; __REQ_DRIVE_CMD)
DECL|macro|REQ_DRIVE_TASK
mdefine_line|#define REQ_DRIVE_TASK&t;(1 &lt;&lt; __REQ_DRIVE_TASK)
DECL|macro|REQ_DRIVE_ACB
mdefine_line|#define REQ_DRIVE_ACB&t;(1 &lt;&lt; __REQ_DRIVE_ACB)
DECL|macro|REQ_PC
mdefine_line|#define REQ_PC&t;&t;(1 &lt;&lt; __REQ_PC)
DECL|macro|REQ_SENSE
mdefine_line|#define REQ_SENSE&t;(1 &lt;&lt; __REQ_SENSE)
DECL|macro|REQ_BLOCK_PC
mdefine_line|#define REQ_BLOCK_PC&t;(1 &lt;&lt; __REQ_BLOCK_PC)
DECL|macro|REQ_SPECIAL
mdefine_line|#define REQ_SPECIAL&t;(1 &lt;&lt; __REQ_SPECIAL)
DECL|macro|REQ_DRIVE_TASKFILE
mdefine_line|#define REQ_DRIVE_TASKFILE&t;REQ_DRIVE_ACB
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
DECL|typedef|queue_proc
r_typedef
id|request_queue_t
op_star
(paren
id|queue_proc
)paren
(paren
id|kdev_t
id|dev
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
DECL|typedef|unplug_device_fn
r_typedef
r_void
(paren
id|unplug_device_fn
)paren
(paren
r_void
op_star
id|q
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
multiline_comment|/*&n; * Default nr free requests per queue, ll_rw_blk will scale it down&n; * according to available RAM at init time&n; */
DECL|macro|QUEUE_NR_REQUESTS
mdefine_line|#define QUEUE_NR_REQUESTS&t;8192
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
(braket
l_int|2
)braket
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
multiline_comment|/*&n;&t; * The VM-level readahead tunable for this device.  In&n;&t; * units of 512-byte sectors.&n;&t; */
DECL|member|ra_sectors
r_int
id|ra_sectors
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
multiline_comment|/*&n;&t; * This is used to remove the plug when tq_disk runs.&n;&t; */
DECL|member|plug_tq
r_struct
id|tq_struct
id|plug_tq
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
DECL|member|queue_wait
id|wait_queue_head_t
id|queue_wait
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
DECL|macro|QUEUE_FLAG_PLUGGED
mdefine_line|#define QUEUE_FLAG_PLUGGED&t;0&t;/* queue is plugged */
DECL|macro|QUEUE_FLAG_CLUSTER
mdefine_line|#define QUEUE_FLAG_CLUSTER&t;1&t;/* cluster several segments into 1 */
DECL|macro|blk_queue_plugged
mdefine_line|#define blk_queue_plugged(q)&t;test_bit(QUEUE_FLAG_PLUGGED, &amp;(q)-&gt;queue_flags)
DECL|macro|blk_mark_plugged
mdefine_line|#define blk_mark_plugged(q)&t;set_bit(QUEUE_FLAG_PLUGGED, &amp;(q)-&gt;queue_flags)
DECL|macro|blk_queue_empty
mdefine_line|#define blk_queue_empty(q)&t;elv_queue_empty(q)
DECL|macro|list_entry_rq
mdefine_line|#define list_entry_rq(ptr)&t;list_entry((ptr), struct request, queuelist)
DECL|macro|rq_data_dir
mdefine_line|#define rq_data_dir(rq)&t;&t;((rq)-&gt;flags &amp; 1)
multiline_comment|/*&n; * mergeable request must not have _NOMERGE or _BARRIER bit set, nor may&n; * it already be started by driver.&n; */
DECL|macro|rq_mergeable
mdefine_line|#define rq_mergeable(rq)&t;&bslash;&n;&t;(!((rq)-&gt;flags &amp; (REQ_NOMERGE | REQ_STARTED | REQ_BARRIER))&t;&bslash;&n;&t;&amp;&amp; ((rq)-&gt;flags &amp; REQ_CMD))
multiline_comment|/*&n; * noop, requests are automagically marked as active/inactive by I/O&n; * scheduler -- see elv_next_request&n; */
DECL|macro|blk_queue_headactive
mdefine_line|#define blk_queue_headactive(q, head_active)
r_extern
r_int
r_int
id|blk_max_low_pfn
comma
id|blk_max_pfn
suffix:semicolon
multiline_comment|/*&n; * standard bounce addresses:&n; *&n; * BLK_BOUNCE_HIGH&t;: bounce all highmem pages&n; * BLK_BOUNCE_ANY&t;: don&squot;t bounce anything&n; * BLK_BOUNCE_ISA&t;: bounce pages above ISA DMA boundary&n; */
DECL|macro|BLK_BOUNCE_HIGH
mdefine_line|#define BLK_BOUNCE_HIGH&t;&t;(blk_max_low_pfn &lt;&lt; PAGE_SHIFT)
DECL|macro|BLK_BOUNCE_ANY
mdefine_line|#define BLK_BOUNCE_ANY&t;&t;(blk_max_pfn &lt;&lt; PAGE_SHIFT)
DECL|macro|BLK_BOUNCE_ISA
mdefine_line|#define BLK_BOUNCE_ISA&t;&t;(ISA_DMA_THRESHOLD)
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
id|create_bounce
c_func
(paren
r_int
r_int
id|pfn
comma
r_int
id|gfp
comma
r_struct
id|bio
op_star
op_star
id|bio_orig
)paren
suffix:semicolon
DECL|function|blk_queue_bounce
r_extern
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
id|create_bounce
c_func
(paren
id|q-&gt;bounce_pfn
comma
id|q-&gt;bounce_gfp
comma
id|bio
)paren
suffix:semicolon
)brace
DECL|macro|rq_for_each_bio
mdefine_line|#define rq_for_each_bio(bio, rq)&t;&bslash;&n;&t;if ((rq-&gt;bio))&t;&t;&t;&bslash;&n;&t;&t;for (bio = (rq)-&gt;bio; bio; bio = bio-&gt;bi_next)
DECL|struct|blk_dev_struct
r_struct
id|blk_dev_struct
(brace
multiline_comment|/*&n;&t; * queue_proc has to be atomic&n;&t; */
DECL|member|request_queue
id|request_queue_t
id|request_queue
suffix:semicolon
DECL|member|queue
id|queue_proc
op_star
id|queue
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
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
multiline_comment|/*&n; * Used to indicate the default queue for drivers that don&squot;t bother&n; * to implement multiple queues.  We have this access macro here&n; * so as to eliminate the need for each and every block device&n; * driver to know about the internal structure of blk_dev[].&n; */
DECL|macro|BLK_DEFAULT_QUEUE
mdefine_line|#define BLK_DEFAULT_QUEUE(_MAJOR)  &amp;blk_dev[_MAJOR].request_queue
r_extern
r_struct
id|sec_size
op_star
id|blk_sec
(braket
id|MAX_BLKDEV
)braket
suffix:semicolon
r_extern
r_struct
id|blk_dev_struct
id|blk_dev
(braket
id|MAX_BLKDEV
)braket
suffix:semicolon
r_extern
r_void
id|grok_partitions
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|wipe_partitions
c_func
(paren
id|kdev_t
id|dev
)paren
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
comma
id|kdev_t
id|first
comma
r_int
id|minors
comma
r_struct
id|block_device_operations
op_star
id|ops
comma
r_int
id|size
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
r_inline
id|request_queue_t
op_star
id|blk_get_queue
c_func
(paren
id|kdev_t
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|blkdev_release_request
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
id|blk_plug_device
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
id|block_ioctl
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
r_int
id|ll_10byte_cmd_build
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
id|q
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
id|q
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
id|q
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
id|q
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
id|q
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
id|q
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_assign_lock
c_func
(paren
id|request_queue_t
op_star
id|q
comma
id|spinlock_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_prep_rq
c_func
(paren
id|request_queue_t
op_star
id|q
comma
id|prep_rq_fn
op_star
id|pfn
)paren
suffix:semicolon
r_extern
r_int
id|blk_set_readahead
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|sectors
)paren
suffix:semicolon
r_extern
r_int
id|blk_get_readahead
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
op_star
id|blk_size
(braket
id|MAX_BLKDEV
)braket
suffix:semicolon
multiline_comment|/* in units of 1024 bytes */
r_extern
r_int
op_star
id|blksize_size
(braket
id|MAX_BLKDEV
)braket
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
DECL|function|blk_clear
r_extern
r_inline
r_void
id|blk_clear
c_func
(paren
r_int
id|major
)paren
(brace
id|blk_size
(braket
id|major
)braket
op_assign
l_int|NULL
suffix:semicolon
macro_line|#if 0
id|blk_size_in_bytes
(braket
id|major
)braket
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
id|blksize_size
(braket
id|major
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|queue_hardsect_size
r_extern
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
DECL|function|get_hardsect_size
r_extern
r_inline
r_int
id|get_hardsect_size
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_return
id|queue_hardsect_size
c_func
(paren
id|blk_get_queue
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
)brace
DECL|function|bdev_hardsect_size
r_extern
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
id|blk_get_queue
c_func
(paren
id|to_kdev_t
c_func
(paren
id|bdev-&gt;bd_dev
)paren
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
r_extern
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
id|kdev_t
id|dev
)paren
(brace
r_int
id|retval
op_assign
id|BLOCK_SIZE
suffix:semicolon
r_int
id|major
op_assign
id|major
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blksize_size
(braket
id|major
)braket
)paren
(brace
r_int
id|minor
op_assign
id|minor
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blksize_size
(braket
id|major
)braket
(braket
id|minor
)braket
)paren
id|retval
op_assign
id|blksize_size
(braket
id|major
)braket
(braket
id|minor
)braket
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|blkdev_size_in_bytes
r_static
r_inline
id|loff_t
id|blkdev_size_in_bytes
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
macro_line|#if 0
r_if
c_cond
(paren
id|blk_size_in_bytes
(braket
id|major
c_func
(paren
id|dev
)paren
)braket
)paren
r_return
id|blk_size_in_bytes
(braket
id|major
c_func
(paren
id|dev
)paren
)braket
(braket
id|minor
c_func
(paren
id|dev
)paren
)braket
suffix:semicolon
r_else
macro_line|#endif
r_if
c_cond
(paren
id|blk_size
(braket
id|major
c_func
(paren
id|dev
)paren
)braket
)paren
r_return
(paren
id|loff_t
)paren
id|blk_size
(braket
id|major
c_func
(paren
id|dev
)paren
)braket
(braket
id|minor
c_func
(paren
id|dev
)paren
)braket
op_lshift
id|BLOCK_SIZE_BITS
suffix:semicolon
r_else
r_return
l_int|0
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
r_int
r_int
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
macro_line|#endif
eof
