multiline_comment|/*&n; *  linux/arch/m68k/atari/stmda.c&n; *&n; *  Copyright (C) 1994 Roman Hodek&n; *&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
multiline_comment|/* This file contains some function for controlling the access to the  */
multiline_comment|/* ST-DMA chip that may be shared between devices. Currently we have:  */
multiline_comment|/*   TT:     Floppy and ACSI bus                                       */
multiline_comment|/*   Falcon: Floppy and SCSI                                           */
multiline_comment|/*                                                                     */
multiline_comment|/* The controlling functions set up a wait queue for access to the     */
multiline_comment|/* ST-DMA chip. Callers to stdma_lock() that cannot granted access are */
multiline_comment|/* put onto a queue and waked up later if the owner calls              */
multiline_comment|/* stdma_release(). Additionally, the caller gives his interrupt       */
multiline_comment|/* service routine to stdma_lock().                                    */
multiline_comment|/*                                                                     */
multiline_comment|/* On the Falcon, the IDE bus uses just the ACSI/Floppy interrupt, but */
multiline_comment|/* not the ST-DMA chip itself. So falhd.c needs not to lock the        */
multiline_comment|/* chip. The interrupt is routed to falhd.c if IDE is configured, the  */
multiline_comment|/* model is a Falcon and the interrupt was caused by the HD controller */
multiline_comment|/* (can be determined by looking at its status register).              */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/atari_stdma.h&gt;
macro_line|#include &lt;asm/atariints.h&gt;
macro_line|#include &lt;asm/atarihw.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|variable|stdma_locked
r_static
r_int
id|stdma_locked
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* the semaphore */
multiline_comment|/* int func to be called */
DECL|variable|stdma_isr
r_static
r_void
(paren
op_star
id|stdma_isr
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|stdma_isr_data
r_static
r_void
op_star
id|stdma_isr_data
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* data passed to isr */
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|stdma_wait
)paren
suffix:semicolon
multiline_comment|/* wait queue for ST-DMA */
multiline_comment|/***************************** Prototypes *****************************/
r_static
r_void
id|stdma_int
(paren
r_int
id|irq
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
suffix:semicolon
multiline_comment|/************************* End of Prototypes **************************/
multiline_comment|/*&n; * Function: void stdma_lock( isrfunc isr, void *data )&n; *&n; * Purpose: Tries to get a lock on the ST-DMA chip that is used by more&n; *   then one device driver. Waits on stdma_wait until lock is free.&n; *   stdma_lock() may not be called from an interrupt! You have to&n; *   get the lock in your main routine and release it when your&n; *   request is finished.&n; *&n; * Inputs: A interrupt function that is called until the lock is&n; *   released.&n; *&n; * Returns: nothing&n; *&n; */
DECL|function|stdma_lock
r_void
id|stdma_lock
c_func
(paren
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_void
op_star
id|data
)paren
(brace
r_int
r_int
id|oldflags
suffix:semicolon
id|save_flags
c_func
(paren
id|oldflags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* protect lock */
r_while
c_loop
(paren
id|stdma_locked
)paren
(brace
multiline_comment|/* Since the DMA is used for file system purposes, we&n;&t;&t; have to sleep uninterruptible (there may be locked&n;&t;&t; buffers) */
id|sleep_on
c_func
(paren
op_amp
id|stdma_wait
)paren
suffix:semicolon
)brace
id|stdma_locked
op_assign
l_int|1
suffix:semicolon
id|stdma_isr
op_assign
id|handler
suffix:semicolon
id|stdma_isr_data
op_assign
id|data
suffix:semicolon
id|restore_flags
c_func
(paren
id|oldflags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: void stdma_release( void )&n; *&n; * Purpose: Releases the lock on the ST-DMA chip. &n; *&n; * Inputs: none&n; *&n; * Returns: nothing&n; *&n; */
DECL|function|stdma_release
r_void
id|stdma_release
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|oldflags
suffix:semicolon
id|save_flags
c_func
(paren
id|oldflags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|stdma_locked
op_assign
l_int|0
suffix:semicolon
id|stdma_isr
op_assign
l_int|NULL
suffix:semicolon
id|stdma_isr_data
op_assign
l_int|NULL
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|stdma_wait
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|oldflags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: int stdma_others_waiting( void )&n; *&n; * Purpose: Check if someone waits for the ST-DMA lock.&n; *&n; * Inputs: none&n; *&n; * Returns: 0 if no one is waiting, != 0 otherwise&n; *&n; */
DECL|function|stdma_others_waiting
r_int
id|stdma_others_waiting
c_func
(paren
r_void
)paren
(brace
r_return
id|waitqueue_active
c_func
(paren
op_amp
id|stdma_wait
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: int stdma_islocked( void )&n; *&n; * Purpose: Check if the ST-DMA is currently locked.&n; * Note: Returned status is only valid if ints are disabled while calling and&n; *       as long as they remain disabled.&n; *       If called with ints enabled, status can change only from locked to&n; *       unlocked, because ints may not lock the ST-DMA.&n; *&n; * Inputs: none&n; *&n; * Returns: != 0 if locked, 0 otherwise&n; *&n; */
DECL|function|stdma_islocked
r_int
id|stdma_islocked
c_func
(paren
r_void
)paren
(brace
r_return
id|stdma_locked
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: void stdma_init( void )&n; *&n; * Purpose: Initialize the ST-DMA chip access controlling.&n; *   It sets up the interrupt and its service routine. The int is registered&n; *   as slow int, client devices have to live with that (no problem&n; *   currently).&n; *&n; * Inputs: none&n; *&n; * Return: nothing&n; *&n; */
DECL|function|stdma_init
r_void
id|__init
id|stdma_init
c_func
(paren
r_void
)paren
(brace
id|stdma_isr
op_assign
l_int|NULL
suffix:semicolon
id|request_irq
c_func
(paren
id|IRQ_MFP_FDC
comma
id|stdma_int
comma
id|IRQ_TYPE_SLOW
comma
l_string|&quot;ST-DMA: floppy/ACSI/IDE/Falcon-SCSI&quot;
comma
id|stdma_int
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: void stdma_int()&n; *&n; * Purpose: The interrupt routine for the ST-DMA. It calls the isr&n; *   registered by stdma_lock().&n; *&n; */
DECL|function|stdma_int
r_static
r_void
id|stdma_int
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_if
c_cond
(paren
id|stdma_isr
)paren
(paren
op_star
id|stdma_isr
)paren
(paren
id|irq
comma
id|stdma_isr_data
comma
id|fp
)paren
suffix:semicolon
)brace
eof
