macro_line|#ifndef _LINUX_INIT_H
DECL|macro|_LINUX_INIT_H
mdefine_line|#define _LINUX_INIT_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
multiline_comment|/* These macros are used to mark some functions or &n; * initialized data (doesn&squot;t apply to uninitialized data)&n; * as `initialization&squot; functions. The kernel can take this&n; * as hint that the function is used only during the initialization&n; * phase and free up used memory resources after&n; *&n; * Usage:&n; * For functions:&n; * &n; * You should add __init immediately before the function name, like:&n; *&n; * static void __init initme(int x, int y)&n; * {&n; *    extern int z; z = x * y;&n; * }&n; *&n; * If the function has a prototype somewhere, you can also add&n; * __init between closing brace of the prototype and semicolon:&n; *&n; * extern int initialize_foobar_device(int, int, int) __init;&n; *&n; * For initialized data:&n; * You should insert __initdata between the variable name and equal&n; * sign followed by value, e.g.:&n; *&n; * static int init_variable __initdata = 0;&n; * static char linux_logo[] __initdata = { 0x32, 0x36, ... };&n; *&n; * Don&squot;t forget to initialize data not at file scope, i.e. within a function,&n; * as gcc otherwise puts the data into the bss section and not into the init&n; * section.&n; * &n; * Also note, that this data cannot be &quot;const&quot;.&n; */
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
multiline_comment|/* For assembly routines */
DECL|macro|__INIT
mdefine_line|#define __INIT&t;&t;.section&t;&quot;.init.text&quot;,&quot;ax&quot;
DECL|macro|__FINIT
mdefine_line|#define __FINIT&t;&t;.previous
DECL|macro|__INITDATA
mdefine_line|#define __INITDATA&t;.section&t;&quot;.init.data&quot;,&quot;aw&quot;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Used for initialization calls..&n; */
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
r_extern
id|initcall_t
id|__con_initcall_start
(braket
)braket
comma
id|__con_initcall_end
(braket
)braket
suffix:semicolon
r_extern
id|initcall_t
id|__security_initcall_start
(braket
)braket
comma
id|__security_initcall_end
(braket
)braket
suffix:semicolon
multiline_comment|/* Defined in init/main.c */
r_extern
r_char
id|saved_command_line
(braket
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifndef MODULE
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* initcalls are now grouped by functionality into separate &n; * subsections. Ordering inside the subsections is determined&n; * by link order. &n; * For backwards compatibility, initcall() puts the call in &n; * the device init subsection.&n; */
DECL|macro|__define_initcall
mdefine_line|#define __define_initcall(level,fn) &bslash;&n;&t;static initcall_t __initcall_##fn __attribute_used__ &bslash;&n;&t;__attribute__((__section__(&quot;.initcall&quot; level &quot;.init&quot;))) = fn
DECL|macro|core_initcall
mdefine_line|#define core_initcall(fn)&t;&t;__define_initcall(&quot;1&quot;,fn)
DECL|macro|postcore_initcall
mdefine_line|#define postcore_initcall(fn)&t;&t;__define_initcall(&quot;2&quot;,fn)
DECL|macro|arch_initcall
mdefine_line|#define arch_initcall(fn)&t;&t;__define_initcall(&quot;3&quot;,fn)
DECL|macro|subsys_initcall
mdefine_line|#define subsys_initcall(fn)&t;&t;__define_initcall(&quot;4&quot;,fn)
DECL|macro|fs_initcall
mdefine_line|#define fs_initcall(fn)&t;&t;&t;__define_initcall(&quot;5&quot;,fn)
DECL|macro|device_initcall
mdefine_line|#define device_initcall(fn)&t;&t;__define_initcall(&quot;6&quot;,fn)
DECL|macro|late_initcall
mdefine_line|#define late_initcall(fn)&t;&t;__define_initcall(&quot;7&quot;,fn)
DECL|macro|__initcall
mdefine_line|#define __initcall(fn) device_initcall(fn)
DECL|macro|__exitcall
mdefine_line|#define __exitcall(fn) &bslash;&n;&t;static exitcall_t __exitcall_##fn __exit_call = fn
DECL|macro|console_initcall
mdefine_line|#define console_initcall(fn) &bslash;&n;&t;static initcall_t __initcall_##fn &bslash;&n;&t;__attribute_used__ __attribute__((__section__(&quot;.con_initcall.init&quot;)))=fn
DECL|macro|security_initcall
mdefine_line|#define security_initcall(fn) &bslash;&n;&t;static initcall_t __initcall_##fn &bslash;&n;&t;__attribute_used__ __attribute__((__section__(&quot;.security_initcall.init&quot;))) = fn
DECL|struct|obs_kernel_param
r_struct
id|obs_kernel_param
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
)paren
suffix:semicolon
DECL|member|early
r_int
id|early
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Only for really core code.  See moduleparam.h for the normal way.&n; *&n; * Force the alignment so the compiler doesn&squot;t space elements of the&n; * obs_kernel_param &quot;array&quot; too far apart in .init.setup.&n; */
DECL|macro|__setup_param
mdefine_line|#define __setup_param(str, unique_id, fn, early)&t;&t;&t;&bslash;&n;&t;static char __setup_str_##unique_id[] __initdata = str;&t;&bslash;&n;&t;static struct obs_kernel_param __setup_##unique_id&t;&bslash;&n;&t;&t;__attribute_used__&t;&t;&t;&t;&bslash;&n;&t;&t;__attribute__((__section__(&quot;.init.setup&quot;)))&t;&bslash;&n;&t;&t;__attribute__((aligned((sizeof(long)))))&t;&bslash;&n;&t;&t;= { __setup_str_##unique_id, fn, early }
DECL|macro|__setup_null_param
mdefine_line|#define __setup_null_param(str, unique_id)&t;&t;&t;&bslash;&n;&t;__setup_param(str, unique_id, NULL, 0)
DECL|macro|__setup
mdefine_line|#define __setup(str, fn)&t;&t;&t;&t;&t;&bslash;&n;&t;__setup_param(str, fn, fn, 0)
DECL|macro|__obsolete_setup
mdefine_line|#define __obsolete_setup(str)&t;&t;&t;&t;&t;&bslash;&n;&t;__setup_null_param(str, __LINE__)
multiline_comment|/* NOTE: fn is as per module_param, not __setup!  Emits warning if fn&n; * returns non-zero. */
DECL|macro|early_param
mdefine_line|#define early_param(str, fn)&t;&t;&t;&t;&t;&bslash;&n;&t;__setup_param(str, fn, fn, 1)
multiline_comment|/* Relies on saved_command_line being set */
r_void
id|__init
id|parse_early_param
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/**&n; * module_init() - driver initialization entry point&n; * @x: function to be run at kernel boot time or module insertion&n; * &n; * module_init() will either be called during do_initcalls (if&n; * builtin) or at module insertion time (if a module).  There can only&n; * be one per module.&n; */
DECL|macro|module_init
mdefine_line|#define module_init(x)&t;__initcall(x);
multiline_comment|/**&n; * module_exit() - driver exit entry point&n; * @x: function to be run when driver is removed&n; * &n; * module_exit() will wrap the driver clean-up code&n; * with cleanup_module() when used with rmmod when&n; * the driver is a module.  If the driver is statically&n; * compiled into the kernel, module_exit() has no effect.&n; * There can only be one per module.&n; */
DECL|macro|module_exit
mdefine_line|#define module_exit(x)&t;__exitcall(x);
macro_line|#else /* MODULE */
multiline_comment|/* Don&squot;t use these in modules, but some people do... */
DECL|macro|core_initcall
mdefine_line|#define core_initcall(fn)&t;&t;module_init(fn)
DECL|macro|postcore_initcall
mdefine_line|#define postcore_initcall(fn)&t;&t;module_init(fn)
DECL|macro|arch_initcall
mdefine_line|#define arch_initcall(fn)&t;&t;module_init(fn)
DECL|macro|subsys_initcall
mdefine_line|#define subsys_initcall(fn)&t;&t;module_init(fn)
DECL|macro|fs_initcall
mdefine_line|#define fs_initcall(fn)&t;&t;&t;module_init(fn)
DECL|macro|device_initcall
mdefine_line|#define device_initcall(fn)&t;&t;module_init(fn)
DECL|macro|late_initcall
mdefine_line|#define late_initcall(fn)&t;&t;module_init(fn)
DECL|macro|security_initcall
mdefine_line|#define security_initcall(fn)&t;&t;module_init(fn)
multiline_comment|/* These macros create a dummy inline: gcc 2.9x does not count alias&n; as usage, hence the `unused function&squot; warning when __init functions&n; are declared static. We use the dummy __*_module_inline functions&n; both to kill the warning and check the type of the init/cleanup&n; function. */
multiline_comment|/* Each module must use one module_init(), or one no_module_init */
DECL|macro|module_init
mdefine_line|#define module_init(initfn)&t;&t;&t;&t;&t;&bslash;&n;&t;static inline initcall_t __inittest(void)&t;&t;&bslash;&n;&t;{ return initfn; }&t;&t;&t;&t;&t;&bslash;&n;&t;int init_module(void) __attribute__((alias(#initfn)));
multiline_comment|/* This is only required if you want to be unloadable. */
DECL|macro|module_exit
mdefine_line|#define module_exit(exitfn)&t;&t;&t;&t;&t;&bslash;&n;&t;static inline exitcall_t __exittest(void)&t;&t;&bslash;&n;&t;{ return exitfn; }&t;&t;&t;&t;&t;&bslash;&n;&t;void cleanup_module(void) __attribute__((alias(#exitfn)));
DECL|macro|__setup_param
mdefine_line|#define __setup_param(str, unique_id, fn)&t;/* nothing */
DECL|macro|__setup_null_param
mdefine_line|#define __setup_null_param(str, unique_id) &t;/* nothing */
DECL|macro|__setup
mdefine_line|#define __setup(str, func) &t;&t;&t;/* nothing */
DECL|macro|__obsolete_setup
mdefine_line|#define __obsolete_setup(str) &t;&t;&t;/* nothing */
macro_line|#endif
multiline_comment|/* Data marked not to be saved by software_suspend() */
DECL|macro|__nosavedata
mdefine_line|#define __nosavedata __attribute__ ((__section__ (&quot;.data.nosave&quot;)))
multiline_comment|/* This means &quot;can be init if no module support, otherwise module load&n;   may call it.&quot; */
macro_line|#ifdef CONFIG_MODULES
DECL|macro|__init_or_module
mdefine_line|#define __init_or_module
DECL|macro|__initdata_or_module
mdefine_line|#define __initdata_or_module
macro_line|#else
DECL|macro|__init_or_module
mdefine_line|#define __init_or_module __init
DECL|macro|__initdata_or_module
mdefine_line|#define __initdata_or_module __initdata
macro_line|#endif /*CONFIG_MODULES*/
macro_line|#ifdef CONFIG_HOTPLUG
DECL|macro|__devinit
mdefine_line|#define __devinit
DECL|macro|__devinitdata
mdefine_line|#define __devinitdata
DECL|macro|__devexit
mdefine_line|#define __devexit
DECL|macro|__devexitdata
mdefine_line|#define __devexitdata
macro_line|#else
DECL|macro|__devinit
mdefine_line|#define __devinit __init
DECL|macro|__devinitdata
mdefine_line|#define __devinitdata __initdata
DECL|macro|__devexit
mdefine_line|#define __devexit __exit
DECL|macro|__devexitdata
mdefine_line|#define __devexitdata __exitdata
macro_line|#endif
multiline_comment|/* Functions marked as __devexit may be discarded at kernel link time, depending&n;   on config options.  Newer versions of binutils detect references from&n;   retained sections to discarded sections and flag an error.  Pointers to&n;   __devexit functions must use __devexit_p(function_name), the wrapper will&n;   insert either the function_name or NULL, depending on the config options.&n; */
macro_line|#if defined(MODULE) || defined(CONFIG_HOTPLUG)
DECL|macro|__devexit_p
mdefine_line|#define __devexit_p(x) x
macro_line|#else
DECL|macro|__devexit_p
mdefine_line|#define __devexit_p(x) NULL
macro_line|#endif
macro_line|#ifdef MODULE
DECL|macro|__exit_p
mdefine_line|#define __exit_p(x) x
macro_line|#else
DECL|macro|__exit_p
mdefine_line|#define __exit_p(x) NULL
macro_line|#endif
macro_line|#endif /* _LINUX_INIT_H */
eof
