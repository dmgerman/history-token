multiline_comment|/*&n; * include/asm-arm/arch-ixp2000/serial.h&n; *&n; * Serial port defn for ixp2000 based systems.&n; *&n; * Author: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * Copyright (c) 2002-2004 MontaVista Software, Inc.&n; *&n; * We do not register serial ports staticly b/c there is no easy way&n; * to autodetect an XScale port. Instead we register them at runtime&n; * via early_serial_init().&n; */
macro_line|#ifndef _ARCH_SERIAL_H_
DECL|macro|_ARCH_SERIAL_H_
mdefine_line|#define _ARCH_SERIAL_H_
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD (50000000/ 16)
multiline_comment|/*&n; * Currently no IXP2000 systems with &gt; 3 serial ports.&n; * If you add a system that does, just up this.&n; */
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define&t;STD_SERIAL_PORT_DEFNS
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define&t;EXTRA_SERIAL_PORT_DEFNS
macro_line|#endif  
singleline_comment|// __ARCH_SERIAL_H_
eof
