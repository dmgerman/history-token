macro_line|#ifndef _ASM_IA64_MACHVEC_HPSIM_h
DECL|macro|_ASM_IA64_MACHVEC_HPSIM_h
mdefine_line|#define _ASM_IA64_MACHVEC_HPSIM_h
r_extern
id|ia64_mv_setup_t
id|hpsim_setup
suffix:semicolon
r_extern
id|ia64_mv_irq_init_t
id|hpsim_irq_init
suffix:semicolon
r_extern
id|ia64_mv_map_nr_t
id|map_nr_dense
suffix:semicolon
multiline_comment|/*&n; * This stuff has dual use!&n; *&n; * For a generic kernel, the macros are used to initialize the&n; * platform&squot;s machvec structure.  When compiling a non-generic kernel,&n; * the macros are used directly.&n; */
DECL|macro|platform_name
mdefine_line|#define platform_name&t;&t;&quot;hpsim&quot;
DECL|macro|platform_setup
mdefine_line|#define platform_setup&t;&t;hpsim_setup
DECL|macro|platform_irq_init
mdefine_line|#define platform_irq_init&t;hpsim_irq_init
DECL|macro|platform_map_nr
mdefine_line|#define platform_map_nr&t;&t;map_nr_dense
macro_line|#endif /* _ASM_IA64_MACHVEC_HPSIM_h */
eof
