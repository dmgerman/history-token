multiline_comment|/*&n; * Copyright (c) 2001-2002 by David Brownell&n; * &n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY&n; * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; * for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __LINUX_EHCI_HCD_H
DECL|macro|__LINUX_EHCI_HCD_H
mdefine_line|#define __LINUX_EHCI_HCD_H
multiline_comment|/* definitions used for the EHCI driver */
multiline_comment|/* ehci_hcd-&gt;lock guards shared data against other CPUs:&n; *   ehci_hcd:&t;async, reclaim, periodic (and shadow), ...&n; *   hcd_dev:&t;ep[]&n; *   ehci_qh:&t;qh_next, qtd_list&n; *   ehci_qtd:&t;qtd_list&n; *&n; * Also, hold this lock when talking to HC registers or&n; * when updating hw_* fields in shared qh/qtd/... structures.&n; */
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
suffix:semicolon
multiline_comment|/* periodic schedule support */
DECL|macro|DEFAULT_I_TDPS
mdefine_line|#define&t;DEFAULT_I_TDPS&t;&t;1024&t;&t;/* some HCs can do less */
DECL|member|periodic_size
r_int
id|periodic_size
suffix:semicolon
DECL|member|periodic
id|u32
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
DECL|member|periodic_urbs
r_int
id|periodic_urbs
suffix:semicolon
multiline_comment|/* how many urbs scheduled? */
multiline_comment|/* deferred work from IRQ, etc */
DECL|member|tasklet
r_struct
id|tasklet_struct
id|tasklet
suffix:semicolon
multiline_comment|/* per root hub port */
DECL|member|reset_done
r_int
r_int
id|reset_done
(braket
id|EHCI_MAX_ROOT_PORTS
)braket
suffix:semicolon
multiline_comment|/* glue to PCI and HCD framework */
DECL|member|hcd
r_struct
id|usb_hcd
id|hcd
suffix:semicolon
DECL|member|caps
r_struct
id|ehci_caps
op_star
id|caps
suffix:semicolon
DECL|member|regs
r_struct
id|ehci_regs
op_star
id|regs
suffix:semicolon
DECL|member|hcs_params
id|u32
id|hcs_params
suffix:semicolon
multiline_comment|/* cached register copy */
multiline_comment|/* per-HC memory pools (could be per-PCI-bus, but ...) */
DECL|member|qh_pool
r_struct
id|pci_pool
op_star
id|qh_pool
suffix:semicolon
multiline_comment|/* qh per active urb */
DECL|member|qtd_pool
r_struct
id|pci_pool
op_star
id|qtd_pool
suffix:semicolon
multiline_comment|/* one or more per qh */
DECL|member|itd_pool
r_struct
id|pci_pool
op_star
id|itd_pool
suffix:semicolon
multiline_comment|/* itd per iso urb */
DECL|member|sitd_pool
r_struct
id|pci_pool
op_star
id|sitd_pool
suffix:semicolon
multiline_comment|/* sitd per split iso urb */
)brace
suffix:semicolon
multiline_comment|/* unwrap an HCD pointer to get an EHCI_HCD pointer */
DECL|macro|hcd_to_ehci
mdefine_line|#define hcd_to_ehci(hcd_ptr) list_entry(hcd_ptr, struct ehci_hcd, hcd)
multiline_comment|/* NOTE:  urb-&gt;transfer_flags expected to not use this bit !!! */
DECL|macro|EHCI_STATE_UNLINK
mdefine_line|#define EHCI_STATE_UNLINK&t;0x8000&t;&t;/* urb being unlinked */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* EHCI register interface, corresponds to EHCI Revision 0.95 specification */
multiline_comment|/* Section 2.2 Host Controller Capability Registers */
DECL|struct|ehci_caps
r_struct
id|ehci_caps
(brace
DECL|member|length
id|u8
id|length
suffix:semicolon
multiline_comment|/* CAPLENGTH - size of this struct */
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
multiline_comment|/* offset 0x1 */
DECL|member|hci_version
id|u16
id|hci_version
suffix:semicolon
multiline_comment|/* HCIVERSION - offset 0x2 */
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
multiline_comment|/* ASYNCICLISTADDR: offset 0x18 */
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
multiline_comment|/* 15:14 for using port indicator leds (if HCS_INDICATOR allows) */
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
id|u32
id|hw_next
suffix:semicolon
multiline_comment|/* see EHCI 3.5.1 */
DECL|member|hw_alt_next
id|u32
id|hw_alt_next
suffix:semicolon
multiline_comment|/* see EHCI 3.5.2 */
DECL|member|hw_token
id|u32
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
id|u32
id|hw_buf
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* see EHCI 3.5.4 */
DECL|member|hw_buf_hi
id|u32
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
multiline_comment|/* dma same in urb&squot;s qtds, except 1st control qtd (setup buffer) */
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
multiline_comment|/* qtd&squot;s urb */
DECL|member|buf_dma
id|dma_addr_t
id|buf_dma
suffix:semicolon
multiline_comment|/* buffer address */
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
id|u32
id|hw_next
suffix:semicolon
multiline_comment|/* see EHCI 3.6.1 */
DECL|member|hw_info1
id|u32
id|hw_info1
suffix:semicolon
multiline_comment|/* see EHCI 3.6.2 */
DECL|macro|QH_HEAD
mdefine_line|#define&t;QH_HEAD&t;&t;0x00008000
DECL|member|hw_info2
id|u32
id|hw_info2
suffix:semicolon
multiline_comment|/* see EHCI 3.6.2 */
DECL|member|hw_current
id|u32
id|hw_current
suffix:semicolon
multiline_comment|/* qtd list - see EHCI 3.6.4 */
multiline_comment|/* qtd overlay (hardware parts of a struct ehci_qtd) */
DECL|member|hw_qtd_next
id|u32
id|hw_qtd_next
suffix:semicolon
DECL|member|hw_alt_next
id|u32
id|hw_alt_next
suffix:semicolon
DECL|member|hw_token
id|u32
id|hw_token
suffix:semicolon
DECL|member|hw_buf
id|u32
id|hw_buf
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|hw_buf_hi
id|u32
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
DECL|member|refcount
id|atomic_t
id|refcount
suffix:semicolon
DECL|member|usecs
r_int
r_int
id|usecs
suffix:semicolon
multiline_comment|/* intr bandwidth */
DECL|member|c_usecs
r_int
r_int
id|c_usecs
suffix:semicolon
multiline_comment|/* ... split completion bw */
DECL|member|qh_state
r_int
id|qh_state
suffix:semicolon
DECL|macro|QH_STATE_LINKED
mdefine_line|#define&t;QH_STATE_LINKED&t;&t;1&t;&t;/* HC sees this */
DECL|macro|QH_STATE_UNLINK
mdefine_line|#define&t;QH_STATE_UNLINK&t;&t;2&t;&t;/* HC may still see this */
DECL|macro|QH_STATE_IDLE
mdefine_line|#define&t;QH_STATE_IDLE&t;&t;3&t;&t;/* HC doesn&squot;t see this */
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
multiline_comment|/*&n; * EHCI Specification 0.95 Section 3.3&n; * Fig 3-4 &quot;Isochronous Transaction Descriptor (iTD)&quot;&n; *&n; * Schedule records for high speed iso xfers&n; */
DECL|struct|ehci_itd
r_struct
id|ehci_itd
(brace
multiline_comment|/* first part defined by EHCI spec */
DECL|member|hw_next
id|u32
id|hw_next
suffix:semicolon
multiline_comment|/* see EHCI 3.3.1 */
DECL|member|hw_transaction
id|u32
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
mdefine_line|#define&t;EHCI_ITD_LENGTH(tok)&t;(((tok)&gt;&gt;16) &amp; 0x7fff)
DECL|macro|EHCI_ITD_IOC
mdefine_line|#define&t;EHCI_ITD_IOC&t;&t;(1 &lt;&lt; 15)&t;/* interrupt on complete */
DECL|member|hw_bufp
id|u32
id|hw_bufp
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* see EHCI 3.3.3 */
DECL|member|hw_bufp_hi
id|u32
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
DECL|member|itd_list
r_struct
id|list_head
id|itd_list
suffix:semicolon
multiline_comment|/* list of urb frames&squot; itds */
DECL|member|buf_dma
id|dma_addr_t
id|buf_dma
suffix:semicolon
multiline_comment|/* frame&squot;s buffer address */
multiline_comment|/* for now, only one hw_transaction per itd */
DECL|member|transaction
id|u32
id|transaction
suffix:semicolon
DECL|member|index
id|u16
id|index
suffix:semicolon
multiline_comment|/* in urb-&gt;iso_frame_desc */
DECL|member|uframe
id|u16
id|uframe
suffix:semicolon
multiline_comment|/* in periodic schedule */
DECL|member|usecs
id|u16
id|usecs
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
multiline_comment|/*&n; * EHCI Specification 0.95 Section 3.4 &n; * siTD, aka split-transaction isochronous Transfer Descriptor&n; *       ... describe low/full speed iso xfers through TT in hubs&n; * see Figure 3-5 &quot;Split-transaction Isochronous Transaction Descriptor (siTD)&n; */
DECL|struct|ehci_sitd
r_struct
id|ehci_sitd
(brace
multiline_comment|/* first part defined by EHCI spec */
DECL|member|hw_next
id|u32
id|hw_next
suffix:semicolon
multiline_comment|/* uses bit field macros above - see EHCI 0.95 Table 3-8 */
DECL|member|hw_fullspeed_ep
id|u32
id|hw_fullspeed_ep
suffix:semicolon
multiline_comment|/* see EHCI table 3-9 */
DECL|member|hw_uframe
id|u32
id|hw_uframe
suffix:semicolon
multiline_comment|/* see EHCI table 3-10 */
DECL|member|hw_tx_results1
id|u32
id|hw_tx_results1
suffix:semicolon
multiline_comment|/* see EHCI table 3-11 */
DECL|member|hw_tx_results2
id|u32
id|hw_tx_results2
suffix:semicolon
multiline_comment|/* see EHCI table 3-12 */
DECL|member|hw_tx_results3
id|u32
id|hw_tx_results3
suffix:semicolon
multiline_comment|/* see EHCI table 3-12 */
DECL|member|hw_backpointer
id|u32
id|hw_backpointer
suffix:semicolon
multiline_comment|/* see EHCI table 3-13 */
DECL|member|hw_buf_hi
id|u32
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
DECL|member|buf_dma
id|dma_addr_t
id|buf_dma
suffix:semicolon
multiline_comment|/* buffer address */
DECL|member|usecs
r_int
r_int
id|usecs
suffix:semicolon
multiline_comment|/* start bandwidth */
DECL|member|c_usecs
r_int
r_int
id|c_usecs
suffix:semicolon
multiline_comment|/* completion bandwidth */
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
id|u32
id|hw_next
suffix:semicolon
multiline_comment|/* any periodic q entry */
DECL|member|hw_prev
id|u32
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
macro_line|#endif /* __LINUX_EHCI_HCD_H */
eof
