multiline_comment|/*  $Id$&n; *  1993/03/31&n; *  linux/kernel/aha1740.c&n; *&n; *  Based loosely on aha1542.c which is&n; *  Copyright (C) 1992  Tommy Thorn and&n; *  Modified by Eric Youngdale&n; *&n; *  This file is aha1740.c, written and&n; *  Copyright (C) 1992,1993  Brad McLean&n; *  &n; *  Modifications to makecode and queuecommand&n; *  for proper handling of multiple devices courteously&n; *  provided by Michael Weller, March, 1993&n; *&n; *  Multiple adapter support, extended translation detection,&n; *  update to current scsi subsystem changes, proc fs support,&n; *  working (!) module support based on patches from Andreas Arens,&n; *  by Andreas Degert &lt;ad@papyrus.hamburg.com&gt;, 2/1997&n; *&n; * aha1740_makecode may still need even more work&n; * if it doesn&squot;t work for your devices, take a look.&n; *&n; * Reworked for new_eh and new locking by Alan Cox &lt;alan@redhat.com&gt;&n; *&n; * For the avoidance of doubt the &quot;preferred form&quot; of this code is one which&n; * is in an open non patent encumbered format. Where cryptographic key signing&n; * forms part of the process of creating an executable the information&n; * including keys needed to generate an equivalently functional executable&n; * are deemed to be part of the source code.&n; */
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;aha1740.h&quot;
multiline_comment|/* IF YOU ARE HAVING PROBLEMS WITH THIS DRIVER, AND WANT TO WATCH&n;   IT WORK, THEN:&n;#define DEBUG&n;*/
macro_line|#ifdef DEBUG
DECL|macro|DEB
mdefine_line|#define DEB(x) x
macro_line|#else
DECL|macro|DEB
mdefine_line|#define DEB(x)
macro_line|#endif
multiline_comment|/*&n;static const char RCSid[] = &quot;$Header: /usr/src/linux/kernel/blk_drv/scsi/RCS/aha1740.c,v 1.1 1992/07/24 06:27:38 root Exp root $&quot;;&n;*/
DECL|struct|aha1740_hostdata
r_struct
id|aha1740_hostdata
(brace
DECL|member|slot
r_int
r_int
id|slot
suffix:semicolon
DECL|member|translation
r_int
r_int
id|translation
suffix:semicolon
DECL|member|last_ecb_used
r_int
r_int
id|last_ecb_used
suffix:semicolon
DECL|member|ecb
r_struct
id|ecb
id|ecb
(braket
id|AHA1740_ECBS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HOSTDATA
mdefine_line|#define HOSTDATA(host) ((struct aha1740_hostdata *) &amp;host-&gt;hostdata)
DECL|variable|aha1740_lock
r_static
id|spinlock_t
id|aha1740_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* One for each IRQ level (9-15) */
DECL|variable|aha_host
r_static
r_struct
id|Scsi_Host
op_star
id|aha_host
(braket
l_int|8
)braket
op_assign
(brace
l_int|NULL
comma
)brace
suffix:semicolon
DECL|function|aha1740_proc_info
r_static
r_int
id|aha1740_proc_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|hostno
comma
r_int
id|inout
)paren
(brace
r_int
id|len
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|shpnt
suffix:semicolon
r_struct
id|aha1740_hostdata
op_star
id|host
suffix:semicolon
r_if
c_cond
(paren
id|inout
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_for
c_loop
(paren
id|len
op_assign
l_int|0
suffix:semicolon
id|len
OL
l_int|8
suffix:semicolon
id|len
op_increment
)paren
(brace
id|shpnt
op_assign
id|aha_host
(braket
id|len
)braket
suffix:semicolon
r_if
c_cond
(paren
id|shpnt
op_logical_and
id|shpnt-&gt;host_no
op_eq
id|hostno
)paren
r_break
suffix:semicolon
)brace
id|host
op_assign
id|HOSTDATA
c_func
(paren
id|shpnt
)paren
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;aha174x at IO:%lx, IRQ %d, SLOT %d.&bslash;n&quot;
l_string|&quot;Extended translation %sabled.&bslash;n&quot;
comma
id|shpnt-&gt;io_port
comma
id|shpnt-&gt;irq
comma
id|host-&gt;slot
comma
id|host-&gt;translation
ques
c_cond
l_string|&quot;en&quot;
suffix:colon
l_string|&quot;dis&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
OG
id|len
)paren
(brace
op_star
id|start
op_assign
id|buffer
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|start
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
id|len
op_sub_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|aha1740_makecode
r_static
r_int
id|aha1740_makecode
c_func
(paren
id|unchar
op_star
id|sense
comma
id|unchar
op_star
id|status
)paren
(brace
r_struct
id|statusword
(brace
id|ushort
id|don
suffix:colon
l_int|1
comma
multiline_comment|/* Command Done - No Error */
id|du
suffix:colon
l_int|1
comma
multiline_comment|/* Data underrun */
suffix:colon
l_int|1
comma
id|qf
suffix:colon
l_int|1
comma
multiline_comment|/* Queue full */
id|sc
suffix:colon
l_int|1
comma
multiline_comment|/* Specification Check */
id|dor
suffix:colon
l_int|1
comma
multiline_comment|/* Data overrun */
id|ch
suffix:colon
l_int|1
comma
multiline_comment|/* Chaining Halted */
id|intr
suffix:colon
l_int|1
comma
multiline_comment|/* Interrupt issued */
id|asa
suffix:colon
l_int|1
comma
multiline_comment|/* Additional Status Available */
id|sns
suffix:colon
l_int|1
comma
multiline_comment|/* Sense information Stored */
suffix:colon
l_int|1
comma
id|ini
suffix:colon
l_int|1
comma
multiline_comment|/* Initialization Required */
id|me
suffix:colon
l_int|1
comma
multiline_comment|/* Major error or exception */
suffix:colon
l_int|1
comma
id|eca
suffix:colon
l_int|1
comma
multiline_comment|/* Extended Contingent alliance */
suffix:colon
l_int|1
suffix:semicolon
)brace
id|status_word
suffix:semicolon
r_int
id|retval
op_assign
id|DID_OK
suffix:semicolon
id|status_word
op_assign
op_star
(paren
r_struct
id|statusword
op_star
)paren
id|status
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;makecode from %x,%x,%x,%x %x,%x,%x,%x&quot;
comma
id|status
(braket
l_int|0
)braket
comma
id|status
(braket
l_int|1
)braket
comma
id|status
(braket
l_int|2
)braket
comma
id|status
(braket
l_int|3
)braket
comma
id|sense
(braket
l_int|0
)braket
comma
id|sense
(braket
l_int|1
)braket
comma
id|sense
(braket
l_int|2
)braket
comma
id|sense
(braket
l_int|3
)braket
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|status_word.don
)paren
multiline_comment|/* Anything abnormal was detected */
(brace
r_if
c_cond
(paren
(paren
id|status
(braket
l_int|1
)braket
op_amp
l_int|0x18
)paren
op_logical_or
id|status_word.sc
)paren
multiline_comment|/*Additional info available*/
(brace
multiline_comment|/* Use the supplied info for further diagnostics */
r_switch
c_cond
(paren
id|status
(braket
l_int|2
)braket
)paren
(brace
r_case
l_int|0x12
suffix:colon
r_if
c_cond
(paren
id|status_word.dor
)paren
id|retval
op_assign
id|DID_ERROR
suffix:semicolon
multiline_comment|/* It&squot;s an Overrun */
multiline_comment|/* If not overrun, assume underrun and ignore it! */
r_case
l_int|0x00
suffix:colon
multiline_comment|/* No info, assume no error, should not occur */
r_break
suffix:semicolon
r_case
l_int|0x11
suffix:colon
r_case
l_int|0x21
suffix:colon
id|retval
op_assign
id|DID_TIME_OUT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0a
suffix:colon
id|retval
op_assign
id|DID_BAD_TARGET
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x04
suffix:colon
r_case
l_int|0x05
suffix:colon
id|retval
op_assign
id|DID_ABORT
suffix:semicolon
multiline_comment|/* Either by this driver or the AHA1740 itself */
r_break
suffix:semicolon
r_default
suffix:colon
id|retval
op_assign
id|DID_ERROR
suffix:semicolon
multiline_comment|/* No further diagnostics possible */
)brace
)brace
r_else
(brace
multiline_comment|/* Michael suggests, and Brad concurs: */
r_if
c_cond
(paren
id|status_word.qf
)paren
(brace
id|retval
op_assign
id|DID_TIME_OUT
suffix:semicolon
multiline_comment|/* forces a redo */
multiline_comment|/* I think this specific one should not happen -Brad */
id|printk
c_func
(paren
l_string|&quot;aha1740.c: WARNING: AHA1740 queue overflow!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|status
(braket
l_int|0
)braket
op_amp
l_int|0x60
)paren
(brace
id|retval
op_assign
id|DID_ERROR
suffix:semicolon
multiline_comment|/* Didn&squot;t find a better error */
)brace
multiline_comment|/* In any other case return DID_OK so for example&n;&t;       CONDITION_CHECKS make it through to the appropriate&n;&t;       device driver */
)brace
)brace
multiline_comment|/* Under all circumstances supply the target status -Michael */
r_return
id|status
(braket
l_int|3
)braket
op_or
id|retval
op_lshift
l_int|16
suffix:semicolon
)brace
DECL|function|aha1740_test_port
r_static
r_int
id|aha1740_test_port
c_func
(paren
r_int
r_int
id|base
)paren
(brace
r_char
id|name
(braket
l_int|4
)braket
comma
id|tmp
suffix:semicolon
multiline_comment|/* Okay, look for the EISA ID&squot;s */
id|name
(braket
l_int|0
)braket
op_assign
l_char|&squot;A&squot;
op_minus
l_int|1
op_plus
(paren
(paren
id|tmp
op_assign
id|inb
c_func
(paren
id|HID0
c_func
(paren
id|base
)paren
)paren
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
multiline_comment|/* First character */
id|name
(braket
l_int|1
)braket
op_assign
l_char|&squot;A&squot;
op_minus
l_int|1
op_plus
(paren
(paren
id|tmp
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
id|name
(braket
l_int|1
)braket
op_add_assign
(paren
(paren
id|tmp
op_assign
id|inb
c_func
(paren
id|HID1
c_func
(paren
id|base
)paren
)paren
)paren
op_rshift
l_int|5
)paren
op_amp
l_int|0x7
suffix:semicolon
multiline_comment|/* Second Character */
id|name
(braket
l_int|2
)braket
op_assign
l_char|&squot;A&squot;
op_minus
l_int|1
op_plus
(paren
id|tmp
op_amp
l_int|0x1f
)paren
suffix:semicolon
multiline_comment|/* Third Character */
id|name
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|tmp
op_assign
id|inb
c_func
(paren
id|HID2
c_func
(paren
id|base
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
(paren
id|name
comma
id|HID_MFG
)paren
op_logical_or
id|inb
c_func
(paren
id|HID2
c_func
(paren
id|base
)paren
)paren
op_ne
id|HID_PRD
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Not an Adaptec 174x */
multiline_comment|/*  if ( inb(HID3(base)) != HID_REV )&n;&t;printk(&quot;aha174x: Warning; board revision of %d; expected %d&bslash;n&quot;,&n;&t;    inb(HID3(base)),HID_REV); */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|EBCNTRL
c_func
(paren
id|base
)paren
)paren
op_ne
id|EBCNTRL_VALUE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;aha174x: Board detected, but EBCNTRL = %x, so disabled it.&bslash;n&quot;
comma
id|inb
c_func
(paren
id|EBCNTRL
c_func
(paren
id|base
)paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inb
c_func
(paren
id|PORTADR
c_func
(paren
id|base
)paren
)paren
op_amp
id|PORTADDR_ENH
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Okay, we&squot;re all set */
id|printk
c_func
(paren
l_string|&quot;aha174x: Board detected, but not in enhanced mode, so disabled it.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* A &quot;high&quot; level interrupt handler */
DECL|function|aha1740_intr_handle
r_static
r_void
id|aha1740_intr_handle
c_func
(paren
r_int
id|irq
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
r_struct
id|Scsi_Host
op_star
id|host
op_assign
id|aha_host
(braket
id|irq
op_minus
l_int|9
)braket
suffix:semicolon
r_void
(paren
op_star
id|my_done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|errstatus
comma
id|adapstat
suffix:semicolon
r_int
id|number_serviced
suffix:semicolon
r_struct
id|ecb
op_star
id|ecbptr
suffix:semicolon
id|Scsi_Cmnd
op_star
id|SCtmp
suffix:semicolon
r_int
r_int
id|base
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host
)paren
id|panic
c_func
(paren
l_string|&quot;aha1740.c: Irq from unknown host!&bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
id|host-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
id|base
op_assign
id|host-&gt;io_port
suffix:semicolon
id|number_serviced
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|inb
c_func
(paren
id|G2STAT
c_func
(paren
id|base
)paren
)paren
op_amp
id|G2STAT_INTPEND
)paren
(brace
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;aha1740_intr top of loop.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|adapstat
op_assign
id|inb
c_func
(paren
id|G2INTST
c_func
(paren
id|base
)paren
)paren
suffix:semicolon
id|ecbptr
op_assign
(paren
r_struct
id|ecb
op_star
)paren
id|isa_bus_to_virt
c_func
(paren
id|inl
c_func
(paren
id|MBOXIN0
c_func
(paren
id|base
)paren
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|G2CNTRL_IRST
comma
id|G2CNTRL
c_func
(paren
id|base
)paren
)paren
suffix:semicolon
multiline_comment|/* interrupt reset */
r_switch
c_cond
(paren
id|adapstat
op_amp
id|G2INTST_MASK
)paren
(brace
r_case
id|G2INTST_CCBRETRY
suffix:colon
r_case
id|G2INTST_CCBERROR
suffix:colon
r_case
id|G2INTST_CCBGOOD
suffix:colon
multiline_comment|/* Host Ready -&gt; Mailbox in complete */
id|outb
c_func
(paren
id|G2CNTRL_HRDY
comma
id|G2CNTRL
c_func
(paren
id|base
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ecbptr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Aha1740 null ecbptr in interrupt (%x,%x,%x,%d)&bslash;n&quot;
comma
id|inb
c_func
(paren
id|G2STAT
c_func
(paren
id|base
)paren
)paren
comma
id|adapstat
comma
id|inb
c_func
(paren
id|G2INTST
c_func
(paren
id|base
)paren
)paren
comma
id|number_serviced
op_increment
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|SCtmp
op_assign
id|ecbptr-&gt;SCpnt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|SCtmp
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Aha1740 null SCtmp in interrupt (%x,%x,%x,%d)&bslash;n&quot;
comma
id|inb
c_func
(paren
id|G2STAT
c_func
(paren
id|base
)paren
)paren
comma
id|adapstat
comma
id|inb
c_func
(paren
id|G2INTST
c_func
(paren
id|base
)paren
)paren
comma
id|number_serviced
op_increment
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|SCtmp-&gt;host_scribble
)paren
id|kfree
c_func
(paren
id|SCtmp-&gt;host_scribble
)paren
suffix:semicolon
multiline_comment|/* Fetch the sense data, and tuck it away, in the required slot.&n;&t;       The Adaptec automatically fetches it, and there is no&n;&t;       guarantee that we will still have it in the cdb when we come&n;&t;       back */
r_if
c_cond
(paren
(paren
id|adapstat
op_amp
id|G2INTST_MASK
)paren
op_eq
id|G2INTST_CCBERROR
)paren
(brace
id|memcpy
c_func
(paren
id|SCtmp-&gt;sense_buffer
comma
id|ecbptr-&gt;sense
comma
r_sizeof
(paren
id|SCtmp-&gt;sense_buffer
)paren
)paren
suffix:semicolon
id|errstatus
op_assign
id|aha1740_makecode
c_func
(paren
id|ecbptr-&gt;sense
comma
id|ecbptr-&gt;status
)paren
suffix:semicolon
)brace
r_else
id|errstatus
op_assign
l_int|0
suffix:semicolon
id|DEB
c_func
(paren
r_if
(paren
id|errstatus
)paren
id|printk
c_func
(paren
l_string|&quot;aha1740_intr_handle: returning %6x&bslash;n&quot;
comma
id|errstatus
)paren
)paren
suffix:semicolon
id|SCtmp-&gt;result
op_assign
id|errstatus
suffix:semicolon
id|my_done
op_assign
id|ecbptr-&gt;done
suffix:semicolon
id|memset
c_func
(paren
id|ecbptr
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ecb
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|my_done
)paren
id|my_done
c_func
(paren
id|SCtmp
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|G2INTST_HARDFAIL
suffix:colon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;aha1740 hardware failure!&bslash;n&quot;
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;aha1740.c&quot;
)paren
suffix:semicolon
multiline_comment|/* Goodbye */
r_case
id|G2INTST_ASNEVENT
suffix:colon
id|printk
c_func
(paren
l_string|&quot;aha1740 asynchronous event: %02x %02x %02x %02x %02x&bslash;n&quot;
comma
id|adapstat
comma
id|inb
c_func
(paren
id|MBOXIN0
c_func
(paren
id|base
)paren
)paren
comma
id|inb
c_func
(paren
id|MBOXIN1
c_func
(paren
id|base
)paren
)paren
comma
id|inb
c_func
(paren
id|MBOXIN2
c_func
(paren
id|base
)paren
)paren
comma
id|inb
c_func
(paren
id|MBOXIN3
c_func
(paren
id|base
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Say What? */
multiline_comment|/* Host Ready -&gt; Mailbox in complete */
id|outb
c_func
(paren
id|G2CNTRL_HRDY
comma
id|G2CNTRL
c_func
(paren
id|base
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|G2INTST_CMDGOOD
suffix:colon
multiline_comment|/* set immediate command success flag here: */
r_break
suffix:semicolon
r_case
id|G2INTST_CMDERROR
suffix:colon
multiline_comment|/* Set immediate command failure flag here: */
r_break
suffix:semicolon
)brace
id|number_serviced
op_increment
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
id|host-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|aha1740_queuecommand
r_static
r_int
id|aha1740_queuecommand
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
(brace
id|unchar
id|direction
suffix:semicolon
id|unchar
op_star
id|cmd
op_assign
(paren
id|unchar
op_star
)paren
id|SCpnt-&gt;cmnd
suffix:semicolon
id|unchar
id|target
op_assign
id|SCpnt-&gt;device-&gt;id
suffix:semicolon
r_struct
id|aha1740_hostdata
op_star
id|host
op_assign
id|HOSTDATA
c_func
(paren
id|SCpnt-&gt;device-&gt;host
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_void
op_star
id|buff
op_assign
id|SCpnt-&gt;request_buffer
suffix:semicolon
r_int
id|bufflen
op_assign
id|SCpnt-&gt;request_bufflen
suffix:semicolon
r_int
id|ecbno
suffix:semicolon
id|DEB
c_func
(paren
r_int
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cmd
op_eq
id|REQUEST_SENSE
)paren
(brace
id|SCpnt-&gt;result
op_assign
l_int|0
suffix:semicolon
id|done
c_func
(paren
id|SCpnt
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
op_star
id|cmd
op_eq
id|READ_10
op_logical_or
op_star
id|cmd
op_eq
id|WRITE_10
)paren
id|i
op_assign
id|xscsi2int
c_func
(paren
id|cmd
op_plus
l_int|2
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|cmd
op_eq
id|READ_6
op_logical_or
op_star
id|cmd
op_eq
id|WRITE_6
)paren
id|i
op_assign
id|scsi2int
c_func
(paren
id|cmd
op_plus
l_int|2
)paren
suffix:semicolon
r_else
id|i
op_assign
op_minus
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;aha1740_queuecommand: dev %d cmd %02x pos %d len %d &quot;
comma
id|target
comma
op_star
id|cmd
comma
id|i
comma
id|bufflen
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;scsi cmd:&quot;
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
id|SCpnt-&gt;cmd_len
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|cmd
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* locate an available ecb */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|aha1740_lock
comma
id|flags
)paren
suffix:semicolon
id|ecbno
op_assign
id|host-&gt;last_ecb_used
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* An optimization */
r_if
c_cond
(paren
id|ecbno
op_ge
id|AHA1740_ECBS
)paren
id|ecbno
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|cmdw
)paren
r_break
suffix:semicolon
id|ecbno
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ecbno
op_ge
id|AHA1740_ECBS
)paren
id|ecbno
op_assign
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ecbno
op_ne
id|host-&gt;last_ecb_used
)paren
suffix:semicolon
r_if
c_cond
(paren
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|cmdw
)paren
id|panic
c_func
(paren
l_string|&quot;Unable to find empty ecb for aha1740.&bslash;n&quot;
)paren
suffix:semicolon
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|cmdw
op_assign
id|AHA1740CMD_INIT
suffix:semicolon
multiline_comment|/* SCSI Initiator Command&n;&t;&t;&t;&t;&t;&t;   doubles as reserved flag */
id|host-&gt;last_ecb_used
op_assign
id|ecbno
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|aha1740_lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Sending command (%d %x)...&quot;
comma
id|ecbno
comma
id|done
)paren
suffix:semicolon
macro_line|#endif
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|cdblen
op_assign
id|SCpnt-&gt;cmd_len
suffix:semicolon
multiline_comment|/* SCSI Command Descriptor Block Length */
id|direction
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cmd
op_eq
id|READ_10
op_logical_or
op_star
id|cmd
op_eq
id|READ_6
)paren
id|direction
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|cmd
op_eq
id|WRITE_10
op_logical_or
op_star
id|cmd
op_eq
id|WRITE_6
)paren
id|direction
op_assign
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|cdb
comma
id|cmd
comma
id|SCpnt-&gt;cmd_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt-&gt;use_sg
)paren
(brace
r_struct
id|scatterlist
op_star
id|sgpnt
suffix:semicolon
r_struct
id|aha1740_chain
op_star
id|cptr
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DEB
c_func
(paren
r_int
r_char
op_star
id|ptr
)paren
suffix:semicolon
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|sg
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* SCSI Initiator Command  w/scatter-gather*/
id|SCpnt-&gt;host_scribble
op_assign
(paren
r_int
r_char
op_star
)paren
id|kmalloc
c_func
(paren
l_int|512
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt-&gt;host_scribble
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;aha1740: out of memory in queuecommand!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|sgpnt
op_assign
(paren
r_struct
id|scatterlist
op_star
)paren
id|SCpnt-&gt;request_buffer
suffix:semicolon
id|cptr
op_assign
(paren
r_struct
id|aha1740_chain
op_star
)paren
id|SCpnt-&gt;host_scribble
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
id|SCpnt-&gt;use_sg
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cptr
(braket
id|i
)braket
dot
id|datalen
op_assign
id|sgpnt
(braket
id|i
)braket
dot
id|length
suffix:semicolon
id|cptr
(braket
id|i
)braket
dot
id|dataptr
op_assign
id|isa_virt_to_bus
c_func
(paren
id|page_address
c_func
(paren
id|sgpnt
(braket
id|i
)braket
dot
id|page
)paren
op_plus
id|sgpnt
(braket
id|i
)braket
dot
id|offset
)paren
suffix:semicolon
)brace
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|datalen
op_assign
id|SCpnt-&gt;use_sg
op_star
r_sizeof
(paren
r_struct
id|aha1740_chain
)paren
suffix:semicolon
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|dataptr
op_assign
id|isa_virt_to_bus
c_func
(paren
id|cptr
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;cptr %x: &quot;
comma
id|cptr
)paren
suffix:semicolon
id|ptr
op_assign
(paren
r_int
r_char
op_star
)paren
id|cptr
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
l_int|24
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|ptr
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_else
(brace
id|SCpnt-&gt;host_scribble
op_assign
l_int|NULL
suffix:semicolon
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|datalen
op_assign
id|bufflen
suffix:semicolon
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|dataptr
op_assign
id|isa_virt_to_bus
c_func
(paren
id|buff
)paren
suffix:semicolon
)brace
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|lun
op_assign
id|SCpnt-&gt;device-&gt;lun
suffix:semicolon
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|ses
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Suppress underrun errors */
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|dir
op_assign
id|direction
suffix:semicolon
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|ars
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Yes, get the sense on an error */
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|senselen
op_assign
l_int|12
suffix:semicolon
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|senseptr
op_assign
id|isa_virt_to_bus
c_func
(paren
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|sense
)paren
suffix:semicolon
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|statusptr
op_assign
id|isa_virt_to_bus
c_func
(paren
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|status
)paren
suffix:semicolon
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|done
op_assign
id|done
suffix:semicolon
id|host-&gt;ecb
(braket
id|ecbno
)braket
dot
id|SCpnt
op_assign
id|SCpnt
suffix:semicolon
macro_line|#ifdef DEBUG
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;aha1740_command: sending.. &quot;
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
r_sizeof
(paren
id|host-&gt;ecb
(braket
id|ecbno
)braket
)paren
op_minus
l_int|10
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
(paren
(paren
id|unchar
op_star
)paren
op_amp
id|host-&gt;ecb
(braket
id|ecbno
)braket
)paren
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|done
)paren
(brace
multiline_comment|/*  The Adaptec Spec says the card is so fast that the loops will&n;&t;  only be executed once in the code below. Even if this was true&n;&t;  with the fastest processors when the spec was written, it doesn&squot;t&n;&t;  seem to be true with todays fast processors. We print a warning&n;&t;  if the code is executed more often than LOOPCNT_WARN. If this&n;&t;  happens, it should be investigated. If the count reaches&n;&t;  LOOPCNT_MAX, we assume something is broken; since there is no&n;&t;  way to return an error (the return value is ignored by the&n;&t;  mid-level scsi layer) we have to panic (and maybe that&squot;s the&n;&t;  best thing we can do then anyhow). */
DECL|macro|LOOPCNT_WARN
mdefine_line|#define LOOPCNT_WARN 10&t;&t;/* excessive mbxout wait -&gt; syslog-msg */
DECL|macro|LOOPCNT_MAX
mdefine_line|#define LOOPCNT_MAX 1000000&t;/* mbxout deadlock -&gt; panic() after ~ 2 sec. */
r_int
id|loopcnt
suffix:semicolon
r_int
r_int
id|base
op_assign
id|SCpnt-&gt;device-&gt;host-&gt;io_port
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;aha1740[%d] critical section&bslash;n&quot;
comma
id|ecbno
)paren
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|aha1740_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|loopcnt
op_assign
l_int|0
suffix:semicolon
suffix:semicolon
id|loopcnt
op_increment
)paren
(brace
r_if
c_cond
(paren
id|inb
c_func
(paren
id|G2STAT
c_func
(paren
id|base
)paren
)paren
op_amp
id|G2STAT_MBXOUT
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|loopcnt
op_eq
id|LOOPCNT_WARN
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;aha1740[%d]_mbxout wait!&bslash;n&quot;
comma
id|ecbno
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|loopcnt
op_eq
id|LOOPCNT_MAX
)paren
id|panic
c_func
(paren
l_string|&quot;aha1740.c: mbxout busy!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|outl
c_func
(paren
id|isa_virt_to_bus
c_func
(paren
id|host-&gt;ecb
op_plus
id|ecbno
)paren
comma
id|MBOXOUT0
c_func
(paren
id|base
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|loopcnt
op_assign
l_int|0
suffix:semicolon
suffix:semicolon
id|loopcnt
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|inb
c_func
(paren
id|G2STAT
c_func
(paren
id|base
)paren
)paren
op_amp
id|G2STAT_BUSY
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|loopcnt
op_eq
id|LOOPCNT_WARN
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;aha1740[%d]_attn wait!&bslash;n&quot;
comma
id|ecbno
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|loopcnt
op_eq
id|LOOPCNT_MAX
)paren
id|panic
c_func
(paren
l_string|&quot;aha1740.c: attn wait failed!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|outb
c_func
(paren
id|ATTN_START
op_or
(paren
id|target
op_amp
l_int|7
)paren
comma
id|ATTN
c_func
(paren
id|base
)paren
)paren
suffix:semicolon
multiline_comment|/* Start it up */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|aha1740_lock
comma
id|flags
)paren
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;aha1740[%d] request queued.&bslash;n&quot;
comma
id|ecbno
)paren
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;aha1740_queuecommand: done can&squot;t be NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|internal_done
r_static
r_void
id|internal_done
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
id|SCpnt-&gt;SCp.Status
op_increment
suffix:semicolon
)brace
DECL|function|aha1740_command
r_static
r_int
id|aha1740_command
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
id|aha1740_queuecommand
c_func
(paren
id|SCpnt
comma
id|internal_done
)paren
suffix:semicolon
id|SCpnt-&gt;SCp.Status
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|SCpnt-&gt;SCp.Status
)paren
(brace
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|SCpnt-&gt;result
suffix:semicolon
)brace
multiline_comment|/* Query the board for its irq_level.  Nothing else matters&n;   in enhanced mode on an EISA bus. */
DECL|function|aha1740_getconfig
r_static
r_void
id|aha1740_getconfig
c_func
(paren
r_int
r_int
id|base
comma
r_int
r_int
op_star
id|irq_level
comma
r_int
r_int
op_star
id|translation
)paren
(brace
r_static
r_int
id|intab
(braket
)braket
op_assign
(brace
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|12
comma
l_int|0
comma
l_int|14
comma
l_int|15
comma
l_int|0
)brace
suffix:semicolon
op_star
id|irq_level
op_assign
id|intab
(braket
id|inb
c_func
(paren
id|INTDEF
c_func
(paren
id|base
)paren
)paren
op_amp
l_int|0x7
)braket
suffix:semicolon
op_star
id|translation
op_assign
id|inb
c_func
(paren
id|RESV1
c_func
(paren
id|base
)paren
)paren
op_amp
l_int|0x1
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|INTDEF
c_func
(paren
id|base
)paren
)paren
op_or
l_int|0x10
comma
id|INTDEF
c_func
(paren
id|base
)paren
)paren
suffix:semicolon
)brace
DECL|function|aha1740_detect
r_static
r_int
id|aha1740_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
r_int
id|count
op_assign
l_int|0
comma
id|slot
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;aha1740_detect: &bslash;n&quot;
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|slot
op_assign
id|MINEISA
suffix:semicolon
id|slot
op_le
id|MAXEISA
suffix:semicolon
id|slot
op_increment
)paren
(brace
r_int
id|slotbase
suffix:semicolon
r_int
r_int
id|irq_level
comma
id|translation
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|shpnt
suffix:semicolon
r_struct
id|aha1740_hostdata
op_star
id|host
suffix:semicolon
id|slotbase
op_assign
id|SLOTBASE
c_func
(paren
id|slot
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The ioports for eisa boards are generally beyond that used in the&n;&t; * check/allocate region code, but this may change at some point,&n;&t; * so we go through the motions.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|slotbase
comma
id|SLOTSIZE
comma
l_string|&quot;aha1740&quot;
)paren
)paren
multiline_comment|/* See if in use */
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|aha1740_test_port
c_func
(paren
id|slotbase
)paren
)paren
r_goto
id|err_release
suffix:semicolon
id|aha1740_getconfig
c_func
(paren
id|slotbase
comma
op_amp
id|irq_level
comma
op_amp
id|translation
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|G2STAT
c_func
(paren
id|slotbase
)paren
)paren
op_amp
(paren
id|G2STAT_MBXOUT
op_or
id|G2STAT_BUSY
)paren
)paren
op_ne
id|G2STAT_MBXOUT
)paren
(brace
multiline_comment|/* If the card isn&squot;t ready, hard reset it */
id|outb
c_func
(paren
id|G2CNTRL_HRST
comma
id|G2CNTRL
c_func
(paren
id|slotbase
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|G2CNTRL
c_func
(paren
id|slotbase
)paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Configuring aha174x at IO:%x, IRQ %d&bslash;n&quot;
comma
id|slotbase
comma
id|irq_level
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;aha174x: Extended translation %sabled.&bslash;n&quot;
comma
id|translation
ques
c_cond
l_string|&quot;en&quot;
suffix:colon
l_string|&quot;dis&quot;
)paren
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;aha1740_detect: enable interrupt channel %d&bslash;n&quot;
comma
id|irq_level
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|irq_level
comma
id|aha1740_intr_handle
comma
l_int|0
comma
l_string|&quot;aha1740&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to allocate IRQ for adaptec controller.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_release
suffix:semicolon
)brace
id|shpnt
op_assign
id|scsi_register
c_func
(paren
id|tpnt
comma
r_sizeof
(paren
r_struct
id|aha1740_hostdata
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shpnt
op_eq
l_int|NULL
)paren
(brace
r_goto
id|err_free_irq
suffix:semicolon
)brace
id|shpnt-&gt;base
op_assign
l_int|0
suffix:semicolon
id|shpnt-&gt;io_port
op_assign
id|slotbase
suffix:semicolon
id|shpnt-&gt;n_io_port
op_assign
id|SLOTSIZE
suffix:semicolon
id|shpnt-&gt;irq
op_assign
id|irq_level
suffix:semicolon
id|shpnt-&gt;dma_channel
op_assign
l_int|0xff
suffix:semicolon
id|host
op_assign
id|HOSTDATA
c_func
(paren
id|shpnt
)paren
suffix:semicolon
id|host-&gt;slot
op_assign
id|slot
suffix:semicolon
id|host-&gt;translation
op_assign
id|translation
suffix:semicolon
id|aha_host
(braket
id|irq_level
op_minus
l_int|9
)braket
op_assign
id|shpnt
suffix:semicolon
id|count
op_increment
suffix:semicolon
r_continue
suffix:semicolon
id|err_free_irq
suffix:colon
id|free_irq
c_func
(paren
id|irq_level
comma
id|aha1740_intr_handle
)paren
suffix:semicolon
id|err_release
suffix:colon
id|release_region
c_func
(paren
id|slotbase
comma
id|SLOTSIZE
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|aha1740_biosparam
r_static
r_int
id|aha1740_biosparam
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_struct
id|block_device
op_star
id|dev
comma
id|sector_t
id|capacity
comma
r_int
op_star
id|ip
)paren
(brace
r_int
id|size
op_assign
id|capacity
suffix:semicolon
r_int
id|extended
op_assign
id|HOSTDATA
c_func
(paren
id|sdev-&gt;host
)paren
op_member_access_from_pointer
id|translation
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;aha1740_biosparam&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|extended
op_logical_and
(paren
id|ip
(braket
l_int|2
)braket
OG
l_int|1024
)paren
)paren
(brace
id|ip
(braket
l_int|0
)braket
op_assign
l_int|255
suffix:semicolon
id|ip
(braket
l_int|1
)braket
op_assign
l_int|63
suffix:semicolon
id|ip
(braket
l_int|2
)braket
op_assign
id|size
op_div
(paren
l_int|255
op_star
l_int|63
)paren
suffix:semicolon
)brace
r_else
(brace
id|ip
(braket
l_int|0
)braket
op_assign
l_int|64
suffix:semicolon
id|ip
(braket
l_int|1
)braket
op_assign
l_int|32
suffix:semicolon
id|ip
(braket
l_int|2
)braket
op_assign
id|size
op_rshift
l_int|11
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* Eventually this will go into an include file, but this will be later */
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
id|AHA1740
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
multiline_comment|/* Okay, you made it all the way through.  As of this writing, 3/31/93, I&squot;m&n;brad@saturn.gaylord.com or brad@bradpc.gaylord.com.  I&squot;ll try to help as time&n;permits if you have any trouble with this driver.  Happy Linuxing! */
eof
