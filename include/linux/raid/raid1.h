macro_line|#ifndef _RAID1_H
DECL|macro|_RAID1_H
mdefine_line|#define _RAID1_H
macro_line|#include &lt;linux/raid/md.h&gt;
DECL|typedef|mirror_info_t
r_typedef
r_struct
id|mirror_info
id|mirror_info_t
suffix:semicolon
DECL|struct|mirror_info
r_struct
id|mirror_info
(brace
DECL|member|number
r_int
id|number
suffix:semicolon
DECL|member|raid_disk
r_int
id|raid_disk
suffix:semicolon
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
DECL|member|head_position
id|sector_t
id|head_position
suffix:semicolon
DECL|member|nr_pending
id|atomic_t
id|nr_pending
suffix:semicolon
multiline_comment|/*&n;&t; * State bits:&n;&t; */
DECL|member|operational
r_int
id|operational
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
DECL|typedef|r1bio_t
r_typedef
r_struct
id|r1bio_s
id|r1bio_t
suffix:semicolon
DECL|struct|r1_private_data_s
r_struct
id|r1_private_data_s
(brace
DECL|member|mddev
id|mddev_t
op_star
id|mddev
suffix:semicolon
DECL|member|mirrors
id|mirror_info_t
id|mirrors
(braket
id|MD_SB_DISKS
)braket
suffix:semicolon
DECL|member|nr_disks
r_int
id|nr_disks
suffix:semicolon
DECL|member|raid_disks
r_int
id|raid_disks
suffix:semicolon
DECL|member|working_disks
r_int
id|working_disks
suffix:semicolon
DECL|member|last_used
r_int
id|last_used
suffix:semicolon
DECL|member|next_seq_sect
id|sector_t
id|next_seq_sect
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
DECL|member|resync_mirrors
r_int
id|resync_mirrors
suffix:semicolon
DECL|member|spare
id|mirror_info_t
op_star
id|spare
suffix:semicolon
DECL|member|device_lock
id|spinlock_t
id|device_lock
suffix:semicolon
multiline_comment|/* for use when syncing mirrors: */
DECL|member|resync_lock
id|spinlock_t
id|resync_lock
suffix:semicolon
DECL|member|nr_pending
r_int
id|nr_pending
suffix:semicolon
DECL|member|barrier
r_int
id|barrier
suffix:semicolon
DECL|member|next_resync
id|sector_t
id|next_resync
suffix:semicolon
DECL|member|wait_idle
id|wait_queue_head_t
id|wait_idle
suffix:semicolon
DECL|member|wait_resume
id|wait_queue_head_t
id|wait_resume
suffix:semicolon
DECL|member|r1bio_pool
id|mempool_t
op_star
id|r1bio_pool
suffix:semicolon
DECL|member|r1buf_pool
id|mempool_t
op_star
id|r1buf_pool
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|conf_t
r_typedef
r_struct
id|r1_private_data_s
id|conf_t
suffix:semicolon
multiline_comment|/*&n; * this is the only point in the RAID code where we violate&n; * C type safety. mddev-&gt;private is an &squot;opaque&squot; pointer.&n; */
DECL|macro|mddev_to_conf
mdefine_line|#define mddev_to_conf(mddev) ((conf_t *) mddev-&gt;private)
multiline_comment|/*&n; * this is our &squot;private&squot; RAID1 bio.&n; *&n; * it contains information about what kind of IO operations were started&n; * for this RAID1 operation, and about their status:&n; */
DECL|struct|r1bio_s
r_struct
id|r1bio_s
(brace
DECL|member|remaining
id|atomic_t
id|remaining
suffix:semicolon
multiline_comment|/* &squot;have we finished&squot; count,&n;&t;&t;&t;&t;&t;    * used from IRQ handlers&n;&t;&t;&t;&t;&t;    */
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
DECL|member|sector
id|sector_t
id|sector
suffix:semicolon
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|mddev
id|mddev_t
op_star
id|mddev
suffix:semicolon
multiline_comment|/*&n;&t; * original bio going to /dev/mdx&n;&t; */
DECL|member|master_bio
r_struct
id|bio
op_star
id|master_bio
suffix:semicolon
multiline_comment|/*&n;&t; * if the IO is in READ direction, then this bio is used:&n;&t; */
DECL|member|read_bio
r_struct
id|bio
op_star
id|read_bio
suffix:semicolon
DECL|member|read_disk
r_int
id|read_disk
suffix:semicolon
multiline_comment|/*&n;&t; * if the IO is in WRITE direction, then multiple bios are used:&n;&t; */
DECL|member|write_bios
r_struct
id|bio
op_star
id|write_bios
(braket
id|MD_SB_DISKS
)braket
suffix:semicolon
DECL|member|next_r1
id|r1bio_t
op_star
id|next_r1
suffix:semicolon
multiline_comment|/* next for retry or in free list */
DECL|member|retry_list
r_struct
id|list_head
id|retry_list
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* bits for r1bio.state */
DECL|macro|R1BIO_Uptodate
mdefine_line|#define&t;R1BIO_Uptodate&t;1
macro_line|#endif
eof
