multiline_comment|/*&n; * direct.c - Low-level direct PCI config space access&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;pci.h&quot;
multiline_comment|/*&n; * Functions for accessing PCI configuration space with type 1 accesses&n; */
DECL|macro|PCI_CONF1_ADDRESS
mdefine_line|#define PCI_CONF1_ADDRESS(bus, dev, fn, reg) &bslash;&n;&t;(0x80000000 | (bus &lt;&lt; 16) | (dev &lt;&lt; 11) | (fn &lt;&lt; 8) | (reg &amp; ~3))
DECL|function|pci_conf1_read
r_static
r_int
id|pci_conf1_read
(paren
r_int
id|seg
comma
r_int
id|bus
comma
r_int
id|dev
comma
r_int
id|fn
comma
r_int
id|reg
comma
r_int
id|len
comma
id|u32
op_star
id|value
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
(paren
id|bus
OG
l_int|255
)paren
op_logical_or
(paren
id|dev
OG
l_int|31
)paren
op_logical_or
(paren
id|fn
OG
l_int|7
)paren
op_logical_or
(paren
id|reg
OG
l_int|255
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pci_config_lock
comma
id|flags
)paren
suffix:semicolon
id|outl
c_func
(paren
id|PCI_CONF1_ADDRESS
c_func
(paren
id|bus
comma
id|dev
comma
id|fn
comma
id|reg
)paren
comma
l_int|0xCF8
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|len
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
id|reg
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
id|reg
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
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pci_config_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_conf1_write
r_static
r_int
id|pci_conf1_write
(paren
r_int
id|seg
comma
r_int
id|bus
comma
r_int
id|dev
comma
r_int
id|fn
comma
r_int
id|reg
comma
r_int
id|len
comma
id|u32
id|value
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bus
OG
l_int|255
)paren
op_logical_or
(paren
id|dev
OG
l_int|31
)paren
op_logical_or
(paren
id|fn
OG
l_int|7
)paren
op_logical_or
(paren
id|reg
OG
l_int|255
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pci_config_lock
comma
id|flags
)paren
suffix:semicolon
id|outl
c_func
(paren
id|PCI_CONF1_ADDRESS
c_func
(paren
id|bus
comma
id|dev
comma
id|fn
comma
id|reg
)paren
comma
l_int|0xCF8
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|len
)paren
(brace
r_case
l_int|1
suffix:colon
id|outb
c_func
(paren
(paren
id|u8
)paren
id|value
comma
l_int|0xCFC
op_plus
(paren
id|reg
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
(paren
id|u16
)paren
id|value
comma
l_int|0xCFC
op_plus
(paren
id|reg
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
(paren
id|u32
)paren
id|value
comma
l_int|0xCFC
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pci_config_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|PCI_CONF1_ADDRESS
macro_line|#undef PCI_CONF1_ADDRESS
DECL|function|pci_conf1_read_config_byte
r_static
r_int
id|pci_conf1_read_config_byte
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
r_int
id|result
suffix:semicolon
id|u32
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|result
op_assign
id|pci_conf1_read
c_func
(paren
l_int|0
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|where
comma
l_int|1
comma
op_amp
id|data
)paren
suffix:semicolon
op_star
id|value
op_assign
(paren
id|u8
)paren
id|data
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|pci_conf1_read_config_word
r_static
r_int
id|pci_conf1_read_config_word
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
r_int
id|result
suffix:semicolon
id|u32
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|result
op_assign
id|pci_conf1_read
c_func
(paren
l_int|0
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|where
comma
l_int|2
comma
op_amp
id|data
)paren
suffix:semicolon
op_star
id|value
op_assign
(paren
id|u16
)paren
id|data
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|pci_conf1_read_config_dword
r_static
r_int
id|pci_conf1_read_config_dword
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
op_logical_neg
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|pci_conf1_read
c_func
(paren
l_int|0
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|where
comma
l_int|4
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|pci_conf1_write_config_byte
r_static
r_int
id|pci_conf1_write_config_byte
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
id|pci_conf1_write
c_func
(paren
l_int|0
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|where
comma
l_int|1
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|pci_conf1_write_config_word
r_static
r_int
id|pci_conf1_write_config_word
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
id|pci_conf1_write
c_func
(paren
l_int|0
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|where
comma
l_int|2
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|pci_conf1_write_config_dword
r_static
r_int
id|pci_conf1_write_config_dword
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
r_return
id|pci_conf1_write
c_func
(paren
l_int|0
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|where
comma
l_int|4
comma
id|value
)paren
suffix:semicolon
)brace
DECL|variable|pci_direct_conf1
r_static
r_struct
id|pci_ops
id|pci_direct_conf1
op_assign
(brace
id|pci_conf1_read_config_byte
comma
id|pci_conf1_read_config_word
comma
id|pci_conf1_read_config_dword
comma
id|pci_conf1_write_config_byte
comma
id|pci_conf1_write_config_word
comma
id|pci_conf1_write_config_dword
)brace
suffix:semicolon
multiline_comment|/*&n; * Functions for accessing PCI configuration space with type 2 accesses&n; */
DECL|macro|PCI_CONF2_ADDRESS
mdefine_line|#define PCI_CONF2_ADDRESS(dev, reg)&t;(u16)(0xC000 | (dev &lt;&lt; 8) | reg)
DECL|function|pci_conf2_read
r_static
r_int
id|pci_conf2_read
(paren
r_int
id|seg
comma
r_int
id|bus
comma
r_int
id|dev
comma
r_int
id|fn
comma
r_int
id|reg
comma
r_int
id|len
comma
id|u32
op_star
id|value
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
(paren
id|bus
OG
l_int|255
)paren
op_logical_or
(paren
id|dev
OG
l_int|31
)paren
op_logical_or
(paren
id|fn
OG
l_int|7
)paren
op_logical_or
(paren
id|reg
OG
l_int|255
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_amp
l_int|0x10
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pci_config_lock
comma
id|flags
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|u8
)paren
(paren
l_int|0xF0
op_or
(paren
id|fn
op_lshift
l_int|1
)paren
)paren
comma
l_int|0xCF8
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|u8
)paren
id|bus
comma
l_int|0xCFA
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|len
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
id|PCI_CONF2_ADDRESS
c_func
(paren
id|dev
comma
id|reg
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
id|PCI_CONF2_ADDRESS
c_func
(paren
id|dev
comma
id|reg
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
id|PCI_CONF2_ADDRESS
c_func
(paren
id|dev
comma
id|reg
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|outb
(paren
l_int|0
comma
l_int|0xCF8
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pci_config_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_conf2_write
r_static
r_int
id|pci_conf2_write
(paren
r_int
id|seg
comma
r_int
id|bus
comma
r_int
id|dev
comma
r_int
id|fn
comma
r_int
id|reg
comma
r_int
id|len
comma
id|u32
id|value
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bus
OG
l_int|255
)paren
op_logical_or
(paren
id|dev
OG
l_int|31
)paren
op_logical_or
(paren
id|fn
OG
l_int|7
)paren
op_logical_or
(paren
id|reg
OG
l_int|255
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_amp
l_int|0x10
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pci_config_lock
comma
id|flags
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|u8
)paren
(paren
l_int|0xF0
op_or
(paren
id|fn
op_lshift
l_int|1
)paren
)paren
comma
l_int|0xCF8
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|u8
)paren
id|bus
comma
l_int|0xCFA
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|len
)paren
(brace
r_case
l_int|1
suffix:colon
id|outb
(paren
(paren
id|u8
)paren
id|value
comma
id|PCI_CONF2_ADDRESS
c_func
(paren
id|dev
comma
id|reg
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|outw
(paren
(paren
id|u16
)paren
id|value
comma
id|PCI_CONF2_ADDRESS
c_func
(paren
id|dev
comma
id|reg
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|outl
(paren
(paren
id|u32
)paren
id|value
comma
id|PCI_CONF2_ADDRESS
c_func
(paren
id|dev
comma
id|reg
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|outb
(paren
l_int|0
comma
l_int|0xCF8
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pci_config_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|PCI_CONF2_ADDRESS
macro_line|#undef PCI_CONF2_ADDRESS
DECL|function|pci_conf2_read_config_byte
r_static
r_int
id|pci_conf2_read_config_byte
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
r_int
id|result
suffix:semicolon
id|u32
id|data
suffix:semicolon
id|result
op_assign
id|pci_conf2_read
c_func
(paren
l_int|0
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|where
comma
l_int|1
comma
op_amp
id|data
)paren
suffix:semicolon
op_star
id|value
op_assign
(paren
id|u8
)paren
id|data
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|pci_conf2_read_config_word
r_static
r_int
id|pci_conf2_read_config_word
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
r_int
id|result
suffix:semicolon
id|u32
id|data
suffix:semicolon
id|result
op_assign
id|pci_conf2_read
c_func
(paren
l_int|0
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|where
comma
l_int|2
comma
op_amp
id|data
)paren
suffix:semicolon
op_star
id|value
op_assign
(paren
id|u16
)paren
id|data
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|pci_conf2_read_config_dword
r_static
r_int
id|pci_conf2_read_config_dword
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
r_return
id|pci_conf2_read
c_func
(paren
l_int|0
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|where
comma
l_int|4
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|pci_conf2_write_config_byte
r_static
r_int
id|pci_conf2_write_config_byte
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
id|pci_conf2_write
c_func
(paren
l_int|0
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|where
comma
l_int|1
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|pci_conf2_write_config_word
r_static
r_int
id|pci_conf2_write_config_word
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
id|pci_conf2_write
c_func
(paren
l_int|0
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|where
comma
l_int|2
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|pci_conf2_write_config_dword
r_static
r_int
id|pci_conf2_write_config_dword
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
r_return
id|pci_conf2_write
c_func
(paren
l_int|0
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|where
comma
l_int|4
comma
id|value
)paren
suffix:semicolon
)brace
DECL|variable|pci_direct_conf2
r_static
r_struct
id|pci_ops
id|pci_direct_conf2
op_assign
(brace
id|pci_conf2_read_config_byte
comma
id|pci_conf2_read_config_word
comma
id|pci_conf2_read_config_dword
comma
id|pci_conf2_write_config_byte
comma
id|pci_conf2_write_config_word
comma
id|pci_conf2_write_config_dword
)brace
suffix:semicolon
multiline_comment|/*&n; * Before we decide to use direct hardware access mechanisms, we try to do some&n; * trivial checks to ensure it at least _seems_ to be working -- we just test&n; * whether bus 00 contains a host bridge (this is similar to checking&n; * techniques used in XFree86, but ours should be more reliable since we&n; * attempt to make use of direct access hints provided by the PCI BIOS).&n; *&n; * This should be close to trivial, but it isn&squot;t, because there are buggy&n; * chipsets (yes, you guessed it, by Intel and Compaq) that have no class ID.&n; */
DECL|function|pci_sanity_check
r_static
r_int
id|__devinit
id|pci_sanity_check
c_func
(paren
r_struct
id|pci_ops
op_star
id|o
)paren
(brace
id|u16
id|x
suffix:semicolon
r_struct
id|pci_bus
id|bus
suffix:semicolon
multiline_comment|/* Fake bus and device */
r_struct
id|pci_dev
id|dev
suffix:semicolon
r_if
c_cond
(paren
id|pci_probe
op_amp
id|PCI_NO_CHECKS
)paren
r_return
l_int|1
suffix:semicolon
id|bus.number
op_assign
l_int|0
suffix:semicolon
id|dev.bus
op_assign
op_amp
id|bus
suffix:semicolon
r_for
c_loop
(paren
id|dev.devfn
op_assign
l_int|0
suffix:semicolon
id|dev.devfn
OL
l_int|0x100
suffix:semicolon
id|dev.devfn
op_increment
)paren
r_if
c_cond
(paren
(paren
op_logical_neg
id|o
op_member_access_from_pointer
id|read_word
c_func
(paren
op_amp
id|dev
comma
id|PCI_CLASS_DEVICE
comma
op_amp
id|x
)paren
op_logical_and
(paren
id|x
op_eq
id|PCI_CLASS_BRIDGE_HOST
op_logical_or
id|x
op_eq
id|PCI_CLASS_DISPLAY_VGA
)paren
)paren
op_logical_or
(paren
op_logical_neg
id|o
op_member_access_from_pointer
id|read_word
c_func
(paren
op_amp
id|dev
comma
id|PCI_VENDOR_ID
comma
op_amp
id|x
)paren
op_logical_and
(paren
id|x
op_eq
id|PCI_VENDOR_ID_INTEL
op_logical_or
id|x
op_eq
id|PCI_VENDOR_ID_COMPAQ
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI: Sanity check failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_check_direct
r_static
r_struct
id|pci_ops
op_star
id|__devinit
id|pci_check_direct
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check if configuration type 1 works.&n;&t; */
r_if
c_cond
(paren
id|pci_probe
op_amp
id|PCI_PROBE_CONF1
)paren
(brace
id|outb
(paren
l_int|0x01
comma
l_int|0xCFB
)paren
suffix:semicolon
id|tmp
op_assign
id|inl
(paren
l_int|0xCF8
)paren
suffix:semicolon
id|outl
(paren
l_int|0x80000000
comma
l_int|0xCF8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inl
(paren
l_int|0xCF8
)paren
op_eq
l_int|0x80000000
op_logical_and
id|pci_sanity_check
c_func
(paren
op_amp
id|pci_direct_conf1
)paren
)paren
(brace
id|outl
(paren
id|tmp
comma
l_int|0xCF8
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Using configuration type 1&bslash;n&quot;
)paren
suffix:semicolon
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
l_string|&quot;PCI conf1&quot;
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
op_amp
id|pci_direct_conf1
suffix:semicolon
)brace
id|outl
(paren
id|tmp
comma
l_int|0xCF8
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Check if configuration type 2 works.&n;&t; */
r_if
c_cond
(paren
id|pci_probe
op_amp
id|PCI_PROBE_CONF2
)paren
(brace
id|outb
(paren
l_int|0x00
comma
l_int|0xCFB
)paren
suffix:semicolon
id|outb
(paren
l_int|0x00
comma
l_int|0xCF8
)paren
suffix:semicolon
id|outb
(paren
l_int|0x00
comma
l_int|0xCFA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
(paren
l_int|0xCF8
)paren
op_eq
l_int|0x00
op_logical_and
id|inb
(paren
l_int|0xCFA
)paren
op_eq
l_int|0x00
op_logical_and
id|pci_sanity_check
c_func
(paren
op_amp
id|pci_direct_conf2
)paren
)paren
(brace
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Using configuration type 2&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
l_int|0xCF8
comma
l_int|4
comma
l_string|&quot;PCI conf2&quot;
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
op_amp
id|pci_direct_conf2
suffix:semicolon
)brace
)brace
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pci_direct_init
r_static
r_int
id|__init
id|pci_direct_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
(paren
id|pci_probe
op_amp
(paren
id|PCI_PROBE_CONF1
op_or
id|PCI_PROBE_CONF2
)paren
)paren
op_logical_and
(paren
id|pci_root_ops
op_assign
id|pci_check_direct
c_func
(paren
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|pci_root_ops
op_eq
op_amp
id|pci_direct_conf1
)paren
(brace
id|pci_config_read
op_assign
id|pci_conf1_read
suffix:semicolon
id|pci_config_write
op_assign
id|pci_conf1_write
suffix:semicolon
)brace
r_else
(brace
id|pci_config_read
op_assign
id|pci_conf2_read
suffix:semicolon
id|pci_config_write
op_assign
id|pci_conf2_write
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pci_direct_init
id|arch_initcall
c_func
(paren
id|pci_direct_init
)paren
suffix:semicolon
eof
