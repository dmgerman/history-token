macro_line|#ifndef _LMC_VAR_H_
DECL|macro|_LMC_VAR_H_
mdefine_line|#define _LMC_VAR_H_
multiline_comment|/* $Id: lmc_var.h,v 1.17 2000/04/06 12:16:47 asj Exp $ */
multiline_comment|/*&n;  * Copyright (c) 1997-2000 LAN Media Corporation (LMC)&n;  * All rights reserved.  www.lanmedia.com&n;  *&n;  * This code is written by:&n;  * Andrew Stanley-Jones (asj@cban.com)&n;  * Rob Braun (bbraun@vix.com),&n;  * Michael Graff (explorer@vix.com) and&n;  * Matt Thomas (matt@3am-software.com).&n;  *&n;  * This software may be used and distributed according to the terms&n;  * of the GNU General Public License version 2, incorporated herein by reference.&n;  */
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#ifndef __KERNEL__
DECL|typedef|s8
r_typedef
r_int
r_char
id|s8
suffix:semicolon
DECL|typedef|u8
r_typedef
r_int
r_char
id|u8
suffix:semicolon
DECL|typedef|s16
r_typedef
r_int
r_int
id|s16
suffix:semicolon
DECL|typedef|u16
r_typedef
r_int
r_int
id|u16
suffix:semicolon
DECL|typedef|s32
r_typedef
r_int
r_int
id|s32
suffix:semicolon
DECL|typedef|u32
r_typedef
r_int
r_int
id|u32
suffix:semicolon
DECL|typedef|s64
r_typedef
r_int
r_int
r_int
id|s64
suffix:semicolon
DECL|typedef|u64
r_typedef
r_int
r_int
r_int
id|u64
suffix:semicolon
DECL|macro|BITS_PER_LONG
mdefine_line|#define BITS_PER_LONG 32 
macro_line|#endif
multiline_comment|/*&n; * basic definitions used in lmc include files&n; */
DECL|typedef|lmc_softc_t
r_typedef
r_struct
id|lmc___softc
id|lmc_softc_t
suffix:semicolon
DECL|typedef|lmc_media_t
r_typedef
r_struct
id|lmc___media
id|lmc_media_t
suffix:semicolon
DECL|typedef|lmc_ctl_t
r_typedef
r_struct
id|lmc___ctl
id|lmc_ctl_t
suffix:semicolon
DECL|macro|lmc_csrptr_t
mdefine_line|#define lmc_csrptr_t    unsigned long
DECL|macro|u_int16_t
mdefine_line|#define u_int16_t&t;u16
DECL|macro|u_int8_t
mdefine_line|#define u_int8_t&t;u8
DECL|macro|tulip_uint32_t
mdefine_line|#define tulip_uint32_t&t;u32
macro_line|#if LINUX_VERSION_CODE &lt; 0x20155
DECL|macro|u_int32_t
mdefine_line|#define u_int32_t&t;u32
macro_line|#endif
DECL|macro|LMC_REG_RANGE
mdefine_line|#define LMC_REG_RANGE 0x80
DECL|macro|LMC_PRINTF_FMT
mdefine_line|#define LMC_PRINTF_FMT  &quot;%s&quot;
DECL|macro|LMC_PRINTF_ARGS
mdefine_line|#define LMC_PRINTF_ARGS&t;(sc-&gt;lmc_device-&gt;name)
DECL|macro|TX_TIMEOUT
mdefine_line|#define TX_TIMEOUT (2*HZ)
DECL|macro|LMC_TXDESCS
mdefine_line|#define LMC_TXDESCS            32
DECL|macro|LMC_RXDESCS
mdefine_line|#define LMC_RXDESCS            32
DECL|macro|LMC_LINK_UP
mdefine_line|#define LMC_LINK_UP            1
DECL|macro|LMC_LINK_DOWN
mdefine_line|#define LMC_LINK_DOWN          0
multiline_comment|/* These macros for generic read and write to and from the dec chip */
DECL|macro|LMC_CSR_READ
mdefine_line|#define LMC_CSR_READ(sc, csr) &bslash;&n;&t;inl((sc)-&gt;lmc_csrs.csr)
DECL|macro|LMC_CSR_WRITE
mdefine_line|#define LMC_CSR_WRITE(sc, reg, val) &bslash;&n;&t;outl((val), (sc)-&gt;lmc_csrs.reg)
singleline_comment|//#ifdef _LINUX_DELAY_H
singleline_comment|//&t;#define SLOW_DOWN_IO udelay(2);
singleline_comment|//&t;#undef __SLOW_DOWN_IO
singleline_comment|//&t;#define __SLOW_DOWN_IO udelay(2);
singleline_comment|//#endif
DECL|macro|DELAY
mdefine_line|#define DELAY(n) SLOW_DOWN_IO
DECL|macro|lmc_delay
mdefine_line|#define lmc_delay() inl(sc-&gt;lmc_csrs.csr_9)
multiline_comment|/* This macro sync&squot;s up with the mii so that reads and writes can take place */
DECL|macro|LMC_MII_SYNC
mdefine_line|#define LMC_MII_SYNC(sc) do {int n=32; while( n &gt;= 0 ) { &bslash;&n;                LMC_CSR_WRITE((sc), csr_9, 0x20000); &bslash;&n;&t;&t;lmc_delay(); &bslash;&n;&t;&t;LMC_CSR_WRITE((sc), csr_9, 0x30000); &bslash;&n;                lmc_delay(); &bslash;&n;&t;&t;n--; }} while(0);
DECL|struct|lmc_regfile_t
r_struct
id|lmc_regfile_t
(brace
DECL|member|csr_busmode
id|lmc_csrptr_t
id|csr_busmode
suffix:semicolon
multiline_comment|/* CSR0 */
DECL|member|csr_txpoll
id|lmc_csrptr_t
id|csr_txpoll
suffix:semicolon
multiline_comment|/* CSR1 */
DECL|member|csr_rxpoll
id|lmc_csrptr_t
id|csr_rxpoll
suffix:semicolon
multiline_comment|/* CSR2 */
DECL|member|csr_rxlist
id|lmc_csrptr_t
id|csr_rxlist
suffix:semicolon
multiline_comment|/* CSR3 */
DECL|member|csr_txlist
id|lmc_csrptr_t
id|csr_txlist
suffix:semicolon
multiline_comment|/* CSR4 */
DECL|member|csr_status
id|lmc_csrptr_t
id|csr_status
suffix:semicolon
multiline_comment|/* CSR5 */
DECL|member|csr_command
id|lmc_csrptr_t
id|csr_command
suffix:semicolon
multiline_comment|/* CSR6 */
DECL|member|csr_intr
id|lmc_csrptr_t
id|csr_intr
suffix:semicolon
multiline_comment|/* CSR7 */
DECL|member|csr_missed_frames
id|lmc_csrptr_t
id|csr_missed_frames
suffix:semicolon
multiline_comment|/* CSR8 */
DECL|member|csr_9
id|lmc_csrptr_t
id|csr_9
suffix:semicolon
multiline_comment|/* CSR9 */
DECL|member|csr_10
id|lmc_csrptr_t
id|csr_10
suffix:semicolon
multiline_comment|/* CSR10 */
DECL|member|csr_11
id|lmc_csrptr_t
id|csr_11
suffix:semicolon
multiline_comment|/* CSR11 */
DECL|member|csr_12
id|lmc_csrptr_t
id|csr_12
suffix:semicolon
multiline_comment|/* CSR12 */
DECL|member|csr_13
id|lmc_csrptr_t
id|csr_13
suffix:semicolon
multiline_comment|/* CSR13 */
DECL|member|csr_14
id|lmc_csrptr_t
id|csr_14
suffix:semicolon
multiline_comment|/* CSR14 */
DECL|member|csr_15
id|lmc_csrptr_t
id|csr_15
suffix:semicolon
multiline_comment|/* CSR15 */
)brace
suffix:semicolon
DECL|macro|csr_enetrom
mdefine_line|#define csr_enetrom             csr_9   /* 21040 */
DECL|macro|csr_reserved
mdefine_line|#define csr_reserved            csr_10  /* 21040 */
DECL|macro|csr_full_duplex
mdefine_line|#define csr_full_duplex         csr_11  /* 21040 */
DECL|macro|csr_bootrom
mdefine_line|#define csr_bootrom             csr_10  /* 21041/21140A/?? */
DECL|macro|csr_gp
mdefine_line|#define csr_gp                  csr_12  /* 21140* */
DECL|macro|csr_watchdog
mdefine_line|#define csr_watchdog            csr_15  /* 21140* */
DECL|macro|csr_gp_timer
mdefine_line|#define csr_gp_timer            csr_11  /* 21041/21140* */
DECL|macro|csr_srom_mii
mdefine_line|#define csr_srom_mii            csr_9   /* 21041/21140* */
DECL|macro|csr_sia_status
mdefine_line|#define csr_sia_status          csr_12  /* 2104x */
DECL|macro|csr_sia_connectivity
mdefine_line|#define csr_sia_connectivity    csr_13  /* 2104x */
DECL|macro|csr_sia_tx_rx
mdefine_line|#define csr_sia_tx_rx           csr_14  /* 2104x */
DECL|macro|csr_sia_general
mdefine_line|#define csr_sia_general         csr_15  /* 2104x */
multiline_comment|/* tulip length/control transmit descriptor definitions&n; *  used to define bits in the second tulip_desc_t field (length)&n; *  for the transmit descriptor -baz */
DECL|macro|LMC_TDES_FIRST_BUFFER_SIZE
mdefine_line|#define LMC_TDES_FIRST_BUFFER_SIZE       ((u_int32_t)(0x000007FF))
DECL|macro|LMC_TDES_SECOND_BUFFER_SIZE
mdefine_line|#define LMC_TDES_SECOND_BUFFER_SIZE      ((u_int32_t)(0x003FF800))
DECL|macro|LMC_TDES_HASH_FILTERING
mdefine_line|#define LMC_TDES_HASH_FILTERING          ((u_int32_t)(0x00400000))
DECL|macro|LMC_TDES_DISABLE_PADDING
mdefine_line|#define LMC_TDES_DISABLE_PADDING         ((u_int32_t)(0x00800000))
DECL|macro|LMC_TDES_SECOND_ADDR_CHAINED
mdefine_line|#define LMC_TDES_SECOND_ADDR_CHAINED     ((u_int32_t)(0x01000000))
DECL|macro|LMC_TDES_END_OF_RING
mdefine_line|#define LMC_TDES_END_OF_RING             ((u_int32_t)(0x02000000))
DECL|macro|LMC_TDES_ADD_CRC_DISABLE
mdefine_line|#define LMC_TDES_ADD_CRC_DISABLE         ((u_int32_t)(0x04000000))
DECL|macro|LMC_TDES_SETUP_PACKET
mdefine_line|#define LMC_TDES_SETUP_PACKET            ((u_int32_t)(0x08000000))
DECL|macro|LMC_TDES_INVERSE_FILTERING
mdefine_line|#define LMC_TDES_INVERSE_FILTERING       ((u_int32_t)(0x10000000))
DECL|macro|LMC_TDES_FIRST_SEGMENT
mdefine_line|#define LMC_TDES_FIRST_SEGMENT           ((u_int32_t)(0x20000000))
DECL|macro|LMC_TDES_LAST_SEGMENT
mdefine_line|#define LMC_TDES_LAST_SEGMENT            ((u_int32_t)(0x40000000))
DECL|macro|LMC_TDES_INTERRUPT_ON_COMPLETION
mdefine_line|#define LMC_TDES_INTERRUPT_ON_COMPLETION ((u_int32_t)(0x80000000))
DECL|macro|TDES_SECOND_BUFFER_SIZE_BIT_NUMBER
mdefine_line|#define TDES_SECOND_BUFFER_SIZE_BIT_NUMBER  11
DECL|macro|TDES_COLLISION_COUNT_BIT_NUMBER
mdefine_line|#define TDES_COLLISION_COUNT_BIT_NUMBER     3
multiline_comment|/* Constants for the RCV descriptor RDES */
DECL|macro|LMC_RDES_OVERFLOW
mdefine_line|#define LMC_RDES_OVERFLOW             ((u_int32_t)(0x00000001))
DECL|macro|LMC_RDES_CRC_ERROR
mdefine_line|#define LMC_RDES_CRC_ERROR            ((u_int32_t)(0x00000002))
DECL|macro|LMC_RDES_DRIBBLING_BIT
mdefine_line|#define LMC_RDES_DRIBBLING_BIT            ((u_int32_t)(0x00000004))
DECL|macro|LMC_RDES_REPORT_ON_MII_ERR
mdefine_line|#define LMC_RDES_REPORT_ON_MII_ERR    ((u_int32_t)(0x00000008))
DECL|macro|LMC_RDES_RCV_WATCHDOG_TIMEOUT
mdefine_line|#define LMC_RDES_RCV_WATCHDOG_TIMEOUT ((u_int32_t)(0x00000010))
DECL|macro|LMC_RDES_FRAME_TYPE
mdefine_line|#define LMC_RDES_FRAME_TYPE           ((u_int32_t)(0x00000020))
DECL|macro|LMC_RDES_COLLISION_SEEN
mdefine_line|#define LMC_RDES_COLLISION_SEEN       ((u_int32_t)(0x00000040))
DECL|macro|LMC_RDES_FRAME_TOO_LONG
mdefine_line|#define LMC_RDES_FRAME_TOO_LONG       ((u_int32_t)(0x00000080))
DECL|macro|LMC_RDES_LAST_DESCRIPTOR
mdefine_line|#define LMC_RDES_LAST_DESCRIPTOR      ((u_int32_t)(0x00000100))
DECL|macro|LMC_RDES_FIRST_DESCRIPTOR
mdefine_line|#define LMC_RDES_FIRST_DESCRIPTOR     ((u_int32_t)(0x00000200))
DECL|macro|LMC_RDES_MULTICAST_FRAME
mdefine_line|#define LMC_RDES_MULTICAST_FRAME      ((u_int32_t)(0x00000400))
DECL|macro|LMC_RDES_RUNT_FRAME
mdefine_line|#define LMC_RDES_RUNT_FRAME           ((u_int32_t)(0x00000800))
DECL|macro|LMC_RDES_DATA_TYPE
mdefine_line|#define LMC_RDES_DATA_TYPE            ((u_int32_t)(0x00003000))
DECL|macro|LMC_RDES_LENGTH_ERROR
mdefine_line|#define LMC_RDES_LENGTH_ERROR         ((u_int32_t)(0x00004000))
DECL|macro|LMC_RDES_ERROR_SUMMARY
mdefine_line|#define LMC_RDES_ERROR_SUMMARY        ((u_int32_t)(0x00008000))
DECL|macro|LMC_RDES_FRAME_LENGTH
mdefine_line|#define LMC_RDES_FRAME_LENGTH         ((u_int32_t)(0x3FFF0000))
DECL|macro|LMC_RDES_OWN_BIT
mdefine_line|#define LMC_RDES_OWN_BIT              ((u_int32_t)(0x80000000))
DECL|macro|RDES_FRAME_LENGTH_BIT_NUMBER
mdefine_line|#define RDES_FRAME_LENGTH_BIT_NUMBER       16
DECL|macro|LMC_RDES_ERROR_MASK
mdefine_line|#define LMC_RDES_ERROR_MASK ( (u_int32_t)( &bslash;&n;&t;  LMC_RDES_OVERFLOW &bslash;&n;&t;| LMC_RDES_DRIBBLING_BIT &bslash;&n;&t;| LMC_RDES_REPORT_ON_MII_ERR &bslash;&n;        | LMC_RDES_COLLISION_SEEN ) )
multiline_comment|/*&n; * Ioctl info&n; */
r_typedef
r_struct
(brace
DECL|member|n
id|u_int32_t
id|n
suffix:semicolon
DECL|member|m
id|u_int32_t
id|m
suffix:semicolon
DECL|member|v
id|u_int32_t
id|v
suffix:semicolon
DECL|member|x
id|u_int32_t
id|x
suffix:semicolon
DECL|member|r
id|u_int32_t
id|r
suffix:semicolon
DECL|member|f
id|u_int32_t
id|f
suffix:semicolon
DECL|member|exact
id|u_int32_t
id|exact
suffix:semicolon
DECL|typedef|lmc_av9110_t
)brace
id|lmc_av9110_t
suffix:semicolon
multiline_comment|/*&n; * Common structure passed to the ioctl code.&n; */
DECL|struct|lmc___ctl
r_struct
id|lmc___ctl
(brace
DECL|member|cardtype
id|u_int32_t
id|cardtype
suffix:semicolon
DECL|member|clock_source
id|u_int32_t
id|clock_source
suffix:semicolon
multiline_comment|/* HSSI, T1 */
DECL|member|clock_rate
id|u_int32_t
id|clock_rate
suffix:semicolon
multiline_comment|/* T1 */
DECL|member|crc_length
id|u_int32_t
id|crc_length
suffix:semicolon
DECL|member|cable_length
id|u_int32_t
id|cable_length
suffix:semicolon
multiline_comment|/* DS3 */
DECL|member|scrambler_onoff
id|u_int32_t
id|scrambler_onoff
suffix:semicolon
multiline_comment|/* DS3 */
DECL|member|cable_type
id|u_int32_t
id|cable_type
suffix:semicolon
multiline_comment|/* T1 */
DECL|member|keepalive_onoff
id|u_int32_t
id|keepalive_onoff
suffix:semicolon
multiline_comment|/* protocol */
DECL|member|ticks
id|u_int32_t
id|ticks
suffix:semicolon
multiline_comment|/* ticks/sec */
r_union
(brace
DECL|member|ssi
id|lmc_av9110_t
id|ssi
suffix:semicolon
DECL|member|cardspec
)brace
id|cardspec
suffix:semicolon
DECL|member|circuit_type
id|u_int32_t
id|circuit_type
suffix:semicolon
multiline_comment|/* T1 or E1 */
)brace
suffix:semicolon
multiline_comment|/*&n; * Carefull, look at the data sheet, there&squot;s more to this&n; * structure than meets the eye.  It should probably be:&n; *&n; * struct tulip_desc_t {&n; *         u8  own:1;&n; *         u32 status:31;&n; *         u32 control:10;&n; *         u32 buffer1;&n; *         u32 buffer2;&n; * };&n; * You could also expand status control to provide more bit information&n; */
DECL|struct|tulip_desc_t
r_struct
id|tulip_desc_t
(brace
DECL|member|status
id|s32
id|status
suffix:semicolon
DECL|member|length
id|s32
id|length
suffix:semicolon
DECL|member|buffer1
id|u32
id|buffer1
suffix:semicolon
DECL|member|buffer2
id|u32
id|buffer2
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * media independent methods to check on media status, link, light LEDs,&n; * etc.&n; */
DECL|struct|lmc___media
r_struct
id|lmc___media
(brace
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
id|lmc_softc_t
op_star
r_const
)paren
suffix:semicolon
DECL|member|defaults
r_void
(paren
op_star
id|defaults
)paren
(paren
id|lmc_softc_t
op_star
r_const
)paren
suffix:semicolon
DECL|member|set_status
r_void
(paren
op_star
id|set_status
)paren
(paren
id|lmc_softc_t
op_star
r_const
comma
id|lmc_ctl_t
op_star
)paren
suffix:semicolon
DECL|member|set_clock_source
r_void
(paren
op_star
id|set_clock_source
)paren
(paren
id|lmc_softc_t
op_star
r_const
comma
r_int
)paren
suffix:semicolon
DECL|member|set_speed
r_void
(paren
op_star
id|set_speed
)paren
(paren
id|lmc_softc_t
op_star
r_const
comma
id|lmc_ctl_t
op_star
)paren
suffix:semicolon
DECL|member|set_cable_length
r_void
(paren
op_star
id|set_cable_length
)paren
(paren
id|lmc_softc_t
op_star
r_const
comma
r_int
)paren
suffix:semicolon
DECL|member|set_scrambler
r_void
(paren
op_star
id|set_scrambler
)paren
(paren
id|lmc_softc_t
op_star
r_const
comma
r_int
)paren
suffix:semicolon
DECL|member|get_link_status
r_int
(paren
op_star
id|get_link_status
)paren
(paren
id|lmc_softc_t
op_star
r_const
)paren
suffix:semicolon
DECL|member|set_link_status
r_void
(paren
op_star
id|set_link_status
)paren
(paren
id|lmc_softc_t
op_star
r_const
comma
r_int
)paren
suffix:semicolon
DECL|member|set_crc_length
r_void
(paren
op_star
id|set_crc_length
)paren
(paren
id|lmc_softc_t
op_star
r_const
comma
r_int
)paren
suffix:semicolon
DECL|member|set_circuit_type
r_void
(paren
op_star
id|set_circuit_type
)paren
(paren
id|lmc_softc_t
op_star
r_const
comma
r_int
)paren
suffix:semicolon
DECL|member|watchdog
r_void
(paren
op_star
id|watchdog
)paren
(paren
id|lmc_softc_t
op_star
r_const
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|STATCHECK
mdefine_line|#define STATCHECK     0xBEEFCAFE
multiline_comment|/*  Included in this structure are first&n; *   - standard net_device_stats&n; *   - some other counters used for debug and driver performance&n; *  evaluation -baz&n; */
DECL|struct|lmc_statistics
r_struct
id|lmc_statistics
(brace
DECL|member|rx_packets
r_int
r_int
id|rx_packets
suffix:semicolon
multiline_comment|/* total packets received       */
DECL|member|tx_packets
r_int
r_int
id|tx_packets
suffix:semicolon
multiline_comment|/* total packets transmitted    */
DECL|member|rx_bytes
r_int
r_int
id|rx_bytes
suffix:semicolon
DECL|member|tx_bytes
r_int
r_int
id|tx_bytes
suffix:semicolon
DECL|member|rx_errors
r_int
r_int
id|rx_errors
suffix:semicolon
multiline_comment|/* bad packets received         */
DECL|member|tx_errors
r_int
r_int
id|tx_errors
suffix:semicolon
multiline_comment|/* packet transmit problems     */
DECL|member|rx_dropped
r_int
r_int
id|rx_dropped
suffix:semicolon
multiline_comment|/* no space in linux buffers    */
DECL|member|tx_dropped
r_int
r_int
id|tx_dropped
suffix:semicolon
multiline_comment|/* no space available in linux  */
DECL|member|multicast
r_int
r_int
id|multicast
suffix:semicolon
multiline_comment|/* multicast packets received   */
DECL|member|collisions
r_int
r_int
id|collisions
suffix:semicolon
multiline_comment|/* detailed rx_errors: */
DECL|member|rx_length_errors
r_int
r_int
id|rx_length_errors
suffix:semicolon
DECL|member|rx_over_errors
r_int
r_int
id|rx_over_errors
suffix:semicolon
multiline_comment|/* receiver ring buff overflow  */
DECL|member|rx_crc_errors
r_int
r_int
id|rx_crc_errors
suffix:semicolon
multiline_comment|/* recved pkt with crc error    */
DECL|member|rx_frame_errors
r_int
r_int
id|rx_frame_errors
suffix:semicolon
multiline_comment|/* recv&squot;d frame alignment error */
DECL|member|rx_fifo_errors
r_int
r_int
id|rx_fifo_errors
suffix:semicolon
multiline_comment|/* recv&squot;r fifo overrun          */
DECL|member|rx_missed_errors
r_int
r_int
id|rx_missed_errors
suffix:semicolon
multiline_comment|/* receiver missed packet       */
multiline_comment|/* detailed tx_errors */
DECL|member|tx_aborted_errors
r_int
r_int
id|tx_aborted_errors
suffix:semicolon
DECL|member|tx_carrier_errors
r_int
r_int
id|tx_carrier_errors
suffix:semicolon
DECL|member|tx_fifo_errors
r_int
r_int
id|tx_fifo_errors
suffix:semicolon
DECL|member|tx_heartbeat_errors
r_int
r_int
id|tx_heartbeat_errors
suffix:semicolon
DECL|member|tx_window_errors
r_int
r_int
id|tx_window_errors
suffix:semicolon
multiline_comment|/* for cslip etc */
DECL|member|rx_compressed
r_int
r_int
id|rx_compressed
suffix:semicolon
DECL|member|tx_compressed
r_int
r_int
id|tx_compressed
suffix:semicolon
multiline_comment|/* -------------------------------------&n;         * Custom stats &amp; counters follow -baz */
DECL|member|version_size
id|u_int32_t
id|version_size
suffix:semicolon
DECL|member|lmc_cardtype
id|u_int32_t
id|lmc_cardtype
suffix:semicolon
DECL|member|tx_ProcTimeout
id|u_int32_t
id|tx_ProcTimeout
suffix:semicolon
DECL|member|tx_IntTimeout
id|u_int32_t
id|tx_IntTimeout
suffix:semicolon
DECL|member|tx_NoCompleteCnt
id|u_int32_t
id|tx_NoCompleteCnt
suffix:semicolon
DECL|member|tx_MaxXmtsB4Int
id|u_int32_t
id|tx_MaxXmtsB4Int
suffix:semicolon
DECL|member|tx_TimeoutCnt
id|u_int32_t
id|tx_TimeoutCnt
suffix:semicolon
DECL|member|tx_OutOfSyncPtr
id|u_int32_t
id|tx_OutOfSyncPtr
suffix:semicolon
DECL|member|tx_tbusy0
id|u_int32_t
id|tx_tbusy0
suffix:semicolon
DECL|member|tx_tbusy1
id|u_int32_t
id|tx_tbusy1
suffix:semicolon
DECL|member|tx_tbusy_calls
id|u_int32_t
id|tx_tbusy_calls
suffix:semicolon
DECL|member|resetCount
id|u_int32_t
id|resetCount
suffix:semicolon
DECL|member|lmc_txfull
id|u_int32_t
id|lmc_txfull
suffix:semicolon
DECL|member|tbusy
id|u_int32_t
id|tbusy
suffix:semicolon
DECL|member|dirtyTx
id|u_int32_t
id|dirtyTx
suffix:semicolon
DECL|member|lmc_next_tx
id|u_int32_t
id|lmc_next_tx
suffix:semicolon
DECL|member|otherTypeCnt
id|u_int32_t
id|otherTypeCnt
suffix:semicolon
DECL|member|lastType
id|u_int32_t
id|lastType
suffix:semicolon
DECL|member|lastTypeOK
id|u_int32_t
id|lastTypeOK
suffix:semicolon
DECL|member|txLoopCnt
id|u_int32_t
id|txLoopCnt
suffix:semicolon
DECL|member|usedXmtDescripCnt
id|u_int32_t
id|usedXmtDescripCnt
suffix:semicolon
DECL|member|txIndexCnt
id|u_int32_t
id|txIndexCnt
suffix:semicolon
DECL|member|rxIntLoopCnt
id|u_int32_t
id|rxIntLoopCnt
suffix:semicolon
DECL|member|rx_SmallPktCnt
id|u_int32_t
id|rx_SmallPktCnt
suffix:semicolon
DECL|member|rx_BadPktSurgeCnt
id|u_int32_t
id|rx_BadPktSurgeCnt
suffix:semicolon
DECL|member|rx_BuffAllocErr
id|u_int32_t
id|rx_BuffAllocErr
suffix:semicolon
DECL|member|tx_lossOfClockCnt
id|u_int32_t
id|tx_lossOfClockCnt
suffix:semicolon
multiline_comment|/* T1 error counters */
DECL|member|framingBitErrorCount
id|u_int32_t
id|framingBitErrorCount
suffix:semicolon
DECL|member|lineCodeViolationCount
id|u_int32_t
id|lineCodeViolationCount
suffix:semicolon
DECL|member|lossOfFrameCount
id|u_int32_t
id|lossOfFrameCount
suffix:semicolon
DECL|member|changeOfFrameAlignmentCount
id|u_int32_t
id|changeOfFrameAlignmentCount
suffix:semicolon
DECL|member|severelyErroredFrameCount
id|u_int32_t
id|severelyErroredFrameCount
suffix:semicolon
DECL|member|check
id|u_int32_t
id|check
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|lmc_xinfo
r_typedef
r_struct
id|lmc_xinfo
(brace
DECL|member|Magic0
id|u_int32_t
id|Magic0
suffix:semicolon
multiline_comment|/* BEEFCAFE */
DECL|member|PciCardType
id|u_int32_t
id|PciCardType
suffix:semicolon
DECL|member|PciSlotNumber
id|u_int32_t
id|PciSlotNumber
suffix:semicolon
multiline_comment|/* PCI slot number       */
DECL|member|DriverMajorVersion
id|u_int16_t
id|DriverMajorVersion
suffix:semicolon
DECL|member|DriverMinorVersion
id|u_int16_t
id|DriverMinorVersion
suffix:semicolon
DECL|member|DriverSubVersion
id|u_int16_t
id|DriverSubVersion
suffix:semicolon
DECL|member|XilinxRevisionNumber
id|u_int16_t
id|XilinxRevisionNumber
suffix:semicolon
DECL|member|MaxFrameSize
id|u_int16_t
id|MaxFrameSize
suffix:semicolon
DECL|member|t1_alarm1_status
id|u_int16_t
id|t1_alarm1_status
suffix:semicolon
DECL|member|t1_alarm2_status
id|u_int16_t
id|t1_alarm2_status
suffix:semicolon
DECL|member|link_status
r_int
id|link_status
suffix:semicolon
DECL|member|mii_reg16
id|u_int32_t
id|mii_reg16
suffix:semicolon
DECL|member|Magic1
id|u_int32_t
id|Magic1
suffix:semicolon
multiline_comment|/* DEADBEEF */
DECL|typedef|LMC_XINFO
)brace
id|LMC_XINFO
suffix:semicolon
multiline_comment|/*&n; * forward decl&n; */
DECL|struct|lmc___softc
r_struct
id|lmc___softc
(brace
DECL|member|if_ptr
r_void
op_star
id|if_ptr
suffix:semicolon
multiline_comment|/* General purpose pointer (used by SPPP) */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|board_idx
id|u8
id|board_idx
suffix:semicolon
DECL|member|stats
r_struct
id|lmc_statistics
id|stats
suffix:semicolon
DECL|member|lmc_device
r_struct
id|net_device
op_star
id|lmc_device
suffix:semicolon
DECL|member|hang
DECL|member|rxdesc
DECL|member|bad_packet
DECL|member|some_counter
r_int
id|hang
comma
id|rxdesc
comma
id|bad_packet
comma
id|some_counter
suffix:semicolon
DECL|member|txgo
id|u_int32_t
id|txgo
suffix:semicolon
DECL|member|lmc_csrs
r_struct
id|lmc_regfile_t
id|lmc_csrs
suffix:semicolon
DECL|member|lmc_txtick
r_volatile
id|u_int32_t
id|lmc_txtick
suffix:semicolon
DECL|member|lmc_rxtick
r_volatile
id|u_int32_t
id|lmc_rxtick
suffix:semicolon
DECL|member|lmc_flags
id|u_int32_t
id|lmc_flags
suffix:semicolon
DECL|member|lmc_intrmask
id|u_int32_t
id|lmc_intrmask
suffix:semicolon
multiline_comment|/* our copy of csr_intr */
DECL|member|lmc_cmdmode
id|u_int32_t
id|lmc_cmdmode
suffix:semicolon
multiline_comment|/* our copy of csr_cmdmode */
DECL|member|lmc_busmode
id|u_int32_t
id|lmc_busmode
suffix:semicolon
multiline_comment|/* our copy of csr_busmode */
DECL|member|lmc_gpio_io
id|u_int32_t
id|lmc_gpio_io
suffix:semicolon
multiline_comment|/* state of in/out settings */
DECL|member|lmc_gpio
id|u_int32_t
id|lmc_gpio
suffix:semicolon
multiline_comment|/* state of outputs */
DECL|member|lmc_txq
r_struct
id|sk_buff
op_star
id|lmc_txq
(braket
id|LMC_TXDESCS
)braket
suffix:semicolon
DECL|member|lmc_rxq
r_struct
id|sk_buff
op_star
id|lmc_rxq
(braket
id|LMC_RXDESCS
)braket
suffix:semicolon
r_volatile
DECL|member|lmc_rxring
r_struct
id|tulip_desc_t
id|lmc_rxring
(braket
id|LMC_RXDESCS
)braket
suffix:semicolon
r_volatile
DECL|member|lmc_txring
r_struct
id|tulip_desc_t
id|lmc_txring
(braket
id|LMC_TXDESCS
)braket
suffix:semicolon
DECL|member|lmc_next_rx
DECL|member|lmc_next_tx
r_int
r_int
id|lmc_next_rx
comma
id|lmc_next_tx
suffix:semicolon
r_volatile
DECL|member|lmc_taint_tx
DECL|member|lmc_taint_rx
r_int
r_int
id|lmc_taint_tx
comma
id|lmc_taint_rx
suffix:semicolon
DECL|member|lmc_tx_start
DECL|member|lmc_txfull
r_int
id|lmc_tx_start
comma
id|lmc_txfull
suffix:semicolon
DECL|member|lmc_txbusy
r_int
id|lmc_txbusy
suffix:semicolon
DECL|member|lmc_miireg16
id|u_int16_t
id|lmc_miireg16
suffix:semicolon
DECL|member|lmc_ok
r_int
id|lmc_ok
suffix:semicolon
DECL|member|last_link_status
r_int
id|last_link_status
suffix:semicolon
DECL|member|lmc_cardtype
r_int
id|lmc_cardtype
suffix:semicolon
DECL|member|last_frameerr
id|u_int32_t
id|last_frameerr
suffix:semicolon
DECL|member|lmc_media
id|lmc_media_t
op_star
id|lmc_media
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|ictl
id|lmc_ctl_t
id|ictl
suffix:semicolon
DECL|member|TxDescriptControlInit
id|u_int32_t
id|TxDescriptControlInit
suffix:semicolon
DECL|member|next_module
r_struct
id|net_device
op_star
id|next_module
suffix:semicolon
multiline_comment|/* Link to the next module  */
DECL|member|tx_TimeoutInd
r_int
id|tx_TimeoutInd
suffix:semicolon
multiline_comment|/* additional driver state */
DECL|member|tx_TimeoutDisplay
r_int
id|tx_TimeoutDisplay
suffix:semicolon
DECL|member|lastlmc_taint_tx
r_int
r_int
id|lastlmc_taint_tx
suffix:semicolon
DECL|member|lasttx_packets
r_int
id|lasttx_packets
suffix:semicolon
DECL|member|tx_clockState
id|u_int32_t
id|tx_clockState
suffix:semicolon
DECL|member|lmc_crcSize
id|u_int32_t
id|lmc_crcSize
suffix:semicolon
DECL|member|lmc_xinfo
id|LMC_XINFO
id|lmc_xinfo
suffix:semicolon
DECL|member|lmc_yel
DECL|member|lmc_blue
DECL|member|lmc_red
r_char
id|lmc_yel
comma
id|lmc_blue
comma
id|lmc_red
suffix:semicolon
multiline_comment|/* for T1 and DS3 */
DECL|member|lmc_timing
r_char
id|lmc_timing
suffix:semicolon
multiline_comment|/* for HSSI and SSI */
DECL|member|got_irq
r_int
id|got_irq
suffix:semicolon
DECL|member|last_led_err
r_char
id|last_led_err
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|last_int
id|u32
id|last_int
suffix:semicolon
DECL|member|num_int
id|u32
id|num_int
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x20200
DECL|member|lmc_lock
id|spinlock_t
id|lmc_lock
suffix:semicolon
macro_line|#endif
DECL|member|if_type
id|u_int16_t
id|if_type
suffix:semicolon
multiline_comment|/* PPP or NET */
DECL|member|pd
r_struct
id|ppp_device
op_star
id|pd
suffix:semicolon
multiline_comment|/* Failure cases */
DECL|member|failed_ring
id|u8
id|failed_ring
suffix:semicolon
DECL|member|failed_recv_alloc
id|u8
id|failed_recv_alloc
suffix:semicolon
multiline_comment|/* Structure check */
DECL|member|check
id|u32
id|check
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|LMC_PCI_TIME
mdefine_line|#define LMC_PCI_TIME 1
DECL|macro|LMC_EXT_TIME
mdefine_line|#define LMC_EXT_TIME 0
DECL|macro|PKT_BUF_SZ
mdefine_line|#define PKT_BUF_SZ              1542  /* was 1536 */
multiline_comment|/* CSR5 settings */
DECL|macro|TIMER_INT
mdefine_line|#define TIMER_INT     0x00000800
DECL|macro|TP_LINK_FAIL
mdefine_line|#define TP_LINK_FAIL  0x00001000
DECL|macro|TP_LINK_PASS
mdefine_line|#define TP_LINK_PASS  0x00000010
DECL|macro|NORMAL_INT
mdefine_line|#define NORMAL_INT    0x00010000
DECL|macro|ABNORMAL_INT
mdefine_line|#define ABNORMAL_INT  0x00008000
DECL|macro|RX_JABBER_INT
mdefine_line|#define RX_JABBER_INT 0x00000200
DECL|macro|RX_DIED
mdefine_line|#define RX_DIED       0x00000100
DECL|macro|RX_NOBUFF
mdefine_line|#define RX_NOBUFF     0x00000080
DECL|macro|RX_INT
mdefine_line|#define RX_INT        0x00000040
DECL|macro|TX_FIFO_UNDER
mdefine_line|#define TX_FIFO_UNDER 0x00000020
DECL|macro|TX_JABBER
mdefine_line|#define TX_JABBER     0x00000008
DECL|macro|TX_NOBUFF
mdefine_line|#define TX_NOBUFF     0x00000004
DECL|macro|TX_DIED
mdefine_line|#define TX_DIED       0x00000002
DECL|macro|TX_INT
mdefine_line|#define TX_INT        0x00000001
multiline_comment|/* CSR6 settings */
DECL|macro|OPERATION_MODE
mdefine_line|#define OPERATION_MODE  0x00000200 /* Full Duplex      */
DECL|macro|PROMISC_MODE
mdefine_line|#define PROMISC_MODE    0x00000040 /* Promiscuous Mode */
DECL|macro|RECIEVE_ALL
mdefine_line|#define RECIEVE_ALL     0x40000000 /* Recieve All      */
DECL|macro|PASS_BAD_FRAMES
mdefine_line|#define PASS_BAD_FRAMES 0x00000008 /* Pass Bad Frames  */
multiline_comment|/* Dec control registers  CSR6 as well */
DECL|macro|LMC_DEC_ST
mdefine_line|#define LMC_DEC_ST 0x00002000
DECL|macro|LMC_DEC_SR
mdefine_line|#define LMC_DEC_SR 0x00000002
multiline_comment|/* CSR15 settings */
DECL|macro|RECV_WATCHDOG_DISABLE
mdefine_line|#define RECV_WATCHDOG_DISABLE 0x00000010
DECL|macro|JABBER_DISABLE
mdefine_line|#define JABBER_DISABLE        0x00000001
multiline_comment|/* More settings */
multiline_comment|/*&n; * aSR6 -- Command (Operation Mode) Register&n; */
DECL|macro|TULIP_CMD_RECEIVEALL
mdefine_line|#define TULIP_CMD_RECEIVEALL    0x40000000L /* (RW)  Receivel all frames? */
DECL|macro|TULIP_CMD_MUSTBEONE
mdefine_line|#define TULIP_CMD_MUSTBEONE     0x02000000L /* (RW)  Must Be One (21140) */
DECL|macro|TULIP_CMD_TXTHRSHLDCTL
mdefine_line|#define TULIP_CMD_TXTHRSHLDCTL  0x00400000L /* (RW)  Transmit Threshold Mode (21140) */
DECL|macro|TULIP_CMD_STOREFWD
mdefine_line|#define TULIP_CMD_STOREFWD      0x00200000L /* (RW)  Store and Foward (21140) */
DECL|macro|TULIP_CMD_NOHEARTBEAT
mdefine_line|#define TULIP_CMD_NOHEARTBEAT   0x00080000L /* (RW)  No Heartbeat (21140) */
DECL|macro|TULIP_CMD_PORTSELECT
mdefine_line|#define TULIP_CMD_PORTSELECT    0x00040000L /* (RW)  Post Select (100Mb) (21140) */
DECL|macro|TULIP_CMD_FULLDUPLEX
mdefine_line|#define TULIP_CMD_FULLDUPLEX    0x00000200L /* (RW)  Full Duplex Mode */
DECL|macro|TULIP_CMD_OPERMODE
mdefine_line|#define TULIP_CMD_OPERMODE      0x00000C00L /* (RW)  Operating Mode */
DECL|macro|TULIP_CMD_PROMISCUOUS
mdefine_line|#define TULIP_CMD_PROMISCUOUS   0x00000041L /* (RW)  Promiscuous Mode */
DECL|macro|TULIP_CMD_PASSBADPKT
mdefine_line|#define TULIP_CMD_PASSBADPKT    0x00000008L /* (RW)  Pass Bad Frames */
DECL|macro|TULIP_CMD_THRESHOLDCTL
mdefine_line|#define TULIP_CMD_THRESHOLDCTL  0x0000C000L /* (RW)  Threshold Control */
DECL|macro|TULIP_GP_PINSET
mdefine_line|#define TULIP_GP_PINSET         0x00000100L
DECL|macro|TULIP_BUSMODE_SWRESET
mdefine_line|#define TULIP_BUSMODE_SWRESET   0x00000001L
DECL|macro|TULIP_WATCHDOG_TXDISABLE
mdefine_line|#define TULIP_WATCHDOG_TXDISABLE 0x00000001L
DECL|macro|TULIP_WATCHDOG_RXDISABLE
mdefine_line|#define TULIP_WATCHDOG_RXDISABLE 0x00000010L
DECL|macro|TULIP_STS_NORMALINTR
mdefine_line|#define TULIP_STS_NORMALINTR    0x00010000L /* (RW)  Normal Interrupt */
DECL|macro|TULIP_STS_ABNRMLINTR
mdefine_line|#define TULIP_STS_ABNRMLINTR    0x00008000L /* (RW)  Abnormal Interrupt */
DECL|macro|TULIP_STS_ERI
mdefine_line|#define TULIP_STS_ERI           0x00004000L /* (RW)  Early Receive Interupt */
DECL|macro|TULIP_STS_SYSERROR
mdefine_line|#define TULIP_STS_SYSERROR      0x00002000L /* (RW)  System Error */
DECL|macro|TULIP_STS_GTE
mdefine_line|#define TULIP_STS_GTE           0x00000800L /* (RW)  General Pupose Timer Exp */
DECL|macro|TULIP_STS_ETI
mdefine_line|#define TULIP_STS_ETI           0x00000400L /* (RW)  Early Transmit Interupt */
DECL|macro|TULIP_STS_RXWT
mdefine_line|#define TULIP_STS_RXWT          0x00000200L /* (RW)  Receiver Watchdog Timeout */
DECL|macro|TULIP_STS_RXSTOPPED
mdefine_line|#define TULIP_STS_RXSTOPPED     0x00000100L /* (RW)  Receiver Process Stopped */
DECL|macro|TULIP_STS_RXNOBUF
mdefine_line|#define TULIP_STS_RXNOBUF       0x00000080L /* (RW)  Receive Buf Unavail */
DECL|macro|TULIP_STS_RXINTR
mdefine_line|#define TULIP_STS_RXINTR        0x00000040L /* (RW)  Receive Interrupt */
DECL|macro|TULIP_STS_TXUNDERFLOW
mdefine_line|#define TULIP_STS_TXUNDERFLOW   0x00000020L /* (RW)  Transmit Underflow */
DECL|macro|TULIP_STS_TXJABER
mdefine_line|#define TULIP_STS_TXJABER       0x00000008L /* (RW)  Jabber timeout */
DECL|macro|TULIP_STS_TXNOBUF
mdefine_line|#define TULIP_STS_TXNOBUF       0x00000004L
DECL|macro|TULIP_STS_TXSTOPPED
mdefine_line|#define TULIP_STS_TXSTOPPED     0x00000002L /* (RW)  Transmit Process Stopped */
DECL|macro|TULIP_STS_TXINTR
mdefine_line|#define TULIP_STS_TXINTR        0x00000001L /* (RW)  Transmit Interrupt */
DECL|macro|TULIP_STS_RXS_STOPPED
mdefine_line|#define TULIP_STS_RXS_STOPPED   0x00000000L /*        000 - Stopped */
DECL|macro|TULIP_STS_RXSTOPPED
mdefine_line|#define TULIP_STS_RXSTOPPED     0x00000100L             /* (RW)  Receive Process Stopped */
DECL|macro|TULIP_STS_RXNOBUF
mdefine_line|#define TULIP_STS_RXNOBUF       0x00000080L
DECL|macro|TULIP_CMD_TXRUN
mdefine_line|#define TULIP_CMD_TXRUN         0x00002000L /* (RW)  Start/Stop Transmitter */
DECL|macro|TULIP_CMD_RXRUN
mdefine_line|#define TULIP_CMD_RXRUN         0x00000002L /* (RW)  Start/Stop Receive Filtering */
DECL|macro|TULIP_DSTS_TxDEFERRED
mdefine_line|#define TULIP_DSTS_TxDEFERRED   0x00000001      /* Initially Deferred */
DECL|macro|TULIP_DSTS_OWNER
mdefine_line|#define TULIP_DSTS_OWNER        0x80000000      /* Owner (1 = 21040) */
DECL|macro|TULIP_DSTS_RxMIIERR
mdefine_line|#define TULIP_DSTS_RxMIIERR     0x00000008
DECL|macro|LMC_DSTS_ERRSUM
mdefine_line|#define LMC_DSTS_ERRSUM         (TULIP_DSTS_RxMIIERR)
DECL|macro|TULIP_DEFAULT_INTR_MASK
mdefine_line|#define TULIP_DEFAULT_INTR_MASK  (TULIP_STS_NORMALINTR &bslash;&n;  | TULIP_STS_RXINTR       &bslash;&n;  | TULIP_STS_TXINTR     &bslash;&n;  | TULIP_STS_ABNRMLINTR &bslash;&n;  | TULIP_STS_SYSERROR   &bslash;&n;  | TULIP_STS_TXSTOPPED  &bslash;&n;  | TULIP_STS_TXUNDERFLOW&bslash;&n;  | TULIP_STS_RXSTOPPED )
DECL|macro|DESC_OWNED_BY_SYSTEM
mdefine_line|#define DESC_OWNED_BY_SYSTEM   ((u_int32_t)(0x00000000))
DECL|macro|DESC_OWNED_BY_DC21X4
mdefine_line|#define DESC_OWNED_BY_DC21X4   ((u_int32_t)(0x80000000))
macro_line|#ifndef TULIP_CMD_RECEIVEALL
DECL|macro|TULIP_CMD_RECEIVEALL
mdefine_line|#define TULIP_CMD_RECEIVEALL 0x40000000L
macro_line|#endif
multiline_comment|/* PCI register values */
DECL|macro|CORRECT_VENDOR_ID
mdefine_line|#define CORRECT_VENDOR_ID    0x1011
DECL|macro|CORRECT_DEV_ID
mdefine_line|#define CORRECT_DEV_ID       9
DECL|macro|PCI_VENDOR_LMC
mdefine_line|#define PCI_VENDOR_LMC&t;&t;0x1376
DECL|macro|PCI_PRODUCT_LMC_HSSI
mdefine_line|#define PCI_PRODUCT_LMC_HSSI&t;0x0003
DECL|macro|PCI_PRODUCT_LMC_DS3
mdefine_line|#define PCI_PRODUCT_LMC_DS3&t;0x0004
DECL|macro|PCI_PRODUCT_LMC_SSI
mdefine_line|#define PCI_PRODUCT_LMC_SSI&t;0x0005
DECL|macro|PCI_PRODUCT_LMC_T1
mdefine_line|#define PCI_PRODUCT_LMC_T1      0x0006
multiline_comment|/* Adapcter module number */
DECL|macro|LMC_ADAP_HSSI
mdefine_line|#define LMC_ADAP_HSSI           2
DECL|macro|LMC_ADAP_DS3
mdefine_line|#define LMC_ADAP_DS3            3
DECL|macro|LMC_ADAP_SSI
mdefine_line|#define LMC_ADAP_SSI            4
DECL|macro|LMC_ADAP_T1
mdefine_line|#define LMC_ADAP_T1             5
DECL|macro|HDLC_HDR_LEN
mdefine_line|#define HDLC_HDR_LEN  4
DECL|macro|HDLC_ADDR_LEN
mdefine_line|#define HDLC_ADDR_LEN 1
DECL|macro|HDLC_SLARP
mdefine_line|#define HDLC_SLARP    0x8035
DECL|macro|LMC_MTU
mdefine_line|#define LMC_MTU 1500
DECL|macro|SLARP_LINECHECK
mdefine_line|#define SLARP_LINECHECK 2
DECL|macro|LMC_CRC_LEN_16
mdefine_line|#define LMC_CRC_LEN_16 2  /* 16-bit CRC */
DECL|macro|LMC_CRC_LEN_32
mdefine_line|#define LMC_CRC_LEN_32 4
macro_line|#if LINUX_VERSION_CODE &lt; 0x20100
DECL|macro|test_and_set_bit
mdefine_line|#define test_and_set_bit(val, addr) set_bit(val, addr)
macro_line|#endif
macro_line|#ifdef LMC_HDLC
multiline_comment|/* definition of an hdlc header. */
DECL|struct|hdlc_hdr
r_struct
id|hdlc_hdr
(brace
DECL|member|address
id|u8
id|address
suffix:semicolon
DECL|member|control
id|u8
id|control
suffix:semicolon
DECL|member|type
id|u16
id|type
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* definition of a slarp header. */
DECL|struct|slarp
r_struct
id|slarp
(brace
DECL|member|code
r_int
id|code
suffix:semicolon
DECL|union|sl
r_union
id|sl
(brace
r_struct
(brace
DECL|member|address
id|ulong
id|address
suffix:semicolon
DECL|member|mask
id|ulong
id|mask
suffix:semicolon
DECL|member|unused
id|ushort
id|unused
suffix:semicolon
DECL|member|add
)brace
id|add
suffix:semicolon
r_struct
(brace
DECL|member|mysequence
id|ulong
id|mysequence
suffix:semicolon
DECL|member|yoursequence
id|ulong
id|yoursequence
suffix:semicolon
DECL|member|reliability
id|ushort
id|reliability
suffix:semicolon
DECL|member|time
id|ulong
id|time
suffix:semicolon
DECL|member|chk
)brace
id|chk
suffix:semicolon
DECL|member|t
)brace
id|t
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* LMC_HDLC */
macro_line|#endif /* _LMC_VAR_H_ */
eof
