multiline_comment|/*!**************************************************************************&n;*!                                                            &n;*! MACROS:&n;*!   IO_MASK(reg,field)&n;*!   IO_STATE(reg,field,state)&n;*!   IO_EXTRACT(reg,field,val)&n;*!   IO_STATE_VALUE(reg,field,state)&n;*!   IO_BITNR(reg,field)&n;*!   IO_WIDTH(reg,field)&n;*!   IO_FIELD(reg,field,val)&n;*!   IO_RD(reg)&n;*!   All moderegister addresses and fields of these.&n;*!&n;*!**************************************************************************/
macro_line|#ifndef __sv_addr_ag_h__
DECL|macro|__sv_addr_ag_h__
mdefine_line|#define __sv_addr_ag_h__
DECL|macro|__test_sv_addr__
mdefine_line|#define __test_sv_addr__ 0
multiline_comment|/*------------------------------------------------------------&n;!* General macros to manipulate moderegisters.&n;!*-----------------------------------------------------------*/
multiline_comment|/* IO_MASK returns a mask for a specified bitfield in a register.&n;   Note that this macro doesn&squot;t work when field width is 32 bits. */
DECL|macro|IO_MASK
mdefine_line|#define IO_MASK(reg,field) &bslash;&n;    ( ( ( 1 &lt;&lt; reg##__##field##__WIDTH ) - 1 ) &lt;&lt; reg##__##field##__BITNR )
multiline_comment|/* IO_STATE returns a constant corresponding to a one of the symbolic&n;   states that the bitfield can have. (Shifted to correct position)  */
DECL|macro|IO_STATE
mdefine_line|#define IO_STATE(reg,field,state) &bslash;&n;    ( reg##__##field##__##state &lt;&lt; reg##__##field##__BITNR )
multiline_comment|/* IO_EXTRACT returns the masked and shifted value corresponding to the&n;   bitfield can have. */
DECL|macro|IO_EXTRACT
mdefine_line|#define IO_EXTRACT(reg,field,val) ( (( ( ( 1 &lt;&lt; reg##__##field##__WIDTH ) &bslash;&n;     - 1 ) &lt;&lt; reg##__##field##__BITNR ) &amp; (val)) &gt;&gt; reg##__##field##__BITNR )
multiline_comment|/* IO_STATE_VALUE returns a constant corresponding to a one of the symbolic&n;   states that the bitfield can have. (Not shifted)  */
DECL|macro|IO_STATE_VALUE
mdefine_line|#define IO_STATE_VALUE(reg,field,state) ( reg##__##field##__##state )
multiline_comment|/* IO_FIELD shifts the val parameter to be aligned with the bitfield&n;   specified. */
DECL|macro|IO_FIELD
mdefine_line|#define IO_FIELD(reg,field,val) ((val) &lt;&lt; reg##__##field##__BITNR)
multiline_comment|/* IO_BITNR returns the starting bitnumber of a bitfield. Bit 0 is&n;   LSB and the returned bitnumber is LSB of the field. */
DECL|macro|IO_BITNR
mdefine_line|#define IO_BITNR(reg,field) (reg##__##field##__BITNR)
multiline_comment|/* IO_WIDTH returns the width, in bits, of a bitfield. */
DECL|macro|IO_WIDTH
mdefine_line|#define IO_WIDTH(reg,field) (reg##__##field##__WIDTH)
multiline_comment|/*--- Obsolete. Kept for backw compatibility. ---*/
multiline_comment|/* Reads (or writes) a byte/uword/udword from the specified mode&n;   register. */
DECL|macro|IO_RD
mdefine_line|#define IO_RD(reg) (*(volatile u32*)(reg))
DECL|macro|IO_RD_B
mdefine_line|#define IO_RD_B(reg) (*(volatile u8*)(reg))
DECL|macro|IO_RD_W
mdefine_line|#define IO_RD_W(reg) (*(volatile u16*)(reg))
DECL|macro|IO_RD_D
mdefine_line|#define IO_RD_D(reg) (*(volatile u32*)(reg))
multiline_comment|/*------------------------------------------------------------&n;!* Start addresses of the different memory areas.&n;!*-----------------------------------------------------------*/
DECL|macro|MEM_CSE0_START
mdefine_line|#define MEM_CSE0_START (0x00000000)
DECL|macro|MEM_CSE1_START
mdefine_line|#define MEM_CSE1_START (0x04000000)
DECL|macro|MEM_CSR0_START
mdefine_line|#define MEM_CSR0_START (0x08000000)
DECL|macro|MEM_CSR1_START
mdefine_line|#define MEM_CSR1_START (0x0c000000)
DECL|macro|MEM_CSP0_START
mdefine_line|#define MEM_CSP0_START (0x10000000)
DECL|macro|MEM_CSP1_START
mdefine_line|#define MEM_CSP1_START (0x14000000)
DECL|macro|MEM_CSP2_START
mdefine_line|#define MEM_CSP2_START (0x18000000)
DECL|macro|MEM_CSP3_START
mdefine_line|#define MEM_CSP3_START (0x1c000000)
DECL|macro|MEM_CSP4_START
mdefine_line|#define MEM_CSP4_START (0x20000000)
DECL|macro|MEM_CSP5_START
mdefine_line|#define MEM_CSP5_START (0x24000000)
DECL|macro|MEM_CSP6_START
mdefine_line|#define MEM_CSP6_START (0x28000000)
DECL|macro|MEM_CSP7_START
mdefine_line|#define MEM_CSP7_START (0x2c000000)
DECL|macro|MEM_DRAM_START
mdefine_line|#define MEM_DRAM_START (0x40000000)
DECL|macro|MEM_NON_CACHEABLE
mdefine_line|#define MEM_NON_CACHEABLE (0x80000000)
multiline_comment|/*------------------------------------------------------------&n;!* Type casts used in mode register macros, making pointer&n;!* dereferencing possible. Empty in assembler.&n;!*-----------------------------------------------------------*/
macro_line|#ifndef __ASSEMBLER__
DECL|macro|IO_TYPECAST_UDWORD
macro_line|# define  IO_TYPECAST_UDWORD  (volatile u32*)
DECL|macro|IO_TYPECAST_RO_UDWORD
macro_line|# define  IO_TYPECAST_RO_UDWORD  (const volatile u32*)
DECL|macro|IO_TYPECAST_UWORD
macro_line|# define  IO_TYPECAST_UWORD  (volatile u16*)
DECL|macro|IO_TYPECAST_RO_UWORD
macro_line|# define  IO_TYPECAST_RO_UWORD  (const volatile u16*)
DECL|macro|IO_TYPECAST_BYTE
macro_line|# define  IO_TYPECAST_BYTE  (volatile u8*)
DECL|macro|IO_TYPECAST_RO_BYTE
macro_line|# define  IO_TYPECAST_RO_BYTE  (const volatile u8*)
macro_line|#else
DECL|macro|IO_TYPECAST_UDWORD
macro_line|# define  IO_TYPECAST_UDWORD
DECL|macro|IO_TYPECAST_RO_UDWORD
macro_line|# define  IO_TYPECAST_RO_UDWORD
DECL|macro|IO_TYPECAST_UWORD
macro_line|# define  IO_TYPECAST_UWORD
DECL|macro|IO_TYPECAST_RO_UWORD
macro_line|# define  IO_TYPECAST_RO_UWORD
DECL|macro|IO_TYPECAST_BYTE
macro_line|# define  IO_TYPECAST_BYTE
DECL|macro|IO_TYPECAST_RO_BYTE
macro_line|# define  IO_TYPECAST_RO_BYTE
macro_line|#endif
multiline_comment|/*------------------------------------------------------------*/
macro_line|#include &quot;sv_addr.agh&quot;
macro_line|#if __test_sv_addr__
multiline_comment|/* IO_MASK( R_BUS_CONFIG , CE ) */
id|IO_MASK
c_func
(paren
id|R_WAITSTATES
comma
id|SRAM_WS
)paren
id|IO_MASK
c_func
(paren
id|R_TEST
comma
id|W32
)paren
id|IO_STATE
c_func
(paren
id|R_BUS_CONFIG
comma
id|CE
comma
id|DISABLE
)paren
id|IO_STATE
c_func
(paren
id|R_BUS_CONFIG
comma
id|CE
comma
id|ENABLE
)paren
id|IO_STATE
c_func
(paren
id|R_DRAM_TIMING
comma
id|REF
comma
id|IVAL2
)paren
id|IO_MASK
c_func
(paren
id|R_DRAM_TIMING
comma
id|REF
)paren
id|IO_MASK
c_func
(paren
id|R_EXT_DMA_0_STAT
comma
id|TFR_COUNT
)paren
op_rshift
id|IO_BITNR
c_func
(paren
id|R_EXT_DMA_0_STAT
comma
id|TFR_COUNT
)paren
id|IO_RD
c_func
(paren
id|R_EXT_DMA_0_STAT
)paren
op_amp
id|IO_MASK
c_func
(paren
id|R_EXT_DMA_0_STAT
comma
id|S
)paren
op_eq
id|IO_STATE
c_func
(paren
id|R_EXT_DMA_0_STAT
comma
id|S
comma
id|STARTED
)paren
macro_line|#endif
macro_line|#endif  /* ifndef __sv_addr_ag_h__ */
eof
