multiline_comment|/*&n; *  linux/arch/arm/mach-ebsa110/hardware.h&n; *&n; *  Copyright (C) 2001 Russell King&n; *&n; *  Local hardware definitions.&n; */
macro_line|#ifndef HARDWARE_H
DECL|macro|HARDWARE_H
mdefine_line|#define HARDWARE_H
DECL|macro|IRQ_MASK
mdefine_line|#define IRQ_MASK&t;&t;0xfe000000&t;/* read */
DECL|macro|IRQ_MSET
mdefine_line|#define IRQ_MSET&t;&t;0xfe000000&t;/* write */
DECL|macro|IRQ_STAT
mdefine_line|#define IRQ_STAT&t;&t;0xff000000&t;/* read */
DECL|macro|IRQ_MCLR
mdefine_line|#define IRQ_MCLR&t;&t;0xff000000&t;/* write */
macro_line|#endif
eof
