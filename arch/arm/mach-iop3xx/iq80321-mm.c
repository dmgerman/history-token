multiline_comment|/*&n; * linux/arch/arm/mach-iop3xx/mm.c&n; *&n; * Low level memory initialization for iq80321 platform&n; *&n; * Author: Rory Bolt &lt;rorybolt@pacbell.net&gt;&n; * Copyright (C) 2002 Rory Bolt&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
multiline_comment|/*&n; * IQ80321 specific IO mappings&n; *&n; * We use RedBoot&squot;s setup for the onboard devices.&n; */
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
id|IQ80321_UART
comma
id|IQ80321_UART
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
eof
