multiline_comment|/*&n; * pci.c - Low-Level PCI Access in IA-64&n; *&n; * Derived from bios32.c of i386 tree.&n; */
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#ifdef CONFIG_IA64_MCA
r_extern
r_void
id|ia64_mca_check_errors
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * This interrupt-safe spinlock protects all accesses to PCI&n; * configuration space.&n; */
DECL|variable|pci_lock
id|spinlock_t
id|pci_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|pcibios_fixups
r_struct
id|pci_fixup
id|pcibios_fixups
(braket
)braket
op_assign
(brace
(brace
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* Macro to build a PCI configuration address to be passed as a parameter to SAL. */
DECL|macro|PCI_CONFIG_ADDRESS
mdefine_line|#define PCI_CONFIG_ADDRESS(dev, where) &bslash;&n;&t;(((u64) dev-&gt;bus-&gt;number &lt;&lt; 16) | ((u64) (dev-&gt;devfn &amp; 0xff) &lt;&lt; 8) | (where &amp; 0xff))
r_static
r_int
DECL|function|pci_conf_read_config_byte
id|pci_conf_read_config_byte
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
id|s64
id|status
suffix:semicolon
id|u64
id|lval
suffix:semicolon
id|status
op_assign
id|ia64_sal_pci_config_read
c_func
(paren
id|PCI_CONFIG_ADDRESS
c_func
(paren
id|dev
comma
id|where
)paren
comma
l_int|1
comma
op_amp
id|lval
)paren
suffix:semicolon
op_star
id|value
op_assign
id|lval
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|pci_conf_read_config_word
id|pci_conf_read_config_word
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
id|s64
id|status
suffix:semicolon
id|u64
id|lval
suffix:semicolon
id|status
op_assign
id|ia64_sal_pci_config_read
c_func
(paren
id|PCI_CONFIG_ADDRESS
c_func
(paren
id|dev
comma
id|where
)paren
comma
l_int|2
comma
op_amp
id|lval
)paren
suffix:semicolon
op_star
id|value
op_assign
id|lval
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|pci_conf_read_config_dword
id|pci_conf_read_config_dword
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
id|s64
id|status
suffix:semicolon
id|u64
id|lval
suffix:semicolon
id|status
op_assign
id|ia64_sal_pci_config_read
c_func
(paren
id|PCI_CONFIG_ADDRESS
c_func
(paren
id|dev
comma
id|where
)paren
comma
l_int|4
comma
op_amp
id|lval
)paren
suffix:semicolon
op_star
id|value
op_assign
id|lval
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|pci_conf_write_config_byte
id|pci_conf_write_config_byte
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
id|ia64_sal_pci_config_write
c_func
(paren
id|PCI_CONFIG_ADDRESS
c_func
(paren
id|dev
comma
id|where
)paren
comma
l_int|1
comma
id|value
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pci_conf_write_config_word
id|pci_conf_write_config_word
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
id|ia64_sal_pci_config_write
c_func
(paren
id|PCI_CONFIG_ADDRESS
c_func
(paren
id|dev
comma
id|where
)paren
comma
l_int|2
comma
id|value
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pci_conf_write_config_dword
id|pci_conf_write_config_dword
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
id|ia64_sal_pci_config_write
c_func
(paren
id|PCI_CONFIG_ADDRESS
c_func
(paren
id|dev
comma
id|where
)paren
comma
l_int|4
comma
id|value
)paren
suffix:semicolon
)brace
DECL|variable|pci_conf
r_struct
id|pci_ops
id|pci_conf
op_assign
(brace
id|pci_conf_read_config_byte
comma
id|pci_conf_read_config_word
comma
id|pci_conf_read_config_dword
comma
id|pci_conf_write_config_byte
comma
id|pci_conf_write_config_word
comma
id|pci_conf_write_config_dword
)brace
suffix:semicolon
multiline_comment|/*&n; * Initialization. Uses the SAL interface&n; */
r_void
id|__init
DECL|function|pcibios_init
id|pcibios_init
(paren
r_void
)paren
(brace
DECL|macro|PCI_BUSES_TO_SCAN
macro_line|#&t;define PCI_BUSES_TO_SCAN 255
r_int
id|i
suffix:semicolon
macro_line|#ifdef CONFIG_IA64_MCA
id|ia64_mca_check_errors
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* For post-failure MCA error logging */
macro_line|#endif
id|platform_pci_fixup
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* phase 0 initialization (before PCI bus has been scanned) */
id|printk
c_func
(paren
l_string|&quot;PCI: Probing PCI hardware&bslash;n&quot;
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
id|PCI_BUSES_TO_SCAN
suffix:semicolon
id|i
op_increment
)paren
id|pci_scan_bus
c_func
(paren
id|i
comma
op_amp
id|pci_conf
comma
l_int|NULL
)paren
suffix:semicolon
id|platform_pci_fixup
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* phase 1 initialization (after PCI bus has been scanned) */
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; *  Called after each bus is probed, but before its children&n; *  are examined.&n; */
r_void
id|__init
DECL|function|pcibios_fixup_bus
id|pcibios_fixup_bus
(paren
r_struct
id|pci_bus
op_star
id|b
)paren
(brace
r_return
suffix:semicolon
)brace
r_void
id|__init
DECL|function|pcibios_update_resource
id|pcibios_update_resource
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|resource
op_star
id|root
comma
r_struct
id|resource
op_star
id|res
comma
r_int
id|resource
)paren
(brace
r_int
r_int
id|where
comma
id|size
suffix:semicolon
id|u32
id|reg
suffix:semicolon
id|where
op_assign
id|PCI_BASE_ADDRESS_0
op_plus
(paren
id|resource
op_star
l_int|4
)paren
suffix:semicolon
id|size
op_assign
id|res-&gt;end
op_minus
id|res-&gt;start
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|where
comma
op_amp
id|reg
)paren
suffix:semicolon
id|reg
op_assign
(paren
id|reg
op_amp
id|size
)paren
op_or
(paren
(paren
(paren
id|u32
)paren
(paren
id|res-&gt;start
op_minus
id|root-&gt;start
)paren
)paren
op_amp
op_complement
id|size
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|where
comma
id|reg
)paren
suffix:semicolon
multiline_comment|/* ??? FIXME -- record old value for shutdown.  */
)brace
r_void
id|__init
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
r_void
id|__init
DECL|function|pcibios_fixup_pbus_ranges
id|pcibios_fixup_pbus_ranges
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_struct
id|pbus_set_ranges_data
op_star
id|ranges
)paren
(brace
id|ranges-&gt;io_start
op_sub_assign
id|bus-&gt;resource
(braket
l_int|0
)braket
op_member_access_from_pointer
id|start
suffix:semicolon
id|ranges-&gt;io_end
op_sub_assign
id|bus-&gt;resource
(braket
l_int|0
)braket
op_member_access_from_pointer
id|start
suffix:semicolon
id|ranges-&gt;mem_start
op_sub_assign
id|bus-&gt;resource
(braket
l_int|1
)braket
op_member_access_from_pointer
id|start
suffix:semicolon
id|ranges-&gt;mem_end
op_sub_assign
id|bus-&gt;resource
(braket
l_int|1
)braket
op_member_access_from_pointer
id|start
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
)paren
(brace
multiline_comment|/* Not needed, since we enable all devices at startup.  */
r_return
l_int|0
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
eof
