multiline_comment|/*&n; * linux/arch/arm/mach-iop3xx/mm.c&n; *&n; * Low level memory initialization for IOP321 based systems&n; *&n; * Author: Rory Bolt &lt;rorybolt@pacbell.net&gt;&n; * Copyright (C) 2002 Rory Bolt&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
multiline_comment|/*&n; * Standard IO mapping for all IOP321 based systems&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|iop80321_std_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical      length      type */
multiline_comment|/* mem mapped registers */
(brace
id|IOP321_VIRT_MEM_BASE
comma
id|IOP321_PHY_MEM_BASE
comma
l_int|0x00002000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* PCI IO space */
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
DECL|function|iop321_map_io
r_void
id|__init
id|iop321_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|iop80321_std_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|iop80321_std_desc
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * IQ80321 specific IO mappings&n; *&n; * We use RedBoot&squot;s setup for the onboard devices.&n; */
macro_line|#ifdef CONFIG_ARCH_IQ80321
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|iq80321_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical      length        type */
multiline_comment|/* on-board devices */
(brace
l_int|0xfe800000
comma
id|IQ80321_UART1
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
)brace
suffix:semicolon
DECL|function|iq80321_map_io
r_void
id|__init
id|iq80321_map_io
c_func
(paren
r_void
)paren
(brace
id|iop321_map_io
c_func
(paren
)paren
suffix:semicolon
id|iotable_init
c_func
(paren
id|iq80321_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|iq80321_io_desc
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif 
singleline_comment|// CONFIG_ARCH_IQ80321
eof
