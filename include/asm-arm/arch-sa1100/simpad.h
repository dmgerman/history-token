multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/simpad.h&n; *&n; * based of assabet.h same as HUW_Webpanel&n; *&n; * This file contains the hardware specific definitions for SIMpad&n; *&n; * 2001/05/14 Juergen Messerer &lt;juergen.messerer@siemens.ch&gt;&n; */
macro_line|#ifndef SIMPAD_H
DECL|macro|SIMPAD_H
mdefine_line|#define SIMPAD_H
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
macro_line|#error &quot;include &lt;asm/hardware.h&gt; instead&quot;
macro_line|#endif
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
DECL|macro|GPIO_UCB1300_IRQ
mdefine_line|#define GPIO_UCB1300_IRQ&t;GPIO_GPIO (22)&t;/* UCB GPIO and touchscreen */
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
DECL|macro|IRQ_GPIO_UCB1300_IRQ
mdefine_line|#define IRQ_GPIO_UCB1300_IRQ IRQ_GPIO22 
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
singleline_comment|// For 5V PCMCIA 
DECL|macro|VCC_3V_EN
mdefine_line|#define VCC_3V_EN       0x0002 
singleline_comment|// FOR 3.3V PCMCIA
DECL|macro|EN1
mdefine_line|#define EN1             0x0004 
singleline_comment|// This is only for EPROM&squot;s
DECL|macro|EN0
mdefine_line|#define EN0             0x0008 
singleline_comment|// Both should be enable for 3.3V or 5V
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
singleline_comment|// Shutdown for powersave
DECL|macro|RS232_ON
mdefine_line|#define RS232_ON        0x0400
DECL|macro|SD_MEDIAQ
mdefine_line|#define SD_MEDIAQ       0x0800 
singleline_comment|// Shutdown for powersave
DECL|macro|LED2_ON
mdefine_line|#define LED2_ON         0x1000 
DECL|macro|IRDA_MODE
mdefine_line|#define IRDA_MODE       0x2000 
singleline_comment|// Fast/Slow IrDA mode
DECL|macro|ENABLE_5V
mdefine_line|#define ENABLE_5V       0x4000 
singleline_comment|// Enable 5V circuit
DECL|macro|RESET_SIMCARD
mdefine_line|#define RESET_SIMCARD   0x8000
DECL|macro|RS232_ENABLE
mdefine_line|#define RS232_ENABLE    0x0440
DECL|macro|PCMCIAMASK
mdefine_line|#define PCMCIAMASK      0x402f   
macro_line|#endif 
singleline_comment|// SIMPAD_H
eof
