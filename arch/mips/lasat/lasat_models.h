multiline_comment|/*&n; * Model description tables&n; */
DECL|struct|product_info_t
r_typedef
r_struct
id|product_info_t
(brace
DECL|member|pi_name
r_const
r_char
op_star
id|pi_name
suffix:semicolon
DECL|member|pi_type
r_const
r_char
op_star
id|pi_type
suffix:semicolon
DECL|typedef|product_info_t
)brace
id|product_info_t
suffix:semicolon
DECL|struct|vendor_info_t
r_typedef
r_struct
id|vendor_info_t
(brace
DECL|member|vi_name
r_const
r_char
op_star
id|vi_name
suffix:semicolon
DECL|member|vi_product_info
r_const
id|product_info_t
op_star
id|vi_product_info
suffix:semicolon
DECL|typedef|vendor_info_t
)brace
id|vendor_info_t
suffix:semicolon
multiline_comment|/*&n; * Base models&n; */
DECL|variable|txt_base_models
r_static
r_const
r_char
op_star
r_const
id|txt_base_models
(braket
)braket
op_assign
(brace
l_string|&quot;MQ 2&quot;
comma
l_string|&quot;MQ Pro&quot;
comma
l_string|&quot;SP 25&quot;
comma
l_string|&quot;SP 50&quot;
comma
l_string|&quot;SP 100&quot;
comma
l_string|&quot;SP 5000&quot;
comma
l_string|&quot;SP 7000&quot;
comma
l_string|&quot;SP 1000&quot;
comma
l_string|&quot;Unknown&quot;
)brace
suffix:semicolon
DECL|macro|N_BASE_MODELS
mdefine_line|#define N_BASE_MODELS (sizeof(txt_base_models)/sizeof(char*)-1)
multiline_comment|/*&n; * Eicon Networks&n; */
DECL|variable|txt_en_mq
r_static
r_const
r_char
id|txt_en_mq
(braket
)braket
op_assign
l_string|&quot;Masquerade&quot;
suffix:semicolon
DECL|variable|txt_en_sp
r_static
r_const
r_char
id|txt_en_sp
(braket
)braket
op_assign
l_string|&quot;Safepipe&quot;
suffix:semicolon
DECL|variable|product_info_eicon
r_static
r_const
id|product_info_t
id|product_info_eicon
(braket
)braket
op_assign
(brace
(brace
id|txt_en_mq
comma
l_string|&quot;II&quot;
)brace
comma
multiline_comment|/*  0 */
(brace
id|txt_en_mq
comma
l_string|&quot;Pro&quot;
)brace
comma
multiline_comment|/*  1 */
(brace
id|txt_en_sp
comma
l_string|&quot;25&quot;
)brace
comma
multiline_comment|/*  2 */
(brace
id|txt_en_sp
comma
l_string|&quot;50&quot;
)brace
comma
multiline_comment|/*  3 */
(brace
id|txt_en_sp
comma
l_string|&quot;100&quot;
)brace
comma
multiline_comment|/*  4 */
(brace
id|txt_en_sp
comma
l_string|&quot;5000&quot;
)brace
comma
multiline_comment|/*  5 */
(brace
id|txt_en_sp
comma
l_string|&quot;7000&quot;
)brace
comma
multiline_comment|/*  6 */
(brace
id|txt_en_sp
comma
l_string|&quot;30&quot;
)brace
comma
multiline_comment|/*  7 */
(brace
id|txt_en_sp
comma
l_string|&quot;5100&quot;
)brace
comma
multiline_comment|/*  8 */
(brace
id|txt_en_sp
comma
l_string|&quot;7100&quot;
)brace
comma
multiline_comment|/*  9 */
(brace
id|txt_en_sp
comma
l_string|&quot;1110&quot;
)brace
comma
multiline_comment|/* 10 */
(brace
id|txt_en_sp
comma
l_string|&quot;3020&quot;
)brace
comma
multiline_comment|/* 11 */
(brace
id|txt_en_sp
comma
l_string|&quot;3030&quot;
)brace
comma
multiline_comment|/* 12 */
(brace
id|txt_en_sp
comma
l_string|&quot;5020&quot;
)brace
comma
multiline_comment|/* 13 */
(brace
id|txt_en_sp
comma
l_string|&quot;5030&quot;
)brace
comma
multiline_comment|/* 14 */
(brace
id|txt_en_sp
comma
l_string|&quot;1120&quot;
)brace
comma
multiline_comment|/* 15 */
(brace
id|txt_en_sp
comma
l_string|&quot;1130&quot;
)brace
comma
multiline_comment|/* 16 */
(brace
id|txt_en_sp
comma
l_string|&quot;6010&quot;
)brace
comma
multiline_comment|/* 17 */
(brace
id|txt_en_sp
comma
l_string|&quot;6110&quot;
)brace
comma
multiline_comment|/* 18 */
(brace
id|txt_en_sp
comma
l_string|&quot;6210&quot;
)brace
comma
multiline_comment|/* 19 */
(brace
id|txt_en_sp
comma
l_string|&quot;1020&quot;
)brace
comma
multiline_comment|/* 20 */
(brace
id|txt_en_sp
comma
l_string|&quot;1040&quot;
)brace
comma
multiline_comment|/* 21 */
(brace
id|txt_en_sp
comma
l_string|&quot;1050&quot;
)brace
comma
multiline_comment|/* 22 */
(brace
id|txt_en_sp
comma
l_string|&quot;1060&quot;
)brace
comma
multiline_comment|/* 23 */
)brace
suffix:semicolon
DECL|macro|N_PRIDS
mdefine_line|#define N_PRIDS (sizeof(product_info_eicon)/sizeof(product_info_t))
multiline_comment|/*&n; * The vendor table&n; */
DECL|variable|vendor_info_table
r_static
id|vendor_info_t
r_const
id|vendor_info_table
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;Eicon Networks&quot;
comma
id|product_info_eicon
)brace
comma
)brace
suffix:semicolon
DECL|macro|N_VENDORS
mdefine_line|#define N_VENDORS (sizeof(vendor_info_table)/sizeof(vendor_info_t))
eof
