multiline_comment|/*&n; *  linux/arch/m68k/sun3/config.c&n; *&n; *  Copyright (C) 1996,1997 Pekka Pietik{inen&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/contregs.h&gt;
macro_line|#include &lt;asm/movs.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/sun3-head.h&gt;
macro_line|#include &lt;asm/sun3mmu.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/intersil.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/sun3ints.h&gt;
r_extern
r_char
id|_text
comma
id|_end
suffix:semicolon
DECL|variable|sun3_reserved_pmeg
r_char
id|sun3_reserved_pmeg
(braket
id|SUN3_PMEGS_NUM
)braket
suffix:semicolon
r_extern
r_int
r_int
id|sun3_gettimeoffset
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|show_sun3_interrupts
(paren
r_struct
id|seq_file
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sun3_sched_init
c_func
(paren
id|irqreturn_t
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
suffix:semicolon
r_extern
r_void
id|sun3_get_model
(paren
r_char
op_star
id|model
)paren
suffix:semicolon
r_extern
r_void
id|idprom_init
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|sun3_hwclk
c_func
(paren
r_int
id|set
comma
r_struct
id|rtc_time
op_star
id|t
)paren
suffix:semicolon
DECL|variable|clock_va
r_volatile
r_char
op_star
id|clock_va
suffix:semicolon
r_extern
r_volatile
r_int
r_char
op_star
id|sun3_intreg
suffix:semicolon
r_extern
r_int
r_int
id|availmem
suffix:semicolon
DECL|variable|num_pages
r_int
r_int
id|num_pages
suffix:semicolon
DECL|function|sun3_get_hardware_list
r_static
r_int
id|sun3_get_hardware_list
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;PROM Revision:&bslash;t%s&bslash;n&quot;
comma
id|romvec-&gt;pv_monid
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|sun3_init
r_void
id|__init
id|sun3_init
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|enable_register
suffix:semicolon
r_int
id|i
suffix:semicolon
id|m68k_machtype
op_assign
id|MACH_SUN3
suffix:semicolon
id|m68k_cputype
op_assign
id|CPU_68020
suffix:semicolon
id|m68k_fputype
op_assign
id|FPU_68881
suffix:semicolon
multiline_comment|/* mc68881 actually */
id|m68k_mmutype
op_assign
id|MMU_SUN3
suffix:semicolon
id|clock_va
op_assign
(paren
r_char
op_star
)paren
l_int|0xfe06000
suffix:semicolon
multiline_comment|/* dark  */
id|sun3_intreg
op_assign
(paren
r_int
r_char
op_star
)paren
l_int|0xfe0a000
suffix:semicolon
multiline_comment|/* magic */
id|sun3_disable_interrupts
c_func
(paren
)paren
suffix:semicolon
id|prom_init
c_func
(paren
(paren
r_void
op_star
)paren
id|LINUX_OPPROM_BEGVM
)paren
suffix:semicolon
id|GET_CONTROL_BYTE
c_func
(paren
id|AC_SENABLE
comma
id|enable_register
)paren
suffix:semicolon
id|enable_register
op_or_assign
l_int|0x50
suffix:semicolon
multiline_comment|/* Enable FPU */
id|SET_CONTROL_BYTE
c_func
(paren
id|AC_SENABLE
comma
id|enable_register
)paren
suffix:semicolon
id|GET_CONTROL_BYTE
c_func
(paren
id|AC_SENABLE
comma
id|enable_register
)paren
suffix:semicolon
multiline_comment|/* This code looks suspicious, because it doesn&squot;t subtract&n;           memory belonging to the kernel from the available space */
id|memset
c_func
(paren
id|sun3_reserved_pmeg
comma
l_int|0
comma
r_sizeof
(paren
id|sun3_reserved_pmeg
)paren
)paren
suffix:semicolon
multiline_comment|/* Reserve important PMEGS */
multiline_comment|/* FIXME: These should be probed instead of hardcoded */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* Kernel PMEGs */
id|sun3_reserved_pmeg
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
id|sun3_reserved_pmeg
(braket
l_int|247
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* ROM mapping  */
id|sun3_reserved_pmeg
(braket
l_int|248
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* AMD Ethernet */
id|sun3_reserved_pmeg
(braket
l_int|251
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* VB area      */
id|sun3_reserved_pmeg
(braket
l_int|254
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* main I/O     */
id|sun3_reserved_pmeg
(braket
l_int|249
)braket
op_assign
l_int|1
suffix:semicolon
id|sun3_reserved_pmeg
(braket
l_int|252
)braket
op_assign
l_int|1
suffix:semicolon
id|sun3_reserved_pmeg
(braket
l_int|253
)braket
op_assign
l_int|1
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
)brace
multiline_comment|/* Without this, Bad Things happen when something calls arch_reset. */
DECL|function|sun3_reboot
r_static
r_void
id|sun3_reboot
(paren
r_void
)paren
(brace
id|prom_reboot
(paren
l_string|&quot;vmlinux&quot;
)paren
suffix:semicolon
)brace
DECL|function|sun3_halt
r_static
r_void
id|sun3_halt
(paren
r_void
)paren
(brace
id|prom_halt
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* sun3 bootmem allocation */
DECL|function|sun3_bootmem_alloc
r_void
id|__init
id|sun3_bootmem_alloc
c_func
(paren
r_int
r_int
id|memory_start
comma
r_int
r_int
id|memory_end
)paren
(brace
r_int
r_int
id|start_page
suffix:semicolon
multiline_comment|/* align start/end to page boundaries */
id|memory_start
op_assign
(paren
(paren
id|memory_start
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
id|memory_end
op_assign
id|memory_end
op_amp
id|PAGE_MASK
suffix:semicolon
id|start_page
op_assign
id|__pa
c_func
(paren
id|memory_start
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|num_pages
op_assign
id|__pa
c_func
(paren
id|memory_end
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|high_memory
op_assign
(paren
r_void
op_star
)paren
id|memory_end
suffix:semicolon
id|availmem
op_assign
id|memory_start
suffix:semicolon
id|availmem
op_add_assign
id|init_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|0
)paren
comma
id|start_page
comma
l_int|0
comma
id|num_pages
)paren
suffix:semicolon
id|availmem
op_assign
(paren
id|availmem
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
id|free_bootmem
c_func
(paren
id|__pa
c_func
(paren
id|availmem
)paren
comma
id|memory_end
op_minus
(paren
id|availmem
)paren
)paren
suffix:semicolon
)brace
DECL|function|config_sun3
r_void
id|__init
id|config_sun3
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|memory_start
comma
id|memory_end
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ARCH: SUN3&bslash;n&quot;
)paren
suffix:semicolon
id|idprom_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Subtract kernel memory from available memory */
id|mach_sched_init
op_assign
id|sun3_sched_init
suffix:semicolon
id|mach_init_IRQ
op_assign
id|sun3_init_IRQ
suffix:semicolon
id|mach_default_handler
op_assign
op_amp
id|sun3_default_handler
suffix:semicolon
id|mach_request_irq
op_assign
id|sun3_request_irq
suffix:semicolon
id|mach_free_irq
op_assign
id|sun3_free_irq
suffix:semicolon
id|enable_irq
op_assign
id|sun3_enable_irq
suffix:semicolon
id|disable_irq
op_assign
id|sun3_disable_irq
suffix:semicolon
id|mach_process_int
op_assign
id|sun3_process_int
suffix:semicolon
id|mach_get_irq_list
op_assign
id|show_sun3_interrupts
suffix:semicolon
id|mach_reset
op_assign
id|sun3_reboot
suffix:semicolon
id|mach_gettimeoffset
op_assign
id|sun3_gettimeoffset
suffix:semicolon
id|mach_get_model
op_assign
id|sun3_get_model
suffix:semicolon
id|mach_hwclk
op_assign
id|sun3_hwclk
suffix:semicolon
id|mach_halt
op_assign
id|sun3_halt
suffix:semicolon
id|mach_get_hardware_list
op_assign
id|sun3_get_hardware_list
suffix:semicolon
macro_line|#if defined(CONFIG_DUMMY_CONSOLE)
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
id|memory_start
op_assign
(paren
(paren
(paren
(paren
r_int
)paren
op_amp
id|_end
)paren
op_plus
l_int|0x2000
)paren
op_amp
op_complement
l_int|0x1fff
)paren
suffix:semicolon
singleline_comment|// PROM seems to want the last couple of physical pages. --m
id|memory_end
op_assign
op_star
(paren
id|romvec-&gt;pv_sun3mem
)paren
op_plus
id|PAGE_OFFSET
op_minus
l_int|2
op_star
id|PAGE_SIZE
suffix:semicolon
id|m68k_num_memory
op_assign
l_int|1
suffix:semicolon
id|m68k_memory
(braket
l_int|0
)braket
dot
id|size
op_assign
op_star
(paren
id|romvec-&gt;pv_sun3mem
)paren
suffix:semicolon
id|sun3_bootmem_alloc
c_func
(paren
id|memory_start
comma
id|memory_end
)paren
suffix:semicolon
)brace
DECL|function|sun3_sched_init
r_void
id|__init
id|sun3_sched_init
c_func
(paren
id|irqreturn_t
(paren
op_star
id|timer_routine
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
(brace
id|sun3_disable_interrupts
c_func
(paren
)paren
suffix:semicolon
id|intersil_clock-&gt;cmd_reg
op_assign
(paren
id|INTERSIL_RUN
op_or
id|INTERSIL_INT_DISABLE
op_or
id|INTERSIL_24H_MODE
)paren
suffix:semicolon
id|intersil_clock-&gt;int_reg
op_assign
id|INTERSIL_HZ_100_MASK
suffix:semicolon
id|intersil_clear
c_func
(paren
)paren
suffix:semicolon
id|sun3_enable_irq
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|intersil_clock-&gt;cmd_reg
op_assign
(paren
id|INTERSIL_RUN
op_or
id|INTERSIL_INT_ENABLE
op_or
id|INTERSIL_24H_MODE
)paren
suffix:semicolon
id|sun3_enable_interrupts
c_func
(paren
)paren
suffix:semicolon
id|intersil_clear
c_func
(paren
)paren
suffix:semicolon
)brace
eof
