macro_line|#ifndef _3c523_INCLUDE_
DECL|macro|_3c523_INCLUDE_
mdefine_line|#define _3c523_INCLUDE_
multiline_comment|/*&n;&t;This is basically a hacked version of ni52.h, for the 3c523&n;&t;Etherlink/MC.&n;*/
multiline_comment|/*&n; * Intel i82586 Ethernet definitions&n; *&n; * This is an extension to the Linux operating system, and is covered by the&n; * same GNU General Public License that covers that work.&n; *&n; * Copyright 1995 by Chris Beauregard (cpbeaure@undergrad.math.uwaterloo.ca)&n; *&n; * See 3c523.c for details.&n; *&n; * $Header: /home/chrisb/linux-1.2.13-3c523/drivers/net/RCS/3c523.h,v 1.6 1996/01/20 05:09:00 chrisb Exp chrisb $&n; */
multiline_comment|/*&n; * where to find the System Configuration Pointer (SCP)&n; */
DECL|macro|SCP_DEFAULT_ADDRESS
mdefine_line|#define SCP_DEFAULT_ADDRESS 0xfffff4
multiline_comment|/*&n; * System Configuration Pointer Struct&n; */
DECL|struct|scp_struct
r_struct
id|scp_struct
(brace
DECL|member|zero_dum0
r_int
r_int
id|zero_dum0
suffix:semicolon
multiline_comment|/* has to be zero */
DECL|member|sysbus
r_int
r_char
id|sysbus
suffix:semicolon
multiline_comment|/* 0=16Bit,1=8Bit */
DECL|member|zero_dum1
r_int
r_char
id|zero_dum1
suffix:semicolon
multiline_comment|/* has to be zero for 586 */
DECL|member|zero_dum2
r_int
r_int
id|zero_dum2
suffix:semicolon
DECL|member|zero_dum3
r_int
r_int
id|zero_dum3
suffix:semicolon
DECL|member|iscp
r_char
op_star
id|iscp
suffix:semicolon
multiline_comment|/* pointer to the iscp-block */
)brace
suffix:semicolon
multiline_comment|/*&n; * Intermediate System Configuration Pointer (ISCP)&n; */
DECL|struct|iscp_struct
r_struct
id|iscp_struct
(brace
DECL|member|busy
r_int
r_char
id|busy
suffix:semicolon
multiline_comment|/* 586 clears after successful init */
DECL|member|zero_dummy
r_int
r_char
id|zero_dummy
suffix:semicolon
multiline_comment|/* hast to be zero */
DECL|member|scb_offset
r_int
r_int
id|scb_offset
suffix:semicolon
multiline_comment|/* pointeroffset to the scb_base */
DECL|member|scb_base
r_char
op_star
id|scb_base
suffix:semicolon
multiline_comment|/* base-address of all 16-bit offsets */
)brace
suffix:semicolon
multiline_comment|/*&n; * System Control Block (SCB)&n; */
DECL|struct|scb_struct
r_struct
id|scb_struct
(brace
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/* status word */
DECL|member|cmd
r_int
r_int
id|cmd
suffix:semicolon
multiline_comment|/* command word */
DECL|member|cbl_offset
r_int
r_int
id|cbl_offset
suffix:semicolon
multiline_comment|/* pointeroffset, command block list */
DECL|member|rfa_offset
r_int
r_int
id|rfa_offset
suffix:semicolon
multiline_comment|/* pointeroffset, receive frame area */
DECL|member|crc_errs
r_int
r_int
id|crc_errs
suffix:semicolon
multiline_comment|/* CRC-Error counter */
DECL|member|aln_errs
r_int
r_int
id|aln_errs
suffix:semicolon
multiline_comment|/* alignmenterror counter */
DECL|member|rsc_errs
r_int
r_int
id|rsc_errs
suffix:semicolon
multiline_comment|/* Resourceerror counter */
DECL|member|ovrn_errs
r_int
r_int
id|ovrn_errs
suffix:semicolon
multiline_comment|/* OVerrunerror counter */
)brace
suffix:semicolon
multiline_comment|/*&n; * possible command values for the command word&n; */
DECL|macro|RUC_MASK
mdefine_line|#define RUC_MASK&t;0x0070&t;/* mask for RU commands */
DECL|macro|RUC_NOP
mdefine_line|#define RUC_NOP&t;&t;0x0000&t;/* NOP-command */
DECL|macro|RUC_START
mdefine_line|#define RUC_START&t;0x0010&t;/* start RU */
DECL|macro|RUC_RESUME
mdefine_line|#define RUC_RESUME&t;0x0020&t;/* resume RU after suspend */
DECL|macro|RUC_SUSPEND
mdefine_line|#define RUC_SUSPEND&t;0x0030&t;/* suspend RU */
DECL|macro|RUC_ABORT
mdefine_line|#define RUC_ABORT&t;0x0040&t;/* abort receiver operation immediately */
DECL|macro|CUC_MASK
mdefine_line|#define CUC_MASK&t;0x0700&t;/* mask for CU command */
DECL|macro|CUC_NOP
mdefine_line|#define CUC_NOP&t;&t;0x0000&t;/* NOP-command */
DECL|macro|CUC_START
mdefine_line|#define CUC_START&t;0x0100&t;/* start execution of 1. cmd on the CBL */
DECL|macro|CUC_RESUME
mdefine_line|#define CUC_RESUME&t;0x0200&t;/* resume after suspend */
DECL|macro|CUC_SUSPEND
mdefine_line|#define CUC_SUSPEND&t;0x0300&t;/* Suspend CU */
DECL|macro|CUC_ABORT
mdefine_line|#define CUC_ABORT&t;0x0400&t;/* abort command operation immediately */
DECL|macro|ACK_MASK
mdefine_line|#define ACK_MASK&t;0xf000&t;/* mask for ACK command */
DECL|macro|ACK_CX
mdefine_line|#define ACK_CX&t;&t;0x8000&t;/* acknowledges STAT_CX */
DECL|macro|ACK_FR
mdefine_line|#define ACK_FR&t;&t;0x4000&t;/* ack. STAT_FR */
DECL|macro|ACK_CNA
mdefine_line|#define ACK_CNA&t;&t;0x2000&t;/* ack. STAT_CNA */
DECL|macro|ACK_RNR
mdefine_line|#define ACK_RNR&t;&t;0x1000&t;/* ack. STAT_RNR */
multiline_comment|/*&n; * possible status values for the status word&n; */
DECL|macro|STAT_MASK
mdefine_line|#define STAT_MASK&t;0xf000&t;/* mask for cause of interrupt */
DECL|macro|STAT_CX
mdefine_line|#define STAT_CX&t;&t;0x8000&t;/* CU finished cmd with its I bit set */
DECL|macro|STAT_FR
mdefine_line|#define STAT_FR&t;&t;0x4000&t;/* RU finished receiving a frame */
DECL|macro|STAT_CNA
mdefine_line|#define STAT_CNA&t;0x2000&t;/* CU left active state */
DECL|macro|STAT_RNR
mdefine_line|#define STAT_RNR&t;0x1000&t;/* RU left ready state */
DECL|macro|CU_STATUS
mdefine_line|#define CU_STATUS&t;0x700&t;/* CU status, 0=idle */
DECL|macro|CU_SUSPEND
mdefine_line|#define CU_SUSPEND&t;0x100&t;/* CU is suspended */
DECL|macro|CU_ACTIVE
mdefine_line|#define CU_ACTIVE&t;0x200&t;/* CU is active */
DECL|macro|RU_STATUS
mdefine_line|#define RU_STATUS&t;0x70&t;/* RU status, 0=idle */
DECL|macro|RU_SUSPEND
mdefine_line|#define RU_SUSPEND&t;0x10&t;/* RU suspended */
DECL|macro|RU_NOSPACE
mdefine_line|#define RU_NOSPACE&t;0x20&t;/* RU no resources */
DECL|macro|RU_READY
mdefine_line|#define RU_READY&t;0x40&t;/* RU is ready */
multiline_comment|/*&n; * Receive Frame Descriptor (RFD)&n; */
DECL|struct|rfd_struct
r_struct
id|rfd_struct
(brace
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/* status word */
DECL|member|last
r_int
r_int
id|last
suffix:semicolon
multiline_comment|/* Bit15,Last Frame on List / Bit14,suspend */
DECL|member|next
r_int
r_int
id|next
suffix:semicolon
multiline_comment|/* linkoffset to next RFD */
DECL|member|rbd_offset
r_int
r_int
id|rbd_offset
suffix:semicolon
multiline_comment|/* pointeroffset to RBD-buffer */
DECL|member|dest
r_int
r_char
id|dest
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* ethernet-address, destination */
DECL|member|source
r_int
r_char
id|source
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* ethernet-address, source */
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* 802.3 frame-length */
DECL|member|zero_dummy
r_int
r_int
id|zero_dummy
suffix:semicolon
multiline_comment|/* dummy */
)brace
suffix:semicolon
DECL|macro|RFD_LAST
mdefine_line|#define RFD_LAST     0x8000&t;/* last: last rfd in the list */
DECL|macro|RFD_SUSP
mdefine_line|#define RFD_SUSP     0x4000&t;/* last: suspend RU after  */
DECL|macro|RFD_ERRMASK
mdefine_line|#define RFD_ERRMASK  0x0fe1     /* status: errormask */
DECL|macro|RFD_MATCHADD
mdefine_line|#define RFD_MATCHADD 0x0002     /* status: Destinationaddress !matches IA */
DECL|macro|RFD_RNR
mdefine_line|#define RFD_RNR      0x0200&t;/* status: receiver out of resources */
multiline_comment|/*&n; * Receive Buffer Descriptor (RBD)&n; */
DECL|struct|rbd_struct
r_struct
id|rbd_struct
(brace
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/* status word,number of used bytes in buff */
DECL|member|next
r_int
r_int
id|next
suffix:semicolon
multiline_comment|/* pointeroffset to next RBD */
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
multiline_comment|/* receive buffer address pointer */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size of this buffer */
DECL|member|zero_dummy
r_int
r_int
id|zero_dummy
suffix:semicolon
multiline_comment|/* dummy */
)brace
suffix:semicolon
DECL|macro|RBD_LAST
mdefine_line|#define RBD_LAST&t;0x8000&t;/* last buffer */
DECL|macro|RBD_USED
mdefine_line|#define RBD_USED&t;0x4000&t;/* this buffer has data */
DECL|macro|RBD_MASK
mdefine_line|#define RBD_MASK&t;0x3fff&t;/* size-mask for length */
multiline_comment|/*&n; * Statusvalues for Commands/RFD&n; */
DECL|macro|STAT_COMPL
mdefine_line|#define STAT_COMPL   0x8000&t;/* status: frame/command is complete */
DECL|macro|STAT_BUSY
mdefine_line|#define STAT_BUSY    0x4000&t;/* status: frame/command is busy */
DECL|macro|STAT_OK
mdefine_line|#define STAT_OK      0x2000&t;/* status: frame/command is ok */
multiline_comment|/*&n; * Action-Commands&n; */
DECL|macro|CMD_NOP
mdefine_line|#define CMD_NOP&t;&t;0x0000&t;/* NOP */
DECL|macro|CMD_IASETUP
mdefine_line|#define CMD_IASETUP&t;0x0001&t;/* initial address setup command */
DECL|macro|CMD_CONFIGURE
mdefine_line|#define CMD_CONFIGURE&t;0x0002&t;/* configure command */
DECL|macro|CMD_MCSETUP
mdefine_line|#define CMD_MCSETUP&t;0x0003&t;/* MC setup command */
DECL|macro|CMD_XMIT
mdefine_line|#define CMD_XMIT&t;0x0004&t;/* transmit command */
DECL|macro|CMD_TDR
mdefine_line|#define CMD_TDR&t;&t;0x0005&t;/* time domain reflectometer (TDR) command */
DECL|macro|CMD_DUMP
mdefine_line|#define CMD_DUMP&t;0x0006&t;/* dump command */
DECL|macro|CMD_DIAGNOSE
mdefine_line|#define CMD_DIAGNOSE&t;0x0007&t;/* diagnose command */
multiline_comment|/*&n; * Action command bits&n; */
DECL|macro|CMD_LAST
mdefine_line|#define CMD_LAST&t;0x8000&t;/* indicates last command in the CBL */
DECL|macro|CMD_SUSPEND
mdefine_line|#define CMD_SUSPEND&t;0x4000&t;/* suspend CU after this CB */
DECL|macro|CMD_INT
mdefine_line|#define CMD_INT&t;&t;0x2000&t;/* generate interrupt after execution */
multiline_comment|/*&n; * NOP - command&n; */
DECL|struct|nop_cmd_struct
r_struct
id|nop_cmd_struct
(brace
DECL|member|cmd_status
r_int
r_int
id|cmd_status
suffix:semicolon
multiline_comment|/* status of this command */
DECL|member|cmd_cmd
r_int
r_int
id|cmd_cmd
suffix:semicolon
multiline_comment|/* the command itself (+bits) */
DECL|member|cmd_link
r_int
r_int
id|cmd_link
suffix:semicolon
multiline_comment|/* offsetpointer to next command */
)brace
suffix:semicolon
multiline_comment|/*&n; * IA Setup command&n; */
DECL|struct|iasetup_cmd_struct
r_struct
id|iasetup_cmd_struct
(brace
DECL|member|cmd_status
r_int
r_int
id|cmd_status
suffix:semicolon
DECL|member|cmd_cmd
r_int
r_int
id|cmd_cmd
suffix:semicolon
DECL|member|cmd_link
r_int
r_int
id|cmd_link
suffix:semicolon
DECL|member|iaddr
r_int
r_char
id|iaddr
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Configure command &n; */
DECL|struct|configure_cmd_struct
r_struct
id|configure_cmd_struct
(brace
DECL|member|cmd_status
r_int
r_int
id|cmd_status
suffix:semicolon
DECL|member|cmd_cmd
r_int
r_int
id|cmd_cmd
suffix:semicolon
DECL|member|cmd_link
r_int
r_int
id|cmd_link
suffix:semicolon
DECL|member|byte_cnt
r_int
r_char
id|byte_cnt
suffix:semicolon
multiline_comment|/* size of the config-cmd */
DECL|member|fifo
r_int
r_char
id|fifo
suffix:semicolon
multiline_comment|/* fifo/recv monitor */
DECL|member|sav_bf
r_int
r_char
id|sav_bf
suffix:semicolon
multiline_comment|/* save bad frames (bit7=1)*/
DECL|member|adr_len
r_int
r_char
id|adr_len
suffix:semicolon
multiline_comment|/* adr_len(0-2),al_loc(3),pream(4-5),loopbak(6-7)*/
DECL|member|priority
r_int
r_char
id|priority
suffix:semicolon
multiline_comment|/* lin_prio(0-2),exp_prio(4-6),bof_metd(7) */
DECL|member|ifs
r_int
r_char
id|ifs
suffix:semicolon
multiline_comment|/* inter frame spacing */
DECL|member|time_low
r_int
r_char
id|time_low
suffix:semicolon
multiline_comment|/* slot time low */
DECL|member|time_high
r_int
r_char
id|time_high
suffix:semicolon
multiline_comment|/* slot time high(0-2) and max. retries(4-7) */
DECL|member|promisc
r_int
r_char
id|promisc
suffix:semicolon
multiline_comment|/* promisc-mode(0) , et al (1-7) */
DECL|member|carr_coll
r_int
r_char
id|carr_coll
suffix:semicolon
multiline_comment|/* carrier(0-3)/collision(4-7) stuff */
DECL|member|fram_len
r_int
r_char
id|fram_len
suffix:semicolon
multiline_comment|/* minimal frame len */
DECL|member|dummy
r_int
r_char
id|dummy
suffix:semicolon
multiline_comment|/* dummy */
)brace
suffix:semicolon
multiline_comment|/*&n; * Multicast Setup command &n; */
DECL|struct|mcsetup_cmd_struct
r_struct
id|mcsetup_cmd_struct
(brace
DECL|member|cmd_status
r_int
r_int
id|cmd_status
suffix:semicolon
DECL|member|cmd_cmd
r_int
r_int
id|cmd_cmd
suffix:semicolon
DECL|member|cmd_link
r_int
r_int
id|cmd_link
suffix:semicolon
DECL|member|mc_cnt
r_int
r_int
id|mc_cnt
suffix:semicolon
multiline_comment|/* number of bytes in the MC-List */
DECL|member|mc_list
r_int
r_char
id|mc_list
(braket
l_int|0
)braket
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* pointer to 6 bytes entries */
)brace
suffix:semicolon
multiline_comment|/*&n; * transmit command &n; */
DECL|struct|transmit_cmd_struct
r_struct
id|transmit_cmd_struct
(brace
DECL|member|cmd_status
r_int
r_int
id|cmd_status
suffix:semicolon
DECL|member|cmd_cmd
r_int
r_int
id|cmd_cmd
suffix:semicolon
DECL|member|cmd_link
r_int
r_int
id|cmd_link
suffix:semicolon
DECL|member|tbd_offset
r_int
r_int
id|tbd_offset
suffix:semicolon
multiline_comment|/* pointeroffset to TBD */
DECL|member|dest
r_int
r_char
id|dest
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* destination address of the frame */
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* user defined: 802.3 length / Ether type */
)brace
suffix:semicolon
DECL|macro|TCMD_ERRMASK
mdefine_line|#define TCMD_ERRMASK     0x0fa0
DECL|macro|TCMD_MAXCOLLMASK
mdefine_line|#define TCMD_MAXCOLLMASK 0x000f
DECL|macro|TCMD_MAXCOLL
mdefine_line|#define TCMD_MAXCOLL     0x0020
DECL|macro|TCMD_HEARTBEAT
mdefine_line|#define TCMD_HEARTBEAT   0x0040
DECL|macro|TCMD_DEFERRED
mdefine_line|#define TCMD_DEFERRED    0x0080
DECL|macro|TCMD_UNDERRUN
mdefine_line|#define TCMD_UNDERRUN    0x0100
DECL|macro|TCMD_LOSTCTS
mdefine_line|#define TCMD_LOSTCTS     0x0200
DECL|macro|TCMD_NOCARRIER
mdefine_line|#define TCMD_NOCARRIER   0x0400
DECL|macro|TCMD_LATECOLL
mdefine_line|#define TCMD_LATECOLL    0x0800
DECL|struct|tdr_cmd_struct
r_struct
id|tdr_cmd_struct
(brace
DECL|member|cmd_status
r_int
r_int
id|cmd_status
suffix:semicolon
DECL|member|cmd_cmd
r_int
r_int
id|cmd_cmd
suffix:semicolon
DECL|member|cmd_link
r_int
r_int
id|cmd_link
suffix:semicolon
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TDR_LNK_OK
mdefine_line|#define TDR_LNK_OK&t;0x8000&t;/* No link problem identified */
DECL|macro|TDR_XCVR_PRB
mdefine_line|#define TDR_XCVR_PRB&t;0x4000&t;/* indicates a transceiver problem */
DECL|macro|TDR_ET_OPN
mdefine_line|#define TDR_ET_OPN&t;0x2000&t;/* open, no correct termination */
DECL|macro|TDR_ET_SRT
mdefine_line|#define TDR_ET_SRT&t;0x1000&t;/* TDR detected a short circuit */
DECL|macro|TDR_TIMEMASK
mdefine_line|#define TDR_TIMEMASK&t;0x07ff&t;/* mask for the time field */
multiline_comment|/*&n; * Transmit Buffer Descriptor (TBD)&n; */
DECL|struct|tbd_struct
r_struct
id|tbd_struct
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size + EOF-Flag(15) */
DECL|member|next
r_int
r_int
id|next
suffix:semicolon
multiline_comment|/* pointeroffset to next TBD */
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
multiline_comment|/* pointer to buffer */
)brace
suffix:semicolon
DECL|macro|TBD_LAST
mdefine_line|#define TBD_LAST 0x8000         /* EOF-Flag, indicates last buffer in list */
multiline_comment|/*************************************************************************/
multiline_comment|/*&n;Verbatim from the Crynwyr stuff:&n;&n;    The 3c523 responds with adapter code 0x6042 at slot&n;registers xxx0 and xxx1.  The setup register is at xxx2 and&n;contains the following bits:&n;&n;0: card enable&n;2,1: csr address select&n;    00 = 0300&n;    01 = 1300&n;    10 = 2300&n;    11 = 3300&n;4,3: shared memory address select&n;    00 = 0c0000&n;    01 = 0c8000&n;    10 = 0d0000&n;    11 = 0d8000&n;5: set to disable on-board thinnet&n;7,6: (read-only) shows selected irq&n;    00 = 12&n;    01 = 7&n;    10 = 3&n;    11 = 9&n;&n;The interrupt-select register is at xxx3 and uses one bit per irq.&n;&n;0: int 12&n;1: int 7&n;2: int 3&n;3: int 9&n;&n;    Again, the documentation stresses that the setup register&n;should never be written.  The interrupt-select register may be&n;written with the value corresponding to bits 7.6 in&n;the setup register to insure corret setup.&n;*/
multiline_comment|/* Offsets from the base I/O address. */
DECL|macro|ELMC_SA
mdefine_line|#define&t;ELMC_SA&t;&t;0&t;/* first 6 bytes are IEEE network address */
DECL|macro|ELMC_CTRL
mdefine_line|#define ELMC_CTRL&t;6&t;/* control &amp; status register */
DECL|macro|ELMC_REVISION
mdefine_line|#define ELMC_REVISION&t;7&t;/* revision register, first 4 bits only */
DECL|macro|ELMC_IO_EXTENT
mdefine_line|#define ELMC_IO_EXTENT  8
multiline_comment|/* these are the bit selects for the port register 2 */
DECL|macro|ELMC_STATUS_ENABLED
mdefine_line|#define ELMC_STATUS_ENABLED&t;0x01
DECL|macro|ELMC_STATUS_CSR_SELECT
mdefine_line|#define ELMC_STATUS_CSR_SELECT&t;0x06
DECL|macro|ELMC_STATUS_MEMORY_SELECT
mdefine_line|#define ELMC_STATUS_MEMORY_SELECT&t;0x18
DECL|macro|ELMC_STATUS_DISABLE_THIN
mdefine_line|#define ELMC_STATUS_DISABLE_THIN&t;0x20
DECL|macro|ELMC_STATUS_IRQ_SELECT
mdefine_line|#define ELMC_STATUS_IRQ_SELECT&t;0xc0
multiline_comment|/* this is the card id used in the detection code.  You might recognize&n;it from @6042.adf */
DECL|macro|ELMC_MCA_ID
mdefine_line|#define ELMC_MCA_ID 0x6042
multiline_comment|/*&n;   The following define the bits for the control &amp; status register&n;&n;   The bank select registers can be used if more than 16K of memory is&n;   on the card.  For some stupid reason, bank 3 is the one for the&n;   bottom 16K, and the card defaults to bank 0.  So we have to set the&n;   bank to 3 before the card will even think of operating.  To get bank&n;   3, set BS0 and BS1 to high (of course...)&n;*/
DECL|macro|ELMC_CTRL_BS0
mdefine_line|#define ELMC_CTRL_BS0&t;0x01&t;/* RW bank select */
DECL|macro|ELMC_CTRL_BS1
mdefine_line|#define ELMC_CTRL_BS1&t;0x02&t;/* RW bank select */
DECL|macro|ELMC_CTRL_INTE
mdefine_line|#define ELMC_CTRL_INTE&t;0x04&t;/* RW interrupt enable, assert high */
DECL|macro|ELMC_CTRL_INT
mdefine_line|#define ELMC_CTRL_INT&t;0x08&t;/* R interrupt active, assert high */
multiline_comment|/*#define ELMC_CTRL_*&t;0x10*/
multiline_comment|/* reserved */
DECL|macro|ELMC_CTRL_LBK
mdefine_line|#define ELMC_CTRL_LBK&t;0x20&t;/* RW loopback enable, assert high */
DECL|macro|ELMC_CTRL_CA
mdefine_line|#define ELMC_CTRL_CA&t;0x40&t;/* RW channel attention, assert high */
DECL|macro|ELMC_CTRL_RST
mdefine_line|#define ELMC_CTRL_RST&t;0x80&t;/* RW 82586 reset, assert low */
multiline_comment|/* some handy compound bits */
multiline_comment|/* normal operation should have bank 3 and RST high, ints enabled */
DECL|macro|ELMC_NORMAL
mdefine_line|#define ELMC_NORMAL (ELMC_CTRL_INTE|ELMC_CTRL_RST|0x3)
macro_line|#endif /* _3c523_INCLUDE_ */
eof
