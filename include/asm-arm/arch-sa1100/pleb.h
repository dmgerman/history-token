multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/pleb.h&n; *&n; * Created 2000/12/08 by Daniel Potts &lt;danielp@cse.unsw.edu.au&gt;&n; *&n; * This file contains the hardware specific definitions for the&n; * PLEB board. http://www.cse.unsw.edu.au/~pleb&n; */
macro_line|#ifndef _INCLUDE_PLEB_H_
DECL|macro|_INCLUDE_PLEB_H_
mdefine_line|#define _INCLUDE_PLEB_H_
DECL|macro|PLEB_ETH0_P
mdefine_line|#define PLEB_ETH0_P&t;&t;(0x20000300)&t;/* Ethernet 0 in PCMCIA0 IO */
DECL|macro|PLEB_ETH0_V
mdefine_line|#define PLEB_ETH0_V&t;&t;(0xf6000300)
DECL|macro|GPIO_ETH0_IRQ
mdefine_line|#define GPIO_ETH0_IRQ&t;&t;GPIO_GPIO (21)
DECL|macro|GPIO_ETH0_EN
mdefine_line|#define GPIO_ETH0_EN&t;&t;GPIO_GPIO (26)
DECL|macro|IRQ_GPIO_ETH0_IRQ
mdefine_line|#define IRQ_GPIO_ETH0_IRQ&t;IRQ_GPIO21
macro_line|#endif
eof
