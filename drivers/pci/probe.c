multiline_comment|/*&n; * probe.c - PCI detection and setup code&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif
DECL|macro|CARDBUS_LATENCY_TIMER
mdefine_line|#define CARDBUS_LATENCY_TIMER&t;176&t;/* secondary latency timer */
DECL|macro|CARDBUS_RESERVE_BUSNR
mdefine_line|#define CARDBUS_RESERVE_BUSNR&t;3
DECL|variable|pci_root_buses
id|LIST_HEAD
c_func
(paren
id|pci_root_buses
)paren
suffix:semicolon
DECL|variable|pci_devices
id|LIST_HEAD
c_func
(paren
id|pci_devices
)paren
suffix:semicolon
multiline_comment|/*&n; * Translate the low bits of the PCI base&n; * to the resource type&n; */
DECL|function|pci_calc_resource_flags
r_static
r_inline
r_int
r_int
id|pci_calc_resource_flags
c_func
(paren
r_int
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
id|flags
op_amp
id|PCI_BASE_ADDRESS_SPACE_IO
)paren
r_return
id|IORESOURCE_IO
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|PCI_BASE_ADDRESS_MEM_PREFETCH
)paren
r_return
id|IORESOURCE_MEM
op_or
id|IORESOURCE_PREFETCH
suffix:semicolon
r_return
id|IORESOURCE_MEM
suffix:semicolon
)brace
multiline_comment|/*&n; * Find the extent of a PCI decode..&n; */
DECL|function|pci_size
r_static
id|u32
id|pci_size
c_func
(paren
id|u32
id|base
comma
id|u32
id|maxbase
comma
r_int
r_int
id|mask
)paren
(brace
id|u32
id|size
op_assign
id|mask
op_amp
id|maxbase
suffix:semicolon
multiline_comment|/* Find the significant bits */
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Get the lowest of them to find the decode size, and&n;&t;   from that the extent.  */
id|size
op_assign
(paren
id|size
op_amp
op_complement
(paren
id|size
op_minus
l_int|1
)paren
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* base == maxbase can be valid only if the BAR has&n;&t;   already been programmed with all 1s.  */
r_if
c_cond
(paren
id|base
op_eq
id|maxbase
op_logical_and
(paren
(paren
id|base
op_or
id|size
)paren
op_amp
id|mask
)paren
op_ne
id|mask
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|function|pci_read_bases
r_static
r_void
id|pci_read_bases
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
r_int
id|howmany
comma
r_int
id|rom
)paren
(brace
r_int
r_int
id|pos
comma
id|reg
comma
id|next
suffix:semicolon
id|u32
id|l
comma
id|sz
suffix:semicolon
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_for
c_loop
(paren
id|pos
op_assign
l_int|0
suffix:semicolon
id|pos
OL
id|howmany
suffix:semicolon
id|pos
op_assign
id|next
)paren
(brace
id|next
op_assign
id|pos
op_plus
l_int|1
suffix:semicolon
id|res
op_assign
op_amp
id|dev-&gt;resource
(braket
id|pos
)braket
suffix:semicolon
id|res-&gt;name
op_assign
id|dev-&gt;dev.name
suffix:semicolon
id|reg
op_assign
id|PCI_BASE_ADDRESS_0
op_plus
(paren
id|pos
op_lshift
l_int|2
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|reg
comma
op_amp
id|l
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|reg
comma
op_complement
l_int|0
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|reg
comma
op_amp
id|sz
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|reg
comma
id|l
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sz
op_logical_or
id|sz
op_eq
l_int|0xffffffff
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|l
op_eq
l_int|0xffffffff
)paren
id|l
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|l
op_amp
id|PCI_BASE_ADDRESS_SPACE
)paren
op_eq
id|PCI_BASE_ADDRESS_SPACE_MEMORY
)paren
(brace
id|sz
op_assign
id|pci_size
c_func
(paren
id|l
comma
id|sz
comma
id|PCI_BASE_ADDRESS_MEM_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sz
)paren
r_continue
suffix:semicolon
id|res-&gt;start
op_assign
id|l
op_amp
id|PCI_BASE_ADDRESS_MEM_MASK
suffix:semicolon
id|res-&gt;flags
op_or_assign
id|l
op_amp
op_complement
id|PCI_BASE_ADDRESS_MEM_MASK
suffix:semicolon
)brace
r_else
(brace
id|sz
op_assign
id|pci_size
c_func
(paren
id|l
comma
id|sz
comma
id|PCI_BASE_ADDRESS_IO_MASK
op_amp
l_int|0xffff
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sz
)paren
r_continue
suffix:semicolon
id|res-&gt;start
op_assign
id|l
op_amp
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
id|res-&gt;flags
op_or_assign
id|l
op_amp
op_complement
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
)brace
id|res-&gt;end
op_assign
id|res-&gt;start
op_plus
(paren
r_int
r_int
)paren
id|sz
suffix:semicolon
id|res-&gt;flags
op_or_assign
id|pci_calc_resource_flags
c_func
(paren
id|l
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|l
op_amp
(paren
id|PCI_BASE_ADDRESS_SPACE
op_or
id|PCI_BASE_ADDRESS_MEM_TYPE_MASK
)paren
)paren
op_eq
(paren
id|PCI_BASE_ADDRESS_SPACE_MEMORY
op_or
id|PCI_BASE_ADDRESS_MEM_TYPE_64
)paren
)paren
(brace
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|reg
op_plus
l_int|4
comma
op_amp
id|l
)paren
suffix:semicolon
id|next
op_increment
suffix:semicolon
macro_line|#if BITS_PER_LONG == 64
id|res-&gt;start
op_or_assign
(paren
(paren
r_int
r_int
)paren
id|l
)paren
op_lshift
l_int|32
suffix:semicolon
id|res-&gt;end
op_assign
id|res-&gt;start
op_plus
id|sz
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|reg
op_plus
l_int|4
comma
op_complement
l_int|0
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|reg
op_plus
l_int|4
comma
op_amp
id|sz
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|reg
op_plus
l_int|4
comma
id|l
)paren
suffix:semicolon
r_if
c_cond
(paren
op_complement
id|sz
)paren
id|res-&gt;end
op_assign
id|res-&gt;start
op_plus
l_int|0xffffffff
op_plus
(paren
(paren
(paren
r_int
r_int
)paren
op_complement
id|sz
)paren
op_lshift
l_int|32
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|l
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Unable to handle 64-bit address for device %s&bslash;n&quot;
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
id|res-&gt;start
op_assign
l_int|0
suffix:semicolon
id|res-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
macro_line|#endif
)brace
)brace
r_if
c_cond
(paren
id|rom
)paren
(brace
id|dev-&gt;rom_base_reg
op_assign
id|rom
suffix:semicolon
id|res
op_assign
op_amp
id|dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
suffix:semicolon
id|res-&gt;name
op_assign
id|dev-&gt;dev.name
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|rom
comma
op_amp
id|l
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|rom
comma
op_complement
id|PCI_ROM_ADDRESS_ENABLE
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|rom
comma
op_amp
id|sz
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|rom
comma
id|l
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l
op_eq
l_int|0xffffffff
)paren
id|l
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sz
op_logical_and
id|sz
op_ne
l_int|0xffffffff
)paren
(brace
id|sz
op_assign
id|pci_size
c_func
(paren
id|l
comma
id|sz
comma
id|PCI_ROM_ADDRESS_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sz
)paren
(brace
id|res-&gt;flags
op_assign
(paren
id|l
op_amp
id|PCI_ROM_ADDRESS_ENABLE
)paren
op_or
id|IORESOURCE_MEM
op_or
id|IORESOURCE_PREFETCH
op_or
id|IORESOURCE_READONLY
op_or
id|IORESOURCE_CACHEABLE
suffix:semicolon
id|res-&gt;start
op_assign
id|l
op_amp
id|PCI_ROM_ADDRESS_MASK
suffix:semicolon
id|res-&gt;end
op_assign
id|res-&gt;start
op_plus
(paren
r_int
r_int
)paren
id|sz
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|pci_read_bridge_bases
r_void
id|__devinit
id|pci_read_bridge_bases
c_func
(paren
r_struct
id|pci_bus
op_star
id|child
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|child-&gt;self
suffix:semicolon
id|u8
id|io_base_lo
comma
id|io_limit_lo
suffix:semicolon
id|u16
id|mem_base_lo
comma
id|mem_limit_lo
suffix:semicolon
r_int
r_int
id|base
comma
id|limit
suffix:semicolon
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
multiline_comment|/* It&squot;s a host bus, nothing to read */
r_return
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;transparent
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Transparent bridge - %s&bslash;n&quot;
comma
id|dev-&gt;dev.name
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
id|PCI_BUS_NUM_RESOURCES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|child-&gt;resource
(braket
id|i
)braket
op_assign
id|child-&gt;parent-&gt;resource
(braket
id|i
)braket
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
id|child-&gt;resource
(braket
id|i
)braket
op_assign
op_amp
id|dev-&gt;resource
(braket
id|PCI_BRIDGE_RESOURCES
op_plus
id|i
)braket
suffix:semicolon
)brace
id|res
op_assign
id|child-&gt;resource
(braket
l_int|0
)braket
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_IO_BASE
comma
op_amp
id|io_base_lo
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_IO_LIMIT
comma
op_amp
id|io_limit_lo
)paren
suffix:semicolon
id|base
op_assign
(paren
id|io_base_lo
op_amp
id|PCI_IO_RANGE_MASK
)paren
op_lshift
l_int|8
suffix:semicolon
id|limit
op_assign
(paren
id|io_limit_lo
op_amp
id|PCI_IO_RANGE_MASK
)paren
op_lshift
l_int|8
suffix:semicolon
r_if
c_cond
(paren
(paren
id|io_base_lo
op_amp
id|PCI_IO_RANGE_TYPE_MASK
)paren
op_eq
id|PCI_IO_RANGE_TYPE_32
)paren
(brace
id|u16
id|io_base_hi
comma
id|io_limit_hi
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_IO_BASE_UPPER16
comma
op_amp
id|io_base_hi
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_IO_LIMIT_UPPER16
comma
op_amp
id|io_limit_hi
)paren
suffix:semicolon
id|base
op_or_assign
(paren
id|io_base_hi
op_lshift
l_int|16
)paren
suffix:semicolon
id|limit
op_or_assign
(paren
id|io_limit_hi
op_lshift
l_int|16
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|base
op_logical_and
id|base
op_le
id|limit
)paren
(brace
id|res-&gt;flags
op_assign
(paren
id|io_base_lo
op_amp
id|PCI_IO_RANGE_TYPE_MASK
)paren
op_or
id|IORESOURCE_IO
suffix:semicolon
id|res-&gt;start
op_assign
id|base
suffix:semicolon
id|res-&gt;end
op_assign
id|limit
op_plus
l_int|0xfff
suffix:semicolon
)brace
id|res
op_assign
id|child-&gt;resource
(braket
l_int|1
)braket
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_MEMORY_BASE
comma
op_amp
id|mem_base_lo
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_MEMORY_LIMIT
comma
op_amp
id|mem_limit_lo
)paren
suffix:semicolon
id|base
op_assign
(paren
id|mem_base_lo
op_amp
id|PCI_MEMORY_RANGE_MASK
)paren
op_lshift
l_int|16
suffix:semicolon
id|limit
op_assign
(paren
id|mem_limit_lo
op_amp
id|PCI_MEMORY_RANGE_MASK
)paren
op_lshift
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|base
op_logical_and
id|base
op_le
id|limit
)paren
(brace
id|res-&gt;flags
op_assign
(paren
id|mem_base_lo
op_amp
id|PCI_MEMORY_RANGE_TYPE_MASK
)paren
op_or
id|IORESOURCE_MEM
suffix:semicolon
id|res-&gt;start
op_assign
id|base
suffix:semicolon
id|res-&gt;end
op_assign
id|limit
op_plus
l_int|0xfffff
suffix:semicolon
)brace
id|res
op_assign
id|child-&gt;resource
(braket
l_int|2
)braket
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_PREF_MEMORY_BASE
comma
op_amp
id|mem_base_lo
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_PREF_MEMORY_LIMIT
comma
op_amp
id|mem_limit_lo
)paren
suffix:semicolon
id|base
op_assign
(paren
id|mem_base_lo
op_amp
id|PCI_PREF_RANGE_MASK
)paren
op_lshift
l_int|16
suffix:semicolon
id|limit
op_assign
(paren
id|mem_limit_lo
op_amp
id|PCI_PREF_RANGE_MASK
)paren
op_lshift
l_int|16
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mem_base_lo
op_amp
id|PCI_PREF_RANGE_TYPE_MASK
)paren
op_eq
id|PCI_PREF_RANGE_TYPE_64
)paren
(brace
id|u32
id|mem_base_hi
comma
id|mem_limit_hi
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|PCI_PREF_BASE_UPPER32
comma
op_amp
id|mem_base_hi
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|PCI_PREF_LIMIT_UPPER32
comma
op_amp
id|mem_limit_hi
)paren
suffix:semicolon
macro_line|#if BITS_PER_LONG == 64
id|base
op_or_assign
(paren
(paren
r_int
)paren
id|mem_base_hi
)paren
op_lshift
l_int|32
suffix:semicolon
id|limit
op_or_assign
(paren
(paren
r_int
)paren
id|mem_limit_hi
)paren
op_lshift
l_int|32
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|mem_base_hi
op_logical_or
id|mem_limit_hi
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Unable to handle 64-bit address space for %s&bslash;n&quot;
comma
id|child-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
)brace
r_if
c_cond
(paren
id|base
op_logical_and
id|base
op_le
id|limit
)paren
(brace
id|res-&gt;flags
op_assign
(paren
id|mem_base_lo
op_amp
id|PCI_MEMORY_RANGE_TYPE_MASK
)paren
op_or
id|IORESOURCE_MEM
op_or
id|IORESOURCE_PREFETCH
suffix:semicolon
id|res-&gt;start
op_assign
id|base
suffix:semicolon
id|res-&gt;end
op_assign
id|limit
op_plus
l_int|0xfffff
suffix:semicolon
)brace
)brace
DECL|function|pci_alloc_bus
r_static
r_struct
id|pci_bus
op_star
id|__devinit
id|pci_alloc_bus
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_bus
op_star
id|b
suffix:semicolon
id|b
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|b
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b
)paren
(brace
id|memset
c_func
(paren
id|b
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|b
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|b-&gt;node
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|b-&gt;children
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|b-&gt;devices
)paren
suffix:semicolon
)brace
r_return
id|b
suffix:semicolon
)brace
r_static
r_struct
id|pci_bus
op_star
id|__devinit
DECL|function|pci_alloc_child_bus
id|pci_alloc_child_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|parent
comma
r_struct
id|pci_dev
op_star
id|bridge
comma
r_int
id|busnr
)paren
(brace
r_struct
id|pci_bus
op_star
id|child
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate a new bus, and inherit stuff from the parent..&n;&t; */
id|child
op_assign
id|pci_alloc_bus
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child
)paren
(brace
r_int
id|i
suffix:semicolon
id|child-&gt;self
op_assign
id|bridge
suffix:semicolon
id|child-&gt;parent
op_assign
id|parent
suffix:semicolon
id|child-&gt;ops
op_assign
id|parent-&gt;ops
suffix:semicolon
id|child-&gt;sysdata
op_assign
id|parent-&gt;sysdata
suffix:semicolon
id|child-&gt;dev
op_assign
op_amp
id|bridge-&gt;dev
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set up the primary, secondary and subordinate&n;&t;&t; * bus numbers.&n;&t;&t; */
id|child-&gt;number
op_assign
id|child-&gt;secondary
op_assign
id|busnr
suffix:semicolon
id|child-&gt;primary
op_assign
id|parent-&gt;secondary
suffix:semicolon
id|child-&gt;subordinate
op_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* Set up default resource pointers and names.. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|child-&gt;resource
(braket
id|i
)braket
op_assign
op_amp
id|bridge-&gt;resource
(braket
id|PCI_BRIDGE_RESOURCES
op_plus
id|i
)braket
suffix:semicolon
id|child-&gt;resource
(braket
id|i
)braket
op_member_access_from_pointer
id|name
op_assign
id|child-&gt;name
suffix:semicolon
)brace
id|bridge-&gt;subordinate
op_assign
id|child
suffix:semicolon
)brace
r_return
id|child
suffix:semicolon
)brace
DECL|function|pci_add_new_bus
r_struct
id|pci_bus
op_star
id|__devinit
id|pci_add_new_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|parent
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|busnr
)paren
(brace
r_struct
id|pci_bus
op_star
id|child
suffix:semicolon
id|child
op_assign
id|pci_alloc_child_bus
c_func
(paren
id|parent
comma
id|dev
comma
id|busnr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child
)paren
id|list_add_tail
c_func
(paren
op_amp
id|child-&gt;node
comma
op_amp
id|parent-&gt;children
)paren
suffix:semicolon
r_return
id|child
suffix:semicolon
)brace
r_static
r_int
r_int
id|__devinit
id|pci_scan_child_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
suffix:semicolon
multiline_comment|/*&n; * If it&squot;s a bridge, configure it and scan the bus behind it.&n; * For CardBus bridges, we don&squot;t scan behind as the devices will&n; * be handled by the bridge driver itself.&n; *&n; * We need to process bridges in two passes -- first we scan those&n; * already configured by the BIOS and after we are done with all of&n; * them, we proceed to assigning numbers to the remaining buses in&n; * order to avoid overlaps between old and new bus numbers.&n; */
DECL|function|pci_scan_bridge
r_int
id|__devinit
id|pci_scan_bridge
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|max
comma
r_int
id|pass
)paren
(brace
r_struct
id|pci_bus
op_star
id|child
suffix:semicolon
r_int
id|is_cardbus
op_assign
(paren
id|dev-&gt;hdr_type
op_eq
id|PCI_HEADER_TYPE_CARDBUS
)paren
suffix:semicolon
id|u32
id|buses
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|PCI_PRIMARY_BUS
comma
op_amp
id|buses
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;Scanning behind PCI bridge %s, config %06x, pass %d&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|buses
op_amp
l_int|0xffffff
comma
id|pass
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buses
op_amp
l_int|0xffff00
)paren
op_logical_and
op_logical_neg
id|pcibios_assign_all_busses
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|is_cardbus
)paren
(brace
r_int
r_int
id|cmax
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Bus already configured by firmware, process it in the first&n;&t;&t; * pass and just note the configuration.&n;&t;&t; */
r_if
c_cond
(paren
id|pass
)paren
r_return
id|max
suffix:semicolon
id|child
op_assign
id|pci_alloc_child_bus
c_func
(paren
id|bus
comma
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|child-&gt;primary
op_assign
id|buses
op_amp
l_int|0xFF
suffix:semicolon
id|child-&gt;secondary
op_assign
(paren
id|buses
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|child-&gt;subordinate
op_assign
(paren
id|buses
op_rshift
l_int|16
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|child-&gt;number
op_assign
id|child-&gt;secondary
suffix:semicolon
id|cmax
op_assign
id|pci_scan_child_bus
c_func
(paren
id|child
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmax
OG
id|max
)paren
id|max
op_assign
id|cmax
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * We need to assign a number to this bus which we always&n;&t;&t; * do in the second pass.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|pass
)paren
r_return
id|max
suffix:semicolon
multiline_comment|/* Clear errors */
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_STATUS
comma
l_int|0xffff
)paren
suffix:semicolon
id|child
op_assign
id|pci_alloc_child_bus
c_func
(paren
id|bus
comma
id|dev
comma
op_increment
id|max
)paren
suffix:semicolon
id|buses
op_assign
(paren
id|buses
op_amp
l_int|0xff000000
)paren
op_or
(paren
(paren
r_int
r_int
)paren
(paren
id|child-&gt;primary
)paren
op_lshift
l_int|0
)paren
op_or
(paren
(paren
r_int
r_int
)paren
(paren
id|child-&gt;secondary
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
r_int
r_int
)paren
(paren
id|child-&gt;subordinate
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * yenta.c forces a secondary latency timer of 176.&n;&t;&t; * Copy that behaviour here.&n;&t;&t; */
r_if
c_cond
(paren
id|is_cardbus
)paren
(brace
id|buses
op_and_assign
op_complement
l_int|0xff000000
suffix:semicolon
id|buses
op_or_assign
id|CARDBUS_LATENCY_TIMER
op_lshift
l_int|24
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * We need to blast all three values with a single write.&n;&t;&t; */
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_PRIMARY_BUS
comma
id|buses
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_cardbus
)paren
(brace
multiline_comment|/* Now we can scan all subordinate buses... */
id|max
op_assign
id|pci_scan_child_bus
c_func
(paren
id|child
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * For CardBus bridges, we leave 4 bus numbers&n;&t;&t;&t; * as cards with a PCI-to-PCI bridge can be&n;&t;&t;&t; * inserted later.&n;&t;&t;&t; */
id|max
op_add_assign
id|CARDBUS_RESERVE_BUSNR
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Set the subordinate bus number to its real value.&n;&t;&t; */
id|child-&gt;subordinate
op_assign
id|max
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_SUBORDINATE_BUS
comma
id|max
)paren
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|child-&gt;name
comma
(paren
id|is_cardbus
ques
c_cond
l_string|&quot;PCI CardBus #%02x&quot;
suffix:colon
l_string|&quot;PCI Bus #%02x&quot;
)paren
comma
id|child-&gt;number
)paren
suffix:semicolon
r_return
id|max
suffix:semicolon
)brace
multiline_comment|/*&n; * Read interrupt line and base address registers.&n; * The architecture-dependent code can tweak these, of course.&n; */
DECL|function|pci_read_irq
r_static
r_void
id|pci_read_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
r_char
id|irq
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
)paren
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
op_amp
id|irq
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_setup_device - fill in class and map information of a device&n; * @dev: the device structure to fill&n; *&n; * Initialize the device structure with information about the device&squot;s &n; * vendor,class,memory and IO-space addresses,IRQ lines etc.&n; * Called at initialisation of the PCI subsystem and by CardBus services.&n; * Returns 0 on success and -1 if unknown type of device (not normal, bridge&n; * or CardBus).&n; */
DECL|function|pci_setup_device
r_static
r_int
id|pci_setup_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u32
r_class
suffix:semicolon
id|sprintf
c_func
(paren
id|dev-&gt;slot_name
comma
l_string|&quot;%02x:%02x.%d&quot;
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
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|dev-&gt;dev.name
comma
l_string|&quot;PCI device %04x:%04x&quot;
comma
id|dev-&gt;vendor
comma
id|dev-&gt;device
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dev-&gt;pools
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|PCI_CLASS_REVISION
comma
op_amp
r_class
)paren
suffix:semicolon
r_class
op_rshift_assign
l_int|8
suffix:semicolon
multiline_comment|/* upper 3 bytes */
id|dev
op_member_access_from_pointer
r_class
op_assign
r_class
suffix:semicolon
r_class
op_rshift_assign
l_int|8
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;Found %02x:%02x [%04x/%04x] %06x %02x&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|dev-&gt;vendor
comma
id|dev-&gt;device
comma
r_class
comma
id|dev-&gt;hdr_type
)paren
suffix:semicolon
multiline_comment|/* &quot;Unknown power state&quot; */
id|dev-&gt;current_state
op_assign
l_int|4
suffix:semicolon
r_switch
c_cond
(paren
id|dev-&gt;hdr_type
)paren
(brace
multiline_comment|/* header type */
r_case
id|PCI_HEADER_TYPE_NORMAL
suffix:colon
multiline_comment|/* standard header */
r_if
c_cond
(paren
r_class
op_eq
id|PCI_CLASS_BRIDGE_PCI
)paren
r_goto
id|bad
suffix:semicolon
id|pci_read_irq
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pci_read_bases
c_func
(paren
id|dev
comma
l_int|6
comma
id|PCI_ROM_ADDRESS
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_SUBSYSTEM_VENDOR_ID
comma
op_amp
id|dev-&gt;subsystem_vendor
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_SUBSYSTEM_ID
comma
op_amp
id|dev-&gt;subsystem_device
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_HEADER_TYPE_BRIDGE
suffix:colon
multiline_comment|/* bridge header */
r_if
c_cond
(paren
r_class
op_ne
id|PCI_CLASS_BRIDGE_PCI
)paren
r_goto
id|bad
suffix:semicolon
multiline_comment|/* The PCI-to-PCI bridge spec requires that subtractive&n;&t;&t;   decoding (i.e. transparent) bridge must have programming&n;&t;&t;   interface code of 0x01. */
id|dev-&gt;transparent
op_assign
(paren
(paren
id|dev
op_member_access_from_pointer
r_class
op_amp
l_int|0xff
)paren
op_eq
l_int|1
)paren
suffix:semicolon
id|pci_read_bases
c_func
(paren
id|dev
comma
l_int|2
comma
id|PCI_ROM_ADDRESS1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_HEADER_TYPE_CARDBUS
suffix:colon
multiline_comment|/* CardBus bridge header */
r_if
c_cond
(paren
r_class
op_ne
id|PCI_CLASS_BRIDGE_CARDBUS
)paren
r_goto
id|bad
suffix:semicolon
id|pci_read_irq
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pci_read_bases
c_func
(paren
id|dev
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_CB_SUBSYSTEM_VENDOR_ID
comma
op_amp
id|dev-&gt;subsystem_vendor
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_CB_SUBSYSTEM_ID
comma
op_amp
id|dev-&gt;subsystem_device
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* unknown header */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: device %s has unknown header type %02x, ignoring.&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|dev-&gt;hdr_type
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
id|bad
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: %s: class %x doesn&squot;t match header type %02x. Ignoring class.&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
r_class
comma
id|dev-&gt;hdr_type
)paren
suffix:semicolon
id|dev
op_member_access_from_pointer
r_class
op_assign
id|PCI_CLASS_NOT_DEFINED
suffix:semicolon
)brace
multiline_comment|/* We found a fine healthy device, go go go... */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_release_dev - free a pci device structure when all users of it are finished.&n; * @dev: device that&squot;s been disconnected&n; *&n; * Will be called only by the device core when all users of this pci device are&n; * done.&n; */
DECL|function|pci_release_dev
r_static
r_void
id|pci_release_dev
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
id|pci_dev
op_assign
id|to_pci_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the config data for a PCI device, sanity-check it&n; * and fill in the dev structure...&n; */
r_static
r_struct
id|pci_dev
op_star
id|__devinit
DECL|function|pci_scan_device
id|pci_scan_device
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
id|devfn
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|u32
id|l
suffix:semicolon
id|u8
id|hdr_type
suffix:semicolon
r_if
c_cond
(paren
id|pci_bus_read_config_byte
c_func
(paren
id|bus
comma
id|devfn
comma
id|PCI_HEADER_TYPE
comma
op_amp
id|hdr_type
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|pci_bus_read_config_dword
c_func
(paren
id|bus
comma
id|devfn
comma
id|PCI_VENDOR_ID
comma
op_amp
id|l
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* some broken boards return 0 or ~0 if a slot is empty: */
r_if
c_cond
(paren
id|l
op_eq
l_int|0xffffffff
op_logical_or
id|l
op_eq
l_int|0x00000000
op_logical_or
id|l
op_eq
l_int|0x0000ffff
op_logical_or
id|l
op_eq
l_int|0xffff0000
)paren
r_return
l_int|NULL
suffix:semicolon
id|dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pci_dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|pci_dev
)paren
)paren
suffix:semicolon
id|dev-&gt;bus
op_assign
id|bus
suffix:semicolon
id|dev-&gt;sysdata
op_assign
id|bus-&gt;sysdata
suffix:semicolon
id|dev-&gt;dev.parent
op_assign
id|bus-&gt;dev
suffix:semicolon
id|dev-&gt;dev.bus
op_assign
op_amp
id|pci_bus_type
suffix:semicolon
id|dev-&gt;devfn
op_assign
id|devfn
suffix:semicolon
id|dev-&gt;hdr_type
op_assign
id|hdr_type
op_amp
l_int|0x7f
suffix:semicolon
id|dev-&gt;multifunction
op_assign
op_logical_neg
op_logical_neg
(paren
id|hdr_type
op_amp
l_int|0x80
)paren
suffix:semicolon
id|dev-&gt;vendor
op_assign
id|l
op_amp
l_int|0xffff
suffix:semicolon
id|dev-&gt;device
op_assign
(paren
id|l
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
suffix:semicolon
multiline_comment|/* Assume 32-bit PCI; let 64-bit PCI cards (which are far rarer)&n;&t;   set this higher, assuming the system even supports it.  */
id|dev-&gt;dma_mask
op_assign
l_int|0xffffffff
suffix:semicolon
id|dev-&gt;consistent_dma_mask
op_assign
l_int|0xffffffff
suffix:semicolon
r_if
c_cond
(paren
id|pci_setup_device
c_func
(paren
id|dev
)paren
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|device_initialize
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
id|dev-&gt;dev.release
op_assign
id|pci_release_dev
suffix:semicolon
id|pci_dev_get
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pci_name_device
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* now put in global tree */
id|sprintf
c_func
(paren
id|dev-&gt;dev.bus_id
comma
l_string|&quot;%04x:%s&quot;
comma
id|pci_domain_nr
c_func
(paren
id|bus
)paren
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
id|dev-&gt;dev.dma_mask
op_assign
op_amp
id|dev-&gt;dma_mask
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_scan_slot - scan a PCI slot on a bus for devices.&n; * @bus: PCI bus to scan&n; * @devfn: slot number to scan (must have zero function.)&n; *&n; * Scan a PCI slot on the specified PCI bus for devices, adding&n; * discovered devices to the @bus-&gt;devices list.  New devices&n; * will have an empty dev-&gt;global_list head.&n; */
DECL|function|pci_scan_slot
r_int
id|__devinit
id|pci_scan_slot
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
id|devfn
)paren
(brace
r_int
id|func
comma
id|nr
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|func
op_assign
l_int|0
suffix:semicolon
id|func
OL
l_int|8
suffix:semicolon
id|func
op_increment
comma
id|devfn
op_increment
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|dev
op_assign
id|pci_scan_device
c_func
(paren
id|bus
comma
id|devfn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|func
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_break
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_continue
suffix:semicolon
id|dev-&gt;multifunction
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Fix up broken headers */
id|pci_fixup_device
c_func
(paren
id|PCI_FIXUP_HEADER
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Add the device to our list of discovered devices&n;&t;&t; * and the bus list for fixup functions, etc.&n;&t;&t; */
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dev-&gt;global_list
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|dev-&gt;bus_list
comma
op_amp
id|bus-&gt;devices
)paren
suffix:semicolon
id|nr
op_increment
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If this is a single function device,&n;&t;&t; * don&squot;t scan past the first function.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;multifunction
)paren
r_break
suffix:semicolon
)brace
r_return
id|nr
suffix:semicolon
)brace
DECL|function|pci_scan_child_bus
r_static
r_int
r_int
id|__devinit
id|pci_scan_child_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_int
r_int
id|devfn
comma
id|pass
comma
id|max
op_assign
id|bus-&gt;secondary
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;Scanning bus %02x&bslash;n&quot;
comma
id|bus-&gt;number
)paren
suffix:semicolon
multiline_comment|/* Go find them, Rover! */
r_for
c_loop
(paren
id|devfn
op_assign
l_int|0
suffix:semicolon
id|devfn
OL
l_int|0x100
suffix:semicolon
id|devfn
op_add_assign
l_int|8
)paren
id|pci_scan_slot
c_func
(paren
id|bus
comma
id|devfn
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * After performing arch-dependent fixup of the bus, look behind&n;&t; * all PCI-to-PCI bridges on this bus.&n;&t; */
id|DBG
c_func
(paren
l_string|&quot;Fixups for bus %02x&bslash;n&quot;
comma
id|bus-&gt;number
)paren
suffix:semicolon
id|pcibios_fixup_bus
c_func
(paren
id|bus
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pass
op_assign
l_int|0
suffix:semicolon
id|pass
OL
l_int|2
suffix:semicolon
id|pass
op_increment
)paren
id|list_for_each_entry
c_func
(paren
id|dev
comma
op_amp
id|bus-&gt;devices
comma
id|bus_list
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;hdr_type
op_eq
id|PCI_HEADER_TYPE_BRIDGE
op_logical_or
id|dev-&gt;hdr_type
op_eq
id|PCI_HEADER_TYPE_CARDBUS
)paren
id|max
op_assign
id|pci_scan_bridge
c_func
(paren
id|bus
comma
id|dev
comma
id|max
comma
id|pass
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We&squot;ve scanned the bus and so we know all about what&squot;s on&n;&t; * the other side of any bridges that may be on this bus plus&n;&t; * any devices.&n;&t; *&n;&t; * Return how far we&squot;ve got finding sub-buses.&n;&t; */
id|DBG
c_func
(paren
l_string|&quot;Bus scan for %02x returning with max=%02x&bslash;n&quot;
comma
id|bus-&gt;number
comma
id|max
)paren
suffix:semicolon
r_return
id|max
suffix:semicolon
)brace
DECL|function|pci_do_scan_bus
r_int
r_int
id|__devinit
id|pci_do_scan_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_int
r_int
id|max
suffix:semicolon
id|max
op_assign
id|pci_scan_child_bus
c_func
(paren
id|bus
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Make the discovered devices available.&n;&t; */
id|pci_bus_add_devices
c_func
(paren
id|bus
)paren
suffix:semicolon
r_return
id|max
suffix:semicolon
)brace
DECL|function|pci_bus_exists
r_int
id|__devinit
id|pci_bus_exists
c_func
(paren
r_const
r_struct
id|list_head
op_star
id|list
comma
r_int
id|nr
)paren
(brace
r_const
r_struct
id|pci_bus
op_star
id|b
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|b
comma
id|list
comma
id|node
)paren
(brace
r_if
c_cond
(paren
id|b-&gt;number
op_eq
id|nr
op_logical_or
id|pci_bus_exists
c_func
(paren
op_amp
id|b-&gt;children
comma
id|nr
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
DECL|function|pci_alloc_primary_bus_parented
r_static
r_struct
id|pci_bus
op_star
id|__devinit
id|pci_alloc_primary_bus_parented
c_func
(paren
r_struct
id|device
op_star
id|parent
comma
r_int
id|bus
)paren
(brace
r_struct
id|pci_bus
op_star
id|b
suffix:semicolon
r_if
c_cond
(paren
id|pci_bus_exists
c_func
(paren
op_amp
id|pci_root_buses
comma
id|bus
)paren
)paren
(brace
multiline_comment|/* If we already got to this bus through a different bridge, ignore it */
id|DBG
c_func
(paren
l_string|&quot;PCI: Bus %02x already known&bslash;n&quot;
comma
id|bus
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|b
op_assign
id|pci_alloc_bus
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|b
)paren
r_return
l_int|NULL
suffix:semicolon
id|b-&gt;dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
(paren
id|b-&gt;dev
)paren
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|b-&gt;dev
)paren
(brace
id|kfree
c_func
(paren
id|b
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|list_add_tail
c_func
(paren
op_amp
id|b-&gt;node
comma
op_amp
id|pci_root_buses
)paren
suffix:semicolon
id|memset
c_func
(paren
id|b-&gt;dev
comma
l_int|0
comma
r_sizeof
(paren
op_star
(paren
id|b-&gt;dev
)paren
)paren
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|b-&gt;dev-&gt;bus_id
comma
l_string|&quot;pci%d&quot;
comma
id|bus
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|b-&gt;dev-&gt;name
comma
l_string|&quot;Host/PCI Bridge&quot;
)paren
suffix:semicolon
id|b-&gt;dev-&gt;parent
op_assign
id|parent
suffix:semicolon
id|device_register
c_func
(paren
id|b-&gt;dev
)paren
suffix:semicolon
id|b-&gt;number
op_assign
id|b-&gt;secondary
op_assign
id|bus
suffix:semicolon
id|b-&gt;resource
(braket
l_int|0
)braket
op_assign
op_amp
id|ioport_resource
suffix:semicolon
id|b-&gt;resource
(braket
l_int|1
)braket
op_assign
op_amp
id|iomem_resource
suffix:semicolon
r_return
id|b
suffix:semicolon
)brace
DECL|function|pci_scan_bus_parented
r_struct
id|pci_bus
op_star
id|__devinit
id|pci_scan_bus_parented
c_func
(paren
r_struct
id|device
op_star
id|parent
comma
r_int
id|bus
comma
r_struct
id|pci_ops
op_star
id|ops
comma
r_void
op_star
id|sysdata
)paren
(brace
r_struct
id|pci_bus
op_star
id|b
op_assign
id|pci_alloc_primary_bus_parented
c_func
(paren
id|parent
comma
id|bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b
)paren
(brace
id|b-&gt;sysdata
op_assign
id|sysdata
suffix:semicolon
id|b-&gt;ops
op_assign
id|ops
suffix:semicolon
id|b-&gt;subordinate
op_assign
id|pci_scan_child_bus
c_func
(paren
id|b
)paren
suffix:semicolon
id|pci_bus_add_devices
c_func
(paren
id|b
)paren
suffix:semicolon
)brace
r_return
id|b
suffix:semicolon
)brace
DECL|variable|pci_scan_bus_parented
id|EXPORT_SYMBOL
c_func
(paren
id|pci_scan_bus_parented
)paren
suffix:semicolon
DECL|variable|pci_root_buses
id|EXPORT_SYMBOL
c_func
(paren
id|pci_root_buses
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HOTPLUG
DECL|variable|pci_add_new_bus
id|EXPORT_SYMBOL
c_func
(paren
id|pci_add_new_bus
)paren
suffix:semicolon
DECL|variable|pci_do_scan_bus
id|EXPORT_SYMBOL
c_func
(paren
id|pci_do_scan_bus
)paren
suffix:semicolon
DECL|variable|pci_scan_slot
id|EXPORT_SYMBOL
c_func
(paren
id|pci_scan_slot
)paren
suffix:semicolon
DECL|variable|pci_scan_bus
id|EXPORT_SYMBOL
c_func
(paren
id|pci_scan_bus
)paren
suffix:semicolon
DECL|variable|pci_scan_bridge
id|EXPORT_SYMBOL
c_func
(paren
id|pci_scan_bridge
)paren
suffix:semicolon
macro_line|#endif
eof
