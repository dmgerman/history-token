macro_line|#ifndef LED_H
DECL|macro|LED_H
mdefine_line|#define LED_H
DECL|macro|LED7
mdefine_line|#define&t;LED7&t;&t;0x80&t;&t;/* top (or furthest right) LED */
DECL|macro|LED6
mdefine_line|#define&t;LED6&t;&t;0x40
DECL|macro|LED5
mdefine_line|#define&t;LED5&t;&t;0x20
DECL|macro|LED4
mdefine_line|#define&t;LED4&t;&t;0x10
DECL|macro|LED3
mdefine_line|#define&t;LED3&t;&t;0x08
DECL|macro|LED2
mdefine_line|#define&t;LED2&t;&t;0x04
DECL|macro|LED1
mdefine_line|#define&t;LED1&t;&t;0x02
DECL|macro|LED0
mdefine_line|#define&t;LED0&t;&t;0x01&t;&t;/* bottom (or furthest left) LED */
DECL|macro|LED_LAN_TX
mdefine_line|#define&t;LED_LAN_TX&t;LED0&t;&t;/* for LAN transmit activity */
DECL|macro|LED_LAN_RCV
mdefine_line|#define&t;LED_LAN_RCV&t;LED1&t;&t;/* for LAN receive activity */
DECL|macro|LED_DISK_IO
mdefine_line|#define&t;LED_DISK_IO&t;LED2&t;&t;/* for disk activity */
DECL|macro|LED_HEARTBEAT
mdefine_line|#define&t;LED_HEARTBEAT&t;LED3&t;&t;/* heartbeat */
multiline_comment|/* irq function */
r_extern
r_void
id|led_interrupt_func
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* LASI &amp; ASP specific LED initialization funcs */
r_extern
r_void
id|__init
id|lasi_led_init
c_func
(paren
r_int
r_int
id|lasi_hpa
)paren
suffix:semicolon
r_extern
r_void
id|__init
id|asp_led_init
c_func
(paren
r_int
r_int
id|led_ptr
)paren
suffix:semicolon
multiline_comment|/* registers the LED regions for procfs */
r_extern
r_void
id|__init
id|register_led_regions
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* main LED initialization function (uses the PDC) */
r_extern
r_int
id|__init
id|led_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* LED_H */
eof
