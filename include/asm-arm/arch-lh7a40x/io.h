multiline_comment|/* include/asm-arm/arch-lh7a40x/io.h&n; *&n; *  Copyright (C) 2004 Coastal Environmental Systems&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  version 2 as published by the Free Software Foundation.&n; *&n; */
macro_line|#ifndef __ASM_ARCH_IO_H
DECL|macro|__ASM_ARCH_IO_H
mdefine_line|#define __ASM_ARCH_IO_H
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
multiline_comment|/* No ISA or PCI bus on this machine. */
DECL|macro|__io
mdefine_line|#define __io(a)&t;&t;&t;((void __iomem *)(a))
DECL|macro|__mem_pci
mdefine_line|#define __mem_pci(a)&t;&t;(a)
DECL|macro|__mem_isa
mdefine_line|#define __mem_isa(a)&t;&t;(a)
macro_line|#endif /* __ASM_ARCH_IO_H */
eof
