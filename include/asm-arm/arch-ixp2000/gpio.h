multiline_comment|/*&n; * include/asm-arm/arch-ixp2000/ixp2000-gpio.h&n; *&n; * Copyright (C) 2002 Intel Corporation.&n; *&n; * This program is free software, you can redistribute it and/or modify &n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
multiline_comment|/*&n; * IXP2000 GPIO in/out, edge/level detection for IRQs:&n; * IRQs are generated on Falling-edge, Rising-Edge, Level-low, Level-High&n; * or both Falling-edge and Rising-edge.  &n; * This must be called *before* the corresponding IRQ is registerd.&n; * Use this instead of directly setting the GPIO registers.&n; * GPIOs may also be used as GPIOs (e.g. for emulating i2c/smb)&n; */
macro_line|#ifndef _ASM_ARCH_IXP2000_GPIO_H_
DECL|macro|_ASM_ARCH_IXP2000_GPIO_H_
mdefine_line|#define _ASM_ARCH_IXP2000_GPIO_H_
macro_line|#ifndef __ASSEMBLY__
DECL|macro|GPIO_OUT
mdefine_line|#define GPIO_OUT&t;&t;&t;0x0
DECL|macro|GPIO_IN
mdefine_line|#define GPIO_IN&t;&t;&t;&t;0x80
DECL|macro|IXP2000_GPIO_LOW
mdefine_line|#define IXP2000_GPIO_LOW&t;&t;0
DECL|macro|IXP2000_GPIO_HIGH
mdefine_line|#define IXP2000_GPIO_HIGH&t;&t;1
DECL|macro|GPIO_NO_EDGES
mdefine_line|#define GPIO_NO_EDGES           &t;0
DECL|macro|GPIO_FALLING_EDGE
mdefine_line|#define GPIO_FALLING_EDGE       &t;1
DECL|macro|GPIO_RISING_EDGE
mdefine_line|#define GPIO_RISING_EDGE        &t;2
DECL|macro|GPIO_BOTH_EDGES
mdefine_line|#define GPIO_BOTH_EDGES         &t;3
DECL|macro|GPIO_LEVEL_LOW
mdefine_line|#define GPIO_LEVEL_LOW          &t;4
DECL|macro|GPIO_LEVEL_HIGH
mdefine_line|#define GPIO_LEVEL_HIGH         &t;8
r_extern
r_void
id|set_GPIO_IRQ_edge
c_func
(paren
r_int
id|gpio_nr
comma
r_int
id|edge
)paren
suffix:semicolon
r_extern
r_void
id|set_GPIO_IRQ_level
c_func
(paren
r_int
id|gpio_nr
comma
r_int
id|level
)paren
suffix:semicolon
r_extern
r_void
id|gpio_line_config
c_func
(paren
r_int
id|line
comma
r_int
id|style
)paren
suffix:semicolon
DECL|function|gpio_line_get
r_static
r_inline
r_int
id|gpio_line_get
c_func
(paren
r_int
id|line
)paren
(brace
r_return
(paren
(paren
(paren
op_star
id|IXP2000_GPIO_PLR
)paren
op_rshift
id|line
)paren
op_amp
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|gpio_line_set
r_static
r_inline
r_void
id|gpio_line_set
c_func
(paren
r_int
id|line
comma
r_int
id|value
)paren
(brace
r_if
c_cond
(paren
id|value
op_eq
id|IXP2000_GPIO_HIGH
)paren
(brace
id|ixp_reg_write
c_func
(paren
id|IXP2000_GPIO_POSR
comma
id|BIT
c_func
(paren
id|line
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|value
op_eq
id|IXP2000_GPIO_LOW
)paren
id|ixp_reg_write
c_func
(paren
id|IXP2000_GPIO_POCR
comma
id|BIT
c_func
(paren
id|line
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* ASM_ARCH_IXP2000_GPIO_H_ */
eof
