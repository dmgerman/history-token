multiline_comment|/*&n; *  linux/include/asm-arm/arch-versatile/irqs.h&n; *&n; *  Copyright (C) 2003 ARM Limited&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;asm/arch/platform.h&gt;
multiline_comment|/* &n; *  IRQ interrupts definitions are the same the INT definitions&n; *  held within platform.h&n; */
DECL|macro|IRQ_VIC_START
mdefine_line|#define IRQ_VIC_START&t;&t;0
DECL|macro|IRQ_WDOGINT
mdefine_line|#define IRQ_WDOGINT&t;&t;(IRQ_VIC_START + INT_WDOGINT)
DECL|macro|IRQ_SOFTINT
mdefine_line|#define IRQ_SOFTINT&t;&t;(IRQ_VIC_START + INT_SOFTINT)
DECL|macro|IRQ_COMMRx
mdefine_line|#define IRQ_COMMRx&t;&t;(IRQ_VIC_START + INT_COMMRx)
DECL|macro|IRQ_COMMTx
mdefine_line|#define IRQ_COMMTx&t;&t;(IRQ_VIC_START + INT_COMMTx)
DECL|macro|IRQ_TIMERINT0_1
mdefine_line|#define IRQ_TIMERINT0_1&t;&t;(IRQ_VIC_START + INT_TIMERINT0_1)
DECL|macro|IRQ_TIMERINT2_3
mdefine_line|#define IRQ_TIMERINT2_3&t;&t;(IRQ_VIC_START + INT_TIMERINT2_3)
DECL|macro|IRQ_GPIOINT0
mdefine_line|#define IRQ_GPIOINT0&t;&t;(IRQ_VIC_START + INT_GPIOINT0)
DECL|macro|IRQ_GPIOINT1
mdefine_line|#define IRQ_GPIOINT1&t;&t;(IRQ_VIC_START + INT_GPIOINT1)
DECL|macro|IRQ_GPIOINT2
mdefine_line|#define IRQ_GPIOINT2&t;&t;(IRQ_VIC_START + INT_GPIOINT2)
DECL|macro|IRQ_GPIOINT3
mdefine_line|#define IRQ_GPIOINT3&t;&t;(IRQ_VIC_START + INT_GPIOINT3)
DECL|macro|IRQ_RTCINT
mdefine_line|#define IRQ_RTCINT&t;&t;(IRQ_VIC_START + INT_RTCINT)
DECL|macro|IRQ_SSPINT
mdefine_line|#define IRQ_SSPINT&t;&t;(IRQ_VIC_START + INT_SSPINT)
DECL|macro|IRQ_UARTINT0
mdefine_line|#define IRQ_UARTINT0&t;&t;(IRQ_VIC_START + INT_UARTINT0)
DECL|macro|IRQ_UARTINT1
mdefine_line|#define IRQ_UARTINT1&t;&t;(IRQ_VIC_START + INT_UARTINT1)
DECL|macro|IRQ_UARTINT2
mdefine_line|#define IRQ_UARTINT2&t;&t;(IRQ_VIC_START + INT_UARTINT2)
DECL|macro|IRQ_SCIINT
mdefine_line|#define IRQ_SCIINT&t;&t;(IRQ_VIC_START + INT_SCIINT)
DECL|macro|IRQ_CLCDINT
mdefine_line|#define IRQ_CLCDINT&t;&t;(IRQ_VIC_START + INT_CLCDINT)
DECL|macro|IRQ_DMAINT
mdefine_line|#define IRQ_DMAINT&t;&t;(IRQ_VIC_START + INT_DMAINT)
DECL|macro|IRQ_PWRFAILINT
mdefine_line|#define IRQ_PWRFAILINT &t;&t;(IRQ_VIC_START + INT_PWRFAILINT)
DECL|macro|IRQ_MBXINT
mdefine_line|#define IRQ_MBXINT&t;&t;(IRQ_VIC_START + INT_MBXINT)
DECL|macro|IRQ_GNDINT
mdefine_line|#define IRQ_GNDINT&t;&t;(IRQ_VIC_START + INT_GNDINT)
DECL|macro|IRQ_VICSOURCE21
mdefine_line|#define IRQ_VICSOURCE21&t;&t;(IRQ_VIC_START + INT_VICSOURCE21)
DECL|macro|IRQ_VICSOURCE22
mdefine_line|#define IRQ_VICSOURCE22&t;&t;(IRQ_VIC_START + INT_VICSOURCE22)
DECL|macro|IRQ_VICSOURCE23
mdefine_line|#define IRQ_VICSOURCE23&t;&t;(IRQ_VIC_START + INT_VICSOURCE23)
DECL|macro|IRQ_VICSOURCE24
mdefine_line|#define IRQ_VICSOURCE24&t;&t;(IRQ_VIC_START + INT_VICSOURCE24)
DECL|macro|IRQ_VICSOURCE25
mdefine_line|#define IRQ_VICSOURCE25&t;&t;(IRQ_VIC_START + INT_VICSOURCE25)
DECL|macro|IRQ_VICSOURCE26
mdefine_line|#define IRQ_VICSOURCE26&t;&t;(IRQ_VIC_START + INT_VICSOURCE26)
DECL|macro|IRQ_VICSOURCE27
mdefine_line|#define IRQ_VICSOURCE27&t;&t;(IRQ_VIC_START + INT_VICSOURCE27)
DECL|macro|IRQ_VICSOURCE28
mdefine_line|#define IRQ_VICSOURCE28&t;&t;(IRQ_VIC_START + INT_VICSOURCE28)
DECL|macro|IRQ_VICSOURCE29
mdefine_line|#define IRQ_VICSOURCE29&t;&t;(IRQ_VIC_START + INT_VICSOURCE29)
DECL|macro|IRQ_VICSOURCE30
mdefine_line|#define IRQ_VICSOURCE30&t;&t;(IRQ_VIC_START + INT_VICSOURCE30)
DECL|macro|IRQ_VICSOURCE31
mdefine_line|#define IRQ_VICSOURCE31&t;&t;(IRQ_VIC_START + INT_VICSOURCE31)
DECL|macro|IRQ_VIC_END
mdefine_line|#define IRQ_VIC_END&t;&t;(IRQ_VIC_START + 31)
DECL|macro|IRQMASK_WDOGINT
mdefine_line|#define IRQMASK_WDOGINT&t;&t;INTMASK_WDOGINT
DECL|macro|IRQMASK_SOFTINT
mdefine_line|#define IRQMASK_SOFTINT&t;&t;INTMASK_SOFTINT
DECL|macro|IRQMASK_COMMRx
mdefine_line|#define IRQMASK_COMMRx &t;&t;INTMASK_COMMRx
DECL|macro|IRQMASK_COMMTx
mdefine_line|#define IRQMASK_COMMTx &t;&t;INTMASK_COMMTx
DECL|macro|IRQMASK_TIMERINT0_1
mdefine_line|#define IRQMASK_TIMERINT0_1&t;INTMASK_TIMERINT0_1
DECL|macro|IRQMASK_TIMERINT2_3
mdefine_line|#define IRQMASK_TIMERINT2_3&t;INTMASK_TIMERINT2_3
DECL|macro|IRQMASK_GPIOINT0
mdefine_line|#define IRQMASK_GPIOINT0&t;INTMASK_GPIOINT0
DECL|macro|IRQMASK_GPIOINT1
mdefine_line|#define IRQMASK_GPIOINT1&t;INTMASK_GPIOINT1
DECL|macro|IRQMASK_GPIOINT2
mdefine_line|#define IRQMASK_GPIOINT2&t;INTMASK_GPIOINT2
DECL|macro|IRQMASK_GPIOINT3
mdefine_line|#define IRQMASK_GPIOINT3&t;INTMASK_GPIOINT3
DECL|macro|IRQMASK_RTCINT
mdefine_line|#define IRQMASK_RTCINT &t;&t;INTMASK_RTCINT
DECL|macro|IRQMASK_SSPINT
mdefine_line|#define IRQMASK_SSPINT &t;&t;INTMASK_SSPINT
DECL|macro|IRQMASK_UARTINT0
mdefine_line|#define IRQMASK_UARTINT0&t;INTMASK_UARTINT0
DECL|macro|IRQMASK_UARTINT1
mdefine_line|#define IRQMASK_UARTINT1&t;INTMASK_UARTINT1
DECL|macro|IRQMASK_UARTINT2
mdefine_line|#define IRQMASK_UARTINT2&t;INTMASK_UARTINT2
DECL|macro|IRQMASK_SCIINT
mdefine_line|#define IRQMASK_SCIINT &t;&t;INTMASK_SCIINT
DECL|macro|IRQMASK_CLCDINT
mdefine_line|#define IRQMASK_CLCDINT&t;&t;INTMASK_CLCDINT
DECL|macro|IRQMASK_DMAINT
mdefine_line|#define IRQMASK_DMAINT &t;&t;INTMASK_DMAINT
DECL|macro|IRQMASK_PWRFAILINT
mdefine_line|#define IRQMASK_PWRFAILINT&t;INTMASK_PWRFAILINT
DECL|macro|IRQMASK_MBXINT
mdefine_line|#define IRQMASK_MBXINT &t;&t;INTMASK_MBXINT
DECL|macro|IRQMASK_GNDINT
mdefine_line|#define IRQMASK_GNDINT &t;&t;INTMASK_GNDINT
DECL|macro|IRQMASK_VICSOURCE21
mdefine_line|#define IRQMASK_VICSOURCE21&t;INTMASK_VICSOURCE21
DECL|macro|IRQMASK_VICSOURCE22
mdefine_line|#define IRQMASK_VICSOURCE22&t;INTMASK_VICSOURCE22
DECL|macro|IRQMASK_VICSOURCE23
mdefine_line|#define IRQMASK_VICSOURCE23&t;INTMASK_VICSOURCE23
DECL|macro|IRQMASK_VICSOURCE24
mdefine_line|#define IRQMASK_VICSOURCE24&t;INTMASK_VICSOURCE24
DECL|macro|IRQMASK_VICSOURCE25
mdefine_line|#define IRQMASK_VICSOURCE25&t;INTMASK_VICSOURCE25
DECL|macro|IRQMASK_VICSOURCE26
mdefine_line|#define IRQMASK_VICSOURCE26&t;INTMASK_VICSOURCE26
DECL|macro|IRQMASK_VICSOURCE27
mdefine_line|#define IRQMASK_VICSOURCE27&t;INTMASK_VICSOURCE27
DECL|macro|IRQMASK_VICSOURCE28
mdefine_line|#define IRQMASK_VICSOURCE28&t;INTMASK_VICSOURCE28
DECL|macro|IRQMASK_VICSOURCE29
mdefine_line|#define IRQMASK_VICSOURCE29&t;INTMASK_VICSOURCE29
DECL|macro|IRQMASK_VICSOURCE30
mdefine_line|#define IRQMASK_VICSOURCE30&t;INTMASK_VICSOURCE30
DECL|macro|IRQMASK_VICSOURCE31
mdefine_line|#define IRQMASK_VICSOURCE31&t;INTMASK_VICSOURCE31
multiline_comment|/* &n; *  FIQ interrupts definitions are the same the INT definitions.&n; */
DECL|macro|FIQ_WDOGINT
mdefine_line|#define FIQ_WDOGINT&t;&t;INT_WDOGINT
DECL|macro|FIQ_SOFTINT
mdefine_line|#define FIQ_SOFTINT&t;&t;INT_SOFTINT
DECL|macro|FIQ_COMMRx
mdefine_line|#define FIQ_COMMRx&t;&t;INT_COMMRx
DECL|macro|FIQ_COMMTx
mdefine_line|#define FIQ_COMMTx&t;&t;INT_COMMTx
DECL|macro|FIQ_TIMERINT0_1
mdefine_line|#define FIQ_TIMERINT0_1&t;&t;INT_TIMERINT0_1
DECL|macro|FIQ_TIMERINT2_3
mdefine_line|#define FIQ_TIMERINT2_3&t;&t;INT_TIMERINT2_3
DECL|macro|FIQ_GPIOINT0
mdefine_line|#define FIQ_GPIOINT0&t;&t;INT_GPIOINT0
DECL|macro|FIQ_GPIOINT1
mdefine_line|#define FIQ_GPIOINT1&t;&t;INT_GPIOINT1
DECL|macro|FIQ_GPIOINT2
mdefine_line|#define FIQ_GPIOINT2&t;&t;INT_GPIOINT2
DECL|macro|FIQ_GPIOINT3
mdefine_line|#define FIQ_GPIOINT3&t;&t;INT_GPIOINT3
DECL|macro|FIQ_RTCINT
mdefine_line|#define FIQ_RTCINT&t;&t;INT_RTCINT
DECL|macro|FIQ_SSPINT
mdefine_line|#define FIQ_SSPINT&t;&t;INT_SSPINT
DECL|macro|FIQ_UARTINT0
mdefine_line|#define FIQ_UARTINT0&t;&t;INT_UARTINT0
DECL|macro|FIQ_UARTINT1
mdefine_line|#define FIQ_UARTINT1&t;&t;INT_UARTINT1
DECL|macro|FIQ_UARTINT2
mdefine_line|#define FIQ_UARTINT2&t;&t;INT_UARTINT2
DECL|macro|FIQ_SCIINT
mdefine_line|#define FIQ_SCIINT&t;&t;INT_SCIINT
DECL|macro|FIQ_CLCDINT
mdefine_line|#define FIQ_CLCDINT&t;&t;INT_CLCDINT
DECL|macro|FIQ_DMAINT
mdefine_line|#define FIQ_DMAINT&t;&t;INT_DMAINT
DECL|macro|FIQ_PWRFAILINT
mdefine_line|#define FIQ_PWRFAILINT &t;&t;INT_PWRFAILINT
DECL|macro|FIQ_MBXINT
mdefine_line|#define FIQ_MBXINT&t;&t;INT_MBXINT
DECL|macro|FIQ_GNDINT
mdefine_line|#define FIQ_GNDINT&t;&t;INT_GNDINT
DECL|macro|FIQ_VICSOURCE21
mdefine_line|#define FIQ_VICSOURCE21&t;&t;INT_VICSOURCE21
DECL|macro|FIQ_VICSOURCE22
mdefine_line|#define FIQ_VICSOURCE22&t;&t;INT_VICSOURCE22
DECL|macro|FIQ_VICSOURCE23
mdefine_line|#define FIQ_VICSOURCE23&t;&t;INT_VICSOURCE23
DECL|macro|FIQ_VICSOURCE24
mdefine_line|#define FIQ_VICSOURCE24&t;&t;INT_VICSOURCE24
DECL|macro|FIQ_VICSOURCE25
mdefine_line|#define FIQ_VICSOURCE25&t;&t;INT_VICSOURCE25
DECL|macro|FIQ_VICSOURCE26
mdefine_line|#define FIQ_VICSOURCE26&t;&t;INT_VICSOURCE26
DECL|macro|FIQ_VICSOURCE27
mdefine_line|#define FIQ_VICSOURCE27&t;&t;INT_VICSOURCE27
DECL|macro|FIQ_VICSOURCE28
mdefine_line|#define FIQ_VICSOURCE28&t;&t;INT_VICSOURCE28
DECL|macro|FIQ_VICSOURCE29
mdefine_line|#define FIQ_VICSOURCE29&t;&t;INT_VICSOURCE29
DECL|macro|FIQ_VICSOURCE30
mdefine_line|#define FIQ_VICSOURCE30&t;&t;INT_VICSOURCE30
DECL|macro|FIQ_VICSOURCE31
mdefine_line|#define FIQ_VICSOURCE31&t;&t;INT_VICSOURCE31
DECL|macro|FIQMASK_WDOGINT
mdefine_line|#define FIQMASK_WDOGINT&t;&t;INTMASK_WDOGINT
DECL|macro|FIQMASK_SOFTINT
mdefine_line|#define FIQMASK_SOFTINT&t;&t;INTMASK_SOFTINT
DECL|macro|FIQMASK_COMMRx
mdefine_line|#define FIQMASK_COMMRx &t;&t;INTMASK_COMMRx
DECL|macro|FIQMASK_COMMTx
mdefine_line|#define FIQMASK_COMMTx &t;&t;INTMASK_COMMTx
DECL|macro|FIQMASK_TIMERINT0_1
mdefine_line|#define FIQMASK_TIMERINT0_1&t;INTMASK_TIMERINT0_1
DECL|macro|FIQMASK_TIMERINT2_3
mdefine_line|#define FIQMASK_TIMERINT2_3&t;INTMASK_TIMERINT2_3
DECL|macro|FIQMASK_GPIOINT0
mdefine_line|#define FIQMASK_GPIOINT0&t;INTMASK_GPIOINT0
DECL|macro|FIQMASK_GPIOINT1
mdefine_line|#define FIQMASK_GPIOINT1&t;INTMASK_GPIOINT1
DECL|macro|FIQMASK_GPIOINT2
mdefine_line|#define FIQMASK_GPIOINT2&t;INTMASK_GPIOINT2
DECL|macro|FIQMASK_GPIOINT3
mdefine_line|#define FIQMASK_GPIOINT3&t;INTMASK_GPIOINT3
DECL|macro|FIQMASK_RTCINT
mdefine_line|#define FIQMASK_RTCINT &t;&t;INTMASK_RTCINT
DECL|macro|FIQMASK_SSPINT
mdefine_line|#define FIQMASK_SSPINT &t;&t;INTMASK_SSPINT
DECL|macro|FIQMASK_UARTINT0
mdefine_line|#define FIQMASK_UARTINT0&t;INTMASK_UARTINT0
DECL|macro|FIQMASK_UARTINT1
mdefine_line|#define FIQMASK_UARTINT1&t;INTMASK_UARTINT1
DECL|macro|FIQMASK_UARTINT2
mdefine_line|#define FIQMASK_UARTINT2&t;INTMASK_UARTINT2
DECL|macro|FIQMASK_SCIINT
mdefine_line|#define FIQMASK_SCIINT &t;&t;INTMASK_SCIINT
DECL|macro|FIQMASK_CLCDINT
mdefine_line|#define FIQMASK_CLCDINT&t;&t;INTMASK_CLCDINT
DECL|macro|FIQMASK_DMAINT
mdefine_line|#define FIQMASK_DMAINT &t;&t;INTMASK_DMAINT
DECL|macro|FIQMASK_PWRFAILINT
mdefine_line|#define FIQMASK_PWRFAILINT&t;INTMASK_PWRFAILINT
DECL|macro|FIQMASK_MBXINT
mdefine_line|#define FIQMASK_MBXINT &t;&t;INTMASK_MBXINT
DECL|macro|FIQMASK_GNDINT
mdefine_line|#define FIQMASK_GNDINT &t;&t;INTMASK_GNDINT
DECL|macro|FIQMASK_VICSOURCE21
mdefine_line|#define FIQMASK_VICSOURCE21&t;INTMASK_VICSOURCE21
DECL|macro|FIQMASK_VICSOURCE22
mdefine_line|#define FIQMASK_VICSOURCE22&t;INTMASK_VICSOURCE22
DECL|macro|FIQMASK_VICSOURCE23
mdefine_line|#define FIQMASK_VICSOURCE23&t;INTMASK_VICSOURCE23
DECL|macro|FIQMASK_VICSOURCE24
mdefine_line|#define FIQMASK_VICSOURCE24&t;INTMASK_VICSOURCE24
DECL|macro|FIQMASK_VICSOURCE25
mdefine_line|#define FIQMASK_VICSOURCE25&t;INTMASK_VICSOURCE25
DECL|macro|FIQMASK_VICSOURCE26
mdefine_line|#define FIQMASK_VICSOURCE26&t;INTMASK_VICSOURCE26
DECL|macro|FIQMASK_VICSOURCE27
mdefine_line|#define FIQMASK_VICSOURCE27&t;INTMASK_VICSOURCE27
DECL|macro|FIQMASK_VICSOURCE28
mdefine_line|#define FIQMASK_VICSOURCE28&t;INTMASK_VICSOURCE28
DECL|macro|FIQMASK_VICSOURCE29
mdefine_line|#define FIQMASK_VICSOURCE29&t;INTMASK_VICSOURCE29
DECL|macro|FIQMASK_VICSOURCE30
mdefine_line|#define FIQMASK_VICSOURCE30&t;INTMASK_VICSOURCE30
DECL|macro|FIQMASK_VICSOURCE31
mdefine_line|#define FIQMASK_VICSOURCE31&t;INTMASK_VICSOURCE31
multiline_comment|/*&n; * Secondary interrupt controller&n; */
DECL|macro|IRQ_SIC_START
mdefine_line|#define IRQ_SIC_START&t;&t;32
DECL|macro|IRQ_SIC_MMCI0B
mdefine_line|#define IRQ_SIC_MMCI0B &t;&t;(IRQ_SIC_START + SIC_INT_MMCI0B)
DECL|macro|IRQ_SIC_MMCI1B
mdefine_line|#define IRQ_SIC_MMCI1B &t;&t;(IRQ_SIC_START + SIC_INT_MMCI1B)
DECL|macro|IRQ_SIC_KMI0
mdefine_line|#define IRQ_SIC_KMI0&t;&t;(IRQ_SIC_START + SIC_INT_KMI0)
DECL|macro|IRQ_SIC_KMI1
mdefine_line|#define IRQ_SIC_KMI1&t;&t;(IRQ_SIC_START + SIC_INT_KMI1)
DECL|macro|IRQ_SIC_SCI3
mdefine_line|#define IRQ_SIC_SCI3&t;&t;(IRQ_SIC_START + SIC_INT_SCI3)
DECL|macro|IRQ_SIC_UART3
mdefine_line|#define IRQ_SIC_UART3&t;&t;(IRQ_SIC_START + SIC_INT_UART3)
DECL|macro|IRQ_SIC_CLCD
mdefine_line|#define IRQ_SIC_CLCD&t;&t;(IRQ_SIC_START + SIC_INT_CLCD)
DECL|macro|IRQ_SIC_TOUCH
mdefine_line|#define IRQ_SIC_TOUCH&t;&t;(IRQ_SIC_START + SIC_INT_TOUCH)
DECL|macro|IRQ_SIC_KEYPAD
mdefine_line|#define IRQ_SIC_KEYPAD &t;&t;(IRQ_SIC_START + SIC_INT_KEYPAD)
DECL|macro|IRQ_SIC_DoC
mdefine_line|#define IRQ_SIC_DoC&t;&t;(IRQ_SIC_START + SIC_INT_DoC)
DECL|macro|IRQ_SIC_MMCI0A
mdefine_line|#define IRQ_SIC_MMCI0A &t;&t;(IRQ_SIC_START + SIC_INT_MMCI0A)
DECL|macro|IRQ_SIC_MMCI1A
mdefine_line|#define IRQ_SIC_MMCI1A &t;&t;(IRQ_SIC_START + SIC_INT_MMCI1A)
DECL|macro|IRQ_SIC_AACI
mdefine_line|#define IRQ_SIC_AACI&t;&t;(IRQ_SIC_START + SIC_INT_AACI)
DECL|macro|IRQ_SIC_ETH
mdefine_line|#define IRQ_SIC_ETH&t;&t;(IRQ_SIC_START + SIC_INT_ETH)
DECL|macro|IRQ_SIC_USB
mdefine_line|#define IRQ_SIC_USB&t;&t;(IRQ_SIC_START + SIC_INT_USB)
DECL|macro|IRQ_SIC_PCI0
mdefine_line|#define IRQ_SIC_PCI0&t;&t;(IRQ_SIC_START + SIC_INT_PCI0)
DECL|macro|IRQ_SIC_PCI1
mdefine_line|#define IRQ_SIC_PCI1&t;&t;(IRQ_SIC_START + SIC_INT_PCI1)
DECL|macro|IRQ_SIC_PCI2
mdefine_line|#define IRQ_SIC_PCI2&t;&t;(IRQ_SIC_START + SIC_INT_PCI2)
DECL|macro|IRQ_SIC_PCI3
mdefine_line|#define IRQ_SIC_PCI3&t;&t;(IRQ_SIC_START + SIC_INT_PCI3)
DECL|macro|IRQ_SIC_END
mdefine_line|#define IRQ_SIC_END&t;&t;63
DECL|macro|SIC_IRQMASK_MMCI0B
mdefine_line|#define SIC_IRQMASK_MMCI0B&t;SIC_INTMASK_MMCI0B
DECL|macro|SIC_IRQMASK_MMCI1B
mdefine_line|#define SIC_IRQMASK_MMCI1B&t;SIC_INTMASK_MMCI1B
DECL|macro|SIC_IRQMASK_KMI0
mdefine_line|#define SIC_IRQMASK_KMI0&t;SIC_INTMASK_KMI0
DECL|macro|SIC_IRQMASK_KMI1
mdefine_line|#define SIC_IRQMASK_KMI1&t;SIC_INTMASK_KMI1
DECL|macro|SIC_IRQMASK_SCI3
mdefine_line|#define SIC_IRQMASK_SCI3&t;SIC_INTMASK_SCI3
DECL|macro|SIC_IRQMASK_UART3
mdefine_line|#define SIC_IRQMASK_UART3&t;SIC_INTMASK_UART3
DECL|macro|SIC_IRQMASK_CLCD
mdefine_line|#define SIC_IRQMASK_CLCD&t;SIC_INTMASK_CLCD
DECL|macro|SIC_IRQMASK_TOUCH
mdefine_line|#define SIC_IRQMASK_TOUCH&t;SIC_INTMASK_TOUCH
DECL|macro|SIC_IRQMASK_KEYPAD
mdefine_line|#define SIC_IRQMASK_KEYPAD&t;SIC_INTMASK_KEYPAD
DECL|macro|SIC_IRQMASK_DoC
mdefine_line|#define SIC_IRQMASK_DoC&t;&t;SIC_INTMASK_DoC
DECL|macro|SIC_IRQMASK_MMCI0A
mdefine_line|#define SIC_IRQMASK_MMCI0A&t;SIC_INTMASK_MMCI0A
DECL|macro|SIC_IRQMASK_MMCI1A
mdefine_line|#define SIC_IRQMASK_MMCI1A&t;SIC_INTMASK_MMCI1A
DECL|macro|SIC_IRQMASK_AACI
mdefine_line|#define SIC_IRQMASK_AACI&t;SIC_INTMASK_AACI
DECL|macro|SIC_IRQMASK_ETH
mdefine_line|#define SIC_IRQMASK_ETH&t;&t;SIC_INTMASK_ETH
DECL|macro|SIC_IRQMASK_USB
mdefine_line|#define SIC_IRQMASK_USB&t;&t;SIC_INTMASK_USB
DECL|macro|SIC_IRQMASK_PCI0
mdefine_line|#define SIC_IRQMASK_PCI0&t;SIC_INTMASK_PCI0
DECL|macro|SIC_IRQMASK_PCI1
mdefine_line|#define SIC_IRQMASK_PCI1&t;SIC_INTMASK_PCI1
DECL|macro|SIC_IRQMASK_PCI2
mdefine_line|#define SIC_IRQMASK_PCI2&t;SIC_INTMASK_PCI2
DECL|macro|SIC_IRQMASK_PCI3
mdefine_line|#define SIC_IRQMASK_PCI3&t;SIC_INTMASK_PCI3
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;64
eof
