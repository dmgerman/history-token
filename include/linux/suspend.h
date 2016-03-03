macro_line|#ifndef _LINUX_SWSUSP_H
DECL|macro|_LINUX_SWSUSP_H
mdefine_line|#define _LINUX_SWSUSP_H
macro_line|#if defined(CONFIG_X86) || defined(CONFIG_FRV) || defined(CONFIG_PPC32)
macro_line|#include &lt;asm/suspend.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
multiline_comment|/* page backup entry */
DECL|struct|pbe
r_typedef
r_struct
id|pbe
(brace
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
multiline_comment|/* address of the copy */
DECL|member|orig_address
r_int
r_int
id|orig_address
suffix:semicolon
multiline_comment|/* original address of page */
DECL|member|swap_address
id|swp_entry_t
id|swap_address
suffix:semicolon
DECL|member|next
r_struct
id|pbe
op_star
id|next
suffix:semicolon
multiline_comment|/* also used as scratch space at&n;&t;&t;&t;&t; * end of page (see link, diskpage)&n;&t;&t;&t;&t; */
DECL|typedef|suspend_pagedir_t
)brace
id|suspend_pagedir_t
suffix:semicolon
DECL|macro|for_each_pbe
mdefine_line|#define for_each_pbe(pbe, pblist) &bslash;&n;&t;for (pbe = pblist ; pbe ; pbe = pbe-&gt;next)
DECL|macro|PBES_PER_PAGE
mdefine_line|#define PBES_PER_PAGE      (PAGE_SIZE/sizeof(struct pbe))
DECL|macro|PB_PAGE_SKIP
mdefine_line|#define PB_PAGE_SKIP       (PBES_PER_PAGE-1)
DECL|macro|for_each_pb_page
mdefine_line|#define for_each_pb_page(pbe, pblist) &bslash;&n;&t;for (pbe = pblist ; pbe ; pbe = (pbe+PB_PAGE_SKIP)-&gt;next)
DECL|macro|SWAP_FILENAME_MAXLENGTH
mdefine_line|#define SWAP_FILENAME_MAXLENGTH&t;32
r_extern
id|dev_t
id|swsusp_resume_device
suffix:semicolon
multiline_comment|/* mm/vmscan.c */
r_extern
r_int
id|shrink_mem
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* mm/page_alloc.c */
r_extern
r_void
id|drain_local_pages
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mark_free_pages
c_func
(paren
r_struct
id|zone
op_star
id|zone
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PM
multiline_comment|/* kernel/power/swsusp.c */
r_extern
r_int
id|software_suspend
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pm_prepare_console
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pm_restore_console
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|function|software_suspend
r_static
r_inline
r_int
id|software_suspend
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Warning: fake suspend called&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|disable_nonboot_cpus
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|enable_nonboot_cpus
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|function|disable_nonboot_cpus
r_static
r_inline
r_void
id|disable_nonboot_cpus
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|enable_nonboot_cpus
r_static
r_inline
r_void
id|enable_nonboot_cpus
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
r_void
id|save_processor_state
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|restore_processor_state
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|saved_context
suffix:semicolon
r_void
id|__save_processor_state
c_func
(paren
r_struct
id|saved_context
op_star
id|ctxt
)paren
suffix:semicolon
r_void
id|__restore_processor_state
c_func
(paren
r_struct
id|saved_context
op_star
id|ctxt
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_SWSUSP_H */
eof
