multiline_comment|/*&n; * include/asm-arm/arch-ixp4xx/ixdp425.h&n; *&n; * IXDP425 platform specific definitions&n; *&n; * Author: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * Copyright 2004 (c) MontaVista, Software, Inc. &n; * &n; * This file is licensed under  the terms of the GNU General Public &n; * License version 2. This program is licensed &quot;as is&quot; without any &n; * warranty of any kind, whether express or implied.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H__
macro_line|#error &quot;Do not include this directly, instead #include &lt;asm/hardware.h&gt;&quot;
macro_line|#endif
DECL|macro|IXDP425_FLASH_BASE
mdefine_line|#define&t;IXDP425_FLASH_BASE&t;IXP4XX_EXP_BUS_CS0_BASE_PHYS
DECL|macro|IXDP425_FLASH_SIZE
mdefine_line|#define&t;IXDP425_FLASH_SIZE&t;IXP4XX_EXP_BUS_CSX_REGION_SIZE
DECL|macro|IXDP425_SDA_PIN
mdefine_line|#define&t;IXDP425_SDA_PIN&t;&t;7
DECL|macro|IXDP425_SCL_PIN
mdefine_line|#define&t;IXDP425_SCL_PIN&t;&t;6
multiline_comment|/*&n; * IXDP425 PCI IRQs&n; */
DECL|macro|IXDP425_PCI_MAX_DEV
mdefine_line|#define IXDP425_PCI_MAX_DEV&t;4
DECL|macro|IXDP425_PCI_IRQ_LINES
mdefine_line|#define IXDP425_PCI_IRQ_LINES&t;4
multiline_comment|/* PCI controller GPIO to IRQ pin mappings */
DECL|macro|IXDP425_PCI_INTA_PIN
mdefine_line|#define IXDP425_PCI_INTA_PIN&t;11
DECL|macro|IXDP425_PCI_INTB_PIN
mdefine_line|#define IXDP425_PCI_INTB_PIN&t;10
DECL|macro|IXDP425_PCI_INTC_PIN
mdefine_line|#define&t;IXDP425_PCI_INTC_PIN&t;9
DECL|macro|IXDP425_PCI_INTD_PIN
mdefine_line|#define&t;IXDP425_PCI_INTD_PIN&t;8
eof
