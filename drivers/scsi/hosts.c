multiline_comment|/*&n; *  hosts.c Copyright (C) 1992 Drew Eckhardt&n; *          Copyright (C) 1993, 1994, 1995 Eric Youngdale&n; *&n; *  mid to lowlevel SCSI driver interface&n; *      Initial versions: Drew Eckhardt&n; *      Subsequent revisions: Eric Youngdale&n; *&n; *  &lt;drew@colorado.edu&gt;&n; *&n; *  Jiffies wrap fixes (host-&gt;resetting), 3 Dec 1998 Andrea Arcangeli&n; *  Added QLOGIC QLA1280 SCSI controller kernel host support. &n; *     August 4, 1999 Fred Lewis, Intel DuPont&n; *&n; *  Updated to reflect the new initialization scheme for the higher &n; *  level of scsi drivers (sd/sr/st)&n; *  September 17, 2000 Torben Mathiasen &lt;tmm@image.dk&gt;&n; *&n; *  Restructured scsi_host lists and associated functions.&n; *  September 04, 2002 Mike Anderson (andmike@us.ibm.com)&n; */
multiline_comment|/*&n; *  This file contains the medium level SCSI&n; *  host interface initialization, as well as the scsi_hosts list of SCSI&n; *  hosts currently present in the system.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;scsi_priv.h&quot;
macro_line|#include &quot;scsi_logging.h&quot;
r_static
id|LIST_HEAD
c_func
(paren
id|scsi_host_list
)paren
suffix:semicolon
DECL|variable|scsi_host_list_lock
r_static
id|spinlock_t
id|scsi_host_list_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|scsi_host_next_hn
r_static
r_int
id|scsi_host_next_hn
suffix:semicolon
multiline_comment|/* host_no for next new host */
DECL|variable|scsihosts
r_static
r_char
op_star
id|scsihosts
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|scsihosts
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|scsihosts
comma
l_string|&quot;scsihosts=driver1,driver2,driver3&quot;
)paren
suffix:semicolon
macro_line|#ifndef MODULE
DECL|function|scsi_setup
r_int
id|__init
id|scsi_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|scsihosts
op_assign
id|str
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;scsihosts=&quot;
comma
id|scsi_setup
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/**&n;  * scsi_find_host_by_num - get a Scsi_Host by host no&n;  *&n;  * @host_no:&t;host number to locate&n;  *&n;  * Return value:&n;  *&t;A pointer to located Scsi_Host or NULL.&n;  **/
DECL|function|scsi_find_host_by_num
r_static
r_struct
id|Scsi_Host
op_star
id|scsi_find_host_by_num
c_func
(paren
r_int
r_int
id|host_no
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|shost
comma
op_star
id|shost_found
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|scsi_host_list_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|shost
comma
op_amp
id|scsi_host_list
comma
id|sh_list
)paren
(brace
r_if
c_cond
(paren
id|shost-&gt;host_no
OG
id|host_no
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * The list is sorted.&n;&t;&t;&t; */
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|shost-&gt;host_no
op_eq
id|host_no
)paren
(brace
id|shost_found
op_assign
id|shost
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|scsi_host_list_lock
)paren
suffix:semicolon
r_return
id|shost_found
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_alloc_hostnum - choose new SCSI host number based on host name.&n; * @name:&t;String to store in name field&n; *&n; * Return value:&n; *&t;Pointer to a new Scsi_Host_Name&n; **/
DECL|function|scsi_alloc_host_num
r_static
r_int
id|scsi_alloc_host_num
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_int
id|hostnum
suffix:semicolon
r_int
id|namelen
suffix:semicolon
r_const
r_char
op_star
id|start
comma
op_star
id|end
suffix:semicolon
r_if
c_cond
(paren
id|name
)paren
(brace
id|hostnum
op_assign
l_int|0
suffix:semicolon
id|namelen
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
id|start
op_assign
id|scsihosts
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|hostlen
suffix:semicolon
r_if
c_cond
(paren
id|start
op_logical_and
id|start
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|end
op_assign
id|strpbrk
c_func
(paren
id|start
comma
l_string|&quot;,:&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end
)paren
(brace
id|hostlen
op_assign
(paren
id|end
op_minus
id|start
)paren
suffix:semicolon
id|end
op_increment
suffix:semicolon
)brace
r_else
id|hostlen
op_assign
id|strlen
c_func
(paren
id|start
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Look for a match on the scsihosts list.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|hostlen
op_eq
id|namelen
)paren
op_logical_and
(paren
id|strncmp
c_func
(paren
id|name
comma
id|start
comma
id|hostlen
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
op_logical_neg
id|scsi_find_host_by_num
c_func
(paren
id|hostnum
)paren
)paren
)paren
r_return
id|hostnum
suffix:semicolon
id|start
op_assign
id|end
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Look for any unused numbers.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|scsi_find_host_by_num
c_func
(paren
id|hostnum
)paren
)paren
r_return
id|hostnum
suffix:semicolon
)brace
id|hostnum
op_increment
suffix:semicolon
)brace
)brace
r_else
r_return
id|scsi_host_next_hn
op_increment
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_tp_for_each_host - call function for each scsi host off a template&n; * @shost_tp:&t;a pointer to a scsi host template&n; * @callback:&t;a pointer to callback function&n; *&n; * Return value:&n; * &t;0 on Success / 1 on Failure&n; **/
DECL|function|scsi_tp_for_each_host
r_int
id|scsi_tp_for_each_host
c_func
(paren
id|Scsi_Host_Template
op_star
id|shost_tp
comma
r_int
(paren
op_star
id|callback
)paren
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
)paren
(brace
r_struct
id|list_head
op_star
id|lh
comma
op_star
id|lh_sf
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|shost
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|scsi_host_list_lock
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|lh
comma
id|lh_sf
comma
op_amp
id|scsi_host_list
)paren
(brace
id|shost
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|Scsi_Host
comma
id|sh_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shost-&gt;hostt
op_eq
id|shost_tp
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|scsi_host_list_lock
)paren
suffix:semicolon
id|callback
c_func
(paren
id|shost
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|scsi_host_list_lock
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|scsi_host_list_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_host_legacy_release - default release function for hosts&n; * @shost: &n; * &n; * Description:&n; * &t;This is the default case for the release function.  Its completely&n; *&t;useless for anything but old ISA adapters&n; **/
DECL|function|scsi_host_legacy_release
r_static
r_int
id|scsi_host_legacy_release
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
id|shost-&gt;irq
)paren
id|free_irq
c_func
(paren
id|shost-&gt;irq
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_GENERIC_ISA_DMA
r_if
c_cond
(paren
id|shost-&gt;dma_channel
op_ne
l_int|0xff
)paren
id|free_dma
c_func
(paren
id|shost-&gt;dma_channel
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|shost-&gt;io_port
op_logical_and
id|shost-&gt;n_io_port
)paren
id|release_region
c_func
(paren
id|shost-&gt;io_port
comma
id|shost-&gt;n_io_port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|Scsi_Host_Template
op_star
id|sht
op_assign
id|shost-&gt;hostt
suffix:semicolon
r_struct
id|scsi_device
op_star
id|sdev
suffix:semicolon
r_int
id|error
op_assign
l_int|0
comma
id|saved_error
op_assign
l_int|0
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
id|error
)paren
r_return
id|error
suffix:semicolon
id|scsi_proc_host_add
c_func
(paren
id|shost
)paren
suffix:semicolon
id|scsi_scan_host
c_func
(paren
id|shost
)paren
suffix:semicolon
id|list_for_each_entry
(paren
id|sdev
comma
op_amp
id|shost-&gt;my_devices
comma
id|siblings
)paren
(brace
id|error
op_assign
id|scsi_attach_device
c_func
(paren
id|sdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|saved_error
op_assign
id|error
suffix:semicolon
)brace
r_return
id|saved_error
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_unregister - unregister a scsi host&n; * @shost:&t;scsi host to be unregistered&n; **/
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
id|scsi_host_put
c_func
(paren
id|shost
)paren
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
multiline_comment|/* Remove shost from scsi_host_list */
id|spin_lock
c_func
(paren
op_amp
id|scsi_host_list_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|shost-&gt;sh_list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|scsi_host_list_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Next, kill the kernel error recovery thread for this host.&n;&t; */
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
multiline_comment|/**&n; * scsi_register - register a scsi host adapter instance.&n; * @shost_tp:&t;pointer to scsi host template&n; * @xtr_bytes:&t;extra bytes to allocate for driver&n; *&n; * Note:&n; * &t;We call this when we come across a new host adapter. We only do&n; * &t;this once we are 100% sure that we want to use this host adapter -&n; * &t;it is a pain to reverse this, so we try to avoid it &n; *&n; * Return value:&n; * &t;Pointer to a new Scsi_Host&n; **/
r_extern
r_int
id|blk_nohighio
suffix:semicolon
DECL|function|scsi_register
r_struct
id|Scsi_Host
op_star
id|scsi_register
c_func
(paren
id|Scsi_Host_Template
op_star
id|shost_tp
comma
r_int
id|xtr_bytes
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|shost
comma
op_star
id|shost_scr
suffix:semicolon
r_int
id|gfp_mask
comma
id|rval
suffix:semicolon
id|DECLARE_COMPLETION
c_func
(paren
id|sem
)paren
suffix:semicolon
multiline_comment|/* Check to see if this host has any error handling facilities */
r_if
c_cond
(paren
id|shost_tp-&gt;eh_strategy_handler
op_eq
l_int|NULL
op_logical_and
id|shost_tp-&gt;eh_abort_handler
op_eq
l_int|NULL
op_logical_and
id|shost_tp-&gt;eh_device_reset_handler
op_eq
l_int|NULL
op_logical_and
id|shost_tp-&gt;eh_bus_reset_handler
op_eq
l_int|NULL
op_logical_and
id|shost_tp-&gt;eh_host_reset_handler
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ERROR: SCSI host `%s&squot; has no error handling&bslash;nERROR: This is not a safe way to run your SCSI host&bslash;nERROR: The error handling must be added to this driver&bslash;n&quot;
comma
id|shost_tp-&gt;proc_name
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
)brace
id|gfp_mask
op_assign
id|GFP_KERNEL
suffix:semicolon
r_if
c_cond
(paren
id|shost_tp-&gt;unchecked_isa_dma
op_logical_and
id|xtr_bytes
)paren
id|gfp_mask
op_or_assign
id|__GFP_DMA
suffix:semicolon
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
id|xtr_bytes
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
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: out of memory.&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
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
id|xtr_bytes
)paren
suffix:semicolon
id|shost-&gt;host_no
op_assign
id|scsi_alloc_host_num
c_func
(paren
id|shost_tp-&gt;proc_name
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
id|shost_tp
suffix:semicolon
id|shost-&gt;host_blocked
op_assign
l_int|0
suffix:semicolon
id|shost-&gt;host_self_blocked
op_assign
id|FALSE
suffix:semicolon
id|shost-&gt;max_host_blocked
op_assign
id|shost_tp-&gt;max_host_blocked
ques
c_cond
id|shost_tp-&gt;max_host_blocked
suffix:colon
id|SCSI_DEFAULT_HOST_BLOCKED
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: %x %x: %d&bslash;n&quot;
comma
id|__FUNCTION_
(paren
r_int
)paren
id|shost
comma
(paren
r_int
)paren
id|shost-&gt;hostt
comma
id|xtr_bytes
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * The next six are the default values which can be overridden if&n;&t; * need be&n;&t; */
id|shost-&gt;this_id
op_assign
id|shost_tp-&gt;this_id
suffix:semicolon
id|shost-&gt;can_queue
op_assign
id|shost_tp-&gt;can_queue
suffix:semicolon
id|shost-&gt;sg_tablesize
op_assign
id|shost_tp-&gt;sg_tablesize
suffix:semicolon
id|shost-&gt;cmd_per_lun
op_assign
id|shost_tp-&gt;cmd_per_lun
suffix:semicolon
id|shost-&gt;unchecked_isa_dma
op_assign
id|shost_tp-&gt;unchecked_isa_dma
suffix:semicolon
id|shost-&gt;use_clustering
op_assign
id|shost_tp-&gt;use_clustering
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|blk_nohighio
)paren
id|shost-&gt;highmem_io
op_assign
id|shost_tp-&gt;highmem_io
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shost_tp-&gt;max_sectors
)paren
(brace
multiline_comment|/*&n;&t;&t; * Driver imposes no hard sector transfer limit.&n;&t;&t; * start at machine infinity initially.&n;&t;&t; */
id|shost-&gt;max_sectors
op_assign
id|SCSI_DEFAULT_MAX_SECTORS
suffix:semicolon
)brace
r_else
id|shost-&gt;max_sectors
op_assign
id|shost_tp-&gt;max_sectors
suffix:semicolon
id|shost-&gt;use_blk_tcq
op_assign
id|shost_tp-&gt;use_blk_tcq
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|scsi_host_list_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * FIXME When device naming is complete remove this step that&n;&t; * orders the scsi_host_list by host number and just do a&n;&t; * list_add_tail.&n;&t; */
id|list_for_each_entry
c_func
(paren
id|shost_scr
comma
op_amp
id|scsi_host_list
comma
id|sh_list
)paren
(brace
r_if
c_cond
(paren
id|shost-&gt;host_no
OL
id|shost_scr-&gt;host_no
)paren
(brace
id|__list_add
c_func
(paren
op_amp
id|shost-&gt;sh_list
comma
id|shost_scr-&gt;sh_list.prev
comma
op_amp
id|shost_scr-&gt;sh_list
)paren
suffix:semicolon
r_goto
id|found
suffix:semicolon
)brace
)brace
id|list_add_tail
c_func
(paren
op_amp
id|shost-&gt;sh_list
comma
op_amp
id|scsi_host_list
)paren
suffix:semicolon
id|found
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|scsi_host_list_lock
)paren
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
id|sem
suffix:semicolon
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
(paren
r_void
op_star
)paren
id|shost
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now wait for the kernel error thread to initialize itself&n;&t; * as it might be needed when we scan the bus.&n;&t; */
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
id|shost-&gt;hostt-&gt;present
op_increment
suffix:semicolon
r_return
id|shost
suffix:semicolon
id|fail
suffix:colon
id|spin_lock
c_func
(paren
op_amp
id|scsi_host_list_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|shost-&gt;sh_list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|scsi_host_list_lock
)paren
suffix:semicolon
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
multiline_comment|/**&n; * scsi_register_host - register a low level host driver&n; * @shost_tp:&t;pointer to a scsi host driver template&n; *&n; * Return value:&n; * &t;0 on Success / 1 on Failure.&n; **/
DECL|function|scsi_register_host
r_int
id|scsi_register_host
c_func
(paren
id|Scsi_Host_Template
op_star
id|shost_tp
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|shost
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|shost_tp-&gt;detect
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shost_tp-&gt;release
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;scsi HBA driver %s didn&squot;t set a release method, &quot;
l_string|&quot;please fix the template&bslash;n&quot;
comma
id|shost_tp-&gt;name
)paren
suffix:semicolon
id|shost_tp-&gt;release
op_assign
op_amp
id|scsi_host_legacy_release
suffix:semicolon
)brace
id|shost_tp
op_member_access_from_pointer
id|detect
c_func
(paren
id|shost_tp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shost_tp-&gt;present
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * XXX(hch) use scsi_tp_for_each_host() once it propagates&n;&t; *&t;    error returns properly.&n;&t; */
id|list_for_each_entry
c_func
(paren
id|shost
comma
op_amp
id|scsi_host_list
comma
id|sh_list
)paren
r_if
c_cond
(paren
id|shost-&gt;hostt
op_eq
id|shost_tp
)paren
r_if
c_cond
(paren
id|scsi_add_host
c_func
(paren
id|shost
comma
l_int|NULL
)paren
)paren
r_goto
id|out_of_space
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_of_space
suffix:colon
id|scsi_unregister_host
c_func
(paren
id|shost_tp
)paren
suffix:semicolon
multiline_comment|/* easiest way to clean up?? */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_unregister_host - unregister a low level host adapter driver&n; * @shost_tp:&t;scsi host template to unregister.&n; *&n; * Description:&n; * &t;Similarly, this entry point should be called by a loadable module&n; * &t;if it is trying to remove a low level scsi driver from the system.&n; *&n; * Return value:&n; * &t;0 on Success / 1 on Failure&n; *&n; * Notes:&n; * &t;rmmod does not care what we return here the module will be&n; * &t;removed.&n; **/
DECL|function|scsi_unregister_host
r_int
id|scsi_unregister_host
c_func
(paren
id|Scsi_Host_Template
op_star
id|shost_tp
)paren
(brace
id|scsi_tp_for_each_host
c_func
(paren
id|shost_tp
comma
id|scsi_remove_host
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * *scsi_host_get_next - get scsi host and inc ref count&n; * @shost:&t;pointer to a Scsi_Host or NULL to start.&n; *&n; * Return value:&n; * &t;A pointer to next Scsi_Host in list or NULL.&n; **/
DECL|function|scsi_host_get_next
r_struct
id|Scsi_Host
op_star
id|scsi_host_get_next
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
r_struct
id|list_head
op_star
id|lh
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|scsi_host_list_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shost
)paren
(brace
multiline_comment|/* XXX Dec ref on cur shost */
id|lh
op_assign
id|shost-&gt;sh_list.next
suffix:semicolon
)brace
r_else
(brace
id|lh
op_assign
id|scsi_host_list.next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lh
op_eq
op_amp
id|scsi_host_list
)paren
(brace
id|shost
op_assign
(paren
r_struct
id|Scsi_Host
op_star
)paren
l_int|NULL
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|shost
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|Scsi_Host
comma
id|sh_list
)paren
suffix:semicolon
multiline_comment|/* XXX Inc ref count */
id|done
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|scsi_host_list_lock
)paren
suffix:semicolon
r_return
id|shost
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_host_hn_get - get a Scsi_Host by host no and inc ref count&n; * @host_no:&t;host number to locate&n; *&n; * Return value:&n; * &t;A pointer to located Scsi_Host or NULL.&n; **/
DECL|function|scsi_host_hn_get
r_struct
id|Scsi_Host
op_star
id|scsi_host_hn_get
c_func
(paren
r_int
r_int
id|host_no
)paren
(brace
multiline_comment|/* XXX Inc ref count */
r_return
id|scsi_find_host_by_num
c_func
(paren
id|host_no
)paren
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
id|shost-&gt;host_gendev
)paren
suffix:semicolon
id|class_device_get
c_func
(paren
op_amp
id|shost-&gt;class_dev
)paren
suffix:semicolon
r_return
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
id|shost-&gt;class_dev
)paren
suffix:semicolon
id|put_device
c_func
(paren
op_amp
id|shost-&gt;host_gendev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_host_init - set up the scsi host number list based on any entries&n; * scsihosts.&n; **/
DECL|function|scsi_host_init
r_void
id|__init
id|scsi_host_init
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|shost_hn
suffix:semicolon
id|shost_hn
op_assign
id|scsihosts
suffix:semicolon
r_while
c_loop
(paren
id|shost_hn
)paren
(brace
id|scsi_host_next_hn
op_increment
suffix:semicolon
id|shost_hn
op_assign
id|strpbrk
c_func
(paren
id|shost_hn
comma
l_string|&quot;:,&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shost_hn
)paren
id|shost_hn
op_increment
suffix:semicolon
)brace
)brace
DECL|function|scsi_host_busy_inc
r_void
id|scsi_host_busy_inc
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
comma
id|Scsi_Device
op_star
id|sdev
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
id|shost-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
id|shost-&gt;host_busy
op_increment
suffix:semicolon
id|sdev-&gt;device_busy
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|shost-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|scsi_host_busy_dec_and_test
r_void
id|scsi_host_busy_dec_and_test
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
comma
id|Scsi_Device
op_star
id|sdev
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
id|shost-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
id|shost-&gt;host_busy
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|shost-&gt;in_recovery
op_logical_and
id|shost-&gt;host_failed
op_logical_and
(paren
id|shost-&gt;host_busy
op_eq
id|shost-&gt;host_failed
)paren
)paren
(brace
id|up
c_func
(paren
id|shost-&gt;eh_wait
)paren
suffix:semicolon
id|SCSI_LOG_ERROR_RECOVERY
c_func
(paren
l_int|5
comma
id|printk
c_func
(paren
l_string|&quot;Waking error handler&quot;
l_string|&quot; thread&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
id|shost-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
)brace
eof
