multiline_comment|/*&n; *  linux/include/asm-arm/memory.h&n; *&n; *  Copyright (C) 2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Note: this file should not be included by non-asm/.h files&n; *&n; *  Modifications:&n; */
macro_line|#ifndef __ASM_ARM_MEMORY_H
DECL|macro|__ASM_ARM_MEMORY_H
mdefine_line|#define __ASM_ARM_MEMORY_H
macro_line|#include &lt;asm/arch/memory.h&gt;
DECL|function|virt_to_phys
r_static
r_inline
r_int
r_int
id|virt_to_phys
c_func
(paren
r_volatile
r_void
op_star
id|x
)paren
(brace
r_return
id|__virt_to_phys
c_func
(paren
(paren
r_int
r_int
)paren
(paren
id|x
)paren
)paren
suffix:semicolon
)brace
DECL|function|phys_to_virt
r_static
r_inline
r_void
op_star
id|phys_to_virt
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|__phys_to_virt
c_func
(paren
(paren
r_int
r_int
)paren
(paren
id|x
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Virtual &lt;-&gt; DMA view memory address translations&n; */
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus(x)&t;&t;(__virt_to_bus((unsigned long)(x)))
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt(x)&t;&t;((void *)(__bus_to_virt((unsigned long)(x))))
macro_line|#endif
eof
