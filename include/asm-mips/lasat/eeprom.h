macro_line|#include &lt;asm/addrspace.h&gt;
multiline_comment|/* lasat 100 */
DECL|macro|AT93C_REG_100
mdefine_line|#define AT93C_REG_100               KSEG1ADDR(0x1c810000)
DECL|macro|AT93C_RDATA_REG_100
mdefine_line|#define AT93C_RDATA_REG_100         AT93C_REG_100
DECL|macro|AT93C_RDATA_SHIFT_100
mdefine_line|#define AT93C_RDATA_SHIFT_100       4
DECL|macro|AT93C_WDATA_SHIFT_100
mdefine_line|#define AT93C_WDATA_SHIFT_100       4
DECL|macro|AT93C_CS_M_100
mdefine_line|#define AT93C_CS_M_100              ( 1 &lt;&lt; 5 )
DECL|macro|AT93C_CLK_M_100
mdefine_line|#define AT93C_CLK_M_100             ( 1 &lt;&lt; 3 )
multiline_comment|/* lasat 200 */
DECL|macro|AT93C_REG_200
mdefine_line|#define AT93C_REG_200&t;&t;KSEG1ADDR(0x11000000)
DECL|macro|AT93C_RDATA_REG_200
mdefine_line|#define AT93C_RDATA_REG_200&t;(AT93C_REG_200+0x10000)
DECL|macro|AT93C_RDATA_SHIFT_200
mdefine_line|#define AT93C_RDATA_SHIFT_200&t;8
DECL|macro|AT93C_WDATA_SHIFT_200
mdefine_line|#define AT93C_WDATA_SHIFT_200&t;2
DECL|macro|AT93C_CS_M_200
mdefine_line|#define AT93C_CS_M_200&t;&t;( 1 &lt;&lt; 0 )
DECL|macro|AT93C_CLK_M_200
mdefine_line|#define AT93C_CLK_M_200&t;&t;( 1 &lt;&lt; 1 )
eof
