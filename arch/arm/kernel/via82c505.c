macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
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
mdefine_line|#define CONFIG_CMD(dev, where)   (0x80000000 | (dev-&gt;bus-&gt;number &lt;&lt; 16) | (dev-&gt;devfn &lt;&lt; 8) | (where &amp; ~3))
r_static
r_int
DECL|function|via82c505_read_config_byte
id|via82c505_read_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u8
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
id|dev
comma
id|where
)paren
comma
l_int|0xCF8
)paren
suffix:semicolon
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
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|via82c505_read_config_word
id|via82c505_read_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u16
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
id|dev
comma
id|where
)paren
comma
l_int|0xCF8
)paren
suffix:semicolon
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
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|via82c505_read_config_dword
id|via82c505_read_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
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
id|dev
comma
id|where
)paren
comma
l_int|0xCF8
)paren
suffix:semicolon
op_star
id|value
op_assign
id|inl
c_func
(paren
l_int|0xCFC
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|via82c505_write_config_byte
id|via82c505_write_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u8
id|value
)paren
(brace
id|outl
c_func
(paren
id|CONFIG_CMD
c_func
(paren
id|dev
comma
id|where
)paren
comma
l_int|0xCF8
)paren
suffix:semicolon
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
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|via82c505_write_config_word
id|via82c505_write_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u16
id|value
)paren
(brace
id|outl
c_func
(paren
id|CONFIG_CMD
c_func
(paren
id|dev
comma
id|where
)paren
comma
l_int|0xCF8
)paren
suffix:semicolon
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
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|via82c505_write_config_dword
id|via82c505_write_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
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
id|dev
comma
id|where
)paren
comma
l_int|0xCF8
)paren
suffix:semicolon
id|outl
c_func
(paren
id|value
comma
l_int|0xCFC
)paren
suffix:semicolon
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
id|via82c505_read_config_byte
comma
id|via82c505_read_config_word
comma
id|via82c505_read_config_dword
comma
id|via82c505_write_config_byte
comma
id|via82c505_write_config_word
comma
id|via82c505_write_config_dword
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_ARCH_SHARK
DECL|variable|size_wanted
r_static
r_char
id|size_wanted
suffix:semicolon
r_static
r_int
DECL|function|dummy_read_config_byte
id|dummy_read_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u8
op_star
id|value
)paren
(brace
op_star
id|value
op_assign
l_int|0
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|dummy_read_config_word
id|dummy_read_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u16
op_star
id|value
)paren
(brace
op_star
id|value
op_assign
l_int|0
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|dummy_read_config_dword
id|dummy_read_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u32
op_star
id|value
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;devfn
op_ne
l_int|0
)paren
op_star
id|value
op_assign
l_int|0
suffix:semicolon
r_else
r_switch
c_cond
(paren
id|where
)paren
(brace
r_case
id|PCI_VENDOR_ID
suffix:colon
op_star
id|value
op_assign
id|PCI_VENDOR_ID_INTERG
op_or
id|PCI_DEVICE_ID_INTERG_2010
op_lshift
l_int|16
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_CLASS_REVISION
suffix:colon
op_star
id|value
op_assign
id|PCI_CLASS_DISPLAY_VGA
op_lshift
l_int|16
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_BASE_ADDRESS_0
suffix:colon
r_if
c_cond
(paren
id|size_wanted
)paren
(brace
multiline_comment|/* 0x00900000 bytes long (0xff700000) */
op_star
id|value
op_assign
l_int|0xff000000
suffix:semicolon
id|size_wanted
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
op_star
id|value
op_assign
id|FB_START
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PCI_INTERRUPT_LINE
suffix:colon
op_star
id|value
op_assign
l_int|6
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
op_star
id|value
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|dummy_write_config_byte
id|dummy_write_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u8
id|value
)paren
(brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|dummy_write_config_word
id|dummy_write_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u16
id|value
)paren
(brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|dummy_write_config_dword
id|dummy_write_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u32
id|value
)paren
(brace
r_if
c_cond
(paren
(paren
id|dev-&gt;devfn
op_eq
l_int|0
)paren
op_logical_and
(paren
id|where
op_eq
id|PCI_BASE_ADDRESS_0
)paren
op_logical_and
(paren
id|value
op_eq
l_int|0xffffffff
)paren
)paren
id|size_wanted
op_assign
l_int|1
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|dummy_ops
r_static
r_struct
id|pci_ops
id|dummy_ops
op_assign
(brace
id|dummy_read_config_byte
comma
id|dummy_read_config_word
comma
id|dummy_read_config_dword
comma
id|dummy_write_config_byte
comma
id|dummy_write_config_word
comma
id|dummy_write_config_dword
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|function|via82c505_init
r_void
id|__init
id|via82c505_init
c_func
(paren
r_void
op_star
id|sysdata
)paren
(brace
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;PCI: VIA 82c505&bslash;n&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xA8
comma
l_int|2
comma
l_string|&quot;via config&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xCF8
comma
l_int|8
comma
l_string|&quot;pci config&quot;
)paren
suffix:semicolon
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
macro_line|#ifdef CONFIG_ARCH_SHARK
multiline_comment|/* &n;&t; * Initialize a fake pci-bus number 1 for the CyberPro&n;         * on the vlbus&n;&t; */
id|bus
op_assign
id|pci_scan_bus
c_func
(paren
l_int|1
comma
op_amp
id|dummy_ops
comma
id|sysdata
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
