multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_noritake.c&n; *&n; *&t;Copyright (C) 1995 David A Rusling&n; *&t;Copyright (C) 1996 Jay A Estabrook&n; *&t;Copyright (C) 1998, 1999 Richard Henderson&n; *&n; * Code supporting the NORITAKE (AlphaServer 1000A), &n; * CORELLE (AlphaServer 800), and ALCOR Primo (AlphaStation 600A).&n; */
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
macro_line|#include &lt;asm/core_apecs.h&gt;
macro_line|#include &lt;asm/core_cia.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq_impl.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
macro_line|#include &quot;machvec_impl.h&quot;
multiline_comment|/* Note mask bit is true for ENABLED irqs.  */
DECL|variable|cached_irq_mask
r_static
r_int
id|cached_irq_mask
suffix:semicolon
r_static
r_inline
r_void
DECL|function|noritake_update_irq_hw
id|noritake_update_irq_hw
c_func
(paren
r_int
id|irq
comma
r_int
id|mask
)paren
(brace
r_int
id|port
op_assign
l_int|0x54a
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
l_int|32
)paren
(brace
id|mask
op_rshift_assign
l_int|16
suffix:semicolon
id|port
op_assign
l_int|0x54c
suffix:semicolon
)brace
id|outw
c_func
(paren
id|mask
comma
id|port
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|noritake_enable_irq
id|noritake_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|noritake_update_irq_hw
c_func
(paren
id|irq
comma
id|cached_irq_mask
op_or_assign
l_int|1
op_lshift
(paren
id|irq
op_minus
l_int|16
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|noritake_disable_irq
id|noritake_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|noritake_update_irq_hw
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
(paren
id|irq
op_minus
l_int|16
)paren
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|noritake_startup_irq
id|noritake_startup_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|noritake_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|noritake_irq_type
r_static
r_struct
id|hw_interrupt_type
id|noritake_irq_type
op_assign
(brace
r_typename
suffix:colon
l_string|&quot;NORITAKE&quot;
comma
id|startup
suffix:colon
id|noritake_startup_irq
comma
id|shutdown
suffix:colon
id|noritake_disable_irq
comma
id|enable
suffix:colon
id|noritake_enable_irq
comma
id|disable
suffix:colon
id|noritake_disable_irq
comma
id|ack
suffix:colon
id|noritake_disable_irq
comma
id|end
suffix:colon
id|noritake_enable_irq
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|noritake_device_interrupt
id|noritake_device_interrupt
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
multiline_comment|/* Read the interrupt summary registers of NORITAKE */
id|pld
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|inw
c_func
(paren
l_int|0x54c
)paren
op_lshift
l_int|32
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|inw
c_func
(paren
l_int|0x54a
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|inb
c_func
(paren
l_int|0xa0
)paren
op_lshift
l_int|8
)paren
op_or
id|inb
c_func
(paren
l_int|0x20
)paren
)paren
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
OL
l_int|16
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
DECL|function|noritake_srm_device_interrupt
id|noritake_srm_device_interrupt
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
multiline_comment|/*&n;&t; * I really hate to do this, too, but the NORITAKE SRM console also&n;&t; * reports PCI vectors *lower* than I expected from the bit numbers&n;&t; * in the documentation.&n;&t; * But I really don&squot;t want to change the fixup code for allocation&n;&t; * of IRQs, nor the alpha_irq_mask maintenance stuff, both of which&n;&t; * look nice and clean now.&n;&t; * So, here&squot;s this additional grotty hack... :-(&n;&t; */
r_if
c_cond
(paren
id|irq
op_ge
l_int|16
)paren
id|irq
op_assign
id|irq
op_plus
l_int|1
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
DECL|function|noritake_init_irq
id|noritake_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|alpha_using_srm
)paren
id|alpha_mv.device_interrupt
op_assign
id|noritake_srm_device_interrupt
suffix:semicolon
id|outw
c_func
(paren
l_int|0
comma
l_int|0x54a
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|0
comma
l_int|0x54c
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
l_int|48
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
id|noritake_irq_type
suffix:semicolon
)brace
id|init_i8259a_irqs
c_func
(paren
)paren
suffix:semicolon
id|common_init_isa_dma
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * PCI Fixup configuration.&n; *&n; * Summary @ 0x542, summary register #1:&n; * Bit      Meaning&n; * 0        All valid ints from summary regs 2 &amp; 3&n; * 1        QLOGIC ISP1020A SCSI&n; * 2        Interrupt Line A from slot 0&n; * 3        Interrupt Line B from slot 0&n; * 4        Interrupt Line A from slot 1&n; * 5        Interrupt line B from slot 1&n; * 6        Interrupt Line A from slot 2&n; * 7        Interrupt Line B from slot 2&n; * 8        Interrupt Line A from slot 3&n; * 9        Interrupt Line B from slot 3&n; *10        Interrupt Line A from slot 4&n; *11        Interrupt Line B from slot 4&n; *12        Interrupt Line A from slot 5&n; *13        Interrupt Line B from slot 5&n; *14        Interrupt Line A from slot 6&n; *15        Interrupt Line B from slot 6&n; *&n; * Summary @ 0x544, summary register #2:&n; * Bit      Meaning&n; * 0        OR of all unmasked ints in SR #2&n; * 1        OR of secondary bus ints&n; * 2        Interrupt Line C from slot 0&n; * 3        Interrupt Line D from slot 0&n; * 4        Interrupt Line C from slot 1&n; * 5        Interrupt line D from slot 1&n; * 6        Interrupt Line C from slot 2&n; * 7        Interrupt Line D from slot 2&n; * 8        Interrupt Line C from slot 3&n; * 9        Interrupt Line D from slot 3&n; *10        Interrupt Line C from slot 4&n; *11        Interrupt Line D from slot 4&n; *12        Interrupt Line C from slot 5&n; *13        Interrupt Line D from slot 5&n; *14        Interrupt Line C from slot 6&n; *15        Interrupt Line D from slot 6&n; *&n; * The device to slot mapping looks like:&n; *&n; * Slot     Device&n; *  7       Intel PCI-EISA bridge chip&n; *  8       DEC PCI-PCI bridge chip&n; * 11       PCI on board slot 0&n; * 12       PCI on board slot 1&n; * 13       PCI on board slot 2&n; *   &n; *&n; * This two layered interrupt approach means that we allocate IRQ 16 and &n; * above for PCI interrupts.  The IRQ relates to which bit the interrupt&n; * comes in on.  This makes interrupt processing much easier.&n; */
r_static
r_int
id|__init
DECL|function|noritake_map_irq
id|noritake_map_irq
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
l_int|15
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*INT    INTA   INTB   INTC   INTD */
multiline_comment|/* note: IDSELs 16, 17, and 25 are CORELLE only */
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
l_int|1
comma
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|1
)brace
comma
multiline_comment|/* IdSel 16,  QLOGIC */
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
multiline_comment|/* IdSel 17, S3 Trio64 */
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
multiline_comment|/* IdSel 18,  PCEB */
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
multiline_comment|/* IdSel 19,  PPB  */
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
multiline_comment|/* IdSel 20,  ???? */
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
multiline_comment|/* IdSel 21,  ???? */
(brace
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
l_int|3
comma
l_int|32
op_plus
l_int|2
comma
l_int|32
op_plus
l_int|3
)brace
comma
multiline_comment|/* IdSel 22,  slot 0 */
(brace
l_int|16
op_plus
l_int|4
comma
l_int|16
op_plus
l_int|4
comma
l_int|16
op_plus
l_int|5
comma
l_int|32
op_plus
l_int|4
comma
l_int|32
op_plus
l_int|5
)brace
comma
multiline_comment|/* IdSel 23,  slot 1 */
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
l_int|7
comma
l_int|32
op_plus
l_int|6
comma
l_int|32
op_plus
l_int|7
)brace
comma
multiline_comment|/* IdSel 24,  slot 2 */
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
l_int|32
op_plus
l_int|8
comma
l_int|32
op_plus
l_int|9
)brace
comma
multiline_comment|/* IdSel 25,  slot 3 */
multiline_comment|/* The following 5 are actually on PCI bus 1, which is &n;&t;&t;   across the built-in bridge of the NORITAKE only.  */
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
l_int|1
comma
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|1
)brace
comma
multiline_comment|/* IdSel 16,  QLOGIC */
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
l_int|32
op_plus
l_int|8
comma
l_int|32
op_plus
l_int|9
)brace
comma
multiline_comment|/* IdSel 17,  slot 3 */
(brace
l_int|16
op_plus
l_int|10
comma
l_int|16
op_plus
l_int|10
comma
l_int|16
op_plus
l_int|11
comma
l_int|32
op_plus
l_int|10
comma
l_int|32
op_plus
l_int|11
)brace
comma
multiline_comment|/* IdSel 18,  slot 4 */
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
l_int|32
op_plus
l_int|12
comma
l_int|32
op_plus
l_int|13
)brace
comma
multiline_comment|/* IdSel 19,  slot 5 */
(brace
l_int|16
op_plus
l_int|14
comma
l_int|16
op_plus
l_int|14
comma
l_int|16
op_plus
l_int|15
comma
l_int|32
op_plus
l_int|14
comma
l_int|32
op_plus
l_int|15
)brace
comma
multiline_comment|/* IdSel 20,  slot 6 */
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
l_int|19
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
DECL|function|noritake_swizzle
id|noritake_swizzle
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
id|dev-&gt;bus-&gt;number
op_eq
l_int|0
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
multiline_comment|/* Check for the built-in bridge */
r_else
r_if
c_cond
(paren
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
op_plus
l_int|15
suffix:semicolon
multiline_comment|/* WAG! */
)brace
r_else
(brace
multiline_comment|/* Must be a card-based bridge.  */
r_do
(brace
r_if
c_cond
(paren
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
op_plus
l_int|15
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
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || !defined(CONFIG_ALPHA_PRIMO)
r_static
r_void
DECL|function|noritake_apecs_machine_check
id|noritake_apecs_machine_check
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
DECL|macro|MCHK_NO_DEVSEL
mdefine_line|#define MCHK_NO_DEVSEL 0x205U
DECL|macro|MCHK_NO_TABT
mdefine_line|#define MCHK_NO_TABT 0x204U
r_struct
id|el_common
op_star
id|mchk_header
suffix:semicolon
r_int
r_int
id|code
suffix:semicolon
id|mchk_header
op_assign
(paren
r_struct
id|el_common
op_star
)paren
id|la_ptr
suffix:semicolon
multiline_comment|/* Clear the error before any reporting.  */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* magic */
id|draina
c_func
(paren
)paren
suffix:semicolon
id|apecs_pci_clr_err
c_func
(paren
)paren
suffix:semicolon
id|wrmces
c_func
(paren
l_int|0x7
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|code
op_assign
id|mchk_header-&gt;code
suffix:semicolon
id|process_mcheck_info
c_func
(paren
id|vector
comma
id|la_ptr
comma
id|regs
comma
l_string|&quot;NORITAKE APECS&quot;
comma
(paren
id|mcheck_expected
c_func
(paren
l_int|0
)paren
op_logical_and
(paren
id|code
op_eq
id|MCHK_NO_DEVSEL
op_logical_or
id|code
op_eq
id|MCHK_NO_TABT
)paren
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * The System Vectors&n; */
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || !defined(CONFIG_ALPHA_PRIMO)
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|noritake_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;Noritake&quot;
comma
id|DO_EV4_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_APECS_IO
comma
id|DO_APECS_BUS
comma
id|machine_check
suffix:colon
id|noritake_apecs_machine_check
comma
id|max_isa_dma_address
suffix:colon
id|ALPHA_MAX_ISA_DMA_ADDRESS
comma
id|min_io_address
suffix:colon
id|EISA_DEFAULT_IO_BASE
comma
id|min_mem_address
suffix:colon
id|APECS_AND_LCA_DEFAULT_MEM_BASE
comma
id|nr_irqs
suffix:colon
l_int|48
comma
id|device_interrupt
suffix:colon
id|noritake_device_interrupt
comma
id|init_arch
suffix:colon
id|apecs_init_arch
comma
id|init_irq
suffix:colon
id|noritake_init_irq
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
l_int|NULL
comma
id|pci_map_irq
suffix:colon
id|noritake_map_irq
comma
id|pci_swizzle
suffix:colon
id|noritake_swizzle
comma
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|noritake
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_PRIMO)
r_struct
id|alpha_machine_vector
id|noritake_primo_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;Noritake-Primo&quot;
comma
id|DO_EV5_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_CIA_IO
comma
id|DO_CIA_BUS
comma
id|machine_check
suffix:colon
id|cia_machine_check
comma
id|max_isa_dma_address
suffix:colon
id|ALPHA_MAX_ISA_DMA_ADDRESS
comma
id|min_io_address
suffix:colon
id|EISA_DEFAULT_IO_BASE
comma
id|min_mem_address
suffix:colon
id|CIA_DEFAULT_MEM_BASE
comma
id|nr_irqs
suffix:colon
l_int|48
comma
id|device_interrupt
suffix:colon
id|noritake_device_interrupt
comma
id|init_arch
suffix:colon
id|cia_init_arch
comma
id|init_irq
suffix:colon
id|noritake_init_irq
comma
id|init_rtc
suffix:colon
id|common_init_rtc
comma
id|init_pci
suffix:colon
id|cia_init_pci
comma
id|pci_map_irq
suffix:colon
id|noritake_map_irq
comma
id|pci_swizzle
suffix:colon
id|noritake_swizzle
comma
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|noritake_primo
)paren
macro_line|#endif
eof
