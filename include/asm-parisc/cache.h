multiline_comment|/*&n; * include/asm-parisc/cache.h&n; */
macro_line|#ifndef __ARCH_PARISC_CACHE_H
DECL|macro|__ARCH_PARISC_CACHE_H
mdefine_line|#define __ARCH_PARISC_CACHE_H
multiline_comment|/*&n;** XXX FIXME : L1_CACHE_BYTES (cacheline size) should be a boot time thing.&n;** &n;** 32-bit on PA2.0 is not covered well by the #ifdef __LP64__ below.&n;** PA2.0 processors have 64-byte cachelines.&n;**&n;** The issue is mostly cacheline ping-ponging on SMP boxes.&n;** To avoid this, code should define stuff to be per CPU on cacheline&n;** aligned boundaries. This can make a 2x or more difference in perf&n;** depending on how badly the thrashing is.&n;**&n;** We don&squot;t need to worry about I/O since all PA2.0 boxes (except T600)&n;** are I/O coherent. That means flushing less than you needed to generally&n;** doesn&squot;t matter - the I/O MMU will read/modify/write the cacheline.&n;**&n;** (Digression: it is possible to program I/O MMU&squot;s to not first read&n;** a cacheline for inbound data - ie just grab ownership and start writing.&n;** While it improves I/O throughput, you gotta know the device driver&n;** is well behaved and can deal with the issues.)&n;*/
macro_line|#if defined(__LP64__)
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES 64
macro_line|#else
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES 32
macro_line|#endif
DECL|macro|L1_CACHE_ALIGN
mdefine_line|#define L1_CACHE_ALIGN(x)       (((x)+(L1_CACHE_BYTES-1))&amp;~(L1_CACHE_BYTES-1))
DECL|macro|SMP_CACHE_BYTES
mdefine_line|#define SMP_CACHE_BYTES L1_CACHE_BYTES
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned __attribute__((__aligned__(L1_CACHE_BYTES)))
r_extern
r_void
id|init_cache
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* initializes cache-flushing */
r_extern
r_void
id|flush_data_cache
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* flushes data-cache only */
r_extern
r_void
id|flush_instruction_cache
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* flushes code-cache only */
r_extern
r_void
id|flush_all_caches
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* flushes code and data-cache */
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
r_struct
id|pdc_cache_info
id|cache_info
suffix:semicolon
DECL|macro|fdce
mdefine_line|#define fdce(addr) asm volatile(&quot;fdce 0(%0)&quot; : : &quot;r&quot; (addr))
DECL|macro|fice
mdefine_line|#define fice(addr) asm volatile(&quot;fice 0(%%sr1,%0)&quot; : : &quot;r&quot; (addr))
DECL|macro|pdtlbe
mdefine_line|#define pdtlbe(addr) asm volatile(&quot;pdtlbe 0(%%sr1,%0)&quot; : : &quot;r&quot; (addr))
DECL|macro|pdtlb_kernel
mdefine_line|#define pdtlb_kernel(addr)  asm volatile(&quot;pdtlb 0(%0)&quot; : : &quot;r&quot; (addr));
DECL|macro|pitlbe
mdefine_line|#define pitlbe(addr) asm volatile(&quot;pitlbe 0(%%sr1,%0)&quot; : : &quot;r&quot; (addr))
DECL|macro|kernel_fdc
mdefine_line|#define kernel_fdc(addr) asm volatile(&quot;fdc 0(%%sr0, %0)&quot; : : &quot;r&quot; (addr))
macro_line|#endif
eof
