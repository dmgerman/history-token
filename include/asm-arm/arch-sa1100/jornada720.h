multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/jornada720.h&n; *&n; * Created 2000/11/29 by John Ankcorn &lt;jca@lcs.mit.edu&gt;&n; *&n; * This file contains the hardware specific definitions for HP Jornada 720&n; *&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
macro_line|#error &quot;include &lt;asm/hardware.h&gt; instead&quot;
macro_line|#endif
DECL|macro|SA1111_BASE
mdefine_line|#define SA1111_BASE             (0x40000000)
DECL|macro|GPIO_JORNADA720_KEYBOARD
mdefine_line|#define GPIO_JORNADA720_KEYBOARD&t;GPIO_GPIO(0)
DECL|macro|GPIO_JORNADA720_MOUSE
mdefine_line|#define GPIO_JORNADA720_MOUSE&t;&t;GPIO_GPIO(9)
DECL|macro|GPIO_JORNADA720_KEYBOARD_IRQ
mdefine_line|#define GPIO_JORNADA720_KEYBOARD_IRQ&t;IRQ_GPIO0
DECL|macro|GPIO_JORNADA720_MOUSE_IRQ
mdefine_line|#define GPIO_JORNADA720_MOUSE_IRQ&t;&t;IRQ_GPIO9
macro_line|#ifndef __ASSEMBLY__
r_void
id|jornada720_mcu_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|jornada_contrast
c_func
(paren
r_int
id|arg_contrast
)paren
suffix:semicolon
r_void
id|jornada720_battery
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|jornada720_getkey
c_func
(paren
r_int
r_char
op_star
id|data
comma
r_int
id|size
)paren
suffix:semicolon
macro_line|#endif
eof
