multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/pangolin.h&n; *&n; * Created 2000/08/25 by Murphy Chen &lt;murphy@mail.dialogue.com.tw&gt;&n; *&n; * This file contains the hardware specific definitions for Pangolin&n; *&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
macro_line|#error &quot;include &lt;asm/hardware.h&gt; instead&quot;
macro_line|#endif
multiline_comment|/* GPIOs for which the generic definition doesn&squot;t say much */
DECL|macro|GPIO_CF_BUS_ON
mdefine_line|#define GPIO_CF_BUS_ON&t;&t;GPIO_GPIO (3)
DECL|macro|GPIO_CF_RESET
mdefine_line|#define GPIO_CF_RESET&t;&t;GPIO_GPIO (2)
DECL|macro|GPIO_CF_CD
mdefine_line|#define GPIO_CF_CD&t;&t;GPIO_GPIO (22)
DECL|macro|GPIO_CF_IRQ
mdefine_line|#define GPIO_CF_IRQ&t;&t;GPIO_GPIO (21)
DECL|macro|IRQ_GPIO_CF_IRQ
mdefine_line|#define IRQ_GPIO_CF_IRQ&t;&t;IRQ_GPIO21
DECL|macro|IRQ_GPIO_CF_CD
mdefine_line|#define IRQ_GPIO_CF_CD&t;&t;IRQ_GPIO22
eof
