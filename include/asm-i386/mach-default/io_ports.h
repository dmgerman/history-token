multiline_comment|/*&n; *  arch/i386/mach-generic/io_ports.h&n; *&n; *  Machine specific IO port address definition for generic.&n; *  Written by Osamu Tomita &lt;tomita@cinet.co.jp&gt;&n; */
macro_line|#ifndef _MACH_IO_PORTS_H
DECL|macro|_MACH_IO_PORTS_H
mdefine_line|#define _MACH_IO_PORTS_H
multiline_comment|/* i8253A PIT registers */
DECL|macro|PIT_MODE
mdefine_line|#define PIT_MODE&t;&t;0x43
DECL|macro|PIT_CH0
mdefine_line|#define PIT_CH0&t;&t;&t;0x40
DECL|macro|PIT_CH2
mdefine_line|#define PIT_CH2&t;&t;&t;0x42
multiline_comment|/* i8259A PIC registers */
DECL|macro|PIC_MASTER_CMD
mdefine_line|#define PIC_MASTER_CMD&t;&t;0x20
DECL|macro|PIC_MASTER_IMR
mdefine_line|#define PIC_MASTER_IMR&t;&t;0x21
DECL|macro|PIC_MASTER_ISR
mdefine_line|#define PIC_MASTER_ISR&t;&t;PIC_MASTER_CMD
DECL|macro|PIC_MASTER_POLL
mdefine_line|#define PIC_MASTER_POLL&t;&t;PIC_MASTER_ISR
DECL|macro|PIC_MASTER_OCW3
mdefine_line|#define PIC_MASTER_OCW3&t;&t;PIC_MASTER_ISR
DECL|macro|PIC_SLAVE_CMD
mdefine_line|#define PIC_SLAVE_CMD&t;&t;0xa0
DECL|macro|PIC_SLAVE_IMR
mdefine_line|#define PIC_SLAVE_IMR&t;&t;0xa1
multiline_comment|/* i8259A PIC related value */
DECL|macro|PIC_CASCADE_IR
mdefine_line|#define PIC_CASCADE_IR&t;&t;2
DECL|macro|MASTER_ICW4_DEFAULT
mdefine_line|#define MASTER_ICW4_DEFAULT&t;0x01
DECL|macro|SLAVE_ICW4_DEFAULT
mdefine_line|#define SLAVE_ICW4_DEFAULT&t;0x01
DECL|macro|PIC_ICW4_AEOI
mdefine_line|#define PIC_ICW4_AEOI&t;&t;2
macro_line|#endif /* !_MACH_IO_PORTS_H */
eof
