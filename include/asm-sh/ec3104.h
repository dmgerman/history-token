macro_line|#ifndef __ASM_EC3104_H
DECL|macro|__ASM_EC3104_H
mdefine_line|#define __ASM_EC3104_H
multiline_comment|/*&n; * Most of the register set is at 0xb0ec0000 - 0xb0ecffff.&n; *&n; * as far as I&squot;ve figured it out the register map is:&n; * 0xb0ec0000 - id string&n; * 0xb0ec0XXX - power management&n; * 0xb0ec1XXX - interrupt control&n; * 0xb0ec3XXX - ps2 port (touch pad on aero 8000)&n; * 0xb0ec6XXX - i2c&n; * 0xb0ec7000 - first serial port (proprietary connector on aero 8000)&n; * 0xb0ec8000 - second serial port&n; * 0xb0ec9000 - third serial port&n; * 0xb0eca000 - fourth serial port (keyboard controller on aero 8000)&n; * 0xb0eccXXX - GPIO&n; * 0xb0ecdXXX - GPIO&n; */
DECL|macro|EC3104_BASE
mdefine_line|#define EC3104_BASE&t;0xb0ec0000
DECL|macro|EC3104_SER4_DATA
mdefine_line|#define EC3104_SER4_DATA&t;(EC3104_BASE+0xa000)
DECL|macro|EC3104_SER4_IIR
mdefine_line|#define EC3104_SER4_IIR&t;&t;(EC3104_BASE+0xa008)
DECL|macro|EC3104_SER4_MCR
mdefine_line|#define EC3104_SER4_MCR&t;&t;(EC3104_BASE+0xa010)
DECL|macro|EC3104_SER4_LSR
mdefine_line|#define EC3104_SER4_LSR&t;&t;(EC3104_BASE+0xa014)
DECL|macro|EC3104_SER4_MSR
mdefine_line|#define EC3104_SER4_MSR&t;&t;(EC3104_BASE+0xa018)
multiline_comment|/*&n; * our ISA bus.  this seems to be real ISA.&n; */
DECL|macro|EC3104_ISA_BASE
mdefine_line|#define EC3104_ISA_BASE&t;0xa5000000
DECL|macro|EC3104_IRQ
mdefine_line|#define EC3104_IRQ&t;11
DECL|macro|EC3104_IRQBASE
mdefine_line|#define EC3104_IRQBASE&t;64
DECL|macro|EC3104_IRQ_SER1
mdefine_line|#define EC3104_IRQ_SER1&t;EC3104_IRQBASE + 7
DECL|macro|EC3104_IRQ_SER2
mdefine_line|#define EC3104_IRQ_SER2&t;EC3104_IRQBASE + 8
DECL|macro|EC3104_IRQ_SER3
mdefine_line|#define EC3104_IRQ_SER3&t;EC3104_IRQBASE + 9
DECL|macro|EC3104_IRQ_SER4
mdefine_line|#define EC3104_IRQ_SER4&t;EC3104_IRQBASE + 10
macro_line|#endif /* __ASM_EC3104_H */
eof
