multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_dp264.c&n; *&n; *&t;Copyright (C) 1995 David A Rusling&n; *&t;Copyright (C) 1996, 1999 Jay A Estabrook&n; *&t;Copyright (C) 1998, 1999 Richard Henderson&n; *&n; *&t;Modified by Christopher C. Chimelis, 2001 to&n; *&t;add support for the addition of Shark to the&n; *&t;Tsunami family.&n; *&n; * Code supporting the DP264 (EV6+TSUNAMI).&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/core_tsunami.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq_impl.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
macro_line|#include &quot;machvec_impl.h&quot;
multiline_comment|/* Note mask bit is true for ENABLED irqs.  */
DECL|variable|cached_irq_mask
r_static
r_int
r_int
id|cached_irq_mask
suffix:semicolon
multiline_comment|/* dp264 boards handle at max four CPUs */
DECL|variable|cpu_irq_affinity
r_static
r_int
r_int
id|cpu_irq_affinity
(braket
l_int|4
)braket
op_assign
(brace
l_int|0UL
comma
l_int|0UL
comma
l_int|0UL
comma
l_int|0UL
)brace
suffix:semicolon
DECL|variable|dp264_irq_lock
id|spinlock_t
id|dp264_irq_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_static
r_void
DECL|function|tsunami_update_irq_hw
id|tsunami_update_irq_hw
c_func
(paren
r_int
r_int
id|mask
)paren
(brace
r_register
id|tsunami_cchip
op_star
id|cchip
op_assign
id|TSUNAMI_cchip
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
r_register
r_int
r_int
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
id|cpu_irq_affinity
(braket
l_int|0
)braket
suffix:semicolon
id|mask1
op_assign
id|mask
op_amp
id|cpu_irq_affinity
(braket
l_int|1
)braket
suffix:semicolon
id|mask2
op_assign
id|mask
op_amp
id|cpu_irq_affinity
(braket
l_int|2
)braket
suffix:semicolon
id|mask3
op_assign
id|mask
op_amp
id|cpu_irq_affinity
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
(paren
id|cpm
op_amp
l_int|1
)paren
op_eq
l_int|0
)paren
id|dim0
op_assign
op_amp
id|dummy
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cpm
op_amp
l_int|2
)paren
op_eq
l_int|0
)paren
id|dim1
op_assign
op_amp
id|dummy
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cpm
op_amp
l_int|4
)paren
op_eq
l_int|0
)paren
id|dim2
op_assign
op_amp
id|dummy
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cpm
op_amp
l_int|8
)paren
op_eq
l_int|0
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
r_if
c_cond
(paren
id|bcpu
op_eq
l_int|0
)paren
id|dimB
op_assign
op_amp
id|cchip-&gt;dim0.csr
suffix:semicolon
r_else
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
r_void
DECL|function|dp264_enable_irq
id|dp264_enable_irq
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
id|dp264_irq_lock
)paren
suffix:semicolon
id|cached_irq_mask
op_or_assign
l_int|1UL
op_lshift
id|irq
suffix:semicolon
id|tsunami_update_irq_hw
c_func
(paren
id|cached_irq_mask
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dp264_irq_lock
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|dp264_disable_irq
id|dp264_disable_irq
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
id|dp264_irq_lock
)paren
suffix:semicolon
id|cached_irq_mask
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
id|irq
)paren
suffix:semicolon
id|tsunami_update_irq_hw
c_func
(paren
id|cached_irq_mask
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dp264_irq_lock
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|dp264_startup_irq
id|dp264_startup_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|dp264_enable_irq
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
DECL|function|dp264_end_irq
id|dp264_end_irq
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
id|dp264_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|clipper_enable_irq
id|clipper_enable_irq
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
id|dp264_irq_lock
)paren
suffix:semicolon
id|cached_irq_mask
op_or_assign
l_int|1UL
op_lshift
(paren
id|irq
op_minus
l_int|16
)paren
suffix:semicolon
id|tsunami_update_irq_hw
c_func
(paren
id|cached_irq_mask
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dp264_irq_lock
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|clipper_disable_irq
id|clipper_disable_irq
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
id|dp264_irq_lock
)paren
suffix:semicolon
id|cached_irq_mask
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
id|tsunami_update_irq_hw
c_func
(paren
id|cached_irq_mask
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dp264_irq_lock
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|clipper_startup_irq
id|clipper_startup_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|clipper_enable_irq
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
DECL|function|clipper_end_irq
id|clipper_end_irq
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
id|clipper_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|cpu_set_irq_affinity
id|cpu_set_irq_affinity
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
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
r_int
r_int
id|aff
op_assign
id|cpu_irq_affinity
(braket
id|cpu
)braket
suffix:semicolon
r_if
c_cond
(paren
id|affinity
op_amp
(paren
l_int|1UL
op_lshift
id|cpu
)paren
)paren
id|aff
op_or_assign
l_int|1UL
op_lshift
id|irq
suffix:semicolon
r_else
id|aff
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
id|irq
)paren
suffix:semicolon
id|cpu_irq_affinity
(braket
id|cpu
)braket
op_assign
id|aff
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|dp264_set_affinity
id|dp264_set_affinity
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|affinity
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|dp264_irq_lock
)paren
suffix:semicolon
id|cpu_set_irq_affinity
c_func
(paren
id|irq
comma
id|affinity
)paren
suffix:semicolon
id|tsunami_update_irq_hw
c_func
(paren
id|cached_irq_mask
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dp264_irq_lock
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|clipper_set_affinity
id|clipper_set_affinity
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|affinity
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|dp264_irq_lock
)paren
suffix:semicolon
id|cpu_set_irq_affinity
c_func
(paren
id|irq
op_minus
l_int|16
comma
id|affinity
)paren
suffix:semicolon
id|tsunami_update_irq_hw
c_func
(paren
id|cached_irq_mask
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dp264_irq_lock
)paren
suffix:semicolon
)brace
DECL|variable|dp264_irq_type
r_static
r_struct
id|hw_interrupt_type
id|dp264_irq_type
op_assign
(brace
r_typename
suffix:colon
l_string|&quot;DP264&quot;
comma
id|startup
suffix:colon
id|dp264_startup_irq
comma
id|shutdown
suffix:colon
id|dp264_disable_irq
comma
id|enable
suffix:colon
id|dp264_enable_irq
comma
id|disable
suffix:colon
id|dp264_disable_irq
comma
id|ack
suffix:colon
id|dp264_disable_irq
comma
id|end
suffix:colon
id|dp264_end_irq
comma
id|set_affinity
suffix:colon
id|dp264_set_affinity
comma
)brace
suffix:semicolon
DECL|variable|clipper_irq_type
r_static
r_struct
id|hw_interrupt_type
id|clipper_irq_type
op_assign
(brace
r_typename
suffix:colon
l_string|&quot;CLIPPER&quot;
comma
id|startup
suffix:colon
id|clipper_startup_irq
comma
id|shutdown
suffix:colon
id|clipper_disable_irq
comma
id|enable
suffix:colon
id|clipper_enable_irq
comma
id|disable
suffix:colon
id|clipper_disable_irq
comma
id|ack
suffix:colon
id|clipper_disable_irq
comma
id|end
suffix:colon
id|clipper_end_irq
comma
id|set_affinity
suffix:colon
id|clipper_set_affinity
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|dp264_device_interrupt
id|dp264_device_interrupt
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
macro_line|#if 1
id|printk
c_func
(paren
l_string|&quot;dp264_device_interrupt: NOT IMPLEMENTED YET!! &bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
r_int
r_int
id|pld
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/* Read the interrupt summary register of TSUNAMI */
id|pld
op_assign
id|TSUNAMI_cchip-&gt;dir0.csr
suffix:semicolon
multiline_comment|/*&n;&t; * Now for every possible bit set, work through them and call&n;&t; * the appropriate interrupt handler.&n;&t; */
r_while
c_loop
(paren
id|pld
)paren
(brace
id|i
op_assign
id|ffz
c_func
(paren
op_complement
id|pld
)paren
suffix:semicolon
id|pld
op_and_assign
id|pld
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* clear least bit set */
r_if
c_cond
(paren
id|i
op_eq
l_int|55
)paren
id|isa_device_interrupt
c_func
(paren
id|vector
comma
id|regs
)paren
suffix:semicolon
r_else
id|handle_irq
c_func
(paren
l_int|16
op_plus
id|i
comma
l_int|16
op_plus
id|i
comma
id|regs
)paren
suffix:semicolon
macro_line|#if 0
id|TSUNAMI_cchip-&gt;dir0.csr
op_assign
l_int|1UL
op_lshift
id|i
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|tmp
op_assign
id|TSUNAMI_cchip-&gt;dir0.csr
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
)brace
r_static
r_void
DECL|function|dp264_srm_device_interrupt
id|dp264_srm_device_interrupt
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
multiline_comment|/*&n;&t; * The SRM console reports PCI interrupts with a vector calculated by:&n;&t; *&n;&t; *&t;0x900 + (0x10 * DRIR-bit)&n;&t; *&n;&t; * So bit 16 shows up as IRQ 32, etc.&n;&t; * &n;&t; * On DP264/BRICK/MONET, we adjust it down by 16 because at least&n;&t; * that many of the low order bits of the DRIR are not used, and&n;&t; * so we don&squot;t count them.&n;&t; */
r_if
c_cond
(paren
id|irq
op_ge
l_int|32
)paren
id|irq
op_sub_assign
l_int|16
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
DECL|function|clipper_srm_device_interrupt
id|clipper_srm_device_interrupt
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
multiline_comment|/*&n;&t; * The SRM console reports PCI interrupts with a vector calculated by:&n;&t; *&n;&t; *&t;0x900 + (0x10 * DRIR-bit)&n;&t; *&n;&t; * So bit 16 shows up as IRQ 32, etc.&n;&t; * &n;&t; * CLIPPER uses bits 8-47 for PCI interrupts, so we do not need&n;&t; * to scale down the vector reported, we just use it.&n;&t; *&n;&t; * Eg IRQ 24 is DRIR bit 8, etc, etc&n;&t; */
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
DECL|function|init_tsunami_irqs
id|init_tsunami_irqs
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
r_static
r_void
id|__init
DECL|function|dp264_init_irq
id|dp264_init_irq
c_func
(paren
r_void
)paren
(brace
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
r_if
c_cond
(paren
id|alpha_using_srm
)paren
id|alpha_mv.device_interrupt
op_assign
id|dp264_srm_device_interrupt
suffix:semicolon
id|tsunami_update_irq_hw
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|init_i8259a_irqs
c_func
(paren
)paren
suffix:semicolon
id|init_tsunami_irqs
c_func
(paren
op_amp
id|dp264_irq_type
comma
l_int|16
comma
l_int|47
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|clipper_init_irq
id|clipper_init_irq
c_func
(paren
r_void
)paren
(brace
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
r_if
c_cond
(paren
id|alpha_using_srm
)paren
id|alpha_mv.device_interrupt
op_assign
id|clipper_srm_device_interrupt
suffix:semicolon
id|tsunami_update_irq_hw
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|init_i8259a_irqs
c_func
(paren
)paren
suffix:semicolon
id|init_tsunami_irqs
c_func
(paren
op_amp
id|clipper_irq_type
comma
l_int|24
comma
l_int|63
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * PCI Fixup configuration.&n; *&n; * Summary @ TSUNAMI_CSR_DIM0:&n; * Bit      Meaning&n; * 0-17     Unused&n; *18        Interrupt SCSI B (Adaptec 7895 builtin)&n; *19        Interrupt SCSI A (Adaptec 7895 builtin)&n; *20        Interrupt Line D from slot 2 PCI0&n; *21        Interrupt Line C from slot 2 PCI0&n; *22        Interrupt Line B from slot 2 PCI0&n; *23        Interrupt Line A from slot 2 PCI0&n; *24        Interrupt Line D from slot 1 PCI0&n; *25        Interrupt Line C from slot 1 PCI0&n; *26        Interrupt Line B from slot 1 PCI0&n; *27        Interrupt Line A from slot 1 PCI0&n; *28        Interrupt Line D from slot 0 PCI0&n; *29        Interrupt Line C from slot 0 PCI0&n; *30        Interrupt Line B from slot 0 PCI0&n; *31        Interrupt Line A from slot 0 PCI0&n; *&n; *32        Interrupt Line D from slot 3 PCI1&n; *33        Interrupt Line C from slot 3 PCI1&n; *34        Interrupt Line B from slot 3 PCI1&n; *35        Interrupt Line A from slot 3 PCI1&n; *36        Interrupt Line D from slot 2 PCI1&n; *37        Interrupt Line C from slot 2 PCI1&n; *38        Interrupt Line B from slot 2 PCI1&n; *39        Interrupt Line A from slot 2 PCI1&n; *40        Interrupt Line D from slot 1 PCI1&n; *41        Interrupt Line C from slot 1 PCI1&n; *42        Interrupt Line B from slot 1 PCI1&n; *43        Interrupt Line A from slot 1 PCI1&n; *44        Interrupt Line D from slot 0 PCI1&n; *45        Interrupt Line C from slot 0 PCI1&n; *46        Interrupt Line B from slot 0 PCI1&n; *47        Interrupt Line A from slot 0 PCI1&n; *48-52     Unused&n; *53        PCI0 NMI (from Cypress)&n; *54        PCI0 SMI INT (from Cypress)&n; *55        PCI0 ISA Interrupt (from Cypress)&n; *56-60     Unused&n; *61        PCI1 Bus Error&n; *62        PCI0 Bus Error&n; *63        Reserved&n; *&n; * IdSel&t;&n; *   5&t; Cypress Bridge I/O&n; *   6&t; SCSI Adaptec builtin&n; *   7&t; 64 bit PCI option slot 0 (all busses)&n; *   8&t; 64 bit PCI option slot 1 (all busses)&n; *   9&t; 64 bit PCI option slot 2 (all busses)&n; *  10&t; 64 bit PCI option slot 3 (not bus 0)&n; */
r_static
r_int
id|__init
DECL|function|dp264_map_irq
id|dp264_map_irq
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
r_static
r_char
id|irq_tab
(braket
l_int|6
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*INT    INTA   INTB   INTC   INTD */
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* IdSel 5 ISA Bridge */
(brace
l_int|16
op_plus
l_int|3
comma
l_int|16
op_plus
l_int|3
comma
l_int|16
op_plus
l_int|2
comma
l_int|16
op_plus
l_int|2
comma
l_int|16
op_plus
l_int|2
)brace
comma
multiline_comment|/* IdSel 6 SCSI builtin*/
(brace
l_int|16
op_plus
l_int|15
comma
l_int|16
op_plus
l_int|15
comma
l_int|16
op_plus
l_int|14
comma
l_int|16
op_plus
l_int|13
comma
l_int|16
op_plus
l_int|12
)brace
comma
multiline_comment|/* IdSel 7 slot 0 */
(brace
l_int|16
op_plus
l_int|11
comma
l_int|16
op_plus
l_int|11
comma
l_int|16
op_plus
l_int|10
comma
l_int|16
op_plus
l_int|9
comma
l_int|16
op_plus
l_int|8
)brace
comma
multiline_comment|/* IdSel 8 slot 1 */
(brace
l_int|16
op_plus
l_int|7
comma
l_int|16
op_plus
l_int|7
comma
l_int|16
op_plus
l_int|6
comma
l_int|16
op_plus
l_int|5
comma
l_int|16
op_plus
l_int|4
)brace
comma
multiline_comment|/* IdSel 9 slot 2 */
(brace
l_int|16
op_plus
l_int|3
comma
l_int|16
op_plus
l_int|3
comma
l_int|16
op_plus
l_int|2
comma
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|0
)brace
multiline_comment|/* IdSel 10 slot 3 */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|5
comma
id|max_idsel
op_assign
l_int|10
comma
id|irqs_per_slot
op_assign
l_int|5
suffix:semicolon
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|dev-&gt;sysdata
suffix:semicolon
r_int
id|irq
op_assign
id|COMMON_TABLE_LOOKUP
suffix:semicolon
r_if
c_cond
(paren
id|irq
OG
l_int|0
)paren
(brace
id|irq
op_add_assign
l_int|16
op_star
id|hose-&gt;index
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* ??? The Contaq IDE controller on the ISA bridge uses&n;&t;&t;   &quot;legacy&quot; interrupts 14 and 15.  I don&squot;t know if anything&n;&t;&t;   can wind up at the same slot+pin on hose1, so we&squot;ll&n;&t;&t;   just have to trust whatever value the console might&n;&t;&t;   have assigned.  */
id|u8
id|irq8
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
op_amp
id|irq8
)paren
suffix:semicolon
id|irq
op_assign
id|irq8
suffix:semicolon
)brace
r_return
id|irq
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|monet_map_irq
id|monet_map_irq
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
r_static
r_char
id|irq_tab
(braket
l_int|13
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*INT    INTA   INTB   INTC   INTD */
(brace
l_int|45
comma
l_int|45
comma
l_int|45
comma
l_int|45
comma
l_int|45
)brace
comma
multiline_comment|/* IdSel 3 21143 PCI1 */
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* IdSel 4 unused */
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* IdSel 5 unused */
(brace
l_int|47
comma
l_int|47
comma
l_int|47
comma
l_int|47
comma
l_int|47
)brace
comma
multiline_comment|/* IdSel 6 SCSI PCI1 */
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* IdSel 7 ISA Bridge */
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* IdSel 8 P2P PCI1 */
macro_line|#if 1
(brace
l_int|28
comma
l_int|28
comma
l_int|29
comma
l_int|30
comma
l_int|31
)brace
comma
multiline_comment|/* IdSel 14 slot 4 PCI2*/
(brace
l_int|24
comma
l_int|24
comma
l_int|25
comma
l_int|26
comma
l_int|27
)brace
comma
multiline_comment|/* IdSel 15 slot 5 PCI2*/
macro_line|#else
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* IdSel 9 unused */
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* IdSel 10 unused */
macro_line|#endif
(brace
l_int|40
comma
l_int|40
comma
l_int|41
comma
l_int|42
comma
l_int|43
)brace
comma
multiline_comment|/* IdSel 11 slot 1 PCI0*/
(brace
l_int|36
comma
l_int|36
comma
l_int|37
comma
l_int|38
comma
l_int|39
)brace
comma
multiline_comment|/* IdSel 12 slot 2 PCI0*/
(brace
l_int|32
comma
l_int|32
comma
l_int|33
comma
l_int|34
comma
l_int|35
)brace
comma
multiline_comment|/* IdSel 13 slot 3 PCI0*/
(brace
l_int|28
comma
l_int|28
comma
l_int|29
comma
l_int|30
comma
l_int|31
)brace
comma
multiline_comment|/* IdSel 14 slot 4 PCI2*/
(brace
l_int|24
comma
l_int|24
comma
l_int|25
comma
l_int|26
comma
l_int|27
)brace
multiline_comment|/* IdSel 15 slot 5 PCI2*/
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|3
comma
id|max_idsel
op_assign
l_int|15
comma
id|irqs_per_slot
op_assign
l_int|5
suffix:semicolon
r_return
id|COMMON_TABLE_LOOKUP
suffix:semicolon
)brace
r_static
id|u8
id|__init
DECL|function|monet_swizzle
id|monet_swizzle
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
op_star
id|pinp
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|dev-&gt;sysdata
suffix:semicolon
r_int
id|slot
comma
id|pin
op_assign
op_star
id|pinp
suffix:semicolon
r_if
c_cond
(paren
id|hose-&gt;first_busno
op_eq
id|dev-&gt;bus-&gt;number
)paren
(brace
id|slot
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
)brace
multiline_comment|/* Check for the built-in bridge on hose 1. */
r_else
r_if
c_cond
(paren
id|hose-&gt;index
op_eq
l_int|1
op_logical_and
id|PCI_SLOT
c_func
(paren
id|dev-&gt;bus-&gt;self-&gt;devfn
)paren
op_eq
l_int|8
)paren
(brace
id|slot
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Must be a card-based bridge.  */
r_do
(brace
multiline_comment|/* Check for built-in bridge on hose 1. */
r_if
c_cond
(paren
id|hose-&gt;index
op_eq
l_int|1
op_logical_and
id|PCI_SLOT
c_func
(paren
id|dev-&gt;bus-&gt;self-&gt;devfn
)paren
op_eq
l_int|8
)paren
(brace
id|slot
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pin
op_assign
id|bridge_swizzle
c_func
(paren
id|pin
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
multiline_comment|/* Move up the chain of bridges.  */
id|dev
op_assign
id|dev-&gt;bus-&gt;self
suffix:semicolon
multiline_comment|/* Slot of the next bridge.  */
id|slot
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|dev-&gt;bus-&gt;self
)paren
suffix:semicolon
)brace
op_star
id|pinp
op_assign
id|pin
suffix:semicolon
r_return
id|slot
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|webbrick_map_irq
id|webbrick_map_irq
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
r_static
r_char
id|irq_tab
(braket
l_int|13
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*INT    INTA   INTB   INTC   INTD */
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* IdSel 7 ISA Bridge */
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* IdSel 8 unused */
(brace
l_int|29
comma
l_int|29
comma
l_int|29
comma
l_int|29
comma
l_int|29
)brace
comma
multiline_comment|/* IdSel 9 21143 #1 */
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* IdSel 10 unused */
(brace
l_int|30
comma
l_int|30
comma
l_int|30
comma
l_int|30
comma
l_int|30
)brace
comma
multiline_comment|/* IdSel 11 21143 #2 */
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* IdSel 12 unused */
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* IdSel 13 unused */
(brace
l_int|35
comma
l_int|35
comma
l_int|34
comma
l_int|33
comma
l_int|32
)brace
comma
multiline_comment|/* IdSel 14 slot 0 */
(brace
l_int|39
comma
l_int|39
comma
l_int|38
comma
l_int|37
comma
l_int|36
)brace
comma
multiline_comment|/* IdSel 15 slot 1 */
(brace
l_int|43
comma
l_int|43
comma
l_int|42
comma
l_int|41
comma
l_int|40
)brace
comma
multiline_comment|/* IdSel 16 slot 2 */
(brace
l_int|47
comma
l_int|47
comma
l_int|46
comma
l_int|45
comma
l_int|44
)brace
comma
multiline_comment|/* IdSel 17 slot 3 */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|7
comma
id|max_idsel
op_assign
l_int|17
comma
id|irqs_per_slot
op_assign
l_int|5
suffix:semicolon
r_return
id|COMMON_TABLE_LOOKUP
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|clipper_map_irq
id|clipper_map_irq
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
r_static
r_char
id|irq_tab
(braket
l_int|7
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*INT    INTA   INTB   INTC   INTD */
(brace
l_int|16
op_plus
l_int|8
comma
l_int|16
op_plus
l_int|8
comma
l_int|16
op_plus
l_int|9
comma
l_int|16
op_plus
l_int|10
comma
l_int|16
op_plus
l_int|11
)brace
comma
multiline_comment|/* IdSel 1 slot 1 */
(brace
l_int|16
op_plus
l_int|12
comma
l_int|16
op_plus
l_int|12
comma
l_int|16
op_plus
l_int|13
comma
l_int|16
op_plus
l_int|14
comma
l_int|16
op_plus
l_int|15
)brace
comma
multiline_comment|/* IdSel 2 slot 2 */
(brace
l_int|16
op_plus
l_int|16
comma
l_int|16
op_plus
l_int|16
comma
l_int|16
op_plus
l_int|17
comma
l_int|16
op_plus
l_int|18
comma
l_int|16
op_plus
l_int|19
)brace
comma
multiline_comment|/* IdSel 3 slot 3 */
(brace
l_int|16
op_plus
l_int|20
comma
l_int|16
op_plus
l_int|20
comma
l_int|16
op_plus
l_int|21
comma
l_int|16
op_plus
l_int|22
comma
l_int|16
op_plus
l_int|23
)brace
comma
multiline_comment|/* IdSel 4 slot 4 */
(brace
l_int|16
op_plus
l_int|24
comma
l_int|16
op_plus
l_int|24
comma
l_int|16
op_plus
l_int|25
comma
l_int|16
op_plus
l_int|26
comma
l_int|16
op_plus
l_int|27
)brace
comma
multiline_comment|/* IdSel 5 slot 5 */
(brace
l_int|16
op_plus
l_int|28
comma
l_int|16
op_plus
l_int|28
comma
l_int|16
op_plus
l_int|29
comma
l_int|16
op_plus
l_int|30
comma
l_int|16
op_plus
l_int|31
)brace
comma
multiline_comment|/* IdSel 6 slot 6 */
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
multiline_comment|/* IdSel 7 ISA Bridge */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|1
comma
id|max_idsel
op_assign
l_int|7
comma
id|irqs_per_slot
op_assign
l_int|5
suffix:semicolon
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|dev-&gt;sysdata
suffix:semicolon
r_int
id|irq
op_assign
id|COMMON_TABLE_LOOKUP
suffix:semicolon
r_if
c_cond
(paren
id|irq
OG
l_int|0
)paren
id|irq
op_add_assign
l_int|16
op_star
id|hose-&gt;index
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|dp264_init_pci
id|dp264_init_pci
c_func
(paren
r_void
)paren
(brace
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
)brace
r_static
r_void
id|__init
DECL|function|monet_init_pci
id|monet_init_pci
c_func
(paren
r_void
)paren
(brace
id|common_init_pci
c_func
(paren
)paren
suffix:semicolon
id|SMC669_Init
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|es1888_init
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|webbrick_init_arch
id|webbrick_init_arch
c_func
(paren
r_void
)paren
(brace
id|tsunami_init_arch
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Tsunami caches 4 PTEs at a time; DS10 has only 1 hose. */
id|hose_head-&gt;sg_isa-&gt;align_entry
op_assign
l_int|4
suffix:semicolon
id|hose_head-&gt;sg_pci-&gt;align_entry
op_assign
l_int|4
suffix:semicolon
)brace
multiline_comment|/*&n; * The System Vectors&n; */
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|dp264_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;DP264&quot;
comma
id|DO_EV6_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_TSUNAMI_IO
comma
id|DO_TSUNAMI_BUS
comma
id|machine_check
suffix:colon
id|tsunami_machine_check
comma
id|max_dma_address
suffix:colon
id|ALPHA_MAX_DMA_ADDRESS
comma
id|min_io_address
suffix:colon
id|DEFAULT_IO_BASE
comma
id|min_mem_address
suffix:colon
id|DEFAULT_MEM_BASE
comma
id|pci_dac_offset
suffix:colon
id|TSUNAMI_DAC_OFFSET
comma
id|nr_irqs
suffix:colon
l_int|64
comma
id|device_interrupt
suffix:colon
id|dp264_device_interrupt
comma
id|init_arch
suffix:colon
id|tsunami_init_arch
comma
id|init_irq
suffix:colon
id|dp264_init_irq
comma
id|init_rtc
suffix:colon
id|common_init_rtc
comma
id|init_pci
suffix:colon
id|dp264_init_pci
comma
id|kill_arch
suffix:colon
id|tsunami_kill_arch
comma
id|pci_map_irq
suffix:colon
id|dp264_map_irq
comma
id|pci_swizzle
suffix:colon
id|common_swizzle
comma
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|dp264
)paren
r_struct
id|alpha_machine_vector
id|monet_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;Monet&quot;
comma
id|DO_EV6_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_TSUNAMI_IO
comma
id|DO_TSUNAMI_BUS
comma
id|machine_check
suffix:colon
id|tsunami_machine_check
comma
id|max_dma_address
suffix:colon
id|ALPHA_MAX_DMA_ADDRESS
comma
id|min_io_address
suffix:colon
id|DEFAULT_IO_BASE
comma
id|min_mem_address
suffix:colon
id|DEFAULT_MEM_BASE
comma
id|pci_dac_offset
suffix:colon
id|TSUNAMI_DAC_OFFSET
comma
id|nr_irqs
suffix:colon
l_int|64
comma
id|device_interrupt
suffix:colon
id|dp264_device_interrupt
comma
id|init_arch
suffix:colon
id|tsunami_init_arch
comma
id|init_irq
suffix:colon
id|dp264_init_irq
comma
id|init_rtc
suffix:colon
id|common_init_rtc
comma
id|init_pci
suffix:colon
id|monet_init_pci
comma
id|kill_arch
suffix:colon
id|tsunami_kill_arch
comma
id|pci_map_irq
suffix:colon
id|monet_map_irq
comma
id|pci_swizzle
suffix:colon
id|monet_swizzle
comma
)brace
suffix:semicolon
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|webbrick_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;Webbrick&quot;
comma
id|DO_EV6_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_TSUNAMI_IO
comma
id|DO_TSUNAMI_BUS
comma
id|machine_check
suffix:colon
id|tsunami_machine_check
comma
id|max_dma_address
suffix:colon
id|ALPHA_MAX_DMA_ADDRESS
comma
id|min_io_address
suffix:colon
id|DEFAULT_IO_BASE
comma
id|min_mem_address
suffix:colon
id|DEFAULT_MEM_BASE
comma
id|pci_dac_offset
suffix:colon
id|TSUNAMI_DAC_OFFSET
comma
id|nr_irqs
suffix:colon
l_int|64
comma
id|device_interrupt
suffix:colon
id|dp264_device_interrupt
comma
id|init_arch
suffix:colon
id|webbrick_init_arch
comma
id|init_irq
suffix:colon
id|dp264_init_irq
comma
id|init_rtc
suffix:colon
id|common_init_rtc
comma
id|init_pci
suffix:colon
id|common_init_pci
comma
id|kill_arch
suffix:colon
id|tsunami_kill_arch
comma
id|pci_map_irq
suffix:colon
id|webbrick_map_irq
comma
id|pci_swizzle
suffix:colon
id|common_swizzle
comma
)brace
suffix:semicolon
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|clipper_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;Clipper&quot;
comma
id|DO_EV6_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_TSUNAMI_IO
comma
id|DO_TSUNAMI_BUS
comma
id|machine_check
suffix:colon
id|tsunami_machine_check
comma
id|max_dma_address
suffix:colon
id|ALPHA_MAX_DMA_ADDRESS
comma
id|min_io_address
suffix:colon
id|DEFAULT_IO_BASE
comma
id|min_mem_address
suffix:colon
id|DEFAULT_MEM_BASE
comma
id|pci_dac_offset
suffix:colon
id|TSUNAMI_DAC_OFFSET
comma
id|nr_irqs
suffix:colon
l_int|64
comma
id|device_interrupt
suffix:colon
id|dp264_device_interrupt
comma
id|init_arch
suffix:colon
id|tsunami_init_arch
comma
id|init_irq
suffix:colon
id|clipper_init_irq
comma
id|init_rtc
suffix:colon
id|common_init_rtc
comma
id|init_pci
suffix:colon
id|common_init_pci
comma
id|kill_arch
suffix:colon
id|tsunami_kill_arch
comma
id|pci_map_irq
suffix:colon
id|clipper_map_irq
comma
id|pci_swizzle
suffix:colon
id|common_swizzle
comma
)brace
suffix:semicolon
multiline_comment|/* Sharks strongly resemble Clipper, at least as far&n; * as interrupt routing, etc, so we&squot;re using the&n; * same functions as Clipper does&n; */
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|shark_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;Shark&quot;
comma
id|DO_EV6_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_TSUNAMI_IO
comma
id|DO_TSUNAMI_BUS
comma
id|machine_check
suffix:colon
id|tsunami_machine_check
comma
id|max_dma_address
suffix:colon
id|ALPHA_MAX_DMA_ADDRESS
comma
id|min_io_address
suffix:colon
id|DEFAULT_IO_BASE
comma
id|min_mem_address
suffix:colon
id|DEFAULT_MEM_BASE
comma
id|pci_dac_offset
suffix:colon
id|TSUNAMI_DAC_OFFSET
comma
id|nr_irqs
suffix:colon
l_int|64
comma
id|device_interrupt
suffix:colon
id|dp264_device_interrupt
comma
id|init_arch
suffix:colon
id|tsunami_init_arch
comma
id|init_irq
suffix:colon
id|clipper_init_irq
comma
id|init_rtc
suffix:colon
id|common_init_rtc
comma
id|init_pci
suffix:colon
id|common_init_pci
comma
id|kill_arch
suffix:colon
id|tsunami_kill_arch
comma
id|pci_map_irq
suffix:colon
id|clipper_map_irq
comma
id|pci_swizzle
suffix:colon
id|common_swizzle
comma
)brace
suffix:semicolon
multiline_comment|/* No alpha_mv alias for webbrick/monet/clipper, since we compile them&n;   in unconditionally with DP264; setup_arch knows how to cope.  */
eof
