multiline_comment|/*&n; * serial.h&n; *&n; * Copyright (C) 2003 Develer S.r.l. (http://www.develer.com/)&n; * Author: Bernardo Innocenti &lt;bernie@codewiz.org&gt;&n; *&n; * Based on linux/include/asm-i386/serial.h&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/serial-regs.h&gt;
multiline_comment|/*&n; * the base baud is derived from the clock speed and so is variable&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD 0
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS&t;&t;ASYNC_BOOT_AUTOCONF
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS
eof
