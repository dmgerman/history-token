multiline_comment|/*&n; *  This is a direct copy of the ev96100.h file, with a global&n; * search and replace.  The numbers are the same.&n; *&n; *  The reason I&squot;m duplicating this is so that the 64120/96100&n; * defines won&squot;t be confusing in the source code.&n; */
macro_line|#ifndef __ASM_GALILEO_BOARDS_MIPS_EV64120_H
DECL|macro|__ASM_GALILEO_BOARDS_MIPS_EV64120_H
mdefine_line|#define __ASM_GALILEO_BOARDS_MIPS_EV64120_H
multiline_comment|/*&n; *   GT64120 config space base address&n; */
r_extern
r_int
r_int
id|gt64120_base
suffix:semicolon
DECL|macro|GT64120_BASE
mdefine_line|#define GT64120_BASE&t;(gt64120_base)
multiline_comment|/*&n; *   PCI Bus allocation&n; */
DECL|macro|GT_PCI_MEM_BASE
mdefine_line|#define GT_PCI_MEM_BASE&t;0x12000000UL
DECL|macro|GT_PCI_MEM_SIZE
mdefine_line|#define GT_PCI_MEM_SIZE&t;0x02000000UL
DECL|macro|GT_PCI_IO_BASE
mdefine_line|#define GT_PCI_IO_BASE&t;0x10000000UL
DECL|macro|GT_PCI_IO_SIZE
mdefine_line|#define GT_PCI_IO_SIZE&t;0x02000000UL
DECL|macro|GT_ISA_IO_BASE
mdefine_line|#define GT_ISA_IO_BASE&t;PCI_IO_BASE
multiline_comment|/*&n; *   Duart I/O ports.&n; */
DECL|macro|EV64120_COM1_BASE_ADDR
mdefine_line|#define EV64120_COM1_BASE_ADDR&t;(0x1d000000 + 0x20)
DECL|macro|EV64120_COM2_BASE_ADDR
mdefine_line|#define EV64120_COM2_BASE_ADDR&t;(0x1d000000 + 0x00)
multiline_comment|/*&n; *   EV64120 interrupt controller register base.&n; */
DECL|macro|EV64120_ICTRL_REGS_BASE
mdefine_line|#define EV64120_ICTRL_REGS_BASE&t;(KSEG1ADDR(0x1f000000))
multiline_comment|/*&n; *   EV64120 UART register base.&n; */
DECL|macro|EV64120_UART0_REGS_BASE
mdefine_line|#define EV64120_UART0_REGS_BASE&t;(KSEG1ADDR(EV64120_COM1_BASE_ADDR))
DECL|macro|EV64120_UART1_REGS_BASE
mdefine_line|#define EV64120_UART1_REGS_BASE&t;(KSEG1ADDR(EV64120_COM2_BASE_ADDR))
DECL|macro|EV64120_BASE_BAUD
mdefine_line|#define EV64120_BASE_BAUD ( 3686400 / 16 )
multiline_comment|/*&n; * PCI interrupts will come in on either the INTA or INTD interrups lines,&n; * which are mapped to the #2 and #5 interrupt pins of the MIPS.  On our&n; * boards, they all either come in on IntD or they all come in on IntA, they&n; * aren&squot;t mixed. There can be numerous PCI interrupts, so we keep a list of the&n; * &quot;requested&quot; interrupt numbers and go through the list whenever we get an&n; * IntA/D.&n; *&n; * Interrupts &lt; 8 are directly wired to the processor; PCI INTA is 8 and&n; * INTD is 11.&n; */
DECL|macro|GT_TIMER
mdefine_line|#define GT_TIMER&t;4
DECL|macro|GT_INTA
mdefine_line|#define GT_INTA&t;&t;2
DECL|macro|GT_INTD
mdefine_line|#define GT_INTD&t;&t;5
macro_line|#endif /* __ASM_GALILEO_BOARDS_MIPS_EV64120_H */
eof
