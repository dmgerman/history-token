multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_eiger.c&n; *&n; *&t;Copyright (C) 1995 David A Rusling&n; *&t;Copyright (C) 1996, 1999 Jay A Estabrook&n; *&t;Copyright (C) 1998, 1999 Richard Henderson&n; *&t;Copyright (C) 1999 Iain Grant&n; *&n; * Code supporting the EIGER (EV6+TSUNAMI).&n; */
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
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/core_tsunami.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq_impl.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
macro_line|#include &quot;machvec_impl.h&quot;
multiline_comment|/* Note that this interrupt code is identical to TAKARA.  */
multiline_comment|/* Note mask bit is true for DISABLED irqs.  */
DECL|variable|cached_irq_mask
r_static
r_int
r_int
id|cached_irq_mask
(braket
l_int|2
)braket
op_assign
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
suffix:semicolon
r_static
r_inline
r_void
DECL|function|eiger_update_irq_hw
id|eiger_update_irq_hw
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
r_int
id|regaddr
suffix:semicolon
id|mask
op_assign
(paren
id|irq
op_ge
l_int|64
ques
c_cond
id|mask
op_lshift
l_int|16
suffix:colon
id|mask
op_rshift
(paren
(paren
id|irq
op_minus
l_int|16
)paren
op_amp
l_int|0x30
)paren
)paren
suffix:semicolon
id|regaddr
op_assign
l_int|0x510
op_plus
(paren
(paren
(paren
id|irq
op_minus
l_int|16
)paren
op_rshift
l_int|2
)paren
op_amp
l_int|0x0c
)paren
suffix:semicolon
id|outl
c_func
(paren
id|mask
op_amp
l_int|0xffff0000UL
comma
id|regaddr
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|eiger_enable_irq
id|eiger_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
id|mask
op_assign
(paren
id|cached_irq_mask
(braket
id|irq
op_ge
l_int|64
)braket
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
(paren
id|irq
op_amp
l_int|63
)paren
)paren
)paren
suffix:semicolon
id|eiger_update_irq_hw
c_func
(paren
id|irq
comma
id|mask
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|eiger_disable_irq
id|eiger_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
id|mask
op_assign
(paren
id|cached_irq_mask
(braket
id|irq
op_ge
l_int|64
)braket
op_or_assign
l_int|1UL
op_lshift
(paren
id|irq
op_amp
l_int|63
)paren
)paren
suffix:semicolon
id|eiger_update_irq_hw
c_func
(paren
id|irq
comma
id|mask
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|eiger_startup_irq
id|eiger_startup_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|eiger_enable_irq
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
DECL|function|eiger_end_irq
id|eiger_end_irq
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
id|eiger_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|eiger_irq_type
r_static
r_struct
id|hw_interrupt_type
id|eiger_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;EIGER&quot;
comma
dot
id|startup
op_assign
id|eiger_startup_irq
comma
dot
id|shutdown
op_assign
id|eiger_disable_irq
comma
dot
id|enable
op_assign
id|eiger_enable_irq
comma
dot
id|disable
op_assign
id|eiger_disable_irq
comma
dot
id|ack
op_assign
id|eiger_disable_irq
comma
dot
id|end
op_assign
id|eiger_end_irq
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|eiger_device_interrupt
id|eiger_device_interrupt
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
id|intstatus
suffix:semicolon
multiline_comment|/*&n;&t; * The PALcode will have passed us vectors 0x800 or 0x810,&n;&t; * which are fairly arbitrary values and serve only to tell&n;&t; * us whether an interrupt has come in on IRQ0 or IRQ1. If&n;&t; * it&squot;s IRQ1 it&squot;s a PCI interrupt; if it&squot;s IRQ0, it&squot;s&n;&t; * probably ISA, but PCI interrupts can come through IRQ0&n;&t; * as well if the interrupt controller isn&squot;t in accelerated&n;&t; * mode.&n;&t; *&n;&t; * OTOH, the accelerator thing doesn&squot;t seem to be working&n;&t; * overly well, so what we&squot;ll do instead is try directly&n;&t; * examining the Master Interrupt Register to see if it&squot;s a&n;&t; * PCI interrupt, and if _not_ then we&squot;ll pass it on to the&n;&t; * ISA handler.&n;&t; */
id|intstatus
op_assign
id|inw
c_func
(paren
l_int|0x500
)paren
op_amp
l_int|15
suffix:semicolon
r_if
c_cond
(paren
id|intstatus
)paren
(brace
multiline_comment|/*&n;&t;&t; * This is a PCI interrupt. Check each bit and&n;&t;&t; * despatch an interrupt if it&squot;s set.&n;&t;&t; */
r_if
c_cond
(paren
id|intstatus
op_amp
l_int|8
)paren
id|handle_irq
c_func
(paren
l_int|16
op_plus
l_int|3
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intstatus
op_amp
l_int|4
)paren
id|handle_irq
c_func
(paren
l_int|16
op_plus
l_int|2
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intstatus
op_amp
l_int|2
)paren
id|handle_irq
c_func
(paren
l_int|16
op_plus
l_int|1
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intstatus
op_amp
l_int|1
)paren
id|handle_irq
c_func
(paren
l_int|16
op_plus
l_int|0
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
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
)brace
r_static
r_void
DECL|function|eiger_srm_device_interrupt
id|eiger_srm_device_interrupt
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
DECL|function|eiger_init_irq
id|eiger_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
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
id|eiger_srm_device_interrupt
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
l_int|128
suffix:semicolon
id|i
op_add_assign
l_int|16
)paren
id|eiger_update_irq_hw
c_func
(paren
id|i
comma
op_minus
l_int|1
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
l_int|128
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
id|eiger_irq_type
suffix:semicolon
)brace
)brace
r_static
r_int
id|__init
DECL|function|eiger_map_irq
id|eiger_map_irq
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
id|irq_orig
suffix:semicolon
multiline_comment|/* The SRM console has already calculated out the IRQ value&squot;s for&n;&t;   option cards. As this works lets just read in the value already&n;&t;   set and change it to a useable value by Linux.&n;&n;&t;   All the IRQ values generated by the console are greater than 90,&n;&t;   so we subtract 80 because it is (90 - allocated ISA IRQ&squot;s).  */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
op_amp
id|irq_orig
)paren
suffix:semicolon
r_return
id|irq_orig
op_minus
l_int|0x80
suffix:semicolon
)brace
r_static
id|u8
id|__init
DECL|function|eiger_swizzle
id|eiger_swizzle
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
r_int
id|bridge_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Find the number of backplane bridges.  */
r_int
id|backplane
op_assign
id|inw
c_func
(paren
l_int|0x502
)paren
op_amp
l_int|0x0f
suffix:semicolon
r_switch
c_cond
(paren
id|backplane
)paren
(brace
r_case
l_int|0x00
suffix:colon
id|bridge_count
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* No bridges */
r_case
l_int|0x01
suffix:colon
id|bridge_count
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* 1 */
r_case
l_int|0x03
suffix:colon
id|bridge_count
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* 2 */
r_case
l_int|0x07
suffix:colon
id|bridge_count
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* 3 */
r_case
l_int|0x0f
suffix:colon
id|bridge_count
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* 4 */
)brace
suffix:semicolon
id|slot
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
r_while
c_loop
(paren
id|dev-&gt;bus-&gt;self
)paren
(brace
multiline_comment|/* Check for built-in bridges on hose 0. */
r_if
c_cond
(paren
id|hose-&gt;index
op_eq
l_int|0
op_logical_and
(paren
id|PCI_SLOT
c_func
(paren
id|dev-&gt;bus-&gt;self-&gt;devfn
)paren
OG
l_int|20
op_minus
id|bridge_count
)paren
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
multiline_comment|/* Must be a card-based bridge.  */
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
multiline_comment|/*&n; * The System Vectors&n; */
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|eiger_mv
id|__initmv
op_assign
(brace
dot
id|vector_name
op_assign
l_string|&quot;Eiger&quot;
comma
id|DO_EV6_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_TSUNAMI_IO
comma
id|DO_TSUNAMI_BUS
comma
dot
id|machine_check
op_assign
id|tsunami_machine_check
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
id|TSUNAMI_DAC_OFFSET
comma
dot
id|nr_irqs
op_assign
l_int|128
comma
dot
id|device_interrupt
op_assign
id|eiger_device_interrupt
comma
dot
id|init_arch
op_assign
id|tsunami_init_arch
comma
dot
id|init_irq
op_assign
id|eiger_init_irq
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
id|tsunami_kill_arch
comma
dot
id|pci_map_irq
op_assign
id|eiger_map_irq
comma
dot
id|pci_swizzle
op_assign
id|eiger_swizzle
comma
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|eiger
)paren
eof
