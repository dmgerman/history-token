multiline_comment|/*&n; * linux/arch/arm/mach-iop310/mm.c&n; *&n; * Low level memory intialization for IOP310 based systems&n; *&n; * Author: Nicolas Pitre &lt;npitre@mvista.com&gt;&n; *&n; * Copyright 2000-2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#ifdef CONFIG_IOP310_MU
macro_line|#include &quot;message.h&quot;
macro_line|#endif
multiline_comment|/*&n; * Standard IO mapping for all IOP310 based systems&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|iop80310_std_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical      length       type */
singleline_comment|// IOP310 Memory Mapped Registers
(brace
l_int|0xe8001000
comma
l_int|0x00001000
comma
l_int|0x00001000
comma
id|MT_DEVICE
)brace
comma
singleline_comment|// PCI I/O Space
(brace
l_int|0xfe000000
comma
l_int|0x90000000
comma
l_int|0x00020000
comma
id|MT_DEVICE
)brace
)brace
suffix:semicolon
DECL|function|iop310_map_io
r_void
id|__init
id|iop310_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|iop80310_std_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|iop80310_std_desc
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * IQ80310 specific IO mappings&n; */
macro_line|#ifdef CONFIG_ARCH_IQ80310
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|iq80310_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical      length        type */
singleline_comment|// IQ80310 On-Board Devices
(brace
l_int|0xfe800000
comma
l_int|0xfe800000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
)brace
suffix:semicolon
DECL|function|iq80310_map_io
r_void
id|__init
id|iq80310_map_io
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_IOP310_MU
multiline_comment|/* acquiring 1MB of memory aligned on 1MB boundary for MU */
id|mu_mem
op_assign
id|__alloc_bootmem
c_func
(paren
l_int|0x100000
comma
l_int|0x100000
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|iop310_map_io
c_func
(paren
)paren
suffix:semicolon
id|iotable_init
c_func
(paren
id|iq80310_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|iq80310_io_desc
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif 
singleline_comment|// CONFIG_ARCH_IQ80310
eof
