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
DECL|macro|VERMAGIC_STRING
mdefine_line|#define VERMAGIC_STRING &t;&t;&t;&t;&t;&t;&bslash;&n;&t;UTS_RELEASE &quot; &quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;MODULE_VERMAGIC_SMP MODULE_VERMAGIC_PREEMPT &t;&t;&t;&bslash;&n;&t;MODULE_ARCH_VERMAGIC &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;gcc-&quot; __stringify(__GNUC__) &quot;.&quot; __stringify(__GNUC_MINOR__)
eof
