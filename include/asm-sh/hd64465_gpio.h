macro_line|#ifndef _ASM_SH_HD64465_GPIO_
DECL|macro|_ASM_SH_HD64465_GPIO_
mdefine_line|#define _ASM_SH_HD64465_GPIO_ 1
multiline_comment|/*&n; * $Id: hd64465_gpio.h,v 1.1 2001/01/02 15:35:22 mjd Exp $&n; *&n; * Hitachi HD64465 companion chip: General Purpose IO pins support.&n; * This layer enables other device drivers to configure GPIO&n; * pins, get and set their values, and register an interrupt&n; * routine for when input pins change in hardware.&n; *&n; * by Greg Banks &lt;gbanks@pocketpenguins.com&gt;&n; * (c) 2000 PocketPenguins Inc.&n; */
macro_line|#include &lt;asm/hd64465.h&gt;
multiline_comment|/* Macro to construct a portpin number (used in all&n; * subsequent functions) from a port letter and a pin&n; * number, e.g. HD64465_GPIO_PORTPIN(&squot;A&squot;, 5).&n; */
DECL|macro|HD64465_GPIO_PORTPIN
mdefine_line|#define HD64465_GPIO_PORTPIN(port,pin)&t;(((port)-&squot;A&squot;)&lt;&lt;3|(pin))
multiline_comment|/* Pin configuration constants for _configure() */
DECL|macro|HD64465_GPIO_FUNCTION2
mdefine_line|#define HD64465_GPIO_FUNCTION2&t;0&t;/* use the pin&squot;s *other* function */
DECL|macro|HD64465_GPIO_OUT
mdefine_line|#define HD64465_GPIO_OUT&t;1&t;/* output */
DECL|macro|HD64465_GPIO_IN_PULLUP
mdefine_line|#define HD64465_GPIO_IN_PULLUP&t;2&t;/* input, pull-up MOS on */
DECL|macro|HD64465_GPIO_IN
mdefine_line|#define HD64465_GPIO_IN&t;&t;3&t;/* input */
multiline_comment|/* Configure a pin&squot;s direction */
r_extern
r_void
id|hd64465_gpio_configure
c_func
(paren
r_int
id|portpin
comma
r_int
id|direction
)paren
suffix:semicolon
multiline_comment|/* Get, set value */
r_extern
r_void
id|hd64465_gpio_set_pin
c_func
(paren
r_int
id|portpin
comma
r_int
r_int
id|value
)paren
suffix:semicolon
r_extern
r_int
r_int
id|hd64465_gpio_get_pin
c_func
(paren
r_int
id|portpin
)paren
suffix:semicolon
r_extern
r_void
id|hd64465_gpio_set_port
c_func
(paren
r_int
id|port
comma
r_int
r_int
id|value
)paren
suffix:semicolon
r_extern
r_int
r_int
id|hd64465_gpio_get_port
c_func
(paren
r_int
id|port
)paren
suffix:semicolon
multiline_comment|/* mode constants for _register_irq() */
DECL|macro|HD64465_GPIO_FALLING
mdefine_line|#define HD64465_GPIO_FALLING&t;0
DECL|macro|HD64465_GPIO_RISING
mdefine_line|#define HD64465_GPIO_RISING&t;1
multiline_comment|/* Interrupt on external value change */
r_extern
r_void
id|hd64465_gpio_register_irq
c_func
(paren
r_int
id|portpin
comma
r_int
id|mode
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
id|portpin
comma
r_void
op_star
id|dev
)paren
comma
r_void
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|hd64465_gpio_unregister_irq
c_func
(paren
r_int
id|portpin
)paren
suffix:semicolon
macro_line|#endif /* _ASM_SH_HD64465_GPIO_  */
eof
