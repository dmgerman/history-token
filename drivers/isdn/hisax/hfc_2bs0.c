multiline_comment|/* $Id: hfc_2bs0.c,v 1.17.6.3 2001/09/23 22:24:47 kai Exp $&n; *&n; * specific routines for CCD&squot;s HFC 2BS0&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;hfc_2bs0.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
macro_line|#include &lt;linux/interrupt.h&gt;
r_static
r_inline
r_int
DECL|function|WaitForBusy
id|WaitForBusy
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_int
id|to
op_assign
l_int|130
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|u_char
id|val
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
op_logical_neg
(paren
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_STATUS
comma
l_int|0
)paren
op_amp
id|HFC_BUSY
)paren
op_logical_and
id|to
)paren
(brace
id|val
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA
comma
id|HFC_CIP
op_or
id|HFC_F2
op_or
(paren
id|cs-&gt;hw.hfc.cip
op_amp
l_int|3
)paren
)paren
suffix:semicolon
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
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|to
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: waitforBusy timeout&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
r_return
(paren
id|to
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|WaitNoBusy
id|WaitNoBusy
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_int
id|to
op_assign
l_int|125
suffix:semicolon
r_while
c_loop
(paren
(paren
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_STATUS
comma
l_int|0
)paren
op_amp
id|HFC_BUSY
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
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: waitforBusy timeout&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
r_return
(paren
id|to
)paren
suffix:semicolon
)brace
r_int
DECL|function|GetFreeFifoBytes
id|GetFreeFifoBytes
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
)paren
(brace
r_int
id|s
suffix:semicolon
r_if
c_cond
(paren
id|bcs-&gt;hw.hfc.f1
op_eq
id|bcs-&gt;hw.hfc.f2
)paren
r_return
(paren
id|bcs-&gt;cs-&gt;hw.hfc.fifosize
)paren
suffix:semicolon
id|s
op_assign
id|bcs-&gt;hw.hfc.send
(braket
id|bcs-&gt;hw.hfc.f1
)braket
op_minus
id|bcs-&gt;hw.hfc.send
(braket
id|bcs-&gt;hw.hfc.f2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|s
op_le
l_int|0
)paren
id|s
op_add_assign
id|bcs-&gt;cs-&gt;hw.hfc.fifosize
suffix:semicolon
id|s
op_assign
id|bcs-&gt;cs-&gt;hw.hfc.fifosize
op_minus
id|s
suffix:semicolon
r_return
(paren
id|s
)paren
suffix:semicolon
)brace
r_int
DECL|function|ReadZReg
id|ReadZReg
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
comma
id|u_char
id|reg
)paren
(brace
r_int
id|val
suffix:semicolon
id|WaitNoBusy
c_func
(paren
id|bcs-&gt;cs
)paren
suffix:semicolon
id|val
op_assign
l_int|256
op_star
id|bcs-&gt;cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|bcs-&gt;cs
comma
id|HFC_DATA
comma
id|reg
op_or
id|HFC_CIP
op_or
id|HFC_Z_HIGH
)paren
suffix:semicolon
id|WaitNoBusy
c_func
(paren
id|bcs-&gt;cs
)paren
suffix:semicolon
id|val
op_add_assign
id|bcs-&gt;cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|bcs-&gt;cs
comma
id|HFC_DATA
comma
id|reg
op_or
id|HFC_CIP
op_or
id|HFC_Z_LOW
)paren
suffix:semicolon
r_return
(paren
id|val
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|hfc_clear_fifo
id|hfc_clear_fifo
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
id|flags
suffix:semicolon
r_int
id|idx
comma
id|cnt
suffix:semicolon
r_int
id|rcnt
comma
id|z1
comma
id|z2
suffix:semicolon
id|u_char
id|cip
comma
id|f1
comma
id|f2
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
l_string|&quot;hfc_clear_fifo&quot;
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
id|cip
op_assign
id|HFC_CIP
op_or
id|HFC_F1
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cip
op_amp
l_int|0xc3
)paren
op_ne
(paren
id|cs-&gt;hw.hfc.cip
op_amp
l_int|0xc3
)paren
)paren
(brace
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|HFC_STATUS
comma
id|cip
comma
id|cip
)paren
suffix:semicolon
id|WaitForBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
id|WaitNoBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|f1
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA
comma
id|cip
)paren
suffix:semicolon
id|cip
op_assign
id|HFC_CIP
op_or
id|HFC_F2
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
suffix:semicolon
id|WaitNoBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|f2
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA
comma
id|cip
)paren
suffix:semicolon
id|z1
op_assign
id|ReadZReg
c_func
(paren
id|bcs
comma
id|HFC_Z1
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
)paren
suffix:semicolon
id|z2
op_assign
id|ReadZReg
c_func
(paren
id|bcs
comma
id|HFC_Z2
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
)paren
suffix:semicolon
id|cnt
op_assign
l_int|32
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
id|f1
op_ne
id|f2
)paren
op_logical_or
(paren
id|z1
op_ne
id|z2
)paren
)paren
op_logical_and
id|cnt
op_decrement
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
l_string|&quot;hfc clear %d f1(%d) f2(%d)&quot;
comma
id|bcs-&gt;channel
comma
id|f1
comma
id|f2
)paren
suffix:semicolon
id|rcnt
op_assign
id|z1
op_minus
id|z2
suffix:semicolon
r_if
c_cond
(paren
id|rcnt
OL
l_int|0
)paren
id|rcnt
op_add_assign
id|cs-&gt;hw.hfc.fifosize
suffix:semicolon
r_if
c_cond
(paren
id|rcnt
)paren
id|rcnt
op_increment
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
l_string|&quot;hfc clear %d z1(%x) z2(%x) cnt(%d)&quot;
comma
id|bcs-&gt;channel
comma
id|z1
comma
id|z2
comma
id|rcnt
)paren
suffix:semicolon
id|cip
op_assign
id|HFC_CIP
op_or
id|HFC_FIFO_OUT
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
suffix:semicolon
id|idx
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|idx
OL
id|rcnt
)paren
op_logical_and
id|WaitNoBusy
c_func
(paren
id|cs
)paren
)paren
(brace
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA_NODEB
comma
id|cip
)paren
suffix:semicolon
id|idx
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|f1
op_ne
id|f2
)paren
(brace
id|WaitNoBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA
comma
id|HFC_CIP
op_or
id|HFC_F2_INC
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
)paren
suffix:semicolon
id|WaitForBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
id|cip
op_assign
id|HFC_CIP
op_or
id|HFC_F1
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
suffix:semicolon
id|WaitNoBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|f1
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA
comma
id|cip
)paren
suffix:semicolon
id|cip
op_assign
id|HFC_CIP
op_or
id|HFC_F2
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
suffix:semicolon
id|WaitNoBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|f2
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA
comma
id|cip
)paren
suffix:semicolon
id|z1
op_assign
id|ReadZReg
c_func
(paren
id|bcs
comma
id|HFC_Z1
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
)paren
suffix:semicolon
id|z2
op_assign
id|ReadZReg
c_func
(paren
id|bcs
comma
id|HFC_Z2
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_struct
id|sk_buff
op_star
DECL|function|hfc_empty_fifo
id|hfc_empty_fifo
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
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|bcs-&gt;cs
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_int
id|chksum
suffix:semicolon
id|u_char
id|stat
comma
id|cip
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
l_string|&quot;hfc_empty_fifo&quot;
)paren
suffix:semicolon
id|idx
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|HSCX_BUFMAX
op_plus
l_int|3
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
l_string|&quot;hfc_empty_fifo: incoming packet too large&quot;
)paren
suffix:semicolon
id|cip
op_assign
id|HFC_CIP
op_or
id|HFC_FIFO_OUT
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|idx
op_increment
OL
id|count
)paren
op_logical_and
id|WaitNoBusy
c_func
(paren
id|cs
)paren
)paren
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA_NODEB
comma
id|cip
)paren
suffix:semicolon
id|WaitNoBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|stat
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA
comma
id|HFC_CIP
op_or
id|HFC_F2_INC
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
)paren
suffix:semicolon
id|WaitForBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|count
OL
l_int|4
)paren
op_logical_and
(paren
id|bcs-&gt;mode
op_ne
id|L1_MODE_TRANS
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
l_string|&quot;hfc_empty_fifo: incoming packet too small&quot;
)paren
suffix:semicolon
id|cip
op_assign
id|HFC_CIP
op_or
id|HFC_FIFO_OUT
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|idx
op_increment
OL
id|count
)paren
op_logical_and
id|WaitNoBusy
c_func
(paren
id|cs
)paren
)paren
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA_NODEB
comma
id|cip
)paren
suffix:semicolon
id|WaitNoBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|stat
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA
comma
id|HFC_CIP
op_or
id|HFC_F2_INC
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
)paren
suffix:semicolon
id|WaitForBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
macro_line|#ifdef ERROR_STATISTIC
id|bcs-&gt;err_inv
op_increment
suffix:semicolon
macro_line|#endif
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bcs-&gt;mode
op_eq
id|L1_MODE_TRANS
)paren
id|count
op_sub_assign
l_int|1
suffix:semicolon
r_else
id|count
op_sub_assign
l_int|3
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
l_string|&quot;HFC: receive out of memory&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|ptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
id|count
)paren
suffix:semicolon
id|idx
op_assign
l_int|0
suffix:semicolon
id|cip
op_assign
id|HFC_CIP
op_or
id|HFC_FIFO_OUT
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|idx
OL
id|count
)paren
op_logical_and
id|WaitNoBusy
c_func
(paren
id|cs
)paren
)paren
(brace
op_star
id|ptr
op_increment
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA_NODEB
comma
id|cip
)paren
suffix:semicolon
id|idx
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|idx
op_ne
id|count
)paren
(brace
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;RFIFO BUSY error&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HFC FIFO channel %d BUSY Error&bslash;n&quot;
comma
id|bcs-&gt;channel
)paren
suffix:semicolon
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bcs-&gt;mode
op_ne
id|L1_MODE_TRANS
)paren
(brace
id|WaitNoBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|stat
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA
comma
id|HFC_CIP
op_or
id|HFC_F2_INC
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
)paren
suffix:semicolon
id|WaitForBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bcs-&gt;mode
op_ne
id|L1_MODE_TRANS
)paren
(brace
id|WaitNoBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|chksum
op_assign
(paren
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA
comma
id|cip
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|WaitNoBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|chksum
op_add_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA
comma
id|cip
)paren
suffix:semicolon
id|WaitNoBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|stat
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA
comma
id|cip
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
l_string|&quot;hfc_empty_fifo %d chksum %x stat %x&quot;
comma
id|bcs-&gt;channel
comma
id|chksum
comma
id|stat
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
)paren
(brace
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;FIFO CRC error&quot;
)paren
suffix:semicolon
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef ERROR_STATISTIC
id|bcs-&gt;err_crc
op_increment
suffix:semicolon
macro_line|#endif
)brace
id|WaitNoBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|stat
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA
comma
id|HFC_CIP
op_or
id|HFC_F2_INC
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
)paren
suffix:semicolon
id|WaitForBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
id|skb
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|hfc_fill_fifo
id|hfc_fill_fifo
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
id|flags
suffix:semicolon
r_int
id|idx
comma
id|fcnt
suffix:semicolon
r_int
id|count
suffix:semicolon
r_int
id|z1
comma
id|z2
suffix:semicolon
id|u_char
id|cip
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
id|cip
op_assign
id|HFC_CIP
op_or
id|HFC_F1
op_or
id|HFC_SEND
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cip
op_amp
l_int|0xc3
)paren
op_ne
(paren
id|cs-&gt;hw.hfc.cip
op_amp
l_int|0xc3
)paren
)paren
(brace
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|HFC_STATUS
comma
id|cip
comma
id|cip
)paren
suffix:semicolon
id|WaitForBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
id|WaitNoBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bcs-&gt;mode
op_ne
id|L1_MODE_TRANS
)paren
(brace
id|bcs-&gt;hw.hfc.f1
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA
comma
id|cip
)paren
suffix:semicolon
id|cip
op_assign
id|HFC_CIP
op_or
id|HFC_F2
op_or
id|HFC_SEND
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
suffix:semicolon
id|WaitNoBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|bcs-&gt;hw.hfc.f2
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA
comma
id|cip
)paren
suffix:semicolon
id|bcs-&gt;hw.hfc.send
(braket
id|bcs-&gt;hw.hfc.f1
)braket
op_assign
id|ReadZReg
c_func
(paren
id|bcs
comma
id|HFC_Z1
op_or
id|HFC_SEND
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
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
l_string|&quot;hfc_fill_fifo %d f1(%d) f2(%d) z1(%x)&quot;
comma
id|bcs-&gt;channel
comma
id|bcs-&gt;hw.hfc.f1
comma
id|bcs-&gt;hw.hfc.f2
comma
id|bcs-&gt;hw.hfc.send
(braket
id|bcs-&gt;hw.hfc.f1
)braket
)paren
suffix:semicolon
id|fcnt
op_assign
id|bcs-&gt;hw.hfc.f1
op_minus
id|bcs-&gt;hw.hfc.f2
suffix:semicolon
r_if
c_cond
(paren
id|fcnt
OL
l_int|0
)paren
id|fcnt
op_add_assign
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|fcnt
OG
l_int|30
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
l_string|&quot;hfc_fill_fifo more as 30 frames&quot;
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|count
op_assign
id|GetFreeFifoBytes
c_func
(paren
id|bcs
)paren
suffix:semicolon
)brace
r_else
(brace
id|WaitForBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|z1
op_assign
id|ReadZReg
c_func
(paren
id|bcs
comma
id|HFC_Z1
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
)paren
suffix:semicolon
id|z2
op_assign
id|ReadZReg
c_func
(paren
id|bcs
comma
id|HFC_Z2
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
)paren
suffix:semicolon
id|count
op_assign
id|z1
op_minus
id|z2
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
id|count
op_add_assign
id|cs-&gt;hw.hfc.fifosize
suffix:semicolon
)brace
multiline_comment|/* L1_MODE_TRANS */
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
l_string|&quot;hfc_fill_fifo %d count(%ld/%d)&quot;
comma
id|bcs-&gt;channel
comma
id|bcs-&gt;tx_skb-&gt;len
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|bcs-&gt;tx_skb-&gt;len
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
l_string|&quot;hfc_fill_fifo no fifo mem&quot;
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cip
op_assign
id|HFC_CIP
op_or
id|HFC_FIFO_IN
op_or
id|HFC_SEND
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
suffix:semicolon
id|idx
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|idx
OL
id|bcs-&gt;tx_skb-&gt;len
)paren
op_logical_and
id|WaitNoBusy
c_func
(paren
id|cs
)paren
)paren
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA_NODEB
comma
id|cip
comma
id|bcs-&gt;tx_skb-&gt;data
(braket
id|idx
op_increment
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ne
id|bcs-&gt;tx_skb-&gt;len
)paren
(brace
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;FIFO Send BUSY error&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HFC S FIFO channel %d BUSY Error&bslash;n&quot;
comma
id|bcs-&gt;channel
)paren
suffix:semicolon
)brace
r_else
(brace
id|count
op_assign
id|bcs-&gt;tx_skb-&gt;len
suffix:semicolon
id|bcs-&gt;tx_cnt
op_sub_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|PACKET_NOACK
op_eq
id|bcs-&gt;tx_skb-&gt;pkt_type
)paren
id|count
op_assign
op_minus
l_int|1
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|bcs-&gt;cmpl_queue
comma
id|bcs-&gt;tx_skb
)paren
suffix:semicolon
id|sched_b_event
c_func
(paren
id|bcs
comma
id|B_CMPLREADY
)paren
suffix:semicolon
id|bcs-&gt;tx_skb
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|bcs-&gt;mode
op_ne
id|L1_MODE_TRANS
)paren
(brace
id|WaitForBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|WaitNoBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA
comma
id|HFC_CIP
op_or
id|HFC_F1_INC
op_or
id|HFC_SEND
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
)paren
suffix:semicolon
)brace
id|test_and_clear_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|bcs-&gt;Flag
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_void
DECL|function|main_irq_hfc
id|main_irq_hfc
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
)paren
(brace
r_int
id|flags
suffix:semicolon
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|bcs-&gt;cs
suffix:semicolon
r_int
id|z1
comma
id|z2
comma
id|rcnt
suffix:semicolon
id|u_char
id|f1
comma
id|f2
comma
id|cip
suffix:semicolon
r_int
id|receive
comma
id|transmit
comma
id|count
op_assign
l_int|5
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|Begin
suffix:colon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
id|cip
op_assign
id|HFC_CIP
op_or
id|HFC_F1
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cip
op_amp
l_int|0xc3
)paren
op_ne
(paren
id|cs-&gt;hw.hfc.cip
op_amp
l_int|0xc3
)paren
)paren
(brace
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|HFC_STATUS
comma
id|cip
comma
id|cip
)paren
suffix:semicolon
id|WaitForBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
id|WaitNoBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|receive
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bcs-&gt;mode
op_eq
id|L1_MODE_HDLC
)paren
(brace
id|f1
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA
comma
id|cip
)paren
suffix:semicolon
id|cip
op_assign
id|HFC_CIP
op_or
id|HFC_F2
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
suffix:semicolon
id|WaitNoBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|f2
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|HFC_DATA
comma
id|cip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f1
op_ne
id|f2
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
l_string|&quot;hfc rec %d f1(%d) f2(%d)&quot;
comma
id|bcs-&gt;channel
comma
id|f1
comma
id|f2
)paren
suffix:semicolon
id|receive
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|receive
op_logical_or
(paren
id|bcs-&gt;mode
op_eq
id|L1_MODE_TRANS
)paren
)paren
(brace
id|WaitForBusy
c_func
(paren
id|cs
)paren
suffix:semicolon
id|z1
op_assign
id|ReadZReg
c_func
(paren
id|bcs
comma
id|HFC_Z1
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
)paren
suffix:semicolon
id|z2
op_assign
id|ReadZReg
c_func
(paren
id|bcs
comma
id|HFC_Z2
op_or
id|HFC_REC
op_or
id|HFC_CHANNEL
c_func
(paren
id|bcs-&gt;channel
)paren
)paren
suffix:semicolon
id|rcnt
op_assign
id|z1
op_minus
id|z2
suffix:semicolon
r_if
c_cond
(paren
id|rcnt
OL
l_int|0
)paren
id|rcnt
op_add_assign
id|cs-&gt;hw.hfc.fifosize
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bcs-&gt;mode
op_eq
id|L1_MODE_HDLC
)paren
op_logical_or
(paren
id|rcnt
)paren
)paren
(brace
id|rcnt
op_increment
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
l_string|&quot;hfc rec %d z1(%x) z2(%x) cnt(%d)&quot;
comma
id|bcs-&gt;channel
comma
id|z1
comma
id|z2
comma
id|rcnt
)paren
suffix:semicolon
multiline_comment|/*              sti(); */
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|hfc_empty_fifo
c_func
(paren
id|bcs
comma
id|rcnt
)paren
)paren
)paren
(brace
id|skb_queue_tail
c_func
(paren
op_amp
id|bcs-&gt;rqueue
comma
id|skb
)paren
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
id|receive
op_assign
l_int|1
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
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
id|bcs-&gt;tx_skb
)paren
(brace
id|transmit
op_assign
l_int|1
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
id|hfc_fill_fifo
c_func
(paren
id|bcs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|bcs-&gt;Flag
)paren
)paren
id|transmit
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
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
id|transmit
op_assign
l_int|1
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
id|hfc_fill_fifo
c_func
(paren
id|bcs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|bcs-&gt;Flag
)paren
)paren
id|transmit
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|transmit
op_assign
l_int|0
suffix:semicolon
id|sched_b_event
c_func
(paren
id|bcs
comma
id|B_XMTBUFREADY
)paren
suffix:semicolon
)brace
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|receive
op_logical_or
id|transmit
)paren
op_logical_and
id|count
)paren
r_goto
id|Begin
suffix:semicolon
r_return
suffix:semicolon
)brace
r_void
DECL|function|mode_hfc
id|mode_hfc
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
comma
r_int
id|mode
comma
r_int
id|bc
)paren
(brace
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|bcs-&gt;cs
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
l_string|&quot;HFC 2BS0 mode %d bchan %d/%d&quot;
comma
id|mode
comma
id|bc
comma
id|bcs-&gt;channel
)paren
suffix:semicolon
id|bcs-&gt;mode
op_assign
id|mode
suffix:semicolon
id|bcs-&gt;channel
op_assign
id|bc
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
(paren
id|L1_MODE_NULL
)paren
suffix:colon
r_if
c_cond
(paren
id|bc
)paren
(brace
id|cs-&gt;hw.hfc.ctmt
op_and_assign
op_complement
l_int|1
suffix:semicolon
id|cs-&gt;hw.hfc.isac_spcr
op_and_assign
op_complement
l_int|0x03
suffix:semicolon
)brace
r_else
(brace
id|cs-&gt;hw.hfc.ctmt
op_and_assign
op_complement
l_int|2
suffix:semicolon
id|cs-&gt;hw.hfc.isac_spcr
op_and_assign
op_complement
l_int|0x0c
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
(paren
id|L1_MODE_TRANS
)paren
suffix:colon
id|cs-&gt;hw.hfc.ctmt
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|bc
)paren
suffix:semicolon
multiline_comment|/* set HDLC mode */
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|HFC_STATUS
comma
id|cs-&gt;hw.hfc.ctmt
comma
id|cs-&gt;hw.hfc.ctmt
)paren
suffix:semicolon
id|hfc_clear_fifo
c_func
(paren
id|bcs
)paren
suffix:semicolon
multiline_comment|/* complete fifo clear */
r_if
c_cond
(paren
id|bc
)paren
(brace
id|cs-&gt;hw.hfc.ctmt
op_or_assign
l_int|1
suffix:semicolon
id|cs-&gt;hw.hfc.isac_spcr
op_and_assign
op_complement
l_int|0x03
suffix:semicolon
id|cs-&gt;hw.hfc.isac_spcr
op_or_assign
l_int|0x02
suffix:semicolon
)brace
r_else
(brace
id|cs-&gt;hw.hfc.ctmt
op_or_assign
l_int|2
suffix:semicolon
id|cs-&gt;hw.hfc.isac_spcr
op_and_assign
op_complement
l_int|0x0c
suffix:semicolon
id|cs-&gt;hw.hfc.isac_spcr
op_or_assign
l_int|0x08
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
(paren
id|L1_MODE_HDLC
)paren
suffix:colon
r_if
c_cond
(paren
id|bc
)paren
(brace
id|cs-&gt;hw.hfc.ctmt
op_and_assign
op_complement
l_int|1
suffix:semicolon
id|cs-&gt;hw.hfc.isac_spcr
op_and_assign
op_complement
l_int|0x03
suffix:semicolon
id|cs-&gt;hw.hfc.isac_spcr
op_or_assign
l_int|0x02
suffix:semicolon
)brace
r_else
(brace
id|cs-&gt;hw.hfc.ctmt
op_and_assign
op_complement
l_int|2
suffix:semicolon
id|cs-&gt;hw.hfc.isac_spcr
op_and_assign
op_complement
l_int|0x0c
suffix:semicolon
id|cs-&gt;hw.hfc.isac_spcr
op_or_assign
l_int|0x08
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|HFC_STATUS
comma
id|cs-&gt;hw.hfc.ctmt
comma
id|cs-&gt;hw.hfc.ctmt
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|writeisac
c_func
(paren
id|cs
comma
id|ISAC_SPCR
comma
id|cs-&gt;hw.hfc.isac_spcr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_eq
id|L1_MODE_HDLC
)paren
id|hfc_clear_fifo
c_func
(paren
id|bcs
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|hfc_l2l1
id|hfc_l2l1
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
id|sk_buff
op_star
id|skb
op_assign
id|arg
suffix:semicolon
r_int
id|flags
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
id|st-&gt;l1.bcs-&gt;tx_skb
)paren
(brace
id|skb_queue_tail
c_func
(paren
op_amp
id|st-&gt;l1.bcs-&gt;squeue
comma
id|skb
)paren
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
id|st-&gt;l1.bcs-&gt;tx_skb
op_assign
id|skb
suffix:semicolon
id|test_and_set_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|st-&gt;l1.bcs-&gt;Flag
)paren
suffix:semicolon
id|st-&gt;l1.bcs-&gt;cs
op_member_access_from_pointer
id|BC_Send_Data
c_func
(paren
id|st-&gt;l1.bcs
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
(paren
id|PH_PULL
op_or
id|INDICATION
)paren
suffix:colon
r_if
c_cond
(paren
id|st-&gt;l1.bcs-&gt;tx_skb
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;hfc_l2l1: this shouldn&squot;t happen&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
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
id|test_and_set_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|st-&gt;l1.bcs-&gt;Flag
)paren
suffix:semicolon
id|st-&gt;l1.bcs-&gt;tx_skb
op_assign
id|skb
suffix:semicolon
id|st-&gt;l1.bcs-&gt;cs
op_member_access_from_pointer
id|BC_Send_Data
c_func
(paren
id|st-&gt;l1.bcs
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
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
r_if
c_cond
(paren
op_logical_neg
id|st-&gt;l1.bcs-&gt;tx_skb
)paren
(brace
id|test_and_clear_bit
c_func
(paren
id|FLG_L1_PULL_REQ
comma
op_amp
id|st-&gt;l1.Flags
)paren
suffix:semicolon
id|L1L2
c_func
(paren
id|st
comma
id|PH_PULL
op_or
id|CONFIRM
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
id|test_and_set_bit
c_func
(paren
id|FLG_L1_PULL_REQ
comma
op_amp
id|st-&gt;l1.Flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|PH_ACTIVATE
op_or
id|REQUEST
)paren
suffix:colon
id|test_and_set_bit
c_func
(paren
id|BC_FLG_ACTIV
comma
op_amp
id|st-&gt;l1.bcs-&gt;Flag
)paren
suffix:semicolon
id|mode_hfc
c_func
(paren
id|st-&gt;l1.bcs
comma
id|st-&gt;l1.mode
comma
id|st-&gt;l1.bc
)paren
suffix:semicolon
id|l1_msg_b
c_func
(paren
id|st
comma
id|pr
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|PH_DEACTIVATE
op_or
id|REQUEST
)paren
suffix:colon
id|l1_msg_b
c_func
(paren
id|st
comma
id|pr
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|PH_DEACTIVATE
op_or
id|CONFIRM
)paren
suffix:colon
id|test_and_clear_bit
c_func
(paren
id|BC_FLG_ACTIV
comma
op_amp
id|st-&gt;l1.bcs-&gt;Flag
)paren
suffix:semicolon
id|test_and_clear_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|st-&gt;l1.bcs-&gt;Flag
)paren
suffix:semicolon
id|mode_hfc
c_func
(paren
id|st-&gt;l1.bcs
comma
l_int|0
comma
id|st-&gt;l1.bc
)paren
suffix:semicolon
id|L1L2
c_func
(paren
id|st
comma
id|PH_DEACTIVATE
op_or
id|CONFIRM
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_void
DECL|function|close_hfcstate
id|close_hfcstate
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
)paren
(brace
id|mode_hfc
c_func
(paren
id|bcs
comma
l_int|0
comma
id|bcs-&gt;channel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|BC_FLG_INIT
comma
op_amp
id|bcs-&gt;Flag
)paren
)paren
(brace
id|skb_queue_purge
c_func
(paren
op_amp
id|bcs-&gt;rqueue
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|bcs-&gt;squeue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bcs-&gt;tx_skb
)paren
(brace
id|dev_kfree_skb_any
c_func
(paren
id|bcs-&gt;tx_skb
)paren
suffix:semicolon
id|bcs-&gt;tx_skb
op_assign
l_int|NULL
suffix:semicolon
id|test_and_clear_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|bcs-&gt;Flag
)paren
suffix:semicolon
)brace
)brace
id|test_and_clear_bit
c_func
(paren
id|BC_FLG_INIT
comma
op_amp
id|bcs-&gt;Flag
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|open_hfcstate
id|open_hfcstate
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_struct
id|BCState
op_star
id|bcs
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|BC_FLG_INIT
comma
op_amp
id|bcs-&gt;Flag
)paren
)paren
(brace
id|skb_queue_head_init
c_func
(paren
op_amp
id|bcs-&gt;rqueue
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|bcs-&gt;squeue
)paren
suffix:semicolon
)brace
id|bcs-&gt;tx_skb
op_assign
l_int|NULL
suffix:semicolon
id|test_and_clear_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|bcs-&gt;Flag
)paren
suffix:semicolon
id|bcs-&gt;event
op_assign
l_int|0
suffix:semicolon
id|bcs-&gt;tx_cnt
op_assign
l_int|0
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_int
DECL|function|setstack_hfc
id|setstack_hfc
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_struct
id|BCState
op_star
id|bcs
)paren
(brace
id|bcs-&gt;channel
op_assign
id|st-&gt;l1.bc
suffix:semicolon
r_if
c_cond
(paren
id|open_hfcstate
c_func
(paren
id|st-&gt;l1.hardware
comma
id|bcs
)paren
)paren
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
id|st-&gt;l1.bcs
op_assign
id|bcs
suffix:semicolon
id|st-&gt;l1.l2l1
op_assign
id|hfc_l2l1
suffix:semicolon
id|setstack_manager
c_func
(paren
id|st
)paren
suffix:semicolon
id|bcs-&gt;st
op_assign
id|st
suffix:semicolon
id|setstack_l1_B
c_func
(paren
id|st
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|init_send
id|init_send
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bcs-&gt;hw.hfc.send
op_assign
id|kmalloc
c_func
(paren
l_int|32
op_star
r_sizeof
(paren
r_int
r_int
)paren
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: No memory for hfc.send&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32
suffix:semicolon
id|i
op_increment
)paren
id|bcs-&gt;hw.hfc.send
(braket
id|i
)braket
op_assign
l_int|0x1fff
suffix:semicolon
)brace
r_void
id|__init
DECL|function|inithfc
id|inithfc
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|init_send
c_func
(paren
op_amp
id|cs-&gt;bcs
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|init_send
c_func
(paren
op_amp
id|cs-&gt;bcs
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|cs-&gt;BC_Send_Data
op_assign
op_amp
id|hfc_fill_fifo
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|0
)braket
dot
id|BC_SetStack
op_assign
id|setstack_hfc
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|1
)braket
dot
id|BC_SetStack
op_assign
id|setstack_hfc
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|0
)braket
dot
id|BC_Close
op_assign
id|close_hfcstate
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|1
)braket
dot
id|BC_Close
op_assign
id|close_hfcstate
suffix:semicolon
id|mode_hfc
c_func
(paren
id|cs-&gt;bcs
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|mode_hfc
c_func
(paren
id|cs-&gt;bcs
op_plus
l_int|1
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|releasehfc
id|releasehfc
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
id|cs-&gt;bcs
(braket
l_int|0
)braket
dot
id|hw.hfc.send
)paren
(brace
id|kfree
c_func
(paren
id|cs-&gt;bcs
(braket
l_int|0
)braket
dot
id|hw.hfc.send
)paren
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|0
)braket
dot
id|hw.hfc.send
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cs-&gt;bcs
(braket
l_int|1
)braket
dot
id|hw.hfc.send
)paren
(brace
id|kfree
c_func
(paren
id|cs-&gt;bcs
(braket
l_int|1
)braket
dot
id|hw.hfc.send
)paren
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|1
)braket
dot
id|hw.hfc.send
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
eof
