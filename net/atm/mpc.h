macro_line|#ifndef _MPC_H_
DECL|macro|_MPC_H_
mdefine_line|#define _MPC_H_
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/atm.h&gt;
macro_line|#include &lt;linux/atmmpc.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &quot;mpoa_caches.h&quot;
multiline_comment|/* kernel -&gt; mpc-daemon */
r_int
id|msg_to_mpoad
c_func
(paren
r_struct
id|k_message
op_star
id|msg
comma
r_struct
id|mpoa_client
op_star
id|mpc
)paren
suffix:semicolon
DECL|struct|mpoa_client
r_struct
id|mpoa_client
(brace
DECL|member|next
r_struct
id|mpoa_client
op_star
id|next
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* lec in question                     */
DECL|member|dev_num
r_int
id|dev_num
suffix:semicolon
multiline_comment|/* e.g. 2 for lec2                     */
DECL|member|old_hard_start_xmit
r_int
(paren
op_star
id|old_hard_start_xmit
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|mpoad_vcc
r_struct
id|atm_vcc
op_star
id|mpoad_vcc
suffix:semicolon
multiline_comment|/* control channel to mpoad            */
DECL|member|mps_ctrl_addr
r_uint8
id|mps_ctrl_addr
(braket
id|ATM_ESA_LEN
)braket
suffix:semicolon
multiline_comment|/* MPS control ATM address     */
DECL|member|our_ctrl_addr
r_uint8
id|our_ctrl_addr
(braket
id|ATM_ESA_LEN
)braket
suffix:semicolon
multiline_comment|/* MPC&squot;s control ATM address   */
DECL|member|ingress_lock
id|rwlock_t
id|ingress_lock
suffix:semicolon
DECL|member|in_ops
r_struct
id|in_cache_ops
op_star
id|in_ops
suffix:semicolon
multiline_comment|/* ingress cache operations            */
DECL|member|in_cache
id|in_cache_entry
op_star
id|in_cache
suffix:semicolon
multiline_comment|/* the ingress cache of this MPC       */
DECL|member|egress_lock
id|rwlock_t
id|egress_lock
suffix:semicolon
DECL|member|eg_ops
r_struct
id|eg_cache_ops
op_star
id|eg_ops
suffix:semicolon
multiline_comment|/* egress cache operations             */
DECL|member|eg_cache
id|eg_cache_entry
op_star
id|eg_cache
suffix:semicolon
multiline_comment|/* the egress  cache of this MPC       */
DECL|member|mps_macs
r_uint8
op_star
id|mps_macs
suffix:semicolon
multiline_comment|/* array of MPS MAC addresses, &gt;=1     */
DECL|member|number_of_mps_macs
r_int
id|number_of_mps_macs
suffix:semicolon
multiline_comment|/* number of the above MAC addresses   */
DECL|member|parameters
r_struct
id|mpc_parameters
id|parameters
suffix:semicolon
multiline_comment|/* parameters for this client    */
)brace
suffix:semicolon
DECL|struct|atm_mpoa_qos
r_struct
id|atm_mpoa_qos
(brace
DECL|member|next
r_struct
id|atm_mpoa_qos
op_star
id|next
suffix:semicolon
DECL|member|ipaddr
r_uint32
id|ipaddr
suffix:semicolon
DECL|member|qos
r_struct
id|atm_qos
id|qos
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* MPOA QoS operations */
r_struct
id|atm_mpoa_qos
op_star
id|atm_mpoa_add_qos
c_func
(paren
r_uint32
id|dst_ip
comma
r_struct
id|atm_qos
op_star
id|qos
)paren
suffix:semicolon
r_struct
id|atm_mpoa_qos
op_star
id|atm_mpoa_search_qos
c_func
(paren
r_uint32
id|dst_ip
)paren
suffix:semicolon
r_int
id|atm_mpoa_delete_qos
c_func
(paren
r_struct
id|atm_mpoa_qos
op_star
id|qos
)paren
suffix:semicolon
multiline_comment|/* Display QoS entries. This is for the procfs */
r_struct
id|seq_file
suffix:semicolon
r_void
id|atm_mpoa_disp_qos
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
suffix:semicolon
macro_line|#endif /* _MPC_H_ */
eof
