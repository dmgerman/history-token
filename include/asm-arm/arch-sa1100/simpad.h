multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/trizeps.h&n; *&n; * based of assabet.h same as HUW_Webpanel&n; *&n; * This file contains the hardware specific definitions for Trizeps&n; *&n; * 2001/03/14 Peter Lueg &lt;peter.lueg@dsa-ac.de&gt;&n; */
macro_line|#ifndef SIMPAD_H
DECL|macro|SIMPAD_H
mdefine_line|#define SIMPAD_H
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
macro_line|#error &quot;include &lt;asm/hardware.h&gt; instead&quot;
macro_line|#endif
multiline_comment|/* System Configuration Register flags */
DECL|macro|SCR_SDRAM_LOW
mdefine_line|#define SCR_SDRAM_LOW&t;(1&lt;&lt;2)&t;/* SDRAM size (low bit) */
DECL|macro|SCR_SDRAM_HIGH
mdefine_line|#define SCR_SDRAM_HIGH&t;(1&lt;&lt;3)&t;/* SDRAM size (high bit) */
DECL|macro|SCR_FLASH_LOW
mdefine_line|#define SCR_FLASH_LOW&t;(1&lt;&lt;4)&t;/* Flash size (low bit) */
DECL|macro|SCR_FLASH_HIGH
mdefine_line|#define SCR_FLASH_HIGH&t;(1&lt;&lt;5)&t;/* Flash size (high bit) */
DECL|macro|SCR_GFX
mdefine_line|#define SCR_GFX&t;&t;(1&lt;&lt;8)&t;/* Graphics Accelerator (0 = present) */
DECL|macro|SCR_SA1111
mdefine_line|#define SCR_SA1111&t;(1&lt;&lt;9)&t;/* Neponset (0 = present) */
DECL|macro|SCR_INIT
mdefine_line|#define SCR_INIT&t;-1
DECL|macro|GPIO_UART1_RTS
mdefine_line|#define GPIO_UART1_RTS&t;GPIO_GPIO14
DECL|macro|GPIO_UART1_DTR
mdefine_line|#define GPIO_UART1_DTR&t;GPIO_GPIO7
DECL|macro|GPIO_UART1_CTS
mdefine_line|#define GPIO_UART1_CTS&t;GPIO_GPIO8
DECL|macro|GPIO_UART1_DCD
mdefine_line|#define GPIO_UART1_DCD&t;GPIO_GPIO23
DECL|macro|GPIO_UART1_DSR
mdefine_line|#define GPIO_UART1_DSR&t;GPIO_GPIO6
DECL|macro|GPIO_UART3_RTS
mdefine_line|#define GPIO_UART3_RTS&t;GPIO_GPIO12
DECL|macro|GPIO_UART3_DTR
mdefine_line|#define GPIO_UART3_DTR&t;GPIO_GPIO16
DECL|macro|GPIO_UART3_CTS
mdefine_line|#define GPIO_UART3_CTS&t;GPIO_GPIO13
DECL|macro|GPIO_UART3_DCD
mdefine_line|#define GPIO_UART3_DCD&t;GPIO_GPIO18
DECL|macro|GPIO_UART3_DSR
mdefine_line|#define GPIO_UART3_DSR&t;GPIO_GPIO17
DECL|macro|IRQ_UART1_CTS
mdefine_line|#define IRQ_UART1_CTS&t;IRQ_GPIO15
DECL|macro|IRQ_UART1_DCD
mdefine_line|#define IRQ_UART1_DCD&t;GPIO_GPIO23
DECL|macro|IRQ_UART1_DSR
mdefine_line|#define IRQ_UART1_DSR&t;GPIO_GPIO6
DECL|macro|IRQ_UART3_CTS
mdefine_line|#define IRQ_UART3_CTS&t;GPIO_GPIO13
DECL|macro|IRQ_UART3_DCD
mdefine_line|#define IRQ_UART3_DCD&t;GPIO_GPIO18
DECL|macro|IRQ_UART3_DSR
mdefine_line|#define IRQ_UART3_DSR&t;GPIO_GPIO17
DECL|macro|GPIO_UCB1300_IRQ
mdefine_line|#define GPIO_UCB1300_IRQ&t;GPIO_GPIO (22)&t;/* UCB GPIO and touchscreen */
DECL|macro|IRQ_GPIO_UCB1300_IRQ
mdefine_line|#define IRQ_GPIO_UCB1300_IRQ IRQ_GPIO22
DECL|macro|SA1100_UART1_EXT
mdefine_line|#define SA1100_UART1_EXT &bslash;&n;  (struct huw_irq_desc){GPIO_UART1_CTS, IRQ_UART1_CTS, &bslash;&n;                        GPIO_UART1_DCD, IRQ_UART1_DCD, &bslash;&n;                        GPIO_UART1_DSR, IRQ_UART1_DSR}
DECL|macro|SA1100_UART3_EXT
mdefine_line|#define SA1100_UART3_EXT &bslash;&n;  (struct huw_irq_desc){GPIO_UART3_CTS, IRQ_UART3_CTS, &bslash;&n;                        GPIO_UART3_DCD, IRQ_UART3_DCD, &bslash;&n;                        GPIO_UART3_DSR, IRQ_UART3_DSR}
multiline_comment|/*---  PCMCIA  ---*/
DECL|macro|GPIO_CF_CD
mdefine_line|#define GPIO_CF_CD              GPIO_GPIO24
DECL|macro|GPIO_CF_IRQ
mdefine_line|#define GPIO_CF_IRQ             GPIO_GPIO1
DECL|macro|IRQ_GPIO_CF_IRQ
mdefine_line|#define IRQ_GPIO_CF_IRQ         IRQ_GPIO1
DECL|macro|IRQ_GPIO_CF_CD
mdefine_line|#define IRQ_GPIO_CF_CD          IRQ_GPIO24
singleline_comment|// CS3 Latch is write only, a shadow is neccessary
DECL|macro|CS3BUSTYPE
mdefine_line|#define CS3BUSTYPE unsigned volatile long
DECL|macro|CS3_BASE
mdefine_line|#define CS3_BASE        0xf1000000
DECL|macro|VCC_5V_EN
mdefine_line|#define VCC_5V_EN       0x0001
DECL|macro|VCC_3V_EN
mdefine_line|#define VCC_3V_EN       0x0002
DECL|macro|EN1
mdefine_line|#define EN1             0x0004
DECL|macro|EN0
mdefine_line|#define EN0             0x0008
DECL|macro|DISPLAY_ON
mdefine_line|#define DISPLAY_ON      0x0010
DECL|macro|PCMCIA_BUFF_DIS
mdefine_line|#define PCMCIA_BUFF_DIS 0x0020
DECL|macro|MQ_RESET
mdefine_line|#define MQ_RESET        0x0040
DECL|macro|PCMCIA_RESET
mdefine_line|#define PCMCIA_RESET    0x0080
DECL|macro|DECT_POWER_ON
mdefine_line|#define DECT_POWER_ON   0x0100
DECL|macro|IRDA_SD
mdefine_line|#define IRDA_SD         0x0200
DECL|macro|RS232_ON
mdefine_line|#define RS232_ON        0x0400
DECL|macro|SD_MEDIAQ
mdefine_line|#define SD_MEDIAQ       0x0800
DECL|macro|LED2_ON
mdefine_line|#define LED2_ON         0x1000
DECL|macro|IRDA_MODE
mdefine_line|#define IRDA_MODE       0x2000
DECL|macro|ENABLE_5V
mdefine_line|#define ENABLE_5V       0x4000
DECL|macro|RESET_SIMCARD
mdefine_line|#define RESET_SIMCARD   0x8000
DECL|macro|RS232_ENABLE
mdefine_line|#define RS232_ENABLE    0x0440
DECL|macro|PCMCIAMASK
mdefine_line|#define PCMCIAMASK      0x402f
macro_line|#ifndef __ASSEMBLY__
DECL|variable|cs3_shadow
r_static
r_int
id|cs3_shadow
suffix:semicolon
r_void
id|init_simpad_cs3
c_func
(paren
)paren
suffix:semicolon
r_void
id|PCMCIA_setbit
c_func
(paren
r_int
id|value
)paren
suffix:semicolon
r_void
id|PCMCIA_clearbit
c_func
(paren
r_int
id|value
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif 
singleline_comment|// SIMPAD_H
eof
