multiline_comment|/*******************************************************&n;*  Define constants                                    *&n;*                                                      *&n;********************************************************/
DECL|macro|VERSION_CLAW_H
mdefine_line|#define VERSION_CLAW_H &quot;$Revision: 1.6 $&quot;
multiline_comment|/*-----------------------------------------------------*&n;*     CCW command codes for CLAW protocol              *&n;*------------------------------------------------------*/
DECL|macro|CCW_CLAW_CMD_WRITE
mdefine_line|#define CCW_CLAW_CMD_WRITE           0x01      /* write - not including link */
DECL|macro|CCW_CLAW_CMD_READ
mdefine_line|#define CCW_CLAW_CMD_READ            0x02      /* read */
DECL|macro|CCW_CLAW_CMD_NOP
mdefine_line|#define CCW_CLAW_CMD_NOP             0x03      /* NOP */
DECL|macro|CCW_CLAW_CMD_SENSE
mdefine_line|#define CCW_CLAW_CMD_SENSE           0x04      /* Sense */
DECL|macro|CCW_CLAW_CMD_SIGNAL_SMOD
mdefine_line|#define CCW_CLAW_CMD_SIGNAL_SMOD     0x05      /* Signal Status Modifier */
DECL|macro|CCW_CLAW_CMD_TIC
mdefine_line|#define CCW_CLAW_CMD_TIC             0x08      /* TIC */
DECL|macro|CCW_CLAW_CMD_READHEADER
mdefine_line|#define CCW_CLAW_CMD_READHEADER      0x12      /* read header data */
DECL|macro|CCW_CLAW_CMD_READFF
mdefine_line|#define CCW_CLAW_CMD_READFF          0x22      /* read an FF */
DECL|macro|CCW_CLAW_CMD_SENSEID
mdefine_line|#define CCW_CLAW_CMD_SENSEID         0xe4      /* Sense ID */
multiline_comment|/*-----------------------------------------------------*&n;*    CLAW Unique constants                             *&n;*------------------------------------------------------*/
DECL|macro|MORE_to_COME_FLAG
mdefine_line|#define MORE_to_COME_FLAG       0x04   /* OR with write CCW in case of m-t-c */
DECL|macro|CLAW_IDLE
mdefine_line|#define CLAW_IDLE               0x00   /* flag to indicate CLAW is idle */
DECL|macro|CLAW_BUSY
mdefine_line|#define CLAW_BUSY               0xff   /* flag to indicate CLAW is busy */
DECL|macro|CLAW_PENDING
mdefine_line|#define CLAW_PENDING            0x00   /* flag to indicate i/o is pending */
DECL|macro|CLAW_COMPLETE
mdefine_line|#define CLAW_COMPLETE           0xff   /* flag to indicate i/o completed */
multiline_comment|/*-----------------------------------------------------*&n;*     CLAW control comand code                         *&n;*------------------------------------------------------*/
DECL|macro|SYSTEM_VALIDATE_REQUEST
mdefine_line|#define SYSTEM_VALIDATE_REQUEST   0x01  /* System Validate request */
DECL|macro|SYSTEM_VALIDATE_RESPONSE
mdefine_line|#define SYSTEM_VALIDATE_RESPONSE  0x02  /* System Validate response */
DECL|macro|CONNECTION_REQUEST
mdefine_line|#define CONNECTION_REQUEST        0x21  /* Connection request */
DECL|macro|CONNECTION_RESPONSE
mdefine_line|#define CONNECTION_RESPONSE       0x22  /* Connection response */
DECL|macro|CONNECTION_CONFIRM
mdefine_line|#define CONNECTION_CONFIRM        0x23  /* Connection confirm */
DECL|macro|DISCONNECT
mdefine_line|#define DISCONNECT                0x24  /* Disconnect */
DECL|macro|CLAW_ERROR
mdefine_line|#define CLAW_ERROR                0x41  /* CLAW error message */
DECL|macro|CLAW_VERSION_ID
mdefine_line|#define CLAW_VERSION_ID           2     /* CLAW version ID */
multiline_comment|/*-----------------------------------------------------*&n;*  CLAW adater sense bytes                             *&n;*------------------------------------------------------*/
DECL|macro|CLAW_ADAPTER_SENSE_BYTE
mdefine_line|#define CLAW_ADAPTER_SENSE_BYTE 0x41   /* Stop command issued to adapter */
multiline_comment|/*-----------------------------------------------------*&n;*      CLAW control command return codes               *&n;*------------------------------------------------------*/
DECL|macro|CLAW_RC_NAME_MISMATCH
mdefine_line|#define CLAW_RC_NAME_MISMATCH       166  /*  names do not match */
DECL|macro|CLAW_RC_WRONG_VERSION
mdefine_line|#define CLAW_RC_WRONG_VERSION       167  /*  wrong CLAW version number */
DECL|macro|CLAW_RC_HOST_RCV_TOO_SMALL
mdefine_line|#define CLAW_RC_HOST_RCV_TOO_SMALL  180  /*  Host maximum receive is   */
multiline_comment|/*  less than Linux on zSeries*/
multiline_comment|/*  transmit size             */
multiline_comment|/*-----------------------------------------------------*&n;*      CLAW Constants application name                 *&n;*------------------------------------------------------*/
DECL|macro|HOST_APPL_NAME
mdefine_line|#define HOST_APPL_NAME          &quot;TCPIP   &quot;
DECL|macro|WS_APPL_NAME_IP_LINK
mdefine_line|#define WS_APPL_NAME_IP_LINK    &quot;TCPIP   &quot;
DECL|macro|WS_APPL_NAME_IP_NAME
mdefine_line|#define WS_APPL_NAME_IP_NAME&t;&quot;IP      &quot;
DECL|macro|WS_APPL_NAME_API_LINK
mdefine_line|#define WS_APPL_NAME_API_LINK   &quot;API     &quot;
DECL|macro|WS_APPL_NAME_PACKED
mdefine_line|#define WS_APPL_NAME_PACKED     &quot;PACKED  &quot;
DECL|macro|WS_NAME_NOT_DEF
mdefine_line|#define WS_NAME_NOT_DEF         &quot;NOT_DEF &quot;
DECL|macro|PACKING_ASK
mdefine_line|#define PACKING_ASK&t;&t;1
DECL|macro|PACK_SEND
mdefine_line|#define PACK_SEND&t;&t;2
DECL|macro|DO_PACKED
mdefine_line|#define DO_PACKED&t;&t;3
DECL|macro|MAX_ENVELOPE_SIZE
mdefine_line|#define MAX_ENVELOPE_SIZE       65536
DECL|macro|CLAW_DEFAULT_MTU_SIZE
mdefine_line|#define CLAW_DEFAULT_MTU_SIZE   4096
DECL|macro|DEF_PACK_BUFSIZE
mdefine_line|#define DEF_PACK_BUFSIZE&t;32768
DECL|macro|READ
mdefine_line|#define READ                    0
DECL|macro|WRITE
mdefine_line|#define WRITE                   1
DECL|macro|TB_TX
mdefine_line|#define TB_TX                   0          /* sk buffer handling in process  */
DECL|macro|TB_STOP
mdefine_line|#define TB_STOP                 1          /* network device stop in process */
DECL|macro|TB_RETRY
mdefine_line|#define TB_RETRY                2          /* retry in process               */
DECL|macro|TB_NOBUFFER
mdefine_line|#define TB_NOBUFFER             3          /* no buffer on free queue        */
DECL|macro|CLAW_MAX_LINK_ID
mdefine_line|#define CLAW_MAX_LINK_ID        1
DECL|macro|CLAW_MAX_DEV
mdefine_line|#define CLAW_MAX_DEV            256        /*      max claw devices          */
DECL|macro|MAX_NAME_LEN
mdefine_line|#define MAX_NAME_LEN            8          /* host name, adapter name length */
DECL|macro|CLAW_FRAME_SIZE
mdefine_line|#define CLAW_FRAME_SIZE         4096
DECL|macro|CLAW_ID_SIZE
mdefine_line|#define CLAW_ID_SIZE            BUS_ID_SIZE+3
multiline_comment|/* state machine codes used in claw_irq_handler */
DECL|macro|CLAW_STOP
mdefine_line|#define CLAW_STOP                0
DECL|macro|CLAW_START_HALT_IO
mdefine_line|#define CLAW_START_HALT_IO       1
DECL|macro|CLAW_START_SENSEID
mdefine_line|#define CLAW_START_SENSEID       2
DECL|macro|CLAW_START_READ
mdefine_line|#define CLAW_START_READ          3
DECL|macro|CLAW_START_WRITE
mdefine_line|#define CLAW_START_WRITE         4
multiline_comment|/*-----------------------------------------------------*&n;*    Lock flag                                         *&n;*------------------------------------------------------*/
DECL|macro|LOCK_YES
mdefine_line|#define LOCK_YES             0
DECL|macro|LOCK_NO
mdefine_line|#define LOCK_NO              1
multiline_comment|/*-----------------------------------------------------*&n;*    DBF Debug macros                                  *&n;*------------------------------------------------------*/
DECL|macro|CLAW_DBF_TEXT
mdefine_line|#define CLAW_DBF_TEXT(level, name, text) &bslash;&n;&t;do { &bslash;&n;&t;&t;debug_text_event(claw_dbf_##name, level, text); &bslash;&n;&t;} while (0)
DECL|macro|CLAW_DBF_HEX
mdefine_line|#define CLAW_DBF_HEX(level,name,addr,len) &bslash;&n;do { &bslash;&n;&t;debug_event(claw_dbf_##name,level,(void*)(addr),len); &bslash;&n;} while (0)
DECL|macro|CLAW_DBF_TEXT_
mdefine_line|#define CLAW_DBF_TEXT_(level,name,text...) &bslash;&n;do {                                       &bslash;&n;&t;sprintf(debug_buffer, text);  &bslash;&n;&t;&t;debug_text_event(claw_dbf_##name,level, debug_buffer);&bslash;&n;} while (0)
multiline_comment|/*******************************************************&n;*  Define Control Blocks                               *&n;*                                                      *&n;********************************************************/
multiline_comment|/*------------------------------------------------------*/
multiline_comment|/*     CLAW header                                      */
multiline_comment|/*------------------------------------------------------*/
DECL|struct|clawh
r_struct
id|clawh
(brace
DECL|member|length
id|__u16
id|length
suffix:semicolon
multiline_comment|/* length of data read by preceding read CCW */
DECL|member|opcode
id|__u8
id|opcode
suffix:semicolon
multiline_comment|/* equivalent read CCW */
DECL|member|flag
id|__u8
id|flag
suffix:semicolon
multiline_comment|/* flag of FF to indicate read was completed */
)brace
suffix:semicolon
multiline_comment|/*------------------------------------------------------*/
multiline_comment|/*     CLAW Packing header   4 bytes                    */
multiline_comment|/*------------------------------------------------------*/
DECL|struct|clawph
r_struct
id|clawph
(brace
DECL|member|len
id|__u16
id|len
suffix:semicolon
multiline_comment|/* Length of Packed Data Area   */
DECL|member|flag
id|__u8
id|flag
suffix:semicolon
multiline_comment|/* Reserved not used            */
DECL|member|link_num
id|__u8
id|link_num
suffix:semicolon
multiline_comment|/* Link ID                      */
)brace
suffix:semicolon
multiline_comment|/*------------------------------------------------------*/
multiline_comment|/*     CLAW Ending struct ccwbk                         */
multiline_comment|/*------------------------------------------------------*/
DECL|struct|endccw
r_struct
id|endccw
(brace
DECL|member|real
id|__u32
id|real
suffix:semicolon
multiline_comment|/* real address of this block */
DECL|member|write1
id|__u8
id|write1
suffix:semicolon
multiline_comment|/* write 1 is active */
DECL|member|read1
id|__u8
id|read1
suffix:semicolon
multiline_comment|/* read 1 is active  */
DECL|member|reserved
id|__u16
id|reserved
suffix:semicolon
multiline_comment|/* reserved for future use */
DECL|member|write1_nop1
r_struct
id|ccw1
id|write1_nop1
suffix:semicolon
DECL|member|write1_nop2
r_struct
id|ccw1
id|write1_nop2
suffix:semicolon
DECL|member|write2_nop1
r_struct
id|ccw1
id|write2_nop1
suffix:semicolon
DECL|member|write2_nop2
r_struct
id|ccw1
id|write2_nop2
suffix:semicolon
DECL|member|read1_nop1
r_struct
id|ccw1
id|read1_nop1
suffix:semicolon
DECL|member|read1_nop2
r_struct
id|ccw1
id|read1_nop2
suffix:semicolon
DECL|member|read2_nop1
r_struct
id|ccw1
id|read2_nop1
suffix:semicolon
DECL|member|read2_nop2
r_struct
id|ccw1
id|read2_nop2
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*------------------------------------------------------*/
multiline_comment|/*     CLAW struct ccwbk                                       */
multiline_comment|/*------------------------------------------------------*/
DECL|struct|ccwbk
r_struct
id|ccwbk
(brace
DECL|member|next
r_void
op_star
id|next
suffix:semicolon
multiline_comment|/* pointer to next ccw block */
DECL|member|real
id|__u32
id|real
suffix:semicolon
multiline_comment|/* real address of this ccw */
DECL|member|p_buffer
r_void
op_star
id|p_buffer
suffix:semicolon
multiline_comment|/* virtual address of data */
DECL|member|header
r_struct
id|clawh
id|header
suffix:semicolon
multiline_comment|/* claw header */
DECL|member|write
r_struct
id|ccw1
id|write
suffix:semicolon
multiline_comment|/* write CCW    */
DECL|member|w_read_FF
r_struct
id|ccw1
id|w_read_FF
suffix:semicolon
multiline_comment|/* read FF */
DECL|member|w_TIC_1
r_struct
id|ccw1
id|w_TIC_1
suffix:semicolon
multiline_comment|/* TIC */
DECL|member|read
r_struct
id|ccw1
id|read
suffix:semicolon
multiline_comment|/* read CCW  */
DECL|member|read_h
r_struct
id|ccw1
id|read_h
suffix:semicolon
multiline_comment|/* read header */
DECL|member|signal
r_struct
id|ccw1
id|signal
suffix:semicolon
multiline_comment|/* signal SMOD  */
DECL|member|r_TIC_1
r_struct
id|ccw1
id|r_TIC_1
suffix:semicolon
multiline_comment|/* TIC1 */
DECL|member|r_read_FF
r_struct
id|ccw1
id|r_read_FF
suffix:semicolon
multiline_comment|/* read FF  */
DECL|member|r_TIC_2
r_struct
id|ccw1
id|r_TIC_2
suffix:semicolon
multiline_comment|/* TIC2 */
)brace
suffix:semicolon
multiline_comment|/*------------------------------------------------------*/
multiline_comment|/*     CLAW control block                               */
multiline_comment|/*------------------------------------------------------*/
DECL|struct|clawctl
r_struct
id|clawctl
(brace
DECL|member|command
id|__u8
id|command
suffix:semicolon
multiline_comment|/* control command */
DECL|member|version
id|__u8
id|version
suffix:semicolon
multiline_comment|/* CLAW protocol version */
DECL|member|linkid
id|__u8
id|linkid
suffix:semicolon
multiline_comment|/* link ID   */
DECL|member|correlator
id|__u8
id|correlator
suffix:semicolon
multiline_comment|/* correlator */
DECL|member|rc
id|__u8
id|rc
suffix:semicolon
multiline_comment|/* return code */
DECL|member|reserved1
id|__u8
id|reserved1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|reserved2
id|__u8
id|reserved2
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|reserved3
id|__u8
id|reserved3
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|data
id|__u8
id|data
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* command specific fields */
)brace
suffix:semicolon
multiline_comment|/*------------------------------------------------------*/
multiline_comment|/*     Data for SYSTEMVALIDATE command                  */
multiline_comment|/*------------------------------------------------------*/
DECL|struct|sysval
r_struct
id|sysval
(brace
DECL|member|WS_name
r_char
id|WS_name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Workstation System name  */
DECL|member|host_name
r_char
id|host_name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Host system name     */
DECL|member|read_frame_size
id|__u16
id|read_frame_size
suffix:semicolon
multiline_comment|/* read frame size */
DECL|member|write_frame_size
id|__u16
id|write_frame_size
suffix:semicolon
multiline_comment|/* write frame size */
DECL|member|reserved
id|__u8
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* reserved */
)brace
suffix:semicolon
multiline_comment|/*------------------------------------------------------*/
multiline_comment|/*     Data for Connect command                         */
multiline_comment|/*------------------------------------------------------*/
DECL|struct|conncmd
r_struct
id|conncmd
(brace
DECL|member|WS_name
r_char
id|WS_name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Workstation application name  */
DECL|member|host_name
r_char
id|host_name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Host application name      */
DECL|member|reserved1
id|__u16
id|reserved1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* read frame size */
DECL|member|reserved2
id|__u8
id|reserved2
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* reserved  */
)brace
suffix:semicolon
multiline_comment|/*------------------------------------------------------*/
multiline_comment|/*     Data for CLAW error                              */
multiline_comment|/*------------------------------------------------------*/
DECL|struct|clawwerror
r_struct
id|clawwerror
(brace
DECL|member|reserved1
r_char
id|reserved1
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|reserved2
r_char
id|reserved2
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* reserved  */
DECL|member|reserved3
r_char
id|reserved3
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* reserved  */
)brace
suffix:semicolon
multiline_comment|/*------------------------------------------------------*/
multiline_comment|/*     Data buffer for CLAW                             */
multiline_comment|/*------------------------------------------------------*/
DECL|struct|clawbuf
r_struct
id|clawbuf
(brace
DECL|member|buffer
r_char
id|buffer
(braket
id|MAX_ENVELOPE_SIZE
)braket
suffix:semicolon
multiline_comment|/* data buffer */
)brace
suffix:semicolon
multiline_comment|/*------------------------------------------------------*/
multiline_comment|/*     Channel control block for read and write channel */
multiline_comment|/*------------------------------------------------------*/
DECL|struct|chbk
r_struct
id|chbk
(brace
DECL|member|devno
r_int
r_int
id|devno
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|id
r_char
id|id
(braket
id|CLAW_ID_SIZE
)braket
suffix:semicolon
DECL|member|IO_active
id|__u32
id|IO_active
suffix:semicolon
DECL|member|claw_state
id|__u8
id|claw_state
suffix:semicolon
DECL|member|irb
r_struct
id|irb
op_star
id|irb
suffix:semicolon
DECL|member|cdev
r_struct
id|ccw_device
op_star
id|cdev
suffix:semicolon
multiline_comment|/* pointer to the channel device */
DECL|member|ndev
r_struct
id|net_device
op_star
id|ndev
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|tasklet
r_struct
id|tasklet_struct
id|tasklet
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|flag_a
r_int
r_int
id|flag_a
suffix:semicolon
multiline_comment|/* atomic flags */
DECL|macro|CLAW_BH_ACTIVE
mdefine_line|#define CLAW_BH_ACTIVE      0
DECL|member|flag_b
r_int
r_int
id|flag_b
suffix:semicolon
multiline_comment|/* atomic flags */
DECL|macro|CLAW_WRITE_ACTIVE
mdefine_line|#define CLAW_WRITE_ACTIVE   0
DECL|member|last_dstat
id|__u8
id|last_dstat
suffix:semicolon
DECL|member|flag
id|__u8
id|flag
suffix:semicolon
DECL|member|collect_queue
r_struct
id|sk_buff_head
id|collect_queue
suffix:semicolon
DECL|member|collect_lock
id|spinlock_t
id|collect_lock
suffix:semicolon
DECL|macro|CLAW_WRITE
mdefine_line|#define CLAW_WRITE      0x02      /* - Set if this is a write channel */
DECL|macro|CLAW_READ
mdefine_line|#define CLAW_READ&t;0x01      /* - Set if this is a read channel  */
DECL|macro|CLAW_TIMER
mdefine_line|#define CLAW_TIMER      0x80      /* - Set if timer made the wake_up  */
)brace
suffix:semicolon
multiline_comment|/*--------------------------------------------------------------*&n;*           CLAW  environment block                             *&n;*---------------------------------------------------------------*/
DECL|struct|claw_env
r_struct
id|claw_env
(brace
DECL|member|devno
r_int
r_int
id|devno
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* device number */
DECL|member|host_name
r_char
id|host_name
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* Host name */
DECL|member|adapter_name
r_char
id|adapter_name
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* adapter name */
DECL|member|api_type
r_char
id|api_type
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* TCPIP, API or PACKED */
DECL|member|p_priv
r_void
op_star
id|p_priv
suffix:semicolon
multiline_comment|/* privptr */
DECL|member|read_buffers
id|__u16
id|read_buffers
suffix:semicolon
multiline_comment|/* read buffer number */
DECL|member|write_buffers
id|__u16
id|write_buffers
suffix:semicolon
multiline_comment|/* write buffer number */
DECL|member|read_size
id|__u16
id|read_size
suffix:semicolon
multiline_comment|/* read buffer size */
DECL|member|write_size
id|__u16
id|write_size
suffix:semicolon
multiline_comment|/* write buffer size */
DECL|member|dev_id
id|__u16
id|dev_id
suffix:semicolon
multiline_comment|/* device ident */
DECL|member|packing
id|__u8
id|packing
suffix:semicolon
multiline_comment|/* are we packing? */
DECL|member|queme_switch
r_volatile
id|__u8
id|queme_switch
suffix:semicolon
multiline_comment|/* gate for imed packing  */
DECL|member|pk_delay
r_volatile
r_int
r_int
id|pk_delay
suffix:semicolon
multiline_comment|/* Delay for adaptive packing */
DECL|member|in_use
id|__u8
id|in_use
suffix:semicolon
multiline_comment|/* device active flag */
DECL|member|ndev
r_struct
id|net_device
op_star
id|ndev
suffix:semicolon
multiline_comment|/* backward ptr to the net dev*/
)brace
suffix:semicolon
multiline_comment|/*--------------------------------------------------------------*&n;*           CLAW  main control block                            *&n;*---------------------------------------------------------------*/
DECL|struct|claw_privbk
r_struct
id|claw_privbk
(brace
DECL|member|p_buff_ccw
r_void
op_star
id|p_buff_ccw
suffix:semicolon
DECL|member|p_buff_ccw_num
id|__u32
id|p_buff_ccw_num
suffix:semicolon
DECL|member|p_buff_read
r_void
op_star
id|p_buff_read
suffix:semicolon
DECL|member|p_buff_read_num
id|__u32
id|p_buff_read_num
suffix:semicolon
DECL|member|p_buff_pages_perread
id|__u32
id|p_buff_pages_perread
suffix:semicolon
DECL|member|p_buff_write
r_void
op_star
id|p_buff_write
suffix:semicolon
DECL|member|p_buff_write_num
id|__u32
id|p_buff_write_num
suffix:semicolon
DECL|member|p_buff_pages_perwrite
id|__u32
id|p_buff_pages_perwrite
suffix:semicolon
DECL|member|active_link_ID
r_int
id|active_link_ID
suffix:semicolon
multiline_comment|/* Active logical link ID */
DECL|member|p_write_free_chain
r_struct
id|ccwbk
op_star
id|p_write_free_chain
suffix:semicolon
multiline_comment|/* pointer to free ccw chain */
DECL|member|p_write_active_first
r_struct
id|ccwbk
op_star
id|p_write_active_first
suffix:semicolon
multiline_comment|/* ptr to the first write ccw */
DECL|member|p_write_active_last
r_struct
id|ccwbk
op_star
id|p_write_active_last
suffix:semicolon
multiline_comment|/* ptr to the last write ccw */
DECL|member|p_read_active_first
r_struct
id|ccwbk
op_star
id|p_read_active_first
suffix:semicolon
multiline_comment|/* ptr to the first read ccw */
DECL|member|p_read_active_last
r_struct
id|ccwbk
op_star
id|p_read_active_last
suffix:semicolon
multiline_comment|/* ptr to the last read ccw */
DECL|member|p_end_ccw
r_struct
id|endccw
op_star
id|p_end_ccw
suffix:semicolon
multiline_comment|/*ptr to ending ccw */
DECL|member|p_claw_signal_blk
r_struct
id|ccwbk
op_star
id|p_claw_signal_blk
suffix:semicolon
multiline_comment|/* ptr to signal block */
DECL|member|write_free_count
id|__u32
id|write_free_count
suffix:semicolon
multiline_comment|/* number of free bufs for write */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
multiline_comment|/* &t; device status    */
DECL|member|channel
r_struct
id|chbk
id|channel
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Channel control blocks */
DECL|member|mtc_skipping
id|__u8
id|mtc_skipping
suffix:semicolon
DECL|member|mtc_offset
r_int
id|mtc_offset
suffix:semicolon
DECL|member|mtc_logical_link
r_int
id|mtc_logical_link
suffix:semicolon
DECL|member|p_mtc_envelope
r_void
op_star
id|p_mtc_envelope
suffix:semicolon
DECL|member|pk_skb
r_struct
id|sk_buff
op_star
id|pk_skb
suffix:semicolon
multiline_comment|/* packing buffer    */
DECL|member|pk_cnt
r_int
id|pk_cnt
suffix:semicolon
DECL|member|ctl_bk
r_struct
id|clawctl
id|ctl_bk
suffix:semicolon
DECL|member|p_env
r_struct
id|claw_env
op_star
id|p_env
suffix:semicolon
DECL|member|system_validate_comp
id|__u8
id|system_validate_comp
suffix:semicolon
DECL|member|release_pend
id|__u8
id|release_pend
suffix:semicolon
DECL|member|checksum_received_ip_pkts
id|__u8
id|checksum_received_ip_pkts
suffix:semicolon
DECL|member|buffs_alloc
id|__u8
id|buffs_alloc
suffix:semicolon
DECL|member|end_ccw
r_struct
id|endccw
id|end_ccw
suffix:semicolon
DECL|member|tbusy
r_int
r_int
id|tbusy
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/************************************************************/
multiline_comment|/* define global constants                                  */
multiline_comment|/************************************************************/
DECL|macro|CCWBK_SIZE
mdefine_line|#define CCWBK_SIZE sizeof(struct ccwbk)
eof
