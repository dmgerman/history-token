macro_line|#ifndef _ASM_IA64_MACHVEC_DIG_h
DECL|macro|_ASM_IA64_MACHVEC_DIG_h
mdefine_line|#define _ASM_IA64_MACHVEC_DIG_h
r_extern
id|ia64_mv_setup_t
id|dig_setup
suffix:semicolon
r_extern
id|ia64_mv_irq_init_t
id|dig_irq_init
suffix:semicolon
r_extern
id|ia64_mv_pci_fixup_t
id|iosapic_pci_fixup
suffix:semicolon
r_extern
id|ia64_mv_map_nr_t
id|map_nr_dense
suffix:semicolon
multiline_comment|/*&n; * This stuff has dual use!&n; *&n; * For a generic kernel, the macros are used to initialize the&n; * platform&squot;s machvec structure.  When compiling a non-generic kernel,&n; * the macros are used directly.&n; */
DECL|macro|platform_name
mdefine_line|#define platform_name&t;&t;&quot;dig&quot;
DECL|macro|platform_setup
mdefine_line|#define platform_setup&t;&t;dig_setup
DECL|macro|platform_irq_init
mdefine_line|#define platform_irq_init&t;dig_irq_init
DECL|macro|platform_pci_fixup
mdefine_line|#define platform_pci_fixup&t;iosapic_pci_fixup
DECL|macro|platform_map_nr
mdefine_line|#define platform_map_nr&t;&t;map_nr_dense
macro_line|#endif /* _ASM_IA64_MACHVEC_DIG_h */
eof
