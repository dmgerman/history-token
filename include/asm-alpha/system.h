macro_line|#ifndef __ALPHA_SYSTEM_H
DECL|macro|__ALPHA_SYSTEM_H
mdefine_line|#define __ALPHA_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/pal.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; * System defines.. Note that this is included both from .c and .S&n; * files, so it does only defines, not any C code.&n; */
multiline_comment|/*&n; * We leave one page for the initial stack page, and one page for&n; * the initial process structure. Also, the console eats 3 MB for&n; * the initial bootloader (one of which we can reclaim later).&n; */
DECL|macro|BOOT_PCB
mdefine_line|#define BOOT_PCB&t;0x20000000
DECL|macro|BOOT_ADDR
mdefine_line|#define BOOT_ADDR&t;0x20000000
multiline_comment|/* Remove when official MILO sources have ELF support: */
DECL|macro|BOOT_SIZE
mdefine_line|#define BOOT_SIZE&t;(16*1024)
macro_line|#ifdef CONFIG_ALPHA_LEGACY_START_ADDRESS
DECL|macro|KERNEL_START_PHYS
mdefine_line|#define KERNEL_START_PHYS&t;0x300000 /* Old bootloaders hardcoded this.  */
macro_line|#else
DECL|macro|KERNEL_START_PHYS
mdefine_line|#define KERNEL_START_PHYS&t;0x800000 /* Wildfire has a huge console */
macro_line|#endif
DECL|macro|KERNEL_START
mdefine_line|#define KERNEL_START&t;(PAGE_OFFSET+KERNEL_START_PHYS)
DECL|macro|SWAPPER_PGD
mdefine_line|#define SWAPPER_PGD&t;KERNEL_START
DECL|macro|INIT_STACK
mdefine_line|#define INIT_STACK&t;(PAGE_OFFSET+KERNEL_START_PHYS+0x02000)
DECL|macro|EMPTY_PGT
mdefine_line|#define EMPTY_PGT&t;(PAGE_OFFSET+KERNEL_START_PHYS+0x04000)
DECL|macro|EMPTY_PGE
mdefine_line|#define EMPTY_PGE&t;(PAGE_OFFSET+KERNEL_START_PHYS+0x08000)
DECL|macro|ZERO_PGE
mdefine_line|#define ZERO_PGE&t;(PAGE_OFFSET+KERNEL_START_PHYS+0x0A000)
DECL|macro|START_ADDR
mdefine_line|#define START_ADDR&t;(PAGE_OFFSET+KERNEL_START_PHYS+0x10000)
multiline_comment|/*&n; * This is setup by the secondary bootstrap loader.  Because&n; * the zero page is zeroed out as soon as the vm system is&n; * initialized, we need to copy things out into a more permanent&n; * place.&n; */
DECL|macro|PARAM
mdefine_line|#define PARAM&t;&t;&t;ZERO_PGE
DECL|macro|COMMAND_LINE
mdefine_line|#define COMMAND_LINE&t;&t;((char*)(PARAM + 0x0000))
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE&t;256
DECL|macro|INITRD_START
mdefine_line|#define INITRD_START&t;&t;(*(unsigned long *) (PARAM+0x100))
DECL|macro|INITRD_SIZE
mdefine_line|#define INITRD_SIZE&t;&t;(*(unsigned long *) (PARAM+0x108))
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/kernel.h&gt;
multiline_comment|/*&n; * This is the logout header that should be common to all platforms&n; * (assuming they are running OSF/1 PALcode, I guess).&n; */
DECL|struct|el_common
r_struct
id|el_common
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size in bytes of logout area */
DECL|member|sbz1
r_int
id|sbz1
suffix:colon
l_int|30
suffix:semicolon
multiline_comment|/* should be zero */
DECL|member|err2
r_int
id|err2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* second error */
DECL|member|retry
r_int
id|retry
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* retry flag */
DECL|member|proc_offset
r_int
r_int
id|proc_offset
suffix:semicolon
multiline_comment|/* processor-specific offset */
DECL|member|sys_offset
r_int
r_int
id|sys_offset
suffix:semicolon
multiline_comment|/* system-specific offset */
DECL|member|code
r_int
r_int
id|code
suffix:semicolon
multiline_comment|/* machine check code */
)brace
suffix:semicolon
multiline_comment|/* Machine Check Frame for uncorrectable errors (Large format)&n; *      --- This is used to log uncorrectable errors such as&n; *          double bit ECC errors.&n; *      --- These errors are detected by both processor and systems.&n; */
DECL|struct|el_common_EV5_uncorrectable_mcheck
r_struct
id|el_common_EV5_uncorrectable_mcheck
(brace
DECL|member|shadow
r_int
r_int
id|shadow
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Shadow reg. 8-14, 25           */
DECL|member|paltemp
r_int
r_int
id|paltemp
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* PAL TEMP REGS.                 */
DECL|member|exc_addr
r_int
r_int
id|exc_addr
suffix:semicolon
multiline_comment|/* Address of excepting instruction*/
DECL|member|exc_sum
r_int
r_int
id|exc_sum
suffix:semicolon
multiline_comment|/* Summary of arithmetic traps.   */
DECL|member|exc_mask
r_int
r_int
id|exc_mask
suffix:semicolon
multiline_comment|/* Exception mask (from exc_sum). */
DECL|member|pal_base
r_int
r_int
id|pal_base
suffix:semicolon
multiline_comment|/* Base address for PALcode.      */
DECL|member|isr
r_int
r_int
id|isr
suffix:semicolon
multiline_comment|/* Interrupt Status Reg.          */
DECL|member|icsr
r_int
r_int
id|icsr
suffix:semicolon
multiline_comment|/* CURRENT SETUP OF EV5 IBOX      */
DECL|member|ic_perr_stat
r_int
r_int
id|ic_perr_stat
suffix:semicolon
multiline_comment|/* I-CACHE Reg. &lt;11&gt; set Data parity&n;                                                         &lt;12&gt; set TAG parity*/
DECL|member|dc_perr_stat
r_int
r_int
id|dc_perr_stat
suffix:semicolon
multiline_comment|/* D-CACHE error Reg. Bits set to 1:&n;                                                     &lt;2&gt; Data error in bank 0&n;                                                     &lt;3&gt; Data error in bank 1&n;                                                     &lt;4&gt; Tag error in bank 0&n;                                                     &lt;5&gt; Tag error in bank 1 */
DECL|member|va
r_int
r_int
id|va
suffix:semicolon
multiline_comment|/* Effective VA of fault or miss. */
DECL|member|mm_stat
r_int
r_int
id|mm_stat
suffix:semicolon
multiline_comment|/* Holds the reason for D-stream &n;                                             fault or D-cache parity errors */
DECL|member|sc_addr
r_int
r_int
id|sc_addr
suffix:semicolon
multiline_comment|/* Address that was being accessed&n;                                             when EV5 detected Secondary cache&n;                                             failure.                 */
DECL|member|sc_stat
r_int
r_int
id|sc_stat
suffix:semicolon
multiline_comment|/* Helps determine if the error was&n;                                             TAG/Data parity(Secondary Cache)*/
DECL|member|bc_tag_addr
r_int
r_int
id|bc_tag_addr
suffix:semicolon
multiline_comment|/* Contents of EV5 BC_TAG_ADDR    */
DECL|member|ei_addr
r_int
r_int
id|ei_addr
suffix:semicolon
multiline_comment|/* Physical address of any transfer&n;                                             that is logged in EV5 EI_STAT */
DECL|member|fill_syndrome
r_int
r_int
id|fill_syndrome
suffix:semicolon
multiline_comment|/* For correcting ECC errors.     */
DECL|member|ei_stat
r_int
r_int
id|ei_stat
suffix:semicolon
multiline_comment|/* Helps identify reason of any &n;                                             processor uncorrectable error&n;                                             at its external interface.     */
DECL|member|ld_lock
r_int
r_int
id|ld_lock
suffix:semicolon
multiline_comment|/* Contents of EV5 LD_LOCK register*/
)brace
suffix:semicolon
DECL|struct|el_common_EV6_mcheck
r_struct
id|el_common_EV6_mcheck
(brace
DECL|member|FrameSize
r_int
r_int
id|FrameSize
suffix:semicolon
multiline_comment|/* Bytes, including this field */
DECL|member|FrameFlags
r_int
r_int
id|FrameFlags
suffix:semicolon
multiline_comment|/* &lt;31&gt; = Retry, &lt;30&gt; = Second Error */
DECL|member|CpuOffset
r_int
r_int
id|CpuOffset
suffix:semicolon
multiline_comment|/* Offset to CPU-specific info */
DECL|member|SystemOffset
r_int
r_int
id|SystemOffset
suffix:semicolon
multiline_comment|/* Offset to system-specific info */
DECL|member|MCHK_Code
r_int
r_int
id|MCHK_Code
suffix:semicolon
DECL|member|MCHK_Frame_Rev
r_int
r_int
id|MCHK_Frame_Rev
suffix:semicolon
DECL|member|I_STAT
r_int
r_int
id|I_STAT
suffix:semicolon
multiline_comment|/* EV6 Internal Processor Registers */
DECL|member|DC_STAT
r_int
r_int
id|DC_STAT
suffix:semicolon
multiline_comment|/* (See the 21264 Spec) */
DECL|member|C_ADDR
r_int
r_int
id|C_ADDR
suffix:semicolon
DECL|member|DC1_SYNDROME
r_int
r_int
id|DC1_SYNDROME
suffix:semicolon
DECL|member|DC0_SYNDROME
r_int
r_int
id|DC0_SYNDROME
suffix:semicolon
DECL|member|C_STAT
r_int
r_int
id|C_STAT
suffix:semicolon
DECL|member|C_STS
r_int
r_int
id|C_STS
suffix:semicolon
DECL|member|RESERVED0
r_int
r_int
id|RESERVED0
suffix:semicolon
DECL|member|EXC_ADDR
r_int
r_int
id|EXC_ADDR
suffix:semicolon
DECL|member|IER_CM
r_int
r_int
id|IER_CM
suffix:semicolon
DECL|member|ISUM
r_int
r_int
id|ISUM
suffix:semicolon
DECL|member|MM_STAT
r_int
r_int
id|MM_STAT
suffix:semicolon
DECL|member|PAL_BASE
r_int
r_int
id|PAL_BASE
suffix:semicolon
DECL|member|I_CTL
r_int
r_int
id|I_CTL
suffix:semicolon
DECL|member|PCTX
r_int
r_int
id|PCTX
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|halt
c_func
(paren
r_void
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
DECL|macro|__halt
mdefine_line|#define __halt() __asm__ __volatile__ (&quot;call_pal %0 #halt&quot; : : &quot;i&quot; (PAL_halt))
DECL|macro|prepare_to_switch
mdefine_line|#define prepare_to_switch()&t;do { } while(0)
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long pcbb;&t;&t;&t;&t;&bslash;&n;&t;current = (next);&t;&t;&t;&t;&bslash;&n;&t;pcbb = virt_to_phys(&amp;current-&gt;thread);&t;&t;&bslash;&n;&t;(last) = alpha_switch_to(pcbb, (prev));&t;&t;&bslash;&n;&t;check_mmu_context();&t;&t;&t;&t;&bslash;&n;} while (0)
r_extern
r_struct
id|task_struct
op_star
id|alpha_switch_to
c_func
(paren
r_int
r_int
comma
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
DECL|macro|mb
mdefine_line|#define mb() &bslash;&n;__asm__ __volatile__(&quot;mb&quot;: : :&quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb() &bslash;&n;__asm__ __volatile__(&quot;mb&quot;: : :&quot;memory&quot;)
DECL|macro|wmb
mdefine_line|#define wmb() &bslash;&n;__asm__ __volatile__(&quot;wmb&quot;: : :&quot;memory&quot;)
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
mdefine_line|#define set_mb(var, value) &bslash;&n;do { var = value; mb(); } while (0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value) &bslash;&n;do { var = value; wmb(); } while (0)
DECL|macro|imb
mdefine_line|#define imb() &bslash;&n;__asm__ __volatile__ (&quot;call_pal %0 #imb&quot; : : &quot;i&quot; (PAL_imb) : &quot;memory&quot;)
DECL|macro|draina
mdefine_line|#define draina() &bslash;&n;__asm__ __volatile__ (&quot;call_pal %0 #draina&quot; : : &quot;i&quot; (PAL_draina) : &quot;memory&quot;)
DECL|enum|implver_enum
r_enum
id|implver_enum
(brace
DECL|enumerator|IMPLVER_EV4
id|IMPLVER_EV4
comma
DECL|enumerator|IMPLVER_EV5
id|IMPLVER_EV5
comma
DECL|enumerator|IMPLVER_EV6
id|IMPLVER_EV6
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_ALPHA_GENERIC
DECL|macro|implver
mdefine_line|#define implver()&t;&t;&t;&t;&bslash;&n;({ unsigned long __implver;&t;&t;&t;&bslash;&n;   __asm__ (&quot;implver %0&quot; : &quot;=r&quot;(__implver));&t;&bslash;&n;   (enum implver_enum) __implver; })
macro_line|#else
multiline_comment|/* Try to eliminate some dead code.  */
macro_line|#ifdef CONFIG_ALPHA_EV4
DECL|macro|implver
mdefine_line|#define implver() IMPLVER_EV4
macro_line|#endif
macro_line|#ifdef CONFIG_ALPHA_EV5
DECL|macro|implver
mdefine_line|#define implver() IMPLVER_EV5
macro_line|#endif
macro_line|#if defined(CONFIG_ALPHA_EV6) || defined(CONFIG_ALPHA_EV67)
DECL|macro|implver
mdefine_line|#define implver() IMPLVER_EV6
macro_line|#endif
macro_line|#endif
DECL|enum|amask_enum
r_enum
id|amask_enum
(brace
DECL|enumerator|AMASK_BWX
id|AMASK_BWX
op_assign
(paren
l_int|1UL
op_lshift
l_int|0
)paren
comma
DECL|enumerator|AMASK_FIX
id|AMASK_FIX
op_assign
(paren
l_int|1UL
op_lshift
l_int|1
)paren
comma
DECL|enumerator|AMASK_MAX
id|AMASK_MAX
op_assign
(paren
l_int|1UL
op_lshift
l_int|8
)paren
comma
DECL|enumerator|AMASK_PRECISE_TRAP
id|AMASK_PRECISE_TRAP
op_assign
(paren
l_int|1UL
op_lshift
l_int|9
)paren
comma
)brace
suffix:semicolon
DECL|macro|amask
mdefine_line|#define amask(mask)&t;&t;&t;&t;&t;&t;&bslash;&n;({ unsigned long __amask, __input = (mask);&t;&t;&t;&bslash;&n;   __asm__ (&quot;amask %1,%0&quot; : &quot;=r&quot;(__amask) : &quot;rI&quot;(__input));&t;&bslash;&n;   __amask; })
DECL|macro|__CALL_PAL_R0
mdefine_line|#define __CALL_PAL_R0(NAME, TYPE)&t;&t;&t;&t;&bslash;&n;static inline TYPE NAME(void)&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register TYPE __r0 __asm__(&quot;$0&quot;);&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;call_pal %1 # &quot; #NAME&t;&t;&t;&t;&bslash;&n;&t;&t;:&quot;=r&quot; (__r0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;:&quot;i&quot; (PAL_ ## NAME)&t;&t;&t;&t;&bslash;&n;&t;&t;:&quot;$1&quot;, &quot;$16&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;);&t;&bslash;&n;&t;return __r0;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|__CALL_PAL_W1
mdefine_line|#define __CALL_PAL_W1(NAME, TYPE0)&t;&t;&t;&t;&bslash;&n;static inline void NAME(TYPE0 arg0)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register TYPE0 __r16 __asm__(&quot;$16&quot;) = arg0;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;call_pal %1 # &quot;#NAME&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__r16)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;i&quot;(PAL_ ## NAME), &quot;0&quot;(__r16)&t;&t;&t;&bslash;&n;&t;&t;: &quot;$1&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;);&t;&t;&bslash;&n;}
DECL|macro|__CALL_PAL_W2
mdefine_line|#define __CALL_PAL_W2(NAME, TYPE0, TYPE1)&t;&t;&t;&bslash;&n;static inline void NAME(TYPE0 arg0, TYPE1 arg1)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register TYPE0 __r16 __asm__(&quot;$16&quot;) = arg0;&t;&t;&bslash;&n;&t;register TYPE1 __r17 __asm__(&quot;$17&quot;) = arg1;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;call_pal %2 # &quot;#NAME&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__r16), &quot;=r&quot;(__r17)&t;&t;&t;&bslash;&n;&t;&t;: &quot;i&quot;(PAL_ ## NAME), &quot;0&quot;(__r16), &quot;1&quot;(__r17)&t;&bslash;&n;&t;&t;: &quot;$1&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;);&t;&t;&bslash;&n;}
DECL|macro|__CALL_PAL_RW1
mdefine_line|#define __CALL_PAL_RW1(NAME, RTYPE, TYPE0)&t;&t;&t;&bslash;&n;static inline RTYPE NAME(TYPE0 arg0)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register RTYPE __r0 __asm__(&quot;$0&quot;);&t;&t;&t;&bslash;&n;&t;register TYPE0 __r16 __asm__(&quot;$16&quot;) = arg0;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;call_pal %2 # &quot;#NAME&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__r16), &quot;=r&quot;(__r0)&t;&t;&t;&bslash;&n;&t;&t;: &quot;i&quot;(PAL_ ## NAME), &quot;0&quot;(__r16)&t;&t;&t;&bslash;&n;&t;&t;: &quot;$1&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;);&t;&t;&bslash;&n;&t;return __r0;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|__CALL_PAL_RW2
mdefine_line|#define __CALL_PAL_RW2(NAME, RTYPE, TYPE0, TYPE1)&t;&t;&bslash;&n;static inline RTYPE NAME(TYPE0 arg0, TYPE1 arg1)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register RTYPE __r0 __asm__(&quot;$0&quot;);&t;&t;&t;&bslash;&n;&t;register TYPE0 __r16 __asm__(&quot;$16&quot;) = arg0;&t;&t;&bslash;&n;&t;register TYPE1 __r17 __asm__(&quot;$17&quot;) = arg1;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;call_pal %3 # &quot;#NAME&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__r16), &quot;=r&quot;(__r17), &quot;=r&quot;(__r0)&t;&t;&bslash;&n;&t;&t;: &quot;i&quot;(PAL_ ## NAME), &quot;0&quot;(__r16), &quot;1&quot;(__r17)&t;&bslash;&n;&t;&t;: &quot;$1&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;);&t;&t;&bslash;&n;&t;return __r0;&t;&t;&t;&t;&t;&t;&bslash;&n;}
id|__CALL_PAL_W1
c_func
(paren
id|cflush
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_R0
c_func
(paren
id|rdmces
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_R0
c_func
(paren
id|rdps
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_R0
c_func
(paren
id|rdusp
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_RW1
c_func
(paren
id|swpipl
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_R0
c_func
(paren
id|whami
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_W2
c_func
(paren
id|wrent
comma
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_W1
c_func
(paren
id|wripir
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_W1
c_func
(paren
id|wrkgp
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_W1
c_func
(paren
id|wrmces
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_RW2
c_func
(paren
id|wrperfmon
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_W1
c_func
(paren
id|wrusp
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_W1
c_func
(paren
id|wrvptptr
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|IPL_MIN
mdefine_line|#define IPL_MIN&t;&t;0
DECL|macro|IPL_SW0
mdefine_line|#define IPL_SW0&t;&t;1
DECL|macro|IPL_SW1
mdefine_line|#define IPL_SW1&t;&t;2
DECL|macro|IPL_DEV0
mdefine_line|#define IPL_DEV0&t;3
DECL|macro|IPL_DEV1
mdefine_line|#define IPL_DEV1&t;4
DECL|macro|IPL_TIMER
mdefine_line|#define IPL_TIMER&t;5
DECL|macro|IPL_PERF
mdefine_line|#define IPL_PERF&t;6
DECL|macro|IPL_POWERFAIL
mdefine_line|#define IPL_POWERFAIL&t;6
DECL|macro|IPL_MCHECK
mdefine_line|#define IPL_MCHECK&t;7
DECL|macro|IPL_MAX
mdefine_line|#define IPL_MAX&t;&t;7
macro_line|#ifdef CONFIG_ALPHA_BROKEN_IRQ_MASK
DECL|macro|IPL_MIN
macro_line|#undef IPL_MIN
DECL|macro|IPL_MIN
mdefine_line|#define IPL_MIN&t;&t;__min_ipl
r_extern
r_int
id|__min_ipl
suffix:semicolon
macro_line|#endif
DECL|macro|getipl
mdefine_line|#define getipl()&t;&t;(rdps() &amp; 7)
DECL|macro|setipl
mdefine_line|#define setipl(ipl)&t;&t;((void) swpipl(ipl))
DECL|macro|__cli
mdefine_line|#define __cli()&t;&t;&t;do { setipl(IPL_MAX); barrier(); } while(0)
DECL|macro|__sti
mdefine_line|#define __sti()&t;&t;&t;do { barrier(); setipl(IPL_MIN); } while(0)
DECL|macro|__save_flags
mdefine_line|#define __save_flags(flags)&t;((flags) = rdps())
DECL|macro|__save_and_cli
mdefine_line|#define __save_and_cli(flags)&t;do { (flags) = swpipl(IPL_MAX); barrier(); } while(0)
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(flags)&t;do { barrier(); setipl(flags); barrier(); } while(0)
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(flags)&t;&t;__save_and_cli(flags)
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(flags)&t;__restore_flags(flags)
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable()&t;&t;__cli()
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()&t;&t;__sti()
macro_line|#ifdef CONFIG_SMP
r_extern
r_int
id|global_irq_holder
suffix:semicolon
DECL|macro|save_and_cli
mdefine_line|#define save_and_cli(flags)     (save_flags(flags), cli())
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
id|flags
)paren
suffix:semicolon
DECL|macro|cli
mdefine_line|#define cli()                   __global_cli()
DECL|macro|sti
mdefine_line|#define sti()                   __global_sti()
DECL|macro|save_flags
mdefine_line|#define save_flags(flags)&t;((flags) = __global_save_flags())
DECL|macro|restore_flags
mdefine_line|#define restore_flags(flags)    __global_restore_flags(flags)
macro_line|#else /* CONFIG_SMP */
DECL|macro|cli
mdefine_line|#define cli()&t;&t;&t;__cli()
DECL|macro|sti
mdefine_line|#define sti()&t;&t;&t;__sti()
DECL|macro|save_flags
mdefine_line|#define save_flags(flags)&t;__save_flags(flags)
DECL|macro|save_and_cli
mdefine_line|#define save_and_cli(flags)&t;__save_and_cli(flags)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(flags)&t;__restore_flags(flags)
macro_line|#endif /* CONFIG_SMP */
multiline_comment|/*&n; * TB routines..&n; */
DECL|macro|__tbi
mdefine_line|#define __tbi(nr,arg,arg1...)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register unsigned long __r16 __asm__(&quot;$16&quot;) = (nr);&t;&bslash;&n;&t;register unsigned long __r17 __asm__(&quot;$17&quot;); arg;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;call_pal %3 #__tbi&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;:&quot;=r&quot; (__r16),&quot;=r&quot; (__r17)&t;&t;&t;&bslash;&n;&t;&t;:&quot;0&quot; (__r16),&quot;i&quot; (PAL_tbi) ,##arg1&t;&t;&bslash;&n;&t;&t;:&quot;$0&quot;, &quot;$1&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;);&t;&bslash;&n;})
DECL|macro|tbi
mdefine_line|#define tbi(x,y)&t;__tbi(x,__r17=(y),&quot;1&quot; (__r17))
DECL|macro|tbisi
mdefine_line|#define tbisi(x)&t;__tbi(1,__r17=(x),&quot;1&quot; (__r17))
DECL|macro|tbisd
mdefine_line|#define tbisd(x)&t;__tbi(2,__r17=(x),&quot;1&quot; (__r17))
DECL|macro|tbis
mdefine_line|#define tbis(x)&t;&t;__tbi(3,__r17=(x),&quot;1&quot; (__r17))
DECL|macro|tbiap
mdefine_line|#define tbiap()&t;&t;__tbi(-1, /* no second argument */)
DECL|macro|tbia
mdefine_line|#define tbia()&t;&t;__tbi(-2, /* no second argument */)
multiline_comment|/*&n; * Atomic exchange.&n; * Since it can be used to implement critical sections&n; * it must clobber &quot;memory&quot; (also for interrupts in UP).&n; */
r_extern
id|__inline__
r_int
r_int
DECL|function|__xchg_u32
id|__xchg_u32
c_func
(paren
r_volatile
r_int
op_star
id|m
comma
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l %0,%4&bslash;n&quot;
l_string|&quot;&t;bis $31,%3,%1&bslash;n&quot;
l_string|&quot;&t;stl_c %1,%2&bslash;n&quot;
l_string|&quot;&t;beq %1,2f&bslash;n&quot;
macro_line|#ifdef CONFIG_SMP
l_string|&quot;&t;mb&bslash;n&quot;
macro_line|#endif
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;2:&t;br 1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
suffix:colon
l_string|&quot;rI&quot;
(paren
id|val
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|m
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
r_int
DECL|function|__xchg_u64
id|__xchg_u64
c_func
(paren
r_volatile
r_int
op_star
id|m
comma
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldq_l %0,%4&bslash;n&quot;
l_string|&quot;&t;bis $31,%3,%1&bslash;n&quot;
l_string|&quot;&t;stq_c %1,%2&bslash;n&quot;
l_string|&quot;&t;beq %1,2f&bslash;n&quot;
macro_line|#ifdef CONFIG_SMP
l_string|&quot;&t;mb&bslash;n&quot;
macro_line|#endif
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;2:&t;br 1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
suffix:colon
l_string|&quot;rI&quot;
(paren
id|val
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|m
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/* This function doesn&squot;t exist, so you&squot;ll get a linker error&n;   if something tries to do an invalid xchg().  */
r_extern
r_void
id|__xchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
id|__inline__
r_int
r_int
DECL|function|__xchg
id|__xchg
c_func
(paren
r_volatile
r_void
op_star
id|ptr
comma
r_int
r_int
id|x
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
l_int|4
suffix:colon
r_return
id|__xchg_u32
c_func
(paren
id|ptr
comma
id|x
)paren
suffix:semicolon
r_case
l_int|8
suffix:colon
r_return
id|__xchg_u64
c_func
(paren
id|ptr
comma
id|x
)paren
suffix:semicolon
)brace
id|__xchg_called_with_bad_pointer
c_func
(paren
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x)&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;  ({&t;&t;&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;     __typeof__(*(ptr)) _x_ = (x);&t;&t;&t;&t;&t;     &bslash;&n;     (__typeof__(*(ptr))) __xchg((ptr), (unsigned long)_x_, sizeof(*(ptr))); &bslash;&n;  })
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr),1))
multiline_comment|/* &n; * Atomic compare and exchange.  Compare OLD with MEM, if identical,&n; * store NEW in MEM.  Return the initial value in MEM.  Success is&n; * indicated by comparing RETURN with OLD.&n; *&n; * The memory barrier should be placed in SMP only when we actually&n; * make the change. If we don&squot;t change anything (so if the returned&n; * prev is equal to old) then we aren&squot;t acquiring anything new and&n; * we don&squot;t need any memory barrier as far I can tell.&n; */
DECL|macro|__HAVE_ARCH_CMPXCHG
mdefine_line|#define __HAVE_ARCH_CMPXCHG 1
r_extern
id|__inline__
r_int
r_int
DECL|function|__cmpxchg_u32
id|__cmpxchg_u32
c_func
(paren
r_volatile
r_int
op_star
id|m
comma
r_int
id|old
comma
r_int
r_new
)paren
(brace
r_int
r_int
id|prev
comma
id|cmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l %0,%5&bslash;n&quot;
l_string|&quot;&t;cmpeq %0,%3,%1&bslash;n&quot;
l_string|&quot;&t;beq %1,2f&bslash;n&quot;
l_string|&quot;&t;mov %4,%1&bslash;n&quot;
l_string|&quot;&t;stl_c %1,%2&bslash;n&quot;
l_string|&quot;&t;beq %1,3f&bslash;n&quot;
macro_line|#ifdef CONFIG_SMP
l_string|&quot;&t;mb&bslash;n&quot;
macro_line|#endif
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;3:&t;br 1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|prev
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|cmp
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
r_int
)paren
id|old
)paren
comma
l_string|&quot;r&quot;
(paren
r_new
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|m
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|prev
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
r_int
DECL|function|__cmpxchg_u64
id|__cmpxchg_u64
c_func
(paren
r_volatile
r_int
op_star
id|m
comma
r_int
r_int
id|old
comma
r_int
r_int
r_new
)paren
(brace
r_int
r_int
id|prev
comma
id|cmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldq_l %0,%5&bslash;n&quot;
l_string|&quot;&t;cmpeq %0,%3,%1&bslash;n&quot;
l_string|&quot;&t;beq %1,2f&bslash;n&quot;
l_string|&quot;&t;mov %4,%1&bslash;n&quot;
l_string|&quot;&t;stq_c %1,%2&bslash;n&quot;
l_string|&quot;&t;beq %1,3f&bslash;n&quot;
macro_line|#ifdef CONFIG_SMP
l_string|&quot;&t;mb&bslash;n&quot;
macro_line|#endif
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;3:&t;br 1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|prev
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|cmp
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
r_int
)paren
id|old
)paren
comma
l_string|&quot;r&quot;
(paren
r_new
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|m
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|prev
suffix:semicolon
)brace
multiline_comment|/* This function doesn&squot;t exist, so you&squot;ll get a linker error&n;   if something tries to do an invalid cmpxchg().  */
r_extern
r_void
id|__cmpxchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
id|__inline__
r_int
r_int
DECL|function|__cmpxchg
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
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|4
suffix:colon
r_return
id|__cmpxchg_u32
c_func
(paren
id|ptr
comma
id|old
comma
r_new
)paren
suffix:semicolon
r_case
l_int|8
suffix:colon
r_return
id|__cmpxchg_u64
c_func
(paren
id|ptr
comma
id|old
comma
r_new
)paren
suffix:semicolon
)brace
id|__cmpxchg_called_with_bad_pointer
c_func
(paren
)paren
suffix:semicolon
r_return
id|old
suffix:semicolon
)brace
DECL|macro|cmpxchg
mdefine_line|#define cmpxchg(ptr,o,n)&t;&t;&t;&t;&t;&t; &bslash;&n;  ({&t;&t;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;     __typeof__(*(ptr)) _o_ = (o);&t;&t;&t;&t;&t; &bslash;&n;     __typeof__(*(ptr)) _n_ = (n);&t;&t;&t;&t;&t; &bslash;&n;     (__typeof__(*(ptr))) __cmpxchg((ptr), (unsigned long)_o_,&t;&t; &bslash;&n;&t;&t;&t;&t;    (unsigned long)_n_, sizeof(*(ptr))); &bslash;&n;  })
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif
eof
