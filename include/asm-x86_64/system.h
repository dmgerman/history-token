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
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/* one of the stranger aspects of C forward declarations.. */
r_extern
r_void
id|__switch_to
c_func
(paren
r_struct
id|task_struct
op_star
id|prev
comma
r_struct
id|task_struct
op_star
id|next
)paren
suffix:semicolon
DECL|macro|prepare_to_switch
mdefine_line|#define prepare_to_switch()&t;do { } while(0)
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last) do {&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile(&quot;pushq %%rbp&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;pushq %%rbx&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;pushq %%r8&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;pushq %%r9&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;pushq %%r10&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;pushq %%r11&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;pushq %%r12&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;pushq %%r13&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;pushq %%r14&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;pushq %%r15&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;movq %%rsp,%0&bslash;n&bslash;t&quot;&t;/* save RSP */&t;&t;&bslash;&n;&t;&t;     &quot;movq %3,%%rsp&bslash;n&bslash;t&quot;&t;/* restore RSP */&t;&bslash;&n;&t;&t;     &quot;leaq 1f(%%rip),%%rbp&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;movq %%rbp,%1&bslash;n&bslash;t&quot;&t;/* save RIP */&t;&t;&bslash;&n;&t;&t;     &quot;pushq %4&bslash;n&bslash;t&quot;&t;&t;/* setup new RIP */&t;&bslash;&n;&t;&t;     &quot;jmp __switch_to&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;     &quot;1:&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;     &quot;popq %%r15&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;popq %%r14&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;popq %%r13&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;popq %%r12&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;popq %%r11&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;popq %%r10&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;popq %%r9&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;popq %%r8&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;popq %%rbx&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;popq %%rbp&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     :&quot;=m&quot; (prev-&gt;thread.rsp),&quot;=m&quot; (prev-&gt;thread.rip),&t;&bslash;&n;&t;&t;      &quot;=b&quot; (last)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     :&quot;m&quot; (next-&gt;thread.rsp),&quot;m&quot; (next-&gt;thread.rip),&t;&bslash;&n;&t;&t;      &quot;b&quot; (prev), &quot;S&quot; (next), &quot;D&quot; (prev));&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Load a segment. Fall back on loading the zero&n; * segment if something goes wrong..&n; */
DECL|macro|loadsegment
mdefine_line|#define loadsegment(seg,value)&t;do { int v = value;&t;&bslash;&n;&t;asm volatile(&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;movl %0,%%&quot; #seg &quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;3:&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;pushq $0 ; popq %% &quot; #seg &quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;jmp 2b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;.align 4&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.quad 1b,3b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&bslash;&n;&t;&t;: :&quot;r&quot; (v)); } while(0)
DECL|macro|set_debug
mdefine_line|#define set_debug(value,register) &bslash;&n;                __asm__(&quot;movq %0,%%db&quot; #register  &bslash;&n;&t;&t;: /* no output */ &bslash;&n;&t;&t;:&quot;r&quot; ((unsigned long) value))
multiline_comment|/*&n; * Clear and set &squot;TS&squot; bit respectively&n; */
DECL|macro|clts
mdefine_line|#define clts() __asm__ __volatile__ (&quot;clts&quot;)
DECL|macro|read_cr0
mdefine_line|#define read_cr0() ({ &bslash;&n;&t;unsigned long __dummy; &bslash;&n;&t;__asm__( &bslash;&n;&t;&t;&quot;movq %%cr0,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;:&quot;=r&quot; (__dummy)); &bslash;&n;&t;__dummy; &bslash;&n;})
DECL|macro|write_cr0
mdefine_line|#define write_cr0(x) &bslash;&n;&t;__asm__(&quot;movq %0,%%cr0&quot;: :&quot;r&quot; (x));
DECL|macro|read_cr4
mdefine_line|#define read_cr4() ({ &bslash;&n;&t;unsigned long __dummy; &bslash;&n;&t;__asm__( &bslash;&n;&t;&t;&quot;movq %%cr4,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;:&quot;=r&quot; (__dummy)); &bslash;&n;&t;__dummy; &bslash;&n;})
DECL|macro|write_cr4
mdefine_line|#define write_cr4(x) &bslash;&n;&t;__asm__(&quot;movq %0,%%cr4&quot;: :&quot;r&quot; (x));
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
macro_line|#else
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;barrier()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;barrier()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;barrier()
macro_line|#endif
multiline_comment|/*&n; * Force strict CPU ordering.&n; * And yes, this is required on UP too when we&squot;re talking&n; * to devices.&n; *&n; * For now, &quot;wmb()&quot; doesn&squot;t actually do anything, as all&n; * Intel CPU&squot;s follow what Intel calls a *Processor Order*,&n; * in which all writes are seen in the program order even&n; * outside the CPU.&n; *&n; * I expect future Intel CPU&squot;s to have a weaker ordering,&n; * but I&squot;d also expect them to finally get their act together&n; * and add some real memory barriers if so.&n; */
DECL|macro|mb
mdefine_line|#define mb() &t;__asm__ __volatile__ (&quot;lock; addl $0,0(%%rsp)&quot;: : :&quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb()&t;mb()
DECL|macro|wmb
mdefine_line|#define wmb()&t;__asm__ __volatile__ (&quot;&quot;: : :&quot;memory&quot;)
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value) do { xchg(&amp;var, value); } while (0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value) do { var = value; wmb(); } while (0)
multiline_comment|/* interrupt control.. */
DECL|macro|__save_flags
mdefine_line|#define __save_flags(x)&t;&t;__asm__ __volatile__(&quot;# save_flags &bslash;n&bslash;t pushfq ; popq %q0&quot;:&quot;=g&quot; (x): /* no input */ :&quot;memory&quot;)
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(x) &t;__asm__ __volatile__(&quot;# restore_flags &bslash;n&bslash;t pushq %0 ; popfq&quot;: /* no output */ :&quot;g&quot; (x):&quot;memory&quot;, &quot;cc&quot;)
DECL|macro|__cli
mdefine_line|#define __cli() &t;&t;__asm__ __volatile__(&quot;cli&quot;: : :&quot;memory&quot;)
DECL|macro|__sti
mdefine_line|#define __sti()&t;&t;&t;__asm__ __volatile__(&quot;sti&quot;: : :&quot;memory&quot;)
multiline_comment|/* used in the idle loop; sti takes one instruction cycle to complete */
DECL|macro|safe_halt
mdefine_line|#define safe_halt()&t;&t;__asm__ __volatile__(&quot;sti; hlt&quot;: : :&quot;memory&quot;)
multiline_comment|/* For spinlocks etc */
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x)&t;__asm__ __volatile__(&quot;# local_irq_save &bslash;n&bslash;t pushfq ; popq %0 ; cli&quot;:&quot;=g&quot; (x): /* no input */ :&quot;memory&quot;)
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x)&t;__asm__ __volatile__(&quot;# local_irq_restore &bslash;n&bslash;t pushq %0 ; popfq&quot;: /* no output */ :&quot;g&quot; (x):&quot;memory&quot;)
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable()&t;__asm__ __volatile__(&quot;cli&quot;: : :&quot;memory&quot;)
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()&t;__asm__ __volatile__(&quot;sti&quot;: : :&quot;memory&quot;)
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|__global_cli
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__global_sti
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__global_save_flags
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__global_restore_flags
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|cli
mdefine_line|#define cli() __global_cli()
DECL|macro|sti
mdefine_line|#define sti() __global_sti()
DECL|macro|save_flags
mdefine_line|#define save_flags(x) ((x)=__global_save_flags())
DECL|macro|restore_flags
mdefine_line|#define restore_flags(x) __global_restore_flags(x)
macro_line|#else
DECL|macro|cli
mdefine_line|#define cli() __cli()
DECL|macro|sti
mdefine_line|#define sti() __sti()
DECL|macro|save_flags
mdefine_line|#define save_flags(x) __save_flags(x)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(x) __restore_flags(x)
macro_line|#endif
DECL|macro|icebp
mdefine_line|#define icebp() asm volatile(&quot;xchg %bx,%bx&quot;)
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
macro_line|#endif
eof
