multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Derived from IRIX &lt;sys/SN/SN0/hubni.h&gt;, Revision 1.27.&n; *&n; * Copyright (C) 1992-1997, 1999 Silicon Graphics, Inc.&n; * Copyright (C) 1999 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_SGI_SN0_HUBNI_H
DECL|macro|_ASM_SGI_SN0_HUBNI_H
mdefine_line|#define _ASM_SGI_SN0_HUBNI_H
macro_line|#ifdef _LANGUAGE_C
macro_line|#include &lt;linux/types.h&gt;
macro_line|#endif
multiline_comment|/*&n; * Hub Network Interface registers&n; *&n; * All registers in this file are subject to change until Hub chip tapeout.&n; */
DECL|macro|NI_BASE
mdefine_line|#define NI_BASE&t;&t;&t;0x600000
DECL|macro|NI_BASE_TABLES
mdefine_line|#define NI_BASE_TABLES&t;&t;0x630000
DECL|macro|NI_STATUS_REV_ID
mdefine_line|#define NI_STATUS_REV_ID&t;0x600000 /* Hub network status, rev, and ID */
DECL|macro|NI_PORT_RESET
mdefine_line|#define NI_PORT_RESET&t;&t;0x600008 /* Reset the network interface     */
DECL|macro|NI_PROTECTION
mdefine_line|#define NI_PROTECTION&t;&t;0x600010 /* NI register access permissions  */
DECL|macro|NI_GLOBAL_PARMS
mdefine_line|#define NI_GLOBAL_PARMS&t;&t;0x600018 /* LLP parameters &t;&t;    */
DECL|macro|NI_SCRATCH_REG0
mdefine_line|#define NI_SCRATCH_REG0&t;&t;0x600100 /* Scratch register 0 (64 bits)    */
DECL|macro|NI_SCRATCH_REG1
mdefine_line|#define NI_SCRATCH_REG1&t;&t;0x600108 /* Scratch register 1 (64 bits)    */
DECL|macro|NI_DIAG_PARMS
mdefine_line|#define NI_DIAG_PARMS&t;&t;0x600110 /* Parameters for diags&t;    */
DECL|macro|NI_VECTOR_PARMS
mdefine_line|#define NI_VECTOR_PARMS&t;&t;0x600200 /* Vector PIO routing parameters   */
DECL|macro|NI_VECTOR
mdefine_line|#define NI_VECTOR&t;&t;0x600208 /* Vector PIO route &t;&t;    */
DECL|macro|NI_VECTOR_DATA
mdefine_line|#define NI_VECTOR_DATA&t;&t;0x600210 /* Vector PIO data &t;&t;    */
DECL|macro|NI_VECTOR_STATUS
mdefine_line|#define NI_VECTOR_STATUS&t;0x600300 /* Vector PIO return status &t;    */
DECL|macro|NI_RETURN_VECTOR
mdefine_line|#define NI_RETURN_VECTOR&t;0x600308 /* Vector PIO return vector &t;    */
DECL|macro|NI_VECTOR_READ_DATA
mdefine_line|#define NI_VECTOR_READ_DATA&t;0x600310 /* Vector PIO read data &t;    */
DECL|macro|NI_VECTOR_CLEAR
mdefine_line|#define NI_VECTOR_CLEAR&t;&t;0x600380 /* Vector PIO read &amp; clear status  */
DECL|macro|NI_IO_PROTECT
mdefine_line|#define NI_IO_PROTECT&t;&t;0x600400 /* PIO protection bits &t;    */
DECL|macro|NI_IO_PROT_OVRRD
mdefine_line|#define NI_IO_PROT_OVRRD&t;0x600408 /* PIO protection bit override     */
DECL|macro|NI_AGE_CPU0_MEMORY
mdefine_line|#define NI_AGE_CPU0_MEMORY&t;0x600500 /* CPU 0 memory age control &t;    */
DECL|macro|NI_AGE_CPU0_PIO
mdefine_line|#define NI_AGE_CPU0_PIO&t;&t;0x600508 /* CPU 0 PIO age control &t;    */
DECL|macro|NI_AGE_CPU1_MEMORY
mdefine_line|#define NI_AGE_CPU1_MEMORY&t;0x600510 /* CPU 1 memory age control &t;    */
DECL|macro|NI_AGE_CPU1_PIO
mdefine_line|#define NI_AGE_CPU1_PIO&t;&t;0x600518 /* CPU 1 PIO age control &t;    */
DECL|macro|NI_AGE_GBR_MEMORY
mdefine_line|#define NI_AGE_GBR_MEMORY&t;0x600520 /* GBR memory age control &t;    */
DECL|macro|NI_AGE_GBR_PIO
mdefine_line|#define NI_AGE_GBR_PIO&t;&t;0x600528 /* GBR PIO age control &t;    */
DECL|macro|NI_AGE_IO_MEMORY
mdefine_line|#define NI_AGE_IO_MEMORY&t;0x600530 /* IO memory age control &t;    */
DECL|macro|NI_AGE_IO_PIO
mdefine_line|#define NI_AGE_IO_PIO&t;&t;0x600538 /* IO PIO age control &t;&t;    */
DECL|macro|NI_AGE_REG_MIN
mdefine_line|#define NI_AGE_REG_MIN&t;&t;NI_AGE_CPU0_MEMORY
DECL|macro|NI_AGE_REG_MAX
mdefine_line|#define NI_AGE_REG_MAX&t;&t;NI_AGE_IO_PIO
DECL|macro|NI_PORT_PARMS
mdefine_line|#define NI_PORT_PARMS&t;&t;0x608000 /* LLP Parameters &t;&t;    */
DECL|macro|NI_PORT_ERROR
mdefine_line|#define NI_PORT_ERROR&t;&t;0x608008 /* LLP Errors &t;&t;&t;    */
DECL|macro|NI_PORT_ERROR_CLEAR
mdefine_line|#define NI_PORT_ERROR_CLEAR&t;0x608088 /* Clear the error bits &t;    */
DECL|macro|NI_META_TABLE0
mdefine_line|#define NI_META_TABLE0&t;&t;0x638000 /* First meta routing table entry  */
DECL|macro|NI_META_TABLE
mdefine_line|#define NI_META_TABLE(_x)&t;(NI_META_TABLE0 + (8 * (_x)))
DECL|macro|NI_META_ENTRIES
mdefine_line|#define NI_META_ENTRIES&t;&t;32
DECL|macro|NI_LOCAL_TABLE0
mdefine_line|#define NI_LOCAL_TABLE0&t;&t;0x638100 /* First local routing table entry */
DECL|macro|NI_LOCAL_TABLE
mdefine_line|#define NI_LOCAL_TABLE(_x)&t;(NI_LOCAL_TABLE0 + (8 * (_x)))
DECL|macro|NI_LOCAL_ENTRIES
mdefine_line|#define NI_LOCAL_ENTRIES&t;16
multiline_comment|/*&n; * NI_STATUS_REV_ID mask and shift definitions&n; * Have to use UINT64_CAST instead of &squot;L&squot; suffix, for assembler.&n; */
DECL|macro|NSRI_8BITMODE_SHFT
mdefine_line|#define NSRI_8BITMODE_SHFT&t;30
DECL|macro|NSRI_8BITMODE_MASK
mdefine_line|#define NSRI_8BITMODE_MASK&t;(UINT64_CAST 0x1 &lt;&lt; 30)
DECL|macro|NSRI_LINKUP_SHFT
mdefine_line|#define NSRI_LINKUP_SHFT&t;29
DECL|macro|NSRI_LINKUP_MASK
mdefine_line|#define NSRI_LINKUP_MASK&t;(UINT64_CAST 0x1 &lt;&lt; 29)
DECL|macro|NSRI_DOWNREASON_SHFT
mdefine_line|#define NSRI_DOWNREASON_SHFT&t;28&t;&t;/* 0=failed, 1=never came   */
DECL|macro|NSRI_DOWNREASON_MASK
mdefine_line|#define NSRI_DOWNREASON_MASK&t;(UINT64_CAST 0x1 &lt;&lt; 28)&t;/*    out of reset. */
DECL|macro|NSRI_MORENODES_SHFT
mdefine_line|#define NSRI_MORENODES_SHFT&t;18
DECL|macro|NSRI_MORENODES_MASK
mdefine_line|#define NSRI_MORENODES_MASK&t;(UINT64_CAST 1 &lt;&lt; 18)&t;/* Max. # of nodes  */
DECL|macro|MORE_MEMORY
mdefine_line|#define&t; MORE_MEMORY&t;&t;0
DECL|macro|MORE_NODES
mdefine_line|#define&t; MORE_NODES&t;&t;1
DECL|macro|NSRI_REGIONSIZE_SHFT
mdefine_line|#define NSRI_REGIONSIZE_SHFT&t;17
DECL|macro|NSRI_REGIONSIZE_MASK
mdefine_line|#define NSRI_REGIONSIZE_MASK&t;(UINT64_CAST 1 &lt;&lt; 17)&t;/* Granularity &t;    */
DECL|macro|REGIONSIZE_FINE
mdefine_line|#define&t; REGIONSIZE_FINE&t;1
DECL|macro|REGIONSIZE_COARSE
mdefine_line|#define&t; REGIONSIZE_COARSE&t;0
DECL|macro|NSRI_NODEID_SHFT
mdefine_line|#define NSRI_NODEID_SHFT&t;8
DECL|macro|NSRI_NODEID_MASK
mdefine_line|#define NSRI_NODEID_MASK&t;(UINT64_CAST 0x1ff &lt;&lt; 8)/* Node (Hub) ID    */
DECL|macro|NSRI_REV_SHFT
mdefine_line|#define NSRI_REV_SHFT&t;&t;4
DECL|macro|NSRI_REV_MASK
mdefine_line|#define NSRI_REV_MASK&t;&t;(UINT64_CAST 0xf &lt;&lt; 4)&t;/* Chip Revision    */
DECL|macro|NSRI_CHIPID_SHFT
mdefine_line|#define NSRI_CHIPID_SHFT&t;0
DECL|macro|NSRI_CHIPID_MASK
mdefine_line|#define NSRI_CHIPID_MASK&t;(UINT64_CAST 0xf)&t;/* Chip type ID     */
multiline_comment|/*&n; * In fine mode, each node is a region.  In coarse mode, there are&n; * eight nodes per region.&n; */
DECL|macro|NASID_TO_FINEREG_SHFT
mdefine_line|#define NASID_TO_FINEREG_SHFT&t;0
DECL|macro|NASID_TO_COARSEREG_SHFT
mdefine_line|#define NASID_TO_COARSEREG_SHFT&t;3
multiline_comment|/* NI_PORT_RESET mask definitions */
DECL|macro|NPR_PORTRESET
mdefine_line|#define NPR_PORTRESET&t;&t;(UINT64_CAST 1 &lt;&lt; 7)&t;/* Send warm reset  */
DECL|macro|NPR_LINKRESET
mdefine_line|#define NPR_LINKRESET&t;&t;(UINT64_CAST 1 &lt;&lt; 1)&t;/* Send link reset  */
DECL|macro|NPR_LOCALRESET
mdefine_line|#define NPR_LOCALRESET&t;&t;(UINT64_CAST 1)&t;&t;/* Reset entire hub */
multiline_comment|/* NI_PROTECTION mask and shift definitions */
DECL|macro|NPROT_RESETOK
mdefine_line|#define NPROT_RESETOK&t;&t;(UINT64_CAST 1)
multiline_comment|/* NI_GLOBAL_PARMS mask and shift definitions */
DECL|macro|NGP_MAXRETRY_SHFT
mdefine_line|#define NGP_MAXRETRY_SHFT&t;48&t;&t;/* Maximum retries  &t;    */
DECL|macro|NGP_MAXRETRY_MASK
mdefine_line|#define NGP_MAXRETRY_MASK&t;(UINT64_CAST 0x3ff &lt;&lt; 48)
DECL|macro|NGP_TAILTOWRAP_SHFT
mdefine_line|#define NGP_TAILTOWRAP_SHFT&t;32&t;&t;/* Tail timeout wrap &t;    */
DECL|macro|NGP_TAILTOWRAP_MASK
mdefine_line|#define NGP_TAILTOWRAP_MASK&t;(UINT64_CAST 0xffff &lt;&lt; 32)
DECL|macro|NGP_CREDITTOVAL_SHFT
mdefine_line|#define NGP_CREDITTOVAL_SHFT&t;16&t;&t;/* Tail timeout wrap &t;    */
DECL|macro|NGP_CREDITTOVAL_MASK
mdefine_line|#define NGP_CREDITTOVAL_MASK&t;(UINT64_CAST 0xf &lt;&lt; 16)
DECL|macro|NGP_TAILTOVAL_SHFT
mdefine_line|#define NGP_TAILTOVAL_SHFT&t;4&t;&t;/* Tail timeout value &t;    */
DECL|macro|NGP_TAILTOVAL_MASK
mdefine_line|#define NGP_TAILTOVAL_MASK&t;(UINT64_CAST 0xf &lt;&lt; 4)
multiline_comment|/* NI_DIAG_PARMS mask and shift definitions */
DECL|macro|NDP_PORTTORESET
mdefine_line|#define NDP_PORTTORESET&t;&t;(UINT64_CAST 1 &lt;&lt; 18)&t;/* Port tmout reset */
DECL|macro|NDP_LLP8BITMODE
mdefine_line|#define NDP_LLP8BITMODE&t;&t;(UINT64_CAST 1 &lt;&lt; 12)&t;/* LLP 8-bit mode   */
DECL|macro|NDP_PORTDISABLE
mdefine_line|#define NDP_PORTDISABLE&t;&t;(UINT64_CAST 1 &lt;&lt;  6)&t;/* Port disable     */
DECL|macro|NDP_SENDERROR
mdefine_line|#define NDP_SENDERROR&t;&t;(UINT64_CAST 1)&t;&t;/* Send data error  */
multiline_comment|/*&n; * NI_VECTOR_PARMS mask and shift definitions.&n; * TYPE may be any of the first four PIOTYPEs defined under NI_VECTOR_STATUS.&n; */
DECL|macro|NVP_PIOID_SHFT
mdefine_line|#define NVP_PIOID_SHFT&t;&t;40
DECL|macro|NVP_PIOID_MASK
mdefine_line|#define NVP_PIOID_MASK&t;&t;(UINT64_CAST 0x3ff &lt;&lt; 40)
DECL|macro|NVP_WRITEID_SHFT
mdefine_line|#define NVP_WRITEID_SHFT&t;32
DECL|macro|NVP_WRITEID_MASK
mdefine_line|#define NVP_WRITEID_MASK&t;(UINT64_CAST 0xff &lt;&lt; 32)
DECL|macro|NVP_ADDRESS_MASK
mdefine_line|#define NVP_ADDRESS_MASK&t;(UINT64_CAST 0xffff8)&t;/* Bits 19:3 &t;    */
DECL|macro|NVP_TYPE_SHFT
mdefine_line|#define NVP_TYPE_SHFT&t;&t;0
DECL|macro|NVP_TYPE_MASK
mdefine_line|#define NVP_TYPE_MASK&t;&t;(UINT64_CAST 0x3)
multiline_comment|/* NI_VECTOR_STATUS mask and shift definitions */
DECL|macro|NVS_VALID
mdefine_line|#define NVS_VALID&t;&t;(UINT64_CAST 1 &lt;&lt; 63)
DECL|macro|NVS_OVERRUN
mdefine_line|#define NVS_OVERRUN&t;&t;(UINT64_CAST 1 &lt;&lt; 62)
DECL|macro|NVS_TARGET_SHFT
mdefine_line|#define NVS_TARGET_SHFT&t;&t;51
DECL|macro|NVS_TARGET_MASK
mdefine_line|#define NVS_TARGET_MASK&t;&t;(UINT64_CAST 0x3ff &lt;&lt; 51)
DECL|macro|NVS_PIOID_SHFT
mdefine_line|#define NVS_PIOID_SHFT&t;&t;40
DECL|macro|NVS_PIOID_MASK
mdefine_line|#define NVS_PIOID_MASK&t;&t;(UINT64_CAST 0x3ff &lt;&lt; 40)
DECL|macro|NVS_WRITEID_SHFT
mdefine_line|#define NVS_WRITEID_SHFT&t;32
DECL|macro|NVS_WRITEID_MASK
mdefine_line|#define NVS_WRITEID_MASK&t;(UINT64_CAST 0xff &lt;&lt; 32)
DECL|macro|NVS_ADDRESS_MASK
mdefine_line|#define NVS_ADDRESS_MASK&t;(UINT64_CAST 0xfffffff8)   /* Bits 31:3     */
DECL|macro|NVS_TYPE_SHFT
mdefine_line|#define NVS_TYPE_SHFT&t;&t;0
DECL|macro|NVS_TYPE_MASK
mdefine_line|#define NVS_TYPE_MASK&t;&t;(UINT64_CAST 0x7)
DECL|macro|NVS_ERROR_MASK
mdefine_line|#define NVS_ERROR_MASK&t;&t;(UINT64_CAST 0x4)  /* bit set means error */
DECL|macro|PIOTYPE_READ
mdefine_line|#define&t; PIOTYPE_READ&t;&t;0&t;/* VECTOR_PARMS and VECTOR_STATUS   */
DECL|macro|PIOTYPE_WRITE
mdefine_line|#define&t; PIOTYPE_WRITE&t;&t;1&t;/* VECTOR_PARMS and VECTOR_STATUS   */
DECL|macro|PIOTYPE_UNDEFINED
mdefine_line|#define&t; PIOTYPE_UNDEFINED&t;2&t;/* VECTOR_PARMS and VECTOR_STATUS   */
DECL|macro|PIOTYPE_EXCHANGE
mdefine_line|#define&t; PIOTYPE_EXCHANGE&t;3&t;/* VECTOR_PARMS and VECTOR_STATUS   */
DECL|macro|PIOTYPE_ADDR_ERR
mdefine_line|#define&t; PIOTYPE_ADDR_ERR&t;4&t;/* VECTOR_STATUS only &t;&t;    */
DECL|macro|PIOTYPE_CMD_ERR
mdefine_line|#define&t; PIOTYPE_CMD_ERR&t;5&t;/* VECTOR_STATUS only &t;&t;    */
DECL|macro|PIOTYPE_PROT_ERR
mdefine_line|#define&t; PIOTYPE_PROT_ERR&t;6&t;/* VECTOR_STATUS only &t;&t;    */
DECL|macro|PIOTYPE_UNKNOWN
mdefine_line|#define&t; PIOTYPE_UNKNOWN&t;7&t;/* VECTOR_STATUS only &t;&t;    */
multiline_comment|/* NI_AGE_XXX mask and shift definitions */
DECL|macro|NAGE_VCH_SHFT
mdefine_line|#define NAGE_VCH_SHFT&t;&t;10
DECL|macro|NAGE_VCH_MASK
mdefine_line|#define NAGE_VCH_MASK&t;&t;(UINT64_CAST 3 &lt;&lt; 10)
DECL|macro|NAGE_CC_SHFT
mdefine_line|#define NAGE_CC_SHFT&t;&t;8
DECL|macro|NAGE_CC_MASK
mdefine_line|#define NAGE_CC_MASK&t;&t;(UINT64_CAST 3 &lt;&lt; 8)
DECL|macro|NAGE_AGE_SHFT
mdefine_line|#define NAGE_AGE_SHFT&t;&t;0
DECL|macro|NAGE_AGE_MASK
mdefine_line|#define NAGE_AGE_MASK&t;&t;(UINT64_CAST 0xff)
DECL|macro|NAGE_MASK
mdefine_line|#define NAGE_MASK&t;&t;(NAGE_VCH_MASK | NAGE_CC_MASK | NAGE_AGE_MASK)
DECL|macro|VCHANNEL_A
mdefine_line|#define&t; VCHANNEL_A&t;&t;0
DECL|macro|VCHANNEL_B
mdefine_line|#define&t; VCHANNEL_B&t;&t;1
DECL|macro|VCHANNEL_ANY
mdefine_line|#define&t; VCHANNEL_ANY&t;&t;2
multiline_comment|/* NI_PORT_PARMS mask and shift definitions */
DECL|macro|NPP_NULLTO_SHFT
mdefine_line|#define NPP_NULLTO_SHFT&t;&t;10
DECL|macro|NPP_NULLTO_MASK
mdefine_line|#define NPP_NULLTO_MASK&t;&t;(UINT64_CAST 0x3f &lt;&lt; 16)
DECL|macro|NPP_MAXBURST_SHFT
mdefine_line|#define NPP_MAXBURST_SHFT&t;0
DECL|macro|NPP_MAXBURST_MASK
mdefine_line|#define NPP_MAXBURST_MASK&t;(UINT64_CAST 0x3ff)
DECL|macro|NPP_RESET_DFLT_HUB20
mdefine_line|#define NPP_RESET_DFLT_HUB20&t;((UINT64_CAST 1&t;    &lt;&lt; NPP_NULLTO_SHFT) | &bslash;&n;&t;&t;&t;&t; (UINT64_CAST 0x3f0 &lt;&lt; NPP_MAXBURST_SHFT))
DECL|macro|NPP_RESET_DEFAULTS
mdefine_line|#define NPP_RESET_DEFAULTS&t;((UINT64_CAST 6&t;    &lt;&lt; NPP_NULLTO_SHFT) | &bslash;&n;&t;&t;&t;&t; (UINT64_CAST 0x3f0 &lt;&lt; NPP_MAXBURST_SHFT))
multiline_comment|/* NI_PORT_ERROR mask and shift definitions */
DECL|macro|NPE_LINKRESET
mdefine_line|#define NPE_LINKRESET&t;&t;(UINT64_CAST 1 &lt;&lt; 37)
DECL|macro|NPE_INTERNALERROR
mdefine_line|#define NPE_INTERNALERROR&t;(UINT64_CAST 1 &lt;&lt; 36)
DECL|macro|NPE_BADMESSAGE
mdefine_line|#define NPE_BADMESSAGE&t;&t;(UINT64_CAST 1 &lt;&lt; 35)
DECL|macro|NPE_BADDEST
mdefine_line|#define NPE_BADDEST&t;&t;(UINT64_CAST 1 &lt;&lt; 34)
DECL|macro|NPE_FIFOOVERFLOW
mdefine_line|#define NPE_FIFOOVERFLOW&t;(UINT64_CAST 1 &lt;&lt; 33)
DECL|macro|NPE_CREDITTO_SHFT
mdefine_line|#define NPE_CREDITTO_SHFT&t;28
DECL|macro|NPE_CREDITTO_MASK
mdefine_line|#define NPE_CREDITTO_MASK&t;(UINT64_CAST 0xf &lt;&lt; 28)
DECL|macro|NPE_TAILTO_SHFT
mdefine_line|#define NPE_TAILTO_SHFT&t;&t;24
DECL|macro|NPE_TAILTO_MASK
mdefine_line|#define NPE_TAILTO_MASK&t;&t;(UINT64_CAST 0xf &lt;&lt; 24)
DECL|macro|NPE_RETRYCOUNT_SHFT
mdefine_line|#define NPE_RETRYCOUNT_SHFT&t;16
DECL|macro|NPE_RETRYCOUNT_MASK
mdefine_line|#define NPE_RETRYCOUNT_MASK&t;(UINT64_CAST 0xff &lt;&lt; 16)
DECL|macro|NPE_CBERRCOUNT_SHFT
mdefine_line|#define NPE_CBERRCOUNT_SHFT&t;8
DECL|macro|NPE_CBERRCOUNT_MASK
mdefine_line|#define NPE_CBERRCOUNT_MASK&t;(UINT64_CAST 0xff &lt;&lt; 8)
DECL|macro|NPE_SNERRCOUNT_SHFT
mdefine_line|#define NPE_SNERRCOUNT_SHFT&t;0
DECL|macro|NPE_SNERRCOUNT_MASK
mdefine_line|#define NPE_SNERRCOUNT_MASK&t;(UINT64_CAST 0xff &lt;&lt; 0)
DECL|macro|NPE_MASK
mdefine_line|#define NPE_MASK&t;&t;0x3effffffff
DECL|macro|NPE_COUNT_MAX
mdefine_line|#define NPE_COUNT_MAX&t;&t;0xff
DECL|macro|NPE_FATAL_ERRORS
mdefine_line|#define NPE_FATAL_ERRORS&t;(NPE_LINKRESET | NPE_INTERNALERROR |&t;&bslash;&n;&t;&t;&t;&t; NPE_BADMESSAGE | NPE_BADDEST |&t;&t;&bslash;&n;&t;&t;&t;&t; NPE_FIFOOVERFLOW | NPE_CREDITTO_MASK |&t;&bslash;&n;&t;&t;&t;&t; NPE_TAILTO_MASK)
multiline_comment|/* NI_META_TABLE mask and shift definitions */
DECL|macro|NMT_EXIT_PORT_MASK
mdefine_line|#define NMT_EXIT_PORT_MASK (UINT64_CAST 0xf)
multiline_comment|/* NI_LOCAL_TABLE mask and shift definitions */
DECL|macro|NLT_EXIT_PORT_MASK
mdefine_line|#define NLT_EXIT_PORT_MASK (UINT64_CAST 0xf)
macro_line|#ifdef _LANGUAGE_C
DECL|union|hubni_port_error_u
r_typedef
r_union
id|hubni_port_error_u
(brace
DECL|member|nipe_reg_value
id|u64
id|nipe_reg_value
suffix:semicolon
r_struct
(brace
DECL|member|nipe_rsvd
id|u64
id|nipe_rsvd
suffix:colon
l_int|26
comma
multiline_comment|/* unused */
DECL|member|nipe_lnk_reset
id|nipe_lnk_reset
suffix:colon
l_int|1
comma
multiline_comment|/* link reset */
DECL|member|nipe_intl_err
id|nipe_intl_err
suffix:colon
l_int|1
comma
multiline_comment|/* internal error */
DECL|member|nipe_bad_msg
id|nipe_bad_msg
suffix:colon
l_int|1
comma
multiline_comment|/* bad message */
DECL|member|nipe_bad_dest
id|nipe_bad_dest
suffix:colon
l_int|1
comma
multiline_comment|/* bad dest&t;*/
DECL|member|nipe_fifo_ovfl
id|nipe_fifo_ovfl
suffix:colon
l_int|1
comma
multiline_comment|/* fifo overflow */
DECL|member|nipe_rsvd1
id|nipe_rsvd1
suffix:colon
l_int|1
comma
multiline_comment|/* unused */
DECL|member|nipe_credit_to
id|nipe_credit_to
suffix:colon
l_int|4
comma
multiline_comment|/* credit timeout */
DECL|member|nipe_tail_to
id|nipe_tail_to
suffix:colon
l_int|4
comma
multiline_comment|/* tail timeout */
DECL|member|nipe_retry_cnt
id|nipe_retry_cnt
suffix:colon
l_int|8
comma
multiline_comment|/* retry error count */
DECL|member|nipe_cb_cnt
id|nipe_cb_cnt
suffix:colon
l_int|8
comma
multiline_comment|/* checkbit error count */
DECL|member|nipe_sn_cnt
id|nipe_sn_cnt
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* sequence number count */
DECL|member|nipe_fields_s
)brace
id|nipe_fields_s
suffix:semicolon
DECL|typedef|hubni_port_error_t
)brace
id|hubni_port_error_t
suffix:semicolon
DECL|macro|NI_LLP_RETRY_MAX
mdefine_line|#define NI_LLP_RETRY_MAX&t;0xff
DECL|macro|NI_LLP_CB_MAX
mdefine_line|#define NI_LLP_CB_MAX&t;&t;0xff
DECL|macro|NI_LLP_SN_MAX
mdefine_line|#define NI_LLP_SN_MAX&t;&t;0xff
macro_line|#endif /* LANGUAGE_C */
macro_line|#endif /* _ASM_SGI_SN0_HUBNI_H */
eof
