macro_line|#ifndef __ARCH_S390_PERCPU__
DECL|macro|__ARCH_S390_PERCPU__
mdefine_line|#define __ARCH_S390_PERCPU__
macro_line|#include &lt;asm-generic/percpu.h&gt;
macro_line|#include &lt;asm/lowcore.h&gt;
multiline_comment|/*&n; * For builtin kernel code s390 uses the generic implementation for&n; * per cpu data, with the exception that the offset of the cpu local&n; * data area is cached in the cpu&squot;s lowcore memory&n; * For 64 bit module code s390 forces the use of a GOT slot for the&n; * address of the per cpu variable. This is needed because the module&n; * may be more than 4G above the per cpu area.&n; */
macro_line|#if defined(__s390x__) &amp;&amp; defined(MODULE)
DECL|macro|__get_got_cpu_var
mdefine_line|#define __get_got_cpu_var(var,offset) &bslash;&n;  (*({ unsigned long *__ptr; &bslash;&n;       asm ( &quot;larl %0,per_cpu__&quot;#var&quot;@GOTENT&quot; : &quot;=a&quot; (__ptr) ); &bslash;&n;       ((typeof(&amp;per_cpu__##var))((*__ptr) + offset)); &bslash;&n;    }))
DECL|macro|__get_cpu_var
macro_line|#undef __get_cpu_var
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var) __get_got_cpu_var(var,S390_lowcore.percpu_offset)
DECL|macro|per_cpu
macro_line|#undef per_cpu
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var,cpu) __get_got_cpu_var(var,__per_cpu_offset[cpu])
macro_line|#else
DECL|macro|__get_cpu_var
macro_line|#undef __get_cpu_var
DECL|macro|__get_cpu_var
mdefine_line|#define __get_cpu_var(var) (*RELOC_HIDE(&amp;per_cpu__##var, S390_lowcore.percpu_offset))
macro_line|#endif
macro_line|#endif /* __ARCH_S390_PERCPU__ */
eof
