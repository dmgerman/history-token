multiline_comment|/*&n; * File:&t;mca_drv.h&n; * Purpose:&t;Define helpers for Generic MCA handling&n; *&n; * Copyright (C) 2004 FUJITSU LIMITED&n; * Copyright (C) Hidetoshi Seto (seto.hidetoshi@jp.fujitsu.com)&n; */
multiline_comment|/*&n; * Processor error section: &n; *&n; *  +-sal_log_processor_info_t *info-------------+&n; *  | sal_log_section_hdr_t header;              |&n; *  | ...                                        |&n; *  | sal_log_mod_error_info_t info[0];          |&n; *  +-+----------------+-------------------------+&n; *    | CACHE_CHECK    |  ^ num_cache_check v&n; *    +----------------+&n; *    | TLB_CHECK      |  ^ num_tlb_check v&n; *    +----------------+&n; *    | BUS_CHECK      |  ^ num_bus_check v&n; *    +----------------+&n; *    | REG_FILE_CHECK |  ^ num_reg_file_check v&n; *    +----------------+&n; *    | MS_CHECK       |  ^ num_ms_check v&n; *  +-struct cpuid_info *id----------------------+&n; *  | regs[5];                                   |&n; *  | reserved;                                  |&n; *  +-sal_processor_static_info_t *regs----------+&n; *  | valid;                                     |&n; *  | ...                                        |&n; *  | fr[128];                                   |&n; *  +--------------------------------------------+&n; */
multiline_comment|/* peidx: index of processor error section */
DECL|struct|peidx_table
r_typedef
r_struct
id|peidx_table
(brace
DECL|member|info
id|sal_log_processor_info_t
op_star
id|info
suffix:semicolon
DECL|member|id
r_struct
id|sal_cpuid_info
op_star
id|id
suffix:semicolon
DECL|member|regs
id|sal_processor_static_info_t
op_star
id|regs
suffix:semicolon
DECL|typedef|peidx_table_t
)brace
id|peidx_table_t
suffix:semicolon
DECL|macro|peidx_head
mdefine_line|#define peidx_head(p)   (((p)-&gt;info))
DECL|macro|peidx_mid
mdefine_line|#define peidx_mid(p)    (((p)-&gt;id))
DECL|macro|peidx_bottom
mdefine_line|#define peidx_bottom(p) (((p)-&gt;regs))
DECL|macro|peidx_psp
mdefine_line|#define peidx_psp(p)           (&amp;(peidx_head(p)-&gt;proc_state_parameter))
DECL|macro|peidx_field_valid
mdefine_line|#define peidx_field_valid(p)   (&amp;(peidx_head(p)-&gt;valid))
DECL|macro|peidx_minstate_area
mdefine_line|#define peidx_minstate_area(p) (&amp;(peidx_bottom(p)-&gt;min_state_area))
DECL|macro|peidx_cache_check_num
mdefine_line|#define peidx_cache_check_num(p)    (peidx_head(p)-&gt;valid.num_cache_check)
DECL|macro|peidx_tlb_check_num
mdefine_line|#define peidx_tlb_check_num(p)      (peidx_head(p)-&gt;valid.num_tlb_check)
DECL|macro|peidx_bus_check_num
mdefine_line|#define peidx_bus_check_num(p)      (peidx_head(p)-&gt;valid.num_bus_check)
DECL|macro|peidx_reg_file_check_num
mdefine_line|#define peidx_reg_file_check_num(p) (peidx_head(p)-&gt;valid.num_reg_file_check)
DECL|macro|peidx_ms_check_num
mdefine_line|#define peidx_ms_check_num(p)       (peidx_head(p)-&gt;valid.num_ms_check)
DECL|macro|peidx_cache_check_idx
mdefine_line|#define peidx_cache_check_idx(p, n)    (n)
DECL|macro|peidx_tlb_check_idx
mdefine_line|#define peidx_tlb_check_idx(p, n)      (peidx_cache_check_idx(p, peidx_cache_check_num(p)) + n)
DECL|macro|peidx_bus_check_idx
mdefine_line|#define peidx_bus_check_idx(p, n)      (peidx_tlb_check_idx(p, peidx_tlb_check_num(p)) + n)
DECL|macro|peidx_reg_file_check_idx
mdefine_line|#define peidx_reg_file_check_idx(p, n) (peidx_bus_check_idx(p, peidx_bus_check_num(p)) + n)
DECL|macro|peidx_ms_check_idx
mdefine_line|#define peidx_ms_check_idx(p, n)       (peidx_reg_file_check_idx(p, peidx_reg_file_check_num(p)) + n)
DECL|macro|peidx_mod_error_info
mdefine_line|#define peidx_mod_error_info(p, name, n) &bslash;&n;({&t;int __idx = peidx_##name##_idx(p, n); &bslash;&n;&t;sal_log_mod_error_info_t *__ret = NULL; &bslash;&n;&t;if (peidx_##name##_num(p) &gt; n) /*BUG*/ &bslash;&n;&t;&t;__ret = &amp;(peidx_head(p)-&gt;info[__idx]); &bslash;&n;&t;__ret; })
DECL|macro|peidx_cache_check
mdefine_line|#define peidx_cache_check(p, n)    peidx_mod_error_info(p, cache_check, n)
DECL|macro|peidx_tlb_check
mdefine_line|#define peidx_tlb_check(p, n)      peidx_mod_error_info(p, tlb_check, n)
DECL|macro|peidx_bus_check
mdefine_line|#define peidx_bus_check(p, n)      peidx_mod_error_info(p, bus_check, n)
DECL|macro|peidx_reg_file_check
mdefine_line|#define peidx_reg_file_check(p, n) peidx_mod_error_info(p, reg_file_check, n)
DECL|macro|peidx_ms_check
mdefine_line|#define peidx_ms_check(p, n)       peidx_mod_error_info(p, ms_check, n)
DECL|macro|peidx_check_info
mdefine_line|#define peidx_check_info(proc, name, n) &bslash;&n;({ &bslash;&n;&t;sal_log_mod_error_info_t *__info = peidx_mod_error_info(proc, name, n);&bslash;&n;&t;u64 __temp = __info &amp;&amp; __info-&gt;valid.check_info &bslash;&n;&t;&t;? __info-&gt;check_info : 0; &bslash;&n;&t;__temp; })
multiline_comment|/* slidx: index of SAL log error record */
DECL|struct|slidx_list
r_typedef
r_struct
id|slidx_list
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|hdr
id|sal_log_section_hdr_t
op_star
id|hdr
suffix:semicolon
DECL|typedef|slidx_list_t
)brace
id|slidx_list_t
suffix:semicolon
DECL|struct|slidx_table
r_typedef
r_struct
id|slidx_table
(brace
DECL|member|header
id|sal_log_record_header_t
op_star
id|header
suffix:semicolon
DECL|member|n_sections
r_int
id|n_sections
suffix:semicolon
multiline_comment|/* # of section headers */
DECL|member|proc_err
r_struct
id|list_head
id|proc_err
suffix:semicolon
DECL|member|mem_dev_err
r_struct
id|list_head
id|mem_dev_err
suffix:semicolon
DECL|member|sel_dev_err
r_struct
id|list_head
id|sel_dev_err
suffix:semicolon
DECL|member|pci_bus_err
r_struct
id|list_head
id|pci_bus_err
suffix:semicolon
DECL|member|smbios_dev_err
r_struct
id|list_head
id|smbios_dev_err
suffix:semicolon
DECL|member|pci_comp_err
r_struct
id|list_head
id|pci_comp_err
suffix:semicolon
DECL|member|plat_specific_err
r_struct
id|list_head
id|plat_specific_err
suffix:semicolon
DECL|member|host_ctlr_err
r_struct
id|list_head
id|host_ctlr_err
suffix:semicolon
DECL|member|plat_bus_err
r_struct
id|list_head
id|plat_bus_err
suffix:semicolon
DECL|member|unsupported
r_struct
id|list_head
id|unsupported
suffix:semicolon
multiline_comment|/* list of unsupported sections */
DECL|typedef|slidx_table_t
)brace
id|slidx_table_t
suffix:semicolon
DECL|macro|slidx_foreach_entry
mdefine_line|#define slidx_foreach_entry(pos, head) &bslash;&n;&t;list_for_each_entry(pos, head, list)
DECL|macro|slidx_first_entry
mdefine_line|#define slidx_first_entry(head) &bslash;&n;&t;(((head)-&gt;next != (head)) ? list_entry((head)-&gt;next, typeof(slidx_list_t), list) : NULL)
DECL|macro|slidx_count
mdefine_line|#define slidx_count(slidx, sec) &bslash;&n;({&t;int __count = 0; &bslash;&n;&t;slidx_list_t *__pos; &bslash;&n;&t;slidx_foreach_entry(__pos, &amp;((slidx)-&gt;sec)) { __count++; }&bslash;&n;&t;__count; })
eof
