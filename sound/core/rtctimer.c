multiline_comment|/*&n; *  RTC based high-frequency timer&n; *&n; *  Copyright (C) 2000 Takashi Iwai&n; *&t;based on rtctimer.c by Steve Ratcliffe&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/timer.h&gt;
macro_line|#include &lt;sound/info.h&gt;
macro_line|#if defined(CONFIG_RTC) || defined(CONFIG_RTC_MODULE)
macro_line|#include &lt;linux/mc146818rtc.h&gt;
DECL|macro|RTC_FREQ
mdefine_line|#define RTC_FREQ&t;1024&t;&t;/* default frequency */
DECL|macro|NANO_SEC
mdefine_line|#define NANO_SEC&t;1000000000L&t;/* 10^9 in sec */
multiline_comment|/*&n; * prototypes&n; */
r_static
r_int
id|rtctimer_open
c_func
(paren
id|snd_timer_t
op_star
id|t
)paren
suffix:semicolon
r_static
r_int
id|rtctimer_close
c_func
(paren
id|snd_timer_t
op_star
id|t
)paren
suffix:semicolon
r_static
r_int
id|rtctimer_start
c_func
(paren
id|snd_timer_t
op_star
id|t
)paren
suffix:semicolon
r_static
r_int
id|rtctimer_stop
c_func
(paren
id|snd_timer_t
op_star
id|t
)paren
suffix:semicolon
multiline_comment|/*&n; * The hardware dependent description for this timer.&n; */
DECL|variable|rtc_hw
r_static
r_struct
id|_snd_timer_hardware
id|rtc_hw
op_assign
(brace
dot
id|flags
op_assign
id|SNDRV_TIMER_HW_FIRST
op_or
id|SNDRV_TIMER_HW_AUTO
comma
dot
id|ticks
op_assign
l_int|100000000L
comma
multiline_comment|/* FIXME: XXX */
dot
id|open
op_assign
id|rtctimer_open
comma
dot
id|close
op_assign
id|rtctimer_close
comma
dot
id|start
op_assign
id|rtctimer_start
comma
dot
id|stop
op_assign
id|rtctimer_stop
comma
)brace
suffix:semicolon
DECL|variable|rtctimer_freq
r_int
id|rtctimer_freq
op_assign
id|RTC_FREQ
suffix:semicolon
multiline_comment|/* frequency */
DECL|variable|rtctimer
r_static
id|snd_timer_t
op_star
id|rtctimer
suffix:semicolon
DECL|variable|rtc_inc
r_static
id|atomic_t
id|rtc_inc
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
DECL|variable|rtc_task
r_static
id|rtc_task_t
id|rtc_task
suffix:semicolon
r_static
r_int
DECL|function|rtctimer_open
id|rtctimer_open
c_func
(paren
id|snd_timer_t
op_star
id|t
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|rtc_register
c_func
(paren
op_amp
id|rtc_task
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|t-&gt;private_data
op_assign
op_amp
id|rtc_task
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|rtctimer_close
id|rtctimer_close
c_func
(paren
id|snd_timer_t
op_star
id|t
)paren
(brace
id|rtc_task_t
op_star
id|rtc
op_assign
id|t-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|rtc
)paren
(brace
id|rtc_unregister
c_func
(paren
id|rtc
)paren
suffix:semicolon
id|t-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|rtctimer_start
id|rtctimer_start
c_func
(paren
id|snd_timer_t
op_star
id|timer
)paren
(brace
id|rtc_task_t
op_star
id|rtc
op_assign
id|timer-&gt;private_data
suffix:semicolon
id|snd_assert
c_func
(paren
id|rtc
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|rtc_control
c_func
(paren
id|rtc
comma
id|RTC_IRQP_SET
comma
id|rtctimer_freq
)paren
suffix:semicolon
id|rtc_control
c_func
(paren
id|rtc
comma
id|RTC_PIE_ON
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|rtc_inc
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|rtctimer_stop
id|rtctimer_stop
c_func
(paren
id|snd_timer_t
op_star
id|timer
)paren
(brace
id|rtc_task_t
op_star
id|rtc
op_assign
id|timer-&gt;private_data
suffix:semicolon
id|snd_assert
c_func
(paren
id|rtc
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|rtc_control
c_func
(paren
id|rtc
comma
id|RTC_PIE_OFF
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * interrupt&n; */
DECL|function|rtctimer_interrupt
r_static
r_void
id|rtctimer_interrupt
c_func
(paren
r_void
op_star
id|private_data
)paren
(brace
r_int
id|ticks
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|rtc_inc
)paren
suffix:semicolon
id|ticks
op_assign
id|atomic_read
c_func
(paren
op_amp
id|rtc_inc
)paren
suffix:semicolon
id|snd_timer_interrupt
c_func
(paren
(paren
id|snd_timer_t
op_star
)paren
id|private_data
comma
id|ticks
)paren
suffix:semicolon
id|atomic_sub
c_func
(paren
id|ticks
comma
op_amp
id|rtc_inc
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  ENTRY functions&n; */
DECL|function|rtctimer_init
r_static
r_int
id|__init
id|rtctimer_init
c_func
(paren
r_void
)paren
(brace
r_int
id|order
comma
id|err
suffix:semicolon
id|snd_timer_t
op_star
id|timer
suffix:semicolon
r_if
c_cond
(paren
id|rtctimer_freq
template_param
l_int|8192
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rtctimer: invalid frequency %d&bslash;n&quot;
comma
id|rtctimer_freq
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|order
op_assign
l_int|1
suffix:semicolon
id|rtctimer_freq
OG
id|order
suffix:semicolon
id|order
op_lshift_assign
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtctimer_freq
op_ne
id|order
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rtctimer: invalid frequency %d&bslash;n&quot;
comma
id|rtctimer_freq
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Create a new timer and set up the fields */
id|err
op_assign
id|snd_timer_global_new
c_func
(paren
l_string|&quot;rtc&quot;
comma
id|SNDRV_TIMER_GLOBAL_RTC
comma
op_amp
id|timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|strcpy
c_func
(paren
id|timer-&gt;name
comma
l_string|&quot;RTC timer&quot;
)paren
suffix:semicolon
id|timer-&gt;hw
op_assign
id|rtc_hw
suffix:semicolon
id|timer-&gt;hw.resolution
op_assign
id|NANO_SEC
op_div
id|rtctimer_freq
suffix:semicolon
multiline_comment|/* set up RTC callback */
id|rtc_task.func
op_assign
id|rtctimer_interrupt
suffix:semicolon
id|rtc_task.private_data
op_assign
id|timer
suffix:semicolon
id|err
op_assign
id|snd_timer_global_register
c_func
(paren
id|timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|snd_timer_global_free
c_func
(paren
id|timer
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|rtctimer
op_assign
id|timer
suffix:semicolon
multiline_comment|/* remember this */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rtctimer_exit
r_static
r_void
id|__exit
id|rtctimer_exit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|rtctimer
)paren
(brace
id|snd_timer_global_unregister
c_func
(paren
id|rtctimer
)paren
suffix:semicolon
id|rtctimer
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * exported stuff&n; */
id|module_init
c_func
(paren
id|rtctimer_init
)paren
id|module_exit
c_func
(paren
id|rtctimer_exit
)paren
id|MODULE_PARM
c_func
(paren
id|rtctimer_freq
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|rtctimer_freq
comma
l_string|&quot;timer frequency in Hz&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_RTC || CONFIG_RTC_MODULE */
eof
