multiline_comment|/*&n; * OHCI HCD (Host Controller Driver) for USB.&n; *&n; * (C) Copyright 1999 Roman Weissgaerber &lt;weissg@vienna.at&gt;&n; * (C) Copyright 2000-2002 David Brownell &lt;dbrownell@users.sourceforge.net&gt;&n; * &n; * [ Initialisation is based on Linus&squot;  ]&n; * [ uhci code and gregs ohci fragments ]&n; * [ (C) Copyright 1999 Linus Torvalds  ]&n; * [ (C) Copyright 1999 Gregory P. Smith]&n; * &n; * &n; * History:&n; * &n; * 2002/06/01 remember frame when HC won&squot;t see EDs any more; use that info&n; *&t;to fix urb unlink races caused by interrupt latency assumptions;&n; *&t;minor ED field and function naming updates&n; * 2002/01/18 package as a patch for 2.5.3; this should match the&n; *&t;2.4.17 kernel modulo some bugs being fixed.&n; *&n; * 2001/10/18 merge pmac cleanup (Benjamin Herrenschmidt) and bugfixes&n; *&t;from post-2.4.5 patches.&n; * 2001/09/20 USB_ZERO_PACKET support; hcca_dma portability, OPTi warning&n; * 2001/09/07 match PCI PM changes, errnos from Linus&squot; tree&n; * 2001/05/05 fork 2.4.5 version into &quot;hcd&quot; framework, cleanup, simplify;&n; *&t;pbook pci quirks gone (please fix pbook pci sw!) (db)&n; *&n; * 2001/04/08 Identify version on module load (gb)&n; * 2001/03/24 td/ed hashing to remove bus_to_virt (Steve Longerbeam);&n; &t;pci_map_single (db)&n; * 2001/03/21 td and dev/ed allocation uses new pci_pool API (db)&n; * 2001/03/07 hcca allocation uses pci_alloc_consistent (Steve Longerbeam)&n; *&n; * 2000/09/26 fixed races in removing the private portion of the urb&n; * 2000/09/07 disable bulk and control lists when unlinking the last&n; *&t;endpoint descriptor in order to avoid unrecoverable errors on&n; *&t;the Lucent chips. (rwc@sgi)&n; * 2000/08/29 use bandwidth claiming hooks (thanks Randy!), fix some&n; *&t;urb unlink probs, indentation fixes&n; * 2000/08/11 various oops fixes mostly affecting iso and cleanup from&n; *&t;device unplugs.&n; * 2000/06/28 use PCI hotplug framework, for better power management&n; *&t;and for Cardbus support (David Brownell)&n; * 2000/earlier:  fixes for NEC/Lucent chips; suspend/resume handling&n; *&t;when the controller loses power; handle UE; cleanup; ...&n; *&n; * v5.2 1999/12/07 URB 3rd preview, &n; * v5.1 1999/11/30 URB 2nd preview, cpia, (usb-scsi)&n; * v5.0 1999/11/22 URB Technical preview, Paul Mackerras powerbook susp/resume &n; * &t;i386: HUB, Keyboard, Mouse, Printer &n; *&n; * v4.3 1999/10/27 multiple HCs, bulk_request&n; * v4.2 1999/09/05 ISO API alpha, new dev alloc, neg Error-codes&n; * v4.1 1999/08/27 Randy Dunlap&squot;s - ISO API first impl.&n; * v4.0 1999/08/18 &n; * v3.0 1999/06/25 &n; * v2.1 1999/05/09  code clean up&n; * v2.0 1999/05/04 &n; * v1.0 1999/04/27 initial release&n; *&n; * This file is licenced under the GPL.&n; * $Id: ohci-hcd.c,v 1.9 2002/03/27 20:41:57 dbrownell Exp $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;  /* for in_interrupt () */
macro_line|#ifdef CONFIG_USB_DEBUG
DECL|macro|DEBUG
macro_line|#&t;define DEBUG
macro_line|#else
DECL|macro|DEBUG
macro_line|#&t;undef DEBUG
macro_line|#endif
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &quot;../core/hcd.h&quot;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/*&n; * TO DO:&n; *&n; *&t;- &quot;disabled&quot; should be the hcd state&n; *&t;- bandwidth alloc to generic code&n; *&t;- lots more testing!!&n; */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;2002-Jun-01&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Roman Weissgaerber &lt;weissg@vienna.at&gt;, David Brownell&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;USB 1.1 &squot;Open&squot; Host Controller (OHCI) Driver&quot;
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|macro|OHCI_USE_NPS
mdefine_line|#define OHCI_USE_NPS&t;&t;
singleline_comment|// force NoPowerSwitching mode
singleline_comment|// #define OHCI_VERBOSE_DEBUG&t;/* not always helpful */
multiline_comment|/* For initializing controller (mask in an HCFS mode too) */
DECL|macro|OHCI_CONTROL_INIT
mdefine_line|#define&t;OHCI_CONTROL_INIT &bslash;&n;&t; (OHCI_CTRL_CBSR &amp; 0x3) | OHCI_CTRL_IE | OHCI_CTRL_PLE
DECL|macro|OHCI_UNLINK_TIMEOUT
mdefine_line|#define OHCI_UNLINK_TIMEOUT&t; (HZ / 10)
multiline_comment|/*-------------------------------------------------------------------------*/
macro_line|#include &quot;ohci.h&quot;
macro_line|#include &quot;ohci-hub.c&quot;
macro_line|#include &quot;ohci-dbg.c&quot;
macro_line|#include &quot;ohci-mem.c&quot;
macro_line|#include &quot;ohci-q.c&quot;
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * queue up an urb for anything except the root hub&n; */
DECL|function|ohci_urb_enqueue
r_static
r_int
id|ohci_urb_enqueue
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
r_struct
id|urb
op_star
id|urb
comma
r_int
id|mem_flags
)paren
(brace
r_struct
id|ohci_hcd
op_star
id|ohci
op_assign
id|hcd_to_ohci
(paren
id|hcd
)paren
suffix:semicolon
r_struct
id|ed
op_star
id|ed
suffix:semicolon
id|urb_priv_t
op_star
id|urb_priv
suffix:semicolon
r_int
r_int
id|pipe
op_assign
id|urb-&gt;pipe
suffix:semicolon
r_int
id|i
comma
id|size
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|bustime
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef OHCI_VERBOSE_DEBUG
id|urb_print
(paren
id|urb
comma
l_string|&quot;SUB&quot;
comma
id|usb_pipein
(paren
id|pipe
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* every endpoint has a ed, locate and fill it */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ed
op_assign
id|ep_add_ed
(paren
id|urb-&gt;dev
comma
id|pipe
comma
id|urb-&gt;interval
comma
l_int|1
comma
id|mem_flags
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* for the private part of the URB we need the number of TDs (size) */
r_switch
c_cond
(paren
id|usb_pipetype
(paren
id|pipe
)paren
)paren
(brace
r_case
id|PIPE_CONTROL
suffix:colon
multiline_comment|/* 1 TD for setup, 1 for ACK, plus ... */
id|size
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* FALLTHROUGH */
r_case
id|PIPE_BULK
suffix:colon
multiline_comment|/* one TD for every 4096 Bytes (can be upto 8K) */
id|size
op_add_assign
id|urb-&gt;transfer_buffer_length
op_div
l_int|4096
suffix:semicolon
multiline_comment|/* ... and for any remaining bytes ... */
r_if
c_cond
(paren
(paren
id|urb-&gt;transfer_buffer_length
op_mod
l_int|4096
)paren
op_ne
l_int|0
)paren
id|size
op_increment
suffix:semicolon
multiline_comment|/* ... and maybe a zero length packet to wrap it up */
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
id|size
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|urb-&gt;transfer_flags
op_amp
id|USB_ZERO_PACKET
)paren
op_ne
l_int|0
op_logical_and
(paren
id|urb-&gt;transfer_buffer_length
op_mod
id|usb_maxpacket
(paren
id|urb-&gt;dev
comma
id|pipe
comma
id|usb_pipeout
(paren
id|pipe
)paren
)paren
)paren
op_ne
l_int|0
)paren
id|size
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PIPE_ISOCHRONOUS
suffix:colon
multiline_comment|/* number of packets from URB */
id|size
op_assign
id|urb-&gt;number_of_packets
suffix:semicolon
r_if
c_cond
(paren
id|size
op_le
l_int|0
)paren
r_return
op_minus
id|EINVAL
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
id|urb-&gt;number_of_packets
suffix:semicolon
id|i
op_increment
)paren
(brace
id|urb-&gt;iso_frame_desc
(braket
id|i
)braket
dot
id|actual_length
op_assign
l_int|0
suffix:semicolon
id|urb-&gt;iso_frame_desc
(braket
id|i
)braket
dot
id|status
op_assign
op_minus
id|EXDEV
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PIPE_INTERRUPT
suffix:colon
multiline_comment|/* one TD */
id|size
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* allocate the private part of the URB */
id|urb_priv
op_assign
id|kmalloc
(paren
r_sizeof
(paren
id|urb_priv_t
)paren
op_plus
id|size
op_star
r_sizeof
(paren
r_struct
id|td
op_star
)paren
comma
id|mem_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb_priv
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
(paren
id|urb_priv
comma
l_int|0
comma
r_sizeof
(paren
id|urb_priv_t
)paren
op_plus
id|size
op_star
r_sizeof
(paren
r_struct
id|td
op_star
)paren
)paren
suffix:semicolon
multiline_comment|/* fill the private part of the URB */
id|urb_priv-&gt;length
op_assign
id|size
suffix:semicolon
id|urb_priv-&gt;ed
op_assign
id|ed
suffix:semicolon
multiline_comment|/* allocate the TDs (updating hash chains) */
id|spin_lock_irqsave
(paren
op_amp
id|ohci-&gt;lock
comma
id|flags
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
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|urb_priv-&gt;td
(braket
id|i
)braket
op_assign
id|td_alloc
(paren
id|ohci
comma
id|SLAB_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb_priv-&gt;td
(braket
id|i
)braket
)paren
(brace
id|urb_priv-&gt;length
op_assign
id|i
suffix:semicolon
id|urb_free_priv
(paren
id|ohci
comma
id|urb_priv
)paren
suffix:semicolon
id|spin_unlock_irqrestore
(paren
op_amp
id|ohci-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
)brace
singleline_comment|// FIXME:  much of this switch should be generic, move to hcd code ...
multiline_comment|/* allocate and claim bandwidth if needed; ISO&n;&t; * needs start frame index if it was&squot;t provided.&n;&t; */
r_switch
c_cond
(paren
id|usb_pipetype
(paren
id|pipe
)paren
)paren
(brace
r_case
id|PIPE_ISOCHRONOUS
suffix:colon
r_if
c_cond
(paren
id|urb-&gt;transfer_flags
op_amp
id|USB_ISO_ASAP
)paren
(brace
id|urb-&gt;start_frame
op_assign
(paren
(paren
id|ed-&gt;state
op_eq
id|ED_OPER
)paren
ques
c_cond
(paren
id|ed-&gt;intriso.last_iso
op_plus
l_int|1
)paren
suffix:colon
(paren
id|le16_to_cpu
(paren
id|ohci-&gt;hcca-&gt;frame_no
)paren
op_plus
l_int|10
)paren
)paren
op_amp
l_int|0xffff
suffix:semicolon
)brace
multiline_comment|/* FALLTHROUGH */
r_case
id|PIPE_INTERRUPT
suffix:colon
r_if
c_cond
(paren
id|urb-&gt;bandwidth
op_eq
l_int|0
)paren
(brace
id|bustime
op_assign
id|usb_check_bandwidth
(paren
id|urb-&gt;dev
comma
id|urb
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bustime
OL
l_int|0
)paren
(brace
id|urb_free_priv
(paren
id|ohci
comma
id|urb_priv
)paren
suffix:semicolon
id|spin_unlock_irqrestore
(paren
op_amp
id|ohci-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|bustime
suffix:semicolon
)brace
id|usb_claim_bandwidth
(paren
id|urb-&gt;dev
comma
id|urb
comma
id|bustime
comma
id|usb_pipeisoc
(paren
id|urb-&gt;pipe
)paren
)paren
suffix:semicolon
)brace
id|urb-&gt;hcpriv
op_assign
id|urb_priv
suffix:semicolon
multiline_comment|/* link the ed into a chain if is not already */
r_if
c_cond
(paren
id|ed-&gt;state
op_ne
id|ED_OPER
)paren
id|ep_link
(paren
id|ohci
comma
id|ed
)paren
suffix:semicolon
multiline_comment|/* fill the TDs and link them to the ed; and&n;&t; * enable that part of the schedule, if needed&n;&t; */
id|td_submit_urb
(paren
id|urb
)paren
suffix:semicolon
id|spin_unlock_irqrestore
(paren
op_amp
id|ohci-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * decouple the URB from the HC queues (TDs, urb_priv); it&squot;s&n; * already marked for deletion.  reporting is always done&n; * asynchronously, and we might be dealing with an urb that&squot;s&n; * almost completed anyway...&n; */
DECL|function|ohci_urb_dequeue
r_static
r_int
id|ohci_urb_dequeue
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|ohci_hcd
op_star
id|ohci
op_assign
id|hcd_to_ohci
(paren
id|hcd
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
macro_line|#ifdef DEBUG
id|urb_print
(paren
id|urb
comma
l_string|&quot;UNLINK&quot;
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif&t;&t;  
r_if
c_cond
(paren
op_logical_neg
id|ohci-&gt;disabled
)paren
(brace
id|urb_priv_t
op_star
id|urb_priv
suffix:semicolon
multiline_comment|/* flag the urb&squot;s data for deletion in some upcoming&n;&t;&t; * SF interrupt&squot;s delete list processing&n;&t;&t; */
id|spin_lock_irqsave
(paren
op_amp
id|ohci-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|urb_priv
op_assign
id|urb-&gt;hcpriv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb_priv
op_logical_or
(paren
id|urb_priv-&gt;state
op_eq
id|URB_DEL
)paren
)paren
(brace
id|spin_unlock_irqrestore
(paren
op_amp
id|ohci-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|urb_priv-&gt;state
op_assign
id|URB_DEL
suffix:semicolon
id|start_urb_unlink
(paren
id|ohci
comma
id|urb_priv-&gt;ed
)paren
suffix:semicolon
id|spin_unlock_irqrestore
(paren
op_amp
id|ohci-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * with HC dead, we won&squot;t respect hc queue pointers&n;&t;&t; * any more ... just clean up every urb&squot;s memory.&n;&t;&t; */
id|finish_urb
(paren
id|ohci
comma
id|urb
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
r_static
r_void
DECL|function|ohci_free_config
id|ohci_free_config
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
r_struct
id|usb_device
op_star
id|udev
)paren
(brace
r_struct
id|ohci_hcd
op_star
id|ohci
op_assign
id|hcd_to_ohci
(paren
id|hcd
)paren
suffix:semicolon
r_struct
id|hcd_dev
op_star
id|dev
op_assign
(paren
r_struct
id|hcd_dev
op_star
)paren
id|udev-&gt;hcpriv
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* free any eds, and dummy tds, still hanging around */
id|spin_lock_irqsave
(paren
op_amp
id|ohci-&gt;lock
comma
id|flags
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
l_int|32
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|ed
op_star
id|ed
op_assign
id|dev-&gt;ep
(braket
id|i
)braket
suffix:semicolon
r_struct
id|td
op_star
id|tdTailP
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ed
)paren
r_continue
suffix:semicolon
id|ed-&gt;state
op_and_assign
op_complement
id|ED_URB_DEL
suffix:semicolon
r_if
c_cond
(paren
id|ohci-&gt;disabled
op_logical_and
id|ed-&gt;state
op_eq
id|ED_OPER
)paren
id|ed-&gt;state
op_assign
id|ED_UNLINK
suffix:semicolon
r_switch
c_cond
(paren
id|ed-&gt;state
)paren
(brace
r_case
id|ED_NEW
suffix:colon
r_break
suffix:semicolon
r_case
id|ED_UNLINK
suffix:colon
id|tdTailP
op_assign
id|dma_to_td
(paren
id|ohci
comma
id|le32_to_cpup
(paren
op_amp
id|ed-&gt;hwTailP
)paren
op_amp
l_int|0xfffffff0
)paren
suffix:semicolon
id|td_free
(paren
id|ohci
comma
id|tdTailP
)paren
suffix:semicolon
multiline_comment|/* free dummy td */
id|hash_free_ed
(paren
id|ohci
comma
id|ed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ED_OPER
suffix:colon
r_default
suffix:colon
id|err
(paren
l_string|&quot;illegal ED %d state in free_config, %d&quot;
comma
id|i
comma
id|ed-&gt;state
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|BUG
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
id|ed_free
(paren
id|ohci
comma
id|ed
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
(paren
op_amp
id|ohci-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|ohci_get_frame
r_static
r_int
id|ohci_get_frame
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
r_struct
id|ohci_hcd
op_star
id|ohci
op_assign
id|hcd_to_ohci
(paren
id|hcd
)paren
suffix:semicolon
r_return
id|le16_to_cpu
(paren
id|ohci-&gt;hcca-&gt;frame_no
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*&n; * HC functions&n; *-------------------------------------------------------------------------*/
multiline_comment|/* reset the HC and BUS */
DECL|function|hc_reset
r_static
r_int
id|hc_reset
(paren
r_struct
id|ohci_hcd
op_star
id|ohci
)paren
(brace
r_int
id|timeout
op_assign
l_int|30
suffix:semicolon
r_int
id|smm_timeout
op_assign
l_int|50
suffix:semicolon
multiline_comment|/* 0,5 sec */
r_if
c_cond
(paren
id|readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
op_amp
id|OHCI_CTRL_IR
)paren
(brace
multiline_comment|/* SMM owns the HC */
id|writel
(paren
id|OHCI_INTR_OC
comma
op_amp
id|ohci-&gt;regs-&gt;intrenable
)paren
suffix:semicolon
id|writel
(paren
id|OHCI_OCR
comma
op_amp
id|ohci-&gt;regs-&gt;cmdstatus
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;USB HC TakeOver from SMM&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
op_amp
id|OHCI_CTRL_IR
)paren
(brace
id|wait_ms
(paren
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|smm_timeout
op_eq
l_int|0
)paren
(brace
id|err
(paren
l_string|&quot;USB HC TakeOver failed!&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Disable HC interrupts */
id|writel
(paren
id|OHCI_INTR_MIE
comma
op_amp
id|ohci-&gt;regs-&gt;intrdisable
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;USB HC reset_hc %s: ctrl = 0x%x ;&quot;
comma
id|ohci-&gt;hcd.self.bus_name
comma
id|readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
)paren
suffix:semicolon
multiline_comment|/* Reset USB (needed by some controllers) */
id|writel
(paren
l_int|0
comma
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
multiline_comment|/* HC Reset requires max 10 ms delay */
id|writel
(paren
id|OHCI_HCR
comma
op_amp
id|ohci-&gt;regs-&gt;cmdstatus
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|readl
(paren
op_amp
id|ohci-&gt;regs-&gt;cmdstatus
)paren
op_amp
id|OHCI_HCR
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|timeout
op_eq
l_int|0
)paren
(brace
id|err
(paren
l_string|&quot;USB HC reset timed out!&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|udelay
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* Start an OHCI controller, set the BUS operational&n; * enable interrupts &n; * connect the virtual root hub&n; */
DECL|function|hc_start
r_static
r_int
id|hc_start
(paren
r_struct
id|ohci_hcd
op_star
id|ohci
)paren
(brace
id|__u32
id|mask
suffix:semicolon
r_int
r_int
id|fminterval
suffix:semicolon
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
id|spin_lock_init
(paren
op_amp
id|ohci-&gt;lock
)paren
suffix:semicolon
id|ohci-&gt;disabled
op_assign
l_int|1
suffix:semicolon
id|ohci-&gt;sleeping
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Tell the controller where the control and bulk lists are&n;&t; * The lists are empty now. */
id|writel
(paren
l_int|0
comma
op_amp
id|ohci-&gt;regs-&gt;ed_controlhead
)paren
suffix:semicolon
id|writel
(paren
l_int|0
comma
op_amp
id|ohci-&gt;regs-&gt;ed_bulkhead
)paren
suffix:semicolon
multiline_comment|/* a reset clears this */
id|writel
(paren
(paren
id|u32
)paren
id|ohci-&gt;hcca_dma
comma
op_amp
id|ohci-&gt;regs-&gt;hcca
)paren
suffix:semicolon
id|fminterval
op_assign
l_int|0x2edf
suffix:semicolon
id|writel
(paren
(paren
id|fminterval
op_star
l_int|9
)paren
op_div
l_int|10
comma
op_amp
id|ohci-&gt;regs-&gt;periodicstart
)paren
suffix:semicolon
id|fminterval
op_or_assign
(paren
(paren
(paren
(paren
id|fminterval
op_minus
l_int|210
)paren
op_star
l_int|6
)paren
op_div
l_int|7
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
id|writel
(paren
id|fminterval
comma
op_amp
id|ohci-&gt;regs-&gt;fminterval
)paren
suffix:semicolon
id|writel
(paren
l_int|0x628
comma
op_amp
id|ohci-&gt;regs-&gt;lsthresh
)paren
suffix:semicolon
multiline_comment|/* start controller operations */
id|ohci-&gt;hc_control
op_assign
id|OHCI_CONTROL_INIT
op_or
id|OHCI_USB_OPER
suffix:semicolon
id|ohci-&gt;disabled
op_assign
l_int|0
suffix:semicolon
id|writel
(paren
id|ohci-&gt;hc_control
comma
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
multiline_comment|/* Choose the interrupts we care about now, others later on demand */
id|mask
op_assign
id|OHCI_INTR_MIE
op_or
id|OHCI_INTR_UE
op_or
id|OHCI_INTR_WDH
suffix:semicolon
id|writel
(paren
id|mask
comma
op_amp
id|ohci-&gt;regs-&gt;intrstatus
)paren
suffix:semicolon
id|writel
(paren
id|mask
comma
op_amp
id|ohci-&gt;regs-&gt;intrenable
)paren
suffix:semicolon
macro_line|#ifdef&t;OHCI_USE_NPS
multiline_comment|/* required for AMD-756 and some Mac platforms */
id|writel
(paren
(paren
id|roothub_a
(paren
id|ohci
)paren
op_or
id|RH_A_NPS
)paren
op_amp
op_complement
id|RH_A_PSM
comma
op_amp
id|ohci-&gt;regs-&gt;roothub.a
)paren
suffix:semicolon
id|writel
(paren
id|RH_HS_LPSC
comma
op_amp
id|ohci-&gt;regs-&gt;roothub.status
)paren
suffix:semicolon
macro_line|#endif&t;/* OHCI_USE_NPS */
singleline_comment|// POTPGT delay is bits 24-31, in 2 ms units.
id|mdelay
(paren
(paren
id|roothub_a
(paren
id|ohci
)paren
op_rshift
l_int|23
)paren
op_amp
l_int|0x1fe
)paren
suffix:semicolon
multiline_comment|/* connect the virtual root hub */
id|ohci-&gt;hcd.self.root_hub
op_assign
id|udev
op_assign
id|usb_alloc_dev
(paren
l_int|NULL
comma
op_amp
id|ohci-&gt;hcd.self
)paren
suffix:semicolon
id|ohci-&gt;hcd.state
op_assign
id|USB_STATE_READY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|udev
)paren
(brace
id|ohci-&gt;disabled
op_assign
l_int|1
suffix:semicolon
singleline_comment|// FIXME cleanup
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|usb_connect
(paren
id|udev
)paren
suffix:semicolon
id|udev-&gt;speed
op_assign
id|USB_SPEED_FULL
suffix:semicolon
r_if
c_cond
(paren
id|usb_register_root_hub
(paren
id|udev
comma
id|ohci-&gt;parent_dev
)paren
op_ne
l_int|0
)paren
(brace
id|usb_free_dev
(paren
id|udev
)paren
suffix:semicolon
id|ohci-&gt;disabled
op_assign
l_int|1
suffix:semicolon
singleline_comment|// FIXME cleanup
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* an interrupt happens */
DECL|function|ohci_irq
r_static
r_void
id|ohci_irq
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
r_struct
id|ohci_hcd
op_star
id|ohci
op_assign
id|hcd_to_ohci
(paren
id|hcd
)paren
suffix:semicolon
r_struct
id|ohci_regs
op_star
id|regs
op_assign
id|ohci-&gt;regs
suffix:semicolon
r_int
id|ints
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ohci-&gt;hcca-&gt;done_head
op_ne
l_int|0
)paren
op_logical_and
op_logical_neg
(paren
id|le32_to_cpup
(paren
op_amp
id|ohci-&gt;hcca-&gt;done_head
)paren
op_amp
l_int|0x01
)paren
)paren
(brace
id|ints
op_assign
id|OHCI_INTR_WDH
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|ints
op_assign
(paren
id|readl
(paren
op_amp
id|regs-&gt;intrstatus
)paren
op_amp
id|readl
(paren
op_amp
id|regs-&gt;intrenable
)paren
)paren
)paren
op_eq
l_int|0
)paren
(brace
r_return
suffix:semicolon
)brace
singleline_comment|// dbg (&quot;Interrupt: %x frame: %x&quot;, ints, le16_to_cpu (ohci-&gt;hcca-&gt;frame_no));
r_if
c_cond
(paren
id|ints
op_amp
id|OHCI_INTR_UE
)paren
(brace
id|ohci-&gt;disabled
op_increment
suffix:semicolon
id|err
(paren
l_string|&quot;OHCI Unrecoverable Error, %s disabled&quot;
comma
id|hcd-&gt;self.bus_name
)paren
suffix:semicolon
singleline_comment|// e.g. due to PCI Master/Target Abort
macro_line|#ifdef&t;DEBUG
id|ohci_dump
(paren
id|ohci
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
id|hc_reset
(paren
id|ohci
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ints
op_amp
id|OHCI_INTR_WDH
)paren
(brace
id|writel
(paren
id|OHCI_INTR_WDH
comma
op_amp
id|regs-&gt;intrdisable
)paren
suffix:semicolon
id|dl_done_list
(paren
id|ohci
comma
id|dl_reverse_done_list
(paren
id|ohci
)paren
)paren
suffix:semicolon
id|writel
(paren
id|OHCI_INTR_WDH
comma
op_amp
id|regs-&gt;intrenable
)paren
suffix:semicolon
)brace
multiline_comment|/* could track INTR_SO to reduce available PCI/... bandwidth */
multiline_comment|/* handle any pending URB/ED unlinks, leaving INTR_SF enabled&n;&t; * when there&squot;s still unlinking to be done (next frame).&n;&t; */
id|spin_lock
(paren
op_amp
id|ohci-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ohci-&gt;ed_rm_list
)paren
id|finish_unlinks
(paren
id|ohci
comma
id|le16_to_cpu
(paren
id|ohci-&gt;hcca-&gt;frame_no
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ints
op_amp
id|OHCI_INTR_SF
)paren
op_ne
l_int|0
op_logical_and
op_logical_neg
id|ohci-&gt;ed_rm_list
)paren
id|writel
(paren
id|OHCI_INTR_SF
comma
op_amp
id|regs-&gt;intrdisable
)paren
suffix:semicolon
id|spin_unlock
(paren
op_amp
id|ohci-&gt;lock
)paren
suffix:semicolon
id|writel
(paren
id|ints
comma
op_amp
id|regs-&gt;intrstatus
)paren
suffix:semicolon
id|writel
(paren
id|OHCI_INTR_MIE
comma
op_amp
id|regs-&gt;intrenable
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|ohci_stop
r_static
r_void
id|ohci_stop
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
r_struct
id|ohci_hcd
op_star
id|ohci
op_assign
id|hcd_to_ohci
(paren
id|hcd
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;%s: stop %s controller%s&quot;
comma
id|hcd-&gt;self.bus_name
comma
id|hcfs2string
(paren
id|ohci-&gt;hc_control
op_amp
id|OHCI_CTRL_HCFS
)paren
comma
id|ohci-&gt;disabled
ques
c_cond
l_string|&quot; (disabled)&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
macro_line|#ifdef&t;DEBUG
id|ohci_dump
(paren
id|ohci
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|ohci-&gt;disabled
)paren
id|hc_reset
(paren
id|ohci
)paren
suffix:semicolon
id|ohci_mem_cleanup
(paren
id|ohci
)paren
suffix:semicolon
id|pci_free_consistent
(paren
id|ohci-&gt;hcd.pdev
comma
r_sizeof
op_star
id|ohci-&gt;hcca
comma
id|ohci-&gt;hcca
comma
id|ohci-&gt;hcca_dma
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
singleline_comment|// FIXME:  this restart logic should be generic,
singleline_comment|// and handle full hcd state cleanup
multiline_comment|/* controller died; cleanup debris, then restart */
multiline_comment|/* must not be called from interrupt context */
macro_line|#ifdef CONFIG_PM
DECL|function|hc_restart
r_static
r_int
id|hc_restart
(paren
r_struct
id|ohci_hcd
op_star
id|ohci
)paren
(brace
r_int
id|temp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|ohci-&gt;disabled
op_assign
l_int|1
suffix:semicolon
id|ohci-&gt;sleeping
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ohci-&gt;hcd.self.root_hub
)paren
id|usb_disconnect
(paren
op_amp
id|ohci-&gt;hcd.self.root_hub
)paren
suffix:semicolon
multiline_comment|/* empty the interrupt branches */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_INTS
suffix:semicolon
id|i
op_increment
)paren
id|ohci-&gt;ohci_int_load
(braket
id|i
)braket
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
id|NUM_INTS
suffix:semicolon
id|i
op_increment
)paren
id|ohci-&gt;hcca-&gt;int_table
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* no EDs to remove */
id|ohci-&gt;ed_rm_list
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* empty control and bulk lists */
id|ohci-&gt;ed_isotail
op_assign
l_int|NULL
suffix:semicolon
id|ohci-&gt;ed_controltail
op_assign
l_int|NULL
suffix:semicolon
id|ohci-&gt;ed_bulktail
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|temp
op_assign
id|hc_reset
(paren
id|ohci
)paren
)paren
OL
l_int|0
op_logical_or
(paren
id|temp
op_assign
id|hc_start
(paren
id|ohci
)paren
)paren
OL
l_int|0
)paren
(brace
id|err
(paren
l_string|&quot;can&squot;t restart %s, %d&quot;
comma
id|ohci-&gt;hcd.self.bus_name
comma
id|temp
)paren
suffix:semicolon
r_return
id|temp
suffix:semicolon
)brace
r_else
id|dbg
(paren
l_string|&quot;restart %s completed&quot;
comma
id|ohci-&gt;hcd.self.bus_name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|variable|hcd_name
r_static
r_const
r_char
id|hcd_name
(braket
)braket
op_assign
l_string|&quot;ohci-hcd&quot;
suffix:semicolon
DECL|macro|DRIVER_INFO
mdefine_line|#define DRIVER_INFO DRIVER_VERSION &quot; &quot; DRIVER_DESC
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_INFO
id|MODULE_DESCRIPTION
(paren
id|DRIVER_INFO
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
macro_line|#include &quot;ohci-pci.c&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SA1111
macro_line|#include &quot;ohci-sa1111.c&quot;
macro_line|#endif
macro_line|#if !(defined(CONFIG_PCI) || defined(CONFIG_SA1111))
macro_line|#error &quot;missing bus glue for ohci-hcd&quot;
macro_line|#endif
eof
