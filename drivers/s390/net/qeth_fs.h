multiline_comment|/*&n; * linux/drivers/s390/net/qeth_fs.h&n; *&n; * Linux on zSeries OSA Express and HiperSockets support.&n; *&n; * This header file contains definitions related to sysfs and procfs.&n; *&n; * Copyright 2000,2003 IBM Corporation&n; * Author(s): Thomas Spatzier &lt;tspat@de.ibm.com&gt;&n; *&n; */
macro_line|#ifndef __QETH_FS_H__
DECL|macro|__QETH_FS_H__
mdefine_line|#define __QETH_FS_H__
DECL|macro|VERSION_QETH_FS_H
mdefine_line|#define VERSION_QETH_FS_H &quot;$Revision: 1.9 $&quot;
r_extern
r_const
r_char
op_star
id|VERSION_QETH_PROC_C
suffix:semicolon
r_extern
r_const
r_char
op_star
id|VERSION_QETH_SYS_C
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
r_extern
r_int
id|qeth_create_procfs_entries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|qeth_remove_procfs_entries
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
r_static
r_inline
r_int
DECL|function|qeth_create_procfs_entries
id|qeth_create_procfs_entries
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|qeth_remove_procfs_entries
id|qeth_remove_procfs_entries
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* CONFIG_PROC_FS */
r_extern
r_int
id|qeth_create_device_attributes
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|qeth_remove_device_attributes
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|qeth_create_driver_attributes
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|qeth_remove_driver_attributes
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * utility functions used in qeth_proc.c and qeth_sys.c&n; */
r_static
r_inline
r_const
r_char
op_star
DECL|function|qeth_get_checksum_str
id|qeth_get_checksum_str
c_func
(paren
r_struct
id|qeth_card
op_star
id|card
)paren
(brace
r_if
c_cond
(paren
id|card-&gt;options.checksum_type
op_eq
id|SW_CHECKSUMMING
)paren
r_return
l_string|&quot;sw&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|card-&gt;options.checksum_type
op_eq
id|HW_CHECKSUMMING
)paren
r_return
l_string|&quot;hw&quot;
suffix:semicolon
r_else
r_return
l_string|&quot;no&quot;
suffix:semicolon
)brace
r_static
r_inline
r_const
r_char
op_star
DECL|function|qeth_get_prioq_str
id|qeth_get_prioq_str
c_func
(paren
r_struct
id|qeth_card
op_star
id|card
comma
r_char
op_star
id|buf
)paren
(brace
r_if
c_cond
(paren
id|card-&gt;qdio.do_prio_queueing
op_eq
id|QETH_NO_PRIO_QUEUEING
)paren
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;always_q_%i&quot;
comma
id|card-&gt;qdio.default_out_queue
)paren
suffix:semicolon
r_else
id|strcpy
c_func
(paren
id|buf
comma
(paren
id|card-&gt;qdio.do_prio_queueing
op_eq
id|QETH_PRIO_Q_ING_PREC
)paren
ques
c_cond
l_string|&quot;by_prec.&quot;
suffix:colon
l_string|&quot;by_ToS&quot;
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
r_static
r_inline
r_const
r_char
op_star
DECL|function|qeth_get_bufsize_str
id|qeth_get_bufsize_str
c_func
(paren
r_struct
id|qeth_card
op_star
id|card
)paren
(brace
r_if
c_cond
(paren
id|card-&gt;qdio.in_buf_size
op_eq
l_int|16384
)paren
r_return
l_string|&quot;16k&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|card-&gt;qdio.in_buf_size
op_eq
l_int|24576
)paren
r_return
l_string|&quot;24k&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|card-&gt;qdio.in_buf_size
op_eq
l_int|32768
)paren
r_return
l_string|&quot;32k&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|card-&gt;qdio.in_buf_size
op_eq
l_int|40960
)paren
r_return
l_string|&quot;40k&quot;
suffix:semicolon
r_else
r_return
l_string|&quot;64k&quot;
suffix:semicolon
)brace
r_static
r_inline
r_const
r_char
op_star
DECL|function|qeth_get_cardname
id|qeth_get_cardname
c_func
(paren
r_struct
id|qeth_card
op_star
id|card
)paren
(brace
r_if
c_cond
(paren
id|card-&gt;info.guestlan
)paren
(brace
r_switch
c_cond
(paren
id|card-&gt;info.type
)paren
(brace
r_case
id|QETH_CARD_TYPE_OSAE
suffix:colon
r_return
l_string|&quot; Guest LAN QDIO&quot;
suffix:semicolon
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
l_string|&quot; Guest LAN Hiper&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot; unknown&quot;
suffix:semicolon
)brace
)brace
r_else
(brace
r_switch
c_cond
(paren
id|card-&gt;info.type
)paren
(brace
r_case
id|QETH_CARD_TYPE_OSAE
suffix:colon
r_return
l_string|&quot; OSD Express&quot;
suffix:semicolon
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
l_string|&quot; HiperSockets&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot; unknown&quot;
suffix:semicolon
)brace
)brace
r_return
l_string|&quot; n/a&quot;
suffix:semicolon
)brace
multiline_comment|/* max length to be returned: 14 */
r_static
r_inline
r_const
r_char
op_star
DECL|function|qeth_get_cardname_short
id|qeth_get_cardname_short
c_func
(paren
r_struct
id|qeth_card
op_star
id|card
)paren
(brace
r_if
c_cond
(paren
id|card-&gt;info.guestlan
)paren
(brace
r_switch
c_cond
(paren
id|card-&gt;info.type
)paren
(brace
r_case
id|QETH_CARD_TYPE_OSAE
suffix:colon
r_return
l_string|&quot;GuestLAN QDIO&quot;
suffix:semicolon
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
l_string|&quot;GuestLAN Hiper&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;unknown&quot;
suffix:semicolon
)brace
)brace
r_else
(brace
r_switch
c_cond
(paren
id|card-&gt;info.type
)paren
(brace
r_case
id|QETH_CARD_TYPE_OSAE
suffix:colon
r_switch
c_cond
(paren
id|card-&gt;info.link_type
)paren
(brace
r_case
id|QETH_LINK_TYPE_FAST_ETH
suffix:colon
r_return
l_string|&quot;OSD_100&quot;
suffix:semicolon
r_case
id|QETH_LINK_TYPE_HSTR
suffix:colon
r_return
l_string|&quot;HSTR&quot;
suffix:semicolon
r_case
id|QETH_LINK_TYPE_GBIT_ETH
suffix:colon
r_return
l_string|&quot;OSD_1000&quot;
suffix:semicolon
r_case
id|QETH_LINK_TYPE_10GBIT_ETH
suffix:colon
r_return
l_string|&quot;OSD_10GIG&quot;
suffix:semicolon
r_case
id|QETH_LINK_TYPE_LANE_ETH100
suffix:colon
r_return
l_string|&quot;OSD_FE_LANE&quot;
suffix:semicolon
r_case
id|QETH_LINK_TYPE_LANE_TR
suffix:colon
r_return
l_string|&quot;OSD_TR_LANE&quot;
suffix:semicolon
r_case
id|QETH_LINK_TYPE_LANE_ETH1000
suffix:colon
r_return
l_string|&quot;OSD_GbE_LANE&quot;
suffix:semicolon
r_case
id|QETH_LINK_TYPE_LANE
suffix:colon
r_return
l_string|&quot;OSD_ATM_LANE&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;OSD_Express&quot;
suffix:semicolon
)brace
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
l_string|&quot;HiperSockets&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;unknown&quot;
suffix:semicolon
)brace
)brace
r_return
l_string|&quot;n/a&quot;
suffix:semicolon
)brace
macro_line|#endif /* __QETH_FS_H__ */
eof
