multiline_comment|/*&n; * Driver for the SWIM (Super Woz Integrated Machine) IOP&n; * floppy controller on the Macintosh IIfx and Quadra 900/950&n; *&n; * Written by Joshua M. Thompson (funaho@jurai.org)&n; * based on the SWIM3 driver (c) 1996 by Paul Mackerras.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * 1999-06-12 (jmt) - Initial implementation.&n; */
multiline_comment|/*&n; * -------------------&n; * Theory of Operation&n; * -------------------&n; *&n; * Since the SWIM IOP is message-driven we implement a simple request queue&n; * system.  One outstanding request may be queued at any given time (this is&n; * an IOP limitation); only when that request has completed can a new request&n; * be sent.&n; */
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/fd.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/mac_iop.h&gt;
macro_line|#include &lt;asm/swim_iop.h&gt;
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;Version 0.1 (1999-06-12)&quot;
DECL|macro|MAX_FLOPPIES
mdefine_line|#define MAX_FLOPPIES&t;4
DECL|enum|swim_state
r_enum
id|swim_state
(brace
DECL|enumerator|idle
id|idle
comma
DECL|enumerator|available
id|available
comma
DECL|enumerator|revalidating
id|revalidating
comma
DECL|enumerator|transferring
id|transferring
comma
DECL|enumerator|ejecting
id|ejecting
)brace
suffix:semicolon
DECL|struct|floppy_state
r_struct
id|floppy_state
(brace
DECL|member|state
r_enum
id|swim_state
id|state
suffix:semicolon
DECL|member|drive_num
r_int
id|drive_num
suffix:semicolon
multiline_comment|/* device number */
DECL|member|secpercyl
r_int
id|secpercyl
suffix:semicolon
multiline_comment|/* disk geometry information */
DECL|member|secpertrack
r_int
id|secpertrack
suffix:semicolon
DECL|member|total_secs
r_int
id|total_secs
suffix:semicolon
DECL|member|write_prot
r_int
id|write_prot
suffix:semicolon
multiline_comment|/* 1 if write-protected, 0 if not, -1 dunno */
DECL|member|ref_count
r_int
id|ref_count
suffix:semicolon
DECL|member|timeout
r_struct
id|timer_list
id|timeout
suffix:semicolon
DECL|member|ejected
r_int
id|ejected
suffix:semicolon
DECL|member|wait
r_struct
id|wait_queue
op_star
id|wait
suffix:semicolon
DECL|member|wanted
r_int
id|wanted
suffix:semicolon
DECL|member|timeout_pending
r_int
id|timeout_pending
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|swim_iop_req
r_struct
id|swim_iop_req
(brace
DECL|member|sent
r_int
id|sent
suffix:semicolon
DECL|member|complete
r_int
id|complete
suffix:semicolon
DECL|member|command
id|__u8
id|command
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|fs
r_struct
id|floppy_state
op_star
id|fs
suffix:semicolon
DECL|member|done
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|swim_iop_req
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|current_req
r_static
r_struct
id|swim_iop_req
op_star
id|current_req
suffix:semicolon
DECL|variable|floppy_count
r_static
r_int
id|floppy_count
suffix:semicolon
DECL|variable|floppy_states
r_static
r_struct
id|floppy_state
id|floppy_states
(braket
id|MAX_FLOPPIES
)braket
suffix:semicolon
DECL|variable|swim_iop_lock
r_static
id|spinlock_t
id|swim_iop_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|CURRENT
mdefine_line|#define CURRENT elv_next_request(&amp;swim_queue)
DECL|variable|drive_names
r_static
r_char
op_star
id|drive_names
(braket
l_int|7
)braket
op_assign
(brace
l_string|&quot;not installed&quot;
comma
multiline_comment|/* DRV_NONE    */
l_string|&quot;unknown (1)&quot;
comma
multiline_comment|/* DRV_UNKNOWN */
l_string|&quot;a 400K drive&quot;
comma
multiline_comment|/* DRV_400K    */
l_string|&quot;an 800K drive&quot;
multiline_comment|/* DRV_800K    */
l_string|&quot;unknown (4)&quot;
comma
multiline_comment|/* ????        */
l_string|&quot;an FDHD&quot;
comma
multiline_comment|/* DRV_FDHD    */
l_string|&quot;unknown (6)&quot;
comma
multiline_comment|/* ????        */
l_string|&quot;an Apple HD20&quot;
multiline_comment|/* DRV_HD20    */
)brace
suffix:semicolon
r_int
id|swimiop_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|swimiop_init_request
c_func
(paren
r_struct
id|swim_iop_req
op_star
)paren
suffix:semicolon
r_static
r_int
id|swimiop_send_request
c_func
(paren
r_struct
id|swim_iop_req
op_star
)paren
suffix:semicolon
r_static
r_void
id|swimiop_receive
c_func
(paren
r_struct
id|iop_msg
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_static
r_void
id|swimiop_status_update
c_func
(paren
r_int
comma
r_struct
id|swim_drvstatus
op_star
)paren
suffix:semicolon
r_static
r_int
id|swimiop_eject
c_func
(paren
r_struct
id|floppy_state
op_star
id|fs
)paren
suffix:semicolon
r_static
r_int
id|floppy_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|param
)paren
suffix:semicolon
r_static
r_int
id|floppy_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_static
r_int
id|floppy_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_static
r_int
id|floppy_check_change
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
)paren
suffix:semicolon
r_static
r_int
id|floppy_revalidate
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
)paren
suffix:semicolon
r_static
r_int
id|grab_drive
c_func
(paren
r_struct
id|floppy_state
op_star
id|fs
comma
r_enum
id|swim_state
id|state
comma
r_int
id|interruptible
)paren
suffix:semicolon
r_static
r_void
id|release_drive
c_func
(paren
r_struct
id|floppy_state
op_star
id|fs
)paren
suffix:semicolon
r_static
r_void
id|set_timeout
c_func
(paren
r_struct
id|floppy_state
op_star
id|fs
comma
r_int
id|nticks
comma
r_void
(paren
op_star
id|proc
)paren
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_static
r_void
id|fd_request_timeout
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|do_fd_request
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
suffix:semicolon
r_static
r_void
id|start_request
c_func
(paren
r_struct
id|floppy_state
op_star
id|fs
)paren
suffix:semicolon
DECL|variable|floppy_fops
r_static
r_struct
id|block_device_operations
id|floppy_fops
op_assign
(brace
dot
id|open
op_assign
id|floppy_open
comma
dot
id|release
op_assign
id|floppy_release
comma
dot
id|ioctl
op_assign
id|floppy_ioctl
comma
dot
id|media_changed
op_assign
id|floppy_check_change
comma
dot
id|revalidate_disk
op_assign
id|floppy_revalidate
comma
)brace
suffix:semicolon
DECL|variable|swim_queue
r_static
r_struct
id|request_queue
id|swim_queue
suffix:semicolon
multiline_comment|/*&n; * SWIM IOP initialization&n; */
DECL|function|swimiop_init
r_int
id|swimiop_init
c_func
(paren
r_void
)paren
(brace
r_volatile
r_struct
id|swim_iop_req
id|req
suffix:semicolon
r_struct
id|swimcmd_status
op_star
id|cmd
op_assign
(paren
r_struct
id|swimcmd_status
op_star
)paren
op_amp
id|req.command
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|swim_drvstatus
op_star
id|ds
op_assign
op_amp
id|cmd-&gt;status
suffix:semicolon
r_struct
id|floppy_state
op_star
id|fs
suffix:semicolon
r_int
id|i
suffix:semicolon
id|current_req
op_assign
l_int|NULL
suffix:semicolon
id|floppy_count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iop_ism_present
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|register_blkdev
c_func
(paren
id|FLOPPY_MAJOR
comma
l_string|&quot;fd&quot;
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|blk_init_queue
c_func
(paren
op_amp
id|swim_queue
comma
id|do_fd_request
comma
op_amp
id|swim_iop_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SWIM-IOP: %s by Joshua M. Thompson (funaho@jurai.org)&bslash;n&quot;
comma
id|DRIVER_VERSION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iop_listen
c_func
(paren
id|SWIM_IOP
comma
id|SWIM_CHAN
comma
id|swimiop_receive
comma
l_string|&quot;SWIM&quot;
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SWIM-IOP: IOP channel already in use; can&squot;t initialize.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SWIM_IOP: probing for installed drives.&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_FLOPPIES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|memset
c_func
(paren
op_amp
id|floppy_states
(braket
id|i
)braket
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|floppy_state
)paren
)paren
suffix:semicolon
id|fs
op_assign
op_amp
id|floppy_states
(braket
id|floppy_count
)braket
suffix:semicolon
id|swimiop_init_request
c_func
(paren
op_amp
id|req
)paren
suffix:semicolon
id|cmd-&gt;code
op_assign
id|CMD_STATUS
suffix:semicolon
id|cmd-&gt;drive_num
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|swimiop_send_request
c_func
(paren
op_amp
id|req
)paren
op_ne
l_int|0
)paren
r_continue
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|req.complete
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;error
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SWIM-IOP: probe on drive %d returned error %d&bslash;n&quot;
comma
id|i
comma
(paren
id|uint
)paren
id|cmd-&gt;error
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ds-&gt;installed
op_ne
l_int|0x01
)paren
r_continue
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SWIM-IOP: drive %d is %s (%s, %s, %s, %s)&bslash;n&quot;
comma
id|i
comma
id|drive_names
(braket
id|ds-&gt;info.type
)braket
comma
id|ds-&gt;info.external
ques
c_cond
l_string|&quot;ext&quot;
suffix:colon
l_string|&quot;int&quot;
comma
id|ds-&gt;info.scsi
ques
c_cond
l_string|&quot;scsi&quot;
suffix:colon
l_string|&quot;floppy&quot;
comma
id|ds-&gt;info.fixed
ques
c_cond
l_string|&quot;fixed&quot;
suffix:colon
l_string|&quot;removable&quot;
comma
id|ds-&gt;info.secondary
ques
c_cond
l_string|&quot;secondary&quot;
suffix:colon
l_string|&quot;primary&quot;
)paren
suffix:semicolon
id|swimiop_status_update
c_func
(paren
id|floppy_count
comma
id|ds
)paren
suffix:semicolon
id|fs-&gt;state
op_assign
id|idle
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|fs-&gt;timeout
)paren
suffix:semicolon
id|floppy_count
op_increment
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;SWIM-IOP: detected %d installed drives.&bslash;n&quot;
comma
id|floppy_count
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|floppy_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|gendisk
op_star
id|disk
op_assign
id|alloc_disk
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|disk
)paren
r_continue
suffix:semicolon
id|disk-&gt;major
op_assign
id|FLOPPY_MAJOR
suffix:semicolon
id|disk-&gt;first_minor
op_assign
id|i
suffix:semicolon
id|disk-&gt;fops
op_assign
op_amp
id|floppy_fops
suffix:semicolon
id|sprintf
c_func
(paren
id|disk-&gt;disk_name
comma
l_string|&quot;fd%d&quot;
comma
id|i
)paren
suffix:semicolon
id|disk-&gt;private_data
op_assign
op_amp
id|floppy_states
(braket
id|i
)braket
suffix:semicolon
id|disk-&gt;queue
op_assign
op_amp
id|swim_queue
suffix:semicolon
id|set_capacity
c_func
(paren
id|disk
comma
l_int|2880
op_star
l_int|2
)paren
suffix:semicolon
id|add_disk
c_func
(paren
id|disk
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|swimiop_init_request
r_static
r_void
id|swimiop_init_request
c_func
(paren
r_struct
id|swim_iop_req
op_star
id|req
)paren
(brace
id|req-&gt;sent
op_assign
l_int|0
suffix:semicolon
id|req-&gt;complete
op_assign
l_int|0
suffix:semicolon
id|req-&gt;done
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|swimiop_send_request
r_static
r_int
id|swimiop_send_request
c_func
(paren
r_struct
id|swim_iop_req
op_star
id|req
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* It&squot;s doubtful an interrupt routine would try to send */
multiline_comment|/* a SWIM request, but I&squot;d rather play it safe here.    */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current_req
op_ne
l_int|NULL
)paren
(brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|current_req
op_assign
id|req
suffix:semicolon
multiline_comment|/* Interrupts should be back on for iop_send_message() */
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|err
op_assign
id|iop_send_message
c_func
(paren
id|SWIM_IOP
comma
id|SWIM_CHAN
comma
(paren
r_void
op_star
)paren
id|req
comma
r_sizeof
(paren
id|req-&gt;command
)paren
comma
(paren
id|__u8
op_star
)paren
op_amp
id|req-&gt;command
(braket
l_int|0
)braket
comma
id|swimiop_receive
)paren
suffix:semicolon
multiline_comment|/* No race condition here; we own current_req at this point */
r_if
c_cond
(paren
id|err
)paren
(brace
id|current_req
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|req-&gt;sent
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Receive a SWIM message from the IOP.&n; *&n; * This will be called in two cases:&n; *&n; * 1. A message has been successfully sent to the IOP.&n; * 2. An unsolicited message was received from the IOP.&n; */
DECL|function|swimiop_receive
r_void
id|swimiop_receive
c_func
(paren
r_struct
id|iop_msg
op_star
id|msg
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|swim_iop_req
op_star
id|req
suffix:semicolon
r_struct
id|swimmsg_status
op_star
id|sm
suffix:semicolon
r_struct
id|swim_drvstatus
op_star
id|ds
suffix:semicolon
id|req
op_assign
id|current_req
suffix:semicolon
r_switch
c_cond
(paren
id|msg-&gt;status
)paren
(brace
r_case
id|IOP_MSGSTATUS_COMPLETE
suffix:colon
id|memcpy
c_func
(paren
op_amp
id|req-&gt;command
(braket
l_int|0
)braket
comma
op_amp
id|msg-&gt;reply
(braket
l_int|0
)braket
comma
r_sizeof
(paren
id|req-&gt;command
)paren
)paren
suffix:semicolon
id|req-&gt;complete
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;done
)paren
(paren
op_star
id|req-&gt;done
)paren
(paren
id|req
)paren
suffix:semicolon
id|current_req
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IOP_MSGSTATUS_UNSOL
suffix:colon
id|sm
op_assign
(paren
r_struct
id|swimmsg_status
op_star
)paren
op_amp
id|msg-&gt;message
(braket
l_int|0
)braket
suffix:semicolon
id|ds
op_assign
op_amp
id|sm-&gt;status
suffix:semicolon
id|swimiop_status_update
c_func
(paren
id|sm-&gt;drive_num
comma
id|ds
)paren
suffix:semicolon
id|iop_complete_message
c_func
(paren
id|msg
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|swimiop_status_update
r_static
r_void
id|swimiop_status_update
c_func
(paren
r_int
id|drive_num
comma
r_struct
id|swim_drvstatus
op_star
id|ds
)paren
(brace
r_struct
id|floppy_state
op_star
id|fs
op_assign
op_amp
id|floppy_states
(braket
id|drive_num
)braket
suffix:semicolon
id|fs-&gt;write_prot
op_assign
(paren
id|ds-&gt;write_prot
op_eq
l_int|0x80
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ds-&gt;disk_in_drive
op_ne
l_int|0x01
)paren
op_logical_and
(paren
id|ds-&gt;disk_in_drive
op_ne
l_int|0x02
)paren
)paren
(brace
id|fs-&gt;ejected
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|fs-&gt;ejected
op_assign
l_int|0
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|ds-&gt;info.type
)paren
(brace
r_case
id|DRV_400K
suffix:colon
id|fs-&gt;secpercyl
op_assign
l_int|10
suffix:semicolon
id|fs-&gt;secpertrack
op_assign
l_int|10
suffix:semicolon
id|fs-&gt;total_secs
op_assign
l_int|800
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DRV_800K
suffix:colon
id|fs-&gt;secpercyl
op_assign
l_int|20
suffix:semicolon
id|fs-&gt;secpertrack
op_assign
l_int|10
suffix:semicolon
id|fs-&gt;total_secs
op_assign
l_int|1600
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DRV_FDHD
suffix:colon
id|fs-&gt;secpercyl
op_assign
l_int|36
suffix:semicolon
id|fs-&gt;secpertrack
op_assign
l_int|18
suffix:semicolon
id|fs-&gt;total_secs
op_assign
l_int|2880
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|fs-&gt;secpercyl
op_assign
l_int|0
suffix:semicolon
id|fs-&gt;secpertrack
op_assign
l_int|0
suffix:semicolon
id|fs-&gt;total_secs
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|swimiop_eject
r_static
r_int
id|swimiop_eject
c_func
(paren
r_struct
id|floppy_state
op_star
id|fs
)paren
(brace
r_int
id|err
comma
id|n
suffix:semicolon
r_struct
id|swim_iop_req
id|req
suffix:semicolon
r_struct
id|swimcmd_eject
op_star
id|cmd
op_assign
(paren
r_struct
id|swimcmd_eject
op_star
)paren
op_amp
id|req.command
(braket
l_int|0
)braket
suffix:semicolon
id|err
op_assign
id|grab_drive
c_func
(paren
id|fs
comma
id|ejecting
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|swimiop_init_request
c_func
(paren
op_amp
id|req
)paren
suffix:semicolon
id|cmd-&gt;code
op_assign
id|CMD_EJECT
suffix:semicolon
id|cmd-&gt;drive_num
op_assign
id|fs-&gt;drive_num
suffix:semicolon
id|err
op_assign
id|swimiop_send_request
c_func
(paren
op_amp
id|req
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|release_drive
c_func
(paren
id|fs
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_for
c_loop
(paren
id|n
op_assign
l_int|2
op_star
id|HZ
suffix:semicolon
id|n
OG
l_int|0
suffix:semicolon
op_decrement
id|n
)paren
(brace
r_if
c_cond
(paren
id|req.complete
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
)brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|release_drive
c_func
(paren
id|fs
)paren
suffix:semicolon
r_return
id|cmd-&gt;error
suffix:semicolon
)brace
DECL|variable|floppy_type
r_static
r_struct
id|floppy_struct
id|floppy_type
op_assign
(brace
l_int|2880
comma
l_int|18
comma
l_int|2
comma
l_int|80
comma
l_int|0
comma
l_int|0x1B
comma
l_int|0x00
comma
l_int|0xCF
comma
l_int|0x6C
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/*  7 1.44MB 3.5&quot;   */
DECL|function|floppy_ioctl
r_static
r_int
id|floppy_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|param
)paren
(brace
r_struct
id|floppy_state
op_star
id|fs
op_assign
id|inode-&gt;i_bdev-&gt;bd_disk-&gt;private_data
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cmd
op_amp
l_int|0x80
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|FDEJECT
suffix:colon
r_if
c_cond
(paren
id|fs-&gt;ref_count
op_ne
l_int|1
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|err
op_assign
id|swimiop_eject
c_func
(paren
id|fs
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
r_case
id|FDGETPRM
suffix:colon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|param
comma
(paren
r_void
op_star
)paren
op_amp
id|floppy_type
comma
r_sizeof
(paren
r_struct
id|floppy_struct
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENOTTY
suffix:semicolon
)brace
DECL|function|floppy_open
r_static
r_int
id|floppy_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_struct
id|floppy_state
op_star
id|fs
op_assign
id|inode-&gt;i_bdev-&gt;bd_disk-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|fs-&gt;ref_count
op_eq
op_minus
l_int|1
op_logical_or
id|filp-&gt;f_flags
op_amp
id|O_EXCL
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
(paren
id|filp-&gt;f_flags
op_amp
id|O_NDELAY
)paren
op_eq
l_int|0
op_logical_and
(paren
id|filp-&gt;f_mode
op_amp
l_int|3
)paren
)paren
(brace
id|check_disk_change
c_func
(paren
id|inode-&gt;i_bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fs-&gt;ejected
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|filp-&gt;f_mode
op_amp
l_int|2
)paren
op_logical_and
id|fs-&gt;write_prot
)paren
r_return
op_minus
id|EROFS
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_EXCL
)paren
id|fs-&gt;ref_count
op_assign
op_minus
l_int|1
suffix:semicolon
r_else
op_increment
id|fs-&gt;ref_count
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|floppy_release
r_static
r_int
id|floppy_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_struct
id|floppy_state
op_star
id|fs
op_assign
id|inode-&gt;i_bdev-&gt;bd_disk-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|fs-&gt;ref_count
OG
l_int|0
)paren
id|fs-&gt;ref_count
op_decrement
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|floppy_check_change
r_static
r_int
id|floppy_check_change
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
)paren
(brace
r_struct
id|floppy_state
op_star
id|fs
op_assign
id|disk-&gt;private_data
suffix:semicolon
r_return
id|fs-&gt;ejected
suffix:semicolon
)brace
DECL|function|floppy_revalidate
r_static
r_int
id|floppy_revalidate
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
)paren
(brace
r_struct
id|floppy_state
op_star
id|fs
op_assign
id|disk-&gt;private_data
suffix:semicolon
id|grab_drive
c_func
(paren
id|fs
comma
id|revalidating
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* yadda, yadda */
id|release_drive
c_func
(paren
id|fs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|floppy_off
r_static
r_void
id|floppy_off
c_func
(paren
r_int
r_int
id|nr
)paren
(brace
)brace
DECL|function|grab_drive
r_static
r_int
id|grab_drive
c_func
(paren
r_struct
id|floppy_state
op_star
id|fs
comma
r_enum
id|swim_state
id|state
comma
r_int
id|interruptible
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fs-&gt;state
op_ne
id|idle
)paren
(brace
op_increment
id|fs-&gt;wanted
suffix:semicolon
r_while
c_loop
(paren
id|fs-&gt;state
op_ne
id|available
)paren
(brace
r_if
c_cond
(paren
id|interruptible
op_logical_and
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
op_decrement
id|fs-&gt;wanted
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
id|interruptible_sleep_on
c_func
(paren
op_amp
id|fs-&gt;wait
)paren
suffix:semicolon
)brace
op_decrement
id|fs-&gt;wanted
suffix:semicolon
)brace
id|fs-&gt;state
op_assign
id|state
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|release_drive
r_static
r_void
id|release_drive
c_func
(paren
r_struct
id|floppy_state
op_star
id|fs
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|fs-&gt;state
op_assign
id|idle
suffix:semicolon
id|start_request
c_func
(paren
id|fs
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|set_timeout
r_static
r_void
id|set_timeout
c_func
(paren
r_struct
id|floppy_state
op_star
id|fs
comma
r_int
id|nticks
comma
r_void
(paren
op_star
id|proc
)paren
(paren
r_int
r_int
)paren
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fs-&gt;timeout_pending
)paren
id|del_timer
c_func
(paren
op_amp
id|fs-&gt;timeout
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|fs-&gt;timeout
)paren
suffix:semicolon
id|fs-&gt;timeout.expires
op_assign
id|jiffies
op_plus
id|nticks
suffix:semicolon
id|fs-&gt;timeout.function
op_assign
id|proc
suffix:semicolon
id|fs-&gt;timeout.data
op_assign
(paren
r_int
r_int
)paren
id|fs
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|fs-&gt;timeout
)paren
suffix:semicolon
id|fs-&gt;timeout_pending
op_assign
l_int|1
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|do_fd_request
r_static
r_void
id|do_fd_request
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|floppy_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|start_request
c_func
(paren
op_amp
id|floppy_states
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
DECL|function|fd_request_complete
r_static
r_void
id|fd_request_complete
c_func
(paren
r_struct
id|swim_iop_req
op_star
id|req
)paren
(brace
r_struct
id|floppy_state
op_star
id|fs
op_assign
id|req-&gt;fs
suffix:semicolon
r_struct
id|swimcmd_rw
op_star
id|cmd
op_assign
(paren
r_struct
id|swimcmd_rw
op_star
)paren
op_amp
id|req-&gt;command
(braket
l_int|0
)braket
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|fs-&gt;timeout
)paren
suffix:semicolon
id|fs-&gt;timeout_pending
op_assign
l_int|0
suffix:semicolon
id|fs-&gt;state
op_assign
id|idle
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;error
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SWIM-IOP: error %d on read/write request.&bslash;n&quot;
comma
id|cmd-&gt;error
)paren
suffix:semicolon
id|end_request
c_func
(paren
id|CURRENT
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|CURRENT-&gt;sector
op_add_assign
id|cmd-&gt;num_blocks
suffix:semicolon
id|CURRENT-&gt;current_nr_sectors
op_sub_assign
id|cmd-&gt;num_blocks
suffix:semicolon
r_if
c_cond
(paren
id|CURRENT-&gt;current_nr_sectors
op_le
l_int|0
)paren
(brace
id|end_request
c_func
(paren
id|CURRENT
comma
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|start_request
c_func
(paren
id|fs
)paren
suffix:semicolon
)brace
DECL|function|fd_request_timeout
r_static
r_void
id|fd_request_timeout
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|floppy_state
op_star
id|fs
op_assign
(paren
r_struct
id|floppy_state
op_star
)paren
id|data
suffix:semicolon
id|fs-&gt;timeout_pending
op_assign
l_int|0
suffix:semicolon
id|end_request
c_func
(paren
id|CURRENT
comma
l_int|0
)paren
suffix:semicolon
id|fs-&gt;state
op_assign
id|idle
suffix:semicolon
)brace
DECL|function|start_request
r_static
r_void
id|start_request
c_func
(paren
r_struct
id|floppy_state
op_star
id|fs
)paren
(brace
r_volatile
r_struct
id|swim_iop_req
id|req
suffix:semicolon
r_struct
id|swimcmd_rw
op_star
id|cmd
op_assign
(paren
r_struct
id|swimcmd_rw
op_star
)paren
op_amp
id|req.command
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|fs-&gt;state
op_eq
id|idle
op_logical_and
id|fs-&gt;wanted
)paren
(brace
id|fs-&gt;state
op_assign
id|available
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|fs-&gt;wait
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|CURRENT
op_logical_and
id|fs-&gt;state
op_eq
id|idle
)paren
(brace
r_if
c_cond
(paren
id|CURRENT-&gt;bh
op_logical_and
op_logical_neg
id|buffer_locked
c_func
(paren
id|CURRENT-&gt;bh
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;floppy: block not locked&quot;
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;do_fd_req: dev=%s cmd=%d sec=%ld nr_sec=%ld buf=%p&bslash;n&quot;
comma
id|CURRENT-&gt;rq_disk-&gt;disk_name
comma
id|CURRENT-&gt;cmd
comma
id|CURRENT-&gt;sector
comma
id|CURRENT-&gt;nr_sectors
comma
id|CURRENT-&gt;buffer
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;           rq_status=%d errors=%d current_nr_sectors=%ld&bslash;n&quot;
comma
id|CURRENT-&gt;rq_status
comma
id|CURRENT-&gt;errors
comma
id|CURRENT-&gt;current_nr_sectors
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|CURRENT-&gt;sector
OL
l_int|0
op_logical_or
id|CURRENT-&gt;sector
op_ge
id|fs-&gt;total_secs
)paren
(brace
id|end_request
c_func
(paren
id|CURRENT
comma
l_int|0
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|CURRENT-&gt;current_nr_sectors
op_eq
l_int|0
)paren
(brace
id|end_request
c_func
(paren
id|CURRENT
comma
l_int|1
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fs-&gt;ejected
)paren
(brace
id|end_request
c_func
(paren
id|CURRENT
comma
l_int|0
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|swimiop_init_request
c_func
(paren
op_amp
id|req
)paren
suffix:semicolon
id|req.fs
op_assign
id|fs
suffix:semicolon
id|req.done
op_assign
id|fd_request_complete
suffix:semicolon
r_if
c_cond
(paren
id|CURRENT-&gt;cmd
op_eq
id|WRITE
)paren
(brace
r_if
c_cond
(paren
id|fs-&gt;write_prot
)paren
(brace
id|end_request
c_func
(paren
id|CURRENT
comma
l_int|0
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|cmd-&gt;code
op_assign
id|CMD_WRITE
suffix:semicolon
)brace
r_else
(brace
id|cmd-&gt;code
op_assign
id|CMD_READ
suffix:semicolon
)brace
id|cmd-&gt;drive_num
op_assign
id|fs-&gt;drive_num
suffix:semicolon
id|cmd-&gt;buffer
op_assign
id|CURRENT-&gt;buffer
suffix:semicolon
id|cmd-&gt;first_block
op_assign
id|CURRENT-&gt;sector
suffix:semicolon
id|cmd-&gt;num_blocks
op_assign
id|CURRENT-&gt;current_nr_sectors
suffix:semicolon
r_if
c_cond
(paren
id|swimiop_send_request
c_func
(paren
op_amp
id|req
)paren
)paren
(brace
id|end_request
c_func
(paren
id|CURRENT
comma
l_int|0
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|set_timeout
c_func
(paren
id|fs
comma
id|HZ
op_star
id|CURRENT-&gt;current_nr_sectors
comma
id|fd_request_timeout
)paren
suffix:semicolon
id|fs-&gt;state
op_assign
id|transferring
suffix:semicolon
)brace
)brace
eof
