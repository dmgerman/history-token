multiline_comment|/*&n; *  linux/include/asm-arm/arch-camelot/irqs.h&n; *&n; *  Copyright (C) 2001 Altera Corporation&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/* Use the Excalibur chip definitions */
DECL|macro|INT_CTRL00_TYPE
mdefine_line|#define INT_CTRL00_TYPE
macro_line|#include &quot;asm/arch/int_ctrl00.h&quot;
DECL|macro|IRQ_PLD0
mdefine_line|#define IRQ_PLD0                     INT_MS_P0_OFST
DECL|macro|IRQ_PLD1
mdefine_line|#define IRQ_PLD1                     INT_MS_P1_OFST
DECL|macro|IRQ_PLD2
mdefine_line|#define IRQ_PLD2                     INT_MS_P2_OFST
DECL|macro|IRQ_PLD3
mdefine_line|#define IRQ_PLD3                     INT_MS_P3_OFST
DECL|macro|IRQ_PLD4
mdefine_line|#define IRQ_PLD4                     INT_MS_P4_OFST
DECL|macro|IRQ_PLD5
mdefine_line|#define IRQ_PLD5                     INT_MS_P5_OFST
DECL|macro|IRQ_EXT
mdefine_line|#define IRQ_EXT                      INT_MS_IP_OFST
DECL|macro|IRQ_UART
mdefine_line|#define IRQ_UART                     INT_MS_UA_OFST
DECL|macro|IRQ_TIMER0
mdefine_line|#define IRQ_TIMER0                   INT_MS_T0_OFST
DECL|macro|IRQ_TIMER1
mdefine_line|#define IRQ_TIMER1                   INT_MS_T1_OFST
DECL|macro|IRQ_PLL
mdefine_line|#define IRQ_PLL                      INT_MS_PLL_OFST
DECL|macro|IRQ_EBI
mdefine_line|#define IRQ_EBI                      INT_MS_EBI_OFST
DECL|macro|IRQ_STRIPE_BRIDGE
mdefine_line|#define IRQ_STRIPE_BRIDGE            INT_MS_PLL_OFST
DECL|macro|IRQ_AHB_BRIDGE
mdefine_line|#define IRQ_AHB_BRIDGE               INT_MS_PLL_OFST
DECL|macro|IRQ_COMMRX
mdefine_line|#define IRQ_COMMRX                   INT_MS_CR_OFST
DECL|macro|IRQ_COMMTX
mdefine_line|#define IRQ_COMMTX                   INT_MS_CT_OFST
DECL|macro|IRQ_FAST_COMM
mdefine_line|#define IRQ_FAST_COMM                INT_MS_FC_OFST
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS                         (INT_MS_FC_OFST + 1)
eof
