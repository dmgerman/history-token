multiline_comment|/* $Id: eicon.h,v 1.23.6.4 2001/06/09 15:14:16 kai Exp $&n; *&n; * ISDN low-level module for Eicon active ISDN-Cards.&n; *&n; * Copyright 1998    by Fritz Elfert (fritz@isdn4linux.de)&n; * Copyright 1998-2000  by Armin Schindler (mac@melware.de) &n; * Copyright 1999,2000  Cytronics &amp; Melware (info@melware.de)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; *&n; */
macro_line|#ifndef eicon_h
DECL|macro|eicon_h
mdefine_line|#define eicon_h
DECL|macro|EICON_IOCTL_SETMMIO
mdefine_line|#define EICON_IOCTL_SETMMIO   0
DECL|macro|EICON_IOCTL_GETMMIO
mdefine_line|#define EICON_IOCTL_GETMMIO   1
DECL|macro|EICON_IOCTL_SETIRQ
mdefine_line|#define EICON_IOCTL_SETIRQ    2
DECL|macro|EICON_IOCTL_GETIRQ
mdefine_line|#define EICON_IOCTL_GETIRQ    3
DECL|macro|EICON_IOCTL_LOADBOOT
mdefine_line|#define EICON_IOCTL_LOADBOOT  4
DECL|macro|EICON_IOCTL_ADDCARD
mdefine_line|#define EICON_IOCTL_ADDCARD   5
DECL|macro|EICON_IOCTL_GETTYPE
mdefine_line|#define EICON_IOCTL_GETTYPE   6
DECL|macro|EICON_IOCTL_LOADPCI
mdefine_line|#define EICON_IOCTL_LOADPCI   7 
DECL|macro|EICON_IOCTL_LOADISA
mdefine_line|#define EICON_IOCTL_LOADISA   8 
DECL|macro|EICON_IOCTL_GETVER
mdefine_line|#define EICON_IOCTL_GETVER    9 
DECL|macro|EICON_IOCTL_GETXLOG
mdefine_line|#define EICON_IOCTL_GETXLOG  10 
DECL|macro|EICON_IOCTL_MANIF
mdefine_line|#define EICON_IOCTL_MANIF    90 
DECL|macro|EICON_IOCTL_FREEIT
mdefine_line|#define EICON_IOCTL_FREEIT   97
DECL|macro|EICON_IOCTL_TEST
mdefine_line|#define EICON_IOCTL_TEST     98
DECL|macro|EICON_IOCTL_DEBUGVAR
mdefine_line|#define EICON_IOCTL_DEBUGVAR 99
DECL|macro|EICON_IOCTL_DIA_OFFSET
mdefine_line|#define EICON_IOCTL_DIA_OFFSET&t;100
multiline_comment|/* Bus types */
DECL|macro|EICON_BUS_ISA
mdefine_line|#define EICON_BUS_ISA          1
DECL|macro|EICON_BUS_MCA
mdefine_line|#define EICON_BUS_MCA          2
DECL|macro|EICON_BUS_PCI
mdefine_line|#define EICON_BUS_PCI          3
multiline_comment|/* Constants for describing Card-Type */
DECL|macro|EICON_CTYPE_S
mdefine_line|#define EICON_CTYPE_S            0
DECL|macro|EICON_CTYPE_SX
mdefine_line|#define EICON_CTYPE_SX           1
DECL|macro|EICON_CTYPE_SCOM
mdefine_line|#define EICON_CTYPE_SCOM         2
DECL|macro|EICON_CTYPE_QUADRO
mdefine_line|#define EICON_CTYPE_QUADRO       3
DECL|macro|EICON_CTYPE_S2M
mdefine_line|#define EICON_CTYPE_S2M          4
DECL|macro|EICON_CTYPE_MAESTRA
mdefine_line|#define EICON_CTYPE_MAESTRA      5
DECL|macro|EICON_CTYPE_MAESTRAQ
mdefine_line|#define EICON_CTYPE_MAESTRAQ     6
DECL|macro|EICON_CTYPE_MAESTRAQ_U
mdefine_line|#define EICON_CTYPE_MAESTRAQ_U   7
DECL|macro|EICON_CTYPE_MAESTRAP
mdefine_line|#define EICON_CTYPE_MAESTRAP     8
DECL|macro|EICON_CTYPE_ISABRI
mdefine_line|#define EICON_CTYPE_ISABRI       0x10
DECL|macro|EICON_CTYPE_ISAPRI
mdefine_line|#define EICON_CTYPE_ISAPRI       0x20
DECL|macro|EICON_CTYPE_MASK
mdefine_line|#define EICON_CTYPE_MASK         0x0f
DECL|macro|EICON_CTYPE_QUADRO_NR
mdefine_line|#define EICON_CTYPE_QUADRO_NR(n) (n&lt;&lt;4)
DECL|macro|MAX_HEADER_LEN
mdefine_line|#define MAX_HEADER_LEN 10
DECL|macro|MAX_STATUS_BUFFER
mdefine_line|#define MAX_STATUS_BUFFER&t;150
multiline_comment|/* Struct for adding new cards */
DECL|struct|eicon_cdef
r_typedef
r_struct
id|eicon_cdef
(brace
DECL|member|membase
r_int
id|membase
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|id
r_char
id|id
(braket
l_int|10
)braket
suffix:semicolon
DECL|typedef|eicon_cdef
)brace
id|eicon_cdef
suffix:semicolon
DECL|macro|EICON_ISA_BOOT_MEMCHK
mdefine_line|#define EICON_ISA_BOOT_MEMCHK 1
DECL|macro|EICON_ISA_BOOT_NORMAL
mdefine_line|#define EICON_ISA_BOOT_NORMAL 2
multiline_comment|/* Struct for downloading protocol via ioctl for ISA cards */
multiline_comment|/* same struct for downloading protocol via ioctl for MCA cards */
r_typedef
r_struct
(brace
multiline_comment|/* start-up parameters */
DECL|member|tei
r_int
r_char
id|tei
suffix:semicolon
DECL|member|nt2
r_int
r_char
id|nt2
suffix:semicolon
DECL|member|skip1
r_int
r_char
id|skip1
suffix:semicolon
DECL|member|WatchDog
r_int
r_char
id|WatchDog
suffix:semicolon
DECL|member|Permanent
r_int
r_char
id|Permanent
suffix:semicolon
DECL|member|XInterface
r_int
r_char
id|XInterface
suffix:semicolon
DECL|member|StableL2
r_int
r_char
id|StableL2
suffix:semicolon
DECL|member|NoOrderCheck
r_int
r_char
id|NoOrderCheck
suffix:semicolon
DECL|member|HandsetType
r_int
r_char
id|HandsetType
suffix:semicolon
DECL|member|skip2
r_int
r_char
id|skip2
suffix:semicolon
DECL|member|LowChannel
r_int
r_char
id|LowChannel
suffix:semicolon
DECL|member|ProtVersion
r_int
r_char
id|ProtVersion
suffix:semicolon
DECL|member|Crc4
r_int
r_char
id|Crc4
suffix:semicolon
DECL|member|Loopback
r_int
r_char
id|Loopback
suffix:semicolon
DECL|member|oad
r_int
r_char
id|oad
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|osa
r_int
r_char
id|osa
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|spid
r_int
r_char
id|spid
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|boot_opt
r_int
r_char
id|boot_opt
suffix:semicolon
DECL|member|bootstrap_len
r_int
r_int
id|bootstrap_len
suffix:semicolon
DECL|member|firmware_len
r_int
r_int
id|firmware_len
suffix:semicolon
DECL|member|code
r_int
r_char
id|code
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Rest (bootstrap- and firmware code) will be allocated */
DECL|typedef|eicon_isa_codebuf
)brace
id|eicon_isa_codebuf
suffix:semicolon
multiline_comment|/* Data for downloading protocol via ioctl */
r_typedef
r_union
(brace
DECL|member|isa
id|eicon_isa_codebuf
id|isa
suffix:semicolon
DECL|member|mca
id|eicon_isa_codebuf
id|mca
suffix:semicolon
DECL|typedef|eicon_codebuf
)brace
id|eicon_codebuf
suffix:semicolon
multiline_comment|/* Data for Management interface */
r_typedef
r_struct
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|pos
r_int
id|pos
suffix:semicolon
DECL|member|length
r_int
id|length
(braket
l_int|50
)braket
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
l_int|700
)braket
suffix:semicolon
DECL|typedef|eicon_manifbuf
)brace
id|eicon_manifbuf
suffix:semicolon
DECL|macro|TRACE_OK
mdefine_line|#define TRACE_OK                 (1)
macro_line|#ifdef __KERNEL__
multiline_comment|/* Kernel includes */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/isdn.h&gt;
macro_line|#include &lt;linux/isdnif.h&gt;
r_typedef
r_struct
(brace
DECL|member|length
id|__u16
id|length
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* length of data/parameter field */
DECL|member|P
id|__u8
id|P
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* data/parameter field */
DECL|typedef|eicon_PBUFFER
)brace
id|eicon_PBUFFER
suffix:semicolon
macro_line|#include &quot;eicon_isa.h&quot;
macro_line|#include &quot;idi.h&quot;
r_typedef
r_struct
(brace
DECL|member|NextReq
id|__u16
id|NextReq
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* pointer to next Req Buffer */
DECL|member|NextRc
id|__u16
id|NextRc
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* pointer to next Rc Buffer  */
DECL|member|NextInd
id|__u16
id|NextInd
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* pointer to next Ind Buffer */
DECL|member|ReqInput
id|__u8
id|ReqInput
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* number of Req Buffers sent */
DECL|member|ReqOutput
id|__u8
id|ReqOutput
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* number of Req Buffers returned */
DECL|member|ReqReserved
id|__u8
id|ReqReserved
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*number of Req Buffers reserved */
DECL|member|Int
id|__u8
id|Int
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* ISDN-P interrupt           */
DECL|member|XLock
id|__u8
id|XLock
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Lock field for arbitration */
DECL|member|RcOutput
id|__u8
id|RcOutput
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* number of Rc buffers received */
DECL|member|IndOutput
id|__u8
id|IndOutput
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* number of Ind buffers received */
DECL|member|IMask
id|__u8
id|IMask
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Interrupt Mask Flag        */
DECL|member|Reserved1
id|__u8
id|Reserved1
(braket
l_int|2
)braket
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* reserved field, do not use */
DECL|member|ReadyInt
id|__u8
id|ReadyInt
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* request field for ready int */
DECL|member|Reserved2
id|__u8
id|Reserved2
(braket
l_int|12
)braket
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* reserved field, do not use */
DECL|member|InterfaceType
id|__u8
id|InterfaceType
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* interface type 1=16K    */
DECL|member|Signature
id|__u16
id|Signature
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* ISDN-P initialized ind  */
DECL|member|B
id|__u8
id|B
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* buffer space for Req,Ind and Rc */
DECL|typedef|eicon_pr_ram
)brace
id|eicon_pr_ram
suffix:semicolon
multiline_comment|/* Macro for delay via schedule() */
DECL|macro|SLEEP
mdefine_line|#define SLEEP(j) {                     &bslash;&n;  set_current_state(TASK_UNINTERRUPTIBLE); &bslash;&n;  schedule_timeout(j);                 &bslash;&n;}
r_typedef
r_struct
(brace
DECL|member|Req
id|__u8
id|Req
suffix:semicolon
multiline_comment|/* pending request          */
DECL|member|Rc
id|__u8
id|Rc
suffix:semicolon
multiline_comment|/* return code received     */
DECL|member|Ind
id|__u8
id|Ind
suffix:semicolon
multiline_comment|/* indication received      */
DECL|member|ReqCh
id|__u8
id|ReqCh
suffix:semicolon
multiline_comment|/* channel of current Req   */
DECL|member|RcCh
id|__u8
id|RcCh
suffix:semicolon
multiline_comment|/* channel of current Rc    */
DECL|member|IndCh
id|__u8
id|IndCh
suffix:semicolon
multiline_comment|/* channel of current Ind   */
DECL|member|D3Id
id|__u8
id|D3Id
suffix:semicolon
multiline_comment|/* ID used by this entity   */
DECL|member|B2Id
id|__u8
id|B2Id
suffix:semicolon
multiline_comment|/* ID used by this entity   */
DECL|member|GlobalId
id|__u8
id|GlobalId
suffix:semicolon
multiline_comment|/* reserved field           */
DECL|member|XNum
id|__u8
id|XNum
suffix:semicolon
multiline_comment|/* number of X-buffers      */
DECL|member|RNum
id|__u8
id|RNum
suffix:semicolon
multiline_comment|/* number of R-buffers      */
DECL|member|X
r_struct
id|sk_buff_head
id|X
suffix:semicolon
multiline_comment|/* X-buffer queue           */
DECL|member|R
r_struct
id|sk_buff_head
id|R
suffix:semicolon
multiline_comment|/* R-buffer queue           */
DECL|member|RNR
id|__u8
id|RNR
suffix:semicolon
multiline_comment|/* receive not ready flag   */
DECL|member|complete
id|__u8
id|complete
suffix:semicolon
multiline_comment|/* receive complete status  */
DECL|member|busy
id|__u8
id|busy
suffix:semicolon
multiline_comment|/* busy flag                */
DECL|member|ref
id|__u16
id|ref
suffix:semicolon
multiline_comment|/* saved reference          */
DECL|typedef|entity
)brace
id|entity
suffix:semicolon
DECL|macro|FAX_MAX_SCANLINE
mdefine_line|#define FAX_MAX_SCANLINE 256
r_typedef
r_struct
(brace
DECL|member|PrevObject
id|__u8
id|PrevObject
suffix:semicolon
DECL|member|NextObject
id|__u8
id|NextObject
suffix:semicolon
DECL|member|abLine
id|__u8
id|abLine
(braket
id|FAX_MAX_SCANLINE
)braket
suffix:semicolon
DECL|member|abFrame
id|__u8
id|abFrame
(braket
id|FAX_MAX_SCANLINE
)braket
suffix:semicolon
DECL|member|LineLen
r_int
r_int
id|LineLen
suffix:semicolon
DECL|member|LineDataLen
r_int
r_int
id|LineDataLen
suffix:semicolon
DECL|member|LineData
id|__u32
id|LineData
suffix:semicolon
DECL|member|NullBytesPos
r_int
r_int
id|NullBytesPos
suffix:semicolon
DECL|member|NullByteExist
id|__u8
id|NullByteExist
suffix:semicolon
DECL|member|PageCount
r_int
id|PageCount
suffix:semicolon
DECL|member|Dle
id|__u8
id|Dle
suffix:semicolon
DECL|member|Eop
id|__u8
id|Eop
suffix:semicolon
DECL|typedef|eicon_ch_fax_buf
)brace
id|eicon_ch_fax_buf
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|No
r_int
id|No
suffix:semicolon
multiline_comment|/* Channel Number&t;        */
DECL|member|fsm_state
r_int
r_int
id|fsm_state
suffix:semicolon
multiline_comment|/* Current D-Channel state     */
DECL|member|statectrl
r_int
r_int
id|statectrl
suffix:semicolon
multiline_comment|/* State controling bits&t;*/
DECL|member|eazmask
r_int
r_int
id|eazmask
suffix:semicolon
multiline_comment|/* EAZ-Mask for this Channel   */
DECL|member|queued
r_int
id|queued
suffix:semicolon
multiline_comment|/* User-Data Bytes in TX queue */
DECL|member|pqueued
r_int
id|pqueued
suffix:semicolon
multiline_comment|/* User-Data Packets in TX queue */
DECL|member|waitq
r_int
id|waitq
suffix:semicolon
multiline_comment|/* User-Data Bytes in wait queue */
DECL|member|waitpq
r_int
id|waitpq
suffix:semicolon
multiline_comment|/* User-Data Bytes in packet queue */
DECL|member|tskb1
r_struct
id|sk_buff
op_star
id|tskb1
suffix:semicolon
multiline_comment|/* temp skb 1&t;&t;&t;*/
DECL|member|tskb2
r_struct
id|sk_buff
op_star
id|tskb2
suffix:semicolon
multiline_comment|/* temp skb 2&t;&t;&t;*/
DECL|member|l2prot
r_int
r_char
id|l2prot
suffix:semicolon
multiline_comment|/* Layer 2 protocol            */
DECL|member|l3prot
r_int
r_char
id|l3prot
suffix:semicolon
multiline_comment|/* Layer 3 protocol            */
macro_line|#ifdef CONFIG_ISDN_TTY_FAX
DECL|member|fax
id|T30_s
op_star
id|fax
suffix:semicolon
multiline_comment|/* pointer to fax data in LL&t;*/
DECL|member|fax2
id|eicon_ch_fax_buf
id|fax2
suffix:semicolon
multiline_comment|/* fax related struct&t;&t;*/
macro_line|#endif
DECL|member|e
id|entity
id|e
suffix:semicolon
multiline_comment|/* Native Entity&t;&t;*/
DECL|member|de
id|ENTITY
id|de
suffix:semicolon
multiline_comment|/* Divas D Entity &t;&t;*/
DECL|member|be
id|ENTITY
id|be
suffix:semicolon
multiline_comment|/* Divas B Entity &t;&t;*/
DECL|member|cpn
r_char
id|cpn
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* remember cpn&t;&t;*/
DECL|member|oad
r_char
id|oad
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* remember oad&t;&t;*/
DECL|member|dsa
r_char
id|dsa
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* remember dsa&t;&t;*/
DECL|member|osa
r_char
id|osa
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* remember osa&t;&t;*/
DECL|member|cause
r_int
r_char
id|cause
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Last Cause&t;&t;&t;*/
DECL|member|si1
r_int
r_char
id|si1
suffix:semicolon
DECL|member|si2
r_int
r_char
id|si2
suffix:semicolon
DECL|member|plan
r_int
r_char
id|plan
suffix:semicolon
DECL|member|screen
r_int
r_char
id|screen
suffix:semicolon
DECL|typedef|eicon_chan
)brace
id|eicon_chan
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ptr
id|eicon_chan
op_star
id|ptr
suffix:semicolon
DECL|typedef|eicon_chan_ptr
)brace
id|eicon_chan_ptr
suffix:semicolon
macro_line|#include &quot;eicon_pci.h&quot;
DECL|macro|EICON_FLAGS_RUNNING
mdefine_line|#define EICON_FLAGS_RUNNING  1 /* Cards driver activated */
DECL|macro|EICON_FLAGS_PVALID
mdefine_line|#define EICON_FLAGS_PVALID   2 /* Cards port is valid    */
DECL|macro|EICON_FLAGS_IVALID
mdefine_line|#define EICON_FLAGS_IVALID   4 /* Cards irq is valid     */
DECL|macro|EICON_FLAGS_MVALID
mdefine_line|#define EICON_FLAGS_MVALID   8 /* Cards membase is valid */
DECL|macro|EICON_FLAGS_LOADED
mdefine_line|#define EICON_FLAGS_LOADED   8 /* Firmware loaded        */
multiline_comment|/* D-Channel states */
DECL|macro|EICON_STATE_NULL
mdefine_line|#define EICON_STATE_NULL     0
DECL|macro|EICON_STATE_ICALL
mdefine_line|#define EICON_STATE_ICALL    1
DECL|macro|EICON_STATE_OCALL
mdefine_line|#define EICON_STATE_OCALL    2
DECL|macro|EICON_STATE_IWAIT
mdefine_line|#define EICON_STATE_IWAIT    3
DECL|macro|EICON_STATE_OWAIT
mdefine_line|#define EICON_STATE_OWAIT    4
DECL|macro|EICON_STATE_IBWAIT
mdefine_line|#define EICON_STATE_IBWAIT   5
DECL|macro|EICON_STATE_OBWAIT
mdefine_line|#define EICON_STATE_OBWAIT   6
DECL|macro|EICON_STATE_BWAIT
mdefine_line|#define EICON_STATE_BWAIT    7
DECL|macro|EICON_STATE_BHWAIT
mdefine_line|#define EICON_STATE_BHWAIT   8
DECL|macro|EICON_STATE_BHWAIT2
mdefine_line|#define EICON_STATE_BHWAIT2  9
DECL|macro|EICON_STATE_DHWAIT
mdefine_line|#define EICON_STATE_DHWAIT  10
DECL|macro|EICON_STATE_DHWAIT2
mdefine_line|#define EICON_STATE_DHWAIT2 11
DECL|macro|EICON_STATE_BSETUP
mdefine_line|#define EICON_STATE_BSETUP  12
DECL|macro|EICON_STATE_ACTIVE
mdefine_line|#define EICON_STATE_ACTIVE  13
DECL|macro|EICON_STATE_ICALLW
mdefine_line|#define EICON_STATE_ICALLW  14
DECL|macro|EICON_STATE_LISTEN
mdefine_line|#define EICON_STATE_LISTEN  15
DECL|macro|EICON_STATE_WMCONN
mdefine_line|#define EICON_STATE_WMCONN  16
DECL|macro|EICON_MAX_QUEUE
mdefine_line|#define EICON_MAX_QUEUE  2138
r_typedef
r_union
(brace
DECL|member|isa
id|eicon_isa_card
id|isa
suffix:semicolon
DECL|member|pci
id|eicon_pci_card
id|pci
suffix:semicolon
DECL|member|mca
id|eicon_isa_card
id|mca
suffix:semicolon
DECL|typedef|eicon_hwif
)brace
id|eicon_hwif
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ret
id|__u8
id|ret
suffix:semicolon
DECL|member|id
id|__u8
id|id
suffix:semicolon
DECL|member|ch
id|__u8
id|ch
suffix:semicolon
DECL|typedef|eicon_ack
)brace
id|eicon_ack
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|code
id|__u8
id|code
suffix:semicolon
DECL|member|id
id|__u8
id|id
suffix:semicolon
DECL|member|ch
id|__u8
id|ch
suffix:semicolon
DECL|typedef|eicon_req
)brace
id|eicon_req
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ret
id|__u8
id|ret
suffix:semicolon
DECL|member|id
id|__u8
id|id
suffix:semicolon
DECL|member|ch
id|__u8
id|ch
suffix:semicolon
DECL|member|more
id|__u8
id|more
suffix:semicolon
DECL|typedef|eicon_indhdr
)brace
id|eicon_indhdr
suffix:semicolon
multiline_comment|/*&n; * Per card driver data&n; */
DECL|struct|eicon_card
r_typedef
r_struct
id|eicon_card
(brace
DECL|member|hwif
id|eicon_hwif
id|hwif
suffix:semicolon
multiline_comment|/* Hardware dependant interface     */
DECL|member|d
id|DESCRIPTOR
op_star
id|d
suffix:semicolon
multiline_comment|/* IDI Descriptor&t;&t;     */
DECL|member|ptype
id|u_char
id|ptype
suffix:semicolon
multiline_comment|/* Protocol type (1TR6 or Euro)     */
DECL|member|bus
id|u_char
id|bus
suffix:semicolon
multiline_comment|/* Bustype (ISA, MCA, PCI)          */
DECL|member|type
id|u_char
id|type
suffix:semicolon
multiline_comment|/* Cardtype (EICON_CTYPE_...)       */
DECL|member|qnext
r_struct
id|eicon_card
op_star
id|qnext
suffix:semicolon
multiline_comment|/* Pointer to next quadro adapter   */
DECL|member|Feature
r_int
id|Feature
suffix:semicolon
multiline_comment|/* Protocol Feature Value           */
DECL|member|next
r_struct
id|eicon_card
op_star
id|next
suffix:semicolon
multiline_comment|/* Pointer to next device struct    */
DECL|member|myid
r_int
id|myid
suffix:semicolon
multiline_comment|/* Driver-Nr. assigned by linklevel */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Statusflags                      */
DECL|member|rcvq
r_struct
id|sk_buff_head
id|rcvq
suffix:semicolon
multiline_comment|/* Receive-Message queue            */
DECL|member|sndq
r_struct
id|sk_buff_head
id|sndq
suffix:semicolon
multiline_comment|/* Send-Message queue               */
DECL|member|rackq
r_struct
id|sk_buff_head
id|rackq
suffix:semicolon
multiline_comment|/* Req-Ack-Message queue            */
DECL|member|sackq
r_struct
id|sk_buff_head
id|sackq
suffix:semicolon
multiline_comment|/* Data-Ack-Message queue           */
DECL|member|statq
r_struct
id|sk_buff_head
id|statq
suffix:semicolon
multiline_comment|/* Status-Message queue             */
DECL|member|statq_entries
r_int
id|statq_entries
suffix:semicolon
DECL|member|snd_tq
r_struct
id|tq_struct
id|snd_tq
suffix:semicolon
multiline_comment|/* Task struct for xmit bh          */
DECL|member|rcv_tq
r_struct
id|tq_struct
id|rcv_tq
suffix:semicolon
multiline_comment|/* Task struct for rcv bh           */
DECL|member|ack_tq
r_struct
id|tq_struct
id|ack_tq
suffix:semicolon
multiline_comment|/* Task struct for ack bh           */
DECL|member|IdTable
id|eicon_chan
op_star
id|IdTable
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* Table to find entity   */
DECL|member|ref_in
id|__u16
id|ref_in
suffix:semicolon
DECL|member|ref_out
id|__u16
id|ref_out
suffix:semicolon
DECL|member|nchannels
r_int
id|nchannels
suffix:semicolon
multiline_comment|/* Number of B-Channels             */
DECL|member|ReadyInt
r_int
id|ReadyInt
suffix:semicolon
multiline_comment|/* Ready Interrupt&t;&t;     */
DECL|member|bch
id|eicon_chan
op_star
id|bch
suffix:semicolon
multiline_comment|/* B-Channel status/control         */
DECL|member|dbuf
id|DBUFFER
op_star
id|dbuf
suffix:semicolon
multiline_comment|/* Dbuffer for Diva Server&t;     */
DECL|member|sbuf
id|BUFFERS
op_star
id|sbuf
suffix:semicolon
multiline_comment|/* Buffer for Diva Server&t;     */
DECL|member|sbufp
r_char
op_star
id|sbufp
suffix:semicolon
multiline_comment|/* Data Buffer for Diva Server&t;     */
DECL|member|interface
id|isdn_if
id|interface
suffix:semicolon
multiline_comment|/* Interface to upper layer         */
DECL|member|regname
r_char
id|regname
(braket
l_int|35
)braket
suffix:semicolon
multiline_comment|/* Drivers card name &t;&t;     */
macro_line|#ifdef CONFIG_MCA
DECL|member|mca_slot
r_int
id|mca_slot
suffix:semicolon
multiline_comment|/* # of cards MCA slot              */
DECL|member|mca_io
r_int
id|mca_io
suffix:semicolon
multiline_comment|/* MCA cards IO port&t;&t;     */
macro_line|#endif /* CONFIG_MCA */
DECL|typedef|eicon_card
)brace
id|eicon_card
suffix:semicolon
macro_line|#include &quot;eicon_idi.h&quot;
r_extern
id|eicon_card
op_star
id|cards
suffix:semicolon
r_extern
r_char
op_star
id|eicon_ctype_name
(braket
)braket
suffix:semicolon
DECL|function|eicon_schedule_tx
r_extern
id|__inline__
r_void
id|eicon_schedule_tx
c_func
(paren
id|eicon_card
op_star
id|card
)paren
(brace
id|queue_task
c_func
(paren
op_amp
id|card-&gt;snd_tq
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
DECL|function|eicon_schedule_rx
r_extern
id|__inline__
r_void
id|eicon_schedule_rx
c_func
(paren
id|eicon_card
op_star
id|card
)paren
(brace
id|queue_task
c_func
(paren
op_amp
id|card-&gt;rcv_tq
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
DECL|function|eicon_schedule_ack
r_extern
id|__inline__
r_void
id|eicon_schedule_ack
c_func
(paren
id|eicon_card
op_star
id|card
)paren
(brace
id|queue_task
c_func
(paren
op_amp
id|card-&gt;ack_tq
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
r_extern
r_int
id|eicon_addcard
c_func
(paren
r_int
comma
r_int
comma
r_int
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|eicon_io_transmit
c_func
(paren
id|eicon_card
op_star
id|card
)paren
suffix:semicolon
r_extern
r_void
id|eicon_irq
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
suffix:semicolon
r_extern
r_void
id|eicon_io_rcv_dispatch
c_func
(paren
id|eicon_card
op_star
id|ccard
)paren
suffix:semicolon
r_extern
r_void
id|eicon_io_ack_dispatch
c_func
(paren
id|eicon_card
op_star
id|ccard
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MCA
r_extern
r_int
id|eicon_mca_find_card
c_func
(paren
r_int
comma
r_int
comma
r_int
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|eicon_mca_probe
c_func
(paren
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|eicon_info
c_func
(paren
r_char
op_star
comma
r_int
comma
r_void
op_star
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_MCA */
r_extern
id|ulong
id|DebugVar
suffix:semicolon
r_extern
r_void
id|eicon_log
c_func
(paren
id|eicon_card
op_star
id|card
comma
r_int
id|level
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|eicon_putstatus
c_func
(paren
id|eicon_card
op_star
id|card
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
r_extern
id|spinlock_t
id|eicon_lock
suffix:semicolon
macro_line|#endif  /* __KERNEL__ */
macro_line|#endif&t;/* eicon_h */
eof
