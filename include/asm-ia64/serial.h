multiline_comment|/*&n; * include/asm-ia64/serial.h&n; *&n; * Derived from the i386 version.&n; */
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( 1843200 / 16 )
multiline_comment|/*&n; * All legacy serial ports should be enumerated via ACPI namespace, so&n; * we need not list them here.&n; */
eof
