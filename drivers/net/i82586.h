multiline_comment|/*&n; * Intel 82586 IEEE 802.3 Ethernet LAN Coprocessor.&n; *&n; * See:&n; *&t;Intel Microcommunications 1991&n; *&t;p1-1 to p1-37&n; *&t;Intel order No. 231658&n; *&t;ISBN 1-55512-119-5&n; *&n; *     Unfortunately, the above chapter mentions neither&n; * the System Configuration Pointer (SCP) nor the&n; * Intermediate System Configuration Pointer (ISCP),&n; * so we probably need to look elsewhere for the&n; * whole story -- some recommend the &quot;Intel LAN&n; * Components manual&quot; but I have neither a copy&n; * nor a full reference.  But &quot;elsewhere&quot; may be&n; * in the same publication...&n; *     The description of a later device, the&n; * &quot;82596CA High-Performance 32-Bit Local Area Network&n; * Coprocessor&quot;, (ibid. p1-38 to p1-109) does mention&n; * the SCP and ISCP and also has an i82586 compatibility&n; * mode.  Even more useful is &quot;AP-235 An 82586 Data Link&n; * Driver&quot; (ibid. p1-337 to p1-417).&n; */
DECL|macro|I82586_MEMZ
mdefine_line|#define&t;I82586_MEMZ&t;(64 * 1024)
DECL|macro|I82586_SCP_ADDR
mdefine_line|#define&t;I82586_SCP_ADDR&t;(I82586_MEMZ - sizeof(scp_t))
DECL|macro|ADDR_LEN
mdefine_line|#define&t;ADDR_LEN&t;6
DECL|macro|I82586NULL
mdefine_line|#define&t;I82586NULL&t;0xFFFF
DECL|macro|toff
mdefine_line|#define&t;toff(t,p,f) &t;(unsigned short)((void *)(&amp;((t *)((void *)0 + (p)))-&gt;f) - (void *)0)
multiline_comment|/*&n; * System Configuration Pointer (SCP).&n; */
DECL|typedef|scp_t
r_typedef
r_struct
id|scp_t
id|scp_t
suffix:semicolon
DECL|struct|scp_t
r_struct
id|scp_t
(brace
DECL|member|scp_sysbus
r_int
r_int
id|scp_sysbus
suffix:semicolon
multiline_comment|/* 82586 bus width:&t;*/
DECL|macro|SCP_SY_16BBUS
mdefine_line|#define&t;&t;SCP_SY_16BBUS&t;(0x0 &lt;&lt; 0)&t;/* 16 bits */
DECL|macro|SCP_SY_8BBUS
mdefine_line|#define&t;&t;SCP_SY_8BBUS&t;(0x1 &lt;&lt; 0)&t;/*  8 bits. */
DECL|member|scp_junk
r_int
r_int
id|scp_junk
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|scp_iscpl
r_int
r_int
id|scp_iscpl
suffix:semicolon
multiline_comment|/* lower 16 bits of ISCP_ADDR */
DECL|member|scp_iscph
r_int
r_int
id|scp_iscph
suffix:semicolon
multiline_comment|/* upper 16 bits of ISCP_ADDR */
)brace
suffix:semicolon
multiline_comment|/*&n; * Intermediate System Configuration Pointer (ISCP).&n; */
DECL|typedef|iscp_t
r_typedef
r_struct
id|iscp_t
id|iscp_t
suffix:semicolon
DECL|struct|iscp_t
r_struct
id|iscp_t
(brace
DECL|member|iscp_busy
r_int
r_int
id|iscp_busy
suffix:semicolon
multiline_comment|/* set by CPU before first CA,&t;*/
multiline_comment|/* cleared by 82586 after read.&t;*/
DECL|member|iscp_offset
r_int
r_int
id|iscp_offset
suffix:semicolon
multiline_comment|/* offset of SCB&t;&t;*/
DECL|member|iscp_basel
r_int
r_int
id|iscp_basel
suffix:semicolon
multiline_comment|/* base of SCB&t;&t;&t;*/
DECL|member|iscp_baseh
r_int
r_int
id|iscp_baseh
suffix:semicolon
multiline_comment|/*  &quot;&t;&t;&t;&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * System Control Block (SCB).&n; *&t;The 82586 writes its status to scb_status and then&n; *&t;raises an interrupt to alert the CPU.&n; *&t;The CPU writes a command to scb_command and&n; *&t;then issues a Channel Attention (CA) to alert the 82586.&n; */
DECL|typedef|scb_t
r_typedef
r_struct
id|scb_t
id|scb_t
suffix:semicolon
DECL|struct|scb_t
r_struct
id|scb_t
(brace
DECL|member|scb_status
r_int
r_int
id|scb_status
suffix:semicolon
multiline_comment|/* Status of 82586&t;&t;*/
DECL|macro|SCB_ST_INT
mdefine_line|#define&t;&t;SCB_ST_INT&t;(0xF &lt;&lt; 12)&t;/* Some of:&t;&t;*/
DECL|macro|SCB_ST_CX
mdefine_line|#define&t;&t;SCB_ST_CX&t;(0x1 &lt;&lt; 15)&t;/* Cmd completed&t;*/
DECL|macro|SCB_ST_FR
mdefine_line|#define&t;&t;SCB_ST_FR&t;(0x1 &lt;&lt; 14)&t;/* Frame received&t;*/
DECL|macro|SCB_ST_CNA
mdefine_line|#define&t;&t;SCB_ST_CNA&t;(0x1 &lt;&lt; 13)&t;/* Cmd unit not active&t;*/
DECL|macro|SCB_ST_RNR
mdefine_line|#define&t;&t;SCB_ST_RNR&t;(0x1 &lt;&lt; 12)&t;/* Rcv unit not ready&t;*/
DECL|macro|SCB_ST_JUNK0
mdefine_line|#define&t;&t;SCB_ST_JUNK0&t;(0x1 &lt;&lt; 11)&t;/* 0&t;&t;&t;*/
DECL|macro|SCB_ST_CUS
mdefine_line|#define&t;&t;SCB_ST_CUS&t;(0x7 &lt;&lt;  8)&t;/* Cmd unit status&t;*/
DECL|macro|SCB_ST_CUS_IDLE
mdefine_line|#define&t;&t;&t;SCB_ST_CUS_IDLE&t;(0 &lt;&lt; 8)&t;/* Idle&t;&t;*/
DECL|macro|SCB_ST_CUS_SUSP
mdefine_line|#define&t;&t;&t;SCB_ST_CUS_SUSP&t;(1 &lt;&lt; 8)&t;/* Suspended&t;*/
DECL|macro|SCB_ST_CUS_ACTV
mdefine_line|#define&t;&t;&t;SCB_ST_CUS_ACTV&t;(2 &lt;&lt; 8)&t;/* Active&t;*/
DECL|macro|SCB_ST_JUNK1
mdefine_line|#define&t;&t;SCB_ST_JUNK1&t;(0x1 &lt;&lt;  7)&t;/* 0&t;&t;&t;*/
DECL|macro|SCB_ST_RUS
mdefine_line|#define&t;&t;SCB_ST_RUS&t;(0x7 &lt;&lt;  4)&t;/* Rcv unit status&t;*/
DECL|macro|SCB_ST_RUS_IDLE
mdefine_line|#define&t;&t;&t;SCB_ST_RUS_IDLE&t;(0 &lt;&lt; 4)&t;/* Idle&t;&t;*/
DECL|macro|SCB_ST_RUS_SUSP
mdefine_line|#define&t;&t;&t;SCB_ST_RUS_SUSP&t;(1 &lt;&lt; 4)&t;/* Suspended&t;*/
DECL|macro|SCB_ST_RUS_NRES
mdefine_line|#define&t;&t;&t;SCB_ST_RUS_NRES&t;(2 &lt;&lt; 4)&t;/* No resources&t;*/
DECL|macro|SCB_ST_RUS_RDY
mdefine_line|#define&t;&t;&t;SCB_ST_RUS_RDY&t;(4 &lt;&lt; 4)&t;/* Ready&t;*/
DECL|member|scb_command
r_int
r_int
id|scb_command
suffix:semicolon
multiline_comment|/* Next command&t;&t;&t;*/
DECL|macro|SCB_CMD_ACK_CX
mdefine_line|#define&t;&t;SCB_CMD_ACK_CX&t;(0x1 &lt;&lt; 15)&t;/* Ack cmd completion&t;*/
DECL|macro|SCB_CMD_ACK_FR
mdefine_line|#define&t;&t;SCB_CMD_ACK_FR&t;(0x1 &lt;&lt; 14)&t;/* Ack frame received&t;*/
DECL|macro|SCB_CMD_ACK_CNA
mdefine_line|#define&t;&t;SCB_CMD_ACK_CNA&t;(0x1 &lt;&lt; 13)&t;/* Ack CU not active&t;*/
DECL|macro|SCB_CMD_ACK_RNR
mdefine_line|#define&t;&t;SCB_CMD_ACK_RNR&t;(0x1 &lt;&lt; 12)&t;/* Ack RU not ready&t;*/
DECL|macro|SCB_CMD_JUNKX
mdefine_line|#define&t;&t;SCB_CMD_JUNKX&t;(0x1 &lt;&lt; 11)&t;/* Unused&t;&t;*/
DECL|macro|SCB_CMD_CUC
mdefine_line|#define&t;&t;SCB_CMD_CUC&t;(0x7 &lt;&lt;  8)&t;/* Command Unit command&t;*/
DECL|macro|SCB_CMD_CUC_NOP
mdefine_line|#define&t;&t;&t;SCB_CMD_CUC_NOP&t;(0 &lt;&lt; 8)&t;/* Nop&t;&t;*/
DECL|macro|SCB_CMD_CUC_GO
mdefine_line|#define&t;&t;&t;SCB_CMD_CUC_GO&t;(1 &lt;&lt; 8)&t;/* Start cbl_offset */
DECL|macro|SCB_CMD_CUC_RES
mdefine_line|#define&t;&t;&t;SCB_CMD_CUC_RES&t;(2 &lt;&lt; 8)&t;/* Resume execution */
DECL|macro|SCB_CMD_CUC_SUS
mdefine_line|#define&t;&t;&t;SCB_CMD_CUC_SUS&t;(3 &lt;&lt; 8)&t;/* Suspend   &quot;&t;*/
DECL|macro|SCB_CMD_CUC_ABT
mdefine_line|#define&t;&t;&t;SCB_CMD_CUC_ABT&t;(4 &lt;&lt; 8)&t;/* Abort     &quot;&t;*/
DECL|macro|SCB_CMD_RESET
mdefine_line|#define&t;&t;SCB_CMD_RESET&t;(0x1 &lt;&lt;  7)&t;/* Reset chip (hardware) */
DECL|macro|SCB_CMD_RUC
mdefine_line|#define&t;&t;SCB_CMD_RUC&t;(0x7 &lt;&lt;  4)&t;/* Receive Unit command&t;*/
DECL|macro|SCB_CMD_RUC_NOP
mdefine_line|#define&t;&t;&t;SCB_CMD_RUC_NOP&t;(0 &lt;&lt; 4)&t;/* Nop&t;&t;*/
DECL|macro|SCB_CMD_RUC_GO
mdefine_line|#define&t;&t;&t;SCB_CMD_RUC_GO&t;(1 &lt;&lt; 4)&t;/* Start rfa_offset */
DECL|macro|SCB_CMD_RUC_RES
mdefine_line|#define&t;&t;&t;SCB_CMD_RUC_RES&t;(2 &lt;&lt; 4)&t;/* Resume reception */
DECL|macro|SCB_CMD_RUC_SUS
mdefine_line|#define&t;&t;&t;SCB_CMD_RUC_SUS&t;(3 &lt;&lt; 4)&t;/* Suspend   &quot;&t;*/
DECL|macro|SCB_CMD_RUC_ABT
mdefine_line|#define&t;&t;&t;SCB_CMD_RUC_ABT&t;(4 &lt;&lt; 4)&t;/* Abort     &quot;&t;*/
DECL|member|scb_cbl_offset
r_int
r_int
id|scb_cbl_offset
suffix:semicolon
multiline_comment|/* Offset of first command unit&t;*/
multiline_comment|/* Action Command&t;&t;*/
DECL|member|scb_rfa_offset
r_int
r_int
id|scb_rfa_offset
suffix:semicolon
multiline_comment|/* Offset of first Receive&t;*/
multiline_comment|/* Frame Descriptor in the&t;*/
multiline_comment|/* Receive Frame Area&t;&t;*/
DECL|member|scb_crcerrs
r_int
r_int
id|scb_crcerrs
suffix:semicolon
multiline_comment|/* Properly aligned frames&t;*/
multiline_comment|/* received with a CRC error&t;*/
DECL|member|scb_alnerrs
r_int
r_int
id|scb_alnerrs
suffix:semicolon
multiline_comment|/* Misaligned frames received&t;*/
multiline_comment|/* with a CRC error&t;&t;*/
DECL|member|scb_rscerrs
r_int
r_int
id|scb_rscerrs
suffix:semicolon
multiline_comment|/* Frames lost due to no space&t;*/
DECL|member|scb_ovrnerrs
r_int
r_int
id|scb_ovrnerrs
suffix:semicolon
multiline_comment|/* Frames lost due to slow bus&t;*/
)brace
suffix:semicolon
DECL|macro|scboff
mdefine_line|#define&t;scboff(p,f) &t;toff(scb_t, p, f)
multiline_comment|/*&n; * The eight Action Commands.&n; */
DECL|typedef|acmd_e
r_typedef
r_enum
id|acmd_e
id|acmd_e
suffix:semicolon
DECL|enum|acmd_e
r_enum
id|acmd_e
(brace
DECL|enumerator|acmd_nop
id|acmd_nop
op_assign
l_int|0
comma
multiline_comment|/* Do nothing&t;&t;&t;&t;*/
DECL|enumerator|acmd_ia_setup
id|acmd_ia_setup
op_assign
l_int|1
comma
multiline_comment|/* Load an (ethernet) address into the&t;*/
multiline_comment|/* 82586&t;&t;&t;&t;*/
DECL|enumerator|acmd_configure
id|acmd_configure
op_assign
l_int|2
comma
multiline_comment|/* Update the 82586 operating parameters */
DECL|enumerator|acmd_mc_setup
id|acmd_mc_setup
op_assign
l_int|3
comma
multiline_comment|/* Load a list of (ethernet) multicast&t;*/
multiline_comment|/* addresses into the 82586&t;&t;*/
DECL|enumerator|acmd_transmit
id|acmd_transmit
op_assign
l_int|4
comma
multiline_comment|/* Transmit a frame&t;&t;&t;*/
DECL|enumerator|acmd_tdr
id|acmd_tdr
op_assign
l_int|5
comma
multiline_comment|/* Perform a Time Domain Reflectometer&t;*/
multiline_comment|/* test on the serial link&t;&t;*/
DECL|enumerator|acmd_dump
id|acmd_dump
op_assign
l_int|6
comma
multiline_comment|/* Copy 82586 registers to memory&t;*/
DECL|enumerator|acmd_diagnose
id|acmd_diagnose
op_assign
l_int|7
comma
multiline_comment|/* Run an internal self test&t;&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * Generic Action Command header.&n; */
DECL|typedef|ach_t
r_typedef
r_struct
id|ach_t
id|ach_t
suffix:semicolon
DECL|struct|ach_t
r_struct
id|ach_t
(brace
DECL|member|ac_status
r_int
r_int
id|ac_status
suffix:semicolon
multiline_comment|/* Command status:&t;*/
DECL|macro|AC_SFLD_C
mdefine_line|#define&t;&t;AC_SFLD_C&t;(0x1 &lt;&lt; 15)&t;/* Command completed&t;*/
DECL|macro|AC_SFLD_B
mdefine_line|#define&t;&t;AC_SFLD_B&t;(0x1 &lt;&lt; 14)&t;/* Busy executing&t;*/
DECL|macro|AC_SFLD_OK
mdefine_line|#define&t;&t;AC_SFLD_OK&t;(0x1 &lt;&lt; 13)&t;/* Completed error free&t;*/
DECL|macro|AC_SFLD_A
mdefine_line|#define&t;&t;AC_SFLD_A&t;(0x1 &lt;&lt; 12)&t;/* Command aborted&t;*/
DECL|macro|AC_SFLD_FAIL
mdefine_line|#define&t;&t;AC_SFLD_FAIL&t;(0x1 &lt;&lt; 11)&t;/* Selftest failed&t;*/
DECL|macro|AC_SFLD_S10
mdefine_line|#define&t;&t;AC_SFLD_S10&t;(0x1 &lt;&lt; 10)&t;/* No carrier sense&t;*/
multiline_comment|/* during transmission&t;*/
DECL|macro|AC_SFLD_S9
mdefine_line|#define&t;&t;AC_SFLD_S9&t;(0x1 &lt;&lt;  9)&t;/* Tx unsuccessful:&t;*/
multiline_comment|/* (stopped) lost CTS&t;*/
DECL|macro|AC_SFLD_S8
mdefine_line|#define&t;&t;AC_SFLD_S8&t;(0x1 &lt;&lt;  8)&t;/* Tx unsuccessful:&t;*/
multiline_comment|/* (stopped) slow DMA&t;*/
DECL|macro|AC_SFLD_S7
mdefine_line|#define&t;&t;AC_SFLD_S7&t;(0x1 &lt;&lt;  7)&t;/* Tx deferred:&t;&t;*/
multiline_comment|/* other link traffic&t;*/
DECL|macro|AC_SFLD_S6
mdefine_line|#define&t;&t;AC_SFLD_S6&t;(0x1 &lt;&lt;  6)&t;/* Heart Beat: collision */
multiline_comment|/* detect after last tx&t;*/
DECL|macro|AC_SFLD_S5
mdefine_line|#define&t;&t;AC_SFLD_S5&t;(0x1 &lt;&lt;  5)&t;/* Tx stopped:&t;&t;*/
multiline_comment|/* excessive collisions&t;*/
DECL|macro|AC_SFLD_MAXCOL
mdefine_line|#define&t;&t;AC_SFLD_MAXCOL&t;(0xF &lt;&lt;  0)&t;/* Collision count  &t;*/
DECL|member|ac_command
r_int
r_int
id|ac_command
suffix:semicolon
multiline_comment|/* Command specifier:&t;*/
DECL|macro|AC_CFLD_EL
mdefine_line|#define&t;&t;AC_CFLD_EL&t;(0x1 &lt;&lt; 15)&t;/* End of command list&t;*/
DECL|macro|AC_CFLD_S
mdefine_line|#define&t;&t;AC_CFLD_S&t;(0x1 &lt;&lt; 14)&t;/* Suspend on completion */
DECL|macro|AC_CFLD_I
mdefine_line|#define&t;&t;AC_CFLD_I&t;(0x1 &lt;&lt; 13)&t;/* Interrupt on completion */
DECL|macro|AC_CFLD_CMD
mdefine_line|#define&t;&t;AC_CFLD_CMD&t;(0x7 &lt;&lt;  0)&t;/* acmd_e&t;&t;*/
DECL|member|ac_link
r_int
r_int
id|ac_link
suffix:semicolon
multiline_comment|/* Next Action Command&t;*/
)brace
suffix:semicolon
DECL|macro|acoff
mdefine_line|#define&t;acoff(p,f) &t;toff(ach_t, p, f)
multiline_comment|/*&n; * The Nop Action Command.&n; */
DECL|typedef|ac_nop_t
r_typedef
r_struct
id|ac_nop_t
id|ac_nop_t
suffix:semicolon
DECL|struct|ac_nop_t
r_struct
id|ac_nop_t
(brace
DECL|member|nop_h
id|ach_t
id|nop_h
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The IA-Setup Action Command.&n; */
DECL|typedef|ac_ias_t
r_typedef
r_struct
id|ac_ias_t
id|ac_ias_t
suffix:semicolon
DECL|struct|ac_ias_t
r_struct
id|ac_ias_t
(brace
DECL|member|ias_h
id|ach_t
id|ias_h
suffix:semicolon
DECL|member|ias_addr
r_int
r_char
id|ias_addr
(braket
id|ADDR_LEN
)braket
suffix:semicolon
multiline_comment|/* The (ethernet) address&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * The Configure Action Command.&n; */
DECL|typedef|ac_cfg_t
r_typedef
r_struct
id|ac_cfg_t
id|ac_cfg_t
suffix:semicolon
DECL|struct|ac_cfg_t
r_struct
id|ac_cfg_t
(brace
DECL|member|cfg_h
id|ach_t
id|cfg_h
suffix:semicolon
DECL|member|cfg_byte_cnt
r_int
r_char
id|cfg_byte_cnt
suffix:semicolon
multiline_comment|/* Size foll data: 4-12&t;*/
DECL|macro|AC_CFG_BYTE_CNT
mdefine_line|#define&t;AC_CFG_BYTE_CNT(v)&t;(((v) &amp; 0xF) &lt;&lt; 0)
DECL|member|cfg_fifolim
r_int
r_char
id|cfg_fifolim
suffix:semicolon
multiline_comment|/* FIFO threshold&t;*/
DECL|macro|AC_CFG_FIFOLIM
mdefine_line|#define&t;AC_CFG_FIFOLIM(v)&t;(((v) &amp; 0xF) &lt;&lt; 0)
DECL|member|cfg_byte8
r_int
r_char
id|cfg_byte8
suffix:semicolon
DECL|macro|AC_CFG_SAV_BF
mdefine_line|#define&t;AC_CFG_SAV_BF(v) &t;(((v) &amp; 0x1) &lt;&lt; 7)&t;/* Save rxd bad frames&t;*/
DECL|macro|AC_CFG_SRDY
mdefine_line|#define&t;AC_CFG_SRDY(v) &t;&t;(((v) &amp; 0x1) &lt;&lt; 6)&t;/* SRDY/ARDY pin means&t;*/
multiline_comment|/* external sync.&t;*/
DECL|member|cfg_byte9
r_int
r_char
id|cfg_byte9
suffix:semicolon
DECL|macro|AC_CFG_ELPBCK
mdefine_line|#define&t;AC_CFG_ELPBCK(v)&t;(((v) &amp; 0x1) &lt;&lt; 7)&t;/* External loopback&t;*/
DECL|macro|AC_CFG_ILPBCK
mdefine_line|#define&t;AC_CFG_ILPBCK(v)&t;(((v) &amp; 0x1) &lt;&lt; 6)&t;/* Internal loopback&t;*/
DECL|macro|AC_CFG_PRELEN
mdefine_line|#define&t;AC_CFG_PRELEN(v)&t;(((v) &amp; 0x3) &lt;&lt; 4)&t;/* Preamble length&t;*/
DECL|macro|AC_CFG_PLEN_2
mdefine_line|#define&t;&t;AC_CFG_PLEN_2&t;&t;0&t;&t;/*  2 bytes&t;*/
DECL|macro|AC_CFG_PLEN_4
mdefine_line|#define&t;&t;AC_CFG_PLEN_4&t;&t;1&t;&t;/*  4 bytes&t;*/
DECL|macro|AC_CFG_PLEN_8
mdefine_line|#define&t;&t;AC_CFG_PLEN_8&t;&t;2&t;&t;/*  8 bytes&t;*/
DECL|macro|AC_CFG_PLEN_16
mdefine_line|#define&t;&t;AC_CFG_PLEN_16&t;&t;3&t;&t;/* 16 bytes&t;*/
DECL|macro|AC_CFG_ALOC
mdefine_line|#define&t;AC_CFG_ALOC(v)&t;&t;(((v) &amp; 0x1) &lt;&lt; 3)&t;/* Addr/len data is&t;*/
multiline_comment|/* explicit in buffers&t;*/
DECL|macro|AC_CFG_ADDRLEN
mdefine_line|#define&t;AC_CFG_ADDRLEN(v)&t;(((v) &amp; 0x7) &lt;&lt; 0)&t;/* Bytes per address&t;*/
DECL|member|cfg_byte10
r_int
r_char
id|cfg_byte10
suffix:semicolon
DECL|macro|AC_CFG_BOFMET
mdefine_line|#define&t;AC_CFG_BOFMET(v)&t;(((v) &amp; 0x1) &lt;&lt; 7)&t;/* Use alternate expo.&t;*/
multiline_comment|/* backoff method&t;*/
DECL|macro|AC_CFG_ACR
mdefine_line|#define&t;AC_CFG_ACR(v)&t;&t;(((v) &amp; 0x7) &lt;&lt; 4)&t;/* Accelerated cont. res. */
DECL|macro|AC_CFG_LINPRIO
mdefine_line|#define&t;AC_CFG_LINPRIO(v)&t;(((v) &amp; 0x7) &lt;&lt; 0)&t;/* Linear priority&t;*/
DECL|member|cfg_ifs
r_int
r_char
id|cfg_ifs
suffix:semicolon
multiline_comment|/* Interframe spacing&t;&t;*/
DECL|member|cfg_slotl
r_int
r_char
id|cfg_slotl
suffix:semicolon
multiline_comment|/* Slot time (low byte)&t;&t;*/
DECL|member|cfg_byte13
r_int
r_char
id|cfg_byte13
suffix:semicolon
DECL|macro|AC_CFG_RETRYNUM
mdefine_line|#define&t;AC_CFG_RETRYNUM(v)&t;(((v) &amp; 0xF) &lt;&lt; 4)&t;/* Max. collision retry&t;*/
DECL|macro|AC_CFG_SLTTMHI
mdefine_line|#define&t;AC_CFG_SLTTMHI(v)&t;(((v) &amp; 0x7) &lt;&lt; 0)&t;/* Slot time (high bits) */
DECL|member|cfg_byte14
r_int
r_char
id|cfg_byte14
suffix:semicolon
DECL|macro|AC_CFG_FLGPAD
mdefine_line|#define&t;AC_CFG_FLGPAD(v)&t;(((v) &amp; 0x1) &lt;&lt; 7)&t;/* Pad with HDLC flags&t;*/
DECL|macro|AC_CFG_BTSTF
mdefine_line|#define&t;AC_CFG_BTSTF(v)&t;&t;(((v) &amp; 0x1) &lt;&lt; 6)&t;/* Do HDLC bitstuffing&t;*/
DECL|macro|AC_CFG_CRC16
mdefine_line|#define&t;AC_CFG_CRC16(v)&t;&t;(((v) &amp; 0x1) &lt;&lt; 5)&t;/* 16 bit CCITT CRC&t;*/
DECL|macro|AC_CFG_NCRC
mdefine_line|#define&t;AC_CFG_NCRC(v)&t;&t;(((v) &amp; 0x1) &lt;&lt; 4)&t;/* Insert no CRC&t;*/
DECL|macro|AC_CFG_TNCRS
mdefine_line|#define&t;AC_CFG_TNCRS(v)&t;&t;(((v) &amp; 0x1) &lt;&lt; 3)&t;/* Tx even if no carrier */
DECL|macro|AC_CFG_MANCH
mdefine_line|#define&t;AC_CFG_MANCH(v)&t;&t;(((v) &amp; 0x1) &lt;&lt; 2)&t;/* Manchester coding&t;*/
DECL|macro|AC_CFG_BCDIS
mdefine_line|#define&t;AC_CFG_BCDIS(v)&t;&t;(((v) &amp; 0x1) &lt;&lt; 1)&t;/* Disable broadcast&t;*/
DECL|macro|AC_CFG_PRM
mdefine_line|#define&t;AC_CFG_PRM(v)&t;&t;(((v) &amp; 0x1) &lt;&lt; 0)&t;/* Promiscuous mode&t;*/
DECL|member|cfg_byte15
r_int
r_char
id|cfg_byte15
suffix:semicolon
DECL|macro|AC_CFG_ICDS
mdefine_line|#define&t;AC_CFG_ICDS(v)&t;&t;(((v) &amp; 0x1) &lt;&lt; 7)&t;/* Internal collision&t;*/
multiline_comment|/* detect source&t;*/
DECL|macro|AC_CFG_CDTF
mdefine_line|#define&t;AC_CFG_CDTF(v)&t;&t;(((v) &amp; 0x7) &lt;&lt; 4)&t;/* Collision detect&t;*/
multiline_comment|/* filter in bit times&t;*/
DECL|macro|AC_CFG_ICSS
mdefine_line|#define&t;AC_CFG_ICSS(v)&t;&t;(((v) &amp; 0x1) &lt;&lt; 3)&t;/* Internal carrier&t;*/
multiline_comment|/* sense source&t;&t;*/
DECL|macro|AC_CFG_CSTF
mdefine_line|#define&t;AC_CFG_CSTF(v)&t;&t;(((v) &amp; 0x7) &lt;&lt; 0)&t;/* Carrier sense&t;*/
multiline_comment|/* filter in bit times&t;*/
DECL|member|cfg_min_frm_len
r_int
r_int
id|cfg_min_frm_len
suffix:semicolon
DECL|macro|AC_CFG_MNFRM
mdefine_line|#define&t;AC_CFG_MNFRM(v)&t;&t;(((v) &amp; 0xFF) &lt;&lt; 0)&t;/* Min. bytes/frame (&lt;= 255) */
)brace
suffix:semicolon
multiline_comment|/*&n; * The MC-Setup Action Command.&n; */
DECL|typedef|ac_mcs_t
r_typedef
r_struct
id|ac_mcs_t
id|ac_mcs_t
suffix:semicolon
DECL|struct|ac_mcs_t
r_struct
id|ac_mcs_t
(brace
DECL|member|mcs_h
id|ach_t
id|mcs_h
suffix:semicolon
DECL|member|mcs_cnt
r_int
r_int
id|mcs_cnt
suffix:semicolon
multiline_comment|/* No. of bytes of MC addresses&t;*/
macro_line|#if 0
r_int
r_char
id|mcs_data
(braket
id|ADDR_LEN
)braket
suffix:semicolon
multiline_comment|/* The first MC address ..&t;*/
dot
dot
dot
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|I82586_MAX_MULTICAST_ADDRESSES
mdefine_line|#define I82586_MAX_MULTICAST_ADDRESSES&t;128&t;/* Hardware hashed filter */
multiline_comment|/*&n; * The Transmit Action Command.&n; */
DECL|typedef|ac_tx_t
r_typedef
r_struct
id|ac_tx_t
id|ac_tx_t
suffix:semicolon
DECL|struct|ac_tx_t
r_struct
id|ac_tx_t
(brace
DECL|member|tx_h
id|ach_t
id|tx_h
suffix:semicolon
DECL|member|tx_tbd_offset
r_int
r_int
id|tx_tbd_offset
suffix:semicolon
multiline_comment|/* Address of list of buffers.&t;*/
macro_line|#if&t;0
id|Linux
id|packets
id|are
id|passed
id|down
id|with
id|the
id|destination
id|MAC
id|address
op_logical_and
id|length
op_div
id|type
id|field
id|already
id|prepended
id|to
id|the
id|data
comma
id|so
id|we
r_do
op_logical_neg
id|need
id|to
id|insert
id|it
dot
id|Consistent
id|with
id|this
id|we
id|must
id|also
id|set
id|the
id|AC_CFG_ALOC
c_func
(paren
dot
dot
)paren
id|flag
id|during
id|the
id|ac_cfg_t
id|action
id|command
dot
r_int
r_char
id|tx_addr
(braket
id|ADDR_LEN
)braket
suffix:semicolon
multiline_comment|/* The frame dest. address&t;*/
r_int
r_int
id|tx_length
suffix:semicolon
multiline_comment|/* The frame length&t;&t;*/
macro_line|#endif&t;/* 0 */
)brace
suffix:semicolon
multiline_comment|/*&n; * The Time Domain Reflectometer Action Command.&n; */
DECL|typedef|ac_tdr_t
r_typedef
r_struct
id|ac_tdr_t
id|ac_tdr_t
suffix:semicolon
DECL|struct|ac_tdr_t
r_struct
id|ac_tdr_t
(brace
DECL|member|tdr_h
id|ach_t
id|tdr_h
suffix:semicolon
DECL|member|tdr_result
r_int
r_int
id|tdr_result
suffix:semicolon
multiline_comment|/* Result.&t;*/
DECL|macro|AC_TDR_LNK_OK
mdefine_line|#define&t;&t;AC_TDR_LNK_OK&t;(0x1 &lt;&lt; 15)&t;/* No link problem&t;*/
DECL|macro|AC_TDR_XCVR_PRB
mdefine_line|#define&t;&t;AC_TDR_XCVR_PRB&t;(0x1 &lt;&lt; 14)&t;/* Txcvr cable problem&t;*/
DECL|macro|AC_TDR_ET_OPN
mdefine_line|#define&t;&t;AC_TDR_ET_OPN&t;(0x1 &lt;&lt; 13)&t;/* Open on the link&t;*/
DECL|macro|AC_TDR_ET_SRT
mdefine_line|#define&t;&t;AC_TDR_ET_SRT&t;(0x1 &lt;&lt; 12)&t;/* Short on the link&t;*/
DECL|macro|AC_TDR_TIME
mdefine_line|#define&t;&t;AC_TDR_TIME&t;(0x7FF &lt;&lt; 0)&t;/* Distance to problem&t;*/
multiline_comment|/* site&t;in transmit&t;*/
multiline_comment|/* clock cycles&t;&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * The Dump Action Command.&n; */
DECL|typedef|ac_dmp_t
r_typedef
r_struct
id|ac_dmp_t
id|ac_dmp_t
suffix:semicolon
DECL|struct|ac_dmp_t
r_struct
id|ac_dmp_t
(brace
DECL|member|dmp_h
id|ach_t
id|dmp_h
suffix:semicolon
DECL|member|dmp_offset
r_int
r_int
id|dmp_offset
suffix:semicolon
multiline_comment|/* Result.&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * Size of the result of the dump command.&n; */
DECL|macro|DUMPBYTES
mdefine_line|#define&t;DUMPBYTES&t;170
multiline_comment|/*&n; * The Diagnose Action Command.&n; */
DECL|typedef|ac_dgn_t
r_typedef
r_struct
id|ac_dgn_t
id|ac_dgn_t
suffix:semicolon
DECL|struct|ac_dgn_t
r_struct
id|ac_dgn_t
(brace
DECL|member|dgn_h
id|ach_t
id|dgn_h
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Transmit Buffer Descriptor (TBD).&n; */
DECL|typedef|tbd_t
r_typedef
r_struct
id|tbd_t
id|tbd_t
suffix:semicolon
DECL|struct|tbd_t
r_struct
id|tbd_t
(brace
DECL|member|tbd_status
r_int
r_int
id|tbd_status
suffix:semicolon
multiline_comment|/* Written by the CPU&t;*/
DECL|macro|TBD_STATUS_EOF
mdefine_line|#define&t;&t;TBD_STATUS_EOF&t;(0x1 &lt;&lt; 15)&t;/* This TBD is the&t;*/
multiline_comment|/* last for this frame&t;*/
DECL|macro|TBD_STATUS_ACNT
mdefine_line|#define&t;&t;TBD_STATUS_ACNT&t;(0x3FFF &lt;&lt; 0)&t;/* Actual count of data&t;*/
multiline_comment|/* bytes in this buffer&t;*/
DECL|member|tbd_next_bd_offset
r_int
r_int
id|tbd_next_bd_offset
suffix:semicolon
multiline_comment|/* Next in list&t;&t;*/
DECL|member|tbd_bufl
r_int
r_int
id|tbd_bufl
suffix:semicolon
multiline_comment|/* Buffer address (low)&t;*/
DECL|member|tbd_bufh
r_int
r_int
id|tbd_bufh
suffix:semicolon
multiline_comment|/*    &quot;&t;     &quot;&t;(high)&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * Receive Buffer Descriptor (RBD).&n; */
DECL|typedef|rbd_t
r_typedef
r_struct
id|rbd_t
id|rbd_t
suffix:semicolon
DECL|struct|rbd_t
r_struct
id|rbd_t
(brace
DECL|member|rbd_status
r_int
r_int
id|rbd_status
suffix:semicolon
multiline_comment|/* Written by the 82586&t;*/
DECL|macro|RBD_STATUS_EOF
mdefine_line|#define&t;&t;RBD_STATUS_EOF&t;(0x1 &lt;&lt; 15)&t;/* This RBD is the&t;*/
multiline_comment|/* last for this frame&t;*/
DECL|macro|RBD_STATUS_F
mdefine_line|#define&t;&t;RBD_STATUS_F&t;(0x1 &lt;&lt; 14)&t;/* ACNT field is valid&t;*/
DECL|macro|RBD_STATUS_ACNT
mdefine_line|#define&t;&t;RBD_STATUS_ACNT&t;(0x3FFF &lt;&lt; 0)&t;/* Actual no. of data&t;*/
multiline_comment|/* bytes in this buffer&t;*/
DECL|member|rbd_next_rbd_offset
r_int
r_int
id|rbd_next_rbd_offset
suffix:semicolon
multiline_comment|/* Next rbd in list&t;*/
DECL|member|rbd_bufl
r_int
r_int
id|rbd_bufl
suffix:semicolon
multiline_comment|/* Data pointer (low)&t;*/
DECL|member|rbd_bufh
r_int
r_int
id|rbd_bufh
suffix:semicolon
multiline_comment|/*  &quot;&t;   &quot;    (high)&t;*/
DECL|member|rbd_el_size
r_int
r_int
id|rbd_el_size
suffix:semicolon
multiline_comment|/* EL+Data buf. size&t;*/
DECL|macro|RBD_EL
mdefine_line|#define&t;&t;RBD_EL&t;(0x1 &lt;&lt; 15)&t;&t;/* This BD is the&t;*/
multiline_comment|/* last in the list&t;*/
DECL|macro|RBD_SIZE
mdefine_line|#define&t;&t;RBD_SIZE (0x3FFF &lt;&lt; 0)&t;&t;/* No. of bytes the&t;*/
multiline_comment|/* buffer can hold&t;*/
)brace
suffix:semicolon
DECL|macro|rbdoff
mdefine_line|#define&t;rbdoff(p,f) &t;toff(rbd_t, p, f)
multiline_comment|/*&n; * Frame Descriptor (FD).&n; */
DECL|typedef|fd_t
r_typedef
r_struct
id|fd_t
id|fd_t
suffix:semicolon
DECL|struct|fd_t
r_struct
id|fd_t
(brace
DECL|member|fd_status
r_int
r_int
id|fd_status
suffix:semicolon
multiline_comment|/* Written by the 82586&t;*/
DECL|macro|FD_STATUS_C
mdefine_line|#define&t;&t;FD_STATUS_C&t;(0x1 &lt;&lt; 15)&t;/* Completed storing frame */
DECL|macro|FD_STATUS_B
mdefine_line|#define&t;&t;FD_STATUS_B&t;(0x1 &lt;&lt; 14)&t;/* FD was consumed by RU */
DECL|macro|FD_STATUS_OK
mdefine_line|#define&t;&t;FD_STATUS_OK&t;(0x1 &lt;&lt; 13)&t;/* Frame rxd successfully */
DECL|macro|FD_STATUS_S11
mdefine_line|#define&t;&t;FD_STATUS_S11&t;(0x1 &lt;&lt; 11)&t;/* CRC error&t;&t;*/
DECL|macro|FD_STATUS_S10
mdefine_line|#define&t;&t;FD_STATUS_S10&t;(0x1 &lt;&lt; 10)&t;/* Alignment error&t;*/
DECL|macro|FD_STATUS_S9
mdefine_line|#define&t;&t;FD_STATUS_S9&t;(0x1 &lt;&lt;  9)&t;/* Ran out of resources&t;*/
DECL|macro|FD_STATUS_S8
mdefine_line|#define&t;&t;FD_STATUS_S8&t;(0x1 &lt;&lt;  8)&t;/* Rx DMA overrun&t;*/
DECL|macro|FD_STATUS_S7
mdefine_line|#define&t;&t;FD_STATUS_S7&t;(0x1 &lt;&lt;  7)&t;/* Frame too short&t;*/
DECL|macro|FD_STATUS_S6
mdefine_line|#define&t;&t;FD_STATUS_S6&t;(0x1 &lt;&lt;  6)&t;/* No EOF flag&t;&t;*/
DECL|member|fd_command
r_int
r_int
id|fd_command
suffix:semicolon
multiline_comment|/* Command&t;&t;*/
DECL|macro|FD_COMMAND_EL
mdefine_line|#define&t;&t;FD_COMMAND_EL&t;(0x1 &lt;&lt; 15)&t;/* Last FD in list&t;*/
DECL|macro|FD_COMMAND_S
mdefine_line|#define&t;&t;FD_COMMAND_S&t;(0x1 &lt;&lt; 14)&t;/* Suspend RU after rx&t;*/
DECL|member|fd_link_offset
r_int
r_int
id|fd_link_offset
suffix:semicolon
multiline_comment|/* Next FD&t;&t;*/
DECL|member|fd_rbd_offset
r_int
r_int
id|fd_rbd_offset
suffix:semicolon
multiline_comment|/* First RBD (data)&t;*/
multiline_comment|/* Prepared by CPU,&t;*/
multiline_comment|/* updated by 82586&t;*/
macro_line|#if&t;0
id|I
id|think
id|the
id|rest
id|is
id|unused
id|since
id|we
id|have
id|set
id|AC_CFG_ALOC
c_func
(paren
dot
dot
)paren
dot
id|However
comma
id|just
id|in
r_case
comma
id|we
id|leave
id|the
id|space
dot
macro_line|#endif&t;/* 0 */
DECL|member|fd_dest
r_int
r_char
id|fd_dest
(braket
id|ADDR_LEN
)braket
suffix:semicolon
multiline_comment|/* Destination address&t;*/
multiline_comment|/* Written by 82586&t;*/
DECL|member|fd_src
r_int
r_char
id|fd_src
(braket
id|ADDR_LEN
)braket
suffix:semicolon
multiline_comment|/* Source address&t;*/
multiline_comment|/* Written by 82586&t;*/
DECL|member|fd_length
r_int
r_int
id|fd_length
suffix:semicolon
multiline_comment|/* Frame length or type&t;*/
multiline_comment|/* Written by 82586&t;*/
)brace
suffix:semicolon
DECL|macro|fdoff
mdefine_line|#define&t;fdoff(p,f) &t;toff(fd_t, p, f)
multiline_comment|/*&n; * This software may only be used and distributed&n; * according to the terms of the GNU Public License.&n; *&n; * For more details, see wavelan.c.&n; */
eof
