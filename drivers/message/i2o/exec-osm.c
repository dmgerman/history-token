multiline_comment|/*&n; *&t;Executive OSM&n; *&n; * &t;Copyright (C) 1999-2002&t;Red Hat Software&n; *&n; *&t;Written by Alan Cox, Building Number Three Ltd&n; *&n; *&t;This program is free software; you can redistribute it and/or modify it&n; *&t;under the terms of the GNU General Public License as published by the&n; *&t;Free Software Foundation; either version 2 of the License, or (at your&n; *&t;option) any later version.&n; *&n; *&t;A lot of the I2O message side code from this is taken from the Red&n; *&t;Creek RCPCI45 adapter driver by Red Creek Communications&n; *&n; *&t;Fixes/additions:&n; *&t;&t;Philipp Rumpf&n; *&t;&t;Juha Siev&#xfffd;nen &lt;Juha.Sievanen@cs.Helsinki.FI&gt;&n; *&t;&t;Auvo H&#xfffd;kkinen &lt;Auvo.Hakkinen@cs.Helsinki.FI&gt;&n; *&t;&t;Deepak Saxena &lt;deepak@plexity.net&gt;&n; *&t;&t;Boji T Kannanthanam &lt;boji.t.kannanthanam@intel.com&gt;&n; *&t;&t;Alan Cox &lt;alan@redhat.com&gt;:&n; *&t;&t;&t;Ported to Linux 2.5.&n; *&t;&t;Markus Lidel &lt;Markus.Lidel@shadowconnect.com&gt;:&n; *&t;&t;&t;Minor fixes for 2.6.&n; *&t;&t;Markus Lidel &lt;Markus.Lidel@shadowconnect.com&gt;:&n; *&t;&t;&t;Support for sysfs included.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/i2o.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
DECL|variable|i2o_exec_driver
r_struct
id|i2o_driver
id|i2o_exec_driver
suffix:semicolon
r_static
r_int
id|i2o_exec_lct_notify
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
id|u32
id|change_ind
)paren
suffix:semicolon
multiline_comment|/* Module internal functions from other sources */
r_extern
r_int
id|i2o_device_parse_lct
c_func
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
multiline_comment|/* global wait list for POST WAIT */
r_static
id|LIST_HEAD
c_func
(paren
id|i2o_exec_wait_list
)paren
suffix:semicolon
multiline_comment|/* Wait struct needed for POST WAIT */
DECL|struct|i2o_exec_wait
r_struct
id|i2o_exec_wait
(brace
DECL|member|wq
id|wait_queue_head_t
op_star
id|wq
suffix:semicolon
multiline_comment|/* Pointer to Wait queue */
DECL|member|dma
r_struct
id|i2o_dma
id|dma
suffix:semicolon
multiline_comment|/* DMA buffers to free on failure */
DECL|member|tcntxt
id|u32
id|tcntxt
suffix:semicolon
multiline_comment|/* transaction context from reply */
DECL|member|complete
r_int
id|complete
suffix:semicolon
multiline_comment|/* 1 if reply received otherwise 0 */
DECL|member|m
id|u32
id|m
suffix:semicolon
multiline_comment|/* message id */
DECL|member|msg
r_struct
id|i2o_message
op_star
id|msg
suffix:semicolon
multiline_comment|/* pointer to the reply message */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* node in global wait list */
)brace
suffix:semicolon
multiline_comment|/* Exec OSM class handling definition */
DECL|variable|i2o_exec_class_id
r_static
r_struct
id|i2o_class_id
id|i2o_exec_class_id
(braket
)braket
op_assign
(brace
(brace
id|I2O_CLASS_EXECUTIVE
)brace
comma
(brace
id|I2O_CLASS_END
)brace
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_exec_wait_alloc - Allocate a i2o_exec_wait struct an initialize it&n; *&n; *&t;Allocate the i2o_exec_wait struct and initialize the wait.&n; *&n; *&t;Returns i2o_exec_wait pointer on success or negative error code on&n; *&t;failure.&n; */
DECL|function|i2o_exec_wait_alloc
r_static
r_struct
id|i2o_exec_wait
op_star
id|i2o_exec_wait_alloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|i2o_exec_wait
op_star
id|wait
suffix:semicolon
id|wait
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|wait
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|wait
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|memset
c_func
(paren
id|wait
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|wait
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|wait-&gt;list
)paren
suffix:semicolon
r_return
id|wait
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_exec_wait_free - Free a i2o_exec_wait struct&n; *&t;@i2o_exec_wait: I2O wait data which should be cleaned up&n; */
DECL|function|i2o_exec_wait_free
r_static
r_void
id|i2o_exec_wait_free
c_func
(paren
r_struct
id|i2o_exec_wait
op_star
id|wait
)paren
(brace
id|kfree
c_func
(paren
id|wait
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * &t;i2o_msg_post_wait_mem - Post and wait a message with DMA buffers&n; *&t;@c: controller&n; *&t;@m: message to post&n; *&t;@timeout: time in seconds to wait&n; *&t;@dma: i2o_dma struct of the DMA buffer to free on failure&n; *&n; * &t;This API allows an OSM to post a message and then be told whether or&n; *&t;not the system received a successful reply. If the message times out&n; *&t;then the value &squot;-ETIMEDOUT&squot; is returned. This is a special case. In&n; *&t;this situation the message may (should) complete at an indefinite time&n; *&t;in the future. When it completes it will use the memory buffer&n; *&t;attached to the request. If -ETIMEDOUT is returned then the memory&n; *&t;buffer must not be freed. Instead the event completion will free them&n; *&t;for you. In all other cases the buffer are your problem.&n; *&n; *&t;Returns 0 on success or negative error code on failure.&n; */
DECL|function|i2o_msg_post_wait_mem
r_int
id|i2o_msg_post_wait_mem
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
id|u32
id|m
comma
r_int
r_int
id|timeout
comma
r_struct
id|i2o_dma
op_star
id|dma
)paren
(brace
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|wq
)paren
suffix:semicolon
id|DEFINE_WAIT
c_func
(paren
id|wait
)paren
suffix:semicolon
r_struct
id|i2o_exec_wait
op_star
id|iwait
suffix:semicolon
r_static
id|u32
id|tcntxt
op_assign
l_int|0x80000000
suffix:semicolon
r_struct
id|i2o_message
op_star
id|msg
op_assign
id|c-&gt;in_queue.virt
op_plus
id|m
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|iwait
op_assign
id|i2o_exec_wait_alloc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iwait
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|tcntxt
op_eq
l_int|0xffffffff
)paren
id|tcntxt
op_assign
l_int|0x80000000
suffix:semicolon
r_if
c_cond
(paren
id|dma
)paren
id|iwait-&gt;dma
op_assign
op_star
id|dma
suffix:semicolon
multiline_comment|/*&n;&t; * Fill in the message initiator context and transaction context.&n;&t; * We will only use transaction contexts &gt;= 0x80000000 for POST WAIT,&n;&t; * so we could find a POST WAIT reply easier in the reply handler.&n;&t; */
id|writel
c_func
(paren
id|i2o_exec_driver.context
comma
op_amp
id|msg-&gt;u.s.icntxt
)paren
suffix:semicolon
id|iwait-&gt;tcntxt
op_assign
id|tcntxt
op_increment
suffix:semicolon
id|writel
c_func
(paren
id|iwait-&gt;tcntxt
comma
op_amp
id|msg-&gt;u.s.tcntxt
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Post the message to the controller. At some point later it will&n;&t; * return. If we time out before it returns then complete will be zero.&n;&t; */
id|i2o_msg_post
c_func
(paren
id|c
comma
id|m
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iwait-&gt;complete
)paren
(brace
id|iwait-&gt;wq
op_assign
op_amp
id|wq
suffix:semicolon
multiline_comment|/*&n;&t;&t; * we add elements add the head, because if a entry in the list&n;&t;&t; * will never be removed, we have to iterate over it every time&n;&t;&t; */
id|list_add
c_func
(paren
op_amp
id|iwait-&gt;list
comma
op_amp
id|i2o_exec_wait_list
)paren
suffix:semicolon
id|prepare_to_wait
c_func
(paren
op_amp
id|wq
comma
op_amp
id|wait
comma
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iwait-&gt;complete
)paren
id|msleep_interruptible
c_func
(paren
id|timeout
op_star
l_int|1000
)paren
suffix:semicolon
id|finish_wait
c_func
(paren
op_amp
id|wq
comma
op_amp
id|wait
)paren
suffix:semicolon
id|iwait-&gt;wq
op_assign
l_int|NULL
suffix:semicolon
)brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iwait-&gt;complete
)paren
(brace
r_if
c_cond
(paren
id|readl
c_func
(paren
op_amp
id|iwait-&gt;msg-&gt;body
(braket
l_int|0
)braket
)paren
op_rshift
l_int|24
)paren
id|rc
op_assign
id|readl
c_func
(paren
op_amp
id|iwait-&gt;msg-&gt;body
(braket
l_int|0
)braket
)paren
op_amp
l_int|0xff
suffix:semicolon
id|i2o_flush_reply
c_func
(paren
id|c
comma
id|iwait-&gt;m
)paren
suffix:semicolon
id|i2o_exec_wait_free
c_func
(paren
id|iwait
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * We cannot remove it now. This is important. When it does&n;&t;&t; * terminate (which it must do if the controller has not&n;&t;&t; * died...) then it will otherwise scribble on stuff.&n;&t;&t; *&n;&t;&t; * FIXME: try abort message&n;&t;&t; */
r_if
c_cond
(paren
id|dma
)paren
id|dma-&gt;virt
op_assign
l_int|NULL
suffix:semicolon
id|rc
op_assign
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_msg_post_wait_complete - Reply to a i2o_msg_post request from IOP&n; *&t;@c: I2O controller which answers&n; *&t;@m: message id&n; *&t;@msg: pointer to the I2O reply message&n; *&n; *&t;This function is called in interrupt context only. If the reply reached&n; *&t;before the timeout, the i2o_exec_wait struct is filled with the message&n; *&t;and the task will be waked up. The task is now responsible for returning&n; *&t;the message m back to the controller! If the message reaches us after&n; *&t;the timeout clean up the i2o_exec_wait struct (including allocated&n; *&t;DMA buffer).&n; *&n; *&t;Return 0 on success and if the message m should not be given back to the&n; *&t;I2O controller, or &gt;0 on success and if the message should be given back&n; *&t;afterwords. Returns negative error code on failure. In this case the&n; *&t;message must also be given back to the controller.&n; */
DECL|function|i2o_msg_post_wait_complete
r_static
r_int
id|i2o_msg_post_wait_complete
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
id|u32
id|m
comma
r_struct
id|i2o_message
op_star
id|msg
)paren
(brace
r_struct
id|i2o_exec_wait
op_star
id|wait
comma
op_star
id|tmp
suffix:semicolon
r_static
id|spinlock_t
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_int
id|rc
op_assign
l_int|1
suffix:semicolon
id|u32
id|context
suffix:semicolon
id|context
op_assign
id|readl
c_func
(paren
op_amp
id|msg-&gt;u.s.tcntxt
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We need to search through the i2o_exec_wait_list to see if the given&n;&t; * message is still outstanding. If not, it means that the IOP took&n;&t; * longer to respond to the message than we had allowed and timer has&n;&t; * already expired. Not much we can do about that except log it for&n;&t; * debug purposes, increase timeout, and recompile.&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|wait
comma
id|tmp
comma
op_amp
id|i2o_exec_wait_list
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|wait-&gt;tcntxt
op_eq
id|context
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|wait-&gt;list
)paren
suffix:semicolon
id|wait-&gt;m
op_assign
id|m
suffix:semicolon
id|wait-&gt;msg
op_assign
id|msg
suffix:semicolon
id|wait-&gt;complete
op_assign
l_int|1
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait-&gt;wq
)paren
(brace
id|wake_up_interruptible
c_func
(paren
id|wait-&gt;wq
)paren
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_struct
id|device
op_star
id|dev
suffix:semicolon
id|dev
op_assign
op_amp
id|c-&gt;pdev-&gt;dev
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;timedout reply received!&bslash;n&quot;
)paren
suffix:semicolon
id|i2o_dma_free
c_func
(paren
id|dev
comma
op_amp
id|wait-&gt;dma
)paren
suffix:semicolon
id|i2o_exec_wait_free
c_func
(paren
id|wait
)paren
suffix:semicolon
id|rc
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;i2o: Bogus reply in POST WAIT (tr-context: %08x)!&bslash;n&quot;
comma
id|context
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_exec_probe - Called if a new I2O device (executive class) appears&n; *&t;@dev: I2O device which should be probed&n; *&n; *&t;Registers event notification for every event from Executive device. The&n; *&t;return is always 0, because we want all devices of class Executive.&n; *&n; *&t;Returns 0 on success.&n; */
DECL|function|i2o_exec_probe
r_static
r_int
id|i2o_exec_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|i2o_device
op_star
id|i2o_dev
op_assign
id|to_i2o_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|i2o_event_register
c_func
(paren
id|i2o_dev
comma
op_amp
id|i2o_exec_driver
comma
l_int|0
comma
l_int|0xffffffff
)paren
suffix:semicolon
id|i2o_dev-&gt;iop-&gt;exec
op_assign
id|i2o_dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_exec_remove - Called on I2O device removal&n; *&t;@dev: I2O device which was removed&n; *&n; *&t;Unregisters event notification from Executive I2O device.&n; *&n; *&t;Returns 0 on success.&n; */
DECL|function|i2o_exec_remove
r_static
r_int
id|i2o_exec_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|i2o_event_register
c_func
(paren
id|to_i2o_device
c_func
(paren
id|dev
)paren
comma
op_amp
id|i2o_exec_driver
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_exec_lct_modified - Called on LCT NOTIFY reply&n; *&t;@c: I2O controller on which the LCT has modified&n; *&n; *&t;This function handles asynchronus LCT NOTIFY replies. It parses the&n; *&t;new LCT and if the buffer for the LCT was to small sends a LCT NOTIFY&n; *&t;again.&n; */
DECL|function|i2o_exec_lct_modified
r_static
r_void
id|i2o_exec_lct_modified
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
)paren
(brace
r_if
c_cond
(paren
id|i2o_device_parse_lct
c_func
(paren
id|c
)paren
op_eq
op_minus
id|EAGAIN
)paren
id|i2o_exec_lct_notify
c_func
(paren
id|c
comma
l_int|0
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_exec_reply -  I2O Executive reply handler&n; *&t;@c: I2O controller from which the reply comes&n; *&t;@m: message id&n; *&t;@msg: pointer to the I2O reply message&n; *&n; *&t;This function is always called from interrupt context. If a POST WAIT&n; *&t;reply was received, pass it to the complete function. If a LCT NOTIFY&n; *&t;reply was received, a new event is created to handle the update.&n; *&n; *&t;Returns 0 on success and if the reply should not be flushed or &gt; 0&n; *&t;on success and if the reply should be flushed. Returns negative error&n; *&t;code on failure and if the reply should be flushed.&n; */
DECL|function|i2o_exec_reply
r_static
r_int
id|i2o_exec_reply
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
id|u32
id|m
comma
r_struct
id|i2o_message
op_star
id|msg
)paren
(brace
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|msg-&gt;u.head
(braket
l_int|0
)braket
)paren
op_amp
id|MSG_FAIL
)paren
(brace
singleline_comment|// Fail bit is set
r_struct
id|i2o_message
op_star
id|pmsg
suffix:semicolon
multiline_comment|/* preserved message */
id|u32
id|pm
suffix:semicolon
id|pm
op_assign
id|le32_to_cpu
c_func
(paren
id|msg-&gt;body
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|pmsg
op_assign
id|i2o_msg_in_to_virt
c_func
(paren
id|c
comma
id|pm
)paren
suffix:semicolon
id|i2o_report_status
c_func
(paren
id|KERN_INFO
comma
l_string|&quot;i2o_core&quot;
comma
id|msg
)paren
suffix:semicolon
multiline_comment|/* Release the preserved msg by resubmitting it as a NOP */
id|i2o_msg_nop
c_func
(paren
id|c
comma
id|pm
)paren
suffix:semicolon
multiline_comment|/* If reply to i2o_post_wait failed, return causes a timeout */
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|msg-&gt;u.s.tcntxt
)paren
op_amp
l_int|0x80000000
)paren
r_return
id|i2o_msg_post_wait_complete
c_func
(paren
id|c
comma
id|m
comma
id|msg
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|le32_to_cpu
c_func
(paren
id|msg-&gt;u.head
(braket
l_int|1
)braket
)paren
op_rshift
l_int|24
)paren
op_eq
id|I2O_CMD_LCT_NOTIFY
)paren
(brace
r_struct
id|work_struct
op_star
id|work
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: LCT notify received&bslash;n&quot;
comma
id|c-&gt;name
)paren
suffix:semicolon
id|work
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|work
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|work
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|INIT_WORK
c_func
(paren
id|work
comma
(paren
r_void
(paren
op_star
)paren
(paren
r_void
op_star
)paren
)paren
id|i2o_exec_lct_modified
comma
id|c
)paren
suffix:semicolon
id|queue_work
c_func
(paren
id|i2o_exec_driver.event_queue
comma
id|work
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If this happens, we want to dump the message to the syslog so&n;&t; * it can be sent back to the card manufacturer by the end user&n;&t; * to aid in debugging.&n;&t; *&n;&t; */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Unsolicited message reply sent to core!&quot;
l_string|&quot;Message dumped to syslog&bslash;n&quot;
comma
id|c-&gt;name
)paren
suffix:semicolon
id|i2o_dump_message
c_func
(paren
id|msg
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;i2o_exec_event - Event handling function&n; *&t;@evt: Event which occurs&n; *&n; *&t;Handles events send by the Executive device. At the moment does not do&n; *&t;anything useful.&n; */
DECL|function|i2o_exec_event
r_static
r_void
id|i2o_exec_event
c_func
(paren
r_struct
id|i2o_event
op_star
id|evt
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Event received from device: %d&bslash;n&quot;
comma
id|evt-&gt;i2o_dev-&gt;lct_data.tid
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|evt
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_exec_lct_get - Get the IOP&squot;s Logical Configuration Table&n; *&t;@c: I2O controller from which the LCT should be fetched&n; *&n; *&t;Send a LCT NOTIFY request to the controller, and wait&n; *&t;I2O_TIMEOUT_LCT_GET seconds until arrival of response. If the LCT is&n; *&t;to large, retry it.&n; *&n; *&t;Returns 0 on success or negative error code on failure.&n; */
DECL|function|i2o_exec_lct_get
r_int
id|i2o_exec_lct_get
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
)paren
(brace
r_struct
id|i2o_message
op_star
id|msg
suffix:semicolon
id|u32
id|m
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|rc
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|I2O_LCT_GET_TRIES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|m
op_assign
id|i2o_msg_get_wait
c_func
(paren
id|c
comma
op_amp
id|msg
comma
id|I2O_TIMEOUT_MESSAGE_GET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m
op_eq
id|I2O_QUEUE_EMPTY
)paren
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
id|writel
c_func
(paren
id|EIGHT_WORD_MSG_SIZE
op_or
id|SGL_OFFSET_6
comma
op_amp
id|msg-&gt;u.head
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|writel
c_func
(paren
id|I2O_CMD_LCT_NOTIFY
op_lshift
l_int|24
op_or
id|HOST_TID
op_lshift
l_int|12
op_or
id|ADAPTER_TID
comma
op_amp
id|msg-&gt;u.head
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0xffffffff
comma
op_amp
id|msg-&gt;body
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0x00000000
comma
op_amp
id|msg-&gt;body
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0xd0000000
op_or
id|c-&gt;dlct.len
comma
op_amp
id|msg-&gt;body
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|writel
c_func
(paren
id|c-&gt;dlct.phys
comma
op_amp
id|msg-&gt;body
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|rc
op_assign
id|i2o_msg_post_wait
c_func
(paren
id|c
comma
id|m
comma
id|I2O_TIMEOUT_LCT_GET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
r_break
suffix:semicolon
id|rc
op_assign
id|i2o_device_parse_lct
c_func
(paren
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
op_minus
id|EAGAIN
)paren
r_break
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;i2o_exec_lct_notify - Send a asynchronus LCT NOTIFY request&n; *&t;@c: I2O controller to which the request should be send&n; *&t;@change_ind: change indicator&n; *&n; *&t;This function sends a LCT NOTIFY request to the I2O controller with&n; *&t;the change indicator change_ind. If the change_ind == 0 the controller&n; *&t;replies immediately after the request. If change_ind &gt; 0 the reply is&n; *&t;send after change indicator of the LCT is &gt; change_ind.&n; */
DECL|function|i2o_exec_lct_notify
r_static
r_int
id|i2o_exec_lct_notify
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
id|u32
id|change_ind
)paren
(brace
id|i2o_status_block
op_star
id|sb
op_assign
id|c-&gt;status_block.virt
suffix:semicolon
r_struct
id|device
op_star
id|dev
suffix:semicolon
r_struct
id|i2o_message
op_star
id|msg
suffix:semicolon
id|u32
id|m
suffix:semicolon
id|dev
op_assign
op_amp
id|c-&gt;pdev-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
id|i2o_dma_realloc
c_func
(paren
id|dev
comma
op_amp
id|c-&gt;dlct
comma
id|sb-&gt;expected_lct_size
comma
id|GFP_KERNEL
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|m
op_assign
id|i2o_msg_get_wait
c_func
(paren
id|c
comma
op_amp
id|msg
comma
id|I2O_TIMEOUT_MESSAGE_GET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m
op_eq
id|I2O_QUEUE_EMPTY
)paren
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
id|writel
c_func
(paren
id|EIGHT_WORD_MSG_SIZE
op_or
id|SGL_OFFSET_6
comma
op_amp
id|msg-&gt;u.head
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|writel
c_func
(paren
id|I2O_CMD_LCT_NOTIFY
op_lshift
l_int|24
op_or
id|HOST_TID
op_lshift
l_int|12
op_or
id|ADAPTER_TID
comma
op_amp
id|msg-&gt;u.head
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|writel
c_func
(paren
id|i2o_exec_driver.context
comma
op_amp
id|msg-&gt;u.s.icntxt
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
op_amp
id|msg-&gt;u.s.tcntxt
)paren
suffix:semicolon
multiline_comment|/* FIXME */
id|writel
c_func
(paren
l_int|0xffffffff
comma
op_amp
id|msg-&gt;body
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|writel
c_func
(paren
id|change_ind
comma
op_amp
id|msg-&gt;body
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0xd0000000
op_or
id|c-&gt;dlct.len
comma
op_amp
id|msg-&gt;body
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|writel
c_func
(paren
id|c-&gt;dlct.phys
comma
op_amp
id|msg-&gt;body
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|i2o_msg_post
c_func
(paren
id|c
comma
id|m
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Exec OSM driver struct */
DECL|variable|i2o_exec_driver
r_struct
id|i2o_driver
id|i2o_exec_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;exec-osm&quot;
comma
dot
id|reply
op_assign
id|i2o_exec_reply
comma
dot
id|event
op_assign
id|i2o_exec_event
comma
dot
id|classes
op_assign
id|i2o_exec_class_id
comma
dot
id|driver
op_assign
(brace
dot
id|probe
op_assign
id|i2o_exec_probe
comma
dot
id|remove
op_assign
id|i2o_exec_remove
comma
)brace
comma
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_exec_init - Registers the Exec OSM&n; *&n; *&t;Registers the Exec OSM in the I2O core.&n; *&n; *&t;Returns 0 on success or negative error code on failure.&n; */
DECL|function|i2o_exec_init
r_int
id|__init
id|i2o_exec_init
c_func
(paren
r_void
)paren
(brace
r_return
id|i2o_driver_register
c_func
(paren
op_amp
id|i2o_exec_driver
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_exec_exit - Removes the Exec OSM&n; *&n; *&t;Unregisters the Exec OSM from the I2O core.&n; */
DECL|function|i2o_exec_exit
r_void
id|__exit
id|i2o_exec_exit
c_func
(paren
r_void
)paren
(brace
id|i2o_driver_unregister
c_func
(paren
op_amp
id|i2o_exec_driver
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|i2o_msg_post_wait_mem
id|EXPORT_SYMBOL
c_func
(paren
id|i2o_msg_post_wait_mem
)paren
suffix:semicolon
DECL|variable|i2o_exec_lct_get
id|EXPORT_SYMBOL
c_func
(paren
id|i2o_exec_lct_get
)paren
suffix:semicolon
eof
