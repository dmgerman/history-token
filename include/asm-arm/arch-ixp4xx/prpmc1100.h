multiline_comment|/*&n; * include/asm-arm/arch-ixp4xx/prpmc1100.h&n; *&n; * Motorolla PrPMC1100 platform specific definitions&n; *&n; * Author: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * Copyright 2004 (c) MontaVista, Software, Inc. &n; * &n; * This file is licensed under  the terms of the GNU General Public &n; * License version 2. This program is licensed &quot;as is&quot; without any &n; * warranty of any kind, whether express or implied.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H__
macro_line|#error &quot;Do not include this directly, instead #include &lt;asm/hardware.h&gt;&quot;
macro_line|#endif
DECL|macro|PRPMC1100_FLASH_BASE
mdefine_line|#define&t;PRPMC1100_FLASH_BASE&t;IXP4XX_EXP_BUS_CS0_BASE_PHYS
DECL|macro|PRPMC1100_FLASH_SIZE
mdefine_line|#define&t;PRPMC1100_FLASH_SIZE&t;IXP4XX_EXP_BUS_CSX_REGION_SIZE
DECL|macro|PRPMC1100_PCI_MIN_DEVID
mdefine_line|#define&t;PRPMC1100_PCI_MIN_DEVID&t;10
DECL|macro|PRPMC1100_PCI_MAX_DEVID
mdefine_line|#define&t;PRPMC1100_PCI_MAX_DEVID&t;16
DECL|macro|PRPMC1100_PCI_IRQ_LINES
mdefine_line|#define&t;PRPMC1100_PCI_IRQ_LINES&t;4
multiline_comment|/* PCI controller GPIO to IRQ pin mappings */
DECL|macro|PRPMC1100_PCI_INTA_PIN
mdefine_line|#define PRPMC1100_PCI_INTA_PIN&t;11
DECL|macro|PRPMC1100_PCI_INTB_PIN
mdefine_line|#define PRPMC1100_PCI_INTB_PIN&t;10
DECL|macro|PRPMC1100_PCI_INTC_PIN
mdefine_line|#define&t;PRPMC1100_PCI_INTC_PIN&t;9
DECL|macro|PRPMC1100_PCI_INTD_PIN
mdefine_line|#define&t;PRPMC1100_PCI_INTD_PIN&t;8
eof
