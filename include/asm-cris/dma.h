multiline_comment|/* $Id: dma.h,v 1.2 2001/05/09 12:17:42 johana Exp $&n; * linux/include/asm/dma.h: Defines for using and allocating dma channels.&n; */
macro_line|#ifndef _ASM_DMA_H
DECL|macro|_ASM_DMA_H
mdefine_line|#define _ASM_DMA_H
multiline_comment|/* it&squot;s useless on the Etrax, but unfortunately needed by the new&n;   bootmem allocator (but this should do it for this) */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS PAGE_OFFSET
multiline_comment|/* TODO: check nbr of channels on Etrax-100LX */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;10
multiline_comment|/* dma0 and dma1 used for network (ethernet) */
DECL|macro|NETWORK_TX_DMA_NBR
mdefine_line|#define NETWORK_TX_DMA_NBR 0
DECL|macro|NETWORK_RX_DMA_NBR
mdefine_line|#define NETWORK_RX_DMA_NBR 1
multiline_comment|/* dma2 and dma3 shared by par0, scsi0, ser2 and ata */
DECL|macro|PAR0_TX_DMA_NBR
mdefine_line|#define PAR0_TX_DMA_NBR 2
DECL|macro|PAR0_RX_DMA_NBR
mdefine_line|#define PAR0_RX_DMA_NBR 3
DECL|macro|SCSI0_TX_DMA_NBR
mdefine_line|#define SCSI0_TX_DMA_NBR 2
DECL|macro|SCSI0_RX_DMA_NBR
mdefine_line|#define SCSI0_RX_DMA_NBR 3
DECL|macro|SER2_TX_DMA_NBR
mdefine_line|#define SER2_TX_DMA_NBR 2
DECL|macro|SER2_RX_DMA_NBR
mdefine_line|#define SER2_RX_DMA_NBR 3
DECL|macro|ATA_TX_DMA_NBR
mdefine_line|#define ATA_TX_DMA_NBR 2
DECL|macro|ATA_RX_DMA_NBR
mdefine_line|#define ATA_RX_DMA_NBR 3
multiline_comment|/* dma4 and dma5 shared by par1, scsi1, ser3 and extdma0 */
DECL|macro|PAR1_TX_DMA_NBR
mdefine_line|#define PAR1_TX_DMA_NBR 4
DECL|macro|PAR1_RX_DMA_NBR
mdefine_line|#define PAR1_RX_DMA_NBR 5
DECL|macro|SCSI1_TX_DMA_NBR
mdefine_line|#define SCSI1_TX_DMA_NBR 4
DECL|macro|SCSI1_RX_DMA_NBR
mdefine_line|#define SCSI1_RX_DMA_NBR 5
DECL|macro|SER3_TX_DMA_NBR
mdefine_line|#define SER3_TX_DMA_NBR 4
DECL|macro|SER3_RX_DMA_NBR
mdefine_line|#define SER3_RX_DMA_NBR 5
DECL|macro|EXTDMA0_TX_DMA_NBR
mdefine_line|#define EXTDMA0_TX_DMA_NBR 4
DECL|macro|EXTDMA0_RX_DMA_NBR
mdefine_line|#define EXTDMA0_RX_DMA_NBR 5
multiline_comment|/* dma6 and dma7 shared by ser0, extdma1 and mem2mem */
DECL|macro|SER0_TX_DMA_NBR
mdefine_line|#define SER0_TX_DMA_NBR 6
DECL|macro|SER0_RX_DMA_NBR
mdefine_line|#define SER0_RX_DMA_NBR 7
DECL|macro|EXTDMA1_TX_DMA_NBR
mdefine_line|#define EXTDMA1_TX_DMA_NBR 6
DECL|macro|EXTDMA1_RX_DMA_NBR
mdefine_line|#define EXTDMA1_RX_DMA_NBR 7
DECL|macro|MEM2MEM_TX_DMA_NBR
mdefine_line|#define MEM2MEM_TX_DMA_NBR 6
DECL|macro|MEM2MEM_RX_DMA_NBR
mdefine_line|#define MEM2MEM_RX_DMA_NBR 7
multiline_comment|/* dma8 and dma9 shared by ser1 and usb */
DECL|macro|SER1_TX_DMA_NBR
mdefine_line|#define SER1_TX_DMA_NBR 8
DECL|macro|SER1_RX_DMA_NBR
mdefine_line|#define SER1_RX_DMA_NBR 9
DECL|macro|USB_TX_DMA_NBR
mdefine_line|#define USB_TX_DMA_NBR 8
DECL|macro|USB_RX_DMA_NBR
mdefine_line|#define USB_RX_DMA_NBR 9
multiline_comment|/* These are in kernel/dma.c: */
r_extern
r_int
id|request_dma
c_func
(paren
r_int
r_int
id|dmanr
comma
r_const
r_char
op_star
id|device_id
)paren
suffix:semicolon
multiline_comment|/* reserve a DMA channel */
r_extern
r_void
id|free_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
multiline_comment|/* release it */
macro_line|#endif /* _ASM_DMA_H */
eof
