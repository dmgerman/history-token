multiline_comment|/* Written 2000 by Andi Kleen */
macro_line|#ifndef __ARCH_DESC_H
DECL|macro|__ARCH_DESC_H
mdefine_line|#define __ARCH_DESC_H
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/ldt.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
singleline_comment|// 8 byte segment descriptor
DECL|struct|desc_struct
r_struct
id|desc_struct
(brace
DECL|member|limit0
id|u16
id|limit0
suffix:semicolon
DECL|member|base0
id|u16
id|base0
suffix:semicolon
DECL|member|base1
DECL|member|type
DECL|member|s
DECL|member|dpl
DECL|member|p
r_int
id|base1
suffix:colon
l_int|8
comma
id|type
suffix:colon
l_int|4
comma
id|s
suffix:colon
l_int|1
comma
id|dpl
suffix:colon
l_int|2
comma
id|p
suffix:colon
l_int|1
suffix:semicolon
DECL|member|limit
DECL|member|avl
DECL|member|l
DECL|member|d
DECL|member|g
DECL|member|base2
r_int
id|limit
suffix:colon
l_int|4
comma
id|avl
suffix:colon
l_int|1
comma
id|l
suffix:colon
l_int|1
comma
id|d
suffix:colon
l_int|1
comma
id|g
suffix:colon
l_int|1
comma
id|base2
suffix:colon
l_int|8
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|n_desc_struct
r_struct
id|n_desc_struct
(brace
DECL|member|a
DECL|member|b
r_int
r_int
id|a
comma
id|b
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|desc_struct
id|cpu_gdt_table
(braket
id|NR_CPUS
)braket
(braket
id|GDT_ENTRIES
)braket
suffix:semicolon
r_enum
(brace
DECL|enumerator|GATE_INTERRUPT
id|GATE_INTERRUPT
op_assign
l_int|0xE
comma
DECL|enumerator|GATE_TRAP
id|GATE_TRAP
op_assign
l_int|0xF
comma
DECL|enumerator|GATE_CALL
id|GATE_CALL
op_assign
l_int|0xC
comma
)brace
suffix:semicolon
singleline_comment|// 16byte gate
DECL|struct|gate_struct
r_struct
id|gate_struct
(brace
DECL|member|offset_low
id|u16
id|offset_low
suffix:semicolon
DECL|member|segment
id|u16
id|segment
suffix:semicolon
DECL|member|ist
DECL|member|zero0
DECL|member|type
DECL|member|dpl
DECL|member|p
r_int
id|ist
suffix:colon
l_int|3
comma
id|zero0
suffix:colon
l_int|5
comma
id|type
suffix:colon
l_int|5
comma
id|dpl
suffix:colon
l_int|2
comma
id|p
suffix:colon
l_int|1
suffix:semicolon
DECL|member|offset_middle
id|u16
id|offset_middle
suffix:semicolon
DECL|member|offset_high
id|u32
id|offset_high
suffix:semicolon
DECL|member|zero1
id|u32
id|zero1
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|PTR_LOW
mdefine_line|#define PTR_LOW(x) ((unsigned long)(x) &amp; 0xFFFF) 
DECL|macro|PTR_MIDDLE
mdefine_line|#define PTR_MIDDLE(x) (((unsigned long)(x) &gt;&gt; 16) &amp; 0xFFFF)
DECL|macro|PTR_HIGH
mdefine_line|#define PTR_HIGH(x) ((unsigned long)(x) &gt;&gt; 32)
r_enum
(brace
DECL|enumerator|DESC_TSS
id|DESC_TSS
op_assign
l_int|0x9
comma
DECL|enumerator|DESC_LDT
id|DESC_LDT
op_assign
l_int|0x2
comma
)brace
suffix:semicolon
singleline_comment|// LDT or TSS descriptor in the GDT. 16 bytes.
DECL|struct|ldttss_desc
r_struct
id|ldttss_desc
(brace
DECL|member|limit0
id|u16
id|limit0
suffix:semicolon
DECL|member|base0
id|u16
id|base0
suffix:semicolon
DECL|member|base1
DECL|member|type
DECL|member|dpl
DECL|member|p
r_int
id|base1
suffix:colon
l_int|8
comma
id|type
suffix:colon
l_int|5
comma
id|dpl
suffix:colon
l_int|2
comma
id|p
suffix:colon
l_int|1
suffix:semicolon
DECL|member|limit1
DECL|member|zero0
DECL|member|g
DECL|member|base2
r_int
id|limit1
suffix:colon
l_int|4
comma
id|zero0
suffix:colon
l_int|3
comma
id|g
suffix:colon
l_int|1
comma
id|base2
suffix:colon
l_int|8
suffix:semicolon
DECL|member|base3
id|u32
id|base3
suffix:semicolon
DECL|member|zero1
id|u32
id|zero1
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|desc_ptr
r_struct
id|desc_ptr
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
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|load_TR_desc
mdefine_line|#define load_TR_desc() asm volatile(&quot;ltr %w0&quot;::&quot;r&quot; (GDT_ENTRY_TSS*8))
DECL|macro|load_LDT_desc
mdefine_line|#define load_LDT_desc() asm volatile(&quot;lldt %w0&quot;::&quot;r&quot; (GDT_ENTRY_LDT*8))
DECL|macro|clear_LDT
mdefine_line|#define clear_LDT()  asm volatile(&quot;lldt %w0&quot;::&quot;r&quot; (0))
multiline_comment|/*&n; * This is the ldt that every process will get unless we need&n; * something other than this.&n; */
r_extern
r_struct
id|desc_struct
id|default_ldt
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|gate_struct
id|idt_table
(braket
)braket
suffix:semicolon
DECL|function|_set_gate
r_static
r_inline
r_void
id|_set_gate
c_func
(paren
r_void
op_star
id|adr
comma
r_int
id|type
comma
r_int
r_int
id|func
comma
r_int
id|dpl
comma
r_int
id|ist
)paren
(brace
r_struct
id|gate_struct
id|s
suffix:semicolon
id|s.offset_low
op_assign
id|PTR_LOW
c_func
(paren
id|func
)paren
suffix:semicolon
id|s.segment
op_assign
id|__KERNEL_CS
suffix:semicolon
id|s.ist
op_assign
id|ist
suffix:semicolon
id|s.p
op_assign
l_int|1
suffix:semicolon
id|s.dpl
op_assign
id|dpl
suffix:semicolon
id|s.zero0
op_assign
l_int|0
suffix:semicolon
id|s.zero1
op_assign
l_int|0
suffix:semicolon
id|s.type
op_assign
id|type
suffix:semicolon
id|s.offset_middle
op_assign
id|PTR_MIDDLE
c_func
(paren
id|func
)paren
suffix:semicolon
id|s.offset_high
op_assign
id|PTR_HIGH
c_func
(paren
id|func
)paren
suffix:semicolon
multiline_comment|/* does not need to be atomic because it is only done once at setup time */
id|memcpy
c_func
(paren
id|adr
comma
op_amp
id|s
comma
l_int|16
)paren
suffix:semicolon
)brace
DECL|function|set_intr_gate
r_static
r_inline
r_void
id|set_intr_gate
c_func
(paren
r_int
id|nr
comma
r_void
op_star
id|func
)paren
(brace
id|_set_gate
c_func
(paren
op_amp
id|idt_table
(braket
id|nr
)braket
comma
id|GATE_INTERRUPT
comma
(paren
r_int
r_int
)paren
id|func
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|set_intr_gate_ist
r_static
r_inline
r_void
id|set_intr_gate_ist
c_func
(paren
r_int
id|nr
comma
r_void
op_star
id|func
comma
r_int
id|ist
)paren
(brace
id|_set_gate
c_func
(paren
op_amp
id|idt_table
(braket
id|nr
)braket
comma
id|GATE_INTERRUPT
comma
(paren
r_int
r_int
)paren
id|func
comma
l_int|0
comma
id|ist
)paren
suffix:semicolon
)brace
DECL|function|set_system_gate
r_static
r_inline
r_void
id|set_system_gate
c_func
(paren
r_int
id|nr
comma
r_void
op_star
id|func
)paren
(brace
id|_set_gate
c_func
(paren
op_amp
id|idt_table
(braket
id|nr
)braket
comma
id|GATE_INTERRUPT
comma
(paren
r_int
r_int
)paren
id|func
comma
l_int|3
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|set_tssldt_descriptor
r_static
r_inline
r_void
id|set_tssldt_descriptor
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
r_int
id|tss
comma
r_int
id|type
comma
r_int
id|size
)paren
(brace
r_struct
id|ldttss_desc
id|d
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|d
comma
l_int|0
comma
r_sizeof
(paren
id|d
)paren
)paren
suffix:semicolon
id|d.limit0
op_assign
id|size
op_amp
l_int|0xFFFF
suffix:semicolon
id|d.base0
op_assign
id|PTR_LOW
c_func
(paren
id|tss
)paren
suffix:semicolon
id|d.base1
op_assign
id|PTR_MIDDLE
c_func
(paren
id|tss
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|d.type
op_assign
id|type
suffix:semicolon
id|d.p
op_assign
l_int|1
suffix:semicolon
id|d.limit1
op_assign
(paren
id|size
op_rshift
l_int|16
)paren
op_amp
l_int|0xF
suffix:semicolon
id|d.base2
op_assign
(paren
id|PTR_MIDDLE
c_func
(paren
id|tss
)paren
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|d.base3
op_assign
id|PTR_HIGH
c_func
(paren
id|tss
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ptr
comma
op_amp
id|d
comma
l_int|16
)paren
suffix:semicolon
)brace
DECL|function|set_tss_desc
r_static
r_inline
r_void
id|set_tss_desc
c_func
(paren
r_int
id|cpu
comma
r_void
op_star
id|addr
)paren
(brace
id|set_tssldt_descriptor
c_func
(paren
op_amp
id|cpu_gdt_table
(braket
id|cpu
)braket
(braket
id|GDT_ENTRY_TSS
)braket
comma
(paren
r_int
r_int
)paren
id|addr
comma
id|DESC_TSS
comma
r_sizeof
(paren
r_struct
id|tss_struct
)paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|set_ldt_desc
r_static
r_inline
r_void
id|set_ldt_desc
c_func
(paren
r_int
id|cpu
comma
r_void
op_star
id|addr
comma
r_int
id|size
)paren
(brace
id|set_tssldt_descriptor
c_func
(paren
op_amp
id|cpu_gdt_table
(braket
id|cpu
)braket
(braket
id|GDT_ENTRY_LDT
)braket
comma
(paren
r_int
r_int
)paren
id|addr
comma
id|DESC_LDT
comma
id|size
op_star
l_int|8
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|set_seg_base
r_static
r_inline
r_void
id|set_seg_base
c_func
(paren
r_int
id|cpu
comma
r_int
id|entry
comma
r_void
op_star
id|base
)paren
(brace
r_struct
id|desc_struct
op_star
id|d
op_assign
op_amp
id|cpu_gdt_table
(braket
id|cpu
)braket
(braket
id|entry
)braket
suffix:semicolon
id|u32
id|addr
op_assign
(paren
id|u32
)paren
(paren
id|u64
)paren
id|base
suffix:semicolon
id|BUG_ON
c_func
(paren
(paren
id|u64
)paren
id|base
op_rshift
l_int|32
)paren
suffix:semicolon
id|d-&gt;base0
op_assign
id|addr
op_amp
l_int|0xffff
suffix:semicolon
id|d-&gt;base1
op_assign
(paren
id|addr
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|d-&gt;base2
op_assign
(paren
id|addr
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
suffix:semicolon
)brace
DECL|macro|LDT_entry_a
mdefine_line|#define LDT_entry_a(info) &bslash;&n;&t;((((info)-&gt;base_addr &amp; 0x0000ffff) &lt;&lt; 16) | ((info)-&gt;limit &amp; 0x0ffff))
multiline_comment|/* Don&squot;t allow setting of the lm bit. It is useless anyways because &n;   64bit system calls require __USER_CS. */
DECL|macro|LDT_entry_b
mdefine_line|#define LDT_entry_b(info) &bslash;&n;&t;(((info)-&gt;base_addr &amp; 0xff000000) | &bslash;&n;&t;(((info)-&gt;base_addr &amp; 0x00ff0000) &gt;&gt; 16) | &bslash;&n;&t;((info)-&gt;limit &amp; 0xf0000) | &bslash;&n;&t;(((info)-&gt;read_exec_only ^ 1) &lt;&lt; 9) | &bslash;&n;&t;((info)-&gt;contents &lt;&lt; 10) | &bslash;&n;&t;(((info)-&gt;seg_not_present ^ 1) &lt;&lt; 15) | &bslash;&n;&t;((info)-&gt;seg_32bit &lt;&lt; 22) | &bslash;&n;&t;((info)-&gt;limit_in_pages &lt;&lt; 23) | &bslash;&n;&t;((info)-&gt;useable &lt;&lt; 20) | &bslash;&n;&t;/* ((info)-&gt;lm &lt;&lt; 21) | */ &bslash;&n;&t;0x7000)
DECL|macro|LDT_empty
mdefine_line|#define LDT_empty(info) (&bslash;&n;&t;(info)-&gt;base_addr&t;== 0&t;&amp;&amp; &bslash;&n;&t;(info)-&gt;limit&t;&t;== 0&t;&amp;&amp; &bslash;&n;&t;(info)-&gt;contents&t;== 0&t;&amp;&amp; &bslash;&n;&t;(info)-&gt;read_exec_only&t;== 1&t;&amp;&amp; &bslash;&n;&t;(info)-&gt;seg_32bit&t;== 0&t;&amp;&amp; &bslash;&n;&t;(info)-&gt;limit_in_pages&t;== 0&t;&amp;&amp; &bslash;&n;&t;(info)-&gt;seg_not_present&t;== 1&t;&amp;&amp; &bslash;&n;&t;(info)-&gt;useable&t;&t;== 0&t;&amp;&amp; &bslash;&n;&t;(info)-&gt;lm&t;&t;== 0)
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
id|u64
op_star
id|gdt
op_assign
(paren
id|u64
op_star
)paren
(paren
id|cpu_gdt_table
(braket
id|cpu
)braket
op_plus
id|GDT_ENTRY_TLS_MIN
)paren
suffix:semicolon
id|gdt
(braket
l_int|0
)braket
op_assign
id|t-&gt;tls_array
(braket
l_int|0
)braket
suffix:semicolon
id|gdt
(braket
l_int|1
)braket
op_assign
id|t-&gt;tls_array
(braket
l_int|1
)braket
suffix:semicolon
id|gdt
(braket
l_int|2
)braket
op_assign
id|t-&gt;tls_array
(braket
l_int|2
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * load one particular LDT into the current CPU&n; */
DECL|function|load_LDT_nolock
r_extern
r_inline
r_void
id|load_LDT_nolock
(paren
id|mm_context_t
op_star
id|pc
comma
r_int
id|cpu
)paren
(brace
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
id|clear_LDT
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|set_ldt_desc
c_func
(paren
id|cpu
comma
id|pc-&gt;ldt
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
r_extern
r_struct
id|desc_ptr
id|idt_descr
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif
eof
