multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
DECL|macro|PHYS
mdefine_line|#define PHYS&t;&t;&t;0&t;&t;/* physical addr */
DECL|macro|PERM_ADDR
mdefine_line|#define PERM_ADDR&t;&t;0x80&t;&t;/* permanet address */
DECL|macro|SB_STATIC
mdefine_line|#define SB_STATIC&t;&t;0x00000001
DECL|macro|MAX_PAYLOAD
mdefine_line|#define MAX_PAYLOAD&t;&t;1562
DECL|macro|PRIMARY_RING
mdefine_line|#define PRIMARY_RING&t;&t;0x00000001
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL&t;&t;&t;0x00
macro_line|#endif
multiline_comment|/*********************** SB_Input Variable Values ***********************/
multiline_comment|/*&t; may be needed when ever the SBA state machine is called&t;*/
DECL|macro|UNKNOWN_SYNC_SOURCE
mdefine_line|#define UNKNOWN_SYNC_SOURCE&t;0x0001
DECL|macro|REQ_ALLOCATION
mdefine_line|#define REQ_ALLOCATION&t;&t;0x0002
DECL|macro|REPORT_RESP
mdefine_line|#define REPORT_RESP&t;&t;0x0003
DECL|macro|CHANGE_RESP
mdefine_line|#define CHANGE_RESP&t;&t;0x0004
DECL|macro|TNEG
mdefine_line|#define TNEG&t;&t;&t;0x0005
DECL|macro|NIF
mdefine_line|#define NIF&t;&t;&t;0x0006
DECL|macro|SB_STOP
mdefine_line|#define SB_STOP&t;&t;&t;0x0007
DECL|macro|SB_START
mdefine_line|#define SB_START&t;&t;0x0008
DECL|macro|REPORT_TIMER
mdefine_line|#define REPORT_TIMER&t;&t;0x0009
DECL|macro|CHANGE_REQUIRED
mdefine_line|#define CHANGE_REQUIRED&t;&t;0x000A
DECL|macro|DEFAULT_OV
mdefine_line|#define DEFAULT_OV&t;&t;50
macro_line|#ifdef SBA
multiline_comment|/**************************** SBA STATES *****************************/
DECL|macro|SBA_STANDBY
mdefine_line|#define SBA_STANDBY&t;&t;0x00000000
DECL|macro|SBA_ACTIVE
mdefine_line|#define SBA_ACTIVE&t;&t;0x00000001
DECL|macro|SBA_RECOVERY
mdefine_line|#define SBA_RECOVERY&t;&t;0x00000002
DECL|macro|SBA_REPORT
mdefine_line|#define SBA_REPORT&t;&t;0x00000003
DECL|macro|SBA_CHANGE
mdefine_line|#define SBA_CHANGE&t;&t;0x00000004
multiline_comment|/**************************** OTHERS *********************************/
DECL|macro|FIFTY_PERCENT
mdefine_line|#define FIFTY_PERCENT&t;&t;50&t;&t;/* bytes per second */
DECL|macro|MAX_SESSIONS
mdefine_line|#define MAX_SESSIONS&t;&t;150&t;
DECL|macro|TWO_MINUTES
mdefine_line|#define TWO_MINUTES&t;&t;13079&t;&t;/* 9.175 ms/tick */
DECL|macro|FIFTY_BYTES
mdefine_line|#define FIFTY_BYTES&t;&t;50
DECL|macro|SBA_DENIED
mdefine_line|#define SBA_DENIED&t;&t;0x0000000D
DECL|macro|I_NEED_ONE
mdefine_line|#define I_NEED_ONE&t;&t;0x00000000
DECL|macro|MAX_NODES
mdefine_line|#define MAX_NODES&t;&t;50
multiline_comment|/*#define T_REPORT&t;&t;0x59682F00L*/
multiline_comment|/* 120s/80ns in Hex */
DECL|macro|TWO_MIN
mdefine_line|#define&t;TWO_MIN&t;&t;&t;120&t;&t;/* seconds */
DECL|macro|SBA_ST_UNKNOWN
mdefine_line|#define SBA_ST_UNKNOWN&t;&t;0x00000002
DECL|macro|SBA_ST_ACTIVE
mdefine_line|#define SBA_ST_ACTIVE&t;&t;0x00000001
DECL|macro|S_CLEAR
mdefine_line|#define S_CLEAR&t;&t;&t;0x00000000L
DECL|macro|ZERO
mdefine_line|#define ZERO&t;&t;&t;0x00000000
DECL|macro|FULL
mdefine_line|#define FULL&t;&t;&t;0x00000000&t;/* old: 0xFFFFFFFFF */
DECL|macro|S_SET
mdefine_line|#define S_SET&t;&t;&t;0x00000001L
DECL|macro|LOW_PRIO
mdefine_line|#define LOW_PRIO&t;&t;0x02&t;&t;/* ??????? */
DECL|macro|OK
mdefine_line|#define OK&t;&t;&t;0x01&t;&t;/* ??????? */
DECL|macro|NOT_OK
mdefine_line|#define NOT_OK&t;&t;&t;0x00&t;&t;/* ??????? */
multiline_comment|/****************************************/
multiline_comment|/* deallocate_status[ni][si] values&t;*/
multiline_comment|/****************************************/
DECL|macro|TX_CHANGE
mdefine_line|#define TX_CHANGE&t;&t;0X00000001L
DECL|macro|PENDING
mdefine_line|#define PENDING&t;&t;&t;0x00000002L
DECL|macro|NONE
mdefine_line|#define NONE&t;&t;&t;0X00000000L
macro_line|#endif
eof
