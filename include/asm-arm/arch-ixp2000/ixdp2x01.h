multiline_comment|/*&n; * include/asm/arch/ixdp2x01.h&n; *&n; * Platform definitions for IXDP2X01 &amp;&amp; IXDP2801 systems&n; *&n; * Author: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * Copyright 2004 (c) MontaVista Software, Inc. &n; *&n; * Based on original code Copyright (c) 2002-2003 Intel Corporation&n; * &n; * This file is licensed under  the terms of the GNU General Public &n; * License version 2. This program is licensed &quot;as is&quot; without any &n; * warranty of any kind, whether express or implied.&n; */
macro_line|#ifndef __IXDP2X01_H__
DECL|macro|__IXDP2X01_H__
mdefine_line|#define __IXDP2X01_H__
DECL|macro|IXDP2X01_PHYS_CPLD_BASE
mdefine_line|#define&t;IXDP2X01_PHYS_CPLD_BASE&t;&t;0xc6024000
DECL|macro|IXDP2X01_VIRT_CPLD_BASE
mdefine_line|#define&t;IXDP2X01_VIRT_CPLD_BASE&t;&t;0xfefdd000
DECL|macro|IXDP2X01_CPLD_REGION_SIZE
mdefine_line|#define&t;IXDP2X01_CPLD_REGION_SIZE&t;0x1000
DECL|macro|IXDP2X01_CPLD_VIRT_REG
mdefine_line|#define IXDP2X01_CPLD_VIRT_REG(reg) (volatile unsigned long*)(IXDP2X01_VIRT_CPLD_BASE | reg)
DECL|macro|IXDP2X01_CPLD_PHYS_REG
mdefine_line|#define IXDP2X01_CPLD_PHYS_REG(reg) (volatile u32*)(IXDP2X01_PHYS_CPLD_BASE | reg)
DECL|macro|IXDP2X01_UART1_VIRT_BASE
mdefine_line|#define IXDP2X01_UART1_VIRT_BASE&t;IXDP2X01_CPLD_VIRT_REG(0x40)
DECL|macro|IXDP2X01_UART1_PHYS_BASE
mdefine_line|#define IXDP2X01_UART1_PHYS_BASE&t;IXDP2X01_CPLD_PHYS_REG(0x40)
DECL|macro|IXDP2X01_UART2_VIRT_BASE
mdefine_line|#define IXDP2X01_UART2_VIRT_BASE&t;IXDP2X01_CPLD_VIRT_REG(0x60)
DECL|macro|IXDP2X01_UART2_PHYS_BASE
mdefine_line|#define IXDP2X01_UART2_PHYS_BASE&t;IXDP2X01_CPLD_PHYS_REG(0x60)
DECL|macro|IXDP2X01_CS8900_VIRT_BASE
mdefine_line|#define IXDP2X01_CS8900_VIRT_BASE&t;IXDP2X01_CPLD_VIRT_REG(0x80)
DECL|macro|IXDP2X01_CS8900_VIRT_END
mdefine_line|#define IXDP2X01_CS8900_VIRT_END&t;(IXDP2X01_CS8900_VIRT_BASE + 16)
DECL|macro|IXDP2X01_CPLD_RESET_REG
mdefine_line|#define IXDP2X01_CPLD_RESET_REG         IXDP2X01_CPLD_VIRT_REG(0x00)
DECL|macro|IXDP2X01_INT_MASK_SET_REG
mdefine_line|#define IXDP2X01_INT_MASK_SET_REG&t;IXDP2X01_CPLD_VIRT_REG(0x08)
DECL|macro|IXDP2X01_INT_STAT_REG
mdefine_line|#define IXDP2X01_INT_STAT_REG&t;&t;IXDP2X01_CPLD_VIRT_REG(0x0C)
DECL|macro|IXDP2X01_INT_RAW_REG
mdefine_line|#define IXDP2X01_INT_RAW_REG&t;&t;IXDP2X01_CPLD_VIRT_REG(0x10) 
DECL|macro|IXDP2X01_INT_MASK_CLR_REG
mdefine_line|#define IXDP2X01_INT_MASK_CLR_REG&t;IXDP2X01_INT_RAW_REG
DECL|macro|IXDP2X01_INT_SIM_REG
mdefine_line|#define IXDP2X01_INT_SIM_REG&t;&t;IXDP2X01_CPLD_VIRT_REG(0x14)
DECL|macro|IXDP2X01_CPLD_FLASH_REG
mdefine_line|#define IXDP2X01_CPLD_FLASH_REG&t;&t;IXDP2X01_CPLD_VIRT_REG(0x20)
DECL|macro|IXDP2X01_CPLD_FLASH_INTERN
mdefine_line|#define IXDP2X01_CPLD_FLASH_INTERN &t;0x8000
DECL|macro|IXDP2X01_CPLD_FLASH_BANK_MASK
mdefine_line|#define IXDP2X01_CPLD_FLASH_BANK_MASK &t;0xF
DECL|macro|IXDP2X01_FLASH_WINDOW_BITS
mdefine_line|#define IXDP2X01_FLASH_WINDOW_BITS &t;25
DECL|macro|IXDP2X01_FLASH_WINDOW_SIZE
mdefine_line|#define IXDP2X01_FLASH_WINDOW_SIZE &t;(1 &lt;&lt; IXDP2X01_FLASH_WINDOW_BITS)
DECL|macro|IXDP2X01_FLASH_WINDOW_MASK
mdefine_line|#define IXDP2X01_FLASH_WINDOW_MASK &t;(IXDP2X01_FLASH_WINDOW_SIZE - 1)
DECL|macro|IXDP2X01_UART_CLK
mdefine_line|#define&t;IXDP2X01_UART_CLK&t;&t;1843200
DECL|macro|IXDP2X01_GPIO_I2C_ENABLE
mdefine_line|#define&t;IXDP2X01_GPIO_I2C_ENABLE&t;0x02
DECL|macro|IXDP2X01_GPIO_SCL
mdefine_line|#define&t;IXDP2X01_GPIO_SCL&t;&t;0x07
DECL|macro|IXDP2X01_GPIO_SDA
mdefine_line|#define&t;IXDP2X01_GPIO_SDA&t;&t;0x06
macro_line|#endif /* __IXDP2x01_H__ */
eof
