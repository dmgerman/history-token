multiline_comment|/* &n; * File...........: linux/drivers/s390/block/dasd_int.h&n; * Author(s)......: Holger Smolinski &lt;Holger.Smolinski@de.ibm.com&gt;&n; *                  Horst Hummel &lt;Horst.Hummel@de.ibm.com&gt; &n; *&t;&t;    Martin Schwidefsky &lt;schwidefsky@de.ibm.com&gt;&n; * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n; * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 1999,2000&n; *&n; * $Revision: 1.36 $&n; *&n; * History of changes (starts July 2000)&n; * 02/01/01 added dynamic registration of ioctls&n; * 2002/01/04 Created 2.4-2.5 compatibility mode&n; * 05/04/02 code restructuring.&n; */
macro_line|#ifndef DASD_INT_H
DECL|macro|DASD_INT_H
mdefine_line|#define DASD_INT_H
macro_line|#ifdef __KERNEL__
DECL|macro|DASD_PER_MAJOR
mdefine_line|#define DASD_PER_MAJOR ( 1U&lt;&lt;(MINORBITS-DASD_PARTN_BITS))
DECL|macro|DASD_PARTN_MASK
mdefine_line|#define DASD_PARTN_MASK ((1 &lt;&lt; DASD_PARTN_BITS) - 1)
multiline_comment|/*&n; * States a dasd device can have:&n; *   new: the dasd_device_t structure is allocated.&n; *   known: the discipline for the device is identified.&n; *   basic: the device can do basic i/o.&n; *   accept: the device is analysed (format is known).&n; *   ready: partition detection is done and the device is can do block io.&n; *   online: the device accepts requests from the block device queue.&n; *&n; * Things to do for startup state transitions:&n; *   new -&gt; known: find discipline for the device and create devfs entries.&n; *   known -&gt; basic: request irq line for the device.&n; *   basic -&gt; accept: do the initial analysis, e.g. format detection.&n; *   accept-&gt; ready: do block device setup and detect partitions.&n; *   ready -&gt; online: schedule the device tasklet.&n; * Things to do for shutdown state transitions:&n; *   online -&gt; ready: just set the new device state.&n; *   ready -&gt; accept: flush requests from the block device layer and&n; *                    clear partition information.&n; *   accept -&gt; basic: reset format information.&n; *   basic -&gt; known: terminate all requests and free irq.&n; *   known -&gt; new: remove devfs entries and forget discipline.&n; */
DECL|macro|DASD_STATE_NEW
mdefine_line|#define DASD_STATE_NEW&t;  0
DECL|macro|DASD_STATE_KNOWN
mdefine_line|#define DASD_STATE_KNOWN  1
DECL|macro|DASD_STATE_BASIC
mdefine_line|#define DASD_STATE_BASIC  2
DECL|macro|DASD_STATE_ACCEPT
mdefine_line|#define DASD_STATE_ACCEPT 3
DECL|macro|DASD_STATE_READY
mdefine_line|#define DASD_STATE_READY  4
DECL|macro|DASD_STATE_ONLINE
mdefine_line|#define DASD_STATE_ONLINE 5
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/ccwdev.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;asm/debug.h&gt;
macro_line|#include &lt;asm/dasd.h&gt;
macro_line|#include &lt;asm/idals.h&gt;
multiline_comment|/*&n; * SECTION: Type definitions&n; */
r_struct
id|dasd_device_t
suffix:semicolon
DECL|typedef|dasd_ioctl_fn_t
r_typedef
r_int
(paren
op_star
id|dasd_ioctl_fn_t
)paren
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|no
comma
r_int
id|args
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|no
r_int
id|no
suffix:semicolon
DECL|member|handler
id|dasd_ioctl_fn_t
id|handler
suffix:semicolon
DECL|typedef|dasd_ioctl_list_t
)brace
id|dasd_ioctl_list_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|dasd_era_fatal
id|dasd_era_fatal
op_assign
op_minus
l_int|1
comma
multiline_comment|/* no chance to recover&t;&t;     */
DECL|enumerator|dasd_era_none
id|dasd_era_none
op_assign
l_int|0
comma
multiline_comment|/* don&squot;t recover, everything alright */
DECL|enumerator|dasd_era_msg
id|dasd_era_msg
op_assign
l_int|1
comma
multiline_comment|/* don&squot;t recover, just report...     */
DECL|enumerator|dasd_era_recover
id|dasd_era_recover
op_assign
l_int|2
multiline_comment|/* recovery action recommended&t;     */
DECL|typedef|dasd_era_t
)brace
id|dasd_era_t
suffix:semicolon
multiline_comment|/* BIT DEFINITIONS FOR SENSE DATA */
DECL|macro|DASD_SENSE_BIT_0
mdefine_line|#define DASD_SENSE_BIT_0 0x80
DECL|macro|DASD_SENSE_BIT_1
mdefine_line|#define DASD_SENSE_BIT_1 0x40
DECL|macro|DASD_SENSE_BIT_2
mdefine_line|#define DASD_SENSE_BIT_2 0x20
DECL|macro|DASD_SENSE_BIT_3
mdefine_line|#define DASD_SENSE_BIT_3 0x10
multiline_comment|/*&n; * SECTION: MACROs for klogd and s390 debug feature (dbf)&n; */
DECL|macro|DBF_DEV_EVENT
mdefine_line|#define DBF_DEV_EVENT(d_level, d_device, d_str, d_data...) &bslash;&n;do { &bslash;&n;&t;debug_sprintf_event(d_device-&gt;debug_area, &bslash;&n;&t;&t;&t;    d_level, &bslash;&n;&t;&t;&t;    d_str &quot;&bslash;n&quot;, &bslash;&n;&t;&t;&t;    d_data); &bslash;&n;} while(0)
DECL|macro|DBF_DEV_EXC
mdefine_line|#define DBF_DEV_EXC(d_level, d_device, d_str, d_data...) &bslash;&n;do { &bslash;&n;&t;debug_sprintf_exception(d_device-&gt;debug_area, &bslash;&n;&t;&t;&t;&t;d_level, &bslash;&n;&t;&t;&t;&t;d_str &quot;&bslash;n&quot;, &bslash;&n;&t;&t;&t;&t;d_data); &bslash;&n;} while(0)
DECL|macro|DBF_EVENT
mdefine_line|#define DBF_EVENT(d_level, d_str, d_data...)&bslash;&n;do { &bslash;&n;&t;debug_sprintf_event(dasd_debug_area, &bslash;&n;&t;&t;&t;    d_level,&bslash;&n;&t;&t;&t;    d_str &quot;&bslash;n&quot;, &bslash;&n;&t;&t;&t;    d_data); &bslash;&n;} while(0)
DECL|macro|DBF_EXC
mdefine_line|#define DBF_EXC(d_level, d_str, d_data...)&bslash;&n;do { &bslash;&n;&t;debug_sprintf_exception(dasd_debug_area, &bslash;&n;&t;&t;&t;&t;d_level,&bslash;&n;&t;&t;&t;&t;d_str &quot;&bslash;n&quot;, &bslash;&n;&t;&t;&t;&t;d_data); &bslash;&n;} while(0)
multiline_comment|/* definition of dbf debug levels */
DECL|macro|DBF_EMERG
mdefine_line|#define&t;DBF_EMERG&t;0&t;/* system is unusable&t;&t;&t;*/
DECL|macro|DBF_ALERT
mdefine_line|#define&t;DBF_ALERT&t;1&t;/* action must be taken immediately&t;*/
DECL|macro|DBF_CRIT
mdefine_line|#define&t;DBF_CRIT&t;2&t;/* critical conditions&t;&t;&t;*/
DECL|macro|DBF_ERR
mdefine_line|#define&t;DBF_ERR&t;&t;3&t;/* error conditions&t;&t;&t;*/
DECL|macro|DBF_WARNING
mdefine_line|#define&t;DBF_WARNING&t;4&t;/* warning conditions&t;&t;&t;*/
DECL|macro|DBF_NOTICE
mdefine_line|#define&t;DBF_NOTICE&t;5&t;/* normal but significant condition&t;*/
DECL|macro|DBF_INFO
mdefine_line|#define&t;DBF_INFO&t;6&t;/* informational&t;&t;&t;*/
DECL|macro|DBF_DEBUG
mdefine_line|#define&t;DBF_DEBUG&t;6&t;/* debug-level messages&t;&t;&t;*/
multiline_comment|/* messages to be written via klogd and dbf */
DECL|macro|DEV_MESSAGE
mdefine_line|#define DEV_MESSAGE(d_loglevel,d_device,d_string,d_args...)&bslash;&n;do { &bslash;&n;&t;printk(d_loglevel PRINTK_HEADER &quot; %s,%s: &quot; &bslash;&n;&t;       d_string &quot;&bslash;n&quot;, d_device-&gt;gdp-&gt;disk_name, &bslash;&n;&t;       d_device-&gt;cdev-&gt;dev.bus_id, d_args); &bslash;&n;&t;DBF_DEV_EVENT(DBF_ALERT, d_device, d_string, d_args); &bslash;&n;} while(0)
DECL|macro|MESSAGE
mdefine_line|#define MESSAGE(d_loglevel,d_string,d_args...)&bslash;&n;do { &bslash;&n;&t;printk(d_loglevel PRINTK_HEADER &quot; &quot; d_string &quot;&bslash;n&quot;, d_args); &bslash;&n;&t;DBF_EVENT(DBF_ALERT, d_string, d_args); &bslash;&n;} while(0)
DECL|struct|dasd_ccw_req_t
r_typedef
r_struct
id|dasd_ccw_req_t
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* Eye catcher */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* list_head for request queueing. */
multiline_comment|/* Where to execute what... */
DECL|member|device
r_struct
id|dasd_device_t
op_star
id|device
suffix:semicolon
multiline_comment|/* device the request is for */
DECL|member|cpaddr
r_struct
id|ccw1
op_star
id|cpaddr
suffix:semicolon
multiline_comment|/* address of channel program */
DECL|member|status
r_char
id|status
suffix:semicolon
multiline_comment|/* status of this request */
DECL|member|retries
r_int
id|retries
suffix:semicolon
multiline_comment|/* A retry counter */
multiline_comment|/* ... and how */
DECL|member|expires
r_int
id|expires
suffix:semicolon
multiline_comment|/* expiration period in jiffies */
DECL|member|lpm
r_char
id|lpm
suffix:semicolon
multiline_comment|/* logical path mask */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* pointer to data area */
multiline_comment|/* these are important for recovering erroneous requests          */
DECL|member|dstat
r_struct
id|irb
op_star
id|dstat
suffix:semicolon
multiline_comment|/* device status in case of an error */
DECL|member|refers
r_struct
id|dasd_ccw_req_t
op_star
id|refers
suffix:semicolon
multiline_comment|/* ERP-chain queueing. */
DECL|member|function
r_void
op_star
id|function
suffix:semicolon
multiline_comment|/* originating ERP action */
DECL|member|buildclk
r_int
r_int
r_int
id|buildclk
suffix:semicolon
multiline_comment|/* TOD-clock of request generation */
DECL|member|startclk
r_int
r_int
r_int
id|startclk
suffix:semicolon
multiline_comment|/* TOD-clock of request start */
DECL|member|stopclk
r_int
r_int
r_int
id|stopclk
suffix:semicolon
multiline_comment|/* TOD-clock of request interrupt */
DECL|member|endclk
r_int
r_int
r_int
id|endclk
suffix:semicolon
multiline_comment|/* TOD-clock of request termination */
multiline_comment|/* Callback that is called after reaching final status. */
DECL|member|callback
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|dasd_ccw_req_t
op_star
comma
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|member|callback_data
r_void
op_star
id|callback_data
suffix:semicolon
DECL|typedef|dasd_ccw_req_t
)brace
id|dasd_ccw_req_t
suffix:semicolon
multiline_comment|/* &n; * dasd_ccw_req_t -&gt; status can be:&n; */
DECL|macro|DASD_CQR_FILLED
mdefine_line|#define DASD_CQR_FILLED   0x00&t;/* request is ready to be processed */
DECL|macro|DASD_CQR_QUEUED
mdefine_line|#define DASD_CQR_QUEUED   0x01&t;/* request is queued to be processed */
DECL|macro|DASD_CQR_IN_IO
mdefine_line|#define DASD_CQR_IN_IO    0x02&t;/* request is currently in IO */
DECL|macro|DASD_CQR_DONE
mdefine_line|#define DASD_CQR_DONE     0x03&t;/* request is completed successfully */
DECL|macro|DASD_CQR_ERROR
mdefine_line|#define DASD_CQR_ERROR    0x04&t;/* request is completed with error */
DECL|macro|DASD_CQR_FAILED
mdefine_line|#define DASD_CQR_FAILED   0x05&t;/* request is finally failed */
DECL|macro|DASD_CQR_PENDING
mdefine_line|#define DASD_CQR_PENDING  0x06  /* request is waiting for interrupt - ERP only */ 
multiline_comment|/* Signature for error recovery functions. */
DECL|typedef|dasd_erp_fn_t
r_typedef
id|dasd_ccw_req_t
op_star
(paren
op_star
id|dasd_erp_fn_t
)paren
(paren
id|dasd_ccw_req_t
op_star
id|cqr
)paren
suffix:semicolon
multiline_comment|/*&n; * the dasd_discipline_t is&n; * sth like a table of virtual functions, if you think of dasd_eckd&n; * inheriting dasd...&n; * no, currently we are not planning to reimplement the driver in C++&n; */
DECL|struct|dasd_discipline_t
r_typedef
r_struct
id|dasd_discipline_t
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|ebcname
r_char
id|ebcname
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* a name used for tagging and printks */
DECL|member|name
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* a name used for tagging and printks */
DECL|member|max_blocks
r_int
id|max_blocks
suffix:semicolon
multiline_comment|/* maximum number of blocks to be chained */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* used for list of disciplines */
multiline_comment|/*&n;         * Device recognition functions. check_device is used to verify&n;         * the sense data and the information returned by read device&n;         * characteristics. It returns 0 if the discipline can be used&n;         * for the device in question.&n;         * do_analysis is used in the step from device state &quot;basic&quot; to&n;         * state &quot;accept&quot;. It returns 0 if the device can be made ready,&n;         * it returns -EMEDIUMTYPE if the device can&squot;t be made ready or&n;         * -EAGAIN if do_analysis started a ccw that needs to complete&n;         * before the analysis may be repeated.&n;         */
DECL|member|check_device
r_int
(paren
op_star
id|check_device
)paren
(paren
r_struct
id|dasd_device_t
op_star
)paren
suffix:semicolon
DECL|member|do_analysis
r_int
(paren
op_star
id|do_analysis
)paren
(paren
r_struct
id|dasd_device_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;         * Device operation functions. build_cp creates a ccw chain for&n;         * a block device request, start_io starts the request and&n;         * term_IO cancels it (e.g. in case of a timeout). format_device&n;         * returns a ccw chain to be used to format the device.&n;         */
DECL|member|build_cp
id|dasd_ccw_req_t
op_star
(paren
op_star
id|build_cp
)paren
(paren
r_struct
id|dasd_device_t
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
DECL|member|start_IO
r_int
(paren
op_star
id|start_IO
)paren
(paren
id|dasd_ccw_req_t
op_star
)paren
suffix:semicolon
DECL|member|term_IO
r_int
(paren
op_star
id|term_IO
)paren
(paren
id|dasd_ccw_req_t
op_star
)paren
suffix:semicolon
DECL|member|format_device
id|dasd_ccw_req_t
op_star
(paren
op_star
id|format_device
)paren
(paren
r_struct
id|dasd_device_t
op_star
comma
r_struct
id|format_data_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;         * Error recovery functions. examine_error() returns a value that&n;         * indicates what to do for an error condition. If examine_error()&n;         * returns &squot;dasd_era_recover&squot; erp_action() is called to create a &n;         * special error recovery ccw. erp_postaction() is called after&n;         * an error recovery ccw has finished its execution. dump_sense&n;         * is called for every error condition to print the sense data&n;         * to the console.&n;         */
DECL|member|examine_error
id|dasd_era_t
c_func
(paren
op_star
id|examine_error
)paren
(paren
id|dasd_ccw_req_t
op_star
comma
r_struct
id|irb
op_star
)paren
suffix:semicolon
DECL|member|erp_action
id|dasd_erp_fn_t
c_func
(paren
op_star
id|erp_action
)paren
(paren
id|dasd_ccw_req_t
op_star
)paren
suffix:semicolon
DECL|member|erp_postaction
id|dasd_erp_fn_t
c_func
(paren
op_star
id|erp_postaction
)paren
(paren
id|dasd_ccw_req_t
op_star
)paren
suffix:semicolon
DECL|member|dump_sense
r_void
(paren
op_star
id|dump_sense
)paren
(paren
r_struct
id|dasd_device_t
op_star
comma
id|dasd_ccw_req_t
op_star
comma
r_struct
id|irb
op_star
)paren
suffix:semicolon
multiline_comment|/* i/o control functions. */
DECL|member|fill_geometry
r_int
(paren
op_star
id|fill_geometry
)paren
(paren
r_struct
id|dasd_device_t
op_star
comma
r_struct
id|hd_geometry
op_star
)paren
suffix:semicolon
DECL|member|fill_info
r_int
(paren
op_star
id|fill_info
)paren
(paren
r_struct
id|dasd_device_t
op_star
comma
id|dasd_information2_t
op_star
)paren
suffix:semicolon
DECL|typedef|dasd_discipline_t
)brace
id|dasd_discipline_t
suffix:semicolon
r_extern
id|dasd_discipline_t
id|dasd_diag_discipline
suffix:semicolon
macro_line|#ifdef CONFIG_DASD_DIAG
DECL|macro|dasd_diag_discipline_pointer
mdefine_line|#define dasd_diag_discipline_pointer (&amp;dasd_diag_discipline)
macro_line|#else
DECL|macro|dasd_diag_discipline_pointer
mdefine_line|#define dasd_diag_discipline_pointer (0)
macro_line|#endif
DECL|struct|dasd_device_t
r_typedef
r_struct
id|dasd_device_t
(brace
multiline_comment|/* Block device stuff. */
DECL|member|gdp
r_struct
id|gendisk
op_star
id|gdp
suffix:semicolon
DECL|member|devfs_entry
id|devfs_handle_t
id|devfs_entry
suffix:semicolon
DECL|member|request_queue
id|request_queue_t
op_star
id|request_queue
suffix:semicolon
DECL|member|request_queue_lock
id|spinlock_t
id|request_queue_lock
suffix:semicolon
DECL|member|blocks
r_int
r_int
id|blocks
suffix:semicolon
multiline_comment|/* size of volume in blocks */
DECL|member|bp_block
r_int
r_int
id|bp_block
suffix:semicolon
multiline_comment|/* bytes per block */
DECL|member|s2b_shift
r_int
r_int
id|s2b_shift
suffix:semicolon
multiline_comment|/* log2 (bp_block/512) */
DECL|member|ro_flag
r_int
id|ro_flag
suffix:semicolon
multiline_comment|/* read-only flag */
DECL|member|use_diag_flag
r_int
id|use_diag_flag
suffix:semicolon
multiline_comment|/* diag allowed flag */
multiline_comment|/* Device discipline stuff. */
DECL|member|discipline
id|dasd_discipline_t
op_star
id|discipline
suffix:semicolon
DECL|member|private
r_char
op_star
r_private
suffix:semicolon
multiline_comment|/* Device state and target state. */
DECL|member|state
DECL|member|target
r_int
id|state
comma
id|target
suffix:semicolon
multiline_comment|/* Open and reference count. */
DECL|member|ref_count
id|atomic_t
id|ref_count
suffix:semicolon
DECL|member|open_count
id|atomic_t
id|open_count
suffix:semicolon
multiline_comment|/* ccw queue and memory for static ccw/erp buffers. */
DECL|member|ccw_queue
r_struct
id|list_head
id|ccw_queue
suffix:semicolon
DECL|member|mem_lock
id|spinlock_t
id|mem_lock
suffix:semicolon
DECL|member|ccw_mem
r_void
op_star
id|ccw_mem
suffix:semicolon
DECL|member|erp_mem
r_void
op_star
id|erp_mem
suffix:semicolon
DECL|member|ccw_chunks
r_struct
id|list_head
id|ccw_chunks
suffix:semicolon
DECL|member|erp_chunks
r_struct
id|list_head
id|erp_chunks
suffix:semicolon
multiline_comment|/* Common i/o stuff. */
multiline_comment|/* FIXME: remove the next */
DECL|member|devno
r_int
id|devno
suffix:semicolon
DECL|member|tasklet_scheduled
id|atomic_t
id|tasklet_scheduled
suffix:semicolon
DECL|member|tasklet
r_struct
id|tasklet_struct
id|tasklet
suffix:semicolon
DECL|member|kick_work
r_struct
id|work_struct
id|kick_work
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|debug_area
id|debug_info_t
op_star
id|debug_area
suffix:semicolon
DECL|member|cdev
r_struct
id|ccw_device
op_star
id|cdev
suffix:semicolon
macro_line|#ifdef CONFIG_DASD_PROFILE
DECL|member|profile
id|dasd_profile_info_t
id|profile
suffix:semicolon
macro_line|#endif
DECL|typedef|dasd_device_t
)brace
id|dasd_device_t
suffix:semicolon
multiline_comment|/*&n; * dasd_devmap_t is used to store the features and the relation&n; * between device number and device index. To find a dasd_devmap_t&n; * that corresponds to a device number of a device index each&n; * dasd_devmap_t is added to two linked lists, one to search by&n; * the device number and one to search by the device index. As&n; * soon as big minor numbers are available the device index list&n; * can be removed since the device number will then be identical&n; * to the device index.&n; */
r_typedef
r_struct
(brace
DECL|member|devindex_list
r_struct
id|list_head
id|devindex_list
suffix:semicolon
DECL|member|devno_list
r_struct
id|list_head
id|devno_list
suffix:semicolon
DECL|member|devindex
r_int
r_int
id|devindex
suffix:semicolon
DECL|member|devno
r_int
r_int
id|devno
suffix:semicolon
DECL|member|features
r_int
r_int
id|features
suffix:semicolon
DECL|member|device
id|dasd_device_t
op_star
id|device
suffix:semicolon
DECL|typedef|dasd_devmap_t
)brace
id|dasd_devmap_t
suffix:semicolon
multiline_comment|/*&n; * The static memory in ccw_mem and erp_mem is managed by a sorted&n; * list of free memory chunks.&n; */
DECL|struct|dasd_mchunk_t
r_typedef
r_struct
id|dasd_mchunk_t
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|typedef|dasd_mchunk_t
)brace
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
id|dasd_mchunk_t
suffix:semicolon
r_static
r_inline
r_void
DECL|function|dasd_init_chunklist
id|dasd_init_chunklist
c_func
(paren
r_struct
id|list_head
op_star
id|chunk_list
comma
r_void
op_star
id|mem
comma
r_int
r_int
id|size
)paren
(brace
id|dasd_mchunk_t
op_star
id|chunk
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
id|chunk_list
)paren
suffix:semicolon
id|chunk
op_assign
(paren
id|dasd_mchunk_t
op_star
)paren
id|mem
suffix:semicolon
id|chunk-&gt;size
op_assign
id|size
op_minus
r_sizeof
(paren
id|dasd_mchunk_t
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|chunk-&gt;list
comma
id|chunk_list
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
op_star
DECL|function|dasd_alloc_chunk
id|dasd_alloc_chunk
c_func
(paren
r_struct
id|list_head
op_star
id|chunk_list
comma
r_int
r_int
id|size
)paren
(brace
id|dasd_mchunk_t
op_star
id|chunk
comma
op_star
id|tmp
suffix:semicolon
r_struct
id|list_head
op_star
id|l
suffix:semicolon
id|size
op_assign
(paren
id|size
op_plus
l_int|7L
)paren
op_amp
op_minus
l_int|8L
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
id|chunk_list
)paren
(brace
id|chunk
op_assign
id|list_entry
c_func
(paren
id|l
comma
id|dasd_mchunk_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chunk-&gt;size
OL
id|size
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|chunk-&gt;size
OG
id|size
op_plus
r_sizeof
(paren
id|dasd_mchunk_t
)paren
)paren
(brace
r_char
op_star
id|endaddr
op_assign
(paren
r_char
op_star
)paren
(paren
id|chunk
op_plus
l_int|1
)paren
op_plus
id|chunk-&gt;size
suffix:semicolon
id|tmp
op_assign
(paren
id|dasd_mchunk_t
op_star
)paren
(paren
id|endaddr
op_minus
id|size
)paren
op_minus
l_int|1
suffix:semicolon
id|tmp-&gt;size
op_assign
id|size
suffix:semicolon
id|chunk-&gt;size
op_sub_assign
id|size
op_plus
r_sizeof
(paren
id|dasd_mchunk_t
)paren
suffix:semicolon
id|chunk
op_assign
id|tmp
suffix:semicolon
)brace
r_else
id|list_del
c_func
(paren
op_amp
id|chunk-&gt;list
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
(paren
id|chunk
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|dasd_free_chunk
id|dasd_free_chunk
c_func
(paren
r_struct
id|list_head
op_star
id|chunk_list
comma
r_void
op_star
id|mem
)paren
(brace
id|dasd_mchunk_t
op_star
id|chunk
comma
op_star
id|tmp
suffix:semicolon
r_struct
id|list_head
op_star
id|p
comma
op_star
id|left
suffix:semicolon
id|chunk
op_assign
(paren
id|dasd_mchunk_t
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|mem
op_minus
r_sizeof
(paren
id|dasd_mchunk_t
)paren
)paren
suffix:semicolon
multiline_comment|/* Find out the left neighbour in chunk_list. */
id|left
op_assign
id|chunk_list
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
id|chunk_list
)paren
(brace
r_if
c_cond
(paren
id|list_entry
c_func
(paren
id|p
comma
id|dasd_mchunk_t
comma
id|list
)paren
OG
id|chunk
)paren
r_break
suffix:semicolon
id|left
op_assign
id|p
suffix:semicolon
)brace
multiline_comment|/* Try to merge with right neighbour = next element from left. */
r_if
c_cond
(paren
id|left-&gt;next
op_ne
id|chunk_list
)paren
(brace
id|tmp
op_assign
id|list_entry
c_func
(paren
id|left-&gt;next
comma
id|dasd_mchunk_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
(paren
id|chunk
op_plus
l_int|1
)paren
op_plus
id|chunk-&gt;size
op_eq
(paren
r_char
op_star
)paren
id|tmp
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|tmp-&gt;list
)paren
suffix:semicolon
id|chunk-&gt;size
op_add_assign
id|tmp-&gt;size
op_plus
r_sizeof
(paren
id|dasd_mchunk_t
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Try to merge with left neighbour. */
r_if
c_cond
(paren
id|left
op_ne
id|chunk_list
)paren
(brace
id|tmp
op_assign
id|list_entry
c_func
(paren
id|left
comma
id|dasd_mchunk_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
(paren
id|tmp
op_plus
l_int|1
)paren
op_plus
id|tmp-&gt;size
op_eq
(paren
r_char
op_star
)paren
id|chunk
)paren
(brace
id|tmp-&gt;size
op_add_assign
id|chunk-&gt;size
op_plus
r_sizeof
(paren
id|dasd_mchunk_t
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|__list_add
c_func
(paren
op_amp
id|chunk-&gt;list
comma
id|left
comma
id|left-&gt;next
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Check if bsize is in { 512, 1024, 2048, 4096 }&n; */
r_static
r_inline
r_int
DECL|function|dasd_check_blocksize
id|dasd_check_blocksize
c_func
(paren
r_int
id|bsize
)paren
(brace
r_if
c_cond
(paren
id|bsize
template_param
l_int|4096
op_logical_or
(paren
id|bsize
op_amp
(paren
id|bsize
op_minus
l_int|1
)paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EMEDIUMTYPE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* externals in dasd.c */
DECL|macro|DASD_PROFILE_ON
mdefine_line|#define DASD_PROFILE_ON&t; 1
DECL|macro|DASD_PROFILE_OFF
mdefine_line|#define DASD_PROFILE_OFF 0
r_extern
id|debug_info_t
op_star
id|dasd_debug_area
suffix:semicolon
r_extern
id|dasd_profile_info_t
id|dasd_global_profile
suffix:semicolon
r_extern
r_int
r_int
id|dasd_profile_level
suffix:semicolon
r_extern
r_struct
id|block_device_operations
id|dasd_device_operations
suffix:semicolon
id|dasd_ccw_req_t
op_star
id|dasd_kmalloc_request
c_func
(paren
r_char
op_star
comma
r_int
comma
r_int
comma
id|dasd_device_t
op_star
)paren
suffix:semicolon
multiline_comment|/* unused */
id|dasd_ccw_req_t
op_star
id|dasd_smalloc_request
c_func
(paren
r_char
op_star
comma
r_int
comma
r_int
comma
id|dasd_device_t
op_star
)paren
suffix:semicolon
r_void
id|dasd_kfree_request
c_func
(paren
id|dasd_ccw_req_t
op_star
comma
id|dasd_device_t
op_star
)paren
suffix:semicolon
r_void
id|dasd_sfree_request
c_func
(paren
id|dasd_ccw_req_t
op_star
comma
id|dasd_device_t
op_star
)paren
suffix:semicolon
r_static
r_inline
r_int
DECL|function|dasd_kmalloc_set_cda
id|dasd_kmalloc_set_cda
c_func
(paren
r_struct
id|ccw1
op_star
id|ccw
comma
r_void
op_star
id|cda
comma
id|dasd_device_t
op_star
id|device
)paren
(brace
r_return
id|set_normalized_cda
c_func
(paren
id|ccw
comma
id|cda
)paren
suffix:semicolon
)brace
id|dasd_device_t
op_star
id|dasd_alloc_device
c_func
(paren
id|dasd_devmap_t
op_star
)paren
suffix:semicolon
r_void
id|dasd_free_device
c_func
(paren
id|dasd_device_t
op_star
)paren
suffix:semicolon
r_void
id|dasd_enable_device
c_func
(paren
id|dasd_device_t
op_star
)paren
suffix:semicolon
r_void
id|dasd_set_target_state
c_func
(paren
id|dasd_device_t
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|dasd_kick_device
c_func
(paren
id|dasd_device_t
op_star
)paren
suffix:semicolon
r_void
id|dasd_add_request_head
c_func
(paren
id|dasd_ccw_req_t
op_star
)paren
suffix:semicolon
r_void
id|dasd_add_request_tail
c_func
(paren
id|dasd_ccw_req_t
op_star
)paren
suffix:semicolon
multiline_comment|/* unused */
r_int
id|dasd_start_IO
c_func
(paren
id|dasd_ccw_req_t
op_star
)paren
suffix:semicolon
r_int
id|dasd_term_IO
c_func
(paren
id|dasd_ccw_req_t
op_star
)paren
suffix:semicolon
r_void
id|dasd_schedule_bh
c_func
(paren
id|dasd_device_t
op_star
)paren
suffix:semicolon
r_int
id|dasd_sleep_on
c_func
(paren
id|dasd_ccw_req_t
op_star
)paren
suffix:semicolon
r_int
id|dasd_sleep_on_immediatly
c_func
(paren
id|dasd_ccw_req_t
op_star
)paren
suffix:semicolon
r_int
id|dasd_sleep_on_interruptible
c_func
(paren
id|dasd_ccw_req_t
op_star
)paren
suffix:semicolon
r_void
id|dasd_set_timer
c_func
(paren
id|dasd_device_t
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|dasd_clear_timer
c_func
(paren
id|dasd_device_t
op_star
)paren
suffix:semicolon
r_int
id|dasd_cancel_req
c_func
(paren
id|dasd_ccw_req_t
op_star
)paren
suffix:semicolon
multiline_comment|/* unused */
r_int
id|dasd_generic_probe
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
id|dasd_discipline_t
op_star
id|discipline
)paren
suffix:semicolon
r_int
id|dasd_generic_remove
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
suffix:semicolon
r_int
id|dasd_generic_set_online
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
id|dasd_discipline_t
op_star
id|discipline
)paren
suffix:semicolon
r_int
id|dasd_generic_set_offline
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
suffix:semicolon
multiline_comment|/* externals in dasd_devmap.c */
r_extern
r_int
id|dasd_max_devindex
suffix:semicolon
r_extern
r_int
id|dasd_probeonly
suffix:semicolon
r_extern
r_int
id|dasd_autodetect
suffix:semicolon
r_int
id|dasd_devmap_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|dasd_devmap_exit
c_func
(paren
r_void
)paren
suffix:semicolon
id|dasd_devmap_t
op_star
id|dasd_devmap_from_devno
c_func
(paren
r_int
)paren
suffix:semicolon
id|dasd_devmap_t
op_star
id|dasd_devmap_from_devindex
c_func
(paren
r_int
)paren
suffix:semicolon
id|dasd_device_t
op_star
id|dasd_get_device
c_func
(paren
id|dasd_devmap_t
op_star
)paren
suffix:semicolon
r_void
id|dasd_put_device
c_func
(paren
id|dasd_devmap_t
op_star
)paren
suffix:semicolon
r_int
id|dasd_parse
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|dasd_add_range
c_func
(paren
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* externals in dasd_gendisk.c */
r_int
id|dasd_gendisk_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|dasd_gendisk_exit
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|dasd_gendisk_index_major
c_func
(paren
r_int
)paren
suffix:semicolon
r_struct
id|gendisk
op_star
id|dasd_gendisk_alloc
c_func
(paren
r_int
)paren
suffix:semicolon
r_void
id|dasd_setup_partitions
c_func
(paren
id|dasd_device_t
op_star
)paren
suffix:semicolon
r_void
id|dasd_destroy_partitions
c_func
(paren
id|dasd_device_t
op_star
)paren
suffix:semicolon
multiline_comment|/* externals in dasd_ioctl.c */
r_int
id|dasd_ioctl_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|dasd_ioctl_exit
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|dasd_ioctl_no_register
c_func
(paren
r_struct
id|module
op_star
comma
r_int
comma
id|dasd_ioctl_fn_t
)paren
suffix:semicolon
r_int
id|dasd_ioctl_no_unregister
c_func
(paren
r_struct
id|module
op_star
comma
r_int
comma
id|dasd_ioctl_fn_t
)paren
suffix:semicolon
r_int
id|dasd_ioctl
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* externals in dasd_proc.c */
r_int
id|dasd_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|dasd_proc_exit
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* externals in dasd_erp.c */
id|dasd_ccw_req_t
op_star
id|dasd_default_erp_action
c_func
(paren
id|dasd_ccw_req_t
op_star
)paren
suffix:semicolon
id|dasd_ccw_req_t
op_star
id|dasd_default_erp_postaction
c_func
(paren
id|dasd_ccw_req_t
op_star
)paren
suffix:semicolon
id|dasd_ccw_req_t
op_star
id|dasd_alloc_erp_request
c_func
(paren
r_char
op_star
comma
r_int
comma
r_int
comma
id|dasd_device_t
op_star
)paren
suffix:semicolon
r_void
id|dasd_free_erp_request
c_func
(paren
id|dasd_ccw_req_t
op_star
comma
id|dasd_device_t
op_star
)paren
suffix:semicolon
r_void
id|dasd_log_sense
c_func
(paren
id|dasd_ccw_req_t
op_star
comma
r_struct
id|irb
op_star
)paren
suffix:semicolon
r_void
id|dasd_log_ccw
c_func
(paren
id|dasd_ccw_req_t
op_star
comma
r_int
comma
id|__u32
)paren
suffix:semicolon
multiline_comment|/* externals in dasd_3370_erp.c */
id|dasd_era_t
id|dasd_3370_erp_examine
c_func
(paren
id|dasd_ccw_req_t
op_star
comma
r_struct
id|irb
op_star
)paren
suffix:semicolon
multiline_comment|/* externals in dasd_3990_erp.c */
id|dasd_era_t
id|dasd_3990_erp_examine
c_func
(paren
id|dasd_ccw_req_t
op_star
comma
r_struct
id|irb
op_star
)paren
suffix:semicolon
id|dasd_ccw_req_t
op_star
id|dasd_3990_erp_action
c_func
(paren
id|dasd_ccw_req_t
op_star
)paren
suffix:semicolon
multiline_comment|/* externals in dasd_9336_erp.c */
id|dasd_era_t
id|dasd_9336_erp_examine
c_func
(paren
id|dasd_ccw_req_t
op_star
comma
r_struct
id|irb
op_star
)paren
suffix:semicolon
multiline_comment|/* externals in dasd_9336_erp.c */
id|dasd_era_t
id|dasd_9343_erp_examine
c_func
(paren
id|dasd_ccw_req_t
op_star
comma
r_struct
id|irb
op_star
)paren
suffix:semicolon
id|dasd_ccw_req_t
op_star
id|dasd_9343_erp_action
c_func
(paren
id|dasd_ccw_req_t
op_star
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
macro_line|#endif&t;&t;&t;&t;/* DASD_H */
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4 &n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: 1&n; * tab-width: 8&n; * End:&n; */
eof
