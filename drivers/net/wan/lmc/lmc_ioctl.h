macro_line|#ifndef _LMC_IOCTL_H_
DECL|macro|_LMC_IOCTL_H_
mdefine_line|#define _LMC_IOCTL_H_
multiline_comment|/*&t;$Id: lmc_ioctl.h,v 1.15 2000/04/06 12:16:43 asj Exp $&t;*/
multiline_comment|/*&n;  * Copyright (c) 1997-2000 LAN Media Corporation (LMC)&n;  * All rights reserved.  www.lanmedia.com&n;  *&n;  * This code is written by:&n;  * Andrew Stanley-Jones (asj@cban.com)&n;  * Rob Braun (bbraun@vix.com),&n;  * Michael Graff (explorer@vix.com) and&n;  * Matt Thomas (matt@3am-software.com).&n;  *&n;  * This software may be used and distributed according to the terms&n;  * of the GNU Public License version 2, incorporated herein by reference.&n;  */
DECL|macro|LMCIOCGINFO
mdefine_line|#define LMCIOCGINFO             SIOCDEVPRIVATE+3 /* get current state */
DECL|macro|LMCIOCSINFO
mdefine_line|#define LMCIOCSINFO             SIOCDEVPRIVATE+4 /* set state to user values */
DECL|macro|LMCIOCGETLMCSTATS
mdefine_line|#define LMCIOCGETLMCSTATS       SIOCDEVPRIVATE+5
DECL|macro|LMCIOCCLEARLMCSTATS
mdefine_line|#define LMCIOCCLEARLMCSTATS     SIOCDEVPRIVATE+6
DECL|macro|LMCIOCDUMPEVENTLOG
mdefine_line|#define LMCIOCDUMPEVENTLOG      SIOCDEVPRIVATE+7
DECL|macro|LMCIOCGETXINFO
mdefine_line|#define LMCIOCGETXINFO          SIOCDEVPRIVATE+8
DECL|macro|LMCIOCSETCIRCUIT
mdefine_line|#define LMCIOCSETCIRCUIT        SIOCDEVPRIVATE+9
DECL|macro|LMCIOCUNUSEDATM
mdefine_line|#define LMCIOCUNUSEDATM         SIOCDEVPRIVATE+10
DECL|macro|LMCIOCRESET
mdefine_line|#define LMCIOCRESET             SIOCDEVPRIVATE+11
DECL|macro|LMCIOCT1CONTROL
mdefine_line|#define LMCIOCT1CONTROL         SIOCDEVPRIVATE+12
DECL|macro|LMCIOCIFTYPE
mdefine_line|#define LMCIOCIFTYPE            SIOCDEVPRIVATE+13
DECL|macro|LMCIOCXILINX
mdefine_line|#define LMCIOCXILINX            SIOCDEVPRIVATE+14
DECL|macro|LMC_CARDTYPE_UNKNOWN
mdefine_line|#define LMC_CARDTYPE_UNKNOWN            -1
DECL|macro|LMC_CARDTYPE_HSSI
mdefine_line|#define LMC_CARDTYPE_HSSI               1       /* probed card is a HSSI card */
DECL|macro|LMC_CARDTYPE_DS3
mdefine_line|#define LMC_CARDTYPE_DS3                2       /* probed card is a DS3 card */
DECL|macro|LMC_CARDTYPE_SSI
mdefine_line|#define LMC_CARDTYPE_SSI                3       /* probed card is a SSI card */
DECL|macro|LMC_CARDTYPE_T1
mdefine_line|#define LMC_CARDTYPE_T1                 4       /* probed card is a T1 card */
DECL|macro|LMC_CTL_CARDTYPE_LMC5200
mdefine_line|#define LMC_CTL_CARDTYPE_LMC5200&t;0&t;/* HSSI */
DECL|macro|LMC_CTL_CARDTYPE_LMC5245
mdefine_line|#define LMC_CTL_CARDTYPE_LMC5245&t;1&t;/* DS3 */
DECL|macro|LMC_CTL_CARDTYPE_LMC1000
mdefine_line|#define LMC_CTL_CARDTYPE_LMC1000&t;2&t;/* SSI, V.35 */
DECL|macro|LMC_CTL_CARDTYPE_LMC1200
mdefine_line|#define LMC_CTL_CARDTYPE_LMC1200        3       /* DS1 */
DECL|macro|LMC_CTL_OFF
mdefine_line|#define LMC_CTL_OFF&t;&t;&t;0&t;/* generic OFF value */
DECL|macro|LMC_CTL_ON
mdefine_line|#define LMC_CTL_ON&t;&t;&t;1&t;/* generic ON value */
DECL|macro|LMC_CTL_CLOCK_SOURCE_EXT
mdefine_line|#define LMC_CTL_CLOCK_SOURCE_EXT&t;0&t;/* clock off line */
DECL|macro|LMC_CTL_CLOCK_SOURCE_INT
mdefine_line|#define LMC_CTL_CLOCK_SOURCE_INT&t;1&t;/* internal clock */
DECL|macro|LMC_CTL_CRC_LENGTH_16
mdefine_line|#define LMC_CTL_CRC_LENGTH_16&t;&t;16
DECL|macro|LMC_CTL_CRC_LENGTH_32
mdefine_line|#define LMC_CTL_CRC_LENGTH_32&t;&t;32
DECL|macro|LMC_CTL_CRC_BYTESIZE_2
mdefine_line|#define LMC_CTL_CRC_BYTESIZE_2          2
DECL|macro|LMC_CTL_CRC_BYTESIZE_4
mdefine_line|#define LMC_CTL_CRC_BYTESIZE_4          4
DECL|macro|LMC_CTL_CABLE_LENGTH_LT_100FT
mdefine_line|#define LMC_CTL_CABLE_LENGTH_LT_100FT&t;0&t;/* DS3 cable &lt; 100 feet */
DECL|macro|LMC_CTL_CABLE_LENGTH_GT_100FT
mdefine_line|#define LMC_CTL_CABLE_LENGTH_GT_100FT&t;1&t;/* DS3 cable &gt;= 100 feet */
DECL|macro|LMC_CTL_CIRCUIT_TYPE_E1
mdefine_line|#define LMC_CTL_CIRCUIT_TYPE_E1 0
DECL|macro|LMC_CTL_CIRCUIT_TYPE_T1
mdefine_line|#define LMC_CTL_CIRCUIT_TYPE_T1 1
multiline_comment|/*&n; * IFTYPE defines&n; */
DECL|macro|LMC_PPP
mdefine_line|#define LMC_PPP         1               /* use sppp interface */
DECL|macro|LMC_NET
mdefine_line|#define LMC_NET         2               /* use direct net interface */
DECL|macro|LMC_RAW
mdefine_line|#define LMC_RAW         3               /* use direct net interface */
multiline_comment|/*&n; * These are not in the least IOCTL related, but I want them common.&n; */
multiline_comment|/*&n; * assignments for the GPIO register on the DEC chip (common)&n; */
DECL|macro|LMC_GEP_INIT
mdefine_line|#define LMC_GEP_INIT&t;&t;0x01 /* 0: */
DECL|macro|LMC_GEP_RESET
mdefine_line|#define LMC_GEP_RESET&t;&t;0x02 /* 1: */
DECL|macro|LMC_GEP_MODE
mdefine_line|#define LMC_GEP_MODE&t;&t;0x10 /* 4: */
DECL|macro|LMC_GEP_DP
mdefine_line|#define LMC_GEP_DP&t;&t;0x20 /* 5: */
DECL|macro|LMC_GEP_DATA
mdefine_line|#define LMC_GEP_DATA&t;&t;0x40 /* 6: serial out */
DECL|macro|LMC_GEP_CLK
mdefine_line|#define LMC_GEP_CLK&t;        0x80 /* 7: serial clock */
multiline_comment|/*&n; * HSSI GPIO assignments&n; */
DECL|macro|LMC_GEP_HSSI_ST
mdefine_line|#define LMC_GEP_HSSI_ST&t;&t;0x04 /* 2: receive timing sense (deprecated) */
DECL|macro|LMC_GEP_HSSI_CLOCK
mdefine_line|#define LMC_GEP_HSSI_CLOCK&t;0x08 /* 3: clock source */
multiline_comment|/*&n; * T1 GPIO assignments&n; */
DECL|macro|LMC_GEP_SSI_GENERATOR
mdefine_line|#define LMC_GEP_SSI_GENERATOR&t;0x04 /* 2: enable prog freq gen serial i/f */
DECL|macro|LMC_GEP_SSI_TXCLOCK
mdefine_line|#define LMC_GEP_SSI_TXCLOCK&t;0x08 /* 3: provide clock on TXCLOCK output */
multiline_comment|/*&n; * Common MII16 bits&n; */
DECL|macro|LMC_MII16_LED0
mdefine_line|#define LMC_MII16_LED0         0x0080
DECL|macro|LMC_MII16_LED1
mdefine_line|#define LMC_MII16_LED1         0x0100
DECL|macro|LMC_MII16_LED2
mdefine_line|#define LMC_MII16_LED2         0x0200
DECL|macro|LMC_MII16_LED3
mdefine_line|#define LMC_MII16_LED3         0x0400  /* Error, and the red one */
DECL|macro|LMC_MII16_LED_ALL
mdefine_line|#define LMC_MII16_LED_ALL      0x0780  /* LED bit mask */
DECL|macro|LMC_MII16_FIFO_RESET
mdefine_line|#define LMC_MII16_FIFO_RESET   0x0800
multiline_comment|/*&n; * definitions for HSSI&n; */
DECL|macro|LMC_MII16_HSSI_TA
mdefine_line|#define LMC_MII16_HSSI_TA      0x0001
DECL|macro|LMC_MII16_HSSI_CA
mdefine_line|#define LMC_MII16_HSSI_CA      0x0002
DECL|macro|LMC_MII16_HSSI_LA
mdefine_line|#define LMC_MII16_HSSI_LA      0x0004
DECL|macro|LMC_MII16_HSSI_LB
mdefine_line|#define LMC_MII16_HSSI_LB      0x0008
DECL|macro|LMC_MII16_HSSI_LC
mdefine_line|#define LMC_MII16_HSSI_LC      0x0010
DECL|macro|LMC_MII16_HSSI_TM
mdefine_line|#define LMC_MII16_HSSI_TM      0x0020
DECL|macro|LMC_MII16_HSSI_CRC
mdefine_line|#define LMC_MII16_HSSI_CRC     0x0040
multiline_comment|/*&n; * assignments for the MII register 16 (DS3)&n; */
DECL|macro|LMC_MII16_DS3_ZERO
mdefine_line|#define LMC_MII16_DS3_ZERO&t;0x0001
DECL|macro|LMC_MII16_DS3_TRLBK
mdefine_line|#define LMC_MII16_DS3_TRLBK&t;0x0002
DECL|macro|LMC_MII16_DS3_LNLBK
mdefine_line|#define LMC_MII16_DS3_LNLBK&t;0x0004
DECL|macro|LMC_MII16_DS3_RAIS
mdefine_line|#define LMC_MII16_DS3_RAIS&t;0x0008
DECL|macro|LMC_MII16_DS3_TAIS
mdefine_line|#define LMC_MII16_DS3_TAIS&t;0x0010
DECL|macro|LMC_MII16_DS3_BIST
mdefine_line|#define LMC_MII16_DS3_BIST&t;0x0020
DECL|macro|LMC_MII16_DS3_DLOS
mdefine_line|#define LMC_MII16_DS3_DLOS&t;0x0040
DECL|macro|LMC_MII16_DS3_CRC
mdefine_line|#define LMC_MII16_DS3_CRC&t;0x1000
DECL|macro|LMC_MII16_DS3_SCRAM
mdefine_line|#define LMC_MII16_DS3_SCRAM&t;0x2000
DECL|macro|LMC_MII16_DS3_SCRAM_LARS
mdefine_line|#define LMC_MII16_DS3_SCRAM_LARS 0x4000
multiline_comment|/* Note: 2 pairs of LEDs where swapped by mistake&n; * in Xilinx code for DS3 &amp; DS1 adapters */
DECL|macro|LMC_DS3_LED0
mdefine_line|#define LMC_DS3_LED0    0x0100          /* bit 08  yellow */
DECL|macro|LMC_DS3_LED1
mdefine_line|#define LMC_DS3_LED1    0x0080          /* bit 07  blue   */
DECL|macro|LMC_DS3_LED2
mdefine_line|#define LMC_DS3_LED2    0x0400          /* bit 10  green  */
DECL|macro|LMC_DS3_LED3
mdefine_line|#define LMC_DS3_LED3    0x0200          /* bit 09  red    */
multiline_comment|/*&n; * framer register 0 and 7 (7 is latched and reset on read)&n; */
DECL|macro|LMC_FRAMER_REG0_DLOS
mdefine_line|#define LMC_FRAMER_REG0_DLOS            0x80    /* digital loss of service */
DECL|macro|LMC_FRAMER_REG0_OOFS
mdefine_line|#define LMC_FRAMER_REG0_OOFS            0x40    /* out of frame sync */
DECL|macro|LMC_FRAMER_REG0_AIS
mdefine_line|#define LMC_FRAMER_REG0_AIS             0x20    /* alarm indication signal */
DECL|macro|LMC_FRAMER_REG0_CIS
mdefine_line|#define LMC_FRAMER_REG0_CIS             0x10    /* channel idle */
DECL|macro|LMC_FRAMER_REG0_LOC
mdefine_line|#define LMC_FRAMER_REG0_LOC             0x08    /* loss of clock */
multiline_comment|/*&n; * Framer register 9 contains the blue alarm signal&n; */
DECL|macro|LMC_FRAMER_REG9_RBLUE
mdefine_line|#define LMC_FRAMER_REG9_RBLUE          0x02     /* Blue alarm failure */
multiline_comment|/*&n; * Framer register 0x10 contains xbit error&n; */
DECL|macro|LMC_FRAMER_REG10_XBIT
mdefine_line|#define LMC_FRAMER_REG10_XBIT          0x01     /* X bit error alarm failure */
multiline_comment|/*&n; * And SSI, LMC1000&n; */
DECL|macro|LMC_MII16_SSI_DTR
mdefine_line|#define LMC_MII16_SSI_DTR&t;0x0001&t;/* DTR output RW */
DECL|macro|LMC_MII16_SSI_DSR
mdefine_line|#define LMC_MII16_SSI_DSR&t;0x0002&t;/* DSR input RO */
DECL|macro|LMC_MII16_SSI_RTS
mdefine_line|#define LMC_MII16_SSI_RTS&t;0x0004&t;/* RTS output RW */
DECL|macro|LMC_MII16_SSI_CTS
mdefine_line|#define LMC_MII16_SSI_CTS&t;0x0008&t;/* CTS input RO */
DECL|macro|LMC_MII16_SSI_DCD
mdefine_line|#define LMC_MII16_SSI_DCD&t;0x0010&t;/* DCD input RO */
DECL|macro|LMC_MII16_SSI_RI
mdefine_line|#define LMC_MII16_SSI_RI&t;&t;0x0020&t;/* RI input RO */
DECL|macro|LMC_MII16_SSI_CRC
mdefine_line|#define LMC_MII16_SSI_CRC                0x1000  /* CRC select - RW */
multiline_comment|/*&n; * bits 0x0080 through 0x0800 are generic, and described&n; * above with LMC_MII16_LED[0123] _LED_ALL, and _FIFO_RESET&n; */
DECL|macro|LMC_MII16_SSI_LL
mdefine_line|#define LMC_MII16_SSI_LL&t;&t;0x1000&t;/* LL output RW */
DECL|macro|LMC_MII16_SSI_RL
mdefine_line|#define LMC_MII16_SSI_RL&t;&t;0x2000&t;/* RL output RW */
DECL|macro|LMC_MII16_SSI_TM
mdefine_line|#define LMC_MII16_SSI_TM&t;&t;0x4000&t;/* TM input RO */
DECL|macro|LMC_MII16_SSI_LOOP
mdefine_line|#define LMC_MII16_SSI_LOOP&t;0x8000&t;/* loopback enable RW */
multiline_comment|/*&n; * Some of the MII16 bits are mirrored in the MII17 register as well,&n; * but let&squot;s keep thing seperate for now, and get only the cable from&n; * the MII17.&n; */
DECL|macro|LMC_MII17_SSI_CABLE_MASK
mdefine_line|#define LMC_MII17_SSI_CABLE_MASK&t;0x0038&t;/* mask to extract the cable type */
DECL|macro|LMC_MII17_SSI_CABLE_SHIFT
mdefine_line|#define LMC_MII17_SSI_CABLE_SHIFT 3&t;/* shift to extract the cable type */
multiline_comment|/*&n; * And T1, LMC1200&n; */
DECL|macro|LMC_MII16_T1_UNUSED1
mdefine_line|#define LMC_MII16_T1_UNUSED1    0x0003
DECL|macro|LMC_MII16_T1_XOE
mdefine_line|#define LMC_MII16_T1_XOE                0x0004
DECL|macro|LMC_MII16_T1_RST
mdefine_line|#define LMC_MII16_T1_RST                0x0008  /* T1 chip reset - RW */
DECL|macro|LMC_MII16_T1_Z
mdefine_line|#define LMC_MII16_T1_Z                  0x0010  /* output impedance T1=1, E1=0 output - RW */
DECL|macro|LMC_MII16_T1_INTR
mdefine_line|#define LMC_MII16_T1_INTR               0x0020  /* interrupt from 8370 - RO */
DECL|macro|LMC_MII16_T1_ONESEC
mdefine_line|#define LMC_MII16_T1_ONESEC             0x0040  /* one second square wave - ro */
DECL|macro|LMC_MII16_T1_LED0
mdefine_line|#define LMC_MII16_T1_LED0               0x0100
DECL|macro|LMC_MII16_T1_LED1
mdefine_line|#define LMC_MII16_T1_LED1               0x0080
DECL|macro|LMC_MII16_T1_LED2
mdefine_line|#define LMC_MII16_T1_LED2               0x0400
DECL|macro|LMC_MII16_T1_LED3
mdefine_line|#define LMC_MII16_T1_LED3               0x0200
DECL|macro|LMC_MII16_T1_FIFO_RESET
mdefine_line|#define LMC_MII16_T1_FIFO_RESET 0x0800
DECL|macro|LMC_MII16_T1_CRC
mdefine_line|#define LMC_MII16_T1_CRC                0x1000  /* CRC select - RW */
DECL|macro|LMC_MII16_T1_UNUSED2
mdefine_line|#define LMC_MII16_T1_UNUSED2    0xe000
multiline_comment|/* 8370 framer registers  */
DECL|macro|T1FRAMER_ALARM1_STATUS
mdefine_line|#define T1FRAMER_ALARM1_STATUS  0x47
DECL|macro|T1FRAMER_ALARM2_STATUS
mdefine_line|#define T1FRAMER_ALARM2_STATUS  0x48
DECL|macro|T1FRAMER_FERR_LSB
mdefine_line|#define T1FRAMER_FERR_LSB               0x50
DECL|macro|T1FRAMER_FERR_MSB
mdefine_line|#define T1FRAMER_FERR_MSB               0x51    /* framing bit error counter */
DECL|macro|T1FRAMER_LCV_LSB
mdefine_line|#define T1FRAMER_LCV_LSB                0x54
DECL|macro|T1FRAMER_LCV_MSB
mdefine_line|#define T1FRAMER_LCV_MSB                0x55    /* line code violation counter */
DECL|macro|T1FRAMER_AERR
mdefine_line|#define T1FRAMER_AERR                   0x5A
multiline_comment|/* mask for the above AERR register */
DECL|macro|T1FRAMER_LOF_MASK
mdefine_line|#define T1FRAMER_LOF_MASK               (0x0f0) /* receive loss of frame */
DECL|macro|T1FRAMER_COFA_MASK
mdefine_line|#define T1FRAMER_COFA_MASK              (0x0c0) /* change of frame alignment */
DECL|macro|T1FRAMER_SEF_MASK
mdefine_line|#define T1FRAMER_SEF_MASK               (0x03)  /* severely errored frame  */
multiline_comment|/* 8370 framer register ALM1 (0x47) values&n; * used to determine link status&n; */
DECL|macro|T1F_SIGFRZ
mdefine_line|#define T1F_SIGFRZ      0x01    /* signaling freeze */
DECL|macro|T1F_RLOF
mdefine_line|#define T1F_RLOF        0x02    /* receive loss of frame alignment */
DECL|macro|T1F_RLOS
mdefine_line|#define T1F_RLOS        0x04    /* receive loss of signal */
DECL|macro|T1F_RALOS
mdefine_line|#define T1F_RALOS       0x08    /* receive analog loss of signal or RCKI loss of clock */
DECL|macro|T1F_RAIS
mdefine_line|#define T1F_RAIS        0x10    /* receive alarm indication signal */
DECL|macro|T1F_UNUSED
mdefine_line|#define T1F_UNUSED      0x20
DECL|macro|T1F_RYEL
mdefine_line|#define T1F_RYEL        0x40    /* receive yellow alarm */
DECL|macro|T1F_RMYEL
mdefine_line|#define T1F_RMYEL       0x80    /* receive multiframe yellow alarm */
DECL|macro|LMC_T1F_WRITE
mdefine_line|#define LMC_T1F_WRITE       0
DECL|macro|LMC_T1F_READ
mdefine_line|#define LMC_T1F_READ        1
DECL|struct|lmc_st1f_control
r_typedef
r_struct
id|lmc_st1f_control
(brace
DECL|member|command
r_int
id|command
suffix:semicolon
DECL|member|address
r_int
id|address
suffix:semicolon
DECL|member|value
r_int
id|value
suffix:semicolon
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
DECL|typedef|lmc_t1f_control
)brace
id|lmc_t1f_control
suffix:semicolon
DECL|enum|lmc_xilinx_c
r_enum
id|lmc_xilinx_c
(brace
DECL|enumerator|lmc_xilinx_reset
id|lmc_xilinx_reset
op_assign
l_int|1
comma
DECL|enumerator|lmc_xilinx_load_prom
id|lmc_xilinx_load_prom
op_assign
l_int|2
comma
DECL|enumerator|lmc_xilinx_load
id|lmc_xilinx_load
op_assign
l_int|3
)brace
suffix:semicolon
DECL|struct|lmc_xilinx_control
r_struct
id|lmc_xilinx_control
(brace
DECL|member|command
r_enum
id|lmc_xilinx_c
id|command
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ------------------ end T1 defs ------------------- */
DECL|macro|LMC_MII_LedMask
mdefine_line|#define LMC_MII_LedMask                 0x0780
DECL|macro|LMC_MII_LedBitPos
mdefine_line|#define LMC_MII_LedBitPos               7
macro_line|#endif
eof
