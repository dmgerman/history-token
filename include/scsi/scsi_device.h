macro_line|#ifndef _SCSI_SCSI_DEVICE_H
DECL|macro|_SCSI_SCSI_DEVICE_H
mdefine_line|#define _SCSI_SCSI_DEVICE_H
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
r_struct
id|request_queue
suffix:semicolon
r_struct
id|scsi_cmnd
suffix:semicolon
r_struct
id|scsi_mode_data
suffix:semicolon
multiline_comment|/*&n; * sdev state: If you alter this, you also need to alter scsi_sysfs.c&n; * (for the ascii descriptions) and the state model enforcer:&n; * scsi_lib:scsi_device_set_state().&n; */
DECL|enum|scsi_device_state
r_enum
id|scsi_device_state
(brace
DECL|enumerator|SDEV_CREATED
id|SDEV_CREATED
op_assign
l_int|1
comma
multiline_comment|/* device created but not added to sysfs&n;&t;&t;&t;&t; * Only internal commands allowed (for inq) */
DECL|enumerator|SDEV_RUNNING
id|SDEV_RUNNING
comma
multiline_comment|/* device properly configured&n;&t;&t;&t;&t; * All commands allowed */
DECL|enumerator|SDEV_CANCEL
id|SDEV_CANCEL
comma
multiline_comment|/* beginning to delete device&n;&t;&t;&t;&t; * Only error handler commands allowed */
DECL|enumerator|SDEV_DEL
id|SDEV_DEL
comma
multiline_comment|/* device deleted &n;&t;&t;&t;&t; * no commands allowed */
DECL|enumerator|SDEV_QUIESCE
id|SDEV_QUIESCE
comma
multiline_comment|/* Device quiescent.  No block commands&n;&t;&t;&t;&t; * will be accepted, only specials (which&n;&t;&t;&t;&t; * originate in the mid-layer) */
DECL|enumerator|SDEV_OFFLINE
id|SDEV_OFFLINE
comma
multiline_comment|/* Device offlined (by error handling or&n;&t;&t;&t;&t; * user request */
DECL|enumerator|SDEV_BLOCK
id|SDEV_BLOCK
comma
multiline_comment|/* Device blocked by scsi lld.  No scsi &n;&t;&t;&t;&t; * commands from user or midlayer should be issued&n;&t;&t;&t;&t; * to the scsi lld. */
)brace
suffix:semicolon
DECL|struct|scsi_device
r_struct
id|scsi_device
(brace
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
multiline_comment|/* the next two are protected by the host-&gt;host_lock */
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
DECL|member|inq_periph_qual
r_char
id|inq_periph_qual
suffix:semicolon
multiline_comment|/* PQ from INQUIRY data */
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
DECL|member|sdev_bflags
r_int
r_int
id|sdev_bflags
suffix:semicolon
multiline_comment|/* black/white flags as also found in&n;&t;&t;&t;&t; * scsi_devinfo.[hc]. For now used only to&n;&t;&t;&t;&t; * pass settings from slave_alloc to scsi&n;&t;&t;&t;&t; * core. */
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
DECL|member|skip_ms_page_8
r_int
id|skip_ms_page_8
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* do not use MODE SENSE page 0x08 */
DECL|member|skip_ms_page_3f
r_int
id|skip_ms_page_3f
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* do not use MODE SENSE page 0x3f */
DECL|member|use_192_bytes_for_3f
r_int
id|use_192_bytes_for_3f
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ask for 192 bytes from page 0x3f */
DECL|member|no_start_on_add
r_int
id|no_start_on_add
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* do not issue start on add */
DECL|member|allow_restart
r_int
id|allow_restart
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* issue START_UNIT in error handler */
DECL|member|no_uld_attach
r_int
id|no_uld_attach
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* disable connecting to upper level drivers */
DECL|member|select_no_atn
r_int
id|select_no_atn
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fix_capacity
r_int
id|fix_capacity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* READ_CAPACITY is too high by 1 */
DECL|member|retry_hwerror
r_int
id|retry_hwerror
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Retry HARDWARE_ERROR */
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
DECL|member|iorequest_cnt
id|atomic_t
id|iorequest_cnt
suffix:semicolon
DECL|member|iodone_cnt
id|atomic_t
id|iodone_cnt
suffix:semicolon
DECL|member|ioerr_cnt
id|atomic_t
id|ioerr_cnt
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
DECL|member|sdev_gendev
r_struct
id|device
id|sdev_gendev
suffix:semicolon
DECL|member|sdev_classdev
r_struct
id|class_device
id|sdev_classdev
suffix:semicolon
DECL|member|sdev_state
r_enum
id|scsi_device_state
id|sdev_state
suffix:semicolon
DECL|member|sdev_data
r_int
r_int
id|sdev_data
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
)paren
suffix:semicolon
DECL|macro|to_scsi_device
mdefine_line|#define&t;to_scsi_device(d)&t;&bslash;&n;&t;container_of(d, struct scsi_device, sdev_gendev)
DECL|macro|class_to_sdev
mdefine_line|#define&t;class_to_sdev(d)&t;&bslash;&n;&t;container_of(d, struct scsi_device, sdev_classdev)
DECL|macro|transport_class_to_sdev
mdefine_line|#define transport_class_to_sdev(class_dev) &bslash;&n;&t;to_scsi_device(class_dev-&gt;dev)
multiline_comment|/*&n; * scsi_target: representation of a scsi target, for now, this is only&n; * used for single_lun devices. If no one has active IO to the target,&n; * starget_sdev_user is NULL, else it points to the active sdev.&n; */
DECL|struct|scsi_target
r_struct
id|scsi_target
(brace
DECL|member|starget_sdev_user
r_struct
id|scsi_device
op_star
id|starget_sdev_user
suffix:semicolon
DECL|member|siblings
r_struct
id|list_head
id|siblings
suffix:semicolon
DECL|member|devices
r_struct
id|list_head
id|devices
suffix:semicolon
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
DECL|member|reap_ref
r_int
r_int
id|reap_ref
suffix:semicolon
multiline_comment|/* protected by the host lock */
DECL|member|channel
r_int
r_int
id|channel
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
multiline_comment|/* target id ... replace&n;&t;&t;&t;&t;     * scsi_device.id eventually */
DECL|member|create
r_int
r_int
id|create
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* signal that it needs to be added */
DECL|member|starget_data
r_int
r_int
id|starget_data
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
)paren
suffix:semicolon
DECL|macro|to_scsi_target
mdefine_line|#define to_scsi_target(d)&t;container_of(d, struct scsi_target, dev)
DECL|function|scsi_target
r_static
r_inline
r_struct
id|scsi_target
op_star
id|scsi_target
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
r_return
id|to_scsi_target
c_func
(paren
id|sdev-&gt;sdev_gendev.parent
)paren
suffix:semicolon
)brace
DECL|macro|transport_class_to_starget
mdefine_line|#define transport_class_to_starget(class_dev) &bslash;&n;&t;to_scsi_target(class_dev-&gt;dev)
r_extern
r_struct
id|scsi_device
op_star
id|__scsi_add_device
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
comma
r_void
op_star
id|hostdata
)paren
suffix:semicolon
DECL|macro|scsi_add_device
mdefine_line|#define scsi_add_device(host, channel, target, lun) &bslash;&n;&t;__scsi_add_device(host, channel, target, lun, NULL)
r_extern
r_void
id|scsi_remove_device
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_device_cancel
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
r_struct
id|scsi_device
op_star
id|scsi_device_lookup
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
r_struct
id|scsi_device
op_star
id|__scsi_device_lookup
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
r_struct
id|scsi_device
op_star
id|scsi_device_lookup_by_target
c_func
(paren
r_struct
id|scsi_target
op_star
comma
id|uint
)paren
suffix:semicolon
r_extern
r_struct
id|scsi_device
op_star
id|__scsi_device_lookup_by_target
c_func
(paren
r_struct
id|scsi_target
op_star
comma
id|uint
)paren
suffix:semicolon
r_extern
r_void
id|starget_for_each_device
c_func
(paren
r_struct
id|scsi_target
op_star
comma
r_void
op_star
comma
r_void
(paren
op_star
id|fn
)paren
(paren
r_struct
id|scsi_device
op_star
comma
r_void
op_star
)paren
)paren
suffix:semicolon
multiline_comment|/* only exposed to implement shost_for_each_device */
r_extern
r_struct
id|scsi_device
op_star
id|__scsi_iterate_devices
c_func
(paren
r_struct
id|Scsi_Host
op_star
comma
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
multiline_comment|/**&n; * shost_for_each_device  -  iterate over all devices of a host&n; * @sdev:&t;iterator&n; * @host:&t;host whiches devices we want to iterate over&n; *&n; * This traverses over each devices of @shost.  The devices have&n; * a reference that must be released by scsi_host_put when breaking&n; * out of the loop.&n; */
DECL|macro|shost_for_each_device
mdefine_line|#define shost_for_each_device(sdev, shost) &bslash;&n;&t;for ((sdev) = __scsi_iterate_devices((shost), NULL); &bslash;&n;&t;     (sdev); &bslash;&n;&t;     (sdev) = __scsi_iterate_devices((shost), (sdev)))
multiline_comment|/**&n; * __shost_for_each_device  -  iterate over all devices of a host (UNLOCKED)&n; * @sdev:&t;iterator&n; * @host:&t;host whiches devices we want to iterate over&n; *&n; * This traverses over each devices of @shost.  It does _not_ take a&n; * reference on the scsi_device, thus it the whole loop must be protected&n; * by shost-&gt;host_lock.&n; *&n; * Note:  The only reason why drivers would want to use this is because&n; * they&squot;re need to access the device list in irq context.  Otherwise you&n; * really want to use shost_for_each_device instead.&n; */
DECL|macro|__shost_for_each_device
mdefine_line|#define __shost_for_each_device(sdev, shost) &bslash;&n;&t;list_for_each_entry((sdev), &amp;((shost)-&gt;__devices), siblings)
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
r_extern
r_int
id|scsi_test_unit_ready
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_int
id|timeout
comma
r_int
id|retries
)paren
suffix:semicolon
r_extern
r_int
id|scsi_device_set_state
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_enum
id|scsi_device_state
id|state
)paren
suffix:semicolon
r_extern
r_int
id|scsi_device_quiesce
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
suffix:semicolon
r_extern
r_void
id|scsi_device_resume
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
suffix:semicolon
r_extern
r_void
id|scsi_target_quiesce
c_func
(paren
r_struct
id|scsi_target
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_target_resume
c_func
(paren
r_struct
id|scsi_target
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_scan_target
c_func
(paren
r_struct
id|device
op_star
id|parent
comma
r_int
r_int
id|channel
comma
r_int
r_int
id|id
comma
r_int
r_int
id|lun
comma
r_int
id|rescan
)paren
suffix:semicolon
r_extern
r_void
id|scsi_target_reap
c_func
(paren
r_struct
id|scsi_target
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_target_block
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_target_unblock
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_remove_target
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|scsi_device_state_name
c_func
(paren
r_enum
id|scsi_device_state
)paren
suffix:semicolon
r_extern
r_int
id|scsi_is_sdev_device
c_func
(paren
r_const
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_is_target_device
c_func
(paren
r_const
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|function|scsi_device_online
r_static
r_inline
r_int
id|scsi_device_online
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
r_return
id|sdev-&gt;sdev_state
op_ne
id|SDEV_OFFLINE
suffix:semicolon
)brace
multiline_comment|/* accessor functions for the SCSI parameters */
DECL|function|scsi_device_sync
r_static
r_inline
r_int
id|scsi_device_sync
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
r_return
id|sdev-&gt;sdtr
suffix:semicolon
)brace
DECL|function|scsi_device_wide
r_static
r_inline
r_int
id|scsi_device_wide
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
r_return
id|sdev-&gt;wdtr
suffix:semicolon
)brace
DECL|function|scsi_device_dt
r_static
r_inline
r_int
id|scsi_device_dt
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
r_return
id|sdev-&gt;ppr
suffix:semicolon
)brace
DECL|function|scsi_device_dt_only
r_static
r_inline
r_int
id|scsi_device_dt_only
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
r_if
c_cond
(paren
id|sdev-&gt;inquiry_len
OL
l_int|57
)paren
r_return
l_int|0
suffix:semicolon
r_return
(paren
id|sdev-&gt;inquiry
(braket
l_int|56
)braket
op_amp
l_int|0x0c
)paren
op_eq
l_int|0x04
suffix:semicolon
)brace
DECL|function|scsi_device_ius
r_static
r_inline
r_int
id|scsi_device_ius
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
r_if
c_cond
(paren
id|sdev-&gt;inquiry_len
OL
l_int|57
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|sdev-&gt;inquiry
(braket
l_int|56
)braket
op_amp
l_int|0x01
suffix:semicolon
)brace
DECL|function|scsi_device_qas
r_static
r_inline
r_int
id|scsi_device_qas
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
r_if
c_cond
(paren
id|sdev-&gt;inquiry_len
OL
l_int|57
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|sdev-&gt;inquiry
(braket
l_int|56
)braket
op_amp
l_int|0x02
suffix:semicolon
)brace
macro_line|#endif /* _SCSI_SCSI_DEVICE_H */
eof
