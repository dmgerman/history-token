multiline_comment|/*  &n;    UHCI HCD (Host Controller Driver) for USB, main part for HCD frame&n;   &n;    (c) 1999-2002 &n;    Georg Acher      +    Deti Fliegl    +    Thomas Sailer&n;    georg@acher.org      deti@fliegl.de   sailer@ife.ee.ethz.ch&n;   &n;    with the help of&n;    David Brownell, david-b@pacbell.net &n;    Adam Richter, adam@yggdrasil.com&n;    Roman Weissgaerber, weissg@vienna.at    &n;    &n;    HW-initalization based on material of&n;    Randy Dunlap + Johannes Erdfelt + Gregory P. Smith + Linus Torvalds &n;&n;    $Id: usb-uhci-hcd.c,v 1.1 2002/05/14 20:36:57 acher Exp $&n; */
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
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
DECL|macro|CONFIG_USB_DEBUG
mdefine_line|#define CONFIG_USB_DEBUG
macro_line|#ifdef CONFIG_USB_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#else
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#endif
macro_line|#include &quot;../core/hcd.h&quot;
macro_line|#include &quot;usb-uhci-hcd.h&quot;
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;$Revision: 1.1 $&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Georg Acher, Deti Fliegl, Thomas Sailer&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;USB 1.1 Universal Host Controller Interface driver (HCD)&quot;
multiline_comment|/*--------------------------------------------------------------------------*/
singleline_comment|// Values you may tweak
multiline_comment|/* CONFIG_USB_UHCI_HIGH_BANDWITH turns on Full Speed Bandwidth&n; * Reclamation: feature that puts loop on descriptor loop when&n; * there&squot;s some transfer going on. With FSBR, USB performance&n; * is optimal, but PCI can be slowed down up-to 5 times, slowing down&n; * system performance (eg. framebuffer devices).&n; */
DECL|macro|CONFIG_USB_UHCI_HIGH_BANDWIDTH
mdefine_line|#define CONFIG_USB_UHCI_HIGH_BANDWIDTH 
multiline_comment|/* *_DEPTH_FIRST puts descriptor in depth-first mode. This has&n; * somehow similar effect to FSBR (higher speed), but does not&n; * slow PCI down. OTOH USB performace is slightly slower than&n; * in FSBR case and single device could hog whole USB, starving&n; * other devices.&n; */
DECL|macro|USE_CTRL_DEPTH_FIRST
mdefine_line|#define USE_CTRL_DEPTH_FIRST 0  
singleline_comment|// 0: Breadth first, 1: Depth first
DECL|macro|USE_BULK_DEPTH_FIRST
mdefine_line|#define USE_BULK_DEPTH_FIRST 0  
singleline_comment|// 0: Breadth first, 1: Depth first
multiline_comment|/* Turning off both CONFIG_USB_UHCI_HIGH_BANDWITH and *_DEPTH_FIRST&n; * will lead to &lt;64KB/sec performance over USB for bulk transfers targeting&n; * one device&squot;s endpoint. You probably do not want to do that.&n; */
singleline_comment|// stop bandwidth reclamation after (roughly) 50ms
DECL|macro|IDLE_TIMEOUT
mdefine_line|#define IDLE_TIMEOUT  (HZ/20)
singleline_comment|// Suppress HC interrupt error messages for 5s
DECL|macro|ERROR_SUPPRESSION_TIME
mdefine_line|#define ERROR_SUPPRESSION_TIME (HZ*5)
singleline_comment|// HC watchdog
DECL|macro|WATCHDOG_TIMEOUT
mdefine_line|#define WATCHDOG_TIMEOUT (4*HZ)
DECL|macro|MAX_REANIMATIONS
mdefine_line|#define MAX_REANIMATIONS 5
DECL|macro|DEBUG_SYMBOLS
mdefine_line|#define DEBUG_SYMBOLS
macro_line|#ifdef DEBUG_SYMBOLS
macro_line|#ifndef EXPORT_SYMTAB
DECL|macro|EXPORT_SYMTAB
mdefine_line|#define EXPORT_SYMTAB
macro_line|#endif
macro_line|#endif
DECL|macro|queue_dbg
mdefine_line|#define queue_dbg dbg 
DECL|macro|async_dbg
mdefine_line|#define async_dbg dbg
DECL|macro|init_dbg
mdefine_line|#define init_dbg dbg
multiline_comment|/*--------------------------------------------------------------------------*/
singleline_comment|//                   NO serviceable parts below!
multiline_comment|/*--------------------------------------------------------------------------*/
DECL|variable|devs
r_static
r_struct
id|uhci
op_star
id|devs
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* used by userspace UHCI data structure dumper */
DECL|variable|uhci_devices
r_struct
id|uhci
op_star
op_star
id|uhci_devices
op_assign
op_amp
id|devs
suffix:semicolon
multiline_comment|/* A few prototypes */
r_static
r_int
id|uhci_urb_dequeue
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
suffix:semicolon
r_static
r_int
id|hc_reset
(paren
r_struct
id|uhci_hcd
op_star
id|uhci
)paren
suffix:semicolon
r_static
r_void
id|uhci_stop
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
suffix:semicolon
r_static
r_int
id|process_transfer
(paren
r_struct
id|uhci_hcd
op_star
id|uhci
comma
r_struct
id|urb
op_star
id|urb
comma
r_int
id|mode
)paren
suffix:semicolon
r_static
r_int
id|process_iso
(paren
r_struct
id|uhci_hcd
op_star
id|uhci
comma
r_struct
id|urb
op_star
id|urb
comma
r_int
id|mode
)paren
suffix:semicolon
r_static
r_int
id|process_interrupt
(paren
r_struct
id|uhci_hcd
op_star
id|uhci
comma
r_struct
id|urb
op_star
id|urb
comma
r_int
id|mode
)paren
suffix:semicolon
r_static
r_int
id|process_urb
(paren
r_struct
id|uhci_hcd
op_star
id|uhci
comma
r_struct
id|list_head
op_star
id|p
)paren
suffix:semicolon
r_static
r_int
id|uhci_urb_enqueue
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
suffix:semicolon
r_static
r_int
id|hc_defibrillate
c_func
(paren
r_struct
id|uhci_hcd
op_star
id|uhci
)paren
suffix:semicolon
r_static
r_int
id|hc_irq_run
c_func
(paren
r_struct
id|uhci_hcd
op_star
id|uhci
)paren
suffix:semicolon
macro_line|#include &quot;usb-uhci-dbg.c&quot;
macro_line|#include &quot;usb-uhci-mem.c&quot;
macro_line|#include &quot;usb-uhci-hub.c&quot;
macro_line|#include &quot;usb-uhci-q.c&quot;
DECL|macro|PIPESTRING
mdefine_line|#define PIPESTRING(x) (x==PIPE_BULK?&quot;Bulk&quot;:(x==PIPE_INTERRUPT?&quot;Interrupt&quot;:(x==PIPE_CONTROL?&quot;Control&quot;:&quot;Iso&quot;)))
multiline_comment|/*--------------------------------------------------------------------------*/
DECL|function|uhci_urb_enqueue
r_static
r_int
id|uhci_urb_enqueue
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
id|uhci_hcd
op_star
id|uhci
op_assign
id|hcd_to_uhci
(paren
id|hcd
)paren
suffix:semicolon
id|urb_priv_t
op_star
id|urb_priv
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
comma
id|type
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|urb
op_star
id|queued_urb
op_assign
l_int|NULL
suffix:semicolon
r_int
id|bustime
suffix:semicolon
id|type
op_assign
id|usb_pipetype
(paren
id|urb-&gt;pipe
)paren
suffix:semicolon
singleline_comment|//&t;err(&quot;submit_urb: scheduling %p (%s), tb %p, len %i&quot;, urb, 
singleline_comment|//&t;PIPESTRING(type),urb-&gt;transfer_buffer,urb-&gt;transfer_buffer_length);
r_if
c_cond
(paren
id|uhci-&gt;need_init
)paren
(brace
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
r_return
op_minus
id|ESHUTDOWN
suffix:semicolon
id|spin_lock_irqsave
(paren
op_amp
id|uhci-&gt;urb_list_lock
comma
id|flags
)paren
suffix:semicolon
id|ret
op_assign
id|hc_defibrillate
c_func
(paren
id|uhci
)paren
suffix:semicolon
id|spin_unlock_irqrestore
(paren
op_amp
id|uhci-&gt;urb_list_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|uhci-&gt;running
)paren
r_return
op_minus
id|ESHUTDOWN
suffix:semicolon
id|spin_lock_irqsave
(paren
op_amp
id|uhci-&gt;urb_list_lock
comma
id|flags
)paren
suffix:semicolon
id|queued_urb
op_assign
id|search_dev_ep
(paren
id|uhci
comma
id|urb
)paren
suffix:semicolon
singleline_comment|// returns already queued urb for that pipe
r_if
c_cond
(paren
id|queued_urb
)paren
(brace
id|queue_dbg
c_func
(paren
l_string|&quot;found bulk urb %p&bslash;n&quot;
comma
id|queued_urb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|type
op_ne
id|PIPE_BULK
)paren
op_logical_or
(paren
(paren
id|type
op_eq
id|PIPE_BULK
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|urb-&gt;transfer_flags
op_amp
id|USB_QUEUE_BULK
)paren
op_logical_or
op_logical_neg
(paren
id|queued_urb-&gt;transfer_flags
op_amp
id|USB_QUEUE_BULK
)paren
)paren
)paren
)paren
(brace
id|spin_unlock_irqrestore
(paren
op_amp
id|uhci-&gt;urb_list_lock
comma
id|flags
)paren
suffix:semicolon
id|err
c_func
(paren
l_string|&quot;ENXIO (%s)  %08x, flags %x, urb %p, burb %p, propably device driver bug...&quot;
comma
id|PIPESTRING
c_func
(paren
id|type
)paren
comma
id|urb-&gt;pipe
comma
id|urb-&gt;transfer_flags
comma
id|urb
comma
id|queued_urb
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
singleline_comment|// urb already queued
)brace
)brace
id|urb_priv
op_assign
id|uhci_alloc_priv
c_func
(paren
id|mem_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb_priv
)paren
(brace
id|spin_unlock_irqrestore
(paren
op_amp
id|uhci-&gt;urb_list_lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|urb-&gt;hcpriv
op_assign
id|urb_priv
suffix:semicolon
id|urb_priv-&gt;urb
op_assign
id|urb
suffix:semicolon
id|INIT_LIST_HEAD
(paren
op_amp
id|urb_priv-&gt;desc_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|PIPE_CONTROL
)paren
id|urb_priv-&gt;setup_packet_dma
op_assign
id|pci_map_single
c_func
(paren
id|uhci-&gt;uhci_pci
comma
id|urb-&gt;setup_packet
comma
r_sizeof
(paren
r_struct
id|usb_ctrlrequest
)paren
comma
id|PCI_DMA_TODEVICE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;transfer_buffer_length
)paren
id|urb_priv-&gt;transfer_buffer_dma
op_assign
id|pci_map_single
c_func
(paren
id|uhci-&gt;uhci_pci
comma
id|urb-&gt;transfer_buffer
comma
id|urb-&gt;transfer_buffer_length
comma
id|usb_pipein
c_func
(paren
id|urb-&gt;pipe
)paren
ques
c_cond
id|PCI_DMA_FROMDEVICE
suffix:colon
id|PCI_DMA_TODEVICE
)paren
suffix:semicolon
singleline_comment|// for bulk queuing it is essential that interrupts are disabled until submission
singleline_comment|// all other type enable interrupts again
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|PIPE_BULK
suffix:colon
r_if
c_cond
(paren
id|queued_urb
)paren
(brace
r_while
c_loop
(paren
(paren
(paren
id|urb_priv_t
op_star
)paren
id|queued_urb-&gt;hcpriv
)paren
op_member_access_from_pointer
id|next_queued_urb
)paren
singleline_comment|// find last queued bulk
id|queued_urb
op_assign
(paren
(paren
id|urb_priv_t
op_star
)paren
id|queued_urb-&gt;hcpriv
)paren
op_member_access_from_pointer
id|next_queued_urb
suffix:semicolon
(paren
(paren
id|urb_priv_t
op_star
)paren
id|queued_urb-&gt;hcpriv
)paren
op_member_access_from_pointer
id|next_queued_urb
op_assign
id|urb
suffix:semicolon
)brace
id|atomic_inc
(paren
op_amp
id|uhci-&gt;avoid_bulk
)paren
suffix:semicolon
id|ret
op_assign
id|uhci_submit_bulk_urb
(paren
id|uhci
comma
id|urb
comma
id|queued_urb
)paren
suffix:semicolon
id|atomic_dec
(paren
op_amp
id|uhci-&gt;avoid_bulk
)paren
suffix:semicolon
id|spin_unlock_irqrestore
(paren
op_amp
id|uhci-&gt;urb_list_lock
comma
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PIPE_ISOCHRONOUS
suffix:colon
id|spin_unlock_irqrestore
(paren
op_amp
id|uhci-&gt;urb_list_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;bandwidth
op_eq
l_int|0
)paren
(brace
multiline_comment|/* not yet checked/allocated */
id|bustime
op_assign
id|usb_check_bandwidth
(paren
id|urb-&gt;dev
comma
id|urb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bustime
OL
l_int|0
)paren
id|ret
op_assign
id|bustime
suffix:semicolon
r_else
(brace
id|ret
op_assign
id|uhci_submit_iso_urb
c_func
(paren
id|uhci
comma
id|urb
comma
id|mem_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|usb_claim_bandwidth
(paren
id|urb-&gt;dev
comma
id|urb
comma
id|bustime
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* bandwidth is already set */
id|ret
op_assign
id|uhci_submit_iso_urb
c_func
(paren
id|uhci
comma
id|urb
comma
id|mem_flags
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PIPE_INTERRUPT
suffix:colon
id|spin_unlock_irqrestore
(paren
op_amp
id|uhci-&gt;urb_list_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;bandwidth
op_eq
l_int|0
)paren
(brace
multiline_comment|/* not yet checked/allocated */
id|bustime
op_assign
id|usb_check_bandwidth
(paren
id|urb-&gt;dev
comma
id|urb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bustime
OL
l_int|0
)paren
id|ret
op_assign
id|bustime
suffix:semicolon
r_else
(brace
id|ret
op_assign
id|uhci_submit_int_urb
c_func
(paren
id|uhci
comma
id|urb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|usb_claim_bandwidth
(paren
id|urb-&gt;dev
comma
id|urb
comma
id|bustime
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* bandwidth is already set */
id|ret
op_assign
id|uhci_submit_int_urb
c_func
(paren
id|uhci
comma
id|urb
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PIPE_CONTROL
suffix:colon
id|spin_unlock_irqrestore
(paren
op_amp
id|uhci-&gt;urb_list_lock
comma
id|flags
)paren
suffix:semicolon
id|ret
op_assign
id|uhci_submit_control_urb
(paren
id|uhci
comma
id|urb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|spin_unlock_irqrestore
(paren
op_amp
id|uhci-&gt;urb_list_lock
comma
id|flags
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
singleline_comment|//&t;err(&quot;submit_urb: scheduled with ret: %d&quot;, ret);
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
id|uhci_free_priv
c_func
(paren
id|uhci
comma
id|urb
comma
id|urb_priv
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*--------------------------------------------------------------------------*/
DECL|function|uhci_urb_dequeue
r_static
r_int
id|uhci_urb_dequeue
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
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_struct
id|uhci_hcd
op_star
id|uhci
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;uhci_urb_dequeue called for %p&quot;
comma
id|urb
)paren
suffix:semicolon
id|uhci
op_assign
id|hcd_to_uhci
(paren
id|hcd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;transfer_flags
op_amp
id|USB_ASYNC_UNLINK
)paren
(brace
r_int
id|ret
suffix:semicolon
id|spin_lock_irqsave
(paren
op_amp
id|uhci-&gt;urb_list_lock
comma
id|flags
)paren
suffix:semicolon
id|ret
op_assign
id|uhci_unlink_urb_async
c_func
(paren
id|uhci
comma
id|urb
comma
id|UNLINK_ASYNC_STORE_URB
)paren
suffix:semicolon
id|spin_unlock_irqrestore
(paren
op_amp
id|uhci-&gt;urb_list_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_else
r_return
id|uhci_unlink_urb_sync
c_func
(paren
id|uhci
comma
id|urb
)paren
suffix:semicolon
)brace
multiline_comment|/*--------------------------------------------------------------------------*/
DECL|function|uhci_get_frame
r_static
r_int
id|uhci_get_frame
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
r_struct
id|uhci_hcd
op_star
id|uhci
op_assign
id|hcd_to_uhci
(paren
id|hcd
)paren
suffix:semicolon
r_return
id|inw
(paren
(paren
r_int
)paren
id|uhci-&gt;hcd.regs
op_plus
id|USBFRNUM
)paren
suffix:semicolon
)brace
multiline_comment|/*--------------------------------------------------------------------------*/
singleline_comment|//             Init and shutdown functions for HW 
multiline_comment|/*--------------------------------------------------------------------------*/
DECL|function|hc_reset
r_static
r_int
id|hc_reset
(paren
r_struct
id|uhci_hcd
op_star
id|uhci
)paren
(brace
r_int
r_int
id|io_addr
op_assign
(paren
r_int
)paren
id|uhci-&gt;hcd.regs
suffix:semicolon
id|uhci-&gt;apm_state
op_assign
l_int|0
suffix:semicolon
id|uhci-&gt;running
op_assign
l_int|0
suffix:semicolon
id|outw
(paren
id|USBCMD_GRESET
comma
id|io_addr
op_plus
id|USBCMD
)paren
suffix:semicolon
id|uhci_wait_ms
(paren
l_int|50
)paren
suffix:semicolon
multiline_comment|/* Global reset for 50ms */
id|outw
(paren
l_int|0
comma
id|io_addr
op_plus
id|USBCMD
)paren
suffix:semicolon
id|uhci_wait_ms
(paren
l_int|10
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*--------------------------------------------------------------------------*/
DECL|function|hc_irq_run
r_static
r_int
id|hc_irq_run
c_func
(paren
r_struct
id|uhci_hcd
op_star
id|uhci
)paren
(brace
r_int
r_int
id|io_addr
op_assign
(paren
r_int
)paren
id|uhci-&gt;hcd.regs
suffix:semicolon
multiline_comment|/* Turn on all interrupts */
id|outw
(paren
id|USBINTR_TIMEOUT
op_or
id|USBINTR_RESUME
op_or
id|USBINTR_IOC
op_or
id|USBINTR_SP
comma
id|io_addr
op_plus
id|USBINTR
)paren
suffix:semicolon
multiline_comment|/* Start at frame 0 */
id|outw
(paren
l_int|0
comma
id|io_addr
op_plus
id|USBFRNUM
)paren
suffix:semicolon
id|outl
(paren
id|uhci-&gt;framelist_dma
comma
id|io_addr
op_plus
id|USBFLBASEADD
)paren
suffix:semicolon
multiline_comment|/* Run and mark it configured with a 64-byte max packet */
id|outw
(paren
id|USBCMD_RS
op_or
id|USBCMD_CF
op_or
id|USBCMD_MAXP
comma
id|io_addr
op_plus
id|USBCMD
)paren
suffix:semicolon
id|uhci-&gt;apm_state
op_assign
l_int|1
suffix:semicolon
id|uhci-&gt;running
op_assign
l_int|1
suffix:semicolon
id|uhci-&gt;last_hcd_irq
op_assign
id|jiffies
op_plus
l_int|4
op_star
id|HZ
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*--------------------------------------------------------------------------*/
DECL|function|hc_start
r_static
r_int
id|hc_start
(paren
r_struct
id|uhci_hcd
op_star
id|uhci
)paren
(brace
r_int
r_int
id|io_addr
op_assign
(paren
r_int
)paren
id|uhci-&gt;hcd.regs
suffix:semicolon
r_int
id|timeout
op_assign
l_int|10
suffix:semicolon
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
id|init_dbg
c_func
(paren
l_string|&quot;hc_start uhci %p&quot;
comma
id|uhci
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Reset the HC - this will force us to get a&n;&t; * new notification of any already connected&n;&t; * ports due to the virtual disconnect that it&n;&t; * implies.&n;&t; */
id|outw
(paren
id|USBCMD_HCRESET
comma
id|io_addr
op_plus
id|USBCMD
)paren
suffix:semicolon
r_while
c_loop
(paren
id|inw
(paren
id|io_addr
op_plus
id|USBCMD
)paren
op_amp
id|USBCMD_HCRESET
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|timeout
)paren
(brace
id|err
c_func
(paren
l_string|&quot;USBCMD_HCRESET timed out!&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|hc_irq_run
c_func
(paren
id|uhci
)paren
suffix:semicolon
multiline_comment|/* connect the virtual root hub */
id|uhci-&gt;hcd.self.root_hub
op_assign
id|udev
op_assign
id|usb_alloc_dev
(paren
l_int|NULL
comma
op_amp
id|uhci-&gt;hcd.self
)paren
suffix:semicolon
id|uhci-&gt;hcd.state
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
id|uhci-&gt;running
op_assign
l_int|0
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
op_amp
id|uhci-&gt;hcd.pdev-&gt;dev
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
id|uhci-&gt;running
op_assign
l_int|0
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
multiline_comment|/*--------------------------------------------------------------------------*/
singleline_comment|// Start up UHCI, find ports, init DMA lists
DECL|function|uhci_start
r_static
r_int
id|__devinit
id|uhci_start
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
r_struct
id|uhci_hcd
op_star
id|uhci
op_assign
id|hcd_to_uhci
(paren
id|hcd
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
id|io_addr
op_assign
(paren
r_int
)paren
id|hcd-&gt;regs
comma
id|io_size
op_assign
l_int|0x20
suffix:semicolon
singleline_comment|// FIXME
id|init_dbg
c_func
(paren
l_string|&quot;uhci_start hcd %p uhci %p, pdev %p&quot;
comma
id|hcd
comma
id|uhci
comma
id|hcd-&gt;pdev
)paren
suffix:semicolon
multiline_comment|/* disable legacy emulation, Linux takes over... */
id|pci_write_config_word
(paren
id|hcd-&gt;pdev
comma
id|USBLEGSUP
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* UHCI specs says devices must have 2 ports, but goes on to say */
multiline_comment|/* they may have more but give no way to determine how many they */
multiline_comment|/* have, so default to 2 */
multiline_comment|/* According to the UHCI spec, Bit 7 is always set to 1. So we try */
multiline_comment|/* to use this to our advantage */
r_for
c_loop
(paren
id|uhci-&gt;maxports
op_assign
l_int|0
suffix:semicolon
id|uhci-&gt;maxports
OL
(paren
id|io_size
op_minus
l_int|0x10
)paren
op_div
l_int|2
suffix:semicolon
id|uhci-&gt;maxports
op_increment
)paren
(brace
r_int
r_int
id|portstatus
suffix:semicolon
id|portstatus
op_assign
id|inw
(paren
id|io_addr
op_plus
l_int|0x10
op_plus
(paren
id|uhci-&gt;maxports
op_star
l_int|2
)paren
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;port %i, adr %x status %x&quot;
comma
id|uhci-&gt;maxports
comma
id|io_addr
op_plus
l_int|0x10
op_plus
(paren
id|uhci-&gt;maxports
op_star
l_int|2
)paren
comma
id|portstatus
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|portstatus
op_amp
l_int|0x0080
)paren
)paren
r_break
suffix:semicolon
)brace
id|warn
c_func
(paren
l_string|&quot;Detected %d ports&quot;
comma
id|uhci-&gt;maxports
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uhci-&gt;maxports
template_param
l_int|8
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;Port count misdetected, forcing to 2 ports&quot;
)paren
suffix:semicolon
id|uhci-&gt;maxports
op_assign
l_int|2
suffix:semicolon
)brace
id|ret
op_assign
id|init_skel
c_func
(paren
id|uhci
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|hc_reset
(paren
id|uhci
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hc_start
(paren
id|uhci
)paren
OL
l_int|0
)paren
(brace
id|err
(paren
l_string|&quot;can&squot;t start %s&quot;
comma
id|uhci-&gt;hcd.self.bus_name
)paren
suffix:semicolon
id|uhci_stop
(paren
id|hcd
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
singleline_comment|// Enable PIRQ
id|pci_write_config_word
(paren
id|hcd-&gt;pdev
comma
id|USBLEGSUP
comma
id|USBLEGSUP_DEFAULT
)paren
suffix:semicolon
id|set_td_ioc
c_func
(paren
id|uhci-&gt;td128ms
)paren
suffix:semicolon
singleline_comment|// start watchdog interrupt
id|uhci-&gt;last_hcd_irq
op_assign
id|jiffies
op_plus
l_int|5
op_star
id|HZ
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*--------------------------------------------------------------------------*/
DECL|function|uhci_free_config
r_static
r_void
id|uhci_free_config
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
id|dbg
c_func
(paren
l_string|&quot;uhci_free_config for dev %p&quot;
comma
id|udev
)paren
suffix:semicolon
id|uhci_unlink_urbs
(paren
id|hcd_to_uhci
(paren
id|hcd
)paren
comma
id|udev
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// Forced unlink of remaining URBs
)brace
multiline_comment|/*--------------------------------------------------------------------------*/
DECL|function|uhci_stop
r_static
r_void
id|uhci_stop
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
r_struct
id|uhci_hcd
op_star
id|uhci
op_assign
id|hcd_to_uhci
(paren
id|hcd
)paren
suffix:semicolon
id|init_dbg
c_func
(paren
l_string|&quot;%s: stop controller&quot;
comma
id|hcd-&gt;bus_name
)paren
suffix:semicolon
id|uhci-&gt;running
op_assign
l_int|0
suffix:semicolon
id|hc_reset
(paren
id|uhci
)paren
suffix:semicolon
id|wait_ms
(paren
l_int|1
)paren
suffix:semicolon
id|uhci_unlink_urbs
(paren
id|uhci
comma
l_int|0
comma
id|CLEAN_FORCED
)paren
suffix:semicolon
singleline_comment|// Forced unlink of remaining URBs
id|uhci_cleanup_unlink
(paren
id|uhci
comma
id|CLEAN_FORCED
)paren
suffix:semicolon
singleline_comment|// force cleanup of async killed URBs
id|cleanup_skel
(paren
id|uhci
)paren
suffix:semicolon
)brace
multiline_comment|/*--------------------------------------------------------------------------*/
singleline_comment|//                  UHCI INTERRUPT PROCESSING
multiline_comment|/*--------------------------------------------------------------------------*/
DECL|function|uhci_irq
r_static
r_void
id|uhci_irq
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
r_struct
id|uhci_hcd
op_star
id|uhci
op_assign
id|hcd_to_uhci
(paren
id|hcd
)paren
suffix:semicolon
r_int
r_int
id|io_addr
op_assign
(paren
r_int
)paren
id|hcd-&gt;regs
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
r_struct
id|list_head
op_star
id|p
comma
op_star
id|p2
suffix:semicolon
r_int
id|restarts
comma
id|work_done
suffix:semicolon
multiline_comment|/*&n;&t; * Read the interrupt status, and write it back to clear the&n;&t; * interrupt cause&n;&t; */
id|status
op_assign
id|inw
(paren
id|io_addr
op_plus
id|USBSTS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
multiline_comment|/* shared interrupt, not mine */
r_return
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;interrupt&quot;
)paren
suffix:semicolon
id|uhci-&gt;last_hcd_irq
op_assign
id|jiffies
suffix:semicolon
singleline_comment|// for watchdog
r_if
c_cond
(paren
id|status
op_ne
l_int|1
)paren
(brace
singleline_comment|// Avoid too much error messages at a time
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|uhci-&gt;last_error_time
op_plus
id|ERROR_SUPPRESSION_TIME
)paren
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;interrupt, status %x, frame# %i&quot;
comma
id|status
comma
id|UHCI_GET_CURRENT_FRAME
c_func
(paren
id|uhci
)paren
)paren
suffix:semicolon
id|uhci-&gt;last_error_time
op_assign
id|jiffies
suffix:semicolon
)brace
singleline_comment|// remove host controller halted state
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0x20
)paren
op_logical_and
(paren
id|uhci-&gt;running
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;Host controller halted, waiting for timeout.&quot;
)paren
suffix:semicolon
singleline_comment|//&t;&t;&t;outw (USBCMD_RS | inw(io_addr + USBCMD), io_addr + USBCMD);
)brace
singleline_comment|//uhci_show_status (s);
)brace
multiline_comment|/*&n;&t; * traverse the list in *reverse* direction, because new entries&n;&t; * may be added at the end.&n;&t; * also, because process_urb may unlink the current urb,&n;&t; * we need to advance the list before&n;&t; * New: check for max. workload and restart count&n;&t; */
id|spin_lock
(paren
op_amp
id|uhci-&gt;urb_list_lock
)paren
suffix:semicolon
id|restarts
op_assign
l_int|0
suffix:semicolon
id|work_done
op_assign
l_int|0
suffix:semicolon
id|restart
suffix:colon
id|uhci-&gt;unlink_urb_done
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
id|uhci-&gt;urb_list.prev
suffix:semicolon
r_while
c_loop
(paren
id|p
op_ne
op_amp
id|uhci-&gt;urb_list
op_logical_and
(paren
id|work_done
OL
l_int|1024
)paren
)paren
(brace
id|p2
op_assign
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;prev
suffix:semicolon
id|process_urb
(paren
id|uhci
comma
id|p2
)paren
suffix:semicolon
id|work_done
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|uhci-&gt;unlink_urb_done
)paren
(brace
id|uhci-&gt;unlink_urb_done
op_assign
l_int|0
suffix:semicolon
id|restarts
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|restarts
OL
l_int|16
)paren
singleline_comment|// avoid endless restarts
r_goto
id|restart
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|uhci-&gt;timeout_check
op_plus
(paren
id|HZ
op_div
l_int|30
)paren
)paren
)paren
id|uhci_check_timeouts
c_func
(paren
id|uhci
)paren
suffix:semicolon
id|clean_descs
c_func
(paren
id|uhci
comma
id|CLEAN_NOT_FORCED
)paren
suffix:semicolon
id|uhci_cleanup_unlink
c_func
(paren
id|uhci
comma
id|CLEAN_NOT_FORCED
)paren
suffix:semicolon
id|uhci_switch_timer_int
c_func
(paren
id|uhci
)paren
suffix:semicolon
id|spin_unlock
(paren
op_amp
id|uhci-&gt;urb_list_lock
)paren
suffix:semicolon
id|outw
(paren
id|status
comma
id|io_addr
op_plus
id|USBSTS
)paren
suffix:semicolon
singleline_comment|//dbg(&quot;uhci_interrupt: done&quot;);
)brace
multiline_comment|/*--------------------------------------------------------------------------*/
singleline_comment|//             POWER MANAGEMENT
macro_line|#ifdef&t;CONFIG_PM
DECL|function|uhci_suspend
r_static
r_int
id|uhci_suspend
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
id|u32
id|state
)paren
(brace
r_struct
id|uhci_hcd
op_star
id|uhci
op_assign
id|hcd_to_uhci
(paren
id|hcd
)paren
suffix:semicolon
id|hc_reset
c_func
(paren
id|uhci
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*--------------------------------------------------------------------------*/
DECL|function|uhci_resume
r_static
r_int
id|uhci_resume
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
r_struct
id|uhci_hcd
op_star
id|uhci
op_assign
id|hcd_to_uhci
(paren
id|hcd
)paren
suffix:semicolon
id|hc_start
c_func
(paren
id|uhci
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*--------------------------------------------------------------------------*/
DECL|variable|hcd_name
r_static
r_const
r_char
id|hcd_name
(braket
)braket
op_assign
l_string|&quot;usb-uhci-hcd&quot;
suffix:semicolon
DECL|variable|uhci_driver
r_static
r_const
r_struct
id|hc_driver
id|uhci_driver
op_assign
(brace
id|description
suffix:colon
id|hcd_name
comma
singleline_comment|// generic hardware linkage
id|irq
suffix:colon
id|uhci_irq
comma
id|flags
suffix:colon
id|HCD_USB11
comma
singleline_comment|// basic lifecycle operations
id|start
suffix:colon
id|uhci_start
comma
macro_line|#ifdef&t;CONFIG_PM
id|suspend
suffix:colon
id|uhci_suspend
comma
id|resume
suffix:colon
id|uhci_resume
comma
macro_line|#endif
id|stop
suffix:colon
id|uhci_stop
comma
singleline_comment|// memory lifecycle (except per-request)
id|hcd_alloc
suffix:colon
id|uhci_hcd_alloc
comma
id|hcd_free
suffix:colon
id|uhci_hcd_free
comma
singleline_comment|// managing i/o requests and associated device resources
id|urb_enqueue
suffix:colon
id|uhci_urb_enqueue
comma
id|urb_dequeue
suffix:colon
id|uhci_urb_dequeue
comma
id|free_config
suffix:colon
id|uhci_free_config
comma
singleline_comment|// scheduling support
id|get_frame_number
suffix:colon
id|uhci_get_frame
comma
singleline_comment|// root hub support
id|hub_status_data
suffix:colon
id|uhci_hub_status_data
comma
id|hub_control
suffix:colon
id|uhci_hub_control
comma
)brace
suffix:semicolon
DECL|macro|DRIVER_INFO
mdefine_line|#define DRIVER_INFO DRIVER_VERSION &quot; &quot; DRIVER_DESC
id|EXPORT_NO_SYMBOLS
suffix:semicolon
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
DECL|variable|pci_ids
r_static
r_const
r_struct
id|pci_device_id
id|__devinitdata
id|pci_ids
(braket
)braket
op_assign
(brace
(brace
multiline_comment|/* handle any USB UHCI controller */
r_class
suffix:colon
(paren
id|PCI_CLASS_SERIAL_USB
op_lshift
l_int|8
)paren
op_or
l_int|0x00
comma
id|class_mask
suffix:colon
op_complement
l_int|0
comma
id|driver_data
suffix:colon
(paren
r_int
r_int
)paren
op_amp
id|uhci_driver
comma
multiline_comment|/* no matter who makes it */
id|vendor
suffix:colon
id|PCI_ANY_ID
comma
id|device
suffix:colon
id|PCI_ANY_ID
comma
id|subvendor
suffix:colon
id|PCI_ANY_ID
comma
id|subdevice
suffix:colon
id|PCI_ANY_ID
comma
)brace
comma
(brace
multiline_comment|/* end: all zeroes */
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|pci
comma
id|pci_ids
)paren
suffix:semicolon
multiline_comment|/* pci driver glue; this is a &quot;new style&quot; PCI driver module */
DECL|variable|uhci_pci_driver
r_static
r_struct
id|pci_driver
id|uhci_pci_driver
op_assign
(brace
id|name
suffix:colon
(paren
r_char
op_star
)paren
id|hcd_name
comma
id|id_table
suffix:colon
id|pci_ids
comma
id|probe
suffix:colon
id|usb_hcd_pci_probe
comma
id|remove
suffix:colon
id|usb_hcd_pci_remove
comma
macro_line|#ifdef&t;CONFIG_PM
id|suspend
suffix:colon
id|usb_hcd_pci_suspend
comma
id|resume
suffix:colon
id|usb_hcd_pci_resume
comma
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|uhci_hcd_init
r_static
r_int
id|__init
id|uhci_hcd_init
(paren
r_void
)paren
(brace
id|init_dbg
(paren
id|DRIVER_INFO
)paren
suffix:semicolon
id|init_dbg
(paren
l_string|&quot;block sizes: hq %d td %d&quot;
comma
r_sizeof
(paren
r_struct
id|qh
)paren
comma
r_sizeof
(paren
r_struct
id|td
)paren
)paren
suffix:semicolon
r_return
id|pci_module_init
(paren
op_amp
id|uhci_pci_driver
)paren
suffix:semicolon
)brace
DECL|function|uhci_hcd_cleanup
r_static
r_void
id|__exit
id|uhci_hcd_cleanup
(paren
r_void
)paren
(brace
id|pci_unregister_driver
(paren
op_amp
id|uhci_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|uhci_hcd_init
id|module_init
(paren
id|uhci_hcd_init
)paren
suffix:semicolon
DECL|variable|uhci_hcd_cleanup
id|module_exit
(paren
id|uhci_hcd_cleanup
)paren
suffix:semicolon
eof
