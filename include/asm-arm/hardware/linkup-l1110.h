multiline_comment|/*&n;*&n;* Definitions for H3600 Handheld Computer&n;*&n;* Copyright 2001 Compaq Computer Corporation.&n;*&n;* Use consistent with the GNU GPL is permitted,&n;* provided that this copyright notice is&n;* preserved in its entirety in all copies and derived works.&n;*&n;* COMPAQ COMPUTER CORPORATION MAKES NO WARRANTIES, EXPRESSED OR IMPLIED,&n;* AS TO THE USEFULNESS OR CORRECTNESS OF THIS CODE OR ITS&n;* FITNESS FOR ANY PARTICULAR PURPOSE.&n;*&n;* Author: Jamey Hicks.&n;*&n;*/
multiline_comment|/* LinkUp Systems PCCard/CompactFlash Interface for SA-1100 */
multiline_comment|/* PC Card Status Register */
DECL|macro|LINKUP_PRS_S1
mdefine_line|#define LINKUP_PRS_S1&t;(1 &lt;&lt; 0) /* voltage control bits S1-S4 */
DECL|macro|LINKUP_PRS_S2
mdefine_line|#define LINKUP_PRS_S2&t;(1 &lt;&lt; 1)
DECL|macro|LINKUP_PRS_S3
mdefine_line|#define LINKUP_PRS_S3&t;(1 &lt;&lt; 2)
DECL|macro|LINKUP_PRS_S4
mdefine_line|#define LINKUP_PRS_S4&t;(1 &lt;&lt; 3)
DECL|macro|LINKUP_PRS_BVD1
mdefine_line|#define LINKUP_PRS_BVD1&t;(1 &lt;&lt; 4)
DECL|macro|LINKUP_PRS_BVD2
mdefine_line|#define LINKUP_PRS_BVD2&t;(1 &lt;&lt; 5)
DECL|macro|LINKUP_PRS_VS1
mdefine_line|#define LINKUP_PRS_VS1&t;(1 &lt;&lt; 6)
DECL|macro|LINKUP_PRS_VS2
mdefine_line|#define LINKUP_PRS_VS2&t;(1 &lt;&lt; 7)
DECL|macro|LINKUP_PRS_RDY
mdefine_line|#define LINKUP_PRS_RDY&t;(1 &lt;&lt; 8)
DECL|macro|LINKUP_PRS_CD1
mdefine_line|#define LINKUP_PRS_CD1&t;(1 &lt;&lt; 9)
DECL|macro|LINKUP_PRS_CD2
mdefine_line|#define LINKUP_PRS_CD2&t;(1 &lt;&lt; 10)
multiline_comment|/* PC Card Command Register */
DECL|macro|LINKUP_PRC_S1
mdefine_line|#define LINKUP_PRC_S1&t;(1 &lt;&lt; 0)
DECL|macro|LINKUP_PRC_S2
mdefine_line|#define LINKUP_PRC_S2&t;(1 &lt;&lt; 1)
DECL|macro|LINKUP_PRC_S3
mdefine_line|#define LINKUP_PRC_S3&t;(1 &lt;&lt; 2)
DECL|macro|LINKUP_PRC_S4
mdefine_line|#define LINKUP_PRC_S4&t;(1 &lt;&lt; 3)
DECL|macro|LINKUP_PRC_RESET
mdefine_line|#define LINKUP_PRC_RESET (1 &lt;&lt; 4)
DECL|macro|LINKUP_PRC_APOE
mdefine_line|#define LINKUP_PRC_APOE&t;(1 &lt;&lt; 5) /* Auto Power Off Enable: clears S1-S4 when either nCD goes high */
DECL|macro|LINKUP_PRC_CFE
mdefine_line|#define LINKUP_PRC_CFE&t;(1 &lt;&lt; 6) /* CompactFlash mode Enable: addresses A[10:0] only, A[25:11] high */
DECL|macro|LINKUP_PRC_SOE
mdefine_line|#define LINKUP_PRC_SOE&t;(1 &lt;&lt; 7) /* signal output driver enable */
DECL|macro|LINKUP_PRC_SSP
mdefine_line|#define LINKUP_PRC_SSP&t;(1 &lt;&lt; 8) /* sock select polarity: 0 for socket 0, 1 for socket 1 */
DECL|macro|LINKUP_PRC_MBZ
mdefine_line|#define LINKUP_PRC_MBZ&t;(1 &lt;&lt; 15) /* must be zero */
DECL|struct|linkup_l1110
r_struct
id|linkup_l1110
(brace
DECL|member|prc
r_volatile
r_int
id|prc
suffix:semicolon
)brace
suffix:semicolon
eof
