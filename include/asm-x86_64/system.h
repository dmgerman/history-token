macro_line|#ifndef __ASM_SYSTEM_H
DECL|macro|__ASM_SYSTEM_H
mdefine_line|#define __ASM_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_SMP
DECL|macro|LOCK_PREFIX
mdefine_line|#define LOCK_PREFIX &quot;lock ; &quot;
macro_line|#else
DECL|macro|LOCK_PREFIX
mdefine_line|#define LOCK_PREFIX &quot;&quot;
macro_line|#endif
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
DECL|macro|STR
mdefine_line|#define STR(x) __STR(x)
DECL|macro|__SAVE
mdefine_line|#define __SAVE(reg,offset) &quot;movq %%&quot; #reg &quot;,(14-&quot; #offset &quot;)*8(%%rsp)&bslash;n&bslash;t&quot;
DECL|macro|__RESTORE
mdefine_line|#define __RESTORE(reg,offset) &quot;movq (14-&quot; #offset &quot;)*8(%%rsp),%%&quot; #reg &quot;&bslash;n&bslash;t&quot;
multiline_comment|/* frame pointer must be last for get_wchan */
DECL|macro|SAVE_CONTEXT
mdefine_line|#define SAVE_CONTEXT    &quot;pushfq ; pushq %%rbp ; movq %%rsi,%%rbp&bslash;n&bslash;t&quot;
DECL|macro|RESTORE_CONTEXT
mdefine_line|#define RESTORE_CONTEXT &quot;movq %%rbp,%%rsi ; popq %%rbp ; popfq&bslash;n&bslash;t&quot; 
DECL|macro|__EXTRA_CLOBBER
mdefine_line|#define __EXTRA_CLOBBER  &bslash;&n;&t;,&quot;rcx&quot;,&quot;rbx&quot;,&quot;rdx&quot;,&quot;r8&quot;,&quot;r9&quot;,&quot;r10&quot;,&quot;r11&quot;,&quot;r12&quot;,&quot;r13&quot;,&quot;r14&quot;,&quot;r15&quot;
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last) &bslash;&n;&t;asm volatile(SAVE_CONTEXT&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;&t;     &quot;movq %%rsp,%P[threadrsp](%[prev])&bslash;n&bslash;t&quot; /* save RSP */&t;  &bslash;&n;&t;&t;     &quot;movq %P[threadrsp](%[next]),%%rsp&bslash;n&bslash;t&quot; /* restore RSP */&t;  &bslash;&n;&t;&t;     &quot;call __switch_to&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;  &bslash;&n;&t;&t;     &quot;.globl thread_return&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;thread_return:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;    &bslash;&n;&t;&t;     &quot;movq %%gs:%P[pda_pcurrent],%%rsi&bslash;n&bslash;t&quot;&t;&t;&t;  &bslash;&n;&t;&t;     &quot;movq %P[thread_info](%%rsi),%%r8&bslash;n&bslash;t&quot;&t;&t;&t;  &bslash;&n;&t;&t;     LOCK &quot;btr  %[tif_fork],%P[ti_flags](%%r8)&bslash;n&bslash;t&quot;&t;&t;  &bslash;&n;&t;&t;     &quot;movq %%rax,%%rdi&bslash;n&bslash;t&quot; &t;&t;&t;&t;&t;  &bslash;&n;&t;&t;     &quot;jc   ret_from_fork&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;  &bslash;&n;&t;&t;     RESTORE_CONTEXT&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;&t;     : &quot;=a&quot; (last)&t;&t;&t;&t;&t;  &t;  &bslash;&n;&t;&t;     : [next] &quot;S&quot; (next), [prev] &quot;D&quot; (prev),&t;&t;&t;  &bslash;&n;&t;&t;       [threadrsp] &quot;i&quot; (offsetof(struct task_struct, thread.rsp)), &bslash;&n;&t;&t;       [ti_flags] &quot;i&quot; (offsetof(struct thread_info, flags)),&bslash;&n;&t;&t;       [tif_fork] &quot;i&quot; (TIF_FORK),&t;&t;&t;  &bslash;&n;&t;&t;       [thread_info] &quot;i&quot; (offsetof(struct task_struct, thread_info)), &bslash;&n;&t;&t;       [pda_pcurrent] &quot;i&quot; (offsetof(struct x8664_pda, pcurrent))   &bslash;&n;&t;&t;     : &quot;memory&quot;, &quot;cc&quot; __EXTRA_CLOBBER)
r_extern
r_void
id|load_gs_index
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Load a segment. Fall back on loading the zero&n; * segment if something goes wrong..&n; */
DECL|macro|loadsegment
mdefine_line|#define loadsegment(seg,value)&t;&bslash;&n;&t;asm volatile(&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;movl %k0,%%&quot; #seg &quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;3:&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;movl %1,%%&quot; #seg &quot;&bslash;n&bslash;t&quot; &t;&bslash;&n;&t;&t;&quot;jmp 2b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;.align 8&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.quad 1b,3b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&bslash;&n;&t;&t;: :&quot;r&quot; (value), &quot;r&quot; (0))
DECL|macro|set_debug
mdefine_line|#define set_debug(value,register) &bslash;&n;                __asm__(&quot;movq %0,%%db&quot; #register  &bslash;&n;&t;&t;: /* no output */ &bslash;&n;&t;&t;:&quot;r&quot; ((unsigned long) value))
macro_line|#ifdef __KERNEL__
DECL|struct|alt_instr
r_struct
id|alt_instr
(brace
DECL|member|instr
id|__u8
op_star
id|instr
suffix:semicolon
multiline_comment|/* original instruction */
DECL|member|replacement
id|__u8
op_star
id|replacement
suffix:semicolon
DECL|member|cpuid
id|__u8
id|cpuid
suffix:semicolon
multiline_comment|/* cpuid bit set for replacement */
DECL|member|instrlen
id|__u8
id|instrlen
suffix:semicolon
multiline_comment|/* length of original instruction */
DECL|member|replacementlen
id|__u8
id|replacementlen
suffix:semicolon
multiline_comment|/* length of new instruction, &lt;= instrlen */
DECL|member|pad
id|__u8
id|pad
(braket
l_int|5
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Alternative instructions for different CPU types or capabilities.&n; * &n; * This allows to use optimized instructions even on generic binary&n; * kernels.&n; * &n; * length of oldinstr must be longer or equal the length of newinstr&n; * It can be padded with nops as needed.&n; * &n; * For non barrier like inlines please define new variants&n; * without volatile and memory clobber.&n; */
DECL|macro|alternative
mdefine_line|#define alternative(oldinstr, newinstr, feature) &t;&bslash;&n;&t;asm volatile (&quot;661:&bslash;n&bslash;t&quot; oldinstr &quot;&bslash;n662:&bslash;n&quot; &t;&t;     &bslash;&n;&t;&t;      &quot;.section .altinstructions,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;     &t;     &bslash;&n;&t;&t;      &quot;  .align 8&bslash;n&quot;&t;&t;&t;&t;       &bslash;&n;&t;&t;      &quot;  .quad 661b&bslash;n&quot;            /* label */          &bslash;&n;&t;&t;      &quot;  .quad 663f&bslash;n&quot;&t;&t;  /* new instruction */ &bslash;&n;&t;&t;      &quot;  .byte %c0&bslash;n&quot;             /* feature bit */    &bslash;&n;&t;&t;      &quot;  .byte 662b-661b&bslash;n&quot;       /* sourcelen */      &bslash;&n;&t;&t;      &quot;  .byte 664f-663f&bslash;n&quot;       /* replacementlen */ &bslash;&n;&t;&t;      &quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;      &quot;.section .altinstr_replacement,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;      &quot;663:&bslash;n&bslash;t&quot; newinstr &quot;&bslash;n664:&bslash;n&quot;   /* replacement */ &bslash;&n;&t;&t;      &quot;.previous&quot; :: &quot;i&quot; (feature) : &quot;memory&quot;)  
multiline_comment|/*&n; * Alternative inline assembly with input.&n; * &n; * Pecularities:&n; * No memory clobber here. &n; * Argument numbers start with 1.&n; * Best is to use constraints that are fixed size (like (%1) ... &quot;r&quot;)&n; * If you use variable sized constraints like &quot;m&quot; or &quot;g&quot; in the &n; * replacement maake sure to pad to the worst case length.&n; */
DECL|macro|alternative_input
mdefine_line|#define alternative_input(oldinstr, newinstr, feature, input...)&t;&bslash;&n;&t;asm volatile (&quot;661:&bslash;n&bslash;t&quot; oldinstr &quot;&bslash;n662:&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;      &quot;.section .altinstructions,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;      &quot;  .align 8&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;      &quot;  .quad 661b&bslash;n&quot;            /* label */&t;&t;&bslash;&n;&t;&t;      &quot;  .quad 663f&bslash;n&quot;&t;&t;  /* new instruction */&t;&bslash;&n;&t;&t;      &quot;  .byte %c0&bslash;n&quot;             /* feature bit */&t;&bslash;&n;&t;&t;      &quot;  .byte 662b-661b&bslash;n&quot;       /* sourcelen */&t;&bslash;&n;&t;&t;      &quot;  .byte 664f-663f&bslash;n&quot;       /* replacementlen */&t;&bslash;&n;&t;&t;      &quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;      &quot;.section .altinstr_replacement,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;      &quot;663:&bslash;n&bslash;t&quot; newinstr &quot;&bslash;n664:&bslash;n&quot;   /* replacement */ &bslash;&n;&t;&t;      &quot;.previous&quot; :: &quot;i&quot; (feature), ##input)
multiline_comment|/*&n; * Clear and set &squot;TS&squot; bit respectively&n; */
DECL|macro|clts
mdefine_line|#define clts() __asm__ __volatile__ (&quot;clts&quot;)
DECL|function|read_cr0
r_static
r_inline
r_int
r_int
id|read_cr0
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|cr0
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movq %%cr0,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr0
)paren
)paren
suffix:semicolon
r_return
id|cr0
suffix:semicolon
)brace
DECL|function|write_cr0
r_static
r_inline
r_void
id|write_cr0
c_func
(paren
r_int
r_int
id|val
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;movq %0,%%cr0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
DECL|function|read_cr3
r_static
r_inline
r_int
r_int
id|read_cr3
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|cr3
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movq %%cr3,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr3
)paren
)paren
suffix:semicolon
r_return
id|cr3
suffix:semicolon
)brace
DECL|function|read_cr4
r_static
r_inline
r_int
r_int
id|read_cr4
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|cr4
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movq %%cr4,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr4
)paren
)paren
suffix:semicolon
r_return
id|cr4
suffix:semicolon
)brace
DECL|function|write_cr4
r_static
r_inline
r_void
id|write_cr4
c_func
(paren
r_int
r_int
id|val
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;movq %0,%%cr4&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
DECL|macro|stts
mdefine_line|#define stts() write_cr0(8 | read_cr0())
DECL|macro|wbinvd
mdefine_line|#define wbinvd() &bslash;&n;&t;__asm__ __volatile__ (&quot;wbinvd&quot;: : :&quot;memory&quot;);
macro_line|#endif&t;/* __KERNEL__ */
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__ (&quot;nop&quot;)
DECL|macro|xchg
mdefine_line|#define xchg(ptr,v) ((__typeof__(*(ptr)))__xchg((unsigned long)(v),(ptr),sizeof(*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr),1))
DECL|macro|__xg
mdefine_line|#define __xg(x) ((volatile long *)(x))
DECL|function|set_64bit
r_extern
r_inline
r_void
id|set_64bit
c_func
(paren
r_volatile
r_int
r_int
op_star
id|ptr
comma
r_int
r_int
id|val
)paren
(brace
op_star
id|ptr
op_assign
id|val
suffix:semicolon
)brace
DECL|macro|_set_64bit
mdefine_line|#define _set_64bit set_64bit
multiline_comment|/*&n; * Note: no &quot;lock&quot; prefix even on SMP: xchg always implies lock anyway&n; * Note 2: xchg has side effect, so that attribute volatile is necessary,&n; *&t;  but generally the primitive is invalid, *ptr is output argument. --ANK&n; */
DECL|function|__xchg
r_static
r_inline
r_int
r_int
id|__xchg
c_func
(paren
r_int
r_int
id|x
comma
r_volatile
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;xchgb %b0,%1&quot;
suffix:colon
l_string|&quot;=q&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
comma
l_string|&quot;0&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;xchgw %w0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
comma
l_string|&quot;0&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;xchgl %k0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
comma
l_string|&quot;0&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;xchgq %0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
comma
l_string|&quot;0&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|x
suffix:semicolon
)brace
multiline_comment|/*&n; * Atomic compare and exchange.  Compare OLD with MEM, if identical,&n; * store NEW in MEM.  Return the initial value in MEM.  Success is&n; * indicated by comparing RETURN with OLD.&n; */
DECL|macro|__HAVE_ARCH_CMPXCHG
mdefine_line|#define __HAVE_ARCH_CMPXCHG 1
DECL|function|__cmpxchg
r_static
r_inline
r_int
r_int
id|__cmpxchg
c_func
(paren
r_volatile
r_void
op_star
id|ptr
comma
r_int
r_int
id|old
comma
r_int
r_int
r_new
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|prev
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK_PREFIX
l_string|&quot;cmpxchgb %b1,%2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|prev
)paren
suffix:colon
l_string|&quot;q&quot;
(paren
r_new
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
comma
l_string|&quot;0&quot;
(paren
id|old
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|prev
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK_PREFIX
l_string|&quot;cmpxchgw %w1,%2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|prev
)paren
suffix:colon
l_string|&quot;q&quot;
(paren
r_new
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
comma
l_string|&quot;0&quot;
(paren
id|old
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|prev
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK_PREFIX
l_string|&quot;cmpxchgl %k1,%2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|prev
)paren
suffix:colon
l_string|&quot;q&quot;
(paren
r_new
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
comma
l_string|&quot;0&quot;
(paren
id|old
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|prev
suffix:semicolon
r_case
l_int|8
suffix:colon
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK_PREFIX
l_string|&quot;cmpxchgq %1,%2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|prev
)paren
suffix:colon
l_string|&quot;q&quot;
(paren
r_new
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
comma
l_string|&quot;0&quot;
(paren
id|old
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|prev
suffix:semicolon
)brace
r_return
id|old
suffix:semicolon
)brace
DECL|macro|cmpxchg
mdefine_line|#define cmpxchg(ptr,o,n)&bslash;&n;&t;((__typeof__(*(ptr)))__cmpxchg((ptr),(unsigned long)(o),&bslash;&n;&t;&t;&t;&t;&t;(unsigned long)(n),sizeof(*(ptr))))
macro_line|#ifdef CONFIG_SMP
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;mb()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;rmb()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;wmb()
DECL|macro|smp_read_barrier_depends
mdefine_line|#define smp_read_barrier_depends()&t;do {} while(0)
macro_line|#else
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;barrier()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;barrier()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;barrier()
DECL|macro|smp_read_barrier_depends
mdefine_line|#define smp_read_barrier_depends()&t;do {} while(0)
macro_line|#endif
multiline_comment|/*&n; * Force strict CPU ordering.&n; * And yes, this is required on UP too when we&squot;re talking&n; * to devices.&n; */
DECL|macro|mb
mdefine_line|#define mb() &t;asm volatile(&quot;mfence&quot;:::&quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb()&t;asm volatile(&quot;lfence&quot;:::&quot;memory&quot;)
macro_line|#ifdef CONFIG_UNORDERED_IO
DECL|macro|wmb
mdefine_line|#define wmb()&t;asm volatile(&quot;sfence&quot; ::: &quot;memory&quot;)
macro_line|#else
DECL|macro|wmb
mdefine_line|#define wmb()&t;asm volatile(&quot;&quot; ::: &quot;memory&quot;)
macro_line|#endif
DECL|macro|read_barrier_depends
mdefine_line|#define read_barrier_depends()&t;do {} while(0)
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value) do { xchg(&amp;var, value); } while (0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value) do { var = value; wmb(); } while (0)
DECL|macro|warn_if_not_ulong
mdefine_line|#define warn_if_not_ulong(x) do { unsigned long foo; (void) (&amp;(x) == &amp;foo); } while (0)
multiline_comment|/* interrupt control.. */
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(x)&t;do { warn_if_not_ulong(x); __asm__ __volatile__(&quot;# save_flags &bslash;n&bslash;t pushfq ; popq %q0&quot;:&quot;=g&quot; (x): /* no input */ :&quot;memory&quot;); } while (0)
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x) &t;__asm__ __volatile__(&quot;# restore_flags &bslash;n&bslash;t pushq %0 ; popfq&quot;: /* no output */ :&quot;g&quot; (x):&quot;memory&quot;, &quot;cc&quot;)
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable() &t;__asm__ __volatile__(&quot;cli&quot;: : :&quot;memory&quot;)
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()&t;__asm__ __volatile__(&quot;sti&quot;: : :&quot;memory&quot;)
multiline_comment|/* used in the idle loop; sti takes one instruction cycle to complete */
DECL|macro|safe_halt
mdefine_line|#define safe_halt()&t;&t;__asm__ __volatile__(&quot;sti; hlt&quot;: : :&quot;memory&quot;)
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&bslash;&n;&t;local_save_flags(flags);&t;&bslash;&n;&t;!(flags &amp; (1&lt;&lt;9));&t;&t;&bslash;&n;})
multiline_comment|/* For spinlocks etc */
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x) &t;do { warn_if_not_ulong(x); __asm__ __volatile__(&quot;# local_irq_save &bslash;n&bslash;t pushfq ; popq %0 ; cli&quot;:&quot;=g&quot; (x): /* no input */ :&quot;memory&quot;); } while (0)
r_void
id|cpu_idle_wait
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * disable hlt during certain critical i/o operations&n; */
DECL|macro|HAVE_DISABLE_HLT
mdefine_line|#define HAVE_DISABLE_HLT
r_void
id|disable_hlt
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|enable_hlt
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|HAVE_EAT_KEY
mdefine_line|#define HAVE_EAT_KEY
r_void
id|eat_key
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
