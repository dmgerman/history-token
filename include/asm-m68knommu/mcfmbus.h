multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *      mcfmbus.h -- Coldfire MBUS support defines.&n; *&n; *      (C) Copyright 1999, Martin Floeer (mfloeer@axcent.de) &n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef mcfmbus_h
DECL|macro|mcfmbus_h
mdefine_line|#define mcfmbus_h
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|MCFMBUS_BASE
mdefine_line|#define MCFMBUS_BASE&t;&t;0x280
DECL|macro|MCFMBUS_IRQ_VECTOR
mdefine_line|#define MCFMBUS_IRQ_VECTOR&t;0x19
DECL|macro|MCFMBUS_IRQ
mdefine_line|#define MCFMBUS_IRQ&t;&t;0x1
DECL|macro|MCFMBUS_CLK
mdefine_line|#define MCFMBUS_CLK&t;&t;0x3f
DECL|macro|MCFMBUS_IRQ_LEVEL
mdefine_line|#define MCFMBUS_IRQ_LEVEL&t;0x07&t;/*IRQ Level 1*/
DECL|macro|MCFMBUS_ADDRESS
mdefine_line|#define MCFMBUS_ADDRESS&t;&t;0x01
multiline_comment|/*&n;*&t;Define the 5307 MBUS register set addresses&n;*/
DECL|macro|MCFMBUS_MADR
mdefine_line|#define MCFMBUS_MADR&t;0x00
DECL|macro|MCFMBUS_MFDR
mdefine_line|#define MCFMBUS_MFDR&t;0x04
DECL|macro|MCFMBUS_MBCR
mdefine_line|#define MCFMBUS_MBCR&t;0x08
DECL|macro|MCFMBUS_MBSR
mdefine_line|#define MCFMBUS_MBSR&t;0x0C
DECL|macro|MCFMBUS_MBDR
mdefine_line|#define MCFMBUS_MBDR&t;0x10
DECL|macro|MCFMBUS_MADR_ADDR
mdefine_line|#define MCFMBUS_MADR_ADDR(a)&t;(((a)&amp;0x7F)&lt;&lt;0x01) /*Slave Address*/
DECL|macro|MCFMBUS_MFDR_MBC
mdefine_line|#define MCFMBUS_MFDR_MBC(a)&t;((a)&amp;0x3F)&t;   /*M-Bus Clock*/
multiline_comment|/*&n;*&t;Define bit flags in Controll Register&n;*/
DECL|macro|MCFMBUS_MBCR_MEN
mdefine_line|#define MCFMBUS_MBCR_MEN           (0x80)  /* M-Bus Enable                 */
DECL|macro|MCFMBUS_MBCR_MIEN
mdefine_line|#define MCFMBUS_MBCR_MIEN          (0x40)  /* M-Bus Interrupt Enable       */
DECL|macro|MCFMBUS_MBCR_MSTA
mdefine_line|#define MCFMBUS_MBCR_MSTA          (0x20)  /* Master/Slave Mode Select Bit */
DECL|macro|MCFMBUS_MBCR_MTX
mdefine_line|#define MCFMBUS_MBCR_MTX           (0x10)  /* Transmit/Rcv Mode Select Bit */
DECL|macro|MCFMBUS_MBCR_TXAK
mdefine_line|#define MCFMBUS_MBCR_TXAK          (0x08)  /* Transmit Acknowledge Enable  */
DECL|macro|MCFMBUS_MBCR_RSTA
mdefine_line|#define MCFMBUS_MBCR_RSTA          (0x04)  /* Repeat Start                 */
multiline_comment|/*&n;*&t;Define bit flags in Status Register&n;*/
DECL|macro|MCFMBUS_MBSR_MCF
mdefine_line|#define MCFMBUS_MBSR_MCF           (0x80)  /* Data Transfer Complete       */
DECL|macro|MCFMBUS_MBSR_MAAS
mdefine_line|#define MCFMBUS_MBSR_MAAS          (0x40)  /* Addressed as a Slave         */
DECL|macro|MCFMBUS_MBSR_MBB
mdefine_line|#define MCFMBUS_MBSR_MBB           (0x20)  /* Bus Busy                     */
DECL|macro|MCFMBUS_MBSR_MAL
mdefine_line|#define MCFMBUS_MBSR_MAL           (0x10)  /* Arbitration Lost             */
DECL|macro|MCFMBUS_MBSR_SRW
mdefine_line|#define MCFMBUS_MBSR_SRW           (0x04)  /* Slave Transmit               */
DECL|macro|MCFMBUS_MBSR_MIF
mdefine_line|#define MCFMBUS_MBSR_MIF           (0x02)  /* M-Bus Interrupt              */
DECL|macro|MCFMBUS_MBSR_RXAK
mdefine_line|#define MCFMBUS_MBSR_RXAK          (0x01)  /* No Acknowledge Received      */
multiline_comment|/*&n;*&t;Define bit flags in DATA I/O Register&n;*/
DECL|macro|MCFMBUS_MBDR_READ
mdefine_line|#define MCFMBUS_MBDR_READ          (0x01)  /* 1=read 0=write MBUS */
DECL|macro|MBUSIOCSCLOCK
mdefine_line|#define MBUSIOCSCLOCK&t;&t;1
DECL|macro|MBUSIOCGCLOCK
mdefine_line|#define MBUSIOCGCLOCK&t;&t;2
DECL|macro|MBUSIOCSADDR
mdefine_line|#define MBUSIOCSADDR&t;&t;&t;3
DECL|macro|MBUSIOCGADDR
mdefine_line|#define MBUSIOCGADDR&t;&t;&t;4
DECL|macro|MBUSIOCSSLADDR
mdefine_line|#define MBUSIOCSSLADDR&t;&t;&t;5
DECL|macro|MBUSIOCGSLADDR
mdefine_line|#define MBUSIOCGSLADDR&t;&t;&t;6
DECL|macro|MBUSIOCSSUBADDR
mdefine_line|#define MBUSIOCSSUBADDR&t;&t;&t;7
DECL|macro|MBUSIOCGSUBADDR
mdefine_line|#define MBUSIOCGSUBADDR&t;&t;&t;8
macro_line|#endif
eof
