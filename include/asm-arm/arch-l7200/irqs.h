multiline_comment|/*&n; * include/asm-arm/arch-l7200/irqs.h&n; *&n; * Copyright (C) 2000 Rob Scott (rscott@mtrob.fdns.net)&n; *                    Steve Hill (sjhill@cotw.com)&n; *&n; * Changelog:&n; *   01-02-2000 RS&t;Create l7200 version&n; *   03-28-2000 SJH&t;Removed unused interrupt&n; */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS          32
DECL|macro|IRQ_STWDOG
mdefine_line|#define IRQ_STWDOG        0   /* Watchdog timer */
DECL|macro|IRQ_PROG
mdefine_line|#define IRQ_PROG          1   /* Programmable interrupt */
DECL|macro|IRQ_DEBUG_RX
mdefine_line|#define IRQ_DEBUG_RX      2   /* Comm Rx debug */
DECL|macro|IRQ_DEBUG_TX
mdefine_line|#define IRQ_DEBUG_TX      3   /* Comm Tx debug */
DECL|macro|IRQ_GCTC1
mdefine_line|#define IRQ_GCTC1         4   /* Timer 1 */
DECL|macro|IRQ_GCTC2
mdefine_line|#define IRQ_GCTC2         5   /* Timer 2 */
DECL|macro|IRQ_DMA
mdefine_line|#define IRQ_DMA           6   /* DMA controller */
DECL|macro|IRQ_CLCD
mdefine_line|#define IRQ_CLCD          7   /* Color LCD controller */
DECL|macro|IRQ_SM_RX
mdefine_line|#define IRQ_SM_RX         8   /* Smart card */
DECL|macro|IRQ_SM_TX
mdefine_line|#define IRQ_SM_TX         9   /* Smart cart */
DECL|macro|IRQ_SM_RST
mdefine_line|#define IRQ_SM_RST       10   /* Smart card */
DECL|macro|IRQ_SIB
mdefine_line|#define IRQ_SIB          11   /* Serial Interface Bus */
DECL|macro|IRQ_MMC
mdefine_line|#define IRQ_MMC          12   /* MultiMediaCard */
DECL|macro|IRQ_SSP1
mdefine_line|#define IRQ_SSP1         13   /* Synchronous Serial Port 1 */
DECL|macro|IRQ_SSP2
mdefine_line|#define IRQ_SSP2         14   /* Synchronous Serial Port 1 */
DECL|macro|IRQ_SPI
mdefine_line|#define IRQ_SPI          15   /* SPI slave */
DECL|macro|IRQ_UART_1
mdefine_line|#define IRQ_UART_1       16   /* UART 1 */
DECL|macro|IRQ_UART_2
mdefine_line|#define IRQ_UART_2       17   /* UART 2 */
DECL|macro|IRQ_IRDA
mdefine_line|#define IRQ_IRDA         18   /* IRDA */
DECL|macro|IRQ_RTC_TICK
mdefine_line|#define IRQ_RTC_TICK     19   /* Real Time Clock tick */
DECL|macro|IRQ_RTC_ALARM
mdefine_line|#define IRQ_RTC_ALARM    20   /* Real Time Clock alarm */
DECL|macro|IRQ_GPIO
mdefine_line|#define IRQ_GPIO         21   /* General Purpose IO */
DECL|macro|IRQ_GPIO_DMA
mdefine_line|#define IRQ_GPIO_DMA     22   /* General Purpose IO, DMA */
DECL|macro|IRQ_M2M
mdefine_line|#define IRQ_M2M          23   /* Memory to memory DMA  */
DECL|macro|IRQ_RESERVED
mdefine_line|#define IRQ_RESERVED     24   /* RESERVED, don&squot;t use */
DECL|macro|IRQ_INTF
mdefine_line|#define IRQ_INTF         25   /* External active low interrupt */
DECL|macro|IRQ_INT0
mdefine_line|#define IRQ_INT0         26   /* External active low interrupt */
DECL|macro|IRQ_INT1
mdefine_line|#define IRQ_INT1         27   /* External active low interrupt */
DECL|macro|IRQ_INT2
mdefine_line|#define IRQ_INT2         28   /* External active low interrupt */
DECL|macro|IRQ_INT3
mdefine_line|#define IRQ_INT3         29   /* External active low interrupt */
DECL|macro|IRQ_BAT_LO
mdefine_line|#define IRQ_BAT_LO       30   /* Low batery or external power */
DECL|macro|IRQ_MEDIA_CHG
mdefine_line|#define IRQ_MEDIA_CHG    31   /* Media change interrupt */
eof
