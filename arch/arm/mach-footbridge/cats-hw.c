multiline_comment|/*&n; * linux/arch/arm/mach-footbridge/cats-hw.c&n; *&n; * CATS machine fixup&n; *&n; * Copyright (C) 1998, 1999 Russell King, Phil Blundell&n; */
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
DECL|macro|CFG_PORT
mdefine_line|#define CFG_PORT&t;0x370
DECL|macro|INDEX_PORT
mdefine_line|#define INDEX_PORT&t;(CFG_PORT)
DECL|macro|DATA_PORT
mdefine_line|#define DATA_PORT&t;(CFG_PORT + 1)
DECL|function|cats_hw_init
r_static
r_int
id|__init
id|cats_hw_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_cats
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* Set Aladdin to CONFIGURE mode */
id|outb
c_func
(paren
l_int|0x51
comma
id|CFG_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x23
comma
id|CFG_PORT
)paren
suffix:semicolon
multiline_comment|/* Select logical device 3 */
id|outb
c_func
(paren
l_int|0x07
comma
id|INDEX_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x03
comma
id|DATA_PORT
)paren
suffix:semicolon
multiline_comment|/* Set parallel port to DMA channel 3, ECP+EPP1.9, &n;&t;&t;   enable EPP timeout */
id|outb
c_func
(paren
l_int|0x74
comma
id|INDEX_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x03
comma
id|DATA_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xf0
comma
id|INDEX_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x0f
comma
id|DATA_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xf1
comma
id|INDEX_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x07
comma
id|DATA_PORT
)paren
suffix:semicolon
multiline_comment|/* Select logical device 4 */
id|outb
c_func
(paren
l_int|0x07
comma
id|INDEX_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x04
comma
id|DATA_PORT
)paren
suffix:semicolon
multiline_comment|/* UART1 high speed mode */
id|outb
c_func
(paren
l_int|0xf0
comma
id|INDEX_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x02
comma
id|DATA_PORT
)paren
suffix:semicolon
multiline_comment|/* Select logical device 5 */
id|outb
c_func
(paren
l_int|0x07
comma
id|INDEX_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x05
comma
id|DATA_PORT
)paren
suffix:semicolon
multiline_comment|/* UART2 high speed mode */
id|outb
c_func
(paren
l_int|0xf0
comma
id|INDEX_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x02
comma
id|DATA_PORT
)paren
suffix:semicolon
multiline_comment|/* Set Aladdin to RUN mode */
id|outb
c_func
(paren
l_int|0xbb
comma
id|CFG_PORT
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cats_hw_init
id|__initcall
c_func
(paren
id|cats_hw_init
)paren
suffix:semicolon
eof
