multiline_comment|/*&n; *  linux/include/asm-arm/hardware/ep7212.h&n; *&n; *  This file contains the hardware definitions of the EP7212 internal&n; *  registers.&n; *&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_HARDWARE_EP7212_H
DECL|macro|__ASM_HARDWARE_EP7212_H
mdefine_line|#define __ASM_HARDWARE_EP7212_H
multiline_comment|/*&n; * define EP7212_BASE to be the base address of the region&n; * you want to access.&n; */
DECL|macro|EP7212_PHYS_BASE
mdefine_line|#define EP7212_PHYS_BASE&t;(0x80000000)
macro_line|#ifndef __ASSEMBLY__
DECL|macro|ep_readl
mdefine_line|#define ep_readl(off)&t;&t;__raw_readl(EP7212_BASE + (off))
DECL|macro|ep_writel
mdefine_line|#define ep_writel(val,off)&t;__raw_writel(val, EP7212_BASE + (off))
macro_line|#endif
multiline_comment|/*&n; * These registers are specific to the EP7212 only&n; */
DECL|macro|DAIR
mdefine_line|#define DAIR&t;&t;&t;0x2000
DECL|macro|DAIR0
mdefine_line|#define DAIR0&t;&t;&t;0x2040
DECL|macro|DAIDR1
mdefine_line|#define DAIDR1&t;&t;&t;0x2080
DECL|macro|DAIDR2
mdefine_line|#define DAIDR2&t;&t;&t;0x20c0
DECL|macro|DAISR
mdefine_line|#define DAISR&t;&t;&t;0x2100
DECL|macro|SYSCON3
mdefine_line|#define SYSCON3&t;&t;&t;0x2200
DECL|macro|INTSR3
mdefine_line|#define INTSR3&t;&t;&t;0x2240
DECL|macro|INTMR3
mdefine_line|#define INTMR3&t;&t;&t;0x2280
DECL|macro|LEDFLSH
mdefine_line|#define LEDFLSH&t;&t;&t;0x22c0
DECL|macro|DAIR_DAIEN
mdefine_line|#define DAIR_DAIEN&t;&t;(1 &lt;&lt; 16)
DECL|macro|DAIR_ECS
mdefine_line|#define DAIR_ECS&t;&t;(1 &lt;&lt; 17)
DECL|macro|DAIR_LCTM
mdefine_line|#define DAIR_LCTM&t;&t;(1 &lt;&lt; 19)
DECL|macro|DAIR_LCRM
mdefine_line|#define DAIR_LCRM&t;&t;(1 &lt;&lt; 20)
DECL|macro|DAIR_RCTM
mdefine_line|#define DAIR_RCTM&t;&t;(1 &lt;&lt; 21)
DECL|macro|DAIR_RCRM
mdefine_line|#define DAIR_RCRM&t;&t;(1 &lt;&lt; 22)
DECL|macro|DAIR_LBM
mdefine_line|#define DAIR_LBM&t;&t;(1 &lt;&lt; 23)
DECL|macro|DAIDR2_FIFOEN
mdefine_line|#define DAIDR2_FIFOEN&t;&t;(1 &lt;&lt; 15)
DECL|macro|DAIDR2_FIFOLEFT
mdefine_line|#define DAIDR2_FIFOLEFT&t;&t;(0x0d &lt;&lt; 16)
DECL|macro|DAIDR2_FIFORIGHT
mdefine_line|#define DAIDR2_FIFORIGHT&t;(0x11 &lt;&lt; 16)
DECL|macro|DAISR_RCTS
mdefine_line|#define DAISR_RCTS&t;&t;(1 &lt;&lt; 0)
DECL|macro|DAISR_RCRS
mdefine_line|#define DAISR_RCRS&t;&t;(1 &lt;&lt; 1)
DECL|macro|DAISR_LCTS
mdefine_line|#define DAISR_LCTS&t;&t;(1 &lt;&lt; 2)
DECL|macro|DAISR_LCRS
mdefine_line|#define DAISR_LCRS&t;&t;(1 &lt;&lt; 3)
DECL|macro|DAISR_RCTU
mdefine_line|#define DAISR_RCTU&t;&t;(1 &lt;&lt; 4)
DECL|macro|DAISR_RCRO
mdefine_line|#define DAISR_RCRO&t;&t;(1 &lt;&lt; 5)
DECL|macro|DAISR_LCTU
mdefine_line|#define DAISR_LCTU&t;&t;(1 &lt;&lt; 6)
DECL|macro|DAISR_LCRO
mdefine_line|#define DAISR_LCRO&t;&t;(1 &lt;&lt; 7)
DECL|macro|DAISR_RCNF
mdefine_line|#define DAISR_RCNF&t;&t;(1 &lt;&lt; 8)
DECL|macro|DAISR_RCNE
mdefine_line|#define DAISR_RCNE&t;&t;(1 &lt;&lt; 9)
DECL|macro|DAISR_LCNF
mdefine_line|#define DAISR_LCNF&t;&t;(1 &lt;&lt; 10)
DECL|macro|DAISR_LCNE
mdefine_line|#define DAISR_LCNE&t;&t;(1 &lt;&lt; 11)
DECL|macro|DAISR_FIFO
mdefine_line|#define DAISR_FIFO&t;&t;(1 &lt;&lt; 12)
DECL|macro|SYSCON3_ADCCON
mdefine_line|#define SYSCON3_ADCCON&t;&t;(1 &lt;&lt; 0)
DECL|macro|SYSCON3_DAISEL
mdefine_line|#define SYSCON3_DAISEL&t;&t;(1 &lt;&lt; 3)
DECL|macro|SYSCON3_ADCCKNSEN
mdefine_line|#define SYSCON3_ADCCKNSEN&t;(1 &lt;&lt; 4)
DECL|macro|SYSCON3_FASTWAKE
mdefine_line|#define SYSCON3_FASTWAKE&t;(1 &lt;&lt; 8)
DECL|macro|SYSCON3_DAIEN
mdefine_line|#define SYSCON3_DAIEN&t;&t;(1 &lt;&lt; 9)
macro_line|#endif /* __ASM_HARDWARE_EP7212_H */
eof
