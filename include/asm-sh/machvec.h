multiline_comment|/*&n; * include/asm-sh/machvec.h&n; *&n; * Copyright 2000 Stuart Menefy (stuart.menefy@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; */
macro_line|#ifndef _ASM_SH_MACHVEC_H
DECL|macro|_ASM_SH_MACHVEC_H
mdefine_line|#define _ASM_SH_MACHVEC_H 1
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
r_struct
id|timeval
suffix:semicolon
DECL|struct|sh_machine_vector
r_struct
id|sh_machine_vector
(brace
DECL|member|mv_name
r_const
r_char
op_star
id|mv_name
suffix:semicolon
DECL|member|mv_nr_irqs
r_int
id|mv_nr_irqs
suffix:semicolon
DECL|member|mv_inb
r_int
r_char
(paren
op_star
id|mv_inb
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|mv_inw
r_int
r_int
(paren
op_star
id|mv_inw
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|mv_inl
r_int
r_int
(paren
op_star
id|mv_inl
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|mv_outb
r_void
(paren
op_star
id|mv_outb
)paren
(paren
r_int
r_char
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|mv_outw
r_void
(paren
op_star
id|mv_outw
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|mv_outl
r_void
(paren
op_star
id|mv_outl
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|mv_inb_p
r_int
r_char
(paren
op_star
id|mv_inb_p
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|mv_inw_p
r_int
r_int
(paren
op_star
id|mv_inw_p
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|mv_inl_p
r_int
r_int
(paren
op_star
id|mv_inl_p
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|mv_outb_p
r_void
(paren
op_star
id|mv_outb_p
)paren
(paren
r_int
r_char
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|mv_outw_p
r_void
(paren
op_star
id|mv_outw_p
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|mv_outl_p
r_void
(paren
op_star
id|mv_outl_p
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|mv_insb
r_void
(paren
op_star
id|mv_insb
)paren
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
DECL|member|mv_insw
r_void
(paren
op_star
id|mv_insw
)paren
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
DECL|member|mv_insl
r_void
(paren
op_star
id|mv_insl
)paren
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
DECL|member|mv_outsb
r_void
(paren
op_star
id|mv_outsb
)paren
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
DECL|member|mv_outsw
r_void
(paren
op_star
id|mv_outsw
)paren
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
DECL|member|mv_outsl
r_void
(paren
op_star
id|mv_outsl
)paren
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
DECL|member|mv_readb
r_int
r_char
(paren
op_star
id|mv_readb
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|mv_readw
r_int
r_int
(paren
op_star
id|mv_readw
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|mv_readl
r_int
r_int
(paren
op_star
id|mv_readl
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|mv_writeb
r_void
(paren
op_star
id|mv_writeb
)paren
(paren
r_int
r_char
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|mv_writew
r_void
(paren
op_star
id|mv_writew
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|mv_writel
r_void
(paren
op_star
id|mv_writel
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|mv_ioremap
r_void
op_star
(paren
op_star
id|mv_ioremap
)paren
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|member|mv_iounmap
r_void
(paren
op_star
id|mv_iounmap
)paren
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
DECL|member|mv_isa_port2addr
r_int
r_int
(paren
op_star
id|mv_isa_port2addr
)paren
(paren
r_int
r_int
id|offset
)paren
suffix:semicolon
DECL|member|mv_irq_demux
r_int
(paren
op_star
id|mv_irq_demux
)paren
(paren
r_int
id|irq
)paren
suffix:semicolon
DECL|member|mv_init_arch
r_void
(paren
op_star
id|mv_init_arch
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|mv_init_irq
r_void
(paren
op_star
id|mv_init_irq
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|mv_init_pci
r_void
(paren
op_star
id|mv_init_pci
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|mv_kill_arch
r_void
(paren
op_star
id|mv_kill_arch
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|mv_heartbeat
r_void
(paren
op_star
id|mv_heartbeat
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|mv_rtc_gettimeofday
r_void
(paren
op_star
id|mv_rtc_gettimeofday
)paren
(paren
r_struct
id|timeval
op_star
id|tv
)paren
suffix:semicolon
DECL|member|mv_rtc_settimeofday
r_int
(paren
op_star
id|mv_rtc_settimeofday
)paren
(paren
r_const
r_struct
id|timeval
op_star
id|tv
)paren
suffix:semicolon
DECL|member|mv_hw_se
r_int
r_int
id|mv_hw_se
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mv_hw_hp600
r_int
r_int
id|mv_hw_hp600
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mv_hw_hp620
r_int
r_int
id|mv_hw_hp620
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mv_hw_hp680
r_int
r_int
id|mv_hw_hp680
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mv_hw_hp690
r_int
r_int
id|mv_hw_hp690
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mv_hw_hd64461
r_int
r_int
id|mv_hw_hd64461
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mv_hw_sh2000
r_int
r_int
id|mv_hw_sh2000
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mv_hw_hd64465
r_int
r_int
id|mv_hw_hd64465
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mv_hw_dreamcast
r_int
r_int
id|mv_hw_dreamcast
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mv_hw_bigsur
r_int
r_int
id|mv_hw_bigsur
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mv_hw_7751se
r_int
r_int
id|mv_hw_7751se
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mv_hw_adx
r_int
r_int
id|mv_hw_adx
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|sh_machine_vector
id|sh_mv
suffix:semicolon
multiline_comment|/* Machine check macros */
macro_line|#ifdef CONFIG_SH_GENERIC
DECL|macro|MACH_SE
mdefine_line|#define MACH_SE&t;&t;(sh_mv.mv_hw_se)
DECL|macro|MACH_HP600
mdefine_line|#define MACH_HP600&t;(sh_mv.mv_hw_hp600)
DECL|macro|MACH_HP620
mdefine_line|#define MACH_HP620&t;(sh_mv.mv_hw_hp620)
DECL|macro|MACH_HP680
mdefine_line|#define MACH_HP680&t;(sh_mv.mv_hw_hp680)
DECL|macro|MACH_HP690
mdefine_line|#define MACH_HP690&t;(sh_mv.mv_hw_hp690)
DECL|macro|MACH_HD64461
mdefine_line|#define MACH_HD64461&t;(sh_mv.mv_hw_hd64461)
DECL|macro|MACH_HD64465
mdefine_line|#define MACH_HD64465&t;(sh_mv.mv_hw_hd64465)
DECL|macro|MACH_SH2000
mdefine_line|#define MACH_SH2000&t;(sh_mv.mv_hw_sh2000)
DECL|macro|MACH_DREAMCAST
mdefine_line|#define MACH_DREAMCAST&t;(sh_mv.mv_hw_dreamcast)
DECL|macro|MACH_BIGSUR
mdefine_line|#define MACH_BIGSUR&t;(sh_mv.mv_hw_bigsur)
DECL|macro|MACH_7751SE
mdefine_line|#define MACH_7751SE&t;(sh_mv.mv_hw_7751se)
DECL|macro|MACH_ADX
mdefine_line|#define MACH_ADX&t;(sh_mv.mv_hw_adx)
macro_line|#else
macro_line|# ifdef CONFIG_SH_SOLUTION_ENGINE
DECL|macro|MACH_SE
macro_line|#  define MACH_SE&t;&t;1
macro_line|# else
DECL|macro|MACH_SE
macro_line|#  define MACH_SE&t;&t;0
macro_line|# endif
macro_line|# ifdef CONFIG_SH_7751_SOLUTION_ENGINE
DECL|macro|MACH_7751SE
macro_line|#  define MACH_7751SE&t;&t;1
macro_line|# else
DECL|macro|MACH_7751SE
macro_line|#  define MACH_7751SE&t;&t;0
macro_line|# endif
macro_line|# ifdef CONFIG_SH_HP600
DECL|macro|MACH_HP600
macro_line|#  define MACH_HP600&t;&t;1
macro_line|# else
DECL|macro|MACH_HP600
macro_line|#  define MACH_HP600&t;&t;0
macro_line|# endif
macro_line|# ifdef CONFIG_SH_HP620
DECL|macro|MACH_HP620
macro_line|#  define MACH_HP620&t;&t;1
macro_line|# else
DECL|macro|MACH_HP620
macro_line|#  define MACH_HP620&t;&t;0
macro_line|# endif
macro_line|# ifdef CONFIG_SH_HP680
DECL|macro|MACH_HP680
macro_line|#  define MACH_HP680&t;&t;1
macro_line|# else
DECL|macro|MACH_HP680
macro_line|#  define MACH_HP680&t;&t;0
macro_line|# endif
macro_line|# ifdef CONFIG_SH_HP690
DECL|macro|MACH_HP690
macro_line|#  define MACH_HP690&t;&t;1
macro_line|# else
DECL|macro|MACH_HP690
macro_line|#  define MACH_HP690&t;&t;0
macro_line|# endif
macro_line|# ifdef CONFIG_HD64461
DECL|macro|MACH_HD64461
macro_line|#  define MACH_HD64461&t;&t;1
macro_line|# else
DECL|macro|MACH_HD64461
macro_line|#  define MACH_HD64461&t;&t;0
macro_line|# endif
macro_line|# ifdef CONFIG_HD64465
DECL|macro|MACH_HD64465
macro_line|#  define MACH_HD64465&t;&t;1
macro_line|# else
DECL|macro|MACH_HD64465
macro_line|#  define MACH_HD64465&t;&t;0
macro_line|# endif
macro_line|# ifdef CONFIG_SH_SH2000
DECL|macro|MACH_SH2000
macro_line|#  define MACH_SH2000&t;&t;1
macro_line|# else
DECL|macro|MACH_SH2000
macro_line|#  define MACH_SH2000&t;&t;0
macro_line|# endif
macro_line|# ifdef CONFIG_SH_EC3104
DECL|macro|MACH_EC3104
macro_line|#  define MACH_EC3104&t;&t;1
macro_line|# else
DECL|macro|MACH_EC3104
macro_line|#  define MACH_EC3104&t;&t;0
macro_line|# endif
macro_line|# ifdef CONFIG_SH_DREAMCAST
DECL|macro|MACH_DREAMCAST
macro_line|#  define MACH_DREAMCAST&t;1
macro_line|# else
DECL|macro|MACH_DREAMCAST
macro_line|#  define MACH_DREAMCAST&t;0
macro_line|# endif
macro_line|# ifdef CONFIG_SH_BIGSUR
DECL|macro|MACH_BIGSUR
macro_line|#  define MACH_BIGSUR&t;&t;1
macro_line|# else
DECL|macro|MACH_BIGSUR
macro_line|#  define MACH_BIGSUR&t;&t;0
macro_line|# endif
macro_line|# ifdef CONFIG_SH_ADX
DECL|macro|MACH_ADX
macro_line|#  define MACH_ADX&t;&t;1
macro_line|# else
DECL|macro|MACH_ADX
macro_line|#  define MACH_ADX&t;&t;0
macro_line|# endif
macro_line|#endif
macro_line|#endif /* _ASM_SH_MACHVEC_H */
eof
