multiline_comment|/*&n; * arch/arm/mach-ixp4xx/ixdp425-pci.c &n; *&n; * IXDP425 board-level PCI initialization&n; *&n; * Copyright (C) 2002 Intel Corporation.&n; * Copyright (C) 2003-2004 MontaVista Software, Inc.&n; *&n; * Maintainer: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/mach/pci.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
DECL|function|ixdp425_pci_preinit
r_void
id|__init
id|ixdp425_pci_preinit
c_func
(paren
r_void
)paren
(brace
id|gpio_line_config
c_func
(paren
id|IXDP425_PCI_INTA_PIN
comma
id|IXP4XX_GPIO_IN
op_or
id|IXP4XX_GPIO_ACTIVE_LOW
)paren
suffix:semicolon
id|gpio_line_config
c_func
(paren
id|IXDP425_PCI_INTB_PIN
comma
id|IXP4XX_GPIO_IN
op_or
id|IXP4XX_GPIO_ACTIVE_LOW
)paren
suffix:semicolon
id|gpio_line_config
c_func
(paren
id|IXDP425_PCI_INTC_PIN
comma
id|IXP4XX_GPIO_IN
op_or
id|IXP4XX_GPIO_ACTIVE_LOW
)paren
suffix:semicolon
id|gpio_line_config
c_func
(paren
id|IXDP425_PCI_INTD_PIN
comma
id|IXP4XX_GPIO_IN
op_or
id|IXP4XX_GPIO_ACTIVE_LOW
)paren
suffix:semicolon
id|gpio_line_isr_clear
c_func
(paren
id|IXDP425_PCI_INTA_PIN
)paren
suffix:semicolon
id|gpio_line_isr_clear
c_func
(paren
id|IXDP425_PCI_INTB_PIN
)paren
suffix:semicolon
id|gpio_line_isr_clear
c_func
(paren
id|IXDP425_PCI_INTC_PIN
)paren
suffix:semicolon
id|gpio_line_isr_clear
c_func
(paren
id|IXDP425_PCI_INTD_PIN
)paren
suffix:semicolon
id|ixp4xx_pci_preinit
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|ixdp425_map_irq
r_static
r_int
id|__init
id|ixdp425_map_irq
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
r_int
id|pci_irq_table
(braket
id|IXDP425_PCI_IRQ_LINES
)braket
op_assign
(brace
id|IRQ_IXDP425_PCI_INTA
comma
id|IRQ_IXDP425_PCI_INTB
comma
id|IRQ_IXDP425_PCI_INTC
comma
id|IRQ_IXDP425_PCI_INTD
)brace
suffix:semicolon
r_int
id|irq
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_ge
l_int|1
op_logical_and
id|slot
op_le
id|IXDP425_PCI_MAX_DEV
op_logical_and
id|pin
op_ge
l_int|1
op_logical_and
id|pin
op_le
id|IXDP425_PCI_IRQ_LINES
)paren
(brace
id|irq
op_assign
id|pci_irq_table
(braket
(paren
id|slot
op_plus
id|pin
op_minus
l_int|2
)paren
op_mod
l_int|4
)braket
suffix:semicolon
)brace
r_return
id|irq
suffix:semicolon
)brace
DECL|variable|__initdata
r_struct
id|hw_pci
id|ixdp425_pci
id|__initdata
op_assign
(brace
dot
id|nr_controllers
op_assign
l_int|1
comma
dot
id|preinit
op_assign
id|ixdp425_pci_preinit
comma
dot
id|swizzle
op_assign
id|pci_std_swizzle
comma
dot
id|setup
op_assign
id|ixp4xx_setup
comma
dot
id|scan
op_assign
id|ixp4xx_scan_bus
comma
dot
id|map_irq
op_assign
id|ixdp425_map_irq
comma
)brace
suffix:semicolon
DECL|function|ixdp425_pci_init
r_int
id|__init
id|ixdp425_pci_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_ixdp425
c_func
(paren
)paren
op_logical_or
id|machine_is_ixcdp1100
c_func
(paren
)paren
op_logical_or
id|machine_is_avila
c_func
(paren
)paren
op_logical_or
id|machine_is_ixdp465
c_func
(paren
)paren
)paren
id|pci_common_init
c_func
(paren
op_amp
id|ixdp425_pci
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ixdp425_pci_init
id|subsys_initcall
c_func
(paren
id|ixdp425_pci_init
)paren
suffix:semicolon
eof
