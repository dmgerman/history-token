multiline_comment|/*&n; *  linux/arch/arm/vfp/vfpinstr.h&n; *&n; *  Copyright (C) 2004 ARM Limited.&n; *  Written by Deep Blue Solutions Limited.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * VFP instruction masks.&n; */
DECL|macro|INST_CPRTDO
mdefine_line|#define INST_CPRTDO(inst)&t;(((inst) &amp; 0x0f000000) == 0x0e000000)
DECL|macro|INST_CPRT
mdefine_line|#define INST_CPRT(inst)&t;&t;((inst) &amp; (1 &lt;&lt; 4))
DECL|macro|INST_CPRT_L
mdefine_line|#define INST_CPRT_L(inst)&t;((inst) &amp; (1 &lt;&lt; 20))
DECL|macro|INST_CPRT_Rd
mdefine_line|#define INST_CPRT_Rd(inst)&t;(((inst) &amp; (15 &lt;&lt; 12)) &gt;&gt; 12)
DECL|macro|INST_CPRT_OP
mdefine_line|#define INST_CPRT_OP(inst)&t;(((inst) &gt;&gt; 21) &amp; 7)
DECL|macro|INST_CPNUM
mdefine_line|#define INST_CPNUM(inst)&t;((inst) &amp; 0xf00)
DECL|macro|CPNUM
mdefine_line|#define CPNUM(cp)&t;&t;((cp) &lt;&lt; 8)
DECL|macro|FOP_MASK
mdefine_line|#define FOP_MASK&t;(0x00b00040)
DECL|macro|FOP_FMAC
mdefine_line|#define FOP_FMAC&t;(0x00000000)
DECL|macro|FOP_FNMAC
mdefine_line|#define FOP_FNMAC&t;(0x00000040)
DECL|macro|FOP_FMSC
mdefine_line|#define FOP_FMSC&t;(0x00100000)
DECL|macro|FOP_FNMSC
mdefine_line|#define FOP_FNMSC&t;(0x00100040)
DECL|macro|FOP_FMUL
mdefine_line|#define FOP_FMUL&t;(0x00200000)
DECL|macro|FOP_FNMUL
mdefine_line|#define FOP_FNMUL&t;(0x00200040)
DECL|macro|FOP_FADD
mdefine_line|#define FOP_FADD&t;(0x00300000)
DECL|macro|FOP_FSUB
mdefine_line|#define FOP_FSUB&t;(0x00300040)
DECL|macro|FOP_FDIV
mdefine_line|#define FOP_FDIV&t;(0x00800000)
DECL|macro|FOP_EXT
mdefine_line|#define FOP_EXT&t;&t;(0x00b00040)
DECL|macro|FOP_TO_IDX
mdefine_line|#define FOP_TO_IDX(inst)&t;((inst &amp; 0x00b00000) &gt;&gt; 20 | (inst &amp; (1 &lt;&lt; 6)) &gt;&gt; 4)
DECL|macro|FEXT_MASK
mdefine_line|#define FEXT_MASK&t;(0x000f0080)
DECL|macro|FEXT_FCPY
mdefine_line|#define FEXT_FCPY&t;(0x00000000)
DECL|macro|FEXT_FABS
mdefine_line|#define FEXT_FABS&t;(0x00000080)
DECL|macro|FEXT_FNEG
mdefine_line|#define FEXT_FNEG&t;(0x00010000)
DECL|macro|FEXT_FSQRT
mdefine_line|#define FEXT_FSQRT&t;(0x00010080)
DECL|macro|FEXT_FCMP
mdefine_line|#define FEXT_FCMP&t;(0x00040000)
DECL|macro|FEXT_FCMPE
mdefine_line|#define FEXT_FCMPE&t;(0x00040080)
DECL|macro|FEXT_FCMPZ
mdefine_line|#define FEXT_FCMPZ&t;(0x00050000)
DECL|macro|FEXT_FCMPEZ
mdefine_line|#define FEXT_FCMPEZ&t;(0x00050080)
DECL|macro|FEXT_FCVT
mdefine_line|#define FEXT_FCVT&t;(0x00070080)
DECL|macro|FEXT_FUITO
mdefine_line|#define FEXT_FUITO&t;(0x00080000)
DECL|macro|FEXT_FSITO
mdefine_line|#define FEXT_FSITO&t;(0x00080080)
DECL|macro|FEXT_FTOUI
mdefine_line|#define FEXT_FTOUI&t;(0x000c0000)
DECL|macro|FEXT_FTOUIZ
mdefine_line|#define FEXT_FTOUIZ&t;(0x000c0080)
DECL|macro|FEXT_FTOSI
mdefine_line|#define FEXT_FTOSI&t;(0x000d0000)
DECL|macro|FEXT_FTOSIZ
mdefine_line|#define FEXT_FTOSIZ&t;(0x000d0080)
DECL|macro|FEXT_TO_IDX
mdefine_line|#define FEXT_TO_IDX(inst)&t;((inst &amp; 0x000f0000) &gt;&gt; 15 | (inst &amp; (1 &lt;&lt; 7)) &gt;&gt; 7)
DECL|macro|vfp_get_sd
mdefine_line|#define vfp_get_sd(inst)&t;((inst &amp; 0x0000f000) &gt;&gt; 11 | (inst &amp; (1 &lt;&lt; 22)) &gt;&gt; 22)
DECL|macro|vfp_get_dd
mdefine_line|#define vfp_get_dd(inst)&t;((inst &amp; 0x0000f000) &gt;&gt; 12)
DECL|macro|vfp_get_sm
mdefine_line|#define vfp_get_sm(inst)&t;((inst &amp; 0x0000000f) &lt;&lt; 1 | (inst &amp; (1 &lt;&lt; 5)) &gt;&gt; 5)
DECL|macro|vfp_get_dm
mdefine_line|#define vfp_get_dm(inst)&t;((inst &amp; 0x0000000f))
DECL|macro|vfp_get_sn
mdefine_line|#define vfp_get_sn(inst)&t;((inst &amp; 0x000f0000) &gt;&gt; 15 | (inst &amp; (1 &lt;&lt; 7)) &gt;&gt; 7)
DECL|macro|vfp_get_dn
mdefine_line|#define vfp_get_dn(inst)&t;((inst &amp; 0x000f0000) &gt;&gt; 16)
DECL|macro|vfp_single
mdefine_line|#define vfp_single(inst)&t;(((inst) &amp; 0x0000f00) == 0xa00)
DECL|macro|FPSCR_N
mdefine_line|#define FPSCR_N&t;(1 &lt;&lt; 31)
DECL|macro|FPSCR_Z
mdefine_line|#define FPSCR_Z&t;(1 &lt;&lt; 30)
DECL|macro|FPSCR_C
mdefine_line|#define FPSCR_C (1 &lt;&lt; 29)
DECL|macro|FPSCR_V
mdefine_line|#define FPSCR_V&t;(1 &lt;&lt; 28)
multiline_comment|/*&n; * Since we aren&squot;t building with -mfpu=vfp, we need to code&n; * these instructions using their MRC/MCR equivalents.&n; */
DECL|macro|vfpreg
mdefine_line|#define vfpreg(_vfp_) #_vfp_
DECL|macro|fmrx
mdefine_line|#define fmrx(_vfp_) ({&t;&t;&t;&bslash;&n;&t;u32 __v;&t;&t;&t;&bslash;&n;&t;asm(&quot;mrc%? p10, 7, %0, &quot; vfpreg(_vfp_) &quot;, cr0, 0 @ fmrx&t;%0, &quot; #_vfp_&t;&bslash;&n;&t;    : &quot;=r&quot; (__v));&t;&t;&bslash;&n;&t;__v;&t;&t;&t;&t;&bslash;&n; })
DECL|macro|fmxr
mdefine_line|#define fmxr(_vfp_,_var_)&t;&t;&bslash;&n;&t;asm(&quot;mcr%? p10, 7, %0, &quot; vfpreg(_vfp_) &quot;, cr0, 0 @ fmxr&t;&quot; #_vfp_ &quot;, %0&quot;&t;&bslash;&n;&t;   : : &quot;r&quot; (_var_))
id|u32
id|vfp_single_cpdo
c_func
(paren
id|u32
id|inst
comma
id|u32
id|fpscr
)paren
suffix:semicolon
id|u32
id|vfp_single_cprt
c_func
(paren
id|u32
id|inst
comma
id|u32
id|fpscr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
id|u32
id|vfp_double_cpdo
c_func
(paren
id|u32
id|inst
comma
id|u32
id|fpscr
)paren
suffix:semicolon
eof
