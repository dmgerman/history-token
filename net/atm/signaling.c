multiline_comment|/* net/atm/signaling.c - ATM signaling */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#include &lt;linux/errno.h&gt;&t;/* error codes */
macro_line|#include &lt;linux/kernel.h&gt;&t;/* printk */
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/sched.h&gt;&t;/* jiffies and HZ */
macro_line|#include &lt;linux/atm.h&gt;&t;&t;/* ATM stuff */
macro_line|#include &lt;linux/atmsap.h&gt;
macro_line|#include &lt;linux/atmsvc.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &quot;resources.h&quot;
macro_line|#include &quot;signaling.h&quot;
DECL|macro|WAIT_FOR_DEMON
macro_line|#undef WAIT_FOR_DEMON&t;&t;/* #define this if system calls on SVC sockets&n;&t;&t;&t;&t;   should block until the demon runs.&n;&t;&t;&t;&t;   Danger: may cause nasty hangs if the demon&n;&t;&t;&t;&t;   crashes. */
macro_line|#if 0
mdefine_line|#define DPRINTK(format,args...) printk(KERN_DEBUG format,##args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format,args...)
macro_line|#endif
DECL|variable|sigd
r_struct
id|atm_vcc
op_star
id|sigd
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef WAIT_FOR_DEMON
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|sigd_sleep
)paren
suffix:semicolon
macro_line|#endif
DECL|function|sigd_put_skb
r_static
r_void
id|sigd_put_skb
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
macro_line|#ifdef WAIT_FOR_DEMON
r_static
r_int
r_int
id|silence
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|sigd_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|sigd
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|silence
)paren
op_logical_or
id|silence
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;atmsvc: waiting for signaling demon &quot;
l_string|&quot;...&bslash;n&quot;
)paren
suffix:semicolon
id|silence
op_assign
(paren
id|jiffies
op_plus
l_int|30
op_star
id|HZ
)paren
op_or
l_int|1
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|sigd_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
op_logical_neg
id|sigd
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;atmsvc: no signaling demon&bslash;n&quot;
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
id|atm_force_charge
c_func
(paren
id|sigd
comma
id|skb-&gt;truesize
)paren
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|sk_atm
c_func
(paren
id|sigd
)paren
op_member_access_from_pointer
id|sk_receive_queue
comma
id|skb
)paren
suffix:semicolon
id|sk_atm
c_func
(paren
id|sigd
)paren
op_member_access_from_pointer
id|sk_data_ready
c_func
(paren
id|sk_atm
c_func
(paren
id|sigd
)paren
comma
id|skb-&gt;len
)paren
suffix:semicolon
)brace
DECL|function|modify_qos
r_static
r_void
id|modify_qos
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|atmsvc_msg
op_star
id|msg
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|ATM_VF_RELEASED
comma
op_amp
id|vcc-&gt;flags
)paren
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|ATM_VF_READY
comma
op_amp
id|vcc-&gt;flags
)paren
)paren
r_return
suffix:semicolon
id|msg-&gt;type
op_assign
id|as_error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vcc-&gt;dev-&gt;ops-&gt;change_qos
)paren
id|msg-&gt;reply
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_else
(brace
multiline_comment|/* should lock VCC */
id|msg-&gt;reply
op_assign
id|vcc-&gt;dev-&gt;ops
op_member_access_from_pointer
id|change_qos
c_func
(paren
id|vcc
comma
op_amp
id|msg-&gt;qos
comma
id|msg-&gt;reply
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|msg-&gt;reply
)paren
id|msg-&gt;type
op_assign
id|as_okay
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Should probably just turn around the old skb. But the, the buffer&n;&t; * space accounting needs to follow the change too. Maybe later.&n;&t; */
r_while
c_loop
(paren
op_logical_neg
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
r_sizeof
(paren
r_struct
id|atmsvc_msg
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
r_struct
id|atmsvc_msg
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|atmsvc_msg
)paren
)paren
op_assign
op_star
id|msg
suffix:semicolon
id|sigd_put_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|sigd_send
r_static
r_int
id|sigd_send
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|atmsvc_msg
op_star
id|msg
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|session_vcc
suffix:semicolon
r_struct
id|sock
op_star
id|sk
suffix:semicolon
id|msg
op_assign
(paren
r_struct
id|atmsvc_msg
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|atomic_sub
c_func
(paren
id|skb-&gt;truesize
comma
op_amp
id|sk_atm
c_func
(paren
id|vcc
)paren
op_member_access_from_pointer
id|sk_wmem_alloc
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;sigd_send %d (0x%lx)&bslash;n&quot;
comma
(paren
r_int
)paren
id|msg-&gt;type
comma
(paren
r_int
r_int
)paren
id|msg-&gt;vcc
)paren
suffix:semicolon
id|vcc
op_assign
op_star
(paren
r_struct
id|atm_vcc
op_star
op_star
)paren
op_amp
id|msg-&gt;vcc
suffix:semicolon
id|sk
op_assign
id|sk_atm
c_func
(paren
id|vcc
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|msg-&gt;type
)paren
(brace
r_case
id|as_okay
suffix:colon
id|sk-&gt;sk_err
op_assign
op_minus
id|msg-&gt;reply
suffix:semicolon
id|clear_bit
c_func
(paren
id|ATM_VF_WAITING
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|vcc-&gt;local.sas_addr.prv
op_logical_and
op_logical_neg
op_star
id|vcc-&gt;local.sas_addr.pub
)paren
(brace
id|vcc-&gt;local.sas_family
op_assign
id|AF_ATMSVC
suffix:semicolon
id|memcpy
c_func
(paren
id|vcc-&gt;local.sas_addr.prv
comma
id|msg-&gt;local.sas_addr.prv
comma
id|ATM_ESA_LEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|vcc-&gt;local.sas_addr.pub
comma
id|msg-&gt;local.sas_addr.pub
comma
id|ATM_E164_LEN
op_plus
l_int|1
)paren
suffix:semicolon
)brace
id|session_vcc
op_assign
id|vcc-&gt;session
ques
c_cond
id|vcc-&gt;session
suffix:colon
id|vcc
suffix:semicolon
r_if
c_cond
(paren
id|session_vcc-&gt;vpi
op_logical_or
id|session_vcc-&gt;vci
)paren
r_break
suffix:semicolon
id|session_vcc-&gt;itf
op_assign
id|msg-&gt;pvc.sap_addr.itf
suffix:semicolon
id|session_vcc-&gt;vpi
op_assign
id|msg-&gt;pvc.sap_addr.vpi
suffix:semicolon
id|session_vcc-&gt;vci
op_assign
id|msg-&gt;pvc.sap_addr.vci
suffix:semicolon
r_if
c_cond
(paren
id|session_vcc-&gt;vpi
op_logical_or
id|session_vcc-&gt;vci
)paren
id|session_vcc-&gt;qos
op_assign
id|msg-&gt;qos
suffix:semicolon
r_break
suffix:semicolon
r_case
id|as_error
suffix:colon
id|clear_bit
c_func
(paren
id|ATM_VF_REGIS
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|ATM_VF_READY
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
id|sk-&gt;sk_err
op_assign
op_minus
id|msg-&gt;reply
suffix:semicolon
id|clear_bit
c_func
(paren
id|ATM_VF_WAITING
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|as_indicate
suffix:colon
id|vcc
op_assign
op_star
(paren
r_struct
id|atm_vcc
op_star
op_star
)paren
op_amp
id|msg-&gt;listen_vcc
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;as_indicate!!!&bslash;n&quot;
)paren
suffix:semicolon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;sk_ack_backlog
op_eq
id|sk-&gt;sk_max_ack_backlog
)paren
(brace
id|sigd_enq
c_func
(paren
l_int|NULL
comma
id|as_reject
comma
id|vcc
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_goto
id|as_indicate_complete
suffix:semicolon
)brace
id|sk-&gt;sk_ack_backlog
op_increment
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;sk_receive_queue
comma
id|skb
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;waking sk-&gt;sk_sleep 0x%p&bslash;n&quot;
comma
id|sk-&gt;sk_sleep
)paren
suffix:semicolon
id|sk
op_member_access_from_pointer
id|sk_state_change
c_func
(paren
id|sk
)paren
suffix:semicolon
id|as_indicate_complete
suffix:colon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|as_close
suffix:colon
id|set_bit
c_func
(paren
id|ATM_VF_RELEASED
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
id|vcc_release_async
c_func
(paren
id|vcc
comma
id|msg-&gt;reply
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|as_modify
suffix:colon
id|modify_qos
c_func
(paren
id|vcc
comma
id|msg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|as_addparty
suffix:colon
r_case
id|as_dropparty
suffix:colon
id|sk-&gt;sk_err_soft
op_assign
id|msg-&gt;reply
suffix:semicolon
multiline_comment|/* &lt; 0 failure, otherwise ep_ref */
id|clear_bit
c_func
(paren
id|ATM_VF_WAITING
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;sigd_send: bad message type %d&bslash;n&quot;
comma
(paren
r_int
)paren
id|msg-&gt;type
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|sk
op_member_access_from_pointer
id|sk_state_change
c_func
(paren
id|sk
)paren
suffix:semicolon
id|out
suffix:colon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sigd_enq2
r_void
id|sigd_enq2
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_enum
id|atmsvc_msg_type
id|type
comma
r_struct
id|atm_vcc
op_star
id|listen_vcc
comma
r_const
r_struct
id|sockaddr_atmpvc
op_star
id|pvc
comma
r_const
r_struct
id|sockaddr_atmsvc
op_star
id|svc
comma
r_const
r_struct
id|atm_qos
op_star
id|qos
comma
r_int
id|reply
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|atmsvc_msg
op_star
id|msg
suffix:semicolon
r_static
r_int
id|session
op_assign
l_int|0
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;sigd_enq %d (0x%p)&bslash;n&quot;
comma
(paren
r_int
)paren
id|type
comma
id|vcc
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
r_sizeof
(paren
r_struct
id|atmsvc_msg
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|msg
op_assign
(paren
r_struct
id|atmsvc_msg
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|atmsvc_msg
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|msg
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|msg
)paren
)paren
suffix:semicolon
id|msg-&gt;type
op_assign
id|type
suffix:semicolon
op_star
(paren
r_struct
id|atm_vcc
op_star
op_star
)paren
op_amp
id|msg-&gt;vcc
op_assign
id|vcc
suffix:semicolon
op_star
(paren
r_struct
id|atm_vcc
op_star
op_star
)paren
op_amp
id|msg-&gt;listen_vcc
op_assign
id|listen_vcc
suffix:semicolon
id|msg-&gt;reply
op_assign
id|reply
suffix:semicolon
r_if
c_cond
(paren
id|qos
)paren
id|msg-&gt;qos
op_assign
op_star
id|qos
suffix:semicolon
r_if
c_cond
(paren
id|vcc
)paren
id|msg-&gt;sap
op_assign
id|vcc-&gt;sap
suffix:semicolon
r_if
c_cond
(paren
id|svc
)paren
id|msg-&gt;svc
op_assign
op_star
id|svc
suffix:semicolon
r_if
c_cond
(paren
id|vcc
)paren
id|msg-&gt;local
op_assign
id|vcc-&gt;local
suffix:semicolon
r_if
c_cond
(paren
id|pvc
)paren
id|msg-&gt;pvc
op_assign
op_star
id|pvc
suffix:semicolon
r_if
c_cond
(paren
id|vcc
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
id|as_connect
op_logical_and
id|test_bit
c_func
(paren
id|ATM_VF_SESSION
comma
op_amp
id|vcc-&gt;flags
)paren
)paren
id|msg-&gt;session
op_assign
op_increment
id|session
suffix:semicolon
multiline_comment|/* every new pmp connect gets the next session number */
)brace
id|sigd_put_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vcc
)paren
id|set_bit
c_func
(paren
id|ATM_VF_REGIS
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
)brace
DECL|function|sigd_enq
r_void
id|sigd_enq
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_enum
id|atmsvc_msg_type
id|type
comma
r_struct
id|atm_vcc
op_star
id|listen_vcc
comma
r_const
r_struct
id|sockaddr_atmpvc
op_star
id|pvc
comma
r_const
r_struct
id|sockaddr_atmsvc
op_star
id|svc
)paren
(brace
id|sigd_enq2
c_func
(paren
id|vcc
comma
id|type
comma
id|listen_vcc
comma
id|pvc
comma
id|svc
comma
id|vcc
ques
c_cond
op_amp
id|vcc-&gt;qos
suffix:colon
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* other ISP applications may use &quot;reply&quot; */
)brace
DECL|function|purge_vcc
r_static
r_void
id|purge_vcc
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
(brace
r_if
c_cond
(paren
id|sk_atm
c_func
(paren
id|vcc
)paren
op_member_access_from_pointer
id|sk_family
op_eq
id|PF_ATMSVC
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
id|ATM_VF_META
comma
op_amp
id|vcc-&gt;flags
)paren
)paren
(brace
id|set_bit
c_func
(paren
id|ATM_VF_RELEASED
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
id|vcc_release_async
c_func
(paren
id|vcc
comma
op_minus
id|EUNATCH
)paren
suffix:semicolon
)brace
)brace
DECL|function|sigd_close
r_static
r_void
id|sigd_close
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
(brace
r_struct
id|hlist_node
op_star
id|node
suffix:semicolon
r_struct
id|sock
op_star
id|s
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;sigd_close&bslash;n&quot;
)paren
suffix:semicolon
id|sigd
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|skb_peek
c_func
(paren
op_amp
id|sk_atm
c_func
(paren
id|vcc
)paren
op_member_access_from_pointer
id|sk_receive_queue
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sigd_close: closing with requests pending&bslash;n&quot;
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|sk_atm
c_func
(paren
id|vcc
)paren
op_member_access_from_pointer
id|sk_receive_queue
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|vcc_sklist_lock
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
id|VCC_HTABLE_SIZE
suffix:semicolon
op_increment
id|i
)paren
(brace
r_struct
id|hlist_head
op_star
id|head
op_assign
op_amp
id|vcc_hash
(braket
id|i
)braket
suffix:semicolon
id|sk_for_each
c_func
(paren
id|s
comma
id|node
comma
id|head
)paren
(brace
r_struct
id|atm_vcc
op_star
id|vcc
op_assign
id|atm_sk
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vcc-&gt;dev
)paren
id|purge_vcc
c_func
(paren
id|vcc
)paren
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|vcc_sklist_lock
)paren
suffix:semicolon
)brace
DECL|variable|sigd_dev_ops
r_static
r_struct
id|atmdev_ops
id|sigd_dev_ops
op_assign
(brace
dot
id|close
op_assign
id|sigd_close
comma
dot
id|send
op_assign
id|sigd_send
)brace
suffix:semicolon
DECL|variable|sigd_dev
r_static
r_struct
id|atm_dev
id|sigd_dev
op_assign
(brace
dot
id|ops
op_assign
op_amp
id|sigd_dev_ops
comma
dot
id|type
op_assign
l_string|&quot;sig&quot;
comma
dot
id|number
op_assign
l_int|999
comma
dot
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
)brace
suffix:semicolon
DECL|function|sigd_attach
r_int
id|sigd_attach
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
(brace
r_if
c_cond
(paren
id|sigd
)paren
r_return
op_minus
id|EADDRINUSE
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;sigd_attach&bslash;n&quot;
)paren
suffix:semicolon
id|sigd
op_assign
id|vcc
suffix:semicolon
id|vcc-&gt;dev
op_assign
op_amp
id|sigd_dev
suffix:semicolon
id|vcc_insert_socket
c_func
(paren
id|sk_atm
c_func
(paren
id|vcc
)paren
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|ATM_VF_META
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|ATM_VF_READY
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
macro_line|#ifdef WAIT_FOR_DEMON
id|wake_up
c_func
(paren
op_amp
id|sigd_sleep
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
eof
