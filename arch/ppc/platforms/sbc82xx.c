multiline_comment|/*&n; * arch/ppc/platforms/sbc82xx.c&n; *&n; * SBC82XX platform support&n; *&n; * Author: Guy Streeter &lt;streeter@redhat.com&gt;&n; *&n; * Derived from: est8260_setup.c by Allen Curtis, ONZ&n; *&n; * Copyright 2004 Red Hat, Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/mpc8260.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
macro_line|#include &lt;asm/immap_cpm2.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
DECL|variable|callback_setup_arch
r_static
r_void
(paren
op_star
id|callback_setup_arch
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|callback_init_IRQ
r_static
r_void
(paren
op_star
id|callback_init_IRQ
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|__res
(braket
r_sizeof
(paren
id|bd_t
)paren
)braket
suffix:semicolon
r_extern
r_void
id|m8260_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|late_time_init
)paren
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|__init
DECL|function|sbc82xx_setup_arch
id|sbc82xx_setup_arch
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SBC PowerQUICC II Port&bslash;n&quot;
)paren
suffix:semicolon
id|callback_setup_arch
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_GEN_RTC
id|TODC_ALLOC
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Timer init happens before mem_init but after paging init, so we cannot&n; * directly use ioremap() at that time.&n; * late_time_init() is call after paging init.&n; */
DECL|function|sbc82xx_time_init
r_static
r_void
id|sbc82xx_time_init
c_func
(paren
r_void
)paren
(brace
r_volatile
id|memctl_cpm2_t
op_star
id|mc
op_assign
op_amp
id|cpm2_immr-&gt;im_memctl
suffix:semicolon
multiline_comment|/* Set up CS11 for RTC chip */
id|mc-&gt;memc_br11
op_assign
l_int|0
suffix:semicolon
id|mc-&gt;memc_or11
op_assign
l_int|0xffff0836
suffix:semicolon
id|mc-&gt;memc_br11
op_assign
id|SBC82xx_TODC_NVRAM_ADDR
op_or
l_int|0x0801
suffix:semicolon
id|TODC_INIT
c_func
(paren
id|TODC_TYPE_MK48T59
comma
l_int|0
comma
l_int|0
comma
id|SBC82xx_TODC_NVRAM_ADDR
comma
l_int|0
)paren
suffix:semicolon
id|todc_info-&gt;nvram_data
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|todc_info-&gt;nvram_data
comma
l_int|0x2000
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|todc_info-&gt;nvram_data
)paren
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|todc_get_rtc_time
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
id|todc_set_rtc_time
suffix:semicolon
id|ppc_md.nvram_read_val
op_assign
id|todc_direct_read_val
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
id|todc_direct_write_val
suffix:semicolon
id|todc_time_init
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_GEN_RTC */
DECL|variable|sbc82xx_i8259_map
r_static
r_volatile
r_char
op_star
id|sbc82xx_i8259_map
suffix:semicolon
DECL|variable|sbc82xx_i8259_mask
r_static
r_char
id|sbc82xx_i8259_mask
op_assign
l_int|0xff
suffix:semicolon
DECL|variable|sbc82xx_i8259_lock
r_static
id|spinlock_t
id|sbc82xx_i8259_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|sbc82xx_i8259_mask_and_ack_irq
r_static
r_void
id|sbc82xx_i8259_mask_and_ack_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|irq_nr
op_sub_assign
id|NR_SIU_INTS
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sbc82xx_i8259_lock
comma
id|flags
)paren
suffix:semicolon
id|sbc82xx_i8259_mask
op_or_assign
l_int|1
op_lshift
id|irq_nr
suffix:semicolon
(paren
r_void
)paren
id|sbc82xx_i8259_map
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Dummy read */
id|sbc82xx_i8259_map
(braket
l_int|1
)braket
op_assign
id|sbc82xx_i8259_mask
suffix:semicolon
id|sbc82xx_i8259_map
(braket
l_int|0
)braket
op_assign
l_int|0x20
suffix:semicolon
multiline_comment|/* OCW2: Non-specific EOI */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sbc82xx_i8259_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|sbc82xx_i8259_mask_irq
r_static
r_void
id|sbc82xx_i8259_mask_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|irq_nr
op_sub_assign
id|NR_SIU_INTS
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sbc82xx_i8259_lock
comma
id|flags
)paren
suffix:semicolon
id|sbc82xx_i8259_mask
op_or_assign
l_int|1
op_lshift
id|irq_nr
suffix:semicolon
id|sbc82xx_i8259_map
(braket
l_int|1
)braket
op_assign
id|sbc82xx_i8259_mask
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sbc82xx_i8259_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|sbc82xx_i8259_unmask_irq
r_static
r_void
id|sbc82xx_i8259_unmask_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|irq_nr
op_sub_assign
id|NR_SIU_INTS
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sbc82xx_i8259_lock
comma
id|flags
)paren
suffix:semicolon
id|sbc82xx_i8259_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq_nr
)paren
suffix:semicolon
id|sbc82xx_i8259_map
(braket
l_int|1
)braket
op_assign
id|sbc82xx_i8259_mask
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sbc82xx_i8259_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|sbc82xx_i8259_end_irq
r_static
r_void
id|sbc82xx_i8259_end_irq
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
op_logical_and
id|irq_desc
(braket
id|irq
)braket
dot
id|action
)paren
id|sbc82xx_i8259_unmask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|sbc82xx_i8259_ic
r_struct
id|hw_interrupt_type
id|sbc82xx_i8259_ic
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot; i8259     &quot;
comma
dot
id|enable
op_assign
id|sbc82xx_i8259_unmask_irq
comma
dot
id|disable
op_assign
id|sbc82xx_i8259_mask_irq
comma
dot
id|ack
op_assign
id|sbc82xx_i8259_mask_and_ack_irq
comma
dot
id|end
op_assign
id|sbc82xx_i8259_end_irq
comma
)brace
suffix:semicolon
DECL|function|sbc82xx_i8259_demux
r_static
id|irqreturn_t
id|sbc82xx_i8259_demux
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
id|spin_lock
c_func
(paren
op_amp
id|sbc82xx_i8259_lock
)paren
suffix:semicolon
id|sbc82xx_i8259_map
(braket
l_int|0
)braket
op_assign
l_int|0x0c
suffix:semicolon
multiline_comment|/* OCW3: Read IR register on RD# pulse */
id|irq
op_assign
id|sbc82xx_i8259_map
(braket
l_int|0
)braket
op_amp
l_int|7
suffix:semicolon
multiline_comment|/* Read IRR */
r_if
c_cond
(paren
id|irq
op_eq
l_int|7
)paren
(brace
multiline_comment|/* Possible spurious interrupt */
r_int
id|isr
suffix:semicolon
id|sbc82xx_i8259_map
(braket
l_int|0
)braket
op_assign
l_int|0x0b
suffix:semicolon
multiline_comment|/* OCW3: Read IS register on RD# pulse */
id|isr
op_assign
id|sbc82xx_i8259_map
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Read ISR */
r_if
c_cond
(paren
op_logical_neg
(paren
id|isr
op_amp
l_int|0x80
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Spurious i8259 interrupt&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
)brace
id|ppc_irq_dispatch_handler
c_func
(paren
id|regs
comma
id|NR_SIU_INTS
op_plus
id|irq
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|sbc82xx_init_IRQ
r_void
id|__init
id|sbc82xx_init_IRQ
c_func
(paren
r_void
)paren
(brace
r_volatile
id|memctl_cpm2_t
op_star
id|mc
op_assign
op_amp
id|cpm2_immr-&gt;im_memctl
suffix:semicolon
r_volatile
id|intctl_cpm2_t
op_star
id|ic
op_assign
op_amp
id|cpm2_immr-&gt;im_intctl
suffix:semicolon
r_int
id|i
suffix:semicolon
id|callback_init_IRQ
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* u-boot doesn&squot;t always set the board up correctly */
id|mc-&gt;memc_br5
op_assign
l_int|0
suffix:semicolon
id|mc-&gt;memc_or5
op_assign
l_int|0xfff00856
suffix:semicolon
id|mc-&gt;memc_br5
op_assign
l_int|0x22000801
suffix:semicolon
id|sbc82xx_i8259_map
op_assign
id|ioremap
c_func
(paren
l_int|0x22008000
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbc82xx_i8259_map
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Mapping i8259 interrupt controller failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Set up the interrupt handlers for the i8259 IRQs */
r_for
c_loop
(paren
id|i
op_assign
id|NR_SIU_INTS
suffix:semicolon
id|i
OL
id|NR_SIU_INTS
op_plus
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|sbc82xx_i8259_ic
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|status
op_or_assign
id|IRQ_LEVEL
suffix:semicolon
)brace
multiline_comment|/* make IRQ6 level sensitive */
id|ic-&gt;ic_siexr
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
l_int|14
op_minus
(paren
id|SIU_INT_IRQ6
op_minus
id|SIU_INT_IRQ1
)paren
)paren
)paren
suffix:semicolon
id|irq_desc
(braket
id|SIU_INT_IRQ6
)braket
dot
id|status
op_or_assign
id|IRQ_LEVEL
suffix:semicolon
multiline_comment|/* Initialise the i8259 */
id|sbc82xx_i8259_map
(braket
l_int|0
)braket
op_assign
l_int|0x1b
suffix:semicolon
multiline_comment|/* ICW1: Level, no cascade, ICW4 */
id|sbc82xx_i8259_map
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* ICW2: vector base */
multiline_comment|/* No ICW3 (no cascade) */
id|sbc82xx_i8259_map
(braket
l_int|1
)braket
op_assign
l_int|0x01
suffix:semicolon
multiline_comment|/* ICW4: 8086 mode, normal EOI */
id|sbc82xx_i8259_map
(braket
l_int|0
)braket
op_assign
l_int|0x0b
suffix:semicolon
multiline_comment|/* OCW3: Read IS register on RD# pulse */
id|sbc82xx_i8259_map
(braket
l_int|1
)braket
op_assign
id|sbc82xx_i8259_mask
suffix:semicolon
multiline_comment|/* Set interrupt mask */
multiline_comment|/* Request cascade IRQ */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|SIU_INT_IRQ6
comma
id|sbc82xx_i8259_demux
comma
id|SA_INTERRUPT
comma
l_string|&quot;i8259 demux&quot;
comma
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Installation of i8259 IRQ demultiplexer failed.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|sbc82xx_pci_map_irq
r_static
r_int
id|sbc82xx_pci_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
r_char
id|idsel
comma
r_int
r_char
id|pin
)paren
(brace
r_static
r_char
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
op_assign
(brace
multiline_comment|/*&n;&t;&t; * PCI IDSEL/INTPIN-&gt;INTLINE&n;&t;&t; *  A      B      C      D&n;&t;&t; */
(brace
id|SBC82xx_PIRQA
comma
id|SBC82xx_PIRQB
comma
id|SBC82xx_PIRQC
comma
id|SBC82xx_PIRQD
)brace
comma
multiline_comment|/* IDSEL 16 - PMC slot */
(brace
id|SBC82xx_PC_IRQA
comma
id|SBC82xx_PC_IRQB
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* IDSEL 17 - CardBus */
(brace
id|SBC82xx_PIRQA
comma
id|SBC82xx_PIRQB
comma
id|SBC82xx_PIRQC
comma
id|SBC82xx_PIRQD
)brace
comma
multiline_comment|/* IDSEL 18 - PCI-X bridge */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|16
comma
id|max_idsel
op_assign
l_int|18
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
)brace
r_void
id|__init
DECL|function|platform_init
id|platform_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
(brace
multiline_comment|/* Generic 8260 platform initialization */
id|m8260_init
c_func
(paren
id|r3
comma
id|r4
comma
id|r5
comma
id|r6
comma
id|r7
)paren
suffix:semicolon
multiline_comment|/* u-boot may be using one of the FCC Ethernet devices.&n;&t;   Use the MAC address to the SCC. */
id|__res
(braket
m_offsetof
(paren
id|bd_t
comma
id|bi_enetaddr
(braket
l_int|5
)braket
)paren
)braket
op_and_assign
op_complement
l_int|3
suffix:semicolon
multiline_comment|/* Anything special for this platform */
id|callback_setup_arch
op_assign
id|ppc_md.setup_arch
suffix:semicolon
id|callback_init_IRQ
op_assign
id|ppc_md.init_IRQ
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|sbc82xx_setup_arch
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|sbc82xx_init_IRQ
suffix:semicolon
id|ppc_md.pci_map_irq
op_assign
id|sbc82xx_pci_map_irq
suffix:semicolon
macro_line|#ifdef CONFIG_GEN_RTC
id|ppc_md.time_init
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.nvram_read_val
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
l_int|NULL
suffix:semicolon
id|late_time_init
op_assign
id|sbc82xx_time_init
suffix:semicolon
macro_line|#endif /* CONFIG_GEN_RTC */
)brace
eof
