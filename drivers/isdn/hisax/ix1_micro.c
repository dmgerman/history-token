multiline_comment|/* $Id: ix1_micro.c,v 2.10.6.2 2001/09/23 22:24:49 kai Exp $&n; *&n; * low level stuff for ITK ix1-micro Rev.2 isdn cards&n; * derived from the original file teles3.c from Karsten Keil&n; *&n; * Author       Klaus-Peter Nischke&n; * Copyright    by Klaus-Peter Nischke, ITK AG&n; *                                   &lt;klaus@nischke.do.eunet.de&gt;&n; *              by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * Klaus-Peter Nischke&n; * Deusener Str. 287&n; * 44369 Dortmund&n; * Germany&n; */
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
DECL|variable|ix1_revision
r_const
r_char
op_star
id|ix1_revision
op_assign
l_string|&quot;$Revision: 2.10.6.2 $&quot;
suffix:semicolon
DECL|variable|ix1_micro_lock
r_static
id|spinlock_t
id|ix1_micro_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|byteout
mdefine_line|#define byteout(addr,val) outb(val,addr)
DECL|macro|bytein
mdefine_line|#define bytein(addr) inb(addr)
DECL|macro|SPECIAL_PORT_OFFSET
mdefine_line|#define SPECIAL_PORT_OFFSET 3
DECL|macro|ISAC_COMMAND_OFFSET
mdefine_line|#define ISAC_COMMAND_OFFSET 2
DECL|macro|ISAC_DATA_OFFSET
mdefine_line|#define ISAC_DATA_OFFSET 0
DECL|macro|HSCX_COMMAND_OFFSET
mdefine_line|#define HSCX_COMMAND_OFFSET 2
DECL|macro|HSCX_DATA_OFFSET
mdefine_line|#define HSCX_DATA_OFFSET 1
DECL|macro|TIMEOUT
mdefine_line|#define TIMEOUT 50
r_static
r_inline
id|u8
DECL|function|readreg
id|readreg
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
r_int
id|adr
comma
id|u8
id|off
)paren
(brace
id|u8
id|ret
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ix1_micro_lock
comma
id|flags
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.ix1.isac_ale
comma
id|off
)paren
suffix:semicolon
id|ret
op_assign
id|bytein
c_func
(paren
id|adr
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ix1_micro_lock
comma
id|flags
)paren
suffix:semicolon
r_return
(paren
id|ret
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
r_struct
id|IsdnCardState
op_star
id|cs
comma
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
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ix1_micro_lock
comma
id|flags
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.ix1.isac_ale
comma
id|off
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|adr
comma
id|data
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ix1_micro_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|readfifo
id|readfifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
r_int
id|adr
comma
id|u8
id|off
comma
id|u8
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|byteout
c_func
(paren
id|cs-&gt;hw.ix1.isac_ale
comma
id|off
)paren
suffix:semicolon
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
r_inline
r_void
DECL|function|writefifo
id|writefifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
r_int
id|adr
comma
id|u8
id|off
comma
id|u8
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|byteout
c_func
(paren
id|cs-&gt;hw.ix1.isac_ale
comma
id|off
)paren
suffix:semicolon
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
id|cs
comma
id|cs-&gt;hw.ix1.isac
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
id|cs
comma
id|cs-&gt;hw.ix1.isac
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
id|readfifo
c_func
(paren
id|cs
comma
id|cs-&gt;hw.ix1.isac
comma
l_int|0
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
id|writefifo
c_func
(paren
id|cs
comma
id|cs-&gt;hw.ix1.isac
comma
l_int|0
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
id|cs
comma
id|cs-&gt;hw.ix1.hscx
comma
id|offset
op_plus
(paren
id|hscx
ques
c_cond
l_int|0x40
suffix:colon
l_int|0
)paren
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
id|cs
comma
id|cs-&gt;hw.ix1.hscx
comma
id|offset
op_plus
(paren
id|hscx
ques
c_cond
l_int|0x40
suffix:colon
l_int|0
)paren
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
id|readfifo
c_func
(paren
id|cs
comma
id|cs-&gt;hw.ix1.hscx
comma
id|hscx
ques
c_cond
l_int|0x40
suffix:colon
l_int|0
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
id|writefifo
c_func
(paren
id|cs
comma
id|cs-&gt;hw.ix1.hscx
comma
id|hscx
ques
c_cond
l_int|0x40
suffix:colon
l_int|0
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
DECL|function|ix1_reset
id|ix1_reset
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_int
id|cnt
suffix:semicolon
multiline_comment|/* reset isac */
id|cnt
op_assign
l_int|3
op_star
(paren
id|HZ
op_div
l_int|10
)paren
op_plus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|cnt
op_decrement
)paren
(brace
id|byteout
c_func
(paren
id|cs-&gt;hw.ix1.cfg_reg
op_plus
id|SPECIAL_PORT_OFFSET
comma
l_int|1
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* wait &gt;=10 ms */
)brace
id|byteout
c_func
(paren
id|cs-&gt;hw.ix1.cfg_reg
op_plus
id|SPECIAL_PORT_OFFSET
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ix1_ops
r_static
r_struct
id|card_ops
id|ix1_ops
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
id|ix1_reset
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
id|itk_ids
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;I&squot;
comma
l_char|&squot;T&squot;
comma
l_char|&squot;K&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x25
)paren
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;I&squot;
comma
l_char|&squot;T&squot;
comma
l_char|&squot;K&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x25
)paren
comma
(paren
r_int
r_int
)paren
l_string|&quot;ITK micro 2&quot;
)brace
comma
(brace
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;I&squot;
comma
l_char|&squot;T&squot;
comma
l_char|&squot;K&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x29
)paren
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;I&squot;
comma
l_char|&squot;T&squot;
comma
l_char|&squot;K&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x29
)paren
comma
(paren
r_int
r_int
)paren
l_string|&quot;ITK micro 2.&quot;
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|variable|idev
r_static
r_struct
id|isapnp_device_id
op_star
id|idev
op_assign
op_amp
id|itk_ids
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
id|__init
DECL|function|setup_ix1micro
id|setup_ix1micro
c_func
(paren
r_struct
id|IsdnCard
op_star
id|card
)paren
(brace
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
id|ix1_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: ITK IX1 driver Rev. %s&bslash;n&quot;
comma
id|HiSax_getrev
c_func
(paren
id|tmp
)paren
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
id|idev-&gt;card_vendor
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
id|idev-&gt;card_vendor
comma
id|idev-&gt;card_device
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
id|idev-&gt;vendor
comma
id|idev-&gt;function
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
id|idev-&gt;driver_data
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
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ITK PnP:some resources are missing %ld/%lx&bslash;n&quot;
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
l_string|&quot;ITK PnP: PnP error card found, no device&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|idev
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
id|idev-&gt;card_vendor
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ITK PnP: no ISAPnP card found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/* IO-Ports */
id|cs-&gt;hw.ix1.isac_ale
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
id|ISAC_COMMAND_OFFSET
suffix:semicolon
id|cs-&gt;hw.ix1.isac
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
id|ISAC_DATA_OFFSET
suffix:semicolon
id|cs-&gt;hw.ix1.hscx
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
id|HSCX_DATA_OFFSET
suffix:semicolon
id|cs-&gt;hw.ix1.cfg_reg
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
suffix:semicolon
id|cs-&gt;irq
op_assign
id|card-&gt;para
(braket
l_int|0
)braket
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
id|cs-&gt;hw.ix1.cfg_reg
comma
l_int|4
comma
l_string|&quot;ix1micro cfg&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: %s config irq:%d io:0x%X&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
id|cs-&gt;irq
comma
id|cs-&gt;hw.ix1.cfg_reg
)paren
suffix:semicolon
id|ix1_reset
c_func
(paren
id|cs
)paren
suffix:semicolon
id|cs-&gt;card_ops
op_assign
op_amp
id|ix1_ops
suffix:semicolon
r_if
c_cond
(paren
id|hscxisac_setup
c_func
(paren
id|cs
comma
op_amp
id|isac_ops
comma
op_amp
id|hscx_ops
)paren
)paren
r_goto
id|err
suffix:semicolon
r_return
l_int|1
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
l_int|0
suffix:semicolon
)brace
eof
