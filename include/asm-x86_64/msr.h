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
mdefine_line|#define rdtscll(val) do { &bslash;&n;     unsigned int __a,__d; &bslash;&n;     asm volatile(&quot;rdtsc&quot; : &quot;=a&quot; (__a), &quot;=d&quot; (__d)); &bslash;&n;     (val) = ((unsigned long)__a) | (((unsigned long)__d)&lt;&lt;32); &bslash;&n;} while(0)
DECL|macro|rdpmc
mdefine_line|#define rdpmc(counter,low,high) &bslash;&n;     __asm__ __volatile__(&quot;rdpmc&quot; &bslash;&n;&t;&t;&t;  : &quot;=a&quot; (low), &quot;=d&quot; (high) &bslash;&n;&t;&t;&t;  : &quot;c&quot; (counter))
DECL|macro|write_tsc
mdefine_line|#define write_tsc(val1,val2) wrmsr(0x10, val1, val2)
DECL|macro|rdpmc
mdefine_line|#define rdpmc(counter,low,high) &bslash;&n;     __asm__ __volatile__(&quot;rdpmc&quot; &bslash;&n;&t;&t;&t;  : &quot;=a&quot; (low), &quot;=d&quot; (high) &bslash;&n;&t;&t;&t;  : &quot;c&quot; (counter))
DECL|function|cpuid
r_extern
r_inline
r_void
id|cpuid
c_func
(paren
r_int
id|op
comma
r_int
r_int
op_star
id|eax
comma
r_int
r_int
op_star
id|ebx
comma
r_int
r_int
op_star
id|ecx
comma
r_int
r_int
op_star
id|edx
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;cpuid&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
op_star
id|eax
)paren
comma
l_string|&quot;=b&quot;
(paren
op_star
id|ebx
)paren
comma
l_string|&quot;=c&quot;
(paren
op_star
id|ecx
)paren
comma
l_string|&quot;=d&quot;
(paren
op_star
id|edx
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|op
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * CPUID functions returning a single datum&n; */
DECL|function|cpuid_eax
r_extern
r_inline
r_int
r_int
id|cpuid_eax
c_func
(paren
r_int
r_int
id|op
)paren
(brace
r_int
r_int
id|eax
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;cpuid&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|eax
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|op
)paren
suffix:colon
l_string|&quot;bx&quot;
comma
l_string|&quot;cx&quot;
comma
l_string|&quot;dx&quot;
)paren
suffix:semicolon
r_return
id|eax
suffix:semicolon
)brace
DECL|function|cpuid_ebx
r_extern
r_inline
r_int
r_int
id|cpuid_ebx
c_func
(paren
r_int
r_int
id|op
)paren
(brace
r_int
r_int
id|eax
comma
id|ebx
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;cpuid&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;=b&quot;
(paren
id|ebx
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|op
)paren
suffix:colon
l_string|&quot;cx&quot;
comma
l_string|&quot;dx&quot;
)paren
suffix:semicolon
r_return
id|ebx
suffix:semicolon
)brace
DECL|function|cpuid_ecx
r_extern
r_inline
r_int
r_int
id|cpuid_ecx
c_func
(paren
r_int
r_int
id|op
)paren
(brace
r_int
r_int
id|eax
comma
id|ecx
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;cpuid&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;=c&quot;
(paren
id|ecx
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|op
)paren
suffix:colon
l_string|&quot;bx&quot;
comma
l_string|&quot;dx&quot;
)paren
suffix:semicolon
r_return
id|ecx
suffix:semicolon
)brace
DECL|function|cpuid_edx
r_extern
r_inline
r_int
r_int
id|cpuid_edx
c_func
(paren
r_int
r_int
id|op
)paren
(brace
r_int
r_int
id|eax
comma
id|edx
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;cpuid&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;=d&quot;
(paren
id|edx
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|op
)paren
suffix:colon
l_string|&quot;bx&quot;
comma
l_string|&quot;cx&quot;
)paren
suffix:semicolon
r_return
id|edx
suffix:semicolon
)brace
DECL|macro|MSR_IA32_UCODE_WRITE
mdefine_line|#define MSR_IA32_UCODE_WRITE&t;&t;0x79
DECL|macro|MSR_IA32_UCODE_REV
mdefine_line|#define MSR_IA32_UCODE_REV&t;&t;0x8b
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
mdefine_line|#define EFER_LME (1&lt;&lt;_EFER_LME)
DECL|macro|EFER_LMA
mdefine_line|#define EFER_LMA (1&lt;&lt;_EFER_LMA)
DECL|macro|EFER_NX
mdefine_line|#define EFER_NX (1&lt;&lt;_EFER_NX)
multiline_comment|/* Intel MSRs. Some also available on other CPUs */
DECL|macro|MSR_IA32_PLATFORM_ID
mdefine_line|#define MSR_IA32_PLATFORM_ID&t;0x17
DECL|macro|MSR_IA32_PERFCTR0
mdefine_line|#define MSR_IA32_PERFCTR0      0xc1
DECL|macro|MSR_IA32_PERFCTR1
mdefine_line|#define MSR_IA32_PERFCTR1      0xc2
DECL|macro|MSR_MTRRcap
mdefine_line|#define MSR_MTRRcap&t;&t;0x0fe
DECL|macro|MSR_IA32_BBL_CR_CTL
mdefine_line|#define MSR_IA32_BBL_CR_CTL        0x119
DECL|macro|MSR_IA32_SYSENTER_CS
mdefine_line|#define MSR_IA32_SYSENTER_CS&t;0x174
DECL|macro|MSR_IA32_SYSENTER_ESP
mdefine_line|#define MSR_IA32_SYSENTER_ESP&t;0x175
DECL|macro|MSR_IA32_SYSENTER_EIP
mdefine_line|#define MSR_IA32_SYSENTER_EIP&t;0x176
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
DECL|macro|MSR_MTRRfix64K_00000
mdefine_line|#define MSR_MTRRfix64K_00000&t;0x250
DECL|macro|MSR_MTRRfix16K_80000
mdefine_line|#define MSR_MTRRfix16K_80000&t;0x258
DECL|macro|MSR_MTRRfix16K_A0000
mdefine_line|#define MSR_MTRRfix16K_A0000&t;0x259
DECL|macro|MSR_MTRRfix4K_C0000
mdefine_line|#define MSR_MTRRfix4K_C0000&t;0x268
DECL|macro|MSR_MTRRfix4K_C8000
mdefine_line|#define MSR_MTRRfix4K_C8000&t;0x269
DECL|macro|MSR_MTRRfix4K_D0000
mdefine_line|#define MSR_MTRRfix4K_D0000&t;0x26a
DECL|macro|MSR_MTRRfix4K_D8000
mdefine_line|#define MSR_MTRRfix4K_D8000&t;0x26b
DECL|macro|MSR_MTRRfix4K_E0000
mdefine_line|#define MSR_MTRRfix4K_E0000&t;0x26c
DECL|macro|MSR_MTRRfix4K_E8000
mdefine_line|#define MSR_MTRRfix4K_E8000&t;0x26d
DECL|macro|MSR_MTRRfix4K_F0000
mdefine_line|#define MSR_MTRRfix4K_F0000&t;0x26e
DECL|macro|MSR_MTRRfix4K_F8000
mdefine_line|#define MSR_MTRRfix4K_F8000&t;0x26f
DECL|macro|MSR_MTRRdefType
mdefine_line|#define MSR_MTRRdefType&t;&t;0x2ff
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
DECL|macro|MSR_VIA_LONGHAUL
mdefine_line|#define MSR_VIA_LONGHAUL&t;&t;0x110a
DECL|macro|MSR_VIA_RNG
mdefine_line|#define MSR_VIA_RNG&t;&t;&t;0x110b
DECL|macro|MSR_VIA_BCR2
mdefine_line|#define MSR_VIA_BCR2&t;&t;&t;0x1147
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
macro_line|#endif
eof
