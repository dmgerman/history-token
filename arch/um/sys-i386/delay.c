DECL|function|__delay
r_void
id|__delay
c_func
(paren
r_int
r_int
id|time
)paren
(brace
multiline_comment|/* Stolen from the i386 __loop_delay */
r_int
id|d0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;tjmp 1f&bslash;n&quot;
l_string|&quot;.align 16&bslash;n&quot;
l_string|&quot;1:&bslash;tjmp 2f&bslash;n&quot;
l_string|&quot;.align 16&bslash;n&quot;
l_string|&quot;2:&bslash;tdecl %0&bslash;n&bslash;tjns 2b&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|d0
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|time
)paren
)paren
suffix:semicolon
)brace
eof
