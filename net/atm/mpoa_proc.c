macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_PROC_FS
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt; 
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/time.h&gt;
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
id|ssize_t
id|proc_mpc_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buff
comma
r_int
id|count
comma
id|loff_t
op_star
id|pos
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
comma
r_int
id|len
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
id|read
op_assign
id|proc_mpc_read
comma
dot
id|write
op_assign
id|proc_mpc_write
comma
)brace
suffix:semicolon
DECL|function|print_header
r_static
r_int
(def_block
id|print_header
c_func
(paren
r_char
op_star
id|buff
comma
r_struct
id|mpoa_client
op_star
id|mpc
)paren
(brace
r_if
c_cond
(paren
id|mpc
op_ne
l_int|NULL
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|buff
comma
l_string|&quot;&bslash;nInterface %d:&bslash;n&bslash;n&quot;
comma
id|mpc-&gt;dev_num
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
)def_block
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
multiline_comment|/*&n; * READING function - called when the /proc/atm/mpoa file is read from.&n; */
DECL|function|proc_mpc_read
r_static
id|ssize_t
(def_block
id|proc_mpc_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buff
comma
r_int
id|count
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_int
r_int
id|page
op_assign
l_int|0
suffix:semicolon
r_int
r_char
op_star
id|temp
suffix:semicolon
id|ssize_t
id|length
op_assign
l_int|0
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_struct
id|mpoa_client
op_star
id|mpc
op_assign
id|mpcs
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
id|count
op_eq
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
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
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|atm_mpoa_disp_qos
c_func
(paren
(paren
r_char
op_star
)paren
id|page
comma
op_amp
id|length
)paren
suffix:semicolon
r_while
c_loop
(paren
id|mpc
op_ne
l_int|NULL
)paren
(brace
id|length
op_add_assign
id|print_header
c_func
(paren
(paren
r_char
op_star
)paren
id|page
op_plus
id|length
comma
id|mpc
)paren
suffix:semicolon
id|length
op_add_assign
id|sprintf
c_func
(paren
(paren
r_char
op_star
)paren
id|page
op_plus
id|length
comma
l_string|&quot;Ingress Entries:&bslash;nIP address      State      Holding time  Packets fwded  VPI  VCI&bslash;n&quot;
)paren
suffix:semicolon
id|in_entry
op_assign
id|mpc-&gt;in_cache
suffix:semicolon
id|do_gettimeofday
c_func
(paren
op_amp
id|now
)paren
suffix:semicolon
r_while
c_loop
(paren
id|in_entry
op_ne
l_int|NULL
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
id|length
op_add_assign
id|sprintf
c_func
(paren
(paren
r_char
op_star
)paren
id|page
op_plus
id|length
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
(paren
id|in_entry-&gt;ctrl_info.holding_time
op_minus
(paren
id|now.tv_sec
op_minus
id|in_entry-&gt;tv.tv_sec
)paren
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
(brace
id|length
op_add_assign
id|sprintf
c_func
(paren
(paren
r_char
op_star
)paren
id|page
op_plus
id|length
comma
l_string|&quot;   %-3d  %-3d&quot;
comma
id|in_entry-&gt;shortcut-&gt;vpi
comma
id|in_entry-&gt;shortcut-&gt;vci
)paren
suffix:semicolon
)brace
id|length
op_add_assign
id|sprintf
c_func
(paren
(paren
r_char
op_star
)paren
id|page
op_plus
id|length
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|in_entry
op_assign
id|in_entry-&gt;next
suffix:semicolon
)brace
id|length
op_add_assign
id|sprintf
c_func
(paren
(paren
r_char
op_star
)paren
id|page
op_plus
id|length
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|eg_entry
op_assign
id|mpc-&gt;eg_cache
suffix:semicolon
id|length
op_add_assign
id|sprintf
c_func
(paren
(paren
r_char
op_star
)paren
id|page
op_plus
id|length
comma
l_string|&quot;Egress Entries:&bslash;nIngress MPC ATM addr&bslash;nCache-id        State      Holding time  Packets recvd  Latest IP addr   VPI VCI&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|eg_entry
op_ne
l_int|NULL
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
id|ATM_ESA_LEN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|length
op_add_assign
id|sprintf
c_func
(paren
(paren
r_char
op_star
)paren
id|page
op_plus
id|length
comma
l_string|&quot;%02x&quot;
comma
id|eg_entry-&gt;ctrl_info.in_MPC_data_ATM_addr
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|length
op_add_assign
id|sprintf
c_func
(paren
(paren
r_char
op_star
)paren
id|page
op_plus
id|length
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
id|length
op_add_assign
id|sprintf
c_func
(paren
(paren
r_char
op_star
)paren
id|page
op_plus
id|length
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
(brace
id|length
op_add_assign
id|sprintf
c_func
(paren
(paren
r_char
op_star
)paren
id|page
op_plus
id|length
comma
l_string|&quot; %-3d %-3d&quot;
comma
id|eg_entry-&gt;shortcut-&gt;vpi
comma
id|eg_entry-&gt;shortcut-&gt;vci
)paren
suffix:semicolon
)brace
id|length
op_add_assign
id|sprintf
c_func
(paren
(paren
r_char
op_star
)paren
id|page
op_plus
id|length
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|eg_entry
op_assign
id|eg_entry-&gt;next
suffix:semicolon
)brace
id|length
op_add_assign
id|sprintf
c_func
(paren
(paren
r_char
op_star
)paren
id|page
op_plus
id|length
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|mpc
op_assign
id|mpc-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|pos
op_ge
id|length
)paren
id|length
op_assign
l_int|0
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
(paren
id|count
op_plus
op_star
id|pos
)paren
OG
id|length
)paren
id|count
op_assign
id|length
op_minus
op_star
id|pos
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buff
comma
(paren
r_char
op_star
)paren
id|page
comma
id|count
)paren
)paren
(brace
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
op_star
id|pos
op_add_assign
id|count
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
)def_block
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
r_int
id|incoming
comma
id|error
comma
id|retval
suffix:semicolon
r_char
op_star
id|page
comma
id|c
suffix:semicolon
r_const
r_char
op_star
id|tmp
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
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|buff
comma
id|nbytes
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
id|page
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|incoming
op_assign
l_int|0
suffix:semicolon
id|tmp
op_assign
id|buff
suffix:semicolon
r_while
c_loop
(paren
id|incoming
OL
id|nbytes
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|c
comma
id|tmp
op_increment
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|incoming
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_or
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
r_break
suffix:semicolon
)brace
id|retval
op_assign
id|copy_from_user
c_func
(paren
id|page
comma
id|buff
comma
id|incoming
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mpoa: proc_mpc_write: copy_from_user() failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
op_star
id|ppos
op_add_assign
id|incoming
suffix:semicolon
id|page
(braket
id|incoming
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|retval
op_assign
id|parse_qos
c_func
(paren
id|page
comma
id|incoming
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
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
id|nbytes
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
comma
r_int
id|len
)paren
(brace
multiline_comment|/* possible lines look like this&n;         * add 130.230.54.142 tx=max_pcr,max_sdu rx=max_pcr,max_sdu&n;         */
r_int
id|pos
comma
id|i
suffix:semicolon
r_uint32
id|ipaddr
suffix:semicolon
r_int
r_char
id|ip
(braket
l_int|4
)braket
suffix:semicolon
r_char
id|cmd
(braket
l_int|4
)braket
comma
id|temp
(braket
l_int|256
)braket
suffix:semicolon
r_const
r_char
op_star
id|tmp
comma
op_star
id|prev
suffix:semicolon
r_struct
id|atm_qos
id|qos
suffix:semicolon
r_int
id|value
(braket
l_int|5
)braket
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
id|strncpy
c_func
(paren
id|cmd
comma
id|buff
comma
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|cmd
comma
l_string|&quot;add&quot;
comma
l_int|3
)paren
op_logical_and
id|strncmp
c_func
(paren
id|cmd
comma
l_string|&quot;del&quot;
comma
l_int|3
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* not add or del */
id|pos
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* next parse ip */
id|prev
op_assign
id|buff
op_plus
id|pos
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tmp
op_assign
id|strchr
c_func
(paren
id|prev
comma
l_char|&squot;.&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|temp
comma
l_char|&squot;&bslash;0&squot;
comma
l_int|256
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|temp
comma
id|prev
comma
id|tmp
op_minus
id|prev
)paren
suffix:semicolon
id|ip
(braket
id|i
)braket
op_assign
(paren
r_char
)paren
id|simple_strtoul
c_func
(paren
id|temp
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|tmp
op_increment
suffix:semicolon
id|prev
op_assign
id|tmp
suffix:semicolon
)brace
id|tmp
op_assign
id|strchr
c_func
(paren
id|prev
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|temp
comma
l_char|&squot;&bslash;0&squot;
comma
l_int|256
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|temp
comma
id|prev
comma
id|tmp
op_minus
id|prev
)paren
suffix:semicolon
id|ip
(braket
id|i
)braket
op_assign
(paren
r_char
)paren
id|simple_strtoul
c_func
(paren
id|temp
comma
l_int|NULL
comma
l_int|0
)paren
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
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|cmd
comma
l_string|&quot;del&quot;
comma
l_int|3
)paren
)paren
(brace
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
multiline_comment|/* next transmit values */
id|tmp
op_assign
id|strstr
c_func
(paren
id|buff
comma
l_string|&quot;tx=&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|tmp
op_add_assign
l_int|3
suffix:semicolon
id|prev
op_assign
id|tmp
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
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tmp
op_assign
id|strchr
c_func
(paren
id|prev
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|temp
comma
l_char|&squot;&bslash;0&squot;
comma
l_int|256
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|temp
comma
id|prev
comma
id|tmp
op_minus
id|prev
)paren
suffix:semicolon
id|value
(braket
id|i
)braket
op_assign
(paren
r_int
)paren
id|simple_strtoul
c_func
(paren
id|temp
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|tmp
op_increment
suffix:semicolon
id|prev
op_assign
id|tmp
suffix:semicolon
)brace
id|tmp
op_assign
id|strchr
c_func
(paren
id|prev
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|temp
comma
l_char|&squot;&bslash;0&squot;
comma
l_int|256
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|temp
comma
id|prev
comma
id|tmp
op_minus
id|prev
)paren
suffix:semicolon
id|value
(braket
id|i
)braket
op_assign
(paren
r_int
)paren
id|simple_strtoul
c_func
(paren
id|temp
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|qos.txtp.traffic_class
op_assign
id|ATM_CBR
suffix:semicolon
id|qos.txtp.max_pcr
op_assign
id|value
(braket
l_int|0
)braket
suffix:semicolon
id|qos.txtp.max_sdu
op_assign
id|value
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* next receive values */
id|tmp
op_assign
id|strstr
c_func
(paren
id|buff
comma
l_string|&quot;rx=&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|buff
comma
l_string|&quot;rx=tx&quot;
)paren
)paren
(brace
multiline_comment|/* rx == tx */
id|qos.rxtp.traffic_class
op_assign
id|qos.txtp.traffic_class
suffix:semicolon
id|qos.rxtp.max_pcr
op_assign
id|qos.txtp.max_pcr
suffix:semicolon
id|qos.rxtp.max_cdv
op_assign
id|qos.txtp.max_cdv
suffix:semicolon
id|qos.rxtp.max_sdu
op_assign
id|qos.txtp.max_sdu
suffix:semicolon
)brace
r_else
(brace
id|tmp
op_add_assign
l_int|3
suffix:semicolon
id|prev
op_assign
id|tmp
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
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tmp
op_assign
id|strchr
c_func
(paren
id|prev
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|temp
comma
l_char|&squot;&bslash;0&squot;
comma
l_int|256
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|temp
comma
id|prev
comma
id|tmp
op_minus
id|prev
)paren
suffix:semicolon
id|value
(braket
id|i
)braket
op_assign
(paren
r_int
)paren
id|simple_strtoul
c_func
(paren
id|temp
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|tmp
op_increment
suffix:semicolon
id|prev
op_assign
id|tmp
suffix:semicolon
)brace
id|tmp
op_assign
id|strchr
c_func
(paren
id|prev
comma
l_char|&squot;&bslash;0&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|temp
comma
l_char|&squot;&bslash;0&squot;
comma
l_int|256
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|temp
comma
id|prev
comma
id|tmp
op_minus
id|prev
)paren
suffix:semicolon
id|value
(braket
id|i
)braket
op_assign
(paren
r_int
)paren
id|simple_strtoul
c_func
(paren
id|temp
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|qos.rxtp.traffic_class
op_assign
id|ATM_CBR
suffix:semicolon
id|qos.rxtp.max_pcr
op_assign
id|value
(braket
l_int|0
)braket
suffix:semicolon
id|qos.rxtp.max_sdu
op_assign
id|value
(braket
l_int|1
)braket
suffix:semicolon
)brace
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
