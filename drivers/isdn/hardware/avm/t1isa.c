multiline_comment|/* $Id: t1isa.c,v 1.16.6.7 2001/09/23 22:24:34 kai Exp $&n; * &n; * Module for AVM T1 HEMA-card.&n; * &n; * Copyright 1999 by Carsten Paeth &lt;calle@calle.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/capi.h&gt;
macro_line|#include &lt;linux/kernelcapi.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/isdn/capicmd.h&gt;
macro_line|#include &lt;linux/isdn/capiutil.h&gt;
macro_line|#include &lt;linux/isdn/capilli.h&gt;
macro_line|#include &quot;avmcard.h&quot;
DECL|variable|revision
r_static
r_char
op_star
id|revision
op_assign
l_string|&quot;$Revision: 1.16.6.7 $&quot;
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------- */
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;CAPI4Linux: Driver for AVM T1 HEMA ISA card&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Carsten Paeth&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------- */
DECL|variable|di
r_static
r_struct
id|capi_driver_interface
op_star
id|di
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------- */
DECL|variable|hema_irq_table
r_static
r_int
id|hema_irq_table
(braket
l_int|16
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0x80
comma
multiline_comment|/* irq 3 */
l_int|0
comma
l_int|0x90
comma
multiline_comment|/* irq 5 */
l_int|0
comma
l_int|0xA0
comma
multiline_comment|/* irq 7 */
l_int|0
comma
l_int|0xB0
comma
multiline_comment|/* irq 9 */
l_int|0xC0
comma
multiline_comment|/* irq 10 */
l_int|0xD0
comma
multiline_comment|/* irq 11 */
l_int|0xE0
comma
multiline_comment|/* irq 12 */
l_int|0
comma
l_int|0
comma
l_int|0xF0
comma
multiline_comment|/* irq 15 */
)brace
suffix:semicolon
DECL|function|t1_detectandinit
r_static
r_int
id|t1_detectandinit
c_func
(paren
r_int
r_int
id|base
comma
r_int
id|irq
comma
r_int
id|cardnr
)paren
(brace
r_int
r_char
id|cregs
(braket
l_int|8
)braket
suffix:semicolon
r_int
r_char
id|reverse_cardnr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_char
id|dummy
suffix:semicolon
r_int
id|i
suffix:semicolon
id|reverse_cardnr
op_assign
(paren
(paren
id|cardnr
op_amp
l_int|0x01
)paren
op_lshift
l_int|3
)paren
op_or
(paren
(paren
id|cardnr
op_amp
l_int|0x02
)paren
op_lshift
l_int|1
)paren
op_or
(paren
(paren
id|cardnr
op_amp
l_int|0x04
)paren
op_rshift
l_int|1
)paren
op_or
(paren
(paren
id|cardnr
op_amp
l_int|0x08
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|cregs
(braket
l_int|0
)braket
op_assign
(paren
id|HEMA_VERSION_ID
op_lshift
l_int|4
)paren
op_or
(paren
id|reverse_cardnr
op_amp
l_int|0xf
)paren
suffix:semicolon
id|cregs
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* fast &amp; slow link connected to CON1 */
id|cregs
(braket
l_int|2
)braket
op_assign
l_int|0x05
suffix:semicolon
multiline_comment|/* fast link 20MBit, slow link 20 MBit */
id|cregs
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|cregs
(braket
l_int|4
)braket
op_assign
l_int|0x11
suffix:semicolon
multiline_comment|/* zero wait state */
id|cregs
(braket
l_int|5
)braket
op_assign
id|hema_irq_table
(braket
id|irq
op_amp
l_int|0xf
)braket
suffix:semicolon
id|cregs
(braket
l_int|6
)braket
op_assign
l_int|0
suffix:semicolon
id|cregs
(braket
l_int|7
)braket
op_assign
l_int|0
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
multiline_comment|/* board reset */
id|t1outp
c_func
(paren
id|base
comma
id|T1_RESETBOARD
comma
l_int|0xf
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|dummy
op_assign
id|t1inp
c_func
(paren
id|base
comma
id|T1_FASTLINK
op_plus
id|T1_OUTSTAT
)paren
suffix:semicolon
multiline_comment|/* first read */
multiline_comment|/* write config */
id|dummy
op_assign
(paren
id|base
op_rshift
l_int|4
)paren
op_amp
l_int|0xff
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
l_int|0xf
suffix:semicolon
id|i
op_increment
)paren
id|t1outp
c_func
(paren
id|base
comma
id|i
comma
id|dummy
)paren
suffix:semicolon
id|t1outp
c_func
(paren
id|base
comma
id|HEMA_PAL_ID
op_amp
l_int|0xf
comma
id|dummy
)paren
suffix:semicolon
id|t1outp
c_func
(paren
id|base
comma
id|HEMA_PAL_ID
op_rshift
l_int|4
comma
id|cregs
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|7
suffix:semicolon
id|i
op_increment
)paren
(brace
id|t1outp
c_func
(paren
id|base
comma
l_int|0
comma
id|cregs
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|t1outp
c_func
(paren
id|base
comma
(paren
(paren
id|base
op_rshift
l_int|4
)paren
)paren
op_amp
l_int|0x3
comma
id|cregs
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|t1outp
c_func
(paren
id|base
comma
id|T1_FASTLINK
op_plus
id|T1_RESETLINK
comma
l_int|0
)paren
suffix:semicolon
id|t1outp
c_func
(paren
id|base
comma
id|T1_SLOWLINK
op_plus
id|T1_RESETLINK
comma
l_int|0
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|t1outp
c_func
(paren
id|base
comma
id|T1_FASTLINK
op_plus
id|T1_RESETLINK
comma
l_int|1
)paren
suffix:semicolon
id|t1outp
c_func
(paren
id|base
comma
id|T1_SLOWLINK
op_plus
id|T1_RESETLINK
comma
l_int|1
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|t1outp
c_func
(paren
id|base
comma
id|T1_FASTLINK
op_plus
id|T1_RESETLINK
comma
l_int|0
)paren
suffix:semicolon
id|t1outp
c_func
(paren
id|base
comma
id|T1_SLOWLINK
op_plus
id|T1_RESETLINK
comma
l_int|0
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|t1outp
c_func
(paren
id|base
comma
id|T1_FASTLINK
op_plus
id|T1_ANALYSE
comma
l_int|0
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|t1outp
c_func
(paren
id|base
comma
id|T1_SLOWLINK
op_plus
id|T1_ANALYSE
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t1inp
c_func
(paren
id|base
comma
id|T1_FASTLINK
op_plus
id|T1_OUTSTAT
)paren
op_ne
l_int|0x1
)paren
multiline_comment|/* tx empty */
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|t1inp
c_func
(paren
id|base
comma
id|T1_FASTLINK
op_plus
id|T1_INSTAT
)paren
op_ne
l_int|0x0
)paren
multiline_comment|/* rx empty */
r_return
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|t1inp
c_func
(paren
id|base
comma
id|T1_FASTLINK
op_plus
id|T1_IRQENABLE
)paren
op_ne
l_int|0x0
)paren
r_return
l_int|3
suffix:semicolon
r_if
c_cond
(paren
(paren
id|t1inp
c_func
(paren
id|base
comma
id|T1_FASTLINK
op_plus
id|T1_FIFOSTAT
)paren
op_amp
l_int|0xf0
)paren
op_ne
l_int|0x70
)paren
r_return
l_int|4
suffix:semicolon
r_if
c_cond
(paren
(paren
id|t1inp
c_func
(paren
id|base
comma
id|T1_FASTLINK
op_plus
id|T1_IRQMASTER
)paren
op_amp
l_int|0x0e
)paren
op_ne
l_int|0
)paren
r_return
l_int|5
suffix:semicolon
r_if
c_cond
(paren
(paren
id|t1inp
c_func
(paren
id|base
comma
id|T1_FASTLINK
op_plus
id|T1_IDENT
)paren
op_amp
l_int|0x7d
)paren
op_ne
l_int|1
)paren
r_return
l_int|6
suffix:semicolon
r_if
c_cond
(paren
id|t1inp
c_func
(paren
id|base
comma
id|T1_SLOWLINK
op_plus
id|T1_OUTSTAT
)paren
op_ne
l_int|0x1
)paren
multiline_comment|/* tx empty */
r_return
l_int|7
suffix:semicolon
r_if
c_cond
(paren
(paren
id|t1inp
c_func
(paren
id|base
comma
id|T1_SLOWLINK
op_plus
id|T1_IRQMASTER
)paren
op_amp
l_int|0x0e
)paren
op_ne
l_int|0
)paren
r_return
l_int|8
suffix:semicolon
r_if
c_cond
(paren
(paren
id|t1inp
c_func
(paren
id|base
comma
id|T1_SLOWLINK
op_plus
id|T1_IDENT
)paren
op_amp
l_int|0x7d
)paren
op_ne
l_int|0
)paren
r_return
l_int|9
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|t1isa_interrupt
r_static
r_void
id|t1isa_interrupt
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
id|avmcard
op_star
id|card
op_assign
id|devptr
suffix:semicolon
id|avmctrl_info
op_star
id|cinfo
op_assign
op_amp
id|card-&gt;ctrlinfo
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|capi_ctr
op_star
id|ctrl
op_assign
id|cinfo-&gt;capi_ctrl
suffix:semicolon
r_int
r_char
id|b1cmd
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|ApplId
suffix:semicolon
r_int
id|MsgLen
suffix:semicolon
r_int
id|DataB3Len
suffix:semicolon
r_int
id|NCCI
suffix:semicolon
r_int
id|WindowSize
suffix:semicolon
r_while
c_loop
(paren
id|b1_rx_full
c_func
(paren
id|card-&gt;port
)paren
)paren
(brace
id|b1cmd
op_assign
id|b1_get_byte
c_func
(paren
id|card-&gt;port
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|b1cmd
)paren
(brace
r_case
id|RECEIVE_DATA_B3_IND
suffix:colon
id|ApplId
op_assign
(paren
r_int
)paren
id|b1_get_word
c_func
(paren
id|card-&gt;port
)paren
suffix:semicolon
id|MsgLen
op_assign
id|t1_get_slice
c_func
(paren
id|card-&gt;port
comma
id|card-&gt;msgbuf
)paren
suffix:semicolon
id|DataB3Len
op_assign
id|t1_get_slice
c_func
(paren
id|card-&gt;port
comma
id|card-&gt;databuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|MsgLen
OL
l_int|30
)paren
(brace
multiline_comment|/* not CAPI 64Bit */
id|memset
c_func
(paren
id|card-&gt;msgbuf
op_plus
id|MsgLen
comma
l_int|0
comma
l_int|30
op_minus
id|MsgLen
)paren
suffix:semicolon
id|MsgLen
op_assign
l_int|30
suffix:semicolon
id|CAPIMSG_SETLEN
c_func
(paren
id|card-&gt;msgbuf
comma
l_int|30
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|DataB3Len
op_plus
id|MsgLen
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: incoming packet dropped&bslash;n&quot;
comma
id|card-&gt;name
)paren
suffix:semicolon
)brace
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
id|MsgLen
)paren
comma
id|card-&gt;msgbuf
comma
id|MsgLen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
id|DataB3Len
)paren
comma
id|card-&gt;databuf
comma
id|DataB3Len
)paren
suffix:semicolon
id|ctrl
op_member_access_from_pointer
id|handle_capimsg
c_func
(paren
id|ctrl
comma
id|ApplId
comma
id|skb
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|RECEIVE_MESSAGE
suffix:colon
id|ApplId
op_assign
(paren
r_int
)paren
id|b1_get_word
c_func
(paren
id|card-&gt;port
)paren
suffix:semicolon
id|MsgLen
op_assign
id|t1_get_slice
c_func
(paren
id|card-&gt;port
comma
id|card-&gt;msgbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|MsgLen
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: incoming packet dropped&bslash;n&quot;
comma
id|card-&gt;name
)paren
suffix:semicolon
)brace
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
id|MsgLen
)paren
comma
id|card-&gt;msgbuf
comma
id|MsgLen
)paren
suffix:semicolon
id|ctrl
op_member_access_from_pointer
id|handle_capimsg
c_func
(paren
id|ctrl
comma
id|ApplId
comma
id|skb
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|RECEIVE_NEW_NCCI
suffix:colon
id|ApplId
op_assign
id|b1_get_word
c_func
(paren
id|card-&gt;port
)paren
suffix:semicolon
id|NCCI
op_assign
id|b1_get_word
c_func
(paren
id|card-&gt;port
)paren
suffix:semicolon
id|WindowSize
op_assign
id|b1_get_word
c_func
(paren
id|card-&gt;port
)paren
suffix:semicolon
id|ctrl
op_member_access_from_pointer
id|new_ncci
c_func
(paren
id|ctrl
comma
id|ApplId
comma
id|NCCI
comma
id|WindowSize
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RECEIVE_FREE_NCCI
suffix:colon
id|ApplId
op_assign
id|b1_get_word
c_func
(paren
id|card-&gt;port
)paren
suffix:semicolon
id|NCCI
op_assign
id|b1_get_word
c_func
(paren
id|card-&gt;port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|NCCI
op_ne
l_int|0xffffffff
)paren
id|ctrl
op_member_access_from_pointer
id|free_ncci
c_func
(paren
id|ctrl
comma
id|ApplId
comma
id|NCCI
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RECEIVE_START
suffix:colon
id|b1_put_byte
c_func
(paren
id|card-&gt;port
comma
id|SEND_POLLACK
)paren
suffix:semicolon
id|ctrl
op_member_access_from_pointer
id|resume_output
c_func
(paren
id|ctrl
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RECEIVE_STOP
suffix:colon
id|ctrl
op_member_access_from_pointer
id|suspend_output
c_func
(paren
id|ctrl
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RECEIVE_INIT
suffix:colon
id|cinfo-&gt;versionlen
op_assign
id|t1_get_slice
c_func
(paren
id|card-&gt;port
comma
id|cinfo-&gt;versionbuf
)paren
suffix:semicolon
id|b1_parse_version
c_func
(paren
id|cinfo
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: %s-card (%s) now active&bslash;n&quot;
comma
id|card-&gt;name
comma
id|cinfo-&gt;version
(braket
id|VER_CARDTYPE
)braket
comma
id|cinfo-&gt;version
(braket
id|VER_DRIVER
)braket
)paren
suffix:semicolon
id|ctrl
op_member_access_from_pointer
id|ready
c_func
(paren
id|ctrl
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RECEIVE_TASK_READY
suffix:colon
id|ApplId
op_assign
(paren
r_int
)paren
id|b1_get_word
c_func
(paren
id|card-&gt;port
)paren
suffix:semicolon
id|MsgLen
op_assign
id|t1_get_slice
c_func
(paren
id|card-&gt;port
comma
id|card-&gt;msgbuf
)paren
suffix:semicolon
id|card-&gt;msgbuf
(braket
id|MsgLen
)braket
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|MsgLen
OG
l_int|0
op_logical_and
(paren
id|card-&gt;msgbuf
(braket
id|MsgLen
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_or
id|card-&gt;msgbuf
(braket
id|MsgLen
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;r&squot;
)paren
)paren
(brace
id|card-&gt;msgbuf
(braket
id|MsgLen
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|MsgLen
op_decrement
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: task %d &bslash;&quot;%s&bslash;&quot; ready.&bslash;n&quot;
comma
id|card-&gt;name
comma
id|ApplId
comma
id|card-&gt;msgbuf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RECEIVE_DEBUGMSG
suffix:colon
id|MsgLen
op_assign
id|t1_get_slice
c_func
(paren
id|card-&gt;port
comma
id|card-&gt;msgbuf
)paren
suffix:semicolon
id|card-&gt;msgbuf
(braket
id|MsgLen
)braket
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|MsgLen
OG
l_int|0
op_logical_and
(paren
id|card-&gt;msgbuf
(braket
id|MsgLen
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_or
id|card-&gt;msgbuf
(braket
id|MsgLen
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;r&squot;
)paren
)paren
(brace
id|card-&gt;msgbuf
(braket
id|MsgLen
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|MsgLen
op_decrement
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: DEBUG: %s&bslash;n&quot;
comma
id|card-&gt;name
comma
id|card-&gt;msgbuf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xff
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: card reseted ?&bslash;n&quot;
comma
id|card-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: b1_interrupt: 0x%x ???&bslash;n&quot;
comma
id|card-&gt;name
comma
id|b1cmd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|t1isa_load_firmware
r_static
r_int
id|t1isa_load_firmware
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
comma
id|capiloaddata
op_star
id|data
)paren
(brace
id|avmctrl_info
op_star
id|cinfo
op_assign
(paren
id|avmctrl_info
op_star
)paren
(paren
id|ctrl-&gt;driverdata
)paren
suffix:semicolon
id|avmcard
op_star
id|card
op_assign
id|cinfo-&gt;card
suffix:semicolon
r_int
r_int
id|port
op_assign
id|card-&gt;port
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|t1_disable_irq
c_func
(paren
id|port
)paren
suffix:semicolon
id|b1_reset
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|b1_load_t4file
c_func
(paren
id|card
comma
op_amp
id|data-&gt;firmware
)paren
)paren
)paren
(brace
id|b1_reset
c_func
(paren
id|port
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to load t4file!!&bslash;n&quot;
comma
id|card-&gt;name
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data-&gt;configuration.len
OG
l_int|0
op_logical_and
id|data-&gt;configuration.data
)paren
(brace
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|b1_load_config
c_func
(paren
id|card
comma
op_amp
id|data-&gt;configuration
)paren
)paren
)paren
(brace
id|b1_reset
c_func
(paren
id|port
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to load config!!&bslash;n&quot;
comma
id|card-&gt;name
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|b1_loaded
c_func
(paren
id|card
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to load t4file.&bslash;n&quot;
comma
id|card-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EIO
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
id|b1_setinterrupt
c_func
(paren
id|port
comma
id|card-&gt;irq
comma
id|card-&gt;cardtype
)paren
suffix:semicolon
id|b1_put_byte
c_func
(paren
id|port
comma
id|SEND_INIT
)paren
suffix:semicolon
id|b1_put_word
c_func
(paren
id|port
comma
id|CAPI_MAXAPPL
)paren
suffix:semicolon
id|b1_put_word
c_func
(paren
id|port
comma
id|AVM_NCCI_PER_CHANNEL
op_star
l_int|30
)paren
suffix:semicolon
id|b1_put_word
c_func
(paren
id|port
comma
id|ctrl-&gt;cnr
op_minus
l_int|1
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|t1isa_reset_ctr
r_void
id|t1isa_reset_ctr
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
)paren
(brace
id|avmctrl_info
op_star
id|cinfo
op_assign
(paren
id|avmctrl_info
op_star
)paren
(paren
id|ctrl-&gt;driverdata
)paren
suffix:semicolon
id|avmcard
op_star
id|card
op_assign
id|cinfo-&gt;card
suffix:semicolon
r_int
r_int
id|port
op_assign
id|card-&gt;port
suffix:semicolon
id|t1_disable_irq
c_func
(paren
id|port
)paren
suffix:semicolon
id|b1_reset
c_func
(paren
id|port
)paren
suffix:semicolon
id|b1_reset
c_func
(paren
id|port
)paren
suffix:semicolon
id|memset
c_func
(paren
id|cinfo-&gt;version
comma
l_int|0
comma
r_sizeof
(paren
id|cinfo-&gt;version
)paren
)paren
suffix:semicolon
id|ctrl
op_member_access_from_pointer
id|reseted
c_func
(paren
id|ctrl
)paren
suffix:semicolon
)brace
DECL|function|t1isa_remove_ctr
r_static
r_void
id|t1isa_remove_ctr
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
)paren
(brace
id|avmctrl_info
op_star
id|cinfo
op_assign
(paren
id|avmctrl_info
op_star
)paren
(paren
id|ctrl-&gt;driverdata
)paren
suffix:semicolon
id|avmcard
op_star
id|card
op_assign
id|cinfo-&gt;card
suffix:semicolon
r_int
r_int
id|port
op_assign
id|card-&gt;port
suffix:semicolon
id|t1_disable_irq
c_func
(paren
id|port
)paren
suffix:semicolon
id|b1_reset
c_func
(paren
id|port
)paren
suffix:semicolon
id|b1_reset
c_func
(paren
id|port
)paren
suffix:semicolon
id|t1_reset
c_func
(paren
id|port
)paren
suffix:semicolon
id|di
op_member_access_from_pointer
id|detach_ctr
c_func
(paren
id|ctrl
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|card-&gt;irq
comma
id|card
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|card-&gt;port
comma
id|AVMB1_PORTLEN
)paren
suffix:semicolon
id|b1_free_card
c_func
(paren
id|card
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|t1isa_add_card
r_static
r_int
id|t1isa_add_card
c_func
(paren
r_struct
id|capi_driver
op_star
id|driver
comma
r_struct
id|capicardparams
op_star
id|p
)paren
(brace
r_struct
id|capi_ctr
op_star
id|ctrl
suffix:semicolon
id|avmctrl_info
op_star
id|cinfo
suffix:semicolon
id|avmcard
op_star
id|card
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|card
op_assign
id|b1_alloc_card
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: no memory.&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
id|cinfo
op_assign
id|card-&gt;ctrlinfo
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;name
comma
l_string|&quot;t1isa-%x&quot;
comma
id|p-&gt;port
)paren
suffix:semicolon
id|card-&gt;port
op_assign
id|p-&gt;port
suffix:semicolon
id|card-&gt;irq
op_assign
id|p-&gt;irq
suffix:semicolon
id|card-&gt;cardtype
op_assign
id|avm_t1isa
suffix:semicolon
id|card-&gt;cardnr
op_assign
id|p-&gt;cardnr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
(paren
id|card-&gt;port
op_amp
l_int|0x7
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
(paren
id|card-&gt;port
op_amp
l_int|0x30
)paren
op_ne
l_int|0x30
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: illegal port 0x%x.&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;port
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|err_free
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hema_irq_table
(braket
id|card-&gt;irq
op_amp
l_int|0xf
)braket
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: irq %d not valid.&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;irq
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|err_free
suffix:semicolon
)brace
r_for
c_loop
(paren
id|ctrl
op_assign
id|driver-&gt;controller
suffix:semicolon
id|ctrl
suffix:semicolon
id|ctrl
op_assign
id|ctrl-&gt;next
)paren
(brace
id|avmcard
op_star
id|cardp
op_assign
(paren
(paren
id|avmctrl_info
op_star
)paren
(paren
id|ctrl-&gt;driverdata
)paren
)paren
op_member_access_from_pointer
id|card
suffix:semicolon
r_if
c_cond
(paren
id|cardp-&gt;cardnr
op_eq
id|card-&gt;cardnr
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: card with number %d already installed at 0x%x.&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;cardnr
comma
id|cardp-&gt;port
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|err_free
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|card-&gt;port
comma
id|AVMB1_PORTLEN
comma
id|card-&gt;name
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: ports 0x%03x-0x%03x in use.&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;port
comma
id|card-&gt;port
op_plus
id|AVMB1_PORTLEN
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|err_free
suffix:semicolon
)brace
id|retval
op_assign
id|request_irq
c_func
(paren
id|card-&gt;irq
comma
id|t1isa_interrupt
comma
l_int|0
comma
id|card-&gt;name
comma
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to get IRQ %d.&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;irq
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|err_release_region
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|t1_detectandinit
c_func
(paren
id|card-&gt;port
comma
id|card-&gt;irq
comma
id|card-&gt;cardnr
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: NO card at 0x%x (%d)&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;port
comma
id|retval
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|err_free_irq
suffix:semicolon
)brace
id|t1_disable_irq
c_func
(paren
id|card-&gt;port
)paren
suffix:semicolon
id|b1_reset
c_func
(paren
id|card-&gt;port
)paren
suffix:semicolon
id|cinfo-&gt;capi_ctrl
op_assign
id|di
op_member_access_from_pointer
id|attach_ctr
c_func
(paren
id|driver
comma
id|card-&gt;name
comma
id|cinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cinfo-&gt;capi_ctrl
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: attach controller failed.&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|err_free_irq
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: AVM T1 ISA at i/o %#x, irq %d, card %d&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;port
comma
id|card-&gt;irq
comma
id|card-&gt;cardnr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_free_irq
suffix:colon
id|free_irq
c_func
(paren
id|card-&gt;irq
comma
id|card
)paren
suffix:semicolon
id|err_release_region
suffix:colon
id|release_region
c_func
(paren
id|card-&gt;port
comma
id|AVMB1_PORTLEN
)paren
suffix:semicolon
id|err_free
suffix:colon
id|b1_free_card
c_func
(paren
id|card
)paren
suffix:semicolon
id|err
suffix:colon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|t1isa_send_message
r_static
r_void
id|t1isa_send_message
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|avmctrl_info
op_star
id|cinfo
op_assign
(paren
id|avmctrl_info
op_star
)paren
(paren
id|ctrl-&gt;driverdata
)paren
suffix:semicolon
id|avmcard
op_star
id|card
op_assign
id|cinfo-&gt;card
suffix:semicolon
r_int
r_int
id|port
op_assign
id|card-&gt;port
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u16
id|len
op_assign
id|CAPIMSG_LEN
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
id|u8
id|cmd
op_assign
id|CAPIMSG_COMMAND
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
id|u8
id|subcmd
op_assign
id|CAPIMSG_SUBCOMMAND
c_func
(paren
id|skb-&gt;data
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
id|CAPICMD
c_func
(paren
id|cmd
comma
id|subcmd
)paren
op_eq
id|CAPI_DATA_B3_REQ
)paren
(brace
id|u16
id|dlen
op_assign
id|CAPIMSG_DATALEN
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
id|b1_put_byte
c_func
(paren
id|port
comma
id|SEND_DATA_B3_REQ
)paren
suffix:semicolon
id|t1_put_slice
c_func
(paren
id|port
comma
id|skb-&gt;data
comma
id|len
)paren
suffix:semicolon
id|t1_put_slice
c_func
(paren
id|port
comma
id|skb-&gt;data
op_plus
id|len
comma
id|dlen
)paren
suffix:semicolon
)brace
r_else
(brace
id|b1_put_byte
c_func
(paren
id|port
comma
id|SEND_MESSAGE
)paren
suffix:semicolon
id|t1_put_slice
c_func
(paren
id|port
comma
id|skb-&gt;data
comma
id|len
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|t1isa_procinfo
r_static
r_char
op_star
id|t1isa_procinfo
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
)paren
(brace
id|avmctrl_info
op_star
id|cinfo
op_assign
(paren
id|avmctrl_info
op_star
)paren
(paren
id|ctrl-&gt;driverdata
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cinfo
)paren
r_return
l_string|&quot;&quot;
suffix:semicolon
id|sprintf
c_func
(paren
id|cinfo-&gt;infobuf
comma
l_string|&quot;%s %s 0x%x %d %d&quot;
comma
id|cinfo-&gt;cardname
(braket
l_int|0
)braket
ques
c_cond
id|cinfo-&gt;cardname
suffix:colon
l_string|&quot;-&quot;
comma
id|cinfo-&gt;version
(braket
id|VER_DRIVER
)braket
ques
c_cond
id|cinfo-&gt;version
(braket
id|VER_DRIVER
)braket
suffix:colon
l_string|&quot;-&quot;
comma
id|cinfo-&gt;card
ques
c_cond
id|cinfo-&gt;card-&gt;port
suffix:colon
l_int|0x0
comma
id|cinfo-&gt;card
ques
c_cond
id|cinfo-&gt;card-&gt;irq
suffix:colon
l_int|0
comma
id|cinfo-&gt;card
ques
c_cond
id|cinfo-&gt;card-&gt;cardnr
suffix:colon
l_int|0
)paren
suffix:semicolon
r_return
id|cinfo-&gt;infobuf
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|variable|t1isa_driver
r_static
r_struct
id|capi_driver
id|t1isa_driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;t1isa&quot;
comma
id|revision
suffix:colon
l_string|&quot;0.0&quot;
comma
id|load_firmware
suffix:colon
id|t1isa_load_firmware
comma
id|reset_ctr
suffix:colon
id|t1isa_reset_ctr
comma
id|remove_ctr
suffix:colon
id|t1isa_remove_ctr
comma
id|register_appl
suffix:colon
id|b1_register_appl
comma
id|release_appl
suffix:colon
id|b1_release_appl
comma
id|send_message
suffix:colon
id|t1isa_send_message
comma
id|procinfo
suffix:colon
id|t1isa_procinfo
comma
id|ctr_read_proc
suffix:colon
id|b1ctl_read_proc
comma
id|driver_read_proc
suffix:colon
l_int|0
comma
multiline_comment|/* use standard driver_read_proc */
id|add_card
suffix:colon
id|t1isa_add_card
comma
)brace
suffix:semicolon
DECL|function|t1isa_init
r_static
r_int
id|__init
id|t1isa_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|capi_driver
op_star
id|driver
op_assign
op_amp
id|t1isa_driver
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|strchr
c_func
(paren
id|revision
comma
l_char|&squot;:&squot;
)paren
)paren
op_ne
l_int|0
op_logical_and
id|p
(braket
l_int|1
)braket
)paren
(brace
id|strncpy
c_func
(paren
id|driver-&gt;revision
comma
id|p
op_plus
l_int|2
comma
r_sizeof
(paren
id|driver-&gt;revision
)paren
)paren
suffix:semicolon
id|driver-&gt;revision
(braket
r_sizeof
(paren
id|driver-&gt;revision
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|strchr
c_func
(paren
id|driver-&gt;revision
comma
l_char|&squot;$&squot;
)paren
)paren
op_ne
l_int|0
op_logical_and
id|p
OG
id|driver-&gt;revision
)paren
op_star
(paren
id|p
op_minus
l_int|1
)paren
op_assign
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: revision %s&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|driver-&gt;revision
)paren
suffix:semicolon
id|di
op_assign
id|attach_capi_driver
c_func
(paren
id|driver
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|di
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to attach capi_driver&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|t1isa_exit
r_static
r_void
id|__exit
id|t1isa_exit
c_func
(paren
r_void
)paren
(brace
id|detach_capi_driver
c_func
(paren
op_amp
id|t1isa_driver
)paren
suffix:semicolon
)brace
DECL|variable|t1isa_init
id|module_init
c_func
(paren
id|t1isa_init
)paren
suffix:semicolon
DECL|variable|t1isa_exit
id|module_exit
c_func
(paren
id|t1isa_exit
)paren
suffix:semicolon
eof
