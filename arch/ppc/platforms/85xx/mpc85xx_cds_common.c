multiline_comment|/*&n; * arch/ppc/platform/85xx/mpc85xx_cds_common.c&n; *&n; * MPC85xx CDS board specific routines&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2004 Freescale Semiconductor, Inc&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/fsl_devices.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/open_pic.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/mpc85xx.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/immap_85xx.h&gt;
macro_line|#include &lt;asm/immap_cpm2.h&gt;
macro_line|#include &lt;asm/ppc_sys.h&gt;
macro_line|#include &lt;asm/kgdb.h&gt;
macro_line|#include &lt;mm/mmu_decl.h&gt;
macro_line|#include &lt;syslib/cpm2_pic.h&gt;
macro_line|#include &lt;syslib/ppc85xx_common.h&gt;
macro_line|#include &lt;syslib/ppc85xx_setup.h&gt;
macro_line|#ifndef CONFIG_PCI
DECL|variable|isa_io_base
r_int
r_int
id|isa_io_base
op_assign
l_int|0
suffix:semicolon
DECL|variable|isa_mem_base
r_int
r_int
id|isa_mem_base
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_extern
r_int
r_int
id|total_memory
suffix:semicolon
multiline_comment|/* in mm/init */
DECL|variable|__res
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
DECL|variable|cds_pci_slot
r_static
r_int
id|cds_pci_slot
op_assign
l_int|2
suffix:semicolon
DECL|variable|cadmus
r_static
r_volatile
id|u8
op_star
id|cadmus
suffix:semicolon
multiline_comment|/* Internal interrupts are all Level Sensitive, and Positive Polarity */
DECL|variable|__initdata
r_static
id|u_char
id|mpc85xx_cds_openpic_initsenses
(braket
)braket
id|__initdata
op_assign
(brace
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal  0: L2 Cache */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal  1: ECM */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal  2: DDR DRAM */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal  3: LBIU */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal  4: DMA 0 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal  5: DMA 1 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal  6: DMA 2 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal  7: DMA 3 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal  8: PCI/PCI-X */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal  9: RIO Inbound Port Write Error */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 10: RIO Doorbell Inbound */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 11: RIO Outbound Message */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 12: RIO Inbound Message */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 13: TSEC 0 Transmit */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 14: TSEC 0 Receive */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 15: Unused */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 16: Unused */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 17: Unused */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 18: TSEC 0 Receive/Transmit Error */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 19: TSEC 1 Transmit */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 20: TSEC 1 Receive */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 21: Unused */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 22: Unused */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 23: Unused */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 24: TSEC 1 Receive/Transmit Error */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 25: Fast Ethernet */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 26: DUART */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 27: I2C */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 28: Performance Monitor */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 29: Unused */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 30: CPM */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* Internal 31: Unused */
macro_line|#if defined(CONFIG_PCI)
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* External 0: PCI1 slot */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* External 1: PCI1 slot */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* External 2: PCI1 slot */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* External 3: PCI1 slot */
macro_line|#else
l_int|0x0
comma
multiline_comment|/* External  0: */
l_int|0x0
comma
multiline_comment|/* External  1: */
l_int|0x0
comma
multiline_comment|/* External  2: */
l_int|0x0
comma
multiline_comment|/* External  3: */
macro_line|#endif
l_int|0x0
comma
multiline_comment|/* External  4: */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* External 5: PHY */
l_int|0x0
comma
multiline_comment|/* External  6: */
l_int|0x0
comma
multiline_comment|/* External  7: */
l_int|0x0
comma
multiline_comment|/* External  8: */
l_int|0x0
comma
multiline_comment|/* External  9: */
l_int|0x0
comma
multiline_comment|/* External 10: */
macro_line|#if defined(CONFIG_85xx_PCI2) &amp;&amp; defined(CONFIG_PCI)
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* External 11: PCI2 slot 0 */
macro_line|#else
l_int|0x0
comma
multiline_comment|/* External 11: */
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* ************************************************************************ */
r_int
DECL|function|mpc85xx_cds_show_cpuinfo
id|mpc85xx_cds_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
id|uint
id|pvid
comma
id|svid
comma
id|phid1
suffix:semicolon
id|uint
id|memsize
op_assign
id|total_memory
suffix:semicolon
id|bd_t
op_star
id|binfo
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
r_int
r_int
id|freq
suffix:semicolon
multiline_comment|/* get the core frequency */
id|freq
op_assign
id|binfo-&gt;bi_intfreq
suffix:semicolon
id|pvid
op_assign
id|mfspr
c_func
(paren
id|PVR
)paren
suffix:semicolon
id|svid
op_assign
id|mfspr
c_func
(paren
id|SVR
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Vendor&bslash;t&bslash;t: Freescale Semiconductor&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Machine&bslash;t&bslash;t: CDS (%x)&bslash;n&quot;
comma
id|cadmus
(braket
id|CM_VER
)braket
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;clock&bslash;t&bslash;t: %dMHz&bslash;n&quot;
comma
id|freq
op_div
l_int|1000000
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;PVR&bslash;t&bslash;t: 0x%x&bslash;n&quot;
comma
id|pvid
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;SVR&bslash;t&bslash;t: 0x%x&bslash;n&quot;
comma
id|svid
)paren
suffix:semicolon
multiline_comment|/* Display cpu Pll setting */
id|phid1
op_assign
id|mfspr
c_func
(paren
id|HID1
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;PLL setting&bslash;t: 0x%x&bslash;n&quot;
comma
(paren
(paren
id|phid1
op_rshift
l_int|24
)paren
op_amp
l_int|0x3f
)paren
)paren
suffix:semicolon
multiline_comment|/* Display the amount of memory */
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Memory&bslash;t&bslash;t: %d MB&bslash;n&quot;
comma
id|memsize
op_div
(paren
l_int|1024
op_star
l_int|1024
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_CPM2
DECL|function|cpm2_cascade
r_static
r_void
id|cpm2_cascade
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
r_while
c_loop
(paren
(paren
id|irq
op_assign
id|cpm2_get_irq
c_func
(paren
id|regs
)paren
)paren
op_ge
l_int|0
)paren
(brace
id|__do_IRQ
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
DECL|variable|cpm2_irqaction
r_static
r_struct
id|irqaction
id|cpm2_irqaction
op_assign
(brace
dot
id|handler
op_assign
id|cpm2_cascade
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|mask
op_assign
id|CPU_MASK_NONE
comma
dot
id|name
op_assign
l_string|&quot;cpm2_cascade&quot;
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_CPM2 */
r_void
id|__init
DECL|function|mpc85xx_cds_init_IRQ
id|mpc85xx_cds_init_IRQ
c_func
(paren
r_void
)paren
(brace
id|bd_t
op_star
id|binfo
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
macro_line|#ifdef CONFIG_CPM2
r_volatile
id|cpm2_map_t
op_star
id|immap
op_assign
id|cpm2_immr
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#endif
multiline_comment|/* Determine the Physical Address of the OpenPIC regs */
id|phys_addr_t
id|OpenPIC_PAddr
op_assign
id|binfo-&gt;bi_immr_base
op_plus
id|MPC85xx_OPENPIC_OFFSET
suffix:semicolon
id|OpenPIC_Addr
op_assign
id|ioremap
c_func
(paren
id|OpenPIC_PAddr
comma
id|MPC85xx_OPENPIC_SIZE
)paren
suffix:semicolon
id|OpenPIC_InitSenses
op_assign
id|mpc85xx_cds_openpic_initsenses
suffix:semicolon
id|OpenPIC_NumInitSenses
op_assign
r_sizeof
(paren
id|mpc85xx_cds_openpic_initsenses
)paren
suffix:semicolon
multiline_comment|/* Skip reserved space and internal sources */
id|openpic_set_sources
c_func
(paren
l_int|0
comma
l_int|32
comma
id|OpenPIC_Addr
op_plus
l_int|0x10200
)paren
suffix:semicolon
multiline_comment|/* Map PIC IRQs 0-11 */
id|openpic_set_sources
c_func
(paren
l_int|32
comma
l_int|12
comma
id|OpenPIC_Addr
op_plus
l_int|0x10000
)paren
suffix:semicolon
multiline_comment|/* we let openpic interrupts starting from an offset, to&n;         * leave space for cascading interrupts underneath.&n;         */
id|openpic_init
c_func
(paren
id|MPC85xx_OPENPIC_IRQ_OFFSET
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPM2
multiline_comment|/* disable all CPM interupts */
id|immap-&gt;im_intctl.ic_simrh
op_assign
l_int|0x0
suffix:semicolon
id|immap-&gt;im_intctl.ic_simrl
op_assign
l_int|0x0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|CPM_IRQ_OFFSET
suffix:semicolon
id|i
OL
(paren
id|NR_CPM_INTS
op_plus
id|CPM_IRQ_OFFSET
)paren
suffix:semicolon
id|i
op_increment
)paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|cpm2_pic
suffix:semicolon
multiline_comment|/* Initialize the default interrupt mapping priorities,&n;&t; * in case the boot rom changed something on us.&n;&t; */
id|immap-&gt;im_intctl.ic_sicr
op_assign
l_int|0
suffix:semicolon
id|immap-&gt;im_intctl.ic_scprrh
op_assign
l_int|0x05309770
suffix:semicolon
id|immap-&gt;im_intctl.ic_scprrl
op_assign
l_int|0x05309770
suffix:semicolon
id|setup_irq
c_func
(paren
id|MPC85xx_IRQ_CPM
comma
op_amp
id|cpm2_irqaction
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PCI
multiline_comment|/*&n; * interrupt routing&n; */
r_int
DECL|function|mpc85xx_map_irq
id|mpc85xx_map_irq
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
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|pci_bus_to_hose
c_func
(paren
id|dev-&gt;bus-&gt;number
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hose-&gt;index
)paren
(brace
multiline_comment|/* Handle PCI1 interrupts */
r_char
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
op_assign
multiline_comment|/*&n;&t;&t;&t; *      PCI IDSEL/INTPIN-&gt;INTLINE&n;&t;&t;&t; *        A      B      C      D&n;&t;&t;&t; */
multiline_comment|/* Note IRQ assignment for slots is based on which slot the elysium is&n;&t;&t;&t; * in -- in this setup elysium is in slot #2 (this PIRQA as first&n;&t;&t;&t; * interrupt on slot */
(brace
(brace
l_int|0
comma
l_int|1
comma
l_int|2
comma
l_int|3
)brace
comma
multiline_comment|/* 16 - PMC */
(brace
l_int|3
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* 17 P2P (Tsi320) */
(brace
l_int|0
comma
l_int|1
comma
l_int|2
comma
l_int|3
)brace
comma
multiline_comment|/* 18 - Slot 1 */
(brace
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|0
)brace
comma
multiline_comment|/* 19 - Slot 2 */
(brace
l_int|2
comma
l_int|3
comma
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* 20 - Slot 3 */
(brace
l_int|3
comma
l_int|0
comma
l_int|1
comma
l_int|2
)brace
comma
multiline_comment|/* 21 - Slot 4 */
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
l_int|21
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|4
suffix:semicolon
id|j
op_increment
)paren
id|pci_irq_table
(braket
id|i
)braket
(braket
id|j
)braket
op_assign
(paren
(paren
id|pci_irq_table
(braket
id|i
)braket
(braket
id|j
)braket
op_plus
l_int|5
op_minus
id|cds_pci_slot
)paren
op_amp
l_int|0x3
)paren
op_plus
id|PIRQ0A
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Handle PCI2 interrupts (if we have one) */
r_char
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
op_assign
(brace
multiline_comment|/*&n;&t;&t;&t; * We only have one slot and one interrupt&n;&t;&t;&t; * going to PIRQA - PIRQD */
(brace
id|PIRQ1A
comma
id|PIRQ1A
comma
id|PIRQ1A
comma
id|PIRQ1A
)brace
comma
multiline_comment|/* 21 - slot 0 */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|21
comma
id|max_idsel
op_assign
l_int|21
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
)brace
)brace
DECL|macro|ARCADIA_HOST_BRIDGE_IDSEL
mdefine_line|#define ARCADIA_HOST_BRIDGE_IDSEL     17
DECL|macro|ARCADIA_2ND_BRIDGE_IDSEL
mdefine_line|#define ARCADIA_2ND_BRIDGE_IDSEL     3
r_int
DECL|function|mpc85xx_exclude_device
id|mpc85xx_exclude_device
c_func
(paren
id|u_char
id|bus
comma
id|u_char
id|devfn
)paren
(brace
r_if
c_cond
(paren
id|bus
op_eq
l_int|0
op_logical_and
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
op_eq
l_int|0
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
macro_line|#ifdef CONFIG_85xx_PCI2
multiline_comment|/* With the current code we know PCI2 will be bus 2, however this may&n;&t; * not be guarnteed */
r_if
c_cond
(paren
id|bus
op_eq
l_int|2
op_logical_and
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
op_eq
l_int|0
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
macro_line|#endif
multiline_comment|/* We explicitly do not go past the Tundra 320 Bridge */
r_if
c_cond
(paren
id|bus
op_eq
l_int|1
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bus
op_eq
l_int|0
)paren
op_logical_and
(paren
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
op_eq
id|ARCADIA_2ND_BRIDGE_IDSEL
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
r_else
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PCI */
multiline_comment|/* ************************************************************************&n; *&n; * Setup the architecture&n; *&n; */
r_static
r_void
id|__init
DECL|function|mpc85xx_cds_setup_arch
id|mpc85xx_cds_setup_arch
c_func
(paren
r_void
)paren
(brace
id|bd_t
op_star
id|binfo
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
r_int
r_int
id|freq
suffix:semicolon
r_struct
id|gianfar_platform_data
op_star
id|pdata
suffix:semicolon
multiline_comment|/* get the core frequency */
id|freq
op_assign
id|binfo-&gt;bi_intfreq
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;mpc85xx_cds_setup_arch&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPM2
id|cpm2_reset
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|cadmus
op_assign
id|ioremap
c_func
(paren
id|CADMUS_BASE
comma
id|CADMUS_SIZE
)paren
suffix:semicolon
id|cds_pci_slot
op_assign
(paren
(paren
id|cadmus
(braket
id|CM_CSR
)braket
op_rshift
l_int|6
)paren
op_amp
l_int|0x3
)paren
op_plus
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CDS Version = %x in PCI slot %d&bslash;n&quot;
comma
id|cadmus
(braket
id|CM_VER
)braket
comma
id|cds_pci_slot
)paren
suffix:semicolon
multiline_comment|/* Set loops_per_jiffy to a half-way reasonable value,&n;           for use until calibrate_delay gets called. */
id|loops_per_jiffy
op_assign
id|freq
op_div
id|HZ
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
multiline_comment|/* setup PCI host bridges */
id|mpc85xx_setup_hose
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_8250
id|mpc85xx_early_serial_map
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_TEXT_DEBUG
multiline_comment|/* Invalidate the entry we stole earlier the serial ports&n;&t; * should be properly mapped */
id|invalidate_tlbcam_entry
c_func
(paren
id|NUM_TLBCAMS
op_minus
l_int|1
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* setup the board related information for the enet controllers */
id|pdata
op_assign
(paren
r_struct
id|gianfar_platform_data
op_star
)paren
id|ppc_sys_get_pdata
c_func
(paren
id|MPC85xx_TSEC1
)paren
suffix:semicolon
id|pdata-&gt;board_flags
op_assign
id|FSL_GIANFAR_BRD_HAS_PHY_INTR
suffix:semicolon
id|pdata-&gt;interruptPHY
op_assign
id|MPC85xx_IRQ_EXT5
suffix:semicolon
id|pdata-&gt;phyid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* fixup phy address */
id|pdata-&gt;phy_reg_addr
op_add_assign
id|binfo-&gt;bi_immr_base
suffix:semicolon
id|memcpy
c_func
(paren
id|pdata-&gt;mac_addr
comma
id|binfo-&gt;bi_enetaddr
comma
l_int|6
)paren
suffix:semicolon
id|pdata
op_assign
(paren
r_struct
id|gianfar_platform_data
op_star
)paren
id|ppc_sys_get_pdata
c_func
(paren
id|MPC85xx_TSEC2
)paren
suffix:semicolon
id|pdata-&gt;board_flags
op_assign
id|FSL_GIANFAR_BRD_HAS_PHY_INTR
suffix:semicolon
id|pdata-&gt;interruptPHY
op_assign
id|MPC85xx_IRQ_EXT5
suffix:semicolon
id|pdata-&gt;phyid
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* fixup phy address */
id|pdata-&gt;phy_reg_addr
op_add_assign
id|binfo-&gt;bi_immr_base
suffix:semicolon
id|memcpy
c_func
(paren
id|pdata-&gt;mac_addr
comma
id|binfo-&gt;bi_enet1addr
comma
l_int|6
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|initrd_start
)paren
id|ROOT_DEV
op_assign
id|Root_RAM0
suffix:semicolon
r_else
macro_line|#endif
macro_line|#ifdef  CONFIG_ROOT_NFS
id|ROOT_DEV
op_assign
id|Root_NFS
suffix:semicolon
macro_line|#else
id|ROOT_DEV
op_assign
id|Root_HDA1
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* ************************************************************************ */
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
multiline_comment|/* parse_bootinfo must always be called first */
id|parse_bootinfo
c_func
(paren
id|find_bootinfo
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;         * If we were passed in a board information, copy it into the&n;         * residual data area.&n;         */
r_if
c_cond
(paren
id|r3
)paren
(brace
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|__res
comma
(paren
r_void
op_star
)paren
(paren
id|r3
op_plus
id|KERNELBASE
)paren
comma
r_sizeof
(paren
id|bd_t
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SERIAL_TEXT_DEBUG
(brace
id|bd_t
op_star
id|binfo
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
multiline_comment|/* Use the last TLB entry to map CCSRBAR to allow access to DUART regs */
id|settlbcam
c_func
(paren
id|NUM_TLBCAMS
op_minus
l_int|1
comma
id|binfo-&gt;bi_immr_base
comma
id|binfo-&gt;bi_immr_base
comma
id|MPC85xx_CCSRBAR_SIZE
comma
id|_PAGE_IO
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_BLK_DEV_INITRD)
multiline_comment|/*&n;         * If the init RAM disk has been configured in, and there&squot;s a valid&n;         * starting address for it, set it up.&n;         */
r_if
c_cond
(paren
id|r4
)paren
(brace
id|initrd_start
op_assign
id|r4
op_plus
id|KERNELBASE
suffix:semicolon
id|initrd_end
op_assign
id|r5
op_plus
id|KERNELBASE
suffix:semicolon
)brace
macro_line|#endif                          /* CONFIG_BLK_DEV_INITRD */
multiline_comment|/* Copy the kernel command line arguments to a safe place. */
r_if
c_cond
(paren
id|r6
)paren
(brace
op_star
(paren
r_char
op_star
)paren
(paren
id|r7
op_plus
id|KERNELBASE
)paren
op_assign
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
id|cmd_line
comma
(paren
r_char
op_star
)paren
(paren
id|r6
op_plus
id|KERNELBASE
)paren
)paren
suffix:semicolon
)brace
id|identify_ppc_sys_by_id
c_func
(paren
id|mfspr
c_func
(paren
id|SVR
)paren
)paren
suffix:semicolon
multiline_comment|/* setup the PowerPC module struct */
id|ppc_md.setup_arch
op_assign
id|mpc85xx_cds_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|mpc85xx_cds_show_cpuinfo
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|mpc85xx_cds_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|openpic_get_irq
suffix:semicolon
id|ppc_md.restart
op_assign
id|mpc85xx_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|mpc85xx_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|mpc85xx_halt
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|mpc85xx_find_end_of_memory
suffix:semicolon
id|ppc_md.time_init
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|mpc85xx_calibrate_decr
suffix:semicolon
macro_line|#if defined(CONFIG_SERIAL_8250) &amp;&amp; defined(CONFIG_SERIAL_TEXT_DEBUG)
id|ppc_md.progress
op_assign
id|gen550_progress
suffix:semicolon
macro_line|#endif /* CONFIG_SERIAL_8250 &amp;&amp; CONFIG_SERIAL_TEXT_DEBUG */
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;mpc85xx_cds_init(): exit&quot;
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
