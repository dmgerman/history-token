multiline_comment|/*&n; * Description: EBTables 802.1Q match extension kernelspace module.&n; * Authors: Nick Fedchik &lt;nick@fedchik.org.ua&gt;&n; *          Bart De Schuymer &lt;bdschuym@pandora.be&gt;&n; *    &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *  &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/if_vlan.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netfilter_bridge/ebtables.h&gt;
macro_line|#include &lt;linux/netfilter_bridge/ebt_vlan.h&gt;
DECL|variable|debug
r_static
r_int
r_char
id|debug
suffix:semicolon
DECL|macro|MODULE_VERSION
mdefine_line|#define MODULE_VERSION &quot;0.6&quot;
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;0-1b&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;debug=1 is turn on debug messages&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Nick Fedchik &lt;nick@fedchik.org.ua&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;802.1Q match module (ebtables extension), v&quot;
id|MODULE_VERSION
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|DEBUG_MSG
mdefine_line|#define DEBUG_MSG(...) if (debug) printk (KERN_DEBUG &quot;ebt_vlan: &quot; __VA_ARGS__)
DECL|macro|INV_FLAG
mdefine_line|#define INV_FLAG(_inv_flag_) (info-&gt;invflags &amp; _inv_flag_) ? &quot;!&quot; : &quot;&quot;
DECL|macro|GET_BITMASK
mdefine_line|#define GET_BITMASK(_BIT_MASK_) info-&gt;bitmask &amp; _BIT_MASK_
DECL|macro|SET_BITMASK
mdefine_line|#define SET_BITMASK(_BIT_MASK_) info-&gt;bitmask |= _BIT_MASK_
DECL|macro|EXIT_ON_MISMATCH
mdefine_line|#define EXIT_ON_MISMATCH(_MATCH_,_MASK_) if (!((info-&gt;_MATCH_ == _MATCH_)^!!(info-&gt;invflags &amp; _MASK_))) return 1;
multiline_comment|/*&n; * Function description: ebt_filter_vlan() is main engine for &n; * checking passed 802.1Q frame according to &n; * the passed extension parameters (in the *data buffer)&n; * ebt_filter_vlan() is called after successfull check the rule params&n; * by ebt_check_vlan() function.&n; * Parameters:&n; * const struct sk_buff *skb - pointer to passed ethernet frame buffer&n; * const void *data - pointer to passed extension parameters&n; * unsigned int datalen - length of passed *data buffer&n; * const struct net_device *in  -&n; * const struct net_device *out -&n; * const struct ebt_counter *c -&n; * Returned values:&n; * 0 - ok (all rule params matched)&n; * 1 - miss (rule params not acceptable to the parsed frame)&n; */
r_static
r_int
DECL|function|ebt_filter_vlan
id|ebt_filter_vlan
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_const
r_struct
id|net_device
op_star
id|in
comma
r_const
r_struct
id|net_device
op_star
id|out
comma
r_const
r_void
op_star
id|data
comma
r_int
r_int
id|datalen
)paren
(brace
r_struct
id|ebt_vlan_info
op_star
id|info
op_assign
(paren
r_struct
id|ebt_vlan_info
op_star
)paren
id|data
suffix:semicolon
multiline_comment|/* userspace data */
r_struct
id|vlan_ethhdr
op_star
id|frame
op_assign
(paren
r_struct
id|vlan_ethhdr
op_star
)paren
id|skb-&gt;mac.raw
suffix:semicolon
multiline_comment|/* Passed tagged frame */
r_int
r_int
id|TCI
suffix:semicolon
multiline_comment|/* Whole TCI, given from parsed frame */
r_int
r_int
id|id
suffix:semicolon
multiline_comment|/* VLAN ID, given from frame TCI */
r_int
r_char
id|prio
suffix:semicolon
multiline_comment|/* user_priority, given from frame TCI */
r_int
r_int
id|encap
suffix:semicolon
multiline_comment|/* VLAN encapsulated Type/Length field, given from orig frame */
multiline_comment|/*&n;&t; * Tag Control Information (TCI) consists of the following elements:&n;&t; * - User_priority. The user_priority field is three bits in length, &n;&t; * interpreted as a binary number. &n;&t; * - Canonical Format Indicator (CFI). The Canonical Format Indicator &n;&t; * (CFI) is a single bit flag value. Currently ignored.&n;&t; * - VLAN Identifier (VID). The VID is encoded as &n;&t; * an unsigned binary number. &n;&t; */
id|TCI
op_assign
id|ntohs
c_func
(paren
id|frame-&gt;h_vlan_TCI
)paren
suffix:semicolon
id|id
op_assign
id|TCI
op_amp
id|VLAN_VID_MASK
suffix:semicolon
id|prio
op_assign
(paren
id|TCI
op_rshift
l_int|13
)paren
op_amp
l_int|0x7
suffix:semicolon
id|encap
op_assign
id|frame-&gt;h_vlan_encapsulated_proto
suffix:semicolon
multiline_comment|/*&n;&t; * Checking VLAN Identifier (VID)&n;&t; */
r_if
c_cond
(paren
id|GET_BITMASK
c_func
(paren
id|EBT_VLAN_ID
)paren
)paren
(brace
multiline_comment|/* Is VLAN ID parsed? */
id|EXIT_ON_MISMATCH
c_func
(paren
id|id
comma
id|EBT_VLAN_ID
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Checking user_priority&n;&t; */
r_if
c_cond
(paren
id|GET_BITMASK
c_func
(paren
id|EBT_VLAN_PRIO
)paren
)paren
(brace
multiline_comment|/* Is VLAN user_priority parsed? */
id|EXIT_ON_MISMATCH
c_func
(paren
id|prio
comma
id|EBT_VLAN_PRIO
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Checking Encapsulated Proto (Length/Type) field&n;&t; */
r_if
c_cond
(paren
id|GET_BITMASK
c_func
(paren
id|EBT_VLAN_ENCAP
)paren
)paren
(brace
multiline_comment|/* Is VLAN Encap parsed? */
id|EXIT_ON_MISMATCH
c_func
(paren
id|encap
comma
id|EBT_VLAN_ENCAP
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * All possible extension parameters was parsed.&n;&t; * If rule never returned by missmatch, then all ok.&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function description: ebt_vlan_check() is called when userspace &n; * delivers the table entry to the kernel, &n; * and to check that userspace doesn&squot;t give a bad table.&n; * Parameters:&n; * const char *tablename - table name string&n; * unsigned int hooknr - hook number&n; * const struct ebt_entry *e - ebtables entry basic set&n; * const void *data - pointer to passed extension parameters&n; * unsigned int datalen - length of passed *data buffer&n; * Returned values:&n; * 0 - ok (all delivered rule params are correct)&n; * 1 - miss (rule params is out of range, invalid, incompatible, etc.)&n; */
r_static
r_int
DECL|function|ebt_check_vlan
id|ebt_check_vlan
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_int
r_int
id|hooknr
comma
r_const
r_struct
id|ebt_entry
op_star
id|e
comma
r_void
op_star
id|data
comma
r_int
r_int
id|datalen
)paren
(brace
r_struct
id|ebt_vlan_info
op_star
id|info
op_assign
(paren
r_struct
id|ebt_vlan_info
op_star
)paren
id|data
suffix:semicolon
multiline_comment|/*&n;&t; * Parameters buffer overflow check &n;&t; */
r_if
c_cond
(paren
id|datalen
op_ne
r_sizeof
(paren
r_struct
id|ebt_vlan_info
)paren
)paren
(brace
id|DEBUG_MSG
(paren
l_string|&quot;passed size %d is not eq to ebt_vlan_info (%Zd)&bslash;n&quot;
comma
id|datalen
comma
r_sizeof
(paren
r_struct
id|ebt_vlan_info
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Is it 802.1Q frame checked?&n;&t; */
r_if
c_cond
(paren
id|e-&gt;ethproto
op_ne
id|__constant_htons
c_func
(paren
id|ETH_P_8021Q
)paren
)paren
(brace
id|DEBUG_MSG
(paren
l_string|&quot;passed entry proto %2.4X is not 802.1Q (8100)&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|ntohs
c_func
(paren
id|e-&gt;ethproto
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Check for bitmask range &n;&t; * True if even one bit is out of mask&n;&t; */
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
op_complement
id|EBT_VLAN_MASK
)paren
(brace
id|DEBUG_MSG
c_func
(paren
l_string|&quot;bitmask %2X is out of mask (%2X)&bslash;n&quot;
comma
id|info-&gt;bitmask
comma
id|EBT_VLAN_MASK
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Check for inversion flags range &n;&t; */
r_if
c_cond
(paren
id|info-&gt;invflags
op_amp
op_complement
id|EBT_VLAN_MASK
)paren
(brace
id|DEBUG_MSG
c_func
(paren
l_string|&quot;inversion flags %2X is out of mask (%2X)&bslash;n&quot;
comma
id|info-&gt;invflags
comma
id|EBT_VLAN_MASK
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Reserved VLAN ID (VID) values&n;&t; * -----------------------------&n;&t; * 0 - The null VLAN ID. &n;&t; * 1 - The default Port VID (PVID)&n;&t; * 0x0FFF - Reserved for implementation use. &n;&t; * if_vlan.h: VLAN_GROUP_ARRAY_LEN 4096.&n;&t; */
r_if
c_cond
(paren
id|GET_BITMASK
c_func
(paren
id|EBT_VLAN_ID
)paren
)paren
(brace
multiline_comment|/* when vlan-id param was spec-ed */
r_if
c_cond
(paren
op_logical_neg
op_logical_neg
id|info-&gt;id
)paren
(brace
multiline_comment|/* if id!=0 =&gt; check vid range */
r_if
c_cond
(paren
id|info-&gt;id
OG
id|VLAN_GROUP_ARRAY_LEN
)paren
(brace
id|DEBUG_MSG
(paren
l_string|&quot;id %d is out of range (1-4096)&bslash;n&quot;
comma
id|info-&gt;id
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Note: This is valid VLAN-tagged frame point.&n;&t;&t;&t; * Any value of user_priority are acceptable, &n;&t;&t;&t; * but should be ignored according to 802.1Q Std.&n;&t;&t;&t; * So we just drop the prio flag. &n;&t;&t;&t; */
id|info-&gt;bitmask
op_and_assign
op_complement
id|EBT_VLAN_PRIO
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Else, id=0 (null VLAN ID)  =&gt; user_priority range (any?)&n;&t;&t; */
)brace
r_if
c_cond
(paren
id|GET_BITMASK
c_func
(paren
id|EBT_VLAN_PRIO
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
r_char
)paren
id|info-&gt;prio
OG
l_int|7
)paren
(brace
id|DEBUG_MSG
(paren
l_string|&quot;prio %d is out of range (0-7)&bslash;n&quot;
comma
id|info-&gt;prio
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Check for encapsulated proto range - it is possible to be &n;&t; * any value for u_short range.&n;&t; * if_ether.h:  ETH_ZLEN        60   -  Min. octets in frame sans FCS&n;&t; */
r_if
c_cond
(paren
id|GET_BITMASK
c_func
(paren
id|EBT_VLAN_ENCAP
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|ntohs
c_func
(paren
id|info-&gt;encap
)paren
OL
id|ETH_ZLEN
)paren
(brace
id|DEBUG_MSG
(paren
l_string|&quot;encap frame length %d is less than minimal&bslash;n&quot;
comma
id|ntohs
c_func
(paren
id|info-&gt;encap
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|filter_vlan
r_static
r_struct
id|ebt_match
id|filter_vlan
op_assign
(brace
dot
id|name
op_assign
id|EBT_VLAN_MATCH
comma
dot
id|match
op_assign
id|ebt_filter_vlan
comma
dot
id|check
op_assign
id|ebt_check_vlan
comma
dot
id|me
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Module initialization function.&n; */
DECL|function|init
r_static
r_int
id|__init
id|init
c_func
(paren
r_void
)paren
(brace
id|DEBUG_MSG
c_func
(paren
l_string|&quot;ebtables 802.1Q extension module v&quot;
id|MODULE_VERSION
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|DEBUG_MSG
c_func
(paren
l_string|&quot;module debug=%d&bslash;n&quot;
comma
op_logical_neg
op_logical_neg
id|debug
)paren
suffix:semicolon
r_return
id|ebt_register_match
c_func
(paren
op_amp
id|filter_vlan
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Module &quot;finalization&quot; function&n; */
DECL|function|fini
r_static
r_void
id|__exit
id|fini
c_func
(paren
r_void
)paren
(brace
id|ebt_unregister_match
c_func
(paren
op_amp
id|filter_vlan
)paren
suffix:semicolon
)brace
DECL|variable|init
id|module_init
c_func
(paren
id|init
)paren
suffix:semicolon
DECL|variable|fini
id|module_exit
c_func
(paren
id|fini
)paren
suffix:semicolon
eof
