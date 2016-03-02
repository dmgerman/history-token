macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_PPC_PROCESSOR_H
DECL|macro|__ASM_PPC_PROCESSOR_H
mdefine_line|#define __ASM_PPC_PROCESSOR_H
multiline_comment|/*&n; * The Book E definitions are hacked into here for 440 right&n; * now.  This whole thing needs regorganized (maybe two files)&n; * so that it becomes readable. -Matt&n; */
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ __label__ _l; _l: &amp;&amp;_l;})
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stringify.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/mpc8xx.h&gt;
multiline_comment|/* Machine State Register (MSR) Fields */
macro_line|#ifdef CONFIG_PPC64BRIDGE
DECL|macro|MSR_SF
mdefine_line|#define MSR_SF&t;&t;(1&lt;&lt;63)
DECL|macro|MSR_ISF
mdefine_line|#define MSR_ISF&t;&t;(1&lt;&lt;61)
macro_line|#endif /* CONFIG_PPC64BRIDGE */
DECL|macro|MSR_VEC
mdefine_line|#define MSR_VEC&t;&t;(1&lt;&lt;25)&t;&t;/* Enable AltiVec */
DECL|macro|MSR_POW
mdefine_line|#define MSR_POW&t;&t;(1&lt;&lt;18)&t;&t;/* Enable Power Management */
DECL|macro|MSR_WE
mdefine_line|#define MSR_WE&t;&t;(1&lt;&lt;18)&t;&t;/* Wait State Enable */
DECL|macro|MSR_TGPR
mdefine_line|#define MSR_TGPR&t;(1&lt;&lt;17)&t;&t;/* TLB Update registers in use */
DECL|macro|MSR_CE
mdefine_line|#define MSR_CE&t;&t;(1&lt;&lt;17)&t;&t;/* Critical Interrupt Enable */
DECL|macro|MSR_ILE
mdefine_line|#define MSR_ILE&t;&t;(1&lt;&lt;16)&t;&t;/* Interrupt Little Endian */
DECL|macro|MSR_EE
mdefine_line|#define MSR_EE&t;&t;(1&lt;&lt;15)&t;&t;/* External Interrupt Enable */
DECL|macro|MSR_PR
mdefine_line|#define MSR_PR&t;&t;(1&lt;&lt;14)&t;&t;/* Problem State / Privilege Level */
DECL|macro|MSR_FP
mdefine_line|#define MSR_FP&t;&t;(1&lt;&lt;13)&t;&t;/* Floating Point enable */
DECL|macro|MSR_ME
mdefine_line|#define MSR_ME&t;&t;(1&lt;&lt;12)&t;&t;/* Machine Check Enable */
DECL|macro|MSR_FE0
mdefine_line|#define MSR_FE0&t;&t;(1&lt;&lt;11)&t;&t;/* Floating Exception mode 0 */
DECL|macro|MSR_SE
mdefine_line|#define MSR_SE&t;&t;(1&lt;&lt;10)&t;&t;/* Single Step */
DECL|macro|MSR_DWE
mdefine_line|#define MSR_DWE&t;&t;(1&lt;&lt;10)&t;&t;/* Debug Wait Enable (4xx) */
DECL|macro|MSR_BE
mdefine_line|#define MSR_BE&t;&t;(1&lt;&lt;9)&t;&t;/* Branch Trace */
DECL|macro|MSR_DE
mdefine_line|#define MSR_DE&t;&t;(1&lt;&lt;9) &t;&t;/* Debug Exception Enable */
DECL|macro|MSR_FE1
mdefine_line|#define MSR_FE1&t;&t;(1&lt;&lt;8)&t;&t;/* Floating Exception mode 1 */
DECL|macro|MSR_IP
mdefine_line|#define MSR_IP&t;&t;(1&lt;&lt;6)&t;&t;/* Exception prefix 0x000/0xFFF */
DECL|macro|MSR_IR
mdefine_line|#define MSR_IR&t;&t;(1&lt;&lt;5) &t;&t;/* Instruction Relocate */
DECL|macro|MSR_DR
mdefine_line|#define MSR_DR&t;&t;(1&lt;&lt;4) &t;&t;/* Data Relocate */
DECL|macro|MSR_PE
mdefine_line|#define MSR_PE&t;&t;(1&lt;&lt;3)&t;&t;/* Protection Enable */
DECL|macro|MSR_PX
mdefine_line|#define MSR_PX&t;&t;(1&lt;&lt;2)&t;&t;/* Protection Exclusive Mode */
DECL|macro|MSR_RI
mdefine_line|#define MSR_RI&t;&t;(1&lt;&lt;1)&t;&t;/* Recoverable Exception */
DECL|macro|MSR_LE
mdefine_line|#define MSR_LE&t;&t;(1&lt;&lt;0) &t;&t;/* Little Endian */
macro_line|#ifdef CONFIG_BOOKE
DECL|macro|MSR_IS
mdefine_line|#define MSR_IS&t;&t;MSR_IR&t;&t;/* Instruction Space */
DECL|macro|MSR_DS
mdefine_line|#define MSR_DS&t;&t;MSR_DR&t;&t;/* Data Space */
macro_line|#endif
macro_line|#ifdef CONFIG_APUS_FAST_EXCEPT
DECL|macro|MSR_
mdefine_line|#define MSR_&t;&t;(MSR_ME|MSR_IP|MSR_RI)
macro_line|#else
DECL|macro|MSR_
mdefine_line|#define MSR_&t;&t;(MSR_ME|MSR_RI)
macro_line|#endif
macro_line|#ifdef CONFIG_4xx
DECL|macro|MSR_KERNEL
mdefine_line|#define MSR_KERNEL&t;(MSR_|MSR_IR|MSR_DR|MSR_CE|MSR_DE)
macro_line|#else
DECL|macro|MSR_KERNEL
mdefine_line|#define MSR_KERNEL      (MSR_|MSR_IR|MSR_DR)
macro_line|#endif
DECL|macro|MSR_USER
mdefine_line|#define MSR_USER&t;(MSR_KERNEL|MSR_PR|MSR_EE)
multiline_comment|/* Floating Point Status and Control Register (FPSCR) Fields */
DECL|macro|FPSCR_FX
mdefine_line|#define FPSCR_FX&t;0x80000000&t;/* FPU exception summary */
DECL|macro|FPSCR_FEX
mdefine_line|#define FPSCR_FEX&t;0x40000000&t;/* FPU enabled exception summary */
DECL|macro|FPSCR_VX
mdefine_line|#define FPSCR_VX&t;0x20000000&t;/* Invalid operation summary */
DECL|macro|FPSCR_OX
mdefine_line|#define FPSCR_OX&t;0x10000000&t;/* Overflow exception summary */
DECL|macro|FPSCR_UX
mdefine_line|#define FPSCR_UX&t;0x08000000&t;/* Underflow exception summary */
DECL|macro|FPSCR_ZX
mdefine_line|#define FPSCR_ZX&t;0x04000000&t;/* Zero-devide exception summary */
DECL|macro|FPSCR_XX
mdefine_line|#define FPSCR_XX&t;0x02000000&t;/* Inexact exception summary */
DECL|macro|FPSCR_VXSNAN
mdefine_line|#define FPSCR_VXSNAN&t;0x01000000&t;/* Invalid op for SNaN */
DECL|macro|FPSCR_VXISI
mdefine_line|#define FPSCR_VXISI&t;0x00800000&t;/* Invalid op for Inv - Inv */
DECL|macro|FPSCR_VXIDI
mdefine_line|#define FPSCR_VXIDI&t;0x00400000&t;/* Invalid op for Inv / Inv */
DECL|macro|FPSCR_VXZDZ
mdefine_line|#define FPSCR_VXZDZ&t;0x00200000&t;/* Invalid op for Zero / Zero */
DECL|macro|FPSCR_VXIMZ
mdefine_line|#define FPSCR_VXIMZ&t;0x00100000&t;/* Invalid op for Inv * Zero */
DECL|macro|FPSCR_VXVC
mdefine_line|#define FPSCR_VXVC&t;0x00080000&t;/* Invalid op for Compare */
DECL|macro|FPSCR_FR
mdefine_line|#define FPSCR_FR&t;0x00040000&t;/* Fraction rounded */
DECL|macro|FPSCR_FI
mdefine_line|#define FPSCR_FI&t;0x00020000&t;/* Fraction inexact */
DECL|macro|FPSCR_FPRF
mdefine_line|#define FPSCR_FPRF&t;0x0001f000&t;/* FPU Result Flags */
DECL|macro|FPSCR_FPCC
mdefine_line|#define FPSCR_FPCC&t;0x0000f000&t;/* FPU Condition Codes */
DECL|macro|FPSCR_VXSOFT
mdefine_line|#define FPSCR_VXSOFT&t;0x00000400&t;/* Invalid op for software request */
DECL|macro|FPSCR_VXSQRT
mdefine_line|#define FPSCR_VXSQRT&t;0x00000200&t;/* Invalid op for square root */
DECL|macro|FPSCR_VXCVI
mdefine_line|#define FPSCR_VXCVI&t;0x00000100&t;/* Invalid op for integer convert */
DECL|macro|FPSCR_VE
mdefine_line|#define FPSCR_VE&t;0x00000080&t;/* Invalid op exception enable */
DECL|macro|FPSCR_OE
mdefine_line|#define FPSCR_OE&t;0x00000040&t;/* IEEE overflow exception enable */
DECL|macro|FPSCR_UE
mdefine_line|#define FPSCR_UE&t;0x00000020&t;/* IEEE underflow exception enable */
DECL|macro|FPSCR_ZE
mdefine_line|#define FPSCR_ZE&t;0x00000010&t;/* IEEE zero divide exception enable */
DECL|macro|FPSCR_XE
mdefine_line|#define FPSCR_XE&t;0x00000008&t;/* FP inexact exception enable */
DECL|macro|FPSCR_NI
mdefine_line|#define FPSCR_NI&t;0x00000004&t;/* FPU non IEEE-Mode */
DECL|macro|FPSCR_RN
mdefine_line|#define FPSCR_RN&t;0x00000003&t;/* FPU rounding control */
multiline_comment|/* Special Purpose Registers (SPRNs)*/
DECL|macro|SPRN_CCR0
mdefine_line|#define&t;SPRN_CCR0&t;0x3B3&t;/* Core Configuration Register (4xx) */
DECL|macro|SPRN_CDBCR
mdefine_line|#define&t;SPRN_CDBCR&t;0x3D7&t;/* Cache Debug Control Register */
DECL|macro|SPRN_CTR
mdefine_line|#define&t;SPRN_CTR&t;0x009&t;/* Count Register */
DECL|macro|SPRN_DABR
mdefine_line|#define&t;SPRN_DABR&t;0x3F5&t;/* Data Address Breakpoint Register */
macro_line|#ifndef CONFIG_BOOKE
DECL|macro|SPRN_DAC1
mdefine_line|#define&t;SPRN_DAC1&t;0x3F6&t;/* Data Address Compare 1 */
DECL|macro|SPRN_DAC2
mdefine_line|#define&t;SPRN_DAC2&t;0x3F7&t;/* Data Address Compare 2 */
macro_line|#else
DECL|macro|SPRN_DAC1
mdefine_line|#define&t;SPRN_DAC1&t;0x13C&t;/* Book E Data Address Compare 1 */
DECL|macro|SPRN_DAC2
mdefine_line|#define&t;SPRN_DAC2&t;0x13D&t;/* Book E Data Address Compare 2 */
macro_line|#endif /* CONFIG_BOOKE */
DECL|macro|SPRN_DAR
mdefine_line|#define&t;SPRN_DAR&t;0x013&t;/* Data Address Register */
DECL|macro|SPRN_DBAT0L
mdefine_line|#define&t;SPRN_DBAT0L&t;0x219&t;/* Data BAT 0 Lower Register */
DECL|macro|SPRN_DBAT0U
mdefine_line|#define&t;SPRN_DBAT0U&t;0x218&t;/* Data BAT 0 Upper Register */
DECL|macro|SPRN_DBAT1L
mdefine_line|#define&t;SPRN_DBAT1L&t;0x21B&t;/* Data BAT 1 Lower Register */
DECL|macro|SPRN_DBAT1U
mdefine_line|#define&t;SPRN_DBAT1U&t;0x21A&t;/* Data BAT 1 Upper Register */
DECL|macro|SPRN_DBAT2L
mdefine_line|#define&t;SPRN_DBAT2L&t;0x21D&t;/* Data BAT 2 Lower Register */
DECL|macro|SPRN_DBAT2U
mdefine_line|#define&t;SPRN_DBAT2U&t;0x21C&t;/* Data BAT 2 Upper Register */
DECL|macro|SPRN_DBAT3L
mdefine_line|#define&t;SPRN_DBAT3L&t;0x21F&t;/* Data BAT 3 Lower Register */
DECL|macro|SPRN_DBAT3U
mdefine_line|#define&t;SPRN_DBAT3U&t;0x21E&t;/* Data BAT 3 Upper Register */
DECL|macro|SPRN_DBAT4L
mdefine_line|#define&t;SPRN_DBAT4L&t;0x239&t;/* Data BAT 4 Lower Register */
DECL|macro|SPRN_DBAT4U
mdefine_line|#define&t;SPRN_DBAT4U&t;0x238&t;/* Data BAT 4 Upper Register */
DECL|macro|SPRN_DBAT5L
mdefine_line|#define&t;SPRN_DBAT5L&t;0x23B&t;/* Data BAT 5 Lower Register */
DECL|macro|SPRN_DBAT5U
mdefine_line|#define&t;SPRN_DBAT5U&t;0x23A&t;/* Data BAT 5 Upper Register */
DECL|macro|SPRN_DBAT6L
mdefine_line|#define&t;SPRN_DBAT6L&t;0x23D&t;/* Data BAT 6 Lower Register */
DECL|macro|SPRN_DBAT6U
mdefine_line|#define&t;SPRN_DBAT6U&t;0x23C&t;/* Data BAT 6 Upper Register */
DECL|macro|SPRN_DBAT7L
mdefine_line|#define&t;SPRN_DBAT7L&t;0x23F&t;/* Data BAT 7 Lower Register */
DECL|macro|SPRN_DBAT7U
mdefine_line|#define&t;SPRN_DBAT7U&t;0x23E&t;/* Data BAT 7 Upper Register */
DECL|macro|SPRN_DBCR
mdefine_line|#define&t;SPRN_DBCR&t;0x3F2&t;/* Debug Control Regsiter */
DECL|macro|DBCR_EDM
mdefine_line|#define&t;  DBCR_EDM&t;0x80000000
DECL|macro|DBCR_IDM
mdefine_line|#define&t;  DBCR_IDM&t;0x40000000
DECL|macro|DBCR_RST
mdefine_line|#define&t;  DBCR_RST(x)&t;(((x) &amp; 0x3) &lt;&lt; 28)
DECL|macro|DBCR_RST_NONE
mdefine_line|#define&t;    DBCR_RST_NONE       &t;0
DECL|macro|DBCR_RST_CORE
mdefine_line|#define&t;    DBCR_RST_CORE       &t;1
DECL|macro|DBCR_RST_CHIP
mdefine_line|#define&t;    DBCR_RST_CHIP       &t;2
DECL|macro|DBCR_RST_SYSTEM
mdefine_line|#define&t;    DBCR_RST_SYSTEM&t;&t;3
DECL|macro|DBCR_IC
mdefine_line|#define&t;  DBCR_IC&t;0x08000000&t;/* Instruction Completion Debug Evnt */
DECL|macro|DBCR_BT
mdefine_line|#define&t;  DBCR_BT&t;0x04000000&t;/* Branch Taken Debug Event */
DECL|macro|DBCR_EDE
mdefine_line|#define&t;  DBCR_EDE&t;0x02000000&t;/* Exception Debug Event */
DECL|macro|DBCR_TDE
mdefine_line|#define&t;  DBCR_TDE&t;0x01000000&t;/* TRAP Debug Event */
DECL|macro|DBCR_FER
mdefine_line|#define&t;  DBCR_FER&t;0x00F80000&t;/* First Events Remaining Mask */
DECL|macro|DBCR_FT
mdefine_line|#define&t;  DBCR_FT&t;0x00040000&t;/* Freeze Timers on Debug Event */
DECL|macro|DBCR_IA1
mdefine_line|#define&t;  DBCR_IA1&t;0x00020000&t;/* Instr. Addr. Compare 1 Enable */
DECL|macro|DBCR_IA2
mdefine_line|#define&t;  DBCR_IA2&t;0x00010000&t;/* Instr. Addr. Compare 2 Enable */
DECL|macro|DBCR_D1R
mdefine_line|#define&t;  DBCR_D1R&t;0x00008000&t;/* Data Addr. Compare 1 Read Enable */
DECL|macro|DBCR_D1W
mdefine_line|#define&t;  DBCR_D1W&t;0x00004000&t;/* Data Addr. Compare 1 Write Enable */
DECL|macro|DBCR_D1S
mdefine_line|#define&t;  DBCR_D1S(x)&t;(((x) &amp; 0x3) &lt;&lt; 12)&t;/* Data Adrr. Compare 1 Size */
DECL|macro|DAC_BYTE
mdefine_line|#define&t;    DAC_BYTE&t;0
DECL|macro|DAC_HALF
mdefine_line|#define&t;    DAC_HALF&t;1
DECL|macro|DAC_WORD
mdefine_line|#define&t;    DAC_WORD&t;2
DECL|macro|DAC_QUAD
mdefine_line|#define&t;    DAC_QUAD&t;3
DECL|macro|DBCR_D2R
mdefine_line|#define&t;  DBCR_D2R&t;0x00000800&t;/* Data Addr. Compare 2 Read Enable */
DECL|macro|DBCR_D2W
mdefine_line|#define&t;  DBCR_D2W&t;0x00000400&t;/* Data Addr. Compare 2 Write Enable */
DECL|macro|DBCR_D2S
mdefine_line|#define&t;  DBCR_D2S(x)&t;(((x) &amp; 0x3) &lt;&lt; 8)&t;/* Data Addr. Compare 2 Size */
DECL|macro|DBCR_SBT
mdefine_line|#define&t;  DBCR_SBT&t;0x00000040&t;/* Second Branch Taken Debug Event */
DECL|macro|DBCR_SED
mdefine_line|#define&t;  DBCR_SED&t;0x00000020&t;/* Second Exception Debug Event */
DECL|macro|DBCR_STD
mdefine_line|#define&t;  DBCR_STD&t;0x00000010&t;/* Second Trap Debug Event */
DECL|macro|DBCR_SIA
mdefine_line|#define&t;  DBCR_SIA&t;0x00000008&t;/* Second IAC Enable */
DECL|macro|DBCR_SDA
mdefine_line|#define&t;  DBCR_SDA&t;0x00000004&t;/* Second DAC Enable */
DECL|macro|DBCR_JOI
mdefine_line|#define&t;  DBCR_JOI&t;0x00000002&t;/* JTAG Serial Outbound Int. Enable */
DECL|macro|DBCR_JII
mdefine_line|#define&t;  DBCR_JII&t;0x00000001&t;/* JTAG Serial Inbound Int. Enable */
macro_line|#ifndef CONFIG_BOOKE
DECL|macro|SPRN_DBCR0
mdefine_line|#define&t;SPRN_DBCR0&t;0x3F2&t;/* Debug Control Register 0 */
macro_line|#else
DECL|macro|SPRN_DBCR0
mdefine_line|#define&t;SPRN_DBCR0&t;0x134&t;&t;/* Book E Debug Control Register 0 */
macro_line|#endif /* CONFIG_BOOKE */
DECL|macro|DBCR0_EDM
mdefine_line|#define   DBCR0_EDM         0x80000000  /* External Debug Mode             */
DECL|macro|DBCR0_IDM
mdefine_line|#define   DBCR0_IDM         0x40000000  /* Internal Debug Mode             */
DECL|macro|DBCR0_RST
mdefine_line|#define   DBCR0_RST         0x30000000  /* all the bits in the RST field   */
DECL|macro|DBCR0_RST_SYSTEM
mdefine_line|#define   DBCR0_RST_SYSTEM  0x30000000  /* System Reset                    */
DECL|macro|DBCR0_RST_CHIP
mdefine_line|#define   DBCR0_RST_CHIP    0x20000000  /* Chip   Reset                    */
DECL|macro|DBCR0_RST_CORE
mdefine_line|#define   DBCR0_RST_CORE    0x10000000  /* Core   Reset                    */
DECL|macro|DBCR0_RST_NONE
mdefine_line|#define   DBCR0_RST_NONE    0x00000000  /* No     Reset                    */
DECL|macro|DBCR0_IC
mdefine_line|#define   DBCR0_IC          0x08000000  /* Instruction Completion          */
DECL|macro|DBCR0_BT
mdefine_line|#define   DBCR0_BT          0x04000000  /* Branch Taken                    */
DECL|macro|DBCR0_EDE
mdefine_line|#define   DBCR0_EDE         0x02000000  /* Exception Debug Event           */
DECL|macro|DBCR0_TDE
mdefine_line|#define   DBCR0_TDE         0x01000000  /* TRAP Debug Event                */
DECL|macro|DBCR0_IA1
mdefine_line|#define   DBCR0_IA1         0x00800000  /* Instr Addr compare 1 enable     */
DECL|macro|DBCR0_IA2
mdefine_line|#define   DBCR0_IA2         0x00400000  /* Instr Addr compare 2 enable     */
DECL|macro|DBCR0_IA12
mdefine_line|#define   DBCR0_IA12        0x00200000  /* Instr Addr 1-2 range enable     */
DECL|macro|DBCR0_IA12X
mdefine_line|#define   DBCR0_IA12X       0x00100000  /* Instr Addr 1-2 range eXclusive  */
DECL|macro|DBCR0_IA3
mdefine_line|#define   DBCR0_IA3         0x00080000  /* Instr Addr compare 3 enable     */
DECL|macro|DBCR0_IA4
mdefine_line|#define   DBCR0_IA4         0x00040000  /* Instr Addr compare 4 enable     */
DECL|macro|DBCR0_IA34
mdefine_line|#define   DBCR0_IA34        0x00020000  /* Instr Addr 3-4 range Enable     */
DECL|macro|DBCR0_IA34X
mdefine_line|#define   DBCR0_IA34X       0x00010000  /* Instr Addr 3-4 range eXclusive  */
DECL|macro|DBCR0_IA12T
mdefine_line|#define   DBCR0_IA12T       0x00008000  /* Instr Addr 1-2 range Toggle     */
DECL|macro|DBCR0_IA34T
mdefine_line|#define   DBCR0_IA34T       0x00004000  /* Instr Addr 3-4 range Toggle     */
DECL|macro|DBCR0_FT
mdefine_line|#define   DBCR0_FT          0x00000001  /* Freeze Timers on debug event    */
macro_line|#ifndef CONFIG_BOOKE
DECL|macro|SPRN_DBCR1
mdefine_line|#define&t;SPRN_DBCR1&t;0x3BD&t;/* Debug Control Register 1 */&t;&t;
DECL|macro|SPRN_DBSR
mdefine_line|#define&t;SPRN_DBSR&t;0x3F0&t;/* Debug Status Register */&t;&t;
DECL|macro|DBSR_IC
mdefine_line|#define   DBSR_IC&t;    0x80000000&t;/* Instruction Completion          */
DECL|macro|DBSR_BT
mdefine_line|#define   DBSR_BT&t;    0x40000000&t;/* Branch taken */
DECL|macro|DBSR_TIE
mdefine_line|#define   DBSR_TIE&t;    0x10000000&t;/* Trap Instruction debug Event    */
macro_line|#else
DECL|macro|SPRN_DBCR1
mdefine_line|#define&t;SPRN_DBCR1&t;0x135&t;&t;/* Book E Debug Control Register 1 */
DECL|macro|SPRN_DBSR
mdefine_line|#define&t;SPRN_DBSR&t;0x130&t;&t;/* Book E Debug Status Register */
DECL|macro|DBSR_IC
mdefine_line|#define   DBSR_IC&t;    0x08000000&t;/* Book E Instruction Completion  */
DECL|macro|DBSR_TIE
mdefine_line|#define   DBSR_TIE&t;    0x01000000&t;/* Book E Trap Instruction Event */
macro_line|#endif /* CONFIG_BOOKE */
DECL|macro|SPRN_DCCR
mdefine_line|#define&t;SPRN_DCCR&t;0x3FA&t;/* Data Cache Cacheability Register */
DECL|macro|DCCR_NOCACHE
mdefine_line|#define&t;  DCCR_NOCACHE&t;&t;0&t;/* Noncacheable */
DECL|macro|DCCR_CACHE
mdefine_line|#define&t;  DCCR_CACHE&t;&t;1&t;/* Cacheable */
DECL|macro|SPRN_DCMP
mdefine_line|#define&t;SPRN_DCMP&t;0x3D1&t;/* Data TLB Compare Register */
DECL|macro|SPRN_DCWR
mdefine_line|#define&t;SPRN_DCWR&t;0x3BA&t;/* Data Cache Write-thru Register */
DECL|macro|DCWR_COPY
mdefine_line|#define&t;  DCWR_COPY&t;&t;0&t;/* Copy-back */
DECL|macro|DCWR_WRITE
mdefine_line|#define&t;  DCWR_WRITE&t;&t;1&t;/* Write-through */
macro_line|#ifndef CONFIG_BOOKE
DECL|macro|SPRN_DEAR
mdefine_line|#define&t;SPRN_DEAR&t;0x3D5&t;/* Data Error Address Register */
macro_line|#else
DECL|macro|SPRN_DEAR
mdefine_line|#define SPRN_DEAR&t;0x03D&t;/* Book E Data Error Address Register */
macro_line|#endif /* CONFIG_BOOKE */
DECL|macro|SPRN_DEC
mdefine_line|#define&t;SPRN_DEC&t;0x016&t;/* Decrement Register */
DECL|macro|SPRN_DER
mdefine_line|#define&t;SPRN_DER&t;0x095&t;/* Debug Enable Regsiter */
DECL|macro|DER_RSTE
mdefine_line|#define   DER_RSTE&t;0x40000000&t;/* Reset Interrupt */
DECL|macro|DER_CHSTPE
mdefine_line|#define   DER_CHSTPE&t;0x20000000&t;/* Check Stop */
DECL|macro|DER_MCIE
mdefine_line|#define   DER_MCIE&t;0x10000000&t;/* Machine Check Interrupt */
DECL|macro|DER_EXTIE
mdefine_line|#define   DER_EXTIE&t;0x02000000&t;/* External Interrupt */
DECL|macro|DER_ALIE
mdefine_line|#define   DER_ALIE&t;0x01000000&t;/* Alignment Interrupt */
DECL|macro|DER_PRIE
mdefine_line|#define   DER_PRIE&t;0x00800000&t;/* Program Interrupt */
DECL|macro|DER_FPUVIE
mdefine_line|#define   DER_FPUVIE&t;0x00400000&t;/* FP Unavailable Interrupt */
DECL|macro|DER_DECIE
mdefine_line|#define   DER_DECIE&t;0x00200000&t;/* Decrementer Interrupt */
DECL|macro|DER_SYSIE
mdefine_line|#define   DER_SYSIE&t;0x00040000&t;/* System Call Interrupt */
DECL|macro|DER_TRE
mdefine_line|#define   DER_TRE&t;0x00020000&t;/* Trace Interrupt */
DECL|macro|DER_SEIE
mdefine_line|#define   DER_SEIE&t;0x00004000&t;/* FP SW Emulation Interrupt */
DECL|macro|DER_ITLBMSE
mdefine_line|#define   DER_ITLBMSE&t;0x00002000&t;/* Imp. Spec. Instruction TLB Miss */
DECL|macro|DER_ITLBERE
mdefine_line|#define   DER_ITLBERE&t;0x00001000&t;/* Imp. Spec. Instruction TLB Error */
DECL|macro|DER_DTLBMSE
mdefine_line|#define   DER_DTLBMSE&t;0x00000800&t;/* Imp. Spec. Data TLB Miss */
DECL|macro|DER_DTLBERE
mdefine_line|#define   DER_DTLBERE&t;0x00000400&t;/* Imp. Spec. Data TLB Error */
DECL|macro|DER_LBRKE
mdefine_line|#define   DER_LBRKE&t;0x00000008&t;/* Load/Store Breakpoint Interrupt */
DECL|macro|DER_IBRKE
mdefine_line|#define   DER_IBRKE&t;0x00000004&t;/* Instruction Breakpoint Interrupt */
DECL|macro|DER_EBRKE
mdefine_line|#define   DER_EBRKE&t;0x00000002&t;/* External Breakpoint Interrupt */
DECL|macro|DER_DPIE
mdefine_line|#define   DER_DPIE&t;0x00000001&t;/* Dev. Port Nonmaskable Request */
DECL|macro|SPRN_DMISS
mdefine_line|#define&t;SPRN_DMISS&t;0x3D0&t;/* Data TLB Miss Register */
DECL|macro|SPRN_DSISR
mdefine_line|#define&t;SPRN_DSISR&t;0x012&t;/* Data Storage Interrupt Status Register */
DECL|macro|SPRN_EAR
mdefine_line|#define&t;SPRN_EAR&t;0x11A&t;/* External Address Register */
macro_line|#ifndef CONFIG_BOOKE
DECL|macro|SPRN_ESR
mdefine_line|#define&t;SPRN_ESR&t;0x3D4&t;/* Exception Syndrome Register */
macro_line|#else
DECL|macro|SPRN_ESR
mdefine_line|#define SPRN_ESR&t;0x03E&t;&t;/* Book E Exception Syndrome Register */
macro_line|#endif /* CONFIG_BOOKE */
DECL|macro|ESR_MCI
mdefine_line|#define&t;  ESR_MCI&t;0x80000000&t;/* 405 Machine Check - Instruction */
DECL|macro|ESR_IMCP
mdefine_line|#define&t;  ESR_IMCP&t;0x80000000&t;/* Instr. Machine Check - Protection */
DECL|macro|ESR_IMCN
mdefine_line|#define&t;  ESR_IMCN&t;0x40000000&t;/* Instr. Machine Check - Non-config */
DECL|macro|ESR_IMCB
mdefine_line|#define&t;  ESR_IMCB&t;0x20000000&t;/* Instr. Machine Check - Bus error */
DECL|macro|ESR_IMCT
mdefine_line|#define&t;  ESR_IMCT&t;0x10000000&t;/* Instr. Machine Check - Timeout */
DECL|macro|ESR_PIL
mdefine_line|#define&t;  ESR_PIL&t;0x08000000&t;/* Program Exception - Illegal */
DECL|macro|ESR_PPR
mdefine_line|#define&t;  ESR_PPR&t;0x04000000&t;/* Program Exception - Priveleged */
DECL|macro|ESR_PTR
mdefine_line|#define&t;  ESR_PTR&t;0x02000000&t;/* Program Exception - Trap */
DECL|macro|ESR_DST
mdefine_line|#define&t;  ESR_DST&t;0x00800000&t;/* Storage Exception - Data miss */
DECL|macro|ESR_DIZ
mdefine_line|#define&t;  ESR_DIZ&t;0x00400000&t;/* Storage Exception - Zone fault */
DECL|macro|SPRN_EVPR
mdefine_line|#define&t;SPRN_EVPR&t;0x3D6&t;/* Exception Vector Prefix Register */
DECL|macro|SPRN_HASH1
mdefine_line|#define&t;SPRN_HASH1&t;0x3D2&t;/* Primary Hash Address Register */
DECL|macro|SPRN_HASH2
mdefine_line|#define&t;SPRN_HASH2&t;0x3D3&t;/* Secondary Hash Address Resgister */
DECL|macro|SPRN_HID0
mdefine_line|#define&t;SPRN_HID0&t;0x3F0&t;/* Hardware Implementation Register 0 */
DECL|macro|HID0_EMCP
mdefine_line|#define&t;  HID0_EMCP&t;(1&lt;&lt;31)&t;&t;/* Enable Machine Check pin */
DECL|macro|HID0_EBA
mdefine_line|#define&t;  HID0_EBA&t;(1&lt;&lt;29)&t;&t;/* Enable Bus Address Parity */
DECL|macro|HID0_EBD
mdefine_line|#define&t;  HID0_EBD&t;(1&lt;&lt;28)&t;&t;/* Enable Bus Data Parity */
DECL|macro|HID0_SBCLK
mdefine_line|#define&t;  HID0_SBCLK&t;(1&lt;&lt;27)
DECL|macro|HID0_EICE
mdefine_line|#define&t;  HID0_EICE&t;(1&lt;&lt;26)
DECL|macro|HID0_TBEN
mdefine_line|#define&t;  HID0_TBEN&t;(1&lt;&lt;26)&t;&t;/* Timebase enable - 745x */
DECL|macro|HID0_ECLK
mdefine_line|#define&t;  HID0_ECLK&t;(1&lt;&lt;25)
DECL|macro|HID0_PAR
mdefine_line|#define&t;  HID0_PAR&t;(1&lt;&lt;24)
DECL|macro|HID0_STEN
mdefine_line|#define&t;  HID0_STEN&t;(1&lt;&lt;24)&t;&t;/* Software table search enable - 745x */
DECL|macro|HID0_HIGH_BAT
mdefine_line|#define&t;  HID0_HIGH_BAT&t;(1&lt;&lt;23)&t;&t;/* Enable high BATs - 7455 */
DECL|macro|HID0_DOZE
mdefine_line|#define&t;  HID0_DOZE&t;(1&lt;&lt;23)
DECL|macro|HID0_NAP
mdefine_line|#define&t;  HID0_NAP&t;(1&lt;&lt;22)
DECL|macro|HID0_SLEEP
mdefine_line|#define&t;  HID0_SLEEP&t;(1&lt;&lt;21)
DECL|macro|HID0_DPM
mdefine_line|#define&t;  HID0_DPM&t;(1&lt;&lt;20)
DECL|macro|HID0_BHTCLR
mdefine_line|#define&t;  HID0_BHTCLR&t;(1&lt;&lt;18)&t;&t;/* Clear branch history table - 7450 */
DECL|macro|HID0_XAEN
mdefine_line|#define&t;  HID0_XAEN&t;(1&lt;&lt;17)&t;&t;/* Extended addressing enable - 7450 */
DECL|macro|HID0_NHR
mdefine_line|#define   HID0_NHR&t;(1&lt;&lt;16)&t;&t;/* Not hard reset (software bit-7450)*/
DECL|macro|HID0_ICE
mdefine_line|#define&t;  HID0_ICE&t;(1&lt;&lt;15)&t;&t;/* Instruction Cache Enable */
DECL|macro|HID0_DCE
mdefine_line|#define&t;  HID0_DCE&t;(1&lt;&lt;14)&t;&t;/* Data Cache Enable */
DECL|macro|HID0_ILOCK
mdefine_line|#define&t;  HID0_ILOCK&t;(1&lt;&lt;13)&t;&t;/* Instruction Cache Lock */
DECL|macro|HID0_DLOCK
mdefine_line|#define&t;  HID0_DLOCK&t;(1&lt;&lt;12)&t;&t;/* Data Cache Lock */
DECL|macro|HID0_ICFI
mdefine_line|#define&t;  HID0_ICFI&t;(1&lt;&lt;11)&t;&t;/* Instr. Cache Flash Invalidate */
DECL|macro|HID0_DCI
mdefine_line|#define&t;  HID0_DCI&t;(1&lt;&lt;10)&t;&t;/* Data Cache Invalidate */
DECL|macro|HID0_SPD
mdefine_line|#define   HID0_SPD&t;(1&lt;&lt;9)&t;&t;/* Speculative disable */
DECL|macro|HID0_SGE
mdefine_line|#define   HID0_SGE&t;(1&lt;&lt;7)&t;&t;/* Store Gathering Enable */
DECL|macro|HID0_SIED
mdefine_line|#define&t;  HID0_SIED&t;(1&lt;&lt;7)&t;&t;/* Serial Instr. Execution [Disable] */
DECL|macro|HID0_DFCA
mdefine_line|#define&t;  HID0_DFCA&t;(1&lt;&lt;6)&t;&t;/* Data Cache Flush Assist */
DECL|macro|HID0_LRSTK
mdefine_line|#define   HID0_LRSTK&t;(1&lt;&lt;4)&t;&t;/* Link register stack - 745x */
DECL|macro|HID0_BTIC
mdefine_line|#define   HID0_BTIC&t;(1&lt;&lt;5)&t;&t;/* Branch Target Instr Cache Enable */
DECL|macro|HID0_ABE
mdefine_line|#define   HID0_ABE&t;(1&lt;&lt;3)&t;&t;/* Address Broadcast Enable */
DECL|macro|HID0_FOLD
mdefine_line|#define   HID0_FOLD&t;(1&lt;&lt;3)&t;&t;/* Branch Folding enable - 745x */
DECL|macro|HID0_BHTE
mdefine_line|#define&t;  HID0_BHTE&t;(1&lt;&lt;2)&t;&t;/* Branch History Table Enable */
DECL|macro|HID0_BTCD
mdefine_line|#define&t;  HID0_BTCD&t;(1&lt;&lt;1)&t;&t;/* Branch target cache disable */
DECL|macro|HID0_NOPDST
mdefine_line|#define&t;  HID0_NOPDST&t;(1&lt;&lt;1)&t;&t;/* No-op dst, dstt, etc. instr. */
DECL|macro|HID0_NOPTI
mdefine_line|#define&t;  HID0_NOPTI&t;(1&lt;&lt;0)&t;&t;/* No-op dcbt and dcbst instr. */
DECL|macro|SPRN_HID1
mdefine_line|#define&t;SPRN_HID1&t;0x3F1&t;/* Hardware Implementation Register 1 */
DECL|macro|HID1_EMCP
mdefine_line|#define&t;  HID1_EMCP&t;(1&lt;&lt;31)&t;&t;/* 7450 Machine Check Pin Enable */
DECL|macro|HID1_PC0
mdefine_line|#define   HID1_PC0&t;(1&lt;&lt;16)&t;&t;/* 7450 PLL_CFG[0] */
DECL|macro|HID1_PC1
mdefine_line|#define   HID1_PC1&t;(1&lt;&lt;15)&t;&t;/* 7450 PLL_CFG[1] */
DECL|macro|HID1_PC2
mdefine_line|#define   HID1_PC2&t;(1&lt;&lt;14)&t;&t;/* 7450 PLL_CFG[2] */
DECL|macro|HID1_PC3
mdefine_line|#define   HID1_PC3&t;(1&lt;&lt;13)&t;&t;/* 7450 PLL_CFG[3] */
DECL|macro|HID1_SYNCBE
mdefine_line|#define&t;  HID1_SYNCBE&t;(1&lt;&lt;11)&t;&t;/* 7450 ABE for sync, eieio */
DECL|macro|HID1_ABE
mdefine_line|#define&t;  HID1_ABE&t;(1&lt;&lt;10)&t;&t;/* 7450 Address Broadcast Enable */
DECL|macro|SPRN_IABR
mdefine_line|#define&t;SPRN_IABR&t;0x3F2&t;/* Instruction Address Breakpoint Register */
macro_line|#ifndef CONFIG_BOOKE
DECL|macro|SPRN_IAC1
mdefine_line|#define&t;SPRN_IAC1&t;0x3F4&t;/* Instruction Address Compare 1 */
DECL|macro|SPRN_IAC2
mdefine_line|#define&t;SPRN_IAC2&t;0x3F5&t;/* Instruction Address Compare 2 */
macro_line|#else
DECL|macro|SPRN_IAC1
mdefine_line|#define&t;SPRN_IAC1&t;0x138&t;/* Book E Instruction Address Compare 1 */
DECL|macro|SPRN_IAC2
mdefine_line|#define&t;SPRN_IAC2&t;0x139&t;/* Book E Instruction Address Compare 2 */
macro_line|#endif /* CONFIG_BOOKE */
DECL|macro|SPRN_IBAT0L
mdefine_line|#define&t;SPRN_IBAT0L&t;0x211&t;/* Instruction BAT 0 Lower Register */
DECL|macro|SPRN_IBAT0U
mdefine_line|#define&t;SPRN_IBAT0U&t;0x210&t;/* Instruction BAT 0 Upper Register */
DECL|macro|SPRN_IBAT1L
mdefine_line|#define&t;SPRN_IBAT1L&t;0x213&t;/* Instruction BAT 1 Lower Register */
DECL|macro|SPRN_IBAT1U
mdefine_line|#define&t;SPRN_IBAT1U&t;0x212&t;/* Instruction BAT 1 Upper Register */
DECL|macro|SPRN_IBAT2L
mdefine_line|#define&t;SPRN_IBAT2L&t;0x215&t;/* Instruction BAT 2 Lower Register */
DECL|macro|SPRN_IBAT2U
mdefine_line|#define&t;SPRN_IBAT2U&t;0x214&t;/* Instruction BAT 2 Upper Register */
DECL|macro|SPRN_IBAT3L
mdefine_line|#define&t;SPRN_IBAT3L&t;0x217&t;/* Instruction BAT 3 Lower Register */
DECL|macro|SPRN_IBAT3U
mdefine_line|#define&t;SPRN_IBAT3U&t;0x216&t;/* Instruction BAT 3 Upper Register */
DECL|macro|SPRN_IBAT4L
mdefine_line|#define&t;SPRN_IBAT4L&t;0x231&t;/* Instruction BAT 4 Lower Register */
DECL|macro|SPRN_IBAT4U
mdefine_line|#define&t;SPRN_IBAT4U&t;0x230&t;/* Instruction BAT 4 Upper Register */
DECL|macro|SPRN_IBAT5L
mdefine_line|#define&t;SPRN_IBAT5L&t;0x233&t;/* Instruction BAT 5 Lower Register */
DECL|macro|SPRN_IBAT5U
mdefine_line|#define&t;SPRN_IBAT5U&t;0x232&t;/* Instruction BAT 5 Upper Register */
DECL|macro|SPRN_IBAT6L
mdefine_line|#define&t;SPRN_IBAT6L&t;0x235&t;/* Instruction BAT 6 Lower Register */
DECL|macro|SPRN_IBAT6U
mdefine_line|#define&t;SPRN_IBAT6U&t;0x234&t;/* Instruction BAT 6 Upper Register */
DECL|macro|SPRN_IBAT7L
mdefine_line|#define&t;SPRN_IBAT7L&t;0x237&t;/* Instruction BAT 7 Lower Register */
DECL|macro|SPRN_IBAT7U
mdefine_line|#define&t;SPRN_IBAT7U&t;0x236&t;/* Instruction BAT 7 Upper Register */
DECL|macro|SPRN_ICCR
mdefine_line|#define&t;SPRN_ICCR&t;0x3FB&t;/* Instruction Cache Cacheability Register */
DECL|macro|ICCR_NOCACHE
mdefine_line|#define&t;  ICCR_NOCACHE&t;&t;0&t;/* Noncacheable */
DECL|macro|ICCR_CACHE
mdefine_line|#define&t;  ICCR_CACHE&t;&t;1&t;/* Cacheable */
DECL|macro|SPRN_ICDBDR
mdefine_line|#define&t;SPRN_ICDBDR&t;0x3D3&t;/* Instruction Cache Debug Data Register */
DECL|macro|SPRN_ICMP
mdefine_line|#define&t;SPRN_ICMP&t;0x3D5&t;/* Instruction TLB Compare Register */
DECL|macro|SPRN_ICTC
mdefine_line|#define&t;SPRN_ICTC&t;0x3FB&t;/* Instruction Cache Throttling Control Reg */
DECL|macro|SPRN_ICTRL
mdefine_line|#define&t;SPRN_ICTRL &t;0x3F3&t;/* 1011 7450 icache and interrupt ctrl */
DECL|macro|ICTRL_EICE
mdefine_line|#define   ICTRL_EICE&t;&t;0x08000000&t;/* enable icache parity errs */
DECL|macro|ICTRL_EDCE
mdefine_line|#define   ICTRL_EDCE&t;&t;0x04000000&t;/* enable dcache parity errs */
DECL|macro|ICTRL_EICP
mdefine_line|#define   ICTRL_EICP&t;&t;0x00000100&t;/* enable icache par. check */
DECL|macro|SPRN_IMISS
mdefine_line|#define&t;SPRN_IMISS&t;0x3D4&t;/* Instruction TLB Miss Register */
DECL|macro|SPRN_IMMR
mdefine_line|#define&t;SPRN_IMMR&t;0x27E  &t;/* Internal Memory Map Register */
DECL|macro|SPRN_L2CR
mdefine_line|#define&t;SPRN_L2CR&t;0x3F9&t;/* Level 2 Cache Control Regsiter */
DECL|macro|L2CR_L2E
mdefine_line|#define L2CR_L2E&t;&t;0x80000000&t;/* L2 enable */
DECL|macro|L2CR_L2PE
mdefine_line|#define L2CR_L2PE&t;&t;0x40000000&t;/* L2 parity enable */
DECL|macro|L2CR_L2SIZ_MASK
mdefine_line|#define&t;L2CR_L2SIZ_MASK&t;&t;0x30000000&t;/* L2 size mask */
DECL|macro|L2CR_L2SIZ_256KB
mdefine_line|#define L2CR_L2SIZ_256KB&t;0x10000000&t;/* L2 size 256KB */
DECL|macro|L2CR_L2SIZ_512KB
mdefine_line|#define L2CR_L2SIZ_512KB&t;0x20000000&t;/* L2 size 512KB */
DECL|macro|L2CR_L2SIZ_1MB
mdefine_line|#define L2CR_L2SIZ_1MB&t;&t;0x30000000&t;/* L2 size 1MB */
DECL|macro|L2CR_L2CLK_MASK
mdefine_line|#define L2CR_L2CLK_MASK&t;&t;0x0e000000&t;/* L2 clock mask */
DECL|macro|L2CR_L2CLK_DISABLED
mdefine_line|#define L2CR_L2CLK_DISABLED&t;0x00000000&t;/* L2 clock disabled */
DECL|macro|L2CR_L2CLK_DIV1
mdefine_line|#define L2CR_L2CLK_DIV1&t;&t;0x02000000&t;/* L2 clock / 1 */
DECL|macro|L2CR_L2CLK_DIV1_5
mdefine_line|#define L2CR_L2CLK_DIV1_5&t;0x04000000&t;/* L2 clock / 1.5 */
DECL|macro|L2CR_L2CLK_DIV2
mdefine_line|#define L2CR_L2CLK_DIV2&t;&t;0x08000000&t;/* L2 clock / 2 */
DECL|macro|L2CR_L2CLK_DIV2_5
mdefine_line|#define L2CR_L2CLK_DIV2_5&t;0x0a000000&t;/* L2 clock / 2.5 */
DECL|macro|L2CR_L2CLK_DIV3
mdefine_line|#define L2CR_L2CLK_DIV3&t;&t;0x0c000000&t;/* L2 clock / 3 */
DECL|macro|L2CR_L2RAM_MASK
mdefine_line|#define L2CR_L2RAM_MASK&t;&t;0x01800000&t;/* L2 RAM type mask */
DECL|macro|L2CR_L2RAM_FLOW
mdefine_line|#define L2CR_L2RAM_FLOW&t;&t;0x00000000&t;/* L2 RAM flow through */
DECL|macro|L2CR_L2RAM_PIPE
mdefine_line|#define L2CR_L2RAM_PIPE&t;&t;0x01000000&t;/* L2 RAM pipelined */
DECL|macro|L2CR_L2RAM_PIPE_LW
mdefine_line|#define L2CR_L2RAM_PIPE_LW&t;0x01800000&t;/* L2 RAM pipelined latewr */
DECL|macro|L2CR_L2DO
mdefine_line|#define&t;L2CR_L2DO&t;&t;0x00400000&t;/* L2 data only */
DECL|macro|L2CR_L2I
mdefine_line|#define L2CR_L2I&t;&t;0x00200000&t;/* L2 global invalidate */
DECL|macro|L2CR_L2CTL
mdefine_line|#define L2CR_L2CTL&t;&t;0x00100000&t;/* L2 RAM control */
DECL|macro|L2CR_L2WT
mdefine_line|#define L2CR_L2WT&t;&t;0x00080000&t;/* L2 write-through */
DECL|macro|L2CR_L2TS
mdefine_line|#define L2CR_L2TS&t;&t;0x00040000&t;/* L2 test support */
DECL|macro|L2CR_L2OH_MASK
mdefine_line|#define L2CR_L2OH_MASK&t;&t;0x00030000&t;/* L2 output hold mask */
DECL|macro|L2CR_L2OH_0_5
mdefine_line|#define L2CR_L2OH_0_5&t;&t;0x00000000&t;/* L2 output hold 0.5 ns */
DECL|macro|L2CR_L2OH_1_0
mdefine_line|#define L2CR_L2OH_1_0&t;&t;0x00010000&t;/* L2 output hold 1.0 ns */
DECL|macro|L2CR_L2SL
mdefine_line|#define L2CR_L2SL&t;&t;0x00008000&t;/* L2 DLL slow */
DECL|macro|L2CR_L2DF
mdefine_line|#define L2CR_L2DF&t;&t;0x00004000&t;/* L2 differential clock */
DECL|macro|L2CR_L2BYP
mdefine_line|#define L2CR_L2BYP&t;&t;0x00002000&t;/* L2 DLL bypass */
DECL|macro|L2CR_L2IP
mdefine_line|#define L2CR_L2IP&t;&t;0x00000001&t;/* L2 GI in progress */
DECL|macro|SPRN_L2CR2
mdefine_line|#define SPRN_L2CR2      0x3f8
DECL|macro|SPRN_L3CR
mdefine_line|#define&t;SPRN_L3CR&t;0x3FA&t;/* Level 3 Cache Control Regsiter (7450) */
DECL|macro|L3CR_L3E
mdefine_line|#define L3CR_L3E&t;&t;0x80000000&t;/* L3 enable */
DECL|macro|L3CR_L3PE
mdefine_line|#define L3CR_L3PE&t;&t;0x40000000&t;/* L3 data parity enable */
DECL|macro|L3CR_L3APE
mdefine_line|#define L3CR_L3APE&t;&t;0x20000000&t;/* L3 addr parity enable */
DECL|macro|L3CR_L3SIZ
mdefine_line|#define L3CR_L3SIZ&t;&t;0x10000000&t;/* L3 size */
DECL|macro|L3CR_L3CLKEN
mdefine_line|#define L3CR_L3CLKEN&t;&t;0x08000000&t;/* L3 clock enable */
DECL|macro|L3CR_L3RES
mdefine_line|#define L3CR_L3RES&t;&t;0x04000000&t;/* L3 special reserved bit */
DECL|macro|L3CR_L3CLKDIV
mdefine_line|#define L3CR_L3CLKDIV&t;&t;0x03800000&t;/* L3 clock divisor */
DECL|macro|L3CR_L3IO
mdefine_line|#define L3CR_L3IO&t;&t;0x00400000&t;/* L3 instruction only */
DECL|macro|L3CR_L3SPO
mdefine_line|#define L3CR_L3SPO&t;&t;0x00040000&t;/* L3 sample point override */
DECL|macro|L3CR_L3CKSP
mdefine_line|#define L3CR_L3CKSP&t;&t;0x00030000&t;/* L3 clock sample point */
DECL|macro|L3CR_L3PSP
mdefine_line|#define L3CR_L3PSP&t;&t;0x0000e000&t;/* L3 P-clock sample point */
DECL|macro|L3CR_L3REP
mdefine_line|#define L3CR_L3REP&t;&t;0x00001000&t;/* L3 replacement algorithm */
DECL|macro|L3CR_L3HWF
mdefine_line|#define L3CR_L3HWF&t;&t;0x00000800&t;/* L3 hardware flush */
DECL|macro|L3CR_L3I
mdefine_line|#define L3CR_L3I&t;&t;0x00000400&t;/* L3 global invalidate */
DECL|macro|L3CR_L3RT
mdefine_line|#define L3CR_L3RT&t;&t;0x00000300&t;/* L3 SRAM type */
DECL|macro|L3CR_L3NIRCA
mdefine_line|#define L3CR_L3NIRCA&t;&t;0x00000080&t;/* L3 non-integer ratio clock adj. */
DECL|macro|L3CR_L3DO
mdefine_line|#define L3CR_L3DO&t;&t;0x00000040&t;/* L3 data only mode */
DECL|macro|L3CR_PMEN
mdefine_line|#define L3CR_PMEN&t;&t;0x00000004&t;/* L3 private memory enable */
DECL|macro|L3CR_PMSIZ
mdefine_line|#define L3CR_PMSIZ&t;&t;0x00000001&t;/* L3 private memory size */
DECL|macro|SPRN_MSSCR0
mdefine_line|#define SPRN_MSSCR0&t;0x3f6&t;/* Memory Subsystem Control Register 0 */
DECL|macro|SPRN_MSSSR0
mdefine_line|#define SPRN_MSSSR0&t;0x3f7&t;/* Memory Subsystem Status Register 1 */
DECL|macro|SPRN_LDSTCR
mdefine_line|#define SPRN_LDSTCR&t;0x3f8&t;/* Load/Store control register */
DECL|macro|SPRN_LDSTDB
mdefine_line|#define SPRN_LDSTDB&t;0x3f4&t;/* */
DECL|macro|SPRN_LR
mdefine_line|#define&t;SPRN_LR&t;&t;0x008&t;/* Link Register */
DECL|macro|SPRN_MMCR0
mdefine_line|#define&t;SPRN_MMCR0&t;0x3B8&t;/* Monitor Mode Control Register 0 */
DECL|macro|SPRN_MMCR1
mdefine_line|#define&t;SPRN_MMCR1&t;0x3BC&t;/* Monitor Mode Control Register 1 */
DECL|macro|SPRN_PBL1
mdefine_line|#define&t;SPRN_PBL1&t;0x3FC&t;/* Protection Bound Lower 1 */
DECL|macro|SPRN_PBL2
mdefine_line|#define&t;SPRN_PBL2&t;0x3FE&t;/* Protection Bound Lower 2 */
DECL|macro|SPRN_PBU1
mdefine_line|#define&t;SPRN_PBU1&t;0x3FD&t;/* Protection Bound Upper 1 */
DECL|macro|SPRN_PBU2
mdefine_line|#define&t;SPRN_PBU2&t;0x3FF&t;/* Protection Bound Upper 2 */
macro_line|#ifndef CONFIG_BOOKE
DECL|macro|SPRN_PID
mdefine_line|#define&t;SPRN_PID&t;0x3B1&t;/* Process ID */
DECL|macro|SPRN_PIR
mdefine_line|#define&t;SPRN_PIR&t;0x3FF&t;/* Processor Identification Register */
macro_line|#else
DECL|macro|SPRN_PID
mdefine_line|#define&t;SPRN_PID&t;0x030&t;/* Book E Process ID */
DECL|macro|SPRN_PIR
mdefine_line|#define&t;SPRN_PIR&t;0x11E&t;/* Book E Processor Identification Register */
macro_line|#endif /* CONFIG_BOOKE */
DECL|macro|SPRN_PIT
mdefine_line|#define&t;SPRN_PIT&t;0x3DB&t;/* Programmable Interval Timer */
DECL|macro|SPRN_PMC1
mdefine_line|#define&t;SPRN_PMC1&t;0x3B9&t;/* Performance Counter Register 1 */
DECL|macro|SPRN_PMC2
mdefine_line|#define&t;SPRN_PMC2&t;0x3BA&t;/* Performance Counter Register 2 */
DECL|macro|SPRN_PMC3
mdefine_line|#define&t;SPRN_PMC3&t;0x3BD&t;/* Performance Counter Register 3 */
DECL|macro|SPRN_PMC4
mdefine_line|#define&t;SPRN_PMC4&t;0x3BE&t;/* Performance Counter Register 4 */
DECL|macro|SPRN_PTEHI
mdefine_line|#define&t;SPRN_PTEHI&t;0x3D5&t;/* 981 7450 PTE HI word (S/W TLB load) */
DECL|macro|SPRN_PTELO
mdefine_line|#define&t;SPRN_PTELO&t;0x3D6&t;/* 982 7450 PTE LO word (S/W TLB load)  */
DECL|macro|SPRN_PVR
mdefine_line|#define&t;SPRN_PVR&t;0x11F&t;/* Processor Version Register */
DECL|macro|SPRN_RPA
mdefine_line|#define&t;SPRN_RPA&t;0x3D6&t;/* Required Physical Address Register */
DECL|macro|SPRN_SDA
mdefine_line|#define&t;SPRN_SDA&t;0x3BF&t;/* Sampled Data Address Register */
DECL|macro|SPRN_SDR1
mdefine_line|#define&t;SPRN_SDR1&t;0x019&t;/* MMU Hash Base Register */
DECL|macro|SPRN_SGR
mdefine_line|#define&t;SPRN_SGR&t;0x3B9&t;/* Storage Guarded Register */
DECL|macro|SGR_NORMAL
mdefine_line|#define&t;  SGR_NORMAL&t;&t;0
DECL|macro|SGR_GUARDED
mdefine_line|#define&t;  SGR_GUARDED&t;&t;1
DECL|macro|SPRN_SIA
mdefine_line|#define&t;SPRN_SIA&t;0x3BB&t;/* Sampled Instruction Address Register */
DECL|macro|SPRN_SLER
mdefine_line|#define&t;SPRN_SLER&t;0x3BB&t;/* Little-endian real mode */
DECL|macro|SPRN_SPRG0
mdefine_line|#define&t;SPRN_SPRG0&t;0x110&t;/* Special Purpose Register General 0 */
DECL|macro|SPRN_SPRG1
mdefine_line|#define&t;SPRN_SPRG1&t;0x111&t;/* Special Purpose Register General 1 */
DECL|macro|SPRN_SPRG2
mdefine_line|#define&t;SPRN_SPRG2&t;0x112&t;/* Special Purpose Register General 2 */
DECL|macro|SPRN_SPRG3
mdefine_line|#define&t;SPRN_SPRG3&t;0x113&t;/* Special Purpose Register General 3 */
DECL|macro|SPRN_SPRG4
mdefine_line|#define&t;SPRN_SPRG4&t;0x114&t;/* Special Purpose Register General 4 (4xx) */
DECL|macro|SPRN_SPRG5
mdefine_line|#define&t;SPRN_SPRG5&t;0x115&t;/* Special Purpose Register General 5 (4xx) */
DECL|macro|SPRN_SPRG6
mdefine_line|#define&t;SPRN_SPRG6&t;0x116&t;/* Special Purpose Register General 6 (4xx) */
DECL|macro|SPRN_SPRG7
mdefine_line|#define&t;SPRN_SPRG7&t;0x117&t;/* Special Purpose Register General 7 (4xx) */
DECL|macro|SPRN_SRR0
mdefine_line|#define&t;SPRN_SRR0&t;0x01A&t;/* Save/Restore Register 0 */
DECL|macro|SPRN_SRR1
mdefine_line|#define&t;SPRN_SRR1&t;0x01B&t;/* Save/Restore Register 1 */
DECL|macro|SPRN_SRR2
mdefine_line|#define&t;SPRN_SRR2&t;0x3DE&t;/* Save/Restore Register 2 */
DECL|macro|SPRN_SRR3
mdefine_line|#define&t;SPRN_SRR3 &t;0x3DF&t;/* Save/Restore Register 3 */
DECL|macro|SPRN_SU0R
mdefine_line|#define&t;SPRN_SU0R&t;0x3BC&t;/* &quot;User 0&quot; real mode */
DECL|macro|SPRN_TBHI
mdefine_line|#define&t;SPRN_TBHI&t;0x3DC&t;/* Time Base High (4xx) */
DECL|macro|SPRN_TBHU
mdefine_line|#define&t;SPRN_TBHU&t;0x3CC&t;/* Time Base High User-mode (4xx) */
DECL|macro|SPRN_TBLO
mdefine_line|#define&t;SPRN_TBLO&t;0x3DD&t;/* Time Base Low (4xx) */
DECL|macro|SPRN_TBLU
mdefine_line|#define&t;SPRN_TBLU&t;0x3CD&t;/* Time Base Low User-mode (4xx) */
DECL|macro|SPRN_TBRL
mdefine_line|#define&t;SPRN_TBRL&t;0x10C&t;/* Time Base Read Lower Register (user, R/O) */
DECL|macro|SPRN_TBRU
mdefine_line|#define&t;SPRN_TBRU&t;0x10D&t;/* Time Base Read Upper Register (user, R/O) */
DECL|macro|SPRN_TBWL
mdefine_line|#define&t;SPRN_TBWL&t;0x11C&t;/* Time Base Lower Register (super, R/W) */
DECL|macro|SPRN_TBWU
mdefine_line|#define&t;SPRN_TBWU&t;0x11D&t;/* Time Base Upper Register (super, R/W) */
macro_line|#ifndef CONFIG_BOOKE
DECL|macro|SPRN_TCR
mdefine_line|#define&t;SPRN_TCR&t;0x3DA&t;/* Timer Control Register */
macro_line|#else
DECL|macro|SPRN_TCR
mdefine_line|#define&t;SPRN_TCR&t;0x154&t;/* Book E Timer Control Register */
macro_line|#endif
DECL|macro|TCR_WP
mdefine_line|#define&t;  TCR_WP(x)&t;&t;(((x)&amp;0x3)&lt;&lt;30)&t;/* WDT Period */
DECL|macro|TCR_WP_MASK
mdefine_line|#define     TCR_WP_MASK         TCR_WP(3)
DECL|macro|WP_2_17
mdefine_line|#define&t;    WP_2_17&t;&t;0&t;&t;/* 2^17 clocks */
DECL|macro|WP_2_21
mdefine_line|#define&t;    WP_2_21&t;&t;1&t;&t;/* 2^21 clocks */
DECL|macro|WP_2_25
mdefine_line|#define&t;    WP_2_25&t;&t;2&t;&t;/* 2^25 clocks */
DECL|macro|WP_2_29
mdefine_line|#define&t;    WP_2_29&t;&t;3&t;&t;/* 2^29 clocks */
DECL|macro|TCR_WRC
mdefine_line|#define&t;  TCR_WRC(x)&t;&t;(((x)&amp;0x3)&lt;&lt;28)&t;/* WDT Reset Control */
DECL|macro|TCR_WRC_MASK
mdefine_line|#define     TCR_WRC_MASK        TCR_WRC(3)
DECL|macro|WRC_NONE
mdefine_line|#define&t;    WRC_NONE&t;&t;0&t;&t;/* No reset will occur */
DECL|macro|WRC_CORE
mdefine_line|#define&t;    WRC_CORE&t;&t;1&t;&t;/* Core reset will occur */
DECL|macro|WRC_CHIP
mdefine_line|#define&t;    WRC_CHIP&t;&t;2&t;&t;/* Chip reset will occur */
DECL|macro|WRC_SYSTEM
mdefine_line|#define&t;    WRC_SYSTEM&t;&t;3&t;&t;/* System reset will occur */
DECL|macro|TCR_WIE
mdefine_line|#define&t;  TCR_WIE&t;&t;0x08000000&t;/* WDT Interrupt Enable */
DECL|macro|TCR_PIE
mdefine_line|#define&t;  TCR_PIE&t;&t;0x04000000&t;/* PIT Interrupt Enable */
DECL|macro|TCR_DIE
mdefine_line|#define&t;  TCR_DIE&t;&t;TCR_PIE&t;&t;/* DEC Interrupt Enable */
DECL|macro|TCR_FP
mdefine_line|#define&t;  TCR_FP(x)&t;&t;(((x)&amp;0x3)&lt;&lt;24)&t;/* FIT Period */
DECL|macro|TCR_FP_MASK
mdefine_line|#define     TCR_FP_MASK         TCR_FP(3)
DECL|macro|FP_2_9
mdefine_line|#define&t;    FP_2_9&t;&t;0&t;&t;/* 2^9 clocks */
DECL|macro|FP_2_13
mdefine_line|#define&t;    FP_2_13&t;&t;1&t;&t;/* 2^13 clocks */
DECL|macro|FP_2_17
mdefine_line|#define&t;    FP_2_17&t;&t;2&t;&t;/* 2^17 clocks */
DECL|macro|FP_2_21
mdefine_line|#define&t;    FP_2_21&t;&t;3&t;&t;/* 2^21 clocks */
DECL|macro|TCR_FIE
mdefine_line|#define&t;  TCR_FIE&t;&t;0x00800000&t;/* FIT Interrupt Enable */
DECL|macro|TCR_ARE
mdefine_line|#define&t;  TCR_ARE&t;&t;0x00400000&t;/* Auto Reload Enable */
DECL|macro|SPRN_THRM1
mdefine_line|#define&t;SPRN_THRM1&t;0x3FC&t;/* Thermal Management Register 1 */
multiline_comment|/* these bits were defined in inverted endian sense originally, ugh, confusing */
DECL|macro|THRM1_TIN
mdefine_line|#define&t;  THRM1_TIN&t;&t;(1 &lt;&lt; 31)
DECL|macro|THRM1_TIV
mdefine_line|#define&t;  THRM1_TIV&t;&t;(1 &lt;&lt; 30)
DECL|macro|THRM1_THRES
mdefine_line|#define&t;  THRM1_THRES(x)&t;((x&amp;0x7f)&lt;&lt;23)
DECL|macro|THRM3_SITV
mdefine_line|#define   THRM3_SITV(x)&t;&t;((x&amp;0x3fff)&lt;&lt;1)
DECL|macro|THRM1_TID
mdefine_line|#define&t;  THRM1_TID&t;&t;(1&lt;&lt;2)
DECL|macro|THRM1_TIE
mdefine_line|#define&t;  THRM1_TIE&t;&t;(1&lt;&lt;1)
DECL|macro|THRM1_V
mdefine_line|#define&t;  THRM1_V&t;&t;(1&lt;&lt;0)
DECL|macro|SPRN_THRM2
mdefine_line|#define&t;SPRN_THRM2&t;0x3FD&t;/* Thermal Management Register 2 */
DECL|macro|SPRN_THRM3
mdefine_line|#define&t;SPRN_THRM3&t;0x3FE&t;/* Thermal Management Register 3 */
DECL|macro|THRM3_E
mdefine_line|#define&t;  THRM3_E&t;&t;(1&lt;&lt;0)
DECL|macro|SPRN_TLBMISS
mdefine_line|#define&t;SPRN_TLBMISS&t;0x3D4&t;/* 980 7450 TLB Miss Register */
macro_line|#ifndef CONFIG_BOOKE
DECL|macro|SPRN_TSR
mdefine_line|#define&t;SPRN_TSR&t;0x3D8&t;/* Timer Status Register */
macro_line|#else
DECL|macro|SPRN_TSR
mdefine_line|#define&t;SPRN_TSR&t;0x150&t;/* Book E Timer Status Register */
macro_line|#endif /* CONFIG_BOOKE */
DECL|macro|TSR_ENW
mdefine_line|#define&t;  TSR_ENW&t;&t;0x80000000&t;/* Enable Next Watchdog */
DECL|macro|TSR_WIS
mdefine_line|#define&t;  TSR_WIS&t;&t;0x40000000&t;/* WDT Interrupt Status */
DECL|macro|TSR_WRS
mdefine_line|#define&t;  TSR_WRS(x)&t;&t;(((x)&amp;0x3)&lt;&lt;28)&t;/* WDT Reset Status */
DECL|macro|WRS_NONE
mdefine_line|#define&t;    WRS_NONE&t;&t;0&t;&t;/* No WDT reset occurred */
DECL|macro|WRS_CORE
mdefine_line|#define&t;    WRS_CORE&t;&t;1&t;&t;/* WDT forced core reset */
DECL|macro|WRS_CHIP
mdefine_line|#define&t;    WRS_CHIP&t;&t;2&t;&t;/* WDT forced chip reset */
DECL|macro|WRS_SYSTEM
mdefine_line|#define&t;    WRS_SYSTEM&t;&t;3&t;&t;/* WDT forced system reset */
DECL|macro|TSR_PIS
mdefine_line|#define&t;  TSR_PIS&t;&t;0x08000000&t;/* PIT Interrupt Status */
DECL|macro|TSR_DIS
mdefine_line|#define&t;  TSR_DIS&t;&t;TSR_PIS&t;&t;/* DEC Interrupt Status */
DECL|macro|TSR_FIS
mdefine_line|#define&t;  TSR_FIS&t;&t;0x04000000&t;/* FIT Interrupt Status */
DECL|macro|SPRN_UMMCR0
mdefine_line|#define&t;SPRN_UMMCR0&t;0x3A8&t;/* User Monitor Mode Control Register 0 */
DECL|macro|SPRN_UMMCR1
mdefine_line|#define&t;SPRN_UMMCR1&t;0x3AC&t;/* User Monitor Mode Control Register 0 */
DECL|macro|SPRN_UPMC1
mdefine_line|#define&t;SPRN_UPMC1&t;0x3A9&t;/* User Performance Counter Register 1 */
DECL|macro|SPRN_UPMC2
mdefine_line|#define&t;SPRN_UPMC2&t;0x3AA&t;/* User Performance Counter Register 2 */
DECL|macro|SPRN_UPMC3
mdefine_line|#define&t;SPRN_UPMC3&t;0x3AD&t;/* User Performance Counter Register 3 */
DECL|macro|SPRN_UPMC4
mdefine_line|#define&t;SPRN_UPMC4&t;0x3AE&t;/* User Performance Counter Register 4 */
DECL|macro|SPRN_USIA
mdefine_line|#define&t;SPRN_USIA&t;0x3AB&t;/* User Sampled Instruction Address Register */
DECL|macro|SPRN_VRSAVE
mdefine_line|#define SPRN_VRSAVE&t;0x100&t;/* Vector Register Save Register */
DECL|macro|SPRN_XER
mdefine_line|#define&t;SPRN_XER&t;0x001&t;/* Fixed Point Exception Register */
DECL|macro|SPRN_ZPR
mdefine_line|#define&t;SPRN_ZPR&t;0x3B0&t;/* Zone Protection Register */
multiline_comment|/* Book E definitions */
DECL|macro|SPRN_DECAR
mdefine_line|#define SPRN_DECAR&t;0x036&t;/* Decrementer Auto Reload Register */
DECL|macro|SPRN_CSRR0
mdefine_line|#define SPRN_CSRR0&t;0x03A&t;/* Critical Save and Restore Register 0 */
DECL|macro|SPRN_CSRR1
mdefine_line|#define SPRN_CSRR1&t;0x03B&t;/* Critical Save and Restore Register 1 */
DECL|macro|SPRN_IVPR
mdefine_line|#define&t;SPRN_IVPR&t;0x03F&t;/* Interrupt Vector Prefix Register */
DECL|macro|SPRN_USPRG0
mdefine_line|#define SPRN_USPRG0&t;0x100&t;/* User Special Purpose Register General 0 */
DECL|macro|SPRN_SPRG4R
mdefine_line|#define&t;SPRN_SPRG4R&t;0x104&t;/* Special Purpose Register General 4 Read */
DECL|macro|SPRN_SPRG5R
mdefine_line|#define&t;SPRN_SPRG5R&t;0x105&t;/* Special Purpose Register General 5 Read */
DECL|macro|SPRN_SPRG6R
mdefine_line|#define&t;SPRN_SPRG6R&t;0x106&t;/* Special Purpose Register General 6 Read */
DECL|macro|SPRN_SPRG7R
mdefine_line|#define&t;SPRN_SPRG7R&t;0x107&t;/* Special Purpose Register General 7 Read */
DECL|macro|SPRN_SPRG4W
mdefine_line|#define&t;SPRN_SPRG4W&t;0x114&t;/* Special Purpose Register General 4 Write */
DECL|macro|SPRN_SPRG5W
mdefine_line|#define&t;SPRN_SPRG5W&t;0x115&t;/* Special Purpose Register General 5 Write */
DECL|macro|SPRN_SPRG6W
mdefine_line|#define&t;SPRN_SPRG6W&t;0x116&t;/* Special Purpose Register General 6 Write */
DECL|macro|SPRN_SPRG7W
mdefine_line|#define&t;SPRN_SPRG7W&t;0x117&t;/* Special Purpose Register General 7 Write */
DECL|macro|SPRN_DBCR2
mdefine_line|#define SPRN_DBCR2&t;0x136&t;/* Debug Control Register 2 */
DECL|macro|SPRN_IAC3
mdefine_line|#define&t;SPRN_IAC3&t;0x13A&t;/* Instruction Address Compare 3 */
DECL|macro|SPRN_IAC4
mdefine_line|#define&t;SPRN_IAC4&t;0x13B&t;/* Instruction Address Compare 4 */
DECL|macro|SPRN_DVC1
mdefine_line|#define SPRN_DVC1&t;0x13E&t;/* */
DECL|macro|SPRN_DVC2
mdefine_line|#define SPRN_DVC2&t;0x13F&t;/* */
DECL|macro|SPRN_IVOR0
mdefine_line|#define SPRN_IVOR0&t;0x190&t;/* Interrupt Vector Offset Register 0 */
DECL|macro|SPRN_IVOR1
mdefine_line|#define SPRN_IVOR1&t;0x191&t;/* Interrupt Vector Offset Register 1 */
DECL|macro|SPRN_IVOR2
mdefine_line|#define SPRN_IVOR2&t;0x192&t;/* Interrupt Vector Offset Register 2 */
DECL|macro|SPRN_IVOR3
mdefine_line|#define SPRN_IVOR3&t;0x193&t;/* Interrupt Vector Offset Register 3 */
DECL|macro|SPRN_IVOR4
mdefine_line|#define SPRN_IVOR4&t;0x194&t;/* Interrupt Vector Offset Register 4 */
DECL|macro|SPRN_IVOR5
mdefine_line|#define SPRN_IVOR5&t;0x195&t;/* Interrupt Vector Offset Register 5 */
DECL|macro|SPRN_IVOR6
mdefine_line|#define SPRN_IVOR6&t;0x196&t;/* Interrupt Vector Offset Register 6 */
DECL|macro|SPRN_IVOR7
mdefine_line|#define SPRN_IVOR7&t;0x197&t;/* Interrupt Vector Offset Register 7 */
DECL|macro|SPRN_IVOR8
mdefine_line|#define SPRN_IVOR8&t;0x198&t;/* Interrupt Vector Offset Register 8 */
DECL|macro|SPRN_IVOR9
mdefine_line|#define SPRN_IVOR9&t;0x199&t;/* Interrupt Vector Offset Register 9 */
DECL|macro|SPRN_IVOR10
mdefine_line|#define SPRN_IVOR10&t;0x19a&t;/* Interrupt Vector Offset Register 10 */
DECL|macro|SPRN_IVOR11
mdefine_line|#define SPRN_IVOR11&t;0x19b&t;/* Interrupt Vector Offset Register 11 */
DECL|macro|SPRN_IVOR12
mdefine_line|#define SPRN_IVOR12&t;0x19c&t;/* Interrupt Vector Offset Register 12 */
DECL|macro|SPRN_IVOR13
mdefine_line|#define SPRN_IVOR13&t;0x19d&t;/* Interrupt Vector Offset Register 13 */
DECL|macro|SPRN_IVOR14
mdefine_line|#define SPRN_IVOR14&t;0x19e&t;/* Interrupt Vector Offset Register 14 */
DECL|macro|SPRN_IVOR15
mdefine_line|#define SPRN_IVOR15&t;0x19f&t;/* Interrupt Vector Offset Register 15 */
DECL|macro|SPRN_MMUCR
mdefine_line|#define SPRN_MMUCR&t;0x3b2&t;/* MMU Control Register */
DECL|macro|ESR_ST
mdefine_line|#define ESR_ST&t;&t;0x00800000&t;/* Store Operation */
multiline_comment|/* Short-hand versions for a number of the above SPRNs */
DECL|macro|CTR
mdefine_line|#define&t;CTR&t;SPRN_CTR&t;/* Counter Register */
DECL|macro|DAR
mdefine_line|#define&t;DAR&t;SPRN_DAR&t;/* Data Address Register */
DECL|macro|DABR
mdefine_line|#define&t;DABR&t;SPRN_DABR&t;/* Data Address Breakpoint Register */
DECL|macro|DBAT0L
mdefine_line|#define&t;DBAT0L&t;SPRN_DBAT0L&t;/* Data BAT 0 Lower Register */
DECL|macro|DBAT0U
mdefine_line|#define&t;DBAT0U&t;SPRN_DBAT0U&t;/* Data BAT 0 Upper Register */
DECL|macro|DBAT1L
mdefine_line|#define&t;DBAT1L&t;SPRN_DBAT1L&t;/* Data BAT 1 Lower Register */
DECL|macro|DBAT1U
mdefine_line|#define&t;DBAT1U&t;SPRN_DBAT1U&t;/* Data BAT 1 Upper Register */
DECL|macro|DBAT2L
mdefine_line|#define&t;DBAT2L&t;SPRN_DBAT2L&t;/* Data BAT 2 Lower Register */
DECL|macro|DBAT2U
mdefine_line|#define&t;DBAT2U&t;SPRN_DBAT2U&t;/* Data BAT 2 Upper Register */
DECL|macro|DBAT3L
mdefine_line|#define&t;DBAT3L&t;SPRN_DBAT3L&t;/* Data BAT 3 Lower Register */
DECL|macro|DBAT3U
mdefine_line|#define&t;DBAT3U&t;SPRN_DBAT3U&t;/* Data BAT 3 Upper Register */
DECL|macro|DBAT4L
mdefine_line|#define&t;DBAT4L&t;SPRN_DBAT4L&t;/* Data BAT 4 Lower Register */
DECL|macro|DBAT4U
mdefine_line|#define&t;DBAT4U&t;SPRN_DBAT4U&t;/* Data BAT 4 Upper Register */
DECL|macro|DBAT5L
mdefine_line|#define&t;DBAT5L&t;SPRN_DBAT5L&t;/* Data BAT 5 Lower Register */
DECL|macro|DBAT5U
mdefine_line|#define&t;DBAT5U&t;SPRN_DBAT5U&t;/* Data BAT 5 Upper Register */
DECL|macro|DBAT6L
mdefine_line|#define&t;DBAT6L&t;SPRN_DBAT6L&t;/* Data BAT 6 Lower Register */
DECL|macro|DBAT6U
mdefine_line|#define&t;DBAT6U&t;SPRN_DBAT6U&t;/* Data BAT 6 Upper Register */
DECL|macro|DBAT7L
mdefine_line|#define&t;DBAT7L&t;SPRN_DBAT7L&t;/* Data BAT 7 Lower Register */
DECL|macro|DBAT7U
mdefine_line|#define&t;DBAT7U&t;SPRN_DBAT7U&t;/* Data BAT 7 Upper Register */
DECL|macro|DCMP
mdefine_line|#define&t;DCMP&t;SPRN_DCMP      &t;/* Data TLB Compare Register */
DECL|macro|DEC
mdefine_line|#define&t;DEC&t;SPRN_DEC       &t;/* Decrement Register */
DECL|macro|DMISS
mdefine_line|#define&t;DMISS&t;SPRN_DMISS     &t;/* Data TLB Miss Register */
DECL|macro|DSISR
mdefine_line|#define&t;DSISR&t;SPRN_DSISR&t;/* Data Storage Interrupt Status Register */
DECL|macro|EAR
mdefine_line|#define&t;EAR&t;SPRN_EAR       &t;/* External Address Register */
DECL|macro|HASH1
mdefine_line|#define&t;HASH1&t;SPRN_HASH1&t;/* Primary Hash Address Register */
DECL|macro|HASH2
mdefine_line|#define&t;HASH2&t;SPRN_HASH2&t;/* Secondary Hash Address Register */
DECL|macro|HID0
mdefine_line|#define&t;HID0&t;SPRN_HID0&t;/* Hardware Implementation Register 0 */
DECL|macro|HID1
mdefine_line|#define&t;HID1&t;SPRN_HID1&t;/* Hardware Implementation Register 1 */
DECL|macro|IABR
mdefine_line|#define&t;IABR&t;SPRN_IABR      &t;/* Instruction Address Breakpoint Register */
DECL|macro|IBAT0L
mdefine_line|#define&t;IBAT0L&t;SPRN_IBAT0L&t;/* Instruction BAT 0 Lower Register */
DECL|macro|IBAT0U
mdefine_line|#define&t;IBAT0U&t;SPRN_IBAT0U&t;/* Instruction BAT 0 Upper Register */
DECL|macro|IBAT1L
mdefine_line|#define&t;IBAT1L&t;SPRN_IBAT1L&t;/* Instruction BAT 1 Lower Register */
DECL|macro|IBAT1U
mdefine_line|#define&t;IBAT1U&t;SPRN_IBAT1U&t;/* Instruction BAT 1 Upper Register */
DECL|macro|IBAT2L
mdefine_line|#define&t;IBAT2L&t;SPRN_IBAT2L&t;/* Instruction BAT 2 Lower Register */
DECL|macro|IBAT2U
mdefine_line|#define&t;IBAT2U&t;SPRN_IBAT2U&t;/* Instruction BAT 2 Upper Register */
DECL|macro|IBAT3L
mdefine_line|#define&t;IBAT3L&t;SPRN_IBAT3L&t;/* Instruction BAT 3 Lower Register */
DECL|macro|IBAT3U
mdefine_line|#define&t;IBAT3U&t;SPRN_IBAT3U&t;/* Instruction BAT 3 Upper Register */
DECL|macro|IBAT4L
mdefine_line|#define&t;IBAT4L&t;SPRN_IBAT4L&t;/* Instruction BAT 4 Lower Register */
DECL|macro|IBAT4U
mdefine_line|#define&t;IBAT4U&t;SPRN_IBAT4U&t;/* Instruction BAT 4 Upper Register */
DECL|macro|IBAT5L
mdefine_line|#define&t;IBAT5L&t;SPRN_IBAT5L&t;/* Instruction BAT 5 Lower Register */
DECL|macro|IBAT5U
mdefine_line|#define&t;IBAT5U&t;SPRN_IBAT5U&t;/* Instruction BAT 5 Upper Register */
DECL|macro|IBAT6L
mdefine_line|#define&t;IBAT6L&t;SPRN_IBAT6L&t;/* Instruction BAT 6 Lower Register */
DECL|macro|IBAT6U
mdefine_line|#define&t;IBAT6U&t;SPRN_IBAT6U&t;/* Instruction BAT 6 Upper Register */
DECL|macro|IBAT7L
mdefine_line|#define&t;IBAT7L&t;SPRN_IBAT7L&t;/* Instruction BAT 7 Lower Register */
DECL|macro|IBAT7U
mdefine_line|#define&t;IBAT7U&t;SPRN_IBAT7U&t;/* Instruction BAT 7 Upper Register */
DECL|macro|ICMP
mdefine_line|#define&t;ICMP&t;SPRN_ICMP&t;/* Instruction TLB Compare Register */
DECL|macro|IMISS
mdefine_line|#define&t;IMISS&t;SPRN_IMISS&t;/* Instruction TLB Miss Register */
DECL|macro|IMMR
mdefine_line|#define&t;IMMR&t;SPRN_IMMR      &t;/* PPC 860/821 Internal Memory Map Register */
DECL|macro|L2CR
mdefine_line|#define&t;L2CR&t;SPRN_L2CR    &t;/* Classic PPC L2 cache control register */
DECL|macro|L3CR
mdefine_line|#define&t;L3CR&t;SPRN_L3CR&t;/* PPC 745x L3 cache control register */
DECL|macro|LR
mdefine_line|#define&t;LR&t;SPRN_LR
DECL|macro|PVR
mdefine_line|#define&t;PVR&t;SPRN_PVR&t;/* Processor Version */
DECL|macro|RPA
mdefine_line|#define&t;RPA&t;SPRN_RPA&t;/* Required Physical Address Register */
DECL|macro|SDR1
mdefine_line|#define&t;SDR1&t;SPRN_SDR1      &t;/* MMU hash base register */
DECL|macro|SPR0
mdefine_line|#define&t;SPR0&t;SPRN_SPRG0&t;/* Supervisor Private Registers */
DECL|macro|SPR1
mdefine_line|#define&t;SPR1&t;SPRN_SPRG1
DECL|macro|SPR2
mdefine_line|#define&t;SPR2&t;SPRN_SPRG2
DECL|macro|SPR3
mdefine_line|#define&t;SPR3&t;SPRN_SPRG3
DECL|macro|SPR4
mdefine_line|#define&t;SPR4&t;SPRN_SPRG4&t;/* Supervisor Private Registers (4xx) */
DECL|macro|SPR5
mdefine_line|#define&t;SPR5&t;SPRN_SPRG5
DECL|macro|SPR6
mdefine_line|#define&t;SPR6&t;SPRN_SPRG6
DECL|macro|SPR7
mdefine_line|#define&t;SPR7&t;SPRN_SPRG7
DECL|macro|SPRG0
mdefine_line|#define&t;SPRG0   SPRN_SPRG0
DECL|macro|SPRG1
mdefine_line|#define&t;SPRG1   SPRN_SPRG1
DECL|macro|SPRG2
mdefine_line|#define&t;SPRG2   SPRN_SPRG2
DECL|macro|SPRG3
mdefine_line|#define&t;SPRG3   SPRN_SPRG3
DECL|macro|SPRG4
mdefine_line|#define&t;SPRG4   SPRN_SPRG4
DECL|macro|SPRG5
mdefine_line|#define&t;SPRG5   SPRN_SPRG5
DECL|macro|SPRG6
mdefine_line|#define&t;SPRG6   SPRN_SPRG6
DECL|macro|SPRG7
mdefine_line|#define&t;SPRG7   SPRN_SPRG7
DECL|macro|SPRG4R
mdefine_line|#define SPRG4R  SPRN_SPRG4R     /* Book E Supervisor Private Registers */
DECL|macro|SPRG5R
mdefine_line|#define SPRG5R  SPRN_SPRG5R
DECL|macro|SPRG6R
mdefine_line|#define SPRG6R  SPRN_SPRG6R
DECL|macro|SPRG7R
mdefine_line|#define SPRG7R  SPRN_SPRG7R
DECL|macro|SPRG4W
mdefine_line|#define SPRG4W  SPRN_SPRG4W
DECL|macro|SPRG5W
mdefine_line|#define SPRG5W  SPRN_SPRG5W
DECL|macro|SPRG6W
mdefine_line|#define SPRG6W  SPRN_SPRG6W
DECL|macro|SPRG7W
mdefine_line|#define SPRG7W  SPRN_SPRG7W
DECL|macro|CSRR0
mdefine_line|#define CSRR0&t;SPRN_CSRR0&t;/* Critical Save and Restore Register 0 */
DECL|macro|CSRR1
mdefine_line|#define CSRR1&t;SPRN_CSRR1&t;/* Critical Save and Restore Register 1 */
DECL|macro|SRR0
mdefine_line|#define&t;SRR0&t;SPRN_SRR0&t;/* Save and Restore Register 0 */
DECL|macro|SRR1
mdefine_line|#define&t;SRR1&t;SPRN_SRR1&t;/* Save and Restore Register 1 */
DECL|macro|SRR2
mdefine_line|#define&t;SRR2&t;SPRN_SRR2&t;/* Save and Restore Register 2 */
DECL|macro|SRR3
mdefine_line|#define&t;SRR3&t;SPRN_SRR3&t;/* Save and Restore Register 3 */
DECL|macro|TBRL
mdefine_line|#define&t;TBRL&t;SPRN_TBRL&t;/* Time Base Read Lower Register */
DECL|macro|TBRU
mdefine_line|#define&t;TBRU&t;SPRN_TBRU&t;/* Time Base Read Upper Register */
DECL|macro|TBWL
mdefine_line|#define&t;TBWL&t;SPRN_TBWL&t;/* Time Base Write Lower Register */
DECL|macro|TBWU
mdefine_line|#define&t;TBWU&t;SPRN_TBWU&t;/* Time Base Write Upper Register */
DECL|macro|ICTC
mdefine_line|#define ICTC&t;1019
DECL|macro|THRM1
mdefine_line|#define&t;THRM1&t;SPRN_THRM1&t;/* Thermal Management Register 1 */
DECL|macro|THRM2
mdefine_line|#define&t;THRM2&t;SPRN_THRM2&t;/* Thermal Management Register 2 */
DECL|macro|THRM3
mdefine_line|#define&t;THRM3&t;SPRN_THRM3&t;/* Thermal Management Register 3 */
DECL|macro|XER
mdefine_line|#define&t;XER&t;SPRN_XER
multiline_comment|/* Processor Version Register */
multiline_comment|/* Processor Version Register (PVR) field extraction */
DECL|macro|PVR_VER
mdefine_line|#define&t;PVR_VER(pvr)  (((pvr) &gt;&gt;  16) &amp; 0xFFFF)&t;/* Version field */
DECL|macro|PVR_REV
mdefine_line|#define&t;PVR_REV(pvr)  (((pvr) &gt;&gt;   0) &amp; 0xFFFF)&t;/* Revison field */
multiline_comment|/*&n; * IBM has further subdivided the standard PowerPC 16-bit version and&n; * revision subfields of the PVR for the PowerPC 403s into the following:&n; */
DECL|macro|PVR_FAM
mdefine_line|#define&t;PVR_FAM(pvr)&t;(((pvr) &gt;&gt; 20) &amp; 0xFFF)&t;/* Family field */
DECL|macro|PVR_MEM
mdefine_line|#define&t;PVR_MEM(pvr)&t;(((pvr) &gt;&gt; 16) &amp; 0xF)&t;/* Member field */
DECL|macro|PVR_CORE
mdefine_line|#define&t;PVR_CORE(pvr)&t;(((pvr) &gt;&gt; 12) &amp; 0xF)&t;/* Core field */
DECL|macro|PVR_CFG
mdefine_line|#define&t;PVR_CFG(pvr)&t;(((pvr) &gt;&gt;  8) &amp; 0xF)&t;/* Configuration field */
DECL|macro|PVR_MAJ
mdefine_line|#define&t;PVR_MAJ(pvr)&t;(((pvr) &gt;&gt;  4) &amp; 0xF)&t;/* Major revision field */
DECL|macro|PVR_MIN
mdefine_line|#define&t;PVR_MIN(pvr)&t;(((pvr) &gt;&gt;  0) &amp; 0xF)&t;/* Minor revision field */
multiline_comment|/* Processor Version Numbers */
DECL|macro|PVR_403GA
mdefine_line|#define&t;PVR_403GA&t;0x00200000
DECL|macro|PVR_403GB
mdefine_line|#define&t;PVR_403GB&t;0x00200100
DECL|macro|PVR_403GC
mdefine_line|#define&t;PVR_403GC&t;0x00200200
DECL|macro|PVR_403GCX
mdefine_line|#define&t;PVR_403GCX&t;0x00201400
DECL|macro|PVR_405GP
mdefine_line|#define&t;PVR_405GP&t;0x40110000
DECL|macro|PVR_STB03XXX
mdefine_line|#define&t;PVR_STB03XXX&t;0x40310000
DECL|macro|PVR_NP405H
mdefine_line|#define&t;PVR_NP405H&t;0x41410000
DECL|macro|PVR_NP405L
mdefine_line|#define&t;PVR_NP405L&t;0x41610000
DECL|macro|PVR_440GP_RB
mdefine_line|#define PVR_440GP_RB&t;0x40120440
DECL|macro|PVR_440GP_RC1
mdefine_line|#define PVR_440GP_RC1&t;0x40120481
DECL|macro|PVR_440GP_RC2
mdefine_line|#define PVR_440GP_RC2&t;0x40200481
DECL|macro|PVR_440GX_RC1
mdefine_line|#define PVR_440GX_RC1&t;0x51b21850
DECL|macro|PVR_601
mdefine_line|#define&t;PVR_601&t;&t;0x00010000
DECL|macro|PVR_602
mdefine_line|#define&t;PVR_602&t;&t;0x00050000
DECL|macro|PVR_603
mdefine_line|#define&t;PVR_603&t;&t;0x00030000
DECL|macro|PVR_603e
mdefine_line|#define&t;PVR_603e&t;0x00060000
DECL|macro|PVR_603ev
mdefine_line|#define&t;PVR_603ev&t;0x00070000
DECL|macro|PVR_603r
mdefine_line|#define&t;PVR_603r&t;0x00071000
DECL|macro|PVR_604
mdefine_line|#define&t;PVR_604&t;&t;0x00040000
DECL|macro|PVR_604e
mdefine_line|#define&t;PVR_604e&t;0x00090000
DECL|macro|PVR_604r
mdefine_line|#define&t;PVR_604r&t;0x000A0000
DECL|macro|PVR_620
mdefine_line|#define&t;PVR_620&t;&t;0x00140000
DECL|macro|PVR_740
mdefine_line|#define&t;PVR_740&t;&t;0x00080000
DECL|macro|PVR_750
mdefine_line|#define&t;PVR_750&t;&t;PVR_740
DECL|macro|PVR_740P
mdefine_line|#define&t;PVR_740P&t;0x10080000
DECL|macro|PVR_750P
mdefine_line|#define&t;PVR_750P&t;PVR_740P
DECL|macro|PVR_7400
mdefine_line|#define&t;PVR_7400&t;0x000C0000
DECL|macro|PVR_7410
mdefine_line|#define&t;PVR_7410&t;0x800C0000
DECL|macro|PVR_7450
mdefine_line|#define&t;PVR_7450&t;0x80000000
multiline_comment|/*&n; * For the 8xx processors, all of them report the same PVR family for&n; * the PowerPC core. The various versions of these processors must be&n; * differentiated by the version number in the Communication Processor&n; * Module (CPM).&n; */
DECL|macro|PVR_821
mdefine_line|#define&t;PVR_821&t;&t;0x00500000
DECL|macro|PVR_823
mdefine_line|#define&t;PVR_823&t;&t;PVR_821
DECL|macro|PVR_850
mdefine_line|#define&t;PVR_850&t;&t;PVR_821
DECL|macro|PVR_860
mdefine_line|#define&t;PVR_860&t;&t;PVR_821
DECL|macro|PVR_8240
mdefine_line|#define&t;PVR_8240&t;0x00810100
DECL|macro|PVR_8245
mdefine_line|#define&t;PVR_8245&t;0x80811014
DECL|macro|PVR_8260
mdefine_line|#define&t;PVR_8260&t;PVR_8240
multiline_comment|/* We only need to define a new _MACH_xxx for machines which are part of&n; * a configuration which supports more than one type of different machine.&n; * This is currently limited to CONFIG_PPC_MULTIPLATFORM and CHRP/PReP/PMac. -- Tom&n; */
DECL|macro|_MACH_prep
mdefine_line|#define _MACH_prep&t;0x00000001
DECL|macro|_MACH_Pmac
mdefine_line|#define _MACH_Pmac&t;0x00000002&t;/* pmac or pmac clone (non-chrp) */
DECL|macro|_MACH_chrp
mdefine_line|#define _MACH_chrp&t;0x00000004&t;/* chrp machine */
multiline_comment|/* see residual.h for these */
DECL|macro|_PREP_Motorola
mdefine_line|#define _PREP_Motorola 0x01  /* motorola prep */
DECL|macro|_PREP_Firm
mdefine_line|#define _PREP_Firm     0x02  /* firmworks prep */
DECL|macro|_PREP_IBM
mdefine_line|#define _PREP_IBM      0x00  /* ibm prep */
DECL|macro|_PREP_Bull
mdefine_line|#define _PREP_Bull     0x03  /* bull prep */
multiline_comment|/* these are arbitrary */
DECL|macro|_CHRP_Motorola
mdefine_line|#define _CHRP_Motorola 0x04  /* motorola chrp, the cobra */
DECL|macro|_CHRP_IBM
mdefine_line|#define _CHRP_IBM      0x05  /* IBM chrp, the longtrail and longtrail 2 */
DECL|macro|_GLOBAL
mdefine_line|#define _GLOBAL(n)&bslash;&n;        .stabs __stringify(n:F-1),N_FUN,0,0,n;&bslash;&n;&t;.globl n;&bslash;&n;n:
multiline_comment|/* Macros for setting and retrieving special purpose registers */
DECL|macro|stringify
mdefine_line|#define stringify(s)&t;tostring(s)
DECL|macro|tostring
mdefine_line|#define tostring(s)&t;#s
DECL|macro|mfmsr
mdefine_line|#define mfmsr()&t;&t;({unsigned int rval; &bslash;&n;&t;&t;&t;asm volatile(&quot;mfmsr %0&quot; : &quot;=r&quot; (rval)); rval;})
DECL|macro|mtmsr
mdefine_line|#define mtmsr(v)&t;asm volatile(&quot;mtmsr %0&quot; : : &quot;r&quot; (v))
DECL|macro|mfspr
mdefine_line|#define mfspr(rn)&t;({unsigned int rval; &bslash;&n;&t;&t;&t;asm volatile(&quot;mfspr %0,&quot; stringify(rn) &bslash;&n;&t;&t;&t;&t;     : &quot;=r&quot; (rval)); rval;})
DECL|macro|mtspr
mdefine_line|#define mtspr(rn, v)&t;asm volatile(&quot;mtspr &quot; stringify(rn) &quot;,%0&quot; : : &quot;r&quot; (v))
DECL|macro|mfsrin
mdefine_line|#define mfsrin(v)&t;({unsigned int rval; &bslash;&n;&t;&t;&t;asm volatile(&quot;mfsrin %0,%1&quot; : &quot;=r&quot; (rval) : &quot;r&quot; (v)); &bslash;&n;&t;&t;&t;&t;&t;rval;})
DECL|macro|proc_trap
mdefine_line|#define proc_trap()  &t;asm volatile(&quot;trap&quot;)
multiline_comment|/* Segment Registers */
DECL|macro|SR0
mdefine_line|#define SR0&t;0
DECL|macro|SR1
mdefine_line|#define SR1&t;1
DECL|macro|SR2
mdefine_line|#define SR2&t;2
DECL|macro|SR3
mdefine_line|#define SR3&t;3
DECL|macro|SR4
mdefine_line|#define SR4&t;4
DECL|macro|SR5
mdefine_line|#define SR5&t;5
DECL|macro|SR6
mdefine_line|#define SR6&t;6
DECL|macro|SR7
mdefine_line|#define SR7&t;7
DECL|macro|SR8
mdefine_line|#define SR8&t;8
DECL|macro|SR9
mdefine_line|#define SR9&t;9
DECL|macro|SR10
mdefine_line|#define SR10&t;10
DECL|macro|SR11
mdefine_line|#define SR11&t;11
DECL|macro|SR12
mdefine_line|#define SR12&t;12
DECL|macro|SR13
mdefine_line|#define SR13&t;13
DECL|macro|SR14
mdefine_line|#define SR14&t;14
DECL|macro|SR15
mdefine_line|#define SR15&t;15
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef CONFIG_PPC_MULTIPLATFORM
r_extern
r_int
id|_machine
suffix:semicolon
multiline_comment|/* what kind of prep workstation we are */
r_extern
r_int
id|_prep_type
suffix:semicolon
multiline_comment|/*&n; * This is used to identify the board type from a given PReP board&n; * vendor. Board revision is also made available.&n; */
r_extern
r_int
r_char
id|ucSystemType
suffix:semicolon
r_extern
r_int
r_char
id|ucBoardRev
suffix:semicolon
r_extern
r_int
r_char
id|ucBoardRevMaj
comma
id|ucBoardRevMin
suffix:semicolon
macro_line|#else
DECL|macro|_machine
mdefine_line|#define _machine 0
macro_line|#endif /* CONFIG_PPC_MULTIPLATFORM */
r_struct
id|task_struct
suffix:semicolon
r_void
id|start_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|nip
comma
r_int
r_int
id|sp
)paren
suffix:semicolon
r_void
id|release_thread
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
multiline_comment|/* Prepare to copy thread state - unlazy all lazy status */
r_extern
r_void
id|prepare_to_copy
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
multiline_comment|/*&n; * Create a new kernel thread.&n; */
r_extern
r_int
id|kernel_thread
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro
multiline_comment|/* Lazy FPU handling on uni-processor */
r_extern
r_struct
id|task_struct
op_star
id|last_task_used_math
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|last_task_used_altivec
suffix:semicolon
multiline_comment|/*&n; * this is the minimum allowable io space due to the location&n; * of the io areas on prep (first one at 0x80000000) but&n; * as soon as I get around to remapping the io areas with the BATs&n; * to match the mac we can raise this. -- Cort&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(CONFIG_TASK_SIZE)
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;(TASK_SIZE / 8 * 3)
r_typedef
r_struct
(brace
DECL|member|seg
r_int
r_int
id|seg
suffix:semicolon
DECL|typedef|mm_segment_t
)brace
id|mm_segment_t
suffix:semicolon
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
multiline_comment|/* Kernel stack pointer */
DECL|member|regs
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
multiline_comment|/* Pointer to saved register state */
DECL|member|fs
id|mm_segment_t
id|fs
suffix:semicolon
multiline_comment|/* for get_fs() validation */
DECL|member|pgdir
r_void
op_star
id|pgdir
suffix:semicolon
multiline_comment|/* root of page-table tree */
DECL|member|fpexc_mode
r_int
id|fpexc_mode
suffix:semicolon
multiline_comment|/* floating-point exception mode */
DECL|member|last_syscall
r_int
r_int
id|last_syscall
suffix:semicolon
macro_line|#ifdef CONFIG_4xx
DECL|member|dbcr0
r_int
r_int
id|dbcr0
suffix:semicolon
multiline_comment|/* debug control register values */
DECL|member|dbcr1
r_int
r_int
id|dbcr1
suffix:semicolon
macro_line|#endif
DECL|member|fpr
r_float
id|fpr
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Complete floating point set */
DECL|member|fpscr_pad
r_int
r_int
id|fpscr_pad
suffix:semicolon
multiline_comment|/* fpr ... fpscr must be contiguous */
DECL|member|fpscr
r_int
r_int
id|fpscr
suffix:semicolon
multiline_comment|/* Floating point status */
macro_line|#ifdef CONFIG_ALTIVEC
multiline_comment|/* Complete AltiVec register set */
id|vector128
id|vr
(braket
l_int|32
)braket
id|__attribute
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* AltiVec status */
id|vector128
id|vscr
id|__attribute
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
DECL|member|vrsave
r_int
r_int
id|vrsave
suffix:semicolon
DECL|member|used_vr
r_int
id|used_vr
suffix:semicolon
multiline_comment|/* set if process has used altivec */
macro_line|#endif /* CONFIG_ALTIVEC */
)brace
suffix:semicolon
DECL|macro|INIT_SP
mdefine_line|#define INIT_SP&t;&t;(sizeof(init_stack) + (unsigned long) &amp;init_stack)
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  { &bslash;&n;&t;.ksp = INIT_SP, &bslash;&n;&t;.fs = KERNEL_DS, &bslash;&n;&t;.pgdir = swapper_pg_dir, &bslash;&n;&t;.fpexc_mode = MSR_FE0 | MSR_FE1, &bslash;&n;}
multiline_comment|/*&n; * Return saved PC of a blocked thread. For now, this is the &quot;user&quot; PC&n; */
DECL|macro|thread_saved_pc
mdefine_line|#define thread_saved_pc(tsk)&t;&bslash;&n;&t;((tsk)-&gt;thread.regs? (tsk)-&gt;thread.regs-&gt;nip: 0)
r_int
r_int
id|get_wchan
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
suffix:semicolon
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)  ((tsk)-&gt;thread.regs? (tsk)-&gt;thread.regs-&gt;nip: 0)
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)  ((tsk)-&gt;thread.regs? (tsk)-&gt;thread.regs-&gt;gpr[1]: 0)
multiline_comment|/* Get/set floating-point exception mode */
DECL|macro|GET_FPEXC_CTL
mdefine_line|#define GET_FPEXC_CTL(tsk, adr)&t;get_fpexc_mode((tsk), (adr))
DECL|macro|SET_FPEXC_CTL
mdefine_line|#define SET_FPEXC_CTL(tsk, val)&t;set_fpexc_mode((tsk), (val))
r_extern
r_int
id|get_fpexc_mode
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|adr
)paren
suffix:semicolon
r_extern
r_int
id|set_fpexc_mode
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|val
)paren
suffix:semicolon
DECL|function|__unpack_fe01
r_static
r_inline
r_int
r_int
id|__unpack_fe01
c_func
(paren
r_int
r_int
id|msr_bits
)paren
(brace
r_return
(paren
(paren
id|msr_bits
op_amp
id|MSR_FE0
)paren
op_rshift
l_int|10
)paren
op_or
(paren
(paren
id|msr_bits
op_amp
id|MSR_FE1
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|__pack_fe01
r_static
r_inline
r_int
r_int
id|__pack_fe01
c_func
(paren
r_int
r_int
id|fpmode
)paren
(brace
r_return
(paren
(paren
id|fpmode
op_lshift
l_int|10
)paren
op_amp
id|MSR_FE0
)paren
op_or
(paren
(paren
id|fpmode
op_lshift
l_int|8
)paren
op_amp
id|MSR_FE1
)paren
suffix:semicolon
)brace
multiline_comment|/* in process.c - for early bootup debug -- Cort */
r_int
id|ll_printk
c_func
(paren
r_const
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
r_void
id|ll_puts
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* In misc.c */
r_void
id|_nmask_and_or_msr
c_func
(paren
r_int
r_int
id|nmask
comma
r_int
r_int
id|or_val
)paren
suffix:semicolon
DECL|macro|have_of
mdefine_line|#define have_of (_machine == _MACH_chrp || _machine == _MACH_Pmac)
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;barrier()
multiline_comment|/*&n; * Prefetch macros.&n; */
DECL|macro|ARCH_HAS_PREFETCH
mdefine_line|#define ARCH_HAS_PREFETCH
DECL|macro|ARCH_HAS_PREFETCHW
mdefine_line|#define ARCH_HAS_PREFETCHW
DECL|macro|ARCH_HAS_SPINLOCK_PREFETCH
mdefine_line|#define ARCH_HAS_SPINLOCK_PREFETCH
DECL|function|prefetch
r_extern
r_inline
r_void
id|prefetch
c_func
(paren
r_const
r_void
op_star
id|x
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;dcbt 0,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
)brace
DECL|function|prefetchw
r_extern
r_inline
r_void
id|prefetchw
c_func
(paren
r_const
r_void
op_star
id|x
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;dcbtst 0,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
)brace
DECL|macro|spin_lock_prefetch
mdefine_line|#define spin_lock_prefetch(x)&t;prefetchw(x)
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __ASM_PPC_PROCESSOR_H */
macro_line|#endif /* __KERNEL__ */
eof
