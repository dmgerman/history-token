multiline_comment|/*&n; *  Touchscreen driver for Sharp Corgi models (SL-C7xx)&n; *&n; *  Copyright (c) 2004-2005 Richard Purdie&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License version 2 as&n; *  published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/arch/corgi.h&gt;
macro_line|#include &lt;asm/arch/hardware.h&gt;
macro_line|#include &lt;asm/arch/pxa-regs.h&gt;
DECL|macro|PWR_MODE_ACTIVE
mdefine_line|#define PWR_MODE_ACTIVE&t;&t;0
DECL|macro|PWR_MODE_SUSPEND
mdefine_line|#define PWR_MODE_SUSPEND &t;1
DECL|macro|X_AXIS_MAX
mdefine_line|#define X_AXIS_MAX&t;&t;3830
DECL|macro|X_AXIS_MIN
mdefine_line|#define X_AXIS_MIN&t;&t;150
DECL|macro|Y_AXIS_MAX
mdefine_line|#define Y_AXIS_MAX&t;&t;3830
DECL|macro|Y_AXIS_MIN
mdefine_line|#define Y_AXIS_MIN&t;&t;190
DECL|macro|PRESSURE_MIN
mdefine_line|#define PRESSURE_MIN&t;0
DECL|macro|PRESSURE_MAX
mdefine_line|#define PRESSURE_MAX&t;15000
DECL|struct|ts_event
r_struct
id|ts_event
(brace
DECL|member|pressure
r_int
id|pressure
suffix:semicolon
DECL|member|x
r_int
id|x
suffix:semicolon
DECL|member|y
r_int
id|y
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|corgi_ts
r_struct
id|corgi_ts
(brace
DECL|member|phys
r_char
id|phys
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|input
r_struct
id|input_dev
id|input
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|tc
r_struct
id|ts_event
id|tc
suffix:semicolon
DECL|member|pendown
r_int
id|pendown
suffix:semicolon
DECL|member|power_mode
r_int
id|power_mode
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|STATUS_HSYNC
mdefine_line|#define STATUS_HSYNC &t;&t;(GPLR(CORGI_GPIO_HSYNC) &amp; GPIO_bit(CORGI_GPIO_HSYNC))
DECL|macro|SyncHS
mdefine_line|#define SyncHS()&t;while((STATUS_HSYNC) == 0); while((STATUS_HSYNC) != 0);
DECL|macro|CCNT
mdefine_line|#define CCNT(a)&t;&t;asm volatile (&quot;mrc p14, 0, %0, C1, C0, 0&quot; : &quot;=r&quot;(a))
DECL|macro|CCNT_ON
mdefine_line|#define CCNT_ON()&t;{int pmnc = 1; asm volatile (&quot;mcr p14, 0, %0, C0, C0, 0&quot; : : &quot;r&quot;(pmnc));}
DECL|macro|CCNT_OFF
mdefine_line|#define CCNT_OFF()&t;{int pmnc = 0; asm volatile (&quot;mcr p14, 0, %0, C0, C0, 0&quot; : : &quot;r&quot;(pmnc));}
DECL|macro|WAIT_HS_400_VGA
mdefine_line|#define WAIT_HS_400_VGA&t;&t;7013U&t;
singleline_comment|// 17.615us
DECL|macro|WAIT_HS_400_QVGA
mdefine_line|#define WAIT_HS_400_QVGA&t;16622U&t;
singleline_comment|// 41.750us
multiline_comment|/* ADS7846 Touch Screen Controller bit definitions */
DECL|macro|ADSCTRL_PD0
mdefine_line|#define ADSCTRL_PD0&t;&t;(1u &lt;&lt; 0)&t;/* PD0 */
DECL|macro|ADSCTRL_PD1
mdefine_line|#define ADSCTRL_PD1&t;&t;(1u &lt;&lt; 1)&t;/* PD1 */
DECL|macro|ADSCTRL_DFR
mdefine_line|#define ADSCTRL_DFR&t;&t;(1u &lt;&lt; 2)&t;/* SER/DFR */
DECL|macro|ADSCTRL_MOD
mdefine_line|#define ADSCTRL_MOD&t;&t;(1u &lt;&lt; 3)&t;/* Mode */
DECL|macro|ADSCTRL_ADR_SH
mdefine_line|#define ADSCTRL_ADR_SH&t;4&t;/* Address setting */
DECL|macro|ADSCTRL_STS
mdefine_line|#define ADSCTRL_STS&t;&t;(1u &lt;&lt; 7)&t;/* Start Bit */
multiline_comment|/* External Functions */
r_extern
r_int
id|w100fb_get_xres
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|w100fb_get_blanking
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|w100fb_get_fastsysclk
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_clk_frequency_khz
c_func
(paren
r_int
id|info
)paren
suffix:semicolon
DECL|function|calc_waittime
r_static
r_int
r_int
id|calc_waittime
c_func
(paren
r_void
)paren
(brace
r_int
id|w100fb_xres
op_assign
id|w100fb_get_xres
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|waittime
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|w100fb_xres
op_eq
l_int|480
op_logical_or
id|w100fb_xres
op_eq
l_int|640
)paren
(brace
id|waittime
op_assign
id|WAIT_HS_400_VGA
op_star
id|get_clk_frequency_khz
c_func
(paren
l_int|0
)paren
op_div
l_int|398131U
suffix:semicolon
r_if
c_cond
(paren
id|w100fb_get_fastsysclk
c_func
(paren
)paren
op_eq
l_int|100
)paren
id|waittime
op_assign
id|waittime
op_star
l_int|75
op_div
l_int|100
suffix:semicolon
r_if
c_cond
(paren
id|w100fb_xres
op_eq
l_int|640
)paren
id|waittime
op_assign
id|waittime
op_star
l_int|3
suffix:semicolon
r_return
id|waittime
suffix:semicolon
)brace
r_return
id|WAIT_HS_400_QVGA
op_star
id|get_clk_frequency_khz
c_func
(paren
l_int|0
)paren
op_div
l_int|398131U
suffix:semicolon
)brace
DECL|function|sync_receive_data_send_cmd
r_static
r_int
id|sync_receive_data_send_cmd
c_func
(paren
r_int
id|doRecive
comma
r_int
id|doSend
comma
r_int
r_int
id|address
comma
r_int
r_int
id|wait_time
)paren
(brace
r_int
id|pos
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|timer1
op_assign
l_int|0
comma
id|timer2
suffix:semicolon
r_int
id|dosleep
suffix:semicolon
id|dosleep
op_assign
op_logical_neg
id|w100fb_get_blanking
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dosleep
op_logical_and
id|doSend
)paren
(brace
id|CCNT_ON
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* polling HSync */
id|SyncHS
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* get CCNT */
id|CCNT
c_func
(paren
id|timer1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|doRecive
)paren
id|pos
op_assign
id|corgi_ssp_ads7846_get
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|doSend
)paren
(brace
r_int
id|cmd
op_assign
id|ADSCTRL_PD0
op_or
id|ADSCTRL_PD1
op_or
(paren
id|address
op_lshift
id|ADSCTRL_ADR_SH
)paren
op_or
id|ADSCTRL_STS
suffix:semicolon
multiline_comment|/* dummy command */
id|corgi_ssp_ads7846_put
c_func
(paren
id|cmd
)paren
suffix:semicolon
id|corgi_ssp_ads7846_get
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dosleep
)paren
(brace
multiline_comment|/* Wait after HSync */
id|CCNT
c_func
(paren
id|timer2
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|timer2
op_minus
id|timer1
)paren
OG
id|wait_time
)paren
(brace
multiline_comment|/* timeout */
id|SyncHS
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* get OSCR */
id|CCNT
c_func
(paren
id|timer1
)paren
suffix:semicolon
multiline_comment|/* Wait after HSync */
id|CCNT
c_func
(paren
id|timer2
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|timer2
op_minus
id|timer1
)paren
OL
id|wait_time
)paren
(brace
id|CCNT
c_func
(paren
id|timer2
)paren
suffix:semicolon
)brace
)brace
id|corgi_ssp_ads7846_put
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dosleep
)paren
id|CCNT_OFF
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|pos
suffix:semicolon
)brace
DECL|function|read_xydata
r_static
r_int
id|read_xydata
c_func
(paren
r_struct
id|corgi_ts
op_star
id|corgi_ts
)paren
(brace
r_int
r_int
id|x
comma
id|y
comma
id|z1
comma
id|z2
suffix:semicolon
r_int
r_int
id|flags
comma
id|wait_time
suffix:semicolon
multiline_comment|/* critical section */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|corgi_ssp_ads7846_lock
c_func
(paren
)paren
suffix:semicolon
id|wait_time
op_assign
id|calc_waittime
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Y-axis */
id|sync_receive_data_send_cmd
c_func
(paren
l_int|0
comma
l_int|1
comma
l_int|1u
comma
id|wait_time
)paren
suffix:semicolon
multiline_comment|/* Y-axis */
id|sync_receive_data_send_cmd
c_func
(paren
l_int|1
comma
l_int|1
comma
l_int|1u
comma
id|wait_time
)paren
suffix:semicolon
multiline_comment|/* X-axis */
id|y
op_assign
id|sync_receive_data_send_cmd
c_func
(paren
l_int|1
comma
l_int|1
comma
l_int|5u
comma
id|wait_time
)paren
suffix:semicolon
multiline_comment|/* Z1 */
id|x
op_assign
id|sync_receive_data_send_cmd
c_func
(paren
l_int|1
comma
l_int|1
comma
l_int|3u
comma
id|wait_time
)paren
suffix:semicolon
multiline_comment|/* Z2 */
id|z1
op_assign
id|sync_receive_data_send_cmd
c_func
(paren
l_int|1
comma
l_int|1
comma
l_int|4u
comma
id|wait_time
)paren
suffix:semicolon
id|z2
op_assign
id|sync_receive_data_send_cmd
c_func
(paren
l_int|1
comma
l_int|0
comma
l_int|4u
comma
id|wait_time
)paren
suffix:semicolon
multiline_comment|/* Power-Down Enable */
id|corgi_ssp_ads7846_put
c_func
(paren
(paren
l_int|1u
op_lshift
id|ADSCTRL_ADR_SH
)paren
op_or
id|ADSCTRL_STS
)paren
suffix:semicolon
id|corgi_ssp_ads7846_get
c_func
(paren
)paren
suffix:semicolon
id|corgi_ssp_ads7846_unlock
c_func
(paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|x
op_eq
l_int|0
)paren
op_logical_or
(paren
id|y
op_eq
l_int|0
)paren
op_logical_or
(paren
id|z1
op_eq
l_int|0
)paren
op_logical_or
(paren
(paren
id|x
op_star
(paren
id|z2
op_minus
id|z1
)paren
op_div
id|z1
)paren
op_ge
l_int|15000
)paren
)paren
(brace
id|corgi_ts-&gt;tc.pressure
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|corgi_ts-&gt;tc.x
op_assign
id|x
suffix:semicolon
id|corgi_ts-&gt;tc.y
op_assign
id|y
suffix:semicolon
id|corgi_ts-&gt;tc.pressure
op_assign
(paren
id|x
op_star
(paren
id|z2
op_minus
id|z1
)paren
)paren
op_div
id|z1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|new_data
r_static
r_void
id|new_data
c_func
(paren
r_struct
id|corgi_ts
op_star
id|corgi_ts
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
id|corgi_ts-&gt;power_mode
op_ne
id|PWR_MODE_ACTIVE
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|corgi_ts-&gt;tc.pressure
op_logical_and
id|corgi_ts-&gt;pendown
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|regs
)paren
id|input_regs
c_func
(paren
op_amp
id|corgi_ts-&gt;input
comma
id|regs
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
op_amp
id|corgi_ts-&gt;input
comma
id|ABS_X
comma
id|corgi_ts-&gt;tc.x
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
op_amp
id|corgi_ts-&gt;input
comma
id|ABS_Y
comma
id|corgi_ts-&gt;tc.y
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
op_amp
id|corgi_ts-&gt;input
comma
id|ABS_PRESSURE
comma
id|corgi_ts-&gt;tc.pressure
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
op_amp
id|corgi_ts-&gt;input
comma
id|BTN_TOUCH
comma
(paren
id|corgi_ts-&gt;pendown
op_ne
l_int|0
)paren
)paren
suffix:semicolon
id|input_sync
c_func
(paren
op_amp
id|corgi_ts-&gt;input
)paren
suffix:semicolon
)brace
DECL|function|ts_interrupt_main
r_static
r_void
id|ts_interrupt_main
c_func
(paren
r_struct
id|corgi_ts
op_star
id|corgi_ts
comma
r_int
id|isTimer
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
(paren
id|GPLR
c_func
(paren
id|CORGI_GPIO_TP_INT
)paren
op_amp
id|GPIO_bit
c_func
(paren
id|CORGI_GPIO_TP_INT
)paren
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Disable Interrupt */
id|set_irq_type
c_func
(paren
id|CORGI_IRQ_GPIO_TP_INT
comma
id|IRQT_NOEDGE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_xydata
c_func
(paren
id|corgi_ts
)paren
)paren
(brace
id|corgi_ts-&gt;pendown
op_assign
l_int|1
suffix:semicolon
id|new_data
c_func
(paren
id|corgi_ts
comma
id|regs
)paren
suffix:semicolon
)brace
id|mod_timer
c_func
(paren
op_amp
id|corgi_ts-&gt;timer
comma
id|jiffies
op_plus
id|HZ
op_div
l_int|100
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|corgi_ts-&gt;pendown
op_eq
l_int|1
op_logical_or
id|corgi_ts-&gt;pendown
op_eq
l_int|2
)paren
(brace
id|mod_timer
c_func
(paren
op_amp
id|corgi_ts-&gt;timer
comma
id|jiffies
op_plus
id|HZ
op_div
l_int|100
)paren
suffix:semicolon
id|corgi_ts-&gt;pendown
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|corgi_ts-&gt;pendown
)paren
(brace
id|corgi_ts-&gt;tc.pressure
op_assign
l_int|0
suffix:semicolon
id|new_data
c_func
(paren
id|corgi_ts
comma
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable Falling Edge */
id|set_irq_type
c_func
(paren
id|CORGI_IRQ_GPIO_TP_INT
comma
id|IRQT_FALLING
)paren
suffix:semicolon
id|corgi_ts-&gt;pendown
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|corgi_ts_timer
r_static
r_void
id|corgi_ts_timer
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|corgi_ts
op_star
id|corgits_data
op_assign
(paren
r_struct
id|corgi_ts
op_star
)paren
id|data
suffix:semicolon
id|ts_interrupt_main
c_func
(paren
id|corgits_data
comma
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|ts_interrupt
r_static
id|irqreturn_t
id|ts_interrupt
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
r_struct
id|corgi_ts
op_star
id|corgits_data
op_assign
id|dev_id
suffix:semicolon
id|ts_interrupt_main
c_func
(paren
id|corgits_data
comma
l_int|0
comma
id|regs
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PM
DECL|function|corgits_suspend
r_static
r_int
id|corgits_suspend
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_uint32
id|state
comma
r_uint32
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
(brace
r_struct
id|corgi_ts
op_star
id|corgi_ts
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|corgi_ts-&gt;pendown
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|corgi_ts-&gt;timer
)paren
suffix:semicolon
id|corgi_ts-&gt;tc.pressure
op_assign
l_int|0
suffix:semicolon
id|new_data
c_func
(paren
id|corgi_ts
comma
l_int|NULL
)paren
suffix:semicolon
id|corgi_ts-&gt;pendown
op_assign
l_int|0
suffix:semicolon
)brace
id|corgi_ts-&gt;power_mode
op_assign
id|PWR_MODE_SUSPEND
suffix:semicolon
id|corgi_ssp_ads7846_putget
c_func
(paren
(paren
l_int|1u
op_lshift
id|ADSCTRL_ADR_SH
)paren
op_or
id|ADSCTRL_STS
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|corgits_resume
r_static
r_int
id|corgits_resume
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_uint32
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
(brace
r_struct
id|corgi_ts
op_star
id|corgi_ts
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|corgi_ssp_ads7846_putget
c_func
(paren
(paren
l_int|4u
op_lshift
id|ADSCTRL_ADR_SH
)paren
op_or
id|ADSCTRL_STS
)paren
suffix:semicolon
multiline_comment|/* Enable Falling Edge */
id|set_irq_type
c_func
(paren
id|CORGI_IRQ_GPIO_TP_INT
comma
id|IRQT_FALLING
)paren
suffix:semicolon
id|corgi_ts-&gt;power_mode
op_assign
id|PWR_MODE_ACTIVE
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|macro|corgits_suspend
mdefine_line|#define corgits_suspend&t;&t;NULL
DECL|macro|corgits_resume
mdefine_line|#define corgits_resume&t;&t;NULL
macro_line|#endif
DECL|function|corgits_probe
r_static
r_int
id|__init
id|corgits_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|corgi_ts
op_star
id|corgi_ts
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|corgi_ts
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|corgi_ts
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|dev_set_drvdata
c_func
(paren
id|dev
comma
id|corgi_ts
)paren
suffix:semicolon
id|memset
c_func
(paren
id|corgi_ts
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|corgi_ts
)paren
)paren
suffix:semicolon
id|init_input_dev
c_func
(paren
op_amp
id|corgi_ts-&gt;input
)paren
suffix:semicolon
id|corgi_ts-&gt;input.evbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|EV_KEY
)paren
op_or
id|BIT
c_func
(paren
id|EV_ABS
)paren
suffix:semicolon
id|corgi_ts-&gt;input.keybit
(braket
id|LONG
c_func
(paren
id|BTN_TOUCH
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|BTN_TOUCH
)paren
suffix:semicolon
id|input_set_abs_params
c_func
(paren
op_amp
id|corgi_ts-&gt;input
comma
id|ABS_X
comma
id|X_AXIS_MIN
comma
id|X_AXIS_MAX
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|input_set_abs_params
c_func
(paren
op_amp
id|corgi_ts-&gt;input
comma
id|ABS_Y
comma
id|Y_AXIS_MIN
comma
id|Y_AXIS_MAX
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|input_set_abs_params
c_func
(paren
op_amp
id|corgi_ts-&gt;input
comma
id|ABS_PRESSURE
comma
id|PRESSURE_MIN
comma
id|PRESSURE_MAX
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|corgi_ts-&gt;phys
comma
l_string|&quot;corgits/input0&quot;
)paren
suffix:semicolon
id|corgi_ts-&gt;input
dot
r_private
op_assign
id|corgi_ts
suffix:semicolon
id|corgi_ts-&gt;input.name
op_assign
l_string|&quot;Corgi Touchscreen&quot;
suffix:semicolon
id|corgi_ts-&gt;input.dev
op_assign
id|dev
suffix:semicolon
id|corgi_ts-&gt;input.phys
op_assign
id|corgi_ts-&gt;phys
suffix:semicolon
id|corgi_ts-&gt;input.id.bustype
op_assign
id|BUS_HOST
suffix:semicolon
id|corgi_ts-&gt;input.id.vendor
op_assign
l_int|0x0001
suffix:semicolon
id|corgi_ts-&gt;input.id.product
op_assign
l_int|0x0002
suffix:semicolon
id|corgi_ts-&gt;input.id.version
op_assign
l_int|0x0100
suffix:semicolon
id|pxa_gpio_mode
c_func
(paren
id|CORGI_GPIO_TP_INT
op_or
id|GPIO_IN
)paren
suffix:semicolon
id|pxa_gpio_mode
c_func
(paren
id|CORGI_GPIO_HSYNC
op_or
id|GPIO_IN
)paren
suffix:semicolon
multiline_comment|/* Initiaize ADS7846 Difference Reference mode */
id|corgi_ssp_ads7846_putget
c_func
(paren
(paren
l_int|1u
op_lshift
id|ADSCTRL_ADR_SH
)paren
op_or
id|ADSCTRL_STS
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|corgi_ssp_ads7846_putget
c_func
(paren
(paren
l_int|3u
op_lshift
id|ADSCTRL_ADR_SH
)paren
op_or
id|ADSCTRL_STS
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|corgi_ssp_ads7846_putget
c_func
(paren
(paren
l_int|4u
op_lshift
id|ADSCTRL_ADR_SH
)paren
op_or
id|ADSCTRL_STS
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|corgi_ssp_ads7846_putget
c_func
(paren
(paren
l_int|5u
op_lshift
id|ADSCTRL_ADR_SH
)paren
op_or
id|ADSCTRL_STS
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|corgi_ts-&gt;timer
)paren
suffix:semicolon
id|corgi_ts-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|corgi_ts
suffix:semicolon
id|corgi_ts-&gt;timer.function
op_assign
id|corgi_ts_timer
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|corgi_ts-&gt;input
)paren
suffix:semicolon
id|corgi_ts-&gt;power_mode
op_assign
id|PWR_MODE_ACTIVE
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|CORGI_IRQ_GPIO_TP_INT
comma
id|ts_interrupt
comma
id|SA_INTERRUPT
comma
l_string|&quot;ts&quot;
comma
id|corgi_ts
)paren
)paren
(brace
id|input_unregister_device
c_func
(paren
op_amp
id|corgi_ts-&gt;input
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|corgi_ts
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/* Enable Falling Edge */
id|set_irq_type
c_func
(paren
id|CORGI_IRQ_GPIO_TP_INT
comma
id|IRQT_FALLING
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: Corgi Touchscreen Registered&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|corgits_remove
r_static
r_int
id|corgits_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|corgi_ts
op_star
id|corgi_ts
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|CORGI_IRQ_GPIO_TP_INT
comma
l_int|NULL
)paren
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|corgi_ts-&gt;input
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|corgi_ts
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|corgits_driver
r_static
r_struct
id|device_driver
id|corgits_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;corgi-ts&quot;
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
id|corgits_probe
comma
dot
id|remove
op_assign
id|corgits_remove
comma
dot
id|suspend
op_assign
id|corgits_suspend
comma
dot
id|resume
op_assign
id|corgits_resume
comma
)brace
suffix:semicolon
DECL|function|corgits_init
r_static
r_int
id|__devinit
id|corgits_init
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
id|corgits_driver
)paren
suffix:semicolon
)brace
DECL|function|corgits_exit
r_static
r_void
id|__exit
id|corgits_exit
c_func
(paren
r_void
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|corgits_driver
)paren
suffix:semicolon
)brace
DECL|variable|corgits_init
id|module_init
c_func
(paren
id|corgits_init
)paren
suffix:semicolon
DECL|variable|corgits_exit
id|module_exit
c_func
(paren
id|corgits_exit
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
l_string|&quot;Corgi TouchScreen Driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
