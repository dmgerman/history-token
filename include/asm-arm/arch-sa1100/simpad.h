multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/simpad.h&n; *&n; * based of assabet.h same as HUW_Webpanel&n; *&n; * This file contains the hardware specific definitions for SIMpad&n; *&n; * 2001/05/14 Juergen Messerer &lt;juergen.messerer@freesurf.ch&gt;&n; */
macro_line|#ifndef __ASM_ARCH_SIMPAD_H
DECL|macro|__ASM_ARCH_SIMPAD_H
mdefine_line|#define __ASM_ARCH_SIMPAD_H
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
DECL|macro|GPIO_POWER_BUTTON
mdefine_line|#define GPIO_POWER_BUTTON&t;GPIO_GPIO0
DECL|macro|GPIO_UCB1300_IRQ
mdefine_line|#define GPIO_UCB1300_IRQ&t;GPIO_GPIO22&t;/* UCB GPIO and touchscreen */
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
DECL|macro|IRQ_GPIO_POWER_BUTTON
mdefine_line|#define IRQ_GPIO_POWER_BUTTON IRQ_GPIO0
multiline_comment|/*---  PCMCIA  ---*/
DECL|macro|GPIO_CF_CD
mdefine_line|#define GPIO_CF_CD              GPIO_GPIO24
DECL|macro|GPIO_CF_IRQ
mdefine_line|#define GPIO_CF_IRQ             GPIO_GPIO1
DECL|macro|IRQ_GPIO_CF_IRQ
mdefine_line|#define IRQ_GPIO_CF_IRQ         IRQ_GPIO1
DECL|macro|IRQ_GPIO_CF_CD
mdefine_line|#define IRQ_GPIO_CF_CD          IRQ_GPIO24
multiline_comment|/*--- SmartCard ---*/
DECL|macro|GPIO_SMART_CARD
mdefine_line|#define GPIO_SMART_CARD&t;&t;GPIO_GPIO10
DECL|macro|IRQ_GPIO_SMARD_CARD
mdefine_line|#define IRQ_GPIO_SMARD_CARD&t;IRQ_GPIO10
singleline_comment|// CS3 Latch is write only, a shadow is necessary
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
DECL|struct|simpad_battery
r_struct
id|simpad_battery
(brace
DECL|member|ac_status
r_int
r_char
id|ac_status
suffix:semicolon
multiline_comment|/* line connected yes/no */
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
multiline_comment|/* battery loading yes/no */
DECL|member|percentage
r_int
r_char
id|percentage
suffix:semicolon
multiline_comment|/* percentage loaded */
DECL|member|life
r_int
r_int
id|life
suffix:semicolon
multiline_comment|/* life till empty */
)brace
suffix:semicolon
multiline_comment|/* These should match the apm_bios.h definitions */
DECL|macro|SIMPAD_AC_STATUS_AC_OFFLINE
mdefine_line|#define SIMPAD_AC_STATUS_AC_OFFLINE      0x00
DECL|macro|SIMPAD_AC_STATUS_AC_ONLINE
mdefine_line|#define SIMPAD_AC_STATUS_AC_ONLINE       0x01
DECL|macro|SIMPAD_AC_STATUS_AC_BACKUP
mdefine_line|#define SIMPAD_AC_STATUS_AC_BACKUP       0x02   /* What does this mean? */
DECL|macro|SIMPAD_AC_STATUS_AC_UNKNOWN
mdefine_line|#define SIMPAD_AC_STATUS_AC_UNKNOWN      0xff
multiline_comment|/* These bitfields are rarely &quot;or&squot;d&quot; together */
DECL|macro|SIMPAD_BATT_STATUS_HIGH
mdefine_line|#define SIMPAD_BATT_STATUS_HIGH          0x01
DECL|macro|SIMPAD_BATT_STATUS_LOW
mdefine_line|#define SIMPAD_BATT_STATUS_LOW           0x02
DECL|macro|SIMPAD_BATT_STATUS_CRITICAL
mdefine_line|#define SIMPAD_BATT_STATUS_CRITICAL      0x04
DECL|macro|SIMPAD_BATT_STATUS_CHARGING
mdefine_line|#define SIMPAD_BATT_STATUS_CHARGING      0x08
DECL|macro|SIMPAD_BATT_STATUS_CHARGE_MAIN
mdefine_line|#define SIMPAD_BATT_STATUS_CHARGE_MAIN   0x10
DECL|macro|SIMPAD_BATT_STATUS_DEAD
mdefine_line|#define SIMPAD_BATT_STATUS_DEAD          0x20   /* Battery will not charge */
DECL|macro|SIMPAD_BATT_NOT_INSTALLED
mdefine_line|#define SIMPAD_BATT_NOT_INSTALLED        0x20   /* For expansion pack batteries */
DECL|macro|SIMPAD_BATT_STATUS_FULL
mdefine_line|#define SIMPAD_BATT_STATUS_FULL          0x40   /* Battery fully charged (and connected to AC) */
DECL|macro|SIMPAD_BATT_STATUS_NOBATT
mdefine_line|#define SIMPAD_BATT_STATUS_NOBATT        0x80
DECL|macro|SIMPAD_BATT_STATUS_UNKNOWN
mdefine_line|#define SIMPAD_BATT_STATUS_UNKNOWN       0xff
r_extern
r_int
id|simpad_get_battery
c_func
(paren
r_struct
id|simpad_battery
op_star
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// __ASM_ARCH_SIMPAD_H
eof
