multiline_comment|/*&n; *  linux/include/asm-arm/hardware/cs89712.h&n; *&n; *  This file contains the hardware definitions of the CS89712&n; *  additional internal registers.&n; *&n; *  Copyright (C) 2001 Thomas Gleixner autronix automation &lt;gleixner@autronix.de&gt;&n; *&t;&t;&t;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_HARDWARE_CS89712_H
DECL|macro|__ASM_HARDWARE_CS89712_H
mdefine_line|#define __ASM_HARDWARE_CS89712_H
multiline_comment|/*&n;*&t;CS89712 additional registers&n;*/
DECL|macro|PCDR
mdefine_line|#define PCDR&t;&t;&t;0x0002&t;/* Port C Data register ---------------------------- */
DECL|macro|PCDDR
mdefine_line|#define PCDDR&t;&t;&t;0x0042&t;/* Port C Data Direction register ------------------ */
DECL|macro|SDCONF
mdefine_line|#define SDCONF&t;&t;&t;0x2300  /* SDRAM Configuration register ---------------------*/
DECL|macro|SDRFPR
mdefine_line|#define SDRFPR&t;&t;&t;0x2340  /* SDRAM Refresh period register --------------------*/
DECL|macro|SDCONF_ACTIVE
mdefine_line|#define SDCONF_ACTIVE&t;&t;(1 &lt;&lt; 10)
DECL|macro|SDCONF_CLKCTL
mdefine_line|#define SDCONF_CLKCTL&t;&t;(1 &lt;&lt; 9)
DECL|macro|SDCONF_WIDTH_4
mdefine_line|#define SDCONF_WIDTH_4&t;&t;(0 &lt;&lt; 7)
DECL|macro|SDCONF_WIDTH_8
mdefine_line|#define SDCONF_WIDTH_8&t;&t;(1 &lt;&lt; 7)
DECL|macro|SDCONF_WIDTH_16
mdefine_line|#define SDCONF_WIDTH_16&t;&t;(2 &lt;&lt; 7)
DECL|macro|SDCONF_WIDTH_32
mdefine_line|#define SDCONF_WIDTH_32&t;&t;(3 &lt;&lt; 7)
DECL|macro|SDCONF_SIZE_16
mdefine_line|#define SDCONF_SIZE_16&t;&t;(0 &lt;&lt; 5)
DECL|macro|SDCONF_SIZE_64
mdefine_line|#define SDCONF_SIZE_64&t;&t;(1 &lt;&lt; 5)
DECL|macro|SDCONF_SIZE_128
mdefine_line|#define SDCONF_SIZE_128&t;&t;(2 &lt;&lt; 5)
DECL|macro|SDCONF_SIZE_256
mdefine_line|#define SDCONF_SIZE_256&t;&t;(3 &lt;&lt; 5)
DECL|macro|SDCONF_CASLAT_2
mdefine_line|#define SDCONF_CASLAT_2&t;&t;(2)
DECL|macro|SDCONF_CASLAT_3
mdefine_line|#define SDCONF_CASLAT_3&t;&t;(3)
macro_line|#endif /* __ASM_HARDWARE_CS89712_H */
eof
