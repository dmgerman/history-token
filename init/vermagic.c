macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
multiline_comment|/* Simply sanity version stamp for modules. */
macro_line|#ifdef CONFIG_SMP
DECL|macro|MODULE_VERMAGIC_SMP
mdefine_line|#define MODULE_VERMAGIC_SMP &quot;SMP &quot;
macro_line|#else
DECL|macro|MODULE_VERMAGIC_SMP
mdefine_line|#define MODULE_VERMAGIC_SMP &quot;&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_PREEMPT
DECL|macro|MODULE_VERMAGIC_PREEMPT
mdefine_line|#define MODULE_VERMAGIC_PREEMPT &quot;preempt &quot;
macro_line|#else
DECL|macro|MODULE_VERMAGIC_PREEMPT
mdefine_line|#define MODULE_VERMAGIC_PREEMPT &quot;&quot;
macro_line|#endif
macro_line|#ifndef MODULE_ARCH_VERMAGIC
DECL|macro|MODULE_ARCH_VERMAGIC
mdefine_line|#define MODULE_ARCH_VERMAGIC &quot;&quot;
macro_line|#endif
DECL|variable|vermagic
r_const
r_char
id|vermagic
(braket
)braket
id|__attribute__
c_func
(paren
(paren
id|section
c_func
(paren
l_string|&quot;__vermagic&quot;
)paren
)paren
)paren
op_assign
id|UTS_RELEASE
l_string|&quot; &quot;
id|MODULE_VERMAGIC_SMP
id|MODULE_VERMAGIC_PREEMPT
id|MODULE_ARCH_VERMAGIC
l_string|&quot;gcc-&quot;
id|__stringify
c_func
(paren
id|__GNUC__
)paren
l_string|&quot;.&quot;
id|__stringify
c_func
(paren
id|__GNUC_MINOR__
)paren
suffix:semicolon
eof
