multiline_comment|/*&n; *    Chassis LCD/LED driver for HP-PARISC workstations&n; *&n; *      (c) Copyright 2000 Red Hat Software&n; *      (c) Copyright 2000 Helge Deller &lt;hdeller@redhat.com&gt;&n; *      (c) Copyright 2001-2002 Helge Deller &lt;deller@gmx.de&gt;&n; *      (c) Copyright 2001 Randolph Chung &lt;tausq@debian.org&gt;&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; * TODO:&n; *&t;- speed-up calculations with inlined assembler&n; *&t;- interface to write to second row of LCD from /proc&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;&t;/* for offsetof() */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/param.h&gt;&t;&t;/* HZ */
macro_line|#include &lt;asm/led.h&gt;
macro_line|#include &lt;asm/pdc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* The control of the LEDs and LCDs on PARISC-machines have to be done &n;   completely in software. The necessary calculations are done in a tasklet&n;   which is scheduled at every timer interrupt and since the calculations &n;   may consume relatively much CPU-time some of the calculations can be &n;   turned off with the following variables (controlled via procfs) */
DECL|variable|led_type
r_static
r_int
id|led_type
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|led_heartbeat
r_static
r_int
id|led_heartbeat
op_assign
l_int|1
suffix:semicolon
DECL|variable|led_diskio
r_static
r_int
id|led_diskio
op_assign
l_int|1
suffix:semicolon
DECL|variable|led_lanrxtx
r_static
r_int
id|led_lanrxtx
op_assign
l_int|1
suffix:semicolon
DECL|variable|lcd_text
r_static
r_char
id|lcd_text
(braket
l_int|32
)braket
suffix:semicolon
macro_line|#if 0
mdefine_line|#define DPRINTK(x)&t;printk x
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(x)
macro_line|#endif
DECL|macro|CALC_ADD
mdefine_line|#define CALC_ADD(val, comp, add) &bslash;&n; (val&lt;=(comp/8) ? add/16 : val&lt;=(comp/4) ? add/8 : val&lt;=(comp/2) ? add/4 : add)
DECL|struct|lcd_block
r_struct
id|lcd_block
(brace
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
multiline_comment|/* stores the command byte      */
DECL|member|on
r_int
r_char
id|on
suffix:semicolon
multiline_comment|/* value for turning LED on     */
DECL|member|off
r_int
r_char
id|off
suffix:semicolon
multiline_comment|/* value for turning LED off    */
)brace
suffix:semicolon
multiline_comment|/* Structure returned by PDC_RETURN_CHASSIS_INFO */
multiline_comment|/* NOTE: we use unsigned long:16 two times, since the following member &n;   lcd_cmd_reg_addr needs to be 64bit aligned on 64bit PA2.0-machines */
DECL|struct|pdc_chassis_lcd_info_ret_block
r_struct
id|pdc_chassis_lcd_info_ret_block
(brace
DECL|member|model
r_int
r_int
id|model
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* DISPLAY_MODEL_XXXX */
DECL|member|lcd_width
r_int
r_int
id|lcd_width
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* width of the LCD in chars (DISPLAY_MODEL_LCD only) */
DECL|member|lcd_cmd_reg_addr
r_char
op_star
id|lcd_cmd_reg_addr
suffix:semicolon
multiline_comment|/* ptr to LCD cmd-register &amp; data ptr for LED */
DECL|member|lcd_data_reg_addr
r_char
op_star
id|lcd_data_reg_addr
suffix:semicolon
multiline_comment|/* ptr to LCD data-register (LCD only) */
DECL|member|min_cmd_delay
r_int
r_int
id|min_cmd_delay
suffix:semicolon
multiline_comment|/* delay in uS after cmd-write (LCD only) */
DECL|member|reset_cmd1
r_int
r_char
id|reset_cmd1
suffix:semicolon
multiline_comment|/* command #1 for writing LCD string (LCD only) */
DECL|member|reset_cmd2
r_int
r_char
id|reset_cmd2
suffix:semicolon
multiline_comment|/* command #2 for writing LCD string (LCD only) */
DECL|member|act_enable
r_int
r_char
id|act_enable
suffix:semicolon
multiline_comment|/* 0 = no activity (LCD only) */
DECL|member|heartbeat
r_struct
id|lcd_block
id|heartbeat
suffix:semicolon
DECL|member|disk_io
r_struct
id|lcd_block
id|disk_io
suffix:semicolon
DECL|member|lan_rcv
r_struct
id|lcd_block
id|lan_rcv
suffix:semicolon
DECL|member|lan_tx
r_struct
id|lcd_block
id|lan_tx
suffix:semicolon
DECL|member|_pad
r_char
id|_pad
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* LCD_CMD and LCD_DATA for KittyHawk machines */
DECL|macro|KITTYHAWK_LCD_CMD
mdefine_line|#define KITTYHAWK_LCD_CMD  (0xfffffffff0190000UL) /* 64bit-ready */
DECL|macro|KITTYHAWK_LCD_DATA
mdefine_line|#define KITTYHAWK_LCD_DATA (KITTYHAWK_LCD_CMD+1)
multiline_comment|/* lcd_info is pre-initialized to the values needed to program KittyHawk LCD&squot;s &n; * HP seems to have used Sharp/Hitachi HD44780 LCDs most of the time. */
r_static
r_struct
id|pdc_chassis_lcd_info_ret_block
DECL|variable|lcd_info
id|lcd_info
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
op_assign
(brace
dot
id|model
op_assign
id|DISPLAY_MODEL_LCD
comma
dot
id|lcd_width
op_assign
l_int|16
comma
dot
id|lcd_cmd_reg_addr
op_assign
(paren
r_char
op_star
)paren
id|KITTYHAWK_LCD_CMD
comma
dot
id|lcd_data_reg_addr
op_assign
(paren
r_char
op_star
)paren
id|KITTYHAWK_LCD_DATA
comma
dot
id|min_cmd_delay
op_assign
l_int|40
comma
dot
id|reset_cmd1
op_assign
l_int|0x80
comma
dot
id|reset_cmd2
op_assign
l_int|0xc0
comma
)brace
suffix:semicolon
multiline_comment|/* direct access to some of the lcd_info variables */
DECL|macro|LCD_CMD_REG
mdefine_line|#define LCD_CMD_REG&t;lcd_info.lcd_cmd_reg_addr&t; 
DECL|macro|LCD_DATA_REG
mdefine_line|#define LCD_DATA_REG&t;lcd_info.lcd_data_reg_addr&t; 
DECL|macro|LED_DATA_REG
mdefine_line|#define LED_DATA_REG&t;lcd_info.lcd_cmd_reg_addr&t;/* LASI &amp; ASP only */
multiline_comment|/* ptr to LCD/LED-specific function */
DECL|variable|led_func_ptr
r_static
r_void
(paren
op_star
id|led_func_ptr
)paren
(paren
r_int
r_char
)paren
suffix:semicolon
DECL|macro|LED_HASLCD
mdefine_line|#define LED_HASLCD 1
DECL|macro|LED_NOLCD
mdefine_line|#define LED_NOLCD  0
macro_line|#ifdef CONFIG_PROC_FS
DECL|function|led_proc_read
r_static
r_int
id|led_proc_read
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
r_void
op_star
id|data
)paren
(brace
r_char
op_star
id|out
op_assign
id|page
suffix:semicolon
r_int
id|len
suffix:semicolon
r_switch
c_cond
(paren
(paren
r_int
)paren
id|data
)paren
(brace
r_case
id|LED_NOLCD
suffix:colon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;Heartbeat: %d&bslash;n&quot;
comma
id|led_heartbeat
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;Disk IO: %d&bslash;n&quot;
comma
id|led_diskio
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;LAN Rx/Tx: %d&bslash;n&quot;
comma
id|led_lanrxtx
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LED_HASLCD
suffix:colon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|lcd_text
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|len
op_assign
id|out
op_minus
id|page
op_minus
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|count
)paren
(brace
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|len
op_assign
id|count
suffix:semicolon
)brace
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|led_proc_write
r_static
r_int
id|led_proc_write
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
id|buf
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_char
op_star
id|cur
comma
id|lbuf
(braket
id|count
)braket
suffix:semicolon
r_int
id|d
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|memset
c_func
(paren
id|lbuf
comma
l_int|0
comma
id|count
)paren
suffix:semicolon
id|copy_from_user
c_func
(paren
id|lbuf
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|cur
op_assign
id|lbuf
suffix:semicolon
multiline_comment|/* skip initial spaces */
r_while
c_loop
(paren
op_star
id|cur
op_logical_and
id|isspace
c_func
(paren
op_star
id|cur
)paren
)paren
(brace
id|cur
op_increment
suffix:semicolon
)brace
r_switch
c_cond
(paren
(paren
r_int
)paren
id|data
)paren
(brace
r_case
id|LED_NOLCD
suffix:colon
id|d
op_assign
op_star
id|cur
op_increment
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|d
op_ne
l_int|0
op_logical_and
id|d
op_ne
l_int|1
)paren
r_goto
id|parse_error
suffix:semicolon
id|led_heartbeat
op_assign
id|d
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cur
op_increment
op_ne
l_char|&squot; &squot;
)paren
r_goto
id|parse_error
suffix:semicolon
id|d
op_assign
op_star
id|cur
op_increment
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|d
op_ne
l_int|0
op_logical_and
id|d
op_ne
l_int|1
)paren
r_goto
id|parse_error
suffix:semicolon
id|led_diskio
op_assign
id|d
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cur
op_increment
op_ne
l_char|&squot; &squot;
)paren
r_goto
id|parse_error
suffix:semicolon
id|d
op_assign
op_star
id|cur
op_increment
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|d
op_ne
l_int|0
op_logical_and
id|d
op_ne
l_int|1
)paren
r_goto
id|parse_error
suffix:semicolon
id|led_lanrxtx
op_assign
id|d
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LED_HASLCD
suffix:colon
r_if
c_cond
(paren
op_star
id|cur
op_eq
l_int|0
)paren
(brace
multiline_comment|/* reset to default */
id|lcd_print
c_func
(paren
l_string|&quot;Linux &quot;
id|UTS_RELEASE
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* chop off trailing &bslash;n.. if the user gives multiple&n;&t;&t;&t; * &bslash;n then it&squot;s all their fault.. */
r_if
c_cond
(paren
op_star
id|cur
op_logical_and
id|cur
(braket
id|strlen
c_func
(paren
id|cur
)paren
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|cur
(braket
id|strlen
c_func
(paren
id|cur
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|lcd_print
c_func
(paren
id|cur
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
id|parse_error
suffix:colon
r_if
c_cond
(paren
(paren
r_int
)paren
id|data
op_eq
id|LED_NOLCD
)paren
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Parse error: expect &bslash;&quot;n n n&bslash;&quot; (n == 0 or 1) for heartbeat,&bslash;ndisk io and lan tx/rx indicators&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|led_create_procfs
r_static
r_int
id|__init
id|led_create_procfs
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|proc_pdc_root
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
r_if
c_cond
(paren
id|led_type
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|proc_pdc_root
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;pdc&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_pdc_root
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|proc_pdc_root-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|ent
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;led&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|proc_pdc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|ent-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|ent-&gt;data
op_assign
(paren
r_void
op_star
)paren
id|LED_NOLCD
suffix:semicolon
multiline_comment|/* LED */
id|ent-&gt;read_proc
op_assign
id|led_proc_read
suffix:semicolon
id|ent-&gt;write_proc
op_assign
id|led_proc_write
suffix:semicolon
id|ent-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
r_if
c_cond
(paren
id|led_type
op_eq
id|LED_HASLCD
)paren
(brace
id|ent
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;lcd&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|proc_pdc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|ent-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|ent-&gt;data
op_assign
(paren
r_void
op_star
)paren
id|LED_HASLCD
suffix:semicolon
multiline_comment|/* LCD */
id|ent-&gt;read_proc
op_assign
id|led_proc_read
suffix:semicolon
id|ent-&gt;write_proc
op_assign
id|led_proc_write
suffix:semicolon
id|ent-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;   ** &n;   ** led_ASP_driver()&n;   ** &n; */
DECL|macro|LED_DATA
mdefine_line|#define&t;LED_DATA&t;0x01&t;/* data to shift (0:on 1:off) */
DECL|macro|LED_STROBE
mdefine_line|#define&t;LED_STROBE&t;0x02&t;/* strobe to clock data */
DECL|function|led_ASP_driver
r_static
r_void
id|led_ASP_driver
c_func
(paren
r_int
r_char
id|leds
)paren
(brace
r_int
id|i
suffix:semicolon
id|leds
op_assign
op_complement
id|leds
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
id|value
suffix:semicolon
id|value
op_assign
(paren
id|leds
op_amp
l_int|0x80
)paren
op_rshift
l_int|7
suffix:semicolon
id|gsc_writeb
c_func
(paren
id|value
comma
id|LED_DATA_REG
)paren
suffix:semicolon
id|gsc_writeb
c_func
(paren
id|value
op_or
id|LED_STROBE
comma
id|LED_DATA_REG
)paren
suffix:semicolon
id|leds
op_lshift_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;   ** &n;   ** led_LASI_driver()&n;   ** &n; */
DECL|function|led_LASI_driver
r_static
r_void
id|led_LASI_driver
c_func
(paren
r_int
r_char
id|leds
)paren
(brace
id|leds
op_assign
op_complement
id|leds
suffix:semicolon
id|gsc_writeb
c_func
(paren
id|leds
comma
id|LED_DATA_REG
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;   ** &n;   ** led_LCD_driver()&n;   ** &n;   ** The logic of the LCD driver is, that we write at every scheduled call&n;   ** only to one of LCD_CMD_REG _or_ LCD_DATA_REG - registers.&n;   ** That way we don&squot;t need to let this tasklet busywait for min_cmd_delay&n;   ** milliseconds.&n;   **&n;   ** TODO: check the value of &quot;min_cmd_delay&quot; against the value of HZ.&n;   **   &n; */
DECL|function|led_LCD_driver
r_static
r_void
id|led_LCD_driver
c_func
(paren
r_int
r_char
id|leds
)paren
(brace
r_static
r_int
id|last_index
suffix:semicolon
multiline_comment|/* 0:heartbeat, 1:disk, 2:lan_in, 3:lan_out */
r_static
r_int
id|last_was_cmd
suffix:semicolon
multiline_comment|/* 0: CMD was written last, 1: DATA was last */
r_struct
id|lcd_block
op_star
id|block_ptr
suffix:semicolon
r_int
id|value
suffix:semicolon
r_switch
c_cond
(paren
id|last_index
)paren
(brace
r_case
l_int|0
suffix:colon
id|block_ptr
op_assign
op_amp
id|lcd_info.heartbeat
suffix:semicolon
id|value
op_assign
id|leds
op_amp
id|LED_HEARTBEAT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|block_ptr
op_assign
op_amp
id|lcd_info.disk_io
suffix:semicolon
id|value
op_assign
id|leds
op_amp
id|LED_DISK_IO
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|block_ptr
op_assign
op_amp
id|lcd_info.lan_rcv
suffix:semicolon
id|value
op_assign
id|leds
op_amp
id|LED_LAN_RCV
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|block_ptr
op_assign
op_amp
id|lcd_info.lan_tx
suffix:semicolon
id|value
op_assign
id|leds
op_amp
id|LED_LAN_TX
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* should never happen: */
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|last_was_cmd
)paren
(brace
multiline_comment|/* write the value to the LCD data port */
id|gsc_writeb
c_func
(paren
id|value
ques
c_cond
id|block_ptr-&gt;on
suffix:colon
id|block_ptr-&gt;off
comma
id|LCD_DATA_REG
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* write the command-byte to the LCD command register */
id|gsc_writeb
c_func
(paren
id|block_ptr-&gt;command
comma
id|LCD_CMD_REG
)paren
suffix:semicolon
)brace
multiline_comment|/* now update the vars for the next interrupt iteration */
r_if
c_cond
(paren
op_increment
id|last_was_cmd
op_eq
l_int|2
)paren
(brace
multiline_comment|/* switch between cmd &amp; data */
id|last_was_cmd
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|last_index
op_eq
l_int|4
)paren
id|last_index
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* switch back to heartbeat index */
)brace
)brace
multiline_comment|/*&n;   ** &n;   ** led_get_net_stats()&n;   ** &n;   ** calculate the TX- &amp; RX-troughput on the network interfaces in&n;   ** the system for usage in the LED code&n;   **&n;   ** (analog to dev_get_info() from net/core/dev.c)&n;   **   &n; */
DECL|variable|led_net_rx_counter
DECL|variable|led_net_tx_counter
r_static
r_int
r_int
id|led_net_rx_counter
comma
id|led_net_tx_counter
suffix:semicolon
DECL|function|led_get_net_stats
r_static
r_void
id|led_get_net_stats
c_func
(paren
r_int
id|addvalue
)paren
(brace
macro_line|#ifdef CONFIG_NET
r_static
r_int
r_int
id|rx_total_last
comma
id|tx_total_last
suffix:semicolon
r_int
r_int
id|rx_total
comma
id|tx_total
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_struct
id|net_device_stats
op_star
id|stats
suffix:semicolon
id|rx_total
op_assign
id|tx_total
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* we are running as a tasklet, so locking dev_base &n;&t; * for reading should be OK */
id|read_lock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|dev_base
suffix:semicolon
id|dev
op_ne
l_int|NULL
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;get_stats
)paren
(brace
id|stats
op_assign
id|dev
op_member_access_from_pointer
id|get_stats
c_func
(paren
id|dev
)paren
suffix:semicolon
id|rx_total
op_add_assign
id|stats-&gt;rx_packets
suffix:semicolon
id|tx_total
op_add_assign
id|stats-&gt;tx_packets
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
id|rx_total
op_sub_assign
id|rx_total_last
suffix:semicolon
id|tx_total
op_sub_assign
id|tx_total_last
suffix:semicolon
r_if
c_cond
(paren
id|rx_total
)paren
id|led_net_rx_counter
op_add_assign
id|CALC_ADD
c_func
(paren
id|rx_total
comma
id|tx_total
comma
id|addvalue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tx_total
)paren
id|led_net_tx_counter
op_add_assign
id|CALC_ADD
c_func
(paren
id|tx_total
comma
id|rx_total
comma
id|addvalue
)paren
suffix:semicolon
id|rx_total_last
op_add_assign
id|rx_total
suffix:semicolon
id|tx_total_last
op_add_assign
id|tx_total
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n;   ** &n;   ** led_get_diskio_stats()&n;   ** &n;   ** calculate the disk-io througput in the system&n;   ** (analog to linux/fs/proc/proc_misc.c)&n;   **   &n; */
DECL|variable|led_diskio_counter
r_static
r_int
r_int
id|led_diskio_counter
suffix:semicolon
DECL|function|led_get_diskio_stats
r_static
r_void
id|led_get_diskio_stats
c_func
(paren
r_int
id|addvalue
)paren
(brace
r_static
r_int
r_int
id|diskio_total_last
comma
id|diskio_max
suffix:semicolon
r_int
id|major
comma
id|disk
comma
id|total
suffix:semicolon
id|total
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|major
op_assign
l_int|0
suffix:semicolon
id|major
OL
id|DK_MAX_MAJOR
suffix:semicolon
id|major
op_increment
)paren
(brace
r_for
c_loop
(paren
id|disk
op_assign
l_int|0
suffix:semicolon
id|disk
OL
id|DK_MAX_DISK
suffix:semicolon
id|disk
op_increment
)paren
id|total
op_add_assign
id|kstat.dk_drive
(braket
id|major
)braket
(braket
id|disk
)braket
suffix:semicolon
)brace
id|total
op_sub_assign
id|diskio_total_last
suffix:semicolon
r_if
c_cond
(paren
id|total
)paren
(brace
r_if
c_cond
(paren
id|total
op_ge
id|diskio_max
)paren
(brace
id|led_diskio_counter
op_add_assign
id|addvalue
suffix:semicolon
id|diskio_max
op_assign
id|total
suffix:semicolon
multiline_comment|/* new maximum value found */
)brace
r_else
id|led_diskio_counter
op_add_assign
id|CALC_ADD
c_func
(paren
id|total
comma
id|diskio_max
comma
id|addvalue
)paren
suffix:semicolon
)brace
id|diskio_total_last
op_add_assign
id|total
suffix:semicolon
)brace
multiline_comment|/*&n;   ** led_tasklet_func()&n;   ** &n;   ** is scheduled at every timer interrupt from time.c and&n;   ** updates the chassis LCD/LED &n;&n;    TODO:&n;    - display load average (older machines like 715/64 have 4 &quot;free&quot; LED&squot;s for that)&n;    - optimizations&n; */
DECL|variable|currentleds
r_static
r_int
r_char
id|currentleds
suffix:semicolon
multiline_comment|/* stores current value of the LEDs */
DECL|macro|HEARTBEAT_LEN
mdefine_line|#define HEARTBEAT_LEN (HZ*6/100)
DECL|macro|HEARTBEAT_2ND_RANGE_START
mdefine_line|#define HEARTBEAT_2ND_RANGE_START (HZ*22/100)
DECL|macro|HEARTBEAT_2ND_RANGE_END
mdefine_line|#define HEARTBEAT_2ND_RANGE_END   (HEARTBEAT_2ND_RANGE_START + HEARTBEAT_LEN)
DECL|function|led_tasklet_func
r_static
r_void
id|led_tasklet_func
c_func
(paren
r_int
r_int
id|unused
)paren
(brace
r_static
r_int
r_int
id|count
comma
id|count_HZ
suffix:semicolon
r_static
r_int
r_char
id|lastleds
suffix:semicolon
multiline_comment|/* exit if not initialized */
r_if
c_cond
(paren
op_logical_neg
id|led_func_ptr
)paren
r_return
suffix:semicolon
multiline_comment|/* increment the local counters */
op_increment
id|count
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|count_HZ
op_eq
id|HZ
)paren
id|count_HZ
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|led_heartbeat
)paren
(brace
multiline_comment|/* flash heartbeat-LED like a real heart (2 x short then a long delay) */
r_if
c_cond
(paren
id|count_HZ
OL
id|HEARTBEAT_LEN
op_logical_or
(paren
id|count_HZ
op_ge
id|HEARTBEAT_2ND_RANGE_START
op_logical_and
id|count_HZ
OL
id|HEARTBEAT_2ND_RANGE_END
)paren
)paren
id|currentleds
op_or_assign
id|LED_HEARTBEAT
suffix:semicolon
r_else
id|currentleds
op_and_assign
op_complement
id|LED_HEARTBEAT
suffix:semicolon
)brace
multiline_comment|/* gather network and diskio statistics and flash LEDs respectively */
r_if
c_cond
(paren
id|led_lanrxtx
)paren
(brace
r_if
c_cond
(paren
(paren
id|count
op_amp
l_int|31
)paren
op_eq
l_int|0
)paren
id|led_get_net_stats
c_func
(paren
l_int|30
)paren
suffix:semicolon
r_if
c_cond
(paren
id|led_net_rx_counter
)paren
(brace
id|led_net_rx_counter
op_decrement
suffix:semicolon
id|currentleds
op_or_assign
id|LED_LAN_RCV
suffix:semicolon
)brace
r_else
id|currentleds
op_and_assign
op_complement
id|LED_LAN_RCV
suffix:semicolon
r_if
c_cond
(paren
id|led_net_tx_counter
)paren
(brace
id|led_net_tx_counter
op_decrement
suffix:semicolon
id|currentleds
op_or_assign
id|LED_LAN_TX
suffix:semicolon
)brace
r_else
id|currentleds
op_and_assign
op_complement
id|LED_LAN_TX
suffix:semicolon
)brace
r_if
c_cond
(paren
id|led_diskio
)paren
(brace
multiline_comment|/* avoid to calculate diskio-stats at same irq as netio-stats ! */
r_if
c_cond
(paren
(paren
id|count
op_amp
l_int|31
)paren
op_eq
l_int|15
)paren
id|led_get_diskio_stats
c_func
(paren
l_int|30
)paren
suffix:semicolon
r_if
c_cond
(paren
id|led_diskio_counter
)paren
(brace
id|led_diskio_counter
op_decrement
suffix:semicolon
id|currentleds
op_or_assign
id|LED_DISK_IO
suffix:semicolon
)brace
r_else
id|currentleds
op_and_assign
op_complement
id|LED_DISK_IO
suffix:semicolon
)brace
multiline_comment|/* update the LCD/LEDs */
r_if
c_cond
(paren
id|currentleds
op_ne
id|lastleds
)paren
(brace
id|led_func_ptr
c_func
(paren
id|currentleds
)paren
suffix:semicolon
id|lastleds
op_assign
id|currentleds
suffix:semicolon
)brace
)brace
multiline_comment|/* main led tasklet struct (scheduled from time.c) */
id|DECLARE_TASKLET_DISABLED
c_func
(paren
id|led_tasklet
comma
id|led_tasklet_func
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;   ** led_halt()&n;   ** &n;   ** called by the reboot notifier chain at shutdown and stops all&n;   ** LED/LCD activities.&n;   ** &n; */
r_static
r_int
id|led_halt
c_func
(paren
r_struct
id|notifier_block
op_star
comma
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
DECL|variable|led_notifier
r_static
r_struct
id|notifier_block
id|led_notifier
op_assign
(brace
id|notifier_call
suffix:colon
id|led_halt
comma
)brace
suffix:semicolon
DECL|function|led_halt
r_static
r_int
id|led_halt
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
comma
r_int
r_int
id|event
comma
r_void
op_star
id|buf
)paren
(brace
r_char
op_star
id|txt
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|SYS_RESTART
suffix:colon
id|txt
op_assign
l_string|&quot;SYSTEM RESTART&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYS_HALT
suffix:colon
id|txt
op_assign
l_string|&quot;SYSTEM HALT&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYS_POWER_OFF
suffix:colon
id|txt
op_assign
l_string|&quot;SYSTEM POWER OFF&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
multiline_comment|/* completely stop the LED/LCD tasklet */
id|tasklet_disable
c_func
(paren
op_amp
id|led_tasklet
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lcd_info.model
op_eq
id|DISPLAY_MODEL_LCD
)paren
id|lcd_print
c_func
(paren
id|txt
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|led_func_ptr
)paren
id|led_func_ptr
c_func
(paren
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* turn all LEDs ON */
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|led_notifier
)paren
suffix:semicolon
r_return
id|NOTIFY_OK
suffix:semicolon
)brace
multiline_comment|/*&n;   ** register_led_driver()&n;   ** &n;   ** registers an external LED or LCD for usage by this driver.&n;   ** currently only LCD-, LASI- and ASP-style LCD/LED&squot;s are supported.&n;   ** &n; */
DECL|function|register_led_driver
r_int
id|__init
id|register_led_driver
c_func
(paren
r_int
id|model
comma
r_char
op_star
id|cmd_reg
comma
r_char
op_star
id|data_reg
)paren
(brace
r_static
r_int
id|initialized
suffix:semicolon
r_if
c_cond
(paren
id|initialized
op_logical_or
op_logical_neg
id|data_reg
)paren
r_return
l_int|1
suffix:semicolon
id|lcd_info.model
op_assign
id|model
suffix:semicolon
multiline_comment|/* store the values */
id|LCD_CMD_REG
op_assign
(paren
id|cmd_reg
op_eq
id|LED_CMD_REG_NONE
)paren
ques
c_cond
l_int|NULL
suffix:colon
id|cmd_reg
suffix:semicolon
r_switch
c_cond
(paren
id|lcd_info.model
)paren
(brace
r_case
id|DISPLAY_MODEL_LCD
suffix:colon
id|LCD_DATA_REG
op_assign
id|data_reg
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;LCD display at %p,%p registered&bslash;n&quot;
comma
id|LCD_CMD_REG
comma
id|LCD_DATA_REG
)paren
suffix:semicolon
id|led_func_ptr
op_assign
id|led_LCD_driver
suffix:semicolon
id|lcd_print
c_func
(paren
l_string|&quot;Linux &quot;
id|UTS_RELEASE
)paren
suffix:semicolon
id|led_type
op_assign
id|LED_HASLCD
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DISPLAY_MODEL_LASI
suffix:colon
id|LED_DATA_REG
op_assign
id|data_reg
suffix:semicolon
id|led_func_ptr
op_assign
id|led_LASI_driver
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;LED display at %p registered&bslash;n&quot;
comma
id|LED_DATA_REG
)paren
suffix:semicolon
id|led_type
op_assign
id|LED_NOLCD
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DISPLAY_MODEL_OLD_ASP
suffix:colon
id|LED_DATA_REG
op_assign
id|data_reg
suffix:semicolon
id|led_func_ptr
op_assign
id|led_ASP_driver
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;LED (ASP-style) display at %p registered&bslash;n&quot;
comma
id|LED_DATA_REG
)paren
suffix:semicolon
id|led_type
op_assign
id|LED_NOLCD
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Wrong LCD/LED model %d !&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|lcd_info.model
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* mark the LCD/LED driver now as initialized and &n;&t; * register to the reboot notifier chain */
id|initialized
op_increment
suffix:semicolon
id|register_reboot_notifier
c_func
(paren
op_amp
id|led_notifier
)paren
suffix:semicolon
multiline_comment|/* start the led tasklet for the first time */
id|tasklet_enable
c_func
(paren
op_amp
id|led_tasklet
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;   ** register_led_regions()&n;   ** &n;   ** register_led_regions() registers the LCD/LED regions for /procfs.&n;   ** At bootup - where the initialisation of the LCD/LED normally happens - &n;   ** not all internal structures of request_region() are properly set up,&n;   ** so that we delay the led-registration until after busdevices_init() &n;   ** has been executed.&n;   **&n; */
DECL|function|register_led_regions
r_void
id|__init
id|register_led_regions
c_func
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|lcd_info.model
)paren
(brace
r_case
id|DISPLAY_MODEL_LCD
suffix:colon
id|request_mem_region
c_func
(paren
(paren
r_int
r_int
)paren
id|LCD_CMD_REG
comma
l_int|1
comma
l_string|&quot;lcd_cmd&quot;
)paren
suffix:semicolon
id|request_mem_region
c_func
(paren
(paren
r_int
r_int
)paren
id|LCD_DATA_REG
comma
l_int|1
comma
l_string|&quot;lcd_data&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DISPLAY_MODEL_LASI
suffix:colon
r_case
id|DISPLAY_MODEL_OLD_ASP
suffix:colon
id|request_mem_region
c_func
(paren
(paren
r_int
r_int
)paren
id|LED_DATA_REG
comma
l_int|1
comma
l_string|&quot;led_data&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;   ** &n;   ** lcd_print()&n;   ** &n;   ** Displays the given string on the LCD-Display of newer machines.&n;   ** lcd_print() disables the timer-based led tasklet during its &n;   ** execution and enables it afterwards again.&n;   **&n; */
DECL|function|lcd_print
r_int
id|lcd_print
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|led_func_ptr
op_logical_or
id|lcd_info.model
op_ne
id|DISPLAY_MODEL_LCD
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* temporarily disable the led tasklet */
id|tasklet_disable
c_func
(paren
op_amp
id|led_tasklet
)paren
suffix:semicolon
multiline_comment|/* copy display string to buffer for procfs */
id|strncpy
c_func
(paren
id|lcd_text
comma
id|str
comma
r_sizeof
(paren
id|lcd_text
)paren
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Set LCD Cursor to 1st character */
id|gsc_writeb
c_func
(paren
id|lcd_info.reset_cmd1
comma
id|LCD_CMD_REG
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|lcd_info.min_cmd_delay
)paren
suffix:semicolon
multiline_comment|/* Print the string */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|lcd_info.lcd_width
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|str
op_logical_and
op_star
id|str
)paren
id|gsc_writeb
c_func
(paren
op_star
id|str
op_increment
comma
id|LCD_DATA_REG
)paren
suffix:semicolon
r_else
id|gsc_writeb
c_func
(paren
l_char|&squot; &squot;
comma
id|LCD_DATA_REG
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|lcd_info.min_cmd_delay
)paren
suffix:semicolon
)brace
multiline_comment|/* re-enable the led tasklet */
id|tasklet_enable
c_func
(paren
op_amp
id|led_tasklet
)paren
suffix:semicolon
r_return
id|lcd_info.lcd_width
suffix:semicolon
)brace
multiline_comment|/*&n;   ** led_init()&n;   ** &n;   ** led_init() is called very early in the bootup-process from setup.c &n;   ** and asks the PDC for an usable chassis LCD or LED.&n;   ** If the PDC doesn&squot;t return any info, then the LED&n;   ** is detected by lasi.c or asp.c and registered with the&n;   ** above functions lasi_led_init() or asp_led_init().&n;   ** KittyHawk machines have often a buggy PDC, so that&n;   ** we explicitly check for those machines here.&n; */
DECL|function|led_init
r_int
id|__init
id|led_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|pdc_chassis_info
id|chassis_info
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* Work around the buggy PDC of KittyHawk-machines */
r_switch
c_cond
(paren
id|CPU_HVERSION
)paren
(brace
r_case
l_int|0x580
suffix:colon
multiline_comment|/* KittyHawk DC2-100 (K100) */
r_case
l_int|0x581
suffix:colon
multiline_comment|/* KittyHawk DC3-120 (K210) */
r_case
l_int|0x582
suffix:colon
multiline_comment|/* KittyHawk DC3 100 (K400) */
r_case
l_int|0x583
suffix:colon
multiline_comment|/* KittyHawk DC3 120 (K410) */
r_case
l_int|0x58B
suffix:colon
multiline_comment|/* KittyHawk DC2 100 (K200) */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: KittyHawk-Machine (hversion 0x%x) found, &quot;
l_string|&quot;LED detection skipped.&bslash;n&quot;
comma
id|__FILE__
comma
id|CPU_HVERSION
)paren
suffix:semicolon
r_goto
id|found
suffix:semicolon
multiline_comment|/* use the preinitialized values of lcd_info */
)brace
multiline_comment|/* initialize the struct, so that we can check for valid return values */
id|lcd_info.model
op_assign
id|DISPLAY_MODEL_NONE
suffix:semicolon
id|chassis_info.actcnt
op_assign
id|chassis_info.maxcnt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|pdc_chassis_info
c_func
(paren
op_amp
id|chassis_info
comma
op_amp
id|lcd_info
comma
r_sizeof
(paren
id|lcd_info
)paren
)paren
)paren
op_eq
id|PDC_OK
)paren
(brace
id|DPRINTK
c_func
(paren
(paren
id|KERN_INFO
l_string|&quot;%s: chassis info: model=%d (%s), &quot;
l_string|&quot;lcd_width=%d, cmd_delay=%u,&bslash;n&quot;
l_string|&quot;%s: sizecnt=%d, actcnt=%ld, maxcnt=%ld&bslash;n&quot;
comma
id|__FILE__
comma
id|lcd_info.model
comma
(paren
id|lcd_info.model
op_eq
id|DISPLAY_MODEL_LCD
)paren
ques
c_cond
l_string|&quot;LCD&quot;
suffix:colon
(paren
id|lcd_info.model
op_eq
id|DISPLAY_MODEL_LASI
)paren
ques
c_cond
l_string|&quot;LED&quot;
suffix:colon
l_string|&quot;unknown&quot;
comma
id|lcd_info.lcd_width
comma
id|lcd_info.min_cmd_delay
comma
id|__FILE__
comma
r_sizeof
(paren
id|lcd_info
)paren
comma
id|chassis_info.actcnt
comma
id|chassis_info.maxcnt
)paren
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
id|KERN_INFO
l_string|&quot;%s: cmd=%p, data=%p, reset1=%x, reset2=%x, act_enable=%d&bslash;n&quot;
comma
id|__FILE__
comma
id|lcd_info.lcd_cmd_reg_addr
comma
id|lcd_info.lcd_data_reg_addr
comma
id|lcd_info.reset_cmd1
comma
id|lcd_info.reset_cmd2
comma
id|lcd_info.act_enable
)paren
)paren
suffix:semicolon
multiline_comment|/* check the results. Some machines have a buggy PDC */
r_if
c_cond
(paren
id|chassis_info.actcnt
op_le
l_int|0
op_logical_or
id|chassis_info.actcnt
op_ne
id|chassis_info.maxcnt
)paren
r_goto
id|not_found
suffix:semicolon
r_switch
c_cond
(paren
id|lcd_info.model
)paren
(brace
r_case
id|DISPLAY_MODEL_LCD
suffix:colon
multiline_comment|/* LCD display */
r_if
c_cond
(paren
id|chassis_info.actcnt
OL
m_offsetof
(paren
r_struct
id|pdc_chassis_lcd_info_ret_block
comma
id|_pad
)paren
op_minus
l_int|1
)paren
r_goto
id|not_found
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lcd_info.act_enable
)paren
(brace
id|DPRINTK
c_func
(paren
(paren
id|KERN_INFO
l_string|&quot;PDC prohibited usage of the LCD.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|not_found
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|DISPLAY_MODEL_NONE
suffix:colon
multiline_comment|/* no LED or LCD available */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PDC reported no LCD or LED.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|not_found
suffix:semicolon
r_case
id|DISPLAY_MODEL_LASI
suffix:colon
multiline_comment|/* Lasi style 8 bit LED display */
r_if
c_cond
(paren
id|chassis_info.actcnt
op_ne
l_int|8
op_logical_and
id|chassis_info.actcnt
op_ne
l_int|32
)paren
r_goto
id|not_found
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PDC reported unknown LCD/LED model %d&bslash;n&quot;
comma
id|lcd_info.model
)paren
suffix:semicolon
r_goto
id|not_found
suffix:semicolon
)brace
multiline_comment|/* switch() */
id|found
suffix:colon
multiline_comment|/* register the LCD/LED driver */
id|register_led_driver
c_func
(paren
id|lcd_info.model
comma
id|LCD_CMD_REG
comma
id|LCD_DATA_REG
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* if() */
id|DPRINTK
c_func
(paren
(paren
id|KERN_INFO
l_string|&quot;pdc_chassis_info call failed with retval = %d&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
)brace
id|not_found
suffix:colon
id|lcd_info.model
op_assign
id|DISPLAY_MODEL_NONE
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
id|module_init
c_func
(paren
id|led_create_procfs
)paren
macro_line|#endif
eof
