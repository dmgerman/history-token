multiline_comment|/* pluto.c: SparcSTORAGE Array SCSI host adapter driver.&n; *&n; * Copyright (C) 1997,1998,1999 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_KMOD
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;../fc4/fcp_impl.h&quot;
macro_line|#include &quot;pluto.h&quot;
macro_line|#include &lt;linux/module.h&gt;
multiline_comment|/* #define PLUTO_DEBUG */
DECL|macro|pluto_printk
mdefine_line|#define pluto_printk printk (&quot;PLUTO %s: &quot;, fc-&gt;name); printk
macro_line|#ifdef PLUTO_DEBUG
DECL|macro|PLD
mdefine_line|#define PLD(x)  pluto_printk x;
DECL|macro|PLND
mdefine_line|#define PLND(x) printk (&quot;PLUTO: &quot;); printk x;
macro_line|#else
DECL|macro|PLD
mdefine_line|#define PLD(x)
DECL|macro|PLND
mdefine_line|#define PLND(x)
macro_line|#endif
DECL|struct|ctrl_inquiry
r_static
r_struct
id|ctrl_inquiry
(brace
DECL|member|host
r_struct
id|Scsi_Host
id|host
suffix:semicolon
DECL|member|pluto
r_struct
id|pluto
id|pluto
suffix:semicolon
DECL|member|cmd
id|Scsi_Cmnd
id|cmd
suffix:semicolon
DECL|member|inquiry
r_char
id|inquiry
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|fc
id|fc_channel
op_star
id|fc
suffix:semicolon
DECL|variable|__initdata
)brace
op_star
id|fcs
id|__initdata
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|fcscount
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
id|atomic_t
id|fcss
id|__initdata
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
DECL|variable|fc_sem
id|DECLARE_MUTEX_LOCKED
c_func
(paren
id|fc_sem
)paren
suffix:semicolon
r_static
r_int
id|pluto_encode_addr
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
id|u16
op_star
id|addr
comma
id|fc_channel
op_star
id|fc
comma
id|fcp_cmnd
op_star
id|fcmd
)paren
suffix:semicolon
DECL|function|pluto_detect_timeout
r_static
r_void
id|__init
id|pluto_detect_timeout
c_func
(paren
r_int
r_int
id|data
)paren
(brace
id|PLND
c_func
(paren
(paren
l_string|&quot;Timeout&bslash;n&quot;
)paren
)paren
id|up
c_func
(paren
op_amp
id|fc_sem
)paren
suffix:semicolon
)brace
DECL|function|pluto_detect_done
r_static
r_void
id|__init
id|pluto_detect_done
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
multiline_comment|/* Do nothing */
)brace
DECL|function|pluto_detect_scsi_done
r_static
r_void
id|__init
id|pluto_detect_scsi_done
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
id|SCpnt-&gt;request-&gt;rq_status
op_assign
id|RQ_SCSI_DONE
suffix:semicolon
id|PLND
c_func
(paren
(paren
l_string|&quot;Detect done %08lx&bslash;n&quot;
comma
(paren
r_int
)paren
id|SCpnt
)paren
)paren
r_if
c_cond
(paren
id|atomic_dec_and_test
(paren
op_amp
id|fcss
)paren
)paren
id|up
c_func
(paren
op_amp
id|fc_sem
)paren
suffix:semicolon
)brace
DECL|function|pluto_slave_configure
r_int
id|pluto_slave_configure
c_func
(paren
id|Scsi_Device
op_star
id|device
)paren
(brace
r_int
id|depth_to_use
suffix:semicolon
r_if
c_cond
(paren
id|device-&gt;tagged_supported
)paren
id|depth_to_use
op_assign
multiline_comment|/* 254 */
l_int|8
suffix:semicolon
r_else
id|depth_to_use
op_assign
l_int|2
suffix:semicolon
id|scsi_adjust_queue_depth
c_func
(paren
id|device
comma
(paren
id|device-&gt;tagged_supported
ques
c_cond
id|MSG_SIMPLE_TAG
suffix:colon
l_int|0
)paren
comma
id|depth_to_use
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Detect all SSAs attached to the machine.&n;   To be fast, do it on all online FC channels at the same time. */
DECL|function|pluto_detect
r_int
id|__init
id|pluto_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
r_int
id|i
comma
id|retry
comma
id|nplutos
suffix:semicolon
id|fc_channel
op_star
id|fc
suffix:semicolon
id|Scsi_Device
id|dev
suffix:semicolon
r_struct
id|timer_list
id|fc_timer
op_assign
id|TIMER_INITIALIZER
c_func
(paren
id|pluto_detect_timeout
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|tpnt-&gt;proc_name
op_assign
l_string|&quot;pluto&quot;
suffix:semicolon
id|fcscount
op_assign
l_int|0
suffix:semicolon
id|for_each_online_fc_channel
c_func
(paren
id|fc
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fc-&gt;posmap
)paren
id|fcscount
op_increment
suffix:semicolon
)brace
id|PLND
c_func
(paren
(paren
l_string|&quot;%d channels online&bslash;n&quot;
comma
id|fcscount
)paren
)paren
r_if
c_cond
(paren
op_logical_neg
id|fcscount
)paren
(brace
macro_line|#if defined(MODULE) &amp;&amp; defined(CONFIG_FC4_SOC_MODULE) &amp;&amp; defined(CONFIG_KMOD)
id|request_module
c_func
(paren
l_string|&quot;soc&quot;
)paren
suffix:semicolon
id|for_each_online_fc_channel
c_func
(paren
id|fc
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fc-&gt;posmap
)paren
id|fcscount
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|fcscount
)paren
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
id|fcs
op_assign
(paren
r_struct
id|ctrl_inquiry
op_star
)paren
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|ctrl_inquiry
)paren
op_star
id|fcscount
comma
id|GFP_DMA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fcs
)paren
(brace
id|printk
(paren
l_string|&quot;PLUTO: Not enough memory to probe&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|memset
(paren
id|fcs
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ctrl_inquiry
)paren
op_star
id|fcscount
)paren
suffix:semicolon
id|memset
(paren
op_amp
id|dev
comma
l_int|0
comma
r_sizeof
(paren
id|dev
)paren
)paren
suffix:semicolon
id|atomic_set
(paren
op_amp
id|fcss
comma
id|fcscount
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|for_each_online_fc_channel
c_func
(paren
id|fc
)paren
(brace
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
r_struct
id|pluto
op_star
id|pluto
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|fcscount
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|fc-&gt;posmap
)paren
r_continue
suffix:semicolon
id|PLD
c_func
(paren
(paren
l_string|&quot;trying to find SSA&bslash;n&quot;
)paren
)paren
multiline_comment|/* If this is already registered to some other SCSI host, then it cannot be pluto */
r_if
c_cond
(paren
id|fc-&gt;scsi_name
(braket
l_int|0
)braket
)paren
r_continue
suffix:semicolon
id|memcpy
(paren
id|fc-&gt;scsi_name
comma
l_string|&quot;SSA&quot;
comma
l_int|4
)paren
suffix:semicolon
id|fcs
(braket
id|i
)braket
dot
id|fc
op_assign
id|fc
suffix:semicolon
id|fc-&gt;can_queue
op_assign
id|PLUTO_CAN_QUEUE
suffix:semicolon
id|fc-&gt;rsp_size
op_assign
l_int|64
suffix:semicolon
id|fc-&gt;encode_addr
op_assign
id|pluto_encode_addr
suffix:semicolon
id|fc
op_member_access_from_pointer
id|fcp_register
c_func
(paren
id|fc
comma
id|TYPE_SCSI_FCP
comma
l_int|0
)paren
suffix:semicolon
id|SCpnt
op_assign
op_amp
(paren
id|fcs
(braket
id|i
)braket
dot
id|cmd
)paren
suffix:semicolon
id|host
op_assign
op_amp
(paren
id|fcs
(braket
id|i
)braket
dot
id|host
)paren
suffix:semicolon
id|pluto
op_assign
(paren
r_struct
id|pluto
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
id|pluto-&gt;fc
op_assign
id|fc
suffix:semicolon
id|SCpnt-&gt;host
op_assign
id|host
suffix:semicolon
id|SCpnt-&gt;cmnd
(braket
l_int|0
)braket
op_assign
id|INQUIRY
suffix:semicolon
id|SCpnt-&gt;cmnd
(braket
l_int|4
)braket
op_assign
l_int|255
suffix:semicolon
multiline_comment|/* FC layer requires this, so that SCpnt-&gt;device-&gt;tagged_supported is initially 0 */
id|SCpnt-&gt;device
op_assign
op_amp
id|dev
suffix:semicolon
id|SCpnt-&gt;cmd_len
op_assign
id|COMMAND_SIZE
c_func
(paren
id|INQUIRY
)paren
suffix:semicolon
id|SCpnt-&gt;request-&gt;rq_status
op_assign
id|RQ_SCSI_BUSY
suffix:semicolon
id|SCpnt-&gt;done
op_assign
id|pluto_detect_done
suffix:semicolon
id|SCpnt-&gt;bufflen
op_assign
l_int|256
suffix:semicolon
id|SCpnt-&gt;buffer
op_assign
id|fcs
(braket
id|i
)braket
dot
id|inquiry
suffix:semicolon
id|SCpnt-&gt;request_bufflen
op_assign
l_int|256
suffix:semicolon
id|SCpnt-&gt;request_buffer
op_assign
id|fcs
(braket
id|i
)braket
dot
id|inquiry
suffix:semicolon
id|PLD
c_func
(paren
(paren
l_string|&quot;set up %d %08lx&bslash;n&quot;
comma
id|i
comma
(paren
r_int
)paren
id|SCpnt
)paren
)paren
id|i
op_increment
suffix:semicolon
)brace
r_for
c_loop
(paren
id|retry
op_assign
l_int|0
suffix:semicolon
id|retry
OL
l_int|5
suffix:semicolon
id|retry
op_increment
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
id|fcscount
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fcs
(braket
id|i
)braket
dot
id|fc
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|fcs
(braket
id|i
)braket
dot
id|cmd.request-&gt;rq_status
op_ne
id|RQ_SCSI_DONE
)paren
(brace
id|disable_irq
c_func
(paren
id|fcs
(braket
id|i
)braket
dot
id|fc-&gt;irq
)paren
suffix:semicolon
id|PLND
c_func
(paren
(paren
l_string|&quot;queuecommand %d %d&bslash;n&quot;
comma
id|retry
comma
id|i
)paren
)paren
id|fcp_scsi_queuecommand
(paren
op_amp
(paren
id|fcs
(braket
id|i
)braket
dot
id|cmd
)paren
comma
id|pluto_detect_scsi_done
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
id|fcs
(braket
id|i
)braket
dot
id|fc-&gt;irq
)paren
suffix:semicolon
)brace
)brace
id|fc_timer.expires
op_assign
id|jiffies
op_plus
l_int|10
op_star
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|fc_timer
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|fc_sem
)paren
suffix:semicolon
id|PLND
c_func
(paren
(paren
l_string|&quot;Woken up&bslash;n&quot;
)paren
)paren
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|fcss
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* All fc channels have answered us */
)brace
id|del_timer_sync
c_func
(paren
op_amp
id|fc_timer
)paren
suffix:semicolon
id|PLND
c_func
(paren
(paren
l_string|&quot;Finished search&bslash;n&quot;
)paren
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|nplutos
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|fcscount
suffix:semicolon
id|i
op_increment
)paren
(brace
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|fc
op_assign
id|fcs
(braket
id|i
)braket
dot
id|fc
)paren
)paren
r_break
suffix:semicolon
id|SCpnt
op_assign
op_amp
(paren
id|fcs
(braket
id|i
)braket
dot
id|cmd
)paren
suffix:semicolon
multiline_comment|/* Let FC mid-level free allocated resources */
id|SCpnt-&gt;done
(paren
id|SCpnt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|SCpnt-&gt;result
)paren
(brace
r_struct
id|pluto_inquiry
op_star
id|inq
suffix:semicolon
r_struct
id|pluto
op_star
id|pluto
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
id|inq
op_assign
(paren
r_struct
id|pluto_inquiry
op_star
)paren
id|fcs
(braket
id|i
)braket
dot
id|inquiry
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inq-&gt;dtype
op_amp
l_int|0x1f
)paren
op_eq
id|TYPE_PROCESSOR
op_logical_and
op_logical_neg
id|strncmp
(paren
id|inq-&gt;vendor_id
comma
l_string|&quot;SUN&quot;
comma
l_int|3
)paren
op_logical_and
op_logical_neg
id|strncmp
(paren
id|inq-&gt;product_id
comma
l_string|&quot;SSA&quot;
comma
l_int|3
)paren
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_int
op_star
id|ages
suffix:semicolon
id|ages
op_assign
id|kmalloc
(paren
(paren
(paren
id|inq-&gt;channels
op_plus
l_int|1
)paren
op_star
id|inq-&gt;targets
)paren
op_star
r_sizeof
(paren
r_int
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ages
)paren
r_continue
suffix:semicolon
id|host
op_assign
id|scsi_register
(paren
id|tpnt
comma
r_sizeof
(paren
r_struct
id|pluto
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host
)paren
(brace
id|kfree
c_func
(paren
id|ages
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|fc-&gt;module
)paren
)paren
(brace
id|kfree
c_func
(paren
id|ages
)paren
suffix:semicolon
id|scsi_unregister
c_func
(paren
id|host
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|nplutos
op_increment
suffix:semicolon
id|pluto
op_assign
(paren
r_struct
id|pluto
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
id|host-&gt;max_id
op_assign
id|inq-&gt;targets
suffix:semicolon
id|host-&gt;max_channel
op_assign
id|inq-&gt;channels
suffix:semicolon
id|host-&gt;irq
op_assign
id|fc-&gt;irq
suffix:semicolon
macro_line|#ifdef __sparc_v9__
id|host-&gt;unchecked_isa_dma
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
id|fc-&gt;channels
op_assign
id|inq-&gt;channels
op_plus
l_int|1
suffix:semicolon
id|fc-&gt;targets
op_assign
id|inq-&gt;targets
suffix:semicolon
id|fc-&gt;ages
op_assign
id|ages
suffix:semicolon
id|memset
(paren
id|ages
comma
l_int|0
comma
(paren
(paren
id|inq-&gt;channels
op_plus
l_int|1
)paren
op_star
id|inq-&gt;targets
)paren
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|pluto-&gt;fc
op_assign
id|fc
suffix:semicolon
id|memcpy
(paren
id|pluto-&gt;rev_str
comma
id|inq-&gt;revision
comma
l_int|4
)paren
suffix:semicolon
id|pluto-&gt;rev_str
(braket
l_int|4
)braket
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
id|strchr
(paren
id|pluto-&gt;rev_str
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
op_star
id|p
op_assign
l_int|0
suffix:semicolon
id|memcpy
(paren
id|pluto-&gt;fw_rev_str
comma
id|inq-&gt;fw_revision
comma
l_int|4
)paren
suffix:semicolon
id|pluto-&gt;fw_rev_str
(braket
l_int|4
)braket
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
id|strchr
(paren
id|pluto-&gt;fw_rev_str
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
op_star
id|p
op_assign
l_int|0
suffix:semicolon
id|memcpy
(paren
id|pluto-&gt;serial_str
comma
id|inq-&gt;serial
comma
l_int|12
)paren
suffix:semicolon
id|pluto-&gt;serial_str
(braket
l_int|12
)braket
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
id|strchr
(paren
id|pluto-&gt;serial_str
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
op_star
id|p
op_assign
l_int|0
suffix:semicolon
id|PLD
c_func
(paren
(paren
l_string|&quot;Found SSA rev %s fw rev %s serial %s %dx%d&bslash;n&quot;
comma
id|pluto-&gt;rev_str
comma
id|pluto-&gt;fw_rev_str
comma
id|pluto-&gt;serial_str
comma
id|host-&gt;max_channel
comma
id|host-&gt;max_id
)paren
)paren
)brace
r_else
id|fc
op_member_access_from_pointer
id|fcp_register
c_func
(paren
id|fc
comma
id|TYPE_SCSI_FCP
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
id|fc
op_member_access_from_pointer
id|fcp_register
c_func
(paren
id|fc
comma
id|TYPE_SCSI_FCP
comma
l_int|1
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
(paren
r_char
op_star
)paren
id|fcs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nplutos
)paren
id|printk
(paren
l_string|&quot;PLUTO: Total of %d SparcSTORAGE Arrays found&bslash;n&quot;
comma
id|nplutos
)paren
suffix:semicolon
r_return
id|nplutos
suffix:semicolon
)brace
DECL|function|pluto_release
r_int
id|pluto_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
(brace
r_struct
id|pluto
op_star
id|pluto
op_assign
(paren
r_struct
id|pluto
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
id|fc_channel
op_star
id|fc
op_assign
id|pluto-&gt;fc
suffix:semicolon
r_if
c_cond
(paren
id|fc-&gt;module
)paren
id|__MOD_DEC_USE_COUNT
c_func
(paren
id|fc-&gt;module
)paren
suffix:semicolon
id|fc
op_member_access_from_pointer
id|fcp_register
c_func
(paren
id|fc
comma
id|TYPE_SCSI_FCP
comma
l_int|1
)paren
suffix:semicolon
id|PLND
c_func
(paren
(paren
l_string|&quot; releasing pluto.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|kfree
(paren
id|fc-&gt;ages
)paren
suffix:semicolon
id|PLND
c_func
(paren
(paren
l_string|&quot;released pluto!&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pluto_info
r_const
r_char
op_star
id|pluto_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
(brace
r_static
r_char
id|buf
(braket
l_int|128
)braket
comma
op_star
id|p
suffix:semicolon
r_struct
id|pluto
op_star
id|pluto
op_assign
(paren
r_struct
id|pluto
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;SUN SparcSTORAGE Array %s fw %s serial %s %dx%d on %s&quot;
comma
id|pluto-&gt;rev_str
comma
id|pluto-&gt;fw_rev_str
comma
id|pluto-&gt;serial_str
comma
id|host-&gt;max_channel
comma
id|host-&gt;max_id
comma
id|pluto-&gt;fc-&gt;name
)paren
suffix:semicolon
macro_line|#ifdef __sparc__
id|p
op_assign
id|strchr
c_func
(paren
id|buf
comma
l_int|0
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot; PROM node %x&quot;
comma
id|pluto-&gt;fc-&gt;dev-&gt;prom_node
)paren
suffix:semicolon
macro_line|#endif&t;
r_return
id|buf
suffix:semicolon
)brace
multiline_comment|/* SSA uses this FC4S addressing:&n;   switch (addr[0])&n;   {&n;   case 0: CONTROLLER - All of addr[1]..addr[3] has to be 0&n;   case 1: SINGLE DISK - addr[1] channel, addr[2] id, addr[3] 0&n;   case 2: DISK GROUP - ???&n;   }&n;   &n;   So that SCSI mid-layer can access to these, we reserve&n;   channel 0 id 0 lun 0 for CONTROLLER&n;   and channels 1 .. max_channel are normal single disks.&n; */
DECL|function|pluto_encode_addr
r_static
r_int
id|pluto_encode_addr
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
id|u16
op_star
id|addr
comma
id|fc_channel
op_star
id|fc
comma
id|fcp_cmnd
op_star
id|fcmd
)paren
(brace
id|PLND
c_func
(paren
(paren
l_string|&quot;encode addr %d %d %d&bslash;n&quot;
comma
id|SCpnt-&gt;channel
comma
id|SCpnt-&gt;target
comma
id|SCpnt-&gt;cmnd
(braket
l_int|1
)braket
op_amp
l_int|0xe0
)paren
)paren
multiline_comment|/* We don&squot;t support LUNs - neither does SSA :) */
r_if
c_cond
(paren
id|SCpnt-&gt;cmnd
(braket
l_int|1
)braket
op_amp
l_int|0xe0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|SCpnt-&gt;channel
)paren
(brace
r_if
c_cond
(paren
id|SCpnt-&gt;target
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|memset
(paren
id|addr
comma
l_int|0
comma
l_int|4
op_star
r_sizeof
(paren
id|u16
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|addr
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
id|addr
(braket
l_int|1
)braket
op_assign
id|SCpnt-&gt;channel
op_minus
l_int|1
suffix:semicolon
id|addr
(braket
l_int|2
)braket
op_assign
id|SCpnt-&gt;target
suffix:semicolon
id|addr
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* We&squot;re Point-to-Point, so target it to the default DID */
id|fcmd-&gt;did
op_assign
id|fc-&gt;did
suffix:semicolon
id|PLND
c_func
(paren
(paren
l_string|&quot;trying %04x%04x%04x%04x&bslash;n&quot;
comma
id|addr
(braket
l_int|0
)braket
comma
id|addr
(braket
l_int|1
)braket
comma
id|addr
(braket
l_int|2
)braket
comma
id|addr
(braket
l_int|3
)braket
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
id|PLUTO
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
eof
