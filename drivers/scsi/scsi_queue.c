multiline_comment|/*&n; *  scsi_queue.c Copyright (C) 1997 Eric Youngdale&n; *&n; *  generic mid-level SCSI queueing.&n; *&n; *  The point of this is that we need to track when hosts are unable to&n; *  accept a command because they are busy.  In addition, we track devices&n; *  that cannot accept a command because of a QUEUE_FULL condition.  In both&n; *  of these cases, we enter the command in the queue.  At some later point,&n; *  we attempt to remove commands from the queue and retry them.&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;constants.h&quot;
multiline_comment|/*&n; * TODO:&n; *      1) Prevent multiple traversals of list to look for commands to&n; *         queue.&n; *      2) Protect against multiple insertions of list at the same time.&n; * DONE:&n; *      1) Set state of scsi command to a new state value for ml queue.&n; *      2) Insert into queue when host rejects command.&n; *      3) Make sure status code is properly passed from low-level queue func&n; *         so that internal_cmnd properly returns the right value.&n; *      4) Insert into queue when QUEUE_FULL.&n; *      5) Cull queue in bottom half handler.&n; *      6) Check usage count prior to queue insertion.  Requeue if usage&n; *         count is 0.&n; *      7) Don&squot;t send down any more commands if the host/device is busy.&n; */
DECL|variable|RCSid
r_static
r_const
r_char
id|RCSid
(braket
)braket
op_assign
l_string|&quot;$Header: /mnt/ide/home/eric/CVSROOT/linux/drivers/scsi/scsi_queue.c,v 1.1 1997/10/21 11:16:38 eric Exp $&quot;
suffix:semicolon
multiline_comment|/*&n; * Function:    scsi_mlqueue_insert()&n; *&n; * Purpose:     Insert a command in the midlevel queue.&n; *&n; * Arguments:   cmd    - command that we are adding to queue.&n; *              reason - why we are inserting command to queue.&n; *&n; * Lock status: Assumed that lock is not held upon entry.&n; *&n; * Returns:     Nothing.&n; *&n; * Notes:       We do this for one of two cases.  Either the host is busy&n; *              and it cannot accept any more commands for the time being,&n; *              or the device returned QUEUE_FULL and can accept no more&n; *              commands.&n; * Notes:       This could be called either from an interrupt context or a&n; *              normal process context.&n; */
DECL|function|scsi_mlqueue_insert
r_int
id|scsi_mlqueue_insert
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
comma
r_int
id|reason
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|SCSI_LOG_MLQUEUE
c_func
(paren
l_int|1
comma
id|printk
c_func
(paren
l_string|&quot;Inserting command %p into mlqueue&bslash;n&quot;
comma
id|cmd
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We are inserting the command into the ml queue.  First, we&n;&t; * cancel the timer, so it doesn&squot;t time out.&n;&t; */
id|scsi_delete_timer
c_func
(paren
id|cmd
)paren
suffix:semicolon
id|host
op_assign
id|cmd-&gt;host
suffix:semicolon
multiline_comment|/*&n;&t; * Next, set the appropriate busy bit for the device/host.&n;&t; */
r_if
c_cond
(paren
id|reason
op_eq
id|SCSI_MLQUEUE_HOST_BUSY
)paren
(brace
multiline_comment|/*&n;&t;&t; * Protect against race conditions.  If the host isn&squot;t busy,&n;&t;&t; * assume that something actually completed, and that we should&n;&t;&t; * be able to queue a command now.  Note that there is an implicit&n;&t;&t; * assumption that every host can always queue at least one command.&n;&t;&t; * If a host is inactive and cannot queue any commands, I don&squot;t see&n;&t;&t; * how things could possibly work anyways.&n;&t;&t; */
r_if
c_cond
(paren
id|host-&gt;host_busy
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|scsi_retry_command
c_func
(paren
id|cmd
)paren
op_eq
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|host-&gt;host_blocked
op_assign
id|TRUE
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Protect against race conditions.  If the device isn&squot;t busy,&n;&t;&t; * assume that something actually completed, and that we should&n;&t;&t; * be able to queue a command now.  Note that there is an implicit&n;&t;&t; * assumption that every host can always queue at least one command.&n;&t;&t; * If a host is inactive and cannot queue any commands, I don&squot;t see&n;&t;&t; * how things could possibly work anyways.&n;&t;&t; */
r_if
c_cond
(paren
id|cmd-&gt;device-&gt;device_busy
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|scsi_retry_command
c_func
(paren
id|cmd
)paren
op_eq
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|cmd-&gt;device-&gt;device_blocked
op_assign
id|TRUE
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Register the fact that we own the thing for now.&n;&t; */
id|cmd-&gt;state
op_assign
id|SCSI_STATE_MLQUEUE
suffix:semicolon
id|cmd-&gt;owner
op_assign
id|SCSI_OWNER_MIDLEVEL
suffix:semicolon
id|cmd-&gt;bh_next
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Decrement the counters, since these commands are no longer&n;&t; * active on the host/device.&n;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|cmd-&gt;host-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
id|cmd-&gt;host-&gt;host_busy
op_decrement
suffix:semicolon
id|cmd-&gt;device-&gt;device_busy
op_decrement
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|cmd-&gt;host-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Insert this command at the head of the queue for it&squot;s device.&n;&t; * It will go before all other commands that are already in the queue.&n;&t; */
id|scsi_insert_special_cmd
c_func
(paren
id|cmd
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
