multiline_comment|/*&n; * BK Id: SCCS/s.cache.h 1.10 10/18/01 15:02:09 trini&n; */
multiline_comment|/*&n; * include/asm-ppc/cache.h&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ARCH_PPC_CACHE_H
DECL|macro|__ARCH_PPC_CACHE_H
mdefine_line|#define __ARCH_PPC_CACHE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/* bytes per L1 cache line */
macro_line|#if defined(CONFIG_8xx) || defined(CONFIG_403GCX)
DECL|macro|L1_CACHE_LINE_SIZE
mdefine_line|#define&t;L1_CACHE_LINE_SIZE&t;16
DECL|macro|LG_L1_CACHE_LINE_SIZE
mdefine_line|#define LG_L1_CACHE_LINE_SIZE&t;4
DECL|macro|MAX_L1_COPY_PREFETCH
mdefine_line|#define MAX_L1_COPY_PREFETCH&t;1
macro_line|#elif defined(CONFIG_PPC64BRIDGE)
DECL|macro|L1_CACHE_LINE_SIZE
mdefine_line|#define L1_CACHE_LINE_SIZE&t;128
DECL|macro|LG_L1_CACHE_LINE_SIZE
mdefine_line|#define LG_L1_CACHE_LINE_SIZE&t;7
DECL|macro|MAX_L1_COPY_PREFETCH
mdefine_line|#define MAX_L1_COPY_PREFETCH&t;1
macro_line|#else
DECL|macro|L1_CACHE_LINE_SIZE
mdefine_line|#define&t;L1_CACHE_LINE_SIZE  32
DECL|macro|LG_L1_CACHE_LINE_SIZE
mdefine_line|#define LG_L1_CACHE_LINE_SIZE&t;5
DECL|macro|MAX_L1_COPY_PREFETCH
mdefine_line|#define MAX_L1_COPY_PREFETCH&t;4
macro_line|#endif
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define&t;L1_CACHE_BYTES L1_CACHE_LINE_SIZE
DECL|macro|SMP_CACHE_BYTES
mdefine_line|#define&t;SMP_CACHE_BYTES L1_CACHE_BYTES
DECL|macro|L1_CACHE_ALIGN
mdefine_line|#define&t;L1_CACHE_ALIGN(x)       (((x)+(L1_CACHE_BYTES-1))&amp;~(L1_CACHE_BYTES-1))
DECL|macro|L1_CACHE_PAGES
mdefine_line|#define&t;L1_CACHE_PAGES&t;&t;8
macro_line|#ifdef MODULE
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned __attribute__((__aligned__(L1_CACHE_BYTES)))
macro_line|#else
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned&t;&t;&t;&t;&t;&bslash;&n;  __attribute__((__aligned__(L1_CACHE_BYTES),&t;&t;&t;&bslash;&n;&t;&t; __section__(&quot;.data.cacheline_aligned&quot;)))
macro_line|#endif
macro_line|#if defined(__KERNEL__) &amp;&amp; !defined(__ASSEMBLY__)
r_extern
r_void
id|flush_dcache_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|stop
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* prep registers for L2 */
DECL|macro|CACHECRBA
mdefine_line|#define CACHECRBA       0x80000823      /* Cache configuration register address */
DECL|macro|L2CACHE_MASK
mdefine_line|#define L2CACHE_MASK&t;0x03&t;/* Mask for 2 L2 Cache bits */
DECL|macro|L2CACHE_512KB
mdefine_line|#define L2CACHE_512KB&t;0x00&t;/* 512KB */
DECL|macro|L2CACHE_256KB
mdefine_line|#define L2CACHE_256KB&t;0x01&t;/* 256KB */
DECL|macro|L2CACHE_1MB
mdefine_line|#define L2CACHE_1MB&t;0x02&t;/* 1MB */
DECL|macro|L2CACHE_NONE
mdefine_line|#define L2CACHE_NONE&t;0x03&t;/* NONE */
DECL|macro|L2CACHE_PARITY
mdefine_line|#define L2CACHE_PARITY  0x08    /* Mask for L2 Cache Parity Protected bit */
macro_line|#ifdef CONFIG_8xx
multiline_comment|/* Cache control on the MPC8xx is provided through some additional&n; * special purpose registers.&n; */
DECL|macro|IC_CST
mdefine_line|#define IC_CST&t;&t;560&t;/* Instruction cache control/status */
DECL|macro|IC_ADR
mdefine_line|#define IC_ADR&t;&t;561&t;/* Address needed for some commands */
DECL|macro|IC_DAT
mdefine_line|#define IC_DAT&t;&t;562&t;/* Read-only data register */
DECL|macro|DC_CST
mdefine_line|#define DC_CST&t;&t;568&t;/* Data cache control/status */
DECL|macro|DC_ADR
mdefine_line|#define DC_ADR&t;&t;569&t;/* Address needed for some commands */
DECL|macro|DC_DAT
mdefine_line|#define DC_DAT&t;&t;570&t;/* Read-only data register */
multiline_comment|/* Commands.  Only the first few are available to the instruction cache.&n;*/
DECL|macro|IDC_ENABLE
mdefine_line|#define&t;IDC_ENABLE&t;0x02000000&t;/* Cache enable */
DECL|macro|IDC_DISABLE
mdefine_line|#define IDC_DISABLE&t;0x04000000&t;/* Cache disable */
DECL|macro|IDC_LDLCK
mdefine_line|#define IDC_LDLCK&t;0x06000000&t;/* Load and lock */
DECL|macro|IDC_UNLINE
mdefine_line|#define IDC_UNLINE&t;0x08000000&t;/* Unlock line */
DECL|macro|IDC_UNALL
mdefine_line|#define IDC_UNALL&t;0x0a000000&t;/* Unlock all */
DECL|macro|IDC_INVALL
mdefine_line|#define IDC_INVALL&t;0x0c000000&t;/* Invalidate all */
DECL|macro|DC_FLINE
mdefine_line|#define DC_FLINE&t;0x0e000000&t;/* Flush data cache line */
DECL|macro|DC_SFWT
mdefine_line|#define DC_SFWT&t;&t;0x01000000&t;/* Set forced writethrough mode */
DECL|macro|DC_CFWT
mdefine_line|#define DC_CFWT&t;&t;0x03000000&t;/* Clear forced writethrough mode */
DECL|macro|DC_SLES
mdefine_line|#define DC_SLES&t;&t;0x05000000&t;/* Set little endian swap mode */
DECL|macro|DC_CLES
mdefine_line|#define DC_CLES&t;&t;0x07000000&t;/* Clear little endian swap mode */
multiline_comment|/* Status.&n;*/
DECL|macro|IDC_ENABLED
mdefine_line|#define IDC_ENABLED&t;0x80000000&t;/* Cache is enabled */
DECL|macro|IDC_CERR1
mdefine_line|#define IDC_CERR1&t;0x00200000&t;/* Cache error 1 */
DECL|macro|IDC_CERR2
mdefine_line|#define IDC_CERR2&t;0x00100000&t;/* Cache error 2 */
DECL|macro|IDC_CERR3
mdefine_line|#define IDC_CERR3&t;0x00080000&t;/* Cache error 3 */
DECL|macro|DC_DFWT
mdefine_line|#define DC_DFWT&t;&t;0x40000000&t;/* Data cache is forced write through */
DECL|macro|DC_LES
mdefine_line|#define DC_LES&t;&t;0x20000000&t;/* Caches are little endian mode */
macro_line|#endif /* CONFIG_8xx */
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
eof
