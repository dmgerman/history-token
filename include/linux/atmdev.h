multiline_comment|/* atmdev.h - ATM device driver declarations and various related items */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef LINUX_ATMDEV_H
DECL|macro|LINUX_ATMDEV_H
mdefine_line|#define LINUX_ATMDEV_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/atmapi.h&gt;
macro_line|#include &lt;linux/atm.h&gt;
macro_line|#include &lt;linux/atmioc.h&gt;
DECL|macro|ESI_LEN
mdefine_line|#define ESI_LEN&t;&t;6
DECL|macro|ATM_OC3_PCR
mdefine_line|#define ATM_OC3_PCR&t;(155520000/270*260/8/53)
multiline_comment|/* OC3 link rate:  155520000 bps&n;&t;&t;&t;   SONET overhead: /270*260 (9 section, 1 path)&n;&t;&t;&t;   bits per cell:  /8/53&n;&t;&t;&t;   max cell rate:  353207.547 cells/sec */
DECL|macro|ATM_25_PCR
mdefine_line|#define ATM_25_PCR&t;((25600000/8-8000)/54)
multiline_comment|/* 25 Mbps ATM cell rate (59111) */
DECL|macro|ATM_OC12_PCR
mdefine_line|#define ATM_OC12_PCR&t;(622080000/1080*1040/8/53)
multiline_comment|/* OC12 link rate: 622080000 bps&n;&t;&t;&t;   SONET overhead: /1080*1040&n;&t;&t;&t;   bits per cell:  /8/53&n;&t;&t;&t;   max cell rate:  1412830.188 cells/sec */
DECL|macro|ATM_DS3_PCR
mdefine_line|#define ATM_DS3_PCR&t;(8000*12)
multiline_comment|/* DS3: 12 cells in a 125 usec time slot */
DECL|macro|ATM_PDU_OVHD
mdefine_line|#define ATM_PDU_OVHD&t;0&t;/* number of bytes to charge against buffer&n;&t;&t;&t;&t;   quota per PDU */
DECL|macro|ATM_SD
mdefine_line|#define ATM_SD(s)&t;((s)-&gt;sk-&gt;protinfo.af_atm)
DECL|macro|__AAL_STAT_ITEMS
mdefine_line|#define __AAL_STAT_ITEMS &bslash;&n;    __HANDLE_ITEM(tx);&t;&t;&t;/* TX okay */ &bslash;&n;    __HANDLE_ITEM(tx_err);&t;&t;/* TX errors */ &bslash;&n;    __HANDLE_ITEM(rx);&t;&t;&t;/* RX okay */ &bslash;&n;    __HANDLE_ITEM(rx_err);&t;&t;/* RX errors */ &bslash;&n;    __HANDLE_ITEM(rx_drop);&t;&t;/* RX out of memory */
DECL|struct|atm_aal_stats
r_struct
id|atm_aal_stats
(brace
DECL|macro|__HANDLE_ITEM
mdefine_line|#define __HANDLE_ITEM(i) int i
id|__AAL_STAT_ITEMS
DECL|macro|__HANDLE_ITEM
macro_line|#undef __HANDLE_ITEM
)brace
suffix:semicolon
DECL|struct|atm_dev_stats
r_struct
id|atm_dev_stats
(brace
DECL|member|aal0
r_struct
id|atm_aal_stats
id|aal0
suffix:semicolon
DECL|member|aal34
r_struct
id|atm_aal_stats
id|aal34
suffix:semicolon
DECL|member|aal5
r_struct
id|atm_aal_stats
id|aal5
suffix:semicolon
DECL|variable|__ATM_API_ALIGN
)brace
id|__ATM_API_ALIGN
suffix:semicolon
DECL|macro|ATM_GETLINKRATE
mdefine_line|#define ATM_GETLINKRATE&t;_IOW(&squot;a&squot;,ATMIOC_ITF+1,struct atmif_sioc)
multiline_comment|/* get link rate */
DECL|macro|ATM_GETNAMES
mdefine_line|#define ATM_GETNAMES&t;_IOW(&squot;a&squot;,ATMIOC_ITF+3,struct atm_iobuf)
multiline_comment|/* get interface names (numbers) */
DECL|macro|ATM_GETTYPE
mdefine_line|#define ATM_GETTYPE&t;_IOW(&squot;a&squot;,ATMIOC_ITF+4,struct atmif_sioc)
multiline_comment|/* get interface type name */
DECL|macro|ATM_GETESI
mdefine_line|#define ATM_GETESI&t;_IOW(&squot;a&squot;,ATMIOC_ITF+5,struct atmif_sioc)
multiline_comment|/* get interface ESI */
DECL|macro|ATM_GETADDR
mdefine_line|#define ATM_GETADDR&t;_IOW(&squot;a&squot;,ATMIOC_ITF+6,struct atmif_sioc)
multiline_comment|/* get itf&squot;s local ATM addr. list */
DECL|macro|ATM_RSTADDR
mdefine_line|#define ATM_RSTADDR&t;_IOW(&squot;a&squot;,ATMIOC_ITF+7,struct atmif_sioc)
multiline_comment|/* reset itf&squot;s ATM address list */
DECL|macro|ATM_ADDADDR
mdefine_line|#define ATM_ADDADDR&t;_IOW(&squot;a&squot;,ATMIOC_ITF+8,struct atmif_sioc)
multiline_comment|/* add a local ATM address */
DECL|macro|ATM_DELADDR
mdefine_line|#define ATM_DELADDR&t;_IOW(&squot;a&squot;,ATMIOC_ITF+9,struct atmif_sioc)
multiline_comment|/* remove a local ATM address */
DECL|macro|ATM_GETCIRANGE
mdefine_line|#define ATM_GETCIRANGE&t;_IOW(&squot;a&squot;,ATMIOC_ITF+10,struct atmif_sioc)
multiline_comment|/* get connection identifier range */
DECL|macro|ATM_SETCIRANGE
mdefine_line|#define ATM_SETCIRANGE&t;_IOW(&squot;a&squot;,ATMIOC_ITF+11,struct atmif_sioc)
multiline_comment|/* set connection identifier range */
DECL|macro|ATM_SETESI
mdefine_line|#define ATM_SETESI&t;_IOW(&squot;a&squot;,ATMIOC_ITF+12,struct atmif_sioc)
multiline_comment|/* set interface ESI */
DECL|macro|ATM_SETESIF
mdefine_line|#define ATM_SETESIF&t;_IOW(&squot;a&squot;,ATMIOC_ITF+13,struct atmif_sioc)
multiline_comment|/* force interface ESI */
DECL|macro|ATM_GETSTAT
mdefine_line|#define ATM_GETSTAT&t;_IOW(&squot;a&squot;,ATMIOC_SARCOM+0,struct atmif_sioc)
multiline_comment|/* get AAL layer statistics */
DECL|macro|ATM_GETSTATZ
mdefine_line|#define ATM_GETSTATZ&t;_IOW(&squot;a&squot;,ATMIOC_SARCOM+1,struct atmif_sioc)
multiline_comment|/* get AAL layer statistics and zero */
DECL|macro|ATM_GETLOOP
mdefine_line|#define ATM_GETLOOP&t;_IOW(&squot;a&squot;,ATMIOC_SARCOM+2,struct atmif_sioc)
multiline_comment|/* get loopback mode */
DECL|macro|ATM_SETLOOP
mdefine_line|#define ATM_SETLOOP&t;_IOW(&squot;a&squot;,ATMIOC_SARCOM+3,struct atmif_sioc)
multiline_comment|/* set loopback mode */
DECL|macro|ATM_QUERYLOOP
mdefine_line|#define ATM_QUERYLOOP&t;_IOW(&squot;a&squot;,ATMIOC_SARCOM+4,struct atmif_sioc)
multiline_comment|/* query supported loopback modes */
DECL|macro|ATM_SETSC
mdefine_line|#define ATM_SETSC&t;_IOW(&squot;a&squot;,ATMIOC_SPECIAL+1,int)
multiline_comment|/* enable or disable single-copy */
DECL|macro|ATM_SETBACKEND
mdefine_line|#define ATM_SETBACKEND&t;_IOW(&squot;a&squot;,ATMIOC_SPECIAL+2,atm_backend_t)
multiline_comment|/* set backend handler */
multiline_comment|/*&n; * These are backend handkers that can be set via the ATM_SETBACKEND call&n; * above.  In the future we may support dynamic loading of these - for now,&n; * they&squot;re just being used to share the ATMIOC_BACKEND ioctls&n; */
DECL|macro|ATM_BACKEND_RAW
mdefine_line|#define ATM_BACKEND_RAW&t;&t;0&t;
DECL|macro|ATM_BACKEND_PPP
mdefine_line|#define ATM_BACKEND_PPP&t;&t;1&t;/* PPPoATM - RFC2364 */
DECL|macro|ATM_BACKEND_BR_2684
mdefine_line|#define ATM_BACKEND_BR_2684&t;2&t;/* Bridged RFC1483/2684 */
multiline_comment|/* for ATM_GETTYPE */
DECL|macro|ATM_ITFTYP_LEN
mdefine_line|#define ATM_ITFTYP_LEN&t;8&t;/* maximum length of interface type name */
multiline_comment|/*&n; * Loopback modes for ATM_{PHY,SAR}_{GET,SET}LOOP&n; */
multiline_comment|/* Point of loopback&t;&t;&t;&t;CPU--&gt;SAR--&gt;PHY--&gt;line--&gt; ... */
DECL|macro|__ATM_LM_NONE
mdefine_line|#define __ATM_LM_NONE&t;0&t;/* no loop back     ^     ^     ^      ^      */
DECL|macro|__ATM_LM_AAL
mdefine_line|#define __ATM_LM_AAL&t;1&t;/* loop back PDUs --&squot;     |     |      |      */
DECL|macro|__ATM_LM_ATM
mdefine_line|#define __ATM_LM_ATM&t;2&t;/* loop back ATM cells ---&squot;     |      |      */
multiline_comment|/* RESERVED&t;&t;4&t;loop back on PHY side  ---&squot;&t;&t;      */
DECL|macro|__ATM_LM_PHY
mdefine_line|#define __ATM_LM_PHY&t;8&t;/* loop back bits (digital) ----&squot;      |      */
DECL|macro|__ATM_LM_ANALOG
mdefine_line|#define __ATM_LM_ANALOG 16&t;/* loop back the analog signal --------&squot;      */
multiline_comment|/* Direction of loopback */
DECL|macro|__ATM_LM_MKLOC
mdefine_line|#define __ATM_LM_MKLOC(n)&t;((n))&t;    /* Local (i.e. loop TX to RX) */
DECL|macro|__ATM_LM_MKRMT
mdefine_line|#define __ATM_LM_MKRMT(n)&t;((n) &lt;&lt; 8)  /* Remote (i.e. loop RX to TX) */
DECL|macro|__ATM_LM_XTLOC
mdefine_line|#define __ATM_LM_XTLOC(n)&t;((n) &amp; 0xff)
DECL|macro|__ATM_LM_XTRMT
mdefine_line|#define __ATM_LM_XTRMT(n)&t;(((n) &gt;&gt; 8) &amp; 0xff)
DECL|macro|ATM_LM_NONE
mdefine_line|#define ATM_LM_NONE&t;0&t;/* no loopback */
DECL|macro|ATM_LM_LOC_AAL
mdefine_line|#define ATM_LM_LOC_AAL&t;__ATM_LM_MKLOC(__ATM_LM_AAL)
DECL|macro|ATM_LM_LOC_ATM
mdefine_line|#define ATM_LM_LOC_ATM&t;__ATM_LM_MKLOC(__ATM_LM_ATM)
DECL|macro|ATM_LM_LOC_PHY
mdefine_line|#define ATM_LM_LOC_PHY&t;__ATM_LM_MKLOC(__ATM_LM_PHY)
DECL|macro|ATM_LM_LOC_ANALOG
mdefine_line|#define ATM_LM_LOC_ANALOG __ATM_LM_MKLOC(__ATM_LM_ANALOG)
DECL|macro|ATM_LM_RMT_AAL
mdefine_line|#define ATM_LM_RMT_AAL&t;__ATM_LM_MKRMT(__ATM_LM_AAL)
DECL|macro|ATM_LM_RMT_ATM
mdefine_line|#define ATM_LM_RMT_ATM&t;__ATM_LM_MKRMT(__ATM_LM_ATM)
DECL|macro|ATM_LM_RMT_PHY
mdefine_line|#define ATM_LM_RMT_PHY&t;__ATM_LM_MKRMT(__ATM_LM_PHY)
DECL|macro|ATM_LM_RMT_ANALOG
mdefine_line|#define ATM_LM_RMT_ANALOG __ATM_LM_MKRMT(__ATM_LM_ANALOG)
multiline_comment|/*&n; * Note: ATM_LM_LOC_* and ATM_LM_RMT_* can be combined, provided that&n; * __ATM_LM_XTLOC(x) &lt;= __ATM_LM_XTRMT(x)&n; */
DECL|struct|atm_iobuf
r_struct
id|atm_iobuf
(brace
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* for ATM_GETCIRANGE / ATM_SETCIRANGE */
DECL|macro|ATM_CI_MAX
mdefine_line|#define ATM_CI_MAX      -1              /* use maximum range of VPI/VCI */
DECL|struct|atm_cirange
r_struct
id|atm_cirange
(brace
DECL|member|vpi_bits
r_char
id|vpi_bits
suffix:semicolon
multiline_comment|/* 1..8, ATM_CI_MAX (-1) for maximum */
DECL|member|vci_bits
r_char
id|vci_bits
suffix:semicolon
multiline_comment|/* 1..16, ATM_CI_MAX (-1) for maximum */
)brace
suffix:semicolon
multiline_comment|/* for ATM_SETSC; actually taken from the ATM_VF number space */
DECL|macro|ATM_SC_RX
mdefine_line|#define ATM_SC_RX&t;1024&t;&t;/* enable RX single-copy */
DECL|macro|ATM_SC_TX
mdefine_line|#define ATM_SC_TX&t;2048&t;&t;/* enable TX single-copy */
DECL|macro|ATM_BACKLOG_DEFAULT
mdefine_line|#define ATM_BACKLOG_DEFAULT 32 /* if we get more, we&squot;re likely to time out&n;&t;&t;&t;&t;  anyway */
multiline_comment|/* MF: change_qos (Modify) flags */
DECL|macro|ATM_MF_IMMED
mdefine_line|#define ATM_MF_IMMED&t; 1&t;/* Block until change is effective */
DECL|macro|ATM_MF_INC_RSV
mdefine_line|#define ATM_MF_INC_RSV&t; 2&t;/* Change reservation on increase */
DECL|macro|ATM_MF_INC_SHP
mdefine_line|#define ATM_MF_INC_SHP&t; 4&t;/* Change shaping on increase */
DECL|macro|ATM_MF_DEC_RSV
mdefine_line|#define ATM_MF_DEC_RSV&t; 8&t;/* Change reservation on decrease */
DECL|macro|ATM_MF_DEC_SHP
mdefine_line|#define ATM_MF_DEC_SHP&t;16&t;/* Change shaping on decrease */
DECL|macro|ATM_MF_BWD
mdefine_line|#define ATM_MF_BWD&t;32&t;/* Set the backward direction parameters */
DECL|macro|ATM_MF_SET
mdefine_line|#define ATM_MF_SET&t;(ATM_MF_INC_RSV | ATM_MF_INC_SHP | ATM_MF_DEC_RSV | &bslash;&n;&t;&t;&t;  ATM_MF_DEC_SHP | ATM_MF_BWD)
multiline_comment|/*&n; * ATM_VS_* are used to express VC state in a human-friendly way.&n; */
DECL|macro|ATM_VS_IDLE
mdefine_line|#define ATM_VS_IDLE&t;0&t;/* VC is not used */
DECL|macro|ATM_VS_CONNECTED
mdefine_line|#define ATM_VS_CONNECTED 1&t;/* VC is connected */
DECL|macro|ATM_VS_CLOSING
mdefine_line|#define ATM_VS_CLOSING&t;2&t;/* VC is closing */
DECL|macro|ATM_VS_LISTEN
mdefine_line|#define ATM_VS_LISTEN&t;3&t;/* VC is listening for incoming setups */
DECL|macro|ATM_VS_INUSE
mdefine_line|#define ATM_VS_INUSE&t;4&t;/* VC is in use (registered with atmsigd) */
DECL|macro|ATM_VS_BOUND
mdefine_line|#define ATM_VS_BOUND&t;5&t;/* VC is bound */
DECL|macro|ATM_VS2TXT_MAP
mdefine_line|#define ATM_VS2TXT_MAP &bslash;&n;    &quot;IDLE&quot;, &quot;CONNECTED&quot;, &quot;CLOSING&quot;, &quot;LISTEN&quot;, &quot;INUSE&quot;, &quot;BOUND&quot;
DECL|macro|ATM_VF2TXT_MAP
mdefine_line|#define ATM_VF2TXT_MAP &bslash;&n;    &quot;ADDR&quot;,&t;&quot;READY&quot;,&t;&quot;PARTIAL&quot;,&t;&quot;REGIS&quot;, &bslash;&n;    &quot;RELEASED&quot;, &quot;HASQOS&quot;,&t;&quot;LISTEN&quot;,&t;&quot;META&quot;, &bslash;&n;    &quot;256&quot;,&t;&quot;512&quot;,&t;&t;&quot;1024&quot;,&t;&t;&quot;2048&quot;, &bslash;&n;    &quot;SESSION&quot;,&t;&quot;HASSAP&quot;,&t;&quot;BOUND&quot;,&t;&quot;CLOSE&quot;
macro_line|#ifndef __KERNEL__
DECL|macro|__AAL_STAT_ITEMS
macro_line|#undef __AAL_STAT_ITEMS
macro_line|#else
macro_line|#include &lt;linux/sched.h&gt; /* wait_queue_head_t */
macro_line|#include &lt;linux/time.h&gt; /* struct timeval */
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt; /* struct sk_buff */
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#ifdef CONFIG_PROC_FS
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#endif
DECL|struct|k_atm_aal_stats
r_struct
id|k_atm_aal_stats
(brace
DECL|macro|__HANDLE_ITEM
mdefine_line|#define __HANDLE_ITEM(i) atomic_t i
id|__AAL_STAT_ITEMS
DECL|macro|__HANDLE_ITEM
macro_line|#undef __HANDLE_ITEM
)brace
suffix:semicolon
DECL|struct|k_atm_dev_stats
r_struct
id|k_atm_dev_stats
(brace
DECL|member|aal0
r_struct
id|k_atm_aal_stats
id|aal0
suffix:semicolon
DECL|member|aal34
r_struct
id|k_atm_aal_stats
id|aal34
suffix:semicolon
DECL|member|aal5
r_struct
id|k_atm_aal_stats
id|aal5
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|ATM_VF_ADDR
id|ATM_VF_ADDR
comma
multiline_comment|/* Address is in use. Set by anybody, cleared&n;&t;&t;&t;&t;   by device driver. */
DECL|enumerator|ATM_VF_READY
id|ATM_VF_READY
comma
multiline_comment|/* VC is ready to transfer data. Set by device&n;&t;&t;&t;&t;   driver, cleared by anybody. */
DECL|enumerator|ATM_VF_PARTIAL
id|ATM_VF_PARTIAL
comma
multiline_comment|/* resources are bound to PVC (partial PVC&n;&t;&t;&t;&t;   setup), controlled by socket layer */
DECL|enumerator|ATM_VF_REGIS
id|ATM_VF_REGIS
comma
multiline_comment|/* registered with demon, controlled by SVC&n;&t;&t;&t;&t;   socket layer */
DECL|enumerator|ATM_VF_BOUND
id|ATM_VF_BOUND
comma
multiline_comment|/* local SAP is set, controlled by SVC socket&n;&t;&t;&t;&t;   layer */
DECL|enumerator|ATM_VF_RELEASED
id|ATM_VF_RELEASED
comma
multiline_comment|/* demon has indicated/requested release,&n;&t;&t;&t;&t;   controlled by SVC socket layer */
DECL|enumerator|ATM_VF_HASQOS
id|ATM_VF_HASQOS
comma
multiline_comment|/* QOS parameters have been set */
DECL|enumerator|ATM_VF_LISTEN
id|ATM_VF_LISTEN
comma
multiline_comment|/* socket is used for listening */
DECL|enumerator|ATM_VF_META
id|ATM_VF_META
comma
multiline_comment|/* SVC socket isn&squot;t used for normal data&n;&t;&t;&t;&t;   traffic and doesn&squot;t depend on signaling&n;&t;&t;&t;&t;   to be available */
DECL|enumerator|ATM_VF_SESSION
id|ATM_VF_SESSION
comma
multiline_comment|/* VCC is p2mp session control descriptor */
DECL|enumerator|ATM_VF_HASSAP
id|ATM_VF_HASSAP
comma
multiline_comment|/* SAP has been set */
DECL|enumerator|ATM_VF_CLOSE
id|ATM_VF_CLOSE
comma
multiline_comment|/* asynchronous close - treat like VF_RELEASED*/
)brace
suffix:semicolon
DECL|macro|ATM_VF2VS
mdefine_line|#define ATM_VF2VS(flags) &bslash;&n;    (test_bit(ATM_VF_READY,&amp;(flags)) ? ATM_VS_CONNECTED : &bslash;&n;     test_bit(ATM_VF_RELEASED,&amp;(flags)) ? ATM_VS_CLOSING : &bslash;&n;     test_bit(ATM_VF_LISTEN,&amp;(flags)) ? ATM_VS_LISTEN : &bslash;&n;     test_bit(ATM_VF_REGIS,&amp;(flags)) ? ATM_VS_INUSE : &bslash;&n;     test_bit(ATM_VF_BOUND,&amp;(flags)) ? ATM_VS_BOUND : ATM_VS_IDLE)
r_enum
(brace
DECL|enumerator|ATM_DF_CLOSE
id|ATM_DF_CLOSE
comma
multiline_comment|/* close device when last VCC is closed */
)brace
suffix:semicolon
DECL|macro|ATM_PHY_SIG_LOST
mdefine_line|#define ATM_PHY_SIG_LOST    0&t;/* no carrier/light */
DECL|macro|ATM_PHY_SIG_UNKNOWN
mdefine_line|#define ATM_PHY_SIG_UNKNOWN 1&t;/* carrier/light status is unknown */
DECL|macro|ATM_PHY_SIG_FOUND
mdefine_line|#define ATM_PHY_SIG_FOUND   2&t;/* carrier/light okay */
DECL|macro|ATM_ATMOPT_CLP
mdefine_line|#define ATM_ATMOPT_CLP&t;1&t;/* set CLP bit */
DECL|member|bits
DECL|typedef|atm_vcc_flags_t
r_typedef
r_struct
(brace
r_int
r_int
id|bits
suffix:semicolon
)brace
id|atm_vcc_flags_t
suffix:semicolon
DECL|struct|atm_vcc
r_struct
id|atm_vcc
(brace
DECL|member|flags
id|atm_vcc_flags_t
id|flags
suffix:semicolon
multiline_comment|/* VCC flags (ATM_VF_*) */
DECL|member|family
r_int
r_char
id|family
suffix:semicolon
multiline_comment|/* address family; 0 if unused */
DECL|member|vpi
r_int
id|vpi
suffix:semicolon
multiline_comment|/* VPI and VCI (types must be equal */
multiline_comment|/* with sockaddr) */
DECL|member|vci
r_int
id|vci
suffix:semicolon
DECL|member|aal_options
r_int
r_int
id|aal_options
suffix:semicolon
multiline_comment|/* AAL layer options */
DECL|member|atm_options
r_int
r_int
id|atm_options
suffix:semicolon
multiline_comment|/* ATM layer options */
DECL|member|dev
r_struct
id|atm_dev
op_star
id|dev
suffix:semicolon
multiline_comment|/* device back pointer */
DECL|member|qos
r_struct
id|atm_qos
id|qos
suffix:semicolon
multiline_comment|/* QOS */
DECL|member|sap
r_struct
id|atm_sap
id|sap
suffix:semicolon
multiline_comment|/* SAP */
DECL|member|tx_inuse
DECL|member|rx_inuse
id|atomic_t
id|tx_inuse
comma
id|rx_inuse
suffix:semicolon
multiline_comment|/* buffer space in use */
DECL|member|push
r_void
(paren
op_star
id|push
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|member|pop
r_void
(paren
op_star
id|pop
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* optional */
DECL|member|alloc_tx
r_struct
id|sk_buff
op_star
(paren
op_star
id|alloc_tx
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* TX allocation routine - can be */
multiline_comment|/* modified by protocol or by driver.*/
multiline_comment|/* NOTE: this interface will change */
DECL|member|push_oam
r_int
(paren
op_star
id|push_oam
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_void
op_star
id|cell
)paren
suffix:semicolon
DECL|member|send
r_int
(paren
op_star
id|send
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|member|dev_data
r_void
op_star
id|dev_data
suffix:semicolon
multiline_comment|/* per-device data */
DECL|member|proto_data
r_void
op_star
id|proto_data
suffix:semicolon
multiline_comment|/* per-protocol data */
DECL|member|timestamp
r_struct
id|timeval
id|timestamp
suffix:semicolon
multiline_comment|/* AAL timestamps */
DECL|member|recvq
r_struct
id|sk_buff_head
id|recvq
suffix:semicolon
multiline_comment|/* receive queue */
DECL|member|stats
r_struct
id|k_atm_aal_stats
op_star
id|stats
suffix:semicolon
multiline_comment|/* pointer to AAL stats group */
DECL|member|sleep
id|wait_queue_head_t
id|sleep
suffix:semicolon
multiline_comment|/* if socket is busy */
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
multiline_comment|/* socket backpointer */
DECL|member|prev
DECL|member|next
r_struct
id|atm_vcc
op_star
id|prev
comma
op_star
id|next
suffix:semicolon
multiline_comment|/* SVC part --- may move later ------------------------------------- */
DECL|member|itf
r_int
id|itf
suffix:semicolon
multiline_comment|/* interface number */
DECL|member|local
r_struct
id|sockaddr_atmsvc
id|local
suffix:semicolon
DECL|member|remote
r_struct
id|sockaddr_atmsvc
id|remote
suffix:semicolon
DECL|member|callback
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
suffix:semicolon
DECL|member|listenq
r_struct
id|sk_buff_head
id|listenq
suffix:semicolon
DECL|member|backlog_quota
r_int
id|backlog_quota
suffix:semicolon
multiline_comment|/* number of connection requests we */
multiline_comment|/* can still accept */
DECL|member|reply
r_int
id|reply
suffix:semicolon
multiline_comment|/* also used by ATMTCP */
multiline_comment|/* Multipoint part ------------------------------------------------- */
DECL|member|session
r_struct
id|atm_vcc
op_star
id|session
suffix:semicolon
multiline_comment|/* session VCC descriptor */
multiline_comment|/* Other stuff ----------------------------------------------------- */
DECL|member|user_back
r_void
op_star
id|user_back
suffix:semicolon
multiline_comment|/* user backlink - not touched by */
multiline_comment|/* native ATM stack. Currently used */
multiline_comment|/* by CLIP and sch_atm. */
)brace
suffix:semicolon
DECL|struct|atm_dev_addr
r_struct
id|atm_dev_addr
(brace
DECL|member|addr
r_struct
id|sockaddr_atmsvc
id|addr
suffix:semicolon
multiline_comment|/* ATM address */
DECL|member|next
r_struct
id|atm_dev_addr
op_star
id|next
suffix:semicolon
multiline_comment|/* next address */
)brace
suffix:semicolon
DECL|member|bits
DECL|typedef|atm_dev_flags_t
r_typedef
r_struct
(brace
r_int
r_int
id|bits
suffix:semicolon
)brace
id|atm_dev_flags_t
suffix:semicolon
DECL|struct|atm_dev
r_struct
id|atm_dev
(brace
DECL|member|ops
r_const
r_struct
id|atmdev_ops
op_star
id|ops
suffix:semicolon
multiline_comment|/* device operations; NULL if unused */
DECL|member|phy
r_const
r_struct
id|atmphy_ops
op_star
id|phy
suffix:semicolon
multiline_comment|/* PHY operations, may be undefined */
multiline_comment|/* (NULL) */
DECL|member|type
r_const
r_char
op_star
id|type
suffix:semicolon
multiline_comment|/* device type name */
DECL|member|number
r_int
id|number
suffix:semicolon
multiline_comment|/* device index */
DECL|member|vccs
r_struct
id|atm_vcc
op_star
id|vccs
suffix:semicolon
multiline_comment|/* VCC table (or NULL) */
DECL|member|last
r_struct
id|atm_vcc
op_star
id|last
suffix:semicolon
multiline_comment|/* last VCC (or undefined) */
DECL|member|dev_data
r_void
op_star
id|dev_data
suffix:semicolon
multiline_comment|/* per-device data */
DECL|member|phy_data
r_void
op_star
id|phy_data
suffix:semicolon
multiline_comment|/* private PHY date */
DECL|member|flags
id|atm_dev_flags_t
id|flags
suffix:semicolon
multiline_comment|/* device flags (ATM_DF_*) */
DECL|member|local
r_struct
id|atm_dev_addr
op_star
id|local
suffix:semicolon
multiline_comment|/* local ATM addresses */
DECL|member|esi
r_int
r_char
id|esi
(braket
id|ESI_LEN
)braket
suffix:semicolon
multiline_comment|/* ESI (&quot;MAC&quot; addr) */
DECL|member|ci_range
r_struct
id|atm_cirange
id|ci_range
suffix:semicolon
multiline_comment|/* VPI/VCI range */
DECL|member|stats
r_struct
id|k_atm_dev_stats
id|stats
suffix:semicolon
multiline_comment|/* statistics */
DECL|member|signal
r_char
id|signal
suffix:semicolon
multiline_comment|/* signal status (ATM_PHY_SIG_*) */
DECL|member|link_rate
r_int
id|link_rate
suffix:semicolon
multiline_comment|/* link rate (default: OC3) */
macro_line|#ifdef CONFIG_PROC_FS
DECL|member|proc_entry
r_struct
id|proc_dir_entry
op_star
id|proc_entry
suffix:semicolon
multiline_comment|/* proc entry */
DECL|member|proc_name
r_char
op_star
id|proc_name
suffix:semicolon
multiline_comment|/* proc entry name */
macro_line|#endif
DECL|member|prev
DECL|member|next
r_struct
id|atm_dev
op_star
id|prev
comma
op_star
id|next
suffix:semicolon
multiline_comment|/* linkage */
)brace
suffix:semicolon
multiline_comment|/*&n; * ioctl, getsockopt, setsockopt, and sg_send are optional and can be set to&n; * NULL. */
multiline_comment|/* OF: send_Oam Flags */
DECL|macro|ATM_OF_IMMED
mdefine_line|#define ATM_OF_IMMED&t;1&t;/* Attempt immediate delivery */
DECL|macro|ATM_OF_INRATE
mdefine_line|#define ATM_OF_INRATE&t;2&t;/* Attempt in-rate delivery */
DECL|struct|atmdev_ops
r_struct
id|atmdev_ops
(brace
multiline_comment|/* only send is required */
DECL|member|dev_close
r_void
(paren
op_star
id|dev_close
)paren
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|vpi
comma
r_int
id|vci
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
DECL|member|getsockopt
r_int
(paren
op_star
id|getsockopt
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|level
comma
r_int
id|optname
comma
r_void
op_star
id|optval
comma
r_int
id|optlen
)paren
suffix:semicolon
DECL|member|setsockopt
r_int
(paren
op_star
id|setsockopt
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|level
comma
r_int
id|optname
comma
r_void
op_star
id|optval
comma
r_int
id|optlen
)paren
suffix:semicolon
DECL|member|send
r_int
(paren
op_star
id|send
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|member|sg_send
r_int
(paren
op_star
id|sg_send
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
suffix:semicolon
macro_line|#if 0 /* keep the current hack for now */
r_int
(paren
op_star
id|send_iovec
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|iovec
op_star
id|iov
comma
r_int
id|size
comma
r_void
(paren
op_star
id|discard
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_void
op_star
id|user
)paren
comma
r_void
op_star
id|user
)paren
suffix:semicolon
macro_line|#endif
DECL|member|send_oam
r_int
(paren
op_star
id|send_oam
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_void
op_star
id|cell
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|phy_put
r_void
(paren
op_star
id|phy_put
)paren
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
r_int
r_char
id|value
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|member|phy_get
r_int
r_char
(paren
op_star
id|phy_get
)paren
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|member|feedback
r_void
(paren
op_star
id|feedback
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_int
id|start
comma
r_int
r_int
id|dest
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|change_qos
r_int
(paren
op_star
id|change_qos
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|atm_qos
op_star
id|qos
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|free_rx_skb
r_void
(paren
op_star
id|free_rx_skb
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* @@@ temporary hack */
DECL|member|proc_read
r_int
(paren
op_star
id|proc_read
)paren
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
id|loff_t
op_star
id|pos
comma
r_char
op_star
id|page
)paren
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|atmphy_ops
r_struct
id|atmphy_ops
(brace
DECL|member|start
r_int
(paren
op_star
id|start
)paren
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
DECL|member|interrupt
r_void
(paren
op_star
id|interrupt
)paren
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|member|stop
r_int
(paren
op_star
id|stop
)paren
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|atm_skb_data
r_struct
id|atm_skb_data
(brace
DECL|member|vcc
r_struct
id|atm_vcc
op_star
id|vcc
suffix:semicolon
multiline_comment|/* ATM VCC */
DECL|member|iovcnt
r_int
id|iovcnt
suffix:semicolon
multiline_comment|/* 0 for &quot;normal&quot; operation */
DECL|member|atm_options
r_int
r_int
id|atm_options
suffix:semicolon
multiline_comment|/* ATM layer options */
)brace
suffix:semicolon
DECL|macro|ATM_SKB
mdefine_line|#define ATM_SKB(skb) (((struct atm_skb_data *) (skb)-&gt;cb))
r_struct
id|atm_dev
op_star
id|atm_dev_register
c_func
(paren
r_const
r_char
op_star
id|type
comma
r_const
r_struct
id|atmdev_ops
op_star
id|ops
comma
r_int
id|number
comma
id|atm_dev_flags_t
op_star
id|flags
)paren
suffix:semicolon
multiline_comment|/* number == -1: pick first available */
r_struct
id|atm_dev
op_star
id|atm_find_dev
c_func
(paren
r_int
id|number
)paren
suffix:semicolon
r_void
id|atm_dev_deregister
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|shutdown_atm_dev
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|bind_vcc
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|atm_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n; * This is approximately the algorithm used by alloc_skb.&n; *&n; */
DECL|function|atm_guess_pdu2truesize
r_static
id|__inline__
r_int
id|atm_guess_pdu2truesize
c_func
(paren
r_int
id|pdu_size
)paren
(brace
r_return
(paren
(paren
id|pdu_size
op_plus
l_int|15
)paren
op_amp
op_complement
l_int|15
)paren
op_plus
r_sizeof
(paren
r_struct
id|sk_buff
)paren
suffix:semicolon
)brace
DECL|function|atm_force_charge
r_static
id|__inline__
r_void
id|atm_force_charge
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|truesize
)paren
(brace
id|atomic_add
c_func
(paren
id|truesize
op_plus
id|ATM_PDU_OVHD
comma
op_amp
id|vcc-&gt;rx_inuse
)paren
suffix:semicolon
)brace
DECL|function|atm_return
r_static
id|__inline__
r_void
id|atm_return
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|truesize
)paren
(brace
id|atomic_sub
c_func
(paren
id|truesize
op_plus
id|ATM_PDU_OVHD
comma
op_amp
id|vcc-&gt;rx_inuse
)paren
suffix:semicolon
)brace
DECL|function|atm_may_send
r_static
id|__inline__
r_int
id|atm_may_send
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|size
op_plus
id|atomic_read
c_func
(paren
op_amp
id|vcc-&gt;tx_inuse
)paren
op_plus
id|ATM_PDU_OVHD
OL
id|vcc-&gt;sk-&gt;sndbuf
suffix:semicolon
)brace
r_int
id|atm_charge
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|truesize
)paren
suffix:semicolon
r_struct
id|sk_buff
op_star
id|atm_alloc_charge
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|pdu_size
comma
r_int
id|gfp_flags
)paren
suffix:semicolon
r_int
id|atm_find_ci
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
op_star
id|vpi
comma
r_int
op_star
id|vci
)paren
suffix:semicolon
r_int
id|atm_pcr_goal
c_func
(paren
r_struct
id|atm_trafprm
op_star
id|tp
)paren
suffix:semicolon
r_void
id|atm_async_release_vcc
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|reply
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
