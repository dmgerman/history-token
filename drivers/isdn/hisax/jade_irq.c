multiline_comment|/* $Id: jade_irq.c,v 1.5.6.2 2001/09/23 22:24:49 kai Exp $&n; *&n; * Low level JADE IRQ stuff (derived from original hscx_irq.c)&n; *&n; * Author       Roland Klabunde&n; * Copyright    by Roland Klabunde   &lt;R.Klabunde@Berkom.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
DECL|variable|jade_irq_lock
r_static
id|spinlock_t
id|jade_irq_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
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
id|jade
comma
r_int
id|reg
)paren
(brace
r_int
id|to
op_assign
l_int|50
suffix:semicolon
r_int
id|mask
op_assign
(paren
id|reg
op_eq
id|jade_HDLC_XCMD
ques
c_cond
id|jadeSTAR_XCEC
suffix:colon
id|jadeSTAR_RCEC
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|READJADE
c_func
(paren
id|cs
comma
id|jade
comma
id|jade_HDLC_STAR
)paren
op_amp
id|mask
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
l_string|&quot;HiSax: waitforCEC (jade) timeout&bslash;n&quot;
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
id|jade
)paren
(brace
multiline_comment|/* Does not work on older jade versions, don&squot;t care */
)brace
r_static
r_inline
r_void
DECL|function|WriteJADECMDR
id|WriteJADECMDR
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|jade
comma
r_int
id|reg
comma
id|u_char
id|data
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|jade_irq_lock
comma
id|flags
)paren
suffix:semicolon
id|waitforCEC
c_func
(paren
id|cs
comma
id|jade
comma
id|reg
)paren
suffix:semicolon
id|WRITEJADE
c_func
(paren
id|cs
comma
id|jade
comma
id|reg
comma
id|data
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|jade_irq_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|jade_empty_fifo
id|jade_empty_fifo
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
l_string|&quot;jade_empty_fifo&quot;
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
l_string|&quot;jade_empty_fifo: incoming packet too large&quot;
)paren
suffix:semicolon
id|WriteJADECMDR
c_func
(paren
id|cs
comma
id|bcs-&gt;hw.hscx.hscx
comma
id|jade_HDLC_RCMD
comma
id|jadeRCMD_RMC
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|jade_irq_lock
comma
id|flags
)paren
suffix:semicolon
id|READJADEFIFO
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
id|WriteJADECMDR
c_func
(paren
id|cs
comma
id|bcs-&gt;hw.hscx.hscx
comma
id|jade_HDLC_RCMD
comma
id|jadeRCMD_RMC
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|jade_irq_lock
comma
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
l_string|&quot;jade_empty_fifo %c cnt %d&quot;
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
DECL|function|jade_fill_fifo
id|jade_fill_fifo
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
l_int|32
suffix:semicolon
id|u_char
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
l_string|&quot;jade_fill_fifo&quot;
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|jade_irq_lock
comma
id|flags
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
id|bcs-&gt;count
op_add_assign
id|count
suffix:semicolon
id|WRITEJADEFIFO
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
id|WriteJADECMDR
c_func
(paren
id|cs
comma
id|bcs-&gt;hw.hscx.hscx
comma
id|jade_HDLC_XCMD
comma
id|more
ques
c_cond
id|jadeXCMD_XF
suffix:colon
(paren
id|jadeXCMD_XF
op_or
id|jadeXCMD_XME
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|jade_irq_lock
comma
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
l_string|&quot;jade_fill_fifo %c cnt %d&quot;
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
DECL|function|jade_interrupt
id|jade_interrupt
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
id|jade
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
id|jade
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|fifo_size
op_assign
l_int|32
suffix:semicolon
r_int
id|count
suffix:semicolon
r_int
id|i_jade
op_assign
(paren
r_int
)paren
id|jade
suffix:semicolon
multiline_comment|/* To satisfy the compiler */
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
id|READJADE
c_func
(paren
id|cs
comma
id|i_jade
comma
id|jade_HDLC_RSTA
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
l_string|&quot;JADE %s invalid frame&quot;
comma
(paren
id|jade
ques
c_cond
l_string|&quot;B&quot;
suffix:colon
l_string|&quot;A&quot;
)paren
)paren
suffix:semicolon
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
l_string|&quot;JADE %c RDO mode=%d&quot;
comma
l_char|&squot;A&squot;
op_plus
id|jade
comma
id|bcs-&gt;mode
)paren
suffix:semicolon
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
l_string|&quot;JADE %c CRC error&quot;
comma
l_char|&squot;A&squot;
op_plus
id|jade
)paren
suffix:semicolon
id|WriteJADECMDR
c_func
(paren
id|cs
comma
id|jade
comma
id|jade_HDLC_RCMD
comma
id|jadeRCMD_RMC
)paren
suffix:semicolon
)brace
r_else
(brace
id|count
op_assign
id|READJADE
c_func
(paren
id|cs
comma
id|i_jade
comma
id|jade_HDLC_RBCL
)paren
op_amp
l_int|0x1F
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
id|jade_empty_fifo
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
l_string|&quot;JADE %s receive out of memory&bslash;n&quot;
comma
(paren
id|jade
ques
c_cond
l_string|&quot;B&quot;
suffix:colon
l_string|&quot;A&quot;
)paren
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
id|sched_b_event
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
id|jade_empty_fifo
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
id|sched_b_event
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
id|jade_fill_fifo
c_func
(paren
id|bcs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|xmit_complete_b
c_func
(paren
id|bcs
)paren
suffix:semicolon
id|bcs-&gt;count
op_assign
l_int|0
suffix:semicolon
)brace
id|xmit_ready_b
c_func
(paren
id|bcs
)paren
suffix:semicolon
)brace
)brace
r_static
r_inline
r_void
DECL|function|jade_int_main
id|jade_int_main
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
r_int
id|jade
)paren
(brace
r_struct
id|BCState
op_star
id|bcs
suffix:semicolon
id|bcs
op_assign
id|cs-&gt;bcs
op_plus
id|jade
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|jadeISR_RFO
)paren
(brace
multiline_comment|/* handled with RDO */
id|val
op_and_assign
op_complement
id|jadeISR_RFO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|val
op_amp
id|jadeISR_XDU
)paren
(brace
multiline_comment|/* relevant in HDLC mode only */
multiline_comment|/* don&squot;t reset XPR here */
r_if
c_cond
(paren
id|bcs-&gt;mode
op_eq
l_int|1
)paren
id|jade_fill_fifo
c_func
(paren
id|bcs
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/* Here we lost an TX interrupt, so&n;&t;&t;&t;   * restart transmitting the whole frame.&n;&t;&t;&t; */
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
id|bcs-&gt;count
)paren
suffix:semicolon
id|bcs-&gt;tx_cnt
op_add_assign
id|bcs-&gt;count
suffix:semicolon
id|bcs-&gt;count
op_assign
l_int|0
suffix:semicolon
)brace
id|WriteJADECMDR
c_func
(paren
id|cs
comma
id|bcs-&gt;hw.hscx.hscx
comma
id|jade_HDLC_XCMD
comma
id|jadeXCMD_XRES
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
l_string|&quot;JADE %c EXIR %x Lost TX&quot;
comma
l_char|&squot;A&squot;
op_plus
id|jade
comma
id|val
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|val
op_amp
(paren
id|jadeISR_RME
op_or
id|jadeISR_RPF
op_or
id|jadeISR_XPR
)paren
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
l_string|&quot;JADE %c interrupt %x&quot;
comma
l_char|&squot;A&squot;
op_plus
id|jade
comma
id|val
)paren
suffix:semicolon
id|jade_interrupt
c_func
(paren
id|cs
comma
id|val
comma
id|jade
)paren
suffix:semicolon
)brace
)brace
eof
