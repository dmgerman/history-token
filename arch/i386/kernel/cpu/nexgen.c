macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &quot;cpu.h&quot;
multiline_comment|/*&n; *&t;Detect a NexGen CPU running without BIOS hypercode new enough&n; *&t;to have CPUID. (Thanks to Herbert Oppmann)&n; */
DECL|function|deep_magic_nexgen_probe
r_static
r_int
id|__init
id|deep_magic_nexgen_probe
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;&t;movw&t;$0x5555, %%ax&bslash;n&quot;
l_string|&quot;&t;xorw&t;%%dx,%%dx&bslash;n&quot;
l_string|&quot;&t;movw&t;$2, %%cx&bslash;n&quot;
l_string|&quot;&t;divw&t;%%cx&bslash;n&quot;
l_string|&quot;&t;movl&t;$0, %%eax&bslash;n&quot;
l_string|&quot;&t;jnz&t;1f&bslash;n&quot;
l_string|&quot;&t;movl&t;$1, %%eax&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|ret
)paren
suffix:colon
suffix:colon
l_string|&quot;cx&quot;
comma
l_string|&quot;dx&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|init_nexgen
r_static
r_void
id|__init
id|init_nexgen
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
id|c-&gt;x86_cache_size
op_assign
l_int|256
suffix:semicolon
multiline_comment|/* A few had 1 MB... */
)brace
DECL|function|nexgen_identify
r_static
r_void
id|nexgen_identify
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
multiline_comment|/* Detect NexGen with old hypercode */
r_if
c_cond
(paren
id|deep_magic_nexgen_probe
c_func
(paren
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|c-&gt;x86_vendor_id
comma
l_string|&quot;NexGenDriven&quot;
)paren
suffix:semicolon
)brace
id|generic_identify
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|cpu_dev
id|nexgen_cpu_dev
id|__initdata
op_assign
(brace
dot
id|c_vendor
op_assign
l_string|&quot;Nexgen&quot;
comma
dot
id|c_ident
op_assign
(brace
l_string|&quot;NexGenDriven&quot;
)brace
comma
dot
id|c_models
op_assign
(brace
(brace
dot
id|vendor
op_assign
id|X86_VENDOR_NEXGEN
comma
dot
id|family
op_assign
l_int|5
comma
dot
id|model_names
op_assign
(brace
(braket
l_int|1
)braket
op_assign
l_string|&quot;Nx586&quot;
)brace
)brace
comma
)brace
comma
dot
id|c_init
op_assign
id|init_nexgen
comma
dot
id|c_identify
op_assign
id|nexgen_identify
comma
)brace
suffix:semicolon
DECL|function|nexgen_init_cpu
r_int
id|__init
id|nexgen_init_cpu
c_func
(paren
r_void
)paren
(brace
id|cpu_devs
(braket
id|X86_VENDOR_NEXGEN
)braket
op_assign
op_amp
id|nexgen_cpu_dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|//early_arch_initcall(nexgen_init_cpu);
eof
