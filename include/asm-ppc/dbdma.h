multiline_comment|/*&n; * Definitions for using the Apple Descriptor-Based DMA controller&n; * in Power Macintosh computers.&n; *&n; * Copyright (C) 1996 Paul Mackerras.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _ASM_DBDMA_H_
DECL|macro|_ASM_DBDMA_H_
mdefine_line|#define _ASM_DBDMA_H_
multiline_comment|/*&n; * DBDMA control/status registers.  All little-endian.&n; */
DECL|struct|dbdma_regs
r_struct
id|dbdma_regs
(brace
DECL|member|control
r_int
r_int
id|control
suffix:semicolon
multiline_comment|/* lets you change bits in status */
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/* DMA and device status bits (see below) */
DECL|member|cmdptr_hi
r_int
r_int
id|cmdptr_hi
suffix:semicolon
multiline_comment|/* upper 32 bits of command address */
DECL|member|cmdptr
r_int
r_int
id|cmdptr
suffix:semicolon
multiline_comment|/* (lower 32 bits of) command address (phys) */
DECL|member|intr_sel
r_int
r_int
id|intr_sel
suffix:semicolon
multiline_comment|/* select interrupt condition bit */
DECL|member|br_sel
r_int
r_int
id|br_sel
suffix:semicolon
multiline_comment|/* select branch condition bit */
DECL|member|wait_sel
r_int
r_int
id|wait_sel
suffix:semicolon
multiline_comment|/* select wait condition bit */
DECL|member|xfer_mode
r_int
r_int
id|xfer_mode
suffix:semicolon
DECL|member|data2ptr_hi
r_int
r_int
id|data2ptr_hi
suffix:semicolon
DECL|member|data2ptr
r_int
r_int
id|data2ptr
suffix:semicolon
DECL|member|res1
r_int
r_int
id|res1
suffix:semicolon
DECL|member|address_hi
r_int
r_int
id|address_hi
suffix:semicolon
DECL|member|br_addr_hi
r_int
r_int
id|br_addr_hi
suffix:semicolon
DECL|member|res2
r_int
r_int
id|res2
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Bits in control and status registers */
DECL|macro|RUN
mdefine_line|#define RUN&t;0x8000
DECL|macro|PAUSE
mdefine_line|#define PAUSE&t;0x4000
DECL|macro|FLUSH
mdefine_line|#define FLUSH&t;0x2000
DECL|macro|WAKE
mdefine_line|#define WAKE&t;0x1000
DECL|macro|DEAD
mdefine_line|#define DEAD&t;0x0800
DECL|macro|ACTIVE
mdefine_line|#define ACTIVE&t;0x0400
DECL|macro|BT
mdefine_line|#define BT&t;0x0100
DECL|macro|DEVSTAT
mdefine_line|#define DEVSTAT&t;0x00ff
multiline_comment|/*&n; * DBDMA command structure.  These fields are all little-endian!&n; */
DECL|struct|dbdma_cmd
r_struct
id|dbdma_cmd
(brace
DECL|member|req_count
r_int
r_int
id|req_count
suffix:semicolon
multiline_comment|/* requested byte transfer count */
DECL|member|command
r_int
r_int
id|command
suffix:semicolon
multiline_comment|/* command word (has bit-fields) */
DECL|member|phy_addr
r_int
r_int
id|phy_addr
suffix:semicolon
multiline_comment|/* physical data address */
DECL|member|cmd_dep
r_int
r_int
id|cmd_dep
suffix:semicolon
multiline_comment|/* command-dependent field */
DECL|member|res_count
r_int
r_int
id|res_count
suffix:semicolon
multiline_comment|/* residual count after completion */
DECL|member|xfer_status
r_int
r_int
id|xfer_status
suffix:semicolon
multiline_comment|/* transfer status */
)brace
suffix:semicolon
multiline_comment|/* DBDMA command values in command field */
DECL|macro|OUTPUT_MORE
mdefine_line|#define OUTPUT_MORE&t;0&t;/* transfer memory data to stream */
DECL|macro|OUTPUT_LAST
mdefine_line|#define OUTPUT_LAST&t;0x1000&t;/* ditto followed by end marker */
DECL|macro|INPUT_MORE
mdefine_line|#define INPUT_MORE&t;0x2000&t;/* transfer stream data to memory */
DECL|macro|INPUT_LAST
mdefine_line|#define INPUT_LAST&t;0x3000&t;/* ditto, expect end marker */
DECL|macro|STORE_WORD
mdefine_line|#define STORE_WORD&t;0x4000&t;/* write word (4 bytes) to device reg */
DECL|macro|LOAD_WORD
mdefine_line|#define LOAD_WORD&t;0x5000&t;/* read word (4 bytes) from device reg */
DECL|macro|DBDMA_NOP
mdefine_line|#define DBDMA_NOP&t;0x6000&t;/* do nothing */
DECL|macro|DBDMA_STOP
mdefine_line|#define DBDMA_STOP&t;0x7000&t;/* suspend processing */
multiline_comment|/* Key values in command field */
DECL|macro|KEY_STREAM0
mdefine_line|#define KEY_STREAM0&t;0&t;/* usual data stream */
DECL|macro|KEY_STREAM1
mdefine_line|#define KEY_STREAM1&t;0x100&t;/* control/status stream */
DECL|macro|KEY_STREAM2
mdefine_line|#define KEY_STREAM2&t;0x200&t;/* device-dependent stream */
DECL|macro|KEY_STREAM3
mdefine_line|#define KEY_STREAM3&t;0x300&t;/* device-dependent stream */
DECL|macro|KEY_REGS
mdefine_line|#define KEY_REGS&t;0x500&t;/* device register space */
DECL|macro|KEY_SYSTEM
mdefine_line|#define KEY_SYSTEM&t;0x600&t;/* system memory-mapped space */
DECL|macro|KEY_DEVICE
mdefine_line|#define KEY_DEVICE&t;0x700&t;/* device memory-mapped space */
multiline_comment|/* Interrupt control values in command field */
DECL|macro|INTR_NEVER
mdefine_line|#define INTR_NEVER&t;0&t;/* don&squot;t interrupt */
DECL|macro|INTR_IFSET
mdefine_line|#define INTR_IFSET&t;0x10&t;/* intr if condition bit is 1 */
DECL|macro|INTR_IFCLR
mdefine_line|#define INTR_IFCLR&t;0x20&t;/* intr if condition bit is 0 */
DECL|macro|INTR_ALWAYS
mdefine_line|#define INTR_ALWAYS&t;0x30&t;/* always interrupt */
multiline_comment|/* Branch control values in command field */
DECL|macro|BR_NEVER
mdefine_line|#define BR_NEVER&t;0&t;/* don&squot;t branch */
DECL|macro|BR_IFSET
mdefine_line|#define BR_IFSET&t;0x4&t;/* branch if condition bit is 1 */
DECL|macro|BR_IFCLR
mdefine_line|#define BR_IFCLR&t;0x8&t;/* branch if condition bit is 0 */
DECL|macro|BR_ALWAYS
mdefine_line|#define BR_ALWAYS&t;0xc&t;/* always branch */
multiline_comment|/* Wait control values in command field */
DECL|macro|WAIT_NEVER
mdefine_line|#define WAIT_NEVER&t;0&t;/* don&squot;t wait */
DECL|macro|WAIT_IFSET
mdefine_line|#define WAIT_IFSET&t;1&t;/* wait if condition bit is 1 */
DECL|macro|WAIT_IFCLR
mdefine_line|#define WAIT_IFCLR&t;2&t;/* wait if condition bit is 0 */
DECL|macro|WAIT_ALWAYS
mdefine_line|#define WAIT_ALWAYS&t;3&t;/* always wait */
multiline_comment|/* Align an address for a DBDMA command structure */
DECL|macro|DBDMA_ALIGN
mdefine_line|#define DBDMA_ALIGN(x)&t;(((unsigned)(x) + sizeof(struct dbdma_cmd) - 1) &bslash;&n;&t;&t;&t; &amp; -sizeof(struct dbdma_cmd))
macro_line|#endif /* _ASM_DBDMA_H_ */
macro_line|#endif /* __KERNEL__ */
eof
