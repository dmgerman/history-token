multiline_comment|/* $Id: i4lididrv.h,v 1.1.2.2 2002/10/02 14:38:37 armin Exp $&n; *&n; * ISDN interface module for Eicon active cards.&n; * I4L - IDI Interface&n; *&n; * Copyright 1998-2000  by Armin Schindler (mac@melware.de) &n; * Copyright 1999-2002  Cytronics &amp; Melware (info@melware.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#ifndef i4lididrv_h
DECL|macro|i4lididrv_h
mdefine_line|#define i4lididrv_h
macro_line|#include &lt;linux/isdn.h&gt;
macro_line|#include &lt;linux/isdnif.h&gt;
macro_line|#include &quot;platform.h&quot;
macro_line|#include &quot;di_defs.h&quot;
DECL|macro|EICON_IOCTL_GETTYPE
mdefine_line|#define EICON_IOCTL_GETTYPE   6
DECL|macro|EICON_IOCTL_LOADPCI
mdefine_line|#define EICON_IOCTL_LOADPCI   7 
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
multiline_comment|/* Macro for delay via schedule() */
DECL|macro|SLEEP
mdefine_line|#define SLEEP(j) {                     &bslash;&n;  set_current_state(TASK_INTERRUPTIBLE); &bslash;&n;  schedule_timeout(j);                 &bslash;&n;}
multiline_comment|/* Kernel includes */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
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
mdefine_line|#define FAX_MAX_SCANLINE 2500 
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
DECL|member|a_para
r_int
r_char
id|a_para
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Additional parameter        */
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
DECL|macro|EICON_FLAGS_RUNNING
mdefine_line|#define EICON_FLAGS_RUNNING  1 /* Cards driver activated */
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
DECL|member|d
id|DESCRIPTOR
id|d
suffix:semicolon
multiline_comment|/* IDI Descriptor&t;&t;     */
DECL|member|ptype
id|u_char
id|ptype
suffix:semicolon
multiline_comment|/* Protocol type (1TR6 or Euro)     */
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
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* spin lock per card&t;&t;     */
DECL|member|tq
r_struct
id|tq_struct
id|tq
suffix:semicolon
multiline_comment|/* task queue for thread            */
DECL|typedef|eicon_card
)brace
id|eicon_card
suffix:semicolon
macro_line|#include &quot;i4l_idi.h&quot;
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
r_void
id|eicon_tx_request
c_func
(paren
r_struct
id|eicon_card
op_star
)paren
suffix:semicolon
r_extern
id|spinlock_t
id|eicon_lock
suffix:semicolon
macro_line|#endif  /* __KERNEL__ */
macro_line|#endif&t;/* i4lididrv_h */
eof
