multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/dma.h&n; *&n; * Generic SA1100 DMA support&n; *&n; * Copyright (C) 2000 Nicolas Pitre&n; *&n; */
macro_line|#ifndef __ASM_ARCH_DMA_H
DECL|macro|__ASM_ARCH_DMA_H
mdefine_line|#define __ASM_ARCH_DMA_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;hardware.h&quot;
multiline_comment|/*&n; * This is the maximum DMA address that can be DMAd to.&n; */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0xffffffff
multiline_comment|/*&n; * The regular generic DMA interface is inappropriate for the&n; * SA1100 DMA model.  None of the SA1100 specific drivers using&n; * DMA are portable anyway so it&squot;s pointless to try to twist the&n; * regular DMA API to accommodate them.&n; */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;0
multiline_comment|/*&n; * The SA1100 has six internal DMA channels.&n; */
DECL|macro|SA1100_DMA_CHANNELS
mdefine_line|#define SA1100_DMA_CHANNELS&t;6
multiline_comment|/*&n; * Maximum physical DMA buffer size&n; */
DECL|macro|MAX_DMA_SIZE
mdefine_line|#define MAX_DMA_SIZE&t;&t;0x1fff
DECL|macro|CUT_DMA_SIZE
mdefine_line|#define CUT_DMA_SIZE&t;&t;0x1000
multiline_comment|/*&n; * All possible SA1100 devices a DMA channel can be attached to.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|DMA_Ser0UDCWr
id|DMA_Ser0UDCWr
op_assign
id|DDAR_Ser0UDCWr
comma
multiline_comment|/* Ser. port 0 UDC Write */
DECL|enumerator|DMA_Ser0UDCRd
id|DMA_Ser0UDCRd
op_assign
id|DDAR_Ser0UDCRd
comma
multiline_comment|/* Ser. port 0 UDC Read */
DECL|enumerator|DMA_Ser1UARTWr
id|DMA_Ser1UARTWr
op_assign
id|DDAR_Ser1UARTWr
comma
multiline_comment|/* Ser. port 1 UART Write */
DECL|enumerator|DMA_Ser1UARTRd
id|DMA_Ser1UARTRd
op_assign
id|DDAR_Ser1UARTRd
comma
multiline_comment|/* Ser. port 1 UART Read */
DECL|enumerator|DMA_Ser1SDLCWr
id|DMA_Ser1SDLCWr
op_assign
id|DDAR_Ser1SDLCWr
comma
multiline_comment|/* Ser. port 1 SDLC Write */
DECL|enumerator|DMA_Ser1SDLCRd
id|DMA_Ser1SDLCRd
op_assign
id|DDAR_Ser1SDLCRd
comma
multiline_comment|/* Ser. port 1 SDLC Read */
DECL|enumerator|DMA_Ser2UARTWr
id|DMA_Ser2UARTWr
op_assign
id|DDAR_Ser2UARTWr
comma
multiline_comment|/* Ser. port 2 UART Write */
DECL|enumerator|DMA_Ser2UARTRd
id|DMA_Ser2UARTRd
op_assign
id|DDAR_Ser2UARTRd
comma
multiline_comment|/* Ser. port 2 UART Read */
DECL|enumerator|DMA_Ser2HSSPWr
id|DMA_Ser2HSSPWr
op_assign
id|DDAR_Ser2HSSPWr
comma
multiline_comment|/* Ser. port 2 HSSP Write */
DECL|enumerator|DMA_Ser2HSSPRd
id|DMA_Ser2HSSPRd
op_assign
id|DDAR_Ser2HSSPRd
comma
multiline_comment|/* Ser. port 2 HSSP Read */
DECL|enumerator|DMA_Ser3UARTWr
id|DMA_Ser3UARTWr
op_assign
id|DDAR_Ser3UARTWr
comma
multiline_comment|/* Ser. port 3 UART Write */
DECL|enumerator|DMA_Ser3UARTRd
id|DMA_Ser3UARTRd
op_assign
id|DDAR_Ser3UARTRd
comma
multiline_comment|/* Ser. port 3 UART Read */
DECL|enumerator|DMA_Ser4MCP0Wr
id|DMA_Ser4MCP0Wr
op_assign
id|DDAR_Ser4MCP0Wr
comma
multiline_comment|/* Ser. port 4 MCP 0 Write (audio) */
DECL|enumerator|DMA_Ser4MCP0Rd
id|DMA_Ser4MCP0Rd
op_assign
id|DDAR_Ser4MCP0Rd
comma
multiline_comment|/* Ser. port 4 MCP 0 Read (audio) */
DECL|enumerator|DMA_Ser4MCP1Wr
id|DMA_Ser4MCP1Wr
op_assign
id|DDAR_Ser4MCP1Wr
comma
multiline_comment|/* Ser. port 4 MCP 1 Write */
DECL|enumerator|DMA_Ser4MCP1Rd
id|DMA_Ser4MCP1Rd
op_assign
id|DDAR_Ser4MCP1Rd
comma
multiline_comment|/* Ser. port 4 MCP 1 Read */
DECL|enumerator|DMA_Ser4SSPWr
id|DMA_Ser4SSPWr
op_assign
id|DDAR_Ser4SSPWr
comma
multiline_comment|/* Ser. port 4 SSP Write (16 bits) */
DECL|enumerator|DMA_Ser4SSPRd
id|DMA_Ser4SSPRd
op_assign
id|DDAR_Ser4SSPRd
multiline_comment|/* Ser. port 4 SSP Read (16 bits) */
DECL|typedef|dma_device_t
)brace
id|dma_device_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|DDAR
r_volatile
id|u_long
id|DDAR
suffix:semicolon
DECL|member|SetDCSR
r_volatile
id|u_long
id|SetDCSR
suffix:semicolon
DECL|member|ClrDCSR
r_volatile
id|u_long
id|ClrDCSR
suffix:semicolon
DECL|member|RdDCSR
r_volatile
id|u_long
id|RdDCSR
suffix:semicolon
DECL|member|DBSA
r_volatile
id|dma_addr_t
id|DBSA
suffix:semicolon
DECL|member|DBTA
r_volatile
id|u_long
id|DBTA
suffix:semicolon
DECL|member|DBSB
r_volatile
id|dma_addr_t
id|DBSB
suffix:semicolon
DECL|member|DBTB
r_volatile
id|u_long
id|DBTB
suffix:semicolon
DECL|typedef|dma_regs_t
)brace
id|dma_regs_t
suffix:semicolon
DECL|typedef|dma_callback_t
r_typedef
r_void
(paren
op_star
id|dma_callback_t
)paren
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/*&n; * DMA function prototypes&n; */
r_extern
r_int
id|sa1100_request_dma
c_func
(paren
id|dma_device_t
id|device
comma
r_const
r_char
op_star
id|device_id
comma
id|dma_callback_t
id|callback
comma
r_void
op_star
id|data
comma
id|dma_regs_t
op_star
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|sa1100_free_dma
c_func
(paren
id|dma_regs_t
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|sa1100_start_dma
c_func
(paren
id|dma_regs_t
op_star
id|regs
comma
id|dma_addr_t
id|dma_ptr
comma
id|u_int
id|size
)paren
suffix:semicolon
r_extern
id|dma_addr_t
id|sa1100_get_dma_pos
c_func
(paren
id|dma_regs_t
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|sa1100_reset_dma
c_func
(paren
id|dma_regs_t
op_star
id|regs
)paren
suffix:semicolon
multiline_comment|/**&n; * &t;sa1100_stop_dma - stop DMA in progress&n; * &t;@regs: identifier for the channel to use&n; *&n; * &t;This stops DMA without clearing buffer pointers. Unlike&n; * &t;sa1100_clear_dma() this allows subsequent use of sa1100_resume_dma()&n; * &t;or sa1100_get_dma_pos().&n; *&n; * &t;The @regs identifier is provided by a successful call to&n; * &t;sa1100_request_dma().&n; **/
DECL|macro|sa1100_stop_dma
mdefine_line|#define sa1100_stop_dma(regs)&t;((regs)-&gt;ClrDCSR = DCSR_IE|DCSR_RUN)
multiline_comment|/**&n; * &t;sa1100_resume_dma - resume DMA on a stopped channel&n; * &t;@regs: identifier for the channel to use&n; *&n; * &t;This resumes DMA on a channel previously stopped with&n; * &t;sa1100_stop_dma().&n; *&n; * &t;The @regs identifier is provided by a successful call to&n; * &t;sa1100_request_dma().&n; **/
DECL|macro|sa1100_resume_dma
mdefine_line|#define sa1100_resume_dma(regs)&t;((regs)-&gt;SetDCSR = DCSR_IE|DCSR_RUN)
multiline_comment|/**&n; * &t;sa1100_clear_dma - clear DMA pointers&n; * &t;@regs: identifier for the channel to use&n; *&n; * &t;This clear any DMA state so the DMA engine is ready to restart&n; * &t;with new buffers through sa1100_start_dma(). Any buffers in flight&n; * &t;are discarded.&n; *&n; * &t;The @regs identifier is provided by a successful call to&n; * &t;sa1100_request_dma().&n; **/
DECL|macro|sa1100_clear_dma
mdefine_line|#define sa1100_clear_dma(regs)&t;((regs)-&gt;ClrDCSR = DCSR_IE|DCSR_RUN|DCSR_STRTA|DCSR_STRTB)
macro_line|#ifdef CONFIG_SA1111
r_static
r_inline
r_void
DECL|function|__arch_adjust_zones
id|__arch_adjust_zones
c_func
(paren
r_int
id|node
comma
r_int
r_int
op_star
id|size
comma
r_int
r_int
op_star
id|holes
)paren
(brace
r_int
r_int
id|sz
op_assign
l_int|256
suffix:semicolon
r_if
c_cond
(paren
id|node
op_ne
l_int|0
)paren
id|sz
op_assign
l_int|0
suffix:semicolon
id|size
(braket
l_int|1
)braket
op_assign
id|size
(braket
l_int|0
)braket
op_minus
id|sz
suffix:semicolon
id|size
(braket
l_int|0
)braket
op_assign
id|sz
suffix:semicolon
)brace
DECL|macro|arch_adjust_zones
mdefine_line|#define arch_adjust_zones(node,size,holes) __arch_adjust_zones(node,size,holes)
macro_line|#endif
macro_line|#endif /* _ASM_ARCH_DMA_H */
eof
