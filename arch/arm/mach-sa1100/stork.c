multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/stork.c&n; *&n; *     Copyright (C) 2001 Ken Gordon&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/keyboard.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|macro|STORK_VM_BASE_CS1
mdefine_line|#define STORK_VM_BASE_CS1 0xf0000000&t;&t;/* where we get mapped (virtual) */
DECL|macro|STORK_VM_OFF_CS1
mdefine_line|#define STORK_VM_OFF_CS1 0x08000000             /* where we started mapping (physical) */
DECL|macro|STORK_VM_ADJUST_CS1
mdefine_line|#define STORK_VM_ADJUST_CS1 (STORK_VM_BASE_CS1-STORK_VM_OFF_CS1) /* add to the phys to get virt */
DECL|macro|STORK_VM_BASE_CS2
mdefine_line|#define STORK_VM_BASE_CS2 0xf1000000&t;&t;/* where we get mapped (virtual) */
DECL|macro|STORK_VM_OFF_CS2
mdefine_line|#define STORK_VM_OFF_CS2  0x10000000             /* where we started mapping (physical) */
DECL|macro|STORK_VM_ADJUST_CS2
mdefine_line|#define STORK_VM_ADJUST_CS2 (STORK_VM_BASE_CS2-STORK_VM_OFF_CS2) /* add to the phys to get virt */
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
DECL|variable|storkLatchA
r_static
r_int
id|storkLatchA
op_assign
l_int|0
suffix:semicolon
DECL|variable|storkLatchB
r_static
r_int
id|storkLatchB
op_assign
l_int|0
suffix:semicolon
DECL|variable|storkLCDCPLD
r_static
r_int
id|storkLCDCPLD
(braket
l_int|4
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
DECL|function|storkSetLatchA
id|storkSetLatchA
c_func
(paren
r_int
id|bits
)paren
(brace
r_int
id|ret
op_assign
id|storkLatchA
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|latch
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|STORK_LATCH_A_ADDR
op_plus
id|STORK_VM_ADJUST_CS1
)paren
suffix:semicolon
id|storkLatchA
op_or_assign
id|bits
suffix:semicolon
op_star
id|latch
op_assign
id|storkLatchA
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_int
DECL|function|storkClearLatchA
id|storkClearLatchA
c_func
(paren
r_int
id|bits
)paren
(brace
r_int
id|ret
op_assign
id|storkLatchA
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|latch
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|STORK_LATCH_A_ADDR
op_plus
id|STORK_VM_ADJUST_CS1
)paren
suffix:semicolon
id|storkLatchA
op_and_assign
op_complement
id|bits
suffix:semicolon
op_star
id|latch
op_assign
id|storkLatchA
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_int
DECL|function|storkSetLCDCPLD
id|storkSetLCDCPLD
c_func
(paren
r_int
id|which
comma
r_int
id|bits
)paren
(brace
r_int
id|ret
op_assign
id|storkLCDCPLD
(braket
id|which
)braket
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|latch
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|STORK_LCDCPLD_BASE_ADDR
op_plus
id|STORK_VM_ADJUST_CS2
op_plus
l_int|0x20
op_star
id|which
)paren
suffix:semicolon
id|storkLCDCPLD
(braket
id|which
)braket
op_or_assign
id|bits
suffix:semicolon
op_star
id|latch
op_assign
id|storkLCDCPLD
(braket
id|which
)braket
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* NB we don&squot;t shadow these &squot;cos there is no relation between the data written and the data read */
multiline_comment|/* ie the read registers are read only and the write registers write only */
r_int
DECL|function|storkGetLCDCPLD
id|storkGetLCDCPLD
c_func
(paren
r_int
id|which
)paren
(brace
r_volatile
r_int
r_int
op_star
id|latch
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|STORK_LCDCPLD_BASE_ADDR
op_plus
id|STORK_VM_ADJUST_CS2
op_plus
l_int|0x20
op_star
id|which
)paren
suffix:semicolon
r_return
op_star
id|latch
suffix:semicolon
)brace
r_int
DECL|function|storkClearLCDCPLD
id|storkClearLCDCPLD
c_func
(paren
r_int
id|which
comma
r_int
id|bits
)paren
(brace
r_int
id|ret
op_assign
id|storkLCDCPLD
(braket
id|which
)braket
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|latch
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|STORK_LCDCPLD_BASE_ADDR
op_plus
id|STORK_VM_ADJUST_CS2
op_plus
l_int|0x20
op_star
id|which
)paren
suffix:semicolon
id|storkLCDCPLD
(braket
id|which
)braket
op_and_assign
op_complement
id|bits
suffix:semicolon
op_star
id|latch
op_assign
id|storkLCDCPLD
(braket
id|which
)braket
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_int
DECL|function|storkSetLatchB
id|storkSetLatchB
c_func
(paren
r_int
id|bits
)paren
(brace
r_int
id|ret
op_assign
id|storkLatchB
suffix:semicolon
r_char
id|buf
(braket
l_int|100
)braket
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|latch
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|STORK_LATCH_B_ADDR
op_plus
id|STORK_VM_ADJUST_CS1
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s: bits %04x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|bits
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug
)paren
id|printk
c_func
(paren
id|buf
)paren
suffix:semicolon
id|storkLatchB
op_or_assign
id|bits
suffix:semicolon
op_star
id|latch
op_assign
id|storkLatchB
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_int
DECL|function|storkClearLatchB
id|storkClearLatchB
c_func
(paren
r_int
id|bits
)paren
(brace
r_int
id|ret
op_assign
id|storkLatchB
suffix:semicolon
r_char
id|buf
(braket
l_int|100
)braket
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|latch
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|STORK_LATCH_B_ADDR
op_plus
id|STORK_VM_ADJUST_CS1
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s: bits %04x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|bits
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug
)paren
id|printk
c_func
(paren
id|buf
)paren
suffix:semicolon
id|storkLatchB
op_and_assign
op_complement
id|bits
suffix:semicolon
op_star
id|latch
op_assign
id|storkLatchB
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_void
DECL|function|storkSetGPIO
id|storkSetGPIO
c_func
(paren
r_int
id|bits
)paren
(brace
r_char
id|buf
(braket
l_int|100
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s: bits %04x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|bits
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug
)paren
id|printk
c_func
(paren
id|buf
)paren
suffix:semicolon
id|GPSR
op_assign
id|bits
suffix:semicolon
)brace
r_void
DECL|function|storkClearGPIO
id|storkClearGPIO
c_func
(paren
r_int
id|bits
)paren
(brace
r_char
id|buf
(braket
l_int|100
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s: bits %04x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|bits
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug
)paren
id|printk
c_func
(paren
id|buf
)paren
suffix:semicolon
id|GPCR
op_assign
id|bits
suffix:semicolon
)brace
r_int
DECL|function|storkGetGPIO
id|storkGetGPIO
c_func
(paren
)paren
(brace
r_char
id|buf
(braket
l_int|100
)braket
suffix:semicolon
r_int
id|bits
op_assign
id|GPLR
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s: bits %04x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|bits
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug
)paren
id|printk
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|bits
suffix:semicolon
)brace
multiline_comment|/* this will return the current state of the hardware ANDED with the given bits&n;   so NE =&gt; at least one bit was set, but maybe not all of them! */
r_int
DECL|function|storkTestGPIO
id|storkTestGPIO
c_func
(paren
r_int
id|bits
)paren
(brace
r_int
id|val
op_assign
id|storkGetGPIO
c_func
(paren
)paren
suffix:semicolon
r_char
id|buf
(braket
l_int|100
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s: bits %04x val %04x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|bits
comma
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug
)paren
id|printk
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
(paren
id|val
op_amp
id|bits
)paren
suffix:semicolon
)brace
multiline_comment|/* NB the touch screen and the d to a use the same data and clock out pins */
DECL|function|storkClockTS
r_static
r_void
id|storkClockTS
c_func
(paren
r_void
)paren
(brace
id|storkSetLatchB
c_func
(paren
id|STORK_TOUCH_SCREEN_DCLK
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
multiline_comment|/* hmm wait 200ns (min) - ok this ought to be udelay(1) but that doesn&squot;t get */
multiline_comment|/* consistant values so I&squot;m using 10 (urgh) */
id|storkClearLatchB
c_func
(paren
id|STORK_TOUCH_SCREEN_DCLK
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
r_int
multiline_comment|/* there is always a 12 bit read after the write! */
DECL|function|storkClockByteToTS
id|storkClockByteToTS
c_func
(paren
r_int
id|byte
)paren
(brace
r_int
id|timeout
op_assign
l_int|10000
suffix:semicolon
multiline_comment|/* stuff is meant to happen in 60ns */
r_int
id|bit
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|debug
)paren
id|printk
c_func
(paren
l_string|&quot;storkClockByteToTS: %02x&bslash;n&quot;
comma
id|byte
)paren
suffix:semicolon
id|storkClearLatchB
c_func
(paren
id|STORK_TOUCH_SCREEN_CS
)paren
suffix:semicolon
multiline_comment|/* slect touch screen */
r_while
c_loop
(paren
id|timeout
op_decrement
OG
l_int|0
)paren
r_if
c_cond
(paren
id|storkTestGPIO
c_func
(paren
id|GPIO_STORK_TOUCH_SCREEN_BUSY
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|timeout
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;storkClockBitToTS: GPIO_STORK_TOUCH_SCREEN_BUSY didn&squot;t go low!&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
multiline_comment|/* ignore error for now        return; */
)brace
multiline_comment|/* clock out the given byte */
r_for
c_loop
(paren
id|bit
op_assign
l_int|0x80
suffix:semicolon
id|bit
OG
l_int|0
suffix:semicolon
id|bit
op_assign
id|bit
op_rshift
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
id|bit
op_amp
id|byte
)paren
op_eq
l_int|0
)paren
id|storkClearLatchB
c_func
(paren
id|STORK_TOUCH_SCREEN_DIN
)paren
suffix:semicolon
r_else
id|storkSetLatchB
c_func
(paren
id|STORK_TOUCH_SCREEN_DIN
)paren
suffix:semicolon
id|storkClockTS
c_func
(paren
)paren
suffix:semicolon
)brace
id|storkClockTS
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* will be busy for at a clock  (at least) */
r_for
c_loop
(paren
id|timeout
op_assign
l_int|10000
suffix:semicolon
id|timeout
op_ge
l_int|0
suffix:semicolon
id|timeout
op_decrement
)paren
r_if
c_cond
(paren
id|storkTestGPIO
c_func
(paren
id|GPIO_STORK_TOUCH_SCREEN_BUSY
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|timeout
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;storkClockBitToTS: 2nd GPIO_STORK_TOUCH_SCREEN_BUSY didn&squot;t go low!&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
multiline_comment|/* ignore error for now        return; */
)brace
multiline_comment|/* clock in the result */
r_for
c_loop
(paren
id|bit
op_assign
l_int|0x0800
suffix:semicolon
id|bit
OG
l_int|0
suffix:semicolon
id|bit
op_assign
id|bit
op_rshift
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|storkTestGPIO
c_func
(paren
id|GPIO_STORK_TOUCH_SCREEN_DATA
)paren
)paren
id|result
op_or_assign
id|bit
suffix:semicolon
id|storkClockTS
c_func
(paren
)paren
suffix:semicolon
)brace
id|storkSetLatchB
c_func
(paren
id|STORK_TOUCH_SCREEN_CS
)paren
suffix:semicolon
multiline_comment|/* unselect touch screen */
r_return
id|result
suffix:semicolon
)brace
r_void
DECL|function|storkClockShortToDtoA
id|storkClockShortToDtoA
c_func
(paren
r_int
id|word
)paren
(brace
r_int
id|bit
suffix:semicolon
id|storkClearLatchB
c_func
(paren
id|STORK_DA_CS
)paren
suffix:semicolon
multiline_comment|/* select D to A */
multiline_comment|/* clock out the given byte */
r_for
c_loop
(paren
id|bit
op_assign
l_int|0x8000
suffix:semicolon
id|bit
OG
l_int|0
suffix:semicolon
id|bit
op_assign
id|bit
op_rshift
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
id|bit
op_amp
id|word
)paren
op_eq
l_int|0
)paren
id|storkClearLatchB
c_func
(paren
id|STORK_TOUCH_SCREEN_DIN
)paren
suffix:semicolon
r_else
id|storkSetLatchB
c_func
(paren
id|STORK_TOUCH_SCREEN_DIN
)paren
suffix:semicolon
id|storkClockTS
c_func
(paren
)paren
suffix:semicolon
)brace
id|storkSetLatchB
c_func
(paren
id|STORK_DA_CS
)paren
suffix:semicolon
multiline_comment|/* unselect D to A */
multiline_comment|/* set DTOA#_LOAD low then high (min 20ns) to transfer value to D to A */
id|storkClearLatchB
c_func
(paren
id|STORK_DA_LD
)paren
suffix:semicolon
id|storkSetLatchB
c_func
(paren
id|STORK_DA_LD
)paren
suffix:semicolon
)brace
r_void
DECL|function|storkInitTSandDtoA
id|storkInitTSandDtoA
c_func
(paren
r_void
)paren
(brace
id|storkClearLatchB
c_func
(paren
id|STORK_TOUCH_SCREEN_DCLK
op_or
id|STORK_TOUCH_SCREEN_DIN
)paren
suffix:semicolon
id|storkSetLatchB
c_func
(paren
id|STORK_TOUCH_SCREEN_CS
op_or
id|STORK_DA_CS
op_or
id|STORK_DA_LD
)paren
suffix:semicolon
id|storkClockByteToTS
c_func
(paren
l_int|0xE2
)paren
suffix:semicolon
multiline_comment|/* turn on the reference */
id|storkClockShortToDtoA
c_func
(paren
l_int|0x8D00
)paren
suffix:semicolon
multiline_comment|/* turn on the contrast */
id|storkClockShortToDtoA
c_func
(paren
l_int|0x0A00
)paren
suffix:semicolon
multiline_comment|/* turn on the brightness */
)brace
multiline_comment|/* see asm-arm/keyboard.h - there are a bunch of basically virtual functions required */
multiline_comment|/* we have to fill in for them or else we can&squot;t call handle_scancode when we see a button pressed */
r_static
r_int
DECL|function|stork_kbd_translate
id|stork_kbd_translate
c_func
(paren
r_int
r_char
id|scancode
comma
r_int
r_char
op_star
id|keycode
comma
r_char
id|rawmode
)paren
(brace
r_if
c_cond
(paren
id|keycode
)paren
op_star
id|keycode
op_assign
id|scancode
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_char
DECL|function|stork_kbd_unexpected_up
id|stork_kbd_unexpected_up
c_func
(paren
r_int
r_char
id|code
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|__initdata
r_struct
id|map_desc
id|stork_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      domain     r  w  c  b */
(brace
l_int|0xe8000000
comma
l_int|0x00000000
comma
l_int|0x02000000
comma
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* Flash bank 0 */
(brace
id|STORK_VM_BASE_CS1
comma
id|STORK_VM_OFF_CS1
comma
l_int|0x01000000
comma
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* EGPIO 0 */
(brace
l_int|0xf1000000
comma
l_int|0x10000000
comma
l_int|0x02800000
comma
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* static memory bank 2 */
(brace
l_int|0xf3800000
comma
l_int|0x40000000
comma
l_int|0x00800000
comma
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* static memory bank 4 */
id|LAST_DESC
)brace
suffix:semicolon
r_int
id|__init
DECL|function|stork_map_io
id|stork_map_io
c_func
(paren
r_void
)paren
(brace
id|sa1100_map_io
c_func
(paren
)paren
suffix:semicolon
id|iotable_init
c_func
(paren
id|stork_io_desc
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|0
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* com port */
id|sa1100_register_uart
c_func
(paren
l_int|1
comma
l_int|2
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|2
comma
l_int|3
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Stork driver initing latches&bslash;r&bslash;n&quot;
)paren
suffix:semicolon
id|storkClearLatchB
c_func
(paren
id|STORK_RED_LED
)paren
suffix:semicolon
multiline_comment|/* let&squot;s have the red LED on please */
id|storkSetLatchB
c_func
(paren
id|STORK_YELLOW_LED
)paren
suffix:semicolon
id|storkSetLatchB
c_func
(paren
id|STORK_GREEN_LED
)paren
suffix:semicolon
id|storkSetLatchA
c_func
(paren
id|STORK_BATTERY_CHARGER_ON
)paren
suffix:semicolon
id|storkSetLatchA
c_func
(paren
id|STORK_LCD_5V_POWER_ON
)paren
suffix:semicolon
id|storkSetLatchA
c_func
(paren
id|STORK_LCD_3V3_POWER_ON
)paren
suffix:semicolon
id|storkInitTSandDtoA
c_func
(paren
)paren
suffix:semicolon
id|k_translate
op_assign
id|stork_kbd_translate
suffix:semicolon
id|k_unexpected_up
op_assign
id|stork_kbd_unexpected_up
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|STORK
comma
l_string|&quot;Stork Technologies prototype&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0xc0000000
comma
l_int|0x80000000
comma
l_int|0xf8000000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0xc0000100
)paren
id|MAPIO
c_func
(paren
id|stork_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
id|EXPORT_SYMBOL
c_func
(paren
id|storkTestGPIO
)paren
suffix:semicolon
DECL|variable|EXPORT_SYMBOL
id|EXPORT_SYMBOL
c_func
(paren
id|storkSetGPIO
)paren
suffix:semicolon
DECL|variable|storkClearGPIO
id|EXPORT_SYMBOL
c_func
(paren
id|storkClearGPIO
)paren
suffix:semicolon
DECL|variable|storkSetLatchA
id|EXPORT_SYMBOL
c_func
(paren
id|storkSetLatchA
)paren
suffix:semicolon
DECL|variable|storkClearLatchA
id|EXPORT_SYMBOL
c_func
(paren
id|storkClearLatchA
)paren
suffix:semicolon
DECL|variable|storkSetLatchB
id|EXPORT_SYMBOL
c_func
(paren
id|storkSetLatchB
)paren
suffix:semicolon
DECL|variable|storkClearLatchB
id|EXPORT_SYMBOL
c_func
(paren
id|storkClearLatchB
)paren
suffix:semicolon
DECL|variable|storkClockByteToTS
id|EXPORT_SYMBOL
c_func
(paren
id|storkClockByteToTS
)paren
suffix:semicolon
DECL|variable|storkClockShortToDtoA
id|EXPORT_SYMBOL
c_func
(paren
id|storkClockShortToDtoA
)paren
suffix:semicolon
DECL|variable|storkGetLCDCPLD
id|EXPORT_SYMBOL
c_func
(paren
id|storkGetLCDCPLD
)paren
suffix:semicolon
DECL|variable|storkSetLCDCPLD
id|EXPORT_SYMBOL
c_func
(paren
id|storkSetLCDCPLD
)paren
suffix:semicolon
eof
