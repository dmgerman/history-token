multiline_comment|/*&n; *  linux/arch/arm/mach-footbridge/common.c&n; *&n; *  Copyright (C) 1998-2000 Russell King, Dave Gilbert.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/hardware/dec21285.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &quot;common.h&quot;
r_extern
r_void
id|__init
id|isa_init_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
DECL|variable|mem_fclk_21285
r_int
r_int
id|mem_fclk_21285
op_assign
l_int|50000000
suffix:semicolon
DECL|variable|mem_fclk_21285
id|EXPORT_SYMBOL
c_func
(paren
id|mem_fclk_21285
)paren
suffix:semicolon
DECL|function|parse_tag_memclk
r_static
r_int
id|__init
id|parse_tag_memclk
c_func
(paren
r_const
r_struct
id|tag
op_star
id|tag
)paren
(brace
id|mem_fclk_21285
op_assign
id|tag-&gt;u.memclk.fmemclk
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__tagtable
c_func
(paren
id|ATAG_MEMCLK
comma
id|parse_tag_memclk
)paren
suffix:semicolon
multiline_comment|/*&n; * Footbridge IRQ translation table&n; *  Converts from our IRQ numbers into FootBridge masks&n; */
DECL|variable|fb_irq_mask
r_static
r_const
r_int
id|fb_irq_mask
(braket
)braket
op_assign
(brace
id|IRQ_MASK_UART_RX
comma
multiline_comment|/*  0 */
id|IRQ_MASK_UART_TX
comma
multiline_comment|/*  1 */
id|IRQ_MASK_TIMER1
comma
multiline_comment|/*  2 */
id|IRQ_MASK_TIMER2
comma
multiline_comment|/*  3 */
id|IRQ_MASK_TIMER3
comma
multiline_comment|/*  4 */
id|IRQ_MASK_IN0
comma
multiline_comment|/*  5 */
id|IRQ_MASK_IN1
comma
multiline_comment|/*  6 */
id|IRQ_MASK_IN2
comma
multiline_comment|/*  7 */
id|IRQ_MASK_IN3
comma
multiline_comment|/*  8 */
id|IRQ_MASK_DOORBELLHOST
comma
multiline_comment|/*  9 */
id|IRQ_MASK_DMA1
comma
multiline_comment|/* 10 */
id|IRQ_MASK_DMA2
comma
multiline_comment|/* 11 */
id|IRQ_MASK_PCI
comma
multiline_comment|/* 12 */
id|IRQ_MASK_SDRAMPARITY
comma
multiline_comment|/* 13 */
id|IRQ_MASK_I2OINPOST
comma
multiline_comment|/* 14 */
id|IRQ_MASK_PCI_ABORT
comma
multiline_comment|/* 15 */
id|IRQ_MASK_PCI_SERR
comma
multiline_comment|/* 16 */
id|IRQ_MASK_DISCARD_TIMER
comma
multiline_comment|/* 17 */
id|IRQ_MASK_PCI_DPERR
comma
multiline_comment|/* 18 */
id|IRQ_MASK_PCI_PERR
comma
multiline_comment|/* 19 */
)brace
suffix:semicolon
DECL|function|fb_mask_irq
r_static
r_void
id|fb_mask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
op_star
id|CSR_IRQ_DISABLE
op_assign
id|fb_irq_mask
(braket
id|_DC21285_INR
c_func
(paren
id|irq
)paren
)braket
suffix:semicolon
)brace
DECL|function|fb_unmask_irq
r_static
r_void
id|fb_unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
op_star
id|CSR_IRQ_ENABLE
op_assign
id|fb_irq_mask
(braket
id|_DC21285_INR
c_func
(paren
id|irq
)paren
)braket
suffix:semicolon
)brace
DECL|variable|fb_chip
r_static
r_struct
id|irqchip
id|fb_chip
op_assign
(brace
dot
id|ack
op_assign
id|fb_mask_irq
comma
dot
id|mask
op_assign
id|fb_mask_irq
comma
dot
id|unmask
op_assign
id|fb_unmask_irq
comma
)brace
suffix:semicolon
DECL|function|__fb_init_irq
r_static
r_void
id|__init
id|__fb_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/*&n;&t; * setup DC21285 IRQs&n;&t; */
op_star
id|CSR_IRQ_DISABLE
op_assign
op_minus
l_int|1
suffix:semicolon
op_star
id|CSR_FIQ_DISABLE
op_assign
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
id|_DC21285_IRQ
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|irq
OL
id|_DC21285_IRQ
c_func
(paren
l_int|20
)paren
suffix:semicolon
id|irq
op_increment
)paren
(brace
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|fb_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|irq
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|irq
comma
id|IRQF_VALID
op_or
id|IRQF_PROBE
)paren
suffix:semicolon
)brace
)brace
DECL|function|footbridge_init_irq
r_void
id|__init
id|footbridge_init_irq
c_func
(paren
r_void
)paren
(brace
id|__fb_init_irq
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|footbridge_cfn_mode
c_func
(paren
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_ebsa285
c_func
(paren
)paren
)paren
multiline_comment|/* The following is dependent on which slot&n;&t;&t; * you plug the Southbridge card into.  We&n;&t;&t; * currently assume that you plug it into&n;&t;&t; * the right-hand most slot.&n;&t;&t; */
id|isa_init_irq
c_func
(paren
id|IRQ_PCI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_cats
c_func
(paren
)paren
)paren
id|isa_init_irq
c_func
(paren
id|IRQ_IN2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_netwinder
c_func
(paren
)paren
)paren
id|isa_init_irq
c_func
(paren
id|IRQ_IN3
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Common mapping for all systems.  Note that the outbound write flush is&n; * commented out since there is a &quot;No Fix&quot; problem with it.  Not mapping&n; * it means that we have extra bullet protection on our feet.&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|fb_common_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|ARMCSR_BASE
comma
id|DC21285_ARMCSR_BASE
comma
id|ARMCSR_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|XBUS_BASE
comma
l_int|0x40000000
comma
id|XBUS_SIZE
comma
id|MT_DEVICE
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * The mapping when the footbridge is in host mode.  We don&squot;t map any of&n; * this when we are in add-in mode.&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|ebsa285_host_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
macro_line|#if defined(CONFIG_ARCH_FOOTBRIDGE) &amp;&amp; defined(CONFIG_FOOTBRIDGE_HOST)
(brace
id|PCIMEM_BASE
comma
id|DC21285_PCI_MEM
comma
id|PCIMEM_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|PCICFG0_BASE
comma
id|DC21285_PCI_TYPE_0_CONFIG
comma
id|PCICFG0_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|PCICFG1_BASE
comma
id|DC21285_PCI_TYPE_1_CONFIG
comma
id|PCICFG1_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|PCIIACK_BASE
comma
id|DC21285_PCI_IACK
comma
id|PCIIACK_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|PCIO_BASE
comma
id|DC21285_PCI_IO
comma
id|PCIO_SIZE
comma
id|MT_DEVICE
)brace
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; * The CO-ebsa285 mapping.&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|co285_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
macro_line|#ifdef CONFIG_ARCH_CO285
(brace
id|PCIO_BASE
comma
id|DC21285_PCI_IO
comma
id|PCIO_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|PCIMEM_BASE
comma
id|DC21285_PCI_MEM
comma
id|PCIMEM_SIZE
comma
id|MT_DEVICE
)brace
macro_line|#endif
)brace
suffix:semicolon
DECL|function|footbridge_map_io
r_void
id|__init
id|footbridge_map_io
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Set up the common mapping first; we need this to&n;&t; * determine whether we&squot;re in host mode or not.&n;&t; */
id|iotable_init
c_func
(paren
id|fb_common_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|fb_common_io_desc
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now, work out what we&squot;ve got to map in addition on this&n;&t; * platform.&n;&t; */
r_if
c_cond
(paren
id|machine_is_co285
c_func
(paren
)paren
)paren
id|iotable_init
c_func
(paren
id|co285_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|co285_io_desc
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|footbridge_cfn_mode
c_func
(paren
)paren
)paren
id|iotable_init
c_func
(paren
id|ebsa285_host_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|ebsa285_host_io_desc
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_FOOTBRIDGE_ADDIN
multiline_comment|/*&n; * These two functions convert virtual addresses to PCI addresses and PCI&n; * addresses to virtual addresses.  Note that it is only legal to use these&n; * on memory obtained via get_zeroed_page or kmalloc.&n; */
DECL|function|__virt_to_bus
r_int
r_int
id|__virt_to_bus
c_func
(paren
r_int
r_int
id|res
)paren
(brace
id|WARN_ON
c_func
(paren
id|res
OL
id|PAGE_OFFSET
op_logical_or
id|res
op_ge
(paren
r_int
r_int
)paren
id|high_memory
)paren
suffix:semicolon
r_return
(paren
id|res
op_minus
id|PAGE_OFFSET
)paren
op_plus
(paren
op_star
id|CSR_PCISDRAMBASE
op_amp
l_int|0xfffffff0
)paren
suffix:semicolon
)brace
DECL|variable|__virt_to_bus
id|EXPORT_SYMBOL
c_func
(paren
id|__virt_to_bus
)paren
suffix:semicolon
DECL|function|__bus_to_virt
r_int
r_int
id|__bus_to_virt
c_func
(paren
r_int
r_int
id|res
)paren
(brace
id|res
op_sub_assign
(paren
op_star
id|CSR_PCISDRAMBASE
op_amp
l_int|0xfffffff0
)paren
suffix:semicolon
id|res
op_add_assign
id|PAGE_OFFSET
suffix:semicolon
id|WARN_ON
c_func
(paren
id|res
OL
id|PAGE_OFFSET
op_logical_or
id|res
op_ge
(paren
r_int
r_int
)paren
id|high_memory
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|variable|__bus_to_virt
id|EXPORT_SYMBOL
c_func
(paren
id|__bus_to_virt
)paren
suffix:semicolon
macro_line|#endif
eof
