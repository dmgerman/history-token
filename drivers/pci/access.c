macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
multiline_comment|/*&n; * This interrupt-safe spinlock protects all accesses to PCI&n; * configuration space.&n; */
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|pci_lock
)paren
suffix:semicolon
multiline_comment|/*&n; *  Wrappers for all PCI configuration access functions.  They just check&n; *  alignment, do locking and call the low-level functions pointed to&n; *  by pci_dev-&gt;ops.&n; */
DECL|macro|PCI_byte_BAD
mdefine_line|#define PCI_byte_BAD 0
DECL|macro|PCI_word_BAD
mdefine_line|#define PCI_word_BAD (pos &amp; 1)
DECL|macro|PCI_dword_BAD
mdefine_line|#define PCI_dword_BAD (pos &amp; 3)
DECL|macro|PCI_OP_READ
mdefine_line|#define PCI_OP_READ(size,type,len) &bslash;&n;int pci_bus_read_config_##size &bslash;&n;&t;(struct pci_bus *bus, unsigned int devfn, int pos, type *value)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;u32 data = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (PCI_##size##_BAD) return PCIBIOS_BAD_REGISTER_NUMBER;&t;&bslash;&n;&t;spin_lock_irqsave(&amp;pci_lock, flags);&t;&t;&t;&t;&bslash;&n;&t;res = bus-&gt;ops-&gt;read(bus, devfn, pos, len, &amp;data);&t;&t;&bslash;&n;&t;*value = (type)data;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;spin_unlock_irqrestore(&amp;pci_lock, flags);&t;&t;&t;&bslash;&n;&t;return res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|PCI_OP_WRITE
mdefine_line|#define PCI_OP_WRITE(size,type,len) &bslash;&n;int pci_bus_write_config_##size &bslash;&n;&t;(struct pci_bus *bus, unsigned int devfn, int pos, type value)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (PCI_##size##_BAD) return PCIBIOS_BAD_REGISTER_NUMBER;&t;&bslash;&n;&t;spin_lock_irqsave(&amp;pci_lock, flags);&t;&t;&t;&t;&bslash;&n;&t;res = bus-&gt;ops-&gt;write(bus, devfn, pos, len, value);&t;&t;&bslash;&n;&t;spin_unlock_irqrestore(&amp;pci_lock, flags);&t;&t;&t;&bslash;&n;&t;return res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
id|PCI_OP_READ
c_func
(paren
id|byte
comma
id|u8
comma
l_int|1
)paren
id|PCI_OP_READ
c_func
(paren
id|word
comma
id|u16
comma
l_int|2
)paren
id|PCI_OP_READ
c_func
(paren
id|dword
comma
id|u32
comma
l_int|4
)paren
id|PCI_OP_WRITE
c_func
(paren
id|byte
comma
id|u8
comma
l_int|1
)paren
id|PCI_OP_WRITE
c_func
(paren
id|word
comma
id|u16
comma
l_int|2
)paren
id|PCI_OP_WRITE
c_func
(paren
id|dword
comma
id|u32
comma
l_int|4
)paren
DECL|variable|pci_bus_read_config_byte
id|EXPORT_SYMBOL
c_func
(paren
id|pci_bus_read_config_byte
)paren
suffix:semicolon
DECL|variable|pci_bus_read_config_word
id|EXPORT_SYMBOL
c_func
(paren
id|pci_bus_read_config_word
)paren
suffix:semicolon
DECL|variable|pci_bus_read_config_dword
id|EXPORT_SYMBOL
c_func
(paren
id|pci_bus_read_config_dword
)paren
suffix:semicolon
DECL|variable|pci_bus_write_config_byte
id|EXPORT_SYMBOL
c_func
(paren
id|pci_bus_write_config_byte
)paren
suffix:semicolon
DECL|variable|pci_bus_write_config_word
id|EXPORT_SYMBOL
c_func
(paren
id|pci_bus_write_config_word
)paren
suffix:semicolon
DECL|variable|pci_bus_write_config_dword
id|EXPORT_SYMBOL
c_func
(paren
id|pci_bus_write_config_dword
)paren
suffix:semicolon
eof
