multiline_comment|/*&n; *&n; */
macro_line|#ifndef _MIPS_EV96100_H
DECL|macro|_MIPS_EV96100_H
mdefine_line|#define _MIPS_EV96100_H
macro_line|#include &lt;asm/addrspace.h&gt;
multiline_comment|/*&n; *   GT64120 config space base address&n; */
DECL|macro|GT64120_BASE
mdefine_line|#define GT64120_BASE    (KSEG1ADDR(0x14000000))
DECL|macro|MIPS_GT_BASE
mdefine_line|#define MIPS_GT_BASE    GT64120_BASE
multiline_comment|/*&n; *   PCI Bus allocation&n; */
DECL|macro|GT_PCI_MEM_BASE
mdefine_line|#define GT_PCI_MEM_BASE    0x12000000
DECL|macro|GT_PCI_MEM_SIZE
mdefine_line|#define GT_PCI_MEM_SIZE    0x02000000
DECL|macro|GT_PCI_IO_BASE
mdefine_line|#define GT_PCI_IO_BASE     0x10000000
DECL|macro|GT_PCI_IO_SIZE
mdefine_line|#define GT_PCI_IO_SIZE     0x02000000
DECL|macro|GT_ISA_IO_BASE
mdefine_line|#define GT_ISA_IO_BASE     PCI_IO_BASE
multiline_comment|/*&n; *   Duart I/O ports.&n; */
DECL|macro|EV96100_COM1_BASE_ADDR
mdefine_line|#define EV96100_COM1_BASE_ADDR  (0xBD000000 + 0x20)
DECL|macro|EV96100_COM2_BASE_ADDR
mdefine_line|#define EV96100_COM2_BASE_ADDR  (0xBD000000 + 0x00)
multiline_comment|/*&n; *   EV96100 interrupt controller register base.&n; */
DECL|macro|EV96100_ICTRL_REGS_BASE
mdefine_line|#define EV96100_ICTRL_REGS_BASE   (KSEG1ADDR(0x1f000000))
multiline_comment|/*&n; *   EV96100 UART register base.&n; */
DECL|macro|EV96100_UART0_REGS_BASE
mdefine_line|#define EV96100_UART0_REGS_BASE    EV96100_COM1_BASE_ADDR
DECL|macro|EV96100_UART1_REGS_BASE
mdefine_line|#define EV96100_UART1_REGS_BASE    EV96100_COM2_BASE_ADDR
DECL|macro|EV96100_BASE_BAUD
mdefine_line|#define EV96100_BASE_BAUD ( 3686400 / 16 )
multiline_comment|/*&n; * Because of an error/peculiarity in the Galileo chip, we need to swap the&n; * bytes when running bigendian.&n; */
DECL|macro|GT_WRITE
mdefine_line|#define GT_WRITE(ofs, data)  &bslash;&n;             *(volatile u32 *)(MIPS_GT_BASE+ofs) = cpu_to_le32(data)
DECL|macro|GT_READ
mdefine_line|#define GT_READ(ofs, data)   &bslash;&n;             data = le32_to_cpu(*(volatile u32 *)(MIPS_GT_BASE+ofs))
macro_line|#endif /* !(_MIPS_EV96100_H) */
eof
