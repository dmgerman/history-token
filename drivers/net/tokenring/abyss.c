multiline_comment|/*&n; *  abyss.c: Network driver for the Madge Smart 16/4 PCI Mk2 token ring card.&n; *&n; *  Written 1999-2000 by Adam Fritzler&n; *&n; *  This software may be used and distributed according to the terms&n; *  of the GNU General Public License, incorporated herein by reference.&n; *&n; *  This driver module supports the following cards:&n; *      - Madge Smart 16/4 PCI Mk2&n; *&n; *  Maintainer(s):&n; *    AF&t;Adam Fritzler&t;&t;mid@auk.cx&n; *&n; *  Modification History:&n; *&t;30-Dec-99&t;AF&t;Split off from the tms380tr driver.&n; *&t;22-Jan-00&t;AF&t;Updated to use indirect read/writes &n; *&t;23-Nov-00&t;JG&t;New PCI API, cleanups&n; *&n; *&n; *  TODO:&n; *&t;1. See if we can use MMIO instead of inb/outb/inw/outw&n; *&t;2. Add support for Mk1 (has AT24 attached to the PCI&n; *&t;&t;config registers)&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/trdevice.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;tms380tr.h&quot;
macro_line|#include &quot;abyss.h&quot;            /* Madge-specific constants */
DECL|variable|__devinitdata
r_static
r_char
id|version
(braket
)braket
id|__devinitdata
op_assign
l_string|&quot;abyss.c: v1.02 23/11/2000 by Adam Fritzler&bslash;n&quot;
suffix:semicolon
DECL|macro|ABYSS_IO_EXTENT
mdefine_line|#define ABYSS_IO_EXTENT 64
DECL|variable|abyss_pci_tbl
r_static
r_struct
id|pci_device_id
id|abyss_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_MADGE
comma
id|PCI_DEVICE_ID_MADGE_MK2
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|PCI_CLASS_NETWORK_TOKEN_RING
op_lshift
l_int|8
comma
l_int|0x00ffffff
comma
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|abyss_pci_tbl
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
r_static
r_int
id|abyss_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|abyss_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|abyss_enable
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|abyss_chipset_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|abyss_read_eeprom
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
r_int
id|abyss_setnselout_pins
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|at24_writedatabyte
c_func
(paren
r_int
r_int
id|regaddr
comma
r_int
r_char
id|byte
)paren
suffix:semicolon
r_static
r_int
id|at24_sendfullcmd
c_func
(paren
r_int
r_int
id|regaddr
comma
r_int
r_char
id|cmd
comma
r_int
r_char
id|addr
)paren
suffix:semicolon
r_static
r_int
id|at24_sendcmd
c_func
(paren
r_int
r_int
id|regaddr
comma
r_int
r_char
id|cmd
)paren
suffix:semicolon
r_static
r_int
r_char
id|at24_readdatabit
c_func
(paren
r_int
r_int
id|regaddr
)paren
suffix:semicolon
r_static
r_int
r_char
id|at24_readdatabyte
c_func
(paren
r_int
r_int
id|regaddr
)paren
suffix:semicolon
r_static
r_int
id|at24_waitforack
c_func
(paren
r_int
r_int
id|regaddr
)paren
suffix:semicolon
r_static
r_int
id|at24_waitfornack
c_func
(paren
r_int
r_int
id|regaddr
)paren
suffix:semicolon
r_static
r_void
id|at24_setlines
c_func
(paren
r_int
r_int
id|regaddr
comma
r_int
r_char
id|clock
comma
r_int
r_char
id|data
)paren
suffix:semicolon
r_static
r_void
id|at24_start
c_func
(paren
r_int
r_int
id|regaddr
)paren
suffix:semicolon
r_static
r_int
r_char
id|at24_readb
c_func
(paren
r_int
r_int
id|regaddr
comma
r_int
r_char
id|addr
)paren
suffix:semicolon
DECL|function|abyss_sifreadb
r_static
r_int
r_int
id|abyss_sifreadb
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|reg
)paren
(brace
r_return
id|inb
c_func
(paren
id|dev-&gt;base_addr
op_plus
id|reg
)paren
suffix:semicolon
)brace
DECL|function|abyss_sifreadw
r_static
r_int
r_int
id|abyss_sifreadw
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|reg
)paren
(brace
r_return
id|inw
c_func
(paren
id|dev-&gt;base_addr
op_plus
id|reg
)paren
suffix:semicolon
)brace
DECL|function|abyss_sifwriteb
r_static
r_void
id|abyss_sifwriteb
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|val
comma
r_int
r_int
id|reg
)paren
(brace
id|outb
c_func
(paren
id|val
comma
id|dev-&gt;base_addr
op_plus
id|reg
)paren
suffix:semicolon
)brace
DECL|function|abyss_sifwritew
r_static
r_void
id|abyss_sifwritew
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|val
comma
r_int
r_int
id|reg
)paren
(brace
id|outw
c_func
(paren
id|val
comma
id|dev-&gt;base_addr
op_plus
id|reg
)paren
suffix:semicolon
)brace
DECL|function|abyss_attach
r_static
r_int
id|__devinit
id|abyss_attach
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
(brace
r_static
r_int
id|versionprinted
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_struct
id|net_local
op_star
id|tp
suffix:semicolon
r_int
id|i
comma
id|ret
comma
id|pci_irq_line
suffix:semicolon
r_int
r_int
id|pci_ioaddr
suffix:semicolon
r_if
c_cond
(paren
id|versionprinted
op_increment
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|version
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|pdev
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* Remove I/O space marker in bit 0. */
id|pci_irq_line
op_assign
id|pdev-&gt;irq
suffix:semicolon
id|pci_ioaddr
op_assign
id|pci_resource_start
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* At this point we have found a valid card. */
id|dev
op_assign
id|alloc_trdev
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|pci_ioaddr
comma
id|ABYSS_IO_EXTENT
comma
id|dev-&gt;name
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|err_out_trdev
suffix:semicolon
)brace
id|ret
op_assign
id|request_irq
c_func
(paren
id|pdev-&gt;irq
comma
id|tms380tr_interrupt
comma
id|SA_SHIRQ
comma
id|dev-&gt;name
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|err_out_region
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|pci_ioaddr
suffix:semicolon
id|dev-&gt;irq
op_assign
id|pci_irq_line
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: Madge Smart 16/4 PCI Mk2 (Abyss)&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s:    IO: %#4lx  IRQ: %d&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|pci_ioaddr
comma
id|dev-&gt;irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The TMS SIF registers lay 0x10 above the card base address.&n;&t; */
id|dev-&gt;base_addr
op_add_assign
l_int|0x10
suffix:semicolon
id|ret
op_assign
id|tmsdev_init
c_func
(paren
id|dev
comma
id|PCI_MAX_ADDRESS
comma
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: unable to get memory for dev-&gt;priv.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_goto
id|err_out_irq
suffix:semicolon
)brace
id|abyss_read_eeprom
c_func
(paren
id|dev
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s:    Ring Station Address: &quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%2.2x&quot;
comma
id|dev-&gt;dev_addr
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;:%2.2x&quot;
comma
id|dev-&gt;dev_addr
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|tp
op_assign
id|dev-&gt;priv
suffix:semicolon
id|tp-&gt;setnselout
op_assign
id|abyss_setnselout_pins
suffix:semicolon
id|tp-&gt;sifreadb
op_assign
id|abyss_sifreadb
suffix:semicolon
id|tp-&gt;sifreadw
op_assign
id|abyss_sifreadw
suffix:semicolon
id|tp-&gt;sifwriteb
op_assign
id|abyss_sifwriteb
suffix:semicolon
id|tp-&gt;sifwritew
op_assign
id|abyss_sifwritew
suffix:semicolon
id|memcpy
c_func
(paren
id|tp-&gt;ProductID
comma
l_string|&quot;Madge PCI 16/4 Mk2&quot;
comma
id|PROD_ID_SIZE
op_plus
l_int|1
)paren
suffix:semicolon
id|dev-&gt;open
op_assign
id|abyss_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|abyss_close
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|pdev
comma
id|dev
)paren
suffix:semicolon
id|ret
op_assign
id|register_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|err_out_tmsdev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_out_tmsdev
suffix:colon
id|pci_set_drvdata
c_func
(paren
id|pdev
comma
l_int|NULL
)paren
suffix:semicolon
id|tmsdev_term
c_func
(paren
id|dev
)paren
suffix:semicolon
id|err_out_irq
suffix:colon
id|free_irq
c_func
(paren
id|pdev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|err_out_region
suffix:colon
id|release_region
c_func
(paren
id|pci_ioaddr
comma
id|ABYSS_IO_EXTENT
)paren
suffix:semicolon
id|err_out_trdev
suffix:colon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|abyss_setnselout_pins
r_static
r_int
r_int
id|abyss_setnselout_pins
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
r_int
id|val
op_assign
l_int|0
suffix:semicolon
r_struct
id|net_local
op_star
id|tp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;DataRate
op_eq
id|SPEED_4
)paren
(brace
id|val
op_or_assign
l_int|0x01
suffix:semicolon
)brace
multiline_comment|/* Set 4Mbps */
r_else
id|val
op_or_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Set 16Mbps */
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/*&n; * The following Madge boards should use this code:&n; *   - Smart 16/4 PCI Mk2 (Abyss)&n; *   - Smart 16/4 PCI Mk1 (PCI T)&n; *   - Smart 16/4 Client Plus PnP (Big Apple)&n; *   - Smart 16/4 Cardbus Mk2&n; *&n; * These access an Atmel AT24 SEEPROM using their glue chip registers. &n; *&n; */
DECL|function|at24_writedatabyte
r_static
r_void
id|at24_writedatabyte
c_func
(paren
r_int
r_int
id|regaddr
comma
r_int
r_char
id|byte
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|at24_setlines
c_func
(paren
id|regaddr
comma
l_int|0
comma
(paren
id|byte
op_rshift
(paren
l_int|7
op_minus
id|i
)paren
)paren
op_amp
l_int|0x01
)paren
suffix:semicolon
id|at24_setlines
c_func
(paren
id|regaddr
comma
l_int|1
comma
(paren
id|byte
op_rshift
(paren
l_int|7
op_minus
id|i
)paren
)paren
op_amp
l_int|0x01
)paren
suffix:semicolon
id|at24_setlines
c_func
(paren
id|regaddr
comma
l_int|0
comma
(paren
id|byte
op_rshift
(paren
l_int|7
op_minus
id|i
)paren
)paren
op_amp
l_int|0x01
)paren
suffix:semicolon
)brace
)brace
DECL|function|at24_sendfullcmd
r_static
r_int
id|at24_sendfullcmd
c_func
(paren
r_int
r_int
id|regaddr
comma
r_int
r_char
id|cmd
comma
r_int
r_char
id|addr
)paren
(brace
r_if
c_cond
(paren
id|at24_sendcmd
c_func
(paren
id|regaddr
comma
id|cmd
)paren
)paren
(brace
id|at24_writedatabyte
c_func
(paren
id|regaddr
comma
id|addr
)paren
suffix:semicolon
r_return
id|at24_waitforack
c_func
(paren
id|regaddr
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|at24_sendcmd
r_static
r_int
id|at24_sendcmd
c_func
(paren
r_int
r_int
id|regaddr
comma
r_int
r_char
id|cmd
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|10
suffix:semicolon
id|i
op_increment
)paren
(brace
id|at24_start
c_func
(paren
id|regaddr
)paren
suffix:semicolon
id|at24_writedatabyte
c_func
(paren
id|regaddr
comma
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|at24_waitforack
c_func
(paren
id|regaddr
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|at24_readdatabit
r_static
r_int
r_char
id|at24_readdatabit
c_func
(paren
r_int
r_int
id|regaddr
)paren
(brace
r_int
r_char
id|val
suffix:semicolon
id|at24_setlines
c_func
(paren
id|regaddr
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|at24_setlines
c_func
(paren
id|regaddr
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|val
op_assign
(paren
id|inb
c_func
(paren
id|regaddr
)paren
op_amp
id|AT24_DATA
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|at24_setlines
c_func
(paren
id|regaddr
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|at24_setlines
c_func
(paren
id|regaddr
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|at24_readdatabyte
r_static
r_int
r_char
id|at24_readdatabyte
c_func
(paren
r_int
r_int
id|regaddr
)paren
(brace
r_int
r_char
id|data
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|data
op_lshift_assign
l_int|1
suffix:semicolon
id|data
op_or_assign
id|at24_readdatabit
c_func
(paren
id|regaddr
)paren
suffix:semicolon
)brace
r_return
id|data
suffix:semicolon
)brace
DECL|function|at24_waitforack
r_static
r_int
id|at24_waitforack
c_func
(paren
r_int
r_int
id|regaddr
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|10
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|at24_readdatabit
c_func
(paren
id|regaddr
)paren
op_amp
l_int|0x01
)paren
op_eq
l_int|0x00
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|at24_waitfornack
r_static
r_int
id|at24_waitfornack
c_func
(paren
r_int
r_int
id|regaddr
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|10
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|at24_readdatabit
c_func
(paren
id|regaddr
)paren
op_amp
l_int|0x01
)paren
op_eq
l_int|0x01
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|at24_setlines
r_static
r_void
id|at24_setlines
c_func
(paren
r_int
r_int
id|regaddr
comma
r_int
r_char
id|clock
comma
r_int
r_char
id|data
)paren
(brace
r_int
r_char
id|val
op_assign
id|AT24_ENABLE
suffix:semicolon
r_if
c_cond
(paren
id|clock
)paren
id|val
op_or_assign
id|AT24_CLOCK
suffix:semicolon
r_if
c_cond
(paren
id|data
)paren
id|val
op_or_assign
id|AT24_DATA
suffix:semicolon
id|outb
c_func
(paren
id|val
comma
id|regaddr
)paren
suffix:semicolon
id|tms380tr_wait
c_func
(paren
l_int|20
)paren
suffix:semicolon
multiline_comment|/* Very necessary. */
)brace
DECL|function|at24_start
r_static
r_void
id|at24_start
c_func
(paren
r_int
r_int
id|regaddr
)paren
(brace
id|at24_setlines
c_func
(paren
id|regaddr
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|at24_setlines
c_func
(paren
id|regaddr
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|at24_setlines
c_func
(paren
id|regaddr
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|at24_setlines
c_func
(paren
id|regaddr
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|at24_readb
r_static
r_int
r_char
id|at24_readb
c_func
(paren
r_int
r_int
id|regaddr
comma
r_int
r_char
id|addr
)paren
(brace
r_int
r_char
id|data
op_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|at24_sendfullcmd
c_func
(paren
id|regaddr
comma
id|AT24_WRITE
comma
id|addr
)paren
)paren
(brace
r_if
c_cond
(paren
id|at24_sendcmd
c_func
(paren
id|regaddr
comma
id|AT24_READ
)paren
)paren
(brace
id|data
op_assign
id|at24_readdatabyte
c_func
(paren
id|regaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|at24_waitfornack
c_func
(paren
id|regaddr
)paren
)paren
id|data
op_assign
l_int|0xff
suffix:semicolon
)brace
)brace
r_return
id|data
suffix:semicolon
)brace
multiline_comment|/*&n; * Enable basic functions of the Madge chipset needed&n; * for initialization.&n; */
DECL|function|abyss_enable
r_static
r_void
id|abyss_enable
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
r_char
id|reset_reg
suffix:semicolon
r_int
r_int
id|ioaddr
suffix:semicolon
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|reset_reg
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|PCIBM2_RESET_REG
)paren
suffix:semicolon
id|reset_reg
op_or_assign
id|PCIBM2_RESET_REG_CHIP_NRES
suffix:semicolon
id|outb
c_func
(paren
id|reset_reg
comma
id|ioaddr
op_plus
id|PCIBM2_RESET_REG
)paren
suffix:semicolon
id|tms380tr_wait
c_func
(paren
l_int|100
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Enable the functions of the Madge chipset needed for&n; * full working order. &n; */
DECL|function|abyss_chipset_init
r_static
r_int
id|abyss_chipset_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
r_char
id|reset_reg
suffix:semicolon
r_int
r_int
id|ioaddr
suffix:semicolon
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|reset_reg
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|PCIBM2_RESET_REG
)paren
suffix:semicolon
id|reset_reg
op_or_assign
id|PCIBM2_RESET_REG_CHIP_NRES
suffix:semicolon
id|outb
c_func
(paren
id|reset_reg
comma
id|ioaddr
op_plus
id|PCIBM2_RESET_REG
)paren
suffix:semicolon
id|reset_reg
op_and_assign
op_complement
(paren
id|PCIBM2_RESET_REG_CHIP_NRES
op_or
id|PCIBM2_RESET_REG_FIFO_NRES
op_or
id|PCIBM2_RESET_REG_SIF_NRES
)paren
suffix:semicolon
id|outb
c_func
(paren
id|reset_reg
comma
id|ioaddr
op_plus
id|PCIBM2_RESET_REG
)paren
suffix:semicolon
id|tms380tr_wait
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|reset_reg
op_or_assign
id|PCIBM2_RESET_REG_CHIP_NRES
suffix:semicolon
id|outb
c_func
(paren
id|reset_reg
comma
id|ioaddr
op_plus
id|PCIBM2_RESET_REG
)paren
suffix:semicolon
id|reset_reg
op_or_assign
id|PCIBM2_RESET_REG_SIF_NRES
suffix:semicolon
id|outb
c_func
(paren
id|reset_reg
comma
id|ioaddr
op_plus
id|PCIBM2_RESET_REG
)paren
suffix:semicolon
id|reset_reg
op_or_assign
id|PCIBM2_RESET_REG_FIFO_NRES
suffix:semicolon
id|outb
c_func
(paren
id|reset_reg
comma
id|ioaddr
op_plus
id|PCIBM2_RESET_REG
)paren
suffix:semicolon
id|outb
c_func
(paren
id|PCIBM2_INT_CONTROL_REG_SINTEN
op_or
id|PCIBM2_INT_CONTROL_REG_PCI_ERR_ENABLE
comma
id|ioaddr
op_plus
id|PCIBM2_INT_CONTROL_REG
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|30
comma
id|ioaddr
op_plus
id|PCIBM2_FIFO_THRESHOLD
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|abyss_chipset_close
r_static
r_inline
r_void
id|abyss_chipset_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
r_int
id|ioaddr
suffix:semicolon
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|PCIBM2_RESET_REG
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read configuration data from the AT24 SEEPROM on Madge cards.&n; *&n; */
DECL|function|abyss_read_eeprom
r_static
r_void
id|abyss_read_eeprom
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|net_local
op_star
id|tp
suffix:semicolon
r_int
r_int
id|ioaddr
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
r_int
id|i
suffix:semicolon
id|tp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
multiline_comment|/* Must enable glue chip first */
id|abyss_enable
c_func
(paren
id|dev
)paren
suffix:semicolon
id|val
op_assign
id|at24_readb
c_func
(paren
id|ioaddr
op_plus
id|PCIBM2_SEEPROM_REG
comma
id|PCIBM2_SEEPROM_RING_SPEED
)paren
suffix:semicolon
id|tp-&gt;DataRate
op_assign
id|val
ques
c_cond
id|SPEED_4
suffix:colon
id|SPEED_16
suffix:semicolon
multiline_comment|/* set open speed */
id|printk
c_func
(paren
l_string|&quot;%s:    SEEPROM: ring speed: %dMb/sec&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|tp-&gt;DataRate
)paren
suffix:semicolon
id|val
op_assign
id|at24_readb
c_func
(paren
id|ioaddr
op_plus
id|PCIBM2_SEEPROM_REG
comma
id|PCIBM2_SEEPROM_RAM_SIZE
)paren
op_star
l_int|128
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s:    SEEPROM: adapter RAM: %dkb&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|val
)paren
suffix:semicolon
id|dev-&gt;addr_len
op_assign
l_int|6
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|at24_readb
c_func
(paren
id|ioaddr
op_plus
id|PCIBM2_SEEPROM_REG
comma
id|PCIBM2_SEEPROM_BIA
op_plus
id|i
)paren
suffix:semicolon
)brace
DECL|function|abyss_open
r_static
r_int
id|abyss_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|abyss_chipset_init
c_func
(paren
id|dev
)paren
suffix:semicolon
id|tms380tr_open
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|abyss_close
r_static
r_int
id|abyss_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|tms380tr_close
c_func
(paren
id|dev
)paren
suffix:semicolon
id|abyss_chipset_close
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|abyss_detach
r_static
r_void
id|__devexit
id|abyss_detach
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|pci_get_drvdata
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|dev-&gt;base_addr
op_minus
l_int|0x10
comma
id|ABYSS_IO_EXTENT
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|tmsdev_term
c_func
(paren
id|dev
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|pdev
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|abyss_driver
r_static
r_struct
id|pci_driver
id|abyss_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;abyss&quot;
comma
dot
id|id_table
op_assign
id|abyss_pci_tbl
comma
dot
id|probe
op_assign
id|abyss_attach
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|abyss_detach
)paren
comma
)brace
suffix:semicolon
DECL|function|abyss_init
r_static
r_int
id|__init
id|abyss_init
(paren
r_void
)paren
(brace
r_int
id|rc
op_assign
id|pci_register_driver
(paren
op_amp
id|abyss_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
r_return
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
(brace
id|pci_unregister_driver
(paren
op_amp
id|abyss_driver
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|abyss_rmmod
r_static
r_void
id|__exit
id|abyss_rmmod
(paren
r_void
)paren
(brace
id|pci_unregister_driver
(paren
op_amp
id|abyss_driver
)paren
suffix:semicolon
)brace
DECL|variable|abyss_init
id|module_init
c_func
(paren
id|abyss_init
)paren
suffix:semicolon
DECL|variable|abyss_rmmod
id|module_exit
c_func
(paren
id|abyss_rmmod
)paren
suffix:semicolon
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  compile-command: &quot;gcc -DMODVERSIONS  -DMODULE -D__KERNEL__ -Wall -Wstrict-prototypes -O6 -fomit-frame-pointer -I/usr/src/linux/drivers/net/tokenring/ -c abyss.c&quot;&n; *  alt-compile-command: &quot;gcc -DMODULE -D__KERNEL__ -Wall -Wstrict-prototypes -O6 -fomit-frame-pointer -I/usr/src/linux/drivers/net/tokenring/ -c abyss.c&quot;&n; *  c-set-style &quot;K&amp;R&quot;&n; *  c-indent-level: 8&n; *  c-basic-offset: 8&n; *  tab-width: 8&n; * End:&n; */
eof
