multiline_comment|/*&n; * linux/include/asm-arm/arch-imx/mx1ads.h&n; *&n; * Copyright (C) 2004 Robert Schwebel, Pengutronix&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
macro_line|#ifndef __ASM_ARCH_MX1ADS_H
DECL|macro|__ASM_ARCH_MX1ADS_H
mdefine_line|#define __ASM_ARCH_MX1ADS_H
multiline_comment|/* ------------------------------------------------------------------------ */
multiline_comment|/* Memory Map for the M9328MX1ADS (MX1ADS) Board                            */
multiline_comment|/* ------------------------------------------------------------------------ */
DECL|macro|MX1ADS_FLASH_PHYS
mdefine_line|#define MX1ADS_FLASH_PHYS&t;&t;0x10000000
DECL|macro|MX1ADS_FLASH_SIZE
mdefine_line|#define MX1ADS_FLASH_SIZE&t;&t;(16*1024*1024)
DECL|macro|IMX_FB_PHYS
mdefine_line|#define IMX_FB_PHYS&t;&t;&t;(0x0C000000 - 0x40000)
DECL|macro|CLK32
mdefine_line|#define CLK32 32000
macro_line|#endif /* __ASM_ARCH_MX1ADS_H */
eof
