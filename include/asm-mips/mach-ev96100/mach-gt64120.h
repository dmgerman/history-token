multiline_comment|/*&n; *  This is a direct copy of the ev96100.h file, with a global&n; * search and replace.  The numbers are the same.&n; *&n; *  The reason I&squot;m duplicating this is so that the 64120/96100&n; * defines won&squot;t be confusing in the source code.&n; */
macro_line|#ifndef _ASM_GT64120_EV96100_GT64120_DEP_H
DECL|macro|_ASM_GT64120_EV96100_GT64120_DEP_H
mdefine_line|#define _ASM_GT64120_EV96100_GT64120_DEP_H
multiline_comment|/*&n; *   GT96100 config space base address&n; */
DECL|macro|GT64120_BASE
mdefine_line|#define GT64120_BASE&t;(KSEG1ADDR(0x14000000))
multiline_comment|/*&n; *   PCI Bus allocation&n; *&n; *   (Guessing ...)&n; */
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
DECL|macro|EV96100_COM1_BASE_ADDR
mdefine_line|#define EV96100_COM1_BASE_ADDR&t;(0xBD000000 + 0x20)
DECL|macro|EV96100_COM2_BASE_ADDR
mdefine_line|#define EV96100_COM2_BASE_ADDR&t;(0xBD000000 + 0x00)
multiline_comment|/*&n; *   EV96100 interrupt controller register base.&n; */
DECL|macro|EV96100_ICTRL_REGS_BASE
mdefine_line|#define EV96100_ICTRL_REGS_BASE&t;(KSEG1ADDR(0x1f000000))
multiline_comment|/*&n; *   EV96100 UART register base.&n; */
DECL|macro|EV96100_UART0_REGS_BASE
mdefine_line|#define EV96100_UART0_REGS_BASE&t;EV96100_COM1_BASE_ADDR
DECL|macro|EV96100_UART1_REGS_BASE
mdefine_line|#define EV96100_UART1_REGS_BASE&t;EV96100_COM2_BASE_ADDR
DECL|macro|EV96100_BASE_BAUD
mdefine_line|#define EV96100_BASE_BAUD&t;( 3686400 / 16 )
macro_line|#endif /* _ASM_GT64120_EV96100_GT64120_DEP_H */
eof
