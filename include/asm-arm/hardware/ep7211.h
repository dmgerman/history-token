multiline_comment|/*&n; *  linux/include/asm-arm/hardware/ep7211.h&n; *&n; *  This file contains the hardware definitions of the EP7211 internal&n; *  registers.&n; *&n; *  Copyright (C) 2001 Blue Mug, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_HARDWARE_EP7211_H
DECL|macro|__ASM_HARDWARE_EP7211_H
mdefine_line|#define __ASM_HARDWARE_EP7211_H
macro_line|#include &lt;asm/hardware/clps7111.h&gt;
multiline_comment|/*&n; * define EP7211_BASE to be the base address of the region&n; * you want to access.&n; */
DECL|macro|EP7211_PHYS_BASE
mdefine_line|#define EP7211_PHYS_BASE&t;(0x80000000)
multiline_comment|/*&n; * XXX miket@bluemug.com: need to introduce EP7211 registers (those not&n; * present in 7212) here.&n; */
macro_line|#endif /* __ASM_HARDWARE_EP7211_H */
eof
