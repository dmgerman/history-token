multiline_comment|/*&n; * serial167.h&n; *&n; * Richard Hirst [richard@sleepie.demon.co.uk]&n; *&n; * Based on cyclades.h&n; */
DECL|struct|cyclades_monitor
r_struct
id|cyclades_monitor
(brace
DECL|member|int_count
r_int
r_int
id|int_count
suffix:semicolon
DECL|member|char_count
r_int
r_int
id|char_count
suffix:semicolon
DECL|member|char_max
r_int
r_int
id|char_max
suffix:semicolon
DECL|member|char_last
r_int
r_int
id|char_last
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is our internal structure for each serial port&squot;s state.&n; * &n; * Many fields are paralleled by the structure used by the serial_struct&n; * structure.&n; *&n; * For definitions of the flags field, see tty.h&n; */
DECL|struct|cyclades_port
r_struct
id|cyclades_port
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|card
r_int
id|card
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* defined in tty.h */
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|read_status_mask
r_int
id|read_status_mask
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
DECL|member|xmit_fifo_size
r_int
id|xmit_fifo_size
suffix:semicolon
DECL|member|cor1
DECL|member|cor2
DECL|member|cor3
DECL|member|cor4
DECL|member|cor5
DECL|member|cor6
DECL|member|cor7
r_int
id|cor1
comma
id|cor2
comma
id|cor3
comma
id|cor4
comma
id|cor5
comma
id|cor6
comma
id|cor7
suffix:semicolon
DECL|member|tbpr
DECL|member|tco
DECL|member|rbpr
DECL|member|rco
r_int
id|tbpr
comma
id|tco
comma
id|rbpr
comma
id|rco
suffix:semicolon
DECL|member|ignore_status_mask
r_int
id|ignore_status_mask
suffix:semicolon
DECL|member|close_delay
r_int
id|close_delay
suffix:semicolon
DECL|member|IER
r_int
id|IER
suffix:semicolon
multiline_comment|/* Interrupt Enable Register */
DECL|member|event
r_int
id|event
suffix:semicolon
DECL|member|last_active
r_int
r_int
id|last_active
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* # of fd on device */
DECL|member|x_char
r_int
id|x_char
suffix:semicolon
multiline_comment|/* to be pushed out ASAP */
DECL|member|x_break
r_int
id|x_break
suffix:semicolon
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
multiline_comment|/* # of blocked opens */
DECL|member|session
r_int
id|session
suffix:semicolon
multiline_comment|/* Session of opening process */
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
multiline_comment|/* pgrp of opening process */
DECL|member|xmit_buf
r_int
r_char
op_star
id|xmit_buf
suffix:semicolon
DECL|member|xmit_head
r_int
id|xmit_head
suffix:semicolon
DECL|member|xmit_tail
r_int
id|xmit_tail
suffix:semicolon
DECL|member|xmit_cnt
r_int
id|xmit_cnt
suffix:semicolon
DECL|member|default_threshold
r_int
id|default_threshold
suffix:semicolon
DECL|member|default_timeout
r_int
id|default_timeout
suffix:semicolon
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
DECL|member|normal_termios
r_struct
id|termios
id|normal_termios
suffix:semicolon
DECL|member|callout_termios
r_struct
id|termios
id|callout_termios
suffix:semicolon
DECL|member|open_wait
id|wait_queue_head_t
id|open_wait
suffix:semicolon
DECL|member|close_wait
id|wait_queue_head_t
id|close_wait
suffix:semicolon
DECL|member|mon
r_struct
id|cyclades_monitor
id|mon
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CYCLADES_MAGIC
mdefine_line|#define CYCLADES_MAGIC  0x4359
DECL|macro|CYGETMON
mdefine_line|#define CYGETMON                0x435901
DECL|macro|CYGETTHRESH
mdefine_line|#define CYGETTHRESH             0x435902
DECL|macro|CYSETTHRESH
mdefine_line|#define CYSETTHRESH             0x435903
DECL|macro|CYGETDEFTHRESH
mdefine_line|#define CYGETDEFTHRESH          0x435904
DECL|macro|CYSETDEFTHRESH
mdefine_line|#define CYSETDEFTHRESH          0x435905
DECL|macro|CYGETTIMEOUT
mdefine_line|#define CYGETTIMEOUT            0x435906
DECL|macro|CYSETTIMEOUT
mdefine_line|#define CYSETTIMEOUT            0x435907
DECL|macro|CYGETDEFTIMEOUT
mdefine_line|#define CYGETDEFTIMEOUT         0x435908
DECL|macro|CYSETDEFTIMEOUT
mdefine_line|#define CYSETDEFTIMEOUT         0x435909
multiline_comment|/*&n; * Events are used to schedule things to happen at timer-interrupt&n; * time, instead of at cy interrupt time.&n; */
DECL|macro|Cy_EVENT_READ_PROCESS
mdefine_line|#define Cy_EVENT_READ_PROCESS&t;0
DECL|macro|Cy_EVENT_WRITE_WAKEUP
mdefine_line|#define Cy_EVENT_WRITE_WAKEUP&t;1
DECL|macro|Cy_EVENT_HANGUP
mdefine_line|#define Cy_EVENT_HANGUP&t;&t;2
DECL|macro|Cy_EVENT_BREAK
mdefine_line|#define Cy_EVENT_BREAK&t;&t;3
DECL|macro|Cy_EVENT_OPEN_WAKEUP
mdefine_line|#define Cy_EVENT_OPEN_WAKEUP&t;4
DECL|macro|CyMaxChipsPerCard
mdefine_line|#define CyMaxChipsPerCard 1
multiline_comment|/**** cd2401 registers ****/
DECL|macro|CyGFRCR
mdefine_line|#define CyGFRCR         (0x81)
DECL|macro|CyCCR
mdefine_line|#define CyCCR&t;&t;(0x13)
DECL|macro|CyCLR_CHAN
mdefine_line|#define      CyCLR_CHAN&t;&t;(0x40)
DECL|macro|CyINIT_CHAN
mdefine_line|#define      CyINIT_CHAN&t;(0x20)
DECL|macro|CyCHIP_RESET
mdefine_line|#define      CyCHIP_RESET&t;(0x10)
DECL|macro|CyENB_XMTR
mdefine_line|#define      CyENB_XMTR&t;&t;(0x08)
DECL|macro|CyDIS_XMTR
mdefine_line|#define      CyDIS_XMTR&t;&t;(0x04)
DECL|macro|CyENB_RCVR
mdefine_line|#define      CyENB_RCVR&t;&t;(0x02)
DECL|macro|CyDIS_RCVR
mdefine_line|#define      CyDIS_RCVR&t;&t;(0x01)
DECL|macro|CyCAR
mdefine_line|#define CyCAR&t;&t;(0xee)
DECL|macro|CyIER
mdefine_line|#define CyIER&t;&t;(0x11)
DECL|macro|CyMdmCh
mdefine_line|#define      CyMdmCh&t;&t;(0x80)
DECL|macro|CyRxExc
mdefine_line|#define      CyRxExc&t;&t;(0x20)
DECL|macro|CyRxData
mdefine_line|#define      CyRxData&t;&t;(0x08)
DECL|macro|CyTxMpty
mdefine_line|#define      CyTxMpty&t;&t;(0x02)
DECL|macro|CyTxRdy
mdefine_line|#define      CyTxRdy&t;&t;(0x01)
DECL|macro|CyLICR
mdefine_line|#define CyLICR&t;&t;(0x26)
DECL|macro|CyRISR
mdefine_line|#define CyRISR&t;&t;(0x89)
DECL|macro|CyTIMEOUT
mdefine_line|#define      CyTIMEOUT&t;&t;(0x80)
DECL|macro|CySPECHAR
mdefine_line|#define      CySPECHAR&t;&t;(0x70)
DECL|macro|CyOVERRUN
mdefine_line|#define      CyOVERRUN&t;&t;(0x08)
DECL|macro|CyPARITY
mdefine_line|#define      CyPARITY&t;&t;(0x04)
DECL|macro|CyFRAME
mdefine_line|#define      CyFRAME&t;&t;(0x02)
DECL|macro|CyBREAK
mdefine_line|#define      CyBREAK&t;&t;(0x01)
DECL|macro|CyREOIR
mdefine_line|#define CyREOIR&t;&t;(0x84)
DECL|macro|CyTEOIR
mdefine_line|#define CyTEOIR&t;&t;(0x85)
DECL|macro|CyMEOIR
mdefine_line|#define CyMEOIR&t;&t;(0x86)
DECL|macro|CyNOTRANS
mdefine_line|#define      CyNOTRANS&t;&t;(0x08)
DECL|macro|CyRFOC
mdefine_line|#define CyRFOC&t;&t;(0x30)
DECL|macro|CyRDR
mdefine_line|#define CyRDR&t;&t;(0xf8)
DECL|macro|CyTDR
mdefine_line|#define CyTDR&t;&t;(0xf8)
DECL|macro|CyMISR
mdefine_line|#define CyMISR&t;&t;(0x8b)
DECL|macro|CyRISR
mdefine_line|#define CyRISR&t;&t;(0x89)
DECL|macro|CyTISR
mdefine_line|#define CyTISR&t;&t;(0x8a)
DECL|macro|CyMSVR1
mdefine_line|#define CyMSVR1&t;&t;(0xde)
DECL|macro|CyMSVR2
mdefine_line|#define CyMSVR2&t;&t;(0xdf)
DECL|macro|CyDSR
mdefine_line|#define      CyDSR&t;&t;(0x80)
DECL|macro|CyDCD
mdefine_line|#define      CyDCD&t;&t;(0x40)
DECL|macro|CyCTS
mdefine_line|#define      CyCTS&t;&t;(0x20)
DECL|macro|CyDTR
mdefine_line|#define      CyDTR&t;&t;(0x02)
DECL|macro|CyRTS
mdefine_line|#define      CyRTS&t;&t;(0x01)
DECL|macro|CyRTPRL
mdefine_line|#define CyRTPRL&t;&t;(0x25)
DECL|macro|CyRTPRH
mdefine_line|#define CyRTPRH&t;&t;(0x24)
DECL|macro|CyCOR1
mdefine_line|#define CyCOR1&t;&t;(0x10)
DECL|macro|CyPARITY_NONE
mdefine_line|#define      CyPARITY_NONE&t;(0x00)
DECL|macro|CyPARITY_E
mdefine_line|#define      CyPARITY_E&t;&t;(0x40)
DECL|macro|CyPARITY_O
mdefine_line|#define      CyPARITY_O&t;&t;(0xC0)
DECL|macro|Cy_5_BITS
mdefine_line|#define      Cy_5_BITS&t;&t;(0x04)
DECL|macro|Cy_6_BITS
mdefine_line|#define      Cy_6_BITS&t;&t;(0x05)
DECL|macro|Cy_7_BITS
mdefine_line|#define      Cy_7_BITS&t;&t;(0x06)
DECL|macro|Cy_8_BITS
mdefine_line|#define      Cy_8_BITS&t;&t;(0x07)
DECL|macro|CyCOR2
mdefine_line|#define CyCOR2&t;&t;(0x17)
DECL|macro|CyETC
mdefine_line|#define      CyETC&t;&t;(0x20)
DECL|macro|CyCtsAE
mdefine_line|#define      CyCtsAE&t;&t;(0x02)
DECL|macro|CyCOR3
mdefine_line|#define CyCOR3&t;&t;(0x16)
DECL|macro|Cy_1_STOP
mdefine_line|#define      Cy_1_STOP&t;&t;(0x02)
DECL|macro|Cy_2_STOP
mdefine_line|#define      Cy_2_STOP&t;&t;(0x04)
DECL|macro|CyCOR4
mdefine_line|#define CyCOR4&t;&t;(0x15)
DECL|macro|CyREC_FIFO
mdefine_line|#define      CyREC_FIFO&t;&t;(0x0F)  /* Receive FIFO threshold */
DECL|macro|CyCOR5
mdefine_line|#define CyCOR5&t;&t;(0x14)
DECL|macro|CyCOR6
mdefine_line|#define CyCOR6&t;&t;(0x18)
DECL|macro|CyCOR7
mdefine_line|#define CyCOR7&t;&t;(0x07)
DECL|macro|CyRBPR
mdefine_line|#define CyRBPR&t;&t;(0xcb)
DECL|macro|CyRCOR
mdefine_line|#define CyRCOR&t;&t;(0xc8)
DECL|macro|CyTBPR
mdefine_line|#define CyTBPR&t;&t;(0xc3)
DECL|macro|CyTCOR
mdefine_line|#define CyTCOR&t;&t;(0xc0)
DECL|macro|CySCHR1
mdefine_line|#define CySCHR1&t;&t;(0x1f)
DECL|macro|CySCHR2
mdefine_line|#define CySCHR2 &t;(0x1e)
DECL|macro|CyTPR
mdefine_line|#define CyTPR&t;&t;(0xda)
DECL|macro|CyPILR1
mdefine_line|#define CyPILR1&t;&t;(0xe3)
DECL|macro|CyPILR2
mdefine_line|#define CyPILR2&t;&t;(0xe0)
DECL|macro|CyPILR3
mdefine_line|#define CyPILR3&t;&t;(0xe1)
DECL|macro|CyCMR
mdefine_line|#define CyCMR&t;&t;(0x1b)
DECL|macro|CyASYNC
mdefine_line|#define      CyASYNC&t;&t;(0x02)
DECL|macro|CyLICR
mdefine_line|#define CyLICR          (0x26)
DECL|macro|CyLIVR
mdefine_line|#define CyLIVR          (0x09)
DECL|macro|CySCRL
mdefine_line|#define CySCRL&t;&t;(0x23)
DECL|macro|CySCRH
mdefine_line|#define CySCRH&t;&t;(0x22)
DECL|macro|CyTFTC
mdefine_line|#define CyTFTC&t;&t;(0x80)
multiline_comment|/* max number of chars in the FIFO */
DECL|macro|CyMAX_CHAR_FIFO
mdefine_line|#define CyMAX_CHAR_FIFO&t;12
multiline_comment|/***************************************************************************/
eof
