multiline_comment|/*&n; * arch/ppc/platforms/85xx/sbc85xx.h&n; *&n; * WindRiver PowerQUICC III SBC85xx common board definitions&n; *&n; * Copyright 2003 Motorola Inc.&n; * Copyright 2004 Red Hat, Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifndef __PLATFORMS_85XX_SBC85XX_H__
DECL|macro|__PLATFORMS_85XX_SBC85XX_H__
mdefine_line|#define __PLATFORMS_85XX_SBC85XX_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
DECL|macro|BOARD_CCSRBAR
mdefine_line|#define BOARD_CCSRBAR&t;&t;((uint)0xff700000)
DECL|macro|CCSRBAR_SIZE
mdefine_line|#define CCSRBAR_SIZE&t;&t;((uint)1024*1024)
DECL|macro|BCSR_ADDR
mdefine_line|#define BCSR_ADDR&t;&t;((uint)0xfc000000)
DECL|macro|BCSR_SIZE
mdefine_line|#define BCSR_SIZE&t;&t;((uint)(16 * 1024 * 1024))
DECL|macro|UARTA_ADDR
mdefine_line|#define UARTA_ADDR&t;&t;(BCSR_ADDR + 0x00700000)
DECL|macro|UARTB_ADDR
mdefine_line|#define UARTB_ADDR&t;&t;(BCSR_ADDR + 0x00800000)
DECL|macro|RTC_DEVICE_ADDR
mdefine_line|#define RTC_DEVICE_ADDR&t;&t;(BCSR_ADDR + 0x00900000)
DECL|macro|EEPROM_ADDR
mdefine_line|#define EEPROM_ADDR&t;&t;(BCSR_ADDR + 0x00b00000)
r_extern
r_int
id|sbc8560_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
suffix:semicolon
r_extern
r_void
id|sbc8560_init_IRQ
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
multiline_comment|/* PCI interrupt controller */
DECL|macro|PIRQA
mdefine_line|#define PIRQA&t;&t;MPC85xx_IRQ_EXT1
DECL|macro|PIRQB
mdefine_line|#define PIRQB&t;&t;MPC85xx_IRQ_EXT2
DECL|macro|PIRQC
mdefine_line|#define PIRQC&t;&t;MPC85xx_IRQ_EXT3
DECL|macro|PIRQD
mdefine_line|#define PIRQD&t;&t;MPC85xx_IRQ_EXT4
DECL|macro|MPC85XX_PCI1_LOWER_IO
mdefine_line|#define MPC85XX_PCI1_LOWER_IO&t;0x00000000
DECL|macro|MPC85XX_PCI1_UPPER_IO
mdefine_line|#define MPC85XX_PCI1_UPPER_IO&t;0x00ffffff
DECL|macro|MPC85XX_PCI1_LOWER_MEM
mdefine_line|#define MPC85XX_PCI1_LOWER_MEM&t;0x80000000
DECL|macro|MPC85XX_PCI1_UPPER_MEM
mdefine_line|#define MPC85XX_PCI1_UPPER_MEM&t;0x9fffffff
DECL|macro|MPC85XX_PCI1_IO_BASE
mdefine_line|#define MPC85XX_PCI1_IO_BASE&t;0xe2000000
DECL|macro|MPC85XX_PCI1_MEM_OFFSET
mdefine_line|#define MPC85XX_PCI1_MEM_OFFSET&t;0x00000000
DECL|macro|MPC85XX_PCI1_IO_SIZE
mdefine_line|#define MPC85XX_PCI1_IO_SIZE&t;0x01000000
macro_line|#endif /* __PLATFORMS_85XX_SBC85XX_H__ */
eof
