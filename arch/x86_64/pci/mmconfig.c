multiline_comment|/*&n; * mmconfig.c - Low-level direct PCI config space access via MMCONFIG&n; * &n; * This is an 64bit optimized version that always keeps the full mmconfig&n; * space mapped. This allows lockless config space operation.&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|macro|MMCONFIG_APER_SIZE
mdefine_line|#define MMCONFIG_APER_SIZE (256*1024*1024)
multiline_comment|/* The physical address of the MMCONFIG aperture.  Set from ACPI tables. */
DECL|variable|pci_mmcfg_base_addr
id|u32
id|pci_mmcfg_base_addr
suffix:semicolon
multiline_comment|/* Static virtual mapping of the MMCONFIG aperture */
DECL|variable|pci_mmcfg_virt
r_char
op_star
id|pci_mmcfg_virt
suffix:semicolon
DECL|function|pci_dev_base
r_static
r_inline
r_char
op_star
id|pci_dev_base
c_func
(paren
r_int
id|bus
comma
r_int
id|devfn
)paren
(brace
r_return
id|pci_mmcfg_virt
op_plus
(paren
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
)paren
suffix:semicolon
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
r_char
op_star
id|addr
op_assign
id|pci_dev_base
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
id|unlikely
c_func
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
)paren
r_return
op_minus
id|EINVAL
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
id|addr
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
id|addr
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
id|addr
op_plus
id|reg
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
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
r_char
op_star
id|addr
op_assign
id|pci_dev_base
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
id|unlikely
c_func
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
)paren
r_return
op_minus
id|EINVAL
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
id|addr
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
id|addr
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
id|addr
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
id|addr
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
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_mmcfg_base_addr
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* RED-PEN i386 doesn&squot;t do _nocache right now */
id|pci_mmcfg_virt
op_assign
id|ioremap_nocache
c_func
(paren
id|pci_mmcfg_base_addr
comma
id|MMCONFIG_APER_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_mmcfg_virt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Cannot map mmconfig aperture&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Using MMCONFIG at %lx&bslash;n&quot;
comma
id|pci_mmcfg_base_addr
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
