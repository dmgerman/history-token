multiline_comment|/* linux/include/asm-arm/arch-s3c2410/irqs.h&n; *&n; * Copyright (c) 2003-2005 Simtec Electronics&n; *   Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Changelog:&n; *  12-May-2003 BJD  Created file&n; *  08-Jan-2003 BJD  Linux 2.6.0 version, moved BAST bits out&n; *  12-Mar-2004 BJD  Fixed bug in header protection&n; *  10-Feb-2005 BJD  Added camera IRQ from guillaume.gourat@nexvision.tv&n; *  28-Feb-2005 BJD  Updated s3c2440 IRQs&n; */
macro_line|#ifndef __ASM_ARCH_IRQS_H
DECL|macro|__ASM_ARCH_IRQS_H
mdefine_line|#define __ASM_ARCH_IRQS_H __FILE__
multiline_comment|/* we keep the first set of CPU IRQs out of the range of&n; * the ISA space, so that the PC104 has them to itself&n; * and we don&squot;t end up having to do horrible things to the&n; * standard ISA drivers....&n; */
DECL|macro|S3C2410_CPUIRQ_OFFSET
mdefine_line|#define S3C2410_CPUIRQ_OFFSET&t; (16)
DECL|macro|S3C2410_IRQ
mdefine_line|#define S3C2410_IRQ(x) ((x) + S3C2410_CPUIRQ_OFFSET)
multiline_comment|/* main cpu interrupts */
DECL|macro|IRQ_EINT0
mdefine_line|#define IRQ_EINT0      S3C2410_IRQ(0)&t;    /* 16 */
DECL|macro|IRQ_EINT1
mdefine_line|#define IRQ_EINT1      S3C2410_IRQ(1)
DECL|macro|IRQ_EINT2
mdefine_line|#define IRQ_EINT2      S3C2410_IRQ(2)
DECL|macro|IRQ_EINT3
mdefine_line|#define IRQ_EINT3      S3C2410_IRQ(3)
DECL|macro|IRQ_EINT4t7
mdefine_line|#define IRQ_EINT4t7    S3C2410_IRQ(4)&t;    /* 20 */
DECL|macro|IRQ_EINT8t23
mdefine_line|#define IRQ_EINT8t23   S3C2410_IRQ(5)
DECL|macro|IRQ_RESERVED6
mdefine_line|#define IRQ_RESERVED6  S3C2410_IRQ(6)&t;    /* for s3c2410 */
DECL|macro|IRQ_CAM
mdefine_line|#define IRQ_CAM        S3C2410_IRQ(6)&t;    /* for s3c2440 */
DECL|macro|IRQ_BATT_FLT
mdefine_line|#define IRQ_BATT_FLT   S3C2410_IRQ(7)
DECL|macro|IRQ_TICK
mdefine_line|#define IRQ_TICK       S3C2410_IRQ(8)&t;    /* 24 */
DECL|macro|IRQ_WDT
mdefine_line|#define IRQ_WDT&t;       S3C2410_IRQ(9)
DECL|macro|IRQ_TIMER0
mdefine_line|#define IRQ_TIMER0     S3C2410_IRQ(10)
DECL|macro|IRQ_TIMER1
mdefine_line|#define IRQ_TIMER1     S3C2410_IRQ(11)
DECL|macro|IRQ_TIMER2
mdefine_line|#define IRQ_TIMER2     S3C2410_IRQ(12)
DECL|macro|IRQ_TIMER3
mdefine_line|#define IRQ_TIMER3     S3C2410_IRQ(13)
DECL|macro|IRQ_TIMER4
mdefine_line|#define IRQ_TIMER4     S3C2410_IRQ(14)
DECL|macro|IRQ_UART2
mdefine_line|#define IRQ_UART2      S3C2410_IRQ(15)
DECL|macro|IRQ_LCD
mdefine_line|#define IRQ_LCD&t;       S3C2410_IRQ(16)&t;    /* 32 */
DECL|macro|IRQ_DMA0
mdefine_line|#define IRQ_DMA0       S3C2410_IRQ(17)
DECL|macro|IRQ_DMA1
mdefine_line|#define IRQ_DMA1       S3C2410_IRQ(18)
DECL|macro|IRQ_DMA2
mdefine_line|#define IRQ_DMA2       S3C2410_IRQ(19)
DECL|macro|IRQ_DMA3
mdefine_line|#define IRQ_DMA3       S3C2410_IRQ(20)
DECL|macro|IRQ_SDI
mdefine_line|#define IRQ_SDI&t;       S3C2410_IRQ(21)
DECL|macro|IRQ_SPI0
mdefine_line|#define IRQ_SPI0       S3C2410_IRQ(22)
DECL|macro|IRQ_UART1
mdefine_line|#define IRQ_UART1      S3C2410_IRQ(23)
DECL|macro|IRQ_RESERVED24
mdefine_line|#define IRQ_RESERVED24 S3C2410_IRQ(24)&t;    /* 40 */
DECL|macro|IRQ_NFCON
mdefine_line|#define IRQ_NFCON      S3C2410_IRQ(24)&t;    /* for s3c2440 */
DECL|macro|IRQ_USBD
mdefine_line|#define IRQ_USBD       S3C2410_IRQ(25)
DECL|macro|IRQ_USBH
mdefine_line|#define IRQ_USBH       S3C2410_IRQ(26)
DECL|macro|IRQ_IIC
mdefine_line|#define IRQ_IIC&t;       S3C2410_IRQ(27)
DECL|macro|IRQ_UART0
mdefine_line|#define IRQ_UART0      S3C2410_IRQ(28)&t;    /* 44 */
DECL|macro|IRQ_SPI1
mdefine_line|#define IRQ_SPI1       S3C2410_IRQ(29)
DECL|macro|IRQ_RTC
mdefine_line|#define IRQ_RTC&t;       S3C2410_IRQ(30)
DECL|macro|IRQ_ADCPARENT
mdefine_line|#define IRQ_ADCPARENT  S3C2410_IRQ(31)
multiline_comment|/* interrupts generated from the external interrupts sources */
DECL|macro|IRQ_EINT4
mdefine_line|#define IRQ_EINT4      S3C2410_IRQ(32)&t;   /* 48 */
DECL|macro|IRQ_EINT5
mdefine_line|#define IRQ_EINT5      S3C2410_IRQ(33)
DECL|macro|IRQ_EINT6
mdefine_line|#define IRQ_EINT6      S3C2410_IRQ(34)
DECL|macro|IRQ_EINT7
mdefine_line|#define IRQ_EINT7      S3C2410_IRQ(35)
DECL|macro|IRQ_EINT8
mdefine_line|#define IRQ_EINT8      S3C2410_IRQ(36)
DECL|macro|IRQ_EINT9
mdefine_line|#define IRQ_EINT9      S3C2410_IRQ(37)
DECL|macro|IRQ_EINT10
mdefine_line|#define IRQ_EINT10     S3C2410_IRQ(38)
DECL|macro|IRQ_EINT11
mdefine_line|#define IRQ_EINT11     S3C2410_IRQ(39)
DECL|macro|IRQ_EINT12
mdefine_line|#define IRQ_EINT12     S3C2410_IRQ(40)
DECL|macro|IRQ_EINT13
mdefine_line|#define IRQ_EINT13     S3C2410_IRQ(41)
DECL|macro|IRQ_EINT14
mdefine_line|#define IRQ_EINT14     S3C2410_IRQ(42)
DECL|macro|IRQ_EINT15
mdefine_line|#define IRQ_EINT15     S3C2410_IRQ(43)
DECL|macro|IRQ_EINT16
mdefine_line|#define IRQ_EINT16     S3C2410_IRQ(44)
DECL|macro|IRQ_EINT17
mdefine_line|#define IRQ_EINT17     S3C2410_IRQ(45)
DECL|macro|IRQ_EINT18
mdefine_line|#define IRQ_EINT18     S3C2410_IRQ(46)
DECL|macro|IRQ_EINT19
mdefine_line|#define IRQ_EINT19     S3C2410_IRQ(47)
DECL|macro|IRQ_EINT20
mdefine_line|#define IRQ_EINT20     S3C2410_IRQ(48)&t;   /* 64 */
DECL|macro|IRQ_EINT21
mdefine_line|#define IRQ_EINT21     S3C2410_IRQ(49)
DECL|macro|IRQ_EINT22
mdefine_line|#define IRQ_EINT22     S3C2410_IRQ(50)
DECL|macro|IRQ_EINT23
mdefine_line|#define IRQ_EINT23     S3C2410_IRQ(51)
DECL|macro|IRQ_EINT
mdefine_line|#define IRQ_EINT(x)    S3C2410_IRQ((x &gt;= 4) ? (IRQ_EINT4 + (x) - 4) : (S3C2410_IRQ(0) + (x)))
DECL|macro|IRQ_LCD_FIFO
mdefine_line|#define IRQ_LCD_FIFO   S3C2410_IRQ(52)
DECL|macro|IRQ_LCD_FRAME
mdefine_line|#define IRQ_LCD_FRAME  S3C2410_IRQ(53)
multiline_comment|/* IRQs for the interal UARTs, and ADC&n; * these need to be ordered in number of appearance in the&n; * SUBSRC mask register&n;*/
DECL|macro|IRQ_S3CUART_RX0
mdefine_line|#define IRQ_S3CUART_RX0  S3C2410_IRQ(54)   /* 70 */
DECL|macro|IRQ_S3CUART_TX0
mdefine_line|#define IRQ_S3CUART_TX0  S3C2410_IRQ(55)   /* 71 */
DECL|macro|IRQ_S3CUART_ERR0
mdefine_line|#define IRQ_S3CUART_ERR0 S3C2410_IRQ(56)
DECL|macro|IRQ_S3CUART_RX1
mdefine_line|#define IRQ_S3CUART_RX1  S3C2410_IRQ(57)
DECL|macro|IRQ_S3CUART_TX1
mdefine_line|#define IRQ_S3CUART_TX1  S3C2410_IRQ(58)
DECL|macro|IRQ_S3CUART_ERR1
mdefine_line|#define IRQ_S3CUART_ERR1 S3C2410_IRQ(59)
DECL|macro|IRQ_S3CUART_RX2
mdefine_line|#define IRQ_S3CUART_RX2  S3C2410_IRQ(60)
DECL|macro|IRQ_S3CUART_TX2
mdefine_line|#define IRQ_S3CUART_TX2  S3C2410_IRQ(61)
DECL|macro|IRQ_S3CUART_ERR2
mdefine_line|#define IRQ_S3CUART_ERR2 S3C2410_IRQ(62)
DECL|macro|IRQ_TC
mdefine_line|#define IRQ_TC&t;&t; S3C2410_IRQ(63)
DECL|macro|IRQ_ADC
mdefine_line|#define IRQ_ADC&t;&t; S3C2410_IRQ(64)
multiline_comment|/* extra irqs for s3c2440 */
DECL|macro|IRQ_S3C2440_CAM_C
mdefine_line|#define IRQ_S3C2440_CAM_C&t;S3C2410_IRQ(65)
DECL|macro|IRQ_S3C2440_CAM_P
mdefine_line|#define IRQ_S3C2440_CAM_P&t;S3C2410_IRQ(66)
DECL|macro|IRQ_S3C2440_WDT
mdefine_line|#define IRQ_S3C2440_WDT&t;&t;S3C2410_IRQ(67)
DECL|macro|IRQ_S3C2440_AC97
mdefine_line|#define IRQ_S3C2440_AC97&t;S3C2410_IRQ(68)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS (IRQ_S3C2440_AC97+1)
macro_line|#endif /* __ASM_ARCH_IRQ_H */
eof
