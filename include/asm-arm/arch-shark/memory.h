multiline_comment|/*&n; * linux/include/asm-arm/arch-shark/memory.h&n; *&n; * by Alexander Schulz&n; *&n; * derived from:&n; * linux/include/asm-arm/arch-ebsa110/memory.h&n; * Copyright (c) 1996-1999 Russell King.&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
macro_line|#include &lt;asm/sizes.h&gt;
multiline_comment|/*&n; * Physical DRAM offset.&n; */
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET     (0x08000000UL)
macro_line|#ifndef __ASSEMBLY__
DECL|function|__arch_adjust_zones
r_static
r_inline
r_void
id|__arch_adjust_zones
c_func
(paren
r_int
id|node
comma
r_int
r_int
op_star
id|zone_size
comma
r_int
r_int
op_star
id|zhole_size
)paren
(brace
r_if
c_cond
(paren
id|node
op_ne
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/* Only the first 4 MB (=1024 Pages) are usable for DMA */
id|zone_size
(braket
l_int|1
)braket
op_assign
id|zone_size
(braket
l_int|0
)braket
op_minus
l_int|1024
suffix:semicolon
id|zone_size
(braket
l_int|0
)braket
op_assign
l_int|1024
suffix:semicolon
id|zhole_size
(braket
l_int|1
)braket
op_assign
id|zhole_size
(braket
l_int|0
)braket
suffix:semicolon
id|zhole_size
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
)brace
DECL|macro|arch_adjust_zones
mdefine_line|#define arch_adjust_zones(node, size, holes) &bslash;&n;&t;__arch_adjust_zones(node, size, holes)
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD&t;(PHYS_OFFSET + SZ_4M - 1)
macro_line|#endif
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t;__virt_to_phys(x)
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)&t;__phys_to_virt(x)
macro_line|#endif
eof
