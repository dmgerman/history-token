macro_line|#include &lt;asm/addrspace.h&gt;
multiline_comment|/* Lasat 100&t;*/
DECL|macro|DS1603_REG_100
mdefine_line|#define DS1603_REG_100&t;&t;(KSEG1ADDR(0x1c810000))
DECL|macro|DS1603_RST_100
mdefine_line|#define DS1603_RST_100&t;&t;(1 &lt;&lt; 2)
DECL|macro|DS1603_CLK_100
mdefine_line|#define DS1603_CLK_100&t;&t;(1 &lt;&lt; 0)
DECL|macro|DS1603_DATA_SHIFT_100
mdefine_line|#define DS1603_DATA_SHIFT_100&t;1
DECL|macro|DS1603_DATA_100
mdefine_line|#define DS1603_DATA_100&t;&t;(1 &lt;&lt; DS1603_DATA_SHIFT_100)
multiline_comment|/* Lasat 200&t;*/
DECL|macro|DS1603_REG_200
mdefine_line|#define DS1603_REG_200&t;&t;(KSEG1ADDR(0x11000000))
DECL|macro|DS1603_RST_200
mdefine_line|#define DS1603_RST_200&t;&t;(1 &lt;&lt; 3)
DECL|macro|DS1603_CLK_200
mdefine_line|#define DS1603_CLK_200&t;&t;(1 &lt;&lt; 4)
DECL|macro|DS1603_DATA_200
mdefine_line|#define DS1603_DATA_200&t;&t;(1 &lt;&lt; 5)
DECL|macro|DS1603_DATA_REG_200
mdefine_line|#define DS1603_DATA_REG_200&t;&t;(DS1603_REG_200 + 0x10000)
DECL|macro|DS1603_DATA_READ_SHIFT_200
mdefine_line|#define DS1603_DATA_READ_SHIFT_200&t;9
DECL|macro|DS1603_DATA_READ_200
mdefine_line|#define DS1603_DATA_READ_200&t;(1 &lt;&lt; DS1603_DATA_READ_SHIFT_200)
eof
