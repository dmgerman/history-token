multiline_comment|/*&n; *      FarSync X21 driver for Linux&n; *&n; *      Actually sync driver for X.21, V.35 and V.24 on FarSync T-series cards&n; *&n; *      Copyright (C) 2001 FarSite Communications Ltd.&n; *      www.farsite.co.uk&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; *      Author: R.J.Dunlop      &lt;bob.dunlop@farsite.co.uk&gt;&n; *&n; *      For the most part this file only contains structures and information&n; *      that is visible to applications outside the driver. Shared memory&n; *      layout etc is internal to the driver and described within farsync.c.&n; *      Overlap exists in that the values used for some fields within the&n; *      ioctl interface extend into the cards firmware interface so values in&n; *      this file may not be changed arbitrarily.&n; */
multiline_comment|/*      What&squot;s in a name&n; *&n; *      The project name for this driver is Oscar. The driver is intended to be&n; *      used with the FarSite T-Series cards (T2P &amp; T4P) running in the high&n; *      speed frame shifter mode. This is sometimes referred to as X.21 mode&n; *      which is a complete misnomer as the card continues to support V.24 and&n; *      V.35 as well as X.21.&n; *&n; *      A short common prefix is useful for routines within the driver to avoid&n; *      conflict with other similar drivers and I chosen to use &quot;fst_&quot; for this&n; *      purpose (FarSite T-series).&n; *&n; *      Finally the device driver needs a short network interface name. Since&n; *      &quot;hdlc&quot; is already in use I&squot;ve chosen the even less informative &quot;sync&quot;&n; *      for the present.&n; */
DECL|macro|FST_NAME
mdefine_line|#define FST_NAME                &quot;fst&quot;           /* In debug/info etc */
DECL|macro|FST_NDEV_NAME
mdefine_line|#define FST_NDEV_NAME           &quot;sync&quot;          /* For net interface */
DECL|macro|FST_DEV_NAME
mdefine_line|#define FST_DEV_NAME            &quot;farsync&quot;       /* For misc interfaces */
multiline_comment|/*      User version number&n; *&n; *      This version number is incremented with each official release of the&n; *      package and is a simplified number for normal user reference.&n; *      Individual files are tracked by the version control system and may&n; *      have individual versions (or IDs) that move much faster than the&n; *      the release version as individual updates are tracked.&n; */
DECL|macro|FST_USER_VERSION
mdefine_line|#define FST_USER_VERSION        &quot;1.04&quot;
multiline_comment|/*      Ioctl call command values&n; *&n; *      The first three private ioctls are used by the sync-PPP module,&n; *      allowing a little room for expansion we start our numbering at 10.&n; */
DECL|macro|FSTWRITE
mdefine_line|#define FSTWRITE        (SIOCDEVPRIVATE+10)
DECL|macro|FSTCPURESET
mdefine_line|#define FSTCPURESET     (SIOCDEVPRIVATE+11)
DECL|macro|FSTCPURELEASE
mdefine_line|#define FSTCPURELEASE   (SIOCDEVPRIVATE+12)
DECL|macro|FSTGETCONF
mdefine_line|#define FSTGETCONF      (SIOCDEVPRIVATE+13)
DECL|macro|FSTSETCONF
mdefine_line|#define FSTSETCONF      (SIOCDEVPRIVATE+14)
multiline_comment|/*      FSTWRITE&n; *&n; *      Used to write a block of data (firmware etc) before the card is running&n; */
DECL|struct|fstioc_write
r_struct
id|fstioc_write
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
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
multiline_comment|/*      FSTCPURESET and FSTCPURELEASE&n; *&n; *      These take no additional data.&n; *      FSTCPURESET forces the cards CPU into a reset state and holds it there.&n; *      FSTCPURELEASE releases the CPU from this reset state allowing it to run,&n; *      the reset vector should be setup before this ioctl is run.&n; */
multiline_comment|/*      FSTGETCONF and FSTSETCONF&n; *&n; *      Get and set a card/ports configuration.&n; *      In order to allow selective setting of items and for the kernel to&n; *      indicate a partial status response the first field &quot;valid&quot; is a bitmask&n; *      indicating which other fields in the structure are valid.&n; *      Many of the field names in this structure match those used in the&n; *      firmware shared memory configuration interface and come originally from&n; *      the NT header file Smc.h&n; *&n; *      When used with FSTGETCONF this structure should be zeroed before use.&n; *      This is to allow for possible future expansion when some of the fields&n; *      might be used to indicate a different (expanded) structure.&n; */
DECL|struct|fstioc_info
r_struct
id|fstioc_info
(brace
DECL|member|valid
r_int
r_int
id|valid
suffix:semicolon
multiline_comment|/* Bits of structure that are valid */
DECL|member|nports
r_int
r_int
id|nports
suffix:semicolon
multiline_comment|/* Number of serial ports */
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* Type index of card */
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
multiline_comment|/* State of card */
DECL|member|index
r_int
r_int
id|index
suffix:semicolon
multiline_comment|/* Index of port ioctl was issued on */
DECL|member|smcFirmwareVersion
r_int
r_int
id|smcFirmwareVersion
suffix:semicolon
DECL|member|kernelVersion
r_int
r_int
id|kernelVersion
suffix:semicolon
multiline_comment|/* What Kernel version we are working with */
DECL|member|lineInterface
r_int
r_int
id|lineInterface
suffix:semicolon
multiline_comment|/* Physical interface type */
DECL|member|proto
r_int
r_char
id|proto
suffix:semicolon
multiline_comment|/* Line protocol */
DECL|member|internalClock
r_int
r_char
id|internalClock
suffix:semicolon
multiline_comment|/* 1 =&gt; internal clock, 0 =&gt; external */
DECL|member|lineSpeed
r_int
r_int
id|lineSpeed
suffix:semicolon
multiline_comment|/* Speed in bps */
DECL|member|v24IpSts
r_int
r_int
id|v24IpSts
suffix:semicolon
multiline_comment|/* V.24 control input status */
DECL|member|v24OpSts
r_int
r_int
id|v24OpSts
suffix:semicolon
multiline_comment|/* V.24 control output status */
DECL|member|clockStatus
r_int
r_int
id|clockStatus
suffix:semicolon
multiline_comment|/* lsb: 0=&gt; present, 1=&gt; absent */
DECL|member|cableStatus
r_int
r_int
id|cableStatus
suffix:semicolon
multiline_comment|/* lsb: 0=&gt; present, 1=&gt; absent */
DECL|member|cardMode
r_int
r_int
id|cardMode
suffix:semicolon
multiline_comment|/* lsb: LED id mode */
DECL|member|debug
r_int
r_int
id|debug
suffix:semicolon
multiline_comment|/* Debug flags */
DECL|member|transparentMode
r_int
r_char
id|transparentMode
suffix:semicolon
multiline_comment|/* Not used always 0 */
DECL|member|invertClock
r_int
r_char
id|invertClock
suffix:semicolon
multiline_comment|/* Invert clock feature for syncing */
DECL|member|startingSlot
r_int
r_char
id|startingSlot
suffix:semicolon
multiline_comment|/* Time slot to use for start of tx */
DECL|member|clockSource
r_int
r_char
id|clockSource
suffix:semicolon
multiline_comment|/* External or internal */
DECL|member|framing
r_int
r_char
id|framing
suffix:semicolon
multiline_comment|/* E1, T1 or J1 */
DECL|member|structure
r_int
r_char
id|structure
suffix:semicolon
multiline_comment|/* unframed, double, crc4, f4, f12, */
multiline_comment|/* f24 f72 */
DECL|member|interface
r_int
r_char
id|interface
suffix:semicolon
multiline_comment|/* rj48c or bnc */
DECL|member|coding
r_int
r_char
id|coding
suffix:semicolon
multiline_comment|/* hdb3 b8zs */
DECL|member|lineBuildOut
r_int
r_char
id|lineBuildOut
suffix:semicolon
multiline_comment|/* 0, -7.5, -15, -22 */
DECL|member|equalizer
r_int
r_char
id|equalizer
suffix:semicolon
multiline_comment|/* short or lon haul settings */
DECL|member|loopMode
r_int
r_char
id|loopMode
suffix:semicolon
multiline_comment|/* various loopbacks */
DECL|member|range
r_int
r_char
id|range
suffix:semicolon
multiline_comment|/* cable lengths */
DECL|member|txBufferMode
r_int
r_char
id|txBufferMode
suffix:semicolon
multiline_comment|/* tx elastic buffer depth */
DECL|member|rxBufferMode
r_int
r_char
id|rxBufferMode
suffix:semicolon
multiline_comment|/* rx elastic buffer depth */
DECL|member|losThreshold
r_int
r_char
id|losThreshold
suffix:semicolon
multiline_comment|/* Attenuation on LOS signal */
DECL|member|idleCode
r_int
r_char
id|idleCode
suffix:semicolon
multiline_comment|/* Value to send as idle timeslot */
DECL|member|receiveBufferDelay
r_int
r_int
id|receiveBufferDelay
suffix:semicolon
multiline_comment|/* delay thro rx buffer timeslots */
DECL|member|framingErrorCount
r_int
r_int
id|framingErrorCount
suffix:semicolon
multiline_comment|/* framing errors */
DECL|member|codeViolationCount
r_int
r_int
id|codeViolationCount
suffix:semicolon
multiline_comment|/* code violations */
DECL|member|crcErrorCount
r_int
r_int
id|crcErrorCount
suffix:semicolon
multiline_comment|/* CRC errors */
DECL|member|lineAttenuation
r_int
id|lineAttenuation
suffix:semicolon
multiline_comment|/* in dB*/
DECL|member|lossOfSignal
r_int
r_int
id|lossOfSignal
suffix:semicolon
DECL|member|receiveRemoteAlarm
r_int
r_int
id|receiveRemoteAlarm
suffix:semicolon
DECL|member|alarmIndicationSignal
r_int
r_int
id|alarmIndicationSignal
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &quot;valid&quot; bitmask */
DECL|macro|FSTVAL_NONE
mdefine_line|#define FSTVAL_NONE     0x00000000      /* Nothing valid (firmware not running).&n;                                         * Slight misnomer. In fact nports,&n;                                         * type, state and index will be set&n;                                         * based on hardware detected.&n;                                         */
DECL|macro|FSTVAL_OMODEM
mdefine_line|#define FSTVAL_OMODEM   0x0000001F      /* First 5 bits correspond to the&n;                                         * output status bits defined for&n;                                         * v24OpSts&n;                                         */
DECL|macro|FSTVAL_SPEED
mdefine_line|#define FSTVAL_SPEED    0x00000020      /* internalClock, lineSpeed, clockStatus&n;                                         */
DECL|macro|FSTVAL_CABLE
mdefine_line|#define FSTVAL_CABLE    0x00000040      /* lineInterface, cableStatus */
DECL|macro|FSTVAL_IMODEM
mdefine_line|#define FSTVAL_IMODEM   0x00000080      /* v24IpSts */
DECL|macro|FSTVAL_CARD
mdefine_line|#define FSTVAL_CARD     0x00000100      /* nports, type, state, index,&n;                                         * smcFirmwareVersion&n;                                         */
DECL|macro|FSTVAL_PROTO
mdefine_line|#define FSTVAL_PROTO    0x00000200      /* proto */
DECL|macro|FSTVAL_MODE
mdefine_line|#define FSTVAL_MODE     0x00000400      /* cardMode */
DECL|macro|FSTVAL_PHASE
mdefine_line|#define FSTVAL_PHASE    0x00000800      /* Clock phase */
DECL|macro|FSTVAL_TE1
mdefine_line|#define FSTVAL_TE1      0x00001000      /* T1E1 Configuration */
DECL|macro|FSTVAL_DEBUG
mdefine_line|#define FSTVAL_DEBUG    0x80000000      /* debug */
DECL|macro|FSTVAL_ALL
mdefine_line|#define FSTVAL_ALL      0x00001FFF      /* Note: does not include DEBUG flag */
multiline_comment|/* &quot;type&quot; */
DECL|macro|FST_TYPE_NONE
mdefine_line|#define FST_TYPE_NONE   0               /* Probably should never happen */
DECL|macro|FST_TYPE_T2P
mdefine_line|#define FST_TYPE_T2P    1               /* T2P X21 2 port card */
DECL|macro|FST_TYPE_T4P
mdefine_line|#define FST_TYPE_T4P    2               /* T4P X21 4 port card */
DECL|macro|FST_TYPE_T1U
mdefine_line|#define FST_TYPE_T1U    3               /* T1U X21 1 port card */
DECL|macro|FST_TYPE_T2U
mdefine_line|#define FST_TYPE_T2U    4               /* T2U X21 2 port card */
DECL|macro|FST_TYPE_T4U
mdefine_line|#define FST_TYPE_T4U    5               /* T4U X21 4 port card */
DECL|macro|FST_TYPE_TE1
mdefine_line|#define FST_TYPE_TE1    6               /* T1E1 X21 1 port card */
multiline_comment|/* &quot;family&quot; */
DECL|macro|FST_FAMILY_TXP
mdefine_line|#define FST_FAMILY_TXP  0               /* T2P or T4P */
DECL|macro|FST_FAMILY_TXU
mdefine_line|#define FST_FAMILY_TXU  1               /* T1U or T2U or T4U */
multiline_comment|/* &quot;state&quot; */
DECL|macro|FST_UNINIT
mdefine_line|#define FST_UNINIT      0               /* Raw uninitialised state following&n;                                         * system startup */
DECL|macro|FST_RESET
mdefine_line|#define FST_RESET       1               /* Processor held in reset state */
DECL|macro|FST_DOWNLOAD
mdefine_line|#define FST_DOWNLOAD    2               /* Card being downloaded */
DECL|macro|FST_STARTING
mdefine_line|#define FST_STARTING    3               /* Released following download */
DECL|macro|FST_RUNNING
mdefine_line|#define FST_RUNNING     4               /* Processor running */
DECL|macro|FST_BADVERSION
mdefine_line|#define FST_BADVERSION  5               /* Bad shared memory version detected */
DECL|macro|FST_HALTED
mdefine_line|#define FST_HALTED      6               /* Processor flagged a halt */
DECL|macro|FST_IFAILED
mdefine_line|#define FST_IFAILED     7               /* Firmware issued initialisation failed&n;                                         * interrupt&n;                                         */
multiline_comment|/* &quot;lineInterface&quot; */
DECL|macro|V24
mdefine_line|#define V24             1
DECL|macro|X21
mdefine_line|#define X21             2
DECL|macro|V35
mdefine_line|#define V35             3
DECL|macro|X21D
mdefine_line|#define X21D            4
DECL|macro|T1
mdefine_line|#define T1              5
DECL|macro|E1
mdefine_line|#define E1              6
DECL|macro|J1
mdefine_line|#define J1              7
multiline_comment|/* &quot;proto&quot; */
DECL|macro|FST_HDLC
mdefine_line|#define FST_HDLC        1               /* Cisco compatible HDLC */
DECL|macro|FST_PPP
mdefine_line|#define FST_PPP         2               /* Sync PPP */
DECL|macro|FST_MONITOR
mdefine_line|#define FST_MONITOR     3               /* Monitor only (raw packet reception) */
DECL|macro|FST_RAW
mdefine_line|#define FST_RAW         4               /* Two way raw packets */
DECL|macro|FST_GEN_HDLC
mdefine_line|#define FST_GEN_HDLC    5               /* Using &quot;Generic HDLC&quot; module */
multiline_comment|/* &quot;internalClock&quot; */
DECL|macro|INTCLK
mdefine_line|#define INTCLK          1
DECL|macro|EXTCLK
mdefine_line|#define EXTCLK          0
multiline_comment|/* &quot;v24IpSts&quot; bitmask */
DECL|macro|IPSTS_CTS
mdefine_line|#define IPSTS_CTS       0x00000001      /* Clear To Send (Indicate for X.21) */
DECL|macro|IPSTS_INDICATE
mdefine_line|#define IPSTS_INDICATE  IPSTS_CTS
DECL|macro|IPSTS_DSR
mdefine_line|#define IPSTS_DSR       0x00000002      /* Data Set Ready (T2P Port A) */
DECL|macro|IPSTS_DCD
mdefine_line|#define IPSTS_DCD       0x00000004      /* Data Carrier Detect */
DECL|macro|IPSTS_RI
mdefine_line|#define IPSTS_RI        0x00000008      /* Ring Indicator (T2P Port A) */
DECL|macro|IPSTS_TMI
mdefine_line|#define IPSTS_TMI       0x00000010      /* Test Mode Indicator (Not Supported)*/
multiline_comment|/* &quot;v24OpSts&quot; bitmask */
DECL|macro|OPSTS_RTS
mdefine_line|#define OPSTS_RTS       0x00000001      /* Request To Send (Control for X.21) */
DECL|macro|OPSTS_CONTROL
mdefine_line|#define OPSTS_CONTROL   OPSTS_RTS
DECL|macro|OPSTS_DTR
mdefine_line|#define OPSTS_DTR       0x00000002      /* Data Terminal Ready */
DECL|macro|OPSTS_DSRS
mdefine_line|#define OPSTS_DSRS      0x00000004      /* Data Signalling Rate Select (Not&n;                                         * Supported) */
DECL|macro|OPSTS_SS
mdefine_line|#define OPSTS_SS        0x00000008      /* Select Standby (Not Supported) */
DECL|macro|OPSTS_LL
mdefine_line|#define OPSTS_LL        0x00000010      /* Maintenance Test (Not Supported) */
multiline_comment|/* &quot;cardMode&quot; bitmask */
DECL|macro|CARD_MODE_IDENTIFY
mdefine_line|#define CARD_MODE_IDENTIFY      0x0001
multiline_comment|/* &n; * Constants for T1/E1 configuration&n; */
multiline_comment|/*&n; * Clock source&n; */
DECL|macro|CLOCKING_SLAVE
mdefine_line|#define CLOCKING_SLAVE       0
DECL|macro|CLOCKING_MASTER
mdefine_line|#define CLOCKING_MASTER      1
multiline_comment|/*&n; * Framing&n; */
DECL|macro|FRAMING_E1
mdefine_line|#define FRAMING_E1           0
DECL|macro|FRAMING_J1
mdefine_line|#define FRAMING_J1           1
DECL|macro|FRAMING_T1
mdefine_line|#define FRAMING_T1           2
multiline_comment|/*&n; * Structure&n; */
DECL|macro|STRUCTURE_UNFRAMED
mdefine_line|#define STRUCTURE_UNFRAMED   0
DECL|macro|STRUCTURE_E1_DOUBLE
mdefine_line|#define STRUCTURE_E1_DOUBLE  1
DECL|macro|STRUCTURE_E1_CRC4
mdefine_line|#define STRUCTURE_E1_CRC4    2
DECL|macro|STRUCTURE_E1_CRC4M
mdefine_line|#define STRUCTURE_E1_CRC4M   3
DECL|macro|STRUCTURE_T1_4
mdefine_line|#define STRUCTURE_T1_4       4
DECL|macro|STRUCTURE_T1_12
mdefine_line|#define STRUCTURE_T1_12      5
DECL|macro|STRUCTURE_T1_24
mdefine_line|#define STRUCTURE_T1_24      6
DECL|macro|STRUCTURE_T1_72
mdefine_line|#define STRUCTURE_T1_72      7
multiline_comment|/*&n; * Interface&n; */
DECL|macro|INTERFACE_RJ48C
mdefine_line|#define INTERFACE_RJ48C      0
DECL|macro|INTERFACE_BNC
mdefine_line|#define INTERFACE_BNC        1
multiline_comment|/*&n; * Coding&n; */
DECL|macro|CODING_HDB3
mdefine_line|#define CODING_HDB3          0
DECL|macro|CODING_NRZ
mdefine_line|#define CODING_NRZ           1
DECL|macro|CODING_CMI
mdefine_line|#define CODING_CMI           2
DECL|macro|CODING_CMI_HDB3
mdefine_line|#define CODING_CMI_HDB3      3
DECL|macro|CODING_CMI_B8ZS
mdefine_line|#define CODING_CMI_B8ZS      4
DECL|macro|CODING_AMI
mdefine_line|#define CODING_AMI           5
DECL|macro|CODING_AMI_ZCS
mdefine_line|#define CODING_AMI_ZCS       6
DECL|macro|CODING_B8ZS
mdefine_line|#define CODING_B8ZS          7
multiline_comment|/*&n; * Line Build Out&n; */
DECL|macro|LBO_0dB
mdefine_line|#define LBO_0dB              0
DECL|macro|LBO_7dB5
mdefine_line|#define LBO_7dB5             1
DECL|macro|LBO_15dB
mdefine_line|#define LBO_15dB             2
DECL|macro|LBO_22dB5
mdefine_line|#define LBO_22dB5            3
multiline_comment|/*&n; * Range for long haul t1 &gt; 655ft&n; */
DECL|macro|RANGE_0_133_FT
mdefine_line|#define RANGE_0_133_FT       0
DECL|macro|RANGE_0_40_M
mdefine_line|#define RANGE_0_40_M         RANGE_0_133_FT
DECL|macro|RANGE_133_266_FT
mdefine_line|#define RANGE_133_266_FT     1
DECL|macro|RANGE_40_81_M
mdefine_line|#define RANGE_40_81_M        RANGE_133_266_FT
DECL|macro|RANGE_266_399_FT
mdefine_line|#define RANGE_266_399_FT     2
DECL|macro|RANGE_81_122_M
mdefine_line|#define RANGE_81_122_M       RANGE_266_399_FT
DECL|macro|RANGE_399_533_FT
mdefine_line|#define RANGE_399_533_FT     3
DECL|macro|RANGE_122_162_M
mdefine_line|#define RANGE_122_162_M       RANGE_399_533_FT
DECL|macro|RANGE_533_655_FT
mdefine_line|#define RANGE_533_655_FT     4
DECL|macro|RANGE_162_200_M
mdefine_line|#define RANGE_162_200_M      RANGE_533_655_FT
multiline_comment|/*&n; * Receive Equaliser&n; */
DECL|macro|EQUALIZER_SHORT
mdefine_line|#define EQUALIZER_SHORT      0
DECL|macro|EQUALIZER_LONG
mdefine_line|#define EQUALIZER_LONG       1
multiline_comment|/*&n; * Loop modes&n; */
DECL|macro|LOOP_NONE
mdefine_line|#define LOOP_NONE            0
DECL|macro|LOOP_LOCAL
mdefine_line|#define LOOP_LOCAL           1
DECL|macro|LOOP_PAYLOAD_EXC_TS0
mdefine_line|#define LOOP_PAYLOAD_EXC_TS0 2
DECL|macro|LOOP_PAYLOAD_INC_TS0
mdefine_line|#define LOOP_PAYLOAD_INC_TS0 3
DECL|macro|LOOP_REMOTE
mdefine_line|#define LOOP_REMOTE          4
multiline_comment|/*&n; * Buffer modes&n; */
DECL|macro|BUFFER_2_FRAME
mdefine_line|#define BUFFER_2_FRAME       0
DECL|macro|BUFFER_1_FRAME
mdefine_line|#define BUFFER_1_FRAME       1
DECL|macro|BUFFER_96_BIT
mdefine_line|#define BUFFER_96_BIT        2
DECL|macro|BUFFER_NONE
mdefine_line|#define BUFFER_NONE          3
multiline_comment|/*      Debug support&n; *&n; *      These should only be enabled for development kernels, production code&n; *      should define FST_DEBUG=0 in order to exclude the code.&n; *      Setting FST_DEBUG=1 will include all the debug code but in a disabled&n; *      state, use the FSTSETCONF ioctl to enable specific debug actions, or&n; *      FST_DEBUG can be set to prime the debug selection.&n; */
DECL|macro|FST_DEBUG
mdefine_line|#define FST_DEBUG       0x0000
macro_line|#if FST_DEBUG
r_extern
r_int
id|fst_debug_mask
suffix:semicolon
multiline_comment|/* Bit mask of actions to debug, bits&n;                                         * listed below. Note: Bit 0 is used&n;                                         * to trigger the inclusion of this&n;                                         * code, without enabling any actions.&n;                                         */
DECL|macro|DBG_INIT
mdefine_line|#define DBG_INIT        0x0002          /* Card detection and initialisation */
DECL|macro|DBG_OPEN
mdefine_line|#define DBG_OPEN        0x0004          /* Open and close sequences */
DECL|macro|DBG_PCI
mdefine_line|#define DBG_PCI         0x0008          /* PCI config operations */
DECL|macro|DBG_IOCTL
mdefine_line|#define DBG_IOCTL       0x0010          /* Ioctls and other config */
DECL|macro|DBG_INTR
mdefine_line|#define DBG_INTR        0x0020          /* Interrupt routines (be careful) */
DECL|macro|DBG_TX
mdefine_line|#define DBG_TX          0x0040          /* Packet transmission */
DECL|macro|DBG_RX
mdefine_line|#define DBG_RX          0x0080          /* Packet reception */
DECL|macro|DBG_CMD
mdefine_line|#define DBG_CMD         0x0100          /* Port command issuing */
DECL|macro|DBG_ASS
mdefine_line|#define DBG_ASS         0xFFFF          /* Assert like statements. Code that&n;                                         * should never be reached, if you see&n;                                         * one of these then I&squot;ve been an ass&n;                                         */
macro_line|#endif  /* FST_DEBUG */
eof
