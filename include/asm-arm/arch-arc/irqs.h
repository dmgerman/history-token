multiline_comment|/*&n; *  linux/include/asm-arm/arch-arc/irqs.h&n; *&n; *  Copyright (C) 1996 Russell King, Dave Gilbert&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Modifications:&n; *   04-04-1998&t;PJB&t;Merged arc and a5k versions&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_ARCH_A5K)
DECL|macro|IRQ_PRINTER
mdefine_line|#define IRQ_PRINTER&t;&t;0
DECL|macro|IRQ_BATLOW
mdefine_line|#define IRQ_BATLOW&t;&t;1
DECL|macro|IRQ_FLOPPYINDEX
mdefine_line|#define IRQ_FLOPPYINDEX&t;&t;2
DECL|macro|IRQ_FLOPPYDISK
mdefine_line|#define IRQ_FLOPPYDISK&t;&t;12
macro_line|#elif defined(CONFIG_ARCH_ARC)
DECL|macro|IRQ_PRINTERBUSY
mdefine_line|#define IRQ_PRINTERBUSY&t;&t;0
DECL|macro|IRQ_SERIALRING
mdefine_line|#define&t;IRQ_SERIALRING&t;&t;1
DECL|macro|IRQ_PRINTERACK
mdefine_line|#define IRQ_PRINTERACK&t;&t;2
DECL|macro|IRQ_FLOPPYCHANGED
mdefine_line|#define IRQ_FLOPPYCHANGED&t;12
macro_line|#endif
DECL|macro|IRQ_VSYNCPULSE
mdefine_line|#define IRQ_VSYNCPULSE&t;&t;3
DECL|macro|IRQ_POWERON
mdefine_line|#define IRQ_POWERON&t;&t;4
DECL|macro|IRQ_TIMER0
mdefine_line|#define IRQ_TIMER0&t;&t;5
DECL|macro|IRQ_TIMER1
mdefine_line|#define IRQ_TIMER1&t;&t;6
DECL|macro|IRQ_IMMEDIATE
mdefine_line|#define IRQ_IMMEDIATE&t;&t;7
DECL|macro|IRQ_EXPCARDFIQ
mdefine_line|#define IRQ_EXPCARDFIQ&t;&t;8
DECL|macro|IRQ_SOUNDCHANGE
mdefine_line|#define IRQ_SOUNDCHANGE&t;&t;9
DECL|macro|IRQ_SERIALPORT
mdefine_line|#define IRQ_SERIALPORT&t;&t;10
DECL|macro|IRQ_HARDDISK
mdefine_line|#define IRQ_HARDDISK&t;&t;11
DECL|macro|IRQ_EXPANSIONCARD
mdefine_line|#define IRQ_EXPANSIONCARD&t;13
DECL|macro|IRQ_KEYBOARDTX
mdefine_line|#define IRQ_KEYBOARDTX&t;&t;14
DECL|macro|IRQ_KEYBOARDRX
mdefine_line|#define IRQ_KEYBOARDRX&t;&t;15
macro_line|#if defined(CONFIG_ARCH_A5K)
DECL|macro|FIQ_SERIALPORT
mdefine_line|#define FIQ_SERIALPORT&t;&t;4
macro_line|#elif defined(CONFIG_ARCH_ARC)
DECL|macro|FIQ_FLOPPYIRQ
mdefine_line|#define FIQ_FLOPPYIRQ&t;&t;1
DECL|macro|FIQ_FD1772
mdefine_line|#define FIQ_FD1772&t;&t;FIQ_FLOPPYIRQ
macro_line|#endif
DECL|macro|FIQ_FLOPPYDATA
mdefine_line|#define FIQ_FLOPPYDATA&t;&t;0
DECL|macro|FIQ_ECONET
mdefine_line|#define FIQ_ECONET&t;&t;2
DECL|macro|FIQ_EXPANSIONCARD
mdefine_line|#define FIQ_EXPANSIONCARD&t;6
DECL|macro|FIQ_FORCE
mdefine_line|#define FIQ_FORCE&t;&t;7
DECL|macro|IRQ_TIMER
mdefine_line|#define IRQ_TIMER&t;&t;IRQ_TIMER0
multiline_comment|/*&n; * This is the offset of the FIQ &quot;IRQ&quot; numbers&n; */
DECL|macro|FIQ_START
mdefine_line|#define FIQ_START&t;&t;64
DECL|macro|irq_cannonicalize
mdefine_line|#define irq_cannonicalize(i)&t;(i)
eof
