multiline_comment|/*&n; *  scsi_obsolete.h Copyright (C) 1997 Eric Youngdale&n; *&n; */
macro_line|#ifndef _SCSI_OBSOLETE_H
DECL|macro|_SCSI_OBSOLETE_H
mdefine_line|#define _SCSI_OBSOLETE_H
multiline_comment|/*&n; * These are the return codes for the abort and reset functions.  The mid-level&n; * code uses these to decide what to do next.  Each of the low level abort&n; * and reset functions must correctly indicate what it has done.&n; * The descriptions are written from the point of view of the mid-level code,&n; * so that the return code is telling the mid-level drivers exactly what&n; * the low level driver has already done, and what remains to be done.&n; */
multiline_comment|/* We did not do anything.  &n; * Wait some more for this command to complete, and if this does not work, &n; * try something more serious. */
DECL|macro|SCSI_ABORT_SNOOZE
mdefine_line|#define SCSI_ABORT_SNOOZE 0
multiline_comment|/* This means that we were able to abort the command.  We have already&n; * called the mid-level done function, and do not expect an interrupt that &n; * will lead to another call to the mid-level done function for this command */
DECL|macro|SCSI_ABORT_SUCCESS
mdefine_line|#define SCSI_ABORT_SUCCESS 1
multiline_comment|/* We called for an abort of this command, and we should get an interrupt &n; * when this succeeds.  Thus we should not restore the timer for this&n; * command in the mid-level abort function. */
DECL|macro|SCSI_ABORT_PENDING
mdefine_line|#define SCSI_ABORT_PENDING 2
multiline_comment|/* Unable to abort - command is currently on the bus.  Grin and bear it. */
DECL|macro|SCSI_ABORT_BUSY
mdefine_line|#define SCSI_ABORT_BUSY 3
multiline_comment|/* The command is not active in the low level code. Command probably&n; * finished. */
DECL|macro|SCSI_ABORT_NOT_RUNNING
mdefine_line|#define SCSI_ABORT_NOT_RUNNING 4
multiline_comment|/* Something went wrong.  The low level driver will indicate the correct&n; * error condition when it calls scsi_done, so the mid-level abort function&n; * can simply wait until this comes through */
DECL|macro|SCSI_ABORT_ERROR
mdefine_line|#define SCSI_ABORT_ERROR 5
multiline_comment|/* We do not know how to reset the bus, or we do not want to.  Bummer.&n; * Anyway, just wait a little more for the command in question, and hope that&n; * it eventually finishes.  If it never finishes, the SCSI device could&n; * hang, so use this with caution. */
DECL|macro|SCSI_RESET_SNOOZE
mdefine_line|#define SCSI_RESET_SNOOZE 0
multiline_comment|/* We do not know how to reset the bus, or we do not want to.  Bummer.&n; * We have given up on this ever completing.  The mid-level code will&n; * request sense information to decide how to proceed from here. */
DECL|macro|SCSI_RESET_PUNT
mdefine_line|#define SCSI_RESET_PUNT 1
multiline_comment|/* This means that we were able to reset the bus.  We have restarted all of&n; * the commands that should be restarted, and we should be able to continue&n; * on normally from here.  We do not expect any interrupts that will return&n; * DID_RESET to any of the other commands in the host_queue, and the mid-level&n; * code does not need to do anything special to keep the commands alive. &n; * If a hard reset was performed then all outstanding commands on the&n; * bus have been restarted. */
DECL|macro|SCSI_RESET_SUCCESS
mdefine_line|#define SCSI_RESET_SUCCESS 2
multiline_comment|/* We called for a reset of this bus, and we should get an interrupt &n; * when this succeeds.  Each command should get its own status&n; * passed up to scsi_done, but this has not happened yet. &n; * If a hard reset was performed, then we expect an interrupt&n; * for *each* of the outstanding commands that will have the&n; * effect of restarting the commands.&n; */
DECL|macro|SCSI_RESET_PENDING
mdefine_line|#define SCSI_RESET_PENDING 3
multiline_comment|/* We did a reset, but do not expect an interrupt to signal DID_RESET.&n; * This tells the upper level code to request the sense info, and this&n; * should keep the command alive. */
DECL|macro|SCSI_RESET_WAKEUP
mdefine_line|#define SCSI_RESET_WAKEUP 4
multiline_comment|/* The command is not active in the low level code. Command probably&n;   finished. */
DECL|macro|SCSI_RESET_NOT_RUNNING
mdefine_line|#define SCSI_RESET_NOT_RUNNING 5
multiline_comment|/* Something went wrong, and we do not know how to fix it. */
DECL|macro|SCSI_RESET_ERROR
mdefine_line|#define SCSI_RESET_ERROR 6
DECL|macro|SCSI_RESET_SYNCHRONOUS
mdefine_line|#define SCSI_RESET_SYNCHRONOUS&t;&t;0x01
DECL|macro|SCSI_RESET_ASYNCHRONOUS
mdefine_line|#define SCSI_RESET_ASYNCHRONOUS&t;&t;0x02
DECL|macro|SCSI_RESET_SUGGEST_BUS_RESET
mdefine_line|#define SCSI_RESET_SUGGEST_BUS_RESET&t;0x04
DECL|macro|SCSI_RESET_SUGGEST_HOST_RESET
mdefine_line|#define SCSI_RESET_SUGGEST_HOST_RESET&t;0x08
multiline_comment|/*&n; * This is a bitmask that is ored with one of the above codes.&n; * It tells the mid-level code that we did a hard reset.&n; */
DECL|macro|SCSI_RESET_BUS_RESET
mdefine_line|#define SCSI_RESET_BUS_RESET 0x100
multiline_comment|/*&n; * This is a bitmask that is ored with one of the above codes.&n; * It tells the mid-level code that we did a host adapter reset.&n; */
DECL|macro|SCSI_RESET_HOST_RESET
mdefine_line|#define SCSI_RESET_HOST_RESET 0x200
multiline_comment|/*&n; * Used to mask off bits and to obtain the basic action that was&n; * performed.  &n; */
DECL|macro|SCSI_RESET_ACTION
mdefine_line|#define SCSI_RESET_ACTION   0xff
macro_line|#endif&t;&t;&t;&t;/* SCSI_OBSOLETE_H */
eof
