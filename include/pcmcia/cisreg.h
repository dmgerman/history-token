multiline_comment|/*&n; * cisreg.h 1.17 2000/06/12 21:55:41&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_CISREG_H
DECL|macro|_LINUX_CISREG_H
mdefine_line|#define _LINUX_CISREG_H
multiline_comment|/*&n; * Offsets from ConfigBase for CIS registers&n; */
DECL|macro|CISREG_COR
mdefine_line|#define CISREG_COR&t;&t;0x00
DECL|macro|CISREG_CCSR
mdefine_line|#define CISREG_CCSR&t;&t;0x02
DECL|macro|CISREG_PRR
mdefine_line|#define CISREG_PRR&t;&t;0x04
DECL|macro|CISREG_SCR
mdefine_line|#define CISREG_SCR&t;&t;0x06
DECL|macro|CISREG_ESR
mdefine_line|#define CISREG_ESR&t;&t;0x08
DECL|macro|CISREG_IOBASE_0
mdefine_line|#define CISREG_IOBASE_0&t;&t;0x0a
DECL|macro|CISREG_IOBASE_1
mdefine_line|#define CISREG_IOBASE_1&t;&t;0x0c
DECL|macro|CISREG_IOBASE_2
mdefine_line|#define CISREG_IOBASE_2&t;&t;0x0e
DECL|macro|CISREG_IOBASE_3
mdefine_line|#define CISREG_IOBASE_3&t;&t;0x10
DECL|macro|CISREG_IOSIZE
mdefine_line|#define CISREG_IOSIZE&t;&t;0x12
multiline_comment|/*&n; * Configuration Option Register&n; */
DECL|macro|COR_CONFIG_MASK
mdefine_line|#define COR_CONFIG_MASK&t;&t;0x3f
DECL|macro|COR_MFC_CONFIG_MASK
mdefine_line|#define COR_MFC_CONFIG_MASK&t;0x38
DECL|macro|COR_FUNC_ENA
mdefine_line|#define COR_FUNC_ENA&t;&t;0x01
DECL|macro|COR_ADDR_DECODE
mdefine_line|#define COR_ADDR_DECODE&t;&t;0x02
DECL|macro|COR_IREQ_ENA
mdefine_line|#define COR_IREQ_ENA&t;&t;0x04
DECL|macro|COR_LEVEL_REQ
mdefine_line|#define COR_LEVEL_REQ&t;&t;0x40
DECL|macro|COR_SOFT_RESET
mdefine_line|#define COR_SOFT_RESET&t;&t;0x80
multiline_comment|/*&n; * Card Configuration and Status Register&n; */
DECL|macro|CCSR_INTR_ACK
mdefine_line|#define CCSR_INTR_ACK&t;&t;0x01
DECL|macro|CCSR_INTR_PENDING
mdefine_line|#define CCSR_INTR_PENDING&t;0x02
DECL|macro|CCSR_POWER_DOWN
mdefine_line|#define CCSR_POWER_DOWN&t;&t;0x04
DECL|macro|CCSR_AUDIO_ENA
mdefine_line|#define CCSR_AUDIO_ENA&t;&t;0x08
DECL|macro|CCSR_IOIS8
mdefine_line|#define CCSR_IOIS8&t;&t;0x20
DECL|macro|CCSR_SIGCHG_ENA
mdefine_line|#define CCSR_SIGCHG_ENA&t;&t;0x40
DECL|macro|CCSR_CHANGED
mdefine_line|#define CCSR_CHANGED&t;&t;0x80
multiline_comment|/*&n; * Pin Replacement Register&n; */
DECL|macro|PRR_WP_STATUS
mdefine_line|#define PRR_WP_STATUS&t;&t;0x01
DECL|macro|PRR_READY_STATUS
mdefine_line|#define PRR_READY_STATUS&t;0x02
DECL|macro|PRR_BVD2_STATUS
mdefine_line|#define PRR_BVD2_STATUS&t;&t;0x04
DECL|macro|PRR_BVD1_STATUS
mdefine_line|#define PRR_BVD1_STATUS&t;&t;0x08
DECL|macro|PRR_WP_EVENT
mdefine_line|#define PRR_WP_EVENT&t;&t;0x10
DECL|macro|PRR_READY_EVENT
mdefine_line|#define PRR_READY_EVENT&t;&t;0x20
DECL|macro|PRR_BVD2_EVENT
mdefine_line|#define PRR_BVD2_EVENT&t;&t;0x40
DECL|macro|PRR_BVD1_EVENT
mdefine_line|#define PRR_BVD1_EVENT&t;&t;0x80
multiline_comment|/*&n; * Socket and Copy Register&n; */
DECL|macro|SCR_SOCKET_NUM
mdefine_line|#define SCR_SOCKET_NUM&t;&t;0x0f
DECL|macro|SCR_COPY_NUM
mdefine_line|#define SCR_COPY_NUM&t;&t;0x70
multiline_comment|/*&n; * Extended Status Register&n; */
DECL|macro|ESR_REQ_ATTN_ENA
mdefine_line|#define ESR_REQ_ATTN_ENA&t;0x01
DECL|macro|ESR_REQ_ATTN
mdefine_line|#define ESR_REQ_ATTN&t;&t;0x10
multiline_comment|/*&n; * CardBus Function Status Registers&n; */
DECL|macro|CBFN_EVENT
mdefine_line|#define CBFN_EVENT&t;&t;0x00
DECL|macro|CBFN_MASK
mdefine_line|#define CBFN_MASK&t;&t;0x04
DECL|macro|CBFN_STATE
mdefine_line|#define CBFN_STATE&t;&t;0x08
DECL|macro|CBFN_FORCE
mdefine_line|#define CBFN_FORCE&t;&t;0x0c
multiline_comment|/*&n; * These apply to all the CardBus function registers&n; */
DECL|macro|CBFN_WP
mdefine_line|#define CBFN_WP&t;&t;&t;0x0001
DECL|macro|CBFN_READY
mdefine_line|#define CBFN_READY&t;&t;0x0002
DECL|macro|CBFN_BVD2
mdefine_line|#define CBFN_BVD2&t;&t;0x0004
DECL|macro|CBFN_BVD1
mdefine_line|#define CBFN_BVD1&t;&t;0x0008
DECL|macro|CBFN_GWAKE
mdefine_line|#define CBFN_GWAKE&t;&t;0x0010
DECL|macro|CBFN_INTR
mdefine_line|#define CBFN_INTR&t;&t;0x8000
multiline_comment|/*&n; * Extra bits in the Function Event Mask Register&n; */
DECL|macro|FEMR_BAM_ENA
mdefine_line|#define FEMR_BAM_ENA&t;&t;0x0020
DECL|macro|FEMR_PWM_ENA
mdefine_line|#define FEMR_PWM_ENA&t;&t;0x0040
DECL|macro|FEMR_WKUP_MASK
mdefine_line|#define FEMR_WKUP_MASK&t;&t;0x4000
multiline_comment|/*&n; * Indirect Addressing Registers for Zoomed Video: these are addresses&n; * in common memory space&n; */
DECL|macro|CISREG_ICTRL0
mdefine_line|#define CISREG_ICTRL0&t;&t;0x02&t;/* control registers */
DECL|macro|CISREG_ICTRL1
mdefine_line|#define CISREG_ICTRL1&t;&t;0x03
DECL|macro|CISREG_IADDR0
mdefine_line|#define CISREG_IADDR0&t;&t;0x04&t;/* address registers */
DECL|macro|CISREG_IADDR1
mdefine_line|#define CISREG_IADDR1&t;&t;0x05
DECL|macro|CISREG_IADDR2
mdefine_line|#define CISREG_IADDR2&t;&t;0x06
DECL|macro|CISREG_IADDR3
mdefine_line|#define CISREG_IADDR3&t;&t;0x07
DECL|macro|CISREG_IDATA0
mdefine_line|#define CISREG_IDATA0&t;&t;0x08&t;/* data registers */
DECL|macro|CISREG_IDATA1
mdefine_line|#define CISREG_IDATA1&t;&t;0x09
DECL|macro|ICTRL0_COMMON
mdefine_line|#define ICTRL0_COMMON&t;&t;0x01
DECL|macro|ICTRL0_AUTOINC
mdefine_line|#define ICTRL0_AUTOINC&t;&t;0x02
DECL|macro|ICTRL0_BYTEGRAN
mdefine_line|#define ICTRL0_BYTEGRAN&t;&t;0x04
macro_line|#endif /* _LINUX_CISREG_H */
eof
