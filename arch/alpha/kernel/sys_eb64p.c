multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_eb64p.c&n; *&n; *&t;Copyright (C) 1995 David A Rusling&n; *&t;Copyright (C) 1996 Jay A Estabrook&n; *&t;Copyright (C) 1998, 1999 Richard Henderson&n; *&n; * Code supporting the EB64+ and EB66.&n; */
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
macro_line|#include &lt;asm/core_apecs.h&gt;
macro_line|#include &lt;asm/core_lca.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq_impl.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
macro_line|#include &quot;machvec_impl.h&quot;
multiline_comment|/* Note mask bit is true for DISABLED irqs.  */
DECL|variable|cached_irq_mask
r_static
r_int
r_int
id|cached_irq_mask
op_assign
op_minus
l_int|1
suffix:semicolon
r_static
r_inline
r_void
DECL|function|eb64p_update_irq_hw
id|eb64p_update_irq_hw
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|mask
)paren
(brace
id|outb
c_func
(paren
id|mask
op_rshift
(paren
id|irq
op_ge
l_int|24
ques
c_cond
l_int|24
suffix:colon
l_int|16
)paren
comma
(paren
id|irq
op_ge
l_int|24
ques
c_cond
l_int|0x27
suffix:colon
l_int|0x26
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|eb64p_enable_irq
id|eb64p_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|eb64p_update_irq_hw
c_func
(paren
id|irq
comma
id|cached_irq_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|eb64p_disable_irq
id|eb64p_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|eb64p_update_irq_hw
c_func
(paren
id|irq
comma
id|cached_irq_mask
op_or_assign
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|eb64p_startup_irq
id|eb64p_startup_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|eb64p_enable_irq
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
DECL|function|eb64p_end_irq
id|eb64p_end_irq
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
id|eb64p_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|eb64p_irq_type
r_static
r_struct
id|hw_interrupt_type
id|eb64p_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;EB64P&quot;
comma
dot
id|startup
op_assign
id|eb64p_startup_irq
comma
dot
id|shutdown
op_assign
id|eb64p_disable_irq
comma
dot
id|enable
op_assign
id|eb64p_enable_irq
comma
dot
id|disable
op_assign
id|eb64p_disable_irq
comma
dot
id|ack
op_assign
id|eb64p_disable_irq
comma
dot
id|end
op_assign
id|eb64p_end_irq
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|eb64p_device_interrupt
id|eb64p_device_interrupt
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
r_int
id|pld
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/* Read the interrupt summary registers */
id|pld
op_assign
id|inb
c_func
(paren
l_int|0x26
)paren
op_or
(paren
id|inb
c_func
(paren
l_int|0x27
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now, for every possible bit set, work through&n;&t; * them and call the appropriate interrupt handler.&n;&t; */
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
l_int|5
)paren
(brace
id|isa_device_interrupt
c_func
(paren
id|vector
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
(brace
id|handle_irq
c_func
(paren
l_int|16
op_plus
id|i
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
)brace
r_static
r_void
id|__init
DECL|function|eb64p_init_irq
id|eb64p_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_CABRIOLET)
multiline_comment|/*&n;&t; * CABRIO SRM may not set variation correctly, so here we test&n;&t; * the high word of the interrupt summary register for the RAZ&n;&t; * bits, and hope that a true EB64+ would read all ones...&n;&t; */
r_if
c_cond
(paren
id|inw
c_func
(paren
l_int|0x806
)paren
op_ne
l_int|0xffff
)paren
(brace
r_extern
r_struct
id|alpha_machine_vector
id|cabriolet_mv
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Detected Cabriolet: correcting HWRPB.&bslash;n&quot;
)paren
suffix:semicolon
id|hwrpb-&gt;sys_variation
op_or_assign
l_int|2L
op_lshift
l_int|10
suffix:semicolon
id|hwrpb_update_checksum
c_func
(paren
id|hwrpb
)paren
suffix:semicolon
id|alpha_mv
op_assign
id|cabriolet_mv
suffix:semicolon
id|alpha_mv
dot
id|init_irq
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif /* GENERIC */
id|outb
c_func
(paren
l_int|0xff
comma
l_int|0x26
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xff
comma
l_int|0x27
)paren
suffix:semicolon
id|init_i8259a_irqs
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|16
suffix:semicolon
id|i
OL
l_int|32
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
op_amp
id|eb64p_irq_type
suffix:semicolon
)brace
id|common_init_isa_dma
c_func
(paren
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
l_int|16
op_plus
l_int|5
comma
op_amp
id|isa_cascade_irqaction
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * PCI Fixup configuration.&n; *&n; * There are two 8 bit external summary registers as follows:&n; *&n; * Summary @ 0x26:&n; * Bit      Meaning&n; * 0        Interrupt Line A from slot 0&n; * 1        Interrupt Line A from slot 1&n; * 2        Interrupt Line B from slot 0&n; * 3        Interrupt Line B from slot 1&n; * 4        Interrupt Line C from slot 0&n; * 5        Interrupt line from the two ISA PICs&n; * 6        Tulip&n; * 7        NCR SCSI&n; *&n; * Summary @ 0x27&n; * Bit      Meaning&n; * 0        Interrupt Line C from slot 1&n; * 1        Interrupt Line D from slot 0&n; * 2        Interrupt Line D from slot 1&n; * 3        RAZ&n; * 4        RAZ&n; * 5        RAZ&n; * 6        RAZ&n; * 7        RAZ&n; *&n; * The device to slot mapping looks like:&n; *&n; * Slot     Device&n; *  5       NCR SCSI controller&n; *  6       PCI on board slot 0&n; *  7       PCI on board slot 1&n; *  8       Intel SIO PCI-ISA bridge chip&n; *  9       Tulip - DECchip 21040 Ethernet controller&n; *   &n; *&n; * This two layered interrupt approach means that we allocate IRQ 16 and &n; * above for PCI interrupts.  The IRQ relates to which bit the interrupt&n; * comes in on.  This makes interrupt processing much easier.&n; */
r_static
r_int
id|__init
DECL|function|eb64p_map_irq
id|eb64p_map_irq
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
l_int|5
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*INT  INTA  INTB  INTC   INTD */
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
l_int|7
comma
l_int|16
op_plus
l_int|7
comma
l_int|16
op_plus
l_int|7
)brace
comma
multiline_comment|/* IdSel 5,  slot ?, ?? */
(brace
l_int|16
op_plus
l_int|0
comma
l_int|16
op_plus
l_int|0
comma
l_int|16
op_plus
l_int|2
comma
l_int|16
op_plus
l_int|4
comma
l_int|16
op_plus
l_int|9
)brace
comma
multiline_comment|/* IdSel 6,  slot ?, ?? */
(brace
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|3
comma
l_int|16
op_plus
l_int|8
comma
l_int|16
op_plus
l_int|10
)brace
comma
multiline_comment|/* IdSel 7,  slot ?, ?? */
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
multiline_comment|/* IdSel 8,  SIO */
(brace
l_int|16
op_plus
l_int|6
comma
l_int|16
op_plus
l_int|6
comma
l_int|16
op_plus
l_int|6
comma
l_int|16
op_plus
l_int|6
comma
l_int|16
op_plus
l_int|6
)brace
comma
multiline_comment|/* IdSel 9,  TULIP */
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
l_int|9
comma
id|irqs_per_slot
op_assign
l_int|5
suffix:semicolon
r_return
id|COMMON_TABLE_LOOKUP
suffix:semicolon
)brace
multiline_comment|/*&n; * The System Vector&n; */
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_EB64P)
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|eb64p_mv
id|__initmv
op_assign
(brace
dot
id|vector_name
op_assign
l_string|&quot;EB64+&quot;
comma
id|DO_EV4_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_APECS_IO
comma
dot
id|machine_check
op_assign
id|apecs_machine_check
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
id|APECS_AND_LCA_DEFAULT_MEM_BASE
comma
dot
id|nr_irqs
op_assign
l_int|32
comma
dot
id|device_interrupt
op_assign
id|eb64p_device_interrupt
comma
dot
id|init_arch
op_assign
id|apecs_init_arch
comma
dot
id|init_irq
op_assign
id|eb64p_init_irq
comma
dot
id|init_rtc
op_assign
id|common_init_rtc
comma
dot
id|init_pci
op_assign
id|common_init_pci
comma
dot
id|kill_arch
op_assign
l_int|NULL
comma
dot
id|pci_map_irq
op_assign
id|eb64p_map_irq
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
id|eb64p
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_EB66)
r_struct
id|alpha_machine_vector
id|eb66_mv
id|__initmv
op_assign
(brace
dot
id|vector_name
op_assign
l_string|&quot;EB66&quot;
comma
id|DO_EV4_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_LCA_IO
comma
dot
id|machine_check
op_assign
id|lca_machine_check
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
id|APECS_AND_LCA_DEFAULT_MEM_BASE
comma
dot
id|nr_irqs
op_assign
l_int|32
comma
dot
id|device_interrupt
op_assign
id|eb64p_device_interrupt
comma
dot
id|init_arch
op_assign
id|lca_init_arch
comma
dot
id|init_irq
op_assign
id|eb64p_init_irq
comma
dot
id|init_rtc
op_assign
id|common_init_rtc
comma
dot
id|init_pci
op_assign
id|common_init_pci
comma
dot
id|pci_map_irq
op_assign
id|eb64p_map_irq
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
id|eb66
)paren
macro_line|#endif
eof
