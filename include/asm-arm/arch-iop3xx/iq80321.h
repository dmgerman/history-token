multiline_comment|/*&n; * linux/include/asm/arch-iop3xx/iq80321.h&n; *&n; * Intel IQ80321 evaluation board registers&n; */
macro_line|#ifndef _IQ80321_H_
DECL|macro|_IQ80321_H_
mdefine_line|#define _IQ80321_H_
DECL|macro|IQ80321_RAMBASE
mdefine_line|#define IQ80321_RAMBASE&t;&t;0xa0000000
DECL|macro|IQ80321_FLASHBASE
mdefine_line|#define&t;IQ80321_FLASHBASE&t;0xf0000000&t;/* Flash */
DECL|macro|IQ80321_FLASHSIZE
mdefine_line|#define&t;IQ80321_FLASHSIZE&t;0x00800000
DECL|macro|IQ80321_FLASHWIDTH
mdefine_line|#define&t;IQ80321_FLASHWIDTH&t;1
DECL|macro|IQ80321_UART
mdefine_line|#define IQ80321_UART&t;&t;0xfe800000&t;/* UART #1 */
DECL|macro|IQ80321_7SEG_1
mdefine_line|#define IQ80321_7SEG_1&t;&t;0xfe840000&t;/* 7-Segment MSB */
DECL|macro|IQ80321_7SEG_0
mdefine_line|#define IQ80321_7SEG_0&t;&t;0xfe850000&t;/* 7-Segment LSB (WO) */
DECL|macro|IQ80321_ROTARY_SW
mdefine_line|#define IQ80321_ROTARY_SW&t;0xfe8d0000&t;/* Rotary Switch */
DECL|macro|IQ80321_BATT_STAT
mdefine_line|#define IQ80321_BATT_STAT&t;0xfe8f0000&t;/* Battery Status */
multiline_comment|/*&n; * IQ80321 PCI I/O and Mem space regions&n; */
DECL|macro|IQ80321_PCI_IO_BASE
mdefine_line|#define IQ80321_PCI_IO_BASE&t;0x90000000
DECL|macro|IQ80321_PCI_IO_SIZE
mdefine_line|#define IQ80321_PCI_IO_SIZE&t;0x00010000
DECL|macro|IQ80321_PCI_MEM_BASE
mdefine_line|#define IQ80321_PCI_MEM_BASE&t;0x80000000
DECL|macro|IQ80321_PCI_MEM_SIZE
mdefine_line|#define IQ80321_PCI_MEM_SIZE&t;0x04000000
DECL|macro|IQ80321_PCI_IO_OFFSET
mdefine_line|#define&t;IQ80321_PCI_IO_OFFSET&t;0x6e000000
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|iq80321_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;
singleline_comment|// _IQ80321_H_
eof
