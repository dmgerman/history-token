multiline_comment|/*&n; *  toshiba_acpi.c - Toshiba Laptop ACPI Extras&n; *&n; *&n; *  Copyright (C) 2002-2003 John Belmonte&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; *&n; *  The devolpment page for this driver is located at&n; *  http://memebeam.org/toys/ToshibaAcpiDriver.&n; *&n; *  Credits:&n; *&t;Jonathan A. Buzzard - Toshiba HCI info, and critical tips on reverse&n; *&t;&t;engineering the Windows drivers&n; *&t;Yasushi Nagato - changes for linux kernel 2.4 -&gt; 2.5&n; *&t;Rob Miller - TV out and hotkeys help&n; *&n; *&n; *  TODO&n; *&n; */
DECL|macro|TOSHIBA_ACPI_VERSION
mdefine_line|#define TOSHIBA_ACPI_VERSION&t;&quot;0.16&quot;
DECL|macro|PROC_INTERFACE_VERSION
mdefine_line|#define PROC_INTERFACE_VERSION&t;1
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;acpi/acpi_drivers.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;John Belmonte&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Toshiba Laptop ACPI Extras Driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* Toshiba ACPI method paths */
DECL|macro|METHOD_LCD_BRIGHTNESS
mdefine_line|#define METHOD_LCD_BRIGHTNESS&t;&quot;&bslash;&bslash;_SB_.PCI0.VGA_.LCD_._BCM&quot;
DECL|macro|METHOD_HCI
mdefine_line|#define METHOD_HCI&t;&t;&quot;&bslash;&bslash;_SB_.VALD.GHCI&quot;
DECL|macro|METHOD_VIDEO_OUT
mdefine_line|#define METHOD_VIDEO_OUT&t;&quot;&bslash;&bslash;_SB_.VALX.DSSX&quot;
multiline_comment|/* Toshiba HCI interface definitions&n; *&n; * HCI is Toshiba&squot;s &quot;Hardware Control Interface&quot; which is supposed to&n; * be uniform across all their models.  Ideally we would just call&n; * dedicated ACPI methods instead of using this primitive interface.&n; * However the ACPI methods seem to be incomplete in some areas (for&n; * example they allow setting, but not reading, the LCD brightness value),&n; * so this is still useful.&n; */
DECL|macro|HCI_WORDS
mdefine_line|#define HCI_WORDS&t;&t;&t;6
multiline_comment|/* operations */
DECL|macro|HCI_SET
mdefine_line|#define HCI_SET&t;&t;&t;&t;0xff00
DECL|macro|HCI_GET
mdefine_line|#define HCI_GET&t;&t;&t;&t;0xfe00
multiline_comment|/* return codes */
DECL|macro|HCI_SUCCESS
mdefine_line|#define HCI_SUCCESS&t;&t;&t;0x0000
DECL|macro|HCI_FAILURE
mdefine_line|#define HCI_FAILURE&t;&t;&t;0x1000
DECL|macro|HCI_NOT_SUPPORTED
mdefine_line|#define HCI_NOT_SUPPORTED&t;&t;0x8000
DECL|macro|HCI_EMPTY
mdefine_line|#define HCI_EMPTY&t;&t;&t;0x8c00
multiline_comment|/* registers */
DECL|macro|HCI_FAN
mdefine_line|#define HCI_FAN&t;&t;&t;&t;0x0004
DECL|macro|HCI_SYSTEM_EVENT
mdefine_line|#define HCI_SYSTEM_EVENT&t;&t;0x0016
DECL|macro|HCI_VIDEO_OUT
mdefine_line|#define HCI_VIDEO_OUT&t;&t;&t;0x001c
DECL|macro|HCI_HOTKEY_EVENT
mdefine_line|#define HCI_HOTKEY_EVENT&t;&t;0x001e
DECL|macro|HCI_LCD_BRIGHTNESS
mdefine_line|#define HCI_LCD_BRIGHTNESS&t;&t;0x002a
multiline_comment|/* field definitions */
DECL|macro|HCI_LCD_BRIGHTNESS_BITS
mdefine_line|#define HCI_LCD_BRIGHTNESS_BITS&t;&t;3
DECL|macro|HCI_LCD_BRIGHTNESS_SHIFT
mdefine_line|#define HCI_LCD_BRIGHTNESS_SHIFT&t;(16-HCI_LCD_BRIGHTNESS_BITS)
DECL|macro|HCI_LCD_BRIGHTNESS_LEVELS
mdefine_line|#define HCI_LCD_BRIGHTNESS_LEVELS&t;(1 &lt;&lt; HCI_LCD_BRIGHTNESS_BITS)
DECL|macro|HCI_VIDEO_OUT_LCD
mdefine_line|#define HCI_VIDEO_OUT_LCD&t;&t;0x1
DECL|macro|HCI_VIDEO_OUT_CRT
mdefine_line|#define HCI_VIDEO_OUT_CRT&t;&t;0x2
DECL|macro|HCI_VIDEO_OUT_TV
mdefine_line|#define HCI_VIDEO_OUT_TV&t;&t;0x4
multiline_comment|/* utility&n; */
r_static
id|__inline__
r_void
DECL|function|_set_bit
id|_set_bit
c_func
(paren
id|u32
op_star
id|word
comma
id|u32
id|mask
comma
r_int
id|value
)paren
(brace
op_star
id|word
op_assign
(paren
op_star
id|word
op_amp
op_complement
id|mask
)paren
op_or
(paren
id|mask
op_star
id|value
)paren
suffix:semicolon
)brace
multiline_comment|/* an sscanf that takes explicit string length */
r_static
r_int
DECL|function|snscanf
id|snscanf
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_int
id|n
comma
r_const
r_char
op_star
id|format
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|result
suffix:semicolon
r_char
op_star
id|str2
op_assign
id|kmalloc
c_func
(paren
id|n
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|str2
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* NOTE: don&squot;t even _think_ about replacing this with strlcpy */
id|strncpy
c_func
(paren
id|str2
comma
id|str
comma
id|n
)paren
suffix:semicolon
id|str2
(braket
id|n
)braket
op_assign
l_int|0
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|format
)paren
suffix:semicolon
id|result
op_assign
id|vsscanf
c_func
(paren
id|str2
comma
id|format
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|str2
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* acpi interface wrappers&n; */
r_static
r_int
DECL|function|write_acpi_int
id|write_acpi_int
c_func
(paren
r_const
r_char
op_star
id|methodName
comma
r_int
id|val
)paren
(brace
r_struct
id|acpi_object_list
id|params
suffix:semicolon
r_union
id|acpi_object
id|in_objs
(braket
l_int|1
)braket
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|params.count
op_assign
r_sizeof
(paren
id|in_objs
)paren
op_div
r_sizeof
(paren
id|in_objs
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|params.pointer
op_assign
id|in_objs
suffix:semicolon
id|in_objs
(braket
l_int|0
)braket
dot
id|type
op_assign
id|ACPI_TYPE_INTEGER
suffix:semicolon
id|in_objs
(braket
l_int|0
)braket
dot
id|integer.value
op_assign
id|val
suffix:semicolon
id|status
op_assign
id|acpi_evaluate_object
c_func
(paren
l_int|0
comma
(paren
r_char
op_star
)paren
id|methodName
comma
op_amp
id|params
comma
l_int|0
)paren
suffix:semicolon
r_return
(paren
id|status
op_eq
id|AE_OK
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_static
r_int
id|read_acpi_int
c_func
(paren
r_const
r_char
op_star
id|methodName
comma
r_int
op_star
id|pVal
)paren
(brace
r_struct
id|acpi_buffer
id|results
suffix:semicolon
r_union
id|acpi_object
id|out_objs
(braket
l_int|1
)braket
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|results.length
op_assign
r_sizeof
(paren
id|out_objs
)paren
suffix:semicolon
id|results.pointer
op_assign
id|out_objs
suffix:semicolon
id|status
op_assign
id|acpi_evaluate_object
c_func
(paren
l_int|0
comma
(paren
r_char
op_star
)paren
id|methodName
comma
l_int|0
comma
op_amp
id|results
)paren
suffix:semicolon
op_star
id|pVal
op_assign
id|out_objs
(braket
l_int|0
)braket
dot
id|integer.value
suffix:semicolon
r_return
(paren
id|status
op_eq
id|AE_OK
)paren
op_logical_and
(paren
id|out_objs
(braket
l_int|0
)braket
dot
id|type
op_eq
id|ACPI_TYPE_INTEGER
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Perform a raw HCI call.  Here we don&squot;t care about input or output buffer&n; * format.&n; */
r_static
id|acpi_status
DECL|function|hci_raw
id|hci_raw
c_func
(paren
r_const
id|u32
id|in
(braket
id|HCI_WORDS
)braket
comma
id|u32
id|out
(braket
id|HCI_WORDS
)braket
)paren
(brace
r_struct
id|acpi_object_list
id|params
suffix:semicolon
r_union
id|acpi_object
id|in_objs
(braket
id|HCI_WORDS
)braket
suffix:semicolon
r_struct
id|acpi_buffer
id|results
suffix:semicolon
r_union
id|acpi_object
id|out_objs
(braket
id|HCI_WORDS
op_plus
l_int|1
)braket
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
r_int
id|i
suffix:semicolon
id|params.count
op_assign
id|HCI_WORDS
suffix:semicolon
id|params.pointer
op_assign
id|in_objs
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
id|HCI_WORDS
suffix:semicolon
op_increment
id|i
)paren
(brace
id|in_objs
(braket
id|i
)braket
dot
id|type
op_assign
id|ACPI_TYPE_INTEGER
suffix:semicolon
id|in_objs
(braket
id|i
)braket
dot
id|integer.value
op_assign
id|in
(braket
id|i
)braket
suffix:semicolon
)brace
id|results.length
op_assign
r_sizeof
(paren
id|out_objs
)paren
suffix:semicolon
id|results.pointer
op_assign
id|out_objs
suffix:semicolon
id|status
op_assign
id|acpi_evaluate_object
c_func
(paren
l_int|0
comma
id|METHOD_HCI
comma
op_amp
id|params
comma
op_amp
id|results
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_eq
id|AE_OK
)paren
op_logical_and
(paren
id|out_objs-&gt;package.count
op_le
id|HCI_WORDS
)paren
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|out_objs-&gt;package.count
suffix:semicolon
op_increment
id|i
)paren
(brace
id|out
(braket
id|i
)braket
op_assign
id|out_objs-&gt;package.elements
(braket
id|i
)braket
dot
id|integer.value
suffix:semicolon
)brace
)brace
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/* common hci tasks (get or set one value)&n; *&n; * In addition to the ACPI status, the HCI system returns a result which&n; * may be useful (such as &quot;not supported&quot;).&n; */
r_static
id|acpi_status
DECL|function|hci_write1
id|hci_write1
c_func
(paren
id|u32
id|reg
comma
id|u32
id|in1
comma
id|u32
op_star
id|result
)paren
(brace
id|u32
id|in
(braket
id|HCI_WORDS
)braket
op_assign
(brace
id|HCI_SET
comma
id|reg
comma
id|in1
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
id|u32
id|out
(braket
id|HCI_WORDS
)braket
suffix:semicolon
id|acpi_status
id|status
op_assign
id|hci_raw
c_func
(paren
id|in
comma
id|out
)paren
suffix:semicolon
op_star
id|result
op_assign
(paren
id|status
op_eq
id|AE_OK
)paren
ques
c_cond
id|out
(braket
l_int|0
)braket
suffix:colon
id|HCI_FAILURE
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
id|acpi_status
DECL|function|hci_read1
id|hci_read1
c_func
(paren
id|u32
id|reg
comma
id|u32
op_star
id|out1
comma
id|u32
op_star
id|result
)paren
(brace
id|u32
id|in
(braket
id|HCI_WORDS
)braket
op_assign
(brace
id|HCI_GET
comma
id|reg
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
id|u32
id|out
(braket
id|HCI_WORDS
)braket
suffix:semicolon
id|acpi_status
id|status
op_assign
id|hci_raw
c_func
(paren
id|in
comma
id|out
)paren
suffix:semicolon
op_star
id|out1
op_assign
id|out
(braket
l_int|2
)braket
suffix:semicolon
op_star
id|result
op_assign
(paren
id|status
op_eq
id|AE_OK
)paren
ques
c_cond
id|out
(braket
l_int|0
)braket
suffix:colon
id|HCI_FAILURE
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|variable|toshiba_proc_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|toshiba_proc_dir
suffix:semicolon
DECL|variable|force_fan
r_static
r_int
id|force_fan
suffix:semicolon
DECL|variable|last_key_event
r_static
r_int
id|last_key_event
suffix:semicolon
DECL|variable|key_event_valid
r_static
r_int
id|key_event_valid
suffix:semicolon
DECL|struct|_ProcItem
r_typedef
r_struct
id|_ProcItem
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|read_func
r_char
op_star
(paren
op_star
id|read_func
)paren
(paren
r_char
op_star
)paren
suffix:semicolon
DECL|member|write_func
r_int
r_int
(paren
op_star
id|write_func
)paren
(paren
r_const
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|typedef|ProcItem
)brace
id|ProcItem
suffix:semicolon
multiline_comment|/* proc file handlers&n; */
r_static
r_int
DECL|function|dispatch_read
id|dispatch_read
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
id|ProcItem
op_star
id|item
)paren
(brace
r_char
op_star
id|p
op_assign
id|page
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|off
op_eq
l_int|0
)paren
id|p
op_assign
id|item
op_member_access_from_pointer
id|read_func
c_func
(paren
id|p
)paren
suffix:semicolon
multiline_comment|/* ISSUE: I don&squot;t understand this code */
id|len
op_assign
(paren
id|p
op_minus
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
id|off
op_plus
id|count
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|count
)paren
id|len
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_static
r_int
DECL|function|dispatch_write
id|dispatch_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
id|ProcItem
op_star
id|item
)paren
(brace
r_return
id|item
op_member_access_from_pointer
id|write_func
c_func
(paren
id|buffer
comma
id|count
)paren
suffix:semicolon
)brace
r_static
r_char
op_star
DECL|function|read_lcd
id|read_lcd
c_func
(paren
r_char
op_star
id|p
)paren
(brace
id|u32
id|hci_result
suffix:semicolon
id|u32
id|value
suffix:semicolon
id|hci_read1
c_func
(paren
id|HCI_LCD_BRIGHTNESS
comma
op_amp
id|value
comma
op_amp
id|hci_result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hci_result
op_eq
id|HCI_SUCCESS
)paren
(brace
id|value
op_assign
id|value
op_rshift
id|HCI_LCD_BRIGHTNESS_SHIFT
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;brightness:              %d&bslash;n&quot;
comma
id|value
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;brightness_levels:       %d&bslash;n&quot;
comma
id|HCI_LCD_BRIGHTNESS_LEVELS
)paren
suffix:semicolon
)brace
r_else
(brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;ERROR&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|write_lcd
id|write_lcd
c_func
(paren
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
)paren
(brace
r_int
id|value
suffix:semicolon
id|u32
id|hci_result
suffix:semicolon
r_if
c_cond
(paren
id|snscanf
c_func
(paren
id|buffer
comma
id|count
comma
l_string|&quot; brightness : %i&quot;
comma
op_amp
id|value
)paren
op_eq
l_int|1
op_logical_and
id|value
op_ge
l_int|0
op_logical_and
id|value
OL
id|HCI_LCD_BRIGHTNESS_LEVELS
)paren
(brace
id|value
op_assign
id|value
op_lshift
id|HCI_LCD_BRIGHTNESS_SHIFT
suffix:semicolon
id|hci_write1
c_func
(paren
id|HCI_LCD_BRIGHTNESS
comma
id|value
comma
op_amp
id|hci_result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hci_result
op_ne
id|HCI_SUCCESS
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
r_static
r_char
op_star
DECL|function|read_video
id|read_video
c_func
(paren
r_char
op_star
id|p
)paren
(brace
id|u32
id|hci_result
suffix:semicolon
id|u32
id|value
suffix:semicolon
id|hci_read1
c_func
(paren
id|HCI_VIDEO_OUT
comma
op_amp
id|value
comma
op_amp
id|hci_result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hci_result
op_eq
id|HCI_SUCCESS
)paren
(brace
r_int
id|is_lcd
op_assign
(paren
id|value
op_amp
id|HCI_VIDEO_OUT_LCD
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_int
id|is_crt
op_assign
(paren
id|value
op_amp
id|HCI_VIDEO_OUT_CRT
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_int
id|is_tv
op_assign
(paren
id|value
op_amp
id|HCI_VIDEO_OUT_TV
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;lcd_out:                 %d&bslash;n&quot;
comma
id|is_lcd
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;crt_out:                 %d&bslash;n&quot;
comma
id|is_crt
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;tv_out:                  %d&bslash;n&quot;
comma
id|is_tv
)paren
suffix:semicolon
)brace
r_else
(brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;ERROR&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|write_video
id|write_video
c_func
(paren
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
)paren
(brace
r_int
id|value
suffix:semicolon
r_const
r_char
op_star
id|buffer_end
op_assign
id|buffer
op_plus
id|count
suffix:semicolon
r_int
id|lcd_out
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|crt_out
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|tv_out
op_assign
op_minus
l_int|1
suffix:semicolon
id|u32
id|hci_result
suffix:semicolon
r_int
id|video_out
suffix:semicolon
multiline_comment|/* scan expression.  Multiple expressions may be delimited with ; */
r_do
(brace
r_if
c_cond
(paren
id|snscanf
c_func
(paren
id|buffer
comma
id|count
comma
l_string|&quot; lcd_out : %i&quot;
comma
op_amp
id|value
)paren
op_eq
l_int|1
)paren
id|lcd_out
op_assign
id|value
op_amp
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|snscanf
c_func
(paren
id|buffer
comma
id|count
comma
l_string|&quot; crt_out : %i&quot;
comma
op_amp
id|value
)paren
op_eq
l_int|1
)paren
id|crt_out
op_assign
id|value
op_amp
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|snscanf
c_func
(paren
id|buffer
comma
id|count
comma
l_string|&quot; tv_out : %i&quot;
comma
op_amp
id|value
)paren
op_eq
l_int|1
)paren
id|tv_out
op_assign
id|value
op_amp
l_int|1
suffix:semicolon
multiline_comment|/* advance to one character past the next ; */
r_do
op_increment
id|buffer
suffix:semicolon
r_while
c_loop
(paren
(paren
id|buffer
OL
id|buffer_end
)paren
op_logical_and
(paren
op_star
(paren
id|buffer
op_minus
l_int|1
)paren
op_ne
l_char|&squot;;&squot;
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|buffer
OL
id|buffer_end
)paren
suffix:semicolon
id|hci_read1
c_func
(paren
id|HCI_VIDEO_OUT
comma
op_amp
id|video_out
comma
op_amp
id|hci_result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hci_result
op_eq
id|HCI_SUCCESS
)paren
(brace
r_int
id|new_video_out
op_assign
id|video_out
suffix:semicolon
r_if
c_cond
(paren
id|lcd_out
op_ne
op_minus
l_int|1
)paren
id|_set_bit
c_func
(paren
op_amp
id|new_video_out
comma
id|HCI_VIDEO_OUT_LCD
comma
id|lcd_out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|crt_out
op_ne
op_minus
l_int|1
)paren
id|_set_bit
c_func
(paren
op_amp
id|new_video_out
comma
id|HCI_VIDEO_OUT_CRT
comma
id|crt_out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tv_out
op_ne
op_minus
l_int|1
)paren
id|_set_bit
c_func
(paren
op_amp
id|new_video_out
comma
id|HCI_VIDEO_OUT_TV
comma
id|tv_out
)paren
suffix:semicolon
multiline_comment|/* To avoid unnecessary video disruption, only write the new&n;&t;&t; * video setting if something changed. */
r_if
c_cond
(paren
id|new_video_out
op_ne
id|video_out
)paren
id|write_acpi_int
c_func
(paren
id|METHOD_VIDEO_OUT
comma
id|new_video_out
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
r_static
r_char
op_star
DECL|function|read_fan
id|read_fan
c_func
(paren
r_char
op_star
id|p
)paren
(brace
id|u32
id|hci_result
suffix:semicolon
id|u32
id|value
suffix:semicolon
id|hci_read1
c_func
(paren
id|HCI_FAN
comma
op_amp
id|value
comma
op_amp
id|hci_result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hci_result
op_eq
id|HCI_SUCCESS
)paren
(brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;running:                 %d&bslash;n&quot;
comma
(paren
id|value
OG
l_int|0
)paren
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;force_on:                %d&bslash;n&quot;
comma
id|force_fan
)paren
suffix:semicolon
)brace
r_else
(brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;ERROR&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|write_fan
id|write_fan
c_func
(paren
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
)paren
(brace
r_int
id|value
suffix:semicolon
id|u32
id|hci_result
suffix:semicolon
r_if
c_cond
(paren
id|snscanf
c_func
(paren
id|buffer
comma
id|count
comma
l_string|&quot; force_on : %i&quot;
comma
op_amp
id|value
)paren
op_eq
l_int|1
op_logical_and
id|value
op_ge
l_int|0
op_logical_and
id|value
op_le
l_int|1
)paren
(brace
id|hci_write1
c_func
(paren
id|HCI_FAN
comma
id|value
comma
op_amp
id|hci_result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hci_result
op_ne
id|HCI_SUCCESS
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_else
id|force_fan
op_assign
id|value
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
r_static
r_char
op_star
DECL|function|read_keys
id|read_keys
c_func
(paren
r_char
op_star
id|p
)paren
(brace
id|u32
id|hci_result
suffix:semicolon
id|u32
id|value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|key_event_valid
)paren
(brace
id|hci_read1
c_func
(paren
id|HCI_SYSTEM_EVENT
comma
op_amp
id|value
comma
op_amp
id|hci_result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hci_result
op_eq
id|HCI_SUCCESS
)paren
(brace
id|key_event_valid
op_assign
l_int|1
suffix:semicolon
id|last_key_event
op_assign
id|value
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hci_result
op_eq
id|HCI_EMPTY
)paren
(brace
multiline_comment|/* better luck next time */
)brace
r_else
r_if
c_cond
(paren
id|hci_result
op_eq
id|HCI_NOT_SUPPORTED
)paren
(brace
multiline_comment|/* This is a workaround for an unresolved issue on&n;&t;&t;&t; * some machines where system events sporadically&n;&t;&t;&t; * become disabled. */
id|hci_write1
c_func
(paren
id|HCI_SYSTEM_EVENT
comma
l_int|1
comma
op_amp
id|hci_result
)paren
suffix:semicolon
)brace
r_else
(brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;ERROR&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
)brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;hotkey_ready:            %d&bslash;n&quot;
comma
id|key_event_valid
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;hotkey:                  0x%04x&bslash;n&quot;
comma
id|last_key_event
)paren
suffix:semicolon
id|end
suffix:colon
r_return
id|p
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|write_keys
id|write_keys
c_func
(paren
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
)paren
(brace
r_int
id|value
suffix:semicolon
r_if
c_cond
(paren
id|snscanf
c_func
(paren
id|buffer
comma
id|count
comma
l_string|&quot; hotkey_ready : %i&quot;
comma
op_amp
id|value
)paren
op_eq
l_int|1
op_logical_and
id|value
op_eq
l_int|0
)paren
(brace
id|key_event_valid
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
r_static
r_char
op_star
DECL|function|read_version
id|read_version
c_func
(paren
r_char
op_star
id|p
)paren
(brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;driver:                  %s&bslash;n&quot;
comma
id|TOSHIBA_ACPI_VERSION
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;proc_interface:          %d&bslash;n&quot;
comma
id|PROC_INTERFACE_VERSION
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/* proc and module init&n; */
DECL|macro|PROC_TOSHIBA
mdefine_line|#define PROC_TOSHIBA&t;&t;&quot;toshiba&quot;
DECL|variable|proc_items
id|ProcItem
id|proc_items
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;lcd&quot;
comma
id|read_lcd
comma
id|write_lcd
)brace
comma
(brace
l_string|&quot;video&quot;
comma
id|read_video
comma
id|write_video
)brace
comma
(brace
l_string|&quot;fan&quot;
comma
id|read_fan
comma
id|write_fan
)brace
comma
(brace
l_string|&quot;keys&quot;
comma
id|read_keys
comma
id|write_keys
)brace
comma
(brace
l_string|&quot;version&quot;
comma
id|read_version
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
r_static
id|acpi_status
DECL|function|add_device
id|add_device
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|proc
suffix:semicolon
id|ProcItem
op_star
id|item
suffix:semicolon
r_for
c_loop
(paren
id|item
op_assign
id|proc_items
suffix:semicolon
id|item-&gt;name
suffix:semicolon
op_increment
id|item
)paren
(brace
id|proc
op_assign
id|create_proc_read_entry
c_func
(paren
id|item-&gt;name
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|toshiba_proc_dir
comma
(paren
id|read_proc_t
op_star
)paren
id|dispatch_read
comma
id|item
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proc
op_logical_and
id|item-&gt;write_func
)paren
id|proc-&gt;write_proc
op_assign
(paren
id|write_proc_t
op_star
)paren
id|dispatch_write
suffix:semicolon
)brace
r_return
id|AE_OK
suffix:semicolon
)brace
r_static
id|acpi_status
DECL|function|remove_device
id|remove_device
c_func
(paren
r_void
)paren
(brace
id|ProcItem
op_star
id|item
suffix:semicolon
r_for
c_loop
(paren
id|item
op_assign
id|proc_items
suffix:semicolon
id|item-&gt;name
suffix:semicolon
op_increment
id|item
)paren
id|remove_proc_entry
c_func
(paren
id|item-&gt;name
comma
id|toshiba_proc_dir
)paren
suffix:semicolon
r_return
id|AE_OK
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|toshiba_acpi_init
id|toshiba_acpi_init
c_func
(paren
r_void
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_int
id|value
suffix:semicolon
id|u32
id|hci_result
suffix:semicolon
multiline_comment|/* simple device detection: try reading an HCI register */
id|hci_read1
c_func
(paren
id|HCI_LCD_BRIGHTNESS
comma
op_amp
id|value
comma
op_amp
id|hci_result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hci_result
op_ne
id|HCI_SUCCESS
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Toshiba Laptop ACPI Extras version %s&bslash;n&quot;
comma
id|TOSHIBA_ACPI_VERSION
)paren
suffix:semicolon
id|force_fan
op_assign
l_int|0
suffix:semicolon
id|key_event_valid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* enable event fifo */
id|hci_write1
c_func
(paren
id|HCI_SYSTEM_EVENT
comma
l_int|1
comma
op_amp
id|hci_result
)paren
suffix:semicolon
id|toshiba_proc_dir
op_assign
id|proc_mkdir
c_func
(paren
id|PROC_TOSHIBA
comma
id|acpi_root_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|toshiba_proc_dir
)paren
(brace
id|status
op_assign
id|AE_ERROR
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
id|add_device
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
id|remove_proc_entry
c_func
(paren
id|PROC_TOSHIBA
comma
id|acpi_root_dir
)paren
suffix:semicolon
)brace
r_return
(paren
id|ACPI_SUCCESS
c_func
(paren
id|status
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENODEV
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|toshiba_acpi_exit
id|toshiba_acpi_exit
c_func
(paren
r_void
)paren
(brace
id|remove_device
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|toshiba_proc_dir
)paren
id|remove_proc_entry
c_func
(paren
id|PROC_TOSHIBA
comma
id|acpi_root_dir
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|toshiba_acpi_init
id|module_init
c_func
(paren
id|toshiba_acpi_init
)paren
suffix:semicolon
DECL|variable|toshiba_acpi_exit
id|module_exit
c_func
(paren
id|toshiba_acpi_exit
)paren
suffix:semicolon
eof
