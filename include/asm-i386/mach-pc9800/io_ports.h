multiline_comment|/*&n; *  arch/i386/mach-pc9800/io_ports.h&n; *&n; *  Machine specific IO port address definition for PC-9800.&n; *  Written by Osamu Tomita &lt;tomita@cinet.co.jp&gt;&n; */
macro_line|#ifndef _MACH_IO_PORTS_H
DECL|macro|_MACH_IO_PORTS_H
mdefine_line|#define _MACH_IO_PORTS_H
multiline_comment|/* i8253A PIT registers */
DECL|macro|PIT_MODE
mdefine_line|#define PIT_MODE&t;&t;0x77
DECL|macro|PIT_CH0
mdefine_line|#define PIT_CH0&t;&t;&t;0x71
DECL|macro|PIT_CH2
mdefine_line|#define PIT_CH2&t;&t;&t;0x75
multiline_comment|/* i8259A PIC registers */
DECL|macro|PIC_MASTER_CMD
mdefine_line|#define PIC_MASTER_CMD&t;&t;0x00
DECL|macro|PIC_MASTER_IMR
mdefine_line|#define PIC_MASTER_IMR&t;&t;0x02
DECL|macro|PIC_MASTER_ISR
mdefine_line|#define PIC_MASTER_ISR&t;&t;PIC_MASTER_CMD
DECL|macro|PIC_MASTER_POLL
mdefine_line|#define PIC_MASTER_POLL&t;&t;PIC_MASTER_ISR
DECL|macro|PIC_MASTER_OCW3
mdefine_line|#define PIC_MASTER_OCW3&t;&t;PIC_MASTER_ISR
DECL|macro|PIC_SLAVE_CMD
mdefine_line|#define PIC_SLAVE_CMD&t;&t;0x08
DECL|macro|PIC_SLAVE_IMR
mdefine_line|#define PIC_SLAVE_IMR&t;&t;0x0a
multiline_comment|/* i8259A PIC related values */
DECL|macro|PIC_CASCADE_IR
mdefine_line|#define PIC_CASCADE_IR&t;&t;7
DECL|macro|MASTER_ICW4_DEFAULT
mdefine_line|#define MASTER_ICW4_DEFAULT&t;0x1d
DECL|macro|SLAVE_ICW4_DEFAULT
mdefine_line|#define SLAVE_ICW4_DEFAULT&t;0x09
DECL|macro|PIC_ICW4_AEOI
mdefine_line|#define PIC_ICW4_AEOI&t;&t;0x02
macro_line|#endif /* !_MACH_IO_PORTS_H */
eof
