multiline_comment|/*  &n; * Miscellaneous definitions used to initialise the interrupt vector table&n; * with the machine-specific interrupt routines.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997 by Paul M. Antoine.&n; * reworked 1998 by Harald Koerfgen.&n; */
macro_line|#ifndef __ASM_DEC_INTERRUPTS_H 
DECL|macro|__ASM_DEC_INTERRUPTS_H
mdefine_line|#define __ASM_DEC_INTERRUPTS_H 
multiline_comment|/*&n; * DECstation Interrupts&n; */
multiline_comment|/*&n; * This list reflects the priority of the Interrupts.&n; * Exception: on kmins we have to handle Memory Error &n; * Interrupts before the TC Interrupts.&n; */
DECL|macro|CLOCK
mdefine_line|#define CLOCK &t;0
DECL|macro|SCSI_DMA_INT
mdefine_line|#define SCSI_DMA_INT &t;1
DECL|macro|SCSI_INT
mdefine_line|#define SCSI_INT&t;2
DECL|macro|ETHER
mdefine_line|#define ETHER&t;&t;3
DECL|macro|SERIAL
mdefine_line|#define SERIAL&t;&t;4
DECL|macro|TC0
mdefine_line|#define TC0&t;&t;5
DECL|macro|TC1
mdefine_line|#define TC1&t;&t;6
DECL|macro|TC2
mdefine_line|#define TC2&t;&t;7
DECL|macro|MEMORY
mdefine_line|#define MEMORY&t;&t;8
DECL|macro|FPU
mdefine_line|#define FPU&t;&t;9
DECL|macro|HALT
mdefine_line|#define HALT&t;&t;10
DECL|macro|NR_INTS
mdefine_line|#define NR_INTS&t;11
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Data structure to hide the differences between the DECstation Interrupts&n; *&n; * If asic_mask == NULL, the interrupt is directly handled by the CPU.&n; * Otherwise this Interrupt is handled the IRQ Controller.&n; */
r_typedef
r_struct
(brace
DECL|member|cpu_mask
r_int
r_int
id|cpu_mask
suffix:semicolon
multiline_comment|/* checking and enabling interrupts in CP0&t;*/
DECL|member|iemask
r_int
r_int
id|iemask
suffix:semicolon
multiline_comment|/* enabling interrupts in IRQ Controller&t;*/
DECL|typedef|decint_t
)brace
id|decint_t
suffix:semicolon
r_extern
r_volatile
r_int
r_int
op_star
id|isr
suffix:semicolon
multiline_comment|/* address of the interrupt status register  */
r_extern
r_volatile
r_int
r_int
op_star
id|imr
suffix:semicolon
multiline_comment|/* address of the interrupt mask register    */
r_extern
id|decint_t
id|dec_interrupt
(braket
id|NR_INTS
)braket
suffix:semicolon
multiline_comment|/*&n; * Interrupt table structure to hide differences between different&n; * systems such.&n; */
r_extern
r_void
op_star
id|cpu_ivec_tbl
(braket
l_int|8
)braket
suffix:semicolon
r_extern
r_int
id|cpu_mask_tbl
(braket
l_int|8
)braket
suffix:semicolon
r_extern
r_int
id|cpu_irq_nr
(braket
l_int|8
)braket
suffix:semicolon
r_extern
r_int
id|asic_irq_nr
(braket
l_int|32
)braket
suffix:semicolon
r_extern
r_int
id|asic_mask_tbl
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/*&n; * Common interrupt routine prototypes for all DECStations&n; */
r_extern
r_void
id|dec_intr_unimplemented
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dec_intr_fpu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dec_intr_rtc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|kn02_io_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|kn02xa_io_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|kn03_io_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|asic_intr_unimplemented
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif 
eof
