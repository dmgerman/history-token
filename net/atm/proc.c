multiline_comment|/* net/atm/proc.c - ATM /proc interface&n; *&n; * Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA&n; *&n; * seq_file api usage by romieu@fr.zoreil.com&n; *&n; * Evaluating the efficiency of the whole thing if left as an exercise to&n; * the reader.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt; /* for EXPORT_SYMBOL */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/atm.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/atmclip.h&gt;
macro_line|#include &lt;linux/init.h&gt; /* for __init */
macro_line|#include &lt;net/atmclip.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/param.h&gt; /* for HZ */
macro_line|#include &quot;resources.h&quot;
macro_line|#include &quot;common.h&quot; /* atm_proc_init prototype */
macro_line|#include &quot;signaling.h&quot; /* to get sigd - ugly too */
r_static
id|ssize_t
id|proc_dev_atm_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|pos
)paren
suffix:semicolon
DECL|variable|proc_atm_dev_ops
r_static
r_struct
id|file_operations
id|proc_atm_dev_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|read
op_assign
id|proc_dev_atm_read
comma
)brace
suffix:semicolon
DECL|function|add_stats
r_static
r_void
id|add_stats
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_const
r_char
op_star
id|aal
comma
r_const
r_struct
id|k_atm_aal_stats
op_star
id|stats
)paren
(brace
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%s ( %d %d %d %d %d )&quot;
comma
id|aal
comma
id|atomic_read
c_func
(paren
op_amp
id|stats-&gt;tx
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|stats-&gt;tx_err
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|stats-&gt;rx
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|stats-&gt;rx_err
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|stats-&gt;rx_drop
)paren
)paren
suffix:semicolon
)brace
DECL|function|atm_dev_info
r_static
r_void
id|atm_dev_info
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_const
r_struct
id|atm_dev
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%3d %-8s&quot;
comma
id|dev-&gt;number
comma
id|dev-&gt;type
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
id|ESI_LEN
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%02x&quot;
comma
id|dev-&gt;esi
(braket
id|i
)braket
)paren
suffix:semicolon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;  &quot;
)paren
suffix:semicolon
id|add_stats
c_func
(paren
id|seq
comma
l_string|&quot;0&quot;
comma
op_amp
id|dev-&gt;stats.aal0
)paren
suffix:semicolon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;  &quot;
)paren
suffix:semicolon
id|add_stats
c_func
(paren
id|seq
comma
l_string|&quot;5&quot;
comma
op_amp
id|dev-&gt;stats.aal5
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;&bslash;t[%d]&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|dev-&gt;refcnt
)paren
)paren
suffix:semicolon
id|seq_putc
c_func
(paren
id|seq
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
DECL|struct|vcc_state
r_struct
id|vcc_state
(brace
DECL|member|bucket
r_int
id|bucket
suffix:semicolon
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
DECL|member|family
r_int
id|family
suffix:semicolon
)brace
suffix:semicolon
DECL|function|compare_family
r_static
r_inline
r_int
id|compare_family
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|family
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
id|sk
)paren
suffix:semicolon
r_return
op_logical_neg
id|family
op_logical_or
(paren
id|vcc-&gt;sk-&gt;sk_family
op_eq
id|family
)paren
suffix:semicolon
)brace
DECL|function|__vcc_walk
r_static
r_int
id|__vcc_walk
c_func
(paren
r_struct
id|sock
op_star
op_star
id|sock
comma
r_int
id|family
comma
r_int
op_star
id|bucket
comma
id|loff_t
id|l
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
op_star
id|sock
suffix:semicolon
r_if
c_cond
(paren
id|sk
op_eq
(paren
r_void
op_star
)paren
l_int|1
)paren
(brace
r_for
c_loop
(paren
op_star
id|bucket
op_assign
l_int|0
suffix:semicolon
op_star
id|bucket
OL
id|VCC_HTABLE_SIZE
suffix:semicolon
op_increment
op_star
id|bucket
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
op_star
id|bucket
)braket
suffix:semicolon
id|sk
op_assign
id|hlist_empty
c_func
(paren
id|head
)paren
ques
c_cond
l_int|NULL
suffix:colon
id|__sk_head
c_func
(paren
id|head
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk
)paren
r_break
suffix:semicolon
)brace
id|l
op_decrement
suffix:semicolon
)brace
id|try_again
suffix:colon
r_for
c_loop
(paren
suffix:semicolon
id|sk
suffix:semicolon
id|sk
op_assign
id|sk_next
c_func
(paren
id|sk
)paren
)paren
(brace
id|l
op_sub_assign
id|compare_family
c_func
(paren
id|sk
comma
id|family
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sk
op_logical_and
op_increment
op_star
id|bucket
OL
id|VCC_HTABLE_SIZE
)paren
(brace
id|sk
op_assign
id|sk_head
c_func
(paren
op_amp
id|vcc_hash
(braket
op_star
id|bucket
)braket
)paren
suffix:semicolon
r_goto
id|try_again
suffix:semicolon
)brace
id|sk
op_assign
(paren
r_void
op_star
)paren
l_int|1
suffix:semicolon
id|out
suffix:colon
op_star
id|sock
op_assign
id|sk
suffix:semicolon
r_return
(paren
id|l
OL
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|vcc_walk
r_static
r_inline
r_void
op_star
id|vcc_walk
c_func
(paren
r_struct
id|vcc_state
op_star
id|state
comma
id|loff_t
id|l
)paren
(brace
r_return
id|__vcc_walk
c_func
(paren
op_amp
id|state-&gt;sk
comma
id|state-&gt;family
comma
op_amp
id|state-&gt;bucket
comma
id|l
)paren
ques
c_cond
id|state
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|__vcc_seq_open
r_static
r_int
id|__vcc_seq_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
id|family
comma
r_struct
id|seq_operations
op_star
id|ops
)paren
(brace
r_struct
id|vcc_state
op_star
id|state
suffix:semicolon
r_struct
id|seq_file
op_star
id|seq
suffix:semicolon
r_int
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|state
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|state
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state
)paren
r_goto
id|out
suffix:semicolon
id|rc
op_assign
id|seq_open
c_func
(paren
id|file
comma
id|ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_goto
id|out_kfree
suffix:semicolon
id|state-&gt;family
op_assign
id|family
suffix:semicolon
id|seq
op_assign
id|file-&gt;private_data
suffix:semicolon
id|seq
op_member_access_from_pointer
r_private
op_assign
id|state
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
id|out_kfree
suffix:colon
id|kfree
c_func
(paren
id|state
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|vcc_seq_release
r_static
r_int
id|vcc_seq_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|seq_release_private
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
)brace
DECL|function|vcc_seq_start
r_static
r_void
op_star
id|vcc_seq_start
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|vcc_state
op_star
id|state
op_assign
id|seq
op_member_access_from_pointer
r_private
suffix:semicolon
id|loff_t
id|left
op_assign
op_star
id|pos
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|vcc_sklist_lock
)paren
suffix:semicolon
id|state-&gt;sk
op_assign
(paren
r_void
op_star
)paren
l_int|1
suffix:semicolon
r_return
id|left
ques
c_cond
id|vcc_walk
c_func
(paren
id|state
comma
id|left
)paren
suffix:colon
(paren
r_void
op_star
)paren
l_int|1
suffix:semicolon
)brace
DECL|function|vcc_seq_stop
r_static
r_void
id|vcc_seq_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
)paren
(brace
id|read_unlock
c_func
(paren
op_amp
id|vcc_sklist_lock
)paren
suffix:semicolon
)brace
DECL|function|vcc_seq_next
r_static
r_void
op_star
id|vcc_seq_next
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|vcc_state
op_star
id|state
op_assign
id|seq
op_member_access_from_pointer
r_private
suffix:semicolon
id|v
op_assign
id|vcc_walk
c_func
(paren
id|state
comma
l_int|1
)paren
suffix:semicolon
op_star
id|pos
op_add_assign
op_logical_neg
op_logical_neg
id|PTR_ERR
c_func
(paren
id|v
)paren
suffix:semicolon
r_return
id|v
suffix:semicolon
)brace
DECL|function|pvc_info
r_static
r_void
id|pvc_info
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_struct
id|atm_vcc
op_star
id|vcc
)paren
(brace
r_static
r_const
r_char
op_star
id|class_name
(braket
)braket
op_assign
(brace
l_string|&quot;off&quot;
comma
l_string|&quot;UBR&quot;
comma
l_string|&quot;CBR&quot;
comma
l_string|&quot;VBR&quot;
comma
l_string|&quot;ABR&quot;
)brace
suffix:semicolon
r_static
r_const
r_char
op_star
id|aal_name
(braket
)braket
op_assign
(brace
l_string|&quot;---&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3/4&quot;
comma
multiline_comment|/*  0- 3 */
l_string|&quot;???&quot;
comma
l_string|&quot;5&quot;
comma
l_string|&quot;???&quot;
comma
l_string|&quot;???&quot;
comma
multiline_comment|/*  4- 7 */
l_string|&quot;???&quot;
comma
l_string|&quot;???&quot;
comma
l_string|&quot;???&quot;
comma
l_string|&quot;???&quot;
comma
multiline_comment|/*  8-11 */
l_string|&quot;???&quot;
comma
l_string|&quot;0&quot;
comma
l_string|&quot;???&quot;
comma
l_string|&quot;???&quot;
)brace
suffix:semicolon
multiline_comment|/* 12-15 */
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%3d %3d %5d %-3s %7d %-5s %7d %-6s&quot;
comma
id|vcc-&gt;dev-&gt;number
comma
id|vcc-&gt;vpi
comma
id|vcc-&gt;vci
comma
id|vcc-&gt;qos.aal
op_ge
r_sizeof
(paren
id|aal_name
)paren
op_div
r_sizeof
(paren
id|aal_name
(braket
l_int|0
)braket
)paren
ques
c_cond
l_string|&quot;err&quot;
suffix:colon
id|aal_name
(braket
id|vcc-&gt;qos.aal
)braket
comma
id|vcc-&gt;qos.rxtp.min_pcr
comma
id|class_name
(braket
id|vcc-&gt;qos.rxtp.traffic_class
)braket
comma
id|vcc-&gt;qos.txtp.min_pcr
comma
id|class_name
(braket
id|vcc-&gt;qos.txtp.traffic_class
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|ATM_VF_IS_CLIP
comma
op_amp
id|vcc-&gt;flags
)paren
)paren
(brace
r_struct
id|clip_vcc
op_star
id|clip_vcc
op_assign
id|CLIP_VCC
c_func
(paren
id|vcc
)paren
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
id|dev
op_assign
id|clip_vcc-&gt;entry
ques
c_cond
id|clip_vcc-&gt;entry-&gt;neigh-&gt;dev
suffix:colon
l_int|NULL
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;CLIP, Itf:%s, Encap:&quot;
comma
id|dev
ques
c_cond
id|dev-&gt;name
suffix:colon
l_string|&quot;none?&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%s&quot;
comma
id|clip_vcc-&gt;encap
ques
c_cond
l_string|&quot;LLC/SNAP&quot;
suffix:colon
l_string|&quot;None&quot;
)paren
suffix:semicolon
)brace
id|seq_putc
c_func
(paren
id|seq
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
DECL|function|vcc_state
r_static
r_const
r_char
op_star
id|vcc_state
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
(brace
r_static
r_const
r_char
op_star
id|map
(braket
)braket
op_assign
(brace
id|ATM_VS2TXT_MAP
)brace
suffix:semicolon
r_return
id|map
(braket
id|ATM_VF2VS
c_func
(paren
id|vcc-&gt;flags
)paren
)braket
suffix:semicolon
)brace
DECL|function|vcc_info
r_static
r_void
id|vcc_info
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_struct
id|atm_vcc
op_star
id|vcc
)paren
(brace
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%p &quot;
comma
id|vcc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vcc-&gt;dev
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;Unassigned    &quot;
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%3d %3d %5d &quot;
comma
id|vcc-&gt;dev-&gt;number
comma
id|vcc-&gt;vpi
comma
id|vcc-&gt;vci
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|vcc-&gt;sk-&gt;sk_family
)paren
(brace
r_case
id|AF_ATMPVC
suffix:colon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;PVC&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AF_ATMSVC
suffix:colon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;SVC&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%3d&quot;
comma
id|vcc-&gt;sk-&gt;sk_family
)paren
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %04lx  %5d %7d/%7d %7d/%7d [%d]&bslash;n&quot;
comma
id|vcc-&gt;flags
comma
id|vcc-&gt;sk-&gt;sk_err
comma
id|atomic_read
c_func
(paren
op_amp
id|vcc-&gt;sk-&gt;sk_wmem_alloc
)paren
comma
id|vcc-&gt;sk-&gt;sk_sndbuf
comma
id|atomic_read
c_func
(paren
op_amp
id|vcc-&gt;sk-&gt;sk_rmem_alloc
)paren
comma
id|vcc-&gt;sk-&gt;sk_rcvbuf
comma
id|atomic_read
c_func
(paren
op_amp
id|vcc-&gt;sk-&gt;sk_refcnt
)paren
)paren
suffix:semicolon
)brace
DECL|function|svc_info
r_static
r_void
id|svc_info
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_struct
id|atm_vcc
op_star
id|vcc
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|vcc-&gt;dev
)paren
id|seq_printf
c_func
(paren
id|seq
comma
r_sizeof
(paren
r_void
op_star
)paren
op_eq
l_int|4
ques
c_cond
l_string|&quot;N/A@%p%10s&quot;
suffix:colon
l_string|&quot;N/A@%p%2s&quot;
comma
id|vcc
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%3d %3d %5d         &quot;
comma
id|vcc-&gt;dev-&gt;number
comma
id|vcc-&gt;vpi
comma
id|vcc-&gt;vci
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%-10s &quot;
comma
id|vcc_state
c_func
(paren
id|vcc
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%s%s&quot;
comma
id|vcc-&gt;remote.sas_addr.pub
comma
op_star
id|vcc-&gt;remote.sas_addr.pub
op_logical_and
op_star
id|vcc-&gt;remote.sas_addr.prv
ques
c_cond
l_string|&quot;+&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|vcc-&gt;remote.sas_addr.prv
)paren
(brace
r_int
id|i
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
id|ATM_ESA_LEN
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%02x&quot;
comma
id|vcc-&gt;remote.sas_addr.prv
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|seq_putc
c_func
(paren
id|seq
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
DECL|function|atm_dev_seq_show
r_static
r_int
id|atm_dev_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
)paren
(brace
r_static
r_char
id|atm_dev_banner
(braket
)braket
op_assign
l_string|&quot;Itf Type    ESI/&bslash;&quot;MAC&bslash;&quot;addr &quot;
l_string|&quot;AAL(TX,err,RX,err,drop) ...               [refcnt]&bslash;n&quot;
suffix:semicolon
r_if
c_cond
(paren
id|v
op_eq
(paren
r_void
op_star
)paren
l_int|1
)paren
id|seq_puts
c_func
(paren
id|seq
comma
id|atm_dev_banner
)paren
suffix:semicolon
r_else
(brace
r_struct
id|atm_dev
op_star
id|dev
op_assign
id|list_entry
c_func
(paren
id|v
comma
r_struct
id|atm_dev
comma
id|dev_list
)paren
suffix:semicolon
id|atm_dev_info
c_func
(paren
id|seq
comma
id|dev
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|atm_dev_seq_ops
r_static
r_struct
id|seq_operations
id|atm_dev_seq_ops
op_assign
(brace
dot
id|start
op_assign
id|atm_dev_seq_start
comma
dot
id|next
op_assign
id|atm_dev_seq_next
comma
dot
id|stop
op_assign
id|atm_dev_seq_stop
comma
dot
id|show
op_assign
id|atm_dev_seq_show
comma
)brace
suffix:semicolon
DECL|function|atm_dev_seq_open
r_static
r_int
id|atm_dev_seq_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|atm_dev_seq_ops
)paren
suffix:semicolon
)brace
DECL|variable|devices_seq_fops
r_static
r_struct
id|file_operations
id|devices_seq_fops
op_assign
(brace
dot
id|open
op_assign
id|atm_dev_seq_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|seq_release
comma
)brace
suffix:semicolon
DECL|function|pvc_seq_show
r_static
r_int
id|pvc_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
)paren
(brace
r_static
r_char
id|atm_pvc_banner
(braket
)braket
op_assign
l_string|&quot;Itf VPI VCI   AAL RX(PCR,Class) TX(PCR,Class)&bslash;n&quot;
suffix:semicolon
r_if
c_cond
(paren
id|v
op_eq
(paren
r_void
op_star
)paren
l_int|1
)paren
id|seq_puts
c_func
(paren
id|seq
comma
id|atm_pvc_banner
)paren
suffix:semicolon
r_else
(brace
r_struct
id|vcc_state
op_star
id|state
op_assign
id|seq
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|vcc
op_assign
id|atm_sk
c_func
(paren
id|state-&gt;sk
)paren
suffix:semicolon
id|pvc_info
c_func
(paren
id|seq
comma
id|vcc
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pvc_seq_ops
r_static
r_struct
id|seq_operations
id|pvc_seq_ops
op_assign
(brace
dot
id|start
op_assign
id|vcc_seq_start
comma
dot
id|next
op_assign
id|vcc_seq_next
comma
dot
id|stop
op_assign
id|vcc_seq_stop
comma
dot
id|show
op_assign
id|pvc_seq_show
comma
)brace
suffix:semicolon
DECL|function|pvc_seq_open
r_static
r_int
id|pvc_seq_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|__vcc_seq_open
c_func
(paren
id|inode
comma
id|file
comma
id|PF_ATMPVC
comma
op_amp
id|pvc_seq_ops
)paren
suffix:semicolon
)brace
DECL|variable|pvc_seq_fops
r_static
r_struct
id|file_operations
id|pvc_seq_fops
op_assign
(brace
dot
id|open
op_assign
id|pvc_seq_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|vcc_seq_release
comma
)brace
suffix:semicolon
DECL|function|vcc_seq_show
r_static
r_int
id|vcc_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
)paren
(brace
r_if
c_cond
(paren
id|v
op_eq
(paren
r_void
op_star
)paren
l_int|1
)paren
(brace
id|seq_printf
c_func
(paren
id|seq
comma
r_sizeof
(paren
r_void
op_star
)paren
op_eq
l_int|4
ques
c_cond
l_string|&quot;%-8s%s&quot;
suffix:colon
l_string|&quot;%-16s%s&quot;
comma
l_string|&quot;Address &quot;
comma
l_string|&quot;Itf VPI VCI   Fam Flags Reply &quot;
l_string|&quot;Send buffer     Recv buffer      [refcnt]&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|vcc_state
op_star
id|state
op_assign
id|seq
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|vcc
op_assign
id|atm_sk
c_func
(paren
id|state-&gt;sk
)paren
suffix:semicolon
id|vcc_info
c_func
(paren
id|seq
comma
id|vcc
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|vcc_seq_ops
r_static
r_struct
id|seq_operations
id|vcc_seq_ops
op_assign
(brace
dot
id|start
op_assign
id|vcc_seq_start
comma
dot
id|next
op_assign
id|vcc_seq_next
comma
dot
id|stop
op_assign
id|vcc_seq_stop
comma
dot
id|show
op_assign
id|vcc_seq_show
comma
)brace
suffix:semicolon
DECL|function|vcc_seq_open
r_static
r_int
id|vcc_seq_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|__vcc_seq_open
c_func
(paren
id|inode
comma
id|file
comma
l_int|0
comma
op_amp
id|vcc_seq_ops
)paren
suffix:semicolon
)brace
DECL|variable|vcc_seq_fops
r_static
r_struct
id|file_operations
id|vcc_seq_fops
op_assign
(brace
dot
id|open
op_assign
id|vcc_seq_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|vcc_seq_release
comma
)brace
suffix:semicolon
DECL|function|svc_seq_show
r_static
r_int
id|svc_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
)paren
(brace
r_static
r_char
id|atm_svc_banner
(braket
)braket
op_assign
l_string|&quot;Itf VPI VCI           State      Remote&bslash;n&quot;
suffix:semicolon
r_if
c_cond
(paren
id|v
op_eq
(paren
r_void
op_star
)paren
l_int|1
)paren
id|seq_puts
c_func
(paren
id|seq
comma
id|atm_svc_banner
)paren
suffix:semicolon
r_else
(brace
r_struct
id|vcc_state
op_star
id|state
op_assign
id|seq
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|vcc
op_assign
id|atm_sk
c_func
(paren
id|state-&gt;sk
)paren
suffix:semicolon
id|svc_info
c_func
(paren
id|seq
comma
id|vcc
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|svc_seq_ops
r_static
r_struct
id|seq_operations
id|svc_seq_ops
op_assign
(brace
dot
id|start
op_assign
id|vcc_seq_start
comma
dot
id|next
op_assign
id|vcc_seq_next
comma
dot
id|stop
op_assign
id|vcc_seq_stop
comma
dot
id|show
op_assign
id|svc_seq_show
comma
)brace
suffix:semicolon
DECL|function|svc_seq_open
r_static
r_int
id|svc_seq_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|__vcc_seq_open
c_func
(paren
id|inode
comma
id|file
comma
id|PF_ATMSVC
comma
op_amp
id|svc_seq_ops
)paren
suffix:semicolon
)brace
DECL|variable|svc_seq_fops
r_static
r_struct
id|file_operations
id|svc_seq_fops
op_assign
(brace
dot
id|open
op_assign
id|svc_seq_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|vcc_seq_release
comma
)brace
suffix:semicolon
DECL|function|proc_dev_atm_read
r_static
id|ssize_t
id|proc_dev_atm_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|atm_dev
op_star
id|dev
suffix:semicolon
r_int
r_int
id|page
suffix:semicolon
r_int
id|length
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|page
op_assign
id|get_zeroed_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|dev
op_assign
id|PDE
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
op_member_access_from_pointer
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ops-&gt;proc_read
)paren
id|length
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_else
(brace
id|length
op_assign
id|dev-&gt;ops
op_member_access_from_pointer
id|proc_read
c_func
(paren
id|dev
comma
id|pos
comma
(paren
r_char
op_star
)paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
id|count
)paren
id|length
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|length
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
(paren
r_char
op_star
)paren
id|page
comma
id|length
)paren
)paren
id|length
op_assign
op_minus
id|EFAULT
suffix:semicolon
(paren
op_star
id|pos
)paren
op_increment
suffix:semicolon
)brace
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|length
suffix:semicolon
)brace
DECL|variable|atm_proc_root
r_struct
id|proc_dir_entry
op_star
id|atm_proc_root
suffix:semicolon
DECL|variable|atm_proc_root
id|EXPORT_SYMBOL
c_func
(paren
id|atm_proc_root
)paren
suffix:semicolon
DECL|function|atm_proc_dev_register
r_int
id|atm_proc_dev_register
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
(brace
r_int
id|digits
comma
id|num
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/* No proc info */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ops-&gt;proc_read
)paren
r_return
l_int|0
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|digits
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|num
op_assign
id|dev-&gt;number
suffix:semicolon
id|num
suffix:semicolon
id|num
op_div_assign
l_int|10
)paren
id|digits
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|digits
)paren
id|digits
op_increment
suffix:semicolon
id|dev-&gt;proc_name
op_assign
id|kmalloc
c_func
(paren
id|strlen
c_func
(paren
id|dev-&gt;type
)paren
op_plus
id|digits
op_plus
l_int|2
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;proc_name
)paren
r_goto
id|err_out
suffix:semicolon
id|sprintf
c_func
(paren
id|dev-&gt;proc_name
comma
l_string|&quot;%s:%d&quot;
comma
id|dev-&gt;type
comma
id|dev-&gt;number
)paren
suffix:semicolon
id|dev-&gt;proc_entry
op_assign
id|create_proc_entry
c_func
(paren
id|dev-&gt;proc_name
comma
l_int|0
comma
id|atm_proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;proc_entry
)paren
r_goto
id|err_free_name
suffix:semicolon
id|dev-&gt;proc_entry-&gt;data
op_assign
id|dev
suffix:semicolon
id|dev-&gt;proc_entry-&gt;proc_fops
op_assign
op_amp
id|proc_atm_dev_ops
suffix:semicolon
id|dev-&gt;proc_entry-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_free_name
suffix:colon
id|kfree
c_func
(paren
id|dev-&gt;proc_name
)paren
suffix:semicolon
id|err_out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|atm_proc_dev_deregister
r_void
id|atm_proc_dev_deregister
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ops-&gt;proc_read
)paren
r_return
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|dev-&gt;proc_name
comma
id|atm_proc_root
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev-&gt;proc_name
)paren
suffix:semicolon
)brace
DECL|struct|atm_proc_entry
r_static
r_struct
id|atm_proc_entry
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|proc_fops
r_struct
id|file_operations
op_star
id|proc_fops
suffix:semicolon
DECL|member|dirent
r_struct
id|proc_dir_entry
op_star
id|dirent
suffix:semicolon
DECL|variable|atm_proc_ents
)brace
id|atm_proc_ents
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;devices&quot;
comma
dot
id|proc_fops
op_assign
op_amp
id|devices_seq_fops
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;pvc&quot;
comma
dot
id|proc_fops
op_assign
op_amp
id|pvc_seq_fops
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;svc&quot;
comma
dot
id|proc_fops
op_assign
op_amp
id|svc_seq_fops
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;vc&quot;
comma
dot
id|proc_fops
op_assign
op_amp
id|vcc_seq_fops
)brace
comma
(brace
dot
id|name
op_assign
l_int|NULL
comma
dot
id|proc_fops
op_assign
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|function|atm_proc_dirs_remove
r_static
r_void
id|atm_proc_dirs_remove
c_func
(paren
r_void
)paren
(brace
r_static
r_struct
id|atm_proc_entry
op_star
id|e
suffix:semicolon
r_for
c_loop
(paren
id|e
op_assign
id|atm_proc_ents
suffix:semicolon
id|e-&gt;name
suffix:semicolon
id|e
op_increment
)paren
(brace
r_if
c_cond
(paren
id|e-&gt;dirent
)paren
id|remove_proc_entry
c_func
(paren
id|e-&gt;name
comma
id|atm_proc_root
)paren
suffix:semicolon
)brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;net/atm&quot;
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|atm_proc_init
r_int
id|__init
id|atm_proc_init
c_func
(paren
r_void
)paren
(brace
r_static
r_struct
id|atm_proc_entry
op_star
id|e
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|atm_proc_root
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;net/atm&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atm_proc_root
)paren
r_goto
id|err_out
suffix:semicolon
r_for
c_loop
(paren
id|e
op_assign
id|atm_proc_ents
suffix:semicolon
id|e-&gt;name
suffix:semicolon
id|e
op_increment
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|dirent
suffix:semicolon
id|dirent
op_assign
id|create_proc_entry
c_func
(paren
id|e-&gt;name
comma
id|S_IRUGO
comma
id|atm_proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dirent
)paren
r_goto
id|err_out_remove
suffix:semicolon
id|dirent-&gt;proc_fops
op_assign
id|e-&gt;proc_fops
suffix:semicolon
id|dirent-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|e-&gt;dirent
op_assign
id|dirent
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
id|err_out_remove
suffix:colon
id|atm_proc_dirs_remove
c_func
(paren
)paren
suffix:semicolon
id|err_out
suffix:colon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|atm_proc_exit
r_void
id|__exit
id|atm_proc_exit
c_func
(paren
r_void
)paren
(brace
id|atm_proc_dirs_remove
c_func
(paren
)paren
suffix:semicolon
)brace
eof
