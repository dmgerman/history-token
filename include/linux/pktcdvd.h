multiline_comment|/*&n; * Copyright (C) 2000 Jens Axboe &lt;axboe@suse.de&gt;&n; * Copyright (C) 2001-2004 Peter Osterlund &lt;petero2@telia.com&gt;&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * Packet writing layer for ATAPI and SCSI CD-R, CD-RW, DVD-R, and&n; * DVD-RW devices.&n; *&n; */
macro_line|#ifndef __PKTCDVD_H
DECL|macro|__PKTCDVD_H
mdefine_line|#define __PKTCDVD_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * 1 for normal debug messages, 2 is very verbose. 0 to turn it off.&n; */
DECL|macro|PACKET_DEBUG
mdefine_line|#define PACKET_DEBUG&t;&t;1
DECL|macro|MAX_WRITERS
mdefine_line|#define&t;MAX_WRITERS&t;&t;8
DECL|macro|PKT_RB_POOL_SIZE
mdefine_line|#define PKT_RB_POOL_SIZE&t;512
multiline_comment|/*&n; * How long we should hold a non-full packet before starting data gathering.&n; */
DECL|macro|PACKET_WAIT_TIME
mdefine_line|#define PACKET_WAIT_TIME&t;(HZ * 5 / 1000)
multiline_comment|/*&n; * use drive write caching -- we need deferred error handling to be&n; * able to sucessfully recover with this option (drive will return good&n; * status as soon as the cdb is validated).&n; */
macro_line|#if defined(CONFIG_CDROM_PKTCDVD_WCACHE)
DECL|macro|USE_WCACHING
mdefine_line|#define USE_WCACHING&t;&t;1
macro_line|#else
DECL|macro|USE_WCACHING
mdefine_line|#define USE_WCACHING&t;&t;0
macro_line|#endif
multiline_comment|/*&n; * No user-servicable parts beyond this point -&gt;&n; */
multiline_comment|/*&n; * device types&n; */
DECL|macro|PACKET_CDR
mdefine_line|#define PACKET_CDR&t;&t;1
DECL|macro|PACKET_CDRW
mdefine_line|#define&t;PACKET_CDRW&t;&t;2
DECL|macro|PACKET_DVDR
mdefine_line|#define PACKET_DVDR&t;&t;3
DECL|macro|PACKET_DVDRW
mdefine_line|#define PACKET_DVDRW&t;&t;4
multiline_comment|/*&n; * flags&n; */
DECL|macro|PACKET_WRITABLE
mdefine_line|#define PACKET_WRITABLE&t;&t;1&t;/* pd is writable */
DECL|macro|PACKET_NWA_VALID
mdefine_line|#define PACKET_NWA_VALID&t;2&t;/* next writable address valid */
DECL|macro|PACKET_LRA_VALID
mdefine_line|#define PACKET_LRA_VALID&t;3&t;/* last recorded address valid */
DECL|macro|PACKET_MERGE_SEGS
mdefine_line|#define PACKET_MERGE_SEGS&t;4&t;/* perform segment merging to keep */
multiline_comment|/* underlying cdrom device happy */
multiline_comment|/*&n; * Disc status -- from READ_DISC_INFO&n; */
DECL|macro|PACKET_DISC_EMPTY
mdefine_line|#define PACKET_DISC_EMPTY&t;0
DECL|macro|PACKET_DISC_INCOMPLETE
mdefine_line|#define PACKET_DISC_INCOMPLETE&t;1
DECL|macro|PACKET_DISC_COMPLETE
mdefine_line|#define PACKET_DISC_COMPLETE&t;2
DECL|macro|PACKET_DISC_OTHER
mdefine_line|#define PACKET_DISC_OTHER&t;3
multiline_comment|/*&n; * write type, and corresponding data block type&n; */
DECL|macro|PACKET_MODE1
mdefine_line|#define PACKET_MODE1&t;&t;1
DECL|macro|PACKET_MODE2
mdefine_line|#define PACKET_MODE2&t;&t;2
DECL|macro|PACKET_BLOCK_MODE1
mdefine_line|#define PACKET_BLOCK_MODE1&t;8
DECL|macro|PACKET_BLOCK_MODE2
mdefine_line|#define PACKET_BLOCK_MODE2&t;10
multiline_comment|/*&n; * Last session/border status&n; */
DECL|macro|PACKET_SESSION_EMPTY
mdefine_line|#define PACKET_SESSION_EMPTY&t;&t;0
DECL|macro|PACKET_SESSION_INCOMPLETE
mdefine_line|#define PACKET_SESSION_INCOMPLETE&t;1
DECL|macro|PACKET_SESSION_RESERVED
mdefine_line|#define PACKET_SESSION_RESERVED&t;&t;2
DECL|macro|PACKET_SESSION_COMPLETE
mdefine_line|#define PACKET_SESSION_COMPLETE&t;&t;3
DECL|macro|PACKET_MCN
mdefine_line|#define PACKET_MCN&t;&t;&t;&quot;4a656e734178626f65323030300000&quot;
DECL|macro|PACKET_USE_LS
macro_line|#undef PACKET_USE_LS
DECL|macro|PKT_CTRL_CMD_SETUP
mdefine_line|#define PKT_CTRL_CMD_SETUP&t;0
DECL|macro|PKT_CTRL_CMD_TEARDOWN
mdefine_line|#define PKT_CTRL_CMD_TEARDOWN&t;1
DECL|macro|PKT_CTRL_CMD_STATUS
mdefine_line|#define PKT_CTRL_CMD_STATUS&t;2
DECL|struct|pkt_ctrl_command
r_struct
id|pkt_ctrl_command
(brace
DECL|member|command
id|__u32
id|command
suffix:semicolon
multiline_comment|/* in: Setup, teardown, status */
DECL|member|dev_index
id|__u32
id|dev_index
suffix:semicolon
multiline_comment|/* in/out: Device index */
DECL|member|dev
id|__u32
id|dev
suffix:semicolon
multiline_comment|/* in/out: Device nr for cdrw device */
DECL|member|pkt_dev
id|__u32
id|pkt_dev
suffix:semicolon
multiline_comment|/* in/out: Device nr for packet device */
DECL|member|num_devices
id|__u32
id|num_devices
suffix:semicolon
multiline_comment|/* out: Largest device index + 1 */
DECL|member|padding
id|__u32
id|padding
suffix:semicolon
multiline_comment|/* Not used */
)brace
suffix:semicolon
multiline_comment|/*&n; * packet ioctls&n; */
DECL|macro|PACKET_IOCTL_MAGIC
mdefine_line|#define PACKET_IOCTL_MAGIC&t;(&squot;X&squot;)
DECL|macro|PACKET_CTRL_CMD
mdefine_line|#define PACKET_CTRL_CMD&t;&t;_IOWR(PACKET_IOCTL_MAGIC, 1, struct pkt_ctrl_command)
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/cdrom.h&gt;
DECL|struct|packet_settings
r_struct
id|packet_settings
(brace
DECL|member|size
id|__u8
id|size
suffix:semicolon
multiline_comment|/* packet size in (512 byte) sectors */
DECL|member|fp
id|__u8
id|fp
suffix:semicolon
multiline_comment|/* fixed packets */
DECL|member|link_loss
id|__u8
id|link_loss
suffix:semicolon
multiline_comment|/* the rest is specified&n;&t;&t;&t;&t;&t;&t; * as per Mt Fuji */
DECL|member|write_type
id|__u8
id|write_type
suffix:semicolon
DECL|member|track_mode
id|__u8
id|track_mode
suffix:semicolon
DECL|member|block_mode
id|__u8
id|block_mode
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Very crude stats for now&n; */
DECL|struct|packet_stats
r_struct
id|packet_stats
(brace
DECL|member|pkt_started
r_int
r_int
id|pkt_started
suffix:semicolon
DECL|member|pkt_ended
r_int
r_int
id|pkt_ended
suffix:semicolon
DECL|member|secs_w
r_int
r_int
id|secs_w
suffix:semicolon
DECL|member|secs_rg
r_int
r_int
id|secs_rg
suffix:semicolon
DECL|member|secs_r
r_int
r_int
id|secs_r
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|packet_cdrw
r_struct
id|packet_cdrw
(brace
DECL|member|pkt_free_list
r_struct
id|list_head
id|pkt_free_list
suffix:semicolon
DECL|member|pkt_active_list
r_struct
id|list_head
id|pkt_active_list
suffix:semicolon
DECL|member|active_list_lock
id|spinlock_t
id|active_list_lock
suffix:semicolon
multiline_comment|/* Serialize access to pkt_active_list */
DECL|member|thread
r_struct
id|task_struct
op_star
id|thread
suffix:semicolon
DECL|member|pending_bios
id|atomic_t
id|pending_bios
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Switch to high speed reading after reading this many kilobytes&n; * with no interspersed writes.&n; */
DECL|macro|HI_SPEED_SWITCH
mdefine_line|#define HI_SPEED_SWITCH 512
DECL|struct|packet_iosched
r_struct
id|packet_iosched
(brace
DECL|member|attention
id|atomic_t
id|attention
suffix:semicolon
multiline_comment|/* Set to non-zero when queue processing is needed */
DECL|member|writing
r_int
id|writing
suffix:semicolon
multiline_comment|/* Non-zero when writing, zero when reading */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* Protecting read/write queue manipulations */
DECL|member|read_queue
r_struct
id|bio
op_star
id|read_queue
suffix:semicolon
DECL|member|read_queue_tail
r_struct
id|bio
op_star
id|read_queue_tail
suffix:semicolon
DECL|member|write_queue
r_struct
id|bio
op_star
id|write_queue
suffix:semicolon
DECL|member|write_queue_tail
r_struct
id|bio
op_star
id|write_queue_tail
suffix:semicolon
DECL|member|high_prio_read
r_int
id|high_prio_read
suffix:semicolon
multiline_comment|/* An important read request has been queued */
DECL|member|successive_reads
r_int
id|successive_reads
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * 32 buffers of 2048 bytes&n; */
DECL|macro|PACKET_MAX_SIZE
mdefine_line|#define PACKET_MAX_SIZE&t;&t;32
DECL|macro|PAGES_PER_PACKET
mdefine_line|#define PAGES_PER_PACKET&t;(PACKET_MAX_SIZE * CD_FRAMESIZE / PAGE_SIZE)
DECL|macro|PACKET_MAX_SECTORS
mdefine_line|#define PACKET_MAX_SECTORS&t;(PACKET_MAX_SIZE * CD_FRAMESIZE &gt;&gt; 9)
DECL|enum|packet_data_state
r_enum
id|packet_data_state
(brace
DECL|enumerator|PACKET_IDLE_STATE
id|PACKET_IDLE_STATE
comma
multiline_comment|/* Not used at the moment */
DECL|enumerator|PACKET_WAITING_STATE
id|PACKET_WAITING_STATE
comma
multiline_comment|/* Waiting for more bios to arrive, so */
multiline_comment|/* we don&squot;t have to do as much */
multiline_comment|/* data gathering */
DECL|enumerator|PACKET_READ_WAIT_STATE
id|PACKET_READ_WAIT_STATE
comma
multiline_comment|/* Waiting for reads to fill in holes */
DECL|enumerator|PACKET_WRITE_WAIT_STATE
id|PACKET_WRITE_WAIT_STATE
comma
multiline_comment|/* Waiting for the write to complete */
DECL|enumerator|PACKET_RECOVERY_STATE
id|PACKET_RECOVERY_STATE
comma
multiline_comment|/* Recover after read/write errors */
DECL|enumerator|PACKET_FINISHED_STATE
id|PACKET_FINISHED_STATE
comma
multiline_comment|/* After write has finished */
DECL|enumerator|PACKET_NUM_STATES
id|PACKET_NUM_STATES
multiline_comment|/* Number of possible states */
)brace
suffix:semicolon
multiline_comment|/*&n; * Information needed for writing a single packet&n; */
r_struct
id|pktcdvd_device
suffix:semicolon
DECL|struct|packet_data
r_struct
id|packet_data
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* Lock protecting state transitions and */
multiline_comment|/* orig_bios list */
DECL|member|orig_bios
r_struct
id|bio
op_star
id|orig_bios
suffix:semicolon
multiline_comment|/* Original bios passed to pkt_make_request */
DECL|member|orig_bios_tail
r_struct
id|bio
op_star
id|orig_bios_tail
suffix:semicolon
multiline_comment|/* that will be handled by this packet */
DECL|member|write_size
r_int
id|write_size
suffix:semicolon
multiline_comment|/* Total size of all bios in the orig_bios */
multiline_comment|/* list, measured in number of frames */
DECL|member|w_bio
r_struct
id|bio
op_star
id|w_bio
suffix:semicolon
multiline_comment|/* The bio we will send to the real CD */
multiline_comment|/* device once we have all data for the */
multiline_comment|/* packet we are going to write */
DECL|member|sector
id|sector_t
id|sector
suffix:semicolon
multiline_comment|/* First sector in this packet */
DECL|member|frames
r_int
id|frames
suffix:semicolon
multiline_comment|/* Number of frames in this packet */
DECL|member|state
r_enum
id|packet_data_state
id|state
suffix:semicolon
multiline_comment|/* Current state */
DECL|member|run_sm
id|atomic_t
id|run_sm
suffix:semicolon
multiline_comment|/* Incremented whenever the state */
multiline_comment|/* machine needs to be run */
DECL|member|sleep_time
r_int
id|sleep_time
suffix:semicolon
multiline_comment|/* Set this to non-zero to make the state */
multiline_comment|/* machine run after this many jiffies. */
DECL|member|io_wait
id|atomic_t
id|io_wait
suffix:semicolon
multiline_comment|/* Number of pending IO operations */
DECL|member|io_errors
id|atomic_t
id|io_errors
suffix:semicolon
multiline_comment|/* Number of read/write errors during IO */
DECL|member|r_bios
r_struct
id|bio
op_star
id|r_bios
(braket
id|PACKET_MAX_SIZE
)braket
suffix:semicolon
multiline_comment|/* bios to use during data gathering */
DECL|member|pages
r_struct
id|page
op_star
id|pages
(braket
id|PAGES_PER_PACKET
)braket
suffix:semicolon
DECL|member|cache_valid
r_int
id|cache_valid
suffix:semicolon
multiline_comment|/* If non-zero, the data for the zone defined */
multiline_comment|/* by the sector variable is completely cached */
multiline_comment|/* in the pages[] vector. */
DECL|member|id
r_int
id|id
suffix:semicolon
multiline_comment|/* ID number for debugging */
DECL|member|pd
r_struct
id|pktcdvd_device
op_star
id|pd
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pkt_rb_node
r_struct
id|pkt_rb_node
(brace
DECL|member|rb_node
r_struct
id|rb_node
id|rb_node
suffix:semicolon
DECL|member|bio
r_struct
id|bio
op_star
id|bio
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|packet_stacked_data
r_struct
id|packet_stacked_data
(brace
DECL|member|bio
r_struct
id|bio
op_star
id|bio
suffix:semicolon
multiline_comment|/* Original read request bio */
DECL|member|pd
r_struct
id|pktcdvd_device
op_star
id|pd
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PSD_POOL_SIZE
mdefine_line|#define PSD_POOL_SIZE&t;&t;64
DECL|struct|pktcdvd_device
r_struct
id|pktcdvd_device
(brace
DECL|member|bdev
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
multiline_comment|/* dev attached */
DECL|member|pkt_dev
id|dev_t
id|pkt_dev
suffix:semicolon
multiline_comment|/* our dev */
DECL|member|name
r_char
id|name
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|settings
r_struct
id|packet_settings
id|settings
suffix:semicolon
DECL|member|stats
r_struct
id|packet_stats
id|stats
suffix:semicolon
DECL|member|refcnt
r_int
id|refcnt
suffix:semicolon
multiline_comment|/* Open count */
DECL|member|write_speed
r_int
id|write_speed
suffix:semicolon
multiline_comment|/* current write speed, kB/s */
DECL|member|read_speed
r_int
id|read_speed
suffix:semicolon
multiline_comment|/* current read speed, kB/s */
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/* start offset */
DECL|member|mode_offset
id|__u8
id|mode_offset
suffix:semicolon
multiline_comment|/* 0 / 8 */
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|mmc3_profile
id|__u16
id|mmc3_profile
suffix:semicolon
DECL|member|nwa
id|__u32
id|nwa
suffix:semicolon
multiline_comment|/* next writable address */
DECL|member|lra
id|__u32
id|lra
suffix:semicolon
multiline_comment|/* last recorded address */
DECL|member|cdrw
r_struct
id|packet_cdrw
id|cdrw
suffix:semicolon
DECL|member|wqueue
id|wait_queue_head_t
id|wqueue
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* Serialize access to bio_queue */
DECL|member|bio_queue
r_struct
id|rb_root
id|bio_queue
suffix:semicolon
multiline_comment|/* Work queue of bios we need to handle */
DECL|member|bio_queue_size
r_int
id|bio_queue_size
suffix:semicolon
multiline_comment|/* Number of nodes in bio_queue */
DECL|member|current_sector
id|sector_t
id|current_sector
suffix:semicolon
multiline_comment|/* Keep track of where the elevator is */
DECL|member|scan_queue
id|atomic_t
id|scan_queue
suffix:semicolon
multiline_comment|/* Set to non-zero when pkt_handle_queue */
multiline_comment|/* needs to be run. */
DECL|member|rb_pool
id|mempool_t
op_star
id|rb_pool
suffix:semicolon
multiline_comment|/* mempool for pkt_rb_node allocations */
DECL|member|iosched
r_struct
id|packet_iosched
id|iosched
suffix:semicolon
DECL|member|disk
r_struct
id|gendisk
op_star
id|disk
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __PKTCDVD_H */
eof
