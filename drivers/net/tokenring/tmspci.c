multiline_comment|/*&n; *  tmspci.c: A generic network driver for TMS380-based PCI token ring cards.&n; *&n; *  Written 1999 by Adam Fritzler&n; *&n; *  This software may be used and distributed according to the terms&n; *  of the GNU General Public License, incorporated herein by reference.&n; *&n; *  This driver module supports the following cards:&n; *&t;- SysKonnect TR4/16(+) PCI&t;(SK-4590)&n; *&t;- SysKonnect TR4/16 PCI&t;&t;(SK-4591)&n; *      - Compaq TR 4/16 PCI&n; *      - Thomas-Conrad TC4048 4/16 PCI &n; *      - 3Com 3C339 Token Link Velocity&n; *&n; *  Maintainer(s):&n; *    AF&t;Adam Fritzler&t;&t;mid@auk.cx&n; *&n; *  Modification History:&n; *&t;30-Dec-99&t;AF&t;Split off from the tms380tr driver.&n; *&t;22-Jan-00&t;AF&t;Updated to use indirect read/writes&n; *&t;23-Nov-00&t;JG&t;New PCI API, cleanups&n; *&n; *  TODO:&n; *&t;1. See if we can use MMIO instead of port accesses&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/trdevice.h&gt;
macro_line|#include &quot;tms380tr.h&quot;
DECL|variable|__initdata
r_static
r_char
id|version
(braket
)braket
id|__initdata
op_assign
l_string|&quot;tmspci.c: v1.02 23/11/2000 by Adam Fritzler&bslash;n&quot;
suffix:semicolon
DECL|macro|TMS_PCI_IO_EXTENT
mdefine_line|#define TMS_PCI_IO_EXTENT 32
DECL|struct|card_info
r_struct
id|card_info
(brace
DECL|member|nselout
r_int
r_char
id|nselout
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* NSELOUT vals for 4mb([0]) and 16mb([1]) */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|card_info_table
r_static
r_struct
id|card_info
id|card_info_table
(braket
)braket
op_assign
(brace
(brace
(brace
l_int|0x03
comma
l_int|0x01
)brace
comma
l_string|&quot;Compaq 4/16 TR PCI&quot;
)brace
comma
(brace
(brace
l_int|0x03
comma
l_int|0x01
)brace
comma
l_string|&quot;SK NET TR 4/16 PCI&quot;
)brace
comma
(brace
(brace
l_int|0x03
comma
l_int|0x01
)brace
comma
l_string|&quot;Thomas-Conrad TC4048 PCI 4/16&quot;
)brace
comma
(brace
(brace
l_int|0x03
comma
l_int|0x01
)brace
comma
l_string|&quot;3Com Token Link Velocity&quot;
)brace
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|pci_device_id
id|tmspci_pci_tbl
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|PCI_VENDOR_ID_COMPAQ
comma
id|PCI_DEVICE_ID_COMPAQ_TOKENRING
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
id|PCI_VENDOR_ID_SYSKONNECT
comma
id|PCI_DEVICE_ID_SYSKONNECT_TR
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
comma
(brace
id|PCI_VENDOR_ID_TCONRAD
comma
id|PCI_DEVICE_ID_TCONRAD_TOKENRING
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|2
)brace
comma
(brace
id|PCI_VENDOR_ID_3COM
comma
id|PCI_DEVICE_ID_3COM_3C339
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|3
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
id|tmspci_pci_tbl
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
r_static
r_void
id|tms_pci_read_eeprom
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
id|tms_pci_setnselout_pins
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|function|tms_pci_sifreadb
r_static
r_int
r_int
id|tms_pci_sifreadb
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
DECL|function|tms_pci_sifreadw
r_static
r_int
r_int
id|tms_pci_sifreadw
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
DECL|function|tms_pci_sifwriteb
r_static
r_void
id|tms_pci_sifwriteb
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
DECL|function|tms_pci_sifwritew
r_static
r_void
id|tms_pci_sifwritew
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
DECL|function|tms_pci_attach
r_static
r_int
id|__init
id|tms_pci_attach
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
suffix:semicolon
r_int
r_int
id|pci_irq_line
suffix:semicolon
r_int
r_int
id|pci_ioaddr
suffix:semicolon
r_struct
id|card_info
op_star
id|cardinfo
op_assign
op_amp
id|card_info_table
(braket
id|ent-&gt;driver_data
)braket
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
id|init_trdev
c_func
(paren
l_int|NULL
comma
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
id|TMS_PCI_IO_EXTENT
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
id|dev-&gt;dma
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: %s&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|cardinfo-&gt;name
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s:    IO: %#4lx  IRQ: %d&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;base_addr
comma
id|dev-&gt;irq
)paren
suffix:semicolon
id|tms_pci_read_eeprom
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
id|tp
op_assign
id|dev-&gt;priv
suffix:semicolon
id|tp-&gt;setnselout
op_assign
id|tms_pci_setnselout_pins
suffix:semicolon
id|tp-&gt;sifreadb
op_assign
id|tms_pci_sifreadb
suffix:semicolon
id|tp-&gt;sifreadw
op_assign
id|tms_pci_sifreadw
suffix:semicolon
id|tp-&gt;sifwriteb
op_assign
id|tms_pci_sifwriteb
suffix:semicolon
id|tp-&gt;sifwritew
op_assign
id|tms_pci_sifwritew
suffix:semicolon
id|memcpy
c_func
(paren
id|tp-&gt;ProductID
comma
id|cardinfo-&gt;name
comma
id|PROD_ID_SIZE
op_plus
l_int|1
)paren
suffix:semicolon
id|tp-&gt;tmspriv
op_assign
id|cardinfo
suffix:semicolon
id|dev-&gt;open
op_assign
id|tms380tr_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|tms380tr_close
suffix:semicolon
id|ret
op_assign
id|register_trdev
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
id|pci_set_drvdata
c_func
(paren
id|pdev
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_out_tmsdev
suffix:colon
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
id|TMS_PCI_IO_EXTENT
)paren
suffix:semicolon
id|err_out_trdev
suffix:colon
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
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
multiline_comment|/*&n; * Reads MAC address from adapter RAM, which should&squot;ve read it from&n; * the onboard ROM.  &n; *&n; * Calling this on a board that does not support it can be a very&n; * dangerous thing.  The Madge board, for instance, will lock your&n; * machine hard when this is called.  Luckily, its supported in a&n; * seperate driver.  --ASF&n; */
DECL|function|tms_pci_read_eeprom
r_static
r_void
id|tms_pci_read_eeprom
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Address: 0000:0000 */
id|tms_pci_sifwritew
c_func
(paren
id|dev
comma
l_int|0
comma
id|SIFADX
)paren
suffix:semicolon
id|tms_pci_sifwritew
c_func
(paren
id|dev
comma
l_int|0
comma
id|SIFADR
)paren
suffix:semicolon
multiline_comment|/* Read six byte MAC address data */
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
(brace
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|tms_pci_sifreadw
c_func
(paren
id|dev
comma
id|SIFINC
)paren
op_rshift
l_int|8
suffix:semicolon
)brace
)brace
DECL|function|tms_pci_setnselout_pins
r_static
r_int
r_int
id|tms_pci_setnselout_pins
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
id|dev-&gt;priv
suffix:semicolon
r_struct
id|card_info
op_star
id|cardinfo
op_assign
id|tp-&gt;tmspriv
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
id|cardinfo-&gt;nselout
(braket
l_int|0
)braket
suffix:semicolon
)brace
multiline_comment|/* Set 4Mbps */
r_else
id|val
op_or_assign
id|cardinfo-&gt;nselout
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Set 16Mbps */
r_return
id|val
suffix:semicolon
)brace
DECL|function|tms_pci_detach
r_static
r_void
id|__devexit
id|tms_pci_detach
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
comma
id|TMS_PCI_IO_EXTENT
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
id|kfree
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
DECL|variable|tms_pci_driver
r_static
r_struct
id|pci_driver
id|tms_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;tmspci&quot;
comma
dot
id|id_table
op_assign
id|tmspci_pci_tbl
comma
dot
id|probe
op_assign
id|tms_pci_attach
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|tms_pci_detach
)paren
comma
)brace
suffix:semicolon
DECL|function|tms_pci_init
r_static
r_int
id|__init
id|tms_pci_init
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
id|tms_pci_driver
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
id|tms_pci_driver
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
DECL|function|tms_pci_rmmod
r_static
r_void
id|__devexit
id|tms_pci_rmmod
(paren
r_void
)paren
(brace
id|pci_unregister_driver
(paren
op_amp
id|tms_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|tms_pci_init
id|module_init
c_func
(paren
id|tms_pci_init
)paren
suffix:semicolon
DECL|variable|tms_pci_rmmod
id|module_exit
c_func
(paren
id|tms_pci_rmmod
)paren
suffix:semicolon
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  compile-command: &quot;gcc -DMODVERSIONS  -DMODULE -D__KERNEL__ -Wall -Wstrict-prototypes -O6 -fomit-frame-pointer -I/usr/src/linux/drivers/net/tokenring/ -c tmspci.c&quot;&n; *  alt-compile-command: &quot;gcc -DMODULE -D__KERNEL__ -Wall -Wstrict-prototypes -O6 -fomit-frame-pointer -I/usr/src/linux/drivers/net/tokenring/ -c tmspci.c&quot;&n; *  c-set-style &quot;K&amp;R&quot;&n; *  c-indent-level: 8&n; *  c-basic-offset: 8&n; *  tab-width: 8&n; * End:&n; */
eof
