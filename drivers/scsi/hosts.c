multiline_comment|/*&n; *  hosts.c Copyright (C) 1992 Drew Eckhardt&n; *          Copyright (C) 1993, 1994, 1995 Eric Youngdale&n; *&n; *  mid to lowlevel SCSI driver interface&n; *      Initial versions: Drew Eckhardt&n; *      Subsequent revisions: Eric Youngdale&n; *&n; *  &lt;drew@colorado.edu&gt;&n; *&n; *  Jiffies wrap fixes (host-&gt;resetting), 3 Dec 1998 Andrea Arcangeli&n; *  Added QLOGIC QLA1280 SCSI controller kernel host support. &n; *     August 4, 1999 Fred Lewis, Intel DuPont&n; *&n; *  Updated to reflect the new initialization scheme for the higher &n; *  level of scsi drivers (sd/sr/st)&n; *  September 17, 2000 Torben Mathiasen &lt;tmm@image.dk&gt;&n; *&n; *  Restructured scsi_host lists and associated functions.&n; *  September 04, 2002 Mike Anderson (andmike@us.ibm.com)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;scsi_priv.h&quot;
macro_line|#include &quot;scsi_logging.h&quot;
DECL|variable|scsi_host_next_hn
r_static
r_int
id|scsi_host_next_hn
suffix:semicolon
multiline_comment|/* host_no for next new host */
multiline_comment|/**&n; * scsi_remove_host - check a scsi host for release and release&n; * @shost:&t;a pointer to a scsi host to release&n; *&n; * Return value:&n; * &t;0 on Success / 1 on Failure&n; **/
DECL|function|scsi_remove_host
r_int
id|scsi_remove_host
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
r_struct
id|scsi_device
op_star
id|sdev
suffix:semicolon
multiline_comment|/*&n;&t; * FIXME Do ref counting.  We force all of the devices offline to&n;&t; * help prevent race conditions where other hosts/processors could&n;&t; * try and get in and queue a command.&n;&t; */
id|list_for_each_entry
c_func
(paren
id|sdev
comma
op_amp
id|shost-&gt;my_devices
comma
id|siblings
)paren
id|sdev-&gt;online
op_assign
id|FALSE
suffix:semicolon
id|scsi_proc_host_rm
c_func
(paren
id|shost
)paren
suffix:semicolon
id|scsi_forget_host
c_func
(paren
id|shost
)paren
suffix:semicolon
id|scsi_sysfs_remove_host
c_func
(paren
id|shost
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
id|error
op_assign
id|scsi_sysfs_add_host
c_func
(paren
id|shost
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|scsi_proc_host_add
c_func
(paren
id|shost
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_free_sdev - free a scsi hosts resources&n; * @shost:&t;scsi host to free &n; **/
DECL|function|scsi_free_shost
r_void
id|scsi_free_shost
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
id|shost-&gt;hostt-&gt;present
op_decrement
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
id|shost-&gt;my_devices
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
id|shost-&gt;use_blk_tcq
op_assign
id|sht-&gt;use_blk_tcq
suffix:semicolon
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
id|fail
suffix:semicolon
id|scsi_sysfs_init_host
c_func
(paren
id|shost
)paren
suffix:semicolon
id|shost-&gt;eh_notify
op_assign
op_amp
id|complete
suffix:semicolon
multiline_comment|/* XXX(hch): handle error return */
id|kernel_thread
c_func
(paren
(paren
r_int
(paren
op_star
)paren
(paren
r_void
op_star
)paren
)paren
id|scsi_error_handler
comma
id|shost
comma
l_int|0
)paren
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
id|shost-&gt;hostt-&gt;present
op_increment
suffix:semicolon
r_return
id|shost
suffix:semicolon
id|fail
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
id|class_get
c_func
(paren
op_amp
id|shost_class
)paren
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
l_int|NULL
comma
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
r_class
)paren
(brace
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
id|scsi_host_get
c_func
(paren
id|p
)paren
suffix:semicolon
id|shost
op_assign
id|p
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
)brace
r_return
id|shost
suffix:semicolon
)brace
multiline_comment|/**&n; * *scsi_host_get - inc a Scsi_Host ref count&n; * @shost:&t;Pointer to Scsi_Host to inc.&n; **/
DECL|function|scsi_host_get
r_void
id|scsi_host_get
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
id|get_device
c_func
(paren
op_amp
id|shost-&gt;shost_gendev
)paren
suffix:semicolon
id|class_device_get
c_func
(paren
op_amp
id|shost-&gt;shost_classdev
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * *scsi_host_put - dec a Scsi_Host ref count&n; * @shost:&t;Pointer to Scsi_Host to dec.&n; **/
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
id|class_device_put
c_func
(paren
op_amp
id|shost-&gt;shost_classdev
)paren
suffix:semicolon
id|put_device
c_func
(paren
op_amp
id|shost-&gt;shost_gendev
)paren
suffix:semicolon
)brace
eof
