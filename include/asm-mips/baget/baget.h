multiline_comment|/* $Id$&n; * baget.h: Definitions specific to Baget/MIPS machines.&n; *&n; * Copyright (C) 1998 Gleb Raiko &amp; Vladimir Roganov&n; */
macro_line|#ifndef _MIPS_BAGET_H
DECL|macro|_MIPS_BAGET_H
mdefine_line|#define _MIPS_BAGET_H
macro_line|#include &quot;vic.h&quot;
macro_line|#include &quot;vac.h&quot;
DECL|macro|VIC_BASE
mdefine_line|#define VIC_BASE         0xBFFC0000 
DECL|macro|VAC_BASE
mdefine_line|#define VAC_BASE         0xBFFD0000
multiline_comment|/* Baget interrupt registers and their sizes */
DECL|struct|baget_int_reg
r_struct
id|baget_int_reg
(brace
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* in bytes */
)brace
suffix:semicolon
DECL|macro|BAGET_INT_NONE
mdefine_line|#define BAGET_INT_NONE   {0,0}
DECL|macro|BAGET_INT0_ACK
mdefine_line|#define BAGET_INT0_ACK   {0xbffa0003,1}
DECL|macro|BAGET_INT1_ACK
mdefine_line|#define BAGET_INT1_ACK   {0xbffa0008,4}
DECL|macro|BAGET_INT5_ACK
mdefine_line|#define BAGET_INT5_ACK   {0xbff00000,1}
DECL|macro|BAGET_WRERR_ACK
mdefine_line|#define BAGET_WRERR_ACK  ((volatile char*)0xbff00000)
multiline_comment|/* Baget address spaces */
DECL|macro|BAGET_A24M_BASE
mdefine_line|#define BAGET_A24M_BASE       0xFC000000      /* VME-master A24 base address  */
DECL|macro|BAGET_A24S_BASE
mdefine_line|#define BAGET_A24S_BASE       0x00000000      /* VME-slave A24 base address   */
DECL|macro|BAGET_A24S_MASK
mdefine_line|#define BAGET_A24S_MASK       0x00c00000      /* VME-slave A24 address mask   */
DECL|macro|BAGET_GSW_BASE
mdefine_line|#define BAGET_GSW_BASE        0xf000          /* global switches address base */
DECL|macro|BAGET_MSW_BASE
mdefine_line|#define BAGET_MSW_BASE(P) (0xe000+(P)*0x100)  /* module switches address base */
DECL|macro|BAGET_LED_BASE
mdefine_line|#define BAGET_LED_BASE  ((volatile short *)(0xbffd0000 + 0x00001800))
DECL|macro|BAGET_PIL_NR
mdefine_line|#define BAGET_PIL_NR            8
DECL|macro|BAGET_IRQ_NR
mdefine_line|#define BAGET_IRQ_NR            NR_IRQS /* 64 */
DECL|macro|BAGET_IRQ_MASK
mdefine_line|#define BAGET_IRQ_MASK(x)       ((NR_IRQS-1) &amp; (x))
DECL|macro|BAGET_FPU_IRQ
mdefine_line|#define BAGET_FPU_IRQ           0x26
DECL|macro|BAGET_VIC_TIMER_IRQ
mdefine_line|#define BAGET_VIC_TIMER_IRQ     0x32 
DECL|macro|BAGET_VAC_TIMER_IRQ
mdefine_line|#define BAGET_VAC_TIMER_IRQ     0x36 
DECL|macro|BAGET_BSM_IRQ
mdefine_line|#define BAGET_BSM_IRQ           0x3C
DECL|macro|BAGET_LANCE_MEM_BASE
mdefine_line|#define BAGET_LANCE_MEM_BASE    0xfcf10000
DECL|macro|BAGET_LANCE_MEM_SIZE
mdefine_line|#define BAGET_LANCE_MEM_SIZE    0x10000
DECL|macro|BAGET_LANCE_IO_BASE
mdefine_line|#define BAGET_LANCE_IO_BASE     0xbffeff00
DECL|macro|BALO_OFFSET
mdefine_line|#define BALO_OFFSET     0x400000 /* sync with ld.script.balo  */
DECL|macro|BALO_SIZE
mdefine_line|#define BALO_SIZE       0x200000 /* sync with image segs size */
multiline_comment|/* move it to the right place, somehere in include/asm */
DECL|macro|CAUSE_DBE
mdefine_line|#define CAUSE_DBE       0x1C
DECL|macro|CAUSE_MASK
mdefine_line|#define CAUSE_MASK      0x7C
multiline_comment|/* Simple debug fascilities */
r_extern
r_void
id|outc
c_func
(paren
r_char
)paren
suffix:semicolon
r_extern
r_void
id|outs
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|baget_write
c_func
(paren
r_char
op_star
id|s
comma
r_int
id|l
)paren
suffix:semicolon
r_extern
r_int
id|baget_printk
c_func
(paren
r_const
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|balo_printf
c_func
(paren
r_char
op_star
id|f
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|balo_hungup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* !(_MIPS_BAGET_H) */
eof
