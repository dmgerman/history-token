multiline_comment|/* $Id: isac.c,v 1.28.6.3 2001/09/23 22:24:49 kai Exp $&n; *&n; * ISAC specific routines&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * For changes and modifications please read&n; * ../../../Documentation/isdn/HiSax.cert&n; *&n; */
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;arcofi.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|macro|DBUSY_TIMER_VALUE
mdefine_line|#define DBUSY_TIMER_VALUE 80
DECL|macro|ARCOFI_USE
mdefine_line|#define ARCOFI_USE 1
DECL|variable|__devinitdata
r_static
r_char
op_star
id|ISACVer
(braket
)braket
id|__devinitdata
op_assign
(brace
l_string|&quot;2086/2186 V1.1&quot;
comma
l_string|&quot;2085 B1&quot;
comma
l_string|&quot;2085 B2&quot;
comma
l_string|&quot;2085 V2.3&quot;
)brace
suffix:semicolon
r_static
r_inline
id|u8
DECL|function|isac_read
id|isac_read
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u8
id|addr
)paren
(brace
r_return
id|cs-&gt;dc_hw_ops
op_member_access_from_pointer
id|read_reg
c_func
(paren
id|cs
comma
id|addr
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|isac_write
id|isac_write
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u8
id|addr
comma
id|u8
id|val
)paren
(brace
id|cs-&gt;dc_hw_ops
op_member_access_from_pointer
id|write_reg
c_func
(paren
id|cs
comma
id|addr
comma
id|val
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|isac_write_fifo
id|isac_write_fifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u8
op_star
id|p
comma
r_int
id|len
)paren
(brace
r_return
id|cs-&gt;dc_hw_ops
op_member_access_from_pointer
id|write_fifo
c_func
(paren
id|cs
comma
id|p
comma
id|len
)paren
suffix:semicolon
)brace
r_void
DECL|function|ISACVersion
id|ISACVersion
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_char
op_star
id|s
)paren
(brace
r_int
id|val
suffix:semicolon
id|val
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_RBCH
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s ISAC version (%x): %s&bslash;n&quot;
comma
id|s
comma
id|val
comma
id|ISACVer
(braket
(paren
id|val
op_rshift
l_int|5
)paren
op_amp
l_int|3
)braket
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|ph_command
id|ph_command
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
r_int
id|command
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_ISAC
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ph_command %x&quot;
comma
id|command
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_CIX0
comma
(paren
id|command
op_lshift
l_int|2
)paren
op_or
l_int|3
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|isac_new_ph
id|isac_new_ph
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_switch
c_cond
(paren
id|cs-&gt;dc.isac.ph_state
)paren
(brace
r_case
(paren
id|ISAC_IND_RS
)paren
suffix:colon
r_case
(paren
id|ISAC_IND_EI
)paren
suffix:colon
id|ph_command
c_func
(paren
id|cs
comma
id|ISAC_CMD_DUI
)paren
suffix:semicolon
id|l1_msg
c_func
(paren
id|cs
comma
id|HW_RESET
op_or
id|INDICATION
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|ISAC_IND_DID
)paren
suffix:colon
id|l1_msg
c_func
(paren
id|cs
comma
id|HW_DEACTIVATE
op_or
id|CONFIRM
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|ISAC_IND_DR
)paren
suffix:colon
id|l1_msg
c_func
(paren
id|cs
comma
id|HW_DEACTIVATE
op_or
id|INDICATION
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|ISAC_IND_PU
)paren
suffix:colon
id|l1_msg
c_func
(paren
id|cs
comma
id|HW_POWERUP
op_or
id|CONFIRM
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|ISAC_IND_RSY
)paren
suffix:colon
id|l1_msg
c_func
(paren
id|cs
comma
id|HW_RSYNC
op_or
id|INDICATION
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|ISAC_IND_ARD
)paren
suffix:colon
id|l1_msg
c_func
(paren
id|cs
comma
id|HW_INFO2
op_or
id|INDICATION
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|ISAC_IND_AI8
)paren
suffix:colon
id|l1_msg
c_func
(paren
id|cs
comma
id|HW_INFO4_P8
op_or
id|INDICATION
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|ISAC_IND_AI10
)paren
suffix:colon
id|l1_msg
c_func
(paren
id|cs
comma
id|HW_INFO4_P10
op_or
id|INDICATION
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|isac_bh
id|isac_bh
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|data
suffix:semicolon
r_struct
id|PStack
op_star
id|stptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cs
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|D_CLEARBUSY
comma
op_amp
id|cs-&gt;event
)paren
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;D-Channel Busy cleared&quot;
)paren
suffix:semicolon
id|stptr
op_assign
id|cs-&gt;stlist
suffix:semicolon
r_while
c_loop
(paren
id|stptr
op_ne
l_int|NULL
)paren
(brace
id|L1L2
c_func
(paren
id|stptr
comma
id|PH_PAUSE
op_or
id|CONFIRM
comma
l_int|NULL
)paren
suffix:semicolon
id|stptr
op_assign
id|stptr-&gt;next
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|D_L1STATECHANGE
comma
op_amp
id|cs-&gt;event
)paren
)paren
id|isac_new_ph
c_func
(paren
id|cs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|D_RCVBUFREADY
comma
op_amp
id|cs-&gt;event
)paren
)paren
id|DChannel_proc_rcv
c_func
(paren
id|cs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|D_XMTBUFREADY
comma
op_amp
id|cs-&gt;event
)paren
)paren
id|DChannel_proc_xmt
c_func
(paren
id|cs
)paren
suffix:semicolon
macro_line|#if ARCOFI_USE
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|HW_ARCOFI
comma
op_amp
id|cs-&gt;HW_Flags
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|D_RX_MON1
comma
op_amp
id|cs-&gt;event
)paren
)paren
id|arcofi_fsm
c_func
(paren
id|cs
comma
id|ARCOFI_RX_END
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|D_TX_MON1
comma
op_amp
id|cs-&gt;event
)paren
)paren
id|arcofi_fsm
c_func
(paren
id|cs
comma
id|ARCOFI_TX_END
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
)brace
r_void
DECL|function|isac_empty_fifo
id|isac_empty_fifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|count
)paren
(brace
id|recv_empty_fifo_d
c_func
(paren
id|cs
comma
id|count
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_CMDR
comma
l_int|0x80
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|isac_fill_fifo
id|isac_fill_fifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_int
id|count
comma
id|more
suffix:semicolon
r_int
r_char
op_star
id|p
suffix:semicolon
id|p
op_assign
id|xmit_fill_fifo_d
c_func
(paren
id|cs
comma
l_int|32
comma
op_amp
id|count
comma
op_amp
id|more
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
suffix:semicolon
id|isac_write_fifo
c_func
(paren
id|cs
comma
id|p
comma
id|count
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_CMDR
comma
id|more
ques
c_cond
l_int|0x8
suffix:colon
l_int|0xa
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|FLG_DBUSY_TIMER
comma
op_amp
id|cs-&gt;HW_Flags
)paren
)paren
(brace
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;isac_fill_fifo dbusytimer running&quot;
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|cs-&gt;dbusytimer
)paren
suffix:semicolon
)brace
id|init_timer
c_func
(paren
op_amp
id|cs-&gt;dbusytimer
)paren
suffix:semicolon
id|cs-&gt;dbusytimer.expires
op_assign
id|jiffies
op_plus
(paren
(paren
id|DBUSY_TIMER_VALUE
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|cs-&gt;dbusytimer
)paren
suffix:semicolon
)brace
r_void
DECL|function|isac_interrupt
id|isac_interrupt
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u8
id|val
)paren
(brace
id|u8
id|exval
comma
id|v1
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_ISAC
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC interrupt %x&quot;
comma
id|val
)paren
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
id|exval
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_RSTA
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|exval
op_amp
l_int|0x70
)paren
op_ne
l_int|0x20
)paren
(brace
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
id|cs-&gt;debug
op_amp
id|L1_DEB_WARN
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC RDO&quot;
)paren
suffix:semicolon
macro_line|#ifdef ERROR_STATISTIC
id|cs-&gt;err_rx
op_increment
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|exval
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
l_string|&quot;ISAC CRC error&quot;
)paren
suffix:semicolon
macro_line|#ifdef ERROR_STATISTIC
id|cs-&gt;err_crc
op_increment
suffix:semicolon
macro_line|#endif
)brace
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_CMDR
comma
l_int|0x80
)paren
suffix:semicolon
id|cs-&gt;rcvidx
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|count
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_RBCL
)paren
op_amp
l_int|0x1f
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
l_int|32
suffix:semicolon
id|isac_empty_fifo
c_func
(paren
id|cs
comma
id|count
)paren
suffix:semicolon
id|recv_rme_d
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
id|cs-&gt;rcvidx
op_assign
l_int|0
suffix:semicolon
id|sched_d_event
c_func
(paren
id|cs
comma
id|D_RCVBUFREADY
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
id|isac_empty_fifo
c_func
(paren
id|cs
comma
l_int|32
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|val
op_amp
l_int|0x20
)paren
(brace
multiline_comment|/* RSC */
multiline_comment|/* never */
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
l_string|&quot;ISAC RSC interrupt&quot;
)paren
suffix:semicolon
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
id|xmit_xpr_d
c_func
(paren
id|cs
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
multiline_comment|/* CISQ */
id|exval
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_CIR0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_ISAC
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC CIR0 %02X&quot;
comma
id|exval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exval
op_amp
l_int|2
)paren
(brace
id|cs-&gt;dc.isac.ph_state
op_assign
(paren
id|exval
op_rshift
l_int|2
)paren
op_amp
l_int|0xf
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_ISAC
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ph_state change %x&quot;
comma
id|cs-&gt;dc.isac.ph_state
)paren
suffix:semicolon
id|sched_d_event
c_func
(paren
id|cs
comma
id|D_L1STATECHANGE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|exval
op_amp
l_int|1
)paren
(brace
id|exval
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_CIR1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_ISAC
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC CIR1 %02X&quot;
comma
id|exval
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|val
op_amp
l_int|0x02
)paren
(brace
multiline_comment|/* SIN */
multiline_comment|/* never */
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
l_string|&quot;ISAC SIN interrupt&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|val
op_amp
l_int|0x01
)paren
(brace
multiline_comment|/* EXI */
id|exval
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_EXIR
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
l_string|&quot;ISAC EXIR %02x&quot;
comma
id|exval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exval
op_amp
l_int|0x80
)paren
(brace
multiline_comment|/* XMR */
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC XMR&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: ISAC XMR&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|exval
op_amp
l_int|0x40
)paren
(brace
multiline_comment|/* XDU */
id|xmit_xdu_d
c_func
(paren
id|cs
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|exval
op_amp
l_int|0x04
)paren
(brace
multiline_comment|/* MOS */
id|v1
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_MOSR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_MONITOR
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC MOSR %02x&quot;
comma
id|v1
)paren
suffix:semicolon
macro_line|#if ARCOFI_USE
r_if
c_cond
(paren
id|v1
op_amp
l_int|0x08
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cs-&gt;dc.isac.mon_rx
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|cs-&gt;dc.isac.mon_rx
op_assign
id|kmalloc
c_func
(paren
id|MAX_MON_FRAME
comma
id|GFP_ATOMIC
)paren
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
l_string|&quot;ISAC MON RX out of memory!&quot;
)paren
suffix:semicolon
id|cs-&gt;dc.isac.mocr
op_and_assign
l_int|0xf0
suffix:semicolon
id|cs-&gt;dc.isac.mocr
op_or_assign
l_int|0x0a
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MOCR
comma
id|cs-&gt;dc.isac.mocr
)paren
suffix:semicolon
r_goto
id|afterMONR0
suffix:semicolon
)brace
r_else
id|cs-&gt;dc.isac.mon_rxp
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cs-&gt;dc.isac.mon_rxp
op_ge
id|MAX_MON_FRAME
)paren
(brace
id|cs-&gt;dc.isac.mocr
op_and_assign
l_int|0xf0
suffix:semicolon
id|cs-&gt;dc.isac.mocr
op_or_assign
l_int|0x0a
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MOCR
comma
id|cs-&gt;dc.isac.mocr
)paren
suffix:semicolon
id|cs-&gt;dc.isac.mon_rxp
op_assign
l_int|0
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
l_string|&quot;ISAC MON RX overflow!&quot;
)paren
suffix:semicolon
r_goto
id|afterMONR0
suffix:semicolon
)brace
id|cs-&gt;dc.isac.mon_rx
(braket
id|cs-&gt;dc.isac.mon_rxp
op_increment
)braket
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_MOR0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_MONITOR
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC MOR0 %02x&quot;
comma
id|cs-&gt;dc.isac.mon_rx
(braket
id|cs-&gt;dc.isac.mon_rxp
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;dc.isac.mon_rxp
op_eq
l_int|1
)paren
(brace
id|cs-&gt;dc.isac.mocr
op_or_assign
l_int|0x04
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MOCR
comma
id|cs-&gt;dc.isac.mocr
)paren
suffix:semicolon
)brace
)brace
id|afterMONR0
suffix:colon
r_if
c_cond
(paren
id|v1
op_amp
l_int|0x80
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cs-&gt;dc.isac.mon_rx
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|cs-&gt;dc.isac.mon_rx
op_assign
id|kmalloc
c_func
(paren
id|MAX_MON_FRAME
comma
id|GFP_ATOMIC
)paren
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
l_string|&quot;ISAC MON RX out of memory!&quot;
)paren
suffix:semicolon
id|cs-&gt;dc.isac.mocr
op_and_assign
l_int|0x0f
suffix:semicolon
id|cs-&gt;dc.isac.mocr
op_or_assign
l_int|0xa0
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MOCR
comma
id|cs-&gt;dc.isac.mocr
)paren
suffix:semicolon
r_goto
id|afterMONR1
suffix:semicolon
)brace
r_else
id|cs-&gt;dc.isac.mon_rxp
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cs-&gt;dc.isac.mon_rxp
op_ge
id|MAX_MON_FRAME
)paren
(brace
id|cs-&gt;dc.isac.mocr
op_and_assign
l_int|0x0f
suffix:semicolon
id|cs-&gt;dc.isac.mocr
op_or_assign
l_int|0xa0
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MOCR
comma
id|cs-&gt;dc.isac.mocr
)paren
suffix:semicolon
id|cs-&gt;dc.isac.mon_rxp
op_assign
l_int|0
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
l_string|&quot;ISAC MON RX overflow!&quot;
)paren
suffix:semicolon
r_goto
id|afterMONR1
suffix:semicolon
)brace
id|cs-&gt;dc.isac.mon_rx
(braket
id|cs-&gt;dc.isac.mon_rxp
op_increment
)braket
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_MOR1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_MONITOR
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC MOR1 %02x&quot;
comma
id|cs-&gt;dc.isac.mon_rx
(braket
id|cs-&gt;dc.isac.mon_rxp
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|cs-&gt;dc.isac.mocr
op_or_assign
l_int|0x40
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MOCR
comma
id|cs-&gt;dc.isac.mocr
)paren
suffix:semicolon
)brace
id|afterMONR1
suffix:colon
r_if
c_cond
(paren
id|v1
op_amp
l_int|0x04
)paren
(brace
id|cs-&gt;dc.isac.mocr
op_and_assign
l_int|0xf0
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MOCR
comma
id|cs-&gt;dc.isac.mocr
)paren
suffix:semicolon
id|cs-&gt;dc.isac.mocr
op_or_assign
l_int|0x0a
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MOCR
comma
id|cs-&gt;dc.isac.mocr
)paren
suffix:semicolon
id|sched_d_event
c_func
(paren
id|cs
comma
id|D_RX_MON0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|v1
op_amp
l_int|0x40
)paren
(brace
id|cs-&gt;dc.isac.mocr
op_and_assign
l_int|0x0f
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MOCR
comma
id|cs-&gt;dc.isac.mocr
)paren
suffix:semicolon
id|cs-&gt;dc.isac.mocr
op_or_assign
l_int|0xa0
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MOCR
comma
id|cs-&gt;dc.isac.mocr
)paren
suffix:semicolon
id|sched_d_event
c_func
(paren
id|cs
comma
id|D_RX_MON1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|v1
op_amp
l_int|0x02
)paren
(brace
r_if
c_cond
(paren
(paren
op_logical_neg
id|cs-&gt;dc.isac.mon_tx
)paren
op_logical_or
(paren
id|cs-&gt;dc.isac.mon_txc
op_logical_and
(paren
id|cs-&gt;dc.isac.mon_txp
op_ge
id|cs-&gt;dc.isac.mon_txc
)paren
op_logical_and
op_logical_neg
(paren
id|v1
op_amp
l_int|0x08
)paren
)paren
)paren
(brace
id|cs-&gt;dc.isac.mocr
op_and_assign
l_int|0xf0
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MOCR
comma
id|cs-&gt;dc.isac.mocr
)paren
suffix:semicolon
id|cs-&gt;dc.isac.mocr
op_or_assign
l_int|0x0a
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MOCR
comma
id|cs-&gt;dc.isac.mocr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;dc.isac.mon_txc
op_logical_and
(paren
id|cs-&gt;dc.isac.mon_txp
op_ge
id|cs-&gt;dc.isac.mon_txc
)paren
)paren
id|sched_d_event
c_func
(paren
id|cs
comma
id|D_TX_MON0
)paren
suffix:semicolon
r_goto
id|AfterMOX0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cs-&gt;dc.isac.mon_txc
op_logical_and
(paren
id|cs-&gt;dc.isac.mon_txp
op_ge
id|cs-&gt;dc.isac.mon_txc
)paren
)paren
(brace
id|sched_d_event
c_func
(paren
id|cs
comma
id|D_TX_MON0
)paren
suffix:semicolon
r_goto
id|AfterMOX0
suffix:semicolon
)brace
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MOX0
comma
id|cs-&gt;dc.isac.mon_tx
(braket
id|cs-&gt;dc.isac.mon_txp
op_increment
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_MONITOR
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC %02x -&gt; MOX0&quot;
comma
id|cs-&gt;dc.isac.mon_tx
(braket
id|cs-&gt;dc.isac.mon_txp
op_minus
l_int|1
)braket
)paren
suffix:semicolon
)brace
id|AfterMOX0
suffix:colon
r_if
c_cond
(paren
id|v1
op_amp
l_int|0x20
)paren
(brace
r_if
c_cond
(paren
(paren
op_logical_neg
id|cs-&gt;dc.isac.mon_tx
)paren
op_logical_or
(paren
id|cs-&gt;dc.isac.mon_txc
op_logical_and
(paren
id|cs-&gt;dc.isac.mon_txp
op_ge
id|cs-&gt;dc.isac.mon_txc
)paren
op_logical_and
op_logical_neg
(paren
id|v1
op_amp
l_int|0x80
)paren
)paren
)paren
(brace
id|cs-&gt;dc.isac.mocr
op_and_assign
l_int|0x0f
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MOCR
comma
id|cs-&gt;dc.isac.mocr
)paren
suffix:semicolon
id|cs-&gt;dc.isac.mocr
op_or_assign
l_int|0xa0
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MOCR
comma
id|cs-&gt;dc.isac.mocr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;dc.isac.mon_txc
op_logical_and
(paren
id|cs-&gt;dc.isac.mon_txp
op_ge
id|cs-&gt;dc.isac.mon_txc
)paren
)paren
id|sched_d_event
c_func
(paren
id|cs
comma
id|D_TX_MON1
)paren
suffix:semicolon
r_goto
id|AfterMOX1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cs-&gt;dc.isac.mon_txc
op_logical_and
(paren
id|cs-&gt;dc.isac.mon_txp
op_ge
id|cs-&gt;dc.isac.mon_txc
)paren
)paren
(brace
id|sched_d_event
c_func
(paren
id|cs
comma
id|D_TX_MON1
)paren
suffix:semicolon
r_goto
id|AfterMOX1
suffix:semicolon
)brace
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MOX1
comma
id|cs-&gt;dc.isac.mon_tx
(braket
id|cs-&gt;dc.isac.mon_txp
op_increment
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_MONITOR
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC %02x -&gt; MOX1&quot;
comma
id|cs-&gt;dc.isac.mon_tx
(braket
id|cs-&gt;dc.isac.mon_txp
op_minus
l_int|1
)braket
)paren
suffix:semicolon
)brace
id|AfterMOX1
suffix:colon
suffix:semicolon
macro_line|#endif
)brace
)brace
)brace
r_static
r_void
DECL|function|ISAC_l1hw
id|ISAC_l1hw
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_int
id|pr
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
(paren
r_struct
id|IsdnCardState
op_star
)paren
id|st-&gt;l1.hardware
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|arg
suffix:semicolon
r_int
id|val
suffix:semicolon
r_switch
c_cond
(paren
id|pr
)paren
(brace
r_case
(paren
id|PH_DATA
op_or
id|REQUEST
)paren
suffix:colon
id|xmit_data_req_d
c_func
(paren
id|cs
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|PH_PULL
op_or
id|INDICATION
)paren
suffix:colon
id|xmit_pull_ind_d
c_func
(paren
id|cs
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|PH_PULL
op_or
id|REQUEST
)paren
suffix:colon
id|xmit_pull_req_d
c_func
(paren
id|st
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|HW_RESET
op_or
id|REQUEST
)paren
suffix:colon
r_if
c_cond
(paren
(paren
id|cs-&gt;dc.isac.ph_state
op_eq
id|ISAC_IND_EI
)paren
op_logical_or
(paren
id|cs-&gt;dc.isac.ph_state
op_eq
id|ISAC_IND_DR
)paren
op_logical_or
(paren
id|cs-&gt;dc.isac.ph_state
op_eq
id|ISAC_IND_RS
)paren
)paren
id|ph_command
c_func
(paren
id|cs
comma
id|ISAC_CMD_TIM
)paren
suffix:semicolon
r_else
id|ph_command
c_func
(paren
id|cs
comma
id|ISAC_CMD_RS
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|HW_ENABLE
op_or
id|REQUEST
)paren
suffix:colon
id|ph_command
c_func
(paren
id|cs
comma
id|ISAC_CMD_TIM
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|HW_INFO3
op_or
id|REQUEST
)paren
suffix:colon
id|ph_command
c_func
(paren
id|cs
comma
id|ISAC_CMD_AR8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|HW_TESTLOOP
op_or
id|REQUEST
)paren
suffix:colon
id|val
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
l_int|1
op_amp
(paren
r_int
)paren
id|arg
)paren
id|val
op_or_assign
l_int|0x0c
suffix:semicolon
r_if
c_cond
(paren
l_int|2
op_amp
(paren
r_int
)paren
id|arg
)paren
id|val
op_or_assign
l_int|0x3
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|HW_IOM1
comma
op_amp
id|cs-&gt;HW_Flags
)paren
)paren
(brace
multiline_comment|/* IOM 1 Mode */
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
(brace
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_SPCR
comma
l_int|0xa
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_ADF1
comma
l_int|0x2
)paren
suffix:semicolon
)brace
r_else
(brace
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_SPCR
comma
id|val
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_ADF1
comma
l_int|0xa
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* IOM 2 Mode */
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_SPCR
comma
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_ADF1
comma
l_int|0x8
)paren
suffix:semicolon
r_else
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_ADF1
comma
l_int|0x0
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
(paren
id|HW_DEACTIVATE
op_or
id|RESPONSE
)paren
suffix:colon
id|skb_queue_purge
c_func
(paren
op_amp
id|cs-&gt;rq
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|cs-&gt;sq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;tx_skb
)paren
(brace
id|dev_kfree_skb_any
c_func
(paren
id|cs-&gt;tx_skb
)paren
suffix:semicolon
id|cs-&gt;tx_skb
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|FLG_DBUSY_TIMER
comma
op_amp
id|cs-&gt;HW_Flags
)paren
)paren
id|del_timer
c_func
(paren
op_amp
id|cs-&gt;dbusytimer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|FLG_L1_DBUSY
comma
op_amp
id|cs-&gt;HW_Flags
)paren
)paren
id|sched_d_event
c_func
(paren
id|cs
comma
id|D_CLEARBUSY
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
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
l_string|&quot;isac_l1hw unknown %04x&quot;
comma
id|pr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_void
DECL|function|setstack_isac
id|setstack_isac
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|st-&gt;l1.l1hw
op_assign
id|ISAC_l1hw
suffix:semicolon
)brace
r_void
DECL|function|DC_Close_isac
id|DC_Close_isac
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;dc.isac.mon_rx
)paren
(brace
id|kfree
c_func
(paren
id|cs-&gt;dc.isac.mon_rx
)paren
suffix:semicolon
id|cs-&gt;dc.isac.mon_rx
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cs-&gt;dc.isac.mon_tx
)paren
(brace
id|kfree
c_func
(paren
id|cs-&gt;dc.isac.mon_tx
)paren
suffix:semicolon
id|cs-&gt;dc.isac.mon_tx
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|dbusy_timer_handler
id|dbusy_timer_handler
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_struct
id|PStack
op_star
id|stptr
suffix:semicolon
r_int
id|rbch
comma
id|star
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|FLG_DBUSY_TIMER
comma
op_amp
id|cs-&gt;HW_Flags
)paren
)paren
(brace
id|rbch
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_RBCH
)paren
suffix:semicolon
id|star
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_STAR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;debug
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;D-Channel Busy RBCH %02x STAR %02x&quot;
comma
id|rbch
comma
id|star
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rbch
op_amp
id|ISAC_RBCH_XAC
)paren
(brace
multiline_comment|/* D-Channel Busy */
id|test_and_set_bit
c_func
(paren
id|FLG_L1_DBUSY
comma
op_amp
id|cs-&gt;HW_Flags
)paren
suffix:semicolon
id|stptr
op_assign
id|cs-&gt;stlist
suffix:semicolon
r_while
c_loop
(paren
id|stptr
op_ne
l_int|NULL
)paren
(brace
id|L1L2
c_func
(paren
id|stptr
comma
id|PH_PAUSE
op_or
id|INDICATION
comma
l_int|NULL
)paren
suffix:semicolon
id|stptr
op_assign
id|stptr-&gt;next
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* discard frame; reset transceiver */
id|test_and_clear_bit
c_func
(paren
id|FLG_DBUSY_TIMER
comma
op_amp
id|cs-&gt;HW_Flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;tx_skb
)paren
(brace
id|dev_kfree_skb_any
c_func
(paren
id|cs-&gt;tx_skb
)paren
suffix:semicolon
id|cs-&gt;tx_cnt
op_assign
l_int|0
suffix:semicolon
id|cs-&gt;tx_skb
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: ISAC D-Channel Busy no skb&bslash;n&quot;
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;D-Channel Busy no skb&quot;
)paren
suffix:semicolon
)brace
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_CMDR
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* Transmitter reset */
id|cs-&gt;card_ops
op_member_access_from_pointer
id|irq_func
c_func
(paren
id|cs-&gt;irq
comma
id|cs
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
)brace
r_void
id|__devinit
DECL|function|initisac
id|initisac
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_int
id|val
comma
id|eval
suffix:semicolon
id|val
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_STAR
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC STAR %x&quot;
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_MODE
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC MODE %x&quot;
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_ADF2
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC ADF2 %x&quot;
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_ISTA
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC ISTA %x&quot;
comma
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
l_int|0x01
)paren
(brace
id|eval
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_EXIR
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC EXIR %x&quot;
comma
id|eval
)paren
suffix:semicolon
)brace
multiline_comment|/* Disable all IRQ */
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|INIT_WORK
c_func
(paren
op_amp
id|cs-&gt;work
comma
id|isac_bh
comma
id|cs
)paren
suffix:semicolon
id|cs-&gt;setstack_d
op_assign
id|setstack_isac
suffix:semicolon
id|cs-&gt;DC_Send_Data
op_assign
id|isac_fill_fifo
suffix:semicolon
id|cs-&gt;DC_Close
op_assign
id|DC_Close_isac
suffix:semicolon
id|cs-&gt;dc.isac.mon_tx
op_assign
l_int|NULL
suffix:semicolon
id|cs-&gt;dc.isac.mon_rx
op_assign
l_int|NULL
suffix:semicolon
id|cs-&gt;dbusytimer.function
op_assign
(paren
r_void
op_star
)paren
id|dbusy_timer_handler
suffix:semicolon
id|cs-&gt;dbusytimer.data
op_assign
(paren
r_int
)paren
id|cs
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|cs-&gt;dbusytimer
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MASK
comma
l_int|0xff
)paren
suffix:semicolon
id|cs-&gt;dc.isac.mocr
op_assign
l_int|0xaa
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|HW_IOM1
comma
op_amp
id|cs-&gt;HW_Flags
)paren
)paren
(brace
multiline_comment|/* IOM 1 Mode */
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_ADF2
comma
l_int|0x0
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_SPCR
comma
l_int|0xa
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_ADF1
comma
l_int|0x2
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_STCR
comma
l_int|0x70
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MODE
comma
l_int|0xc9
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* IOM 2 Mode */
r_if
c_cond
(paren
op_logical_neg
id|cs-&gt;dc.isac.adf2
)paren
id|cs-&gt;dc.isac.adf2
op_assign
l_int|0x80
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_ADF2
comma
id|cs-&gt;dc.isac.adf2
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_SQXR
comma
l_int|0x2f
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_SPCR
comma
l_int|0x00
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_STCR
comma
l_int|0x70
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MODE
comma
l_int|0xc9
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_TIMR
comma
l_int|0x00
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_ADF1
comma
l_int|0x00
)paren
suffix:semicolon
)brace
id|ph_command
c_func
(paren
id|cs
comma
id|ISAC_CMD_RS
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MASK
comma
l_int|0x0
)paren
suffix:semicolon
id|val
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_CIR0
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC CIR0 %x&quot;
comma
id|val
)paren
suffix:semicolon
id|cs-&gt;dc.isac.ph_state
op_assign
(paren
id|val
op_rshift
l_int|2
)paren
op_amp
l_int|0xf
suffix:semicolon
id|sched_d_event
c_func
(paren
id|cs
comma
id|D_L1STATECHANGE
)paren
suffix:semicolon
multiline_comment|/* RESET Receiver and Transmitter */
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_CMDR
comma
l_int|0x41
)paren
suffix:semicolon
)brace
eof
