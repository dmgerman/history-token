multiline_comment|/*&n; * consolemap.h&n; *&n; * Interface between console.c, selection.c  and consolemap.c&n; */
DECL|macro|LAT1_MAP
mdefine_line|#define LAT1_MAP 0
DECL|macro|GRAF_MAP
mdefine_line|#define GRAF_MAP 1
DECL|macro|IBMPC_MAP
mdefine_line|#define IBMPC_MAP 2
DECL|macro|USER_MAP
mdefine_line|#define USER_MAP 3
r_struct
id|vc_data
suffix:semicolon
r_extern
r_int
r_char
id|inverse_translate
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|glyph
)paren
suffix:semicolon
r_extern
r_int
r_int
op_star
id|set_translate
c_func
(paren
r_int
id|m
comma
r_int
id|currcons
)paren
suffix:semicolon
r_extern
r_int
id|conv_uni_to_pc
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|ucs
)paren
suffix:semicolon
eof
