multiline_comment|/* generated by Benny &n;   MODIFY ON YOUR OWN RISK */
macro_line|#ifndef __HEADER_cwcbinhack_H__
DECL|macro|__HEADER_cwcbinhack_H__
mdefine_line|#define __HEADER_cwcbinhack_H__
DECL|variable|cwcbinhack_symbols
r_static
id|symbol_entry_t
id|cwcbinhack_symbols
(braket
)braket
op_assign
(brace
(brace
l_int|0x02c8
comma
l_string|&quot;OVERLAYBEGINADDRESS&quot;
comma
l_int|0x00
)brace
comma
(brace
l_int|0x02c8
comma
l_string|&quot;MAGICSNOOPTASK&quot;
comma
l_int|0x03
)brace
comma
(brace
l_int|0x0308
comma
l_string|&quot;#CODE_END&quot;
comma
l_int|0x00
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* cwcbinhack symbols */
DECL|variable|cwcbinhack_code
r_static
id|u32
id|cwcbinhack_code
(braket
)braket
op_assign
(brace
multiline_comment|/* 0x02c8 */
l_int|0x0007bfb0
comma
l_int|0x000bc240
comma
l_int|0x00000c2e
comma
l_int|0x000c6084
comma
multiline_comment|/* 1 */
l_int|0x000b8630
comma
l_int|0x00001016
comma
l_int|0x00006408
comma
l_int|0x000efb84
comma
multiline_comment|/* 2 */
l_int|0x00016008
comma
l_int|0x00000000
comma
l_int|0x0001c088
comma
l_int|0x000c0000
comma
multiline_comment|/* 3 */
l_int|0x000fc908
comma
l_int|0x000e3392
comma
l_int|0x0005f488
comma
l_int|0x000efb84
comma
multiline_comment|/* 4 */
l_int|0x0001d402
comma
l_int|0x000b2e00
comma
l_int|0x0003d418
comma
l_int|0x00001000
comma
multiline_comment|/* 5 */
l_int|0x0008d574
comma
l_int|0x000c4293
comma
l_int|0x00065625
comma
l_int|0x000ea30e
comma
multiline_comment|/* 6 */
l_int|0x00096c01
comma
l_int|0x000c6f92
comma
l_int|0x0001a58a
comma
l_int|0x000c6085
comma
multiline_comment|/* 7 */
l_int|0x00002f43
comma
l_int|0x00000000
comma
l_int|0x000e03a0
comma
l_int|0x00001016
comma
multiline_comment|/* 8 */
l_int|0x0005e608
comma
l_int|0x000c0000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 9 */
l_int|0x000ca108
comma
l_int|0x000dcca1
comma
l_int|0x00003bac
comma
l_int|0x000c3205
comma
multiline_comment|/* 10 */
l_int|0x00073843
comma
l_int|0x00000000
comma
l_int|0x00010730
comma
l_int|0x00001017
comma
multiline_comment|/* 11 */
l_int|0x0001600a
comma
l_int|0x000c0000
comma
l_int|0x00057488
comma
l_int|0x00000000
comma
multiline_comment|/* 12 */
l_int|0x00000000
comma
l_int|0x000e5084
comma
l_int|0x00000000
comma
l_int|0x000eba44
comma
multiline_comment|/* 13 */
l_int|0x00087401
comma
l_int|0x000e4782
comma
l_int|0x00000734
comma
l_int|0x00001000
comma
multiline_comment|/* 14 */
l_int|0x00010705
comma
l_int|0x000a6880
comma
l_int|0x00006a88
comma
l_int|0x000c75c4
comma
multiline_comment|/* 15 */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/* 16 */
)brace
suffix:semicolon
multiline_comment|/* #CODE_END */
DECL|variable|cwcbinhack_segments
r_static
id|segment_desc_t
id|cwcbinhack_segments
(braket
)braket
op_assign
(brace
(brace
id|SEGTYPE_SP_PROGRAM
comma
l_int|0x00000000
comma
l_int|64
comma
id|cwcbinhack_code
)brace
comma
)brace
suffix:semicolon
DECL|variable|cwcbinhack_module
r_static
id|dsp_module_desc_t
id|cwcbinhack_module
op_assign
(brace
l_string|&quot;cwcbinhack&quot;
comma
(brace
l_int|3
comma
id|cwcbinhack_symbols
)brace
comma
l_int|1
comma
id|cwcbinhack_segments
comma
)brace
suffix:semicolon
macro_line|#endif /* __HEADER_cwcbinhack_H__ */
eof
