multiline_comment|/* linux/arch/arm/mach-s3c2410/mach-ipaq.c&n; *&n; * Copyright (c) 2003 Simtec Electronics&n; *   Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * http://www.handhelds.org/projects/h1940.html&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *     16-May-2003 BJD  Created initial version&n; *     16-Aug-2003 BJD  Fixed header files and copyright, added URL&n; *     05-Sep-2003 BJD  Moved to v2.6 kernel&n; *     06-Jan-2003 BJD  Updates for &lt;arch/map.h&gt;&n; *     18-Jan-2003 BJD  Added serial port configuration&n; *     17-Feb-2003 BJD  Copied to mach-ipaq.c&n;*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/hardware/iomd.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
singleline_comment|//#include &lt;asm/debug-ll.h&gt;
macro_line|#include &lt;asm/arch/regs-serial.h&gt;
macro_line|#include &quot;s3c2410.h&quot;
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|ipaq_iodesc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* nothing here yet */
)brace
suffix:semicolon
DECL|macro|UCON
mdefine_line|#define UCON S3C2410_UCON_DEFAULT | S3C2410_UCON_UCLK
DECL|macro|ULCON
mdefine_line|#define ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
DECL|macro|UFCON
mdefine_line|#define UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE
DECL|variable|ipaq_uartcfgs
r_static
r_struct
id|s3c2410_uartcfg
id|ipaq_uartcfgs
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
(brace
dot
id|hwport
op_assign
l_int|0
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|clock
op_assign
op_amp
id|s3c2410_hclk
comma
dot
id|ucon
op_assign
l_int|0x3c5
comma
dot
id|ulcon
op_assign
l_int|0x03
comma
dot
id|ufcon
op_assign
l_int|0x51
comma
)brace
comma
(braket
l_int|1
)braket
op_assign
(brace
dot
id|hwport
op_assign
l_int|1
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|clock
op_assign
op_amp
id|s3c2410_hclk
comma
dot
id|ucon
op_assign
l_int|0x245
comma
dot
id|ulcon
op_assign
l_int|0x03
comma
dot
id|ufcon
op_assign
l_int|0x00
comma
)brace
comma
multiline_comment|/* IR port */
(braket
l_int|2
)braket
op_assign
(brace
dot
id|hwport
op_assign
l_int|2
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|clock
op_assign
op_amp
id|s3c2410_hclk
comma
dot
id|ucon
op_assign
l_int|0x3c5
comma
dot
id|ulcon
op_assign
l_int|0x43
comma
dot
id|ufcon
op_assign
l_int|0x51
comma
)brace
)brace
suffix:semicolon
DECL|function|ipaq_map_io
r_void
id|__init
id|ipaq_map_io
c_func
(paren
r_void
)paren
(brace
id|s3c2410_map_io
c_func
(paren
id|ipaq_iodesc
comma
id|ARRAY_SIZE
c_func
(paren
id|ipaq_iodesc
)paren
)paren
suffix:semicolon
id|s3c2410_uartcfgs
op_assign
id|ipaq_uartcfgs
suffix:semicolon
)brace
DECL|function|ipaq_init_irq
r_void
id|__init
id|ipaq_init_irq
c_func
(paren
r_void
)paren
(brace
singleline_comment|//llprintk(&quot;ipaq_init_irq:&bslash;n&quot;);
id|s3c2410_init_irq
c_func
(paren
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|H1940
comma
l_string|&quot;IPAQ-H1940&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Ben Dooks &lt;ben@fluff.org&gt;&quot;
)paren
id|BOOT_MEM
c_func
(paren
id|S3C2410_SDRAM_PA
comma
id|S3C2410_PA_UART
comma
id|S3C2410_VA_UART
)paren
id|BOOT_PARAMS
c_func
(paren
id|S3C2410_SDRAM_PA
op_plus
l_int|0x100
)paren
id|MAPIO
c_func
(paren
id|ipaq_map_io
)paren
id|INITIRQ
c_func
(paren
id|ipaq_init_irq
)paren
id|MACHINE_END
eof
