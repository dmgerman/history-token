multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2001 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SN1_HUBLB_NEXT_H
DECL|macro|_ASM_IA64_SN_SN1_HUBLB_NEXT_H
mdefine_line|#define _ASM_IA64_SN_SN1_HUBLB_NEXT_H
multiline_comment|/**********************************************************************&n;&n; This contains some mask and shift values for LB defined as required&n; for compatibility.&n;&n; **********************************************************************/
DECL|macro|LRI_SYSTEM_SIZE_SHFT
mdefine_line|#define LRI_SYSTEM_SIZE_SHFT        46
DECL|macro|LRI_SYSTEM_SIZE_MASK
mdefine_line|#define LRI_SYSTEM_SIZE_MASK        (UINT64_CAST 0x3 &lt;&lt; LRI_SYSTEM_SIZE_SHFT)
DECL|macro|LRI_NODEID_SHFT
mdefine_line|#define LRI_NODEID_SHFT        32
DECL|macro|LRI_NODEID_MASK
mdefine_line|#define LRI_NODEID_MASK        (UINT64_CAST 0xff &lt;&lt; LRI_NODEID_SHFT)/* Node ID    */
DECL|macro|LRI_CHIPID_SHFT
mdefine_line|#define LRI_CHIPID_SHFT&t;&t;12
DECL|macro|LRI_CHIPID_MASK
mdefine_line|#define LRI_CHIPID_MASK&t;&t;(UINT64_CAST 0xffff &lt;&lt; LRI_CHIPID_SHFT) /* should be 0x3012 */
DECL|macro|LRI_REV_SHFT
mdefine_line|#define LRI_REV_SHFT        28
DECL|macro|LRI_REV_MASK
mdefine_line|#define LRI_REV_MASK        (UINT64_CAST 0xf &lt;&lt; LRI_REV_SHFT)/* Chip revision    */
multiline_comment|/* Values for LRI_SYSTEM_SIZE */
DECL|macro|SYSTEM_SIZE_INVALID
mdefine_line|#define SYSTEM_SIZE_INVALID&t;0x3
DECL|macro|SYSTEM_SIZE_NMODE
mdefine_line|#define SYSTEM_SIZE_NMODE&t;0x2
DECL|macro|SYSTEM_SIZE_COARSE
mdefine_line|#define SYSTEM_SIZE_COARSE &t;0x1
DECL|macro|SYSTEM_SIZE_SMALL
mdefine_line|#define SYSTEM_SIZE_SMALL&t;0x0
multiline_comment|/* In fine mode, each node is a region.  In coarse mode, there are&n; * 2 nodes per region.  In N-mode, there are 4 nodes per region. */
DECL|macro|NASID_TO_FINEREG_SHFT
mdefine_line|#define NASID_TO_FINEREG_SHFT   0
DECL|macro|NASID_TO_COARSEREG_SHFT
mdefine_line|#define NASID_TO_COARSEREG_SHFT 1
DECL|macro|NASID_TO_NMODEREG_SHFT
mdefine_line|#define NASID_TO_NMODEREG_SHFT  2
DECL|macro|LR_LOCALRESET
mdefine_line|#define LR_LOCALRESET               (UINT64_CAST 1)
multiline_comment|/*&n; * LB_VECTOR_PARMS mask and shift definitions.&n; * TYPE may be any of the first four PIOTYPEs defined under NI_VECTOR_STATUS.&n; */
DECL|macro|LVP_BUSY
mdefine_line|#define LVP_BUSY&t;&t;(UINT64_CAST 1 &lt;&lt; 63)
DECL|macro|LVP_PIOID_SHFT
mdefine_line|#define LVP_PIOID_SHFT          40
DECL|macro|LVP_PIOID_MASK
mdefine_line|#define LVP_PIOID_MASK          (UINT64_CAST 0x7ff &lt;&lt; 40)
DECL|macro|LVP_WRITEID_SHFT
mdefine_line|#define LVP_WRITEID_SHFT        32
DECL|macro|LVP_WRITEID_MASK
mdefine_line|#define LVP_WRITEID_MASK        (UINT64_CAST 0xff &lt;&lt; 32)
DECL|macro|LVP_ADDRESS_MASK
mdefine_line|#define LVP_ADDRESS_MASK        (UINT64_CAST 0xfffff8)   /* Bits 23:3        */
DECL|macro|LVP_TYPE_SHFT
mdefine_line|#define LVP_TYPE_SHFT           0
DECL|macro|LVP_TYPE_MASK
mdefine_line|#define LVP_TYPE_MASK           (UINT64_CAST 0x3)
multiline_comment|/* LB_VECTOR_STATUS mask and shift definitions */
DECL|macro|LVS_VALID
mdefine_line|#define LVS_VALID               (UINT64_CAST 1 &lt;&lt; 63)
DECL|macro|LVS_OVERRUN
mdefine_line|#define LVS_OVERRUN             (UINT64_CAST 1 &lt;&lt; 62)
DECL|macro|LVS_TARGET_SHFT
mdefine_line|#define LVS_TARGET_SHFT         51
DECL|macro|LVS_TARGET_MASK
mdefine_line|#define LVS_TARGET_MASK         (UINT64_CAST 0x7ff &lt;&lt; 51)
DECL|macro|LVS_PIOID_SHFT
mdefine_line|#define LVS_PIOID_SHFT          40
DECL|macro|LVS_PIOID_MASK
mdefine_line|#define LVS_PIOID_MASK          (UINT64_CAST 0x7ff &lt;&lt; 40)
DECL|macro|LVS_WRITEID_SHFT
mdefine_line|#define LVS_WRITEID_SHFT        32
DECL|macro|LVS_WRITEID_MASK
mdefine_line|#define LVS_WRITEID_MASK        (UINT64_CAST 0xff &lt;&lt; 32)
DECL|macro|LVS_ADDRESS_MASK
mdefine_line|#define LVS_ADDRESS_MASK        (UINT64_CAST 0xfffff8)   /* Bits 23:3     */
DECL|macro|LVS_TYPE_SHFT
mdefine_line|#define LVS_TYPE_SHFT           0
DECL|macro|LVS_TYPE_MASK
mdefine_line|#define LVS_TYPE_MASK           (UINT64_CAST 0x7)
DECL|macro|LVS_ERROR_MASK
mdefine_line|#define LVS_ERROR_MASK          (UINT64_CAST 0x4)  /* bit set means error */
multiline_comment|/* LB_RT_LOCAL_CTRL mask and shift definitions */
DECL|macro|LRLC_USE_INT_SHFT
mdefine_line|#define LRLC_USE_INT_SHFT       32
DECL|macro|LRLC_USE_INT_MASK
mdefine_line|#define LRLC_USE_INT_MASK       (UINT64_CAST 1 &lt;&lt; 32)
DECL|macro|LRLC_USE_INT
mdefine_line|#define LRLC_USE_INT            (UINT64_CAST 1 &lt;&lt; 32)
DECL|macro|LRLC_GCLK_SHFT
mdefine_line|#define LRLC_GCLK_SHFT          28
DECL|macro|LRLC_GCLK_MASK
mdefine_line|#define LRLC_GCLK_MASK          (UINT64_CAST 1 &lt;&lt; 28)
DECL|macro|LRLC_GCLK
mdefine_line|#define LRLC_GCLK               (UINT64_CAST 1 &lt;&lt; 28)
DECL|macro|LRLC_GCLK_COUNT_SHFT
mdefine_line|#define LRLC_GCLK_COUNT_SHFT    16
DECL|macro|LRLC_GCLK_COUNT_MASK
mdefine_line|#define LRLC_GCLK_COUNT_MASK    (UINT64_CAST 0x3ff &lt;&lt; 16)
DECL|macro|LRLC_MAX_COUNT_SHFT
mdefine_line|#define LRLC_MAX_COUNT_SHFT     4
DECL|macro|LRLC_MAX_COUNT_MASK
mdefine_line|#define LRLC_MAX_COUNT_MASK     (UINT64_CAST 0x3ff &lt;&lt; 4)
DECL|macro|LRLC_GCLK_EN_SHFT
mdefine_line|#define LRLC_GCLK_EN_SHFT       0
DECL|macro|LRLC_GCLK_EN_MASK
mdefine_line|#define LRLC_GCLK_EN_MASK       (UINT64_CAST 1)
DECL|macro|LRLC_GCLK_EN
mdefine_line|#define LRLC_GCLK_EN            (UINT64_CAST 1)
multiline_comment|/* LB_NODES_ABSENT mask and shift definitions */
DECL|macro|LNA_VALID_SHFT
mdefine_line|#define LNA_VALID_SHFT&t;&t;15
DECL|macro|LNA_VALID_MASK
mdefine_line|#define LNA_VALID_MASK&t;&t;(UINT64_CAST 1 &lt;&lt; LNA_VALID_SHFT)
DECL|macro|LNA_VALID
mdefine_line|#define LNA_VALID&t;&t;(UINT64_CAST 1 &lt;&lt; LNA_VALID_SHFT)
DECL|macro|LNA_NODE_SHFT
mdefine_line|#define LNA_NODE_SHFT&t;&t;0
DECL|macro|LNA_NODE_MASK
mdefine_line|#define LNA_NODE_MASK&t;&t;(UINT64_CAST 0xff &lt;&lt; LNA_NODE_SHFT)
multiline_comment|/* LB_NODES_ABSENT has 4 identical sub-registers, on 16-bit boundaries */
DECL|macro|LNA_ENTRY_SHFT
mdefine_line|#define LNA_ENTRY_SHFT&t;&t;16
DECL|macro|LNA_MAX_ENTRIES
mdefine_line|#define LNA_MAX_ENTRIES&t;&t;4
DECL|macro|LNA_ADD
mdefine_line|#define LNA_ADD(_reg, _n)&t;((_reg) = (_reg) &lt;&lt; LNA_ENTRY_SHFT | &bslash;&n;&t;&t;&t;&t; &t;LNA_VALID | (_n) &lt;&lt; LNA_NODE_SHFT)
DECL|macro|PIOTYPE_READ
mdefine_line|#define  PIOTYPE_READ           0       /* VECTOR_PARMS and VECTOR_STATUS   */
DECL|macro|PIOTYPE_WRITE
mdefine_line|#define  PIOTYPE_WRITE          1       /* VECTOR_PARMS and VECTOR_STATUS   */
DECL|macro|PIOTYPE_UNDEFINED
mdefine_line|#define  PIOTYPE_UNDEFINED      2       /* VECTOR_PARMS and VECTOR_STATUS   */
multiline_comment|/* XXX IP35 doesn&squot;t support vector exchange:  scr. regs. do locks directly */
DECL|macro|PIOTYPE_EXCHANGE
mdefine_line|#define  PIOTYPE_EXCHANGE       3       /* VECTOR_PARMS and VECTOR_STATUS   */
DECL|macro|PIOTYPE_ADDR_ERR
mdefine_line|#define  PIOTYPE_ADDR_ERR       4       /* VECTOR_STATUS only               */
DECL|macro|PIOTYPE_CMD_ERR
mdefine_line|#define  PIOTYPE_CMD_ERR        5       /* VECTOR_STATUS only               */
DECL|macro|PIOTYPE_PROT_ERR
mdefine_line|#define  PIOTYPE_PROT_ERR       6       /* VECTOR_STATUS only               */
DECL|macro|PIOTYPE_UNKNOWN
mdefine_line|#define  PIOTYPE_UNKNOWN        7       /* VECTOR_STATUS only               */
macro_line|#endif /* _ASM_IA64_SN_SN1_HUBLB_NEXT_H */
eof
