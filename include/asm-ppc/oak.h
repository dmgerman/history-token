multiline_comment|/*&n; * BK Id: SCCS/s.oak.h 1.7 05/17/01 18:14:25 cort&n; */
multiline_comment|/*&n; *&n; *    Copyright (c) 1999 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *&n; *    Module name: oak.h&n; *&n; *    Description:&n; *&t;Macros, definitions, and data structures specific to the IBM PowerPC&n; *      403G{A,B,C,CX} &quot;Oak&quot; evaluation board. Anything specific to the pro-&n; *      cessor itself is defined elsewhere.&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef&t;__OAK_H__
DECL|macro|__OAK_H__
mdefine_line|#define&t;__OAK_H__
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE&t;0
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE&t;0
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET&t;0
multiline_comment|/* Memory map for the &quot;Oak&quot; evaluation board */
DECL|macro|PPC403SPU_IO_BASE
mdefine_line|#define&t;PPC403SPU_IO_BASE      &t;0x40000000&t;/* 403 On-chip serial port */
DECL|macro|PPC403SPU_IO_SIZE
mdefine_line|#define&t;PPC403SPU_IO_SIZE      &t;0x00000008
DECL|macro|OAKSERIAL_IO_BASE
mdefine_line|#define&t;OAKSERIAL_IO_BASE&t;0x7E000000&t;/* NS16550DV serial port */
DECL|macro|OAKSERIAL_IO_SIZE
mdefine_line|#define&t;OAKSERIAL_IO_SIZE&t;0x00000008
DECL|macro|OAKNET_IO_BASE
mdefine_line|#define&t;OAKNET_IO_BASE&t;&t;0xF4000000&t;/* NS83902AV Ethernet */
DECL|macro|OAKNET_IO_SIZE
mdefine_line|#define&t;OAKNET_IO_SIZE&t;&t;0x00000040
DECL|macro|OAKPROM_IO_BASE
mdefine_line|#define&t;OAKPROM_IO_BASE&t;&t;0xFFFE0000&t;/* AMD 29F010 Flash ROM */
DECL|macro|OAKPROM_IO_SIZE
mdefine_line|#define&t;OAKPROM_IO_SIZE&t;&t;0x00020000
multiline_comment|/* Interrupt assignments fixed by the hardware implementation */
DECL|macro|PPC403SPU_RX_INT
mdefine_line|#define&t;PPC403SPU_RX_INT&t;AIC_INT4
DECL|macro|PPC403SPU_TX_INT
mdefine_line|#define&t;PPC403SPU_TX_INT&t;AIC_INT5
DECL|macro|OAKNET_INT
mdefine_line|#define&t;OAKNET_INT&t;&t;AIC_INT27
DECL|macro|OAKSERIAL_INT
mdefine_line|#define&t;OAKSERIAL_INT&t;&t;AIC_INT28
multiline_comment|/*&n; * Data structure defining board information maintained by the boot&n; * ROM on IBM&squot;s &quot;Oak&quot; evaluation board. An effort has been made to&n; * keep the field names consistent with the 8xx &squot;bd_t&squot; board info&n; * structures.&n; */
DECL|struct|board_info
r_typedef
r_struct
id|board_info
(brace
DECL|member|bi_s_version
r_int
r_char
id|bi_s_version
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Version of this structure */
DECL|member|bi_r_version
r_int
r_char
id|bi_r_version
(braket
l_int|30
)braket
suffix:semicolon
multiline_comment|/* Version of the IBM ROM */
DECL|member|bi_memsize
r_int
r_int
id|bi_memsize
suffix:semicolon
multiline_comment|/* DRAM installed, in bytes */
DECL|member|bi_enetaddr
r_int
r_char
id|bi_enetaddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Ethernet MAC address */
DECL|member|bi_intfreq
r_int
r_int
id|bi_intfreq
suffix:semicolon
multiline_comment|/* Processor speed, in Hz */
DECL|member|bi_busfreq
r_int
r_int
id|bi_busfreq
suffix:semicolon
multiline_comment|/* Bus speed, in Hz */
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
multiline_comment|/* Generic 4xx type&n;*/
DECL|macro|_MACH_4xx
mdefine_line|#define _MACH_4xx (_MACH_oak)
macro_line|#endif /* __OAK_H__ */
macro_line|#endif /* __KERNEL__ */
eof
