multiline_comment|/*&n; *  linux/include/asm-arm/hardware/amba_kmi.h&n; *&n; *  Internal header file for AMBA KMI ports&n; *&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; *&n; * ---------------------------------------------------------------------------&n; *  From ARM PrimeCell(tm) PS2 Keyboard/Mouse Interface (PL050) Technical&n; *  Reference Manual - ARM DDI 0143B - see http://www.arm.com/&n; * ---------------------------------------------------------------------------&n; */
macro_line|#ifndef ASM_ARM_HARDWARE_AMBA_KMI_H
DECL|macro|ASM_ARM_HARDWARE_AMBA_KMI_H
mdefine_line|#define ASM_ARM_HARDWARE_AMBA_KMI_H
multiline_comment|/*&n; * KMI control register:&n; *  KMICR_TYPE       0 = PS2/AT mode, 1 = No line control bit mode&n; *  KMICR_RXINTREN   1 = enable RX interrupts&n; *  KMICR_TXINTREN   1 = enable TX interrupts&n; *  KMICR_EN         1 = enable KMI&n; *  KMICR_FD         1 = force KMI data low&n; *  KMICR_FC         1 = force KMI clock low&n; */
DECL|macro|KMICR
mdefine_line|#define KMICR&t;&t;(KMI_BASE + 0x00)
DECL|macro|KMICR_TYPE
mdefine_line|#define KMICR_TYPE&t;&t;(1 &lt;&lt; 5)
DECL|macro|KMICR_RXINTREN
mdefine_line|#define KMICR_RXINTREN&t;&t;(1 &lt;&lt; 4)
DECL|macro|KMICR_TXINTREN
mdefine_line|#define KMICR_TXINTREN&t;&t;(1 &lt;&lt; 3)
DECL|macro|KMICR_EN
mdefine_line|#define KMICR_EN&t;&t;(1 &lt;&lt; 2)
DECL|macro|KMICR_FD
mdefine_line|#define KMICR_FD&t;&t;(1 &lt;&lt; 1)
DECL|macro|KMICR_FC
mdefine_line|#define KMICR_FC&t;&t;(1 &lt;&lt; 0)
multiline_comment|/*&n; * KMI status register:&n; *  KMISTAT_TXEMPTY  1 = transmitter register empty&n; *  KMISTAT_TXBUSY   1 = currently sending data&n; *  KMISTAT_RXFULL   1 = receiver register ready to be read&n; *  KMISTAT_RXBUSY   1 = currently receiving data&n; *  KMISTAT_RXPARITY parity of last databyte received&n; *  KMISTAT_IC       current level of KMI clock input&n; *  KMISTAT_ID       current level of KMI data input&n; */
DECL|macro|KMISTAT
mdefine_line|#define KMISTAT&t;&t;(KMI_BASE + 0x04)
DECL|macro|KMISTAT_TXEMPTY
mdefine_line|#define KMISTAT_TXEMPTY&t;&t;(1 &lt;&lt; 6)
DECL|macro|KMISTAT_TXBUSY
mdefine_line|#define KMISTAT_TXBUSY&t;&t;(1 &lt;&lt; 5)
DECL|macro|KMISTAT_RXFULL
mdefine_line|#define KMISTAT_RXFULL&t;&t;(1 &lt;&lt; 4)
DECL|macro|KMISTAT_RXBUSY
mdefine_line|#define KMISTAT_RXBUSY&t;&t;(1 &lt;&lt; 3)
DECL|macro|KMISTAT_RXPARITY
mdefine_line|#define KMISTAT_RXPARITY&t;(1 &lt;&lt; 2)
DECL|macro|KMISTAT_IC
mdefine_line|#define KMISTAT_IC&t;&t;(1 &lt;&lt; 1)
DECL|macro|KMISTAT_ID
mdefine_line|#define KMISTAT_ID&t;&t;(1 &lt;&lt; 0)
multiline_comment|/*&n; * KMI data register&n; */
DECL|macro|KMIDATA
mdefine_line|#define KMIDATA&t;&t;(KMI_BASE + 0x08)
multiline_comment|/*&n; * KMI clock divisor: to generate 8MHz internal clock&n; *  div = (ref / 8MHz) - 1; 0 &lt;= div &lt;= 15&n; */
DECL|macro|KMICLKDIV
mdefine_line|#define KMICLKDIV&t;(KMI_BASE + 0x0c)
multiline_comment|/*&n; * KMI interrupt register:&n; *  KMIIR_TXINTR     1 = transmit interrupt asserted&n; *  KMIIR_RXINTR     1 = receive interrupt asserted&n; */
DECL|macro|KMIIR
mdefine_line|#define KMIIR&t;&t;(KMI_BASE + 0x10)
DECL|macro|KMIIR_TXINTR
mdefine_line|#define KMIIR_TXINTR&t;&t;(1 &lt;&lt; 1)
DECL|macro|KMIIR_RXINTR
mdefine_line|#define KMIIR_RXINTR&t;&t;(1 &lt;&lt; 0)
multiline_comment|/*&n; * The size of the KMI primecell&n; */
DECL|macro|KMI_SIZE
mdefine_line|#define KMI_SIZE&t;(0x100)
macro_line|#endif
eof
