macro_line|#ifndef __ASM_S390_PCI_H
DECL|macro|__ASM_S390_PCI_H
mdefine_line|#define __ASM_S390_PCI_H
multiline_comment|/* S/390 systems don&squot;t have a PCI bus. This file is just here because some stupid .c code&n; * includes it even if CONFIG_PCI is not set.&n; */
DECL|macro|PCI_DMA_BUS_IS_PHYS
mdefine_line|#define PCI_DMA_BUS_IS_PHYS (1)
macro_line|#endif /* __ASM_S390_PCI_H */
eof
