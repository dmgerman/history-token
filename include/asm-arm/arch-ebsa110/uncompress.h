multiline_comment|/*&n; *  linux/include/asm-arm/arch-ebsa110/uncompress.h&n; *&n; *  Copyright (C) 1996,1997,1998 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
multiline_comment|/*&n; * This does not append a newline&n; */
DECL|function|putstr
r_static
r_void
id|putstr
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_int
r_int
id|tmp1
comma
id|tmp2
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldrb&t;%0, [%2], #1&bslash;n&quot;
l_string|&quot;&t;teq&t;%0, #0&bslash;n&quot;
l_string|&quot;&t;beq&t;3f&bslash;n&quot;
l_string|&quot;1:&t;strb&t;%0, [%3]&bslash;n&quot;
l_string|&quot;2:&t;ldrb&t;%1, [%3, #0x14]&bslash;n&quot;
l_string|&quot;&t;and&t;%1, %1, #0x60&bslash;n&quot;
l_string|&quot;&t;teq&t;%1, #0x60&bslash;n&quot;
l_string|&quot;&t;bne&t;2b&bslash;n&quot;
l_string|&quot;&t;teq&t;%0, #&squot;&bslash;n&squot;&bslash;n&quot;
l_string|&quot;&t;moveq&t;%0, #&squot;&bslash;r&squot;&bslash;n&quot;
l_string|&quot;&t;beq&t;1b&bslash;n&quot;
l_string|&quot;&t;ldrb&t;%0, [%2], #1&bslash;n&quot;
l_string|&quot;&t;teq&t;%0, #0&bslash;n&quot;
l_string|&quot;&t;bne&t;1b&bslash;n&quot;
l_string|&quot;3:&t;ldrb&t;%1, [%3, #0x14]&bslash;n&quot;
l_string|&quot;&t;and&t;%1, %1, #0x60&bslash;n&quot;
l_string|&quot;&t;teq&t;%1, #0x60&bslash;n&quot;
l_string|&quot;&t;bne&t;3b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp2
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|s
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0xf0000be0
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * nothing to do&n; */
DECL|macro|arch_decomp_setup
mdefine_line|#define arch_decomp_setup()
DECL|macro|arch_decomp_wdog
mdefine_line|#define arch_decomp_wdog()
eof
