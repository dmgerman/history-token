macro_line|#ifndef _ASM_H8300_PCI_H
DECL|macro|_ASM_H8300_PCI_H
mdefine_line|#define _ASM_H8300_PCI_H
multiline_comment|/*&n; * asm-h8300/pci.h - H8/300 specific PCI declarations.&n; *&n; * Yoshinori Sato &lt;ysato@users.sourceforge.jp&gt;&n; */
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()&t;0
DECL|function|pcibios_set_master
r_extern
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
r_extern
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
macro_line|#endif /* _ASM_H8300_PCI_H */
eof
