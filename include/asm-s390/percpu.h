macro_line|#ifndef __ARCH_S390_PERCPU__
DECL|macro|__ARCH_S390_PERCPU__
mdefine_line|#define __ARCH_S390_PERCPU__
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/lowcore.h&gt;
DECL|macro|__GENERIC_PER_CPU
mdefine_line|#define __GENERIC_PER_CPU
multiline_comment|/*&n; * s390 uses its own implementation for per cpu data, the offset of&n; * the cpu local data area is cached in the cpu&squot;s lowcore memory.&n; * For 64 bit module code s390 forces the use of a GOT slot for the&n; * address of the per cpu variable. This is needed because the module&n; * may be more than 4G above the per cpu area.&n; */
macro_line|#if defined(__s390x__) &amp;&amp; defined(MODULE)
DECL|macro|__reloc_hide
mdefine_line|#define __reloc_hide(var,offset) &bslash;&n;  (*({ unsigned long *__ptr; &bslash;&n;       asm ( &quot;larl %0,per_cpu__&quot;#var&quot;@GOTENT&quot; &bslash;&n;             : &quot;=a&quot; (__ptr) : &quot;X&quot; (per_cpu__##var) ); &bslash;&n;       (typeof(&amp;per_cpu__##var))((*__ptr) + (offset)); }))
macro_line|#else
DECL|macro|__reloc_hide
mdefine_line|#define __reloc_hide(var, offset) &bslash;&n;  (*({ unsigned long __ptr; &bslash;&n;       asm ( &quot;&quot; : &quot;=a&quot; (__ptr) : &quot;0&quot; (&amp;per_cpu__##var) ); &bslash;&n;       (typeof(&amp;per_cpu__##var)) (__ptr + (offset)); }))
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
r_extern
r_int
r_int
id|__per_cpu_offset
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/* Separate out the type, so (int[3], foo) works. */
DECL|macro|DEFINE_PER_CPU
mdefine_line|#define DEFINE_PER_CPU(type, name) &bslash;&n;    __attribute__((__section__(&quot;.data.percpu&quot;))) &bslash;&n;    __typeof__(type) per_cpu__##name
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var) __reloc_hide(var,S390_lowcore.percpu_offset)
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var,cpu) __reloc_hide(var,__per_cpu_offset[cpu])
multiline_comment|/* A macro to avoid #include hell... */
DECL|macro|percpu_modcopy
mdefine_line|#define percpu_modcopy(pcpudst, src, size)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int __i;&t;&t;&t;&t;&t;&bslash;&n;&t;for (__i = 0; __i &lt; NR_CPUS; __i++)&t;&t;&t;&bslash;&n;&t;&t;if (cpu_possible(__i))&t;&t;&t;&t;&bslash;&n;&t;&t;&t;memcpy((pcpudst)+__per_cpu_offset[__i],&t;&bslash;&n;&t;&t;&t;       (src), (size));&t;&t;&t;&bslash;&n;} while (0)
macro_line|#else /* ! SMP */
DECL|macro|DEFINE_PER_CPU
mdefine_line|#define DEFINE_PER_CPU(type, name) &bslash;&n;    __typeof__(type) per_cpu__##name
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var) __reloc_hide(var,0)
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var,cpu) __reloc_hide(var,0)
macro_line|#endif /* SMP */
DECL|macro|DECLARE_PER_CPU
mdefine_line|#define DECLARE_PER_CPU(type, name) extern __typeof__(type) per_cpu__##name
DECL|macro|EXPORT_PER_CPU_SYMBOL
mdefine_line|#define EXPORT_PER_CPU_SYMBOL(var) EXPORT_SYMBOL(per_cpu__##var)
DECL|macro|EXPORT_PER_CPU_SYMBOL_GPL
mdefine_line|#define EXPORT_PER_CPU_SYMBOL_GPL(var) EXPORT_SYMBOL_GPL(per_cpu__##var)
macro_line|#endif /* __ARCH_S390_PERCPU__ */
eof
