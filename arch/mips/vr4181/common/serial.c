multiline_comment|/*&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; *&n; * arch/mips/vr4181/common/serial.c&n; *     initialize serial port on vr4181.&n; *&n; * This program is free software; you can redistribute&t;it and/or modify it&n; * under  the terms of&t;the GNU General&t; Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
multiline_comment|/*&n; * [jsun, 010925]&n; * You need to make sure rs_table has at least one element in&n; * drivers/char/serial.c file.&t;There is no good way to do it right&n; * now.&t; A workaround is to include CONFIG_SERIAL_MANY_PORTS in your&n; * configure file, which would gives you 64 ports and wastes 11K ram.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;asm/vr4181/vr4181.h&gt;
DECL|function|vr4181_init_serial
r_void
id|__init
id|vr4181_init_serial
c_func
(paren
r_void
)paren
(brace
r_struct
id|serial_struct
id|s
suffix:semicolon
multiline_comment|/* turn on UART clock */
op_star
id|VR4181_CMUCLKMSK
op_or_assign
id|VR4181_CMUCLKMSK_MSKSIU
suffix:semicolon
multiline_comment|/* clear memory */
id|memset
c_func
(paren
op_amp
id|s
comma
l_int|0
comma
r_sizeof
(paren
id|s
)paren
)paren
suffix:semicolon
id|s.line
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* we set the first one */
id|s.baud_base
op_assign
l_int|1152000
suffix:semicolon
id|s.irq
op_assign
id|VR4181_IRQ_SIU
suffix:semicolon
id|s.flags
op_assign
id|ASYNC_BOOT_AUTOCONF
op_or
id|ASYNC_SKIP_TEST
suffix:semicolon
multiline_comment|/* STD_COM_FLAGS */
id|s.iomem_base
op_assign
(paren
id|u8
op_star
)paren
id|VR4181_SIURB
suffix:semicolon
id|s.iomem_reg_shift
op_assign
l_int|0
suffix:semicolon
id|s.io_type
op_assign
id|SERIAL_IO_MEM
suffix:semicolon
r_if
c_cond
(paren
id|early_serial_setup
c_func
(paren
op_amp
id|s
)paren
op_ne
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;vr4181_init_serial() failed!&quot;
)paren
suffix:semicolon
)brace
)brace
eof
