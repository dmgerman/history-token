multiline_comment|/*&n; * include/asm/opsput/opsput_pld.h&n; *&n; * Definitions for Programable Logic Device(PLD) on OPSPUT board.&n; *&n; * Copyright (c) 2002&t;Takeo Takahashi&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file &quot;COPYING&quot; in the main directory of&n; * this archive for more details.&n; *&n; * $Id: opsput_pld.h,v 1.1 2004/07/27 06:54:20 sakugawa Exp $&n; */
macro_line|#ifndef _OPSPUT_OPSPUT_PLD_H
DECL|macro|_OPSPUT_OPSPUT_PLD_H
mdefine_line|#define _OPSPUT_OPSPUT_PLD_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|PLD_PLAT_BASE
mdefine_line|#define PLD_PLAT_BASE&t;&t;0x1cc00000
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * C functions use non-cache address.&n; */
DECL|macro|PLD_BASE
mdefine_line|#define PLD_BASE&t;&t;(PLD_PLAT_BASE /* + NONCACHE_OFFSET */)
DECL|macro|__reg8
mdefine_line|#define __reg8&t;&t;&t;(volatile unsigned char *)
DECL|macro|__reg16
mdefine_line|#define __reg16&t;&t;&t;(volatile unsigned short *)
DECL|macro|__reg32
mdefine_line|#define __reg32&t;&t;&t;(volatile unsigned int *)
macro_line|#else
DECL|macro|PLD_BASE
mdefine_line|#define PLD_BASE&t;&t;(PLD_PLAT_BASE + NONCACHE_OFFSET)
DECL|macro|__reg8
mdefine_line|#define __reg8
DECL|macro|__reg16
mdefine_line|#define __reg16
DECL|macro|__reg32
mdefine_line|#define __reg32
macro_line|#endif&t;/* __ASSEMBLY__ */
multiline_comment|/* CFC */
DECL|macro|PLD_CFRSTCR
mdefine_line|#define&t;PLD_CFRSTCR&t;&t;__reg16(PLD_BASE + 0x0000)
DECL|macro|PLD_CFSTS
mdefine_line|#define PLD_CFSTS&t;&t;__reg16(PLD_BASE + 0x0002)
DECL|macro|PLD_CFIMASK
mdefine_line|#define PLD_CFIMASK&t;&t;__reg16(PLD_BASE + 0x0004)
DECL|macro|PLD_CFBUFCR
mdefine_line|#define PLD_CFBUFCR&t;&t;__reg16(PLD_BASE + 0x0006)
DECL|macro|PLD_CFVENCR
mdefine_line|#define PLD_CFVENCR&t;&t;__reg16(PLD_BASE + 0x0008)
DECL|macro|PLD_CFCR0
mdefine_line|#define PLD_CFCR0&t;&t;__reg16(PLD_BASE + 0x000a)
DECL|macro|PLD_CFCR1
mdefine_line|#define PLD_CFCR1&t;&t;__reg16(PLD_BASE + 0x000c)
DECL|macro|PLD_IDERSTCR
mdefine_line|#define PLD_IDERSTCR&t;&t;__reg16(PLD_BASE + 0x0010)
multiline_comment|/* MMC */
DECL|macro|PLD_MMCCR
mdefine_line|#define PLD_MMCCR&t;&t;__reg16(PLD_BASE + 0x4000)
DECL|macro|PLD_MMCMOD
mdefine_line|#define PLD_MMCMOD&t;&t;__reg16(PLD_BASE + 0x4002)
DECL|macro|PLD_MMCSTS
mdefine_line|#define PLD_MMCSTS&t;&t;__reg16(PLD_BASE + 0x4006)
DECL|macro|PLD_MMCBAUR
mdefine_line|#define PLD_MMCBAUR&t;&t;__reg16(PLD_BASE + 0x400a)
DECL|macro|PLD_MMCCMDBCUT
mdefine_line|#define PLD_MMCCMDBCUT&t;&t;__reg16(PLD_BASE + 0x400c)
DECL|macro|PLD_MMCCDTBCUT
mdefine_line|#define PLD_MMCCDTBCUT&t;&t;__reg16(PLD_BASE + 0x400e)
DECL|macro|PLD_MMCDET
mdefine_line|#define PLD_MMCDET&t;&t;__reg16(PLD_BASE + 0x4010)
DECL|macro|PLD_MMCWP
mdefine_line|#define PLD_MMCWP&t;&t;__reg16(PLD_BASE + 0x4012)
DECL|macro|PLD_MMCWDATA
mdefine_line|#define PLD_MMCWDATA&t;&t;__reg16(PLD_BASE + 0x5000)
DECL|macro|PLD_MMCRDATA
mdefine_line|#define PLD_MMCRDATA&t;&t;__reg16(PLD_BASE + 0x6000)
DECL|macro|PLD_MMCCMDDATA
mdefine_line|#define PLD_MMCCMDDATA&t;&t;__reg16(PLD_BASE + 0x7000)
DECL|macro|PLD_MMCRSPDATA
mdefine_line|#define PLD_MMCRSPDATA&t;&t;__reg16(PLD_BASE + 0x7006)
multiline_comment|/* ICU&n; *  ICUISTS:&t;status register&n; *  ICUIREQ0: &t;request register&n; *  ICUIREQ1: &t;request register&n; *  ICUCR3:&t;control register for CFIREQ# interrupt&n; *  ICUCR4:&t;control register for CFC Card insert interrupt&n; *  ICUCR5:&t;control register for CFC Card eject interrupt&n; *  ICUCR6:&t;control register for external interrupt&n; *  ICUCR11:&t;control register for MMC Card insert/eject interrupt&n; *  ICUCR13:&t;control register for SC error interrupt&n; *  ICUCR14:&t;control register for SC receive interrupt&n; *  ICUCR15:&t;control register for SC send interrupt&n; *  ICUCR16:&t;control register for SIO0 receive interrupt&n; *  ICUCR17:&t;control register for SIO0 send interrupt&n; */
macro_line|#if !defined(CONFIG_PLAT_USRV)
DECL|macro|PLD_IRQ_INT0
mdefine_line|#define PLD_IRQ_INT0&t;&t;(OPSPUT_PLD_IRQ_BASE + 0)&t;/* None */
DECL|macro|PLD_IRQ_INT1
mdefine_line|#define PLD_IRQ_INT1&t;&t;(OPSPUT_PLD_IRQ_BASE + 1)&t;/* reserved */
DECL|macro|PLD_IRQ_INT2
mdefine_line|#define PLD_IRQ_INT2&t;&t;(OPSPUT_PLD_IRQ_BASE + 2)&t;/* reserved */
DECL|macro|PLD_IRQ_CFIREQ
mdefine_line|#define PLD_IRQ_CFIREQ&t;&t;(OPSPUT_PLD_IRQ_BASE + 3)&t;/* CF IREQ */
DECL|macro|PLD_IRQ_CFC_INSERT
mdefine_line|#define PLD_IRQ_CFC_INSERT&t;(OPSPUT_PLD_IRQ_BASE + 4)&t;/* CF Insert */
DECL|macro|PLD_IRQ_CFC_EJECT
mdefine_line|#define PLD_IRQ_CFC_EJECT&t;(OPSPUT_PLD_IRQ_BASE + 5)&t;/* CF Eject */
DECL|macro|PLD_IRQ_EXINT
mdefine_line|#define PLD_IRQ_EXINT&t;&t;(OPSPUT_PLD_IRQ_BASE + 6)&t;/* EXINT */
DECL|macro|PLD_IRQ_INT7
mdefine_line|#define PLD_IRQ_INT7&t;&t;(OPSPUT_PLD_IRQ_BASE + 7)&t;/* reserved */
DECL|macro|PLD_IRQ_INT8
mdefine_line|#define PLD_IRQ_INT8&t;&t;(OPSPUT_PLD_IRQ_BASE + 8)&t;/* reserved */
DECL|macro|PLD_IRQ_INT9
mdefine_line|#define PLD_IRQ_INT9&t;&t;(OPSPUT_PLD_IRQ_BASE + 9)&t;/* reserved */
DECL|macro|PLD_IRQ_INT10
mdefine_line|#define PLD_IRQ_INT10&t;&t;(OPSPUT_PLD_IRQ_BASE + 10)&t;/* reserved */
DECL|macro|PLD_IRQ_MMCCARD
mdefine_line|#define PLD_IRQ_MMCCARD&t;&t;(OPSPUT_PLD_IRQ_BASE + 11)&t;/* MMC Insert/Eject */
DECL|macro|PLD_IRQ_INT12
mdefine_line|#define PLD_IRQ_INT12&t;&t;(OPSPUT_PLD_IRQ_BASE + 12)&t;/* reserved */
DECL|macro|PLD_IRQ_SC_ERROR
mdefine_line|#define PLD_IRQ_SC_ERROR&t;(OPSPUT_PLD_IRQ_BASE + 13)&t;/* SC error */
DECL|macro|PLD_IRQ_SC_RCV
mdefine_line|#define PLD_IRQ_SC_RCV&t;&t;(OPSPUT_PLD_IRQ_BASE + 14)&t;/* SC receive */
DECL|macro|PLD_IRQ_SC_SND
mdefine_line|#define PLD_IRQ_SC_SND&t;&t;(OPSPUT_PLD_IRQ_BASE + 15)&t;/* SC send */
DECL|macro|PLD_IRQ_SIO0_RCV
mdefine_line|#define PLD_IRQ_SIO0_RCV&t;(OPSPUT_PLD_IRQ_BASE + 16)&t;/* SIO receive */
DECL|macro|PLD_IRQ_SIO0_SND
mdefine_line|#define PLD_IRQ_SIO0_SND&t;(OPSPUT_PLD_IRQ_BASE + 17)&t;/* SIO send */
DECL|macro|PLD_IRQ_INT18
mdefine_line|#define PLD_IRQ_INT18&t;&t;(OPSPUT_PLD_IRQ_BASE + 18)&t;/* reserved */
DECL|macro|PLD_IRQ_INT19
mdefine_line|#define PLD_IRQ_INT19&t;&t;(OPSPUT_PLD_IRQ_BASE + 19)&t;/* reserved */
DECL|macro|PLD_IRQ_INT20
mdefine_line|#define PLD_IRQ_INT20&t;&t;(OPSPUT_PLD_IRQ_BASE + 20)&t;/* reserved */
DECL|macro|PLD_IRQ_INT21
mdefine_line|#define PLD_IRQ_INT21&t;&t;(OPSPUT_PLD_IRQ_BASE + 21)&t;/* reserved */
DECL|macro|PLD_IRQ_INT22
mdefine_line|#define PLD_IRQ_INT22&t;&t;(OPSPUT_PLD_IRQ_BASE + 22)&t;/* reserved */
DECL|macro|PLD_IRQ_INT23
mdefine_line|#define PLD_IRQ_INT23&t;&t;(OPSPUT_PLD_IRQ_BASE + 23)&t;/* reserved */
DECL|macro|PLD_IRQ_INT24
mdefine_line|#define PLD_IRQ_INT24&t;&t;(OPSPUT_PLD_IRQ_BASE + 24)&t;/* reserved */
DECL|macro|PLD_IRQ_INT25
mdefine_line|#define PLD_IRQ_INT25&t;&t;(OPSPUT_PLD_IRQ_BASE + 25)&t;/* reserved */
DECL|macro|PLD_IRQ_INT26
mdefine_line|#define PLD_IRQ_INT26&t;&t;(OPSPUT_PLD_IRQ_BASE + 26)&t;/* reserved */
DECL|macro|PLD_IRQ_INT27
mdefine_line|#define PLD_IRQ_INT27&t;&t;(OPSPUT_PLD_IRQ_BASE + 27)&t;/* reserved */
DECL|macro|PLD_IRQ_INT28
mdefine_line|#define PLD_IRQ_INT28&t;&t;(OPSPUT_PLD_IRQ_BASE + 28)&t;/* reserved */
DECL|macro|PLD_IRQ_INT29
mdefine_line|#define PLD_IRQ_INT29&t;&t;(OPSPUT_PLD_IRQ_BASE + 29)&t;/* reserved */
DECL|macro|PLD_IRQ_INT30
mdefine_line|#define PLD_IRQ_INT30&t;&t;(OPSPUT_PLD_IRQ_BASE + 30)&t;/* reserved */
DECL|macro|PLD_IRQ_INT31
mdefine_line|#define PLD_IRQ_INT31&t;&t;(OPSPUT_PLD_IRQ_BASE + 31)&t;/* reserved */
macro_line|#else&t;/* CONFIG_PLAT_USRV */
DECL|macro|PLD_IRQ_INT0
mdefine_line|#define PLD_IRQ_INT0&t;&t;(OPSPUT_PLD_IRQ_BASE + 0)&t;/* None */
DECL|macro|PLD_IRQ_INT1
mdefine_line|#define PLD_IRQ_INT1&t;&t;(OPSPUT_PLD_IRQ_BASE + 1)&t;/* reserved */
DECL|macro|PLD_IRQ_INT2
mdefine_line|#define PLD_IRQ_INT2&t;&t;(OPSPUT_PLD_IRQ_BASE + 2)&t;/* reserved */
DECL|macro|PLD_IRQ_CF0
mdefine_line|#define PLD_IRQ_CF0&t;&t;(OPSPUT_PLD_IRQ_BASE + 3)&t;/* CF0# */
DECL|macro|PLD_IRQ_CF1
mdefine_line|#define PLD_IRQ_CF1&t;&t;(OPSPUT_PLD_IRQ_BASE + 4)&t;/* CF1# */
DECL|macro|PLD_IRQ_CF2
mdefine_line|#define PLD_IRQ_CF2&t;&t;(OPSPUT_PLD_IRQ_BASE + 5)&t;/* CF2# */
DECL|macro|PLD_IRQ_CF3
mdefine_line|#define PLD_IRQ_CF3&t;&t;(OPSPUT_PLD_IRQ_BASE + 6)&t;/* CF3# */
DECL|macro|PLD_IRQ_CF4
mdefine_line|#define PLD_IRQ_CF4&t;&t;(OPSPUT_PLD_IRQ_BASE + 7)&t;/* CF4# */
DECL|macro|PLD_IRQ_INT8
mdefine_line|#define PLD_IRQ_INT8&t;&t;(OPSPUT_PLD_IRQ_BASE + 8)&t;/* reserved */
DECL|macro|PLD_IRQ_INT9
mdefine_line|#define PLD_IRQ_INT9&t;&t;(OPSPUT_PLD_IRQ_BASE + 9)&t;/* reserved */
DECL|macro|PLD_IRQ_INT10
mdefine_line|#define PLD_IRQ_INT10&t;&t;(OPSPUT_PLD_IRQ_BASE + 10)&t;/* reserved */
DECL|macro|PLD_IRQ_INT11
mdefine_line|#define PLD_IRQ_INT11&t;&t;(OPSPUT_PLD_IRQ_BASE + 11)&t;/* reserved */
DECL|macro|PLD_IRQ_UART0
mdefine_line|#define PLD_IRQ_UART0&t;&t;(OPSPUT_PLD_IRQ_BASE + 12)&t;/* UARTIRQ0 */
DECL|macro|PLD_IRQ_UART1
mdefine_line|#define PLD_IRQ_UART1&t;&t;(OPSPUT_PLD_IRQ_BASE + 13)&t;/* UARTIRQ1 */
DECL|macro|PLD_IRQ_INT14
mdefine_line|#define PLD_IRQ_INT14&t;&t;(OPSPUT_PLD_IRQ_BASE + 14)&t;/* reserved */
DECL|macro|PLD_IRQ_INT15
mdefine_line|#define PLD_IRQ_INT15&t;&t;(OPSPUT_PLD_IRQ_BASE + 15)&t;/* reserved */
DECL|macro|PLD_IRQ_SNDINT
mdefine_line|#define PLD_IRQ_SNDINT&t;&t;(OPSPUT_PLD_IRQ_BASE + 16)&t;/* SNDINT# */
DECL|macro|PLD_IRQ_INT17
mdefine_line|#define PLD_IRQ_INT17&t;&t;(OPSPUT_PLD_IRQ_BASE + 17)&t;/* reserved */
DECL|macro|PLD_IRQ_INT18
mdefine_line|#define PLD_IRQ_INT18&t;&t;(OPSPUT_PLD_IRQ_BASE + 18)&t;/* reserved */
DECL|macro|PLD_IRQ_INT19
mdefine_line|#define PLD_IRQ_INT19&t;&t;(OPSPUT_PLD_IRQ_BASE + 19)&t;/* reserved */
DECL|macro|PLD_IRQ_INT20
mdefine_line|#define PLD_IRQ_INT20&t;&t;(OPSPUT_PLD_IRQ_BASE + 20)&t;/* reserved */
DECL|macro|PLD_IRQ_INT21
mdefine_line|#define PLD_IRQ_INT21&t;&t;(OPSPUT_PLD_IRQ_BASE + 21)&t;/* reserved */
DECL|macro|PLD_IRQ_INT22
mdefine_line|#define PLD_IRQ_INT22&t;&t;(OPSPUT_PLD_IRQ_BASE + 22)&t;/* reserved */
DECL|macro|PLD_IRQ_INT23
mdefine_line|#define PLD_IRQ_INT23&t;&t;(OPSPUT_PLD_IRQ_BASE + 23)&t;/* reserved */
DECL|macro|PLD_IRQ_INT24
mdefine_line|#define PLD_IRQ_INT24&t;&t;(OPSPUT_PLD_IRQ_BASE + 24)&t;/* reserved */
DECL|macro|PLD_IRQ_INT25
mdefine_line|#define PLD_IRQ_INT25&t;&t;(OPSPUT_PLD_IRQ_BASE + 25)&t;/* reserved */
DECL|macro|PLD_IRQ_INT26
mdefine_line|#define PLD_IRQ_INT26&t;&t;(OPSPUT_PLD_IRQ_BASE + 26)&t;/* reserved */
DECL|macro|PLD_IRQ_INT27
mdefine_line|#define PLD_IRQ_INT27&t;&t;(OPSPUT_PLD_IRQ_BASE + 27)&t;/* reserved */
DECL|macro|PLD_IRQ_INT28
mdefine_line|#define PLD_IRQ_INT28&t;&t;(OPSPUT_PLD_IRQ_BASE + 28)&t;/* reserved */
DECL|macro|PLD_IRQ_INT29
mdefine_line|#define PLD_IRQ_INT29&t;&t;(OPSPUT_PLD_IRQ_BASE + 29)&t;/* reserved */
DECL|macro|PLD_IRQ_INT30
mdefine_line|#define PLD_IRQ_INT30&t;&t;(OPSPUT_PLD_IRQ_BASE + 30)&t;/* reserved */
macro_line|#endif&t;/* CONFIG_PLAT_USRV */
DECL|macro|PLD_ICUISTS
mdefine_line|#define PLD_ICUISTS&t;&t;__reg16(PLD_BASE + 0x8002)
DECL|macro|PLD_ICUISTS_VECB_MASK
mdefine_line|#define PLD_ICUISTS_VECB_MASK&t;(0xf000)
DECL|macro|PLD_ICUISTS_VECB
mdefine_line|#define PLD_ICUISTS_VECB(x)&t;((x) &amp; PLD_ICUISTS_VECB_MASK)
DECL|macro|PLD_ICUISTS_ISN_MASK
mdefine_line|#define PLD_ICUISTS_ISN_MASK&t;(0x07c0)
DECL|macro|PLD_ICUISTS_ISN
mdefine_line|#define PLD_ICUISTS_ISN(x)&t;((x) &amp; PLD_ICUISTS_ISN_MASK)
DECL|macro|PLD_ICUIREQ0
mdefine_line|#define PLD_ICUIREQ0&t;&t;__reg16(PLD_BASE + 0x8004)
DECL|macro|PLD_ICUIREQ1
mdefine_line|#define PLD_ICUIREQ1&t;&t;__reg16(PLD_BASE + 0x8006)
DECL|macro|PLD_ICUCR1
mdefine_line|#define PLD_ICUCR1&t;&t;__reg16(PLD_BASE + 0x8100)
DECL|macro|PLD_ICUCR2
mdefine_line|#define PLD_ICUCR2&t;&t;__reg16(PLD_BASE + 0x8102)
DECL|macro|PLD_ICUCR3
mdefine_line|#define PLD_ICUCR3&t;&t;__reg16(PLD_BASE + 0x8104)
DECL|macro|PLD_ICUCR4
mdefine_line|#define PLD_ICUCR4&t;&t;__reg16(PLD_BASE + 0x8106)
DECL|macro|PLD_ICUCR5
mdefine_line|#define PLD_ICUCR5&t;&t;__reg16(PLD_BASE + 0x8108)
DECL|macro|PLD_ICUCR6
mdefine_line|#define PLD_ICUCR6&t;&t;__reg16(PLD_BASE + 0x810a)
DECL|macro|PLD_ICUCR7
mdefine_line|#define PLD_ICUCR7&t;&t;__reg16(PLD_BASE + 0x810c)
DECL|macro|PLD_ICUCR8
mdefine_line|#define PLD_ICUCR8&t;&t;__reg16(PLD_BASE + 0x810e)
DECL|macro|PLD_ICUCR9
mdefine_line|#define PLD_ICUCR9&t;&t;__reg16(PLD_BASE + 0x8110)
DECL|macro|PLD_ICUCR10
mdefine_line|#define PLD_ICUCR10&t;&t;__reg16(PLD_BASE + 0x8112)
DECL|macro|PLD_ICUCR11
mdefine_line|#define PLD_ICUCR11&t;&t;__reg16(PLD_BASE + 0x8114)
DECL|macro|PLD_ICUCR12
mdefine_line|#define PLD_ICUCR12&t;&t;__reg16(PLD_BASE + 0x8116)
DECL|macro|PLD_ICUCR13
mdefine_line|#define PLD_ICUCR13&t;&t;__reg16(PLD_BASE + 0x8118)
DECL|macro|PLD_ICUCR14
mdefine_line|#define PLD_ICUCR14&t;&t;__reg16(PLD_BASE + 0x811a)
DECL|macro|PLD_ICUCR15
mdefine_line|#define PLD_ICUCR15&t;&t;__reg16(PLD_BASE + 0x811c)
DECL|macro|PLD_ICUCR16
mdefine_line|#define PLD_ICUCR16&t;&t;__reg16(PLD_BASE + 0x811e)
DECL|macro|PLD_ICUCR17
mdefine_line|#define PLD_ICUCR17&t;&t;__reg16(PLD_BASE + 0x8120)
DECL|macro|PLD_ICUCR_IEN
mdefine_line|#define PLD_ICUCR_IEN&t;&t;(0x1000)
DECL|macro|PLD_ICUCR_IREQ
mdefine_line|#define PLD_ICUCR_IREQ&t;&t;(0x0100)
DECL|macro|PLD_ICUCR_ISMOD00
mdefine_line|#define PLD_ICUCR_ISMOD00&t;(0x0000)&t;/* Low edge */
DECL|macro|PLD_ICUCR_ISMOD01
mdefine_line|#define PLD_ICUCR_ISMOD01&t;(0x0010)&t;/* Low level */
DECL|macro|PLD_ICUCR_ISMOD02
mdefine_line|#define PLD_ICUCR_ISMOD02&t;(0x0020)&t;/* High edge */
DECL|macro|PLD_ICUCR_ISMOD03
mdefine_line|#define PLD_ICUCR_ISMOD03&t;(0x0030)&t;/* High level */
DECL|macro|PLD_ICUCR_ILEVEL0
mdefine_line|#define PLD_ICUCR_ILEVEL0&t;(0x0000)
DECL|macro|PLD_ICUCR_ILEVEL1
mdefine_line|#define PLD_ICUCR_ILEVEL1&t;(0x0001)
DECL|macro|PLD_ICUCR_ILEVEL2
mdefine_line|#define PLD_ICUCR_ILEVEL2&t;(0x0002)
DECL|macro|PLD_ICUCR_ILEVEL3
mdefine_line|#define PLD_ICUCR_ILEVEL3&t;(0x0003)
DECL|macro|PLD_ICUCR_ILEVEL4
mdefine_line|#define PLD_ICUCR_ILEVEL4&t;(0x0004)
DECL|macro|PLD_ICUCR_ILEVEL5
mdefine_line|#define PLD_ICUCR_ILEVEL5&t;(0x0005)
DECL|macro|PLD_ICUCR_ILEVEL6
mdefine_line|#define PLD_ICUCR_ILEVEL6&t;(0x0006)
DECL|macro|PLD_ICUCR_ILEVEL7
mdefine_line|#define PLD_ICUCR_ILEVEL7&t;(0x0007)
multiline_comment|/* Power Control of MMC and CF */
DECL|macro|PLD_CPCR
mdefine_line|#define PLD_CPCR&t;&t;__reg16(PLD_BASE + 0x14000)
DECL|macro|PLD_CPCR_CF
mdefine_line|#define PLD_CPCR_CF&t;&t;0x0001
DECL|macro|PLD_CPCR_MMC
mdefine_line|#define PLD_CPCR_MMC&t;&t;0x0002
multiline_comment|/* LED Control&n; *&n; * 1: DIP swich side&n; * 2: Reset switch side&n; */
DECL|macro|PLD_IOLEDCR
mdefine_line|#define PLD_IOLEDCR&t;&t;__reg16(PLD_BASE + 0x14002)
DECL|macro|PLD_IOLED_1_ON
mdefine_line|#define PLD_IOLED_1_ON&t;&t;0x001
DECL|macro|PLD_IOLED_1_OFF
mdefine_line|#define PLD_IOLED_1_OFF&t;&t;0x000
DECL|macro|PLD_IOLED_2_ON
mdefine_line|#define PLD_IOLED_2_ON&t;&t;0x002
DECL|macro|PLD_IOLED_2_OFF
mdefine_line|#define PLD_IOLED_2_OFF&t;&t;0x000
multiline_comment|/* DIP Switch&n; *  0: Write-protect of Flash Memory (0:protected, 1:non-protected)&n; *  1: -&n; *  2: -&n; *  3: -&n; */
DECL|macro|PLD_IOSWSTS
mdefine_line|#define PLD_IOSWSTS&t;&t;__reg16(PLD_BASE + 0x14004)
DECL|macro|PLD_IOSWSTS_IOSW2
mdefine_line|#define&t;PLD_IOSWSTS_IOSW2&t;0x0200
DECL|macro|PLD_IOSWSTS_IOSW1
mdefine_line|#define&t;PLD_IOSWSTS_IOSW1&t;0x0100
DECL|macro|PLD_IOSWSTS_IOWP0
mdefine_line|#define&t;PLD_IOSWSTS_IOWP0&t;0x0001
multiline_comment|/* CRC */
DECL|macro|PLD_CRC7DATA
mdefine_line|#define PLD_CRC7DATA&t;&t;__reg16(PLD_BASE + 0x18000)
DECL|macro|PLD_CRC7INDATA
mdefine_line|#define PLD_CRC7INDATA&t;&t;__reg16(PLD_BASE + 0x18002)
DECL|macro|PLD_CRC16DATA
mdefine_line|#define PLD_CRC16DATA&t;&t;__reg16(PLD_BASE + 0x18004)
DECL|macro|PLD_CRC16INDATA
mdefine_line|#define PLD_CRC16INDATA&t;&t;__reg16(PLD_BASE + 0x18006)
DECL|macro|PLD_CRC16ADATA
mdefine_line|#define PLD_CRC16ADATA&t;&t;__reg16(PLD_BASE + 0x18008)
DECL|macro|PLD_CRC16AINDATA
mdefine_line|#define PLD_CRC16AINDATA&t;__reg16(PLD_BASE + 0x1800a)
multiline_comment|/* RTC */
DECL|macro|PLD_RTCCR
mdefine_line|#define PLD_RTCCR&t;&t;__reg16(PLD_BASE + 0x1c000)
DECL|macro|PLD_RTCBAUR
mdefine_line|#define PLD_RTCBAUR&t;&t;__reg16(PLD_BASE + 0x1c002)
DECL|macro|PLD_RTCWRDATA
mdefine_line|#define PLD_RTCWRDATA&t;&t;__reg16(PLD_BASE + 0x1c004)
DECL|macro|PLD_RTCRDDATA
mdefine_line|#define PLD_RTCRDDATA&t;&t;__reg16(PLD_BASE + 0x1c006)
DECL|macro|PLD_RTCRSTODT
mdefine_line|#define PLD_RTCRSTODT&t;&t;__reg16(PLD_BASE + 0x1c008)
multiline_comment|/* SIO0 */
DECL|macro|PLD_ESIO0CR
mdefine_line|#define PLD_ESIO0CR&t;&t;__reg16(PLD_BASE + 0x20000)
DECL|macro|PLD_ESIO0CR_TXEN
mdefine_line|#define&t;PLD_ESIO0CR_TXEN&t;0x0001
DECL|macro|PLD_ESIO0CR_RXEN
mdefine_line|#define&t;PLD_ESIO0CR_RXEN&t;0x0002
DECL|macro|PLD_ESIO0MOD0
mdefine_line|#define PLD_ESIO0MOD0&t;&t;__reg16(PLD_BASE + 0x20002)
DECL|macro|PLD_ESIO0MOD0_CTSS
mdefine_line|#define&t;PLD_ESIO0MOD0_CTSS&t;0x0040
DECL|macro|PLD_ESIO0MOD0_RTSS
mdefine_line|#define&t;PLD_ESIO0MOD0_RTSS&t;0x0080
DECL|macro|PLD_ESIO0MOD1
mdefine_line|#define PLD_ESIO0MOD1&t;&t;__reg16(PLD_BASE + 0x20004)
DECL|macro|PLD_ESIO0MOD1_LMFS
mdefine_line|#define&t;PLD_ESIO0MOD1_LMFS&t;0x0010
DECL|macro|PLD_ESIO0STS
mdefine_line|#define PLD_ESIO0STS&t;&t;__reg16(PLD_BASE + 0x20006)
DECL|macro|PLD_ESIO0STS_TEMP
mdefine_line|#define&t;PLD_ESIO0STS_TEMP&t;0x0001
DECL|macro|PLD_ESIO0STS_TXCP
mdefine_line|#define&t;PLD_ESIO0STS_TXCP&t;0x0002
DECL|macro|PLD_ESIO0STS_RXCP
mdefine_line|#define&t;PLD_ESIO0STS_RXCP&t;0x0004
DECL|macro|PLD_ESIO0STS_TXSC
mdefine_line|#define&t;PLD_ESIO0STS_TXSC&t;0x0100
DECL|macro|PLD_ESIO0STS_RXSC
mdefine_line|#define&t;PLD_ESIO0STS_RXSC&t;0x0200
DECL|macro|PLD_ESIO0STS_TXREADY
mdefine_line|#define PLD_ESIO0STS_TXREADY&t;(PLD_ESIO0STS_TXCP | PLD_ESIO0STS_TEMP)
DECL|macro|PLD_ESIO0INTCR
mdefine_line|#define PLD_ESIO0INTCR&t;&t;__reg16(PLD_BASE + 0x20008)
DECL|macro|PLD_ESIO0INTCR_TXIEN
mdefine_line|#define&t;PLD_ESIO0INTCR_TXIEN&t;0x0002
DECL|macro|PLD_ESIO0INTCR_RXCEN
mdefine_line|#define&t;PLD_ESIO0INTCR_RXCEN&t;0x0004
DECL|macro|PLD_ESIO0BAUR
mdefine_line|#define PLD_ESIO0BAUR&t;&t;__reg16(PLD_BASE + 0x2000a)
DECL|macro|PLD_ESIO0TXB
mdefine_line|#define PLD_ESIO0TXB&t;&t;__reg16(PLD_BASE + 0x2000c)
DECL|macro|PLD_ESIO0RXB
mdefine_line|#define PLD_ESIO0RXB&t;&t;__reg16(PLD_BASE + 0x2000e)
multiline_comment|/* SIM Card */
DECL|macro|PLD_SCCR
mdefine_line|#define PLD_SCCR&t;&t;__reg16(PLD_BASE + 0x38000)
DECL|macro|PLD_SCMOD
mdefine_line|#define PLD_SCMOD&t;&t;__reg16(PLD_BASE + 0x38004)
DECL|macro|PLD_SCSTS
mdefine_line|#define PLD_SCSTS&t;&t;__reg16(PLD_BASE + 0x38006)
DECL|macro|PLD_SCINTCR
mdefine_line|#define PLD_SCINTCR&t;&t;__reg16(PLD_BASE + 0x38008)
DECL|macro|PLD_SCBAUR
mdefine_line|#define PLD_SCBAUR&t;&t;__reg16(PLD_BASE + 0x3800a)
DECL|macro|PLD_SCTXB
mdefine_line|#define PLD_SCTXB&t;&t;__reg16(PLD_BASE + 0x3800c)
DECL|macro|PLD_SCRXB
mdefine_line|#define PLD_SCRXB&t;&t;__reg16(PLD_BASE + 0x3800e)
macro_line|#endif&t;/* _OPSPUT_OPSPUT_PLD.H */
eof
