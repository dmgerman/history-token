multiline_comment|/* $Id: isdn_divertif.h,v 1.4.6.1 2001/09/23 22:25:05 kai Exp $&n; *&n; * Header for the diversion supplementary interface for i4l.&n; *&n; * Author    Werner Cornelius (werner@titro.de)&n; * Copyright by Werner Cornelius (werner@titro.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
multiline_comment|/***********************************************************/
multiline_comment|/* magic value is also used to control version information */
multiline_comment|/***********************************************************/
DECL|macro|DIVERT_IF_MAGIC
mdefine_line|#define DIVERT_IF_MAGIC 0x25873401
DECL|macro|DIVERT_CMD_REG
mdefine_line|#define DIVERT_CMD_REG  0x00  /* register command */
DECL|macro|DIVERT_CMD_REL
mdefine_line|#define DIVERT_CMD_REL  0x01  /* release command */
DECL|macro|DIVERT_NO_ERR
mdefine_line|#define DIVERT_NO_ERR   0x00  /* return value no error */
DECL|macro|DIVERT_CMD_ERR
mdefine_line|#define DIVERT_CMD_ERR  0x01  /* invalid cmd */
DECL|macro|DIVERT_VER_ERR
mdefine_line|#define DIVERT_VER_ERR  0x02  /* magic/version invalid */
DECL|macro|DIVERT_REG_ERR
mdefine_line|#define DIVERT_REG_ERR  0x03  /* module already registered */
DECL|macro|DIVERT_REL_ERR
mdefine_line|#define DIVERT_REL_ERR  0x04  /* module not registered */
DECL|macro|DIVERT_REG_NAME
mdefine_line|#define DIVERT_REG_NAME isdn_register_divert
multiline_comment|/***************************************************************/
multiline_comment|/* structure exchanging data between isdn hl and divert module */
multiline_comment|/***************************************************************/
r_typedef
r_struct
DECL|member|if_magic
(brace
id|ulong
id|if_magic
suffix:semicolon
multiline_comment|/* magic info and version */
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
multiline_comment|/* command */
DECL|member|stat_callback
r_int
(paren
op_star
id|stat_callback
)paren
(paren
id|isdn_ctrl
op_star
)paren
suffix:semicolon
multiline_comment|/* supplied by divert module when calling */
DECL|member|ll_cmd
r_int
(paren
op_star
id|ll_cmd
)paren
(paren
id|isdn_ctrl
op_star
)paren
suffix:semicolon
multiline_comment|/* supplied by hl on return */
DECL|member|drv_to_name
r_char
op_star
(paren
op_star
id|drv_to_name
)paren
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* map a driver id to name, supplied by hl */
DECL|member|name_to_drv
r_int
(paren
op_star
id|name_to_drv
)paren
(paren
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* map a driver id to name, supplied by hl */
DECL|typedef|isdn_divert_if
)brace
id|isdn_divert_if
suffix:semicolon
multiline_comment|/*********************/
multiline_comment|/* function register */
multiline_comment|/*********************/
r_extern
r_int
id|DIVERT_REG_NAME
c_func
(paren
id|isdn_divert_if
op_star
)paren
suffix:semicolon
eof
