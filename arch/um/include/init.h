macro_line|#ifndef _LINUX_UML_INIT_H
DECL|macro|_LINUX_UML_INIT_H
mdefine_line|#define _LINUX_UML_INIT_H
multiline_comment|/* These macros are used to mark some functions or&n; * initialized data (doesn&squot;t apply to uninitialized data)&n; * as `initialization&squot; functions. The kernel can take this&n; * as hint that the function is used only during the initialization&n; * phase and free up used memory resources after&n; *&n; * Usage:&n; * For functions:&n; *&n; * You should add __init immediately before the function name, like:&n; *&n; * static void __init initme(int x, int y)&n; * {&n; *    extern int z; z = x * y;&n; * }&n; *&n; * If the function has a prototype somewhere, you can also add&n; * __init between closing brace of the prototype and semicolon:&n; *&n; * extern int initialize_foobar_device(int, int, int) __init;&n; *&n; * For initialized data:&n; * You should insert __initdata between the variable name and equal&n; * sign followed by value, e.g.:&n; *&n; * static int init_variable __initdata = 0;&n; * static char linux_logo[] __initdata = { 0x32, 0x36, ... };&n; *&n; * Don&squot;t forget to initialize data not at file scope, i.e. within a function,&n; * as gcc otherwise puts the data into the bss section and not into the init&n; * section.&n; *&n; * Also note, that this data cannot be &quot;const&quot;.&n; */
macro_line|#ifndef _LINUX_INIT_H
DECL|typedef|initcall_t
r_typedef
r_int
(paren
op_star
id|initcall_t
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|exitcall_t
r_typedef
r_void
(paren
op_star
id|exitcall_t
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* These are for everybody (although not all archs will actually&n;   discard it in modules) */
DECL|macro|__init
mdefine_line|#define __init&t;&t;__attribute__ ((__section__ (&quot;.init.text&quot;)))
DECL|macro|__initdata
mdefine_line|#define __initdata&t;__attribute__ ((__section__ (&quot;.init.data&quot;)))
DECL|macro|__exitdata
mdefine_line|#define __exitdata&t;__attribute__ ((__section__(&quot;.exit.data&quot;)))
DECL|macro|__exit_call
mdefine_line|#define __exit_call&t;__attribute_used__ __attribute__ ((__section__ (&quot;.exitcall.exit&quot;)))
macro_line|#ifdef MODULE
DECL|macro|__exit
mdefine_line|#define __exit&t;&t;__attribute__ ((__section__(&quot;.exit.text&quot;)))
macro_line|#else
DECL|macro|__exit
mdefine_line|#define __exit&t;&t;__attribute_used__ __attribute__ ((__section__(&quot;.exit.text&quot;)))
macro_line|#endif
macro_line|#endif
macro_line|#ifndef MODULE
DECL|struct|uml_param
r_struct
id|uml_param
(brace
DECL|member|str
r_const
r_char
op_star
id|str
suffix:semicolon
DECL|member|setup_func
r_int
(paren
op_star
id|setup_func
)paren
(paren
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
id|initcall_t
id|__uml_initcall_start
comma
id|__uml_initcall_end
suffix:semicolon
r_extern
id|initcall_t
id|__uml_postsetup_start
comma
id|__uml_postsetup_end
suffix:semicolon
r_extern
r_const
r_char
op_star
id|__uml_help_start
comma
op_star
id|__uml_help_end
suffix:semicolon
macro_line|#endif
DECL|macro|__uml_initcall
mdefine_line|#define __uml_initcall(fn)&t;&t;&t;&t;&t;  &t;&bslash;&n;&t;static initcall_t __uml_initcall_##fn __uml_init_call = fn
DECL|macro|__uml_exitcall
mdefine_line|#define __uml_exitcall(fn)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;static exitcall_t __uml_exitcall_##fn __uml_exit_call = fn
r_extern
r_struct
id|uml_param
id|__uml_setup_start
comma
id|__uml_setup_end
suffix:semicolon
DECL|macro|__uml_postsetup
mdefine_line|#define __uml_postsetup(fn)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;static initcall_t __uml_postsetup_##fn __uml_postsetup_call = fn
DECL|macro|__non_empty_string
mdefine_line|#define __non_empty_string(dummyname,string)&t;&t;&t;&t;&bslash;&n;&t;struct __uml_non_empty_string_struct_##dummyname&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;char _string[sizeof(string)-2];&t;&t;&t;&t;&bslash;&n;&t;}
macro_line|#ifndef MODULE
DECL|macro|__uml_setup
mdefine_line|#define __uml_setup(str, fn, help...)&t;&t;&t;&t;&t;&bslash;&n;&t;__non_empty_string(fn ##_setup, str);&t;&t;&t;&t;&bslash;&n;&t;__uml_help(fn, help);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;static char __uml_setup_str_##fn[] __initdata = str;&t;&t;&bslash;&n;&t;static struct uml_param __uml_setup_##fn __uml_init_setup = { __uml_setup_str_##fn, fn }
macro_line|#else
DECL|macro|__uml_setup
mdefine_line|#define __uml_setup(str, fn, help...)&t;&t;&t;&t;&t;&bslash;&n;
macro_line|#endif
DECL|macro|__uml_help
mdefine_line|#define __uml_help(fn, help...)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__non_empty_string(fn ##__help, help);&t;&t;&t;&t;&bslash;&n;&t;static char __uml_help_str_##fn[] __initdata = help;&t;&t;&bslash;&n;&t;static const char *__uml_help_##fn __uml_setup_help = __uml_help_str_##fn
multiline_comment|/*&n; * Mark functions and data as being only used at initialization&n; * or exit time.&n; */
DECL|macro|__uml_init_setup
mdefine_line|#define __uml_init_setup&t;__attribute_used__ __attribute__ ((__section__ (&quot;.uml.setup.init&quot;)))
DECL|macro|__uml_setup_help
mdefine_line|#define __uml_setup_help&t;__attribute_used__ __attribute__ ((__section__ (&quot;.uml.help.init&quot;)))
DECL|macro|__uml_init_call
mdefine_line|#define __uml_init_call&t;&t;__attribute_used__ __attribute__ ((__section__ (&quot;.uml.initcall.init&quot;)))
DECL|macro|__uml_postsetup_call
mdefine_line|#define __uml_postsetup_call&t;__attribute_used__ __attribute__ ((__section__ (&quot;.uml.postsetup.init&quot;)))
DECL|macro|__uml_exit_call
mdefine_line|#define __uml_exit_call&t;&t;__attribute_used__ __attribute__ ((__section__ (&quot;.uml.exitcall.exit&quot;)))
macro_line|#ifndef __KERNEL__
DECL|macro|__initcall
mdefine_line|#define __initcall(fn) static initcall_t __initcall_##fn __init_call = fn
DECL|macro|__exitcall
mdefine_line|#define __exitcall(fn) static exitcall_t __exitcall_##fn __exit_call = fn
DECL|macro|__init_call
mdefine_line|#define __init_call __attribute__ ((unused,__section__ (&quot;.initcall.init&quot;)))
macro_line|#endif
macro_line|#endif /* _LINUX_UML_INIT_H */
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
