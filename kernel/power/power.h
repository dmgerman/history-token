macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
multiline_comment|/* With SUSPEND_CONSOLE defined, it suspend looks *really* cool, but&n;   we probably do not take enough locks for switching consoles, etc,&n;   so bad things might happen.&n;*/
macro_line|#if defined(CONFIG_VT) &amp;&amp; defined(CONFIG_VT_CONSOLE)
DECL|macro|SUSPEND_CONSOLE
mdefine_line|#define SUSPEND_CONSOLE&t;(MAX_NR_CONSOLES-1)
macro_line|#endif
DECL|struct|swsusp_info
r_struct
id|swsusp_info
(brace
DECL|member|uts
r_struct
id|new_utsname
id|uts
suffix:semicolon
DECL|member|version_code
id|u32
id|version_code
suffix:semicolon
DECL|member|num_physpages
r_int
r_int
id|num_physpages
suffix:semicolon
DECL|member|cpus
r_int
id|cpus
suffix:semicolon
DECL|member|image_pages
r_int
r_int
id|image_pages
suffix:semicolon
DECL|member|pagedir_pages
r_int
r_int
id|pagedir_pages
suffix:semicolon
DECL|member|suspend_pagedir
id|suspend_pagedir_t
op_star
id|suspend_pagedir
suffix:semicolon
DECL|member|pagedir
id|swp_entry_t
id|pagedir
(braket
l_int|768
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
id|PAGE_SIZE
)paren
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PM_DISK
r_extern
r_int
id|pm_suspend_disk
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|function|pm_suspend_disk
r_static
r_inline
r_int
id|pm_suspend_disk
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
macro_line|#endif
r_extern
r_struct
id|semaphore
id|pm_sem
suffix:semicolon
DECL|macro|power_attr
mdefine_line|#define power_attr(_name) &bslash;&n;static struct subsys_attribute _name##_attr = {&t;&bslash;&n;&t;.attr&t;= {&t;&t;&t;&t;&bslash;&n;&t;&t;.name = __stringify(_name),&t;&bslash;&n;&t;&t;.mode = 0644,&t;&t;&t;&bslash;&n;&t;},&t;&t;&t;&t;&t;&bslash;&n;&t;.show&t;= _name##_show,&t;&t;&t;&bslash;&n;&t;.store&t;= _name##_store,&t;&t;&bslash;&n;}
r_extern
r_struct
id|subsystem
id|power_subsys
suffix:semicolon
r_extern
r_int
id|freeze_processes
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|thaw_processes
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
eof
