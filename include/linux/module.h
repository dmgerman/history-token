multiline_comment|/*&n; * Dynamic loading of modules into the kernel.&n; *&n; * Rewritten by Richard Henderson &lt;rth@tamu.edu&gt; Dec 1996&n; */
macro_line|#ifndef _LINUX_MODULE_H
DECL|macro|_LINUX_MODULE_H
mdefine_line|#define _LINUX_MODULE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/* Don&squot;t need to bring in all of uaccess.h just for this decl.  */
r_struct
id|exception_table_entry
suffix:semicolon
multiline_comment|/* Used by get_kernel_syms, which is obsolete.  */
DECL|struct|kernel_sym
r_struct
id|kernel_sym
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
l_int|60
)braket
suffix:semicolon
multiline_comment|/* should have been 64-sizeof(long); oh well */
)brace
suffix:semicolon
DECL|struct|module_symbol
r_struct
id|module_symbol
(brace
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|module_ref
r_struct
id|module_ref
(brace
DECL|member|dep
r_struct
id|module
op_star
id|dep
suffix:semicolon
multiline_comment|/* &quot;parent&quot; pointer */
DECL|member|ref
r_struct
id|module
op_star
id|ref
suffix:semicolon
multiline_comment|/* &quot;child&quot; pointer */
DECL|member|next_ref
r_struct
id|module_ref
op_star
id|next_ref
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* TBD */
r_struct
id|module_persist
suffix:semicolon
DECL|struct|module
r_struct
id|module
(brace
DECL|member|size_of_struct
r_int
r_int
id|size_of_struct
suffix:semicolon
multiline_comment|/* == sizeof(module) */
DECL|member|next
r_struct
id|module
op_star
id|next
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
r_union
(brace
DECL|member|usecount
id|atomic_t
id|usecount
suffix:semicolon
DECL|member|pad
r_int
id|pad
suffix:semicolon
DECL|member|uc
)brace
id|uc
suffix:semicolon
multiline_comment|/* Needs to keep its size - so says rth */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* AUTOCLEAN et al */
DECL|member|nsyms
r_int
id|nsyms
suffix:semicolon
DECL|member|ndeps
r_int
id|ndeps
suffix:semicolon
DECL|member|syms
r_struct
id|module_symbol
op_star
id|syms
suffix:semicolon
DECL|member|deps
r_struct
id|module_ref
op_star
id|deps
suffix:semicolon
DECL|member|refs
r_struct
id|module_ref
op_star
id|refs
suffix:semicolon
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
DECL|member|cleanup
r_void
(paren
op_star
id|cleanup
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|ex_table_start
r_const
r_struct
id|exception_table_entry
op_star
id|ex_table_start
suffix:semicolon
DECL|member|ex_table_end
r_const
r_struct
id|exception_table_entry
op_star
id|ex_table_end
suffix:semicolon
macro_line|#ifdef __alpha__
DECL|member|gp
r_int
r_int
id|gp
suffix:semicolon
macro_line|#endif
multiline_comment|/* Members past this point are extensions to the basic&n;&t;   module support and are optional.  Use mod_member_present()&n;&t;   to examine them.  */
DECL|member|persist_start
r_const
r_struct
id|module_persist
op_star
id|persist_start
suffix:semicolon
DECL|member|persist_end
r_const
r_struct
id|module_persist
op_star
id|persist_end
suffix:semicolon
DECL|member|can_unload
r_int
(paren
op_star
id|can_unload
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|runsize
r_int
id|runsize
suffix:semicolon
multiline_comment|/* In modutils, not currently used */
DECL|member|kallsyms_start
r_const
r_char
op_star
id|kallsyms_start
suffix:semicolon
multiline_comment|/* All symbols for kernel debugging */
DECL|member|kallsyms_end
r_const
r_char
op_star
id|kallsyms_end
suffix:semicolon
DECL|member|archdata_start
r_const
r_char
op_star
id|archdata_start
suffix:semicolon
multiline_comment|/* arch specific data for module */
DECL|member|archdata_end
r_const
r_char
op_star
id|archdata_end
suffix:semicolon
DECL|member|kernel_data
r_const
r_char
op_star
id|kernel_data
suffix:semicolon
multiline_comment|/* Reserved for kernel internal use */
)brace
suffix:semicolon
DECL|struct|module_info
r_struct
id|module_info
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|usecount
r_int
id|usecount
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Bits of module.flags.  */
DECL|macro|MOD_UNINITIALIZED
mdefine_line|#define MOD_UNINITIALIZED&t;0
DECL|macro|MOD_RUNNING
mdefine_line|#define MOD_RUNNING&t;&t;1
DECL|macro|MOD_DELETED
mdefine_line|#define MOD_DELETED&t;&t;2
DECL|macro|MOD_AUTOCLEAN
mdefine_line|#define MOD_AUTOCLEAN&t;&t;4
DECL|macro|MOD_VISITED
mdefine_line|#define MOD_VISITED  &t;&t;8
DECL|macro|MOD_USED_ONCE
mdefine_line|#define MOD_USED_ONCE&t;&t;16
DECL|macro|MOD_JUST_FREED
mdefine_line|#define MOD_JUST_FREED&t;&t;32
DECL|macro|MOD_INITIALIZING
mdefine_line|#define MOD_INITIALIZING&t;64
multiline_comment|/* Values for query_module&squot;s which.  */
DECL|macro|QM_MODULES
mdefine_line|#define QM_MODULES&t;1
DECL|macro|QM_DEPS
mdefine_line|#define QM_DEPS&t;&t;2
DECL|macro|QM_REFS
mdefine_line|#define QM_REFS&t;&t;3
DECL|macro|QM_SYMBOLS
mdefine_line|#define QM_SYMBOLS&t;4
DECL|macro|QM_INFO
mdefine_line|#define QM_INFO&t;&t;5
multiline_comment|/* Can the module be queried? */
DECL|macro|MOD_CAN_QUERY
mdefine_line|#define MOD_CAN_QUERY(mod) (((mod)-&gt;flags &amp; (MOD_RUNNING | MOD_INITIALIZING)) &amp;&amp; !((mod)-&gt;flags &amp; MOD_DELETED))
multiline_comment|/* When struct module is extended, we must test whether the new member&n;   is present in the header received from insmod before we can use it.  &n;   This function returns true if the member is present.  */
DECL|macro|mod_member_present
mdefine_line|#define mod_member_present(mod,member) &t;&t;&t;&t;&t;&bslash;&n;&t;((unsigned long)(&amp;((struct module *)0L)-&gt;member + 1)&t;&t;&bslash;&n;&t; &lt;= (mod)-&gt;size_of_struct)
multiline_comment|/*&n; * Ditto for archdata.  Assumes mod-&gt;archdata_start and mod-&gt;archdata_end&n; * are validated elsewhere.&n; */
DECL|macro|mod_archdata_member_present
mdefine_line|#define mod_archdata_member_present(mod, type, member)&t;&t;&t;&bslash;&n;&t;(((unsigned long)(&amp;((type *)0L)-&gt;member) +&t;&t;&t;&bslash;&n;&t;  sizeof(((type *)0L)-&gt;member)) &lt;=&t;&t;&t;&t;&bslash;&n;&t; ((mod)-&gt;archdata_end - (mod)-&gt;archdata_start))
multiline_comment|/* Check if an address p with number of entries n is within the body of module m */
DECL|macro|mod_bound
mdefine_line|#define mod_bound(p, n, m) ((unsigned long)(p) &gt;= ((unsigned long)(m) + ((m)-&gt;size_of_struct)) &amp;&amp; &bslash;&n;&t;         (unsigned long)((p)+(n)) &lt;= (unsigned long)(m) + (m)-&gt;size)
multiline_comment|/* Backwards compatibility definition.  */
DECL|macro|GET_USE_COUNT
mdefine_line|#define GET_USE_COUNT(module)&t;(atomic_read(&amp;(module)-&gt;uc.usecount))
multiline_comment|/* Poke the use count of a module.  */
DECL|macro|__MOD_INC_USE_COUNT
mdefine_line|#define __MOD_INC_USE_COUNT(mod)&t;&t;&t;&t;&t;&bslash;&n;&t;(atomic_inc(&amp;(mod)-&gt;uc.usecount), (mod)-&gt;flags |= MOD_VISITED|MOD_USED_ONCE)
DECL|macro|__MOD_DEC_USE_COUNT
mdefine_line|#define __MOD_DEC_USE_COUNT(mod)&t;&t;&t;&t;&t;&bslash;&n;&t;(atomic_dec(&amp;(mod)-&gt;uc.usecount), (mod)-&gt;flags |= MOD_VISITED)
DECL|macro|__MOD_IN_USE
mdefine_line|#define __MOD_IN_USE(mod)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(mod_member_present((mod), can_unload) &amp;&amp; (mod)-&gt;can_unload&t;&bslash;&n;&t; ? (mod)-&gt;can_unload() : atomic_read(&amp;(mod)-&gt;uc.usecount))
multiline_comment|/* Indirect stringification.  */
DECL|macro|__MODULE_STRING_1
mdefine_line|#define __MODULE_STRING_1(x)&t;#x
DECL|macro|__MODULE_STRING
mdefine_line|#define __MODULE_STRING(x)&t;__MODULE_STRING_1(x)
multiline_comment|/* Generic inter module communication.&n; *&n; * NOTE: This interface is intended for small amounts of data that are&n; *       passed between two objects and either or both of the objects&n; *       might be compiled as modules.  Do not over use this interface.&n; *&n; *       If more than two objects need to communicate then you probably&n; *       need a specific interface instead of abusing this generic&n; *       interface.  If both objects are *always* built into the kernel&n; *       then a global extern variable is good enough, you do not need&n; *       this interface.&n; *&n; * Keith Owens &lt;kaos@ocs.com.au&gt; 28 Oct 2000.&n; */
macro_line|#ifdef __KERNEL__
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
DECL|struct|inter_module_entry
r_struct
id|inter_module_entry
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|im_name
r_const
r_char
op_star
id|im_name
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|userdata
r_const
r_void
op_star
id|userdata
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|try_inc_mod_count
c_func
(paren
r_struct
id|module
op_star
id|mod
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#if defined(MODULE) &amp;&amp; !defined(__GENKSYMS__)
multiline_comment|/* Embedded module documentation macros.  */
multiline_comment|/* For documentation purposes only.  */
DECL|macro|MODULE_AUTHOR
mdefine_line|#define MODULE_AUTHOR(name)&t;&t;&t;&t;&t;&t;   &bslash;&n;const char __module_author[] __attribute__((section(&quot;.modinfo&quot;))) = &t;   &bslash;&n;&quot;author=&quot; name
DECL|macro|MODULE_DESCRIPTION
mdefine_line|#define MODULE_DESCRIPTION(desc)&t;&t;&t;&t;&t;   &bslash;&n;const char __module_description[] __attribute__((section(&quot;.modinfo&quot;))) =   &bslash;&n;&quot;description=&quot; desc
multiline_comment|/* Could potentially be used by kmod...  */
DECL|macro|MODULE_SUPPORTED_DEVICE
mdefine_line|#define MODULE_SUPPORTED_DEVICE(dev)&t;&t;&t;&t;&t;   &bslash;&n;const char __module_device[] __attribute__((section(&quot;.modinfo&quot;))) = &t;   &bslash;&n;&quot;device=&quot; dev
multiline_comment|/* Used to verify parameters given to the module.  The TYPE arg should&n;   be a string in the following format:&n;   &t;[min[-max]]{b,h,i,l,s}&n;   The MIN and MAX specifiers delimit the length of the array.  If MAX&n;   is omitted, it defaults to MIN; if both are omitted, the default is 1.&n;   The final character is a type specifier:&n;&t;b&t;byte&n;&t;h&t;short&n;&t;i&t;int&n;&t;l&t;long&n;&t;s&t;string&n;*/
DECL|macro|MODULE_PARM
mdefine_line|#define MODULE_PARM(var,type)&t;&t;&t;&bslash;&n;const char __module_parm_##var[]&t;&t;&bslash;&n;__attribute__((section(&quot;.modinfo&quot;))) =&t;&t;&bslash;&n;&quot;parm_&quot; __MODULE_STRING(var) &quot;=&quot; type
DECL|macro|MODULE_PARM_DESC
mdefine_line|#define MODULE_PARM_DESC(var,desc)&t;&t;&bslash;&n;const char __module_parm_desc_##var[]&t;&t;&bslash;&n;__attribute__((section(&quot;.modinfo&quot;))) =&t;&t;&bslash;&n;&quot;parm_desc_&quot; __MODULE_STRING(var) &quot;=&quot; desc
multiline_comment|/*&n; * MODULE_DEVICE_TABLE exports information about devices&n; * currently supported by this module.  A device type, such as PCI,&n; * is a C-like identifier passed as the first arg to this macro.&n; * The second macro arg is the variable containing the device&n; * information being made public.&n; *&n; * The following is a list of known device types (arg 1),&n; * and the C types which are to be passed as arg 2.&n; * pci - struct pci_device_id - List of PCI ids supported by this module&n; * isapnp - struct isapnp_device_id - List of ISA PnP ids supported by this module&n; * usb - struct usb_device_id - List of USB ids supported by this module&n; */
DECL|macro|MODULE_GENERIC_TABLE
mdefine_line|#define MODULE_GENERIC_TABLE(gtype,name)&t;&bslash;&n;static const unsigned long __module_##gtype##_size &bslash;&n;  __attribute__ ((unused)) = sizeof(struct gtype##_id); &bslash;&n;static const struct gtype##_id * __module_##gtype##_table &bslash;&n;  __attribute__ ((unused)) = name
multiline_comment|/*&n; * The following license idents are currently accepted as indicating free&n; * software modules&n; *&n; *&t;&quot;GPL&quot;&t;&t;&t;&t;[GNU Public License v2 or later]&n; *&t;&quot;GPL v2&quot;&t;&t;&t;[GNU Public License v2]&n; *&t;&quot;GPL and additional rights&quot;&t;[GNU Public License v2 rights and more]&n; *&t;&quot;Dual BSD/GPL&quot;&t;&t;&t;[GNU Public License v2 or BSD license choice]&n; *&t;&quot;Dual MPL/GPL&quot;&t;&t;&t;[GNU Public License v2 or Mozilla license choice]&n; *&n; * The following other idents are available&n; *&n; *&t;&quot;Proprietary&quot;&t;&t;&t;[Non free products]&n; *&n; * There are dual licensed components, but when running with Linux it is the&n; * GPL that is relevant so this is a non issue. Similarly LGPL linked with GPL&n; * is a GPL combined work.&n; *&n; * This exists for several reasons&n; * 1.&t;So modinfo can show license info for users wanting to vet their setup &n; *&t;is free&n; * 2.&t;So the community can ignore bug reports including proprietary modules&n; * 3.&t;So vendors can do likewise based on their own policies&n; */
DECL|macro|MODULE_LICENSE
mdefine_line|#define MODULE_LICENSE(license) &t;&bslash;&n;static const char __module_license[]&t;&bslash;&n;  __attribute__((section(&quot;.modinfo&quot;), unused)) = &quot;license=&quot; license
multiline_comment|/* Define the module variable, and usage macros.  */
r_extern
r_struct
id|module
id|__this_module
suffix:semicolon
DECL|macro|THIS_MODULE
mdefine_line|#define THIS_MODULE&t;&t;(&amp;__this_module)
DECL|macro|MOD_INC_USE_COUNT
mdefine_line|#define MOD_INC_USE_COUNT&t;__MOD_INC_USE_COUNT(THIS_MODULE)
DECL|macro|MOD_DEC_USE_COUNT
mdefine_line|#define MOD_DEC_USE_COUNT&t;__MOD_DEC_USE_COUNT(THIS_MODULE)
DECL|macro|MOD_IN_USE
mdefine_line|#define MOD_IN_USE&t;&t;__MOD_IN_USE(THIS_MODULE)
macro_line|#include &lt;linux/version.h&gt;
DECL|variable|__module_kernel_version
r_static
r_const
r_char
id|__module_kernel_version
(braket
)braket
id|__attribute__
c_func
(paren
(paren
id|section
c_func
(paren
l_string|&quot;.modinfo&quot;
)paren
comma
id|unused
)paren
)paren
op_assign
l_string|&quot;kernel_version=&quot;
id|UTS_RELEASE
suffix:semicolon
macro_line|#ifdef CONFIG_MODVERSIONS
DECL|variable|__module_using_checksums
r_static
r_const
r_char
id|__module_using_checksums
(braket
)braket
id|__attribute__
c_func
(paren
(paren
id|section
c_func
(paren
l_string|&quot;.modinfo&quot;
)paren
comma
id|unused
)paren
)paren
op_assign
l_string|&quot;using_checksums=1&quot;
suffix:semicolon
macro_line|#endif
macro_line|#else /* MODULE */
DECL|macro|MODULE_AUTHOR
mdefine_line|#define MODULE_AUTHOR(name)
DECL|macro|MODULE_LICENSE
mdefine_line|#define MODULE_LICENSE(license)
DECL|macro|MODULE_DESCRIPTION
mdefine_line|#define MODULE_DESCRIPTION(desc)
DECL|macro|MODULE_SUPPORTED_DEVICE
mdefine_line|#define MODULE_SUPPORTED_DEVICE(name)
DECL|macro|MODULE_PARM
mdefine_line|#define MODULE_PARM(var,type)
DECL|macro|MODULE_PARM_DESC
mdefine_line|#define MODULE_PARM_DESC(var,desc)
multiline_comment|/* Create a dummy reference to the table to suppress gcc unused warnings.  Put&n; * the reference in the .data.exit section which is discarded when code is built&n; * in, so the reference does not bloat the running kernel.  Note: cannot be&n; * const, other exit data may be writable.&n; */
DECL|macro|MODULE_GENERIC_TABLE
mdefine_line|#define MODULE_GENERIC_TABLE(gtype,name) &bslash;&n;static const struct gtype##_id * __module_##gtype##_table &bslash;&n;  __attribute__ ((unused, __section__(&quot;.data.exit&quot;))) = name
macro_line|#ifndef __GENKSYMS__
DECL|macro|THIS_MODULE
mdefine_line|#define THIS_MODULE&t;&t;NULL
DECL|macro|MOD_INC_USE_COUNT
mdefine_line|#define MOD_INC_USE_COUNT&t;do { } while (0)
DECL|macro|MOD_DEC_USE_COUNT
mdefine_line|#define MOD_DEC_USE_COUNT&t;do { } while (0)
DECL|macro|MOD_IN_USE
mdefine_line|#define MOD_IN_USE&t;&t;1
macro_line|#endif /* !__GENKSYMS__ */
macro_line|#endif /* MODULE */
DECL|macro|MODULE_DEVICE_TABLE
mdefine_line|#define MODULE_DEVICE_TABLE(type,name)&t;&t;&bslash;&n;  MODULE_GENERIC_TABLE(type##_device,name)
multiline_comment|/* Export a symbol either from the kernel or a module.&n;&n;   In the kernel, the symbol is added to the kernel&squot;s global symbol table.&n;&n;   In a module, it controls which variables are exported.  If no&n;   variables are explicitly exported, the action is controled by the&n;   insmod -[xX] flags.  Otherwise, only the variables listed are exported.&n;   This obviates the need for the old register_symtab() function.  */
multiline_comment|/* So how does the CONFIG_MODVERSIONS magic work? &n; *&n; * A module can only be loaded if it&squot;s undefined symbols can be resolved&n; * using symbols the kernel exports for that purpose. The idea behind&n; * CONFIG_MODVERSIONS is to mangle those symbols depending on their&n; * definition (see man genksyms) - a change in the definition will thus&n; * caused the mangled name to change, and the module will refuse to&n; * load due to unresolved symbols.&n; *&n; * Let&squot;s start with taking a look how things work when we don&squot;t use&n; * CONFIG_MODVERSIONS. In this case, the only thing which is worth&n; * mentioning is the EXPORT_SYMBOL() macro. Using EXPORT_SYMBOL(foo)&n; * will expand into __EXPORT_SYMBOL(foo, &quot;foo&quot;), which then uses&n; * some ELF section magic to generate a list of pairs &n; * (address, symbol_name), which is used to resolve undefined &n; * symbols into addresses when loading a module.&n; * &n; * That&squot;s easy. Let&squot;s get back to CONFIG_MODVERSIONS=y.&n; *&n; * The first step is to generate the checksums. This is done at&n; * &quot;make dep&quot; time, code which exports symbols (using EXPORT_SYMTAB)&n; * is preprocessed with the additional macro __GENKSYMS__ set and fed&n; * into genksyms.&n; * At this stage, for each file that exports symbols an corresponding&n; * file in include/linux/module is generated, which for each exported&n; * symbol contains&n; *&n; *         #define __ver_schedule_task     2d6c3d04&n; *         #define schedule_task   _set_ver(schedule_task)&n; *&n; * In addition, include/linux/modversions.h is generated, which&n; * looks like&n; *&n; *         #include &lt;linux/modsetver.h&gt;&n; *         #include &lt;linux/modules/kernel__context.ver&gt;&n; *        &lt;&lt;&lt;lists all of the files just described&gt;&gt;&gt;&n; *&n; * Let&squot;s see what happens for different cases during compilation.&n; *&n; * o compile a file into the kernel which does not export symbols:&n; *&n; *   Since the file is known to not export symbols (it&squot;s not listed&n; *   in the export-objs variable in the corresponding Makefile), the&n; *   kernel build system does compile it with no extra flags set.&n; *   The macro EXPORT_SYMTAB is unset, and you can see below that&n; *   files which still try to use EXPORT_SYMBOL() will be trapped.&n; *   Other than that, just regular compilation.&n; *&n; * o compile a file into the kernel which does export symbols:&n; *&n; *   In this case, the file will compiled with the macro &n; *   EXPORT_SYMTAB defined.&n; *   As MODULE is not set, we hit this case from below:&n; *&n; *         #define _set_ver(sym) sym&n; *         #include &lt;linux/modversions.h&gt;&n; *         &n; *         #define EXPORT_SYMBOL(var) &bslash;&n; *          __EXPORT_SYMBOL(var, __MODULE_STRING(__VERSIONED_SYMBOL(var)))&n; *&n; *   The first two lines will in essence include&n; *&n; *         #define __ver_schedule_task     2d6c3d04&n; *         #define schedule_task   schedule_task&n; *&n; *   for each symbol. The second line really doesn&squot;t do much, but the&n; *   first one gives us the checksums we generated before.&n; *   &n; *   So EXPORT_SYMBOL(schedule_task) will expand into&n; *   __EXPORT_SYMBOL(schedule_task, &quot;schedule_task_R2d6c3d04&quot;),&n; *   hence exporting the symbol for schedule_task under the name of&n; *   schedule_task_R2d6c3d04.&n; *&n; * o compile a file into a module&n; *   &n; *   In this case, the kernel build system will add &n; *   &quot;-include include/linux/modversions.h&quot; to the command line. So&n; *   modversions.h is prepended to the actual source, turning into&n; *&n; *         #define __ver_schedule_task     2d6c3d04&n; *         #define schedule_task   schedule_task_R2d6c3d04&n; *&n; *   Though the source code says &quot;schedule_task&quot;, the compiler will&n; *   see the mangled symbol everywhere. So the module will end up with&n; *   an undefined symbol &quot;schedule_task_R2d6c3d04&quot; - which is exactly&n; *   the symbols which occurs in the kernel&squot;s list of symbols, with&n; *   a value of &amp;schedule_task - it all comes together nicely.&n; *&n; *   One question remains: What happens if a module itself exports&n; *   a symbol - the answer is simple: It&squot;s actually handled as the&n; *   CONFIG_MODVERSIONS=n case described first, only that the compiler&n; *   sees the mangled symbol everywhere. So &amp;foo_R12345678 is exported&n; *   with the name &quot;foo_R12345678&quot;. Think about it. It all makes sense.&n; */
macro_line|#if defined(__GENKSYMS__)
multiline_comment|/* We want the EXPORT_SYMBOL tag left intact for recognition.  */
macro_line|#elif !defined(CONFIG_MODULES)
DECL|macro|__EXPORT_SYMBOL
mdefine_line|#define __EXPORT_SYMBOL(sym,str)
DECL|macro|EXPORT_SYMBOL
mdefine_line|#define EXPORT_SYMBOL(var)
DECL|macro|EXPORT_SYMBOL_NOVERS
mdefine_line|#define EXPORT_SYMBOL_NOVERS(var)
DECL|macro|EXPORT_SYMBOL_GPL
mdefine_line|#define EXPORT_SYMBOL_GPL(var)
macro_line|#elif !defined(EXPORT_SYMTAB)
DECL|macro|__EXPORT_SYMBOL
mdefine_line|#define __EXPORT_SYMBOL(sym,str)   error this_object_must_be_defined_as_export_objs_in_the_Makefile
DECL|macro|EXPORT_SYMBOL
mdefine_line|#define EXPORT_SYMBOL(var)&t;   error this_object_must_be_defined_as_export_objs_in_the_Makefile
DECL|macro|EXPORT_SYMBOL_NOVERS
mdefine_line|#define EXPORT_SYMBOL_NOVERS(var)  error this_object_must_be_defined_as_export_objs_in_the_Makefile
DECL|macro|EXPORT_SYMBOL_GPL
mdefine_line|#define EXPORT_SYMBOL_GPL(var)  error this_object_must_be_defined_as_export_objs_in_the_Makefile
macro_line|#else
DECL|macro|__EXPORT_SYMBOL
mdefine_line|#define __EXPORT_SYMBOL(sym, str)&t;&t;&t;&bslash;&n;const char __kstrtab_##sym[]&t;&t;&t;&t;&bslash;&n;__attribute__((section(&quot;.kstrtab&quot;))) = str;&t;&t;&bslash;&n;const struct module_symbol __ksymtab_##sym &t;&t;&bslash;&n;__attribute__((section(&quot;__ksymtab&quot;))) =&t;&t;&t;&bslash;&n;{ (unsigned long)&amp;sym, __kstrtab_##sym }
DECL|macro|__EXPORT_SYMBOL_GPL
mdefine_line|#define __EXPORT_SYMBOL_GPL(sym, str)&t;&t;&t;&bslash;&n;const char __kstrtab_##sym[]&t;&t;&t;&t;&bslash;&n;__attribute__((section(&quot;.kstrtab&quot;))) = &quot;GPLONLY_&quot; str;&t;&bslash;&n;const struct module_symbol __ksymtab_##sym&t;&t;&bslash;&n;__attribute__((section(&quot;__ksymtab&quot;))) =&t;&t;&t;&bslash;&n;{ (unsigned long)&amp;sym, __kstrtab_##sym }
macro_line|#if defined(CONFIG_MODVERSIONS) &amp;&amp; !defined(MODULE)
DECL|macro|_set_ver
mdefine_line|#define _set_ver(sym) sym
macro_line|#include &lt;linux/modversions.h&gt;
DECL|macro|EXPORT_SYMBOL
mdefine_line|#define EXPORT_SYMBOL(var)  __EXPORT_SYMBOL(var, __MODULE_STRING(__VERSIONED_SYMBOL(var)))
DECL|macro|EXPORT_SYMBOL_GPL
mdefine_line|#define EXPORT_SYMBOL_GPL(var)  __EXPORT_SYMBOL(var, __MODULE_STRING(__VERSIONED_SYMBOL(var)))
macro_line|#else /* !defined (CONFIG_MODVERSIONS) || defined(MODULE) */
DECL|macro|EXPORT_SYMBOL
mdefine_line|#define EXPORT_SYMBOL(var)  __EXPORT_SYMBOL(var, __MODULE_STRING(var))
DECL|macro|EXPORT_SYMBOL_GPL
mdefine_line|#define EXPORT_SYMBOL_GPL(var)  __EXPORT_SYMBOL_GPL(var, __MODULE_STRING(var))
macro_line|#endif /* defined(CONFIG_MODVERSIONS) &amp;&amp; !defined(MODULE) */
DECL|macro|EXPORT_SYMBOL_NOVERS
mdefine_line|#define EXPORT_SYMBOL_NOVERS(var)  __EXPORT_SYMBOL(var, __MODULE_STRING(var))
macro_line|#endif /* __GENKSYMS__ */
multiline_comment|/* &n; * Force a module to export no symbols.&n; * EXPORT_NO_SYMBOLS is default now, leave the define around for sources&n; * which still have it&n; */
DECL|macro|EXPORT_NO_SYMBOLS
mdefine_line|#define EXPORT_NO_SYMBOLS
macro_line|#ifdef CONFIG_MODULES
multiline_comment|/* &n; * Always allocate a section &quot;__ksymtab&quot;. If we encounter EXPORT_SYMBOL,&n; * the exported symbol will be added to it.&n; * If it remains empty, that tells modutils that we do not want to&n; * export any symbols (as opposed to it not being present, which means&n; * &quot;export all symbols&quot; to modutils)&n; */
id|__asm__
c_func
(paren
l_string|&quot;.section __ksymtab,&bslash;&quot;a&bslash;&quot;&bslash;n.previous&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MODULES
DECL|macro|SET_MODULE_OWNER
mdefine_line|#define SET_MODULE_OWNER(some_struct) do { (some_struct)-&gt;owner = THIS_MODULE; } while (0)
macro_line|#else
DECL|macro|SET_MODULE_OWNER
mdefine_line|#define SET_MODULE_OWNER(some_struct) do { } while (0)
macro_line|#endif
r_extern
r_void
id|print_modules
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_MODULES) || defined(CONFIG_KALLSYMS)
r_extern
r_struct
id|module
op_star
id|module_list
suffix:semicolon
multiline_comment|/*&n; * print_symbols takes a format string containing one %s.&n; * If support for resolving symbols is compiled in, the %s will&n; * be replaced by the closest symbol to the address and the entire&n; * string is printk()ed. Otherwise, nothing is printed.&n; */
r_extern
r_void
id|print_symbol
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
r_int
r_int
id|address
)paren
suffix:semicolon
macro_line|#else
r_static
r_inline
r_int
DECL|function|print_symbol
id|print_symbol
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
r_int
r_int
id|address
)paren
(brace
r_return
op_minus
id|ESRCH
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* _LINUX_MODULE_H */
eof
