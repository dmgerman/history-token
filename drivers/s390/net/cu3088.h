macro_line|#ifndef _CU3088_H
DECL|macro|_CU3088_H
mdefine_line|#define _CU3088_H
multiline_comment|/**&n; * Enum for classifying detected devices.&n; */
DECL|enum|channel_types
r_enum
id|channel_types
(brace
multiline_comment|/* Device is not a channel  */
DECL|enumerator|channel_type_none
id|channel_type_none
comma
multiline_comment|/* Device is a CTC/A */
DECL|enumerator|channel_type_parallel
id|channel_type_parallel
comma
multiline_comment|/* Device is a ESCON channel */
DECL|enumerator|channel_type_escon
id|channel_type_escon
comma
multiline_comment|/* Device is a FICON channel */
DECL|enumerator|channel_type_ficon
id|channel_type_ficon
comma
multiline_comment|/* Device is a P390 LCS card */
DECL|enumerator|channel_type_p390
id|channel_type_p390
comma
multiline_comment|/* Device is a OSA2 card */
DECL|enumerator|channel_type_osa2
id|channel_type_osa2
comma
multiline_comment|/* Device is a channel, but we don&squot;t know&n;&t; * anything about it */
DECL|enumerator|channel_type_unknown
id|channel_type_unknown
comma
multiline_comment|/* Device is an unsupported model */
DECL|enumerator|channel_type_unsupported
id|channel_type_unsupported
comma
multiline_comment|/* number of type entries */
DECL|enumerator|num_channel_types
id|num_channel_types
)brace
suffix:semicolon
r_extern
r_const
r_char
op_star
id|cu3088_type
(braket
id|num_channel_types
)braket
suffix:semicolon
r_extern
r_int
id|register_cu3088_discipline
c_func
(paren
r_struct
id|ccwgroup_driver
op_star
)paren
suffix:semicolon
r_extern
r_void
id|unregister_cu3088_discipline
c_func
(paren
r_struct
id|ccwgroup_driver
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
