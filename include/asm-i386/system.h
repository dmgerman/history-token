macro_line|#ifndef __ASM_SYSTEM_H
DECL|macro|__ASM_SYSTEM_H
mdefine_line|#define __ASM_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/bitops.h&gt; /* for LOCK_PREFIX */
macro_line|#ifdef __KERNEL__
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/* one of the stranger aspects of C forward declarations.. */
r_extern
r_void
id|FASTCALL
c_func
(paren
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
)paren
suffix:semicolon
DECL|macro|prepare_to_switch
mdefine_line|#define prepare_to_switch()&t;do { } while(0)
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next) do {&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile(&quot;pushl %%esi&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;pushl %%edi&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;pushl %%ebp&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;movl %%esp,%0&bslash;n&bslash;t&quot;&t;/* save ESP */&t;&t;&bslash;&n;&t;&t;     &quot;movl %2,%%esp&bslash;n&bslash;t&quot;&t;/* restore ESP */&t;&bslash;&n;&t;&t;     &quot;movl $1f,%1&bslash;n&bslash;t&quot;&t;&t;/* save EIP */&t;&t;&bslash;&n;&t;&t;     &quot;pushl %3&bslash;n&bslash;t&quot;&t;&t;/* restore EIP */&t;&bslash;&n;&t;&t;     &quot;jmp __switch_to&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;1:&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;popl %%ebp&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;popl %%edi&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;popl %%esi&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     :&quot;=m&quot; (prev-&gt;thread.esp),&quot;=m&quot; (prev-&gt;thread.eip)&t;&bslash;&n;&t;&t;     :&quot;m&quot; (next-&gt;thread.esp),&quot;m&quot; (next-&gt;thread.eip),&t;&bslash;&n;&t;&t;      &quot;a&quot; (prev), &quot;d&quot; (next));&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|_set_base
mdefine_line|#define _set_base(addr,base) do { unsigned long __pr; &bslash;&n;__asm__ __volatile__ (&quot;movw %%dx,%1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%dl,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%dh,%3&quot; &bslash;&n;&t;:&quot;=&amp;d&quot; (__pr) &bslash;&n;&t;:&quot;m&quot; (*((addr)+2)), &bslash;&n;&t; &quot;m&quot; (*((addr)+4)), &bslash;&n;&t; &quot;m&quot; (*((addr)+7)), &bslash;&n;         &quot;0&quot; (base) &bslash;&n;        ); } while(0)
DECL|macro|_set_limit
mdefine_line|#define _set_limit(addr,limit) do { unsigned long __lr; &bslash;&n;__asm__ __volatile__ (&quot;movw %%dx,%1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %2,%%dh&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;andb $0xf0,%%dh&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;orb %%dh,%%dl&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%dl,%2&quot; &bslash;&n;&t;:&quot;=&amp;d&quot; (__lr) &bslash;&n;&t;:&quot;m&quot; (*(addr)), &bslash;&n;&t; &quot;m&quot; (*((addr)+6)), &bslash;&n;&t; &quot;0&quot; (limit) &bslash;&n;        ); } while(0)
DECL|macro|set_base
mdefine_line|#define set_base(ldt,base) _set_base( ((char *)&amp;(ldt)) , (base) )
DECL|macro|set_limit
mdefine_line|#define set_limit(ldt,limit) _set_limit( ((char *)&amp;(ldt)) , ((limit)-1)&gt;&gt;12 )
DECL|function|_get_base
r_static
r_inline
r_int
r_int
id|_get_base
c_func
(paren
r_char
op_star
id|addr
)paren
(brace
r_int
r_int
id|__base
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movb %3,%%dh&bslash;n&bslash;t&quot;
l_string|&quot;movb %2,%%dl&bslash;n&bslash;t&quot;
l_string|&quot;shll $16,%%edx&bslash;n&bslash;t&quot;
l_string|&quot;movw %1,%%dx&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|__base
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
(paren
(paren
id|addr
)paren
op_plus
l_int|2
)paren
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
(paren
id|addr
)paren
op_plus
l_int|4
)paren
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
(paren
id|addr
)paren
op_plus
l_int|7
)paren
)paren
)paren
suffix:semicolon
r_return
id|__base
suffix:semicolon
)brace
DECL|macro|get_base
mdefine_line|#define get_base(ldt) _get_base( ((char *)&amp;(ldt)) )
multiline_comment|/*&n; * Load a segment. Fall back on loading the zero&n; * segment if something goes wrong..&n; */
DECL|macro|loadsegment
mdefine_line|#define loadsegment(seg,value)&t;&t;&t;&bslash;&n;&t;asm volatile(&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;movl %0,%%&quot; #seg &quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;3:&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;pushl $0&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;popl %%&quot; #seg &quot;&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;jmp 2b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;.align 4&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.long 1b,3b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&bslash;&n;&t;&t;: :&quot;m&quot; (*(unsigned int *)&amp;(value)))
multiline_comment|/*&n; * Clear and set &squot;TS&squot; bit respectively&n; */
DECL|macro|clts
mdefine_line|#define clts() __asm__ __volatile__ (&quot;clts&quot;)
DECL|macro|read_cr0
mdefine_line|#define read_cr0() ({ &bslash;&n;&t;unsigned int __dummy; &bslash;&n;&t;__asm__( &bslash;&n;&t;&t;&quot;movl %%cr0,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;:&quot;=r&quot; (__dummy)); &bslash;&n;&t;__dummy; &bslash;&n;})
DECL|macro|write_cr0
mdefine_line|#define write_cr0(x) &bslash;&n;&t;__asm__(&quot;movl %0,%%cr0&quot;: :&quot;r&quot; (x));
DECL|macro|read_cr4
mdefine_line|#define read_cr4() ({ &bslash;&n;&t;unsigned int __dummy; &bslash;&n;&t;__asm__( &bslash;&n;&t;&t;&quot;movl %%cr4,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;:&quot;=r&quot; (__dummy)); &bslash;&n;&t;__dummy; &bslash;&n;})
DECL|macro|write_cr4
mdefine_line|#define write_cr4(x) &bslash;&n;&t;__asm__(&quot;movl %0,%%cr4&quot;: :&quot;r&quot; (x));
DECL|macro|stts
mdefine_line|#define stts() write_cr0(8 | read_cr0())
macro_line|#endif&t;/* __KERNEL__ */
DECL|macro|wbinvd
mdefine_line|#define wbinvd() &bslash;&n;&t;__asm__ __volatile__ (&quot;wbinvd&quot;: : :&quot;memory&quot;);
DECL|function|get_limit
r_static
r_inline
r_int
r_int
id|get_limit
c_func
(paren
r_int
r_int
id|segment
)paren
(brace
r_int
r_int
id|__limit
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;lsll %1,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__limit
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|segment
)paren
)paren
suffix:semicolon
r_return
id|__limit
op_plus
l_int|1
suffix:semicolon
)brace
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__ (&quot;nop&quot;)
DECL|macro|xchg
mdefine_line|#define xchg(ptr,v) ((__typeof__(*(ptr)))__xchg((unsigned long)(v),(ptr),sizeof(*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr),1))
DECL|struct|__xchg_dummy
DECL|member|a
r_struct
id|__xchg_dummy
(brace
r_int
r_int
id|a
(braket
l_int|100
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|__xg
mdefine_line|#define __xg(x) ((struct __xchg_dummy *)(x))
multiline_comment|/*&n; * The semantics of XCHGCMP8B are a bit strange, this is why&n; * there is a loop and the loading of %%eax and %%edx has to&n; * be inside. This inlines well in most cases, the cached&n; * cost is around ~38 cycles. (in the future we might want&n; * to do an SIMD/3DNOW!/MMX/FPU 64-bit store here, but that&n; * might have an implicit FPU-save as a cost, so it&squot;s not&n; * clear which path to go.)&n; */
DECL|function|__set_64bit
r_static
r_inline
r_void
id|__set_64bit
(paren
r_int
r_int
r_int
op_star
id|ptr
comma
r_int
r_int
id|low
comma
r_int
r_int
id|high
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;&bslash;n1:&bslash;t&quot;
l_string|&quot;movl (%0), %%eax&bslash;n&bslash;t&quot;
l_string|&quot;movl 4(%0), %%edx&bslash;n&bslash;t&quot;
l_string|&quot;cmpxchg8b (%0)&bslash;n&bslash;t&quot;
l_string|&quot;jnz 1b&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;D&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;b&quot;
(paren
id|low
)paren
comma
l_string|&quot;c&quot;
(paren
id|high
)paren
suffix:colon
l_string|&quot;ax&quot;
comma
l_string|&quot;dx&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|__set_64bit_constant
r_static
r_inline
r_void
id|__set_64bit_constant
(paren
r_int
r_int
r_int
op_star
id|ptr
comma
r_int
r_int
r_int
id|value
)paren
(brace
id|__set_64bit
c_func
(paren
id|ptr
comma
(paren
r_int
r_int
)paren
(paren
id|value
)paren
comma
(paren
r_int
r_int
)paren
(paren
(paren
id|value
)paren
op_rshift
l_int|32ULL
)paren
)paren
suffix:semicolon
)brace
DECL|macro|ll_low
mdefine_line|#define ll_low(x)&t;*(((unsigned int*)&amp;(x))+0)
DECL|macro|ll_high
mdefine_line|#define ll_high(x)&t;*(((unsigned int*)&amp;(x))+1)
DECL|function|__set_64bit_var
r_static
r_inline
r_void
id|__set_64bit_var
(paren
r_int
r_int
r_int
op_star
id|ptr
comma
r_int
r_int
r_int
id|value
)paren
(brace
id|__set_64bit
c_func
(paren
id|ptr
comma
id|ll_low
c_func
(paren
id|value
)paren
comma
id|ll_high
c_func
(paren
id|value
)paren
)paren
suffix:semicolon
)brace
DECL|macro|set_64bit
mdefine_line|#define set_64bit(ptr,value) &bslash;&n;(__builtin_constant_p(value) ? &bslash;&n; __set_64bit_constant(ptr, value) : &bslash;&n; __set_64bit_var(ptr, value) )
DECL|macro|_set_64bit
mdefine_line|#define _set_64bit(ptr,value) &bslash;&n;(__builtin_constant_p(value) ? &bslash;&n; __set_64bit(ptr, (unsigned int)(value), (unsigned int)((value)&gt;&gt;32ULL) ) : &bslash;&n; __set_64bit(ptr, ll_low(value), ll_high(value)) )
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
l_string|&quot;xchgl %0,%1&quot;
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
macro_line|#ifdef CONFIG_X86_CMPXCHG
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
l_string|&quot;cmpxchgl %1,%2&quot;
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
macro_line|#else
multiline_comment|/* Compiling for a 386 proper.&t;Is it worth implementing via cli/sti?  */
macro_line|#endif
multiline_comment|/*&n; * Force strict CPU ordering.&n; * And yes, this is required on UP too when we&squot;re talking&n; * to devices.&n; *&n; * For now, &quot;wmb()&quot; doesn&squot;t actually do anything, as all&n; * Intel CPU&squot;s follow what Intel calls a *Processor Order*,&n; * in which all writes are seen in the program order even&n; * outside the CPU.&n; *&n; * I expect future Intel CPU&squot;s to have a weaker ordering,&n; * but I&squot;d also expect them to finally get their act together&n; * and add some real memory barriers if so.&n; *&n; * Some non intel clones support out of order store. wmb() ceases to be a&n; * nop for these.&n; */
DECL|macro|mb
mdefine_line|#define mb() &t;__asm__ __volatile__ (&quot;lock; addl $0,0(%%esp)&quot;: : :&quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb()&t;mb()
macro_line|#ifdef CONFIG_X86_OOSTORE
DECL|macro|wmb
mdefine_line|#define wmb() &t;__asm__ __volatile__ (&quot;lock; addl $0,0(%%esp)&quot;: : :&quot;memory&quot;)
macro_line|#else
DECL|macro|wmb
mdefine_line|#define wmb()&t;__asm__ __volatile__ (&quot;&quot;: : :&quot;memory&quot;)
macro_line|#endif
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
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value) do { xchg(&amp;var, value); } while (0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value) do { var = value; wmb(); } while (0)
multiline_comment|/* interrupt control.. */
DECL|macro|__save_flags
mdefine_line|#define __save_flags(x)&t;&t;__asm__ __volatile__(&quot;pushfl ; popl %0&quot;:&quot;=g&quot; (x): /* no input */)
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(x) &t;__asm__ __volatile__(&quot;pushl %0 ; popfl&quot;: /* no output */ :&quot;g&quot; (x):&quot;memory&quot;, &quot;cc&quot;)
DECL|macro|__cli
mdefine_line|#define __cli() &t;&t;__asm__ __volatile__(&quot;cli&quot;: : :&quot;memory&quot;)
DECL|macro|__sti
mdefine_line|#define __sti()&t;&t;&t;__asm__ __volatile__(&quot;sti&quot;: : :&quot;memory&quot;)
multiline_comment|/* used in the idle loop; sti takes one instruction cycle to complete */
DECL|macro|safe_halt
mdefine_line|#define safe_halt()&t;&t;__asm__ __volatile__(&quot;sti; hlt&quot;: : :&quot;memory&quot;)
multiline_comment|/* For spinlocks etc */
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x)&t;__asm__ __volatile__(&quot;pushfl ; popl %0 ; cli&quot;:&quot;=g&quot; (x): /* no input */ :&quot;memory&quot;)
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x)&t;__restore_flags(x)
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable()&t;__cli()
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()&t;__sti()
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
r_extern
r_int
r_int
id|dmi_broken
suffix:semicolon
r_extern
r_int
id|is_sony_vaio_laptop
suffix:semicolon
DECL|macro|BROKEN_ACPI_Sx
mdefine_line|#define BROKEN_ACPI_Sx&t;&t;0x0001
DECL|macro|BROKEN_INIT_AFTER_S1
mdefine_line|#define BROKEN_INIT_AFTER_S1&t;0x0002
macro_line|#endif
eof
