multiline_comment|/******************************************************************************&n; *                  QLOGIC LINUX SOFTWARE&n; *&n; * QLogic ISP2x00 device driver for Linux 2.6.x&n; * Copyright (C) 2003 QLogic Corporation&n; * (www.qlogic.com)&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * Compile time Options:&n; *     0 - Disable and 1 - Enable&n; */
DECL|macro|DEBUG_QLA2100
mdefine_line|#define DEBUG_QLA2100&t;&t;0&t;/* For Debug of qla2x00 */
DECL|macro|MEMORY_MAPPED_IO
mdefine_line|#define MEMORY_MAPPED_IO&t;1
DECL|macro|STOP_ON_ERROR
mdefine_line|#define STOP_ON_ERROR&t;&t;0&t;/* Stop on aborts and resets  */
DECL|macro|STOP_ON_RESET
mdefine_line|#define STOP_ON_RESET&t;&t;0
DECL|macro|USE_ABORT_TGT
mdefine_line|#define USE_ABORT_TGT&t;&t;1&t;/* Use Abort Target mbx cmd */
DECL|macro|VSA
mdefine_line|#define VSA&t;&t;&t;0&t;/* Volume Set Addressing */
multiline_comment|/* Failover options */
DECL|macro|MAX_RECOVERYTIME
mdefine_line|#define MAX_RECOVERYTIME&t;10&t;/*&n;&t;&t;&t;&t;&t; * Max suspend time for a lun recovery&n;&t;&t;&t;&t;&t; * time&n;&t;&t;&t;&t;&t; */
DECL|macro|MAX_FAILBACKTIME
mdefine_line|#define MAX_FAILBACKTIME&t;5&t;/* Max suspend time before fail back */
DECL|macro|QLA_CMD_TIMER_DELTA
mdefine_line|#define QLA_CMD_TIMER_DELTA&t;3
multiline_comment|/* &n; * When a lun is suspended for the &quot;Not Ready&quot; condition then it will suspend&n; * the lun for increments of 6 sec delays.  SUSPEND_COUNT is that count.&n; */
DECL|macro|SUSPEND_COUNT
mdefine_line|#define SUSPEND_COUNT&t;&t;10&t;/* 6 secs * 10 retries = 60 secs */
multiline_comment|/*&n; * Defines the time in seconds that the driver extends the command timeout to&n; * get around the problem where the mid-layer only allows 5 retries for&n; * commands that return BUS_BUSY&n; */
DECL|macro|EXTEND_CMD_TIMEOUT
mdefine_line|#define EXTEND_CMD_TIMEOUT&t;60
DECL|macro|MAX_RETRIES_OF_ISP_ABORT
mdefine_line|#define MAX_RETRIES_OF_ISP_ABORT&t;5
multiline_comment|/* Max time to wait for the loop to be in LOOP_READY state */
DECL|macro|MAX_LOOP_TIMEOUT
mdefine_line|#define MAX_LOOP_TIMEOUT&t;(60 * 5)
DECL|macro|EH_ACTIVE
mdefine_line|#define EH_ACTIVE&t;&t;1&t;/* Error handler active */
multiline_comment|/*&n; * Some vendor subsystems do not recover properly after a device reset.  Define&n; * the following to force a logout after a successful device reset.&n; */
DECL|macro|LOGOUT_AFTER_DEVICE_RESET
macro_line|#undef LOGOUT_AFTER_DEVICE_RESET
macro_line|#include &quot;qla_version.h&quot;
eof
