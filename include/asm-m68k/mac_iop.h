multiline_comment|/*&n; * I/O Processor (IOP) defines and structures, mostly snagged from A/UX&n; * header files.&n; *&n; * The original header from which this was taken is copyrighted. I&squot;ve done some&n; * rewriting (in fact my changes make this a bit more readable, IMHO) but some&n; * more should be done.&n; */
multiline_comment|/*&n; * This is the base address of the IOPs. Use this as the address of&n; * a &quot;struct iop&quot; (see below) to see where the actual registers fall.&n; */
DECL|macro|SCC_IOP_BASE_IIFX
mdefine_line|#define SCC_IOP_BASE_IIFX&t;(0x50F04000)
DECL|macro|ISM_IOP_BASE_IIFX
mdefine_line|#define ISM_IOP_BASE_IIFX&t;(0x50F12000)
DECL|macro|SCC_IOP_BASE_QUADRA
mdefine_line|#define SCC_IOP_BASE_QUADRA&t;(0x50F0C000)
DECL|macro|ISM_IOP_BASE_QUADRA
mdefine_line|#define ISM_IOP_BASE_QUADRA&t;(0x50F1E000)
multiline_comment|/* IOP status/control register bits: */
DECL|macro|IOP_BYPASS
mdefine_line|#define&t;IOP_BYPASS&t;0x01&t;/* bypass-mode hardware access */
DECL|macro|IOP_AUTOINC
mdefine_line|#define&t;IOP_AUTOINC&t;0x02&t;/* allow autoincrement of ramhi/lo */
DECL|macro|IOP_RUN
mdefine_line|#define&t;IOP_RUN&t;&t;0x04&t;/* set to 0 to reset IOP chip */
DECL|macro|IOP_IRQ
mdefine_line|#define&t;IOP_IRQ&t;&t;0x08&t;/* generate IRQ to IOP if 1 */
DECL|macro|IOP_INT0
mdefine_line|#define&t;IOP_INT0&t;0x10&t;/* intr priority from IOP to host */
DECL|macro|IOP_INT1
mdefine_line|#define&t;IOP_INT1&t;0x20&t;/* intr priority from IOP to host */
DECL|macro|IOP_HWINT
mdefine_line|#define&t;IOP_HWINT&t;0x40&t;/* IRQ from hardware; bypass mode only */
DECL|macro|IOP_DMAINACTIVE
mdefine_line|#define&t;IOP_DMAINACTIVE&t;0x80&t;/* no DMA request active; bypass mode only */
DECL|macro|NUM_IOPS
mdefine_line|#define NUM_IOPS&t;2
DECL|macro|NUM_IOP_CHAN
mdefine_line|#define NUM_IOP_CHAN&t;7
DECL|macro|NUM_IOP_MSGS
mdefine_line|#define NUM_IOP_MSGS&t;NUM_IOP_CHAN*8
DECL|macro|IOP_MSG_LEN
mdefine_line|#define IOP_MSG_LEN&t;32
multiline_comment|/* IOP reference numbers, used by the globally-visible iop_xxx functions */
DECL|macro|IOP_NUM_SCC
mdefine_line|#define IOP_NUM_SCC&t;0
DECL|macro|IOP_NUM_ISM
mdefine_line|#define IOP_NUM_ISM&t;1
multiline_comment|/* IOP channel states */
DECL|macro|IOP_MSG_IDLE
mdefine_line|#define IOP_MSG_IDLE&t;&t;0       /* idle                         */
DECL|macro|IOP_MSG_NEW
mdefine_line|#define IOP_MSG_NEW&t;&t;1       /* new message sent             */
DECL|macro|IOP_MSG_RCVD
mdefine_line|#define IOP_MSG_RCVD&t;&t;2       /* message received; processing */
DECL|macro|IOP_MSG_COMPLETE
mdefine_line|#define IOP_MSG_COMPLETE&t;3       /* message processing complete  */
multiline_comment|/* IOP message status codes */
DECL|macro|IOP_MSGSTATUS_UNUSED
mdefine_line|#define IOP_MSGSTATUS_UNUSED&t;0&t;/* Unusued message structure       */
DECL|macro|IOP_MSGSTATUS_WAITING
mdefine_line|#define IOP_MSGSTATUS_WAITING&t;1&t;/* waiting for channel             */
DECL|macro|IOP_MSGSTATUS_SENT
mdefine_line|#define IOP_MSGSTATUS_SENT&t;2&t;/* message sent, awaiting reply    */
DECL|macro|IOP_MSGSTATUS_COMPLETE
mdefine_line|#define IOP_MSGSTATUS_COMPLETE&t;3&t;/* message complete and reply rcvd */
DECL|macro|IOP_MSGSTATUS_UNSOL
mdefine_line|#define IOP_MSGSTATUS_UNSOL&t;6&t;/* message is unsolicited          */
multiline_comment|/* IOP memory addresses of the members of the mac_iop_kernel structure. */
DECL|macro|IOP_ADDR_MAX_SEND_CHAN
mdefine_line|#define IOP_ADDR_MAX_SEND_CHAN&t;0x0200
DECL|macro|IOP_ADDR_SEND_STATE
mdefine_line|#define IOP_ADDR_SEND_STATE&t;0x0201
DECL|macro|IOP_ADDR_PATCH_CTRL
mdefine_line|#define IOP_ADDR_PATCH_CTRL&t;0x021F
DECL|macro|IOP_ADDR_SEND_MSG
mdefine_line|#define IOP_ADDR_SEND_MSG&t;0x0220
DECL|macro|IOP_ADDR_MAX_RECV_CHAN
mdefine_line|#define IOP_ADDR_MAX_RECV_CHAN&t;0x0300
DECL|macro|IOP_ADDR_RECV_STATE
mdefine_line|#define IOP_ADDR_RECV_STATE&t;0x0301
DECL|macro|IOP_ADDR_ALIVE
mdefine_line|#define IOP_ADDR_ALIVE&t;&t;0x031F
DECL|macro|IOP_ADDR_RECV_MSG
mdefine_line|#define IOP_ADDR_RECV_MSG&t;0x0320
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * IOP Control registers, staggered because in usual Apple style they were&n; * too lazy to decode the A0 bit. This structure is assumed to begin at&n; * one of the xxx_IOP_BASE addresses given above.&n; */
DECL|struct|mac_iop
r_struct
id|mac_iop
(brace
DECL|member|ram_addr_hi
id|__u8
id|ram_addr_hi
suffix:semicolon
multiline_comment|/* shared RAM address hi byte */
DECL|member|pad0
id|__u8
id|pad0
suffix:semicolon
DECL|member|ram_addr_lo
id|__u8
id|ram_addr_lo
suffix:semicolon
multiline_comment|/* shared RAM address lo byte */
DECL|member|pad1
id|__u8
id|pad1
suffix:semicolon
DECL|member|status_ctrl
id|__u8
id|status_ctrl
suffix:semicolon
multiline_comment|/* status/control register */
DECL|member|pad2
id|__u8
id|pad2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ram_data
id|__u8
id|ram_data
suffix:semicolon
multiline_comment|/* RAM data byte at ramhi/lo */
DECL|member|pad3
id|__u8
id|pad3
(braket
l_int|23
)braket
suffix:semicolon
multiline_comment|/* Bypass-mode hardware access registers */
r_union
(brace
r_struct
(brace
multiline_comment|/* SCC registers */
DECL|member|sccb_cmd
id|__u8
id|sccb_cmd
suffix:semicolon
multiline_comment|/* SCC B command reg */
DECL|member|pad4
id|__u8
id|pad4
suffix:semicolon
DECL|member|scca_cmd
id|__u8
id|scca_cmd
suffix:semicolon
multiline_comment|/* SCC A command reg */
DECL|member|pad5
id|__u8
id|pad5
suffix:semicolon
DECL|member|sccb_data
id|__u8
id|sccb_data
suffix:semicolon
multiline_comment|/* SCC B data */
DECL|member|pad6
id|__u8
id|pad6
suffix:semicolon
DECL|member|scca_data
id|__u8
id|scca_data
suffix:semicolon
multiline_comment|/* SCC A data */
DECL|member|scc_regs
)brace
id|scc_regs
suffix:semicolon
r_struct
(brace
multiline_comment|/* ISM registers */
DECL|member|wdata
id|__u8
id|wdata
suffix:semicolon
multiline_comment|/* write a data byte */
DECL|member|pad7
id|__u8
id|pad7
suffix:semicolon
DECL|member|wmark
id|__u8
id|wmark
suffix:semicolon
multiline_comment|/* write a mark byte */
DECL|member|pad8
id|__u8
id|pad8
suffix:semicolon
DECL|member|wcrc
id|__u8
id|wcrc
suffix:semicolon
multiline_comment|/* write 2-byte crc to disk */
DECL|member|pad9
id|__u8
id|pad9
suffix:semicolon
DECL|member|wparams
id|__u8
id|wparams
suffix:semicolon
multiline_comment|/* write the param regs */
DECL|member|pad10
id|__u8
id|pad10
suffix:semicolon
DECL|member|wphase
id|__u8
id|wphase
suffix:semicolon
multiline_comment|/* write the phase states &amp; dirs */
DECL|member|pad11
id|__u8
id|pad11
suffix:semicolon
DECL|member|wsetup
id|__u8
id|wsetup
suffix:semicolon
multiline_comment|/* write the setup register */
DECL|member|pad12
id|__u8
id|pad12
suffix:semicolon
DECL|member|wzeroes
id|__u8
id|wzeroes
suffix:semicolon
multiline_comment|/* mode reg: 1&squot;s clr bits, 0&squot;s are x */
DECL|member|pad13
id|__u8
id|pad13
suffix:semicolon
DECL|member|wones
id|__u8
id|wones
suffix:semicolon
multiline_comment|/* mode reg: 1&squot;s set bits, 0&squot;s are x */
DECL|member|pad14
id|__u8
id|pad14
suffix:semicolon
DECL|member|rdata
id|__u8
id|rdata
suffix:semicolon
multiline_comment|/* read a data byte */
DECL|member|pad15
id|__u8
id|pad15
suffix:semicolon
DECL|member|rmark
id|__u8
id|rmark
suffix:semicolon
multiline_comment|/* read a mark byte */
DECL|member|pad16
id|__u8
id|pad16
suffix:semicolon
DECL|member|rerror
id|__u8
id|rerror
suffix:semicolon
multiline_comment|/* read the error register */
DECL|member|pad17
id|__u8
id|pad17
suffix:semicolon
DECL|member|rparams
id|__u8
id|rparams
suffix:semicolon
multiline_comment|/* read the param regs */
DECL|member|pad18
id|__u8
id|pad18
suffix:semicolon
DECL|member|rphase
id|__u8
id|rphase
suffix:semicolon
multiline_comment|/* read the phase states &amp; dirs */
DECL|member|pad19
id|__u8
id|pad19
suffix:semicolon
DECL|member|rsetup
id|__u8
id|rsetup
suffix:semicolon
multiline_comment|/* read the setup register */
DECL|member|pad20
id|__u8
id|pad20
suffix:semicolon
DECL|member|rmode
id|__u8
id|rmode
suffix:semicolon
multiline_comment|/* read the mode register */
DECL|member|pad21
id|__u8
id|pad21
suffix:semicolon
DECL|member|rhandshake
id|__u8
id|rhandshake
suffix:semicolon
multiline_comment|/* read the handshake register */
DECL|member|ism_regs
)brace
id|ism_regs
suffix:semicolon
DECL|member|b
)brace
id|b
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This structure is used to track IOP messages in the Linux kernel */
DECL|struct|iop_msg
r_struct
id|iop_msg
(brace
DECL|member|next
r_struct
id|iop_msg
op_star
id|next
suffix:semicolon
multiline_comment|/* next message in queue or NULL     */
DECL|member|iop_num
id|uint
id|iop_num
suffix:semicolon
multiline_comment|/* IOP number                        */
DECL|member|channel
id|uint
id|channel
suffix:semicolon
multiline_comment|/* channel number                    */
DECL|member|caller_priv
r_void
op_star
id|caller_priv
suffix:semicolon
multiline_comment|/* caller private data               */
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* status of this message            */
DECL|member|message
id|__u8
id|message
(braket
id|IOP_MSG_LEN
)braket
suffix:semicolon
multiline_comment|/* the message being sent/received   */
DECL|member|reply
id|__u8
id|reply
(braket
id|IOP_MSG_LEN
)braket
suffix:semicolon
multiline_comment|/* the reply to the message          */
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_struct
id|iop_msg
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/* function to call when reply recvd */
)brace
suffix:semicolon
r_extern
r_int
id|iop_scc_present
comma
id|iop_ism_present
suffix:semicolon
r_extern
r_int
id|iop_listen
c_func
(paren
id|uint
comma
id|uint
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_struct
id|iop_msg
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|iop_send_message
c_func
(paren
id|uint
comma
id|uint
comma
r_void
op_star
comma
id|uint
comma
id|__u8
op_star
comma
r_void
(paren
op_star
)paren
(paren
r_struct
id|iop_msg
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
suffix:semicolon
r_extern
r_void
id|iop_complete_message
c_func
(paren
r_struct
id|iop_msg
op_star
)paren
suffix:semicolon
r_extern
r_void
id|iop_upload_code
c_func
(paren
id|uint
comma
id|__u8
op_star
comma
id|uint
comma
id|__u16
)paren
suffix:semicolon
r_extern
r_void
id|iop_download_code
c_func
(paren
id|uint
comma
id|__u8
op_star
comma
id|uint
comma
id|__u16
)paren
suffix:semicolon
r_extern
id|__u8
op_star
id|iop_compare_code
c_func
(paren
id|uint
comma
id|__u8
op_star
comma
id|uint
comma
id|__u16
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
eof
