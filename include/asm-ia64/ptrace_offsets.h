macro_line|#ifndef _ASM_IA64_PTRACE_OFFSETS_H
DECL|macro|_ASM_IA64_PTRACE_OFFSETS_H
mdefine_line|#define _ASM_IA64_PTRACE_OFFSETS_H
multiline_comment|/*&n; * Copyright (C) 1999 Hewlett-Packard Co&n; * Copyright (C) 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
multiline_comment|/*&n; * The &quot;uarea&quot; that can be accessed via PEEKUSER and POKEUSER is a&n; * virtual structure that would have the following definition:&n; *&n; *&t;struct uarea {&n; *&t;&t;struct ia64_fpreg fph[96];&t;&t;// f32-f127&n; *&t;&t;struct switch_stack sw;&n; *&t;&t;struct pt_regs pt;&n; *&t;&t;unsigned long rsvd1[712];&n; *&t;&t;unsigned long dbr[8];&n; *&t;&t;unsigned long rsvd2[504];&n; *&t;&t;unsigned long ibr[8];&n; *&t;&t;unsigned long rsvd3[504];&n; *&t;&t;unsigned long pmd[4];&n; *&t;}&n; */
multiline_comment|/* fph: */
DECL|macro|PT_F32
mdefine_line|#define PT_F32&t;&t;&t;0x0000
DECL|macro|PT_F33
mdefine_line|#define PT_F33&t;&t;&t;0x0010
DECL|macro|PT_F34
mdefine_line|#define PT_F34&t;&t;&t;0x0020
DECL|macro|PT_F35
mdefine_line|#define PT_F35&t;&t;&t;0x0030
DECL|macro|PT_F36
mdefine_line|#define PT_F36&t;&t;&t;0x0040
DECL|macro|PT_F37
mdefine_line|#define PT_F37&t;&t;&t;0x0050
DECL|macro|PT_F38
mdefine_line|#define PT_F38&t;&t;&t;0x0060
DECL|macro|PT_F39
mdefine_line|#define PT_F39&t;&t;&t;0x0070
DECL|macro|PT_F40
mdefine_line|#define PT_F40&t;&t;&t;0x0080
DECL|macro|PT_F41
mdefine_line|#define PT_F41&t;&t;&t;0x0090
DECL|macro|PT_F42
mdefine_line|#define PT_F42&t;&t;&t;0x00a0
DECL|macro|PT_F43
mdefine_line|#define PT_F43&t;&t;&t;0x00b0
DECL|macro|PT_F44
mdefine_line|#define PT_F44&t;&t;&t;0x00c0
DECL|macro|PT_F45
mdefine_line|#define PT_F45&t;&t;&t;0x00d0
DECL|macro|PT_F46
mdefine_line|#define PT_F46&t;&t;&t;0x00e0
DECL|macro|PT_F47
mdefine_line|#define PT_F47&t;&t;&t;0x00f0
DECL|macro|PT_F48
mdefine_line|#define PT_F48&t;&t;&t;0x0100
DECL|macro|PT_F49
mdefine_line|#define PT_F49&t;&t;&t;0x0110
DECL|macro|PT_F50
mdefine_line|#define PT_F50&t;&t;&t;0x0120
DECL|macro|PT_F51
mdefine_line|#define PT_F51&t;&t;&t;0x0130
DECL|macro|PT_F52
mdefine_line|#define PT_F52&t;&t;&t;0x0140
DECL|macro|PT_F53
mdefine_line|#define PT_F53&t;&t;&t;0x0150
DECL|macro|PT_F54
mdefine_line|#define PT_F54&t;&t;&t;0x0160
DECL|macro|PT_F55
mdefine_line|#define PT_F55&t;&t;&t;0x0170
DECL|macro|PT_F56
mdefine_line|#define PT_F56&t;&t;&t;0x0180
DECL|macro|PT_F57
mdefine_line|#define PT_F57&t;&t;&t;0x0190
DECL|macro|PT_F58
mdefine_line|#define PT_F58&t;&t;&t;0x01a0
DECL|macro|PT_F59
mdefine_line|#define PT_F59&t;&t;&t;0x01b0
DECL|macro|PT_F60
mdefine_line|#define PT_F60&t;&t;&t;0x01c0
DECL|macro|PT_F61
mdefine_line|#define PT_F61&t;&t;&t;0x01d0
DECL|macro|PT_F62
mdefine_line|#define PT_F62&t;&t;&t;0x01e0
DECL|macro|PT_F63
mdefine_line|#define PT_F63&t;&t;&t;0x01f0
DECL|macro|PT_F64
mdefine_line|#define PT_F64&t;&t;&t;0x0200
DECL|macro|PT_F65
mdefine_line|#define PT_F65&t;&t;&t;0x0210
DECL|macro|PT_F66
mdefine_line|#define PT_F66&t;&t;&t;0x0220
DECL|macro|PT_F67
mdefine_line|#define PT_F67&t;&t;&t;0x0230
DECL|macro|PT_F68
mdefine_line|#define PT_F68&t;&t;&t;0x0240
DECL|macro|PT_F69
mdefine_line|#define PT_F69&t;&t;&t;0x0250
DECL|macro|PT_F70
mdefine_line|#define PT_F70&t;&t;&t;0x0260
DECL|macro|PT_F71
mdefine_line|#define PT_F71&t;&t;&t;0x0270
DECL|macro|PT_F72
mdefine_line|#define PT_F72&t;&t;&t;0x0280
DECL|macro|PT_F73
mdefine_line|#define PT_F73&t;&t;&t;0x0290
DECL|macro|PT_F74
mdefine_line|#define PT_F74&t;&t;&t;0x02a0
DECL|macro|PT_F75
mdefine_line|#define PT_F75&t;&t;&t;0x02b0
DECL|macro|PT_F76
mdefine_line|#define PT_F76&t;&t;&t;0x02c0
DECL|macro|PT_F77
mdefine_line|#define PT_F77&t;&t;&t;0x02d0
DECL|macro|PT_F78
mdefine_line|#define PT_F78&t;&t;&t;0x02e0
DECL|macro|PT_F79
mdefine_line|#define PT_F79&t;&t;&t;0x02f0
DECL|macro|PT_F80
mdefine_line|#define PT_F80&t;&t;&t;0x0300
DECL|macro|PT_F81
mdefine_line|#define PT_F81&t;&t;&t;0x0310
DECL|macro|PT_F82
mdefine_line|#define PT_F82&t;&t;&t;0x0320
DECL|macro|PT_F83
mdefine_line|#define PT_F83&t;&t;&t;0x0330
DECL|macro|PT_F84
mdefine_line|#define PT_F84&t;&t;&t;0x0340
DECL|macro|PT_F85
mdefine_line|#define PT_F85&t;&t;&t;0x0350
DECL|macro|PT_F86
mdefine_line|#define PT_F86&t;&t;&t;0x0360
DECL|macro|PT_F87
mdefine_line|#define PT_F87&t;&t;&t;0x0370
DECL|macro|PT_F88
mdefine_line|#define PT_F88&t;&t;&t;0x0380
DECL|macro|PT_F89
mdefine_line|#define PT_F89&t;&t;&t;0x0390
DECL|macro|PT_F90
mdefine_line|#define PT_F90&t;&t;&t;0x03a0
DECL|macro|PT_F91
mdefine_line|#define PT_F91&t;&t;&t;0x03b0
DECL|macro|PT_F92
mdefine_line|#define PT_F92&t;&t;&t;0x03c0
DECL|macro|PT_F93
mdefine_line|#define PT_F93&t;&t;&t;0x03d0
DECL|macro|PT_F94
mdefine_line|#define PT_F94&t;&t;&t;0x03e0
DECL|macro|PT_F95
mdefine_line|#define PT_F95&t;&t;&t;0x03f0
DECL|macro|PT_F96
mdefine_line|#define PT_F96&t;&t;&t;0x0400
DECL|macro|PT_F97
mdefine_line|#define PT_F97&t;&t;&t;0x0410
DECL|macro|PT_F98
mdefine_line|#define PT_F98&t;&t;&t;0x0420
DECL|macro|PT_F99
mdefine_line|#define PT_F99&t;&t;&t;0x0430
DECL|macro|PT_F100
mdefine_line|#define PT_F100&t;&t;&t;0x0440
DECL|macro|PT_F101
mdefine_line|#define PT_F101&t;&t;&t;0x0450
DECL|macro|PT_F102
mdefine_line|#define PT_F102&t;&t;&t;0x0460
DECL|macro|PT_F103
mdefine_line|#define PT_F103&t;&t;&t;0x0470
DECL|macro|PT_F104
mdefine_line|#define PT_F104&t;&t;&t;0x0480
DECL|macro|PT_F105
mdefine_line|#define PT_F105&t;&t;&t;0x0490
DECL|macro|PT_F106
mdefine_line|#define PT_F106&t;&t;&t;0x04a0
DECL|macro|PT_F107
mdefine_line|#define PT_F107&t;&t;&t;0x04b0
DECL|macro|PT_F108
mdefine_line|#define PT_F108&t;&t;&t;0x04c0
DECL|macro|PT_F109
mdefine_line|#define PT_F109&t;&t;&t;0x04d0
DECL|macro|PT_F110
mdefine_line|#define PT_F110&t;&t;&t;0x04e0
DECL|macro|PT_F111
mdefine_line|#define PT_F111&t;&t;&t;0x04f0
DECL|macro|PT_F112
mdefine_line|#define PT_F112&t;&t;&t;0x0500
DECL|macro|PT_F113
mdefine_line|#define PT_F113&t;&t;&t;0x0510
DECL|macro|PT_F114
mdefine_line|#define PT_F114&t;&t;&t;0x0520
DECL|macro|PT_F115
mdefine_line|#define PT_F115&t;&t;&t;0x0530
DECL|macro|PT_F116
mdefine_line|#define PT_F116&t;&t;&t;0x0540
DECL|macro|PT_F117
mdefine_line|#define PT_F117&t;&t;&t;0x0550
DECL|macro|PT_F118
mdefine_line|#define PT_F118&t;&t;&t;0x0560
DECL|macro|PT_F119
mdefine_line|#define PT_F119&t;&t;&t;0x0570
DECL|macro|PT_F120
mdefine_line|#define PT_F120&t;&t;&t;0x0580
DECL|macro|PT_F121
mdefine_line|#define PT_F121&t;&t;&t;0x0590
DECL|macro|PT_F122
mdefine_line|#define PT_F122&t;&t;&t;0x05a0
DECL|macro|PT_F123
mdefine_line|#define PT_F123&t;&t;&t;0x05b0
DECL|macro|PT_F124
mdefine_line|#define PT_F124&t;&t;&t;0x05c0
DECL|macro|PT_F125
mdefine_line|#define PT_F125&t;&t;&t;0x05d0
DECL|macro|PT_F126
mdefine_line|#define PT_F126&t;&t;&t;0x05e0
DECL|macro|PT_F127
mdefine_line|#define PT_F127&t;&t;&t;0x05f0
multiline_comment|/* switch stack: */
DECL|macro|PT_NAT_BITS
mdefine_line|#define PT_NAT_BITS&t;&t;0x0600
DECL|macro|PT_F2
mdefine_line|#define PT_F2&t;&t;&t;0x0610
DECL|macro|PT_F3
mdefine_line|#define PT_F3&t;&t;&t;0x0620
DECL|macro|PT_F4
mdefine_line|#define PT_F4&t;&t;&t;0x0630
DECL|macro|PT_F5
mdefine_line|#define PT_F5&t;&t;&t;0x0640
DECL|macro|PT_F10
mdefine_line|#define PT_F10&t;&t;&t;0x0650
DECL|macro|PT_F11
mdefine_line|#define PT_F11&t;&t;&t;0x0660
DECL|macro|PT_F12
mdefine_line|#define PT_F12&t;&t;&t;0x0670
DECL|macro|PT_F13
mdefine_line|#define PT_F13&t;&t;&t;0x0680
DECL|macro|PT_F14
mdefine_line|#define PT_F14&t;&t;&t;0x0690
DECL|macro|PT_F15
mdefine_line|#define PT_F15&t;&t;&t;0x06a0
DECL|macro|PT_F16
mdefine_line|#define PT_F16&t;&t;&t;0x06b0
DECL|macro|PT_F17
mdefine_line|#define PT_F17&t;&t;&t;0x06c0
DECL|macro|PT_F18
mdefine_line|#define PT_F18&t;&t;&t;0x06d0
DECL|macro|PT_F19
mdefine_line|#define PT_F19&t;&t;&t;0x06e0
DECL|macro|PT_F20
mdefine_line|#define PT_F20&t;&t;&t;0x06f0
DECL|macro|PT_F21
mdefine_line|#define PT_F21&t;&t;&t;0x0700
DECL|macro|PT_F22
mdefine_line|#define PT_F22&t;&t;&t;0x0710
DECL|macro|PT_F23
mdefine_line|#define PT_F23&t;&t;&t;0x0720
DECL|macro|PT_F24
mdefine_line|#define PT_F24&t;&t;&t;0x0730
DECL|macro|PT_F25
mdefine_line|#define PT_F25&t;&t;&t;0x0740
DECL|macro|PT_F26
mdefine_line|#define PT_F26&t;&t;&t;0x0750
DECL|macro|PT_F27
mdefine_line|#define PT_F27&t;&t;&t;0x0760
DECL|macro|PT_F28
mdefine_line|#define PT_F28&t;&t;&t;0x0770
DECL|macro|PT_F29
mdefine_line|#define PT_F29&t;&t;&t;0x0780
DECL|macro|PT_F30
mdefine_line|#define PT_F30&t;&t;&t;0x0790
DECL|macro|PT_F31
mdefine_line|#define PT_F31&t;&t;&t;0x07a0
DECL|macro|PT_R4
mdefine_line|#define PT_R4&t;&t;&t;0x07b0
DECL|macro|PT_R5
mdefine_line|#define PT_R5&t;&t;&t;0x07b8
DECL|macro|PT_R6
mdefine_line|#define PT_R6&t;&t;&t;0x07c0
DECL|macro|PT_R7
mdefine_line|#define PT_R7&t;&t;&t;0x07c8
DECL|macro|PT_B1
mdefine_line|#define PT_B1&t;&t;&t;0x07d8
DECL|macro|PT_B2
mdefine_line|#define PT_B2&t;&t;&t;0x07e0
DECL|macro|PT_B3
mdefine_line|#define PT_B3&t;&t;&t;0x07e8
DECL|macro|PT_B4
mdefine_line|#define PT_B4&t;&t;&t;0x07f0
DECL|macro|PT_B5
mdefine_line|#define PT_B5&t;&t;&t;0x07f8
DECL|macro|PT_AR_EC
mdefine_line|#define PT_AR_EC&t;&t;0x0800
DECL|macro|PT_AR_LC
mdefine_line|#define PT_AR_LC&t;&t;0x0808
multiline_comment|/* pt_regs */
DECL|macro|PT_CR_IPSR
mdefine_line|#define PT_CR_IPSR&t;&t;0x0830
DECL|macro|PT_CR_IIP
mdefine_line|#define PT_CR_IIP&t;&t;0x0838
DECL|macro|PT_CFM
mdefine_line|#define PT_CFM&t;&t;&t;0x0840
DECL|macro|PT_AR_UNAT
mdefine_line|#define PT_AR_UNAT&t;&t;0x0848
DECL|macro|PT_AR_PFS
mdefine_line|#define PT_AR_PFS&t;&t;0x0850
DECL|macro|PT_AR_RSC
mdefine_line|#define PT_AR_RSC&t;&t;0x0858
DECL|macro|PT_AR_RNAT
mdefine_line|#define PT_AR_RNAT&t;&t;0x0860
DECL|macro|PT_AR_BSPSTORE
mdefine_line|#define PT_AR_BSPSTORE&t;&t;0x0868
DECL|macro|PT_PR
mdefine_line|#define PT_PR&t;&t;&t;0x0870
DECL|macro|PT_B6
mdefine_line|#define PT_B6&t;&t;&t;0x0878
DECL|macro|PT_AR_BSP
mdefine_line|#define PT_AR_BSP&t;&t;0x0880&t;/* note: this points to the *end* of the backing store! */
DECL|macro|PT_R1
mdefine_line|#define PT_R1&t;&t;&t;0x0888
DECL|macro|PT_R2
mdefine_line|#define PT_R2&t;&t;&t;0x0890
DECL|macro|PT_R3
mdefine_line|#define PT_R3&t;&t;&t;0x0898
DECL|macro|PT_R12
mdefine_line|#define PT_R12&t;&t;&t;0x08a0
DECL|macro|PT_R13
mdefine_line|#define PT_R13&t;&t;&t;0x08a8
DECL|macro|PT_R14
mdefine_line|#define PT_R14&t;&t;&t;0x08b0
DECL|macro|PT_R15
mdefine_line|#define PT_R15&t;&t;&t;0x08b8
DECL|macro|PT_R8
mdefine_line|#define PT_R8 &t;&t;&t;0x08c0
DECL|macro|PT_R9
mdefine_line|#define PT_R9&t;&t;&t;0x08c8
DECL|macro|PT_R10
mdefine_line|#define PT_R10&t;&t;&t;0x08d0
DECL|macro|PT_R11
mdefine_line|#define PT_R11&t;&t;&t;0x08d8
DECL|macro|PT_R16
mdefine_line|#define PT_R16&t;&t;&t;0x08e0
DECL|macro|PT_R17
mdefine_line|#define PT_R17&t;&t;&t;0x08e8
DECL|macro|PT_R18
mdefine_line|#define PT_R18&t;&t;&t;0x08f0
DECL|macro|PT_R19
mdefine_line|#define PT_R19&t;&t;&t;0x08f8
DECL|macro|PT_R20
mdefine_line|#define PT_R20&t;&t;&t;0x0900
DECL|macro|PT_R21
mdefine_line|#define PT_R21&t;&t;&t;0x0908
DECL|macro|PT_R22
mdefine_line|#define PT_R22&t;&t;&t;0x0910
DECL|macro|PT_R23
mdefine_line|#define PT_R23&t;&t;&t;0x0918
DECL|macro|PT_R24
mdefine_line|#define PT_R24&t;&t;&t;0x0920
DECL|macro|PT_R25
mdefine_line|#define PT_R25&t;&t;&t;0x0928
DECL|macro|PT_R26
mdefine_line|#define PT_R26&t;&t;&t;0x0930
DECL|macro|PT_R27
mdefine_line|#define PT_R27&t;&t;&t;0x0938
DECL|macro|PT_R28
mdefine_line|#define PT_R28&t;&t;&t;0x0940
DECL|macro|PT_R29
mdefine_line|#define PT_R29&t;&t;&t;0x0948
DECL|macro|PT_R30
mdefine_line|#define PT_R30&t;&t;&t;0x0950
DECL|macro|PT_R31
mdefine_line|#define PT_R31&t;&t;&t;0x0958
DECL|macro|PT_AR_CCV
mdefine_line|#define PT_AR_CCV&t;&t;0x0960
DECL|macro|PT_AR_FPSR
mdefine_line|#define PT_AR_FPSR&t;&t;0x0968
DECL|macro|PT_B0
mdefine_line|#define PT_B0&t;&t;&t;0x0970
DECL|macro|PT_B7
mdefine_line|#define PT_B7&t;&t;&t;0x0978
DECL|macro|PT_F6
mdefine_line|#define PT_F6&t;&t;&t;0x0980
DECL|macro|PT_F7
mdefine_line|#define PT_F7&t;&t;&t;0x0990
DECL|macro|PT_F8
mdefine_line|#define PT_F8&t;&t;&t;0x09a0
DECL|macro|PT_F9
mdefine_line|#define PT_F9&t;&t;&t;0x09b0
DECL|macro|PT_DBR
mdefine_line|#define PT_DBR&t;&t;&t;0x2000&t;/* data breakpoint registers */
DECL|macro|PT_IBR
mdefine_line|#define PT_IBR&t;&t;&t;0x3000&t;/* instruction breakpoint registers */
DECL|macro|PT_PMD
mdefine_line|#define PT_PMD&t;&t;&t;0x4000&t;/* performance monitoring counters */
macro_line|#endif /* _ASM_IA64_PTRACE_OFFSETS_H */
eof
