multiline_comment|/*&n; * linux/include/asm-generic/pci.h&n; *&n; *  Copyright (C) 2003 Russell King&n; */
macro_line|#ifndef _ASM_GENERIC_PCI_H
DECL|macro|_ASM_GENERIC_PCI_H
mdefine_line|#define _ASM_GENERIC_PCI_H
multiline_comment|/**&n; * pcibios_resource_to_bus - convert resource to PCI bus address&n; * @dev: device which owns this resource&n; * @region: converted bus-centric region (start,end)&n; * @res: resource to convert&n; *&n; * Convert a resource to a PCI device bus address or bus window.&n; */
r_static
r_inline
r_void
DECL|function|pcibios_resource_to_bus
id|pcibios_resource_to_bus
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|pci_bus_region
op_star
id|region
comma
r_struct
id|resource
op_star
id|res
)paren
(brace
id|region-&gt;start
op_assign
id|res-&gt;start
suffix:semicolon
id|region-&gt;end
op_assign
id|res-&gt;end
suffix:semicolon
)brace
DECL|macro|pcibios_scan_all_fns
mdefine_line|#define pcibios_scan_all_fns(a, b)&t;0
macro_line|#ifndef HAVE_ARCH_PCI_GET_LEGACY_IDE_IRQ
DECL|function|pci_get_legacy_ide_irq
r_static
r_inline
r_int
id|pci_get_legacy_ide_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|channel
)paren
(brace
r_return
id|channel
ques
c_cond
l_int|15
suffix:colon
l_int|14
suffix:semicolon
)brace
macro_line|#endif /* HAVE_ARCH_PCI_GET_LEGACY_IDE_IRQ */
macro_line|#endif
eof
