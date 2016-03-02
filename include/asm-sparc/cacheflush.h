macro_line|#ifndef _SPARC_CACHEFLUSH_H
DECL|macro|_SPARC_CACHEFLUSH_H
mdefine_line|#define _SPARC_CACHEFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;&t;&t;/* Common for other includes */
singleline_comment|// #include &lt;linux/kernel.h&gt; from pgalloc.h
singleline_comment|// #include &lt;linux/sched.h&gt;  from pgalloc.h
singleline_comment|// #include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/btfixup.h&gt;
multiline_comment|/*&n; * Fine grained cache flushing.&n; */
macro_line|#ifdef CONFIG_SMP
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|local_flush_cache_all
comma
r_void
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|local_flush_cache_mm
comma
r_struct
id|mm_struct
op_star
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|local_flush_cache_range
comma
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|local_flush_cache_page
comma
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
)paren
DECL|macro|local_flush_cache_all
mdefine_line|#define local_flush_cache_all() BTFIXUP_CALL(local_flush_cache_all)()
DECL|macro|local_flush_cache_mm
mdefine_line|#define local_flush_cache_mm(mm) BTFIXUP_CALL(local_flush_cache_mm)(mm)
DECL|macro|local_flush_cache_range
mdefine_line|#define local_flush_cache_range(vma,start,end) BTFIXUP_CALL(local_flush_cache_range)(vma,start,end)
DECL|macro|local_flush_cache_page
mdefine_line|#define local_flush_cache_page(vma,addr) BTFIXUP_CALL(local_flush_cache_page)(vma,addr)
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|local_flush_page_to_ram
comma
r_int
r_int
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|local_flush_sig_insns
comma
r_struct
id|mm_struct
op_star
comma
r_int
r_int
)paren
DECL|macro|local_flush_page_to_ram
mdefine_line|#define local_flush_page_to_ram(addr) BTFIXUP_CALL(local_flush_page_to_ram)(addr)
DECL|macro|local_flush_sig_insns
mdefine_line|#define local_flush_sig_insns(mm,insn_addr) BTFIXUP_CALL(local_flush_sig_insns)(mm,insn_addr)
r_extern
r_void
id|smp_flush_cache_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|smp_flush_cache_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_extern
r_void
id|smp_flush_cache_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
r_extern
r_void
id|smp_flush_cache_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|page
)paren
suffix:semicolon
r_extern
r_void
id|smp_flush_page_to_ram
c_func
(paren
r_int
r_int
id|page
)paren
suffix:semicolon
r_extern
r_void
id|smp_flush_sig_insns
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|insn_addr
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|flush_cache_all
comma
r_void
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|flush_cache_mm
comma
r_struct
id|mm_struct
op_star
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|flush_cache_range
comma
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|flush_cache_page
comma
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
)paren
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all() BTFIXUP_CALL(flush_cache_all)()
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm) BTFIXUP_CALL(flush_cache_mm)(mm)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(vma,start,end) BTFIXUP_CALL(flush_cache_range)(vma,start,end)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma,addr) BTFIXUP_CALL(flush_cache_page)(vma,addr)
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start, end)&t;&t;do { } while (0)
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma, pg)&t;&t;do { } while (0)
DECL|macro|flush_icache_user_range
mdefine_line|#define flush_icache_user_range(vma,pg,adr,len)&t;do { } while (0)
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|__flush_page_to_ram
comma
r_int
r_int
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|flush_sig_insns
comma
r_struct
id|mm_struct
op_star
comma
r_int
r_int
)paren
DECL|macro|__flush_page_to_ram
mdefine_line|#define __flush_page_to_ram(addr) BTFIXUP_CALL(__flush_page_to_ram)(addr)
DECL|macro|flush_sig_insns
mdefine_line|#define flush_sig_insns(mm,insn_addr) BTFIXUP_CALL(flush_sig_insns)(mm,insn_addr)
r_extern
r_void
id|flush_page_to_ram
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page)&t;&t;&t;do { } while (0)
macro_line|#endif /* _SPARC_CACHEFLUSH_H */
eof
