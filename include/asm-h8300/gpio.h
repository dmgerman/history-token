macro_line|#ifndef _H8300_GPIO_H
DECL|macro|_H8300_GPIO_H
mdefine_line|#define _H8300_GPIO_H
DECL|macro|H8300_GPIO_P1
mdefine_line|#define H8300_GPIO_P1 0
DECL|macro|H8300_GPIO_P2
mdefine_line|#define H8300_GPIO_P2 1
DECL|macro|H8300_GPIO_P3
mdefine_line|#define H8300_GPIO_P3 2
DECL|macro|H8300_GPIO_P4
mdefine_line|#define H8300_GPIO_P4 3
DECL|macro|H8300_GPIO_P5
mdefine_line|#define H8300_GPIO_P5 4
DECL|macro|H8300_GPIO_P6
mdefine_line|#define H8300_GPIO_P6 5
DECL|macro|H8300_GPIO_P7
mdefine_line|#define H8300_GPIO_P7 6
DECL|macro|H8300_GPIO_P8
mdefine_line|#define H8300_GPIO_P8 7
DECL|macro|H8300_GPIO_P9
mdefine_line|#define H8300_GPIO_P9 8
DECL|macro|H8300_GPIO_PA
mdefine_line|#define H8300_GPIO_PA 9
DECL|macro|H8300_GPIO_PB
mdefine_line|#define H8300_GPIO_PB 10
DECL|macro|H8300_GPIO_PC
mdefine_line|#define H8300_GPIO_PC 11
DECL|macro|H8300_GPIO_PD
mdefine_line|#define H8300_GPIO_PD 12
DECL|macro|H8300_GPIO_PE
mdefine_line|#define H8300_GPIO_PE 13
DECL|macro|H8300_GPIO_PF
mdefine_line|#define H8300_GPIO_PF 14
DECL|macro|H8300_GPIO_PG
mdefine_line|#define H8300_GPIO_PG 15
DECL|macro|H8300_GPIO_PH
mdefine_line|#define H8300_GPIO_PH 16
DECL|macro|H8300_GPIO_B7
mdefine_line|#define H8300_GPIO_B7 0x80
DECL|macro|H8300_GPIO_B6
mdefine_line|#define H8300_GPIO_B6 0x40
DECL|macro|H8300_GPIO_B5
mdefine_line|#define H8300_GPIO_B5 0x20
DECL|macro|H8300_GPIO_B4
mdefine_line|#define H8300_GPIO_B4 0x10
DECL|macro|H8300_GPIO_B3
mdefine_line|#define H8300_GPIO_B3 0x08
DECL|macro|H8300_GPIO_B2
mdefine_line|#define H8300_GPIO_B2 0x04
DECL|macro|H8300_GPIO_B1
mdefine_line|#define H8300_GPIO_B1 0x02
DECL|macro|H8300_GPIO_B0
mdefine_line|#define H8300_GPIO_B0 0x01
DECL|macro|H8300_GPIO_INPUT
mdefine_line|#define H8300_GPIO_INPUT 0
DECL|macro|H8300_GPIO_OUTPUT
mdefine_line|#define H8300_GPIO_OUTPUT 1
DECL|macro|H8300_GPIO_RESERVE
mdefine_line|#define H8300_GPIO_RESERVE(port, bits) &bslash;&n;        h8300_reserved_gpio(port, bits)
DECL|macro|H8300_GPIO_FREE
mdefine_line|#define H8300_GPIO_FREE(port, bits) &bslash;&n;        h8300_free_gpio(port, bits)
DECL|macro|H8300_GPIO_DDR
mdefine_line|#define H8300_GPIO_DDR(port, bit, dir) &bslash;&n;        h8300_set_gpio_dir(((port) &lt;&lt; 8) | (bit), dir)
DECL|macro|H8300_GPIO_GETDIR
mdefine_line|#define H8300_GPIO_GETDIR(port, bit) &bslash;&n;        h8300_get_gpio_dir(((port) &lt;&lt; 8) | (bit))
r_extern
r_int
id|h8300_reserved_gpio
c_func
(paren
r_int
id|port
comma
r_int
id|bits
)paren
suffix:semicolon
r_extern
r_int
id|h8300_free_gpio
c_func
(paren
r_int
id|port
comma
r_int
id|bits
)paren
suffix:semicolon
r_extern
r_int
id|h8300_set_gpio_dir
c_func
(paren
r_int
id|port_bit
comma
r_int
id|dir
)paren
suffix:semicolon
r_extern
r_int
id|h8300_get_gpio_dir
c_func
(paren
r_int
id|port_bit
)paren
suffix:semicolon
r_extern
r_int
id|h8300_init_gpio
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
