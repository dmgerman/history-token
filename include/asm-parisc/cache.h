multiline_comment|/*&n; * include/asm-parisc/cache.h&n; */
macro_line|#ifndef __ARCH_PARISC_CACHE_H
DECL|macro|__ARCH_PARISC_CACHE_H
mdefine_line|#define __ARCH_PARISC_CACHE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * PA 2.0 processors have 64-byte cachelines; PA 1.1 processors have&n; * 32-byte cachelines.  The default configuration is not for SMP anyway,&n; * so if you&squot;re building for SMP, you should select the appropriate&n; * processor type.  There is a potential livelock danger when running&n; * a machine with this value set too small, but it&squot;s more probable you&squot;ll&n; * just ruin performance.&n; */
macro_line|#ifdef CONFIG_PA20
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES 64
DECL|macro|L1_CACHE_SHIFT
mdefine_line|#define L1_CACHE_SHIFT 6
macro_line|#else
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES 32
DECL|macro|L1_CACHE_SHIFT
mdefine_line|#define L1_CACHE_SHIFT 5
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
DECL|macro|L1_CACHE_ALIGN
mdefine_line|#define L1_CACHE_ALIGN(x)       (((x)+(L1_CACHE_BYTES-1))&amp;~(L1_CACHE_BYTES-1))
DECL|macro|SMP_CACHE_BYTES
mdefine_line|#define SMP_CACHE_BYTES L1_CACHE_BYTES
DECL|macro|L1_CACHE_SHIFT_MAX
mdefine_line|#define L1_CACHE_SHIFT_MAX 5&t;/* largest L1 which this arch supports */
r_extern
r_void
id|flush_data_cache_local
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* flushes local data-cache only */
r_extern
r_void
id|flush_instruction_cache_local
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* flushes local code-cache only */
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|flush_data_cache
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* flushes data-cache only (all processors) */
r_extern
r_void
id|flush_instruction_cache
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* flushes i-cache only (all processors) */
macro_line|#else
DECL|macro|flush_data_cache
mdefine_line|#define flush_data_cache flush_data_cache_local
DECL|macro|flush_instruction_cache
mdefine_line|#define flush_instruction_cache flush_instruction_cache_local
macro_line|#endif
r_extern
r_void
id|parisc_cache_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* initializes cache-flushing */
r_extern
r_void
id|flush_all_caches
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* flush everything (tlb &amp; cache) */
r_extern
r_int
id|get_cache_info
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|flush_user_icache_range_asm
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|flush_kernel_icache_range_asm
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|flush_user_dcache_range_asm
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|flush_kernel_dcache_range_asm
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|flush_kernel_dcache_page
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|flush_kernel_icache_page
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|disable_sr_hashing
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* turns off space register hashing */
r_extern
r_void
id|disable_sr_hashing_asm
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* low level support for above */
r_extern
r_void
id|free_sid
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_int
r_int
id|alloc_sid
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|flush_user_dcache_page
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|flush_user_icache_page
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_struct
id|seq_file
suffix:semicolon
r_extern
r_void
id|show_cache_info
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
suffix:semicolon
r_extern
r_int
id|split_tlb
suffix:semicolon
r_extern
r_int
id|dcache_stride
suffix:semicolon
r_extern
r_int
id|icache_stride
suffix:semicolon
r_extern
r_struct
id|pdc_cache_info
id|cache_info
suffix:semicolon
DECL|macro|pdtlb
mdefine_line|#define pdtlb(addr)         asm volatile(&quot;pdtlb 0(%%sr1,%0)&quot; : : &quot;r&quot; (addr));
DECL|macro|pitlb
mdefine_line|#define pitlb(addr)         asm volatile(&quot;pitlb 0(%%sr1,%0)&quot; : : &quot;r&quot; (addr));
DECL|macro|pdtlb_kernel
mdefine_line|#define pdtlb_kernel(addr)  asm volatile(&quot;pdtlb 0(%0)&quot; : : &quot;r&quot; (addr));
macro_line|#endif /* ! __ASSEMBLY__ */
multiline_comment|/* Classes of processor wrt: disabling space register hashing */
DECL|macro|SRHASH_PCXST
mdefine_line|#define SRHASH_PCXST    0   /* pcxs, pcxt, pcxt_ */
DECL|macro|SRHASH_PCXL
mdefine_line|#define SRHASH_PCXL     1   /* pcxl */
DECL|macro|SRHASH_PA20
mdefine_line|#define SRHASH_PA20     2   /* pcxu, pcxu_, pcxw, pcxw_ */
macro_line|#endif
eof
