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
mdefine_line|#define SA1100_DMA_CHANNELS     6
multiline_comment|/*&n; * The SA-1111 SAC has two DMA channels.&n; */
DECL|macro|SA1111_SAC_DMA_CHANNELS
mdefine_line|#define SA1111_SAC_DMA_CHANNELS 2
DECL|macro|SA1111_SAC_XMT_CHANNEL
mdefine_line|#define SA1111_SAC_XMT_CHANNEL  0
DECL|macro|SA1111_SAC_RCV_CHANNEL
mdefine_line|#define SA1111_SAC_RCV_CHANNEL  1
multiline_comment|/*&n; * The SA-1111 SAC channels will reside in the same index space as&n; * the built-in SA-1100 channels, and will take on the next available&n; * identifiers after the 1100.&n; */
DECL|macro|SA1111_SAC_DMA_BASE
mdefine_line|#define SA1111_SAC_DMA_BASE     SA1100_DMA_CHANNELS
macro_line|#ifdef CONFIG_SA1111
DECL|macro|MAX_SA1100_DMA_CHANNELS
macro_line|# define MAX_SA1100_DMA_CHANNELS (SA1100_DMA_CHANNELS + SA1111_SAC_DMA_CHANNELS)
macro_line|#else
DECL|macro|MAX_SA1100_DMA_CHANNELS
macro_line|# define MAX_SA1100_DMA_CHANNELS SA1100_DMA_CHANNELS
macro_line|#endif
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
id|buf_id
comma
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* SA1100 DMA API */
r_extern
r_int
id|sa1100_request_dma
c_func
(paren
id|dmach_t
op_star
id|channel
comma
r_const
r_char
op_star
id|device_id
)paren
suffix:semicolon
r_extern
r_int
id|sa1100_dma_set_callback
c_func
(paren
id|dmach_t
id|channel
comma
id|dma_callback_t
id|cb
)paren
suffix:semicolon
r_extern
r_int
id|sa1100_dma_set_device
c_func
(paren
id|dmach_t
id|channel
comma
id|dma_device_t
id|device
)paren
suffix:semicolon
r_extern
r_int
id|sa1100_dma_set_spin
c_func
(paren
id|dmach_t
id|channel
comma
id|dma_addr_t
id|addr
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|sa1100_dma_queue_buffer
c_func
(paren
id|dmach_t
id|channel
comma
r_void
op_star
id|buf_id
comma
id|dma_addr_t
id|data
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|sa1100_dma_get_current
c_func
(paren
id|dmach_t
id|channel
comma
r_void
op_star
op_star
id|buf_id
comma
id|dma_addr_t
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|sa1100_dma_stop
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
r_extern
r_int
id|sa1100_dma_resume
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
r_extern
r_int
id|sa1100_dma_flush_all
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
r_extern
r_void
id|sa1100_free_dma
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
multiline_comment|/* Sa1111 DMA interface (all but registration uses the above) */
r_extern
r_int
id|sa1111_sac_request_dma
c_func
(paren
id|dmach_t
op_star
id|channel
comma
r_const
r_char
op_star
id|device_id
comma
r_int
r_int
id|direction
)paren
suffix:semicolon
r_extern
r_int
id|sa1111_check_dma_bug
c_func
(paren
id|dma_addr_t
id|addr
)paren
suffix:semicolon
macro_line|#endif /* _ASM_ARCH_DMA_H */
eof
