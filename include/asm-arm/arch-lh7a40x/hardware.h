multiline_comment|/* include/asm-arm/arch-lh7a40x/hardware.h&n; *&n; *  Copyright (C) 2004 Coastal Environmental Systems&n; *&n; *  [ Substantially cribbed from include/asm-arm/arch-pxa/hardware.h ]&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  version 2 as published by the Free Software Foundation.&n; *&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
DECL|macro|io_p2v
mdefine_line|#define io_p2v(x) (0xf0000000 | (((x) &amp; 0xfff00000) &gt;&gt; 4) | ((x) &amp; 0x0000ffff))
DECL|macro|io_v2p
mdefine_line|#define io_v2p(x) (             (((x) &amp; 0x0fff0000) &lt;&lt; 4) | ((x) &amp; 0x0000ffff))
macro_line|#ifdef __ASSEMBLY__
DECL|macro|__REG
macro_line|# define __REG(x)&t;io_p2v(x)
DECL|macro|__PREG
macro_line|# define __PREG(x)&t;io_v2p(x)
macro_line|#else
macro_line|# if 0
macro_line|#  define __REG(x)&t;(*((volatile u32 *)io_p2v(x)))
macro_line|# else
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
DECL|member|offset
DECL|typedef|__regbase16
r_typedef
r_struct
(brace
r_volatile
id|u16
id|offset
(braket
l_int|4096
)braket
suffix:semicolon
)brace
id|__regbase16
suffix:semicolon
DECL|macro|__REGP16
macro_line|# define __REGP16(x)&t;((__regbase16 *)((x)&amp;~4095))-&gt;offset[((x)&amp;4095)&gt;&gt;2]
DECL|macro|__REG16
macro_line|# define __REG16(x)&t;__REGP16(io_p2v(x))
DECL|member|offset
DECL|typedef|__regbase8
r_typedef
r_struct
(brace
r_volatile
id|u8
id|offset
(braket
l_int|4096
)braket
suffix:semicolon
)brace
id|__regbase8
suffix:semicolon
DECL|macro|__REGP8
macro_line|# define __REGP8(x)&t;((__regbase8 *)((x)&amp;~4095))-&gt;offset[((x)&amp;4095)&gt;&gt;2]
DECL|macro|__REG8
macro_line|# define __REG8(x)&t;__REGP8(io_p2v(x))
macro_line|#endif
multiline_comment|/* Let&squot;s kick gcc&squot;s ass again... */
DECL|macro|__REG2
macro_line|# define __REG2(x,y)&t;&bslash;&n;&t;( __builtin_constant_p(y) ? (__REG((x) + (y))) &bslash;&n;&t;&t;&t;&t;  : (*(volatile u32 *)((u32)&amp;__REG(x) + (y))) )
DECL|macro|__PREG
macro_line|# define __PREG(x)&t;(io_v2p((u32)&amp;(x)))
macro_line|#endif
macro_line|#include &quot;registers.h&quot;
macro_line|#endif  /* _ASM_ARCH_HARDWARE_H */
eof
