multiline_comment|/*&n; * arch/ppc/platform/85xx/sbc85xx.c&n; * &n; * WindRiver PowerQUICC III SBC85xx board common routines&n; *&n; * Copyright 2002, 2003 Motorola Inc.&n; * Copyright 2004 Red Hat, Inc.&n; * &n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
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
macro_line|#include &lt;asm/ppc_sys.h&gt;
macro_line|#include &lt;mm/mmu_decl.h&gt;
macro_line|#include &lt;platforms/85xx/sbc85xx.h&gt;
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
DECL|variable|pci_dram_offset
r_int
r_int
id|pci_dram_offset
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
multiline_comment|/* Internal interrupts are all Level Sensitive, and Positive Polarity */
DECL|variable|__initdata
r_static
id|u_char
id|sbc8560_openpic_initsenses
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
l_int|0x0
comma
multiline_comment|/* External  0: */
l_int|0x0
comma
multiline_comment|/* External  1: */
macro_line|#if defined(CONFIG_PCI)
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* External 2: PCI slot 0 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* External 3: PCI slot 1 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* External 4: PCI slot 2 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* External 5: PCI slot 3 */
macro_line|#else
l_int|0x0
comma
multiline_comment|/* External  2: */
l_int|0x0
comma
multiline_comment|/* External  3: */
l_int|0x0
comma
multiline_comment|/* External  4: */
l_int|0x0
comma
multiline_comment|/* External  5: */
macro_line|#endif
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* External 6: PHY */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* External 7: PHY */
l_int|0x0
comma
multiline_comment|/* External  8: */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* External 9: PHY */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_POSITIVE
)paren
comma
multiline_comment|/* External 10: PHY */
l_int|0x0
comma
multiline_comment|/* External 11: */
)brace
suffix:semicolon
multiline_comment|/* ************************************************************************ */
r_int
DECL|function|sbc8560_show_cpuinfo
id|sbc8560_show_cpuinfo
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
l_string|&quot;chip&bslash;t&bslash;t: MPC%s&bslash;n&quot;
comma
id|cur_ppc_sys_spec-&gt;ppc_sys_name
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Vendor&bslash;t&bslash;t: Wind River&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Machine&bslash;t&bslash;t: SBC%s&bslash;n&quot;
comma
id|cur_ppc_sys_spec-&gt;ppc_sys_name
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
r_void
id|__init
DECL|function|sbc8560_init_IRQ
id|sbc8560_init_IRQ
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
id|sbc8560_openpic_initsenses
suffix:semicolon
id|OpenPIC_NumInitSenses
op_assign
r_sizeof
(paren
id|sbc8560_openpic_initsenses
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
multiline_comment|/* we let openpic interrupts starting from an offset, to &n;&t; * leave space for cascading interrupts underneath.&n;&t; */
id|openpic_init
c_func
(paren
id|MPC85xx_OPENPIC_IRQ_OFFSET
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * interrupt routing&n; */
macro_line|#ifdef CONFIG_PCI
DECL|function|mpc85xx_map_irq
r_int
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
r_static
r_char
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
op_assign
multiline_comment|/*&n;&t;     *      PCI IDSEL/INTPIN-&gt;INTLINE&n;&t;     *        A      B      C      D&n;&t;     */
(brace
(brace
id|PIRQA
comma
id|PIRQB
comma
id|PIRQC
comma
id|PIRQD
)brace
comma
(brace
id|PIRQD
comma
id|PIRQA
comma
id|PIRQB
comma
id|PIRQC
)brace
comma
(brace
id|PIRQC
comma
id|PIRQD
comma
id|PIRQA
comma
id|PIRQB
)brace
comma
(brace
id|PIRQB
comma
id|PIRQC
comma
id|PIRQD
comma
id|PIRQA
)brace
comma
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|12
comma
id|max_idsel
op_assign
l_int|15
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
)brace
DECL|function|mpc85xx_exclude_device
r_int
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
r_else
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PCI */
eof
