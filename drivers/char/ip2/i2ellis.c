multiline_comment|/*******************************************************************************&n;*&n;*   (c) 1998 by Computone Corporation&n;*&n;********************************************************************************&n;*&n;*&n;*   PACKAGE:     Linux tty Device Driver for IntelliPort family of multiport&n;*                serial I/O controllers.&n;*&n;*   DESCRIPTION: Low-level interface code for the device driver&n;*                (This is included source code, not a separate compilation&n;*                module.)&n;*&n;*******************************************************************************/
singleline_comment|//---------------------------------------------
singleline_comment|// Function declarations private to this module
singleline_comment|//---------------------------------------------
singleline_comment|// Functions called only indirectly through i2eBordStr entries.
r_static
r_int
id|iiWriteBuf16
c_func
(paren
id|i2eBordStrPtr
comma
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|iiWriteBuf8
c_func
(paren
id|i2eBordStrPtr
comma
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|iiReadBuf16
c_func
(paren
id|i2eBordStrPtr
comma
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|iiReadBuf8
c_func
(paren
id|i2eBordStrPtr
comma
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
r_int
id|iiReadWord16
c_func
(paren
id|i2eBordStrPtr
)paren
suffix:semicolon
r_static
r_int
r_int
id|iiReadWord8
c_func
(paren
id|i2eBordStrPtr
)paren
suffix:semicolon
r_static
r_void
id|iiWriteWord16
c_func
(paren
id|i2eBordStrPtr
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|iiWriteWord8
c_func
(paren
id|i2eBordStrPtr
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_int
id|iiWaitForTxEmptyII
c_func
(paren
id|i2eBordStrPtr
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|iiWaitForTxEmptyIIEX
c_func
(paren
id|i2eBordStrPtr
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|iiTxMailEmptyII
c_func
(paren
id|i2eBordStrPtr
)paren
suffix:semicolon
r_static
r_int
id|iiTxMailEmptyIIEX
c_func
(paren
id|i2eBordStrPtr
)paren
suffix:semicolon
r_static
r_int
id|iiTrySendMailII
c_func
(paren
id|i2eBordStrPtr
comma
r_int
r_char
)paren
suffix:semicolon
r_static
r_int
id|iiTrySendMailIIEX
c_func
(paren
id|i2eBordStrPtr
comma
r_int
r_char
)paren
suffix:semicolon
r_static
r_int
r_int
id|iiGetMailII
c_func
(paren
id|i2eBordStrPtr
)paren
suffix:semicolon
r_static
r_int
r_int
id|iiGetMailIIEX
c_func
(paren
id|i2eBordStrPtr
)paren
suffix:semicolon
r_static
r_void
id|iiEnableMailIrqII
c_func
(paren
id|i2eBordStrPtr
)paren
suffix:semicolon
r_static
r_void
id|iiEnableMailIrqIIEX
c_func
(paren
id|i2eBordStrPtr
)paren
suffix:semicolon
r_static
r_void
id|iiWriteMaskII
c_func
(paren
id|i2eBordStrPtr
comma
r_int
r_char
)paren
suffix:semicolon
r_static
r_void
id|iiWriteMaskIIEX
c_func
(paren
id|i2eBordStrPtr
comma
r_int
r_char
)paren
suffix:semicolon
r_static
r_void
id|ii2DelayTimer
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|ii2DelayWakeup
c_func
(paren
r_int
r_int
id|id
)paren
suffix:semicolon
r_static
r_void
id|ii2Nop
c_func
(paren
r_void
)paren
suffix:semicolon
singleline_comment|//***************
singleline_comment|//* Static Data *
singleline_comment|//***************
DECL|variable|ii2Safe
r_static
r_int
id|ii2Safe
suffix:semicolon
singleline_comment|// Safe I/O address for delay routine
DECL|variable|iiDelayed
r_static
r_int
id|iiDelayed
suffix:semicolon
singleline_comment|// Set when the iiResetDelay function is
singleline_comment|// called. Cleared when ANY board is reset.
DECL|variable|pDelayTimer
r_static
r_struct
id|timer_list
op_star
id|pDelayTimer
suffix:semicolon
singleline_comment|// Used by iiDelayTimer
DECL|variable|pDelayWait
r_static
id|wait_queue_head_t
id|pDelayWait
suffix:semicolon
singleline_comment|// Used by iiDelayTimer
DECL|variable|Dl_spinlock
r_static
id|rwlock_t
id|Dl_spinlock
suffix:semicolon
singleline_comment|//********
singleline_comment|//* Code *
singleline_comment|//********
singleline_comment|//=======================================================
singleline_comment|// Initialization Routines
singleline_comment|//
singleline_comment|// iiSetAddress
singleline_comment|// iiReset
singleline_comment|// iiResetDelay
singleline_comment|// iiInitialize
singleline_comment|//=======================================================
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiEllisInit()
singleline_comment|// Parameters: None
singleline_comment|//
singleline_comment|// Returns:    Nothing
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// This routine performs any required initialization of the iiEllis subsystem.
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_void
DECL|function|iiEllisInit
id|iiEllisInit
c_func
(paren
r_void
)paren
(brace
id|pDelayTimer
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|timer_list
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|pDelayWait
)paren
suffix:semicolon
id|LOCK_INIT
c_func
(paren
op_amp
id|Dl_spinlock
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiEllisCleanup()
singleline_comment|// Parameters: None
singleline_comment|//
singleline_comment|// Returns:    Nothing
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// This routine performs any required cleanup of the iiEllis subsystem.
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_void
DECL|function|iiEllisCleanup
id|iiEllisCleanup
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|pDelayTimer
op_ne
l_int|NULL
)paren
(brace
id|kfree
(paren
id|pDelayTimer
)paren
suffix:semicolon
)brace
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiSetAddress(pB, address, delay)
singleline_comment|// Parameters: pB      - pointer to the board structure
singleline_comment|//             address - the purported I/O address of the board
singleline_comment|//             delay   - pointer to the 1-ms delay function to use
singleline_comment|//                       in this and any future operations to this board
singleline_comment|//
singleline_comment|// Returns:    True if everything appears copacetic.
singleline_comment|//             False if there is any error: the pB-&gt;i2eError field has the error
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// This routine (roughly) checks for address validity, sets the i2eValid OK and
singleline_comment|// sets the state to II_STATE_COLD which means that we haven&squot;t even sent a reset
singleline_comment|// yet.
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
DECL|function|iiSetAddress
id|iiSetAddress
c_func
(paren
id|i2eBordStrPtr
id|pB
comma
r_int
id|address
comma
id|delayFunc_t
id|delay
)paren
(brace
singleline_comment|// Should any failure occur before init is finished...
id|pB-&gt;i2eValid
op_assign
id|I2E_INCOMPLETE
suffix:semicolon
singleline_comment|// Cannot check upper limit except extremely: Might be microchannel
singleline_comment|// Address must be on an 8-byte boundary
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|address
op_le
l_int|0x100
op_logical_or
(paren
r_int
r_int
)paren
id|address
op_ge
l_int|0xfff8
op_logical_or
(paren
id|address
op_amp
l_int|0x7
)paren
)paren
(brace
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_BADADDR
)paren
suffix:semicolon
)brace
singleline_comment|// Initialize accelerators
id|pB-&gt;i2eBase
op_assign
id|address
suffix:semicolon
id|pB-&gt;i2eData
op_assign
id|address
op_plus
id|FIFO_DATA
suffix:semicolon
id|pB-&gt;i2eStatus
op_assign
id|address
op_plus
id|FIFO_STATUS
suffix:semicolon
id|pB-&gt;i2ePointer
op_assign
id|address
op_plus
id|FIFO_PTR
suffix:semicolon
id|pB-&gt;i2eXMail
op_assign
id|address
op_plus
id|FIFO_MAIL
suffix:semicolon
id|pB-&gt;i2eXMask
op_assign
id|address
op_plus
id|FIFO_MASK
suffix:semicolon
singleline_comment|// Initialize i/o address for ii2DelayIO
id|ii2Safe
op_assign
id|address
op_plus
id|FIFO_NOP
suffix:semicolon
singleline_comment|// Initialize the delay routine
id|pB-&gt;i2eDelay
op_assign
(paren
(paren
id|delay
op_ne
(paren
id|delayFunc_t
)paren
l_int|NULL
)paren
ques
c_cond
id|delay
suffix:colon
(paren
id|delayFunc_t
)paren
id|ii2Nop
)paren
suffix:semicolon
id|pB-&gt;i2eValid
op_assign
id|I2E_MAGIC
suffix:semicolon
id|pB-&gt;i2eState
op_assign
id|II_STATE_COLD
suffix:semicolon
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_GOOD
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiReset(pB)
singleline_comment|// Parameters: pB - pointer to the board structure
singleline_comment|//
singleline_comment|// Returns:    True if everything appears copacetic.
singleline_comment|//             False if there is any error: the pB-&gt;i2eError field has the error
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Attempts to reset the board (see also i2hw.h). Normally, we would use this to
singleline_comment|// reset a board immediately after iiSetAddress(), but it is valid to reset a
singleline_comment|// board from any state, say, in order to change or re-load loadware. (Under
singleline_comment|// such circumstances, no reason to re-run iiSetAddress(), which is why it is a
singleline_comment|// separate routine and not included in this routine.
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
DECL|function|iiReset
id|iiReset
c_func
(paren
id|i2eBordStrPtr
id|pB
)paren
(brace
singleline_comment|// Magic number should be set, else even the address is suspect
r_if
c_cond
(paren
id|pB-&gt;i2eValid
op_ne
id|I2E_MAGIC
)paren
(brace
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_BADMAGIC
)paren
suffix:semicolon
)brace
id|OUTB
c_func
(paren
id|pB-&gt;i2eBase
op_plus
id|FIFO_RESET
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// Any data will do
id|iiDelay
c_func
(paren
id|pB
comma
l_int|50
)paren
suffix:semicolon
singleline_comment|// Pause between resets
id|OUTB
c_func
(paren
id|pB-&gt;i2eBase
op_plus
id|FIFO_RESET
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// Second reset
singleline_comment|// We must wait before even attempting to read anything from the FIFO: the
singleline_comment|// board&squot;s P.O.S.T may actually attempt to read and write its end of the
singleline_comment|// FIFO in order to check flags, loop back (where supported), etc. On
singleline_comment|// completion of this testing it would reset the FIFO, and on completion
singleline_comment|// of all // P.O.S.T., write the message. We must not mistake data which
singleline_comment|// might have been sent for testing as part of the reset message. To
singleline_comment|// better utilize time, say, when resetting several boards, we allow the
singleline_comment|// delay to be performed externally; in this way the caller can reset 
singleline_comment|// several boards, delay a single time, then call the initialization
singleline_comment|// routine for all.
id|pB-&gt;i2eState
op_assign
id|II_STATE_RESET
suffix:semicolon
id|iiDelayed
op_assign
l_int|0
suffix:semicolon
singleline_comment|// i.e., the delay routine hasn&squot;t been called since the most
singleline_comment|// recent reset.
singleline_comment|// Ensure anything which would have been of use to standard loadware is
singleline_comment|// blanked out, since board has now forgotten everything!.
id|pB-&gt;i2eUsingIrq
op_assign
id|IRQ_UNDEFINED
suffix:semicolon
singleline_comment|// Not set up to use an interrupt yet
id|pB-&gt;i2eWaitingForEmptyFifo
op_assign
l_int|0
suffix:semicolon
id|pB-&gt;i2eOutMailWaiting
op_assign
l_int|0
suffix:semicolon
id|pB-&gt;i2eChannelPtr
op_assign
l_int|NULL
suffix:semicolon
id|pB-&gt;i2eChannelCnt
op_assign
l_int|0
suffix:semicolon
id|pB-&gt;i2eLeadoffWord
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|pB-&gt;i2eFifoInInts
op_assign
l_int|0
suffix:semicolon
id|pB-&gt;i2eFifoOutInts
op_assign
l_int|0
suffix:semicolon
id|pB-&gt;i2eFatalTrap
op_assign
l_int|NULL
suffix:semicolon
id|pB-&gt;i2eFatal
op_assign
l_int|0
suffix:semicolon
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_GOOD
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiResetDelay(pB)
singleline_comment|// Parameters: pB - pointer to the board structure
singleline_comment|//
singleline_comment|// Returns:    True if everything appears copacetic.
singleline_comment|//             False if there is any error: the pB-&gt;i2eError field has the error
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Using the delay defined in board structure, waits two seconds (for board to
singleline_comment|// reset).
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
DECL|function|iiResetDelay
id|iiResetDelay
c_func
(paren
id|i2eBordStrPtr
id|pB
)paren
(brace
r_if
c_cond
(paren
id|pB-&gt;i2eValid
op_ne
id|I2E_MAGIC
)paren
(brace
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_BADMAGIC
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pB-&gt;i2eState
op_ne
id|II_STATE_RESET
)paren
(brace
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_BADSTATE
)paren
suffix:semicolon
)brace
id|iiDelay
c_func
(paren
id|pB
comma
l_int|2000
)paren
suffix:semicolon
multiline_comment|/* Now we wait for two seconds. */
id|iiDelayed
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Delay has been called: ok to initialize */
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_GOOD
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiInitialize(pB)
singleline_comment|// Parameters: pB - pointer to the board structure
singleline_comment|//
singleline_comment|// Returns:    True if everything appears copacetic.
singleline_comment|//             False if there is any error: the pB-&gt;i2eError field has the error
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Attempts to read the Power-on reset message. Initializes any remaining fields
singleline_comment|// in the pB structure.
singleline_comment|//
singleline_comment|// This should be called as the third step of a process beginning with
singleline_comment|// iiReset(), then iiResetDelay(). This routine checks to see that the structure
singleline_comment|// is &quot;valid&quot; and in the reset state, also confirms that the delay routine has
singleline_comment|// been called since the latest reset (to any board! overly strong!).
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
DECL|function|iiInitialize
id|iiInitialize
c_func
(paren
id|i2eBordStrPtr
id|pB
)paren
(brace
r_int
id|itemp
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
r_int
r_int
id|utemp
suffix:semicolon
r_int
r_int
id|ilimit
suffix:semicolon
r_if
c_cond
(paren
id|pB-&gt;i2eValid
op_ne
id|I2E_MAGIC
)paren
(brace
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_BADMAGIC
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pB-&gt;i2eState
op_ne
id|II_STATE_RESET
op_logical_or
op_logical_neg
id|iiDelayed
)paren
(brace
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_BADSTATE
)paren
suffix:semicolon
)brace
singleline_comment|// In case there is a failure short of our completely reading the power-up
singleline_comment|// message.
id|pB-&gt;i2eValid
op_assign
id|I2E_INCOMPLETE
suffix:semicolon
singleline_comment|// Now attempt to read the message.
r_for
c_loop
(paren
id|itemp
op_assign
l_int|0
suffix:semicolon
id|itemp
OL
r_sizeof
(paren
id|porStr
)paren
suffix:semicolon
id|itemp
op_increment
)paren
(brace
singleline_comment|// We expect the entire message is ready.
r_if
c_cond
(paren
id|HAS_NO_INPUT
c_func
(paren
id|pB
)paren
)paren
(brace
id|pB-&gt;i2ePomSize
op_assign
id|itemp
suffix:semicolon
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_PORM_SHORT
)paren
suffix:semicolon
)brace
id|pB-&gt;i2ePom.c
(braket
id|itemp
)braket
op_assign
id|c
op_assign
id|BYTE_FROM
c_func
(paren
id|pB
)paren
suffix:semicolon
singleline_comment|// We check the magic numbers as soon as they are supposed to be read
singleline_comment|// (rather than after) to minimize effect of reading something we
singleline_comment|// already suspect can&squot;t be &quot;us&quot;.
r_if
c_cond
(paren
(paren
id|itemp
op_eq
id|POR_1_INDEX
op_logical_and
id|c
op_ne
id|POR_MAGIC_1
)paren
op_logical_or
(paren
id|itemp
op_eq
id|POR_2_INDEX
op_logical_and
id|c
op_ne
id|POR_MAGIC_2
)paren
)paren
(brace
id|pB-&gt;i2ePomSize
op_assign
id|itemp
op_plus
l_int|1
suffix:semicolon
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_BADMAGIC
)paren
suffix:semicolon
)brace
)brace
id|pB-&gt;i2ePomSize
op_assign
id|itemp
suffix:semicolon
singleline_comment|// Ensure that this was all the data...
r_if
c_cond
(paren
id|HAS_INPUT
c_func
(paren
id|pB
)paren
)paren
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_PORM_LONG
)paren
suffix:semicolon
singleline_comment|// For now, we&squot;ll fail to initialize if P.O.S.T reports bad chip mapper:
singleline_comment|// Implying we will not be able to download any code either:  That&squot;s ok: the
singleline_comment|// condition is pretty explicit.
r_if
c_cond
(paren
id|pB-&gt;i2ePom.e.porDiag1
op_amp
id|POR_BAD_MAPPER
)paren
(brace
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_POSTERR
)paren
suffix:semicolon
)brace
singleline_comment|// Determine anything which must be done differently depending on the family
singleline_comment|// of boards!
r_switch
c_cond
(paren
id|pB-&gt;i2ePom.e.porID
op_amp
id|POR_ID_FAMILY
)paren
(brace
r_case
id|POR_ID_FII
suffix:colon
singleline_comment|// IntelliPort-II
id|pB-&gt;i2eFifoStyle
op_assign
id|FIFO_II
suffix:semicolon
id|pB-&gt;i2eFifoSize
op_assign
l_int|512
suffix:semicolon
singleline_comment|// 512 bytes, always
id|pB-&gt;i2eDataWidth16
op_assign
id|NO
suffix:semicolon
id|pB-&gt;i2eMaxIrq
op_assign
l_int|15
suffix:semicolon
singleline_comment|// Because board cannot tell us it is in an 8-bit
singleline_comment|// slot, we do allow it to be done (documentation!)
id|pB-&gt;i2eGoodMap
(braket
l_int|1
)braket
op_assign
id|pB-&gt;i2eGoodMap
(braket
l_int|2
)braket
op_assign
id|pB-&gt;i2eGoodMap
(braket
l_int|3
)braket
op_assign
id|pB-&gt;i2eChannelMap
(braket
l_int|1
)braket
op_assign
id|pB-&gt;i2eChannelMap
(braket
l_int|2
)braket
op_assign
id|pB-&gt;i2eChannelMap
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|pB-&gt;i2ePom.e.porID
op_amp
id|POR_ID_SIZE
)paren
(brace
r_case
id|POR_ID_II_4
suffix:colon
id|pB-&gt;i2eGoodMap
(braket
l_int|0
)braket
op_assign
id|pB-&gt;i2eChannelMap
(braket
l_int|0
)braket
op_assign
l_int|0x0f
suffix:semicolon
singleline_comment|// four-port
singleline_comment|// Since porPorts1 is based on the Hardware ID register, the numbers
singleline_comment|// should always be consistent for IntelliPort-II.  Ditto below...
r_if
c_cond
(paren
id|pB-&gt;i2ePom.e.porPorts1
op_ne
l_int|4
)paren
(brace
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_INCONSIST
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|POR_ID_II_8
suffix:colon
r_case
id|POR_ID_II_8R
suffix:colon
id|pB-&gt;i2eGoodMap
(braket
l_int|0
)braket
op_assign
id|pB-&gt;i2eChannelMap
(braket
l_int|0
)braket
op_assign
l_int|0xff
suffix:semicolon
singleline_comment|// Eight port
r_if
c_cond
(paren
id|pB-&gt;i2ePom.e.porPorts1
op_ne
l_int|8
)paren
(brace
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_INCONSIST
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|POR_ID_II_6
suffix:colon
id|pB-&gt;i2eGoodMap
(braket
l_int|0
)braket
op_assign
id|pB-&gt;i2eChannelMap
(braket
l_int|0
)braket
op_assign
l_int|0x3f
suffix:semicolon
singleline_comment|// Six Port
r_if
c_cond
(paren
id|pB-&gt;i2ePom.e.porPorts1
op_ne
l_int|6
)paren
(brace
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_INCONSIST
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
singleline_comment|// Fix up the &quot;good channel list based on any errors reported.
r_if
c_cond
(paren
id|pB-&gt;i2ePom.e.porDiag1
op_amp
id|POR_BAD_UART1
)paren
(brace
id|pB-&gt;i2eGoodMap
(braket
l_int|0
)braket
op_and_assign
op_complement
l_int|0x0f
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pB-&gt;i2ePom.e.porDiag1
op_amp
id|POR_BAD_UART2
)paren
(brace
id|pB-&gt;i2eGoodMap
(braket
l_int|0
)braket
op_and_assign
op_complement
l_int|0xf0
suffix:semicolon
)brace
r_break
suffix:semicolon
singleline_comment|// POR_ID_FII case
r_case
id|POR_ID_FIIEX
suffix:colon
singleline_comment|// IntelliPort-IIEX
id|pB-&gt;i2eFifoStyle
op_assign
id|FIFO_IIEX
suffix:semicolon
id|itemp
op_assign
id|pB-&gt;i2ePom.e.porFifoSize
suffix:semicolon
singleline_comment|// Implicit assumption that fifo would not grow beyond 32k, 
singleline_comment|// nor would ever be less than 256.
r_if
c_cond
(paren
id|itemp
template_param
l_int|15
)paren
(brace
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_INCONSIST
)paren
suffix:semicolon
)brace
id|pB-&gt;i2eFifoSize
op_assign
(paren
l_int|1
op_lshift
id|itemp
)paren
suffix:semicolon
singleline_comment|// These are based on what P.O.S.T thinks should be there, based on
singleline_comment|// box ID registers
id|ilimit
op_assign
id|pB-&gt;i2ePom.e.porNumBoxes
suffix:semicolon
r_if
c_cond
(paren
id|ilimit
OG
id|ABS_MAX_BOXES
)paren
(brace
id|ilimit
op_assign
id|ABS_MAX_BOXES
suffix:semicolon
)brace
singleline_comment|// For as many boxes as EXIST, gives the type of box.
singleline_comment|// Added 8/6/93: check for the ISA-4 (asic) which looks like an
singleline_comment|// expandable but for whom &quot;8 or 16?&quot; is not the right question.
id|utemp
op_assign
id|pB-&gt;i2ePom.e.porFlags
suffix:semicolon
r_if
c_cond
(paren
id|utemp
op_amp
id|POR_CEX4
)paren
(brace
id|pB-&gt;i2eChannelMap
(braket
l_int|0
)braket
op_assign
l_int|0x000f
suffix:semicolon
)brace
r_else
(brace
id|utemp
op_and_assign
id|POR_BOXES
suffix:semicolon
r_for
c_loop
(paren
id|itemp
op_assign
l_int|0
suffix:semicolon
id|itemp
OL
id|ilimit
suffix:semicolon
id|itemp
op_increment
)paren
(brace
id|pB-&gt;i2eChannelMap
(braket
id|itemp
)braket
op_assign
(paren
(paren
id|utemp
op_amp
id|POR_BOX_16
)paren
ques
c_cond
l_int|0xffff
suffix:colon
l_int|0x00ff
)paren
suffix:semicolon
id|utemp
op_rshift_assign
l_int|1
suffix:semicolon
)brace
)brace
singleline_comment|// These are based on what P.O.S.T actually found.
id|utemp
op_assign
(paren
id|pB-&gt;i2ePom.e.porPorts2
op_lshift
l_int|8
)paren
op_plus
id|pB-&gt;i2ePom.e.porPorts1
suffix:semicolon
r_for
c_loop
(paren
id|itemp
op_assign
l_int|0
suffix:semicolon
id|itemp
OL
id|ilimit
suffix:semicolon
id|itemp
op_increment
)paren
(brace
id|pB-&gt;i2eGoodMap
(braket
id|itemp
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|utemp
op_amp
l_int|1
)paren
id|pB-&gt;i2eGoodMap
(braket
id|itemp
)braket
op_or_assign
l_int|0x000f
suffix:semicolon
r_if
c_cond
(paren
id|utemp
op_amp
l_int|2
)paren
id|pB-&gt;i2eGoodMap
(braket
id|itemp
)braket
op_or_assign
l_int|0x00f0
suffix:semicolon
r_if
c_cond
(paren
id|utemp
op_amp
l_int|4
)paren
id|pB-&gt;i2eGoodMap
(braket
id|itemp
)braket
op_or_assign
l_int|0x0f00
suffix:semicolon
r_if
c_cond
(paren
id|utemp
op_amp
l_int|8
)paren
id|pB-&gt;i2eGoodMap
(braket
id|itemp
)braket
op_or_assign
l_int|0xf000
suffix:semicolon
id|utemp
op_rshift_assign
l_int|4
suffix:semicolon
)brace
singleline_comment|// Now determine whether we should transfer in 8 or 16-bit mode.
r_switch
c_cond
(paren
id|pB-&gt;i2ePom.e.porBus
op_amp
(paren
id|POR_BUS_SLOT16
op_or
id|POR_BUS_DIP16
)paren
)paren
(brace
r_case
id|POR_BUS_SLOT16
op_or
id|POR_BUS_DIP16
suffix:colon
id|pB-&gt;i2eDataWidth16
op_assign
id|YES
suffix:semicolon
id|pB-&gt;i2eMaxIrq
op_assign
l_int|15
suffix:semicolon
r_break
suffix:semicolon
r_case
id|POR_BUS_SLOT16
suffix:colon
id|pB-&gt;i2eDataWidth16
op_assign
id|NO
suffix:semicolon
id|pB-&gt;i2eMaxIrq
op_assign
l_int|15
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
r_case
id|POR_BUS_DIP16
suffix:colon
singleline_comment|// In an 8-bit slot, DIP switch don&squot;t care.
r_default
suffix:colon
id|pB-&gt;i2eDataWidth16
op_assign
id|NO
suffix:semicolon
id|pB-&gt;i2eMaxIrq
op_assign
l_int|7
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
singleline_comment|// POR_ID_FIIEX case
r_default
suffix:colon
singleline_comment|// Unknown type of board
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_BAD_FAMILY
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
singleline_comment|// End the switch based on family
singleline_comment|// Temporarily, claim there is no room in the outbound fifo. 
singleline_comment|// We will maintain this whenever we check for an empty outbound FIFO.
id|pB-&gt;i2eFifoRemains
op_assign
l_int|0
suffix:semicolon
singleline_comment|// Now, based on the bus type, should we expect to be able to re-configure
singleline_comment|// interrupts (say, for testing purposes).
r_switch
c_cond
(paren
id|pB-&gt;i2ePom.e.porBus
op_amp
id|POR_BUS_TYPE
)paren
(brace
r_case
id|POR_BUS_T_ISA
suffix:colon
r_case
id|POR_BUS_T_UNK
suffix:colon
singleline_comment|// If the type of bus is undeclared, assume ok.
id|pB-&gt;i2eChangeIrq
op_assign
id|YES
suffix:semicolon
r_break
suffix:semicolon
r_case
id|POR_BUS_T_MCA
suffix:colon
r_case
id|POR_BUS_T_EISA
suffix:colon
id|pB-&gt;i2eChangeIrq
op_assign
id|NO
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_BADBUS
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pB-&gt;i2eDataWidth16
op_eq
id|YES
)paren
(brace
id|pB-&gt;i2eWriteBuf
op_assign
id|iiWriteBuf16
suffix:semicolon
id|pB-&gt;i2eReadBuf
op_assign
id|iiReadBuf16
suffix:semicolon
id|pB-&gt;i2eWriteWord
op_assign
id|iiWriteWord16
suffix:semicolon
id|pB-&gt;i2eReadWord
op_assign
id|iiReadWord16
suffix:semicolon
)brace
r_else
(brace
id|pB-&gt;i2eWriteBuf
op_assign
id|iiWriteBuf8
suffix:semicolon
id|pB-&gt;i2eReadBuf
op_assign
id|iiReadBuf8
suffix:semicolon
id|pB-&gt;i2eWriteWord
op_assign
id|iiWriteWord8
suffix:semicolon
id|pB-&gt;i2eReadWord
op_assign
id|iiReadWord8
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|pB-&gt;i2eFifoStyle
)paren
(brace
r_case
id|FIFO_II
suffix:colon
id|pB-&gt;i2eWaitForTxEmpty
op_assign
id|iiWaitForTxEmptyII
suffix:semicolon
id|pB-&gt;i2eTxMailEmpty
op_assign
id|iiTxMailEmptyII
suffix:semicolon
id|pB-&gt;i2eTrySendMail
op_assign
id|iiTrySendMailII
suffix:semicolon
id|pB-&gt;i2eGetMail
op_assign
id|iiGetMailII
suffix:semicolon
id|pB-&gt;i2eEnableMailIrq
op_assign
id|iiEnableMailIrqII
suffix:semicolon
id|pB-&gt;i2eWriteMask
op_assign
id|iiWriteMaskII
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FIFO_IIEX
suffix:colon
id|pB-&gt;i2eWaitForTxEmpty
op_assign
id|iiWaitForTxEmptyIIEX
suffix:semicolon
id|pB-&gt;i2eTxMailEmpty
op_assign
id|iiTxMailEmptyIIEX
suffix:semicolon
id|pB-&gt;i2eTrySendMail
op_assign
id|iiTrySendMailIIEX
suffix:semicolon
id|pB-&gt;i2eGetMail
op_assign
id|iiGetMailIIEX
suffix:semicolon
id|pB-&gt;i2eEnableMailIrq
op_assign
id|iiEnableMailIrqIIEX
suffix:semicolon
id|pB-&gt;i2eWriteMask
op_assign
id|iiWriteMaskIIEX
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_INCONSIST
)paren
suffix:semicolon
)brace
singleline_comment|// Initialize state information.
id|pB-&gt;i2eState
op_assign
id|II_STATE_READY
suffix:semicolon
singleline_comment|// Ready to load loadware.
singleline_comment|// Some Final cleanup:
singleline_comment|// For some boards, the bootstrap firmware may perform some sort of test
singleline_comment|// resulting in a stray character pending in the incoming mailbox. If one is
singleline_comment|// there, it should be read and discarded, especially since for the standard
singleline_comment|// firmware, it&squot;s the mailbox that interrupts the host.
id|pB-&gt;i2eStartMail
op_assign
id|iiGetMail
c_func
(paren
id|pB
)paren
suffix:semicolon
singleline_comment|// Everything is ok now, return with good status/
id|pB-&gt;i2eValid
op_assign
id|I2E_MAGIC
suffix:semicolon
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_GOOD
)paren
suffix:semicolon
)brace
singleline_comment|//=======================================================
singleline_comment|// Delay Routines
singleline_comment|//
singleline_comment|// iiDelayIO
singleline_comment|// iiNop
singleline_comment|//=======================================================
r_static
r_void
DECL|function|ii2DelayWakeup
id|ii2DelayWakeup
c_func
(paren
r_int
r_int
id|id
)paren
(brace
id|wake_up_interruptible
(paren
op_amp
id|pDelayWait
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   ii2DelayTimer(mseconds)
singleline_comment|// Parameters: mseconds - number of milliseconds to delay
singleline_comment|//
singleline_comment|// Returns:    Nothing
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// This routine delays for approximately mseconds milliseconds and is intended
singleline_comment|// to be called indirectly through i2Delay field in i2eBordStr. It uses the
singleline_comment|// Linux timer_list mechanism.
singleline_comment|//
singleline_comment|// The Linux timers use a unit called &quot;jiffies&quot; which are 10mS in the Intel
singleline_comment|// architecture. This function rounds the delay period up to the next &quot;jiffy&quot;.
singleline_comment|// In the Alpha architecture the &quot;jiffy&quot; is 1mS, but this driver is not intended
singleline_comment|// for Alpha platforms at this time.
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_void
DECL|function|ii2DelayTimer
id|ii2DelayTimer
c_func
(paren
r_int
r_int
id|mseconds
)paren
(brace
id|init_timer
(paren
id|pDelayTimer
)paren
suffix:semicolon
id|pDelayTimer-&gt;expires
op_assign
id|jiffies
op_plus
(paren
id|mseconds
op_plus
l_int|9
)paren
op_div
l_int|10
suffix:semicolon
id|pDelayTimer-&gt;function
op_assign
id|ii2DelayWakeup
suffix:semicolon
id|pDelayTimer-&gt;data
op_assign
l_int|0
suffix:semicolon
id|add_timer
(paren
id|pDelayTimer
)paren
suffix:semicolon
id|interruptible_sleep_on
(paren
op_amp
id|pDelayWait
)paren
suffix:semicolon
id|del_timer
(paren
id|pDelayTimer
)paren
suffix:semicolon
)brace
macro_line|#if 0
singleline_comment|//static void ii2DelayIO(unsigned int);
singleline_comment|//******************************************************************************
singleline_comment|// !!! Not Used, this is DOS crap, some of you young folks may be interested in
singleline_comment|//     in how things were done in the stone age of caculating machines       !!!
singleline_comment|// Function:   ii2DelayIO(mseconds)
singleline_comment|// Parameters: mseconds - number of milliseconds to delay
singleline_comment|//
singleline_comment|// Returns:    Nothing
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// This routine delays for approximately mseconds milliseconds and is intended
singleline_comment|// to be called indirectly through i2Delay field in i2eBordStr. It is intended
singleline_comment|// for use where a clock-based function is impossible: for example, DOS drivers.
singleline_comment|//
singleline_comment|// This function uses the IN instruction to place bounds on the timing and
singleline_comment|// assumes that ii2Safe has been set. This is because I/O instructions are not
singleline_comment|// subject to caching and will therefore take a certain minimum time. To ensure
singleline_comment|// the delay is at least long enough on fast machines, it is based on some
singleline_comment|// fastest-case calculations.  On slower machines this may cause VERY long
singleline_comment|// delays. (3 x fastest case). In the fastest case, everything is cached except
singleline_comment|// the I/O instruction itself.
singleline_comment|//
singleline_comment|// Timing calculations:
singleline_comment|// The fastest bus speed for I/O operations is likely to be 10 MHz. The I/O
singleline_comment|// operation in question is a byte operation to an odd address. For 8-bit
singleline_comment|// operations, the architecture generally enforces two wait states. At 10 MHz, a
singleline_comment|// single cycle time is 100nS. A read operation at two wait states takes 6
singleline_comment|// cycles for a total time of 600nS. Therefore approximately 1666 iterations
singleline_comment|// would be required to generate a single millisecond delay. The worst
singleline_comment|// (reasonable) case would be an 8MHz system with no cacheing. In this case, the
singleline_comment|// I/O instruction would take 125nS x 6 cyles = 750 nS. More importantly, code
singleline_comment|// fetch of other instructions in the loop would take time (zero wait states,
singleline_comment|// however) and would be hard to estimate. This is minimized by using in-line
singleline_comment|// assembler for the in inner loop of IN instructions. This consists of just a
singleline_comment|// few bytes. So we&squot;ll guess about four code fetches per loop. Each code fetch
singleline_comment|// should take four cycles, so we have 125nS * 8 = 1000nS. Worst case then is
singleline_comment|// that what should have taken 1 mS takes instead 1666 * (1750) = 2.9 mS.
singleline_comment|//
singleline_comment|// So much for theoretical timings: results using 1666 value on some actual
singleline_comment|// machines:
singleline_comment|// IBM      286      6MHz     3.15 mS
singleline_comment|// Zenith   386      33MHz    2.45 mS
singleline_comment|// (brandX) 386      33MHz    1.90 mS  (has cache)
singleline_comment|// (brandY) 486      33MHz    2.35 mS
singleline_comment|// NCR      486      ??       1.65 mS (microchannel)
singleline_comment|//
singleline_comment|// For most machines, it is probably safe to scale this number back (remember,
singleline_comment|// for robust operation use an actual timed delay if possible), so we are using
singleline_comment|// a value of 1190. This yields 1.17 mS for the fastest machine in our sample,
singleline_comment|// 1.75 mS for typical 386 machines, and 2.25 mS the absolute slowest machine.
singleline_comment|//
singleline_comment|// 1/29/93:
singleline_comment|// The above timings are too slow. Actual cycle times might be faster. ISA cycle
singleline_comment|// times could approach 500 nS, and ...
singleline_comment|// The IBM model 77 being microchannel has no wait states for 8-bit reads and
singleline_comment|// seems to be accessing the I/O at 440 nS per access (from start of one to
singleline_comment|// start of next). This would imply we need 1000/.440 = 2272 iterations to
singleline_comment|// guarantee we are fast enough. In actual testing, we see that 2 * 1190 are in
singleline_comment|// fact enough. For diagnostics, we keep the level at 1190, but developers note
singleline_comment|// this needs tuning.
singleline_comment|//
singleline_comment|// Safe assumption:  2270 i/o reads = 1 millisecond
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
id|ii2DelValue
op_assign
l_int|1190
suffix:semicolon
singleline_comment|// See timing calculations below
singleline_comment|// 1666 for fastest theoretical machine
singleline_comment|// 1190 safe for most fast 386 machines
singleline_comment|// 1000 for fastest machine tested here
singleline_comment|//  540 (sic) for AT286/6Mhz
r_static
r_void
id|ii2DelayIO
c_func
(paren
r_int
r_int
id|mseconds
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ii2Safe
)paren
r_return
suffix:semicolon
multiline_comment|/* Do nothing if this variable uninitialized */
r_while
c_loop
(paren
id|mseconds
op_decrement
)paren
(brace
r_int
id|i
op_assign
id|ii2DelValue
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
(brace
id|INB
(paren
id|ii2Safe
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif 
singleline_comment|//******************************************************************************
singleline_comment|// Function:   ii2Nop()
singleline_comment|// Parameters: None
singleline_comment|//
singleline_comment|// Returns:    Nothing
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// iiInitialize will set i2eDelay to this if the delay parameter is NULL. This
singleline_comment|// saves checking for a NULL pointer at every call.
singleline_comment|//******************************************************************************
r_static
r_void
DECL|function|ii2Nop
id|ii2Nop
c_func
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
singleline_comment|// no mystery here
)brace
singleline_comment|//=======================================================
singleline_comment|// Routines which are available in 8/16-bit versions, or
singleline_comment|// in different fifo styles. These are ALL called
singleline_comment|// indirectly through the board structure.
singleline_comment|//=======================================================
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiWriteBuf16(pB, address, count)
singleline_comment|// Parameters: pB      - pointer to board structure
singleline_comment|//             address - address of data to write
singleline_comment|//             count   - number of data bytes to write
singleline_comment|//
singleline_comment|// Returns:    True if everything appears copacetic.
singleline_comment|//             False if there is any error: the pB-&gt;i2eError field has the error
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Writes &squot;count&squot; bytes from &squot;address&squot; to the data fifo specified by the board
singleline_comment|// structure pointer pB. Should count happen to be odd, an extra pad byte is
singleline_comment|// sent (identity unknown...). Uses 16-bit (word) operations. Is called
singleline_comment|// indirectly through pB-&gt;i2eWriteBuf.
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
DECL|function|iiWriteBuf16
id|iiWriteBuf16
c_func
(paren
id|i2eBordStrPtr
id|pB
comma
r_int
r_char
op_star
id|address
comma
r_int
id|count
)paren
(brace
singleline_comment|// Rudimentary sanity checking here.
r_if
c_cond
(paren
id|pB-&gt;i2eValid
op_ne
id|I2E_MAGIC
)paren
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_INVALID
)paren
suffix:semicolon
id|OUTSW
(paren
id|pB-&gt;i2eData
comma
id|address
comma
id|count
)paren
suffix:semicolon
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_GOOD
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiWriteBuf8(pB, address, count)
singleline_comment|// Parameters: pB      - pointer to board structure
singleline_comment|//             address - address of data to write
singleline_comment|//             count   - number of data bytes to write
singleline_comment|//
singleline_comment|// Returns:    True if everything appears copacetic.
singleline_comment|//             False if there is any error: the pB-&gt;i2eError field has the error
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Writes &squot;count&squot; bytes from &squot;address&squot; to the data fifo specified by the board
singleline_comment|// structure pointer pB. Should count happen to be odd, an extra pad byte is
singleline_comment|// sent (identity unknown...). This is to be consistant with the 16-bit version.
singleline_comment|// Uses 8-bit (byte) operations. Is called indirectly through pB-&gt;i2eWriteBuf.
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
DECL|function|iiWriteBuf8
id|iiWriteBuf8
c_func
(paren
id|i2eBordStrPtr
id|pB
comma
r_int
r_char
op_star
id|address
comma
r_int
id|count
)paren
(brace
multiline_comment|/* Rudimentary sanity checking here */
r_if
c_cond
(paren
id|pB-&gt;i2eValid
op_ne
id|I2E_MAGIC
)paren
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_INVALID
)paren
suffix:semicolon
id|OUTSB
(paren
id|pB-&gt;i2eData
comma
id|address
comma
id|count
)paren
suffix:semicolon
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_GOOD
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiReadBuf16(pB, address, count)
singleline_comment|// Parameters: pB      - pointer to board structure
singleline_comment|//             address - address to put data read
singleline_comment|//             count   - number of data bytes to read
singleline_comment|//
singleline_comment|// Returns:    True if everything appears copacetic.
singleline_comment|//             False if there is any error: the pB-&gt;i2eError field has the error
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Reads &squot;count&squot; bytes into &squot;address&squot; from the data fifo specified by the board
singleline_comment|// structure pointer pB. Should count happen to be odd, an extra pad byte is
singleline_comment|// received (identity unknown...). Uses 16-bit (word) operations. Is called
singleline_comment|// indirectly through pB-&gt;i2eReadBuf.
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
DECL|function|iiReadBuf16
id|iiReadBuf16
c_func
(paren
id|i2eBordStrPtr
id|pB
comma
r_int
r_char
op_star
id|address
comma
r_int
id|count
)paren
(brace
singleline_comment|// Rudimentary sanity checking here.
r_if
c_cond
(paren
id|pB-&gt;i2eValid
op_ne
id|I2E_MAGIC
)paren
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_INVALID
)paren
suffix:semicolon
id|INSW
(paren
id|pB-&gt;i2eData
comma
id|address
comma
id|count
)paren
suffix:semicolon
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_GOOD
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiReadBuf8(pB, address, count)
singleline_comment|// Parameters: pB      - pointer to board structure
singleline_comment|//             address - address to put data read
singleline_comment|//             count   - number of data bytes to read
singleline_comment|//
singleline_comment|// Returns:    True if everything appears copacetic.
singleline_comment|//             False if there is any error: the pB-&gt;i2eError field has the error
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Reads &squot;count&squot; bytes into &squot;address&squot; from the data fifo specified by the board
singleline_comment|// structure pointer pB. Should count happen to be odd, an extra pad byte is
singleline_comment|// received (identity unknown...). This to match the 16-bit behaviour. Uses
singleline_comment|// 8-bit (byte) operations. Is called indirectly through pB-&gt;i2eReadBuf.
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
DECL|function|iiReadBuf8
id|iiReadBuf8
c_func
(paren
id|i2eBordStrPtr
id|pB
comma
r_int
r_char
op_star
id|address
comma
r_int
id|count
)paren
(brace
singleline_comment|// Rudimentary sanity checking here.
r_if
c_cond
(paren
id|pB-&gt;i2eValid
op_ne
id|I2E_MAGIC
)paren
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_INVALID
)paren
suffix:semicolon
id|INSB
(paren
id|pB-&gt;i2eData
comma
id|address
comma
id|count
)paren
suffix:semicolon
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_GOOD
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiReadWord16(pB)
singleline_comment|// Parameters: pB      - pointer to board structure
singleline_comment|//
singleline_comment|// Returns:    True if everything appears copacetic.
singleline_comment|//             False if there is any error: the pB-&gt;i2eError field has the error
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Returns the word read from the data fifo specified by the board-structure
singleline_comment|// pointer pB. Uses a 16-bit operation. Is called indirectly through
singleline_comment|// pB-&gt;i2eReadWord.
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
r_int
DECL|function|iiReadWord16
id|iiReadWord16
c_func
(paren
id|i2eBordStrPtr
id|pB
)paren
(brace
r_return
(paren
r_int
r_int
)paren
(paren
id|INW
c_func
(paren
id|pB-&gt;i2eData
)paren
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiReadWord8(pB)
singleline_comment|// Parameters: pB      - pointer to board structure
singleline_comment|//
singleline_comment|// Returns:    True if everything appears copacetic.
singleline_comment|//             False if there is any error: the pB-&gt;i2eError field has the error
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Returns the word read from the data fifo specified by the board-structure
singleline_comment|// pointer pB. Uses two 8-bit operations. Bytes are assumed to be LSB first. Is
singleline_comment|// called indirectly through pB-&gt;i2eReadWord.
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
r_int
DECL|function|iiReadWord8
id|iiReadWord8
c_func
(paren
id|i2eBordStrPtr
id|pB
)paren
(brace
r_int
r_int
id|urs
suffix:semicolon
id|urs
op_assign
id|INB
(paren
id|pB-&gt;i2eData
)paren
suffix:semicolon
r_return
(paren
(paren
id|INB
(paren
id|pB-&gt;i2eData
)paren
op_lshift
l_int|8
)paren
op_or
id|urs
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiWriteWord16(pB, value)
singleline_comment|// Parameters: pB    - pointer to board structure
singleline_comment|//             value - data to write
singleline_comment|//
singleline_comment|// Returns:    True if everything appears copacetic.
singleline_comment|//             False if there is any error: the pB-&gt;i2eError field has the error
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Writes the word &squot;value&squot; to the data fifo specified by the board-structure
singleline_comment|// pointer pB. Uses 16-bit operation. Is called indirectly through
singleline_comment|// pB-&gt;i2eWriteWord.
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_void
DECL|function|iiWriteWord16
id|iiWriteWord16
c_func
(paren
id|i2eBordStrPtr
id|pB
comma
r_int
r_int
id|value
)paren
(brace
id|WORD_TO
c_func
(paren
id|pB
comma
(paren
r_int
)paren
id|value
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiWriteWord8(pB, value)
singleline_comment|// Parameters: pB    - pointer to board structure
singleline_comment|//             value - data to write
singleline_comment|//
singleline_comment|// Returns:    True if everything appears copacetic.
singleline_comment|//             False if there is any error: the pB-&gt;i2eError field has the error
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Writes the word &squot;value&squot; to the data fifo specified by the board-structure
singleline_comment|// pointer pB. Uses two 8-bit operations (writes LSB first). Is called
singleline_comment|// indirectly through pB-&gt;i2eWriteWord.
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_void
DECL|function|iiWriteWord8
id|iiWriteWord8
c_func
(paren
id|i2eBordStrPtr
id|pB
comma
r_int
r_int
id|value
)paren
(brace
id|BYTE_TO
c_func
(paren
id|pB
comma
(paren
r_char
)paren
id|value
)paren
suffix:semicolon
id|BYTE_TO
c_func
(paren
id|pB
comma
(paren
r_char
)paren
(paren
id|value
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiWaitForTxEmptyII(pB, mSdelay)
singleline_comment|// Parameters: pB      - pointer to board structure
singleline_comment|//             mSdelay - period to wait before returning
singleline_comment|//
singleline_comment|// Returns:    True if the FIFO is empty.
singleline_comment|//             False if it not empty in the required time: the pB-&gt;i2eError
singleline_comment|//             field has the error.
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Waits up to &quot;mSdelay&quot; milliseconds for the outgoing FIFO to become empty; if
singleline_comment|// not empty by the required time, returns false and error in pB-&gt;i2eError,
singleline_comment|// otherwise returns true.
singleline_comment|//
singleline_comment|// mSdelay == 0 is taken to mean must be empty on the first test.
singleline_comment|//
singleline_comment|// This version operates on IntelliPort-II - style FIFO&squot;s
singleline_comment|//
singleline_comment|// Note this routine is organized so that if status is ok there is no delay at
singleline_comment|// all called either before or after the test.  Is called indirectly through
singleline_comment|// pB-&gt;i2eWaitForTxEmpty.
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
DECL|function|iiWaitForTxEmptyII
id|iiWaitForTxEmptyII
c_func
(paren
id|i2eBordStrPtr
id|pB
comma
r_int
id|mSdelay
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|itemp
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
singleline_comment|// This routine hinges on being able to see the &quot;other&quot; status register
singleline_comment|// (as seen by the local processor).  His incoming fifo is our outgoing
singleline_comment|// FIFO.
singleline_comment|//
singleline_comment|// By the nature of this routine, you would be using this as part of a
singleline_comment|// larger atomic context: i.e., you would use this routine to ensure the
singleline_comment|// fifo empty, then act on this information. Between these two halves, 
singleline_comment|// you will generally not want to service interrupts or in any way 
singleline_comment|// disrupt the assumptions implicit in the larger context.
singleline_comment|//
singleline_comment|// Even worse, however, this routine &quot;shifts&quot; the status register to 
singleline_comment|// point to the local status register which is not the usual situation.
singleline_comment|// Therefore for extra safety, we force the critical section to be
singleline_comment|// completely atomic, and pick up after ourselves before allowing any
singleline_comment|// interrupts of any kind.
id|WRITE_LOCK_IRQSAVE
c_func
(paren
op_amp
id|Dl_spinlock
comma
id|flags
)paren
id|OUTB
c_func
(paren
id|pB-&gt;i2ePointer
comma
id|SEL_COMMAND
)paren
suffix:semicolon
id|OUTB
c_func
(paren
id|pB-&gt;i2ePointer
comma
id|SEL_CMD_SH
)paren
suffix:semicolon
id|itemp
op_assign
id|INB
c_func
(paren
id|pB-&gt;i2eStatus
)paren
suffix:semicolon
id|OUTB
c_func
(paren
id|pB-&gt;i2ePointer
comma
id|SEL_COMMAND
)paren
suffix:semicolon
id|OUTB
c_func
(paren
id|pB-&gt;i2ePointer
comma
id|SEL_CMD_UNSH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|itemp
op_amp
id|ST_IN_EMPTY
)paren
(brace
id|UPDATE_FIFO_ROOM
c_func
(paren
id|pB
)paren
suffix:semicolon
id|WRITE_UNLOCK_IRQRESTORE
c_func
(paren
op_amp
id|Dl_spinlock
comma
id|flags
)paren
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_GOOD
)paren
suffix:semicolon
)brace
id|WRITE_UNLOCK_IRQRESTORE
c_func
(paren
op_amp
id|Dl_spinlock
comma
id|flags
)paren
r_if
c_cond
(paren
id|mSdelay
op_decrement
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|iiDelay
c_func
(paren
id|pB
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* 1 mS granularity on checking condition */
)brace
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_TXE_TIME
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiWaitForTxEmptyIIEX(pB, mSdelay)
singleline_comment|// Parameters: pB      - pointer to board structure
singleline_comment|//             mSdelay - period to wait before returning
singleline_comment|//
singleline_comment|// Returns:    True if the FIFO is empty.
singleline_comment|//             False if it not empty in the required time: the pB-&gt;i2eError
singleline_comment|//             field has the error.
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Waits up to &quot;mSdelay&quot; milliseconds for the outgoing FIFO to become empty; if
singleline_comment|// not empty by the required time, returns false and error in pB-&gt;i2eError,
singleline_comment|// otherwise returns true.
singleline_comment|//
singleline_comment|// mSdelay == 0 is taken to mean must be empty on the first test.
singleline_comment|//
singleline_comment|// This version operates on IntelliPort-IIEX - style FIFO&squot;s
singleline_comment|//
singleline_comment|// Note this routine is organized so that if status is ok there is no delay at
singleline_comment|// all called either before or after the test.  Is called indirectly through
singleline_comment|// pB-&gt;i2eWaitForTxEmpty.
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
DECL|function|iiWaitForTxEmptyIIEX
id|iiWaitForTxEmptyIIEX
c_func
(paren
id|i2eBordStrPtr
id|pB
comma
r_int
id|mSdelay
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
singleline_comment|// By the nature of this routine, you would be using this as part of a
singleline_comment|// larger atomic context: i.e., you would use this routine to ensure the
singleline_comment|// fifo empty, then act on this information. Between these two halves,
singleline_comment|// you will generally not want to service interrupts or in any way
singleline_comment|// disrupt the assumptions implicit in the larger context.
id|WRITE_LOCK_IRQSAVE
c_func
(paren
op_amp
id|Dl_spinlock
comma
id|flags
)paren
r_if
c_cond
(paren
id|INB
c_func
(paren
id|pB-&gt;i2eStatus
)paren
op_amp
id|STE_OUT_MT
)paren
(brace
id|UPDATE_FIFO_ROOM
c_func
(paren
id|pB
)paren
suffix:semicolon
id|WRITE_UNLOCK_IRQRESTORE
c_func
(paren
op_amp
id|Dl_spinlock
comma
id|flags
)paren
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_GOOD
)paren
suffix:semicolon
)brace
id|WRITE_UNLOCK_IRQRESTORE
c_func
(paren
op_amp
id|Dl_spinlock
comma
id|flags
)paren
r_if
c_cond
(paren
id|mSdelay
op_decrement
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|iiDelay
c_func
(paren
id|pB
comma
l_int|1
)paren
suffix:semicolon
singleline_comment|// 1 mS granularity on checking condition
)brace
id|COMPLETE
c_func
(paren
id|pB
comma
id|I2EE_TXE_TIME
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiTxMailEmptyII(pB)
singleline_comment|// Parameters: pB      - pointer to board structure
singleline_comment|//
singleline_comment|// Returns:    True if the transmit mailbox is empty.
singleline_comment|//             False if it not empty.
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Returns true or false according to whether the transmit mailbox is empty (and
singleline_comment|// therefore able to accept more mail)
singleline_comment|//
singleline_comment|// This version operates on IntelliPort-II - style FIFO&squot;s
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
DECL|function|iiTxMailEmptyII
id|iiTxMailEmptyII
c_func
(paren
id|i2eBordStrPtr
id|pB
)paren
(brace
r_int
id|port
op_assign
id|pB-&gt;i2ePointer
suffix:semicolon
id|OUTB
(paren
id|port
comma
id|SEL_OUTMAIL
)paren
suffix:semicolon
r_return
(paren
id|INB
c_func
(paren
id|port
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiTxMailEmptyIIEX(pB)
singleline_comment|// Parameters: pB      - pointer to board structure
singleline_comment|//
singleline_comment|// Returns:    True if the transmit mailbox is empty.
singleline_comment|//             False if it not empty.
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Returns true or false according to whether the transmit mailbox is empty (and
singleline_comment|// therefore able to accept more mail)
singleline_comment|//
singleline_comment|// This version operates on IntelliPort-IIEX - style FIFO&squot;s
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
DECL|function|iiTxMailEmptyIIEX
id|iiTxMailEmptyIIEX
c_func
(paren
id|i2eBordStrPtr
id|pB
)paren
(brace
r_return
op_logical_neg
(paren
id|INB
c_func
(paren
id|pB-&gt;i2eStatus
)paren
op_amp
id|STE_OUT_MAIL
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiTrySendMailII(pB,mail)
singleline_comment|// Parameters: pB   - pointer to board structure
singleline_comment|//             mail - value to write to mailbox
singleline_comment|//
singleline_comment|// Returns:    True if the transmit mailbox is empty, and mail is sent.
singleline_comment|//             False if it not empty.
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// If outgoing mailbox is empty, sends mail and returns true. If outgoing
singleline_comment|// mailbox is not empty, returns false.
singleline_comment|//
singleline_comment|// This version operates on IntelliPort-II - style FIFO&squot;s
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
DECL|function|iiTrySendMailII
id|iiTrySendMailII
c_func
(paren
id|i2eBordStrPtr
id|pB
comma
r_int
r_char
id|mail
)paren
(brace
r_int
id|port
op_assign
id|pB-&gt;i2ePointer
suffix:semicolon
id|OUTB
c_func
(paren
id|port
comma
id|SEL_OUTMAIL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|INB
c_func
(paren
id|port
)paren
op_eq
l_int|0
)paren
(brace
id|OUTB
c_func
(paren
id|port
comma
id|SEL_OUTMAIL
)paren
suffix:semicolon
id|OUTB
c_func
(paren
id|port
comma
id|mail
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiTrySendMailIIEX(pB,mail)
singleline_comment|// Parameters: pB   - pointer to board structure
singleline_comment|//             mail - value to write to mailbox
singleline_comment|//
singleline_comment|// Returns:    True if the transmit mailbox is empty, and mail is sent.
singleline_comment|//             False if it not empty.
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// If outgoing mailbox is empty, sends mail and returns true. If outgoing
singleline_comment|// mailbox is not empty, returns false.
singleline_comment|//
singleline_comment|// This version operates on IntelliPort-IIEX - style FIFO&squot;s
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
DECL|function|iiTrySendMailIIEX
id|iiTrySendMailIIEX
c_func
(paren
id|i2eBordStrPtr
id|pB
comma
r_int
r_char
id|mail
)paren
(brace
r_if
c_cond
(paren
id|INB
c_func
(paren
id|pB-&gt;i2eStatus
)paren
op_amp
id|STE_OUT_MAIL
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|OUTB
c_func
(paren
id|pB-&gt;i2eXMail
comma
id|mail
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiGetMailII(pB,mail)
singleline_comment|// Parameters: pB   - pointer to board structure
singleline_comment|//
singleline_comment|// Returns:    Mailbox data or NO_MAIL_HERE.
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// If no mail available, returns NO_MAIL_HERE otherwise returns the data from
singleline_comment|// the mailbox, which is guaranteed != NO_MAIL_HERE.
singleline_comment|//
singleline_comment|// This version operates on IntelliPort-II - style FIFO&squot;s
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
r_int
DECL|function|iiGetMailII
id|iiGetMailII
c_func
(paren
id|i2eBordStrPtr
id|pB
)paren
(brace
r_if
c_cond
(paren
id|HAS_MAIL
c_func
(paren
id|pB
)paren
)paren
(brace
id|OUTB
c_func
(paren
id|pB-&gt;i2ePointer
comma
id|SEL_INMAIL
)paren
suffix:semicolon
r_return
id|INB
c_func
(paren
id|pB-&gt;i2ePointer
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|NO_MAIL_HERE
suffix:semicolon
)brace
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiGetMailIIEX(pB,mail)
singleline_comment|// Parameters: pB   - pointer to board structure
singleline_comment|//
singleline_comment|// Returns:    Mailbox data or NO_MAIL_HERE.
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// If no mail available, returns NO_MAIL_HERE otherwise returns the data from
singleline_comment|// the mailbox, which is guaranteed != NO_MAIL_HERE.
singleline_comment|//
singleline_comment|// This version operates on IntelliPort-IIEX - style FIFO&squot;s
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
r_int
DECL|function|iiGetMailIIEX
id|iiGetMailIIEX
c_func
(paren
id|i2eBordStrPtr
id|pB
)paren
(brace
r_if
c_cond
(paren
id|HAS_MAIL
c_func
(paren
id|pB
)paren
)paren
(brace
r_return
id|INB
c_func
(paren
id|pB-&gt;i2eXMail
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|NO_MAIL_HERE
suffix:semicolon
)brace
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiEnableMailIrqII(pB)
singleline_comment|// Parameters: pB - pointer to board structure
singleline_comment|//
singleline_comment|// Returns:    Nothing
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Enables board to interrupt host (only) by writing to host&squot;s in-bound mailbox.
singleline_comment|//
singleline_comment|// This version operates on IntelliPort-II - style FIFO&squot;s
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_void
DECL|function|iiEnableMailIrqII
id|iiEnableMailIrqII
c_func
(paren
id|i2eBordStrPtr
id|pB
)paren
(brace
id|OUTB
c_func
(paren
id|pB-&gt;i2ePointer
comma
id|SEL_MASK
)paren
suffix:semicolon
id|OUTB
c_func
(paren
id|pB-&gt;i2ePointer
comma
id|ST_IN_MAIL
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiEnableMailIrqIIEX(pB)
singleline_comment|// Parameters: pB - pointer to board structure
singleline_comment|//
singleline_comment|// Returns:    Nothing
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Enables board to interrupt host (only) by writing to host&squot;s in-bound mailbox.
singleline_comment|//
singleline_comment|// This version operates on IntelliPort-IIEX - style FIFO&squot;s
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_void
DECL|function|iiEnableMailIrqIIEX
id|iiEnableMailIrqIIEX
c_func
(paren
id|i2eBordStrPtr
id|pB
)paren
(brace
id|OUTB
c_func
(paren
id|pB-&gt;i2eXMask
comma
id|MX_IN_MAIL
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiWriteMaskII(pB)
singleline_comment|// Parameters: pB - pointer to board structure
singleline_comment|//
singleline_comment|// Returns:    Nothing
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Writes arbitrary value to the mask register.
singleline_comment|//
singleline_comment|// This version operates on IntelliPort-II - style FIFO&squot;s
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_void
DECL|function|iiWriteMaskII
id|iiWriteMaskII
c_func
(paren
id|i2eBordStrPtr
id|pB
comma
r_int
r_char
id|value
)paren
(brace
id|OUTB
c_func
(paren
id|pB-&gt;i2ePointer
comma
id|SEL_MASK
)paren
suffix:semicolon
id|OUTB
c_func
(paren
id|pB-&gt;i2ePointer
comma
id|value
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiWriteMaskIIEX(pB)
singleline_comment|// Parameters: pB - pointer to board structure
singleline_comment|//
singleline_comment|// Returns:    Nothing
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Writes arbitrary value to the mask register.
singleline_comment|//
singleline_comment|// This version operates on IntelliPort-IIEX - style FIFO&squot;s
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_void
DECL|function|iiWriteMaskIIEX
id|iiWriteMaskIIEX
c_func
(paren
id|i2eBordStrPtr
id|pB
comma
r_int
r_char
id|value
)paren
(brace
id|OUTB
c_func
(paren
id|pB-&gt;i2eXMask
comma
id|value
)paren
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiDownloadBlock(pB, pSource, isStandard)
singleline_comment|// Parameters: pB         - pointer to board structure
singleline_comment|//             pSource    - loadware block to download
singleline_comment|//             isStandard - True if &quot;standard&quot; loadware, else false.
singleline_comment|//
singleline_comment|// Returns:    Success or Failure
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Downloads a single block (at pSource)to the board referenced by pB. Caller
singleline_comment|// sets isStandard to true/false according to whether the &quot;standard&quot; loadware is
singleline_comment|// what&squot;s being loaded. The normal process, then, is to perform an iiInitialize
singleline_comment|// to the board, then perform some number of iiDownloadBlocks using the returned
singleline_comment|// state to determine when download is complete.
singleline_comment|//
singleline_comment|// Possible return values: (see I2ELLIS.H)
singleline_comment|// II_DOWN_BADVALID
singleline_comment|// II_DOWN_BADFILE
singleline_comment|// II_DOWN_CONTINUING
singleline_comment|// II_DOWN_GOOD
singleline_comment|// II_DOWN_BAD
singleline_comment|// II_DOWN_BADSTATE
singleline_comment|// II_DOWN_TIMEOUT
singleline_comment|//
singleline_comment|// Uses the i2eState and i2eToLoad fields (initialized at iiInitialize) to
singleline_comment|// determine whether this is the first block, whether to check for magic
singleline_comment|// numbers, how many blocks there are to go...
singleline_comment|//
singleline_comment|//******************************************************************************
r_static
r_int
DECL|function|iiDownloadBlock
id|iiDownloadBlock
(paren
id|i2eBordStrPtr
id|pB
comma
id|loadHdrStrPtr
id|pSource
comma
r_int
id|isStandard
)paren
(brace
r_int
id|itemp
suffix:semicolon
r_int
id|loadedFirst
suffix:semicolon
r_if
c_cond
(paren
id|pB-&gt;i2eValid
op_ne
id|I2E_MAGIC
)paren
r_return
id|II_DOWN_BADVALID
suffix:semicolon
r_switch
c_cond
(paren
id|pB-&gt;i2eState
)paren
(brace
r_case
id|II_STATE_READY
suffix:colon
singleline_comment|// Loading the first block after reset. Must check the magic number of the
singleline_comment|// loadfile, store the number of blocks we expect to load.
r_if
c_cond
(paren
id|pSource-&gt;e.loadMagic
op_ne
id|MAGIC_LOADFILE
)paren
(brace
r_return
id|II_DOWN_BADFILE
suffix:semicolon
)brace
singleline_comment|// Next we store the total number of blocks to load, including this one.
id|pB-&gt;i2eToLoad
op_assign
l_int|1
op_plus
id|pSource-&gt;e.loadBlocksMore
suffix:semicolon
singleline_comment|// Set the state, store the version numbers. (&squot;Cause this may have come
singleline_comment|// from a file - we might want to report these versions and revisions in
singleline_comment|// case of an error!
id|pB-&gt;i2eState
op_assign
id|II_STATE_LOADING
suffix:semicolon
id|pB-&gt;i2eLVersion
op_assign
id|pSource-&gt;e.loadVersion
suffix:semicolon
id|pB-&gt;i2eLRevision
op_assign
id|pSource-&gt;e.loadRevision
suffix:semicolon
id|pB-&gt;i2eLSub
op_assign
id|pSource-&gt;e.loadSubRevision
suffix:semicolon
singleline_comment|// The time and date of compilation is also available but don&squot;t bother
singleline_comment|// storing it for normal purposes.
id|loadedFirst
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|II_STATE_LOADING
suffix:colon
id|loadedFirst
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|II_DOWN_BADSTATE
suffix:semicolon
)brace
singleline_comment|// Now we must be in the II_STATE_LOADING state, and we assume i2eToLoad
singleline_comment|// must be positive still, because otherwise we would have cleaned up last
singleline_comment|// time and set the state to II_STATE_LOADED.
r_if
c_cond
(paren
op_logical_neg
id|iiWaitForTxEmpty
c_func
(paren
id|pB
comma
id|MAX_DLOAD_READ_TIME
)paren
)paren
(brace
r_return
id|II_DOWN_TIMEOUT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|iiWriteBuf
c_func
(paren
id|pB
comma
id|pSource-&gt;c
comma
id|LOADWARE_BLOCK_SIZE
)paren
)paren
(brace
r_return
id|II_DOWN_BADVALID
suffix:semicolon
)brace
singleline_comment|// If we just loaded the first block, wait for the fifo to empty an extra
singleline_comment|// long time to allow for any special startup code in the firmware, like
singleline_comment|// sending status messages to the LCD&squot;s.
r_if
c_cond
(paren
id|loadedFirst
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|iiWaitForTxEmpty
c_func
(paren
id|pB
comma
id|MAX_DLOAD_START_TIME
)paren
)paren
(brace
r_return
id|II_DOWN_TIMEOUT
suffix:semicolon
)brace
)brace
singleline_comment|// Determine whether this was our last block!
r_if
c_cond
(paren
op_decrement
(paren
id|pB-&gt;i2eToLoad
)paren
)paren
(brace
r_return
id|II_DOWN_CONTINUING
suffix:semicolon
singleline_comment|// more to come...
)brace
singleline_comment|// It WAS our last block: Clean up operations...
singleline_comment|// ...Wait for last buffer to drain from the board...
r_if
c_cond
(paren
op_logical_neg
id|iiWaitForTxEmpty
c_func
(paren
id|pB
comma
id|MAX_DLOAD_READ_TIME
)paren
)paren
(brace
r_return
id|II_DOWN_TIMEOUT
suffix:semicolon
)brace
singleline_comment|// If there were only a single block written, this would come back
singleline_comment|// immediately and be harmless, though not strictly necessary.
id|itemp
op_assign
id|MAX_DLOAD_ACK_TIME
op_div
l_int|10
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|itemp
)paren
(brace
r_if
c_cond
(paren
id|HAS_INPUT
c_func
(paren
id|pB
)paren
)paren
(brace
r_switch
c_cond
(paren
id|BYTE_FROM
c_func
(paren
id|pB
)paren
)paren
(brace
r_case
id|LOADWARE_OK
suffix:colon
id|pB-&gt;i2eState
op_assign
id|isStandard
ques
c_cond
id|II_STATE_STDLOADED
suffix:colon
id|II_STATE_LOADED
suffix:semicolon
singleline_comment|// Some revisions of the bootstrap firmware (e.g. ISA-8 1.0.2)
singleline_comment|// will, // if there is a debug port attached, require some
singleline_comment|// time to send information to the debug port now. It will do
singleline_comment|// this before // executing any of the code we just downloaded.
singleline_comment|// It may take up to 700 milliseconds.
r_if
c_cond
(paren
id|pB-&gt;i2ePom.e.porDiag2
op_amp
id|POR_DEBUG_PORT
)paren
(brace
id|iiDelay
c_func
(paren
id|pB
comma
l_int|700
)paren
suffix:semicolon
)brace
r_return
id|II_DOWN_GOOD
suffix:semicolon
r_case
id|LOADWARE_BAD
suffix:colon
r_default
suffix:colon
r_return
id|II_DOWN_BAD
suffix:semicolon
)brace
)brace
id|iiDelay
c_func
(paren
id|pB
comma
l_int|10
)paren
suffix:semicolon
singleline_comment|// 10 mS granularity on checking condition
)brace
singleline_comment|// Drop-through --&gt; timed out waiting for firmware confirmation
id|pB-&gt;i2eState
op_assign
id|II_STATE_BADLOAD
suffix:semicolon
r_return
id|II_DOWN_TIMEOUT
suffix:semicolon
)brace
singleline_comment|//******************************************************************************
singleline_comment|// Function:   iiDownloadAll(pB, pSource, isStandard, size)
singleline_comment|// Parameters: pB         - pointer to board structure
singleline_comment|//             pSource    - loadware block to download
singleline_comment|//             isStandard - True if &quot;standard&quot; loadware, else false.
singleline_comment|//             size       - size of data to download (in bytes)
singleline_comment|//
singleline_comment|// Returns:    Success or Failure
singleline_comment|//
singleline_comment|// Description:
singleline_comment|//
singleline_comment|// Given a pointer to a board structure, a pointer to the beginning of some
singleline_comment|// loadware, whether it is considered the &quot;standard loadware&quot;, and the size of
singleline_comment|// the array in bytes loads the entire array to the board as loadware.
singleline_comment|//
singleline_comment|// Assumes the board has been freshly reset and the power-up reset message read.
singleline_comment|// (i.e., in II_STATE_READY). Complains if state is bad, or if there seems to be
singleline_comment|// too much or too little data to load, or if iiDownloadBlock complains.
singleline_comment|//******************************************************************************
r_static
r_int
DECL|function|iiDownloadAll
id|iiDownloadAll
c_func
(paren
id|i2eBordStrPtr
id|pB
comma
id|loadHdrStrPtr
id|pSource
comma
r_int
id|isStandard
comma
r_int
id|size
)paren
(brace
r_int
id|status
suffix:semicolon
singleline_comment|// We know (from context) board should be ready for the first block of
singleline_comment|// download.  Complain if not.
r_if
c_cond
(paren
id|pB-&gt;i2eState
op_ne
id|II_STATE_READY
)paren
r_return
id|II_DOWN_BADSTATE
suffix:semicolon
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
id|size
op_sub_assign
id|LOADWARE_BLOCK_SIZE
suffix:semicolon
singleline_comment|// How much data should there be left to
singleline_comment|// load after the following operation ?
singleline_comment|// Note we just bump pSource by &quot;one&quot;, because its size is actually that
singleline_comment|// of an entire block, same as LOADWARE_BLOCK_SIZE.
id|status
op_assign
id|iiDownloadBlock
c_func
(paren
id|pB
comma
id|pSource
op_increment
comma
id|isStandard
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|II_DOWN_GOOD
suffix:colon
r_return
(paren
(paren
id|size
OG
l_int|0
)paren
ques
c_cond
id|II_DOWN_OVER
suffix:colon
id|II_DOWN_GOOD
)paren
suffix:semicolon
r_case
id|II_DOWN_CONTINUING
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|status
suffix:semicolon
)brace
)brace
singleline_comment|// We shouldn&squot;t drop out: it means &quot;while&quot; caught us with nothing left to
singleline_comment|// download, yet the previous DownloadBlock did not return complete. Ergo,
singleline_comment|// not enough data to match the size byte in the header.
r_return
id|II_DOWN_UNDER
suffix:semicolon
)brace
eof
