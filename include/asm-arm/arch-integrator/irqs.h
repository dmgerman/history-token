multiline_comment|/*&n; *  linux/include/asm-arm/arch-integrator/irqs.h&n; *&n; *  Copyright (C) 1999 ARM Limited&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/* Use the integrator definitions */
macro_line|#include &lt;asm/arch/platform.h&gt;
multiline_comment|/* &n; *  IRQ interrupts definitions are the same the INT definitions&n; *  held within platform.h&n; */
DECL|macro|IRQ_SOFTINT
mdefine_line|#define IRQ_SOFTINT                     INT_SOFTINT
DECL|macro|IRQ_UARTINT0
mdefine_line|#define IRQ_UARTINT0                    INT_UARTINT0
DECL|macro|IRQ_UARTINT1
mdefine_line|#define IRQ_UARTINT1                    INT_UARTINT1
DECL|macro|IRQ_KMIINT0
mdefine_line|#define IRQ_KMIINT0                     INT_KMIINT0
DECL|macro|IRQ_KMIINT1
mdefine_line|#define IRQ_KMIINT1                     INT_KMIINT1
DECL|macro|IRQ_TIMERINT0
mdefine_line|#define IRQ_TIMERINT0                   INT_TIMERINT0
DECL|macro|IRQ_TIMERINT1
mdefine_line|#define IRQ_TIMERINT1                   INT_TIMERINT1
DECL|macro|IRQ_TIMERINT2
mdefine_line|#define IRQ_TIMERINT2                   INT_TIMERINT2
DECL|macro|IRQ_RTCINT
mdefine_line|#define IRQ_RTCINT                      INT_RTCINT
DECL|macro|IRQ_EXPINT0
mdefine_line|#define IRQ_EXPINT0                     INT_EXPINT0
DECL|macro|IRQ_EXPINT1
mdefine_line|#define IRQ_EXPINT1                     INT_EXPINT1
DECL|macro|IRQ_EXPINT2
mdefine_line|#define IRQ_EXPINT2                     INT_EXPINT2
DECL|macro|IRQ_EXPINT3
mdefine_line|#define IRQ_EXPINT3                     INT_EXPINT3
DECL|macro|IRQ_PCIINT0
mdefine_line|#define IRQ_PCIINT0                     INT_PCIINT0
DECL|macro|IRQ_PCIINT1
mdefine_line|#define IRQ_PCIINT1                     INT_PCIINT1
DECL|macro|IRQ_PCIINT2
mdefine_line|#define IRQ_PCIINT2                     INT_PCIINT2
DECL|macro|IRQ_PCIINT3
mdefine_line|#define IRQ_PCIINT3                     INT_PCIINT3
DECL|macro|IRQ_V3INT
mdefine_line|#define IRQ_V3INT                       INT_V3INT
DECL|macro|IRQ_CPINT0
mdefine_line|#define IRQ_CPINT0                      INT_CPINT0
DECL|macro|IRQ_CPINT1
mdefine_line|#define IRQ_CPINT1                      INT_CPINT1
DECL|macro|IRQ_LBUSTIMEOUT
mdefine_line|#define IRQ_LBUSTIMEOUT                 INT_LBUSTIMEOUT
DECL|macro|IRQ_APCINT
mdefine_line|#define IRQ_APCINT                      INT_APCINT
DECL|macro|IRQMASK_SOFTINT
mdefine_line|#define IRQMASK_SOFTINT                 INTMASK_SOFTINT
DECL|macro|IRQMASK_UARTINT0
mdefine_line|#define IRQMASK_UARTINT0                INTMASK_UARTINT0
DECL|macro|IRQMASK_UARTINT1
mdefine_line|#define IRQMASK_UARTINT1                INTMASK_UARTINT1
DECL|macro|IRQMASK_KMIINT0
mdefine_line|#define IRQMASK_KMIINT0                 INTMASK_KMIINT0
DECL|macro|IRQMASK_KMIINT1
mdefine_line|#define IRQMASK_KMIINT1                 INTMASK_KMIINT1
DECL|macro|IRQMASK_TIMERINT0
mdefine_line|#define IRQMASK_TIMERINT0               INTMASK_TIMERINT0
DECL|macro|IRQMASK_TIMERINT1
mdefine_line|#define IRQMASK_TIMERINT1               INTMASK_TIMERINT1
DECL|macro|IRQMASK_TIMERINT2
mdefine_line|#define IRQMASK_TIMERINT2               INTMASK_TIMERINT2
DECL|macro|IRQMASK_RTCINT
mdefine_line|#define IRQMASK_RTCINT                  INTMASK_RTCINT
DECL|macro|IRQMASK_EXPINT0
mdefine_line|#define IRQMASK_EXPINT0                 INTMASK_EXPINT0
DECL|macro|IRQMASK_EXPINT1
mdefine_line|#define IRQMASK_EXPINT1                 INTMASK_EXPINT1
DECL|macro|IRQMASK_EXPINT2
mdefine_line|#define IRQMASK_EXPINT2                 INTMASK_EXPINT2
DECL|macro|IRQMASK_EXPINT3
mdefine_line|#define IRQMASK_EXPINT3                 INTMASK_EXPINT3
DECL|macro|IRQMASK_PCIINT0
mdefine_line|#define IRQMASK_PCIINT0                 INTMASK_PCIINT0
DECL|macro|IRQMASK_PCIINT1
mdefine_line|#define IRQMASK_PCIINT1                 INTMASK_PCIINT1
DECL|macro|IRQMASK_PCIINT2
mdefine_line|#define IRQMASK_PCIINT2                 INTMASK_PCIINT2
DECL|macro|IRQMASK_PCIINT3
mdefine_line|#define IRQMASK_PCIINT3                 INTMASK_PCIINT3
DECL|macro|IRQMASK_V3INT
mdefine_line|#define IRQMASK_V3INT                   INTMASK_V3INT
DECL|macro|IRQMASK_CPINT0
mdefine_line|#define IRQMASK_CPINT0                  INTMASK_CPINT0
DECL|macro|IRQMASK_CPINT1
mdefine_line|#define IRQMASK_CPINT1                  INTMASK_CPINT1
DECL|macro|IRQMASK_LBUSTIMEOUT
mdefine_line|#define IRQMASK_LBUSTIMEOUT             INTMASK_LBUSTIMEOUT
DECL|macro|IRQMASK_APCINT
mdefine_line|#define IRQMASK_APCINT                  INTMASK_APCINT
multiline_comment|/* &n; *  FIQ interrupts definitions are the same the INT definitions.&n; */
DECL|macro|FIQ_SOFTINT
mdefine_line|#define FIQ_SOFTINT                     INT_SOFTINT
DECL|macro|FIQ_UARTINT0
mdefine_line|#define FIQ_UARTINT0                    INT_UARTINT0
DECL|macro|FIQ_UARTINT1
mdefine_line|#define FIQ_UARTINT1                    INT_UARTINT1
DECL|macro|FIQ_KMIINT0
mdefine_line|#define FIQ_KMIINT0                     INT_KMIINT0
DECL|macro|FIQ_KMIINT1
mdefine_line|#define FIQ_KMIINT1                     INT_KMIINT1
DECL|macro|FIQ_TIMERINT0
mdefine_line|#define FIQ_TIMERINT0                   INT_TIMERINT0
DECL|macro|FIQ_TIMERINT1
mdefine_line|#define FIQ_TIMERINT1                   INT_TIMERINT1
DECL|macro|FIQ_TIMERINT2
mdefine_line|#define FIQ_TIMERINT2                   INT_TIMERINT2
DECL|macro|FIQ_RTCINT
mdefine_line|#define FIQ_RTCINT                      INT_RTCINT
DECL|macro|FIQ_EXPINT0
mdefine_line|#define FIQ_EXPINT0                     INT_EXPINT0
DECL|macro|FIQ_EXPINT1
mdefine_line|#define FIQ_EXPINT1                     INT_EXPINT1
DECL|macro|FIQ_EXPINT2
mdefine_line|#define FIQ_EXPINT2                     INT_EXPINT2
DECL|macro|FIQ_EXPINT3
mdefine_line|#define FIQ_EXPINT3                     INT_EXPINT3
DECL|macro|FIQ_PCIINT0
mdefine_line|#define FIQ_PCIINT0                     INT_PCIINT0
DECL|macro|FIQ_PCIINT1
mdefine_line|#define FIQ_PCIINT1                     INT_PCIINT1
DECL|macro|FIQ_PCIINT2
mdefine_line|#define FIQ_PCIINT2                     INT_PCIINT2
DECL|macro|FIQ_PCIINT3
mdefine_line|#define FIQ_PCIINT3                     INT_PCIINT3
DECL|macro|FIQ_V3INT
mdefine_line|#define FIQ_V3INT                       INT_V3INT
DECL|macro|FIQ_CPINT0
mdefine_line|#define FIQ_CPINT0                      INT_CPINT0
DECL|macro|FIQ_CPINT1
mdefine_line|#define FIQ_CPINT1                      INT_CPINT1
DECL|macro|FIQ_LBUSTIMEOUT
mdefine_line|#define FIQ_LBUSTIMEOUT                 INT_LBUSTIMEOUT
DECL|macro|FIQ_APCINT
mdefine_line|#define FIQ_APCINT                      INT_APCINT
DECL|macro|FIQMASK_SOFTINT
mdefine_line|#define FIQMASK_SOFTINT                 INTMASK_SOFTINT
DECL|macro|FIQMASK_UARTINT0
mdefine_line|#define FIQMASK_UARTINT0                INTMASK_UARTINT0
DECL|macro|FIQMASK_UARTINT1
mdefine_line|#define FIQMASK_UARTINT1                INTMASK_UARTINT1
DECL|macro|FIQMASK_KMIINT0
mdefine_line|#define FIQMASK_KMIINT0                 INTMASK_KMIINT0
DECL|macro|FIQMASK_KMIINT1
mdefine_line|#define FIQMASK_KMIINT1                 INTMASK_KMIINT1
DECL|macro|FIQMASK_TIMERINT0
mdefine_line|#define FIQMASK_TIMERINT0               INTMASK_TIMERINT0
DECL|macro|FIQMASK_TIMERINT1
mdefine_line|#define FIQMASK_TIMERINT1               INTMASK_TIMERINT1
DECL|macro|FIQMASK_TIMERINT2
mdefine_line|#define FIQMASK_TIMERINT2               INTMASK_TIMERINT2
DECL|macro|FIQMASK_RTCINT
mdefine_line|#define FIQMASK_RTCINT                  INTMASK_RTCINT
DECL|macro|FIQMASK_EXPINT0
mdefine_line|#define FIQMASK_EXPINT0                 INTMASK_EXPINT0
DECL|macro|FIQMASK_EXPINT1
mdefine_line|#define FIQMASK_EXPINT1                 INTMASK_EXPINT1
DECL|macro|FIQMASK_EXPINT2
mdefine_line|#define FIQMASK_EXPINT2                 INTMASK_EXPINT2
DECL|macro|FIQMASK_EXPINT3
mdefine_line|#define FIQMASK_EXPINT3                 INTMASK_EXPINT3
DECL|macro|FIQMASK_PCIINT0
mdefine_line|#define FIQMASK_PCIINT0                 INTMASK_PCIINT0
DECL|macro|FIQMASK_PCIINT1
mdefine_line|#define FIQMASK_PCIINT1                 INTMASK_PCIINT1
DECL|macro|FIQMASK_PCIINT2
mdefine_line|#define FIQMASK_PCIINT2                 INTMASK_PCIINT2
DECL|macro|FIQMASK_PCIINT3
mdefine_line|#define FIQMASK_PCIINT3                 INTMASK_PCIINT3
DECL|macro|FIQMASK_V3INT
mdefine_line|#define FIQMASK_V3INT                   INTMASK_V3INT
DECL|macro|FIQMASK_CPINT0
mdefine_line|#define FIQMASK_CPINT0                  INTMASK_CPINT0
DECL|macro|FIQMASK_CPINT1
mdefine_line|#define FIQMASK_CPINT1                  INTMASK_CPINT1
DECL|macro|FIQMASK_LBUSTIMEOUT
mdefine_line|#define FIQMASK_LBUSTIMEOUT             INTMASK_LBUSTIMEOUT
DECL|macro|FIQMASK_APCINT
mdefine_line|#define FIQMASK_APCINT                  INTMASK_APCINT
multiline_comment|/* &n; *  Misc. interrupt definitions&n; */
DECL|macro|IRQ_KEYBDINT
mdefine_line|#define IRQ_KEYBDINT                    INT_KMIINT0
DECL|macro|IRQ_MOUSEINT
mdefine_line|#define IRQ_MOUSEINT                    INT_KMIINT1
DECL|macro|IRQMASK_KEYBDINT
mdefine_line|#define IRQMASK_KEYBDINT                INTMASK_KMIINT0
DECL|macro|IRQMASK_MOUSEINT
mdefine_line|#define IRQMASK_MOUSEINT                INTMASK_KMIINT1
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS                         (MAXIRQNUM + 1)
eof
