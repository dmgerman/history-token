macro_line|#ifndef __ARCH_DESC_H
DECL|macro|__ARCH_DESC_H
mdefine_line|#define __ARCH_DESC_H
macro_line|#include &lt;asm/ldt.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
DECL|macro|CPU_16BIT_STACK_SIZE
mdefine_line|#define CPU_16BIT_STACK_SIZE 1024
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/preempt.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
r_extern
r_struct
id|desc_struct
id|cpu_gdt_table
(braket
id|GDT_ENTRIES
)braket
suffix:semicolon
id|DECLARE_PER_CPU
c_func
(paren
r_struct
id|desc_struct
comma
id|cpu_gdt_table
(braket
id|GDT_ENTRIES
)braket
)paren
suffix:semicolon
id|DECLARE_PER_CPU
c_func
(paren
r_int
r_char
comma
id|cpu_16bit_stack
(braket
id|CPU_16BIT_STACK_SIZE
)braket
)paren
suffix:semicolon
DECL|struct|Xgt_desc_struct
r_struct
id|Xgt_desc_struct
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|address
r_int
r_int
id|address
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|Xgt_desc_struct
id|idt_descr
comma
id|cpu_gdt_descr
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|load_TR_desc
mdefine_line|#define load_TR_desc() __asm__ __volatile__(&quot;ltr %%ax&quot;::&quot;a&quot; (GDT_ENTRY_TSS*8))
DECL|macro|load_LDT_desc
mdefine_line|#define load_LDT_desc() __asm__ __volatile__(&quot;lldt %%ax&quot;::&quot;a&quot; (GDT_ENTRY_LDT*8))
multiline_comment|/*&n; * This is the ldt that every process will get unless we need&n; * something other than this.&n; */
r_extern
r_struct
id|desc_struct
id|default_ldt
(braket
)braket
suffix:semicolon
r_extern
r_void
id|set_intr_gate
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|addr
)paren
suffix:semicolon
DECL|macro|_set_tssldt_desc
mdefine_line|#define _set_tssldt_desc(n,addr,limit,type) &bslash;&n;__asm__ __volatile__ (&quot;movw %w3,0(%2)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movw %%ax,2(%2)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%al,4(%2)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %4,5(%2)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb $0,6(%2)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%ah,7(%2)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%%eax&quot; &bslash;&n;&t;: &quot;=m&quot;(*(n)) : &quot;a&quot; (addr), &quot;r&quot;(n), &quot;ir&quot;(limit), &quot;i&quot;(type))
DECL|function|__set_tss_desc
r_static
r_inline
r_void
id|__set_tss_desc
c_func
(paren
r_int
r_int
id|cpu
comma
r_int
r_int
id|entry
comma
r_void
op_star
id|addr
)paren
(brace
id|_set_tssldt_desc
c_func
(paren
op_amp
id|per_cpu
c_func
(paren
id|cpu_gdt_table
comma
id|cpu
)paren
(braket
id|entry
)braket
comma
(paren
r_int
)paren
id|addr
comma
m_offsetof
(paren
r_struct
id|tss_struct
comma
id|__cacheline_filler
)paren
op_minus
l_int|1
comma
l_int|0x89
)paren
suffix:semicolon
)brace
DECL|macro|set_tss_desc
mdefine_line|#define set_tss_desc(cpu,addr) __set_tss_desc(cpu, GDT_ENTRY_TSS, addr)
DECL|function|set_ldt_desc
r_static
r_inline
r_void
id|set_ldt_desc
c_func
(paren
r_int
r_int
id|cpu
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|size
)paren
(brace
id|_set_tssldt_desc
c_func
(paren
op_amp
id|per_cpu
c_func
(paren
id|cpu_gdt_table
comma
id|cpu
)paren
(braket
id|GDT_ENTRY_LDT
)braket
comma
(paren
r_int
)paren
id|addr
comma
(paren
(paren
id|size
op_lshift
l_int|3
)paren
op_minus
l_int|1
)paren
comma
l_int|0x82
)paren
suffix:semicolon
)brace
DECL|macro|LDT_entry_a
mdefine_line|#define LDT_entry_a(info) &bslash;&n;&t;((((info)-&gt;base_addr &amp; 0x0000ffff) &lt;&lt; 16) | ((info)-&gt;limit &amp; 0x0ffff))
DECL|macro|LDT_entry_b
mdefine_line|#define LDT_entry_b(info) &bslash;&n;&t;(((info)-&gt;base_addr &amp; 0xff000000) | &bslash;&n;&t;(((info)-&gt;base_addr &amp; 0x00ff0000) &gt;&gt; 16) | &bslash;&n;&t;((info)-&gt;limit &amp; 0xf0000) | &bslash;&n;&t;(((info)-&gt;read_exec_only ^ 1) &lt;&lt; 9) | &bslash;&n;&t;((info)-&gt;contents &lt;&lt; 10) | &bslash;&n;&t;(((info)-&gt;seg_not_present ^ 1) &lt;&lt; 15) | &bslash;&n;&t;((info)-&gt;seg_32bit &lt;&lt; 22) | &bslash;&n;&t;((info)-&gt;limit_in_pages &lt;&lt; 23) | &bslash;&n;&t;((info)-&gt;useable &lt;&lt; 20) | &bslash;&n;&t;0x7000)
DECL|macro|LDT_empty
mdefine_line|#define LDT_empty(info) (&bslash;&n;&t;(info)-&gt;base_addr&t;== 0&t;&amp;&amp; &bslash;&n;&t;(info)-&gt;limit&t;&t;== 0&t;&amp;&amp; &bslash;&n;&t;(info)-&gt;contents&t;== 0&t;&amp;&amp; &bslash;&n;&t;(info)-&gt;read_exec_only&t;== 1&t;&amp;&amp; &bslash;&n;&t;(info)-&gt;seg_32bit&t;== 0&t;&amp;&amp; &bslash;&n;&t;(info)-&gt;limit_in_pages&t;== 0&t;&amp;&amp; &bslash;&n;&t;(info)-&gt;seg_not_present&t;== 1&t;&amp;&amp; &bslash;&n;&t;(info)-&gt;useable&t;&t;== 0&t;)
macro_line|#if TLS_SIZE != 24
macro_line|# error update this code.
macro_line|#endif
DECL|function|load_TLS
r_static
r_inline
r_void
id|load_TLS
c_func
(paren
r_struct
id|thread_struct
op_star
id|t
comma
r_int
r_int
id|cpu
)paren
(brace
DECL|macro|C
mdefine_line|#define C(i) per_cpu(cpu_gdt_table, cpu)[GDT_ENTRY_TLS_MIN + i] = t-&gt;tls_array[i]
id|C
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|C
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|C
c_func
(paren
l_int|2
)paren
suffix:semicolon
DECL|macro|C
macro_line|#undef C
)brace
DECL|function|clear_LDT
r_static
r_inline
r_void
id|clear_LDT
c_func
(paren
r_void
)paren
(brace
r_int
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
id|set_ldt_desc
c_func
(paren
id|cpu
comma
op_amp
id|default_ldt
(braket
l_int|0
)braket
comma
l_int|5
)paren
suffix:semicolon
id|load_LDT_desc
c_func
(paren
)paren
suffix:semicolon
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * load one particular LDT into the current CPU&n; */
DECL|function|load_LDT_nolock
r_static
r_inline
r_void
id|load_LDT_nolock
c_func
(paren
id|mm_context_t
op_star
id|pc
comma
r_int
id|cpu
)paren
(brace
r_void
op_star
id|segments
op_assign
id|pc-&gt;ldt
suffix:semicolon
r_int
id|count
op_assign
id|pc-&gt;size
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
id|count
)paren
)paren
(brace
id|segments
op_assign
op_amp
id|default_ldt
(braket
l_int|0
)braket
suffix:semicolon
id|count
op_assign
l_int|5
suffix:semicolon
)brace
id|set_ldt_desc
c_func
(paren
id|cpu
comma
id|segments
comma
id|count
)paren
suffix:semicolon
id|load_LDT_desc
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|load_LDT
r_static
r_inline
r_void
id|load_LDT
c_func
(paren
id|mm_context_t
op_star
id|pc
)paren
(brace
r_int
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
id|load_LDT_nolock
c_func
(paren
id|pc
comma
id|cpu
)paren
suffix:semicolon
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|get_desc_base
r_static
r_inline
r_int
r_int
id|get_desc_base
c_func
(paren
r_int
r_int
op_star
id|desc
)paren
(brace
r_int
r_int
id|base
suffix:semicolon
id|base
op_assign
(paren
(paren
id|desc
(braket
l_int|0
)braket
op_rshift
l_int|16
)paren
op_amp
l_int|0x0000ffff
)paren
op_or
(paren
(paren
id|desc
(braket
l_int|1
)braket
op_lshift
l_int|16
)paren
op_amp
l_int|0x00ff0000
)paren
op_or
(paren
id|desc
(braket
l_int|1
)braket
op_amp
l_int|0xff000000
)paren
suffix:semicolon
r_return
id|base
suffix:semicolon
)brace
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif
eof
