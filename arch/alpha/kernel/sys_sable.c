multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_sable.c&n; *&n; *&t;Copyright (C) 1995 David A Rusling&n; *&t;Copyright (C) 1996 Jay A Estabrook&n; *&t;Copyright (C) 1998, 1999 Richard Henderson&n; *&n; * Code supporting the Sable and Sable-Gamma systems.&n; */
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
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/core_t2.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq_impl.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
macro_line|#include &quot;machvec_impl.h&quot;
DECL|variable|sable_irq_lock
id|spinlock_t
id|sable_irq_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; *   For SABLE, which is really baroque, we manage 40 IRQ&squot;s, but the&n; *   hardware really only supports 24, not via normal ISA PIC,&n; *   but cascaded custom 8259&squot;s, etc.&n; *&t; 0-7  (char at 536)&n; *&t; 8-15 (char at 53a)&n; *&t;16-23 (char at 53c)&n; *&n; * Summary Registers (536/53a/53c):&n; *&n; * Bit      Meaning               Kernel IRQ&n; *------------------------------------------&n; * 0        PCI slot 0&t;&t;&t;34&n; * 1        NCR810 (builtin)&t;&t;33&n; * 2        TULIP (builtin)&t;&t;32&n; * 3        mouse&t;&t;&t;12&n; * 4        PCI slot 1&t;&t;&t;35&n; * 5        PCI slot 2&t;&t;&t;36&n; * 6        keyboard&t;&t;&t;1&n; * 7        floppy&t;&t;&t;6&n; * 8        COM2&t;&t;&t;3&n; * 9        parallel port&t;&t;7&n; *10        EISA irq 3&t;&t;&t;-&n; *11        EISA irq 4&t;&t;&t;-&n; *12        EISA irq 5&t;&t;&t;5&n; *13        EISA irq 6&t;&t;&t;-&n; *14        EISA irq 7&t;&t;&t;-&n; *15        COM1&t;&t;&t;4&n; *16        EISA irq 9&t;&t;&t;9&n; *17        EISA irq 10&t;&t;&t;10&n; *18        EISA irq 11&t;&t;&t;11&n; *19        EISA irq 12&t;&t;&t;-&n; *20        EISA irq 13&t;&t;&t;-&n; *21        EISA irq 14&t;&t;&t;14&n; *22        NC&t;&t;&t;&t;15&n; *23        IIC&t;&t;&t;&t;-&n; */
r_static
r_struct
(brace
DECL|member|irq_to_mask
r_char
id|irq_to_mask
(braket
l_int|40
)braket
suffix:semicolon
DECL|member|mask_to_irq
r_char
id|mask_to_irq
(braket
l_int|40
)braket
suffix:semicolon
multiline_comment|/* Note mask bit is true for DISABLED irqs.  */
DECL|member|shadow_mask
r_int
r_int
id|shadow_mask
suffix:semicolon
DECL|variable|sable_irq_swizzle
)brace
id|sable_irq_swizzle
op_assign
(brace
(brace
op_minus
l_int|1
comma
l_int|6
comma
op_minus
l_int|1
comma
l_int|8
comma
l_int|15
comma
l_int|12
comma
l_int|7
comma
l_int|9
comma
multiline_comment|/* pseudo PIC  0-7  */
op_minus
l_int|1
comma
l_int|16
comma
l_int|17
comma
l_int|18
comma
l_int|3
comma
op_minus
l_int|1
comma
l_int|21
comma
l_int|22
comma
multiline_comment|/* pseudo PIC  8-15 */
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
multiline_comment|/* pseudo EISA 0-7  */
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
multiline_comment|/* pseudo EISA 8-15 */
l_int|2
comma
l_int|1
comma
l_int|0
comma
l_int|4
comma
l_int|5
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
multiline_comment|/* pseudo PCI */
)brace
comma
(brace
l_int|34
comma
l_int|33
comma
l_int|32
comma
l_int|12
comma
l_int|35
comma
l_int|36
comma
l_int|1
comma
l_int|6
comma
multiline_comment|/* mask 0-7  */
l_int|3
comma
l_int|7
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|5
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|4
comma
multiline_comment|/* mask 8-15  */
l_int|9
comma
l_int|10
comma
l_int|11
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|14
comma
l_int|15
comma
op_minus
l_int|1
comma
multiline_comment|/* mask 16-23  */
)brace
comma
op_minus
l_int|1
)brace
suffix:semicolon
r_static
r_inline
r_void
DECL|function|sable_update_irq_hw
id|sable_update_irq_hw
c_func
(paren
r_int
r_int
id|bit
comma
r_int
r_int
id|mask
)paren
(brace
r_int
id|port
op_assign
l_int|0x537
suffix:semicolon
r_if
c_cond
(paren
id|bit
op_ge
l_int|16
)paren
(brace
id|port
op_assign
l_int|0x53d
suffix:semicolon
id|mask
op_rshift_assign
l_int|16
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|bit
op_ge
l_int|8
)paren
(brace
id|port
op_assign
l_int|0x53b
suffix:semicolon
id|mask
op_rshift_assign
l_int|8
suffix:semicolon
)brace
id|outb
c_func
(paren
id|mask
comma
id|port
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|sable_ack_irq_hw
id|sable_ack_irq_hw
c_func
(paren
r_int
r_int
id|bit
)paren
(brace
r_int
id|port
comma
id|val1
comma
id|val2
suffix:semicolon
r_if
c_cond
(paren
id|bit
op_ge
l_int|16
)paren
(brace
id|port
op_assign
l_int|0x53c
suffix:semicolon
id|val1
op_assign
l_int|0xE0
op_or
(paren
id|bit
op_minus
l_int|16
)paren
suffix:semicolon
id|val2
op_assign
l_int|0xE0
op_or
l_int|4
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|bit
op_ge
l_int|8
)paren
(brace
id|port
op_assign
l_int|0x53a
suffix:semicolon
id|val1
op_assign
l_int|0xE0
op_or
(paren
id|bit
op_minus
l_int|8
)paren
suffix:semicolon
id|val2
op_assign
l_int|0xE0
op_or
l_int|3
suffix:semicolon
)brace
r_else
(brace
id|port
op_assign
l_int|0x536
suffix:semicolon
id|val1
op_assign
l_int|0xE0
op_or
(paren
id|bit
op_minus
l_int|0
)paren
suffix:semicolon
id|val2
op_assign
l_int|0xE0
op_or
l_int|1
suffix:semicolon
)brace
id|outb
c_func
(paren
id|val1
comma
id|port
)paren
suffix:semicolon
multiline_comment|/* ack the slave */
id|outb
c_func
(paren
id|val2
comma
l_int|0x534
)paren
suffix:semicolon
multiline_comment|/* ack the master */
)brace
r_static
r_inline
r_void
DECL|function|sable_enable_irq
id|sable_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|bit
comma
id|mask
suffix:semicolon
id|bit
op_assign
id|sable_irq_swizzle.irq_to_mask
(braket
id|irq
)braket
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sable_irq_lock
)paren
suffix:semicolon
id|mask
op_assign
id|sable_irq_swizzle.shadow_mask
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
id|bit
)paren
suffix:semicolon
id|sable_update_irq_hw
c_func
(paren
id|bit
comma
id|mask
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sable_irq_lock
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|sable_disable_irq
id|sable_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|bit
comma
id|mask
suffix:semicolon
id|bit
op_assign
id|sable_irq_swizzle.irq_to_mask
(braket
id|irq
)braket
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sable_irq_lock
)paren
suffix:semicolon
id|mask
op_assign
id|sable_irq_swizzle.shadow_mask
op_or_assign
l_int|1UL
op_lshift
id|bit
suffix:semicolon
id|sable_update_irq_hw
c_func
(paren
id|bit
comma
id|mask
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sable_irq_lock
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|sable_startup_irq
id|sable_startup_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|sable_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|sable_end_irq
id|sable_end_irq
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
id|sable_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|sable_mask_and_ack_irq
id|sable_mask_and_ack_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|bit
comma
id|mask
suffix:semicolon
id|bit
op_assign
id|sable_irq_swizzle.irq_to_mask
(braket
id|irq
)braket
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sable_irq_lock
)paren
suffix:semicolon
id|mask
op_assign
id|sable_irq_swizzle.shadow_mask
op_or_assign
l_int|1UL
op_lshift
id|bit
suffix:semicolon
id|sable_update_irq_hw
c_func
(paren
id|bit
comma
id|mask
)paren
suffix:semicolon
id|sable_ack_irq_hw
c_func
(paren
id|bit
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sable_irq_lock
)paren
suffix:semicolon
)brace
DECL|variable|sable_irq_type
r_static
r_struct
id|hw_interrupt_type
id|sable_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;SABLE&quot;
comma
dot
id|startup
op_assign
id|sable_startup_irq
comma
dot
id|shutdown
op_assign
id|sable_disable_irq
comma
dot
id|enable
op_assign
id|sable_enable_irq
comma
dot
id|disable
op_assign
id|sable_disable_irq
comma
dot
id|ack
op_assign
id|sable_mask_and_ack_irq
comma
dot
id|end
op_assign
id|sable_end_irq
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|sable_srm_device_interrupt
id|sable_srm_device_interrupt
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
multiline_comment|/* Note that the vector reported by the SRM PALcode corresponds&n;&t;   to the interrupt mask bits, but we have to manage via more&n;&t;   normal IRQs.  */
r_int
id|bit
comma
id|irq
suffix:semicolon
id|bit
op_assign
(paren
id|vector
op_minus
l_int|0x800
)paren
op_rshift
l_int|4
suffix:semicolon
id|irq
op_assign
id|sable_irq_swizzle.mask_to_irq
(braket
id|bit
)braket
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
DECL|function|sable_init_irq
id|sable_init_irq
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
op_minus
l_int|1
comma
l_int|0x537
)paren
suffix:semicolon
multiline_comment|/* slave 0 */
id|outb
c_func
(paren
op_minus
l_int|1
comma
l_int|0x53b
)paren
suffix:semicolon
multiline_comment|/* slave 1 */
id|outb
c_func
(paren
op_minus
l_int|1
comma
l_int|0x53d
)paren
suffix:semicolon
multiline_comment|/* slave 2 */
id|outb
c_func
(paren
l_int|0x44
comma
l_int|0x535
)paren
suffix:semicolon
multiline_comment|/* enable cascades in master */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|40
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
id|sable_irq_type
suffix:semicolon
)brace
id|common_init_isa_dma
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * PCI Fixup configuration for ALPHA SABLE (2100) - 2100A is different ??&n; *&n; * The device to slot mapping looks like:&n; *&n; * Slot     Device&n; *  0       TULIP&n; *  1       SCSI&n; *  2       PCI-EISA bridge&n; *  3       none&n; *  4       none&n; *  5       none&n; *  6       PCI on board slot 0&n; *  7       PCI on board slot 1&n; *  8       PCI on board slot 2&n; *   &n; *&n; * This two layered interrupt approach means that we allocate IRQ 16 and &n; * above for PCI interrupts.  The IRQ relates to which bit the interrupt&n; * comes in on.  This makes interrupt processing much easier.&n; */
multiline_comment|/*&n; * NOTE: the IRQ assignments below are arbitrary, but need to be consistent&n; * with the values in the irq swizzling tables above.&n; */
r_static
r_int
id|__init
DECL|function|sable_map_irq
id|sable_map_irq
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
l_int|9
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*INT    INTA   INTB   INTC   INTD */
(brace
l_int|32
op_plus
l_int|0
comma
l_int|32
op_plus
l_int|0
comma
l_int|32
op_plus
l_int|0
comma
l_int|32
op_plus
l_int|0
comma
l_int|32
op_plus
l_int|0
)brace
comma
multiline_comment|/* IdSel 0,  TULIP  */
(brace
l_int|32
op_plus
l_int|1
comma
l_int|32
op_plus
l_int|1
comma
l_int|32
op_plus
l_int|1
comma
l_int|32
op_plus
l_int|1
comma
l_int|32
op_plus
l_int|1
)brace
comma
multiline_comment|/* IdSel 1,  SCSI   */
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
multiline_comment|/* IdSel 2,  SIO   */
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
multiline_comment|/* IdSel 3,  none   */
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
multiline_comment|/* IdSel 4,  none   */
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
multiline_comment|/* IdSel 5,  none   */
(brace
l_int|32
op_plus
l_int|2
comma
l_int|32
op_plus
l_int|2
comma
l_int|32
op_plus
l_int|2
comma
l_int|32
op_plus
l_int|2
comma
l_int|32
op_plus
l_int|2
)brace
comma
multiline_comment|/* IdSel 6,  slot 0 */
(brace
l_int|32
op_plus
l_int|3
comma
l_int|32
op_plus
l_int|3
comma
l_int|32
op_plus
l_int|3
comma
l_int|32
op_plus
l_int|3
comma
l_int|32
op_plus
l_int|3
)brace
comma
multiline_comment|/* IdSel 7,  slot 1 */
(brace
l_int|32
op_plus
l_int|4
comma
l_int|32
op_plus
l_int|4
comma
l_int|32
op_plus
l_int|4
comma
l_int|32
op_plus
l_int|4
comma
l_int|32
op_plus
l_int|4
)brace
comma
multiline_comment|/* IdSel 8,  slot 2 */
)brace
suffix:semicolon
r_int
id|min_idsel
op_assign
l_int|0
comma
id|max_idsel
op_assign
l_int|8
comma
id|irqs_per_slot
op_assign
l_int|5
suffix:semicolon
r_return
id|COMMON_TABLE_LOOKUP
suffix:semicolon
)brace
multiline_comment|/*&n; * The System Vectors&n; *&n; * In order that T2_HAE_ADDRESS should be a constant, we play&n; * these games with GAMMA_BIAS.&n; */
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || !defined(CONFIG_ALPHA_GAMMA)
DECL|macro|GAMMA_BIAS
macro_line|#undef GAMMA_BIAS
DECL|macro|GAMMA_BIAS
mdefine_line|#define GAMMA_BIAS 0
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|sable_mv
id|__initmv
op_assign
(brace
dot
id|vector_name
op_assign
l_string|&quot;Sable&quot;
comma
id|DO_EV4_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_T2_IO
comma
id|DO_T2_BUS
comma
dot
id|machine_check
op_assign
id|t2_machine_check
comma
dot
id|max_isa_dma_address
op_assign
id|ALPHA_SABLE_MAX_ISA_DMA_ADDRESS
comma
dot
id|min_io_address
op_assign
id|EISA_DEFAULT_IO_BASE
comma
dot
id|min_mem_address
op_assign
id|T2_DEFAULT_MEM_BASE
comma
dot
id|nr_irqs
op_assign
l_int|40
comma
dot
id|device_interrupt
op_assign
id|sable_srm_device_interrupt
comma
dot
id|init_arch
op_assign
id|t2_init_arch
comma
dot
id|init_irq
op_assign
id|sable_init_irq
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
id|sable_map_irq
comma
dot
id|pci_swizzle
op_assign
id|common_swizzle
comma
dot
id|sys
op_assign
(brace
dot
id|t2
op_assign
(brace
dot
id|gamma_bias
op_assign
l_int|0
)brace
)brace
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|sable
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_GAMMA)
DECL|macro|GAMMA_BIAS
macro_line|#undef GAMMA_BIAS
DECL|macro|GAMMA_BIAS
mdefine_line|#define GAMMA_BIAS _GAMMA_BIAS
r_struct
id|alpha_machine_vector
id|sable_gamma_mv
id|__initmv
op_assign
(brace
dot
id|vector_name
op_assign
l_string|&quot;Sable-Gamma&quot;
comma
id|DO_EV5_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_T2_IO
comma
id|DO_T2_BUS
comma
dot
id|machine_check
op_assign
id|t2_machine_check
comma
dot
id|max_isa_dma_address
op_assign
id|ALPHA_SABLE_MAX_ISA_DMA_ADDRESS
comma
dot
id|min_io_address
op_assign
id|EISA_DEFAULT_IO_BASE
comma
dot
id|min_mem_address
op_assign
id|T2_DEFAULT_MEM_BASE
comma
dot
id|nr_irqs
op_assign
l_int|40
comma
dot
id|device_interrupt
op_assign
id|sable_srm_device_interrupt
comma
dot
id|init_arch
op_assign
id|t2_init_arch
comma
dot
id|init_irq
op_assign
id|sable_init_irq
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
id|sable_map_irq
comma
dot
id|pci_swizzle
op_assign
id|common_swizzle
comma
dot
id|sys
op_assign
(brace
dot
id|t2
op_assign
(brace
dot
id|gamma_bias
op_assign
id|_GAMMA_BIAS
)brace
)brace
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|sable_gamma
)paren
macro_line|#endif
eof
