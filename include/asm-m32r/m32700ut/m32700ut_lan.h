multiline_comment|/*&n; * include/asm/m32700ut_lan.h&n; *&n; * M32700UT-LAN board&n; *&n; * Copyright (c) 2002&t;Takeo Takahashi&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file &quot;COPYING&quot; in the main directory of&n; * this archive for more details.&n; *&n; * $Id$&n; */
macro_line|#ifndef _M32700UT_M32700UT_LAN_H
DECL|macro|_M32700UT_M32700UT_LAN_H
mdefine_line|#define _M32700UT_M32700UT_LAN_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * C functions use non-cache address.&n; */
DECL|macro|M32700UT_LAN_BASE
mdefine_line|#define M32700UT_LAN_BASE&t;(0x10000000 /* + NONCACHE_OFFSET */)
macro_line|#else
DECL|macro|M32700UT_LAN_BASE
mdefine_line|#define M32700UT_LAN_BASE&t;(0x10000000 + NONCACHE_OFFSET)
macro_line|#endif&t;/* __ASSEMBLY__ */
multiline_comment|/* ICU&n; *  ICUISTS:&t;status register&n; *  ICUIREQ0: &t;request register&n; *  ICUIREQ1: &t;request register&n; *  ICUCR3:&t;control register for CFIREQ# interrupt&n; *  ICUCR4:&t;control register for CFC Card insert interrupt&n; *  ICUCR5:&t;control register for CFC Card eject interrupt&n; *  ICUCR6:&t;control register for external interrupt&n; *  ICUCR11:&t;control register for MMC Card insert/eject interrupt&n; *  ICUCR13:&t;control register for SC error interrupt&n; *  ICUCR14:&t;control register for SC receive interrupt&n; *  ICUCR15:&t;control register for SC send interrupt&n; *  ICUCR16:&t;control register for SIO0 receive interrupt&n; *  ICUCR17:&t;control register for SIO0 send interrupt&n; */
DECL|macro|M32700UT_LAN_IRQ_LAN
mdefine_line|#define M32700UT_LAN_IRQ_LAN&t;(M32700UT_LAN_PLD_IRQ_BASE + 1)&t;/* LAN */
DECL|macro|M32700UT_LAN_IRQ_I2C
mdefine_line|#define M32700UT_LAN_IRQ_I2C&t;(M32700UT_LAN_PLD_IRQ_BASE + 3)&t;/* I2C */
DECL|macro|M32700UT_LAN_ICUISTS
mdefine_line|#define M32700UT_LAN_ICUISTS&t;__reg16(M32700UT_LAN_BASE + 0xc0002)
DECL|macro|M32700UT_LAN_ICUISTS_VECB_MASK
mdefine_line|#define M32700UT_LAN_ICUISTS_VECB_MASK&t;(0xf000)
DECL|macro|M32700UT_LAN_VECB
mdefine_line|#define M32700UT_LAN_VECB(x)&t;((x) &amp; M32700UT_LAN_ICUISTS_VECB_MASK)
DECL|macro|M32700UT_LAN_ICUISTS_ISN_MASK
mdefine_line|#define M32700UT_LAN_ICUISTS_ISN_MASK&t;(0x07c0)
DECL|macro|M32700UT_LAN_ICUISTS_ISN
mdefine_line|#define M32700UT_LAN_ICUISTS_ISN(x)&t;((x) &amp; M32700UT_LAN_ICUISTS_ISN_MASK)
DECL|macro|M32700UT_LAN_ICUIREQ0
mdefine_line|#define M32700UT_LAN_ICUIREQ0&t;__reg16(M32700UT_LAN_BASE + 0xc0004)
DECL|macro|M32700UT_LAN_ICUCR1
mdefine_line|#define M32700UT_LAN_ICUCR1&t;__reg16(M32700UT_LAN_BASE + 0xc0010)
DECL|macro|M32700UT_LAN_ICUCR3
mdefine_line|#define M32700UT_LAN_ICUCR3&t;__reg16(M32700UT_LAN_BASE + 0xc0014)
multiline_comment|/*&n; * AR register on PLD&n; */
DECL|macro|ARVCR0
mdefine_line|#define ARVCR0&t;&t;__reg32(M32700UT_LAN_BASE + 0x40000)
DECL|macro|ARVCR0_VDS
mdefine_line|#define ARVCR0_VDS&t;&t;0x00080000
DECL|macro|ARVCR0_RST
mdefine_line|#define ARVCR0_RST&t;&t;0x00010000
DECL|macro|ARVCR1
mdefine_line|#define ARVCR1&t;&t;__reg32(M32700UT_LAN_BASE + 0x40004)
DECL|macro|ARVCR1_QVGA
mdefine_line|#define ARVCR1_QVGA&t;&t;0x02000000
DECL|macro|ARVCR1_NORMAL
mdefine_line|#define ARVCR1_NORMAL&t;&t;0x01000000
DECL|macro|ARVCR1_HIEN
mdefine_line|#define ARVCR1_HIEN&t;&t;0x00010000
DECL|macro|ARVHCOUNT
mdefine_line|#define ARVHCOUNT&t;__reg32(M32700UT_LAN_BASE + 0x40008)
DECL|macro|ARDATA
mdefine_line|#define ARDATA&t;&t;__reg32(M32700UT_LAN_BASE + 0x40010)
DECL|macro|ARINTSEL
mdefine_line|#define ARINTSEL&t;__reg32(M32700UT_LAN_BASE + 0x40014)
DECL|macro|ARINTSEL_INT3
mdefine_line|#define ARINTSEL_INT3&t;&t;0x10000000&t;/* CPU INT3 */
DECL|macro|ARDATA32
mdefine_line|#define ARDATA32&t;__reg32(M32700UT_LAN_BASE + 0x04040010)&t;
singleline_comment|// Block 5
multiline_comment|/*&n;#define ARINTSEL_SEL2&t;&t;0x00002000&n;#define ARINTSEL_SEL3&t;&t;0x00001000&n;#define ARINTSEL_SEL6&t;&t;0x00000200&n;#define ARINTSEL_SEL7&t;&t;0x00000100&n;#define ARINTSEL_SEL9&t;&t;0x00000040&n;#define ARINTSEL_SEL10&t;&t;0x00000020&n;#define ARINTSEL_SEL11&t;&t;0x00000010&n;#define ARINTSEL_SEL12&t;&t;0x00000008&n;*/
multiline_comment|/*&n; * I2C register on PLD&n; */
DECL|macro|PLDI2CCR
mdefine_line|#define PLDI2CCR&t;__reg32(M32700UT_LAN_BASE + 0x40040)
DECL|macro|PLDI2CCR_ES0
mdefine_line|#define&t;PLDI2CCR_ES0&t;&t;0x00000001&t;/* enable I2C interface */
DECL|macro|PLDI2CMOD
mdefine_line|#define PLDI2CMOD&t;__reg32(M32700UT_LAN_BASE + 0x40044)
DECL|macro|PLDI2CMOD_ACKCLK
mdefine_line|#define PLDI2CMOD_ACKCLK&t;0x00000200
DECL|macro|PLDI2CMOD_DTWD
mdefine_line|#define PLDI2CMOD_DTWD&t;&t;0x00000100
DECL|macro|PLDI2CMOD_10BT
mdefine_line|#define PLDI2CMOD_10BT&t;&t;0x00000004
DECL|macro|PLDI2CMOD_ATM_NORMAL
mdefine_line|#define PLDI2CMOD_ATM_NORMAL&t;0x00000000
DECL|macro|PLDI2CMOD_ATM_AUTO
mdefine_line|#define PLDI2CMOD_ATM_AUTO&t;0x00000003
DECL|macro|PLDI2CACK
mdefine_line|#define PLDI2CACK&t;__reg32(M32700UT_LAN_BASE + 0x40048)
DECL|macro|PLDI2CACK_ACK
mdefine_line|#define PLDI2CACK_ACK&t;&t;0x00000001
DECL|macro|PLDI2CFREQ
mdefine_line|#define PLDI2CFREQ&t;__reg32(M32700UT_LAN_BASE + 0x4004c)
DECL|macro|PLDI2CCND
mdefine_line|#define PLDI2CCND&t;__reg32(M32700UT_LAN_BASE + 0x40050)
DECL|macro|PLDI2CCND_START
mdefine_line|#define PLDI2CCND_START&t;&t;0x00000001
DECL|macro|PLDI2CCND_STOP
mdefine_line|#define PLDI2CCND_STOP&t;&t;0x00000002
DECL|macro|PLDI2CSTEN
mdefine_line|#define PLDI2CSTEN&t;__reg32(M32700UT_LAN_BASE + 0x40054)
DECL|macro|PLDI2CSTEN_STEN
mdefine_line|#define PLDI2CSTEN_STEN&t;&t;0x00000001
DECL|macro|PLDI2CDATA
mdefine_line|#define PLDI2CDATA&t;__reg32(M32700UT_LAN_BASE + 0x40060)
DECL|macro|PLDI2CSTS
mdefine_line|#define PLDI2CSTS&t;__reg32(M32700UT_LAN_BASE + 0x40064)
DECL|macro|PLDI2CSTS_TRX
mdefine_line|#define PLDI2CSTS_TRX&t;&t;0x00000020
DECL|macro|PLDI2CSTS_BB
mdefine_line|#define PLDI2CSTS_BB&t;&t;0x00000010
DECL|macro|PLDI2CSTS_NOACK
mdefine_line|#define PLDI2CSTS_NOACK&t;&t;0x00000001&t;/* 0:ack, 1:noack */
macro_line|#endif&t;/* _M32700UT_M32700UT_LAN_H */
eof
