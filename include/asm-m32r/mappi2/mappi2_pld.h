multiline_comment|/*&n; * include/asm/mappi2/mappi2_pld.h&n; *&n; * Definitions for Extended IO Logic on MAPPI2 board.&n; *  based on m32700ut_pld.h by&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file &quot;COPYING&quot; in the main directory of&n; * this archive for more details.&n; *&n; */
macro_line|#ifndef _MAPPI2_PLD_H
DECL|macro|_MAPPI2_PLD_H
mdefine_line|#define _MAPPI2_PLD_H
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* FIXME:&n; * Some C functions use non-cache address, so can&squot;t define non-cache address.&n; */
DECL|macro|PLD_BASE
mdefine_line|#define PLD_BASE&t;&t;(0x10c00000 /* + NONCACHE_OFFSET */)
DECL|macro|__reg8
mdefine_line|#define __reg8&t;&t;&t;(volatile unsigned char *)
DECL|macro|__reg16
mdefine_line|#define __reg16&t;&t;&t;(volatile unsigned short *)
DECL|macro|__reg32
mdefine_line|#define __reg32&t;&t;&t;(volatile unsigned int *)
macro_line|#else
DECL|macro|PLD_BASE
mdefine_line|#define PLD_BASE&t;&t;(0x10c00000 + NONCACHE_OFFSET)
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
DECL|macro|PLD_CFCR0
mdefine_line|#define PLD_CFCR0&t;&t;__reg16(PLD_BASE + 0x000a)
DECL|macro|PLD_CFCR1
mdefine_line|#define PLD_CFCR1&t;&t;__reg16(PLD_BASE + 0x000c)
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
multiline_comment|/* Power Control of MMC and CF */
DECL|macro|PLD_CPCR
mdefine_line|#define PLD_CPCR&t;&t;__reg16(PLD_BASE + 0x14000)
multiline_comment|/*==== ICU ====*/
DECL|macro|M32R_IRQ_PC104
mdefine_line|#define  M32R_IRQ_PC104        (5)   /* INT4(PC/104) */
DECL|macro|M32R_IRQ_I2C
mdefine_line|#define  M32R_IRQ_I2C          (28)  /* I2C-BUS     */
macro_line|#if 1
DECL|macro|PLD_IRQ_CFIREQ
mdefine_line|#define  PLD_IRQ_CFIREQ       (40)  /* CFC Card Interrupt */
DECL|macro|PLD_IRQ_CFC_INSERT
mdefine_line|#define  PLD_IRQ_CFC_INSERT   (41)  /* CFC Card Insert */
DECL|macro|PLD_IRQ_CFC_EJECT
mdefine_line|#define  PLD_IRQ_CFC_EJECT    (42)  /* CFC Card Eject */
DECL|macro|PLD_IRQ_MMCCARD
mdefine_line|#define  PLD_IRQ_MMCCARD      (43)  /* MMC Card Insert */
DECL|macro|PLD_IRQ_MMCIRQ
mdefine_line|#define  PLD_IRQ_MMCIRQ       (44)  /* MMC Transfer Done */
macro_line|#else
DECL|macro|PLD_IRQ_CFIREQ
mdefine_line|#define  PLD_IRQ_CFIREQ       (34)  /* CFC Card Interrupt */
DECL|macro|PLD_IRQ_CFC_INSERT
mdefine_line|#define  PLD_IRQ_CFC_INSERT   (35)  /* CFC Card Insert */
DECL|macro|PLD_IRQ_CFC_EJECT
mdefine_line|#define  PLD_IRQ_CFC_EJECT    (36)  /* CFC Card Eject */
DECL|macro|PLD_IRQ_MMCCARD
mdefine_line|#define  PLD_IRQ_MMCCARD      (37)  /* MMC Card Insert */
DECL|macro|PLD_IRQ_MMCIRQ
mdefine_line|#define  PLD_IRQ_MMCIRQ       (38)  /* MMC Transfer Done */
macro_line|#endif
macro_line|#if 0
multiline_comment|/* LED Control&n; *&n; * 1: DIP swich side&n; * 2: Reset switch side&n; */
mdefine_line|#define PLD_IOLEDCR&t;&t;__reg16(PLD_BASE + 0x14002)
mdefine_line|#define PLD_IOLED_1_ON&t;&t;0x001
mdefine_line|#define PLD_IOLED_1_OFF&t;&t;0x000
mdefine_line|#define PLD_IOLED_2_ON&t;&t;0x002
mdefine_line|#define PLD_IOLED_2_OFF&t;&t;0x000
multiline_comment|/* DIP Switch&n; *  0: Write-protect of Flash Memory (0:protected, 1:non-protected)&n; *  1: -&n; *  2: -&n; *  3: -&n; */
mdefine_line|#define PLD_IOSWSTS&t;&t;__reg16(PLD_BASE + 0x14004)
mdefine_line|#define&t;PLD_IOSWSTS_IOSW2&t;0x0200
mdefine_line|#define&t;PLD_IOSWSTS_IOSW1&t;0x0100
mdefine_line|#define&t;PLD_IOSWSTS_IOWP0&t;0x0001
macro_line|#endif
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
macro_line|#if 0
multiline_comment|/* RTC */
mdefine_line|#define PLD_RTCCR&t;&t;__reg16(PLD_BASE + 0x1c000)
mdefine_line|#define PLD_RTCBAUR&t;&t;__reg16(PLD_BASE + 0x1c002)
mdefine_line|#define PLD_RTCWRDATA&t;&t;__reg16(PLD_BASE + 0x1c004)
mdefine_line|#define PLD_RTCRDDATA&t;&t;__reg16(PLD_BASE + 0x1c006)
mdefine_line|#define PLD_RTCRSTODT&t;&t;__reg16(PLD_BASE + 0x1c008)
multiline_comment|/* SIO0 */
mdefine_line|#define PLD_ESIO0CR&t;&t;__reg16(PLD_BASE + 0x20000)
mdefine_line|#define&t;PLD_ESIO0CR_TXEN&t;0x0001
mdefine_line|#define&t;PLD_ESIO0CR_RXEN&t;0x0002
mdefine_line|#define PLD_ESIO0MOD0&t;&t;__reg16(PLD_BASE + 0x20002)
mdefine_line|#define&t;PLD_ESIO0MOD0_CTSS&t;0x0040
mdefine_line|#define&t;PLD_ESIO0MOD0_RTSS&t;0x0080
mdefine_line|#define PLD_ESIO0MOD1&t;&t;__reg16(PLD_BASE + 0x20004)
mdefine_line|#define&t;PLD_ESIO0MOD1_LMFS&t;0x0010
mdefine_line|#define PLD_ESIO0STS&t;&t;__reg16(PLD_BASE + 0x20006)
mdefine_line|#define&t;PLD_ESIO0STS_TEMP&t;0x0001
mdefine_line|#define&t;PLD_ESIO0STS_TXCP&t;0x0002
mdefine_line|#define&t;PLD_ESIO0STS_RXCP&t;0x0004
mdefine_line|#define&t;PLD_ESIO0STS_TXSC&t;0x0100
mdefine_line|#define&t;PLD_ESIO0STS_RXSC&t;0x0200
mdefine_line|#define PLD_ESIO0STS_TXREADY&t;(PLD_ESIO0STS_TXCP | PLD_ESIO0STS_TEMP)
mdefine_line|#define PLD_ESIO0INTCR&t;&t;__reg16(PLD_BASE + 0x20008)
mdefine_line|#define&t;PLD_ESIO0INTCR_TXIEN&t;0x0002
mdefine_line|#define&t;PLD_ESIO0INTCR_RXCEN&t;0x0004
mdefine_line|#define PLD_ESIO0BAUR&t;&t;__reg16(PLD_BASE + 0x2000a)
mdefine_line|#define PLD_ESIO0TXB&t;&t;__reg16(PLD_BASE + 0x2000c)
mdefine_line|#define PLD_ESIO0RXB&t;&t;__reg16(PLD_BASE + 0x2000e)
multiline_comment|/* SIM Card */
mdefine_line|#define PLD_SCCR&t;&t;__reg16(PLD_BASE + 0x38000)
mdefine_line|#define PLD_SCMOD&t;&t;__reg16(PLD_BASE + 0x38004)
mdefine_line|#define PLD_SCSTS&t;&t;__reg16(PLD_BASE + 0x38006)
mdefine_line|#define PLD_SCINTCR&t;&t;__reg16(PLD_BASE + 0x38008)
mdefine_line|#define PLD_SCBAUR&t;&t;__reg16(PLD_BASE + 0x3800a)
mdefine_line|#define PLD_SCTXB&t;&t;__reg16(PLD_BASE + 0x3800c)
mdefine_line|#define PLD_SCRXB&t;&t;__reg16(PLD_BASE + 0x3800e)
macro_line|#endif
macro_line|#endif&t;/* _MAPPI2_PLD.H */
eof
