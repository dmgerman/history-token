multiline_comment|/* $Id: telespci.c,v 2.16.6.5 2001/09/23 22:24:52 kai Exp $&n; *&n; * low level stuff for Teles PCI isdn cards&n; *&n; * Author       Ton van Rosmalen&n; *              Karsten Keil&n; * Copyright    by Ton van Rosmalen&n; *              by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;hscx.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
macro_line|#include &lt;linux/pci.h&gt;
r_extern
r_const
r_char
op_star
id|CardType
(braket
)braket
suffix:semicolon
DECL|variable|telespci_revision
r_const
r_char
op_star
id|telespci_revision
op_assign
l_string|&quot;$Revision: 2.16.6.5 $&quot;
suffix:semicolon
DECL|macro|ZORAN_PO_RQ_PEN
mdefine_line|#define ZORAN_PO_RQ_PEN&t;0x02000000
DECL|macro|ZORAN_PO_WR
mdefine_line|#define ZORAN_PO_WR&t;0x00800000
DECL|macro|ZORAN_PO_GID0
mdefine_line|#define ZORAN_PO_GID0&t;0x00000000
DECL|macro|ZORAN_PO_GID1
mdefine_line|#define ZORAN_PO_GID1&t;0x00100000
DECL|macro|ZORAN_PO_GREG0
mdefine_line|#define ZORAN_PO_GREG0&t;0x00000000
DECL|macro|ZORAN_PO_GREG1
mdefine_line|#define ZORAN_PO_GREG1&t;0x00010000
DECL|macro|ZORAN_PO_DMASK
mdefine_line|#define ZORAN_PO_DMASK&t;0xFF
DECL|macro|WRITE_ADDR_ISAC
mdefine_line|#define WRITE_ADDR_ISAC&t;(ZORAN_PO_WR | ZORAN_PO_GID0 | ZORAN_PO_GREG0)
DECL|macro|READ_DATA_ISAC
mdefine_line|#define READ_DATA_ISAC&t;(ZORAN_PO_GID0 | ZORAN_PO_GREG1)
DECL|macro|WRITE_DATA_ISAC
mdefine_line|#define WRITE_DATA_ISAC&t;(ZORAN_PO_WR | ZORAN_PO_GID0 | ZORAN_PO_GREG1)
DECL|macro|WRITE_ADDR_HSCX
mdefine_line|#define WRITE_ADDR_HSCX&t;(ZORAN_PO_WR | ZORAN_PO_GID1 | ZORAN_PO_GREG0)
DECL|macro|READ_DATA_HSCX
mdefine_line|#define READ_DATA_HSCX&t;(ZORAN_PO_GID1 | ZORAN_PO_GREG1)
DECL|macro|WRITE_DATA_HSCX
mdefine_line|#define WRITE_DATA_HSCX&t;(ZORAN_PO_WR | ZORAN_PO_GID1 | ZORAN_PO_GREG1)
DECL|macro|ZORAN_WAIT_NOBUSY
mdefine_line|#define ZORAN_WAIT_NOBUSY&t;do { &bslash;&n;&t;&t;&t;&t;&t;portdata = readl(adr); &bslash;&n;&t;&t;&t;&t;} while (portdata &amp; ZORAN_PO_RQ_PEN)
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
id|off
)paren
(brace
r_void
op_star
id|adr
op_assign
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x200
suffix:semicolon
r_int
r_int
id|portdata
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
multiline_comment|/* set address for ISAC */
id|writel
c_func
(paren
id|WRITE_ADDR_ISAC
op_or
id|off
comma
id|adr
)paren
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
multiline_comment|/* read data from ISAC */
id|writel
c_func
(paren
id|READ_DATA_ISAC
comma
id|adr
)paren
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
r_return
(paren
id|u8
)paren
(paren
id|portdata
op_amp
id|ZORAN_PO_DMASK
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
id|off
comma
id|u8
id|data
)paren
(brace
r_void
op_star
id|adr
op_assign
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x200
suffix:semicolon
r_int
r_int
id|portdata
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
multiline_comment|/* set address for ISAC */
id|writel
c_func
(paren
id|WRITE_ADDR_ISAC
op_or
id|off
comma
id|adr
)paren
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
multiline_comment|/* write data to ISAC */
id|writel
c_func
(paren
id|WRITE_DATA_ISAC
op_or
id|data
comma
id|adr
)paren
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
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
r_void
op_star
id|adr
op_assign
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x200
suffix:semicolon
r_int
r_int
id|portdata
suffix:semicolon
r_int
id|i
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
multiline_comment|/* read data from ISAC */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* set address for ISAC fifo */
id|writel
c_func
(paren
id|WRITE_ADDR_ISAC
op_or
l_int|0x1E
comma
id|adr
)paren
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
id|writel
c_func
(paren
id|READ_DATA_ISAC
comma
id|adr
)paren
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
id|data
(braket
id|i
)braket
op_assign
(paren
id|u8
)paren
(paren
id|portdata
op_amp
id|ZORAN_PO_DMASK
)paren
suffix:semicolon
)brace
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
r_void
op_star
id|adr
op_assign
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x200
suffix:semicolon
r_int
r_int
id|portdata
suffix:semicolon
r_int
id|i
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
multiline_comment|/* write data to ISAC */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* set address for ISAC fifo */
id|writel
c_func
(paren
id|WRITE_ADDR_ISAC
op_or
l_int|0x1E
comma
id|adr
)paren
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
id|writel
c_func
(paren
id|WRITE_DATA_ISAC
op_or
id|data
(braket
id|i
)braket
comma
id|adr
)paren
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
)brace
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
id|off
)paren
(brace
r_void
op_star
id|adr
op_assign
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x200
suffix:semicolon
r_int
r_int
id|portdata
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
multiline_comment|/* set address for HSCX */
id|writel
c_func
(paren
id|WRITE_ADDR_HSCX
op_or
(paren
(paren
id|hscx
ques
c_cond
l_int|0x40
suffix:colon
l_int|0
)paren
op_plus
id|off
)paren
comma
id|adr
)paren
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
multiline_comment|/* read data from HSCX */
id|writel
c_func
(paren
id|READ_DATA_HSCX
comma
id|adr
)paren
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
r_return
(paren
(paren
id|u8
)paren
(paren
id|portdata
op_amp
id|ZORAN_PO_DMASK
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
id|off
comma
id|u8
id|data
)paren
(brace
r_void
op_star
id|adr
op_assign
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x200
suffix:semicolon
r_int
r_int
id|portdata
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
multiline_comment|/* set address for HSCX */
id|writel
c_func
(paren
id|WRITE_ADDR_HSCX
op_or
(paren
(paren
id|hscx
ques
c_cond
l_int|0x40
suffix:colon
l_int|0
)paren
op_plus
id|off
)paren
comma
id|adr
)paren
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
multiline_comment|/* write data to HSCX */
id|writel
c_func
(paren
id|WRITE_DATA_HSCX
op_or
id|data
comma
id|adr
)paren
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
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
r_void
op_star
id|adr
op_assign
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x200
suffix:semicolon
r_int
r_int
id|portdata
suffix:semicolon
r_int
id|i
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
multiline_comment|/* read data from HSCX */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* set address for HSCX fifo */
id|writel
c_func
(paren
id|WRITE_ADDR_HSCX
op_or
(paren
id|hscx
ques
c_cond
l_int|0x5F
suffix:colon
l_int|0x1F
)paren
comma
id|adr
)paren
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
id|writel
c_func
(paren
id|READ_DATA_HSCX
comma
id|adr
)paren
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
id|data
(braket
id|i
)braket
op_assign
(paren
id|u8
)paren
(paren
id|portdata
op_amp
id|ZORAN_PO_DMASK
)paren
suffix:semicolon
)brace
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
r_void
op_star
id|adr
op_assign
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x200
suffix:semicolon
r_int
r_int
id|portdata
suffix:semicolon
r_int
id|i
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
multiline_comment|/* write data to HSCX */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* set address for HSCX fifo */
id|writel
c_func
(paren
id|WRITE_ADDR_HSCX
op_or
(paren
id|hscx
ques
c_cond
l_int|0x5F
suffix:colon
l_int|0x1F
)paren
comma
id|adr
)paren
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
id|writel
c_func
(paren
id|WRITE_DATA_HSCX
op_or
id|data
(braket
id|i
)braket
comma
id|adr
)paren
suffix:semicolon
id|ZORAN_WAIT_NOBUSY
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
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
DECL|function|telespci_interrupt
id|telespci_interrupt
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
DECL|macro|MAXCOUNT
mdefine_line|#define MAXCOUNT 20
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|dev_id
suffix:semicolon
id|u8
id|val
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cs-&gt;lock
)paren
suffix:semicolon
id|val
op_assign
id|hscx_read
c_func
(paren
id|cs
comma
l_int|1
comma
id|HSCX_ISTA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
id|hscx_int_main
c_func
(paren
id|cs
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
r_if
c_cond
(paren
id|val
)paren
id|isac_interrupt
c_func
(paren
id|cs
comma
id|val
)paren
suffix:semicolon
multiline_comment|/* Clear interrupt register for Zoran PCI controller */
id|writel
c_func
(paren
l_int|0x70000000
comma
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x3C
)paren
suffix:semicolon
id|hscx_write
c_func
(paren
id|cs
comma
l_int|0
comma
id|HSCX_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|hscx_write
c_func
(paren
id|cs
comma
l_int|1
comma
id|HSCX_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
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
id|hscx_write
c_func
(paren
id|cs
comma
l_int|0
comma
id|HSCX_MASK
comma
l_int|0x0
)paren
suffix:semicolon
id|hscx_write
c_func
(paren
id|cs
comma
l_int|1
comma
id|HSCX_MASK
comma
l_int|0x0
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cs-&gt;lock
)paren
suffix:semicolon
)brace
DECL|variable|telespci_ops
r_static
r_struct
id|card_ops
id|telespci_ops
op_assign
(brace
dot
id|init
op_assign
id|inithscxisac
comma
dot
id|release
op_assign
id|hisax_release_resources
comma
dot
id|irq_func
op_assign
id|telespci_interrupt
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|pci_dev
op_star
id|dev_tel
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
r_int
id|__init
DECL|function|setup_telespci
id|setup_telespci
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
macro_line|#ifdef __BIG_ENDIAN
macro_line|#error &quot;not running on big endian machines now&quot;
macro_line|#endif
id|strcpy
c_func
(paren
id|tmp
comma
id|telespci_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: Teles/PCI driver Rev. %s&bslash;n&quot;
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
id|dev_tel
op_assign
id|pci_find_device
(paren
id|PCI_VENDOR_ID_ZORAN
comma
id|PCI_DEVICE_ID_ZORAN_36120
comma
id|dev_tel
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
id|dev_tel
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|cs-&gt;irq
op_assign
id|dev_tel-&gt;irq
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cs-&gt;irq
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Teles: No IRQ for PCI card found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|cs-&gt;hw.teles0.membase
op_assign
id|request_mmio
c_func
(paren
op_amp
id|cs-&gt;rs
comma
id|pci_resource_start
c_func
(paren
id|dev_tel
comma
l_int|0
)paren
comma
l_int|4096
comma
l_string|&quot;telespci&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cs-&gt;hw.teles0.membase
)paren
r_goto
id|err
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Found: Zoran, base-address: 0x%lx, irq: 0x%x&bslash;n&quot;
comma
id|pci_resource_start
c_func
(paren
id|dev_tel
comma
l_int|0
)paren
comma
id|dev_tel-&gt;irq
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;TelesPCI: No PCI card found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Initialize Zoran PCI controller */
id|writel
c_func
(paren
l_int|0x00000000
comma
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x28
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0x01000000
comma
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x28
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0x01000000
comma
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x28
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0x7BFFFFFF
comma
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x2C
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0x70000000
comma
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x3C
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0x61000000
comma
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* writel(0x00800000, cs-&gt;hw.teles0.membase + 0x200); */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: %s config irq:%d mem:%p&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
id|cs-&gt;irq
comma
id|cs-&gt;hw.teles0.membase
)paren
suffix:semicolon
id|cs-&gt;irq_flags
op_or_assign
id|SA_SHIRQ
suffix:semicolon
id|cs-&gt;card_ops
op_assign
op_amp
id|telespci_ops
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
