macro_line|#ifndef _ALPHA_CACHEFLUSH_H
DECL|macro|_ALPHA_CACHEFLUSH_H
mdefine_line|#define _ALPHA_CACHEFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
multiline_comment|/* Caches aren&squot;t brain-dead on the Alpha. */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(vma, start, end)&t;do { } while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma, vmaddr)&t;&t;do { } while (0)
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;&t;&t;do { } while (0)
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page)&t;&t;&t;do { } while (0)
multiline_comment|/* Note that the following two definitions are _highly_ dependent&n;   on the contexts in which they are used in the kernel.  I personally&n;   think it is criminal how loosely defined these macros are.  */
multiline_comment|/* We need to flush the kernel&squot;s icache after loading modules.  The&n;   only other use of this macro is in load_aout_interp which is not&n;   used on Alpha. &n;&n;   Note that this definition should *not* be used for userspace&n;   icache flushing.  While functional, it is _way_ overkill.  The&n;   icache is tagged with ASNs and it suffices to allocate a new ASN&n;   for the process.  */
macro_line|#ifndef CONFIG_SMP
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start, end)&t;&t;imb()
macro_line|#else
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start, end)&t;&t;smp_imb()
r_extern
r_void
id|smp_imb
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* We need to flush the userspace icache after setting breakpoints in&n;   ptrace.&n;&n;   Instead of indiscriminately using imb, take advantage of the fact&n;   that icache entries are tagged with the ASN and load a new mm context.  */
multiline_comment|/* ??? Ought to use this in arch/alpha/kernel/signal.c too.  */
macro_line|#ifndef CONFIG_SMP
r_extern
r_void
id|__load_new_mm_context
c_func
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
r_static
r_inline
r_void
DECL|function|flush_icache_user_range
id|flush_icache_user_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|addr
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;active_mm
op_eq
id|mm
)paren
id|__load_new_mm_context
c_func
(paren
id|mm
)paren
suffix:semicolon
r_else
id|mm-&gt;context
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#else
r_extern
r_void
id|flush_icache_user_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|addr
comma
r_int
id|len
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* This is used only in do_no_page and do_swap_page.  */
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma, page) &bslash;&n;  flush_icache_user_range((vma), (page), 0, 0)
macro_line|#endif /* _ALPHA_CACHEFLUSH_H */
eof
