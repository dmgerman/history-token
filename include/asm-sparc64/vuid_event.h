multiline_comment|/* SunOS Virtual User Input Device (VUID) compatibility */
DECL|struct|firm_event
r_typedef
r_struct
id|firm_event
(brace
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
multiline_comment|/* tag for this event */
DECL|member|pair_type
r_int
r_char
id|pair_type
suffix:semicolon
multiline_comment|/* unused by X11 */
DECL|member|pair
r_int
r_char
id|pair
suffix:semicolon
multiline_comment|/* unused by X11 */
DECL|member|value
r_int
id|value
suffix:semicolon
multiline_comment|/* VKEY_UP, VKEY_DOWN or delta */
DECL|member|time
r_struct
id|timeval
id|time
suffix:semicolon
DECL|typedef|Firm_event
)brace
id|Firm_event
suffix:semicolon
r_enum
(brace
DECL|enumerator|FE_PAIR_NONE
id|FE_PAIR_NONE
comma
DECL|enumerator|FE_PAIR_SET
id|FE_PAIR_SET
comma
DECL|enumerator|FE_PAIR_DELTA
id|FE_PAIR_DELTA
comma
DECL|enumerator|FE_PAIR_ABSOLUTE
id|FE_PAIR_ABSOLUTE
)brace
suffix:semicolon
multiline_comment|/* VUID stream formats */
DECL|macro|VUID_NATIVE
mdefine_line|#define VUID_NATIVE     0&t;/* Native byte stream format */
DECL|macro|VUID_FIRM_EVENT
mdefine_line|#define VUID_FIRM_EVENT 1&t;/* send firm_event structures */
multiline_comment|/* ioctls */
multiline_comment|/* Set input device byte stream format (any of VUID_{NATIVE,FIRM_EVENT}) */
DECL|macro|VUIDSFORMAT
mdefine_line|#define VUIDSFORMAT   _IOW(&squot;v&squot;, 1, int)
multiline_comment|/* Retrieve input device byte stream format */
DECL|macro|VUIDGFORMAT
mdefine_line|#define VUIDGFORMAT   _IOR(&squot;v&squot;, 2, int)
multiline_comment|/* Possible tag values */
multiline_comment|/*    mouse buttons: */
DECL|macro|MS_LEFT
mdefine_line|#define MS_LEFT         0x7f20
DECL|macro|MS_MIDDLE
mdefine_line|#define MS_MIDDLE       0x7f21
DECL|macro|MS_RIGHT
mdefine_line|#define MS_RIGHT        0x7f22
multiline_comment|/*    motion: */
DECL|macro|LOC_X_DELTA
mdefine_line|#define LOC_X_DELTA     0x7f80
DECL|macro|LOC_Y_DELTA
mdefine_line|#define LOC_Y_DELTA     0x7f81
DECL|macro|LOC_X_ABSOLUTE
mdefine_line|#define LOC_X_ABSOLUTE  0x7f82  /* X compat, unsupported */
DECL|macro|LOC_Y_ABSOLUTE
mdefine_line|#define LOC_Y_ABSOLUTE  0x7f83  /* X compat, unsupported */
DECL|macro|VKEY_UP
mdefine_line|#define VKEY_UP   0
DECL|macro|VKEY_DOWN
mdefine_line|#define VKEY_DOWN 1
eof
