macro_line|#ifndef _RAID5_H
DECL|macro|_RAID5_H
mdefine_line|#define _RAID5_H
macro_line|#include &lt;linux/raid/md.h&gt;
macro_line|#include &lt;linux/raid/xor.h&gt;
multiline_comment|/*&n; *&n; * Each stripe contains one buffer per disc.  Each buffer can be in&n; * one of a number of states stored in &quot;flags&quot;.  Changes between&n; * these states happen *almost* exclusively under a per-stripe&n; * spinlock.  Some very specific changes can happen in bi_end_io, and&n; * these are not protected by the spin lock.&n; *&n; * The flag bits that are used to represent these states are:&n; *   R5_UPTODATE and R5_LOCKED&n; *&n; * State Empty == !UPTODATE, !LOCK&n; *        We have no data, and there is no active request&n; * State Want == !UPTODATE, LOCK&n; *        A read request is being submitted for this block&n; * State Dirty == UPTODATE, LOCK&n; *        Some new data is in this buffer, and it is being written out&n; * State Clean == UPTODATE, !LOCK&n; *        We have valid data which is the same as on disc&n; *&n; * The possible state transitions are:&n; *&n; *  Empty -&gt; Want   - on read or write to get old data for  parity calc&n; *  Empty -&gt; Dirty  - on compute_parity to satisfy write/sync request.(RECONSTRUCT_WRITE)&n; *  Empty -&gt; Clean  - on compute_block when computing a block for failed drive&n; *  Want  -&gt; Empty  - on failed read&n; *  Want  -&gt; Clean  - on successful completion of read request&n; *  Dirty -&gt; Clean  - on successful completion of write request&n; *  Dirty -&gt; Clean  - on failed write&n; *  Clean -&gt; Dirty  - on compute_parity to satisfy write/sync (RECONSTRUCT or RMW)&n; *&n; * The Want-&gt;Empty, Want-&gt;Clean, Dirty-&gt;Clean, transitions&n; * all happen in b_end_io at interrupt time.&n; * Each sets the Uptodate bit before releasing the Lock bit.&n; * This leaves one multi-stage transition:&n; *    Want-&gt;Dirty-&gt;Clean&n; * This is safe because thinking that a Clean buffer is actually dirty&n; * will at worst delay some action, and the stripe will be scheduled&n; * for attention after the transition is complete.&n; *&n; * There is one possibility that is not covered by these states.  That&n; * is if one drive has failed and there is a spare being rebuilt.  We&n; * can&squot;t distinguish between a clean block that has been generated&n; * from parity calculations, and a clean block that has been&n; * successfully written to the spare ( or to parity when resyncing).&n; * To distingush these states we have a stripe bit STRIPE_INSYNC that&n; * is set whenever a write is scheduled to the spare, or to the parity&n; * disc if there is no spare.  A sync request clears this bit, and&n; * when we find it set with no buffers locked, we know the sync is&n; * complete.&n; *&n; * Buffers for the md device that arrive via make_request are attached&n; * to the appropriate stripe in one of two lists linked on b_reqnext.&n; * One list (bh_read) for read requests, one (bh_write) for write.&n; * There should never be more than one buffer on the two lists&n; * together, but we are not guaranteed of that so we allow for more.&n; *&n; * If a buffer is on the read list when the associated cache buffer is&n; * Uptodate, the data is copied into the read buffer and it&squot;s b_end_io&n; * routine is called.  This may happen in the end_request routine only&n; * if the buffer has just successfully been read.  end_request should&n; * remove the buffers from the list and then set the Uptodate bit on&n; * the buffer.  Other threads may do this only if they first check&n; * that the Uptodate bit is set.  Once they have checked that they may&n; * take buffers off the read queue.&n; *&n; * When a buffer on the write list is committed for write is it copied&n; * into the cache buffer, which is then marked dirty, and moved onto a&n; * third list, the written list (bh_written).  Once both the parity&n; * block and the cached buffer are successfully written, any buffer on&n; * a written list can be returned with b_end_io.&n; *&n; * The write list and read list both act as fifos.  The read list is&n; * protected by the device_lock.  The write and written lists are&n; * protected by the stripe lock.  The device_lock, which can be&n; * claimed while the stipe lock is held, is only for list&n; * manipulations and will only be held for a very short time.  It can&n; * be claimed from interrupts.&n; *&n; *&n; * Stripes in the stripe cache can be on one of two lists (or on&n; * neither).  The &quot;inactive_list&quot; contains stripes which are not&n; * currently being used for any request.  They can freely be reused&n; * for another stripe.  The &quot;handle_list&quot; contains stripes that need&n; * to be handled in some way.  Both of these are fifo queues.  Each&n; * stripe is also (potentially) linked to a hash bucket in the hash&n; * table so that it can be found by sector number.  Stripes that are&n; * not hashed must be on the inactive_list, and will normally be at&n; * the front.  All stripes start life this way.&n; *&n; * The inactive_list, handle_list and hash bucket lists are all protected by the&n; * device_lock.&n; *  - stripes on the inactive_list never have their stripe_lock held.&n; *  - stripes have a reference counter. If count==0, they are on a list.&n; *  - If a stripe might need handling, STRIPE_HANDLE is set.&n; *  - When refcount reaches zero, then if STRIPE_HANDLE it is put on&n; *    handle_list else inactive_list&n; *&n; * This, combined with the fact that STRIPE_HANDLE is only ever&n; * cleared while a stripe has a non-zero count means that if the&n; * refcount is 0 and STRIPE_HANDLE is set, then it is on the&n; * handle_list and if recount is 0 and STRIPE_HANDLE is not set, then&n; * the stripe is on inactive_list.&n; *&n; * The possible transitions are:&n; *  activate an unhashed/inactive stripe (get_active_stripe())&n; *     lockdev check-hash unlink-stripe cnt++ clean-stripe hash-stripe unlockdev&n; *  activate a hashed, possibly active stripe (get_active_stripe())&n; *     lockdev check-hash if(!cnt++)unlink-stripe unlockdev&n; *  attach a request to an active stripe (add_stripe_bh())&n; *     lockdev attach-buffer unlockdev&n; *  handle a stripe (handle_stripe())&n; *     lockstripe clrSTRIPE_HANDLE ... (lockdev check-buffers unlockdev) .. change-state .. record io needed unlockstripe schedule io&n; *  release an active stripe (release_stripe())&n; *     lockdev if (!--cnt) { if  STRIPE_HANDLE, add to handle_list else add to inactive-list } unlockdev&n; *&n; * The refcount counts each thread that have activated the stripe,&n; * plus raid5d if it is handling it, plus one for each active request&n; * on a cached buffer.&n; */
DECL|struct|stripe_head
r_struct
id|stripe_head
(brace
DECL|member|hash_next
DECL|member|hash_pprev
r_struct
id|stripe_head
op_star
id|hash_next
comma
op_star
op_star
id|hash_pprev
suffix:semicolon
multiline_comment|/* hash pointers */
DECL|member|lru
r_struct
id|list_head
id|lru
suffix:semicolon
multiline_comment|/* inactive_list or handle_list */
DECL|member|raid_conf
r_struct
id|raid5_private_data
op_star
id|raid_conf
suffix:semicolon
DECL|member|sector
id|sector_t
id|sector
suffix:semicolon
multiline_comment|/* sector of this row */
DECL|member|pd_idx
r_int
id|pd_idx
suffix:semicolon
multiline_comment|/* parity disk index */
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
multiline_comment|/* state flags */
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
multiline_comment|/* nr of active thread/requests */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|struct|r5dev
r_struct
id|r5dev
(brace
DECL|member|req
r_struct
id|bio
id|req
suffix:semicolon
DECL|member|vec
r_struct
id|bio_vec
id|vec
suffix:semicolon
DECL|member|page
r_struct
id|page
op_star
id|page
suffix:semicolon
DECL|member|toread
DECL|member|towrite
DECL|member|written
r_struct
id|bio
op_star
id|toread
comma
op_star
id|towrite
comma
op_star
id|written
suffix:semicolon
DECL|member|sector
id|sector_t
id|sector
suffix:semicolon
multiline_comment|/* sector of this page */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|dev
)brace
id|dev
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* allocated with extra space depending of RAID geometry */
)brace
suffix:semicolon
multiline_comment|/* Flags */
DECL|macro|R5_UPTODATE
mdefine_line|#define&t;R5_UPTODATE&t;0&t;/* page contains current data */
DECL|macro|R5_LOCKED
mdefine_line|#define&t;R5_LOCKED&t;1&t;/* IO has been submitted on &quot;req&quot; */
DECL|macro|R5_OVERWRITE
mdefine_line|#define&t;R5_OVERWRITE&t;2&t;/* towrite covers whole page */
multiline_comment|/*&n; * Write method&n; */
DECL|macro|RECONSTRUCT_WRITE
mdefine_line|#define RECONSTRUCT_WRITE&t;1
DECL|macro|READ_MODIFY_WRITE
mdefine_line|#define READ_MODIFY_WRITE&t;2
multiline_comment|/* not a write method, but a compute_parity mode */
DECL|macro|CHECK_PARITY
mdefine_line|#define&t;CHECK_PARITY&t;&t;3
multiline_comment|/*&n; * Stripe state&n; */
DECL|macro|STRIPE_ERROR
mdefine_line|#define STRIPE_ERROR&t;&t;1
DECL|macro|STRIPE_HANDLE
mdefine_line|#define STRIPE_HANDLE&t;&t;2
DECL|macro|STRIPE_SYNCING
mdefine_line|#define&t;STRIPE_SYNCING&t;&t;3
DECL|macro|STRIPE_INSYNC
mdefine_line|#define&t;STRIPE_INSYNC&t;&t;4
DECL|macro|STRIPE_PREREAD_ACTIVE
mdefine_line|#define&t;STRIPE_PREREAD_ACTIVE&t;5
DECL|macro|STRIPE_DELAYED
mdefine_line|#define&t;STRIPE_DELAYED&t;&t;6
multiline_comment|/*&n; * Plugging:&n; *&n; * To improve write throughput, we need to delay the handling of some&n; * stripes until there has been a chance that several write requests&n; * for the one stripe have all been collected.&n; * In particular, any write request that would require pre-reading&n; * is put on a &quot;delayed&quot; queue until there are no stripes currently&n; * in a pre-read phase.  Further, if the &quot;delayed&quot; queue is empty when&n; * a stripe is put on it then we &quot;plug&quot; the queue and do not process it&n; * until an unplug call is made. (blk_run_queues is run).&n; *&n; * When preread is initiated on a stripe, we set PREREAD_ACTIVE and add&n; * it to the count of prereading stripes.&n; * When write is initiated, or the stripe refcnt == 0 (just in case) we&n; * clear the PREREAD_ACTIVE flag and decrement the count&n; * Whenever the delayed queue is empty and the device is not plugged, we&n; * move any strips from delayed to handle and clear the DELAYED flag and set PREREAD_ACTIVE.&n; * In stripe_handle, if we find pre-reading is necessary, we do it if&n; * PREREAD_ACTIVE is set, else we set DELAYED which will send it to the delayed queue.&n; * HANDLE gets cleared if stripe_handle leave nothing locked.&n; */
DECL|struct|disk_info
r_struct
id|disk_info
(brace
DECL|member|dev
id|kdev_t
id|dev
suffix:semicolon
DECL|member|bdev
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
DECL|member|operational
r_int
id|operational
suffix:semicolon
DECL|member|number
r_int
id|number
suffix:semicolon
DECL|member|raid_disk
r_int
id|raid_disk
suffix:semicolon
DECL|member|write_only
r_int
id|write_only
suffix:semicolon
DECL|member|spare
r_int
id|spare
suffix:semicolon
DECL|member|used_slot
r_int
id|used_slot
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|raid5_private_data
r_struct
id|raid5_private_data
(brace
DECL|member|stripe_hashtbl
r_struct
id|stripe_head
op_star
op_star
id|stripe_hashtbl
suffix:semicolon
DECL|member|mddev
id|mddev_t
op_star
id|mddev
suffix:semicolon
DECL|member|thread
DECL|member|resync_thread
id|mdk_thread_t
op_star
id|thread
comma
op_star
id|resync_thread
suffix:semicolon
DECL|member|disks
r_struct
id|disk_info
id|disks
(braket
id|MD_SB_DISKS
)braket
suffix:semicolon
DECL|member|spare
r_struct
id|disk_info
op_star
id|spare
suffix:semicolon
DECL|member|chunk_size
DECL|member|level
DECL|member|algorithm
r_int
id|chunk_size
comma
id|level
comma
id|algorithm
suffix:semicolon
DECL|member|raid_disks
DECL|member|working_disks
DECL|member|failed_disks
r_int
id|raid_disks
comma
id|working_disks
comma
id|failed_disks
suffix:semicolon
DECL|member|resync_parity
r_int
id|resync_parity
suffix:semicolon
DECL|member|max_nr_stripes
r_int
id|max_nr_stripes
suffix:semicolon
DECL|member|handle_list
r_struct
id|list_head
id|handle_list
suffix:semicolon
multiline_comment|/* stripes needing handling */
DECL|member|delayed_list
r_struct
id|list_head
id|delayed_list
suffix:semicolon
multiline_comment|/* stripes that have plugged requests */
DECL|member|preread_active_stripes
id|atomic_t
id|preread_active_stripes
suffix:semicolon
multiline_comment|/* stripes with scheduled io */
DECL|member|cache_name
r_char
id|cache_name
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|slab_cache
id|kmem_cache_t
op_star
id|slab_cache
suffix:semicolon
multiline_comment|/* for allocating stripes */
multiline_comment|/*&n;&t; * Free stripes pool&n;&t; */
DECL|member|active_stripes
id|atomic_t
id|active_stripes
suffix:semicolon
DECL|member|inactive_list
r_struct
id|list_head
id|inactive_list
suffix:semicolon
DECL|member|wait_for_stripe
id|wait_queue_head_t
id|wait_for_stripe
suffix:semicolon
DECL|member|inactive_blocked
r_int
id|inactive_blocked
suffix:semicolon
multiline_comment|/* release of inactive stripes blocked,&n;&t;&t;&t;&t;&t;&t;&t; * waiting for 25% to be free&n;&t;&t;&t;&t;&t;&t;&t; */
DECL|member|device_lock
id|spinlock_t
id|device_lock
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|raid5_conf_t
r_typedef
r_struct
id|raid5_private_data
id|raid5_conf_t
suffix:semicolon
DECL|macro|mddev_to_conf
mdefine_line|#define mddev_to_conf(mddev) ((raid5_conf_t *) mddev-&gt;private)
multiline_comment|/*&n; * Our supported algorithms&n; */
DECL|macro|ALGORITHM_LEFT_ASYMMETRIC
mdefine_line|#define ALGORITHM_LEFT_ASYMMETRIC&t;0
DECL|macro|ALGORITHM_RIGHT_ASYMMETRIC
mdefine_line|#define ALGORITHM_RIGHT_ASYMMETRIC&t;1
DECL|macro|ALGORITHM_LEFT_SYMMETRIC
mdefine_line|#define ALGORITHM_LEFT_SYMMETRIC&t;2
DECL|macro|ALGORITHM_RIGHT_SYMMETRIC
mdefine_line|#define ALGORITHM_RIGHT_SYMMETRIC&t;3
macro_line|#endif
eof
