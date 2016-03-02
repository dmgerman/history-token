multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/io.h&n; *&n; * Copyright (C) 1997-1999 Russell King&n; *&n; * Modifications:&n; *  06-12-1997&t;RMK&t;Created.&n; *  07-04-1999&t;RMK&t;Major cleanup&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
multiline_comment|/*&n; * We don&squot;t actually have real ISA nor PCI buses, but there is so many &n; * drivers out there that might just work if we fake them...&n; */
DECL|macro|__io
mdefine_line|#define __io(a)&t;&t;&t;((void __iomem *)(PCIO_BASE + (a)))
DECL|macro|__mem_pci
mdefine_line|#define __mem_pci(a)&t;&t;(a)
DECL|macro|__mem_isa
mdefine_line|#define __mem_isa(a)&t;&t;(a)
macro_line|#endif
eof
