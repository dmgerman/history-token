multiline_comment|/* $Id: niccy.c,v 1.15.6.6 2001/10/20 22:08:24 kai Exp $&n; *&n; * low level stuff for Dr. Neuhaus NICCY PnP and NICCY PCI and&n; * compatible (SAGEM cybermodem)&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; * &n; * Thanks to Dr. Neuhaus and SAGEM for information&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;hscx.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/isapnp.h&gt;
r_extern
r_const
r_char
op_star
id|CardType
(braket
)braket
suffix:semicolon
DECL|variable|niccy_revision
r_const
r_char
op_star
id|niccy_revision
op_assign
l_string|&quot;$Revision: 1.15.6.6 $&quot;
suffix:semicolon
DECL|variable|niccy_lock
r_static
id|spinlock_t
id|niccy_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|byteout
mdefine_line|#define byteout(addr,val) outb(val,addr)
DECL|macro|bytein
mdefine_line|#define bytein(addr) inb(addr)
DECL|macro|ISAC_PCI_DATA
mdefine_line|#define ISAC_PCI_DATA&t;0
DECL|macro|HSCX_PCI_DATA
mdefine_line|#define HSCX_PCI_DATA&t;1
DECL|macro|ISAC_PCI_ADDR
mdefine_line|#define ISAC_PCI_ADDR&t;2
DECL|macro|HSCX_PCI_ADDR
mdefine_line|#define HSCX_PCI_ADDR&t;3
DECL|macro|ISAC_PNP
mdefine_line|#define ISAC_PNP&t;0
DECL|macro|HSCX_PNP
mdefine_line|#define HSCX_PNP&t;1
multiline_comment|/* SUB Types */
DECL|macro|NICCY_PNP
mdefine_line|#define NICCY_PNP&t;1
DECL|macro|NICCY_PCI
mdefine_line|#define NICCY_PCI&t;2
multiline_comment|/* PCI stuff */
DECL|macro|PCI_IRQ_CTRL_REG
mdefine_line|#define PCI_IRQ_CTRL_REG&t;0x38
DECL|macro|PCI_IRQ_ENABLE
mdefine_line|#define PCI_IRQ_ENABLE&t;&t;0x1f00
DECL|macro|PCI_IRQ_DISABLE
mdefine_line|#define PCI_IRQ_DISABLE&t;&t;0xff0000
DECL|macro|PCI_IRQ_ASSERT
mdefine_line|#define PCI_IRQ_ASSERT&t;&t;0x800000
r_static
r_inline
id|u8
DECL|function|readreg
id|readreg
c_func
(paren
r_int
r_int
id|ale
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
id|niccy_lock
comma
id|flags
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|ale
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
id|niccy_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
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
id|ale
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
id|niccy_lock
comma
id|flags
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|ale
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
id|niccy_lock
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
r_int
r_int
id|ale
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
id|ale
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
r_int
r_int
id|ale
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
id|ale
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
id|cs-&gt;hw.niccy.isac_ale
comma
id|cs-&gt;hw.niccy.isac
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
id|cs-&gt;hw.niccy.isac_ale
comma
id|cs-&gt;hw.niccy.isac
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
id|cs-&gt;hw.niccy.isac_ale
comma
id|cs-&gt;hw.niccy.isac
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
id|cs-&gt;hw.niccy.isac_ale
comma
id|cs-&gt;hw.niccy.isac
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
id|cs-&gt;hw.niccy.hscx_ale
comma
id|cs-&gt;hw.niccy.hscx
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
id|cs-&gt;hw.niccy.hscx_ale
comma
id|cs-&gt;hw.niccy.hscx
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
id|cs-&gt;hw.niccy.hscx_ale
comma
id|cs-&gt;hw.niccy.hscx
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
id|cs-&gt;hw.niccy.hscx_ale
comma
id|cs-&gt;hw.niccy.hscx
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
r_void
DECL|function|niccy_interrupt
id|niccy_interrupt
c_func
(paren
r_int
id|intno
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|dev_id
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;subtyp
op_eq
id|NICCY_PCI
)paren
(brace
r_int
id|ival
suffix:semicolon
id|ival
op_assign
id|inl
c_func
(paren
id|cs-&gt;hw.niccy.cfg_reg
op_plus
id|PCI_IRQ_CTRL_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ival
op_amp
id|PCI_IRQ_ASSERT
)paren
)paren
multiline_comment|/* IRQ not for us (shared) */
r_return
suffix:semicolon
id|outl
c_func
(paren
id|ival
comma
id|cs-&gt;hw.niccy.cfg_reg
op_plus
id|PCI_IRQ_CTRL_REG
)paren
suffix:semicolon
)brace
id|hscxisac_irq
c_func
(paren
id|intno
comma
id|dev_id
comma
id|regs
)paren
suffix:semicolon
)brace
r_void
DECL|function|niccy_release
id|niccy_release
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
id|cs-&gt;subtyp
op_eq
id|NICCY_PCI
)paren
(brace
r_int
id|val
suffix:semicolon
id|val
op_assign
id|inl
c_func
(paren
id|cs-&gt;hw.niccy.cfg_reg
op_plus
id|PCI_IRQ_CTRL_REG
)paren
suffix:semicolon
id|val
op_and_assign
id|PCI_IRQ_DISABLE
suffix:semicolon
id|outl
c_func
(paren
id|val
comma
id|cs-&gt;hw.niccy.cfg_reg
op_plus
id|PCI_IRQ_CTRL_REG
)paren
suffix:semicolon
)brace
id|hisax_release_resources
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|niccy_reset
id|niccy_reset
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
id|cs-&gt;subtyp
op_eq
id|NICCY_PCI
)paren
(brace
r_int
id|val
suffix:semicolon
id|val
op_assign
id|inl
c_func
(paren
id|cs-&gt;hw.niccy.cfg_reg
op_plus
id|PCI_IRQ_CTRL_REG
)paren
suffix:semicolon
id|val
op_or_assign
id|PCI_IRQ_ENABLE
suffix:semicolon
id|outl
c_func
(paren
id|val
comma
id|cs-&gt;hw.niccy.cfg_reg
op_plus
id|PCI_IRQ_CTRL_REG
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|niccy_ops
r_static
r_struct
id|card_ops
id|niccy_ops
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
id|niccy_reset
comma
dot
id|release
op_assign
id|niccy_release
comma
dot
id|irq_func
op_assign
id|niccy_interrupt
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|pci_dev
op_star
id|niccy_dev
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef __ISAPNP__
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
DECL|function|setup_niccy
id|setup_niccy
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
id|niccy_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: Niccy driver Rev. %s&bslash;n&quot;
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
r_if
c_cond
(paren
(paren
id|pb
op_assign
id|isapnp_find_card
c_func
(paren
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;S&squot;
comma
l_char|&squot;D&squot;
comma
l_char|&squot;A&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x0150
)paren
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
op_logical_neg
(paren
id|pd
op_assign
id|isapnp_find_dev
c_func
(paren
id|pnp_c
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;S&squot;
comma
l_char|&squot;D&squot;
comma
l_char|&squot;A&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x0150
)paren
comma
id|pd
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NiccyPnP: PnP error card found, no device&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
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
l_string|&quot;NiccyPnP:some resources are missing %ld/%lx/%lx&bslash;n&quot;
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
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;NiccyPnP: no ISAPnP card found&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_if
c_cond
(paren
id|card-&gt;para
(braket
l_int|1
)braket
)paren
(brace
id|cs-&gt;hw.niccy.isac
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
id|ISAC_PNP
suffix:semicolon
id|cs-&gt;hw.niccy.hscx
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
id|HSCX_PNP
suffix:semicolon
id|cs-&gt;hw.niccy.isac_ale
op_assign
id|card-&gt;para
(braket
l_int|2
)braket
op_plus
id|ISAC_PNP
suffix:semicolon
id|cs-&gt;hw.niccy.hscx_ale
op_assign
id|card-&gt;para
(braket
l_int|2
)braket
op_plus
id|HSCX_PNP
suffix:semicolon
id|cs-&gt;hw.niccy.cfg_reg
op_assign
l_int|0
suffix:semicolon
id|cs-&gt;subtyp
op_assign
id|NICCY_PNP
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
id|cs-&gt;hw.niccy.isac
comma
l_int|2
comma
l_string|&quot;niccy data&quot;
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
id|cs-&gt;hw.niccy.isac_ale
comma
l_int|2
comma
l_string|&quot;niccy addr&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
)brace
r_else
(brace
macro_line|#if CONFIG_PCI
id|u_int
id|pci_ioaddr
suffix:semicolon
id|cs-&gt;subtyp
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|niccy_dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_SATSAGEM
comma
id|PCI_DEVICE_ID_SATSAGEM_NICCY
comma
id|niccy_dev
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|niccy_dev
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* get IRQ */
r_if
c_cond
(paren
op_logical_neg
id|niccy_dev-&gt;irq
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Niccy: No IRQ for PCI card found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|cs-&gt;irq
op_assign
id|niccy_dev-&gt;irq
suffix:semicolon
id|cs-&gt;hw.niccy.cfg_reg
op_assign
id|pci_resource_start
c_func
(paren
id|niccy_dev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cs-&gt;hw.niccy.cfg_reg
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Niccy: No IO-Adr for PCI cfg found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pci_ioaddr
op_assign
id|pci_resource_start
c_func
(paren
id|niccy_dev
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_ioaddr
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Niccy: No IO-Adr for PCI card found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|cs-&gt;subtyp
op_assign
id|NICCY_PCI
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Niccy: No PCI card found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|cs-&gt;irq_flags
op_or_assign
id|SA_SHIRQ
suffix:semicolon
id|cs-&gt;hw.niccy.isac
op_assign
id|pci_ioaddr
op_plus
id|ISAC_PCI_DATA
suffix:semicolon
id|cs-&gt;hw.niccy.isac_ale
op_assign
id|pci_ioaddr
op_plus
id|ISAC_PCI_ADDR
suffix:semicolon
id|cs-&gt;hw.niccy.hscx
op_assign
id|pci_ioaddr
op_plus
id|HSCX_PCI_DATA
suffix:semicolon
id|cs-&gt;hw.niccy.hscx_ale
op_assign
id|pci_ioaddr
op_plus
id|HSCX_PCI_ADDR
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
id|cs-&gt;hw.niccy.isac
comma
l_int|4
comma
l_string|&quot;niccy&quot;
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
id|cs-&gt;hw.niccy.cfg_reg
comma
l_int|0x40
comma
l_string|&quot;niccy pci&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
macro_line|#endif /* CONFIG_PCI */
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: %s %s config irq:%d data:0x%X ale:0x%X&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
(paren
id|cs-&gt;subtyp
op_eq
l_int|1
)paren
ques
c_cond
l_string|&quot;PnP&quot;
suffix:colon
l_string|&quot;PCI&quot;
comma
id|cs-&gt;irq
comma
id|cs-&gt;hw.niccy.isac
comma
id|cs-&gt;hw.niccy.isac_ale
)paren
suffix:semicolon
id|cs-&gt;card_ops
op_assign
op_amp
id|niccy_ops
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
id|niccy_release
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
