macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &quot;cpu.h&quot;
DECL|variable|__initdata
r_static
r_int
id|cachesize_override
id|__initdata
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|disable_x86_fxsr
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|cpu_devs
r_struct
id|cpu_dev
op_star
id|cpu_devs
(braket
id|X86_VENDOR_NUM
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|variable|default_cpu
r_static
r_struct
id|cpu_dev
id|default_cpu
suffix:semicolon
DECL|variable|this_cpu
r_static
r_struct
id|cpu_dev
op_star
id|this_cpu
op_assign
op_amp
id|default_cpu
suffix:semicolon
r_extern
r_void
id|mcheck_init
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
suffix:semicolon
DECL|function|default_init
r_static
r_void
id|default_init
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
multiline_comment|/* Not much we can do here... */
multiline_comment|/* Check if at least it has cpuid */
r_if
c_cond
(paren
id|c-&gt;cpuid_level
op_eq
op_minus
l_int|1
)paren
(brace
multiline_comment|/* No cpuid. It must be an ancient CPU */
r_if
c_cond
(paren
id|c-&gt;x86
op_eq
l_int|4
)paren
id|strcpy
c_func
(paren
id|c-&gt;x86_model_id
comma
l_string|&quot;486&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c-&gt;x86
op_eq
l_int|3
)paren
id|strcpy
c_func
(paren
id|c-&gt;x86_model_id
comma
l_string|&quot;386&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|variable|default_cpu
r_static
r_struct
id|cpu_dev
id|default_cpu
op_assign
(brace
id|c_init
suffix:colon
id|default_init
comma
)brace
suffix:semicolon
DECL|function|cachesize_setup
r_static
r_int
id|__init
id|cachesize_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|get_option
(paren
op_amp
id|str
comma
op_amp
id|cachesize_override
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;cachesize=&quot;
comma
id|cachesize_setup
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_X86_TSC
DECL|variable|__initdata
r_static
r_int
id|tsc_disable
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|function|tsc_setup
r_static
r_int
id|__init
id|tsc_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|tsc_disable
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;notsc&quot;
comma
id|tsc_setup
)paren
suffix:semicolon
macro_line|#endif
DECL|function|get_model_name
r_int
id|__init
id|get_model_name
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_int
r_int
op_star
id|v
suffix:semicolon
r_char
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_if
c_cond
(paren
id|cpuid_eax
c_func
(paren
l_int|0x80000000
)paren
OL
l_int|0x80000004
)paren
r_return
l_int|0
suffix:semicolon
id|v
op_assign
(paren
r_int
r_int
op_star
)paren
id|c-&gt;x86_model_id
suffix:semicolon
id|cpuid
c_func
(paren
l_int|0x80000002
comma
op_amp
id|v
(braket
l_int|0
)braket
comma
op_amp
id|v
(braket
l_int|1
)braket
comma
op_amp
id|v
(braket
l_int|2
)braket
comma
op_amp
id|v
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|cpuid
c_func
(paren
l_int|0x80000003
comma
op_amp
id|v
(braket
l_int|4
)braket
comma
op_amp
id|v
(braket
l_int|5
)braket
comma
op_amp
id|v
(braket
l_int|6
)braket
comma
op_amp
id|v
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|cpuid
c_func
(paren
l_int|0x80000004
comma
op_amp
id|v
(braket
l_int|8
)braket
comma
op_amp
id|v
(braket
l_int|9
)braket
comma
op_amp
id|v
(braket
l_int|10
)braket
comma
op_amp
id|v
(braket
l_int|11
)braket
)paren
suffix:semicolon
id|c-&gt;x86_model_id
(braket
l_int|48
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Intel chips right-justify this string for some dumb reason;&n;&t;   undo that brain damage */
id|p
op_assign
id|q
op_assign
op_amp
id|c-&gt;x86_model_id
(braket
l_int|0
)braket
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
op_eq
l_char|&squot; &squot;
)paren
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ne
id|q
)paren
(brace
r_while
c_loop
(paren
op_star
id|p
)paren
op_star
id|q
op_increment
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|q
op_le
op_amp
id|c-&gt;x86_model_id
(braket
l_int|48
)braket
)paren
op_star
id|q
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* Zero-pad the rest */
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|display_cacheinfo
r_void
id|__init
id|display_cacheinfo
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_int
r_int
id|n
comma
id|dummy
comma
id|ecx
comma
id|edx
comma
id|l2size
suffix:semicolon
id|n
op_assign
id|cpuid_eax
c_func
(paren
l_int|0x80000000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
l_int|0x80000005
)paren
(brace
id|cpuid
c_func
(paren
l_int|0x80000005
comma
op_amp
id|dummy
comma
op_amp
id|dummy
comma
op_amp
id|ecx
comma
op_amp
id|edx
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CPU: L1 I Cache: %dK (%d bytes/line), D cache %dK (%d bytes/line)&bslash;n&quot;
comma
id|edx
op_rshift
l_int|24
comma
id|edx
op_amp
l_int|0xFF
comma
id|ecx
op_rshift
l_int|24
comma
id|ecx
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|c-&gt;x86_cache_size
op_assign
(paren
id|ecx
op_rshift
l_int|24
)paren
op_plus
(paren
id|edx
op_rshift
l_int|24
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n
OL
l_int|0x80000006
)paren
multiline_comment|/* Some chips just has a large L1. */
r_return
suffix:semicolon
id|ecx
op_assign
id|cpuid_ecx
c_func
(paren
l_int|0x80000006
)paren
suffix:semicolon
id|l2size
op_assign
id|ecx
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* do processor-specific cache resizing */
r_if
c_cond
(paren
id|this_cpu-&gt;c_size_cache
)paren
id|l2size
op_assign
id|this_cpu
op_member_access_from_pointer
id|c_size_cache
c_func
(paren
id|c
comma
id|l2size
)paren
suffix:semicolon
multiline_comment|/* Allow user to override all this if necessary. */
r_if
c_cond
(paren
id|cachesize_override
op_ne
op_minus
l_int|1
)paren
id|l2size
op_assign
id|cachesize_override
suffix:semicolon
r_if
c_cond
(paren
id|l2size
op_eq
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/* Again, no L2 cache is possible */
id|c-&gt;x86_cache_size
op_assign
id|l2size
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CPU: L2 Cache: %dK (%d bytes/line)&bslash;n&quot;
comma
id|l2size
comma
id|ecx
op_amp
l_int|0xFF
)paren
suffix:semicolon
)brace
multiline_comment|/* Naming convention should be: &lt;Name&gt; [(&lt;Codename&gt;)] */
multiline_comment|/* This table only is used unless init_&lt;vendor&gt;() below doesn&squot;t set it; */
multiline_comment|/* in particular, if CPUID levels 0x80000002..4 are supported, this isn&squot;t used */
multiline_comment|/* Look up CPU names by table lookup. */
DECL|function|table_lookup_model
r_static
r_char
id|__init
op_star
id|table_lookup_model
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_struct
id|cpu_model_info
op_star
id|info
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;x86_model
op_ge
l_int|16
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Range check */
r_if
c_cond
(paren
op_logical_neg
id|this_cpu
)paren
r_return
l_int|NULL
suffix:semicolon
id|info
op_assign
id|this_cpu-&gt;c_models
suffix:semicolon
r_while
c_loop
(paren
id|info
op_logical_and
id|info-&gt;family
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;family
op_eq
id|c-&gt;x86
)paren
r_return
id|info-&gt;model_names
(braket
id|c-&gt;x86_model
)braket
suffix:semicolon
id|info
op_increment
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Not found */
)brace
DECL|function|get_cpu_vendor
r_void
id|__init
id|get_cpu_vendor
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_char
op_star
id|v
op_assign
id|c-&gt;x86_vendor_id
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|X86_VENDOR_NUM
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cpu_devs
(braket
id|i
)braket
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|v
comma
id|cpu_devs
(braket
id|i
)braket
op_member_access_from_pointer
id|c_ident
(braket
l_int|0
)braket
)paren
op_logical_or
(paren
id|cpu_devs
(braket
id|i
)braket
op_member_access_from_pointer
id|c_ident
(braket
l_int|1
)braket
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|v
comma
id|cpu_devs
(braket
id|i
)braket
op_member_access_from_pointer
id|c_ident
(braket
l_int|1
)braket
)paren
)paren
)paren
(brace
id|c-&gt;x86_vendor
op_assign
id|i
suffix:semicolon
id|this_cpu
op_assign
id|cpu_devs
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|x86_fxsr_setup
r_static
r_int
id|__init
id|x86_fxsr_setup
c_func
(paren
r_char
op_star
id|s
)paren
(brace
id|disable_x86_fxsr
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;nofxsr&quot;
comma
id|x86_fxsr_setup
)paren
suffix:semicolon
multiline_comment|/* Standard macro to see if a specific flag is changeable */
DECL|function|flag_is_changeable_p
r_static
r_inline
r_int
id|flag_is_changeable_p
c_func
(paren
id|u32
id|flag
)paren
(brace
id|u32
id|f1
comma
id|f2
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;pushfl&bslash;n&bslash;t&quot;
l_string|&quot;pushfl&bslash;n&bslash;t&quot;
l_string|&quot;popl %0&bslash;n&bslash;t&quot;
l_string|&quot;movl %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;xorl %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;pushl %0&bslash;n&bslash;t&quot;
l_string|&quot;popfl&bslash;n&bslash;t&quot;
l_string|&quot;pushfl&bslash;n&bslash;t&quot;
l_string|&quot;popl %0&bslash;n&bslash;t&quot;
l_string|&quot;popfl&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|f1
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|f2
)paren
suffix:colon
l_string|&quot;ir&quot;
(paren
id|flag
)paren
)paren
suffix:semicolon
r_return
(paren
(paren
id|f1
op_xor
id|f2
)paren
op_amp
id|flag
)paren
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Probe for the CPUID instruction */
DECL|function|have_cpuid_p
r_int
id|__init
id|have_cpuid_p
c_func
(paren
r_void
)paren
(brace
r_return
id|flag_is_changeable_p
c_func
(paren
id|X86_EFLAGS_ID
)paren
suffix:semicolon
)brace
DECL|function|generic_identify
r_void
id|__init
id|generic_identify
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
id|u32
id|tfms
suffix:semicolon
r_int
id|junk
suffix:semicolon
r_if
c_cond
(paren
id|have_cpuid_p
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* Get vendor name */
id|cpuid
c_func
(paren
l_int|0x00000000
comma
op_amp
id|c-&gt;cpuid_level
comma
(paren
r_int
op_star
)paren
op_amp
id|c-&gt;x86_vendor_id
(braket
l_int|0
)braket
comma
(paren
r_int
op_star
)paren
op_amp
id|c-&gt;x86_vendor_id
(braket
l_int|8
)braket
comma
(paren
r_int
op_star
)paren
op_amp
id|c-&gt;x86_vendor_id
(braket
l_int|4
)braket
)paren
suffix:semicolon
id|get_cpu_vendor
c_func
(paren
id|c
)paren
suffix:semicolon
multiline_comment|/* Initialize the standard set of capabilities */
multiline_comment|/* Note that the vendor-specific code below might override */
multiline_comment|/* Intel-defined flags: level 0x00000001 */
r_if
c_cond
(paren
id|c-&gt;cpuid_level
op_ge
l_int|0x00000001
)paren
(brace
id|u32
id|capability
suffix:semicolon
id|cpuid
c_func
(paren
l_int|0x00000001
comma
op_amp
id|tfms
comma
op_amp
id|junk
comma
op_amp
id|junk
comma
op_amp
id|capability
)paren
suffix:semicolon
id|c-&gt;x86_capability
(braket
l_int|0
)braket
op_assign
id|capability
suffix:semicolon
id|c-&gt;x86
op_assign
(paren
id|tfms
op_rshift
l_int|8
)paren
op_amp
l_int|15
suffix:semicolon
id|c-&gt;x86_model
op_assign
(paren
id|tfms
op_rshift
l_int|4
)paren
op_amp
l_int|15
suffix:semicolon
id|c-&gt;x86_mask
op_assign
id|tfms
op_amp
l_int|15
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Have CPUID level 0 only - unheard of */
id|c-&gt;x86
op_assign
l_int|4
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * This does the hard work of actually picking apart the CPU stuff...&n; */
DECL|function|identify_cpu
r_void
id|__init
id|identify_cpu
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_int
id|i
suffix:semicolon
id|c-&gt;loops_per_jiffy
op_assign
id|loops_per_jiffy
suffix:semicolon
id|c-&gt;x86_cache_size
op_assign
op_minus
l_int|1
suffix:semicolon
id|c-&gt;x86_vendor
op_assign
id|X86_VENDOR_UNKNOWN
suffix:semicolon
id|c-&gt;cpuid_level
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* CPUID not detected */
id|c-&gt;x86_model
op_assign
id|c-&gt;x86_mask
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* So far unknown... */
id|c-&gt;x86_vendor_id
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* Unset */
id|c-&gt;x86_model_id
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* Unset */
id|memset
c_func
(paren
op_amp
id|c-&gt;x86_capability
comma
l_int|0
comma
r_sizeof
id|c-&gt;x86_capability
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|have_cpuid_p
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* First of all, decide if this is a 486 or higher */
multiline_comment|/* It&squot;s a 486 if we can modify the AC flag */
r_if
c_cond
(paren
id|flag_is_changeable_p
c_func
(paren
id|X86_EFLAGS_AC
)paren
)paren
id|c-&gt;x86
op_assign
l_int|4
suffix:semicolon
r_else
id|c-&gt;x86
op_assign
l_int|3
suffix:semicolon
)brace
r_if
c_cond
(paren
id|this_cpu-&gt;c_identify
)paren
id|this_cpu
op_member_access_from_pointer
id|c_identify
c_func
(paren
id|c
)paren
suffix:semicolon
r_else
id|generic_identify
c_func
(paren
id|c
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;CPU: Before vendor init, caps: %08lx %08lx %08lx, vendor = %d&bslash;n&quot;
comma
id|c-&gt;x86_capability
(braket
l_int|0
)braket
comma
id|c-&gt;x86_capability
(braket
l_int|1
)braket
comma
id|c-&gt;x86_capability
(braket
l_int|2
)braket
comma
id|c-&gt;x86_vendor
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Vendor-specific initialization.  In this section we&n;&t; * canonicalize the feature flags, meaning if there are&n;&t; * features a certain CPU supports which CPUID doesn&squot;t&n;&t; * tell us, CPUID claiming incorrect flags, or other bugs,&n;&t; * we handle them here.&n;&t; *&n;&t; * At the end of this section, c-&gt;x86_capability better&n;&t; * indicate the features this CPU genuinely supports!&n;&t; */
r_if
c_cond
(paren
id|this_cpu-&gt;c_init
)paren
id|this_cpu
op_member_access_from_pointer
id|c_init
c_func
(paren
id|c
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;CPU: After vendor init, caps: %08lx %08lx %08lx %08lx&bslash;n&quot;
comma
id|c-&gt;x86_capability
(braket
l_int|0
)braket
comma
id|c-&gt;x86_capability
(braket
l_int|1
)braket
comma
id|c-&gt;x86_capability
(braket
l_int|2
)braket
comma
id|c-&gt;x86_capability
(braket
l_int|3
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The vendor-specific functions might have changed features.  Now&n;&t; * we do &quot;generic changes.&quot;&n;&t; */
multiline_comment|/* TSC disabled? */
macro_line|#ifndef CONFIG_X86_TSC
r_if
c_cond
(paren
id|tsc_disable
)paren
id|clear_bit
c_func
(paren
id|X86_FEATURE_TSC
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* FXSR disabled? */
r_if
c_cond
(paren
id|disable_x86_fxsr
)paren
(brace
id|clear_bit
c_func
(paren
id|X86_FEATURE_FXSR
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|X86_FEATURE_XMM
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
)brace
multiline_comment|/* Init Machine Check Exception if available. */
id|mcheck_init
c_func
(paren
id|c
)paren
suffix:semicolon
multiline_comment|/* If the model name is still unset, do table lookup. */
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;x86_model_id
(braket
l_int|0
)braket
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
id|p
op_assign
id|table_lookup_model
c_func
(paren
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
id|strcpy
c_func
(paren
id|c-&gt;x86_model_id
comma
id|p
)paren
suffix:semicolon
r_else
multiline_comment|/* Last resort... */
id|sprintf
c_func
(paren
id|c-&gt;x86_model_id
comma
l_string|&quot;%02x/%02x&quot;
comma
id|c-&gt;x86_vendor
comma
id|c-&gt;x86_model
)paren
suffix:semicolon
)brace
multiline_comment|/* Now the feature flags better reflect actual CPU features! */
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;CPU:     After generic, caps: %08lx %08lx %08lx %08lx&bslash;n&quot;
comma
id|c-&gt;x86_capability
(braket
l_int|0
)braket
comma
id|c-&gt;x86_capability
(braket
l_int|1
)braket
comma
id|c-&gt;x86_capability
(braket
l_int|2
)braket
comma
id|c-&gt;x86_capability
(braket
l_int|3
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * On SMP, boot_cpu_data holds the common feature set between&n;&t; * all CPUs; so make sure that we indicate which features are&n;&t; * common between the CPUs.  The first time this routine gets&n;&t; * executed, c == &amp;boot_cpu_data.&n;&t; */
r_if
c_cond
(paren
id|c
op_ne
op_amp
id|boot_cpu_data
)paren
(brace
multiline_comment|/* AND the already accumulated flags with these */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NCAPINTS
suffix:semicolon
id|i
op_increment
)paren
id|boot_cpu_data.x86_capability
(braket
id|i
)braket
op_and_assign
id|c-&gt;x86_capability
(braket
id|i
)braket
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;CPU:             Common caps: %08lx %08lx %08lx %08lx&bslash;n&quot;
comma
id|boot_cpu_data.x86_capability
(braket
l_int|0
)braket
comma
id|boot_cpu_data.x86_capability
(braket
l_int|1
)braket
comma
id|boot_cpu_data.x86_capability
(braket
l_int|2
)braket
comma
id|boot_cpu_data.x86_capability
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Perform early boot up checks for a valid TSC. See arch/i386/kernel/time.c&n; */
DECL|function|dodgy_tsc
r_void
id|__init
id|dodgy_tsc
c_func
(paren
r_void
)paren
(brace
id|get_cpu_vendor
c_func
(paren
op_amp
id|boot_cpu_data
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|boot_cpu_data.x86_vendor
op_eq
id|X86_VENDOR_CYRIX
)paren
op_logical_or
(paren
id|boot_cpu_data.x86_vendor
op_eq
id|X86_VENDOR_NSC
)paren
)paren
id|cpu_devs
(braket
id|X86_VENDOR_CYRIX
)braket
op_member_access_from_pointer
id|c_init
c_func
(paren
op_amp
id|boot_cpu_data
)paren
suffix:semicolon
)brace
DECL|function|print_cpu_info
r_void
id|__init
id|print_cpu_info
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_char
op_star
id|vendor
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;x86_vendor
OL
id|X86_VENDOR_NUM
)paren
id|vendor
op_assign
id|this_cpu-&gt;c_vendor
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c-&gt;cpuid_level
op_ge
l_int|0
)paren
id|vendor
op_assign
id|c-&gt;x86_vendor_id
suffix:semicolon
r_if
c_cond
(paren
id|vendor
op_logical_and
id|strncmp
c_func
(paren
id|c-&gt;x86_model_id
comma
id|vendor
comma
id|strlen
c_func
(paren
id|vendor
)paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;%s &quot;
comma
id|vendor
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;x86_model_id
(braket
l_int|0
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;%d86&quot;
comma
id|c-&gt;x86
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|c-&gt;x86_model_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;x86_mask
op_logical_or
id|c-&gt;cpuid_level
op_ge
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot; stepping %02x&bslash;n&quot;
comma
id|c-&gt;x86_mask
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_int
r_int
id|cpu_initialized
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* This is hacky. :)&n; * We&squot;re emulating future behavior.&n; * In the future, the cpu-specific init functions will be called implicitly&n; * via the magic of initcalls.&n; * They will insert themselves into the cpu_devs structure.&n; * Then, when cpu_init() is called, we can just iterate over that array.&n; */
r_extern
r_int
id|intel_cpu_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|cyrix_init_cpu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|nsc_init_cpu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|amd_init_cpu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|centaur_init_cpu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|transmeta_init_cpu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|rise_init_cpu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|nexgen_init_cpu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|umc_init_cpu
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|early_cpu_init
r_void
id|__init
id|early_cpu_init
c_func
(paren
r_void
)paren
(brace
id|intel_cpu_init
c_func
(paren
)paren
suffix:semicolon
id|cyrix_init_cpu
c_func
(paren
)paren
suffix:semicolon
id|nsc_init_cpu
c_func
(paren
)paren
suffix:semicolon
id|amd_init_cpu
c_func
(paren
)paren
suffix:semicolon
id|centaur_init_cpu
c_func
(paren
)paren
suffix:semicolon
id|transmeta_init_cpu
c_func
(paren
)paren
suffix:semicolon
id|rise_init_cpu
c_func
(paren
)paren
suffix:semicolon
id|nexgen_init_cpu
c_func
(paren
)paren
suffix:semicolon
id|umc_init_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * cpu_init() initializes state that is per-CPU. Some data is already&n; * initialized (naturally) in the bootstrap process, such as the GDT&n; * and IDT. We reload them nevertheless, this function acts as a&n; * &squot;CPU state barrier&squot;, nothing should get across.&n; */
DECL|function|cpu_init
r_void
id|__init
id|cpu_init
(paren
r_void
)paren
(brace
r_int
id|nr
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_struct
id|tss_struct
op_star
id|t
op_assign
op_amp
id|init_tss
(braket
id|nr
)braket
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|nr
comma
op_amp
id|cpu_initialized
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;CPU#%d already initialized!&bslash;n&quot;
comma
id|nr
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
id|__sti
c_func
(paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Initializing CPU#%d&bslash;n&quot;
comma
id|nr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_vme
op_logical_or
id|cpu_has_tsc
op_logical_or
id|cpu_has_de
)paren
id|clear_in_cr4
c_func
(paren
id|X86_CR4_VME
op_or
id|X86_CR4_PVI
op_or
id|X86_CR4_TSD
op_or
id|X86_CR4_DE
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_X86_TSC
r_if
c_cond
(paren
id|tsc_disable
op_logical_and
id|cpu_has_tsc
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Disabling TSC...&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/**** FIX-HPA: DOES THIS REALLY BELONG HERE? ****/
id|clear_bit
c_func
(paren
id|X86_FEATURE_TSC
comma
id|boot_cpu_data.x86_capability
)paren
suffix:semicolon
id|set_in_cr4
c_func
(paren
id|X86_CR4_TSD
)paren
suffix:semicolon
)brace
macro_line|#endif
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lgdt %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|gdt_descr
)paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lidt %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|idt_descr
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Delete NT&n;&t; */
id|__asm__
c_func
(paren
l_string|&quot;pushfl ; andl $0xffffbfff,(%esp) ; popfl&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * set up and load the per-CPU TSS and LDT&n;&t; */
id|atomic_inc
c_func
(paren
op_amp
id|init_mm.mm_count
)paren
suffix:semicolon
id|current-&gt;active_mm
op_assign
op_amp
id|init_mm
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;mm
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|enter_lazy_tlb
c_func
(paren
op_amp
id|init_mm
comma
id|current
comma
id|nr
)paren
suffix:semicolon
id|t-&gt;esp0
op_assign
id|current-&gt;thread.esp0
suffix:semicolon
id|set_tss_desc
c_func
(paren
id|nr
comma
id|t
)paren
suffix:semicolon
id|gdt_table
(braket
id|__TSS
c_func
(paren
id|nr
)paren
)braket
dot
id|b
op_and_assign
l_int|0xfffffdff
suffix:semicolon
id|load_TR
c_func
(paren
id|nr
)paren
suffix:semicolon
id|load_LDT
c_func
(paren
op_amp
id|init_mm.context
)paren
suffix:semicolon
multiline_comment|/* Clear %fs and %gs. */
id|asm
r_volatile
(paren
l_string|&quot;xorl %eax, %eax; movl %eax, %fs; movl %eax, %gs&quot;
)paren
suffix:semicolon
multiline_comment|/* Clear all 6 debug registers: */
DECL|macro|CD
mdefine_line|#define CD(register) __asm__(&quot;movl %0,%%db&quot; #register ::&quot;r&quot;(0) );
id|CD
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|CD
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|CD
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|CD
c_func
(paren
l_int|3
)paren
suffix:semicolon
multiline_comment|/* no db4 and db5 */
suffix:semicolon
id|CD
c_func
(paren
l_int|6
)paren
suffix:semicolon
id|CD
c_func
(paren
l_int|7
)paren
suffix:semicolon
DECL|macro|CD
macro_line|#undef CD
multiline_comment|/*&n;&t; * Force FPU initialization:&n;&t; */
id|clear_thread_flag
c_func
(paren
id|TIF_USEDFPU
)paren
suffix:semicolon
id|current-&gt;used_math
op_assign
l_int|0
suffix:semicolon
id|stts
c_func
(paren
)paren
suffix:semicolon
)brace
eof