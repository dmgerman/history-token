macro_line|#ifndef X86_64_MSR_H
DECL|macro|X86_64_MSR_H
mdefine_line|#define X86_64_MSR_H 1
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Access to machine-specific registers (available on 586 and better only)&n; * Note: the rd* operations modify the parameters directly (without using&n; * pointer indirection), this allows gcc to optimize better&n; */
DECL|macro|rdmsr
mdefine_line|#define rdmsr(msr,val1,val2) &bslash;&n;       __asm__ __volatile__(&quot;rdmsr&quot; &bslash;&n;&t;&t;&t;    : &quot;=a&quot; (val1), &quot;=d&quot; (val2) &bslash;&n;&t;&t;&t;    : &quot;c&quot; (msr))
DECL|macro|rdmsrl
mdefine_line|#define rdmsrl(msr,val) do { unsigned long a__,b__; &bslash;&n;       __asm__ __volatile__(&quot;rdmsr&quot; &bslash;&n;&t;&t;&t;    : &quot;=a&quot; (a__), &quot;=d&quot; (b__) &bslash;&n;&t;&t;&t;    : &quot;c&quot; (msr)); &bslash;&n;       val = a__ | (b__&lt;&lt;32); &bslash;&n;} while(0); 
DECL|macro|wrmsr
mdefine_line|#define wrmsr(msr,val1,val2) &bslash;&n;     __asm__ __volatile__(&quot;wrmsr&quot; &bslash;&n;&t;&t;&t;  : /* no outputs */ &bslash;&n;&t;&t;&t;  : &quot;c&quot; (msr), &quot;a&quot; (val1), &quot;d&quot; (val2))
DECL|macro|wrmsrl
mdefine_line|#define wrmsrl(msr,val) wrmsr(msr,(__u32)((__u64)(val)),((__u64)(val))&gt;&gt;32) 
multiline_comment|/* wrmsrl with exception handling */
DECL|macro|checking_wrmsrl
mdefine_line|#define checking_wrmsrl(msr,val) ({ int ret__;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile(&quot;2: wrmsr ; xorl %0,%0&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;1:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;3:  movl %4,%0 ; jmp 1b&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; &t;&t;     &quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;   .align 8&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;   .quad &t;2b,3b&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;.previous&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     : &quot;=a&quot; (ret__)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     : &quot;c&quot; (msr), &quot;0&quot; ((__u32)val), &quot;d&quot; ((val)&gt;&gt;32), &quot;i&quot; (-EFAULT));&bslash;&n;&t;ret__; })
DECL|macro|rdtsc
mdefine_line|#define rdtsc(low,high) &bslash;&n;     __asm__ __volatile__(&quot;rdtsc&quot; : &quot;=a&quot; (low), &quot;=d&quot; (high))
DECL|macro|rdtscl
mdefine_line|#define rdtscl(low) &bslash;&n;     __asm__ __volatile__ (&quot;rdtsc&quot; : &quot;=a&quot; (low) : : &quot;edx&quot;)
DECL|macro|rdtscll
mdefine_line|#define rdtscll(val) do { &bslash;&n;     unsigned int a,d; &bslash;&n;     asm volatile(&quot;rdtsc&quot; : &quot;=a&quot; (a), &quot;=d&quot; (d)); &bslash;&n;     (val) = ((unsigned long)a) | (((unsigned long)d)&lt;&lt;32); &bslash;&n;} while(0)
DECL|macro|rdpmc
mdefine_line|#define rdpmc(counter,low,high) &bslash;&n;     __asm__ __volatile__(&quot;rdpmc&quot; &bslash;&n;&t;&t;&t;  : &quot;=a&quot; (low), &quot;=d&quot; (high) &bslash;&n;&t;&t;&t;  : &quot;c&quot; (counter))
DECL|macro|write_tsc
mdefine_line|#define write_tsc(val1,val2) wrmsr(0x10, val1, val2)
DECL|macro|rdpmc
mdefine_line|#define rdpmc(counter,low,high) &bslash;&n;     __asm__ __volatile__(&quot;rdpmc&quot; &bslash;&n;&t;&t;&t;  : &quot;=a&quot; (low), &quot;=d&quot; (high) &bslash;&n;&t;&t;&t;  : &quot;c&quot; (counter))
macro_line|#endif
multiline_comment|/* AMD/K8 specific MSRs */
DECL|macro|MSR_EFER
mdefine_line|#define MSR_EFER 0xc0000080&t;&t;/* extended feature register */
DECL|macro|MSR_STAR
mdefine_line|#define MSR_STAR 0xc0000081&t;&t;/* legacy mode SYSCALL target */
DECL|macro|MSR_LSTAR
mdefine_line|#define MSR_LSTAR 0xc0000082 &t;&t;/* long mode SYSCALL target */
DECL|macro|MSR_CSTAR
mdefine_line|#define MSR_CSTAR 0xc0000083&t;&t;/* compatibility mode SYSCALL target */
DECL|macro|MSR_SYSCALL_MASK
mdefine_line|#define MSR_SYSCALL_MASK 0xc0000084&t;/* EFLAGS mask for syscall */
DECL|macro|MSR_FS_BASE
mdefine_line|#define MSR_FS_BASE 0xc0000100&t;&t;/* 64bit GS base */
DECL|macro|MSR_GS_BASE
mdefine_line|#define MSR_GS_BASE 0xc0000101&t;&t;/* 64bit FS base */
DECL|macro|MSR_KERNEL_GS_BASE
mdefine_line|#define MSR_KERNEL_GS_BASE  0xc0000102&t;/* SwapGS GS shadow (or USER_GS from kernel) */ 
multiline_comment|/* EFER bits: */
DECL|macro|_EFER_SCE
mdefine_line|#define _EFER_SCE 0  /* SYSCALL/SYSRET */
DECL|macro|_EFER_LME
mdefine_line|#define _EFER_LME 8  /* Long mode enable */
DECL|macro|_EFER_LMA
mdefine_line|#define _EFER_LMA 10 /* Long mode active (read-only) */
DECL|macro|_EFER_NX
mdefine_line|#define _EFER_NX 11  /* No execute enable */
DECL|macro|EFER_SCE
mdefine_line|#define EFER_SCE (1&lt;&lt;_EFER_SCE)
DECL|macro|EFER_LME
mdefine_line|#define EFER_LME (1&lt;&lt;EFER_LME)
DECL|macro|EFER_LMA
mdefine_line|#define EFER_LMA (1&lt;&lt;EFER_LMA)
DECL|macro|EFER_NX
mdefine_line|#define EFER_NX (1&lt;&lt;_EFER_NX)
multiline_comment|/* Intel MSRs. Some also available on other CPUs */
DECL|macro|MSR_IA32_PLATFORM_ID
mdefine_line|#define MSR_IA32_PLATFORM_ID&t;0x17
DECL|macro|MSR_IA32_PERFCTR0
mdefine_line|#define MSR_IA32_PERFCTR0      0xc1
DECL|macro|MSR_IA32_PERFCTR1
mdefine_line|#define MSR_IA32_PERFCTR1      0xc2
DECL|macro|MSR_IA32_BBL_CR_CTL
mdefine_line|#define MSR_IA32_BBL_CR_CTL        0x119
DECL|macro|MSR_IA32_MCG_CAP
mdefine_line|#define MSR_IA32_MCG_CAP       0x179
DECL|macro|MSR_IA32_MCG_STATUS
mdefine_line|#define MSR_IA32_MCG_STATUS        0x17a
DECL|macro|MSR_IA32_MCG_CTL
mdefine_line|#define MSR_IA32_MCG_CTL       0x17b
DECL|macro|MSR_IA32_EVNTSEL0
mdefine_line|#define MSR_IA32_EVNTSEL0      0x186
DECL|macro|MSR_IA32_EVNTSEL1
mdefine_line|#define MSR_IA32_EVNTSEL1      0x187
DECL|macro|MSR_IA32_DEBUGCTLMSR
mdefine_line|#define MSR_IA32_DEBUGCTLMSR       0x1d9
DECL|macro|MSR_IA32_LASTBRANCHFROMIP
mdefine_line|#define MSR_IA32_LASTBRANCHFROMIP  0x1db
DECL|macro|MSR_IA32_LASTBRANCHTOIP
mdefine_line|#define MSR_IA32_LASTBRANCHTOIP        0x1dc
DECL|macro|MSR_IA32_LASTINTFROMIP
mdefine_line|#define MSR_IA32_LASTINTFROMIP     0x1dd
DECL|macro|MSR_IA32_LASTINTTOIP
mdefine_line|#define MSR_IA32_LASTINTTOIP       0x1de
DECL|macro|MSR_IA32_MC0_CTL
mdefine_line|#define MSR_IA32_MC0_CTL       0x400
DECL|macro|MSR_IA32_MC0_STATUS
mdefine_line|#define MSR_IA32_MC0_STATUS        0x401
DECL|macro|MSR_IA32_MC0_ADDR
mdefine_line|#define MSR_IA32_MC0_ADDR      0x402
DECL|macro|MSR_IA32_MC0_MISC
mdefine_line|#define MSR_IA32_MC0_MISC      0x403
DECL|macro|MSR_P6_PERFCTR0
mdefine_line|#define MSR_P6_PERFCTR0&t;&t;&t;0xc1
DECL|macro|MSR_P6_PERFCTR1
mdefine_line|#define MSR_P6_PERFCTR1&t;&t;&t;0xc2
DECL|macro|MSR_P6_EVNTSEL0
mdefine_line|#define MSR_P6_EVNTSEL0&t;&t;&t;0x186
DECL|macro|MSR_P6_EVNTSEL1
mdefine_line|#define MSR_P6_EVNTSEL1&t;&t;&t;0x187
multiline_comment|/* K7/K8 MSRs. Not complete. See the architecture manual for a more complete list. */
DECL|macro|MSR_K7_EVNTSEL0
mdefine_line|#define MSR_K7_EVNTSEL0            0xC0010000
DECL|macro|MSR_K7_PERFCTR0
mdefine_line|#define MSR_K7_PERFCTR0            0xC0010004
DECL|macro|MSR_K7_EVNTSEL1
mdefine_line|#define MSR_K7_EVNTSEL1            0xC0010001
DECL|macro|MSR_K7_PERFCTR1
mdefine_line|#define MSR_K7_PERFCTR1            0xC0010005
DECL|macro|MSR_K7_EVNTSEL2
mdefine_line|#define MSR_K7_EVNTSEL2            0xC0010002
DECL|macro|MSR_K7_PERFCTR2
mdefine_line|#define MSR_K7_PERFCTR2            0xC0010006
DECL|macro|MSR_K7_EVNTSEL3
mdefine_line|#define MSR_K7_EVNTSEL3            0xC0010003
DECL|macro|MSR_K7_PERFCTR3
mdefine_line|#define MSR_K7_PERFCTR3            0xC0010007
DECL|macro|MSR_K8_TOP_MEM1
mdefine_line|#define MSR_K8_TOP_MEM1&t;&t;   0xC001001A
DECL|macro|MSR_K8_TOP_MEM2
mdefine_line|#define MSR_K8_TOP_MEM2&t;&t;   0xC001001D
DECL|macro|MSR_K8_SYSCFG
mdefine_line|#define MSR_K8_SYSCFG&t;&t;   0xC0000010&t;
multiline_comment|/* K6 MSRs */
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
mdefine_line|#define MSR_IA32_APICBASE               0x1b
DECL|macro|MSR_IA32_APICBASE_BSP
mdefine_line|#define MSR_IA32_APICBASE_BSP           (1&lt;&lt;8)
DECL|macro|MSR_IA32_APICBASE_ENABLE
mdefine_line|#define MSR_IA32_APICBASE_ENABLE        (1&lt;&lt;11)
DECL|macro|MSR_IA32_APICBASE_BASE
mdefine_line|#define MSR_IA32_APICBASE_BASE          (0xfffff&lt;&lt;12)
DECL|macro|MSR_IA32_THERM_CONTROL
mdefine_line|#define MSR_IA32_THERM_CONTROL&t;&t;0x19a
DECL|macro|MSR_IA32_THERM_INTERRUPT
mdefine_line|#define MSR_IA32_THERM_INTERRUPT&t;0x19b
DECL|macro|MSR_IA32_THERM_STATUS
mdefine_line|#define MSR_IA32_THERM_STATUS&t;&t;0x19c
DECL|macro|MSR_IA32_MISC_ENABLE
mdefine_line|#define MSR_IA32_MISC_ENABLE&t;&t;0x1a0
macro_line|#endif
eof
