multiline_comment|/* Definitions for an IBM Token Ring card. */
multiline_comment|/* This file is distributed under the GNU GPL   */
multiline_comment|/* ported to the Alpha architecture 02/20/96 (just used the HZ macro) */
DECL|macro|TR_RETRY_INTERVAL
mdefine_line|#define TR_RETRY_INTERVAL (5*HZ) /* 500 on PC = 5 s */
DECL|macro|TR_RESET_INTERVAL
mdefine_line|#define TR_RESET_INTERVAL (HZ/20) /* 5 on PC = 50 ms */
DECL|macro|TR_BUSY_INTERVAL
mdefine_line|#define TR_BUSY_INTERVAL (HZ/5) /* 5 on PC = 200 ms */
DECL|macro|TR_SPIN_INTERVAL
mdefine_line|#define TR_SPIN_INTERVAL (3*HZ) /* 3 seconds before init timeout */
DECL|macro|TR_RETRIES
mdefine_line|#define TR_RETRIES 6            /* number of open retries */ 
DECL|macro|TR_ISA
mdefine_line|#define TR_ISA 1
DECL|macro|TR_MCA
mdefine_line|#define TR_MCA 2
DECL|macro|TR_ISAPNP
mdefine_line|#define TR_ISAPNP 3
DECL|macro|NOTOK
mdefine_line|#define NOTOK 0
DECL|macro|TOKDEBUG
mdefine_line|#define TOKDEBUG 1
DECL|macro|IBMTR_SHARED_RAM_SIZE
mdefine_line|#define IBMTR_SHARED_RAM_SIZE 0x10000
DECL|macro|IBMTR_IO_EXTENT
mdefine_line|#define IBMTR_IO_EXTENT 4
DECL|macro|IBMTR_MAX_ADAPTERS
mdefine_line|#define IBMTR_MAX_ADAPTERS 2
DECL|macro|CHANNEL_ID
mdefine_line|#define CHANNEL_ID      0X1F30
DECL|macro|AIP
mdefine_line|#define AIP             0X1F00
DECL|macro|AIPCHKSUM1
mdefine_line|#define AIPCHKSUM1      0X1F60
DECL|macro|AIPCHKSUM2
mdefine_line|#define AIPCHKSUM2      0X1FF0
DECL|macro|AIPADAPTYPE
mdefine_line|#define AIPADAPTYPE     0X1FA0
DECL|macro|AIPDATARATE
mdefine_line|#define AIPDATARATE     0X1FA2
DECL|macro|AIPEARLYTOKEN
mdefine_line|#define AIPEARLYTOKEN   0X1FA4
DECL|macro|AIPAVAILSHRAM
mdefine_line|#define AIPAVAILSHRAM   0X1FA6
DECL|macro|AIPSHRAMPAGE
mdefine_line|#define AIPSHRAMPAGE    0X1FA8
DECL|macro|AIP4MBDHB
mdefine_line|#define AIP4MBDHB       0X1FAA
DECL|macro|AIP16MBDHB
mdefine_line|#define AIP16MBDHB      0X1FAC
DECL|macro|AIPFID
mdefine_line|#define AIPFID&t;&t;0X1FBA
multiline_comment|/* Note, 0xA20 == 0x220 since motherboard decodes 10 bits.  I left everything&n;   the way my documentation had it, ie: 0x0A20.     */
DECL|macro|ADAPTINTCNTRL
mdefine_line|#define ADAPTINTCNTRL   0x02f0  /* Adapter interrupt control */
DECL|macro|ADAPTRESET
mdefine_line|#define ADAPTRESET      0x1     /* Control Adapter reset (add to base) */
DECL|macro|ADAPTRESETREL
mdefine_line|#define ADAPTRESETREL   0x2     /* Release Adapter from reset ( &quot;&quot;&quot;)  */
DECL|macro|ADAPTINTREL
mdefine_line|#define ADAPTINTREL&t;0x3 &t;/* Adapter interrupt release */
DECL|macro|MMIOStartLocP
mdefine_line|#define MMIOStartLocP   0x0a20  /* Primary adapter&squot;s starting MMIO area */
DECL|macro|MMIOStartLocA
mdefine_line|#define MMIOStartLocA   0x0a24  /* Alternate adapter&squot;s starting MMIO area */
DECL|macro|GLOBAL_INT_ENABLE
mdefine_line|#define GLOBAL_INT_ENABLE 0x02f0
multiline_comment|/* MMIO bits 0-4 select register */
DECL|macro|RRR_EVEN
mdefine_line|#define RRR_EVEN        0x00    /* Shared RAM relocation registers - even and odd */
multiline_comment|/* Used to set the starting address of shared RAM  */
multiline_comment|/* Bits 1 through 7 of this register map to bits 13 through 19 of the shared RAM address.*/
multiline_comment|/* ie: 0x02 sets RAM address to ...ato!  issy su wazzoo !! GODZILLA!!! */
DECL|macro|RRR_ODD
mdefine_line|#define RRR_ODD         0x01
multiline_comment|/* Bits 2 and 3 of this register can be read to determine shared RAM size */
multiline_comment|/* 00 for 8k, 01 for 16k, 10 for 32k, 11 for 64k  */
DECL|macro|WRBR_EVEN
mdefine_line|#define WRBR_EVEN       0x02    /* Write region base registers - even and odd */
DECL|macro|WRBR_ODD
mdefine_line|#define WRBR_ODD        0x03
DECL|macro|WWOR_EVEN
mdefine_line|#define WWOR_EVEN       0x04    /* Write window open registers - even and odd */
DECL|macro|WWOR_ODD
mdefine_line|#define WWOR_ODD        0x05
DECL|macro|WWCR_EVEN
mdefine_line|#define WWCR_EVEN       0x06    /* Write window close registers - even and odd */
DECL|macro|WWCR_ODD
mdefine_line|#define WWCR_ODD        0x07
multiline_comment|/* Interrupt status registers - PC system  - even and odd */
DECL|macro|ISRP_EVEN
mdefine_line|#define ISRP_EVEN       0x08
DECL|macro|TCR_INT
mdefine_line|#define TCR_INT 0x10    /* Bit 4 - Timer interrupt.  The TVR_EVEN timer has&n;                                                                   expired. */
DECL|macro|ERR_INT
mdefine_line|#define ERR_INT 0x08    /* Bit 3 - Error interrupt.  The adapter has had an&n;                                                                   internal error. */
DECL|macro|ACCESS_INT
mdefine_line|#define ACCESS_INT 0x04    /* Bit 2 - Access interrupt.  You have attempted to&n;                                                           write to an invalid area of shared RAM or an invalid&n;                                                                   register within the MMIO. */
multiline_comment|/*      In addition, the following bits within ISRP_EVEN can be turned on or off by you */
multiline_comment|/*      to control the interrupt processing:   */
DECL|macro|INT_IRQ
mdefine_line|#define INT_IRQ 0x80    /* Bit 7 - If 0 the adapter will issue a CHCK, if 1 and&n;                                                              IRQ.  This should normally be set (by you) to 1.  */
DECL|macro|INT_ENABLE
mdefine_line|#define INT_ENABLE 0x40 /* Bit 6 - Interrupt enable.  If 0, no interrupts will&n;                                                                   occur.  If 1, interrupts will occur normally.&n;                                                                   Normally set to 1.  */
multiline_comment|/* Bit 0 - Primary or alternate adapter.  Set to zero if this adapter is the primary adapter,*/
multiline_comment|/*         1 if this adapter is the alternate adapter. */
DECL|macro|ISRP_ODD
mdefine_line|#define ISRP_ODD        0x09
DECL|macro|ADAP_CHK_INT
mdefine_line|#define ADAP_CHK_INT 0x40 /* Bit 6 - Adapter check.  the adapter has&n;                             encountered a serious problem and has closed&n;                             itself.  Whoa.  */
DECL|macro|SRB_RESP_INT
mdefine_line|#define SRB_RESP_INT 0x20 /* Bit 5 - SRB response.  The adapter has accepted&n;                             an SRB request and set the return code within&n;                             the SRB. */
DECL|macro|ASB_FREE_INT
mdefine_line|#define ASB_FREE_INT 0x10 /* Bit 4 - ASB free.  The adapter has read the ASB&n;                                                                          and this area can be safely reused. This interrupt&n;                                                                          is only used if your application has set the ASB&n;                                                                          free request bit in ISRA_ODD or if an error was&n;                                                                detected in your response. */
DECL|macro|ARB_CMD_INT
mdefine_line|#define ARB_CMD_INT  0x08 /* Bit 3 - ARB command.  The adapter has given you a&n;                                                                          command for action.  The command is located in the&n;                                                                          ARB area of shared memory. */
DECL|macro|SSB_RESP_INT
mdefine_line|#define SSB_RESP_INT 0x04 /* Bit 2 - SSB response.  The adapter has posted a&n;                                                                          response to your SRB (the response is located in&n;                                                                          the SSB area of shared memory). */
multiline_comment|/* Bit 1 - Bridge frame forward complete. */
DECL|macro|ISRA_EVEN
mdefine_line|#define ISRA_EVEN       0x0A    /* Interrupt status registers - adapter  - even and odd */
multiline_comment|/* Bit 7 - Internal parity error (on adapter&squot;s internal bus) */
multiline_comment|/* Bit 6 - Timer interrupt pending */
multiline_comment|/* Bit 5 - Access interrupt (attempt by adapter to access illegal address) */
multiline_comment|/* Bit 4 - Adapter microcode problem (microcode dead-man timer expired) */
multiline_comment|/* Bit 3 - Adapter processor check status */
multiline_comment|/* Bit 2 - Reserved */
multiline_comment|/* Bit 1 - Adapter hardware interrupt mask (prevents internal interrupts) */
multiline_comment|/* Bit 0 - Adapter software interrupt mask (prevents internal software interrupts) */
DECL|macro|ISRA_ODD
mdefine_line|#define ISRA_ODD        0x0B
DECL|macro|CMD_IN_SRB
mdefine_line|#define CMD_IN_SRB 0x20 /* Bit 5  - Indicates that you have placed a new&n;                           command in the SRB and are ready for the adapter to&n;                           process the command. */
DECL|macro|RESP_IN_ASB
mdefine_line|#define RESP_IN_ASB 0x10 /* Bit 4 - Indicates that you have placed a response&n;                                                                    (an ASB) in the shared RAM which is available for&n;                                                                         the adapter&squot;s use. */
multiline_comment|/* Bit 3 - Indicates that you are ready to put an SRB in the shared RAM, but that a previous */
multiline_comment|/*         command is still pending.  The adapter will then interrupt you when the previous */
multiline_comment|/*         command is completed */
multiline_comment|/* Bit 2 - Indicates that you are ready to put an ASB in the shared RAM, but that a previous */
multiline_comment|/*         ASB is still pending.  The adapter will then interrupt you when the previous ASB */
multiline_comment|/*         is copied.  */
DECL|macro|ARB_FREE
mdefine_line|#define ARB_FREE 0x2
DECL|macro|SSB_FREE
mdefine_line|#define SSB_FREE 0x1
DECL|macro|TCR_EVEN
mdefine_line|#define TCR_EVEN        0x0C    /* Timer control registers - even and odd */
DECL|macro|TCR_ODD
mdefine_line|#define TCR_ODD         0x0D
DECL|macro|TVR_EVEN
mdefine_line|#define TVR_EVEN        0x0E    /* Timer value registers - even and odd */
DECL|macro|TVR_ODD
mdefine_line|#define TVR_ODD         0x0F
DECL|macro|SRPR_EVEN
mdefine_line|#define SRPR_EVEN       0x18    /* Shared RAM paging registers - even and odd */
DECL|macro|SRPR_ENABLE_PAGING
mdefine_line|#define SRPR_ENABLE_PAGING 0xc0
DECL|macro|SRPR_ODD
mdefine_line|#define SRPR_ODD        0x19 /* Not used. */
DECL|macro|TOKREAD
mdefine_line|#define TOKREAD         0x60
DECL|macro|TOKOR
mdefine_line|#define TOKOR           0x40
DECL|macro|TOKAND
mdefine_line|#define TOKAND          0x20
DECL|macro|TOKWRITE
mdefine_line|#define TOKWRITE        0x00
multiline_comment|/* MMIO bits 5-6 select operation */
multiline_comment|/* 00 is used to write to a register */
multiline_comment|/* 01 is used to bitwise AND a byte with a register */
multiline_comment|/* 10 is used to bitwise OR a byte with a register  */
multiline_comment|/* 11 is used to read from a register */
multiline_comment|/* MMIO bits 7-8 select area of interest.. see below */
multiline_comment|/* 00 selects attachment control area. */
multiline_comment|/* 01 is reserved. */
multiline_comment|/* 10 selects adapter identification area A containing the adapter encoded address. */
multiline_comment|/* 11 selects the adapter identification area B containing test patterns. */
DECL|macro|PCCHANNELID
mdefine_line|#define PCCHANNELID 5049434F3631313039393020
DECL|macro|MCCHANNELID
mdefine_line|#define MCCHANNELID 4D4152533633583435313820
DECL|macro|ACA_OFFSET
mdefine_line|#define ACA_OFFSET 0x1e00
DECL|macro|ACA_SET
mdefine_line|#define ACA_SET 0x40
DECL|macro|ACA_RESET
mdefine_line|#define ACA_RESET 0x20
DECL|macro|ACA_RW
mdefine_line|#define ACA_RW 0x00
macro_line|#ifdef ENABLE_PAGING
DECL|macro|SET_PAGE
mdefine_line|#define SET_PAGE(x) (isa_writeb((x), &bslash;&n;  ti-&gt;mmio + ACA_OFFSET + ACA_RW + SRPR_EVEN))
macro_line|#else
DECL|macro|SET_PAGE
mdefine_line|#define SET_PAGE(x)
macro_line|#endif
DECL|enumerator|IN_PROGRESS
DECL|enumerator|SUCCESS
DECL|enumerator|FAILURE
DECL|enumerator|CLOSED
DECL|typedef|open_state
r_typedef
r_enum
(brace
id|IN_PROGRESS
comma
id|SUCCESS
comma
id|FAILURE
comma
id|CLOSED
)brace
id|open_state
suffix:semicolon
multiline_comment|/* do_tok_int possible values */
DECL|macro|FIRST_INT
mdefine_line|#define FIRST_INT 1
DECL|macro|NOT_FIRST
mdefine_line|#define NOT_FIRST 2
DECL|struct|tok_info
r_struct
id|tok_info
(brace
DECL|member|irq
r_int
r_char
id|irq
suffix:semicolon
DECL|member|mmio
id|__u32
id|mmio
suffix:semicolon
DECL|member|hw_address
r_int
r_char
id|hw_address
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|adapter_type
r_int
r_char
id|adapter_type
suffix:semicolon
DECL|member|data_rate
r_int
r_char
id|data_rate
suffix:semicolon
DECL|member|token_release
r_int
r_char
id|token_release
suffix:semicolon
DECL|member|avail_shared_ram
r_int
r_char
id|avail_shared_ram
suffix:semicolon
DECL|member|shared_ram_paging
r_int
r_char
id|shared_ram_paging
suffix:semicolon
DECL|member|dhb_size4mb
r_int
r_int
id|dhb_size4mb
suffix:semicolon
DECL|member|rbuf_len4
r_int
r_int
id|rbuf_len4
suffix:semicolon
DECL|member|rbuf_cnt4
r_int
r_int
id|rbuf_cnt4
suffix:semicolon
DECL|member|maxmtu4
r_int
r_int
id|maxmtu4
suffix:semicolon
DECL|member|dhb_size16mb
r_int
r_int
id|dhb_size16mb
suffix:semicolon
DECL|member|rbuf_len16
r_int
r_int
id|rbuf_len16
suffix:semicolon
DECL|member|rbuf_cnt16
r_int
r_int
id|rbuf_cnt16
suffix:semicolon
DECL|member|maxmtu16
r_int
r_int
id|maxmtu16
suffix:semicolon
multiline_comment|/* Additions by David Morris       */
DECL|member|do_tok_int
r_int
r_char
id|do_tok_int
suffix:semicolon
DECL|member|wait_for_tok_int
id|wait_queue_head_t
id|wait_for_tok_int
suffix:semicolon
DECL|member|wait_for_reset
id|wait_queue_head_t
id|wait_for_reset
suffix:semicolon
DECL|member|sram_base
r_int
r_char
id|sram_base
suffix:semicolon
multiline_comment|/* Additions by Peter De Schrijver */
DECL|member|page_mask
r_int
r_char
id|page_mask
suffix:semicolon
multiline_comment|/* mask to select RAM page to Map*/
DECL|member|mapped_ram_size
r_int
r_char
id|mapped_ram_size
suffix:semicolon
multiline_comment|/* size of RAM page */
DECL|member|sram
id|__u32
id|sram
suffix:semicolon
multiline_comment|/* Shared memory base address */
DECL|member|init_srb
id|__u32
id|init_srb
suffix:semicolon
multiline_comment|/* Initial System Request Block address */
DECL|member|srb
id|__u32
id|srb
suffix:semicolon
multiline_comment|/* System Request Block address */
DECL|member|ssb
id|__u32
id|ssb
suffix:semicolon
multiline_comment|/* System Status Block address */
DECL|member|arb
id|__u32
id|arb
suffix:semicolon
multiline_comment|/* Adapter Request Block address */
DECL|member|asb
id|__u32
id|asb
suffix:semicolon
multiline_comment|/* Adapter Status Block address */
DECL|member|init_srb_page
id|__u8
id|init_srb_page
suffix:semicolon
DECL|member|srb_page
id|__u8
id|srb_page
suffix:semicolon
DECL|member|ssb_page
id|__u8
id|ssb_page
suffix:semicolon
DECL|member|arb_page
id|__u8
id|arb_page
suffix:semicolon
DECL|member|asb_page
id|__u8
id|asb_page
suffix:semicolon
DECL|member|exsap_station_id
r_int
r_int
id|exsap_station_id
suffix:semicolon
DECL|member|global_int_enable
r_int
r_int
id|global_int_enable
suffix:semicolon
DECL|member|current_skb
r_struct
id|sk_buff
op_star
id|current_skb
suffix:semicolon
DECL|member|tr_stats
r_struct
id|net_device_stats
id|tr_stats
suffix:semicolon
DECL|member|auto_ringspeedsave
r_int
r_char
id|auto_ringspeedsave
suffix:semicolon
DECL|member|open_status
id|open_state
id|open_status
suffix:semicolon
DECL|member|readlog_pending
r_int
r_char
id|readlog_pending
suffix:semicolon
DECL|member|adapter_int_enable
r_int
r_int
id|adapter_int_enable
suffix:semicolon
multiline_comment|/* Adapter-specific int enable */
DECL|member|tr_timer
r_struct
id|timer_list
id|tr_timer
suffix:semicolon
DECL|member|ring_speed
r_int
r_char
id|ring_speed
suffix:semicolon
DECL|member|func_addr
id|__u32
id|func_addr
suffix:semicolon
DECL|member|retry_count
r_int
r_int
id|retry_count
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* SMP protection */
)brace
suffix:semicolon
multiline_comment|/* token ring adapter commands */
DECL|macro|DIR_INTERRUPT
mdefine_line|#define DIR_INTERRUPT &t;&t;0x00 /* struct srb_interrupt */
DECL|macro|DIR_MOD_OPEN_PARAMS
mdefine_line|#define DIR_MOD_OPEN_PARAMS &t;0x01
DECL|macro|DIR_OPEN_ADAPTER
mdefine_line|#define DIR_OPEN_ADAPTER &t;0x03 /* struct dir_open_adapter */
DECL|macro|DIR_CLOSE_ADAPTER
mdefine_line|#define DIR_CLOSE_ADAPTER   &t;0x04
DECL|macro|DIR_SET_GRP_ADDR
mdefine_line|#define DIR_SET_GRP_ADDR    &t;0x06
DECL|macro|DIR_SET_FUNC_ADDR
mdefine_line|#define DIR_SET_FUNC_ADDR   &t;0x07 /* struct srb_set_funct_addr */
DECL|macro|DIR_READ_LOG
mdefine_line|#define DIR_READ_LOG &t;&t;0x08 /* struct srb_read_log */
DECL|macro|DLC_OPEN_SAP
mdefine_line|#define DLC_OPEN_SAP &t;&t;0x15 /* struct dlc_open_sap */
DECL|macro|DLC_CLOSE_SAP
mdefine_line|#define DLC_CLOSE_SAP       &t;0x16
DECL|macro|DATA_LOST
mdefine_line|#define DATA_LOST &t;&t;0x20 /* struct asb_rec */
DECL|macro|REC_DATA
mdefine_line|#define REC_DATA &t;&t;0x81 /* struct arb_rec_req */
DECL|macro|XMIT_DATA_REQ
mdefine_line|#define XMIT_DATA_REQ &t;&t;0x82 /* struct arb_xmit_req */
DECL|macro|DLC_STATUS
mdefine_line|#define DLC_STATUS &t;&t;0x83 /* struct arb_dlc_status */
DECL|macro|RING_STAT_CHANGE
mdefine_line|#define RING_STAT_CHANGE    &t;0x84 /* struct dlc_open_sap ??? */
multiline_comment|/* DIR_OPEN_ADAPTER options */
DECL|macro|OPEN_PASS_BCON_MAC
mdefine_line|#define OPEN_PASS_BCON_MAC 0x0100
DECL|macro|NUM_RCV_BUF
mdefine_line|#define NUM_RCV_BUF 2
DECL|macro|RCV_BUF_LEN
mdefine_line|#define RCV_BUF_LEN 1024
DECL|macro|DHB_LENGTH
mdefine_line|#define DHB_LENGTH 2048
DECL|macro|NUM_DHB
mdefine_line|#define NUM_DHB 2
DECL|macro|DLC_MAX_SAP
mdefine_line|#define DLC_MAX_SAP 2
DECL|macro|DLC_MAX_STA
mdefine_line|#define DLC_MAX_STA 1
multiline_comment|/* DLC_OPEN_SAP options */
DECL|macro|MAX_I_FIELD
mdefine_line|#define MAX_I_FIELD 0x0088
DECL|macro|SAP_OPEN_IND_SAP
mdefine_line|#define SAP_OPEN_IND_SAP 0x04
DECL|macro|SAP_OPEN_PRIORITY
mdefine_line|#define SAP_OPEN_PRIORITY 0x20
DECL|macro|SAP_OPEN_STATION_CNT
mdefine_line|#define SAP_OPEN_STATION_CNT 0x1
DECL|macro|XMIT_DIR_FRAME
mdefine_line|#define XMIT_DIR_FRAME 0x0A
DECL|macro|XMIT_UI_FRAME
mdefine_line|#define XMIT_UI_FRAME  0x0d
DECL|macro|XMIT_XID_CMD
mdefine_line|#define XMIT_XID_CMD   0x0e
DECL|macro|XMIT_TEST_CMD
mdefine_line|#define XMIT_TEST_CMD  0x11
multiline_comment|/* srb close return code */
DECL|macro|SIGNAL_LOSS
mdefine_line|#define SIGNAL_LOSS  0x8000
DECL|macro|HARD_ERROR
mdefine_line|#define HARD_ERROR   0x4000
DECL|macro|XMIT_BEACON
mdefine_line|#define XMIT_BEACON  0x1000
DECL|macro|LOBE_FAULT
mdefine_line|#define LOBE_FAULT   0x0800
DECL|macro|AUTO_REMOVAL
mdefine_line|#define AUTO_REMOVAL 0x0400
DECL|macro|REMOVE_RECV
mdefine_line|#define REMOVE_RECV  0x0100
DECL|macro|LOG_OVERFLOW
mdefine_line|#define LOG_OVERFLOW 0x0080
DECL|macro|RING_RECOVER
mdefine_line|#define RING_RECOVER 0x0020
DECL|struct|srb_init_response
r_struct
id|srb_init_response
(brace
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|member|init_status
r_int
r_char
id|init_status
suffix:semicolon
DECL|member|init_status_2
r_int
r_char
id|init_status_2
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|bring_up_code
id|__u16
id|bring_up_code
suffix:semicolon
DECL|member|encoded_address
id|__u16
id|encoded_address
suffix:semicolon
DECL|member|level_address
id|__u16
id|level_address
suffix:semicolon
DECL|member|adapter_address
id|__u16
id|adapter_address
suffix:semicolon
DECL|member|parms_address
id|__u16
id|parms_address
suffix:semicolon
DECL|member|mac_address
id|__u16
id|mac_address
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dir_open_adapter
r_struct
id|dir_open_adapter
(brace
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|member|reserved
r_char
id|reserved
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|open_options
id|__u16
id|open_options
suffix:semicolon
DECL|member|node_address
r_int
r_char
id|node_address
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|group_address
r_int
r_char
id|group_address
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|funct_address
r_int
r_char
id|funct_address
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|num_rcv_buf
id|__u16
id|num_rcv_buf
suffix:semicolon
DECL|member|rcv_buf_len
id|__u16
id|rcv_buf_len
suffix:semicolon
DECL|member|dhb_length
id|__u16
id|dhb_length
suffix:semicolon
DECL|member|num_dhb
r_int
r_char
id|num_dhb
suffix:semicolon
DECL|member|reserved2
r_char
id|reserved2
suffix:semicolon
DECL|member|dlc_max_sap
r_int
r_char
id|dlc_max_sap
suffix:semicolon
DECL|member|dlc_max_sta
r_int
r_char
id|dlc_max_sta
suffix:semicolon
DECL|member|dlc_max_gsap
r_int
r_char
id|dlc_max_gsap
suffix:semicolon
DECL|member|dlc_max_gmem
r_int
r_char
id|dlc_max_gmem
suffix:semicolon
DECL|member|dlc_t1_tick_1
r_int
r_char
id|dlc_t1_tick_1
suffix:semicolon
DECL|member|dlc_t2_tick_1
r_int
r_char
id|dlc_t2_tick_1
suffix:semicolon
DECL|member|dlc_ti_tick_1
r_int
r_char
id|dlc_ti_tick_1
suffix:semicolon
DECL|member|dlc_t1_tick_2
r_int
r_char
id|dlc_t1_tick_2
suffix:semicolon
DECL|member|dlc_t2_tick_2
r_int
r_char
id|dlc_t2_tick_2
suffix:semicolon
DECL|member|dlc_ti_tick_2
r_int
r_char
id|dlc_ti_tick_2
suffix:semicolon
DECL|member|product_id
r_int
r_char
id|product_id
(braket
l_int|18
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|srb_open_response
r_struct
id|srb_open_response
(brace
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|member|reserved1
r_int
r_char
id|reserved1
suffix:semicolon
DECL|member|ret_code
r_int
r_char
id|ret_code
suffix:semicolon
DECL|member|reserved2
r_int
r_char
id|reserved2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|error_code
id|__u16
id|error_code
suffix:semicolon
DECL|member|asb_addr
id|__u16
id|asb_addr
suffix:semicolon
DECL|member|srb_addr
id|__u16
id|srb_addr
suffix:semicolon
DECL|member|arb_addr
id|__u16
id|arb_addr
suffix:semicolon
DECL|member|ssb_addr
id|__u16
id|ssb_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dlc_open_sap
r_struct
id|dlc_open_sap
(brace
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|member|reserved1
r_int
r_char
id|reserved1
suffix:semicolon
DECL|member|ret_code
r_int
r_char
id|ret_code
suffix:semicolon
DECL|member|reserved2
r_int
r_char
id|reserved2
suffix:semicolon
DECL|member|station_id
id|__u16
id|station_id
suffix:semicolon
DECL|member|timer_t1
r_int
r_char
id|timer_t1
suffix:semicolon
DECL|member|timer_t2
r_int
r_char
id|timer_t2
suffix:semicolon
DECL|member|timer_ti
r_int
r_char
id|timer_ti
suffix:semicolon
DECL|member|maxout
r_int
r_char
id|maxout
suffix:semicolon
DECL|member|maxin
r_int
r_char
id|maxin
suffix:semicolon
DECL|member|maxout_incr
r_int
r_char
id|maxout_incr
suffix:semicolon
DECL|member|max_retry_count
r_int
r_char
id|max_retry_count
suffix:semicolon
DECL|member|gsap_max_mem
r_int
r_char
id|gsap_max_mem
suffix:semicolon
DECL|member|max_i_field
id|__u16
id|max_i_field
suffix:semicolon
DECL|member|sap_value
r_int
r_char
id|sap_value
suffix:semicolon
DECL|member|sap_options
r_int
r_char
id|sap_options
suffix:semicolon
DECL|member|station_count
r_int
r_char
id|station_count
suffix:semicolon
DECL|member|sap_gsap_mem
r_int
r_char
id|sap_gsap_mem
suffix:semicolon
DECL|member|gsap
r_int
r_char
id|gsap
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|srb_xmit
r_struct
id|srb_xmit
(brace
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|member|cmd_corr
r_int
r_char
id|cmd_corr
suffix:semicolon
DECL|member|ret_code
r_int
r_char
id|ret_code
suffix:semicolon
DECL|member|reserved1
r_int
r_char
id|reserved1
suffix:semicolon
DECL|member|station_id
id|__u16
id|station_id
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|srb_interrupt
r_struct
id|srb_interrupt
(brace
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|member|cmd_corr
r_int
r_char
id|cmd_corr
suffix:semicolon
DECL|member|ret_code
r_int
r_char
id|ret_code
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|srb_read_log
r_struct
id|srb_read_log
(brace
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|member|reserved1
r_int
r_char
id|reserved1
suffix:semicolon
DECL|member|ret_code
r_int
r_char
id|ret_code
suffix:semicolon
DECL|member|reserved2
r_int
r_char
id|reserved2
suffix:semicolon
DECL|member|line_errors
r_int
r_char
id|line_errors
suffix:semicolon
DECL|member|internal_errors
r_int
r_char
id|internal_errors
suffix:semicolon
DECL|member|burst_errors
r_int
r_char
id|burst_errors
suffix:semicolon
DECL|member|A_C_errors
r_int
r_char
id|A_C_errors
suffix:semicolon
DECL|member|abort_delimiters
r_int
r_char
id|abort_delimiters
suffix:semicolon
DECL|member|reserved3
r_int
r_char
id|reserved3
suffix:semicolon
DECL|member|lost_frames
r_int
r_char
id|lost_frames
suffix:semicolon
DECL|member|recv_congest_count
r_int
r_char
id|recv_congest_count
suffix:semicolon
DECL|member|frame_copied_errors
r_int
r_char
id|frame_copied_errors
suffix:semicolon
DECL|member|frequency_errors
r_int
r_char
id|frequency_errors
suffix:semicolon
DECL|member|token_errors
r_int
r_char
id|token_errors
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|asb_xmit_resp
r_struct
id|asb_xmit_resp
(brace
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|member|cmd_corr
r_int
r_char
id|cmd_corr
suffix:semicolon
DECL|member|ret_code
r_int
r_char
id|ret_code
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:semicolon
DECL|member|station_id
id|__u16
id|station_id
suffix:semicolon
DECL|member|frame_length
id|__u16
id|frame_length
suffix:semicolon
DECL|member|hdr_length
r_int
r_char
id|hdr_length
suffix:semicolon
DECL|member|rsap_value
r_int
r_char
id|rsap_value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|arb_xmit_req
r_struct
id|arb_xmit_req
(brace
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|member|cmd_corr
r_int
r_char
id|cmd_corr
suffix:semicolon
DECL|member|reserved1
r_int
r_char
id|reserved1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|station_id
id|__u16
id|station_id
suffix:semicolon
DECL|member|dhb_address
id|__u16
id|dhb_address
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|arb_rec_req
r_struct
id|arb_rec_req
(brace
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|member|reserved1
r_int
r_char
id|reserved1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|station_id
id|__u16
id|station_id
suffix:semicolon
DECL|member|rec_buf_addr
id|__u16
id|rec_buf_addr
suffix:semicolon
DECL|member|lan_hdr_len
r_int
r_char
id|lan_hdr_len
suffix:semicolon
DECL|member|dlc_hdr_len
r_int
r_char
id|dlc_hdr_len
suffix:semicolon
DECL|member|frame_len
id|__u16
id|frame_len
suffix:semicolon
DECL|member|msg_type
r_int
r_char
id|msg_type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|asb_rec
r_struct
id|asb_rec
(brace
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|member|reserved1
r_int
r_char
id|reserved1
suffix:semicolon
DECL|member|ret_code
r_int
r_char
id|ret_code
suffix:semicolon
DECL|member|reserved2
r_int
r_char
id|reserved2
suffix:semicolon
DECL|member|station_id
id|__u16
id|station_id
suffix:semicolon
DECL|member|rec_buf_addr
id|__u16
id|rec_buf_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rec_buf
r_struct
id|rec_buf
(brace
multiline_comment|/*&t;unsigned char reserved1[2]; */
DECL|member|buf_ptr
id|__u16
id|buf_ptr
suffix:semicolon
DECL|member|reserved2
r_int
r_char
id|reserved2
suffix:semicolon
DECL|member|buf_len
id|__u16
id|buf_len
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|arb_dlc_status
r_struct
id|arb_dlc_status
(brace
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|member|reserved1
r_int
r_char
id|reserved1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|station_id
id|__u16
id|station_id
suffix:semicolon
DECL|member|status
id|__u16
id|status
suffix:semicolon
DECL|member|frmr_data
r_int
r_char
id|frmr_data
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|access_prio
r_int
r_char
id|access_prio
suffix:semicolon
DECL|member|rem_addr
r_int
r_char
id|rem_addr
(braket
id|TR_ALEN
)braket
suffix:semicolon
DECL|member|rsap_value
r_int
r_char
id|rsap_value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|arb_ring_stat_change
r_struct
id|arb_ring_stat_change
(brace
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|member|reserved1
r_int
r_char
id|reserved1
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|ring_status
id|__u16
id|ring_status
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|srb_close_adapter
r_struct
id|srb_close_adapter
(brace
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|member|reserved1
r_int
r_char
id|reserved1
suffix:semicolon
DECL|member|ret_code
r_int
r_char
id|ret_code
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|srb_set_funct_addr
r_struct
id|srb_set_funct_addr
(brace
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|member|reserved1
r_int
r_char
id|reserved1
suffix:semicolon
DECL|member|ret_code
r_int
r_char
id|ret_code
suffix:semicolon
DECL|member|reserved2
r_int
r_char
id|reserved2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|funct_address
r_int
r_char
id|funct_address
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
eof
