macro_line|#ifndef __ASM_MSR_H
DECL|macro|__ASM_MSR_H
mdefine_line|#define __ASM_MSR_H
multiline_comment|/*&n; * Access to machine-specific registers (available on 586 and better only)&n; * Note: the rd* operations modify the parameters directly (without using&n; * pointer indirection), this allows gcc to optimize better&n; */
DECL|macro|rdmsr
mdefine_line|#define rdmsr(msr,val1,val2) &bslash;&n;&t;__asm__ __volatile__(&quot;rdmsr&quot; &bslash;&n;&t;&t;&t;  : &quot;=a&quot; (val1), &quot;=d&quot; (val2) &bslash;&n;&t;&t;&t;  : &quot;c&quot; (msr))
DECL|macro|wrmsr
mdefine_line|#define wrmsr(msr,val1,val2) &bslash;&n;&t;__asm__ __volatile__(&quot;wrmsr&quot; &bslash;&n;&t;&t;&t;  : /* no outputs */ &bslash;&n;&t;&t;&t;  : &quot;c&quot; (msr), &quot;a&quot; (val1), &quot;d&quot; (val2))
DECL|macro|rdmsrl
mdefine_line|#define rdmsrl(msr,val) do { &bslash;&n;&t;unsigned long l__,h__; &bslash;&n;&t;rdmsr (msr, l__, h__);  &bslash;&n;&t;val = l__;  &bslash;&n;&t;val |= ((u64)h__&lt;&lt;32);  &bslash;&n;} while(0)
DECL|function|wrmsrl
r_static
r_inline
r_void
id|wrmsrl
(paren
id|u32
id|msr
comma
id|u64
id|val
)paren
(brace
id|u32
id|lo
comma
id|hi
suffix:semicolon
id|lo
op_assign
(paren
id|u32
)paren
id|val
suffix:semicolon
id|hi
op_assign
id|val
op_rshift
l_int|32
suffix:semicolon
id|wrmsr
(paren
id|msr
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
)brace
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
DECL|macro|MSR_P6_PERFCTR0
mdefine_line|#define MSR_P6_PERFCTR0&t;&t;0xc1
DECL|macro|MSR_P6_PERFCTR1
mdefine_line|#define MSR_P6_PERFCTR1&t;&t;0xc2
DECL|macro|MSR_IA32_BBL_CR_CTL
mdefine_line|#define MSR_IA32_BBL_CR_CTL&t;&t;0x119
DECL|macro|MSR_IA32_SYSENTER_CS
mdefine_line|#define MSR_IA32_SYSENTER_CS&t;&t;0x174
DECL|macro|MSR_IA32_SYSENTER_ESP
mdefine_line|#define MSR_IA32_SYSENTER_ESP&t;&t;0x175
DECL|macro|MSR_IA32_SYSENTER_EIP
mdefine_line|#define MSR_IA32_SYSENTER_EIP&t;&t;0x176
DECL|macro|MSR_IA32_MCG_CAP
mdefine_line|#define MSR_IA32_MCG_CAP&t;&t;0x179
DECL|macro|MSR_IA32_MCG_STATUS
mdefine_line|#define MSR_IA32_MCG_STATUS&t;&t;0x17a
DECL|macro|MSR_IA32_MCG_CTL
mdefine_line|#define MSR_IA32_MCG_CTL&t;&t;0x17b
multiline_comment|/* P4/Xeon+ specific */
DECL|macro|MSR_IA32_MCG_EAX
mdefine_line|#define MSR_IA32_MCG_EAX&t;&t;0x180
DECL|macro|MSR_IA32_MCG_EBX
mdefine_line|#define MSR_IA32_MCG_EBX&t;&t;0x181
DECL|macro|MSR_IA32_MCG_ECX
mdefine_line|#define MSR_IA32_MCG_ECX&t;&t;0x182
DECL|macro|MSR_IA32_MCG_EDX
mdefine_line|#define MSR_IA32_MCG_EDX&t;&t;0x183
DECL|macro|MSR_IA32_MCG_ESI
mdefine_line|#define MSR_IA32_MCG_ESI&t;&t;0x184
DECL|macro|MSR_IA32_MCG_EDI
mdefine_line|#define MSR_IA32_MCG_EDI&t;&t;0x185
DECL|macro|MSR_IA32_MCG_EBP
mdefine_line|#define MSR_IA32_MCG_EBP&t;&t;0x186
DECL|macro|MSR_IA32_MCG_ESP
mdefine_line|#define MSR_IA32_MCG_ESP&t;&t;0x187
DECL|macro|MSR_IA32_MCG_EFLAGS
mdefine_line|#define MSR_IA32_MCG_EFLAGS&t;&t;0x188
DECL|macro|MSR_IA32_MCG_EIP
mdefine_line|#define MSR_IA32_MCG_EIP&t;&t;0x189
DECL|macro|MSR_IA32_MCG_RESERVED
mdefine_line|#define MSR_IA32_MCG_RESERVED&t;&t;0x18A
DECL|macro|MSR_P6_EVNTSEL0
mdefine_line|#define MSR_P6_EVNTSEL0&t;&t;&t;0x186
DECL|macro|MSR_P6_EVNTSEL1
mdefine_line|#define MSR_P6_EVNTSEL1&t;&t;&t;0x187
DECL|macro|MSR_IA32_PERF_STATUS
mdefine_line|#define MSR_IA32_PERF_STATUS&t;&t;0x198
DECL|macro|MSR_IA32_PERF_CTL
mdefine_line|#define MSR_IA32_PERF_CTL&t;&t;0x199
DECL|macro|MSR_IA32_THERM_CONTROL
mdefine_line|#define MSR_IA32_THERM_CONTROL&t;&t;0x19a
DECL|macro|MSR_IA32_THERM_INTERRUPT
mdefine_line|#define MSR_IA32_THERM_INTERRUPT&t;0x19b
DECL|macro|MSR_IA32_THERM_STATUS
mdefine_line|#define MSR_IA32_THERM_STATUS&t;&t;0x19c
DECL|macro|MSR_IA32_MISC_ENABLE
mdefine_line|#define MSR_IA32_MISC_ENABLE&t;&t;0x1a0
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
multiline_comment|/* Pentium IV performance counter MSRs */
DECL|macro|MSR_P4_BPU_PERFCTR0
mdefine_line|#define MSR_P4_BPU_PERFCTR0 &t;&t;0x300
DECL|macro|MSR_P4_BPU_PERFCTR1
mdefine_line|#define MSR_P4_BPU_PERFCTR1 &t;&t;0x301
DECL|macro|MSR_P4_BPU_PERFCTR2
mdefine_line|#define MSR_P4_BPU_PERFCTR2 &t;&t;0x302
DECL|macro|MSR_P4_BPU_PERFCTR3
mdefine_line|#define MSR_P4_BPU_PERFCTR3 &t;&t;0x303
DECL|macro|MSR_P4_MS_PERFCTR0
mdefine_line|#define MSR_P4_MS_PERFCTR0 &t;&t;0x304
DECL|macro|MSR_P4_MS_PERFCTR1
mdefine_line|#define MSR_P4_MS_PERFCTR1 &t;&t;0x305
DECL|macro|MSR_P4_MS_PERFCTR2
mdefine_line|#define MSR_P4_MS_PERFCTR2 &t;&t;0x306
DECL|macro|MSR_P4_MS_PERFCTR3
mdefine_line|#define MSR_P4_MS_PERFCTR3 &t;&t;0x307
DECL|macro|MSR_P4_FLAME_PERFCTR0
mdefine_line|#define MSR_P4_FLAME_PERFCTR0 &t;&t;0x308
DECL|macro|MSR_P4_FLAME_PERFCTR1
mdefine_line|#define MSR_P4_FLAME_PERFCTR1 &t;&t;0x309
DECL|macro|MSR_P4_FLAME_PERFCTR2
mdefine_line|#define MSR_P4_FLAME_PERFCTR2 &t;&t;0x30a
DECL|macro|MSR_P4_FLAME_PERFCTR3
mdefine_line|#define MSR_P4_FLAME_PERFCTR3 &t;&t;0x30b
DECL|macro|MSR_P4_IQ_PERFCTR0
mdefine_line|#define MSR_P4_IQ_PERFCTR0 &t;&t;0x30c
DECL|macro|MSR_P4_IQ_PERFCTR1
mdefine_line|#define MSR_P4_IQ_PERFCTR1 &t;&t;0x30d
DECL|macro|MSR_P4_IQ_PERFCTR2
mdefine_line|#define MSR_P4_IQ_PERFCTR2 &t;&t;0x30e
DECL|macro|MSR_P4_IQ_PERFCTR3
mdefine_line|#define MSR_P4_IQ_PERFCTR3 &t;&t;0x30f
DECL|macro|MSR_P4_IQ_PERFCTR4
mdefine_line|#define MSR_P4_IQ_PERFCTR4 &t;&t;0x310
DECL|macro|MSR_P4_IQ_PERFCTR5
mdefine_line|#define MSR_P4_IQ_PERFCTR5 &t;&t;0x311
DECL|macro|MSR_P4_BPU_CCCR0
mdefine_line|#define MSR_P4_BPU_CCCR0 &t;&t;0x360
DECL|macro|MSR_P4_BPU_CCCR1
mdefine_line|#define MSR_P4_BPU_CCCR1 &t;&t;0x361
DECL|macro|MSR_P4_BPU_CCCR2
mdefine_line|#define MSR_P4_BPU_CCCR2 &t;&t;0x362
DECL|macro|MSR_P4_BPU_CCCR3
mdefine_line|#define MSR_P4_BPU_CCCR3 &t;&t;0x363
DECL|macro|MSR_P4_MS_CCCR0
mdefine_line|#define MSR_P4_MS_CCCR0 &t;&t;0x364
DECL|macro|MSR_P4_MS_CCCR1
mdefine_line|#define MSR_P4_MS_CCCR1 &t;&t;0x365
DECL|macro|MSR_P4_MS_CCCR2
mdefine_line|#define MSR_P4_MS_CCCR2 &t;&t;0x366
DECL|macro|MSR_P4_MS_CCCR3
mdefine_line|#define MSR_P4_MS_CCCR3 &t;&t;0x367
DECL|macro|MSR_P4_FLAME_CCCR0
mdefine_line|#define MSR_P4_FLAME_CCCR0 &t;&t;0x368
DECL|macro|MSR_P4_FLAME_CCCR1
mdefine_line|#define MSR_P4_FLAME_CCCR1 &t;&t;0x369
DECL|macro|MSR_P4_FLAME_CCCR2
mdefine_line|#define MSR_P4_FLAME_CCCR2 &t;&t;0x36a
DECL|macro|MSR_P4_FLAME_CCCR3
mdefine_line|#define MSR_P4_FLAME_CCCR3 &t;&t;0x36b
DECL|macro|MSR_P4_IQ_CCCR0
mdefine_line|#define MSR_P4_IQ_CCCR0 &t;&t;0x36c
DECL|macro|MSR_P4_IQ_CCCR1
mdefine_line|#define MSR_P4_IQ_CCCR1 &t;&t;0x36d
DECL|macro|MSR_P4_IQ_CCCR2
mdefine_line|#define MSR_P4_IQ_CCCR2 &t;&t;0x36e
DECL|macro|MSR_P4_IQ_CCCR3
mdefine_line|#define MSR_P4_IQ_CCCR3 &t;&t;0x36f
DECL|macro|MSR_P4_IQ_CCCR4
mdefine_line|#define MSR_P4_IQ_CCCR4 &t;&t;0x370
DECL|macro|MSR_P4_IQ_CCCR5
mdefine_line|#define MSR_P4_IQ_CCCR5 &t;&t;0x371
DECL|macro|MSR_P4_ALF_ESCR0
mdefine_line|#define MSR_P4_ALF_ESCR0 &t;&t;0x3ca
DECL|macro|MSR_P4_ALF_ESCR1
mdefine_line|#define MSR_P4_ALF_ESCR1 &t;&t;0x3cb
DECL|macro|MSR_P4_BPU_ESCR0
mdefine_line|#define MSR_P4_BPU_ESCR0 &t;&t;0x3b2
DECL|macro|MSR_P4_BPU_ESCR1
mdefine_line|#define MSR_P4_BPU_ESCR1 &t;&t;0x3b3
DECL|macro|MSR_P4_BSU_ESCR0
mdefine_line|#define MSR_P4_BSU_ESCR0 &t;&t;0x3a0
DECL|macro|MSR_P4_BSU_ESCR1
mdefine_line|#define MSR_P4_BSU_ESCR1 &t;&t;0x3a1
DECL|macro|MSR_P4_CRU_ESCR0
mdefine_line|#define MSR_P4_CRU_ESCR0 &t;&t;0x3b8
DECL|macro|MSR_P4_CRU_ESCR1
mdefine_line|#define MSR_P4_CRU_ESCR1 &t;&t;0x3b9
DECL|macro|MSR_P4_CRU_ESCR2
mdefine_line|#define MSR_P4_CRU_ESCR2 &t;&t;0x3cc
DECL|macro|MSR_P4_CRU_ESCR3
mdefine_line|#define MSR_P4_CRU_ESCR3 &t;&t;0x3cd
DECL|macro|MSR_P4_CRU_ESCR4
mdefine_line|#define MSR_P4_CRU_ESCR4 &t;&t;0x3e0
DECL|macro|MSR_P4_CRU_ESCR5
mdefine_line|#define MSR_P4_CRU_ESCR5 &t;&t;0x3e1
DECL|macro|MSR_P4_DAC_ESCR0
mdefine_line|#define MSR_P4_DAC_ESCR0 &t;&t;0x3a8
DECL|macro|MSR_P4_DAC_ESCR1
mdefine_line|#define MSR_P4_DAC_ESCR1 &t;&t;0x3a9
DECL|macro|MSR_P4_FIRM_ESCR0
mdefine_line|#define MSR_P4_FIRM_ESCR0 &t;&t;0x3a4
DECL|macro|MSR_P4_FIRM_ESCR1
mdefine_line|#define MSR_P4_FIRM_ESCR1 &t;&t;0x3a5
DECL|macro|MSR_P4_FLAME_ESCR0
mdefine_line|#define MSR_P4_FLAME_ESCR0 &t;&t;0x3a6
DECL|macro|MSR_P4_FLAME_ESCR1
mdefine_line|#define MSR_P4_FLAME_ESCR1 &t;&t;0x3a7
DECL|macro|MSR_P4_FSB_ESCR0
mdefine_line|#define MSR_P4_FSB_ESCR0 &t;&t;0x3a2
DECL|macro|MSR_P4_FSB_ESCR1
mdefine_line|#define MSR_P4_FSB_ESCR1 &t;&t;0x3a3
DECL|macro|MSR_P4_IQ_ESCR0
mdefine_line|#define MSR_P4_IQ_ESCR0 &t;&t;0x3ba
DECL|macro|MSR_P4_IQ_ESCR1
mdefine_line|#define MSR_P4_IQ_ESCR1 &t;&t;0x3bb
DECL|macro|MSR_P4_IS_ESCR0
mdefine_line|#define MSR_P4_IS_ESCR0 &t;&t;0x3b4
DECL|macro|MSR_P4_IS_ESCR1
mdefine_line|#define MSR_P4_IS_ESCR1 &t;&t;0x3b5
DECL|macro|MSR_P4_ITLB_ESCR0
mdefine_line|#define MSR_P4_ITLB_ESCR0 &t;&t;0x3b6
DECL|macro|MSR_P4_ITLB_ESCR1
mdefine_line|#define MSR_P4_ITLB_ESCR1 &t;&t;0x3b7
DECL|macro|MSR_P4_IX_ESCR0
mdefine_line|#define MSR_P4_IX_ESCR0 &t;&t;0x3c8
DECL|macro|MSR_P4_IX_ESCR1
mdefine_line|#define MSR_P4_IX_ESCR1 &t;&t;0x3c9
DECL|macro|MSR_P4_MOB_ESCR0
mdefine_line|#define MSR_P4_MOB_ESCR0 &t;&t;0x3aa
DECL|macro|MSR_P4_MOB_ESCR1
mdefine_line|#define MSR_P4_MOB_ESCR1 &t;&t;0x3ab
DECL|macro|MSR_P4_MS_ESCR0
mdefine_line|#define MSR_P4_MS_ESCR0 &t;&t;0x3c0
DECL|macro|MSR_P4_MS_ESCR1
mdefine_line|#define MSR_P4_MS_ESCR1 &t;&t;0x3c1
DECL|macro|MSR_P4_PMH_ESCR0
mdefine_line|#define MSR_P4_PMH_ESCR0 &t;&t;0x3ac
DECL|macro|MSR_P4_PMH_ESCR1
mdefine_line|#define MSR_P4_PMH_ESCR1 &t;&t;0x3ad
DECL|macro|MSR_P4_RAT_ESCR0
mdefine_line|#define MSR_P4_RAT_ESCR0 &t;&t;0x3bc
DECL|macro|MSR_P4_RAT_ESCR1
mdefine_line|#define MSR_P4_RAT_ESCR1 &t;&t;0x3bd
DECL|macro|MSR_P4_SAAT_ESCR0
mdefine_line|#define MSR_P4_SAAT_ESCR0 &t;&t;0x3ae
DECL|macro|MSR_P4_SAAT_ESCR1
mdefine_line|#define MSR_P4_SAAT_ESCR1 &t;&t;0x3af
DECL|macro|MSR_P4_SSU_ESCR0
mdefine_line|#define MSR_P4_SSU_ESCR0 &t;&t;0x3be
DECL|macro|MSR_P4_SSU_ESCR1
mdefine_line|#define MSR_P4_SSU_ESCR1 &t;&t;0x3bf    /* guess: not defined in manual */
DECL|macro|MSR_P4_TBPU_ESCR0
mdefine_line|#define MSR_P4_TBPU_ESCR0 &t;&t;0x3c2
DECL|macro|MSR_P4_TBPU_ESCR1
mdefine_line|#define MSR_P4_TBPU_ESCR1 &t;&t;0x3c3
DECL|macro|MSR_P4_TC_ESCR0
mdefine_line|#define MSR_P4_TC_ESCR0 &t;&t;0x3c4
DECL|macro|MSR_P4_TC_ESCR1
mdefine_line|#define MSR_P4_TC_ESCR1 &t;&t;0x3c5
DECL|macro|MSR_P4_U2L_ESCR0
mdefine_line|#define MSR_P4_U2L_ESCR0 &t;&t;0x3b0
DECL|macro|MSR_P4_U2L_ESCR1
mdefine_line|#define MSR_P4_U2L_ESCR1 &t;&t;0x3b1
multiline_comment|/* AMD Defined MSRs */
DECL|macro|MSR_K6_EFER
mdefine_line|#define MSR_K6_EFER&t;&t;&t;0xC0000080
DECL|macro|MSR_K6_STAR
mdefine_line|#define MSR_K6_STAR&t;&t;&t;0xC0000081
DECL|macro|MSR_K6_WHCR
mdefine_line|#define MSR_K6_WHCR&t;&t;&t;0xC0000082
DECL|macro|MSR_K6_UWCCR
mdefine_line|#define MSR_K6_UWCCR&t;&t;&t;0xC0000085
DECL|macro|MSR_K6_EPMR
mdefine_line|#define MSR_K6_EPMR&t;&t;&t;0xC0000086
DECL|macro|MSR_K6_PSOR
mdefine_line|#define MSR_K6_PSOR&t;&t;&t;0xC0000087
DECL|macro|MSR_K6_PFIR
mdefine_line|#define MSR_K6_PFIR&t;&t;&t;0xC0000088
DECL|macro|MSR_K7_EVNTSEL0
mdefine_line|#define MSR_K7_EVNTSEL0&t;&t;&t;0xC0010000
DECL|macro|MSR_K7_EVNTSEL1
mdefine_line|#define MSR_K7_EVNTSEL1&t;&t;&t;0xC0010001
DECL|macro|MSR_K7_EVNTSEL2
mdefine_line|#define MSR_K7_EVNTSEL2&t;&t;&t;0xC0010002
DECL|macro|MSR_K7_EVNTSEL3
mdefine_line|#define MSR_K7_EVNTSEL3&t;&t;&t;0xC0010003
DECL|macro|MSR_K7_PERFCTR0
mdefine_line|#define MSR_K7_PERFCTR0&t;&t;&t;0xC0010004
DECL|macro|MSR_K7_PERFCTR1
mdefine_line|#define MSR_K7_PERFCTR1&t;&t;&t;0xC0010005
DECL|macro|MSR_K7_PERFCTR2
mdefine_line|#define MSR_K7_PERFCTR2&t;&t;&t;0xC0010006
DECL|macro|MSR_K7_PERFCTR3
mdefine_line|#define MSR_K7_PERFCTR3&t;&t;&t;0xC0010007
DECL|macro|MSR_K7_HWCR
mdefine_line|#define MSR_K7_HWCR&t;&t;&t;0xC0010015
DECL|macro|MSR_K7_CLK_CTL
mdefine_line|#define MSR_K7_CLK_CTL&t;&t;&t;0xC001001b
DECL|macro|MSR_K7_FID_VID_CTL
mdefine_line|#define MSR_K7_FID_VID_CTL&t;&t;0xC0010041
DECL|macro|MSR_K7_FID_VID_STATUS
mdefine_line|#define MSR_K7_FID_VID_STATUS&t;&t;0xC0010042
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
DECL|macro|MSR_VIA_LONGHAUL
mdefine_line|#define MSR_VIA_LONGHAUL&t;&t;0x110a
DECL|macro|MSR_VIA_RNG
mdefine_line|#define MSR_VIA_RNG&t;&t;&t;0x110b
DECL|macro|MSR_VIA_BCR2
mdefine_line|#define MSR_VIA_BCR2&t;&t;&t;0x1147
multiline_comment|/* Transmeta defined MSRs */
DECL|macro|MSR_TMTA_LONGRUN_CTRL
mdefine_line|#define MSR_TMTA_LONGRUN_CTRL&t;&t;0x80868010
DECL|macro|MSR_TMTA_LONGRUN_FLAGS
mdefine_line|#define MSR_TMTA_LONGRUN_FLAGS&t;&t;0x80868011
DECL|macro|MSR_TMTA_LRTI_READOUT
mdefine_line|#define MSR_TMTA_LRTI_READOUT&t;&t;0x80868018
DECL|macro|MSR_TMTA_LRTI_VOLT_MHZ
mdefine_line|#define MSR_TMTA_LRTI_VOLT_MHZ&t;&t;0x8086801a
macro_line|#endif /* __ASM_MSR_H */
eof
