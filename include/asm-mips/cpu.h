multiline_comment|/*&n; * cpu.h: Values of the PRId register used to match up&n; *        various MIPS cpu types.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#ifndef _ASM_CPU_H
DECL|macro|_ASM_CPU_H
mdefine_line|#define _ASM_CPU_H
macro_line|#include &lt;asm/cache.h&gt;
multiline_comment|/* Assigned Company values for bits 23:16 of the PRId Register  &n;   (CP0 register 15, select 0).  As of the MIPS32 and MIPS64 specs from &n;   MTI, the PRId register is defined in this (backwards compatible)&n;   way:&n;&n;  +----------------+----------------+----------------+----------------+&n;  | Company Options| Company ID     | Processor ID   | Revision       |&n;  +----------------+----------------+----------------+----------------+&n;   31            24 23            16 15             8 7&n;&n;   I don&squot;t have docs for all the previous processors, but my impression is&n;   that bits 16-23 have been 0 for all MIPS processors before the MIPS32/64&n;   spec.  &n;*/
DECL|macro|PRID_COMP_LEGACY
mdefine_line|#define PRID_COMP_LEGACY       0x000000
DECL|macro|PRID_COMP_MIPS
mdefine_line|#define PRID_COMP_MIPS         0x010000
DECL|macro|PRID_COMP_ALCHEMY
mdefine_line|#define PRID_COMP_ALCHEMY      0x030000
multiline_comment|/* &n; * Don&squot;t know who should be here...QED and Sandcraft, maybe?&n; */
DECL|macro|PRID_COMP_SIBYTE
mdefine_line|#define PRID_COMP_SIBYTE       0x040000
multiline_comment|/*&n; * Assigned values for the product ID register.  In order to detect a&n; * certain CPU type exactly eventually additional registers may need to&n; * be examined.  These are valid when 23:16 == PRID_COMP_LEGACY&n; */
DECL|macro|PRID_IMP_R2000
mdefine_line|#define PRID_IMP_R2000&t;&t;0x0100
DECL|macro|PRID_IMP_AU1000
mdefine_line|#define PRID_IMP_AU1000&t;0x0100
DECL|macro|PRID_IMP_R3000
mdefine_line|#define PRID_IMP_R3000&t;&t;0x0200&t;&t;/* Same as R2000A  */
DECL|macro|PRID_IMP_R6000
mdefine_line|#define PRID_IMP_R6000&t;&t;0x0300&t;&t;/* Same as R3000A  */
DECL|macro|PRID_IMP_R4000
mdefine_line|#define PRID_IMP_R4000&t;&t;0x0400
DECL|macro|PRID_IMP_R6000A
mdefine_line|#define PRID_IMP_R6000A&t;&t;0x0600
DECL|macro|PRID_IMP_R10000
mdefine_line|#define PRID_IMP_R10000&t;&t;0x0900
DECL|macro|PRID_IMP_R4300
mdefine_line|#define PRID_IMP_R4300&t;&t;0x0b00
DECL|macro|PRID_IMP_R12000
mdefine_line|#define PRID_IMP_R12000&t;&t;0x0e00
DECL|macro|PRID_IMP_R8000
mdefine_line|#define PRID_IMP_R8000&t;&t;0x1000
DECL|macro|PRID_IMP_R4600
mdefine_line|#define PRID_IMP_R4600&t;&t;0x2000
DECL|macro|PRID_IMP_R4700
mdefine_line|#define PRID_IMP_R4700&t;&t;0x2100
DECL|macro|PRID_IMP_TX39
mdefine_line|#define PRID_IMP_TX39&t;&t;0x2200
DECL|macro|PRID_IMP_R4640
mdefine_line|#define PRID_IMP_R4640&t;&t;0x2200
DECL|macro|PRID_IMP_R4650
mdefine_line|#define PRID_IMP_R4650&t;&t;0x2200&t;&t;/* Same as R4640 */
DECL|macro|PRID_IMP_R5000
mdefine_line|#define PRID_IMP_R5000&t;&t;0x2300
DECL|macro|PRID_IMP_R5432
mdefine_line|#define PRID_IMP_R5432&t;&t;0x5400
DECL|macro|PRID_IMP_SONIC
mdefine_line|#define PRID_IMP_SONIC&t;&t;0x2400
DECL|macro|PRID_IMP_MAGIC
mdefine_line|#define PRID_IMP_MAGIC&t;&t;0x2500
DECL|macro|PRID_IMP_RM7000
mdefine_line|#define PRID_IMP_RM7000&t;&t;0x2700
DECL|macro|PRID_IMP_NEVADA
mdefine_line|#define PRID_IMP_NEVADA&t;&t;0x2800&t;&t;/* RM5260 ??? */
DECL|macro|PRID_IMP_4KC
mdefine_line|#define PRID_IMP_4KC&t;&t;0x8000
DECL|macro|PRID_IMP_5KC
mdefine_line|#define PRID_IMP_5KC&t;&t;0x8100
DECL|macro|PRID_IMP_4KEC
mdefine_line|#define PRID_IMP_4KEC&t;&t;0x8400
DECL|macro|PRID_IMP_4KSC
mdefine_line|#define PRID_IMP_4KSC&t;&t;0x8600
DECL|macro|PRID_IMP_UNKNOWN
mdefine_line|#define PRID_IMP_UNKNOWN&t;0xff00
multiline_comment|/*&n; * These are the PRID&squot;s for when 23:16 == PRID_COMP_SIBYTE&n; */
DECL|macro|PRID_IMP_SB1
mdefine_line|#define PRID_IMP_SB1            0x0100
multiline_comment|/*&n; * Definitions for 7:0 on legacy processors&n; */
DECL|macro|PRID_REV_R4400
mdefine_line|#define PRID_REV_R4400&t;&t;0x0040
DECL|macro|PRID_REV_R3000A
mdefine_line|#define PRID_REV_R3000A&t;&t;0x0030
DECL|macro|PRID_REV_R3000
mdefine_line|#define PRID_REV_R3000&t;&t;0x0020
DECL|macro|PRID_REV_R2000A
mdefine_line|#define PRID_REV_R2000A&t;&t;0x0010
DECL|macro|PRID_REV_TX3912
mdefine_line|#define PRID_REV_TX3912 &t;0x0010
DECL|macro|PRID_REV_TX3922
mdefine_line|#define PRID_REV_TX3922 &t;0x0030
DECL|macro|PRID_REV_TX3927
mdefine_line|#define PRID_REV_TX3927 &t;0x0040
macro_line|#ifndef  _LANGUAGE_ASSEMBLY
multiline_comment|/*&n; * Capability and feature descriptor structure for MIPS CPU&n; */
DECL|struct|mips_cpu
r_struct
id|mips_cpu
(brace
DECL|member|processor_id
r_int
r_int
id|processor_id
suffix:semicolon
DECL|member|cputype
r_int
r_int
id|cputype
suffix:semicolon
multiline_comment|/* Old &quot;mips_cputype&quot; code */
DECL|member|isa_level
r_int
id|isa_level
suffix:semicolon
DECL|member|options
r_int
id|options
suffix:semicolon
DECL|member|tlbsize
r_int
id|tlbsize
suffix:semicolon
DECL|member|icache
r_struct
id|cache_desc
id|icache
suffix:semicolon
multiline_comment|/* Primary I-cache */
DECL|member|dcache
r_struct
id|cache_desc
id|dcache
suffix:semicolon
multiline_comment|/* Primary D or combined I/D cache */
DECL|member|scache
r_struct
id|cache_desc
id|scache
suffix:semicolon
multiline_comment|/* Secondary cache */
DECL|member|tcache
r_struct
id|cache_desc
id|tcache
suffix:semicolon
multiline_comment|/* Tertiary/split secondary cache */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * ISA Level encodings&n; */
DECL|macro|MIPS_CPU_ISA_I
mdefine_line|#define MIPS_CPU_ISA_I&t;&t;0x00000001
DECL|macro|MIPS_CPU_ISA_II
mdefine_line|#define MIPS_CPU_ISA_II&t;&t;0x00000002
DECL|macro|MIPS_CPU_ISA_III
mdefine_line|#define MIPS_CPU_ISA_III&t;0x00000003
DECL|macro|MIPS_CPU_ISA_IV
mdefine_line|#define MIPS_CPU_ISA_IV&t;&t;0x00000004
DECL|macro|MIPS_CPU_ISA_V
mdefine_line|#define MIPS_CPU_ISA_V&t;&t;0x00000005
DECL|macro|MIPS_CPU_ISA_M32
mdefine_line|#define MIPS_CPU_ISA_M32&t;0x00000020
DECL|macro|MIPS_CPU_ISA_M64
mdefine_line|#define MIPS_CPU_ISA_M64&t;0x00000040
multiline_comment|/*&n; * CPU Option encodings&n; */
DECL|macro|MIPS_CPU_TLB
mdefine_line|#define MIPS_CPU_TLB&t;&t;0x00000001  /* CPU has TLB */
multiline_comment|/* Leave a spare bit for variant MMU types... */
DECL|macro|MIPS_CPU_4KEX
mdefine_line|#define MIPS_CPU_4KEX&t;&t;0x00000004  /* &quot;R4K&quot; exception model */
DECL|macro|MIPS_CPU_4KTLB
mdefine_line|#define MIPS_CPU_4KTLB&t;&t;0x00000008  /* &quot;R4K&quot; TLB handler */
DECL|macro|MIPS_CPU_FPU
mdefine_line|#define MIPS_CPU_FPU&t;&t;0x00000010  /* CPU has FPU */
DECL|macro|MIPS_CPU_32FPR
mdefine_line|#define MIPS_CPU_32FPR&t;&t;0x00000020  /* 32 dbl. prec. FP registers */
DECL|macro|MIPS_CPU_COUNTER
mdefine_line|#define MIPS_CPU_COUNTER&t;0x00000040 /* Cycle count/compare */
DECL|macro|MIPS_CPU_WATCH
mdefine_line|#define MIPS_CPU_WATCH&t;&t;0x00000080  /* watchpoint registers */
DECL|macro|MIPS_CPU_MIPS16
mdefine_line|#define MIPS_CPU_MIPS16&t;&t;0x00000100  /* code compression */
DECL|macro|MIPS_CPU_DIVEC
mdefine_line|#define MIPS_CPU_DIVEC&t;&t;0x00000200  /* dedicated interrupt vector */
DECL|macro|MIPS_CPU_VCE
mdefine_line|#define MIPS_CPU_VCE&t;&t;0x00000400  /* virt. coherence conflict possible */
DECL|macro|MIPS_CPU_CACHE_CDEX
mdefine_line|#define MIPS_CPU_CACHE_CDEX&t;0x00000800 /* Create_Dirty_Exclusive CACHE op */
macro_line|#endif /* _ASM_CPU_H */
eof
