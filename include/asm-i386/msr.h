macro_line|#ifndef __ASM_MSR_H
DECL|macro|__ASM_MSR_H
mdefine_line|#define __ASM_MSR_H
multiline_comment|/*&n; * Access to machine-specific registers (available on 586 and better only)&n; * Note: the rd* operations modify the parameters directly (without using&n; * pointer indirection), this allows gcc to optimize better&n; */
DECL|macro|rdmsr
mdefine_line|#define rdmsr(msr,val1,val2) &bslash;&n;     __asm__ __volatile__(&quot;rdmsr&quot; &bslash;&n;&t;&t;&t;  : &quot;=a&quot; (val1), &quot;=d&quot; (val2) &bslash;&n;&t;&t;&t;  : &quot;c&quot; (msr))
DECL|macro|wrmsr
mdefine_line|#define wrmsr(msr,val1,val2) &bslash;&n;     __asm__ __volatile__(&quot;wrmsr&quot; &bslash;&n;&t;&t;&t;  : /* no outputs */ &bslash;&n;&t;&t;&t;  : &quot;c&quot; (msr), &quot;a&quot; (val1), &quot;d&quot; (val2))
DECL|macro|rdtsc
mdefine_line|#define rdtsc(low,high) &bslash;&n;     __asm__ __volatile__(&quot;rdtsc&quot; : &quot;=a&quot; (low), &quot;=d&quot; (high))
DECL|macro|rdtscl
mdefine_line|#define rdtscl(low) &bslash;&n;     __asm__ __volatile__(&quot;rdtsc&quot; : &quot;=a&quot; (low) : : &quot;edx&quot;)
DECL|macro|rdtscll
mdefine_line|#define rdtscll(val) &bslash;&n;     __asm__ __volatile__(&quot;rdtsc&quot; : &quot;=A&quot; (val))
DECL|macro|write_tsc
mdefine_line|#define write_tsc(val1,val2) wrmsr(0x10, val1, val2)
DECL|macro|rdpmc
mdefine_line|#define rdpmc(counter,low,high) &bslash;&n;     __asm__ __volatile__(&quot;rdpmc&quot; &bslash;&n;&t;&t;&t;  : &quot;=a&quot; (low), &quot;=d&quot; (high) &bslash;&n;&t;&t;&t;  : &quot;c&quot; (counter))
multiline_comment|/* symbolic names for some interesting MSRs */
multiline_comment|/* Intel defined MSRs. */
DECL|macro|MSR_IA32_P5_MC_ADDR
mdefine_line|#define MSR_IA32_P5_MC_ADDR&t;&t;0
DECL|macro|MSR_IA32_P5_MC_TYPE
mdefine_line|#define MSR_IA32_P5_MC_TYPE&t;&t;1
DECL|macro|MSR_IA32_PLATFORM_ID
mdefine_line|#define MSR_IA32_PLATFORM_ID&t;&t;0x17
DECL|macro|MSR_IA32_EBL_CR_POWERON
mdefine_line|#define MSR_IA32_EBL_CR_POWERON&t;&t;0x2a
DECL|macro|MSR_IA32_APICBASE
mdefine_line|#define MSR_IA32_APICBASE&t;&t;0x1b
DECL|macro|MSR_IA32_APICBASE_BSP
mdefine_line|#define MSR_IA32_APICBASE_BSP&t;&t;(1&lt;&lt;8)
DECL|macro|MSR_IA32_APICBASE_ENABLE
mdefine_line|#define MSR_IA32_APICBASE_ENABLE&t;(1&lt;&lt;11)
DECL|macro|MSR_IA32_APICBASE_BASE
mdefine_line|#define MSR_IA32_APICBASE_BASE&t;&t;(0xfffff&lt;&lt;12)
DECL|macro|MSR_IA32_UCODE_WRITE
mdefine_line|#define MSR_IA32_UCODE_WRITE&t;&t;0x79
DECL|macro|MSR_IA32_UCODE_REV
mdefine_line|#define MSR_IA32_UCODE_REV&t;&t;0x8b
DECL|macro|MSR_IA32_PERFCTR0
mdefine_line|#define MSR_IA32_PERFCTR0&t;&t;0xc1
DECL|macro|MSR_IA32_PERFCTR1
mdefine_line|#define MSR_IA32_PERFCTR1&t;&t;0xc2
DECL|macro|MSR_IA32_BBL_CR_CTL
mdefine_line|#define MSR_IA32_BBL_CR_CTL&t;&t;0x119
DECL|macro|MSR_IA32_MCG_CAP
mdefine_line|#define MSR_IA32_MCG_CAP&t;&t;0x179
DECL|macro|MSR_IA32_MCG_STATUS
mdefine_line|#define MSR_IA32_MCG_STATUS&t;&t;0x17a
DECL|macro|MSR_IA32_MCG_CTL
mdefine_line|#define MSR_IA32_MCG_CTL&t;&t;0x17b
DECL|macro|MSR_IA32_EVNTSEL0
mdefine_line|#define MSR_IA32_EVNTSEL0&t;&t;0x186
DECL|macro|MSR_IA32_EVNTSEL1
mdefine_line|#define MSR_IA32_EVNTSEL1&t;&t;0x187
DECL|macro|MSR_IA32_DEBUGCTLMSR
mdefine_line|#define MSR_IA32_DEBUGCTLMSR&t;&t;0x1d9
DECL|macro|MSR_IA32_LASTBRANCHFROMIP
mdefine_line|#define MSR_IA32_LASTBRANCHFROMIP&t;0x1db
DECL|macro|MSR_IA32_LASTBRANCHTOIP
mdefine_line|#define MSR_IA32_LASTBRANCHTOIP&t;&t;0x1dc
DECL|macro|MSR_IA32_LASTINTFROMIP
mdefine_line|#define MSR_IA32_LASTINTFROMIP&t;&t;0x1dd
DECL|macro|MSR_IA32_LASTINTTOIP
mdefine_line|#define MSR_IA32_LASTINTTOIP&t;&t;0x1de
DECL|macro|MSR_IA32_MC0_CTL
mdefine_line|#define MSR_IA32_MC0_CTL&t;&t;0x400
DECL|macro|MSR_IA32_MC0_STATUS
mdefine_line|#define MSR_IA32_MC0_STATUS&t;&t;0x401
DECL|macro|MSR_IA32_MC0_ADDR
mdefine_line|#define MSR_IA32_MC0_ADDR&t;&t;0x402
DECL|macro|MSR_IA32_MC0_MISC
mdefine_line|#define MSR_IA32_MC0_MISC&t;&t;0x403
multiline_comment|/* AMD Defined MSRs */
DECL|macro|MSR_K6_EFER
mdefine_line|#define MSR_K6_EFER&t;&t;&t;0xC0000080
DECL|macro|MSR_K6_STAR
mdefine_line|#define MSR_K6_STAR&t;&t;&t;0xC0000081
DECL|macro|MSR_K6_WHCR
mdefine_line|#define MSR_K6_WHCR&t;&t;&t;0xC0000082
DECL|macro|MSR_K6_UWCCR
mdefine_line|#define MSR_K6_UWCCR&t;&t;&t;0xC0000085
DECL|macro|MSR_K6_PSOR
mdefine_line|#define MSR_K6_PSOR&t;&t;&t;0xC0000087
DECL|macro|MSR_K6_PFIR
mdefine_line|#define MSR_K6_PFIR&t;&t;&t;0xC0000088
DECL|macro|MSR_K7_EVNTSEL0
mdefine_line|#define MSR_K7_EVNTSEL0&t;&t;&t;0xC0010000
DECL|macro|MSR_K7_PERFCTR0
mdefine_line|#define MSR_K7_PERFCTR0&t;&t;&t;0xC0010004
DECL|macro|MSR_K7_HWCR
mdefine_line|#define MSR_K7_HWCR&t;&t;&t;0xC0010015
multiline_comment|/* Centaur-Hauls/IDT defined MSRs. */
DECL|macro|MSR_IDT_FCR1
mdefine_line|#define MSR_IDT_FCR1&t;&t;&t;0x107
DECL|macro|MSR_IDT_FCR2
mdefine_line|#define MSR_IDT_FCR2&t;&t;&t;0x108
DECL|macro|MSR_IDT_FCR3
mdefine_line|#define MSR_IDT_FCR3&t;&t;&t;0x109
DECL|macro|MSR_IDT_FCR4
mdefine_line|#define MSR_IDT_FCR4&t;&t;&t;0x10a
DECL|macro|MSR_IDT_MCR0
mdefine_line|#define MSR_IDT_MCR0&t;&t;&t;0x110
DECL|macro|MSR_IDT_MCR1
mdefine_line|#define MSR_IDT_MCR1&t;&t;&t;0x111
DECL|macro|MSR_IDT_MCR2
mdefine_line|#define MSR_IDT_MCR2&t;&t;&t;0x112
DECL|macro|MSR_IDT_MCR3
mdefine_line|#define MSR_IDT_MCR3&t;&t;&t;0x113
DECL|macro|MSR_IDT_MCR4
mdefine_line|#define MSR_IDT_MCR4&t;&t;&t;0x114
DECL|macro|MSR_IDT_MCR5
mdefine_line|#define MSR_IDT_MCR5&t;&t;&t;0x115
DECL|macro|MSR_IDT_MCR6
mdefine_line|#define MSR_IDT_MCR6&t;&t;&t;0x116
DECL|macro|MSR_IDT_MCR7
mdefine_line|#define MSR_IDT_MCR7&t;&t;&t;0x117
DECL|macro|MSR_IDT_MCR_CTRL
mdefine_line|#define MSR_IDT_MCR_CTRL&t;&t;0x120
multiline_comment|/* VIA Cyrix defined MSRs*/
DECL|macro|MSR_VIA_FCR
mdefine_line|#define MSR_VIA_FCR&t;&t;&t;0x1107
macro_line|#endif /* __ASM_MSR_H */
eof
