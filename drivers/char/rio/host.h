multiline_comment|/*&n;** -----------------------------------------------------------------------------&n;**&n;**  Perle Specialix driver for Linux&n;**  Ported from existing RIO Driver for SCO sources.&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**&t;Module&t;&t;: host.h&n;**&t;SID&t;&t;: 1.2&n;**&t;Last Modified&t;: 11/6/98 11:34:10&n;**&t;Retrieved&t;: 11/6/98 11:34:21&n;**&n;**  ident @(#)host.h&t;1.2&n;**&n;** -----------------------------------------------------------------------------&n;*/
macro_line|#ifndef __rio_host_h__
DECL|macro|__rio_host_h__
mdefine_line|#define __rio_host_h__
macro_line|#ifdef SCCS_LABELS
macro_line|#ifndef lint
DECL|variable|_host_h_sccs_
r_static
r_char
op_star
id|_host_h_sccs_
op_assign
l_string|&quot;@(#)host.h&t;1.2&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n;** the host structure - one per host card in the system.&n;*/
DECL|macro|MAX_EXTRA_UNITS
mdefine_line|#define&t;MAX_EXTRA_UNITS&t;64
multiline_comment|/*&n;**    Host data structure. This is used for the software equiv. of&n;**    the host.&n;*/
DECL|struct|Host
r_struct
id|Host
(brace
DECL|member|Type
id|uchar
id|Type
suffix:semicolon
multiline_comment|/* RIO_EISA, RIO_MCA, ... */
DECL|member|Ivec
id|uchar
id|Ivec
suffix:semicolon
multiline_comment|/* POLLED or ivec number */
DECL|member|Mode
id|uchar
id|Mode
suffix:semicolon
multiline_comment|/* Control stuff */
DECL|member|Slot
id|uchar
id|Slot
suffix:semicolon
multiline_comment|/* Slot */
DECL|member|Caddr
r_volatile
id|caddr_t
id|Caddr
suffix:semicolon
multiline_comment|/* KV address of DPRAM */
DECL|member|CardP
r_volatile
r_struct
id|DpRam
op_star
id|CardP
suffix:semicolon
multiline_comment|/* KV address of DPRAM, with overlay */
DECL|member|PaddrP
id|paddr_t
id|PaddrP
suffix:semicolon
multiline_comment|/* Phys. address of DPRAM */
DECL|member|Name
r_char
id|Name
(braket
id|MAX_NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* The name of the host */
DECL|member|UniqueNum
id|uint
id|UniqueNum
suffix:semicolon
multiline_comment|/* host unique number */
DECL|member|HostLock
id|spinlock_t
id|HostLock
suffix:semicolon
multiline_comment|/* Lock structure for MPX */
multiline_comment|/*struct pci_devinfo    PciDevInfo; */
multiline_comment|/* PCI Bus/Device/Function stuff */
multiline_comment|/*struct lockb&t;    HostLock;  */
multiline_comment|/* Lock structure for MPX */
DECL|member|WorkToBeDone
id|uint
id|WorkToBeDone
suffix:semicolon
multiline_comment|/* set to true each interrupt */
DECL|member|InIntr
id|uint
id|InIntr
suffix:semicolon
multiline_comment|/* Being serviced? */
DECL|member|IntSrvDone
id|uint
id|IntSrvDone
suffix:semicolon
multiline_comment|/* host&squot;s interrupt has been serviced */
DECL|member|Copy
r_int
(paren
op_star
id|Copy
)paren
(paren
id|caddr_t
comma
id|caddr_t
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* copy func */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/*&n;    **               I M P O R T A N T !&n;    **&n;    ** The rest of this data structure is cleared to zero after&n;    ** a RIO_HOST_FOAD command.&n;    */
DECL|member|Flags
id|ulong
id|Flags
suffix:semicolon
multiline_comment|/* Whats going down */
DECL|macro|RC_WAITING
mdefine_line|#define RC_WAITING            0
DECL|macro|RC_STARTUP
mdefine_line|#define RC_STARTUP            1
DECL|macro|RC_RUNNING
mdefine_line|#define RC_RUNNING            2
DECL|macro|RC_STUFFED
mdefine_line|#define RC_STUFFED            3
DECL|macro|RC_SOMETHING
mdefine_line|#define RC_SOMETHING          4
DECL|macro|RC_SOMETHING_NEW
mdefine_line|#define RC_SOMETHING_NEW      5
DECL|macro|RC_SOMETHING_ELSE
mdefine_line|#define RC_SOMETHING_ELSE     6
DECL|macro|RC_READY
mdefine_line|#define RC_READY              7
DECL|macro|RUN_STATE
mdefine_line|#define RUN_STATE             7
multiline_comment|/*&n;** Boot mode applies to the way in which hosts in this system will&n;** boot RTAs&n;*/
DECL|macro|RC_BOOT_ALL
mdefine_line|#define RC_BOOT_ALL           0x8&t;/* Boot all RTAs attached */
DECL|macro|RC_BOOT_OWN
mdefine_line|#define RC_BOOT_OWN           0x10&t;/* Only boot RTAs bound to this system */
DECL|macro|RC_BOOT_NONE
mdefine_line|#define RC_BOOT_NONE          0x20&t;/* Don&squot;t boot any RTAs (slave mode) */
DECL|member|Topology
r_struct
id|Top
id|Topology
(braket
id|LINKS_PER_UNIT
)braket
suffix:semicolon
multiline_comment|/* one per link */
DECL|member|Mapping
r_struct
id|Map
id|Mapping
(braket
id|MAX_RUP
)braket
suffix:semicolon
multiline_comment|/* Mappings for host */
DECL|member|PhbP
r_struct
id|PHB
op_star
id|PhbP
suffix:semicolon
multiline_comment|/* Pointer to the PHB array */
DECL|member|PhbNumP
id|ushort
op_star
id|PhbNumP
suffix:semicolon
multiline_comment|/* Ptr to Number of PHB&squot;s */
DECL|member|LinkStrP
r_struct
id|LPB
op_star
id|LinkStrP
suffix:semicolon
multiline_comment|/* Link Structure Array */
DECL|member|RupP
r_struct
id|RUP
op_star
id|RupP
suffix:semicolon
multiline_comment|/* Sixteen real rups here */
DECL|member|ParmMapP
r_struct
id|PARM_MAP
op_star
id|ParmMapP
suffix:semicolon
multiline_comment|/* points to the parmmap */
DECL|member|ExtraUnits
id|uint
id|ExtraUnits
(braket
id|MAX_EXTRA_UNITS
)braket
suffix:semicolon
multiline_comment|/* unknown things */
DECL|member|NumExtraBooted
id|uint
id|NumExtraBooted
suffix:semicolon
multiline_comment|/* how many of the above */
multiline_comment|/*&n;    ** Twenty logical rups.&n;    ** The first sixteen are the real Rup entries (above), the last four&n;    ** are the link RUPs.&n;    */
DECL|member|UnixRups
r_struct
id|UnixRup
id|UnixRups
(braket
id|MAX_RUP
op_plus
id|LINKS_PER_UNIT
)braket
suffix:semicolon
DECL|member|timeout_id
r_int
id|timeout_id
suffix:semicolon
multiline_comment|/* For calling 100 ms delays */
DECL|member|timeout_sem
r_int
id|timeout_sem
suffix:semicolon
multiline_comment|/* For calling 100 ms delays */
DECL|member|locks
r_int
id|locks
suffix:semicolon
multiline_comment|/* long req&squot;d for set_bit --RR */
DECL|member|____end_marker____
r_char
id|____end_marker____
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|Control
mdefine_line|#define Control      CardP-&gt;DpControl
DECL|macro|SetInt
mdefine_line|#define SetInt       CardP-&gt;DpSetInt
DECL|macro|ResetTpu
mdefine_line|#define ResetTpu     CardP-&gt;DpResetTpu
DECL|macro|ResetInt
mdefine_line|#define ResetInt     CardP-&gt;DpResetInt
DECL|macro|Signature
mdefine_line|#define Signature    CardP-&gt;DpSignature
DECL|macro|Sram1
mdefine_line|#define Sram1        CardP-&gt;DpSram1
DECL|macro|Sram2
mdefine_line|#define Sram2        CardP-&gt;DpSram2
DECL|macro|Sram3
mdefine_line|#define Sram3        CardP-&gt;DpSram3
DECL|macro|Scratch
mdefine_line|#define Scratch      CardP-&gt;DpScratch
DECL|macro|__ParmMapR
mdefine_line|#define __ParmMapR   CardP-&gt;DpParmMapR
DECL|macro|SLX
mdefine_line|#define SLX          CardP-&gt;DpSlx
DECL|macro|Revision
mdefine_line|#define Revision     CardP-&gt;DpRevision
DECL|macro|Unique
mdefine_line|#define Unique       CardP-&gt;DpUnique
DECL|macro|Year
mdefine_line|#define Year         CardP-&gt;DpYear
DECL|macro|Week
mdefine_line|#define Week         CardP-&gt;DpWeek
DECL|macro|RIO_DUMBPARM
mdefine_line|#define RIO_DUMBPARM 0x0860    /* what not to expect */
macro_line|#endif
eof
