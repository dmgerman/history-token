multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/hardware.h&n; *&n; * Copyright (C) 1998 Nicolas Pitre &lt;nico@cam.org&gt;&n; *&n; * This file contains the hardware definitions for SA1100 architecture&n; *&n; * 2000/05/23 John Dorsey &lt;john+@cs.cmu.edu&gt;&n; *      Definitions for SA1111 added.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
multiline_comment|/* Flushing areas */
DECL|macro|FLUSH_BASE_PHYS
mdefine_line|#define FLUSH_BASE_PHYS&t;&t;0xe0000000&t;/* SA1100 zero bank */
DECL|macro|FLUSH_BASE
mdefine_line|#define FLUSH_BASE&t;&t;0xf5000000
DECL|macro|FLUSH_BASE_MINICACHE
mdefine_line|#define FLUSH_BASE_MINICACHE&t;0xf5800000
DECL|macro|UNCACHEABLE_ADDR
mdefine_line|#define UNCACHEABLE_ADDR&t;0xfa050000
multiline_comment|/*&n; * Those are statically mapped PCMCIA IO space for designs using it as a&n; * generic IO bus, typically with ISA parts, hardwired IDE interfaces, etc.&n; * The actual PCMCIA code is mapping required IO region at run time.&n; */
DECL|macro|PCMCIA_IO_0_BASE
mdefine_line|#define PCMCIA_IO_0_BASE&t;0xf6000000
DECL|macro|PCMCIA_IO_1_BASE
mdefine_line|#define PCMCIA_IO_1_BASE&t;0xf7000000
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
multiline_comment|/*&n; * Implementation specifics.&n; *&n; * *** NOTE ***&n; * Any definitions in these files should be prefixed by an identifier -&n; * eg, ASSABET_UCB1300_IRQ  This will allow us to eleminate these&n; * ifdefs, and lots of other preprocessor gunk elsewhere.&n; */
macro_line|#ifdef CONFIG_SA1100_PANGOLIN
macro_line|#include &quot;pangolin.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_HUW_WEBPANEL
macro_line|#include &quot;huw_webpanel.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_PFS168
macro_line|#include &quot;pfs168.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_YOPY
macro_line|#include &quot;yopy.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_FREEBIRD
macro_line|#include &quot;freebird.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_CERF
macro_line|#include &quot;cerf.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_EMPEG
macro_line|#include &quot;empeg.h&quot;
macro_line|#endif
macro_line|#include &quot;h3600.h&quot;
macro_line|#ifdef CONFIG_SA1100_ITSY
macro_line|#include &quot;itsy.h&quot;
macro_line|#endif
macro_line|#if defined(CONFIG_SA1100_GRAPHICSCLIENT)
macro_line|#include &quot;graphicsclient.h&quot;
macro_line|#endif
macro_line|#if defined(CONFIG_SA1100_OMNIMETER)
macro_line|#include &quot;omnimeter.h&quot;
macro_line|#endif
macro_line|#if defined(CONFIG_SA1100_JORNADA720)
macro_line|#include &quot;jornada720.h&quot;
macro_line|#endif
macro_line|#if defined(CONFIG_SA1100_PLEB)
macro_line|#include &quot;pleb.h&quot;
macro_line|#endif
macro_line|#if defined(CONFIG_SA1100_LART)
macro_line|#include &quot;lart.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_SIMPAD
macro_line|#include &quot;simpad.h&quot;
macro_line|#endif
macro_line|#if defined(CONFIG_SA1100_GRAPHICSMASTER)
macro_line|#include &quot;graphicsmaster.h&quot;
macro_line|#endif
macro_line|#if defined(CONFIG_SA1100_ADSBITSY)
macro_line|#include &quot;adsbitsy.h&quot;
macro_line|#endif
macro_line|#include &quot;system3.h&quot;
macro_line|#ifdef CONFIG_SA1101
multiline_comment|/*&n; * We have mapped the sa1101 depending on the value of SA1101_BASE.&n; * It then appears from 0xf4000000.&n; */
DECL|macro|SA1101_p2v
mdefine_line|#define SA1101_p2v( x )         ((x) - SA1101_BASE + 0xf4000000)
DECL|macro|SA1101_v2p
mdefine_line|#define SA1101_v2p( x )         ((x) - 0xf4000000  + SA1101_BASE)
macro_line|#include &quot;SA-1101.h&quot;
macro_line|#endif
macro_line|#if defined(CONFIG_SA1100_OMNIMETER)
macro_line|#include &quot;omnimeter.h&quot;
macro_line|#endif
macro_line|#if defined(CONFIG_SA1100_JORNADA720)
macro_line|#include &quot;jornada720.h&quot;
macro_line|#endif
macro_line|#if defined(CONFIG_SA1100_FLEXANET)
macro_line|#include &quot;flexanet.h&quot;
macro_line|#endif
macro_line|#endif  /* _ASM_ARCH_HARDWARE_H */
eof
