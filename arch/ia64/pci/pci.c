multiline_comment|/*&n; * pci.c - Low-Level PCI Access in IA-64&n; *&n; * Derived from bios32.c of i386 tree.&n; *&n; * Copyright (C) 2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&t;Bjorn Helgaas &lt;bjorn_helgaas@hp.com&gt;&n; *&n; * Note: Above list of copyright holders is incomplete...&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|# include &lt;asm/smp.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif
DECL|variable|pcibios_fixups
r_struct
id|pci_fixup
id|pcibios_fixups
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/*&n; * Low-level SAL-based PCI configuration access functions. Note that SAL&n; * calls are already serialized (via sal_lock), so we don&squot;t need another&n; * synchronization mechanism here.&n; */
DECL|macro|PCI_SAL_ADDRESS
mdefine_line|#define PCI_SAL_ADDRESS(seg, bus, devfn, reg) &bslash;&n;&t;((u64)(seg &lt;&lt; 24) | (u64)(bus &lt;&lt; 16) | &bslash;&n;&t; (u64)(devfn &lt;&lt; 8) | (u64)(reg))
r_static
r_int
DECL|function|pci_sal_read
id|pci_sal_read
(paren
r_int
id|seg
comma
r_int
id|bus
comma
r_int
id|devfn
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
id|result
op_assign
l_int|0
suffix:semicolon
id|u64
id|data
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|seg
OG
l_int|255
)paren
op_logical_or
(paren
id|bus
OG
l_int|255
)paren
op_logical_or
(paren
id|devfn
OG
l_int|255
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
id|result
op_assign
id|ia64_sal_pci_config_read
c_func
(paren
id|PCI_SAL_ADDRESS
c_func
(paren
id|seg
comma
id|bus
comma
id|devfn
comma
id|reg
)paren
comma
l_int|0
comma
id|len
comma
op_amp
id|data
)paren
suffix:semicolon
op_star
id|value
op_assign
(paren
id|u32
)paren
id|data
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_static
r_int
DECL|function|pci_sal_write
id|pci_sal_write
(paren
r_int
id|seg
comma
r_int
id|bus
comma
r_int
id|devfn
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
r_if
c_cond
(paren
(paren
id|seg
OG
l_int|255
)paren
op_logical_or
(paren
id|bus
OG
l_int|255
)paren
op_logical_or
(paren
id|devfn
OG
l_int|255
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
r_return
id|ia64_sal_pci_config_write
c_func
(paren
id|PCI_SAL_ADDRESS
c_func
(paren
id|seg
comma
id|bus
comma
id|devfn
comma
id|reg
)paren
comma
l_int|0
comma
id|len
comma
id|value
)paren
suffix:semicolon
)brace
DECL|variable|pci_sal_ops
r_static
r_struct
id|pci_raw_ops
id|pci_sal_ops
op_assign
(brace
dot
id|read
op_assign
id|pci_sal_read
comma
dot
id|write
op_assign
id|pci_sal_write
)brace
suffix:semicolon
multiline_comment|/* SAL 3.2 adds support for extended config space. */
DECL|macro|PCI_SAL_EXT_ADDRESS
mdefine_line|#define PCI_SAL_EXT_ADDRESS(seg, bus, devfn, reg) &bslash;&n;&t;((u64)(seg &lt;&lt; 28) | (u64)(bus &lt;&lt; 20) | &bslash;&n;&t; (u64)(devfn &lt;&lt; 12) | (u64)(reg))
r_static
r_int
DECL|function|pci_sal_ext_read
id|pci_sal_ext_read
(paren
r_int
id|seg
comma
r_int
id|bus
comma
r_int
id|devfn
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
id|result
op_assign
l_int|0
suffix:semicolon
id|u64
id|data
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|seg
OG
l_int|65535
)paren
op_logical_or
(paren
id|bus
OG
l_int|255
)paren
op_logical_or
(paren
id|devfn
OG
l_int|255
)paren
op_logical_or
(paren
id|reg
OG
l_int|4095
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|result
op_assign
id|ia64_sal_pci_config_read
c_func
(paren
id|PCI_SAL_EXT_ADDRESS
c_func
(paren
id|seg
comma
id|bus
comma
id|devfn
comma
id|reg
)paren
comma
l_int|1
comma
id|len
comma
op_amp
id|data
)paren
suffix:semicolon
op_star
id|value
op_assign
(paren
id|u32
)paren
id|data
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_static
r_int
DECL|function|pci_sal_ext_write
id|pci_sal_ext_write
(paren
r_int
id|seg
comma
r_int
id|bus
comma
r_int
id|devfn
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
r_if
c_cond
(paren
(paren
id|seg
OG
l_int|65535
)paren
op_logical_or
(paren
id|bus
OG
l_int|255
)paren
op_logical_or
(paren
id|devfn
OG
l_int|255
)paren
op_logical_or
(paren
id|reg
OG
l_int|4095
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|ia64_sal_pci_config_write
c_func
(paren
id|PCI_SAL_EXT_ADDRESS
c_func
(paren
id|seg
comma
id|bus
comma
id|devfn
comma
id|reg
)paren
comma
l_int|1
comma
id|len
comma
id|value
)paren
suffix:semicolon
)brace
DECL|variable|pci_sal_ext_ops
r_static
r_struct
id|pci_raw_ops
id|pci_sal_ext_ops
op_assign
(brace
dot
id|read
op_assign
id|pci_sal_ext_read
comma
dot
id|write
op_assign
id|pci_sal_ext_write
)brace
suffix:semicolon
DECL|variable|raw_pci_ops
r_struct
id|pci_raw_ops
op_star
id|raw_pci_ops
op_assign
op_amp
id|pci_sal_ops
suffix:semicolon
multiline_comment|/* default to SAL &lt; 3.2 */
r_static
r_int
id|__init
DECL|function|pci_set_sal_ops
id|pci_set_sal_ops
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|sal_revision
op_ge
id|SAL_VERSION_CODE
c_func
(paren
l_int|3
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Using SAL 3.2 to access PCI config space&bslash;n&quot;
)paren
suffix:semicolon
id|raw_pci_ops
op_assign
op_amp
id|pci_sal_ext_ops
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pci_set_sal_ops
id|arch_initcall
c_func
(paren
id|pci_set_sal_ops
)paren
suffix:semicolon
r_static
r_int
DECL|function|pci_read
id|pci_read
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
r_return
id|raw_pci_ops
op_member_access_from_pointer
id|read
c_func
(paren
id|pci_domain_nr
c_func
(paren
id|bus
)paren
comma
id|bus-&gt;number
comma
id|devfn
comma
id|where
comma
id|size
comma
id|value
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pci_write
id|pci_write
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
r_return
id|raw_pci_ops
op_member_access_from_pointer
id|write
c_func
(paren
id|pci_domain_nr
c_func
(paren
id|bus
)paren
comma
id|bus-&gt;number
comma
id|devfn
comma
id|where
comma
id|size
comma
id|value
)paren
suffix:semicolon
)brace
DECL|variable|pci_root_ops
r_static
r_struct
id|pci_ops
id|pci_root_ops
op_assign
(brace
dot
id|read
op_assign
id|pci_read
comma
dot
id|write
op_assign
id|pci_write
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|pci_acpi_init
id|pci_acpi_init
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|acpi_pci_irq_init
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Using ACPI for IRQ routing&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: Invalid ACPI-PCI IRQ routing table&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pci_acpi_init
id|subsys_initcall
c_func
(paren
id|pci_acpi_init
)paren
suffix:semicolon
multiline_comment|/* Called by ACPI when it finds a new root bus.  */
r_static
r_struct
id|pci_controller
op_star
id|__devinit
DECL|function|alloc_pci_controller
id|alloc_pci_controller
(paren
r_int
id|seg
)paren
(brace
r_struct
id|pci_controller
op_star
id|controller
suffix:semicolon
id|controller
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|controller
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|controller
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|controller
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|controller
)paren
)paren
suffix:semicolon
id|controller-&gt;segment
op_assign
id|seg
suffix:semicolon
r_return
id|controller
suffix:semicolon
)brace
r_static
r_int
id|__devinit
DECL|function|alloc_resource
id|alloc_resource
(paren
r_char
op_star
id|name
comma
r_struct
id|resource
op_star
id|root
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|resource
op_star
id|res
suffix:semicolon
id|res
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|res
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|res
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|res
)paren
)paren
suffix:semicolon
id|res-&gt;name
op_assign
id|name
suffix:semicolon
id|res-&gt;start
op_assign
id|start
suffix:semicolon
id|res-&gt;end
op_assign
id|end
suffix:semicolon
id|res-&gt;flags
op_assign
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|insert_resource
c_func
(paren
id|root
comma
id|res
)paren
)paren
(brace
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|u64
id|__devinit
DECL|function|add_io_space
id|add_io_space
(paren
r_struct
id|acpi_resource_address64
op_star
id|addr
)paren
(brace
id|u64
id|offset
suffix:semicolon
r_int
id|sparse
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|addr-&gt;address_translation_offset
op_eq
l_int|0
)paren
r_return
id|IO_SPACE_BASE
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* part of legacy IO space */
r_if
c_cond
(paren
id|addr-&gt;attribute.io.translation_attribute
op_eq
id|ACPI_SPARSE_TRANSLATION
)paren
id|sparse
op_assign
l_int|1
suffix:semicolon
id|offset
op_assign
(paren
id|u64
)paren
id|ioremap
c_func
(paren
id|addr-&gt;address_translation_offset
comma
l_int|0
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
id|num_io_spaces
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|io_space
(braket
id|i
)braket
dot
id|mmio_base
op_eq
id|offset
op_logical_and
id|io_space
(braket
id|i
)braket
dot
id|sparse
op_eq
id|sparse
)paren
r_return
id|IO_SPACE_BASE
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num_io_spaces
op_eq
id|MAX_IO_SPACES
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Too many IO port spaces&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_complement
l_int|0
suffix:semicolon
)brace
id|i
op_assign
id|num_io_spaces
op_increment
suffix:semicolon
id|io_space
(braket
id|i
)braket
dot
id|mmio_base
op_assign
id|offset
suffix:semicolon
id|io_space
(braket
id|i
)braket
dot
id|sparse
op_assign
id|sparse
suffix:semicolon
r_return
id|IO_SPACE_BASE
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
r_static
id|acpi_status
id|__devinit
DECL|function|count_window
id|count_window
(paren
r_struct
id|acpi_resource
op_star
id|resource
comma
r_void
op_star
id|data
)paren
(brace
r_int
r_int
op_star
id|windows
op_assign
(paren
r_int
r_int
op_star
)paren
id|data
suffix:semicolon
r_struct
id|acpi_resource_address64
id|addr
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|status
op_assign
id|acpi_resource_to_address64
c_func
(paren
id|resource
comma
op_amp
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
c_func
(paren
id|status
)paren
)paren
r_if
c_cond
(paren
id|addr.resource_type
op_eq
id|ACPI_MEMORY_RANGE
op_logical_or
id|addr.resource_type
op_eq
id|ACPI_IO_RANGE
)paren
(paren
op_star
id|windows
)paren
op_increment
suffix:semicolon
r_return
id|AE_OK
suffix:semicolon
)brace
DECL|struct|pci_root_info
r_struct
id|pci_root_info
(brace
DECL|member|controller
r_struct
id|pci_controller
op_star
id|controller
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
r_static
id|acpi_status
id|__devinit
DECL|function|add_window
id|add_window
(paren
r_struct
id|acpi_resource
op_star
id|res
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|pci_root_info
op_star
id|info
op_assign
(paren
r_struct
id|pci_root_info
op_star
)paren
id|data
suffix:semicolon
r_struct
id|pci_window
op_star
id|window
suffix:semicolon
r_struct
id|acpi_resource_address64
id|addr
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
r_int
r_int
id|flags
comma
id|offset
op_assign
l_int|0
suffix:semicolon
r_struct
id|resource
op_star
id|root
suffix:semicolon
id|status
op_assign
id|acpi_resource_to_address64
c_func
(paren
id|res
comma
op_amp
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
c_func
(paren
id|status
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|addr.address_length
)paren
r_return
id|AE_OK
suffix:semicolon
r_if
c_cond
(paren
id|addr.resource_type
op_eq
id|ACPI_MEMORY_RANGE
)paren
(brace
id|flags
op_assign
id|IORESOURCE_MEM
suffix:semicolon
id|root
op_assign
op_amp
id|iomem_resource
suffix:semicolon
id|offset
op_assign
id|addr.address_translation_offset
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|addr.resource_type
op_eq
id|ACPI_IO_RANGE
)paren
(brace
id|flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
id|root
op_assign
op_amp
id|ioport_resource
suffix:semicolon
id|offset
op_assign
id|add_io_space
c_func
(paren
op_amp
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_eq
op_complement
l_int|0
)paren
r_return
id|AE_OK
suffix:semicolon
)brace
r_else
r_return
id|AE_OK
suffix:semicolon
id|window
op_assign
op_amp
id|info-&gt;controller-&gt;window
(braket
id|info-&gt;controller-&gt;windows
op_increment
)braket
suffix:semicolon
id|window-&gt;resource.flags
op_or_assign
id|flags
suffix:semicolon
id|window-&gt;resource.start
op_assign
id|addr.min_address_range
suffix:semicolon
id|window-&gt;resource.end
op_assign
id|addr.max_address_range
suffix:semicolon
id|window-&gt;offset
op_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|alloc_resource
c_func
(paren
id|info-&gt;name
comma
id|root
comma
id|addr.min_address_range
op_plus
id|offset
comma
id|addr.max_address_range
op_plus
id|offset
comma
id|flags
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;alloc 0x%lx-0x%lx from %s for %s failed&bslash;n&quot;
comma
id|addr.min_address_range
op_plus
id|offset
comma
id|addr.max_address_range
op_plus
id|offset
comma
id|root-&gt;name
comma
id|info-&gt;name
)paren
suffix:semicolon
)brace
r_return
id|AE_OK
suffix:semicolon
)brace
r_struct
id|pci_bus
op_star
id|__devinit
DECL|function|pci_acpi_scan_root
id|pci_acpi_scan_root
(paren
r_struct
id|acpi_device
op_star
id|device
comma
r_int
id|domain
comma
r_int
id|bus
)paren
(brace
r_struct
id|pci_root_info
id|info
suffix:semicolon
r_struct
id|pci_controller
op_star
id|controller
suffix:semicolon
r_int
r_int
id|windows
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
id|controller
op_assign
id|alloc_pci_controller
c_func
(paren
id|domain
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|controller
)paren
r_goto
id|out1
suffix:semicolon
id|controller-&gt;acpi_handle
op_assign
id|device-&gt;handle
suffix:semicolon
id|acpi_walk_resources
c_func
(paren
id|device-&gt;handle
comma
id|METHOD_NAME__CRS
comma
id|count_window
comma
op_amp
id|windows
)paren
suffix:semicolon
id|controller-&gt;window
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|controller-&gt;window
)paren
op_star
id|windows
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|controller-&gt;window
)paren
r_goto
id|out2
suffix:semicolon
id|name
op_assign
id|kmalloc
c_func
(paren
l_int|16
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_goto
id|out3
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;PCI Bus %04x:%02x&quot;
comma
id|domain
comma
id|bus
)paren
suffix:semicolon
id|info.controller
op_assign
id|controller
suffix:semicolon
id|info.name
op_assign
id|name
suffix:semicolon
id|acpi_walk_resources
c_func
(paren
id|device-&gt;handle
comma
id|METHOD_NAME__CRS
comma
id|add_window
comma
op_amp
id|info
)paren
suffix:semicolon
r_return
id|pci_scan_bus
c_func
(paren
id|bus
comma
op_amp
id|pci_root_ops
comma
id|controller
)paren
suffix:semicolon
id|out3
suffix:colon
id|kfree
c_func
(paren
id|controller-&gt;window
)paren
suffix:semicolon
id|out2
suffix:colon
id|kfree
c_func
(paren
id|controller
)paren
suffix:semicolon
id|out1
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
r_void
id|__init
DECL|function|pcibios_fixup_device_resources
id|pcibios_fixup_device_resources
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|pci_controller
op_star
id|controller
op_assign
id|PCI_CONTROLLER
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|pci_window
op_star
id|window
suffix:semicolon
r_int
id|i
comma
id|j
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
id|PCI_NUM_RESOURCES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
)paren
r_continue
suffix:semicolon
DECL|macro|contains
mdefine_line|#define contains(win, res)&t;((res)-&gt;start &gt;= (win)-&gt;start &amp;&amp; &bslash;&n;&t;&t;&t;&t; (res)-&gt;end   &lt;= (win)-&gt;end)
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|controller-&gt;windows
suffix:semicolon
id|j
op_increment
)paren
(brace
id|window
op_assign
op_amp
id|controller-&gt;window
(braket
id|j
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_amp
id|IORESOURCE_MEM
op_logical_and
id|window-&gt;resource.flags
op_amp
id|IORESOURCE_MEM
)paren
op_logical_or
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_amp
id|IORESOURCE_IO
op_logical_and
id|window-&gt;resource.flags
op_amp
id|IORESOURCE_IO
)paren
)paren
op_logical_and
id|contains
c_func
(paren
op_amp
id|window-&gt;resource
comma
op_amp
id|dev-&gt;resource
(braket
id|i
)braket
)paren
)paren
(brace
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_add_assign
id|window-&gt;offset
suffix:semicolon
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|end
op_add_assign
id|window-&gt;offset
suffix:semicolon
)brace
)brace
id|pci_claim_resource
c_func
(paren
id|dev
comma
id|i
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  Called after each bus is probed, but before its children are examined.&n; */
r_void
id|__devinit
DECL|function|pcibios_fixup_bus
id|pcibios_fixup_bus
(paren
r_struct
id|pci_bus
op_star
id|b
)paren
(brace
r_struct
id|list_head
op_star
id|ln
suffix:semicolon
r_for
c_loop
(paren
id|ln
op_assign
id|b-&gt;devices.next
suffix:semicolon
id|ln
op_ne
op_amp
id|b-&gt;devices
suffix:semicolon
id|ln
op_assign
id|ln-&gt;next
)paren
id|pcibios_fixup_device_resources
c_func
(paren
id|pci_dev_b
c_func
(paren
id|ln
)paren
comma
id|b
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_void
id|__devinit
DECL|function|pcibios_update_irq
id|pcibios_update_irq
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|irq
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|irq
)paren
suffix:semicolon
multiline_comment|/* ??? FIXME -- record old value for shutdown.  */
)brace
r_static
r_inline
r_int
DECL|function|pcibios_enable_resources
id|pcibios_enable_resources
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|mask
)paren
(brace
id|u16
id|cmd
comma
id|old_cmd
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_struct
id|resource
op_star
id|r
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
id|old_cmd
op_assign
id|cmd
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
l_int|6
suffix:semicolon
id|idx
op_increment
)paren
(brace
multiline_comment|/* Only set up the desired resources.  */
r_if
c_cond
(paren
op_logical_neg
(paren
id|mask
op_amp
(paren
l_int|1
op_lshift
id|idx
)paren
)paren
)paren
r_continue
suffix:semicolon
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;start
op_logical_and
id|r-&gt;end
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Device %s not available because of resource collisions&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|r-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_IO
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_MEMORY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
dot
id|start
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_MEMORY
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_ne
id|old_cmd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Enabling device %s (%04x -&gt; %04x)&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
id|old_cmd
comma
id|cmd
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|pcibios_enable_device
id|pcibios_enable_device
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|mask
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|pcibios_enable_resources
c_func
(paren
id|dev
comma
id|mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Found IRQ %d for device %s&bslash;n&quot;
comma
id|dev-&gt;irq
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
id|acpi_pci_irq_enable
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_void
DECL|function|pcibios_align_resource
id|pcibios_align_resource
(paren
r_void
op_star
id|data
comma
r_struct
id|resource
op_star
id|res
comma
r_int
r_int
id|size
comma
r_int
r_int
id|align
)paren
(brace
)brace
multiline_comment|/*&n; * PCI BIOS setup, always defaults to SAL interface&n; */
r_char
op_star
id|__init
DECL|function|pcibios_setup
id|pcibios_setup
(paren
r_char
op_star
id|str
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_int
DECL|function|pci_mmap_page_range
id|pci_mmap_page_range
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_enum
id|pci_mmap_state
id|mmap_state
comma
r_int
id|write_combine
)paren
(brace
multiline_comment|/*&n;&t; * I/O space cannot be accessed via normal processor loads and stores on this&n;&t; * platform.&n;&t; */
r_if
c_cond
(paren
id|mmap_state
op_eq
id|pci_mmap_io
)paren
multiline_comment|/*&n;&t;&t; * XXX we could relax this for I/O spaces for which ACPI indicates that&n;&t;&t; * the space is 1-to-1 mapped.  But at the moment, we don&squot;t support&n;&t;&t; * multiple PCI address spaces and the legacy I/O space is not 1-to-1&n;&t;&t; * mapped, so this is moot.&n;&t;&t; */
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t; * Leave vm_pgoff as-is, the PCI space address is the physical address on this&n;&t; * platform.&n;&t; */
id|vma-&gt;vm_flags
op_or_assign
(paren
id|VM_SHM
op_or
id|VM_LOCKED
op_or
id|VM_IO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_combine
)paren
id|vma-&gt;vm_page_prot
op_assign
id|pgprot_writecombine
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
suffix:semicolon
r_else
id|vma-&gt;vm_page_prot
op_assign
id|pgprot_noncached
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remap_page_range
c_func
(paren
id|vma
comma
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
comma
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_page_prot
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_cacheline_size - determine cacheline size for PCI devices&n; * @dev: void&n; *&n; * We want to use the line-size of the outer-most cache.  We assume&n; * that this line-size is the same for all CPUs.&n; *&n; * Code mostly taken from arch/ia64/kernel/palinfo.c:cache_info().&n; *&n; * RETURNS: An appropriate -ERRNO error value on eror, or zero for success.&n; */
r_static
r_int
r_int
DECL|function|pci_cacheline_size
id|pci_cacheline_size
(paren
r_void
)paren
(brace
id|u64
id|levels
comma
id|unique_caches
suffix:semicolon
id|s64
id|status
suffix:semicolon
id|pal_cache_config_info_t
id|cci
suffix:semicolon
r_static
id|u8
id|cacheline_size
suffix:semicolon
r_if
c_cond
(paren
id|cacheline_size
)paren
r_return
id|cacheline_size
suffix:semicolon
id|status
op_assign
id|ia64_pal_cache_summary
c_func
(paren
op_amp
id|levels
comma
op_amp
id|unique_caches
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: ia64_pal_cache_summary() failed (status=%ld)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|status
)paren
suffix:semicolon
r_return
id|SMP_CACHE_BYTES
suffix:semicolon
)brace
id|status
op_assign
id|ia64_pal_cache_config_info
c_func
(paren
id|levels
op_minus
l_int|1
comma
multiline_comment|/* cache_type (data_or_unified)= */
l_int|2
comma
op_amp
id|cci
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: ia64_pal_cache_config_info() failed (status=%ld)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|status
)paren
suffix:semicolon
r_return
id|SMP_CACHE_BYTES
suffix:semicolon
)brace
id|cacheline_size
op_assign
l_int|1
op_lshift
id|cci.pcci_line_size
suffix:semicolon
r_return
id|cacheline_size
suffix:semicolon
)brace
multiline_comment|/**&n; * pcibios_prep_mwi - helper function for drivers/pci/pci.c:pci_set_mwi()&n; * @dev: the PCI device for which MWI is enabled&n; *&n; * For ia64, we can get the cacheline sizes from PAL.&n; *&n; * RETURNS: An appropriate -ERRNO error value on eror, or zero for success.&n; */
r_int
DECL|function|pcibios_prep_mwi
id|pcibios_prep_mwi
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
r_int
id|desired_linesize
comma
id|current_linesize
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|u8
id|pci_linesize
suffix:semicolon
id|desired_linesize
op_assign
id|pci_cacheline_size
c_func
(paren
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_CACHE_LINE_SIZE
comma
op_amp
id|pci_linesize
)paren
suffix:semicolon
id|current_linesize
op_assign
l_int|4
op_star
id|pci_linesize
suffix:semicolon
r_if
c_cond
(paren
id|desired_linesize
op_ne
id|current_linesize
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: slot %s has incorrect PCI cache line size of %lu bytes,&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
id|current_linesize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current_linesize
OG
id|desired_linesize
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; expected %lu bytes instead&bslash;n&quot;
comma
id|desired_linesize
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot; correcting to %lu&bslash;n&quot;
comma
id|desired_linesize
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_CACHE_LINE_SIZE
comma
id|desired_linesize
op_div
l_int|4
)paren
suffix:semicolon
)brace
)brace
r_return
id|rc
suffix:semicolon
)brace
DECL|function|pci_vector_resources
r_int
id|pci_vector_resources
c_func
(paren
r_int
id|last
comma
r_int
id|nr_released
)paren
(brace
r_int
id|count
op_assign
id|nr_released
suffix:semicolon
id|count
op_add_assign
(paren
id|IA64_LAST_DEVICE_VECTOR
op_minus
id|last
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
eof
