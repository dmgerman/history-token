multiline_comment|/* Copyright(c) 2000, Compaq Computer Corporation &n; * Fibre Channel Host Bus Adapter &n; * 64-bit, 66MHz PCI &n; * Originally developed and tested on:&n; * (front): [chip] Tachyon TS HPFC-5166A/1.2  L2C1090 ...&n; *          SP# P225CXCBFIEL6T, Rev XC&n; *          SP# 161290-001, Rev XD&n; * (back): Board No. 010008-001 A/W Rev X5, FAB REV X5&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; * Written by Don Zimmerman&n;*/
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
DECL|macro|SHUTDOWN_SIGS
mdefine_line|#define SHUTDOWN_SIGS&t;(sigmask(SIGKILL)|sigmask(SIGINT)|sigmask(SIGTERM))
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &quot;sd.h&quot;
macro_line|#include &quot;hosts.h&quot;   
singleline_comment|// struct Scsi_Host definition for T handler
macro_line|#include &quot;cpqfcTSchip.h&quot;
macro_line|#include &quot;cpqfcTSstructs.h&quot;
macro_line|#include &quot;cpqfcTStrigger.h&quot;
singleline_comment|//#define LOGIN_DBG 1
singleline_comment|// REMARKS:
singleline_comment|// Since Tachyon chips may be permitted to wait from 500ms up to 2 sec
singleline_comment|// to empty an outgoing frame from its FIFO to the Fibre Channel stream,
singleline_comment|// we cannot do everything we need to in the interrupt handler.  Specifically,
singleline_comment|// every time a link re-init (e.g. LIP) takes place, all SCSI I/O has to be
singleline_comment|// suspended until the login sequences have been completed.  Login commands
singleline_comment|// are frames just like SCSI commands are frames; they are subject to the same
singleline_comment|// timeout issues and delays.  Also, various specs provide up to 2 seconds for
singleline_comment|// devices to log back in (i.e. respond with ACC to a login frame), so I/O to
singleline_comment|// that device has to be suspended.
singleline_comment|// A serious problem here occurs on highly loaded FC-AL systems.  If our FC port
singleline_comment|// has a low priority (e.g. high arbitrated loop physical address, alpa), and
singleline_comment|// some other device is hogging bandwidth (permissible under FC-AL), we might
singleline_comment|// time out thinking the link is hung, when it&squot;s simply busy.  Many such
singleline_comment|// considerations complicate the design.  Although Tachyon assumes control
singleline_comment|// (in silicon) for many link-specific issues, the Linux driver is left with the
singleline_comment|// rest, which turns out to be a difficult, time critical chore.
singleline_comment|// These &quot;worker&quot; functions will handle things like FC Logins; all
singleline_comment|// processes with I/O to our device must wait for the Login to complete
singleline_comment|// and (if successful) I/O to resume.  In the event of a malfunctioning or  
singleline_comment|// very busy loop, it may take hundreds of millisecs or even seconds to complete
singleline_comment|// a frame send.  We don&squot;t want to hang up the entire server (and all
singleline_comment|// processes which don&squot;t depend on Fibre) during this wait.
singleline_comment|// The Tachyon chip can have around 30,000 I/O operations (&quot;exchanges&quot;)
singleline_comment|// open at one time.  However, each exchange must be initiated 
singleline_comment|// synchronously (i.e. each of the 30k I/O had to be started one at a
singleline_comment|// time by sending a starting frame via Tachyon&squot;s outbound que).  
singleline_comment|// To accomodate kernel &quot;module&quot; build, this driver limits the exchanges
singleline_comment|// to 256, because of the contiguous physical memory limitation of 128M.
singleline_comment|// Typical FC Exchanges are opened presuming the FC frames start without errors,
singleline_comment|// while Exchange completion is handled in the interrupt handler.  This
singleline_comment|// optimizes performance for the &quot;everything&squot;s working&quot; case.
singleline_comment|// However, when we have FC related errors or hot plugging of FC ports, we pause
singleline_comment|// I/O and handle FC-specific tasks in the worker thread.  These FC-specific
singleline_comment|// functions will handle things like FC Logins and Aborts.  As the Login sequence
singleline_comment|// completes to each and every target, I/O can resume to that target.  
singleline_comment|// Our kernel &quot;worker thread&quot; must share the HBA with threads calling 
singleline_comment|// &quot;queuecommand&quot;.  We define a &quot;BoardLock&quot; semaphore which indicates
singleline_comment|// to &quot;queuecommand&quot; that the HBA is unavailable, and Cmnds are added to a
singleline_comment|// board lock Q.  When the worker thread finishes with the board, the board
singleline_comment|// lock Q commands are completed with status causing immediate retry.
singleline_comment|// Typically, the board is locked while Logins are in progress after an
singleline_comment|// FC Link Down condition.  When Cmnds are re-queued after board lock, the
singleline_comment|// particular Scsi channel/target may or may not have logged back in.  When
singleline_comment|// the device is waiting for login, the &quot;prli&quot; flag is clear, in which case
singleline_comment|// commands are passed to a Link Down Q.  Whenever the login finally completes,
singleline_comment|// the LinkDown Q is completed, again with status causing immediate retry.
singleline_comment|// When FC devices are logged in, we build and start FC commands to the
singleline_comment|// devices.
singleline_comment|// NOTE!! As of May 2000, kernel 2.2.14, the error recovery logic for devices 
singleline_comment|// that never log back in (e.g. physically removed) is NOT completely
singleline_comment|// understood.  I&squot;ve still seen instances of system hangs on failed Write 
singleline_comment|// commands (possibly from the ext2 layer?) on device removal.  Such special
singleline_comment|// cases need to be evaluated from a system/application view - e.g., how
singleline_comment|// exactly does the system want me to complete commands when the device is
singleline_comment|// physically removed??
singleline_comment|// local functions
r_static
r_void
id|SetLoginFields
c_func
(paren
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
comma
id|TachFCHDR_GCMND
op_star
id|fchs
comma
id|BOOLEAN
id|PDisc
comma
id|BOOLEAN
id|Originator
)paren
suffix:semicolon
r_static
r_void
id|AnalyzeIncomingFrame
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|ULONG
id|QNdx
)paren
suffix:semicolon
r_static
r_void
id|SendLogins
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|__u32
op_star
id|FabricPortIds
)paren
suffix:semicolon
r_static
r_int
id|verify_PLOGI
c_func
(paren
id|PTACHYON
id|fcChip
comma
id|TachFCHDR_GCMND
op_star
id|fchs
comma
id|ULONG
op_star
id|reject_explain
)paren
suffix:semicolon
r_static
r_int
id|verify_PRLI
c_func
(paren
id|TachFCHDR_GCMND
op_star
id|fchs
comma
id|ULONG
op_star
id|reject_explain
)paren
suffix:semicolon
r_static
r_void
id|LoadWWN
c_func
(paren
id|PTACHYON
id|fcChip
comma
id|UCHAR
op_star
id|dest
comma
id|UCHAR
id|type
)paren
suffix:semicolon
r_static
r_void
id|BuildLinkServicePayload
c_func
(paren
id|PTACHYON
id|fcChip
comma
id|ULONG
id|type
comma
r_void
op_star
id|payload
)paren
suffix:semicolon
r_static
r_void
id|UnblockScsiDevice
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|HostAdapter
comma
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
)paren
suffix:semicolon
r_static
r_void
id|cpqfcTSCheckandSnoopFCP
c_func
(paren
id|PTACHYON
id|fcChip
comma
id|ULONG
id|x_ID
)paren
suffix:semicolon
r_static
r_void
id|CompleteBoardLockCmnd
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
)paren
suffix:semicolon
r_static
r_void
id|RevalidateSEST
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|HostAdapter
comma
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
)paren
suffix:semicolon
r_static
r_void
id|IssueReportLunsCommand
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|TachFCHDR_GCMND
op_star
id|fchs
)paren
suffix:semicolon
singleline_comment|// (see scsi_error.c comments on kernel task creation)
DECL|function|cpqfcTSWorkerThread
r_void
id|cpqfcTSWorkerThread
c_func
(paren
r_void
op_star
id|host
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|HostAdapter
op_assign
(paren
r_struct
id|Scsi_Host
op_star
)paren
id|host
suffix:semicolon
id|CPQFCHBA
op_star
id|cpqfcHBAdata
op_assign
(paren
id|CPQFCHBA
op_star
)paren
id|HostAdapter-&gt;hostdata
suffix:semicolon
macro_line|#ifdef PCI_KERNEL_TRACE
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
macro_line|#endif
id|DECLARE_MUTEX_LOCKED
c_func
(paren
id|fcQueReady
)paren
suffix:semicolon
id|DECLARE_MUTEX_LOCKED
c_func
(paren
id|fcTYOBcomplete
)paren
suffix:semicolon
id|DECLARE_MUTEX_LOCKED
c_func
(paren
id|TachFrozen
)paren
suffix:semicolon
id|DECLARE_MUTEX_LOCKED
c_func
(paren
id|BoardLock
)paren
suffix:semicolon
id|ENTER
c_func
(paren
l_string|&quot;WorkerThread&quot;
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|daemonize
c_func
(paren
)paren
suffix:semicolon
id|siginitsetinv
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|SHUTDOWN_SIGS
)paren
suffix:semicolon
multiline_comment|/*&n;   * Set the name of this process.&n;   */
id|sprintf
c_func
(paren
id|current-&gt;comm
comma
l_string|&quot;cpqfcTS_wt_%d&quot;
comma
id|HostAdapter-&gt;host_no
)paren
suffix:semicolon
id|cpqfcHBAdata-&gt;fcQueReady
op_assign
op_amp
id|fcQueReady
suffix:semicolon
singleline_comment|// primary wait point
id|cpqfcHBAdata-&gt;TYOBcomplete
op_assign
op_amp
id|fcTYOBcomplete
suffix:semicolon
id|cpqfcHBAdata-&gt;TachFrozen
op_assign
op_amp
id|TachFrozen
suffix:semicolon
id|cpqfcHBAdata-&gt;worker_thread
op_assign
id|current
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpqfcHBAdata-&gt;notify_wt
op_ne
l_int|NULL
)paren
(brace
id|up
c_func
(paren
id|cpqfcHBAdata-&gt;notify_wt
)paren
suffix:semicolon
)brace
singleline_comment|// OK to continue
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|down_interruptible
c_func
(paren
op_amp
id|fcQueReady
)paren
suffix:semicolon
singleline_comment|// wait for something to do
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_break
suffix:semicolon
id|PCI_TRACE
c_func
(paren
l_int|0x90
)paren
singleline_comment|// first, take the IO lock so the SCSI upper layers can&squot;t call
singleline_comment|// into our _quecommand function (this also disables INTs)
id|spin_lock_irqsave
c_func
(paren
id|HostAdapter-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
singleline_comment|// STOP _que function
id|PCI_TRACE
c_func
(paren
l_int|0x90
)paren
id|CPQ_SPINLOCK_HBA
c_func
(paren
id|cpqfcHBAdata
)paren
singleline_comment|// next, set this pointer to indicate to the _quecommand function
singleline_comment|// that the board is in use, so it should que the command and 
singleline_comment|// immediately return (we don&squot;t actually require the semaphore function
singleline_comment|// in this driver rev)
id|cpqfcHBAdata-&gt;BoardLock
op_assign
op_amp
id|BoardLock
suffix:semicolon
id|PCI_TRACE
c_func
(paren
l_int|0x90
)paren
singleline_comment|// release the IO lock (and re-enable interrupts)
id|spin_unlock_irqrestore
c_func
(paren
id|HostAdapter-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
singleline_comment|// disable OUR HBA interrupt (keep them off as much as possible
singleline_comment|// during error recovery)
id|disable_irq
c_func
(paren
id|cpqfcHBAdata-&gt;HostAdapter-&gt;irq
)paren
suffix:semicolon
singleline_comment|// OK, let&squot;s process the Fibre Channel Link Q and do the work
id|cpqfcTS_WorkTask
c_func
(paren
id|HostAdapter
)paren
suffix:semicolon
singleline_comment|// hopefully, no more &quot;work&quot; to do;
singleline_comment|// re-enable our INTs for &quot;normal&quot; completion processing
id|enable_irq
c_func
(paren
id|cpqfcHBAdata-&gt;HostAdapter-&gt;irq
)paren
suffix:semicolon
id|cpqfcHBAdata-&gt;BoardLock
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|// allow commands to be queued
id|CPQ_SPINUNLOCK_HBA
c_func
(paren
id|cpqfcHBAdata
)paren
singleline_comment|// Now, complete any Cmnd we Q&squot;d up while BoardLock was held
id|CompleteBoardLockCmnd
c_func
(paren
id|cpqfcHBAdata
)paren
suffix:semicolon
)brace
singleline_comment|// hopefully, the signal was for our module exit...
r_if
c_cond
(paren
id|cpqfcHBAdata-&gt;notify_wt
op_ne
l_int|NULL
)paren
(brace
id|up
c_func
(paren
id|cpqfcHBAdata-&gt;notify_wt
)paren
suffix:semicolon
)brace
singleline_comment|// yep, we&squot;re outta here
)brace
singleline_comment|// Freeze Tachyon routine.
singleline_comment|// If Tachyon is already frozen, return FALSE
singleline_comment|// If Tachyon is not frozen, call freeze function, return TRUE
singleline_comment|//
DECL|function|FreezeTach
r_static
id|BOOLEAN
id|FreezeTach
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
)paren
(brace
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
id|BOOLEAN
id|FrozeTach
op_assign
id|FALSE
suffix:semicolon
singleline_comment|// It&squot;s possible that the chip is already frozen; if so,
singleline_comment|// &quot;Freezing&quot; again will NOT! generate another Freeze
singleline_comment|// Completion Message.
r_if
c_cond
(paren
(paren
id|fcChip-&gt;Registers.TYstatus.value
op_amp
l_int|0x70000
)paren
op_ne
l_int|0x70000
)paren
(brace
singleline_comment|// (need to freeze...)
id|fcChip
op_member_access_from_pointer
id|FreezeTachyon
c_func
(paren
id|fcChip
comma
l_int|2
)paren
suffix:semicolon
singleline_comment|// both ERQ and FCP assists
singleline_comment|// 2. Get Tach freeze confirmation
singleline_comment|// (synchronize SEST manipulation with Freeze Completion Message)
singleline_comment|// we need INTs on so semaphore can be set.&t;
id|enable_irq
c_func
(paren
id|cpqfcHBAdata-&gt;HostAdapter-&gt;irq
)paren
suffix:semicolon
singleline_comment|// only way to get Semaphore
id|down_interruptible
c_func
(paren
id|cpqfcHBAdata-&gt;TachFrozen
)paren
suffix:semicolon
singleline_comment|// wait for INT handler sem.
singleline_comment|// can we TIMEOUT semaphore wait?? TBD
id|disable_irq
c_func
(paren
id|cpqfcHBAdata-&gt;HostAdapter-&gt;irq
)paren
suffix:semicolon
id|FrozeTach
op_assign
id|TRUE
suffix:semicolon
)brace
singleline_comment|// (else, already frozen)
r_return
id|FrozeTach
suffix:semicolon
)brace
singleline_comment|// This is the kernel worker thread task, which processes FC
singleline_comment|// tasks which were queued by the Interrupt handler or by
singleline_comment|// other WorkTask functions.
DECL|macro|DBG
mdefine_line|#define DBG 1
singleline_comment|//#undef DBG
DECL|function|cpqfcTS_WorkTask
r_void
id|cpqfcTS_WorkTask
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|HostAdapter
)paren
(brace
id|CPQFCHBA
op_star
id|cpqfcHBAdata
op_assign
(paren
id|CPQFCHBA
op_star
)paren
id|HostAdapter-&gt;hostdata
suffix:semicolon
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
id|FC_EXCHANGES
op_star
id|Exchanges
op_assign
id|fcChip-&gt;Exchanges
suffix:semicolon
id|ULONG
id|QconsumerNdx
suffix:semicolon
id|LONG
id|ExchangeID
suffix:semicolon
id|ULONG
id|ulStatus
op_assign
l_int|0
suffix:semicolon
id|TachFCHDR_GCMND
id|fchs
suffix:semicolon
id|PFC_LINK_QUE
id|fcLQ
op_assign
id|cpqfcHBAdata-&gt;fcLQ
suffix:semicolon
id|ENTER
c_func
(paren
l_string|&quot;WorkTask&quot;
)paren
suffix:semicolon
singleline_comment|// copy current index to work on
id|QconsumerNdx
op_assign
id|fcLQ-&gt;consumer
suffix:semicolon
id|PCI_TRACEO
c_func
(paren
id|fcLQ-&gt;Qitem
(braket
id|QconsumerNdx
)braket
dot
id|Type
comma
l_int|0x90
)paren
singleline_comment|// NOTE: when this switch completes, we will &quot;consume&quot; the Que item
singleline_comment|//  printk(&quot;Que type %Xh&bslash;n&quot;, fcLQ-&gt;Qitem[QconsumerNdx].Type);
r_switch
c_cond
(paren
id|fcLQ-&gt;Qitem
(braket
id|QconsumerNdx
)braket
dot
id|Type
)paren
(brace
singleline_comment|// incoming frame - link service (ACC, UNSOL REQ, etc.)
singleline_comment|// or FCP-SCSI command
r_case
id|SFQ_UNKNOWN
suffix:colon
id|AnalyzeIncomingFrame
c_func
(paren
id|cpqfcHBAdata
comma
id|QconsumerNdx
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EXCHANGE_QUEUED
suffix:colon
singleline_comment|// an Exchange (i.e. FCP-SCSI) was previously
singleline_comment|// Queued because the link was down.  The  
singleline_comment|// heartbeat timer detected it and Queued it here.
singleline_comment|// We attempt to start it again, and if
singleline_comment|// successful we clear the EXCHANGE_Q flag.
singleline_comment|// If the link doesn&squot;t come up, the Exchange
singleline_comment|// will eventually time-out.
id|ExchangeID
op_assign
(paren
id|LONG
)paren
singleline_comment|// x_ID copied from DPC timeout function
id|fcLQ-&gt;Qitem
(braket
id|QconsumerNdx
)braket
dot
id|ulBuff
(braket
l_int|0
)braket
suffix:semicolon
singleline_comment|// It&squot;s possible that a Q&squot;d exchange could have already
singleline_comment|// been started by other logic (e.g. ABTS process)
singleline_comment|// Don&squot;t start if already started (Q&squot;d flag clear)
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
dot
id|status
op_amp
id|EXCHANGE_QUEUED
)paren
(brace
singleline_comment|//        printk(&quot; *Start Q&squot;d x_ID %Xh: type %Xh &quot;, 
singleline_comment|//          ExchangeID, Exchanges-&gt;fcExchange[ExchangeID].type);
id|ulStatus
op_assign
id|cpqfcTSStartExchange
c_func
(paren
id|cpqfcHBAdata
comma
id|ExchangeID
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ulStatus
)paren
(brace
singleline_comment|//          printk(&quot;success* &quot;);
)brace
r_else
(brace
macro_line|#ifdef DBG
r_if
c_cond
(paren
id|ulStatus
op_eq
id|EXCHANGE_QUEUED
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Queued* &quot;
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;failed* &quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
r_break
suffix:semicolon
r_case
id|LINKDOWN
suffix:colon
singleline_comment|// (lots of things already done in INT handler) future here?
r_break
suffix:semicolon
r_case
id|LINKACTIVE
suffix:colon
singleline_comment|// Tachyon set the Lup bit in FM status
singleline_comment|// NOTE: some misbehaving FC ports (like Tach2.1)
singleline_comment|// can re-LIP immediately after a LIP completes.
singleline_comment|// if &quot;initiator&quot;, need to verify LOGs with ports
singleline_comment|//      printk(&quot;&bslash;n*LNKUP* &quot;);
r_if
c_cond
(paren
id|fcChip-&gt;Options.initiator
)paren
(brace
id|SendLogins
c_func
(paren
id|cpqfcHBAdata
comma
l_int|NULL
)paren
suffix:semicolon
)brace
singleline_comment|// PLOGI or PDISC, based on fcPort data
singleline_comment|// if SendLogins successfully completes, PortDiscDone
singleline_comment|// will be set.
singleline_comment|// If SendLogins was successful, then we expect to get incoming
singleline_comment|// ACCepts or REJECTs, which are handled below.
r_break
suffix:semicolon
singleline_comment|// LinkService and Fabric request/reply processing
r_case
id|ELS_FDISC
suffix:colon
singleline_comment|// need to send Fabric Discovery (Login)
r_case
id|ELS_FLOGI
suffix:colon
singleline_comment|// need to send Fabric Login
r_case
id|ELS_SCR
suffix:colon
singleline_comment|// need to send State Change Registration
r_case
id|FCS_NSR
suffix:colon
singleline_comment|// need to send Name Service Request
r_case
id|ELS_PLOGI
suffix:colon
singleline_comment|// need to send PLOGI
r_case
id|ELS_ACC
suffix:colon
singleline_comment|// send generic ACCept
r_case
id|ELS_PLOGI_ACC
suffix:colon
singleline_comment|// need to send ELS ACCept frame to recv&squot;d PLOGI
r_case
id|ELS_PRLI_ACC
suffix:colon
singleline_comment|// need to send ELS ACCept frame to recv&squot;d PRLI
r_case
id|ELS_LOGO
suffix:colon
singleline_comment|// need to send ELS LOGO (logout)
r_case
id|ELS_LOGO_ACC
suffix:colon
singleline_comment|// need to send ELS ACCept frame to recv&squot;d PLOGI
r_case
id|ELS_RJT
suffix:colon
singleline_comment|// ReJecT reply
r_case
id|ELS_PRLI
suffix:colon
singleline_comment|// need to send ELS PRLI
singleline_comment|//      printk(&quot; *ELS %Xh* &quot;, fcLQ-&gt;Qitem[QconsumerNdx].Type);
singleline_comment|// if PortDiscDone is not set, it means the SendLogins routine
singleline_comment|// failed to complete -- assume that LDn occurred, so login frames
singleline_comment|// are invalid
r_if
c_cond
(paren
op_logical_neg
id|cpqfcHBAdata-&gt;PortDiscDone
)paren
singleline_comment|// cleared by LDn
(brace
id|printk
c_func
(paren
l_string|&quot;Discard Q&squot;d ELS login frame&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ulStatus
op_assign
id|cpqfcTSBuildExchange
c_func
(paren
id|cpqfcHBAdata
comma
id|fcLQ-&gt;Qitem
(braket
id|QconsumerNdx
)braket
dot
id|Type
comma
singleline_comment|// e.g. PLOGI
(paren
id|TachFCHDR_GCMND
op_star
)paren
id|fcLQ-&gt;Qitem
(braket
id|QconsumerNdx
)braket
dot
id|ulBuff
comma
singleline_comment|// incoming fchs
l_int|NULL
comma
singleline_comment|// no data (no scatter/gather list)
op_amp
id|ExchangeID
)paren
suffix:semicolon
singleline_comment|// fcController-&gt;fcExchanges index, -1 if failed
r_if
c_cond
(paren
op_logical_neg
id|ulStatus
)paren
singleline_comment|// Exchange setup?
(brace
id|ulStatus
op_assign
id|cpqfcTSStartExchange
c_func
(paren
id|cpqfcHBAdata
comma
id|ExchangeID
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ulStatus
)paren
(brace
singleline_comment|// submitted to Tach&squot;s Outbound Que (ERQ PI incremented)
singleline_comment|// waited for completion for ELS type (Login frames issued
singleline_comment|// synchronously)
)brace
r_else
singleline_comment|// check reason for Exchange not being started - we might
singleline_comment|// want to Queue and start later, or fail with error
(brace
)brace
)brace
r_else
singleline_comment|// Xchange setup failed...
id|printk
c_func
(paren
l_string|&quot; cpqfcTSBuildExchange failed: %Xh&bslash;n&quot;
comma
id|ulStatus
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCSI_REPORT_LUNS
suffix:colon
singleline_comment|// pass the incoming frame (actually, it&squot;s a PRLI frame)
singleline_comment|// so we can send REPORT_LUNS, in order to determine VSA/PDU
singleline_comment|// FCP-SCSI Lun address mode
id|IssueReportLunsCommand
c_func
(paren
id|cpqfcHBAdata
comma
(paren
id|TachFCHDR_GCMND
op_star
)paren
id|fcLQ-&gt;Qitem
(braket
id|QconsumerNdx
)braket
dot
id|ulBuff
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BLS_ABTS
suffix:colon
singleline_comment|// need to ABORT one or more exchanges
(brace
id|LONG
id|x_ID
op_assign
id|fcLQ-&gt;Qitem
(braket
id|QconsumerNdx
)braket
dot
id|ulBuff
(braket
l_int|0
)braket
suffix:semicolon
id|BOOLEAN
id|FrozeTach
op_assign
id|FALSE
suffix:semicolon
r_if
c_cond
(paren
id|x_ID
OG
id|TACH_SEST_LEN
)paren
singleline_comment|// (in)sanity check
(brace
singleline_comment|//&t;printk( &quot; cpqfcTS ERROR! BOGUS x_ID %Xh&quot;, x_ID);
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd
op_eq
l_int|NULL
)paren
singleline_comment|// should be RARE
(brace
singleline_comment|//&t;printk(&quot; ABTS %Xh Scsi Cmnd null! &quot;, x_ID);
r_break
suffix:semicolon
singleline_comment|// nothing to abort!
)brace
singleline_comment|//#define ABTS_DBG
macro_line|#ifdef ABTS_DBG
id|printk
c_func
(paren
l_string|&quot;INV SEST[%X] &quot;
comma
id|x_ID
)paren
suffix:semicolon
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|FC2_TIMEOUT
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;FC2TO&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|INITIATOR_ABORT
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;IA&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|PORTID_CHANGED
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PORTID&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|DEVICE_REMOVED
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;DEVRM&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|LINKFAIL_TX
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;LKF&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|FRAME_TO
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;FRMTO&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|ABORTSEQ_NOTIFY
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ABSQ&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|SFQ_FRAME
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SFQFR&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|type
op_eq
l_int|0x2000
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; WR&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|type
op_eq
l_int|0x3000
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; RD&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|type
op_eq
l_int|0x10
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; ABTS&quot;
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot; %Xh&quot;
comma
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|INITIATOR_ABORT
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; Cmd %p, &quot;
comma
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; brd/chn/trg/lun %d/%d/%d/%d port_id %06X&bslash;n&quot;
comma
id|cpqfcHBAdata-&gt;HBAnum
comma
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;channel
comma
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;target
comma
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;lun
comma
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|fchs.d_id
op_amp
l_int|0xFFFFFF
)paren
suffix:semicolon
)brace
r_else
singleline_comment|// assume that Cmnd ptr is invalid on _abort()
(brace
id|printk
c_func
(paren
l_string|&quot; Cmd ptr invalid&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif      
singleline_comment|// Steps to ABORT a SEST exchange:
singleline_comment|// 1. Freeze TL SCSI assists &amp; ERQ (everything)
singleline_comment|// 2. Receive FROZEN inbound CM (must succeed!)
singleline_comment|// 3. Invalidate x_ID SEST entry 
singleline_comment|// 4. Resume TL SCSI assists &amp; ERQ (everything)
singleline_comment|// 5. Build/start on exchange - change &quot;type&quot; to BLS_ABTS,
singleline_comment|//    timeout to X sec (RA_TOV from PLDA is actually 0)
singleline_comment|// 6. Set Exchange Q&squot;d status if ABTS cannot be started,
singleline_comment|//    or simply complete Exchange in &quot;Terminate&quot; condition
id|PCI_TRACEO
c_func
(paren
id|x_ID
comma
l_int|0xB4
)paren
singleline_comment|// 1 &amp; 2 . Freeze Tach &amp; get confirmation of freeze
id|FrozeTach
op_assign
id|FreezeTach
c_func
(paren
id|cpqfcHBAdata
)paren
suffix:semicolon
singleline_comment|// 3. OK, Tachyon is frozen, so we can invalidate SEST exchange.
singleline_comment|// FC2_TIMEOUT means we are originating the abort, while
singleline_comment|// TARGET_ABORT means we are ACCepting an abort.
singleline_comment|// LINKFAIL_TX, ABORTSEQ_NOFITY, INV_ENTRY or FRAME_TO are 
singleline_comment|// all from Tachyon:
singleline_comment|// Exchange was corrupted by LDn or other FC physical failure
singleline_comment|// INITIATOR_ABORT means the upper layer driver/application
singleline_comment|// requested the abort.
singleline_comment|// clear bit 31 (VALid), to invalidate &amp; take control from TL
id|fcChip-&gt;SEST-&gt;u
(braket
id|x_ID
)braket
dot
id|IWE.Hdr_Len
op_and_assign
l_int|0x7FFFFFFF
suffix:semicolon
singleline_comment|// examine and Tach&squot;s &quot;Linked List&quot; for IWEs that 
singleline_comment|// received (nearly) simultaneous transfer ready (XRDY) 
singleline_comment|// repair linked list if necessary (TBD!)
singleline_comment|// (If we ignore the &quot;Linked List&quot;, we will time out
singleline_comment|// WRITE commands where we received the FCP-SCSI XFRDY
singleline_comment|// frame (because Tachyon didn&squot;t processes it).  Linked List
singleline_comment|// management should be done as an optimization.
singleline_comment|//       readl( fcChip-&gt;Registers.ReMapMemBase+TL_MEM_SEST_LINKED_LIST ));
singleline_comment|// 4. Resume all Tachlite functions (for other open Exchanges)
singleline_comment|// as quickly as possible to allow other exchanges to other ports
singleline_comment|// to resume.  Freezing Tachyon may cause cascading errors, because
singleline_comment|// any received SEST frame cannot be processed by the SEST.
singleline_comment|// Don&squot;t &quot;unfreeze&quot; unless Link is operational
r_if
c_cond
(paren
id|FrozeTach
)paren
(brace
singleline_comment|// did we just freeze it (above)?
id|fcChip
op_member_access_from_pointer
id|UnFreezeTachyon
c_func
(paren
id|fcChip
comma
l_int|2
)paren
suffix:semicolon
)brace
singleline_comment|// both ERQ and FCP assists
id|PCI_TRACEO
c_func
(paren
id|x_ID
comma
l_int|0xB4
)paren
singleline_comment|// Note there is no confirmation that the chip is &quot;unfrozen&quot;.  Also,
singleline_comment|// if the Link is down when unfreeze is called, it has no effect.
singleline_comment|// Chip will unfreeze when the Link is back up.
singleline_comment|// 5. Now send out Abort commands if possible
singleline_comment|// Some Aborts can&squot;t be &quot;sent&quot; (Port_id changed or gone);
singleline_comment|// if the device is gone, there is no port_id to send the ABTS to.
r_if
c_cond
(paren
op_logical_neg
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|PORTID_CHANGED
)paren
op_logical_and
op_logical_neg
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|DEVICE_REMOVED
)paren
)paren
(brace
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|type
op_assign
id|BLS_ABTS
suffix:semicolon
id|fchs.s_id
op_assign
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|fchs.d_id
suffix:semicolon
id|ulStatus
op_assign
id|cpqfcTSBuildExchange
c_func
(paren
id|cpqfcHBAdata
comma
id|BLS_ABTS
comma
op_amp
id|fchs
comma
singleline_comment|// (uses only s_id)
l_int|NULL
comma
singleline_comment|// (no scatter/gather list for ABTS)
op_amp
id|x_ID
)paren
suffix:semicolon
singleline_comment|// ABTS on this Exchange ID
r_if
c_cond
(paren
op_logical_neg
id|ulStatus
)paren
singleline_comment|// Exchange setup build OK?
(brace
singleline_comment|// ABTS may be needed because an Exchange was corrupted
singleline_comment|// by a Link disruption.  If the Link is UP, we can
singleline_comment|// presume that this ABTS can start immediately; otherwise,
singleline_comment|// set Que&squot;d status so the Login functions
singleline_comment|// can restart it when the FC physical Link is restored
r_if
c_cond
(paren
(paren
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0xF0
)paren
op_amp
l_int|0x80
)paren
)paren
singleline_comment|// loop init?
(brace
singleline_comment|//                printk(&quot; *set Q status x_ID %Xh on LDn* &quot;, x_ID);
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_or_assign
id|EXCHANGE_QUEUED
suffix:semicolon
)brace
r_else
singleline_comment|// what FC device (port_id) does the Cmd belong to?
(brace
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
op_assign
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|pLoggedInPort
suffix:semicolon
singleline_comment|// if Port is logged in, we might start the abort.
r_if
c_cond
(paren
(paren
id|pLoggedInPort
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|pLoggedInPort-&gt;prli
op_eq
id|TRUE
)paren
)paren
(brace
singleline_comment|// it&squot;s possible that an Exchange has already been Queued
singleline_comment|// to start after Login completes.  Check and don&squot;t
singleline_comment|// start it (again) here if Q&squot;d status set
singleline_comment|//&t;    printk(&quot; ABTS xchg %Xh &quot;, x_ID);            
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|EXCHANGE_QUEUED
)paren
(brace
singleline_comment|//&t;&t;    printk(&quot;already Q&squot;d &quot;);
)brace
r_else
(brace
singleline_comment|//&t;            printk(&quot;starting &quot;);
id|fcChip-&gt;fcStats.FC2aborted
op_increment
suffix:semicolon
id|ulStatus
op_assign
id|cpqfcTSStartExchange
c_func
(paren
id|cpqfcHBAdata
comma
id|x_ID
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ulStatus
)paren
(brace
singleline_comment|// OK
singleline_comment|// submitted to Tach&squot;s Outbound Que (ERQ PI incremented)
)brace
r_else
(brace
multiline_comment|/*                   printk(&quot;ABTS exchange start failed -status %Xh, x_ID %Xh &quot;,&n;                        ulStatus, x_ID);&n;*/
)brace
)brace
)brace
r_else
(brace
multiline_comment|/*         &t;  printk(&quot; ABTS NOT starting xchg %Xh, %p &quot;,&n;&t;&t;&t;       x_ID, pLoggedInPort);&n;&t;          if( pLoggedInPort )&n;&t;            printk(&quot;prli %d &quot;, pLoggedInPort-&gt;prli);&n;*/
)brace
)brace
)brace
r_else
singleline_comment|// what the #@!
(brace
singleline_comment|// how do we fail to build an Exchange for ABTS??
id|printk
c_func
(paren
l_string|&quot;ABTS exchange build failed -status %Xh, x_ID %Xh&bslash;n&quot;
comma
id|ulStatus
comma
id|x_ID
)paren
suffix:semicolon
)brace
)brace
r_else
singleline_comment|// abort without ABTS -- just complete exchange/Cmnd to Linux
(brace
singleline_comment|//            printk(&quot; *Terminating x_ID %Xh on %Xh* &quot;, 
singleline_comment|//&t;&t;    x_ID, Exchanges-&gt;fcExchange[x_ID].status);
id|cpqfcTSCompleteExchange
c_func
(paren
id|cpqfcHBAdata-&gt;PciDev
comma
id|fcChip
comma
id|x_ID
)paren
suffix:semicolon
)brace
)brace
singleline_comment|// end of ABTS case
r_break
suffix:semicolon
r_case
id|BLS_ABTS_ACC
suffix:colon
singleline_comment|// need to ACCept one ABTS
singleline_comment|// (NOTE! this code not updated for Linux yet..)
id|printk
c_func
(paren
l_string|&quot; *ABTS_ACC* &quot;
)paren
suffix:semicolon
singleline_comment|// 1. Freeze TL
id|fcChip
op_member_access_from_pointer
id|FreezeTachyon
c_func
(paren
id|fcChip
comma
l_int|2
)paren
suffix:semicolon
singleline_comment|// both ERQ and FCP assists
id|memcpy
c_func
(paren
singleline_comment|// copy the incoming ABTS frame
op_amp
id|fchs
comma
id|fcLQ-&gt;Qitem
(braket
id|QconsumerNdx
)braket
dot
id|ulBuff
comma
singleline_comment|// incoming fchs
r_sizeof
(paren
id|fchs
)paren
)paren
suffix:semicolon
singleline_comment|// 3. OK, Tachyon is frozen so we can invalidate SEST entry 
singleline_comment|// (if necessary)
singleline_comment|// Status FC2_TIMEOUT means we are originating the abort, while
singleline_comment|// TARGET_ABORT means we are ACCepting an abort
id|ExchangeID
op_assign
id|fchs.ox_rx_id
op_amp
l_int|0x7FFF
suffix:semicolon
singleline_comment|// RX_ID for exchange
singleline_comment|//      printk(&quot;ABTS ACC for Target ExchangeID %Xh&bslash;n&quot;, ExchangeID);
singleline_comment|// sanity check on received ExchangeID
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
dot
id|status
op_eq
id|TARGET_ABORT
)paren
(brace
singleline_comment|// clear bit 31 (VALid), to invalidate &amp; take control from TL
singleline_comment|//          printk(&quot;Invalidating SEST exchange %Xh&bslash;n&quot;, ExchangeID);
id|fcChip-&gt;SEST-&gt;u
(braket
id|ExchangeID
)braket
dot
id|IWE.Hdr_Len
op_and_assign
l_int|0x7FFFFFFF
suffix:semicolon
)brace
singleline_comment|// 4. Resume all Tachlite functions (for other open Exchanges)
singleline_comment|// as quickly as possible to allow other exchanges to other ports
singleline_comment|// to resume.  Freezing Tachyon for too long may royally screw
singleline_comment|// up everything!
id|fcChip
op_member_access_from_pointer
id|UnFreezeTachyon
c_func
(paren
id|fcChip
comma
l_int|2
)paren
suffix:semicolon
singleline_comment|// both ERQ and FCP assists
singleline_comment|// Note there is no confirmation that the chip is &quot;unfrozen&quot;.  Also,
singleline_comment|// if the Link is down when unfreeze is called, it has no effect.
singleline_comment|// Chip will unfreeze when the Link is back up.
singleline_comment|// 5. Now send out Abort ACC reply for this exchange
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
dot
id|type
op_assign
id|BLS_ABTS_ACC
suffix:semicolon
id|fchs.s_id
op_assign
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
dot
id|fchs.d_id
suffix:semicolon
id|ulStatus
op_assign
id|cpqfcTSBuildExchange
c_func
(paren
id|cpqfcHBAdata
comma
id|BLS_ABTS_ACC
comma
op_amp
id|fchs
comma
l_int|NULL
comma
singleline_comment|// no data (no scatter/gather list)
op_amp
id|ExchangeID
)paren
suffix:semicolon
singleline_comment|// fcController-&gt;fcExchanges index, -1 if failed
r_if
c_cond
(paren
op_logical_neg
id|ulStatus
)paren
singleline_comment|// Exchange setup?
(brace
id|ulStatus
op_assign
id|cpqfcTSStartExchange
c_func
(paren
id|cpqfcHBAdata
comma
id|ExchangeID
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ulStatus
)paren
(brace
singleline_comment|// submitted to Tach&squot;s Outbound Que (ERQ PI incremented)
singleline_comment|// waited for completion for ELS type (Login frames issued
singleline_comment|// synchronously)
)brace
r_else
singleline_comment|// check reason for Exchange not being started - we might
singleline_comment|// want to Queue and start later, or fail with error
(brace
)brace
)brace
r_break
suffix:semicolon
r_case
id|BLS_ABTS_RJT
suffix:colon
singleline_comment|// need to ReJecT one ABTS; reject implies the
singleline_comment|// exchange doesn&squot;t exist in the TARGET context.
singleline_comment|// ExchangeID has to come from LinkService space.
id|printk
c_func
(paren
l_string|&quot; *ABTS_RJT* &quot;
)paren
suffix:semicolon
id|ulStatus
op_assign
id|cpqfcTSBuildExchange
c_func
(paren
id|cpqfcHBAdata
comma
id|BLS_ABTS_RJT
comma
(paren
id|TachFCHDR_GCMND
op_star
)paren
id|fcLQ-&gt;Qitem
(braket
id|QconsumerNdx
)braket
dot
id|ulBuff
comma
singleline_comment|// incoming fchs
l_int|NULL
comma
singleline_comment|// no data (no scatter/gather list)
op_amp
id|ExchangeID
)paren
suffix:semicolon
singleline_comment|// fcController-&gt;fcExchanges index, -1 if failed
r_if
c_cond
(paren
op_logical_neg
id|ulStatus
)paren
singleline_comment|// Exchange setup OK?
(brace
id|ulStatus
op_assign
id|cpqfcTSStartExchange
c_func
(paren
id|cpqfcHBAdata
comma
id|ExchangeID
)paren
suffix:semicolon
singleline_comment|// If it fails, we aren&squot;t required to retry.
)brace
r_if
c_cond
(paren
id|ulStatus
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to send BLS_RJT for ABTS, X_ID %Xh&bslash;n&quot;
comma
id|ExchangeID
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;Sent BLS_RJT for ABTS, X_ID %Xh&bslash;n&quot;
comma
id|ExchangeID
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
singleline_comment|// end switch
singleline_comment|//doNothing:
singleline_comment|// done with this item - now set the NEXT index
r_if
c_cond
(paren
id|QconsumerNdx
op_plus
l_int|1
op_ge
id|FC_LINKQ_DEPTH
)paren
singleline_comment|// rollover test
(brace
id|fcLQ-&gt;consumer
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|fcLQ-&gt;consumer
op_increment
suffix:semicolon
)brace
id|PCI_TRACEO
c_func
(paren
id|fcLQ-&gt;Qitem
(braket
id|QconsumerNdx
)braket
dot
id|Type
comma
l_int|0x94
)paren
id|LEAVE
c_func
(paren
l_string|&quot;WorkTask&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
singleline_comment|// When Tachyon reports link down, bad al_pa, or Link Service (e.g. Login)
singleline_comment|// commands come in, post to the LinkQ so that action can be taken outside the
singleline_comment|// interrupt handler.  
singleline_comment|// This circular Q works like Tachyon&squot;s que - the producer points to the next
singleline_comment|// (unused) entry.  Called by Interrupt handler, WorkerThread, Timer
singleline_comment|// sputlinkq
DECL|function|cpqfcTSPutLinkQue
r_void
id|cpqfcTSPutLinkQue
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
r_int
id|Type
comma
r_void
op_star
id|QueContent
)paren
(brace
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
singleline_comment|//  FC_EXCHANGES *Exchanges = fcChip-&gt;Exchanges;
id|PFC_LINK_QUE
id|fcLQ
op_assign
id|cpqfcHBAdata-&gt;fcLQ
suffix:semicolon
id|ULONG
id|ndx
suffix:semicolon
id|ENTER
c_func
(paren
l_string|&quot;cpqfcTSPutLinkQ&quot;
)paren
suffix:semicolon
id|ndx
op_assign
id|fcLQ-&gt;producer
suffix:semicolon
id|ndx
op_add_assign
l_int|1
suffix:semicolon
singleline_comment|// test for Que full
r_if
c_cond
(paren
id|ndx
op_ge
id|FC_LINKQ_DEPTH
)paren
(brace
singleline_comment|// rollover test
id|ndx
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ndx
op_eq
id|fcLQ-&gt;consumer
)paren
singleline_comment|// QUE full test
(brace
singleline_comment|// QUE was full! lost LK command (fatal to logic)
id|fcChip-&gt;fcStats.lnkQueFull
op_increment
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;*LinkQ Full!*&quot;
)paren
suffix:semicolon
id|TriggerHBA
c_func
(paren
id|fcChip-&gt;Registers.ReMapMemBase
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;    {&n;      int i;&n;      printk(&quot;LinkQ PI %d, CI %d&bslash;n&quot;, fcLQ-&gt;producer,&n;        fcLQ-&gt;consumer);&n;&t;&t;      &n;      for( i=0; i&lt; FC_LINKQ_DEPTH; )&n;      {&n;&t;printk(&quot; [%d]%Xh &quot;, i, fcLQ-&gt;Qitem[i].Type);&n;&t;if( (++i %8) == 0) printk(&quot;&bslash;n&quot;);&n;      }&n;  &n;    }&n;*/
id|printk
c_func
(paren
l_string|&quot;cpqfcTS: WARNING!! PutLinkQue - FULL!&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|// we&squot;re hung
)brace
r_else
singleline_comment|// QUE next element
(brace
singleline_comment|// Prevent certain multiple (back-to-back) requests.
singleline_comment|// This is important in that we don&squot;t want to issue multiple
singleline_comment|// ABTS for the same Exchange, or do multiple FM inits, etc.
singleline_comment|// We can never be sure of the timing of events reported to
singleline_comment|// us by Tach&squot;s IMQ, which can depend on system/bus speeds,
singleline_comment|// FC physical link circumstances, etc.
r_if
c_cond
(paren
(paren
id|fcLQ-&gt;producer
op_ne
id|fcLQ-&gt;consumer
)paren
op_logical_and
(paren
id|Type
op_eq
id|FMINIT
)paren
)paren
(brace
id|LONG
id|lastNdx
suffix:semicolon
singleline_comment|// compute previous producer index
r_if
c_cond
(paren
id|fcLQ-&gt;producer
)paren
(brace
id|lastNdx
op_assign
id|fcLQ-&gt;producer
op_minus
l_int|1
suffix:semicolon
)brace
r_else
id|lastNdx
op_assign
id|FC_LINKQ_DEPTH
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|fcLQ-&gt;Qitem
(braket
id|lastNdx
)braket
dot
id|Type
op_eq
id|FMINIT
)paren
(brace
singleline_comment|//        printk(&quot; *skip FMINIT Q post* &quot;);
singleline_comment|//        goto DoneWithPutQ;
)brace
)brace
singleline_comment|// OK, add the Q&squot;d item...
id|fcLQ-&gt;Qitem
(braket
id|fcLQ-&gt;producer
)braket
dot
id|Type
op_assign
id|Type
suffix:semicolon
id|memcpy
c_func
(paren
id|fcLQ-&gt;Qitem
(braket
id|fcLQ-&gt;producer
)braket
dot
id|ulBuff
comma
id|QueContent
comma
r_sizeof
(paren
id|fcLQ-&gt;Qitem
(braket
id|fcLQ-&gt;producer
)braket
dot
id|ulBuff
)paren
)paren
suffix:semicolon
id|fcLQ-&gt;producer
op_assign
id|ndx
suffix:semicolon
singleline_comment|// increment Que producer
singleline_comment|// set semaphore to wake up Kernel (worker) thread
singleline_comment|// 
id|up
c_func
(paren
id|cpqfcHBAdata-&gt;fcQueReady
)paren
suffix:semicolon
)brace
singleline_comment|//DoneWithPutQ:
id|LEAVE
c_func
(paren
l_string|&quot;cpqfcTSPutLinkQ&quot;
)paren
suffix:semicolon
)brace
singleline_comment|// reset device ext FC link Q
DECL|function|cpqfcTSLinkQReset
r_void
id|cpqfcTSLinkQReset
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
)paren
(brace
id|PFC_LINK_QUE
id|fcLQ
op_assign
id|cpqfcHBAdata-&gt;fcLQ
suffix:semicolon
id|fcLQ-&gt;producer
op_assign
l_int|0
suffix:semicolon
id|fcLQ-&gt;consumer
op_assign
l_int|0
suffix:semicolon
)brace
singleline_comment|// When Tachyon gets an unassisted FCP-SCSI frame, post here so
singleline_comment|// an arbitrary context thread (e.g. IOCTL loopback test function)
singleline_comment|// can process it.
singleline_comment|// (NOTE: Not revised for Linux)
singleline_comment|// This Q works like Tachyon&squot;s que - the producer points to the next
singleline_comment|// (unused) entry.
DECL|function|cpqfcTSPutScsiQue
r_void
id|cpqfcTSPutScsiQue
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
r_int
id|Type
comma
r_void
op_star
id|QueContent
)paren
(brace
singleline_comment|//  CPQFCHBA *cpqfcHBAdata = (CPQFCHBA *)HostAdapter-&gt;hostdata;
singleline_comment|//  PTACHYON fcChip = &amp;cpqfcHBAdata-&gt;fcChip;
singleline_comment|//  ULONG ndx;
singleline_comment|//  ULONG *pExchangeID;
singleline_comment|//  LONG ExchangeID;
multiline_comment|/*&n;  KeAcquireSpinLockAtDpcLevel( &amp;pDevExt-&gt;fcScsiQueLock);&n;  ndx = pDevExt-&gt;fcScsiQue.producer + 1;  // test for Que full&n;&n;  if( ndx &gt;= FC_SCSIQ_DEPTH ) // rollover test&n;    ndx = 0;&n;&n;  if( ndx == pDevExt-&gt;fcScsiQue.consumer )   // QUE full test&n;  {&n;                       // QUE was full! lost LK command (fatal to logic)&n;    fcChip-&gt;fcStats.ScsiQueFull++;&n;#ifdef DBG&n;    printk( &quot;fcPutScsiQue - FULL!&bslash;n&quot;);&n;#endif&n;&n;  }&n;  else                        // QUE next element&n;  {&n;    pDevExt-&gt;fcScsiQue.Qitem[pDevExt-&gt;fcScsiQue.producer].Type = Type;&n;    &n;    if( Type == FCP_RSP )&n;    {&n;      // this TL inbound message type means that a TL SEST exchange has&n;      // copied an FCP response frame into a buffer pointed to by the SEST&n;      // entry.  That buffer is allocated in the SEST structure at -&gt;RspHDR.&n;      // Copy the RspHDR for use by the Que handler.&n;      pExchangeID = (ULONG *)QueContent;&n;      &n;      memcpy(&n;&t;      pDevExt-&gt;fcScsiQue.Qitem[pDevExt-&gt;fcScsiQue.producer].ulBuff,&n;        &amp;fcChip-&gt;SEST-&gt;RspHDR[ *pExchangeID ],&n;&t;      sizeof(pDevExt-&gt;fcScsiQue.Qitem[0].ulBuff)); // (any element for size)&n;      &n;    }&n;    else&n;    {&n;      memcpy(&n;&t;      pDevExt-&gt;fcScsiQue.Qitem[pDevExt-&gt;fcScsiQue.producer].ulBuff,&n;        QueContent, &n;&t;      sizeof(pDevExt-&gt;fcScsiQue.Qitem[pDevExt-&gt;fcScsiQue.producer].ulBuff));&n;    }&n;      &n;    pDevExt-&gt;fcScsiQue.producer = ndx;  // increment Que&n;&n;&n;    KeSetEvent( &amp;pDevExt-&gt;TYIBscsi,  // signal any waiting thread&n;       0,                    // no priority boost&n;&t;&t;   FALSE );              // no waiting later for this event&n;  }&n;  KeReleaseSpinLockFromDpcLevel( &amp;pDevExt-&gt;fcScsiQueLock);&n;*/
)brace
r_static
r_void
id|ProcessELS_Request
c_func
(paren
id|CPQFCHBA
op_star
comma
id|TachFCHDR_GCMND
op_star
)paren
suffix:semicolon
r_static
r_void
id|ProcessELS_Reply
c_func
(paren
id|CPQFCHBA
op_star
comma
id|TachFCHDR_GCMND
op_star
)paren
suffix:semicolon
r_static
r_void
id|ProcessFCS_Reply
c_func
(paren
id|CPQFCHBA
op_star
comma
id|TachFCHDR_GCMND
op_star
)paren
suffix:semicolon
DECL|function|cpqfcTSImplicitLogout
r_void
id|cpqfcTSImplicitLogout
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|PFC_LOGGEDIN_PORT
id|pFcPort
)paren
(brace
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
r_if
c_cond
(paren
id|pFcPort-&gt;port_id
op_ne
l_int|0xFFFC01
)paren
singleline_comment|// don&squot;t care about Fabric
(brace
id|fcChip-&gt;fcStats.logouts
op_increment
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cpqfcTS: Implicit logout of WWN %08X%08X, port_id %06X&bslash;n&quot;
comma
(paren
id|ULONG
)paren
id|pFcPort-&gt;u.liWWN
comma
(paren
id|ULONG
)paren
(paren
id|pFcPort-&gt;u.liWWN
op_rshift
l_int|32
)paren
comma
id|pFcPort-&gt;port_id
)paren
suffix:semicolon
singleline_comment|// Terminate I/O with this (Linux) Scsi target
id|cpqfcTSTerminateExchange
c_func
(paren
id|cpqfcHBAdata
comma
op_amp
id|pFcPort-&gt;ScsiNexus
comma
id|DEVICE_REMOVED
)paren
suffix:semicolon
)brace
singleline_comment|// Do an &quot;implicit logout&quot; - we can&squot;t really Logout the device
singleline_comment|// (i.e. with LOGOut Request) because of port_id confusion
singleline_comment|// (i.e. the Other port has no port_id).
singleline_comment|// A new login for that WWN will have to re-write port_id (0 invalid)
id|pFcPort-&gt;port_id
op_assign
l_int|0
suffix:semicolon
singleline_comment|// invalid!
id|pFcPort-&gt;pdisc
op_assign
id|FALSE
suffix:semicolon
id|pFcPort-&gt;prli
op_assign
id|FALSE
suffix:semicolon
id|pFcPort-&gt;plogi
op_assign
id|FALSE
suffix:semicolon
id|pFcPort-&gt;flogi
op_assign
id|FALSE
suffix:semicolon
id|pFcPort-&gt;LOGO_timer
op_assign
l_int|0
suffix:semicolon
id|pFcPort-&gt;device_blocked
op_assign
id|TRUE
suffix:semicolon
singleline_comment|// block Scsi Requests
id|pFcPort-&gt;ScsiNexus.VolumeSetAddressing
op_assign
l_int|0
suffix:semicolon
)brace
singleline_comment|// On FC-AL, there is a chance that a previously known device can
singleline_comment|// be quietly removed (e.g. with non-managed hub), 
singleline_comment|// while a NEW device (with different WWN) took the same alpa or
singleline_comment|// even 24-bit port_id.  This chance is unlikely but we must always
singleline_comment|// check for it.
DECL|function|TestDuplicatePortId
r_static
r_void
id|TestDuplicatePortId
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
)paren
(brace
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
singleline_comment|// set &quot;other port&quot; at beginning of fcPorts list
id|PFC_LOGGEDIN_PORT
id|pOtherPortWithPortId
op_assign
id|fcChip-&gt;fcPorts.pNextPort
suffix:semicolon
r_while
c_loop
(paren
id|pOtherPortWithPortId
)paren
(brace
r_if
c_cond
(paren
(paren
id|pOtherPortWithPortId-&gt;port_id
op_eq
id|pLoggedInPort-&gt;port_id
)paren
op_logical_and
(paren
id|pOtherPortWithPortId
op_ne
id|pLoggedInPort
)paren
)paren
(brace
singleline_comment|// trouble!  (Implicitly) Log the other guy out
id|printk
c_func
(paren
l_string|&quot; *port_id %Xh is duplicated!* &quot;
comma
id|pOtherPortWithPortId-&gt;port_id
)paren
suffix:semicolon
id|cpqfcTSImplicitLogout
c_func
(paren
id|cpqfcHBAdata
comma
id|pOtherPortWithPortId
)paren
suffix:semicolon
)brace
id|pOtherPortWithPortId
op_assign
id|pOtherPortWithPortId-&gt;pNextPort
suffix:semicolon
)brace
)brace
singleline_comment|// Dynamic Memory Allocation for newly discovered FC Ports.
singleline_comment|// For simplicity, maintain fcPorts structs for ALL
singleline_comment|// for discovered devices, including those we never do I/O with
singleline_comment|// (e.g. Fabric addresses)
DECL|function|CreateFcPort
r_static
id|PFC_LOGGEDIN_PORT
id|CreateFcPort
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|PFC_LOGGEDIN_PORT
id|pLastLoggedInPort
comma
id|TachFCHDR_GCMND
op_star
id|fchs
comma
id|LOGIN_PAYLOAD
op_star
id|plogi
)paren
(brace
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
id|PFC_LOGGEDIN_PORT
id|pNextLoggedInPort
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cpqfcTS: New FC port %06Xh WWN: &quot;
comma
id|fchs-&gt;s_id
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|3
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
singleline_comment|// copy the LOGIN port&squot;s WWN
id|printk
c_func
(paren
l_string|&quot;%02X&quot;
comma
id|plogi-&gt;port_name
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|7
suffix:semicolon
id|i
OG
l_int|3
suffix:semicolon
id|i
op_decrement
)paren
(brace
singleline_comment|// copy the LOGIN port&squot;s WWN
id|printk
c_func
(paren
l_string|&quot;%02X&quot;
comma
id|plogi-&gt;port_name
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
singleline_comment|// allocate mem for new port
singleline_comment|// (these are small and rare allocations...)
id|pNextLoggedInPort
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|FC_LOGGEDIN_PORT
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
singleline_comment|// allocation succeeded?  Fill out NEW PORT
r_if
c_cond
(paren
id|pNextLoggedInPort
)paren
(brace
singleline_comment|// clear out any garbage (sometimes exists)
id|memset
c_func
(paren
id|pNextLoggedInPort
comma
l_int|0
comma
r_sizeof
(paren
id|FC_LOGGEDIN_PORT
)paren
)paren
suffix:semicolon
singleline_comment|// If we login to a Fabric, we don&squot;t want to treat it
singleline_comment|// as a SCSI device...
r_if
c_cond
(paren
(paren
id|fchs-&gt;s_id
op_amp
l_int|0xFFF000
)paren
op_ne
l_int|0xFFF000
)paren
(brace
r_int
id|i
suffix:semicolon
singleline_comment|// create a unique &quot;virtual&quot; SCSI Nexus (for now, just a
singleline_comment|// new target ID) -- we will update channel/target on REPORT_LUNS
singleline_comment|// special case for very first SCSI target...
r_if
c_cond
(paren
id|cpqfcHBAdata-&gt;HostAdapter-&gt;max_id
op_eq
l_int|0
)paren
(brace
id|pNextLoggedInPort-&gt;ScsiNexus.target
op_assign
l_int|0
suffix:semicolon
id|fcChip-&gt;fcPorts.ScsiNexus.target
op_assign
op_minus
l_int|1
suffix:semicolon
singleline_comment|// don&squot;t use &quot;stub&quot;
)brace
r_else
(brace
id|pNextLoggedInPort-&gt;ScsiNexus.target
op_assign
id|cpqfcHBAdata-&gt;HostAdapter-&gt;max_id
suffix:semicolon
)brace
singleline_comment|// initialize the lun[] Nexus struct for lun masking      
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|CPQFCTS_MAX_LUN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pNextLoggedInPort-&gt;ScsiNexus.lun
(braket
id|i
)braket
op_assign
l_int|0xFF
suffix:semicolon
)brace
singleline_comment|// init to NOT USED
id|pNextLoggedInPort-&gt;ScsiNexus.channel
op_assign
l_int|0
suffix:semicolon
singleline_comment|// cpqfcTS has 1 FC port
id|printk
c_func
(paren
l_string|&quot; SCSI Chan/Trgt %d/%d&quot;
comma
id|pNextLoggedInPort-&gt;ScsiNexus.channel
comma
id|pNextLoggedInPort-&gt;ScsiNexus.target
)paren
suffix:semicolon
singleline_comment|// tell Scsi layers about the new target...
id|cpqfcHBAdata-&gt;HostAdapter-&gt;max_id
op_increment
suffix:semicolon
singleline_comment|//    printk(&quot;HostAdapter-&gt;max_id = %d&bslash;n&quot;,
singleline_comment|//      cpqfcHBAdata-&gt;HostAdapter-&gt;max_id);&t;&t;    
)brace
r_else
(brace
singleline_comment|// device is NOT SCSI (in case of Fabric)
id|pNextLoggedInPort-&gt;ScsiNexus.target
op_assign
op_minus
l_int|1
suffix:semicolon
singleline_comment|// invalid
)brace
singleline_comment|// create forward link to new port
id|pLastLoggedInPort-&gt;pNextPort
op_assign
id|pNextLoggedInPort
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|pNextLoggedInPort
suffix:semicolon
singleline_comment|// NULL on allocation failure
)brace
singleline_comment|// end NEW PORT (WWN) logic
singleline_comment|// For certain cases, we want to terminate exchanges without
singleline_comment|// sending ABTS to the device.  Examples include when an FC
singleline_comment|// device changed it&squot;s port_id after Loop re-init, or when
singleline_comment|// the device sent us a logout.  In the case of changed port_id,
singleline_comment|// we want to complete the command and return SOFT_ERROR to
singleline_comment|// force a re-try.  In the case of LOGOut, we might return
singleline_comment|// BAD_TARGET if the device is really gone.
singleline_comment|// Since we must ensure that Tachyon is not operating on the
singleline_comment|// exchange, we have to freeze the chip
singleline_comment|// sterminateex
DECL|function|cpqfcTSTerminateExchange
r_void
id|cpqfcTSTerminateExchange
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|SCSI_NEXUS
op_star
id|ScsiNexus
comma
r_int
id|TerminateStatus
)paren
(brace
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
id|FC_EXCHANGES
op_star
id|Exchanges
op_assign
id|fcChip-&gt;Exchanges
suffix:semicolon
id|ULONG
id|x_ID
suffix:semicolon
r_if
c_cond
(paren
id|ScsiNexus
)paren
(brace
singleline_comment|//    printk(&quot;TerminateExchange: ScsiNexus chan/target %d/%d&bslash;n&quot;,
singleline_comment|//&t;&t;    ScsiNexus-&gt;channel, ScsiNexus-&gt;target);
)brace
r_for
c_loop
(paren
id|x_ID
op_assign
l_int|0
suffix:semicolon
id|x_ID
OL
id|TACH_SEST_LEN
suffix:semicolon
id|x_ID
op_increment
)paren
(brace
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|type
)paren
singleline_comment|// in use?
(brace
r_if
c_cond
(paren
id|ScsiNexus
op_eq
l_int|NULL
)paren
singleline_comment|// our HBA changed - term. all
(brace
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_assign
id|TerminateStatus
suffix:semicolon
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|BLS_ABTS
comma
op_amp
id|x_ID
)paren
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// If a device, according to WWN, has been removed, it&squot;s
singleline_comment|// port_id may be used by another working device, so we
singleline_comment|// have to terminate by SCSI target, NOT port_id.
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd
)paren
singleline_comment|// Cmnd in progress?
(brace
r_if
c_cond
(paren
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;target
op_eq
id|ScsiNexus-&gt;target
)paren
op_logical_and
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;channel
op_eq
id|ScsiNexus-&gt;channel
)paren
)paren
(brace
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_assign
id|TerminateStatus
suffix:semicolon
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|BLS_ABTS
comma
op_amp
id|x_ID
)paren
suffix:semicolon
singleline_comment|// timed-out
)brace
)brace
singleline_comment|// (in case we ever need it...)
singleline_comment|// all SEST structures have a remote node ID at SEST DWORD 2
singleline_comment|//          if( (fcChip-&gt;SEST-&gt;u[ x_ID ].TWE.Remote_Node_ID &gt;&gt; 8)
singleline_comment|//                ==  port_id)
)brace
)brace
)brace
)brace
DECL|function|ProcessELS_Request
r_static
r_void
id|ProcessELS_Request
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|TachFCHDR_GCMND
op_star
id|fchs
)paren
(brace
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
singleline_comment|//  FC_EXCHANGES *Exchanges = fcChip-&gt;Exchanges;
singleline_comment|//  ULONG ox_id = (fchs-&gt;ox_rx_id &gt;&gt;16);
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
op_assign
l_int|NULL
comma
id|pLastLoggedInPort
suffix:semicolon
id|BOOLEAN
id|NeedReject
op_assign
id|FALSE
suffix:semicolon
id|ULONG
id|ls_reject_code
op_assign
l_int|0
suffix:semicolon
singleline_comment|// default don&squot;n know??
singleline_comment|// Check the incoming frame for a supported ELS type
r_switch
c_cond
(paren
id|fchs-&gt;pl
(braket
l_int|0
)braket
op_amp
l_int|0xFFFF
)paren
(brace
r_case
l_int|0x0050
suffix:colon
singleline_comment|//  PDISC?
singleline_comment|// Payload for PLOGI and PDISC is identical (request &amp; reply)
r_if
c_cond
(paren
op_logical_neg
id|verify_PLOGI
c_func
(paren
id|fcChip
comma
id|fchs
comma
op_amp
id|ls_reject_code
)paren
)paren
singleline_comment|// valid payload?
(brace
id|LOGIN_PAYLOAD
id|logi
suffix:semicolon
singleline_comment|// FC-PH Port Login
singleline_comment|// PDISC payload OK. If critical login fields
singleline_comment|// (e.g. WWN) matches last login for this port_id,
singleline_comment|// we may resume any prior exchanges
singleline_comment|// with the other port
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|fchs-&gt;pl
(braket
l_int|0
)braket
comma
(paren
id|UCHAR
op_star
)paren
op_amp
id|logi
comma
r_sizeof
(paren
id|logi
)paren
)paren
suffix:semicolon
id|pLoggedInPort
op_assign
id|fcFindLoggedInPort
c_func
(paren
id|fcChip
comma
l_int|NULL
comma
singleline_comment|// don&squot;t search Scsi Nexus
l_int|0
comma
singleline_comment|// don&squot;t search linked list for port_id
op_amp
id|logi.port_name
(braket
l_int|0
)braket
comma
singleline_comment|// search linked list for WWN
op_amp
id|pLastLoggedInPort
)paren
suffix:semicolon
singleline_comment|// must return non-NULL; when a port_id
singleline_comment|// is not found, this pointer marks the
singleline_comment|// end of the singly linked list
r_if
c_cond
(paren
id|pLoggedInPort
op_ne
l_int|NULL
)paren
singleline_comment|// WWN found (prior login OK)
(brace
r_if
c_cond
(paren
(paren
id|fchs-&gt;s_id
op_amp
l_int|0xFFFFFF
)paren
op_eq
id|pLoggedInPort-&gt;port_id
)paren
(brace
singleline_comment|// Yes.  We were expecting PDISC?
r_if
c_cond
(paren
id|pLoggedInPort-&gt;pdisc
)paren
(brace
singleline_comment|// Yes; set fields accordingly.     (PDISC, not Originator)
id|SetLoginFields
c_func
(paren
id|pLoggedInPort
comma
id|fchs
comma
id|TRUE
comma
id|FALSE
)paren
suffix:semicolon
singleline_comment|// send &squot;ACC&squot; reply 
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|ELS_PLOGI_ACC
comma
singleline_comment|// (PDISC same as PLOGI ACC)
id|fchs
)paren
suffix:semicolon
singleline_comment|// OK to resume I/O...
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;Not expecting PDISC (pdisc=FALSE)&bslash;n&quot;
)paren
suffix:semicolon
id|NeedReject
op_assign
id|TRUE
suffix:semicolon
singleline_comment|// set reject reason code 
id|ls_reject_code
op_assign
id|LS_RJT_REASON
c_func
(paren
id|PROTOCOL_ERROR
comma
id|INITIATOR_CTL_ERROR
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|pLoggedInPort-&gt;port_id
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PDISC PortID change: old %Xh, new %Xh&bslash;n&quot;
comma
id|pLoggedInPort-&gt;port_id
comma
id|fchs-&gt;s_id
op_amp
l_int|0xFFFFFF
)paren
suffix:semicolon
)brace
id|NeedReject
op_assign
id|TRUE
suffix:semicolon
singleline_comment|// set reject reason code 
id|ls_reject_code
op_assign
id|LS_RJT_REASON
c_func
(paren
id|PROTOCOL_ERROR
comma
id|INITIATOR_CTL_ERROR
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;PDISC Request from unknown WWN&bslash;n&quot;
)paren
suffix:semicolon
id|NeedReject
op_assign
id|TRUE
suffix:semicolon
singleline_comment|// set reject reason code 
id|ls_reject_code
op_assign
id|LS_RJT_REASON
c_func
(paren
id|LOGICAL_ERROR
comma
id|INVALID_PORT_NAME
)paren
suffix:semicolon
)brace
)brace
r_else
singleline_comment|// Payload unacceptable
(brace
id|printk
c_func
(paren
l_string|&quot;payload unacceptable&bslash;n&quot;
)paren
suffix:semicolon
id|NeedReject
op_assign
id|TRUE
suffix:semicolon
singleline_comment|// reject code already set
)brace
r_if
c_cond
(paren
id|NeedReject
)paren
(brace
id|ULONG
id|port_id
suffix:semicolon
singleline_comment|// The PDISC failed.  Set login struct flags accordingly,
singleline_comment|// terminate any I/O to this port, and Q a PLOGI
r_if
c_cond
(paren
id|pLoggedInPort
)paren
(brace
id|pLoggedInPort-&gt;pdisc
op_assign
id|FALSE
suffix:semicolon
id|pLoggedInPort-&gt;prli
op_assign
id|FALSE
suffix:semicolon
id|pLoggedInPort-&gt;plogi
op_assign
id|FALSE
suffix:semicolon
id|cpqfcTSTerminateExchange
c_func
(paren
id|cpqfcHBAdata
comma
op_amp
id|pLoggedInPort-&gt;ScsiNexus
comma
id|PORTID_CHANGED
)paren
suffix:semicolon
id|port_id
op_assign
id|pLoggedInPort-&gt;port_id
suffix:semicolon
)brace
r_else
(brace
id|port_id
op_assign
id|fchs-&gt;s_id
op_amp
l_int|0xFFFFFF
suffix:semicolon
)brace
id|fchs-&gt;reserved
op_assign
id|ls_reject_code
suffix:semicolon
singleline_comment|// borrow this (unused) field
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|ELS_RJT
comma
id|fchs
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|0x0003
suffix:colon
singleline_comment|//  PLOGI?
singleline_comment|// Payload for PLOGI and PDISC is identical (request &amp; reply)
r_if
c_cond
(paren
op_logical_neg
id|verify_PLOGI
c_func
(paren
id|fcChip
comma
id|fchs
comma
op_amp
id|ls_reject_code
)paren
)paren
singleline_comment|// valid payload?
(brace
id|LOGIN_PAYLOAD
id|logi
suffix:semicolon
singleline_comment|// FC-PH Port Login
id|BOOLEAN
id|NeedReject
op_assign
id|FALSE
suffix:semicolon
singleline_comment|// PDISC payload OK. If critical login fields
singleline_comment|// (e.g. WWN) matches last login for this port_id,
singleline_comment|// we may resume any prior exchanges
singleline_comment|// with the other port
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|fchs-&gt;pl
(braket
l_int|0
)braket
comma
(paren
id|UCHAR
op_star
)paren
op_amp
id|logi
comma
r_sizeof
(paren
id|logi
)paren
)paren
suffix:semicolon
id|pLoggedInPort
op_assign
id|fcFindLoggedInPort
c_func
(paren
id|fcChip
comma
l_int|NULL
comma
singleline_comment|// don&squot;t search Scsi Nexus
l_int|0
comma
singleline_comment|// don&squot;t search linked list for port_id
op_amp
id|logi.port_name
(braket
l_int|0
)braket
comma
singleline_comment|// search linked list for WWN
op_amp
id|pLastLoggedInPort
)paren
suffix:semicolon
singleline_comment|// must return non-NULL; when a port_id
singleline_comment|// is not found, this pointer marks the
singleline_comment|// end of the singly linked list
r_if
c_cond
(paren
id|pLoggedInPort
op_eq
l_int|NULL
)paren
singleline_comment|// WWN not found -New Port
(brace
id|pLoggedInPort
op_assign
id|CreateFcPort
c_func
(paren
id|cpqfcHBAdata
comma
id|pLastLoggedInPort
comma
id|fchs
comma
op_amp
id|logi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pLoggedInPort
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; cpqfcTS: New port allocation failed - lost FC device!&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|// Now Q a LOGOut Request, since we won&squot;t be talking to that device
id|NeedReject
op_assign
id|TRUE
suffix:semicolon
singleline_comment|// set reject reason code 
id|ls_reject_code
op_assign
id|LS_RJT_REASON
c_func
(paren
id|LOGICAL_ERROR
comma
id|NO_LOGIN_RESOURCES
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|NeedReject
)paren
(brace
singleline_comment|// OK - we have valid fcPort ptr; set fields accordingly.   
singleline_comment|//                         (not PDISC, not Originator)
id|SetLoginFields
c_func
(paren
id|pLoggedInPort
comma
id|fchs
comma
id|FALSE
comma
id|FALSE
)paren
suffix:semicolon
singleline_comment|// send &squot;ACC&squot; reply 
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|ELS_PLOGI_ACC
comma
singleline_comment|// (PDISC same as PLOGI ACC)
id|fchs
)paren
suffix:semicolon
)brace
)brace
r_else
singleline_comment|// Payload unacceptable
(brace
id|printk
c_func
(paren
l_string|&quot;payload unacceptable&bslash;n&quot;
)paren
suffix:semicolon
id|NeedReject
op_assign
id|TRUE
suffix:semicolon
singleline_comment|// reject code already set
)brace
r_if
c_cond
(paren
id|NeedReject
)paren
(brace
singleline_comment|// The PDISC failed.  Set login struct flags accordingly,
singleline_comment|// terminate any I/O to this port, and Q a PLOGI
id|pLoggedInPort-&gt;pdisc
op_assign
id|FALSE
suffix:semicolon
id|pLoggedInPort-&gt;prli
op_assign
id|FALSE
suffix:semicolon
id|pLoggedInPort-&gt;plogi
op_assign
id|FALSE
suffix:semicolon
id|fchs-&gt;reserved
op_assign
id|ls_reject_code
suffix:semicolon
singleline_comment|// borrow this (unused) field
singleline_comment|// send &squot;RJT&squot; reply 
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|ELS_RJT
comma
id|fchs
)paren
suffix:semicolon
)brace
singleline_comment|// terminate any exchanges with this device...
r_if
c_cond
(paren
id|pLoggedInPort
)paren
(brace
id|cpqfcTSTerminateExchange
c_func
(paren
id|cpqfcHBAdata
comma
op_amp
id|pLoggedInPort-&gt;ScsiNexus
comma
id|PORTID_CHANGED
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|0x1020
suffix:colon
singleline_comment|// PRLI?
(brace
id|BOOLEAN
id|NeedReject
op_assign
id|TRUE
suffix:semicolon
id|pLoggedInPort
op_assign
id|fcFindLoggedInPort
c_func
(paren
id|fcChip
comma
l_int|NULL
comma
singleline_comment|// don&squot;t search Scsi Nexus
(paren
id|fchs-&gt;s_id
op_amp
l_int|0xFFFFFF
)paren
comma
singleline_comment|// search linked list for port_id
l_int|NULL
comma
singleline_comment|// DON&squot;T search linked list for WWN
l_int|NULL
)paren
suffix:semicolon
singleline_comment|// don&squot;t care
r_if
c_cond
(paren
id|pLoggedInPort
op_eq
l_int|NULL
)paren
(brace
singleline_comment|// huh?
id|printk
c_func
(paren
l_string|&quot; Unexpected PRLI Request -not logged in!&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|// set reject reason code 
id|ls_reject_code
op_assign
id|LS_RJT_REASON
c_func
(paren
id|PROTOCOL_ERROR
comma
id|INITIATOR_CTL_ERROR
)paren
suffix:semicolon
singleline_comment|// Q a LOGOut here?
)brace
r_else
(brace
singleline_comment|// verify the PRLI ACC payload
r_if
c_cond
(paren
op_logical_neg
id|verify_PRLI
c_func
(paren
id|fchs
comma
op_amp
id|ls_reject_code
)paren
)paren
(brace
singleline_comment|// PRLI Reply is acceptable; were we expecting it?
r_if
c_cond
(paren
id|pLoggedInPort-&gt;plogi
)paren
(brace
singleline_comment|// yes, we expected the PRLI ACC  (not PDISC; not Originator)
id|SetLoginFields
c_func
(paren
id|pLoggedInPort
comma
id|fchs
comma
id|FALSE
comma
id|FALSE
)paren
suffix:semicolon
singleline_comment|// Q an ACCept Reply
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|ELS_PRLI_ACC
comma
id|fchs
)paren
suffix:semicolon
id|NeedReject
op_assign
id|FALSE
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// huh?
id|printk
c_func
(paren
l_string|&quot; (unexpected) PRLI REQEST with plogi FALSE&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|// set reject reason code 
id|ls_reject_code
op_assign
id|LS_RJT_REASON
c_func
(paren
id|PROTOCOL_ERROR
comma
id|INITIATOR_CTL_ERROR
)paren
suffix:semicolon
singleline_comment|// Q a LOGOut here?
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot; PRLI REQUEST payload failed verify&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|// (reject code set by &quot;verify&quot;)
singleline_comment|// Q a LOGOut here?
)brace
)brace
r_if
c_cond
(paren
id|NeedReject
)paren
(brace
singleline_comment|// Q a ReJecT Reply with reason code
id|fchs-&gt;reserved
op_assign
id|ls_reject_code
suffix:semicolon
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|ELS_RJT
comma
singleline_comment|// Q Type
id|fchs
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
l_int|0x0005
suffix:colon
singleline_comment|// LOGOut?
(brace
singleline_comment|// was this LOGOUT because we sent a ELS_PDISC to an FC device
singleline_comment|// with changed (or new) port_id, or does the port refuse 
singleline_comment|// to communicate to us?
singleline_comment|// We maintain a logout counter - if we get 3 consecutive LOGOuts,
singleline_comment|// give up!
id|LOGOUT_PAYLOAD
id|logo
suffix:semicolon
id|BOOLEAN
id|GiveUpOnDevice
op_assign
id|FALSE
suffix:semicolon
id|ULONG
id|ls_reject_code
op_assign
l_int|0
suffix:semicolon
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|fchs-&gt;pl
(braket
l_int|0
)braket
comma
(paren
id|UCHAR
op_star
)paren
op_amp
id|logo
comma
r_sizeof
(paren
id|logo
)paren
)paren
suffix:semicolon
id|pLoggedInPort
op_assign
id|fcFindLoggedInPort
c_func
(paren
id|fcChip
comma
l_int|NULL
comma
singleline_comment|// don&squot;t search Scsi Nexus
l_int|0
comma
singleline_comment|// don&squot;t search linked list for port_id
op_amp
id|logo.port_name
(braket
l_int|0
)braket
comma
singleline_comment|// search linked list for WWN
l_int|NULL
)paren
suffix:semicolon
singleline_comment|// don&squot;t care about end of list
r_if
c_cond
(paren
id|pLoggedInPort
)paren
singleline_comment|// found the device?
(brace
singleline_comment|// Q an ACC reply 
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|ELS_LOGO_ACC
comma
singleline_comment|// Q Type
id|fchs
)paren
suffix:semicolon
singleline_comment|// device to respond to
singleline_comment|// set login struct fields (LOGO_counter increment)
id|SetLoginFields
c_func
(paren
id|pLoggedInPort
comma
id|fchs
comma
id|FALSE
comma
id|FALSE
)paren
suffix:semicolon
singleline_comment|// are we an Initiator?
r_if
c_cond
(paren
id|fcChip-&gt;Options.initiator
)paren
(brace
singleline_comment|// we&squot;re an Initiator, so check if we should 
singleline_comment|// try (another?) login
singleline_comment|// Fabrics routinely log out from us after
singleline_comment|// getting device info - don&squot;t try to log them
singleline_comment|// back in.
r_if
c_cond
(paren
(paren
id|fchs-&gt;s_id
op_amp
l_int|0xFFF000
)paren
op_eq
l_int|0xFFF000
)paren
(brace
suffix:semicolon
singleline_comment|// do nothing
)brace
r_else
r_if
c_cond
(paren
id|pLoggedInPort-&gt;LOGO_counter
op_le
l_int|3
)paren
(brace
singleline_comment|// try (another) login (PLOGI request)
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|ELS_PLOGI
comma
singleline_comment|// Q Type
id|fchs
)paren
suffix:semicolon
singleline_comment|// Terminate I/O with &quot;retry&quot; potential
id|cpqfcTSTerminateExchange
c_func
(paren
id|cpqfcHBAdata
comma
op_amp
id|pLoggedInPort-&gt;ScsiNexus
comma
id|PORTID_CHANGED
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot; Got 3 LOGOuts - terminating comm. with port_id %Xh&bslash;n&quot;
comma
id|fchs-&gt;s_id
op_logical_and
l_int|0xFFFFFF
)paren
suffix:semicolon
id|GiveUpOnDevice
op_assign
id|TRUE
suffix:semicolon
)brace
)brace
r_else
(brace
id|GiveUpOnDevice
op_assign
id|TRUE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|GiveUpOnDevice
op_eq
id|TRUE
)paren
(brace
id|cpqfcTSTerminateExchange
c_func
(paren
id|cpqfcHBAdata
comma
op_amp
id|pLoggedInPort-&gt;ScsiNexus
comma
id|DEVICE_REMOVED
)paren
suffix:semicolon
)brace
)brace
r_else
singleline_comment|// we don&squot;t know this WWN!
(brace
singleline_comment|// Q a ReJecT Reply with reason code
id|fchs-&gt;reserved
op_assign
id|ls_reject_code
suffix:semicolon
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|ELS_RJT
comma
singleline_comment|// Q Type
id|fchs
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
singleline_comment|// FABRIC only case
r_case
l_int|0x0461
suffix:colon
singleline_comment|// ELS RSCN (Registered State Change Notification)?
(brace
r_int
id|Ports
suffix:semicolon
r_int
id|i
suffix:semicolon
id|__u32
id|Buff
suffix:semicolon
singleline_comment|// Typically, one or more devices have been added to or dropped
singleline_comment|// from the Fabric.
singleline_comment|// The format of this frame is defined in FC-FLA (Rev 2.7, Aug 1997)
singleline_comment|// The first 32-bit word has a 2-byte Payload Length, which
singleline_comment|// includes the 4 bytes of the first word.  Consequently,
singleline_comment|// this PL len must never be less than 4, must be a multiple of 4,
singleline_comment|// and has a specified max value 256.
singleline_comment|// (Endianess!)
id|Ports
op_assign
(paren
(paren
id|fchs-&gt;pl
(braket
l_int|0
)braket
op_rshift
l_int|24
)paren
op_minus
l_int|4
)paren
op_div
l_int|4
suffix:semicolon
id|Ports
op_assign
id|Ports
OG
l_int|63
ques
c_cond
l_int|63
suffix:colon
id|Ports
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; RSCN ports: %d&bslash;n&quot;
comma
id|Ports
)paren
suffix:semicolon
r_if
c_cond
(paren
id|Ports
op_le
l_int|0
)paren
singleline_comment|// huh?
(brace
singleline_comment|// ReJecT the command
id|fchs-&gt;reserved
op_assign
id|LS_RJT_REASON
c_func
(paren
id|UNABLE_TO_PERFORM
comma
l_int|0
)paren
suffix:semicolon
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|ELS_RJT
comma
singleline_comment|// Q Type
id|fchs
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
singleline_comment|// Accept the command
(brace
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|ELS_ACC
comma
singleline_comment|// Q Type
id|fchs
)paren
suffix:semicolon
)brace
singleline_comment|// Check the &quot;address format&quot; to determine action.
singleline_comment|// We have 3 cases:
singleline_comment|// 0 = Port Address; 24-bit address of affected device
singleline_comment|// 1 = Area Address; MS 16 bits valid
singleline_comment|// 2 = Domain Address; MS 8 bits valid
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|Ports
suffix:semicolon
id|i
op_increment
)paren
(brace
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|fchs-&gt;pl
(braket
id|i
op_plus
l_int|1
)braket
comma
(paren
id|UCHAR
op_star
)paren
op_amp
id|Buff
comma
l_int|4
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|Buff
op_amp
l_int|0xFF000000
)paren
(brace
r_case
l_int|0
suffix:colon
singleline_comment|// Port Address?
r_case
l_int|0x01000000
suffix:colon
singleline_comment|// Area Domain?
r_case
l_int|0x02000000
suffix:colon
singleline_comment|// Domain Address
singleline_comment|// For example, &quot;port_id&quot; 0x201300 
singleline_comment|// OK, let&squot;s try a Name Service Request (Query)
id|fchs-&gt;s_id
op_assign
l_int|0xFFFFFC
suffix:semicolon
singleline_comment|// Name Server Address
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|FCS_NSR
comma
id|fchs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
singleline_comment|// huh? new value on version change?
r_break
suffix:semicolon
)brace
)brace
)brace
r_break
suffix:semicolon
r_default
suffix:colon
singleline_comment|// don&squot;t support this request (yet)
singleline_comment|// set reject reason code 
id|fchs-&gt;reserved
op_assign
id|LS_RJT_REASON
c_func
(paren
id|UNABLE_TO_PERFORM
comma
id|REQUEST_NOT_SUPPORTED
)paren
suffix:semicolon
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|ELS_RJT
comma
singleline_comment|// Q Type
id|fchs
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|ProcessELS_Reply
r_static
r_void
id|ProcessELS_Reply
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|TachFCHDR_GCMND
op_star
id|fchs
)paren
(brace
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
id|FC_EXCHANGES
op_star
id|Exchanges
op_assign
id|fcChip-&gt;Exchanges
suffix:semicolon
id|ULONG
id|ox_id
op_assign
(paren
id|fchs-&gt;ox_rx_id
op_rshift
l_int|16
)paren
suffix:semicolon
id|ULONG
id|ls_reject_code
suffix:semicolon
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
comma
id|pLastLoggedInPort
suffix:semicolon
singleline_comment|// If this is a valid reply, then we MUST have sent a request.
singleline_comment|// Verify that we can find a valid request OX_ID corresponding to
singleline_comment|// this reply
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
(paren
id|fchs-&gt;ox_rx_id
op_rshift
l_int|16
)paren
)braket
dot
id|type
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; *Discarding ACC/RJT frame, xID %04X/%04X* &quot;
comma
id|ox_id
comma
id|fchs-&gt;ox_rx_id
op_amp
l_int|0xffff
)paren
suffix:semicolon
r_goto
id|Quit
suffix:semicolon
singleline_comment|// exit this routine
)brace
singleline_comment|// Is the reply a RJT (reject)?
r_if
c_cond
(paren
(paren
id|fchs-&gt;pl
(braket
l_int|0
)braket
op_amp
l_int|0xFFFFL
)paren
op_eq
l_int|0x01
)paren
singleline_comment|// Reject reply?
(brace
singleline_comment|//  ******  REJECT REPLY  ********
r_switch
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|ox_id
)braket
dot
id|type
)paren
(brace
r_case
id|ELS_FDISC
suffix:colon
singleline_comment|// we sent out Fabric Discovery
r_case
id|ELS_FLOGI
suffix:colon
singleline_comment|// we sent out FLOGI
id|printk
c_func
(paren
l_string|&quot;RJT received on Fabric Login from %Xh, reason %Xh&bslash;n&quot;
comma
id|fchs-&gt;s_id
comma
id|fchs-&gt;pl
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_goto
id|Done
suffix:semicolon
)brace
singleline_comment|// OK, we have an ACCept...
singleline_comment|// What&squot;s the ACC type? (according to what we sent)
r_switch
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|ox_id
)braket
dot
id|type
)paren
(brace
r_case
id|ELS_PLOGI
suffix:colon
singleline_comment|// we sent out PLOGI
r_if
c_cond
(paren
op_logical_neg
id|verify_PLOGI
c_func
(paren
id|fcChip
comma
id|fchs
comma
op_amp
id|ls_reject_code
)paren
)paren
(brace
id|LOGIN_PAYLOAD
id|logi
suffix:semicolon
singleline_comment|// FC-PH Port Login
singleline_comment|// login ACC payload acceptable; search for WWN in our list
singleline_comment|// of fcPorts
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|fchs-&gt;pl
(braket
l_int|0
)braket
comma
(paren
id|UCHAR
op_star
)paren
op_amp
id|logi
comma
r_sizeof
(paren
id|logi
)paren
)paren
suffix:semicolon
id|pLoggedInPort
op_assign
id|fcFindLoggedInPort
c_func
(paren
id|fcChip
comma
l_int|NULL
comma
singleline_comment|// don&squot;t search Scsi Nexus
l_int|0
comma
singleline_comment|// don&squot;t search linked list for port_id
op_amp
id|logi.port_name
(braket
l_int|0
)braket
comma
singleline_comment|// search linked list for WWN
op_amp
id|pLastLoggedInPort
)paren
suffix:semicolon
singleline_comment|// must return non-NULL; when a port_id
singleline_comment|// is not found, this pointer marks the
singleline_comment|// end of the singly linked list
r_if
c_cond
(paren
id|pLoggedInPort
op_eq
l_int|NULL
)paren
singleline_comment|// WWN not found - new port
(brace
id|pLoggedInPort
op_assign
id|CreateFcPort
c_func
(paren
id|cpqfcHBAdata
comma
id|pLastLoggedInPort
comma
id|fchs
comma
op_amp
id|logi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pLoggedInPort
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; cpqfcTS: New port allocation failed - lost FC device!&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|// Now Q a LOGOut Request, since we won&squot;t be talking to that device
r_goto
id|Done
suffix:semicolon
singleline_comment|// exit with error! dropped login frame
)brace
)brace
r_else
singleline_comment|// WWN was already known.  Ensure that any open
singleline_comment|// exchanges for this WWN are terminated.
singleline_comment|// NOTE: It&squot;s possible that a device can change its 
singleline_comment|// 24-bit port_id after a Link init or Fabric change 
singleline_comment|// (e.g. LIP or Fabric RSCN).  In that case, the old
singleline_comment|// 24-bit port_id may be duplicated, or no longer exist.
(brace
id|cpqfcTSTerminateExchange
c_func
(paren
id|cpqfcHBAdata
comma
op_amp
id|pLoggedInPort-&gt;ScsiNexus
comma
id|PORTID_CHANGED
)paren
suffix:semicolon
)brace
singleline_comment|// We have an fcPort struct - set fields accordingly
singleline_comment|// not PDISC, originator 
id|SetLoginFields
c_func
(paren
id|pLoggedInPort
comma
id|fchs
comma
id|FALSE
comma
id|TRUE
)paren
suffix:semicolon
singleline_comment|// We just set a &quot;port_id&quot;; is it duplicated?
id|TestDuplicatePortId
c_func
(paren
id|cpqfcHBAdata
comma
id|pLoggedInPort
)paren
suffix:semicolon
singleline_comment|// For Fabric operation, we issued PLOGI to 0xFFFFFC
singleline_comment|// so we can send SCR (State Change Registration) 
singleline_comment|// Check for this special case...
r_if
c_cond
(paren
id|fchs-&gt;s_id
op_eq
l_int|0xFFFFFC
)paren
(brace
singleline_comment|// PLOGI ACC was a Fabric response... issue SCR
id|fchs-&gt;s_id
op_assign
l_int|0xFFFFFD
suffix:semicolon
singleline_comment|// address for SCR
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|ELS_SCR
comma
id|fchs
)paren
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// Now we need a PRLI to enable FCP-SCSI operation
singleline_comment|// set flags and Q up a ELS_PRLI
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|ELS_PRLI
comma
id|fchs
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
singleline_comment|// login payload unacceptable - reason in ls_reject_code
singleline_comment|// Q up a Logout Request
id|printk
c_func
(paren
l_string|&quot;Login Payload unacceptable&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
singleline_comment|// PDISC logic very similar to PLOGI, except we never want
singleline_comment|// to allocate mem for &quot;new&quot; port, and we set flags differently
singleline_comment|// (might combine later with PLOGI logic for efficiency)  
r_case
id|ELS_PDISC
suffix:colon
singleline_comment|// we sent out PDISC
r_if
c_cond
(paren
op_logical_neg
id|verify_PLOGI
c_func
(paren
id|fcChip
comma
id|fchs
comma
op_amp
id|ls_reject_code
)paren
)paren
(brace
id|LOGIN_PAYLOAD
id|logi
suffix:semicolon
singleline_comment|// FC-PH Port Login
id|BOOLEAN
id|NeedLogin
op_assign
id|FALSE
suffix:semicolon
singleline_comment|// login payload acceptable; search for WWN in our list
singleline_comment|// of (previously seen) fcPorts
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|fchs-&gt;pl
(braket
l_int|0
)braket
comma
(paren
id|UCHAR
op_star
)paren
op_amp
id|logi
comma
r_sizeof
(paren
id|logi
)paren
)paren
suffix:semicolon
id|pLoggedInPort
op_assign
id|fcFindLoggedInPort
c_func
(paren
id|fcChip
comma
l_int|NULL
comma
singleline_comment|// don&squot;t search Scsi Nexus
l_int|0
comma
singleline_comment|// don&squot;t search linked list for port_id
op_amp
id|logi.port_name
(braket
l_int|0
)braket
comma
singleline_comment|// search linked list for WWN
op_amp
id|pLastLoggedInPort
)paren
suffix:semicolon
singleline_comment|// must return non-NULL; when a port_id
singleline_comment|// is not found, this pointer marks the
singleline_comment|// end of the singly linked list
r_if
c_cond
(paren
id|pLoggedInPort
op_ne
l_int|NULL
)paren
singleline_comment|// WWN found?
(brace
singleline_comment|// WWN has same port_id as last login?  (Of course, a properly
singleline_comment|// working FC device should NEVER ACCept a PDISC if it&squot;s
singleline_comment|// port_id changed, but check just in case...)
r_if
c_cond
(paren
(paren
id|fchs-&gt;s_id
op_amp
l_int|0xFFFFFF
)paren
op_eq
id|pLoggedInPort-&gt;port_id
)paren
(brace
singleline_comment|// Yes.  We were expecting PDISC?
r_if
c_cond
(paren
id|pLoggedInPort-&gt;pdisc
)paren
(brace
r_int
id|i
suffix:semicolon
singleline_comment|// PDISC expected -- set fields.  (PDISC, Originator)
id|SetLoginFields
c_func
(paren
id|pLoggedInPort
comma
id|fchs
comma
id|TRUE
comma
id|TRUE
)paren
suffix:semicolon
singleline_comment|// We are ready to resume FCP-SCSI to this device...
singleline_comment|// Do we need to start anything that was Queued?
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|TACH_SEST_LEN
suffix:semicolon
id|i
op_increment
)paren
(brace
singleline_comment|// see if any exchange for this PDISC&squot;d port was queued
r_if
c_cond
(paren
(paren
(paren
id|fchs-&gt;s_id
op_amp
l_int|0xFFFFFF
)paren
op_eq
(paren
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|fchs.d_id
op_amp
l_int|0xFFFFFF
)paren
)paren
op_logical_and
(paren
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|status
op_amp
id|EXCHANGE_QUEUED
)paren
)paren
(brace
id|fchs-&gt;reserved
op_assign
id|i
suffix:semicolon
singleline_comment|// copy ExchangeID
singleline_comment|//                printk(&quot; *Q x_ID %Xh after PDISC* &quot;,i);
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|EXCHANGE_QUEUED
comma
id|fchs
)paren
suffix:semicolon
)brace
)brace
singleline_comment|// Complete commands Q&squot;d while we were waiting for Login
id|UnblockScsiDevice
c_func
(paren
id|cpqfcHBAdata-&gt;HostAdapter
comma
id|pLoggedInPort
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;Not expecting PDISC (pdisc=FALSE)&bslash;n&quot;
)paren
suffix:semicolon
id|NeedLogin
op_assign
id|TRUE
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;PDISC PortID change: old %Xh, new %Xh&bslash;n&quot;
comma
id|pLoggedInPort-&gt;port_id
comma
id|fchs-&gt;s_id
op_amp
l_int|0xFFFFFF
)paren
suffix:semicolon
id|NeedLogin
op_assign
id|TRUE
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;PDISC ACC from unknown WWN&bslash;n&quot;
)paren
suffix:semicolon
id|NeedLogin
op_assign
id|TRUE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|NeedLogin
)paren
(brace
singleline_comment|// The PDISC failed.  Set login struct flags accordingly,
singleline_comment|// terminate any I/O to this port, and Q a PLOGI
r_if
c_cond
(paren
id|pLoggedInPort
)paren
singleline_comment|// FC device previously known?
(brace
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|ELS_LOGO
comma
singleline_comment|// Q Type
id|fchs
)paren
suffix:semicolon
singleline_comment|// has port_id to send to 
singleline_comment|// There are a variety of error scenarios which can result
singleline_comment|// in PDISC failure, so as a catchall, add the check for
singleline_comment|// duplicate port_id.
id|TestDuplicatePortId
c_func
(paren
id|cpqfcHBAdata
comma
id|pLoggedInPort
)paren
suffix:semicolon
singleline_comment|//    TriggerHBA( fcChip-&gt;Registers.ReMapMemBase, 0);
id|pLoggedInPort-&gt;pdisc
op_assign
id|FALSE
suffix:semicolon
id|pLoggedInPort-&gt;prli
op_assign
id|FALSE
suffix:semicolon
id|pLoggedInPort-&gt;plogi
op_assign
id|FALSE
suffix:semicolon
id|cpqfcTSTerminateExchange
c_func
(paren
id|cpqfcHBAdata
comma
op_amp
id|pLoggedInPort-&gt;ScsiNexus
comma
id|PORTID_CHANGED
)paren
suffix:semicolon
)brace
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|ELS_PLOGI
comma
id|fchs
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
singleline_comment|// login payload unacceptable - reason in ls_reject_code
singleline_comment|// Q up a Logout Request
id|printk
c_func
(paren
l_string|&quot;ERROR: Login Payload unacceptable!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ELS_PRLI
suffix:colon
singleline_comment|// we sent out PRLI
id|pLoggedInPort
op_assign
id|fcFindLoggedInPort
c_func
(paren
id|fcChip
comma
l_int|NULL
comma
singleline_comment|// don&squot;t search Scsi Nexus
(paren
id|fchs-&gt;s_id
op_amp
l_int|0xFFFFFF
)paren
comma
singleline_comment|// search linked list for port_id
l_int|NULL
comma
singleline_comment|// DON&squot;T search linked list for WWN
l_int|NULL
)paren
suffix:semicolon
singleline_comment|// don&squot;t care
r_if
c_cond
(paren
id|pLoggedInPort
op_eq
l_int|NULL
)paren
(brace
singleline_comment|// huh?
id|printk
c_func
(paren
l_string|&quot; Unexpected PRLI ACCept frame!&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|// Q a LOGOut here?
r_goto
id|Done
suffix:semicolon
)brace
singleline_comment|// verify the PRLI ACC payload
r_if
c_cond
(paren
op_logical_neg
id|verify_PRLI
c_func
(paren
id|fchs
comma
op_amp
id|ls_reject_code
)paren
)paren
(brace
singleline_comment|// PRLI Reply is acceptable; were we expecting it?
r_if
c_cond
(paren
id|pLoggedInPort-&gt;plogi
)paren
(brace
singleline_comment|// yes, we expected the PRLI ACC  (not PDISC; Originator)
id|SetLoginFields
c_func
(paren
id|pLoggedInPort
comma
id|fchs
comma
id|FALSE
comma
id|TRUE
)paren
suffix:semicolon
singleline_comment|// OK, let&squot;s send a REPORT_LUNS command to determine
singleline_comment|// whether VSA or PDA FCP-LUN addressing is used.
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|SCSI_REPORT_LUNS
comma
id|fchs
)paren
suffix:semicolon
singleline_comment|// It&squot;s possible that a device we were talking to changed 
singleline_comment|// port_id, and has logged back in.  This function ensures
singleline_comment|// that I/O will resume.
id|UnblockScsiDevice
c_func
(paren
id|cpqfcHBAdata-&gt;HostAdapter
comma
id|pLoggedInPort
)paren
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// huh?
id|printk
c_func
(paren
l_string|&quot; (unexpected) PRLI ACCept with plogi FALSE&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|// Q a LOGOut here?
r_goto
id|Done
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot; PRLI ACCept payload failed verify&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|// Q a LOGOut here?
)brace
r_break
suffix:semicolon
r_case
id|ELS_FLOGI
suffix:colon
singleline_comment|// we sent out FLOGI (Fabric Login)
singleline_comment|// update the upper 16 bits of our port_id in Tachyon
singleline_comment|// the switch adds those upper 16 bits when responding
singleline_comment|// to us (i.e. we are the destination_id)
id|fcChip-&gt;Registers.my_al_pa
op_assign
(paren
id|fchs-&gt;d_id
op_amp
l_int|0xFFFFFF
)paren
suffix:semicolon
id|writel
c_func
(paren
id|fcChip-&gt;Registers.my_al_pa
comma
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_TACH_My_ID
)paren
suffix:semicolon
singleline_comment|// now send out a PLOGI to the well known port_id 0xFFFFFC
id|fchs-&gt;s_id
op_assign
l_int|0xFFFFFC
suffix:semicolon
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|ELS_PLOGI
comma
id|fchs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ELS_FDISC
suffix:colon
singleline_comment|// we sent out FDISC (Fabric Discovery (Login))
id|printk
c_func
(paren
l_string|&quot; ELS_FDISC success &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ELS_SCR
suffix:colon
singleline_comment|// we sent out State Change Registration
singleline_comment|// now we can issue Name Service Request to find any
singleline_comment|// Fabric-connected devices we might want to login to.
id|fchs-&gt;s_id
op_assign
l_int|0xFFFFFC
suffix:semicolon
singleline_comment|// Name Server Address
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|FCS_NSR
comma
id|fchs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot; *Discarding unknown ACC frame, xID %04X/%04X* &quot;
comma
id|ox_id
comma
id|fchs-&gt;ox_rx_id
op_amp
l_int|0xffff
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|Done
suffix:colon
singleline_comment|// Regardless of whether the Reply is valid or not, the
singleline_comment|// the exchange is done - complete
id|cpqfcTSCompleteExchange
c_func
(paren
id|cpqfcHBAdata-&gt;PciDev
comma
id|fcChip
comma
(paren
id|fchs-&gt;ox_rx_id
op_rshift
l_int|16
)paren
)paren
suffix:semicolon
id|Quit
suffix:colon
r_return
suffix:semicolon
)brace
singleline_comment|// ****************  Fibre Channel Services  **************
singleline_comment|// This is where we process the Directory (Name) Service Reply
singleline_comment|// to know which devices are on the Fabric
DECL|function|ProcessFCS_Reply
r_static
r_void
id|ProcessFCS_Reply
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|TachFCHDR_GCMND
op_star
id|fchs
)paren
(brace
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
id|FC_EXCHANGES
op_star
id|Exchanges
op_assign
id|fcChip-&gt;Exchanges
suffix:semicolon
id|ULONG
id|ox_id
op_assign
(paren
id|fchs-&gt;ox_rx_id
op_rshift
l_int|16
)paren
suffix:semicolon
singleline_comment|//  ULONG ls_reject_code;
singleline_comment|//  PFC_LOGGEDIN_PORT pLoggedInPort, pLastLoggedInPort;
singleline_comment|// If this is a valid reply, then we MUST have sent a request.
singleline_comment|// Verify that we can find a valid request OX_ID corresponding to
singleline_comment|// this reply
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
(paren
id|fchs-&gt;ox_rx_id
op_rshift
l_int|16
)paren
)braket
dot
id|type
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; *Discarding Reply frame, xID %04X/%04X* &quot;
comma
id|ox_id
comma
id|fchs-&gt;ox_rx_id
op_amp
l_int|0xffff
)paren
suffix:semicolon
r_goto
id|Quit
suffix:semicolon
singleline_comment|// exit this routine
)brace
singleline_comment|// OK, we were expecting it.  Now check to see if it&squot;s a
singleline_comment|// &quot;Name Service&quot; Reply, and if so force a re-validation of
singleline_comment|// Fabric device logins (i.e. Start the login timeout and
singleline_comment|// send PDISC or PLOGI)
singleline_comment|// (Endianess Byte Swap?)
r_if
c_cond
(paren
id|fchs-&gt;pl
(braket
l_int|1
)braket
op_eq
l_int|0x02FC
)paren
singleline_comment|// Name Service
(brace
singleline_comment|// got a new (or NULL) list of Fabric attach devices... 
singleline_comment|// Invalidate current logins
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
op_assign
op_amp
id|fcChip-&gt;fcPorts
suffix:semicolon
r_while
c_loop
(paren
id|pLoggedInPort
)paren
singleline_comment|// for all ports which are expecting
singleline_comment|// PDISC after the next LIP, set the
singleline_comment|// logoutTimer
(brace
r_if
c_cond
(paren
(paren
id|pLoggedInPort-&gt;port_id
op_amp
l_int|0xFFFF00
)paren
singleline_comment|// Fabric device?
op_logical_and
(paren
id|pLoggedInPort-&gt;port_id
op_ne
l_int|0xFFFFFC
)paren
)paren
singleline_comment|// NOT the F_Port
(brace
id|pLoggedInPort-&gt;LOGO_timer
op_assign
l_int|6
suffix:semicolon
singleline_comment|// what&squot;s the Fabric timeout??
singleline_comment|// suspend any I/O in progress until
singleline_comment|// PDISC received...
id|pLoggedInPort-&gt;prli
op_assign
id|FALSE
suffix:semicolon
singleline_comment|// block FCP-SCSI commands
)brace
id|pLoggedInPort
op_assign
id|pLoggedInPort-&gt;pNextPort
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fchs-&gt;pl
(braket
l_int|2
)braket
op_eq
l_int|0x0280
)paren
singleline_comment|// ACCept?
(brace
singleline_comment|// Send PLOGI or PDISC to these Fabric devices
id|SendLogins
c_func
(paren
id|cpqfcHBAdata
comma
op_amp
id|fchs-&gt;pl
(braket
l_int|4
)braket
)paren
suffix:semicolon
)brace
singleline_comment|// As of this writing, the only reason to reject is because NO
singleline_comment|// devices are left on the Fabric.  We already started
singleline_comment|// &quot;logged out&quot; timers; if the device(s) don&squot;t come
singleline_comment|// back, we&squot;ll do the implicit logout in the heart beat 
singleline_comment|// timer routine
r_else
singleline_comment|// ReJecT
(brace
singleline_comment|// this just means no Fabric device is visible at this instant
)brace
)brace
singleline_comment|// Regardless of whether the Reply is valid or not, the
singleline_comment|// the exchange is done - complete
id|cpqfcTSCompleteExchange
c_func
(paren
id|cpqfcHBAdata-&gt;PciDev
comma
id|fcChip
comma
(paren
id|fchs-&gt;ox_rx_id
op_rshift
l_int|16
)paren
)paren
suffix:semicolon
id|Quit
suffix:colon
r_return
suffix:semicolon
)brace
DECL|function|AnalyzeIncomingFrame
r_static
r_void
id|AnalyzeIncomingFrame
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|ULONG
id|QNdx
)paren
(brace
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
id|FC_EXCHANGES
op_star
id|Exchanges
op_assign
id|fcChip-&gt;Exchanges
suffix:semicolon
id|PFC_LINK_QUE
id|fcLQ
op_assign
id|cpqfcHBAdata-&gt;fcLQ
suffix:semicolon
id|TachFCHDR_GCMND
op_star
id|fchs
op_assign
(paren
id|TachFCHDR_GCMND
op_star
)paren
id|fcLQ-&gt;Qitem
(braket
id|QNdx
)braket
dot
id|ulBuff
suffix:semicolon
singleline_comment|//  ULONG ls_reject_code;  // reason for rejecting login
id|LONG
id|ExchangeID
suffix:semicolon
singleline_comment|//  FC_LOGGEDIN_PORT *pLoggedInPort;
id|BOOLEAN
id|AbortAccept
suffix:semicolon
id|ENTER
c_func
(paren
l_string|&quot;AnalyzeIncomingFrame&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|fcLQ-&gt;Qitem
(braket
id|QNdx
)braket
dot
id|Type
)paren
singleline_comment|// FCP or Unknown
(brace
r_case
id|SFQ_UNKNOWN
suffix:colon
singleline_comment|// unknown frame (e.g. LIP position frame, NOP, etc.)
singleline_comment|// *********  FC-4 Device Data/ Fibre Channel Service *************
r_if
c_cond
(paren
(paren
(paren
id|fchs-&gt;d_id
op_amp
l_int|0xF0000000
)paren
op_eq
l_int|0
)paren
singleline_comment|// R_CTL (upper nibble) 0x0?
op_logical_and
(paren
id|fchs-&gt;f_ctl
op_amp
l_int|0x20000000
)paren
)paren
singleline_comment|// TYPE 20h is Fibre Channel Service
(brace
singleline_comment|// ************** FCS Reply **********************
r_if
c_cond
(paren
(paren
id|fchs-&gt;d_id
op_amp
l_int|0xff000000L
)paren
op_eq
l_int|0x03000000L
)paren
singleline_comment|// (31:23 R_CTL)
(brace
id|ProcessFCS_Reply
c_func
(paren
id|cpqfcHBAdata
comma
id|fchs
)paren
suffix:semicolon
)brace
singleline_comment|// end of  FCS logic
)brace
singleline_comment|// ***********  Extended Link Service **************
r_else
r_if
c_cond
(paren
id|fchs-&gt;d_id
op_amp
l_int|0x20000000
singleline_comment|// R_CTL 0x2?
op_logical_and
(paren
id|fchs-&gt;f_ctl
op_amp
l_int|0x01000000
)paren
)paren
singleline_comment|// TYPE = 1
(brace
singleline_comment|// these frames are either a response to
singleline_comment|// something we sent (0x23) or &quot;unsolicited&quot;
singleline_comment|// frames (0x22).
singleline_comment|// **************Extended Link REPLY **********************
singleline_comment|// R_CTL Solicited Control Reply
r_if
c_cond
(paren
(paren
id|fchs-&gt;d_id
op_amp
l_int|0xff000000L
)paren
op_eq
l_int|0x23000000L
)paren
singleline_comment|// (31:23 R_CTL)
(brace
id|ProcessELS_Reply
c_func
(paren
id|cpqfcHBAdata
comma
id|fchs
)paren
suffix:semicolon
)brace
singleline_comment|// end of  &quot;R_CTL Solicited Control Reply&quot;
singleline_comment|// **************Extended Link REQUEST **********************
singleline_comment|// (unsolicited commands from another port or task...)
singleline_comment|// R_CTL Ext Link REQUEST
r_else
r_if
c_cond
(paren
(paren
id|fchs-&gt;d_id
op_amp
l_int|0xff000000L
)paren
op_eq
l_int|0x22000000L
op_logical_and
(paren
id|fchs-&gt;ox_rx_id
op_ne
l_int|0xFFFFFFFFL
)paren
)paren
singleline_comment|// (ignore LIP frame)
(brace
id|ProcessELS_Request
c_func
(paren
id|cpqfcHBAdata
comma
id|fchs
)paren
suffix:semicolon
)brace
singleline_comment|// ************** LILP **********************
r_else
r_if
c_cond
(paren
(paren
id|fchs-&gt;d_id
op_amp
l_int|0xff000000L
)paren
op_eq
l_int|0x22000000L
op_logical_and
(paren
id|fchs-&gt;ox_rx_id
op_eq
l_int|0xFFFFFFFFL
)paren
)paren
singleline_comment|// (e.g., LIP frames)
(brace
singleline_comment|// SANMark specifies that when available, we must use
singleline_comment|// the LILP frame to determine which ALPAs to send Port Discovery
singleline_comment|// to...
r_if
c_cond
(paren
id|fchs-&gt;pl
(braket
l_int|0
)braket
op_eq
l_int|0x0711L
)paren
singleline_comment|//  ELS_PLOGI?
(brace
singleline_comment|//&t;  UCHAR *ptr = (UCHAR*)&amp;fchs-&gt;pl[1];
singleline_comment|//&t;  printk(&quot; %d ALPAs found&bslash;n&quot;, *ptr);
id|memcpy
c_func
(paren
id|fcChip-&gt;LILPmap
comma
op_amp
id|fchs-&gt;pl
(braket
l_int|1
)braket
comma
l_int|32
op_star
l_int|4
)paren
suffix:semicolon
singleline_comment|// 32 DWORDs
id|fcChip-&gt;Options.LILPin
op_assign
l_int|1
suffix:semicolon
singleline_comment|// our LILPmap is valid!
singleline_comment|// now post to make Port Discovery happen...
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|LINKACTIVE
comma
id|fchs
)paren
suffix:semicolon
)brace
)brace
)brace
singleline_comment|// *****************  BASIC LINK SERVICE *****************
r_else
r_if
c_cond
(paren
id|fchs-&gt;d_id
op_amp
l_int|0x80000000
singleline_comment|// R_CTL:
op_logical_and
singleline_comment|// Basic Link Service Request
op_logical_neg
(paren
id|fchs-&gt;f_ctl
op_amp
l_int|0xFF000000
)paren
)paren
singleline_comment|// type=0 for BLS
(brace
singleline_comment|// Check for ABTS (Abort Sequence)
r_if
c_cond
(paren
(paren
id|fchs-&gt;d_id
op_amp
l_int|0x8F000000
)paren
op_eq
l_int|0x81000000
)paren
(brace
singleline_comment|// look for OX_ID, S_ID pair that matches in our
singleline_comment|// fcExchanges table; if found, reply with ACCept and complete
singleline_comment|// the exchange
singleline_comment|// Per PLDA, an ABTS is sent by an initiator; therefore
singleline_comment|// assume that if we have an exhange open to the port who
singleline_comment|// sent ABTS, it will be the d_id of what we sent.  
r_for
c_loop
(paren
id|ExchangeID
op_assign
l_int|0
comma
id|AbortAccept
op_assign
id|FALSE
suffix:semicolon
id|ExchangeID
OL
id|TACH_SEST_LEN
suffix:semicolon
id|ExchangeID
op_increment
)paren
(brace
singleline_comment|// Valid &quot;target&quot; exchange 24-bit port_id matches? 
singleline_comment|// NOTE: For the case of handling Intiator AND Target
singleline_comment|// functions on the same chip, we can have TWO Exchanges
singleline_comment|// with the same OX_ID -- OX_ID/FFFF for the CMND, and
singleline_comment|// OX_ID/RX_ID for the XRDY or DATA frame(s).  Ideally,
singleline_comment|// we would like to support ABTS from Initiators or Targets,
singleline_comment|// but it&squot;s not clear that can be supported on Tachyon for
singleline_comment|// all cases (requires more investigation).
r_if
c_cond
(paren
(paren
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
dot
id|type
op_eq
id|SCSI_TWE
op_logical_or
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
dot
id|type
op_eq
id|SCSI_TRE
)paren
op_logical_and
(paren
(paren
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
dot
id|fchs.d_id
op_amp
l_int|0xFFFFFF
)paren
op_eq
(paren
id|fchs-&gt;s_id
op_amp
l_int|0xFFFFFF
)paren
)paren
)paren
(brace
singleline_comment|// target xchnge port_id matches -- how about OX_ID?
r_if
c_cond
(paren
(paren
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
dot
id|fchs.ox_rx_id
op_amp
l_int|0xFFFF0000
)paren
op_eq
(paren
id|fchs-&gt;ox_rx_id
op_amp
l_int|0xFFFF0000
)paren
)paren
singleline_comment|// yes! post ACCept response; will be completed by fcStart
(brace
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
dot
id|status
op_assign
id|TARGET_ABORT
suffix:semicolon
singleline_comment|// copy (add) rx_id field for simplified ACCept reply
id|fchs-&gt;ox_rx_id
op_assign
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
dot
id|fchs.ox_rx_id
suffix:semicolon
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|BLS_ABTS_ACC
comma
singleline_comment|// Q Type 
id|fchs
)paren
suffix:semicolon
singleline_comment|// void QueContent
id|AbortAccept
op_assign
id|TRUE
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ACCepting ABTS for x_ID %8.8Xh, SEST pair %8.8Xh&bslash;n&quot;
comma
id|fchs-&gt;ox_rx_id
comma
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
dot
id|fchs.ox_rx_id
)paren
suffix:semicolon
r_break
suffix:semicolon
singleline_comment|// ABTS can affect only ONE exchange -exit loop
)brace
)brace
)brace
singleline_comment|// end of FOR loop
r_if
c_cond
(paren
op_logical_neg
id|AbortAccept
)paren
singleline_comment|// can&squot;t ACCept ABTS - send Reject
(brace
id|printk
c_func
(paren
l_string|&quot;ReJecTing: can&squot;t find ExchangeID %8.8Xh for ABTS command&bslash;n&quot;
comma
id|fchs-&gt;ox_rx_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
dot
id|type
op_logical_and
op_logical_neg
(paren
id|fcChip-&gt;SEST-&gt;u
(braket
id|ExchangeID
)braket
dot
id|IWE.Hdr_Len
op_amp
l_int|0x80000000
)paren
)paren
(brace
id|cpqfcTSCompleteExchange
c_func
(paren
id|cpqfcHBAdata-&gt;PciDev
comma
id|fcChip
comma
id|ExchangeID
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;Unexpected ABTS ReJecT! SEST[%X] Dword 0: %Xh&bslash;n&quot;
comma
id|ExchangeID
comma
id|fcChip-&gt;SEST-&gt;u
(braket
id|ExchangeID
)braket
dot
id|IWE.Hdr_Len
)paren
suffix:semicolon
)brace
)brace
)brace
singleline_comment|// Check for BLS {ABTS? (Abort Sequence)} ACCept
r_else
r_if
c_cond
(paren
(paren
id|fchs-&gt;d_id
op_amp
l_int|0x8F000000
)paren
op_eq
l_int|0x84000000
)paren
(brace
singleline_comment|// target has responded with ACC for our ABTS;
singleline_comment|// complete the indicated exchange with ABORTED status 
singleline_comment|// Make no checks for correct RX_ID, since
singleline_comment|// all we need to conform ABTS ACC is the OX_ID.
singleline_comment|// Verify that the d_id matches!
id|ExchangeID
op_assign
(paren
id|fchs-&gt;ox_rx_id
op_rshift
l_int|16
)paren
op_amp
l_int|0x7FFF
suffix:semicolon
singleline_comment|// x_id from ACC
singleline_comment|//&t;printk(&quot;ABTS ACC x_ID 0x%04X 0x%04X, status %Xh&bslash;n&quot;, 
singleline_comment|//          fchs-&gt;ox_rx_id &gt;&gt; 16, fchs-&gt;ox_rx_id &amp; 0xffff,
singleline_comment|//          Exchanges-&gt;fcExchange[ExchangeID].status);
r_if
c_cond
(paren
id|ExchangeID
OL
id|TACH_SEST_LEN
)paren
singleline_comment|// x_ID makes sense
(brace
singleline_comment|// Does &quot;target&quot; exchange 24-bit port_id match? 
singleline_comment|// (See &quot;NOTE&quot; above for handling Intiator AND Target in
singleline_comment|// the same device driver)
singleline_comment|// First, if this is a target response, then we originated
singleline_comment|// (initiated) it with BLS_ABTS:
r_if
c_cond
(paren
(paren
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
dot
id|type
op_eq
id|BLS_ABTS
)paren
op_logical_and
singleline_comment|// Second, does the source of this ACC match the destination
singleline_comment|// of who we originally sent it to?
(paren
(paren
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
dot
id|fchs.d_id
op_amp
l_int|0xFFFFFF
)paren
op_eq
(paren
id|fchs-&gt;s_id
op_amp
l_int|0xFFFFFF
)paren
)paren
)paren
(brace
id|cpqfcTSCompleteExchange
c_func
(paren
id|cpqfcHBAdata-&gt;PciDev
comma
id|fcChip
comma
id|ExchangeID
)paren
suffix:semicolon
)brace
)brace
)brace
singleline_comment|// Check for BLS {ABTS? (Abort Sequence)} ReJecT
r_else
r_if
c_cond
(paren
(paren
id|fchs-&gt;d_id
op_amp
l_int|0x8F000000
)paren
op_eq
l_int|0x85000000
)paren
(brace
singleline_comment|// target has responded with RJT for our ABTS;
singleline_comment|// complete the indicated exchange with ABORTED status 
singleline_comment|// Make no checks for correct RX_ID, since
singleline_comment|// all we need to conform ABTS ACC is the OX_ID.
singleline_comment|// Verify that the d_id matches!
id|ExchangeID
op_assign
(paren
id|fchs-&gt;ox_rx_id
op_rshift
l_int|16
)paren
op_amp
l_int|0x7FFF
suffix:semicolon
singleline_comment|// x_id from ACC
singleline_comment|//&t;printk(&quot;BLS_ABTS RJT on Exchange 0x%04X 0x%04X&bslash;n&quot;, 
singleline_comment|//          fchs-&gt;ox_rx_id &gt;&gt; 16, fchs-&gt;ox_rx_id &amp; 0xffff);
r_if
c_cond
(paren
id|ExchangeID
OL
id|TACH_SEST_LEN
)paren
singleline_comment|// x_ID makes sense
(brace
singleline_comment|// Does &quot;target&quot; exchange 24-bit port_id match? 
singleline_comment|// (See &quot;NOTE&quot; above for handling Intiator AND Target in
singleline_comment|// the same device driver)
singleline_comment|// First, if this is a target response, then we originated
singleline_comment|// (initiated) it with BLS_ABTS:
r_if
c_cond
(paren
(paren
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
dot
id|type
op_eq
id|BLS_ABTS
)paren
op_logical_and
singleline_comment|// Second, does the source of this ACC match the destination
singleline_comment|// of who we originally sent it to?
(paren
(paren
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
dot
id|fchs.d_id
op_amp
l_int|0xFFFFFF
)paren
op_eq
(paren
id|fchs-&gt;s_id
op_amp
l_int|0xFFFFFF
)paren
)paren
)paren
(brace
singleline_comment|// YES! NOTE: There is a bug in CPQ&squot;s RA-4000 box 
singleline_comment|// where the &quot;reason code&quot; isn&squot;t returned in the payload
singleline_comment|// For now, simply presume the reject is because the target
singleline_comment|// already completed the exchange...
singleline_comment|//            printk(&quot;complete x_ID %Xh on ABTS RJT&bslash;n&quot;, ExchangeID);
id|cpqfcTSCompleteExchange
c_func
(paren
id|cpqfcHBAdata-&gt;PciDev
comma
id|fcChip
comma
id|ExchangeID
)paren
suffix:semicolon
)brace
)brace
)brace
singleline_comment|// end of ABTS check
)brace
singleline_comment|// end of Basic Link Service Request
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;AnalyzeIncomingFrame: unknown type: %Xh(%d)&bslash;n&quot;
comma
id|fcLQ-&gt;Qitem
(braket
id|QNdx
)braket
dot
id|Type
comma
id|fcLQ-&gt;Qitem
(braket
id|QNdx
)braket
dot
id|Type
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
singleline_comment|// Function for Port Discovery necessary after every FC 
singleline_comment|// initialization (e.g. LIP).
singleline_comment|// Also may be called if from Fabric Name Service logic.
DECL|function|SendLogins
r_static
r_void
id|SendLogins
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|__u32
op_star
id|FabricPortIds
)paren
(brace
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
id|FC_EXCHANGES
op_star
id|Exchanges
op_assign
id|fcChip-&gt;Exchanges
suffix:semicolon
id|ULONG
id|ulStatus
op_assign
l_int|0
suffix:semicolon
id|TachFCHDR_GCMND
id|fchs
suffix:semicolon
singleline_comment|// copy fields for transmission
r_int
id|i
suffix:semicolon
id|ULONG
id|loginType
suffix:semicolon
id|LONG
id|ExchangeID
suffix:semicolon
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
suffix:semicolon
id|__u32
id|PortIds
(braket
id|number_of_al_pa
)braket
suffix:semicolon
r_int
id|NumberOfPorts
op_assign
l_int|0
suffix:semicolon
singleline_comment|// We&squot;re going to presume (for now) that our limit of Fabric devices
singleline_comment|// is the same as the number of alpa on a private loop (126 devices).
singleline_comment|// (Of course this could be changed to support however many we have
singleline_comment|// memory for).
id|memset
c_func
(paren
op_amp
id|PortIds
(braket
l_int|0
)braket
comma
l_int|0
comma
r_sizeof
(paren
id|PortIds
)paren
)paren
suffix:semicolon
singleline_comment|// First, check if this login is for our own Link Initialization
singleline_comment|// (e.g. LIP on FC-AL), or if we have knowledge of Fabric devices
singleline_comment|// from a switch.  If we are logging into Fabric devices, we&squot;ll
singleline_comment|// have a non-NULL FabricPortId pointer
r_if
c_cond
(paren
id|FabricPortIds
op_ne
l_int|NULL
)paren
singleline_comment|// may need logins
(brace
r_int
id|LastPort
op_assign
id|FALSE
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|LastPort
)paren
(brace
singleline_comment|// port IDs From NSR payload; byte swap needed?
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
id|FabricPortIds
comma
(paren
id|UCHAR
op_star
)paren
op_amp
id|PortIds
(braket
id|i
)braket
comma
l_int|4
)paren
suffix:semicolon
singleline_comment|//      printk(&quot;FPortId[%d] %Xh &quot;, i, PortIds[i]);
r_if
c_cond
(paren
id|PortIds
(braket
id|i
)braket
op_amp
l_int|0x80000000
)paren
(brace
id|LastPort
op_assign
id|TRUE
suffix:semicolon
)brace
id|PortIds
(braket
id|i
)braket
op_and_assign
l_int|0xFFFFFF
suffix:semicolon
singleline_comment|// get 24-bit port_id
singleline_comment|// some non-Fabric devices (like the Crossroads Fibre/Scsi bridge)
singleline_comment|// erroneously use ALPA 0.
r_if
c_cond
(paren
id|PortIds
(braket
id|i
)braket
)paren
(brace
singleline_comment|// need non-zero port_id...
id|i
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_ge
id|number_of_al_pa
)paren
(brace
singleline_comment|// (in)sanity check
r_break
suffix:semicolon
)brace
id|FabricPortIds
op_increment
suffix:semicolon
singleline_comment|// next...
)brace
id|NumberOfPorts
op_assign
id|i
suffix:semicolon
singleline_comment|//    printk(&quot;NumberOf Fabric ports %d&quot;, NumberOfPorts);
)brace
r_else
singleline_comment|// need to send logins on our &quot;local&quot; link
(brace
singleline_comment|// are we a loop port?  If so, check for reception of LILP frame,
singleline_comment|// and if received use it (SANMark requirement)
r_if
c_cond
(paren
id|fcChip-&gt;Options.LILPin
)paren
(brace
r_int
id|j
op_assign
l_int|0
suffix:semicolon
singleline_comment|// sanity check on number of ALPAs from LILP frame...
singleline_comment|// For format of LILP frame, see FC-AL specs or 
singleline_comment|// &quot;Fibre Channel Bench Reference&quot;, J. Stai, 1995 (ISBN 1-879936-17-8)
singleline_comment|// First byte is number of ALPAs
id|i
op_assign
id|fcChip-&gt;LILPmap
(braket
l_int|0
)braket
op_ge
(paren
l_int|32
op_star
l_int|4
)paren
ques
c_cond
l_int|32
op_star
l_int|4
suffix:colon
id|fcChip-&gt;LILPmap
(braket
l_int|0
)braket
suffix:semicolon
id|NumberOfPorts
op_assign
id|i
suffix:semicolon
singleline_comment|//      printk(&quot; LILP alpa count %d &quot;, i);
r_while
c_loop
(paren
id|i
OG
l_int|0
)paren
(brace
id|PortIds
(braket
id|j
)braket
op_assign
id|fcChip-&gt;LILPmap
(braket
l_int|1
op_plus
id|j
)braket
suffix:semicolon
id|j
op_increment
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
)brace
r_else
singleline_comment|// have to send login to everybody
(brace
r_int
id|j
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
id|number_of_al_pa
suffix:semicolon
id|NumberOfPorts
op_assign
id|i
suffix:semicolon
r_while
c_loop
(paren
id|i
OG
l_int|0
)paren
(brace
id|PortIds
(braket
id|j
)braket
op_assign
id|valid_al_pa
(braket
id|j
)braket
suffix:semicolon
singleline_comment|// all legal ALPAs
id|j
op_increment
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
)brace
)brace
singleline_comment|// Now we have a copy of the port_ids (and how many)...
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NumberOfPorts
suffix:semicolon
id|i
op_increment
)paren
(brace
singleline_comment|// 24-bit FC Port ID
id|fchs.s_id
op_assign
id|PortIds
(braket
id|i
)braket
suffix:semicolon
singleline_comment|// note: only 8-bits used for ALPA
singleline_comment|// don&squot;t log into ourselves (Linux Scsi disk scan will stop on
singleline_comment|// no TARGET support error on us, and quit trying for rest of devices)
r_if
c_cond
(paren
(paren
id|fchs.s_id
op_amp
l_int|0xFF
)paren
op_eq
(paren
id|fcChip-&gt;Registers.my_al_pa
op_amp
l_int|0xFF
)paren
)paren
(brace
r_continue
suffix:semicolon
)brace
singleline_comment|// fabric login needed?
r_if
c_cond
(paren
(paren
id|fchs.s_id
op_eq
l_int|0
)paren
op_logical_or
(paren
id|fcChip-&gt;Options.fabric
op_eq
l_int|1
)paren
)paren
(brace
id|fcChip-&gt;Options.flogi
op_assign
l_int|1
suffix:semicolon
singleline_comment|// fabric needs longer for login
singleline_comment|// Do we need FLOGI or FDISC?
id|pLoggedInPort
op_assign
id|fcFindLoggedInPort
c_func
(paren
id|fcChip
comma
l_int|NULL
comma
singleline_comment|// don&squot;t search SCSI Nexus
l_int|0xFFFFFC
comma
singleline_comment|// search linked list for Fabric port_id
l_int|NULL
comma
singleline_comment|// don&squot;t search WWN
l_int|NULL
)paren
suffix:semicolon
singleline_comment|// (don&squot;t care about end of list)
r_if
c_cond
(paren
id|pLoggedInPort
)paren
singleline_comment|// If found, we have prior experience with
singleline_comment|// this port -- check whether PDISC is needed
(brace
r_if
c_cond
(paren
id|pLoggedInPort-&gt;flogi
)paren
(brace
singleline_comment|// does the switch support FDISC?? (FLOGI for now...)
id|loginType
op_assign
id|ELS_FLOGI
suffix:semicolon
singleline_comment|// prior FLOGI still valid
)brace
r_else
id|loginType
op_assign
id|ELS_FLOGI
suffix:semicolon
singleline_comment|// expired FLOGI
)brace
r_else
singleline_comment|// first FLOGI?
id|loginType
op_assign
id|ELS_FLOGI
suffix:semicolon
id|fchs.s_id
op_assign
l_int|0xFFFFFE
suffix:semicolon
singleline_comment|// well known F_Port address
singleline_comment|// Fabrics are not required to support FDISC, and
singleline_comment|// it&squot;s not clear if that helps us anyway, since
singleline_comment|// we&squot;ll want a Name Service Request to re-verify
singleline_comment|// visible devices...
singleline_comment|// Consequently, we always want our upper 16 bit
singleline_comment|// port_id to be zero (we&squot;ll be rejected if we
singleline_comment|// use our prior port_id if we&squot;ve been plugged into
singleline_comment|// a different switch port).
singleline_comment|// Trick Tachyon to send to ALPA 0 (see TL/TS UG, pg 87)
singleline_comment|// If our ALPA is 55h for instance, we want the FC frame
singleline_comment|// s_id to be 0x000055, while Tach&squot;s my_al_pa register
singleline_comment|// must be 0x000155, to force an OPN at ALPA 0 
singleline_comment|// (the Fabric port)
id|fcChip-&gt;Registers.my_al_pa
op_and_assign
l_int|0xFF
suffix:semicolon
singleline_comment|// only use ALPA for FLOGI
id|writel
c_func
(paren
id|fcChip-&gt;Registers.my_al_pa
op_or
l_int|0x0100
comma
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_TACH_My_ID
)paren
suffix:semicolon
)brace
r_else
singleline_comment|// not FLOGI...
(brace
singleline_comment|// should we send PLOGI or PDISC?  Check if any prior port_id
singleline_comment|// (e.g. alpa) completed a PLOGI/PRLI exchange by checking 
singleline_comment|// the pdisc flag.
id|pLoggedInPort
op_assign
id|fcFindLoggedInPort
c_func
(paren
id|fcChip
comma
l_int|NULL
comma
singleline_comment|// don&squot;t search SCSI Nexus
id|fchs.s_id
comma
singleline_comment|// search linked list for al_pa
l_int|NULL
comma
singleline_comment|// don&squot;t search WWN
l_int|NULL
)paren
suffix:semicolon
singleline_comment|// (don&squot;t care about end of list)
r_if
c_cond
(paren
id|pLoggedInPort
)paren
singleline_comment|// If found, we have prior experience with
singleline_comment|// this port -- check whether PDISC is needed
(brace
r_if
c_cond
(paren
id|pLoggedInPort-&gt;pdisc
)paren
(brace
id|loginType
op_assign
id|ELS_PDISC
suffix:semicolon
singleline_comment|// prior PLOGI and PRLI maybe still valid
)brace
r_else
id|loginType
op_assign
id|ELS_PLOGI
suffix:semicolon
singleline_comment|// prior knowledge, but can&squot;t use PDISC
)brace
r_else
singleline_comment|// never talked to this port_id before
id|loginType
op_assign
id|ELS_PLOGI
suffix:semicolon
singleline_comment|// prior knowledge, but can&squot;t use PDISC
)brace
id|ulStatus
op_assign
id|cpqfcTSBuildExchange
c_func
(paren
id|cpqfcHBAdata
comma
id|loginType
comma
singleline_comment|// e.g. PLOGI
op_amp
id|fchs
comma
singleline_comment|// no incoming frame (we are originator)
l_int|NULL
comma
singleline_comment|// no data (no scatter/gather list)
op_amp
id|ExchangeID
)paren
suffix:semicolon
singleline_comment|// fcController-&gt;fcExchanges index, -1 if failed
r_if
c_cond
(paren
op_logical_neg
id|ulStatus
)paren
singleline_comment|// Exchange setup OK?
(brace
id|ulStatus
op_assign
id|cpqfcTSStartExchange
c_func
(paren
id|cpqfcHBAdata
comma
id|ExchangeID
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ulStatus
)paren
(brace
singleline_comment|// submitted to Tach&squot;s Outbound Que (ERQ PI incremented)
singleline_comment|// waited for completion for ELS type (Login frames issued
singleline_comment|// synchronously)
r_if
c_cond
(paren
id|loginType
op_eq
id|ELS_PDISC
)paren
(brace
singleline_comment|// now, we really shouldn&squot;t Revalidate SEST exchanges until
singleline_comment|// we get an ACC reply from our target and verify that
singleline_comment|// the target address/WWN is unchanged.  However, when a fast
singleline_comment|// target gets the PDISC, they can send SEST Exchange data
singleline_comment|// before we even get around to processing the PDISC ACC.
singleline_comment|// Consequently, we lose the I/O.
singleline_comment|// To avoid this, go ahead and Revalidate when the PDISC goes
singleline_comment|// out, anticipating that the ACC will be truly acceptable
singleline_comment|// (this happens 99.9999....% of the time).
singleline_comment|// If we revalidate a SEST write, and write data goes to a
singleline_comment|// target that is NOT the one we originated the WRITE to,
singleline_comment|// that target is required (FCP-SCSI specs, etc) to discard 
singleline_comment|// our WRITE data.
singleline_comment|// Re-validate SEST entries (Tachyon hardware assists)
id|RevalidateSEST
c_func
(paren
id|cpqfcHBAdata-&gt;HostAdapter
comma
id|pLoggedInPort
)paren
suffix:semicolon
singleline_comment|//TriggerHBA( fcChip-&gt;Registers.ReMapMemBase, 1);
)brace
)brace
r_else
singleline_comment|// give up immediately on error
(brace
macro_line|#ifdef LOGIN_DBG
id|printk
c_func
(paren
l_string|&quot;SendLogins: fcStartExchange failed: %Xh&bslash;n&quot;
comma
id|ulStatus
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0x080
)paren
singleline_comment|// LDn during Port Disc.
(brace
id|ulStatus
op_assign
id|LNKDWN_OSLS
suffix:semicolon
macro_line|#ifdef LOGIN_DBG
id|printk
c_func
(paren
l_string|&quot;SendLogins: PortDisc aborted (LDn) @alpa %Xh&bslash;n&quot;
comma
id|fchs.s_id
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
singleline_comment|// Check the exchange for bad status (i.e. FrameTimeOut),
singleline_comment|// and complete on bad status (most likely due to BAD_ALPA)
singleline_comment|// on LDn, DPC function may already complete (ABORT) a started
singleline_comment|// exchange, so check type first (type = 0 on complete).
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
dot
id|status
)paren
(brace
macro_line|#ifdef LOGIN_DBG 
id|printk
c_func
(paren
l_string|&quot;completing x_ID %X on status %Xh&bslash;n&quot;
comma
id|ExchangeID
comma
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
dot
id|status
)paren
suffix:semicolon
macro_line|#endif
id|cpqfcTSCompleteExchange
c_func
(paren
id|cpqfcHBAdata-&gt;PciDev
comma
id|fcChip
comma
id|ExchangeID
)paren
suffix:semicolon
)brace
)brace
r_else
singleline_comment|// Xchange setup failed...
(brace
macro_line|#ifdef LOGIN_DBG
id|printk
c_func
(paren
l_string|&quot;FC: cpqfcTSBuildExchange failed: %Xh&bslash;n&quot;
comma
id|ulStatus
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|ulStatus
)paren
(brace
singleline_comment|// set the event signifying that all ALPAs were sent out.
macro_line|#ifdef LOGIN_DBG
id|printk
c_func
(paren
l_string|&quot;SendLogins: PortDiscDone&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|cpqfcHBAdata-&gt;PortDiscDone
op_assign
l_int|1
suffix:semicolon
singleline_comment|// TL/TS UG, pg. 184
singleline_comment|// 0x0065 = 100ms for RT_TOV
singleline_comment|// 0x01f5 = 500ms for ED_TOV
id|fcChip-&gt;Registers.ed_tov.value
op_assign
l_int|0x006501f5L
suffix:semicolon
id|writel
c_func
(paren
id|fcChip-&gt;Registers.ed_tov.value
comma
(paren
id|fcChip-&gt;Registers.ed_tov.address
)paren
)paren
suffix:semicolon
singleline_comment|// set the LP_TOV back to ED_TOV (i.e. 500 ms)
id|writel
c_func
(paren
l_int|0x00000010
comma
id|fcChip-&gt;Registers.ReMapMemBase
op_plus
id|TL_MEM_FM_TIMEOUT2
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;SendLogins: failed at xchng %Xh, alpa %Xh, status %Xh&bslash;n&quot;
comma
id|ExchangeID
comma
id|fchs.s_id
comma
id|ulStatus
)paren
suffix:semicolon
)brace
id|LEAVE
c_func
(paren
l_string|&quot;SendLogins&quot;
)paren
suffix:semicolon
)brace
singleline_comment|// for REPORT_LUNS documentation, see &quot;In-Depth Exploration of Scsi&quot;,
singleline_comment|// D. Deming, 1994, pg 7-19 (ISBN 1-879936-08-9)
DECL|function|ScsiReportLunsDone
r_static
r_void
id|ScsiReportLunsDone
c_func
(paren
id|Scsi_Cmnd
op_star
id|Cmnd
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|HostAdapter
op_assign
id|Cmnd-&gt;host
suffix:semicolon
id|CPQFCHBA
op_star
id|cpqfcHBAdata
op_assign
(paren
id|CPQFCHBA
op_star
)paren
id|HostAdapter-&gt;hostdata
suffix:semicolon
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
id|FC_EXCHANGES
op_star
id|Exchanges
op_assign
id|fcChip-&gt;Exchanges
suffix:semicolon
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
suffix:semicolon
r_int
id|LunListLen
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|ULONG
id|x_ID
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
id|UCHAR
op_star
id|ucBuff
op_assign
id|Cmnd-&gt;request_buffer
suffix:semicolon
singleline_comment|//  printk(&quot;cpqfcTS: ReportLunsDone &bslash;n&quot;);
singleline_comment|// first, we need to find the Exchange for this command,
singleline_comment|// so we can find the fcPort struct to make the indicated
singleline_comment|// changes.
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|TACH_SEST_LEN
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|type
singleline_comment|// exchange defined?
op_logical_and
(paren
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|Cmnd
op_eq
id|Cmnd
)paren
)paren
singleline_comment|// matches?
(brace
id|x_ID
op_assign
id|i
suffix:semicolon
singleline_comment|// found exchange!
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|x_ID
op_eq
l_int|0xFFFFFFFF
)paren
(brace
singleline_comment|//    printk(&quot;cpqfcTS: ReportLuns failed - no FC Exchange&bslash;n&quot;);
r_goto
id|Done
suffix:semicolon
singleline_comment|// Report Luns FC Exchange gone; 
singleline_comment|// exchange probably Terminated by Implicit logout
)brace
singleline_comment|// search linked list for the port_id we sent INQUIRY to
id|pLoggedInPort
op_assign
id|fcFindLoggedInPort
c_func
(paren
id|fcChip
comma
l_int|NULL
comma
singleline_comment|// DON&squot;T search Scsi Nexus (we will set it)
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|fchs.d_id
op_amp
l_int|0xFFFFFF
comma
l_int|NULL
comma
singleline_comment|// DON&squot;T search linked list for FC WWN
l_int|NULL
)paren
suffix:semicolon
singleline_comment|// DON&squot;T care about end of list
r_if
c_cond
(paren
op_logical_neg
id|pLoggedInPort
)paren
(brace
singleline_comment|//    printk(&quot;cpqfcTS: ReportLuns failed - device gone&bslash;n&quot;);
r_goto
id|Done
suffix:semicolon
singleline_comment|// error! can&squot;t find logged in Port
)brace
id|LunListLen
op_assign
id|ucBuff
(braket
l_int|3
)braket
suffix:semicolon
id|LunListLen
op_add_assign
id|ucBuff
(braket
l_int|2
)braket
op_rshift
l_int|8
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|LunListLen
)paren
singleline_comment|// failed
(brace
singleline_comment|// generically speaking, a soft error means we should retry...
r_if
c_cond
(paren
(paren
id|Cmnd-&gt;result
op_rshift
l_int|16
)paren
op_eq
id|DID_SOFT_ERROR
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|Cmnd-&gt;sense_buffer
(braket
l_int|2
)braket
op_amp
l_int|0xF
)paren
op_eq
l_int|0x6
)paren
op_logical_and
(paren
id|Cmnd-&gt;sense_buffer
(braket
l_int|12
)braket
op_eq
l_int|0x29
)paren
)paren
singleline_comment|// Sense Code &quot;reset&quot;
(brace
id|TachFCHDR_GCMND
op_star
id|fchs
op_assign
op_amp
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|fchs
suffix:semicolon
singleline_comment|// did we fail because of &quot;check condition, device reset?&quot;
singleline_comment|// e.g. the device was reset (i.e., at every power up)
singleline_comment|// retry the Report Luns
singleline_comment|// who are we sending it to?
singleline_comment|// we know this because we have a copy of the command
singleline_comment|// frame from the original Report Lun command -
singleline_comment|// switch the d_id/s_id fields, because the Exchange Build
singleline_comment|// context is &quot;reply to source&quot;.
id|fchs-&gt;s_id
op_assign
id|fchs-&gt;d_id
suffix:semicolon
singleline_comment|// (temporarily re-use the struct)
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|SCSI_REPORT_LUNS
comma
id|fchs
)paren
suffix:semicolon
)brace
)brace
r_else
singleline_comment|// probably, the device doesn&squot;t support Report Luns
id|pLoggedInPort-&gt;ScsiNexus.VolumeSetAddressing
op_assign
l_int|0
suffix:semicolon
)brace
r_else
singleline_comment|// we have LUN info - check VSA mode
(brace
singleline_comment|// for now, assume all LUNs will have same addr mode
singleline_comment|// for VSA, payload byte 8 will be 0x40; otherwise, 0
id|pLoggedInPort-&gt;ScsiNexus.VolumeSetAddressing
op_assign
id|ucBuff
(braket
l_int|8
)braket
suffix:semicolon
singleline_comment|// Since we got a Report Luns answer, set lun masking flag
id|pLoggedInPort-&gt;ScsiNexus.LunMasking
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|LunListLen
OG
l_int|8
op_star
id|CPQFCTS_MAX_LUN
)paren
(brace
singleline_comment|// We expect CPQFCTS_MAX_LUN max
id|LunListLen
op_assign
l_int|8
op_star
id|CPQFCTS_MAX_LUN
suffix:semicolon
)brace
multiline_comment|/*   &n;    printk(&quot;Device WWN %08X%08X Reports Luns @: &quot;, &n;          (ULONG)(pLoggedInPort-&gt;u.liWWN &amp;0xFFFFFFFF), &n;          (ULONG)(pLoggedInPort-&gt;u.liWWN&gt;&gt;32));&n;&t;    &n;    for( i=8; i&lt;LunListLen+8; i+=8)&n;    {  &n;      printk(&quot;%02X%02X &quot;, ucBuff[i], ucBuff[i+1] );&n;    }&n;    printk(&quot;&bslash;n&quot;);&n;*/
singleline_comment|// Since the device was kind enough to tell us where the
singleline_comment|// LUNs are, lets ensure they are contiguous for Linux&squot;s
singleline_comment|// SCSI driver scan, which expects them to start at 0.
singleline_comment|// Since Linux only supports 8 LUNs, only copy the first
singleline_comment|// eight from the report luns command
singleline_comment|// e.g., the Compaq RA4x00 f/w Rev 2.54 and above may report
singleline_comment|// LUNs 4001, 4004, etc., because other LUNs are masked from
singleline_comment|// this HBA (owned by someone else).  We&squot;ll make those appear as
singleline_comment|// LUN 0, 1... to Linux
(brace
r_int
id|j
suffix:semicolon
r_int
id|AppendLunList
op_assign
l_int|0
suffix:semicolon
singleline_comment|// Walk through the LUN list.  The &squot;j&squot; array number is
singleline_comment|// Linux&squot;s lun #, while the value of .lun[j] is the target&squot;s
singleline_comment|// lun #.
singleline_comment|// Once we build a LUN list, it&squot;s possible for a known device 
singleline_comment|// to go offline while volumes (LUNs) are added.  Later,
singleline_comment|// the device will do another PLOGI ... Report Luns command,
singleline_comment|// and we must not alter the existing Linux Lun map.
singleline_comment|// (This will be very rare).
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|CPQFCTS_MAX_LUN
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pLoggedInPort-&gt;ScsiNexus.lun
(braket
id|j
)braket
op_ne
l_int|0xFF
)paren
(brace
id|AppendLunList
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|AppendLunList
)paren
(brace
r_int
id|k
suffix:semicolon
r_int
id|FreeLunIndex
suffix:semicolon
singleline_comment|//        printk(&quot;cpqfcTS: AppendLunList&bslash;n&quot;);
singleline_comment|// If we get a new Report Luns, we cannot change
singleline_comment|// any existing LUN mapping! (Only additive entry)
singleline_comment|// For all LUNs in ReportLun list
singleline_comment|// if RL lun != ScsiNexus lun
singleline_comment|//   if RL lun present in ScsiNexus lun[], continue
singleline_comment|//   else find ScsiNexus lun[]==FF and add, continue
r_for
c_loop
(paren
id|i
op_assign
l_int|8
comma
id|j
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|LunListLen
op_plus
l_int|8
op_logical_and
id|j
OL
id|CPQFCTS_MAX_LUN
suffix:semicolon
id|i
op_add_assign
l_int|8
comma
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pLoggedInPort-&gt;ScsiNexus.lun
(braket
id|j
)braket
op_ne
id|ucBuff
(braket
id|i
op_plus
l_int|1
)braket
)paren
(brace
singleline_comment|// something changed from the last Report Luns
id|printk
c_func
(paren
l_string|&quot; cpqfcTS: Report Lun change!&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
comma
id|FreeLunIndex
op_assign
id|CPQFCTS_MAX_LUN
suffix:semicolon
id|k
OL
id|CPQFCTS_MAX_LUN
suffix:semicolon
id|k
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pLoggedInPort-&gt;ScsiNexus.lun
(braket
id|k
)braket
op_eq
l_int|0xFF
)paren
(brace
id|FreeLunIndex
op_assign
id|k
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pLoggedInPort-&gt;ScsiNexus.lun
(braket
id|k
)braket
op_eq
id|ucBuff
(braket
id|i
op_plus
l_int|1
)braket
)paren
(brace
r_break
suffix:semicolon
)brace
singleline_comment|// we already masked this lun
)brace
r_if
c_cond
(paren
id|k
op_ge
id|CPQFCTS_MAX_LUN
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; no room for new LUN %d&bslash;n&quot;
comma
id|ucBuff
(braket
id|i
op_plus
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|k
op_eq
id|FreeLunIndex
)paren
singleline_comment|// need to add LUN
(brace
id|pLoggedInPort-&gt;ScsiNexus.lun
(braket
id|k
)braket
op_assign
id|ucBuff
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
singleline_comment|//&t;      printk(&quot;add [%d]-&gt;%02d&bslash;n&quot;, k, pLoggedInPort-&gt;ScsiNexus.lun[k]);
)brace
r_else
(brace
singleline_comment|// lun already known
)brace
r_break
suffix:semicolon
)brace
)brace
singleline_comment|// print out the new list...
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|CPQFCTS_MAX_LUN
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pLoggedInPort-&gt;ScsiNexus.lun
(braket
id|j
)braket
op_eq
l_int|0xFF
)paren
(brace
r_break
suffix:semicolon
)brace
singleline_comment|// done
singleline_comment|//&t;  printk(&quot;[%d]-&gt;%02d &quot;, j, pLoggedInPort-&gt;ScsiNexus.lun[j]);
)brace
)brace
r_else
(brace
singleline_comment|//&t;  printk(&quot;Linux SCSI LUNs[] -&gt; Device LUNs: &quot;);
singleline_comment|// first time - this is easy
r_for
c_loop
(paren
id|i
op_assign
l_int|8
comma
id|j
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|LunListLen
op_plus
l_int|8
op_logical_and
id|j
OL
id|CPQFCTS_MAX_LUN
suffix:semicolon
id|i
op_add_assign
l_int|8
comma
id|j
op_increment
)paren
(brace
id|pLoggedInPort-&gt;ScsiNexus.lun
(braket
id|j
)braket
op_assign
id|ucBuff
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
singleline_comment|//&t;  printk(&quot;[%d]-&gt;%02d &quot;, j, pLoggedInPort-&gt;ScsiNexus.lun[j]);
)brace
singleline_comment|//&t;printk(&quot;&bslash;n&quot;);
)brace
)brace
)brace
id|Done
suffix:colon
)brace
r_static
r_void
DECL|function|call_scsi_done
id|call_scsi_done
c_func
(paren
id|Scsi_Cmnd
op_star
id|Cmnd
)paren
(brace
singleline_comment|// We have to reinitialize sent_command here, so the scsi-mid
singleline_comment|// layer won&squot;t re-use the scsi command leaving it set incorrectly.
singleline_comment|// (incorrectly for our purposes...it&squot;s normally unused.)
r_if
c_cond
(paren
id|Cmnd-&gt;SCp.sent_command
op_ne
l_int|0
)paren
(brace
singleline_comment|// was it a passthru?
id|Cmnd-&gt;SCp.sent_command
op_assign
l_int|0
suffix:semicolon
id|Cmnd-&gt;result
op_and_assign
l_int|0xff00ffff
suffix:semicolon
id|Cmnd-&gt;result
op_or_assign
(paren
id|DID_PASSTHROUGH
op_lshift
l_int|16
)paren
suffix:semicolon
singleline_comment|// prevents retry
)brace
r_if
c_cond
(paren
id|Cmnd-&gt;scsi_done
op_ne
l_int|NULL
)paren
(paren
op_star
id|Cmnd-&gt;scsi_done
)paren
(paren
id|Cmnd
)paren
suffix:semicolon
)brace
singleline_comment|// After successfully getting a &quot;Process Login&quot; (PRLI) from an
singleline_comment|// FC port, we want to Discover the LUNs so that we know the
singleline_comment|// addressing type (e.g., FCP-SCSI Volume Set Address, Peripheral
singleline_comment|// Unit Device), and whether SSP (Selective Storage Presentation or
singleline_comment|// Lun Masking) has made the LUN numbers non-zero based or 
singleline_comment|// non-contiguous.  To remain backward compatible with the SCSI-2
singleline_comment|// driver model, which expects a contiguous LUNs starting at 0,
singleline_comment|// will use the ReportLuns info to map from &quot;device&quot; to &quot;Linux&quot; 
singleline_comment|// LUNs.
DECL|function|IssueReportLunsCommand
r_static
r_void
id|IssueReportLunsCommand
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|TachFCHDR_GCMND
op_star
id|fchs
)paren
(brace
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
suffix:semicolon
id|Scsi_Cmnd
op_star
id|Cmnd
suffix:semicolon
id|LONG
id|x_ID
suffix:semicolon
id|ULONG
id|ulStatus
suffix:semicolon
id|UCHAR
op_star
id|ucBuff
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpqfcHBAdata-&gt;PortDiscDone
)paren
singleline_comment|// cleared by LDn
(brace
id|printk
c_func
(paren
l_string|&quot;Discard Q&squot;d ReportLun command&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
singleline_comment|// find the device (from port_id) we&squot;re talking to
id|pLoggedInPort
op_assign
id|fcFindLoggedInPort
c_func
(paren
id|fcChip
comma
l_int|NULL
comma
singleline_comment|// DON&squot;T search Scsi Nexus 
id|fchs-&gt;s_id
op_amp
l_int|0xFFFFFF
comma
l_int|NULL
comma
singleline_comment|// DON&squot;T search linked list for FC WWN
l_int|NULL
)paren
suffix:semicolon
singleline_comment|// DON&squot;T care about end of list
r_if
c_cond
(paren
id|pLoggedInPort
)paren
singleline_comment|// we&squot;d BETTER find it!
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|pLoggedInPort-&gt;fcp_info
op_amp
id|TARGET_FUNCTION
)paren
)paren
(brace
r_goto
id|Done
suffix:semicolon
)brace
singleline_comment|// forget it - FC device not a &quot;target&quot;
singleline_comment|// now use the port&squot;s Scsi Command buffer for the 
singleline_comment|// Report Luns Command
id|Cmnd
op_assign
op_amp
id|pLoggedInPort-&gt;ScsiCmnd
suffix:semicolon
id|ucBuff
op_assign
id|pLoggedInPort-&gt;ReportLunsPayload
suffix:semicolon
id|memset
c_func
(paren
id|Cmnd
comma
l_int|0
comma
r_sizeof
(paren
id|Scsi_Cmnd
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|ucBuff
comma
l_int|0
comma
id|REPORT_LUNS_PL
)paren
suffix:semicolon
id|Cmnd-&gt;scsi_done
op_assign
id|ScsiReportLunsDone
suffix:semicolon
id|Cmnd-&gt;host
op_assign
id|cpqfcHBAdata-&gt;HostAdapter
suffix:semicolon
id|Cmnd-&gt;request_buffer
op_assign
id|pLoggedInPort-&gt;ReportLunsPayload
suffix:semicolon
id|Cmnd-&gt;request_bufflen
op_assign
id|REPORT_LUNS_PL
suffix:semicolon
id|Cmnd-&gt;cmnd
(braket
l_int|0
)braket
op_assign
l_int|0xA0
suffix:semicolon
id|Cmnd-&gt;cmnd
(braket
l_int|8
)braket
op_assign
id|REPORT_LUNS_PL
op_rshift
l_int|8
suffix:semicolon
id|Cmnd-&gt;cmnd
(braket
l_int|9
)braket
op_assign
(paren
id|UCHAR
)paren
id|REPORT_LUNS_PL
suffix:semicolon
id|Cmnd-&gt;cmd_len
op_assign
l_int|12
suffix:semicolon
id|Cmnd-&gt;channel
op_assign
id|pLoggedInPort-&gt;ScsiNexus.channel
suffix:semicolon
id|Cmnd-&gt;target
op_assign
id|pLoggedInPort-&gt;ScsiNexus.target
suffix:semicolon
id|ulStatus
op_assign
id|cpqfcTSBuildExchange
c_func
(paren
id|cpqfcHBAdata
comma
id|SCSI_IRE
comma
id|fchs
comma
id|Cmnd
comma
singleline_comment|// buffer for Report Lun data
op_amp
id|x_ID
)paren
suffix:semicolon
singleline_comment|// fcController-&gt;fcExchanges index, -1 if failed
r_if
c_cond
(paren
op_logical_neg
id|ulStatus
)paren
singleline_comment|// Exchange setup?
(brace
id|ulStatus
op_assign
id|cpqfcTSStartExchange
c_func
(paren
id|cpqfcHBAdata
comma
id|x_ID
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ulStatus
)paren
(brace
singleline_comment|// submitted to Tach&squot;s Outbound Que (ERQ PI incremented)
singleline_comment|// waited for completion for ELS type (Login frames issued
singleline_comment|// synchronously)
)brace
r_else
singleline_comment|// check reason for Exchange not being started - we might
singleline_comment|// want to Queue and start later, or fail with error
(brace
)brace
)brace
r_else
singleline_comment|// Xchange setup failed...
id|printk
c_func
(paren
l_string|&quot; cpqfcTSBuildExchange failed: %Xh&bslash;n&quot;
comma
id|ulStatus
)paren
suffix:semicolon
)brace
r_else
singleline_comment|// like, we just got a PRLI ACC, and now the port is gone?
(brace
id|printk
c_func
(paren
l_string|&quot; can&squot;t send ReportLuns - no login for port_id %Xh&bslash;n&quot;
comma
id|fchs-&gt;s_id
op_amp
l_int|0xFFFFFF
)paren
suffix:semicolon
)brace
id|Done
suffix:colon
)brace
DECL|function|CompleteBoardLockCmnd
r_static
r_void
id|CompleteBoardLockCmnd
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
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
id|CPQFCTS_REQ_QUEUE_LEN
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|cpqfcHBAdata-&gt;BoardLockCmnd
(braket
id|i
)braket
op_ne
l_int|NULL
)paren
(brace
id|Scsi_Cmnd
op_star
id|Cmnd
op_assign
id|cpqfcHBAdata-&gt;BoardLockCmnd
(braket
id|i
)braket
suffix:semicolon
id|cpqfcHBAdata-&gt;BoardLockCmnd
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|Cmnd-&gt;result
op_assign
(paren
id|DID_SOFT_ERROR
op_lshift
l_int|16
)paren
suffix:semicolon
singleline_comment|// ask for retry
singleline_comment|//      printk(&quot; BoardLockCmnd[%d] %p Complete, chnl/target/lun %d/%d/%d&bslash;n&quot;,
singleline_comment|//        i,Cmnd, Cmnd-&gt;channel, Cmnd-&gt;target, Cmnd-&gt;lun);
id|call_scsi_done
c_func
(paren
id|Cmnd
)paren
suffix:semicolon
)brace
)brace
)brace
singleline_comment|// runs every 1 second for FC exchange timeouts and implicit FC device logouts
DECL|function|cpqfcTSheartbeat
r_void
id|cpqfcTSheartbeat
c_func
(paren
r_int
r_int
id|ptr
)paren
(brace
id|CPQFCHBA
op_star
id|cpqfcHBAdata
op_assign
(paren
id|CPQFCHBA
op_star
)paren
id|ptr
suffix:semicolon
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
id|FC_EXCHANGES
op_star
id|Exchanges
op_assign
id|fcChip-&gt;Exchanges
suffix:semicolon
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
op_assign
op_amp
id|fcChip-&gt;fcPorts
suffix:semicolon
id|ULONG
id|i
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|DECLARE_MUTEX_LOCKED
c_func
(paren
id|BoardLock
)paren
suffix:semicolon
id|PCI_TRACE
c_func
(paren
l_int|0xA8
)paren
r_if
c_cond
(paren
id|cpqfcHBAdata-&gt;BoardLock
)paren
(brace
singleline_comment|// Worker Task Running?
r_goto
id|Skip
suffix:semicolon
)brace
singleline_comment|// STOP _que function
id|spin_lock_irqsave
c_func
(paren
id|cpqfcHBAdata-&gt;HostAdapter-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
id|PCI_TRACE
c_func
(paren
l_int|0xA8
)paren
id|cpqfcHBAdata-&gt;BoardLock
op_assign
op_amp
id|BoardLock
suffix:semicolon
singleline_comment|// stop Linux SCSI command queuing
singleline_comment|// release the IO lock (and re-enable interrupts)
id|spin_unlock_irqrestore
c_func
(paren
id|cpqfcHBAdata-&gt;HostAdapter-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
singleline_comment|// Ensure no contention from  _quecommand or Worker process 
id|CPQ_SPINLOCK_HBA
c_func
(paren
id|cpqfcHBAdata
)paren
id|PCI_TRACE
c_func
(paren
l_int|0xA8
)paren
id|disable_irq
c_func
(paren
id|cpqfcHBAdata-&gt;HostAdapter-&gt;irq
)paren
suffix:semicolon
singleline_comment|// our IRQ
singleline_comment|// Complete the &quot;bad target&quot; commands (normally only used during
singleline_comment|// initialization, since we aren&squot;t supposed to call &quot;scsi_done&quot;
singleline_comment|// inside the queuecommand() function).  (this is overly contorted,
singleline_comment|// scsi_done can be safely called from queuecommand for
singleline_comment|// this bad target case.  May want to simplify this later)
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|CPQFCTS_MAX_TARGET_ID
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cpqfcHBAdata-&gt;BadTargetCmnd
(braket
id|i
)braket
)paren
(brace
id|Scsi_Cmnd
op_star
id|Cmnd
op_assign
id|cpqfcHBAdata-&gt;BadTargetCmnd
(braket
id|i
)braket
suffix:semicolon
id|cpqfcHBAdata-&gt;BadTargetCmnd
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|Cmnd-&gt;result
op_assign
(paren
id|DID_BAD_TARGET
op_lshift
l_int|16
)paren
suffix:semicolon
id|call_scsi_done
c_func
(paren
id|Cmnd
)paren
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
singleline_comment|// logged in ports -- re-login check (ports required to verify login with
singleline_comment|// PDISC after LIP within 2 secs)
singleline_comment|// prevent contention
r_while
c_loop
(paren
id|pLoggedInPort
)paren
singleline_comment|// for all ports which are expecting
singleline_comment|// PDISC after the next LIP, check to see if
singleline_comment|// time is up!
(brace
singleline_comment|// Important: we only detect &quot;timeout&quot; condition on TRANSITION
singleline_comment|// from non-zero to zero
r_if
c_cond
(paren
id|pLoggedInPort-&gt;LOGO_timer
)paren
singleline_comment|// time-out &quot;armed&quot;?
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_decrement
id|pLoggedInPort-&gt;LOGO_timer
)paren
)paren
singleline_comment|// DEC from 1 to 0?
(brace
singleline_comment|// LOGOUT time!  Per PLDA, PDISC hasn&squot;t complete in 2 secs, so
singleline_comment|// issue LOGO request and destroy all I/O with other FC port(s).
multiline_comment|/*          &n;        printk(&quot; ~cpqfcTS heartbeat: LOGOut!~ &quot;);&n;        printk(&quot;Linux SCSI Chanl/Target %d/%d (port_id %06Xh) WWN %08X%08X&bslash;n&quot;, &n;        pLoggedInPort-&gt;ScsiNexus.channel, &n;        pLoggedInPort-&gt;ScsiNexus.target, &n;&t;pLoggedInPort-&gt;port_id,&n;          (ULONG)(pLoggedInPort-&gt;u.liWWN &amp;0xFFFFFFFF), &n;          (ULONG)(pLoggedInPort-&gt;u.liWWN&gt;&gt;32));&n;&n;*/
id|cpqfcTSImplicitLogout
c_func
(paren
id|cpqfcHBAdata
comma
id|pLoggedInPort
)paren
suffix:semicolon
)brace
singleline_comment|// else simply decremented - maybe next time...
)brace
id|pLoggedInPort
op_assign
id|pLoggedInPort-&gt;pNextPort
suffix:semicolon
)brace
singleline_comment|// ************  FC EXCHANGE TIMEOUT CHECK **************
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|TACH_MAX_XID
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|type
)paren
singleline_comment|// exchange defined?
(brace
r_if
c_cond
(paren
op_logical_neg
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|timeOut
)paren
singleline_comment|// time expired
(brace
singleline_comment|// Set Exchange timeout status
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|status
op_or_assign
id|FC2_TIMEOUT
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|TACH_SEST_LEN
)paren
singleline_comment|// Link Service Exchange
(brace
id|cpqfcTSCompleteExchange
c_func
(paren
id|cpqfcHBAdata-&gt;PciDev
comma
id|fcChip
comma
id|i
)paren
suffix:semicolon
singleline_comment|// Don&squot;t &quot;abort&quot; LinkService
)brace
r_else
singleline_comment|// SEST Exchange TO -- may post ABTS to Worker Thread Que
(brace
singleline_comment|// (Make sure we don&squot;t keep timing it out; let other functions
singleline_comment|// complete it or set the timeOut as needed)
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|timeOut
op_assign
l_int|30000
suffix:semicolon
singleline_comment|// seconds default
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|type
op_amp
(paren
id|BLS_ABTS
op_or
id|BLS_ABTS_ACC
)paren
)paren
(brace
singleline_comment|// For BLS_ABTS*, an upper level might still have
singleline_comment|// an outstanding command waiting for low-level completion.
singleline_comment|// Also, in the case of a WRITE, we MUST get confirmation
singleline_comment|// of either ABTS ACC or RJT before re-using the Exchange.
singleline_comment|// It&squot;s possible that the RAID cache algorithm can hang
singleline_comment|// if we fail to complete a WRITE to a LBA, when a READ
singleline_comment|// comes later to that same LBA.  Therefore, we must
singleline_comment|// ensure that the target verifies receipt of ABTS for
singleline_comment|// the exchange
id|printk
c_func
(paren
l_string|&quot;~TO Q&squot;d ABTS (x_ID %Xh)~ &quot;
comma
id|i
)paren
suffix:semicolon
singleline_comment|//            TriggerHBA( fcChip-&gt;Registers.ReMapMemBase);
singleline_comment|// On timeout of a ABTS exchange, check to
singleline_comment|// see if the FC device has a current valid login.
singleline_comment|// If so, restart it.
id|pLoggedInPort
op_assign
id|fcFindLoggedInPort
c_func
(paren
id|fcChip
comma
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|Cmnd
comma
singleline_comment|// find Scsi Nexus
l_int|0
comma
singleline_comment|// DON&squot;T search linked list for FC port id
l_int|NULL
comma
singleline_comment|// DON&squot;T search linked list for FC WWN
l_int|NULL
)paren
suffix:semicolon
singleline_comment|// DON&squot;T care about end of list
singleline_comment|// device exists?
r_if
c_cond
(paren
id|pLoggedInPort
)paren
singleline_comment|// device exists?
(brace
r_if
c_cond
(paren
id|pLoggedInPort-&gt;prli
)paren
singleline_comment|// logged in for FCP-SCSI?
(brace
singleline_comment|// attempt to restart the ABTS
id|printk
c_func
(paren
l_string|&quot; ~restarting ABTS~ &quot;
)paren
suffix:semicolon
id|cpqfcTSStartExchange
c_func
(paren
id|cpqfcHBAdata
comma
id|i
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
singleline_comment|// not an ABTS
(brace
singleline_comment|// We expect the WorkerThread to change the xchng type to
singleline_comment|// abort and set appropriate timeout.
id|cpqfcTSPutLinkQue
c_func
(paren
id|cpqfcHBAdata
comma
id|BLS_ABTS
comma
op_amp
id|i
)paren
suffix:semicolon
singleline_comment|// timed-out
)brace
)brace
)brace
r_else
singleline_comment|// time not expired...
(brace
singleline_comment|// decrement timeout: 1 or more seconds left
op_decrement
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|timeOut
suffix:semicolon
)brace
)brace
)brace
id|enable_irq
c_func
(paren
id|cpqfcHBAdata-&gt;HostAdapter-&gt;irq
)paren
suffix:semicolon
id|CPQ_SPINUNLOCK_HBA
c_func
(paren
id|cpqfcHBAdata
)paren
id|cpqfcHBAdata-&gt;BoardLock
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|// Linux SCSI commands may be queued
singleline_comment|// Now, complete any Cmnd we Q&squot;d up while BoardLock was held
id|CompleteBoardLockCmnd
c_func
(paren
id|cpqfcHBAdata
)paren
suffix:semicolon
singleline_comment|// restart the timer to run again (1 sec later)
id|Skip
suffix:colon
id|mod_timer
c_func
(paren
op_amp
id|cpqfcHBAdata-&gt;cpqfcTStimer
comma
id|jiffies
op_plus
id|HZ
)paren
suffix:semicolon
id|PCI_TRACEO
c_func
(paren
id|i
comma
l_int|0xA8
)paren
r_return
suffix:semicolon
)brace
singleline_comment|// put valid FC-AL physical address in spec order
DECL|variable|valid_al_pa
r_static
r_const
id|UCHAR
id|valid_al_pa
(braket
)braket
op_assign
initialization_block
suffix:semicolon
singleline_comment|// ALPA 0 (Fabric) is special case
DECL|variable|number_of_al_pa
r_const
r_int
id|number_of_al_pa
op_assign
(paren
r_sizeof
(paren
id|valid_al_pa
)paren
)paren
suffix:semicolon
singleline_comment|// this function looks up an al_pa from the table of valid al_pa&squot;s
singleline_comment|// we decrement from the last decimal loop ID, because soft al_pa
singleline_comment|// (our typical case) are assigned with highest priority (and high al_pa)
singleline_comment|// first.  See &quot;In-Depth FC-AL&quot;, R. Kembel pg. 38
singleline_comment|// INPUTS:
singleline_comment|//   al_pa - 24 bit port identifier (8 bit al_pa on private loop)
singleline_comment|// RETURN:
singleline_comment|//  Loop ID - serves are index to array of logged in ports
singleline_comment|//  -1      - invalid al_pa (not all 8 bit values are legal)
macro_line|#if (0)
DECL|function|GetLoopID
r_static
r_int
id|GetLoopID
c_func
(paren
id|ULONG
id|al_pa
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
id|number_of_al_pa
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
singleline_comment|// dec.
(brace
r_if
c_cond
(paren
id|valid_al_pa
(braket
id|i
)braket
op_eq
(paren
id|UCHAR
)paren
id|al_pa
)paren
(brace
singleline_comment|// take lowest 8 bits
r_return
id|i
suffix:semicolon
)brace
singleline_comment|// success - found valid al_pa; return decimal LoopID
)brace
r_return
op_minus
l_int|1
suffix:semicolon
singleline_comment|// failed - not found
)brace
macro_line|#endif
singleline_comment|// Search the singly (forward) linked list &quot;fcPorts&quot; looking for 
singleline_comment|// either the SCSI target (if != -1), port_id (if not NULL), 
singleline_comment|// or WWN (if not null), in that specific order.
singleline_comment|// If we find a SCSI nexus (from Cmnd arg), set the SCp.phase
singleline_comment|// field according to VSA or PDU
singleline_comment|// RETURNS:
singleline_comment|//   Ptr to logged in port struct if found
singleline_comment|//     (NULL if not found)
singleline_comment|//   pLastLoggedInPort - ptr to last struct (for adding new ones)
singleline_comment|// 
DECL|function|fcFindLoggedInPort
id|PFC_LOGGEDIN_PORT
id|fcFindLoggedInPort
c_func
(paren
id|PTACHYON
id|fcChip
comma
id|Scsi_Cmnd
op_star
id|Cmnd
comma
singleline_comment|// search linked list for Scsi Nexus (channel/target/lun)
id|ULONG
id|port_id
comma
singleline_comment|// search linked list for al_pa, or
id|UCHAR
id|wwn
(braket
l_int|8
)braket
comma
singleline_comment|// search linked list for WWN, or...
id|PFC_LOGGEDIN_PORT
op_star
id|pLastLoggedInPort
)paren
(brace
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
op_assign
op_amp
id|fcChip-&gt;fcPorts
suffix:semicolon
id|BOOLEAN
id|target_id_valid
op_assign
id|FALSE
suffix:semicolon
id|BOOLEAN
id|port_id_valid
op_assign
id|FALSE
suffix:semicolon
id|BOOLEAN
id|wwn_valid
op_assign
id|FALSE
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|Cmnd
op_ne
l_int|NULL
)paren
(brace
id|target_id_valid
op_assign
id|TRUE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|port_id
)paren
(brace
singleline_comment|// note! 24-bit NULL address is illegal
id|port_id_valid
op_assign
id|TRUE
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|wwn
)paren
singleline_comment|// non-null arg? (OK to pass NULL when not searching WWN)
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
singleline_comment|// valid WWN passed?  NULL WWN invalid
(brace
r_if
c_cond
(paren
id|wwn
(braket
id|i
)braket
op_ne
l_int|0
)paren
(brace
id|wwn_valid
op_assign
id|TRUE
suffix:semicolon
)brace
singleline_comment|// any non-zero byte makes (presumably) valid
)brace
)brace
)brace
singleline_comment|// check other options ...
singleline_comment|// In case multiple search options are given, we use a priority
singleline_comment|// scheme:
singleline_comment|// While valid pLoggedIn Ptr
singleline_comment|//   If port_id is valid
singleline_comment|//     if port_id matches, return Ptr
singleline_comment|//   If wwn is valid
singleline_comment|//     if wwn matches, return Ptr
singleline_comment|//   Next Ptr in list
singleline_comment|//
singleline_comment|// Return NULL (not found)
r_while
c_loop
(paren
id|pLoggedInPort
)paren
singleline_comment|// NULL marks end of list (1st ptr always valid)
(brace
r_if
c_cond
(paren
id|pLastLoggedInPort
)paren
(brace
singleline_comment|// caller&squot;s pointer valid?
op_star
id|pLastLoggedInPort
op_assign
id|pLoggedInPort
suffix:semicolon
)brace
singleline_comment|// end of linked list
r_if
c_cond
(paren
id|target_id_valid
)paren
(brace
singleline_comment|// check Linux Scsi Cmnd for channel/target Nexus match
singleline_comment|// (all luns are accessed through matching &quot;pLoggedInPort&quot;)
r_if
c_cond
(paren
(paren
id|pLoggedInPort-&gt;ScsiNexus.target
op_eq
id|Cmnd-&gt;target
)paren
op_logical_and
(paren
id|pLoggedInPort-&gt;ScsiNexus.channel
op_eq
id|Cmnd-&gt;channel
)paren
)paren
(brace
singleline_comment|// For &quot;passthru&quot; modes, the IOCTL caller is responsible
singleline_comment|// for setting the FCP-LUN addressing
r_if
c_cond
(paren
op_logical_neg
id|Cmnd-&gt;SCp.sent_command
)paren
singleline_comment|// NOT passthru?
(brace
singleline_comment|// set the FCP-LUN addressing type
id|Cmnd-&gt;SCp.phase
op_assign
id|pLoggedInPort-&gt;ScsiNexus.VolumeSetAddressing
suffix:semicolon
singleline_comment|// set the Device Type we got from the snooped INQUIRY string
id|Cmnd-&gt;SCp.Message
op_assign
id|pLoggedInPort-&gt;ScsiNexus.InqDeviceType
suffix:semicolon
singleline_comment|// handle LUN masking; if not &quot;default&quot; (illegal) lun value,
singleline_comment|// the use it.  These lun values are set by a successful
singleline_comment|// Report Luns command
r_if
c_cond
(paren
id|pLoggedInPort-&gt;ScsiNexus.LunMasking
op_eq
l_int|1
)paren
(brace
singleline_comment|// we KNOW all the valid LUNs... 0xFF is invalid!
id|Cmnd-&gt;SCp.have_data_in
op_assign
id|pLoggedInPort-&gt;ScsiNexus.lun
(braket
id|Cmnd-&gt;lun
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pLoggedInPort-&gt;ScsiNexus.lun
(braket
id|Cmnd-&gt;lun
)braket
op_eq
l_int|0xFF
)paren
r_return
l_int|NULL
suffix:semicolon
singleline_comment|// printk(&quot;xlating lun %d to 0x%02x&bslash;n&quot;, Cmnd-&gt;lun, 
singleline_comment|//&t;pLoggedInPort-&gt;ScsiNexus.lun[Cmnd-&gt;lun]);
)brace
r_else
id|Cmnd-&gt;SCp.have_data_in
op_assign
id|Cmnd-&gt;lun
suffix:semicolon
singleline_comment|// Linux &amp; target luns match
)brace
r_break
suffix:semicolon
singleline_comment|// found it!
)brace
)brace
r_if
c_cond
(paren
id|port_id_valid
)paren
singleline_comment|// look for alpa first
(brace
r_if
c_cond
(paren
id|pLoggedInPort-&gt;port_id
op_eq
id|port_id
)paren
(brace
r_break
suffix:semicolon
)brace
singleline_comment|// found it!
)brace
r_if
c_cond
(paren
id|wwn_valid
)paren
singleline_comment|// look for wwn second
(brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
op_amp
id|pLoggedInPort-&gt;u.ucWWN
(braket
l_int|0
)braket
comma
op_amp
id|wwn
(braket
l_int|0
)braket
comma
l_int|8
)paren
)paren
(brace
singleline_comment|// all 8 bytes of WWN match
r_break
suffix:semicolon
singleline_comment|// found it!
)brace
)brace
id|pLoggedInPort
op_assign
id|pLoggedInPort-&gt;pNextPort
suffix:semicolon
singleline_comment|// try next port
)brace
r_return
id|pLoggedInPort
suffix:semicolon
)brace
singleline_comment|// 
singleline_comment|// We need to examine the SEST table and re-validate
singleline_comment|// any open Exchanges for this LoggedInPort
singleline_comment|// To make Tachyon pay attention, Freeze FCP assists,
singleline_comment|// set VAL bits, Unfreeze FCP assists
DECL|function|RevalidateSEST
r_static
r_void
id|RevalidateSEST
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|HostAdapter
comma
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
)paren
(brace
id|CPQFCHBA
op_star
id|cpqfcHBAdata
op_assign
(paren
id|CPQFCHBA
op_star
)paren
id|HostAdapter-&gt;hostdata
suffix:semicolon
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
id|FC_EXCHANGES
op_star
id|Exchanges
op_assign
id|fcChip-&gt;Exchanges
suffix:semicolon
id|ULONG
id|x_ID
suffix:semicolon
id|BOOLEAN
id|TachFroze
op_assign
id|FALSE
suffix:semicolon
singleline_comment|// re-validate any SEST exchanges that are permitted
singleline_comment|// to survive the link down (e.g., good PDISC performed)
r_for
c_loop
(paren
id|x_ID
op_assign
l_int|0
suffix:semicolon
id|x_ID
OL
id|TACH_SEST_LEN
suffix:semicolon
id|x_ID
op_increment
)paren
(brace
singleline_comment|// If the SEST entry port_id matches the pLoggedInPort,
singleline_comment|// we need to re-validate
r_if
c_cond
(paren
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|type
op_eq
id|SCSI_IRE
)paren
op_logical_or
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|type
op_eq
id|SCSI_IWE
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|fchs.d_id
op_amp
l_int|0xFFFFFF
)paren
singleline_comment|// (24-bit port ID)
op_eq
id|pLoggedInPort-&gt;port_id
)paren
(brace
singleline_comment|//&t;printk(&quot; re-val xID %Xh &quot;, x_ID);
r_if
c_cond
(paren
op_logical_neg
id|TachFroze
)paren
(brace
singleline_comment|// freeze if not already frozen
id|TachFroze
op_or_assign
id|FreezeTach
c_func
(paren
id|cpqfcHBAdata
)paren
suffix:semicolon
)brace
id|fcChip-&gt;SEST-&gt;u
(braket
id|x_ID
)braket
dot
id|IWE.Hdr_Len
op_or_assign
l_int|0x80000000
suffix:semicolon
singleline_comment|// set VAL bit
)brace
)brace
)brace
r_if
c_cond
(paren
id|TachFroze
)paren
(brace
id|fcChip
op_member_access_from_pointer
id|UnFreezeTachyon
c_func
(paren
id|fcChip
comma
l_int|2
)paren
suffix:semicolon
singleline_comment|// both ERQ and FCP assists
)brace
)brace
singleline_comment|// Complete an Linux Cmnds that we Queued because
singleline_comment|// our FC link was down (cause immediate retry)
DECL|function|UnblockScsiDevice
r_static
r_void
id|UnblockScsiDevice
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|HostAdapter
comma
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
)paren
(brace
singleline_comment|//  Scsi_Device *sdev = HostAdapter-&gt;host_queue;
id|CPQFCHBA
op_star
id|cpqfcHBAdata
op_assign
(paren
id|CPQFCHBA
op_star
)paren
id|HostAdapter-&gt;hostdata
suffix:semicolon
id|Scsi_Cmnd
op_star
op_star
id|SCptr
op_assign
op_amp
id|cpqfcHBAdata-&gt;LinkDnCmnd
(braket
l_int|0
)braket
suffix:semicolon
id|Scsi_Cmnd
op_star
id|Cmnd
suffix:semicolon
r_int
id|indx
suffix:semicolon
singleline_comment|// if the device was previously &quot;blocked&quot;, make sure
singleline_comment|// we unblock it so Linux SCSI will resume
id|pLoggedInPort-&gt;device_blocked
op_assign
id|FALSE
suffix:semicolon
singleline_comment|// clear our flag
singleline_comment|// check the Link Down command ptr buffer;
singleline_comment|// we can complete now causing immediate retry
r_for
c_loop
(paren
id|indx
op_assign
l_int|0
suffix:semicolon
id|indx
OL
id|CPQFCTS_REQ_QUEUE_LEN
suffix:semicolon
id|indx
op_increment
comma
id|SCptr
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|SCptr
op_ne
l_int|NULL
)paren
singleline_comment|// scsi command to complete?
(brace
macro_line|#ifdef DUMMYCMND_DBG
id|printk
c_func
(paren
l_string|&quot;complete Cmnd %p in LinkDnCmnd[%d]&bslash;n&quot;
comma
op_star
id|SCptr
comma
id|indx
)paren
suffix:semicolon
macro_line|#endif
id|Cmnd
op_assign
op_star
id|SCptr
suffix:semicolon
singleline_comment|// Are there any Q&squot;d commands for this target?
r_if
c_cond
(paren
(paren
id|Cmnd-&gt;target
op_eq
id|pLoggedInPort-&gt;ScsiNexus.target
)paren
op_logical_and
(paren
id|Cmnd-&gt;channel
op_eq
id|pLoggedInPort-&gt;ScsiNexus.channel
)paren
)paren
(brace
id|Cmnd-&gt;result
op_assign
(paren
id|DID_SOFT_ERROR
op_lshift
l_int|16
)paren
suffix:semicolon
singleline_comment|// force retry
r_if
c_cond
(paren
id|Cmnd-&gt;scsi_done
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;LinkDnCmnd scsi_done ptr null, port_id %Xh&bslash;n&quot;
comma
id|pLoggedInPort-&gt;port_id
)paren
suffix:semicolon
id|Cmnd-&gt;SCp.sent_command
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|call_scsi_done
c_func
(paren
id|Cmnd
)paren
suffix:semicolon
op_star
id|SCptr
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|// free this slot for next use
)brace
)brace
)brace
)brace
singleline_comment|//#define WWN_DBG 1
DECL|function|SetLoginFields
r_static
r_void
id|SetLoginFields
c_func
(paren
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
comma
id|TachFCHDR_GCMND
op_star
id|fchs
comma
id|BOOLEAN
id|PDisc
comma
id|BOOLEAN
id|Originator
)paren
(brace
id|LOGIN_PAYLOAD
id|logi
suffix:semicolon
singleline_comment|// FC-PH Port Login
id|PRLI_REQUEST
id|prli
suffix:semicolon
singleline_comment|// copy for BIG ENDIAN switch
r_int
id|i
suffix:semicolon
macro_line|#ifdef WWN_DBG
id|ULONG
id|ulBuff
suffix:semicolon
macro_line|#endif
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|fchs-&gt;pl
(braket
l_int|0
)braket
comma
(paren
id|UCHAR
op_star
)paren
op_amp
id|logi
comma
r_sizeof
(paren
id|logi
)paren
)paren
suffix:semicolon
id|pLoggedInPort-&gt;Originator
op_assign
id|Originator
suffix:semicolon
id|pLoggedInPort-&gt;port_id
op_assign
id|fchs-&gt;s_id
op_amp
l_int|0xFFFFFF
suffix:semicolon
r_switch
c_cond
(paren
id|fchs-&gt;pl
(braket
l_int|0
)braket
op_amp
l_int|0xffff
)paren
(brace
r_case
l_int|0x00000002
suffix:colon
singleline_comment|//  PLOGI or PDISC ACCept?
r_if
c_cond
(paren
id|PDisc
)paren
(brace
singleline_comment|// PDISC accept
r_goto
id|PDISC_case
suffix:semicolon
)brace
r_case
l_int|0x00000003
suffix:colon
singleline_comment|//  ELS_PLOGI or ELS_PLOGI_ACC
singleline_comment|// Login BB_credit typically 0 for Tachyons
id|pLoggedInPort-&gt;BB_credit
op_assign
id|logi.cmn_services.bb_credit
suffix:semicolon
singleline_comment|// e.g. 128, 256, 1024, 2048 per FC-PH spec
singleline_comment|// We have to use this when setting up SEST Writes,
singleline_comment|// since that determines frame size we send.
id|pLoggedInPort-&gt;rx_data_size
op_assign
id|logi.class3.rx_data_size
suffix:semicolon
id|pLoggedInPort-&gt;plogi
op_assign
id|TRUE
suffix:semicolon
id|pLoggedInPort-&gt;pdisc
op_assign
id|FALSE
suffix:semicolon
id|pLoggedInPort-&gt;prli
op_assign
id|FALSE
suffix:semicolon
singleline_comment|// ELS_PLOGI resets
id|pLoggedInPort-&gt;flogi
op_assign
id|FALSE
suffix:semicolon
singleline_comment|// ELS_PLOGI resets
id|pLoggedInPort-&gt;logo
op_assign
id|FALSE
suffix:semicolon
singleline_comment|// ELS_PLOGI resets
id|pLoggedInPort-&gt;LOGO_counter
op_assign
l_int|0
suffix:semicolon
singleline_comment|// ELS_PLOGI resets
id|pLoggedInPort-&gt;LOGO_timer
op_assign
l_int|0
suffix:semicolon
singleline_comment|// ELS_PLOGI resets
singleline_comment|// was this PLOGI to a Fabric?
r_if
c_cond
(paren
id|pLoggedInPort-&gt;port_id
op_eq
l_int|0xFFFFFC
)paren
(brace
singleline_comment|// well know address
id|pLoggedInPort-&gt;flogi
op_assign
id|TRUE
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
singleline_comment|// copy the LOGIN port&squot;s WWN
id|pLoggedInPort-&gt;u.ucWWN
(braket
id|i
)braket
op_assign
id|logi.port_name
(braket
id|i
)braket
suffix:semicolon
)brace
macro_line|#ifdef WWN_DBG
id|ulBuff
op_assign
(paren
id|ULONG
)paren
id|pLoggedInPort-&gt;u.liWWN
suffix:semicolon
r_if
c_cond
(paren
id|pLoggedInPort-&gt;Originator
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;o&quot;
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;r&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PLOGI port_id %Xh, WWN %08X&quot;
comma
id|pLoggedInPort-&gt;port_id
comma
id|ulBuff
)paren
suffix:semicolon
id|ulBuff
op_assign
(paren
id|ULONG
)paren
(paren
id|pLoggedInPort-&gt;u.liWWN
op_rshift
l_int|32
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%08Xh fcPort %p&bslash;n&quot;
comma
id|ulBuff
comma
id|pLoggedInPort
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
l_int|0x00000005
suffix:colon
singleline_comment|//  ELS_LOGO (logout)
id|pLoggedInPort-&gt;plogi
op_assign
id|FALSE
suffix:semicolon
id|pLoggedInPort-&gt;pdisc
op_assign
id|FALSE
suffix:semicolon
id|pLoggedInPort-&gt;prli
op_assign
id|FALSE
suffix:semicolon
singleline_comment|// ELS_PLOGI resets
id|pLoggedInPort-&gt;flogi
op_assign
id|FALSE
suffix:semicolon
singleline_comment|// ELS_PLOGI resets
id|pLoggedInPort-&gt;logo
op_assign
id|TRUE
suffix:semicolon
singleline_comment|// ELS_PLOGI resets
id|pLoggedInPort-&gt;LOGO_counter
op_increment
suffix:semicolon
singleline_comment|// ELS_PLOGI resets
id|pLoggedInPort-&gt;LOGO_timer
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef WWN_DBG
id|ulBuff
op_assign
(paren
id|ULONG
)paren
id|pLoggedInPort-&gt;u.liWWN
suffix:semicolon
r_if
c_cond
(paren
id|pLoggedInPort-&gt;Originator
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;o&quot;
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;r&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;LOGO port_id %Xh, WWN %08X&quot;
comma
id|pLoggedInPort-&gt;port_id
comma
id|ulBuff
)paren
suffix:semicolon
id|ulBuff
op_assign
(paren
id|ULONG
)paren
(paren
id|pLoggedInPort-&gt;u.liWWN
op_rshift
l_int|32
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%08Xh&bslash;n&quot;
comma
id|ulBuff
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
id|PDISC_case
suffix:colon
r_case
l_int|0x00000050
suffix:colon
singleline_comment|//  ELS_PDISC or ELS_PDISC_ACC
id|pLoggedInPort-&gt;LOGO_timer
op_assign
l_int|0
suffix:semicolon
singleline_comment|// stop the time-out
id|pLoggedInPort-&gt;prli
op_assign
id|TRUE
suffix:semicolon
singleline_comment|// ready to accept FCP-SCSI I/O
macro_line|#ifdef WWN_DBG
id|ulBuff
op_assign
(paren
id|ULONG
)paren
id|pLoggedInPort-&gt;u.liWWN
suffix:semicolon
r_if
c_cond
(paren
id|pLoggedInPort-&gt;Originator
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;o&quot;
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;r&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PDISC port_id %Xh, WWN %08X&quot;
comma
id|pLoggedInPort-&gt;port_id
comma
id|ulBuff
)paren
suffix:semicolon
id|ulBuff
op_assign
(paren
id|ULONG
)paren
(paren
id|pLoggedInPort-&gt;u.liWWN
op_rshift
l_int|32
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%08Xh&bslash;n&quot;
comma
id|ulBuff
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
l_int|0x1020L
suffix:colon
singleline_comment|//  PRLI?
r_case
l_int|0x1002L
suffix:colon
singleline_comment|//  PRLI ACCept?
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|fchs-&gt;pl
(braket
l_int|0
)braket
comma
(paren
id|UCHAR
op_star
)paren
op_amp
id|prli
comma
r_sizeof
(paren
id|prli
)paren
)paren
suffix:semicolon
id|pLoggedInPort-&gt;fcp_info
op_assign
id|prli.fcp_info
suffix:semicolon
singleline_comment|// target/initiator flags
id|pLoggedInPort-&gt;prli
op_assign
id|TRUE
suffix:semicolon
singleline_comment|// PLOGI resets, PDISC doesn&squot;t
id|pLoggedInPort-&gt;pdisc
op_assign
id|TRUE
suffix:semicolon
singleline_comment|// expect to send (or receive) PDISC
singleline_comment|// next time
id|pLoggedInPort-&gt;LOGO_timer
op_assign
l_int|0
suffix:semicolon
singleline_comment|// will be set next LinkDown
macro_line|#ifdef WWN_DBG
id|ulBuff
op_assign
(paren
id|ULONG
)paren
id|pLoggedInPort-&gt;u.liWWN
suffix:semicolon
r_if
c_cond
(paren
id|pLoggedInPort-&gt;Originator
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;o&quot;
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;r&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PRLI port_id %Xh, WWN %08X&quot;
comma
id|pLoggedInPort-&gt;port_id
comma
id|ulBuff
)paren
suffix:semicolon
id|ulBuff
op_assign
(paren
id|ULONG
)paren
(paren
id|pLoggedInPort-&gt;u.liWWN
op_rshift
l_int|32
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%08Xh&bslash;n&quot;
comma
id|ulBuff
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|BuildLinkServicePayload
r_static
r_void
id|BuildLinkServicePayload
c_func
(paren
id|PTACHYON
id|fcChip
comma
id|ULONG
id|type
comma
r_void
op_star
id|payload
)paren
(brace
id|LOGIN_PAYLOAD
op_star
id|plogi
suffix:semicolon
singleline_comment|// FC-PH Port Login
id|LOGIN_PAYLOAD
id|PlogiPayload
suffix:semicolon
singleline_comment|// copy for BIG ENDIAN switch
id|PRLI_REQUEST
op_star
id|prli
suffix:semicolon
singleline_comment|// FCP-SCSI Process Login
id|PRLI_REQUEST
id|PrliPayload
suffix:semicolon
singleline_comment|// copy for BIG ENDIAN switch
id|LOGOUT_PAYLOAD
op_star
id|logo
suffix:semicolon
id|LOGOUT_PAYLOAD
id|LogoutPayload
suffix:semicolon
singleline_comment|//  PRLO_REQUEST  *prlo;
singleline_comment|//  PRLO_REQUEST  PrloPayload;
id|REJECT_MESSAGE
id|rjt
comma
op_star
id|prjt
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|PlogiPayload
comma
l_int|0
comma
r_sizeof
(paren
id|PlogiPayload
)paren
)paren
suffix:semicolon
id|plogi
op_assign
op_amp
id|PlogiPayload
suffix:semicolon
singleline_comment|// load into stack buffer,
singleline_comment|// then BIG-ENDIAN switch a copy to caller
r_switch
c_cond
(paren
id|type
)paren
singleline_comment|// payload type can be ELS_PLOGI, ELS_PRLI, ADISC, ...
(brace
r_case
id|ELS_FDISC
suffix:colon
r_case
id|ELS_FLOGI
suffix:colon
r_case
id|ELS_PLOGI_ACC
suffix:colon
singleline_comment|// FC-PH PORT Login Accept
r_case
id|ELS_PLOGI
suffix:colon
singleline_comment|// FC-PH PORT Login
r_case
id|ELS_PDISC
suffix:colon
singleline_comment|// FC-PH2 Port Discovery - same payload as ELS_PLOGI
id|plogi-&gt;login_cmd
op_assign
id|LS_PLOGI
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|ELS_PDISC
)paren
(brace
id|plogi-&gt;login_cmd
op_assign
id|LS_PDISC
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_eq
id|ELS_PLOGI_ACC
)paren
(brace
id|plogi-&gt;login_cmd
op_assign
id|LS_ACC
suffix:semicolon
)brace
id|plogi-&gt;cmn_services.bb_credit
op_assign
l_int|0x00
suffix:semicolon
id|plogi-&gt;cmn_services.lowest_ver
op_assign
id|fcChip-&gt;lowest_FCPH_ver
suffix:semicolon
id|plogi-&gt;cmn_services.highest_ver
op_assign
id|fcChip-&gt;highest_FCPH_ver
suffix:semicolon
id|plogi-&gt;cmn_services.bb_rx_size
op_assign
id|TACHLITE_TS_RX_SIZE
suffix:semicolon
id|plogi-&gt;cmn_services.common_features
op_assign
id|CONTINUOSLY_INCREASING
op_or
id|RANDOM_RELATIVE_OFFSET
suffix:semicolon
singleline_comment|// fill in with World Wide Name based Port Name - 8 UCHARs
singleline_comment|// get from Tach registers WWN hi &amp; lo
id|LoadWWN
c_func
(paren
id|fcChip
comma
id|plogi-&gt;port_name
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// fill in with World Wide Name based Node/Fabric Name - 8 UCHARs
singleline_comment|// get from Tach registers WWN hi &amp; lo
id|LoadWWN
c_func
(paren
id|fcChip
comma
id|plogi-&gt;node_name
comma
l_int|1
)paren
suffix:semicolon
singleline_comment|// For Seagate Drives.
singleline_comment|//
id|plogi-&gt;cmn_services.common_features
op_or_assign
l_int|0x800
suffix:semicolon
id|plogi-&gt;cmn_services.rel_offset
op_assign
l_int|0xFE
suffix:semicolon
id|plogi-&gt;cmn_services.concurrent_seq
op_assign
l_int|1
suffix:semicolon
id|plogi-&gt;class1.service_options
op_assign
l_int|0x00
suffix:semicolon
id|plogi-&gt;class2.service_options
op_assign
l_int|0x00
suffix:semicolon
id|plogi-&gt;class3.service_options
op_assign
id|CLASS_VALID
suffix:semicolon
id|plogi-&gt;class3.initiator_control
op_assign
l_int|0x00
suffix:semicolon
id|plogi-&gt;class3.rx_data_size
op_assign
id|MAX_RX_PAYLOAD
suffix:semicolon
id|plogi-&gt;class3.recipient_control
op_assign
id|ERROR_DISCARD
op_or
id|ONE_CATEGORY_SEQUENCE
suffix:semicolon
id|plogi-&gt;class3.concurrent_sequences
op_assign
l_int|1
suffix:semicolon
id|plogi-&gt;class3.open_sequences
op_assign
l_int|1
suffix:semicolon
id|plogi-&gt;vendor_id
(braket
l_int|0
)braket
op_assign
l_char|&squot;C&squot;
suffix:semicolon
id|plogi-&gt;vendor_id
(braket
l_int|1
)braket
op_assign
l_char|&squot;Q&squot;
suffix:semicolon
id|plogi-&gt;vendor_version
(braket
l_int|0
)braket
op_assign
l_char|&squot;C&squot;
suffix:semicolon
id|plogi-&gt;vendor_version
(braket
l_int|1
)braket
op_assign
l_char|&squot;Q&squot;
suffix:semicolon
id|plogi-&gt;vendor_version
(braket
l_int|2
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|plogi-&gt;vendor_version
(braket
l_int|3
)braket
op_assign
l_char|&squot;0&squot;
suffix:semicolon
id|plogi-&gt;vendor_version
(braket
l_int|4
)braket
op_assign
l_char|&squot;0&squot;
suffix:semicolon
id|plogi-&gt;vendor_version
(braket
l_int|5
)braket
op_assign
l_char|&squot;0&squot;
suffix:semicolon
singleline_comment|// FLOGI specific fields... (see FC-FLA, Rev 2.7, Aug 1999, sec 5.1)
r_if
c_cond
(paren
(paren
id|type
op_eq
id|ELS_FLOGI
)paren
op_logical_or
(paren
id|type
op_eq
id|ELS_FDISC
)paren
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
id|ELS_FLOGI
)paren
(brace
id|plogi-&gt;login_cmd
op_assign
id|LS_FLOGI
suffix:semicolon
)brace
r_else
id|plogi-&gt;login_cmd
op_assign
id|LS_FDISC
suffix:semicolon
id|plogi-&gt;cmn_services.lowest_ver
op_assign
l_int|0x20
suffix:semicolon
id|plogi-&gt;cmn_services.common_features
op_assign
l_int|0x0800
suffix:semicolon
id|plogi-&gt;cmn_services.rel_offset
op_assign
l_int|0
suffix:semicolon
id|plogi-&gt;cmn_services.concurrent_seq
op_assign
l_int|0
suffix:semicolon
id|plogi-&gt;class3.service_options
op_assign
l_int|0x8800
suffix:semicolon
id|plogi-&gt;class3.rx_data_size
op_assign
l_int|0
suffix:semicolon
id|plogi-&gt;class3.recipient_control
op_assign
l_int|0
suffix:semicolon
id|plogi-&gt;class3.concurrent_sequences
op_assign
l_int|0
suffix:semicolon
id|plogi-&gt;class3.open_sequences
op_assign
l_int|0
suffix:semicolon
)brace
singleline_comment|// copy back to caller&squot;s buff, w/ BIG ENDIAN swap
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|PlogiPayload
comma
id|payload
comma
r_sizeof
(paren
id|PlogiPayload
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ELS_ACC
suffix:colon
singleline_comment|// generic Extended Link Service ACCept&t;    
id|plogi-&gt;login_cmd
op_assign
id|LS_ACC
suffix:semicolon
singleline_comment|// copy back to caller&squot;s buff, w/ BIG ENDIAN swap
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|PlogiPayload
comma
id|payload
comma
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ELS_SCR
suffix:colon
singleline_comment|// Fabric State Change Registration
(brace
id|SCR_PL
id|scr
suffix:semicolon
singleline_comment|// state change registration
id|memset
c_func
(paren
op_amp
id|scr
comma
l_int|0
comma
r_sizeof
(paren
id|scr
)paren
)paren
suffix:semicolon
id|scr.command
op_assign
id|LS_SCR
suffix:semicolon
singleline_comment|// 0x62000000
singleline_comment|// see FC-FLA, Rev 2.7, Table A.22 (pg 82)
id|scr.function
op_assign
l_int|3
suffix:semicolon
singleline_comment|// 1 = Events detected by Fabric
singleline_comment|// 2 = N_Port detected registration
singleline_comment|// 3 = Full registration
singleline_comment|// copy back to caller&squot;s buff, w/ BIG ENDIAN swap
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|scr
comma
id|payload
comma
r_sizeof
(paren
id|SCR_PL
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|FCS_NSR
suffix:colon
singleline_comment|// Fabric Name Service Request
(brace
id|NSR_PL
id|nsr
suffix:semicolon
singleline_comment|// Name Server Req. payload
id|memset
c_func
(paren
op_amp
id|nsr
comma
l_int|0
comma
r_sizeof
(paren
id|NSR_PL
)paren
)paren
suffix:semicolon
singleline_comment|// see Brocade Fabric Programming Guide,
singleline_comment|// Rev 1.3, pg 4-44
id|nsr.CT_Rev
op_assign
l_int|0x01000000
suffix:semicolon
id|nsr.FCS_Type
op_assign
l_int|0xFC020000
suffix:semicolon
id|nsr.Command_code
op_assign
l_int|0x01710000
suffix:semicolon
id|nsr.FCP
op_assign
l_int|8
suffix:semicolon
singleline_comment|// copy back to caller&squot;s buff, w/ BIG ENDIAN swap
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|nsr
comma
id|payload
comma
r_sizeof
(paren
id|NSR_PL
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ELS_LOGO
suffix:colon
singleline_comment|// FC-PH PORT LogOut
id|logo
op_assign
op_amp
id|LogoutPayload
suffix:semicolon
singleline_comment|// load into stack buffer,
singleline_comment|// then BIG-ENDIAN switch a copy to caller
id|logo-&gt;cmd
op_assign
id|LS_LOGO
suffix:semicolon
singleline_comment|// load the 3 UCHARs of the node name
singleline_comment|// (if private loop, upper two UCHARs 0)
id|logo-&gt;reserved
op_assign
l_int|0
suffix:semicolon
id|logo-&gt;n_port_identifier
(braket
l_int|0
)braket
op_assign
(paren
id|UCHAR
)paren
(paren
id|fcChip-&gt;Registers.my_al_pa
)paren
suffix:semicolon
id|logo-&gt;n_port_identifier
(braket
l_int|1
)braket
op_assign
(paren
id|UCHAR
)paren
(paren
id|fcChip-&gt;Registers.my_al_pa
op_rshift
l_int|8
)paren
suffix:semicolon
id|logo-&gt;n_port_identifier
(braket
l_int|2
)braket
op_assign
(paren
id|UCHAR
)paren
(paren
id|fcChip-&gt;Registers.my_al_pa
op_rshift
l_int|16
)paren
suffix:semicolon
singleline_comment|// fill in with World Wide Name based Port Name - 8 UCHARs
singleline_comment|// get from Tach registers WWN hi &amp; lo
id|LoadWWN
c_func
(paren
id|fcChip
comma
id|logo-&gt;port_name
comma
l_int|0
)paren
suffix:semicolon
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|LogoutPayload
comma
id|payload
comma
r_sizeof
(paren
id|LogoutPayload
)paren
)paren
suffix:semicolon
singleline_comment|// 16 UCHAR struct
r_break
suffix:semicolon
r_case
id|ELS_LOGO_ACC
suffix:colon
singleline_comment|// Logout Accept (FH-PH pg 149, table 74)
id|logo
op_assign
op_amp
id|LogoutPayload
suffix:semicolon
singleline_comment|// load into stack buffer,
singleline_comment|// then BIG-ENDIAN switch a copy to caller
id|logo-&gt;cmd
op_assign
id|LS_ACC
suffix:semicolon
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|LogoutPayload
comma
id|payload
comma
l_int|4
)paren
suffix:semicolon
singleline_comment|// 4 UCHAR cmnd
r_break
suffix:semicolon
r_case
id|ELS_RJT
suffix:colon
singleline_comment|// ELS_RJT link service reject (FH-PH pg 155)
id|prjt
op_assign
(paren
id|REJECT_MESSAGE
op_star
)paren
id|payload
suffix:semicolon
singleline_comment|// pick up passed data
id|rjt.command_code
op_assign
id|ELS_RJT
suffix:semicolon
singleline_comment|// reverse fields, because of Swap that follows...
id|rjt.vendor
op_assign
id|prjt-&gt;reserved
suffix:semicolon
singleline_comment|// vendor specific
id|rjt.explain
op_assign
id|prjt-&gt;reason
suffix:semicolon
singleline_comment|//
id|rjt.reason
op_assign
id|prjt-&gt;explain
suffix:semicolon
singleline_comment|//
id|rjt.reserved
op_assign
id|prjt-&gt;vendor
suffix:semicolon
singleline_comment|//
singleline_comment|// BIG-ENDIAN switch a copy to caller
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|rjt
comma
id|payload
comma
l_int|8
)paren
suffix:semicolon
singleline_comment|// 8 UCHAR cmnd
r_break
suffix:semicolon
r_case
id|ELS_PRLI_ACC
suffix:colon
singleline_comment|// Process Login ACCept
r_case
id|ELS_PRLI
suffix:colon
singleline_comment|// Process Login
r_case
id|ELS_PRLO
suffix:colon
singleline_comment|// Process Logout
id|memset
c_func
(paren
op_amp
id|PrliPayload
comma
l_int|0
comma
r_sizeof
(paren
id|PrliPayload
)paren
)paren
suffix:semicolon
id|prli
op_assign
op_amp
id|PrliPayload
suffix:semicolon
singleline_comment|// load into stack buffer,
r_if
c_cond
(paren
id|type
op_eq
id|ELS_PRLI
)paren
(brace
id|prli-&gt;cmd
op_assign
l_int|0x20
suffix:semicolon
)brace
singleline_comment|// Login
r_else
r_if
c_cond
(paren
id|type
op_eq
id|ELS_PRLO
)paren
(brace
id|prli-&gt;cmd
op_assign
l_int|0x21
suffix:semicolon
)brace
singleline_comment|// Logout
r_else
r_if
c_cond
(paren
id|type
op_eq
id|ELS_PRLI_ACC
)paren
(brace
id|prli-&gt;cmd
op_assign
l_int|0x02
suffix:semicolon
singleline_comment|// Login ACCept
id|prli-&gt;valid
op_assign
id|REQUEST_EXECUTED
suffix:semicolon
)brace
id|prli-&gt;valid
op_or_assign
id|SCSI_FCP
op_or
id|ESTABLISH_PAIR
suffix:semicolon
id|prli-&gt;fcp_info
op_assign
id|READ_XFER_RDY
suffix:semicolon
id|prli-&gt;page_length
op_assign
l_int|0x10
suffix:semicolon
id|prli-&gt;payload_length
op_assign
l_int|20
suffix:semicolon
singleline_comment|// Can be initiator AND target
r_if
c_cond
(paren
id|fcChip-&gt;Options.initiator
)paren
(brace
id|prli-&gt;fcp_info
op_or_assign
id|INITIATOR_FUNCTION
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fcChip-&gt;Options.target
)paren
(brace
id|prli-&gt;fcp_info
op_or_assign
id|TARGET_FUNCTION
suffix:semicolon
)brace
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|PrliPayload
comma
id|payload
comma
id|prli-&gt;payload_length
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
singleline_comment|// no can do - programming error
id|printk
c_func
(paren
l_string|&quot; BuildLinkServicePayload unknown!&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
singleline_comment|// loads 8 UCHARs for PORT name or NODE name base on
singleline_comment|// controller&squot;s WWN.
DECL|function|LoadWWN
r_void
id|LoadWWN
c_func
(paren
id|PTACHYON
id|fcChip
comma
id|UCHAR
op_star
id|dest
comma
id|UCHAR
id|type
)paren
(brace
id|UCHAR
op_star
id|bPtr
comma
id|i
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
l_int|0
suffix:colon
singleline_comment|// Port_Name
id|bPtr
op_assign
(paren
id|UCHAR
op_star
)paren
op_amp
id|fcChip-&gt;Registers.wwn_hi
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dest
(braket
id|i
)braket
op_assign
op_star
id|bPtr
op_increment
suffix:semicolon
)brace
id|bPtr
op_assign
(paren
id|UCHAR
op_star
)paren
op_amp
id|fcChip-&gt;Registers.wwn_lo
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|4
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dest
(braket
id|i
)braket
op_assign
op_star
id|bPtr
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
singleline_comment|// Node/Fabric _Name
id|bPtr
op_assign
(paren
id|UCHAR
op_star
)paren
op_amp
id|fcChip-&gt;Registers.wwn_hi
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dest
(braket
id|i
)braket
op_assign
op_star
id|bPtr
op_increment
suffix:semicolon
)brace
id|bPtr
op_assign
(paren
id|UCHAR
op_star
)paren
op_amp
id|fcChip-&gt;Registers.wwn_lo
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|4
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dest
(braket
id|i
)braket
op_assign
op_star
id|bPtr
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
singleline_comment|// We check the Port Login payload for required values.  Note that
singleline_comment|// ELS_PLOGI and ELS_PDISC (Port DISCover) use the same payload.
DECL|function|verify_PLOGI
r_int
id|verify_PLOGI
c_func
(paren
id|PTACHYON
id|fcChip
comma
id|TachFCHDR_GCMND
op_star
id|fchs
comma
id|ULONG
op_star
id|reject_explain
)paren
(brace
id|LOGIN_PAYLOAD
id|login
suffix:semicolon
singleline_comment|// source, dest, len (should be mult. of 4)
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|fchs-&gt;pl
(braket
l_int|0
)braket
comma
(paren
id|UCHAR
op_star
)paren
op_amp
id|login
comma
r_sizeof
(paren
id|login
)paren
)paren
suffix:semicolon
singleline_comment|// check FC version
singleline_comment|// if other port&squot;s highest supported version
singleline_comment|// is less than our lowest, and 
singleline_comment|// if other port&squot;s lowest
r_if
c_cond
(paren
id|login.cmn_services.highest_ver
template_param
id|fcChip-&gt;highest_FCPH_ver
)paren
(brace
op_star
id|reject_explain
op_assign
id|LS_RJT_REASON
c_func
(paren
id|LOGICAL_ERROR
comma
id|OPTIONS_ERROR
)paren
suffix:semicolon
r_return
id|LOGICAL_ERROR
suffix:semicolon
)brace
singleline_comment|// Receive Data Field Size must be &gt;=128
singleline_comment|// per FC-PH
r_if
c_cond
(paren
id|login.cmn_services.bb_rx_size
OL
l_int|128
)paren
(brace
op_star
id|reject_explain
op_assign
id|LS_RJT_REASON
c_func
(paren
id|LOGICAL_ERROR
comma
id|DATA_FIELD_SIZE_ERROR
)paren
suffix:semicolon
r_return
id|LOGICAL_ERROR
suffix:semicolon
)brace
singleline_comment|// Only check Class 3 params
r_if
c_cond
(paren
id|login.class3.service_options
op_amp
id|CLASS_VALID
)paren
(brace
r_if
c_cond
(paren
id|login.class3.rx_data_size
OL
l_int|128
)paren
(brace
op_star
id|reject_explain
op_assign
id|LS_RJT_REASON
c_func
(paren
id|LOGICAL_ERROR
comma
id|INVALID_CSP
)paren
suffix:semicolon
r_return
id|LOGICAL_ERROR
suffix:semicolon
)brace
r_if
c_cond
(paren
id|login.class3.initiator_control
op_amp
id|XID_REQUIRED
)paren
(brace
op_star
id|reject_explain
op_assign
id|LS_RJT_REASON
c_func
(paren
id|LOGICAL_ERROR
comma
id|INITIATOR_CTL_ERROR
)paren
suffix:semicolon
r_return
id|LOGICAL_ERROR
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
singleline_comment|// success
)brace
DECL|function|verify_PRLI
r_int
id|verify_PRLI
c_func
(paren
id|TachFCHDR_GCMND
op_star
id|fchs
comma
id|ULONG
op_star
id|reject_explain
)paren
(brace
id|PRLI_REQUEST
id|prli
suffix:semicolon
singleline_comment|// buffer for BIG ENDIAN
singleline_comment|// source, dest, len (should be mult. of 4)
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|fchs-&gt;pl
(braket
l_int|0
)braket
comma
(paren
id|UCHAR
op_star
)paren
op_amp
id|prli
comma
r_sizeof
(paren
id|prli
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prli.fcp_info
op_eq
l_int|0
)paren
singleline_comment|// i.e., not target or initiator?
(brace
op_star
id|reject_explain
op_assign
id|LS_RJT_REASON
c_func
(paren
id|LOGICAL_ERROR
comma
id|OPTIONS_ERROR
)paren
suffix:semicolon
r_return
id|LOGICAL_ERROR
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
singleline_comment|// success
)brace
singleline_comment|// SWAP UCHARs as required by Fibre Channel (i.e. BIG ENDIAN)
singleline_comment|// INPUTS:
singleline_comment|//   source   - ptr to LITTLE ENDIAN ULONGS
singleline_comment|//   cnt      - number of UCHARs to switch (should be mult. of ULONG)
singleline_comment|// OUTPUTS:
singleline_comment|//   dest     - ptr to BIG ENDIAN copy
singleline_comment|// RETURN:
singleline_comment|//   none
singleline_comment|//
DECL|function|BigEndianSwap
r_void
id|BigEndianSwap
c_func
(paren
id|UCHAR
op_star
id|source
comma
id|UCHAR
op_star
id|dest
comma
id|USHORT
id|cnt
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
id|source
op_add_assign
l_int|3
suffix:semicolon
singleline_comment|// start at MSB of 1st ULONG
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|cnt
suffix:semicolon
id|j
op_add_assign
l_int|4
comma
id|source
op_add_assign
l_int|4
comma
id|dest
op_add_assign
l_int|4
)paren
singleline_comment|// every ULONG
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
singleline_comment|// every UCHAR in ULONG
op_star
(paren
id|dest
op_plus
id|i
)paren
op_assign
op_star
(paren
id|source
op_minus
id|i
)paren
suffix:semicolon
)brace
)brace
)brace
singleline_comment|// Build FC Exchanges............
r_static
r_void
id|buildFCPstatus
c_func
(paren
id|PTACHYON
id|fcChip
comma
id|ULONG
id|ExchangeID
)paren
suffix:semicolon
r_static
id|LONG
id|FindFreeExchange
c_func
(paren
id|PTACHYON
id|fcChip
comma
id|ULONG
id|type
)paren
suffix:semicolon
r_static
id|ULONG
id|build_SEST_sgList
c_func
(paren
r_struct
id|pci_dev
op_star
id|pcidev
comma
id|ULONG
op_star
id|SESTalPairStart
comma
id|Scsi_Cmnd
op_star
id|Cmnd
comma
id|ULONG
op_star
id|sgPairs
comma
id|PSGPAGES
op_star
id|sgPages_head
singleline_comment|// link list of TL Ext. S/G pages from O/S Pool
)paren
suffix:semicolon
r_static
r_int
id|build_FCP_payload
c_func
(paren
id|Scsi_Cmnd
op_star
id|Cmnd
comma
id|UCHAR
op_star
id|payload
comma
id|ULONG
id|type
comma
id|ULONG
id|fcp_dl
)paren
suffix:semicolon
multiline_comment|/*&n;                             IRB&n;      ERQ           __________________&n;  |          |   / | Req_A_SFS_Len    |        ____________________&n;  |----------|  /  | Req_A_SFS_Addr   |-------&gt;|  Reserved         |&n;  |   IRB    | /   | Req_A_D_ID       |        | SOF EOF TimeStamp |&n;  |-----------/    | Req_A_SEST_Index |-+      | R_CTL |   D_ID    |&n;  |   IRB    |     | Req_B...         | |      | CS_CTL|   S_ID    | &n;  |-----------&bslash;    |                  | |      | TYPE  |   F_CTL   |&n;  |   IRB    | &bslash;   |                  | |      | SEQ_ID  | SEQ_CNT |&n;  |-----------  &bslash;  |                  | +--&gt;+--| OX_ID   | RX_ID   |&n;  |          |   &bslash; |__________________|     |  |       RO          |&n;                                            |  | pl (payload/cmnd) |&n;                                            |  |        .....      |&n;                                            |  |___________________|&n;                                            |&n;                                            |&n;+-------------------------------------------+&n;|&n;|&n;|                        e.g. IWE    &n;|    SEST           __________________             for FCP_DATA&n;| |          |   / |       | Hdr_Len  |        ____________________&n;| |----------|  /  |  Hdr_Addr_Addr   |-------&gt;|  Reserved         |&n;| |   [0]    | /   |Remote_ID| RSP_Len|        | SOF EOF TimeStamp |&n;| |-----------/    |   RSP_Addr       |---+    | R_CTL |   D_ID    |&n;+-&gt;   [1]    |     |       | Buff_Off |   |    | CS_CTL|   S_ID    | &n;  |-----------&bslash;    |BuffIndex| Link   |   |    | TYPE  |   F_CTL   |&n;  |   [2]    | &bslash;   | Rsvd  |   RX_ID  |   |    | SEQ_ID  | SEQ_CNT |&n;  |-----------  &bslash;  |    Data_Len      |   |    | OX_ID   | RX_ID   |&n;  |    ...   |   &bslash; |     Exp_RO       |   |    |       RO          |&n;  |----------|     |   Exp_Byte_Cnt   |   |    |___________________|&n;  | SEST_LEN |  +--|    Len           |   |                                             &n;  |__________|  |  |   Address        |   |                                              &n;                |  |    ...           |   |         for FCP_RSP  &n;                |  |__________________|   |    ____________________&n;                |                         +----|  Reserved         |   &n;                |                              | SOF EOF TimeStamp |&n;                |                              | R_CTL |   D_ID    |&n;                |                              | CS_CTL|   S_ID    | &n;                +--- local or extended         |     ....          |&n;                     scatter/gather lists&n;                     defining upper-layer&n;                     data (e.g. from user&squot;s App)&n;&n;&n;*/
singleline_comment|// All TachLite commands must start with a SFS (Single Frame Sequence)
singleline_comment|// command.  In the simplest case (a NOP Basic Link command),
singleline_comment|// only one frame header and ERQ entry is required.  The most complex
singleline_comment|// case is the SCSI assisted command, which requires an ERQ entry,
singleline_comment|// SEST entry, and several frame headers and data buffers all
singleline_comment|// logically linked together.
singleline_comment|// Inputs:
singleline_comment|//   cpqfcHBAdata  - controller struct
singleline_comment|//   type          - PLOGI, SCSI_IWE, etc.
singleline_comment|//   InFCHS        - Incoming Tachlite FCHS which prompted this exchange
singleline_comment|//                   (only s_id set if we are originating)
singleline_comment|//   Data          - PVOID to data struct consistent with &quot;type&quot;
singleline_comment|//   fcExchangeIndex - pointer to OX/RD ID value of built exchange
singleline_comment|// Return:
singleline_comment|//   fcExchangeIndex - OX/RD ID value if successful
singleline_comment|//   0    - success
singleline_comment|//  INVALID_ARGS    - NULL/ invalid passed args
singleline_comment|//  BAD_ALPA        - Bad source al_pa address
singleline_comment|//  LNKDWN_OSLS     - Link Down (according to this controller)
singleline_comment|//  OUTQUE_FULL     - Outbound Que full
singleline_comment|//  DRIVERQ_FULL    - controller&squot;s Exchange array full
singleline_comment|//  SEST_FULL       - SEST table full
singleline_comment|//
singleline_comment|// Remarks:
singleline_comment|// Psuedo code:
singleline_comment|// Check for NULL pointers / bad args
singleline_comment|// Build outgoing FCHS - the header/payload struct
singleline_comment|// Build IRB (for ERQ entry)
singleline_comment|// if SCSI command, build SEST entry (e.g. IWE, TRE,...)
singleline_comment|// return success
singleline_comment|//sbuildex
DECL|function|cpqfcTSBuildExchange
id|ULONG
id|cpqfcTSBuildExchange
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|ULONG
id|type
comma
singleline_comment|// e.g. PLOGI
id|TachFCHDR_GCMND
op_star
id|InFCHS
comma
singleline_comment|// incoming FCHS
r_void
op_star
id|Data
comma
singleline_comment|// the CDB, scatter/gather, etc.  
id|LONG
op_star
id|fcExchangeIndex
)paren
singleline_comment|// points to allocated exchange, 
(brace
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
id|FC_EXCHANGES
op_star
id|Exchanges
op_assign
id|fcChip-&gt;Exchanges
suffix:semicolon
id|ULONG
id|ulStatus
op_assign
l_int|0
suffix:semicolon
singleline_comment|// assume OK
id|USHORT
id|ox_ID
comma
id|rx_ID
op_assign
l_int|0xFFFF
suffix:semicolon
id|ULONG
id|SfsLen
op_assign
l_int|0L
suffix:semicolon
id|TachLiteIRB
op_star
id|pIRB
suffix:semicolon
id|IRBflags
id|IRB_flags
suffix:semicolon
id|UCHAR
op_star
id|pIRB_flags
op_assign
(paren
id|UCHAR
op_star
)paren
op_amp
id|IRB_flags
suffix:semicolon
id|TachFCHDR_GCMND
op_star
id|CMDfchs
suffix:semicolon
id|TachFCHDR
op_star
id|dataHDR
suffix:semicolon
singleline_comment|// 32 byte HEADER ONLY FCP-DATA buffer
id|TachFCHDR_RSP
op_star
id|rspHDR
suffix:semicolon
singleline_comment|// 32 byte header + RSP payload
id|Scsi_Cmnd
op_star
id|Cmnd
op_assign
(paren
id|Scsi_Cmnd
op_star
)paren
id|Data
suffix:semicolon
singleline_comment|// Linux Scsi CDB, S/G, ...
id|TachLiteIWE
op_star
id|pIWE
suffix:semicolon
id|TachLiteIRE
op_star
id|pIRE
suffix:semicolon
id|TachLiteTWE
op_star
id|pTWE
suffix:semicolon
id|TachLiteTRE
op_star
id|pTRE
suffix:semicolon
id|ULONG
id|fcp_dl
suffix:semicolon
singleline_comment|// total byte length of DATA transferred
id|ULONG
id|fl
suffix:semicolon
singleline_comment|// frame length (FC frame size, 128, 256, 512, 1024)
id|ULONG
id|sgPairs
suffix:semicolon
singleline_comment|// number of valid scatter/gather pairs
r_int
id|FCP_SCSI_command
suffix:semicolon
id|BA_ACC_PAYLOAD
op_star
id|ba_acc
suffix:semicolon
id|BA_RJT_PAYLOAD
op_star
id|ba_rjt
suffix:semicolon
singleline_comment|// check passed ARGS
r_if
c_cond
(paren
op_logical_neg
id|fcChip-&gt;ERQ
)paren
(brace
singleline_comment|// NULL ptr means uninitialized Tachlite chip
r_return
id|INVALID_ARGS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|type
op_eq
id|SCSI_IRE
op_logical_or
id|type
op_eq
id|SCSI_TRE
op_logical_or
id|type
op_eq
id|SCSI_IWE
op_logical_or
id|type
op_eq
id|SCSI_TWE
)paren
(brace
id|FCP_SCSI_command
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|FCP_SCSI_command
op_assign
l_int|0
suffix:semicolon
singleline_comment|// for commands that pass payload data (e.g. SCSI write)
singleline_comment|// examine command struct - verify that the
singleline_comment|// length of s/g buffers is adequate for total payload
singleline_comment|// length (end of list is NULL address)
r_if
c_cond
(paren
id|FCP_SCSI_command
)paren
(brace
r_if
c_cond
(paren
id|Data
)paren
singleline_comment|// must have data descriptor (S/G list -- at least
singleline_comment|// one address with at least 1 byte of data)
(brace
singleline_comment|// something to do (later)?
)brace
r_else
r_return
id|INVALID_ARGS
suffix:semicolon
singleline_comment|// invalid DATA ptr
)brace
singleline_comment|// we can build an Exchange for later Queuing (on the TL chip)
singleline_comment|// if an empty slot is available in the DevExt for this controller
singleline_comment|// look for available Exchange slot...
r_if
c_cond
(paren
id|type
op_ne
id|FCP_RESPONSE
op_logical_and
id|type
op_ne
id|BLS_ABTS
op_logical_and
id|type
op_ne
id|BLS_ABTS_ACC
)paren
(brace
singleline_comment|// already have Exchange slot!
op_star
id|fcExchangeIndex
op_assign
id|FindFreeExchange
c_func
(paren
id|fcChip
comma
id|type
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|fcExchangeIndex
op_ne
op_minus
l_int|1
)paren
singleline_comment|// Exchange is available?
(brace
singleline_comment|// assign tmp ptr (shorthand)
id|CMDfchs
op_assign
op_amp
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|fchs
suffix:semicolon
r_if
c_cond
(paren
id|Cmnd
op_ne
l_int|NULL
)paren
singleline_comment|// (necessary for ABTS cases)
(brace
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|Cmnd
op_assign
id|Cmnd
suffix:semicolon
singleline_comment|// Linux Scsi
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|pLoggedInPort
op_assign
id|fcFindLoggedInPort
c_func
(paren
id|fcChip
comma
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|Cmnd
comma
singleline_comment|// find Scsi Nexus
l_int|0
comma
singleline_comment|// DON&squot;T search linked list for FC port id
l_int|NULL
comma
singleline_comment|// DON&squot;T search linked list for FC WWN
l_int|NULL
)paren
suffix:semicolon
singleline_comment|// DON&squot;T care about end of list
)brace
singleline_comment|// Build the command frame header (&amp; data) according
singleline_comment|// to command type
singleline_comment|// fields common for all SFS frame types
id|CMDfchs-&gt;reserved
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// must clear
id|CMDfchs-&gt;sof_eof
op_assign
l_int|0x75000000L
suffix:semicolon
singleline_comment|// SOFi3:EOFn  no UAM; LCr=0, no TS
singleline_comment|// get the destination port_id from incoming FCHS
singleline_comment|// (initialized before calling if we&squot;re Originator)
singleline_comment|// Frame goes to port it was from - the source_id
id|CMDfchs-&gt;d_id
op_assign
id|InFCHS-&gt;s_id
op_amp
l_int|0xFFFFFF
suffix:semicolon
singleline_comment|// destination (add R_CTL later)
id|CMDfchs-&gt;s_id
op_assign
id|fcChip-&gt;Registers.my_al_pa
suffix:semicolon
singleline_comment|// CS_CTL = 0
singleline_comment|// now enter command-specific fields
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|BLS_NOP
suffix:colon
singleline_comment|// FC defined basic link service command NO-OP
singleline_comment|// ensure unique X_IDs! (use tracking function)
op_star
id|pIRB_flags
op_assign
l_int|0
suffix:semicolon
singleline_comment|// clear IRB flags
id|IRB_flags.SFA
op_assign
l_int|1
suffix:semicolon
singleline_comment|// send SFS (not SEST index)
id|SfsLen
op_assign
op_star
id|pIRB_flags
suffix:semicolon
id|SfsLen
op_lshift_assign
l_int|24
suffix:semicolon
singleline_comment|// shift flags to MSB
id|SfsLen
op_add_assign
l_int|32L
suffix:semicolon
singleline_comment|// add len to LSB (header only - no payload)
singleline_comment|// TYPE[31-24] 00 Basic Link Service
singleline_comment|// f_ctl[23:0] exchg originator, 1st seq, xfer S.I.
id|CMDfchs-&gt;d_id
op_or_assign
l_int|0x80000000L
suffix:semicolon
singleline_comment|// R_CTL = 80 for NOP (Basic Link Ser.)
id|CMDfchs-&gt;f_ctl
op_assign
l_int|0x00310000L
suffix:semicolon
singleline_comment|// xchng originator, 1st seq,....
id|CMDfchs-&gt;seq_cnt
op_assign
l_int|0x0L
suffix:semicolon
id|CMDfchs-&gt;ox_rx_id
op_assign
l_int|0xFFFF
suffix:semicolon
singleline_comment|// RX_ID for now; OX_ID on start
id|CMDfchs-&gt;ro
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// relative offset (n/a)
id|CMDfchs-&gt;pl
(braket
l_int|0
)braket
op_assign
l_int|0xaabbccddL
suffix:semicolon
singleline_comment|// words 8-15 frame data payload (n/a)
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|timeOut
op_assign
l_int|1
suffix:semicolon
singleline_comment|// seconds
singleline_comment|// (NOP should complete ~instantly)
r_break
suffix:semicolon
r_case
id|BLS_ABTS_ACC
suffix:colon
singleline_comment|// Abort Sequence ACCept
op_star
id|pIRB_flags
op_assign
l_int|0
suffix:semicolon
singleline_comment|// clear IRB flags
id|IRB_flags.SFA
op_assign
l_int|1
suffix:semicolon
singleline_comment|// send SFS (not SEST index)
id|SfsLen
op_assign
op_star
id|pIRB_flags
suffix:semicolon
id|SfsLen
op_lshift_assign
l_int|24
suffix:semicolon
singleline_comment|// shift flags to MSB
id|SfsLen
op_add_assign
l_int|32
op_plus
l_int|12
suffix:semicolon
singleline_comment|// add len to LSB (header + 3 DWORD payload)
id|CMDfchs-&gt;d_id
op_or_assign
l_int|0x84000000L
suffix:semicolon
singleline_comment|// R_CTL = 84 for BASIC ACCept
singleline_comment|// TYPE[31-24] 00 Basic Link Service
singleline_comment|// f_ctl[23:0] exchg originator, not 1st seq, xfer S.I.
id|CMDfchs-&gt;f_ctl
op_assign
l_int|0x00910000L
suffix:semicolon
singleline_comment|// xchnge responder, last seq, xfer SI
singleline_comment|// CMDfchs-&gt;seq_id &amp; count might be set from DataHdr?
id|CMDfchs-&gt;ro
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// relative offset (n/a)
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|timeOut
op_assign
l_int|5
suffix:semicolon
singleline_comment|// seconds
singleline_comment|// (Timeout in case of weird error)
singleline_comment|// now set the ACCept payload...
id|ba_acc
op_assign
(paren
id|BA_ACC_PAYLOAD
op_star
)paren
op_amp
id|CMDfchs-&gt;pl
(braket
l_int|0
)braket
suffix:semicolon
id|memset
c_func
(paren
id|ba_acc
comma
l_int|0
comma
r_sizeof
(paren
id|BA_ACC_PAYLOAD
)paren
)paren
suffix:semicolon
singleline_comment|// Since PLDA requires (only) entire Exchange aborts, we don&squot;t need
singleline_comment|// to worry about what the last sequence was.
singleline_comment|// We expect that a &quot;target&quot; task is accepting the abort, so we
singleline_comment|// can use the OX/RX ID pair 
id|ba_acc-&gt;ox_rx_id
op_assign
id|CMDfchs-&gt;ox_rx_id
suffix:semicolon
singleline_comment|// source, dest, #bytes
id|BigEndianSwap
c_func
(paren
(paren
id|UCHAR
op_star
)paren
op_amp
id|CMDfchs-&gt;ox_rx_id
comma
(paren
id|UCHAR
op_star
)paren
op_amp
id|ba_acc-&gt;ox_rx_id
comma
l_int|4
)paren
suffix:semicolon
id|ba_acc-&gt;low_seq_cnt
op_assign
l_int|0
suffix:semicolon
id|ba_acc-&gt;high_seq_cnt
op_assign
l_int|0xFFFF
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BLS_ABTS_RJT
suffix:colon
singleline_comment|// Abort Sequence ACCept
op_star
id|pIRB_flags
op_assign
l_int|0
suffix:semicolon
singleline_comment|// clear IRB flags
id|IRB_flags.SFA
op_assign
l_int|1
suffix:semicolon
singleline_comment|// send SFS (not SEST index)
id|SfsLen
op_assign
op_star
id|pIRB_flags
suffix:semicolon
id|SfsLen
op_lshift_assign
l_int|24
suffix:semicolon
singleline_comment|// shift flags to MSB
id|SfsLen
op_add_assign
l_int|32
op_plus
l_int|12
suffix:semicolon
singleline_comment|// add len to LSB (header + 3 DWORD payload)
id|CMDfchs-&gt;d_id
op_or_assign
l_int|0x85000000L
suffix:semicolon
singleline_comment|// R_CTL = 85 for BASIC ReJecT
singleline_comment|// f_ctl[23:0] exchg originator, not 1st seq, xfer S.I.
singleline_comment|// TYPE[31-24] 00 Basic Link Service
id|CMDfchs-&gt;f_ctl
op_assign
l_int|0x00910000L
suffix:semicolon
singleline_comment|// xchnge responder, last seq, xfer SI
singleline_comment|// CMDfchs-&gt;seq_id &amp; count might be set from DataHdr?
id|CMDfchs-&gt;ro
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// relative offset (n/a)
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|timeOut
op_assign
l_int|5
suffix:semicolon
singleline_comment|// seconds
singleline_comment|// (Timeout in case of weird error)
id|CMDfchs-&gt;ox_rx_id
op_assign
id|InFCHS-&gt;ox_rx_id
suffix:semicolon
singleline_comment|// copy from sender!
singleline_comment|// now set the ReJecT payload...
id|ba_rjt
op_assign
(paren
id|BA_RJT_PAYLOAD
op_star
)paren
op_amp
id|CMDfchs-&gt;pl
(braket
l_int|0
)braket
suffix:semicolon
id|memset
c_func
(paren
id|ba_rjt
comma
l_int|0
comma
r_sizeof
(paren
id|BA_RJT_PAYLOAD
)paren
)paren
suffix:semicolon
singleline_comment|// We expect that a &quot;target&quot; task couldn&squot;t find the Exhange in the
singleline_comment|// array of active exchanges, so we use a new LinkService X_ID.
singleline_comment|// See Reject payload description in FC-PH (Rev 4.3), pg. 140
id|ba_rjt-&gt;reason_code
op_assign
l_int|0x09
suffix:semicolon
singleline_comment|// &quot;unable to perform command request&quot;
id|ba_rjt-&gt;reason_explain
op_assign
l_int|0x03
suffix:semicolon
singleline_comment|// invalid OX/RX ID pair
r_break
suffix:semicolon
r_case
id|BLS_ABTS
suffix:colon
singleline_comment|// FC defined basic link service command ABTS 
singleline_comment|// Abort Sequence
op_star
id|pIRB_flags
op_assign
l_int|0
suffix:semicolon
singleline_comment|// clear IRB flags
id|IRB_flags.SFA
op_assign
l_int|1
suffix:semicolon
singleline_comment|// send SFS (not SEST index)
id|SfsLen
op_assign
op_star
id|pIRB_flags
suffix:semicolon
id|SfsLen
op_lshift_assign
l_int|24
suffix:semicolon
singleline_comment|// shift flags to MSB
id|SfsLen
op_add_assign
l_int|32L
suffix:semicolon
singleline_comment|// add len to LSB (header only - no payload)
singleline_comment|// TYPE[31-24] 00 Basic Link Service
singleline_comment|// f_ctl[23:0] exchg originator, not 1st seq, xfer S.I.
id|CMDfchs-&gt;d_id
op_or_assign
l_int|0x81000000L
suffix:semicolon
singleline_comment|// R_CTL = 81 for ABTS
id|CMDfchs-&gt;f_ctl
op_assign
l_int|0x00110000L
suffix:semicolon
singleline_comment|// xchnge originator, last seq, xfer SI
singleline_comment|// CMDfchs-&gt;seq_id &amp; count might be set from DataHdr?
id|CMDfchs-&gt;ro
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// relative offset (n/a)
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|timeOut
op_assign
l_int|2
suffix:semicolon
singleline_comment|// seconds
singleline_comment|// (ABTS must timeout when responder is gone)
r_break
suffix:semicolon
r_case
id|FCS_NSR
suffix:colon
singleline_comment|// Fabric Name Service Request
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|reTries
op_assign
l_int|2
suffix:semicolon
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|timeOut
op_assign
l_int|2
suffix:semicolon
singleline_comment|// seconds
singleline_comment|// OX_ID, linked to Driver Transaction ID
singleline_comment|// (fix-up at Queing time)
id|CMDfchs-&gt;ox_rx_id
op_assign
l_int|0xFFFF
suffix:semicolon
singleline_comment|// RX_ID - Responder (target) to modify
singleline_comment|// OX_ID set at ERQueing time
op_star
id|pIRB_flags
op_assign
l_int|0
suffix:semicolon
singleline_comment|// clear IRB flags
id|IRB_flags.SFA
op_assign
l_int|1
suffix:semicolon
singleline_comment|// send SFS (not SEST index)
id|SfsLen
op_assign
op_star
id|pIRB_flags
suffix:semicolon
id|SfsLen
op_lshift_assign
l_int|24
suffix:semicolon
singleline_comment|// shift flags to MSB
id|SfsLen
op_add_assign
(paren
l_int|32L
op_plus
r_sizeof
(paren
id|NSR_PL
)paren
)paren
suffix:semicolon
singleline_comment|// add len (header &amp; NSR payload)
id|CMDfchs-&gt;d_id
op_or_assign
l_int|0x02000000L
suffix:semicolon
singleline_comment|// R_CTL = 02 for -
singleline_comment|// Name Service Request: Unsolicited 
singleline_comment|// TYPE[31-24] 01 Extended Link Service
singleline_comment|// f_ctl[23:0] exchg originator, 1st seq, xfer S.I.
id|CMDfchs-&gt;f_ctl
op_assign
l_int|0x20210000L
suffix:semicolon
singleline_comment|// OX_ID will be fixed-up at Tachyon enqueing time
id|CMDfchs-&gt;seq_cnt
op_assign
l_int|0
suffix:semicolon
singleline_comment|// seq ID, DF_ctl, seq cnt
id|CMDfchs-&gt;ro
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// relative offset (n/a)
id|BuildLinkServicePayload
c_func
(paren
id|fcChip
comma
id|type
comma
op_amp
id|CMDfchs-&gt;pl
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ELS_PLOGI
suffix:colon
singleline_comment|// FC-PH extended link service command Port Login
singleline_comment|// (May, 2000)
singleline_comment|// NOTE! This special case facilitates SANMark testing.  The SANMark
singleline_comment|// test script for initialization-timeout.fcal.SANMark-1.fc
singleline_comment|// &quot;eats&quot; the OPN() primitive without issuing an R_RDY, causing
singleline_comment|// Tachyon to report LST (loop state timeout), which causes a
singleline_comment|// LIP.  To avoid this, simply send out the frame (i.e. assuming a
singleline_comment|// buffer credit of 1) without waiting for R_RDY.  Many FC devices
singleline_comment|// (other than Tachyon) have been doing this for years.  We don&squot;t
singleline_comment|// ever want to do this for non-Link Service frames unless the
singleline_comment|// other device really did report non-zero login BB credit (i.e.
singleline_comment|// in the PLOGI ACCept frame).
singleline_comment|//      CMDfchs-&gt;sof_eof |= 0x00000400L;  // LCr=1
r_case
id|ELS_FDISC
suffix:colon
singleline_comment|// Fabric Discovery (Login)
r_case
id|ELS_FLOGI
suffix:colon
singleline_comment|// Fabric Login
r_case
id|ELS_SCR
suffix:colon
singleline_comment|// Fabric State Change Registration
r_case
id|ELS_LOGO
suffix:colon
singleline_comment|// FC-PH extended link service command Port Logout
r_case
id|ELS_PDISC
suffix:colon
singleline_comment|// FC-PH extended link service cmnd Port Discovery
r_case
id|ELS_PRLI
suffix:colon
singleline_comment|// FC-PH extended link service cmnd Process Login
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|reTries
op_assign
l_int|2
suffix:semicolon
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|timeOut
op_assign
l_int|2
suffix:semicolon
singleline_comment|// seconds
singleline_comment|// OX_ID, linked to Driver Transaction ID
singleline_comment|// (fix-up at Queing time)
id|CMDfchs-&gt;ox_rx_id
op_assign
l_int|0xFFFF
suffix:semicolon
singleline_comment|// RX_ID - Responder (target) to modify
singleline_comment|// OX_ID set at ERQueing time
op_star
id|pIRB_flags
op_assign
l_int|0
suffix:semicolon
singleline_comment|// clear IRB flags
id|IRB_flags.SFA
op_assign
l_int|1
suffix:semicolon
singleline_comment|// send SFS (not SEST index)
id|SfsLen
op_assign
op_star
id|pIRB_flags
suffix:semicolon
id|SfsLen
op_lshift_assign
l_int|24
suffix:semicolon
singleline_comment|// shift flags to MSB
r_if
c_cond
(paren
id|type
op_eq
id|ELS_LOGO
)paren
(brace
id|SfsLen
op_add_assign
(paren
l_int|32L
op_plus
l_int|16L
)paren
suffix:semicolon
)brace
singleline_comment|//  add len (header &amp; PLOGI payload)
r_else
r_if
c_cond
(paren
id|type
op_eq
id|ELS_PRLI
)paren
(brace
id|SfsLen
op_add_assign
(paren
l_int|32L
op_plus
l_int|20L
)paren
suffix:semicolon
)brace
singleline_comment|//  add len (header &amp; PRLI payload)
r_else
r_if
c_cond
(paren
id|type
op_eq
id|ELS_SCR
)paren
(brace
id|SfsLen
op_add_assign
(paren
l_int|32L
op_plus
r_sizeof
(paren
id|SCR_PL
)paren
)paren
suffix:semicolon
)brace
singleline_comment|//  add len (header &amp; SCR payload)
r_else
id|SfsLen
op_add_assign
(paren
l_int|32L
op_plus
l_int|116L
)paren
suffix:semicolon
singleline_comment|//  add len (header &amp; PLOGI payload)
id|CMDfchs-&gt;d_id
op_or_assign
l_int|0x22000000L
suffix:semicolon
singleline_comment|// R_CTL = 22 for -
singleline_comment|// Extended Link_Data: Unsolicited Control
singleline_comment|// TYPE[31-24] 01 Extended Link Service
singleline_comment|// f_ctl[23:0] exchg originator, 1st seq, xfer S.I.
id|CMDfchs-&gt;f_ctl
op_assign
l_int|0x01210000L
suffix:semicolon
singleline_comment|// OX_ID will be fixed-up at Tachyon enqueing time
id|CMDfchs-&gt;seq_cnt
op_assign
l_int|0
suffix:semicolon
singleline_comment|// seq ID, DF_ctl, seq cnt
id|CMDfchs-&gt;ro
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// relative offset (n/a)
id|BuildLinkServicePayload
c_func
(paren
id|fcChip
comma
id|type
comma
op_amp
id|CMDfchs-&gt;pl
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ELS_LOGO_ACC
suffix:colon
singleline_comment|// FC-PH extended link service logout accept
r_case
id|ELS_RJT
suffix:colon
singleline_comment|// extended link service reject (add reason)
r_case
id|ELS_ACC
suffix:colon
singleline_comment|// ext. link service generic accept
r_case
id|ELS_PLOGI_ACC
suffix:colon
singleline_comment|// ext. link service login accept (PLOGI or PDISC)
r_case
id|ELS_PRLI_ACC
suffix:colon
singleline_comment|// ext. link service process login accept
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|timeOut
op_assign
l_int|1
suffix:semicolon
singleline_comment|// assume done
singleline_comment|// ensure unique X_IDs! (use tracking function)
singleline_comment|// OX_ID from initiator cmd
id|ox_ID
op_assign
(paren
id|USHORT
)paren
(paren
id|InFCHS-&gt;ox_rx_id
op_rshift
l_int|16
)paren
suffix:semicolon
id|rx_ID
op_assign
l_int|0xFFFF
suffix:semicolon
singleline_comment|// RX_ID, linked to Driver Exchange ID
op_star
id|pIRB_flags
op_assign
l_int|0
suffix:semicolon
singleline_comment|// clear IRB flags
id|IRB_flags.SFA
op_assign
l_int|1
suffix:semicolon
singleline_comment|// send SFS (not SEST index)
id|SfsLen
op_assign
op_star
id|pIRB_flags
suffix:semicolon
id|SfsLen
op_lshift_assign
l_int|24
suffix:semicolon
singleline_comment|// shift flags to MSB
r_if
c_cond
(paren
id|type
op_eq
id|ELS_RJT
)paren
(brace
id|SfsLen
op_add_assign
(paren
l_int|32L
op_plus
l_int|8L
)paren
suffix:semicolon
singleline_comment|//  add len (header + payload)
singleline_comment|// ELS_RJT reason codes (utilize unused &quot;reserved&quot; field)
id|CMDfchs-&gt;pl
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
id|CMDfchs-&gt;pl
(braket
l_int|1
)braket
op_assign
id|InFCHS-&gt;reserved
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|type
op_eq
id|ELS_LOGO_ACC
)paren
op_logical_or
(paren
id|type
op_eq
id|ELS_ACC
)paren
)paren
(brace
id|SfsLen
op_add_assign
(paren
l_int|32L
op_plus
l_int|4L
)paren
suffix:semicolon
)brace
singleline_comment|//  add len (header + payload)
r_else
r_if
c_cond
(paren
id|type
op_eq
id|ELS_PLOGI_ACC
)paren
(brace
id|SfsLen
op_add_assign
(paren
l_int|32L
op_plus
l_int|116L
)paren
suffix:semicolon
)brace
singleline_comment|//  add len (header + payload)
r_else
r_if
c_cond
(paren
id|type
op_eq
id|ELS_PRLI_ACC
)paren
(brace
id|SfsLen
op_add_assign
(paren
l_int|32L
op_plus
l_int|20L
)paren
suffix:semicolon
)brace
singleline_comment|//  add len (header + payload)
id|CMDfchs-&gt;d_id
op_or_assign
l_int|0x23000000L
suffix:semicolon
singleline_comment|// R_CTL = 23 for -
singleline_comment|// Extended Link_Data: Control Reply
singleline_comment|// TYPE[31-24] 01 Extended Link Service
singleline_comment|// f_ctl[23:0] exchg responder, last seq, e_s, tsi
id|CMDfchs-&gt;f_ctl
op_assign
l_int|0x01990000L
suffix:semicolon
id|CMDfchs-&gt;seq_cnt
op_assign
l_int|0x0L
suffix:semicolon
id|CMDfchs-&gt;ox_rx_id
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// clear
id|CMDfchs-&gt;ox_rx_id
op_assign
id|ox_ID
suffix:semicolon
singleline_comment|// load upper 16 bits
id|CMDfchs-&gt;ox_rx_id
op_lshift_assign
l_int|16
suffix:semicolon
singleline_comment|// shift them
id|CMDfchs-&gt;ro
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// relative offset (n/a)
id|BuildLinkServicePayload
c_func
(paren
id|fcChip
comma
id|type
comma
op_amp
id|CMDfchs-&gt;pl
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
singleline_comment|// Fibre Channel SCSI &squot;originator&squot; sequences...
singleline_comment|// (originator means &squot;initiator&squot; in FCP-SCSI)
r_case
id|SCSI_IWE
suffix:colon
singleline_comment|// TachLite Initiator Write Entry
(brace
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
op_assign
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|pLoggedInPort
suffix:semicolon
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|reTries
op_assign
l_int|1
suffix:semicolon
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|timeOut
op_assign
l_int|7
suffix:semicolon
singleline_comment|// FC2 timeout
singleline_comment|// first, build FCP_CMND
singleline_comment|// unique X_ID fix-ups in StartExchange 
op_star
id|pIRB_flags
op_assign
l_int|0
suffix:semicolon
singleline_comment|// clear IRB flags
id|IRB_flags.SFA
op_assign
l_int|1
suffix:semicolon
singleline_comment|// send SFS FCP-CMND (not SEST index)
singleline_comment|// NOTE: unlike FC LinkService login frames, normal
singleline_comment|// SCSI commands are sent without outgoing verification
id|IRB_flags.DCM
op_assign
l_int|1
suffix:semicolon
singleline_comment|// Disable completion message for Cmnd frame
id|SfsLen
op_assign
op_star
id|pIRB_flags
suffix:semicolon
id|SfsLen
op_lshift_assign
l_int|24
suffix:semicolon
singleline_comment|// shift flags to MSB
id|SfsLen
op_add_assign
l_int|64L
suffix:semicolon
singleline_comment|// add len to LSB (header &amp; CMND payload)
id|CMDfchs-&gt;d_id
op_or_assign
(paren
l_int|0x06000000L
)paren
suffix:semicolon
singleline_comment|// R_CTL = 6 for command
singleline_comment|// TYPE[31-24] 8 for FCP SCSI
singleline_comment|// f_ctl[23:0] exchg originator, 1st seq, xfer S.I.
singleline_comment|//             valid RO
id|CMDfchs-&gt;f_ctl
op_assign
l_int|0x08210008L
suffix:semicolon
id|CMDfchs-&gt;seq_cnt
op_assign
l_int|0x0L
suffix:semicolon
id|CMDfchs-&gt;ox_rx_id
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// clear for now (-or- in later)
id|CMDfchs-&gt;ro
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// relative offset (n/a)
singleline_comment|// now, fill out FCP-DATA header
singleline_comment|// (use buffer inside SEST object)
id|dataHDR
op_assign
op_amp
id|fcChip-&gt;SEST-&gt;DataHDR
(braket
op_star
id|fcExchangeIndex
)braket
suffix:semicolon
id|dataHDR-&gt;reserved
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// must clear
id|dataHDR-&gt;sof_eof
op_assign
l_int|0x75002000L
suffix:semicolon
singleline_comment|// SOFi3:EOFn  no UAM; no CLS, noLCr, no TS
id|dataHDR-&gt;d_id
op_assign
(paren
id|InFCHS-&gt;s_id
op_or
l_int|0x01000000L
)paren
suffix:semicolon
singleline_comment|// R_CTL= FCP_DATA
id|dataHDR-&gt;s_id
op_assign
id|fcChip-&gt;Registers.my_al_pa
suffix:semicolon
singleline_comment|// CS_CTL = 0
singleline_comment|// TYPE[31-24] 8 for FCP SCSI
singleline_comment|// f_ctl[23:0] xfer S.I.| valid RO
id|dataHDR-&gt;f_ctl
op_assign
l_int|0x08010008L
suffix:semicolon
id|dataHDR-&gt;seq_cnt
op_assign
l_int|0x02000000L
suffix:semicolon
singleline_comment|// sequence ID: df_ctl : seqence count
id|dataHDR-&gt;ox_rx_id
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// clear; fix-up dataHDR fields later
id|dataHDR-&gt;ro
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// relative offset (n/a)
singleline_comment|// Now setup the SEST entry
id|pIWE
op_assign
op_amp
id|fcChip-&gt;SEST-&gt;u
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|IWE
suffix:semicolon
singleline_comment|// fill out the IWE:
singleline_comment|// VALid entry:Dir outbound:DCM:enable CM:enal INT: FC frame len
id|pIWE-&gt;Hdr_Len
op_assign
l_int|0x8e000020L
suffix:semicolon
singleline_comment|// data frame Len always 32 bytes
singleline_comment|// from login parameters with other port, what&squot;s the largest frame
singleline_comment|// we can send? 
r_if
c_cond
(paren
id|pLoggedInPort
op_eq
l_int|NULL
)paren
(brace
id|ulStatus
op_assign
id|INVALID_ARGS
suffix:semicolon
singleline_comment|// failed! give up
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pLoggedInPort-&gt;rx_data_size
op_ge
l_int|2048
)paren
(brace
id|fl
op_assign
l_int|0x00020000
suffix:semicolon
)brace
singleline_comment|// 2048 code (only support 1024!)
r_else
r_if
c_cond
(paren
id|pLoggedInPort-&gt;rx_data_size
op_ge
l_int|1024
)paren
(brace
id|fl
op_assign
l_int|0x00020000
suffix:semicolon
)brace
singleline_comment|// 1024 code
r_else
r_if
c_cond
(paren
id|pLoggedInPort-&gt;rx_data_size
op_ge
l_int|512
)paren
(brace
id|fl
op_assign
l_int|0x00010000
suffix:semicolon
)brace
singleline_comment|// 512 code
r_else
id|fl
op_assign
l_int|0
suffix:semicolon
singleline_comment|// 128 bytes -- should never happen
id|pIWE-&gt;Hdr_Len
op_or_assign
id|fl
suffix:semicolon
singleline_comment|// add xmit FC frame len for data phase
id|pIWE-&gt;Hdr_Addr
op_assign
id|fcChip-&gt;SEST-&gt;base
op_plus
(paren
(paren
r_int
r_int
)paren
op_amp
id|fcChip-&gt;SEST-&gt;DataHDR
(braket
op_star
id|fcExchangeIndex
)braket
op_minus
(paren
r_int
r_int
)paren
id|fcChip-&gt;SEST
)paren
suffix:semicolon
id|pIWE-&gt;RSP_Len
op_assign
r_sizeof
(paren
id|TachFCHDR_RSP
)paren
suffix:semicolon
singleline_comment|// hdr+data (recv&squot;d RSP frame)
id|pIWE-&gt;RSP_Len
op_or_assign
(paren
id|InFCHS-&gt;s_id
op_lshift
l_int|8
)paren
suffix:semicolon
singleline_comment|// MS 24 bits Remote_ID
id|memset
c_func
(paren
op_amp
id|fcChip-&gt;SEST-&gt;RspHDR
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|pl
comma
l_int|0
comma
r_sizeof
(paren
id|FCP_STATUS_RESPONSE
)paren
)paren
suffix:semicolon
singleline_comment|// clear out previous status
id|pIWE-&gt;RSP_Addr
op_assign
id|fcChip-&gt;SEST-&gt;base
op_plus
(paren
(paren
r_int
r_int
)paren
op_amp
id|fcChip-&gt;SEST-&gt;RspHDR
(braket
op_star
id|fcExchangeIndex
)braket
op_minus
(paren
r_int
r_int
)paren
id|fcChip-&gt;SEST
)paren
suffix:semicolon
singleline_comment|// Do we need local or extended gather list?
singleline_comment|// depends on size - we can handle 3 len/addr pairs
singleline_comment|// locally.
id|fcp_dl
op_assign
id|build_SEST_sgList
c_func
(paren
id|cpqfcHBAdata-&gt;PciDev
comma
op_amp
id|pIWE-&gt;GLen1
comma
id|Cmnd
comma
singleline_comment|// S/G list
op_amp
id|sgPairs
comma
singleline_comment|// return # of pairs in S/G list (from &quot;Data&quot; descriptor)
op_amp
id|fcChip-&gt;SEST-&gt;sgPages
(braket
op_star
id|fcExchangeIndex
)braket
)paren
suffix:semicolon
singleline_comment|// (for Freeing later)
r_if
c_cond
(paren
op_logical_neg
id|fcp_dl
)paren
singleline_comment|// error building S/G list?
(brace
id|ulStatus
op_assign
id|MEMPOOL_FAIL
suffix:semicolon
r_break
suffix:semicolon
singleline_comment|// give up
)brace
singleline_comment|// Now that we know total data length in
singleline_comment|// the passed S/G buffer, set FCP CMND frame
id|build_FCP_payload
c_func
(paren
id|Cmnd
comma
(paren
id|UCHAR
op_star
)paren
op_amp
id|CMDfchs-&gt;pl
(braket
l_int|0
)braket
comma
id|type
comma
id|fcp_dl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sgPairs
OG
l_int|3
)paren
(brace
singleline_comment|// need extended s/g list
id|pIWE-&gt;Buff_Off
op_assign
l_int|0x78000000L
suffix:semicolon
)brace
singleline_comment|// extended data | (no offset)
r_else
singleline_comment|// local data pointers (in SEST)
id|pIWE-&gt;Buff_Off
op_assign
l_int|0xf8000000L
suffix:semicolon
singleline_comment|// local data | (no offset)
singleline_comment|// ULONG 5
id|pIWE-&gt;Link
op_assign
l_int|0x0000ffffL
suffix:semicolon
singleline_comment|// Buff_Index | Link
id|pIWE-&gt;RX_ID
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// DWord 6: RX_ID set by target XFER_RDY
singleline_comment|// DWord 7
id|pIWE-&gt;Data_Len
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// TL enters rcv&squot;d XFER_RDY BURST_LEN
id|pIWE-&gt;Exp_RO
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// DWord 8
singleline_comment|// DWord 9
id|pIWE-&gt;Exp_Byte_Cnt
op_assign
id|fcp_dl
suffix:semicolon
singleline_comment|// sum of gather buffers
)brace
r_break
suffix:semicolon
r_case
id|SCSI_IRE
suffix:colon
singleline_comment|// TachLite Initiator Read Entry
r_if
c_cond
(paren
id|Cmnd-&gt;timeout
op_ne
l_int|0
)paren
(brace
singleline_comment|//&t;printk(&quot;Cmnd-&gt;timeout %d&bslash;n&quot;, Cmnd-&gt;timeout);
singleline_comment|// per Linux Scsi
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|timeOut
op_assign
id|Cmnd-&gt;timeout
suffix:semicolon
)brace
r_else
singleline_comment|// use our best guess, based on FC &amp; device
(brace
r_if
c_cond
(paren
id|Cmnd-&gt;SCp.Message
op_eq
l_int|1
)paren
singleline_comment|// Tape device? (from INQUIRY)&t;
(brace
singleline_comment|// turn off our timeouts (for now...)
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|timeOut
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
)brace
r_else
(brace
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|reTries
op_assign
l_int|1
suffix:semicolon
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|timeOut
op_assign
l_int|7
suffix:semicolon
singleline_comment|// per SCSI req.
)brace
)brace
singleline_comment|// first, build FCP_CMND
op_star
id|pIRB_flags
op_assign
l_int|0
suffix:semicolon
singleline_comment|// clear IRB flags
id|IRB_flags.SFA
op_assign
l_int|1
suffix:semicolon
singleline_comment|// send SFS FCP-CMND (not SEST index)
singleline_comment|// NOTE: unlike FC LinkService login frames,
singleline_comment|// normal SCSI commands are sent &quot;open loop&quot;
id|IRB_flags.DCM
op_assign
l_int|1
suffix:semicolon
singleline_comment|// Disable completion message for Cmnd frame
id|SfsLen
op_assign
op_star
id|pIRB_flags
suffix:semicolon
id|SfsLen
op_lshift_assign
l_int|24
suffix:semicolon
singleline_comment|// shift flags to MSB
id|SfsLen
op_add_assign
l_int|64L
suffix:semicolon
singleline_comment|// add len to LSB (header &amp; CMND payload)
id|CMDfchs-&gt;d_id
op_or_assign
(paren
l_int|0x06000000L
)paren
suffix:semicolon
singleline_comment|// R_CTL = 6 for command
singleline_comment|// TYPE[31-24] 8 for FCP SCSI
singleline_comment|// f_ctl[23:0] exchg originator, 1st seq, xfer S.I.
singleline_comment|//             valid RO
id|CMDfchs-&gt;f_ctl
op_assign
l_int|0x08210008L
suffix:semicolon
id|CMDfchs-&gt;seq_cnt
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// x_ID &amp; data direction bit set later
id|CMDfchs-&gt;ox_rx_id
op_assign
l_int|0xFFFF
suffix:semicolon
singleline_comment|// clear
id|CMDfchs-&gt;ro
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// relative offset (n/a)
singleline_comment|// Now setup the SEST entry
id|pIRE
op_assign
op_amp
id|fcChip-&gt;SEST-&gt;u
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|IRE
suffix:semicolon
singleline_comment|// fill out the IRE:
singleline_comment|// VALid entry:Dir outbound:enable CM:enal INT:
id|pIRE-&gt;Seq_Accum
op_assign
l_int|0xCE000000L
suffix:semicolon
singleline_comment|// VAL,DIR inbound,DCM| INI,DAT,RSP
id|pIRE-&gt;reserved
op_assign
l_int|0L
suffix:semicolon
id|pIRE-&gt;RSP_Len
op_assign
r_sizeof
(paren
id|TachFCHDR_RSP
)paren
suffix:semicolon
singleline_comment|// hdr+data (recv&squot;d RSP frame)
id|pIRE-&gt;RSP_Len
op_or_assign
(paren
id|InFCHS-&gt;s_id
op_lshift
l_int|8
)paren
suffix:semicolon
singleline_comment|// MS 24 bits Remote_ID
id|pIRE-&gt;RSP_Addr
op_assign
id|fcChip-&gt;SEST-&gt;base
op_plus
(paren
(paren
r_int
r_int
)paren
op_amp
id|fcChip-&gt;SEST-&gt;RspHDR
(braket
op_star
id|fcExchangeIndex
)braket
op_minus
(paren
r_int
r_int
)paren
id|fcChip-&gt;SEST
)paren
suffix:semicolon
singleline_comment|// Do we need local or extended gather list?
singleline_comment|// depends on size - we can handle 3 len/addr pairs
singleline_comment|// locally.
id|fcp_dl
op_assign
id|build_SEST_sgList
c_func
(paren
id|cpqfcHBAdata-&gt;PciDev
comma
op_amp
id|pIRE-&gt;SLen1
comma
id|Cmnd
comma
singleline_comment|// SCSI command Data desc. with S/G list
op_amp
id|sgPairs
comma
singleline_comment|// return # of pairs in S/G list (from &quot;Data&quot; descriptor)
op_amp
id|fcChip-&gt;SEST-&gt;sgPages
(braket
op_star
id|fcExchangeIndex
)braket
)paren
suffix:semicolon
singleline_comment|// (for Freeing later)
r_if
c_cond
(paren
op_logical_neg
id|fcp_dl
)paren
singleline_comment|// error building S/G list?
(brace
singleline_comment|// It is permissible to have a ZERO LENGTH Read command.
singleline_comment|// If there is the case, simply set fcp_dl (and Exp_Byte_Cnt)
singleline_comment|// to 0 and continue.
r_if
c_cond
(paren
id|Cmnd-&gt;request_bufflen
op_eq
l_int|0
)paren
(brace
id|fcp_dl
op_assign
l_int|0
suffix:semicolon
singleline_comment|// no FC DATA frames expected
)brace
r_else
(brace
id|ulStatus
op_assign
id|MEMPOOL_FAIL
suffix:semicolon
r_break
suffix:semicolon
singleline_comment|// give up
)brace
)brace
singleline_comment|// now that we know the S/G length, build CMND payload
id|build_FCP_payload
c_func
(paren
id|Cmnd
comma
(paren
id|UCHAR
op_star
)paren
op_amp
id|CMDfchs-&gt;pl
(braket
l_int|0
)braket
comma
id|type
comma
id|fcp_dl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sgPairs
OG
l_int|3
)paren
(brace
singleline_comment|// need extended s/g list
id|pIRE-&gt;Buff_Off
op_assign
l_int|0x00000000
suffix:semicolon
)brace
singleline_comment|// DWord 4: extended s/g list, no offset
r_else
id|pIRE-&gt;Buff_Off
op_assign
l_int|0x80000000
suffix:semicolon
singleline_comment|// local data, no offset
id|pIRE-&gt;Buff_Index
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// DWord 5: Buff_Index | Reserved
id|pIRE-&gt;Exp_RO
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// DWord 6: Expected Rel. Offset
id|pIRE-&gt;Byte_Count
op_assign
l_int|0
suffix:semicolon
singleline_comment|// DWord 7: filled in by TL on err
id|pIRE-&gt;reserved_
op_assign
l_int|0
suffix:semicolon
singleline_comment|// DWord 8: reserved
singleline_comment|// NOTE: 0 length READ is OK.
id|pIRE-&gt;Exp_Byte_Cnt
op_assign
id|fcp_dl
suffix:semicolon
singleline_comment|// DWord 9: sum of scatter buffers
r_break
suffix:semicolon
singleline_comment|// Fibre Channel SCSI &squot;responder&squot; sequences...
singleline_comment|// (originator means &squot;target&squot; in FCP-SCSI)
r_case
id|SCSI_TWE
suffix:colon
singleline_comment|// TachLite Target Write Entry
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|timeOut
op_assign
l_int|10
suffix:semicolon
singleline_comment|// per SCSI req.
singleline_comment|// first, build FCP_CMND
op_star
id|pIRB_flags
op_assign
l_int|0
suffix:semicolon
singleline_comment|// clear IRB flags
id|IRB_flags.SFA
op_assign
l_int|1
suffix:semicolon
singleline_comment|// send SFS (XFER_RDY)
id|SfsLen
op_assign
op_star
id|pIRB_flags
suffix:semicolon
id|SfsLen
op_lshift_assign
l_int|24
suffix:semicolon
singleline_comment|// shift flags to MSB
id|SfsLen
op_add_assign
(paren
l_int|32L
op_plus
l_int|12L
)paren
suffix:semicolon
singleline_comment|// add SFS len (header &amp; XFER_RDY payload)
id|CMDfchs-&gt;d_id
op_or_assign
(paren
l_int|0x05000000L
)paren
suffix:semicolon
singleline_comment|// R_CTL = 5 for XFER_RDY
singleline_comment|// TYPE[31-24] 8 for FCP SCSI
singleline_comment|// f_ctl[23:0] exchg responder, 1st seq, xfer S.I.
singleline_comment|//             valid RO
id|CMDfchs-&gt;f_ctl
op_assign
l_int|0x08810008L
suffix:semicolon
id|CMDfchs-&gt;seq_cnt
op_assign
l_int|0x01000000
suffix:semicolon
singleline_comment|// sequence ID: df_ctl: sequence count
singleline_comment|// use originator (other port&squot;s) OX_ID
id|CMDfchs-&gt;ox_rx_id
op_assign
id|InFCHS-&gt;ox_rx_id
suffix:semicolon
singleline_comment|// we want upper 16 bits
id|CMDfchs-&gt;ro
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// relative offset (n/a)
singleline_comment|// now, fill out FCP-RSP header
singleline_comment|// (use buffer inside SEST object)
id|rspHDR
op_assign
op_amp
id|fcChip-&gt;SEST-&gt;RspHDR
(braket
op_star
id|fcExchangeIndex
)braket
suffix:semicolon
id|rspHDR-&gt;reserved
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// must clear
id|rspHDR-&gt;sof_eof
op_assign
l_int|0x75000000L
suffix:semicolon
singleline_comment|// SOFi3:EOFn  no UAM; no CLS, noLCr, no TS
id|rspHDR-&gt;d_id
op_assign
(paren
id|InFCHS-&gt;s_id
op_or
l_int|0x07000000L
)paren
suffix:semicolon
singleline_comment|// R_CTL= FCP_RSP
id|rspHDR-&gt;s_id
op_assign
id|fcChip-&gt;Registers.my_al_pa
suffix:semicolon
singleline_comment|// CS_CTL = 0
singleline_comment|// TYPE[31-24] 8 for FCP SCSI
singleline_comment|// f_ctl[23:0] responder|last seq| xfer S.I.
id|rspHDR-&gt;f_ctl
op_assign
l_int|0x08910000L
suffix:semicolon
id|rspHDR-&gt;seq_cnt
op_assign
l_int|0x03000000
suffix:semicolon
singleline_comment|// sequence ID
id|rspHDR-&gt;ox_rx_id
op_assign
id|InFCHS-&gt;ox_rx_id
suffix:semicolon
singleline_comment|// gives us OX_ID
id|rspHDR-&gt;ro
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// relative offset (n/a)
singleline_comment|// Now setup the SEST entry
id|pTWE
op_assign
op_amp
id|fcChip-&gt;SEST-&gt;u
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|TWE
suffix:semicolon
singleline_comment|// fill out the TWE:
singleline_comment|// VALid entry:Dir outbound:enable CM:enal INT:
id|pTWE-&gt;Seq_Accum
op_assign
l_int|0xC4000000L
suffix:semicolon
singleline_comment|// upper word flags
id|pTWE-&gt;reserved
op_assign
l_int|0L
suffix:semicolon
id|pTWE-&gt;Remote_Node_ID
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// no more auto RSP frame! (TL/TS change)
id|pTWE-&gt;Remote_Node_ID
op_or_assign
(paren
id|InFCHS-&gt;s_id
op_lshift
l_int|8
)paren
suffix:semicolon
singleline_comment|// MS 24 bits Remote_ID
singleline_comment|// Do we need local or extended gather list?
singleline_comment|// depends on size - we can handle 3 len/addr pairs
singleline_comment|// locally.
id|fcp_dl
op_assign
id|build_SEST_sgList
c_func
(paren
id|cpqfcHBAdata-&gt;PciDev
comma
op_amp
id|pTWE-&gt;SLen1
comma
id|Cmnd
comma
singleline_comment|// S/G list
op_amp
id|sgPairs
comma
singleline_comment|// return # of pairs in S/G list (from &quot;Data&quot; descriptor)
op_amp
id|fcChip-&gt;SEST-&gt;sgPages
(braket
op_star
id|fcExchangeIndex
)braket
)paren
suffix:semicolon
singleline_comment|// (for Freeing later)
r_if
c_cond
(paren
op_logical_neg
id|fcp_dl
)paren
singleline_comment|// error building S/G list?
(brace
id|ulStatus
op_assign
id|MEMPOOL_FAIL
suffix:semicolon
r_break
suffix:semicolon
singleline_comment|// give up
)brace
singleline_comment|// now that we know the S/G length, build CMND payload
id|build_FCP_payload
c_func
(paren
id|Cmnd
comma
(paren
id|UCHAR
op_star
)paren
op_amp
id|CMDfchs-&gt;pl
(braket
l_int|0
)braket
comma
id|type
comma
id|fcp_dl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sgPairs
OG
l_int|3
)paren
(brace
singleline_comment|// need extended s/g list
id|pTWE-&gt;Buff_Off
op_assign
l_int|0x00000000
suffix:semicolon
)brace
singleline_comment|// extended s/g list, no offset
r_else
id|pTWE-&gt;Buff_Off
op_assign
l_int|0x80000000
suffix:semicolon
singleline_comment|// local data, no offset
id|pTWE-&gt;Buff_Index
op_assign
l_int|0
suffix:semicolon
singleline_comment|// Buff_Index | Link
id|pTWE-&gt;Exp_RO
op_assign
l_int|0
suffix:semicolon
id|pTWE-&gt;Byte_Count
op_assign
l_int|0
suffix:semicolon
singleline_comment|// filled in by TL on err
id|pTWE-&gt;reserved_
op_assign
l_int|0
suffix:semicolon
id|pTWE-&gt;Exp_Byte_Cnt
op_assign
id|fcp_dl
suffix:semicolon
singleline_comment|// sum of scatter buffers
r_break
suffix:semicolon
r_case
id|SCSI_TRE
suffix:colon
singleline_comment|// TachLite Target Read Entry
singleline_comment|// It doesn&squot;t make much sense for us to &quot;time-out&quot; a READ,
singleline_comment|// but we&squot;ll use it for design consistency and internal error recovery.
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|timeOut
op_assign
l_int|10
suffix:semicolon
singleline_comment|// per SCSI req.
singleline_comment|// I/O request block settings...
op_star
id|pIRB_flags
op_assign
l_int|0
suffix:semicolon
singleline_comment|// clear IRB flags
singleline_comment|// check PRLI (process login) info
singleline_comment|// to see if Initiator Requires XFER_RDY
singleline_comment|// if not, don&squot;t send one!
singleline_comment|// { PRLI check...}
id|IRB_flags.SFA
op_assign
l_int|0
suffix:semicolon
singleline_comment|// don&squot;t send XFER_RDY - start data
id|SfsLen
op_assign
op_star
id|pIRB_flags
suffix:semicolon
id|SfsLen
op_lshift_assign
l_int|24
suffix:semicolon
singleline_comment|// shift flags to MSB
id|SfsLen
op_add_assign
(paren
l_int|32L
op_plus
l_int|12L
)paren
suffix:semicolon
singleline_comment|// add SFS len (header &amp; XFER_RDY payload)
singleline_comment|// now, fill out FCP-DATA header
singleline_comment|// (use buffer inside SEST object)
id|dataHDR
op_assign
op_amp
id|fcChip-&gt;SEST-&gt;DataHDR
(braket
op_star
id|fcExchangeIndex
)braket
suffix:semicolon
id|dataHDR-&gt;reserved
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// must clear
id|dataHDR-&gt;sof_eof
op_assign
l_int|0x75000000L
suffix:semicolon
singleline_comment|// SOFi3:EOFn no UAM; no CLS,noLCr,no TS
id|dataHDR-&gt;d_id
op_assign
(paren
id|InFCHS-&gt;s_id
op_or
l_int|0x01000000L
)paren
suffix:semicolon
singleline_comment|// R_CTL= FCP_DATA
id|dataHDR-&gt;s_id
op_assign
id|fcChip-&gt;Registers.my_al_pa
suffix:semicolon
singleline_comment|// CS_CTL = 0
singleline_comment|// TYPE[31-24] 8 for FCP SCSI
singleline_comment|// f_ctl[23:0] exchg responder, not 1st seq, xfer S.I.
singleline_comment|//             valid RO
id|dataHDR-&gt;f_ctl
op_assign
l_int|0x08810008L
suffix:semicolon
id|dataHDR-&gt;seq_cnt
op_assign
l_int|0x01000000
suffix:semicolon
singleline_comment|// sequence ID (no XRDY)
id|dataHDR-&gt;ox_rx_id
op_assign
id|InFCHS-&gt;ox_rx_id
op_amp
l_int|0xFFFF0000
suffix:semicolon
singleline_comment|// we want upper 16 bits
id|dataHDR-&gt;ro
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// relative offset (n/a)
singleline_comment|// now, fill out FCP-RSP header
singleline_comment|// (use buffer inside SEST object)
id|rspHDR
op_assign
op_amp
id|fcChip-&gt;SEST-&gt;RspHDR
(braket
op_star
id|fcExchangeIndex
)braket
suffix:semicolon
id|rspHDR-&gt;reserved
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// must clear
id|rspHDR-&gt;sof_eof
op_assign
l_int|0x75000000L
suffix:semicolon
singleline_comment|// SOFi3:EOFn  no UAM; no CLS, noLCr, no TS
id|rspHDR-&gt;d_id
op_assign
(paren
id|InFCHS-&gt;s_id
op_or
l_int|0x07000000L
)paren
suffix:semicolon
singleline_comment|// R_CTL= FCP_RSP
id|rspHDR-&gt;s_id
op_assign
id|fcChip-&gt;Registers.my_al_pa
suffix:semicolon
singleline_comment|// CS_CTL = 0
singleline_comment|// TYPE[31-24] 8 for FCP SCSI
singleline_comment|// f_ctl[23:0] responder|last seq| xfer S.I.
id|rspHDR-&gt;f_ctl
op_assign
l_int|0x08910000L
suffix:semicolon
id|rspHDR-&gt;seq_cnt
op_assign
l_int|0x02000000
suffix:semicolon
singleline_comment|// sequence ID: df_ctl: sequence count
id|rspHDR-&gt;ro
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// relative offset (n/a)
singleline_comment|// Now setup the SEST entry
id|pTRE
op_assign
op_amp
id|fcChip-&gt;SEST-&gt;u
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|TRE
suffix:semicolon
singleline_comment|// VALid entry:Dir outbound:enable CM:enal INT:
id|pTRE-&gt;Hdr_Len
op_assign
l_int|0x86010020L
suffix:semicolon
singleline_comment|// data frame Len always 32 bytes
id|pTRE-&gt;Hdr_Addr
op_assign
singleline_comment|// bus address of dataHDR;
id|fcChip-&gt;SEST-&gt;base
op_plus
(paren
(paren
r_int
r_int
)paren
op_amp
id|fcChip-&gt;SEST-&gt;DataHDR
(braket
op_star
id|fcExchangeIndex
)braket
op_minus
(paren
r_int
r_int
)paren
id|fcChip-&gt;SEST
)paren
suffix:semicolon
id|pTRE-&gt;RSP_Len
op_assign
l_int|64L
suffix:semicolon
singleline_comment|// hdr+data (TL assisted RSP frame)
id|pTRE-&gt;RSP_Len
op_or_assign
(paren
id|InFCHS-&gt;s_id
op_lshift
l_int|8
)paren
suffix:semicolon
singleline_comment|// MS 24 bits Remote_ID
id|pTRE-&gt;RSP_Addr
op_assign
singleline_comment|// bus address of rspHDR
id|fcChip-&gt;SEST-&gt;base
op_plus
(paren
(paren
r_int
r_int
)paren
op_amp
id|fcChip-&gt;SEST-&gt;RspHDR
(braket
op_star
id|fcExchangeIndex
)braket
op_minus
(paren
r_int
r_int
)paren
id|fcChip-&gt;SEST
)paren
suffix:semicolon
singleline_comment|// Do we need local or extended gather list?
singleline_comment|// depends on size - we can handle 3 len/addr pairs
singleline_comment|// locally.
id|fcp_dl
op_assign
id|build_SEST_sgList
c_func
(paren
id|cpqfcHBAdata-&gt;PciDev
comma
op_amp
id|pTRE-&gt;GLen1
comma
id|Cmnd
comma
singleline_comment|// S/G list
op_amp
id|sgPairs
comma
singleline_comment|// return # of pairs in S/G list (from &quot;Data&quot; descriptor)
op_amp
id|fcChip-&gt;SEST-&gt;sgPages
(braket
op_star
id|fcExchangeIndex
)braket
)paren
suffix:semicolon
singleline_comment|// (for Freeing later)
r_if
c_cond
(paren
op_logical_neg
id|fcp_dl
)paren
singleline_comment|// error building S/G list?
(brace
id|ulStatus
op_assign
id|MEMPOOL_FAIL
suffix:semicolon
r_break
suffix:semicolon
singleline_comment|// give up
)brace
singleline_comment|// no payload or command to build -- READ doesn&squot;t need XRDY
r_if
c_cond
(paren
id|sgPairs
OG
l_int|3
)paren
(brace
singleline_comment|// need extended s/g list
id|pTRE-&gt;Buff_Off
op_assign
l_int|0x78000000L
suffix:semicolon
)brace
singleline_comment|// extended data | (no offset)
r_else
singleline_comment|// local data pointers (in SEST)
id|pTRE-&gt;Buff_Off
op_assign
l_int|0xf8000000L
suffix:semicolon
singleline_comment|// local data | (no offset)
singleline_comment|// ULONG 5
id|pTRE-&gt;Buff_Index
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// Buff_Index | reserved
id|pTRE-&gt;reserved
op_assign
l_int|0x0L
suffix:semicolon
singleline_comment|// DWord 6
singleline_comment|// DWord 7: NOTE: zero length will
singleline_comment|// hang TachLite!
id|pTRE-&gt;Data_Len
op_assign
id|fcp_dl
suffix:semicolon
singleline_comment|// e.g. sum of scatter buffers
id|pTRE-&gt;reserved_
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// DWord 8
id|pTRE-&gt;reserved__
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// DWord 9
r_break
suffix:semicolon
r_case
id|FCP_RESPONSE
suffix:colon
singleline_comment|// Target response frame: this sequence uses an OX/RX ID
singleline_comment|// pair from a completed SEST exchange.  We built most
singleline_comment|// of the response frame when we created the TWE/TRE.
op_star
id|pIRB_flags
op_assign
l_int|0
suffix:semicolon
singleline_comment|// clear IRB flags
id|IRB_flags.SFA
op_assign
l_int|1
suffix:semicolon
singleline_comment|// send SFS (RSP)
id|SfsLen
op_assign
op_star
id|pIRB_flags
suffix:semicolon
id|SfsLen
op_lshift_assign
l_int|24
suffix:semicolon
singleline_comment|// shift flags to MSB
id|SfsLen
op_add_assign
r_sizeof
(paren
id|TachFCHDR_RSP
)paren
suffix:semicolon
singleline_comment|// add SFS len (header &amp; RSP payload)
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|type
op_assign
id|FCP_RESPONSE
suffix:semicolon
singleline_comment|// change Exchange type to &quot;response&quot; phase
singleline_comment|// take advantage of prior knowledge of OX/RX_ID pair from
singleline_comment|// previous XFER outbound frame (still in fchs of exchange)
id|fcChip-&gt;SEST-&gt;RspHDR
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|ox_rx_id
op_assign
id|CMDfchs-&gt;ox_rx_id
suffix:semicolon
singleline_comment|// Check the status of the DATA phase of the exchange so we can report
singleline_comment|// status to the initiator
id|buildFCPstatus
c_func
(paren
id|fcChip
comma
op_star
id|fcExchangeIndex
)paren
suffix:semicolon
singleline_comment|// set RSP payload fields
id|memcpy
c_func
(paren
id|CMDfchs
comma
singleline_comment|// re-use same XFER fchs for Response frame
op_amp
id|fcChip-&gt;SEST-&gt;RspHDR
(braket
op_star
id|fcExchangeIndex
)braket
comma
r_sizeof
(paren
id|TachFCHDR_RSP
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;cpqfcTS: don&squot;t know how to build FC type: %Xh(%d)&bslash;n&quot;
comma
id|type
comma
id|type
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ulStatus
)paren
singleline_comment|// no errors above?
(brace
singleline_comment|// FCHS is built; now build IRB
singleline_comment|// link the just built FCHS (the &quot;command&quot;) to the IRB entry 
singleline_comment|// for this Exchange.
id|pIRB
op_assign
op_amp
id|Exchanges-&gt;fcExchange
(braket
op_star
id|fcExchangeIndex
)braket
dot
id|IRB
suffix:semicolon
singleline_comment|// len &amp; flags according to command type above
id|pIRB-&gt;Req_A_SFS_Len
op_assign
id|SfsLen
suffix:semicolon
singleline_comment|// includes IRB flags &amp; len
id|pIRB-&gt;Req_A_SFS_Addr
op_assign
singleline_comment|// TL needs physical addr of frame to send
id|fcChip-&gt;exch_dma_handle
op_plus
(paren
r_int
r_int
)paren
id|CMDfchs
op_minus
(paren
r_int
r_int
)paren
id|Exchanges
suffix:semicolon
id|pIRB-&gt;Req_A_SFS_D_ID
op_assign
id|CMDfchs-&gt;d_id
op_lshift
l_int|8
suffix:semicolon
singleline_comment|// Dest_ID must be consistent!
singleline_comment|// Exchange is complete except for &quot;fix-up&quot; fields to be set
singleline_comment|// at Tachyon Queuing time:
singleline_comment|//    IRB-&gt;Req_A_Trans_ID (OX_ID/ RX_ID):  
singleline_comment|//        for SEST entry, lower bits correspond to actual FC Exchange ID
singleline_comment|//    fchs-&gt;OX_ID or RX_ID
)brace
r_else
(brace
macro_line|#ifdef DBG     
id|printk
c_func
(paren
l_string|&quot;FC Error: SEST build Pool Allocation failed&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
singleline_comment|// return resources...
id|cpqfcTSCompleteExchange
c_func
(paren
id|cpqfcHBAdata-&gt;PciDev
comma
id|fcChip
comma
op_star
id|fcExchangeIndex
)paren
suffix:semicolon
singleline_comment|// SEST build failed
)brace
)brace
r_else
singleline_comment|// no Exchanges available
(brace
id|ulStatus
op_assign
id|SEST_FULL
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;FC Error: no fcExchanges available&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|ulStatus
suffix:semicolon
)brace
singleline_comment|// set RSP payload fields
DECL|function|buildFCPstatus
r_static
r_void
id|buildFCPstatus
c_func
(paren
id|PTACHYON
id|fcChip
comma
id|ULONG
id|ExchangeID
)paren
(brace
id|FC_EXCHANGES
op_star
id|Exchanges
op_assign
id|fcChip-&gt;Exchanges
suffix:semicolon
id|FC_EXCHANGE
op_star
id|pExchange
op_assign
op_amp
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
suffix:semicolon
singleline_comment|// shorthand
id|PFCP_STATUS_RESPONSE
id|pFcpStatus
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|fcChip-&gt;SEST-&gt;RspHDR
(braket
id|ExchangeID
)braket
dot
id|pl
comma
l_int|0
comma
r_sizeof
(paren
id|FCP_STATUS_RESPONSE
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pExchange-&gt;status
)paren
singleline_comment|// something wrong?
(brace
id|pFcpStatus
op_assign
(paren
id|PFCP_STATUS_RESPONSE
)paren
singleline_comment|// cast RSP buffer for this xchng
op_amp
id|fcChip-&gt;SEST-&gt;RspHDR
(braket
id|ExchangeID
)braket
dot
id|pl
suffix:semicolon
r_if
c_cond
(paren
id|pExchange-&gt;status
op_amp
id|COUNT_ERROR
)paren
(brace
singleline_comment|// set FCP response len valid (so we can report count error)
id|pFcpStatus-&gt;fcp_status
op_or_assign
id|FCP_RSP_LEN_VALID
suffix:semicolon
id|pFcpStatus-&gt;fcp_rsp_len
op_assign
l_int|0x04000000
suffix:semicolon
singleline_comment|// 4 byte len (BIG Endian)
id|pFcpStatus-&gt;fcp_rsp_info
op_assign
id|FCP_DATA_LEN_NOT_BURST_LEN
suffix:semicolon
singleline_comment|// RSP_CODE
)brace
)brace
)brace
r_static
id|dma_addr_t
DECL|function|cpqfc_pci_map_sg_page
id|cpqfc_pci_map_sg_page
c_func
(paren
r_struct
id|pci_dev
op_star
id|pcidev
comma
id|ULONG
op_star
id|hw_paddr
comma
singleline_comment|// where to put phys addr for HW use
r_void
op_star
id|sgp_vaddr
comma
singleline_comment|// the virtual address of the sg page 
id|dma_addr_t
op_star
id|umap_paddr
comma
singleline_comment|// where to put phys addr for unmap
r_int
r_int
op_star
id|maplen
comma
singleline_comment|// where to store sg entry length
r_int
id|PairCount
)paren
singleline_comment|// number of sg pairs used in the page.&t;
(brace
r_int
r_int
id|aligned_addr
op_assign
(paren
r_int
r_int
)paren
id|sgp_vaddr
suffix:semicolon
op_star
id|maplen
op_assign
id|PairCount
op_star
l_int|8
suffix:semicolon
id|aligned_addr
op_add_assign
id|TL_EXT_SG_PAGE_BYTELEN
suffix:semicolon
id|aligned_addr
op_and_assign
op_complement
(paren
id|TL_EXT_SG_PAGE_BYTELEN
op_minus
l_int|1
)paren
suffix:semicolon
op_star
id|umap_paddr
op_assign
id|pci_map_single
c_func
(paren
id|pcidev
comma
(paren
r_void
op_star
)paren
id|aligned_addr
comma
op_star
id|maplen
comma
id|PCI_DMA_TODEVICE
)paren
suffix:semicolon
op_star
id|hw_paddr
op_assign
(paren
id|ULONG
)paren
op_star
id|umap_paddr
suffix:semicolon
macro_line|#       if BITS_PER_LONG &gt; 32
r_if
c_cond
(paren
op_star
id|umap_paddr
op_rshift
l_int|32
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cqpfcTS:Tach SG DMA addr %p&gt;32 bits&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|umap_paddr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#       endif
r_return
op_star
id|umap_paddr
suffix:semicolon
)brace
r_static
r_void
DECL|function|cpqfc_undo_SEST_mappings
id|cpqfc_undo_SEST_mappings
c_func
(paren
r_struct
id|pci_dev
op_star
id|pcidev
comma
r_int
r_int
id|contigaddr
comma
r_int
id|len
comma
r_int
id|dir
comma
r_struct
id|scatterlist
op_star
id|sgl
comma
r_int
id|use_sg
comma
id|PSGPAGES
op_star
id|sgPages_head
comma
r_int
id|allocated_pages
)paren
(brace
id|PSGPAGES
id|i
comma
id|next
suffix:semicolon
r_if
c_cond
(paren
id|contigaddr
op_ne
(paren
r_int
r_int
)paren
l_int|NULL
)paren
id|pci_unmap_single
c_func
(paren
id|pcidev
comma
id|contigaddr
comma
id|len
comma
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sgl
op_ne
l_int|NULL
)paren
id|pci_unmap_sg
c_func
(paren
id|pcidev
comma
id|sgl
comma
id|use_sg
comma
id|dir
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
op_star
id|sgPages_head
suffix:semicolon
id|i
op_ne
l_int|NULL
suffix:semicolon
id|i
op_assign
id|next
)paren
(brace
id|pci_unmap_single
c_func
(paren
id|pcidev
comma
id|i-&gt;busaddr
comma
id|i-&gt;maplen
comma
id|scsi_to_pci_dma_dir
c_func
(paren
id|PCI_DMA_TODEVICE
)paren
)paren
suffix:semicolon
id|i-&gt;busaddr
op_assign
(paren
id|dma_addr_t
)paren
l_int|NULL
suffix:semicolon
id|i-&gt;maplen
op_assign
l_int|0L
suffix:semicolon
id|next
op_assign
id|i-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
op_star
id|sgPages_head
op_assign
l_int|NULL
suffix:semicolon
)brace
singleline_comment|// This routine builds scatter/gather lists into SEST entries
singleline_comment|// INPUTS:
singleline_comment|//   SESTalPair - SEST address @DWordA &quot;Local Buffer Length&quot;
singleline_comment|//   sgList     - Scatter/Gather linked list of Len/Address data buffers
singleline_comment|// OUTPUT:
singleline_comment|//   sgPairs - number of valid address/length pairs
singleline_comment|// Remarks:
singleline_comment|//   The SEST data buffer pointers only depend on number of
singleline_comment|//   length/ address pairs, NOT on the type (IWE, TRE,...)
singleline_comment|//   Up to 3 pairs can be referenced in the SEST - more than 3
singleline_comment|//   require this Extended S/G list page.  The page holds 4, 8, 16...
singleline_comment|//   len/addr pairs, per Scatter/Gather List Page Length Reg.
singleline_comment|//   TachLite allows pages to be linked to any depth.
singleline_comment|//#define DBG_SEST_SGLIST 1 // for printing out S/G pairs with Ext. pages
DECL|variable|ap_hi_water
r_static
r_int
id|ap_hi_water
op_assign
id|TL_DANGER_SGPAGES
suffix:semicolon
DECL|function|build_SEST_sgList
r_static
id|ULONG
id|build_SEST_sgList
c_func
(paren
r_struct
id|pci_dev
op_star
id|pcidev
comma
id|ULONG
op_star
id|SESTalPairStart
comma
singleline_comment|// the 3 len/address buffers in SEST
id|Scsi_Cmnd
op_star
id|Cmnd
comma
id|ULONG
op_star
id|sgPairs
comma
id|PSGPAGES
op_star
id|sgPages_head
)paren
singleline_comment|// link list of TL Ext. S/G pages from O/S Pool
(brace
id|ULONG
id|i
comma
id|AllocatedPages
op_assign
l_int|0
suffix:semicolon
singleline_comment|// Tach Ext. S/G page allocations
id|ULONG
op_star
id|alPair
op_assign
id|SESTalPairStart
suffix:semicolon
id|ULONG
op_star
id|ext_sg_page_phys_addr_place
op_assign
l_int|NULL
suffix:semicolon
r_int
id|PairCount
suffix:semicolon
r_int
r_int
id|ulBuff
comma
id|contigaddr
suffix:semicolon
id|ULONG
id|total_data_len
op_assign
l_int|0
suffix:semicolon
singleline_comment|// (in bytes)
id|ULONG
id|bytes_to_go
op_assign
id|Cmnd-&gt;request_bufflen
suffix:semicolon
singleline_comment|// total xfer (S/G sum)
id|ULONG
id|thisMappingLen
suffix:semicolon
r_struct
id|scatterlist
op_star
id|sgl
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|// S/G list (Linux format)
r_int
id|sg_count
comma
id|totalsgs
suffix:semicolon
id|dma_addr_t
id|busaddr
suffix:semicolon
r_int
r_int
id|thislen
comma
id|offset
suffix:semicolon
id|PSGPAGES
op_star
id|sgpage
op_assign
id|sgPages_head
suffix:semicolon
id|PSGPAGES
id|prev_page
op_assign
l_int|NULL
suffix:semicolon
DECL|macro|WE_HAVE_SG_LIST
macro_line|# define WE_HAVE_SG_LIST (sgl != (unsigned long) NULL)
id|contigaddr
op_assign
(paren
r_int
r_int
)paren
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|Cmnd-&gt;use_sg
)paren
singleline_comment|// no S/G list?
(brace
r_if
c_cond
(paren
id|bytes_to_go
op_le
id|TL_MAX_SG_ELEM_LEN
)paren
(brace
op_star
id|sgPairs
op_assign
l_int|1
suffix:semicolon
singleline_comment|// use &quot;local&quot; S/G pair in SEST entry
singleline_comment|// (for now, ignore address bits above #31)
op_star
id|alPair
op_increment
op_assign
id|bytes_to_go
suffix:semicolon
singleline_comment|// bits 18-0, length
r_if
c_cond
(paren
id|bytes_to_go
op_ne
l_int|0
)paren
(brace
id|contigaddr
op_assign
id|ulBuff
op_assign
id|pci_map_single
c_func
(paren
id|pcidev
comma
id|Cmnd-&gt;request_buffer
comma
id|Cmnd-&gt;request_bufflen
comma
id|scsi_to_pci_dma_dir
c_func
(paren
id|Cmnd-&gt;sc_data_direction
)paren
)paren
suffix:semicolon
singleline_comment|// printk(&quot;ms %p &quot;, ulBuff);
)brace
r_else
(brace
singleline_comment|// No data transfer, (e.g.: Test Unit Ready)
singleline_comment|// printk(&quot;btg=0 &quot;);
op_star
id|sgPairs
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|alPair
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|alPair
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#&t;&t;if BITS_PER_LONG &gt; 32
r_if
c_cond
(paren
id|ulBuff
op_rshift
l_int|32
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;FATAL! Tachyon DMA address %p &quot;
l_string|&quot;exceeds 32 bits&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|ulBuff
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#&t;&t;endif
op_star
id|alPair
op_assign
(paren
id|ULONG
)paren
id|ulBuff
suffix:semicolon
r_return
id|bytes_to_go
suffix:semicolon
)brace
r_else
singleline_comment|// We have a single large (too big) contiguous buffer.
(brace
singleline_comment|// We will have to break it up.  We&squot;ll use the scatter
singleline_comment|// gather code way below, but use contigaddr instead
singleline_comment|// of sg_dma_addr(). (this is a very rare case).
r_int
r_int
id|btg
suffix:semicolon
id|contigaddr
op_assign
id|pci_map_single
c_func
(paren
id|pcidev
comma
id|Cmnd-&gt;request_buffer
comma
id|Cmnd-&gt;request_bufflen
comma
id|scsi_to_pci_dma_dir
c_func
(paren
id|Cmnd-&gt;sc_data_direction
)paren
)paren
suffix:semicolon
singleline_comment|// printk(&quot;contigaddr = %p, len = %d&bslash;n&quot;, 
singleline_comment|//&t;(void *) contigaddr, bytes_to_go);
id|totalsgs
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|btg
op_assign
id|bytes_to_go
suffix:semicolon
id|btg
OG
l_int|0
suffix:semicolon
)paren
(brace
id|btg
op_sub_assign
(paren
id|btg
OG
id|TL_MAX_SG_ELEM_LEN
ques
c_cond
id|TL_MAX_SG_ELEM_LEN
suffix:colon
id|btg
)paren
suffix:semicolon
id|totalsgs
op_increment
suffix:semicolon
)brace
id|sgl
op_assign
l_int|NULL
suffix:semicolon
op_star
id|sgPairs
op_assign
id|totalsgs
suffix:semicolon
)brace
)brace
r_else
singleline_comment|// we do have a scatter gather list
(brace
singleline_comment|// [TBD - update for Linux to support &gt; 32 bits addressing]
singleline_comment|// since the format for local &amp; extended S/G lists is different,
singleline_comment|// check if S/G pairs exceeds 3.
singleline_comment|// *sgPairs = Cmnd-&gt;use_sg; Nope, that&squot;s wrong.
id|sgl
op_assign
(paren
r_struct
id|scatterlist
op_star
)paren
id|Cmnd-&gt;request_buffer
suffix:semicolon
id|sg_count
op_assign
id|pci_map_sg
c_func
(paren
id|pcidev
comma
id|sgl
comma
id|Cmnd-&gt;use_sg
comma
id|scsi_to_pci_dma_dir
c_func
(paren
id|Cmnd-&gt;sc_data_direction
)paren
)paren
suffix:semicolon
singleline_comment|// printk(&quot;sgl = %p, sg_count = %d&bslash;n&quot;, (void *) sgl, sg_count);
r_if
c_cond
(paren
id|sg_count
op_le
l_int|3
)paren
(brace
singleline_comment|// we need to be careful here that no individual mapping
singleline_comment|// is too large, and if any is, that breaking it up
singleline_comment|// doesn&squot;t push us over 3 sgs, or, if it does, that we
singleline_comment|// handle that case.  Tachyon can take 0x7FFFF bits for length,
singleline_comment|// but sg structure uses &quot;unsigned int&quot;, on the face of it, 
singleline_comment|// up to 0xFFFFFFFF or even more.
r_int
id|i
suffix:semicolon
r_int
r_int
id|thislen
suffix:semicolon
id|totalsgs
op_assign
l_int|0
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
id|sg_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|thislen
op_assign
id|sg_dma_len
c_func
(paren
op_amp
id|sgl
(braket
id|i
)braket
)paren
suffix:semicolon
r_while
c_loop
(paren
id|thislen
op_ge
id|TL_MAX_SG_ELEM_LEN
)paren
(brace
id|totalsgs
op_increment
suffix:semicolon
id|thislen
op_sub_assign
id|TL_MAX_SG_ELEM_LEN
suffix:semicolon
)brace
r_if
c_cond
(paren
id|thislen
OG
l_int|0
)paren
id|totalsgs
op_increment
suffix:semicolon
)brace
op_star
id|sgPairs
op_assign
id|totalsgs
suffix:semicolon
)brace
r_else
id|totalsgs
op_assign
l_int|999
suffix:semicolon
singleline_comment|// as a first estimate, definitely &gt;3, 
singleline_comment|// if (totalsgs != sg_count) 
singleline_comment|//&t;printk(&quot;totalsgs = %d, sgcount=%d&bslash;n&quot;,totalsgs,sg_count);
)brace
singleline_comment|// printk(&quot;totalsgs = %d, sgcount=%d&bslash;n&quot;, totalsgs, sg_count);
r_if
c_cond
(paren
id|totalsgs
op_le
l_int|3
)paren
singleline_comment|// can (must) use &quot;local&quot; SEST list
(brace
r_while
c_loop
(paren
id|bytes_to_go
)paren
(brace
id|offset
op_assign
l_int|0L
suffix:semicolon
r_if
c_cond
(paren
id|WE_HAVE_SG_LIST
)paren
id|thisMappingLen
op_assign
id|sg_dma_len
c_func
(paren
id|sgl
)paren
suffix:semicolon
r_else
singleline_comment|// or contiguous buffer?
id|thisMappingLen
op_assign
id|bytes_to_go
suffix:semicolon
r_while
c_loop
(paren
id|thisMappingLen
OG
l_int|0
)paren
(brace
id|thislen
op_assign
id|thisMappingLen
OG
id|TL_MAX_SG_ELEM_LEN
ques
c_cond
id|TL_MAX_SG_ELEM_LEN
suffix:colon
id|thisMappingLen
suffix:semicolon
id|bytes_to_go
op_assign
id|bytes_to_go
op_minus
id|thislen
suffix:semicolon
singleline_comment|// we have L/A pair; L = thislen, A = physicalAddress
singleline_comment|// load into SEST...
id|total_data_len
op_add_assign
id|thislen
suffix:semicolon
op_star
id|alPair
op_assign
id|thislen
suffix:semicolon
singleline_comment|// bits 18-0, length
id|alPair
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|WE_HAVE_SG_LIST
)paren
id|ulBuff
op_assign
id|sg_dma_address
c_func
(paren
id|sgl
)paren
op_plus
id|offset
suffix:semicolon
r_else
id|ulBuff
op_assign
id|contigaddr
op_plus
id|offset
suffix:semicolon
id|offset
op_add_assign
id|thislen
suffix:semicolon
macro_line|#&t;if BITS_PER_LONG &gt; 32
r_if
c_cond
(paren
id|ulBuff
op_rshift
l_int|32
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cqpfcTS: 2Tach DMA address %p &gt; 32 bits&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|ulBuff
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s = %p, offset = %ld&bslash;n&quot;
comma
id|WE_HAVE_SG_LIST
ques
c_cond
l_string|&quot;ulBuff&quot;
suffix:colon
l_string|&quot;contigaddr&quot;
comma
id|WE_HAVE_SG_LIST
ques
c_cond
(paren
r_void
op_star
)paren
id|ulBuff
suffix:colon
(paren
r_void
op_star
)paren
id|contigaddr
comma
id|offset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#&t;endif
op_star
id|alPair
op_increment
op_assign
(paren
id|ULONG
)paren
id|ulBuff
suffix:semicolon
singleline_comment|// lower 32 bits (31-0)
id|thisMappingLen
op_sub_assign
id|thislen
suffix:semicolon
)brace
r_if
c_cond
(paren
id|WE_HAVE_SG_LIST
)paren
op_increment
id|sgl
suffix:semicolon
singleline_comment|// next S/G pair
r_else
r_if
c_cond
(paren
id|bytes_to_go
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;BTG not zero!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#     ifdef DBG_SEST_SGLIST
id|printk
c_func
(paren
l_string|&quot;L=%d &quot;
comma
id|thisMappingLen
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;btg=%d &quot;
comma
id|bytes_to_go
)paren
suffix:semicolon
macro_line|#     endif
)brace
singleline_comment|// printk(&quot;i:%d&bslash;n&quot;, *sgPairs);
)brace
r_else
singleline_comment|// more than 3 pairs requires Extended S/G page (Pool Allocation)
(brace
singleline_comment|// clear out SEST DWORDs (local S/G addr) C-F (A-B set in following logic)
r_for
c_loop
(paren
id|i
op_assign
l_int|2
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|alPair
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|PairCount
op_assign
id|TL_EXT_SG_PAGE_COUNT
suffix:semicolon
singleline_comment|// forces initial page allocation
id|totalsgs
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|bytes_to_go
)paren
(brace
singleline_comment|// Per SEST format, we can support 524287 byte lengths per
singleline_comment|// S/G pair.  Typical user buffers are 4k, and very rarely
singleline_comment|// exceed 12k due to fragmentation of physical memory pages.
singleline_comment|// However, on certain O/S system (not &quot;user&quot;) buffers (on platforms 
singleline_comment|// with huge memories), it&squot;s possible to exceed this
singleline_comment|// length in a single S/G address/len mapping, so we have to handle
singleline_comment|// that.
id|offset
op_assign
l_int|0L
suffix:semicolon
r_if
c_cond
(paren
id|WE_HAVE_SG_LIST
)paren
id|thisMappingLen
op_assign
id|sg_dma_len
c_func
(paren
id|sgl
)paren
suffix:semicolon
r_else
id|thisMappingLen
op_assign
id|bytes_to_go
suffix:semicolon
r_while
c_loop
(paren
id|thisMappingLen
OG
l_int|0
)paren
(brace
id|thislen
op_assign
id|thisMappingLen
OG
id|TL_MAX_SG_ELEM_LEN
ques
c_cond
id|TL_MAX_SG_ELEM_LEN
suffix:colon
id|thisMappingLen
suffix:semicolon
singleline_comment|// printk(&quot;%d/%d/%d&bslash;n&quot;, thislen, thisMappingLen, bytes_to_go);
singleline_comment|// should we load into &quot;this&quot; extended S/G page, or allocate
singleline_comment|// new page?
r_if
c_cond
(paren
id|PairCount
op_ge
id|TL_EXT_SG_PAGE_COUNT
)paren
(brace
singleline_comment|// Now, we have to map the previous page, (triggering buffer bounce)
singleline_comment|// The first time thru the loop, there won&squot;t be a previous page.
r_if
c_cond
(paren
id|prev_page
op_ne
l_int|NULL
)paren
singleline_comment|// is there a prev page? 
(brace
singleline_comment|// this code is normally kind of hard to trigger, 
singleline_comment|// you have to use up more than 256 scatter gather 
singleline_comment|// elements to get here.  Cranking down TL_MAX_SG_ELEM_LEN
singleline_comment|// to an absurdly low value (128 bytes or so) to artificially
singleline_comment|// break i/o&squot;s into a zillion pieces is how I tested it. 
id|busaddr
op_assign
id|cpqfc_pci_map_sg_page
c_func
(paren
id|pcidev
comma
id|ext_sg_page_phys_addr_place
comma
id|prev_page-&gt;page
comma
op_amp
id|prev_page-&gt;busaddr
comma
op_amp
id|prev_page-&gt;maplen
comma
id|PairCount
)paren
suffix:semicolon
)brace
singleline_comment|// Allocate the TL Extended S/G list page.  We have
singleline_comment|// to allocate twice what we want to ensure required TL alignment
singleline_comment|// (Tachlite TL/TS User Man. Rev 6.0, p 168)
singleline_comment|// We store the original allocated PVOID so we can free later
op_star
id|sgpage
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|SGPAGES
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|sgpage
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cpqfc: Allocation failed @ %d S/G page allocations&bslash;n&quot;
comma
id|AllocatedPages
)paren
suffix:semicolon
id|total_data_len
op_assign
l_int|0
suffix:semicolon
singleline_comment|// failure!! Ext. S/G is All-or-none affair
singleline_comment|// unmap the previous mappings, if any.
id|cpqfc_undo_SEST_mappings
c_func
(paren
id|pcidev
comma
id|contigaddr
comma
id|Cmnd-&gt;request_bufflen
comma
id|scsi_to_pci_dma_dir
c_func
(paren
id|Cmnd-&gt;sc_data_direction
)paren
comma
id|sgl
comma
id|Cmnd-&gt;use_sg
comma
id|sgPages_head
comma
id|AllocatedPages
op_plus
l_int|1
)paren
suffix:semicolon
singleline_comment|// FIXME: testing shows that if we get here, 
singleline_comment|// it&squot;s bad news.  (this has been this way for a long 
singleline_comment|// time though, AFAIK.  Not that that excuses it.)
r_return
l_int|0
suffix:semicolon
singleline_comment|// give up (and probably hang the system)
)brace
singleline_comment|// clear out memory we just allocated
id|memset
c_func
(paren
(paren
op_star
id|sgpage
)paren
op_member_access_from_pointer
id|page
comma
l_int|0
comma
id|TL_EXT_SG_PAGE_BYTELEN
op_star
l_int|2
)paren
suffix:semicolon
(paren
op_star
id|sgpage
)paren
op_member_access_from_pointer
id|next
op_assign
l_int|NULL
suffix:semicolon
(paren
op_star
id|sgpage
)paren
op_member_access_from_pointer
id|busaddr
op_assign
(paren
id|dma_addr_t
)paren
l_int|NULL
suffix:semicolon
(paren
op_star
id|sgpage
)paren
op_member_access_from_pointer
id|maplen
op_assign
l_int|0L
suffix:semicolon
singleline_comment|// align the memory - TL requires sizeof() Ext. S/G page alignment.
singleline_comment|// We doubled the actual required size so we could mask off LSBs 
singleline_comment|// to get desired offset 
id|ulBuff
op_assign
(paren
r_int
r_int
)paren
(paren
op_star
id|sgpage
)paren
op_member_access_from_pointer
id|page
suffix:semicolon
id|ulBuff
op_add_assign
id|TL_EXT_SG_PAGE_BYTELEN
suffix:semicolon
id|ulBuff
op_and_assign
op_complement
(paren
id|TL_EXT_SG_PAGE_BYTELEN
op_minus
l_int|1
)paren
suffix:semicolon
singleline_comment|// set pointer, in SEST if first Ext. S/G page, or in last pair
singleline_comment|// of linked Ext. S/G pages... (Only 32-bit PVOIDs, so just 
singleline_comment|// load lower 32 bits)
singleline_comment|// NOTE: the Len field must be &squot;0&squot; if this is the first Ext. S/G
singleline_comment|// pointer in SEST, and not 0 otherwise (we know thislen != 0).
op_star
id|alPair
op_assign
(paren
id|alPair
op_ne
id|SESTalPairStart
)paren
ques
c_cond
id|thislen
suffix:colon
l_int|0
suffix:semicolon
macro_line|#&t;  ifdef DBG_SEST_SGLIST
id|printk
c_func
(paren
l_string|&quot;PairCount %d @%p even %Xh, &quot;
comma
id|PairCount
comma
id|alPair
comma
op_star
id|alPair
)paren
suffix:semicolon
macro_line|#&t;  endif
singleline_comment|// Save the place where we need to store the physical
singleline_comment|// address of this scatter gather page which we get when we map it
singleline_comment|// (and mapping we can do only after we fill it in.)
id|alPair
op_increment
suffix:semicolon
singleline_comment|// next DWORD, will contain phys addr of the ext page
id|ext_sg_page_phys_addr_place
op_assign
id|alPair
suffix:semicolon
singleline_comment|// Now, set alPair = the virtual addr of the (Extended) S/G page
singleline_comment|// which will accept the Len/ PhysicalAddress pairs
id|alPair
op_assign
(paren
id|ULONG
op_star
)paren
id|ulBuff
suffix:semicolon
id|AllocatedPages
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|AllocatedPages
op_ge
id|ap_hi_water
)paren
(brace
singleline_comment|// This message should rarely, if ever, come out.
singleline_comment|// Previously (cpqfc version &lt;= 2.0.5) the driver would
singleline_comment|// just puke if more than 4 SG pages were used, and nobody
singleline_comment|// ever complained about that.  This only comes out if 
singleline_comment|// more than 8 pages are used.
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;cpqfc: Possible danger.  %d scatter gather pages used.&bslash;n&quot;
l_string|&quot;cpqfc: detected seemingly extreme memory &quot;
l_string|&quot;fragmentation or huge data transfers.&bslash;n&quot;
comma
id|AllocatedPages
)paren
suffix:semicolon
id|ap_hi_water
op_assign
id|AllocatedPages
op_plus
l_int|1
suffix:semicolon
)brace
id|PairCount
op_assign
l_int|1
suffix:semicolon
singleline_comment|// starting new Ext. S/G page
id|prev_page
op_assign
(paren
op_star
id|sgpage
)paren
suffix:semicolon
singleline_comment|// remember this page, for next time thru
id|sgpage
op_assign
op_amp
(paren
(paren
op_star
id|sgpage
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
)brace
singleline_comment|// end of new TL Ext. S/G page allocation
op_star
id|alPair
op_assign
id|thislen
suffix:semicolon
singleline_comment|// bits 18-0, length (range check above)
macro_line|#&t;ifdef DBG_SEST_SGLIST
id|printk
c_func
(paren
l_string|&quot;PairCount %d @%p, even %Xh, &quot;
comma
id|PairCount
comma
id|alPair
comma
op_star
id|alPair
)paren
suffix:semicolon
macro_line|#&t;endif
id|alPair
op_increment
suffix:semicolon
singleline_comment|// next DWORD, physical address 
r_if
c_cond
(paren
id|WE_HAVE_SG_LIST
)paren
id|ulBuff
op_assign
id|sg_dma_address
c_func
(paren
id|sgl
)paren
op_plus
id|offset
suffix:semicolon
r_else
id|ulBuff
op_assign
id|contigaddr
op_plus
id|offset
suffix:semicolon
id|offset
op_add_assign
id|thislen
suffix:semicolon
macro_line|#&t;if BITS_PER_LONG &gt; 32
r_if
c_cond
(paren
id|ulBuff
op_rshift
l_int|32
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cqpfcTS: 1Tach DMA address %p &gt; 32 bits&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|ulBuff
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s = %p, offset = %ld&bslash;n&quot;
comma
id|WE_HAVE_SG_LIST
ques
c_cond
l_string|&quot;ulBuff&quot;
suffix:colon
l_string|&quot;contigaddr&quot;
comma
id|WE_HAVE_SG_LIST
ques
c_cond
(paren
r_void
op_star
)paren
id|ulBuff
suffix:colon
(paren
r_void
op_star
)paren
id|contigaddr
comma
id|offset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#&t;endif
op_star
id|alPair
op_assign
(paren
id|ULONG
)paren
id|ulBuff
suffix:semicolon
singleline_comment|// lower 32 bits (31-0)
macro_line|#       ifdef DBG_SEST_SGLIST
id|printk
c_func
(paren
l_string|&quot;odd %Xh&bslash;n&quot;
comma
op_star
id|alPair
)paren
suffix:semicolon
macro_line|#       endif
id|alPair
op_increment
suffix:semicolon
singleline_comment|// next DWORD, next address/length pair
id|PairCount
op_increment
suffix:semicolon
singleline_comment|// next Length/Address pair
singleline_comment|// if (PairCount &gt; pc_hi_water)
singleline_comment|// {
singleline_comment|// printk(&quot;pc hi = %d &quot;, PairCount);
singleline_comment|// pc_hi_water = PairCount;
singleline_comment|// }
id|bytes_to_go
op_sub_assign
id|thislen
suffix:semicolon
id|total_data_len
op_add_assign
id|thislen
suffix:semicolon
id|thisMappingLen
op_sub_assign
id|thislen
suffix:semicolon
id|totalsgs
op_increment
suffix:semicolon
)brace
singleline_comment|// while (thisMappingLen &gt; 0)
r_if
c_cond
(paren
id|WE_HAVE_SG_LIST
)paren
id|sgl
op_increment
suffix:semicolon
singleline_comment|// next S/G pair
)brace
singleline_comment|// while (bytes_to_go)
singleline_comment|// printk(&quot;Totalsgs=%d&bslash;n&quot;, totalsgs);
op_star
id|sgPairs
op_assign
id|totalsgs
suffix:semicolon
singleline_comment|// PCI map (and bounce) the last (and usually only) extended SG page
id|busaddr
op_assign
id|cpqfc_pci_map_sg_page
c_func
(paren
id|pcidev
comma
id|ext_sg_page_phys_addr_place
comma
id|prev_page-&gt;page
comma
op_amp
id|prev_page-&gt;busaddr
comma
op_amp
id|prev_page-&gt;maplen
comma
id|PairCount
)paren
suffix:semicolon
)brace
r_return
id|total_data_len
suffix:semicolon
)brace
singleline_comment|// The Tachlite SEST table is referenced to OX_ID (or RX_ID).  To optimize
singleline_comment|// performance and debuggability, we index the Exchange structure to FC X_ID
singleline_comment|// This enables us to build exchanges for later en-queing to Tachyon,
singleline_comment|// provided we have an open X_ID slot. At Tachyon queing time, we only 
singleline_comment|// need an ERQ slot; then &quot;fix-up&quot; references in the 
singleline_comment|// IRB, FCHS, etc. as needed.
singleline_comment|// RETURNS:
singleline_comment|// 0 if successful
singleline_comment|// non-zero on error
singleline_comment|//sstartex
DECL|function|cpqfcTSStartExchange
id|ULONG
id|cpqfcTSStartExchange
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|LONG
id|ExchangeID
)paren
(brace
id|PTACHYON
id|fcChip
op_assign
op_amp
id|cpqfcHBAdata-&gt;fcChip
suffix:semicolon
id|FC_EXCHANGES
op_star
id|Exchanges
op_assign
id|fcChip-&gt;Exchanges
suffix:semicolon
id|FC_EXCHANGE
op_star
id|pExchange
op_assign
op_amp
id|Exchanges-&gt;fcExchange
(braket
id|ExchangeID
)braket
suffix:semicolon
singleline_comment|// shorthand
id|USHORT
id|producer
comma
id|consumer
suffix:semicolon
id|ULONG
id|ulStatus
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|ErqIndex
suffix:semicolon
id|BOOLEAN
id|CompleteExchange
op_assign
id|FALSE
suffix:semicolon
singleline_comment|// e.g. ACC replies are complete
id|BOOLEAN
id|SestType
op_assign
id|FALSE
suffix:semicolon
id|ULONG
id|InboundData
op_assign
l_int|0
suffix:semicolon
singleline_comment|// We will manipulate Tachlite chip registers here to successfully
singleline_comment|// start exchanges. 
singleline_comment|// Check that link is not down -- we can&squot;t start an exchange on a
singleline_comment|// down link!
r_if
c_cond
(paren
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0x80
)paren
singleline_comment|// LPSM offline?
(brace
id|printk
c_func
(paren
l_string|&quot;fcStartExchange: PSM offline (%Xh), x_ID %Xh, type %Xh, port_id %Xh&bslash;n&quot;
comma
id|fcChip-&gt;Registers.FMstatus.value
op_amp
l_int|0xFF
comma
id|ExchangeID
comma
id|pExchange-&gt;type
comma
id|pExchange-&gt;fchs.d_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ExchangeID
op_ge
id|TACH_SEST_LEN
)paren
singleline_comment|// Link Service Outbound frame?
(brace
singleline_comment|// Our most popular LinkService commands are port discovery types
singleline_comment|// (PLOGI/ PDISC...), which are implicitly nullified by Link Down
singleline_comment|// events, so it makes no sense to Que them.  However, ABTS should
singleline_comment|// be queued, since exchange sequences are likely destroyed by
singleline_comment|// Link Down events, and we want to notify other ports of broken
singleline_comment|// sequences by aborting the corresponding exchanges.
r_if
c_cond
(paren
id|pExchange-&gt;type
op_ne
id|BLS_ABTS
)paren
(brace
id|ulStatus
op_assign
id|LNKDWN_OSLS
suffix:semicolon
r_goto
id|Done
suffix:semicolon
singleline_comment|// don&squot;t Que most LinkServ exchanges on LINK DOWN
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;fcStartExchange: Que x_ID %Xh, type %Xh&bslash;n&quot;
comma
id|ExchangeID
comma
id|pExchange-&gt;type
)paren
suffix:semicolon
id|pExchange-&gt;status
op_or_assign
id|EXCHANGE_QUEUED
suffix:semicolon
id|ulStatus
op_assign
id|EXCHANGE_QUEUED
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
singleline_comment|// Make sure ERQ has available space.
id|producer
op_assign
(paren
id|USHORT
)paren
id|fcChip-&gt;ERQ-&gt;producerIndex
suffix:semicolon
singleline_comment|// copies for logical arith.
id|consumer
op_assign
(paren
id|USHORT
)paren
id|fcChip-&gt;ERQ-&gt;consumerIndex
suffix:semicolon
id|producer
op_increment
suffix:semicolon
singleline_comment|// We are testing for full que by incrementing
r_if
c_cond
(paren
id|producer
op_ge
id|ERQ_LEN
)paren
(brace
singleline_comment|// rollover condition?
id|producer
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|consumer
op_ne
id|producer
)paren
singleline_comment|// ERQ not full?
(brace
singleline_comment|// ****************** Need Atomic access to chip registers!!********
singleline_comment|// remember ERQ PI for copying IRB
id|ErqIndex
op_assign
(paren
id|USHORT
)paren
id|fcChip-&gt;ERQ-&gt;producerIndex
suffix:semicolon
id|fcChip-&gt;ERQ-&gt;producerIndex
op_assign
id|producer
suffix:semicolon
singleline_comment|// this is written to Tachyon
singleline_comment|// we have an ERQ slot! If SCSI command, need SEST slot
singleline_comment|// otherwise we are done.
singleline_comment|// Note that Tachyon requires that bit 15 of the OX_ID or RX_ID be
singleline_comment|// set according to direction of data to/from Tachyon for SEST assists.
singleline_comment|// For consistency, enforce this rule for Link Service (non-SEST)
singleline_comment|// exchanges as well.
singleline_comment|// fix-up the X_ID field in IRB
id|pExchange-&gt;IRB.Req_A_Trans_ID
op_assign
id|ExchangeID
op_amp
l_int|0x7FFF
suffix:semicolon
singleline_comment|// 15-bit field
singleline_comment|// fix-up the X_ID field in fchs -- depends on Originator or Responder,
singleline_comment|// outgoing or incoming data?
r_switch
c_cond
(paren
id|pExchange-&gt;type
)paren
(brace
singleline_comment|// ORIGINATOR types...  we&squot;re setting our OX_ID and
singleline_comment|// defaulting the responder&squot;s RX_ID to 0xFFFF
r_case
id|SCSI_IRE
suffix:colon
singleline_comment|// Requirement: set MSB of x_ID for Incoming TL data
singleline_comment|// (see &quot;Tachyon TL/TS User&squot;s Manual&quot;, Rev 6.0, Sept.&squot;98, pg. 50)
id|InboundData
op_assign
l_int|0x8000
suffix:semicolon
r_case
id|SCSI_IWE
suffix:colon
id|SestType
op_assign
id|TRUE
suffix:semicolon
id|pExchange-&gt;fchs.ox_rx_id
op_assign
(paren
id|ExchangeID
op_or
id|InboundData
)paren
suffix:semicolon
id|pExchange-&gt;fchs.ox_rx_id
op_lshift_assign
l_int|16
suffix:semicolon
singleline_comment|// MSW shift
id|pExchange-&gt;fchs.ox_rx_id
op_or_assign
l_int|0xffff
suffix:semicolon
singleline_comment|// add default RX_ID
singleline_comment|// now fix-up the Data HDR OX_ID (TL automatically does rx_id)
singleline_comment|// (not necessary for IRE -- data buffer unused)
r_if
c_cond
(paren
id|pExchange-&gt;type
op_eq
id|SCSI_IWE
)paren
(brace
id|fcChip-&gt;SEST-&gt;DataHDR
(braket
id|ExchangeID
)braket
dot
id|ox_rx_id
op_assign
id|pExchange-&gt;fchs.ox_rx_id
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|FCS_NSR
suffix:colon
singleline_comment|// ext. link service Name Service Request
r_case
id|ELS_SCR
suffix:colon
singleline_comment|// ext. link service State Change Registration
r_case
id|ELS_FDISC
suffix:colon
singleline_comment|// ext. link service login
r_case
id|ELS_FLOGI
suffix:colon
singleline_comment|// ext. link service login
r_case
id|ELS_LOGO
suffix:colon
singleline_comment|// FC-PH extended link service logout
r_case
id|BLS_NOP
suffix:colon
singleline_comment|// Basic link service No OPeration
r_case
id|ELS_PLOGI
suffix:colon
singleline_comment|// ext. link service login (PLOGI)
r_case
id|ELS_PDISC
suffix:colon
singleline_comment|// ext. link service login (PDISC)
r_case
id|ELS_PRLI
suffix:colon
singleline_comment|// ext. link service process login
id|pExchange-&gt;fchs.ox_rx_id
op_assign
id|ExchangeID
suffix:semicolon
id|pExchange-&gt;fchs.ox_rx_id
op_lshift_assign
l_int|16
suffix:semicolon
singleline_comment|// MSW shift
id|pExchange-&gt;fchs.ox_rx_id
op_or_assign
l_int|0xffff
suffix:semicolon
singleline_comment|// and RX_ID
r_break
suffix:semicolon
singleline_comment|// RESPONDER types... we must set our RX_ID while preserving
singleline_comment|// sender&squot;s OX_ID
singleline_comment|// outgoing (or no) data
r_case
id|ELS_RJT
suffix:colon
singleline_comment|// extended link service reject 
r_case
id|ELS_LOGO_ACC
suffix:colon
singleline_comment|// FC-PH extended link service logout accept
r_case
id|ELS_ACC
suffix:colon
singleline_comment|// ext. generic link service accept
r_case
id|ELS_PLOGI_ACC
suffix:colon
singleline_comment|// ext. link service login accept (PLOGI or PDISC)
r_case
id|ELS_PRLI_ACC
suffix:colon
singleline_comment|// ext. link service process login accept
id|CompleteExchange
op_assign
id|TRUE
suffix:semicolon
singleline_comment|// Reply (ACC or RJT) is end of exchange
id|pExchange-&gt;fchs.ox_rx_id
op_or_assign
(paren
id|ExchangeID
op_amp
l_int|0xFFFF
)paren
suffix:semicolon
r_break
suffix:semicolon
singleline_comment|// since we are a Responder, OX_ID should already be set by
singleline_comment|// cpqfcTSBuildExchange().  We need to -OR- in RX_ID
r_case
id|SCSI_TWE
suffix:colon
id|SestType
op_assign
id|TRUE
suffix:semicolon
singleline_comment|// Requirement: set MSB of x_ID for Incoming TL data
singleline_comment|// (see &quot;Tachyon TL/TS User&squot;s Manual&quot;, Rev 6.0, Sept.&squot;98, pg. 50)
id|pExchange-&gt;fchs.ox_rx_id
op_and_assign
l_int|0xFFFF0000
suffix:semicolon
singleline_comment|// clear RX_ID
singleline_comment|// Requirement: set MSB of RX_ID for Incoming TL data
singleline_comment|// (see &quot;Tachyon TL/TS User&squot;s Manual&quot;, Rev 6.0, Sept.&squot;98, pg. 50)
id|pExchange-&gt;fchs.ox_rx_id
op_or_assign
(paren
id|ExchangeID
op_or
l_int|0x8000
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCSI_TRE
suffix:colon
id|SestType
op_assign
id|TRUE
suffix:semicolon
singleline_comment|// there is no XRDY for SEST target read; the data
singleline_comment|// header needs to be updated. Also update the RSP
singleline_comment|// exchange IDs for the status frame, in case it is sent automatically
id|fcChip-&gt;SEST-&gt;DataHDR
(braket
id|ExchangeID
)braket
dot
id|ox_rx_id
op_or_assign
id|ExchangeID
suffix:semicolon
id|fcChip-&gt;SEST-&gt;RspHDR
(braket
id|ExchangeID
)braket
dot
id|ox_rx_id
op_assign
id|fcChip-&gt;SEST-&gt;DataHDR
(braket
id|ExchangeID
)braket
dot
id|ox_rx_id
suffix:semicolon
singleline_comment|// for easier FCP response logic (works for TWE and TRE), 
singleline_comment|// copy exchange IDs.  (Not needed if TRE &squot;RSP&squot; bit set)
id|pExchange-&gt;fchs.ox_rx_id
op_assign
id|fcChip-&gt;SEST-&gt;DataHDR
(braket
id|ExchangeID
)braket
dot
id|ox_rx_id
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FCP_RESPONSE
suffix:colon
singleline_comment|// using existing OX_ID/ RX_ID pair,
singleline_comment|// start SFS FCP-RESPONSE frame
singleline_comment|// OX/RX_ID should already be set! (See &quot;fcBuild&quot; above)
id|CompleteExchange
op_assign
id|TRUE
suffix:semicolon
singleline_comment|// RSP is end of FCP-SCSI exchange
r_break
suffix:semicolon
r_case
id|BLS_ABTS_RJT
suffix:colon
singleline_comment|// uses new RX_ID, since SEST x_ID non-existent
r_case
id|BLS_ABTS_ACC
suffix:colon
singleline_comment|// using existing OX_ID/ RX_ID pair from SEST entry
id|CompleteExchange
op_assign
id|TRUE
suffix:semicolon
singleline_comment|// ACC or RJT marks end of FCP-SCSI exchange
r_case
id|BLS_ABTS
suffix:colon
singleline_comment|// using existing OX_ID/ RX_ID pair from SEST entry
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Error on fcStartExchange: undefined type %Xh(%d)&bslash;n&quot;
comma
id|pExchange-&gt;type
comma
id|pExchange-&gt;type
)paren
suffix:semicolon
r_return
id|INVALID_ARGS
suffix:semicolon
)brace
singleline_comment|// X_ID fields are entered -- copy IRB to Tachyon&squot;s ERQ
id|memcpy
c_func
(paren
op_amp
id|fcChip-&gt;ERQ-&gt;QEntry
(braket
id|ErqIndex
)braket
comma
singleline_comment|// dest.
op_amp
id|pExchange-&gt;IRB
comma
l_int|32
)paren
suffix:semicolon
singleline_comment|// fixed (hardware) length!
id|PCI_TRACEO
c_func
(paren
id|ExchangeID
comma
l_int|0xA0
)paren
singleline_comment|// ACTION!  May generate INT and IMQ entry
id|writel
c_func
(paren
id|fcChip-&gt;ERQ-&gt;producerIndex
comma
id|fcChip-&gt;Registers.ERQproducerIndex.address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ExchangeID
op_ge
id|TACH_SEST_LEN
)paren
singleline_comment|// Link Service Outbound frame?
(brace
singleline_comment|// wait for completion! (TDB -- timeout and chip reset)
id|PCI_TRACEO
c_func
(paren
id|ExchangeID
comma
l_int|0xA4
)paren
id|enable_irq
c_func
(paren
id|cpqfcHBAdata-&gt;HostAdapter-&gt;irq
)paren
suffix:semicolon
singleline_comment|// only way to get Sem.
id|down_interruptible
c_func
(paren
id|cpqfcHBAdata-&gt;TYOBcomplete
)paren
suffix:semicolon
id|disable_irq
c_func
(paren
id|cpqfcHBAdata-&gt;HostAdapter-&gt;irq
)paren
suffix:semicolon
id|PCI_TRACE
c_func
(paren
l_int|0xA4
)paren
singleline_comment|// On login exchanges, BAD_ALPA (non-existent port_id) results in 
singleline_comment|// FTO (Frame Time Out) on the Outbound Completion message.
singleline_comment|// If we got an FTO status, complete the exchange (free up slot)
r_if
c_cond
(paren
id|CompleteExchange
op_logical_or
singleline_comment|// flag from Reply frames
id|pExchange-&gt;status
)paren
singleline_comment|// typically, can get FRAME_TO
(brace
id|cpqfcTSCompleteExchange
c_func
(paren
id|cpqfcHBAdata-&gt;PciDev
comma
id|fcChip
comma
id|ExchangeID
)paren
suffix:semicolon
)brace
)brace
r_else
singleline_comment|// SEST Exchange
(brace
id|ulStatus
op_assign
l_int|0
suffix:semicolon
singleline_comment|// ship &amp; pray success (e.g. FCP-SCSI)
r_if
c_cond
(paren
id|CompleteExchange
)paren
singleline_comment|// by Type of exchange (e.g. end-of-xchng)
(brace
id|cpqfcTSCompleteExchange
c_func
(paren
id|cpqfcHBAdata-&gt;PciDev
comma
id|fcChip
comma
id|ExchangeID
)paren
suffix:semicolon
)brace
r_else
id|pExchange-&gt;status
op_and_assign
op_complement
id|EXCHANGE_QUEUED
suffix:semicolon
singleline_comment|// clear ExchangeQueued flag 
)brace
)brace
r_else
singleline_comment|// ERQ &squot;producer&squot; = &squot;consumer&squot; and QUE is full
(brace
id|ulStatus
op_assign
id|OUTQUE_FULL
suffix:semicolon
singleline_comment|// Outbound (ERQ) Que full
)brace
id|Done
suffix:colon
id|PCI_TRACE
c_func
(paren
l_int|0xA0
)paren
r_return
id|ulStatus
suffix:semicolon
)brace
singleline_comment|// Scan fcController-&gt;fcExchanges array for a usuable index (a &quot;free&quot;
singleline_comment|// exchange).
singleline_comment|// Inputs:
singleline_comment|//   fcChip - pointer to TachLite chip structure
singleline_comment|// Return:
singleline_comment|//  index - exchange array element where exchange can be built
singleline_comment|//  -1    - exchange array is full
singleline_comment|// REMARKS:
singleline_comment|// Although this is a (yuk!) linear search, we presume
singleline_comment|// that the system will complete exchanges about as quickly as
singleline_comment|// they are submitted.  A full Exchange array (and hence, max linear
singleline_comment|// search time for free exchange slot) almost guarantees a Fibre problem 
singleline_comment|// of some sort.
singleline_comment|// In the interest of making exchanges easier to debug, we want a LRU
singleline_comment|// (Least Recently Used) scheme.
DECL|function|FindFreeExchange
r_static
id|LONG
id|FindFreeExchange
c_func
(paren
id|PTACHYON
id|fcChip
comma
id|ULONG
id|type
)paren
(brace
id|FC_EXCHANGES
op_star
id|Exchanges
op_assign
id|fcChip-&gt;Exchanges
suffix:semicolon
id|ULONG
id|i
suffix:semicolon
id|ULONG
id|ulStatus
op_assign
op_minus
l_int|1
suffix:semicolon
singleline_comment|// assume failure
r_if
c_cond
(paren
id|type
op_eq
id|SCSI_IRE
op_logical_or
id|type
op_eq
id|SCSI_TRE
op_logical_or
id|type
op_eq
id|SCSI_IWE
op_logical_or
id|type
op_eq
id|SCSI_TWE
)paren
(brace
singleline_comment|// SCSI type - X_IDs should be from 0 to TACH_SEST_LEN-1
r_if
c_cond
(paren
id|fcChip-&gt;fcSestExchangeLRU
op_ge
id|TACH_SEST_LEN
)paren
(brace
singleline_comment|// rollover?
id|fcChip-&gt;fcSestExchangeLRU
op_assign
l_int|0
suffix:semicolon
)brace
id|i
op_assign
id|fcChip-&gt;fcSestExchangeLRU
suffix:semicolon
singleline_comment|// typically it&squot;s already free!
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|type
op_eq
l_int|0
)paren
singleline_comment|// check for &quot;free&quot; element
(brace
id|ulStatus
op_assign
l_int|0
suffix:semicolon
singleline_comment|// success!
)brace
r_else
(brace
singleline_comment|// YUK! we need to do a linear search for free element.
singleline_comment|// Fragmentation of the fcExchange array is due to excessively
singleline_comment|// long completions or timeouts.
r_while
c_loop
(paren
id|TRUE
)paren
(brace
r_if
c_cond
(paren
op_increment
id|i
op_ge
id|TACH_SEST_LEN
)paren
(brace
singleline_comment|// rollover check
id|i
op_assign
l_int|0
suffix:semicolon
)brace
singleline_comment|// beginning of SEST X_IDs
singleline_comment|//        printk( &quot;looping for SCSI xchng ID: i=%d, type=%Xh&bslash;n&quot;, 
singleline_comment|//         i, Exchanges-&gt;fcExchange[i].type);
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|type
op_eq
l_int|0
)paren
singleline_comment|// &quot;free&quot;?
(brace
id|ulStatus
op_assign
l_int|0
suffix:semicolon
singleline_comment|// success!
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|fcChip-&gt;fcSestExchangeLRU
)paren
singleline_comment|// wrapped-around array?
(brace
id|printk
c_func
(paren
l_string|&quot;SEST X_ID space full&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
singleline_comment|// failed - prevent inf. loop
)brace
)brace
)brace
id|fcChip-&gt;fcSestExchangeLRU
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
singleline_comment|// next! (rollover check next pass)
)brace
r_else
singleline_comment|// Link Service type - X_IDs should be from TACH_SEST_LEN 
singleline_comment|// to TACH_MAX_XID
(brace
r_if
c_cond
(paren
id|fcChip-&gt;fcLsExchangeLRU
op_ge
id|TACH_MAX_XID
op_logical_or
singleline_comment|// range check
id|fcChip-&gt;fcLsExchangeLRU
OL
id|TACH_SEST_LEN
)paren
(brace
singleline_comment|// (e.g. startup)
id|fcChip-&gt;fcLsExchangeLRU
op_assign
id|TACH_SEST_LEN
suffix:semicolon
)brace
id|i
op_assign
id|fcChip-&gt;fcLsExchangeLRU
suffix:semicolon
singleline_comment|// typically it&squot;s already free!
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|type
op_eq
l_int|0
)paren
singleline_comment|// check for &quot;free&quot; element
(brace
id|ulStatus
op_assign
l_int|0
suffix:semicolon
singleline_comment|// success!
)brace
r_else
(brace
singleline_comment|// YUK! we need to do a linear search for free element
singleline_comment|// Fragmentation of the fcExchange array is due to excessively
singleline_comment|// long completions or timeouts.
r_while
c_loop
(paren
id|TRUE
)paren
(brace
r_if
c_cond
(paren
op_increment
id|i
op_ge
id|TACH_MAX_XID
)paren
(brace
singleline_comment|// rollover check
id|i
op_assign
id|TACH_SEST_LEN
suffix:semicolon
)brace
singleline_comment|// beginning of Link Service X_IDs
singleline_comment|//        printk( &quot;looping for xchng ID: i=%d, type=%Xh&bslash;n&quot;, 
singleline_comment|//         i, Exchanges-&gt;fcExchange[i].type);
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|type
op_eq
l_int|0
)paren
singleline_comment|// &quot;free&quot;?
(brace
id|ulStatus
op_assign
l_int|0
suffix:semicolon
singleline_comment|// success!
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|fcChip-&gt;fcLsExchangeLRU
)paren
singleline_comment|// wrapped-around array?
(brace
id|printk
c_func
(paren
l_string|&quot;LinkService X_ID space full&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
singleline_comment|// failed - prevent inf. loop
)brace
)brace
)brace
id|fcChip-&gt;fcLsExchangeLRU
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
singleline_comment|// next! (rollover check next pass)
)brace
r_if
c_cond
(paren
op_logical_neg
id|ulStatus
)paren
(brace
singleline_comment|// success?
id|Exchanges-&gt;fcExchange
(braket
id|i
)braket
dot
id|type
op_assign
id|type
suffix:semicolon
)brace
singleline_comment|// allocate it.
r_else
id|i
op_assign
op_minus
l_int|1
suffix:semicolon
singleline_comment|// error - all exchanges &quot;open&quot;
r_return
id|i
suffix:semicolon
)brace
r_static
r_void
DECL|function|cpqfc_pci_unmap_extended_sg
id|cpqfc_pci_unmap_extended_sg
c_func
(paren
r_struct
id|pci_dev
op_star
id|pcidev
comma
id|PTACHYON
id|fcChip
comma
id|ULONG
id|x_ID
)paren
(brace
singleline_comment|// Unmaps the memory regions used to hold the scatter gather lists
id|PSGPAGES
id|i
suffix:semicolon
singleline_comment|// Were there any such regions needing unmapping?
r_if
c_cond
(paren
op_logical_neg
id|USES_EXTENDED_SGLIST
c_func
(paren
id|fcChip-&gt;SEST
comma
id|x_ID
)paren
)paren
r_return
suffix:semicolon
singleline_comment|// No such regions, we&squot;re outta here.
singleline_comment|// for each extended scatter gather region needing unmapping... 
r_for
c_loop
(paren
id|i
op_assign
id|fcChip-&gt;SEST-&gt;sgPages
(braket
id|x_ID
)braket
suffix:semicolon
id|i
op_ne
l_int|NULL
suffix:semicolon
id|i
op_assign
id|i-&gt;next
)paren
id|pci_unmap_single
c_func
(paren
id|pcidev
comma
id|i-&gt;busaddr
comma
id|i-&gt;maplen
comma
id|scsi_to_pci_dma_dir
c_func
(paren
id|PCI_DMA_TODEVICE
)paren
)paren
suffix:semicolon
)brace
singleline_comment|// Called also from cpqfcTScontrol.o, so can&squot;t be static
r_void
DECL|function|cpqfc_pci_unmap
id|cpqfc_pci_unmap
c_func
(paren
r_struct
id|pci_dev
op_star
id|pcidev
comma
id|Scsi_Cmnd
op_star
id|cmd
comma
id|PTACHYON
id|fcChip
comma
id|ULONG
id|x_ID
)paren
(brace
singleline_comment|// Undo the DMA mappings
r_if
c_cond
(paren
id|cmd-&gt;use_sg
)paren
(brace
singleline_comment|// Used scatter gather list for data buffer?
id|cpqfc_pci_unmap_extended_sg
c_func
(paren
id|pcidev
comma
id|fcChip
comma
id|x_ID
)paren
suffix:semicolon
id|pci_unmap_sg
c_func
(paren
id|pcidev
comma
id|cmd-&gt;buffer
comma
id|cmd-&gt;use_sg
comma
id|scsi_to_pci_dma_dir
c_func
(paren
id|cmd-&gt;sc_data_direction
)paren
)paren
suffix:semicolon
singleline_comment|// printk(&quot;umsg %d&bslash;n&quot;, cmd-&gt;use_sg);
)brace
r_else
r_if
c_cond
(paren
id|cmd-&gt;request_bufflen
)paren
(brace
singleline_comment|// printk(&quot;ums %p &quot;, fcChip-&gt;SEST-&gt;u[ x_ID ].IWE.GAddr1);
id|pci_unmap_single
c_func
(paren
id|pcidev
comma
id|fcChip-&gt;SEST-&gt;u
(braket
id|x_ID
)braket
dot
id|IWE.GAddr1
comma
id|cmd-&gt;request_bufflen
comma
id|scsi_to_pci_dma_dir
c_func
(paren
id|cmd-&gt;sc_data_direction
)paren
)paren
suffix:semicolon
)brace
)brace
singleline_comment|// We call this routine to free an Exchange for any reason:
singleline_comment|// completed successfully, completed with error, aborted, etc.
singleline_comment|// returns FALSE if Exchange failed and &quot;retry&quot; is acceptable
singleline_comment|// returns TRUE if Exchange was successful, or retry is impossible
singleline_comment|// (e.g. port/device gone).
singleline_comment|//scompleteexchange
DECL|function|cpqfcTSCompleteExchange
r_void
id|cpqfcTSCompleteExchange
c_func
(paren
r_struct
id|pci_dev
op_star
id|pcidev
comma
id|PTACHYON
id|fcChip
comma
id|ULONG
id|x_ID
)paren
(brace
id|FC_EXCHANGES
op_star
id|Exchanges
op_assign
id|fcChip-&gt;Exchanges
suffix:semicolon
r_int
id|already_unmapped
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|x_ID
OL
id|TACH_SEST_LEN
)paren
singleline_comment|// SEST-based (or LinkServ for FCP exchange)
(brace
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd
op_eq
l_int|NULL
)paren
singleline_comment|// what#@!
(brace
singleline_comment|//      TriggerHBA( fcChip-&gt;Registers.ReMapMemBase, 0);
id|printk
c_func
(paren
l_string|&quot; x_ID %Xh, type %Xh, NULL ptr!&bslash;n&quot;
comma
id|x_ID
comma
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|type
)paren
suffix:semicolon
r_goto
id|CleanUpSestResources
suffix:semicolon
singleline_comment|// this path should be very rare.
)brace
singleline_comment|// we have Linux Scsi Cmnd ptr..., now check our Exchange status
singleline_comment|// to decide how to complete this SEST FCP exchange
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
)paren
singleline_comment|// perhaps a Tach indicated problem,
singleline_comment|// or abnormal exchange completion
(brace
singleline_comment|// set FCP Link statistics
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|FC2_TIMEOUT
)paren
(brace
id|fcChip-&gt;fcStats.timeouts
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|INITIATOR_ABORT
)paren
(brace
id|fcChip-&gt;fcStats.FC4aborted
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|COUNT_ERROR
)paren
(brace
id|fcChip-&gt;fcStats.CntErrors
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|LINKFAIL_TX
)paren
(brace
id|fcChip-&gt;fcStats.linkFailTX
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|LINKFAIL_RX
)paren
(brace
id|fcChip-&gt;fcStats.linkFailRX
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|OVERFLOW
)paren
(brace
id|fcChip-&gt;fcStats.CntErrors
op_increment
suffix:semicolon
)brace
singleline_comment|// First, see if the Scsi upper level initiated an ABORT on this
singleline_comment|// exchange...
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_eq
id|INITIATOR_ABORT
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; DID_ABORT, x_ID %Xh, Cmnd %p &quot;
comma
id|x_ID
comma
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd
)paren
suffix:semicolon
r_goto
id|CleanUpSestResources
suffix:semicolon
singleline_comment|// (we don&squot;t expect Linux _aborts)
)brace
singleline_comment|// Did our driver timeout the Exchange, or did Tachyon indicate
singleline_comment|// a failure during transmission?  Ask for retry with &quot;SOFT_ERROR&quot;
r_else
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|FC2_TIMEOUT
)paren
(brace
singleline_comment|//        printk(&quot;result DID_SOFT_ERROR, x_ID %Xh, Cmnd %p&bslash;n&quot;, 
singleline_comment|//            x_ID, Exchanges-&gt;fcExchange[ x_ID ].Cmnd);
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;result
op_assign
(paren
id|DID_SOFT_ERROR
op_lshift
l_int|16
)paren
suffix:semicolon
)brace
singleline_comment|// Did frame(s) for an open exchange arrive in the SFQ,
singleline_comment|// meaning the SEST was unable to process them?
r_else
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|SFQ_FRAME
)paren
(brace
singleline_comment|//        printk(&quot;result DID_SOFT_ERROR, x_ID %Xh, Cmnd %p&bslash;n&quot;, 
singleline_comment|//            x_ID, Exchanges-&gt;fcExchange[ x_ID ].Cmnd);
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;result
op_assign
(paren
id|DID_SOFT_ERROR
op_lshift
l_int|16
)paren
suffix:semicolon
)brace
singleline_comment|// Did our driver timeout the Exchange, or did Tachyon indicate
singleline_comment|// a failure during transmission?  Ask for retry with &quot;SOFT_ERROR&quot;
r_else
r_if
c_cond
(paren
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|LINKFAIL_TX
)paren
op_logical_or
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|PORTID_CHANGED
)paren
op_logical_or
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|FRAME_TO
)paren
op_logical_or
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|INV_ENTRY
)paren
op_logical_or
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|ABORTSEQ_NOTIFY
)paren
)paren
(brace
singleline_comment|//        printk(&quot;result DID_SOFT_ERROR, x_ID %Xh, Cmnd %p&bslash;n&quot;, 
singleline_comment|//            x_ID, Exchanges-&gt;fcExchange[ x_ID ].Cmnd);
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;result
op_assign
(paren
id|DID_SOFT_ERROR
op_lshift
l_int|16
)paren
suffix:semicolon
)brace
singleline_comment|// e.g., a LOGOut happened, or device never logged back in.
r_else
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_amp
id|DEVICE_REMOVED
)paren
(brace
singleline_comment|//&t;printk(&quot; *LOGOut or timeout on login!* &quot;);
singleline_comment|// trigger?
singleline_comment|//        TriggerHBA( fcChip-&gt;Registers.ReMapMemBase, 0);
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;result
op_assign
(paren
id|DID_BAD_TARGET
op_lshift
l_int|16
)paren
suffix:semicolon
)brace
singleline_comment|// Did Tachyon indicate a CNT error?  We need further analysis
singleline_comment|// to determine if the exchange is acceptable
r_else
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_eq
id|COUNT_ERROR
)paren
(brace
id|UCHAR
id|ScsiStatus
suffix:semicolon
id|FCP_STATUS_RESPONSE
op_star
id|pFcpStatus
op_assign
(paren
id|PFCP_STATUS_RESPONSE
)paren
op_amp
id|fcChip-&gt;SEST-&gt;RspHDR
(braket
id|x_ID
)braket
dot
id|pl
suffix:semicolon
id|ScsiStatus
op_assign
id|pFcpStatus-&gt;fcp_status
op_rshift
l_int|24
suffix:semicolon
singleline_comment|// If the command is a SCSI Read/Write type, we don&squot;t tolerate
singleline_comment|// count errors of any kind; assume the count error is due to
singleline_comment|// a dropped frame and ask for retry...
r_if
c_cond
(paren
(paren
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;cmnd
(braket
l_int|0
)braket
op_eq
l_int|0x8
)paren
op_logical_or
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;cmnd
(braket
l_int|0
)braket
op_eq
l_int|0x28
)paren
op_logical_or
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;cmnd
(braket
l_int|0
)braket
op_eq
l_int|0xA
)paren
op_logical_or
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;cmnd
(braket
l_int|0
)braket
op_eq
l_int|0x2A
)paren
)paren
op_logical_and
id|ScsiStatus
op_eq
l_int|0
)paren
(brace
singleline_comment|// ask for retry
multiline_comment|/*          printk(&quot;COUNT_ERROR retry, x_ID %Xh, status %Xh, Cmnd %p&bslash;n&quot;, &n;            x_ID, Exchanges-&gt;fcExchange[ x_ID ].status,&n;            Exchanges-&gt;fcExchange[ x_ID ].Cmnd);*/
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;result
op_assign
(paren
id|DID_SOFT_ERROR
op_lshift
l_int|16
)paren
suffix:semicolon
)brace
r_else
singleline_comment|// need more analysis
(brace
id|cpqfcTSCheckandSnoopFCP
c_func
(paren
id|fcChip
comma
id|x_ID
)paren
suffix:semicolon
singleline_comment|// (will set -&gt;result)
)brace
)brace
singleline_comment|// default: NOTE! We don&squot;t ever want to get here.  Getting here
singleline_comment|// implies something new is happening that we&squot;ve never had a test
singleline_comment|// case for.  Need code maintenance!  Return &quot;ERROR&quot;
r_else
(brace
r_int
r_int
id|stat
op_assign
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;DEFAULT result %Xh, x_ID %Xh, Cmnd %p&quot;
comma
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
comma
id|x_ID
comma
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|INVALID_ARGS
)paren
id|printk
c_func
(paren
l_string|&quot; INVALID_ARGS &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|LNKDWN_OSLS
)paren
id|printk
c_func
(paren
l_string|&quot; LNKDWN_OSLS &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|LNKDWN_LASER
)paren
id|printk
c_func
(paren
l_string|&quot; LNKDWN_LASER &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|OUTQUE_FULL
)paren
id|printk
c_func
(paren
l_string|&quot; OUTQUE_FULL &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|DRIVERQ_FULL
)paren
id|printk
c_func
(paren
l_string|&quot; DRIVERQ_FULL &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|SEST_FULL
)paren
id|printk
c_func
(paren
l_string|&quot; SEST_FULL &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|BAD_ALPA
)paren
id|printk
c_func
(paren
l_string|&quot; BAD_ALPA &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|OVERFLOW
)paren
id|printk
c_func
(paren
l_string|&quot; OVERFLOW &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|COUNT_ERROR
)paren
id|printk
c_func
(paren
l_string|&quot; COUNT_ERROR &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|LINKFAIL_RX
)paren
id|printk
c_func
(paren
l_string|&quot; LINKFAIL_RX &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|ABORTSEQ_NOTIFY
)paren
id|printk
c_func
(paren
l_string|&quot; ABORTSEQ_NOTIFY &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|LINKFAIL_TX
)paren
id|printk
c_func
(paren
l_string|&quot; LINKFAIL_TX &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|HOSTPROG_ERR
)paren
id|printk
c_func
(paren
l_string|&quot; HOSTPROG_ERR &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|FRAME_TO
)paren
id|printk
c_func
(paren
l_string|&quot; FRAME_TO &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|INV_ENTRY
)paren
id|printk
c_func
(paren
l_string|&quot; INV_ENTRY &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|SESTPROG_ERR
)paren
id|printk
c_func
(paren
l_string|&quot; SESTPROG_ERR &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|OUTBOUND_TIMEOUT
)paren
id|printk
c_func
(paren
l_string|&quot; OUTBOUND_TIMEOUT &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|INITIATOR_ABORT
)paren
id|printk
c_func
(paren
l_string|&quot; INITIATOR_ABORT &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|MEMPOOL_FAIL
)paren
id|printk
c_func
(paren
l_string|&quot; MEMPOOL_FAIL &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|FC2_TIMEOUT
)paren
id|printk
c_func
(paren
l_string|&quot; FC2_TIMEOUT &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|TARGET_ABORT
)paren
id|printk
c_func
(paren
l_string|&quot; TARGET_ABORT &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|EXCHANGE_QUEUED
)paren
id|printk
c_func
(paren
l_string|&quot; EXCHANGE_QUEUED &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|PORTID_CHANGED
)paren
id|printk
c_func
(paren
l_string|&quot; PORTID_CHANGED &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|DEVICE_REMOVED
)paren
id|printk
c_func
(paren
l_string|&quot; DEVICE_REMOVED &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|SFQ_FRAME
)paren
id|printk
c_func
(paren
l_string|&quot; SFQ_FRAME &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;result
op_assign
(paren
id|DID_ERROR
op_lshift
l_int|16
)paren
suffix:semicolon
)brace
)brace
r_else
singleline_comment|// definitely no Tach problem, but perhaps an FCP problem
(brace
singleline_comment|// set FCP Link statistic
id|fcChip-&gt;fcStats.ok
op_increment
suffix:semicolon
id|cpqfcTSCheckandSnoopFCP
c_func
(paren
id|fcChip
comma
id|x_ID
)paren
suffix:semicolon
singleline_comment|// (will set -&gt;result)    
)brace
id|cpqfc_pci_unmap
c_func
(paren
id|pcidev
comma
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd
comma
id|fcChip
comma
id|x_ID
)paren
suffix:semicolon
singleline_comment|// undo DMA mappings.
id|already_unmapped
op_assign
l_int|1
suffix:semicolon
singleline_comment|// OK, we&squot;ve set the Scsi &quot;-&gt;result&quot; field, so proceed with calling
singleline_comment|// Linux Scsi &quot;done&quot; (if not NULL), and free any kernel memory we
singleline_comment|// may have allocated for the exchange.
id|PCI_TRACEO
c_func
(paren
(paren
id|ULONG
)paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd
comma
l_int|0xAC
)paren
suffix:semicolon
singleline_comment|// complete the command back to upper Scsi drivers
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;scsi_done
op_ne
l_int|NULL
)paren
(brace
singleline_comment|// Calling &quot;done&quot; on an Linux _abort() aborted
singleline_comment|// Cmnd causes a kernel panic trying to re-free mem.
singleline_comment|// Actually, we shouldn&squot;t do anything with an _abort CMND
r_if
c_cond
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;result
op_ne
(paren
id|DID_ABORT
op_lshift
l_int|16
)paren
)paren
(brace
id|PCI_TRACE
c_func
(paren
l_int|0xAC
)paren
id|call_scsi_done
c_func
(paren
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd
)paren
suffix:semicolon
)brace
r_else
(brace
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;SCp.sent_command
op_assign
l_int|0
suffix:semicolon
singleline_comment|//&t;printk(&quot; not calling scsi_done on x_ID %Xh, Cmnd %p&bslash;n&quot;,
singleline_comment|//&t;&t;&t;x_ID, Exchanges-&gt;fcExchange[ x_ID ].Cmnd);
)brace
)brace
r_else
(brace
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;SCp.sent_command
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; x_ID %Xh, type %Xh, Cdb0 %Xh&bslash;n&quot;
comma
id|x_ID
comma
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|type
comma
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd-&gt;cmnd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; cpqfcTS: Null scsi_done function pointer!&bslash;n&quot;
)paren
suffix:semicolon
)brace
singleline_comment|// Now, clean up non-Scsi_Cmnd items...
id|CleanUpSestResources
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|already_unmapped
)paren
id|cpqfc_pci_unmap
c_func
(paren
id|pcidev
comma
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd
comma
id|fcChip
comma
id|x_ID
)paren
suffix:semicolon
singleline_comment|// undo DMA mappings.
singleline_comment|// Was an Extended Scatter/Gather page allocated?  We know
singleline_comment|// this by checking DWORD 4, bit 31 (&quot;LOC&quot;) of SEST entry
r_if
c_cond
(paren
op_logical_neg
(paren
id|fcChip-&gt;SEST-&gt;u
(braket
id|x_ID
)braket
dot
id|IWE.Buff_Off
op_amp
l_int|0x80000000
)paren
)paren
(brace
id|PSGPAGES
id|p
comma
id|next
suffix:semicolon
singleline_comment|// extended S/G list was used -- Free the allocated ext. S/G pages
r_for
c_loop
(paren
id|p
op_assign
id|fcChip-&gt;SEST-&gt;sgPages
(braket
id|x_ID
)braket
suffix:semicolon
id|p
op_ne
l_int|NULL
suffix:semicolon
id|p
op_assign
id|next
)paren
(brace
id|next
op_assign
id|p-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
id|fcChip-&gt;SEST-&gt;sgPages
(braket
id|x_ID
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd
op_assign
l_int|NULL
suffix:semicolon
)brace
singleline_comment|// Done with FCP (SEST) exchanges
singleline_comment|// the remaining logic is common to ALL Exchanges: 
singleline_comment|// FCP(SEST) and LinkServ.
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|type
op_assign
l_int|0
suffix:semicolon
singleline_comment|// there -- FREE!  
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|status
op_assign
l_int|0
suffix:semicolon
id|PCI_TRACEO
c_func
(paren
id|x_ID
comma
l_int|0xAC
)paren
r_return
suffix:semicolon
)brace
singleline_comment|// (END of CompleteExchange function)
singleline_comment|// Unfortunately, we must snoop all command completions in
singleline_comment|// order to manipulate certain return fields, and take note of
singleline_comment|// device types, etc., to facilitate the Fibre-Channel to SCSI
singleline_comment|// &quot;mapping&quot;.  
singleline_comment|// (Watch for BIG Endian confusion on some payload fields)
DECL|function|cpqfcTSCheckandSnoopFCP
r_void
id|cpqfcTSCheckandSnoopFCP
c_func
(paren
id|PTACHYON
id|fcChip
comma
id|ULONG
id|x_ID
)paren
(brace
id|FC_EXCHANGES
op_star
id|Exchanges
op_assign
id|fcChip-&gt;Exchanges
suffix:semicolon
id|Scsi_Cmnd
op_star
id|Cmnd
op_assign
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|Cmnd
suffix:semicolon
id|FCP_STATUS_RESPONSE
op_star
id|pFcpStatus
op_assign
(paren
id|PFCP_STATUS_RESPONSE
)paren
op_amp
id|fcChip-&gt;SEST-&gt;RspHDR
(braket
id|x_ID
)braket
dot
id|pl
suffix:semicolon
id|UCHAR
id|ScsiStatus
suffix:semicolon
id|ScsiStatus
op_assign
id|pFcpStatus-&gt;fcp_status
op_rshift
l_int|24
suffix:semicolon
macro_line|#ifdef FCP_COMPLETION_DBG
id|printk
c_func
(paren
l_string|&quot;ScsiStatus = 0x%X&bslash;n&quot;
comma
id|ScsiStatus
)paren
suffix:semicolon
macro_line|#endif&t;
singleline_comment|// First, check FCP status
r_if
c_cond
(paren
id|pFcpStatus-&gt;fcp_status
op_amp
id|FCP_RSP_LEN_VALID
)paren
(brace
singleline_comment|// check response code (RSP_CODE) -- most popular is bad len
singleline_comment|// 1st 4 bytes of rsp info -- only byte 3 interesting
r_if
c_cond
(paren
id|pFcpStatus-&gt;fcp_rsp_info
op_amp
id|FCP_DATA_LEN_NOT_BURST_LEN
)paren
(brace
singleline_comment|// do we EVER get here?
id|printk
c_func
(paren
l_string|&quot;cpqfcTS: FCP data len not burst len, x_ID %Xh&bslash;n&quot;
comma
id|x_ID
)paren
suffix:semicolon
)brace
)brace
singleline_comment|// for now, go by the ScsiStatus, and manipulate certain
singleline_comment|// commands when necessary...
r_if
c_cond
(paren
id|ScsiStatus
op_eq
l_int|0
)paren
singleline_comment|// SCSI status byte &quot;good&quot;?
(brace
id|Cmnd-&gt;result
op_assign
l_int|0
suffix:semicolon
singleline_comment|// everything&squot;s OK
r_if
c_cond
(paren
(paren
id|Cmnd-&gt;cmnd
(braket
l_int|0
)braket
op_eq
id|INQUIRY
)paren
)paren
(brace
id|UCHAR
op_star
id|InquiryData
op_assign
id|Cmnd-&gt;request_buffer
suffix:semicolon
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
suffix:semicolon
singleline_comment|// We need to manipulate INQUIRY
singleline_comment|// strings for COMPAQ RAID controllers to force
singleline_comment|// Linux to scan additional LUNs.  Namely, set
singleline_comment|// the Inquiry string byte 2 (ANSI-approved version)
singleline_comment|// to 2.
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
op_amp
id|InquiryData
(braket
l_int|8
)braket
comma
l_string|&quot;COMPAQ&quot;
comma
l_int|6
)paren
)paren
(brace
id|InquiryData
(braket
l_int|2
)braket
op_assign
l_int|0x2
suffix:semicolon
singleline_comment|// claim SCSI-2 compliance,
singleline_comment|// so multiple LUNs may be scanned.
singleline_comment|// (no SCSI-2 problems known in CPQ)
)brace
singleline_comment|// snoop the Inquiry to detect Disk, Tape, etc. type
singleline_comment|// (search linked list for the port_id we sent INQUIRY to)
id|pLoggedInPort
op_assign
id|fcFindLoggedInPort
c_func
(paren
id|fcChip
comma
l_int|NULL
comma
singleline_comment|// DON&squot;T search Scsi Nexus (we will set it)
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|fchs.d_id
op_amp
l_int|0xFFFFFF
comma
l_int|NULL
comma
singleline_comment|// DON&squot;T search linked list for FC WWN
l_int|NULL
)paren
suffix:semicolon
singleline_comment|// DON&squot;T care about end of list
r_if
c_cond
(paren
id|pLoggedInPort
)paren
(brace
id|pLoggedInPort-&gt;ScsiNexus.InqDeviceType
op_assign
id|InquiryData
(braket
l_int|0
)braket
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;cpqfcTS: can&squot;t find LoggedIn FC port %06X for INQUIRY&bslash;n&quot;
comma
id|Exchanges-&gt;fcExchange
(braket
id|x_ID
)braket
dot
id|fchs.d_id
op_amp
l_int|0xFFFFFF
)paren
suffix:semicolon
)brace
)brace
)brace
singleline_comment|// Scsi Status not good -- pass it back to caller 
r_else
(brace
id|Cmnd-&gt;result
op_assign
id|ScsiStatus
suffix:semicolon
singleline_comment|// SCSI status byte is 1st
singleline_comment|// check for valid &quot;sense&quot; data
r_if
c_cond
(paren
id|pFcpStatus-&gt;fcp_status
op_amp
id|FCP_SNS_LEN_VALID
)paren
(brace
singleline_comment|// limit Scsi Sense field length!
r_int
id|SenseLen
op_assign
id|pFcpStatus-&gt;fcp_sns_len
op_rshift
l_int|24
suffix:semicolon
singleline_comment|// (BigEndian) lower byte
id|SenseLen
op_assign
id|SenseLen
OG
r_sizeof
(paren
id|Cmnd-&gt;sense_buffer
)paren
ques
c_cond
r_sizeof
(paren
id|Cmnd-&gt;sense_buffer
)paren
suffix:colon
id|SenseLen
suffix:semicolon
macro_line|#ifdef FCP_COMPLETION_DBG&t;    
id|printk
c_func
(paren
l_string|&quot;copy sense_buffer %p, len %d, result %Xh&bslash;n&quot;
comma
id|Cmnd-&gt;sense_buffer
comma
id|SenseLen
comma
id|Cmnd-&gt;result
)paren
suffix:semicolon
macro_line|#endif&t;  
singleline_comment|// NOTE: There is some dispute over the FCP response
singleline_comment|// format.  Most FC devices assume that FCP_RSP_INFO
singleline_comment|// is 8 bytes long, in spite of the fact that FCP_RSP_LEN
singleline_comment|// is (virtually) always 0 and the field is &quot;invalid&quot;.  
singleline_comment|// Some other devices assume that
singleline_comment|// the FCP_SNS_INFO begins after FCP_RSP_LEN bytes (i.e. 0)
singleline_comment|// when the FCP_RSP is invalid (this almost appears to be
singleline_comment|// one of those &quot;religious&quot; issues).
singleline_comment|// Consequently, we test the usual position of FCP_SNS_INFO
singleline_comment|// for 7Xh, since the SCSI sense format says the first
singleline_comment|// byte (&quot;error code&quot;) should be 0x70 or 0x71.  In practice,
singleline_comment|// we find that every device does in fact have 0x70 or 0x71
singleline_comment|// in the first byte position, so this test works for all
singleline_comment|// FC devices.  
singleline_comment|// (This logic is especially effective for the CPQ/DEC HSG80
singleline_comment|// &amp; HSG60 controllers).
r_if
c_cond
(paren
(paren
id|pFcpStatus-&gt;fcp_sns_info
(braket
l_int|0
)braket
op_amp
l_int|0x70
)paren
op_eq
l_int|0x70
)paren
(brace
id|memcpy
c_func
(paren
id|Cmnd-&gt;sense_buffer
comma
op_amp
id|pFcpStatus-&gt;fcp_sns_info
(braket
l_int|0
)braket
comma
id|SenseLen
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_char
op_star
id|sbPtr
op_assign
(paren
r_int
r_char
op_star
)paren
op_amp
id|pFcpStatus-&gt;fcp_sns_info
(braket
l_int|0
)braket
suffix:semicolon
id|sbPtr
op_sub_assign
l_int|8
suffix:semicolon
singleline_comment|// back up 8 bytes hoping to find the
singleline_comment|// start of the sense buffer
id|memcpy
c_func
(paren
id|Cmnd-&gt;sense_buffer
comma
id|sbPtr
comma
id|SenseLen
)paren
suffix:semicolon
)brace
singleline_comment|// in the special case of Device Reset, tell upper layer
singleline_comment|// to immediately retry (with SOFT_ERROR status)
singleline_comment|// look for Sense Key Unit Attention (0x6) with ASC Device
singleline_comment|// Reset (0x29)
singleline_comment|//&t;    printk(&quot;SenseLen %d, Key = 0x%X, ASC = 0x%X&bslash;n&quot;,
singleline_comment|//&t;&t;    SenseLen, Cmnd-&gt;sense_buffer[2], 
singleline_comment|//                   Cmnd-&gt;sense_buffer[12]);
r_if
c_cond
(paren
(paren
(paren
id|Cmnd-&gt;sense_buffer
(braket
l_int|2
)braket
op_amp
l_int|0xF
)paren
op_eq
l_int|0x6
)paren
op_logical_and
(paren
id|Cmnd-&gt;sense_buffer
(braket
l_int|12
)braket
op_eq
l_int|0x29
)paren
)paren
singleline_comment|// Sense Code &quot;reset&quot;
(brace
id|Cmnd-&gt;result
op_or_assign
(paren
id|DID_SOFT_ERROR
op_lshift
l_int|16
)paren
suffix:semicolon
singleline_comment|// &quot;Host&quot; status byte 3rd
)brace
singleline_comment|// check for SenseKey &quot;HARDWARE ERROR&quot;, ASC InternalTargetFailure
r_else
r_if
c_cond
(paren
(paren
(paren
id|Cmnd-&gt;sense_buffer
(braket
l_int|2
)braket
op_amp
l_int|0xF
)paren
op_eq
l_int|0x4
)paren
op_logical_and
singleline_comment|// &quot;hardware error&quot;
(paren
id|Cmnd-&gt;sense_buffer
(braket
l_int|12
)braket
op_eq
l_int|0x44
)paren
)paren
singleline_comment|// Addtl. Sense Code 
(brace
singleline_comment|//        printk(&quot;HARDWARE_ERROR, Channel/Target/Lun %d/%d/%d&bslash;n&quot;,
singleline_comment|//&t;&t;Cmnd-&gt;channel, Cmnd-&gt;target, Cmnd-&gt;lun);
id|Cmnd-&gt;result
op_or_assign
(paren
id|DID_ERROR
op_lshift
l_int|16
)paren
suffix:semicolon
singleline_comment|// &quot;Host&quot; status byte 3rd
)brace
)brace
singleline_comment|// (end of sense len valid)
singleline_comment|// there is no sense data to help out Linux&squot;s Scsi layers...
singleline_comment|// We&squot;ll just return the Scsi status and hope he will &quot;do the 
singleline_comment|// right thing&quot;
r_else
(brace
singleline_comment|// as far as we know, the Scsi status is sufficient
id|Cmnd-&gt;result
op_or_assign
(paren
id|DID_OK
op_lshift
l_int|16
)paren
suffix:semicolon
singleline_comment|// &quot;Host&quot; status byte 3rd
)brace
)brace
)brace
singleline_comment|//PPPPPPPPPPPPPPPPPPPPPPPPP  PAYLOAD  PPPPPPPPP
singleline_comment|// build data PAYLOAD; SCSI FCP_CMND I.U.
singleline_comment|// remember BIG ENDIAN payload - DWord values must be byte-reversed
singleline_comment|// (hence the affinity for byte pointer building).
DECL|function|build_FCP_payload
r_static
r_int
id|build_FCP_payload
c_func
(paren
id|Scsi_Cmnd
op_star
id|Cmnd
comma
id|UCHAR
op_star
id|payload
comma
id|ULONG
id|type
comma
id|ULONG
id|fcp_dl
)paren
(brace
r_int
id|i
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|SCSI_IWE
suffix:colon
r_case
id|SCSI_IRE
suffix:colon
singleline_comment|// 8 bytes FCP_LUN
singleline_comment|// Peripheral Device or Volume Set addressing, and LUN mapping
singleline_comment|// When the FC port was looked up, we copied address mode
singleline_comment|// and any LUN mask to the scratch pad SCp.phase &amp; .mode
op_star
id|payload
op_increment
op_assign
(paren
id|UCHAR
)paren
id|Cmnd-&gt;SCp.phase
suffix:semicolon
singleline_comment|// Now, because of &quot;lun masking&quot; 
singleline_comment|// (aka selective storage presentation),
singleline_comment|// the contiguous Linux Scsi lun number may not match the
singleline_comment|// device&squot;s lun number, so we may have to &quot;map&quot;.  
op_star
id|payload
op_increment
op_assign
(paren
id|UCHAR
)paren
id|Cmnd-&gt;SCp.have_data_in
suffix:semicolon
singleline_comment|// We don&squot;t know of anyone in the FC business using these 
singleline_comment|// extra &quot;levels&quot; of addressing.  In fact, confusion still exists
singleline_comment|// just using the FIRST level... ;-)
op_star
id|payload
op_increment
op_assign
l_int|0
suffix:semicolon
singleline_comment|// 2nd level addressing
op_star
id|payload
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|payload
op_increment
op_assign
l_int|0
suffix:semicolon
singleline_comment|// 3rd level addressing
op_star
id|payload
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|payload
op_increment
op_assign
l_int|0
suffix:semicolon
singleline_comment|// 4th level addressing
op_star
id|payload
op_increment
op_assign
l_int|0
suffix:semicolon
singleline_comment|// 4 bytes Control Field FCP_CNTL
op_star
id|payload
op_increment
op_assign
l_int|0
suffix:semicolon
singleline_comment|// byte 0: (MSB) reserved
op_star
id|payload
op_increment
op_assign
l_int|0
suffix:semicolon
singleline_comment|// byte 1: task codes
singleline_comment|// byte 2: task management flags
singleline_comment|// another &quot;use&quot; of the spare field to accomplish TDR
singleline_comment|// note combination needed
r_if
c_cond
(paren
(paren
id|Cmnd-&gt;cmnd
(braket
l_int|0
)braket
op_eq
id|RELEASE
)paren
op_logical_and
(paren
id|Cmnd-&gt;SCp.buffers_residual
op_eq
id|FCP_TARGET_RESET
)paren
)paren
(brace
id|Cmnd-&gt;cmnd
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
singleline_comment|// issue &quot;Test Unit Ready&quot; for TDR
op_star
id|payload
op_increment
op_assign
l_int|0x20
suffix:semicolon
singleline_comment|// target device reset bit
)brace
r_else
op_star
id|payload
op_increment
op_assign
l_int|0
suffix:semicolon
singleline_comment|// no TDR
singleline_comment|// byte 3: (LSB) execution management codes
singleline_comment|// bit 0 write, bit 1 read (don&squot;t set together)
r_if
c_cond
(paren
id|fcp_dl
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
id|SCSI_IWE
)paren
(brace
singleline_comment|// WRITE
op_star
id|payload
op_increment
op_assign
l_int|1
suffix:semicolon
)brace
r_else
singleline_comment|// READ
op_star
id|payload
op_increment
op_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// On some devices, if RD or WR bits are set,
singleline_comment|// and fcp_dl is 0, they will generate an error on the command.
singleline_comment|// (i.e., if direction is specified, they insist on a length).
op_star
id|payload
op_increment
op_assign
l_int|0
suffix:semicolon
singleline_comment|// no data (necessary for CPQ)
)brace
singleline_comment|// NOTE: clean this up if/when MAX_COMMAND_SIZE is increased to 16
singleline_comment|// FCP_CDB allows 16 byte SCSI command descriptor blk;
singleline_comment|// Linux SCSI CDB array is MAX_COMMAND_SIZE (12 at this time...)
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|Cmnd-&gt;cmd_len
)paren
op_logical_and
id|i
OL
id|MAX_COMMAND_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
op_star
id|payload
op_increment
op_assign
id|Cmnd-&gt;cmnd
(braket
id|i
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Cmnd-&gt;cmd_len
op_eq
l_int|16
)paren
(brace
id|memcpy
c_func
(paren
id|payload
comma
op_amp
id|Cmnd-&gt;SCp.buffers_residual
comma
l_int|4
)paren
suffix:semicolon
)brace
id|payload
op_add_assign
(paren
l_int|16
op_minus
id|i
)paren
suffix:semicolon
singleline_comment|// FCP_DL is largest number of expected data bytes
singleline_comment|// per CDB (i.e. read/write command)
op_star
id|payload
op_increment
op_assign
(paren
id|UCHAR
)paren
(paren
id|fcp_dl
op_rshift
l_int|24
)paren
suffix:semicolon
singleline_comment|// (MSB) 8 bytes data len FCP_DL
op_star
id|payload
op_increment
op_assign
(paren
id|UCHAR
)paren
(paren
id|fcp_dl
op_rshift
l_int|16
)paren
suffix:semicolon
op_star
id|payload
op_increment
op_assign
(paren
id|UCHAR
)paren
(paren
id|fcp_dl
op_rshift
l_int|8
)paren
suffix:semicolon
op_star
id|payload
op_increment
op_assign
(paren
id|UCHAR
)paren
id|fcp_dl
suffix:semicolon
singleline_comment|// (LSB)
r_break
suffix:semicolon
r_case
id|SCSI_TWE
suffix:colon
singleline_comment|// need FCP_XFER_RDY
op_star
id|payload
op_increment
op_assign
l_int|0
suffix:semicolon
singleline_comment|// (4 bytes) DATA_RO (MSB byte 0)
op_star
id|payload
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|payload
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|payload
op_increment
op_assign
l_int|0
suffix:semicolon
singleline_comment|// LSB (byte 3)
singleline_comment|// (4 bytes) BURST_LEN
singleline_comment|// size of following FCP_DATA payload
op_star
id|payload
op_increment
op_assign
(paren
id|UCHAR
)paren
(paren
id|fcp_dl
op_rshift
l_int|24
)paren
suffix:semicolon
singleline_comment|// (MSB) 8 bytes data len FCP_DL
op_star
id|payload
op_increment
op_assign
(paren
id|UCHAR
)paren
(paren
id|fcp_dl
op_rshift
l_int|16
)paren
suffix:semicolon
op_star
id|payload
op_increment
op_assign
(paren
id|UCHAR
)paren
(paren
id|fcp_dl
op_rshift
l_int|8
)paren
suffix:semicolon
op_star
id|payload
op_increment
op_assign
(paren
id|UCHAR
)paren
id|fcp_dl
suffix:semicolon
singleline_comment|// (LSB)
singleline_comment|// 4 bytes RESERVED
op_star
id|payload
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|payload
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|payload
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|payload
op_increment
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
