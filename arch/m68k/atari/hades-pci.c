multiline_comment|/*&n; * hades-pci.c - Hardware specific PCI BIOS functions the Hades Atari clone.&n; *&n; * Written by Wout Klaren.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#if 0
macro_line|# define DBG_DEVS(args)&t;&t;printk args
macro_line|#else
DECL|macro|DBG_DEVS
macro_line|# define DBG_DEVS(args)
macro_line|#endif
macro_line|#if defined(CONFIG_PCI) &amp;&amp; defined(CONFIG_HADES)
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/atarihw.h&gt;
macro_line|#include &lt;asm/atariints.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
DECL|macro|HADES_MEM_BASE
mdefine_line|#define HADES_MEM_BASE&t;&t;0x80000000
DECL|macro|HADES_MEM_SIZE
mdefine_line|#define HADES_MEM_SIZE&t;&t;0x20000000
DECL|macro|HADES_CONFIG_BASE
mdefine_line|#define HADES_CONFIG_BASE&t;0xA0000000
DECL|macro|HADES_CONFIG_SIZE
mdefine_line|#define HADES_CONFIG_SIZE&t;0x10000000
DECL|macro|HADES_IO_BASE
mdefine_line|#define HADES_IO_BASE&t;&t;0xB0000000
DECL|macro|HADES_IO_SIZE
mdefine_line|#define HADES_IO_SIZE&t;&t;0x10000000
DECL|macro|HADES_VIRT_IO_SIZE
mdefine_line|#define HADES_VIRT_IO_SIZE&t;0x00010000&t;/* Only 64k is remapped and actually used. */
DECL|macro|N_SLOTS
mdefine_line|#define N_SLOTS&t;&t;&t;&t;4&t;&t;&t;/* Number of PCI slots. */
DECL|variable|pci_mem_name
r_static
r_const
r_char
id|pci_mem_name
(braket
)braket
op_assign
l_string|&quot;PCI memory space&quot;
suffix:semicolon
DECL|variable|pci_io_name
r_static
r_const
r_char
id|pci_io_name
(braket
)braket
op_assign
l_string|&quot;PCI I/O space&quot;
suffix:semicolon
DECL|variable|pci_config_name
r_static
r_const
r_char
id|pci_config_name
(braket
)braket
op_assign
l_string|&quot;PCI config space&quot;
suffix:semicolon
DECL|variable|config_space
r_static
r_struct
id|resource
id|config_space
op_assign
(brace
id|pci_config_name
comma
id|HADES_CONFIG_BASE
comma
id|HADES_CONFIG_BASE
op_plus
id|HADES_CONFIG_SIZE
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|io_space
r_static
r_struct
id|resource
id|io_space
op_assign
(brace
id|pci_io_name
comma
id|HADES_IO_BASE
comma
id|HADES_IO_BASE
op_plus
id|HADES_IO_SIZE
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|pci_conf_base_phys
r_static
r_const
r_int
r_int
id|pci_conf_base_phys
(braket
)braket
op_assign
(brace
l_int|0xA0080000
comma
l_int|0xA0040000
comma
l_int|0xA0020000
comma
l_int|0xA0010000
)brace
suffix:semicolon
DECL|variable|pci_conf_base_virt
r_static
r_int
r_int
id|pci_conf_base_virt
(braket
id|N_SLOTS
)braket
suffix:semicolon
DECL|variable|pci_io_base_virt
r_static
r_int
r_int
id|pci_io_base_virt
suffix:semicolon
multiline_comment|/*&n; * static void *mk_conf_addr(unsigned char bus, unsigned char device_fn,&n; *&t;&t;&t;     unsigned char where)&n; *&n; * Calculate the address of the PCI configuration area of the given&n; * device.&n; *&n; * BUG: boards with multiple functions are probably not correctly&n; * supported.&n; */
DECL|function|mk_conf_addr
r_static
r_void
op_star
id|mk_conf_addr
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
)paren
(brace
r_int
id|device
op_assign
id|dev-&gt;devfn
op_rshift
l_int|3
comma
id|function
op_assign
id|dev-&gt;devfn
op_amp
l_int|7
suffix:semicolon
r_void
op_star
id|result
suffix:semicolon
id|DBG_DEVS
c_func
(paren
(paren
l_string|&quot;mk_conf_addr(bus=%d ,device_fn=0x%x, where=0x%x, pci_addr=0x%p)&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|where
comma
id|pci_addr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|device
OG
l_int|3
)paren
(brace
id|DBG_DEVS
c_func
(paren
(paren
l_string|&quot;mk_conf_addr: device (%d) &gt; 3, returning NULL&bslash;n&quot;
comma
id|device
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_ne
l_int|0
)paren
(brace
id|DBG_DEVS
c_func
(paren
(paren
l_string|&quot;mk_conf_addr: bus (%d) &gt; 0, returning NULL&bslash;n&quot;
comma
id|device
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|result
op_assign
(paren
r_void
op_star
)paren
(paren
id|pci_conf_base_virt
(braket
id|device
)braket
op_or
(paren
id|function
op_lshift
l_int|8
)paren
op_or
(paren
id|where
)paren
)paren
suffix:semicolon
id|DBG_DEVS
c_func
(paren
(paren
l_string|&quot;mk_conf_addr: returning pci_addr 0x%lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|result
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|hades_read_config_byte
r_static
r_int
id|hades_read_config_byte
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
r_volatile
r_int
r_char
op_star
id|pci_addr
suffix:semicolon
op_star
id|value
op_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pci_addr
op_assign
(paren
r_int
r_char
op_star
)paren
id|mk_conf_addr
c_func
(paren
id|dev
comma
id|where
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
op_star
id|value
op_assign
op_star
id|pci_addr
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|hades_read_config_word
r_static
r_int
id|hades_read_config_word
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
r_volatile
r_int
r_int
op_star
id|pci_addr
suffix:semicolon
op_star
id|value
op_assign
l_int|0xffff
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|0x1
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pci_addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|mk_conf_addr
c_func
(paren
id|dev
comma
id|where
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
op_star
id|value
op_assign
id|le16_to_cpu
c_func
(paren
op_star
id|pci_addr
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|hades_read_config_dword
r_static
r_int
id|hades_read_config_dword
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
r_volatile
r_int
r_int
op_star
id|pci_addr
suffix:semicolon
r_int
r_char
id|header_type
suffix:semicolon
r_int
id|result
suffix:semicolon
op_star
id|value
op_assign
l_int|0xffffffff
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|0x3
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pci_addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|mk_conf_addr
c_func
(paren
id|dev
comma
id|where
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
op_star
id|value
op_assign
id|le32_to_cpu
c_func
(paren
op_star
id|pci_addr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check if the value is an address on the bus. If true, add the&n;&t; * base address of the PCI memory or PCI I/O area on the Hades.&n;&t; */
r_if
c_cond
(paren
(paren
id|result
op_assign
id|hades_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_HEADER_TYPE
comma
op_amp
id|header_type
)paren
)paren
op_ne
id|PCIBIOS_SUCCESSFUL
)paren
r_return
id|result
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|where
op_ge
id|PCI_BASE_ADDRESS_0
)paren
op_logical_and
(paren
id|where
op_le
id|PCI_BASE_ADDRESS_1
)paren
)paren
op_logical_or
(paren
(paren
id|header_type
op_ne
id|PCI_HEADER_TYPE_BRIDGE
)paren
op_logical_and
(paren
(paren
id|where
op_ge
id|PCI_BASE_ADDRESS_2
)paren
op_logical_and
(paren
id|where
op_le
id|PCI_BASE_ADDRESS_5
)paren
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|value
op_amp
id|PCI_BASE_ADDRESS_SPACE
)paren
op_eq
id|PCI_BASE_ADDRESS_SPACE_IO
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Base address register that contains an I/O address. If the&n;&t;&t;&t; * address is valid on the Hades (0 &lt;= *value &lt; HADES_VIRT_IO_SIZE),&n;&t;&t;&t; * add &squot;pci_io_base_virt&squot; to the value.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_star
id|value
OL
id|HADES_VIRT_IO_SIZE
)paren
op_star
id|value
op_add_assign
id|pci_io_base_virt
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * Base address register that contains an memory address. If the&n;&t;&t;&t; * address is valid on the Hades (0 &lt;= *value &lt; HADES_MEM_SIZE),&n;&t;&t;&t; * add HADES_MEM_BASE to the value.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_star
id|value
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Base address is 0. Test if this base&n;&t;&t;&t;&t; * address register is used.&n;&t;&t;&t;&t; */
op_star
id|pci_addr
op_assign
l_int|0xffffffff
suffix:semicolon
r_if
c_cond
(paren
op_star
id|pci_addr
op_ne
l_int|0
)paren
(brace
op_star
id|pci_addr
op_assign
op_star
id|value
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
OL
id|HADES_MEM_SIZE
)paren
op_star
id|value
op_add_assign
id|HADES_MEM_BASE
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
op_star
id|value
OL
id|HADES_MEM_SIZE
)paren
op_star
id|value
op_add_assign
id|HADES_MEM_BASE
suffix:semicolon
)brace
)brace
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|hades_write_config_byte
r_static
r_int
id|hades_write_config_byte
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
r_volatile
r_int
r_char
op_star
id|pci_addr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pci_addr
op_assign
(paren
r_int
r_char
op_star
)paren
id|mk_conf_addr
c_func
(paren
id|dev
comma
id|where
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
op_star
id|pci_addr
op_assign
id|value
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|hades_write_config_word
r_static
r_int
id|hades_write_config_word
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
r_volatile
r_int
r_int
op_star
id|pci_addr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pci_addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|mk_conf_addr
c_func
(paren
id|dev
comma
id|where
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
op_star
id|pci_addr
op_assign
id|cpu_to_le16
c_func
(paren
id|value
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|hades_write_config_dword
r_static
r_int
id|hades_write_config_dword
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
r_volatile
r_int
r_int
op_star
id|pci_addr
suffix:semicolon
r_int
r_char
id|header_type
suffix:semicolon
r_int
id|result
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pci_addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|mk_conf_addr
c_func
(paren
id|dev
comma
id|where
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
multiline_comment|/*&n;&t; * Check if the value is an address on the bus. If true, subtract the&n;&t; * base address of the PCI memory or PCI I/O area on the Hades.&n;&t; */
r_if
c_cond
(paren
(paren
id|result
op_assign
id|hades_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_HEADER_TYPE
comma
op_amp
id|header_type
)paren
)paren
op_ne
id|PCIBIOS_SUCCESSFUL
)paren
r_return
id|result
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|where
op_ge
id|PCI_BASE_ADDRESS_0
)paren
op_logical_and
(paren
id|where
op_le
id|PCI_BASE_ADDRESS_1
)paren
)paren
op_logical_or
(paren
(paren
id|header_type
op_ne
id|PCI_HEADER_TYPE_BRIDGE
)paren
op_logical_and
(paren
(paren
id|where
op_ge
id|PCI_BASE_ADDRESS_2
)paren
op_logical_and
(paren
id|where
op_le
id|PCI_BASE_ADDRESS_5
)paren
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|value
op_amp
id|PCI_BASE_ADDRESS_SPACE
)paren
op_eq
id|PCI_BASE_ADDRESS_SPACE_IO
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * I/O address. Check if the address is valid address on&n;&t;&t;&t; * the Hades (pci_io_base_virt &lt;= value &lt; pci_io_base_virt +&n;&t;&t;&t; * HADES_VIRT_IO_SIZE) or if the value is 0xffffffff. If not&n;&t;&t;&t; * true do not write the base address register. If it is a&n;&t;&t;&t; * valid base address subtract &squot;pci_io_base_virt&squot; from the value.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|value
op_ge
id|pci_io_base_virt
)paren
op_logical_and
(paren
id|value
OL
(paren
id|pci_io_base_virt
op_plus
id|HADES_VIRT_IO_SIZE
)paren
)paren
)paren
id|value
op_sub_assign
id|pci_io_base_virt
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|value
op_ne
l_int|0xffffffff
)paren
r_return
id|PCIBIOS_SET_FAILED
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * Memory address. Check if the address is valid address on&n;&t;&t;&t; * the Hades (HADES_MEM_BASE &lt;= value &lt; HADES_MEM_BASE + HADES_MEM_SIZE) or&n;&t;&t;&t; * if the value is 0xffffffff. If not true do not write&n;&t;&t;&t; * the base address register. If it is a valid base address&n;&t;&t;&t; * subtract HADES_MEM_BASE from the value.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|value
op_ge
id|HADES_MEM_BASE
)paren
op_logical_and
(paren
id|value
OL
(paren
id|HADES_MEM_BASE
op_plus
id|HADES_MEM_SIZE
)paren
)paren
)paren
id|value
op_sub_assign
id|HADES_MEM_BASE
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|value
op_ne
l_int|0xffffffff
)paren
r_return
id|PCIBIOS_SET_FAILED
suffix:semicolon
)brace
)brace
)brace
op_star
id|pci_addr
op_assign
id|cpu_to_le32
c_func
(paren
id|value
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
multiline_comment|/*&n; * static inline void hades_fixup(void)&n; *&n; * Assign IRQ numbers as used by Linux to the interrupt pins&n; * of the PCI cards.&n; */
DECL|function|hades_fixup
r_static
r_void
id|__init
id|hades_fixup
c_func
(paren
r_int
id|pci_modify
)paren
(brace
r_char
id|irq_tab
(braket
l_int|4
)braket
op_assign
(brace
id|IRQ_TT_MFP_IO0
comma
multiline_comment|/* Slot 0. */
id|IRQ_TT_MFP_IO1
comma
multiline_comment|/* Slot 1. */
id|IRQ_TT_MFP_SCC
comma
multiline_comment|/* Slot 2. */
id|IRQ_TT_MFP_SCSIDMA
multiline_comment|/* Slot 3. */
)brace
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
r_char
id|slot
suffix:semicolon
multiline_comment|/*&n;&t; * Go through all devices, fixing up irqs as we see fit:&n;&t; */
r_for
c_loop
(paren
id|dev
op_assign
id|pci_devices
suffix:semicolon
id|dev
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|16
op_ne
id|PCI_BASE_CLASS_BRIDGE
)paren
(brace
id|slot
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
multiline_comment|/* Determine slot number. */
id|dev-&gt;irq
op_assign
id|irq_tab
(braket
id|slot
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pci_modify
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|dev-&gt;irq
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * static void hades_conf_device(struct pci_dev *dev)&n; *&n; * Machine dependent Configure the given device.&n; *&n; * Parameters:&n; *&n; * dev&t;&t;- the pci device.&n; */
DECL|function|hades_conf_device
r_static
r_void
id|__init
id|hades_conf_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_CACHE_LINE_SIZE
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|hades_pci_ops
r_static
r_struct
id|pci_ops
id|hades_pci_ops
op_assign
(brace
dot
id|read_byte
op_assign
id|hades_read_config_byte
comma
dot
id|read_word
op_assign
id|hades_read_config_word
comma
dot
id|read_dword
op_assign
id|hades_read_config_dword
comma
dot
id|write_byte
op_assign
id|hades_write_config_byte
comma
dot
id|write_word
op_assign
id|hades_write_config_word
comma
dot
id|write_dword
op_assign
id|hades_write_config_dword
)brace
suffix:semicolon
multiline_comment|/*&n; * struct pci_bus_info *init_hades_pci(void)&n; *&n; * Machine specific initialisation:&n; *&n; * - Allocate and initialise a &squot;pci_bus_info&squot; structure&n; * - Initialise hardware&n; *&n; * Result: pointer to &squot;pci_bus_info&squot; structure.&n; */
DECL|function|init_hades_pci
r_struct
id|pci_bus_info
op_star
id|__init
id|init_hades_pci
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_bus_info
op_star
id|bus
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Remap I/O and configuration space.&n;&t; */
id|pci_io_base_virt
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|HADES_IO_BASE
comma
id|HADES_VIRT_IO_SIZE
)paren
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
id|N_SLOTS
suffix:semicolon
id|i
op_increment
)paren
id|pci_conf_base_virt
(braket
id|i
)braket
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|pci_conf_base_phys
(braket
id|i
)braket
comma
l_int|0x10000
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate memory for bus info structure.&n;&t; */
id|bus
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pci_bus_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bus
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|bus
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|pci_bus_info
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Claim resources. The m68k has no separate I/O space, both&n;&t; * PCI memory space and PCI I/O space are in memory space. Therefore&n;&t; * the I/O resources are requested in memory space as well.&n;&t; */
r_if
c_cond
(paren
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|config_space
)paren
op_ne
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|bus
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|io_space
)paren
op_ne
l_int|0
)paren
(brace
id|release_resource
c_func
(paren
op_amp
id|config_space
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|bus
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|bus-&gt;mem_space.start
op_assign
id|HADES_MEM_BASE
suffix:semicolon
id|bus-&gt;mem_space.end
op_assign
id|HADES_MEM_BASE
op_plus
id|HADES_MEM_SIZE
op_minus
l_int|1
suffix:semicolon
id|bus-&gt;mem_space.name
op_assign
id|pci_mem_name
suffix:semicolon
macro_line|#if 1
r_if
c_cond
(paren
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|bus-&gt;mem_space
)paren
op_ne
l_int|0
)paren
(brace
id|release_resource
c_func
(paren
op_amp
id|io_space
)paren
suffix:semicolon
id|release_resource
c_func
(paren
op_amp
id|config_space
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|bus
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
id|bus-&gt;io_space.start
op_assign
id|pci_io_base_virt
suffix:semicolon
id|bus-&gt;io_space.end
op_assign
id|pci_io_base_virt
op_plus
id|HADES_VIRT_IO_SIZE
op_minus
l_int|1
suffix:semicolon
id|bus-&gt;io_space.name
op_assign
id|pci_io_name
suffix:semicolon
macro_line|#if 1
r_if
c_cond
(paren
id|request_resource
c_func
(paren
op_amp
id|ioport_resource
comma
op_amp
id|bus-&gt;io_space
)paren
op_ne
l_int|0
)paren
(brace
id|release_resource
c_func
(paren
op_amp
id|bus-&gt;mem_space
)paren
suffix:semicolon
id|release_resource
c_func
(paren
op_amp
id|io_space
)paren
suffix:semicolon
id|release_resource
c_func
(paren
op_amp
id|config_space
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|bus
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * Set hardware dependent functions.&n;&t; */
id|bus-&gt;m68k_pci_ops
op_assign
op_amp
id|hades_pci_ops
suffix:semicolon
id|bus-&gt;fixup
op_assign
id|hades_fixup
suffix:semicolon
id|bus-&gt;conf_device
op_assign
id|hades_conf_device
suffix:semicolon
multiline_comment|/*&n;&t; * Select high to low edge for PCI interrupts.&n;&t; */
id|tt_mfp.active_edge
op_and_assign
op_complement
l_int|0x27
suffix:semicolon
r_return
id|bus
suffix:semicolon
)brace
macro_line|#endif
eof
