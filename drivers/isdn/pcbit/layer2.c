multiline_comment|/*&n; * Copyright (C) 1996 Universidade de Lisboa&n; *&n; * Written by Pedro Roque Marques (roque@di.fc.ul.pt)&n; *&n; * This software may be used and distributed according to the terms of&n; * the GNU General Public License, incorporated herein by reference.&n; */
multiline_comment|/*&n; * 19991203 - Fernando Carvalho - takion@superbofh.org&n; * Hacked to compile with egcs and run with current version of isdn modules&n;*/
multiline_comment|/*&n; *        PCBIT-D low-layer interface&n; */
multiline_comment|/*&n; *        Based on documentation provided by Inesc:&n; *        - &quot;Interface com bus do PC para o PCBIT e PCBIT-D&quot;, Inesc, Jan 93&n; */
multiline_comment|/*&n; *        TODO: better handling of errors&n; *              re-write/remove debug printks&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#ifdef MODULE
DECL|macro|INCLUDE_INLINE_FUNCS
mdefine_line|#define INCLUDE_INLINE_FUNCS
macro_line|#endif
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/isdnif.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;pcbit.h&quot;
macro_line|#include &quot;layer2.h&quot;
macro_line|#include &quot;edss1.h&quot;
DECL|macro|DEBUG_FRAG
macro_line|#undef DEBUG_FRAG
multiline_comment|/*&n; *  task queue struct&n; */
multiline_comment|/*&n; *  Layer 3 packet demultiplexer&n; *  drv.c&n; */
r_extern
r_void
id|pcbit_l3_receive
c_func
(paren
r_struct
id|pcbit_dev
op_star
id|dev
comma
id|ulong
id|msg
comma
r_struct
id|sk_buff
op_star
id|skb
comma
id|ushort
id|hdr_len
comma
id|ushort
id|refnum
)paren
suffix:semicolon
multiline_comment|/*&n; *  Prototypes&n; */
r_void
id|pcbit_deliver
c_func
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
r_static
r_void
id|pcbit_transmit
c_func
(paren
r_struct
id|pcbit_dev
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|pcbit_recv_ack
c_func
(paren
r_struct
id|pcbit_dev
op_star
id|dev
comma
r_int
r_char
id|ack
)paren
suffix:semicolon
r_static
r_void
id|pcbit_l2_error
c_func
(paren
r_struct
id|pcbit_dev
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|pcbit_l2_active_conf
c_func
(paren
r_struct
id|pcbit_dev
op_star
id|dev
comma
id|u_char
id|info
)paren
suffix:semicolon
r_static
r_void
id|pcbit_l2_err_recover
c_func
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
r_static
r_void
id|pcbit_firmware_bug
c_func
(paren
r_struct
id|pcbit_dev
op_star
id|dev
)paren
suffix:semicolon
r_static
id|__inline__
r_void
DECL|function|pcbit_sched_delivery
id|pcbit_sched_delivery
c_func
(paren
r_struct
id|pcbit_dev
op_star
id|dev
)paren
(brace
id|queue_task
c_func
(paren
op_amp
id|dev-&gt;qdelivery
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
multiline_comment|/*&n; *  Called from layer3&n; */
r_int
DECL|function|pcbit_l2_write
id|pcbit_l2_write
c_func
(paren
r_struct
id|pcbit_dev
op_star
id|dev
comma
id|ulong
id|msg
comma
id|ushort
id|refnum
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_int
id|hdr_len
)paren
(brace
r_struct
id|frame_buf
op_star
id|frame
comma
op_star
id|ptr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;l2_state
op_ne
id|L2_RUNNING
op_logical_and
id|dev-&gt;l2_state
op_ne
id|L2_LOADING
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|frame
op_assign
(paren
r_struct
id|frame_buf
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|frame_buf
)paren
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;pcbit_2_write: kmalloc failed&bslash;n&quot;
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|frame-&gt;msg
op_assign
id|msg
suffix:semicolon
id|frame-&gt;refnum
op_assign
id|refnum
suffix:semicolon
id|frame-&gt;copied
op_assign
l_int|0
suffix:semicolon
id|frame-&gt;hdr_len
op_assign
id|hdr_len
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
id|frame-&gt;dt_len
op_assign
id|skb-&gt;len
op_minus
id|hdr_len
suffix:semicolon
r_else
id|frame-&gt;dt_len
op_assign
l_int|0
suffix:semicolon
id|frame-&gt;skb
op_assign
id|skb
suffix:semicolon
id|frame-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;write_queue
op_eq
l_int|NULL
)paren
(brace
id|dev-&gt;write_queue
op_assign
id|frame
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|pcbit_transmit
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|ptr
op_assign
id|dev-&gt;write_queue
suffix:semicolon
id|ptr-&gt;next
suffix:semicolon
id|ptr
op_assign
id|ptr-&gt;next
)paren
suffix:semicolon
id|ptr-&gt;next
op_assign
id|frame
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|pcbit_tx_update
id|pcbit_tx_update
c_func
(paren
r_struct
id|pcbit_dev
op_star
id|dev
comma
id|ushort
id|len
)paren
(brace
id|u_char
id|info
suffix:semicolon
id|dev-&gt;send_seq
op_assign
(paren
id|dev-&gt;send_seq
op_plus
l_int|1
)paren
op_mod
l_int|8
suffix:semicolon
id|dev-&gt;fsize
(braket
id|dev-&gt;send_seq
)braket
op_assign
id|len
suffix:semicolon
id|info
op_assign
l_int|0
suffix:semicolon
id|info
op_or_assign
id|dev-&gt;rcv_seq
op_lshift
l_int|3
suffix:semicolon
id|info
op_or_assign
id|dev-&gt;send_seq
suffix:semicolon
id|writeb
c_func
(paren
id|info
comma
id|dev-&gt;sh_mem
op_plus
id|BANK4
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * called by interrupt service routine or by write_2&n; */
r_static
r_void
DECL|function|pcbit_transmit
id|pcbit_transmit
c_func
(paren
r_struct
id|pcbit_dev
op_star
id|dev
)paren
(brace
r_struct
id|frame_buf
op_star
id|frame
op_assign
l_int|NULL
suffix:semicolon
r_int
r_char
id|unacked
suffix:semicolon
r_int
id|flen
suffix:semicolon
multiline_comment|/* fragment frame length including all headers */
r_int
id|free
suffix:semicolon
r_int
id|count
comma
id|cp_len
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|tt
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;l2_state
op_ne
id|L2_RUNNING
op_logical_and
id|dev-&gt;l2_state
op_ne
id|L2_LOADING
)paren
r_return
suffix:semicolon
id|unacked
op_assign
(paren
id|dev-&gt;send_seq
op_plus
(paren
l_int|8
op_minus
id|dev-&gt;unack_seq
)paren
)paren
op_amp
l_int|0x07
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;free
OG
l_int|16
op_logical_and
id|dev-&gt;write_queue
op_logical_and
id|unacked
OL
l_int|7
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;w_busy
)paren
id|dev-&gt;w_busy
op_assign
l_int|1
suffix:semicolon
r_else
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|frame
op_assign
id|dev-&gt;write_queue
suffix:semicolon
id|free
op_assign
id|dev-&gt;free
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|frame-&gt;copied
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Type 0 frame */
id|ulong
id|msg
suffix:semicolon
r_if
c_cond
(paren
id|frame-&gt;skb
)paren
id|flen
op_assign
id|FRAME_HDR_LEN
op_plus
id|PREHDR_LEN
op_plus
id|frame-&gt;skb-&gt;len
suffix:semicolon
r_else
id|flen
op_assign
id|FRAME_HDR_LEN
op_plus
id|PREHDR_LEN
suffix:semicolon
r_if
c_cond
(paren
id|flen
OG
id|free
)paren
id|flen
op_assign
id|free
suffix:semicolon
id|msg
op_assign
id|frame-&gt;msg
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *  Board level 2 header&n;&t;&t;&t; */
id|pcbit_writew
c_func
(paren
id|dev
comma
id|flen
op_minus
id|FRAME_HDR_LEN
)paren
suffix:semicolon
id|pcbit_writeb
c_func
(paren
id|dev
comma
id|GET_MSG_CPU
c_func
(paren
id|msg
)paren
)paren
suffix:semicolon
id|pcbit_writeb
c_func
(paren
id|dev
comma
id|GET_MSG_PROC
c_func
(paren
id|msg
)paren
)paren
suffix:semicolon
multiline_comment|/* TH */
id|pcbit_writew
c_func
(paren
id|dev
comma
id|frame-&gt;hdr_len
op_plus
id|PREHDR_LEN
)paren
suffix:semicolon
multiline_comment|/* TD */
id|pcbit_writew
c_func
(paren
id|dev
comma
id|frame-&gt;dt_len
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *  Board level 3 fixed-header&n;&t;&t;&t; */
multiline_comment|/* LEN = TH */
id|pcbit_writew
c_func
(paren
id|dev
comma
id|frame-&gt;hdr_len
op_plus
id|PREHDR_LEN
)paren
suffix:semicolon
multiline_comment|/* XX */
id|pcbit_writew
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* C + S */
id|pcbit_writeb
c_func
(paren
id|dev
comma
id|GET_MSG_CMD
c_func
(paren
id|msg
)paren
)paren
suffix:semicolon
id|pcbit_writeb
c_func
(paren
id|dev
comma
id|GET_MSG_SCMD
c_func
(paren
id|msg
)paren
)paren
suffix:semicolon
multiline_comment|/* NUM */
id|pcbit_writew
c_func
(paren
id|dev
comma
id|frame-&gt;refnum
)paren
suffix:semicolon
id|count
op_assign
id|FRAME_HDR_LEN
op_plus
id|PREHDR_LEN
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Type 1 frame */
id|flen
op_assign
l_int|2
op_plus
(paren
id|frame-&gt;skb-&gt;len
op_minus
id|frame-&gt;copied
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flen
OG
id|free
)paren
id|flen
op_assign
id|free
suffix:semicolon
multiline_comment|/* TT */
id|tt
op_assign
(paren
(paren
id|ushort
)paren
(paren
id|flen
op_minus
l_int|2
)paren
)paren
op_or
l_int|0x8000U
suffix:semicolon
multiline_comment|/* Type 1 */
id|pcbit_writew
c_func
(paren
id|dev
comma
id|tt
)paren
suffix:semicolon
id|count
op_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|frame-&gt;skb
)paren
(brace
id|cp_len
op_assign
id|frame-&gt;skb-&gt;len
op_minus
id|frame-&gt;copied
suffix:semicolon
r_if
c_cond
(paren
id|cp_len
OG
id|flen
op_minus
id|count
)paren
id|cp_len
op_assign
id|flen
op_minus
id|count
suffix:semicolon
id|memcpy_topcbit
c_func
(paren
id|dev
comma
id|frame-&gt;skb-&gt;data
op_plus
id|frame-&gt;copied
comma
id|cp_len
)paren
suffix:semicolon
id|frame-&gt;copied
op_add_assign
id|cp_len
suffix:semicolon
)brace
multiline_comment|/* bookkeeping */
id|dev-&gt;free
op_sub_assign
id|flen
suffix:semicolon
id|pcbit_tx_update
c_func
(paren
id|dev
comma
id|flen
)paren
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|frame-&gt;skb
op_eq
l_int|NULL
op_logical_or
id|frame-&gt;copied
op_eq
id|frame-&gt;skb-&gt;len
)paren
(brace
id|dev-&gt;write_queue
op_assign
id|frame-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|frame-&gt;skb
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* free frame */
id|dev_kfree_skb
c_func
(paren
id|frame-&gt;skb
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|frame
)paren
suffix:semicolon
)brace
id|dev-&gt;w_busy
op_assign
l_int|0
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;unacked %d free %d write_queue %s&bslash;n&quot;
comma
id|unacked
comma
id|dev-&gt;free
comma
id|dev-&gt;write_queue
ques
c_cond
l_string|&quot;not empty&quot;
suffix:colon
l_string|&quot;empty&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
multiline_comment|/*&n; *  deliver a queued frame to the upper layer&n; */
r_void
DECL|function|pcbit_deliver
id|pcbit_deliver
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|frame_buf
op_star
id|frame
suffix:semicolon
r_int
r_int
id|flags
comma
id|msg
suffix:semicolon
r_struct
id|pcbit_dev
op_star
id|dev
op_assign
(paren
r_struct
id|pcbit_dev
op_star
)paren
id|data
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|frame
op_assign
id|dev-&gt;read_queue
)paren
)paren
(brace
id|dev-&gt;read_queue
op_assign
id|frame-&gt;next
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|SET_MSG_CPU
c_func
(paren
id|msg
comma
l_int|0
)paren
suffix:semicolon
id|SET_MSG_PROC
c_func
(paren
id|msg
comma
l_int|0
)paren
suffix:semicolon
id|SET_MSG_CMD
c_func
(paren
id|msg
comma
id|frame-&gt;skb-&gt;data
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|SET_MSG_SCMD
c_func
(paren
id|msg
comma
id|frame-&gt;skb-&gt;data
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|frame-&gt;refnum
op_assign
op_star
(paren
(paren
id|ushort
op_star
)paren
id|frame-&gt;skb-&gt;data
op_plus
l_int|4
)paren
suffix:semicolon
id|frame-&gt;msg
op_assign
op_star
(paren
(paren
id|ulong
op_star
)paren
op_amp
id|msg
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|frame-&gt;skb
comma
l_int|6
)paren
suffix:semicolon
id|pcbit_l3_receive
c_func
(paren
id|dev
comma
id|frame-&gt;msg
comma
id|frame-&gt;skb
comma
id|frame-&gt;hdr_len
comma
id|frame-&gt;refnum
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|frame
)paren
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Reads BANK 2 &amp; Reassembles&n; */
r_static
r_void
DECL|function|pcbit_receive
id|pcbit_receive
c_func
(paren
r_struct
id|pcbit_dev
op_star
id|dev
)paren
(brace
r_int
r_int
id|tt
suffix:semicolon
id|u_char
id|cpu
comma
id|proc
suffix:semicolon
r_struct
id|frame_buf
op_star
id|frame
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u_char
id|type1
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;l2_state
op_ne
id|L2_RUNNING
op_logical_and
id|dev-&gt;l2_state
op_ne
id|L2_LOADING
)paren
r_return
suffix:semicolon
id|tt
op_assign
id|pcbit_readw
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tt
op_amp
l_int|0x7fffU
)paren
OG
l_int|511
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;pcbit: invalid frame length -&gt; TT=%04x&bslash;n&quot;
comma
id|tt
)paren
suffix:semicolon
id|pcbit_l2_error
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|tt
op_amp
l_int|0x8000U
)paren
)paren
(brace
multiline_comment|/* Type 0 */
id|type1
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;read_frame
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;pcbit_receive: Type 0 frame and read_frame != NULL&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* discard previous queued frame */
r_if
c_cond
(paren
id|dev-&gt;read_frame-&gt;skb
)paren
id|kfree_skb
c_func
(paren
id|dev-&gt;read_frame-&gt;skb
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev-&gt;read_frame
)paren
suffix:semicolon
id|dev-&gt;read_frame
op_assign
l_int|NULL
suffix:semicolon
)brace
id|frame
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|frame_buf
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|frame
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;kmalloc failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memset
c_func
(paren
id|frame
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|frame_buf
)paren
)paren
suffix:semicolon
id|cpu
op_assign
id|pcbit_readb
c_func
(paren
id|dev
)paren
suffix:semicolon
id|proc
op_assign
id|pcbit_readb
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu
op_ne
l_int|0x06
op_logical_and
id|cpu
op_ne
l_int|0x02
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;pcbit: invalid cpu value&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|frame
)paren
suffix:semicolon
id|pcbit_l2_error
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * we discard cpu &amp; proc on receiving&n;&t;&t; * but we read it to update the pointer&n;&t;&t; */
id|frame-&gt;hdr_len
op_assign
id|pcbit_readw
c_func
(paren
id|dev
)paren
suffix:semicolon
id|frame-&gt;dt_len
op_assign
id|pcbit_readw
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;   * 0 sized packet&n;&t;&t;   * I don&squot;t know if they are an error or not...&n;&t;&t;   * But they are very frequent&n;&t;&t;   * Not documented&n;&t;&t; */
r_if
c_cond
(paren
id|frame-&gt;hdr_len
op_eq
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|frame
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;0 sized frame&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|pcbit_firmware_bug
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* sanity check the length values */
r_if
c_cond
(paren
id|frame-&gt;hdr_len
OG
l_int|1024
op_logical_or
id|frame-&gt;dt_len
OG
l_int|2048
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;length problem: &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;TH=%04x TD=%04x&bslash;n&quot;
comma
id|frame-&gt;hdr_len
comma
id|frame-&gt;dt_len
)paren
suffix:semicolon
macro_line|#endif
id|pcbit_l2_error
c_func
(paren
id|dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|frame
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* minimum frame read */
id|frame-&gt;skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|frame-&gt;hdr_len
op_plus
id|frame-&gt;dt_len
op_plus
(paren
(paren
id|frame-&gt;hdr_len
op_plus
l_int|15
)paren
op_amp
op_complement
l_int|15
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|frame-&gt;skb
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;pcbit_receive: out of memory&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|frame
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* 16 byte alignment for IP */
r_if
c_cond
(paren
id|frame-&gt;dt_len
)paren
id|skb_reserve
c_func
(paren
id|frame-&gt;skb
comma
(paren
id|frame-&gt;hdr_len
op_plus
l_int|15
)paren
op_amp
op_complement
l_int|15
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Type 1 */
id|type1
op_assign
l_int|1
suffix:semicolon
id|tt
op_and_assign
l_int|0x7fffU
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|frame
op_assign
id|dev-&gt;read_frame
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Type 1 frame and no frame queued&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* usually after an error: toss frame */
id|dev-&gt;readptr
op_add_assign
id|tt
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;readptr
OG
id|dev-&gt;sh_mem
op_plus
id|BANK2
op_plus
id|BANKLEN
)paren
id|dev-&gt;readptr
op_sub_assign
id|BANKLEN
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|memcpy_frompcbit
c_func
(paren
id|dev
comma
id|skb_put
c_func
(paren
id|frame-&gt;skb
comma
id|tt
)paren
comma
id|tt
)paren
suffix:semicolon
id|frame-&gt;copied
op_add_assign
id|tt
suffix:semicolon
r_if
c_cond
(paren
id|frame-&gt;copied
op_eq
id|frame-&gt;hdr_len
op_plus
id|frame-&gt;dt_len
)paren
(brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type1
)paren
(brace
id|dev-&gt;read_frame
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;read_queue
)paren
(brace
r_struct
id|frame_buf
op_star
id|ptr
suffix:semicolon
r_for
c_loop
(paren
id|ptr
op_assign
id|dev-&gt;read_queue
suffix:semicolon
id|ptr-&gt;next
suffix:semicolon
id|ptr
op_assign
id|ptr-&gt;next
)paren
suffix:semicolon
id|ptr-&gt;next
op_assign
id|frame
suffix:semicolon
)brace
r_else
id|dev-&gt;read_queue
op_assign
id|frame
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|dev-&gt;read_frame
op_assign
id|frame
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  The board sends 0 sized frames&n; *  They are TDATA_CONFs that get messed up somehow&n; *  gotta send a fake acknowledgment to the upper layer somehow&n; */
r_static
id|__inline__
r_void
DECL|function|pcbit_fake_conf
id|pcbit_fake_conf
c_func
(paren
r_struct
id|pcbit_dev
op_star
id|dev
comma
r_struct
id|pcbit_chan
op_star
id|chan
)paren
(brace
id|isdn_ctrl
id|ictl
suffix:semicolon
r_if
c_cond
(paren
id|chan-&gt;queued
)paren
(brace
id|chan-&gt;queued
op_decrement
suffix:semicolon
id|ictl.driver
op_assign
id|dev-&gt;id
suffix:semicolon
id|ictl.command
op_assign
id|ISDN_STAT_BSENT
suffix:semicolon
id|ictl.arg
op_assign
id|chan-&gt;id
suffix:semicolon
id|dev-&gt;dev_if
op_member_access_from_pointer
id|statcallb
c_func
(paren
op_amp
id|ictl
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|pcbit_firmware_bug
id|pcbit_firmware_bug
c_func
(paren
r_struct
id|pcbit_dev
op_star
id|dev
)paren
(brace
r_struct
id|pcbit_chan
op_star
id|chan
suffix:semicolon
id|chan
op_assign
id|dev-&gt;b1
suffix:semicolon
r_if
c_cond
(paren
id|chan-&gt;fsm_state
op_eq
id|ST_ACTIVE
)paren
(brace
id|pcbit_fake_conf
c_func
(paren
id|dev
comma
id|chan
)paren
suffix:semicolon
)brace
id|chan
op_assign
id|dev-&gt;b2
suffix:semicolon
r_if
c_cond
(paren
id|chan-&gt;fsm_state
op_eq
id|ST_ACTIVE
)paren
(brace
id|pcbit_fake_conf
c_func
(paren
id|dev
comma
id|chan
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|pcbit_irq_handler
id|pcbit_irq_handler
c_func
(paren
r_int
id|interrupt
comma
r_void
op_star
id|devptr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|pcbit_dev
op_star
id|dev
suffix:semicolon
id|u_char
id|info
comma
id|ack_seq
comma
id|read_seq
suffix:semicolon
id|dev
op_assign
(paren
r_struct
id|pcbit_dev
op_star
)paren
id|devptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;pcbit_irq_handler: wrong device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;interrupt
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;pcbit: reentering interrupt hander&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dev-&gt;interrupt
op_assign
l_int|1
suffix:semicolon
id|info
op_assign
id|readb
c_func
(paren
id|dev-&gt;sh_mem
op_plus
id|BANK3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;l2_state
op_eq
id|L2_STARTING
op_logical_or
id|dev-&gt;l2_state
op_eq
id|L2_ERROR
)paren
(brace
id|pcbit_l2_active_conf
c_func
(paren
id|dev
comma
id|info
)paren
suffix:semicolon
id|dev-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info
op_amp
l_int|0x40U
)paren
(brace
multiline_comment|/* E bit set */
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;pcbit_irq_handler: E bit on&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|pcbit_l2_error
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;l2_state
op_ne
id|L2_RUNNING
op_logical_and
id|dev-&gt;l2_state
op_ne
id|L2_LOADING
)paren
(brace
id|dev-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ack_seq
op_assign
(paren
id|info
op_rshift
l_int|3
)paren
op_amp
l_int|0x07U
suffix:semicolon
id|read_seq
op_assign
(paren
id|info
op_amp
l_int|0x07U
)paren
suffix:semicolon
id|dev-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|read_seq
op_ne
id|dev-&gt;rcv_seq
)paren
(brace
r_while
c_loop
(paren
id|read_seq
op_ne
id|dev-&gt;rcv_seq
)paren
(brace
id|pcbit_receive
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;rcv_seq
op_assign
(paren
id|dev-&gt;rcv_seq
op_plus
l_int|1
)paren
op_mod
l_int|8
suffix:semicolon
)brace
id|pcbit_sched_delivery
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ack_seq
op_ne
id|dev-&gt;unack_seq
)paren
(brace
id|pcbit_recv_ack
c_func
(paren
id|dev
comma
id|ack_seq
)paren
suffix:semicolon
)brace
id|info
op_assign
id|dev-&gt;rcv_seq
op_lshift
l_int|3
suffix:semicolon
id|info
op_or_assign
id|dev-&gt;send_seq
suffix:semicolon
id|writeb
c_func
(paren
id|info
comma
id|dev-&gt;sh_mem
op_plus
id|BANK4
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|pcbit_l2_active_conf
id|pcbit_l2_active_conf
c_func
(paren
r_struct
id|pcbit_dev
op_star
id|dev
comma
id|u_char
id|info
)paren
(brace
id|u_char
id|state
suffix:semicolon
id|state
op_assign
id|dev-&gt;l2_state
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;layer2_active_confirm&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|info
op_amp
l_int|0x80U
)paren
(brace
id|dev-&gt;rcv_seq
op_assign
id|info
op_amp
l_int|0x07U
suffix:semicolon
id|dev-&gt;l2_state
op_assign
id|L2_RUNNING
suffix:semicolon
)brace
r_else
id|dev-&gt;l2_state
op_assign
id|L2_DOWN
suffix:semicolon
r_if
c_cond
(paren
id|state
op_eq
id|L2_STARTING
)paren
id|wake_up_interruptible
c_func
(paren
op_amp
id|dev-&gt;set_running_wq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
op_eq
id|L2_ERROR
op_logical_and
id|dev-&gt;l2_state
op_eq
id|L2_RUNNING
)paren
(brace
id|pcbit_transmit
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|pcbit_l2_err_recover
id|pcbit_l2_err_recover
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|pcbit_dev
op_star
id|dev
suffix:semicolon
r_struct
id|frame_buf
op_star
id|frame
suffix:semicolon
id|dev
op_assign
(paren
r_struct
id|pcbit_dev
op_star
)paren
id|data
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|dev-&gt;error_recover_timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;w_busy
op_logical_or
id|dev-&gt;r_busy
)paren
(brace
id|init_timer
c_func
(paren
op_amp
id|dev-&gt;error_recover_timer
)paren
suffix:semicolon
id|dev-&gt;error_recover_timer.expires
op_assign
id|jiffies
op_plus
id|ERRTIME
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|dev-&gt;error_recover_timer
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dev-&gt;w_busy
op_assign
id|dev-&gt;r_busy
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;read_frame
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;read_frame-&gt;skb
)paren
id|kfree_skb
c_func
(paren
id|dev-&gt;read_frame-&gt;skb
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev-&gt;read_frame
)paren
suffix:semicolon
id|dev-&gt;read_frame
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;write_queue
)paren
(brace
id|frame
op_assign
id|dev-&gt;write_queue
suffix:semicolon
macro_line|#ifdef FREE_ON_ERROR
id|dev-&gt;write_queue
op_assign
id|dev-&gt;write_queue-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|frame-&gt;skb
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|frame-&gt;skb
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|frame
)paren
suffix:semicolon
macro_line|#else
id|frame-&gt;copied
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
)brace
id|dev-&gt;rcv_seq
op_assign
id|dev-&gt;send_seq
op_assign
id|dev-&gt;unack_seq
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;free
op_assign
l_int|511
suffix:semicolon
id|dev-&gt;l2_state
op_assign
id|L2_ERROR
suffix:semicolon
multiline_comment|/* this is an hack... */
id|pcbit_firmware_bug
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;writeptr
op_assign
id|dev-&gt;sh_mem
suffix:semicolon
id|dev-&gt;readptr
op_assign
id|dev-&gt;sh_mem
op_plus
id|BANK2
suffix:semicolon
id|writeb
c_func
(paren
(paren
l_int|0x80U
op_or
(paren
(paren
id|dev-&gt;rcv_seq
op_amp
l_int|0x07
)paren
op_lshift
l_int|3
)paren
op_or
(paren
id|dev-&gt;send_seq
op_amp
l_int|0x07
)paren
)paren
comma
id|dev-&gt;sh_mem
op_plus
id|BANK4
)paren
suffix:semicolon
id|dev-&gt;w_busy
op_assign
id|dev-&gt;r_busy
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|pcbit_l2_error
id|pcbit_l2_error
c_func
(paren
r_struct
id|pcbit_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;l2_state
op_eq
id|L2_RUNNING
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;pcbit: layer 2 error&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|log_state
c_func
(paren
id|dev
)paren
suffix:semicolon
macro_line|#endif
id|dev-&gt;l2_state
op_assign
id|L2_DOWN
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|dev-&gt;error_recover_timer
)paren
suffix:semicolon
id|dev-&gt;error_recover_timer.function
op_assign
op_amp
id|pcbit_l2_err_recover
suffix:semicolon
id|dev-&gt;error_recover_timer.data
op_assign
(paren
id|ulong
)paren
id|dev
suffix:semicolon
id|dev-&gt;error_recover_timer.expires
op_assign
id|jiffies
op_plus
id|ERRTIME
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|dev-&gt;error_recover_timer
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Description:&n; * if board acks frames&n; *   update dev-&gt;free&n; *   call pcbit_transmit to write possible queued frames&n; */
r_static
r_void
DECL|function|pcbit_recv_ack
id|pcbit_recv_ack
c_func
(paren
r_struct
id|pcbit_dev
op_star
id|dev
comma
r_int
r_char
id|ack
)paren
(brace
r_int
id|i
comma
id|count
suffix:semicolon
r_int
id|unacked
suffix:semicolon
id|unacked
op_assign
(paren
id|dev-&gt;send_seq
op_plus
(paren
l_int|8
op_minus
id|dev-&gt;unack_seq
)paren
)paren
op_amp
l_int|0x07
suffix:semicolon
multiline_comment|/* dev-&gt;unack_seq &lt; ack &lt;= dev-&gt;send_seq; */
r_if
c_cond
(paren
id|unacked
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;send_seq
OG
id|dev-&gt;unack_seq
)paren
(brace
r_if
c_cond
(paren
id|ack
op_le
id|dev-&gt;unack_seq
op_logical_or
id|ack
OG
id|dev-&gt;send_seq
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;layer 2 ack unacceptable - dev %d&quot;
comma
id|dev-&gt;id
)paren
suffix:semicolon
id|pcbit_l2_error
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ack
OG
id|dev-&gt;send_seq
op_logical_and
id|ack
op_le
id|dev-&gt;unack_seq
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;layer 2 ack unacceptable - dev %d&quot;
comma
id|dev-&gt;id
)paren
suffix:semicolon
id|pcbit_l2_error
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* ack is acceptable */
id|i
op_assign
id|dev-&gt;unack_seq
suffix:semicolon
r_do
(brace
id|dev-&gt;unack_seq
op_assign
id|i
op_assign
(paren
id|i
op_plus
l_int|1
)paren
op_mod
l_int|8
suffix:semicolon
id|dev-&gt;free
op_add_assign
id|dev-&gt;fsize
(braket
id|i
)braket
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
op_ne
id|ack
)paren
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|count
OL
l_int|7
op_logical_and
id|dev-&gt;write_queue
)paren
(brace
id|u8
id|lsend_seq
op_assign
id|dev-&gt;send_seq
suffix:semicolon
id|pcbit_transmit
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;send_seq
op_eq
id|lsend_seq
)paren
r_break
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
)brace
r_else
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;recv_ack: unacked = 0&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
