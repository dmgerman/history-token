multiline_comment|/*&n; * LCD Lowlevel Control Abstraction&n; *&n; * Copyright (C) 2003,2004 Hewlett-Packard Company&n; *&n; */
macro_line|#ifndef _LINUX_LCD_H
DECL|macro|_LINUX_LCD_H
mdefine_line|#define _LINUX_LCD_H
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
r_struct
id|lcd_device
suffix:semicolon
r_struct
id|fb_info
suffix:semicolon
multiline_comment|/* This structure defines all the properties of a LCD flat panel. */
DECL|struct|lcd_properties
r_struct
id|lcd_properties
(brace
multiline_comment|/* Owner module */
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
multiline_comment|/* Get the LCD panel power status (0: full on, 1..3: controller&n;&t;   power on, flat panel power off, 4: full off), see FB_BLANK_XXX */
DECL|member|get_power
r_int
(paren
op_star
id|get_power
)paren
(paren
r_struct
id|lcd_device
op_star
)paren
suffix:semicolon
multiline_comment|/* Enable or disable power to the LCD (0: on; 4: off, see FB_BLANK_XXX) */
DECL|member|set_power
r_int
(paren
op_star
id|set_power
)paren
(paren
r_struct
id|lcd_device
op_star
comma
r_int
id|power
)paren
suffix:semicolon
multiline_comment|/* The maximum value for contrast (read-only) */
DECL|member|max_contrast
r_int
id|max_contrast
suffix:semicolon
multiline_comment|/* Get the current contrast setting (0-max_contrast) */
DECL|member|get_contrast
r_int
(paren
op_star
id|get_contrast
)paren
(paren
r_struct
id|lcd_device
op_star
)paren
suffix:semicolon
multiline_comment|/* Set LCD panel contrast */
DECL|member|set_contrast
r_int
(paren
op_star
id|set_contrast
)paren
(paren
r_struct
id|lcd_device
op_star
comma
r_int
id|contrast
)paren
suffix:semicolon
multiline_comment|/* Check if given framebuffer device is the one LCD is bound to;&n;&t;   return 0 if not, !=0 if it is. If NULL, lcd always matches the fb. */
DECL|member|check_fb
r_int
(paren
op_star
id|check_fb
)paren
(paren
r_struct
id|fb_info
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|lcd_device
r_struct
id|lcd_device
(brace
multiline_comment|/* This protects the &squot;props&squot; field. If &squot;props&squot; is NULL, the driver that&n;&t;   registered this device has been unloaded, and if class_get_devdata()&n;&t;   points to something in the body of that driver, it is also invalid. */
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
multiline_comment|/* If this is NULL, the backing module is unloaded */
DECL|member|props
r_struct
id|lcd_properties
op_star
id|props
suffix:semicolon
multiline_comment|/* The framebuffer notifier block */
DECL|member|fb_notif
r_struct
id|notifier_block
id|fb_notif
suffix:semicolon
multiline_comment|/* The class device structure */
DECL|member|class_dev
r_struct
id|class_device
id|class_dev
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|lcd_device
op_star
id|lcd_device_register
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_void
op_star
id|devdata
comma
r_struct
id|lcd_properties
op_star
id|lp
)paren
suffix:semicolon
r_extern
r_void
id|lcd_device_unregister
c_func
(paren
r_struct
id|lcd_device
op_star
id|ld
)paren
suffix:semicolon
DECL|macro|to_lcd_device
mdefine_line|#define to_lcd_device(obj) container_of(obj, struct lcd_device, class_dev)
macro_line|#endif
eof
