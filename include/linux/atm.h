multiline_comment|/* atm.h - general ATM declarations */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
multiline_comment|/*&n; * WARNING: User-space programs should not #include &lt;linux/atm.h&gt; directly.&n; *          Instead, #include &lt;atm.h&gt;&n; */
macro_line|#ifndef _LINUX_ATM_H
DECL|macro|_LINUX_ATM_H
mdefine_line|#define _LINUX_ATM_H
multiline_comment|/*&n; * BEGIN_xx and END_xx markers are used for automatic generation of&n; * documentation. Do not change them.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/atmapi.h&gt;
macro_line|#include &lt;linux/atmsap.h&gt;
macro_line|#include &lt;linux/atmioc.h&gt;
multiline_comment|/* general ATM constants */
DECL|macro|ATM_CELL_SIZE
mdefine_line|#define ATM_CELL_SIZE&t;&t;    53&t;/* ATM cell size incl. header */
DECL|macro|ATM_CELL_PAYLOAD
mdefine_line|#define ATM_CELL_PAYLOAD&t;    48&t;/* ATM payload size */
DECL|macro|ATM_AAL0_SDU
mdefine_line|#define ATM_AAL0_SDU&t;&t;    52&t;/* AAL0 SDU size */
DECL|macro|ATM_MAX_AAL34_PDU
mdefine_line|#define ATM_MAX_AAL34_PDU&t; 65535&t;/* maximum AAL3/4 PDU payload */
DECL|macro|ATM_AAL5_TRAILER
mdefine_line|#define ATM_AAL5_TRAILER&t;     8&t;/* AAL5 trailer size */
DECL|macro|ATM_MAX_AAL5_PDU
mdefine_line|#define ATM_MAX_AAL5_PDU&t; 65535&t;/* maximum AAL5 PDU payload */
DECL|macro|ATM_MAX_CDV
mdefine_line|#define ATM_MAX_CDV&t;&t;  9999&t;/* maximum (default) CDV */
DECL|macro|ATM_NOT_RSV_VCI
mdefine_line|#define ATM_NOT_RSV_VCI&t;&t;    32&t;/* first non-reserved VCI value */
DECL|macro|ATM_MAX_VPI
mdefine_line|#define ATM_MAX_VPI&t;&t;   255&t;/* maximum VPI at the UNI */
DECL|macro|ATM_MAX_VPI_NNI
mdefine_line|#define ATM_MAX_VPI_NNI&t;&t;  4096&t;/* maximum VPI at the NNI */
DECL|macro|ATM_MAX_VCI
mdefine_line|#define ATM_MAX_VCI&t;&t; 65535&t;/* maximum VCI */
multiline_comment|/* &quot;protcol&quot; values for the socket system call */
DECL|macro|ATM_NO_AAL
mdefine_line|#define ATM_NO_AAL&t;0&t;&t;/* AAL not specified */
DECL|macro|ATM_AAL0
mdefine_line|#define ATM_AAL0&t;13&t;&t;/* &quot;raw&quot; ATM cells */
DECL|macro|ATM_AAL1
mdefine_line|#define ATM_AAL1&t;1&t;&t;/* AAL1 (CBR) */
DECL|macro|ATM_AAL2
mdefine_line|#define ATM_AAL2&t;2&t;&t;/* AAL2 (VBR) */
DECL|macro|ATM_AAL34
mdefine_line|#define ATM_AAL34&t;3&t;&t;/* AAL3/4 (data) */
DECL|macro|ATM_AAL5
mdefine_line|#define ATM_AAL5&t;5&t;&t;/* AAL5 (data) */
multiline_comment|/*&n; * socket option name coding functions&n; *&n; * Note that __SO_ENCODE and __SO_LEVEL are somewhat a hack since the&n; * &lt;&lt; 22 only reserves 9 bits for the level.  On some architectures&n; * SOL_SOCKET is 0xFFFF, so that&squot;s a bit of a problem&n; */
DECL|macro|__SO_ENCODE
mdefine_line|#define __SO_ENCODE(l,n,t)&t;((((l) &amp; 0x1FF) &lt;&lt; 22) | ((n) &lt;&lt; 16) | &bslash;&n;&t;&t;&t;&t;sizeof(t))
DECL|macro|__SO_LEVEL_MATCH
mdefine_line|#define __SO_LEVEL_MATCH(c,m)&t;(((c) &gt;&gt; 22) == ((m) &amp; 0x1FF))
DECL|macro|__SO_NUMBER
mdefine_line|#define __SO_NUMBER(c)&t;&t;(((c) &gt;&gt; 16) &amp; 0x3f)
DECL|macro|__SO_SIZE
mdefine_line|#define __SO_SIZE(c)&t;&t;((c) &amp; 0x3fff)
multiline_comment|/*&n; * ATM layer&n; */
DECL|macro|SO_SETCLP
mdefine_line|#define SO_SETCLP&t;__SO_ENCODE(SOL_ATM,0,int)
multiline_comment|/* set CLP bit value - TODO */
DECL|macro|SO_CIRANGE
mdefine_line|#define SO_CIRANGE&t;__SO_ENCODE(SOL_ATM,1,struct atm_cirange)
multiline_comment|/* connection identifier range; socket must be&n;&t;&t;&t;       bound or connected */
DECL|macro|SO_ATMQOS
mdefine_line|#define SO_ATMQOS&t;__SO_ENCODE(SOL_ATM,2,struct atm_qos)
multiline_comment|/* Quality of Service setting */
DECL|macro|SO_ATMSAP
mdefine_line|#define SO_ATMSAP&t;__SO_ENCODE(SOL_ATM,3,struct atm_sap)
multiline_comment|/* Service Access Point */
DECL|macro|SO_ATMPVC
mdefine_line|#define SO_ATMPVC&t;__SO_ENCODE(SOL_ATM,4,struct sockaddr_atmpvc)
multiline_comment|/* &quot;PVC&quot; address (also for SVCs); get only */
multiline_comment|/*&n; * Note @@@: since the socket layers don&squot;t really distinguish the control and&n; * the data plane but generally seems to be data plane-centric, any layer is&n; * about equally wrong for the SAP. If you have a better idea about this,&n; * please speak up ...&n; */
multiline_comment|/* ATM cell header (for AAL0) */
multiline_comment|/* BEGIN_CH */
DECL|macro|ATM_HDR_GFC_MASK
mdefine_line|#define ATM_HDR_GFC_MASK&t;0xf0000000
DECL|macro|ATM_HDR_GFC_SHIFT
mdefine_line|#define ATM_HDR_GFC_SHIFT&t;28
DECL|macro|ATM_HDR_VPI_MASK
mdefine_line|#define ATM_HDR_VPI_MASK&t;0x0ff00000
DECL|macro|ATM_HDR_VPI_SHIFT
mdefine_line|#define ATM_HDR_VPI_SHIFT&t;20
DECL|macro|ATM_HDR_VCI_MASK
mdefine_line|#define ATM_HDR_VCI_MASK&t;0x000ffff0
DECL|macro|ATM_HDR_VCI_SHIFT
mdefine_line|#define ATM_HDR_VCI_SHIFT&t;4
DECL|macro|ATM_HDR_PTI_MASK
mdefine_line|#define ATM_HDR_PTI_MASK&t;0x0000000e
DECL|macro|ATM_HDR_PTI_SHIFT
mdefine_line|#define ATM_HDR_PTI_SHIFT&t;1
DECL|macro|ATM_HDR_CLP
mdefine_line|#define ATM_HDR_CLP&t;&t;0x00000001
multiline_comment|/* END_CH */
multiline_comment|/* PTI codings */
multiline_comment|/* BEGIN_PTI */
DECL|macro|ATM_PTI_US0
mdefine_line|#define ATM_PTI_US0&t;0  /* user data cell, congestion not exp, SDU-type 0 */
DECL|macro|ATM_PTI_US1
mdefine_line|#define ATM_PTI_US1&t;1  /* user data cell, congestion not exp, SDU-type 1 */
DECL|macro|ATM_PTI_UCES0
mdefine_line|#define ATM_PTI_UCES0&t;2  /* user data cell, cong. experienced, SDU-type 0 */
DECL|macro|ATM_PTI_UCES1
mdefine_line|#define ATM_PTI_UCES1&t;3  /* user data cell, cong. experienced, SDU-type 1 */
DECL|macro|ATM_PTI_SEGF5
mdefine_line|#define ATM_PTI_SEGF5&t;4  /* segment OAM F5 flow related cell */
DECL|macro|ATM_PTI_E2EF5
mdefine_line|#define ATM_PTI_E2EF5&t;5  /* end-to-end OAM F5 flow related cell */
DECL|macro|ATM_PTI_RSV_RM
mdefine_line|#define ATM_PTI_RSV_RM&t;6  /* reserved for traffic control/resource mgmt */
DECL|macro|ATM_PTI_RSV
mdefine_line|#define ATM_PTI_RSV&t;7  /* reserved */
multiline_comment|/* END_PTI */
multiline_comment|/*&n; * The following items should stay in linux/atm.h, which should be linked to&n; * netatm/atm.h&n; */
multiline_comment|/* Traffic description */
DECL|macro|ATM_NONE
mdefine_line|#define ATM_NONE&t;0&t;&t;/* no traffic */
DECL|macro|ATM_UBR
mdefine_line|#define ATM_UBR&t;&t;1
DECL|macro|ATM_CBR
mdefine_line|#define ATM_CBR&t;&t;2
DECL|macro|ATM_VBR
mdefine_line|#define ATM_VBR&t;&t;3
DECL|macro|ATM_ABR
mdefine_line|#define ATM_ABR&t;&t;4
DECL|macro|ATM_ANYCLASS
mdefine_line|#define ATM_ANYCLASS&t;5&t;&t;/* compatible with everything */
DECL|macro|ATM_MAX_PCR
mdefine_line|#define ATM_MAX_PCR&t;-1&t;&t;/* maximum available PCR */
DECL|struct|atm_trafprm
r_struct
id|atm_trafprm
(brace
DECL|member|traffic_class
r_int
r_char
id|traffic_class
suffix:semicolon
multiline_comment|/* traffic class (ATM_UBR, ...) */
DECL|member|max_pcr
r_int
id|max_pcr
suffix:semicolon
multiline_comment|/* maximum PCR in cells per second */
DECL|member|pcr
r_int
id|pcr
suffix:semicolon
multiline_comment|/* desired PCR in cells per second */
DECL|member|min_pcr
r_int
id|min_pcr
suffix:semicolon
multiline_comment|/* minimum PCR in cells per second */
DECL|member|max_cdv
r_int
id|max_cdv
suffix:semicolon
multiline_comment|/* maximum CDV in microseconds */
DECL|member|max_sdu
r_int
id|max_sdu
suffix:semicolon
multiline_comment|/* maximum SDU in bytes */
multiline_comment|/* extra params for ABR */
DECL|member|icr
r_int
r_int
id|icr
suffix:semicolon
multiline_comment|/* Initial Cell Rate (24-bit) */
DECL|member|tbe
r_int
r_int
id|tbe
suffix:semicolon
multiline_comment|/* Transient Buffer Exposure (24-bit) */
DECL|member|frtt
r_int
r_int
id|frtt
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* Fixed Round Trip Time (24-bit) */
DECL|member|rif
r_int
r_int
id|rif
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Rate Increment Factor (4-bit) */
DECL|member|rdf
r_int
r_int
id|rdf
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Rate Decrease Factor (4-bit) */
DECL|member|nrm_pres
r_int
r_int
id|nrm_pres
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* nrm present bit */
DECL|member|trm_pres
r_int
r_int
id|trm_pres
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* rm present bit */
DECL|member|adtf_pres
r_int
r_int
id|adtf_pres
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* adtf present bit */
DECL|member|cdf_pres
r_int
r_int
id|cdf_pres
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* cdf present bit*/
DECL|member|nrm
r_int
r_int
id|nrm
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Max # of Cells for each forward RM cell (3-bit) */
DECL|member|trm
r_int
r_int
id|trm
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Time between forward RM cells (3-bit) */
DECL|member|adtf
r_int
r_int
id|adtf
suffix:colon
l_int|10
suffix:semicolon
multiline_comment|/* ACR Decrease Time Factor (10-bit) */
DECL|member|cdf
r_int
r_int
id|cdf
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Cutoff Decrease Factor (3-bit) */
DECL|member|spare
r_int
r_int
id|spare
suffix:colon
l_int|9
suffix:semicolon
multiline_comment|/* spare bits */
)brace
suffix:semicolon
DECL|struct|atm_qos
r_struct
id|atm_qos
(brace
DECL|member|txtp
r_struct
id|atm_trafprm
id|txtp
suffix:semicolon
multiline_comment|/* parameters in TX direction */
DECL|member|__ATM_API_ALIGN
r_struct
id|atm_trafprm
id|rxtp
id|__ATM_API_ALIGN
suffix:semicolon
multiline_comment|/* parameters in RX direction */
DECL|member|__ATM_API_ALIGN
r_int
r_char
id|aal
id|__ATM_API_ALIGN
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* PVC addressing */
DECL|macro|ATM_ITF_ANY
mdefine_line|#define ATM_ITF_ANY&t;-1&t;&t;/* &quot;magic&quot; PVC address values */
DECL|macro|ATM_VPI_ANY
mdefine_line|#define ATM_VPI_ANY&t;-1
DECL|macro|ATM_VCI_ANY
mdefine_line|#define ATM_VCI_ANY&t;-1
DECL|macro|ATM_VPI_UNSPEC
mdefine_line|#define ATM_VPI_UNSPEC&t;-2
DECL|macro|ATM_VCI_UNSPEC
mdefine_line|#define ATM_VCI_UNSPEC&t;-2
DECL|struct|sockaddr_atmpvc
r_struct
id|sockaddr_atmpvc
(brace
DECL|member|sap_family
r_int
r_int
id|sap_family
suffix:semicolon
multiline_comment|/* address family, AF_ATMPVC  */
r_struct
(brace
multiline_comment|/* PVC address */
DECL|member|itf
r_int
id|itf
suffix:semicolon
multiline_comment|/* ATM interface */
DECL|member|vpi
r_int
id|vpi
suffix:semicolon
multiline_comment|/* VPI (only 8 bits at UNI) */
DECL|member|vci
r_int
id|vci
suffix:semicolon
multiline_comment|/* VCI (only 16 bits at UNI) */
DECL|member|__ATM_API_ALIGN
)brace
id|sap_addr
id|__ATM_API_ALIGN
suffix:semicolon
multiline_comment|/* PVC address */
)brace
suffix:semicolon
multiline_comment|/* SVC addressing */
DECL|macro|ATM_ESA_LEN
mdefine_line|#define&t;ATM_ESA_LEN&t;20&t;&t;/* ATM End System Address length */
DECL|macro|ATM_E164_LEN
mdefine_line|#define ATM_E164_LEN&t;12&t;&t;/* maximum E.164 number length */
DECL|macro|ATM_AFI_DCC
mdefine_line|#define ATM_AFI_DCC&t;0x39&t;&t;/* DCC ATM Format */
DECL|macro|ATM_AFI_ICD
mdefine_line|#define ATM_AFI_ICD&t;0x47&t;&t;/* ICD ATM Format */
DECL|macro|ATM_AFI_E164
mdefine_line|#define ATM_AFI_E164&t;0x45&t;&t;/* E.164 ATM Format */
DECL|macro|ATM_AFI_LOCAL
mdefine_line|#define ATM_AFI_LOCAL&t;0x49&t;&t;/* Local ATM Format */ 
DECL|macro|ATM_AFI_DCC_GROUP
mdefine_line|#define ATM_AFI_DCC_GROUP&t;0xBD&t;/* DCC ATM Group Format */
DECL|macro|ATM_AFI_ICD_GROUP
mdefine_line|#define ATM_AFI_ICD_GROUP&t;0xC5&t;/* ICD ATM Group Format */
DECL|macro|ATM_AFI_E164_GROUP
mdefine_line|#define ATM_AFI_E164_GROUP&t;0xC3&t;/* E.164 ATM Group Format */
DECL|macro|ATM_AFI_LOCAL_GROUP
mdefine_line|#define ATM_AFI_LOCAL_GROUP&t;0xC7&t;/* Local ATM Group Format */
DECL|macro|ATM_LIJ_NONE
mdefine_line|#define ATM_LIJ_NONE&t;0&t;&t;/* no leaf-initiated join */
DECL|macro|ATM_LIJ
mdefine_line|#define ATM_LIJ&t;&t;1&t;&t;/* request joining */
DECL|macro|ATM_LIJ_RPJ
mdefine_line|#define ATM_LIJ_RPJ&t;2&t;&t;/* set to root-prompted join */
DECL|macro|ATM_LIJ_NJ
mdefine_line|#define ATM_LIJ_NJ&t;3&t;&t;/* set to network join */
DECL|struct|sockaddr_atmsvc
r_struct
id|sockaddr_atmsvc
(brace
DECL|member|sas_family
r_int
r_int
id|sas_family
suffix:semicolon
multiline_comment|/* address family, AF_ATMSVC */
r_struct
(brace
multiline_comment|/* SVC address */
DECL|member|prv
r_int
r_char
id|prv
(braket
id|ATM_ESA_LEN
)braket
suffix:semicolon
multiline_comment|/* private ATM address */
DECL|member|pub
r_char
id|pub
(braket
id|ATM_E164_LEN
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* public address (E.164) */
multiline_comment|/* unused addresses must be bzero&squot;ed */
DECL|member|lij_type
r_char
id|lij_type
suffix:semicolon
multiline_comment|/* role in LIJ call; one of ATM_LIJ* */
DECL|member|lij_id
r_uint32
id|lij_id
suffix:semicolon
multiline_comment|/* LIJ call identifier */
DECL|member|__ATM_API_ALIGN
)brace
id|sas_addr
id|__ATM_API_ALIGN
suffix:semicolon
multiline_comment|/* SVC address */
)brace
suffix:semicolon
DECL|function|atmsvc_addr_in_use
r_static
id|__inline__
r_int
id|atmsvc_addr_in_use
c_func
(paren
r_struct
id|sockaddr_atmsvc
id|addr
)paren
(brace
r_return
op_star
id|addr.sas_addr.prv
op_logical_or
op_star
id|addr.sas_addr.pub
suffix:semicolon
)brace
DECL|function|atmpvc_addr_in_use
r_static
id|__inline__
r_int
id|atmpvc_addr_in_use
c_func
(paren
r_struct
id|sockaddr_atmpvc
id|addr
)paren
(brace
r_return
id|addr.sap_addr.itf
op_logical_or
id|addr.sap_addr.vpi
op_logical_or
id|addr.sap_addr.vci
suffix:semicolon
)brace
multiline_comment|/*&n; * Some stuff for linux/sockios.h&n; */
DECL|struct|atmif_sioc
r_struct
id|atmif_sioc
(brace
DECL|member|number
r_int
id|number
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|arg
r_void
op_star
id|arg
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/net.h&gt;&t;/* struct net_proto */
r_void
id|atmpvc_proto_init
c_func
(paren
r_struct
id|net_proto
op_star
id|pro
)paren
suffix:semicolon
r_void
id|atmsvc_proto_init
c_func
(paren
r_struct
id|net_proto
op_star
id|pro
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
