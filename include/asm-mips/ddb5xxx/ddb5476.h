multiline_comment|/*&n; * header file specific for ddb5476&n; *&n; * Copyright (C) 2001 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
multiline_comment|/*&n; *  Memory map (physical address)&n; *&n; *  Note most of the following address must be properly aligned by the&n; *  corresponding size.  For example, if PCI_IO_SIZE is 16MB, then&n; *  PCI_IO_BASE must be aligned along 16MB boundary.&n; */
DECL|macro|DDB_SDRAM_BASE
mdefine_line|#define DDB_SDRAM_BASE&t;&t;0x00000000
DECL|macro|DDB_SDRAM_SIZE
mdefine_line|#define DDB_SDRAM_SIZE&t;&t;0x04000000      /* 64MB */
DECL|macro|DDB_DCS3_BASE
mdefine_line|#define&t;DDB_DCS3_BASE&t;&t;0x04000000&t;/* flash 1 */
DECL|macro|DDB_DCS3_SIZE
mdefine_line|#define&t;DDB_DCS3_SIZE&t;&t;0x01000000&t;/* 16MB */
DECL|macro|DDB_DCS2_BASE
mdefine_line|#define&t;DDB_DCS2_BASE&t;&t;0x05000000&t;/* flash 2 */
DECL|macro|DDB_DCS2_SIZE
mdefine_line|#define&t;DDB_DCS2_SIZE&t;&t;0x01000000&t;/* 16MB */
DECL|macro|DDB_PCI_IO_BASE
mdefine_line|#define DDB_PCI_IO_BASE&t;&t;0x06000000
DECL|macro|DDB_PCI_IO_SIZE
mdefine_line|#define DDB_PCI_IO_SIZE&t;&t;0x02000000      /* 32 MB */
DECL|macro|DDB_PCI_MEM_BASE
mdefine_line|#define&t;DDB_PCI_MEM_BASE&t;0x08000000
DECL|macro|DDB_PCI_MEM_SIZE
mdefine_line|#define&t;DDB_PCI_MEM_SIZE&t;0x08000000&t;/* 128 MB */
DECL|macro|DDB_DCS5_BASE
mdefine_line|#define&t;DDB_DCS5_BASE&t;&t;0x13000000&t;/* DDB status regs */
DECL|macro|DDB_DCS5_SIZE
mdefine_line|#define&t;DDB_DCS5_SIZE&t;&t;0x00200000&t;/* 2MB, 8-bit */
DECL|macro|DDB_DCS4_BASE
mdefine_line|#define&t;DDB_DCS4_BASE&t;&t;0x14000000&t;/* DDB control regs */
DECL|macro|DDB_DCS4_SIZE
mdefine_line|#define&t;DDB_DCS4_SIZE&t;&t;0x00200000&t;/* 2MB, 8-bit */
DECL|macro|DDB_INTCS_BASE
mdefine_line|#define DDB_INTCS_BASE&t;&t;0x1fa00000      /* VRC5476 control regs */
DECL|macro|DDB_INTCS_SIZE
mdefine_line|#define DDB_INTCS_SIZE&t;&t;0x00200000      /* 2MB */
DECL|macro|DDB_BOOTCS_BASE
mdefine_line|#define DDB_BOOTCS_BASE         0x1fc00000      /* Boot ROM / EPROM /Flash */
DECL|macro|DDB_BOOTCS_SIZE
mdefine_line|#define DDB_BOOTCS_SIZE         0x00200000      /* 2 MB - doc says 4MB */
multiline_comment|/* aliases */
DECL|macro|DDB_PCI_CONFIG_BASE
mdefine_line|#define&t;DDB_PCI_CONFIG_BASE&t;DDB_PCI_MEM_BASE
DECL|macro|DDB_PCI_CONFIG_SIZE
mdefine_line|#define&t;DDB_PCI_CONFIG_SIZE&t;DDB_PCI_MEM_SIZE
multiline_comment|/* PCI intr ack share PCIW0 with PCI IO */
DECL|macro|DDB_PCI_IACK_BASE
mdefine_line|#define&t;DDB_PCI_IACK_BASE&t;DDB_PCI_IO_BASE
multiline_comment|/*&n; * Interrupt mapping&n; *&n; * We have three interrupt controllers:&n; *&n; *   . CPU itself - 8 sources&n; *   . i8259 - 16 sources&n; *   . vrc5476 - 16 sources&n; *&n; *  They connected as follows:&n; *    all vrc5476 interrupts are routed to cpu IP2 (by software setting)&n; *    all i2869 are routed to INTC in vrc5476 (by hardware connection)&n; *&n; *  All VRC5476 PCI interrupts are level-triggered (no ack needed).&n; *  All PCI irq but INTC are active low.&n; */
multiline_comment|/*&n; * irq number block assignment&n; */
DECL|macro|NUM_CPU_IRQ
mdefine_line|#define&t;NUM_CPU_IRQ&t;&t;8
DECL|macro|NUM_I8259_IRQ
mdefine_line|#define&t;NUM_I8259_IRQ&t;&t;16
DECL|macro|NUM_VRC5476_IRQ
mdefine_line|#define&t;NUM_VRC5476_IRQ&t;&t;16
DECL|macro|DDB_IRQ_BASE
mdefine_line|#define&t;DDB_IRQ_BASE&t;&t;0
DECL|macro|I8259_IRQ_BASE
mdefine_line|#define&t;I8259_IRQ_BASE&t;&t;DDB_IRQ_BASE
DECL|macro|VRC5476_IRQ_BASE
mdefine_line|#define&t;VRC5476_IRQ_BASE&t;(I8259_IRQ_BASE + NUM_I8259_IRQ)
DECL|macro|CPU_IRQ_BASE
mdefine_line|#define&t;CPU_IRQ_BASE&t;&t;(VRC5476_IRQ_BASE + NUM_VRC5476_IRQ)
multiline_comment|/*&n; * vrc5476 irq defs, see page 52-64 of Vrc5074 system controller manual&n; */
DECL|macro|VRC5476_IRQ_CPCE
mdefine_line|#define VRC5476_IRQ_CPCE&t;0&t;/* cpu parity error */
DECL|macro|VRC5476_IRQ_CNTD
mdefine_line|#define VRC5476_IRQ_CNTD&t;1&t;/* cpu no target */
DECL|macro|VRC5476_IRQ_MCE
mdefine_line|#define VRC5476_IRQ_MCE&t;&t;2&t;/* memory check error */
DECL|macro|VRC5476_IRQ_DMA
mdefine_line|#define VRC5476_IRQ_DMA&t;&t;3&t;/* DMA */
DECL|macro|VRC5476_IRQ_UART
mdefine_line|#define VRC5476_IRQ_UART&t;4&t;/* vrc5476 builtin UART, not used */
DECL|macro|VRC5476_IRQ_WDOG
mdefine_line|#define VRC5476_IRQ_WDOG&t;5&t;/* watchdog timer */
DECL|macro|VRC5476_IRQ_GPT
mdefine_line|#define VRC5476_IRQ_GPT&t;&t;6&t;/* general purpose timer */
DECL|macro|VRC5476_IRQ_LBRT
mdefine_line|#define VRC5476_IRQ_LBRT&t;7&t;/* local bus read timeout */
DECL|macro|VRC5476_IRQ_INTA
mdefine_line|#define VRC5476_IRQ_INTA&t;8&t;/* PCI INT #A */
DECL|macro|VRC5476_IRQ_INTB
mdefine_line|#define VRC5476_IRQ_INTB&t;9&t;/* PCI INT #B */
DECL|macro|VRC5476_IRQ_INTC
mdefine_line|#define VRC5476_IRQ_INTC&t;10&t;/* PCI INT #C */
DECL|macro|VRC5476_IRQ_INTD
mdefine_line|#define VRC5476_IRQ_INTD&t;11&t;/* PCI INT #D */
DECL|macro|VRC5476_IRQ_INTE
mdefine_line|#define VRC5476_IRQ_INTE&t;12&t;/* PCI INT #E */
DECL|macro|VRC5476_IRQ_RESERVED_13
mdefine_line|#define VRC5476_IRQ_RESERVED_13&t;13&t;/* reserved  */
DECL|macro|VRC5476_IRQ_PCIS
mdefine_line|#define VRC5476_IRQ_PCIS&t;14&t;/* PCI SERR #  */
DECL|macro|VRC5476_IRQ_PCI
mdefine_line|#define VRC5476_IRQ_PCI&t;&t;15&t;/* PCI internal error */
multiline_comment|/*&n; * i2859 irq assignment&n; */
DECL|macro|I8259_IRQ_RESERVED_0
mdefine_line|#define I8259_IRQ_RESERVED_0&t;0
DECL|macro|I8259_IRQ_KEYBOARD
mdefine_line|#define I8259_IRQ_KEYBOARD&t;1&t;/* M1543 default */
DECL|macro|I8259_IRQ_CASCADE
mdefine_line|#define I8259_IRQ_CASCADE&t;2
DECL|macro|I8259_IRQ_UART_B
mdefine_line|#define I8259_IRQ_UART_B&t;3&t;/* M1543 default, may conflict with RTC according to schematic diagram  */
DECL|macro|I8259_IRQ_UART_A
mdefine_line|#define I8259_IRQ_UART_A&t;4&t;/* M1543 default */
DECL|macro|I8259_IRQ_PARALLEL
mdefine_line|#define I8259_IRQ_PARALLEL&t;5&t;/* M1543 default */
DECL|macro|I8259_IRQ_RESERVED_6
mdefine_line|#define I8259_IRQ_RESERVED_6&t;6
DECL|macro|I8259_IRQ_RESERVED_7
mdefine_line|#define I8259_IRQ_RESERVED_7&t;7
DECL|macro|I8259_IRQ_RTC
mdefine_line|#define I8259_IRQ_RTC&t;&t;8&t;/* who set this? */
DECL|macro|I8259_IRQ_USB
mdefine_line|#define I8259_IRQ_USB&t;&t;9&t;/* ddb_setup */
DECL|macro|I8259_IRQ_PMU
mdefine_line|#define I8259_IRQ_PMU&t;&t;10&t;/* ddb_setup */
DECL|macro|I8259_IRQ_RESERVED_11
mdefine_line|#define I8259_IRQ_RESERVED_11&t;11
DECL|macro|I8259_IRQ_RESERVED_12
mdefine_line|#define I8259_IRQ_RESERVED_12&t;12&t;/* m1543_irq_setup */
DECL|macro|I8259_IRQ_RESERVED_13
mdefine_line|#define I8259_IRQ_RESERVED_13&t;13
DECL|macro|I8259_IRQ_HDC1
mdefine_line|#define I8259_IRQ_HDC1&t;&t;14&t;/* default and ddb_setup */
DECL|macro|I8259_IRQ_HDC2
mdefine_line|#define I8259_IRQ_HDC2&t;&t;15&t;/* default */
multiline_comment|/*&n; * misc&n; */
DECL|macro|VRC5476_I8259_CASCADE
mdefine_line|#define&t;VRC5476_I8259_CASCADE&t;VRC5476_IRQ_INTC
DECL|macro|CPU_VRC5476_CASCADE
mdefine_line|#define&t;CPU_VRC5476_CASCADE&t;2
DECL|macro|is_i8259_irq
mdefine_line|#define is_i8259_irq(irq)       ((irq) &lt; NUM_I8259_IRQ)
DECL|macro|nile4_to_irq
mdefine_line|#define nile4_to_irq(n)         ((n)+NUM_I8259_IRQ)
DECL|macro|irq_to_nile4
mdefine_line|#define irq_to_nile4(n)         ((n)-NUM_I8259_IRQ)
multiline_comment|/*&n; * low-level irq functions&n; */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|nile4_map_irq
c_func
(paren
r_int
id|nile4_irq
comma
r_int
id|cpu_irq
)paren
suffix:semicolon
r_extern
r_void
id|nile4_map_irq_all
c_func
(paren
r_int
id|cpu_irq
)paren
suffix:semicolon
r_extern
r_void
id|nile4_enable_irq
c_func
(paren
r_int
id|nile4_irq
)paren
suffix:semicolon
r_extern
r_void
id|nile4_disable_irq
c_func
(paren
r_int
id|nile4_irq
)paren
suffix:semicolon
r_extern
r_void
id|nile4_disable_irq_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|u16
id|nile4_get_irq_stat
c_func
(paren
r_int
id|cpu_irq
)paren
suffix:semicolon
r_extern
r_void
id|nile4_enable_irq_output
c_func
(paren
r_int
id|cpu_irq
)paren
suffix:semicolon
r_extern
r_void
id|nile4_disable_irq_output
c_func
(paren
r_int
id|cpu_irq
)paren
suffix:semicolon
r_extern
r_void
id|nile4_set_pci_irq_polarity
c_func
(paren
r_int
id|pci_irq
comma
r_int
id|high
)paren
suffix:semicolon
r_extern
r_void
id|nile4_set_pci_irq_level_or_edge
c_func
(paren
r_int
id|pci_irq
comma
r_int
id|level
)paren
suffix:semicolon
r_extern
r_void
id|nile4_clear_irq
c_func
(paren
r_int
id|nile4_irq
)paren
suffix:semicolon
r_extern
r_void
id|nile4_clear_irq_mask
c_func
(paren
id|u32
id|mask
)paren
suffix:semicolon
r_extern
id|u8
id|nile4_i8259_iack
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|nile4_dump_irq_status
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Debug */
macro_line|#endif /* !__ASSEMBLY__ */
eof
