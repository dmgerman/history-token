multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2001 Keith M Wesolowski&n; * Copyright (C) 2001 Paul Mundt&n; * Copyright (C) 2003 Guido Guenther &lt;agx@sigxcpu.org&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ds17287rtc.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/wbflush.h&gt;
macro_line|#include &lt;asm/ip32/ip32_ints.h&gt;
DECL|macro|POWERDOWN_TIMEOUT
mdefine_line|#define POWERDOWN_TIMEOUT&t;120
multiline_comment|/*&n; * Blink frequency during reboot grace period and when paniced.&n; */
DECL|macro|POWERDOWN_FREQ
mdefine_line|#define POWERDOWN_FREQ&t;&t;(HZ / 4)
DECL|macro|PANIC_FREQ
mdefine_line|#define PANIC_FREQ&t;&t;(HZ / 8)
DECL|variable|power_timer
DECL|variable|blink_timer
DECL|variable|debounce_timer
r_static
r_struct
id|timer_list
id|power_timer
comma
id|blink_timer
comma
id|debounce_timer
suffix:semicolon
DECL|variable|shuting_down
DECL|variable|has_paniced
r_static
r_int
id|shuting_down
op_assign
l_int|0
comma
id|has_paniced
op_assign
l_int|0
suffix:semicolon
r_static
r_void
id|ip32_machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
r_static
r_void
id|ip32_machine_halt
c_func
(paren
r_void
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
r_static
r_void
id|ip32_machine_power_off
c_func
(paren
r_void
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
DECL|function|ip32_machine_restart
r_static
r_void
id|ip32_machine_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
r_if
c_cond
(paren
id|shuting_down
)paren
id|ip32_machine_power_off
c_func
(paren
)paren
suffix:semicolon
id|ArcReboot
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|ip32_machine_halt
r_static
r_inline
r_void
id|ip32_machine_halt
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|shuting_down
)paren
id|ip32_machine_power_off
c_func
(paren
)paren
suffix:semicolon
id|ArcEnterInteractiveMode
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|ip32_machine_power_off
r_static
r_void
id|ip32_machine_power_off
c_func
(paren
r_void
)paren
(brace
r_volatile
r_int
r_char
id|reg_a
comma
id|xctrl_a
comma
id|xctrl_b
suffix:semicolon
id|disable_irq
c_func
(paren
id|MACEISA_RTC_IRQ
)paren
suffix:semicolon
id|reg_a
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_REG_A
)paren
suffix:semicolon
multiline_comment|/* setup for kickstart &amp; wake-up (DS12287 Ref. Man. p. 19) */
id|reg_a
op_and_assign
op_complement
id|DS_REGA_DV2
suffix:semicolon
id|reg_a
op_or_assign
id|DS_REGA_DV1
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|reg_a
op_or
id|DS_REGA_DV0
comma
id|RTC_REG_A
)paren
suffix:semicolon
id|wbflush
c_func
(paren
)paren
suffix:semicolon
id|xctrl_b
op_assign
id|CMOS_READ
c_func
(paren
id|DS_B1_XCTRL4B
)paren
op_or
id|DS_XCTRL4B_ABE
op_or
id|DS_XCTRL4B_KFE
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|xctrl_b
comma
id|DS_B1_XCTRL4B
)paren
suffix:semicolon
id|xctrl_a
op_assign
id|CMOS_READ
c_func
(paren
id|DS_B1_XCTRL4A
)paren
op_amp
op_complement
id|DS_XCTRL4A_IFS
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|xctrl_a
comma
id|DS_B1_XCTRL4A
)paren
suffix:semicolon
id|wbflush
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* adios amigos... */
id|CMOS_WRITE
c_func
(paren
id|xctrl_a
op_or
id|DS_XCTRL4A_PAB
comma
id|DS_B1_XCTRL4A
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|reg_a
comma
id|RTC_REG_A
)paren
suffix:semicolon
id|wbflush
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Power off!&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|power_timeout
r_static
r_void
id|power_timeout
c_func
(paren
r_int
r_int
id|data
)paren
(brace
id|ip32_machine_power_off
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|blink_timeout
r_static
r_void
id|blink_timeout
c_func
(paren
r_int
r_int
id|data
)paren
(brace
id|u64
id|mc_led
op_assign
id|mace_read_64
c_func
(paren
id|MACEISA_FLASH_NIC_REG
)paren
suffix:semicolon
id|mc_led
op_xor_assign
id|MACEISA_LED_RED
suffix:semicolon
id|mace_write_64
c_func
(paren
id|MACEISA_FLASH_NIC_REG
comma
id|mc_led
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|blink_timer
comma
id|jiffies
op_plus
id|data
)paren
suffix:semicolon
)brace
DECL|function|debounce
r_static
r_void
id|debounce
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_volatile
r_int
r_char
id|reg_a
comma
id|reg_c
comma
id|xctrl_a
suffix:semicolon
id|reg_c
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_INTR_FLAGS
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|reg_a
op_or
id|DS_REGA_DV0
comma
id|RTC_REG_A
)paren
suffix:semicolon
id|wbflush
c_func
(paren
)paren
suffix:semicolon
id|xctrl_a
op_assign
id|CMOS_READ
c_func
(paren
id|DS_B1_XCTRL4A
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|xctrl_a
op_amp
id|DS_XCTRL4A_IFS
)paren
op_logical_or
(paren
id|reg_c
op_amp
id|RTC_IRQF
)paren
)paren
(brace
multiline_comment|/* Interrupt still being sent. */
id|debounce_timer.expires
op_assign
id|jiffies
op_plus
l_int|50
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|debounce_timer
)paren
suffix:semicolon
multiline_comment|/* clear interrupt source */
id|CMOS_WRITE
c_func
(paren
id|xctrl_a
op_amp
op_complement
id|DS_XCTRL4A_IFS
comma
id|DS_B1_XCTRL4A
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|reg_a
op_amp
op_complement
id|DS_REGA_DV0
comma
id|RTC_REG_A
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|CMOS_WRITE
c_func
(paren
id|reg_a
op_amp
op_complement
id|DS_REGA_DV0
comma
id|RTC_REG_A
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_paniced
)paren
id|ArcReboot
c_func
(paren
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
id|MACEISA_RTC_IRQ
)paren
suffix:semicolon
)brace
DECL|function|ip32_power_button
r_static
r_inline
r_void
id|ip32_power_button
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|has_paniced
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|shuting_down
op_logical_or
id|kill_proc
c_func
(paren
l_int|1
comma
id|SIGINT
comma
l_int|1
)paren
)paren
(brace
multiline_comment|/* No init process or button pressed twice.  */
id|ip32_machine_power_off
c_func
(paren
)paren
suffix:semicolon
)brace
id|shuting_down
op_assign
l_int|1
suffix:semicolon
id|blink_timer.data
op_assign
id|POWERDOWN_FREQ
suffix:semicolon
id|blink_timeout
c_func
(paren
id|POWERDOWN_FREQ
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|power_timer
)paren
suffix:semicolon
id|power_timer.function
op_assign
id|power_timeout
suffix:semicolon
id|power_timer.expires
op_assign
id|jiffies
op_plus
id|POWERDOWN_TIMEOUT
op_star
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|power_timer
)paren
suffix:semicolon
)brace
DECL|function|ip32_rtc_int
r_static
id|irqreturn_t
id|ip32_rtc_int
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_volatile
r_int
r_char
id|reg_c
suffix:semicolon
id|reg_c
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_INTR_FLAGS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg_c
op_amp
id|RTC_IRQF
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: RTC IRQ without RTC_IRQF&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
multiline_comment|/* Wait until interrupt goes away */
id|disable_irq
c_func
(paren
id|MACEISA_RTC_IRQ
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|debounce_timer
)paren
suffix:semicolon
id|debounce_timer.function
op_assign
id|debounce
suffix:semicolon
id|debounce_timer.expires
op_assign
id|jiffies
op_plus
l_int|50
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|debounce_timer
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Power button pressed&bslash;n&quot;
)paren
suffix:semicolon
id|ip32_power_button
c_func
(paren
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|panic_event
r_static
r_int
id|panic_event
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
)paren
(brace
id|u64
id|mc_led
suffix:semicolon
r_if
c_cond
(paren
id|has_paniced
)paren
r_return
id|NOTIFY_DONE
suffix:semicolon
id|has_paniced
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* turn off the green LED */
id|mc_led
op_assign
id|mace_read_64
c_func
(paren
id|MACEISA_FLASH_NIC_REG
)paren
suffix:semicolon
id|mc_led
op_or_assign
id|MACEISA_LED_GREEN
suffix:semicolon
id|mace_write_64
c_func
(paren
id|MACEISA_FLASH_NIC_REG
comma
id|mc_led
)paren
suffix:semicolon
id|blink_timer.data
op_assign
id|PANIC_FREQ
suffix:semicolon
id|blink_timeout
c_func
(paren
id|PANIC_FREQ
)paren
suffix:semicolon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|panic_block
r_static
r_struct
id|notifier_block
id|panic_block
op_assign
(brace
dot
id|notifier_call
op_assign
id|panic_event
comma
)brace
suffix:semicolon
DECL|function|ip32_reboot_setup
r_static
id|__init
r_int
id|ip32_reboot_setup
c_func
(paren
r_void
)paren
(brace
id|u64
id|mc_led
op_assign
id|mace_read_64
c_func
(paren
id|MACEISA_FLASH_NIC_REG
)paren
suffix:semicolon
id|_machine_restart
op_assign
id|ip32_machine_restart
suffix:semicolon
id|_machine_halt
op_assign
id|ip32_machine_halt
suffix:semicolon
id|_machine_power_off
op_assign
id|ip32_machine_power_off
suffix:semicolon
id|request_irq
c_func
(paren
id|MACEISA_RTC_IRQ
comma
id|ip32_rtc_int
comma
l_int|0
comma
l_string|&quot;rtc&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|blink_timer
)paren
suffix:semicolon
id|blink_timer.function
op_assign
id|blink_timeout
suffix:semicolon
id|notifier_chain_register
c_func
(paren
op_amp
id|panic_notifier_list
comma
op_amp
id|panic_block
)paren
suffix:semicolon
multiline_comment|/* turn on the green led only */
id|mc_led
op_or_assign
id|MACEISA_LED_RED
suffix:semicolon
id|mc_led
op_and_assign
op_complement
id|MACEISA_LED_GREEN
suffix:semicolon
id|mace_write_64
c_func
(paren
id|MACEISA_FLASH_NIC_REG
comma
id|mc_led
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ip32_reboot_setup
id|subsys_initcall
c_func
(paren
id|ip32_reboot_setup
)paren
suffix:semicolon
eof
