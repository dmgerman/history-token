multiline_comment|/*******************************************************************************&n;*&n;*   (c) 1998 by Computone Corporation&n;*&n;********************************************************************************&n;*&n;*&n;*   PACKAGE:     Linux tty Device Driver for IntelliPort family of multiport&n;*                serial I/O controllers.&n;*&n;*   DESCRIPTION: Definition table for In-line and Bypass commands. Applicable&n;*                only when the standard loadware is active. (This is included&n;*                source code, not a separate compilation module.)&n;*&n;*******************************************************************************/
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|//
singleline_comment|// Revision History:
singleline_comment|//
singleline_comment|// 10 October 1991   MAG First Draft
singleline_comment|//  7 November 1991  MAG Reflects additional commands.
singleline_comment|// 24 February 1992  MAG Additional commands for 1.4.x loadware
singleline_comment|// 11 March 1992     MAG Additional commands
singleline_comment|// 30 March 1992     MAG Additional command: CMD_DSS_NOW
singleline_comment|// 18 May 1992       MAG Discovered commands 39 &amp; 40 must be at the end of a
singleline_comment|//                       packet: affects implementation.
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|//************
singleline_comment|//* Includes *
singleline_comment|//************
macro_line|#include &quot;i2cmd.h&quot;   /* To get some bit-defines */
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// Here is the table of global arrays which represent each type of command
singleline_comment|// supported in the IntelliPort standard loadware. See also i2cmd.h
singleline_comment|// for a more complete explanation of what is going on.
singleline_comment|//------------------------------------------------------------------------------
singleline_comment|// Here are the various globals: note that the names are not used except through
singleline_comment|// the macros defined in i2cmd.h. Also note that although they are character
singleline_comment|// arrays here (for extendability) they are cast to structure pointers in the
singleline_comment|// i2cmd.h macros. See i2cmd.h for flags definitions.
singleline_comment|//                     Length Flags Command
DECL|variable|ct02
r_static
id|UCHAR
id|ct02
(braket
)braket
op_assign
(brace
l_int|1
comma
id|BTH
comma
l_int|0x02
)brace
suffix:semicolon
singleline_comment|// DTR UP
DECL|variable|ct03
r_static
id|UCHAR
id|ct03
(braket
)braket
op_assign
(brace
l_int|1
comma
id|BTH
comma
l_int|0x03
)brace
suffix:semicolon
singleline_comment|// DTR DN
DECL|variable|ct04
r_static
id|UCHAR
id|ct04
(braket
)braket
op_assign
(brace
l_int|1
comma
id|BTH
comma
l_int|0x04
)brace
suffix:semicolon
singleline_comment|// RTS UP
DECL|variable|ct05
r_static
id|UCHAR
id|ct05
(braket
)braket
op_assign
(brace
l_int|1
comma
id|BTH
comma
l_int|0x05
)brace
suffix:semicolon
singleline_comment|// RTS DN
DECL|variable|ct06
r_static
id|UCHAR
id|ct06
(braket
)braket
op_assign
(brace
l_int|1
comma
id|BYP
comma
l_int|0x06
)brace
suffix:semicolon
singleline_comment|// START FL
DECL|variable|ct07
r_static
id|UCHAR
id|ct07
(braket
)braket
op_assign
(brace
l_int|2
comma
id|BTH
comma
l_int|0x07
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// BAUD
DECL|variable|ct08
r_static
id|UCHAR
id|ct08
(braket
)braket
op_assign
(brace
l_int|2
comma
id|BTH
comma
l_int|0x08
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// BITS
DECL|variable|ct09
r_static
id|UCHAR
id|ct09
(braket
)braket
op_assign
(brace
l_int|2
comma
id|BTH
comma
l_int|0x09
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// STOP
DECL|variable|ct10
r_static
id|UCHAR
id|ct10
(braket
)braket
op_assign
(brace
l_int|2
comma
id|BTH
comma
l_int|0x0A
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// PARITY
DECL|variable|ct11
r_static
id|UCHAR
id|ct11
(braket
)braket
op_assign
(brace
l_int|2
comma
id|BTH
comma
l_int|0x0B
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// XON
DECL|variable|ct12
r_static
id|UCHAR
id|ct12
(braket
)braket
op_assign
(brace
l_int|2
comma
id|BTH
comma
l_int|0x0C
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// XOFF
DECL|variable|ct13
r_static
id|UCHAR
id|ct13
(braket
)braket
op_assign
(brace
l_int|1
comma
id|BTH
comma
l_int|0x0D
)brace
suffix:semicolon
singleline_comment|// STOP FL
DECL|variable|ct14
r_static
id|UCHAR
id|ct14
(braket
)braket
op_assign
(brace
l_int|1
comma
id|BYP
op_or
id|VIP
comma
l_int|0x0E
)brace
suffix:semicolon
singleline_comment|// ACK HOTK
singleline_comment|//static UCHAR ct15[]={ 2, BTH|VIP, 0x0F,0                   }; // IRQ SET
DECL|variable|ct16
r_static
id|UCHAR
id|ct16
(braket
)braket
op_assign
(brace
l_int|2
comma
id|INL
comma
l_int|0x10
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// IXONOPTS
DECL|variable|ct17
r_static
id|UCHAR
id|ct17
(braket
)braket
op_assign
(brace
l_int|2
comma
id|INL
comma
l_int|0x11
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// OXONOPTS
DECL|variable|ct18
r_static
id|UCHAR
id|ct18
(braket
)braket
op_assign
(brace
l_int|1
comma
id|INL
comma
l_int|0x12
)brace
suffix:semicolon
singleline_comment|// CTSENAB
DECL|variable|ct19
r_static
id|UCHAR
id|ct19
(braket
)braket
op_assign
(brace
l_int|1
comma
id|BTH
comma
l_int|0x13
)brace
suffix:semicolon
singleline_comment|// CTSDSAB
DECL|variable|ct20
r_static
id|UCHAR
id|ct20
(braket
)braket
op_assign
(brace
l_int|1
comma
id|INL
comma
l_int|0x14
)brace
suffix:semicolon
singleline_comment|// DCDENAB
DECL|variable|ct21
r_static
id|UCHAR
id|ct21
(braket
)braket
op_assign
(brace
l_int|1
comma
id|BTH
comma
l_int|0x15
)brace
suffix:semicolon
singleline_comment|// DCDDSAB
DECL|variable|ct22
r_static
id|UCHAR
id|ct22
(braket
)braket
op_assign
(brace
l_int|1
comma
id|BTH
comma
l_int|0x16
)brace
suffix:semicolon
singleline_comment|// DSRENAB
DECL|variable|ct23
r_static
id|UCHAR
id|ct23
(braket
)braket
op_assign
(brace
l_int|1
comma
id|BTH
comma
l_int|0x17
)brace
suffix:semicolon
singleline_comment|// DSRDSAB
DECL|variable|ct24
r_static
id|UCHAR
id|ct24
(braket
)braket
op_assign
(brace
l_int|1
comma
id|BTH
comma
l_int|0x18
)brace
suffix:semicolon
singleline_comment|// RIENAB
DECL|variable|ct25
r_static
id|UCHAR
id|ct25
(braket
)braket
op_assign
(brace
l_int|1
comma
id|BTH
comma
l_int|0x19
)brace
suffix:semicolon
singleline_comment|// RIDSAB
DECL|variable|ct26
r_static
id|UCHAR
id|ct26
(braket
)braket
op_assign
(brace
l_int|2
comma
id|BTH
comma
l_int|0x1A
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// BRKENAB
DECL|variable|ct27
r_static
id|UCHAR
id|ct27
(braket
)braket
op_assign
(brace
l_int|1
comma
id|BTH
comma
l_int|0x1B
)brace
suffix:semicolon
singleline_comment|// BRKDSAB
singleline_comment|//static UCHAR ct28[]={ 2, BTH,     0x1C,0                   }; // MAXBLOKSIZE
singleline_comment|//static UCHAR ct29[]={ 2, 0,       0x1D,0                   }; // reserved
DECL|variable|ct30
r_static
id|UCHAR
id|ct30
(braket
)braket
op_assign
(brace
l_int|1
comma
id|INL
comma
l_int|0x1E
)brace
suffix:semicolon
singleline_comment|// CTSFLOWENAB
DECL|variable|ct31
r_static
id|UCHAR
id|ct31
(braket
)braket
op_assign
(brace
l_int|1
comma
id|INL
comma
l_int|0x1F
)brace
suffix:semicolon
singleline_comment|// CTSFLOWDSAB
DECL|variable|ct32
r_static
id|UCHAR
id|ct32
(braket
)braket
op_assign
(brace
l_int|1
comma
id|INL
comma
l_int|0x20
)brace
suffix:semicolon
singleline_comment|// RTSFLOWENAB
DECL|variable|ct33
r_static
id|UCHAR
id|ct33
(braket
)braket
op_assign
(brace
l_int|1
comma
id|INL
comma
l_int|0x21
)brace
suffix:semicolon
singleline_comment|// RTSFLOWDSAB
DECL|variable|ct34
r_static
id|UCHAR
id|ct34
(braket
)braket
op_assign
(brace
l_int|2
comma
id|BTH
comma
l_int|0x22
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// ISTRIPMODE
DECL|variable|ct35
r_static
id|UCHAR
id|ct35
(braket
)braket
op_assign
(brace
l_int|2
comma
id|BTH
op_or
id|END
comma
l_int|0x23
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// SENDBREAK
DECL|variable|ct36
r_static
id|UCHAR
id|ct36
(braket
)braket
op_assign
(brace
l_int|2
comma
id|BTH
comma
l_int|0x24
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// SETERRMODE
singleline_comment|//static UCHAR ct36a[]={ 3, INL,    0x24,0,0                 }; // SET_REPLACE
singleline_comment|// The following is listed for completeness, but should never be sent directly
singleline_comment|// by user-level code. It is sent only by library routines in response to data
singleline_comment|// movement.
singleline_comment|//static UCHAR ct37[]={ 5, BYP|VIP, 0x25,0,0,0,0             }; // FLOW PACKET
singleline_comment|// Back to normal
DECL|variable|ct38
r_static
id|UCHAR
id|ct38
(braket
)braket
op_assign
(brace
l_int|11
comma
id|BTH
op_or
id|VAR
comma
l_int|0x26
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// DEF KEY SEQ
singleline_comment|//static UCHAR ct39[]={ 3, BTH|END, 0x27,0,0                 }; // OPOSTON
singleline_comment|//static UCHAR ct40[]={ 1, BTH|END, 0x28                     }; // OPOSTOFF
DECL|variable|ct41
r_static
id|UCHAR
id|ct41
(braket
)braket
op_assign
(brace
l_int|1
comma
id|BYP
comma
l_int|0x29
)brace
suffix:semicolon
singleline_comment|// RESUME
singleline_comment|//static UCHAR ct42[]={ 2, BTH,     0x2A,0                   }; // TXBAUD
singleline_comment|//static UCHAR ct43[]={ 2, BTH,     0x2B,0                   }; // RXBAUD
singleline_comment|//static UCHAR ct44[]={ 2, BTH,     0x2C,0                   }; // MS PING
singleline_comment|//static UCHAR ct45[]={ 1, BTH,     0x2D                     }; // HOTENAB
singleline_comment|//static UCHAR ct46[]={ 1, BTH,     0x2E                     }; // HOTDSAB
DECL|variable|ct47
r_static
id|UCHAR
id|ct47
(braket
)braket
op_assign
(brace
l_int|7
comma
id|BTH
comma
l_int|0x2F
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// UNIX FLAGS
singleline_comment|//static UCHAR ct48[]={ 1, BTH,     0x30                     }; // DSRFLOWENAB
singleline_comment|//static UCHAR ct49[]={ 1, BTH,     0x31                     }; // DSRFLOWDSAB
singleline_comment|//static UCHAR ct50[]={ 1, BTH,     0x32                     }; // DTRFLOWENAB
singleline_comment|//static UCHAR ct51[]={ 1, BTH,     0x33                     }; // DTRFLOWDSAB
singleline_comment|//static UCHAR ct52[]={ 1, BTH,     0x34                     }; // BAUDTABRESET
DECL|variable|ct53
r_static
id|UCHAR
id|ct53
(braket
)braket
op_assign
(brace
l_int|3
comma
id|BTH
comma
l_int|0x35
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// BAUDREMAP
DECL|variable|ct54
r_static
id|UCHAR
id|ct54
(braket
)braket
op_assign
(brace
l_int|3
comma
id|BTH
comma
l_int|0x36
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// CUSTOMBAUD1
DECL|variable|ct55
r_static
id|UCHAR
id|ct55
(braket
)braket
op_assign
(brace
l_int|3
comma
id|BTH
comma
l_int|0x37
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// CUSTOMBAUD2
DECL|variable|ct56
r_static
id|UCHAR
id|ct56
(braket
)braket
op_assign
(brace
l_int|2
comma
id|BTH
op_or
id|END
comma
l_int|0x38
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// PAUSE
DECL|variable|ct57
r_static
id|UCHAR
id|ct57
(braket
)braket
op_assign
(brace
l_int|1
comma
id|BYP
comma
l_int|0x39
)brace
suffix:semicolon
singleline_comment|// SUSPEND
DECL|variable|ct58
r_static
id|UCHAR
id|ct58
(braket
)braket
op_assign
(brace
l_int|1
comma
id|BYP
comma
l_int|0x3A
)brace
suffix:semicolon
singleline_comment|// UNSUSPEND
DECL|variable|ct59
r_static
id|UCHAR
id|ct59
(braket
)braket
op_assign
(brace
l_int|2
comma
id|BTH
comma
l_int|0x3B
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// PARITYCHK
DECL|variable|ct60
r_static
id|UCHAR
id|ct60
(braket
)braket
op_assign
(brace
l_int|1
comma
id|INL
op_or
id|VIP
comma
l_int|0x3C
)brace
suffix:semicolon
singleline_comment|// BOOKMARKREQ
singleline_comment|//static UCHAR ct61[]={ 2, BTH,     0x3D,0                   }; // INTERNALLOOP
singleline_comment|//static UCHAR ct62[]={ 2, BTH,     0x3E,0                   }; // HOTKTIMEOUT
DECL|variable|ct63
r_static
id|UCHAR
id|ct63
(braket
)braket
op_assign
(brace
l_int|2
comma
id|INL
comma
l_int|0x3F
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// SETTXON
DECL|variable|ct64
r_static
id|UCHAR
id|ct64
(braket
)braket
op_assign
(brace
l_int|2
comma
id|INL
comma
l_int|0x40
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// SETTXOFF
singleline_comment|//static UCHAR ct65[]={ 2, BTH,     0x41,0                   }; // SETAUTORTS
singleline_comment|//static UCHAR ct66[]={ 2, BTH,     0x42,0                   }; // SETHIGHWAT
singleline_comment|//static UCHAR ct67[]={ 2, BYP,     0x43,0                   }; // STARTSELFL
singleline_comment|//static UCHAR ct68[]={ 2, INL,     0x44,0                   }; // ENDSELFL
singleline_comment|//static UCHAR ct69[]={ 1, BYP,     0x45                     }; // HWFLOW_OFF
singleline_comment|//static UCHAR ct70[]={ 1, BTH,     0x46                     }; // ODSRFL_ENAB
singleline_comment|//static UCHAR ct71[]={ 1, BTH,     0x47                     }; // ODSRFL_DSAB
singleline_comment|//static UCHAR ct72[]={ 1, BTH,     0x48                     }; // ODCDFL_ENAB
singleline_comment|//static UCHAR ct73[]={ 1, BTH,     0x49                     }; // ODCDFL_DSAB
singleline_comment|//static UCHAR ct74[]={ 2, BTH,     0x4A,0                   }; // LOADLEVEL
singleline_comment|//static UCHAR ct75[]={ 2, BTH,     0x4B,0                   }; // STATDATA
singleline_comment|//static UCHAR ct76[]={ 1, BYP,     0x4C                     }; // BREAK_ON
singleline_comment|//static UCHAR ct77[]={ 1, BYP,     0x4D                     }; // BREAK_OFF
singleline_comment|//static UCHAR ct78[]={ 1, BYP,     0x4E                     }; // GETFC
DECL|variable|ct79
r_static
id|UCHAR
id|ct79
(braket
)braket
op_assign
(brace
l_int|2
comma
id|BYP
comma
l_int|0x4F
comma
l_int|0
)brace
suffix:semicolon
singleline_comment|// XMIT_NOW
singleline_comment|//static UCHAR ct80[]={ 4, BTH,     0x50,0,0,0               }; // DIVISOR_LATCH
singleline_comment|//static UCHAR ct81[]={ 1, BYP,     0x51                     }; // GET_STATUS
singleline_comment|//static UCHAR ct82[]={ 1, BYP,     0x52                     }; // GET_TXCNT
singleline_comment|//static UCHAR ct83[]={ 1, BYP,     0x53                     }; // GET_RXCNT
singleline_comment|//static UCHAR ct84[]={ 1, BYP,     0x54                     }; // GET_BOXIDS
singleline_comment|//static UCHAR ct85[]={10, BYP,     0x55,0,0,0,0,0,0,0,0,0   }; // ENAB_MULT
singleline_comment|//static UCHAR ct86[]={ 2, BTH,     0x56,0                   }; // RCV_ENABLE
DECL|variable|ct87
r_static
id|UCHAR
id|ct87
(braket
)braket
op_assign
(brace
l_int|1
comma
id|BYP
comma
l_int|0x57
)brace
suffix:semicolon
singleline_comment|// HW_TEST
singleline_comment|//static UCHAR ct88[]={ 3, BTH,     0x58,0,0                 }; // RCV_THRESHOLD
singleline_comment|//static UCHAR ct89[]={ 1, BYP,     0x59                     }; // DSS_NOW
singleline_comment|//static UCHAR ct90[]={ 3, BYP,     0x5A,0,0                 }; // Set SILO
singleline_comment|//static UCHAR ct91[]={ 2, BYP,     0x5B,0                   }; // timed break
singleline_comment|// Some composite commands as well
singleline_comment|//static UCHAR cc01[]={ 2, BTH,     0x02,0x04                }; // DTR &amp; RTS UP
singleline_comment|//static UCHAR cc02[]={ 2, BTH,     0x03,0x05                }; // DTR &amp; RTS DN
singleline_comment|//********
singleline_comment|//* Code *
singleline_comment|//********
singleline_comment|//******************************************************************************
singleline_comment|// Function:   i2cmdSetSeq(type, size, string)
singleline_comment|// Parameters: type   - sequence number
singleline_comment|//             size   - length of sequence
singleline_comment|//             string - substitution string
singleline_comment|//
singleline_comment|// Returns:    Pointer to command structure
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// This routine sets the parameters of command 38 Define Hot Key sequence (alias
singleline_comment|// &quot;special receive sequence&quot;). Returns a pointer to the structure. Endeavours
singleline_comment|// to be bullet-proof in that the sequence number is forced in range, and any
singleline_comment|// out-of-range sizes are forced to zero.
singleline_comment|//******************************************************************************
id|cmdSyntaxPtr
DECL|function|i2cmdSetSeq
id|i2cmdSetSeq
c_func
(paren
r_int
r_char
id|type
comma
r_int
r_char
id|size
comma
r_int
r_char
op_star
id|string
)paren
(brace
id|cmdSyntaxPtr
id|pCM
op_assign
(paren
id|cmdSyntaxPtr
)paren
id|ct38
suffix:semicolon
r_int
r_char
op_star
id|pc
suffix:semicolon
id|pCM-&gt;cmd
(braket
l_int|1
)braket
op_assign
(paren
(paren
id|type
OG
l_int|0xf
)paren
ques
c_cond
l_int|0xf
suffix:colon
id|type
)paren
suffix:semicolon
singleline_comment|// Sequence number
id|size
op_assign
(paren
(paren
id|size
OG
l_int|0x8
)paren
ques
c_cond
l_int|0
suffix:colon
id|size
)paren
suffix:semicolon
singleline_comment|// size
id|pCM-&gt;cmd
(braket
l_int|2
)braket
op_assign
id|size
suffix:semicolon
id|pCM-&gt;length
op_assign
l_int|3
op_plus
id|size
suffix:semicolon
singleline_comment|// UPDATES THE LENGTH!
id|pc
op_assign
op_amp
(paren
id|pCM-&gt;cmd
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
)paren
(brace
op_star
id|pc
op_increment
op_assign
op_star
id|string
op_increment
suffix:semicolon
)brace
r_return
id|pCM
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   i2cmdUnixFlags(iflag, cflag, lflag)
singleline_comment|// Parameters: Unix tty flags
singleline_comment|//
singleline_comment|// Returns:    Pointer to command structure
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// This routine sets the parameters of command 47 and returns a pointer to the
singleline_comment|// appropriate structure.
singleline_comment|//******************************************************************************
id|cmdSyntaxPtr
DECL|function|i2cmdUnixFlags
id|i2cmdUnixFlags
c_func
(paren
r_int
r_int
id|iflag
comma
r_int
r_int
id|cflag
comma
r_int
r_int
id|lflag
)paren
(brace
id|cmdSyntaxPtr
id|pCM
op_assign
(paren
id|cmdSyntaxPtr
)paren
id|ct47
suffix:semicolon
id|pCM-&gt;cmd
(braket
l_int|1
)braket
op_assign
(paren
r_int
r_char
)paren
id|iflag
suffix:semicolon
id|pCM-&gt;cmd
(braket
l_int|2
)braket
op_assign
(paren
r_int
r_char
)paren
(paren
id|iflag
op_rshift
l_int|8
)paren
suffix:semicolon
id|pCM-&gt;cmd
(braket
l_int|3
)braket
op_assign
(paren
r_int
r_char
)paren
id|cflag
suffix:semicolon
id|pCM-&gt;cmd
(braket
l_int|4
)braket
op_assign
(paren
r_int
r_char
)paren
(paren
id|cflag
op_rshift
l_int|8
)paren
suffix:semicolon
id|pCM-&gt;cmd
(braket
l_int|5
)braket
op_assign
(paren
r_int
r_char
)paren
id|lflag
suffix:semicolon
id|pCM-&gt;cmd
(braket
l_int|6
)braket
op_assign
(paren
r_int
r_char
)paren
(paren
id|lflag
op_rshift
l_int|8
)paren
suffix:semicolon
r_return
id|pCM
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   i2cmdBaudRemap(dest,src)
singleline_comment|// Parameters: ?
singleline_comment|//
singleline_comment|// Returns:    Pointer to command structure
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// This routine sets the parameters of command 53 and returns a pointer to the
singleline_comment|// appropriate structure.
singleline_comment|//******************************************************************************
id|cmdSyntaxPtr
DECL|function|i2cmdBaudRemap
id|i2cmdBaudRemap
c_func
(paren
r_int
r_char
id|dest
comma
r_int
r_char
id|src
)paren
(brace
id|cmdSyntaxPtr
id|pCM
op_assign
(paren
id|cmdSyntaxPtr
)paren
id|ct53
suffix:semicolon
id|pCM-&gt;cmd
(braket
l_int|1
)braket
op_assign
id|dest
suffix:semicolon
id|pCM-&gt;cmd
(braket
l_int|2
)braket
op_assign
id|src
suffix:semicolon
r_return
id|pCM
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   i2cmdBaudDef(which, rate)
singleline_comment|// Parameters: ?
singleline_comment|//
singleline_comment|// Returns:    Pointer to command structure
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// This routine sets the parameters of commands 54 or 55 (according to the
singleline_comment|// argument which), and returns a pointer to the appropriate structure.
singleline_comment|//******************************************************************************
id|cmdSyntaxPtr
DECL|function|i2cmdBaudDef
id|i2cmdBaudDef
c_func
(paren
r_int
id|which
comma
r_int
r_int
id|rate
)paren
(brace
id|cmdSyntaxPtr
id|pCM
suffix:semicolon
r_switch
c_cond
(paren
id|which
)paren
(brace
r_case
l_int|1
suffix:colon
id|pCM
op_assign
(paren
id|cmdSyntaxPtr
)paren
id|ct54
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_case
l_int|2
suffix:colon
id|pCM
op_assign
(paren
id|cmdSyntaxPtr
)paren
id|ct55
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pCM-&gt;cmd
(braket
l_int|1
)braket
op_assign
(paren
r_int
r_char
)paren
id|rate
suffix:semicolon
id|pCM-&gt;cmd
(braket
l_int|2
)braket
op_assign
(paren
r_int
r_char
)paren
(paren
id|rate
op_rshift
l_int|8
)paren
suffix:semicolon
r_return
id|pCM
suffix:semicolon
)brace
eof
