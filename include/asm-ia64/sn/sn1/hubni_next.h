multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2001 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SN1_HUBNI_NEXT_H
DECL|macro|_ASM_IA64_SN_SN1_HUBNI_NEXT_H
mdefine_line|#define _ASM_IA64_SN_SN1_HUBNI_NEXT_H
DECL|macro|NI_LOCAL_ENTRIES
mdefine_line|#define NI_LOCAL_ENTRIES        128
DECL|macro|NI_META_ENTRIES
mdefine_line|#define NI_META_ENTRIES        1
DECL|macro|NI_LOCAL_TABLE
mdefine_line|#define NI_LOCAL_TABLE(_x)      (NI_LOCAL_TABLE_0 + (8 * (_x)))
DECL|macro|NI_META_TABLE
mdefine_line|#define NI_META_TABLE(_x)       (NI_GLOBAL_TABLE + (8 * (_x)))
multiline_comment|/**************************************************************&n;&n;  Masks and shifts for NI registers are defined below. &n;&n;**************************************************************/
DECL|macro|NPS_LINKUP_SHFT
mdefine_line|#define NPS_LINKUP_SHFT        1
DECL|macro|NPS_LINKUP_MASK
mdefine_line|#define NPS_LINKUP_MASK        (UINT64_CAST 0x1 &lt;&lt; 1)
DECL|macro|NPR_LOCALRESET
mdefine_line|#define NPR_LOCALRESET          (UINT64_CAST 1 &lt;&lt; 2)    /* Reset loc. bdrck */
DECL|macro|NPR_PORTRESET
mdefine_line|#define NPR_PORTRESET           (UINT64_CAST 1 &lt;&lt; 1)    /* Send warm reset  */
DECL|macro|NPR_LINKRESET
mdefine_line|#define NPR_LINKRESET           (UINT64_CAST 1 &lt;&lt; 0)    /* Send link reset  */
multiline_comment|/* NI_DIAG_PARMS bit definitions */
DECL|macro|NDP_SENDERROR
mdefine_line|#define NDP_SENDERROR           (UINT64_CAST 1 &lt;&lt;  0)   /* Send data error  */
DECL|macro|NDP_PORTDISABLE
mdefine_line|#define NDP_PORTDISABLE         (UINT64_CAST 1 &lt;&lt;  1)   /* Port disable     */
DECL|macro|NDP_SENDERROFF
mdefine_line|#define NDP_SENDERROFF          (UINT64_CAST 1 &lt;&lt;  2)   /* Disable send error recovery */
multiline_comment|/* NI_PORT_ERROR mask and shift definitions (some are not present in SN0) */
DECL|macro|NPE_LINKRESET
mdefine_line|#define NPE_LINKRESET&t;&t;(UINT64_CAST 1 &lt;&lt; 52)
DECL|macro|NPE_INTLONG_SHFT
mdefine_line|#define NPE_INTLONG_SHFT&t;48
DECL|macro|NPE_INTLONG_MASK
mdefine_line|#define NPE_INTLONG_MASK&t;(UINT64_CAST 0xf &lt;&lt; NPE_INTLONG_SHFT)
DECL|macro|NPE_INTSHORT_SHFT
mdefine_line|#define NPE_INTSHORT_SHFT&t;44
DECL|macro|NPE_INTSHORT_MASK
mdefine_line|#define NPE_INTSHORT_MASK&t;(UINT64_CAST 0xf &lt;&lt; NPE_INTSHORT_SHFT)
DECL|macro|NPE_EXTBADHEADER_SHFT
mdefine_line|#define NPE_EXTBADHEADER_SHFT&t;40
DECL|macro|NPE_EXTBADHEADER_MASK
mdefine_line|#define NPE_EXTBADHEADER_MASK&t;(UINT64_CAST 0xf &lt;&lt; NPE_EXTBADHEADER_SHFT)
DECL|macro|NPE_EXTLONG_SHFT
mdefine_line|#define NPE_EXTLONG_SHFT&t;36
DECL|macro|NPE_EXTLONG_MASK
mdefine_line|#define NPE_EXTLONG_MASK&t;(UINT64_CAST 0xf &lt;&lt; NPE_EXTLONG_SHFT)
DECL|macro|NPE_EXTSHORT_SHFT
mdefine_line|#define NPE_EXTSHORT_SHFT&t;32
DECL|macro|NPE_EXTSHORT_MASK
mdefine_line|#define NPE_EXTSHORT_MASK&t;(UINT64_CAST 0xf &lt;&lt; NPE_EXTSHORT_SHFT)
DECL|macro|NPE_FIFOOVFLOW_SHFT
mdefine_line|#define NPE_FIFOOVFLOW_SHFT&t;28
DECL|macro|NPE_FIFOOVFLOW_MASK
mdefine_line|#define NPE_FIFOOVFLOW_MASK&t;(UINT64_CAST 0xf &lt;&lt; NPE_FIFOOVFLOW_SHFT)
DECL|macro|NPE_TAILTO_SHFT
mdefine_line|#define NPE_TAILTO_SHFT&t;&t;24
DECL|macro|NPE_TAILTO_MASK
mdefine_line|#define NPE_TAILTO_MASK&t;&t;(UINT64_CAST 0xf &lt;&lt; NPE_TAILTO_SHFT)
DECL|macro|NPE_RETRYCOUNT_SHFT
mdefine_line|#define NPE_RETRYCOUNT_SHFT&t;16
DECL|macro|NPE_RETRYCOUNT_MASK
mdefine_line|#define NPE_RETRYCOUNT_MASK&t;(UINT64_CAST 0xff &lt;&lt; NPE_RETRYCOUNT_SHFT)
DECL|macro|NPE_CBERRCOUNT_SHFT
mdefine_line|#define NPE_CBERRCOUNT_SHFT&t;8
DECL|macro|NPE_CBERRCOUNT_MASK
mdefine_line|#define NPE_CBERRCOUNT_MASK&t;(UINT64_CAST 0xff &lt;&lt; NPE_CBERRCOUNT_SHFT)
DECL|macro|NPE_SNERRCOUNT_SHFT
mdefine_line|#define NPE_SNERRCOUNT_SHFT&t;0
DECL|macro|NPE_SNERRCOUNT_MASK
mdefine_line|#define NPE_SNERRCOUNT_MASK&t;(UINT64_CAST 0xff &lt;&lt; NPE_SNERRCOUNT_SHFT)
DECL|macro|NPE_COUNT_MAX
mdefine_line|#define NPE_COUNT_MAX&t;&t;0xff
DECL|macro|NPE_FATAL_ERRORS
mdefine_line|#define NPE_FATAL_ERRORS&t;(NPE_LINKRESET | NPE_INTLONG_MASK |&bslash;&n;&t;&t;&t;&t; NPE_INTSHORT_MASK | NPE_EXTBADHEADER_MASK |&bslash;&n;&t;&t;&t;&t; NPE_EXTLONG_MASK | NPE_EXTSHORT_MASK |&bslash;&n;&t;&t;&t;&t; NPE_FIFOOVFLOW_MASK | NPE_TAILTO_MASK)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* NI_PORT_HEADER[AB] registers (not automatically generated) */
macro_line|#ifdef LITTLE_ENDIAN
DECL|union|ni_port_header_a_u
r_typedef
r_union
id|ni_port_header_a_u
(brace
DECL|member|ni_port_header_a_regval
id|bdrkreg_t
id|ni_port_header_a_regval
suffix:semicolon
r_struct
(brace
DECL|member|pha_v
id|bdrkreg_t
id|pha_v
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pha_age
id|bdrkreg_t
id|pha_age
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pha_direction
id|bdrkreg_t
id|pha_direction
suffix:colon
l_int|4
suffix:semicolon
DECL|member|pha_destination
id|bdrkreg_t
id|pha_destination
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pha_reserved_1
id|bdrkreg_t
id|pha_reserved_1
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pha_command
id|bdrkreg_t
id|pha_command
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pha_prexsel
id|bdrkreg_t
id|pha_prexsel
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pha_address_b
id|bdrkreg_t
id|pha_address_b
suffix:colon
l_int|27
suffix:semicolon
DECL|member|pha_reserved
id|bdrkreg_t
id|pha_reserved
suffix:colon
l_int|2
suffix:semicolon
DECL|member|ni_port_header_a_fld_s
)brace
id|ni_port_header_a_fld_s
suffix:semicolon
DECL|typedef|ni_port_header_a_u_t
)brace
id|ni_port_header_a_u_t
suffix:semicolon
macro_line|#else
DECL|union|ni_port_header_a_u
r_typedef
r_union
id|ni_port_header_a_u
(brace
DECL|member|ni_port_header_a_regval
id|bdrkreg_t
id|ni_port_header_a_regval
suffix:semicolon
r_struct
(brace
DECL|member|pha_reserved
id|bdrkreg_t
id|pha_reserved
suffix:colon
l_int|2
suffix:semicolon
DECL|member|pha_address_b
id|bdrkreg_t
id|pha_address_b
suffix:colon
l_int|27
suffix:semicolon
DECL|member|pha_prexsel
id|bdrkreg_t
id|pha_prexsel
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pha_command
id|bdrkreg_t
id|pha_command
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pha_reserved_1
id|bdrkreg_t
id|pha_reserved_1
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pha_destination
id|bdrkreg_t
id|pha_destination
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pha_direction
id|bdrkreg_t
id|pha_direction
suffix:colon
l_int|4
suffix:semicolon
DECL|member|pha_age
id|bdrkreg_t
id|pha_age
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pha_v
id|bdrkreg_t
id|pha_v
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ni_port_header_a_fld_s
)brace
id|ni_port_header_a_fld_s
suffix:semicolon
DECL|typedef|ni_port_header_a_u_t
)brace
id|ni_port_header_a_u_t
suffix:semicolon
macro_line|#endif
macro_line|#ifdef LITTLE_ENDIAN
DECL|union|ni_port_header_b_u
r_typedef
r_union
id|ni_port_header_b_u
(brace
DECL|member|ni_port_header_b_regval
id|bdrkreg_t
id|ni_port_header_b_regval
suffix:semicolon
r_struct
(brace
DECL|member|phb_supplemental
id|bdrkreg_t
id|phb_supplemental
suffix:colon
l_int|11
suffix:semicolon
DECL|member|phb_reserved_2
id|bdrkreg_t
id|phb_reserved_2
suffix:colon
l_int|5
suffix:semicolon
DECL|member|phb_source
id|bdrkreg_t
id|phb_source
suffix:colon
l_int|11
suffix:semicolon
DECL|member|phb_reserved_1
id|bdrkreg_t
id|phb_reserved_1
suffix:colon
l_int|8
suffix:semicolon
DECL|member|phb_address_a
id|bdrkreg_t
id|phb_address_a
suffix:colon
l_int|3
suffix:semicolon
DECL|member|phb_address_c
id|bdrkreg_t
id|phb_address_c
suffix:colon
l_int|8
suffix:semicolon
DECL|member|phb_reserved
id|bdrkreg_t
id|phb_reserved
suffix:colon
l_int|18
suffix:semicolon
DECL|member|ni_port_header_b_fld_s
)brace
id|ni_port_header_b_fld_s
suffix:semicolon
DECL|typedef|ni_port_header_b_u_t
)brace
id|ni_port_header_b_u_t
suffix:semicolon
macro_line|#else
DECL|union|ni_port_header_b_u
r_typedef
r_union
id|ni_port_header_b_u
(brace
DECL|member|ni_port_header_b_regval
id|bdrkreg_t
id|ni_port_header_b_regval
suffix:semicolon
r_struct
(brace
DECL|member|phb_reserved
id|bdrkreg_t
id|phb_reserved
suffix:colon
l_int|18
suffix:semicolon
DECL|member|phb_address_c
id|bdrkreg_t
id|phb_address_c
suffix:colon
l_int|8
suffix:semicolon
DECL|member|phb_address_a
id|bdrkreg_t
id|phb_address_a
suffix:colon
l_int|3
suffix:semicolon
DECL|member|phb_reserved_1
id|bdrkreg_t
id|phb_reserved_1
suffix:colon
l_int|8
suffix:semicolon
DECL|member|phb_source
id|bdrkreg_t
id|phb_source
suffix:colon
l_int|11
suffix:semicolon
DECL|member|phb_reserved_2
id|bdrkreg_t
id|phb_reserved_2
suffix:colon
l_int|5
suffix:semicolon
DECL|member|phb_supplemental
id|bdrkreg_t
id|phb_supplemental
suffix:colon
l_int|11
suffix:semicolon
DECL|member|ni_port_header_b_fld_s
)brace
id|ni_port_header_b_fld_s
suffix:semicolon
DECL|typedef|ni_port_header_b_u_t
)brace
id|ni_port_header_b_u_t
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/* NI_RESET_ENABLE mask definitions */
DECL|macro|NRE_RESETOK
mdefine_line|#define NRE_RESETOK&t;&t;(UINT64_CAST 1)&t;/* Let LLP reset bedrock */
multiline_comment|/* NI PORT_ERRORS, Max number of RETRY_COUNT, Check Bit, and Sequence   */
multiline_comment|/* Number errors (8 bit counters that do not wrap).                     */
DECL|macro|NI_LLP_RETRY_MAX
mdefine_line|#define NI_LLP_RETRY_MAX        0xff
DECL|macro|NI_LLP_CB_MAX
mdefine_line|#define NI_LLP_CB_MAX           0xff
DECL|macro|NI_LLP_SN_MAX
mdefine_line|#define NI_LLP_SN_MAX           0xff
multiline_comment|/* NI_PORT_PARMS shift and mask definitions */
DECL|macro|NPP_VCH_ERR_EN_SHFT
mdefine_line|#define NPP_VCH_ERR_EN_SHFT&t;31
DECL|macro|NPP_VCH_ERR_EN_MASK
mdefine_line|#define NPP_VCH_ERR_EN_MASK&t;(0xf &lt;&lt; NPP_VCH_ERR_EN_SHFT)
DECL|macro|NPP_SQUASH_ERR_EN_SHFT
mdefine_line|#define NPP_SQUASH_ERR_EN_SHFT&t;30
DECL|macro|NPP_SQUASH_ERR_EN_MASK
mdefine_line|#define NPP_SQUASH_ERR_EN_MASK&t;(0x1 &lt;&lt; NPP_SQUASH_ERR_EN_SHFT)
DECL|macro|NPP_FIRST_ERR_EN_SHFT
mdefine_line|#define NPP_FIRST_ERR_EN_SHFT&t;29
DECL|macro|NPP_FIRST_ERR_EN_MASK
mdefine_line|#define NPP_FIRST_ERR_EN_MASK&t;(0x1 &lt;&lt; NPP_FIRST_ERR_EN_SHFT)
DECL|macro|NPP_D_AVAIL_SEL_SHFT
mdefine_line|#define NPP_D_AVAIL_SEL_SHFT&t;26
DECL|macro|NPP_D_AVAIL_SEL_MASK
mdefine_line|#define NPP_D_AVAIL_SEL_MASK&t;(0x3 &lt;&lt; NPP_D_AVAIL_SEL_SHFT)
DECL|macro|NPP_MAX_RETRY_SHFT
mdefine_line|#define NPP_MAX_RETRY_SHFT&t;16
DECL|macro|NPP_MAX_RETRY_MASK
mdefine_line|#define NPP_MAX_RETRY_MASK&t;(0x3ff &lt;&lt; NPP_MAX_RETRY_SHFT)
DECL|macro|NPP_NULL_TIMEOUT_SHFT
mdefine_line|#define NPP_NULL_TIMEOUT_SHFT&t;10
DECL|macro|NPP_NULL_TIMEOUT_MASK
mdefine_line|#define NPP_NULL_TIMEOUT_MASK&t;(0x3f &lt;&lt; NPP_NULL_TIMEOUT_SHFT)
DECL|macro|NPP_MAX_BURST_SHFT
mdefine_line|#define NPP_MAX_BURST_SHFT&t;0
DECL|macro|NPP_MAX_BURST_MASK
mdefine_line|#define NPP_MAX_BURST_MASK&t;(0x3ff &lt;&lt; NPP_MAX_BURST_SHFT)
DECL|macro|NPP_RESET_DEFAULTS
mdefine_line|#define NPP_RESET_DEFAULTS&t;(0xf &lt;&lt; NPP_VCH_ERR_EN_SHFT |   &bslash;&n;&t;&t;&t;&t; 0x1 &lt;&lt; NPP_FIRST_ERR_EN_SHFT | &bslash;&n;&t;&t;&t;&t; 0x3ff &lt;&lt; NPP_MAX_RETRY_SHFT |  &bslash;&n;&t;&t;&t;&t; 0x6 &lt;&lt; NPP_NULL_TIMEOUT_SHFT | &bslash;&n;&t;&t;&t;&t; 0x3f0 &lt;&lt; NPP_MAX_BURST_SHFT)
macro_line|#endif /* _ASM_IA64_SN_SN1_HUBNI_NEXT_H */
eof
