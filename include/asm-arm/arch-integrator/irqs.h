multiline_comment|/*&n; *  linux/include/asm-arm/arch-integrator/irqs.h&n; *&n; *  Copyright (C) 1999 ARM Limited&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/* &n; *  Interrupt numbers&n; */
DECL|macro|IRQ_PIC_START
mdefine_line|#define IRQ_PIC_START&t;&t;&t;0
DECL|macro|IRQ_SOFTINT
mdefine_line|#define IRQ_SOFTINT&t;&t;&t;0
DECL|macro|IRQ_UARTINT0
mdefine_line|#define IRQ_UARTINT0&t;&t;&t;1
DECL|macro|IRQ_UARTINT1
mdefine_line|#define IRQ_UARTINT1&t;&t;&t;2
DECL|macro|IRQ_KMIINT0
mdefine_line|#define IRQ_KMIINT0&t;&t;&t;3
DECL|macro|IRQ_KMIINT1
mdefine_line|#define IRQ_KMIINT1&t;&t;&t;4
DECL|macro|IRQ_TIMERINT0
mdefine_line|#define IRQ_TIMERINT0&t;&t;&t;5
DECL|macro|IRQ_TIMERINT1
mdefine_line|#define IRQ_TIMERINT1&t;&t;&t;6
DECL|macro|IRQ_TIMERINT2
mdefine_line|#define IRQ_TIMERINT2&t;&t;&t;7
DECL|macro|IRQ_RTCINT
mdefine_line|#define IRQ_RTCINT&t;&t;&t;8
DECL|macro|IRQ_AP_EXPINT0
mdefine_line|#define IRQ_AP_EXPINT0&t;&t;&t;9
DECL|macro|IRQ_AP_EXPINT1
mdefine_line|#define IRQ_AP_EXPINT1&t;&t;&t;10
DECL|macro|IRQ_AP_EXPINT2
mdefine_line|#define IRQ_AP_EXPINT2&t;&t;&t;11
DECL|macro|IRQ_AP_EXPINT3
mdefine_line|#define IRQ_AP_EXPINT3&t;&t;&t;12
DECL|macro|IRQ_AP_PCIINT0
mdefine_line|#define IRQ_AP_PCIINT0&t;&t;&t;13
DECL|macro|IRQ_AP_PCIINT1
mdefine_line|#define IRQ_AP_PCIINT1&t;&t;&t;14
DECL|macro|IRQ_AP_PCIINT2
mdefine_line|#define IRQ_AP_PCIINT2&t;&t;&t;15
DECL|macro|IRQ_AP_PCIINT3
mdefine_line|#define IRQ_AP_PCIINT3&t;&t;&t;16
DECL|macro|IRQ_AP_V3INT
mdefine_line|#define IRQ_AP_V3INT&t;&t;&t;17
DECL|macro|IRQ_AP_CPINT0
mdefine_line|#define IRQ_AP_CPINT0&t;&t;&t;18
DECL|macro|IRQ_AP_CPINT1
mdefine_line|#define IRQ_AP_CPINT1&t;&t;&t;19
DECL|macro|IRQ_AP_LBUSTIMEOUT
mdefine_line|#define IRQ_AP_LBUSTIMEOUT &t;&t;20
DECL|macro|IRQ_AP_APCINT
mdefine_line|#define IRQ_AP_APCINT&t;&t;&t;21
DECL|macro|IRQ_PIC_END
mdefine_line|#define IRQ_PIC_END&t;&t;&t;31
DECL|macro|IRQ_CIC_START
mdefine_line|#define IRQ_CIC_START&t;&t;&t;32
DECL|macro|IRQ_CM_SOFTINT
mdefine_line|#define IRQ_CM_SOFTINT&t;&t;&t;32
DECL|macro|IRQ_CM_COMMRX
mdefine_line|#define IRQ_CM_COMMRX&t;&t;&t;33
DECL|macro|IRQ_CM_COMMTX
mdefine_line|#define IRQ_CM_COMMTX&t;&t;&t;34
DECL|macro|IRQ_CIC_END
mdefine_line|#define IRQ_CIC_END&t;&t;&t;34
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS                         47
eof
