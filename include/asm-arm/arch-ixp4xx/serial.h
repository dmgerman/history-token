multiline_comment|/*&n; * include/asm-arm/arch-ixp4xx/serial.h&n; *&n; * Author: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * Copyright (C) 2002-2004 MontaVista Software, Inc.&n; * &n; */
macro_line|#ifndef _ARCH_SERIAL_H_
DECL|macro|_ARCH_SERIAL_H_
mdefine_line|#define _ARCH_SERIAL_H_
multiline_comment|/*&n; * We don&squot;t hardcode our serial port information but instead&n; * fill it in dynamically based on our platform in arch-&gt;map_io.&n; * This allows for per-board serial ports w/o a bunch of&n; * #ifdefs in this file.&n; */
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define&t;STD_SERIAL_PORT_DEFNS
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define&t;EXTRA_SERIAL_PORT_DEFNS
multiline_comment|/*&n; * IXP4XX uses 15.6MHz clock for uart&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( IXP4XX_UART_XTAL / 16 )
macro_line|#endif 
singleline_comment|// _ARCH_SERIAL_H_
eof
