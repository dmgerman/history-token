multiline_comment|/*&n; *  Backlight Driver for Sharp Corgi&n; *&n; *  Copyright (c) 2004-2005 Richard Purdie&n; *&n; *  Based on Sharp&squot;s 2.4 Backlight Driver&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License version 2 as&n; *  published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/backlight.h&gt;
macro_line|#include &lt;asm/arch-pxa/corgi.h&gt;
macro_line|#include &lt;asm/hardware/scoop.h&gt;
DECL|macro|CORGI_MAX_INTENSITY
mdefine_line|#define CORGI_MAX_INTENSITY &t;&t;0x3e
DECL|macro|CORGI_DEFAULT_INTENSITY
mdefine_line|#define CORGI_DEFAULT_INTENSITY&t;&t;0x1f
DECL|macro|CORGI_LIMIT_MASK
mdefine_line|#define CORGI_LIMIT_MASK&t;&t;&t;0x0b
DECL|variable|corgibl_powermode
r_static
r_int
id|corgibl_powermode
op_assign
id|FB_BLANK_UNBLANK
suffix:semicolon
DECL|variable|current_intensity
r_static
r_int
id|current_intensity
op_assign
l_int|0
suffix:semicolon
DECL|variable|corgibl_limit
r_static
r_int
id|corgibl_limit
op_assign
l_int|0
suffix:semicolon
DECL|variable|bl_lock
r_static
id|spinlock_t
id|bl_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|corgibl_send_intensity
r_static
r_void
id|corgibl_send_intensity
c_func
(paren
r_int
id|intensity
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_void
(paren
op_star
id|corgi_kick_batt
)paren
(paren
r_void
)paren
suffix:semicolon
r_if
c_cond
(paren
id|corgibl_powermode
op_ne
id|FB_BLANK_UNBLANK
)paren
(brace
id|intensity
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|corgibl_limit
)paren
id|intensity
op_and_assign
id|CORGI_LIMIT_MASK
suffix:semicolon
)brace
multiline_comment|/* Skip 0x20 as it will blank the display */
r_if
c_cond
(paren
id|intensity
op_ge
l_int|0x20
)paren
id|intensity
op_increment
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|bl_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Bits 0-4 are accessed via the SSP interface */
id|corgi_ssp_blduty_set
c_func
(paren
id|intensity
op_amp
l_int|0x1f
)paren
suffix:semicolon
multiline_comment|/* Bit 5 is via SCOOP */
r_if
c_cond
(paren
id|intensity
op_amp
l_int|0x0020
)paren
id|set_scoop_gpio
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|CORGI_SCP_BACKLIGHT_CONT
)paren
suffix:semicolon
r_else
id|reset_scoop_gpio
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|CORGI_SCP_BACKLIGHT_CONT
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|bl_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|corgibl_blank
r_static
r_void
id|corgibl_blank
c_func
(paren
r_int
id|blank
)paren
(brace
r_switch
c_cond
(paren
id|blank
)paren
(brace
r_case
id|FB_BLANK_NORMAL
suffix:colon
r_case
id|FB_BLANK_VSYNC_SUSPEND
suffix:colon
r_case
id|FB_BLANK_HSYNC_SUSPEND
suffix:colon
r_case
id|FB_BLANK_POWERDOWN
suffix:colon
r_if
c_cond
(paren
id|corgibl_powermode
op_eq
id|FB_BLANK_UNBLANK
)paren
(brace
id|corgibl_send_intensity
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|corgibl_powermode
op_assign
id|blank
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|FB_BLANK_UNBLANK
suffix:colon
r_if
c_cond
(paren
id|corgibl_powermode
op_ne
id|FB_BLANK_UNBLANK
)paren
(brace
id|corgibl_powermode
op_assign
id|blank
suffix:semicolon
id|corgibl_send_intensity
c_func
(paren
id|current_intensity
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_PM
DECL|function|corgibl_suspend
r_static
r_int
id|corgibl_suspend
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|state
comma
id|u32
id|level
)paren
(brace
r_if
c_cond
(paren
id|level
op_eq
id|SUSPEND_POWER_DOWN
)paren
id|corgibl_blank
c_func
(paren
id|FB_BLANK_POWERDOWN
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|corgibl_resume
r_static
r_int
id|corgibl_resume
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|level
)paren
(brace
r_if
c_cond
(paren
id|level
op_eq
id|RESUME_POWER_ON
)paren
id|corgibl_blank
c_func
(paren
id|FB_BLANK_UNBLANK
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|macro|corgibl_suspend
mdefine_line|#define corgibl_suspend&t;NULL
DECL|macro|corgibl_resume
mdefine_line|#define corgibl_resume&t;NULL
macro_line|#endif
DECL|function|corgibl_set_power
r_static
r_int
id|corgibl_set_power
c_func
(paren
r_struct
id|backlight_device
op_star
id|bd
comma
r_int
id|state
)paren
(brace
id|corgibl_blank
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|corgibl_get_power
r_static
r_int
id|corgibl_get_power
c_func
(paren
r_struct
id|backlight_device
op_star
id|bd
)paren
(brace
r_return
id|corgibl_powermode
suffix:semicolon
)brace
DECL|function|corgibl_set_intensity
r_static
r_int
id|corgibl_set_intensity
c_func
(paren
r_struct
id|backlight_device
op_star
id|bd
comma
r_int
id|intensity
)paren
(brace
r_if
c_cond
(paren
id|intensity
OG
id|CORGI_MAX_INTENSITY
)paren
id|intensity
op_assign
id|CORGI_MAX_INTENSITY
suffix:semicolon
id|corgibl_send_intensity
c_func
(paren
id|intensity
)paren
suffix:semicolon
id|current_intensity
op_assign
id|intensity
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|corgibl_get_intensity
r_static
r_int
id|corgibl_get_intensity
c_func
(paren
r_struct
id|backlight_device
op_star
id|bd
)paren
(brace
r_return
id|current_intensity
suffix:semicolon
)brace
multiline_comment|/*&n; * Called when the battery is low to limit the backlight intensity.&n; * If limit==0 clear any limit, otherwise limit the intensity&n; */
DECL|function|corgibl_limit_intensity
r_void
id|corgibl_limit_intensity
c_func
(paren
r_int
id|limit
)paren
(brace
id|corgibl_limit
op_assign
(paren
id|limit
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
id|corgibl_send_intensity
c_func
(paren
id|current_intensity
)paren
suffix:semicolon
)brace
DECL|variable|corgibl_limit_intensity
id|EXPORT_SYMBOL
c_func
(paren
id|corgibl_limit_intensity
)paren
suffix:semicolon
DECL|variable|corgibl_data
r_static
r_struct
id|backlight_properties
id|corgibl_data
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|get_power
op_assign
id|corgibl_get_power
comma
dot
id|set_power
op_assign
id|corgibl_set_power
comma
dot
id|max_brightness
op_assign
id|CORGI_MAX_INTENSITY
comma
dot
id|get_brightness
op_assign
id|corgibl_get_intensity
comma
dot
id|set_brightness
op_assign
id|corgibl_set_intensity
comma
)brace
suffix:semicolon
DECL|variable|corgi_backlight_device
r_static
r_struct
id|backlight_device
op_star
id|corgi_backlight_device
suffix:semicolon
DECL|function|corgibl_probe
r_static
r_int
id|__init
id|corgibl_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|corgi_backlight_device
op_assign
id|backlight_device_register
(paren
l_string|&quot;corgi-bl&quot;
comma
l_int|NULL
comma
op_amp
id|corgibl_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
(paren
id|corgi_backlight_device
)paren
)paren
r_return
id|PTR_ERR
(paren
id|corgi_backlight_device
)paren
suffix:semicolon
id|corgibl_set_intensity
c_func
(paren
l_int|NULL
comma
id|CORGI_DEFAULT_INTENSITY
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Corgi Backlight Driver Initialized.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|corgibl_remove
r_static
r_int
id|corgibl_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|backlight_device_unregister
c_func
(paren
id|corgi_backlight_device
)paren
suffix:semicolon
id|corgibl_set_intensity
c_func
(paren
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Corgi Backlight Driver Unloaded&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|corgibl_driver
r_static
r_struct
id|device_driver
id|corgibl_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;corgi-bl&quot;
comma
dot
id|bus
op_assign
op_amp
id|platform_bus_type
comma
dot
id|probe
op_assign
id|corgibl_probe
comma
dot
id|remove
op_assign
id|corgibl_remove
comma
dot
id|suspend
op_assign
id|corgibl_suspend
comma
dot
id|resume
op_assign
id|corgibl_resume
comma
)brace
suffix:semicolon
DECL|function|corgibl_init
r_static
r_int
id|__init
id|corgibl_init
c_func
(paren
r_void
)paren
(brace
r_return
id|driver_register
c_func
(paren
op_amp
id|corgibl_driver
)paren
suffix:semicolon
)brace
DECL|function|corgibl_exit
r_static
r_void
id|__exit
id|corgibl_exit
c_func
(paren
r_void
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|corgibl_driver
)paren
suffix:semicolon
)brace
DECL|variable|corgibl_init
id|module_init
c_func
(paren
id|corgibl_init
)paren
suffix:semicolon
DECL|variable|corgibl_exit
id|module_exit
c_func
(paren
id|corgibl_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Richard Purdie &lt;rpurdie@rpsys.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Corgi Backlight Driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPLv2&quot;
)paren
suffix:semicolon
eof
