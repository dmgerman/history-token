multiline_comment|/*&n;   md_k.h : kernel internal structure of the Linux MD driver&n;          Copyright (C) 1996-98 Ingo Molnar, Gadi Oxman&n;&t;  &n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2, or (at your option)&n;   any later version.&n;   &n;   You should have received a copy of the GNU General Public License&n;   (for example /usr/src/linux/COPYING); if not, write to the Free&n;   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  &n;*/
macro_line|#ifndef _MD_K_H
DECL|macro|_MD_K_H
mdefine_line|#define _MD_K_H
DECL|macro|MD_RESERVED
mdefine_line|#define MD_RESERVED       0UL
DECL|macro|LINEAR
mdefine_line|#define LINEAR            1UL
DECL|macro|RAID0
mdefine_line|#define RAID0             2UL
DECL|macro|RAID1
mdefine_line|#define RAID1             3UL
DECL|macro|RAID5
mdefine_line|#define RAID5             4UL
DECL|macro|TRANSLUCENT
mdefine_line|#define TRANSLUCENT       5UL
DECL|macro|HSM
mdefine_line|#define HSM               6UL
DECL|macro|MULTIPATH
mdefine_line|#define MULTIPATH         7UL
DECL|macro|MAX_PERSONALITY
mdefine_line|#define MAX_PERSONALITY   8UL
DECL|macro|LEVEL_MULTIPATH
mdefine_line|#define&t;LEVEL_MULTIPATH&t;&t;(-4)
DECL|macro|LEVEL_LINEAR
mdefine_line|#define&t;LEVEL_LINEAR&t;&t;(-1)
DECL|macro|MaxSector
mdefine_line|#define MaxSector (~(sector_t)0)
DECL|macro|MD_THREAD_NAME_MAX
mdefine_line|#define MD_THREAD_NAME_MAX 14
DECL|function|pers_to_level
r_static
r_inline
r_int
id|pers_to_level
(paren
r_int
id|pers
)paren
(brace
r_switch
c_cond
(paren
id|pers
)paren
(brace
r_case
id|MULTIPATH
suffix:colon
r_return
id|LEVEL_MULTIPATH
suffix:semicolon
r_case
id|HSM
suffix:colon
r_return
op_minus
l_int|3
suffix:semicolon
r_case
id|TRANSLUCENT
suffix:colon
r_return
op_minus
l_int|2
suffix:semicolon
r_case
id|LINEAR
suffix:colon
r_return
id|LEVEL_LINEAR
suffix:semicolon
r_case
id|RAID0
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|RAID1
suffix:colon
r_return
l_int|1
suffix:semicolon
r_case
id|RAID5
suffix:colon
r_return
l_int|5
suffix:semicolon
)brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
id|MD_RESERVED
suffix:semicolon
)brace
DECL|function|level_to_pers
r_static
r_inline
r_int
id|level_to_pers
(paren
r_int
id|level
)paren
(brace
r_switch
c_cond
(paren
id|level
)paren
(brace
r_case
id|LEVEL_MULTIPATH
suffix:colon
r_return
id|MULTIPATH
suffix:semicolon
r_case
op_minus
l_int|3
suffix:colon
r_return
id|HSM
suffix:semicolon
r_case
op_minus
l_int|2
suffix:colon
r_return
id|TRANSLUCENT
suffix:semicolon
r_case
id|LEVEL_LINEAR
suffix:colon
r_return
id|LINEAR
suffix:semicolon
r_case
l_int|0
suffix:colon
r_return
id|RAID0
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
id|RAID1
suffix:semicolon
r_case
l_int|4
suffix:colon
r_case
l_int|5
suffix:colon
r_return
id|RAID5
suffix:semicolon
)brace
r_return
id|MD_RESERVED
suffix:semicolon
)brace
DECL|typedef|mddev_t
r_typedef
r_struct
id|mddev_s
id|mddev_t
suffix:semicolon
DECL|typedef|mdk_rdev_t
r_typedef
r_struct
id|mdk_rdev_s
id|mdk_rdev_t
suffix:semicolon
DECL|macro|MAX_MD_DEVS
mdefine_line|#define MAX_MD_DEVS  256&t;/* Max number of md dev */
multiline_comment|/*&n; * options passed in raidrun:&n; */
DECL|macro|MAX_CHUNK_SIZE
mdefine_line|#define MAX_CHUNK_SIZE (4096*1024)
multiline_comment|/*&n; * default readahead&n; */
DECL|function|disk_faulty
r_static
r_inline
r_int
id|disk_faulty
c_func
(paren
id|mdp_disk_t
op_star
id|d
)paren
(brace
r_return
id|d-&gt;state
op_amp
(paren
l_int|1
op_lshift
id|MD_DISK_FAULTY
)paren
suffix:semicolon
)brace
DECL|function|disk_active
r_static
r_inline
r_int
id|disk_active
c_func
(paren
id|mdp_disk_t
op_star
id|d
)paren
(brace
r_return
id|d-&gt;state
op_amp
(paren
l_int|1
op_lshift
id|MD_DISK_ACTIVE
)paren
suffix:semicolon
)brace
DECL|function|disk_sync
r_static
r_inline
r_int
id|disk_sync
c_func
(paren
id|mdp_disk_t
op_star
id|d
)paren
(brace
r_return
id|d-&gt;state
op_amp
(paren
l_int|1
op_lshift
id|MD_DISK_SYNC
)paren
suffix:semicolon
)brace
DECL|function|disk_spare
r_static
r_inline
r_int
id|disk_spare
c_func
(paren
id|mdp_disk_t
op_star
id|d
)paren
(brace
r_return
op_logical_neg
id|disk_sync
c_func
(paren
id|d
)paren
op_logical_and
op_logical_neg
id|disk_active
c_func
(paren
id|d
)paren
op_logical_and
op_logical_neg
id|disk_faulty
c_func
(paren
id|d
)paren
suffix:semicolon
)brace
DECL|function|disk_removed
r_static
r_inline
r_int
id|disk_removed
c_func
(paren
id|mdp_disk_t
op_star
id|d
)paren
(brace
r_return
id|d-&gt;state
op_amp
(paren
l_int|1
op_lshift
id|MD_DISK_REMOVED
)paren
suffix:semicolon
)brace
DECL|function|mark_disk_faulty
r_static
r_inline
r_void
id|mark_disk_faulty
c_func
(paren
id|mdp_disk_t
op_star
id|d
)paren
(brace
id|d-&gt;state
op_or_assign
(paren
l_int|1
op_lshift
id|MD_DISK_FAULTY
)paren
suffix:semicolon
)brace
DECL|function|mark_disk_active
r_static
r_inline
r_void
id|mark_disk_active
c_func
(paren
id|mdp_disk_t
op_star
id|d
)paren
(brace
id|d-&gt;state
op_or_assign
(paren
l_int|1
op_lshift
id|MD_DISK_ACTIVE
)paren
suffix:semicolon
)brace
DECL|function|mark_disk_sync
r_static
r_inline
r_void
id|mark_disk_sync
c_func
(paren
id|mdp_disk_t
op_star
id|d
)paren
(brace
id|d-&gt;state
op_or_assign
(paren
l_int|1
op_lshift
id|MD_DISK_SYNC
)paren
suffix:semicolon
)brace
DECL|function|mark_disk_spare
r_static
r_inline
r_void
id|mark_disk_spare
c_func
(paren
id|mdp_disk_t
op_star
id|d
)paren
(brace
id|d-&gt;state
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|mark_disk_removed
r_static
r_inline
r_void
id|mark_disk_removed
c_func
(paren
id|mdp_disk_t
op_star
id|d
)paren
(brace
id|d-&gt;state
op_assign
(paren
l_int|1
op_lshift
id|MD_DISK_FAULTY
)paren
op_or
(paren
l_int|1
op_lshift
id|MD_DISK_REMOVED
)paren
suffix:semicolon
)brace
DECL|function|mark_disk_inactive
r_static
r_inline
r_void
id|mark_disk_inactive
c_func
(paren
id|mdp_disk_t
op_star
id|d
)paren
(brace
id|d-&gt;state
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|MD_DISK_ACTIVE
)paren
suffix:semicolon
)brace
DECL|function|mark_disk_nonsync
r_static
r_inline
r_void
id|mark_disk_nonsync
c_func
(paren
id|mdp_disk_t
op_star
id|d
)paren
(brace
id|d-&gt;state
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|MD_DISK_SYNC
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * MD&squot;s &squot;extended&squot; device&n; */
DECL|struct|mdk_rdev_s
r_struct
id|mdk_rdev_s
(brace
DECL|member|same_set
r_struct
id|list_head
id|same_set
suffix:semicolon
multiline_comment|/* RAID devices within the same set */
DECL|member|size
id|sector_t
id|size
suffix:semicolon
multiline_comment|/* Device size (in blocks) */
DECL|member|mddev
id|mddev_t
op_star
id|mddev
suffix:semicolon
multiline_comment|/* RAID array if running */
DECL|member|last_events
r_int
r_int
id|last_events
suffix:semicolon
multiline_comment|/* IO event timestamp */
DECL|member|bdev
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
multiline_comment|/* block device handle */
DECL|member|sb_page
r_struct
id|page
op_star
id|sb_page
suffix:semicolon
DECL|member|sb_loaded
r_int
id|sb_loaded
suffix:semicolon
DECL|member|data_offset
id|sector_t
id|data_offset
suffix:semicolon
multiline_comment|/* start of data in array */
DECL|member|sb_offset
id|sector_t
id|sb_offset
suffix:semicolon
DECL|member|preferred_minor
r_int
id|preferred_minor
suffix:semicolon
multiline_comment|/* autorun support */
multiline_comment|/* A device can be in one of three states based on two flags:&n;&t; * Not working:   faulty==1 in_sync==0&n;&t; * Fully working: faulty==0 in_sync==1&n;&t; * Working, but not&n;&t; * in sync with array&n;&t; *                faulty==0 in_sync==0&n;&t; *&n;&t; * It can never have faulty==1, in_sync==1&n;&t; * This reduces the burden of testing multiple flags in many cases&n;&t; */
DECL|member|faulty
r_int
id|faulty
suffix:semicolon
multiline_comment|/* if faulty do not issue IO requests */
DECL|member|in_sync
r_int
id|in_sync
suffix:semicolon
multiline_comment|/* device is a full member of the array */
DECL|member|desc_nr
r_int
id|desc_nr
suffix:semicolon
multiline_comment|/* descriptor index in the superblock */
DECL|member|raid_disk
r_int
id|raid_disk
suffix:semicolon
multiline_comment|/* role of device in array */
DECL|member|nr_pending
id|atomic_t
id|nr_pending
suffix:semicolon
multiline_comment|/* number of pending requests.&n;&t;&t;&t;&t;&t; * only maintained for arrays that&n;&t;&t;&t;&t;&t; * support hot removal&n;&t;&t;&t;&t;&t; */
)brace
suffix:semicolon
DECL|typedef|mdk_personality_t
r_typedef
r_struct
id|mdk_personality_s
id|mdk_personality_t
suffix:semicolon
DECL|struct|mddev_s
r_struct
id|mddev_s
(brace
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
DECL|member|pers
id|mdk_personality_t
op_star
id|pers
suffix:semicolon
DECL|member|__minor
r_int
id|__minor
suffix:semicolon
DECL|member|disks
r_struct
id|list_head
id|disks
suffix:semicolon
DECL|member|sb_dirty
r_int
id|sb_dirty
suffix:semicolon
DECL|member|ro
r_int
id|ro
suffix:semicolon
multiline_comment|/* Superblock information */
DECL|member|major_version
r_int
id|major_version
comma
DECL|member|minor_version
id|minor_version
comma
DECL|member|patch_version
id|patch_version
suffix:semicolon
DECL|member|persistent
r_int
id|persistent
suffix:semicolon
DECL|member|chunk_size
r_int
id|chunk_size
suffix:semicolon
DECL|member|ctime
DECL|member|utime
id|time_t
id|ctime
comma
id|utime
suffix:semicolon
DECL|member|level
DECL|member|layout
r_int
id|level
comma
id|layout
suffix:semicolon
DECL|member|raid_disks
r_int
id|raid_disks
suffix:semicolon
DECL|member|max_disks
r_int
id|max_disks
suffix:semicolon
DECL|member|size
id|sector_t
id|size
suffix:semicolon
multiline_comment|/* used size of component devices */
DECL|member|array_size
id|sector_t
id|array_size
suffix:semicolon
multiline_comment|/* exported array size */
DECL|member|events
id|__u64
id|events
suffix:semicolon
DECL|member|uuid
r_char
id|uuid
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|thread
r_struct
id|mdk_thread_s
op_star
id|thread
suffix:semicolon
multiline_comment|/* management thread */
DECL|member|sync_thread
r_struct
id|mdk_thread_s
op_star
id|sync_thread
suffix:semicolon
multiline_comment|/* doing resync or reconstruct */
DECL|member|curr_resync
r_int
r_int
id|curr_resync
suffix:semicolon
multiline_comment|/* blocks scheduled */
DECL|member|resync_mark
r_int
r_int
id|resync_mark
suffix:semicolon
multiline_comment|/* a recent timestamp */
DECL|member|resync_mark_cnt
r_int
r_int
id|resync_mark_cnt
suffix:semicolon
multiline_comment|/* blocks written at resync_mark */
multiline_comment|/* recovery/resync flags &n;&t; * NEEDED:   we might need to start a resync/recover&n;&t; * RUNNING:  a thread is running, or about to be started&n;&t; * SYNC:     actually doing a resync, not a recovery&n;&t; * ERR:      and IO error was detected - abort the resync/recovery&n;&t; * INTR:     someone requested a (clean) early abort.&n;&t; * DONE:     thread is done and is waiting to be reaped&n;&t; */
DECL|macro|MD_RECOVERY_RUNNING
mdefine_line|#define&t;MD_RECOVERY_RUNNING&t;0
DECL|macro|MD_RECOVERY_SYNC
mdefine_line|#define&t;MD_RECOVERY_SYNC&t;1
DECL|macro|MD_RECOVERY_ERR
mdefine_line|#define&t;MD_RECOVERY_ERR&t;&t;2
DECL|macro|MD_RECOVERY_INTR
mdefine_line|#define&t;MD_RECOVERY_INTR&t;3
DECL|macro|MD_RECOVERY_DONE
mdefine_line|#define&t;MD_RECOVERY_DONE&t;4
DECL|macro|MD_RECOVERY_NEEDED
mdefine_line|#define&t;MD_RECOVERY_NEEDED&t;5
DECL|member|recovery
r_int
r_int
id|recovery
suffix:semicolon
DECL|member|in_sync
r_int
id|in_sync
suffix:semicolon
multiline_comment|/* know to not need resync */
DECL|member|reconfig_sem
r_struct
id|semaphore
id|reconfig_sem
suffix:semicolon
DECL|member|active
id|atomic_t
id|active
suffix:semicolon
DECL|member|degraded
r_int
id|degraded
suffix:semicolon
multiline_comment|/* whether md should consider&n;&t;&t;&t;&t;&t;&t;&t; * adding a spare&n;&t;&t;&t;&t;&t;&t;&t; */
DECL|member|recovery_active
id|atomic_t
id|recovery_active
suffix:semicolon
multiline_comment|/* blocks scheduled, but not written */
DECL|member|recovery_wait
id|wait_queue_head_t
id|recovery_wait
suffix:semicolon
DECL|member|recovery_cp
id|sector_t
id|recovery_cp
suffix:semicolon
DECL|member|safemode
r_int
r_int
id|safemode
suffix:semicolon
multiline_comment|/* if set, update &quot;clean&quot; superblock&n;&t;&t;&t;&t;&t;&t;&t; * when no writes pending.&n;&t;&t;&t;&t;&t;&t;&t; */
DECL|member|safemode_delay
r_int
r_int
id|safemode_delay
suffix:semicolon
DECL|member|safemode_timer
r_struct
id|timer_list
id|safemode_timer
suffix:semicolon
DECL|member|writes_pending
id|atomic_t
id|writes_pending
suffix:semicolon
DECL|member|queue
id|request_queue_t
op_star
id|queue
suffix:semicolon
multiline_comment|/* for plugging ... */
DECL|member|all_mddevs
r_struct
id|list_head
id|all_mddevs
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mdk_personality_s
r_struct
id|mdk_personality_s
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|make_request
r_int
(paren
op_star
id|make_request
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
DECL|member|run
r_int
(paren
op_star
id|run
)paren
(paren
id|mddev_t
op_star
id|mddev
)paren
suffix:semicolon
DECL|member|stop
r_int
(paren
op_star
id|stop
)paren
(paren
id|mddev_t
op_star
id|mddev
)paren
suffix:semicolon
DECL|member|status
r_void
(paren
op_star
id|status
)paren
(paren
r_struct
id|seq_file
op_star
id|seq
comma
id|mddev_t
op_star
id|mddev
)paren
suffix:semicolon
multiline_comment|/* error_handler must set -&gt;faulty and clear -&gt;in_sync&n;&t; * if appropriate, and should abort recovery if needed &n;&t; */
DECL|member|error_handler
r_void
(paren
op_star
id|error_handler
)paren
(paren
id|mddev_t
op_star
id|mddev
comma
id|mdk_rdev_t
op_star
id|rdev
)paren
suffix:semicolon
DECL|member|hot_add_disk
r_int
(paren
op_star
id|hot_add_disk
)paren
(paren
id|mddev_t
op_star
id|mddev
comma
id|mdk_rdev_t
op_star
id|rdev
)paren
suffix:semicolon
DECL|member|hot_remove_disk
r_int
(paren
op_star
id|hot_remove_disk
)paren
(paren
id|mddev_t
op_star
id|mddev
comma
r_int
id|number
)paren
suffix:semicolon
DECL|member|spare_active
r_int
(paren
op_star
id|spare_active
)paren
(paren
id|mddev_t
op_star
id|mddev
)paren
suffix:semicolon
DECL|member|sync_request
r_int
(paren
op_star
id|sync_request
)paren
(paren
id|mddev_t
op_star
id|mddev
comma
id|sector_t
id|sector_nr
comma
r_int
id|go_faster
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Currently we index md_array directly, based on the minor&n; * number. This will have to change to dynamic allocation&n; * once we start supporting partitioning of md devices.&n; */
DECL|function|mdidx
r_static
r_inline
r_int
id|mdidx
(paren
id|mddev_t
op_star
id|mddev
)paren
(brace
r_return
id|mddev-&gt;__minor
suffix:semicolon
)brace
r_extern
id|mdk_rdev_t
op_star
id|find_rdev_nr
c_func
(paren
id|mddev_t
op_star
id|mddev
comma
r_int
id|nr
)paren
suffix:semicolon
multiline_comment|/*&n; * iterates through some rdev ringlist. It&squot;s safe to remove the&n; * current &squot;rdev&squot;. Dont touch &squot;tmp&squot; though.&n; */
DECL|macro|ITERATE_RDEV_GENERIC
mdefine_line|#define ITERATE_RDEV_GENERIC(head,rdev,tmp)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for ((tmp) = (head).next;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(rdev) = (list_entry((tmp), mdk_rdev_t, same_set)),&t;&bslash;&n;&t;&t;&t;(tmp) = (tmp)-&gt;next, (tmp)-&gt;prev != &amp;(head)&t;&bslash;&n;&t;&t;; )
multiline_comment|/*&n; * iterates through the &squot;same array disks&squot; ringlist&n; */
DECL|macro|ITERATE_RDEV
mdefine_line|#define ITERATE_RDEV(mddev,rdev,tmp)&t;&t;&t;&t;&t;&bslash;&n;&t;ITERATE_RDEV_GENERIC((mddev)-&gt;disks,rdev,tmp)
multiline_comment|/*&n; * Iterates through &squot;pending RAID disks&squot;&n; */
DECL|macro|ITERATE_RDEV_PENDING
mdefine_line|#define ITERATE_RDEV_PENDING(rdev,tmp)&t;&t;&t;&t;&t;&bslash;&n;&t;ITERATE_RDEV_GENERIC(pending_raid_disks,rdev,tmp)
DECL|struct|mdk_thread_s
r_typedef
r_struct
id|mdk_thread_s
(brace
DECL|member|run
r_void
(paren
op_star
id|run
)paren
(paren
id|mddev_t
op_star
id|mddev
)paren
suffix:semicolon
DECL|member|mddev
id|mddev_t
op_star
id|mddev
suffix:semicolon
DECL|member|wqueue
id|wait_queue_head_t
id|wqueue
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|event
r_struct
id|completion
op_star
id|event
suffix:semicolon
DECL|member|tsk
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|typedef|mdk_thread_t
)brace
id|mdk_thread_t
suffix:semicolon
DECL|macro|THREAD_WAKEUP
mdefine_line|#define THREAD_WAKEUP  0
DECL|macro|__wait_event_lock_irq
mdefine_line|#define __wait_event_lock_irq(wq, condition, lock) &t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;wait_queue_t __wait;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;init_waitqueue_entry(&amp;__wait, current);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;add_wait_queue(&amp;wq, &amp;__wait);&t;&t;&t;&t;&t;&bslash;&n;&t;for (;;) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_current_state(TASK_UNINTERRUPTIBLE);&t;&t;&bslash;&n;&t;&t;if (condition)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;spin_unlock_irq(&amp;lock);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;blk_run_queues();&t;&t;&t;&t;&t;&bslash;&n;&t;&t;schedule();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;spin_lock_irq(&amp;lock);&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;current-&gt;state = TASK_RUNNING;&t;&t;&t;&t;&t;&bslash;&n;&t;remove_wait_queue(&amp;wq, &amp;__wait);&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|wait_event_lock_irq
mdefine_line|#define wait_event_lock_irq(wq, condition, lock) &t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (condition)&t; &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__wait_event_lock_irq(wq, condition, lock);&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__wait_disk_event
mdefine_line|#define __wait_disk_event(wq, condition) &t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;wait_queue_t __wait;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;init_waitqueue_entry(&amp;__wait, current);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;add_wait_queue(&amp;wq, &amp;__wait);&t;&t;&t;&t;&t;&bslash;&n;&t;for (;;) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_current_state(TASK_UNINTERRUPTIBLE);&t;&t;&bslash;&n;&t;&t;if (condition)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;blk_run_queues();&t;&t;&t;&t;&t;&bslash;&n;&t;&t;schedule();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;current-&gt;state = TASK_RUNNING;&t;&t;&t;&t;&t;&bslash;&n;&t;remove_wait_queue(&amp;wq, &amp;__wait);&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|wait_disk_event
mdefine_line|#define wait_disk_event(wq, condition) &t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (condition)&t; &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__wait_disk_event(wq, condition);&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif
eof
