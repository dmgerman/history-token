DECL|struct|cpu_model_info
r_struct
id|cpu_model_info
(brace
DECL|member|vendor
r_int
id|vendor
suffix:semicolon
DECL|member|family
r_int
id|family
suffix:semicolon
DECL|member|model_names
r_char
op_star
id|model_names
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* attempt to consolidate cpu attributes */
DECL|struct|cpu_dev
r_struct
id|cpu_dev
(brace
DECL|member|c_vendor
r_char
op_star
id|c_vendor
suffix:semicolon
multiline_comment|/* some have two possibilities for cpuid string */
DECL|member|c_ident
r_char
op_star
id|c_ident
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|c_models
r_struct
id|cpu_model_info
id|c_models
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|c_init
r_void
(paren
op_star
id|c_init
)paren
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
suffix:semicolon
DECL|member|c_identify
r_void
(paren
op_star
id|c_identify
)paren
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
suffix:semicolon
DECL|member|c_size_cache
r_int
r_int
(paren
op_star
id|c_size_cache
)paren
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
comma
r_int
r_int
id|size
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|cpu_dev
op_star
id|cpu_devs
(braket
id|X86_VENDOR_NUM
)braket
suffix:semicolon
r_extern
r_int
id|get_model_name
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
suffix:semicolon
r_extern
r_void
id|display_cacheinfo
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
suffix:semicolon
r_extern
r_void
id|generic_identify
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
suffix:semicolon
r_extern
r_int
id|have_cpuid_p
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|early_intel_workaround
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
suffix:semicolon
eof
