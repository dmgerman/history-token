multiline_comment|/* $Id: hscx_irq.c,v 1.16.6.2 2001/09/23 22:24:48 kai Exp $&n; *&n; * low level b-channel stuff for Siemens HSCX&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * This is an include file for fast inline IRQ stuff&n; *&n; */
r_static
r_inline
r_void
DECL|function|waitforCEC
id|waitforCEC
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|hscx
)paren
(brace
r_int
id|to
op_assign
l_int|50
suffix:semicolon
r_while
c_loop
(paren
(paren
id|READHSCX
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_STAR
)paren
op_amp
l_int|0x04
)paren
op_logical_and
id|to
)paren
(brace
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|to
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|to
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: waitforCEC timeout&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|waitforXFW
id|waitforXFW
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|hscx
)paren
(brace
r_int
id|to
op_assign
l_int|50
suffix:semicolon
r_while
c_loop
(paren
(paren
op_logical_neg
(paren
id|READHSCX
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_STAR
)paren
op_amp
l_int|0x44
)paren
op_eq
l_int|0x40
)paren
op_logical_and
id|to
)paren
(brace
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|to
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|to
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: waitforXFW timeout&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|WriteHSCXCMDR
id|WriteHSCXCMDR
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|hscx
comma
id|u_char
id|data
)paren
(brace
r_int
id|flags
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
id|waitforCEC
c_func
(paren
id|cs
comma
id|hscx
)paren
suffix:semicolon
id|WRITEHSCX
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_CMDR
comma
id|data
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|hscx_empty_fifo
id|hscx_empty_fifo
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
comma
r_int
id|count
)paren
(brace
id|u_char
op_star
id|ptr
suffix:semicolon
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|bcs-&gt;cs
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX
)paren
op_logical_and
op_logical_neg
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX_FIFO
)paren
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;hscx_empty_fifo&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bcs-&gt;hw.hscx.rcvidx
op_plus
id|count
OG
id|HSCX_BUFMAX
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_WARN
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;hscx_empty_fifo: incoming packet too large&quot;
)paren
suffix:semicolon
id|WriteHSCXCMDR
c_func
(paren
id|cs
comma
id|bcs-&gt;hw.hscx.hscx
comma
l_int|0x80
)paren
suffix:semicolon
id|bcs-&gt;hw.hscx.rcvidx
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ptr
op_assign
id|bcs-&gt;hw.hscx.rcvbuf
op_plus
id|bcs-&gt;hw.hscx.rcvidx
suffix:semicolon
id|bcs-&gt;hw.hscx.rcvidx
op_add_assign
id|count
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
id|READHSCXFIFO
c_func
(paren
id|cs
comma
id|bcs-&gt;hw.hscx.hscx
comma
id|ptr
comma
id|count
)paren
suffix:semicolon
id|WriteHSCXCMDR
c_func
(paren
id|cs
comma
id|bcs-&gt;hw.hscx.hscx
comma
l_int|0x80
)paren
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
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX_FIFO
)paren
(brace
r_char
op_star
id|t
op_assign
id|bcs-&gt;blog
suffix:semicolon
id|t
op_add_assign
id|sprintf
c_func
(paren
id|t
comma
l_string|&quot;hscx_empty_fifo %c cnt %d&quot;
comma
id|bcs-&gt;hw.hscx.hscx
ques
c_cond
l_char|&squot;B&squot;
suffix:colon
l_char|&squot;A&squot;
comma
id|count
)paren
suffix:semicolon
id|QuickHex
c_func
(paren
id|t
comma
id|ptr
comma
id|count
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
id|bcs-&gt;blog
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|hscx_fill_fifo
id|hscx_fill_fifo
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
)paren
(brace
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|bcs-&gt;cs
suffix:semicolon
r_int
id|more
comma
id|count
suffix:semicolon
r_int
id|fifo_size
op_assign
id|test_bit
c_func
(paren
id|HW_IPAC
comma
op_amp
id|cs-&gt;HW_Flags
)paren
ques
c_cond
l_int|64
suffix:colon
l_int|32
suffix:semicolon
id|u_char
op_star
id|ptr
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX
)paren
op_logical_and
op_logical_neg
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX_FIFO
)paren
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;hscx_fill_fifo&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bcs-&gt;tx_skb
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|bcs-&gt;tx_skb-&gt;len
op_le
l_int|0
)paren
r_return
suffix:semicolon
id|more
op_assign
(paren
id|bcs-&gt;mode
op_eq
id|L1_MODE_TRANS
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bcs-&gt;tx_skb-&gt;len
OG
id|fifo_size
)paren
(brace
id|more
op_assign
op_logical_neg
l_int|0
suffix:semicolon
id|count
op_assign
id|fifo_size
suffix:semicolon
)brace
r_else
id|count
op_assign
id|bcs-&gt;tx_skb-&gt;len
suffix:semicolon
id|waitforXFW
c_func
(paren
id|cs
comma
id|bcs-&gt;hw.hscx.hscx
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
id|ptr
op_assign
id|bcs-&gt;tx_skb-&gt;data
suffix:semicolon
id|skb_pull
c_func
(paren
id|bcs-&gt;tx_skb
comma
id|count
)paren
suffix:semicolon
id|bcs-&gt;tx_cnt
op_sub_assign
id|count
suffix:semicolon
id|bcs-&gt;hw.hscx.count
op_add_assign
id|count
suffix:semicolon
id|WRITEHSCXFIFO
c_func
(paren
id|cs
comma
id|bcs-&gt;hw.hscx.hscx
comma
id|ptr
comma
id|count
)paren
suffix:semicolon
id|WriteHSCXCMDR
c_func
(paren
id|cs
comma
id|bcs-&gt;hw.hscx.hscx
comma
id|more
ques
c_cond
l_int|0x8
suffix:colon
l_int|0xa
)paren
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
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX_FIFO
)paren
(brace
r_char
op_star
id|t
op_assign
id|bcs-&gt;blog
suffix:semicolon
id|t
op_add_assign
id|sprintf
c_func
(paren
id|t
comma
l_string|&quot;hscx_fill_fifo %c cnt %d&quot;
comma
id|bcs-&gt;hw.hscx.hscx
ques
c_cond
l_char|&squot;B&squot;
suffix:colon
l_char|&squot;A&squot;
comma
id|count
)paren
suffix:semicolon
id|QuickHex
c_func
(paren
id|t
comma
id|ptr
comma
id|count
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
id|bcs-&gt;blog
)paren
suffix:semicolon
)brace
)brace
r_static
r_inline
r_void
DECL|function|hscx_interrupt
id|hscx_interrupt
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
id|val
comma
id|u_char
id|hscx
)paren
(brace
id|u_char
id|r
suffix:semicolon
r_struct
id|BCState
op_star
id|bcs
op_assign
id|cs-&gt;bcs
op_plus
id|hscx
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|fifo_size
op_assign
id|test_bit
c_func
(paren
id|HW_IPAC
comma
op_amp
id|cs-&gt;HW_Flags
)paren
ques
c_cond
l_int|64
suffix:colon
l_int|32
suffix:semicolon
r_int
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|BC_FLG_INIT
comma
op_amp
id|bcs-&gt;Flag
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
l_int|0x80
)paren
(brace
multiline_comment|/* RME */
id|r
op_assign
id|READHSCX
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_RSTA
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r
op_amp
l_int|0xf0
)paren
op_ne
l_int|0xa0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|r
op_amp
l_int|0x80
)paren
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_WARN
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX invalid frame&quot;
)paren
suffix:semicolon
macro_line|#ifdef ERROR_STATISTIC
id|bcs-&gt;err_inv
op_increment
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
(paren
id|r
op_amp
l_int|0x40
)paren
op_logical_and
id|bcs-&gt;mode
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_WARN
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX RDO mode=%d&quot;
comma
id|bcs-&gt;mode
)paren
suffix:semicolon
macro_line|#ifdef ERROR_STATISTIC
id|bcs-&gt;err_rdo
op_increment
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|r
op_amp
l_int|0x20
)paren
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_WARN
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX CRC error&quot;
)paren
suffix:semicolon
macro_line|#ifdef ERROR_STATISTIC
id|bcs-&gt;err_crc
op_increment
suffix:semicolon
macro_line|#endif
)brace
id|WriteHSCXCMDR
c_func
(paren
id|cs
comma
id|hscx
comma
l_int|0x80
)paren
suffix:semicolon
)brace
r_else
(brace
id|count
op_assign
id|READHSCX
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_RBCL
)paren
op_amp
(paren
id|test_bit
c_func
(paren
id|HW_IPAC
comma
op_amp
id|cs-&gt;HW_Flags
)paren
ques
c_cond
l_int|0x3f
suffix:colon
l_int|0x1f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
id|count
op_assign
id|fifo_size
suffix:semicolon
id|hscx_empty_fifo
c_func
(paren
id|bcs
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|count
op_assign
id|bcs-&gt;hw.hscx.rcvidx
op_minus
l_int|1
)paren
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX_FIFO
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HX Frame %d&quot;
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|count
)paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HSCX: receive out of memory&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
id|count
)paren
comma
id|bcs-&gt;hw.hscx.rcvbuf
comma
id|count
)paren
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|bcs-&gt;rqueue
comma
id|skb
)paren
suffix:semicolon
)brace
)brace
)brace
id|bcs-&gt;hw.hscx.rcvidx
op_assign
l_int|0
suffix:semicolon
id|hscx_sched_event
c_func
(paren
id|bcs
comma
id|B_RCVBUFREADY
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|val
op_amp
l_int|0x40
)paren
(brace
multiline_comment|/* RPF */
id|hscx_empty_fifo
c_func
(paren
id|bcs
comma
id|fifo_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bcs-&gt;mode
op_eq
id|L1_MODE_TRANS
)paren
(brace
multiline_comment|/* receive audio data */
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|fifo_size
)paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: receive out of memory&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
id|fifo_size
)paren
comma
id|bcs-&gt;hw.hscx.rcvbuf
comma
id|fifo_size
)paren
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|bcs-&gt;rqueue
comma
id|skb
)paren
suffix:semicolon
)brace
id|bcs-&gt;hw.hscx.rcvidx
op_assign
l_int|0
suffix:semicolon
id|hscx_sched_event
c_func
(paren
id|bcs
comma
id|B_RCVBUFREADY
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|val
op_amp
l_int|0x10
)paren
(brace
multiline_comment|/* XPR */
r_if
c_cond
(paren
id|bcs-&gt;tx_skb
)paren
(brace
r_if
c_cond
(paren
id|bcs-&gt;tx_skb-&gt;len
)paren
(brace
id|hscx_fill_fifo
c_func
(paren
id|bcs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|bcs-&gt;st-&gt;lli.l1writewakeup
op_logical_and
(paren
id|PACKET_NOACK
op_ne
id|bcs-&gt;tx_skb-&gt;pkt_type
)paren
)paren
id|bcs-&gt;st-&gt;lli
dot
id|l1writewakeup
c_func
(paren
id|bcs-&gt;st
comma
id|bcs-&gt;hw.hscx.count
)paren
suffix:semicolon
id|dev_kfree_skb_irq
c_func
(paren
id|bcs-&gt;tx_skb
)paren
suffix:semicolon
id|bcs-&gt;hw.hscx.count
op_assign
l_int|0
suffix:semicolon
id|bcs-&gt;tx_skb
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|bcs-&gt;tx_skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|bcs-&gt;squeue
)paren
)paren
)paren
(brace
id|bcs-&gt;hw.hscx.count
op_assign
l_int|0
suffix:semicolon
id|test_and_set_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|bcs-&gt;Flag
)paren
suffix:semicolon
id|hscx_fill_fifo
c_func
(paren
id|bcs
)paren
suffix:semicolon
)brace
r_else
(brace
id|test_and_clear_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|bcs-&gt;Flag
)paren
suffix:semicolon
id|hscx_sched_event
c_func
(paren
id|bcs
comma
id|B_XMTBUFREADY
)paren
suffix:semicolon
)brace
)brace
)brace
r_static
r_inline
r_void
DECL|function|hscx_int_main
id|hscx_int_main
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
id|val
)paren
(brace
id|u_char
id|exval
suffix:semicolon
r_struct
id|BCState
op_star
id|bcs
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
l_int|0x01
)paren
(brace
id|bcs
op_assign
id|cs-&gt;bcs
op_plus
l_int|1
suffix:semicolon
id|exval
op_assign
id|READHSCX
c_func
(paren
id|cs
comma
l_int|1
comma
id|HSCX_EXIR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exval
op_amp
l_int|0x40
)paren
(brace
r_if
c_cond
(paren
id|bcs-&gt;mode
op_eq
l_int|1
)paren
id|hscx_fill_fifo
c_func
(paren
id|bcs
)paren
suffix:semicolon
r_else
(brace
macro_line|#ifdef ERROR_STATISTIC
id|bcs-&gt;err_tx
op_increment
suffix:semicolon
macro_line|#endif
multiline_comment|/* Here we lost an TX interrupt, so&n;&t;&t;&t;&t;   * restart transmitting the whole frame.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|bcs-&gt;tx_skb
)paren
(brace
id|skb_push
c_func
(paren
id|bcs-&gt;tx_skb
comma
id|bcs-&gt;hw.hscx.count
)paren
suffix:semicolon
id|bcs-&gt;tx_cnt
op_add_assign
id|bcs-&gt;hw.hscx.count
suffix:semicolon
id|bcs-&gt;hw.hscx.count
op_assign
l_int|0
suffix:semicolon
)brace
id|WriteHSCXCMDR
c_func
(paren
id|cs
comma
id|bcs-&gt;hw.hscx.hscx
comma
l_int|0x01
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_WARN
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX B EXIR %x Lost TX&quot;
comma
id|exval
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX B EXIR %x&quot;
comma
id|exval
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|val
op_amp
l_int|0xf8
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX B interrupt %x&quot;
comma
id|val
)paren
suffix:semicolon
id|hscx_interrupt
c_func
(paren
id|cs
comma
id|val
comma
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|val
op_amp
l_int|0x02
)paren
(brace
id|bcs
op_assign
id|cs-&gt;bcs
suffix:semicolon
id|exval
op_assign
id|READHSCX
c_func
(paren
id|cs
comma
l_int|0
comma
id|HSCX_EXIR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exval
op_amp
l_int|0x40
)paren
(brace
r_if
c_cond
(paren
id|bcs-&gt;mode
op_eq
id|L1_MODE_TRANS
)paren
id|hscx_fill_fifo
c_func
(paren
id|bcs
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/* Here we lost an TX interrupt, so&n;&t;&t;&t;&t;   * restart transmitting the whole frame.&n;&t;&t;&t;&t; */
macro_line|#ifdef ERROR_STATISTIC
id|bcs-&gt;err_tx
op_increment
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|bcs-&gt;tx_skb
)paren
(brace
id|skb_push
c_func
(paren
id|bcs-&gt;tx_skb
comma
id|bcs-&gt;hw.hscx.count
)paren
suffix:semicolon
id|bcs-&gt;tx_cnt
op_add_assign
id|bcs-&gt;hw.hscx.count
suffix:semicolon
id|bcs-&gt;hw.hscx.count
op_assign
l_int|0
suffix:semicolon
)brace
id|WriteHSCXCMDR
c_func
(paren
id|cs
comma
id|bcs-&gt;hw.hscx.hscx
comma
l_int|0x01
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_WARN
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX A EXIR %x Lost TX&quot;
comma
id|exval
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX A EXIR %x&quot;
comma
id|exval
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|val
op_amp
l_int|0x04
)paren
(brace
id|exval
op_assign
id|READHSCX
c_func
(paren
id|cs
comma
l_int|0
comma
id|HSCX_ISTA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX A interrupt %x&quot;
comma
id|exval
)paren
suffix:semicolon
id|hscx_interrupt
c_func
(paren
id|cs
comma
id|exval
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
eof
