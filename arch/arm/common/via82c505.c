macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/mach/pci.h&gt;
DECL|macro|MAX_SLOTS
mdefine_line|#define MAX_SLOTS&t;&t;7
DECL|macro|CONFIG_CMD
mdefine_line|#define CONFIG_CMD(bus, devfn, where)   (0x80000000 | (bus-&gt;number &lt;&lt; 16) | (devfn &lt;&lt; 8) | (where &amp; ~3))
r_static
r_int
DECL|function|via82c505_read_config
id|via82c505_read_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
op_star
id|value
)paren
(brace
id|outl
c_func
(paren
id|CONFIG_CMD
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
)paren
comma
l_int|0xCF8
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
op_star
id|value
op_assign
id|inb
c_func
(paren
l_int|0xCFC
op_plus
(paren
id|where
op_amp
l_int|3
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
id|value
op_assign
id|inw
c_func
(paren
l_int|0xCFC
op_plus
(paren
id|where
op_amp
l_int|2
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
op_star
id|value
op_assign
id|inl
c_func
(paren
l_int|0xCFC
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|via82c505_write_config
id|via82c505_write_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
id|value
)paren
(brace
id|outl
c_func
(paren
id|CONFIG_CMD
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
)paren
comma
l_int|0xCF8
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|outb
c_func
(paren
id|value
comma
l_int|0xCFC
op_plus
(paren
id|where
op_amp
l_int|3
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|outw
c_func
(paren
id|value
comma
l_int|0xCFC
op_plus
(paren
id|where
op_amp
l_int|2
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|outl
c_func
(paren
id|value
comma
l_int|0xCFC
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|via82c505_ops
r_static
r_struct
id|pci_ops
id|via82c505_ops
op_assign
(brace
dot
id|read
op_assign
id|via82c505_read_config
comma
dot
id|write
op_assign
id|via82c505_write_config
comma
)brace
suffix:semicolon
DECL|function|via82c505_preinit
r_void
id|__init
id|via82c505_preinit
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;PCI: VIA 82c505&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
l_int|0xA8
comma
l_int|2
comma
l_string|&quot;via config&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;VIA 82c505: Unable to request region 0xA8&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
l_int|0xCF8
comma
l_int|8
comma
l_string|&quot;pci config&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;VIA 82c505: Unable to request region 0xCF8&bslash;n&quot;
)paren
suffix:semicolon
id|release_region
c_func
(paren
l_int|0xA8
comma
l_int|2
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Enable compatible Mode */
id|outb
c_func
(paren
l_int|0x96
comma
l_int|0xA8
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x18
comma
l_int|0xA9
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x93
comma
l_int|0xA8
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xd0
comma
l_int|0xA9
)paren
suffix:semicolon
)brace
DECL|function|via82c505_setup
r_int
id|__init
id|via82c505_setup
c_func
(paren
r_int
id|nr
comma
r_struct
id|pci_sys_data
op_star
id|sys
)paren
(brace
r_return
(paren
id|nr
op_eq
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|via82c505_scan_bus
r_struct
id|pci_bus
op_star
id|__init
id|via82c505_scan_bus
c_func
(paren
r_int
id|nr
comma
r_struct
id|pci_sys_data
op_star
id|sysdata
)paren
(brace
r_if
c_cond
(paren
id|nr
op_eq
l_int|0
)paren
r_return
id|pci_scan_bus
c_func
(paren
l_int|0
comma
op_amp
id|via82c505_ops
comma
id|sysdata
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
eof
