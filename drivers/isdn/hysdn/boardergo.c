multiline_comment|/* $Id: boardergo.c,v 1.5.6.7 2001/11/06 21:58:19 kai Exp $&n; *&n; * Linux driver for HYSDN cards, specific routines for ergo type boards.&n; *&n; * Author    Werner Cornelius (werner@titro.de) for Hypercope GmbH&n; * Copyright 1999 by Werner Cornelius (werner@titro.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * As all Linux supported cards Champ2, Ergo and Metro2/4 use the same&n; * DPRAM interface and layout with only minor differences all related&n; * stuff is done here, not in separate modules.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;hysdn_defs.h&quot;
macro_line|#include &quot;boardergo.h&quot;
DECL|macro|byteout
mdefine_line|#define byteout(addr,val) outb(val,addr)
DECL|macro|bytein
mdefine_line|#define bytein(addr) inb(addr)
multiline_comment|/***************************************************/
multiline_comment|/* The cards interrupt handler. Called from system */
multiline_comment|/***************************************************/
r_static
r_void
DECL|function|ergo_interrupt
id|ergo_interrupt
c_func
(paren
r_int
id|intno
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|hysdn_card
op_star
id|card
op_assign
id|dev_id
suffix:semicolon
multiline_comment|/* parameter from irq */
id|tErgDpram
op_star
id|dpr
suffix:semicolon
id|ulong
id|flags
suffix:semicolon
id|uchar
r_volatile
id|b
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
r_return
suffix:semicolon
multiline_comment|/* error -&gt; spurious interrupt */
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;irq_enabled
)paren
r_return
suffix:semicolon
multiline_comment|/* other device interrupting or irq switched off */
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* no further irqs allowed */
r_if
c_cond
(paren
op_logical_neg
(paren
id|bytein
c_func
(paren
id|card-&gt;iobase
op_plus
id|PCI9050_INTR_REG
)paren
op_amp
id|PCI9050_INTR_REG_STAT1
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* restore old state */
r_return
suffix:semicolon
multiline_comment|/* no interrupt requested by E1 */
)brace
multiline_comment|/* clear any pending ints on the board */
id|dpr
op_assign
id|card-&gt;dpram
suffix:semicolon
id|b
op_assign
id|dpr-&gt;ToPcInt
suffix:semicolon
multiline_comment|/* clear for ergo */
id|b
op_or_assign
id|dpr-&gt;ToPcIntMetro
suffix:semicolon
multiline_comment|/* same for metro */
id|b
op_or_assign
id|dpr-&gt;ToHyInt
suffix:semicolon
multiline_comment|/* and for champ */
multiline_comment|/* start kernel task immediately after leaving all interrupts */
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;hw_lock
)paren
(brace
id|queue_task
c_func
(paren
op_amp
id|card-&gt;irq_queue
comma
op_amp
id|tq_immediate
)paren
suffix:semicolon
id|mark_bh
c_func
(paren
id|IMMEDIATE_BH
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* ergo_interrupt */
multiline_comment|/******************************************************************************/
multiline_comment|/* ergo_irq_bh is the function called by the immediate kernel task list after */
multiline_comment|/* being activated with queue_task and no interrupts active. This task is the */
multiline_comment|/* only one handling data transfer from or to the card after booting. The task */
multiline_comment|/* may be queued from everywhere (interrupts included).                       */
multiline_comment|/******************************************************************************/
r_static
r_void
DECL|function|ergo_irq_bh
id|ergo_irq_bh
c_func
(paren
id|hysdn_card
op_star
id|card
)paren
(brace
id|tErgDpram
op_star
id|dpr
suffix:semicolon
r_int
id|again
suffix:semicolon
id|ulong
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;state
op_ne
id|CARD_STATE_RUN
)paren
r_return
suffix:semicolon
multiline_comment|/* invalid call */
id|dpr
op_assign
id|card-&gt;dpram
suffix:semicolon
multiline_comment|/* point to DPRAM */
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;hw_lock
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* hardware currently unavailable */
r_return
suffix:semicolon
)brace
id|card-&gt;hw_lock
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* we now lock the hardware */
r_do
(brace
id|sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* reenable other ints */
id|again
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* assume loop not to be repeated */
r_if
c_cond
(paren
op_logical_neg
id|dpr-&gt;ToHyFlag
)paren
(brace
multiline_comment|/* we are able to send a buffer */
r_if
c_cond
(paren
id|hysdn_sched_tx
c_func
(paren
id|card
comma
id|dpr-&gt;ToHyBuf
comma
op_amp
id|dpr-&gt;ToHySize
comma
op_amp
id|dpr-&gt;ToHyChannel
comma
id|ERG_TO_HY_BUF_SIZE
)paren
)paren
(brace
id|dpr-&gt;ToHyFlag
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* enable tx */
id|again
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* restart loop */
)brace
)brace
multiline_comment|/* we are able to send a buffer */
r_if
c_cond
(paren
id|dpr-&gt;ToPcFlag
)paren
(brace
multiline_comment|/* a message has arrived for us, handle it */
r_if
c_cond
(paren
id|hysdn_sched_rx
c_func
(paren
id|card
comma
id|dpr-&gt;ToPcBuf
comma
id|dpr-&gt;ToPcSize
comma
id|dpr-&gt;ToPcChannel
)paren
)paren
(brace
id|dpr-&gt;ToPcFlag
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* we worked the data */
id|again
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* restart loop */
)brace
)brace
multiline_comment|/* a message has arrived for us */
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* no further ints */
r_if
c_cond
(paren
id|again
)paren
(brace
id|dpr-&gt;ToHyInt
op_assign
l_int|1
suffix:semicolon
id|dpr-&gt;ToPcInt
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* interrupt to E1 for all cards */
)brace
r_else
id|card-&gt;hw_lock
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* free hardware again */
)brace
r_while
c_loop
(paren
id|again
)paren
suffix:semicolon
multiline_comment|/* until nothing more to do */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* ergo_irq_bh */
multiline_comment|/*********************************************************/
multiline_comment|/* stop the card (hardware reset) and disable interrupts */
multiline_comment|/*********************************************************/
r_static
r_void
DECL|function|ergo_stopcard
id|ergo_stopcard
c_func
(paren
id|hysdn_card
op_star
id|card
)paren
(brace
id|ulong
id|flags
suffix:semicolon
id|uchar
id|val
suffix:semicolon
id|hysdn_net_release
c_func
(paren
id|card
)paren
suffix:semicolon
multiline_comment|/* first release the net device if existing */
macro_line|#ifdef CONFIG_HYSDN_CAPI
id|hycapi_capi_stop
c_func
(paren
id|card
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_HYSDN_CAPI */
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|val
op_assign
id|bytein
c_func
(paren
id|card-&gt;iobase
op_plus
id|PCI9050_INTR_REG
)paren
suffix:semicolon
multiline_comment|/* get actual value */
id|val
op_and_assign
op_complement
(paren
id|PCI9050_INTR_REG_ENPCI
op_or
id|PCI9050_INTR_REG_EN1
)paren
suffix:semicolon
multiline_comment|/* mask irq */
id|byteout
c_func
(paren
id|card-&gt;iobase
op_plus
id|PCI9050_INTR_REG
comma
id|val
)paren
suffix:semicolon
id|card-&gt;irq_enabled
op_assign
l_int|0
suffix:semicolon
id|byteout
c_func
(paren
id|card-&gt;iobase
op_plus
id|PCI9050_USER_IO
comma
id|PCI9050_E1_RESET
)paren
suffix:semicolon
multiline_comment|/* reset E1 processor */
id|card-&gt;state
op_assign
id|CARD_STATE_UNUSED
suffix:semicolon
id|card-&gt;err_log_state
op_assign
id|ERRLOG_STATE_OFF
suffix:semicolon
multiline_comment|/* currently no log active */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* ergo_stopcard */
multiline_comment|/**************************************************************************/
multiline_comment|/* enable or disable the cards error log. The event is queued if possible */
multiline_comment|/**************************************************************************/
r_static
r_void
DECL|function|ergo_set_errlog_state
id|ergo_set_errlog_state
c_func
(paren
id|hysdn_card
op_star
id|card
comma
r_int
id|on
)paren
(brace
id|ulong
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;state
op_ne
id|CARD_STATE_RUN
)paren
(brace
id|card-&gt;err_log_state
op_assign
id|ERRLOG_STATE_OFF
suffix:semicolon
multiline_comment|/* must be off */
r_return
suffix:semicolon
)brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|card-&gt;err_log_state
op_eq
id|ERRLOG_STATE_OFF
)paren
op_logical_and
op_logical_neg
id|on
)paren
op_logical_or
(paren
(paren
id|card-&gt;err_log_state
op_eq
id|ERRLOG_STATE_ON
)paren
op_logical_and
id|on
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* nothing to do */
)brace
r_if
c_cond
(paren
id|on
)paren
id|card-&gt;err_log_state
op_assign
id|ERRLOG_STATE_START
suffix:semicolon
multiline_comment|/* request start */
r_else
id|card-&gt;err_log_state
op_assign
id|ERRLOG_STATE_STOP
suffix:semicolon
multiline_comment|/* request stop */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|queue_task
c_func
(paren
op_amp
id|card-&gt;irq_queue
comma
op_amp
id|tq_immediate
)paren
suffix:semicolon
id|mark_bh
c_func
(paren
id|IMMEDIATE_BH
)paren
suffix:semicolon
)brace
multiline_comment|/* ergo_set_errlog_state */
multiline_comment|/******************************************/
multiline_comment|/* test the cards RAM and return 0 if ok. */
multiline_comment|/******************************************/
DECL|variable|TestText
r_static
r_const
r_char
id|TestText
(braket
l_int|36
)braket
op_assign
l_string|&quot;This Message is filler, why read it&quot;
suffix:semicolon
r_static
r_int
DECL|function|ergo_testram
id|ergo_testram
c_func
(paren
id|hysdn_card
op_star
id|card
)paren
(brace
id|tErgDpram
op_star
id|dpr
op_assign
id|card-&gt;dpram
suffix:semicolon
id|memset
c_func
(paren
id|dpr-&gt;TrapTable
comma
l_int|0
comma
r_sizeof
(paren
id|dpr-&gt;TrapTable
)paren
)paren
suffix:semicolon
multiline_comment|/* clear all Traps */
id|dpr-&gt;ToHyInt
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* E1 INTR state forced */
id|memcpy
c_func
(paren
op_amp
id|dpr-&gt;ToHyBuf
(braket
id|ERG_TO_HY_BUF_SIZE
op_minus
r_sizeof
(paren
id|TestText
)paren
)braket
comma
id|TestText
comma
r_sizeof
(paren
id|TestText
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|dpr-&gt;ToHyBuf
(braket
id|ERG_TO_HY_BUF_SIZE
op_minus
r_sizeof
(paren
id|TestText
)paren
)braket
comma
id|TestText
comma
r_sizeof
(paren
id|TestText
)paren
)paren
)paren
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|dpr-&gt;ToPcBuf
(braket
id|ERG_TO_PC_BUF_SIZE
op_minus
r_sizeof
(paren
id|TestText
)paren
)braket
comma
id|TestText
comma
r_sizeof
(paren
id|TestText
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|dpr-&gt;ToPcBuf
(braket
id|ERG_TO_PC_BUF_SIZE
op_minus
r_sizeof
(paren
id|TestText
)paren
)braket
comma
id|TestText
comma
r_sizeof
(paren
id|TestText
)paren
)paren
)paren
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* ergo_testram */
multiline_comment|/*****************************************************************************/
multiline_comment|/* this function is intended to write stage 1 boot image to the cards buffer */
multiline_comment|/* this is done in two steps. First the 1024 hi-words are written (offs=0),  */
multiline_comment|/* then the 1024 lo-bytes are written. The remaining DPRAM is cleared, the   */
multiline_comment|/* PCI-write-buffers flushed and the card is taken out of reset.             */
multiline_comment|/* The function then waits for a reaction of the E1 processor or a timeout.  */
multiline_comment|/* Negative return values are interpreted as errors.                         */
multiline_comment|/*****************************************************************************/
r_static
r_int
DECL|function|ergo_writebootimg
id|ergo_writebootimg
c_func
(paren
r_struct
id|HYSDN_CARD
op_star
id|card
comma
id|uchar
op_star
id|buf
comma
id|ulong
id|offs
)paren
(brace
id|uchar
op_star
id|dst
suffix:semicolon
id|tErgDpram
op_star
id|dpram
suffix:semicolon
r_int
id|cnt
op_assign
(paren
id|BOOT_IMG_SIZE
op_rshift
l_int|2
)paren
suffix:semicolon
multiline_comment|/* number of words to move and swap (byte order!) */
r_if
c_cond
(paren
id|card-&gt;debug_flags
op_amp
id|LOG_POF_CARD
)paren
id|hysdn_addlog
c_func
(paren
id|card
comma
l_string|&quot;ERGO: write bootldr offs=0x%lx &quot;
comma
id|offs
)paren
suffix:semicolon
id|dst
op_assign
id|card-&gt;dpram
suffix:semicolon
multiline_comment|/* pointer to start of DPRAM */
id|dst
op_add_assign
(paren
id|offs
op_plus
id|ERG_DPRAM_FILL_SIZE
)paren
suffix:semicolon
multiline_comment|/* offset in the DPRAM */
r_while
c_loop
(paren
id|cnt
op_decrement
)paren
(brace
op_star
id|dst
op_increment
op_assign
op_star
(paren
id|buf
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* high byte */
op_star
id|dst
op_increment
op_assign
op_star
id|buf
suffix:semicolon
multiline_comment|/* low byte */
id|dst
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* point to next longword */
id|buf
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* buffer only filled with words */
)brace
multiline_comment|/* if low words (offs = 2) have been written, clear the rest of the DPRAM, */
multiline_comment|/* flush the PCI-write-buffer and take the E1 out of reset */
r_if
c_cond
(paren
id|offs
)paren
(brace
id|memset
c_func
(paren
id|card-&gt;dpram
comma
l_int|0
comma
id|ERG_DPRAM_FILL_SIZE
)paren
suffix:semicolon
multiline_comment|/* fill the DPRAM still not cleared */
id|dpram
op_assign
id|card-&gt;dpram
suffix:semicolon
multiline_comment|/* get pointer to dpram structure */
id|dpram-&gt;ToHyNoDpramErrLog
op_assign
l_int|0xFF
suffix:semicolon
multiline_comment|/* write a dpram register */
r_while
c_loop
(paren
op_logical_neg
id|dpram-&gt;ToHyNoDpramErrLog
)paren
suffix:semicolon
multiline_comment|/* reread volatile register to flush PCI */
id|byteout
c_func
(paren
id|card-&gt;iobase
op_plus
id|PCI9050_USER_IO
comma
id|PCI9050_E1_RUN
)paren
suffix:semicolon
multiline_comment|/* start E1 processor */
multiline_comment|/* the interrupts are still masked */
id|sti
c_func
(paren
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
(paren
l_int|20
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
multiline_comment|/* Timeout 20ms */
r_if
c_cond
(paren
(paren
(paren
id|tDpramBootSpooler
op_star
)paren
id|card-&gt;dpram
)paren
op_member_access_from_pointer
id|Len
op_ne
id|DPRAM_SPOOLER_DATA_SIZE
)paren
(brace
r_if
c_cond
(paren
id|card-&gt;debug_flags
op_amp
id|LOG_POF_CARD
)paren
id|hysdn_addlog
c_func
(paren
id|card
comma
l_string|&quot;ERGO: write bootldr no answer&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ERR_BOOTIMG_FAIL
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* start_boot_img */
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* successful */
)brace
multiline_comment|/* ergo_writebootimg */
multiline_comment|/********************************************************************************/
multiline_comment|/* ergo_writebootseq writes the buffer containing len bytes to the E1 processor */
multiline_comment|/* using the boot spool mechanism. If everything works fine 0 is returned. In   */
multiline_comment|/* case of errors a negative error value is returned.                           */
multiline_comment|/********************************************************************************/
r_static
r_int
DECL|function|ergo_writebootseq
id|ergo_writebootseq
c_func
(paren
r_struct
id|HYSDN_CARD
op_star
id|card
comma
id|uchar
op_star
id|buf
comma
r_int
id|len
)paren
(brace
id|tDpramBootSpooler
op_star
id|sp
op_assign
(paren
id|tDpramBootSpooler
op_star
)paren
id|card-&gt;dpram
suffix:semicolon
id|uchar
op_star
id|dst
suffix:semicolon
id|uchar
id|buflen
suffix:semicolon
r_int
id|nr_write
suffix:semicolon
id|uchar
id|tmp_rdptr
suffix:semicolon
id|uchar
id|wr_mirror
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;debug_flags
op_amp
id|LOG_POF_CARD
)paren
id|hysdn_addlog
c_func
(paren
id|card
comma
l_string|&quot;ERGO: write boot seq len=%d &quot;
comma
id|len
)paren
suffix:semicolon
id|dst
op_assign
id|sp-&gt;Data
suffix:semicolon
multiline_comment|/* point to data in spool structure */
id|buflen
op_assign
id|sp-&gt;Len
suffix:semicolon
multiline_comment|/* maximum len of spooled data */
id|wr_mirror
op_assign
id|sp-&gt;WrPtr
suffix:semicolon
multiline_comment|/* only once read */
id|sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* try until all bytes written or error */
id|i
op_assign
l_int|0x1000
suffix:semicolon
multiline_comment|/* timeout value */
r_while
c_loop
(paren
id|len
)paren
(brace
multiline_comment|/* first determine the number of bytes that may be buffered */
r_do
(brace
id|tmp_rdptr
op_assign
id|sp-&gt;RdPtr
suffix:semicolon
multiline_comment|/* first read the pointer */
id|i
op_decrement
suffix:semicolon
multiline_comment|/* decrement timeout */
)brace
r_while
c_loop
(paren
id|i
op_logical_and
(paren
id|tmp_rdptr
op_ne
id|sp-&gt;RdPtr
)paren
)paren
suffix:semicolon
multiline_comment|/* wait for stable pointer */
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
(brace
r_if
c_cond
(paren
id|card-&gt;debug_flags
op_amp
id|LOG_POF_CARD
)paren
id|hysdn_addlog
c_func
(paren
id|card
comma
l_string|&quot;ERGO: write boot seq timeout&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ERR_BOOTSEQ_FAIL
)paren
suffix:semicolon
multiline_comment|/* value not stable -&gt; timeout */
)brace
r_if
c_cond
(paren
(paren
id|nr_write
op_assign
id|tmp_rdptr
op_minus
id|wr_mirror
op_minus
l_int|1
)paren
OL
l_int|0
)paren
id|nr_write
op_add_assign
id|buflen
suffix:semicolon
multiline_comment|/* now we got number of free bytes - 1 in buffer */
r_if
c_cond
(paren
op_logical_neg
id|nr_write
)paren
r_continue
suffix:semicolon
multiline_comment|/* no free bytes in buffer */
r_if
c_cond
(paren
id|nr_write
OG
id|len
)paren
id|nr_write
op_assign
id|len
suffix:semicolon
multiline_comment|/* limit if last few bytes */
id|i
op_assign
l_int|0x1000
suffix:semicolon
multiline_comment|/* reset timeout value */
multiline_comment|/* now we know how much bytes we may put in the puffer */
id|len
op_sub_assign
id|nr_write
suffix:semicolon
multiline_comment|/* we savely could adjust len before output */
r_while
c_loop
(paren
id|nr_write
op_decrement
)paren
(brace
op_star
(paren
id|dst
op_plus
id|wr_mirror
)paren
op_assign
op_star
id|buf
op_increment
suffix:semicolon
multiline_comment|/* output one byte */
r_if
c_cond
(paren
op_increment
id|wr_mirror
op_ge
id|buflen
)paren
id|wr_mirror
op_assign
l_int|0
suffix:semicolon
id|sp-&gt;WrPtr
op_assign
id|wr_mirror
suffix:semicolon
multiline_comment|/* announce the next byte to E1 */
)brace
multiline_comment|/* while (nr_write) */
)brace
multiline_comment|/* while (len) */
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* ergo_writebootseq */
multiline_comment|/***********************************************************************************/
multiline_comment|/* ergo_waitpofready waits for a maximum of 10 seconds for the completition of the */
multiline_comment|/* boot process. If the process has been successful 0 is returned otherwise a     */
multiline_comment|/* negative error code is returned.                                                */
multiline_comment|/***********************************************************************************/
r_static
r_int
DECL|function|ergo_waitpofready
id|ergo_waitpofready
c_func
(paren
r_struct
id|HYSDN_CARD
op_star
id|card
)paren
(brace
id|tErgDpram
op_star
id|dpr
op_assign
id|card-&gt;dpram
suffix:semicolon
multiline_comment|/* pointer to DPRAM structure */
r_int
id|timecnt
op_assign
l_int|10000
op_div
l_int|50
suffix:semicolon
multiline_comment|/* timeout is 10 secs max. */
id|ulong
id|flags
suffix:semicolon
r_int
id|msg_size
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;debug_flags
op_amp
id|LOG_POF_CARD
)paren
id|hysdn_addlog
c_func
(paren
id|card
comma
l_string|&quot;ERGO: waiting for pof ready&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|timecnt
op_decrement
)paren
(brace
multiline_comment|/* wait until timeout  */
r_if
c_cond
(paren
id|dpr-&gt;ToPcFlag
)paren
(brace
multiline_comment|/* data has arrived */
r_if
c_cond
(paren
(paren
id|dpr-&gt;ToPcChannel
op_ne
id|CHAN_SYSTEM
)paren
op_logical_or
(paren
id|dpr-&gt;ToPcSize
OL
id|MIN_RDY_MSG_SIZE
)paren
op_logical_or
(paren
id|dpr-&gt;ToPcSize
OG
id|MAX_RDY_MSG_SIZE
)paren
op_logical_or
(paren
(paren
op_star
(paren
id|ulong
op_star
)paren
id|dpr-&gt;ToPcBuf
)paren
op_ne
id|RDY_MAGIC
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* an error occurred */
multiline_comment|/* Check for additional data delivered during SysReady */
id|msg_size
op_assign
id|dpr-&gt;ToPcSize
op_minus
id|RDY_MAGIC_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|msg_size
OG
l_int|0
)paren
r_if
c_cond
(paren
id|EvalSysrTokData
c_func
(paren
id|card
comma
id|dpr-&gt;ToPcBuf
op_plus
id|RDY_MAGIC_SIZE
comma
id|msg_size
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;debug_flags
op_amp
id|LOG_POF_RECORD
)paren
id|hysdn_addlog
c_func
(paren
id|card
comma
l_string|&quot;ERGO: pof boot success&quot;
)paren
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|card-&gt;state
op_assign
id|CARD_STATE_RUN
suffix:semicolon
multiline_comment|/* now card is running */
multiline_comment|/* enable the cards interrupt */
id|byteout
c_func
(paren
id|card-&gt;iobase
op_plus
id|PCI9050_INTR_REG
comma
id|bytein
c_func
(paren
id|card-&gt;iobase
op_plus
id|PCI9050_INTR_REG
)paren
op_or
(paren
id|PCI9050_INTR_REG_ENPCI
op_or
id|PCI9050_INTR_REG_EN1
)paren
)paren
suffix:semicolon
id|card-&gt;irq_enabled
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* we are ready to receive interrupts */
id|dpr-&gt;ToPcFlag
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* reset data indicator */
id|dpr-&gt;ToHyInt
op_assign
l_int|1
suffix:semicolon
id|dpr-&gt;ToPcInt
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* interrupt to E1 for all cards */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|hynet_enable
op_amp
(paren
l_int|1
op_lshift
id|card-&gt;myid
)paren
)paren
op_logical_and
(paren
id|i
op_assign
id|hysdn_net_create
c_func
(paren
id|card
)paren
)paren
)paren
(brace
id|ergo_stopcard
c_func
(paren
id|card
)paren
suffix:semicolon
id|card-&gt;state
op_assign
id|CARD_STATE_BOOTERR
suffix:semicolon
r_return
(paren
id|i
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HYSDN_CAPI
r_if
c_cond
(paren
(paren
id|i
op_assign
id|hycapi_capi_create
c_func
(paren
id|card
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HYSDN: failed to create capi-interface.&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_HYSDN_CAPI */
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* success */
)brace
multiline_comment|/* data has arrived */
id|sti
c_func
(paren
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
(paren
l_int|50
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
multiline_comment|/* Timeout 50ms */
)brace
multiline_comment|/* wait until timeout */
r_if
c_cond
(paren
id|card-&gt;debug_flags
op_amp
id|LOG_POF_CARD
)paren
id|hysdn_addlog
c_func
(paren
id|card
comma
l_string|&quot;ERGO: pof boot ready timeout&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ERR_POF_TIMEOUT
)paren
suffix:semicolon
)brace
multiline_comment|/* ergo_waitpofready */
multiline_comment|/************************************************************************************/
multiline_comment|/* release the cards hardware. Before releasing do a interrupt disable and hardware */
multiline_comment|/* reset. Also unmap dpram.                                                         */
multiline_comment|/* Use only during module release.                                                  */
multiline_comment|/************************************************************************************/
r_static
r_void
DECL|function|ergo_releasehardware
id|ergo_releasehardware
c_func
(paren
id|hysdn_card
op_star
id|card
)paren
(brace
id|ergo_stopcard
c_func
(paren
id|card
)paren
suffix:semicolon
multiline_comment|/* first stop the card if not already done */
id|free_irq
c_func
(paren
id|card-&gt;irq
comma
id|card
)paren
suffix:semicolon
multiline_comment|/* release interrupt */
id|release_region
c_func
(paren
id|card-&gt;iobase
op_plus
id|PCI9050_INTR_REG
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* release all io ports */
id|release_region
c_func
(paren
id|card-&gt;iobase
op_plus
id|PCI9050_USER_IO
comma
l_int|1
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|card-&gt;dpram
)paren
suffix:semicolon
id|card-&gt;dpram
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* release shared mem */
)brace
multiline_comment|/* ergo_releasehardware */
multiline_comment|/*********************************************************************************/
multiline_comment|/* acquire the needed hardware ports and map dpram. If an error occurs a nonzero */
multiline_comment|/* value is returned.                                                            */
multiline_comment|/* Use only during module init.                                                  */
multiline_comment|/*********************************************************************************/
r_int
DECL|function|ergo_inithardware
id|ergo_inithardware
c_func
(paren
id|hysdn_card
op_star
id|card
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|card-&gt;iobase
op_plus
id|PCI9050_INTR_REG
comma
l_int|1
comma
l_string|&quot;HYSDN&quot;
)paren
)paren
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|card-&gt;iobase
op_plus
id|PCI9050_USER_IO
comma
l_int|1
comma
l_string|&quot;HYSDN&quot;
)paren
)paren
(brace
id|release_region
c_func
(paren
id|card-&gt;iobase
op_plus
id|PCI9050_INTR_REG
comma
l_int|1
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* ports already in use */
)brace
id|card-&gt;memend
op_assign
id|card-&gt;membase
op_plus
id|ERG_DPRAM_PAGE_SIZE
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|card-&gt;dpram
op_assign
id|ioremap
c_func
(paren
id|card-&gt;membase
comma
id|ERG_DPRAM_PAGE_SIZE
)paren
)paren
)paren
(brace
id|release_region
c_func
(paren
id|card-&gt;iobase
op_plus
id|PCI9050_INTR_REG
comma
l_int|1
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|card-&gt;iobase
op_plus
id|PCI9050_USER_IO
comma
l_int|1
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|ergo_stopcard
c_func
(paren
id|card
)paren
suffix:semicolon
multiline_comment|/* disable interrupts */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|card-&gt;irq
comma
id|ergo_interrupt
comma
id|SA_SHIRQ
comma
l_string|&quot;HYSDN&quot;
comma
id|card
)paren
)paren
(brace
id|ergo_releasehardware
c_func
(paren
id|card
)paren
suffix:semicolon
multiline_comment|/* return the acquired hardware */
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* success, now setup the function pointers */
id|card-&gt;stopcard
op_assign
id|ergo_stopcard
suffix:semicolon
id|card-&gt;releasehardware
op_assign
id|ergo_releasehardware
suffix:semicolon
id|card-&gt;testram
op_assign
id|ergo_testram
suffix:semicolon
id|card-&gt;writebootimg
op_assign
id|ergo_writebootimg
suffix:semicolon
id|card-&gt;writebootseq
op_assign
id|ergo_writebootseq
suffix:semicolon
id|card-&gt;waitpofready
op_assign
id|ergo_waitpofready
suffix:semicolon
id|card-&gt;set_errlog_state
op_assign
id|ergo_set_errlog_state
suffix:semicolon
id|card-&gt;irq_queue.sync
op_assign
l_int|0
suffix:semicolon
id|card-&gt;irq_queue.data
op_assign
id|card
suffix:semicolon
multiline_comment|/* init task queue for interrupt */
id|card-&gt;irq_queue.routine
op_assign
(paren
r_void
op_star
)paren
(paren
r_void
op_star
)paren
id|ergo_irq_bh
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* ergo_inithardware */
eof
