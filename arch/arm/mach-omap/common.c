multiline_comment|/*&n; * linux/arch/arm/mach-omap/common.c&n; *&n; * Code common to all OMAP machines.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/arch/clocks.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;common.h&quot;
multiline_comment|/*&n; * Common OMAP I/O mapping&n; *&n; * The machine specific code may provide the extra mapping besides the&n; * default mapping provided here.&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|standard_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|IO_BASE
comma
id|IO_START
comma
id|IO_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|OMAP_DSP_BASE
comma
id|OMAP_DSP_START
comma
id|OMAP_DSP_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|OMAP_DSPREG_BASE
comma
id|OMAP_DSPREG_START
comma
id|OMAP_DSPREG_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|OMAP_SRAM_BASE
comma
id|OMAP_SRAM_START
comma
id|OMAP_SRAM_SIZE
comma
id|MT_DEVICE
)brace
)brace
suffix:semicolon
DECL|variable|initialized
r_static
r_int
id|initialized
op_assign
l_int|0
suffix:semicolon
DECL|function|_omap_map_io
r_static
r_void
id|__init
id|_omap_map_io
c_func
(paren
r_void
)paren
(brace
id|initialized
op_assign
l_int|1
suffix:semicolon
id|iotable_init
c_func
(paren
id|standard_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|standard_io_desc
)paren
)paren
suffix:semicolon
multiline_comment|/* REVISIT: Refer to OMAP5910 Errata, Advisory SYS_1: &quot;Timeout Abort&n;&t; * on a Posted Write in the TIPB Bridge&quot;.&n;&t; */
id|__raw_writew
c_func
(paren
l_int|0x0
comma
id|MPU_PUBLIC_TIPB_CNTL_REG
)paren
suffix:semicolon
id|__raw_writew
c_func
(paren
l_int|0x0
comma
id|MPU_PRIVATE_TIPB_CNTL_REG
)paren
suffix:semicolon
multiline_comment|/* Must init clocks early to assure that timer interrupt works&n;&t; */
id|init_ck
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This should only get called from board specific init&n; */
DECL|function|omap_map_io
r_void
id|omap_map_io
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|initialized
)paren
id|_omap_map_io
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|omap_map_io
id|EXPORT_SYMBOL
c_func
(paren
id|omap_map_io
)paren
suffix:semicolon
eof
