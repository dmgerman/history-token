multiline_comment|/*&n; * LCD, LED and Button interface for Cobalt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1997 by Andrew Bose&n; *&n; * Linux kernel version history:&n; *       March 2001: Ported from 2.0.34  by Liam Davies&n; *&n; */
DECL|macro|RTC_IO_EXTENT
mdefine_line|#define RTC_IO_EXTENT&t;0x10    /*Only really two ports, but...&t;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;lcd.h&quot;
r_static
r_int
id|lcd_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
DECL|variable|lcd_present
r_static
r_int
id|lcd_present
op_assign
l_int|1
suffix:semicolon
DECL|variable|led_state
r_int
id|led_state
op_assign
l_int|0
suffix:semicolon
macro_line|#if defined(CONFIG_TULIP) &amp;&amp; 0
DECL|macro|MAX_INTERFACES
mdefine_line|#define MAX_INTERFACES&t;8
DECL|variable|linkcheck_callbacks
r_static
id|linkcheck_func_t
id|linkcheck_callbacks
(braket
id|MAX_INTERFACES
)braket
suffix:semicolon
DECL|variable|linkcheck_cookies
r_static
r_void
op_star
id|linkcheck_cookies
(braket
id|MAX_INTERFACES
)braket
suffix:semicolon
DECL|function|lcd_register_linkcheck_func
r_int
id|lcd_register_linkcheck_func
c_func
(paren
r_int
id|iface_num
comma
r_void
op_star
id|func
comma
r_void
op_star
id|cookie
)paren
(brace
r_if
c_cond
(paren
id|iface_num
OL
l_int|0
op_logical_or
id|iface_num
op_ge
id|MAX_INTERFACES
op_logical_or
id|linkcheck_callbacks
(braket
id|iface_num
)braket
op_ne
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|linkcheck_callbacks
(braket
id|iface_num
)braket
op_assign
(paren
id|linkcheck_func_t
)paren
id|func
suffix:semicolon
id|linkcheck_cookies
(braket
id|iface_num
)braket
op_assign
id|cookie
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|lcd_ioctl
r_static
r_int
id|lcd_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|lcd_display
id|button_display
suffix:semicolon
r_int
r_int
id|address
comma
id|a
suffix:semicolon
r_int
id|index
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|LCD_On
suffix:colon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x0F
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LCD_Off
suffix:colon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x08
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LCD_Reset
suffix:colon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x3F
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x3F
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x3F
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x3F
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x01
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x06
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LCD_Clear
suffix:colon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x01
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LCD_Cursor_Left
suffix:colon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x10
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LCD_Cursor_Right
suffix:colon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x14
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LCD_Cursor_Off
suffix:colon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x0C
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LCD_Cursor_On
suffix:colon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x0F
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LCD_Blink_Off
suffix:colon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x0E
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LCD_Get_Cursor_Pos
suffix:colon
(brace
r_struct
id|lcd_display
id|display
suffix:semicolon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|display.cursor_address
op_assign
(paren
id|LCDReadInst
)paren
suffix:semicolon
id|display.cursor_address
op_assign
(paren
id|display.cursor_address
op_amp
l_int|0x07F
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|lcd_display
op_star
)paren
id|arg
comma
op_amp
id|display
comma
r_sizeof
(paren
r_struct
id|lcd_display
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|LCD_Set_Cursor_Pos
suffix:colon
(brace
r_struct
id|lcd_display
id|display
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|display
comma
(paren
r_struct
id|lcd_display
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|lcd_display
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|a
op_assign
(paren
id|display.cursor_address
op_or
id|kLCD_Addr
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
id|a
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|LCD_Get_Cursor
suffix:colon
(brace
r_struct
id|lcd_display
id|display
suffix:semicolon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|display.character
op_assign
id|LCDReadData
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|lcd_display
op_star
)paren
id|arg
comma
op_amp
id|display
comma
r_sizeof
(paren
r_struct
id|lcd_display
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x10
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|LCD_Set_Cursor
suffix:colon
(brace
r_struct
id|lcd_display
id|display
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|display
comma
(paren
r_struct
id|lcd_display
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|lcd_display
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteData
c_func
(paren
id|display.character
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x10
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|LCD_Disp_Left
suffix:colon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x18
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LCD_Disp_Right
suffix:colon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x1C
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LCD_Home
suffix:colon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x02
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LCD_Write
suffix:colon
(brace
r_struct
id|lcd_display
id|display
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|display
comma
(paren
r_struct
id|lcd_display
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|lcd_display
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0x80
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
(paren
id|display.size1
)paren
suffix:semicolon
id|index
op_increment
)paren
(brace
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteData
c_func
(paren
id|display.line1
(braket
id|index
)braket
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
)brace
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
l_int|0xC0
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
(paren
id|display.size2
)paren
suffix:semicolon
id|index
op_increment
)paren
(brace
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteData
c_func
(paren
id|display.line2
(braket
id|index
)braket
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|LCD_Read
suffix:colon
(brace
r_struct
id|lcd_display
id|display
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|address
op_assign
id|kDD_R00
suffix:semicolon
id|address
op_le
id|kDD_R01
suffix:semicolon
id|address
op_increment
)paren
(brace
id|a
op_assign
(paren
id|address
op_or
id|kLCD_Addr
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
id|a
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|display.line1
(braket
id|address
)braket
op_assign
id|LCDReadData
suffix:semicolon
)brace
id|display.line1
(braket
l_int|0x27
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_for
c_loop
(paren
id|address
op_assign
id|kDD_R10
suffix:semicolon
id|address
op_le
id|kDD_R11
suffix:semicolon
id|address
op_increment
)paren
(brace
id|a
op_assign
(paren
id|address
op_or
id|kLCD_Addr
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|LCDWriteInst
c_func
(paren
id|a
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|BusyCheck
c_func
(paren
)paren
suffix:semicolon
id|display.line2
(braket
id|address
op_minus
l_int|0x40
)braket
op_assign
id|LCDReadData
suffix:semicolon
)brace
id|display.line2
(braket
l_int|0x27
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|lcd_display
op_star
)paren
id|arg
comma
op_amp
id|display
comma
r_sizeof
(paren
r_struct
id|lcd_display
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
singleline_comment|//  set all GPIO leds to led_display.leds 
r_case
id|LED_Set
suffix:colon
(brace
r_struct
id|lcd_display
id|led_display
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|led_display
comma
(paren
r_struct
id|lcd_display
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|lcd_display
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|led_state
op_assign
id|led_display.leds
suffix:semicolon
id|LEDSet
c_func
(paren
id|led_state
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
singleline_comment|//  set only bit led_display.leds
r_case
id|LED_Bit_Set
suffix:colon
(brace
r_int
id|i
suffix:semicolon
r_int
id|bit
op_assign
l_int|1
suffix:semicolon
r_struct
id|lcd_display
id|led_display
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|led_display
comma
(paren
r_struct
id|lcd_display
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|lcd_display
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
r_int
)paren
id|led_display.leds
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bit
op_assign
l_int|2
op_star
id|bit
suffix:semicolon
)brace
id|led_state
op_assign
id|led_state
op_or
id|bit
suffix:semicolon
id|LEDSet
c_func
(paren
id|led_state
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
singleline_comment|//  clear only bit led_display.leds
r_case
id|LED_Bit_Clear
suffix:colon
(brace
r_int
id|i
suffix:semicolon
r_int
id|bit
op_assign
l_int|1
suffix:semicolon
r_struct
id|lcd_display
id|led_display
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|led_display
comma
(paren
r_struct
id|lcd_display
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|lcd_display
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
r_int
)paren
id|led_display.leds
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bit
op_assign
l_int|2
op_star
id|bit
suffix:semicolon
)brace
id|led_state
op_assign
id|led_state
op_amp
op_complement
id|bit
suffix:semicolon
id|LEDSet
c_func
(paren
id|led_state
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|BUTTON_Read
suffix:colon
(brace
id|button_display.buttons
op_assign
id|GPIRead
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|lcd_display
op_star
)paren
id|arg
comma
op_amp
id|button_display
comma
r_sizeof
(paren
r_struct
id|lcd_display
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|LINK_Check
suffix:colon
(brace
id|button_display.buttons
op_assign
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
l_int|0xB0100060
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|lcd_display
op_star
)paren
id|arg
comma
op_amp
id|button_display
comma
r_sizeof
(paren
r_struct
id|lcd_display
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|LINK_Check_2
suffix:colon
(brace
r_int
id|iface_num
suffix:semicolon
multiline_comment|/* panel-utils should pass in the desired interface status is wanted for&n;&t;&t; * in &quot;buttons&quot; of the structure.  We will set this to non-zero if the&n;&t;&t; * link is in fact up for the requested interface.  --DaveM&n;&t;&t; */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|button_display
comma
(paren
r_struct
id|lcd_display
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|button_display
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|iface_num
op_assign
id|button_display.buttons
suffix:semicolon
macro_line|#if defined(CONFIG_TULIP) &amp;&amp; 0
r_if
c_cond
(paren
id|iface_num
op_ge
l_int|0
op_logical_and
id|iface_num
OL
id|MAX_INTERFACES
op_logical_and
id|linkcheck_callbacks
(braket
id|iface_num
)braket
op_ne
l_int|NULL
)paren
(brace
id|button_display.buttons
op_assign
id|linkcheck_callbacks
(braket
id|iface_num
)braket
(paren
id|linkcheck_cookies
(braket
id|iface_num
)braket
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
id|button_display.buttons
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|__copy_to_user
c_func
(paren
(paren
r_struct
id|lcd_display
op_star
)paren
id|arg
comma
op_amp
id|button_display
comma
r_sizeof
(paren
r_struct
id|lcd_display
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
singleline_comment|//  Erase the flash
r_case
id|FLASH_Erase
suffix:colon
(brace
r_int
id|ctr
op_assign
l_int|0
suffix:semicolon
singleline_comment|// Chip Erase Sequence
id|WRITE_FLASH
c_func
(paren
id|kFlash_Addr1
comma
id|kFlash_Data1
)paren
suffix:semicolon
id|WRITE_FLASH
c_func
(paren
id|kFlash_Addr2
comma
id|kFlash_Data2
)paren
suffix:semicolon
id|WRITE_FLASH
c_func
(paren
id|kFlash_Addr1
comma
id|kFlash_Erase3
)paren
suffix:semicolon
id|WRITE_FLASH
c_func
(paren
id|kFlash_Addr1
comma
id|kFlash_Data1
)paren
suffix:semicolon
id|WRITE_FLASH
c_func
(paren
id|kFlash_Addr2
comma
id|kFlash_Data2
)paren
suffix:semicolon
id|WRITE_FLASH
c_func
(paren
id|kFlash_Addr1
comma
id|kFlash_Erase6
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Erasing Flash.&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
op_logical_neg
id|dqpoll
c_func
(paren
l_int|0x00000000
comma
l_int|0xFF
)paren
)paren
op_logical_and
(paren
op_logical_neg
id|timeout
c_func
(paren
l_int|0x00000000
)paren
)paren
)paren
(brace
id|ctr
op_increment
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|READ_FLASH
c_func
(paren
l_int|0x07FFF0
)paren
op_eq
l_int|0xFF
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Erase Successful&bslash;r&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|timeout
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Erase Timed Out&bslash;r&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
singleline_comment|// burn the flash 
r_case
id|FLASH_Burn
suffix:colon
(brace
r_volatile
r_int
r_int
id|burn_addr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_char
op_star
id|rom
suffix:semicolon
r_struct
id|lcd_display
id|display
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|display
comma
(paren
r_struct
id|lcd_display
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|lcd_display
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|rom
op_assign
(paren
r_int
r_char
op_star
)paren
id|kmalloc
c_func
(paren
(paren
l_int|128
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rom
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
l_string|&quot;broken&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Churning and Burning -&quot;
)paren
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|FLASH_SIZE
suffix:semicolon
id|i
op_assign
id|i
op_plus
l_int|128
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|rom
comma
id|display.RomImage
op_plus
id|i
comma
l_int|128
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|burn_addr
op_assign
id|kFlashBase
op_plus
id|i
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
(paren
l_int|128
)paren
suffix:semicolon
id|index
op_increment
)paren
(brace
id|WRITE_FLASH
c_func
(paren
id|kFlash_Addr1
comma
id|kFlash_Data1
)paren
suffix:semicolon
id|WRITE_FLASH
c_func
(paren
id|kFlash_Addr2
comma
id|kFlash_Data2
)paren
suffix:semicolon
id|WRITE_FLASH
c_func
(paren
id|kFlash_Addr1
comma
id|kFlash_Prog
)paren
suffix:semicolon
op_star
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|burn_addr
)paren
op_assign
(paren
r_volatile
r_int
r_char
)paren
id|rom
(braket
id|index
)braket
suffix:semicolon
r_while
c_loop
(paren
(paren
op_logical_neg
id|dqpoll
c_func
(paren
id|burn_addr
comma
(paren
r_volatile
r_int
r_char
)paren
id|rom
(braket
id|index
)braket
)paren
)paren
op_logical_and
(paren
op_logical_neg
id|timeout
c_func
(paren
id|burn_addr
)paren
)paren
)paren
(brace
)brace
id|burn_addr
op_increment
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|burn_addr
op_minus
l_int|1
)paren
)paren
op_eq
(paren
r_volatile
r_int
r_char
)paren
id|rom
(braket
id|index
op_minus
l_int|1
)braket
)paren
(brace
)brace
r_else
r_if
c_cond
(paren
id|timeout
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Program timed out&bslash;r&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|rom
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
singleline_comment|//  read the flash all at once 
r_case
id|FLASH_Read
suffix:colon
(brace
r_int
r_char
op_star
id|user_bytes
suffix:semicolon
r_volatile
r_int
r_int
id|read_addr
suffix:semicolon
r_int
id|i
suffix:semicolon
id|user_bytes
op_assign
op_amp
(paren
(paren
(paren
r_struct
id|lcd_display
op_star
)paren
id|arg
)paren
op_member_access_from_pointer
id|RomImage
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|user_bytes
comma
id|FLASH_SIZE
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Reading Flash&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|FLASH_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
id|tmp_byte
suffix:semicolon
id|read_addr
op_assign
id|kFlashBase
op_plus
id|i
suffix:semicolon
id|tmp_byte
op_assign
op_star
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|read_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__put_user
(paren
id|tmp_byte
comma
op_amp
id|user_bytes
(braket
id|i
)braket
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lcd_open
r_static
r_int
id|lcd_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|lcd_present
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Only RESET or NEXT counts as button pressed */
DECL|function|button_pressed
r_static
r_inline
r_int
id|button_pressed
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|buttons
op_assign
id|GPIRead
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buttons
op_eq
id|BUTTON_Next
)paren
op_logical_or
(paren
id|buttons
op_eq
id|BUTTON_Next_B
)paren
op_logical_or
(paren
id|buttons
op_eq
id|BUTTON_Reset_B
)paren
)paren
r_return
id|buttons
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* LED daemon sits on this and we wake him up once a key is pressed. */
DECL|variable|lcd_waiters
r_static
r_int
id|lcd_waiters
op_assign
l_int|0
suffix:semicolon
DECL|function|lcd_read
r_static
r_int
id|lcd_read
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
r_int
id|count
)paren
(brace
r_int
id|buttons_now
suffix:semicolon
r_if
c_cond
(paren
id|lcd_waiters
OG
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|lcd_waiters
op_increment
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
id|buttons_now
op_assign
(paren
r_int
)paren
id|button_pressed
c_func
(paren
)paren
)paren
op_eq
l_int|0
)paren
op_logical_and
op_logical_neg
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|2
op_star
id|HZ
)paren
suffix:semicolon
)brace
id|lcd_waiters
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
r_return
id|buttons_now
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;The various file operations we support.&n; */
DECL|variable|lcd_fops
r_static
r_struct
id|file_operations
id|lcd_fops
op_assign
(brace
id|read
suffix:colon
id|lcd_read
comma
id|ioctl
suffix:colon
id|lcd_ioctl
comma
id|open
suffix:colon
id|lcd_open
comma
)brace
suffix:semicolon
DECL|variable|lcd_dev
r_static
r_struct
id|miscdevice
id|lcd_dev
op_assign
(brace
id|LCD_MINOR
comma
l_string|&quot;lcd&quot;
comma
op_amp
id|lcd_fops
)brace
suffix:semicolon
DECL|function|lcd_init
r_int
id|lcd_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|data
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|LCD_DRIVER
)paren
suffix:semicolon
id|misc_register
c_func
(paren
op_amp
id|lcd_dev
)paren
suffix:semicolon
multiline_comment|/* Check region? Naaah! Just snarf it up. */
multiline_comment|/*&t;request_region(RTC_PORT(0), RTC_IO_EXTENT, &quot;lcd&quot;);*/
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
id|data
op_assign
id|LCDReadData
suffix:semicolon
r_if
c_cond
(paren
(paren
id|data
op_amp
l_int|0x000000FF
)paren
op_eq
(paren
l_int|0x00
)paren
)paren
(brace
id|lcd_present
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;LCD Not Present&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|lcd_present
op_assign
l_int|1
suffix:semicolon
id|WRITE_GAL
c_func
(paren
id|kGal_DevBank2PReg
comma
id|kGal_DevBank2Cfg
)paren
suffix:semicolon
id|WRITE_GAL
c_func
(paren
id|kGal_DevBank3PReg
comma
id|kGal_DevBank3Cfg
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|//
singleline_comment|// Function: dqpoll
singleline_comment|//
singleline_comment|// Description:  Polls the data lines to see if the flash is busy
singleline_comment|//
singleline_comment|// In: address, byte data
singleline_comment|//
singleline_comment|// Out: 0 = busy, 1 = write or erase complete
singleline_comment|//
singleline_comment|//
DECL|function|dqpoll
r_int
id|dqpoll
c_func
(paren
r_volatile
r_int
r_int
id|address
comma
r_volatile
r_int
r_char
id|data
)paren
(brace
r_volatile
r_int
r_char
id|dq7
suffix:semicolon
id|dq7
op_assign
id|data
op_amp
l_int|0x80
suffix:semicolon
r_return
(paren
(paren
id|READ_FLASH
c_func
(paren
id|address
)paren
op_amp
l_int|0x80
)paren
op_eq
id|dq7
)paren
suffix:semicolon
)brace
singleline_comment|//
singleline_comment|// Function: timeout
singleline_comment|//
singleline_comment|// Description: Checks to see if erase or write has timed out
singleline_comment|//              By polling dq5
singleline_comment|//
singleline_comment|// In: address
singleline_comment|//
singleline_comment|//
singleline_comment|// Out: 0 = not timed out, 1 = timed out
DECL|function|timeout
r_int
id|timeout
c_func
(paren
r_volatile
r_int
r_int
id|address
)paren
(brace
r_return
(paren
(paren
id|READ_FLASH
c_func
(paren
id|address
)paren
op_amp
l_int|0x20
)paren
op_eq
l_int|0x20
)paren
suffix:semicolon
)brace
eof
