multiline_comment|/*****************************************************************************&n;* sdla_asy.h&t;Header file for the Sangoma S508/S514 asynchronous code API&t;&n;*&n;* Author: &t;Gideon Hack &t;&n;*&n;* Copyright:&t;(c) 2000 Sangoma Technologies Inc.&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;*&n;* Jan 28, 2000&t;Gideon Hack &t;Initial Version&n;*&n;*****************************************************************************/
macro_line|#ifndef _WANPIPE_ASYNC_H
DECL|macro|_WANPIPE_ASYNC_H
mdefine_line|#define _WANPIPE_ASYNC_H
multiline_comment|/* ----------------------------------------------------------------------------&n; *                        Interface commands&n; * --------------------------------------------------------------------------*/
DECL|macro|SET_ASY_CONFIGURATION
mdefine_line|#define SET_ASY_CONFIGURATION&t;&t;0xE2&t;/* set the asychronous operational configuration */
DECL|macro|READ_ASY_CONFIGURATION
mdefine_line|#define READ_ASY_CONFIGURATION&t;&t;0xE3&t;/* read the current asychronous operational configuration */
DECL|macro|ENABLE_ASY_COMMUNICATIONS
mdefine_line|#define ENABLE_ASY_COMMUNICATIONS&t;0xE4&t;/* enable asychronous communications */
DECL|macro|DISABLE_ASY_COMMUNICATIONS
mdefine_line|#define DISABLE_ASY_COMMUNICATIONS&t;0xE5&t;/* disable asychronous communications */
DECL|macro|READ_ASY_OPERATIONAL_STATS
mdefine_line|#define READ_ASY_OPERATIONAL_STATS&t;0xE7&t;/* retrieve the asychronous operational statistics */
DECL|macro|FLUSH_ASY_OPERATIONAL_STATS
mdefine_line|#define FLUSH_ASY_OPERATIONAL_STATS&t;0xE8&t;/* flush the asychronous operational statistics */
DECL|macro|TRANSMIT_ASY_BREAK_SIGNAL
mdefine_line|#define TRANSMIT_ASY_BREAK_SIGNAL&t;0xEC&t;/* transmit an asychronous break signal */
multiline_comment|/* ----------------------------------------------------------------------------&n; *                     Return codes from interface commands&n; * --------------------------------------------------------------------------*/
DECL|macro|COMMAND_INVALID_FOR_PORT
mdefine_line|#define COMMAND_INVALID_FOR_PORT&t;0x50&t;/* the command is invalid for the selected port */
DECL|macro|DISABLE_ASY_COMMS_BEFORE_CFG
mdefine_line|#define DISABLE_ASY_COMMS_BEFORE_CFG &t;0xE1&t;/* communications must be disabled before setting the configuration */
DECL|macro|ASY_COMMS_ENABLED
mdefine_line|#define ASY_COMMS_ENABLED&t;&t;0xE1&t;/* communications are currently enabled */
DECL|macro|ASY_COMMS_DISABLED
mdefine_line|#define ASY_COMMS_DISABLED&t;&t;0xE1&t;/* communications are currently disabled */
DECL|macro|ASY_CFG_BEFORE_COMMS_ENABLED
mdefine_line|#define ASY_CFG_BEFORE_COMMS_ENABLED&t;0xE2&t;/* perform a SET_ASY_CONFIGURATION before enabling comms */
DECL|macro|LGTH_ASY_CFG_DATA_INVALID
mdefine_line|#define LGTH_ASY_CFG_DATA_INVALID  &t;0xE2&t;/* the length of the passed configuration data is invalid */
DECL|macro|INVALID_ASY_CFG_DATA
mdefine_line|#define INVALID_ASY_CFG_DATA&t;&t;0xE3&t;/* the passed configuration data is invalid */
DECL|macro|ASY_BREAK_SIGNAL_BUSY
mdefine_line|#define ASY_BREAK_SIGNAL_BUSY&t;&t;0xEC&t;/* a break signal is being transmitted */
multiline_comment|/* ----------------------------------------------------------------------------&n; *   Constants for the SET_ASY_CONFIGURATION/READ_ASY_CONFIGURATION command&n; * --------------------------------------------------------------------------*/
multiline_comment|/* the asynchronous configuration structure */
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
multiline_comment|/* modem configuration options */
DECL|member|PACKED
r_int
r_int
id|asy_API_options
id|PACKED
suffix:semicolon
multiline_comment|/* asynchronous API options */
DECL|member|PACKED
r_int
r_int
id|asy_protocol_options
id|PACKED
suffix:semicolon
multiline_comment|/* asynchronous protocol options */
DECL|member|PACKED
r_int
r_int
id|Tx_bits_per_char
id|PACKED
suffix:semicolon
multiline_comment|/* number of bits per tx character */
DECL|member|PACKED
r_int
r_int
id|Rx_bits_per_char
id|PACKED
suffix:semicolon
multiline_comment|/* number of bits per received character */
DECL|member|PACKED
r_int
r_int
id|stop_bits
id|PACKED
suffix:semicolon
multiline_comment|/* number of stop bits per character */
DECL|member|PACKED
r_int
r_int
id|parity
id|PACKED
suffix:semicolon
multiline_comment|/* parity definition */
DECL|member|PACKED
r_int
r_int
id|break_timer
id|PACKED
suffix:semicolon
multiline_comment|/* the break signal timer */
DECL|member|PACKED
r_int
r_int
id|asy_Rx_inter_char_timer
id|PACKED
suffix:semicolon
multiline_comment|/* the receive inter-character timer */
DECL|member|PACKED
r_int
r_int
id|asy_Rx_complete_length
id|PACKED
suffix:semicolon
multiline_comment|/* the receive &squot;buffer complete&squot; length */
DECL|member|PACKED
r_int
r_int
id|XON_char
id|PACKED
suffix:semicolon
multiline_comment|/* the XON character */
DECL|member|PACKED
r_int
r_int
id|XOFF_char
id|PACKED
suffix:semicolon
multiline_comment|/* the XOFF character */
DECL|member|PACKED
r_int
r_int
id|asy_statistics_options
id|PACKED
suffix:semicolon
multiline_comment|/* async operational stat options */
DECL|member|PACKED
r_int
r_int
id|ptr_shared_mem_info_struct
id|PACKED
suffix:semicolon
multiline_comment|/* ptr to the shared memory area information structure */
DECL|member|PACKED
r_int
r_int
id|ptr_asy_Tx_stat_el_cfg_struct
id|PACKED
suffix:semicolon
multiline_comment|/* ptr to the transmit status element configuration structure */
DECL|member|PACKED
r_int
r_int
id|ptr_asy_Rx_stat_el_cfg_struct
id|PACKED
suffix:semicolon
multiline_comment|/* ptr to the receive status element configuration structure */
DECL|typedef|ASY_CONFIGURATION_STRUCT
)brace
id|ASY_CONFIGURATION_STRUCT
suffix:semicolon
multiline_comment|/* permitted minimum and maximum values for setting the asynchronous configuration */
DECL|macro|MIN_ASY_BAUD_RATE
mdefine_line|#define MIN_ASY_BAUD_RATE&t;&t;50&t;/* maximum baud rate */
DECL|macro|MAX_ASY_BAUD_RATE
mdefine_line|#define MAX_ASY_BAUD_RATE&t;&t;250000&t;/* minimum baud rate */
DECL|macro|MIN_ASY_BITS_PER_CHAR
mdefine_line|#define MIN_ASY_BITS_PER_CHAR&t;&t;5&t;/* minimum number of bits per character */
DECL|macro|MAX_ASY_BITS_PER_CHAR
mdefine_line|#define MAX_ASY_BITS_PER_CHAR&t;&t;8&t;/* maximum number of bits per character */
DECL|macro|MIN_BREAK_TMR_VAL
mdefine_line|#define MIN_BREAK_TMR_VAL&t;&t;0&t;/* minimum break signal timer */
DECL|macro|MAX_BREAK_TMR_VAL
mdefine_line|#define MAX_BREAK_TMR_VAL&t;&t;5000&t;/* maximum break signal timer */
DECL|macro|MIN_ASY_RX_INTER_CHAR_TMR
mdefine_line|#define MIN_ASY_RX_INTER_CHAR_TMR&t;0&t;/* minimum receive inter-character timer */
DECL|macro|MAX_ASY_RX_INTER_CHAR_TMR
mdefine_line|#define MAX_ASY_RX_INTER_CHAR_TMR&t;30000&t;/* maximum receive inter-character timer */
DECL|macro|MIN_ASY_RX_CPLT_LENGTH
mdefine_line|#define MIN_ASY_RX_CPLT_LENGTH&t;&t;0&t;/* minimum receive &squot;length complete&squot; value */
DECL|macro|MAX_ASY_RX_CPLT_LENGTH
mdefine_line|#define MAX_ASY_RX_CPLT_LENGTH&t;&t;2000&t;/* maximum receive &squot;length complete&squot; value */
multiline_comment|/* bit settings for the &squot;asy_API_options&squot; */
DECL|macro|ASY_RX_DATA_TRANSPARENT
mdefine_line|#define ASY_RX_DATA_TRANSPARENT&t;&t;0x0001&t;/* do not strip parity and unused bits from received characters */
multiline_comment|/* bit settings for the &squot;asy_protocol_options&squot; */
DECL|macro|ASY_RTS_HS_FOR_RX
mdefine_line|#define ASY_RTS_HS_FOR_RX&t;&t;0x0001&t;/* RTS handshaking is used for reception control */
DECL|macro|ASY_XON_XOFF_HS_FOR_RX
mdefine_line|#define ASY_XON_XOFF_HS_FOR_RX&t;&t;0x0002&t;/* XON/XOFF handshaking is used for reception control */
DECL|macro|ASY_XON_XOFF_HS_FOR_TX
mdefine_line|#define ASY_XON_XOFF_HS_FOR_TX&t;&t;0x0004&t;/* XON/XOFF handshaking is used for transmission control */
DECL|macro|ASY_DCD_HS_FOR_TX
mdefine_line|#define ASY_DCD_HS_FOR_TX&t;&t;0x0008&t;/* DCD handshaking is used for transmission control */
DECL|macro|ASY_CTS_HS_FOR_TX
mdefine_line|#define ASY_CTS_HS_FOR_TX&t;&t;0x0020&t;/* CTS handshaking is used for transmission control */
multiline_comment|/* bit settings for the &squot;stop_bits&squot; definition */
DECL|macro|ONE_STOP_BIT
mdefine_line|#define ONE_STOP_BIT&t;&t;&t;1&t;&t;&t;/* representation for 1 stop bit */
DECL|macro|TWO_STOP_BITS
mdefine_line|#define TWO_STOP_BITS&t;&t;&t;2&t;&t;&t;/* representation for 2 stop bits */
DECL|macro|ONE_AND_A_HALF_STOP_BITS
mdefine_line|#define ONE_AND_A_HALF_STOP_BITS&t;3&t;&t;&t;/* representation for 1.5 stop bits */
multiline_comment|/* bit settings for the &squot;parity&squot; definition */
DECL|macro|NO_PARITY
mdefine_line|#define NO_PARITY&t;&t;&t;0&t;&t;&t;/* representation for no parity */
DECL|macro|ODD_PARITY
mdefine_line|#define ODD_PARITY&t;&t;&t;1&t;&t;&t;/* representation for odd parity */
DECL|macro|EVEN_PARITY
mdefine_line|#define EVEN_PARITY&t;&t;&t;2&t;&t;&t;/* representation for even parity */
multiline_comment|/* ----------------------------------------------------------------------------&n; *    Constants for the READ_COMMS_ERROR_STATS command (asynchronous mode)&n; * --------------------------------------------------------------------------*/
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
multiline_comment|/* receiver overrun error count */
DECL|member|PACKED
r_int
r_int
id|Rx_parity_err_count
id|PACKED
suffix:semicolon
multiline_comment|/* parity errors received count */
DECL|member|PACKED
r_int
r_int
id|Rx_framing_err_count
id|PACKED
suffix:semicolon
multiline_comment|/* framing errors received count */
DECL|member|PACKED
r_int
r_int
id|comms_err_stat_reserved_1
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later use */
DECL|member|PACKED
r_int
r_int
id|comms_err_stat_reserved_2
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later use */
DECL|member|PACKED
r_int
r_int
id|comms_err_stat_reserved_3
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later use */
DECL|member|PACKED
r_int
r_int
id|comms_err_stat_reserved_4
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later use */
DECL|member|PACKED
r_int
r_int
id|comms_err_stat_reserved_5
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later use */
DECL|member|PACKED
r_int
r_int
id|DCD_state_change_count
id|PACKED
suffix:semicolon
multiline_comment|/* DCD state change count */
DECL|member|PACKED
r_int
r_int
id|CTS_state_change_count
id|PACKED
suffix:semicolon
multiline_comment|/* CTS state change count */
DECL|typedef|ASY_COMMS_ERROR_STATS_STRUCT
)brace
id|ASY_COMMS_ERROR_STATS_STRUCT
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------------&n; *         Constants for the READ_ASY_OPERATIONAL_STATS command&n; * --------------------------------------------------------------------------*/
multiline_comment|/* the asynchronous operational statistics structure */
r_typedef
r_struct
(brace
multiline_comment|/* Data transmission statistics */
DECL|member|PACKED
r_int
r_int
id|Data_blocks_Tx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of blocks transmitted */
DECL|member|PACKED
r_int
r_int
id|Data_bytes_Tx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of bytes transmitted */
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
multiline_comment|/* number of Data blocks discarded (length error) */
DECL|member|PACKED
r_int
r_int
id|reserved_Data_frm_Tx_stat1
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later use */
DECL|member|PACKED
r_int
r_int
id|reserved_Data_frm_Tx_stat2
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later use */
DECL|member|PACKED
r_int
r_int
id|reserved_Data_frm_Tx_stat3
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later use */
multiline_comment|/* Data reception statistics */
DECL|member|PACKED
r_int
r_int
id|Data_blocks_Rx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of blocks received */
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
id|Rx_Data_bytes_discard_count
id|PACKED
suffix:semicolon
multiline_comment|/* received Data bytes discarded */
DECL|member|PACKED
r_int
r_int
id|reserved_Data_frm_Rx_stat1
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later use */
multiline_comment|/* handshaking protocol statistics */
DECL|member|PACKED
r_int
r_int
id|XON_chars_Tx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of XON characters transmitted */
DECL|member|PACKED
r_int
r_int
id|XOFF_chars_Tx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of XOFF characters transmitted */
DECL|member|PACKED
r_int
r_int
id|XON_chars_Rx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of XON characters received */
DECL|member|PACKED
r_int
r_int
id|XOFF_chars_Rx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of XOFF characters received */
DECL|member|PACKED
r_int
r_int
id|Tx_halt_modem_low_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of times Tx halted (modem line low) */
DECL|member|PACKED
r_int
r_int
id|Rx_halt_RTS_low_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of times Rx halted by setting RTS low */
DECL|member|PACKED
r_int
r_int
id|reserved_handshaking_stat1
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later use */
multiline_comment|/* break statistics */
DECL|member|PACKED
r_int
r_int
id|break_Tx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of break sequences transmitted */
DECL|member|PACKED
r_int
r_int
id|break_Rx_count
id|PACKED
suffix:semicolon
multiline_comment|/* number of break sequences received */
DECL|member|PACKED
r_int
r_int
id|reserved_break_stat1
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
multiline_comment|/* reserved for later use */
DECL|member|PACKED
r_int
r_int
id|reserved_misc_stat2
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for later use */
DECL|typedef|ASY_OPERATIONAL_STATS_STRUCT
)brace
id|ASY_OPERATIONAL_STATS_STRUCT
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------------&n; *                      Constants for Data transmission&n; * --------------------------------------------------------------------------*/
multiline_comment|/* the Data block transmit status element configuration structure */
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
DECL|typedef|ASY_TX_STATUS_EL_CFG_STRUCT
)brace
id|ASY_TX_STATUS_EL_CFG_STRUCT
suffix:semicolon
multiline_comment|/* the Data block transmit status element structure */
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
id|data_length
id|PACKED
suffix:semicolon
multiline_comment|/* length of the block to be transmitted */
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
DECL|typedef|ASY_DATA_TX_STATUS_EL_STRUCT
)brace
id|ASY_DATA_TX_STATUS_EL_STRUCT
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------------&n; *                      Constants for Data reception&n; * --------------------------------------------------------------------------*/
multiline_comment|/* the Data block receive status element configuration structure */
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
DECL|typedef|ASY_RX_STATUS_EL_CFG_STRUCT
)brace
id|ASY_RX_STATUS_EL_CFG_STRUCT
suffix:semicolon
multiline_comment|/* the Data block receive status element structure */
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
id|data_length
id|PACKED
suffix:semicolon
multiline_comment|/* length of the received data block */
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
id|time_stamp
id|PACKED
suffix:semicolon
multiline_comment|/* receive time stamp (HDLC_STREAMING_MODE) */
DECL|member|PACKED
r_int
r_int
id|data_buffered
id|PACKED
suffix:semicolon
multiline_comment|/* the number of data bytes still buffered */
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
DECL|typedef|ASY_DATA_RX_STATUS_EL_STRUCT
)brace
id|ASY_DATA_RX_STATUS_EL_STRUCT
suffix:semicolon
macro_line|#endif
eof
