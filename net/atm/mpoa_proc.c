macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_PROC_FS
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt; 
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/atmmpc.h&gt;
macro_line|#include &lt;linux/atm.h&gt;
macro_line|#include &quot;mpc.h&quot;
macro_line|#include &quot;mpoa_caches.h&quot;
multiline_comment|/*&n; * mpoa_proc.c: Implementation MPOA client&squot;s proc&n; * file system statistics &n; */
macro_line|#if 1
DECL|macro|dprintk
mdefine_line|#define dprintk printk   /* debug */
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(format,args...)
macro_line|#endif
DECL|macro|STAT_FILE_NAME
mdefine_line|#define STAT_FILE_NAME &quot;mpc&quot;     /* Our statistic file&squot;s name */
r_extern
r_struct
id|mpoa_client
op_star
id|mpcs
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
op_star
id|atm_proc_root
suffix:semicolon
multiline_comment|/* from proc.c. */
r_static
r_int
id|proc_mpc_open
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
suffix:semicolon
r_static
id|ssize_t
id|proc_mpc_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buff
comma
r_int
id|nbytes
comma
id|loff_t
op_star
id|ppos
)paren
suffix:semicolon
r_static
r_int
id|parse_qos
c_func
(paren
r_const
r_char
op_star
id|buff
)paren
suffix:semicolon
multiline_comment|/*&n; *   Define allowed FILE OPERATIONS&n; */
DECL|variable|mpc_file_operations
r_static
r_struct
id|file_operations
id|mpc_file_operations
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|proc_mpc_open
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
id|write
op_assign
id|proc_mpc_write
comma
dot
id|release
op_assign
id|seq_release
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Returns the state of an ingress cache entry as a string&n; */
DECL|function|ingress_state_string
r_static
r_const
r_char
(def_block
op_star
id|ingress_state_string
c_func
(paren
r_int
id|state
)paren
(brace
r_switch
c_cond
(paren
id|state
)paren
(brace
r_case
id|INGRESS_RESOLVING
suffix:colon
r_return
l_string|&quot;resolving  &quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INGRESS_RESOLVED
suffix:colon
r_return
l_string|&quot;resolved   &quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INGRESS_INVALID
suffix:colon
r_return
l_string|&quot;invalid    &quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INGRESS_REFRESHING
suffix:colon
r_return
l_string|&quot;refreshing &quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;&quot;
suffix:semicolon
)brace
)brace
)def_block
multiline_comment|/*&n; * Returns the state of an egress cache entry as a string&n; */
DECL|function|egress_state_string
r_static
r_const
r_char
(def_block
op_star
id|egress_state_string
c_func
(paren
r_int
id|state
)paren
(brace
r_switch
c_cond
(paren
id|state
)paren
(brace
r_case
id|EGRESS_RESOLVED
suffix:colon
r_return
l_string|&quot;resolved   &quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EGRESS_PURGE
suffix:colon
r_return
l_string|&quot;purge      &quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EGRESS_INVALID
suffix:colon
r_return
l_string|&quot;invalid    &quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;&quot;
suffix:semicolon
)brace
)brace
)def_block
multiline_comment|/*&n; * FIXME: mpcs (and per-mpc lists) have no locking whatsoever.&n; */
DECL|function|mpc_start
r_static
r_void
op_star
id|mpc_start
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
id|loff_t
op_star
id|pos
)paren
(brace
id|loff_t
id|l
op_assign
op_star
id|pos
suffix:semicolon
r_struct
id|mpoa_client
op_star
id|mpc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|l
op_decrement
)paren
r_return
id|SEQ_START_TOKEN
suffix:semicolon
r_for
c_loop
(paren
id|mpc
op_assign
id|mpcs
suffix:semicolon
id|mpc
suffix:semicolon
id|mpc
op_assign
id|mpc-&gt;next
)paren
r_if
c_cond
(paren
op_logical_neg
id|l
op_decrement
)paren
r_return
id|mpc
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|mpc_next
r_static
r_void
op_star
id|mpc_next
c_func
(paren
r_struct
id|seq_file
op_star
id|m
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
id|mpoa_client
op_star
id|p
op_assign
id|v
suffix:semicolon
(paren
op_star
id|pos
)paren
op_increment
suffix:semicolon
r_return
id|v
op_eq
id|SEQ_START_TOKEN
ques
c_cond
id|mpcs
suffix:colon
id|p-&gt;next
suffix:semicolon
)brace
DECL|function|mpc_stop
r_static
r_void
id|mpc_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
)brace
multiline_comment|/*&n; * READING function - called when the /proc/atm/mpoa file is read from.&n; */
DECL|function|mpc_show
r_static
r_int
id|mpc_show
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
r_struct
id|mpoa_client
op_star
id|mpc
op_assign
id|v
suffix:semicolon
r_int
r_char
op_star
id|temp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|in_cache_entry
op_star
id|in_entry
suffix:semicolon
id|eg_cache_entry
op_star
id|eg_entry
suffix:semicolon
r_struct
id|timeval
id|now
suffix:semicolon
r_int
r_char
id|ip_string
(braket
l_int|16
)braket
suffix:semicolon
r_if
c_cond
(paren
id|v
op_eq
id|SEQ_START_TOKEN
)paren
(brace
id|atm_mpoa_disp_qos
c_func
(paren
id|m
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;&bslash;nInterface %d:&bslash;n&bslash;n&quot;
comma
id|mpc-&gt;dev_num
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Ingress Entries:&bslash;nIP address      State      Holding time  Packets fwded  VPI  VCI&bslash;n&quot;
)paren
suffix:semicolon
id|do_gettimeofday
c_func
(paren
op_amp
id|now
)paren
suffix:semicolon
r_for
c_loop
(paren
id|in_entry
op_assign
id|mpc-&gt;in_cache
suffix:semicolon
id|in_entry
suffix:semicolon
id|in_entry
op_assign
id|in_entry-&gt;next
)paren
(brace
id|temp
op_assign
(paren
r_int
r_char
op_star
)paren
op_amp
id|in_entry-&gt;ctrl_info.in_dst_ip
suffix:semicolon
id|sprintf
c_func
(paren
id|ip_string
comma
l_string|&quot;%d.%d.%d.%d&quot;
comma
id|temp
(braket
l_int|0
)braket
comma
id|temp
(braket
l_int|1
)braket
comma
id|temp
(braket
l_int|2
)braket
comma
id|temp
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%-16s%s%-14lu%-12u&quot;
comma
id|ip_string
comma
id|ingress_state_string
c_func
(paren
id|in_entry-&gt;entry_state
)paren
comma
id|in_entry-&gt;ctrl_info.holding_time
op_minus
(paren
id|now.tv_sec
op_minus
id|in_entry-&gt;tv.tv_sec
)paren
comma
id|in_entry-&gt;packets_fwded
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_entry-&gt;shortcut
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;   %-3d  %-3d&quot;
comma
id|in_entry-&gt;shortcut-&gt;vpi
comma
id|in_entry-&gt;shortcut-&gt;vci
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Egress Entries:&bslash;nIngress MPC ATM addr&bslash;nCache-id        State      Holding time  Packets recvd  Latest IP addr   VPI VCI&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|eg_entry
op_assign
id|mpc-&gt;eg_cache
suffix:semicolon
id|eg_entry
suffix:semicolon
id|eg_entry
op_assign
id|eg_entry-&gt;next
)paren
(brace
r_int
r_char
op_star
id|p
op_assign
id|eg_entry-&gt;ctrl_info.in_MPC_data_ATM_addr
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
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%02x&quot;
comma
id|p
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;&bslash;n%-16lu%s%-14lu%-15u&quot;
comma
(paren
r_int
r_int
)paren
id|ntohl
c_func
(paren
id|eg_entry-&gt;ctrl_info.cache_id
)paren
comma
id|egress_state_string
c_func
(paren
id|eg_entry-&gt;entry_state
)paren
comma
(paren
id|eg_entry-&gt;ctrl_info.holding_time
op_minus
(paren
id|now.tv_sec
op_minus
id|eg_entry-&gt;tv.tv_sec
)paren
)paren
comma
id|eg_entry-&gt;packets_rcvd
)paren
suffix:semicolon
multiline_comment|/* latest IP address */
id|temp
op_assign
(paren
r_int
r_char
op_star
)paren
op_amp
id|eg_entry-&gt;latest_ip_addr
suffix:semicolon
id|sprintf
c_func
(paren
id|ip_string
comma
l_string|&quot;%d.%d.%d.%d&quot;
comma
id|temp
(braket
l_int|0
)braket
comma
id|temp
(braket
l_int|1
)braket
comma
id|temp
(braket
l_int|2
)braket
comma
id|temp
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%-16s&quot;
comma
id|ip_string
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eg_entry-&gt;shortcut
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot; %-3d %-3d&quot;
comma
id|eg_entry-&gt;shortcut-&gt;vpi
comma
id|eg_entry-&gt;shortcut-&gt;vci
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mpc_op
r_static
r_struct
id|seq_operations
id|mpc_op
op_assign
(brace
dot
id|start
op_assign
id|mpc_start
comma
dot
id|next
op_assign
id|mpc_next
comma
dot
id|stop
op_assign
id|mpc_stop
comma
dot
id|show
op_assign
id|mpc_show
)brace
suffix:semicolon
DECL|function|proc_mpc_open
r_static
r_int
id|proc_mpc_open
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
id|mpc_op
)paren
suffix:semicolon
)brace
DECL|function|proc_mpc_write
r_static
id|ssize_t
id|proc_mpc_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buff
comma
r_int
id|nbytes
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_char
op_star
id|page
comma
op_star
id|p
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
op_ge
id|PAGE_SIZE
)paren
id|nbytes
op_assign
id|PAGE_SIZE
op_minus
l_int|1
suffix:semicolon
id|page
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
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
r_for
c_loop
(paren
id|p
op_assign
id|page
comma
id|len
op_assign
l_int|0
suffix:semicolon
id|len
OL
id|nbytes
suffix:semicolon
id|p
op_increment
comma
id|len
op_increment
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
op_star
id|p
comma
id|buff
op_increment
)paren
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_or
op_star
id|p
op_eq
l_char|&squot;&bslash;n&squot;
)paren
r_break
suffix:semicolon
)brace
op_star
id|p
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parse_qos
c_func
(paren
id|page
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;mpoa: proc_mpc_write: could not parse &squot;%s&squot;&bslash;n&quot;
comma
id|page
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|parse_qos
r_static
r_int
id|parse_qos
c_func
(paren
r_const
r_char
op_star
id|buff
)paren
(brace
multiline_comment|/* possible lines look like this&n;         * add 130.230.54.142 tx=max_pcr,max_sdu rx=max_pcr,max_sdu&n;         */
r_int
r_char
id|ip
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|tx_pcr
comma
id|tx_sdu
comma
id|rx_pcr
comma
id|rx_sdu
suffix:semicolon
r_uint32
id|ipaddr
suffix:semicolon
r_struct
id|atm_qos
id|qos
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|qos
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|atm_qos
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|buff
comma
l_string|&quot;del %hhu.%hhu.%hhu.%hhu&quot;
comma
id|ip
comma
id|ip
op_plus
l_int|1
comma
id|ip
op_plus
l_int|2
comma
id|ip
op_plus
l_int|3
)paren
op_eq
l_int|4
)paren
(brace
id|ipaddr
op_assign
op_star
(paren
r_uint32
op_star
)paren
id|ip
suffix:semicolon
r_return
id|atm_mpoa_delete_qos
c_func
(paren
id|atm_mpoa_search_qos
c_func
(paren
id|ipaddr
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|buff
comma
l_string|&quot;add %hhu.%hhu.%hhu.%hhu tx=%d,%d rx=tx&quot;
comma
id|ip
comma
id|ip
op_plus
l_int|1
comma
id|ip
op_plus
l_int|2
comma
id|ip
op_plus
l_int|3
comma
op_amp
id|tx_pcr
comma
op_amp
id|tx_sdu
)paren
op_eq
l_int|6
)paren
(brace
id|rx_pcr
op_assign
id|tx_pcr
suffix:semicolon
id|rx_sdu
op_assign
id|tx_sdu
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|buff
comma
l_string|&quot;add %hhu.%hhu.%hhu.%hhu tx=%d,%d rx=%d,%d&quot;
comma
id|ip
comma
id|ip
op_plus
l_int|1
comma
id|ip
op_plus
l_int|2
comma
id|ip
op_plus
l_int|3
comma
op_amp
id|tx_pcr
comma
op_amp
id|tx_sdu
comma
op_amp
id|rx_pcr
comma
op_amp
id|rx_sdu
)paren
op_ne
l_int|8
)paren
r_return
l_int|0
suffix:semicolon
id|ipaddr
op_assign
op_star
(paren
r_uint32
op_star
)paren
id|ip
suffix:semicolon
id|qos.txtp.traffic_class
op_assign
id|ATM_CBR
suffix:semicolon
id|qos.txtp.max_pcr
op_assign
id|tx_pcr
suffix:semicolon
id|qos.txtp.max_sdu
op_assign
id|tx_sdu
suffix:semicolon
id|qos.rxtp.traffic_class
op_assign
id|ATM_CBR
suffix:semicolon
id|qos.rxtp.max_pcr
op_assign
id|rx_pcr
suffix:semicolon
id|qos.rxtp.max_sdu
op_assign
id|rx_sdu
suffix:semicolon
id|qos.aal
op_assign
id|ATM_AAL5
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;mpoa: mpoa_proc.c: parse_qos(): setting qos paramameters to tx=%d,%d rx=%d,%d&bslash;n&quot;
comma
id|qos.txtp.max_pcr
comma
id|qos.txtp.max_sdu
comma
id|qos.rxtp.max_pcr
comma
id|qos.rxtp.max_sdu
)paren
suffix:semicolon
id|atm_mpoa_add_qos
c_func
(paren
id|ipaddr
comma
op_amp
id|qos
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * INITIALIZATION function - called when module is initialized/loaded.&n; */
DECL|function|mpc_proc_init
r_int
id|mpc_proc_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|p
suffix:semicolon
id|p
op_assign
id|create_proc_entry
c_func
(paren
id|STAT_FILE_NAME
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
id|p
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unable to initialize /proc/atm/%s&bslash;n&quot;
comma
id|STAT_FILE_NAME
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|p-&gt;proc_fops
op_assign
op_amp
id|mpc_file_operations
suffix:semicolon
id|p-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * DELETING function - called when module is removed.&n; */
DECL|function|mpc_proc_clean
r_void
id|mpc_proc_clean
c_func
(paren
r_void
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|STAT_FILE_NAME
comma
id|atm_proc_root
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PROC_FS */
eof
