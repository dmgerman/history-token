multiline_comment|/* $Id: iflash.h,v 1.2 2000/11/13 18:01:54 dwmw2 Exp $ */
macro_line|#ifndef __MTD_IFLASH_H__
DECL|macro|__MTD_IFLASH_H__
mdefine_line|#define __MTD_IFLASH_H__
multiline_comment|/* Extended CIS registers for Series 2 and 2+ cards */
multiline_comment|/* The registers are all offsets from 0x4000 */
DECL|macro|CISREG_CSR
mdefine_line|#define CISREG_CSR&t;&t;0x0100
DECL|macro|CISREG_WP
mdefine_line|#define CISREG_WP&t;&t;0x0104
DECL|macro|CISREG_RDYBSY
mdefine_line|#define CISREG_RDYBSY&t;&t;0x0140
multiline_comment|/* Extended CIS registers for Series 2 cards */
DECL|macro|CISREG_SLEEP
mdefine_line|#define CISREG_SLEEP&t;&t;0x0118
DECL|macro|CISREG_RDY_MASK
mdefine_line|#define CISREG_RDY_MASK&t;&t;0x0120
DECL|macro|CISREG_RDY_STATUS
mdefine_line|#define CISREG_RDY_STATUS&t;0x0130
multiline_comment|/* Extended CIS registers for Series 2+ cards */
DECL|macro|CISREG_VCR
mdefine_line|#define CISREG_VCR&t;&t;0x010c
multiline_comment|/* Card Status Register */
DECL|macro|CSR_SRESET
mdefine_line|#define CSR_SRESET&t;&t;0x20&t;/* Soft reset */
DECL|macro|CSR_CMWP
mdefine_line|#define CSR_CMWP&t;&t;0x10&t;/* Common memory write protect */
DECL|macro|CSR_PWRDOWN
mdefine_line|#define CSR_PWRDOWN&t;&t;0x08&t;/* Power down status */
DECL|macro|CSR_CISWP
mdefine_line|#define CSR_CISWP&t;&t;0x04&t;/* Common memory CIS WP */
DECL|macro|CSR_WP
mdefine_line|#define CSR_WP&t;&t;&t;0x02&t;/* Mechanical write protect */
DECL|macro|CSR_READY
mdefine_line|#define CSR_READY&t;&t;0x01&t;/* Ready/busy status */
multiline_comment|/* Write Protection Register */
DECL|macro|WP_BLKEN
mdefine_line|#define WP_BLKEN&t;&t;0x04&t;/* Enable block locking */
DECL|macro|WP_CMWP
mdefine_line|#define WP_CMWP&t;&t;&t;0x02&t;/* Common memory write protect */
DECL|macro|WP_CISWP
mdefine_line|#define WP_CISWP&t;&t;0x01&t;/* Common memory CIS WP */
multiline_comment|/* Voltage Control Register */
DECL|macro|VCR_VCC_LEVEL
mdefine_line|#define VCR_VCC_LEVEL&t;&t;0x80&t;/* 0 = 5V, 1 = 3.3V */
DECL|macro|VCR_VPP_VALID
mdefine_line|#define VCR_VPP_VALID&t;&t;0x02&t;/* Vpp Valid */
DECL|macro|VCR_VPP_GEN
mdefine_line|#define VCR_VPP_GEN&t;&t;0x01&t;/* Integrated Vpp generator */
multiline_comment|/* Ready/Busy Mode Register */
DECL|macro|RDYBSY_RACK
mdefine_line|#define RDYBSY_RACK&t;&t;0x02&t;/* Ready acknowledge */
DECL|macro|RDYBSY_MODE
mdefine_line|#define RDYBSY_MODE&t;&t;0x01&t;/* 1 = high performance */
DECL|macro|LOW
mdefine_line|#define LOW(x) ((x) &amp; 0xff)
multiline_comment|/* 28F008SA-Compatible Command Set */
DECL|macro|IF_READ_ARRAY
mdefine_line|#define IF_READ_ARRAY&t;&t;0xffff
DECL|macro|IF_INTEL_ID
mdefine_line|#define IF_INTEL_ID&t;&t;0x9090
DECL|macro|IF_READ_CSR
mdefine_line|#define IF_READ_CSR&t;&t;0x7070
DECL|macro|IF_CLEAR_CSR
mdefine_line|#define IF_CLEAR_CSR&t;&t;0x5050
DECL|macro|IF_WRITE
mdefine_line|#define IF_WRITE&t;&t;0x4040
DECL|macro|IF_BLOCK_ERASE
mdefine_line|#define IF_BLOCK_ERASE&t;&t;0x2020
DECL|macro|IF_ERASE_SUSPEND
mdefine_line|#define IF_ERASE_SUSPEND&t;0xb0b0
DECL|macro|IF_CONFIRM
mdefine_line|#define IF_CONFIRM&t;&t;0xd0d0
multiline_comment|/* 28F016SA Performance Enhancement Commands */
DECL|macro|IF_READ_PAGE
mdefine_line|#define IF_READ_PAGE&t;&t;0x7575
DECL|macro|IF_PAGE_SWAP
mdefine_line|#define IF_PAGE_SWAP&t;&t;0x7272
DECL|macro|IF_SINGLE_LOAD
mdefine_line|#define IF_SINGLE_LOAD&t;&t;0x7474
DECL|macro|IF_SEQ_LOAD
mdefine_line|#define IF_SEQ_LOAD&t;&t;0xe0e0
DECL|macro|IF_PAGE_WRITE
mdefine_line|#define IF_PAGE_WRITE&t;&t;0x0c0c
DECL|macro|IF_RDY_MODE
mdefine_line|#define IF_RDY_MODE&t;&t;0x9696
DECL|macro|IF_RDY_LEVEL
mdefine_line|#define IF_RDY_LEVEL&t;&t;0x0101
DECL|macro|IF_RDY_PULSE_WRITE
mdefine_line|#define IF_RDY_PULSE_WRITE&t;0x0202
DECL|macro|IF_RDY_PULSE_ERASE
mdefine_line|#define IF_RDY_PULSE_ERASE&t;0x0303
DECL|macro|IF_RDY_DISABLE
mdefine_line|#define IF_RDY_DISABLE&t;&t;0x0404
DECL|macro|IF_LOCK_BLOCK
mdefine_line|#define IF_LOCK_BLOCK&t;&t;0x7777
DECL|macro|IF_UPLOAD_STATUS
mdefine_line|#define IF_UPLOAD_STATUS&t;0x9797
DECL|macro|IF_READ_ESR
mdefine_line|#define IF_READ_ESR&t;&t;0x7171
DECL|macro|IF_ERASE_UNLOCKED
mdefine_line|#define IF_ERASE_UNLOCKED&t;0xa7a7
DECL|macro|IF_SLEEP
mdefine_line|#define IF_SLEEP&t;&t;0xf0f0
DECL|macro|IF_ABORT
mdefine_line|#define IF_ABORT&t;&t;0x8080
DECL|macro|IF_UPLOAD_DEVINFO
mdefine_line|#define IF_UPLOAD_DEVINFO&t;0x9999
multiline_comment|/* Definitions for Compatible Status Register */
DECL|macro|CSR_WR_READY
mdefine_line|#define CSR_WR_READY&t;&t;0x8080&t;/* Write state machine status */
DECL|macro|CSR_ERA_SUSPEND
mdefine_line|#define CSR_ERA_SUSPEND&t;&t;0x4040&t;/* Erase suspend status */
DECL|macro|CSR_ERA_ERR
mdefine_line|#define CSR_ERA_ERR&t;&t;0x2020&t;/* Erase status */
DECL|macro|CSR_WR_ERR
mdefine_line|#define CSR_WR_ERR&t;&t;0x1010&t;/* Data write status */
DECL|macro|CSR_VPP_LOW
mdefine_line|#define CSR_VPP_LOW&t;&t;0x0808&t;/* Vpp status */
multiline_comment|/* Definitions for Global Status Register */
DECL|macro|GSR_WR_READY
mdefine_line|#define GSR_WR_READY&t;&t;0x8080&t;/* Write state machine status */
DECL|macro|GSR_OP_SUSPEND
mdefine_line|#define GSR_OP_SUSPEND&t;&t;0x4040&t;/* Operation suspend status */
DECL|macro|GSR_OP_ERR
mdefine_line|#define GSR_OP_ERR&t;&t;0x2020&t;/* Device operation status */
DECL|macro|GSR_SLEEP
mdefine_line|#define GSR_SLEEP&t;&t;0x1010&t;/* Device sleep status */
DECL|macro|GSR_QUEUE_FULL
mdefine_line|#define GSR_QUEUE_FULL&t;&t;0x0808&t;/* Queue status */
DECL|macro|GSR_PAGE_AVAIL
mdefine_line|#define GSR_PAGE_AVAIL&t;&t;0x0404&t;/* Page buffer available status */
DECL|macro|GSR_PAGE_READY
mdefine_line|#define GSR_PAGE_READY&t;&t;0x0202&t;/* Page buffer status */
DECL|macro|GSR_PAGE_SELECT
mdefine_line|#define GSR_PAGE_SELECT&t;&t;0x0101&t;/* Page buffer select status */
multiline_comment|/* Definitions for Block Status Register */
DECL|macro|BSR_READY
mdefine_line|#define BSR_READY&t;&t;0x8080&t;/* Block status */
DECL|macro|BSR_UNLOCK
mdefine_line|#define BSR_UNLOCK&t;&t;0x4040&t;/* Block lock status */
DECL|macro|BSR_FAILED
mdefine_line|#define BSR_FAILED&t;&t;0x2020&t;/* Block operation status */
DECL|macro|BSR_ABORTED
mdefine_line|#define BSR_ABORTED&t;&t;0x1010&t;/* Operation abort status */
DECL|macro|BSR_QUEUE_FULL
mdefine_line|#define BSR_QUEUE_FULL&t;&t;0x0808&t;/* Queue status */
DECL|macro|BSR_VPP_LOW
mdefine_line|#define BSR_VPP_LOW&t;&t;0x0404&t;/* Vpp status */
macro_line|#endif /* __MTD_IFLASH_H__ */
eof
