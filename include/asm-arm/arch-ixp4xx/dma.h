multiline_comment|/*&n; * include/asm-arm/arch-ixp4xx/dma.h&n; *&n; * Copyright (C) 2001-2004 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#ifndef __ASM_ARCH_DMA_H
DECL|macro|__ASM_ARCH_DMA_H
mdefine_line|#define __ASM_ARCH_DMA_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/sizes.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;(PAGE_OFFSET + SZ_64M)
multiline_comment|/* No DMA */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;0
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
macro_line|#endif /* _ASM_ARCH_DMA_H */
eof
