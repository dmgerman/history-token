multiline_comment|/* $Id: dbri.h,v 1.13 2000/10/13 00:34:24 uzi Exp $&n; * drivers/sbus/audio/cs4231.h&n; *&n; * Copyright (C) 1997 Rudolf Koenig (rfkoenig@immd4.informatik.uni-erlangen.de)&n; */
macro_line|#ifndef _DBRI_H_
DECL|macro|_DBRI_H_
mdefine_line|#define _DBRI_H_
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* DBRI main registers */
DECL|macro|REG0
mdefine_line|#define REG0&t;0x00UL&t;&t;/* Status and Control */
DECL|macro|REG1
mdefine_line|#define REG1&t;0x04UL&t;&t;/* Mode and Interrupt */
DECL|macro|REG2
mdefine_line|#define REG2&t;0x08UL&t;&t;/* Parallel IO */
DECL|macro|REG3
mdefine_line|#define REG3&t;0x0cUL&t;&t;/* Test */
DECL|macro|REG8
mdefine_line|#define REG8&t;0x20UL&t;&t;/* Command Queue Pointer */
DECL|macro|REG9
mdefine_line|#define REG9&t;0x24UL&t;&t;/* Interrupt Queue Pointer */
DECL|macro|DBRI_NO_CMDS
mdefine_line|#define DBRI_NO_CMDS&t;64
DECL|macro|DBRI_NO_INTS
mdefine_line|#define DBRI_NO_INTS&t;1&t;/* Note: the value of this define was&n;&t;&t;&t;&t; * originally 2.  The ringbuffer to store&n;&t;&t;&t;&t; * interrupts in dma is currently broken.&n;&t;&t;&t;&t; * This is a temporary fix until the ringbuffer&n;&t;&t;&t;&t; * is fixed.&n;&t;&t;&t;&t; */
DECL|macro|DBRI_INT_BLK
mdefine_line|#define DBRI_INT_BLK&t;64
DECL|macro|DBRI_NO_DESCS
mdefine_line|#define DBRI_NO_DESCS&t;64
DECL|macro|DBRI_MM_ONB
mdefine_line|#define DBRI_MM_ONB&t;1
DECL|macro|DBRI_MM_SB
mdefine_line|#define DBRI_MM_SB&t;2
DECL|struct|dbri_mem
r_struct
id|dbri_mem
(brace
DECL|member|word1
r_volatile
id|__u32
id|word1
suffix:semicolon
DECL|member|ba
r_volatile
id|__u32
id|ba
suffix:semicolon
multiline_comment|/* Transmit/Receive Buffer Address */
DECL|member|nda
r_volatile
id|__u32
id|nda
suffix:semicolon
multiline_comment|/* Next Descriptor Address */
DECL|member|word4
r_volatile
id|__u32
id|word4
suffix:semicolon
)brace
suffix:semicolon
macro_line|#include &quot;cs4215.h&quot;
multiline_comment|/* This structure is in a DMA region where it can accessed by both&n; * the CPU and the DBRI&n; */
DECL|struct|dbri_dma
r_struct
id|dbri_dma
(brace
DECL|member|cmd
r_volatile
id|s32
id|cmd
(braket
id|DBRI_NO_CMDS
)braket
suffix:semicolon
multiline_comment|/* Place for commands */
DECL|member|intr
r_volatile
id|s32
id|intr
(braket
id|DBRI_NO_INTS
op_star
id|DBRI_INT_BLK
)braket
suffix:semicolon
multiline_comment|/* Interrupt field */
DECL|member|desc
r_struct
id|dbri_mem
id|desc
(braket
id|DBRI_NO_DESCS
)braket
suffix:semicolon
multiline_comment|/* Xmit/receive descriptors */
)brace
suffix:semicolon
DECL|macro|dbri_dma_off
mdefine_line|#define dbri_dma_off(member, elem)&t;&bslash;&n;&t;((u32)(unsigned long)&t;&t;&bslash;&n;&t; (&amp;(((struct dbri_dma *)0)-&gt;member[elem])))
DECL|enum|in_or_out
DECL|enumerator|PIPEinput
DECL|enumerator|PIPEoutput
r_enum
id|in_or_out
(brace
id|PIPEinput
comma
id|PIPEoutput
)brace
suffix:semicolon
DECL|enum|direction
DECL|enumerator|in
DECL|enumerator|out
r_enum
id|direction
(brace
id|in
comma
id|out
)brace
suffix:semicolon
DECL|struct|dbri_pipe
r_struct
id|dbri_pipe
(brace
DECL|member|sdp
id|u32
id|sdp
suffix:semicolon
multiline_comment|/* SDP command word */
DECL|member|direction
r_enum
id|direction
id|direction
suffix:semicolon
DECL|member|nextpipe
r_int
id|nextpipe
suffix:semicolon
multiline_comment|/* Next pipe in linked list */
DECL|member|prevpipe
r_int
id|prevpipe
suffix:semicolon
DECL|member|cycle
r_int
id|cycle
suffix:semicolon
multiline_comment|/* Offset of timeslot (bits) */
DECL|member|length
r_int
id|length
suffix:semicolon
multiline_comment|/* Length of timeslot (bits) */
DECL|member|desc
r_int
id|desc
suffix:semicolon
multiline_comment|/* Index of active descriptor*/
DECL|member|recv_fixed_ptr
r_volatile
id|__u32
op_star
id|recv_fixed_ptr
suffix:semicolon
multiline_comment|/* Ptr to receive fixed data */
)brace
suffix:semicolon
DECL|struct|dbri_desc
r_struct
id|dbri_desc
(brace
DECL|member|inuse
r_int
id|inuse
suffix:semicolon
multiline_comment|/* Boolean flag */
DECL|member|next
r_int
id|next
suffix:semicolon
multiline_comment|/* Index of next desc, or -1 */
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
multiline_comment|/* CPU view of buffer */
DECL|member|buffer_dvma
id|u32
id|buffer_dvma
suffix:semicolon
multiline_comment|/* Device view */
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|output_callback
r_void
(paren
op_star
id|output_callback
)paren
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|output_callback_arg
r_void
op_star
id|output_callback_arg
suffix:semicolon
DECL|member|input_callback
r_void
(paren
op_star
id|input_callback
)paren
(paren
r_void
op_star
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|input_callback_arg
r_void
op_star
id|input_callback_arg
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This structure holds the information for both chips (DBRI &amp; CS4215) */
DECL|struct|dbri
r_struct
id|dbri
(brace
DECL|member|regs_size
DECL|member|irq
r_int
id|regs_size
comma
id|irq
suffix:semicolon
multiline_comment|/* Needed for unload */
DECL|member|sdev
r_struct
id|sbus_dev
op_star
id|sdev
suffix:semicolon
multiline_comment|/* SBUS device info */
DECL|member|dma
r_volatile
r_struct
id|dbri_dma
op_star
id|dma
suffix:semicolon
multiline_comment|/* Pointer to our DMA block */
DECL|member|dma_dvma
id|u32
id|dma_dvma
suffix:semicolon
multiline_comment|/* DBRI visible DMA address */
DECL|member|regs
r_int
r_int
id|regs
suffix:semicolon
multiline_comment|/* dbri HW regs */
DECL|member|dbri_version
r_int
id|dbri_version
suffix:semicolon
multiline_comment|/* &squot;e&squot; and up is OK */
DECL|member|dbri_irqp
r_int
id|dbri_irqp
suffix:semicolon
multiline_comment|/* intr queue pointer */
DECL|member|wait_seen
r_int
id|wait_seen
suffix:semicolon
DECL|member|pipes
r_struct
id|dbri_pipe
id|pipes
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* DBRI&squot;s 32 data pipes */
DECL|member|descs
r_struct
id|dbri_desc
id|descs
(braket
id|DBRI_NO_DESCS
)braket
suffix:semicolon
DECL|member|chi_in_pipe
r_int
id|chi_in_pipe
suffix:semicolon
DECL|member|chi_out_pipe
r_int
id|chi_out_pipe
suffix:semicolon
DECL|member|chi_bpf
r_int
id|chi_bpf
suffix:semicolon
DECL|member|mm
r_struct
id|cs4215
id|mm
suffix:semicolon
multiline_comment|/* mmcodec special info */
macro_line|#if 0
multiline_comment|/* Where to sleep if busy */
id|wait_queue_head_t
id|wait
comma
id|int_wait
suffix:semicolon
macro_line|#endif
DECL|member|perchip_info
r_struct
id|audio_info
id|perchip_info
suffix:semicolon
multiline_comment|/* Track ISDN LIU and notify changes */
DECL|member|liu_state
r_int
id|liu_state
suffix:semicolon
DECL|member|liu_callback
r_void
(paren
op_star
id|liu_callback
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|liu_callback_arg
r_void
op_star
id|liu_callback_arg
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* DBRI Reg0 - Status Control Register - defines. (Page 17) */
DECL|macro|D_P
mdefine_line|#define D_P&t;&t;(1&lt;&lt;15)&t;/* Program command &amp; queue pointer valid */
DECL|macro|D_G
mdefine_line|#define D_G&t;&t;(1&lt;&lt;14)&t;/* Allow 4-Word SBus Burst */
DECL|macro|D_S
mdefine_line|#define D_S&t;&t;(1&lt;&lt;13)&t;/* Allow 16-Word SBus Burst */
DECL|macro|D_E
mdefine_line|#define D_E&t;&t;(1&lt;&lt;12)&t;/* Allow 8-Word SBus Burst */
DECL|macro|D_X
mdefine_line|#define D_X&t;&t;(1&lt;&lt;7)&t;/* Sanity Timer Disable */
DECL|macro|D_T
mdefine_line|#define D_T&t;&t;(1&lt;&lt;6)&t;/* Permit activation of the TE interface */
DECL|macro|D_N
mdefine_line|#define D_N&t;&t;(1&lt;&lt;5)&t;/* Permit activation of the NT interface */
DECL|macro|D_C
mdefine_line|#define D_C&t;&t;(1&lt;&lt;4)&t;/* Permit activation of the CHI interface */
DECL|macro|D_F
mdefine_line|#define D_F&t;&t;(1&lt;&lt;3)&t;/* Force Sanity Timer Time-Out */
DECL|macro|D_D
mdefine_line|#define D_D&t;&t;(1&lt;&lt;2)&t;/* Disable Master Mode */
DECL|macro|D_H
mdefine_line|#define D_H&t;&t;(1&lt;&lt;1)&t;/* Halt for Analysis */
DECL|macro|D_R
mdefine_line|#define D_R&t;&t;(1&lt;&lt;0)&t;/* Soft Reset */
multiline_comment|/* DBRI Reg1 - Mode and Interrupt Register - defines. (Page 18) */
DECL|macro|D_LITTLE_END
mdefine_line|#define D_LITTLE_END&t;(1&lt;&lt;8)&t;/* Byte Order */
DECL|macro|D_BIG_END
mdefine_line|#define D_BIG_END&t;(0&lt;&lt;8)&t;/* Byte Order */
DECL|macro|D_MRR
mdefine_line|#define D_MRR&t;&t;(1&lt;&lt;4)&t;/* Multiple Error Ack on SBus (readonly) */
DECL|macro|D_MLE
mdefine_line|#define D_MLE&t;&t;(1&lt;&lt;3)&t;/* Multiple Late Error on SBus (readonly) */
DECL|macro|D_LBG
mdefine_line|#define D_LBG&t;&t;(1&lt;&lt;2)&t;/* Lost Bus Grant on SBus (readonly) */
DECL|macro|D_MBE
mdefine_line|#define D_MBE&t;&t;(1&lt;&lt;1)&t;/* Burst Error on SBus (readonly) */
DECL|macro|D_IR
mdefine_line|#define D_IR&t;&t;(1&lt;&lt;0)&t;/* Interrupt Indicator (readonly) */
multiline_comment|/* DBRI Reg2 - Parallel IO Register - defines. (Page 18) */
DECL|macro|D_ENPIO3
mdefine_line|#define D_ENPIO3&t;(1&lt;&lt;7)&t;/* Enable Pin 3 */
DECL|macro|D_ENPIO2
mdefine_line|#define D_ENPIO2&t;(1&lt;&lt;6)&t;/* Enable Pin 2 */
DECL|macro|D_ENPIO1
mdefine_line|#define D_ENPIO1&t;(1&lt;&lt;5)&t;/* Enable Pin 1 */
DECL|macro|D_ENPIO0
mdefine_line|#define D_ENPIO0&t;(1&lt;&lt;4)&t;/* Enable Pin 0 */
DECL|macro|D_ENPIO
mdefine_line|#define D_ENPIO&t;&t;(0xf0)&t;/* Enable all the pins */
DECL|macro|D_PIO3
mdefine_line|#define D_PIO3&t;&t;(1&lt;&lt;3)&t;/* Pin 3: 1: Data mode, 0: Ctrl mode */
DECL|macro|D_PIO2
mdefine_line|#define D_PIO2&t;&t;(1&lt;&lt;2)&t;/* Pin 2: 1: Onboard PDN */
DECL|macro|D_PIO1
mdefine_line|#define D_PIO1&t;&t;(1&lt;&lt;1)&t;/* Pin 1: 0: Reset */
DECL|macro|D_PIO0
mdefine_line|#define D_PIO0&t;&t;(1&lt;&lt;0)&t;/* Pin 0: 1: Speakerbox PDN */
multiline_comment|/* DBRI Commands (Page 20) */
DECL|macro|D_WAIT
mdefine_line|#define D_WAIT&t;&t;0x0&t;/* Stop execution */
DECL|macro|D_PAUSE
mdefine_line|#define D_PAUSE&t;&t;0x1&t;/* Flush long pipes */
DECL|macro|D_JUMP
mdefine_line|#define D_JUMP&t;&t;0x2&t;/* New command queue */
DECL|macro|D_IIQ
mdefine_line|#define D_IIQ&t;&t;0x3&t;/* Initialize Interrupt Queue */
DECL|macro|D_REX
mdefine_line|#define D_REX&t;&t;0x4&t;/* Report command execution via interrupt */
DECL|macro|D_SDP
mdefine_line|#define D_SDP&t;&t;0x5&t;/* Setup Data Pipe */
DECL|macro|D_CDP
mdefine_line|#define D_CDP&t;&t;0x6&t;/* Continue Data Pipe (reread NULL Pointer) */
DECL|macro|D_DTS
mdefine_line|#define D_DTS&t;&t;0x7&t;/* Define Time Slot */
DECL|macro|D_SSP
mdefine_line|#define D_SSP&t;&t;0x8&t;/* Set short Data Pipe */
DECL|macro|D_CHI
mdefine_line|#define D_CHI&t;&t;0x9&t;/* Set CHI Global Mode */
DECL|macro|D_NT
mdefine_line|#define D_NT&t;&t;0xa&t;/* NT Command */
DECL|macro|D_TE
mdefine_line|#define D_TE&t;&t;0xb&t;/* TE Command */
DECL|macro|D_CDEC
mdefine_line|#define D_CDEC&t;&t;0xc&t;/* Codec setup */
DECL|macro|D_TEST
mdefine_line|#define D_TEST&t;&t;0xd&t;/* No comment */
DECL|macro|D_CDM
mdefine_line|#define D_CDM&t;&t;0xe&t;/* CHI Data mode command */
multiline_comment|/* Special bits for some commands */
DECL|macro|D_PIPE
mdefine_line|#define D_PIPE(v)      ((v)&lt;&lt;0)        /* Pipe Nr: 0-15 long, 16-21 short */
multiline_comment|/* Setup Data Pipe */
multiline_comment|/* IRM */
DECL|macro|D_SDP_2SAME
mdefine_line|#define D_SDP_2SAME&t;(1&lt;&lt;18) /* Report 2nd time in a row value rcvd*/
DECL|macro|D_SDP_CHANGE
mdefine_line|#define D_SDP_CHANGE&t;(2&lt;&lt;18) /* Report any changes */
DECL|macro|D_SDP_EVERY
mdefine_line|#define D_SDP_EVERY&t;(3&lt;&lt;18) /* Report any changes */
DECL|macro|D_SDP_EOL
mdefine_line|#define D_SDP_EOL&t;(1&lt;&lt;17) /* EOL interrupt enable */
DECL|macro|D_SDP_IDLE
mdefine_line|#define D_SDP_IDLE&t;(1&lt;&lt;16) /* HDLC idle interrupt enable */
multiline_comment|/* Pipe data MODE */
DECL|macro|D_SDP_MEM
mdefine_line|#define D_SDP_MEM&t;(0&lt;&lt;13)&t;/* To/from memory */
DECL|macro|D_SDP_HDLC
mdefine_line|#define D_SDP_HDLC&t;(2&lt;&lt;13)
DECL|macro|D_SDP_HDLC_D
mdefine_line|#define D_SDP_HDLC_D&t;(3&lt;&lt;13)&t;/* D Channel (prio control)*/
DECL|macro|D_SDP_SER
mdefine_line|#define D_SDP_SER&t;(4&lt;&lt;13)&t;/* Serial to serial */
DECL|macro|D_SDP_FIXED
mdefine_line|#define D_SDP_FIXED&t;(6&lt;&lt;13)&t;/* Short only */
DECL|macro|D_SDP_MODE
mdefine_line|#define D_SDP_MODE(v)&t;((v)&amp;(7&lt;&lt;13))
DECL|macro|D_SDP_TO_SER
mdefine_line|#define D_SDP_TO_SER&t;(1&lt;&lt;12)&t;/* Direction */
DECL|macro|D_SDP_FROM_SER
mdefine_line|#define D_SDP_FROM_SER&t;(0&lt;&lt;12)&t;/* Direction */
DECL|macro|D_SDP_MSB
mdefine_line|#define D_SDP_MSB&t;(1&lt;&lt;11)&t;/* Bit order within Byte */
DECL|macro|D_SDP_LSB
mdefine_line|#define D_SDP_LSB&t;(0&lt;&lt;11)&t;/* Bit order within Byte */
DECL|macro|D_SDP_P
mdefine_line|#define D_SDP_P&t;&t;(1&lt;&lt;10)&t;/* Pointer Valid */
DECL|macro|D_SDP_A
mdefine_line|#define D_SDP_A&t;&t;(1&lt;&lt;8)&t;/* Abort */
DECL|macro|D_SDP_C
mdefine_line|#define D_SDP_C&t;&t;(1&lt;&lt;7)&t;/* Clear */
multiline_comment|/* Define Time Slot */
DECL|macro|D_DTS_VI
mdefine_line|#define D_DTS_VI&t;(1&lt;&lt;17) /* Valid Input Time-Slot Descriptor */
DECL|macro|D_DTS_VO
mdefine_line|#define D_DTS_VO&t;(1&lt;&lt;16) /* Valid Output Time-Slot Descriptor */
DECL|macro|D_DTS_INS
mdefine_line|#define D_DTS_INS&t;(1&lt;&lt;15) /* Insert Time Slot */
DECL|macro|D_DTS_DEL
mdefine_line|#define D_DTS_DEL&t;(0&lt;&lt;15) /* Delete Time Slot */
DECL|macro|D_DTS_PRVIN
mdefine_line|#define D_DTS_PRVIN(v) ((v)&lt;&lt;10) /* Previous In Pipe */
DECL|macro|D_DTS_PRVOUT
mdefine_line|#define D_DTS_PRVOUT(v)        ((v)&lt;&lt;5)  /* Previous Out Pipe */
multiline_comment|/* Time Slot defines */
DECL|macro|D_TS_LEN
mdefine_line|#define D_TS_LEN(v)&t;((v)&lt;&lt;24)&t;/* Number of bits in this time slot */
DECL|macro|D_TS_CYCLE
mdefine_line|#define D_TS_CYCLE(v)&t;((v)&lt;&lt;14)&t;/* Bit Count at start of TS */
DECL|macro|D_TS_DI
mdefine_line|#define D_TS_DI&t;&t;(1&lt;&lt;13)&t;/* Data Invert */
DECL|macro|D_TS_1CHANNEL
mdefine_line|#define D_TS_1CHANNEL&t;(0&lt;&lt;10)&t;/* Single Channel / Normal mode */
DECL|macro|D_TS_MONITOR
mdefine_line|#define D_TS_MONITOR&t;(2&lt;&lt;10)&t;/* Monitor pipe */
DECL|macro|D_TS_NONCONTIG
mdefine_line|#define D_TS_NONCONTIG&t;(3&lt;&lt;10) /* Non contiguous mode */
DECL|macro|D_TS_ANCHOR
mdefine_line|#define D_TS_ANCHOR&t;(7&lt;&lt;10) /* Starting short pipes */
DECL|macro|D_TS_MON
mdefine_line|#define D_TS_MON(v)    ((v)&lt;&lt;5)        /* Monitor Pipe */
DECL|macro|D_TS_NEXT
mdefine_line|#define D_TS_NEXT(v)   ((v)&lt;&lt;0)        /* Pipe Nr: 0-15 long, 16-21 short */
multiline_comment|/* Concentration Highway Interface Modes */
DECL|macro|D_CHI_CHICM
mdefine_line|#define D_CHI_CHICM(v)&t;((v)&lt;&lt;16)&t;/* Clock mode */
DECL|macro|D_CHI_IR
mdefine_line|#define D_CHI_IR&t;(1&lt;&lt;15) /* Immediate Interrupt Report */
DECL|macro|D_CHI_EN
mdefine_line|#define D_CHI_EN&t;(1&lt;&lt;14) /* CHIL Interrupt enabled */
DECL|macro|D_CHI_OD
mdefine_line|#define D_CHI_OD&t;(1&lt;&lt;13) /* Open Drain Enable */
DECL|macro|D_CHI_FE
mdefine_line|#define D_CHI_FE&t;(1&lt;&lt;12) /* Sample CHIFS on Rising Frame Edge */
DECL|macro|D_CHI_FD
mdefine_line|#define D_CHI_FD&t;(1&lt;&lt;11) /* Frame Drive */
DECL|macro|D_CHI_BPF
mdefine_line|#define D_CHI_BPF(v)&t;((v)&lt;&lt;0)&t;/* Bits per Frame */
multiline_comment|/* NT: These are here for completeness */
DECL|macro|D_NT_FBIT
mdefine_line|#define D_NT_FBIT&t;(1&lt;&lt;17)&t;/* Frame Bit */
DECL|macro|D_NT_NBF
mdefine_line|#define D_NT_NBF&t;(1&lt;&lt;16)&t;/* Number of bad frames to loose framing */
DECL|macro|D_NT_IRM_IMM
mdefine_line|#define D_NT_IRM_IMM&t;(1&lt;&lt;15)&t;/* Interrupt Report &amp; Mask: Immediate */
DECL|macro|D_NT_IRM_EN
mdefine_line|#define D_NT_IRM_EN&t;(1&lt;&lt;14)&t;/* Interrupt Report &amp; Mask: Enable */
DECL|macro|D_NT_ISNT
mdefine_line|#define D_NT_ISNT&t;(1&lt;&lt;13)&t;/* Configfure interface as NT */
DECL|macro|D_NT_FT
mdefine_line|#define D_NT_FT&t;&t;(1&lt;&lt;12)&t;/* Fixed Timing */
DECL|macro|D_NT_EZ
mdefine_line|#define D_NT_EZ&t;&t;(1&lt;&lt;11)&t;/* Echo Channel is Zeros */
DECL|macro|D_NT_IFA
mdefine_line|#define D_NT_IFA&t;(1&lt;&lt;10)&t;/* Inhibit Final Activation */
DECL|macro|D_NT_ACT
mdefine_line|#define D_NT_ACT&t;(1&lt;&lt;9)&t;/* Activate Interface */
DECL|macro|D_NT_MFE
mdefine_line|#define D_NT_MFE&t;(1&lt;&lt;8)&t;/* Multiframe Enable */
DECL|macro|D_NT_RLB
mdefine_line|#define D_NT_RLB(v)&t;((v)&lt;&lt;5)&t;/* Remote Loopback */
DECL|macro|D_NT_LLB
mdefine_line|#define D_NT_LLB(v)&t;((v)&lt;&lt;2)&t;/* Local Loopback */
DECL|macro|D_NT_FACT
mdefine_line|#define D_NT_FACT&t;(1&lt;&lt;1)&t;/* Force Activation */
DECL|macro|D_NT_ABV
mdefine_line|#define D_NT_ABV&t;(1&lt;&lt;0)&t;/* Activate Bipolar Violation */
multiline_comment|/* Codec Setup */
DECL|macro|D_CDEC_CK
mdefine_line|#define D_CDEC_CK(v)&t;((v)&lt;&lt;24)&t;/* Clock Select */
DECL|macro|D_CDEC_FED
mdefine_line|#define D_CDEC_FED(v)&t;((v)&lt;&lt;12)&t;/* FSCOD Falling Edge Delay */
DECL|macro|D_CDEC_RED
mdefine_line|#define D_CDEC_RED(v)&t;((v)&lt;&lt;0)&t;/* FSCOD Rising Edge Delay */
multiline_comment|/* Test */
DECL|macro|D_TEST_RAM
mdefine_line|#define D_TEST_RAM(v)&t;((v)&lt;&lt;16)&t;/* RAM Pointer */
DECL|macro|D_TEST_SIZE
mdefine_line|#define D_TEST_SIZE(v)&t;((v)&lt;&lt;11)&t;/* */
DECL|macro|D_TEST_ROMONOFF
mdefine_line|#define D_TEST_ROMONOFF&t;0x5&t;/* Toggle ROM opcode monitor on/off */
DECL|macro|D_TEST_PROC
mdefine_line|#define D_TEST_PROC&t;0x6&t;/* MicroProcessor test */
DECL|macro|D_TEST_SER
mdefine_line|#define D_TEST_SER&t;0x7&t;/* Serial-Controller test */
DECL|macro|D_TEST_RAMREAD
mdefine_line|#define D_TEST_RAMREAD&t;0x8&t;/* Copy from Ram to system memory */
DECL|macro|D_TEST_RAMWRITE
mdefine_line|#define D_TEST_RAMWRITE&t;0x9&t;/* Copy into Ram from system memory */
DECL|macro|D_TEST_RAMBIST
mdefine_line|#define D_TEST_RAMBIST&t;0xa&t;/* RAM Built-In Self Test */
DECL|macro|D_TEST_MCBIST
mdefine_line|#define D_TEST_MCBIST&t;0xb&t;/* Microcontroller Built-In Self Test */
DECL|macro|D_TEST_DUMP
mdefine_line|#define D_TEST_DUMP&t;0xe&t;/* ROM Dump */
multiline_comment|/* CHI Data Mode */
DECL|macro|D_CDM_THI
mdefine_line|#define D_CDM_THI&t;(1&lt;&lt;8)&t;/* Transmit Data on CHIDR Pin */
DECL|macro|D_CDM_RHI
mdefine_line|#define D_CDM_RHI&t;(1&lt;&lt;7)&t;/* Receive Data on CHIDX Pin */
DECL|macro|D_CDM_RCE
mdefine_line|#define D_CDM_RCE&t;(1&lt;&lt;6)&t;/* Receive on Rising Edge of CHICK */
DECL|macro|D_CDM_XCE
mdefine_line|#define D_CDM_XCE&t;(1&lt;&lt;2)&t;/* Transmit Data on Rising Edge of CHICK */
DECL|macro|D_CDM_XEN
mdefine_line|#define D_CDM_XEN&t;(1&lt;&lt;1)&t;/* Transmit Highway Enable */
DECL|macro|D_CDM_REN
mdefine_line|#define D_CDM_REN&t;(1&lt;&lt;0)&t;/* Receive Highway Enable */
multiline_comment|/* The Interrupts */
DECL|macro|D_INTR_BRDY
mdefine_line|#define D_INTR_BRDY&t;1&t;/* Buffer Ready for processing */
DECL|macro|D_INTR_MINT
mdefine_line|#define D_INTR_MINT&t;2&t;/* Marked Interrupt in RD/TD */
DECL|macro|D_INTR_IBEG
mdefine_line|#define D_INTR_IBEG&t;3&t;/* Flag to idle transition detected (HDLC) */
DECL|macro|D_INTR_IEND
mdefine_line|#define D_INTR_IEND&t;4&t;/* Idle to flag transition detected (HDLC) */
DECL|macro|D_INTR_EOL
mdefine_line|#define D_INTR_EOL&t;5&t;/* End of List */
DECL|macro|D_INTR_CMDI
mdefine_line|#define D_INTR_CMDI&t;6&t;/* Command has bean read */
DECL|macro|D_INTR_XCMP
mdefine_line|#define D_INTR_XCMP&t;8&t;/* Transmission of frame complete */
DECL|macro|D_INTR_SBRI
mdefine_line|#define D_INTR_SBRI&t;9&t;/* BRI status change info */
DECL|macro|D_INTR_FXDT
mdefine_line|#define D_INTR_FXDT&t;10&t;/* Fixed data change */
DECL|macro|D_INTR_CHIL
mdefine_line|#define D_INTR_CHIL&t;11&t;/* CHI lost frame sync (channel 36 only) */
DECL|macro|D_INTR_COLL
mdefine_line|#define D_INTR_COLL&t;11&t;/* Unrecoverable D-Channel collision */
DECL|macro|D_INTR_DBYT
mdefine_line|#define D_INTR_DBYT&t;12&t;/* Dropped by frame slip */
DECL|macro|D_INTR_RBYT
mdefine_line|#define D_INTR_RBYT&t;13&t;/* Repeated by frame slip */
DECL|macro|D_INTR_LINT
mdefine_line|#define D_INTR_LINT&t;14&t;/* Lost Interrupt */
DECL|macro|D_INTR_UNDR
mdefine_line|#define D_INTR_UNDR&t;15&t;/* DMA underrun */
DECL|macro|D_INTR_TE
mdefine_line|#define D_INTR_TE&t;32
DECL|macro|D_INTR_NT
mdefine_line|#define D_INTR_NT&t;34
DECL|macro|D_INTR_CHI
mdefine_line|#define D_INTR_CHI&t;36
DECL|macro|D_INTR_CMD
mdefine_line|#define D_INTR_CMD&t;38
DECL|macro|D_INTR_GETCHAN
mdefine_line|#define D_INTR_GETCHAN(v)&t;(((v)&gt;&gt;24) &amp; 0x3f)
DECL|macro|D_INTR_GETCODE
mdefine_line|#define D_INTR_GETCODE(v)&t;(((v)&gt;&gt;20) &amp; 0xf)
DECL|macro|D_INTR_GETCMD
mdefine_line|#define D_INTR_GETCMD(v)&t;(((v)&gt;&gt;16) &amp; 0xf)
DECL|macro|D_INTR_GETVAL
mdefine_line|#define D_INTR_GETVAL(v)&t;((v) &amp; 0xffff)
DECL|macro|D_INTR_GETRVAL
mdefine_line|#define D_INTR_GETRVAL(v)&t;((v) &amp; 0xfffff)
DECL|macro|D_P_0
mdefine_line|#define D_P_0&t;&t;0&t;/* TE receive anchor */
DECL|macro|D_P_1
mdefine_line|#define D_P_1&t;&t;1&t;/* TE transmit anchor */
DECL|macro|D_P_2
mdefine_line|#define D_P_2&t;&t;2&t;/* NT transmit anchor */
DECL|macro|D_P_3
mdefine_line|#define D_P_3&t;&t;3&t;/* NT receive anchor */
DECL|macro|D_P_4
mdefine_line|#define D_P_4&t;&t;4&t;/* CHI send data */
DECL|macro|D_P_5
mdefine_line|#define D_P_5&t;&t;5&t;/* CHI receive data */
DECL|macro|D_P_6
mdefine_line|#define D_P_6&t;&t;6&t;/* */
DECL|macro|D_P_7
mdefine_line|#define D_P_7&t;&t;7&t;/* */
DECL|macro|D_P_8
mdefine_line|#define D_P_8&t;&t;8&t;/* */
DECL|macro|D_P_9
mdefine_line|#define D_P_9&t;&t;9&t;/* */
DECL|macro|D_P_10
mdefine_line|#define D_P_10&t;&t;10&t;/* */
DECL|macro|D_P_11
mdefine_line|#define D_P_11&t;&t;11&t;/* */
DECL|macro|D_P_12
mdefine_line|#define D_P_12&t;&t;12&t;/* */
DECL|macro|D_P_13
mdefine_line|#define D_P_13&t;&t;13&t;/* */
DECL|macro|D_P_14
mdefine_line|#define D_P_14&t;&t;14&t;/* */
DECL|macro|D_P_15
mdefine_line|#define D_P_15&t;&t;15&t;/* */
DECL|macro|D_P_16
mdefine_line|#define D_P_16&t;&t;16&t;/* CHI anchor pipe */
DECL|macro|D_P_17
mdefine_line|#define D_P_17&t;&t;17&t;/* CHI send */
DECL|macro|D_P_18
mdefine_line|#define D_P_18&t;&t;18&t;/* CHI receive */
DECL|macro|D_P_19
mdefine_line|#define D_P_19&t;&t;19&t;/* CHI receive */
DECL|macro|D_P_20
mdefine_line|#define D_P_20&t;&t;20&t;/* CHI receive */
DECL|macro|D_P_21
mdefine_line|#define D_P_21&t;&t;21&t;/* */
DECL|macro|D_P_22
mdefine_line|#define D_P_22&t;&t;22&t;/* */
DECL|macro|D_P_23
mdefine_line|#define D_P_23&t;&t;23&t;/* */
DECL|macro|D_P_24
mdefine_line|#define D_P_24&t;&t;24&t;/* */
DECL|macro|D_P_25
mdefine_line|#define D_P_25&t;&t;25&t;/* */
DECL|macro|D_P_26
mdefine_line|#define D_P_26&t;&t;26&t;/* */
DECL|macro|D_P_27
mdefine_line|#define D_P_27&t;&t;27&t;/* */
DECL|macro|D_P_28
mdefine_line|#define D_P_28&t;&t;28&t;/* */
DECL|macro|D_P_29
mdefine_line|#define D_P_29&t;&t;29&t;/* */
DECL|macro|D_P_30
mdefine_line|#define D_P_30&t;&t;30&t;/* */
DECL|macro|D_P_31
mdefine_line|#define D_P_31&t;&t;31&t;/* */
multiline_comment|/* Transmit descriptor defines */
DECL|macro|DBRI_TD_F
mdefine_line|#define DBRI_TD_F&t;(1&lt;&lt;31)&t;/* End of Frame */
DECL|macro|DBRI_TD_D
mdefine_line|#define DBRI_TD_D&t;(1&lt;&lt;30)&t;/* Do not append CRC */
DECL|macro|DBRI_TD_CNT
mdefine_line|#define DBRI_TD_CNT(v)&t;((v)&lt;&lt;16)&t;/* Number of valid bytes in the buffer */
DECL|macro|DBRI_TD_B
mdefine_line|#define DBRI_TD_B&t;(1&lt;&lt;15)&t;/* Final interrupt */
DECL|macro|DBRI_TD_M
mdefine_line|#define DBRI_TD_M&t;(1&lt;&lt;14)&t;/* Marker interrupt */
DECL|macro|DBRI_TD_I
mdefine_line|#define DBRI_TD_I&t;(1&lt;&lt;13)&t;/* Transmit Idle Characters */
DECL|macro|DBRI_TD_FCNT
mdefine_line|#define DBRI_TD_FCNT(v)&t;(v)&t;/* Flag Count */
DECL|macro|DBRI_TD_UNR
mdefine_line|#define DBRI_TD_UNR&t;(1&lt;&lt;3)&t;/* Underrun: transmitter is out of data */
DECL|macro|DBRI_TD_ABT
mdefine_line|#define DBRI_TD_ABT&t;(1&lt;&lt;2)&t;/* Abort: frame aborted */
DECL|macro|DBRI_TD_TBC
mdefine_line|#define DBRI_TD_TBC&t;(1&lt;&lt;0)&t;/* Transmit buffer Complete */
DECL|macro|DBRI_TD_STATUS
mdefine_line|#define DBRI_TD_STATUS(v)       ((v)&amp;0xff)      /* Transmit status */
multiline_comment|/* Receive descriptor defines */
DECL|macro|DBRI_RD_F
mdefine_line|#define DBRI_RD_F&t;(1&lt;&lt;31)&t;/* End of Frame */
DECL|macro|DBRI_RD_C
mdefine_line|#define DBRI_RD_C&t;(1&lt;&lt;30)&t;/* Completed buffer */
DECL|macro|DBRI_RD_B
mdefine_line|#define DBRI_RD_B&t;(1&lt;&lt;15)&t;/* Final interrupt */
DECL|macro|DBRI_RD_M
mdefine_line|#define DBRI_RD_M&t;(1&lt;&lt;14)&t;/* Marker interrupt */
DECL|macro|DBRI_RD_BCNT
mdefine_line|#define DBRI_RD_BCNT(v)&t;(v)&t;/* Buffer size */
DECL|macro|DBRI_RD_CRC
mdefine_line|#define DBRI_RD_CRC&t;(1&lt;&lt;7)&t;/* 0: CRC is correct */
DECL|macro|DBRI_RD_BBC
mdefine_line|#define DBRI_RD_BBC&t;(1&lt;&lt;6)&t;/* 1: Bad Byte received */
DECL|macro|DBRI_RD_ABT
mdefine_line|#define DBRI_RD_ABT&t;(1&lt;&lt;5)&t;/* Abort: frame aborted */
DECL|macro|DBRI_RD_OVRN
mdefine_line|#define DBRI_RD_OVRN&t;(1&lt;&lt;3)&t;/* Overrun: data lost */
DECL|macro|DBRI_RD_STATUS
mdefine_line|#define DBRI_RD_STATUS(v)      ((v)&amp;0xff)      /* Receive status */
DECL|macro|DBRI_RD_CNT
mdefine_line|#define DBRI_RD_CNT(v) (((v)&gt;&gt;16)&amp;0x1fff)        /* Number of valid bytes in the buffer */
macro_line|#endif /* _DBRI_H_ */
eof
