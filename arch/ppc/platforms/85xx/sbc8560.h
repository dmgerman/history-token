multiline_comment|/*&n; * arch/ppc/platforms/85xx/sbc8560.h&n; *&n; * Wind River SBC8560 board definitions&n; *&n; * Copyright 2003 Motorola Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifndef __MACH_SBC8560_H__
DECL|macro|__MACH_SBC8560_H__
mdefine_line|#define __MACH_SBC8560_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;platforms/85xx/sbc85xx.h&gt;
DECL|macro|CPM_MAP_ADDR
mdefine_line|#define CPM_MAP_ADDR    (CCSRBAR + MPC85xx_CPM_OFFSET)
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  2
macro_line|#endif
multiline_comment|/* Rate for the 1.8432 Mhz clock for the onboard serial chip */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( 1843200 / 16 )
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_SKIP_TEST|ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_SKIP_TEST)
macro_line|#endif
DECL|macro|STD_SERIAL_PORT_DFNS
mdefine_line|#define STD_SERIAL_PORT_DFNS &bslash;&n;        { 0, BASE_BAUD, UARTA_ADDR, MPC85xx_IRQ_EXT9, STD_COM_FLAGS, /* ttyS0 */ &bslash;&n;                iomem_base: (u8 *)UARTA_ADDR,                       &bslash;&n;                io_type: SERIAL_IO_MEM },                                 &bslash;&n;        { 0, BASE_BAUD, UARTB_ADDR, MPC85xx_IRQ_EXT10, STD_COM_FLAGS, /* ttyS1 */ &bslash;&n;                iomem_base: (u8 *)UARTB_ADDR,                       &bslash;&n;                io_type: SERIAL_IO_MEM },
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;        STD_SERIAL_PORT_DFNS
macro_line|#endif /* __MACH_SBC8560_H__ */
eof
