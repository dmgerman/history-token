macro_line|#ifndef __ASM_GENERIC_CPUMASK_H
DECL|macro|__ASM_GENERIC_CPUMASK_H
mdefine_line|#define __ASM_GENERIC_CPUMASK_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/bitmap.h&gt;
macro_line|#if NR_CPUS &gt; BITS_PER_LONG &amp;&amp; NR_CPUS != 1
DECL|macro|CPU_ARRAY_SIZE
mdefine_line|#define CPU_ARRAY_SIZE&t;&t;BITS_TO_LONGS(NR_CPUS)
DECL|struct|cpumask
r_struct
id|cpumask
(brace
DECL|member|mask
r_int
r_int
id|mask
(braket
id|CPU_ARRAY_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|cpumask_t
r_typedef
r_struct
id|cpumask
id|cpumask_t
suffix:semicolon
macro_line|#else
DECL|typedef|cpumask_t
r_typedef
r_int
r_int
id|cpumask_t
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
macro_line|#if NR_CPUS &gt; BITS_PER_LONG
macro_line|#include &lt;asm-generic/cpumask_array.h&gt;
macro_line|#else
macro_line|#include &lt;asm-generic/cpumask_arith.h&gt;
macro_line|#endif
macro_line|#else
macro_line|#include &lt;asm-generic/cpumask_up.h&gt;
macro_line|#endif
macro_line|#if NR_CPUS &lt;= 4*BITS_PER_LONG
macro_line|#include &lt;asm-generic/cpumask_const_value.h&gt;
macro_line|#else
macro_line|#include &lt;asm-generic/cpumask_const_reference.h&gt;
macro_line|#endif
macro_line|#endif /* __ASM_GENERIC_CPUMASK_H */
eof
