macro_line|#ifndef _SCSI_SCSI_DEVICE_H
DECL|macro|_SCSI_SCSI_DEVICE_H
mdefine_line|#define _SCSI_SCSI_DEVICE_H
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
r_struct
id|request_queue
suffix:semicolon
r_struct
id|scsi_cmnd
suffix:semicolon
r_struct
id|scsi_mode_data
suffix:semicolon
DECL|struct|scsi_device
r_struct
id|scsi_device
(brace
DECL|member|sdev_classdev
r_struct
id|class_device
id|sdev_classdev
suffix:semicolon
DECL|member|siblings
r_struct
id|list_head
id|siblings
suffix:semicolon
multiline_comment|/* list of all devices on this host */
DECL|member|same_target_siblings
r_struct
id|list_head
id|same_target_siblings
suffix:semicolon
multiline_comment|/* just the devices sharing same target id */
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
DECL|member|request_queue
r_struct
id|request_queue
op_star
id|request_queue
suffix:semicolon
DECL|member|device_busy
r_volatile
r_int
r_int
id|device_busy
suffix:semicolon
multiline_comment|/* commands actually active on low-level */
DECL|member|sdev_lock
id|spinlock_t
id|sdev_lock
suffix:semicolon
multiline_comment|/* also the request queue_lock */
DECL|member|list_lock
id|spinlock_t
id|list_lock
suffix:semicolon
DECL|member|cmd_list
r_struct
id|list_head
id|cmd_list
suffix:semicolon
multiline_comment|/* queue of in use SCSI Command structures */
DECL|member|starved_entry
r_struct
id|list_head
id|starved_entry
suffix:semicolon
DECL|member|current_cmnd
r_struct
id|scsi_cmnd
op_star
id|current_cmnd
suffix:semicolon
multiline_comment|/* currently active command */
DECL|member|queue_depth
r_int
r_int
id|queue_depth
suffix:semicolon
multiline_comment|/* How deep of a queue we want */
DECL|member|last_queue_full_depth
r_int
r_int
id|last_queue_full_depth
suffix:semicolon
multiline_comment|/* These two are used by */
DECL|member|last_queue_full_count
r_int
r_int
id|last_queue_full_count
suffix:semicolon
multiline_comment|/* scsi_track_queue_full() */
DECL|member|last_queue_full_time
r_int
r_int
id|last_queue_full_time
suffix:semicolon
multiline_comment|/* don&squot;t let QUEUE_FULLs on the same&n;&t;&t;&t;&t;&t;   jiffie count on our counter, they&n;&t;&t;&t;&t;&t;   could all be from the same event. */
DECL|member|id
DECL|member|lun
DECL|member|channel
r_int
r_int
id|id
comma
id|lun
comma
id|channel
suffix:semicolon
DECL|member|manufacturer
r_int
r_int
id|manufacturer
suffix:semicolon
multiline_comment|/* Manufacturer of device, for using &n;&t;&t;&t;&t;&t; * vendor-specific cmd&squot;s */
DECL|member|sector_size
r_int
id|sector_size
suffix:semicolon
multiline_comment|/* size in bytes */
DECL|member|access_count
r_int
id|access_count
suffix:semicolon
multiline_comment|/* Count of open channels/mounts */
DECL|member|hostdata
r_void
op_star
id|hostdata
suffix:semicolon
multiline_comment|/* available to low-level driver */
DECL|member|devfs_name
r_char
id|devfs_name
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* devfs junk */
DECL|member|type
r_char
id|type
suffix:semicolon
DECL|member|scsi_level
r_char
id|scsi_level
suffix:semicolon
DECL|member|inquiry_len
r_int
r_char
id|inquiry_len
suffix:semicolon
multiline_comment|/* valid bytes in &squot;inquiry&squot; */
DECL|member|inquiry
r_int
r_char
op_star
id|inquiry
suffix:semicolon
multiline_comment|/* INQUIRY response data */
DECL|member|vendor
r_char
op_star
id|vendor
suffix:semicolon
multiline_comment|/* [back_compat] point into &squot;inquiry&squot; ... */
DECL|member|model
r_char
op_star
id|model
suffix:semicolon
multiline_comment|/* ... after scan; point to static string */
DECL|member|rev
r_char
op_star
id|rev
suffix:semicolon
multiline_comment|/* ... &quot;nullnullnullnull&quot; before scan */
DECL|member|current_tag
r_int
r_char
id|current_tag
suffix:semicolon
multiline_comment|/* current tag */
DECL|member|sdev_target
r_struct
id|scsi_target
op_star
id|sdev_target
suffix:semicolon
multiline_comment|/* used only for single_lun */
DECL|member|online
r_int
id|online
suffix:colon
l_int|1
suffix:semicolon
DECL|member|writeable
r_int
id|writeable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|removable
r_int
id|removable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|changed
r_int
id|changed
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Data invalid due to media change */
DECL|member|busy
r_int
id|busy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Used to prevent races */
DECL|member|lockable
r_int
id|lockable
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Able to prevent media removal */
DECL|member|locked
r_int
id|locked
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Media removal disabled */
DECL|member|borken
r_int
id|borken
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Tell the Seagate driver to be &n;&t;&t;&t;&t; * painfully slow on this device */
DECL|member|disconnect
r_int
id|disconnect
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* can disconnect */
DECL|member|soft_reset
r_int
id|soft_reset
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Uses soft reset option */
DECL|member|sdtr
r_int
id|sdtr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Device supports SDTR messages */
DECL|member|wdtr
r_int
id|wdtr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Device supports WDTR messages */
DECL|member|ppr
r_int
id|ppr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Device supports PPR messages */
DECL|member|tagged_supported
r_int
id|tagged_supported
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports SCSI-II tagged queuing */
DECL|member|tagged_queue
r_int
id|tagged_queue
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* This is going away!!!!  Look at simple_tags&n;&t;&t;&t;&t;   instead!!!  Please fix your driver now!! */
DECL|member|simple_tags
r_int
id|simple_tags
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* simple queue tag messages are enabled */
DECL|member|ordered_tags
r_int
id|ordered_tags
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ordered queue tag messages are enabled */
DECL|member|single_lun
r_int
id|single_lun
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Indicates we should only allow I/O to&n;&t;&t;&t;&t; * one of the luns for the device at a &n;&t;&t;&t;&t; * time. */
DECL|member|was_reset
r_int
id|was_reset
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* There was a bus reset on the bus for &n;&t;&t;&t;&t; * this device */
DECL|member|expecting_cc_ua
r_int
id|expecting_cc_ua
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Expecting a CHECK_CONDITION/UNIT_ATTN&n;&t;&t;&t;&t;     * because we did a bus reset. */
DECL|member|use_10_for_rw
r_int
id|use_10_for_rw
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* first try 10-byte read / write */
DECL|member|use_10_for_ms
r_int
id|use_10_for_ms
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* first try 10-byte mode sense/select */
DECL|member|no_start_on_add
r_int
id|no_start_on_add
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* do not issue start on add */
DECL|member|device_blocked
r_int
r_int
id|device_blocked
suffix:semicolon
multiline_comment|/* Device returned QUEUE_FULL. */
DECL|member|max_device_blocked
r_int
r_int
id|max_device_blocked
suffix:semicolon
multiline_comment|/* what device_blocked counts down from  */
DECL|macro|SCSI_DEFAULT_DEVICE_BLOCKED
mdefine_line|#define SCSI_DEFAULT_DEVICE_BLOCKED&t;3
DECL|member|sdev_driverfs_dev
r_struct
id|device
id|sdev_driverfs_dev
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_scsi_device
mdefine_line|#define&t;to_scsi_device(d)&t;&bslash;&n;&t;container_of(d, struct scsi_device, sdev_driverfs_dev)
r_extern
r_struct
id|scsi_device
op_star
id|scsi_add_device
c_func
(paren
r_struct
id|Scsi_Host
op_star
comma
id|uint
comma
id|uint
comma
id|uint
)paren
suffix:semicolon
r_extern
r_int
id|scsi_remove_device
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_set_device_offline
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_device_get
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_device_put
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_adjust_queue_depth
c_func
(paren
r_struct
id|scsi_device
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|scsi_track_queue_full
c_func
(paren
r_struct
id|scsi_device
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|scsi_set_medium_removal
c_func
(paren
r_struct
id|scsi_device
op_star
comma
r_char
)paren
suffix:semicolon
r_extern
r_int
id|scsi_mode_sense
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_int
id|dbd
comma
r_int
id|modepage
comma
r_int
r_char
op_star
id|buffer
comma
r_int
id|len
comma
r_int
id|timeout
comma
r_int
id|retries
comma
r_struct
id|scsi_mode_data
op_star
id|data
)paren
suffix:semicolon
macro_line|#endif /* _SCSI_SCSI_DEVICE_H */
eof
