multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_titan.c&n; *&n; *&t;Copyright (C) 1995 David A Rusling&n; *&t;Copyright (C) 1996, 1999 Jay A Estabrook&n; *&t;Copyright (C) 1998, 1999 Richard Henderson&n; *      Copyright (C) 1999, 2000 Jeff Wiedemeier&n; *&n; * Code supporting TITAN systems (EV6+TITAN), currently:&n; *      Privateer&n; */
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
macro_line|#include &lt;asm/core_titan.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq_impl.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
macro_line|#include &quot;machvec_impl.h&quot;
multiline_comment|/* Note mask bit is true for ENABLED irqs. */
DECL|variable|cached_irq_mask
r_static
r_int
r_int
id|cached_irq_mask
suffix:semicolon
multiline_comment|/* Titan boards handle at most four CPUs.  */
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
DECL|function|privateer_enable_irq
id|privateer_enable_irq
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
id|titan_update_irq_hw
c_func
(paren
id|cached_irq_mask
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
DECL|function|privateer_disable_irq
id|privateer_disable_irq
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
id|titan_update_irq_hw
c_func
(paren
id|cached_irq_mask
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
DECL|function|privateer_startup_irq
id|privateer_startup_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|privateer_enable_irq
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
DECL|function|privateer_end_irq
id|privateer_end_irq
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
id|privateer_enable_irq
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
id|cpu_irq_affinity
(braket
id|cpu
)braket
op_or_assign
l_int|1UL
op_lshift
id|irq
suffix:semicolon
r_else
id|cpu_irq_affinity
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
DECL|function|privateer_set_affinity
id|privateer_set_affinity
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
id|titan_irq_lock
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
id|titan_update_irq_hw
c_func
(paren
id|cached_irq_mask
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
DECL|variable|privateer_irq_type
r_static
r_struct
id|hw_interrupt_type
id|privateer_irq_type
op_assign
(brace
r_typename
suffix:colon
l_string|&quot;PRIVATEER&quot;
comma
id|startup
suffix:colon
id|privateer_startup_irq
comma
id|shutdown
suffix:colon
id|privateer_disable_irq
comma
id|enable
suffix:colon
id|privateer_enable_irq
comma
id|disable
suffix:colon
id|privateer_disable_irq
comma
id|ack
suffix:colon
id|privateer_disable_irq
comma
id|end
suffix:colon
id|privateer_end_irq
comma
id|set_affinity
suffix:colon
id|privateer_set_affinity
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|privateer_device_interrupt
id|privateer_device_interrupt
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
l_string|&quot;privateer_device_interrupt: NOT IMPLEMENTED YET!! &bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|privateer_srm_device_interrupt
id|privateer_srm_device_interrupt
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
r_static
r_void
id|__init
DECL|function|privateer_init_irq
id|privateer_init_irq
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
id|privateer_srm_device_interrupt
suffix:semicolon
id|titan_update_irq_hw
c_func
(paren
l_int|0UL
)paren
suffix:semicolon
id|init_i8259a_irqs
c_func
(paren
)paren
suffix:semicolon
id|init_titan_irqs
c_func
(paren
op_amp
id|privateer_irq_type
comma
l_int|16
comma
l_int|63
op_plus
l_int|16
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Privateer PCI Fixup configuration.&n; *&n; * PCHIP 0 BUS 0 (Hose 0)&n; *&n; *     IDSEL&t;Dev&t;What&n; *     -----&t;---&t;----&n; *&t;18&t; 7&t;Embedded Southbridge&n; *&t;19&t; 8&t;Slot 0 &n; *&t;20&t; 9&t;Slot 1&n; *&t;21&t;10&t;Slot 2 &n; *&t;22&t;11&t;Slot 3&n; *&t;23&t;12&t;Embedded HotPlug controller&n; *&t;27&t;16&t;Embedded Southbridge IDE&n; *&t;29&t;18     &t;Embedded Southbridge PMU&n; *&t;31&t;20&t;Embedded Southbridge USB&n; *&n; * PCHIP 1 BUS 0 (Hose 1)&n; *&n; *     IDSEL&t;Dev&t;What&n; *     -----&t;---&t;----&n; *&t;12&t; 1&t;Slot 0&n; * &t;13&t; 2&t;Slot 1&n; *&t;17&t; 6&t;Embedded hotPlug controller&n; *&n; * PCHIP 0 BUS 1 (Hose 2)&n; *&n; *     IDSEL&t;What&n; *     -----&t;----&n; *&t;NONE&t;AGP&n; *&n; * PCHIP 1 BUS 1 (Hose 3)&n; *&n; *     IDSEL&t;Dev&t;What&n; *     -----&t;---&t;----&n; *&t;12&t; 1&t;Slot 0&n; * &t;13&t; 2&t;Slot 1&n; *&t;17&t; 6&t;Embedded hotPlug controller&n; *&n; * Summary @ TITAN_CSR_DIM0:&n; * Bit      Meaning&n; *  0-7     Unused&n; *  8       PCHIP 0 BUS 1 YUKON (if present)&n; *  9       PCHIP 1 BUS 1 YUKON&n; * 10       PCHIP 1 BUS 0 YUKON&n; * 11       PCHIP 0 BUS 0 YUKON&n; * 12       PCHIP 0 BUS 0 SLOT 2 INT A&n; * 13       PCHIP 0 BUS 0 SLOT 2 INT B&n; * 14       PCHIP 0 BUS 0 SLOT 2 INT C&n; * 15       PCHIP 0 BUS 0 SLOT 2 INT D&n; * 16       PCHIP 0 BUS 0 SLOT 3 INT A&n; * 17       PCHIP 0 BUS 0 SLOT 3 INT B&n; * 18       PCHIP 0 BUS 0 SLOT 3 INT C&n; * 19       PCHIP 0 BUS 0 SLOT 3 INT D&n; * 20       PCHIP 0 BUS 0 SLOT 0 INT A&n; * 21       PCHIP 0 BUS 0 SLOT 0 INT B&n; * 22       PCHIP 0 BUS 0 SLOT 0 INT C&n; * 23       PCHIP 0 BUS 0 SLOT 0 INT D&n; * 24       PCHIP 0 BUS 0 SLOT 1 INT A&n; * 25       PCHIP 0 BUS 0 SLOT 1 INT B&n; * 26       PCHIP 0 BUS 0 SLOT 1 INT C&n; * 27       PCHIP 0 BUS 0 SLOT 1 INT D&n; * 28       PCHIP 1 BUS 0 SLOT 0 INT A&n; * 29       PCHIP 1 BUS 0 SLOT 0 INT B&n; * 30       PCHIP 1 BUS 0 SLOT 0 INT C&n; * 31       PCHIP 1 BUS 0 SLOT 0 INT D&n; * 32       PCHIP 1 BUS 0 SLOT 1 INT A&n; * 33       PCHIP 1 BUS 0 SLOT 1 INT B&n; * 34       PCHIP 1 BUS 0 SLOT 1 INT C&n; * 35       PCHIP 1 BUS 0 SLOT 1 INT D&n; * 36       PCHIP 1 BUS 1 SLOT 0 INT A&n; * 37       PCHIP 1 BUS 1 SLOT 0 INT B&n; * 38       PCHIP 1 BUS 1 SLOT 0 INT C&n; * 39       PCHIP 1 BUS 1 SLOT 0 INT D&n; * 40       PCHIP 1 BUS 1 SLOT 1 INT A&n; * 41       PCHIP 1 BUS 1 SLOT 1 INT B&n; * 42       PCHIP 1 BUS 1 SLOT 1 INT C&n; * 43       PCHIP 1 BUS 1 SLOT 1 INT D&n; * 44       AGP INT A&n; * 45       AGP INT B&n; * 46-47    Unused&n; * 49       Reserved for Sleep mode&n; * 50       Temperature Warning (optional)&n; * 51       Power Warning (optional)&n; * 52       Reserved&n; * 53       South Bridge NMI&n; * 54       South Bridge SMI INT&n; * 55       South Bridge ISA Interrupt&n; * 56-58    Unused&n; * 59       PCHIP1_C_ERROR&n; * 60       PCHIP0_C_ERROR &n; * 61       PCHIP1_H_ERROR&n; * 62       PCHIP0_H_ERROR&n; * 63       Reserved&n; *&n; */
r_static
r_int
id|__init
DECL|function|privateer_map_irq
id|privateer_map_irq
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
id|irq
suffix:semicolon
id|pcibios_read_config_byte
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|PCI_INTERRUPT_LINE
comma
op_amp
id|irq
)paren
suffix:semicolon
multiline_comment|/* is it routed through ISA? */
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
(paren
r_int
)paren
id|irq
suffix:semicolon
r_return
(paren
r_int
)paren
id|irq
op_plus
l_int|16
suffix:semicolon
multiline_comment|/* HACK -- this better only be called once */
)brace
macro_line|#ifdef CONFIG_VGA_HOSE
r_static
r_struct
id|pci_controller
op_star
id|__init
DECL|function|privateer_vga_hose_select
id|privateer_vga_hose_select
c_func
(paren
r_struct
id|pci_controller
op_star
id|h1
comma
r_struct
id|pci_controller
op_star
id|h2
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|h1
suffix:semicolon
r_int
id|agp1
comma
id|agp2
suffix:semicolon
multiline_comment|/* which hose(s) are agp? */
id|agp1
op_assign
(paren
l_int|0
op_ne
(paren
id|TITAN_agp
op_amp
(paren
l_int|1
op_lshift
id|h1-&gt;index
)paren
)paren
)paren
suffix:semicolon
id|agp2
op_assign
(paren
l_int|0
op_ne
(paren
id|TITAN_agp
op_amp
(paren
l_int|1
op_lshift
id|h2-&gt;index
)paren
)paren
)paren
suffix:semicolon
id|hose
op_assign
id|h1
suffix:semicolon
multiline_comment|/* default to h1 */
r_if
c_cond
(paren
id|agp1
op_xor
id|agp2
)paren
(brace
r_if
c_cond
(paren
id|agp2
)paren
id|hose
op_assign
id|h2
suffix:semicolon
multiline_comment|/* take agp if only one */
)brace
r_else
r_if
c_cond
(paren
id|h2-&gt;index
OL
id|h1-&gt;index
)paren
id|hose
op_assign
id|h2
suffix:semicolon
multiline_comment|/* first hose if 2xpci or 2xagp */
r_return
id|hose
suffix:semicolon
)brace
macro_line|#endif
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
id|privateer_vga_hose_select
)paren
suffix:semicolon
macro_line|#endif
)brace
r_void
DECL|function|privateer_machine_check
id|privateer_machine_check
c_func
(paren
r_int
r_int
id|vector
comma
r_int
r_int
id|la_ptr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/* only handle system events here */
r_if
c_cond
(paren
id|vector
op_ne
id|SCB_Q_SYSEVENT
)paren
r_return
id|titan_machine_check
c_func
(paren
id|vector
comma
id|la_ptr
comma
id|regs
)paren
suffix:semicolon
multiline_comment|/* it&squot;s a system event, handle it here */
id|printk
c_func
(paren
l_string|&quot;PRIVATEER 680 Machine Check on CPU %d&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The System Vectors&n; */
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|privateer_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;PRIVATEER&quot;
comma
id|DO_EV6_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_TITAN_IO
comma
id|DO_TITAN_BUS
comma
id|machine_check
suffix:colon
id|privateer_machine_check
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
id|TITAN_DAC_OFFSET
comma
id|nr_irqs
suffix:colon
l_int|80
comma
multiline_comment|/* 64 + 16 */
id|device_interrupt
suffix:colon
id|privateer_device_interrupt
comma
id|init_arch
suffix:colon
id|titan_init_arch
comma
id|init_irq
suffix:colon
id|privateer_init_irq
comma
id|init_rtc
suffix:colon
id|common_init_rtc
comma
id|init_pci
suffix:colon
id|privateer_init_pci
comma
id|kill_arch
suffix:colon
id|titan_kill_arch
comma
id|pci_map_irq
suffix:colon
id|privateer_map_irq
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
id|privateer
)paren
eof
