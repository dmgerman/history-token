multiline_comment|/*&n; * mmconfig.c - Low-level direct PCI config space access via MMCONFIG&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;pci.h&quot;
multiline_comment|/* The physical address of the MMCONFIG aperture.  Set from ACPI tables. */
DECL|variable|pci_mmcfg_base_addr
id|u32
id|pci_mmcfg_base_addr
suffix:semicolon
DECL|macro|mmcfg_virt_addr
mdefine_line|#define mmcfg_virt_addr ((void __iomem *) fix_to_virt(FIX_PCIE_MCFG))
multiline_comment|/* The base address of the last MMCONFIG device accessed */
DECL|variable|mmcfg_last_accessed_device
r_static
id|u32
id|mmcfg_last_accessed_device
suffix:semicolon
multiline_comment|/*&n; * Functions for accessing PCI configuration space with MMCONFIG accesses&n; */
DECL|function|pci_exp_set_dev_base
r_static
r_inline
r_void
id|pci_exp_set_dev_base
c_func
(paren
r_int
id|bus
comma
r_int
id|devfn
)paren
(brace
id|u32
id|dev_base
op_assign
id|pci_mmcfg_base_addr
op_or
(paren
id|bus
op_lshift
l_int|20
)paren
op_or
(paren
id|devfn
op_lshift
l_int|12
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_base
op_ne
id|mmcfg_last_accessed_device
)paren
(brace
id|mmcfg_last_accessed_device
op_assign
id|dev_base
suffix:semicolon
id|set_fixmap
c_func
(paren
id|FIX_PCIE_MCFG
comma
id|dev_base
)paren
suffix:semicolon
)brace
)brace
DECL|function|pci_mmcfg_read
r_static
r_int
id|pci_mmcfg_read
c_func
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pci_config_lock
comma
id|flags
)paren
suffix:semicolon
id|pci_exp_set_dev_base
c_func
(paren
id|bus
comma
id|devfn
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
id|readb
c_func
(paren
id|mmcfg_virt_addr
op_plus
id|reg
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
id|readw
c_func
(paren
id|mmcfg_virt_addr
op_plus
id|reg
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
id|readl
c_func
(paren
id|mmcfg_virt_addr
op_plus
id|reg
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
DECL|function|pci_mmcfg_write
r_static
r_int
id|pci_mmcfg_write
c_func
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pci_config_lock
comma
id|flags
)paren
suffix:semicolon
id|pci_exp_set_dev_base
c_func
(paren
id|bus
comma
id|devfn
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
id|writeb
c_func
(paren
id|value
comma
id|mmcfg_virt_addr
op_plus
id|reg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|writew
c_func
(paren
id|value
comma
id|mmcfg_virt_addr
op_plus
id|reg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|writel
c_func
(paren
id|value
comma
id|mmcfg_virt_addr
op_plus
id|reg
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Dummy read to flush PCI write */
id|readl
c_func
(paren
id|mmcfg_virt_addr
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
DECL|variable|pci_mmcfg
r_static
r_struct
id|pci_raw_ops
id|pci_mmcfg
op_assign
(brace
dot
id|read
op_assign
id|pci_mmcfg_read
comma
dot
id|write
op_assign
id|pci_mmcfg_write
comma
)brace
suffix:semicolon
DECL|function|pci_mmcfg_init
r_static
r_int
id|__init
id|pci_mmcfg_init
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
id|PCI_PROBE_MMCONF
)paren
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_mmcfg_base_addr
)paren
r_goto
id|out
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Using MMCONFIG&bslash;n&quot;
)paren
suffix:semicolon
id|raw_pci_ops
op_assign
op_amp
id|pci_mmcfg
suffix:semicolon
id|pci_probe
op_assign
(paren
id|pci_probe
op_amp
op_complement
id|PCI_PROBE_MASK
)paren
op_or
id|PCI_PROBE_MMCONF
suffix:semicolon
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pci_mmcfg_init
id|arch_initcall
c_func
(paren
id|pci_mmcfg_init
)paren
suffix:semicolon
eof
