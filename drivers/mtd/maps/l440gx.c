multiline_comment|/*&n; * $Id: l440gx.c,v 1.14 2004/09/16 23:27:13 gleixner Exp $&n; *&n; * BIOS Flash chip on Intel 440GX board.&n; *&n; * Bugs this currently does not work under linuxBIOS.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|PIIXE_IOBASE_RESOURCE
mdefine_line|#define PIIXE_IOBASE_RESOURCE&t;11
DECL|macro|WINDOW_ADDR
mdefine_line|#define WINDOW_ADDR 0xfff00000
DECL|macro|WINDOW_SIZE
mdefine_line|#define WINDOW_SIZE 0x00100000
DECL|macro|BUSWIDTH
mdefine_line|#define BUSWIDTH 1
DECL|variable|iobase
r_static
id|u32
id|iobase
suffix:semicolon
DECL|macro|IOBASE
mdefine_line|#define IOBASE iobase
DECL|macro|TRIBUF_PORT
mdefine_line|#define TRIBUF_PORT (IOBASE+0x37)
DECL|macro|VPP_PORT
mdefine_line|#define VPP_PORT (IOBASE+0x28)
DECL|variable|mymtd
r_static
r_struct
id|mtd_info
op_star
id|mymtd
suffix:semicolon
multiline_comment|/* Is this really the vpp port? */
DECL|function|l440gx_set_vpp
r_void
id|l440gx_set_vpp
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
id|vpp
)paren
(brace
r_int
r_int
id|l
suffix:semicolon
id|l
op_assign
id|inl
c_func
(paren
id|VPP_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vpp
)paren
(brace
id|l
op_or_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|l
op_and_assign
op_complement
l_int|1
suffix:semicolon
)brace
id|outl
c_func
(paren
id|l
comma
id|VPP_PORT
)paren
suffix:semicolon
)brace
DECL|variable|l440gx_map
r_struct
id|map_info
id|l440gx_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;L440GX BIOS&quot;
comma
dot
id|size
op_assign
id|WINDOW_SIZE
comma
dot
id|bankwidth
op_assign
id|BUSWIDTH
comma
dot
id|phys
op_assign
id|WINDOW_ADDR
comma
macro_line|#if 0
multiline_comment|/* FIXME verify that this is the &n;&t; * appripriate code for vpp enable/disable&n;&t; */
dot
id|set_vpp
op_assign
id|l440gx_set_vpp
macro_line|#endif
)brace
suffix:semicolon
DECL|function|init_l440gx
r_static
r_int
id|__init
id|init_l440gx
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
comma
op_star
id|pm_dev
suffix:semicolon
r_struct
id|resource
op_star
id|pm_iobase
suffix:semicolon
id|__u16
id|word
suffix:semicolon
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82371AB_0
comma
l_int|NULL
)paren
suffix:semicolon
id|pm_dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82371AB_3
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|pm_dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;L440GX flash mapping: failed to find PIIX4 ISA bridge, cannot continue&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|l440gx_map.virt
op_assign
(paren
r_void
id|__iomem
op_star
)paren
id|ioremap_nocache
c_func
(paren
id|WINDOW_ADDR
comma
id|WINDOW_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|l440gx_map.virt
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Failed to ioremap L440GX flash region&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|simple_map_init
c_func
(paren
op_amp
id|l440gx_map
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;window_addr = 0x%08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|l440gx_map.virt
)paren
suffix:semicolon
multiline_comment|/* Setup the pm iobase resource &n;&t; * This code should move into some kind of generic bridge&n;&t; * driver but for the moment I&squot;m content with getting the&n;&t; * allocation correct. &n;&t; */
id|pm_iobase
op_assign
op_amp
id|pm_dev-&gt;resource
(braket
id|PIIXE_IOBASE_RESOURCE
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pm_iobase-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
)paren
(brace
id|pm_iobase-&gt;name
op_assign
l_string|&quot;pm iobase&quot;
suffix:semicolon
id|pm_iobase-&gt;start
op_assign
l_int|0
suffix:semicolon
id|pm_iobase-&gt;end
op_assign
l_int|63
suffix:semicolon
id|pm_iobase-&gt;flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
multiline_comment|/* Put the current value in the resource */
id|pci_read_config_dword
c_func
(paren
id|pm_dev
comma
l_int|0x40
comma
op_amp
id|iobase
)paren
suffix:semicolon
id|iobase
op_and_assign
op_complement
l_int|1
suffix:semicolon
id|pm_iobase-&gt;start
op_add_assign
id|iobase
op_amp
op_complement
l_int|1
suffix:semicolon
id|pm_iobase-&gt;end
op_add_assign
id|iobase
op_amp
op_complement
l_int|1
suffix:semicolon
multiline_comment|/* Allocate the resource region */
r_if
c_cond
(paren
id|pci_assign_resource
c_func
(paren
id|pm_dev
comma
id|PIIXE_IOBASE_RESOURCE
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Could not allocate pm iobase resource&bslash;n&quot;
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|l440gx_map.virt
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
)brace
multiline_comment|/* Set the iobase */
id|iobase
op_assign
id|pm_iobase-&gt;start
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|pm_dev
comma
l_int|0x40
comma
id|iobase
op_or
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Set XBCS# */
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0x4e
comma
op_amp
id|word
)paren
suffix:semicolon
id|word
op_or_assign
l_int|0x4
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x4e
comma
id|word
)paren
suffix:semicolon
multiline_comment|/* Supply write voltage to the chip */
id|l440gx_set_vpp
c_func
(paren
op_amp
id|l440gx_map
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Enable the gate on the WE line */
id|outb
c_func
(paren
id|inb
c_func
(paren
id|TRIBUF_PORT
)paren
op_amp
op_complement
l_int|1
comma
id|TRIBUF_PORT
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Enabled WE line to L440GX BIOS flash chip.&bslash;n&quot;
)paren
suffix:semicolon
id|mymtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;jedec_probe&quot;
comma
op_amp
id|l440gx_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mymtd
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;JEDEC probe on BIOS chip failed. Using ROM&bslash;n&quot;
)paren
suffix:semicolon
id|mymtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;map_rom&quot;
comma
op_amp
id|l440gx_map
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mymtd
)paren
(brace
id|mymtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|add_mtd_device
c_func
(paren
id|mymtd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|l440gx_map.virt
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|cleanup_l440gx
r_static
r_void
id|__exit
id|cleanup_l440gx
c_func
(paren
r_void
)paren
(brace
id|del_mtd_device
c_func
(paren
id|mymtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|mymtd
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|l440gx_map.virt
)paren
suffix:semicolon
)brace
DECL|variable|init_l440gx
id|module_init
c_func
(paren
id|init_l440gx
)paren
suffix:semicolon
DECL|variable|cleanup_l440gx
id|module_exit
c_func
(paren
id|cleanup_l440gx
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;David Woodhouse &lt;dwmw2@infradead.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD map driver for BIOS chips on Intel L440GX motherboards&quot;
)paren
suffix:semicolon
eof
