multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/machvec.h&n; *&n; *&t;Copyright (C) 1997, 1998  Richard Henderson&n; *&n; * This file has goodies to help simplify instantiation of machine vectors.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
multiline_comment|/* Whee.  These systems don&squot;t have an HAE:&n;       IRONGATE, MARVEL, POLARIS, TSUNAMI, TITAN, WILDFIRE&n;   Fix things up for the GENERIC kernel by defining the HAE address&n;   to be that of the cache. Now we can read and write it as we like.  ;-)  */
DECL|macro|IRONGATE_HAE_ADDRESS
mdefine_line|#define IRONGATE_HAE_ADDRESS&t;(&amp;alpha_mv.hae_cache)
DECL|macro|MARVEL_HAE_ADDRESS
mdefine_line|#define MARVEL_HAE_ADDRESS&t;(&amp;alpha_mv.hae_cache)
DECL|macro|POLARIS_HAE_ADDRESS
mdefine_line|#define POLARIS_HAE_ADDRESS&t;(&amp;alpha_mv.hae_cache)
DECL|macro|TSUNAMI_HAE_ADDRESS
mdefine_line|#define TSUNAMI_HAE_ADDRESS&t;(&amp;alpha_mv.hae_cache)
DECL|macro|TITAN_HAE_ADDRESS
mdefine_line|#define TITAN_HAE_ADDRESS&t;(&amp;alpha_mv.hae_cache)
DECL|macro|WILDFIRE_HAE_ADDRESS
mdefine_line|#define WILDFIRE_HAE_ADDRESS&t;(&amp;alpha_mv.hae_cache)
macro_line|#ifdef CIA_ONE_HAE_WINDOW
DECL|macro|CIA_HAE_ADDRESS
mdefine_line|#define CIA_HAE_ADDRESS&t;&t;(&amp;alpha_mv.hae_cache)
macro_line|#endif
macro_line|#ifdef MCPCIA_ONE_HAE_WINDOW
DECL|macro|MCPCIA_HAE_ADDRESS
mdefine_line|#define MCPCIA_HAE_ADDRESS&t;(&amp;alpha_mv.hae_cache)
macro_line|#endif
multiline_comment|/* Only a few systems don&squot;t define IACK_SC, handling all interrupts through&n;   the SRM console.  But splitting out that one case from IO() below&n;   seems like such a pain.  Define this to get things to compile.  */
DECL|macro|JENSEN_IACK_SC
mdefine_line|#define JENSEN_IACK_SC&t;&t;1
DECL|macro|T2_IACK_SC
mdefine_line|#define T2_IACK_SC&t;&t;1
DECL|macro|WILDFIRE_IACK_SC
mdefine_line|#define WILDFIRE_IACK_SC&t;1 /* FIXME */
multiline_comment|/*&n; * Some helpful macros for filling in the blanks.&n; */
DECL|macro|CAT1
mdefine_line|#define CAT1(x,y)  x##y
DECL|macro|CAT
mdefine_line|#define CAT(x,y)   CAT1(x,y)
DECL|macro|DO_DEFAULT_RTC
mdefine_line|#define DO_DEFAULT_RTC rtc_port: 0x70
DECL|macro|DO_EV4_MMU
mdefine_line|#define DO_EV4_MMU&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.max_asn =&t;&t;&t;EV4_MAX_ASN,&t;&t;&t;&bslash;&n;&t;.mv_switch_mm =&t;&t;&t;ev4_switch_mm,&t;&t;&t;&bslash;&n;&t;.mv_activate_mm =&t;&t;ev4_activate_mm,&t;&t;&bslash;&n;&t;.mv_flush_tlb_current =&t;&t;ev4_flush_tlb_current,&t;&t;&bslash;&n;&t;.mv_flush_tlb_current_page =&t;ev4_flush_tlb_current_page
DECL|macro|DO_EV5_MMU
mdefine_line|#define DO_EV5_MMU&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.max_asn =&t;&t;&t;EV5_MAX_ASN,&t;&t;&t;&bslash;&n;&t;.mv_switch_mm =&t;&t;&t;ev5_switch_mm,&t;&t;&t;&bslash;&n;&t;.mv_activate_mm =&t;&t;ev5_activate_mm,&t;&t;&bslash;&n;&t;.mv_flush_tlb_current =&t;&t;ev5_flush_tlb_current,&t;&t;&bslash;&n;&t;.mv_flush_tlb_current_page =&t;ev5_flush_tlb_current_page
DECL|macro|DO_EV6_MMU
mdefine_line|#define DO_EV6_MMU&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.max_asn =&t;&t;&t;EV6_MAX_ASN,&t;&t;&t;&bslash;&n;&t;.mv_switch_mm =&t;&t;&t;ev5_switch_mm,&t;&t;&t;&bslash;&n;&t;.mv_activate_mm =&t;&t;ev5_activate_mm,&t;&t;&bslash;&n;&t;.mv_flush_tlb_current =&t;&t;ev5_flush_tlb_current,&t;&t;&bslash;&n;&t;.mv_flush_tlb_current_page =&t;ev5_flush_tlb_current_page
DECL|macro|DO_EV7_MMU
mdefine_line|#define DO_EV7_MMU&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.max_asn =&t;&t;&t;EV6_MAX_ASN,&t;&t;&t;&bslash;&n;&t;.mv_switch_mm =&t;&t;&t;ev5_switch_mm,&t;&t;&t;&bslash;&n;&t;.mv_activate_mm =&t;&t;ev5_activate_mm,&t;&t;&bslash;&n;&t;.mv_flush_tlb_current =&t;&t;ev5_flush_tlb_current,&t;&t;&bslash;&n;&t;.mv_flush_tlb_current_page =&t;ev5_flush_tlb_current_page
DECL|macro|IO_LITE
mdefine_line|#define IO_LITE(UP,low)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.hae_register =&t;&t;(unsigned long *) CAT(UP,_HAE_ADDRESS),&t;&bslash;&n;&t;.iack_sc =&t;&t;CAT(UP,_IACK_SC),&t;&t;&t;&bslash;&n;&t;.mv_ioread8 =&t;&t;CAT(low,_ioread8),&t;&t;&t;&bslash;&n;&t;.mv_ioread16 =&t;&t;CAT(low,_ioread16),&t;&t;&t;&bslash;&n;&t;.mv_ioread32 =&t;&t;CAT(low,_ioread32),&t;&t;&t;&bslash;&n;&t;.mv_iowrite8 =&t;&t;CAT(low,_iowrite8),&t;&t;&t;&bslash;&n;&t;.mv_iowrite16 =&t;&t;CAT(low,_iowrite16),&t;&t;&t;&bslash;&n;&t;.mv_iowrite32 =&t;&t;CAT(low,_iowrite32),&t;&t;&t;&bslash;&n;&t;.mv_readb =&t;&t;CAT(low,_readb),&t;&t;&t;&bslash;&n;&t;.mv_readw =&t;&t;CAT(low,_readw),&t;&t;&t;&bslash;&n;&t;.mv_readl =&t;&t;CAT(low,_readl),&t;&t;&t;&bslash;&n;&t;.mv_readq =&t;&t;CAT(low,_readq),&t;&t;&t;&bslash;&n;&t;.mv_writeb =&t;&t;CAT(low,_writeb),&t;&t;&t;&bslash;&n;&t;.mv_writew =&t;&t;CAT(low,_writew),&t;&t;&t;&bslash;&n;&t;.mv_writel =&t;&t;CAT(low,_writel),&t;&t;&t;&bslash;&n;&t;.mv_writeq =&t;&t;CAT(low,_writeq),&t;&t;&t;&bslash;&n;&t;.mv_ioportmap =&t;&t;CAT(low,_ioportmap),&t;&t;&t;&bslash;&n;&t;.mv_ioremap =&t;&t;CAT(low,_ioremap),&t;&t;&t;&bslash;&n;&t;.mv_iounmap =&t;&t;CAT(low,_iounmap),&t;&t;&t;&bslash;&n;&t;.mv_is_ioaddr =&t;&t;CAT(low,_is_ioaddr),&t;&t;&t;&bslash;&n;&t;.mv_is_mmio =&t;&t;CAT(low,_is_mmio)&t;&t;&t;&bslash;&n;
DECL|macro|IO
mdefine_line|#define IO(UP,low)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;IO_LITE(UP,low),&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.pci_ops =&t;&t;&amp;CAT(low,_pci_ops),&t;&t;&t;&bslash;&n;&t;.mv_pci_tbi =&t;&t;CAT(low,_pci_tbi)
DECL|macro|DO_APECS_IO
mdefine_line|#define DO_APECS_IO&t;IO(APECS,apecs)
DECL|macro|DO_CIA_IO
mdefine_line|#define DO_CIA_IO&t;IO(CIA,cia)
DECL|macro|DO_IRONGATE_IO
mdefine_line|#define DO_IRONGATE_IO&t;IO(IRONGATE,irongate)
DECL|macro|DO_LCA_IO
mdefine_line|#define DO_LCA_IO&t;IO(LCA,lca)
DECL|macro|DO_MARVEL_IO
mdefine_line|#define DO_MARVEL_IO&t;IO(MARVEL,marvel)
DECL|macro|DO_MCPCIA_IO
mdefine_line|#define DO_MCPCIA_IO&t;IO(MCPCIA,mcpcia)
DECL|macro|DO_POLARIS_IO
mdefine_line|#define DO_POLARIS_IO&t;IO(POLARIS,polaris)
DECL|macro|DO_T2_IO
mdefine_line|#define DO_T2_IO&t;IO(T2,t2)
DECL|macro|DO_TSUNAMI_IO
mdefine_line|#define DO_TSUNAMI_IO&t;IO(TSUNAMI,tsunami)
DECL|macro|DO_TITAN_IO
mdefine_line|#define DO_TITAN_IO&t;IO(TITAN,titan)
DECL|macro|DO_WILDFIRE_IO
mdefine_line|#define DO_WILDFIRE_IO&t;IO(WILDFIRE,wildfire)
DECL|macro|DO_PYXIS_IO
mdefine_line|#define DO_PYXIS_IO&t;IO_LITE(CIA,cia_bwx), &bslash;&n;&t;&t;&t;.pci_ops = &amp;cia_pci_ops, &bslash;&n;&t;&t;&t;.mv_pci_tbi = cia_pci_tbi
multiline_comment|/*&n; * In a GENERIC kernel, we have lots of these vectors floating about,&n; * all but one of which we want to go away.  In a non-GENERIC kernel,&n; * we want only one, ever.&n; *&n; * Accomplish this in the GENERIC kernel by putting all of the vectors&n; * in the .init.data section where they&squot;ll go away.  We&squot;ll copy the&n; * one we want to the real alpha_mv vector in setup_arch.&n; *&n; * Accomplish this in a non-GENERIC kernel by ifdef&squot;ing out all but&n; * one of the vectors, which will not reside in .init.data.  We then&n; * alias this one vector to alpha_mv, so no copy is needed.&n; *&n; * Upshot: set __initdata to nothing for non-GENERIC kernels.&n; */
macro_line|#ifdef CONFIG_ALPHA_GENERIC
DECL|macro|__initmv
mdefine_line|#define __initmv __initdata
DECL|macro|ALIAS_MV
mdefine_line|#define ALIAS_MV(x)
macro_line|#else
DECL|macro|__initmv
mdefine_line|#define __initmv
multiline_comment|/* GCC actually has a syntax for defining aliases, but is under some&n;   delusion that you shouldn&squot;t be able to declare it extern somewhere&n;   else beforehand.  Fine.  We&squot;ll do it ourselves.  */
macro_line|#if 0
mdefine_line|#define ALIAS_MV(system) &bslash;&n;  struct alpha_machine_vector alpha_mv __attribute__((alias(#system &quot;_mv&quot;)));
macro_line|#else
DECL|macro|ALIAS_MV
mdefine_line|#define ALIAS_MV(system) &bslash;&n;  asm(&quot;.global alpha_mv&bslash;nalpha_mv = &quot; #system &quot;_mv&quot;);
macro_line|#endif
macro_line|#endif /* GENERIC */
eof
