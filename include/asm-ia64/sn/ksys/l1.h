multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992-1997,2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; */
macro_line|#ifndef _ASM_SN_KSYS_L1_H
DECL|macro|_ASM_SN_KSYS_L1_H
mdefine_line|#define _ASM_SN_KSYS_L1_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/vector.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/sn/sv.h&gt;
multiline_comment|/* L1 Target Addresses */
multiline_comment|/*&n; * L1 commands and responses use source/target addresses that are&n; * 32 bits long.  These are broken up into multiple bitfields that&n; * specify the type of the target controller (could actually be L2&n; * L3, not just L1), the rack and bay of the target, and the task&n; * id (L1 functionality is divided into several independent &quot;tasks&quot;&n; * that can each receive command requests and transmit responses)&n; */
DECL|macro|L1_ADDR_TYPE_L1
mdefine_line|#define L1_ADDR_TYPE_L1&t;&t;0x00&t;/* L1 system controller */
DECL|macro|L1_ADDR_TYPE_L2
mdefine_line|#define L1_ADDR_TYPE_L2&t;&t;0x01&t;/* L2 system controller */
DECL|macro|L1_ADDR_TYPE_L3
mdefine_line|#define L1_ADDR_TYPE_L3&t;&t;0x02&t;/* L3 system controller */
DECL|macro|L1_ADDR_TYPE_CBRICK
mdefine_line|#define L1_ADDR_TYPE_CBRICK&t;0x03&t;/* attached C brick&t;*/
DECL|macro|L1_ADDR_TYPE_IOBRICK
mdefine_line|#define L1_ADDR_TYPE_IOBRICK&t;0x04&t;/* attached I/O brick&t;*/
DECL|macro|L1_ADDR_TASK_SHFT
mdefine_line|#define L1_ADDR_TASK_SHFT&t;0
DECL|macro|L1_ADDR_TASK_MASK
mdefine_line|#define L1_ADDR_TASK_MASK&t;0x0000001F
DECL|macro|L1_ADDR_TASK_INVALID
mdefine_line|#define L1_ADDR_TASK_INVALID&t;0x00&t;/* invalid task &t;*/
DECL|macro|L1_ADDR_TASK_IROUTER
mdefine_line|#define&t;L1_ADDR_TASK_IROUTER&t;0x01&t;/* iRouter&t;&t;*/
DECL|macro|L1_ADDR_TASK_SYS_MGMT
mdefine_line|#define L1_ADDR_TASK_SYS_MGMT&t;0x02&t;/* system management port */
DECL|macro|L1_ADDR_TASK_CMD
mdefine_line|#define L1_ADDR_TASK_CMD&t;0x03&t;/* command interpreter&t;*/
DECL|macro|L1_ADDR_TASK_ENV
mdefine_line|#define L1_ADDR_TASK_ENV&t;0x04&t;/* environmental monitor */
DECL|macro|L1_ADDR_TASK_BEDROCK
mdefine_line|#define L1_ADDR_TASK_BEDROCK&t;0x05&t;/* bedrock&t;&t;*/
DECL|macro|L1_ADDR_TASK_GENERAL
mdefine_line|#define L1_ADDR_TASK_GENERAL&t;0x06&t;/* general requests&t;*/
DECL|macro|L1_ADDR_LOCAL
mdefine_line|#define L1_ADDR_LOCAL&t;&t;&t;&t;&bslash;&n;    (L1_ADDR_TYPE_L1 &lt;&lt; L1_ADDR_TYPE_SHFT) |&t;&bslash;&n;    (L1_ADDR_RACK_LOCAL &lt;&lt; L1_ADDR_RACK_SHFT) |&t;&bslash;&n;    (L1_ADDR_BAY_LOCAL &lt;&lt; L1_ADDR_BAY_SHFT)
DECL|macro|L1_ADDR_LOCALIO
mdefine_line|#define L1_ADDR_LOCALIO&t;&t;&t;&t;&t;&bslash;&n;    (L1_ADDR_TYPE_IOBRICK &lt;&lt; L1_ADDR_TYPE_SHFT) |&t;&bslash;&n;    (L1_ADDR_RACK_LOCAL &lt;&lt; L1_ADDR_RACK_SHFT) |&t;&t;&bslash;&n;    (L1_ADDR_BAY_LOCAL &lt;&lt; L1_ADDR_BAY_SHFT)
DECL|macro|L1_ADDR_LOCAL_SHFT
mdefine_line|#define L1_ADDR_LOCAL_SHFT&t;L1_ADDR_BAY_SHFT
multiline_comment|/* response argument types */
DECL|macro|L1_ARG_INT
mdefine_line|#define L1_ARG_INT&t;&t;0x00&t;/* 4-byte integer (big-endian)&t;*/
DECL|macro|L1_ARG_ASCII
mdefine_line|#define L1_ARG_ASCII&t;&t;0x01&t;/* null-terminated ASCII string */
DECL|macro|L1_ARG_UNKNOWN
mdefine_line|#define L1_ARG_UNKNOWN&t;&t;0x80&t;/* unknown data type.  The low&n;&t;&t;&t;&t;&t; * 7 bits will contain the data&n;&t;&t;&t;&t;&t; * length.&t;&t;&t;*/
multiline_comment|/* response codes */
DECL|macro|L1_RESP_OK
mdefine_line|#define L1_RESP_OK&t;    0&t;/* no problems encountered      */
DECL|macro|L1_RESP_IROUTER
mdefine_line|#define L1_RESP_IROUTER&t;(-  1)&t;/* iRouter error&t;        */
DECL|macro|L1_RESP_ARGC
mdefine_line|#define L1_RESP_ARGC&t;(-100)&t;/* arg count mismatch&t;        */
DECL|macro|L1_RESP_REQC
mdefine_line|#define L1_RESP_REQC&t;(-101)&t;/* bad request code&t;        */
DECL|macro|L1_RESP_NAVAIL
mdefine_line|#define L1_RESP_NAVAIL&t;(-104)&t;/* requested data not available */
DECL|macro|L1_RESP_ARGVAL
mdefine_line|#define L1_RESP_ARGVAL&t;(-105)  /* arg value out of range       */
DECL|macro|L1_RESP_INVAL
mdefine_line|#define L1_RESP_INVAL   (-107)  /* requested data invalid       */
multiline_comment|/* L1 general requests */
multiline_comment|/* request codes */
DECL|macro|L1_REQ_RDBG
mdefine_line|#define&t;L1_REQ_RDBG&t;&t;0x0001&t;/* read debug switches&t;*/
DECL|macro|L1_REQ_RRACK
mdefine_line|#define L1_REQ_RRACK&t;&t;0x0002&t;/* read brick rack &amp; bay */
DECL|macro|L1_REQ_RRBT
mdefine_line|#define L1_REQ_RRBT&t;&t;0x0003  /* read brick rack, bay &amp; type */
DECL|macro|L1_REQ_SER_NUM
mdefine_line|#define L1_REQ_SER_NUM&t;&t;0x0004  /* read brick serial number */
DECL|macro|L1_REQ_FW_REV
mdefine_line|#define L1_REQ_FW_REV&t;&t;0x0005  /* read L1 firmware revision */
DECL|macro|L1_REQ_EEPROM
mdefine_line|#define L1_REQ_EEPROM&t;&t;0x0006  /* read EEPROM info */
DECL|macro|L1_REQ_EEPROM_FMT
mdefine_line|#define L1_REQ_EEPROM_FMT&t;0x0007  /* get EEPROM data format &amp; size */
DECL|macro|L1_REQ_SYS_SERIAL
mdefine_line|#define L1_REQ_SYS_SERIAL&t;0x0008&t;/* read system serial number */
DECL|macro|L1_REQ_PARTITION_GET
mdefine_line|#define L1_REQ_PARTITION_GET&t;0x0009&t;/* read partition id */
DECL|macro|L1_REQ_PORTSPEED
mdefine_line|#define L1_REQ_PORTSPEED&t;0x000a&t;/* get ioport speed */
DECL|macro|L1_REQ_CONS_SUBCH
mdefine_line|#define L1_REQ_CONS_SUBCH&t;0x1002  /* select this node&squot;s console &n;&t;&t;&t;&t;&t;   subchannel */
DECL|macro|L1_REQ_CONS_NODE
mdefine_line|#define L1_REQ_CONS_NODE&t;0x1003  /* volunteer to be the master &n;&t;&t;&t;&t;&t;   (console-hosting) node */
DECL|macro|L1_REQ_DISP1
mdefine_line|#define L1_REQ_DISP1&t;&t;0x1004  /* write line 1 of L1 display */
DECL|macro|L1_REQ_DISP2
mdefine_line|#define L1_REQ_DISP2&t;&t;0x1005  /* write line 2 of L1 display */
DECL|macro|L1_REQ_PARTITION_SET
mdefine_line|#define L1_REQ_PARTITION_SET&t;0x1006&t;/* set partition id */
DECL|macro|L1_REQ_EVENT_SUBCH
mdefine_line|#define L1_REQ_EVENT_SUBCH&t;0x1007&t;/* set the subchannel for system&n;&t;&t;&t;&t;&t;   controller event transmission */
DECL|macro|L1_REQ_RESET
mdefine_line|#define L1_REQ_RESET&t;&t;0x2000&t;/* request a full system reset */
DECL|macro|L1_REQ_PCI_UP
mdefine_line|#define L1_REQ_PCI_UP&t;&t;0x2001  /* power up pci slot or bus */
DECL|macro|L1_REQ_PCI_DOWN
mdefine_line|#define L1_REQ_PCI_DOWN&t;&t;0x2002  /* power down pci slot or bus */
DECL|macro|L1_REQ_PCI_RESET
mdefine_line|#define L1_REQ_PCI_RESET&t;0x2003  /* reset pci bus or slot */
multiline_comment|/* L1 command interpreter requests */
multiline_comment|/* request codes */
DECL|macro|L1_REQ_EXEC_CMD
mdefine_line|#define L1_REQ_EXEC_CMD&t;&t;0x0000&t;/* interpret and execute an ASCII&n;&t;&t;&t;&t;&t;   command string */
multiline_comment|/* brick type response codes */
DECL|macro|L1_BRICKTYPE_IP45
mdefine_line|#define L1_BRICKTYPE_IP45       0x34            /* 4 */
DECL|macro|L1_BRICKTYPE_C
mdefine_line|#define L1_BRICKTYPE_C          0x43            /* C */
DECL|macro|L1_BRICKTYPE_I
mdefine_line|#define L1_BRICKTYPE_I          0x49            /* I */
DECL|macro|L1_BRICKTYPE_P
mdefine_line|#define L1_BRICKTYPE_P          0x50            /* P */
DECL|macro|L1_BRICKTYPE_R
mdefine_line|#define L1_BRICKTYPE_R          0x52            /* R */
DECL|macro|L1_BRICKTYPE_X
mdefine_line|#define L1_BRICKTYPE_X          0x58            /* X */
DECL|macro|L1_BRICKTYPE_X2
mdefine_line|#define L1_BRICKTYPE_X2         0x59            /* Y */
DECL|macro|L1_BRICKTYPE_N
mdefine_line|#define L1_BRICKTYPE_N          0x4e            /* N */
DECL|macro|L1_BRICKTYPE_PE
mdefine_line|#define L1_BRICKTYPE_PE&t;&t;0x25&t;&t;/* % */
DECL|macro|L1_BRICKTYPE_PX
mdefine_line|#define L1_BRICKTYPE_PX&t;&t;0x23&t;&t;/* # */
DECL|macro|L1_BRICKTYPE_IX
mdefine_line|#define L1_BRICKTYPE_IX&t;&t;0x3d&t;&t;/* = */
multiline_comment|/* EEPROM codes (for the &quot;read EEPROM&quot; request) */
multiline_comment|/* c brick */
DECL|macro|L1_EEP_NODE
mdefine_line|#define L1_EEP_NODE&t;&t;0x00&t;/* node board */
DECL|macro|L1_EEP_PIMM0
mdefine_line|#define L1_EEP_PIMM0&t;&t;0x01
DECL|macro|L1_EEP_PIMM
mdefine_line|#define L1_EEP_PIMM(x)&t;&t;(L1_EEP_PIMM0+(x))
DECL|macro|L1_EEP_DIMM0
mdefine_line|#define L1_EEP_DIMM0&t;&t;0x03
DECL|macro|L1_EEP_DIMM
mdefine_line|#define L1_EEP_DIMM(x)&t;&t;(L1_EEP_DIMM0+(x))
multiline_comment|/* other brick types */
DECL|macro|L1_EEP_POWER
mdefine_line|#define L1_EEP_POWER&t;&t;0x00&t;/* power board */
DECL|macro|L1_EEP_LOGIC
mdefine_line|#define L1_EEP_LOGIC&t;&t;0x01&t;/* logic board */
multiline_comment|/* info area types */
DECL|macro|L1_EEP_CHASSIS
mdefine_line|#define L1_EEP_CHASSIS&t;&t;1&t;/* chassis info area */
DECL|macro|L1_EEP_BOARD
mdefine_line|#define L1_EEP_BOARD&t;&t;2&t;/* board info area */
DECL|macro|L1_EEP_IUSE
mdefine_line|#define L1_EEP_IUSE&t;&t;3&t;/* internal use area */
DECL|macro|L1_EEP_SPD
mdefine_line|#define L1_EEP_SPD&t;&t;4&t;/* serial presence detect record */
DECL|typedef|l1addr_t
r_typedef
r_uint32
id|l1addr_t
suffix:semicolon
DECL|macro|L1_BUILD_ADDR
mdefine_line|#define L1_BUILD_ADDR(addr,at,r,s,t)&t;&t;&t;&t;&t;&bslash;&n;    (*(l1addr_t *)(addr) = ((l1addr_t)(at) &lt;&lt; L1_ADDR_TYPE_SHFT) |&t;&bslash;&n;&t;&t;&t;     ((l1addr_t)(r)  &lt;&lt; L1_ADDR_RACK_SHFT) |&t;&bslash;&n;&t;&t;&t;     ((l1addr_t)(s)  &lt;&lt; L1_ADDR_BAY_SHFT) |&t;&bslash;&n;&t;&t;&t;     ((l1addr_t)(t)  &lt;&lt; L1_ADDR_TASK_SHFT))
DECL|macro|L1_ADDRESS_TO_TASK
mdefine_line|#define L1_ADDRESS_TO_TASK(addr,trb,tsk)&t;&t;&t;&t;&bslash;&n;    (*(l1addr_t *)(addr) = (l1addr_t)(trb) |&t;&t;&t;&t;&bslash;&n;    &t;&t;&t;     ((l1addr_t)(tsk) &lt;&lt; L1_ADDR_TASK_SHFT))
DECL|macro|L1_DISPLAY_LINE_LENGTH
mdefine_line|#define L1_DISPLAY_LINE_LENGTH&t;12&t;/* L1 display characters/line */
macro_line|#ifdef L1_DISP_2LINES
DECL|macro|L1_DISPLAY_LINES
mdefine_line|#define L1_DISPLAY_LINES&t;2&t;/* number of L1 display lines */
macro_line|#else
DECL|macro|L1_DISPLAY_LINES
mdefine_line|#define L1_DISPLAY_LINES&t;1&t;/* number of L1 display lines available&n;&t;&t;&t;&t;&t; * to system software */
macro_line|#endif
DECL|macro|bzero
mdefine_line|#define bzero(d, n)&t;memset((d), 0, (n))
r_int
id|elsc_display_line
c_func
(paren
id|nasid_t
id|nasid
comma
r_char
op_star
id|line
comma
r_int
id|lnum
)paren
suffix:semicolon
r_int
id|iobrick_rack_bay_type_get
c_func
(paren
id|nasid_t
id|nasid
comma
id|uint
op_star
id|rack
comma
id|uint
op_star
id|bay
comma
id|uint
op_star
id|brick_type
)paren
suffix:semicolon
r_int
id|iobrick_module_get
c_func
(paren
id|nasid_t
id|nasid
)paren
suffix:semicolon
macro_line|#endif /* _ASM_SN_KSYS_L1_H */
eof
