DECL|macro|__MACHVEC_HDR
mdefine_line|#define __MACHVEC_HDR(n)&t;&t;&lt;asm/machvec_##n##.h&gt;
DECL|macro|__MACHVEC_EXPAND
mdefine_line|#define __MACHVEC_EXPAND(n)&t;&t;__MACHVEC_HDR(n)
DECL|macro|MACHVEC_PLATFORM_HEADER
mdefine_line|#define MACHVEC_PLATFORM_HEADER&t;&t;__MACHVEC_EXPAND(MACHVEC_PLATFORM_NAME)
macro_line|#include &lt;asm/machvec.h&gt;
r_extern
id|ia64_mv_send_ipi_t
id|ia64_send_ipi
suffix:semicolon
r_extern
id|ia64_mv_global_tlb_purge_t
id|ia64_global_tlb_purge
suffix:semicolon
r_extern
id|ia64_mv_irq_desc
id|__ia64_irq_desc
suffix:semicolon
r_extern
id|ia64_mv_irq_to_vector
id|__ia64_irq_to_vector
suffix:semicolon
r_extern
id|ia64_mv_local_vector_to_irq
id|__ia64_local_vector_to_irq
suffix:semicolon
r_extern
id|ia64_mv_inb_t
id|__ia64_inb
suffix:semicolon
r_extern
id|ia64_mv_inw_t
id|__ia64_inw
suffix:semicolon
r_extern
id|ia64_mv_inl_t
id|__ia64_inl
suffix:semicolon
r_extern
id|ia64_mv_outb_t
id|__ia64_outb
suffix:semicolon
r_extern
id|ia64_mv_outw_t
id|__ia64_outw
suffix:semicolon
r_extern
id|ia64_mv_outl_t
id|__ia64_outl
suffix:semicolon
DECL|macro|MACHVEC_HELPER
mdefine_line|#define MACHVEC_HELPER(name)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; struct ia64_machine_vector machvec_##name __attribute__ ((unused, __section__ (&quot;.machvec&quot;)))&t;&bslash;&n;&t;= MACHVEC_INIT(name);
DECL|macro|MACHVEC_DEFINE
mdefine_line|#define MACHVEC_DEFINE(name)&t;MACHVEC_HELPER(name)
id|MACHVEC_DEFINE
c_func
(paren
id|MACHVEC_PLATFORM_NAME
)paren
eof
