multiline_comment|/* $Id: xdi_msg.h,v 1.1.2.2 2002/10/02 14:38:38 armin Exp $ */
macro_line|#ifndef __DIVA_XDI_UM_CFG_MESSSGE_H__
DECL|macro|__DIVA_XDI_UM_CFG_MESSAGE_H__
mdefine_line|#define __DIVA_XDI_UM_CFG_MESSAGE_H__
multiline_comment|/*&n;  Definition of messages used to communicate between&n;  XDI device driver and user mode configuration utility&n;*/
multiline_comment|/*&n;  As acknowledge one DWORD - card ordinal will be read from the card&n;*/
DECL|macro|DIVA_XDI_UM_CMD_GET_CARD_ORDINAL
mdefine_line|#define DIVA_XDI_UM_CMD_GET_CARD_ORDINAL&t;0
multiline_comment|/*&n;  no acknowledge will be generated, memory block will be written in the&n;  memory at given offset&n;*/
DECL|macro|DIVA_XDI_UM_CMD_WRITE_SDRAM_BLOCK
mdefine_line|#define DIVA_XDI_UM_CMD_WRITE_SDRAM_BLOCK&t;1
multiline_comment|/*&n;  no acknowledge will be genatated, FPGA will be programmed&n;*/
DECL|macro|DIVA_XDI_UM_CMD_WRITE_FPGA
mdefine_line|#define DIVA_XDI_UM_CMD_WRITE_FPGA&t;&t;&t;&t;2
multiline_comment|/*&n;  As acknowledge block of SDRAM will be read in the user buffer&n;*/
DECL|macro|DIVA_XDI_UM_CMD_READ_SDRAM
mdefine_line|#define DIVA_XDI_UM_CMD_READ_SDRAM&t;&t;&t;&t;3
multiline_comment|/*&n;  As acknowledge dword with serial number will be read in the user buffer&n;*/
DECL|macro|DIVA_XDI_UM_CMD_GET_SERIAL_NR
mdefine_line|#define DIVA_XDI_UM_CMD_GET_SERIAL_NR&t;&t;&t;4
multiline_comment|/*&n;  As acknowledge struct consisting from 9 dwords with PCI info.&n;  dword[0...7] = 8 PCI BARS&n;  dword[9]&t;&t; = IRQ&n;*/
DECL|macro|DIVA_XDI_UM_CMD_GET_PCI_HW_CONFIG
mdefine_line|#define DIVA_XDI_UM_CMD_GET_PCI_HW_CONFIG&t;5
multiline_comment|/*&n;  Reset of the board + activation of primary&n;  boot loader&n;*/
DECL|macro|DIVA_XDI_UM_CMD_RESET_ADAPTER
mdefine_line|#define DIVA_XDI_UM_CMD_RESET_ADAPTER&t;&t;&t;6
multiline_comment|/*&n;  Called after code download to start adapter&n;  at specified address&n;  Start does set new set of features due to fact that we not know&n;  if protocol features have changed&n;*/
DECL|macro|DIVA_XDI_UM_CMD_START_ADAPTER
mdefine_line|#define DIVA_XDI_UM_CMD_START_ADAPTER&t;&t;&t;7
multiline_comment|/*&n;  Stop adapter, called if user&n;  wishes to stop adapter without unload&n;  of the driver, to reload adapter with&n;  different protocol&n;*/
DECL|macro|DIVA_XDI_UM_CMD_STOP_ADAPTER
mdefine_line|#define DIVA_XDI_UM_CMD_STOP_ADAPTER&t;&t;&t;8
multiline_comment|/*&n;  Get state of current adapter&n;  Acknowledge is one dword with following values:&n;  0 - adapter ready for download&n;  1 - adapter running&n;  2 - adapter dead&n;  3 - out of service, driver should be restarted or hardware problem&n;*/
DECL|macro|DIVA_XDI_UM_CMD_GET_CARD_STATE
mdefine_line|#define DIVA_XDI_UM_CMD_GET_CARD_STATE&t;&t;9
multiline_comment|/*&n;  Reads XLOG entry from the card&n;*/
DECL|macro|DIVA_XDI_UM_CMD_READ_XLOG_ENTRY
mdefine_line|#define DIVA_XDI_UM_CMD_READ_XLOG_ENTRY&t;&t;10
multiline_comment|/*&n;  Set untranslated protocol code features&n;  */
DECL|macro|DIVA_XDI_UM_CMD_SET_PROTOCOL_FEATURES
mdefine_line|#define DIVA_XDI_UM_CMD_SET_PROTOCOL_FEATURES&t;11
DECL|struct|_diva_xdi_um_cfg_cmd_data_set_features
r_typedef
r_struct
id|_diva_xdi_um_cfg_cmd_data_set_features
(brace
DECL|member|features
id|dword
id|features
suffix:semicolon
DECL|typedef|diva_xdi_um_cfg_cmd_data_set_features_t
)brace
id|diva_xdi_um_cfg_cmd_data_set_features_t
suffix:semicolon
DECL|struct|_diva_xdi_um_cfg_cmd_data_start
r_typedef
r_struct
id|_diva_xdi_um_cfg_cmd_data_start
(brace
DECL|member|offset
id|dword
id|offset
suffix:semicolon
DECL|member|features
id|dword
id|features
suffix:semicolon
DECL|typedef|diva_xdi_um_cfg_cmd_data_start_t
)brace
id|diva_xdi_um_cfg_cmd_data_start_t
suffix:semicolon
DECL|struct|_diva_xdi_um_cfg_cmd_data_write_sdram
r_typedef
r_struct
id|_diva_xdi_um_cfg_cmd_data_write_sdram
(brace
DECL|member|ram_number
id|dword
id|ram_number
suffix:semicolon
DECL|member|offset
id|dword
id|offset
suffix:semicolon
DECL|member|length
id|dword
id|length
suffix:semicolon
DECL|typedef|diva_xdi_um_cfg_cmd_data_write_sdram_t
)brace
id|diva_xdi_um_cfg_cmd_data_write_sdram_t
suffix:semicolon
DECL|struct|_diva_xdi_um_cfg_cmd_data_write_fpga
r_typedef
r_struct
id|_diva_xdi_um_cfg_cmd_data_write_fpga
(brace
DECL|member|fpga_number
id|dword
id|fpga_number
suffix:semicolon
DECL|member|image_length
id|dword
id|image_length
suffix:semicolon
DECL|typedef|diva_xdi_um_cfg_cmd_data_write_fpga_t
)brace
id|diva_xdi_um_cfg_cmd_data_write_fpga_t
suffix:semicolon
DECL|struct|_diva_xdi_um_cfg_cmd_data_read_sdram
r_typedef
r_struct
id|_diva_xdi_um_cfg_cmd_data_read_sdram
(brace
DECL|member|ram_number
id|dword
id|ram_number
suffix:semicolon
DECL|member|offset
id|dword
id|offset
suffix:semicolon
DECL|member|length
id|dword
id|length
suffix:semicolon
DECL|typedef|diva_xdi_um_cfg_cmd_data_read_sdram_t
)brace
id|diva_xdi_um_cfg_cmd_data_read_sdram_t
suffix:semicolon
DECL|union|_diva_xdi_um_cfg_cmd_data
r_typedef
r_union
id|_diva_xdi_um_cfg_cmd_data
(brace
DECL|member|write_sdram
id|diva_xdi_um_cfg_cmd_data_write_sdram_t
id|write_sdram
suffix:semicolon
DECL|member|write_fpga
id|diva_xdi_um_cfg_cmd_data_write_fpga_t
id|write_fpga
suffix:semicolon
DECL|member|read_sdram
id|diva_xdi_um_cfg_cmd_data_read_sdram_t
id|read_sdram
suffix:semicolon
DECL|member|start
id|diva_xdi_um_cfg_cmd_data_start_t
id|start
suffix:semicolon
DECL|member|features
id|diva_xdi_um_cfg_cmd_data_set_features_t
id|features
suffix:semicolon
DECL|typedef|diva_xdi_um_cfg_cmd_data_t
)brace
id|diva_xdi_um_cfg_cmd_data_t
suffix:semicolon
DECL|struct|_diva_xdi_um_cfg_cmd
r_typedef
r_struct
id|_diva_xdi_um_cfg_cmd
(brace
DECL|member|adapter
id|dword
id|adapter
suffix:semicolon
multiline_comment|/* Adapter number 1...N */
DECL|member|command
id|dword
id|command
suffix:semicolon
DECL|member|command_data
id|diva_xdi_um_cfg_cmd_data_t
id|command_data
suffix:semicolon
DECL|member|data_length
id|dword
id|data_length
suffix:semicolon
multiline_comment|/* Plain binary data will follow */
DECL|typedef|diva_xdi_um_cfg_cmd_t
)brace
id|diva_xdi_um_cfg_cmd_t
suffix:semicolon
macro_line|#endif
eof
