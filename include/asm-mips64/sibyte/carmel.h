multiline_comment|/*&n; * Copyright (C) 2002 Broadcom Corporation&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#ifndef __ASM_SIBYTE_CARMEL_H
DECL|macro|__ASM_SIBYTE_CARMEL_H
mdefine_line|#define __ASM_SIBYTE_CARMEL_H
macro_line|#include &lt;asm/sibyte/sb1250.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_int.h&gt;
DECL|macro|SIBYTE_BOARD_NAME
mdefine_line|#define SIBYTE_BOARD_NAME &quot;Carmel&quot;
DECL|macro|GPIO_PHY_INTERRUPT
mdefine_line|#define GPIO_PHY_INTERRUPT      2 
DECL|macro|GPIO_NONMASKABLE_INT
mdefine_line|#define GPIO_NONMASKABLE_INT    3 
DECL|macro|GPIO_CF_INSERTED
mdefine_line|#define GPIO_CF_INSERTED        6 
DECL|macro|GPIO_MONTEREY_RESET
mdefine_line|#define GPIO_MONTEREY_RESET     7 
DECL|macro|GPIO_QUADUART_INT
mdefine_line|#define GPIO_QUADUART_INT       8 
DECL|macro|GPIO_CF_INT
mdefine_line|#define GPIO_CF_INT             9 
DECL|macro|GPIO_FPGA_CCLK
mdefine_line|#define GPIO_FPGA_CCLK          10
DECL|macro|GPIO_FPGA_DOUT
mdefine_line|#define GPIO_FPGA_DOUT          11
DECL|macro|GPIO_FPGA_DIN
mdefine_line|#define GPIO_FPGA_DIN           12
DECL|macro|GPIO_FPGA_PGM
mdefine_line|#define GPIO_FPGA_PGM           13
DECL|macro|GPIO_FPGA_DONE
mdefine_line|#define GPIO_FPGA_DONE          14
DECL|macro|GPIO_FPGA_INIT
mdefine_line|#define GPIO_FPGA_INIT          15
DECL|macro|LEDS_CS
mdefine_line|#define LEDS_CS                 2
DECL|macro|LEDS_PHYS
mdefine_line|#define LEDS_PHYS               0x100C0000
DECL|macro|MLEDS_CS
mdefine_line|#define MLEDS_CS                3
DECL|macro|MLEDS_PHYS
mdefine_line|#define MLEDS_PHYS              0x100A0000
DECL|macro|UART_CS
mdefine_line|#define UART_CS                 4
DECL|macro|UART_PHYS
mdefine_line|#define UART_PHYS               0x100D0000
DECL|macro|ARAVALI_CS
mdefine_line|#define ARAVALI_CS              5
DECL|macro|ARAVALI_PHYS
mdefine_line|#define ARAVALI_PHYS            0x11000000
DECL|macro|IDE_CS
mdefine_line|#define IDE_CS                  6
DECL|macro|IDE_PHYS
mdefine_line|#define IDE_PHYS                0x100B0000
DECL|macro|ARAVALI2_CS
mdefine_line|#define ARAVALI2_CS             7
DECL|macro|ARAVALI2_PHYS
mdefine_line|#define ARAVALI2_PHYS           0x100E0000
macro_line|#if defined(CONFIG_SIBYTE_CARMEL)
DECL|macro|K_GPIO_GB_IDE
mdefine_line|#define K_GPIO_GB_IDE   9
DECL|macro|K_INT_GB_IDE
mdefine_line|#define K_INT_GB_IDE    (K_INT_GPIO_0 + K_GPIO_GB_IDE)
macro_line|#endif
macro_line|#endif /* __ASM_SIBYTE_CARMEL_H */
eof
