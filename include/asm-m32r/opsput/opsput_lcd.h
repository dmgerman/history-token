multiline_comment|/*&n; * include/asm/opsput_lcd.h&n; *&n; * OPSPUT-LCD board&n; *&n; * Copyright (c) 2002&t;Takeo Takahashi&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file &quot;COPYING&quot; in the main directory of&n; * this archive for more details.&n; *&n; * $Id: opsput_lcd.h,v 1.1 2004/07/27 06:54:20 sakugawa Exp $&n; */
macro_line|#ifndef _OPSPUT_OPSPUT_LCD_H
DECL|macro|_OPSPUT_OPSPUT_LCD_H
mdefine_line|#define _OPSPUT_OPSPUT_LCD_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * C functions use non-cache address.&n; */
DECL|macro|OPSPUT_LCD_BASE
mdefine_line|#define OPSPUT_LCD_BASE&t;(0x10000000 /* + NONCACHE_OFFSET */)
macro_line|#else
DECL|macro|OPSPUT_LCD_BASE
mdefine_line|#define OPSPUT_LCD_BASE&t;(0x10000000 + NONCACHE_OFFSET)
macro_line|#endif&t;/* __ASSEMBLY__ */
multiline_comment|/*&n; * ICU&n; */
DECL|macro|OPSPUT_LCD_IRQ_BAT_INT
mdefine_line|#define OPSPUT_LCD_IRQ_BAT_INT&t;(OPSPUT_LCD_PLD_IRQ_BASE + 1)
DECL|macro|OPSPUT_LCD_IRQ_USB_INT1
mdefine_line|#define OPSPUT_LCD_IRQ_USB_INT1&t;(OPSPUT_LCD_PLD_IRQ_BASE + 2)
DECL|macro|OPSPUT_LCD_IRQ_AUDT0
mdefine_line|#define OPSPUT_LCD_IRQ_AUDT0&t;&t;(OPSPUT_LCD_PLD_IRQ_BASE + 3)
DECL|macro|OPSPUT_LCD_IRQ_AUDT2
mdefine_line|#define OPSPUT_LCD_IRQ_AUDT2&t;&t;(OPSPUT_LCD_PLD_IRQ_BASE + 4)
DECL|macro|OPSPUT_LCD_IRQ_BATSIO_RCV
mdefine_line|#define OPSPUT_LCD_IRQ_BATSIO_RCV&t;(OPSPUT_LCD_PLD_IRQ_BASE + 16)
DECL|macro|OPSPUT_LCD_IRQ_BATSIO_SND
mdefine_line|#define OPSPUT_LCD_IRQ_BATSIO_SND&t;(OPSPUT_LCD_PLD_IRQ_BASE + 17)
DECL|macro|OPSPUT_LCD_IRQ_ASNDSIO_RCV
mdefine_line|#define OPSPUT_LCD_IRQ_ASNDSIO_RCV&t;(OPSPUT_LCD_PLD_IRQ_BASE + 18)
DECL|macro|OPSPUT_LCD_IRQ_ASNDSIO_SND
mdefine_line|#define OPSPUT_LCD_IRQ_ASNDSIO_SND&t;(OPSPUT_LCD_PLD_IRQ_BASE + 19)
DECL|macro|OPSPUT_LCD_IRQ_ACNLSIO_SND
mdefine_line|#define OPSPUT_LCD_IRQ_ACNLSIO_SND&t;(OPSPUT_LCD_PLD_IRQ_BASE + 21)
DECL|macro|OPSPUT_LCD_ICUISTS
mdefine_line|#define OPSPUT_LCD_ICUISTS&t;__reg16(OPSPUT_LCD_BASE + 0x300002)
DECL|macro|OPSPUT_LCD_ICUISTS_VECB_MASK
mdefine_line|#define OPSPUT_LCD_ICUISTS_VECB_MASK&t;(0xf000)
DECL|macro|OPSPUT_LCD_VECB
mdefine_line|#define OPSPUT_LCD_VECB(x)&t;((x) &amp; OPSPUT_LCD_ICUISTS_VECB_MASK)
DECL|macro|OPSPUT_LCD_ICUISTS_ISN_MASK
mdefine_line|#define OPSPUT_LCD_ICUISTS_ISN_MASK&t;(0x07c0)
DECL|macro|OPSPUT_LCD_ICUISTS_ISN
mdefine_line|#define OPSPUT_LCD_ICUISTS_ISN(x)&t;((x) &amp; OPSPUT_LCD_ICUISTS_ISN_MASK)
DECL|macro|OPSPUT_LCD_ICUIREQ0
mdefine_line|#define OPSPUT_LCD_ICUIREQ0&t;__reg16(OPSPUT_LCD_BASE + 0x300004)
DECL|macro|OPSPUT_LCD_ICUIREQ1
mdefine_line|#define OPSPUT_LCD_ICUIREQ1&t;__reg16(OPSPUT_LCD_BASE + 0x300006)
DECL|macro|OPSPUT_LCD_ICUCR1
mdefine_line|#define OPSPUT_LCD_ICUCR1&t;__reg16(OPSPUT_LCD_BASE + 0x300020)
DECL|macro|OPSPUT_LCD_ICUCR2
mdefine_line|#define OPSPUT_LCD_ICUCR2&t;__reg16(OPSPUT_LCD_BASE + 0x300022)
DECL|macro|OPSPUT_LCD_ICUCR3
mdefine_line|#define OPSPUT_LCD_ICUCR3&t;__reg16(OPSPUT_LCD_BASE + 0x300024)
DECL|macro|OPSPUT_LCD_ICUCR4
mdefine_line|#define OPSPUT_LCD_ICUCR4&t;__reg16(OPSPUT_LCD_BASE + 0x300026)
DECL|macro|OPSPUT_LCD_ICUCR16
mdefine_line|#define OPSPUT_LCD_ICUCR16&t;__reg16(OPSPUT_LCD_BASE + 0x300030)
DECL|macro|OPSPUT_LCD_ICUCR17
mdefine_line|#define OPSPUT_LCD_ICUCR17&t;__reg16(OPSPUT_LCD_BASE + 0x300032)
DECL|macro|OPSPUT_LCD_ICUCR18
mdefine_line|#define OPSPUT_LCD_ICUCR18&t;__reg16(OPSPUT_LCD_BASE + 0x300034)
DECL|macro|OPSPUT_LCD_ICUCR19
mdefine_line|#define OPSPUT_LCD_ICUCR19&t;__reg16(OPSPUT_LCD_BASE + 0x300036)
DECL|macro|OPSPUT_LCD_ICUCR21
mdefine_line|#define OPSPUT_LCD_ICUCR21&t;__reg16(OPSPUT_LCD_BASE + 0x30003a)
macro_line|#endif&t;/* _OPSPUT_OPSPUT_LCD_H */
eof
