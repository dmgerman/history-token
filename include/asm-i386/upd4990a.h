multiline_comment|/*&n; *  Architecture dependent definitions&n; *  for NEC uPD4990A serial I/O real-time clock.&n; *&n; *  Copyright 2001  TAKAI Kousuke &lt;tak@kmc.kyoto-u.ac.jp&gt;&n; *&t;&t;    Kyoto University Microcomputer Club (KMC).&n; *&n; *  References:&n; *&t;uPD4990A serial I/O real-time clock users&squot; manual (Japanese)&n; *&t;No. S12828JJ4V0UM00 (4th revision), NEC Corporation, 1999.&n; */
macro_line|#ifndef _ASM_I386_uPD4990A_H
DECL|macro|_ASM_I386_uPD4990A_H
mdefine_line|#define _ASM_I386_uPD4990A_H
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|UPD4990A_IO
mdefine_line|#define UPD4990A_IO&t;&t;(0x0020)
DECL|macro|UPD4990A_IO_DATAOUT
mdefine_line|#define UPD4990A_IO_DATAOUT&t;(0x0033)
DECL|macro|UPD4990A_OUTPUT_DATA_CLK
mdefine_line|#define UPD4990A_OUTPUT_DATA_CLK(data, clk)&t;&t;&bslash;&n;&t;outb((((data) &amp; 1) &lt;&lt; 5) | (((clk) &amp; 1) &lt;&lt; 4)&t;&bslash;&n;&t;      | UPD4990A_PAR_SERIAL_MODE, UPD4990A_IO)
DECL|macro|UPD4990A_OUTPUT_CLK
mdefine_line|#define UPD4990A_OUTPUT_CLK(clk)&t;UPD4990A_OUTPUT_DATA_CLK(0, (clk))
DECL|macro|UPD4990A_OUTPUT_STROBE
mdefine_line|#define UPD4990A_OUTPUT_STROBE(stb) &bslash;&n;&t;outb(((stb) &lt;&lt; 3) | UPD4990A_PAR_SERIAL_MODE, UPD4990A_IO)
multiline_comment|/*&n; * Note: udelay() is *not* usable for UPD4990A_DELAY because&n; *&t; the Linux kernel reads uPD4990A to set up system clock&n; *&t; before calibrating delay...&n; */
DECL|macro|UPD4990A_DELAY
mdefine_line|#define UPD4990A_DELAY(usec)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (__builtin_constant_p((usec)) &amp;&amp; (usec) &lt; 5)&t;&bslash;&n;&t;&t;&t;__asm__ (&quot;.rept %c1&bslash;n&bslash;toutb %%al,%0&bslash;n&bslash;t.endr&quot;&t;&bslash;&n;&t;&t;&t;&t; : : &quot;N&quot; (0x5F),&t;&t;&t;&bslash;&n;&t;&t;&t;&t;     &quot;i&quot; (((usec) * 10 + 5) / 6));&t;&bslash;&n;&t;&t;else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;int _count = ((usec) * 10 + 5) / 6;&t;&t;&bslash;&n;&t;&t;&t;__asm__ volatile (&quot;1: outb %%al,%1&bslash;n&bslash;tloop 1b&quot;&t;&bslash;&n;&t;&t;&t;&t;&t;  : &quot;=c&quot; (_count)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;  : &quot;N&quot; (0x5F), &quot;0&quot; (_count));&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/* Caller should ignore all bits except bit0 */
DECL|macro|UPD4990A_READ_DATA
mdefine_line|#define UPD4990A_READ_DATA()&t;inb(UPD4990A_IO_DATAOUT)
macro_line|#endif
eof
