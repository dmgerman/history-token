multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;coldfire.h -- Motorola ColdFire CPU sepecific defines&n; *&n; *&t;(C) Copyright 1999-2002, Greg Ungerer (gerg@snapgear.com)&n; *&t;(C) Copyright 2000, Lineo (www.lineo.com)&n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;coldfire_h
DECL|macro|coldfire_h
mdefine_line|#define&t;coldfire_h
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; *&t;Define the processor support peripherals base address.&n; *&t;This is generally setup by the boards start up code.&n; */
DECL|macro|MCF_MBAR
mdefine_line|#define&t;MCF_MBAR&t;0x10000000
DECL|macro|MCF_MBAR2
mdefine_line|#define&t;MCF_MBAR2&t;0x80000000
DECL|macro|MCF_IPSBAR
mdefine_line|#define&t;MCF_IPSBAR&t;0x40000000
macro_line|#if defined(CONFIG_M527x) || defined(CONFIG_M528x)
DECL|macro|MCF_MBAR
macro_line|#undef MCF_MBAR
DECL|macro|MCF_MBAR
mdefine_line|#define&t;MCF_MBAR&t;MCF_IPSBAR
macro_line|#endif
multiline_comment|/*&n; *&t;Define master clock frequency.&n; */
macro_line|#if defined(CONFIG_CLOCK_11MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;11289600
macro_line|#elif defined(CONFIG_CLOCK_16MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;16000000
macro_line|#elif defined(CONFIG_CLOCK_20MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;20000000
macro_line|#elif defined(CONFIG_CLOCK_24MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;24000000
macro_line|#elif defined(CONFIG_CLOCK_25MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;25000000
macro_line|#elif defined(CONFIG_CLOCK_33MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;33000000
macro_line|#elif defined(CONFIG_CLOCK_40MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;40000000
macro_line|#elif defined(CONFIG_CLOCK_45MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;45000000
macro_line|#elif defined(CONFIG_CLOCK_48MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;48000000
macro_line|#elif defined(CONFIG_CLOCK_50MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;50000000
macro_line|#elif defined(CONFIG_CLOCK_54MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;54000000
macro_line|#elif defined(CONFIG_CLOCK_60MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;60000000
macro_line|#elif defined(CONFIG_CLOCK_64MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;64000000
macro_line|#elif defined(CONFIG_CLOCK_66MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;66000000
macro_line|#elif defined(CONFIG_CLOCK_70MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;70000000
macro_line|#elif defined(CONFIG_CLOCK_100MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;100000000
macro_line|#elif defined(CONFIG_CLOCK_140MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;140000000
macro_line|#elif defined(CONFIG_CLOCK_150MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;150000000
macro_line|#elif defined(CONFIG_CLOCK_166MHz)
DECL|macro|MCF_CLK
mdefine_line|#define&t;MCF_CLK&t;&t;166000000
macro_line|#else
macro_line|#error &quot;Don&squot;t know what your ColdFire CPU clock frequency is??&quot;
macro_line|#endif
multiline_comment|/*&n; *&t;One some ColdFire family members the bus clock (used by internal&n; *&t;peripherals) is not the same as the CPU clock.&n; */
macro_line|#if defined(CONFIG_M5249) || defined(CONFIG_M527x)
DECL|macro|MCF_BUSCLK
mdefine_line|#define&t;MCF_BUSCLK&t;(MCF_CLK / 2)
macro_line|#else
DECL|macro|MCF_BUSCLK
mdefine_line|#define&t;MCF_BUSCLK&t;MCF_CLK
macro_line|#endif
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* coldfire_h */
eof
