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
op_minus
l_int|4
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
op_minus
l_int|1
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
op_minus
l_int|4
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
op_minus
l_int|1
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
macro_line|#if (MINORBITS != 8)
macro_line|#error MD doesnt handle bigger kdev yet
macro_line|#endif
DECL|macro|MAX_MD_DEVS
mdefine_line|#define MAX_MD_DEVS  (1&lt;&lt;MINORBITS)&t;/* Max number of md dev */
multiline_comment|/*&n; * Maps a kdev to an mddev/subdev. How &squot;data&squot; is handled is up to&n; * the personality. (eg. HSM uses this to identify individual LVs)&n; */
DECL|struct|dev_mapping_s
r_typedef
r_struct
id|dev_mapping_s
(brace
DECL|member|mddev
id|mddev_t
op_star
id|mddev
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|typedef|dev_mapping_t
)brace
id|dev_mapping_t
suffix:semicolon
r_extern
id|dev_mapping_t
id|mddev_map
(braket
id|MAX_MD_DEVS
)braket
suffix:semicolon
DECL|function|kdev_to_mddev
r_static
r_inline
id|mddev_t
op_star
id|kdev_to_mddev
(paren
id|kdev_t
id|dev
)paren
(brace
r_if
c_cond
(paren
id|major
c_func
(paren
id|dev
)paren
op_ne
id|MD_MAJOR
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
id|mddev_map
(braket
id|minor
c_func
(paren
id|dev
)paren
)braket
dot
id|mddev
suffix:semicolon
)brace
multiline_comment|/*&n; * options passed in raidrun:&n; */
DECL|macro|MAX_CHUNK_SIZE
mdefine_line|#define MAX_CHUNK_SIZE (4096*1024)
multiline_comment|/*&n; * default readahead&n; */
DECL|macro|MD_READAHEAD
mdefine_line|#define MD_READAHEAD&t;MAX_READAHEAD
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
DECL|member|all
r_struct
id|list_head
id|all
suffix:semicolon
multiline_comment|/* all RAID devices */
DECL|member|pending
r_struct
id|list_head
id|pending
suffix:semicolon
multiline_comment|/* undetected RAID devices */
DECL|member|dev
id|kdev_t
id|dev
suffix:semicolon
multiline_comment|/* Device number */
DECL|member|old_dev
id|kdev_t
id|old_dev
suffix:semicolon
multiline_comment|/*  &quot;&quot; when it was last imported */
DECL|member|size
r_int
r_int
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
DECL|member|sb
id|mdp_super_t
op_star
id|sb
suffix:semicolon
DECL|member|sb_offset
r_int
r_int
id|sb_offset
suffix:semicolon
DECL|member|alias_device
r_int
id|alias_device
suffix:semicolon
multiline_comment|/* device alias to the same disk */
DECL|member|faulty
r_int
id|faulty
suffix:semicolon
multiline_comment|/* if faulty do not issue IO requests */
DECL|member|desc_nr
r_int
id|desc_nr
suffix:semicolon
multiline_comment|/* descriptor index in the superblock */
)brace
suffix:semicolon
multiline_comment|/*&n; * disk operations in a working array:&n; */
DECL|macro|DISKOP_SPARE_INACTIVE
mdefine_line|#define DISKOP_SPARE_INACTIVE&t;0
DECL|macro|DISKOP_SPARE_WRITE
mdefine_line|#define DISKOP_SPARE_WRITE&t;1
DECL|macro|DISKOP_SPARE_ACTIVE
mdefine_line|#define DISKOP_SPARE_ACTIVE&t;2
DECL|macro|DISKOP_HOT_REMOVE_DISK
mdefine_line|#define DISKOP_HOT_REMOVE_DISK&t;3
DECL|macro|DISKOP_HOT_ADD_DISK
mdefine_line|#define DISKOP_HOT_ADD_DISK&t;4
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
DECL|member|sb
id|mdp_super_t
op_star
id|sb
suffix:semicolon
DECL|member|nb_dev
r_int
id|nb_dev
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
DECL|member|param
id|mdu_param_t
id|param
suffix:semicolon
DECL|member|ro
r_int
id|ro
suffix:semicolon
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
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|recovery_running
r_int
id|recovery_running
suffix:semicolon
DECL|member|reconfig_sem
r_struct
id|semaphore
id|reconfig_sem
suffix:semicolon
DECL|member|recovery_sem
r_struct
id|semaphore
id|recovery_sem
suffix:semicolon
DECL|member|resync_sem
r_struct
id|semaphore
id|resync_sem
suffix:semicolon
DECL|member|active
id|atomic_t
id|active
suffix:semicolon
DECL|member|recovery_active
id|atomic_t
id|recovery_active
suffix:semicolon
multiline_comment|/* blocks scheduled, but not written */
DECL|member|recovery_wait
id|wait_queue_head_t
id|recovery_wait
suffix:semicolon
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
DECL|member|make_request
r_int
(paren
op_star
id|make_request
)paren
(paren
id|mddev_t
op_star
id|mddev
comma
r_int
id|rw
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
r_int
(paren
op_star
id|status
)paren
(paren
r_char
op_star
id|page
comma
id|mddev_t
op_star
id|mddev
)paren
suffix:semicolon
DECL|member|error_handler
r_int
(paren
op_star
id|error_handler
)paren
(paren
id|mddev_t
op_star
id|mddev
comma
id|kdev_t
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n; * Some personalities (RAID-1, RAID-5) can have disks hot-added and&n; * hot-removed. Hot removal is different from failure. (failure marks&n; * a disk inactive, but the disk is still part of the array) The interface&n; * to such operations is the &squot;pers-&gt;diskop()&squot; function, can be NULL.&n; *&n; * the diskop function can change the pointer pointing to the incoming&n; * descriptor, but must do so very carefully. (currently only&n; * SPARE_ACTIVE expects such a change)&n; */
DECL|member|diskop
r_int
(paren
op_star
id|diskop
)paren
(paren
id|mddev_t
op_star
id|mddev
comma
id|mdp_disk_t
op_star
op_star
id|descriptor
comma
r_int
id|state
)paren
suffix:semicolon
DECL|member|stop_resync
r_int
(paren
op_star
id|stop_resync
)paren
(paren
id|mddev_t
op_star
id|mddev
)paren
suffix:semicolon
DECL|member|restart_resync
r_int
(paren
op_star
id|restart_resync
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
DECL|function|mddev_to_kdev
r_static
r_inline
id|kdev_t
id|mddev_to_kdev
c_func
(paren
id|mddev_t
op_star
id|mddev
)paren
(brace
r_return
id|mk_kdev
c_func
(paren
id|MD_MAJOR
comma
id|mdidx
c_func
(paren
id|mddev
)paren
)paren
suffix:semicolon
)brace
r_extern
id|mdk_rdev_t
op_star
id|find_rdev
c_func
(paren
id|mddev_t
op_star
id|mddev
comma
id|kdev_t
id|dev
)paren
suffix:semicolon
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
r_extern
id|mdp_disk_t
op_star
id|get_spare
c_func
(paren
id|mddev_t
op_star
id|mddev
)paren
suffix:semicolon
multiline_comment|/*&n; * iterates through some rdev ringlist. It&squot;s safe to remove the&n; * current &squot;rdev&squot;. Dont touch &squot;tmp&squot; though.&n; */
DECL|macro|ITERATE_RDEV_GENERIC
mdefine_line|#define ITERATE_RDEV_GENERIC(head,field,rdev,tmp)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for ((tmp) = (head).next;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(rdev) = (list_entry((tmp), mdk_rdev_t, field)),&t;&bslash;&n;&t;&t;&t;(tmp) = (tmp)-&gt;next, (tmp)-&gt;prev != &amp;(head)&t;&bslash;&n;&t;&t;; )
multiline_comment|/*&n; * iterates through the &squot;same array disks&squot; ringlist&n; */
DECL|macro|ITERATE_RDEV
mdefine_line|#define ITERATE_RDEV(mddev,rdev,tmp)&t;&t;&t;&t;&t;&bslash;&n;&t;ITERATE_RDEV_GENERIC((mddev)-&gt;disks,same_set,rdev,tmp)
multiline_comment|/*&n; * Same as above, but assumes that the device has rdev-&gt;desc_nr numbered&n; * from 0 to mddev-&gt;nb_dev, and iterates through rdevs in ascending order.&n; */
DECL|macro|ITERATE_RDEV_ORDERED
mdefine_line|#define ITERATE_RDEV_ORDERED(mddev,rdev,i)&t;&t;&t;&t;&bslash;&n;&t;for (i = 0; rdev = find_rdev_nr(mddev, i), i &lt; mddev-&gt;nb_dev; i++)
multiline_comment|/*&n; * Iterates through all &squot;RAID managed disks&squot;&n; */
DECL|macro|ITERATE_RDEV_ALL
mdefine_line|#define ITERATE_RDEV_ALL(rdev,tmp)&t;&t;&t;&t;&t;&bslash;&n;&t;ITERATE_RDEV_GENERIC(all_raid_disks,all,rdev,tmp)
multiline_comment|/*&n; * Iterates through &squot;pending RAID disks&squot;&n; */
DECL|macro|ITERATE_RDEV_PENDING
mdefine_line|#define ITERATE_RDEV_PENDING(rdev,tmp)&t;&t;&t;&t;&t;&bslash;&n;&t;ITERATE_RDEV_GENERIC(pending_raid_disks,pending,rdev,tmp)
multiline_comment|/*&n; * iterates through all used mddevs in the system.&n; */
DECL|macro|ITERATE_MDDEV
mdefine_line|#define ITERATE_MDDEV(mddev,tmp)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (tmp = all_mddevs.next;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;mddev = list_entry(tmp, mddev_t, all_mddevs),&t;&bslash;&n;&t;&t;&t;tmp = tmp-&gt;next, tmp-&gt;prev != &amp;all_mddevs&t;&bslash;&n;&t;&t;; )
DECL|function|lock_mddev
r_static
r_inline
r_int
id|lock_mddev
(paren
id|mddev_t
op_star
id|mddev
)paren
(brace
r_return
id|down_interruptible
c_func
(paren
op_amp
id|mddev-&gt;reconfig_sem
)paren
suffix:semicolon
)brace
DECL|function|unlock_mddev
r_static
r_inline
r_void
id|unlock_mddev
(paren
id|mddev_t
op_star
id|mddev
)paren
(brace
id|up
c_func
(paren
op_amp
id|mddev-&gt;reconfig_sem
)paren
suffix:semicolon
)brace
DECL|macro|xchg_values
mdefine_line|#define xchg_values(x,y) do { __typeof__(x) __tmp = x; &bslash;&n;&t;&t;&t;&t;x = y; y = __tmp; } while (0)
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
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
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
DECL|macro|MAX_DISKNAME_LEN
mdefine_line|#define MAX_DISKNAME_LEN 64
DECL|struct|dev_name_s
r_typedef
r_struct
id|dev_name_s
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|dev
id|kdev_t
id|dev
suffix:semicolon
DECL|member|namebuf
r_char
id|namebuf
(braket
id|MAX_DISKNAME_LEN
)braket
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|typedef|dev_name_t
)brace
id|dev_name_t
suffix:semicolon
DECL|macro|__wait_event_lock_irq
mdefine_line|#define __wait_event_lock_irq(wq, condition, lock) &t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;wait_queue_t __wait;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;init_waitqueue_entry(&amp;__wait, current);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;add_wait_queue(&amp;wq, &amp;__wait);&t;&t;&t;&t;&t;&bslash;&n;&t;for (;;) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_current_state(TASK_UNINTERRUPTIBLE);&t;&t;&bslash;&n;&t;&t;if (condition)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;spin_unlock_irq(&amp;lock);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;run_task_queue(&amp;tq_disk);&t;&t;&t;&t;&bslash;&n;&t;&t;schedule();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;spin_lock_irq(&amp;lock);&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;current-&gt;state = TASK_RUNNING;&t;&t;&t;&t;&t;&bslash;&n;&t;remove_wait_queue(&amp;wq, &amp;__wait);&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|wait_event_lock_irq
mdefine_line|#define wait_event_lock_irq(wq, condition, lock) &t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (condition)&t; &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__wait_event_lock_irq(wq, condition, lock);&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__wait_disk_event
mdefine_line|#define __wait_disk_event(wq, condition) &t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;wait_queue_t __wait;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;init_waitqueue_entry(&amp;__wait, current);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;add_wait_queue(&amp;wq, &amp;__wait);&t;&t;&t;&t;&t;&bslash;&n;&t;for (;;) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_current_state(TASK_UNINTERRUPTIBLE);&t;&t;&bslash;&n;&t;&t;if (condition)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;run_task_queue(&amp;tq_disk);&t;&t;&t;&t;&bslash;&n;&t;&t;schedule();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;current-&gt;state = TASK_RUNNING;&t;&t;&t;&t;&t;&bslash;&n;&t;remove_wait_queue(&amp;wq, &amp;__wait);&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|wait_disk_event
mdefine_line|#define wait_disk_event(wq, condition) &t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (condition)&t; &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__wait_disk_event(wq, condition);&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif 
eof
