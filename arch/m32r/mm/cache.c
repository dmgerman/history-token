multiline_comment|/*&n; *  linux/arch/m32r/mm/cache.c&n; *&n; *  Copyright (C) 2002  Hirokazu Takata&n; */
multiline_comment|/* $Id$ */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|macro|MCCR
macro_line|#undef MCCR
macro_line|#if defined(CONFIG_CHIP_XNUX2) || defined(CONFIG_CHIP_M32700) || defined(CONFIG_CHIP_VDEC2) || defined(CONFIG_CHIP_OPSP)
multiline_comment|/* Cache Control Register */
DECL|macro|MCCR
mdefine_line|#define MCCR&t;&t;((volatile unsigned long*)0xfffffffc)
DECL|macro|MCCR_CC
mdefine_line|#define MCCR_CC&t;&t;(1UL &lt;&lt; 7)&t;/* Cache mode modify bit */
DECL|macro|MCCR_IIV
mdefine_line|#define MCCR_IIV&t;(1UL &lt;&lt; 6)&t;/* I-cache invalidate */
DECL|macro|MCCR_DIV
mdefine_line|#define MCCR_DIV&t;(1UL &lt;&lt; 5)&t;/* D-cache invalidate */
DECL|macro|MCCR_DCB
mdefine_line|#define MCCR_DCB&t;(1UL &lt;&lt; 4)&t;/* D-cache copy back */
DECL|macro|MCCR_ICM
mdefine_line|#define MCCR_ICM&t;(1UL &lt;&lt; 1)&t;/* I-cache mode [0:off,1:on] */
DECL|macro|MCCR_DCM
mdefine_line|#define MCCR_DCM&t;(1UL &lt;&lt; 0)&t;/* D-cache mode [0:off,1:on] */
DECL|macro|MCCR_ICACHE_INV
mdefine_line|#define MCCR_ICACHE_INV&t;&t;(MCCR_CC|MCCR_IIV)
DECL|macro|MCCR_DCACHE_CB
mdefine_line|#define MCCR_DCACHE_CB&t;&t;(MCCR_CC|MCCR_DCB)
DECL|macro|MCCR_DCACHE_CBINV
mdefine_line|#define MCCR_DCACHE_CBINV&t;(MCCR_CC|MCCR_DIV|MCCR_DCB)
DECL|macro|CHECK_MCCR
mdefine_line|#define CHECK_MCCR(mccr)&t;(mccr = *MCCR)
macro_line|#elif defined(CONFIG_CHIP_M32102)
DECL|macro|MCCR
mdefine_line|#define MCCR&t;&t;((volatile unsigned long*)0xfffffffc)
DECL|macro|MCCR_IIV
mdefine_line|#define MCCR_IIV&t;(1UL &lt;&lt; 8)&t;/* I-cache invalidate */
DECL|macro|MCCR_ICACHE_INV
mdefine_line|#define MCCR_ICACHE_INV&t;&t;MCCR_IIV
macro_line|#endif /* CONFIG_CHIP_XNUX2 || CONFIG_CHIP_M32700 */
macro_line|#ifndef MCCR
macro_line|#error Unknown cache type.
macro_line|#endif
multiline_comment|/* Copy back and invalidate D-cache and invalidate I-cache all */
DECL|function|_flush_cache_all
r_void
id|_flush_cache_all
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_CHIP_M32102)
op_star
id|MCCR
op_assign
id|MCCR_ICACHE_INV
suffix:semicolon
macro_line|#else
r_int
r_int
id|mccr
suffix:semicolon
multiline_comment|/* Copyback and invalidate D-cache */
multiline_comment|/* Invalidate I-cache */
op_star
id|MCCR
op_assign
id|MCCR_ICACHE_INV
op_or
id|MCCR_DCACHE_CBINV
suffix:semicolon
r_while
c_loop
(paren
(paren
id|mccr
op_assign
op_star
id|MCCR
)paren
op_amp
id|MCCR_IIV
)paren
suffix:semicolon
multiline_comment|/* loop while invalidating... */
macro_line|#endif
)brace
multiline_comment|/* Copy back D-cache and invalidate I-cache all */
DECL|function|_flush_cache_copyback_all
r_void
id|_flush_cache_copyback_all
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_CHIP_M32102)
op_star
id|MCCR
op_assign
id|MCCR_ICACHE_INV
suffix:semicolon
macro_line|#else
r_int
r_int
id|mccr
suffix:semicolon
multiline_comment|/* Copyback D-cache */
multiline_comment|/* Invalidate I-cache */
op_star
id|MCCR
op_assign
id|MCCR_ICACHE_INV
op_or
id|MCCR_DCACHE_CB
suffix:semicolon
r_while
c_loop
(paren
(paren
id|mccr
op_assign
op_star
id|MCCR
)paren
op_amp
id|MCCR_IIV
)paren
suffix:semicolon
multiline_comment|/* loop while invalidating... */
macro_line|#endif
)brace
eof
