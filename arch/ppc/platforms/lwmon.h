multiline_comment|/*&n; * Liebherr LWMON board specific definitions&n; * &n; * Copyright (c) 2001 Wolfgang Denk (wd@denx.de)&n; */
macro_line|#ifndef __MACH_LWMON_H
DECL|macro|__MACH_LWMON_H
mdefine_line|#define __MACH_LWMON_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
DECL|macro|IMAP_ADDR
mdefine_line|#define&t;IMAP_ADDR&t;0xFFF00000&t;/* physical base address of IMMR area&t;*/
DECL|macro|IMAP_SIZE
mdefine_line|#define IMAP_SIZE&t;(64 * 1024)&t;/* mapped size of IMMR area&t;&t;*/
multiline_comment|/*-----------------------------------------------------------------------&n; * PCMCIA stuff&n; *-----------------------------------------------------------------------&n; *&n; */
DECL|macro|PCMCIA_MEM_SIZE
mdefine_line|#define PCMCIA_MEM_SIZE&t;&t;( 64 &lt;&lt; 20 )
DECL|macro|MAX_HWIFS
mdefine_line|#define&t;MAX_HWIFS&t;1&t;/* overwrite default in include/asm-ppc/ide.h&t;*/
multiline_comment|/*&n; * Definitions for IDE0 Interface&n; */
DECL|macro|IDE0_BASE_OFFSET
mdefine_line|#define IDE0_BASE_OFFSET&t;&t;0
DECL|macro|IDE0_DATA_REG_OFFSET
mdefine_line|#define IDE0_DATA_REG_OFFSET&t;&t;(PCMCIA_MEM_SIZE + 0x320)
DECL|macro|IDE0_ERROR_REG_OFFSET
mdefine_line|#define IDE0_ERROR_REG_OFFSET&t;&t;(2 * PCMCIA_MEM_SIZE + 0x320 + 1)
DECL|macro|IDE0_NSECTOR_REG_OFFSET
mdefine_line|#define IDE0_NSECTOR_REG_OFFSET&t;&t;(2 * PCMCIA_MEM_SIZE + 0x320 + 2)
DECL|macro|IDE0_SECTOR_REG_OFFSET
mdefine_line|#define IDE0_SECTOR_REG_OFFSET&t;&t;(2 * PCMCIA_MEM_SIZE + 0x320 + 3)
DECL|macro|IDE0_LCYL_REG_OFFSET
mdefine_line|#define IDE0_LCYL_REG_OFFSET&t;&t;(2 * PCMCIA_MEM_SIZE + 0x320 + 4)
DECL|macro|IDE0_HCYL_REG_OFFSET
mdefine_line|#define IDE0_HCYL_REG_OFFSET&t;&t;(2 * PCMCIA_MEM_SIZE + 0x320 + 5)
DECL|macro|IDE0_SELECT_REG_OFFSET
mdefine_line|#define IDE0_SELECT_REG_OFFSET&t;&t;(2 * PCMCIA_MEM_SIZE + 0x320 + 6)
DECL|macro|IDE0_STATUS_REG_OFFSET
mdefine_line|#define IDE0_STATUS_REG_OFFSET&t;&t;(2 * PCMCIA_MEM_SIZE + 0x320 + 7)
DECL|macro|IDE0_CONTROL_REG_OFFSET
mdefine_line|#define IDE0_CONTROL_REG_OFFSET&t;&t;0x0106
DECL|macro|IDE0_IRQ_REG_OFFSET
mdefine_line|#define IDE0_IRQ_REG_OFFSET&t;&t;0x000A&t;/* not used&t;&t;&t;*/
DECL|macro|IDE0_INTERRUPT
mdefine_line|#define&t;IDE0_INTERRUPT&t;&t;&t;13
multiline_comment|/*&n; * Definitions for I2C devices&n; */
DECL|macro|I2C_ADDR_AUDIO
mdefine_line|#define I2C_ADDR_AUDIO&t;&t;0x28&t;/* Audio volume control&t;&t;&t;*/
DECL|macro|I2C_ADDR_SYSMON
mdefine_line|#define I2C_ADDR_SYSMON&t;&t;0x2E&t;/* LM87 System Monitor&t;&t;&t;*/
DECL|macro|I2C_ADDR_RTC
mdefine_line|#define I2C_ADDR_RTC&t;&t;0x51&t;/* PCF8563 RTC&t;&t;&t;&t;*/
DECL|macro|I2C_ADDR_POWER_A
mdefine_line|#define I2C_ADDR_POWER_A&t;0x52&t;/* PCMCIA/USB power switch, channel A&t;*/
DECL|macro|I2C_ADDR_POWER_B
mdefine_line|#define I2C_ADDR_POWER_B&t;0x53&t;/* PCMCIA/USB power switch, channel B&t;*/
DECL|macro|I2C_ADDR_KEYBD
mdefine_line|#define I2C_ADDR_KEYBD&t;&t;0x56&t;/* PIC LWE keyboard&t;&t;&t;*/
DECL|macro|I2C_ADDR_PICIO
mdefine_line|#define I2C_ADDR_PICIO&t;&t;0x57&t;/* PIC IO Expander&t;&t;&t;*/
DECL|macro|I2C_ADDR_EEPROM
mdefine_line|#define I2C_ADDR_EEPROM&t;&t;0x58&t;/* EEPROM AT24C164&t;&t;&t;*/
multiline_comment|/* We don&squot;t use the 8259.&n;*/
DECL|macro|NR_8259_INTS
mdefine_line|#define NR_8259_INTS&t;0
macro_line|#endif&t;/* __MACH_LWMON_H */
eof
