multiline_comment|/*&n; * linux/include/asm-arm/arch-ixp4xx/memory.h&n; *&n; * Copyright (c) 2001-2004 MontaVista Software, Inc.&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
macro_line|#include &lt;asm/sizes.h&gt;
multiline_comment|/*&n; * Physical DRAM offset.&n; */
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;(0x00000000UL)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Only first 64MB of memory can be accessed via PCI.&n; * We use GFP_DMA to allocate safe buffers to do map/unmap.&n; * This is really ugly and we need a better way of specifying&n; * DMA-capable regions of memory.&n; */
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
r_int
r_int
id|sz
op_assign
id|SZ_64M
op_rshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/*&n;&t; * Only adjust if &gt; 64M on current system&n;&t; */
r_if
c_cond
(paren
id|node
op_logical_or
(paren
id|zone_size
(braket
l_int|0
)braket
op_le
id|sz
)paren
)paren
r_return
suffix:semicolon
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
id|sz
suffix:semicolon
id|zone_size
(braket
l_int|0
)braket
op_assign
id|sz
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
mdefine_line|#define ISA_DMA_THRESHOLD (SZ_64M - 1)
macro_line|#endif
multiline_comment|/*&n; * Virtual view &lt;-&gt; DMA view memory address translations&n; * virt_to_bus: Used to translate the virtual address to an&n; *&t;&t;address suitable to be passed to set_dma_addr&n; * bus_to_virt: Used to convert an address for DMA operations&n; *&t;&t;to an address that the kernel can use.&n; *&n; * These are dummies for now.&n; */
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t; __virt_to_phys(x)
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)&t; __phys_to_virt(x)
macro_line|#endif
eof
