multiline_comment|/*************************************************************************&n; sdla_chdlc.h&t;Sangoma Cisco HDLC firmware API definitions&n;&n; Author:      &t;Gideon Hack&n;&t;&t;Nenad Corbic &lt;ncorbic@sangoma.com&gt;&t;&n;&n; Copyright:&t;(c) 1995-1999 Sangoma Technologies Inc.&n;&n;&t;&t;This program is free software; you can redistribute it and/or&n;&t;&t;modify it under the term of the GNU General Public License&n;&t;&t;as published by the Free Software Foundation; either version&n;&t;&t;2 of the License, or (at your option) any later version.&n;&n;===========================================================================&n;  Oct 04, 1999  Nenad Corbic    Updated API support&n;  Jun 02, 1999  Gideon Hack     Changes for S514 usage.&n;  Oct 28, 1998&t;Jaspreet Singh&t;Made changes for Dual Port CHDLC.&n;  Jun 11, 1998&t;David Fong&t;Initial version.&n;===========================================================================&n;&n; Organization&n;&t;- Compatibility notes&n;&t;- Constants defining the shared memory control block (mailbox)&n;&t;- Interface commands&n;&t;- Return code from interface commands&n;&t;- Constants for the commands (structures for casting data)&n;&t;- UDP Management constants and structures&n;&n;*************************************************************************/
macro_line|#ifndef _SDLA_CHDLC_H
DECL|macro|_SDLC_CHDLC_H
macro_line|#  define _SDLC_CHDLC_H
multiline_comment|/*------------------------------------------------------------------------&n;   Notes:&n;&n;&t;All structres defined in this file are byte-aligned.  &n;&n;&t;Compiler&t;Platform&n;&t;------------------------&n;&t;GNU C&t;&t;Linux&n;&n;------------------------------------------------------------------------*/
macro_line|#ifndef&t;PACKED
DECL|macro|PACKED
mdefine_line|#define&t;PACKED __attribute__((packed))
macro_line|#endif&t;/* PACKED */
multiline_comment|/* ----------------------------------------------------------------------------&n; *        Constants defining the shared memory control block (mailbox)&n; * --------------------------------------------------------------------------*/
DECL|macro|PRI_BASE_ADDR_MB_STRUCT
mdefine_line|#define PRI_BASE_ADDR_MB_STRUCT &t;0xE000 &t;/* the base address of the mailbox structure on the adapter */
DECL|macro|SEC_BASE_ADDR_MB_STRUCT
mdefine_line|#define SEC_BASE_ADDR_MB_STRUCT &t;0xE800 &t;/* the base address of the mailbox structure on the adapter */
DECL|macro|SIZEOF_MB_DATA_BFR
mdefine_line|#define SIZEOF_MB_DATA_BFR&t;&t;2032&t;/* the size of the actual mailbox data area */
DECL|macro|NUMBER_MB_RESERVED_BYTES
mdefine_line|#define NUMBER_MB_RESERVED_BYTES&t;0x0B&t;/* the number of reserved bytes in the mailbox header area */
DECL|macro|MIN_LGTH_CHDLC_DATA_CFG
mdefine_line|#define MIN_LGTH_CHDLC_DATA_CFG  &t;300 &t;/* min length of the CHDLC data field (for configuration purposes) */
DECL|macro|PRI_MAX_NO_DATA_BYTES_IN_FRAME
mdefine_line|#define PRI_MAX_NO_DATA_BYTES_IN_FRAME  15354 /* PRIMARY - max length of the CHDLC data field */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|opp_flag
id|PACKED
suffix:semicolon
multiline_comment|/* the opp flag */
DECL|member|PACKED
r_int
r_char
id|command
id|PACKED
suffix:semicolon
multiline_comment|/* the user command */
DECL|member|PACKED
r_int
r_int
id|buffer_length
id|PACKED
suffix:semicolon
multiline_comment|/* the data length */
DECL|member|PACKED
r_int
r_char
id|return_code
id|PACKED
suffix:semicolon
multiline_comment|/* the return code */
DECL|member|PACKED
r_int
r_char
id|MB_reserved
(braket
id|NUMBER_MB_RESERVED_BYTES
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|member|PACKED
r_int
r_char
id|data
(braket
id|SIZEOF_MB_DATA_BFR
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* the data area */
DECL|typedef|CHDLC_MAILBOX_STRUCT
)brace
id|CHDLC_MAILBOX_STRUCT
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|PACKED
id|pid_t
id|pid_num
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|CHDLC_MAILBOX_STRUCT
id|cmdarea
id|PACKED
suffix:semicolon
DECL|typedef|CMDBLOCK_STRUCT
)brace
id|CMDBLOCK_STRUCT
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------------&n; *                        Interface commands&n; * --------------------------------------------------------------------------*/
multiline_comment|/* global interface commands */
DECL|macro|READ_GLOBAL_EXCEPTION_CONDITION
mdefine_line|#define READ_GLOBAL_EXCEPTION_CONDITION&t;0x01
DECL|macro|SET_GLOBAL_CONFIGURATION
mdefine_line|#define SET_GLOBAL_CONFIGURATION&t;0x02
DECL|macro|READ_GLOBAL_CONFIGURATION
mdefine_line|#define READ_GLOBAL_CONFIGURATION&t;0x03
DECL|macro|READ_GLOBAL_STATISTICS
mdefine_line|#define READ_GLOBAL_STATISTICS&t;&t;0x04
DECL|macro|FLUSH_GLOBAL_STATISTICS
mdefine_line|#define FLUSH_GLOBAL_STATISTICS&t;&t;0x05
DECL|macro|SET_MODEM_STATUS
mdefine_line|#define SET_MODEM_STATUS&t;&t;0x06&t;/* set status of DTR or RTS */
DECL|macro|READ_MODEM_STATUS
mdefine_line|#define READ_MODEM_STATUS&t;&t;0x07&t;/* read status of CTS and DCD */
DECL|macro|READ_COMMS_ERROR_STATS
mdefine_line|#define READ_COMMS_ERROR_STATS&t;&t;0x08&t;
DECL|macro|FLUSH_COMMS_ERROR_STATS
mdefine_line|#define FLUSH_COMMS_ERROR_STATS&t;&t;0x09
DECL|macro|SET_TRACE_CONFIGURATION
mdefine_line|#define SET_TRACE_CONFIGURATION&t;&t;0x0A&t;/* set the line trace config */
DECL|macro|READ_TRACE_CONFIGURATION
mdefine_line|#define READ_TRACE_CONFIGURATION&t;0x0B&t;/* read the line trace config */
DECL|macro|READ_TRACE_STATISTICS
mdefine_line|#define READ_TRACE_STATISTICS&t;&t;0x0C&t;/* read the trace statistics */
DECL|macro|FLUSH_TRACE_STATISTICS
mdefine_line|#define FLUSH_TRACE_STATISTICS&t;&t;0x0D&t;/* flush the trace statistics */
DECL|macro|FT1_MONITOR_STATUS_CTRL
mdefine_line|#define FT1_MONITOR_STATUS_CTRL&t;&t;0x1C&t;/* set the status of the S508/FT1 monitoring */
DECL|macro|SET_FT1_CONFIGURATION
mdefine_line|#define SET_FT1_CONFIGURATION&t;&t;0x18&t;/* set the FT1 configuration */
DECL|macro|READ_FT1_CONFIGURATION
mdefine_line|#define READ_FT1_CONFIGURATION&t;&t;0x19&t;/* read the FT1 configuration */
DECL|macro|TRANSMIT_ASYNC_DATA_TO_FT1
mdefine_line|#define TRANSMIT_ASYNC_DATA_TO_FT1&t;0x1A&t;/* output asynchronous data to the FT1 */
DECL|macro|RECEIVE_ASYNC_DATA_FROM_FT1
mdefine_line|#define RECEIVE_ASYNC_DATA_FROM_FT1&t;0x1B&t;/* receive asynchronous data from the FT1 */
DECL|macro|FT1_MONITOR_STATUS_CTRL
mdefine_line|#define FT1_MONITOR_STATUS_CTRL&t;&t;0x1C&t;/* set the status of the FT1 monitoring */
DECL|macro|READ_FT1_OPERATIONAL_STATS
mdefine_line|#define READ_FT1_OPERATIONAL_STATS&t;0x1D&t;/* read the S508/FT1 operational statistics */
DECL|macro|SET_FT1_MODE
mdefine_line|#define SET_FT1_MODE&t;&t;&t;0x1E&t;/* set the operational mode of the S508/FT1 module */
multiline_comment|/* CHDLC-level interface commands */
DECL|macro|READ_CHDLC_CODE_VERSION
mdefine_line|#define READ_CHDLC_CODE_VERSION&t;&t;0x20&t;
DECL|macro|READ_CHDLC_EXCEPTION_CONDITION
mdefine_line|#define READ_CHDLC_EXCEPTION_CONDITION&t;0x21&t;/* read exception condition from the adapter */
DECL|macro|SET_CHDLC_CONFIGURATION
mdefine_line|#define SET_CHDLC_CONFIGURATION&t;&t;0x22
DECL|macro|READ_CHDLC_CONFIGURATION
mdefine_line|#define READ_CHDLC_CONFIGURATION&t;0x23
DECL|macro|ENABLE_CHDLC_COMMUNICATIONS
mdefine_line|#define ENABLE_CHDLC_COMMUNICATIONS&t;0x24
DECL|macro|DISABLE_CHDLC_COMMUNICATIONS
mdefine_line|#define DISABLE_CHDLC_COMMUNICATIONS&t;0x25
DECL|macro|READ_CHDLC_LINK_STATUS
mdefine_line|#define READ_CHDLC_LINK_STATUS&t;&t;0x26
DECL|macro|READ_CHDLC_OPERATIONAL_STATS
mdefine_line|#define READ_CHDLC_OPERATIONAL_STATS&t;0x27
DECL|macro|FLUSH_CHDLC_OPERATIONAL_STATS
mdefine_line|#define FLUSH_CHDLC_OPERATIONAL_STATS&t;0x28
DECL|macro|SET_CHDLC_INTERRUPT_TRIGGERS
mdefine_line|#define SET_CHDLC_INTERRUPT_TRIGGERS&t;0x30&t;/* set application interrupt triggers */
DECL|macro|READ_CHDLC_INTERRUPT_TRIGGERS
mdefine_line|#define READ_CHDLC_INTERRUPT_TRIGGERS&t;0x31&t;/* read application interrupt trigger configuration */
multiline_comment|/* Special UDP drivers management commands */
DECL|macro|CPIPE_ENABLE_TRACING
mdefine_line|#define CPIPE_ENABLE_TRACING&t;&t;&t;&t;0x50
DECL|macro|CPIPE_DISABLE_TRACING
mdefine_line|#define CPIPE_DISABLE_TRACING&t;&t;&t;&t;0x51
DECL|macro|CPIPE_GET_TRACE_INFO
mdefine_line|#define CPIPE_GET_TRACE_INFO&t;&t;&t;&t;0x52
DECL|macro|CPIPE_GET_IBA_DATA
mdefine_line|#define CPIPE_GET_IBA_DATA&t;&t;&t;&t;0x53
DECL|macro|CPIPE_FT1_READ_STATUS
mdefine_line|#define CPIPE_FT1_READ_STATUS&t;&t;&t;&t;0x54
DECL|macro|CPIPE_DRIVER_STAT_IFSEND
mdefine_line|#define CPIPE_DRIVER_STAT_IFSEND&t;&t;&t;0x55
DECL|macro|CPIPE_DRIVER_STAT_INTR
mdefine_line|#define CPIPE_DRIVER_STAT_INTR&t;&t;&t;&t;0x56
DECL|macro|CPIPE_DRIVER_STAT_GEN
mdefine_line|#define CPIPE_DRIVER_STAT_GEN&t;&t;&t;&t;0x57
DECL|macro|CPIPE_FLUSH_DRIVER_STATS
mdefine_line|#define CPIPE_FLUSH_DRIVER_STATS&t;&t;&t;0x58
DECL|macro|CPIPE_ROUTER_UP_TIME
mdefine_line|#define CPIPE_ROUTER_UP_TIME&t;&t;&t;&t;0x59
multiline_comment|/* Driver specific commands for API */
DECL|macro|CHDLC_READ_TRACE_DATA
mdefine_line|#define&t;CHDLC_READ_TRACE_DATA&t;&t;0xE4&t;/* read trace data */
DECL|macro|TRACE_ALL
mdefine_line|#define TRACE_ALL                       0x00
DECL|macro|TRACE_PROT
mdefine_line|#define TRACE_PROT&t;&t;&t;0x01
DECL|macro|TRACE_DATA
mdefine_line|#define TRACE_DATA&t;&t;&t;0x02
multiline_comment|/* ----------------------------------------------------------------------------&n; *                     Return codes from interface commands&n; * --------------------------------------------------------------------------*/
DECL|macro|COMMAND_OK
mdefine_line|#define COMMAND_OK&t;&t;&t;&t;0x00
multiline_comment|/* return codes from global interface commands */
DECL|macro|NO_GLOBAL_EXCEP_COND_TO_REPORT
mdefine_line|#define NO_GLOBAL_EXCEP_COND_TO_REPORT&t;&t;0x01&t;/* there is no CHDLC exception condition to report */
DECL|macro|LGTH_GLOBAL_CFG_DATA_INVALID
mdefine_line|#define LGTH_GLOBAL_CFG_DATA_INVALID&t;&t;0x01&t;/* the length of the passed global configuration data is invalid */
DECL|macro|LGTH_TRACE_CFG_DATA_INVALID
mdefine_line|#define LGTH_TRACE_CFG_DATA_INVALID&t;&t;0x01&t;/* the length of the passed trace configuration data is invalid */
DECL|macro|IRQ_TIMEOUT_VALUE_INVALID
mdefine_line|#define IRQ_TIMEOUT_VALUE_INVALID&t;&t;0x02&t;/* an invalid application IRQ timeout value was selected */
DECL|macro|TRACE_CONFIG_INVALID
mdefine_line|#define TRACE_CONFIG_INVALID&t;&t;&t;0x02&t;/* the passed line trace configuration is invalid */
DECL|macro|ADAPTER_OPERATING_FREQ_INVALID
mdefine_line|#define ADAPTER_OPERATING_FREQ_INVALID&t;&t;0x03&t;/* an invalid adapter operating frequency was selected */
DECL|macro|TRC_DEAC_TMR_INVALID
mdefine_line|#define TRC_DEAC_TMR_INVALID&t;&t;&t;0x03&t;/* the trace deactivation timer is invalid */
DECL|macro|S508_FT1_ADPTR_NOT_PRESENT
mdefine_line|#define S508_FT1_ADPTR_NOT_PRESENT&t;&t;0x0C&t;/* the S508/FT1 adapter is not present */
DECL|macro|INVALID_FT1_STATUS_SELECTION
mdefine_line|#define INVALID_FT1_STATUS_SELECTION            0x0D    /* the S508/FT1 status selection is invalid */
DECL|macro|FT1_OP_STATS_NOT_ENABLED
mdefine_line|#define FT1_OP_STATS_NOT_ENABLED&t;&t;0x0D    /* the FT1 operational statistics have not been enabled */
DECL|macro|FT1_OP_STATS_NOT_AVAILABLE
mdefine_line|#define FT1_OP_STATS_NOT_AVAILABLE&t;&t;0x0E    /* the FT1 operational statistics are not currently available */
DECL|macro|S508_FT1_MODE_SELECTION_BUSY
mdefine_line|#define S508_FT1_MODE_SELECTION_BUSY&t;&t;0x0E&t;/* the S508/FT1 adapter is busy selecting the operational mode */
multiline_comment|/* return codes from command READ_GLOBAL_EXCEPTION_CONDITION */
DECL|macro|EXCEP_MODEM_STATUS_CHANGE
mdefine_line|#define EXCEP_MODEM_STATUS_CHANGE&t;&t;0x10&t;&t;/* a modem status change occurred */
DECL|macro|EXCEP_TRC_DISABLED
mdefine_line|#define EXCEP_TRC_DISABLED&t;&t;&t;0x11&t;&t;/* the trace has been disabled */
DECL|macro|EXCEP_IRQ_TIMEOUT
mdefine_line|#define EXCEP_IRQ_TIMEOUT&t;&t;&t;0x12&t;&t;/* IRQ timeout */
multiline_comment|/* return codes from CHDLC-level interface commands */
DECL|macro|NO_CHDLC_EXCEP_COND_TO_REPORT
mdefine_line|#define NO_CHDLC_EXCEP_COND_TO_REPORT&t;&t;0x21&t;/* there is no CHDLC exception condition to report */
DECL|macro|CHDLC_COMMS_DISABLED
mdefine_line|#define CHDLC_COMMS_DISABLED&t;&t;&t;0x21&t;/* communications are not currently enabled */
DECL|macro|CHDLC_COMMS_ENABLED
mdefine_line|#define CHDLC_COMMS_ENABLED&t;&t;&t;0x21&t;/* communications are currently enabled */
DECL|macro|DISABLE_CHDLC_COMMS_BEFORE_CFG
mdefine_line|#define DISABLE_CHDLC_COMMS_BEFORE_CFG&t;&t;0x21&t;/* CHDLC communications must be disabled before setting the configuration */
DECL|macro|ENABLE_CHDLC_COMMS_BEFORE_CONN
mdefine_line|#define ENABLE_CHDLC_COMMS_BEFORE_CONN&t;&t;0x21&t;/* communications must be enabled before using the CHDLC_CONNECT conmmand */
DECL|macro|CHDLC_CFG_BEFORE_COMMS_ENABLED
mdefine_line|#define CHDLC_CFG_BEFORE_COMMS_ENABLED&t;&t;0x22&t;/* perform a SET_CHDLC_CONFIGURATION before enabling comms */
DECL|macro|LGTH_CHDLC_CFG_DATA_INVALID
mdefine_line|#define LGTH_CHDLC_CFG_DATA_INVALID &t;&t;0x22&t;/* the length of the passed CHDLC configuration data is invalid */
DECL|macro|LGTH_INT_TRIGGERS_DATA_INVALID
mdefine_line|#define LGTH_INT_TRIGGERS_DATA_INVALID&t;&t;0x22&t;/* the length of the passed interrupt trigger data is invalid */
DECL|macro|INVALID_IRQ_SELECTED
mdefine_line|#define INVALID_IRQ_SELECTED&t;&t;&t;0x23&t;/* in invalid IRQ was selected in the SET_CHDLC_INTERRUPT_TRIGGERS */
DECL|macro|INVALID_CHDLC_CFG_DATA
mdefine_line|#define INVALID_CHDLC_CFG_DATA&t;&t;&t;0x23&t;/* the passed CHDLC configuration data is invalid */
DECL|macro|IRQ_TMR_VALUE_INVALID
mdefine_line|#define IRQ_TMR_VALUE_INVALID&t;&t;&t;0x24&t;/* an invalid application IRQ timer value was selected */
DECL|macro|LARGER_PERCENT_TX_BFR_REQUIRED
mdefine_line|#define LARGER_PERCENT_TX_BFR_REQUIRED&t;&t;0x24&t;/* a larger Tx buffer percentage is required */
DECL|macro|LARGER_PERCENT_RX_BFR_REQUIRED
mdefine_line|#define LARGER_PERCENT_RX_BFR_REQUIRED&t;&t;0x25&t;/* a larger Rx buffer percentage is required */
DECL|macro|S514_BOTH_PORTS_SAME_CLK_MODE
mdefine_line|#define S514_BOTH_PORTS_SAME_CLK_MODE&t;&t;0x26&t;/* S514 - both ports must have same clock mode */
DECL|macro|INVALID_CMND_HDLC_STREAM_MODE
mdefine_line|#define INVALID_CMND_HDLC_STREAM_MODE           0x4E    /* the CHDLC interface command is invalid for HDLC streaming mode */
DECL|macro|INVALID_CHDLC_COMMAND
mdefine_line|#define INVALID_CHDLC_COMMAND&t;&t;&t;0x4F&t;/* the defined CHDLC interface command is invalid */
multiline_comment|/* return codes from command READ_CHDLC_EXCEPTION_CONDITION */
DECL|macro|EXCEP_LINK_ACTIVE
mdefine_line|#define EXCEP_LINK_ACTIVE&t;&t;&t;0x30&t;/* the CHDLC link has become active */
DECL|macro|EXCEP_LINK_INACTIVE_MODEM
mdefine_line|#define EXCEP_LINK_INACTIVE_MODEM&t;&t;0x31&t;/* the CHDLC link has become inactive (modem status) */
DECL|macro|EXCEP_LINK_INACTIVE_KPALV
mdefine_line|#define EXCEP_LINK_INACTIVE_KPALV&t;&t;0x32&t;/* the CHDLC link has become inactive (keepalive status) */
DECL|macro|EXCEP_IP_ADDRESS_DISCOVERED
mdefine_line|#define EXCEP_IP_ADDRESS_DISCOVERED&t;&t;0x33&t;/* the IP address has been discovered */
DECL|macro|EXCEP_LOOPBACK_CONDITION
mdefine_line|#define EXCEP_LOOPBACK_CONDITION&t;&t;0x34&t;/* a loopback condition has occurred */
multiline_comment|/* return code from command CHDLC_SEND_WAIT and CHDLC_SEND_NO_WAIT */
DECL|macro|LINK_DISCONNECTED
mdefine_line|#define LINK_DISCONNECTED&t;&t;&t;0x21
DECL|macro|NO_TX_BFRS_AVAIL
mdefine_line|#define NO_TX_BFRS_AVAIL&t;&t;&t;0x24
multiline_comment|/* ----------------------------------------------------------------------------&n; * Constants for the SET_GLOBAL_CONFIGURATION/READ_GLOBAL_CONFIGURATION commands&n; * --------------------------------------------------------------------------*/
multiline_comment|/* the global configuration structure */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_int
id|adapter_config_options
id|PACKED
suffix:semicolon
multiline_comment|/* adapter config options */
DECL|member|PACKED
r_int
r_int
id|app_IRQ_timeout
id|PACKED
suffix:semicolon
multiline_comment|/* application IRQ timeout */
DECL|member|PACKED
r_int
r_int
id|adapter_operating_frequency
id|PACKED
suffix:semicolon
multiline_comment|/* adapter operating frequency */
DECL|typedef|GLOBAL_CONFIGURATION_STRUCT
)brace
id|GLOBAL_CONFIGURATION_STRUCT
suffix:semicolon
multiline_comment|/* settings for the &squot;app_IRQ_timeout&squot; */
DECL|macro|MAX_APP_IRQ_TIMEOUT_VALUE
mdefine_line|#define MAX_APP_IRQ_TIMEOUT_VALUE&t;5000&t;/* the maximum permitted IRQ timeout */
multiline_comment|/* ----------------------------------------------------------------------------&n; *             Constants for the READ_GLOBAL_STATISTICS command&n; * --------------------------------------------------------------------------*/
multiline_comment|/* the global statistics structure */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_int
id|app_IRQ_timeout_count
id|PACKED
suffix:semicolon
DECL|typedef|GLOBAL_STATS_STRUCT
)brace
id|GLOBAL_STATS_STRUCT
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------------&n; *             Constants for the READ_COMMS_ERROR_STATS command&n; * --------------------------------------------------------------------------*/
multiline_comment|/* the communications error statistics structure */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_int
id|Rx_overrun_err_count
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|CRC_err_count
id|PACKED
suffix:semicolon
multiline_comment|/* receiver CRC error count */
DECL|member|PACKED
r_int
r_int
id|Rx_abort_count
id|PACKED
suffix:semicolon
multiline_comment|/* abort frames recvd count */
DECL|member|PACKED
r_int
r_int
id|Rx_dis_pri_bfrs_full_count
id|PACKED
suffix:semicolon
multiline_comment|/* receiver disabled */
DECL|member|PACKED
r_int
r_int
id|comms_err_stat_reserved_1
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|member|PACKED
r_int
r_int
id|sec_Tx_abort_msd_Tx_int_count
id|PACKED
suffix:semicolon
multiline_comment|/* secondary - abort frames transmitted count (missed Tx interrupt) */
DECL|member|PACKED
r_int
r_int
id|missed_Tx_und_int_count
id|PACKED
suffix:semicolon
multiline_comment|/* missed tx underrun interrupt count */
DECL|member|PACKED
r_int
r_int
id|sec_Tx_abort_count
id|PACKED
suffix:semicolon
multiline_comment|/*secondary-abort frames tx count */
DECL|member|PACKED
r_int
r_int
id|DCD_state_change_count
id|PACKED
suffix:semicolon
multiline_comment|/* DCD state change */
DECL|member|PACKED
r_int
r_int
id|CTS_state_change_count
id|PACKED
suffix:semicolon
multiline_comment|/* CTS state change */
DECL|typedef|COMMS_ERROR_STATS_STRUCT
)brace
id|COMMS_ERROR_STATS_STRUCT
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------------&n; *                  Constants used for line tracing&n; * --------------------------------------------------------------------------*/
multiline_comment|/* the trace configuration structure (SET_TRACE_CONFIGURATION/READ_TRACE_CONFIGURATION commands) */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|trace_config
id|PACKED
suffix:semicolon
multiline_comment|/* trace configuration */
DECL|member|PACKED
r_int
r_int
id|trace_deactivation_timer
id|PACKED
suffix:semicolon
multiline_comment|/* trace deactivation timer */
DECL|member|PACKED
r_int
r_int
id|ptr_trace_stat_el_cfg_struct
id|PACKED
suffix:semicolon
multiline_comment|/* a pointer to the line trace element configuration structure */
DECL|typedef|LINE_TRACE_CONFIG_STRUCT
)brace
id|LINE_TRACE_CONFIG_STRUCT
suffix:semicolon
multiline_comment|/* &squot;trace_config&squot; bit settings */
DECL|macro|TRACE_INACTIVE
mdefine_line|#define TRACE_INACTIVE&t;&t;0x00&t;/* trace is inactive */
DECL|macro|TRACE_ACTIVE
mdefine_line|#define TRACE_ACTIVE&t;&t;0x01&t;/* trace is active */
DECL|macro|TRACE_DELAY_MODE
mdefine_line|#define TRACE_DELAY_MODE&t;0x04&t;/* operate the trace in delay mode */
DECL|macro|TRACE_DATA_FRAMES
mdefine_line|#define TRACE_DATA_FRAMES&t;0x08&t;/* trace Data frames */
DECL|macro|TRACE_SLARP_FRAMES
mdefine_line|#define TRACE_SLARP_FRAMES&t;0x10&t;/* trace SLARP frames */
DECL|macro|TRACE_CDP_FRAMES
mdefine_line|#define TRACE_CDP_FRAMES&t;0x20&t;/* trace CDP frames */
multiline_comment|/* the line trace status element configuration structure */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_int
id|number_trace_status_elements
id|PACKED
suffix:semicolon
multiline_comment|/* number of line trace elements */
DECL|member|PACKED
r_int
r_int
id|base_addr_trace_status_elements
id|PACKED
suffix:semicolon
multiline_comment|/* base address of the trace element list */
DECL|member|PACKED
r_int
r_int
id|next_trace_element_to_use
id|PACKED
suffix:semicolon
multiline_comment|/* pointer to the next trace element to be used */
DECL|member|PACKED
r_int
r_int
id|base_addr_trace_buffer
id|PACKED
suffix:semicolon
multiline_comment|/* base address of the trace data buffer */
DECL|member|PACKED
r_int
r_int
id|end_addr_trace_buffer
id|PACKED
suffix:semicolon
multiline_comment|/* end address of the trace data buffer */
DECL|typedef|TRACE_STATUS_EL_CFG_STRUCT
)brace
id|TRACE_STATUS_EL_CFG_STRUCT
suffix:semicolon
multiline_comment|/* the line trace status element structure */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|opp_flag
id|PACKED
suffix:semicolon
multiline_comment|/* opp flag */
DECL|member|PACKED
r_int
r_int
id|trace_length
id|PACKED
suffix:semicolon
multiline_comment|/* trace length */
DECL|member|PACKED
r_int
r_char
id|trace_type
id|PACKED
suffix:semicolon
multiline_comment|/* trace type */
DECL|member|PACKED
r_int
r_int
id|trace_time_stamp
id|PACKED
suffix:semicolon
multiline_comment|/* time stamp */
DECL|member|PACKED
r_int
r_int
id|trace_reserved_1
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later use */
DECL|member|PACKED
r_int
r_int
id|trace_reserved_2
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later use */
DECL|member|PACKED
r_int
r_int
id|ptr_data_bfr
id|PACKED
suffix:semicolon
multiline_comment|/* ptr to the trace data buffer */
DECL|typedef|TRACE_STATUS_ELEMENT_STRUCT
)brace
id|TRACE_STATUS_ELEMENT_STRUCT
suffix:semicolon
multiline_comment|/* &quot;trace_type&quot; bit settings */
DECL|macro|TRACE_INCOMING
mdefine_line|#define TRACE_INCOMING &t;&t;&t;0x00
DECL|macro|TRACE_OUTGOINGING
mdefine_line|#define TRACE_OUTGOINGING &t;&t;0x01
DECL|macro|TRACE_INCOMING_ABORTED
mdefine_line|#define TRACE_INCOMING_ABORTED &t;&t;0x10
DECL|macro|TRACE_INCOMING_CRC_ERROR
mdefine_line|#define TRACE_INCOMING_CRC_ERROR &t;0x20
DECL|macro|TRACE_INCOMING_OVERRUN_ERROR
mdefine_line|#define TRACE_INCOMING_OVERRUN_ERROR &t;0x40
multiline_comment|/* the line trace statistics structure */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_int
id|frames_traced_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of frames traced */
DECL|member|PACKED
r_int
r_int
id|trc_frms_not_recorded_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of trace frames discarded */
DECL|typedef|LINE_TRACE_STATS_STRUCT
)brace
id|LINE_TRACE_STATS_STRUCT
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------------&n; *               Constants for the FT1_MONITOR_STATUS_CTRL command&n; * --------------------------------------------------------------------------*/
DECL|macro|DISABLE_FT1_STATUS_STATISTICS
mdefine_line|#define DISABLE_FT1_STATUS_STATISTICS&t;0x00    /* disable the FT1 status and statistics monitoring */
DECL|macro|ENABLE_READ_FT1_STATUS
mdefine_line|#define ENABLE_READ_FT1_STATUS&t;&t;0x01    /* read the FT1 operational status */
DECL|macro|ENABLE_READ_FT1_OP_STATS
mdefine_line|#define ENABLE_READ_FT1_OP_STATS&t;0x02    /* read the FT1 operational statistics */
DECL|macro|FLUSH_FT1_OP_STATS
mdefine_line|#define FLUSH_FT1_OP_STATS&t;&t;0x04 &t;/* flush the FT1 operational statistics */
multiline_comment|/* ----------------------------------------------------------------------------&n; *               Constants for the SET_CHDLC_CONFIGURATION command&n; * --------------------------------------------------------------------------*/
multiline_comment|/* the CHDLC configuration structure */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_int
id|baud_rate
id|PACKED
suffix:semicolon
multiline_comment|/* the baud rate */
DECL|member|PACKED
r_int
r_int
id|line_config_options
id|PACKED
suffix:semicolon
multiline_comment|/* line configuration options */
DECL|member|PACKED
r_int
r_int
id|modem_config_options
id|PACKED
suffix:semicolon
multiline_comment|/* modem configration options */
DECL|member|PACKED
r_int
r_int
id|modem_status_timer
id|PACKED
suffix:semicolon
multiline_comment|/* timer for monitoring modem status changes */
DECL|member|PACKED
r_int
r_int
id|CHDLC_API_options
id|PACKED
suffix:semicolon
multiline_comment|/* CHDLC API options */
DECL|member|PACKED
r_int
r_int
id|CHDLC_protocol_options
id|PACKED
suffix:semicolon
multiline_comment|/* CHDLC protocol options */
DECL|member|PACKED
r_int
r_int
id|percent_data_buffer_for_Tx
id|PACKED
suffix:semicolon
multiline_comment|/* percentage data buffering used for Tx */
DECL|member|PACKED
r_int
r_int
id|CHDLC_statistics_options
id|PACKED
suffix:semicolon
multiline_comment|/* CHDLC operational statistics options */
DECL|member|PACKED
r_int
r_int
id|max_CHDLC_data_field_length
id|PACKED
suffix:semicolon
multiline_comment|/* the maximum length of the CHDLC Data field */
DECL|member|PACKED
r_int
r_int
id|transmit_keepalive_timer
id|PACKED
suffix:semicolon
multiline_comment|/* the transmit keepalive timer */
DECL|member|PACKED
r_int
r_int
id|receive_keepalive_timer
id|PACKED
suffix:semicolon
multiline_comment|/* the receive keepalive timer */
DECL|member|PACKED
r_int
r_int
id|keepalive_error_tolerance
id|PACKED
suffix:semicolon
multiline_comment|/* the receive keepalive error tolerance */
DECL|member|PACKED
r_int
r_int
id|SLARP_request_timer
id|PACKED
suffix:semicolon
multiline_comment|/* the SLARP request timer */
DECL|member|PACKED
r_int
r_int
id|IP_address
id|PACKED
suffix:semicolon
multiline_comment|/* the IP address */
DECL|member|PACKED
r_int
r_int
id|IP_netmask
id|PACKED
suffix:semicolon
multiline_comment|/* the IP netmask */
DECL|member|PACKED
r_int
r_int
id|ptr_shared_mem_info_struct
id|PACKED
suffix:semicolon
multiline_comment|/* a pointer to the shared memory area information structure */
DECL|member|PACKED
r_int
r_int
id|ptr_CHDLC_Tx_stat_el_cfg_struct
id|PACKED
suffix:semicolon
multiline_comment|/* a pointer to the transmit status element configuration structure */
DECL|member|PACKED
r_int
r_int
id|ptr_CHDLC_Rx_stat_el_cfg_struct
id|PACKED
suffix:semicolon
multiline_comment|/* a pointer to the receive status element configuration structure */
DECL|typedef|CHDLC_CONFIGURATION_STRUCT
)brace
id|CHDLC_CONFIGURATION_STRUCT
suffix:semicolon
multiline_comment|/* settings for the &squot;line_config_options&squot; */
DECL|macro|INTERFACE_LEVEL_V35
mdefine_line|#define INTERFACE_LEVEL_V35&t;&t;&t;&t;&t;0x0000 /* V.35 interface level */
DECL|macro|INTERFACE_LEVEL_RS232
mdefine_line|#define INTERFACE_LEVEL_RS232&t;&t;&t;&t;&t;0x0001 /* RS-232 interface level */
multiline_comment|/* settings for the &squot;modem_config_options&squot; */
DECL|macro|DONT_RAISE_DTR_RTS_ON_EN_COMMS
mdefine_line|#define DONT_RAISE_DTR_RTS_ON_EN_COMMS&t;&t;0x0001
multiline_comment|/* don&squot;t automatically raise DTR and RTS when performing an&n;   ENABLE_CHDLC_COMMUNICATIONS command */
DECL|macro|DONT_REPORT_CHG_IN_MODEM_STAT
mdefine_line|#define DONT_REPORT_CHG_IN_MODEM_STAT &t;&t;0x0002
multiline_comment|/* don&squot;t report changes in modem status to the application */
multiline_comment|/* bit settings for the &squot;CHDLC_protocol_options&squot; byte */
DECL|macro|IGNORE_DCD_FOR_LINK_STAT
mdefine_line|#define IGNORE_DCD_FOR_LINK_STAT&t;&t;0x0001
multiline_comment|/* ignore DCD in determining the CHDLC link status */
DECL|macro|IGNORE_CTS_FOR_LINK_STAT
mdefine_line|#define IGNORE_CTS_FOR_LINK_STAT&t;&t;0x0002
multiline_comment|/* ignore CTS in determining the CHDLC link status */
DECL|macro|IGNORE_KPALV_FOR_LINK_STAT
mdefine_line|#define IGNORE_KPALV_FOR_LINK_STAT&t;&t;0x0004
multiline_comment|/* ignore keepalive frames in determining the CHDLC link status */
DECL|macro|HDLC_STREAMING_MODE
mdefine_line|#define HDLC_STREAMING_MODE&t;&t;&t;0x8000
multiline_comment|/*   settings for the &squot;CHDLC_statistics_options&squot; */
DECL|macro|CHDLC_TX_DATA_BYTE_COUNT_STAT
mdefine_line|#define CHDLC_TX_DATA_BYTE_COUNT_STAT&t;&t;0x0001
multiline_comment|/* record the number of Data bytes transmitted */
DECL|macro|CHDLC_RX_DATA_BYTE_COUNT_STAT
mdefine_line|#define CHDLC_RX_DATA_BYTE_COUNT_STAT&t;&t;0x0002
multiline_comment|/* record the number of Data bytes received */
DECL|macro|CHDLC_TX_THROUGHPUT_STAT
mdefine_line|#define CHDLC_TX_THROUGHPUT_STAT&t;&t;0x0004
multiline_comment|/* compute the Data frame transmit throughput */
DECL|macro|CHDLC_RX_THROUGHPUT_STAT
mdefine_line|#define CHDLC_RX_THROUGHPUT_STAT&t;&t;0x0008
multiline_comment|/* compute the Data frame receive throughput */
multiline_comment|/* permitted minimum and maximum values for setting the CHDLC configuration */
DECL|macro|PRI_MAX_BAUD_RATE_S508
mdefine_line|#define PRI_MAX_BAUD_RATE_S508&t;2666666 /* PRIMARY   - maximum baud rate (S508) */
DECL|macro|SEC_MAX_BAUD_RATE_S508
mdefine_line|#define SEC_MAX_BAUD_RATE_S508&t;258064 &t;/* SECONDARY - maximum baud rate (S508) */
DECL|macro|PRI_MAX_BAUD_RATE_S514
mdefine_line|#define PRI_MAX_BAUD_RATE_S514  2750000 /* PRIMARY   - maximum baud rate (S508) */
DECL|macro|SEC_MAX_BAUD_RATE_S514
mdefine_line|#define SEC_MAX_BAUD_RATE_S514  515625  /* SECONDARY - maximum baud rate (S508) */
DECL|macro|MIN_MODEM_TIMER
mdefine_line|#define MIN_MODEM_TIMER&t;0&t;&t;&t;/* minimum modem status timer */
DECL|macro|MAX_MODEM_TIMER
mdefine_line|#define MAX_MODEM_TIMER&t;5000&t;&t;&t;/* maximum modem status timer */
DECL|macro|SEC_MAX_NO_DATA_BYTES_IN_FRAME
mdefine_line|#define SEC_MAX_NO_DATA_BYTES_IN_FRAME  2048 /* SECONDARY - max length of the CHDLC data field */
DECL|macro|MIN_Tx_KPALV_TIMER
mdefine_line|#define MIN_Tx_KPALV_TIMER&t;0&t;  /* minimum transmit keepalive timer */
DECL|macro|MAX_Tx_KPALV_TIMER
mdefine_line|#define MAX_Tx_KPALV_TIMER&t;60000&t;  /* maximum transmit keepalive timer */
DECL|macro|DEFAULT_Tx_KPALV_TIMER
mdefine_line|#define DEFAULT_Tx_KPALV_TIMER&t;10000&t;  /* default transmit keepalive timer */
DECL|macro|MIN_Rx_KPALV_TIMER
mdefine_line|#define MIN_Rx_KPALV_TIMER&t;10&t;  /* minimum receive keepalive timer */
DECL|macro|MAX_Rx_KPALV_TIMER
mdefine_line|#define MAX_Rx_KPALV_TIMER&t;60000&t;  /* maximum receive keepalive timer */
DECL|macro|DEFAULT_Rx_KPALV_TIMER
mdefine_line|#define DEFAULT_Rx_KPALV_TIMER&t;10000&t;  /* default receive keepalive timer */
DECL|macro|MIN_KPALV_ERR_TOL
mdefine_line|#define MIN_KPALV_ERR_TOL&t;1&t;  /* min kpalv error tolerance count */
DECL|macro|MAX_KPALV_ERR_TOL
mdefine_line|#define MAX_KPALV_ERR_TOL&t;20&t;  /* max kpalv error tolerance count */
DECL|macro|DEFAULT_KPALV_ERR_TOL
mdefine_line|#define DEFAULT_KPALV_ERR_TOL&t;3&t;  /* default value */
DECL|macro|MIN_SLARP_REQ_TIMER
mdefine_line|#define MIN_SLARP_REQ_TIMER&t;0&t;  /* min transmit SLARP Request timer */
DECL|macro|MAX_SLARP_REQ_TIMER
mdefine_line|#define MAX_SLARP_REQ_TIMER&t;60000&t;  /* max transmit SLARP Request timer */
DECL|macro|DEFAULT_SLARP_REQ_TIMER
mdefine_line|#define DEFAULT_SLARP_REQ_TIMER&t;0&t;  /* default value -- no SLARP */
multiline_comment|/* ----------------------------------------------------------------------------&n; *             Constants for the READ_CHDLC_LINK_STATUS command&n; * --------------------------------------------------------------------------*/
multiline_comment|/* the CHDLC status structure */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|CHDLC_link_status
id|PACKED
suffix:semicolon
multiline_comment|/* CHDLC link status */
DECL|member|PACKED
r_int
r_char
id|no_Data_frms_for_app
id|PACKED
suffix:semicolon
multiline_comment|/* number of Data frames available for the application */
DECL|member|PACKED
r_int
r_char
id|receiver_status
id|PACKED
suffix:semicolon
multiline_comment|/* enabled/disabled */
DECL|member|PACKED
r_int
r_char
id|SLARP_state
id|PACKED
suffix:semicolon
multiline_comment|/* internal SLARP state */
DECL|typedef|CHDLC_LINK_STATUS_STRUCT
)brace
id|CHDLC_LINK_STATUS_STRUCT
suffix:semicolon
multiline_comment|/* settings for the &squot;CHDLC_link_status&squot; variable */
DECL|macro|CHDLC_LINK_INACTIVE
mdefine_line|#define CHDLC_LINK_INACTIVE&t;&t;0x00&t;/* the CHDLC link is inactive */
DECL|macro|CHDLC_LINK_ACTIVE
mdefine_line|#define CHDLC_LINK_ACTIVE&t;&t;0x01&t;/* the CHDLC link is active */
multiline_comment|/* ----------------------------------------------------------------------------&n; *           Constants for the READ_CHDLC_OPERATIONAL_STATS command&n; * --------------------------------------------------------------------------*/
multiline_comment|/* the CHDLC operational statistics structure */
r_typedef
r_struct
(brace
multiline_comment|/* Data frame transmission statistics */
DECL|member|PACKED
r_int
r_int
id|Data_frames_Tx_count
id|PACKED
suffix:semicolon
multiline_comment|/* # of frames transmitted */
DECL|member|PACKED
r_int
r_int
id|Data_bytes_Tx_count
id|PACKED
suffix:semicolon
multiline_comment|/* # of bytes transmitted */
DECL|member|PACKED
r_int
r_int
id|Data_Tx_throughput
id|PACKED
suffix:semicolon
multiline_comment|/* transmit throughput */
DECL|member|PACKED
r_int
r_int
id|no_ms_for_Data_Tx_thruput_comp
id|PACKED
suffix:semicolon
multiline_comment|/* millisecond time used for the Tx throughput computation */
DECL|member|PACKED
r_int
r_int
id|Tx_Data_discard_lgth_err_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of Data frames discarded (length error) */
DECL|member|PACKED
r_int
r_int
id|reserved_Data_frm_Tx_stat1
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|member|PACKED
r_int
r_int
id|reserved_Data_frm_Tx_stat2
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|member|PACKED
r_int
r_int
id|reserved_Data_frm_Tx_stat3
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
multiline_comment|/* Data frame reception statistics */
DECL|member|PACKED
r_int
r_int
id|Data_frames_Rx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of frames received */
DECL|member|PACKED
r_int
r_int
id|Data_bytes_Rx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of bytes received */
DECL|member|PACKED
r_int
r_int
id|Data_Rx_throughput
id|PACKED
suffix:semicolon
multiline_comment|/* receive throughput */
DECL|member|PACKED
r_int
r_int
id|no_ms_for_Data_Rx_thruput_comp
id|PACKED
suffix:semicolon
multiline_comment|/* millisecond time used for the Rx throughput computation */
DECL|member|PACKED
r_int
r_int
id|Rx_Data_discard_short_count
id|PACKED
suffix:semicolon
multiline_comment|/* received Data frames discarded (too short) */
DECL|member|PACKED
r_int
r_int
id|Rx_Data_discard_long_count
id|PACKED
suffix:semicolon
multiline_comment|/* received Data frames discarded (too long) */
DECL|member|PACKED
r_int
r_int
id|Rx_Data_discard_inactive_count
id|PACKED
suffix:semicolon
multiline_comment|/* received Data frames discarded (link inactive) */
DECL|member|PACKED
r_int
r_int
id|reserved_Data_frm_Rx_stat1
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
multiline_comment|/* SLARP frame transmission/reception statistics */
DECL|member|PACKED
r_int
r_int
id|CHDLC_SLARP_REQ_Tx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of SLARP Request frames transmitted */
DECL|member|PACKED
r_int
r_int
id|CHDLC_SLARP_REQ_Rx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of SLARP Request frames received */
DECL|member|PACKED
r_int
r_int
id|CHDLC_SLARP_REPLY_Tx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of SLARP Reply frames transmitted */
DECL|member|PACKED
r_int
r_int
id|CHDLC_SLARP_REPLY_Rx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of SLARP Reply frames received */
DECL|member|PACKED
r_int
r_int
id|CHDLC_SLARP_KPALV_Tx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of SLARP keepalive frames transmitted */
DECL|member|PACKED
r_int
r_int
id|CHDLC_SLARP_KPALV_Rx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of SLARP keepalive frames received */
DECL|member|PACKED
r_int
r_int
id|reserved_SLARP_stat1
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|member|PACKED
r_int
r_int
id|reserved_SLARP_stat2
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
multiline_comment|/* CDP frame transmission/reception statistics */
DECL|member|PACKED
r_int
r_int
id|CHDLC_CDP_Tx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of CDP frames transmitted */
DECL|member|PACKED
r_int
r_int
id|CHDLC_CDP_Rx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of CDP frames received */
DECL|member|PACKED
r_int
r_int
id|reserved_CDP_stat1
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|member|PACKED
r_int
r_int
id|reserved_CDP_stat2
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|member|PACKED
r_int
r_int
id|reserved_CDP_stat3
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|member|PACKED
r_int
r_int
id|reserved_CDP_stat4
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|member|PACKED
r_int
r_int
id|reserved_CDP_stat5
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|member|PACKED
r_int
r_int
id|reserved_CDP_stat6
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
multiline_comment|/* Incomming frames with a format error statistics */
DECL|member|PACKED
r_int
r_int
id|Rx_frm_incomp_CHDLC_hdr_count
id|PACKED
suffix:semicolon
multiline_comment|/* frames received of with incomplete Cisco HDLC header */
DECL|member|PACKED
r_int
r_int
id|Rx_frms_too_long_count
id|PACKED
suffix:semicolon
multiline_comment|/* frames received of excessive length count */
DECL|member|PACKED
r_int
r_int
id|Rx_invalid_CHDLC_addr_count
id|PACKED
suffix:semicolon
multiline_comment|/* frames received with an invalid CHDLC address count */
DECL|member|PACKED
r_int
r_int
id|Rx_invalid_CHDLC_ctrl_count
id|PACKED
suffix:semicolon
multiline_comment|/* frames received with an invalid CHDLC control field count */
DECL|member|PACKED
r_int
r_int
id|Rx_invalid_CHDLC_type_count
id|PACKED
suffix:semicolon
multiline_comment|/* frames received of an invalid CHDLC frame type count */
DECL|member|PACKED
r_int
r_int
id|Rx_SLARP_invalid_code_count
id|PACKED
suffix:semicolon
multiline_comment|/* SLARP frame received with an invalid packet code */
DECL|member|PACKED
r_int
r_int
id|Rx_SLARP_Reply_bad_IP_addr
id|PACKED
suffix:semicolon
multiline_comment|/* SLARP Reply received - bad IP address */
DECL|member|PACKED
r_int
r_int
id|Rx_SLARP_Reply_bad_netmask
id|PACKED
suffix:semicolon
multiline_comment|/* SLARP Reply received - bad netmask */
DECL|member|PACKED
r_int
r_int
id|reserved_frm_format_err1
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|member|PACKED
r_int
r_int
id|reserved_frm_format_err2
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|member|PACKED
r_int
r_int
id|reserved_frm_format_err3
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|member|PACKED
r_int
r_int
id|reserved_frm_format_err4
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
multiline_comment|/* CHDLC timeout/retry statistics */
DECL|member|PACKED
r_int
r_int
id|SLARP_Rx_keepalive_TO_count
id|PACKED
suffix:semicolon
multiline_comment|/* timeout count for incomming SLARP frames */
DECL|member|PACKED
r_int
r_int
id|SLARP_Request_TO_count
id|PACKED
suffix:semicolon
multiline_comment|/* timeout count for SLARP Request frames */
DECL|member|PACKED
r_int
r_int
id|To_retry_reserved_stat1
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|member|PACKED
r_int
r_int
id|To_retry_reserved_stat2
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|member|PACKED
r_int
r_int
id|To_retry_reserved_stat3
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
multiline_comment|/* CHDLC link active/inactive and loopback statistics */
DECL|member|PACKED
r_int
r_int
id|link_active_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of times that the link went active */
DECL|member|PACKED
r_int
r_int
id|link_inactive_modem_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of times that the link went inactive (modem failure) */
DECL|member|PACKED
r_int
r_int
id|link_inactive_keepalive_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of times that the link went inactive (keepalive failure) */
DECL|member|PACKED
r_int
r_int
id|link_looped_count
id|PACKED
suffix:semicolon
multiline_comment|/* link looped count */
DECL|member|PACKED
r_int
r_int
id|link_status_reserved_stat1
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later use */
DECL|member|PACKED
r_int
r_int
id|link_status_reserved_stat2
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later use */
multiline_comment|/* miscellaneous statistics */
DECL|member|PACKED
r_int
r_int
id|reserved_misc_stat1
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|member|PACKED
r_int
r_int
id|reserved_misc_stat2
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|member|PACKED
r_int
r_int
id|reserved_misc_stat3
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|member|PACKED
r_int
r_int
id|reserved_misc_stat4
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|typedef|CHDLC_OPERATIONAL_STATS_STRUCT
)brace
id|CHDLC_OPERATIONAL_STATS_STRUCT
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------------&n; *                 Constants for using application interrupts&n; * --------------------------------------------------------------------------*/
multiline_comment|/* the structure used for the SET_CHDLC_INTERRUPT_TRIGGERS/READ_CHDLC_INTERRUPT_TRIGGERS command */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|CHDLC_interrupt_triggers
id|PACKED
suffix:semicolon
multiline_comment|/* CHDLC interrupt trigger configuration */
DECL|member|PACKED
r_int
r_char
id|IRQ
id|PACKED
suffix:semicolon
multiline_comment|/* IRQ to be used */
DECL|member|PACKED
r_int
r_int
id|interrupt_timer
id|PACKED
suffix:semicolon
multiline_comment|/* interrupt timer */
DECL|member|PACKED
r_int
r_int
id|misc_interrupt_bits
id|PACKED
suffix:semicolon
multiline_comment|/* miscellaneous bits */
DECL|typedef|CHDLC_INT_TRIGGERS_STRUCT
)brace
id|CHDLC_INT_TRIGGERS_STRUCT
suffix:semicolon
multiline_comment|/* &squot;CHDLC_interrupt_triggers&squot; bit settings */
DECL|macro|APP_INT_ON_RX_FRAME
mdefine_line|#define APP_INT_ON_RX_FRAME&t;&t;0x01&t;/* interrupt on Data frame reception */
DECL|macro|APP_INT_ON_TX_FRAME
mdefine_line|#define APP_INT_ON_TX_FRAME&t;&t;0x02&t;/* interrupt when an Data frame may be transmitted */
DECL|macro|APP_INT_ON_COMMAND_COMPLETE
mdefine_line|#define APP_INT_ON_COMMAND_COMPLETE&t;0x04&t;/* interrupt when an interface command is complete */
DECL|macro|APP_INT_ON_TIMER
mdefine_line|#define APP_INT_ON_TIMER&t;&t;0x08&t;/* interrupt on a defined millisecond timeout */
DECL|macro|APP_INT_ON_GLOBAL_EXCEP_COND
mdefine_line|#define APP_INT_ON_GLOBAL_EXCEP_COND &t;0x10&t;/* interrupt on a global exception condition */
DECL|macro|APP_INT_ON_CHDLC_EXCEP_COND
mdefine_line|#define APP_INT_ON_CHDLC_EXCEP_COND&t;0x20&t;/* interrupt on an CHDLC exception condition */
DECL|macro|APP_INT_ON_TRACE_DATA_AVAIL
mdefine_line|#define APP_INT_ON_TRACE_DATA_AVAIL&t;0x80&t;/* interrupt when trace data is available */
multiline_comment|/* interrupt types indicated at &squot;interrupt_type&squot; byte of the INTERRUPT_INFORMATION_STRUCT */
DECL|macro|NO_APP_INTS_PEND
mdefine_line|#define NO_APP_INTS_PEND&t;&t;0x00&t;/* no interrups are pending */
DECL|macro|RX_APP_INT_PEND
mdefine_line|#define RX_APP_INT_PEND&t;&t;&t;0x01&t;/* a receive interrupt is pending */
DECL|macro|TX_APP_INT_PEND
mdefine_line|#define TX_APP_INT_PEND&t;&t;&t;0x02&t;/* a transmit interrupt is pending */
DECL|macro|COMMAND_COMPLETE_APP_INT_PEND
mdefine_line|#define COMMAND_COMPLETE_APP_INT_PEND&t;0x04&t;/* a &squot;command complete&squot; interrupt is pending */
DECL|macro|TIMER_APP_INT_PEND
mdefine_line|#define TIMER_APP_INT_PEND&t;&t;0x08&t;/* a timer interrupt is pending */
DECL|macro|GLOBAL_EXCEP_COND_APP_INT_PEND
mdefine_line|#define GLOBAL_EXCEP_COND_APP_INT_PEND &t;0x10&t;/* a global exception condition interrupt is pending */
DECL|macro|CHDLC_EXCEP_COND_APP_INT_PEND
mdefine_line|#define CHDLC_EXCEP_COND_APP_INT_PEND &t;0x20&t;/* an CHDLC exception condition interrupt is pending */
DECL|macro|TRACE_DATA_AVAIL_APP_INT_PEND
mdefine_line|#define TRACE_DATA_AVAIL_APP_INT_PEND&t;0x80&t;/* a trace data available interrupt is pending */
multiline_comment|/* modem status changes */
DECL|macro|DCD_HIGH
mdefine_line|#define DCD_HIGH&t;&t;&t;0x08
DECL|macro|CTS_HIGH
mdefine_line|#define CTS_HIGH&t;&t;&t;0x20
multiline_comment|/* ----------------------------------------------------------------------------&n; *                   Constants for Data frame transmission&n; * --------------------------------------------------------------------------*/
multiline_comment|/* the Data frame transmit status element configuration structure */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_int
id|number_Tx_status_elements
id|PACKED
suffix:semicolon
multiline_comment|/* number of transmit status elements */
DECL|member|PACKED
r_int
r_int
id|base_addr_Tx_status_elements
id|PACKED
suffix:semicolon
multiline_comment|/* base address of the transmit element list */
DECL|member|PACKED
r_int
r_int
id|next_Tx_status_element_to_use
id|PACKED
suffix:semicolon
multiline_comment|/* pointer to the next transmit element to be used */
DECL|typedef|CHDLC_TX_STATUS_EL_CFG_STRUCT
)brace
id|CHDLC_TX_STATUS_EL_CFG_STRUCT
suffix:semicolon
multiline_comment|/* the Data frame transmit status element structure */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|opp_flag
id|PACKED
suffix:semicolon
multiline_comment|/* opp flag */
DECL|member|PACKED
r_int
r_int
id|frame_length
id|PACKED
suffix:semicolon
multiline_comment|/* length of the frame to be transmitted */
DECL|member|PACKED
r_int
r_char
id|reserved_1
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for internal use */
DECL|member|PACKED
r_int
r_int
id|reserved_2
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for internal use */
DECL|member|PACKED
r_int
r_int
id|reserved_3
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for internal use */
DECL|member|PACKED
r_int
r_int
id|ptr_data_bfr
id|PACKED
suffix:semicolon
multiline_comment|/* pointer to the data area */
DECL|typedef|CHDLC_DATA_TX_STATUS_EL_STRUCT
)brace
id|CHDLC_DATA_TX_STATUS_EL_STRUCT
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------------&n; *                   Constants for Data frame reception&n; * --------------------------------------------------------------------------*/
multiline_comment|/* the Data frame receive status element configuration structure */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_int
id|number_Rx_status_elements
id|PACKED
suffix:semicolon
multiline_comment|/* number of receive status elements */
DECL|member|PACKED
r_int
r_int
id|base_addr_Rx_status_elements
id|PACKED
suffix:semicolon
multiline_comment|/* base address of the receive element list */
DECL|member|PACKED
r_int
r_int
id|next_Rx_status_element_to_use
id|PACKED
suffix:semicolon
multiline_comment|/* pointer to the next receive element to be used */
DECL|member|PACKED
r_int
r_int
id|base_addr_Rx_buffer
id|PACKED
suffix:semicolon
multiline_comment|/* base address of the receive data buffer */
DECL|member|PACKED
r_int
r_int
id|end_addr_Rx_buffer
id|PACKED
suffix:semicolon
multiline_comment|/* end address of the receive data buffer */
DECL|typedef|CHDLC_RX_STATUS_EL_CFG_STRUCT
)brace
id|CHDLC_RX_STATUS_EL_CFG_STRUCT
suffix:semicolon
multiline_comment|/* the Data frame receive status element structure */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|opp_flag
id|PACKED
suffix:semicolon
multiline_comment|/* opp flag */
DECL|member|PACKED
r_int
r_int
id|frame_length
id|PACKED
suffix:semicolon
multiline_comment|/* length of the received frame */
DECL|member|PACKED
r_int
r_char
id|error_flag
id|PACKED
suffix:semicolon
multiline_comment|/* frame errors (HDLC_STREAMING_MODE)*/
DECL|member|PACKED
r_int
r_int
id|time_stamp
id|PACKED
suffix:semicolon
multiline_comment|/* receive time stamp (HDLC_STREAMING_MODE) */
DECL|member|PACKED
r_int
r_int
id|reserved_1
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for internal use */
DECL|member|PACKED
r_int
r_int
id|reserved_2
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for internal use */
DECL|member|PACKED
r_int
r_int
id|ptr_data_bfr
id|PACKED
suffix:semicolon
multiline_comment|/* pointer to the data area */
DECL|typedef|CHDLC_DATA_RX_STATUS_EL_STRUCT
)brace
id|CHDLC_DATA_RX_STATUS_EL_STRUCT
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------------&n; *         Constants defining the shared memory information area&n; * --------------------------------------------------------------------------*/
multiline_comment|/* the global information structure */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|global_status
id|PACKED
suffix:semicolon
multiline_comment|/* global status */
DECL|member|PACKED
r_int
r_char
id|modem_status
id|PACKED
suffix:semicolon
multiline_comment|/* current modem status */
DECL|member|PACKED
r_int
r_char
id|global_excep_conditions
id|PACKED
suffix:semicolon
multiline_comment|/* global exception conditions */
DECL|member|PACKED
r_int
r_char
id|glob_info_reserved
(braket
l_int|5
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|PACKED
r_int
r_char
id|codename
(braket
l_int|4
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* Firmware name */
DECL|member|PACKED
r_int
r_char
id|codeversion
(braket
l_int|4
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* Firmware version */
DECL|typedef|GLOBAL_INFORMATION_STRUCT
)brace
id|GLOBAL_INFORMATION_STRUCT
suffix:semicolon
multiline_comment|/* the CHDLC information structure */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|CHDLC_status
id|PACKED
suffix:semicolon
multiline_comment|/* CHDLC status */
DECL|member|PACKED
r_int
r_char
id|CHDLC_excep_conditions
id|PACKED
suffix:semicolon
multiline_comment|/* CHDLC exception conditions */
DECL|member|PACKED
r_int
r_char
id|CHDLC_info_reserved
(braket
l_int|14
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* reserved */
DECL|typedef|CHDLC_INFORMATION_STRUCT
)brace
id|CHDLC_INFORMATION_STRUCT
suffix:semicolon
multiline_comment|/* the interrupt information structure */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|interrupt_type
id|PACKED
suffix:semicolon
multiline_comment|/* type of interrupt triggered */
DECL|member|PACKED
r_int
r_char
id|interrupt_permission
id|PACKED
suffix:semicolon
multiline_comment|/* interrupt permission mask */
DECL|member|PACKED
r_int
r_char
id|int_info_reserved
(braket
l_int|14
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* reserved */
DECL|typedef|INTERRUPT_INFORMATION_STRUCT
)brace
id|INTERRUPT_INFORMATION_STRUCT
suffix:semicolon
multiline_comment|/* the S508/FT1 information structure */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|parallel_port_A_input
id|PACKED
suffix:semicolon
multiline_comment|/* input - parallel port A */
DECL|member|PACKED
r_int
r_char
id|parallel_port_B_input
id|PACKED
suffix:semicolon
multiline_comment|/* input - parallel port B */
DECL|member|PACKED
r_int
r_char
id|FT1_info_reserved
(braket
l_int|14
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* reserved */
DECL|typedef|FT1_INFORMATION_STRUCT
)brace
id|FT1_INFORMATION_STRUCT
suffix:semicolon
multiline_comment|/* the shared memory area information structure */
r_typedef
r_struct
(brace
DECL|member|PACKED
id|GLOBAL_INFORMATION_STRUCT
id|global_info_struct
id|PACKED
suffix:semicolon
multiline_comment|/* the global information structure */
DECL|member|PACKED
id|CHDLC_INFORMATION_STRUCT
id|CHDLC_info_struct
id|PACKED
suffix:semicolon
multiline_comment|/* the CHDLC information structure */
DECL|member|PACKED
id|INTERRUPT_INFORMATION_STRUCT
id|interrupt_info_struct
id|PACKED
suffix:semicolon
multiline_comment|/* the interrupt information structure */
DECL|member|PACKED
id|FT1_INFORMATION_STRUCT
id|FT1_info_struct
id|PACKED
suffix:semicolon
multiline_comment|/* the S508/FT1 information structure */
DECL|typedef|SHARED_MEMORY_INFO_STRUCT
)brace
id|SHARED_MEMORY_INFO_STRUCT
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------------&n; *        UDP Management constants and structures &n; * --------------------------------------------------------------------------*/
multiline_comment|/* The embedded control block for UDP mgmt &n;   This is essentially a mailbox structure, without the large data field */
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|opp_flag
id|PACKED
suffix:semicolon
multiline_comment|/* the opp flag */
DECL|member|PACKED
r_int
r_char
id|command
id|PACKED
suffix:semicolon
multiline_comment|/* the user command */
DECL|member|PACKED
r_int
r_int
id|buffer_length
id|PACKED
suffix:semicolon
multiline_comment|/* the data length */
DECL|member|PACKED
r_int
r_char
id|return_code
id|PACKED
suffix:semicolon
multiline_comment|/* the return code */
DECL|member|PACKED
r_int
r_char
id|MB_reserved
(braket
id|NUMBER_MB_RESERVED_BYTES
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later */
DECL|typedef|cblock_t
)brace
id|cblock_t
suffix:semicolon
multiline_comment|/* UDP management packet layout (data area of ip packet) */
multiline_comment|/*&n;typedef struct {&n;&t;unsigned char&t;&t;signature[8]&t;PACKED;&n;&t;unsigned char&t;&t;request_reply&t;PACKED;&n;&t;unsigned char&t;&t;id&t;&t;PACKED;&n;&t;unsigned char&t;&t;reserved[6]&t;PACKED;&n;&t;cblock_t&t;&t;cblock&t;&t;PACKED;&n;&t;unsigned char&t;&t;num_frames&t;PACKED;&n;&t;unsigned char&t;&t;ismoredata&t;PACKED;&n;&t;unsigned char &t;&t;data[SIZEOF_MB_DATA_BFR] &t;PACKED;&n;} udp_management_packet_t;&n;&n;*/
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|num_frames
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|ismoredata
id|PACKED
suffix:semicolon
DECL|typedef|trace_info_t
)brace
id|trace_info_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|PACKED
id|ip_pkt_t
id|ip_pkt
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|udp_pkt_t
id|udp_pkt
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|wp_mgmt_t
id|wp_mgmt
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|cblock_t
id|cblock
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|trace_info_t
id|trace_info
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|data
(braket
id|SIZEOF_MB_DATA_BFR
)braket
id|PACKED
suffix:semicolon
DECL|typedef|chdlc_udp_pkt_t
)brace
id|chdlc_udp_pkt_t
suffix:semicolon
DECL|struct|ft1_exec_cmd
r_typedef
r_struct
id|ft1_exec_cmd
(brace
DECL|member|PACKED
r_int
r_char
id|command
id|PACKED
suffix:semicolon
multiline_comment|/* the user command */
DECL|member|PACKED
r_int
r_int
id|buffer_length
id|PACKED
suffix:semicolon
multiline_comment|/* the data length */
DECL|member|PACKED
r_int
r_char
id|return_code
id|PACKED
suffix:semicolon
multiline_comment|/* the return code */
DECL|member|PACKED
r_int
r_char
id|MB_reserved
(braket
id|NUMBER_MB_RESERVED_BYTES
)braket
id|PACKED
suffix:semicolon
DECL|typedef|ft1_exec_cmd_t
)brace
id|ft1_exec_cmd_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|opp_flag
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|ft1_exec_cmd_t
id|cmd
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|data
(braket
id|SIZEOF_MB_DATA_BFR
)braket
id|PACKED
suffix:semicolon
DECL|typedef|ft1_exec_t
)brace
id|ft1_exec_t
suffix:semicolon
DECL|macro|UDPMGMT_SIGNATURE
mdefine_line|#define UDPMGMT_SIGNATURE&t;&quot;CTPIPEAB&quot;
multiline_comment|/* UDP/IP packet (for UDP management) layout */
multiline_comment|/*&n;typedef struct {&n;&t;unsigned char&t;reserved[2]&t;PACKED;&n;&t;unsigned short&t;ip_length&t;PACKED;&n;&t;unsigned char&t;reserved2[4]&t;PACKED;&n;&t;unsigned char&t;ip_ttl&t;&t;PACKED;&n;&t;unsigned char&t;ip_protocol&t;PACKED;&n;&t;unsigned short&t;ip_checksum&t;PACKED;&n;&t;unsigned long&t;ip_src_address&t;PACKED;&n;&t;unsigned long&t;ip_dst_address&t;PACKED;&n;&t;unsigned short&t;udp_src_port&t;PACKED;&n;&t;unsigned short&t;udp_dst_port&t;PACKED;&n;&t;unsigned short&t;udp_length&t;PACKED;&n;&t;unsigned short&t;udp_checksum&t;PACKED;&n;&t;udp_management_packet_t um_packet PACKED;&n;} ip_packet_t;&n;*/
multiline_comment|/* valid ip_protocol for UDP management */
DECL|macro|UDPMGMT_UDP_PROTOCOL
mdefine_line|#define UDPMGMT_UDP_PROTOCOL 0x11
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|status
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|data_avail
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|real_length
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|time_stamp
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|data
(braket
l_int|1
)braket
id|PACKED
suffix:semicolon
DECL|typedef|trace_pkt_t
)brace
id|trace_pkt_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|error_flag
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|time_stamp
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|reserved
(braket
l_int|13
)braket
id|PACKED
suffix:semicolon
DECL|typedef|api_rx_hdr_t
)brace
id|api_rx_hdr_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|PACKED
id|api_rx_hdr_t
id|api_rx_hdr
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_void
op_star
id|data
id|PACKED
suffix:semicolon
DECL|typedef|api_rx_element_t
)brace
id|api_rx_element_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|attr
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|reserved
(braket
l_int|15
)braket
id|PACKED
suffix:semicolon
DECL|typedef|api_tx_hdr_t
)brace
id|api_tx_hdr_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|PACKED
id|api_tx_hdr_t
id|api_tx_hdr
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_void
op_star
id|data
id|PACKED
suffix:semicolon
DECL|typedef|api_tx_element_t
)brace
id|api_tx_element_t
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------------&n; *   Constants for the SET_FT1_CONFIGURATION/READ_FT1_CONFIGURATION command&n; * --------------------------------------------------------------------------*/
multiline_comment|/* the FT1 configuration structure */
r_typedef
r_struct
(brace
DECL|member|framing_mode
r_int
r_int
id|framing_mode
suffix:semicolon
DECL|member|encoding_mode
r_int
r_int
id|encoding_mode
suffix:semicolon
DECL|member|line_build_out
r_int
r_int
id|line_build_out
suffix:semicolon
DECL|member|channel_base
r_int
r_int
id|channel_base
suffix:semicolon
DECL|member|baud_rate_kbps
r_int
r_int
id|baud_rate_kbps
suffix:semicolon
multiline_comment|/* the baud rate (in kbps) */
DECL|member|clock_mode
r_int
r_int
id|clock_mode
suffix:semicolon
DECL|typedef|ft1_config_t
)brace
id|ft1_config_t
suffix:semicolon
multiline_comment|/* settings for the &squot;framing_mode&squot; */
DECL|macro|ESF_FRAMING
mdefine_line|#define ESF_FRAMING &t;0x00&t;/* ESF framing */
DECL|macro|D4_FRAMING
mdefine_line|#define D4_FRAMING  &t;0x01&t;/* D4 framing */
multiline_comment|/* settings for the &squot;encoding_mode&squot; */
DECL|macro|B8ZS_ENCODING
mdefine_line|#define B8ZS_ENCODING &t;0x00&t;/* B8ZS encoding */
DECL|macro|AMI_ENCODING
mdefine_line|#define AMI_ENCODING&t;0x01&t;/* AMI encoding */
multiline_comment|/* settings for the &squot;line_build_out&squot; */
DECL|macro|LN_BLD_CSU_0dB_DSX1_0_to_133
mdefine_line|#define LN_BLD_CSU_0dB_DSX1_0_to_133&t;0x00&t;/* set build out to CSU (0db) or DSX-1 (0-133ft) */
DECL|macro|LN_BLD_DSX1_133_to_266
mdefine_line|#define LN_BLD_DSX1_133_to_266&t;&t;0x01&t;/* set build out DSX-1 (133-266ft) */
DECL|macro|LN_BLD_DSX1_266_to_399
mdefine_line|#define LN_BLD_DSX1_266_to_399&t;&t;0x02&t;/* set build out DSX-1 (266-399ft) */
DECL|macro|LN_BLD_DSX1_399_to_533
mdefine_line|#define LN_BLD_DSX1_399_to_533&t;&t;0x03&t;/* set build out DSX-1 (399-533ft) */
DECL|macro|LN_BLD_DSX1_533_to_655
mdefine_line|#define LN_BLD_DSX1_533_to_655&t;&t;0x04&t;/* set build out DSX-1 (533-655ft) */
DECL|macro|LN_BLD_CSU_NEG_7dB
mdefine_line|#define LN_BLD_CSU_NEG_7dB&t;&t;0x05&t;/* set build out to CSU (-7.5db) */
DECL|macro|LN_BLD_CSU_NEG_15dB
mdefine_line|#define LN_BLD_CSU_NEG_15dB&t;&t;0x06&t;/* set build out to CSU (-15db) */
DECL|macro|LN_BLD_CSU_NEG_22dB
mdefine_line|#define LN_BLD_CSU_NEG_22dB&t;&t;0x07&t;/* set build out to CSU (-22.5db) */
multiline_comment|/* settings for the &squot;channel_base&squot; */
DECL|macro|MIN_CHANNEL_BASE_VALUE
mdefine_line|#define MIN_CHANNEL_BASE_VALUE&t;&t;1&t;&t;/* the minimum permitted channel base value */
DECL|macro|MAX_CHANNEL_BASE_VALUE
mdefine_line|#define MAX_CHANNEL_BASE_VALUE&t;&t;24&t;&t;/* the maximum permitted channel base value */
multiline_comment|/* settings for the &squot;baud_rate_kbps&squot; */
DECL|macro|MIN_BAUD_RATE_KBPS
mdefine_line|#define MIN_BAUD_RATE_KBPS&t;&t;0&t;&t;/* the minimum permitted baud rate (kbps) */
DECL|macro|MAX_BAUD_RATE_KBPS
mdefine_line|#define MAX_BAUD_RATE_KBPS &t;&t;1536&t;/* the maximum permitted baud rate (kbps) */
DECL|macro|BAUD_RATE_FT1_AUTO_CONFIG
mdefine_line|#define BAUD_RATE_FT1_AUTO_CONFIG&t;0xFFFF /* the baud rate used to trigger an automatic FT1 configuration */
multiline_comment|/* settings for the &squot;clock_mode&squot; */
DECL|macro|CLOCK_MODE_NORMAL
mdefine_line|#define CLOCK_MODE_NORMAL&t;&t;0x00&t;/* clock mode set to normal (slave) */
DECL|macro|CLOCK_MODE_MASTER
mdefine_line|#define CLOCK_MODE_MASTER&t;&t;0x01&t;/* clock mode set to master */
DECL|macro|BAUD_RATE_FT1_AUTO_CONFIG
mdefine_line|#define BAUD_RATE_FT1_AUTO_CONFIG   &t;0xFFFF
DECL|macro|AUTO_FT1_CONFIG_NOT_COMPLETE
mdefine_line|#define AUTO_FT1_CONFIG_NOT_COMPLETE&t;0x08
DECL|macro|AUTO_FT1_CFG_FAIL_OP_MODE
mdefine_line|#define AUTO_FT1_CFG_FAIL_OP_MODE&t;0x0C
DECL|macro|AUTO_FT1_CFG_FAIL_INVALID_LINE
mdefine_line|#define AUTO_FT1_CFG_FAIL_INVALID_LINE &t;0x0D
macro_line|#ifdef&t;&t;_MSC_
macro_line|#  pragma&t;pack()
macro_line|#endif
macro_line|#endif&t;/* _SDLA_CHDLC_H */
eof
