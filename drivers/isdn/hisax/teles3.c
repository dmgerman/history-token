multiline_comment|/* $Id: teles3.c,v 2.17.6.2 2001/09/23 22:24:52 kai Exp $&n; *&n; * low level stuff for Teles 16.3 &amp; PNP isdn cards&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * Thanks to    Jan den Ouden&n; *              Fritz Elfert&n; *              Beat Doebeli&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/isapnp.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;hscx.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
r_extern
r_const
r_char
op_star
id|CardType
(braket
)braket
suffix:semicolon
DECL|variable|teles3_revision
r_const
r_char
op_star
id|teles3_revision
op_assign
l_string|&quot;$Revision: 2.17.6.2 $&quot;
suffix:semicolon
DECL|macro|byteout
mdefine_line|#define byteout(addr,val) outb(val,addr)
DECL|macro|bytein
mdefine_line|#define bytein(addr) inb(addr)
r_static
r_inline
id|u8
DECL|function|readreg
id|readreg
c_func
(paren
r_int
r_int
id|adr
comma
id|u8
id|off
)paren
(brace
r_return
(paren
id|bytein
c_func
(paren
id|adr
op_plus
id|off
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|writereg
id|writereg
c_func
(paren
r_int
r_int
id|adr
comma
id|u8
id|off
comma
id|u8
id|data
)paren
(brace
id|byteout
c_func
(paren
id|adr
op_plus
id|off
comma
id|data
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|read_fifo
id|read_fifo
c_func
(paren
r_int
r_int
id|adr
comma
id|u8
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|insb
c_func
(paren
id|adr
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|write_fifo
id|write_fifo
c_func
(paren
r_int
r_int
id|adr
comma
id|u8
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|outsb
c_func
(paren
id|adr
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
r_static
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
id|offset
)paren
(brace
r_return
id|readreg
c_func
(paren
id|cs-&gt;hw.teles3.isac
comma
id|offset
)paren
suffix:semicolon
)brace
r_static
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
id|offset
comma
id|u8
id|value
)paren
(brace
id|writereg
c_func
(paren
id|cs-&gt;hw.teles3.isac
comma
id|offset
comma
id|value
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|isac_read_fifo
id|isac_read_fifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u8
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|read_fifo
c_func
(paren
id|cs-&gt;hw.teles3.isacfifo
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
r_static
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
id|data
comma
r_int
id|size
)paren
(brace
id|write_fifo
c_func
(paren
id|cs-&gt;hw.teles3.isacfifo
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
DECL|variable|isac_ops
r_static
r_struct
id|dc_hw_ops
id|isac_ops
op_assign
(brace
dot
id|read_reg
op_assign
id|isac_read
comma
dot
id|write_reg
op_assign
id|isac_write
comma
dot
id|read_fifo
op_assign
id|isac_read_fifo
comma
dot
id|write_fifo
op_assign
id|isac_write_fifo
comma
)brace
suffix:semicolon
r_static
id|u8
DECL|function|hscx_read
id|hscx_read
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
id|u8
id|offset
)paren
(brace
r_return
id|readreg
c_func
(paren
id|cs-&gt;hw.teles3.hscx
(braket
id|hscx
)braket
comma
id|offset
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|hscx_write
id|hscx_write
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
id|u8
id|offset
comma
id|u8
id|value
)paren
(brace
id|writereg
c_func
(paren
id|cs-&gt;hw.teles3.hscx
(braket
id|hscx
)braket
comma
id|offset
comma
id|value
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|hscx_read_fifo
id|hscx_read_fifo
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
id|u8
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|read_fifo
c_func
(paren
id|cs-&gt;hw.teles3.hscxfifo
(braket
id|hscx
)braket
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|hscx_write_fifo
id|hscx_write_fifo
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
id|u8
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|write_fifo
c_func
(paren
id|cs-&gt;hw.teles3.hscxfifo
(braket
id|hscx
)braket
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
DECL|variable|hscx_ops
r_static
r_struct
id|bc_hw_ops
id|hscx_ops
op_assign
(brace
dot
id|read_reg
op_assign
id|hscx_read
comma
dot
id|write_reg
op_assign
id|hscx_write
comma
dot
id|read_fifo
op_assign
id|hscx_read_fifo
comma
dot
id|write_fifo
op_assign
id|hscx_write_fifo
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|teles3_reset
id|teles3_reset
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|u8
id|irqcfg
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;typ
op_ne
id|ISDN_CTYPE_TELESPCMCIA
)paren
(brace
r_if
c_cond
(paren
(paren
id|cs-&gt;hw.teles3.cfg_reg
)paren
op_logical_and
(paren
id|cs-&gt;typ
op_ne
id|ISDN_CTYPE_COMPAQ_ISA
)paren
)paren
(brace
r_switch
c_cond
(paren
id|cs-&gt;irq
)paren
(brace
r_case
l_int|2
suffix:colon
r_case
l_int|9
suffix:colon
id|irqcfg
op_assign
l_int|0x00
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|irqcfg
op_assign
l_int|0x02
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|irqcfg
op_assign
l_int|0x04
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|irqcfg
op_assign
l_int|0x06
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
id|irqcfg
op_assign
l_int|0x08
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
id|irqcfg
op_assign
l_int|0x0A
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|12
suffix:colon
id|irqcfg
op_assign
l_int|0x0C
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|15
suffix:colon
id|irqcfg
op_assign
l_int|0x0E
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
id|byteout
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
op_plus
l_int|4
comma
id|irqcfg
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
id|HZ
op_div
l_int|10
op_plus
l_int|1
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
op_plus
l_int|4
comma
id|irqcfg
op_or
l_int|1
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
id|HZ
op_div
l_int|10
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_COMPAQ_ISA
)paren
(brace
id|byteout
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
comma
l_int|0xff
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
comma
l_int|0x00
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
l_int|2
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Reset off for 16.3 PnP , thanks to Georg Acher */
id|byteout
c_func
(paren
id|cs-&gt;hw.teles3.isac
op_plus
l_int|0x3c
comma
l_int|0
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.teles3.isac
op_plus
l_int|0x3c
comma
l_int|1
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
l_int|2
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|teles3_ops
r_static
r_struct
id|card_ops
id|teles3_ops
op_assign
(brace
dot
id|init
op_assign
id|inithscxisac
comma
dot
id|reset
op_assign
id|teles3_reset
comma
dot
id|release
op_assign
id|hisax_release_resources
comma
dot
id|irq_func
op_assign
id|hscxisac_irq
comma
)brace
suffix:semicolon
macro_line|#ifdef __ISAPNP__
DECL|variable|__initdata
r_static
r_struct
id|isapnp_device_id
id|teles_ids
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;T&squot;
comma
l_char|&squot;A&squot;
comma
l_char|&squot;G&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x2110
)paren
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;T&squot;
comma
l_char|&squot;A&squot;
comma
l_char|&squot;G&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x2110
)paren
comma
(paren
r_int
r_int
)paren
l_string|&quot;Teles 16.3 PnP&quot;
)brace
comma
(brace
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;C&squot;
comma
l_char|&squot;T&squot;
comma
l_char|&squot;X&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x0
)paren
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;C&squot;
comma
l_char|&squot;T&squot;
comma
l_char|&squot;X&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x0
)paren
comma
(paren
r_int
r_int
)paren
l_string|&quot;Creatix 16.3 PnP&quot;
)brace
comma
(brace
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;C&squot;
comma
l_char|&squot;P&squot;
comma
l_char|&squot;Q&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x1002
)paren
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;C&squot;
comma
l_char|&squot;P&squot;
comma
l_char|&squot;Q&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x1002
)paren
comma
(paren
r_int
r_int
)paren
l_string|&quot;Compaq ISDN S0&quot;
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|variable|tdev
r_static
r_struct
id|isapnp_device_id
op_star
id|tdev
op_assign
op_amp
id|teles_ids
(braket
l_int|0
)braket
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|pci_bus
op_star
id|pnp_c
id|__devinitdata
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
r_int
id|__devinit
DECL|function|setup_teles3
id|setup_teles3
c_func
(paren
r_struct
id|IsdnCard
op_star
id|card
)paren
(brace
id|u8
id|val
suffix:semicolon
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|card-&gt;cs
suffix:semicolon
r_char
id|tmp
(braket
l_int|64
)braket
suffix:semicolon
id|strcpy
c_func
(paren
id|tmp
comma
id|teles3_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: Teles IO driver Rev. %s&bslash;n&quot;
comma
id|HiSax_getrev
c_func
(paren
id|tmp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cs-&gt;typ
op_ne
id|ISDN_CTYPE_16_3
)paren
op_logical_and
(paren
id|cs-&gt;typ
op_ne
id|ISDN_CTYPE_PNP
)paren
op_logical_and
(paren
id|cs-&gt;typ
op_ne
id|ISDN_CTYPE_TELESPCMCIA
)paren
op_logical_and
(paren
id|cs-&gt;typ
op_ne
id|ISDN_CTYPE_COMPAQ_ISA
)paren
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef __ISAPNP__
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;para
(braket
l_int|1
)braket
op_logical_and
id|isapnp_present
c_func
(paren
)paren
)paren
(brace
r_struct
id|pci_bus
op_star
id|pb
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pd
suffix:semicolon
r_while
c_loop
(paren
id|tdev-&gt;card_vendor
)paren
(brace
r_if
c_cond
(paren
(paren
id|pb
op_assign
id|isapnp_find_card
c_func
(paren
id|tdev-&gt;card_vendor
comma
id|tdev-&gt;card_device
comma
id|pnp_c
)paren
)paren
)paren
(brace
id|pnp_c
op_assign
id|pb
suffix:semicolon
id|pd
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pd
op_assign
id|isapnp_find_dev
c_func
(paren
id|pnp_c
comma
id|tdev-&gt;vendor
comma
id|tdev-&gt;function
comma
id|pd
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: %s detected&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
id|tdev-&gt;driver_data
)paren
suffix:semicolon
id|pd
op_member_access_from_pointer
id|prepare
c_func
(paren
id|pd
)paren
suffix:semicolon
id|pd
op_member_access_from_pointer
id|deactivate
c_func
(paren
id|pd
)paren
suffix:semicolon
id|pd
op_member_access_from_pointer
id|activate
c_func
(paren
id|pd
)paren
suffix:semicolon
id|card-&gt;para
(braket
l_int|3
)braket
op_assign
id|pd-&gt;resource
(braket
l_int|2
)braket
dot
id|start
suffix:semicolon
id|card-&gt;para
(braket
l_int|2
)braket
op_assign
id|pd-&gt;resource
(braket
l_int|1
)braket
dot
id|start
suffix:semicolon
id|card-&gt;para
(braket
l_int|1
)braket
op_assign
id|pd-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|card-&gt;para
(braket
l_int|0
)braket
op_assign
id|pd-&gt;irq_resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;para
(braket
l_int|0
)braket
op_logical_or
op_logical_neg
id|card-&gt;para
(braket
l_int|1
)braket
op_logical_or
op_logical_neg
id|card-&gt;para
(braket
l_int|2
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Teles PnP:some resources are missing %ld/%lx/%lx&bslash;n&quot;
comma
id|card-&gt;para
(braket
l_int|0
)braket
comma
id|card-&gt;para
(braket
l_int|1
)braket
comma
id|card-&gt;para
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|pd
op_member_access_from_pointer
id|deactivate
c_func
(paren
id|pd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Teles PnP: PnP error card found, no device&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|tdev
op_increment
suffix:semicolon
id|pnp_c
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|tdev-&gt;card_vendor
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Teles PnP: no ISAPnP card found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif
r_if
c_cond
(paren
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_16_3
)paren
(brace
id|cs-&gt;hw.teles3.cfg_reg
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|cs-&gt;hw.teles3.cfg_reg
)paren
(brace
r_case
l_int|0x180
suffix:colon
r_case
l_int|0x280
suffix:colon
r_case
l_int|0x380
suffix:colon
id|cs-&gt;hw.teles3.cfg_reg
op_or_assign
l_int|0xc00
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cs-&gt;hw.teles3.isac
op_assign
id|cs-&gt;hw.teles3.cfg_reg
op_minus
l_int|0x420
suffix:semicolon
id|cs-&gt;hw.teles3.hscx
(braket
l_int|0
)braket
op_assign
id|cs-&gt;hw.teles3.cfg_reg
op_minus
l_int|0xc20
suffix:semicolon
id|cs-&gt;hw.teles3.hscx
(braket
l_int|1
)braket
op_assign
id|cs-&gt;hw.teles3.cfg_reg
op_minus
l_int|0x820
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_TELESPCMCIA
)paren
(brace
id|cs-&gt;hw.teles3.cfg_reg
op_assign
l_int|0
suffix:semicolon
id|cs-&gt;hw.teles3.hscx
(braket
l_int|0
)braket
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_minus
l_int|0x20
suffix:semicolon
id|cs-&gt;hw.teles3.hscx
(braket
l_int|1
)braket
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
suffix:semicolon
id|cs-&gt;hw.teles3.isac
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
l_int|0x20
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_COMPAQ_ISA
)paren
(brace
id|cs-&gt;hw.teles3.cfg_reg
op_assign
id|card-&gt;para
(braket
l_int|3
)braket
suffix:semicolon
id|cs-&gt;hw.teles3.isac
op_assign
id|card-&gt;para
(braket
l_int|2
)braket
op_minus
l_int|32
suffix:semicolon
id|cs-&gt;hw.teles3.hscx
(braket
l_int|0
)braket
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_minus
l_int|32
suffix:semicolon
id|cs-&gt;hw.teles3.hscx
(braket
l_int|1
)braket
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* PNP */
id|cs-&gt;hw.teles3.cfg_reg
op_assign
l_int|0
suffix:semicolon
id|cs-&gt;hw.teles3.isac
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_minus
l_int|32
suffix:semicolon
id|cs-&gt;hw.teles3.hscx
(braket
l_int|0
)braket
op_assign
id|card-&gt;para
(braket
l_int|2
)braket
op_minus
l_int|32
suffix:semicolon
id|cs-&gt;hw.teles3.hscx
(braket
l_int|1
)braket
op_assign
id|card-&gt;para
(braket
l_int|2
)braket
suffix:semicolon
)brace
id|cs-&gt;irq
op_assign
id|card-&gt;para
(braket
l_int|0
)braket
suffix:semicolon
id|cs-&gt;hw.teles3.isacfifo
op_assign
id|cs-&gt;hw.teles3.isac
op_plus
l_int|0x3e
suffix:semicolon
id|cs-&gt;hw.teles3.hscxfifo
(braket
l_int|0
)braket
op_assign
id|cs-&gt;hw.teles3.hscx
(braket
l_int|0
)braket
op_plus
l_int|0x3e
suffix:semicolon
id|cs-&gt;hw.teles3.hscxfifo
(braket
l_int|1
)braket
op_assign
id|cs-&gt;hw.teles3.hscx
(braket
l_int|1
)braket
op_plus
l_int|0x3e
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_TELESPCMCIA
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_io
c_func
(paren
op_amp
id|cs-&gt;rs
comma
id|cs-&gt;hw.teles3.hscx
(braket
l_int|1
)braket
comma
l_int|96
comma
l_string|&quot;HiSax Teles PCMCIA&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|cs-&gt;hw.teles3.cfg_reg
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_COMPAQ_ISA
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_io
c_func
(paren
op_amp
id|cs-&gt;rs
comma
id|cs-&gt;hw.teles3.cfg_reg
comma
l_int|1
comma
l_string|&quot;teles3 cfg&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_io
c_func
(paren
op_amp
id|cs-&gt;rs
comma
id|cs-&gt;hw.teles3.cfg_reg
comma
l_int|8
comma
l_string|&quot;teles3 cfg&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_io
c_func
(paren
op_amp
id|cs-&gt;rs
comma
id|cs-&gt;hw.teles3.isac
op_plus
l_int|32
comma
l_int|32
comma
l_string|&quot;HiSax isac&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_io
c_func
(paren
op_amp
id|cs-&gt;rs
comma
id|cs-&gt;hw.teles3.hscx
(braket
l_int|0
)braket
op_plus
l_int|32
comma
l_int|32
comma
l_string|&quot;HiSax hscx A&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_io
c_func
(paren
op_amp
id|cs-&gt;rs
comma
id|cs-&gt;hw.teles3.hscx
(braket
l_int|1
)braket
op_plus
l_int|32
comma
l_int|32
comma
l_string|&quot;HiSax hscx B&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|cs-&gt;hw.teles3.cfg_reg
)paren
op_logical_and
(paren
id|cs-&gt;typ
op_ne
id|ISDN_CTYPE_COMPAQ_ISA
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|val
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
op_plus
l_int|0
)paren
)paren
op_ne
l_int|0x51
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Teles: 16.3 Byte at %x is %x&bslash;n&quot;
comma
id|cs-&gt;hw.teles3.cfg_reg
op_plus
l_int|0
comma
id|val
)paren
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|val
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
op_plus
l_int|1
)paren
)paren
op_ne
l_int|0x93
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Teles: 16.3 Byte at %x is %x&bslash;n&quot;
comma
id|cs-&gt;hw.teles3.cfg_reg
op_plus
l_int|1
comma
id|val
)paren
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
id|val
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* 0x1e=without AB&n;&t;&t;&t;&t;&t;&t;&t; * 0x1f=with AB&n;&t;&t;&t;&t;&t;&t;&t; * 0x1c 16.3 ???&n;&t;&t;&t;&t;&t;&t;&t; * 0x39 16.3 1.1&n;&t;&t;&t;&t;&t;&t;&t; * 0x38 16.3 1.3&n;&t;&t;&t;&t;&t;&t;&t; * 0x46 16.3 with AB + Video (Teles-Vision)&n;&t;&t;&t;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|val
op_ne
l_int|0x46
op_logical_and
id|val
op_ne
l_int|0x39
op_logical_and
id|val
op_ne
l_int|0x38
op_logical_and
id|val
op_ne
l_int|0x1c
op_logical_and
id|val
op_ne
l_int|0x1e
op_logical_and
id|val
op_ne
l_int|0x1f
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Teles: 16.3 Byte at %x is %x&bslash;n&quot;
comma
id|cs-&gt;hw.teles3.cfg_reg
op_plus
l_int|2
comma
id|val
)paren
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: %s config irq:%d isac:0x%X  cfg:0x%X&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
id|cs-&gt;irq
comma
id|cs-&gt;hw.teles3.isac
op_plus
l_int|32
comma
id|cs-&gt;hw.teles3.cfg_reg
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: hscx A:0x%X  hscx B:0x%X&bslash;n&quot;
comma
id|cs-&gt;hw.teles3.hscx
(braket
l_int|0
)braket
op_plus
l_int|32
comma
id|cs-&gt;hw.teles3.hscx
(braket
l_int|1
)braket
op_plus
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|teles3_reset
c_func
(paren
id|cs
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Teles3: wrong IRQ&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
id|cs-&gt;dc_hw_ops
op_assign
op_amp
id|isac_ops
suffix:semicolon
id|cs-&gt;bc_hw_ops
op_assign
op_amp
id|hscx_ops
suffix:semicolon
id|cs-&gt;card_ops
op_assign
op_amp
id|teles3_ops
suffix:semicolon
id|ISACVersion
c_func
(paren
id|cs
comma
l_string|&quot;Teles3:&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|HscxVersion
c_func
(paren
id|cs
comma
l_string|&quot;Teles3:&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Teles3: wrong HSCX versions check IO address&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
r_return
(paren
l_int|1
)paren
suffix:semicolon
id|err
suffix:colon
id|hisax_release_resources
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
