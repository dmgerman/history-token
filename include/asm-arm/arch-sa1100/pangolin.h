multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/pangolin.h&n; *&n; * Created 2000/08/25 by Murphy Chen &lt;murphy@mail.dialogue.com.tw&gt;&n; *&n; * This file contains the hardware specific definitions for Pangolin&n; *&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
macro_line|#error &quot;include &lt;asm/hardware.h&gt; instead&quot;
macro_line|#endif
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef CONFIG_SA1100_PANGOLIN_PCMCIA_IDE
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
macro_line|#else
multiline_comment|/*&n; *  These definitions are for PCMCIA/IDE card&n; *&n; *  PSKTSEL = 0 ---&gt; PCMCIA&n; *  PCMCIA_RESET = GPIO_7        ( output )( 0: normal   1: reset )&n; *  PCMCIA_IRQ = GPIO_24         ( input )&n; *  PCMCIA_CD = GPIO_25          ( input )&n; *&n; *  PSKTSEL = 1 ---&gt; IDE port&n; *  IDE_IRQ = GPIO_23            ( input )&n; *&n; *  !!WARNING!!&n; *  When the PCMCIA/IDE card is inserted, the CF slot&n; *  should not have any card inserted!!&n; *&n; */
DECL|macro|GPIO_PCMCIA_RESET
mdefine_line|#define GPIO_PCMCIA_RESET       GPIO_GPIO (7)
DECL|macro|GPIO_PCMCIA_IRQ
mdefine_line|#define GPIO_PCMCIA_IRQ         GPIO_GPIO (24)
DECL|macro|GPIO_PCMCIA_CD
mdefine_line|#define GPIO_PCMCIA_CD          GPIO_GPIO (25)
DECL|macro|GPIO_IDE_IRQ
mdefine_line|#define GPIO_IDE_IRQ            GPIO_GPIO (8)
DECL|macro|IRQ_PCMCIA_IRQ
mdefine_line|#define IRQ_PCMCIA_IRQ          IRQ_GPIO24
DECL|macro|IRQ_PCMCIA_CD
mdefine_line|#define IRQ_PCMCIA_CD           IRQ_GPIO25
DECL|macro|IRQ_IDE_IRQ
mdefine_line|#define IRQ_IDE_IRQ             IRQ_GPIO8
macro_line|#endif
multiline_comment|/*&n; * On board LAN chip&n; */
DECL|macro|PANGOLIN_LAN_ADDR
mdefine_line|#define PANGOLIN_LAN_ADDR      0x32000000
DECL|macro|PANGOLIN_LAN_RESET
mdefine_line|#define PANGOLIN_LAN_RESET     GPIO_GPIO (8)
DECL|macro|PANGOLIN_LAN_IRQ
mdefine_line|#define PANGOLIN_LAN_IRQ       GPIO_GPIO (26)
DECL|macro|PANGOLIN_IRQ_LAN_IRQ
mdefine_line|#define PANGOLIN_IRQ_LAN_IRQ   IRQ_GPIO26
eof
