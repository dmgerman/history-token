macro_line|#ifndef _LINUX_SWSUSP_H
DECL|macro|_LINUX_SWSUSP_H
mdefine_line|#define _LINUX_SWSUSP_H
macro_line|#ifdef CONFIG_X86
macro_line|#include &lt;asm/suspend.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#ifdef CONFIG_SOFTWARE_SUSPEND
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
DECL|member|dummy
id|swp_entry_t
id|dummy
suffix:semicolon
multiline_comment|/* we need scratch space at &n;&t;&t;&t;&t;&t; * end of page (see link, diskpage)&n;&t;&t;&t;&t;&t; */
DECL|typedef|suspend_pagedir_t
)brace
id|suspend_pagedir_t
suffix:semicolon
DECL|macro|SWAP_FILENAME_MAXLENGTH
mdefine_line|#define SWAP_FILENAME_MAXLENGTH&t;32
DECL|struct|suspend_header
r_struct
id|suspend_header
(brace
DECL|member|version_code
id|__u32
id|version_code
suffix:semicolon
DECL|member|num_physpages
r_int
r_int
id|num_physpages
suffix:semicolon
DECL|member|machine
r_char
id|machine
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|version
r_char
id|version
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|num_cpus
r_int
id|num_cpus
suffix:semicolon
DECL|member|page_size
r_int
id|page_size
suffix:semicolon
DECL|member|suspend_pagedir
id|suspend_pagedir_t
op_star
id|suspend_pagedir
suffix:semicolon
DECL|member|num_pbes
r_int
r_int
id|num_pbes
suffix:semicolon
DECL|struct|swap_location
r_struct
id|swap_location
(brace
DECL|member|filename
r_char
id|filename
(braket
id|SWAP_FILENAME_MAXLENGTH
)braket
suffix:semicolon
DECL|member|swap_location
)brace
id|swap_location
(braket
id|MAX_SWAPFILES
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SUSPEND_PD_PAGES
mdefine_line|#define SUSPEND_PD_PAGES(x)     (((x)*sizeof(struct pbe))/PAGE_SIZE+1)
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
r_int
r_int
id|nr_copy_pages
id|__nosavedata
suffix:semicolon
r_extern
id|suspend_pagedir_t
op_star
id|pagedir_nosave
id|__nosavedata
suffix:semicolon
multiline_comment|/* Communication between acpi and arch/i386/suspend.c */
r_extern
r_void
id|do_suspend_lowlevel
c_func
(paren
r_int
id|resume
)paren
suffix:semicolon
r_extern
r_void
id|do_suspend_lowlevel_s4bios
c_func
(paren
r_int
id|resume
)paren
suffix:semicolon
macro_line|#else&t;/* CONFIG_SOFTWARE_SUSPEND */
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
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_SOFTWARE_SUSPEND */
macro_line|#ifdef CONFIG_PM
r_extern
r_void
id|refrigerator
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#else
DECL|function|refrigerator
r_static
r_inline
r_void
id|refrigerator
c_func
(paren
r_int
r_int
id|flag
)paren
(brace
)brace
macro_line|#endif&t;/* CONFIG_PM */
macro_line|#endif /* _LINUX_SWSUSP_H */
eof
