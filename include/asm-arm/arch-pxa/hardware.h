multiline_comment|/*&n; *  linux/include/asm-arm/arch-pxa/hardware.h&n; *&n; *  Author:&t;Nicolas Pitre&n; *  Created:&t;Jun 15, 2001&n; *  Copyright:&t;MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
multiline_comment|/*&n; * These are statically mapped PCMCIA IO space for designs using it as a&n; * generic IO bus, typically with ISA parts, hardwired IDE interfaces, etc.&n; * The actual PCMCIA code is mapping required IO region at run time.&n; */
DECL|macro|PCMCIA_IO_0_BASE
mdefine_line|#define PCMCIA_IO_0_BASE&t;0xf6000000
DECL|macro|PCMCIA_IO_1_BASE
mdefine_line|#define PCMCIA_IO_1_BASE&t;0xf7000000
multiline_comment|/*&n; * We requires absolute addresses.&n; */
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0
multiline_comment|/*&n; * Workarounds for at least 2 errata so far require this.&n; * The mapping is set in mach-pxa/generic.c.&n; */
DECL|macro|UNCACHED_PHYS_0
mdefine_line|#define UNCACHED_PHYS_0&t;&t;0xff000000
DECL|macro|UNCACHED_ADDR
mdefine_line|#define UNCACHED_ADDR&t;&t;UNCACHED_PHYS_0
multiline_comment|/*&n; * Intel PXA internal I/O mappings:&n; *&n; * 0x40000000 - 0x41ffffff &lt;--&gt; 0xf8000000 - 0xf9ffffff&n; * 0x44000000 - 0x45ffffff &lt;--&gt; 0xfa000000 - 0xfbffffff&n; * 0x48000000 - 0x49ffffff &lt;--&gt; 0xfc000000 - 0xfdffffff&n; */
DECL|macro|io_p2v
mdefine_line|#define io_p2v(x)&t;( ((x) | 0xbe000000) ^ (~((x) &gt;&gt; 1) &amp; 0x06000000) )
DECL|macro|io_v2p
mdefine_line|#define io_v2p( x )&t;( ((x) &amp; 0x41ffffff) ^ ( ((x) &amp; 0x06000000) &lt;&lt; 1) )
macro_line|#ifndef __ASSEMBLY__
macro_line|#if 0
macro_line|# define __REG(x)&t;(*((volatile u32 *)io_p2v(x)))
macro_line|#else
multiline_comment|/*&n; * This __REG() version gives the same results as the one above,  except&n; * that we are fooling gcc somehow so it generates far better and smaller&n; * assembly code for access to contigous registers.  It&squot;s a shame that gcc&n; * doesn&squot;t guess this by itself.&n; */
macro_line|#include &lt;asm/types.h&gt;
DECL|member|offset
DECL|typedef|__regbase
r_typedef
r_struct
(brace
r_volatile
id|u32
id|offset
(braket
l_int|4096
)braket
suffix:semicolon
)brace
id|__regbase
suffix:semicolon
DECL|macro|__REGP
macro_line|# define __REGP(x)&t;((__regbase *)((x)&amp;~4095))-&gt;offset[((x)&amp;4095)&gt;&gt;2]
DECL|macro|__REG
macro_line|# define __REG(x)&t;__REGP(io_p2v(x))
macro_line|#endif
multiline_comment|/* Let&squot;s kick gcc&squot;s ass again... */
DECL|macro|__REG2
macro_line|# define __REG2(x,y)&t;&bslash;&n;&t;( __builtin_constant_p(y) ? (__REG((x) + (y))) &bslash;&n;&t;&t;&t;&t;  : (*(volatile u32 *)((u32)&amp;__REG(x) + (y))) )
DECL|macro|__PREG
macro_line|# define __PREG(x)&t;(io_v2p((u32)&amp;(x)))
macro_line|#else
DECL|macro|__REG
macro_line|# define __REG(x)&t;io_p2v(x)
DECL|macro|__PREG
macro_line|# define __PREG(x)&t;io_v2p(x)
macro_line|#endif
macro_line|#include &quot;pxa-regs.h&quot;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Handy routine to set GPIO alternate functions&n; */
r_extern
r_void
id|pxa_gpio_mode
c_func
(paren
r_int
id|gpio_mode
)paren
suffix:semicolon
multiline_comment|/*&n; * return current lclk frequency in units of 10kHz&n; */
r_extern
r_int
r_int
id|get_lclk_frequency_10khz
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Implementation specifics&n; */
macro_line|#include &quot;lubbock.h&quot;
macro_line|#include &quot;idp.h&quot;
macro_line|#endif  /* _ASM_ARCH_HARDWARE_H */
eof
