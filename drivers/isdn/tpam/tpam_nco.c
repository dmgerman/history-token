multiline_comment|/* $Id: tpam_nco.c,v 1.1.2.2 2001/09/23 22:25:03 kai Exp $&n; *&n; * Turbo PAM ISDN driver for Linux. &n; * (Kernel Driver - Low Level NCO Manipulation)&n; *&n; * Copyright 2001 Stelian Pop &lt;stelian.pop@fr.alcove.com&gt;, Alc&#xfffd;ve&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * For all support questions please contact: &lt;support@auvertech.fr&gt;&n; *&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;tpam.h&quot;
multiline_comment|/* Local function prototypes */
r_static
r_struct
id|sk_buff
op_star
id|build_NCOpacket
c_func
(paren
id|u16
comma
id|u16
comma
id|u16
comma
id|u16
comma
id|u16
)paren
suffix:semicolon
r_static
r_int
id|extract_NCOParameter
c_func
(paren
r_struct
id|sk_buff
op_star
comma
id|u8
comma
r_void
op_star
comma
id|u16
)paren
suffix:semicolon
multiline_comment|/*&n; * Build a NCO packet (PCI message).&n; *&n; * &t;messageID: the message type (ID_*)&n; * &t;size: size of the TLV block&n; * &t;data_size: size of the data block&n; * &t;ack: packet needs to send ack upon send&n; * &t;ack_size: size of data to be acknowledged upon send&n; *&n; * Return: the sk_buff filled with the NCO packet, or NULL if error.&n; */
DECL|function|build_NCOpacket
r_static
r_struct
id|sk_buff
op_star
id|build_NCOpacket
c_func
(paren
id|u16
id|messageID
comma
id|u16
id|size
comma
id|u16
id|data_size
comma
id|u16
id|ack
comma
id|u16
id|ack_size
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|skb_header
op_star
id|h
suffix:semicolon
id|pci_mpb
op_star
id|p
suffix:semicolon
id|u16
id|finalsize
suffix:semicolon
multiline_comment|/* reserve enough space for the sk_buff header, the pci * header, &n;&t; * size bytes for the TLV block, size bytes for the data and 4 more&n;&t; * bytes in order to make sure we can write dwords to the board. */
id|finalsize
op_assign
r_sizeof
(paren
id|skb_header
)paren
op_plus
r_sizeof
(paren
id|pci_mpb
)paren
op_plus
id|size
op_plus
id|data_size
op_plus
l_int|4
suffix:semicolon
multiline_comment|/* allocate the sk_buff */
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|finalsize
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM(make_NCOpacket): alloc_skb failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* construct the skb_header */
id|h
op_assign
(paren
id|skb_header
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
r_sizeof
(paren
id|skb_header
)paren
)paren
suffix:semicolon
id|h-&gt;size
op_assign
r_sizeof
(paren
id|pci_mpb
)paren
op_plus
id|size
suffix:semicolon
id|h-&gt;data_size
op_assign
id|data_size
suffix:semicolon
id|h-&gt;ack
op_assign
id|ack
suffix:semicolon
id|h-&gt;ack_size
op_assign
id|ack_size
suffix:semicolon
multiline_comment|/* construct the pci_mpb */
id|p
op_assign
(paren
id|pci_mpb
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
r_sizeof
(paren
id|pci_mpb
)paren
)paren
suffix:semicolon
id|p-&gt;exID
op_assign
l_int|0
suffix:semicolon
id|p-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|p-&gt;errorCode
op_assign
l_int|0
suffix:semicolon
id|p-&gt;messageID
op_assign
id|messageID
suffix:semicolon
id|p-&gt;maximumBlockTLVSize
op_assign
id|MPB_MAXIMUMBLOCKTLVSIZE
suffix:semicolon
id|p-&gt;actualBlockTLVSize
op_assign
id|size
suffix:semicolon
id|p-&gt;maximumDataSize
op_assign
id|MPB_MAXIMUMDATASIZE
suffix:semicolon
id|p-&gt;actualDataSize
op_assign
id|data_size
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
multiline_comment|/*&n; * Build a ACreateNCOReq message.&n; *&n; * &t;phone: the local phone number.&n; *&n; * Return: the sk_buff filled with the NCO packet, or NULL if error.&n; */
DECL|function|build_ACreateNCOReq
r_struct
id|sk_buff
op_star
id|build_ACreateNCOReq
c_func
(paren
r_const
id|u8
op_star
id|phone
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|u8
op_star
id|tlv
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;TurboPAM(build_ACreateNCOReq): phone=%s&bslash;n&quot;
comma
id|phone
)paren
suffix:semicolon
multiline_comment|/* build the NCO packet */
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|build_NCOpacket
c_func
(paren
id|ID_ACreateNCOReq
comma
l_int|23
op_plus
id|strlen
c_func
(paren
id|phone
)paren
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* add the parameters */
id|tlv
op_assign
(paren
id|u8
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|3
)paren
suffix:semicolon
op_star
id|tlv
op_assign
id|PAR_NCOType
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|1
)paren
op_assign
l_int|1
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|2
)paren
op_assign
l_int|5
suffix:semicolon
multiline_comment|/* mistery value... */
id|tlv
op_assign
(paren
id|u8
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|4
)paren
suffix:semicolon
op_star
id|tlv
op_assign
id|PAR_U3Protocol
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|1
)paren
op_assign
l_int|2
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|2
)paren
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* no level 3 protocol */
op_star
(paren
id|tlv
op_plus
l_int|3
)paren
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* HDLC in level 2 */
id|tlv
op_assign
(paren
id|u8
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|3
)paren
suffix:semicolon
op_star
id|tlv
op_assign
id|PAR_Cdirection
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|1
)paren
op_assign
l_int|1
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|2
)paren
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* PCI_DIRECTION_BOTH */
id|tlv
op_assign
(paren
id|u8
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|3
)paren
suffix:semicolon
op_star
id|tlv
op_assign
id|PAR_Udirection
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|1
)paren
op_assign
l_int|1
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|2
)paren
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* PCI_DIRECTION_BOTH */
id|tlv
op_assign
(paren
id|u8
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|4
)paren
suffix:semicolon
op_star
id|tlv
op_assign
id|PAR_BearerCap
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|1
)paren
op_assign
l_int|2
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|2
)paren
op_assign
l_int|0x88
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|3
)paren
op_assign
l_int|0x90
suffix:semicolon
id|tlv
op_assign
(paren
id|u8
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|6
op_plus
id|strlen
c_func
(paren
id|phone
)paren
)paren
suffix:semicolon
op_star
id|tlv
op_assign
id|PAR_CallingNumber
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|1
)paren
op_assign
id|strlen
c_func
(paren
id|phone
)paren
op_plus
l_int|4
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|2
)paren
op_assign
l_int|0x01
suffix:semicolon
multiline_comment|/* international */
op_star
(paren
id|tlv
op_plus
l_int|3
)paren
op_assign
l_int|0x01
suffix:semicolon
multiline_comment|/* isdn */
op_star
(paren
id|tlv
op_plus
l_int|4
)paren
op_assign
l_int|0x00
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|5
)paren
op_assign
l_int|0x00
suffix:semicolon
id|memcpy
c_func
(paren
id|tlv
op_plus
l_int|6
comma
id|phone
comma
id|strlen
c_func
(paren
id|phone
)paren
)paren
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
multiline_comment|/*&n; * Build a ADestroyNCOReq message.&n; *&n; * &t;ncoid: the NCO id.&n; *&n; * Return: the sk_buff filled with the NCO packet, or NULL if error.&n; */
DECL|function|build_ADestroyNCOReq
r_struct
id|sk_buff
op_star
id|build_ADestroyNCOReq
c_func
(paren
id|u32
id|ncoid
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|u8
op_star
id|tlv
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;TurboPAM(build_ADestroyNCOReq): ncoid=%lu&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|ncoid
)paren
suffix:semicolon
multiline_comment|/* build the NCO packet */
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|build_NCOpacket
c_func
(paren
id|ID_ADestroyNCOReq
comma
l_int|6
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* add the parameters */
id|tlv
op_assign
(paren
id|u8
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|6
)paren
suffix:semicolon
op_star
id|tlv
op_assign
id|PAR_NCOID
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|1
)paren
op_assign
l_int|4
suffix:semicolon
op_star
(paren
(paren
id|u32
op_star
)paren
(paren
id|tlv
op_plus
l_int|2
)paren
)paren
op_assign
id|ncoid
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
multiline_comment|/*&n; * Build a CConnectReq message.&n; *&n; * &t;ncoid: the NCO id.&n; * &t;called: the destination phone number&n; * &t;hdlc: type of connection: 1 (HDLC) or 0(modem)&n; *&n; * Return: the sk_buff filled with the NCO packet, or NULL if error.&n; */
DECL|function|build_CConnectReq
r_struct
id|sk_buff
op_star
id|build_CConnectReq
c_func
(paren
id|u32
id|ncoid
comma
r_const
id|u8
op_star
id|called
comma
id|u8
id|hdlc
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|u8
op_star
id|tlv
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;TurboPAM(build_CConnectReq): ncoid=%lu, called=%s, hdlc=%d&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|ncoid
comma
id|called
comma
id|hdlc
)paren
suffix:semicolon
multiline_comment|/* build the NCO packet */
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|build_NCOpacket
c_func
(paren
id|ID_CConnectReq
comma
l_int|20
op_plus
id|strlen
c_func
(paren
id|called
)paren
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* add the parameters */
id|tlv
op_assign
(paren
id|u8
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|6
)paren
suffix:semicolon
op_star
id|tlv
op_assign
id|PAR_NCOID
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|1
)paren
op_assign
l_int|4
suffix:semicolon
op_star
(paren
(paren
id|u32
op_star
)paren
(paren
id|tlv
op_plus
l_int|2
)paren
)paren
op_assign
id|ncoid
suffix:semicolon
id|tlv
op_assign
(paren
id|u8
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|4
op_plus
id|strlen
c_func
(paren
id|called
)paren
)paren
suffix:semicolon
op_star
id|tlv
op_assign
id|PAR_CalledNumber
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|1
)paren
op_assign
id|strlen
c_func
(paren
id|called
)paren
op_plus
l_int|2
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|2
)paren
op_assign
l_int|0x01
suffix:semicolon
multiline_comment|/* international */
op_star
(paren
id|tlv
op_plus
l_int|3
)paren
op_assign
l_int|0x01
suffix:semicolon
multiline_comment|/* isdn */
id|memcpy
c_func
(paren
id|tlv
op_plus
l_int|4
comma
id|called
comma
id|strlen
c_func
(paren
id|called
)paren
)paren
suffix:semicolon
id|tlv
op_assign
(paren
id|u8
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|3
)paren
suffix:semicolon
op_star
id|tlv
op_assign
id|PAR_BearerCap
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|1
)paren
op_assign
l_int|1
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|2
)paren
op_assign
id|hdlc
ques
c_cond
l_int|0x88
multiline_comment|/* HDLC */
suffix:colon
l_int|0x80
multiline_comment|/* MODEM */
suffix:semicolon
id|tlv
op_assign
(paren
id|u8
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|4
)paren
suffix:semicolon
op_star
id|tlv
op_assign
id|PAR_HLC
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|1
)paren
op_assign
l_int|2
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|2
)paren
op_assign
l_int|0x2
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|3
)paren
op_assign
l_int|0x7f
suffix:semicolon
id|tlv
op_assign
(paren
id|u8
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|3
)paren
suffix:semicolon
op_star
id|tlv
op_assign
id|PAR_Facility
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|1
)paren
op_assign
l_int|1
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|2
)paren
op_assign
l_int|2
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
multiline_comment|/*&n; * Build a CConnectRsp message.&n; *&n; * &t;ncoid: the NCO id.&n; *&n; * Return: the sk_buff filled with the NCO packet, or NULL if error.&n; */
DECL|function|build_CConnectRsp
r_struct
id|sk_buff
op_star
id|build_CConnectRsp
c_func
(paren
id|u32
id|ncoid
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|u8
op_star
id|tlv
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;TurboPAM(build_CConnectRsp): ncoid=%lu&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|ncoid
)paren
suffix:semicolon
multiline_comment|/* build the NCO packet */
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|build_NCOpacket
c_func
(paren
id|ID_CConnectRsp
comma
l_int|6
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* add the parameters */
id|tlv
op_assign
(paren
id|u8
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|6
)paren
suffix:semicolon
op_star
id|tlv
op_assign
id|PAR_NCOID
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|1
)paren
op_assign
l_int|4
suffix:semicolon
op_star
(paren
(paren
id|u32
op_star
)paren
(paren
id|tlv
op_plus
l_int|2
)paren
)paren
op_assign
id|ncoid
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
multiline_comment|/*&n; * Build a CDisconnectReq message.&n; *&n; * &t;ncoid: the NCO id.&n; *&n; * Return: the sk_buff filled with the NCO packet, or NULL if error.&n; */
DECL|function|build_CDisconnectReq
r_struct
id|sk_buff
op_star
id|build_CDisconnectReq
c_func
(paren
id|u32
id|ncoid
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|u8
op_star
id|tlv
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;TurboPAM(build_CDisconnectReq): ncoid=%lu&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|ncoid
)paren
suffix:semicolon
multiline_comment|/* build the NCO packet */
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|build_NCOpacket
c_func
(paren
id|ID_CDisconnectReq
comma
l_int|6
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* add the parameters */
id|tlv
op_assign
(paren
id|u8
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|6
)paren
suffix:semicolon
op_star
id|tlv
op_assign
id|PAR_NCOID
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|1
)paren
op_assign
l_int|4
suffix:semicolon
op_star
(paren
(paren
id|u32
op_star
)paren
(paren
id|tlv
op_plus
l_int|2
)paren
)paren
op_assign
id|ncoid
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
multiline_comment|/*&n; * Build a CDisconnectRsp message.&n; *&n; * &t;ncoid: the NCO id.&n; *&n; * Return: the sk_buff filled with the NCO packet, or NULL if error.&n; */
DECL|function|build_CDisconnectRsp
r_struct
id|sk_buff
op_star
id|build_CDisconnectRsp
c_func
(paren
id|u32
id|ncoid
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|u8
op_star
id|tlv
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;TurboPAM(build_CDisconnectRsp): ncoid=%lu&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|ncoid
)paren
suffix:semicolon
multiline_comment|/* build the NCO packet */
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|build_NCOpacket
c_func
(paren
id|ID_CDisconnectRsp
comma
l_int|6
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* add the parameters */
id|tlv
op_assign
(paren
id|u8
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|6
)paren
suffix:semicolon
op_star
id|tlv
op_assign
id|PAR_NCOID
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|1
)paren
op_assign
l_int|4
suffix:semicolon
op_star
(paren
(paren
id|u32
op_star
)paren
(paren
id|tlv
op_plus
l_int|2
)paren
)paren
op_assign
id|ncoid
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
multiline_comment|/*&n; * Build a U3DataReq message.&n; *&n; * &t;ncoid: the NCO id.&n; * &t;data: the data to be send&n; * &t;len: length of the data&n; * &t;ack: send ack upon send&n; * &t;ack_size: size of data to be acknowledged upon send&n; *&n; * Return: the sk_buff filled with the NCO packet, or NULL if error.&n; */
DECL|function|build_U3DataReq
r_struct
id|sk_buff
op_star
id|build_U3DataReq
c_func
(paren
id|u32
id|ncoid
comma
r_void
op_star
id|data
comma
id|u16
id|len
comma
id|u16
id|ack
comma
id|u16
id|ack_size
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|u8
op_star
id|tlv
suffix:semicolon
r_void
op_star
id|p
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;TurboPAM(build_U3DataReq): &quot;
l_string|&quot;ncoid=%lu, len=%d, ack=%d, ack_size=%d&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|ncoid
comma
id|len
comma
id|ack
comma
id|ack_size
)paren
suffix:semicolon
multiline_comment|/* build the NCO packet */
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|build_NCOpacket
c_func
(paren
id|ID_U3DataReq
comma
l_int|6
comma
id|len
comma
id|ack
comma
id|ack_size
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* add the parameters */
id|tlv
op_assign
(paren
id|u8
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
l_int|6
)paren
suffix:semicolon
op_star
id|tlv
op_assign
id|PAR_NCOID
suffix:semicolon
op_star
(paren
id|tlv
op_plus
l_int|1
)paren
op_assign
l_int|4
suffix:semicolon
op_star
(paren
(paren
id|u32
op_star
)paren
(paren
id|tlv
op_plus
l_int|2
)paren
)paren
op_assign
id|ncoid
suffix:semicolon
id|p
op_assign
id|skb_put
c_func
(paren
id|skb
comma
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
id|data
comma
id|len
)paren
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
multiline_comment|/*&n; * Extract a parameter from a TLV block.&n; *&n; * &t;skb: sk_buff containing the PCI message&n; * &t;type: parameter to search for (PARAM_*)&n; * &t;value: to be filled with the value of the parameter&n; * &t;len: maximum length of the parameter value&n; *&n; * Return: 0 if OK, &lt;0 if error.&n; */
DECL|function|extract_NCOParameter
r_static
r_int
id|extract_NCOParameter
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|type
comma
r_void
op_star
id|value
comma
id|u16
id|len
)paren
(brace
r_void
op_star
id|buffer
op_assign
(paren
r_void
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|pci_mpb
op_star
id|p
suffix:semicolon
r_void
op_star
id|bufferend
suffix:semicolon
id|u8
id|valtype
suffix:semicolon
id|u16
id|vallen
suffix:semicolon
multiline_comment|/* calculate the start and end of the TLV block */
id|buffer
op_add_assign
r_sizeof
(paren
id|skb_header
)paren
suffix:semicolon
id|p
op_assign
(paren
id|pci_mpb
op_star
)paren
id|buffer
suffix:semicolon
id|buffer
op_add_assign
r_sizeof
(paren
id|pci_mpb
)paren
suffix:semicolon
id|bufferend
op_assign
id|buffer
op_plus
id|p-&gt;actualBlockTLVSize
suffix:semicolon
multiline_comment|/* walk through the parameters */
r_while
c_loop
(paren
id|buffer
OL
id|bufferend
)paren
(brace
multiline_comment|/* parameter type */
id|valtype
op_assign
op_star
(paren
(paren
id|u8
op_star
)paren
id|buffer
op_increment
)paren
suffix:semicolon
multiline_comment|/* parameter length */
id|vallen
op_assign
op_star
(paren
(paren
id|u8
op_star
)paren
id|buffer
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vallen
op_eq
l_int|0xff
)paren
(brace
multiline_comment|/* parameter length is on 2 bytes */
id|vallen
op_assign
op_star
(paren
(paren
id|u8
op_star
)paren
id|buffer
op_increment
)paren
suffix:semicolon
id|vallen
op_lshift_assign
l_int|8
suffix:semicolon
id|vallen
op_or_assign
op_star
(paren
(paren
id|u8
op_star
)paren
id|buffer
op_increment
)paren
suffix:semicolon
)brace
multiline_comment|/* got the right parameter */
r_if
c_cond
(paren
id|valtype
op_eq
id|type
)paren
(brace
multiline_comment|/* not enough space for returning the value */
r_if
c_cond
(paren
id|vallen
OG
id|len
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* OK, return it */
id|memcpy
c_func
(paren
id|value
comma
id|buffer
comma
id|vallen
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|buffer
op_add_assign
id|vallen
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse a ACreateNCOCnf message.&n; *&n; * &t;skb: the sk_buff containing the message&n; * &t;status: to be filled with the status field value&n; * &t;ncoid: to be filled with the ncoid field value&n; *&n; * Return: 0 if OK, &lt;0 if error.&n; */
DECL|function|parse_ACreateNCOCnf
r_int
id|parse_ACreateNCOCnf
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|status
comma
id|u32
op_star
id|ncoid
)paren
(brace
multiline_comment|/* extract the status */
r_if
c_cond
(paren
id|extract_NCOParameter
c_func
(paren
id|skb
comma
id|PAR_CompletionStatus
comma
id|status
comma
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM(parse_ACreateNCOCnf): &quot;
l_string|&quot;CompletionStatus not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|status
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;TurboPAM(parse_ACreateNCOCnf): status=%d&bslash;n&quot;
comma
op_star
id|status
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* extract the ncoid */
r_if
c_cond
(paren
id|extract_NCOParameter
c_func
(paren
id|skb
comma
id|PAR_NCOID
comma
id|ncoid
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM(parse_ACreateNCOCnf): &quot;
l_string|&quot;NCOID not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;TurboPAM(parse_ACreateNCOCnf): ncoid=%lu, status=%d&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
op_star
id|ncoid
comma
op_star
id|status
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse a ADestroyNCOCnf message. Not used in the driver.&n; *&n; * &t;skb: the sk_buff containing the message&n; * &t;status: to be filled with the status field value&n; * &t;ncoid: to be filled with the ncoid field value&n; *&n; * Return: 0 if OK, &lt;0 if error.&n; */
DECL|function|parse_ADestroyNCOCnf
r_int
id|parse_ADestroyNCOCnf
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|status
comma
id|u32
op_star
id|ncoid
)paren
(brace
multiline_comment|/* extract the status */
r_if
c_cond
(paren
id|extract_NCOParameter
c_func
(paren
id|skb
comma
id|PAR_CompletionStatus
comma
id|status
comma
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM(parse_ADestroyNCOCnf): &quot;
l_string|&quot;CompletionStatus not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|status
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;TurboPAM(parse_ADestroyNCOCnf): status=%d&bslash;n&quot;
comma
op_star
id|status
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* extract the ncoid */
r_if
c_cond
(paren
id|extract_NCOParameter
c_func
(paren
id|skb
comma
id|PAR_NCOID
comma
id|ncoid
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM(parse_ADestroyNCOCnf): &quot;
l_string|&quot;NCOID not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;TurboPAM(parse_ADestroyNCOCnf): ncoid=%lu, status=%d&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
op_star
id|ncoid
comma
op_star
id|status
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse a CConnectCnf message.&n; *&n; * &t;skb: the sk_buff containing the message&n; * &t;ncoid: to be filled with the ncoid field value&n; *&n; * Return: 0 if OK, &lt;0 if error.&n; */
DECL|function|parse_CConnectCnf
r_int
id|parse_CConnectCnf
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u32
op_star
id|ncoid
)paren
(brace
multiline_comment|/* extract the ncoid */
r_if
c_cond
(paren
id|extract_NCOParameter
c_func
(paren
id|skb
comma
id|PAR_NCOID
comma
id|ncoid
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM(parse_CConnectCnf): &quot;
l_string|&quot;NCOID not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;TurboPAM(parse_CConnectCnf): ncoid=%lu&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
op_star
id|ncoid
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse a CConnectInd message.&n; *&n; * &t;skb: the sk_buff containing the message&n; * &t;ncoid: to be filled with the ncoid field value&n; * &t;hdlc: to be filled with 1 if the incoming connection is a HDLC one,&n; * &t;&t;with 0 if the incoming connection is a modem one&n; * &t;calling: to be filled with the calling phone number value&n; * &t;called: to be filled with the called phone number value&n; * &t;plan: to be filled with the plan value&n; * &t;screen: to be filled with the screen value&n; *&n; * Return: 0 if OK, &lt;0 if error.&n; */
DECL|function|parse_CConnectInd
r_int
id|parse_CConnectInd
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u32
op_star
id|ncoid
comma
id|u8
op_star
id|hdlc
comma
id|u8
op_star
id|calling
comma
id|u8
op_star
id|called
comma
id|u8
op_star
id|plan
comma
id|u8
op_star
id|screen
)paren
(brace
id|u8
id|phone
(braket
id|PHONE_MAXIMUMSIZE
op_plus
l_int|4
)braket
suffix:semicolon
multiline_comment|/* extract the ncoid */
r_if
c_cond
(paren
id|extract_NCOParameter
c_func
(paren
id|skb
comma
id|PAR_NCOID
comma
id|ncoid
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM(parse_CConnectInd): &quot;
l_string|&quot;NCOID not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* extract the bearer capability field */
r_if
c_cond
(paren
id|extract_NCOParameter
c_func
(paren
id|skb
comma
id|PAR_BearerCap
comma
id|hdlc
comma
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM(parse_CConnectInd): &quot;
l_string|&quot;BearerCap not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
op_star
id|hdlc
op_assign
(paren
op_star
id|hdlc
op_eq
l_int|0x88
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* extract the calling number / plan / screen */
r_if
c_cond
(paren
id|extract_NCOParameter
c_func
(paren
id|skb
comma
id|PAR_CallingNumber
comma
id|phone
comma
id|PHONE_MAXIMUMSIZE
op_plus
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM(parse_CConnectInd): &quot;
l_string|&quot;CallingNumber not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|calling
comma
id|phone
op_plus
l_int|4
comma
id|PHONE_MAXIMUMSIZE
)paren
suffix:semicolon
op_star
id|plan
op_assign
id|phone
(braket
l_int|1
)braket
suffix:semicolon
op_star
id|screen
op_assign
id|phone
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* extract the called number */
r_if
c_cond
(paren
id|extract_NCOParameter
c_func
(paren
id|skb
comma
id|PAR_CalledNumber
comma
id|phone
comma
id|PHONE_MAXIMUMSIZE
op_plus
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM(parse_CConnectInd): &quot;
l_string|&quot;CalledNumber not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|called
comma
id|phone
op_plus
l_int|2
comma
id|PHONE_MAXIMUMSIZE
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;TurboPAM(parse_CConnectInd): &quot;
l_string|&quot;ncoid=%lu, hdlc=%d, plan=%d, scr=%d, calling=%s, called=%s&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
op_star
id|ncoid
comma
op_star
id|hdlc
comma
op_star
id|plan
comma
op_star
id|screen
comma
id|calling
comma
id|called
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse a CDisconnectCnf message.&n; *&n; * &t;skb: the sk_buff containing the message&n; * &t;ncoid: to be filled with the ncoid field value&n; * &t;causetopuf: to be filled with the cause field value&n; *&n; * Return: 0 if OK, &lt;0 if error.&n; */
DECL|function|parse_CDisconnectCnf
r_int
id|parse_CDisconnectCnf
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u32
op_star
id|ncoid
comma
id|u32
op_star
id|causetopuf
)paren
(brace
multiline_comment|/* extract the ncoid */
r_if
c_cond
(paren
id|extract_NCOParameter
c_func
(paren
id|skb
comma
id|PAR_NCOID
comma
id|ncoid
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM(parse_CDisconnectCnf): &quot;
l_string|&quot;NCOID not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* extract the cause of disconnection */
r_if
c_cond
(paren
id|extract_NCOParameter
c_func
(paren
id|skb
comma
id|PAR_CauseToPUF
comma
id|causetopuf
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM(parse_CDisconnectCnf): &quot;
l_string|&quot;CauseToPUF not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;TurboPAM(parse_CDisconnectCnf): ncoid=%lu, causetopuf=%lu&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
op_star
id|ncoid
comma
(paren
r_int
r_int
)paren
op_star
id|causetopuf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse a CDisconnectInd message.&n; *&n; * &t;skb: the sk_buff containing the message&n; * &t;ncoid: to be filled with the ncoid field value&n; * &t;causetopuf: to be filled with the cause field value&n; *&n; * Return: 0 if OK, &lt;0 if error.&n; */
DECL|function|parse_CDisconnectInd
r_int
id|parse_CDisconnectInd
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u32
op_star
id|ncoid
comma
id|u32
op_star
id|causetopuf
)paren
(brace
multiline_comment|/* extract the ncoid */
r_if
c_cond
(paren
id|extract_NCOParameter
c_func
(paren
id|skb
comma
id|PAR_NCOID
comma
id|ncoid
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM(parse_CDisconnectInd): &quot;
l_string|&quot;NCOID not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* extract the cause of disconnection */
r_if
c_cond
(paren
id|extract_NCOParameter
c_func
(paren
id|skb
comma
id|PAR_CauseToPUF
comma
id|causetopuf
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM(parse_CDisconnectInd): &quot;
l_string|&quot;CauseToPUF not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;TurboPAM(parse_CDisconnectInd): ncoid=%lu, causetopuf=%lu&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
op_star
id|ncoid
comma
(paren
r_int
r_int
)paren
op_star
id|causetopuf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse a U3ReadyToReceiveInd message.&n; *&n; * &t;skb: the sk_buff containing the message&n; * &t;ncoid: to be filled with the ncoid field value&n; * &t;ready: to be filled with the ready field value&n; *&n; * Return: 0 if OK, &lt;0 if error.&n; */
DECL|function|parse_U3ReadyToReceiveInd
r_int
id|parse_U3ReadyToReceiveInd
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u32
op_star
id|ncoid
comma
id|u8
op_star
id|ready
)paren
(brace
multiline_comment|/* extract the ncoid */
r_if
c_cond
(paren
id|extract_NCOParameter
c_func
(paren
id|skb
comma
id|PAR_NCOID
comma
id|ncoid
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM(parse_U3ReadyToReceiveInd): &quot;
l_string|&quot;NCOID not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* extract the ready flag */
r_if
c_cond
(paren
id|extract_NCOParameter
c_func
(paren
id|skb
comma
id|PAR_ReadyFlag
comma
id|ready
comma
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM(parse_U3ReadyToReceiveInd): &quot;
l_string|&quot;ReadyFlag not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;TurboPAM(parse_U3ReadyToReceiveInd): ncoid=%lu, ready=%d&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
op_star
id|ncoid
comma
op_star
id|ready
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse a U3DataInd message.&n; *&n; * &t;skb: the sk_buff containing the message + data&n; * &t;ncoid: to be filled with the ncoid field value&n; * &t;data: to be filled with the data &n; * &t;ready: to be filled with the data length&n; *&n; * Return: 0 if OK, &lt;0 if error.&n; */
DECL|function|parse_U3DataInd
r_int
id|parse_U3DataInd
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u32
op_star
id|ncoid
comma
id|u8
op_star
op_star
id|data
comma
id|u16
op_star
id|len
)paren
(brace
id|pci_mpb
op_star
id|p
suffix:semicolon
multiline_comment|/* extract the ncoid */
r_if
c_cond
(paren
id|extract_NCOParameter
c_func
(paren
id|skb
comma
id|PAR_NCOID
comma
id|ncoid
comma
l_int|4
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TurboPAM(parse_U3DataInd): NCOID not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* get a pointer to the beginning of the data block and its length */
id|p
op_assign
(paren
id|pci_mpb
op_star
)paren
(paren
id|skb-&gt;data
op_plus
r_sizeof
(paren
id|skb_header
)paren
)paren
suffix:semicolon
op_star
id|len
op_assign
id|p-&gt;actualDataSize
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
id|skb_header
)paren
op_plus
r_sizeof
(paren
id|pci_mpb
)paren
op_plus
id|p-&gt;actualBlockTLVSize
)paren
suffix:semicolon
op_star
id|data
op_assign
id|skb-&gt;data
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;TurboPAM(parse_U3DataInd): ncoid=%lu, datalen=%d&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
op_star
id|ncoid
comma
op_star
id|len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
