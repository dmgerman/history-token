multiline_comment|/* $Id: isdnloop.h,v 1.5 2000/11/13 22:51:50 kai Exp $&n;&n; * Loopback lowlevel module for testing of linklevel.&n; *&n; * Copyright 1997 by Fritz Elfert (fritz@isdn4linux.de)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef isdnloop_h
DECL|macro|isdnloop_h
mdefine_line|#define isdnloop_h
DECL|macro|ISDNLOOP_IOCTL_DEBUGVAR
mdefine_line|#define ISDNLOOP_IOCTL_DEBUGVAR  0
DECL|macro|ISDNLOOP_IOCTL_ADDCARD
mdefine_line|#define ISDNLOOP_IOCTL_ADDCARD   1
DECL|macro|ISDNLOOP_IOCTL_LEASEDCFG
mdefine_line|#define ISDNLOOP_IOCTL_LEASEDCFG 2
DECL|macro|ISDNLOOP_IOCTL_STARTUP
mdefine_line|#define ISDNLOOP_IOCTL_STARTUP   3
multiline_comment|/* Struct for adding new cards */
DECL|struct|isdnloop_cdef
r_typedef
r_struct
id|isdnloop_cdef
(brace
DECL|member|id1
r_char
id|id1
(braket
l_int|10
)braket
suffix:semicolon
DECL|typedef|isdnloop_cdef
)brace
id|isdnloop_cdef
suffix:semicolon
multiline_comment|/* Struct for configuring cards */
DECL|struct|isdnloop_sdef
r_typedef
r_struct
id|isdnloop_sdef
(brace
DECL|member|ptype
r_int
id|ptype
suffix:semicolon
DECL|member|num
r_char
id|num
(braket
l_int|3
)braket
(braket
l_int|20
)braket
suffix:semicolon
DECL|typedef|isdnloop_sdef
)brace
id|isdnloop_sdef
suffix:semicolon
macro_line|#if defined(__KERNEL__) || defined(__DEBUGVAR__)
macro_line|#ifdef __KERNEL__
multiline_comment|/* Kernel includes */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
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
macro_line|#include &lt;linux/isdnif.h&gt;
macro_line|#endif                          /* __KERNEL__ */
DECL|macro|ISDNLOOP_FLAGS_B1ACTIVE
mdefine_line|#define ISDNLOOP_FLAGS_B1ACTIVE 1&t;/* B-Channel-1 is open           */
DECL|macro|ISDNLOOP_FLAGS_B2ACTIVE
mdefine_line|#define ISDNLOOP_FLAGS_B2ACTIVE 2&t;/* B-Channel-2 is open           */
DECL|macro|ISDNLOOP_FLAGS_RUNNING
mdefine_line|#define ISDNLOOP_FLAGS_RUNNING  4&t;/* Cards driver activated        */
DECL|macro|ISDNLOOP_FLAGS_RBTIMER
mdefine_line|#define ISDNLOOP_FLAGS_RBTIMER  8&t;/* scheduling of B-Channel-poll  */
DECL|macro|ISDNLOOP_TIMER_BCREAD
mdefine_line|#define ISDNLOOP_TIMER_BCREAD 1 /* B-Channel poll-cycle          */
DECL|macro|ISDNLOOP_TIMER_DCREAD
mdefine_line|#define ISDNLOOP_TIMER_DCREAD (HZ/2)&t;/* D-Channel poll-cycle          */
DECL|macro|ISDNLOOP_TIMER_ALERTWAIT
mdefine_line|#define ISDNLOOP_TIMER_ALERTWAIT (10*HZ)&t;/* Alert timeout                 */
DECL|macro|ISDNLOOP_MAX_SQUEUE
mdefine_line|#define ISDNLOOP_MAX_SQUEUE 65536&t;/* Max. outstanding send-data    */
DECL|macro|ISDNLOOP_BCH
mdefine_line|#define ISDNLOOP_BCH 2          /* channels per card             */
multiline_comment|/*&n; * Per card driver data&n; */
DECL|struct|isdnloop_card
r_typedef
r_struct
id|isdnloop_card
(brace
DECL|member|next
r_struct
id|isdnloop_card
op_star
id|next
suffix:semicolon
multiline_comment|/* Pointer to next device struct    */
r_struct
id|isdnloop_card
DECL|member|rcard
op_star
id|rcard
(braket
id|ISDNLOOP_BCH
)braket
suffix:semicolon
multiline_comment|/* Pointer to &squot;remote&squot; card         */
DECL|member|rch
r_int
id|rch
(braket
id|ISDNLOOP_BCH
)braket
suffix:semicolon
multiline_comment|/* &squot;remote&squot; channel                 */
DECL|member|myid
r_int
id|myid
suffix:semicolon
multiline_comment|/* Driver-Nr. assigned by linklevel */
DECL|member|leased
r_int
id|leased
suffix:semicolon
multiline_comment|/* Flag: This Adapter is connected  */
multiline_comment|/*       to a leased line           */
DECL|member|sil
r_int
id|sil
(braket
id|ISDNLOOP_BCH
)braket
suffix:semicolon
multiline_comment|/* SI&squot;s to listen for               */
DECL|member|eazlist
r_char
id|eazlist
(braket
id|ISDNLOOP_BCH
)braket
(braket
l_int|11
)braket
suffix:semicolon
multiline_comment|/* EAZ&squot;s to listen for              */
DECL|member|s0num
r_char
id|s0num
(braket
l_int|3
)braket
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* 1TR6 base-number or MSN&squot;s        */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Statusflags                      */
DECL|member|ptype
r_int
id|ptype
suffix:semicolon
multiline_comment|/* Protocol type (1TR6 or Euro)     */
DECL|member|st_timer
r_struct
id|timer_list
id|st_timer
suffix:semicolon
multiline_comment|/* Timer for Status-Polls           */
DECL|member|rb_timer
r_struct
id|timer_list
id|rb_timer
suffix:semicolon
multiline_comment|/* Timer for B-Channel-Polls        */
r_struct
id|timer_list
DECL|member|c_timer
id|c_timer
(braket
id|ISDNLOOP_BCH
)braket
suffix:semicolon
multiline_comment|/* Timer for Alerting               */
DECL|member|l2_proto
r_int
id|l2_proto
(braket
id|ISDNLOOP_BCH
)braket
suffix:semicolon
multiline_comment|/* Current layer-2-protocol         */
DECL|member|interface
id|isdn_if
id|interface
suffix:semicolon
multiline_comment|/* Interface to upper layer         */
DECL|member|iptr
r_int
id|iptr
suffix:semicolon
multiline_comment|/* Index to imsg-buffer             */
DECL|member|imsg
r_char
id|imsg
(braket
l_int|60
)braket
suffix:semicolon
multiline_comment|/* Internal buf for status-parsing  */
DECL|member|optr
r_int
id|optr
suffix:semicolon
multiline_comment|/* Index to omsg-buffer             */
DECL|member|omsg
r_char
id|omsg
(braket
l_int|60
)braket
suffix:semicolon
multiline_comment|/* Internal buf for cmd-parsing     */
DECL|member|msg_buf
r_char
id|msg_buf
(braket
l_int|2048
)braket
suffix:semicolon
multiline_comment|/* Buffer for status-messages       */
DECL|member|msg_buf_write
r_char
op_star
id|msg_buf_write
suffix:semicolon
multiline_comment|/* Writepointer for statusbuffer    */
DECL|member|msg_buf_read
r_char
op_star
id|msg_buf_read
suffix:semicolon
multiline_comment|/* Readpointer for statusbuffer     */
DECL|member|msg_buf_end
r_char
op_star
id|msg_buf_end
suffix:semicolon
multiline_comment|/* Pointer to end of statusbuffer   */
DECL|member|sndcount
r_int
id|sndcount
(braket
id|ISDNLOOP_BCH
)braket
suffix:semicolon
multiline_comment|/* Byte-counters for B-Ch.-send     */
r_struct
id|sk_buff_head
DECL|member|bqueue
id|bqueue
(braket
id|ISDNLOOP_BCH
)braket
suffix:semicolon
multiline_comment|/* B-Channel queues                 */
DECL|member|dqueue
r_struct
id|sk_buff_head
id|dqueue
suffix:semicolon
multiline_comment|/* D-Channel queue                  */
DECL|typedef|isdnloop_card
)brace
id|isdnloop_card
suffix:semicolon
multiline_comment|/*&n; * Main driver data&n; */
macro_line|#ifdef __KERNEL__
DECL|variable|cards
r_static
id|isdnloop_card
op_star
id|cards
op_assign
(paren
id|isdnloop_card
op_star
)paren
l_int|0
suffix:semicolon
DECL|variable|isdnloop_id
r_static
r_char
op_star
id|isdnloop_id
op_assign
l_string|&quot;&bslash;0&quot;
suffix:semicolon
macro_line|#ifdef MODULE
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Fritz Elfert&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|isdnloop_id
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|isdnloop_id
comma
l_string|&quot;ID-String of first card&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif                          /* __KERNEL__ */
multiline_comment|/* Utility-Macros */
DECL|macro|CID
mdefine_line|#define CID (card-&gt;interface.id)
DECL|macro|MIN
mdefine_line|#define MIN(a,b) ((a&lt;b)?a:b)
DECL|macro|MAX
mdefine_line|#define MAX(a,b) ((a&gt;b)?a:b)
macro_line|#endif                          /* defined(__KERNEL__) || defined(__DEBUGVAR__) */
macro_line|#endif                          /* isdnloop_h */
eof
