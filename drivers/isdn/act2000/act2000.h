multiline_comment|/* $Id: act2000.h,v 1.8.6.2 2001/02/16 16:43:23 kai Exp $&n; *&n; * ISDN lowlevel-module for the IBM ISDN-S0 Active 2000.&n; *&n; * Copyright 1998 by Fritz Elfert (fritz@isdn4linux.de)&n; * Thanks to Friedemann Baitinger and IBM Germany&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; *&n; */
macro_line|#ifndef act2000_h
DECL|macro|act2000_h
mdefine_line|#define act2000_h
macro_line|#ifdef __KERNEL__
multiline_comment|/* Kernel includes */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif
DECL|macro|ACT2000_IOCTL_SETPORT
mdefine_line|#define ACT2000_IOCTL_SETPORT    1
DECL|macro|ACT2000_IOCTL_GETPORT
mdefine_line|#define ACT2000_IOCTL_GETPORT    2
DECL|macro|ACT2000_IOCTL_SETIRQ
mdefine_line|#define ACT2000_IOCTL_SETIRQ     3
DECL|macro|ACT2000_IOCTL_GETIRQ
mdefine_line|#define ACT2000_IOCTL_GETIRQ     4
DECL|macro|ACT2000_IOCTL_SETBUS
mdefine_line|#define ACT2000_IOCTL_SETBUS     5
DECL|macro|ACT2000_IOCTL_GETBUS
mdefine_line|#define ACT2000_IOCTL_GETBUS     6
DECL|macro|ACT2000_IOCTL_SETPROTO
mdefine_line|#define ACT2000_IOCTL_SETPROTO   7
DECL|macro|ACT2000_IOCTL_GETPROTO
mdefine_line|#define ACT2000_IOCTL_GETPROTO   8
DECL|macro|ACT2000_IOCTL_SETMSN
mdefine_line|#define ACT2000_IOCTL_SETMSN     9
DECL|macro|ACT2000_IOCTL_GETMSN
mdefine_line|#define ACT2000_IOCTL_GETMSN    10
DECL|macro|ACT2000_IOCTL_LOADBOOT
mdefine_line|#define ACT2000_IOCTL_LOADBOOT  11
DECL|macro|ACT2000_IOCTL_ADDCARD
mdefine_line|#define ACT2000_IOCTL_ADDCARD   12
DECL|macro|ACT2000_IOCTL_TEST
mdefine_line|#define ACT2000_IOCTL_TEST      98
DECL|macro|ACT2000_IOCTL_DEBUGVAR
mdefine_line|#define ACT2000_IOCTL_DEBUGVAR  99
DECL|macro|ACT2000_BUS_ISA
mdefine_line|#define ACT2000_BUS_ISA          1
DECL|macro|ACT2000_BUS_MCA
mdefine_line|#define ACT2000_BUS_MCA          2
DECL|macro|ACT2000_BUS_PCMCIA
mdefine_line|#define ACT2000_BUS_PCMCIA       3
multiline_comment|/* Struct for adding new cards */
DECL|struct|act2000_cdef
r_typedef
r_struct
id|act2000_cdef
(brace
DECL|member|bus
r_int
id|bus
suffix:semicolon
DECL|member|port
r_int
id|port
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
DECL|typedef|act2000_cdef
)brace
id|act2000_cdef
suffix:semicolon
multiline_comment|/* Struct for downloading firmware */
DECL|struct|act2000_ddef
r_typedef
r_struct
id|act2000_ddef
(brace
DECL|member|length
r_int
id|length
suffix:semicolon
multiline_comment|/* Length of code */
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
multiline_comment|/* Ptr. to code   */
DECL|typedef|act2000_ddef
)brace
id|act2000_ddef
suffix:semicolon
DECL|struct|act2000_fwid
r_typedef
r_struct
id|act2000_fwid
(brace
DECL|member|isdn
r_char
id|isdn
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|revlen
r_char
id|revlen
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|revision
r_char
id|revision
(braket
l_int|504
)braket
suffix:semicolon
DECL|typedef|act2000_fwid
)brace
id|act2000_fwid
suffix:semicolon
macro_line|#if defined(__KERNEL__) || defined(__DEBUGVAR__)
macro_line|#ifdef __KERNEL__
multiline_comment|/* Kernel includes */
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
macro_line|#include &lt;linux/isdnif.h&gt;
macro_line|#endif                           /* __KERNEL__ */
DECL|macro|ACT2000_PORTLEN
mdefine_line|#define ACT2000_PORTLEN        8
DECL|macro|ACT2000_FLAGS_RUNNING
mdefine_line|#define ACT2000_FLAGS_RUNNING  1 /* Cards driver activated */
DECL|macro|ACT2000_FLAGS_PVALID
mdefine_line|#define ACT2000_FLAGS_PVALID   2 /* Cards port is valid    */
DECL|macro|ACT2000_FLAGS_IVALID
mdefine_line|#define ACT2000_FLAGS_IVALID   4 /* Cards irq is valid     */
DECL|macro|ACT2000_FLAGS_LOADED
mdefine_line|#define ACT2000_FLAGS_LOADED   8 /* Firmware loaded        */
DECL|macro|ACT2000_BCH
mdefine_line|#define ACT2000_BCH            2 /* # of channels per card */
multiline_comment|/* D-Channel states */
DECL|macro|ACT2000_STATE_NULL
mdefine_line|#define ACT2000_STATE_NULL     0
DECL|macro|ACT2000_STATE_ICALL
mdefine_line|#define ACT2000_STATE_ICALL    1
DECL|macro|ACT2000_STATE_OCALL
mdefine_line|#define ACT2000_STATE_OCALL    2
DECL|macro|ACT2000_STATE_IWAIT
mdefine_line|#define ACT2000_STATE_IWAIT    3
DECL|macro|ACT2000_STATE_OWAIT
mdefine_line|#define ACT2000_STATE_OWAIT    4
DECL|macro|ACT2000_STATE_IBWAIT
mdefine_line|#define ACT2000_STATE_IBWAIT   5
DECL|macro|ACT2000_STATE_OBWAIT
mdefine_line|#define ACT2000_STATE_OBWAIT   6
DECL|macro|ACT2000_STATE_BWAIT
mdefine_line|#define ACT2000_STATE_BWAIT    7
DECL|macro|ACT2000_STATE_BHWAIT
mdefine_line|#define ACT2000_STATE_BHWAIT   8
DECL|macro|ACT2000_STATE_BHWAIT2
mdefine_line|#define ACT2000_STATE_BHWAIT2  9
DECL|macro|ACT2000_STATE_DHWAIT
mdefine_line|#define ACT2000_STATE_DHWAIT  10
DECL|macro|ACT2000_STATE_DHWAIT2
mdefine_line|#define ACT2000_STATE_DHWAIT2 11
DECL|macro|ACT2000_STATE_BSETUP
mdefine_line|#define ACT2000_STATE_BSETUP  12
DECL|macro|ACT2000_STATE_ACTIVE
mdefine_line|#define ACT2000_STATE_ACTIVE  13
DECL|macro|ACT2000_MAX_QUEUED
mdefine_line|#define ACT2000_MAX_QUEUED  8000 /* 2 * maxbuff */
DECL|macro|ACT2000_LOCK_TX
mdefine_line|#define ACT2000_LOCK_TX 0
DECL|macro|ACT2000_LOCK_RX
mdefine_line|#define ACT2000_LOCK_RX 1
DECL|struct|act2000_chan
r_typedef
r_struct
id|act2000_chan
(brace
DECL|member|callref
r_int
r_int
id|callref
suffix:semicolon
multiline_comment|/* Call Reference              */
DECL|member|fsm_state
r_int
r_int
id|fsm_state
suffix:semicolon
multiline_comment|/* Current D-Channel state     */
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
DECL|member|plci
r_int
r_int
id|plci
suffix:semicolon
DECL|member|ncci
r_int
r_int
id|ncci
suffix:semicolon
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
DECL|typedef|act2000_chan
)brace
id|act2000_chan
suffix:semicolon
DECL|struct|msn_entry
r_typedef
r_struct
id|msn_entry
(brace
DECL|member|eaz
r_char
id|eaz
suffix:semicolon
DECL|member|msn
r_char
id|msn
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|next
r_struct
id|msn_entry
op_star
id|next
suffix:semicolon
DECL|typedef|msn_entry
)brace
id|msn_entry
suffix:semicolon
DECL|struct|irq_data_isa
r_typedef
r_struct
id|irq_data_isa
(brace
DECL|member|rcvptr
id|__u8
op_star
id|rcvptr
suffix:semicolon
DECL|member|rcvidx
id|__u16
id|rcvidx
suffix:semicolon
DECL|member|rcvlen
id|__u16
id|rcvlen
suffix:semicolon
DECL|member|rcvskb
r_struct
id|sk_buff
op_star
id|rcvskb
suffix:semicolon
DECL|member|rcvignore
id|__u8
id|rcvignore
suffix:semicolon
DECL|member|rcvhdr
id|__u8
id|rcvhdr
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|irq_data_isa
)brace
id|irq_data_isa
suffix:semicolon
DECL|union|irq_data
r_typedef
r_union
id|irq_data
(brace
DECL|member|isa
id|irq_data_isa
id|isa
suffix:semicolon
DECL|typedef|irq_data
)brace
id|irq_data
suffix:semicolon
multiline_comment|/*&n; * Per card driver data&n; */
DECL|struct|act2000_card
r_typedef
r_struct
id|act2000_card
(brace
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
multiline_comment|/* Base-port-address                */
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* Interrupt                        */
DECL|member|ptype
id|u_char
id|ptype
suffix:semicolon
multiline_comment|/* Protocol type (1TR6 or Euro)     */
DECL|member|bus
id|u_char
id|bus
suffix:semicolon
multiline_comment|/* Cardtype (ISA, MCA, PCMCIA)      */
DECL|member|next
r_struct
id|act2000_card
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
DECL|member|ilock
r_int
r_int
id|ilock
suffix:semicolon
multiline_comment|/* Semaphores for IRQ-Routines      */
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
DECL|member|ackq
r_struct
id|sk_buff_head
id|ackq
suffix:semicolon
multiline_comment|/* Data-Ack-Message queue           */
DECL|member|ack_msg
id|u_char
op_star
id|ack_msg
suffix:semicolon
multiline_comment|/* Ptr to User Data in User skb     */
DECL|member|need_b3ack
id|__u16
id|need_b3ack
suffix:semicolon
multiline_comment|/* Flag: Need ACK for current skb   */
DECL|member|sbuf
r_struct
id|sk_buff
op_star
id|sbuf
suffix:semicolon
multiline_comment|/* skb which is currently sent      */
DECL|member|ptimer
r_struct
id|timer_list
id|ptimer
suffix:semicolon
multiline_comment|/* Poll timer                       */
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
DECL|member|poll_tq
r_struct
id|tq_struct
id|poll_tq
suffix:semicolon
multiline_comment|/* Task struct for polled rcv bh    */
DECL|member|msn_list
id|msn_entry
op_star
id|msn_list
suffix:semicolon
DECL|member|msgnum
r_int
r_int
id|msgnum
suffix:semicolon
multiline_comment|/* Message number fur sending       */
DECL|member|bch
id|act2000_chan
id|bch
(braket
id|ACT2000_BCH
)braket
suffix:semicolon
multiline_comment|/* B-Channel status/control         */
DECL|member|status_buf
r_char
id|status_buf
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* Buffer for status messages       */
DECL|member|status_buf_read
r_char
op_star
id|status_buf_read
suffix:semicolon
DECL|member|status_buf_write
r_char
op_star
id|status_buf_write
suffix:semicolon
DECL|member|status_buf_end
r_char
op_star
id|status_buf_end
suffix:semicolon
DECL|member|idat
id|irq_data
id|idat
suffix:semicolon
multiline_comment|/* Data used for IRQ handler        */
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
multiline_comment|/* Name used for request_region     */
DECL|typedef|act2000_card
)brace
id|act2000_card
suffix:semicolon
DECL|function|act2000_schedule_tx
r_extern
id|__inline__
r_void
id|act2000_schedule_tx
c_func
(paren
id|act2000_card
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
DECL|function|act2000_schedule_rx
r_extern
id|__inline__
r_void
id|act2000_schedule_rx
c_func
(paren
id|act2000_card
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
DECL|function|act2000_schedule_poll
r_extern
id|__inline__
r_void
id|act2000_schedule_poll
c_func
(paren
id|act2000_card
op_star
id|card
)paren
(brace
id|queue_task
c_func
(paren
op_amp
id|card-&gt;poll_tq
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
r_char
op_star
id|act2000_find_eaz
c_func
(paren
id|act2000_card
op_star
comma
r_char
)paren
suffix:semicolon
macro_line|#endif                          /* defined(__KERNEL__) || defined(__DEBUGVAR__) */
macro_line|#endif                          /* act2000_h */
eof
