macro_line|#ifndef X86_64_PDA_H
DECL|macro|X86_64_PDA_H
mdefine_line|#define X86_64_PDA_H
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#ifndef ASM_OFFSET_H
macro_line|#include &lt;asm/offset.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/cache.h&gt;
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/* Per processor datastructure. %gs points to it while the kernel runs */
multiline_comment|/* To use a new field with the *_pda macros it needs to be added to tools/offset.c */
DECL|struct|x8664_pda
r_struct
id|x8664_pda
(brace
DECL|member|me
r_struct
id|x8664_pda
op_star
id|me
suffix:semicolon
DECL|member|kernelstack
r_int
r_int
id|kernelstack
suffix:semicolon
multiline_comment|/* TOS for current process */
DECL|member|oldrsp
r_int
r_int
id|oldrsp
suffix:semicolon
multiline_comment|/* user rsp for system call */
DECL|member|irqrsp
r_int
r_int
id|irqrsp
suffix:semicolon
multiline_comment|/* Old rsp for interrupts. */
DECL|member|pcurrent
r_struct
id|task_struct
op_star
id|pcurrent
suffix:semicolon
multiline_comment|/* Current process */
DECL|member|irqcount
r_int
id|irqcount
suffix:semicolon
multiline_comment|/* Irq nesting counter. Starts with -1 */
DECL|member|cpunumber
r_int
id|cpunumber
suffix:semicolon
multiline_comment|/* Logical CPU number */
DECL|member|irqstackptr
r_char
op_star
id|irqstackptr
suffix:semicolon
DECL|member|__softirq_pending
r_int
r_int
id|__softirq_pending
suffix:semicolon
DECL|member|__local_irq_count
r_int
r_int
id|__local_irq_count
suffix:semicolon
DECL|member|__local_bh_count
r_int
r_int
id|__local_bh_count
suffix:semicolon
DECL|member|__nmi_count
r_int
r_int
id|__nmi_count
suffix:semicolon
multiline_comment|/* arch dependent */
DECL|member|__ksoftirqd_task
r_struct
id|task_struct
op_star
id|__ksoftirqd_task
suffix:semicolon
multiline_comment|/* waitqueue is too large */
DECL|member|irqstack
r_char
id|irqstack
(braket
l_int|16
op_star
l_int|1024
)braket
suffix:semicolon
multiline_comment|/* Stack used by interrupts */
DECL|variable|____cacheline_aligned
)brace
id|____cacheline_aligned
suffix:semicolon
DECL|macro|PDA_STACKOFFSET
mdefine_line|#define PDA_STACKOFFSET (5*8)
r_extern
r_struct
id|x8664_pda
id|cpu_pda
(braket
)braket
suffix:semicolon
multiline_comment|/* &n; * There is no fast way to get the base address of the PDA, all the accesses&n; * have to mention %fs/%gs.  So it needs to be done this Torvaldian way.&n; */
DECL|macro|sizeof_field
mdefine_line|#define sizeof_field(type,field)  (sizeof(((type *)0)-&gt;field))
DECL|macro|typeof_field
mdefine_line|#define typeof_field(type,field)  typeof(((type *)0)-&gt;field)
macro_line|#ifndef __STR
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
macro_line|#endif
DECL|macro|__STR2
mdefine_line|#define __STR2(x) __STR(x) 
r_extern
r_void
id|__bad_pda_field
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|pda_to_op
mdefine_line|#define pda_to_op(op,field,val) do { &bslash;&n;       switch (sizeof_field(struct x8664_pda, field)) { &t;&t;&bslash;&n;       case 2: asm volatile(op &quot;w %0,%%gs:&quot; __STR2(pda_ ## field) ::&quot;r&quot; (val):&quot;memory&quot;); break;&t;&bslash;&n;       case 4: asm volatile(op &quot;l %0,%%gs:&quot; __STR2(pda_ ## field) ::&quot;r&quot; (val):&quot;memory&quot;); break;&t;&bslash;&n;       case 8: asm volatile(op &quot;q %0,%%gs:&quot; __STR2(pda_ ## field) ::&quot;r&quot; (val):&quot;memory&quot;); break;&t;&bslash;&n;       default: __bad_pda_field(); &t;&t;&t;&t;&t;&bslash;&n;       } &bslash;&n;       } while (0)
DECL|macro|pda_from_op
mdefine_line|#define pda_from_op(op,field) ({ &bslash;&n;       typedef typeof_field(struct x8664_pda, field) T__; T__ ret__; &bslash;&n;       switch (sizeof_field(struct x8664_pda, field)) { &t;&t;&bslash;&n;       case 2: asm volatile (op &quot;w %%gs:&quot; __STR2(pda_ ## field) &quot;,%0&quot;:&quot;=r&quot; (ret__)::&quot;memory&quot;); break;&t;&bslash;&n;       case 4: asm volatile (op &quot;l %%gs:&quot; __STR2(pda_ ## field) &quot;,%0&quot;:&quot;=r&quot; (ret__)::&quot;memory&quot;); break;&t;&bslash;&n;       case 8: asm volatile (op &quot;q %%gs:&quot; __STR2(pda_ ## field) &quot;,%0&quot;:&quot;=r&quot; (ret__)::&quot;memory&quot;); break;&t;&bslash;&n;       default: __bad_pda_field(); &t;&t;&t;&t;&t;&bslash;&n;       } &bslash;&n;       ret__; })
DECL|macro|read_pda
mdefine_line|#define read_pda(field) pda_from_op(&quot;mov&quot;,field)
DECL|macro|write_pda
mdefine_line|#define write_pda(field,val) pda_to_op(&quot;mov&quot;,field,val)
DECL|macro|add_pda
mdefine_line|#define add_pda(field,val) pda_to_op(&quot;add&quot;,field,val)
DECL|macro|sub_pda
mdefine_line|#define sub_pda(field,val) pda_to_op(&quot;sub&quot;,field,val)
macro_line|#endif
eof
