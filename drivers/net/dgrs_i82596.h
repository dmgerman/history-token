multiline_comment|/*&n; *&t;i82596 ethernet controller bits and structures (little endian)&n; *&n; *&t;$Id: i82596.h,v 1.8 1996/09/03 11:19:03 rick Exp $&n; */
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;PORT commands (p. 4-20).  The least significant nibble is one&t;*/
multiline_comment|/*&t;of these commands, the rest of the command is a memory address&t;*/
multiline_comment|/*&t;aligned on a 16 byte boundary.  Note that port commands must&t;*/
multiline_comment|/*&t;be written to the PORT address and the PORT address+2 with two&t;*/
multiline_comment|/*&t;halfword writes.  Write the LSH first to PORT, then the MSH to&t;*/
multiline_comment|/*&t;PORT+2.  Blame Intel.&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|I596_PORT_RESET
mdefine_line|#define&t;I596_PORT_RESET&t;&t;0x0&t;/* Reset. Wait 5 SysClks &amp; 10 TxClks */
DECL|macro|I596_PORT_SELFTEST
mdefine_line|#define&t;I596_PORT_SELFTEST&t;0x1&t;/* Do a selftest */
DECL|macro|I596_PORT_SCP_ADDR
mdefine_line|#define&t;I596_PORT_SCP_ADDR&t;0x2&t;/* Set new SCP address */
DECL|macro|I596_PORT_DUMP
mdefine_line|#define&t;I596_PORT_DUMP&t;&t;0x3&t;/* Dump internal data structures */
multiline_comment|/*&n; *&t;I596_ST:&t;Selftest results (p. 4-21)&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|signature
id|ulong
id|signature
suffix:semicolon
multiline_comment|/* ROM checksum */
DECL|member|result
id|ulong
id|result
suffix:semicolon
multiline_comment|/* Selftest results: non-zero is a failure */
DECL|typedef|I596_ST
)brace
id|I596_ST
suffix:semicolon
DECL|macro|I596_ST_SELFTEST_FAIL
mdefine_line|#define&t;I596_ST_SELFTEST_FAIL&t;0x1000&t;/* Selftest Failed */
DECL|macro|I596_ST_DIAGNOSE_FAIL
mdefine_line|#define&t;I596_ST_DIAGNOSE_FAIL&t;0x0020&t;/* Diagnose Failed */
DECL|macro|I596_ST_BUSTIMER_FAIL
mdefine_line|#define&t;I596_ST_BUSTIMER_FAIL&t;0x0010&t;/* Bus Timer Failed */
DECL|macro|I596_ST_REGISTER_FAIL
mdefine_line|#define&t;I596_ST_REGISTER_FAIL&t;0x0008&t;/* Register Failed */
DECL|macro|I596_ST_ROM_FAIL
mdefine_line|#define&t;I596_ST_ROM_FAIL&t;0x0004&t;/* ROM Failed */
multiline_comment|/*&n; *&t;I596_DUMP:&t;Dump results&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|dump
id|ulong
id|dump
(braket
l_int|77
)braket
suffix:semicolon
DECL|typedef|I596_DUMP
)brace
id|I596_DUMP
suffix:semicolon
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;I596_TBD:&t;Transmit Buffer Descriptor (p. 4-59)&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|struct|_I596_TBD
r_typedef
r_volatile
r_struct
id|_I596_TBD
(brace
DECL|member|count
id|ulong
id|count
suffix:semicolon
DECL|member|next
id|vol
r_struct
id|_I596_TBD
op_star
id|next
suffix:semicolon
DECL|member|buf
id|uchar
op_star
id|buf
suffix:semicolon
DECL|member|unused1
id|ushort
id|unused1
suffix:semicolon
DECL|member|unused2
id|ushort
id|unused2
suffix:semicolon
DECL|typedef|I596_TBD
)brace
id|I596_TBD
suffix:semicolon
DECL|macro|I596_TBD_NOLINK
mdefine_line|#define&t;I596_TBD_NOLINK&t;&t;((I596_TBD *) 0xffffffff)
DECL|macro|I596_TBD_EOF
mdefine_line|#define&t;I596_TBD_EOF&t;&t;0x8000
DECL|macro|I596_TBD_COUNT_MASK
mdefine_line|#define I596_TBD_COUNT_MASK&t;0x3fff
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;I596_TFD:&t;Transmit Frame Descriptor (p. 4-56)&t;&t;*/
multiline_comment|/*&t;&t;&t;a.k.a. I596_CB_XMIT&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
r_typedef
r_volatile
r_struct
(brace
DECL|member|status
id|ushort
id|status
suffix:semicolon
DECL|member|cmd
id|ushort
id|cmd
suffix:semicolon
DECL|member|next
r_union
id|_I596_CB
op_star
id|next
suffix:semicolon
DECL|member|tbdp
id|I596_TBD
op_star
id|tbdp
suffix:semicolon
DECL|member|count
id|ulong
id|count
suffix:semicolon
multiline_comment|/* for speed */
multiline_comment|/* Application defined data follows structure... */
macro_line|#if 0&t;/* We don&squot;t use these intel defined ones */
id|uchar
id|addr
(braket
l_int|6
)braket
suffix:semicolon
id|ushort
id|len
suffix:semicolon
id|uchar
id|data
(braket
l_int|1
)braket
suffix:semicolon
macro_line|#else
DECL|member|dstchan
id|ulong
id|dstchan
suffix:semicolon
multiline_comment|/* Used by multi-NIC mode */
macro_line|#endif
DECL|typedef|I596_TFD
)brace
id|I596_TFD
suffix:semicolon
DECL|macro|I596_TFD_NOCRC
mdefine_line|#define&t;I596_TFD_NOCRC&t;0x0010&t;/* cmd: No CRC insertion */
DECL|macro|I596_TFD_FLEX
mdefine_line|#define&t;I596_TFD_FLEX&t;0x0008&t;/* cmd: Flexible mode */
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;I596_RBD:&t;Receive Buffer Descriptor (p. 4-84)&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|struct|_I596_RBD
r_typedef
r_volatile
r_struct
id|_I596_RBD
(brace
macro_line|#if INTEL_RETENTIVE
DECL|member|count
id|ushort
id|count
suffix:semicolon
multiline_comment|/* Length of data in buf */
DECL|member|offset
id|ushort
id|offset
suffix:semicolon
macro_line|#else
id|ulong
id|count
suffix:semicolon
multiline_comment|/* Length of data in buf */
macro_line|#endif
DECL|member|next
id|vol
r_struct
id|_I596_RBD
op_star
id|next
suffix:semicolon
multiline_comment|/* Next buffer descriptor in list */
DECL|member|buf
id|uchar
op_star
id|buf
suffix:semicolon
multiline_comment|/* Data buffer */
macro_line|#if INTEL_RETENTIVE
DECL|member|size
id|ushort
id|size
suffix:semicolon
multiline_comment|/* Size of buf (constant) */
DECL|member|zero
id|ushort
id|zero
suffix:semicolon
macro_line|#else
DECL|member|size
id|ulong
id|size
suffix:semicolon
multiline_comment|/* Size of buf (constant) */
macro_line|#endif
multiline_comment|/* Application defined data follows structure... */
DECL|member|chan
id|uchar
id|chan
suffix:semicolon
DECL|member|refcnt
id|uchar
id|refcnt
suffix:semicolon
DECL|member|len
id|ushort
id|len
suffix:semicolon
DECL|typedef|I596_RBD
)brace
id|I596_RBD
suffix:semicolon
DECL|macro|I596_RBD_NOLINK
mdefine_line|#define&t;I596_RBD_NOLINK&t;&t;((I596_RBD *) 0xffffffff)
DECL|macro|I596_RBD_EOF
mdefine_line|#define&t;I596_RBD_EOF&t;&t;0x8000&t;/* This is last buffer in a frame */
DECL|macro|I596_RBD_F
mdefine_line|#define&t;I596_RBD_F&t;&t;0x4000&t;/* The actual count is valid */
DECL|macro|I596_RBD_EL
mdefine_line|#define&t;I596_RBD_EL&t;&t;0x8000&t;/* Last buffer in list */
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;I596_RFD:&t;Receive Frame Descriptor (p. 4-79)&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|struct|_I596_RFD
r_typedef
r_volatile
r_struct
id|_I596_RFD
(brace
DECL|member|status
id|ushort
id|status
suffix:semicolon
DECL|member|cmd
id|ushort
id|cmd
suffix:semicolon
DECL|member|next
id|vol
r_struct
id|_I596_RFD
op_star
id|next
suffix:semicolon
DECL|member|rbdp
id|vol
r_struct
id|_I596_RBD
op_star
id|rbdp
suffix:semicolon
DECL|member|count
id|ushort
id|count
suffix:semicolon
multiline_comment|/* Len of data in RFD: always 0 */
DECL|member|size
id|ushort
id|size
suffix:semicolon
multiline_comment|/* Size of RFD buffer: always 0 */
multiline_comment|/* Application defined data follows structure... */
macro_line|#&t;if 0&t;/* We don&squot;t use these intel defined ones */
id|uchar
id|addr
(braket
l_int|6
)braket
suffix:semicolon
id|ushort
id|len
suffix:semicolon
id|uchar
id|data
(braket
l_int|1
)braket
suffix:semicolon
macro_line|#&t;else
DECL|member|dstchan
id|ulong
id|dstchan
suffix:semicolon
multiline_comment|/* Used by multi-nic mode */
macro_line|#&t;endif
DECL|typedef|I596_RFD
)brace
id|I596_RFD
suffix:semicolon
DECL|macro|I596_RFD_C
mdefine_line|#define&t;I596_RFD_C&t;&t;0x8000&t;/* status: frame complete */
DECL|macro|I596_RFD_B
mdefine_line|#define&t;I596_RFD_B&t;&t;0x4000&t;/* status: frame busy or waiting */
DECL|macro|I596_RFD_OK
mdefine_line|#define&t;I596_RFD_OK&t;&t;0x2000&t;/* status: frame OK */
DECL|macro|I596_RFD_ERR_LENGTH
mdefine_line|#define&t;I596_RFD_ERR_LENGTH&t;0x1000&t;/* status: length error */
DECL|macro|I596_RFD_ERR_CRC
mdefine_line|#define&t;I596_RFD_ERR_CRC&t;0x0800&t;/* status: CRC error */
DECL|macro|I596_RFD_ERR_ALIGN
mdefine_line|#define&t;I596_RFD_ERR_ALIGN&t;0x0400&t;/* status: alignment error */
DECL|macro|I596_RFD_ERR_NOBUFS
mdefine_line|#define&t;I596_RFD_ERR_NOBUFS&t;0x0200&t;/* status: resource error */
DECL|macro|I596_RFD_ERR_DMA
mdefine_line|#define&t;I596_RFD_ERR_DMA&t;0x0100&t;/* status: DMA error */
DECL|macro|I596_RFD_ERR_SHORT
mdefine_line|#define&t;I596_RFD_ERR_SHORT&t;0x0080&t;/* status: too short error */
DECL|macro|I596_RFD_NOMATCH
mdefine_line|#define&t;I596_RFD_NOMATCH&t;0x0002&t;/* status: IA was not matched */
DECL|macro|I596_RFD_COLLISION
mdefine_line|#define&t;I596_RFD_COLLISION&t;0x0001&t;/* status: collision during receive */
DECL|macro|I596_RFD_EL
mdefine_line|#define&t;I596_RFD_EL&t;&t;0x8000&t;/* cmd: end of RFD list */
DECL|macro|I596_RFD_FLEX
mdefine_line|#define&t;I596_RFD_FLEX&t;&t;0x0008&t;/* cmd: Flexible mode */
DECL|macro|I596_RFD_EOF
mdefine_line|#define&t;I596_RFD_EOF&t;&t;0x8000&t;/* count: last buffer in the frame */
DECL|macro|I596_RFD_F
mdefine_line|#define&t;I596_RFD_F&t;&t;0x4000&t;/* count: The actual count is valid */
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Commands&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
multiline_comment|/* values for cmd halfword in all the structs below */
DECL|macro|I596_CB_CMD
mdefine_line|#define I596_CB_CMD&t;&t;0x07&t;/* CB COMMANDS */
DECL|macro|I596_CB_CMD_NOP
mdefine_line|#define I596_CB_CMD_NOP&t;&t;0
DECL|macro|I596_CB_CMD_IA
mdefine_line|#define I596_CB_CMD_IA&t;&t;1
DECL|macro|I596_CB_CMD_CONF
mdefine_line|#define I596_CB_CMD_CONF&t;2
DECL|macro|I596_CB_CMD_MCAST
mdefine_line|#define I596_CB_CMD_MCAST&t;3
DECL|macro|I596_CB_CMD_XMIT
mdefine_line|#define I596_CB_CMD_XMIT&t;4
DECL|macro|I596_CB_CMD_TDR
mdefine_line|#define I596_CB_CMD_TDR&t;&t;5
DECL|macro|I596_CB_CMD_DUMP
mdefine_line|#define I596_CB_CMD_DUMP&t;6
DECL|macro|I596_CB_CMD_DIAG
mdefine_line|#define I596_CB_CMD_DIAG&t;7
DECL|macro|I596_CB_CMD_EL
mdefine_line|#define&t;I596_CB_CMD_EL&t;&t;0x8000&t;/* CB is last in linked list */
DECL|macro|I596_CB_CMD_S
mdefine_line|#define&t;I596_CB_CMD_S&t;&t;0x4000&t;/* Suspend after execution */
DECL|macro|I596_CB_CMD_I
mdefine_line|#define&t;I596_CB_CMD_I&t;&t;0x2000&t;/* cause interrupt */
multiline_comment|/* values for the status halfword in all the struct below */
DECL|macro|I596_CB_STATUS
mdefine_line|#define&t;I596_CB_STATUS&t;&t;0xF000&t;/* All four status bits */
DECL|macro|I596_CB_STATUS_C
mdefine_line|#define&t;I596_CB_STATUS_C&t;0x8000&t;/* Command complete */
DECL|macro|I596_CB_STATUS_B
mdefine_line|#define&t;I596_CB_STATUS_B&t;0x4000&t;/* Command busy executing */
DECL|macro|I596_CB_STATUS_C_OR_B
mdefine_line|#define&t;I596_CB_STATUS_C_OR_B&t;0xC000&t;/* Command complete or busy */
DECL|macro|I596_CB_STATUS_OK
mdefine_line|#define&t;I596_CB_STATUS_OK&t;0x2000&t;/* Command complete, no errors */
DECL|macro|I596_CB_STATUS_A
mdefine_line|#define&t;I596_CB_STATUS_A&t;0x1000&t;/* Command busy executing */
DECL|macro|I596_CB_NOLINK
mdefine_line|#define&t;I596_CB_NOLINK&t;&t;((I596_CB *) 0xffffffff)
multiline_comment|/*&n; *&t;I596_CB_NOP:&t;NOP Command (p. 4-34)&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|status
id|ushort
id|status
suffix:semicolon
DECL|member|cmd
id|ushort
id|cmd
suffix:semicolon
DECL|member|next
r_union
id|_I596_CB
op_star
id|next
suffix:semicolon
DECL|typedef|I596_CB_NOP
)brace
id|I596_CB_NOP
suffix:semicolon
multiline_comment|/*&n; *&t;Same as above, but command and status in one ulong for speed&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|csr
id|ulong
id|csr
suffix:semicolon
DECL|member|next
r_union
id|_I596_CB
op_star
id|next
suffix:semicolon
DECL|typedef|I596_CB_FAST
)brace
id|I596_CB_FAST
suffix:semicolon
DECL|macro|FASTs
mdefine_line|#define&t;FASTs(X)&t;(X)
DECL|macro|FASTc
mdefine_line|#define&t;FASTc(X)&t;((X)&lt;&lt;16)
multiline_comment|/*&n; *&t;I596_CB_IA:&t;Individual (MAC) Address Command (p. 4-35)&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|status
id|ushort
id|status
suffix:semicolon
DECL|member|cmd
id|ushort
id|cmd
suffix:semicolon
DECL|member|next
r_union
id|_I596_CB
op_star
id|next
suffix:semicolon
DECL|member|addr
id|uchar
id|addr
(braket
l_int|6
)braket
suffix:semicolon
DECL|typedef|I596_CB_IA
)brace
id|I596_CB_IA
suffix:semicolon
multiline_comment|/*&n; *&t;I596_CB_CONF:&t;Configure Command (p. 4-37)&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|status
id|ushort
id|status
suffix:semicolon
DECL|member|cmd
id|ushort
id|cmd
suffix:semicolon
DECL|member|next
r_union
id|_I596_CB
op_star
id|next
suffix:semicolon
DECL|member|conf
id|uchar
id|conf
(braket
l_int|14
)braket
suffix:semicolon
DECL|typedef|I596_CB_CONF
)brace
id|I596_CB_CONF
suffix:semicolon
DECL|macro|I596_CONF0_P
mdefine_line|#define&t;I596_CONF0_P&t;&t;0x80&t;/* Enable RBD Prefetch Bit */
DECL|macro|I596_CONF0_COUNT
mdefine_line|#define&t;I596_CONF0_COUNT&t;14&t;/* Count of configuration bytes */
DECL|macro|I596_CONF1_MON_OFF
mdefine_line|#define&t;I596_CONF1_MON_OFF&t;0xC0&t;/* Monitor mode: Monitor off */
DECL|macro|I596_CONF1_MON_ON
mdefine_line|#define&t;I596_CONF1_MON_ON&t;0x80&t;/* Monitor mode: Monitor on */
DECL|macro|I596_CONF1_TxFIFO
mdefine_line|#define&t;I596_CONF1_TxFIFO(W)&t;(W)&t;/* TxFIFO trigger, in words */
DECL|macro|I596_CONF2_SAVEBF
mdefine_line|#define&t;I596_CONF2_SAVEBF&t;0x80&t;/* Save bad frames */
DECL|macro|I596_CONF3_ADDRLEN
mdefine_line|#define&t;I596_CONF3_ADDRLEN(B)&t;(B)&t;/* Address length */
DECL|macro|I596_CONF3_NOSRCINSERT
mdefine_line|#define&t;I596_CONF3_NOSRCINSERT&t;0x08&t;/* Do not insert source address */
DECL|macro|I596_CONF3_PREAMBLE8
mdefine_line|#define&t;I596_CONF3_PREAMBLE8&t;0x20&t;/* 8 byte preamble */
DECL|macro|I596_CONF3_LOOPOFF
mdefine_line|#define&t;I596_CONF3_LOOPOFF&t;0x00&t;/* Loopback: Off */
DECL|macro|I596_CONF3_LOOPINT
mdefine_line|#define&t;I596_CONF3_LOOPINT&t;0x40&t;/* Loopback: internal */
DECL|macro|I596_CONF3_LOOPEXT
mdefine_line|#define&t;I596_CONF3_LOOPEXT&t;0xC0&t;/* Loopback: external */
DECL|macro|I596_CONF4_LINPRI
mdefine_line|#define&t;I596_CONF4_LINPRI(ST)&t;(ST)&t;/* Linear priority: slot times */
DECL|macro|I596_CONF4_EXPPRI
mdefine_line|#define&t;I596_CONF4_EXPPRI(ST)&t;(ST)&t;/* Exponential priority: slot times */
DECL|macro|I596_CONF4_IEEE_BOM
mdefine_line|#define&t;I596_CONF4_IEEE_BOM&t;0&t;/* IEEE 802.3 backoff method */
DECL|macro|I596_CONF5_IFS
mdefine_line|#define&t;I596_CONF5_IFS(X)&t;(X)&t;/* Interframe spacing in clocks */
DECL|macro|I596_CONF6_ST_LOW
mdefine_line|#define&t;I596_CONF6_ST_LOW(X)&t;(X&amp;255)&t;/* Slot time, low byte */
DECL|macro|I596_CONF7_ST_HI
mdefine_line|#define&t;I596_CONF7_ST_HI(X)&t;(X&gt;&gt;8)&t;/* Slot time, high bits */
DECL|macro|I596_CONF7_RETRY
mdefine_line|#define&t;I596_CONF7_RETRY(X)&t;(X&lt;&lt;4)&t;/* Max retry number */
DECL|macro|I596_CONF8_PROMISC
mdefine_line|#define&t;I596_CONF8_PROMISC&t;0x01&t;/* Rcv all frames */
DECL|macro|I596_CONF8_NOBROAD
mdefine_line|#define&t;I596_CONF8_NOBROAD&t;0x02
DECL|macro|I596_CONF8_MANCHESTER
mdefine_line|#define&t;I596_CONF8_MANCHESTER&t;0x04
DECL|macro|I596_CONF8_TxNOCRS
mdefine_line|#define&t;I596_CONF8_TxNOCRS&t;0x08
DECL|macro|I596_CONF8_NOCRC
mdefine_line|#define&t;I596_CONF8_NOCRC&t;0x10
DECL|macro|I596_CONF8_CRC_CCITT
mdefine_line|#define&t;I596_CONF8_CRC_CCITT&t;0x20
DECL|macro|I596_CONF8_BITSTUFFING
mdefine_line|#define&t;I596_CONF8_BITSTUFFING&t;0x40
DECL|macro|I596_CONF8_PADDING
mdefine_line|#define&t;I596_CONF8_PADDING&t;0x80
DECL|macro|I596_CONF9_CSFILTER
mdefine_line|#define&t;I596_CONF9_CSFILTER(X)&t;(X)
DECL|macro|I596_CONF9_CSINT
mdefine_line|#define&t;I596_CONF9_CSINT(X)&t;0x08
DECL|macro|I596_CONF9_CDFILTER
mdefine_line|#define&t;I596_CONF9_CDFILTER(X)&t;(X&lt;&lt;4)
DECL|macro|I596_CONF9_CDINT
mdefine_line|#define&t;I596_CONF9_CDINT(X)&t;0x80
DECL|macro|I596_CONF10_MINLEN
mdefine_line|#define&t;I596_CONF10_MINLEN(X)&t;(X)&t;/* Minimum frame length */
DECL|macro|I596_CONF11_PRECRS_
mdefine_line|#define&t;I596_CONF11_PRECRS_&t;0x01&t;/* Preamble before carrier sense */
DECL|macro|I596_CONF11_LNGFLD_
mdefine_line|#define&t;I596_CONF11_LNGFLD_&t;0x02&t;/* Padding in End of Carrier */
DECL|macro|I596_CONF11_CRCINM_
mdefine_line|#define&t;I596_CONF11_CRCINM_&t;0x04&t;/* CRC in memory */
DECL|macro|I596_CONF11_AUTOTX
mdefine_line|#define&t;I596_CONF11_AUTOTX&t;0x08&t;/* Auto retransmit */
DECL|macro|I596_CONF11_CSBSAC_
mdefine_line|#define&t;I596_CONF11_CSBSAC_&t;0x10&t;/* Collision detect by src addr cmp. */
DECL|macro|I596_CONF11_MCALL_
mdefine_line|#define&t;I596_CONF11_MCALL_&t;0x20&t;/* Multicast all */
DECL|macro|I596_CONF13_RESERVED
mdefine_line|#define I596_CONF13_RESERVED&t;0x3f&t;/* Reserved: must be ones */
DECL|macro|I596_CONF13_MULTIA
mdefine_line|#define I596_CONF13_MULTIA&t;0x40&t;/* Enable multiple addr. reception */
DECL|macro|I596_CONF13_DISBOF
mdefine_line|#define I596_CONF13_DISBOF&t;0x80&t;/* Disable backoff algorithm */
multiline_comment|/*&n; *&t;I596_CB_MCAST:&t;Multicast-Setup Command (p. 4-54)&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|status
id|ushort
id|status
suffix:semicolon
DECL|member|cmd
id|ushort
id|cmd
suffix:semicolon
DECL|member|next
r_union
id|_I596_CB
op_star
id|next
suffix:semicolon
DECL|member|count
id|ushort
id|count
suffix:semicolon
multiline_comment|/* Number of 6-byte addrs that follow */
DECL|member|addr
id|uchar
id|addr
(braket
l_int|6
)braket
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|I596_CB_MCAST
)brace
id|I596_CB_MCAST
suffix:semicolon
multiline_comment|/*&n; *&t;I596_CB_XMIT:&t;Transmit Command (p. 4-56)&n; */
DECL|typedef|I596_CB_XMIT
r_typedef
id|I596_TFD
id|I596_CB_XMIT
suffix:semicolon
DECL|macro|I596_CB_XMIT_NOCRC
mdefine_line|#define&t;I596_CB_XMIT_NOCRC&t;0x0010&t;/* cmd: No CRC insertion */
DECL|macro|I596_CB_XMIT_FLEX
mdefine_line|#define&t;I596_CB_XMIT_FLEX&t;0x0008&t;/* cmd: Flexible memory mode */
DECL|macro|I596_CB_XMIT_ERR_LATE
mdefine_line|#define&t;I596_CB_XMIT_ERR_LATE&t;0x0800&t;/* status: error: late collision */
DECL|macro|I596_CB_XMIT_ERR_NOCRS
mdefine_line|#define&t;I596_CB_XMIT_ERR_NOCRS&t;0x0400&t;/* status: error: no carriers sense */
DECL|macro|I596_CB_XMIT_ERR_NOCTS
mdefine_line|#define&t;I596_CB_XMIT_ERR_NOCTS&t;0x0200&t;/* status: error: loss of CTS */
DECL|macro|I596_CB_XMIT_ERR_UNDER
mdefine_line|#define&t;I596_CB_XMIT_ERR_UNDER&t;0x0100&t;/* status: error: DMA underrun */
DECL|macro|I596_CB_XMIT_ERR_MAXCOL
mdefine_line|#define&t;I596_CB_XMIT_ERR_MAXCOL&t;0x0020&t;/* status: error: maximum collisions */
DECL|macro|I596_CB_XMIT_COLLISIONS
mdefine_line|#define&t;I596_CB_XMIT_COLLISIONS&t;0x000f&t;/* status: number of collisions */
multiline_comment|/*&n; *&t;I596_CB_TDR:&t;Time Domain Reflectometry Command (p. 4-63)&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|status
id|ushort
id|status
suffix:semicolon
DECL|member|cmd
id|ushort
id|cmd
suffix:semicolon
DECL|member|next
r_union
id|_I596_CB
op_star
id|next
suffix:semicolon
DECL|member|time
id|ushort
id|time
suffix:semicolon
DECL|typedef|I596_CB_TDR
)brace
id|I596_CB_TDR
suffix:semicolon
multiline_comment|/*&n; *&t;I596_CB_DUMP:&t;Dump Command (p. 4-65)&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|status
id|ushort
id|status
suffix:semicolon
DECL|member|cmd
id|ushort
id|cmd
suffix:semicolon
DECL|member|next
r_union
id|_I596_CB
op_star
id|next
suffix:semicolon
DECL|member|buf
id|uchar
op_star
id|buf
suffix:semicolon
DECL|typedef|I596_CB_DUMP
)brace
id|I596_CB_DUMP
suffix:semicolon
multiline_comment|/*&n; *&t;I596_CB_DIAG:&t;Diagnose Command (p. 4-77)&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|status
id|ushort
id|status
suffix:semicolon
DECL|member|cmd
id|ushort
id|cmd
suffix:semicolon
DECL|member|next
r_union
id|_I596_CB
op_star
id|next
suffix:semicolon
DECL|typedef|I596_CB_DIAG
)brace
id|I596_CB_DIAG
suffix:semicolon
multiline_comment|/*&n; *&t;I596_CB:&t;Command Block&n; */
DECL|union|_I596_CB
r_typedef
r_union
id|_I596_CB
(brace
DECL|member|nop
id|I596_CB_NOP
id|nop
suffix:semicolon
DECL|member|ia
id|I596_CB_IA
id|ia
suffix:semicolon
DECL|member|conf
id|I596_CB_CONF
id|conf
suffix:semicolon
DECL|member|mcast
id|I596_CB_MCAST
id|mcast
suffix:semicolon
DECL|member|xmit
id|I596_CB_XMIT
id|xmit
suffix:semicolon
DECL|member|tdr
id|I596_CB_TDR
id|tdr
suffix:semicolon
DECL|member|dump
id|I596_CB_DUMP
id|dump
suffix:semicolon
DECL|member|diag
id|I596_CB_DIAG
id|diag
suffix:semicolon
multiline_comment|/* command and status in one ulong for speed... */
DECL|member|fast
id|I596_CB_FAST
id|fast
suffix:semicolon
DECL|typedef|I596_CB
)brace
id|I596_CB
suffix:semicolon
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;I596_SCB:&t;System Configuration Block (p. 4-26)&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
r_typedef
r_volatile
r_struct
(brace
DECL|member|status
r_volatile
id|ushort
id|status
suffix:semicolon
multiline_comment|/* Status word */
DECL|member|cmd
r_volatile
id|ushort
id|cmd
suffix:semicolon
multiline_comment|/* Command word */
DECL|member|cbp
id|I596_CB
op_star
id|cbp
suffix:semicolon
DECL|member|rfdp
id|I596_RFD
op_star
id|rfdp
suffix:semicolon
DECL|member|crc_errs
id|ulong
id|crc_errs
suffix:semicolon
DECL|member|align_errs
id|ulong
id|align_errs
suffix:semicolon
DECL|member|resource_errs
id|ulong
id|resource_errs
suffix:semicolon
DECL|member|overrun_errs
id|ulong
id|overrun_errs
suffix:semicolon
DECL|member|rcvcdt_errs
id|ulong
id|rcvcdt_errs
suffix:semicolon
DECL|member|short_errs
id|ulong
id|short_errs
suffix:semicolon
DECL|member|toff
id|ushort
id|toff
suffix:semicolon
DECL|member|ton
id|ushort
id|ton
suffix:semicolon
DECL|typedef|I596_SCB
)brace
id|I596_SCB
suffix:semicolon
multiline_comment|/* cmd halfword values */
DECL|macro|I596_SCB_ACK
mdefine_line|#define&t;I596_SCB_ACK&t;&t;0xF000&t;/* ACKNOWLEDGMENTS */
DECL|macro|I596_SCB_ACK_CX
mdefine_line|#define&t;I596_SCB_ACK_CX&t;&t;0x8000&t;/* Ack command completion */
DECL|macro|I596_SCB_ACK_FR
mdefine_line|#define&t;I596_SCB_ACK_FR&t;&t;0x4000&t;/* Ack received frame */
DECL|macro|I596_SCB_ACK_CNA
mdefine_line|#define&t;I596_SCB_ACK_CNA&t;0x2000&t;/* Ack command unit not active */
DECL|macro|I596_SCB_ACK_RNR
mdefine_line|#define&t;I596_SCB_ACK_RNR&t;0x1000&t;/* Ack rcv unit not ready */
DECL|macro|I596_SCB_ACK_ALL
mdefine_line|#define&t;I596_SCB_ACK_ALL&t;0xF000&t;/* Ack everything */
DECL|macro|I596_SCB_CUC
mdefine_line|#define&t;I596_SCB_CUC&t;&t;0x0700&t;/* COMMAND UNIT COMMANDS */
DECL|macro|I596_SCB_CUC_NOP
mdefine_line|#define&t;I596_SCB_CUC_NOP&t;0x0000&t;/* No operation */
DECL|macro|I596_SCB_CUC_START
mdefine_line|#define&t;I596_SCB_CUC_START&t;0x0100&t;/* Start execution of first CB */
DECL|macro|I596_SCB_CUC_RESUME
mdefine_line|#define&t;I596_SCB_CUC_RESUME&t;0x0200&t;/* Resume execution */
DECL|macro|I596_SCB_CUC_SUSPEND
mdefine_line|#define&t;I596_SCB_CUC_SUSPEND&t;0x0300&t;/* Suspend after current CB */
DECL|macro|I596_SCB_CUC_ABORT
mdefine_line|#define&t;I596_SCB_CUC_ABORT&t;0x0400&t;/* Abort current CB immediately */
DECL|macro|I596_SCB_CUC_LOAD
mdefine_line|#define&t;I596_SCB_CUC_LOAD&t;0x0500&t;/* Load Bus throttle timers */
DECL|macro|I596_SCB_CUC_LOADIMM
mdefine_line|#define&t;I596_SCB_CUC_LOADIMM&t;0x0600&t;/* Load Bus throttle timers, now */
DECL|macro|I596_SCB_RUC
mdefine_line|#define&t;I596_SCB_RUC&t;&t;0x0070&t;/* RECEIVE UNIT COMMANDS */
DECL|macro|I596_SCB_RUC_NOP
mdefine_line|#define&t;I596_SCB_RUC_NOP&t;0x0000&t;/* No operation */
DECL|macro|I596_SCB_RUC_START
mdefine_line|#define&t;I596_SCB_RUC_START&t;0x0010&t;/* Start reception */
DECL|macro|I596_SCB_RUC_RESUME
mdefine_line|#define&t;I596_SCB_RUC_RESUME&t;0x0020&t;/* Resume reception */
DECL|macro|I596_SCB_RUC_SUSPEND
mdefine_line|#define&t;I596_SCB_RUC_SUSPEND&t;0x0030&t;/* Suspend reception */
DECL|macro|I596_SCB_RUC_ABORT
mdefine_line|#define&t;I596_SCB_RUC_ABORT&t;0x0040&t;/* Abort reception */
DECL|macro|I596_SCB_RESET
mdefine_line|#define&t;I596_SCB_RESET&t;&t;0x0080&t;/* Hard reset chip */
multiline_comment|/* status halfword values */
DECL|macro|I596_SCB_STAT
mdefine_line|#define&t;I596_SCB_STAT&t;&t;0xF000&t;/* STATUS */
DECL|macro|I596_SCB_CX
mdefine_line|#define&t;I596_SCB_CX&t;&t;0x8000&t;/* command completion */
DECL|macro|I596_SCB_FR
mdefine_line|#define&t;I596_SCB_FR&t;&t;0x4000&t;/* received frame */
DECL|macro|I596_SCB_CNA
mdefine_line|#define&t;I596_SCB_CNA&t;&t;0x2000&t;/* command unit not active */
DECL|macro|I596_SCB_RNR
mdefine_line|#define&t;I596_SCB_RNR&t;&t;0x1000&t;/* rcv unit not ready */
DECL|macro|I596_SCB_CUS
mdefine_line|#define&t;I596_SCB_CUS&t;&t;0x0700&t;/* COMMAND UNIT STATUS */
DECL|macro|I596_SCB_CUS_IDLE
mdefine_line|#define&t;I596_SCB_CUS_IDLE&t;0x0000&t;/* Idle */
DECL|macro|I596_SCB_CUS_SUSPENDED
mdefine_line|#define&t;I596_SCB_CUS_SUSPENDED&t;0x0100&t;/* Suspended */
DECL|macro|I596_SCB_CUS_ACTIVE
mdefine_line|#define&t;I596_SCB_CUS_ACTIVE&t;0x0200&t;/* Active */
DECL|macro|I596_SCB_RUS
mdefine_line|#define&t;I596_SCB_RUS&t;&t;0x00F0&t;/* RECEIVE UNIT STATUS */
DECL|macro|I596_SCB_RUS_IDLE
mdefine_line|#define&t;I596_SCB_RUS_IDLE&t;0x0000&t;/* Idle */
DECL|macro|I596_SCB_RUS_SUSPENDED
mdefine_line|#define&t;I596_SCB_RUS_SUSPENDED&t;0x0010&t;/* Suspended */
DECL|macro|I596_SCB_RUS_NORES
mdefine_line|#define&t;I596_SCB_RUS_NORES&t;0x0020&t;/* No Resources */
DECL|macro|I596_SCB_RUS_READY
mdefine_line|#define&t;I596_SCB_RUS_READY&t;0x0040&t;/* Ready */
DECL|macro|I596_SCB_RUS_NORBDS
mdefine_line|#define&t;I596_SCB_RUS_NORBDS&t;0x0080&t;/* No more RBDs modifier */
DECL|macro|I596_SCB_LOADED
mdefine_line|#define&t;I596_SCB_LOADED&t;&t;0x0008&t;/* Bus timers loaded */
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;I596_ISCP:&t;Intermediate System Configuration Ptr (p 4-26)&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
r_typedef
r_volatile
r_struct
(brace
DECL|member|busy
id|ulong
id|busy
suffix:semicolon
multiline_comment|/* Set to 1; I596 clears it when scbp is read */
DECL|member|scbp
id|I596_SCB
op_star
id|scbp
suffix:semicolon
DECL|typedef|I596_ISCP
)brace
id|I596_ISCP
suffix:semicolon
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;I596_SCP:&t;System Configuration Pointer (p. 4-23)&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
r_typedef
r_volatile
r_struct
(brace
DECL|member|sysbus
id|ulong
id|sysbus
suffix:semicolon
DECL|member|dummy
id|ulong
id|dummy
suffix:semicolon
DECL|member|iscpp
id|I596_ISCP
op_star
id|iscpp
suffix:semicolon
DECL|typedef|I596_SCP
)brace
id|I596_SCP
suffix:semicolon
multiline_comment|/* .sysbus values */
DECL|macro|I596_SCP_RESERVED
mdefine_line|#define I596_SCP_RESERVED&t;0x400000&t;/* Reserved bits must be set */
DECL|macro|I596_SCP_INTLOW
mdefine_line|#define I596_SCP_INTLOW&t;&t;0x200000&t;/* Intr. Polarity active low */
DECL|macro|I596_SCP_INTHIGH
mdefine_line|#define I596_SCP_INTHIGH&t;0&t;&t;/* Intr. Polarity active high */
DECL|macro|I596_SCP_LOCKDIS
mdefine_line|#define I596_SCP_LOCKDIS&t;0x100000&t;/* Lock Function disabled */
DECL|macro|I596_SCP_LOCKEN
mdefine_line|#define I596_SCP_LOCKEN&t;&t;0&t;&t;/* Lock Function enabled */
DECL|macro|I596_SCP_ETHROTTLE
mdefine_line|#define I596_SCP_ETHROTTLE&t;0x080000&t;/* External Bus Throttle */
DECL|macro|I596_SCP_ITHROTTLE
mdefine_line|#define I596_SCP_ITHROTTLE&t;0&t;&t;/* Internal Bus Throttle */
DECL|macro|I596_SCP_LINEAR
mdefine_line|#define I596_SCP_LINEAR&t;&t;0x040000&t;/* Linear Mode */
DECL|macro|I596_SCP_SEGMENTED
mdefine_line|#define I596_SCP_SEGMENTED&t;0x020000&t;/* Segmented Mode */
DECL|macro|I596_SCP_82586
mdefine_line|#define I596_SCP_82586&t;&t;0x000000&t;/* 82586 Mode */
eof
