multiline_comment|/*&n; * BK Id: SCCS/s.fads.h 1.14 10/26/01 10:14:09 trini&n; */
multiline_comment|/*&n; * A collection of structures, addresses, and values associated with&n; * the Motorola 860T FADS board.  Copied from the MBX stuff.&n; *&n; * Copyright (c) 1998 Dan Malek (dmalek@jlc.net)&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_FADS_H__
DECL|macro|__ASM_FADS_H__
mdefine_line|#define __ASM_FADS_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
multiline_comment|/* Memory map is configured by the PROM startup.&n; * I tried to follow the FADS manual, although the startup PROM&n; * dictates this and we simply have to move some of the physical&n; * addresses for Linux.&n; */
DECL|macro|BCSR_ADDR
mdefine_line|#define BCSR_ADDR&t;&t;((uint)0xff010000)
DECL|macro|BCSR_SIZE
mdefine_line|#define BCSR_SIZE&t;&t;((uint)(64 * 1024))
DECL|macro|BCSR0
mdefine_line|#define&t;BCSR0&t;&t;&t;((uint)0xff010000)
DECL|macro|BCSR1
mdefine_line|#define&t;BCSR1&t;&t;&t;((uint)0xff010004)
DECL|macro|BCSR2
mdefine_line|#define&t;BCSR2&t;&t;&t;((uint)0xff010008)
DECL|macro|BCSR3
mdefine_line|#define&t;BCSR3&t;&t;&t;((uint)0xff01000c)
DECL|macro|BCSR4
mdefine_line|#define&t;BCSR4&t;&t;&t;((uint)0xff010010)
DECL|macro|IMAP_ADDR
mdefine_line|#define IMAP_ADDR&t;&t;((uint)0xff000000)
DECL|macro|IMAP_SIZE
mdefine_line|#define IMAP_SIZE&t;&t;((uint)(64 * 1024))
DECL|macro|PCMCIA_MEM_ADDR
mdefine_line|#define PCMCIA_MEM_ADDR&t;&t;((uint)0xff020000)
DECL|macro|PCMCIA_MEM_SIZE
mdefine_line|#define PCMCIA_MEM_SIZE&t;&t;((uint)(64 * 1024))
multiline_comment|/* Bits of interest in the BCSRs.&n; */
DECL|macro|BCSR1_ETHEN
mdefine_line|#define BCSR1_ETHEN&t;&t;((uint)0x20000000)
DECL|macro|BCSR1_RS232EN_1
mdefine_line|#define BCSR1_RS232EN_1&t;&t;((uint)0x01000000)
DECL|macro|BCSR1_RS232EN_2
mdefine_line|#define BCSR1_RS232EN_2&t;&t;((uint)0x00040000)
DECL|macro|BCSR4_ETHLOOP
mdefine_line|#define BCSR4_ETHLOOP&t;&t;((uint)0x80000000)&t;/* EEST Loopback */
DECL|macro|BCSR4_EEFDX
mdefine_line|#define BCSR4_EEFDX&t;&t;((uint)0x40000000)&t;/* EEST FDX enable */
DECL|macro|BCSR4_FETH_EN
mdefine_line|#define BCSR4_FETH_EN&t;&t;((uint)0x08000000)&t;/* PHY enable */
DECL|macro|BCSR4_FETHCFG0
mdefine_line|#define BCSR4_FETHCFG0&t;&t;((uint)0x04000000)&t;/* PHY autoneg mode */
DECL|macro|BCSR4_FETHCFG1
mdefine_line|#define BCSR4_FETHCFG1&t;&t;((uint)0x00400000)&t;/* PHY autoneg mode */
DECL|macro|BCSR4_FETHFDE
mdefine_line|#define BCSR4_FETHFDE&t;&t;((uint)0x02000000)&t;/* PHY FDX advertise */
DECL|macro|BCSR4_FETHRST
mdefine_line|#define BCSR4_FETHRST&t;&t;((uint)0x00200000)&t;/* PHY Reset */
multiline_comment|/* Interrupt level assignments.&n; */
DECL|macro|FEC_INTERRUPT
mdefine_line|#define FEC_INTERRUPT&t;SIU_LEVEL1&t;/* FEC interrupt */
DECL|macro|PHY_INTERRUPT
mdefine_line|#define PHY_INTERRUPT&t;SIU_IRQ2&t;/* PHY link change interrupt */
multiline_comment|/* We don&squot;t use the 8259.&n; */
DECL|macro|NR_8259_INTS
mdefine_line|#define NR_8259_INTS&t;0
macro_line|#endif /* __ASM_FADS_H__ */
macro_line|#endif /* __KERNEL__ */
eof
