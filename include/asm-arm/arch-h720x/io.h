multiline_comment|/*&n; * linux/include/asm-arm/arch-h720x/io.h&n; *&n; * Copyright (C) 2000 Steve Hill (sjhill@cotw.com)&n; *&n; * Changelog:&n; *&n; *  09-19-2001&t;JJKIM&n; *  &t;&t;Created from linux/include/asm-arm/arch-l7200/io.h&n; *&n; *  03-27-2003  Robert Schwebel &lt;r.schwebel@pengutronix.de&gt;:&n; *  &t;&t;re-unified header files for h720x&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
macro_line|#include &lt;asm/arch/hardware.h&gt;
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
DECL|macro|__io
mdefine_line|#define __io(a)&t;&t;((void __iomem *)(a))
DECL|macro|__mem_pci
mdefine_line|#define __mem_pci(a)&t;(a)
macro_line|#endif
eof
