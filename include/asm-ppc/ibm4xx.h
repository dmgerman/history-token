multiline_comment|/*&n; *&n; *    Copyright (c) 1999 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *&n; *    Module name: ibm4xx.h&n; *&n; *    Description:&n; *&t;A generic include file which pulls in appropriate include files&n; *      for specific board types based on configuration settings.&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_IBM4XX_H__
DECL|macro|__ASM_IBM4XX_H__
mdefine_line|#define __ASM_IBM4XX_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_4xx
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Device Control Registers */
DECL|macro|stringify
mdefine_line|#define stringify(s)&t;tostring(s)
DECL|macro|tostring
mdefine_line|#define tostring(s)&t;#s
DECL|macro|mfdcr
mdefine_line|#define mfdcr(rn) mfdcr_or_dflt(rn, 0)
DECL|macro|mfdcr_or_dflt
mdefine_line|#define mfdcr_or_dflt(rn,default_rval) &bslash;&n;&t;({unsigned int rval;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (rn == 0)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;rval = default_rval;&t;&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;asm volatile(&quot;mfdcr %0,&quot; stringify(rn) : &quot;=r&quot; (rval));&t;&bslash;&n;&t;rval;})
DECL|macro|mtdcr
mdefine_line|#define mtdcr(rn, v)  &bslash;&n;do {                  &bslash;&n;&t;if (rn != 0) &bslash;&n;&t;&t;asm volatile(&quot;mtdcr &quot; stringify(rn) &quot;,%0&quot; : : &quot;r&quot; (v));&t;&bslash;&n;} while (0)
multiline_comment|/* R/W of indirect DCRs make use of standard naming conventions for DCRs */
DECL|macro|mfdcri
mdefine_line|#define mfdcri(base, reg)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&bslash;&n;     mtdcr(base##_CFGADDR, base##_##reg);&t;&bslash;&n;     mfdcr(base##_CFGDATA);&t;&t;&t;&bslash;&n;})
DECL|macro|mtdcri
mdefine_line|#define mtdcri(base, reg, data)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;     mtdcr(base##_CFGADDR, base##_##reg);&t;&bslash;&n;     mtdcr(base##_CFGDATA, data);&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* CONFIG_4xx */
macro_line|#ifdef CONFIG_40x
macro_line|#if defined(CONFIG_ASH)
macro_line|#include &lt;platforms/4xx/ash.h&gt;
macro_line|#endif
macro_line|#if defined (CONFIG_CEDAR)
macro_line|#include &lt;platforms/4xx/cedar.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_CPCI405)
macro_line|#include &lt;platforms/4xx/cpci405.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_EP405)
macro_line|#include &lt;platforms/4xx/ep405.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_OAK)
macro_line|#include &lt;platforms/4xx/oak.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_REDWOOD_4)
macro_line|#include &lt;platforms/4xx/redwood.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_REDWOOD_5)
macro_line|#include &lt;platforms/4xx/redwood5.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_WALNUT)
macro_line|#include &lt;platforms/4xx/walnut.h&gt;
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * The &quot;residual&quot; board information structure the boot loader passes&n; * into the kernel.&n; */
r_extern
id|bd_t
id|__res
suffix:semicolon
r_void
id|ppc4xx_setup_arch
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ppc4xx_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ppc4xx_init_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ppc4xx_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef PPC4xx_MACHINE_NAME
DECL|macro|PPC4xx_MACHINE_NAME
mdefine_line|#define PPC4xx_MACHINE_NAME&t;&quot;Unidentified 4xx class&quot;
macro_line|#endif
multiline_comment|/* IO_BASE is for PCI I/O.&n; * ISA not supported, just here to resolve copilation.&n; */
macro_line|#ifndef _IO_BASE
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE&t;0xe8000000&t;/* The PCI address window */
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE&t;0
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET&t;0
macro_line|#endif
macro_line|#elif CONFIG_44x
macro_line|#if defined(CONFIG_EBONY)
macro_line|#include &lt;platforms/4xx/ebony.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_OCOTEA)
macro_line|#include &lt;platforms/4xx/ocotea.h&gt;
macro_line|#endif
macro_line|#endif /* CONFIG_40x */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * The &quot;residual&quot; board information structure the boot loader passes&n; * into the kernel.&n; */
r_extern
id|bd_t
id|__res
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __ASM_IBM4XX_H__ */
macro_line|#endif /* __KERNEL__ */
eof
