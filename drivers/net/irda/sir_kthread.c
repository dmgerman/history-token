multiline_comment|/*********************************************************************&n; *&n; *&t;sir_kthread.c:&t;&t;dedicated thread to process scheduled&n; *&t;&t;&t;&t;sir device setup requests&n; *&n; *&t;Copyright (c) 2002 Martin Diehl&n; *&n; *&t;This program is free software; you can redistribute it and/or &n; *&t;modify it under the terms of the GNU General Public License as &n; *&t;published by the Free Software Foundation; either version 2 of &n; *&t;the License, or (at your option) any later version.&n; *&n; ********************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &quot;sir-dev.h&quot;
multiline_comment|/**************************************************************************&n; *&n; * kIrDAd kernel thread and config state machine&n; *&n; */
DECL|struct|irda_request_queue
r_struct
id|irda_request_queue
(brace
DECL|member|request_list
r_struct
id|list_head
id|request_list
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|thread
id|task_t
op_star
id|thread
suffix:semicolon
DECL|member|exit
r_struct
id|completion
m_exit
suffix:semicolon
DECL|member|kick
DECL|member|done
id|wait_queue_head_t
id|kick
comma
id|done
suffix:semicolon
DECL|member|num_pending
id|atomic_t
id|num_pending
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|irda_rq_queue
r_static
r_struct
id|irda_request_queue
id|irda_rq_queue
suffix:semicolon
DECL|function|irda_queue_request
r_static
r_int
id|irda_queue_request
c_func
(paren
r_struct
id|irda_request
op_star
id|rq
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|rq-&gt;pending
)paren
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irda_rq_queue.lock
comma
id|flags
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|rq-&gt;lh_request
comma
op_amp
id|irda_rq_queue.request_list
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|irda_rq_queue.kick
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|irda_rq_queue.num_pending
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irda_rq_queue.lock
comma
id|flags
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|irda_request_timer
r_static
r_void
id|irda_request_timer
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|irda_request
op_star
id|rq
op_assign
(paren
r_struct
id|irda_request
op_star
)paren
id|data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irda_rq_queue.lock
comma
id|flags
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|rq-&gt;lh_request
comma
op_amp
id|irda_rq_queue.request_list
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|irda_rq_queue.kick
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irda_rq_queue.lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|irda_queue_delayed_request
r_static
r_int
id|irda_queue_delayed_request
c_func
(paren
r_struct
id|irda_request
op_star
id|rq
comma
r_int
r_int
id|delay
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|timer_list
op_star
id|timer
op_assign
op_amp
id|rq-&gt;timer
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|rq-&gt;pending
)paren
)paren
(brace
id|timer-&gt;expires
op_assign
id|jiffies
op_plus
id|delay
suffix:semicolon
id|timer-&gt;function
op_assign
id|irda_request_timer
suffix:semicolon
id|timer-&gt;data
op_assign
(paren
r_int
r_int
)paren
id|rq
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|irda_rq_queue.num_pending
)paren
suffix:semicolon
id|add_timer
c_func
(paren
id|timer
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|run_irda_queue
r_static
r_void
id|run_irda_queue
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
comma
op_star
id|tmp
suffix:semicolon
r_struct
id|irda_request
op_star
id|rq
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irda_rq_queue.lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|entry
comma
id|tmp
comma
op_amp
id|irda_rq_queue.request_list
)paren
(brace
id|rq
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|irda_request
comma
id|lh_request
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
id|entry
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irda_rq_queue.lock
comma
id|flags
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|rq-&gt;pending
)paren
suffix:semicolon
id|rq
op_member_access_from_pointer
id|func
c_func
(paren
id|rq-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|irda_rq_queue.num_pending
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|irda_rq_queue.done
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irda_rq_queue.lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irda_rq_queue.lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|irda_thread
r_static
r_int
id|irda_thread
c_func
(paren
r_void
op_star
id|startup
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;kIrDAd&quot;
)paren
suffix:semicolon
id|irda_rq_queue.thread
op_assign
id|current
suffix:semicolon
id|complete
c_func
(paren
(paren
r_struct
id|completion
op_star
)paren
id|startup
)paren
suffix:semicolon
r_while
c_loop
(paren
id|irda_rq_queue.thread
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* We use TASK_INTERRUPTIBLE, rather than&n;&t;&t; * TASK_UNINTERRUPTIBLE.  Andrew Morton made this&n;&t;&t; * change ; he told me that it is safe, because &quot;signal&n;&t;&t; * blocking is now handled in daemonize()&quot;, he added&n;&t;&t; * that the problem is that &quot;uninterruptible sleep&n;&t;&t; * contributes to load average&quot;, making user worry.&n;&t;&t; * Jean II */
id|set_task_state
c_func
(paren
id|current
comma
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|irda_rq_queue.kick
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|irda_rq_queue.request_list
)paren
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_else
id|__set_task_state
c_func
(paren
id|current
comma
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|irda_rq_queue.kick
comma
op_amp
id|wait
)paren
suffix:semicolon
multiline_comment|/* make swsusp happy with our thread */
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_FREEZE
)paren
id|refrigerator
c_func
(paren
id|PF_FREEZE
)paren
suffix:semicolon
id|run_irda_queue
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,35)
id|reparent_to_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|complete_and_exit
c_func
(paren
op_amp
id|irda_rq_queue
dot
m_exit
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* never reached */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|flush_irda_queue
r_static
r_void
id|flush_irda_queue
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|irda_rq_queue.num_pending
)paren
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|irda_rq_queue.request_list
)paren
)paren
id|run_irda_queue
c_func
(paren
)paren
suffix:semicolon
id|set_task_state
c_func
(paren
id|current
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|irda_rq_queue.done
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|irda_rq_queue.num_pending
)paren
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_else
id|__set_task_state
c_func
(paren
id|current
comma
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|irda_rq_queue.done
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* substate handler of the config-fsm to handle the cases where we want&n; * to wait for transmit completion before changing the port configuration&n; */
DECL|function|irda_tx_complete_fsm
r_static
r_int
id|irda_tx_complete_fsm
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
)paren
(brace
r_struct
id|sir_fsm
op_star
id|fsm
op_assign
op_amp
id|dev-&gt;fsm
suffix:semicolon
r_int
id|next_state
comma
id|delay
suffix:semicolon
r_int
id|bytes_left
suffix:semicolon
r_do
(brace
id|next_state
op_assign
id|fsm-&gt;substate
suffix:semicolon
multiline_comment|/* default: stay in current substate */
id|delay
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|fsm-&gt;substate
)paren
(brace
r_case
id|SIRDEV_STATE_WAIT_XMIT
suffix:colon
r_if
c_cond
(paren
id|dev-&gt;drv-&gt;chars_in_buffer
)paren
id|bytes_left
op_assign
id|dev-&gt;drv
op_member_access_from_pointer
id|chars_in_buffer
c_func
(paren
id|dev
)paren
suffix:semicolon
r_else
id|bytes_left
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bytes_left
)paren
(brace
id|next_state
op_assign
id|SIRDEV_STATE_WAIT_UNTIL_SENT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;speed
OG
l_int|115200
)paren
id|delay
op_assign
(paren
id|bytes_left
op_star
l_int|8
op_star
l_int|10000
)paren
op_div
(paren
id|dev-&gt;speed
op_div
l_int|100
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dev-&gt;speed
OG
l_int|0
)paren
id|delay
op_assign
(paren
id|bytes_left
op_star
l_int|10
op_star
l_int|10000
)paren
op_div
(paren
id|dev-&gt;speed
op_div
l_int|100
)paren
suffix:semicolon
r_else
id|delay
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* expected delay (usec) until remaining bytes are sent */
r_if
c_cond
(paren
id|delay
OL
l_int|100
)paren
(brace
id|udelay
c_func
(paren
id|delay
)paren
suffix:semicolon
id|delay
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* sleep some longer delay (msec) */
id|delay
op_assign
(paren
id|delay
op_plus
l_int|999
)paren
op_div
l_int|1000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIRDEV_STATE_WAIT_UNTIL_SENT
suffix:colon
multiline_comment|/* block until underlaying hardware buffer are empty */
r_if
c_cond
(paren
id|dev-&gt;drv-&gt;wait_until_sent
)paren
id|dev-&gt;drv
op_member_access_from_pointer
id|wait_until_sent
c_func
(paren
id|dev
)paren
suffix:semicolon
id|next_state
op_assign
id|SIRDEV_STATE_TX_DONE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIRDEV_STATE_TX_DONE
suffix:colon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
id|IRDA_ERROR
c_func
(paren
l_string|&quot;%s - undefined state&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|fsm-&gt;substate
op_assign
id|next_state
suffix:semicolon
)brace
r_while
c_loop
(paren
id|delay
op_eq
l_int|0
)paren
suffix:semicolon
r_return
id|delay
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_config_fsm&n; *&n; * State machine to handle the configuration of the device (and attached dongle, if any).&n; * This handler is scheduled for execution in kIrDAd context, so we can sleep.&n; * however, kIrDAd is shared by all sir_dev devices so we better don&squot;t sleep there too&n; * long. Instead, for longer delays we start a timer to reschedule us later.&n; * On entry, fsm-&gt;sem is always locked and the netdev xmit queue stopped.&n; * Both must be unlocked/restarted on completion - but only on final exit.&n; */
DECL|function|irda_config_fsm
r_static
r_void
id|irda_config_fsm
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|sir_dev
op_star
id|dev
op_assign
id|data
suffix:semicolon
r_struct
id|sir_fsm
op_star
id|fsm
op_assign
op_amp
id|dev-&gt;fsm
suffix:semicolon
r_int
id|next_state
suffix:semicolon
r_int
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|delay
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), &lt;%ld&gt;&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|jiffies
)paren
suffix:semicolon
r_do
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|3
comma
l_string|&quot;%s - state=0x%04x / substate=0x%04x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|fsm-&gt;state
comma
id|fsm-&gt;substate
)paren
suffix:semicolon
id|next_state
op_assign
id|fsm-&gt;state
suffix:semicolon
id|delay
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|fsm-&gt;state
)paren
(brace
r_case
id|SIRDEV_STATE_DONGLE_OPEN
suffix:colon
r_if
c_cond
(paren
id|dev-&gt;dongle_drv
op_ne
l_int|NULL
)paren
(brace
id|ret
op_assign
id|sirdev_put_dongle
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|fsm-&gt;result
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|next_state
op_assign
id|SIRDEV_STATE_ERROR
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* Initialize dongle */
id|ret
op_assign
id|sirdev_get_dongle
c_func
(paren
id|dev
comma
id|fsm-&gt;param
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|fsm-&gt;result
op_assign
id|ret
suffix:semicolon
id|next_state
op_assign
id|SIRDEV_STATE_ERROR
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Dongles are powered through the modem control lines which&n;&t;&t;&t; * were just set during open. Before resetting, let&squot;s wait for&n;&t;&t;&t; * the power to stabilize. This is what some dongle drivers did&n;&t;&t;&t; * in open before, while others didn&squot;t - should be safe anyway.&n;&t;&t;&t; */
id|delay
op_assign
l_int|50
suffix:semicolon
id|fsm-&gt;substate
op_assign
id|SIRDEV_STATE_DONGLE_RESET
suffix:semicolon
id|next_state
op_assign
id|SIRDEV_STATE_DONGLE_RESET
suffix:semicolon
id|fsm-&gt;param
op_assign
l_int|9600
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIRDEV_STATE_DONGLE_CLOSE
suffix:colon
multiline_comment|/* shouldn&squot;t we just treat this as success=? */
r_if
c_cond
(paren
id|dev-&gt;dongle_drv
op_eq
l_int|NULL
)paren
(brace
id|fsm-&gt;result
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|next_state
op_assign
id|SIRDEV_STATE_ERROR
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ret
op_assign
id|sirdev_put_dongle
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|fsm-&gt;result
op_assign
id|ret
suffix:semicolon
id|next_state
op_assign
id|SIRDEV_STATE_ERROR
suffix:semicolon
r_break
suffix:semicolon
)brace
id|next_state
op_assign
id|SIRDEV_STATE_DONE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIRDEV_STATE_SET_DTR_RTS
suffix:colon
id|ret
op_assign
id|sirdev_set_dtr_rts
c_func
(paren
id|dev
comma
(paren
id|fsm-&gt;param
op_amp
l_int|0x02
)paren
ques
c_cond
id|TRUE
suffix:colon
id|FALSE
comma
(paren
id|fsm-&gt;param
op_amp
l_int|0x01
)paren
ques
c_cond
id|TRUE
suffix:colon
id|FALSE
)paren
suffix:semicolon
id|next_state
op_assign
id|SIRDEV_STATE_DONE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIRDEV_STATE_SET_SPEED
suffix:colon
id|fsm-&gt;substate
op_assign
id|SIRDEV_STATE_WAIT_XMIT
suffix:semicolon
id|next_state
op_assign
id|SIRDEV_STATE_DONGLE_CHECK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIRDEV_STATE_DONGLE_CHECK
suffix:colon
id|ret
op_assign
id|irda_tx_complete_fsm
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|fsm-&gt;result
op_assign
id|ret
suffix:semicolon
id|next_state
op_assign
id|SIRDEV_STATE_ERROR
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|delay
op_assign
id|ret
)paren
op_ne
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;dongle_drv
)paren
(brace
id|fsm-&gt;substate
op_assign
id|SIRDEV_STATE_DONGLE_RESET
suffix:semicolon
id|next_state
op_assign
id|SIRDEV_STATE_DONGLE_RESET
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;speed
op_assign
id|fsm-&gt;param
suffix:semicolon
id|next_state
op_assign
id|SIRDEV_STATE_PORT_SPEED
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SIRDEV_STATE_DONGLE_RESET
suffix:colon
r_if
c_cond
(paren
id|dev-&gt;dongle_drv-&gt;reset
)paren
(brace
id|ret
op_assign
id|dev-&gt;dongle_drv
op_member_access_from_pointer
id|reset
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|fsm-&gt;result
op_assign
id|ret
suffix:semicolon
id|next_state
op_assign
id|SIRDEV_STATE_ERROR
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|delay
op_assign
id|ret
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* set serial port according to dongle default speed */
r_if
c_cond
(paren
id|dev-&gt;drv-&gt;set_speed
)paren
id|dev-&gt;drv
op_member_access_from_pointer
id|set_speed
c_func
(paren
id|dev
comma
id|dev-&gt;speed
)paren
suffix:semicolon
id|fsm-&gt;substate
op_assign
id|SIRDEV_STATE_DONGLE_SPEED
suffix:semicolon
id|next_state
op_assign
id|SIRDEV_STATE_DONGLE_SPEED
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SIRDEV_STATE_DONGLE_SPEED
suffix:colon
r_if
c_cond
(paren
id|dev-&gt;dongle_drv-&gt;reset
)paren
(brace
id|ret
op_assign
id|dev-&gt;dongle_drv
op_member_access_from_pointer
id|set_speed
c_func
(paren
id|dev
comma
id|fsm-&gt;param
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|fsm-&gt;result
op_assign
id|ret
suffix:semicolon
id|next_state
op_assign
id|SIRDEV_STATE_ERROR
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|delay
op_assign
id|ret
)paren
op_eq
l_int|0
)paren
id|next_state
op_assign
id|SIRDEV_STATE_PORT_SPEED
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIRDEV_STATE_PORT_SPEED
suffix:colon
multiline_comment|/* Finally we are ready to change the serial port speed */
r_if
c_cond
(paren
id|dev-&gt;drv-&gt;set_speed
)paren
id|dev-&gt;drv
op_member_access_from_pointer
id|set_speed
c_func
(paren
id|dev
comma
id|dev-&gt;speed
)paren
suffix:semicolon
id|dev-&gt;new_speed
op_assign
l_int|0
suffix:semicolon
id|next_state
op_assign
id|SIRDEV_STATE_DONE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIRDEV_STATE_DONE
suffix:colon
multiline_comment|/* Signal network layer so it can send more frames */
id|netif_wake_queue
c_func
(paren
id|dev-&gt;netdev
)paren
suffix:semicolon
id|next_state
op_assign
id|SIRDEV_STATE_COMPLETE
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_ERROR
c_func
(paren
l_string|&quot;%s - undefined state&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|fsm-&gt;result
op_assign
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* fall thru */
r_case
id|SIRDEV_STATE_ERROR
suffix:colon
id|IRDA_ERROR
c_func
(paren
l_string|&quot;%s - error: %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|fsm-&gt;result
)paren
suffix:semicolon
macro_line|#if 0&t;/* don&squot;t enable this before we have netdev-&gt;tx_timeout to recover */
id|netif_stop_queue
c_func
(paren
id|dev-&gt;netdev
)paren
suffix:semicolon
macro_line|#else
id|netif_wake_queue
c_func
(paren
id|dev-&gt;netdev
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* fall thru */
r_case
id|SIRDEV_STATE_COMPLETE
suffix:colon
multiline_comment|/* config change finished, so we are not busy any longer */
id|sirdev_enable_rx
c_func
(paren
id|dev
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|fsm-&gt;sem
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|fsm-&gt;state
op_assign
id|next_state
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|delay
)paren
(brace
suffix:semicolon
)brace
id|irda_queue_delayed_request
c_func
(paren
op_amp
id|fsm-&gt;rq
comma
id|msecs_to_jiffies
c_func
(paren
id|delay
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* schedule some device configuration task for execution by kIrDAd&n; * on behalf of the above state machine.&n; * can be called from process or interrupt/tasklet context.&n; */
DECL|function|sirdev_schedule_request
r_int
id|sirdev_schedule_request
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
comma
r_int
id|initial_state
comma
r_int
id|param
)paren
(brace
r_struct
id|sir_fsm
op_star
id|fsm
op_assign
op_amp
id|dev-&gt;fsm
suffix:semicolon
r_int
id|xmit_was_down
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s - state=0x%04x / param=%u&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|initial_state
comma
id|param
)paren
suffix:semicolon
r_if
c_cond
(paren
id|down_trylock
c_func
(paren
op_amp
id|fsm-&gt;sem
)paren
)paren
(brace
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
op_logical_or
id|in_atomic
c_func
(paren
)paren
op_logical_or
id|irqs_disabled
c_func
(paren
)paren
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;%s(), state machine busy!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EWOULDBLOCK
suffix:semicolon
)brace
r_else
id|down
c_func
(paren
op_amp
id|fsm-&gt;sem
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fsm-&gt;state
op_eq
id|SIRDEV_STATE_DEAD
)paren
(brace
multiline_comment|/* race with sirdev_close should never happen */
id|IRDA_ERROR
c_func
(paren
l_string|&quot;%s(), instance staled!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|fsm-&gt;sem
)paren
suffix:semicolon
r_return
op_minus
id|ESTALE
suffix:semicolon
multiline_comment|/* or better EPIPE? */
)brace
id|xmit_was_down
op_assign
id|netif_queue_stopped
c_func
(paren
id|dev-&gt;netdev
)paren
suffix:semicolon
id|netif_stop_queue
c_func
(paren
id|dev-&gt;netdev
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;enable_rx
comma
l_int|0
)paren
suffix:semicolon
id|fsm-&gt;state
op_assign
id|initial_state
suffix:semicolon
id|fsm-&gt;param
op_assign
id|param
suffix:semicolon
id|fsm-&gt;result
op_assign
l_int|0
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|fsm-&gt;rq.lh_request
)paren
suffix:semicolon
id|fsm-&gt;rq.pending
op_assign
l_int|0
suffix:semicolon
id|fsm-&gt;rq.func
op_assign
id|irda_config_fsm
suffix:semicolon
id|fsm-&gt;rq.data
op_assign
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irda_queue_request
c_func
(paren
op_amp
id|fsm-&gt;rq
)paren
)paren
(brace
multiline_comment|/* returns 0 on error! */
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;enable_rx
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|xmit_was_down
)paren
id|netif_wake_queue
c_func
(paren
id|dev-&gt;netdev
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|fsm-&gt;sem
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|irda_thread_create
r_int
id|__init
id|irda_thread_create
c_func
(paren
r_void
)paren
(brace
r_struct
id|completion
id|startup
suffix:semicolon
r_int
id|pid
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|irda_rq_queue.lock
)paren
suffix:semicolon
id|irda_rq_queue.thread
op_assign
l_int|NULL
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|irda_rq_queue.request_list
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|irda_rq_queue.kick
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|irda_rq_queue.done
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|irda_rq_queue.num_pending
comma
l_int|0
)paren
suffix:semicolon
id|init_completion
c_func
(paren
op_amp
id|startup
)paren
suffix:semicolon
id|pid
op_assign
id|kernel_thread
c_func
(paren
id|irda_thread
comma
op_amp
id|startup
comma
id|CLONE_FS
op_or
id|CLONE_FILES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_le
l_int|0
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_else
id|wait_for_completion
c_func
(paren
op_amp
id|startup
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|irda_thread_join
r_void
id|__exit
id|irda_thread_join
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|irda_rq_queue.thread
)paren
(brace
id|flush_irda_queue
c_func
(paren
)paren
suffix:semicolon
id|init_completion
c_func
(paren
op_amp
id|irda_rq_queue
dot
m_exit
)paren
suffix:semicolon
id|irda_rq_queue.thread
op_assign
l_int|NULL
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|irda_rq_queue.kick
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|irda_rq_queue
dot
m_exit
)paren
suffix:semicolon
)brace
)brace
eof
