multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;mcfdebug.h -- ColdFire Debug Module support.&n; *&n; * &t;(C) Copyright 2001, Lineo Inc. (www.lineo.com) &n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef mcfdebug_h
DECL|macro|mcfdebug_h
mdefine_line|#define mcfdebug_h
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Define the debug module registers */
DECL|macro|MCFDEBUG_CSR
mdefine_line|#define MCFDEBUG_CSR&t;0x0&t;&t;&t;/* Configuration status&t;&t;*/
DECL|macro|MCFDEBUG_BAAR
mdefine_line|#define MCFDEBUG_BAAR&t;0x5&t;&t;&t;/* BDM address attribute&t;*/
DECL|macro|MCFDEBUG_AATR
mdefine_line|#define MCFDEBUG_AATR&t;0x6&t;&t;&t;/* Address attribute trigger&t;*/
DECL|macro|MCFDEBUG_TDR
mdefine_line|#define MCFDEBUG_TDR&t;0x7&t;&t;&t;/* Trigger definition&t;&t;*/
DECL|macro|MCFDEBUG_PBR
mdefine_line|#define MCFDEBUG_PBR&t;0x8&t;&t;&t;/* PC breakpoint&t;&t;*/
DECL|macro|MCFDEBUG_PBMR
mdefine_line|#define MCFDEBUG_PBMR&t;0x9&t;&t;&t;/* PC breakpoint mask&t;&t;*/
DECL|macro|MCFDEBUG_ABHR
mdefine_line|#define MCFDEBUG_ABHR&t;0xc&t;&t;&t;/* High address breakpoint&t;*/
DECL|macro|MCFDEBUG_ABLR
mdefine_line|#define MCFDEBUG_ABLR&t;0xd&t;&t;&t;/* Low address breakpoint&t;*/
DECL|macro|MCFDEBUG_DBR
mdefine_line|#define MCFDEBUG_DBR&t;0xe&t;&t;&t;/* Data breakpoint&t;&t;*/
DECL|macro|MCFDEBUG_DBMR
mdefine_line|#define MCFDEBUG_DBMR&t;0xf&t;&t;&t;/* Data breakpoint mask&t;&t;*/
multiline_comment|/* Define some handy constants for the trigger definition register */
DECL|macro|MCFDEBUG_TDR_TRC_DISP
mdefine_line|#define MCFDEBUG_TDR_TRC_DISP&t;0x00000000&t;/* display on DDATA only&t;*/
DECL|macro|MCFDEBUG_TDR_TRC_HALT
mdefine_line|#define MCFDEBUG_TDR_TRC_HALT&t;0x40000000&t;/* Processor halt on BP&t;&t;*/
DECL|macro|MCFDEBUG_TDR_TRC_INTR
mdefine_line|#define MCFDEBUG_TDR_TRC_INTR&t;0x80000000&t;/* Debug intr on BP&t;&t;*/
DECL|macro|MCFDEBUG_TDR_LXT1
mdefine_line|#define MCFDEBUG_TDR_LXT1&t;0x00004000&t;/* TDR level 1&t;&t;&t;*/
DECL|macro|MCFDEBUG_TDR_LXT2
mdefine_line|#define MCFDEBUG_TDR_LXT2&t;0x00008000&t;/* TDR level 2&t;&t;&t;*/
DECL|macro|MCFDEBUG_TDR_EBL1
mdefine_line|#define MCFDEBUG_TDR_EBL1&t;0x00002000&t;/* Enable breakpoint level 1&t;*/
DECL|macro|MCFDEBUG_TDR_EBL2
mdefine_line|#define MCFDEBUG_TDR_EBL2&t;0x20000000&t;/* Enable breakpoint level 2&t;*/
DECL|macro|MCFDEBUG_TDR_EDLW1
mdefine_line|#define MCFDEBUG_TDR_EDLW1&t;0x00001000&t;/* Enable data BP longword&t;*/
DECL|macro|MCFDEBUG_TDR_EDLW2
mdefine_line|#define MCFDEBUG_TDR_EDLW2&t;0x10000000
DECL|macro|MCFDEBUG_TDR_EDWL1
mdefine_line|#define MCFDEBUG_TDR_EDWL1&t;0x00000800&t;/* Enable data BP lower word&t;*/
DECL|macro|MCFDEBUG_TDR_EDWL2
mdefine_line|#define MCFDEBUG_TDR_EDWL2&t;0x08000000
DECL|macro|MCFDEBUG_TDR_EDWU1
mdefine_line|#define MCFDEBUG_TDR_EDWU1&t;0x00000400&t;/* Enable data BP upper word&t;*/
DECL|macro|MCFDEBUG_TDR_EDWU2
mdefine_line|#define MCFDEBUG_TDR_EDWU2&t;0x04000000
DECL|macro|MCFDEBUG_TDR_EDLL1
mdefine_line|#define MCFDEBUG_TDR_EDLL1&t;0x00000200&t;/* Enable data BP low low byte&t;*/
DECL|macro|MCFDEBUG_TDR_EDLL2
mdefine_line|#define MCFDEBUG_TDR_EDLL2&t;0x02000000
DECL|macro|MCFDEBUG_TDR_EDLM1
mdefine_line|#define MCFDEBUG_TDR_EDLM1&t;0x00000100&t;/* Enable data BP low mid byte&t;*/
DECL|macro|MCFDEBUG_TDR_EDLM2
mdefine_line|#define MCFDEBUG_TDR_EDLM2&t;0x01000000
DECL|macro|MCFDEBUG_TDR_EDUM1
mdefine_line|#define MCFDEBUG_TDR_EDUM1&t;0x00000080&t;/* Enable data BP up mid byte&t;*/
DECL|macro|MCFDEBUG_TDR_EDUM2
mdefine_line|#define MCFDEBUG_TDR_EDUM2&t;0x00800000
DECL|macro|MCFDEBUG_TDR_EDUU1
mdefine_line|#define MCFDEBUG_TDR_EDUU1&t;0x00000040&t;/* Enable data BP up up byte&t;*/
DECL|macro|MCFDEBUG_TDR_EDUU2
mdefine_line|#define MCFDEBUG_TDR_EDUU2&t;0x00400000
DECL|macro|MCFDEBUG_TDR_DI1
mdefine_line|#define MCFDEBUG_TDR_DI1&t;0x00000020&t;/* Data BP invert&t;&t;*/
DECL|macro|MCFDEBUG_TDR_DI2
mdefine_line|#define MCFDEBUG_TDR_DI2&t;0x00200000
DECL|macro|MCFDEBUG_TDR_EAI1
mdefine_line|#define MCFDEBUG_TDR_EAI1&t;0x00000010&t;/* Enable address BP inverted&t;*/
DECL|macro|MCFDEBUG_TDR_EAI2
mdefine_line|#define MCFDEBUG_TDR_EAI2&t;0x00100000
DECL|macro|MCFDEBUG_TDR_EAR1
mdefine_line|#define MCFDEBUG_TDR_EAR1&t;0x00000008&t;/* Enable address BP range&t;*/
DECL|macro|MCFDEBUG_TDR_EAR2
mdefine_line|#define MCFDEBUG_TDR_EAR2&t;0x00080000
DECL|macro|MCFDEBUG_TDR_EAL1
mdefine_line|#define MCFDEBUG_TDR_EAL1&t;0x00000004&t;/* Enable address BP low&t;*/
DECL|macro|MCFDEBUG_TDR_EAL2
mdefine_line|#define MCFDEBUG_TDR_EAL2&t;0x00040000
DECL|macro|MCFDEBUG_TDR_EPC1
mdefine_line|#define MCFDEBUG_TDR_EPC1&t;0x00000002&t;/* Enable PC BP&t;&t;&t;*/
DECL|macro|MCFDEBUG_TDR_EPC2
mdefine_line|#define MCFDEBUG_TDR_EPC2&t;0x00020000
DECL|macro|MCFDEBUG_TDR_PCI1
mdefine_line|#define MCFDEBUG_TDR_PCI1&t;0x00000001&t;/* PC BP invert&t;&t;&t;*/
DECL|macro|MCFDEBUG_TDR_PCI2
mdefine_line|#define MCFDEBUG_TDR_PCI2&t;0x00010000
multiline_comment|/* Constants for the address attribute trigger register */
DECL|macro|MCFDEBUG_AAR_RESET
mdefine_line|#define MCFDEBUG_AAR_RESET&t;0x00000005
multiline_comment|/* Fields not yet implemented */
multiline_comment|/* And some definitions for the writable sections of the CSR */
DECL|macro|MCFDEBUG_CSR_RESET
mdefine_line|#define MCFDEBUG_CSR_RESET&t;0x00100000
DECL|macro|MCFDEBUG_CSR_PSTCLK
mdefine_line|#define MCFDEBUG_CSR_PSTCLK&t;0x00020000&t;/* PSTCLK disable&t;&t;*/
DECL|macro|MCFDEBUG_CSR_IPW
mdefine_line|#define MCFDEBUG_CSR_IPW&t;0x00010000&t;/* Inhibit processor writes&t;*/
DECL|macro|MCFDEBUG_CSR_MAP
mdefine_line|#define MCFDEBUG_CSR_MAP&t;0x00008000&t;/* Processor refs in emul mode&t;*/
DECL|macro|MCFDEBUG_CSR_TRC
mdefine_line|#define MCFDEBUG_CSR_TRC&t;0x00004000&t;/* Emul mode on trace exception&t;*/
DECL|macro|MCFDEBUG_CSR_EMU
mdefine_line|#define MCFDEBUG_CSR_EMU&t;0x00002000&t;/* Force emulation mode&t;&t;*/
DECL|macro|MCFDEBUG_CSR_DDC_READ
mdefine_line|#define MCFDEBUG_CSR_DDC_READ&t;0x00000800&t;/* Debug data control&t;&t;*/
DECL|macro|MCFDEBUG_CSR_DDC_WRITE
mdefine_line|#define MCFDEBUG_CSR_DDC_WRITE&t;0x00001000
DECL|macro|MCFDEBUG_CSR_UHE
mdefine_line|#define MCFDEBUG_CSR_UHE&t;0x00000400&t;/* User mode halt enable&t;*/
DECL|macro|MCFDEBUG_CSR_BTB0
mdefine_line|#define MCFDEBUG_CSR_BTB0&t;0x00000000&t;/* Branch target 0 bytes&t;*/
DECL|macro|MCFDEBUG_CSR_BTB2
mdefine_line|#define MCFDEBUG_CSR_BTB2&t;0x00000100&t;/* Branch target 2 bytes&t;*/
DECL|macro|MCFDEBUG_CSR_BTB3
mdefine_line|#define MCFDEBUG_CSR_BTB3&t;0x00000200&t;/* Branch target 3 bytes&t;*/
DECL|macro|MCFDEBUG_CSR_BTB4
mdefine_line|#define MCFDEBUG_CSR_BTB4&t;0x00000300&t;/* Branch target 4 bytes&t;*/
DECL|macro|MCFDEBUG_CSR_NPL
mdefine_line|#define MCFDEBUG_CSR_NPL&t;0x00000040&t;/* Non-pipelined mode&t;&t;*/
DECL|macro|MCFDEBUG_CSR_SSM
mdefine_line|#define MCFDEBUG_CSR_SSM&t;0x00000010&t;/* Single step mode&t;&t;*/
multiline_comment|/* Constants for the BDM address attribute register */
DECL|macro|MCFDEBUG_BAAR_RESET
mdefine_line|#define MCFDEBUG_BAAR_RESET&t;0x00000005
multiline_comment|/* Fields not yet implemented */
multiline_comment|/* This routine wrappers up the wdebug asm instruction so that the register&n; * and value can be relatively easily specified.  The biggest hassle here is&n; * that the debug module instructions (2 longs) must be long word aligned and&n; * some pointer fiddling is performed to ensure this.&n; */
DECL|function|wdebug
r_extern
r_inline
r_void
id|wdebug
c_func
(paren
r_int
id|reg
comma
r_int
r_int
id|data
)paren
(brace
r_int
r_int
id|dbg_spc
(braket
l_int|6
)braket
suffix:semicolon
r_int
r_int
op_star
id|dbg
suffix:semicolon
singleline_comment|// Force alignment to long word boundary
id|dbg
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
(paren
(paren
(paren
r_int
r_int
)paren
id|dbg_spc
)paren
op_plus
l_int|3
)paren
op_amp
l_int|0xfffffffc
)paren
suffix:semicolon
singleline_comment|// Build up the debug instruction
id|dbg
(braket
l_int|0
)braket
op_assign
l_int|0x2c80
op_or
(paren
id|reg
op_amp
l_int|0xf
)paren
suffix:semicolon
id|dbg
(braket
l_int|1
)braket
op_assign
(paren
id|data
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
suffix:semicolon
id|dbg
(braket
l_int|2
)braket
op_assign
id|data
op_amp
l_int|0xffff
suffix:semicolon
id|dbg
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
singleline_comment|// Perform the wdebug instruction
macro_line|#if 0
singleline_comment|// This strain is for gas which doesn&squot;t have the wdebug instructions defined
id|asm
c_func
(paren
l_string|&quot;move.l&t;%0, %%a0&bslash;n&bslash;t&quot;
l_string|&quot;.word&t;0xfbd0&bslash;n&bslash;t&quot;
l_string|&quot;.word&t;0x0003&bslash;n&bslash;t&quot;
op_scope_resolution
l_string|&quot;g&quot;
(paren
id|dbg
)paren
suffix:colon
l_string|&quot;a0&quot;
)paren
suffix:semicolon
macro_line|#else
singleline_comment|// And this is for when it does
id|asm
c_func
(paren
l_string|&quot;wdebug&t;(%0)&quot;
op_scope_resolution
l_string|&quot;a&quot;
(paren
id|dbg
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
eof
