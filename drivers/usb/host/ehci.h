multiline_comment|/*&n; * Copyright (c) 2001-2002 by David Brownell&n; * &n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY&n; * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; * for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __LINUX_EHCI_HCD_H
DECL|macro|__LINUX_EHCI_HCD_H
mdefine_line|#define __LINUX_EHCI_HCD_H
multiline_comment|/* definitions used for the EHCI driver */
multiline_comment|/* statistics can be kept for for tuning/monitoring */
DECL|struct|ehci_stats
r_struct
id|ehci_stats
(brace
multiline_comment|/* irq usage */
DECL|member|normal
r_int
r_int
id|normal
suffix:semicolon
DECL|member|error
r_int
r_int
id|error
suffix:semicolon
DECL|member|reclaim
r_int
r_int
id|reclaim
suffix:semicolon
DECL|member|lost_iaa
r_int
r_int
id|lost_iaa
suffix:semicolon
multiline_comment|/* termination of urbs from core */
DECL|member|complete
r_int
r_int
id|complete
suffix:semicolon
DECL|member|unlink
r_int
r_int
id|unlink
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ehci_hcd-&gt;lock guards shared data against other CPUs:&n; *   ehci_hcd:&t;async, reclaim, periodic (and shadow), ...&n; *   usb_host_endpoint: hcpriv&n; *   ehci_qh:&t;qh_next, qtd_list&n; *   ehci_qtd:&t;qtd_list&n; *&n; * Also, hold this lock when talking to HC registers or&n; * when updating hw_* fields in shared qh/qtd/... structures.&n; */
DECL|macro|EHCI_MAX_ROOT_PORTS
mdefine_line|#define&t;EHCI_MAX_ROOT_PORTS&t;15&t;&t;/* see HCS_N_PORTS */
DECL|struct|ehci_hcd
r_struct
id|ehci_hcd
(brace
multiline_comment|/* one per controller */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* async schedule support */
DECL|member|async
r_struct
id|ehci_qh
op_star
id|async
suffix:semicolon
DECL|member|reclaim
r_struct
id|ehci_qh
op_star
id|reclaim
suffix:semicolon
DECL|member|reclaim_ready
r_int
id|reclaim_ready
suffix:colon
l_int|1
suffix:semicolon
DECL|member|scanning
r_int
id|scanning
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* periodic schedule support */
DECL|macro|DEFAULT_I_TDPS
mdefine_line|#define&t;DEFAULT_I_TDPS&t;&t;1024&t;&t;/* some HCs can do less */
DECL|member|periodic_size
r_int
id|periodic_size
suffix:semicolon
DECL|member|periodic
id|__le32
op_star
id|periodic
suffix:semicolon
multiline_comment|/* hw periodic table */
DECL|member|periodic_dma
id|dma_addr_t
id|periodic_dma
suffix:semicolon
DECL|member|i_thresh
r_int
id|i_thresh
suffix:semicolon
multiline_comment|/* uframes HC might cache */
DECL|member|pshadow
r_union
id|ehci_shadow
op_star
id|pshadow
suffix:semicolon
multiline_comment|/* mirror hw periodic table */
DECL|member|next_uframe
r_int
id|next_uframe
suffix:semicolon
multiline_comment|/* scan periodic, start here */
DECL|member|periodic_sched
r_int
id|periodic_sched
suffix:semicolon
multiline_comment|/* periodic activity count */
multiline_comment|/* per root hub port */
DECL|member|reset_done
r_int
r_int
id|reset_done
(braket
id|EHCI_MAX_ROOT_PORTS
)braket
suffix:semicolon
multiline_comment|/* per-HC memory pools (could be per-bus, but ...) */
DECL|member|qh_pool
r_struct
id|dma_pool
op_star
id|qh_pool
suffix:semicolon
multiline_comment|/* qh per active urb */
DECL|member|qtd_pool
r_struct
id|dma_pool
op_star
id|qtd_pool
suffix:semicolon
multiline_comment|/* one or more per qh */
DECL|member|itd_pool
r_struct
id|dma_pool
op_star
id|itd_pool
suffix:semicolon
multiline_comment|/* itd per iso urb */
DECL|member|sitd_pool
r_struct
id|dma_pool
op_star
id|sitd_pool
suffix:semicolon
multiline_comment|/* sitd per split iso urb */
DECL|member|watchdog
r_struct
id|timer_list
id|watchdog
suffix:semicolon
DECL|member|reboot_notifier
r_struct
id|notifier_block
id|reboot_notifier
suffix:semicolon
DECL|member|actions
r_int
r_int
id|actions
suffix:semicolon
DECL|member|stamp
r_int
id|stamp
suffix:semicolon
DECL|member|next_statechange
r_int
r_int
id|next_statechange
suffix:semicolon
DECL|member|command
id|u32
id|command
suffix:semicolon
DECL|member|is_arc_rh_tt
r_int
id|is_arc_rh_tt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ARC roothub with TT */
multiline_comment|/* glue to PCI and HCD framework */
DECL|member|caps
r_struct
id|ehci_caps
id|__iomem
op_star
id|caps
suffix:semicolon
DECL|member|regs
r_struct
id|ehci_regs
id|__iomem
op_star
id|regs
suffix:semicolon
DECL|member|hcs_params
id|__u32
id|hcs_params
suffix:semicolon
multiline_comment|/* cached register copy */
multiline_comment|/* irq statistics */
macro_line|#ifdef EHCI_STATS
DECL|member|stats
r_struct
id|ehci_stats
id|stats
suffix:semicolon
DECL|macro|COUNT
macro_line|#&t;define COUNT(x) do { (x)++; } while (0)
macro_line|#else
DECL|macro|COUNT
macro_line|#&t;define COUNT(x) do {} while (0)
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* convert between an HCD pointer and the corresponding EHCI_HCD */
DECL|function|hcd_to_ehci
r_static
r_inline
r_struct
id|ehci_hcd
op_star
id|hcd_to_ehci
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
r_return
(paren
r_struct
id|ehci_hcd
op_star
)paren
(paren
id|hcd-&gt;hcd_priv
)paren
suffix:semicolon
)brace
DECL|function|ehci_to_hcd
r_static
r_inline
r_struct
id|usb_hcd
op_star
id|ehci_to_hcd
(paren
r_struct
id|ehci_hcd
op_star
id|ehci
)paren
(brace
r_return
id|container_of
(paren
(paren
r_void
op_star
)paren
id|ehci
comma
r_struct
id|usb_hcd
comma
id|hcd_priv
)paren
suffix:semicolon
)brace
DECL|enum|ehci_timer_action
r_enum
id|ehci_timer_action
(brace
DECL|enumerator|TIMER_IO_WATCHDOG
id|TIMER_IO_WATCHDOG
comma
DECL|enumerator|TIMER_IAA_WATCHDOG
id|TIMER_IAA_WATCHDOG
comma
DECL|enumerator|TIMER_ASYNC_SHRINK
id|TIMER_ASYNC_SHRINK
comma
DECL|enumerator|TIMER_ASYNC_OFF
id|TIMER_ASYNC_OFF
comma
)brace
suffix:semicolon
r_static
r_inline
r_void
DECL|function|timer_action_done
id|timer_action_done
(paren
r_struct
id|ehci_hcd
op_star
id|ehci
comma
r_enum
id|ehci_timer_action
id|action
)paren
(brace
id|clear_bit
(paren
id|action
comma
op_amp
id|ehci-&gt;actions
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|timer_action
id|timer_action
(paren
r_struct
id|ehci_hcd
op_star
id|ehci
comma
r_enum
id|ehci_timer_action
id|action
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
(paren
id|action
comma
op_amp
id|ehci-&gt;actions
)paren
)paren
(brace
r_int
r_int
id|t
suffix:semicolon
r_switch
c_cond
(paren
id|action
)paren
(brace
r_case
id|TIMER_IAA_WATCHDOG
suffix:colon
id|t
op_assign
id|EHCI_IAA_JIFFIES
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIMER_IO_WATCHDOG
suffix:colon
id|t
op_assign
id|EHCI_IO_JIFFIES
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIMER_ASYNC_OFF
suffix:colon
id|t
op_assign
id|EHCI_ASYNC_JIFFIES
suffix:semicolon
r_break
suffix:semicolon
singleline_comment|// case TIMER_ASYNC_SHRINK:
r_default
suffix:colon
id|t
op_assign
id|EHCI_SHRINK_JIFFIES
suffix:semicolon
r_break
suffix:semicolon
)brace
id|t
op_add_assign
id|jiffies
suffix:semicolon
singleline_comment|// all timings except IAA watchdog can be overridden.
singleline_comment|// async queue SHRINK often precedes IAA.  while it&squot;s ready
singleline_comment|// to go OFF neither can matter, and afterwards the IO
singleline_comment|// watchdog stops unless there&squot;s still periodic traffic.
r_if
c_cond
(paren
id|action
op_ne
id|TIMER_IAA_WATCHDOG
op_logical_and
id|t
OG
id|ehci-&gt;watchdog.expires
op_logical_and
id|timer_pending
(paren
op_amp
id|ehci-&gt;watchdog
)paren
)paren
r_return
suffix:semicolon
id|mod_timer
(paren
op_amp
id|ehci-&gt;watchdog
comma
id|t
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* EHCI register interface, corresponds to EHCI Revision 0.95 specification */
multiline_comment|/* Section 2.2 Host Controller Capability Registers */
DECL|struct|ehci_caps
r_struct
id|ehci_caps
(brace
multiline_comment|/* these fields are specified as 8 and 16 bit registers,&n;&t; * but some hosts can&squot;t perform 8 or 16 bit PCI accesses.&n;&t; */
DECL|member|hc_capbase
id|u32
id|hc_capbase
suffix:semicolon
DECL|macro|HC_LENGTH
mdefine_line|#define HC_LENGTH(p)&t;&t;(((p)&gt;&gt;00)&amp;0x00ff)&t;/* bits 7:0 */
DECL|macro|HC_VERSION
mdefine_line|#define HC_VERSION(p)&t;&t;(((p)&gt;&gt;16)&amp;0xffff)&t;/* bits 31:16 */
DECL|member|hcs_params
id|u32
id|hcs_params
suffix:semicolon
multiline_comment|/* HCSPARAMS - offset 0x4 */
DECL|macro|HCS_DEBUG_PORT
mdefine_line|#define HCS_DEBUG_PORT(p)&t;(((p)&gt;&gt;20)&amp;0xf)&t;/* bits 23:20, debug port? */
DECL|macro|HCS_INDICATOR
mdefine_line|#define HCS_INDICATOR(p)&t;((p)&amp;(1 &lt;&lt; 16))&t;/* true: has port indicators */
DECL|macro|HCS_N_CC
mdefine_line|#define HCS_N_CC(p)&t;&t;(((p)&gt;&gt;12)&amp;0xf)&t;/* bits 15:12, #companion HCs */
DECL|macro|HCS_N_PCC
mdefine_line|#define HCS_N_PCC(p)&t;&t;(((p)&gt;&gt;8)&amp;0xf)&t;/* bits 11:8, ports per CC */
DECL|macro|HCS_PORTROUTED
mdefine_line|#define HCS_PORTROUTED(p)&t;((p)&amp;(1 &lt;&lt; 7))&t;/* true: port routing */ 
DECL|macro|HCS_PPC
mdefine_line|#define HCS_PPC(p)&t;&t;((p)&amp;(1 &lt;&lt; 4))&t;/* true: port power control */ 
DECL|macro|HCS_N_PORTS
mdefine_line|#define HCS_N_PORTS(p)&t;&t;(((p)&gt;&gt;0)&amp;0xf)&t;/* bits 3:0, ports on HC */
DECL|member|hcc_params
id|u32
id|hcc_params
suffix:semicolon
multiline_comment|/* HCCPARAMS - offset 0x8 */
DECL|macro|HCC_EXT_CAPS
mdefine_line|#define HCC_EXT_CAPS(p)&t;&t;(((p)&gt;&gt;8)&amp;0xff)&t;/* for pci extended caps */
DECL|macro|HCC_ISOC_CACHE
mdefine_line|#define HCC_ISOC_CACHE(p)       ((p)&amp;(1 &lt;&lt; 7))  /* true: can cache isoc frame */
DECL|macro|HCC_ISOC_THRES
mdefine_line|#define HCC_ISOC_THRES(p)       (((p)&gt;&gt;4)&amp;0x7)  /* bits 6:4, uframes cached */
DECL|macro|HCC_CANPARK
mdefine_line|#define HCC_CANPARK(p)&t;&t;((p)&amp;(1 &lt;&lt; 2))  /* true: can park on async qh */
DECL|macro|HCC_PGM_FRAMELISTLEN
mdefine_line|#define HCC_PGM_FRAMELISTLEN(p) ((p)&amp;(1 &lt;&lt; 1))  /* true: periodic_size changes*/
DECL|macro|HCC_64BIT_ADDR
mdefine_line|#define HCC_64BIT_ADDR(p)       ((p)&amp;(1))       /* true: can use 64-bit addr */
DECL|member|portroute
id|u8
id|portroute
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* nibbles for routing - offset 0xC */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Section 2.3 Host Controller Operational Registers */
DECL|struct|ehci_regs
r_struct
id|ehci_regs
(brace
multiline_comment|/* USBCMD: offset 0x00 */
DECL|member|command
id|u32
id|command
suffix:semicolon
multiline_comment|/* 23:16 is r/w intr rate, in microframes; default &quot;8&quot; == 1/msec */
DECL|macro|CMD_PARK
mdefine_line|#define CMD_PARK&t;(1&lt;&lt;11)&t;&t;/* enable &quot;park&quot; on async qh */
DECL|macro|CMD_PARK_CNT
mdefine_line|#define CMD_PARK_CNT(c)&t;(((c)&gt;&gt;8)&amp;3)&t;/* how many transfers to park for */
DECL|macro|CMD_LRESET
mdefine_line|#define CMD_LRESET&t;(1&lt;&lt;7)&t;&t;/* partial reset (no ports, etc) */
DECL|macro|CMD_IAAD
mdefine_line|#define CMD_IAAD&t;(1&lt;&lt;6)&t;&t;/* &quot;doorbell&quot; interrupt async advance */
DECL|macro|CMD_ASE
mdefine_line|#define CMD_ASE&t;&t;(1&lt;&lt;5)&t;&t;/* async schedule enable */
DECL|macro|CMD_PSE
mdefine_line|#define CMD_PSE  &t;(1&lt;&lt;4)&t;&t;/* periodic schedule enable */
multiline_comment|/* 3:2 is periodic frame list size */
DECL|macro|CMD_RESET
mdefine_line|#define CMD_RESET&t;(1&lt;&lt;1)&t;&t;/* reset HC not bus */
DECL|macro|CMD_RUN
mdefine_line|#define CMD_RUN&t;&t;(1&lt;&lt;0)&t;&t;/* start/stop HC */
multiline_comment|/* USBSTS: offset 0x04 */
DECL|member|status
id|u32
id|status
suffix:semicolon
DECL|macro|STS_ASS
mdefine_line|#define STS_ASS&t;&t;(1&lt;&lt;15)&t;&t;/* Async Schedule Status */
DECL|macro|STS_PSS
mdefine_line|#define STS_PSS&t;&t;(1&lt;&lt;14)&t;&t;/* Periodic Schedule Status */
DECL|macro|STS_RECL
mdefine_line|#define STS_RECL&t;(1&lt;&lt;13)&t;&t;/* Reclamation */
DECL|macro|STS_HALT
mdefine_line|#define STS_HALT&t;(1&lt;&lt;12)&t;&t;/* Not running (any reason) */
multiline_comment|/* some bits reserved */
multiline_comment|/* these STS_* flags are also intr_enable bits (USBINTR) */
DECL|macro|STS_IAA
mdefine_line|#define STS_IAA&t;&t;(1&lt;&lt;5)&t;&t;/* Interrupted on async advance */
DECL|macro|STS_FATAL
mdefine_line|#define STS_FATAL&t;(1&lt;&lt;4)&t;&t;/* such as some PCI access errors */
DECL|macro|STS_FLR
mdefine_line|#define STS_FLR&t;&t;(1&lt;&lt;3)&t;&t;/* frame list rolled over */
DECL|macro|STS_PCD
mdefine_line|#define STS_PCD&t;&t;(1&lt;&lt;2)&t;&t;/* port change detect */
DECL|macro|STS_ERR
mdefine_line|#define STS_ERR&t;&t;(1&lt;&lt;1)&t;&t;/* &quot;error&quot; completion (overflow, ...) */
DECL|macro|STS_INT
mdefine_line|#define STS_INT&t;&t;(1&lt;&lt;0)&t;&t;/* &quot;normal&quot; completion (short, ...) */
multiline_comment|/* USBINTR: offset 0x08 */
DECL|member|intr_enable
id|u32
id|intr_enable
suffix:semicolon
multiline_comment|/* FRINDEX: offset 0x0C */
DECL|member|frame_index
id|u32
id|frame_index
suffix:semicolon
multiline_comment|/* current microframe number */
multiline_comment|/* CTRLDSSEGMENT: offset 0x10 */
DECL|member|segment
id|u32
id|segment
suffix:semicolon
multiline_comment|/* address bits 63:32 if needed */
multiline_comment|/* PERIODICLISTBASE: offset 0x14 */
DECL|member|frame_list
id|u32
id|frame_list
suffix:semicolon
multiline_comment|/* points to periodic list */
multiline_comment|/* ASYNCLISTADDR: offset 0x18 */
DECL|member|async_next
id|u32
id|async_next
suffix:semicolon
multiline_comment|/* address of next async queue head */
DECL|member|reserved
id|u32
id|reserved
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* CONFIGFLAG: offset 0x40 */
DECL|member|configured_flag
id|u32
id|configured_flag
suffix:semicolon
DECL|macro|FLAG_CF
mdefine_line|#define FLAG_CF&t;&t;(1&lt;&lt;0)&t;&t;/* true: we&squot;ll support &quot;high speed&quot; */
multiline_comment|/* PORTSC: offset 0x44 */
DECL|member|port_status
id|u32
id|port_status
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* up to N_PORTS */
multiline_comment|/* 31:23 reserved */
DECL|macro|PORT_WKOC_E
mdefine_line|#define PORT_WKOC_E&t;(1&lt;&lt;22)&t;&t;/* wake on overcurrent (enable) */
DECL|macro|PORT_WKDISC_E
mdefine_line|#define PORT_WKDISC_E&t;(1&lt;&lt;21)&t;&t;/* wake on disconnect (enable) */
DECL|macro|PORT_WKCONN_E
mdefine_line|#define PORT_WKCONN_E&t;(1&lt;&lt;20)&t;&t;/* wake on connect (enable) */
multiline_comment|/* 19:16 for port testing */
DECL|macro|PORT_LED_OFF
mdefine_line|#define PORT_LED_OFF&t;(0&lt;&lt;14)
DECL|macro|PORT_LED_AMBER
mdefine_line|#define PORT_LED_AMBER&t;(1&lt;&lt;14)
DECL|macro|PORT_LED_GREEN
mdefine_line|#define PORT_LED_GREEN&t;(2&lt;&lt;14)
DECL|macro|PORT_LED_MASK
mdefine_line|#define PORT_LED_MASK&t;(3&lt;&lt;14)
DECL|macro|PORT_OWNER
mdefine_line|#define PORT_OWNER&t;(1&lt;&lt;13)&t;&t;/* true: companion hc owns this port */
DECL|macro|PORT_POWER
mdefine_line|#define PORT_POWER&t;(1&lt;&lt;12)&t;&t;/* true: has power (see PPC) */
DECL|macro|PORT_USB11
mdefine_line|#define PORT_USB11(x) (((x)&amp;(3&lt;&lt;10))==(1&lt;&lt;10))&t;/* USB 1.1 device */
multiline_comment|/* 11:10 for detecting lowspeed devices (reset vs release ownership) */
multiline_comment|/* 9 reserved */
DECL|macro|PORT_RESET
mdefine_line|#define PORT_RESET&t;(1&lt;&lt;8)&t;&t;/* reset port */
DECL|macro|PORT_SUSPEND
mdefine_line|#define PORT_SUSPEND&t;(1&lt;&lt;7)&t;&t;/* suspend port */
DECL|macro|PORT_RESUME
mdefine_line|#define PORT_RESUME&t;(1&lt;&lt;6)&t;&t;/* resume it */
DECL|macro|PORT_OCC
mdefine_line|#define PORT_OCC&t;(1&lt;&lt;5)&t;&t;/* over current change */
DECL|macro|PORT_OC
mdefine_line|#define PORT_OC&t;&t;(1&lt;&lt;4)&t;&t;/* over current active */
DECL|macro|PORT_PEC
mdefine_line|#define PORT_PEC&t;(1&lt;&lt;3)&t;&t;/* port enable change */
DECL|macro|PORT_PE
mdefine_line|#define PORT_PE&t;&t;(1&lt;&lt;2)&t;&t;/* port enable */
DECL|macro|PORT_CSC
mdefine_line|#define PORT_CSC&t;(1&lt;&lt;1)&t;&t;/* connect status change */
DECL|macro|PORT_CONNECT
mdefine_line|#define PORT_CONNECT&t;(1&lt;&lt;0)&t;&t;/* device connected */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|macro|QTD_NEXT
mdefine_line|#define&t;QTD_NEXT(dma)&t;cpu_to_le32((u32)dma)
multiline_comment|/*&n; * EHCI Specification 0.95 Section 3.5&n; * QTD: describe data transfer components (buffer, direction, ...) &n; * See Fig 3-6 &quot;Queue Element Transfer Descriptor Block Diagram&quot;.&n; *&n; * These are associated only with &quot;QH&quot; (Queue Head) structures,&n; * used with control, bulk, and interrupt transfers.&n; */
DECL|struct|ehci_qtd
r_struct
id|ehci_qtd
(brace
multiline_comment|/* first part defined by EHCI spec */
DECL|member|hw_next
id|__le32
id|hw_next
suffix:semicolon
multiline_comment|/* see EHCI 3.5.1 */
DECL|member|hw_alt_next
id|__le32
id|hw_alt_next
suffix:semicolon
multiline_comment|/* see EHCI 3.5.2 */
DECL|member|hw_token
id|__le32
id|hw_token
suffix:semicolon
multiline_comment|/* see EHCI 3.5.3 */
DECL|macro|QTD_TOGGLE
mdefine_line|#define&t;QTD_TOGGLE&t;(1 &lt;&lt; 31)&t;/* data toggle */
DECL|macro|QTD_LENGTH
mdefine_line|#define&t;QTD_LENGTH(tok)&t;(((tok)&gt;&gt;16) &amp; 0x7fff)
DECL|macro|QTD_IOC
mdefine_line|#define&t;QTD_IOC&t;&t;(1 &lt;&lt; 15)&t;/* interrupt on complete */
DECL|macro|QTD_CERR
mdefine_line|#define&t;QTD_CERR(tok)&t;(((tok)&gt;&gt;10) &amp; 0x3)
DECL|macro|QTD_PID
mdefine_line|#define&t;QTD_PID(tok)&t;(((tok)&gt;&gt;8) &amp; 0x3)
DECL|macro|QTD_STS_ACTIVE
mdefine_line|#define&t;QTD_STS_ACTIVE&t;(1 &lt;&lt; 7)&t;/* HC may execute this */
DECL|macro|QTD_STS_HALT
mdefine_line|#define&t;QTD_STS_HALT&t;(1 &lt;&lt; 6)&t;/* halted on error */
DECL|macro|QTD_STS_DBE
mdefine_line|#define&t;QTD_STS_DBE&t;(1 &lt;&lt; 5)&t;/* data buffer error (in HC) */
DECL|macro|QTD_STS_BABBLE
mdefine_line|#define&t;QTD_STS_BABBLE&t;(1 &lt;&lt; 4)&t;/* device was babbling (qtd halted) */
DECL|macro|QTD_STS_XACT
mdefine_line|#define&t;QTD_STS_XACT&t;(1 &lt;&lt; 3)&t;/* device gave illegal response */
DECL|macro|QTD_STS_MMF
mdefine_line|#define&t;QTD_STS_MMF&t;(1 &lt;&lt; 2)&t;/* incomplete split transaction */
DECL|macro|QTD_STS_STS
mdefine_line|#define&t;QTD_STS_STS&t;(1 &lt;&lt; 1)&t;/* split transaction state */
DECL|macro|QTD_STS_PING
mdefine_line|#define&t;QTD_STS_PING&t;(1 &lt;&lt; 0)&t;/* issue PING? */
DECL|member|hw_buf
id|__le32
id|hw_buf
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* see EHCI 3.5.4 */
DECL|member|hw_buf_hi
id|__le32
id|hw_buf_hi
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* Appendix B */
multiline_comment|/* the rest is HCD-private */
DECL|member|qtd_dma
id|dma_addr_t
id|qtd_dma
suffix:semicolon
multiline_comment|/* qtd address */
DECL|member|qtd_list
r_struct
id|list_head
id|qtd_list
suffix:semicolon
multiline_comment|/* sw qtd list */
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
multiline_comment|/* qtd&squot;s urb */
DECL|member|length
r_int
id|length
suffix:semicolon
multiline_comment|/* length of buffer */
)brace
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|32
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* mask NakCnt+T in qh-&gt;hw_alt_next */
DECL|macro|QTD_MASK
mdefine_line|#define QTD_MASK __constant_cpu_to_le32 (~0x1f)
DECL|macro|IS_SHORT_READ
mdefine_line|#define IS_SHORT_READ(token) (QTD_LENGTH (token) != 0 &amp;&amp; QTD_PID (token) == 1)
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* type tag from {qh,itd,sitd,fstn}-&gt;hw_next */
DECL|macro|Q_NEXT_TYPE
mdefine_line|#define Q_NEXT_TYPE(dma) ((dma) &amp; __constant_cpu_to_le32 (3 &lt;&lt; 1))
multiline_comment|/* values for that type tag */
DECL|macro|Q_TYPE_ITD
mdefine_line|#define Q_TYPE_ITD&t;__constant_cpu_to_le32 (0 &lt;&lt; 1)
DECL|macro|Q_TYPE_QH
mdefine_line|#define Q_TYPE_QH&t;__constant_cpu_to_le32 (1 &lt;&lt; 1)
DECL|macro|Q_TYPE_SITD
mdefine_line|#define Q_TYPE_SITD &t;__constant_cpu_to_le32 (2 &lt;&lt; 1)
DECL|macro|Q_TYPE_FSTN
mdefine_line|#define Q_TYPE_FSTN &t;__constant_cpu_to_le32 (3 &lt;&lt; 1)
multiline_comment|/* next async queue entry, or pointer to interrupt/periodic QH */
DECL|macro|QH_NEXT
mdefine_line|#define&t;QH_NEXT(dma)&t;(cpu_to_le32(((u32)dma)&amp;~0x01f)|Q_TYPE_QH)
multiline_comment|/* for periodic/async schedules and qtd lists, mark end of list */
DECL|macro|EHCI_LIST_END
mdefine_line|#define&t;EHCI_LIST_END&t;__constant_cpu_to_le32(1) /* &quot;null pointer&quot; to hw */
multiline_comment|/*&n; * Entries in periodic shadow table are pointers to one of four kinds&n; * of data structure.  That&squot;s dictated by the hardware; a type tag is&n; * encoded in the low bits of the hardware&squot;s periodic schedule.  Use&n; * Q_NEXT_TYPE to get the tag.&n; *&n; * For entries in the async schedule, the type tag always says &quot;qh&quot;.&n; */
DECL|union|ehci_shadow
r_union
id|ehci_shadow
(brace
DECL|member|qh
r_struct
id|ehci_qh
op_star
id|qh
suffix:semicolon
multiline_comment|/* Q_TYPE_QH */
DECL|member|itd
r_struct
id|ehci_itd
op_star
id|itd
suffix:semicolon
multiline_comment|/* Q_TYPE_ITD */
DECL|member|sitd
r_struct
id|ehci_sitd
op_star
id|sitd
suffix:semicolon
multiline_comment|/* Q_TYPE_SITD */
DECL|member|fstn
r_struct
id|ehci_fstn
op_star
id|fstn
suffix:semicolon
multiline_comment|/* Q_TYPE_FSTN */
DECL|member|hw_next
id|u32
op_star
id|hw_next
suffix:semicolon
multiline_comment|/* (all types) */
DECL|member|ptr
r_void
op_star
id|ptr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * EHCI Specification 0.95 Section 3.6&n; * QH: describes control/bulk/interrupt endpoints&n; * See Fig 3-7 &quot;Queue Head Structure Layout&quot;.&n; *&n; * These appear in both the async and (for interrupt) periodic schedules.&n; */
DECL|struct|ehci_qh
r_struct
id|ehci_qh
(brace
multiline_comment|/* first part defined by EHCI spec */
DECL|member|hw_next
id|__le32
id|hw_next
suffix:semicolon
multiline_comment|/* see EHCI 3.6.1 */
DECL|member|hw_info1
id|__le32
id|hw_info1
suffix:semicolon
multiline_comment|/* see EHCI 3.6.2 */
DECL|macro|QH_HEAD
mdefine_line|#define&t;QH_HEAD&t;&t;0x00008000
DECL|member|hw_info2
id|__le32
id|hw_info2
suffix:semicolon
multiline_comment|/* see EHCI 3.6.2 */
DECL|member|hw_current
id|__le32
id|hw_current
suffix:semicolon
multiline_comment|/* qtd list - see EHCI 3.6.4 */
multiline_comment|/* qtd overlay (hardware parts of a struct ehci_qtd) */
DECL|member|hw_qtd_next
id|__le32
id|hw_qtd_next
suffix:semicolon
DECL|member|hw_alt_next
id|__le32
id|hw_alt_next
suffix:semicolon
DECL|member|hw_token
id|__le32
id|hw_token
suffix:semicolon
DECL|member|hw_buf
id|__le32
id|hw_buf
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|hw_buf_hi
id|__le32
id|hw_buf_hi
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* the rest is HCD-private */
DECL|member|qh_dma
id|dma_addr_t
id|qh_dma
suffix:semicolon
multiline_comment|/* address of qh */
DECL|member|qh_next
r_union
id|ehci_shadow
id|qh_next
suffix:semicolon
multiline_comment|/* ptr to qh; or periodic */
DECL|member|qtd_list
r_struct
id|list_head
id|qtd_list
suffix:semicolon
multiline_comment|/* sw qtd list */
DECL|member|dummy
r_struct
id|ehci_qtd
op_star
id|dummy
suffix:semicolon
DECL|member|reclaim
r_struct
id|ehci_qh
op_star
id|reclaim
suffix:semicolon
multiline_comment|/* next to reclaim */
DECL|member|ehci
r_struct
id|ehci_hcd
op_star
id|ehci
suffix:semicolon
DECL|member|kref
r_struct
id|kref
id|kref
suffix:semicolon
DECL|member|stamp
r_int
id|stamp
suffix:semicolon
DECL|member|qh_state
id|u8
id|qh_state
suffix:semicolon
DECL|macro|QH_STATE_LINKED
mdefine_line|#define&t;QH_STATE_LINKED&t;&t;1&t;&t;/* HC sees this */
DECL|macro|QH_STATE_UNLINK
mdefine_line|#define&t;QH_STATE_UNLINK&t;&t;2&t;&t;/* HC may still see this */
DECL|macro|QH_STATE_IDLE
mdefine_line|#define&t;QH_STATE_IDLE&t;&t;3&t;&t;/* HC doesn&squot;t see this */
DECL|macro|QH_STATE_UNLINK_WAIT
mdefine_line|#define&t;QH_STATE_UNLINK_WAIT&t;4&t;&t;/* LINKED and on reclaim q */
DECL|macro|QH_STATE_COMPLETING
mdefine_line|#define&t;QH_STATE_COMPLETING&t;5&t;&t;/* don&squot;t touch token.HALT */
multiline_comment|/* periodic schedule info */
DECL|member|usecs
id|u8
id|usecs
suffix:semicolon
multiline_comment|/* intr bandwidth */
DECL|member|gap_uf
id|u8
id|gap_uf
suffix:semicolon
multiline_comment|/* uframes split/csplit gap */
DECL|member|c_usecs
id|u8
id|c_usecs
suffix:semicolon
multiline_comment|/* ... split completion bw */
DECL|member|period
r_int
r_int
id|period
suffix:semicolon
multiline_comment|/* polling interval */
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
multiline_comment|/* where polling starts */
DECL|macro|NO_FRAME
mdefine_line|#define NO_FRAME ((unsigned short)~0)&t;&t;&t;/* pick new start */
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* access to TT */
)brace
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|32
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* description of one iso transaction (up to 3 KB data if highspeed) */
DECL|struct|ehci_iso_packet
r_struct
id|ehci_iso_packet
(brace
multiline_comment|/* These will be copied to iTD when scheduling */
DECL|member|bufp
id|u64
id|bufp
suffix:semicolon
multiline_comment|/* itd-&gt;hw_bufp{,_hi}[pg] |= */
DECL|member|transaction
id|__le32
id|transaction
suffix:semicolon
multiline_comment|/* itd-&gt;hw_transaction[i] |= */
DECL|member|cross
id|u8
id|cross
suffix:semicolon
multiline_comment|/* buf crosses pages */
multiline_comment|/* for full speed OUT splits */
DECL|member|buf1
id|u16
id|buf1
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* temporary schedule data for packets from iso urbs (both speeds)&n; * each packet is one logical usb transaction to the device (not TT),&n; * beginning at stream-&gt;next_uframe&n; */
DECL|struct|ehci_iso_sched
r_struct
id|ehci_iso_sched
(brace
DECL|member|td_list
r_struct
id|list_head
id|td_list
suffix:semicolon
DECL|member|span
r_int
id|span
suffix:semicolon
DECL|member|packet
r_struct
id|ehci_iso_packet
id|packet
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ehci_iso_stream - groups all (s)itds for this endpoint.&n; * acts like a qh would, if EHCI had them for ISO.&n; */
DECL|struct|ehci_iso_stream
r_struct
id|ehci_iso_stream
(brace
multiline_comment|/* first two fields match QH, but info1 == 0 */
DECL|member|hw_next
id|__le32
id|hw_next
suffix:semicolon
DECL|member|hw_info1
id|__le32
id|hw_info1
suffix:semicolon
DECL|member|refcount
id|u32
id|refcount
suffix:semicolon
DECL|member|bEndpointAddress
id|u8
id|bEndpointAddress
suffix:semicolon
DECL|member|highspeed
id|u8
id|highspeed
suffix:semicolon
DECL|member|depth
id|u16
id|depth
suffix:semicolon
multiline_comment|/* depth in uframes */
DECL|member|td_list
r_struct
id|list_head
id|td_list
suffix:semicolon
multiline_comment|/* queued itds/sitds */
DECL|member|free_list
r_struct
id|list_head
id|free_list
suffix:semicolon
multiline_comment|/* list of unused itds/sitds */
DECL|member|udev
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
DECL|member|ep
r_struct
id|usb_host_endpoint
op_star
id|ep
suffix:semicolon
multiline_comment|/* output of (re)scheduling */
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
multiline_comment|/* jiffies */
DECL|member|rescheduled
r_int
r_int
id|rescheduled
suffix:semicolon
DECL|member|next_uframe
r_int
id|next_uframe
suffix:semicolon
DECL|member|splits
id|__le32
id|splits
suffix:semicolon
multiline_comment|/* the rest is derived from the endpoint descriptor,&n;&t; * trusting urb-&gt;interval == f(epdesc-&gt;bInterval) and&n;&t; * including the extra info for hw_bufp[0..2]&n;&t; */
DECL|member|interval
id|u8
id|interval
suffix:semicolon
DECL|member|usecs
DECL|member|c_usecs
id|u8
id|usecs
comma
id|c_usecs
suffix:semicolon
DECL|member|maxp
id|u16
id|maxp
suffix:semicolon
DECL|member|raw_mask
id|u16
id|raw_mask
suffix:semicolon
DECL|member|bandwidth
r_int
id|bandwidth
suffix:semicolon
multiline_comment|/* This is used to initialize iTD&squot;s hw_bufp fields */
DECL|member|buf0
id|__le32
id|buf0
suffix:semicolon
DECL|member|buf1
id|__le32
id|buf1
suffix:semicolon
DECL|member|buf2
id|__le32
id|buf2
suffix:semicolon
multiline_comment|/* this is used to initialize sITD&squot;s tt info */
DECL|member|address
id|__le32
id|address
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * EHCI Specification 0.95 Section 3.3&n; * Fig 3-4 &quot;Isochronous Transaction Descriptor (iTD)&quot;&n; *&n; * Schedule records for high speed iso xfers&n; */
DECL|struct|ehci_itd
r_struct
id|ehci_itd
(brace
multiline_comment|/* first part defined by EHCI spec */
DECL|member|hw_next
id|__le32
id|hw_next
suffix:semicolon
multiline_comment|/* see EHCI 3.3.1 */
DECL|member|hw_transaction
id|__le32
id|hw_transaction
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* see EHCI 3.3.2 */
DECL|macro|EHCI_ISOC_ACTIVE
mdefine_line|#define EHCI_ISOC_ACTIVE        (1&lt;&lt;31)        /* activate transfer this slot */
DECL|macro|EHCI_ISOC_BUF_ERR
mdefine_line|#define EHCI_ISOC_BUF_ERR       (1&lt;&lt;30)        /* Data buffer error */
DECL|macro|EHCI_ISOC_BABBLE
mdefine_line|#define EHCI_ISOC_BABBLE        (1&lt;&lt;29)        /* babble detected */
DECL|macro|EHCI_ISOC_XACTERR
mdefine_line|#define EHCI_ISOC_XACTERR       (1&lt;&lt;28)        /* XactErr - transaction error */
DECL|macro|EHCI_ITD_LENGTH
mdefine_line|#define&t;EHCI_ITD_LENGTH(tok)&t;(((tok)&gt;&gt;16) &amp; 0x0fff)
DECL|macro|EHCI_ITD_IOC
mdefine_line|#define&t;EHCI_ITD_IOC&t;&t;(1 &lt;&lt; 15)&t;/* interrupt on complete */
DECL|macro|ITD_ACTIVE
mdefine_line|#define ITD_ACTIVE&t;__constant_cpu_to_le32(EHCI_ISOC_ACTIVE)
DECL|member|hw_bufp
id|__le32
id|hw_bufp
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* see EHCI 3.3.3 */
DECL|member|hw_bufp_hi
id|__le32
id|hw_bufp_hi
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* Appendix B */
multiline_comment|/* the rest is HCD-private */
DECL|member|itd_dma
id|dma_addr_t
id|itd_dma
suffix:semicolon
multiline_comment|/* for this itd */
DECL|member|itd_next
r_union
id|ehci_shadow
id|itd_next
suffix:semicolon
multiline_comment|/* ptr to periodic q entry */
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
DECL|member|stream
r_struct
id|ehci_iso_stream
op_star
id|stream
suffix:semicolon
multiline_comment|/* endpoint&squot;s queue */
DECL|member|itd_list
r_struct
id|list_head
id|itd_list
suffix:semicolon
multiline_comment|/* list of stream&squot;s itds */
multiline_comment|/* any/all hw_transactions here may be used by that urb */
DECL|member|frame
r_int
id|frame
suffix:semicolon
multiline_comment|/* where scheduled */
DECL|member|pg
r_int
id|pg
suffix:semicolon
DECL|member|index
r_int
id|index
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* in urb-&gt;iso_frame_desc */
DECL|member|usecs
id|u8
id|usecs
(braket
l_int|8
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|32
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * EHCI Specification 0.95 Section 3.4 &n; * siTD, aka split-transaction isochronous Transfer Descriptor&n; *       ... describe full speed iso xfers through TT in hubs&n; * see Figure 3-5 &quot;Split-transaction Isochronous Transaction Descriptor (siTD)&n; */
DECL|struct|ehci_sitd
r_struct
id|ehci_sitd
(brace
multiline_comment|/* first part defined by EHCI spec */
DECL|member|hw_next
id|__le32
id|hw_next
suffix:semicolon
multiline_comment|/* uses bit field macros above - see EHCI 0.95 Table 3-8 */
DECL|member|hw_fullspeed_ep
id|__le32
id|hw_fullspeed_ep
suffix:semicolon
multiline_comment|/* EHCI table 3-9 */
DECL|member|hw_uframe
id|__le32
id|hw_uframe
suffix:semicolon
multiline_comment|/* EHCI table 3-10 */
DECL|member|hw_results
id|__le32
id|hw_results
suffix:semicolon
multiline_comment|/* EHCI table 3-11 */
DECL|macro|SITD_IOC
mdefine_line|#define&t;SITD_IOC&t;(1 &lt;&lt; 31)&t;/* interrupt on completion */
DECL|macro|SITD_PAGE
mdefine_line|#define&t;SITD_PAGE&t;(1 &lt;&lt; 30)&t;/* buffer 0/1 */
DECL|macro|SITD_LENGTH
mdefine_line|#define&t;SITD_LENGTH(x)&t;(0x3ff &amp; ((x)&gt;&gt;16))
DECL|macro|SITD_STS_ACTIVE
mdefine_line|#define&t;SITD_STS_ACTIVE&t;(1 &lt;&lt; 7)&t;/* HC may execute this */
DECL|macro|SITD_STS_ERR
mdefine_line|#define&t;SITD_STS_ERR&t;(1 &lt;&lt; 6)&t;/* error from TT */
DECL|macro|SITD_STS_DBE
mdefine_line|#define&t;SITD_STS_DBE&t;(1 &lt;&lt; 5)&t;/* data buffer error (in HC) */
DECL|macro|SITD_STS_BABBLE
mdefine_line|#define&t;SITD_STS_BABBLE&t;(1 &lt;&lt; 4)&t;/* device was babbling */
DECL|macro|SITD_STS_XACT
mdefine_line|#define&t;SITD_STS_XACT&t;(1 &lt;&lt; 3)&t;/* illegal IN response */
DECL|macro|SITD_STS_MMF
mdefine_line|#define&t;SITD_STS_MMF&t;(1 &lt;&lt; 2)&t;/* incomplete split transaction */
DECL|macro|SITD_STS_STS
mdefine_line|#define&t;SITD_STS_STS&t;(1 &lt;&lt; 1)&t;/* split transaction state */
DECL|macro|SITD_ACTIVE
mdefine_line|#define SITD_ACTIVE&t;__constant_cpu_to_le32(SITD_STS_ACTIVE)
DECL|member|hw_buf
id|__le32
id|hw_buf
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* EHCI table 3-12 */
DECL|member|hw_backpointer
id|__le32
id|hw_backpointer
suffix:semicolon
multiline_comment|/* EHCI table 3-13 */
DECL|member|hw_buf_hi
id|__le32
id|hw_buf_hi
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Appendix B */
multiline_comment|/* the rest is HCD-private */
DECL|member|sitd_dma
id|dma_addr_t
id|sitd_dma
suffix:semicolon
DECL|member|sitd_next
r_union
id|ehci_shadow
id|sitd_next
suffix:semicolon
multiline_comment|/* ptr to periodic q entry */
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
DECL|member|stream
r_struct
id|ehci_iso_stream
op_star
id|stream
suffix:semicolon
multiline_comment|/* endpoint&squot;s queue */
DECL|member|sitd_list
r_struct
id|list_head
id|sitd_list
suffix:semicolon
multiline_comment|/* list of stream&squot;s sitds */
DECL|member|frame
r_int
id|frame
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|32
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * EHCI Specification 0.96 Section 3.7&n; * Periodic Frame Span Traversal Node (FSTN)&n; *&n; * Manages split interrupt transactions (using TT) that span frame boundaries&n; * into uframes 0/1; see 4.12.2.2.  In those uframes, a &quot;save place&quot; FSTN&n; * makes the HC jump (back) to a QH to scan for fs/ls QH completions until&n; * it hits a &quot;restore&quot; FSTN; then it returns to finish other uframe 0/1 work.&n; */
DECL|struct|ehci_fstn
r_struct
id|ehci_fstn
(brace
DECL|member|hw_next
id|__le32
id|hw_next
suffix:semicolon
multiline_comment|/* any periodic q entry */
DECL|member|hw_prev
id|__le32
id|hw_prev
suffix:semicolon
multiline_comment|/* qh or EHCI_LIST_END */
multiline_comment|/* the rest is HCD-private */
DECL|member|fstn_dma
id|dma_addr_t
id|fstn_dma
suffix:semicolon
DECL|member|fstn_next
r_union
id|ehci_shadow
id|fstn_next
suffix:semicolon
multiline_comment|/* ptr to periodic q entry */
)brace
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|32
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
macro_line|#ifdef CONFIG_USB_EHCI_ROOT_HUB_TT
multiline_comment|/*&n; * Some EHCI controllers have a Transaction Translator built into the&n; * root hub. This is a non-standard feature.  Each controller will need&n; * to add code to the following inline functions, and call them as&n; * needed (mostly in root hub code).&n; */
DECL|macro|ehci_is_ARC
mdefine_line|#define&t;ehci_is_ARC(e)&t;&t;&t;((e)-&gt;is_arc_rh_tt)
multiline_comment|/* Returns the speed of a device attached to a port on the root hub. */
r_static
r_inline
r_int
r_int
DECL|function|ehci_port_speed
id|ehci_port_speed
c_func
(paren
r_struct
id|ehci_hcd
op_star
id|ehci
comma
r_int
r_int
id|portsc
)paren
(brace
r_if
c_cond
(paren
id|ehci_is_ARC
c_func
(paren
id|ehci
)paren
)paren
(brace
r_switch
c_cond
(paren
(paren
id|portsc
op_rshift
l_int|26
)paren
op_amp
l_int|3
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
(paren
l_int|1
op_lshift
id|USB_PORT_FEAT_LOWSPEED
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
r_default
suffix:colon
r_return
(paren
l_int|1
op_lshift
id|USB_PORT_FEAT_HIGHSPEED
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
l_int|1
op_lshift
id|USB_PORT_FEAT_HIGHSPEED
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|ehci_is_ARC
mdefine_line|#define&t;ehci_is_ARC(e)&t;&t;&t;(0)
DECL|macro|ehci_port_speed
mdefine_line|#define&t;ehci_port_speed(ehci, portsc)&t;(1&lt;&lt;USB_PORT_FEAT_HIGHSPEED)
macro_line|#endif
multiline_comment|/*-------------------------------------------------------------------------*/
macro_line|#ifndef DEBUG
DECL|macro|STUB_DEBUG_FILES
mdefine_line|#define STUB_DEBUG_FILES
macro_line|#endif&t;/* DEBUG */
multiline_comment|/*-------------------------------------------------------------------------*/
macro_line|#endif /* __LINUX_EHCI_HCD_H */
eof
