multiline_comment|/*&n; *  hosts.c Copyright (C) 1992 Drew Eckhardt&n; *          Copyright (C) 1993, 1994, 1995 Eric Youngdale&n; *          Copyright (C) 2002-2003 Christoph Hellwig&n; *&n; *  mid to lowlevel SCSI driver interface&n; *      Initial versions: Drew Eckhardt&n; *      Subsequent revisions: Eric Youngdale&n; *&n; *  &lt;drew@colorado.edu&gt;&n; *&n; *  Jiffies wrap fixes (host-&gt;resetting), 3 Dec 1998 Andrea Arcangeli&n; *  Added QLOGIC QLA1280 SCSI controller kernel host support. &n; *     August 4, 1999 Fred Lewis, Intel DuPont&n; *&n; *  Updated to reflect the new initialization scheme for the higher &n; *  level of scsi drivers (sd/sr/st)&n; *  September 17, 2000 Torben Mathiasen &lt;tmm@image.dk&gt;&n; *&n; *  Restructured scsi_host lists and associated functions.&n; *  September 04, 2002 Mike Anderson (andmike@us.ibm.com)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/transport_class.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &lt;scsi/scsi_transport.h&gt;
macro_line|#include &quot;scsi_priv.h&quot;
macro_line|#include &quot;scsi_logging.h&quot;
DECL|variable|scsi_host_next_hn
r_static
r_int
id|scsi_host_next_hn
suffix:semicolon
multiline_comment|/* host_no for next new host */
DECL|function|scsi_host_cls_release
r_static
r_void
id|scsi_host_cls_release
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
id|put_device
c_func
(paren
op_amp
id|class_to_shost
c_func
(paren
id|class_dev
)paren
op_member_access_from_pointer
id|shost_gendev
)paren
suffix:semicolon
)brace
DECL|variable|shost_class
r_static
r_struct
r_class
id|shost_class
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;scsi_host&quot;
comma
dot
id|release
op_assign
id|scsi_host_cls_release
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * scsi_host_cancel - cancel outstanding IO to this host&n; * @shost:&t;pointer to struct Scsi_Host&n; * recovery:&t;recovery requested to run.&n; **/
DECL|function|scsi_host_cancel
r_void
id|scsi_host_cancel
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
comma
r_int
id|recovery
)paren
(brace
r_struct
id|scsi_device
op_star
id|sdev
suffix:semicolon
id|set_bit
c_func
(paren
id|SHOST_CANCEL
comma
op_amp
id|shost-&gt;shost_state
)paren
suffix:semicolon
id|shost_for_each_device
c_func
(paren
id|sdev
comma
id|shost
)paren
(brace
id|scsi_device_cancel
c_func
(paren
id|sdev
comma
id|recovery
)paren
suffix:semicolon
)brace
id|wait_event
c_func
(paren
id|shost-&gt;host_wait
comma
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|SHOST_RECOVERY
comma
op_amp
id|shost-&gt;shost_state
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_remove_host - remove a scsi host&n; * @shost:&t;a pointer to a scsi host to remove&n; **/
DECL|function|scsi_remove_host
r_void
id|scsi_remove_host
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
id|scsi_forget_host
c_func
(paren
id|shost
)paren
suffix:semicolon
id|scsi_host_cancel
c_func
(paren
id|shost
comma
l_int|0
)paren
suffix:semicolon
id|scsi_proc_host_rm
c_func
(paren
id|shost
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|SHOST_DEL
comma
op_amp
id|shost-&gt;shost_state
)paren
suffix:semicolon
id|transport_unregister_device
c_func
(paren
op_amp
id|shost-&gt;shost_gendev
)paren
suffix:semicolon
id|class_device_unregister
c_func
(paren
op_amp
id|shost-&gt;shost_classdev
)paren
suffix:semicolon
id|device_del
c_func
(paren
op_amp
id|shost-&gt;shost_gendev
)paren
suffix:semicolon
)brace
DECL|variable|scsi_remove_host
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_remove_host
)paren
suffix:semicolon
multiline_comment|/**&n; * scsi_add_host - add a scsi host&n; * @shost:&t;scsi host pointer to add&n; * @dev:&t;a struct device of type scsi class&n; *&n; * Return value: &n; * &t;0 on success / != 0 for error&n; **/
DECL|function|scsi_add_host
r_int
id|scsi_add_host
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
r_struct
id|scsi_host_template
op_star
id|sht
op_assign
id|shost-&gt;hostt
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;scsi%d : %s&bslash;n&quot;
comma
id|shost-&gt;host_no
comma
id|sht-&gt;info
ques
c_cond
id|sht
op_member_access_from_pointer
id|info
c_func
(paren
id|shost
)paren
suffix:colon
id|sht-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shost-&gt;can_queue
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: can_queue = 0 no longer supported&bslash;n&quot;
comma
id|sht-&gt;name
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|shost-&gt;shost_gendev.parent
)paren
id|shost-&gt;shost_gendev.parent
op_assign
id|dev
ques
c_cond
id|dev
suffix:colon
op_amp
id|platform_bus
suffix:semicolon
id|error
op_assign
id|device_add
c_func
(paren
op_amp
id|shost-&gt;shost_gendev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
id|set_bit
c_func
(paren
id|SHOST_ADD
comma
op_amp
id|shost-&gt;shost_state
)paren
suffix:semicolon
id|get_device
c_func
(paren
id|shost-&gt;shost_gendev.parent
)paren
suffix:semicolon
id|error
op_assign
id|class_device_add
c_func
(paren
op_amp
id|shost-&gt;shost_classdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out_del_gendev
suffix:semicolon
id|get_device
c_func
(paren
op_amp
id|shost-&gt;shost_gendev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shost-&gt;transportt-&gt;host_size
op_logical_and
(paren
id|shost-&gt;shost_data
op_assign
id|kmalloc
c_func
(paren
id|shost-&gt;transportt-&gt;host_size
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|out_del_classdev
suffix:semicolon
r_if
c_cond
(paren
id|shost-&gt;transportt-&gt;create_work_queue
)paren
(brace
id|snprintf
c_func
(paren
id|shost-&gt;work_q_name
comma
id|KOBJ_NAME_LEN
comma
l_string|&quot;scsi_wq_%d&quot;
comma
id|shost-&gt;host_no
)paren
suffix:semicolon
id|shost-&gt;work_q
op_assign
id|create_singlethread_workqueue
c_func
(paren
id|shost-&gt;work_q_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shost-&gt;work_q
)paren
r_goto
id|out_free_shost_data
suffix:semicolon
)brace
id|error
op_assign
id|scsi_sysfs_add_host
c_func
(paren
id|shost
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out_destroy_host
suffix:semicolon
id|scsi_proc_host_add
c_func
(paren
id|shost
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
id|out_destroy_host
suffix:colon
r_if
c_cond
(paren
id|shost-&gt;work_q
)paren
id|destroy_workqueue
c_func
(paren
id|shost-&gt;work_q
)paren
suffix:semicolon
id|out_free_shost_data
suffix:colon
id|kfree
c_func
(paren
id|shost-&gt;shost_data
)paren
suffix:semicolon
id|out_del_classdev
suffix:colon
id|class_device_del
c_func
(paren
op_amp
id|shost-&gt;shost_classdev
)paren
suffix:semicolon
id|out_del_gendev
suffix:colon
id|device_del
c_func
(paren
op_amp
id|shost-&gt;shost_gendev
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|scsi_add_host
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_add_host
)paren
suffix:semicolon
DECL|function|scsi_host_dev_release
r_static
r_void
id|scsi_host_dev_release
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|shost
op_assign
id|dev_to_shost
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|device
op_star
id|parent
op_assign
id|dev-&gt;parent
suffix:semicolon
r_if
c_cond
(paren
id|shost-&gt;ehandler
)paren
(brace
id|DECLARE_COMPLETION
c_func
(paren
id|sem
)paren
suffix:semicolon
id|shost-&gt;eh_notify
op_assign
op_amp
id|sem
suffix:semicolon
id|shost-&gt;eh_kill
op_assign
l_int|1
suffix:semicolon
id|up
c_func
(paren
id|shost-&gt;eh_wait
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|sem
)paren
suffix:semicolon
id|shost-&gt;eh_notify
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|shost-&gt;work_q
)paren
id|destroy_workqueue
c_func
(paren
id|shost-&gt;work_q
)paren
suffix:semicolon
id|scsi_proc_hostdir_rm
c_func
(paren
id|shost-&gt;hostt
)paren
suffix:semicolon
id|scsi_destroy_command_freelist
c_func
(paren
id|shost
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|shost-&gt;shost_data
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Some drivers (eg aha1542) do scsi_register()/scsi_unregister()&n;&t; * during probing without performing a scsi_set_device() in between.&n;&t; * In this case dev-&gt;parent is NULL.&n;&t; */
r_if
c_cond
(paren
id|parent
)paren
id|put_device
c_func
(paren
id|parent
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|shost
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_host_alloc - register a scsi host adapter instance.&n; * @sht:&t;pointer to scsi host template&n; * @privsize:&t;extra bytes to allocate for driver&n; *&n; * Note:&n; * &t;Allocate a new Scsi_Host and perform basic initialization.&n; * &t;The host is not published to the scsi midlayer until scsi_add_host&n; * &t;is called.&n; *&n; * Return value:&n; * &t;Pointer to a new Scsi_Host&n; **/
DECL|function|scsi_host_alloc
r_struct
id|Scsi_Host
op_star
id|scsi_host_alloc
c_func
(paren
r_struct
id|scsi_host_template
op_star
id|sht
comma
r_int
id|privsize
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|shost
suffix:semicolon
r_int
id|gfp_mask
op_assign
id|GFP_KERNEL
comma
id|rval
suffix:semicolon
id|DECLARE_COMPLETION
c_func
(paren
id|complete
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sht-&gt;unchecked_isa_dma
op_logical_and
id|privsize
)paren
id|gfp_mask
op_or_assign
id|__GFP_DMA
suffix:semicolon
multiline_comment|/* Check to see if this host has any error handling facilities */
r_if
c_cond
(paren
op_logical_neg
id|sht-&gt;eh_strategy_handler
op_logical_and
op_logical_neg
id|sht-&gt;eh_abort_handler
op_logical_and
op_logical_neg
id|sht-&gt;eh_device_reset_handler
op_logical_and
op_logical_neg
id|sht-&gt;eh_bus_reset_handler
op_logical_and
op_logical_neg
id|sht-&gt;eh_host_reset_handler
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ERROR: SCSI host `%s&squot; has no error handling&bslash;n&quot;
l_string|&quot;ERROR: This is not a safe way to run your &quot;
l_string|&quot;SCSI host&bslash;n&quot;
l_string|&quot;ERROR: The error handling must be added to &quot;
l_string|&quot;this driver&bslash;n&quot;
comma
id|sht-&gt;proc_name
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
)brace
id|shost
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|Scsi_Host
)paren
op_plus
id|privsize
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shost
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|shost
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|Scsi_Host
)paren
op_plus
id|privsize
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|shost-&gt;default_lock
)paren
suffix:semicolon
id|scsi_assign_lock
c_func
(paren
id|shost
comma
op_amp
id|shost-&gt;default_lock
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|shost-&gt;__devices
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|shost-&gt;__targets
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|shost-&gt;eh_cmd_q
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|shost-&gt;starved_list
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|shost-&gt;host_wait
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|shost-&gt;scan_mutex
)paren
suffix:semicolon
id|shost-&gt;host_no
op_assign
id|scsi_host_next_hn
op_increment
suffix:semicolon
multiline_comment|/* XXX(hch): still racy */
id|shost-&gt;dma_channel
op_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* These three are default values which can be overridden */
id|shost-&gt;max_channel
op_assign
l_int|0
suffix:semicolon
id|shost-&gt;max_id
op_assign
l_int|8
suffix:semicolon
id|shost-&gt;max_lun
op_assign
l_int|8
suffix:semicolon
multiline_comment|/* Give each shost a default transportt */
id|shost-&gt;transportt
op_assign
op_amp
id|blank_transport_template
suffix:semicolon
multiline_comment|/*&n;&t; * All drivers right now should be able to handle 12 byte&n;&t; * commands.  Every so often there are requests for 16 byte&n;&t; * commands, but individual low-level drivers need to certify that&n;&t; * they actually do something sensible with such commands.&n;&t; */
id|shost-&gt;max_cmd_len
op_assign
l_int|12
suffix:semicolon
id|shost-&gt;hostt
op_assign
id|sht
suffix:semicolon
id|shost-&gt;this_id
op_assign
id|sht-&gt;this_id
suffix:semicolon
id|shost-&gt;can_queue
op_assign
id|sht-&gt;can_queue
suffix:semicolon
id|shost-&gt;sg_tablesize
op_assign
id|sht-&gt;sg_tablesize
suffix:semicolon
id|shost-&gt;cmd_per_lun
op_assign
id|sht-&gt;cmd_per_lun
suffix:semicolon
id|shost-&gt;unchecked_isa_dma
op_assign
id|sht-&gt;unchecked_isa_dma
suffix:semicolon
id|shost-&gt;use_clustering
op_assign
id|sht-&gt;use_clustering
suffix:semicolon
id|shost-&gt;ordered_flush
op_assign
id|sht-&gt;ordered_flush
suffix:semicolon
id|shost-&gt;ordered_tag
op_assign
id|sht-&gt;ordered_tag
suffix:semicolon
multiline_comment|/*&n;&t; * hosts/devices that do queueing must support ordered tags&n;&t; */
r_if
c_cond
(paren
id|shost-&gt;can_queue
OG
l_int|1
op_logical_and
id|shost-&gt;ordered_flush
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;scsi: ordered flushes don&squot;t support queueing&bslash;n&quot;
)paren
suffix:semicolon
id|shost-&gt;ordered_flush
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sht-&gt;max_host_blocked
)paren
id|shost-&gt;max_host_blocked
op_assign
id|sht-&gt;max_host_blocked
suffix:semicolon
r_else
id|shost-&gt;max_host_blocked
op_assign
id|SCSI_DEFAULT_HOST_BLOCKED
suffix:semicolon
multiline_comment|/*&n;&t; * If the driver imposes no hard sector transfer limit, start at&n;&t; * machine infinity initially.&n;&t; */
r_if
c_cond
(paren
id|sht-&gt;max_sectors
)paren
id|shost-&gt;max_sectors
op_assign
id|sht-&gt;max_sectors
suffix:semicolon
r_else
id|shost-&gt;max_sectors
op_assign
id|SCSI_DEFAULT_MAX_SECTORS
suffix:semicolon
multiline_comment|/*&n;&t; * assume a 4GB boundary, if not set&n;&t; */
r_if
c_cond
(paren
id|sht-&gt;dma_boundary
)paren
id|shost-&gt;dma_boundary
op_assign
id|sht-&gt;dma_boundary
suffix:semicolon
r_else
id|shost-&gt;dma_boundary
op_assign
l_int|0xffffffff
suffix:semicolon
id|rval
op_assign
id|scsi_setup_command_freelist
c_func
(paren
id|shost
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rval
)paren
r_goto
id|fail_kfree
suffix:semicolon
id|device_initialize
c_func
(paren
op_amp
id|shost-&gt;shost_gendev
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|shost-&gt;shost_gendev.bus_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;host%d&quot;
comma
id|shost-&gt;host_no
)paren
suffix:semicolon
id|shost-&gt;shost_gendev.release
op_assign
id|scsi_host_dev_release
suffix:semicolon
id|class_device_initialize
c_func
(paren
op_amp
id|shost-&gt;shost_classdev
)paren
suffix:semicolon
id|shost-&gt;shost_classdev.dev
op_assign
op_amp
id|shost-&gt;shost_gendev
suffix:semicolon
id|shost-&gt;shost_classdev
dot
r_class
op_assign
op_amp
id|shost_class
suffix:semicolon
id|snprintf
c_func
(paren
id|shost-&gt;shost_classdev.class_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;host%d&quot;
comma
id|shost-&gt;host_no
)paren
suffix:semicolon
id|shost-&gt;eh_notify
op_assign
op_amp
id|complete
suffix:semicolon
id|rval
op_assign
id|kernel_thread
c_func
(paren
id|scsi_error_handler
comma
id|shost
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rval
OL
l_int|0
)paren
r_goto
id|fail_destroy_freelist
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|complete
)paren
suffix:semicolon
id|shost-&gt;eh_notify
op_assign
l_int|NULL
suffix:semicolon
id|scsi_proc_hostdir_add
c_func
(paren
id|shost-&gt;hostt
)paren
suffix:semicolon
r_return
id|shost
suffix:semicolon
id|fail_destroy_freelist
suffix:colon
id|scsi_destroy_command_freelist
c_func
(paren
id|shost
)paren
suffix:semicolon
id|fail_kfree
suffix:colon
id|kfree
c_func
(paren
id|shost
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|scsi_host_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_host_alloc
)paren
suffix:semicolon
DECL|function|scsi_register
r_struct
id|Scsi_Host
op_star
id|scsi_register
c_func
(paren
r_struct
id|scsi_host_template
op_star
id|sht
comma
r_int
id|privsize
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|shost
op_assign
id|scsi_host_alloc
c_func
(paren
id|sht
comma
id|privsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sht-&gt;detect
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;scsi_register() called on new-style &quot;
l_string|&quot;template for driver %s&bslash;n&quot;
comma
id|sht-&gt;name
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|shost
)paren
id|list_add_tail
c_func
(paren
op_amp
id|shost-&gt;sht_legacy_list
comma
op_amp
id|sht-&gt;legacy_hosts
)paren
suffix:semicolon
r_return
id|shost
suffix:semicolon
)brace
DECL|variable|scsi_register
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_register
)paren
suffix:semicolon
DECL|function|scsi_unregister
r_void
id|scsi_unregister
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|shost-&gt;sht_legacy_list
)paren
suffix:semicolon
id|scsi_host_put
c_func
(paren
id|shost
)paren
suffix:semicolon
)brace
DECL|variable|scsi_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_unregister
)paren
suffix:semicolon
multiline_comment|/**&n; * scsi_host_lookup - get a reference to a Scsi_Host by host no&n; *&n; * @hostnum:&t;host number to locate&n; *&n; * Return value:&n; *&t;A pointer to located Scsi_Host or NULL.&n; **/
DECL|function|scsi_host_lookup
r_struct
id|Scsi_Host
op_star
id|scsi_host_lookup
c_func
(paren
r_int
r_int
id|hostnum
)paren
(brace
r_struct
r_class
op_star
r_class
op_assign
op_amp
id|shost_class
suffix:semicolon
r_struct
id|class_device
op_star
id|cdev
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|shost
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|ENXIO
)paren
comma
op_star
id|p
suffix:semicolon
id|down_read
c_func
(paren
op_amp
r_class
op_member_access_from_pointer
id|subsys.rwsem
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|cdev
comma
op_amp
r_class
op_member_access_from_pointer
id|children
comma
id|node
)paren
(brace
id|p
op_assign
id|class_to_shost
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;host_no
op_eq
id|hostnum
)paren
(brace
id|shost
op_assign
id|scsi_host_get
c_func
(paren
id|p
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|up_read
c_func
(paren
op_amp
r_class
op_member_access_from_pointer
id|subsys.rwsem
)paren
suffix:semicolon
r_return
id|shost
suffix:semicolon
)brace
DECL|variable|scsi_host_lookup
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_host_lookup
)paren
suffix:semicolon
multiline_comment|/**&n; * scsi_host_get - inc a Scsi_Host ref count&n; * @shost:&t;Pointer to Scsi_Host to inc.&n; **/
DECL|function|scsi_host_get
r_struct
id|Scsi_Host
op_star
id|scsi_host_get
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|SHOST_DEL
comma
op_amp
id|shost-&gt;shost_state
)paren
op_logical_or
op_logical_neg
id|get_device
c_func
(paren
op_amp
id|shost-&gt;shost_gendev
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|shost
suffix:semicolon
)brace
DECL|variable|scsi_host_get
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_host_get
)paren
suffix:semicolon
multiline_comment|/**&n; * scsi_host_put - dec a Scsi_Host ref count&n; * @shost:&t;Pointer to Scsi_Host to dec.&n; **/
DECL|function|scsi_host_put
r_void
id|scsi_host_put
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
id|put_device
c_func
(paren
op_amp
id|shost-&gt;shost_gendev
)paren
suffix:semicolon
)brace
DECL|variable|scsi_host_put
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_host_put
)paren
suffix:semicolon
DECL|function|scsi_init_hosts
r_int
id|scsi_init_hosts
c_func
(paren
r_void
)paren
(brace
r_return
id|class_register
c_func
(paren
op_amp
id|shost_class
)paren
suffix:semicolon
)brace
DECL|function|scsi_exit_hosts
r_void
id|scsi_exit_hosts
c_func
(paren
r_void
)paren
(brace
id|class_unregister
c_func
(paren
op_amp
id|shost_class
)paren
suffix:semicolon
)brace
DECL|function|scsi_is_host_device
r_int
id|scsi_is_host_device
c_func
(paren
r_const
r_struct
id|device
op_star
id|dev
)paren
(brace
r_return
id|dev-&gt;release
op_eq
id|scsi_host_dev_release
suffix:semicolon
)brace
DECL|variable|scsi_is_host_device
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_is_host_device
)paren
suffix:semicolon
multiline_comment|/**&n; * scsi_queue_work - Queue work to the Scsi_Host workqueue.&n; * @shost:&t;Pointer to Scsi_Host.&n; * @work:&t;Work to queue for execution.&n; *&n; * Return value:&n; * &t;0 on success / != 0 for error&n; **/
DECL|function|scsi_queue_work
r_int
id|scsi_queue_work
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
comma
r_struct
id|work_struct
op_star
id|work
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|shost-&gt;work_q
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ERROR: Scsi host &squot;%s&squot; attempted to queue scsi-work, &quot;
l_string|&quot;when no workqueue created.&bslash;n&quot;
comma
id|shost-&gt;hostt-&gt;name
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|queue_work
c_func
(paren
id|shost-&gt;work_q
comma
id|work
)paren
suffix:semicolon
)brace
DECL|variable|scsi_queue_work
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|scsi_queue_work
)paren
suffix:semicolon
multiline_comment|/**&n; * scsi_flush_work - Flush a Scsi_Host&squot;s workqueue.&n; * @shost:&t;Pointer to Scsi_Host.&n; **/
DECL|function|scsi_flush_work
r_void
id|scsi_flush_work
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|shost-&gt;work_q
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ERROR: Scsi host &squot;%s&squot; attempted to flush scsi-work, &quot;
l_string|&quot;when no workqueue created.&bslash;n&quot;
comma
id|shost-&gt;hostt-&gt;name
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|flush_workqueue
c_func
(paren
id|shost-&gt;work_q
)paren
suffix:semicolon
)brace
DECL|variable|scsi_flush_work
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|scsi_flush_work
)paren
suffix:semicolon
eof
