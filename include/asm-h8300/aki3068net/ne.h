multiline_comment|/* AE-3068 (aka. aki3068net) RTL8019AS Config */
macro_line|#ifndef __H8300_AKI3068NET_NE__
DECL|macro|__H8300_AKI3068NET_NE__
mdefine_line|#define __H8300_AKI3068NET_NE__
DECL|macro|NE2000_ADDR
mdefine_line|#define NE2000_ADDR&t;&t;0x200000
DECL|macro|NE2000_IRQ
mdefine_line|#define NE2000_IRQ              5
DECL|macro|NE2000_IRQ_VECTOR
mdefine_line|#define NE2000_IRQ_VECTOR&t;(12 + NE2000_IRQ)
DECL|macro|NE2000_BYTE
mdefine_line|#define&t;NE2000_BYTE&t;&t;volatile unsigned short
DECL|macro|IER
mdefine_line|#define IER                     0xfee015
DECL|macro|ISR
mdefine_line|#define ISR&t;&t;&t;0xfee016
DECL|macro|IRQ_MASK
mdefine_line|#define IRQ_MASK&t;&t;(1 &lt;&lt; NE2000_IRQ)
DECL|macro|WCRL
mdefine_line|#define WCRL                    0xfee023
DECL|macro|MAR0A
mdefine_line|#define MAR0A                   0xffff20
DECL|macro|ETCR0A
mdefine_line|#define ETCR0A                  0xffff24
DECL|macro|DTCR0A
mdefine_line|#define DTCR0A                  0xffff27
DECL|macro|MAR0B
mdefine_line|#define MAR0B                   0xffff28
DECL|macro|DTCR0B
mdefine_line|#define DTCR0B                  0xffff2f
DECL|macro|H8300_INIT_NE
mdefine_line|#define H8300_INIT_NE()                  &bslash;&n;do {                                     &bslash;&n;&t;wordlength = 1;                  &bslash;&n;        outb_p(0x48, ioaddr + EN0_DCFG); &bslash;&n;} while(0)
macro_line|#endif
eof
