multiline_comment|/*&n; *&t;Copyright (c) 2004, 2005 Jeroen Vreeken (pe1rxq@amsat.org)&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;version 2 as published by the Free Software Foundation.&n; *&n; *&t;Parts of this driver have been derived from a wlan-ng version&n; *&t;modified by ZyDAS.&n; *&t;Copyright (C) 1999 AbsoluteValue Systems, Inc.  All Rights Reserved.&n; */
macro_line|#ifndef _INCLUDE_ZD1201_H_
DECL|macro|_INCLUDE_ZD1201_H_
mdefine_line|#define _INCLUDE_ZD1201_H_
DECL|macro|ZD1201_NUMKEYS
mdefine_line|#define ZD1201_NUMKEYS&t;&t;4
DECL|macro|ZD1201_MAXKEYLEN
mdefine_line|#define ZD1201_MAXKEYLEN&t;13
DECL|macro|ZD1201_MAXMULTI
mdefine_line|#define ZD1201_MAXMULTI&t;&t;16
DECL|macro|ZD1201_FRAGMAX
mdefine_line|#define ZD1201_FRAGMAX&t;&t;2500
DECL|macro|ZD1201_FRAGMIN
mdefine_line|#define ZD1201_FRAGMIN&t;&t;256
DECL|macro|ZD1201_RTSMAX
mdefine_line|#define ZD1201_RTSMAX&t;&t;2500
DECL|macro|ZD1201_RXSIZE
mdefine_line|#define ZD1201_RXSIZE&t;&t;3000
DECL|struct|zd1201
r_struct
id|zd1201
(brace
DECL|member|usb
r_struct
id|usb_device
op_star
id|usb
suffix:semicolon
DECL|member|removed
r_int
id|removed
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|iwstats
r_struct
id|iw_statistics
id|iwstats
suffix:semicolon
DECL|member|endp_in
r_int
id|endp_in
suffix:semicolon
DECL|member|endp_out
r_int
id|endp_out
suffix:semicolon
DECL|member|endp_out2
r_int
id|endp_out2
suffix:semicolon
DECL|member|rx_urb
r_struct
id|urb
op_star
id|rx_urb
suffix:semicolon
DECL|member|tx_urb
r_struct
id|urb
op_star
id|tx_urb
suffix:semicolon
DECL|member|rxdata
r_int
r_char
id|rxdata
(braket
id|ZD1201_RXSIZE
)braket
suffix:semicolon
DECL|member|rxlen
r_int
id|rxlen
suffix:semicolon
DECL|member|rxdataq
id|wait_queue_head_t
id|rxdataq
suffix:semicolon
DECL|member|rxdatas
r_int
id|rxdatas
suffix:semicolon
DECL|member|fraglist
r_struct
id|hlist_head
id|fraglist
suffix:semicolon
DECL|member|txdata
r_int
r_char
id|txdata
(braket
id|ZD1201_RXSIZE
)braket
suffix:semicolon
DECL|member|ap
r_int
id|ap
suffix:semicolon
DECL|member|essid
r_char
id|essid
(braket
id|IW_ESSID_MAX_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|essidlen
r_int
id|essidlen
suffix:semicolon
DECL|member|mac_enabled
r_int
id|mac_enabled
suffix:semicolon
DECL|member|monitor
r_int
id|monitor
suffix:semicolon
DECL|member|encode_enabled
r_int
id|encode_enabled
suffix:semicolon
DECL|member|encode_restricted
r_int
id|encode_restricted
suffix:semicolon
DECL|member|encode_keys
r_int
r_char
id|encode_keys
(braket
id|ZD1201_NUMKEYS
)braket
(braket
id|ZD1201_MAXKEYLEN
)braket
suffix:semicolon
DECL|member|encode_keylen
r_int
id|encode_keylen
(braket
id|ZD1201_NUMKEYS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|zd1201_frag
r_struct
id|zd1201_frag
(brace
DECL|member|fnode
r_struct
id|hlist_node
id|fnode
suffix:semicolon
DECL|member|seq
r_int
id|seq
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ZD1201SIWHOSTAUTH
mdefine_line|#define ZD1201SIWHOSTAUTH SIOCIWFIRSTPRIV
DECL|macro|ZD1201GIWHOSTAUTH
mdefine_line|#define ZD1201GIWHOSTAUTH ZD1201SIWHOSTAUTH+1
DECL|macro|ZD1201SIWAUTHSTA
mdefine_line|#define ZD1201SIWAUTHSTA SIOCIWFIRSTPRIV+2
DECL|macro|ZD1201SIWMAXASSOC
mdefine_line|#define ZD1201SIWMAXASSOC SIOCIWFIRSTPRIV+4
DECL|macro|ZD1201GIWMAXASSOC
mdefine_line|#define ZD1201GIWMAXASSOC ZD1201SIWMAXASSOC+1
DECL|macro|ZD1201_FW_TIMEOUT
mdefine_line|#define ZD1201_FW_TIMEOUT&t;(1*HZ)
DECL|macro|ZD1201_TX_TIMEOUT
mdefine_line|#define ZD1201_TX_TIMEOUT&t;(2*HZ)
DECL|macro|ZD1201_USB_CMDREQ
mdefine_line|#define ZD1201_USB_CMDREQ&t;0
DECL|macro|ZD1201_USB_RESREQ
mdefine_line|#define ZD1201_USB_RESREQ&t;1
DECL|macro|ZD1201_CMDCODE_INIT
mdefine_line|#define&t;ZD1201_CMDCODE_INIT&t;0x00
DECL|macro|ZD1201_CMDCODE_ENABLE
mdefine_line|#define ZD1201_CMDCODE_ENABLE&t;0x01
DECL|macro|ZD1201_CMDCODE_DISABLE
mdefine_line|#define ZD1201_CMDCODE_DISABLE&t;0x02
DECL|macro|ZD1201_CMDCODE_ALLOC
mdefine_line|#define ZD1201_CMDCODE_ALLOC&t;0x0a
DECL|macro|ZD1201_CMDCODE_INQUIRE
mdefine_line|#define ZD1201_CMDCODE_INQUIRE&t;0x11
DECL|macro|ZD1201_CMDCODE_SETRXRID
mdefine_line|#define ZD1201_CMDCODE_SETRXRID&t;0x17
DECL|macro|ZD1201_CMDCODE_ACCESS
mdefine_line|#define ZD1201_CMDCODE_ACCESS&t;0x21
DECL|macro|ZD1201_PACKET_EVENTSTAT
mdefine_line|#define ZD1201_PACKET_EVENTSTAT&t;0x0
DECL|macro|ZD1201_PACKET_RXDATA
mdefine_line|#define ZD1201_PACKET_RXDATA&t;0x1
DECL|macro|ZD1201_PACKET_INQUIRE
mdefine_line|#define ZD1201_PACKET_INQUIRE&t;0x2
DECL|macro|ZD1201_PACKET_RESOURCE
mdefine_line|#define ZD1201_PACKET_RESOURCE&t;0x3
DECL|macro|ZD1201_ACCESSBIT
mdefine_line|#define ZD1201_ACCESSBIT&t;0x0100
DECL|macro|ZD1201_RID_CNFPORTTYPE
mdefine_line|#define ZD1201_RID_CNFPORTTYPE&t;&t;0xfc00
DECL|macro|ZD1201_RID_CNFOWNMACADDR
mdefine_line|#define ZD1201_RID_CNFOWNMACADDR&t;0xfc01
DECL|macro|ZD1201_RID_CNFDESIREDSSID
mdefine_line|#define ZD1201_RID_CNFDESIREDSSID&t;0xfc02
DECL|macro|ZD1201_RID_CNFOWNCHANNEL
mdefine_line|#define ZD1201_RID_CNFOWNCHANNEL&t;0xfc03
DECL|macro|ZD1201_RID_CNFOWNSSID
mdefine_line|#define ZD1201_RID_CNFOWNSSID&t;&t;0xfc04
DECL|macro|ZD1201_RID_CNFMAXDATALEN
mdefine_line|#define ZD1201_RID_CNFMAXDATALEN&t;0xfc07
DECL|macro|ZD1201_RID_CNFPMENABLED
mdefine_line|#define ZD1201_RID_CNFPMENABLED&t;&t;0xfc09
DECL|macro|ZD1201_RID_CNFPMEPS
mdefine_line|#define ZD1201_RID_CNFPMEPS&t;&t;0xfc0a
DECL|macro|ZD1201_RID_CNFMAXSLEEPDURATION
mdefine_line|#define ZD1201_RID_CNFMAXSLEEPDURATION&t;0xfc0c
DECL|macro|ZD1201_RID_CNFDEFAULTKEYID
mdefine_line|#define ZD1201_RID_CNFDEFAULTKEYID&t;0xfc23
DECL|macro|ZD1201_RID_CNFDEFAULTKEY0
mdefine_line|#define ZD1201_RID_CNFDEFAULTKEY0&t;0xfc24
DECL|macro|ZD1201_RID_CNFDEFAULTKEY1
mdefine_line|#define ZD1201_RID_CNFDEFAULTKEY1&t;0xfc25
DECL|macro|ZD1201_RID_CNFDEFAULTKEY2
mdefine_line|#define ZD1201_RID_CNFDEFAULTKEY2&t;0xfc26
DECL|macro|ZD1201_RID_CNFDEFAULTKEY3
mdefine_line|#define ZD1201_RID_CNFDEFAULTKEY3&t;0xfc27
DECL|macro|ZD1201_RID_CNFWEBFLAGS
mdefine_line|#define ZD1201_RID_CNFWEBFLAGS&t;&t;0xfc28
DECL|macro|ZD1201_RID_CNFAUTHENTICATION
mdefine_line|#define ZD1201_RID_CNFAUTHENTICATION&t;0xfc2a
DECL|macro|ZD1201_RID_CNFMAXASSOCSTATIONS
mdefine_line|#define ZD1201_RID_CNFMAXASSOCSTATIONS&t;0xfc2b
DECL|macro|ZD1201_RID_CNFHOSTAUTH
mdefine_line|#define ZD1201_RID_CNFHOSTAUTH&t;&t;0xfc2e
DECL|macro|ZD1201_RID_CNFGROUPADDRESS
mdefine_line|#define ZD1201_RID_CNFGROUPADDRESS&t;0xfc80
DECL|macro|ZD1201_RID_CNFFRAGTHRESHOLD
mdefine_line|#define ZD1201_RID_CNFFRAGTHRESHOLD&t;0xfc82
DECL|macro|ZD1201_RID_CNFRTSTHRESHOLD
mdefine_line|#define ZD1201_RID_CNFRTSTHRESHOLD&t;0xfc83
DECL|macro|ZD1201_RID_TXRATECNTL
mdefine_line|#define ZD1201_RID_TXRATECNTL&t;&t;0xfc84
DECL|macro|ZD1201_RID_PROMISCUOUSMODE
mdefine_line|#define ZD1201_RID_PROMISCUOUSMODE&t;0xfc85
DECL|macro|ZD1201_RID_CNFBASICRATES
mdefine_line|#define ZD1201_RID_CNFBASICRATES&t;0xfcb3
DECL|macro|ZD1201_RID_AUTHENTICATESTA
mdefine_line|#define ZD1201_RID_AUTHENTICATESTA&t;0xfce3
DECL|macro|ZD1201_RID_CURRENTBSSID
mdefine_line|#define ZD1201_RID_CURRENTBSSID&t;&t;0xfd42
DECL|macro|ZD1201_RID_COMMSQUALITY
mdefine_line|#define ZD1201_RID_COMMSQUALITY&t;&t;0xfd43
DECL|macro|ZD1201_RID_CURRENTTXRATE
mdefine_line|#define ZD1201_RID_CURRENTTXRATE&t;0xfd44
DECL|macro|ZD1201_RID_CNFMAXTXBUFFERNUMBER
mdefine_line|#define ZD1201_RID_CNFMAXTXBUFFERNUMBER&t;0xfda0
DECL|macro|ZD1201_RID_CURRENTCHANNEL
mdefine_line|#define ZD1201_RID_CURRENTCHANNEL&t;0xfdc1
DECL|macro|ZD1201_INQ_SCANRESULTS
mdefine_line|#define ZD1201_INQ_SCANRESULTS&t;&t;0xf101
DECL|macro|ZD1201_INF_LINKSTATUS
mdefine_line|#define ZD1201_INF_LINKSTATUS&t;&t;0xf200
DECL|macro|ZD1201_INF_ASSOCSTATUS
mdefine_line|#define ZD1201_INF_ASSOCSTATUS&t;&t;0xf201
DECL|macro|ZD1201_INF_AUTHREQ
mdefine_line|#define ZD1201_INF_AUTHREQ&t;&t;0xf202
DECL|macro|ZD1201_ASSOCSTATUS_STAASSOC
mdefine_line|#define ZD1201_ASSOCSTATUS_STAASSOC&t;0x1
DECL|macro|ZD1201_ASSOCSTATUS_REASSOC
mdefine_line|#define ZD1201_ASSOCSTATUS_REASSOC&t;0x2
DECL|macro|ZD1201_ASSOCSTATUS_DISASSOC
mdefine_line|#define ZD1201_ASSOCSTATUS_DISASSOC&t;0x3
DECL|macro|ZD1201_ASSOCSTATUS_ASSOCFAIL
mdefine_line|#define ZD1201_ASSOCSTATUS_ASSOCFAIL&t;0x4
DECL|macro|ZD1201_ASSOCSTATUS_AUTHFAIL
mdefine_line|#define ZD1201_ASSOCSTATUS_AUTHFAIL&t;0x5
DECL|macro|ZD1201_PORTTYPE_IBSS
mdefine_line|#define ZD1201_PORTTYPE_IBSS&t;&t;0
DECL|macro|ZD1201_PORTTYPE_BSS
mdefine_line|#define ZD1201_PORTTYPE_BSS&t;&t;1
DECL|macro|ZD1201_PORTTYPE_WDS
mdefine_line|#define ZD1201_PORTTYPE_WDS&t;&t;2
DECL|macro|ZD1201_PORTTYPE_PSEUDOIBSS
mdefine_line|#define ZD1201_PORTTYPE_PSEUDOIBSS&t;3
DECL|macro|ZD1201_PORTTYPE_AP
mdefine_line|#define ZD1201_PORTTYPE_AP&t;&t;6
DECL|macro|ZD1201_RATEB1
mdefine_line|#define ZD1201_RATEB1&t;1
DECL|macro|ZD1201_RATEB2
mdefine_line|#define ZD1201_RATEB2&t;2
DECL|macro|ZD1201_RATEB5
mdefine_line|#define ZD1201_RATEB5&t;4&t;/* 5.5 really, but 5 is shorter :) */
DECL|macro|ZD1201_RATEB11
mdefine_line|#define ZD1201_RATEB11&t;8
DECL|macro|ZD1201_CNFAUTHENTICATION_OPENSYSTEM
mdefine_line|#define ZD1201_CNFAUTHENTICATION_OPENSYSTEM&t;0
DECL|macro|ZD1201_CNFAUTHENTICATION_SHAREDKEY
mdefine_line|#define ZD1201_CNFAUTHENTICATION_SHAREDKEY&t;1
macro_line|#endif /* _INCLUDE_ZD1201_H_ */
eof
