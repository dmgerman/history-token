multiline_comment|/* linux/include/asm-arm/arch-s3c2410/regs-serial.h&n; *&n; *  From linux/include/asm-arm/hardware/serial_s3c2410.h&n; *&n; *  Internal header file for Samsung S3C2410 serial ports (UART0-2)&n; *&n; *  Copyright (C) 2002 Shane Nay (shane@minirl.com)&n; *&n; *  Additional defines, (c) 2003 Simtec Electronics (linux@simtec.co.uk)&n; *&n; *  Adapted from:&n; *&n; *  Internal header file for MX1ADS serial ports (UART1 &amp; 2)&n; *&n; *  Copyright (C) 2002 Shane Nay (shane@minirl.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_ARM_REGS_SERIAL_H
DECL|macro|__ASM_ARM_REGS_SERIAL_H
mdefine_line|#define __ASM_ARM_REGS_SERIAL_H
DECL|macro|S3C2410_VA_UART0
mdefine_line|#define S3C2410_VA_UART0      (S3C2410_VA_UART)
DECL|macro|S3C2410_VA_UART1
mdefine_line|#define S3C2410_VA_UART1      (S3C2410_VA_UART + 0x4000 )
DECL|macro|S3C2410_VA_UART2
mdefine_line|#define S3C2410_VA_UART2      (S3C2410_VA_UART + 0x8000 )
DECL|macro|S3C2410_PA_UART0
mdefine_line|#define S3C2410_PA_UART0      (S3C2410_PA_UART)
DECL|macro|S3C2410_PA_UART1
mdefine_line|#define S3C2410_PA_UART1      (S3C2410_PA_UART + 0x4000 )
DECL|macro|S3C2410_PA_UART2
mdefine_line|#define S3C2410_PA_UART2      (S3C2410_PA_UART + 0x8000 )
DECL|macro|S3C2410_URXH
mdefine_line|#define S3C2410_URXH&t;  (0x24)
DECL|macro|S3C2410_UTXH
mdefine_line|#define S3C2410_UTXH&t;  (0x20)
DECL|macro|S3C2410_ULCON
mdefine_line|#define S3C2410_ULCON&t;  (0x00)
DECL|macro|S3C2410_UCON
mdefine_line|#define S3C2410_UCON&t;  (0x04)
DECL|macro|S3C2410_UFCON
mdefine_line|#define S3C2410_UFCON&t;  (0x08)
DECL|macro|S3C2410_UMCON
mdefine_line|#define S3C2410_UMCON&t;  (0x0C)
DECL|macro|S3C2410_UBRDIV
mdefine_line|#define S3C2410_UBRDIV&t;  (0x28)
DECL|macro|S3C2410_UTRSTAT
mdefine_line|#define S3C2410_UTRSTAT&t;  (0x10)
DECL|macro|S3C2410_UERSTAT
mdefine_line|#define S3C2410_UERSTAT&t;  (0x14)
DECL|macro|S3C2410_UFSTAT
mdefine_line|#define S3C2410_UFSTAT&t;  (0x18)
DECL|macro|S3C2410_UMSTAT
mdefine_line|#define S3C2410_UMSTAT&t;  (0x1C)
DECL|macro|S3C2410_LCON_CFGMASK
mdefine_line|#define S3C2410_LCON_CFGMASK&t;  ((0xF&lt;&lt;3)|(0x3))
DECL|macro|S3C2410_LCON_CS5
mdefine_line|#define S3C2410_LCON_CS5&t;  (0x0)
DECL|macro|S3C2410_LCON_CS6
mdefine_line|#define S3C2410_LCON_CS6&t;  (0x1)
DECL|macro|S3C2410_LCON_CS7
mdefine_line|#define S3C2410_LCON_CS7&t;  (0x2)
DECL|macro|S3C2410_LCON_CS8
mdefine_line|#define S3C2410_LCON_CS8&t;  (0x3)
DECL|macro|S3C2410_LCON_CSMASK
mdefine_line|#define S3C2410_LCON_CSMASK&t;  (0x3)
DECL|macro|S3C2410_LCON_PNONE
mdefine_line|#define S3C2410_LCON_PNONE&t;  (0x0)
DECL|macro|S3C2410_LCON_PEVEN
mdefine_line|#define S3C2410_LCON_PEVEN&t;  (0x5 &lt;&lt; 3)
DECL|macro|S3C2410_LCON_PODD
mdefine_line|#define S3C2410_LCON_PODD&t;  (0x4 &lt;&lt; 3)
DECL|macro|S3C2410_LCON_PMASK
mdefine_line|#define S3C2410_LCON_PMASK&t;  (0x7 &lt;&lt; 3)
DECL|macro|S3C2410_LCON_STOPB
mdefine_line|#define S3C2410_LCON_STOPB&t;  (1&lt;&lt;2)
DECL|macro|S3C2410_LCON_IRM
mdefine_line|#define S3C2410_LCON_IRM          (1&lt;&lt;6)
DECL|macro|S3C2440_UCON_CLKMASK
mdefine_line|#define S3C2440_UCON_CLKMASK&t;  (3&lt;&lt;10)
DECL|macro|S3C2440_UCON_PCLK
mdefine_line|#define S3C2440_UCON_PCLK&t;  (0&lt;&lt;10)
DECL|macro|S3C2440_UCON_UCLK
mdefine_line|#define S3C2440_UCON_UCLK&t;  (1&lt;&lt;10)
DECL|macro|S3C2440_UCON_PCLK2
mdefine_line|#define S3C2440_UCON_PCLK2&t;  (2&lt;&lt;10)
DECL|macro|S3C2440_UCON_FCLK
mdefine_line|#define S3C2440_UCON_FCLK&t;  (3&lt;&lt;10)
DECL|macro|S3C2410_UCON_UCLK
mdefine_line|#define S3C2410_UCON_UCLK&t;  (1&lt;&lt;10)
DECL|macro|S3C2410_UCON_SBREAK
mdefine_line|#define S3C2410_UCON_SBREAK&t;  (1&lt;&lt;4)
DECL|macro|S3C2410_UCON_TXILEVEL
mdefine_line|#define S3C2410_UCON_TXILEVEL&t;  (1&lt;&lt;9)
DECL|macro|S3C2410_UCON_RXILEVEL
mdefine_line|#define S3C2410_UCON_RXILEVEL&t;  (1&lt;&lt;8)
DECL|macro|S3C2410_UCON_TXIRQMODE
mdefine_line|#define S3C2410_UCON_TXIRQMODE&t;  (1&lt;&lt;2)
DECL|macro|S3C2410_UCON_RXIRQMODE
mdefine_line|#define S3C2410_UCON_RXIRQMODE&t;  (1&lt;&lt;0)
DECL|macro|S3C2410_UCON_RXFIFO_TOI
mdefine_line|#define S3C2410_UCON_RXFIFO_TOI&t;  (1&lt;&lt;7)
DECL|macro|S3C2410_UCON_DEFAULT
mdefine_line|#define S3C2410_UCON_DEFAULT&t;  (S3C2410_UCON_TXILEVEL  | &bslash;&n;&t;&t;&t;&t;   S3C2410_UCON_RXILEVEL  | &bslash;&n;&t;&t;&t;&t;   S3C2410_UCON_TXIRQMODE | &bslash;&n;&t;&t;&t;&t;   S3C2410_UCON_RXIRQMODE | &bslash;&n;&t;&t;&t;&t;   S3C2410_UCON_RXFIFO_TOI)
DECL|macro|S3C2410_UFCON_FIFOMODE
mdefine_line|#define S3C2410_UFCON_FIFOMODE&t;  (1&lt;&lt;0)
DECL|macro|S3C2410_UFCON_TXTRIG0
mdefine_line|#define S3C2410_UFCON_TXTRIG0&t;  (0&lt;&lt;6)
DECL|macro|S3C2410_UFCON_RXTRIG8
mdefine_line|#define S3C2410_UFCON_RXTRIG8&t;  (1&lt;&lt;4)
DECL|macro|S3C2410_UFCON_RXTRIG12
mdefine_line|#define S3C2410_UFCON_RXTRIG12&t;  (2&lt;&lt;4)
multiline_comment|/* S3C2440 FIFO trigger levels */
DECL|macro|S3C2440_UFCON_RXTRIG1
mdefine_line|#define S3C2440_UFCON_RXTRIG1&t;  (0&lt;&lt;4)
DECL|macro|S3C2440_UFCON_RXTRIG8
mdefine_line|#define S3C2440_UFCON_RXTRIG8&t;  (1&lt;&lt;4)
DECL|macro|S3C2440_UFCON_RXTRIG16
mdefine_line|#define S3C2440_UFCON_RXTRIG16&t;  (2&lt;&lt;4)
DECL|macro|S3C2440_UFCON_RXTRIG32
mdefine_line|#define S3C2440_UFCON_RXTRIG32&t;  (3&lt;&lt;4)
DECL|macro|S3C2440_UFCON_TXTRIG0
mdefine_line|#define S3C2440_UFCON_TXTRIG0&t;  (0&lt;&lt;6)
DECL|macro|S3C2440_UFCON_TXTRIG16
mdefine_line|#define S3C2440_UFCON_TXTRIG16&t;  (1&lt;&lt;6)
DECL|macro|S3C2440_UFCON_TXTRIG32
mdefine_line|#define S3C2440_UFCON_TXTRIG32&t;  (2&lt;&lt;6)
DECL|macro|S3C2440_UFCON_TXTRIG48
mdefine_line|#define S3C2440_UFCON_TXTRIG48&t;  (3&lt;&lt;6)
DECL|macro|S3C2410_UFCON_RESETBOTH
mdefine_line|#define S3C2410_UFCON_RESETBOTH&t;  (3&lt;&lt;1)
DECL|macro|S3C2410_UFCON_RESETTX
mdefine_line|#define S3C2410_UFCON_RESETTX&t;  (1&lt;&lt;2)
DECL|macro|S3C2410_UFCON_RESETRX
mdefine_line|#define S3C2410_UFCON_RESETRX&t;  (1&lt;&lt;1)
DECL|macro|S3C2410_UFCON_DEFAULT
mdefine_line|#define S3C2410_UFCON_DEFAULT&t;  (S3C2410_UFCON_FIFOMODE | &bslash;&n;&t;&t;&t;&t;   S3C2410_UFCON_TXTRIG0  | &bslash;&n;&t;&t;&t;&t;   S3C2410_UFCON_RXTRIG8 )
DECL|macro|S3C2410_UMCOM_AFC
mdefine_line|#define&t;S3C2410_UMCOM_AFC&t;  (1&lt;&lt;4)
DECL|macro|S3C2410_UMCOM_RTS_LOW
mdefine_line|#define&t;S3C2410_UMCOM_RTS_LOW&t;  (1&lt;&lt;0)
DECL|macro|S3C2410_UFSTAT_TXFULL
mdefine_line|#define S3C2410_UFSTAT_TXFULL&t;  (1&lt;&lt;9)
DECL|macro|S3C2410_UFSTAT_RXFULL
mdefine_line|#define S3C2410_UFSTAT_RXFULL&t;  (1&lt;&lt;8)
DECL|macro|S3C2410_UFSTAT_TXMASK
mdefine_line|#define S3C2410_UFSTAT_TXMASK&t;  (15&lt;&lt;4)
DECL|macro|S3C2410_UFSTAT_TXSHIFT
mdefine_line|#define S3C2410_UFSTAT_TXSHIFT&t;  (4)
DECL|macro|S3C2410_UFSTAT_RXMASK
mdefine_line|#define S3C2410_UFSTAT_RXMASK&t;  (15&lt;&lt;0)
DECL|macro|S3C2410_UFSTAT_RXSHIFT
mdefine_line|#define S3C2410_UFSTAT_RXSHIFT&t;  (0)
DECL|macro|S3C2440_UFSTAT_TXFULL
mdefine_line|#define S3C2440_UFSTAT_TXFULL&t;  (1&lt;&lt;14)
DECL|macro|S3C2440_UFSTAT_RXFULL
mdefine_line|#define S3C2440_UFSTAT_RXFULL&t;  (1&lt;&lt;6)
DECL|macro|S3C2440_UFSTAT_TXSHIFT
mdefine_line|#define S3C2440_UFSTAT_TXSHIFT&t;  (8)
DECL|macro|S3C2440_UFSTAT_RXSHIFT
mdefine_line|#define S3C2440_UFSTAT_RXSHIFT&t;  (0)
DECL|macro|S3C2440_UFSTAT_TXMASK
mdefine_line|#define S3C2440_UFSTAT_TXMASK&t;  (63&lt;&lt;8)
DECL|macro|S3C2440_UFSTAT_RXMASK
mdefine_line|#define S3C2440_UFSTAT_RXMASK&t;  (63)
DECL|macro|S3C2410_UTRSTAT_TXE
mdefine_line|#define S3C2410_UTRSTAT_TXE&t;  (1&lt;&lt;2)
DECL|macro|S3C2410_UTRSTAT_TXFE
mdefine_line|#define S3C2410_UTRSTAT_TXFE&t;  (1&lt;&lt;1)
DECL|macro|S3C2410_UTRSTAT_RXDR
mdefine_line|#define S3C2410_UTRSTAT_RXDR&t;  (1&lt;&lt;0)
DECL|macro|S3C2410_UERSTAT_OVERRUN
mdefine_line|#define S3C2410_UERSTAT_OVERRUN&t;  (1&lt;&lt;0)
DECL|macro|S3C2410_UERSTAT_FRAME
mdefine_line|#define S3C2410_UERSTAT_FRAME&t;  (1&lt;&lt;2)
DECL|macro|S3C2410_UERSTAT_BREAK
mdefine_line|#define S3C2410_UERSTAT_BREAK&t;  (1&lt;&lt;3)
DECL|macro|S3C2410_UERSTAT_ANY
mdefine_line|#define S3C2410_UERSTAT_ANY&t;  (S3C2410_UERSTAT_OVERRUN | &bslash;&n;&t;&t;&t;&t;   S3C2410_UERSTAT_FRAME | &bslash;&n;&t;&t;&t;&t;   S3C2410_UERSTAT_BREAK)
DECL|macro|S3C2410_UMSTAT_CTS
mdefine_line|#define S3C2410_UMSTAT_CTS&t;  (1&lt;&lt;0)
DECL|macro|S3C2410_UMSTAT_DeltaCTS
mdefine_line|#define S3C2410_UMSTAT_DeltaCTS&t;  (1&lt;&lt;2)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* struct s3c24xx_uart_clksrc&n; *&n; * this structure defines a named clock source that can be used for the&n; * uart, so that the best clock can be selected for the requested baud&n; * rate.&n; *&n; * min_baud and max_baud define the range of baud-rates this clock is&n; * acceptable for, if they are both zero, it is assumed any baud rate that&n; * can be generated from this clock will be used.&n; *&n; * divisor gives the divisor from the clock to the one seen by the uart&n;*/
DECL|struct|s3c24xx_uart_clksrc
r_struct
id|s3c24xx_uart_clksrc
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|divisor
r_int
r_int
id|divisor
suffix:semicolon
DECL|member|min_baud
r_int
r_int
id|min_baud
suffix:semicolon
DECL|member|max_baud
r_int
r_int
id|max_baud
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* configuration structure for per-machine configurations for the&n; * serial port&n; *&n; * the pointer is setup by the machine specific initialisation from the&n; * arch/arm/mach-s3c2410/ directory.&n;*/
DECL|struct|s3c2410_uartcfg
r_struct
id|s3c2410_uartcfg
(brace
DECL|member|hwport
r_int
r_char
id|hwport
suffix:semicolon
multiline_comment|/* hardware port number */
DECL|member|unused
r_int
r_char
id|unused
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|uart_flags
r_int
r_int
id|uart_flags
suffix:semicolon
multiline_comment|/* default uart flags */
DECL|member|ucon
r_int
r_int
id|ucon
suffix:semicolon
multiline_comment|/* value of ucon for port */
DECL|member|ulcon
r_int
r_int
id|ulcon
suffix:semicolon
multiline_comment|/* value of ulcon for port */
DECL|member|ufcon
r_int
r_int
id|ufcon
suffix:semicolon
multiline_comment|/* value of ufcon for port */
DECL|member|clocks
r_struct
id|s3c24xx_uart_clksrc
op_star
id|clocks
suffix:semicolon
DECL|member|clocks_size
r_int
r_int
id|clocks_size
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* s3c24xx_uart_devs&n; *&n; * this is exported from the core as we cannot use driver_register(),&n; * or platform_add_device() before the console_initcall()&n;*/
r_extern
r_struct
id|platform_device
op_star
id|s3c24xx_uart_devs
(braket
l_int|3
)braket
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __ASM_ARM_REGS_SERIAL_H */
eof
