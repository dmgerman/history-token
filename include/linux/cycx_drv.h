multiline_comment|/*&n;* cycx_drv.h&t;CYCX Support Module.  Kernel API Definitions.&n;*&n;* Author:&t;Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n;*&n;* Copyright:&t;(c) 1998-2003 Arnaldo Carvalho de Melo&n;*&n;* Based on sdladrv.h by Gene Kozin &lt;genek@compuserve.com&gt;&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* 1999/10/23&t;acme&t;&t;cycxhw_t cleanup&n;* 1999/01/03&t;acme&t;&t;more judicious use of data types...&n;*&t;&t;&t;&t;uclong, ucchar, etc deleted, the u8, u16, u32&n;*&t;&t;&t;&t;types are the portable way to go.&n;* 1999/01/03&t;acme&t;&t;judicious use of data types... u16, u32, etc&n;* 1998/12/26&t;acme&t; &t;FIXED_BUFFERS, CONF_OFFSET,&n;*                               removal of cy_read{bwl}&n;* 1998/08/08&t;acme&t; &t;Initial version.&n;*/
macro_line|#ifndef&t;_CYCX_DRV_H
DECL|macro|_CYCX_DRV_H
mdefine_line|#define&t;_CYCX_DRV_H
DECL|macro|CYCX_WINDOWSIZE
mdefine_line|#define&t;CYCX_WINDOWSIZE&t;0x4000&t;/* default dual-port memory window size */
DECL|macro|GEN_CYCX_INTR
mdefine_line|#define&t;GEN_CYCX_INTR&t;0x02
DECL|macro|RST_ENABLE
mdefine_line|#define&t;RST_ENABLE&t;0x04
DECL|macro|START_CPU
mdefine_line|#define&t;START_CPU&t;0x06
DECL|macro|RST_DISABLE
mdefine_line|#define&t;RST_DISABLE&t;0x08
DECL|macro|FIXED_BUFFERS
mdefine_line|#define&t;FIXED_BUFFERS&t;0x08
DECL|macro|TEST_PATTERN
mdefine_line|#define&t;TEST_PATTERN&t;0xaa55
DECL|macro|CMD_OFFSET
mdefine_line|#define&t;CMD_OFFSET&t;0x20
DECL|macro|CONF_OFFSET
mdefine_line|#define CONF_OFFSET     0x0380
DECL|macro|RESET_OFFSET
mdefine_line|#define&t;RESET_OFFSET&t;0x3c00&t;/* For reset file load */
DECL|macro|DATA_OFFSET
mdefine_line|#define&t;DATA_OFFSET&t;0x0100&t;/* For code and data files load */
DECL|macro|START_OFFSET
mdefine_line|#define&t;START_OFFSET&t;0x3ff0&t;/* 80186 starts here */
multiline_comment|/**&n; *&t;struct cycx_hw - Adapter hardware configuration&n; *&t;@fwid - firmware ID&n; *&t;@irq - interrupt request level&n; *&t;@dpmbase - dual-port memory base&n; *&t;@dpmsize - dual-port memory size&n; *&t;@reserved - reserved for future use&n; */
DECL|struct|cycx_hw
r_struct
id|cycx_hw
(brace
DECL|member|fwid
id|u32
id|fwid
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|dpmbase
id|u32
id|dpmbase
suffix:semicolon
DECL|member|dpmsize
id|u32
id|dpmsize
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
(braket
l_int|5
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Function Prototypes */
r_extern
r_int
id|cycx_setup
c_func
(paren
r_struct
id|cycx_hw
op_star
id|hw
comma
r_void
op_star
id|sfm
comma
id|u32
id|len
)paren
suffix:semicolon
r_extern
r_int
id|cycx_down
c_func
(paren
r_struct
id|cycx_hw
op_star
id|hw
)paren
suffix:semicolon
r_extern
r_int
id|cycx_peek
c_func
(paren
r_struct
id|cycx_hw
op_star
id|hw
comma
id|u32
id|addr
comma
r_void
op_star
id|buf
comma
id|u32
id|len
)paren
suffix:semicolon
r_extern
r_int
id|cycx_poke
c_func
(paren
r_struct
id|cycx_hw
op_star
id|hw
comma
id|u32
id|addr
comma
r_void
op_star
id|buf
comma
id|u32
id|len
)paren
suffix:semicolon
r_extern
r_int
id|cycx_exec
c_func
(paren
id|u32
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|cycx_inten
c_func
(paren
r_struct
id|cycx_hw
op_star
id|hw
)paren
suffix:semicolon
r_extern
r_void
id|cycx_intr
c_func
(paren
r_struct
id|cycx_hw
op_star
id|hw
)paren
suffix:semicolon
macro_line|#endif&t;/* _CYCX_DRV_H */
eof
