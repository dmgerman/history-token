multiline_comment|/* $Id: tpam.h,v 1.1.2.3 2001/11/06 20:58:30 kai Exp $&n; *&n; * Turbo PAM ISDN driver for Linux. (Kernel Driver)&n; *&n; * Copyright 2001 Stelian Pop &lt;stelian.pop@fr.alcove.com&gt;, Alc&#xfffd;ve&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * For all support questions please contact: &lt;support@auvertech.fr&gt;&n; *&n; */
macro_line|#ifndef _TPAM_PRIV_H_
DECL|macro|_TPAM_PRIV_H_
mdefine_line|#define _TPAM_PRIV_H_
macro_line|#include &lt;linux/isdnif.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/* Maximum number of channels for this board */
DECL|macro|TPAM_NBCHANNEL
mdefine_line|#define TPAM_NBCHANNEL&t;&t;30
multiline_comment|/* Maximum size of data */
DECL|macro|TPAM_MAXBUFSIZE
mdefine_line|#define TPAM_MAXBUFSIZE&t;&t;2032
multiline_comment|/* Size of a page of board memory */
DECL|macro|TPAM_PAGE_SIZE
mdefine_line|#define TPAM_PAGE_SIZE&t;&t;0x003ffffc&t;/* 4 MB */
multiline_comment|/* Magic number present if the board was successfully started */
DECL|macro|TPAM_MAGICNUMBER
mdefine_line|#define TPAM_MAGICNUMBER&t;0x2a343242
multiline_comment|/* Registers in the PCI BAR0 */
DECL|macro|TPAM_PAGE_REGISTER
mdefine_line|#define TPAM_PAGE_REGISTER&t;0x00400000&t;/* Select page */
DECL|macro|TPAM_DSPINT_REGISTER
mdefine_line|#define TPAM_DSPINT_REGISTER&t;0x00400004&t;/* Interrupt board */
DECL|macro|TPAM_RESETPAM_REGISTER
mdefine_line|#define TPAM_RESETPAM_REGISTER&t;0x00400008&t;/* Reset board */
DECL|macro|TPAM_HINTACK_REGISTER
mdefine_line|#define TPAM_HINTACK_REGISTER&t;0x0040000c&t;/* Ack interrupt */
DECL|macro|TPAM_HPIC_REGISTER
mdefine_line|#define TPAM_HPIC_REGISTER&t;0x00400014&t;/* Board ready */
multiline_comment|/* Registers in the board memory */
DECL|macro|TPAM_MAGICNUMBER_REGISTER
mdefine_line|#define TPAM_MAGICNUMBER_REGISTER&t;0x80008000 /* Magic number */
DECL|macro|TPAM_EXID_REGISTER
mdefine_line|#define TPAM_EXID_REGISTER&t;&t;0x80008004 /* EXID - not used */
DECL|macro|TPAM_UPLOADPTR_REGISTER
mdefine_line|#define TPAM_UPLOADPTR_REGISTER&t;&t;0x80008008 /* Upload data ptr */
DECL|macro|TPAM_DOWNLOADPTR_REGISTER
mdefine_line|#define TPAM_DOWNLOADPTR_REGISTER&t;0x8000800c /* Download data ptr */
DECL|macro|TPAM_ACKUPLOAD_REGISTER
mdefine_line|#define TPAM_ACKUPLOAD_REGISTER&t;&t;0x80008010 /* Ack upload */
DECL|macro|TPAM_ACKDOWNLOAD_REGISTER
mdefine_line|#define TPAM_ACKDOWNLOAD_REGISTER&t;0x80008014 /* Ack download */
DECL|macro|TPAM_INTERRUPTACK_REGISTER
mdefine_line|#define TPAM_INTERRUPTACK_REGISTER&t;0x80008018 /* Ack interrupt */
multiline_comment|/* Reserved areas in the board memory */
DECL|macro|TPAM_RESERVEDAREA1_START
mdefine_line|#define&t;TPAM_RESERVEDAREA1_START&t;0x00000000
DECL|macro|TPAM_RESERVEDAREA1_END
mdefine_line|#define TPAM_RESERVEDAREA1_END&t;&t;0x003FFFFF
DECL|macro|TPAM_RESERVEDAREA2_START
mdefine_line|#define TPAM_RESERVEDAREA2_START&t;0x01C00000
DECL|macro|TPAM_RESERVEDAREA2_END
mdefine_line|#define TPAM_RESERVEDAREA2_END&t;&t;0x01FFFFFF
DECL|macro|TPAM_RESERVEDAREA3_START
mdefine_line|#define TPAM_RESERVEDAREA3_START&t;0x04000000
DECL|macro|TPAM_RESERVEDAREA3_END
mdefine_line|#define TPAM_RESERVEDAREA3_END&t;&t;0x7FFFFFFF
DECL|macro|TPAM_RESERVEDAREA4_START
mdefine_line|#define TPAM_RESERVEDAREA4_START&t;0x80010000
DECL|macro|TPAM_RESERVEDAREA4_END
mdefine_line|#define TPAM_RESERVEDAREA4_END&t;&t;0xFFFFFFFF
multiline_comment|/* NCO ID invalid */
DECL|macro|TPAM_NCOID_INVALID
mdefine_line|#define TPAM_NCOID_INVALID&t;0xffff
multiline_comment|/* channel number invalid */
DECL|macro|TPAM_CHANNEL_INVALID
mdefine_line|#define TPAM_CHANNEL_INVALID&t;0xffff
multiline_comment|/* Channel structure */
DECL|struct|tpam_channel
r_typedef
r_struct
id|tpam_channel
(brace
DECL|member|num
r_int
id|num
suffix:semicolon
multiline_comment|/* channel number */
DECL|member|card
r_struct
id|tpam_card
op_star
id|card
suffix:semicolon
multiline_comment|/* channel&squot;s card */
DECL|member|ncoid
id|u32
id|ncoid
suffix:semicolon
multiline_comment|/* ncoid */
DECL|member|hdlc
id|u8
id|hdlc
suffix:semicolon
multiline_comment|/* hdlc mode (set by user level) */
DECL|member|realhdlc
id|u8
id|realhdlc
suffix:semicolon
multiline_comment|/* hdlc mode (negociated with peer) */
DECL|member|hdlcshift
id|u32
id|hdlcshift
suffix:semicolon
multiline_comment|/* hdlc shift */
DECL|member|readytoreceive
id|u8
id|readytoreceive
suffix:semicolon
multiline_comment|/* channel ready to receive data */
DECL|member|sendq
r_struct
id|sk_buff_head
id|sendq
suffix:semicolon
multiline_comment|/* Send queue */
DECL|typedef|tpam_channel
)brace
id|tpam_channel
suffix:semicolon
multiline_comment|/* Card structure */
DECL|struct|tpam_card
r_typedef
r_struct
id|tpam_card
(brace
DECL|member|next
r_struct
id|tpam_card
op_star
id|next
suffix:semicolon
multiline_comment|/* next card in list */
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ used by this board */
DECL|member|bar0
r_int
r_int
id|bar0
suffix:semicolon
multiline_comment|/* ioremapped bar0 */
DECL|member|id
r_int
id|id
suffix:semicolon
multiline_comment|/* id of the board */
DECL|member|interface
id|isdn_if
id|interface
suffix:semicolon
multiline_comment|/* isdn link-level pointer */
DECL|member|channels_used
r_int
id|channels_used
suffix:semicolon
multiline_comment|/* number of channels actually used */
DECL|member|channels_tested
r_int
id|channels_tested
suffix:semicolon
multiline_comment|/* number of channels being tested */
DECL|member|loopmode
id|u8
id|loopmode
suffix:semicolon
multiline_comment|/* board in looptest mode */
DECL|member|channels
id|tpam_channel
id|channels
(braket
id|TPAM_NBCHANNEL
)braket
suffix:semicolon
multiline_comment|/* channels tab */
DECL|member|running
r_int
id|running
suffix:semicolon
multiline_comment|/* card is running */
DECL|member|busy
r_int
id|busy
suffix:semicolon
multiline_comment|/* waiting for ack from card */
DECL|member|roundrobin
r_int
id|roundrobin
suffix:semicolon
multiline_comment|/* round robin between channels */
DECL|member|sendq
r_struct
id|sk_buff_head
id|sendq
suffix:semicolon
multiline_comment|/* send queue */
DECL|member|recvq
r_struct
id|sk_buff_head
id|recvq
suffix:semicolon
multiline_comment|/* receive queue */
DECL|member|send_tq
r_struct
id|tq_struct
id|send_tq
suffix:semicolon
multiline_comment|/* send task queue */
DECL|member|recv_tq
r_struct
id|tq_struct
id|recv_tq
suffix:semicolon
multiline_comment|/* receive task queue */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* lock for the card */
DECL|typedef|tpam_card
)brace
id|tpam_card
suffix:semicolon
multiline_comment|/* Timeout waiting for signature to become available */
DECL|macro|SIGNATURE_TIMEOUT
mdefine_line|#define SIGNATURE_TIMEOUT&t;(5*HZ)
multiline_comment|/* Timeout waiting for receiving all the ACreateNCOCnf */
DECL|macro|NCOCREATE_TIMEOUT
mdefine_line|#define NCOCREATE_TIMEOUT&t;(30*HZ)
multiline_comment|/* Maximum size of the TLV block */
DECL|macro|MPB_MAXIMUMBLOCKTLVSIZE
mdefine_line|#define MPB_MAXIMUMBLOCKTLVSIZE&t; 128
multiline_comment|/* Maximum size of the data block */
DECL|macro|MPB_MAXIMUMDATASIZE
mdefine_line|#define MPB_MAXIMUMDATASIZE&t;4904
multiline_comment|/* Maximum size of a phone number */
DECL|macro|PHONE_MAXIMUMSIZE
mdefine_line|#define PHONE_MAXIMUMSIZE&t;  32
multiline_comment|/* Header for a sk_buff structure */
DECL|struct|skb_header
r_typedef
r_struct
id|skb_header
(brace
DECL|member|size
id|u16
id|size
suffix:semicolon
multiline_comment|/* size of pci_mpb block + size of tlv block */
DECL|member|data_size
id|u16
id|data_size
suffix:semicolon
multiline_comment|/* size of the data block */
DECL|member|ack
id|u16
id|ack
suffix:semicolon
multiline_comment|/* packet needs to send ack upon send */
DECL|member|ack_size
id|u16
id|ack_size
suffix:semicolon
multiline_comment|/* size of data to be acknowledged upon send */
DECL|typedef|skb_header
)brace
id|skb_header
suffix:semicolon
multiline_comment|/* PCI message header structure */
DECL|struct|pci_mpb
r_typedef
r_struct
id|pci_mpb
(brace
DECL|member|exID
id|u16
id|exID
suffix:semicolon
multiline_comment|/* exID - not used */
DECL|member|flags
id|u16
id|flags
suffix:semicolon
multiline_comment|/* flags - not used */
DECL|member|errorCode
id|u32
id|errorCode
suffix:semicolon
multiline_comment|/* errorCode - not used */
DECL|member|messageID
id|u16
id|messageID
suffix:semicolon
multiline_comment|/* message ID - one of ID_XXX */
DECL|member|maximumBlockTLVSize
id|u16
id|maximumBlockTLVSize
suffix:semicolon
multiline_comment|/* MPB_MAXIMUMBLOCKTLVSIZE */
DECL|member|actualBlockTLVSize
id|u16
id|actualBlockTLVSize
suffix:semicolon
multiline_comment|/* size of the tlv block */
DECL|member|maximumDataSize
id|u16
id|maximumDataSize
suffix:semicolon
multiline_comment|/* MPB_MAXIMUMDATASIZE */
DECL|member|actualDataSize
id|u16
id|actualDataSize
suffix:semicolon
multiline_comment|/* size of the data block */
DECL|member|dummy
id|u16
id|dummy
suffix:semicolon
multiline_comment|/* padding */
DECL|typedef|pci_mpb
)brace
id|pci_mpb
suffix:semicolon
multiline_comment|/* Types of PCI messages */
DECL|macro|ID_ACreateNCOReq
mdefine_line|#define ID_ACreateNCOReq&t;101
DECL|macro|ID_ACreateNCOCnf
mdefine_line|#define ID_ACreateNCOCnf&t;102
DECL|macro|ID_ADestroyNCOReq
mdefine_line|#define ID_ADestroyNCOReq&t;103
DECL|macro|ID_ADestroyNCOCnf
mdefine_line|#define ID_ADestroyNCOCnf&t;104
DECL|macro|ID_CConnectReq
mdefine_line|#define ID_CConnectReq&t;&t;203
DECL|macro|ID_CConnectInd
mdefine_line|#define ID_CConnectInd&t;&t;204
DECL|macro|ID_CConnectRsp
mdefine_line|#define ID_CConnectRsp&t;&t;205
DECL|macro|ID_CConnectCnf
mdefine_line|#define ID_CConnectCnf&t;&t;206
DECL|macro|ID_CDisconnectReq
mdefine_line|#define ID_CDisconnectReq&t;207
DECL|macro|ID_CDisconnectInd
mdefine_line|#define ID_CDisconnectInd&t;208
DECL|macro|ID_CDisconnectRsp
mdefine_line|#define ID_CDisconnectRsp&t;209
DECL|macro|ID_CDisconnectCnf
mdefine_line|#define ID_CDisconnectCnf&t;210
DECL|macro|ID_U3DataReq
mdefine_line|#define ID_U3DataReq&t;&t;307
DECL|macro|ID_U3DataInd
mdefine_line|#define ID_U3DataInd&t;&t;308
DECL|macro|ID_U3ReadyToReceiveInd
mdefine_line|#define ID_U3ReadyToReceiveInd&t;318
multiline_comment|/* Parameters for the PCI message TLV block */
DECL|macro|PAR_BearerCap
mdefine_line|#define PAR_BearerCap&t;&t;3
DECL|macro|PAR_CalledNumber
mdefine_line|#define PAR_CalledNumber&t;7
DECL|macro|PAR_CallingNumber
mdefine_line|#define PAR_CallingNumber&t;11
DECL|macro|PAR_CauseToPUF
mdefine_line|#define PAR_CauseToPUF&t;&t;15
DECL|macro|PAR_Cdirection
mdefine_line|#define PAR_Cdirection&t;&t;16
DECL|macro|PAR_CompletionStatus
mdefine_line|#define PAR_CompletionStatus&t;19
DECL|macro|PAR_Facility
mdefine_line|#define PAR_Facility&t;&t;30
DECL|macro|PAR_HLC
mdefine_line|#define PAR_HLC&t;&t;&t;34
DECL|macro|PAR_NCOID
mdefine_line|#define PAR_NCOID&t;&t;49
DECL|macro|PAR_NCOType
mdefine_line|#define PAR_NCOType&t;&t;50
DECL|macro|PAR_ReadyFlag
mdefine_line|#define PAR_ReadyFlag&t;&t;55
DECL|macro|PAR_U3Protocol
mdefine_line|#define PAR_U3Protocol&t;&t;62
DECL|macro|PAR_Udirection
mdefine_line|#define PAR_Udirection&t;&t;64
multiline_comment|/* Delayed statcallb structure */
DECL|struct|tpam_statcallb_data
r_typedef
r_struct
id|tpam_statcallb_data
(brace
DECL|member|card
id|tpam_card
op_star
id|card
suffix:semicolon
multiline_comment|/* card issuing the statcallb */
DECL|member|timer
r_struct
id|timer_list
op_star
id|timer
suffix:semicolon
multiline_comment|/* timer launching the statcallb */
DECL|member|ctrl
id|isdn_ctrl
id|ctrl
suffix:semicolon
multiline_comment|/* isdn command */
DECL|typedef|tpam_statcallb_data
)brace
id|tpam_statcallb_data
suffix:semicolon
multiline_comment|/* Function prototypes from tpam_main.c */
r_extern
id|tpam_card
op_star
id|tpam_findcard
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
id|u32
id|tpam_findchannel
c_func
(paren
id|tpam_card
op_star
comma
id|u32
)paren
suffix:semicolon
multiline_comment|/* Function prototypes from tpam_memory.c */
r_extern
r_void
id|copy_to_pam_dword
c_func
(paren
id|tpam_card
op_star
comma
r_const
r_void
op_star
comma
id|u32
)paren
suffix:semicolon
r_extern
r_void
id|copy_to_pam
c_func
(paren
id|tpam_card
op_star
comma
r_void
op_star
comma
r_const
r_void
op_star
comma
id|u32
)paren
suffix:semicolon
r_extern
id|u32
id|copy_from_pam_dword
c_func
(paren
id|tpam_card
op_star
comma
r_const
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|copy_from_pam
c_func
(paren
id|tpam_card
op_star
comma
r_void
op_star
comma
r_const
r_void
op_star
comma
id|u32
)paren
suffix:semicolon
r_extern
r_int
id|copy_from_pam_to_user
c_func
(paren
id|tpam_card
op_star
comma
r_void
op_star
comma
r_const
r_void
op_star
comma
id|u32
)paren
suffix:semicolon
r_extern
r_int
id|copy_from_user_to_pam
c_func
(paren
id|tpam_card
op_star
comma
r_void
op_star
comma
r_const
r_void
op_star
comma
id|u32
)paren
suffix:semicolon
r_extern
r_int
id|tpam_verify_area
c_func
(paren
id|u32
comma
id|u32
)paren
suffix:semicolon
multiline_comment|/* Function prototypes from tpam_nco.c */
r_extern
r_struct
id|sk_buff
op_star
id|build_ACreateNCOReq
c_func
(paren
r_const
id|u8
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|build_ADestroyNCOReq
c_func
(paren
id|u32
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|build_CConnectReq
c_func
(paren
id|u32
comma
r_const
id|u8
op_star
comma
id|u8
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|build_CConnectRsp
c_func
(paren
id|u32
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|build_CDisconnectReq
c_func
(paren
id|u32
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|build_CDisconnectRsp
c_func
(paren
id|u32
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|build_U3DataReq
c_func
(paren
id|u32
comma
r_void
op_star
comma
id|u16
comma
id|u16
comma
id|u16
)paren
suffix:semicolon
r_extern
r_int
id|parse_ACreateNCOCnf
c_func
(paren
r_struct
id|sk_buff
op_star
comma
id|u8
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
r_extern
r_int
id|parse_ADestroyNCOCnf
c_func
(paren
r_struct
id|sk_buff
op_star
comma
id|u8
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
r_extern
r_int
id|parse_CConnectCnf
c_func
(paren
r_struct
id|sk_buff
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
r_extern
r_int
id|parse_CConnectInd
c_func
(paren
r_struct
id|sk_buff
op_star
comma
id|u32
op_star
comma
id|u8
op_star
comma
id|u8
op_star
comma
id|u8
op_star
comma
id|u8
op_star
comma
id|u8
op_star
)paren
suffix:semicolon
r_extern
r_int
id|parse_CDisconnectCnf
c_func
(paren
r_struct
id|sk_buff
op_star
comma
id|u32
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
r_extern
r_int
id|parse_CDisconnectInd
c_func
(paren
r_struct
id|sk_buff
op_star
comma
id|u32
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
r_extern
r_int
id|parse_U3ReadyToReceiveInd
c_func
(paren
r_struct
id|sk_buff
op_star
comma
id|u32
op_star
comma
id|u8
op_star
)paren
suffix:semicolon
r_extern
r_int
id|parse_U3DataInd
c_func
(paren
r_struct
id|sk_buff
op_star
comma
id|u32
op_star
comma
id|u8
op_star
op_star
comma
id|u16
op_star
)paren
suffix:semicolon
multiline_comment|/* Function prototypes from tpam_queues.c */
r_extern
r_void
id|tpam_enqueue
c_func
(paren
id|tpam_card
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tpam_enqueue_data
c_func
(paren
id|tpam_channel
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tpam_irq
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tpam_recv_tq
c_func
(paren
id|tpam_card
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tpam_send_tq
c_func
(paren
id|tpam_card
op_star
)paren
suffix:semicolon
multiline_comment|/* Function prototypes from tpam_commands.c */
r_extern
r_int
id|tpam_command
c_func
(paren
id|isdn_ctrl
op_star
)paren
suffix:semicolon
r_extern
r_int
id|tpam_writebuf_skb
c_func
(paren
r_int
comma
r_int
comma
r_int
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tpam_recv_ACreateNCOCnf
c_func
(paren
id|tpam_card
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tpam_recv_ADestroyNCOCnf
c_func
(paren
id|tpam_card
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tpam_recv_CConnectCnf
c_func
(paren
id|tpam_card
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tpam_recv_CConnectInd
c_func
(paren
id|tpam_card
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tpam_recv_CDisconnectInd
c_func
(paren
id|tpam_card
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tpam_recv_CDisconnectCnf
c_func
(paren
id|tpam_card
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tpam_recv_U3DataInd
c_func
(paren
id|tpam_card
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tpam_recv_U3ReadyToReceiveInd
c_func
(paren
id|tpam_card
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/* Function prototypes from tpam_hdlc.c */
r_extern
id|u32
id|tpam_hdlc_encode
c_func
(paren
id|u8
op_star
comma
id|u8
op_star
comma
id|u32
op_star
comma
id|u32
)paren
suffix:semicolon
r_extern
id|u32
id|tpam_hdlc_decode
c_func
(paren
id|u8
op_star
comma
id|u8
op_star
comma
id|u32
)paren
suffix:semicolon
multiline_comment|/* Function prototypes from tpam_crcpc.c */
r_extern
r_void
id|init_CRC
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|hdlc_encode_modem
c_func
(paren
id|u8
op_star
comma
id|u32
comma
id|u8
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hdlc_no_accm_encode
c_func
(paren
id|u8
op_star
comma
id|u32
comma
id|u8
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
r_extern
id|u32
id|hdlc_no_accm_decode
c_func
(paren
id|u8
op_star
comma
id|u32
)paren
suffix:semicolon
multiline_comment|/* Define this to enable debug tracing prints */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk printk
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk while(0) printk
macro_line|#endif
macro_line|#endif /* _TPAM_H_ */
eof
