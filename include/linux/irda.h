multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irda.h&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Mon Mar  8 14:06:12 1999&n; * Modified at:   Sat Dec 25 16:06:42 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef KERNEL_IRDA_H
DECL|macro|KERNEL_IRDA_H
mdefine_line|#define KERNEL_IRDA_H
multiline_comment|/* Hint bit positions for first hint byte */
DECL|macro|HINT_PNP
mdefine_line|#define HINT_PNP         0x01
DECL|macro|HINT_PDA
mdefine_line|#define HINT_PDA         0x02
DECL|macro|HINT_COMPUTER
mdefine_line|#define HINT_COMPUTER    0x04
DECL|macro|HINT_PRINTER
mdefine_line|#define HINT_PRINTER     0x08
DECL|macro|HINT_MODEM
mdefine_line|#define HINT_MODEM       0x10
DECL|macro|HINT_FAX
mdefine_line|#define HINT_FAX         0x20
DECL|macro|HINT_LAN
mdefine_line|#define HINT_LAN         0x40
DECL|macro|HINT_EXTENSION
mdefine_line|#define HINT_EXTENSION   0x80
multiline_comment|/* Hint bit positions for second hint byte (first extension byte) */
DECL|macro|HINT_TELEPHONY
mdefine_line|#define HINT_TELEPHONY   0x01
DECL|macro|HINT_FILE_SERVER
mdefine_line|#define HINT_FILE_SERVER 0x02
DECL|macro|HINT_COMM
mdefine_line|#define HINT_COMM        0x04
DECL|macro|HINT_MESSAGE
mdefine_line|#define HINT_MESSAGE     0x08
DECL|macro|HINT_HTTP
mdefine_line|#define HINT_HTTP        0x10
DECL|macro|HINT_OBEX
mdefine_line|#define HINT_OBEX        0x20
multiline_comment|/* IrLMP character code values */
DECL|macro|CS_ASCII
mdefine_line|#define CS_ASCII         0x00
DECL|macro|CS_ISO_8859_1
mdefine_line|#define&t;CS_ISO_8859_1    0x01
DECL|macro|CS_ISO_8859_2
mdefine_line|#define&t;CS_ISO_8859_2    0x02
DECL|macro|CS_ISO_8859_3
mdefine_line|#define&t;CS_ISO_8859_3    0x03
DECL|macro|CS_ISO_8859_4
mdefine_line|#define&t;CS_ISO_8859_4    0x04
DECL|macro|CS_ISO_8859_5
mdefine_line|#define&t;CS_ISO_8859_5    0x05
DECL|macro|CS_ISO_8859_6
mdefine_line|#define&t;CS_ISO_8859_6    0x06
DECL|macro|CS_ISO_8859_7
mdefine_line|#define&t;CS_ISO_8859_7    0x07
DECL|macro|CS_ISO_8859_8
mdefine_line|#define&t;CS_ISO_8859_8    0x08
DECL|macro|CS_ISO_8859_9
mdefine_line|#define&t;CS_ISO_8859_9    0x09
DECL|macro|CS_UNICODE
mdefine_line|#define CS_UNICODE       0xff
multiline_comment|/* These are the currently known dongles */
r_typedef
r_enum
(brace
DECL|enumerator|IRDA_TEKRAM_DONGLE
id|IRDA_TEKRAM_DONGLE
op_assign
l_int|0
comma
DECL|enumerator|IRDA_ESI_DONGLE
id|IRDA_ESI_DONGLE
op_assign
l_int|1
comma
DECL|enumerator|IRDA_ACTISYS_DONGLE
id|IRDA_ACTISYS_DONGLE
op_assign
l_int|2
comma
DECL|enumerator|IRDA_ACTISYS_PLUS_DONGLE
id|IRDA_ACTISYS_PLUS_DONGLE
op_assign
l_int|3
comma
DECL|enumerator|IRDA_GIRBIL_DONGLE
id|IRDA_GIRBIL_DONGLE
op_assign
l_int|4
comma
DECL|enumerator|IRDA_LITELINK_DONGLE
id|IRDA_LITELINK_DONGLE
op_assign
l_int|5
comma
DECL|enumerator|IRDA_AIRPORT_DONGLE
id|IRDA_AIRPORT_DONGLE
op_assign
l_int|6
comma
DECL|enumerator|IRDA_OLD_BELKIN_DONGLE
id|IRDA_OLD_BELKIN_DONGLE
op_assign
l_int|7
comma
DECL|enumerator|IRDA_EP7211_IR
id|IRDA_EP7211_IR
op_assign
l_int|8
comma
DECL|typedef|IRDA_DONGLE
)brace
id|IRDA_DONGLE
suffix:semicolon
multiline_comment|/* Protocol types to be used for SOCK_DGRAM */
r_enum
(brace
DECL|enumerator|IRDAPROTO_UNITDATA
id|IRDAPROTO_UNITDATA
op_assign
l_int|0
comma
DECL|enumerator|IRDAPROTO_ULTRA
id|IRDAPROTO_ULTRA
op_assign
l_int|1
comma
DECL|enumerator|IRDAPROTO_MAX
id|IRDAPROTO_MAX
)brace
suffix:semicolon
DECL|macro|SOL_IRLMP
mdefine_line|#define SOL_IRLMP      266 /* Same as SOL_IRDA for now */
DECL|macro|SOL_IRTTP
mdefine_line|#define SOL_IRTTP      266 /* Same as SOL_IRDA for now */
DECL|macro|IRLMP_ENUMDEVICES
mdefine_line|#define IRLMP_ENUMDEVICES        1&t;/* Return discovery log */
DECL|macro|IRLMP_IAS_SET
mdefine_line|#define IRLMP_IAS_SET            2&t;/* Set an attribute in local IAS */
DECL|macro|IRLMP_IAS_QUERY
mdefine_line|#define IRLMP_IAS_QUERY          3&t;/* Query remote IAS for attribute */
DECL|macro|IRLMP_HINTS_SET
mdefine_line|#define IRLMP_HINTS_SET          4&t;/* Set hint bits advertised */
DECL|macro|IRLMP_QOS_SET
mdefine_line|#define IRLMP_QOS_SET            5
DECL|macro|IRLMP_QOS_GET
mdefine_line|#define IRLMP_QOS_GET            6
DECL|macro|IRLMP_MAX_SDU_SIZE
mdefine_line|#define IRLMP_MAX_SDU_SIZE       7
DECL|macro|IRLMP_IAS_GET
mdefine_line|#define IRLMP_IAS_GET            8&t;/* Get an attribute from local IAS */
DECL|macro|IRLMP_IAS_DEL
mdefine_line|#define IRLMP_IAS_DEL&t;&t; 9&t;/* Remove attribute from local IAS */
DECL|macro|IRLMP_HINT_MASK_SET
mdefine_line|#define IRLMP_HINT_MASK_SET&t;10&t;/* Set discovery filter */
DECL|macro|IRLMP_WAITDEVICE
mdefine_line|#define IRLMP_WAITDEVICE&t;11&t;/* Wait for a new discovery */
DECL|macro|IRTTP_MAX_SDU_SIZE
mdefine_line|#define IRTTP_MAX_SDU_SIZE IRLMP_MAX_SDU_SIZE /* Compatibility */
DECL|macro|IAS_MAX_STRING
mdefine_line|#define IAS_MAX_STRING         256&t;/* See IrLMP 1.1, 4.3.3.2 */
DECL|macro|IAS_MAX_OCTET_STRING
mdefine_line|#define IAS_MAX_OCTET_STRING  1024&t;/* See IrLMP 1.1, 4.3.3.2 */
DECL|macro|IAS_MAX_CLASSNAME
mdefine_line|#define IAS_MAX_CLASSNAME       60&t;/* See IrLMP 1.1, 4.3.1 */
DECL|macro|IAS_MAX_ATTRIBNAME
mdefine_line|#define IAS_MAX_ATTRIBNAME      60&t;/* See IrLMP 1.1, 4.3.3.1 */
DECL|macro|IAS_MAX_ATTRIBNUMBER
mdefine_line|#define IAS_MAX_ATTRIBNUMBER   256&t;/* See IrLMP 1.1, 4.3.3.1 */
multiline_comment|/* For user space backward compatibility - may be fixed in kernel 2.5.X&n; * Note : need 60+1 (&squot;&bslash;0&squot;), make it 64 for alignement - Jean II */
DECL|macro|IAS_EXPORT_CLASSNAME
mdefine_line|#define IAS_EXPORT_CLASSNAME       64
DECL|macro|IAS_EXPORT_ATTRIBNAME
mdefine_line|#define IAS_EXPORT_ATTRIBNAME     256
multiline_comment|/* Attribute type needed for struct irda_ias_set */
DECL|macro|IAS_MISSING
mdefine_line|#define IAS_MISSING 0
DECL|macro|IAS_INTEGER
mdefine_line|#define IAS_INTEGER 1
DECL|macro|IAS_OCT_SEQ
mdefine_line|#define IAS_OCT_SEQ 2
DECL|macro|IAS_STRING
mdefine_line|#define IAS_STRING  3
DECL|macro|LSAP_ANY
mdefine_line|#define LSAP_ANY              0xff
DECL|struct|sockaddr_irda
r_struct
id|sockaddr_irda
(brace
DECL|member|sir_family
id|sa_family_t
id|sir_family
suffix:semicolon
multiline_comment|/* AF_IRDA */
DECL|member|sir_lsap_sel
id|__u8
id|sir_lsap_sel
suffix:semicolon
multiline_comment|/* LSAP selector */
DECL|member|sir_addr
id|__u32
id|sir_addr
suffix:semicolon
multiline_comment|/* Device address */
DECL|member|sir_name
r_char
id|sir_name
(braket
l_int|25
)braket
suffix:semicolon
multiline_comment|/* Usually &lt;service&gt;:IrDA:TinyTP */
)brace
suffix:semicolon
DECL|struct|irda_device_info
r_struct
id|irda_device_info
(brace
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* Address of local interface */
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* Address of remote device */
DECL|member|info
r_char
id|info
(braket
l_int|22
)braket
suffix:semicolon
multiline_comment|/* Description */
DECL|member|charset
id|__u8
id|charset
suffix:semicolon
multiline_comment|/* Charset used for description */
DECL|member|hints
id|__u8
id|hints
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Hint bits */
)brace
suffix:semicolon
DECL|struct|irda_device_list
r_struct
id|irda_device_list
(brace
DECL|member|len
id|__u32
id|len
suffix:semicolon
DECL|member|dev
r_struct
id|irda_device_info
id|dev
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|irda_ias_set
r_struct
id|irda_ias_set
(brace
DECL|member|irda_class_name
r_char
id|irda_class_name
(braket
id|IAS_EXPORT_CLASSNAME
)braket
suffix:semicolon
DECL|member|irda_attrib_name
r_char
id|irda_attrib_name
(braket
id|IAS_EXPORT_ATTRIBNAME
)braket
suffix:semicolon
DECL|member|irda_attrib_type
r_int
r_int
id|irda_attrib_type
suffix:semicolon
r_union
(brace
DECL|member|irda_attrib_int
r_int
r_int
id|irda_attrib_int
suffix:semicolon
r_struct
(brace
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|octet_seq
id|__u8
id|octet_seq
(braket
id|IAS_MAX_OCTET_STRING
)braket
suffix:semicolon
DECL|member|irda_attrib_octet_seq
)brace
id|irda_attrib_octet_seq
suffix:semicolon
r_struct
(brace
DECL|member|len
id|__u8
id|len
suffix:semicolon
DECL|member|charset
id|__u8
id|charset
suffix:semicolon
DECL|member|string
id|__u8
id|string
(braket
id|IAS_MAX_STRING
)braket
suffix:semicolon
DECL|member|irda_attrib_string
)brace
id|irda_attrib_string
suffix:semicolon
DECL|member|attribute
)brace
id|attribute
suffix:semicolon
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* Address of device (for some queries only) */
)brace
suffix:semicolon
multiline_comment|/* Some private IOCTL&squot;s (max 16) */
DECL|macro|SIOCSDONGLE
mdefine_line|#define SIOCSDONGLE    (SIOCDEVPRIVATE + 0)
DECL|macro|SIOCGDONGLE
mdefine_line|#define SIOCGDONGLE    (SIOCDEVPRIVATE + 1)
DECL|macro|SIOCSBANDWIDTH
mdefine_line|#define SIOCSBANDWIDTH (SIOCDEVPRIVATE + 2)
DECL|macro|SIOCSMEDIABUSY
mdefine_line|#define SIOCSMEDIABUSY (SIOCDEVPRIVATE + 3)
DECL|macro|SIOCGMEDIABUSY
mdefine_line|#define SIOCGMEDIABUSY (SIOCDEVPRIVATE + 4)
DECL|macro|SIOCGRECEIVING
mdefine_line|#define SIOCGRECEIVING (SIOCDEVPRIVATE + 5)
DECL|macro|SIOCSMODE
mdefine_line|#define SIOCSMODE      (SIOCDEVPRIVATE + 6)
DECL|macro|SIOCGMODE
mdefine_line|#define SIOCGMODE      (SIOCDEVPRIVATE + 7)
DECL|macro|SIOCSDTRRTS
mdefine_line|#define SIOCSDTRRTS    (SIOCDEVPRIVATE + 8)
DECL|macro|SIOCGQOS
mdefine_line|#define SIOCGQOS       (SIOCDEVPRIVATE + 9)
multiline_comment|/* No reason to include &lt;linux/if.h&gt; just because of this one ;-) */
DECL|macro|IRNAMSIZ
mdefine_line|#define IRNAMSIZ 16 
multiline_comment|/* IrDA quality of service information (must not exceed 16 bytes) */
DECL|struct|if_irda_qos
r_struct
id|if_irda_qos
(brace
DECL|member|baudrate
r_int
r_int
id|baudrate
suffix:semicolon
DECL|member|data_size
r_int
r_int
id|data_size
suffix:semicolon
DECL|member|window_size
r_int
r_int
id|window_size
suffix:semicolon
DECL|member|min_turn_time
r_int
r_int
id|min_turn_time
suffix:semicolon
DECL|member|max_turn_time
r_int
r_int
id|max_turn_time
suffix:semicolon
DECL|member|add_bofs
r_int
r_char
id|add_bofs
suffix:semicolon
DECL|member|link_disc
r_int
r_char
id|link_disc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* For setting RTS and DTR lines of a dongle */
DECL|struct|if_irda_line
r_struct
id|if_irda_line
(brace
DECL|member|dtr
id|__u8
id|dtr
suffix:semicolon
DECL|member|rts
id|__u8
id|rts
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* IrDA interface configuration (data part must not exceed 16 bytes) */
DECL|struct|if_irda_req
r_struct
id|if_irda_req
(brace
r_union
(brace
DECL|member|ifrn_name
r_char
id|ifrn_name
(braket
id|IRNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* if name, e.g. &quot;irda0&quot; */
DECL|member|ifr_ifrn
)brace
id|ifr_ifrn
suffix:semicolon
multiline_comment|/* Data part */
r_union
(brace
DECL|member|ifru_line
r_struct
id|if_irda_line
id|ifru_line
suffix:semicolon
DECL|member|ifru_qos
r_struct
id|if_irda_qos
id|ifru_qos
suffix:semicolon
DECL|member|ifru_flags
r_int
r_int
id|ifru_flags
suffix:semicolon
DECL|member|ifru_receiving
r_int
r_int
id|ifru_receiving
suffix:semicolon
DECL|member|ifru_mode
r_int
r_int
id|ifru_mode
suffix:semicolon
DECL|member|ifru_dongle
r_int
r_int
id|ifru_dongle
suffix:semicolon
DECL|member|ifr_ifru
)brace
id|ifr_ifru
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ifr_baudrate
mdefine_line|#define ifr_baudrate  ifr_ifru.ifru_qos.baudrate
DECL|macro|ifr_receiving
mdefine_line|#define ifr_receiving ifr_ifru.ifru_receiving 
DECL|macro|ifr_dongle
mdefine_line|#define ifr_dongle    ifr_ifru.ifru_dongle
DECL|macro|ifr_mode
mdefine_line|#define ifr_mode      ifr_ifru.ifru_mode
DECL|macro|ifr_dtr
mdefine_line|#define ifr_dtr       ifr_ifru.ifru_line.dtr
DECL|macro|ifr_rts
mdefine_line|#define ifr_rts       ifr_ifru.ifru_line.rts
macro_line|#endif /* KERNEL_IRDA_H */
eof
