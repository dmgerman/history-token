multiline_comment|/*&n; *  hosts.c Copyright (C) 1992 Drew Eckhardt&n; *          Copyright (C) 1993, 1994, 1995 Eric Youngdale&n; *&n; *  mid to lowlevel SCSI driver interface&n; *      Initial versions: Drew Eckhardt&n; *      Subsequent revisions: Eric Youngdale&n; *&n; *  &lt;drew@colorado.edu&gt;&n; *&n; *  Jiffies wrap fixes (host-&gt;resetting), 3 Dec 1998 Andrea Arcangeli&n; *  Added QLOGIC QLA1280 SCSI controller kernel host support. &n; *     August 4, 1999 Fred Lewis, Intel DuPont&n; *&n; *  Updated to reflect the new initialization scheme for the higher &n; *  level of scsi drivers (sd/sr/st)&n; *  September 17, 2000 Torben Mathiasen &lt;tmm@image.dk&gt;&n; *&n; *  Restructured scsi_host lists and associated functions.&n; *  September 04, 2002 Mike Anderson (andmike@us.ibm.com)&n; */
multiline_comment|/*&n; *  This file contains the medium level SCSI&n; *  host interface initialization, as well as the scsi_hosts list of SCSI&n; *  hosts currently present in the system.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
DECL|variable|scsi_host_tmpl_list
id|LIST_HEAD
c_func
(paren
id|scsi_host_tmpl_list
)paren
suffix:semicolon
DECL|variable|scsi_host_hn_list
id|LIST_HEAD
c_func
(paren
id|scsi_host_hn_list
)paren
suffix:semicolon
DECL|variable|scsi_host_list
id|LIST_HEAD
c_func
(paren
id|scsi_host_list
)paren
suffix:semicolon
DECL|variable|scsi_host_list_lock
id|spinlock_t
id|scsi_host_list_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|scsi_devicelist
r_struct
id|Scsi_Device_Template
op_star
id|scsi_devicelist
suffix:semicolon
DECL|variable|scsi_host_next_hn
r_static
r_int
id|scsi_host_next_hn
suffix:semicolon
multiline_comment|/* host_no for next new host */
DECL|variable|scsi_hosts_registered
r_static
r_int
id|scsi_hosts_registered
suffix:semicolon
multiline_comment|/* cnt of registered scsi hosts */
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
multiline_comment|/**&n; * scsi_host_generic_release - default release function for hosts&n; * @shost: &n; * &n; * Description:&n; * &t;This is the default case for the release function.  Its completely&n; *&t;useless for anything but old ISA adapters&n; **/
DECL|function|scsi_host_generic_release
r_static
r_void
id|scsi_host_generic_release
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
)brace
multiline_comment|/**&n; * scsi_host_chk_and_release - check a scsi host for release and release&n; * @shost:&t;a pointer to a scsi host to release&n; *&n; * Return value:&n; * &t;0 on Success / 1 on Failure&n; **/
DECL|function|scsi_host_chk_and_release
r_int
id|scsi_host_chk_and_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
r_int
id|pcount
suffix:semicolon
id|Scsi_Device
op_star
id|sdev
suffix:semicolon
r_struct
id|Scsi_Device_Template
op_star
id|sdev_tp
suffix:semicolon
id|Scsi_Cmnd
op_star
id|scmd
suffix:semicolon
multiline_comment|/*&n;&t; * Current policy is all shosts go away on unregister.&n;&t; */
r_if
c_cond
(paren
id|shost-&gt;hostt-&gt;module
op_logical_and
id|GET_USE_COUNT
c_func
(paren
id|shost-&gt;hostt-&gt;module
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * FIXME Do ref counting.  We force all of the devices offline to&n;&t; * help prevent race conditions where other hosts/processors could&n;&t; * try and get in and queue a command.&n;&t; */
r_for
c_loop
(paren
id|sdev
op_assign
id|shost-&gt;host_queue
suffix:semicolon
id|sdev
suffix:semicolon
id|sdev
op_assign
id|sdev-&gt;next
)paren
id|sdev-&gt;online
op_assign
id|FALSE
suffix:semicolon
r_for
c_loop
(paren
id|sdev
op_assign
id|shost-&gt;host_queue
suffix:semicolon
id|sdev
suffix:semicolon
id|sdev
op_assign
id|sdev-&gt;next
)paren
(brace
multiline_comment|/*&n;&t;&t; * Loop over all of the commands associated with the&n;&t;&t; * device.  If any of them are busy, then set the state&n;&t;&t; * back to inactive and bail.&n;&t;&t; */
r_for
c_loop
(paren
id|scmd
op_assign
id|sdev-&gt;device_queue
suffix:semicolon
id|scmd
suffix:semicolon
id|scmd
op_assign
id|scmd-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|scmd-&gt;request
op_logical_and
id|scmd-&gt;request-&gt;rq_status
op_ne
id|RQ_INACTIVE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SCSI device not inactive&quot;
l_string|&quot;- rq_status=%d, target=%d, pid=%ld,&quot;
l_string|&quot;state=%d, owner=%d.&bslash;n&quot;
comma
id|scmd-&gt;request-&gt;rq_status
comma
id|scmd-&gt;target
comma
id|scmd-&gt;pid
comma
id|scmd-&gt;state
comma
id|scmd-&gt;owner
)paren
suffix:semicolon
r_for
c_loop
(paren
id|sdev
op_assign
id|shost-&gt;host_queue
suffix:semicolon
id|sdev
suffix:semicolon
id|sdev
op_assign
id|sdev-&gt;next
)paren
(brace
r_for
c_loop
(paren
id|scmd
op_assign
id|sdev-&gt;device_queue
suffix:semicolon
id|scmd
suffix:semicolon
id|scmd
op_assign
id|scmd-&gt;next
)paren
r_if
c_cond
(paren
id|scmd-&gt;request-&gt;rq_status
op_eq
id|RQ_SCSI_DISCONNECTING
)paren
id|scmd-&gt;request-&gt;rq_status
op_assign
id|RQ_INACTIVE
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Device busy???&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * No, this device is really free.  Mark it as such, and&n;&t;&t;&t; * continue on.&n;&t;&t;&t; */
id|scmd-&gt;state
op_assign
id|SCSI_STATE_DISCONNECTING
suffix:semicolon
r_if
c_cond
(paren
id|scmd-&gt;request
)paren
id|scmd-&gt;request-&gt;rq_status
op_assign
id|RQ_SCSI_DISCONNECTING
suffix:semicolon
multiline_comment|/* Mark as&n;&t;&t;&t;&t;&t;&t;&t;&t;   busy */
)brace
)brace
multiline_comment|/*&n;&t; * Next we detach the high level drivers from the Scsi_Device&n;&t; * structures&n;&t; */
r_for
c_loop
(paren
id|sdev
op_assign
id|shost-&gt;host_queue
suffix:semicolon
id|sdev
suffix:semicolon
id|sdev
op_assign
id|sdev-&gt;next
)paren
(brace
r_for
c_loop
(paren
id|sdev_tp
op_assign
id|scsi_devicelist
suffix:semicolon
id|sdev_tp
suffix:semicolon
id|sdev_tp
op_assign
id|sdev_tp-&gt;next
)paren
r_if
c_cond
(paren
id|sdev_tp-&gt;detach
)paren
(paren
op_star
id|sdev_tp-&gt;detach
)paren
(paren
id|sdev
)paren
suffix:semicolon
multiline_comment|/* If something still attached, punt */
r_if
c_cond
(paren
id|sdev-&gt;attached
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Attached usage count = %d&bslash;n&quot;
comma
id|sdev-&gt;attached
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|shost-&gt;hostt-&gt;slave_detach
)paren
(paren
op_star
id|shost-&gt;hostt-&gt;slave_detach
)paren
(paren
id|sdev
)paren
suffix:semicolon
id|devfs_unregister
c_func
(paren
id|sdev-&gt;de
)paren
suffix:semicolon
id|device_unregister
c_func
(paren
op_amp
id|sdev-&gt;sdev_driverfs_dev
)paren
suffix:semicolon
)brace
multiline_comment|/* Next we free up the Scsi_Cmnd structures for this host */
r_for
c_loop
(paren
id|sdev
op_assign
id|shost-&gt;host_queue
suffix:semicolon
id|sdev
suffix:semicolon
id|sdev
op_assign
id|shost-&gt;host_queue
)paren
(brace
id|scsi_release_commandblocks
c_func
(paren
id|sdev
)paren
suffix:semicolon
id|blk_cleanup_queue
c_func
(paren
op_amp
id|sdev-&gt;request_queue
)paren
suffix:semicolon
multiline_comment|/* Next free up the Scsi_Device structures for this host */
id|shost-&gt;host_queue
op_assign
id|sdev-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|sdev-&gt;inquiry
)paren
id|kfree
c_func
(paren
id|sdev-&gt;inquiry
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sdev
)paren
suffix:semicolon
)brace
multiline_comment|/* Remove the instance of the individual hosts */
id|pcount
op_assign
id|scsi_hosts_registered
suffix:semicolon
r_if
c_cond
(paren
id|shost-&gt;hostt-&gt;release
)paren
(paren
op_star
id|shost-&gt;hostt-&gt;release
)paren
(paren
id|shost
)paren
suffix:semicolon
r_else
(brace
id|scsi_host_generic_release
c_func
(paren
id|shost
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pcount
op_eq
id|scsi_hosts_registered
)paren
id|scsi_unregister
c_func
(paren
id|shost
)paren
suffix:semicolon
r_return
l_int|0
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
r_struct
id|list_head
op_star
id|lh
suffix:semicolon
id|Scsi_Host_Name
op_star
id|shost_name
suffix:semicolon
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
multiline_comment|/* Unregister from scsi_host_hn_list */
id|list_for_each
c_func
(paren
id|lh
comma
op_amp
id|scsi_host_hn_list
)paren
(brace
id|shost_name
op_assign
id|list_entry
c_func
(paren
id|lh
comma
id|Scsi_Host_Name
comma
id|shn_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shost-&gt;host_no
op_eq
id|shost_name-&gt;host_no
)paren
id|shost_name-&gt;host_registered
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Next, kill the kernel error recovery thread for this host.&n;&t; */
r_if
c_cond
(paren
id|shost-&gt;ehandler
)paren
(brace
id|DECLARE_MUTEX_LOCKED
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
id|send_sig
c_func
(paren
id|SIGHUP
comma
id|shost-&gt;ehandler
comma
l_int|1
)paren
suffix:semicolon
id|down
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
id|scsi_hosts_registered
op_decrement
suffix:semicolon
id|shost-&gt;hostt-&gt;present
op_decrement
suffix:semicolon
multiline_comment|/* Cleanup proc and driverfs */
macro_line|#ifdef CONFIG_PROC_FS
id|scsi_proc_host_rm
c_func
(paren
id|shost
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shost-&gt;hostt-&gt;present
)paren
id|remove_proc_entry
c_func
(paren
id|shost-&gt;hostt-&gt;proc_name
comma
id|proc_scsi
)paren
suffix:semicolon
macro_line|#endif
id|device_unregister
c_func
(paren
op_amp
id|shost-&gt;host_driverfs_dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|shost
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_host_hn_add - allocate and add new Scsi_Host_Name&n; * @name:&t;String to store in name field&n; *&n; * Return value:&n; * &t;Pointer to a new Scsi_Host_Name&n; **/
DECL|function|scsi_host_hn_add
id|Scsi_Host_Name
op_star
id|scsi_host_hn_add
c_func
(paren
r_char
op_star
id|name
)paren
(brace
id|Scsi_Host_Name
op_star
id|shost_name
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
id|shost_name
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|shost_name
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shost_name
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: out of memory at line %d.&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|__LINE__
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|shost_name-&gt;name
op_assign
id|kmalloc
c_func
(paren
id|len
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shost_name-&gt;name
)paren
(brace
id|kfree
c_func
(paren
id|shost_name
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: out of memory at line %d.&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|__LINE__
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
)paren
id|strncpy
c_func
(paren
id|shost_name-&gt;name
comma
id|name
comma
id|len
)paren
suffix:semicolon
id|shost_name-&gt;name
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|shost_name-&gt;host_no
op_assign
id|scsi_host_next_hn
op_increment
suffix:semicolon
id|shost_name-&gt;host_registered
op_assign
l_int|0
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|shost_name-&gt;shn_list
comma
op_amp
id|scsi_host_hn_list
)paren
suffix:semicolon
r_return
id|shost_name
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
id|Scsi_Host_Name
op_star
id|shost_name
op_assign
l_int|NULL
suffix:semicolon
id|Scsi_Host_Name
op_star
id|shn
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|hname
suffix:semicolon
r_int
id|hname_len
suffix:semicolon
r_struct
id|list_head
op_star
id|lh
suffix:semicolon
r_int
id|gfp_mask
suffix:semicolon
id|DECLARE_MUTEX_LOCKED
c_func
(paren
id|sem
)paren
suffix:semicolon
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
multiline_comment|/*&n;&t; * Determine host number. Check reserved first before allocating&n;&t; * new one&n;&t; */
id|hname
op_assign
(paren
id|shost_tp-&gt;proc_name
)paren
ques
c_cond
id|shost_tp-&gt;proc_name
suffix:colon
l_string|&quot;&quot;
suffix:semicolon
id|hname_len
op_assign
id|strlen
c_func
(paren
id|hname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hname_len
)paren
id|list_for_each
c_func
(paren
id|lh
comma
op_amp
id|scsi_host_hn_list
)paren
(brace
id|shn
op_assign
id|list_entry
c_func
(paren
id|lh
comma
id|Scsi_Host_Name
comma
id|shn_list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|shn-&gt;host_registered
)paren
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|hname
comma
id|shn-&gt;name
comma
id|hname_len
)paren
)paren
(brace
id|shost_name
op_assign
id|shn
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|shost_name
)paren
(brace
id|shost_name
op_assign
id|scsi_host_hn_add
c_func
(paren
id|hname
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shost_name
)paren
(brace
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
)brace
id|shost-&gt;host_no
op_assign
id|shost_name-&gt;host_no
suffix:semicolon
id|shost_name-&gt;host_registered
op_assign
l_int|1
suffix:semicolon
id|scsi_hosts_registered
op_increment
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
id|atomic_set
c_func
(paren
op_amp
id|shost-&gt;host_active
comma
l_int|0
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
id|FALSE
suffix:semicolon
id|shost-&gt;host_self_blocked
op_assign
id|FALSE
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
id|list_for_each
c_func
(paren
id|lh
comma
op_amp
id|scsi_host_list
)paren
(brace
id|shost_scr
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
macro_line|#ifdef CONFIG_PROC_FS
multiline_comment|/* Add the new driver to /proc/scsi if not already there */
r_if
c_cond
(paren
op_logical_neg
id|shost_tp-&gt;proc_dir
)paren
id|scsi_proc_host_mkdir
c_func
(paren
id|shost_tp
)paren
suffix:semicolon
id|scsi_proc_host_add
c_func
(paren
id|shost
)paren
suffix:semicolon
macro_line|#endif
id|strncpy
c_func
(paren
id|shost-&gt;host_driverfs_dev.name
comma
id|shost_tp-&gt;proc_name
comma
id|DEVICE_NAME_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|shost-&gt;host_driverfs_dev.bus_id
comma
l_string|&quot;scsi%d&quot;
comma
id|shost-&gt;host_no
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
id|down
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
r_int
id|cur_cnt
suffix:semicolon
id|Scsi_Device
op_star
id|sdev
suffix:semicolon
r_struct
id|Scsi_Device_Template
op_star
id|sdev_tp
suffix:semicolon
r_struct
id|list_head
op_star
id|lh
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|shost
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|shost_tp-&gt;shtp_list
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check no detect routine.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|shost_tp-&gt;detect
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* If max_sectors isn&squot;t set, default to max */
r_if
c_cond
(paren
op_logical_neg
id|shost_tp-&gt;max_sectors
)paren
id|shost_tp-&gt;max_sectors
op_assign
l_int|1024
suffix:semicolon
id|cur_cnt
op_assign
id|scsi_hosts_registered
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
multiline_comment|/*&n;&t; * The detect routine must carefully spinunlock/spinlock if it&n;&t; * enables interrupts, since all interrupt handlers do spinlock as&n;&t; * well.&n;&t; */
multiline_comment|/*&n;&t; * detect should do its own locking&n;&t; * FIXME present is now set is scsi_register which breaks manual&n;&t; * registration code below.&n;&t; */
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
id|shost_tp-&gt;present
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * FIXME Who needs manual registration and why???&n;&t;&t;&t; */
r_if
c_cond
(paren
id|cur_cnt
op_eq
id|scsi_hosts_registered
)paren
(brace
r_if
c_cond
(paren
id|shost_tp-&gt;present
OG
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;scsi: Failure to register&quot;
l_string|&quot;low-level scsi driver&quot;
)paren
suffix:semicolon
id|scsi_unregister_host
c_func
(paren
id|shost_tp
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * The low-level driver failed to register a driver.&n;&t;&t;&t; * We can do this now.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|scsi_register
c_func
(paren
id|shost_tp
comma
l_int|0
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;scsi: register failed.&bslash;n&quot;
)paren
suffix:semicolon
id|scsi_unregister_host
c_func
(paren
id|shost_tp
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|list_add_tail
c_func
(paren
op_amp
id|shost_tp-&gt;shtp_list
comma
op_amp
id|scsi_host_tmpl_list
)paren
suffix:semicolon
multiline_comment|/* The next step is to call scan_scsis here.  This generates the&n;&t;&t; * Scsi_Devices entries&n;&t;&t; */
id|list_for_each
c_func
(paren
id|lh
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
r_const
r_char
op_star
id|dm_name
suffix:semicolon
r_if
c_cond
(paren
id|shost_tp-&gt;info
)paren
(brace
id|dm_name
op_assign
id|shost_tp
op_member_access_from_pointer
id|info
c_func
(paren
id|shost
)paren
suffix:semicolon
)brace
r_else
(brace
id|dm_name
op_assign
id|shost_tp-&gt;name
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;scsi%d : %s&bslash;n&quot;
comma
id|shost-&gt;host_no
comma
id|dm_name
)paren
suffix:semicolon
multiline_comment|/* first register parent with driverfs */
id|device_register
c_func
(paren
op_amp
id|shost-&gt;host_driverfs_dev
)paren
suffix:semicolon
id|scan_scsis
c_func
(paren
id|shost
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|sdev_tp
op_assign
id|scsi_devicelist
suffix:semicolon
id|sdev_tp
suffix:semicolon
id|sdev_tp
op_assign
id|sdev_tp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|sdev_tp-&gt;init
op_logical_and
id|sdev_tp-&gt;dev_noticed
)paren
(paren
op_star
id|sdev_tp-&gt;init
)paren
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Next we create the Scsi_Cmnd structures for this host &n;&t;&t; */
id|list_for_each
c_func
(paren
id|lh
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
r_for
c_loop
(paren
id|sdev
op_assign
id|shost-&gt;host_queue
suffix:semicolon
id|sdev
suffix:semicolon
id|sdev
op_assign
id|sdev-&gt;next
)paren
r_if
c_cond
(paren
id|sdev-&gt;host-&gt;hostt
op_eq
id|shost_tp
)paren
(brace
r_for
c_loop
(paren
id|sdev_tp
op_assign
id|scsi_devicelist
suffix:semicolon
id|sdev_tp
suffix:semicolon
id|sdev_tp
op_assign
id|sdev_tp-&gt;next
)paren
r_if
c_cond
(paren
id|sdev_tp-&gt;attach
)paren
(paren
op_star
id|sdev_tp-&gt;attach
)paren
(paren
id|sdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sdev-&gt;attached
)paren
(brace
id|scsi_build_commandblocks
c_func
(paren
id|sdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sdev-&gt;current_queue_depth
op_eq
l_int|0
)paren
r_goto
id|out_of_space
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* This does any final handling that is required. */
r_for
c_loop
(paren
id|sdev_tp
op_assign
id|scsi_devicelist
suffix:semicolon
id|sdev_tp
suffix:semicolon
id|sdev_tp
op_assign
id|sdev_tp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|sdev_tp-&gt;finish
op_logical_and
id|sdev_tp-&gt;nr_dev
)paren
(brace
(paren
op_star
id|sdev_tp-&gt;finish
)paren
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
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
r_int
id|pcount
suffix:semicolon
multiline_comment|/* get the big kernel lock, so we don&squot;t race with open() */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|pcount
op_assign
id|scsi_hosts_registered
suffix:semicolon
id|scsi_tp_for_each_host
c_func
(paren
id|shost_tp
comma
id|scsi_host_chk_and_release
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pcount
op_ne
id|scsi_hosts_registered
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;scsi : %d host%s left.&bslash;n&quot;
comma
id|scsi_hosts_registered
comma
(paren
id|scsi_hosts_registered
op_eq
l_int|1
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;s&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Remove it from the list if all&n;&t; * hosts were successfully removed (ie preset == 0)&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|shost_tp-&gt;present
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|shost_tp-&gt;shtp_list
)paren
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
id|unlock_kernel
c_func
(paren
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
r_struct
id|list_head
op_star
id|lh
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
id|list_for_each
c_func
(paren
id|lh
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
id|shost-&gt;host_no
op_eq
id|host_no
)paren
(brace
multiline_comment|/* XXX Inc ref count */
r_goto
id|done
suffix:semicolon
)brace
)brace
id|shost
op_assign
(paren
r_struct
id|Scsi_Host
op_star
)paren
l_int|NULL
suffix:semicolon
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
multiline_comment|/* XXX Get list lock */
multiline_comment|/* XXX dec ref count */
multiline_comment|/* XXX Release list lock */
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_host_hn_init - init scsi host number list from string&n; * @shost_hn:&t;string of scsi host driver names.&n; **/
DECL|function|scsi_host_hn_init
r_void
id|__init
id|scsi_host_hn_init
c_func
(paren
r_char
op_star
id|shost_hn
)paren
(brace
r_char
op_star
id|temp
op_assign
id|shost_hn
suffix:semicolon
r_while
c_loop
(paren
id|temp
)paren
(brace
r_while
c_loop
(paren
op_star
id|temp
op_logical_and
(paren
op_star
id|temp
op_ne
l_char|&squot;:&squot;
)paren
op_logical_and
(paren
op_star
id|temp
op_ne
l_char|&squot;,&squot;
)paren
)paren
id|temp
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|temp
)paren
id|temp
op_assign
l_int|NULL
suffix:semicolon
r_else
op_star
id|temp
op_increment
op_assign
l_int|0
suffix:semicolon
(paren
r_void
)paren
id|scsi_host_hn_add
c_func
(paren
id|shost_hn
)paren
suffix:semicolon
id|shost_hn
op_assign
id|temp
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * scsi_host_no_release - free all entries in scsi host number list&n; **/
DECL|function|scsi_host_hn_release
r_void
id|__exit
id|scsi_host_hn_release
c_func
(paren
)paren
(brace
r_struct
id|list_head
op_star
id|lh
comma
op_star
id|next
suffix:semicolon
id|Scsi_Host_Name
op_star
id|shn
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|lh
comma
id|next
comma
op_amp
id|scsi_host_hn_list
)paren
(brace
id|shn
op_assign
id|list_entry
c_func
(paren
id|lh
comma
id|Scsi_Host_Name
comma
id|shn_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shn-&gt;name
)paren
id|kfree
c_func
(paren
id|shn-&gt;name
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|shn
)paren
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
id|sdev-&gt;device_busy
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|shost-&gt;in_recovery
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
DECL|function|scsi_host_failed_inc_and_test
r_void
id|scsi_host_failed_inc_and_test
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
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
id|shost-&gt;in_recovery
op_assign
l_int|1
suffix:semicolon
id|shost-&gt;host_failed
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|shost-&gt;host_busy
op_eq
id|shost-&gt;host_failed
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
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
