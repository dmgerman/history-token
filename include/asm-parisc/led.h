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
multiline_comment|/* values for pdc_chassis_lcd_info_ret_block.model: */
DECL|macro|DISPLAY_MODEL_LCD
mdefine_line|#define DISPLAY_MODEL_LCD  0&t;&t;/* KittyHawk LED or LCD */
DECL|macro|DISPLAY_MODEL_NONE
mdefine_line|#define DISPLAY_MODEL_NONE 1&t;&t;/* no LED or LCD */
DECL|macro|DISPLAY_MODEL_LASI
mdefine_line|#define DISPLAY_MODEL_LASI 2&t;&t;/* LASI style 8 bit LED */
DECL|macro|DISPLAY_MODEL_OLD_ASP
mdefine_line|#define DISPLAY_MODEL_OLD_ASP 0x7F&t;/* faked: ASP style 8 x 1 bit LED (only very old ASP versions) */
DECL|macro|LED_CMD_REG_NONE
mdefine_line|#define LED_CMD_REG_NONE 0&t;&t;/* NULL == no addr for the cmd register */
multiline_comment|/* led tasklet struct */
r_extern
r_struct
id|tasklet_struct
id|led_tasklet
suffix:semicolon
multiline_comment|/* register_led_driver() */
r_int
id|__init
id|register_led_driver
c_func
(paren
r_int
id|model
comma
r_int
r_int
id|cmd_reg
comma
r_int
r_int
id|data_reg
)paren
suffix:semicolon
multiline_comment|/* registers the LED regions for procfs */
r_void
id|__init
id|register_led_regions
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CHASSIS_LCD_LED
multiline_comment|/* writes a string to the LCD display (if possible on this h/w) */
r_int
id|lcd_print
c_func
(paren
r_char
op_star
id|str
)paren
suffix:semicolon
macro_line|#else
DECL|macro|lcd_print
mdefine_line|#define lcd_print(str)
macro_line|#endif
multiline_comment|/* main LED initialization function (uses PDC) */
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
