multiline_comment|/* gpio-regs.h: on-chip general purpose I/O registers&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_GPIO_REGS
DECL|macro|_ASM_GPIO_REGS
mdefine_line|#define _ASM_GPIO_REGS
DECL|macro|__reg
mdefine_line|#define __reg(ADDR) (*(volatile unsigned long *)(ADDR))
DECL|macro|__get_PDR
mdefine_line|#define __get_PDR()&t;({ __reg(0xfeff0400); })
DECL|macro|__set_PDR
mdefine_line|#define __set_PDR(V)&t;do { __reg(0xfeff0400) = (V); mb(); } while(0)
DECL|macro|__get_GPDR
mdefine_line|#define __get_GPDR()&t;({ __reg(0xfeff0408); })
DECL|macro|__set_GPDR
mdefine_line|#define __set_GPDR(V)&t;do { __reg(0xfeff0408) = (V); mb(); } while(0)
DECL|macro|__get_SIR
mdefine_line|#define __get_SIR()&t;({ __reg(0xfeff0410); })
DECL|macro|__set_SIR
mdefine_line|#define __set_SIR(V)&t;do { __reg(0xfeff0410) = (V); mb(); } while(0)
DECL|macro|__get_SOR
mdefine_line|#define __get_SOR()&t;({ __reg(0xfeff0418); })
DECL|macro|__set_SOR
mdefine_line|#define __set_SOR(V)&t;do { __reg(0xfeff0418) = (V); mb(); } while(0)
DECL|macro|__set_PDSR
mdefine_line|#define __set_PDSR(V)&t;do { __reg(0xfeff0420) = (V); mb(); } while(0)
DECL|macro|__set_PDCR
mdefine_line|#define __set_PDCR(V)&t;do { __reg(0xfeff0428) = (V); mb(); } while(0)
DECL|macro|__get_RSTR
mdefine_line|#define __get_RSTR()&t;({ __reg(0xfeff0500); })
DECL|macro|__set_RSTR
mdefine_line|#define __set_RSTR(V)&t;do { __reg(0xfeff0500) = (V); mb(); } while(0)
multiline_comment|/* PDR definitions */
DECL|macro|PDR_GPIO_DATA
mdefine_line|#define PDR_GPIO_DATA(X)&t;(1 &lt;&lt; (X))
multiline_comment|/* GPDR definitions */
DECL|macro|GPDR_INPUT
mdefine_line|#define GPDR_INPUT&t;&t;0
DECL|macro|GPDR_OUTPUT
mdefine_line|#define GPDR_OUTPUT&t;&t;1
DECL|macro|GPDR_DREQ0_BIT
mdefine_line|#define GPDR_DREQ0_BIT&t;&t;0x00001000
DECL|macro|GPDR_DREQ1_BIT
mdefine_line|#define GPDR_DREQ1_BIT&t;&t;0x00008000
DECL|macro|GPDR_DREQ2_BIT
mdefine_line|#define GPDR_DREQ2_BIT&t;&t;0x00040000
DECL|macro|GPDR_DREQ3_BIT
mdefine_line|#define GPDR_DREQ3_BIT&t;&t;0x00080000
DECL|macro|GPDR_DREQ4_BIT
mdefine_line|#define GPDR_DREQ4_BIT&t;&t;0x00004000
DECL|macro|GPDR_DREQ5_BIT
mdefine_line|#define GPDR_DREQ5_BIT&t;&t;0x00020000
DECL|macro|GPDR_DREQ6_BIT
mdefine_line|#define GPDR_DREQ6_BIT&t;&t;0x00100000
DECL|macro|GPDR_DREQ7_BIT
mdefine_line|#define GPDR_DREQ7_BIT&t;&t;0x00200000
DECL|macro|GPDR_DACK0_BIT
mdefine_line|#define GPDR_DACK0_BIT&t;&t;0x00002000
DECL|macro|GPDR_DACK1_BIT
mdefine_line|#define GPDR_DACK1_BIT&t;&t;0x00010000
DECL|macro|GPDR_DACK2_BIT
mdefine_line|#define GPDR_DACK2_BIT&t;&t;0x00100000
DECL|macro|GPDR_DACK3_BIT
mdefine_line|#define GPDR_DACK3_BIT&t;&t;0x00200000
DECL|macro|GPDR_DONE0_BIT
mdefine_line|#define GPDR_DONE0_BIT&t;&t;0x00004000
DECL|macro|GPDR_DONE1_BIT
mdefine_line|#define GPDR_DONE1_BIT&t;&t;0x00020000
DECL|macro|GPDR_GPIO_DIR
mdefine_line|#define GPDR_GPIO_DIR(X,D)&t;((D) &lt;&lt; (X))
multiline_comment|/* SIR definitions */
DECL|macro|SIR_GPIO_INPUT
mdefine_line|#define SIR_GPIO_INPUT&t;&t;0
DECL|macro|SIR_DREQ7_INPUT
mdefine_line|#define SIR_DREQ7_INPUT&t;&t;0x00200000
DECL|macro|SIR_DREQ6_INPUT
mdefine_line|#define SIR_DREQ6_INPUT&t;&t;0x00100000
DECL|macro|SIR_DREQ3_INPUT
mdefine_line|#define SIR_DREQ3_INPUT&t;&t;0x00080000
DECL|macro|SIR_DREQ2_INPUT
mdefine_line|#define SIR_DREQ2_INPUT&t;&t;0x00040000
DECL|macro|SIR_DREQ5_INPUT
mdefine_line|#define SIR_DREQ5_INPUT&t;&t;0x00020000
DECL|macro|SIR_DREQ1_INPUT
mdefine_line|#define SIR_DREQ1_INPUT&t;&t;0x00008000
DECL|macro|SIR_DREQ4_INPUT
mdefine_line|#define SIR_DREQ4_INPUT&t;&t;0x00004000
DECL|macro|SIR_DREQ0_INPUT
mdefine_line|#define SIR_DREQ0_INPUT&t;&t;0x00001000
DECL|macro|SIR_RXD1_INPUT
mdefine_line|#define SIR_RXD1_INPUT&t;&t;0x00000400
DECL|macro|SIR_CTS0_INPUT
mdefine_line|#define SIR_CTS0_INPUT&t;&t;0x00000100
DECL|macro|SIR_RXD0_INPUT
mdefine_line|#define SIR_RXD0_INPUT&t;&t;0x00000040
DECL|macro|SIR_GATE1_INPUT
mdefine_line|#define SIR_GATE1_INPUT&t;&t;0x00000020
DECL|macro|SIR_GATE0_INPUT
mdefine_line|#define SIR_GATE0_INPUT&t;&t;0x00000010
DECL|macro|SIR_IRQ3_INPUT
mdefine_line|#define SIR_IRQ3_INPUT&t;&t;0x00000008
DECL|macro|SIR_IRQ2_INPUT
mdefine_line|#define SIR_IRQ2_INPUT&t;&t;0x00000004
DECL|macro|SIR_IRQ1_INPUT
mdefine_line|#define SIR_IRQ1_INPUT&t;&t;0x00000002
DECL|macro|SIR_IRQ0_INPUT
mdefine_line|#define SIR_IRQ0_INPUT&t;&t;0x00000001
DECL|macro|SIR_DREQ_BITS
mdefine_line|#define SIR_DREQ_BITS&t;&t;(SIR_DREQ0_INPUT | SIR_DREQ1_INPUT | &bslash;&n;&t;&t;&t;&t; SIR_DREQ2_INPUT | SIR_DREQ3_INPUT | &bslash;&n;&t;&t;&t;&t; SIR_DREQ4_INPUT | SIR_DREQ5_INPUT | &bslash;&n;&t;&t;&t;&t; SIR_DREQ6_INPUT | SIR_DREQ7_INPUT)
multiline_comment|/* SOR definitions */
DECL|macro|SOR_GPIO_OUTPUT
mdefine_line|#define SOR_GPIO_OUTPUT&t;&t;0
DECL|macro|SOR_DACK3_OUTPUT
mdefine_line|#define SOR_DACK3_OUTPUT&t;0x00200000
DECL|macro|SOR_DACK2_OUTPUT
mdefine_line|#define SOR_DACK2_OUTPUT&t;0x00100000
DECL|macro|SOR_DONE1_OUTPUT
mdefine_line|#define SOR_DONE1_OUTPUT&t;0x00020000
DECL|macro|SOR_DACK1_OUTPUT
mdefine_line|#define SOR_DACK1_OUTPUT&t;0x00010000
DECL|macro|SOR_DONE0_OUTPUT
mdefine_line|#define SOR_DONE0_OUTPUT&t;0x00004000
DECL|macro|SOR_DACK0_OUTPUT
mdefine_line|#define SOR_DACK0_OUTPUT&t;0x00002000
DECL|macro|SOR_TXD1_OUTPUT
mdefine_line|#define SOR_TXD1_OUTPUT&t;&t;0x00000800
DECL|macro|SOR_RTS0_OUTPUT
mdefine_line|#define SOR_RTS0_OUTPUT&t;&t;0x00000200
DECL|macro|SOR_TXD0_OUTPUT
mdefine_line|#define SOR_TXD0_OUTPUT&t;&t;0x00000080
DECL|macro|SOR_TOUT1_OUTPUT
mdefine_line|#define SOR_TOUT1_OUTPUT&t;0x00000020
DECL|macro|SOR_TOUT0_OUTPUT
mdefine_line|#define SOR_TOUT0_OUTPUT&t;0x00000010
DECL|macro|SOR_DONE_BITS
mdefine_line|#define SOR_DONE_BITS&t;&t;(SOR_DONE0_OUTPUT | SOR_DONE1_OUTPUT)
DECL|macro|SOR_DACK_BITS
mdefine_line|#define SOR_DACK_BITS&t;&t;(SOR_DACK0_OUTPUT | SOR_DACK1_OUTPUT | &bslash;&n;&t;&t;&t;&t; SOR_DACK2_OUTPUT | SOR_DACK3_OUTPUT)
multiline_comment|/* PDSR definitions */
DECL|macro|PDSR_UNCHANGED
mdefine_line|#define PDSR_UNCHANGED&t;&t;0
DECL|macro|PDSR_SET_BIT
mdefine_line|#define PDSR_SET_BIT(X)&t;&t;(1 &lt;&lt; (X))
multiline_comment|/* PDCR definitions */
DECL|macro|PDCR_UNCHANGED
mdefine_line|#define PDCR_UNCHANGED&t;&t;0
DECL|macro|PDCR_CLEAR_BIT
mdefine_line|#define PDCR_CLEAR_BIT(X)&t;(1 &lt;&lt; (X))
multiline_comment|/* RSTR definitions */
multiline_comment|/* Read Only */
DECL|macro|RSTR_POWERON
mdefine_line|#define RSTR_POWERON&t;&t;0x00000400
DECL|macro|RSTR_SOFTRESET_STATUS
mdefine_line|#define RSTR_SOFTRESET_STATUS&t;0x00000100
multiline_comment|/* Write Only */
DECL|macro|RSTR_SOFTRESET
mdefine_line|#define RSTR_SOFTRESET&t;&t;0x00000001
macro_line|#endif /* _ASM_GPIO_REGS */
eof
