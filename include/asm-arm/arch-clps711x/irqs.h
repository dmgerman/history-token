multiline_comment|/*&n; *  linux/include/asm-arm/arch-clps711x/irqs.h&n; *&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/*&n; * Interrupts from INTSR1&n; */
DECL|macro|IRQ_CSINT
mdefine_line|#define IRQ_CSINT&t;&t;&t;4
DECL|macro|IRQ_EINT1
mdefine_line|#define IRQ_EINT1&t;&t;&t;5
DECL|macro|IRQ_EINT2
mdefine_line|#define IRQ_EINT2&t;&t;&t;6
DECL|macro|IRQ_EINT3
mdefine_line|#define IRQ_EINT3&t;&t;&t;7
DECL|macro|IRQ_TC1OI
mdefine_line|#define IRQ_TC1OI&t;&t;&t;8
DECL|macro|IRQ_TC2OI
mdefine_line|#define IRQ_TC2OI&t;&t;&t;9
DECL|macro|IRQ_RTCMI
mdefine_line|#define IRQ_RTCMI&t;&t;&t;10
DECL|macro|IRQ_TINT
mdefine_line|#define IRQ_TINT&t;&t;&t;11
DECL|macro|IRQ_UTXINT1
mdefine_line|#define IRQ_UTXINT1&t;&t;&t;12
DECL|macro|IRQ_URXINT1
mdefine_line|#define IRQ_URXINT1&t;&t;&t;13
DECL|macro|IRQ_UMSINT
mdefine_line|#define IRQ_UMSINT&t;&t;&t;14
DECL|macro|IRQ_SSEOTI
mdefine_line|#define IRQ_SSEOTI&t;&t;&t;15
DECL|macro|INT1_IRQS
mdefine_line|#define INT1_IRQS&t;&t;&t;(0x0000fff0)
DECL|macro|INT1_ACK_IRQS
mdefine_line|#define INT1_ACK_IRQS&t;&t;&t;(0x00004f10)
multiline_comment|/*&n; * Interrupts from INTSR2&n; */
DECL|macro|IRQ_KBDINT
mdefine_line|#define IRQ_KBDINT&t;&t;&t;(16+0)&t;/* bit 0 */
DECL|macro|IRQ_SS2RX
mdefine_line|#define IRQ_SS2RX&t;&t;&t;(16+1)&t;/* bit 1 */
DECL|macro|IRQ_SS2TX
mdefine_line|#define IRQ_SS2TX&t;&t;&t;(16+2)&t;/* bit 2 */
DECL|macro|IRQ_UTXINT2
mdefine_line|#define IRQ_UTXINT2&t;&t;&t;(16+12)&t;/* bit 12 */
DECL|macro|IRQ_URXINT2
mdefine_line|#define IRQ_URXINT2&t;&t;&t;(16+13)&t;/* bit 13 */
DECL|macro|INT2_IRQS
mdefine_line|#define INT2_IRQS&t;&t;&t;(0x30070000)
DECL|macro|INT2_ACK_IRQS
mdefine_line|#define INT2_ACK_IRQS&t;&t;&t;(0x00010000)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS                         30
eof
