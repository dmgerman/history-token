multiline_comment|/*&n; *  include/asm-mips/ddb5074.h -- NEC DDB Vrc-5074 definitions&n; *&n; *  Copyright (C) 2000 Geert Uytterhoeven &lt;geert@sonycom.com&gt;&n; *                     Sony Software Development Center Europe (SDCE), Brussels&n; */
macro_line|#ifndef _ASM_DDB5XXX_DDB5074_H
DECL|macro|_ASM_DDB5XXX_DDB5074_H
mdefine_line|#define _ASM_DDB5XXX_DDB5074_H
macro_line|#include &lt;asm/nile4.h&gt;
DECL|macro|DDB_SDRAM_SIZE
mdefine_line|#define DDB_SDRAM_SIZE      0x04000000      /* 64MB */
DECL|macro|DDB_PCI_IO_BASE
mdefine_line|#define DDB_PCI_IO_BASE     0x06000000
DECL|macro|DDB_PCI_IO_SIZE
mdefine_line|#define DDB_PCI_IO_SIZE     0x02000000      /* 32 MB */
DECL|macro|DDB_PCI_MEM_BASE
mdefine_line|#define DDB_PCI_MEM_BASE    0x08000000
DECL|macro|DDB_PCI_MEM_SIZE
mdefine_line|#define DDB_PCI_MEM_SIZE    0x08000000  /* 128 MB */
DECL|macro|DDB_PCI_CONFIG_BASE
mdefine_line|#define DDB_PCI_CONFIG_BASE DDB_PCI_MEM_BASE
DECL|macro|DDB_PCI_CONFIG_SIZE
mdefine_line|#define DDB_PCI_CONFIG_SIZE DDB_PCI_MEM_SIZE
DECL|macro|NILE4_PCI_IO_BASE
mdefine_line|#define NILE4_PCI_IO_BASE   0xa6000000
DECL|macro|NILE4_PCI_MEM_BASE
mdefine_line|#define NILE4_PCI_MEM_BASE  0xa8000000
DECL|macro|NILE4_PCI_CFG_BASE
mdefine_line|#define NILE4_PCI_CFG_BASE  NILE4_PCI_MEM_BASE
DECL|macro|DDB_PCI_IACK_BASE
mdefine_line|#define DDB_PCI_IACK_BASE NILE4_PCI_IO_BASE
DECL|macro|NILE4_IRQ_BASE
mdefine_line|#define NILE4_IRQ_BASE NUM_I8259_INTERRUPTS
DECL|macro|CPU_IRQ_BASE
mdefine_line|#define CPU_IRQ_BASE (NUM_NILE4_INTERRUPTS + NILE4_IRQ_BASE)
DECL|macro|CPU_NILE4_CASCADE
mdefine_line|#define CPU_NILE4_CASCADE 2
r_extern
r_void
id|ddb5074_led_hex
c_func
(paren
r_int
id|hex
)paren
suffix:semicolon
r_extern
r_void
id|ddb5074_led_d2
c_func
(paren
r_int
id|on
)paren
suffix:semicolon
r_extern
r_void
id|ddb5074_led_d3
c_func
(paren
r_int
id|on
)paren
suffix:semicolon
r_extern
r_void
id|nile4_irq_setup
c_func
(paren
id|u32
id|base
)paren
suffix:semicolon
macro_line|#endif
eof
