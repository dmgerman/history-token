multiline_comment|/*&n; * include/asm/opsput_lan.h&n; *&n; * OPSPUT-LAN board&n; *&n; * Copyright (c) 2002-2004&t;Takeo Takahashi, Mamoru Sakugawa&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file &quot;COPYING&quot; in the main directory of&n; * this archive for more details.&n; *&n; * $Id: opsput_lan.h,v 1.1 2004/07/27 06:54:20 sakugawa Exp $&n; */
macro_line|#ifndef _OPSPUT_OPSPUT_LAN_H
DECL|macro|_OPSPUT_OPSPUT_LAN_H
mdefine_line|#define _OPSPUT_OPSPUT_LAN_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * C functions use non-cache address.&n; */
DECL|macro|OPSPUT_LAN_BASE
mdefine_line|#define OPSPUT_LAN_BASE&t;(0x10000000 /* + NONCACHE_OFFSET */)
macro_line|#else
DECL|macro|OPSPUT_LAN_BASE
mdefine_line|#define OPSPUT_LAN_BASE&t;(0x10000000 + NONCACHE_OFFSET)
macro_line|#endif&t;/* __ASSEMBLY__ */
multiline_comment|/* ICU&n; *  ICUISTS:&t;status register&n; *  ICUIREQ0: &t;request register&n; *  ICUIREQ1: &t;request register&n; *  ICUCR3:&t;control register for CFIREQ# interrupt&n; *  ICUCR4:&t;control register for CFC Card insert interrupt&n; *  ICUCR5:&t;control register for CFC Card eject interrupt&n; *  ICUCR6:&t;control register for external interrupt&n; *  ICUCR11:&t;control register for MMC Card insert/eject interrupt&n; *  ICUCR13:&t;control register for SC error interrupt&n; *  ICUCR14:&t;control register for SC receive interrupt&n; *  ICUCR15:&t;control register for SC send interrupt&n; *  ICUCR16:&t;control register for SIO0 receive interrupt&n; *  ICUCR17:&t;control register for SIO0 send interrupt&n; */
DECL|macro|OPSPUT_LAN_IRQ_LAN
mdefine_line|#define OPSPUT_LAN_IRQ_LAN&t;(OPSPUT_LAN_PLD_IRQ_BASE + 1)&t;/* LAN */
DECL|macro|OPSPUT_LAN_IRQ_I2C
mdefine_line|#define OPSPUT_LAN_IRQ_I2C&t;(OPSPUT_LAN_PLD_IRQ_BASE + 3)&t;/* I2C */
DECL|macro|OPSPUT_LAN_ICUISTS
mdefine_line|#define OPSPUT_LAN_ICUISTS&t;__reg16(OPSPUT_LAN_BASE + 0xc0002)
DECL|macro|OPSPUT_LAN_ICUISTS_VECB_MASK
mdefine_line|#define OPSPUT_LAN_ICUISTS_VECB_MASK&t;(0xf000)
DECL|macro|OPSPUT_LAN_VECB
mdefine_line|#define OPSPUT_LAN_VECB(x)&t;((x) &amp; OPSPUT_LAN_ICUISTS_VECB_MASK)
DECL|macro|OPSPUT_LAN_ICUISTS_ISN_MASK
mdefine_line|#define OPSPUT_LAN_ICUISTS_ISN_MASK&t;(0x07c0)
DECL|macro|OPSPUT_LAN_ICUISTS_ISN
mdefine_line|#define OPSPUT_LAN_ICUISTS_ISN(x)&t;((x) &amp; OPSPUT_LAN_ICUISTS_ISN_MASK)
DECL|macro|OPSPUT_LAN_ICUIREQ0
mdefine_line|#define OPSPUT_LAN_ICUIREQ0&t;__reg16(OPSPUT_LAN_BASE + 0xc0004)
DECL|macro|OPSPUT_LAN_ICUCR1
mdefine_line|#define OPSPUT_LAN_ICUCR1&t;__reg16(OPSPUT_LAN_BASE + 0xc0010)
DECL|macro|OPSPUT_LAN_ICUCR3
mdefine_line|#define OPSPUT_LAN_ICUCR3&t;__reg16(OPSPUT_LAN_BASE + 0xc0014)
macro_line|#endif&t;/* _OPSPUT_OPSPUT_LAN_H */
eof
