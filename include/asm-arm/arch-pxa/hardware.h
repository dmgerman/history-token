multiline_comment|/*&n; *  linux/include/asm-arm/arch-pxa/hardware.h&n; *&n; *  Author:&t;Nicolas Pitre&n; *  Created:&t;Jun 15, 2001&n; *  Copyright:&t;MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
multiline_comment|/*&n; * We requires absolute addresses.&n; */
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0
multiline_comment|/*&n; * Workarounds for at least 2 errata so far require this.&n; * The mapping is set in mach-pxa/generic.c.&n; */
DECL|macro|UNCACHED_PHYS_0
mdefine_line|#define UNCACHED_PHYS_0&t;&t;0xff000000
DECL|macro|UNCACHED_ADDR
mdefine_line|#define UNCACHED_ADDR&t;&t;UNCACHED_PHYS_0
multiline_comment|/*&n; * Intel PXA2xx internal register mapping:&n; *&n; * 0x40000000 - 0x41ffffff &lt;--&gt; 0xf2000000 - 0xf3ffffff&n; * 0x44000000 - 0x45ffffff &lt;--&gt; 0xf4000000 - 0xf5ffffff&n; * 0x48000000 - 0x49ffffff &lt;--&gt; 0xf6000000 - 0xf7ffffff&n; * 0x4c000000 - 0x4dffffff &lt;--&gt; 0xf8000000 - 0xf9ffffff&n; * 0x50000000 - 0x51ffffff &lt;--&gt; 0xfa000000 - 0xfbffffff&n; * 0x54000000 - 0x55ffffff &lt;--&gt; 0xfc000000 - 0xfdffffff&n; * 0x58000000 - 0x59ffffff &lt;--&gt; 0xfe000000 - 0xffffffff&n; *&n; * Note that not all PXA2xx chips implement all those addresses, and the&n; * kernel only maps the minimum needed range of this mapping.&n; */
DECL|macro|io_p2v
mdefine_line|#define io_p2v(x) (0xf2000000 + ((x) &amp; 0x01ffffff) + (((x) &amp; 0x1c000000) &gt;&gt; 1))
DECL|macro|io_v2p
mdefine_line|#define io_v2p(x) (0x3c000000 + ((x) &amp; 0x01ffffff) + (((x) &amp; 0x0e000000) &lt;&lt; 1))
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
multiline_comment|/* With indexed regs we don&squot;t want to feed the index through io_p2v()&n;   especially if it is a variable, otherwise horrible code will result. */
DECL|macro|__REG2
macro_line|# define __REG2(x,y)     (*(volatile u32 *)((u32)&amp;__REG(x) + (y)))
DECL|macro|__PREG
macro_line|# define __PREG(x)&t;(io_v2p((u32)&amp;(x)))
macro_line|#else
DECL|macro|__REG
macro_line|# define __REG(x)&t;io_p2v(x)
DECL|macro|__PREG
macro_line|# define __PREG(x)&t;io_v2p(x)
macro_line|#endif
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
multiline_comment|/*&n; * Routine to enable or disable CKEN&n; */
r_extern
r_void
id|pxa_set_cken
c_func
(paren
r_int
id|clock
comma
r_int
id|enable
)paren
suffix:semicolon
multiline_comment|/*&n; * return current memory and LCD clock frequency in units of 10kHz&n; */
r_extern
r_int
r_int
id|get_memclk_frequency_10khz
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_lcdclk_frequency_10khz
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif  /* _ASM_ARCH_HARDWARE_H */
eof
