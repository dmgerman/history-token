multiline_comment|/*******************************************************************************&n;*&n;*   (c) 1999 by Computone Corporation&n;*&n;********************************************************************************&n;*&n;*&n;*   PACKAGE:     Linux tty Device Driver for IntelliPort II family of multiport&n;*                serial I/O controllers.&n;*&n;*   DESCRIPTION: Definitions and support for In-line and Bypass commands.&n;*                Applicable only when the standard loadware is active.&n;*&n;*******************************************************************************/
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// Revision History:
singleline_comment|//
singleline_comment|// 10 October 1991   MAG First Draft
singleline_comment|//  7 November 1991  MAG Reflects some new commands
singleline_comment|// 20 February 1992  MAG CMD_HOTACK corrected: no argument.
singleline_comment|// 24 February 1992  MAG Support added for new commands for 1.4.x loadware.
singleline_comment|// 11 March 1992     MAG Additional commands.
singleline_comment|// 16 March 1992     MAG Additional commands.
singleline_comment|// 30 March 1992     MAG Additional command: CMD_DSS_NOW
singleline_comment|// 18 May   1992     MAG Changed CMD_OPOST
singleline_comment|//
singleline_comment|//------------------------------------------------------------------------------
macro_line|#ifndef I2CMD_H      
singleline_comment|// To prevent multiple includes
DECL|macro|I2CMD_H
mdefine_line|#define I2CMD_H   1
macro_line|#include &quot;ip2types.h&quot;
singleline_comment|// This module is designed to provide a uniform method of sending commands to
singleline_comment|// the board through command packets. The difficulty is, some commands take
singleline_comment|// parameters, others do not. Furthermore, it is often useful to send several
singleline_comment|// commands to the same channel as part of the same packet. (See also i2pack.h.)
singleline_comment|//
singleline_comment|// This module is designed so that the caller should not be responsible for
singleline_comment|// remembering the exact syntax of each command, or at least so that the
singleline_comment|// compiler could check things somewhat. I&squot;ll explain as we go...
singleline_comment|//
singleline_comment|// First, a structure which can embody the syntax of each type of command.
singleline_comment|//
DECL|struct|_cmdSyntax
r_typedef
r_struct
id|_cmdSyntax
(brace
DECL|member|length
id|UCHAR
id|length
suffix:semicolon
singleline_comment|// Number of bytes in the command
DECL|member|flags
id|UCHAR
id|flags
suffix:semicolon
singleline_comment|// Information about the command (see below)
singleline_comment|// The command and its parameters, which may be of arbitrary length. Don&squot;t
singleline_comment|// worry yet how the parameters will be initialized; macros later take care
singleline_comment|// of it. Also, don&squot;t worry about the arbitrary length issue; this structure
singleline_comment|// is never used to allocate space (see i2cmd.c).
DECL|member|cmd
id|UCHAR
id|cmd
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|cmdSyntax
DECL|typedef|cmdSyntaxPtr
)brace
id|cmdSyntax
comma
op_star
id|cmdSyntaxPtr
suffix:semicolon
singleline_comment|// Bit assignments for flags
DECL|macro|INL
mdefine_line|#define INL 1           
singleline_comment|// Set if suitable for inline commands
DECL|macro|BYP
mdefine_line|#define BYP 2           
singleline_comment|// Set if suitable for bypass commands
DECL|macro|BTH
mdefine_line|#define BTH (INL|BYP)   
singleline_comment|// suitable for either!
DECL|macro|END
mdefine_line|#define END 4           
singleline_comment|// Set if this must be the last command in a block
DECL|macro|VIP
mdefine_line|#define VIP 8           
singleline_comment|// Set if this command is special in some way and really
singleline_comment|// should only be sent from the library-level and not
singleline_comment|// directly from user-level
DECL|macro|VAR
mdefine_line|#define VAR 0x10        
singleline_comment|// This command is of variable length!
singleline_comment|//-----------------------------------
singleline_comment|// External declarations for i2cmd.c
singleline_comment|//-----------------------------------
singleline_comment|// Routine to set up parameters for the &quot;define hot-key sequence&quot; command. Since
singleline_comment|// there is more than one parameter to assign, we must use a function rather
singleline_comment|// than a macro (used usually).
singleline_comment|//
r_extern
id|cmdSyntaxPtr
id|i2cmdSetSeq
c_func
(paren
id|UCHAR
id|seqno
comma
id|UCHAR
id|size
comma
id|UCHAR
op_star
id|string
)paren
suffix:semicolon
r_extern
id|cmdSyntaxPtr
id|i2cmdUnixFlags
c_func
(paren
id|USHORT
id|iflag
comma
id|USHORT
id|cflag
comma
id|USHORT
id|lflag
)paren
suffix:semicolon
r_extern
id|cmdSyntaxPtr
id|i2cmdBaudRemap
c_func
(paren
id|UCHAR
id|dest
comma
id|UCHAR
id|src
)paren
suffix:semicolon
r_extern
id|cmdSyntaxPtr
id|i2cmdBaudDef
c_func
(paren
r_int
id|which
comma
id|USHORT
id|rate
)paren
suffix:semicolon
singleline_comment|// Declarations for the global arrays used to bear the commands and their
singleline_comment|// arguments.
singleline_comment|//
singleline_comment|// Note: Since these are globals and the arguments might change, it is important
singleline_comment|// that the library routine COPY these into buffers from whence they would be
singleline_comment|// sent, rather than merely storing the pointers. In multi-threaded
singleline_comment|// environments, important that the copy should obtain before any context switch
singleline_comment|// is allowed. Also, for parameterized commands, DO NOT ISSUE THE SAME COMMAND
singleline_comment|// MORE THAN ONCE WITH THE SAME PARAMETERS in the same call.
singleline_comment|//
DECL|variable|ct02
r_static
id|UCHAR
id|ct02
(braket
)braket
suffix:semicolon
DECL|variable|ct03
r_static
id|UCHAR
id|ct03
(braket
)braket
suffix:semicolon
DECL|variable|ct04
r_static
id|UCHAR
id|ct04
(braket
)braket
suffix:semicolon
DECL|variable|ct05
r_static
id|UCHAR
id|ct05
(braket
)braket
suffix:semicolon
DECL|variable|ct06
r_static
id|UCHAR
id|ct06
(braket
)braket
suffix:semicolon
DECL|variable|ct07
r_static
id|UCHAR
id|ct07
(braket
)braket
suffix:semicolon
DECL|variable|ct08
r_static
id|UCHAR
id|ct08
(braket
)braket
suffix:semicolon
DECL|variable|ct09
r_static
id|UCHAR
id|ct09
(braket
)braket
suffix:semicolon
DECL|variable|ct10
r_static
id|UCHAR
id|ct10
(braket
)braket
suffix:semicolon
DECL|variable|ct11
r_static
id|UCHAR
id|ct11
(braket
)braket
suffix:semicolon
DECL|variable|ct12
r_static
id|UCHAR
id|ct12
(braket
)braket
suffix:semicolon
DECL|variable|ct13
r_static
id|UCHAR
id|ct13
(braket
)braket
suffix:semicolon
DECL|variable|ct14
r_static
id|UCHAR
id|ct14
(braket
)braket
suffix:semicolon
DECL|variable|ct15
r_static
id|UCHAR
id|ct15
(braket
)braket
suffix:semicolon
DECL|variable|ct16
r_static
id|UCHAR
id|ct16
(braket
)braket
suffix:semicolon
DECL|variable|ct17
r_static
id|UCHAR
id|ct17
(braket
)braket
suffix:semicolon
DECL|variable|ct18
r_static
id|UCHAR
id|ct18
(braket
)braket
suffix:semicolon
DECL|variable|ct19
r_static
id|UCHAR
id|ct19
(braket
)braket
suffix:semicolon
DECL|variable|ct20
r_static
id|UCHAR
id|ct20
(braket
)braket
suffix:semicolon
DECL|variable|ct21
r_static
id|UCHAR
id|ct21
(braket
)braket
suffix:semicolon
DECL|variable|ct22
r_static
id|UCHAR
id|ct22
(braket
)braket
suffix:semicolon
DECL|variable|ct23
r_static
id|UCHAR
id|ct23
(braket
)braket
suffix:semicolon
DECL|variable|ct24
r_static
id|UCHAR
id|ct24
(braket
)braket
suffix:semicolon
DECL|variable|ct25
r_static
id|UCHAR
id|ct25
(braket
)braket
suffix:semicolon
DECL|variable|ct26
r_static
id|UCHAR
id|ct26
(braket
)braket
suffix:semicolon
DECL|variable|ct27
r_static
id|UCHAR
id|ct27
(braket
)braket
suffix:semicolon
DECL|variable|ct28
r_static
id|UCHAR
id|ct28
(braket
)braket
suffix:semicolon
DECL|variable|ct29
r_static
id|UCHAR
id|ct29
(braket
)braket
suffix:semicolon
DECL|variable|ct30
r_static
id|UCHAR
id|ct30
(braket
)braket
suffix:semicolon
DECL|variable|ct31
r_static
id|UCHAR
id|ct31
(braket
)braket
suffix:semicolon
DECL|variable|ct32
r_static
id|UCHAR
id|ct32
(braket
)braket
suffix:semicolon
DECL|variable|ct33
r_static
id|UCHAR
id|ct33
(braket
)braket
suffix:semicolon
DECL|variable|ct34
r_static
id|UCHAR
id|ct34
(braket
)braket
suffix:semicolon
DECL|variable|ct35
r_static
id|UCHAR
id|ct35
(braket
)braket
suffix:semicolon
DECL|variable|ct36
r_static
id|UCHAR
id|ct36
(braket
)braket
suffix:semicolon
DECL|variable|ct36a
r_static
id|UCHAR
id|ct36a
(braket
)braket
suffix:semicolon
DECL|variable|ct41
r_static
id|UCHAR
id|ct41
(braket
)braket
suffix:semicolon
DECL|variable|ct42
r_static
id|UCHAR
id|ct42
(braket
)braket
suffix:semicolon
DECL|variable|ct43
r_static
id|UCHAR
id|ct43
(braket
)braket
suffix:semicolon
DECL|variable|ct44
r_static
id|UCHAR
id|ct44
(braket
)braket
suffix:semicolon
DECL|variable|ct45
r_static
id|UCHAR
id|ct45
(braket
)braket
suffix:semicolon
DECL|variable|ct46
r_static
id|UCHAR
id|ct46
(braket
)braket
suffix:semicolon
DECL|variable|ct48
r_static
id|UCHAR
id|ct48
(braket
)braket
suffix:semicolon
DECL|variable|ct49
r_static
id|UCHAR
id|ct49
(braket
)braket
suffix:semicolon
DECL|variable|ct50
r_static
id|UCHAR
id|ct50
(braket
)braket
suffix:semicolon
DECL|variable|ct51
r_static
id|UCHAR
id|ct51
(braket
)braket
suffix:semicolon
DECL|variable|ct52
r_static
id|UCHAR
id|ct52
(braket
)braket
suffix:semicolon
DECL|variable|ct56
r_static
id|UCHAR
id|ct56
(braket
)braket
suffix:semicolon
DECL|variable|ct57
r_static
id|UCHAR
id|ct57
(braket
)braket
suffix:semicolon
DECL|variable|ct58
r_static
id|UCHAR
id|ct58
(braket
)braket
suffix:semicolon
DECL|variable|ct59
r_static
id|UCHAR
id|ct59
(braket
)braket
suffix:semicolon
DECL|variable|ct60
r_static
id|UCHAR
id|ct60
(braket
)braket
suffix:semicolon
DECL|variable|ct61
r_static
id|UCHAR
id|ct61
(braket
)braket
suffix:semicolon
DECL|variable|ct62
r_static
id|UCHAR
id|ct62
(braket
)braket
suffix:semicolon
DECL|variable|ct63
r_static
id|UCHAR
id|ct63
(braket
)braket
suffix:semicolon
DECL|variable|ct64
r_static
id|UCHAR
id|ct64
(braket
)braket
suffix:semicolon
DECL|variable|ct65
r_static
id|UCHAR
id|ct65
(braket
)braket
suffix:semicolon
DECL|variable|ct66
r_static
id|UCHAR
id|ct66
(braket
)braket
suffix:semicolon
DECL|variable|ct67
r_static
id|UCHAR
id|ct67
(braket
)braket
suffix:semicolon
DECL|variable|ct68
r_static
id|UCHAR
id|ct68
(braket
)braket
suffix:semicolon
DECL|variable|ct69
r_static
id|UCHAR
id|ct69
(braket
)braket
suffix:semicolon
DECL|variable|ct70
r_static
id|UCHAR
id|ct70
(braket
)braket
suffix:semicolon
DECL|variable|ct71
r_static
id|UCHAR
id|ct71
(braket
)braket
suffix:semicolon
DECL|variable|ct72
r_static
id|UCHAR
id|ct72
(braket
)braket
suffix:semicolon
DECL|variable|ct73
r_static
id|UCHAR
id|ct73
(braket
)braket
suffix:semicolon
DECL|variable|ct74
r_static
id|UCHAR
id|ct74
(braket
)braket
suffix:semicolon
DECL|variable|ct75
r_static
id|UCHAR
id|ct75
(braket
)braket
suffix:semicolon
DECL|variable|ct76
r_static
id|UCHAR
id|ct76
(braket
)braket
suffix:semicolon
DECL|variable|ct77
r_static
id|UCHAR
id|ct77
(braket
)braket
suffix:semicolon
DECL|variable|ct78
r_static
id|UCHAR
id|ct78
(braket
)braket
suffix:semicolon
DECL|variable|ct79
r_static
id|UCHAR
id|ct79
(braket
)braket
suffix:semicolon
DECL|variable|ct80
r_static
id|UCHAR
id|ct80
(braket
)braket
suffix:semicolon
DECL|variable|ct81
r_static
id|UCHAR
id|ct81
(braket
)braket
suffix:semicolon
DECL|variable|ct82
r_static
id|UCHAR
id|ct82
(braket
)braket
suffix:semicolon
DECL|variable|ct83
r_static
id|UCHAR
id|ct83
(braket
)braket
suffix:semicolon
DECL|variable|ct84
r_static
id|UCHAR
id|ct84
(braket
)braket
suffix:semicolon
DECL|variable|ct85
r_static
id|UCHAR
id|ct85
(braket
)braket
suffix:semicolon
DECL|variable|ct86
r_static
id|UCHAR
id|ct86
(braket
)braket
suffix:semicolon
DECL|variable|ct87
r_static
id|UCHAR
id|ct87
(braket
)braket
suffix:semicolon
DECL|variable|ct88
r_static
id|UCHAR
id|ct88
(braket
)braket
suffix:semicolon
DECL|variable|ct89
r_static
id|UCHAR
id|ct89
(braket
)braket
suffix:semicolon
DECL|variable|ct90
r_static
id|UCHAR
id|ct90
(braket
)braket
suffix:semicolon
DECL|variable|ct91
r_static
id|UCHAR
id|ct91
(braket
)braket
suffix:semicolon
DECL|variable|cc01
r_static
id|UCHAR
id|cc01
(braket
)braket
suffix:semicolon
DECL|variable|cc02
r_static
id|UCHAR
id|cc02
(braket
)braket
suffix:semicolon
singleline_comment|// Now, refer to i2cmd.c, and see the character arrays defined there. They are
singleline_comment|// cast here to cmdSyntaxPtr.
singleline_comment|//
singleline_comment|// There are library functions for issuing bypass or inline commands. These
singleline_comment|// functions take one or more arguments of the type cmdSyntaxPtr. The routine
singleline_comment|// then can figure out how long each command is supposed to be and easily add it
singleline_comment|// to the list.
singleline_comment|//
singleline_comment|// For ease of use, we define manifests which return pointers to appropriate
singleline_comment|// cmdSyntaxPtr things. But some commands also take arguments. If a single
singleline_comment|// argument is used, we define a macro which performs the single assignment and
singleline_comment|// (through the expedient of a comma expression) references the appropriate
singleline_comment|// pointer. For commands requiring several arguments, we actually define a
singleline_comment|// function to perform the assignments.
DECL|macro|CMD_DTRUP
mdefine_line|#define CMD_DTRUP&t;(cmdSyntaxPtr)(ct02)&t;
singleline_comment|// Raise DTR
DECL|macro|CMD_DTRDN
mdefine_line|#define CMD_DTRDN&t;(cmdSyntaxPtr)(ct03)&t;
singleline_comment|// Lower DTR
DECL|macro|CMD_RTSUP
mdefine_line|#define CMD_RTSUP&t;(cmdSyntaxPtr)(ct04)&t;
singleline_comment|// Raise RTS
DECL|macro|CMD_RTSDN
mdefine_line|#define CMD_RTSDN&t;(cmdSyntaxPtr)(ct05)&t;
singleline_comment|// Lower RTS
DECL|macro|CMD_STARTFL
mdefine_line|#define CMD_STARTFL&t;(cmdSyntaxPtr)(ct06)&t;
singleline_comment|// Start Flushing Data
DECL|macro|CMD_DTRRTS_UP
mdefine_line|#define CMD_DTRRTS_UP (cmdSyntaxPtr)(cc01)&t;
singleline_comment|// Raise DTR and RTS
DECL|macro|CMD_DTRRTS_DN
mdefine_line|#define CMD_DTRRTS_DN (cmdSyntaxPtr)(cc02)&t;
singleline_comment|// Lower DTR and RTS
singleline_comment|// Set Baud Rate for transmit and receive
DECL|macro|CMD_SETBAUD
mdefine_line|#define CMD_SETBAUD(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct07))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct07))
DECL|macro|CBR_50
mdefine_line|#define CBR_50       1
DECL|macro|CBR_75
mdefine_line|#define CBR_75       2
DECL|macro|CBR_110
mdefine_line|#define CBR_110      3
DECL|macro|CBR_134
mdefine_line|#define CBR_134      4
DECL|macro|CBR_150
mdefine_line|#define CBR_150      5
DECL|macro|CBR_200
mdefine_line|#define CBR_200      6
DECL|macro|CBR_300
mdefine_line|#define CBR_300      7
DECL|macro|CBR_600
mdefine_line|#define CBR_600      8
DECL|macro|CBR_1200
mdefine_line|#define CBR_1200     9
DECL|macro|CBR_1800
mdefine_line|#define CBR_1800     10
DECL|macro|CBR_2400
mdefine_line|#define CBR_2400     11
DECL|macro|CBR_4800
mdefine_line|#define CBR_4800     12
DECL|macro|CBR_9600
mdefine_line|#define CBR_9600     13
DECL|macro|CBR_19200
mdefine_line|#define CBR_19200    14
DECL|macro|CBR_38400
mdefine_line|#define CBR_38400    15
DECL|macro|CBR_2000
mdefine_line|#define CBR_2000     16
DECL|macro|CBR_3600
mdefine_line|#define CBR_3600     17
DECL|macro|CBR_7200
mdefine_line|#define CBR_7200     18
DECL|macro|CBR_56000
mdefine_line|#define CBR_56000    19
DECL|macro|CBR_57600
mdefine_line|#define CBR_57600    20
DECL|macro|CBR_64000
mdefine_line|#define CBR_64000    21
DECL|macro|CBR_76800
mdefine_line|#define CBR_76800    22
DECL|macro|CBR_115200
mdefine_line|#define CBR_115200   23
DECL|macro|CBR_C1
mdefine_line|#define CBR_C1       24    
singleline_comment|// Custom baud rate 1
DECL|macro|CBR_C2
mdefine_line|#define CBR_C2       25    
singleline_comment|// Custom baud rate 2
DECL|macro|CBR_153600
mdefine_line|#define CBR_153600   26
DECL|macro|CBR_230400
mdefine_line|#define CBR_230400   27
DECL|macro|CBR_307200
mdefine_line|#define CBR_307200   28
DECL|macro|CBR_460800
mdefine_line|#define CBR_460800   29
DECL|macro|CBR_921600
mdefine_line|#define CBR_921600   30
singleline_comment|// Set Character size
singleline_comment|//
DECL|macro|CMD_SETBITS
mdefine_line|#define CMD_SETBITS(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct08))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct08))
DECL|macro|CSZ_5
mdefine_line|#define CSZ_5  0
DECL|macro|CSZ_6
mdefine_line|#define CSZ_6  1
DECL|macro|CSZ_7
mdefine_line|#define CSZ_7  2
DECL|macro|CSZ_8
mdefine_line|#define CSZ_8  3
singleline_comment|// Set number of stop bits
singleline_comment|//
DECL|macro|CMD_SETSTOP
mdefine_line|#define CMD_SETSTOP(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct09))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct09))
DECL|macro|CST_1
mdefine_line|#define CST_1  0
DECL|macro|CST_15
mdefine_line|#define CST_15 1  
singleline_comment|// 1.5 stop bits
DECL|macro|CST_2
mdefine_line|#define CST_2  2
singleline_comment|// Set parity option
singleline_comment|//
DECL|macro|CMD_SETPAR
mdefine_line|#define CMD_SETPAR(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct10))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct10))
DECL|macro|CSP_NP
mdefine_line|#define CSP_NP 0  
singleline_comment|// no parity
DECL|macro|CSP_OD
mdefine_line|#define CSP_OD 1  
singleline_comment|// odd parity
DECL|macro|CSP_EV
mdefine_line|#define CSP_EV 2  
singleline_comment|// Even parity
DECL|macro|CSP_SP
mdefine_line|#define CSP_SP 3  
singleline_comment|// Space parity
DECL|macro|CSP_MK
mdefine_line|#define CSP_MK 4  
singleline_comment|// Mark parity
singleline_comment|// Define xon char for transmitter flow control
singleline_comment|//
DECL|macro|CMD_DEF_IXON
mdefine_line|#define CMD_DEF_IXON(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct11))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct11))
singleline_comment|// Define xoff char for transmitter flow control
singleline_comment|//
DECL|macro|CMD_DEF_IXOFF
mdefine_line|#define CMD_DEF_IXOFF(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct12))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct12))
DECL|macro|CMD_STOPFL
mdefine_line|#define CMD_STOPFL   (cmdSyntaxPtr)(ct13) 
singleline_comment|// Stop Flushing data
singleline_comment|// Acknowledge receipt of hotkey signal
singleline_comment|//
DECL|macro|CMD_HOTACK
mdefine_line|#define CMD_HOTACK   (cmdSyntaxPtr)(ct14)
singleline_comment|// Define irq level to use. Should actually be sent by library-level code, not
singleline_comment|// directly from user...
singleline_comment|//
DECL|macro|CMDVALUE_IRQ
mdefine_line|#define CMDVALUE_IRQ 15 
singleline_comment|// For library use at initialization. Until this command
singleline_comment|// is sent, board processing doesn&squot;t really start.
DECL|macro|CMD_SET_IRQ
mdefine_line|#define CMD_SET_IRQ(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct15))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct15))
DECL|macro|CIR_POLL
mdefine_line|#define CIR_POLL  0  
singleline_comment|// No IRQ - Poll
DECL|macro|CIR_3
mdefine_line|#define CIR_3     3  
singleline_comment|// IRQ 3
DECL|macro|CIR_4
mdefine_line|#define CIR_4     4  
singleline_comment|// IRQ 4
DECL|macro|CIR_5
mdefine_line|#define CIR_5     5  
singleline_comment|// IRQ 5
DECL|macro|CIR_7
mdefine_line|#define CIR_7     7  
singleline_comment|// IRQ 7
DECL|macro|CIR_10
mdefine_line|#define CIR_10    10 
singleline_comment|// IRQ 10
DECL|macro|CIR_11
mdefine_line|#define CIR_11    11 
singleline_comment|// IRQ 11
DECL|macro|CIR_12
mdefine_line|#define CIR_12    12 
singleline_comment|// IRQ 12
DECL|macro|CIR_15
mdefine_line|#define CIR_15    15 
singleline_comment|// IRQ 15
singleline_comment|// Select transmit flow xon/xoff options
singleline_comment|//
DECL|macro|CMD_IXON_OPT
mdefine_line|#define CMD_IXON_OPT(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct16))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct16))
DECL|macro|CIX_NONE
mdefine_line|#define CIX_NONE  0  
singleline_comment|// Incoming Xon/Xoff characters not special
DECL|macro|CIX_XON
mdefine_line|#define CIX_XON   1  
singleline_comment|// Xoff disable, Xon enable
DECL|macro|CIX_XANY
mdefine_line|#define CIX_XANY  2  
singleline_comment|// Xoff disable, any key enable
singleline_comment|// Select receive flow xon/xoff options
singleline_comment|//
DECL|macro|CMD_OXON_OPT
mdefine_line|#define CMD_OXON_OPT(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct17))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct17))
DECL|macro|COX_NONE
mdefine_line|#define COX_NONE  0  
singleline_comment|// Don&squot;t send Xon/Xoff
DECL|macro|COX_XON
mdefine_line|#define COX_XON   1  
singleline_comment|// Send xon/xoff to start/stop incoming data
DECL|macro|CMD_CTS_REP
mdefine_line|#define CMD_CTS_REP  (cmdSyntaxPtr)(ct18) 
singleline_comment|// Enable  CTS reporting
DECL|macro|CMD_CTS_NREP
mdefine_line|#define CMD_CTS_NREP (cmdSyntaxPtr)(ct19) 
singleline_comment|// Disable CTS reporting
DECL|macro|CMD_DCD_REP
mdefine_line|#define CMD_DCD_REP  (cmdSyntaxPtr)(ct20) 
singleline_comment|// Enable  DCD reporting
DECL|macro|CMD_DCD_NREP
mdefine_line|#define CMD_DCD_NREP (cmdSyntaxPtr)(ct21) 
singleline_comment|// Disable DCD reporting
DECL|macro|CMD_DSR_REP
mdefine_line|#define CMD_DSR_REP  (cmdSyntaxPtr)(ct22) 
singleline_comment|// Enable  DSR reporting
DECL|macro|CMD_DSR_NREP
mdefine_line|#define CMD_DSR_NREP (cmdSyntaxPtr)(ct23) 
singleline_comment|// Disable DSR reporting
DECL|macro|CMD_RI_REP
mdefine_line|#define CMD_RI_REP   (cmdSyntaxPtr)(ct24) 
singleline_comment|// Enable  RI  reporting
DECL|macro|CMD_RI_NREP
mdefine_line|#define CMD_RI_NREP  (cmdSyntaxPtr)(ct25) 
singleline_comment|// Disable RI  reporting
singleline_comment|// Enable break reporting and select style
singleline_comment|//
DECL|macro|CMD_BRK_REP
mdefine_line|#define CMD_BRK_REP(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct26))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct26))
DECL|macro|CBK_STAT
mdefine_line|#define CBK_STAT     0x00  
singleline_comment|// Report breaks as a status (exception,irq)
DECL|macro|CBK_NULL
mdefine_line|#define CBK_NULL     0x01  
singleline_comment|// Report breaks as a good null
DECL|macro|CBK_STAT_SEQ
mdefine_line|#define CBK_STAT_SEQ 0x02  
singleline_comment|// Report breaks as a status AND as in-band character
singleline_comment|//  sequence FFh, 01h, 10h
DECL|macro|CBK_SEQ
mdefine_line|#define CBK_SEQ      0x03  
singleline_comment|// Report breaks as the in-band 
singleline_comment|//sequence FFh, 01h, 10h ONLY.
DECL|macro|CBK_FLSH
mdefine_line|#define CBK_FLSH     0x04  
singleline_comment|// if this bit set also flush input data
DECL|macro|CBK_POSIX
mdefine_line|#define CBK_POSIX    0x08  
singleline_comment|// if this bit set report as FF,0,0 sequence
DECL|macro|CBK_SINGLE
mdefine_line|#define CBK_SINGLE   0x10  
singleline_comment|// if this bit set with CBK_SEQ or CBK_STAT_SEQ
singleline_comment|//then reports single null instead of triple
DECL|macro|CMD_BRK_NREP
mdefine_line|#define CMD_BRK_NREP (cmdSyntaxPtr)(ct27) 
singleline_comment|// Disable break reporting
singleline_comment|// Specify maximum block size for received data
singleline_comment|//
DECL|macro|CMD_MAX_BLOCK
mdefine_line|#define CMD_MAX_BLOCK(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct28))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct28))
singleline_comment|// -- COMMAND 29 is reserved --
DECL|macro|CMD_CTSFL_ENAB
mdefine_line|#define CMD_CTSFL_ENAB  (cmdSyntaxPtr)(ct30) 
singleline_comment|// Enable  CTS flow control
DECL|macro|CMD_CTSFL_DSAB
mdefine_line|#define CMD_CTSFL_DSAB  (cmdSyntaxPtr)(ct31) 
singleline_comment|// Disable CTS flow control
DECL|macro|CMD_RTSFL_ENAB
mdefine_line|#define CMD_RTSFL_ENAB  (cmdSyntaxPtr)(ct32) 
singleline_comment|// Enable  RTS flow control
DECL|macro|CMD_RTSFL_DSAB
mdefine_line|#define CMD_RTSFL_DSAB  (cmdSyntaxPtr)(ct33) 
singleline_comment|// Disable RTS flow control
singleline_comment|// Specify istrip option
singleline_comment|//
DECL|macro|CMD_ISTRIP_OPT
mdefine_line|#define CMD_ISTRIP_OPT(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct34))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct34))
DECL|macro|CIS_NOSTRIP
mdefine_line|#define CIS_NOSTRIP  0  
singleline_comment|// Strip characters to character size
DECL|macro|CIS_STRIP
mdefine_line|#define CIS_STRIP    1  
singleline_comment|// Strip any 8-bit characters to 7 bits
singleline_comment|// Send a break of arg milliseconds
singleline_comment|//
DECL|macro|CMD_SEND_BRK
mdefine_line|#define CMD_SEND_BRK(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct35))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct35))
singleline_comment|// Set error reporting mode
singleline_comment|//
DECL|macro|CMD_SET_ERROR
mdefine_line|#define CMD_SET_ERROR(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct36))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct36))
DECL|macro|CSE_ESTAT
mdefine_line|#define CSE_ESTAT 0  
singleline_comment|// Report error in a status packet
DECL|macro|CSE_NOREP
mdefine_line|#define CSE_NOREP 1  
singleline_comment|// Treat character as though it were good
DECL|macro|CSE_DROP
mdefine_line|#define CSE_DROP  2  
singleline_comment|// Discard the character
DECL|macro|CSE_NULL
mdefine_line|#define CSE_NULL  3  
singleline_comment|// Replace with a null
DECL|macro|CSE_MARK
mdefine_line|#define CSE_MARK  4  
singleline_comment|// Replace with a 3-character sequence (as Unix)
DECL|macro|CMD_SET_REPLACEMENT
mdefine_line|#define  CMD_SET_REPLACEMENT(arg,ch)   &bslash;&n;&t;&t;&t;(((cmdSyntaxPtr)(ct36a))-&gt;cmd[1] = (arg), &bslash;&n;&t;&t;&t;(((cmdSyntaxPtr)(ct36a))-&gt;cmd[2] = (ch),  &bslash;&n;&t;&t;&t;(cmdSyntaxPtr)(ct36a))
DECL|macro|CSE_REPLACE
mdefine_line|#define CSE_REPLACE  0x8&t;
singleline_comment|// Replace the errored character with the
singleline_comment|// replacement character defined here
DECL|macro|CSE_STAT_REPLACE
mdefine_line|#define CSE_STAT_REPLACE   0x18&t;
singleline_comment|// Replace the errored character with the
singleline_comment|// replacement character defined here AND
singleline_comment|// report the error as a status packet (as in
singleline_comment|// CSE_ESTAT).
singleline_comment|// COMMAND 37, to send flow control packets, is handled only by low-level
singleline_comment|// library code in response to data movement and shouldn&squot;t ever be sent by the
singleline_comment|// user code. See i2pack.h and the body of i2lib.c for details.
singleline_comment|// COMMAND 38: Define the hot-key sequence
singleline_comment|// seqno:  sequence number 0-15
singleline_comment|// size:   number of characters in sequence (1-8)
singleline_comment|// string: pointer to the characters
singleline_comment|// (if size == 0, &quot;undefines&quot; this sequence
singleline_comment|//
DECL|macro|CMD_SET_SEQ
mdefine_line|#define CMD_SET_SEQ(seqno,size,string) i2cmdSetSeq(seqno,size,string)
singleline_comment|// Enable on-board post-processing, using options given in oflag argument.
singleline_comment|// Formerly, this command was automatically preceded by a CMD_OPOST_OFF command
singleline_comment|// because the loadware does not permit sending back-to-back CMD_OPOST_ON
singleline_comment|// commands without an intervening CMD_OPOST_OFF. BUT, WE LEARN 18 MAY 92, that
singleline_comment|// CMD_OPOST_ON and CMD_OPOST_OFF must each be at the end of a packet (or in a
singleline_comment|// solo packet). This means the caller must specify separately CMD_OPOST_OFF,
singleline_comment|// CMD_OPOST_ON(parm) when he calls i2QueueCommands(). That function will ensure
singleline_comment|// each gets a separate packet. Extra CMD_OPOST_OFF&squot;s are always ok.
singleline_comment|//
DECL|macro|CMD_OPOST_ON
mdefine_line|#define CMD_OPOST_ON(oflag)   &bslash;&n;&t;(*(USHORT *)(((cmdSyntaxPtr)(ct39))-&gt;cmd[1]) = (oflag), &bslash;&n;&t;&t;(cmdSyntaxPtr)(ct39))
DECL|macro|CMD_OPOST_OFF
mdefine_line|#define CMD_OPOST_OFF   (cmdSyntaxPtr)(ct40) 
singleline_comment|// Disable on-board post-proc
DECL|macro|CMD_RESUME
mdefine_line|#define CMD_RESUME   (cmdSyntaxPtr)(ct41)&t;
singleline_comment|// Resume: behave as though an XON
singleline_comment|// were received;
singleline_comment|// Set Transmit baud rate (see command 7 for arguments)
singleline_comment|//
DECL|macro|CMD_SETBAUD_TX
mdefine_line|#define CMD_SETBAUD_TX(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct42))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct42))
singleline_comment|// Set Receive baud rate (see command 7 for arguments)
singleline_comment|//
DECL|macro|CMD_SETBAUD_RX
mdefine_line|#define CMD_SETBAUD_RX(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct43))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct43))
singleline_comment|// Request interrupt from board each arg milliseconds. Interrupt will specify
singleline_comment|// &quot;received data&quot;, even though there may be no data present. If arg == 0,
singleline_comment|// disables any such interrupts.
singleline_comment|//
DECL|macro|CMD_PING_REQ
mdefine_line|#define CMD_PING_REQ(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct44))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct44))
DECL|macro|CMD_HOT_ENAB
mdefine_line|#define CMD_HOT_ENAB (cmdSyntaxPtr)(ct45) 
singleline_comment|// Enable Hot-key checking
DECL|macro|CMD_HOT_DSAB
mdefine_line|#define CMD_HOT_DSAB (cmdSyntaxPtr)(ct46) 
singleline_comment|// Disable Hot-key checking
singleline_comment|// COMMAND 47: Send Protocol info via Unix flags:
singleline_comment|// iflag = Unix tty t_iflag
singleline_comment|// cflag = Unix tty t_cflag
singleline_comment|// lflag = Unix tty t_lflag
singleline_comment|// See System V Unix/Xenix documentation for the meanings of the bit fields
singleline_comment|// within these flags
singleline_comment|//
DECL|macro|CMD_UNIX_FLAGS
mdefine_line|#define CMD_UNIX_FLAGS(iflag,cflag,lflag) i2cmdUnixFlags(iflag,cflag,lflag)
DECL|macro|CMD_DSRFL_ENAB
mdefine_line|#define CMD_DSRFL_ENAB  (cmdSyntaxPtr)(ct48) 
singleline_comment|// Enable  DSR receiver ctrl
DECL|macro|CMD_DSRFL_DSAB
mdefine_line|#define CMD_DSRFL_DSAB  (cmdSyntaxPtr)(ct49) 
singleline_comment|// Disable DSR receiver ctrl
DECL|macro|CMD_DTRFL_ENAB
mdefine_line|#define CMD_DTRFL_ENAB  (cmdSyntaxPtr)(ct50) 
singleline_comment|// Enable  DTR flow control
DECL|macro|CMD_DTRFL_DSAB
mdefine_line|#define CMD_DTRFL_DSAB  (cmdSyntaxPtr)(ct51) 
singleline_comment|// Disable DTR flow control
DECL|macro|CMD_BAUD_RESET
mdefine_line|#define CMD_BAUD_RESET  (cmdSyntaxPtr)(ct52) 
singleline_comment|// Reset baudrate table
singleline_comment|// COMMAND 53: Remap baud rate table
singleline_comment|// dest = index of table entry to be changed
singleline_comment|// src  = index value to substitute.
singleline_comment|// at default mapping table is f(x) = x
singleline_comment|//
DECL|macro|CMD_BAUD_REMAP
mdefine_line|#define CMD_BAUD_REMAP(dest,src) i2cmdBaudRemap(dest,src)
singleline_comment|// COMMAND 54: Define custom rate #1
singleline_comment|// rate = (short) 1/10 of the desired baud rate
singleline_comment|//
DECL|macro|CMD_BAUD_DEF1
mdefine_line|#define CMD_BAUD_DEF1(rate) i2cmdBaudDef(1,rate)
singleline_comment|// COMMAND 55: Define custom rate #2
singleline_comment|// rate = (short) 1/10 of the desired baud rate
singleline_comment|//
DECL|macro|CMD_BAUD_DEF2
mdefine_line|#define CMD_BAUD_DEF2(rate) i2cmdBaudDef(2,rate)
singleline_comment|// Pause arg hundredths of seconds. (Note, this is NOT milliseconds.)
singleline_comment|//
DECL|macro|CMD_PAUSE
mdefine_line|#define CMD_PAUSE(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct56))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct56))
DECL|macro|CMD_SUSPEND
mdefine_line|#define CMD_SUSPEND     (cmdSyntaxPtr)(ct57) 
singleline_comment|// Suspend output
DECL|macro|CMD_UNSUSPEND
mdefine_line|#define CMD_UNSUSPEND   (cmdSyntaxPtr)(ct58) 
singleline_comment|// Un-Suspend output
singleline_comment|// Set parity-checking options
singleline_comment|//
DECL|macro|CMD_PARCHK
mdefine_line|#define CMD_PARCHK(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct59))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct59))
DECL|macro|CPK_ENAB
mdefine_line|#define CPK_ENAB  0     
singleline_comment|// Enable parity checking on input
DECL|macro|CPK_DSAB
mdefine_line|#define CPK_DSAB  1     
singleline_comment|// Disable parity checking on input
DECL|macro|CMD_BMARK_REQ
mdefine_line|#define CMD_BMARK_REQ   (cmdSyntaxPtr)(ct60) 
singleline_comment|// Bookmark request
singleline_comment|// Enable/Disable internal loopback mode
singleline_comment|//
DECL|macro|CMD_INLOOP
mdefine_line|#define CMD_INLOOP(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct61))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct61))
DECL|macro|CIN_DISABLE
mdefine_line|#define CIN_DISABLE  0  
singleline_comment|// Normal operation (default)
DECL|macro|CIN_ENABLE
mdefine_line|#define CIN_ENABLE   1  
singleline_comment|// Internal (local) loopback
DECL|macro|CIN_REMOTE
mdefine_line|#define CIN_REMOTE   2  
singleline_comment|// Remote loopback
singleline_comment|// Specify timeout for hotkeys: Delay will be (arg x 10) milliseconds, arg == 0
singleline_comment|// --&gt; no timeout: wait forever.
singleline_comment|//
DECL|macro|CMD_HOT_TIME
mdefine_line|#define CMD_HOT_TIME(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct62))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct62))
singleline_comment|// Define (outgoing) xon for receive flow control
singleline_comment|//
DECL|macro|CMD_DEF_OXON
mdefine_line|#define CMD_DEF_OXON(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct63))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct63))
singleline_comment|// Define (outgoing) xoff for receiver flow control
singleline_comment|//
DECL|macro|CMD_DEF_OXOFF
mdefine_line|#define CMD_DEF_OXOFF(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct64))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct64))
singleline_comment|// Enable/Disable RTS on transmit (1/2 duplex-style)
singleline_comment|//
DECL|macro|CMD_RTS_XMIT
mdefine_line|#define CMD_RTS_XMIT(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct65))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct65))
DECL|macro|CHD_DISABLE
mdefine_line|#define CHD_DISABLE  0
DECL|macro|CHD_ENABLE
mdefine_line|#define CHD_ENABLE   1
singleline_comment|// Set high-water-mark level (debugging use only)
singleline_comment|//
DECL|macro|CMD_SETHIGHWAT
mdefine_line|#define CMD_SETHIGHWAT(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct66))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct66))
singleline_comment|// Start flushing tagged data (tag = 0-14)
singleline_comment|//
DECL|macro|CMD_START_SELFL
mdefine_line|#define CMD_START_SELFL(tag) &bslash;&n;&t;(((cmdSyntaxPtr)(ct67))-&gt;cmd[1] = (tag),(cmdSyntaxPtr)(ct67))
singleline_comment|// End flushing tagged data (tag = 0-14)
singleline_comment|//
DECL|macro|CMD_END_SELFL
mdefine_line|#define CMD_END_SELFL(tag) &bslash;&n;&t;(((cmdSyntaxPtr)(ct68))-&gt;cmd[1] = (tag),(cmdSyntaxPtr)(ct68))
DECL|macro|CMD_HWFLOW_OFF
mdefine_line|#define CMD_HWFLOW_OFF  (cmdSyntaxPtr)(ct69) 
singleline_comment|// Disable HW TX flow control
DECL|macro|CMD_ODSRFL_ENAB
mdefine_line|#define CMD_ODSRFL_ENAB (cmdSyntaxPtr)(ct70) 
singleline_comment|// Enable DSR output f/c
DECL|macro|CMD_ODSRFL_DSAB
mdefine_line|#define CMD_ODSRFL_DSAB (cmdSyntaxPtr)(ct71) 
singleline_comment|// Disable DSR output f/c
DECL|macro|CMD_ODCDFL_ENAB
mdefine_line|#define CMD_ODCDFL_ENAB (cmdSyntaxPtr)(ct72) 
singleline_comment|// Enable DCD output f/c
DECL|macro|CMD_ODCDFL_DSAB
mdefine_line|#define CMD_ODCDFL_DSAB (cmdSyntaxPtr)(ct73) 
singleline_comment|// Disable DCD output f/c
singleline_comment|// Set transmit interrupt load level. Count should be an even value 2-12
singleline_comment|//
DECL|macro|CMD_LOADLEVEL
mdefine_line|#define CMD_LOADLEVEL(count) &bslash;&n;&t;(((cmdSyntaxPtr)(ct74))-&gt;cmd[1] = (count),(cmdSyntaxPtr)(ct74))
singleline_comment|// If reporting DSS changes, map to character sequence FFh, 2, MSR
singleline_comment|//
DECL|macro|CMD_STATDATA
mdefine_line|#define CMD_STATDATA(arg) &bslash;&n;&t;(((cmdSyntaxPtr)(ct75))-&gt;cmd[1] = (arg),(cmdSyntaxPtr)(ct75))
DECL|macro|CSTD_DISABLE
mdefine_line|#define CSTD_DISABLE
singleline_comment|// Report DSS changes as status packets only (default)
DECL|macro|CSTD_ENABLE
mdefine_line|#define CSTD_ENABLE&t;
singleline_comment|// Report DSS changes as in-band data sequence as well as
singleline_comment|// by status packet.
DECL|macro|CMD_BREAK_ON
mdefine_line|#define CMD_BREAK_ON    (cmdSyntaxPtr)(ct76)
singleline_comment|// Set break and stop xmit
DECL|macro|CMD_BREAK_OFF
mdefine_line|#define CMD_BREAK_OFF   (cmdSyntaxPtr)(ct77)
singleline_comment|// End break and restart xmit
DECL|macro|CMD_GETFC
mdefine_line|#define CMD_GETFC       (cmdSyntaxPtr)(ct78)
singleline_comment|// Request for flow control packet
singleline_comment|// from board.
singleline_comment|// Transmit this character immediately
singleline_comment|//
DECL|macro|CMD_XMIT_NOW
mdefine_line|#define CMD_XMIT_NOW(ch) &bslash;&n;&t;(((cmdSyntaxPtr)(ct79))-&gt;cmd[1] = (ch),(cmdSyntaxPtr)(ct79))
singleline_comment|// Set baud rate via &quot;divisor latch&quot;
singleline_comment|//
DECL|macro|CMD_DIVISOR_LATCH
mdefine_line|#define CMD_DIVISOR_LATCH(which,value) &bslash;&n;&t;&t;&t;(((cmdSyntaxPtr)(ct80))-&gt;cmd[1] = (which), &bslash;&n;&t;&t;&t;*(USHORT *)(((cmdSyntaxPtr)(ct80))-&gt;cmd[2]) = (value), &bslash;&n;&t;&t;&t;(cmdSyntaxPtr)(ct80))
DECL|macro|CDL_RX
mdefine_line|#define CDL_RX 1&t;
singleline_comment|// Set receiver rate
DECL|macro|CDL_TX
mdefine_line|#define CDL_TX 2&t;
singleline_comment|// Set transmit rate
singleline_comment|// (CDL_TX | CDL_RX) Set both rates
singleline_comment|// Request for special diagnostic status pkt from the board.
singleline_comment|//
DECL|macro|CMD_GET_STATUS
mdefine_line|#define CMD_GET_STATUS (cmdSyntaxPtr)(ct81)
singleline_comment|// Request time-stamped transmit character count packet.
singleline_comment|//
DECL|macro|CMD_GET_TXCNT
mdefine_line|#define CMD_GET_TXCNT  (cmdSyntaxPtr)(ct82)
singleline_comment|// Request time-stamped receive character count packet.
singleline_comment|//
DECL|macro|CMD_GET_RXCNT
mdefine_line|#define CMD_GET_RXCNT  (cmdSyntaxPtr)(ct83)
singleline_comment|// Request for box/board I.D. packet.
DECL|macro|CMD_GET_BOXIDS
mdefine_line|#define CMD_GET_BOXIDS (cmdSyntaxPtr)(ct84)
singleline_comment|// Enable or disable multiple channels according to bit-mapped ushorts box 1-4
singleline_comment|//
DECL|macro|CMD_ENAB_MULT
mdefine_line|#define CMD_ENAB_MULT(enable, box1, box2, box3, box4)    &bslash;&n;&t;&t;&t;(((cmdSytaxPtr)(ct85))-&gt;cmd[1] = (enable),            &bslash;&n;&t;&t;&t;*(USHORT *)(((cmdSyntaxPtr)(ct85))-&gt;cmd[2]) = (box1), &bslash;&n;&t;&t;&t;*(USHORT *)(((cmdSyntaxPtr)(ct85))-&gt;cmd[4]) = (box2), &bslash;&n;&t;&t;&t;*(USHORT *)(((cmdSyntaxPtr)(ct85))-&gt;cmd[6]) = (box3), &bslash;&n;&t;&t;&t;*(USHORT *)(((cmdSyntaxPtr)(ct85))-&gt;cmd[8]) = (box4), &bslash;&n;&t;&t;&t;(cmdSyntaxPtr)(ct85))
DECL|macro|CEM_DISABLE
mdefine_line|#define CEM_DISABLE  0
DECL|macro|CEM_ENABLE
mdefine_line|#define CEM_ENABLE   1
singleline_comment|// Enable or disable receiver or receiver interrupts (default both enabled)
singleline_comment|//
DECL|macro|CMD_RCV_ENABLE
mdefine_line|#define CMD_RCV_ENABLE(ch) &bslash;&n;&t;(((cmdSyntaxPtr)(ct86))-&gt;cmd[1] = (ch),(cmdSyntaxPtr)(ct86))
DECL|macro|CRE_OFF
mdefine_line|#define CRE_OFF      0  
singleline_comment|// Disable the receiver
DECL|macro|CRE_ON
mdefine_line|#define CRE_ON       1  
singleline_comment|// Enable the receiver
DECL|macro|CRE_INTOFF
mdefine_line|#define CRE_INTOFF   2  
singleline_comment|// Disable receiver interrupts (to loadware)
DECL|macro|CRE_INTON
mdefine_line|#define CRE_INTON    3  
singleline_comment|// Enable receiver interrupts (to loadware)
singleline_comment|// Starts up a hardware test process, which runs transparently, and sends a
singleline_comment|// STAT_HWFAIL packet in case a hardware failure is detected.
singleline_comment|//
DECL|macro|CMD_HW_TEST
mdefine_line|#define CMD_HW_TEST  (cmdSyntaxPtr)(ct87)
singleline_comment|// Change receiver threshold and timeout value:
singleline_comment|// Defaults: timeout = 20mS
singleline_comment|// threshold count = 8 when DTRflow not in use,
singleline_comment|// threshold count = 5 when DTRflow in use.
singleline_comment|//
DECL|macro|CMD_RCV_THRESHOLD
mdefine_line|#define CMD_RCV_THRESHOLD(count,ms) &bslash;&n;&t;&t;&t;(((cmdSyntaxPtr)(ct88))-&gt;cmd[1] = (count), &bslash;&n;&t;&t;&t;((cmdSyntaxPtr)(ct88))-&gt;cmd[2] = (ms), &bslash;&n;&t;&t;&t;(cmdSyntaxPtr)(ct88))
singleline_comment|// Makes the loadware report DSS signals for this channel immediately.
singleline_comment|//
DECL|macro|CMD_DSS_NOW
mdefine_line|#define CMD_DSS_NOW (cmdSyntaxPtr)(ct89)
singleline_comment|// Set the receive silo parameters 
singleline_comment|// &t;timeout is ms idle wait until delivery       (~VTIME)
singleline_comment|// &t;threshold is max characters cause interrupt  (~VMIN)
singleline_comment|//
DECL|macro|CMD_SET_SILO
mdefine_line|#define CMD_SET_SILO(timeout,threshold) &bslash;&n;&t;&t;&t;(((cmdSyntaxPtr)(ct90))-&gt;cmd[1] = (timeout), &bslash;&n;&t;&t;&t;((cmdSyntaxPtr)(ct90))-&gt;cmd[2]  = (threshold), &bslash;&n;&t;&t;&t;(cmdSyntaxPtr)(ct90))
singleline_comment|// Set timed break in decisecond (1/10s)
singleline_comment|//
DECL|macro|CMD_LBREAK
mdefine_line|#define CMD_LBREAK(ds) &bslash;&n;&t;(((cmdSyntaxPtr)(ct91))-&gt;cmd[1] = (ds),(cmdSyntaxPtr)(ct66))
macro_line|#endif 
singleline_comment|// I2CMD_H
eof
