multiline_comment|/*&n; * cpu.h: Values of the PRId register used to match up&n; *        various MIPS cpu types.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#ifndef _ASM_CPU_H
DECL|macro|_ASM_CPU_H
mdefine_line|#define _ASM_CPU_H
macro_line|#include &lt;linux/cpu.h&gt;
multiline_comment|/* Assigned Company values for bits 23:16 of the PRId Register&n;   (CP0 register 15, select 0).  As of the MIPS32 and MIPS64 specs from&n;   MTI, the PRId register is defined in this (backwards compatible)&n;   way:&n;&n;  +----------------+----------------+----------------+----------------+&n;  | Company Options| Company ID     | Processor ID   | Revision       |&n;  +----------------+----------------+----------------+----------------+&n;   31            24 23            16 15             8 7&n;&n;   I don&squot;t have docs for all the previous processors, but my impression is&n;   that bits 16-23 have been 0 for all MIPS processors before the MIPS32/64&n;   spec.&n;*/
DECL|macro|PRID_COMP_LEGACY
mdefine_line|#define PRID_COMP_LEGACY       0x000000
DECL|macro|PRID_COMP_MIPS
mdefine_line|#define PRID_COMP_MIPS         0x010000
DECL|macro|PRID_COMP_BROADCOM
mdefine_line|#define PRID_COMP_BROADCOM     0x020000
DECL|macro|PRID_COMP_ALCHEMY
mdefine_line|#define PRID_COMP_ALCHEMY      0x030000
DECL|macro|PRID_COMP_SIBYTE
mdefine_line|#define PRID_COMP_SIBYTE       0x040000
DECL|macro|PRID_COMP_SANDCRAFT
mdefine_line|#define PRID_COMP_SANDCRAFT    0x050000
multiline_comment|/*&n; * Assigned values for the product ID register.  In order to detect a&n; * certain CPU type exactly eventually additional registers may need to&n; * be examined.  These are valid when 23:16 == PRID_COMP_LEGACY&n; */
DECL|macro|PRID_IMP_R2000
mdefine_line|#define PRID_IMP_R2000&t;&t;0x0100
DECL|macro|PRID_IMP_AU1_REV1
mdefine_line|#define PRID_IMP_AU1_REV1&t;0x0100
DECL|macro|PRID_IMP_AU1_REV2
mdefine_line|#define PRID_IMP_AU1_REV2&t;0x0200
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
DECL|macro|PRID_IMP_VR41XX
mdefine_line|#define PRID_IMP_VR41XX&t;&t;0x0c00
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
DECL|macro|PRID_IMP_TX49
mdefine_line|#define PRID_IMP_TX49&t;&t;0x2d00
DECL|macro|PRID_IMP_SONIC
mdefine_line|#define PRID_IMP_SONIC&t;&t;0x2400
DECL|macro|PRID_IMP_MAGIC
mdefine_line|#define PRID_IMP_MAGIC&t;&t;0x2500
DECL|macro|PRID_IMP_RM7000
mdefine_line|#define PRID_IMP_RM7000&t;&t;0x2700
DECL|macro|PRID_IMP_NEVADA
mdefine_line|#define PRID_IMP_NEVADA&t;&t;0x2800&t;&t;/* RM5260 ??? */
DECL|macro|PRID_IMP_R5432
mdefine_line|#define PRID_IMP_R5432&t;&t;0x5400
DECL|macro|PRID_IMP_R5500
mdefine_line|#define PRID_IMP_R5500&t;&t;0x5500
DECL|macro|PRID_IMP_4KC
mdefine_line|#define PRID_IMP_4KC&t;&t;0x8000
DECL|macro|PRID_IMP_5KC
mdefine_line|#define PRID_IMP_5KC&t;&t;0x8100
DECL|macro|PRID_IMP_20KC
mdefine_line|#define PRID_IMP_20KC&t;&t;0x8200
DECL|macro|PRID_IMP_4KEC
mdefine_line|#define PRID_IMP_4KEC&t;&t;0x8400
DECL|macro|PRID_IMP_4KSC
mdefine_line|#define PRID_IMP_4KSC&t;&t;0x8600
DECL|macro|PRID_IMP_UNKNOWN
mdefine_line|#define PRID_IMP_UNKNOWN&t;0xff00
multiline_comment|/*&n; * These are the PRID&squot;s for when 23:16 == PRID_COMP_SIBYTE&n; */
DECL|macro|PRID_IMP_SB1
mdefine_line|#define PRID_IMP_SB1            0x0100
multiline_comment|/*&n; * These are the PRID&squot;s for when 23:16 == PRID_COMP_SANDCRAFT&n; */
DECL|macro|PRID_IMP_SR71000
mdefine_line|#define PRID_IMP_SR71000        0x0400
multiline_comment|/*&n; * Definitions for 7:0 on legacy processors&n; */
DECL|macro|PRID_REV_TX4927
mdefine_line|#define PRID_REV_TX4927&t;&t;0x0022
DECL|macro|PRID_REV_TX4937
mdefine_line|#define PRID_REV_TX4937&t;&t;0x0030
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
DECL|macro|PRID_REV_VR4111
mdefine_line|#define PRID_REV_VR4111&t;&t;0x0050
DECL|macro|PRID_REV_VR4181
mdefine_line|#define PRID_REV_VR4181&t;&t;0x0050&t;/* Same as VR4111 */
DECL|macro|PRID_REV_VR4121
mdefine_line|#define PRID_REV_VR4121&t;&t;0x0060
DECL|macro|PRID_REV_VR4122
mdefine_line|#define PRID_REV_VR4122&t;&t;0x0070
DECL|macro|PRID_REV_VR4181A
mdefine_line|#define PRID_REV_VR4181A&t;0x0070&t;/* Same as VR4122 */
DECL|macro|PRID_REV_VR4131
mdefine_line|#define PRID_REV_VR4131&t;&t;0x0080
multiline_comment|/*&n; * FPU implementation/revision register (CP1 control register 0).&n; *&n; * +---------------------------------+----------------+----------------+&n; * | 0                               | Implementation | Revision       |&n; * +---------------------------------+----------------+----------------+&n; *  31                             16 15             8 7              0&n; */
DECL|macro|FPIR_IMP_NONE
mdefine_line|#define FPIR_IMP_NONE&t;&t;0x0000
DECL|macro|CPU_UNKNOWN
mdefine_line|#define CPU_UNKNOWN&t;&t; 0
DECL|macro|CPU_R2000
mdefine_line|#define CPU_R2000&t;&t; 1
DECL|macro|CPU_R3000
mdefine_line|#define CPU_R3000&t;&t; 2
DECL|macro|CPU_R3000A
mdefine_line|#define CPU_R3000A&t;&t; 3
DECL|macro|CPU_R3041
mdefine_line|#define CPU_R3041&t;&t; 4
DECL|macro|CPU_R3051
mdefine_line|#define CPU_R3051&t;&t; 5
DECL|macro|CPU_R3052
mdefine_line|#define CPU_R3052&t;&t; 6
DECL|macro|CPU_R3081
mdefine_line|#define CPU_R3081&t;&t; 7
DECL|macro|CPU_R3081E
mdefine_line|#define CPU_R3081E&t;&t; 8
DECL|macro|CPU_R4000PC
mdefine_line|#define CPU_R4000PC&t;&t; 9
DECL|macro|CPU_R4000SC
mdefine_line|#define CPU_R4000SC&t;&t;10
DECL|macro|CPU_R4000MC
mdefine_line|#define CPU_R4000MC&t;&t;11
DECL|macro|CPU_R4200
mdefine_line|#define CPU_R4200&t;&t;12
DECL|macro|CPU_R4400PC
mdefine_line|#define CPU_R4400PC&t;&t;13
DECL|macro|CPU_R4400SC
mdefine_line|#define CPU_R4400SC&t;&t;14
DECL|macro|CPU_R4400MC
mdefine_line|#define CPU_R4400MC&t;&t;15
DECL|macro|CPU_R4600
mdefine_line|#define CPU_R4600&t;&t;16
DECL|macro|CPU_R6000
mdefine_line|#define CPU_R6000&t;&t;17
DECL|macro|CPU_R6000A
mdefine_line|#define CPU_R6000A&t;&t;18
DECL|macro|CPU_R8000
mdefine_line|#define CPU_R8000&t;&t;19
DECL|macro|CPU_R10000
mdefine_line|#define CPU_R10000&t;&t;20
DECL|macro|CPU_R12000
mdefine_line|#define CPU_R12000&t;&t;21
DECL|macro|CPU_R4300
mdefine_line|#define CPU_R4300&t;&t;22
DECL|macro|CPU_R4650
mdefine_line|#define CPU_R4650&t;&t;23
DECL|macro|CPU_R4700
mdefine_line|#define CPU_R4700&t;&t;24
DECL|macro|CPU_R5000
mdefine_line|#define CPU_R5000&t;&t;25
DECL|macro|CPU_R5000A
mdefine_line|#define CPU_R5000A&t;&t;26
DECL|macro|CPU_R4640
mdefine_line|#define CPU_R4640&t;&t;27
DECL|macro|CPU_NEVADA
mdefine_line|#define CPU_NEVADA&t;&t;28
DECL|macro|CPU_RM7000
mdefine_line|#define CPU_RM7000&t;&t;29
DECL|macro|CPU_R5432
mdefine_line|#define CPU_R5432&t;&t;30
DECL|macro|CPU_4KC
mdefine_line|#define CPU_4KC&t;&t;&t;31
DECL|macro|CPU_5KC
mdefine_line|#define CPU_5KC&t;&t;&t;32
DECL|macro|CPU_R4310
mdefine_line|#define CPU_R4310&t;&t;33
DECL|macro|CPU_SB1
mdefine_line|#define CPU_SB1&t;&t;&t;34
DECL|macro|CPU_TX3912
mdefine_line|#define CPU_TX3912&t;&t;35
DECL|macro|CPU_TX3922
mdefine_line|#define CPU_TX3922&t;&t;36
DECL|macro|CPU_TX3927
mdefine_line|#define CPU_TX3927&t;&t;37
DECL|macro|CPU_AU1000
mdefine_line|#define CPU_AU1000&t;&t;38
DECL|macro|CPU_4KEC
mdefine_line|#define CPU_4KEC&t;&t;39
DECL|macro|CPU_4KSC
mdefine_line|#define CPU_4KSC&t;&t;40
DECL|macro|CPU_VR41XX
mdefine_line|#define CPU_VR41XX&t;&t;41
DECL|macro|CPU_R5500
mdefine_line|#define CPU_R5500&t;&t;42
DECL|macro|CPU_TX49XX
mdefine_line|#define CPU_TX49XX&t;&t;43
DECL|macro|CPU_AU1500
mdefine_line|#define CPU_AU1500&t;&t;44
DECL|macro|CPU_20KC
mdefine_line|#define CPU_20KC&t;&t;45
DECL|macro|CPU_VR4111
mdefine_line|#define CPU_VR4111&t;&t;46
DECL|macro|CPU_VR4121
mdefine_line|#define CPU_VR4121&t;&t;47
DECL|macro|CPU_VR4122
mdefine_line|#define CPU_VR4122&t;&t;48
DECL|macro|CPU_VR4131
mdefine_line|#define CPU_VR4131&t;&t;49
DECL|macro|CPU_VR4181
mdefine_line|#define CPU_VR4181&t;&t;50
DECL|macro|CPU_VR4181A
mdefine_line|#define CPU_VR4181A&t;&t;51
DECL|macro|CPU_AU1100
mdefine_line|#define CPU_AU1100&t;&t;52
DECL|macro|CPU_SR71000
mdefine_line|#define CPU_SR71000&t;&t;53
DECL|macro|CPU_LAST
mdefine_line|#define CPU_LAST&t;&t;53
multiline_comment|/*&n; * ISA Level encodings&n; *&n; */
DECL|macro|MIPS_CPU_ISA_I
mdefine_line|#define MIPS_CPU_ISA_I&t;&t;0x00000001
DECL|macro|MIPS_CPU_ISA_II
mdefine_line|#define MIPS_CPU_ISA_II&t;&t;0x00000002
DECL|macro|MIPS_CPU_ISA_III
mdefine_line|#define MIPS_CPU_ISA_III&t;0x00008003
DECL|macro|MIPS_CPU_ISA_IV
mdefine_line|#define MIPS_CPU_ISA_IV&t;&t;0x00008004
DECL|macro|MIPS_CPU_ISA_V
mdefine_line|#define MIPS_CPU_ISA_V&t;&t;0x00008005
DECL|macro|MIPS_CPU_ISA_M32
mdefine_line|#define MIPS_CPU_ISA_M32&t;0x00000020
DECL|macro|MIPS_CPU_ISA_M64
mdefine_line|#define MIPS_CPU_ISA_M64&t;0x00008040
multiline_comment|/*&n; * Bit 15 encodes if an ISA level supports 64-bit operations.&n; */
DECL|macro|MIPS_CPU_ISA_64BIT
mdefine_line|#define MIPS_CPU_ISA_64BIT&t;0x00008000
multiline_comment|/*&n; * CPU Option encodings&n; */
DECL|macro|MIPS_CPU_TLB
mdefine_line|#define MIPS_CPU_TLB&t;&t;0x00000001 /* CPU has TLB */
multiline_comment|/* Leave a spare bit for variant MMU types... */
DECL|macro|MIPS_CPU_4KEX
mdefine_line|#define MIPS_CPU_4KEX&t;&t;0x00000004 /* &quot;R4K&quot; exception model */
DECL|macro|MIPS_CPU_4KTLB
mdefine_line|#define MIPS_CPU_4KTLB&t;&t;0x00000008 /* &quot;R4K&quot; TLB handler */
DECL|macro|MIPS_CPU_FPU
mdefine_line|#define MIPS_CPU_FPU&t;&t;0x00000010 /* CPU has FPU */
DECL|macro|MIPS_CPU_32FPR
mdefine_line|#define MIPS_CPU_32FPR&t;&t;0x00000020 /* 32 dbl. prec. FP registers */
DECL|macro|MIPS_CPU_COUNTER
mdefine_line|#define MIPS_CPU_COUNTER&t;0x00000040 /* Cycle count/compare */
DECL|macro|MIPS_CPU_WATCH
mdefine_line|#define MIPS_CPU_WATCH&t;&t;0x00000080 /* watchpoint registers */
DECL|macro|MIPS_CPU_MIPS16
mdefine_line|#define MIPS_CPU_MIPS16&t;&t;0x00000100 /* code compression */
DECL|macro|MIPS_CPU_DIVEC
mdefine_line|#define MIPS_CPU_DIVEC&t;&t;0x00000200 /* dedicated interrupt vector */
DECL|macro|MIPS_CPU_VCE
mdefine_line|#define MIPS_CPU_VCE&t;&t;0x00000400 /* virt. coherence conflict possible */
DECL|macro|MIPS_CPU_CACHE_CDEX
mdefine_line|#define MIPS_CPU_CACHE_CDEX&t;0x00000800 /* Create_Dirty_Exclusive CACHE op */
DECL|macro|MIPS_CPU_MCHECK
mdefine_line|#define MIPS_CPU_MCHECK&t;&t;0x00001000 /* Machine check exception */
DECL|macro|MIPS_CPU_EJTAG
mdefine_line|#define MIPS_CPU_EJTAG&t;&t;0x00002000 /* EJTAG exception */
DECL|macro|MIPS_CPU_NOFPUEX
mdefine_line|#define MIPS_CPU_NOFPUEX&t;0x00000000 /* no FPU exception; never set */
DECL|macro|MIPS_CPU_LLSC
mdefine_line|#define MIPS_CPU_LLSC&t;&t;0x00008000 /* CPU has ll/sc instructions */
DECL|macro|MIPS_CPU_SUBSET_CACHES
mdefine_line|#define MIPS_CPU_SUBSET_CACHES&t;0x00010000 /* P-cache subset enforced */
macro_line|#endif /* _ASM_CPU_H */
eof
