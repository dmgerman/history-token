multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_miata.c&n; *&n; *&t;Copyright (C) 1995 David A Rusling&n; *&t;Copyright (C) 1996 Jay A Estabrook&n; *&t;Copyright (C) 1998, 1999, 2000 Richard Henderson&n; *&n; * Code supporting the MIATA (EV56+PYXIS).&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/core_cia.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq_impl.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
macro_line|#include &quot;machvec_impl.h&quot;
r_static
r_void
DECL|function|miata_srm_device_interrupt
id|miata_srm_device_interrupt
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
multiline_comment|/*&n;&t; * I really hate to do this, but the MIATA SRM console ignores the&n;&t; *  low 8 bits in the interrupt summary register, and reports the&n;&t; *  vector 0x80 *lower* than I expected from the bit numbering in&n;&t; *  the documentation.&n;&t; * This was done because the low 8 summary bits really aren&squot;t used&n;&t; *  for reporting any interrupts (the PCI-ISA bridge, bit 7, isn&squot;t&n;&t; *  used for this purpose, as PIC interrupts are delivered as the&n;&t; *  vectors 0x800-0x8f0).&n;&t; * But I really don&squot;t want to change the fixup code for allocation&n;&t; *  of IRQs, nor the alpha_irq_mask maintenance stuff, both of which&n;&t; *  look nice and clean now.&n;&t; * So, here&squot;s this grotty hack... :-(&n;&t; */
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
l_int|8
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
DECL|function|miata_init_irq
id|miata_init_irq
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|alpha_using_srm
)paren
id|alpha_mv.device_interrupt
op_assign
id|miata_srm_device_interrupt
suffix:semicolon
macro_line|#if 0
multiline_comment|/* These break on MiataGL so we&squot;ll try not to do it at all.  */
op_star
(paren
id|vulp
)paren
id|PYXIS_INT_HILO
op_assign
l_int|0x000000B2UL
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* ISA/NMI HI */
op_star
(paren
id|vulp
)paren
id|PYXIS_RT_COUNT
op_assign
l_int|0UL
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* clear count */
macro_line|#endif
id|init_i8259a_irqs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Not interested in the bogus interrupts (3,10), Fan Fault (0),&n;           NMI (1), or EIDE (9).&n;&n;&t;   We also disable the risers (4,5), since we don&squot;t know how to&n;&t;   route the interrupts behind the bridge.  */
id|init_pyxis_irqs
c_func
(paren
l_int|0x63b0000
)paren
suffix:semicolon
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
l_int|2
comma
op_amp
id|halt_switch_irqaction
)paren
suffix:semicolon
multiline_comment|/* SRM only? */
id|setup_irq
c_func
(paren
l_int|16
op_plus
l_int|6
comma
op_amp
id|timer_cascade_irqaction
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * PCI Fixup configuration.&n; *&n; * Summary @ PYXIS_INT_REQ:&n; * Bit      Meaning&n; * 0        Fan Fault&n; * 1        NMI&n; * 2        Halt/Reset switch&n; * 3        none&n; * 4        CID0 (Riser ID)&n; * 5        CID1 (Riser ID)&n; * 6        Interval timer&n; * 7        PCI-ISA Bridge&n; * 8        Ethernet&n; * 9        EIDE (deprecated, ISA 14/15 used)&n; *10        none&n; *11        USB&n; *12        Interrupt Line A from slot 4&n; *13        Interrupt Line B from slot 4&n; *14        Interrupt Line C from slot 4&n; *15        Interrupt Line D from slot 4&n; *16        Interrupt Line A from slot 5&n; *17        Interrupt line B from slot 5&n; *18        Interrupt Line C from slot 5&n; *19        Interrupt Line D from slot 5&n; *20        Interrupt Line A from slot 1&n; *21        Interrupt Line B from slot 1&n; *22        Interrupt Line C from slot 1&n; *23        Interrupt Line D from slot 1&n; *24        Interrupt Line A from slot 2&n; *25        Interrupt Line B from slot 2&n; *26        Interrupt Line C from slot 2&n; *27        Interrupt Line D from slot 2&n; *27        Interrupt Line A from slot 3&n; *29        Interrupt Line B from slot 3&n; *30        Interrupt Line C from slot 3&n; *31        Interrupt Line D from slot 3&n; *&n; * The device to slot mapping looks like:&n; *&n; * Slot     Device&n; *  3       DC21142 Ethernet&n; *  4       EIDE CMD646&n; *  5       none&n; *  6       USB&n; *  7       PCI-ISA bridge&n; *  8       PCI-PCI Bridge      (SBU Riser)&n; *  9       none&n; * 10       none&n; * 11       PCI on board slot 4 (SBU Riser)&n; * 12       PCI on board slot 5 (SBU Riser)&n; *&n; *  These are behind the bridge, so I&squot;m not sure what to do...&n; *&n; * 13       PCI on board slot 1 (SBU Riser)&n; * 14       PCI on board slot 2 (SBU Riser)&n; * 15       PCI on board slot 3 (SBU Riser)&n; *   &n; *&n; * This two layered interrupt approach means that we allocate IRQ 16 and &n; * above for PCI interrupts.  The IRQ relates to which bit the interrupt&n; * comes in on.  This makes interrupt processing much easier.&n; */
r_static
r_int
id|__init
DECL|function|miata_map_irq
id|miata_map_irq
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
l_int|18
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
l_int|8
comma
l_int|16
op_plus
l_int|8
comma
l_int|16
op_plus
l_int|8
)brace
comma
multiline_comment|/* IdSel 14,  DC21142 */
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
multiline_comment|/* IdSel 15,  EIDE    */
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
multiline_comment|/* IdSel 16,  none    */
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
multiline_comment|/* IdSel 17,  none    */
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
multiline_comment|/* IdSel 18,  PCI-ISA */
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
multiline_comment|/* IdSel 19,  PCI-PCI */
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
multiline_comment|/* IdSel 20,  none    */
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
multiline_comment|/* IdSel 21,  none    */
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
multiline_comment|/* IdSel 22,  slot 4  */
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
multiline_comment|/* IdSel 23,  slot 5  */
multiline_comment|/* the next 7 are actually on PCI bus 1, across the bridge */
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
l_int|11
comma
l_int|16
op_plus
l_int|11
comma
l_int|16
op_plus
l_int|11
)brace
comma
multiline_comment|/* IdSel 24,  QLISP/GL*/
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
multiline_comment|/* IdSel 25,  none    */
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
multiline_comment|/* IdSel 26,  none    */
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
multiline_comment|/* IdSel 27,  none    */
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
multiline_comment|/* IdSel 28,  slot 1  */
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
multiline_comment|/* IdSel 29,  slot 2  */
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
multiline_comment|/* IdSel 30,  slot 3  */
multiline_comment|/* This bridge is on the main bus of the later orig MIATA */
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
multiline_comment|/* IdSel 31,  PCI-PCI */
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
l_int|20
comma
id|irqs_per_slot
op_assign
l_int|5
suffix:semicolon
multiline_comment|/* the USB function of the 82c693 has it&squot;s interrupt connected to &n;           the 2nd 8259 controller. So we have to check for it first. */
r_if
c_cond
(paren
(paren
id|slot
op_eq
l_int|7
)paren
op_logical_and
(paren
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
op_eq
l_int|3
)paren
)paren
(brace
id|u8
id|irq
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pci_read_config_byte
c_func
(paren
id|pci_find_slot
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
op_amp
op_complement
(paren
l_int|7
)paren
)paren
comma
l_int|0x40
comma
op_amp
id|irq
)paren
op_ne
id|PCIBIOS_SUCCESSFUL
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
r_return
id|irq
suffix:semicolon
)brace
r_return
id|COMMON_TABLE_LOOKUP
suffix:semicolon
)brace
r_static
id|u8
id|__init
DECL|function|miata_swizzle
id|miata_swizzle
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
multiline_comment|/* Check for the built-in bridge.  */
r_else
r_if
c_cond
(paren
(paren
id|PCI_SLOT
c_func
(paren
id|dev-&gt;bus-&gt;self-&gt;devfn
)paren
op_eq
l_int|8
)paren
op_logical_or
(paren
id|PCI_SLOT
c_func
(paren
id|dev-&gt;bus-&gt;self-&gt;devfn
)paren
op_eq
l_int|20
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
op_plus
l_int|9
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Must be a card-based bridge.  */
r_do
(brace
r_if
c_cond
(paren
(paren
id|PCI_SLOT
c_func
(paren
id|dev-&gt;bus-&gt;self-&gt;devfn
)paren
op_eq
l_int|8
)paren
op_logical_or
(paren
id|PCI_SLOT
c_func
(paren
id|dev-&gt;bus-&gt;self-&gt;devfn
)paren
op_eq
l_int|20
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
op_plus
l_int|9
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
r_void
id|__init
DECL|function|miata_init_pci
id|miata_init_pci
c_func
(paren
r_void
)paren
(brace
id|cia_init_pci
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
multiline_comment|/* it might be a GL (fails harmlessly if not) */
id|es1888_init
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|miata_kill_arch
id|miata_kill_arch
c_func
(paren
r_int
id|mode
)paren
(brace
id|cia_kill_arch
c_func
(paren
id|mode
)paren
suffix:semicolon
macro_line|#ifndef ALPHA_RESTORE_SRM_SETUP
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|LINUX_REBOOT_CMD_RESTART
suffix:colon
multiline_comment|/* Who said DEC engineers have no sense of humor? ;-)  */
r_if
c_cond
(paren
id|alpha_using_srm
)paren
(brace
op_star
(paren
id|vuip
)paren
id|PYXIS_RESET
op_assign
l_int|0x0000dead
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LINUX_REBOOT_CMD_HALT
suffix:colon
r_break
suffix:semicolon
r_case
id|LINUX_REBOOT_CMD_POWER_OFF
suffix:colon
r_break
suffix:semicolon
)brace
id|halt
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * The System Vector&n; */
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|miata_mv
id|__initmv
op_assign
(brace
dot
id|vector_name
op_assign
l_string|&quot;Miata&quot;
comma
id|DO_EV5_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_PYXIS_IO
comma
id|DO_CIA_BUS
comma
dot
id|machine_check
op_assign
id|cia_machine_check
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
id|PYXIS_DAC_OFFSET
comma
dot
id|nr_irqs
op_assign
l_int|48
comma
dot
id|device_interrupt
op_assign
id|pyxis_device_interrupt
comma
dot
id|init_arch
op_assign
id|pyxis_init_arch
comma
dot
id|init_irq
op_assign
id|miata_init_irq
comma
dot
id|init_rtc
op_assign
id|common_init_rtc
comma
dot
id|init_pci
op_assign
id|miata_init_pci
comma
dot
id|kill_arch
op_assign
id|miata_kill_arch
comma
dot
id|pci_map_irq
op_assign
id|miata_map_irq
comma
dot
id|pci_swizzle
op_assign
id|miata_swizzle
comma
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|miata
)paren
eof
