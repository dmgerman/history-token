multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_titan.c&n; *&n; *&t;Copyright (C) 1995 David A Rusling&n; *&t;Copyright (C) 1996, 1999 Jay A Estabrook&n; *&t;Copyright (C) 1998, 1999 Richard Henderson&n; *      Copyright (C) 1999, 2000 Jeff Wiedemeier&n; *&n; * Code supporting TITAN systems (EV6+TITAN), currently:&n; *      Privateer&n; *&t;Falcon&n; *&t;Granite&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/core_titan.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq_impl.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
macro_line|#include &quot;machvec_impl.h&quot;
macro_line|#include &quot;err_impl.h&quot;
"&f;"
multiline_comment|/*&n; * Titan generic&n; */
multiline_comment|/*&n; * Titan supports up to 4 CPUs&n; */
DECL|variable|titan_cpu_irq_affinity
r_static
r_int
r_int
id|titan_cpu_irq_affinity
(braket
l_int|4
)braket
op_assign
(brace
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
)brace
suffix:semicolon
multiline_comment|/*&n; * Mask is set (1) if enabled&n; */
DECL|variable|titan_cached_irq_mask
r_static
r_int
r_int
id|titan_cached_irq_mask
suffix:semicolon
multiline_comment|/*&n; * Need SMP-safe access to interrupt CSRs&n; */
DECL|variable|titan_irq_lock
id|spinlock_t
id|titan_irq_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_static
r_void
DECL|function|titan_update_irq_hw
id|titan_update_irq_hw
c_func
(paren
r_int
r_int
id|mask
)paren
(brace
r_register
id|titan_cchip
op_star
id|cchip
op_assign
id|TITAN_cchip
suffix:semicolon
r_int
r_int
id|isa_enable
op_assign
l_int|1UL
op_lshift
l_int|55
suffix:semicolon
r_register
r_int
id|bcpu
op_assign
id|boot_cpuid
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|cpumask_t
id|cpm
op_assign
id|cpu_present_mask
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|dim0
comma
op_star
id|dim1
comma
op_star
id|dim2
comma
op_star
id|dim3
suffix:semicolon
r_int
r_int
id|mask0
comma
id|mask1
comma
id|mask2
comma
id|mask3
comma
id|dummy
suffix:semicolon
id|mask
op_and_assign
op_complement
id|isa_enable
suffix:semicolon
id|mask0
op_assign
id|mask
op_amp
id|titan_cpu_irq_affinity
(braket
l_int|0
)braket
suffix:semicolon
id|mask1
op_assign
id|mask
op_amp
id|titan_cpu_irq_affinity
(braket
l_int|1
)braket
suffix:semicolon
id|mask2
op_assign
id|mask
op_amp
id|titan_cpu_irq_affinity
(braket
l_int|2
)braket
suffix:semicolon
id|mask3
op_assign
id|mask
op_amp
id|titan_cpu_irq_affinity
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|bcpu
op_eq
l_int|0
)paren
id|mask0
op_or_assign
id|isa_enable
suffix:semicolon
r_else
r_if
c_cond
(paren
id|bcpu
op_eq
l_int|1
)paren
id|mask1
op_or_assign
id|isa_enable
suffix:semicolon
r_else
r_if
c_cond
(paren
id|bcpu
op_eq
l_int|2
)paren
id|mask2
op_or_assign
id|isa_enable
suffix:semicolon
r_else
id|mask3
op_or_assign
id|isa_enable
suffix:semicolon
id|dim0
op_assign
op_amp
id|cchip-&gt;dim0.csr
suffix:semicolon
id|dim1
op_assign
op_amp
id|cchip-&gt;dim1.csr
suffix:semicolon
id|dim2
op_assign
op_amp
id|cchip-&gt;dim2.csr
suffix:semicolon
id|dim3
op_assign
op_amp
id|cchip-&gt;dim3.csr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_isset
c_func
(paren
l_int|0
comma
id|cpm
)paren
)paren
id|dim0
op_assign
op_amp
id|dummy
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_isset
c_func
(paren
l_int|1
comma
id|cpm
)paren
)paren
id|dim1
op_assign
op_amp
id|dummy
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_isset
c_func
(paren
l_int|2
comma
id|cpm
)paren
)paren
id|dim2
op_assign
op_amp
id|dummy
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_isset
c_func
(paren
l_int|3
comma
id|cpm
)paren
)paren
id|dim3
op_assign
op_amp
id|dummy
suffix:semicolon
op_star
id|dim0
op_assign
id|mask0
suffix:semicolon
op_star
id|dim1
op_assign
id|mask1
suffix:semicolon
op_star
id|dim2
op_assign
id|mask2
suffix:semicolon
op_star
id|dim3
op_assign
id|mask3
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
id|dim0
suffix:semicolon
op_star
id|dim1
suffix:semicolon
op_star
id|dim2
suffix:semicolon
op_star
id|dim3
suffix:semicolon
macro_line|#else
r_volatile
r_int
r_int
op_star
id|dimB
suffix:semicolon
id|dimB
op_assign
op_amp
id|cchip-&gt;dim0.csr
suffix:semicolon
r_if
c_cond
(paren
id|bcpu
op_eq
l_int|1
)paren
id|dimB
op_assign
op_amp
id|cchip-&gt;dim1.csr
suffix:semicolon
r_else
r_if
c_cond
(paren
id|bcpu
op_eq
l_int|2
)paren
id|dimB
op_assign
op_amp
id|cchip-&gt;dim2.csr
suffix:semicolon
r_else
r_if
c_cond
(paren
id|bcpu
op_eq
l_int|3
)paren
id|dimB
op_assign
op_amp
id|cchip-&gt;dim3.csr
suffix:semicolon
op_star
id|dimB
op_assign
id|mask
op_or
id|isa_enable
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
id|dimB
suffix:semicolon
macro_line|#endif
)brace
r_static
r_inline
r_void
DECL|function|titan_enable_irq
id|titan_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|titan_irq_lock
)paren
suffix:semicolon
id|titan_cached_irq_mask
op_or_assign
l_int|1UL
op_lshift
(paren
id|irq
op_minus
l_int|16
)paren
suffix:semicolon
id|titan_update_irq_hw
c_func
(paren
id|titan_cached_irq_mask
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|titan_irq_lock
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|titan_disable_irq
id|titan_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|titan_irq_lock
)paren
suffix:semicolon
id|titan_cached_irq_mask
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
(paren
id|irq
op_minus
l_int|16
)paren
)paren
suffix:semicolon
id|titan_update_irq_hw
c_func
(paren
id|titan_cached_irq_mask
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|titan_irq_lock
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|titan_startup_irq
id|titan_startup_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|titan_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* never anything pending */
)brace
r_static
r_void
DECL|function|titan_end_irq
id|titan_end_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_amp
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
)paren
)paren
)paren
id|titan_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|titan_cpu_set_irq_affinity
id|titan_cpu_set_irq_affinity
c_func
(paren
r_int
r_int
id|irq
comma
id|cpumask_t
id|affinity
)paren
(brace
r_int
id|cpu
suffix:semicolon
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
l_int|4
suffix:semicolon
id|cpu
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cpu_isset
c_func
(paren
id|cpu
comma
id|affinity
)paren
)paren
id|titan_cpu_irq_affinity
(braket
id|cpu
)braket
op_or_assign
l_int|1UL
op_lshift
id|irq
suffix:semicolon
r_else
id|titan_cpu_irq_affinity
(braket
id|cpu
)braket
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
id|irq
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|titan_set_irq_affinity
id|titan_set_irq_affinity
c_func
(paren
r_int
r_int
id|irq
comma
id|cpumask_t
id|affinity
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|titan_irq_lock
)paren
suffix:semicolon
id|titan_cpu_set_irq_affinity
c_func
(paren
id|irq
op_minus
l_int|16
comma
id|affinity
)paren
suffix:semicolon
id|titan_update_irq_hw
c_func
(paren
id|titan_cached_irq_mask
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|titan_irq_lock
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|titan_device_interrupt
id|titan_device_interrupt
c_func
(paren
r_int
r_int
id|vector
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;titan_device_interrupt: NOT IMPLEMENTED YET!! &bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|titan_srm_device_interrupt
id|titan_srm_device_interrupt
c_func
(paren
r_int
r_int
id|vector
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|irq
suffix:semicolon
id|irq
op_assign
(paren
id|vector
op_minus
l_int|0x800
)paren
op_rshift
l_int|4
suffix:semicolon
id|handle_irq
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|init_titan_irqs
id|init_titan_irqs
c_func
(paren
r_struct
id|hw_interrupt_type
op_star
id|ops
comma
r_int
id|imin
comma
r_int
id|imax
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|imin
suffix:semicolon
id|i
op_le
id|imax
suffix:semicolon
op_increment
id|i
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
op_or
id|IRQ_LEVEL
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
id|ops
suffix:semicolon
)brace
)brace
DECL|variable|titan_irq_type
r_static
r_struct
id|hw_interrupt_type
id|titan_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;TITAN&quot;
comma
dot
id|startup
op_assign
id|titan_startup_irq
comma
dot
id|shutdown
op_assign
id|titan_disable_irq
comma
dot
id|enable
op_assign
id|titan_enable_irq
comma
dot
id|disable
op_assign
id|titan_disable_irq
comma
dot
id|ack
op_assign
id|titan_disable_irq
comma
dot
id|end
op_assign
id|titan_end_irq
comma
dot
id|set_affinity
op_assign
id|titan_set_irq_affinity
comma
)brace
suffix:semicolon
r_static
id|irqreturn_t
DECL|function|titan_intr_nop
id|titan_intr_nop
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/*&n;       * This is a NOP interrupt handler for the purposes of&n;       * event counting -- just return.&n;       */
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|titan_init_irq
id|titan_init_irq
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|alpha_using_srm
op_logical_and
op_logical_neg
id|alpha_mv.device_interrupt
)paren
id|alpha_mv.device_interrupt
op_assign
id|titan_srm_device_interrupt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|alpha_mv.device_interrupt
)paren
id|alpha_mv.device_interrupt
op_assign
id|titan_device_interrupt
suffix:semicolon
id|titan_update_irq_hw
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|init_titan_irqs
c_func
(paren
op_amp
id|titan_irq_type
comma
l_int|16
comma
l_int|63
op_plus
l_int|16
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|titan_legacy_init_irq
id|titan_legacy_init_irq
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* init the legacy dma controller */
id|outb
c_func
(paren
l_int|0
comma
id|DMA1_RESET_REG
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|DMA2_RESET_REG
)paren
suffix:semicolon
id|outb
c_func
(paren
id|DMA_MODE_CASCADE
comma
id|DMA2_MODE_REG
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|DMA2_MASK_REG
)paren
suffix:semicolon
multiline_comment|/* init the legacy irq controller */
id|init_i8259a_irqs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* init the titan irqs */
id|titan_init_irq
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|titan_dispatch_irqs
id|titan_dispatch_irqs
c_func
(paren
id|u64
id|mask
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|vector
suffix:semicolon
multiline_comment|/*&n;&t; * Mask down to those interrupts which are enable on this processor&n;&t; */
id|mask
op_and_assign
id|titan_cpu_irq_affinity
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Dispatch all requested interrupts &n;&t; */
r_while
c_loop
(paren
id|mask
)paren
(brace
multiline_comment|/* convert to SRM vector... priority is &lt;63&gt; -&gt; &lt;0&gt; */
id|__asm__
c_func
(paren
l_string|&quot;ctlz %1, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|vector
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
)paren
suffix:semicolon
id|vector
op_assign
l_int|63
op_minus
id|vector
suffix:semicolon
id|mask
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
id|vector
)paren
suffix:semicolon
multiline_comment|/* clear it out &t; */
id|vector
op_assign
l_int|0x900
op_plus
(paren
id|vector
op_lshift
l_int|4
)paren
suffix:semicolon
multiline_comment|/* convert to SRM vector */
multiline_comment|/* dispatch it */
id|alpha_mv
dot
id|device_interrupt
c_func
(paren
id|vector
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
"&f;"
multiline_comment|/*&n; * Titan Family&n; */
r_static
r_void
id|__init
DECL|function|titan_late_init
id|titan_late_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Enable the system error interrupts. These interrupts are &n;&t; * all reported to the kernel as machine checks, so the handler&n;&t; * is a nop so it can be called to count the individual events.&n;&t; */
id|request_irq
c_func
(paren
l_int|63
op_plus
l_int|16
comma
id|titan_intr_nop
comma
id|SA_INTERRUPT
comma
l_string|&quot;CChip Error&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|request_irq
c_func
(paren
l_int|62
op_plus
l_int|16
comma
id|titan_intr_nop
comma
id|SA_INTERRUPT
comma
l_string|&quot;PChip 0 H_Error&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|request_irq
c_func
(paren
l_int|61
op_plus
l_int|16
comma
id|titan_intr_nop
comma
id|SA_INTERRUPT
comma
l_string|&quot;PChip 1 H_Error&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|request_irq
c_func
(paren
l_int|60
op_plus
l_int|16
comma
id|titan_intr_nop
comma
id|SA_INTERRUPT
comma
l_string|&quot;PChip 0 C_Error&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|request_irq
c_func
(paren
l_int|59
op_plus
l_int|16
comma
id|titan_intr_nop
comma
id|SA_INTERRUPT
comma
l_string|&quot;PChip 1 C_Error&quot;
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Register our error handlers.&n;&t; */
id|titan_register_error_handlers
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check if the console left us any error logs.&n;&t; */
id|cdl_check_console_data_log
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_int
id|__devinit
DECL|function|titan_map_irq
id|titan_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
(brace
id|u8
id|intline
suffix:semicolon
r_int
id|irq
suffix:semicolon
multiline_comment|/* Get the current intline.  */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
op_amp
id|intline
)paren
suffix:semicolon
id|irq
op_assign
id|intline
suffix:semicolon
multiline_comment|/* Is it explicitly routed through ISA?  */
r_if
c_cond
(paren
(paren
id|irq
op_amp
l_int|0xF0
)paren
op_eq
l_int|0xE0
)paren
r_return
id|irq
suffix:semicolon
multiline_comment|/* Offset by 16 to make room for ISA interrupts 0 - 15.  */
r_return
id|irq
op_plus
l_int|16
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|titan_init_pci
id|titan_init_pci
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n; &t; * This isn&squot;t really the right place, but there&squot;s some init&n; &t; * that needs to be done after everything is basically up.&n; &t; */
id|titan_late_init
c_func
(paren
)paren
suffix:semicolon
id|pci_probe_only
op_assign
l_int|1
suffix:semicolon
id|common_init_pci
c_func
(paren
)paren
suffix:semicolon
id|SMC669_Init
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_VGA_HOSE
id|locate_and_init_vga
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
)brace
"&f;"
multiline_comment|/*&n; * Privateer&n; */
r_static
r_void
id|__init
DECL|function|privateer_init_pci
id|privateer_init_pci
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Hook a couple of extra err interrupts that the&n;&t; * common titan code won&squot;t.&n;&t; */
id|request_irq
c_func
(paren
l_int|53
op_plus
l_int|16
comma
id|titan_intr_nop
comma
id|SA_INTERRUPT
comma
l_string|&quot;NMI&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|request_irq
c_func
(paren
l_int|50
op_plus
l_int|16
comma
id|titan_intr_nop
comma
id|SA_INTERRUPT
comma
l_string|&quot;Temperature Warning&quot;
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Finish with the common version.&n;&t; */
r_return
id|titan_init_pci
c_func
(paren
)paren
suffix:semicolon
)brace
"&f;"
multiline_comment|/*&n; * The System Vectors.&n; */
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|titan_mv
id|__initmv
op_assign
(brace
dot
id|vector_name
op_assign
l_string|&quot;TITAN&quot;
comma
id|DO_EV6_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_TITAN_IO
comma
dot
id|machine_check
op_assign
id|titan_machine_check
comma
dot
id|max_isa_dma_address
op_assign
id|ALPHA_MAX_ISA_DMA_ADDRESS
comma
dot
id|min_io_address
op_assign
id|DEFAULT_IO_BASE
comma
dot
id|min_mem_address
op_assign
id|DEFAULT_MEM_BASE
comma
dot
id|pci_dac_offset
op_assign
id|TITAN_DAC_OFFSET
comma
dot
id|nr_irqs
op_assign
l_int|80
comma
multiline_comment|/* 64 + 16 */
multiline_comment|/* device_interrupt will be filled in by titan_init_irq */
dot
id|agp_info
op_assign
id|titan_agp_info
comma
dot
id|init_arch
op_assign
id|titan_init_arch
comma
dot
id|init_irq
op_assign
id|titan_legacy_init_irq
comma
dot
id|init_rtc
op_assign
id|common_init_rtc
comma
dot
id|init_pci
op_assign
id|titan_init_pci
comma
dot
id|kill_arch
op_assign
id|titan_kill_arch
comma
dot
id|pci_map_irq
op_assign
id|titan_map_irq
comma
dot
id|pci_swizzle
op_assign
id|common_swizzle
comma
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|titan
)paren
r_struct
id|alpha_machine_vector
id|privateer_mv
id|__initmv
op_assign
(brace
dot
id|vector_name
op_assign
l_string|&quot;PRIVATEER&quot;
comma
id|DO_EV6_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_TITAN_IO
comma
dot
id|machine_check
op_assign
id|privateer_machine_check
comma
dot
id|max_isa_dma_address
op_assign
id|ALPHA_MAX_ISA_DMA_ADDRESS
comma
dot
id|min_io_address
op_assign
id|DEFAULT_IO_BASE
comma
dot
id|min_mem_address
op_assign
id|DEFAULT_MEM_BASE
comma
dot
id|pci_dac_offset
op_assign
id|TITAN_DAC_OFFSET
comma
dot
id|nr_irqs
op_assign
l_int|80
comma
multiline_comment|/* 64 + 16 */
multiline_comment|/* device_interrupt will be filled in by titan_init_irq */
dot
id|agp_info
op_assign
id|titan_agp_info
comma
dot
id|init_arch
op_assign
id|titan_init_arch
comma
dot
id|init_irq
op_assign
id|titan_legacy_init_irq
comma
dot
id|init_rtc
op_assign
id|common_init_rtc
comma
dot
id|init_pci
op_assign
id|privateer_init_pci
comma
dot
id|kill_arch
op_assign
id|titan_kill_arch
comma
dot
id|pci_map_irq
op_assign
id|titan_map_irq
comma
dot
id|pci_swizzle
op_assign
id|common_swizzle
comma
)brace
suffix:semicolon
multiline_comment|/* No alpha_mv alias for privateer since we compile it &n;   in unconditionally with titan; setup_arch knows how to cope. */
eof
