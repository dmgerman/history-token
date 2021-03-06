macro_line|#ifndef _ASM_M68K_PCI_H
DECL|macro|_ASM_M68K_PCI_H
mdefine_line|#define _ASM_M68K_PCI_H
multiline_comment|/*&n; * asm-m68k/pci_m68k.h - m68k specific PCI declarations.&n; *&n; * Written by Wout Klaren.&n; */
macro_line|#include &lt;asm/scatterlist.h&gt;
r_struct
id|pci_ops
suffix:semicolon
multiline_comment|/*&n; * Structure with hardware dependent information and functions of the&n; * PCI bus.&n; */
DECL|struct|pci_bus_info
r_struct
id|pci_bus_info
(brace
multiline_comment|/*&n;&t; * Resources of the PCI bus.&n;&t; */
DECL|member|mem_space
r_struct
id|resource
id|mem_space
suffix:semicolon
DECL|member|io_space
r_struct
id|resource
id|io_space
suffix:semicolon
multiline_comment|/*&n;&t; * System dependent functions.&n;&t; */
DECL|member|m68k_pci_ops
r_struct
id|pci_ops
op_star
id|m68k_pci_ops
suffix:semicolon
DECL|member|fixup
r_void
(paren
op_star
id|fixup
)paren
(paren
r_int
id|pci_modify
)paren
suffix:semicolon
DECL|member|conf_device
r_void
(paren
op_star
id|conf_device
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()&t;0
DECL|macro|pcibios_scan_all_fns
mdefine_line|#define pcibios_scan_all_fns(a, b)&t;0
DECL|function|pcibios_set_master
r_static
r_inline
r_void
id|pcibios_set_master
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
multiline_comment|/* No special bus mastering setup handling */
)brace
DECL|function|pcibios_penalize_isa_irq
r_static
r_inline
r_void
id|pcibios_penalize_isa_irq
c_func
(paren
r_int
id|irq
)paren
(brace
multiline_comment|/* We don&squot;t do dynamic PCI IRQ allocation */
)brace
multiline_comment|/* The PCI address space does equal the physical memory&n; * address space.  The networking and block device layers use&n; * this boolean for bounce buffer decisions.&n; */
DECL|macro|PCI_DMA_BUS_IS_PHYS
mdefine_line|#define PCI_DMA_BUS_IS_PHYS&t;(1)
DECL|function|pcibios_add_platform_entries
r_static
r_inline
r_void
id|pcibios_add_platform_entries
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
)brace
macro_line|#endif /* _ASM_M68K_PCI_H */
eof
