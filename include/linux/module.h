macro_line|#ifndef _LINUX_MODULE_H
DECL|macro|_LINUX_MODULE_H
mdefine_line|#define _LINUX_MODULE_H
multiline_comment|/*&n; * Dynamic loading of modules into the kernel.&n; *&n; * Rewritten by Richard Henderson &lt;rth@tamu.edu&gt; Dec 1996&n; * Rewritten again by Rusty Russell, 2002&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/stringify.h&gt;
macro_line|#include &lt;asm/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt; /* For struct exception_table_entry */
multiline_comment|/* Not Yet Implemented */
DECL|macro|MODULE_LICENSE
mdefine_line|#define MODULE_LICENSE(name)
DECL|macro|MODULE_AUTHOR
mdefine_line|#define MODULE_AUTHOR(name)
DECL|macro|MODULE_DESCRIPTION
mdefine_line|#define MODULE_DESCRIPTION(desc)
DECL|macro|MODULE_SUPPORTED_DEVICE
mdefine_line|#define MODULE_SUPPORTED_DEVICE(name)
DECL|macro|MODULE_PARM_DESC
mdefine_line|#define MODULE_PARM_DESC(var,desc)
DECL|macro|print_modules
mdefine_line|#define print_modules()
multiline_comment|/* v850 toolchain uses a `_&squot; prefix for all user symbols */
macro_line|#ifndef MODULE_SYMBOL_PREFIX
DECL|macro|MODULE_SYMBOL_PREFIX
mdefine_line|#define MODULE_SYMBOL_PREFIX &quot;&quot;
macro_line|#endif
DECL|macro|MODULE_NAME_LEN
mdefine_line|#define MODULE_NAME_LEN (64 - sizeof(unsigned long))
DECL|struct|kernel_symbol
r_struct
id|kernel_symbol
(brace
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|MODULE_NAME_LEN
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef MODULE
macro_line|#ifdef KBUILD_MODNAME
DECL|variable|__module_name
r_static
r_const
r_char
id|__module_name
(braket
id|MODULE_NAME_LEN
)braket
id|__attribute__
c_func
(paren
(paren
id|section
c_func
(paren
l_string|&quot;.gnu.linkonce.modname&quot;
)paren
)paren
)paren
op_assign
"&bslash;"
id|__stringify
c_func
(paren
id|KBUILD_MODNAME
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* For replacement modutils, use an alias not a pointer. */
DECL|macro|MODULE_GENERIC_TABLE
mdefine_line|#define MODULE_GENERIC_TABLE(gtype,name)&t;&t;&t;&bslash;&n;static const unsigned long __module_##gtype##_size&t;&t;&bslash;&n;  __attribute__ ((unused)) = sizeof(struct gtype##_id);&t;&t;&bslash;&n;static const struct gtype##_id * __module_##gtype##_table&t;&bslash;&n;  __attribute__ ((unused)) = name;&t;&t;&t;&t;&bslash;&n;extern const struct gtype##_id __mod_##gtype##_table&t;&t;&bslash;&n;  __attribute__ ((unused, alias(__stringify(name))))
multiline_comment|/* This is magically filled in by the linker, but THIS_MODULE must be&n;   a constant so it works in initializers. */
r_extern
r_struct
id|module
id|__this_module
suffix:semicolon
DECL|macro|THIS_MODULE
mdefine_line|#define THIS_MODULE (&amp;__this_module)
macro_line|#else  /* !MODULE */
DECL|macro|MODULE_GENERIC_TABLE
mdefine_line|#define MODULE_GENERIC_TABLE(gtype,name)
DECL|macro|THIS_MODULE
mdefine_line|#define THIS_MODULE ((struct module *)0)
macro_line|#endif
DECL|macro|MODULE_DEVICE_TABLE
mdefine_line|#define MODULE_DEVICE_TABLE(type,name)&t;&t;&bslash;&n;  MODULE_GENERIC_TABLE(type##_device,name)
DECL|struct|kernel_symbol_group
r_struct
id|kernel_symbol_group
(brace
multiline_comment|/* Links us into the global symbol list */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* Module which owns it (if any) */
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|num_syms
r_int
r_int
id|num_syms
suffix:semicolon
DECL|member|syms
r_const
r_struct
id|kernel_symbol
op_star
id|syms
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|exception_table
r_struct
id|exception_table
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|num_entries
r_int
r_int
id|num_entries
suffix:semicolon
DECL|member|entry
r_const
r_struct
id|exception_table_entry
op_star
id|entry
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_MODULES
multiline_comment|/* Get/put a kernel symbol (calls must be symmetric) */
r_void
op_star
id|__symbol_get
c_func
(paren
r_const
r_char
op_star
id|symbol
)paren
suffix:semicolon
r_void
op_star
id|__symbol_get_gpl
c_func
(paren
r_const
r_char
op_star
id|symbol
)paren
suffix:semicolon
DECL|macro|symbol_get
mdefine_line|#define symbol_get(x) ((typeof(&amp;x))(__symbol_get(MODULE_SYMBOL_PREFIX #x)))
multiline_comment|/* For every exported symbol, place a struct in the __ksymtab section */
DECL|macro|EXPORT_SYMBOL
mdefine_line|#define EXPORT_SYMBOL(sym)&t;&t;&t;&t;&bslash;&n;&t;const struct kernel_symbol __ksymtab_##sym&t;&bslash;&n;&t;__attribute__((section(&quot;__ksymtab&quot;)))&t;&t;&bslash;&n;&t;= { (unsigned long)&amp;sym, MODULE_SYMBOL_PREFIX #sym }
DECL|macro|EXPORT_SYMBOL_NOVERS
mdefine_line|#define EXPORT_SYMBOL_NOVERS(sym) EXPORT_SYMBOL(sym)
DECL|macro|EXPORT_SYMBOL_GPL
mdefine_line|#define EXPORT_SYMBOL_GPL(sym) EXPORT_SYMBOL(sym)
DECL|struct|module_ref
r_struct
id|module_ref
(brace
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|variable|____cacheline_aligned
)brace
id|____cacheline_aligned
suffix:semicolon
DECL|enum|module_state
r_enum
id|module_state
(brace
DECL|enumerator|MODULE_STATE_LIVE
id|MODULE_STATE_LIVE
comma
DECL|enumerator|MODULE_STATE_COMING
id|MODULE_STATE_COMING
comma
DECL|enumerator|MODULE_STATE_GOING
id|MODULE_STATE_GOING
comma
)brace
suffix:semicolon
DECL|struct|module
r_struct
id|module
(brace
DECL|member|state
r_enum
id|module_state
id|state
suffix:semicolon
multiline_comment|/* Member of list of modules */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* Unique handle for this module */
DECL|member|name
r_char
id|name
(braket
id|MODULE_NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* Exported symbols */
DECL|member|symbols
r_struct
id|kernel_symbol_group
id|symbols
suffix:semicolon
multiline_comment|/* Exception tables */
DECL|member|extable
r_struct
id|exception_table
id|extable
suffix:semicolon
multiline_comment|/* Startup function. */
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* If this is non-NULL, vfree after init() returns */
DECL|member|module_init
r_void
op_star
id|module_init
suffix:semicolon
multiline_comment|/* Here is the actual code + data, vfree&squot;d on unload. */
DECL|member|module_core
r_void
op_star
id|module_core
suffix:semicolon
multiline_comment|/* Here are the sizes of the init and core sections */
DECL|member|init_size
DECL|member|core_size
r_int
r_int
id|init_size
comma
id|core_size
suffix:semicolon
multiline_comment|/* Arch-specific module values */
DECL|member|arch
r_struct
id|mod_arch_specific
id|arch
suffix:semicolon
multiline_comment|/* Am I unsafe to unload? */
DECL|member|unsafe
r_int
id|unsafe
suffix:semicolon
macro_line|#ifdef CONFIG_MODULE_UNLOAD
multiline_comment|/* Reference counts */
DECL|member|ref
r_struct
id|module_ref
id|ref
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/* What modules depend on me? */
DECL|member|modules_which_use_me
r_struct
id|list_head
id|modules_which_use_me
suffix:semicolon
multiline_comment|/* Who is waiting for us to be unloaded */
DECL|member|waiter
r_struct
id|task_struct
op_star
id|waiter
suffix:semicolon
multiline_comment|/* Destruction function. */
DECL|member|exit
r_void
(paren
op_star
m_exit
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_KALLSYMS
multiline_comment|/* We keep the symbol and string tables for kallsyms. */
DECL|member|symtab
id|Elf_Sym
op_star
id|symtab
suffix:semicolon
DECL|member|num_syms
r_int
r_int
id|num_syms
suffix:semicolon
DECL|member|strtab
r_char
op_star
id|strtab
suffix:semicolon
macro_line|#endif
multiline_comment|/* The command line arguments (may be mangled).  People like&n;&t;   keeping pointers to this stuff */
DECL|member|args
r_char
id|args
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* FIXME: It&squot;d be nice to isolate modules during init, too, so they&n;   aren&squot;t used before they (may) fail.  But presently too much code&n;   (IDE &amp; SCSI) require entry into the module during init.*/
DECL|function|module_is_live
r_static
r_inline
r_int
id|module_is_live
c_func
(paren
r_struct
id|module
op_star
id|mod
)paren
(brace
r_return
id|mod-&gt;state
op_ne
id|MODULE_STATE_GOING
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MODULE_UNLOAD
r_void
id|__symbol_put
c_func
(paren
r_const
r_char
op_star
id|symbol
)paren
suffix:semicolon
DECL|macro|symbol_put
mdefine_line|#define symbol_put(x) __symbol_put(MODULE_SYMBOL_PREFIX #x)
r_void
id|symbol_put_addr
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
multiline_comment|/* We only need protection against local interrupts. */
macro_line|#ifndef __HAVE_ARCH_LOCAL_INC
DECL|macro|local_inc
mdefine_line|#define local_inc(x) atomic_inc(x)
DECL|macro|local_dec
mdefine_line|#define local_dec(x) atomic_dec(x)
macro_line|#endif
DECL|function|try_module_get
r_static
r_inline
r_int
id|try_module_get
c_func
(paren
r_struct
id|module
op_star
id|module
)paren
(brace
r_int
id|ret
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|module
)paren
(brace
r_int
r_int
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|module_is_live
c_func
(paren
id|module
)paren
)paren
)paren
id|local_inc
c_func
(paren
op_amp
id|module-&gt;ref
(braket
id|cpu
)braket
dot
id|count
)paren
suffix:semicolon
r_else
id|ret
op_assign
l_int|0
suffix:semicolon
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|module_put
r_static
r_inline
r_void
id|module_put
c_func
(paren
r_struct
id|module
op_star
id|module
)paren
(brace
r_if
c_cond
(paren
id|module
)paren
(brace
r_int
r_int
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
id|local_dec
c_func
(paren
op_amp
id|module-&gt;ref
(braket
id|cpu
)braket
dot
id|count
)paren
suffix:semicolon
multiline_comment|/* Maybe they&squot;re waiting for us to drop reference? */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|module_is_live
c_func
(paren
id|module
)paren
)paren
)paren
id|wake_up_process
c_func
(paren
id|module-&gt;waiter
)paren
suffix:semicolon
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#else /*!CONFIG_MODULE_UNLOAD*/
DECL|function|try_module_get
r_static
r_inline
r_int
id|try_module_get
c_func
(paren
r_struct
id|module
op_star
id|module
)paren
(brace
r_return
op_logical_neg
id|module
op_logical_or
id|module_is_live
c_func
(paren
id|module
)paren
suffix:semicolon
)brace
DECL|function|module_put
r_static
r_inline
r_void
id|module_put
c_func
(paren
r_struct
id|module
op_star
id|module
)paren
(brace
)brace
DECL|macro|symbol_put
mdefine_line|#define symbol_put(x) do { } while(0)
DECL|macro|symbol_put_addr
mdefine_line|#define symbol_put_addr(p) do { } while(0)
macro_line|#endif /* CONFIG_MODULE_UNLOAD */
multiline_comment|/* This is a #define so the string doesn&squot;t get put in every .o file */
DECL|macro|module_name
mdefine_line|#define module_name(mod)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct module *__mod = (mod);&t;&t;&bslash;&n;&t;__mod ? __mod-&gt;name : &quot;kernel&quot;;&t;&t;&bslash;&n;})
DECL|macro|__unsafe
mdefine_line|#define __unsafe(mod)&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;if (mod &amp;&amp; !(mod)-&gt;unsafe) {&t;&t;&t;&t;&t;     &bslash;&n;&t;&t;printk(KERN_WARNING&t;&t;&t;&t;&t;     &bslash;&n;&t;&t;       &quot;Module %s cannot be unloaded due to unsafe usage in&quot; &bslash;&n;&t;&t;       &quot; %s:%u&bslash;n&quot;, (mod)-&gt;name, __FILE__, __LINE__);&t;     &bslash;&n;&t;&t;(mod)-&gt;unsafe = 1;&t;&t;&t;&t;&t;     &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;} while(0)
multiline_comment|/* For kallsyms to ask for address resolution.  NULL means not found. */
r_const
r_char
op_star
id|module_address_lookup
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
op_star
id|symbolsize
comma
r_int
r_int
op_star
id|offset
comma
r_char
op_star
op_star
id|modname
)paren
suffix:semicolon
macro_line|#else /* !CONFIG_MODULES... */
DECL|macro|EXPORT_SYMBOL
mdefine_line|#define EXPORT_SYMBOL(sym)
DECL|macro|EXPORT_SYMBOL_GPL
mdefine_line|#define EXPORT_SYMBOL_GPL(sym)
DECL|macro|EXPORT_SYMBOL_NOVERS
mdefine_line|#define EXPORT_SYMBOL_NOVERS(sym)
multiline_comment|/* Get/put a kernel symbol (calls should be symmetric) */
DECL|macro|symbol_get
mdefine_line|#define symbol_get(x) (&amp;(x))
DECL|macro|symbol_put
mdefine_line|#define symbol_put(x) do { } while(0)
DECL|macro|symbol_put_addr
mdefine_line|#define symbol_put_addr(x) do { } while(0)
DECL|macro|try_module_get
mdefine_line|#define try_module_get(module) 1
DECL|macro|module_put
mdefine_line|#define module_put(module) do { } while(0)
DECL|macro|module_name
mdefine_line|#define module_name(mod) &quot;kernel&quot;
DECL|macro|__unsafe
mdefine_line|#define __unsafe(mod)
multiline_comment|/* For kallsyms to ask for address resolution.  NULL means not found. */
DECL|function|module_address_lookup
r_static
r_inline
r_const
r_char
op_star
id|module_address_lookup
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
op_star
id|symbolsize
comma
r_int
r_int
op_star
id|offset
comma
r_char
op_star
op_star
id|modname
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_MODULES */
multiline_comment|/* For archs to search exception tables */
r_extern
r_struct
id|list_head
id|extables
suffix:semicolon
r_extern
id|spinlock_t
id|modlist_lock
suffix:semicolon
DECL|macro|symbol_request
mdefine_line|#define symbol_request(x) try_then_request_module(symbol_get(x), &quot;symbol:&quot; #x)
multiline_comment|/* BELOW HERE ALL THESE ARE OBSOLETE AND WILL VANISH */
DECL|macro|__MOD_INC_USE_COUNT
mdefine_line|#define __MOD_INC_USE_COUNT(mod) &bslash;&n;&t;do { __unsafe(mod); (void)try_module_get(mod); } while(0)
DECL|macro|__MOD_DEC_USE_COUNT
mdefine_line|#define __MOD_DEC_USE_COUNT(mod) module_put(mod)
DECL|macro|SET_MODULE_OWNER
mdefine_line|#define SET_MODULE_OWNER(dev) ((dev)-&gt;owner = THIS_MODULE)
DECL|struct|obsolete_modparm
r_struct
id|obsolete_modparm
(brace
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|type
r_char
id|type
(braket
l_int|64
op_minus
r_sizeof
(paren
r_void
op_star
)paren
)braket
suffix:semicolon
DECL|member|addr
r_void
op_star
id|addr
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef MODULE
multiline_comment|/* DEPRECATED: Do not use. */
DECL|macro|MODULE_PARM
mdefine_line|#define MODULE_PARM(var,type)&t;&t;&t;&t;&t;&t;    &bslash;&n;struct obsolete_modparm __parm_##var __attribute__((section(&quot;__obsparm&quot;))) = &bslash;&n;{ __stringify(var), type };
macro_line|#else
DECL|macro|MODULE_PARM
mdefine_line|#define MODULE_PARM(var,type)
macro_line|#endif
multiline_comment|/* People do this inside their init routines, when the module isn&squot;t&n;   &quot;live&quot; yet.  They should no longer be doing that, but&n;   meanwhile... */
macro_line|#if defined(CONFIG_MODULE_UNLOAD) &amp;&amp; defined(MODULE)
DECL|macro|MOD_INC_USE_COUNT
mdefine_line|#define MOD_INC_USE_COUNT&t;&bslash;&n;&t;do { __unsafe(THIS_MODULE); local_inc(&amp;THIS_MODULE-&gt;ref[get_cpu()].count); put_cpu(); } while (0)
macro_line|#else
DECL|macro|MOD_INC_USE_COUNT
mdefine_line|#define MOD_INC_USE_COUNT &bslash;&n;&t;do { __unsafe(THIS_MODULE); (void)try_module_get(THIS_MODULE); } while (0)
macro_line|#endif
DECL|macro|MOD_DEC_USE_COUNT
mdefine_line|#define MOD_DEC_USE_COUNT module_put(THIS_MODULE)
DECL|macro|try_inc_mod_count
mdefine_line|#define try_inc_mod_count(mod) try_module_get(mod)
DECL|macro|EXPORT_NO_SYMBOLS
mdefine_line|#define EXPORT_NO_SYMBOLS
r_extern
r_int
id|module_dummy_usage
suffix:semicolon
DECL|macro|GET_USE_COUNT
mdefine_line|#define GET_USE_COUNT(module) (module_dummy_usage)
DECL|macro|MOD_IN_USE
mdefine_line|#define MOD_IN_USE 0
DECL|macro|__MODULE_STRING
mdefine_line|#define __MODULE_STRING(x) __stringify(x)
DECL|macro|__mod_between
mdefine_line|#define __mod_between(a_start, a_len, b_start, b_len)&t;&t;&bslash;&n;(((a_start) &gt;= (b_start) &amp;&amp; (a_start) &lt;= (b_start)+(b_len))&t;&bslash;&n; || ((a_start)+(a_len) &gt;= (b_start)&t;&t;&t;&t;&bslash;&n;     &amp;&amp; (a_start)+(a_len) &lt;= (b_start)+(b_len)))
DECL|macro|mod_bound
mdefine_line|#define mod_bound(p, n, m)&t;&t;&t;&t;&t;&bslash;&n;(((m)-&gt;module_init&t;&t;&t;&t;&t;&t;&bslash;&n;  &amp;&amp; __mod_between((p),(n),(m)-&gt;module_init,(m)-&gt;init_size))&t;&bslash;&n; || __mod_between((p),(n),(m)-&gt;module_core,(m)-&gt;core_size))
multiline_comment|/* Old-style &quot;I&squot;ll just call it init_module and it&squot;ll be run at&n;   insert&quot;.  Use module_init(myroutine) instead. */
macro_line|#ifdef MODULE
DECL|macro|init_module
mdefine_line|#define init_module(voidarg) __initfn(void)
DECL|macro|cleanup_module
mdefine_line|#define cleanup_module(voidarg) __exitfn(void)
macro_line|#endif
multiline_comment|/*&n; * The exception and symbol tables, and the lock&n; * to protect them.&n; */
r_extern
id|spinlock_t
id|modlist_lock
suffix:semicolon
r_extern
r_struct
id|list_head
id|extables
suffix:semicolon
r_extern
r_struct
id|list_head
id|symbols
suffix:semicolon
multiline_comment|/* Use symbol_get and symbol_put instead.  You&squot;ll thank me. */
DECL|macro|HAVE_INTER_MODULE
mdefine_line|#define HAVE_INTER_MODULE
r_extern
r_void
id|inter_module_register
c_func
(paren
r_const
r_char
op_star
comma
r_struct
id|module
op_star
comma
r_const
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|inter_module_unregister
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_const
r_void
op_star
id|inter_module_get
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_const
r_void
op_star
id|inter_module_get_request
c_func
(paren
r_const
r_char
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|inter_module_put
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_MODULE_H */
eof
