multiline_comment|/*&n; * This code is heavily based on the code in ip_fw.h; see that file for&n; * copyrights and attributions.  This code is basically GPL.&n; *&n; * 15-Feb-1997: Major changes to allow graphs for firewall rules.&n; *              Paul Russell &lt;Paul.Russell@rustcorp.com.au&gt; and&n; *&t;&t;Michael Neuling &lt;Michael.Neuling@rustcorp.com.au&gt;&n; * 2-Nov-1997: Changed types to __u16, etc.&n; *             Removed IP_FW_F_TCPACK &amp; IP_FW_F_BIDIR.&n; *             Added inverse flags field.&n; *             Removed multiple port specs.&n; */
multiline_comment|/*&n; * &t;Format of an IP firewall descriptor&n; *&n; * &t;src, dst, src_mask, dst_mask are always stored in network byte order.&n; * &t;flags are stored in host byte order (of course).&n; * &t;Port numbers are stored in HOST byte order.&n; */
macro_line|#ifndef _IP_FWCHAINS_H
DECL|macro|_IP_FWCHAINS_H
mdefine_line|#define _IP_FWCHAINS_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/icmp.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#endif /* __KERNEL__ */
DECL|macro|IP_FW_MAX_LABEL_LENGTH
mdefine_line|#define IP_FW_MAX_LABEL_LENGTH 8
DECL|typedef|ip_chainlabel
r_typedef
r_char
id|ip_chainlabel
(braket
id|IP_FW_MAX_LABEL_LENGTH
op_plus
l_int|1
)braket
suffix:semicolon
DECL|struct|ip_fw
r_struct
id|ip_fw
(brace
DECL|member|fw_src
DECL|member|fw_dst
r_struct
id|in_addr
id|fw_src
comma
id|fw_dst
suffix:semicolon
multiline_comment|/* Source and destination IP addr */
DECL|member|fw_smsk
DECL|member|fw_dmsk
r_struct
id|in_addr
id|fw_smsk
comma
id|fw_dmsk
suffix:semicolon
multiline_comment|/* Mask for src and dest IP addr */
DECL|member|fw_mark
id|__u32
id|fw_mark
suffix:semicolon
multiline_comment|/* ID to stamp on packet */
DECL|member|fw_proto
id|__u16
id|fw_proto
suffix:semicolon
multiline_comment|/* Protocol, 0 = ANY */
DECL|member|fw_flg
id|__u16
id|fw_flg
suffix:semicolon
multiline_comment|/* Flags word */
DECL|member|fw_invflg
id|__u16
id|fw_invflg
suffix:semicolon
multiline_comment|/* Inverse flags */
DECL|member|fw_spts
id|__u16
id|fw_spts
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Source port range. */
DECL|member|fw_dpts
id|__u16
id|fw_dpts
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Destination port range. */
DECL|member|fw_redirpt
id|__u16
id|fw_redirpt
suffix:semicolon
multiline_comment|/* Port to redirect to. */
DECL|member|fw_outputsize
id|__u16
id|fw_outputsize
suffix:semicolon
multiline_comment|/* Max amount to output to&n;&t;&t;&t;&t;&t;&t;   NETLINK */
DECL|member|fw_vianame
r_char
id|fw_vianame
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* name of interface &quot;via&quot; */
DECL|member|fw_tosand
DECL|member|fw_tosxor
id|__u8
id|fw_tosand
comma
id|fw_tosxor
suffix:semicolon
multiline_comment|/* Revised packet priority */
)brace
suffix:semicolon
DECL|struct|ip_fwuser
r_struct
id|ip_fwuser
(brace
DECL|member|ipfw
r_struct
id|ip_fw
id|ipfw
suffix:semicolon
DECL|member|label
id|ip_chainlabel
id|label
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Values for &quot;fw_flg&quot; field .  */
DECL|macro|IP_FW_F_PRN
mdefine_line|#define IP_FW_F_PRN&t;0x0001&t;/* Print packet if it matches */
DECL|macro|IP_FW_F_TCPSYN
mdefine_line|#define IP_FW_F_TCPSYN&t;0x0002&t;/* For tcp packets-check SYN only */
DECL|macro|IP_FW_F_FRAG
mdefine_line|#define IP_FW_F_FRAG&t;0x0004  /* Set if rule is a fragment rule */
DECL|macro|IP_FW_F_MARKABS
mdefine_line|#define IP_FW_F_MARKABS&t;0x0008  /* Set the mark to fw_mark, not add. */
DECL|macro|IP_FW_F_WILDIF
mdefine_line|#define IP_FW_F_WILDIF&t;0x0010  /* Need only match start of interface name. */
DECL|macro|IP_FW_F_NETLINK
mdefine_line|#define IP_FW_F_NETLINK 0x0020  /* Redirect to netlink: 2.1.x only */
DECL|macro|IP_FW_F_MASK
mdefine_line|#define IP_FW_F_MASK&t;0x003F&t;/* All possible flag bits mask   */
multiline_comment|/* Values for &quot;fw_invflg&quot; field. */
DECL|macro|IP_FW_INV_SRCIP
mdefine_line|#define IP_FW_INV_SRCIP 0x0001  /* Invert the sense of fw_src. */
DECL|macro|IP_FW_INV_DSTIP
mdefine_line|#define IP_FW_INV_DSTIP 0x0002  /* Invert the sense of fw_dst. */
DECL|macro|IP_FW_INV_PROTO
mdefine_line|#define IP_FW_INV_PROTO 0x0004  /* Invert the sense of fw_proto. */
DECL|macro|IP_FW_INV_SRCPT
mdefine_line|#define IP_FW_INV_SRCPT 0x0008  /* Invert the sense of source ports. */
DECL|macro|IP_FW_INV_DSTPT
mdefine_line|#define IP_FW_INV_DSTPT 0x0010  /* Invert the sense of destination ports. */
DECL|macro|IP_FW_INV_VIA
mdefine_line|#define IP_FW_INV_VIA   0x0020  /* Invert the sense of fw_vianame. */
DECL|macro|IP_FW_INV_SYN
mdefine_line|#define IP_FW_INV_SYN   0x0040  /* Invert the sense of IP_FW_F_TCPSYN. */
DECL|macro|IP_FW_INV_FRAG
mdefine_line|#define IP_FW_INV_FRAG  0x0080  /* Invert the sense of IP_FW_F_FRAG. */
multiline_comment|/*&n; *&t;New IP firewall options for [gs]etsockopt at the RAW IP level.&n; *&t;Unlike BSD Linux inherits IP options so you don&squot;t have to use&n; * a raw socket for this. Instead we check rights in the calls.  */
DECL|macro|IP_FW_BASE_CTL
mdefine_line|#define IP_FW_BASE_CTL  &t;64&t;/* base for firewall socket options */
DECL|macro|IP_FW_APPEND
mdefine_line|#define IP_FW_APPEND&t;&t;(IP_FW_BASE_CTL)    /* Takes ip_fwchange */
DECL|macro|IP_FW_REPLACE
mdefine_line|#define IP_FW_REPLACE&t;&t;(IP_FW_BASE_CTL+1)  /* Takes ip_fwnew */
DECL|macro|IP_FW_DELETE_NUM
mdefine_line|#define IP_FW_DELETE_NUM&t;(IP_FW_BASE_CTL+2)  /* Takes ip_fwdelnum */
DECL|macro|IP_FW_DELETE
mdefine_line|#define IP_FW_DELETE&t;&t;(IP_FW_BASE_CTL+3)  /* Takes ip_fwchange */
DECL|macro|IP_FW_INSERT
mdefine_line|#define IP_FW_INSERT&t;&t;(IP_FW_BASE_CTL+4)  /* Takes ip_fwnew */
DECL|macro|IP_FW_FLUSH
mdefine_line|#define IP_FW_FLUSH&t;&t;(IP_FW_BASE_CTL+5)  /* Takes ip_chainlabel */
DECL|macro|IP_FW_ZERO
mdefine_line|#define IP_FW_ZERO&t;&t;(IP_FW_BASE_CTL+6)  /* Takes ip_chainlabel */
DECL|macro|IP_FW_CHECK
mdefine_line|#define IP_FW_CHECK&t;&t;(IP_FW_BASE_CTL+7)  /* Takes ip_fwtest */
DECL|macro|IP_FW_MASQ_TIMEOUTS
mdefine_line|#define IP_FW_MASQ_TIMEOUTS&t;(IP_FW_BASE_CTL+8)  /* Takes 3 ints */
DECL|macro|IP_FW_CREATECHAIN
mdefine_line|#define IP_FW_CREATECHAIN&t;(IP_FW_BASE_CTL+9)  /* Takes ip_chainlabel */
DECL|macro|IP_FW_DELETECHAIN
mdefine_line|#define IP_FW_DELETECHAIN&t;(IP_FW_BASE_CTL+10) /* Takes ip_chainlabel */
DECL|macro|IP_FW_POLICY
mdefine_line|#define IP_FW_POLICY&t;&t;(IP_FW_BASE_CTL+11) /* Takes ip_fwpolicy */
multiline_comment|/* Masquerade control, only 1 optname */
DECL|macro|IP_FW_MASQ_CTL
mdefine_line|#define IP_FW_MASQ_CTL  &t;(IP_FW_BASE_CTL+12) /* General ip_masq ctl */
multiline_comment|/* Builtin chain labels */
DECL|macro|IP_FW_LABEL_FORWARD
mdefine_line|#define IP_FW_LABEL_FORWARD&t;&quot;forward&quot;
DECL|macro|IP_FW_LABEL_INPUT
mdefine_line|#define IP_FW_LABEL_INPUT&t;&quot;input&quot;
DECL|macro|IP_FW_LABEL_OUTPUT
mdefine_line|#define IP_FW_LABEL_OUTPUT&t;&quot;output&quot;
multiline_comment|/* Special targets */
DECL|macro|IP_FW_LABEL_MASQUERADE
mdefine_line|#define IP_FW_LABEL_MASQUERADE  &quot;MASQ&quot;
DECL|macro|IP_FW_LABEL_REDIRECT
mdefine_line|#define IP_FW_LABEL_REDIRECT    &quot;REDIRECT&quot;
DECL|macro|IP_FW_LABEL_ACCEPT
mdefine_line|#define IP_FW_LABEL_ACCEPT&t;&quot;ACCEPT&quot;
DECL|macro|IP_FW_LABEL_BLOCK
mdefine_line|#define IP_FW_LABEL_BLOCK&t;&quot;DENY&quot;
DECL|macro|IP_FW_LABEL_REJECT
mdefine_line|#define IP_FW_LABEL_REJECT&t;&quot;REJECT&quot;
DECL|macro|IP_FW_LABEL_RETURN
mdefine_line|#define IP_FW_LABEL_RETURN&t;&quot;RETURN&quot;
DECL|macro|IP_FW_LABEL_QUEUE
mdefine_line|#define IP_FW_LABEL_QUEUE       &quot;QUEUE&quot;
multiline_comment|/* Files in /proc/net */
DECL|macro|IP_FW_PROC_CHAINS
mdefine_line|#define IP_FW_PROC_CHAINS&t;&quot;ip_fwchains&quot;
DECL|macro|IP_FW_PROC_CHAIN_NAMES
mdefine_line|#define IP_FW_PROC_CHAIN_NAMES&t;&quot;ip_fwnames&quot;
DECL|struct|ip_fwpkt
r_struct
id|ip_fwpkt
(brace
DECL|member|fwp_iph
r_struct
id|iphdr
id|fwp_iph
suffix:semicolon
multiline_comment|/* IP header */
r_union
(brace
DECL|member|fwp_tcph
r_struct
id|tcphdr
id|fwp_tcph
suffix:semicolon
multiline_comment|/* TCP header or */
DECL|member|fwp_udph
r_struct
id|udphdr
id|fwp_udph
suffix:semicolon
multiline_comment|/* UDP header */
DECL|member|fwp_icmph
r_struct
id|icmphdr
id|fwp_icmph
suffix:semicolon
multiline_comment|/* ICMP header */
DECL|member|fwp_protoh
)brace
id|fwp_protoh
suffix:semicolon
DECL|member|fwp_via
r_struct
id|in_addr
id|fwp_via
suffix:semicolon
multiline_comment|/* interface address */
DECL|member|fwp_vianame
r_char
id|fwp_vianame
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* interface name */
)brace
suffix:semicolon
multiline_comment|/* The argument to IP_FW_DELETE and IP_FW_APPEND */
DECL|struct|ip_fwchange
r_struct
id|ip_fwchange
(brace
DECL|member|fwc_rule
r_struct
id|ip_fwuser
id|fwc_rule
suffix:semicolon
DECL|member|fwc_label
id|ip_chainlabel
id|fwc_label
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The argument to IP_FW_CHECK. */
DECL|struct|ip_fwtest
r_struct
id|ip_fwtest
(brace
DECL|member|fwt_packet
r_struct
id|ip_fwpkt
id|fwt_packet
suffix:semicolon
multiline_comment|/* Packet to be tested */
DECL|member|fwt_label
id|ip_chainlabel
id|fwt_label
suffix:semicolon
multiline_comment|/* Block to start test in */
)brace
suffix:semicolon
multiline_comment|/* The argument to IP_FW_DELETE_NUM */
DECL|struct|ip_fwdelnum
r_struct
id|ip_fwdelnum
(brace
DECL|member|fwd_rulenum
id|__u32
id|fwd_rulenum
suffix:semicolon
DECL|member|fwd_label
id|ip_chainlabel
id|fwd_label
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The argument to IP_FW_REPLACE and IP_FW_INSERT */
DECL|struct|ip_fwnew
r_struct
id|ip_fwnew
(brace
DECL|member|fwn_rulenum
id|__u32
id|fwn_rulenum
suffix:semicolon
DECL|member|fwn_rule
r_struct
id|ip_fwuser
id|fwn_rule
suffix:semicolon
DECL|member|fwn_label
id|ip_chainlabel
id|fwn_label
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The argument to IP_FW_POLICY */
DECL|struct|ip_fwpolicy
r_struct
id|ip_fwpolicy
(brace
DECL|member|fwp_policy
id|ip_chainlabel
id|fwp_policy
suffix:semicolon
DECL|member|fwp_label
id|ip_chainlabel
id|fwp_label
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * timeouts for ip masquerading&n; */
r_extern
r_int
id|ip_fw_masq_timeouts
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Main firewall chains definitions and global var&squot;s definitions.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,1,0)
macro_line|#include &lt;linux/init.h&gt;
r_extern
r_void
id|ip_fw_init
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
macro_line|#else /* 2.0.x */
r_extern
r_void
id|ip_fw_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* 2.1.x */
r_extern
r_int
id|ip_fw_ctl
c_func
(paren
r_int
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IP_MASQUERADE
r_extern
r_int
id|ip_masq_uctl
c_func
(paren
r_int
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* KERNEL */
macro_line|#endif /* _IP_FWCHAINS_H */
eof
