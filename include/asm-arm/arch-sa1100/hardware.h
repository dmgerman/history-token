multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/hardware.h&n; *&n; * Copyright (C) 1998 Nicolas Pitre &lt;nico@cam.org&gt;&n; *&n; * This file contains the hardware definitions for SA1100 architecture&n; *&n; * 2000/05/23 John Dorsey &lt;john+@cs.cmu.edu&gt;&n; *      Definitions for SA1111 added.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Flushing areas */
DECL|macro|FLUSH_BASE_PHYS
mdefine_line|#define FLUSH_BASE_PHYS&t;&t;0xe0000000&t;/* SA1100 zero bank */
DECL|macro|FLUSH_BASE
mdefine_line|#define FLUSH_BASE&t;&t;0xf5000000
DECL|macro|FLUSH_BASE_MINICACHE
mdefine_line|#define FLUSH_BASE_MINICACHE&t;0xf5800000
DECL|macro|UNCACHEABLE_ADDR
mdefine_line|#define UNCACHEABLE_ADDR&t;0xfa050000
multiline_comment|/*&n; * We requires absolute addresses i.e. (PCMCIA_IO_0_BASE + 0x3f8) for &n; * in*()/out*() macros to be usable for all cases.&n; */
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0
multiline_comment|/*&n; * SA1100 internal I/O mappings&n; *&n; * We have the following mapping:&n; *      phys            virt&n; *      80000000        f8000000&n; *      90000000        fa000000&n; *      a0000000        fc000000&n; *      b0000000        fe000000&n; */
DECL|macro|VIO_BASE
mdefine_line|#define VIO_BASE        0xf8000000&t;/* virtual start of IO space */
DECL|macro|VIO_SHIFT
mdefine_line|#define VIO_SHIFT       3&t;&t;/* x = IO space shrink power */
DECL|macro|PIO_START
mdefine_line|#define PIO_START       0x80000000&t;/* physical start of IO space */
DECL|macro|io_p2v
mdefine_line|#define io_p2v( x )             &bslash;&n;   ( (((x)&amp;0x00ffffff) | (((x)&amp;0x30000000)&gt;&gt;VIO_SHIFT)) + VIO_BASE )
DECL|macro|io_v2p
mdefine_line|#define io_v2p( x )             &bslash;&n;   ( (((x)&amp;0x00ffffff) | (((x)&amp;(0x30000000&gt;&gt;VIO_SHIFT))&lt;&lt;VIO_SHIFT)) + PIO_START )
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/types.h&gt;
macro_line|#if 0
macro_line|# define __REG(x)&t;(*((volatile u32 *)io_p2v(x)))
macro_line|#else
multiline_comment|/*&n; * This __REG() version gives the same results as the one above,  except&n; * that we are fooling gcc somehow so it generates far better and smaller&n; * assembly code for access to contigous registers.  It&squot;s a shame that gcc&n; * doesn&squot;t guess this by itself.&n; */
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
DECL|macro|__PREG
macro_line|# define __PREG(x)&t;(io_v2p((u32)&amp;(x)))
macro_line|#else
DECL|macro|__REG
macro_line|# define __REG(x)&t;io_p2v(x)
DECL|macro|__PREG
macro_line|# define __PREG(x)&t;io_v2p(x)
macro_line|#endif
macro_line|#include &quot;SA-1100.h&quot;
macro_line|#ifdef CONFIG_SA1101
macro_line|#include &quot;SA-1101.h&quot;
macro_line|#endif
macro_line|#endif  /* _ASM_ARCH_HARDWARE_H */
eof
