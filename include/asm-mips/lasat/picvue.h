multiline_comment|/* Lasat 100 */
DECL|macro|PVC_REG_100
mdefine_line|#define PVC_REG_100&t;&t;KSEG1ADDR(0x1c820000)
DECL|macro|PVC_DATA_SHIFT_100
mdefine_line|#define PVC_DATA_SHIFT_100&t;0
DECL|macro|PVC_DATA_M_100
mdefine_line|#define PVC_DATA_M_100&t;&t;0xFF
DECL|macro|PVC_E_100
mdefine_line|#define PVC_E_100&t;&t;(1 &lt;&lt; 8)
DECL|macro|PVC_RW_100
mdefine_line|#define PVC_RW_100&t;&t;(1 &lt;&lt; 9)
DECL|macro|PVC_RS_100
mdefine_line|#define PVC_RS_100&t;&t;(1 &lt;&lt; 10)
multiline_comment|/* Lasat 200 */
DECL|macro|PVC_REG_200
mdefine_line|#define PVC_REG_200&t;&t;KSEG1ADDR(0x11000000)
DECL|macro|PVC_DATA_SHIFT_200
mdefine_line|#define PVC_DATA_SHIFT_200&t;24
DECL|macro|PVC_DATA_M_200
mdefine_line|#define PVC_DATA_M_200&t;&t;(0xFF &lt;&lt; PVC_DATA_SHIFT_200)
DECL|macro|PVC_E_200
mdefine_line|#define PVC_E_200&t;&t;(1 &lt;&lt; 16)
DECL|macro|PVC_RW_200
mdefine_line|#define PVC_RW_200&t;&t;(1 &lt;&lt; 17)
DECL|macro|PVC_RS_200
mdefine_line|#define PVC_RS_200&t;&t;(1 &lt;&lt; 18)
eof
