multiline_comment|/*&n; *  hosts.h Copyright (C) 1992 Drew Eckhardt&n; *          Copyright (C) 1993, 1994, 1995, 1998, 1999 Eric Youngdale&n; *&n; *  mid to low-level SCSI driver interface header&n; *      Initial versions: Drew Eckhardt&n; *      Subsequent revisions: Eric Youngdale&n; *&n; *  &lt;drew@colorado.edu&gt;&n; *&n; *&t; Modified by Eric Youngdale eric@andante.org to&n; *&t; add scatter-gather, multiple outstanding request, and other&n; *&t; enhancements.&n; *&n; *  Further modified by Eric Youngdale to support multiple host adapters&n; *  of the same type.&n; *&n; *  Jiffies wrap fixes (host-&gt;resetting), 3 Dec 1998 Andrea Arcangeli&n; *&n; *  Restructured scsi_host lists and associated functions.&n; *  September 04, 2002 Mike Anderson (andmike@us.ibm.com)&n; */
macro_line|#ifndef _HOSTS_H
DECL|macro|_HOSTS_H
mdefine_line|#define _HOSTS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
multiline_comment|/* It is senseless to set SG_ALL any higher than this - the performance&n; *  does not get any better, and it wastes memory&n; */
DECL|macro|SG_NONE
mdefine_line|#define SG_NONE 0
DECL|macro|SG_ALL
mdefine_line|#define SG_ALL 0xff
DECL|macro|DISABLE_CLUSTERING
mdefine_line|#define DISABLE_CLUSTERING 0
DECL|macro|ENABLE_CLUSTERING
mdefine_line|#define ENABLE_CLUSTERING 1
multiline_comment|/* The various choices mean:&n; * NONE: Self evident.&t;Host adapter is not capable of scatter-gather.&n; * ALL:&t; Means that the host adapter module can do scatter-gather,&n; *&t; and that there is no limit to the size of the table to which&n; *&t; we scatter/gather data.&n; * Anything else:  Indicates the maximum number of chains that can be&n; *&t; used in one scatter-gather request.&n; */
multiline_comment|/*&n; * The Scsi_Host_Template type has all that is needed to interface with a SCSI&n; * host in a device independent matter.&t; There is one entry for each different&n; * type of host adapter that is supported on the system.&n; */
DECL|typedef|Disk
r_typedef
r_struct
id|scsi_disk
id|Disk
suffix:semicolon
DECL|struct|SHT
r_typedef
r_struct
id|SHT
(brace
multiline_comment|/* Used with loadable modules so that we know when it is safe to unload */
DECL|member|module
r_struct
id|module
op_star
id|module
suffix:semicolon
multiline_comment|/* The pointer to the /proc/scsi directory entry */
DECL|member|proc_dir
r_struct
id|proc_dir_entry
op_star
id|proc_dir
suffix:semicolon
multiline_comment|/* proc-fs info function.&n;     * Can be used to export driver statistics and other infos to the world&n;     * outside the kernel ie. userspace and it also provides an interface&n;     * to feed the driver with information. Check eata_dma_proc.c for reference&n;     */
DECL|member|proc_info
r_int
(paren
op_star
id|proc_info
)paren
(paren
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
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n;     * The name pointer is a pointer to the name of the SCSI&n;     * device detected.&n;     */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/*&n;     * The detect function shall return non zero on detection,&n;     * indicating the number of host adapters of this particular&n;     * type were found.&t; It should also&n;     * initialize all data necessary for this particular&n;     * SCSI driver.  It is passed the host number, so this host&n;     * knows where the first entry is in the scsi_hosts[] array.&n;     *&n;     * Note that the detect routine MUST not call any of the mid level&n;     * functions to queue commands because things are not guaranteed&n;     * to be set up yet.  The detect routine can send commands to&n;     * the host adapter as long as the program control will not be&n;     * passed to scsi.c in the processing of the command.  Note&n;     * especially that scsi_malloc/scsi_free must not be called.&n;     */
DECL|member|detect
r_int
(paren
op_star
id|detect
)paren
(paren
r_struct
id|SHT
op_star
)paren
suffix:semicolon
multiline_comment|/* Used with loadable modules to unload the host structures.  Note:&n;     * there is a default action built into the modules code which may&n;     * be sufficient for most host adapters.  Thus you may not have to supply&n;     * this at all.&n;     */
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
multiline_comment|/*&n;     * The info function will return whatever useful&n;     * information the developer sees fit.  If not provided, then&n;     * the name field will be used instead.&n;     */
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
multiline_comment|/*&n;     * ioctl interface&n;     */
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
id|Scsi_Device
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
multiline_comment|/*&n;     * The command function takes a target, a command (this is a SCSI&n;     * command formatted as per the SCSI spec, nothing strange), a&n;     * data buffer pointer, and data buffer length pointer.  The return&n;     * is a status int, bit fielded as follows :&n;     * Byte What&n;     * 0    SCSI status code&n;     * 1    SCSI 1 byte message&n;     * 2    host error return.&n;     * 3    mid level error return&n;     */
DECL|member|command
r_int
(paren
op_star
id|command
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;     * The QueueCommand function works in a similar manner&n;     * to the command function.&t; It takes an additional parameter,&n;     * void (* done)(int host, int code) which is passed the host&n;     * # and exit result when the command is complete.&n;     * Host number is the POSITION IN THE hosts array of THIS&n;     * host adapter.&n;     *&n;     * if queuecommand returns 0, then the HBA has accepted the&n;     * command.  The done() function must be called on the command&n;     * when the driver has finished with it. (you may call done on the&n;     * command before queuecommand returns, but in this case you&n;     * *must* return 0 from queuecommand).&n;     *&n;     * queuecommand may also reject the command, in which case it may&n;     * not touch the command and must not call done() for it.&n;     *&n;     * There are two possible rejection returns:&n;     *&n;     *   SCSI_MLQUEUE_DEVICE_BUSY: Block this device temporarily, but&n;     *   allow commands to other devices serviced by this host.&n;     *&n;     *   SCSI_MLQUEUE_HOST_BUSY: Block all devices served by this&n;     *   host temporarily.&n;     *&n;     *   for compatibility, any other non-zero return is treated the&n;     *   same as SCSI_MLQUEUE_HOST_BUSY.&n;     *&n;     *   NOTE: &quot;temporarily&quot; means either until the next command for&n;     *   this device/host completes, or a period of time determined by&n;     *   I/O pressure in the system if there are no other outstanding&n;     *   commands.&n;     * */
DECL|member|queuecommand
r_int
(paren
op_star
id|queuecommand
)paren
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     * This is an error handling strategy routine.  You don&squot;t need to&n;     * define one of these if you don&squot;t want to - there is a default&n;     * routine that is present that should work in most cases.  For those&n;     * driver authors that have the inclination and ability to write their&n;     * own strategy routine, this is where it is specified.  Note - the&n;     * strategy routine is *ALWAYS* run in the context of the kernel eh&n;     * thread.  Thus you are guaranteed to *NOT* be in an interrupt handler&n;     * when you execute this, and you are also guaranteed to *NOT* have any&n;     * other commands being queued while you are in the strategy routine.&n;     * When you return from this function, operations return to normal.&n;     *&n;     * See scsi_error.c scsi_unjam_host for additional comments about what&n;     * this function should and should not be attempting to do.&n;     */
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
id|Scsi_Cmnd
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
id|Scsi_Cmnd
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
id|Scsi_Cmnd
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
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;     * Old EH handlers, no longer used. Make them warn the user of old&n;     * drivers by using a wrong type&n;     */
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
multiline_comment|/*&n;     * Once the device has responded to an INQUIRY and we know the device&n;     * is online, call into the low level driver with the Scsi_Device *&n;     * (so that the low level driver may save it off in a safe location&n;     * for later use in calling scsi_adjust_queue_depth() or possibly&n;     * other scsi_* functions) and char * to the INQUIRY return data buffer.&n;     * This way, low level drivers will no longer have to snoop INQUIRY data&n;     * to see if a drive supports PPR message protocol for Ultra160 speed&n;     * negotiations or other similar items.  Instead it can simply wait until&n;     * the scsi mid layer calls them with the data in hand and then it can&n;     * do it&squot;s checking of INQUIRY data.  This will happen once for each new&n;     * device added on this controller (including once for each lun on&n;     * multi-lun devices, so low level drivers should take care to make&n;     * sure that if they do tagged queueing on a per physical unit basis&n;     * instead of a per logical unit basis that they have the mid layer&n;     * allocate tags accordingly).&n;     *&n;     * Things currently recommended to be handled at this time include:&n;     *&n;     * 1.  Checking for tagged queueing capability and if able then calling&n;     *     scsi_adjust_queue_depth() with the device pointer and the&n;     *     suggested new queue depth.&n;     * 2.  Checking for things such as SCSI level or DT bit in order to&n;     *     determine if PPR message protocols are appropriate on this&n;     *     device (or any other scsi INQUIRY data specific things the&n;     *     driver wants to know in order to properly handle this device).&n;     * 3.  Allocating command structs that the device will need.&n;     * 4.  Setting the default timeout on this device (if needed).&n;     * 5.  Saving the Scsi_Device pointer so that the low level driver&n;     *     will be able to easily call back into scsi_adjust_queue_depth&n;     *     again should it be determined that the queue depth for this&n;     *     device should be lower or higher than it is initially set to.&n;     * 6.  Allocate device data structures as needed that can be attached&n;     *     to the Scsi_Device * via SDpnt-&gt;host_device_ptr&n;     * 7.  Anything else the low level driver might want to do on a device&n;     *     specific setup basis...&n;     * 8.  Return 0 on success, non-0 on error.  The device will be marked&n;     *     as offline on error so that no access will occur.&n;     */
DECL|member|slave_attach
r_int
(paren
op_star
id|slave_attach
)paren
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;     * If we are getting ready to remove a device from the scsi chain then&n;     * we call into the low level driver to let them know.  Once a low&n;     * level driver has been informed that a drive is going away, the low&n;     * level driver *must* remove it&squot;s pointer to the Scsi_Device because&n;     * it is going to be kfree()&squot;ed shortly.  It is no longer safe to call&n;     * any mid layer functions with this Scsi_Device *.  Additionally, the&n;     * mid layer will not make any more calls into the low level driver&squot;s&n;     * queue routine with this device, so it is safe for the device driver&n;     * to deallocate all structs/commands/etc that is has allocated&n;     * specifically for this device at the time of this call.&n;     */
DECL|member|slave_detach
r_void
(paren
op_star
id|slave_detach
)paren
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;     * This function determines the bios parameters for a given&n;     * harddisk.  These tend to be numbers that are made up by&n;     * the host adapter.  Parameters:&n;     * size, device, list (heads, sectors, cylinders)&n;     */
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
multiline_comment|/*&n;     * This determines if we will use a non-interrupt driven&n;     * or an interrupt driven scheme,  It is set to the maximum number&n;     * of simultaneous commands a given host adapter will accept.&n;     */
DECL|member|can_queue
r_int
id|can_queue
suffix:semicolon
multiline_comment|/*&n;     * In many instances, especially where disconnect / reconnect are&n;     * supported, our host also has an ID on the SCSI bus.  If this is&n;     * the case, then it must be reserved.  Please set this_id to -1 if&n;     * your setup is in single initiator mode, and the host lacks an&n;     * ID.&n;     */
DECL|member|this_id
r_int
id|this_id
suffix:semicolon
multiline_comment|/*&n;     * This determines the degree to which the host adapter is capable&n;     * of scatter-gather.&n;     */
DECL|member|sg_tablesize
r_int
r_int
r_int
id|sg_tablesize
suffix:semicolon
multiline_comment|/*&n;     * if the host adapter has limitations beside segment count&n;     */
DECL|member|max_sectors
r_int
r_int
r_int
id|max_sectors
suffix:semicolon
multiline_comment|/*&n;     * True if this host adapter can make good use of linked commands.&n;     * This will allow more than one command to be queued to a given&n;     * unit on a given host.  Set this to the maximum number of command&n;     * blocks to be provided for each device.  Set this to 1 for one&n;     * command block per lun, 2 for two, etc.  Do not set this to 0.&n;     * You should make sure that the host adapter will do the right thing&n;     * before you try setting this above 1.&n;     */
DECL|member|cmd_per_lun
r_int
id|cmd_per_lun
suffix:semicolon
multiline_comment|/*&n;     * present contains counter indicating how many boards of this&n;     * type were found when we did the scan.&n;     */
DECL|member|present
r_int
r_char
id|present
suffix:semicolon
multiline_comment|/*&n;     * true if this host adapter uses unchecked DMA onto an ISA bus.&n;     */
DECL|member|unchecked_isa_dma
r_int
id|unchecked_isa_dma
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*&n;     * true if this host adapter can make good use of clustering.&n;     * I originally thought that if the tablesize was large that it&n;     * was a waste of CPU cycles to prepare a cluster list, but&n;     * it works out that the Buslogic is faster if you use a smaller&n;     * number of segments (i.e. use clustering).  I guess it is&n;     * inefficient.&n;     */
DECL|member|use_clustering
r_int
id|use_clustering
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*&n;     * True for emulated SCSI host adapters (e.g. ATAPI)&n;     */
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
multiline_comment|/* &n;     * True if the driver wishes to use the generic block layer&n;     * tag queueing functions&n;     */
DECL|member|use_blk_tcq
r_int
id|use_blk_tcq
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*&n;     * Name of proc directory&n;     */
DECL|member|proc_name
r_char
op_star
id|proc_name
suffix:semicolon
multiline_comment|/*&n;     * countdown for host blocking with no commands outstanding&n;     */
DECL|member|max_host_blocked
r_int
r_int
id|max_host_blocked
suffix:semicolon
multiline_comment|/*&n;     * Default value for the blocking.  If the queue is empty, host_blocked&n;     * counts down in the request_fn until it restarts host operations as&n;     * zero is reached.  &n;     *&n;     * FIXME: This should probably be a value in the template */
DECL|macro|SCSI_DEFAULT_HOST_BLOCKED
mdefine_line|#define SCSI_DEFAULT_HOST_BLOCKED&t;7
DECL|typedef|Scsi_Host_Template
)brace
id|Scsi_Host_Template
suffix:semicolon
multiline_comment|/*&n; * The scsi_hosts array is the array containing the data for all&n; * possible &lt;supported&gt; scsi hosts.   This is similar to the&n; * Scsi_Host_Template, except that we have one entry for each&n; * actual physical host adapter on the system, stored as a linked&n; * list.  Note that if there are 2 aha1542 boards, then there will&n; * be two Scsi_Host entries, but only 1 Scsi_Host_Template entry.&n; */
DECL|struct|Scsi_Host
r_struct
id|Scsi_Host
(brace
multiline_comment|/* private: */
multiline_comment|/*&n;     * This information is private to the scsi mid-layer.  Wrapping it in a&n;     * struct private is a way of marking it in a sort of C++ type of way.&n;     */
DECL|member|sh_list
r_struct
id|list_head
id|sh_list
suffix:semicolon
DECL|member|host_queue
id|Scsi_Device
op_star
id|host_queue
suffix:semicolon
DECL|member|all_scsi_hosts
r_struct
id|list_head
id|all_scsi_hosts
suffix:semicolon
DECL|member|my_devices
r_struct
id|list_head
id|my_devices
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
id|semaphore
op_star
id|eh_notify
suffix:semicolon
multiline_comment|/* wait for eh to begin */
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
DECL|member|host_wait
id|wait_queue_head_t
id|host_wait
suffix:semicolon
DECL|member|hostt
id|Scsi_Host_Template
op_star
id|hostt
suffix:semicolon
DECL|member|host_active
id|atomic_t
id|host_active
suffix:semicolon
multiline_comment|/* commands checked out */
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
multiline_comment|/* public: */
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
multiline_comment|/*&n;     *&t;These three parameters can be used to allow for wide scsi,&n;     *&t;and for host adapters that support multiple busses&n;     *&t;The first two should be set to 1 more than the actual max id&n;     *&t;or lun (i.e. 8 for normal systems).&n;     */
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
multiline_comment|/* These parameters should be set by the detect routine */
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
multiline_comment|/*&n;     * This is a unique identifier that must be assigned so that we&n;     * have some way of identifying each detected host adapter properly&n;     * and uniquely.  For hosts that do not support more than one card&n;     * in the system at one time, this does not need to be set.  It is&n;     * initialized to 0 in scsi_register.&n;     */
DECL|member|unique_id
r_int
r_int
id|unique_id
suffix:semicolon
multiline_comment|/*&n;     * The rest can be copied from the template, or specifically&n;     * initialized, as required.&n;     */
multiline_comment|/*&n;     * The maximum length of SCSI commands that this host can accept.&n;     * Probably 12 for most host adapters, but could be 16 for others.&n;     * For drivers that don&squot;t set this field, a value of 12 is&n;     * assumed.  I am leaving this as a number rather than a bit&n;     * because you never know what subsequent SCSI standards might do&n;     * (i.e. could there be a 20 byte or a 24-byte command a few years&n;     * down the road?).  &n;     */
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
DECL|member|in_recovery
r_int
id|in_recovery
suffix:colon
l_int|1
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
multiline_comment|/*&n;     * Host has requested that no further requests come through for the&n;     * time being.&n;     */
DECL|member|host_self_blocked
r_int
id|host_self_blocked
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*&n;     * Host uses correct SCSI ordering not PC ordering. The bit is&n;     * set for the minority of drivers whose authors actually read the spec ;)&n;     */
DECL|member|reverse_ordering
r_int
id|reverse_ordering
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*&n;     * Indicates that one or more devices on this host were starved, and&n;     * when the device becomes less busy that we need to feed them.&n;     */
DECL|member|some_device_starved
r_int
id|some_device_starved
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*&n;     * Host has rejected a command because it was busy.&n;     */
DECL|member|host_blocked
r_int
r_int
id|host_blocked
suffix:semicolon
multiline_comment|/*&n;     * Value host_blocked counts down from&n;     */
DECL|member|max_host_blocked
r_int
r_int
id|max_host_blocked
suffix:semicolon
multiline_comment|/*&n;     * For SCSI hosts which are PCI devices, set pci_dev so that&n;     * we can do BIOS EDD 3.0 mappings&n;     */
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
multiline_comment|/* &n;     * Support for driverfs filesystem&n;     */
DECL|member|host_driverfs_dev
r_struct
id|device
id|host_driverfs_dev
suffix:semicolon
multiline_comment|/*&n;     * We should ensure that this is aligned, both for better performance&n;     * and also because some compilers (m68k) don&squot;t automatically force&n;     * alignment to a long boundary.&n;     */
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
multiline_comment|/*&n; * These two functions are used to allocate and free a pseudo device&n; * which will connect to the host adapter itself rather than any&n; * physical device.  You must deallocate when you are done with the&n; * thing.  This physical pseudo-device isn&squot;t real and won&squot;t be available&n; * from any high-level drivers.&n; */
r_extern
r_void
id|scsi_free_host_dev
c_func
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
r_extern
id|Scsi_Device
op_star
id|scsi_get_host_dev
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
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
r_extern
r_void
id|scsi_report_bus_reset
c_func
(paren
r_struct
id|Scsi_Host
op_star
comma
r_int
)paren
suffix:semicolon
DECL|struct|SHN
r_typedef
r_struct
id|SHN
(brace
DECL|member|shn_list
r_struct
id|list_head
id|shn_list
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|host_no
r_int
r_int
id|host_no
suffix:semicolon
DECL|member|host_registered
r_int
r_int
id|host_registered
suffix:semicolon
DECL|typedef|Scsi_Host_Name
)brace
id|Scsi_Host_Name
suffix:semicolon
r_extern
r_void
id|scsi_proc_host_mkdir
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_proc_host_add
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_proc_host_rm
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; *  scsi_init initializes the scsi hosts.&n; */
r_extern
r_int
id|next_scsi_host
suffix:semicolon
r_int
r_int
id|scsi_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|scsi_register_blocked_host
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_deregister_blocked_host
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
DECL|function|scsi_set_pci_device
r_static
r_inline
r_void
id|scsi_set_pci_device
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
comma
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
id|shost-&gt;pci_dev
op_assign
id|pdev
suffix:semicolon
id|shost-&gt;host_driverfs_dev.parent
op_assign
op_amp
id|pdev-&gt;dev
suffix:semicolon
)brace
multiline_comment|/*&n; * Prototypes for functions/data in scsi_scan.c&n; */
r_extern
r_void
id|scan_scsis
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
id|uint
)paren
suffix:semicolon
r_extern
r_void
id|scsi_mark_host_reset
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
DECL|macro|BLANK_HOST
mdefine_line|#define BLANK_HOST {&quot;&quot;, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
DECL|struct|Scsi_Device_Template
r_struct
id|Scsi_Device_Template
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|tag
r_const
r_char
op_star
id|tag
suffix:semicolon
DECL|member|module
r_struct
id|module
op_star
id|module
suffix:semicolon
multiline_comment|/* Used for loadable modules */
DECL|member|scsi_type
r_int
r_char
id|scsi_type
suffix:semicolon
DECL|member|detect
r_int
(paren
op_star
id|detect
)paren
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
multiline_comment|/* Returns 1 if we can attach this device */
DECL|member|attach
r_int
(paren
op_star
id|attach
)paren
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
multiline_comment|/* Attach devices to arrays */
DECL|member|detach
r_void
(paren
op_star
id|detach
)paren
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
DECL|member|init_command
r_int
(paren
op_star
id|init_command
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/* Used by new queueing code. &n;                                           Selects command for blkdevs */
DECL|member|scsi_driverfs_driver
r_struct
id|device_driver
id|scsi_driverfs_driver
suffix:semicolon
)brace
suffix:semicolon
r_void
id|scsi_initialize_queue
c_func
(paren
id|Scsi_Device
op_star
comma
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Highlevel driver registration/unregistration.&n; */
r_extern
r_int
id|scsi_register_device
c_func
(paren
r_struct
id|Scsi_Device_Template
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_unregister_device
c_func
(paren
r_struct
id|Scsi_Device_Template
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * HBA allocation/freeing.&n; */
r_extern
r_struct
id|Scsi_Host
op_star
id|scsi_register
c_func
(paren
id|Scsi_Host_Template
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
multiline_comment|/*&n; * HBA registration/unregistration.&n; */
r_extern
r_int
id|scsi_add_host
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_remove_host
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Legacy HBA template registration/unregistration.&n; */
r_extern
r_int
id|scsi_register_host
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_unregister_host
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|Scsi_Host
op_star
id|scsi_host_get_next
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
id|scsi_host_hn_get
c_func
(paren
r_int
r_int
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
)paren
suffix:semicolon
r_extern
r_void
id|scsi_host_hn_init
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_host_hn_release
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * host_busy inc/dec/test functions&n; */
r_extern
r_void
id|scsi_host_busy_inc
c_func
(paren
r_struct
id|Scsi_Host
op_star
comma
id|Scsi_Device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_host_busy_dec_and_test
c_func
(paren
r_struct
id|Scsi_Host
op_star
comma
id|Scsi_Device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_host_failed_inc_and_test
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
multiline_comment|/**&n; * scsi_find_device - find a device given the host&n; * @shost:&t;SCSI host pointer&n; * @channel:&t;SCSI channel (zero if only one channel)&n; * @pun:&t;SCSI target number (physical unit number)&n; * @lun:&t;SCSI Logical Unit Number&n; **/
DECL|function|scsi_find_device
r_static
r_inline
id|Scsi_Device
op_star
id|scsi_find_device
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
comma
r_int
id|channel
comma
r_int
id|pun
comma
r_int
id|lun
)paren
(brace
id|Scsi_Device
op_star
id|sdev
suffix:semicolon
r_for
c_loop
(paren
id|sdev
op_assign
id|shost-&gt;host_queue
suffix:semicolon
id|sdev
op_ne
l_int|NULL
suffix:semicolon
id|sdev
op_assign
id|sdev-&gt;next
)paren
r_if
c_cond
(paren
id|sdev-&gt;channel
op_eq
id|channel
op_logical_and
id|sdev-&gt;id
op_eq
id|pun
op_logical_and
id|sdev-&gt;lun
op_eq
id|lun
)paren
r_break
suffix:semicolon
r_return
id|sdev
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
