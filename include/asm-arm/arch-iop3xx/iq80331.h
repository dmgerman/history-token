multiline_comment|/*&n; * linux/include/asm/arch-iop3xx/iq80331.h&n; *&n; * Intel IQ80331 evaluation board registers&n; */
macro_line|#ifndef _IQ80331_H_
DECL|macro|_IQ80331_H_
mdefine_line|#define _IQ80331_H_
DECL|macro|IQ80331_RAMBASE
mdefine_line|#define IQ80331_RAMBASE&t;&t;0x00000000
DECL|macro|IQ80331_FLASHBASE
mdefine_line|#define&t;IQ80331_FLASHBASE&t;0xc0000000&t;/* Flash */
DECL|macro|IQ80331_FLASHSIZE
mdefine_line|#define&t;IQ80331_FLASHSIZE&t;0x00800000
DECL|macro|IQ80331_FLASHWIDTH
mdefine_line|#define&t;IQ80331_FLASHWIDTH&t;1
DECL|macro|IQ80331_UART0_PHYS
mdefine_line|#define IQ80331_UART0_PHYS  (IOP331_PHYS_MEM_BASE | 0x00001700)&t;/* UART #1 physical */
DECL|macro|IQ80331_UART1_PHYS
mdefine_line|#define IQ80331_UART1_PHYS  (IOP331_PHYS_MEM_BASE | 0x00001740)&t;/* UART #2 physical */
DECL|macro|IQ80331_UART0_VIRT
mdefine_line|#define IQ80331_UART0_VIRT  (IOP331_VIRT_MEM_BASE | 0x00001700) /* UART #1 virtual addr */
DECL|macro|IQ80331_UART1_VIRT
mdefine_line|#define IQ80331_UART1_VIRT  (IOP331_VIRT_MEM_BASE | 0x00001740) /* UART #2 virtual addr */
DECL|macro|IQ80331_7SEG_1
mdefine_line|#define IQ80331_7SEG_1&t;&t;0xce840000&t;/* 7-Segment MSB */
DECL|macro|IQ80331_7SEG_0
mdefine_line|#define IQ80331_7SEG_0&t;&t;0xce850000&t;/* 7-Segment LSB (WO) */
DECL|macro|IQ80331_ROTARY_SW
mdefine_line|#define IQ80331_ROTARY_SW&t;0xce8d0000&t;/* Rotary Switch */
DECL|macro|IQ80331_BATT_STAT
mdefine_line|#define IQ80331_BATT_STAT&t;0xce8f0000&t;/* Battery Status */
multiline_comment|/*&n; * IQ80331 PCI I/O and Mem space regions&n; */
DECL|macro|IQ80331_PCI_IO_BASE
mdefine_line|#define IQ80331_PCI_IO_BASE&t;0x90000000
DECL|macro|IQ80331_PCI_IO_SIZE
mdefine_line|#define IQ80331_PCI_IO_SIZE&t;0x00010000
DECL|macro|IQ80331_PCI_MEM_BASE
mdefine_line|#define IQ80331_PCI_MEM_BASE&t;0x80000000
DECL|macro|IQ80331_PCI_MEM_SIZE
mdefine_line|#define IQ80331_PCI_MEM_SIZE&t;0x08000000
DECL|macro|IQ80331_PCI_IO_OFFSET
mdefine_line|#define&t;IQ80331_PCI_IO_OFFSET&t;0x6e000000
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|iq80331_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;
singleline_comment|// _IQ80331_H_
eof
