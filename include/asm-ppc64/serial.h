multiline_comment|/*&n; * include/asm-ppc64/serial.h&n; */
macro_line|#ifndef _PPC64_SERIAL_H
DECL|macro|_PPC64_SERIAL_H
mdefine_line|#define _PPC64_SERIAL_H
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
multiline_comment|/* Default baud base if not found in device-tree */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( 1843200 / 16 )
macro_line|#endif /* _PPC64_SERIAL_H */
eof
