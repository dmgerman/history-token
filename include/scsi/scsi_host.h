macro_line|#ifndef _SCSI_SCSI_HOST_H
DECL|macro|_SCSI_SCSI_HOST_H
mdefine_line|#define _SCSI_SCSI_HOST_H
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/types.h&gt;
r_struct
id|block_device
suffix:semicolon
r_struct
id|module
suffix:semicolon
r_struct
id|scsi_cmnd
suffix:semicolon
r_struct
id|scsi_device
suffix:semicolon
r_struct
id|Scsi_Host
suffix:semicolon
r_struct
id|scsi_host_cmd_pool
suffix:semicolon
multiline_comment|/*&n; * The various choices mean:&n; * NONE: Self evident.&t;Host adapter is not capable of scatter-gather.&n; * ALL:&t; Means that the host adapter module can do scatter-gather,&n; *&t; and that there is no limit to the size of the table to which&n; *&t; we scatter/gather data.&n; * Anything else:  Indicates the maximum number of chains that can be&n; *&t; used in one scatter-gather request.&n; */
DECL|macro|SG_NONE
mdefine_line|#define SG_NONE 0
DECL|macro|SG_ALL
mdefine_line|#define SG_ALL 0xff
DECL|macro|DISABLE_CLUSTERING
mdefine_line|#define DISABLE_CLUSTERING 0
DECL|macro|ENABLE_CLUSTERING
mdefine_line|#define ENABLE_CLUSTERING 1
DECL|struct|scsi_host_template
r_struct
id|scsi_host_template
(brace
DECL|member|module
r_struct
id|module
op_star
id|module
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/*&n;&t; * Used to initialize old-style drivers.  For new-style drivers&n;&t; * just perform all work in your module initialization function.&n;&t; *&n;&t; * Status:  OBSOLETE&n;&t; */
DECL|member|detect
r_int
(paren
op_star
id|detect
)paren
(paren
r_struct
id|scsi_host_template
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Used as unload callback for hosts with old-style drivers.&n;&t; *&n;&t; * Status: OBSOLETE&n;&t; */
DECL|member|release
r_int
(paren
op_star
id|release
)paren
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The info function will return whatever useful information the&n;&t; * developer sees fit.  If not provided, then the name field will&n;&t; * be used instead.&n;&t; *&n;&t; * Status: OPTIONAL&n;&t; */
DECL|member|info
r_const
r_char
op_star
(paren
op_star
id|info
)paren
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Ioctl interface&n;&t; *&n;&t; * Status: OPTIONAL&n;&t; */
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|scsi_device
op_star
id|dev
comma
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The queuecommand function is used to queue up a scsi&n;&t; * command block to the LLDD.  When the driver finished&n;&t; * processing the command the done callback is invoked.&n;&t; *&n;&t; * If queuecommand returns 0, then the HBA has accepted the&n;&t; * command.  The done() function must be called on the command&n;&t; * when the driver has finished with it. (you may call done on the&n;&t; * command before queuecommand returns, but in this case you&n;&t; * *must* return 0 from queuecommand).&n;&t; *&n;&t; * Queuecommand may also reject the command, in which case it may&n;&t; * not touch the command and must not call done() for it.&n;&t; *&n;&t; * There are two possible rejection returns:&n;&t; *&n;&t; *   SCSI_MLQUEUE_DEVICE_BUSY: Block this device temporarily, but&n;&t; *   allow commands to other devices serviced by this host.&n;&t; *&n;&t; *   SCSI_MLQUEUE_HOST_BUSY: Block all devices served by this&n;&t; *   host temporarily.&n;&t; *&n;         * For compatibility, any other non-zero return is treated the&n;         * same as SCSI_MLQUEUE_HOST_BUSY.&n;&t; *&n;&t; * NOTE: &quot;temporarily&quot; means either until the next command for#&n;&t; * this device/host completes, or a period of time determined by&n;&t; * I/O pressure in the system if there are no other outstanding&n;&t; * commands.&n;&t; *&n;&t; * STATUS: REQUIRED&n;&t; */
DECL|member|queuecommand
r_int
(paren
op_star
id|queuecommand
)paren
(paren
r_struct
id|scsi_cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This is an error handling strategy routine.  You don&squot;t need to&n;&t; * define one of these if you don&squot;t want to - there is a default&n;&t; * routine that is present that should work in most cases.  For those&n;&t; * driver authors that have the inclination and ability to write their&n;&t; * own strategy routine, this is where it is specified.  Note - the&n;&t; * strategy routine is *ALWAYS* run in the context of the kernel eh&n;&t; * thread.  Thus you are guaranteed to *NOT* be in an interrupt&n;&t; * handler when you execute this, and you are also guaranteed to&n;&t; * *NOT* have any other commands being queued while you are in the&n;&t; * strategy routine. When you return from this function, operations&n;&t; * return to normal.&n;&t; *&n;&t; * See scsi_error.c scsi_unjam_host for additional comments about&n;&t; * what this function should and should not be attempting to do.&n;&t; *&n;&t; * Status: REQUIRED&t;(at least one of them)&n;&t; */
DECL|member|eh_strategy_handler
r_int
(paren
op_star
id|eh_strategy_handler
)paren
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
DECL|member|eh_abort_handler
r_int
(paren
op_star
id|eh_abort_handler
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
DECL|member|eh_device_reset_handler
r_int
(paren
op_star
id|eh_device_reset_handler
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
DECL|member|eh_bus_reset_handler
r_int
(paren
op_star
id|eh_bus_reset_handler
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
DECL|member|eh_host_reset_handler
r_int
(paren
op_star
id|eh_host_reset_handler
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Old EH handlers, no longer used. Make them warn the user of old&n;&t; * drivers by using a wrong type&n;&t; *&n;&t; * Status: MORE THAN OBSOLETE&n;&t; */
DECL|member|abort
r_int
(paren
op_star
m_abort
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|reset
r_int
(paren
op_star
id|reset
)paren
(paren
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Before the mid layer attempts to scan for a new device where none&n;&t; * currently exists, it will call this entry in your driver.  Should&n;&t; * your driver need to allocate any structs or perform any other init&n;&t; * items in order to send commands to a currently unused target/lun&n;&t; * combo, then this is where you can perform those allocations.  This&n;&t; * is specifically so that drivers won&squot;t have to perform any kind of&n;&t; * &quot;is this a new device&quot; checks in their queuecommand routine,&n;&t; * thereby making the hot path a bit quicker.&n;&t; *&n;&t; * Return values: 0 on success, non-0 on failure&n;&t; *&n;&t; * Deallocation:  If we didn&squot;t find any devices at this ID, you will&n;&t; * get an immediate call to slave_destroy().  If we find something&n;&t; * here then you will get a call to slave_configure(), then the&n;&t; * device will be used for however long it is kept around, then when&n;&t; * the device is removed from the system (or * possibly at reboot&n;&t; * time), you will then get a call to slave_detach().  This is&n;&t; * assuming you implement slave_configure and slave_destroy.&n;&t; * However, if you allocate memory and hang it off the device struct,&n;&t; * then you must implement the slave_destroy() routine at a minimum&n;&t; * in order to avoid leaking memory&n;&t; * each time a device is tore down.&n;&t; *&n;&t; * Status: OPTIONAL&n;&t; */
DECL|member|slave_alloc
r_int
(paren
op_star
id|slave_alloc
)paren
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Once the device has responded to an INQUIRY and we know the&n;&t; * device is online, we call into the low level driver with the&n;&t; * struct scsi_device *.  If the low level device driver implements&n;&t; * this function, it *must* perform the task of setting the queue&n;&t; * depth on the device.  All other tasks are optional and depend&n;&t; * on what the driver supports and various implementation details.&n;&t; * &n;&t; * Things currently recommended to be handled at this time include:&n;&t; *&n;&t; * 1.  Setting the device queue depth.  Proper setting of this is&n;&t; *     described in the comments for scsi_adjust_queue_depth.&n;&t; * 2.  Determining if the device supports the various synchronous&n;&t; *     negotiation protocols.  The device struct will already have&n;&t; *     responded to INQUIRY and the results of the standard items&n;&t; *     will have been shoved into the various device flag bits, eg.&n;&t; *     device-&gt;sdtr will be true if the device supports SDTR messages.&n;&t; * 3.  Allocating command structs that the device will need.&n;&t; * 4.  Setting the default timeout on this device (if needed).&n;&t; * 5.  Anything else the low level driver might want to do on a device&n;&t; *     specific setup basis...&n;&t; * 6.  Return 0 on success, non-0 on error.  The device will be marked&n;&t; *     as offline on error so that no access will occur.  If you return&n;&t; *     non-0, your slave_detach routine will never get called for this&n;&t; *     device, so don&squot;t leave any loose memory hanging around, clean&n;&t; *     up after yourself before returning non-0&n;&t; *&n;&t; * Status: OPTIONAL&n;&t; */
DECL|member|slave_configure
r_int
(paren
op_star
id|slave_configure
)paren
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Immediately prior to deallocating the device and after all activity&n;&t; * has ceased the mid layer calls this point so that the low level&n;&t; * driver may completely detach itself from the scsi device and vice&n;&t; * versa.  The low level driver is responsible for freeing any memory&n;&t; * it allocated in the slave_alloc or slave_configure calls. &n;&t; *&n;&t; * Status: OPTIONAL&n;&t; */
DECL|member|slave_destroy
r_void
(paren
op_star
id|slave_destroy
)paren
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This function determines the bios parameters for a given&n;&t; * harddisk.  These tend to be numbers that are made up by&n;&t; * the host adapter.  Parameters:&n;&t; * size, device, list (heads, sectors, cylinders)&n;&t; *&n;&t; * Status: OPTIONAL&n;&t; */
DECL|member|bios_param
r_int
(paren
op_star
id|bios_param
)paren
(paren
r_struct
id|scsi_device
op_star
comma
r_struct
id|block_device
op_star
comma
id|sector_t
comma
r_int
(braket
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Can be used to export driver statistics and other infos to the&n;&t; * world outside the kernel ie. userspace and it also provides an&n;&t; * interface to feed the driver with information.&n;&t; *&n;&t; * Status: OBSOLETE&n;&t; */
DECL|member|proc_info
r_int
(paren
op_star
id|proc_info
)paren
(paren
r_struct
id|Scsi_Host
op_star
comma
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Name of proc directory&n;&t; */
DECL|member|proc_name
r_char
op_star
id|proc_name
suffix:semicolon
multiline_comment|/*&n;&t; * Used to store the procfs directory if a driver implements the&n;&t; * proc_info method.&n;&t; */
DECL|member|proc_dir
r_struct
id|proc_dir_entry
op_star
id|proc_dir
suffix:semicolon
multiline_comment|/*&n;&t; * This determines if we will use a non-interrupt driven&n;&t; * or an interrupt driven scheme,  It is set to the maximum number&n;&t; * of simultaneous commands a given host adapter will accept.&n;&t; */
DECL|member|can_queue
r_int
id|can_queue
suffix:semicolon
multiline_comment|/*&n;&t; * In many instances, especially where disconnect / reconnect are&n;&t; * supported, our host also has an ID on the SCSI bus.  If this is&n;&t; * the case, then it must be reserved.  Please set this_id to -1 if&n;&t; * your setup is in single initiator mode, and the host lacks an&n;&t; * ID.&n;&t; */
DECL|member|this_id
r_int
id|this_id
suffix:semicolon
multiline_comment|/*&n;&t; * This determines the degree to which the host adapter is capable&n;&t; * of scatter-gather.&n;&t; */
DECL|member|sg_tablesize
r_int
r_int
id|sg_tablesize
suffix:semicolon
multiline_comment|/*&n;&t; * If the host adapter has limitations beside segment count&n;&t; */
DECL|member|max_sectors
r_int
r_int
id|max_sectors
suffix:semicolon
multiline_comment|/*&n;&t; * This specifies &quot;machine infinity&quot; for host templates which don&squot;t&n;&t; * limit the transfer size.  Note this limit represents an absolute&n;&t; * maximum, and may be over the transfer limits allowed for&n;&t; * individual devices (e.g. 256 for SCSI-1)&n;&t; */
DECL|macro|SCSI_DEFAULT_MAX_SECTORS
mdefine_line|#define SCSI_DEFAULT_MAX_SECTORS&t;1024
multiline_comment|/*&n;&t; * True if this host adapter can make good use of linked commands.&n;&t; * This will allow more than one command to be queued to a given&n;&t; * unit on a given host.  Set this to the maximum number of command&n;&t; * blocks to be provided for each device.  Set this to 1 for one&n;&t; * command block per lun, 2 for two, etc.  Do not set this to 0.&n;&t; * You should make sure that the host adapter will do the right thing&n;&t; * before you try setting this above 1.&n;&t; */
DECL|member|cmd_per_lun
r_int
id|cmd_per_lun
suffix:semicolon
multiline_comment|/*&n;&t; * present contains counter indicating how many boards of this&n;&t; * type were found when we did the scan.&n;&t; */
DECL|member|present
r_int
r_char
id|present
suffix:semicolon
multiline_comment|/*&n;&t; * true if this host adapter uses unchecked DMA onto an ISA bus.&n;&t; */
DECL|member|unchecked_isa_dma
r_int
id|unchecked_isa_dma
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * true if this host adapter can make good use of clustering.&n;&t; * I originally thought that if the tablesize was large that it&n;&t; * was a waste of CPU cycles to prepare a cluster list, but&n;&t; * it works out that the Buslogic is faster if you use a smaller&n;&t; * number of segments (i.e. use clustering).  I guess it is&n;&t; * inefficient.&n;&t; */
DECL|member|use_clustering
r_int
id|use_clustering
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * True for emulated SCSI host adapters (e.g. ATAPI)&n;&t; */
DECL|member|emulated
r_int
id|emulated
suffix:colon
l_int|1
suffix:semicolon
DECL|member|highmem_io
r_int
id|highmem_io
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* &n;&t; * True if the driver wishes to use the generic block layer&n;&t; * tag queueing functions&n;&t; */
DECL|member|use_blk_tcq
r_int
id|use_blk_tcq
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Countdown for host blocking with no commands outstanding&n;&t; */
DECL|member|max_host_blocked
r_int
r_int
id|max_host_blocked
suffix:semicolon
multiline_comment|/*&n;&t; * Default value for the blocking.  If the queue is empty,&n;&t; * host_blocked counts down in the request_fn until it restarts&n;&t; * host operations as zero is reached.  &n;&t; *&n;&t; * FIXME: This should probably be a value in the template&n;&t; */
DECL|macro|SCSI_DEFAULT_HOST_BLOCKED
mdefine_line|#define SCSI_DEFAULT_HOST_BLOCKED&t;7
multiline_comment|/*&n;&t; * Pointer to the sysfs class properties for this host, NULL terminated.&n;&t; */
DECL|member|shost_attrs
r_struct
id|class_device_attribute
op_star
op_star
id|shost_attrs
suffix:semicolon
multiline_comment|/*&n;&t; * Pointer to the SCSI device properties for this host, NULL terminated.&n;&t; */
DECL|member|sdev_attrs
r_struct
id|device_attribute
op_star
op_star
id|sdev_attrs
suffix:semicolon
multiline_comment|/*&n;&t; * List of hosts per template.&n;&t; *&n;&t; * This is only for use by scsi_module.c for legacy templates.&n;&t; * For these access to it is synchronized implicitly by&n;&t; * module_init/module_exit.&n;&t; */
DECL|member|legacy_hosts
r_struct
id|list_head
id|legacy_hosts
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * shost states&n; */
r_enum
(brace
DECL|enumerator|SHOST_ADD
id|SHOST_ADD
comma
DECL|enumerator|SHOST_DEL
id|SHOST_DEL
comma
DECL|enumerator|SHOST_CANCEL
id|SHOST_CANCEL
comma
DECL|enumerator|SHOST_RECOVERY
id|SHOST_RECOVERY
comma
)brace
suffix:semicolon
DECL|struct|Scsi_Host
r_struct
id|Scsi_Host
(brace
DECL|member|my_devices
r_struct
id|list_head
id|my_devices
suffix:semicolon
DECL|member|cmd_pool
r_struct
id|scsi_host_cmd_pool
op_star
id|cmd_pool
suffix:semicolon
DECL|member|free_list_lock
id|spinlock_t
id|free_list_lock
suffix:semicolon
DECL|member|free_list
r_struct
id|list_head
id|free_list
suffix:semicolon
multiline_comment|/* backup store of cmd structs */
DECL|member|starved_list
r_struct
id|list_head
id|starved_list
suffix:semicolon
DECL|member|default_lock
id|spinlock_t
id|default_lock
suffix:semicolon
DECL|member|host_lock
id|spinlock_t
op_star
id|host_lock
suffix:semicolon
DECL|member|eh_cmd_q
r_struct
id|list_head
id|eh_cmd_q
suffix:semicolon
DECL|member|ehandler
r_struct
id|task_struct
op_star
id|ehandler
suffix:semicolon
multiline_comment|/* Error recovery thread. */
DECL|member|eh_wait
r_struct
id|semaphore
op_star
id|eh_wait
suffix:semicolon
multiline_comment|/* The error recovery thread waits on&n;                                          this. */
DECL|member|eh_notify
r_struct
id|completion
op_star
id|eh_notify
suffix:semicolon
multiline_comment|/* wait for eh to begin or end */
DECL|member|eh_action
r_struct
id|semaphore
op_star
id|eh_action
suffix:semicolon
multiline_comment|/* Wait for specific actions on the&n;                                          host. */
DECL|member|eh_active
r_int
r_int
id|eh_active
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Indicates the eh thread is awake and active if&n;                                          this is true. */
DECL|member|eh_kill
r_int
r_int
id|eh_kill
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set when killing the eh thread */
DECL|member|host_wait
id|wait_queue_head_t
id|host_wait
suffix:semicolon
DECL|member|hostt
r_struct
id|scsi_host_template
op_star
id|hostt
suffix:semicolon
DECL|member|host_busy
r_volatile
r_int
r_int
id|host_busy
suffix:semicolon
multiline_comment|/* commands actually active on low-level */
DECL|member|host_failed
r_volatile
r_int
r_int
id|host_failed
suffix:semicolon
multiline_comment|/* commands that failed. */
DECL|member|host_no
r_int
r_int
id|host_no
suffix:semicolon
multiline_comment|/* Used for IOCTL_GET_IDLUN, /proc/scsi et al. */
DECL|member|resetting
r_int
id|resetting
suffix:semicolon
multiline_comment|/* if set, it means that last_reset is a valid value */
DECL|member|last_reset
r_int
r_int
id|last_reset
suffix:semicolon
multiline_comment|/*&n;&t; * These three parameters can be used to allow for wide scsi,&n;&t; * and for host adapters that support multiple busses&n;&t; * The first two should be set to 1 more than the actual max id&n;&t; * or lun (i.e. 8 for normal systems).&n;&t; */
DECL|member|max_id
r_int
r_int
id|max_id
suffix:semicolon
DECL|member|max_lun
r_int
r_int
id|max_lun
suffix:semicolon
DECL|member|max_channel
r_int
r_int
id|max_channel
suffix:semicolon
multiline_comment|/*&n;&t; * This is a unique identifier that must be assigned so that we&n;&t; * have some way of identifying each detected host adapter properly&n;&t; * and uniquely.  For hosts that do not support more than one card&n;&t; * in the system at one time, this does not need to be set.  It is&n;&t; * initialized to 0 in scsi_register.&n;&t; */
DECL|member|unique_id
r_int
r_int
id|unique_id
suffix:semicolon
multiline_comment|/*&n;&t; * The maximum length of SCSI commands that this host can accept.&n;&t; * Probably 12 for most host adapters, but could be 16 for others.&n;&t; * For drivers that don&squot;t set this field, a value of 12 is&n;&t; * assumed.  I am leaving this as a number rather than a bit&n;&t; * because you never know what subsequent SCSI standards might do&n;&t; * (i.e. could there be a 20 byte or a 24-byte command a few years&n;&t; * down the road?).  &n;&t; */
DECL|member|max_cmd_len
r_int
r_char
id|max_cmd_len
suffix:semicolon
DECL|member|this_id
r_int
id|this_id
suffix:semicolon
DECL|member|can_queue
r_int
id|can_queue
suffix:semicolon
DECL|member|cmd_per_lun
r_int
id|cmd_per_lun
suffix:semicolon
DECL|member|sg_tablesize
r_int
r_int
r_int
id|sg_tablesize
suffix:semicolon
DECL|member|max_sectors
r_int
r_int
r_int
id|max_sectors
suffix:semicolon
DECL|member|unchecked_isa_dma
r_int
id|unchecked_isa_dma
suffix:colon
l_int|1
suffix:semicolon
DECL|member|use_clustering
r_int
id|use_clustering
suffix:colon
l_int|1
suffix:semicolon
DECL|member|highmem_io
r_int
id|highmem_io
suffix:colon
l_int|1
suffix:semicolon
DECL|member|use_blk_tcq
r_int
id|use_blk_tcq
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Host has requested that no further requests come through for the&n;&t; * time being.&n;&t; */
DECL|member|host_self_blocked
r_int
id|host_self_blocked
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Host uses correct SCSI ordering not PC ordering. The bit is&n;&t; * set for the minority of drivers whose authors actually read&n;&t; * the spec ;)&n;&t; */
DECL|member|reverse_ordering
r_int
id|reverse_ordering
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Host has rejected a command because it was busy.&n;&t; */
DECL|member|host_blocked
r_int
r_int
id|host_blocked
suffix:semicolon
multiline_comment|/*&n;&t; * Value host_blocked counts down from&n;&t; */
DECL|member|max_host_blocked
r_int
r_int
id|max_host_blocked
suffix:semicolon
multiline_comment|/* legacy crap */
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
DECL|member|io_port
r_int
r_int
id|io_port
suffix:semicolon
DECL|member|n_io_port
r_int
r_char
id|n_io_port
suffix:semicolon
DECL|member|dma_channel
r_int
r_char
id|dma_channel
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|shost_state
r_int
r_int
id|shost_state
suffix:semicolon
multiline_comment|/* ldm bits */
DECL|member|shost_gendev
r_struct
id|device
id|shost_gendev
suffix:semicolon
DECL|member|shost_classdev
r_struct
id|class_device
id|shost_classdev
suffix:semicolon
multiline_comment|/*&n;&t; * List of hosts per template.&n;&t; *&n;&t; * This is only for use by scsi_module.c for legacy templates.&n;&t; * For these access to it is synchronized implicitly by&n;&t; * module_init/module_exit.&n;&t; */
DECL|member|sht_legacy_list
r_struct
id|list_head
id|sht_legacy_list
suffix:semicolon
multiline_comment|/*&n;&t; * We should ensure that this is aligned, both for better performance&n;&t; * and also because some compilers (m68k) don&squot;t automatically force&n;&t; * alignment to a long boundary.&n;&t; */
DECL|member|hostdata
r_int
r_int
id|hostdata
(braket
l_int|0
)braket
multiline_comment|/* Used for storage of host specific stuff */
id|__attribute__
(paren
(paren
id|aligned
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
)brace
suffix:semicolon
DECL|macro|dev_to_shost
mdefine_line|#define&t;&t;dev_to_shost(d)&t;&t;&bslash;&n;&t;container_of(d, struct Scsi_Host, shost_gendev)
DECL|macro|class_to_shost
mdefine_line|#define&t;&t;class_to_shost(d)&t;&bslash;&n;&t;container_of(d, struct Scsi_Host, shost_classdev)
r_extern
r_struct
id|Scsi_Host
op_star
id|scsi_host_alloc
c_func
(paren
r_struct
id|scsi_host_template
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|scsi_add_host
c_func
(paren
r_struct
id|Scsi_Host
op_star
comma
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_scan_host
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_remove_host
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|Scsi_Host
op_star
id|scsi_host_get
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_host_put
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|t
)paren
suffix:semicolon
r_extern
r_struct
id|Scsi_Host
op_star
id|scsi_host_lookup
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
id|u64
id|scsi_calculate_bounce_limit
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
DECL|function|scsi_assign_lock
r_static
r_inline
r_void
id|scsi_assign_lock
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
comma
id|spinlock_t
op_star
id|lock
)paren
(brace
id|shost-&gt;host_lock
op_assign
id|lock
suffix:semicolon
)brace
DECL|function|scsi_set_device
r_static
r_inline
r_void
id|scsi_set_device
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
id|shost-&gt;shost_gendev.parent
op_assign
id|dev
suffix:semicolon
)brace
DECL|function|scsi_get_device
r_static
r_inline
r_struct
id|device
op_star
id|scsi_get_device
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
r_return
id|shost-&gt;shost_gendev.parent
suffix:semicolon
)brace
r_extern
r_void
id|scsi_unblock_requests
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_block_requests
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * These two functions are used to allocate and free a pseudo device&n; * which will connect to the host adapter itself rather than any&n; * physical device.  You must deallocate when you are done with the&n; * thing.  This physical pseudo-device isn&squot;t real and won&squot;t be available&n; * from any high-level drivers.&n; */
r_extern
r_void
id|scsi_free_host_dev
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
id|scsi_get_host_dev
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
multiline_comment|/* legacy interfaces */
r_extern
r_struct
id|Scsi_Host
op_star
id|scsi_register
c_func
(paren
r_struct
id|scsi_host_template
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|scsi_unregister
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
macro_line|#endif /* _SCSI_SCSI_HOST_H */
eof
