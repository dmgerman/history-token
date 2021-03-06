multiline_comment|/* drivers/atm/atmtcp.c - ATM over TCP &quot;device&quot; driver */
multiline_comment|/* Written 1997-2000 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/atm_tcp.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
r_extern
r_int
id|atm_init_aal5
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
suffix:semicolon
multiline_comment|/* &quot;raw&quot; AAL5 transport */
DECL|macro|PRIV
mdefine_line|#define PRIV(dev) ((struct atmtcp_dev_data *) ((dev)-&gt;dev_data))
DECL|struct|atmtcp_dev_data
r_struct
id|atmtcp_dev_data
(brace
DECL|member|vcc
r_struct
id|atm_vcc
op_star
id|vcc
suffix:semicolon
multiline_comment|/* control VCC; NULL if detached */
DECL|member|persist
r_int
id|persist
suffix:semicolon
multiline_comment|/* non-zero if persistent */
)brace
suffix:semicolon
DECL|macro|DEV_LABEL
mdefine_line|#define DEV_LABEL    &quot;atmtcp&quot;
DECL|macro|MAX_VPI_BITS
mdefine_line|#define MAX_VPI_BITS  8&t;/* simplifies life */
DECL|macro|MAX_VCI_BITS
mdefine_line|#define MAX_VCI_BITS 16
multiline_comment|/*&n; * Hairy code ahead: the control VCC may be closed while we&squot;re still&n; * waiting for an answer, so we need to re-validate out_vcc every once&n; * in a while.&n; */
DECL|function|atmtcp_send_control
r_static
r_int
id|atmtcp_send_control
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|type
comma
r_const
r_struct
id|atmtcp_control
op_star
id|msg
comma
r_int
id|flag
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
r_struct
id|atm_vcc
op_star
id|out_vcc
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|atmtcp_control
op_star
id|new_msg
suffix:semicolon
r_int
id|old_test
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|out_vcc
op_assign
id|PRIV
c_func
(paren
id|vcc-&gt;dev
)paren
ques
c_cond
id|PRIV
c_func
(paren
id|vcc-&gt;dev
)paren
op_member_access_from_pointer
id|vcc
suffix:colon
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|out_vcc
)paren
r_return
op_minus
id|EUNATCH
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
r_sizeof
(paren
op_star
id|msg
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|out_vcc
op_assign
id|PRIV
c_func
(paren
id|vcc-&gt;dev
)paren
ques
c_cond
id|PRIV
c_func
(paren
id|vcc-&gt;dev
)paren
op_member_access_from_pointer
id|vcc
suffix:colon
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|out_vcc
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|EUNATCH
suffix:semicolon
)brace
id|atm_force_charge
c_func
(paren
id|out_vcc
comma
id|skb-&gt;truesize
)paren
suffix:semicolon
id|new_msg
op_assign
(paren
r_struct
id|atmtcp_control
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
r_sizeof
(paren
op_star
id|new_msg
)paren
)paren
suffix:semicolon
op_star
id|new_msg
op_assign
op_star
id|msg
suffix:semicolon
id|new_msg-&gt;hdr.length
op_assign
id|ATMTCP_HDR_MAGIC
suffix:semicolon
id|new_msg-&gt;type
op_assign
id|type
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|new_msg-&gt;vcc
comma
l_int|0
comma
r_sizeof
(paren
id|atm_kptr_t
)paren
)paren
suffix:semicolon
op_star
(paren
r_struct
id|atm_vcc
op_star
op_star
)paren
op_amp
id|new_msg-&gt;vcc
op_assign
id|vcc
suffix:semicolon
id|old_test
op_assign
id|test_bit
c_func
(paren
id|flag
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
id|out_vcc
op_member_access_from_pointer
id|push
c_func
(paren
id|out_vcc
comma
id|skb
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
id|sk_atm
c_func
(paren
id|vcc
)paren
op_member_access_from_pointer
id|sk_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
id|test_bit
c_func
(paren
id|flag
comma
op_amp
id|vcc-&gt;flags
)paren
op_eq
id|old_test
)paren
(brace
id|mb
c_func
(paren
)paren
suffix:semicolon
id|out_vcc
op_assign
id|PRIV
c_func
(paren
id|vcc-&gt;dev
)paren
ques
c_cond
id|PRIV
c_func
(paren
id|vcc-&gt;dev
)paren
op_member_access_from_pointer
id|vcc
suffix:colon
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|out_vcc
)paren
(brace
id|error
op_assign
op_minus
id|EUNATCH
suffix:semicolon
r_break
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
id|sk_atm
c_func
(paren
id|vcc
)paren
op_member_access_from_pointer
id|sk_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|atmtcp_recv_control
r_static
r_int
id|atmtcp_recv_control
c_func
(paren
r_const
r_struct
id|atmtcp_control
op_star
id|msg
)paren
(brace
r_struct
id|atm_vcc
op_star
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
id|vcc-&gt;vpi
op_assign
id|msg-&gt;addr.sap_addr.vpi
suffix:semicolon
id|vcc-&gt;vci
op_assign
id|msg-&gt;addr.sap_addr.vci
suffix:semicolon
id|vcc-&gt;qos
op_assign
id|msg-&gt;qos
suffix:semicolon
id|sk_atm
c_func
(paren
id|vcc
)paren
op_member_access_from_pointer
id|sk_err
op_assign
op_minus
id|msg-&gt;result
suffix:semicolon
r_switch
c_cond
(paren
id|msg-&gt;type
)paren
(brace
r_case
id|ATMTCP_CTRL_OPEN
suffix:colon
id|change_bit
c_func
(paren
id|ATM_VF_READY
comma
op_amp
id|vcc-&gt;flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ATMTCP_CTRL_CLOSE
suffix:colon
id|change_bit
c_func
(paren
id|ATM_VF_ADDR
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
id|KERN_ERR
l_string|&quot;atmtcp_recv_control: unknown type %d&bslash;n&quot;
comma
id|msg-&gt;type
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|wake_up
c_func
(paren
id|sk_atm
c_func
(paren
id|vcc
)paren
op_member_access_from_pointer
id|sk_sleep
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|atmtcp_v_dev_close
r_static
r_void
id|atmtcp_v_dev_close
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
(brace
multiline_comment|/* Nothing.... Isn&squot;t this simple :-)  -- REW */
)brace
DECL|function|atmtcp_v_open
r_static
r_int
id|atmtcp_v_open
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
(brace
r_struct
id|atmtcp_control
id|msg
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
id|vpi
op_assign
id|vcc-&gt;vpi
suffix:semicolon
r_int
id|vci
op_assign
id|vcc-&gt;vci
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|msg
comma
l_int|0
comma
r_sizeof
(paren
id|msg
)paren
)paren
suffix:semicolon
id|msg.addr.sap_family
op_assign
id|AF_ATMPVC
suffix:semicolon
id|msg.hdr.vpi
op_assign
id|htons
c_func
(paren
id|vpi
)paren
suffix:semicolon
id|msg.addr.sap_addr.vpi
op_assign
id|vpi
suffix:semicolon
id|msg.hdr.vci
op_assign
id|htons
c_func
(paren
id|vci
)paren
suffix:semicolon
id|msg.addr.sap_addr.vci
op_assign
id|vci
suffix:semicolon
r_if
c_cond
(paren
id|vpi
op_eq
id|ATM_VPI_UNSPEC
op_logical_or
id|vci
op_eq
id|ATM_VCI_UNSPEC
)paren
r_return
l_int|0
suffix:semicolon
id|msg.type
op_assign
id|ATMTCP_CTRL_OPEN
suffix:semicolon
id|msg.qos
op_assign
id|vcc-&gt;qos
suffix:semicolon
id|set_bit
c_func
(paren
id|ATM_VF_ADDR
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
multiline_comment|/* just in case ... */
id|error
op_assign
id|atmtcp_send_control
c_func
(paren
id|vcc
comma
id|ATMTCP_CTRL_OPEN
comma
op_amp
id|msg
comma
id|ATM_VF_READY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_return
op_minus
id|sk_atm
c_func
(paren
id|vcc
)paren
op_member_access_from_pointer
id|sk_err
suffix:semicolon
)brace
DECL|function|atmtcp_v_close
r_static
r_void
id|atmtcp_v_close
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
(brace
r_struct
id|atmtcp_control
id|msg
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|msg
comma
l_int|0
comma
r_sizeof
(paren
id|msg
)paren
)paren
suffix:semicolon
id|msg.addr.sap_family
op_assign
id|AF_ATMPVC
suffix:semicolon
id|msg.addr.sap_addr.vpi
op_assign
id|vcc-&gt;vpi
suffix:semicolon
id|msg.addr.sap_addr.vci
op_assign
id|vcc-&gt;vci
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
(paren
r_void
)paren
id|atmtcp_send_control
c_func
(paren
id|vcc
comma
id|ATMTCP_CTRL_CLOSE
comma
op_amp
id|msg
comma
id|ATM_VF_ADDR
)paren
suffix:semicolon
)brace
DECL|function|atmtcp_v_ioctl
r_static
r_int
id|atmtcp_v_ioctl
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
r_int
r_int
id|cmd
comma
r_void
id|__user
op_star
id|arg
)paren
(brace
r_struct
id|atm_cirange
id|ci
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|vcc
suffix:semicolon
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
r_if
c_cond
(paren
id|cmd
op_ne
id|ATM_SETCIRANGE
)paren
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ci
comma
id|arg
comma
r_sizeof
(paren
id|ci
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|ci.vpi_bits
op_eq
id|ATM_CI_MAX
)paren
id|ci.vpi_bits
op_assign
id|MAX_VPI_BITS
suffix:semicolon
r_if
c_cond
(paren
id|ci.vci_bits
op_eq
id|ATM_CI_MAX
)paren
id|ci.vci_bits
op_assign
id|MAX_VCI_BITS
suffix:semicolon
r_if
c_cond
(paren
id|ci.vpi_bits
OG
id|MAX_VPI_BITS
op_logical_or
id|ci.vpi_bits
template_param
id|MAX_VCI_BITS
op_logical_or
id|ci.vci_bits
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
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
op_ne
id|dev
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|vcc-&gt;vpi
op_rshift
id|ci.vpi_bits
)paren
op_logical_or
(paren
id|vcc-&gt;vci
op_rshift
id|ci.vci_bits
)paren
)paren
(brace
id|read_unlock
c_func
(paren
op_amp
id|vcc_sklist_lock
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|vcc_sklist_lock
)paren
suffix:semicolon
id|dev-&gt;ci_range
op_assign
id|ci
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|atmtcp_v_send
r_static
r_int
id|atmtcp_v_send
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
id|atmtcp_dev_data
op_star
id|dev_data
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|out_vcc
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Initializer quietens GCC warning */
r_struct
id|sk_buff
op_star
id|new_skb
suffix:semicolon
r_struct
id|atmtcp_hdr
op_star
id|hdr
suffix:semicolon
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
id|vcc-&gt;qos.txtp.traffic_class
op_eq
id|ATM_NONE
)paren
(brace
r_if
c_cond
(paren
id|vcc-&gt;pop
)paren
id|vcc
op_member_access_from_pointer
id|pop
c_func
(paren
id|vcc
comma
id|skb
)paren
suffix:semicolon
r_else
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|dev_data
op_assign
id|PRIV
c_func
(paren
id|vcc-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_data
)paren
id|out_vcc
op_assign
id|dev_data-&gt;vcc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_data
op_logical_or
op_logical_neg
id|out_vcc
)paren
(brace
r_if
c_cond
(paren
id|vcc-&gt;pop
)paren
id|vcc
op_member_access_from_pointer
id|pop
c_func
(paren
id|vcc
comma
id|skb
)paren
suffix:semicolon
r_else
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_data
)paren
r_return
l_int|0
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|vcc-&gt;stats-&gt;tx_err
)paren
suffix:semicolon
r_return
op_minus
id|ENOLINK
suffix:semicolon
)brace
id|size
op_assign
id|skb-&gt;len
op_plus
r_sizeof
(paren
r_struct
id|atmtcp_hdr
)paren
suffix:semicolon
id|new_skb
op_assign
id|atm_alloc_charge
c_func
(paren
id|out_vcc
comma
id|size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_skb
)paren
(brace
r_if
c_cond
(paren
id|vcc-&gt;pop
)paren
id|vcc
op_member_access_from_pointer
id|pop
c_func
(paren
id|vcc
comma
id|skb
)paren
suffix:semicolon
r_else
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|vcc-&gt;stats-&gt;tx_err
)paren
suffix:semicolon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
id|hdr
op_assign
(paren
r_void
op_star
)paren
id|skb_put
c_func
(paren
id|new_skb
comma
r_sizeof
(paren
r_struct
id|atmtcp_hdr
)paren
)paren
suffix:semicolon
id|hdr-&gt;vpi
op_assign
id|htons
c_func
(paren
id|vcc-&gt;vpi
)paren
suffix:semicolon
id|hdr-&gt;vci
op_assign
id|htons
c_func
(paren
id|vcc-&gt;vci
)paren
suffix:semicolon
id|hdr-&gt;length
op_assign
id|htonl
c_func
(paren
id|skb-&gt;len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|new_skb
comma
id|skb-&gt;len
)paren
comma
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vcc-&gt;pop
)paren
id|vcc
op_member_access_from_pointer
id|pop
c_func
(paren
id|vcc
comma
id|skb
)paren
suffix:semicolon
r_else
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|out_vcc
op_member_access_from_pointer
id|push
c_func
(paren
id|out_vcc
comma
id|new_skb
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|vcc-&gt;stats-&gt;tx
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|out_vcc-&gt;stats-&gt;rx
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|atmtcp_v_proc
r_static
r_int
id|atmtcp_v_proc
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
id|loff_t
op_star
id|pos
comma
r_char
op_star
id|page
)paren
(brace
r_struct
id|atmtcp_dev_data
op_star
id|dev_data
op_assign
id|PRIV
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|pos
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_data-&gt;persist
)paren
r_return
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;ephemeral&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;persistent, %sconnected&bslash;n&quot;
comma
id|dev_data-&gt;vcc
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;dis&quot;
)paren
suffix:semicolon
)brace
DECL|function|atmtcp_c_close
r_static
r_void
id|atmtcp_c_close
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
(brace
r_struct
id|atm_dev
op_star
id|atmtcp_dev
suffix:semicolon
r_struct
id|atmtcp_dev_data
op_star
id|dev_data
suffix:semicolon
r_struct
id|sock
op_star
id|s
suffix:semicolon
r_struct
id|hlist_node
op_star
id|node
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|walk
suffix:semicolon
r_int
id|i
suffix:semicolon
id|atmtcp_dev
op_assign
(paren
r_struct
id|atm_dev
op_star
)paren
id|vcc-&gt;dev_data
suffix:semicolon
id|dev_data
op_assign
id|PRIV
c_func
(paren
id|atmtcp_dev
)paren
suffix:semicolon
id|dev_data-&gt;vcc
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|dev_data-&gt;persist
)paren
r_return
suffix:semicolon
id|atmtcp_dev-&gt;dev_data
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|dev_data
)paren
suffix:semicolon
id|shutdown_atm_dev
c_func
(paren
id|atmtcp_dev
)paren
suffix:semicolon
id|vcc-&gt;dev_data
op_assign
l_int|NULL
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
id|walk
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
id|walk-&gt;dev
op_ne
id|atmtcp_dev
)paren
r_continue
suffix:semicolon
id|wake_up
c_func
(paren
id|s-&gt;sk_sleep
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
id|module_put
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
)brace
DECL|function|find_vcc
r_static
r_struct
id|atm_vcc
op_star
id|find_vcc
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
r_int
id|vpi
comma
r_int
id|vci
)paren
(brace
r_struct
id|hlist_head
op_star
id|head
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|vcc
suffix:semicolon
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
id|head
op_assign
op_amp
id|vcc_hash
(braket
id|vci
op_amp
(paren
id|VCC_HTABLE_SIZE
op_minus
l_int|1
)paren
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
op_eq
id|dev
op_logical_and
id|vcc-&gt;vci
op_eq
id|vci
op_logical_and
id|vcc-&gt;vpi
op_eq
id|vpi
op_logical_and
id|vcc-&gt;qos.rxtp.traffic_class
op_ne
id|ATM_NONE
)paren
(brace
r_return
id|vcc
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|atmtcp_c_send
r_static
r_int
id|atmtcp_c_send
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
id|atm_dev
op_star
id|dev
suffix:semicolon
r_struct
id|atmtcp_hdr
op_star
id|hdr
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|out_vcc
suffix:semicolon
r_struct
id|sk_buff
op_star
id|new_skb
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb-&gt;len
)paren
r_return
l_int|0
suffix:semicolon
id|dev
op_assign
id|vcc-&gt;dev_data
suffix:semicolon
id|hdr
op_assign
(paren
r_struct
id|atmtcp_hdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|hdr-&gt;length
op_eq
id|ATMTCP_HDR_MAGIC
)paren
(brace
id|result
op_assign
id|atmtcp_recv_control
c_func
(paren
(paren
r_struct
id|atmtcp_control
op_star
)paren
id|skb-&gt;data
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|read_lock
c_func
(paren
op_amp
id|vcc_sklist_lock
)paren
suffix:semicolon
id|out_vcc
op_assign
id|find_vcc
c_func
(paren
id|dev
comma
id|ntohs
c_func
(paren
id|hdr-&gt;vpi
)paren
comma
id|ntohs
c_func
(paren
id|hdr-&gt;vci
)paren
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|vcc_sklist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|out_vcc
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|vcc-&gt;stats-&gt;tx_err
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|skb_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|atmtcp_hdr
)paren
)paren
suffix:semicolon
id|new_skb
op_assign
id|atm_alloc_charge
c_func
(paren
id|out_vcc
comma
id|skb-&gt;len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_skb
)paren
(brace
id|result
op_assign
op_minus
id|ENOBUFS
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|do_gettimeofday
c_func
(paren
op_amp
id|new_skb-&gt;stamp
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|new_skb
comma
id|skb-&gt;len
)paren
comma
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|out_vcc
op_member_access_from_pointer
id|push
c_func
(paren
id|out_vcc
comma
id|new_skb
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|vcc-&gt;stats-&gt;tx
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|out_vcc-&gt;stats-&gt;rx
)paren
suffix:semicolon
id|done
suffix:colon
r_if
c_cond
(paren
id|vcc-&gt;pop
)paren
id|vcc
op_member_access_from_pointer
id|pop
c_func
(paren
id|vcc
comma
id|skb
)paren
suffix:semicolon
r_else
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * Device operations for the virtual ATM devices created by ATMTCP.&n; */
DECL|variable|atmtcp_v_dev_ops
r_static
r_struct
id|atmdev_ops
id|atmtcp_v_dev_ops
op_assign
(brace
dot
id|dev_close
op_assign
id|atmtcp_v_dev_close
comma
dot
id|open
op_assign
id|atmtcp_v_open
comma
dot
id|close
op_assign
id|atmtcp_v_close
comma
dot
id|ioctl
op_assign
id|atmtcp_v_ioctl
comma
dot
id|send
op_assign
id|atmtcp_v_send
comma
dot
id|proc_read
op_assign
id|atmtcp_v_proc
comma
dot
id|owner
op_assign
id|THIS_MODULE
)brace
suffix:semicolon
multiline_comment|/*&n; * Device operations for the ATMTCP control device.&n; */
DECL|variable|atmtcp_c_dev_ops
r_static
r_struct
id|atmdev_ops
id|atmtcp_c_dev_ops
op_assign
(brace
dot
id|close
op_assign
id|atmtcp_c_close
comma
dot
id|send
op_assign
id|atmtcp_c_send
)brace
suffix:semicolon
DECL|variable|atmtcp_control_dev
r_static
r_struct
id|atm_dev
id|atmtcp_control_dev
op_assign
(brace
dot
id|ops
op_assign
op_amp
id|atmtcp_c_dev_ops
comma
dot
id|type
op_assign
l_string|&quot;atmtcp&quot;
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
DECL|function|atmtcp_create
r_static
r_int
id|atmtcp_create
c_func
(paren
r_int
id|itf
comma
r_int
id|persist
comma
r_struct
id|atm_dev
op_star
op_star
id|result
)paren
(brace
r_struct
id|atmtcp_dev_data
op_star
id|dev_data
suffix:semicolon
r_struct
id|atm_dev
op_star
id|dev
suffix:semicolon
id|dev_data
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|dev_data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_data
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|dev
op_assign
id|atm_dev_register
c_func
(paren
id|DEV_LABEL
comma
op_amp
id|atmtcp_v_dev_ops
comma
id|itf
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|kfree
c_func
(paren
id|dev_data
)paren
suffix:semicolon
r_return
id|itf
op_eq
op_minus
l_int|1
ques
c_cond
op_minus
id|ENOMEM
suffix:colon
op_minus
id|EBUSY
suffix:semicolon
)brace
id|dev-&gt;ci_range.vpi_bits
op_assign
id|MAX_VPI_BITS
suffix:semicolon
id|dev-&gt;ci_range.vci_bits
op_assign
id|MAX_VCI_BITS
suffix:semicolon
id|dev-&gt;dev_data
op_assign
id|dev_data
suffix:semicolon
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|vcc
op_assign
l_int|NULL
suffix:semicolon
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|persist
op_assign
id|persist
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
op_star
id|result
op_assign
id|dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|atmtcp_attach
r_static
r_int
id|atmtcp_attach
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|itf
)paren
(brace
r_struct
id|atm_dev
op_star
id|dev
suffix:semicolon
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|itf
op_ne
op_minus
l_int|1
)paren
id|dev
op_assign
id|atm_dev_lookup
c_func
(paren
id|itf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;ops
op_ne
op_amp
id|atmtcp_v_dev_ops
)paren
(brace
id|atm_dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|EMEDIUMTYPE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|vcc
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_else
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|atmtcp_create
c_func
(paren
id|itf
comma
l_int|0
comma
op_amp
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
)brace
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|vcc
op_assign
id|vcc
suffix:semicolon
id|vcc-&gt;dev
op_assign
op_amp
id|atmtcp_control_dev
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
id|vcc-&gt;dev_data
op_assign
id|dev
suffix:semicolon
(paren
r_void
)paren
id|atm_init_aal5
c_func
(paren
id|vcc
)paren
suffix:semicolon
multiline_comment|/* @@@ losing AAL in transit ... */
id|vcc-&gt;stats
op_assign
op_amp
id|atmtcp_control_dev.stats.aal5
suffix:semicolon
r_return
id|dev-&gt;number
suffix:semicolon
)brace
DECL|function|atmtcp_create_persistent
r_static
r_int
id|atmtcp_create_persistent
c_func
(paren
r_int
id|itf
)paren
(brace
r_return
id|atmtcp_create
c_func
(paren
id|itf
comma
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|atmtcp_remove_persistent
r_static
r_int
id|atmtcp_remove_persistent
c_func
(paren
r_int
id|itf
)paren
(brace
r_struct
id|atm_dev
op_star
id|dev
suffix:semicolon
r_struct
id|atmtcp_dev_data
op_star
id|dev_data
suffix:semicolon
id|dev
op_assign
id|atm_dev_lookup
c_func
(paren
id|itf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;ops
op_ne
op_amp
id|atmtcp_v_dev_ops
)paren
(brace
id|atm_dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|EMEDIUMTYPE
suffix:semicolon
)brace
id|dev_data
op_assign
id|PRIV
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_data-&gt;persist
)paren
r_return
l_int|0
suffix:semicolon
id|dev_data-&gt;persist
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|vcc
)paren
r_return
l_int|0
suffix:semicolon
id|kfree
c_func
(paren
id|dev_data
)paren
suffix:semicolon
id|atm_dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
id|shutdown_atm_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|atmtcp_ioctl
r_static
r_int
id|atmtcp_ioctl
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|vcc
op_assign
id|ATM_SD
c_func
(paren
id|sock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_ne
id|SIOCSIFATMTCP
op_logical_and
id|cmd
op_ne
id|ATMTCP_CREATE
op_logical_and
id|cmd
op_ne
id|ATMTCP_REMOVE
)paren
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SIOCSIFATMTCP
suffix:colon
id|err
op_assign
id|atmtcp_attach
c_func
(paren
id|vcc
comma
(paren
r_int
)paren
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ge
l_int|0
)paren
(brace
id|sock-&gt;state
op_assign
id|SS_CONNECTED
suffix:semicolon
id|__module_get
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ATMTCP_CREATE
suffix:colon
id|err
op_assign
id|atmtcp_create_persistent
c_func
(paren
(paren
r_int
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ATMTCP_REMOVE
suffix:colon
id|err
op_assign
id|atmtcp_remove_persistent
c_func
(paren
(paren
r_int
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|variable|atmtcp_ioctl_ops
r_static
r_struct
id|atm_ioctl
id|atmtcp_ioctl_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|ioctl
op_assign
id|atmtcp_ioctl
comma
)brace
suffix:semicolon
DECL|function|atmtcp_init
r_static
id|__init
r_int
id|atmtcp_init
c_func
(paren
r_void
)paren
(brace
id|register_atm_ioctl
c_func
(paren
op_amp
id|atmtcp_ioctl_ops
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|atmtcp_exit
r_static
r_void
id|__exit
id|atmtcp_exit
c_func
(paren
r_void
)paren
(brace
id|deregister_atm_ioctl
c_func
(paren
op_amp
id|atmtcp_ioctl_ops
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|atmtcp_init
id|module_init
c_func
(paren
id|atmtcp_init
)paren
suffix:semicolon
DECL|variable|atmtcp_exit
id|module_exit
c_func
(paren
id|atmtcp_exit
)paren
suffix:semicolon
eof
