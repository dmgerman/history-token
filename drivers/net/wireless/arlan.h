multiline_comment|/*&n; *  Copyright (C) 1997 Cullen Jennings&n; *  Copyright (C) 1998 Elmer.Joandi@ut.ee, +37-255-13500&t;&n; *  GNU General Public License applies&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;&t;/* For the statistics structure. */
macro_line|#include &lt;linux/if_arp.h&gt;&t;/* For ARPHRD_ETHER */
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
singleline_comment|//#define ARLAN_DEBUGGING 1
DECL|macro|ARLAN_PROC_INTERFACE
mdefine_line|#define ARLAN_PROC_INTERFACE
DECL|macro|MAX_ARLANS
mdefine_line|#define MAX_ARLANS 4 /* not more than 4 ! */
DECL|macro|ARLAN_PROC_SHM_DUMP
mdefine_line|#define ARLAN_PROC_SHM_DUMP /* shows all card registers, makes driver way larger */
DECL|macro|ARLAN_MAX_MULTICAST_ADDRS
mdefine_line|#define ARLAN_MAX_MULTICAST_ADDRS 16
DECL|macro|ARLAN_RCV_CLEAN
mdefine_line|#define ARLAN_RCV_CLEAN &t;0
DECL|macro|ARLAN_RCV_PROMISC
mdefine_line|#define ARLAN_RCV_PROMISC 1
DECL|macro|ARLAN_RCV_CONTROL
mdefine_line|#define ARLAN_RCV_CONTROL 2
macro_line|#ifdef CONFIG_PROC_FS
r_extern
r_int
id|init_arlan_proc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cleanup_arlan_proc
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|macro|init_arlan_proc
mdefine_line|#define init_arlan_proc()&t;(0)
DECL|macro|cleanup_arlan_proc
mdefine_line|#define cleanup_arlan_proc()&t;do { } while (0);
macro_line|#endif
r_extern
r_struct
id|net_device
op_star
id|arlan_device
(braket
id|MAX_ARLANS
)braket
suffix:semicolon
r_extern
r_int
id|arlan_debug
suffix:semicolon
r_extern
r_int
id|arlan_entry_debug
suffix:semicolon
r_extern
r_int
id|arlan_exit_debug
suffix:semicolon
r_extern
r_int
id|testMemory
suffix:semicolon
r_extern
r_int
id|arlan_command
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|command
)paren
suffix:semicolon
DECL|macro|SIDUNKNOWN
mdefine_line|#define SIDUNKNOWN -1
DECL|macro|radioNodeIdUNKNOWN
mdefine_line|#define radioNodeIdUNKNOWN -1
DECL|macro|irqUNKNOWN
mdefine_line|#define irqUNKNOWN 0
DECL|macro|debugUNKNOWN
mdefine_line|#define debugUNKNOWN 0
DECL|macro|testMemoryUNKNOWN
mdefine_line|#define testMemoryUNKNOWN 1
DECL|macro|spreadingCodeUNKNOWN
mdefine_line|#define spreadingCodeUNKNOWN 0
DECL|macro|channelNumberUNKNOWN
mdefine_line|#define channelNumberUNKNOWN 0
DECL|macro|channelSetUNKNOWN
mdefine_line|#define channelSetUNKNOWN 0
DECL|macro|systemIdUNKNOWN
mdefine_line|#define systemIdUNKNOWN -1
DECL|macro|registrationModeUNKNOWN
mdefine_line|#define registrationModeUNKNOWN -1
DECL|macro|IFDEBUG
mdefine_line|#define IFDEBUG( L ) if ( (L) &amp; arlan_debug ) 
DECL|macro|ARLAN_FAKE_HDR_LEN
mdefine_line|#define ARLAN_FAKE_HDR_LEN 12 
macro_line|#ifdef ARLAN_DEBUGGING
DECL|macro|DEBUG
mdefine_line|#define DEBUG 1
DECL|macro|ARLAN_ENTRY_EXIT_DEBUGGING
mdefine_line|#define ARLAN_ENTRY_EXIT_DEBUGGING 1
DECL|macro|ARLAN_DEBUG
mdefine_line|#define ARLAN_DEBUG(a,b) printk(KERN_DEBUG a, b)
macro_line|#else
DECL|macro|ARLAN_DEBUG
mdefine_line|#define ARLAN_DEBUG(a,b) 
macro_line|#endif
DECL|macro|ARLAN_SHMEM_SIZE
mdefine_line|#define ARLAN_SHMEM_SIZE&t;0x2000
DECL|struct|arlan_shmem
r_struct
id|arlan_shmem
(brace
multiline_comment|/* Header Signature */
DECL|member|textRegion
r_volatile
r_char
id|textRegion
(braket
l_int|48
)braket
suffix:semicolon
DECL|member|resetFlag
r_volatile
id|u_char
id|resetFlag
suffix:semicolon
DECL|member|diagnosticInfo
r_volatile
id|u_char
id|diagnosticInfo
suffix:semicolon
DECL|member|diagnosticOffset
r_volatile
id|u_short
id|diagnosticOffset
suffix:semicolon
DECL|member|_1
r_volatile
id|u_char
id|_1
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|lanCardNodeId
r_volatile
id|u_char
id|lanCardNodeId
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|broadcastAddress
r_volatile
id|u_char
id|broadcastAddress
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|hardwareType
r_volatile
id|u_char
id|hardwareType
suffix:semicolon
DECL|member|majorHardwareVersion
r_volatile
id|u_char
id|majorHardwareVersion
suffix:semicolon
DECL|member|minorHardwareVersion
r_volatile
id|u_char
id|minorHardwareVersion
suffix:semicolon
DECL|member|radioModule
r_volatile
id|u_char
id|radioModule
suffix:semicolon
singleline_comment|// shows EEPROM, can be overridden at 0x111
DECL|member|defaultChannelSet
r_volatile
id|u_char
id|defaultChannelSet
suffix:semicolon
singleline_comment|// shows EEProm, can be overriiden at 0x10A
DECL|member|_2
r_volatile
id|u_char
id|_2
(braket
l_int|47
)braket
suffix:semicolon
multiline_comment|/* Control/Status Block - 0x0080 */
DECL|member|interruptInProgress
r_volatile
id|u_char
id|interruptInProgress
suffix:semicolon
multiline_comment|/* not used by lancpu */
DECL|member|cntrlRegImage
r_volatile
id|u_char
id|cntrlRegImage
suffix:semicolon
multiline_comment|/* not used by lancpu */
DECL|member|_3
r_volatile
id|u_char
id|_3
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|dumpByte
r_volatile
id|u_char
id|dumpByte
suffix:semicolon
DECL|member|commandByte
r_volatile
id|u_char
id|commandByte
suffix:semicolon
multiline_comment|/* non-zero = active */
DECL|member|commandParameter
r_volatile
id|u_char
id|commandParameter
(braket
l_int|15
)braket
suffix:semicolon
multiline_comment|/* Receive Status - 0x00a0 */
DECL|member|rxStatus
r_volatile
id|u_char
id|rxStatus
suffix:semicolon
multiline_comment|/* 1- data, 2-control, 0xff - registr change */
DECL|member|rxFrmType
r_volatile
id|u_char
id|rxFrmType
suffix:semicolon
DECL|member|rxOffset
r_volatile
id|u_short
id|rxOffset
suffix:semicolon
DECL|member|rxLength
r_volatile
id|u_short
id|rxLength
suffix:semicolon
DECL|member|rxSrc
r_volatile
id|u_char
id|rxSrc
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|rxBroadcastFlag
r_volatile
id|u_char
id|rxBroadcastFlag
suffix:semicolon
DECL|member|rxQuality
r_volatile
id|u_char
id|rxQuality
suffix:semicolon
DECL|member|scrambled
r_volatile
id|u_char
id|scrambled
suffix:semicolon
DECL|member|_4
r_volatile
id|u_char
id|_4
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Transmit Status - 0x00b0 */
DECL|member|txStatus
r_volatile
id|u_char
id|txStatus
suffix:semicolon
DECL|member|txAckQuality
r_volatile
id|u_char
id|txAckQuality
suffix:semicolon
DECL|member|numRetries
r_volatile
id|u_char
id|numRetries
suffix:semicolon
DECL|member|_5
r_volatile
id|u_char
id|_5
(braket
l_int|14
)braket
suffix:semicolon
DECL|member|registeredRouter
r_volatile
id|u_char
id|registeredRouter
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|backboneRouter
r_volatile
id|u_char
id|backboneRouter
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|registrationStatus
r_volatile
id|u_char
id|registrationStatus
suffix:semicolon
DECL|member|configuredStatusFlag
r_volatile
id|u_char
id|configuredStatusFlag
suffix:semicolon
DECL|member|_6
r_volatile
id|u_char
id|_6
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|ultimateDestAddress
r_volatile
id|u_char
id|ultimateDestAddress
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|immedDestAddress
r_volatile
id|u_char
id|immedDestAddress
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|immedSrcAddress
r_volatile
id|u_char
id|immedSrcAddress
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|rxSequenceNumber
r_volatile
id|u_short
id|rxSequenceNumber
suffix:semicolon
DECL|member|assignedLocaltalkAddress
r_volatile
id|u_char
id|assignedLocaltalkAddress
suffix:semicolon
DECL|member|_7
r_volatile
id|u_char
id|_7
(braket
l_int|27
)braket
suffix:semicolon
multiline_comment|/* System Parameter Block */
multiline_comment|/* - Driver Parameters (Novell Specific) */
DECL|member|txTimeout
r_volatile
id|u_short
id|txTimeout
suffix:semicolon
DECL|member|transportTime
r_volatile
id|u_short
id|transportTime
suffix:semicolon
DECL|member|_8
r_volatile
id|u_char
id|_8
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* - Configuration Parameters */
DECL|member|irqLevel
r_volatile
id|u_char
id|irqLevel
suffix:semicolon
DECL|member|spreadingCode
r_volatile
id|u_char
id|spreadingCode
suffix:semicolon
DECL|member|channelSet
r_volatile
id|u_char
id|channelSet
suffix:semicolon
DECL|member|channelNumber
r_volatile
id|u_char
id|channelNumber
suffix:semicolon
DECL|member|radioNodeId
r_volatile
id|u_short
id|radioNodeId
suffix:semicolon
DECL|member|_9
r_volatile
id|u_char
id|_9
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|scramblingDisable
r_volatile
id|u_char
id|scramblingDisable
suffix:semicolon
DECL|member|radioType
r_volatile
id|u_char
id|radioType
suffix:semicolon
DECL|member|routerId
r_volatile
id|u_short
id|routerId
suffix:semicolon
DECL|member|_10
r_volatile
id|u_char
id|_10
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|txAttenuation
r_volatile
id|u_char
id|txAttenuation
suffix:semicolon
DECL|member|systemId
r_volatile
id|u_char
id|systemId
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|globalChecksum
r_volatile
id|u_short
id|globalChecksum
suffix:semicolon
DECL|member|_11
r_volatile
id|u_char
id|_11
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|maxDatagramSize
r_volatile
id|u_short
id|maxDatagramSize
suffix:semicolon
DECL|member|maxFrameSize
r_volatile
id|u_short
id|maxFrameSize
suffix:semicolon
DECL|member|maxRetries
r_volatile
id|u_char
id|maxRetries
suffix:semicolon
DECL|member|receiveMode
r_volatile
id|u_char
id|receiveMode
suffix:semicolon
DECL|member|priority
r_volatile
id|u_char
id|priority
suffix:semicolon
DECL|member|rootOrRepeater
r_volatile
id|u_char
id|rootOrRepeater
suffix:semicolon
DECL|member|specifiedRouter
r_volatile
id|u_char
id|specifiedRouter
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|fastPollPeriod
r_volatile
id|u_short
id|fastPollPeriod
suffix:semicolon
DECL|member|pollDecay
r_volatile
id|u_char
id|pollDecay
suffix:semicolon
DECL|member|fastPollDelay
r_volatile
id|u_char
id|fastPollDelay
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|arlThreshold
r_volatile
id|u_char
id|arlThreshold
suffix:semicolon
DECL|member|arlDecay
r_volatile
id|u_char
id|arlDecay
suffix:semicolon
DECL|member|_12
r_volatile
id|u_char
id|_12
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|specRouterTimeout
r_volatile
id|u_short
id|specRouterTimeout
suffix:semicolon
DECL|member|_13
r_volatile
id|u_char
id|_13
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* Scrambled Area */
DECL|member|SID
r_volatile
id|u_char
id|SID
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|encryptionKey
r_volatile
id|u_char
id|encryptionKey
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|_14
r_volatile
id|u_char
id|_14
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|waitTime
r_volatile
id|u_char
id|waitTime
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|lParameter
r_volatile
id|u_char
id|lParameter
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|_15
r_volatile
id|u_char
id|_15
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|headerSize
r_volatile
id|u_short
id|headerSize
suffix:semicolon
DECL|member|sectionChecksum
r_volatile
id|u_short
id|sectionChecksum
suffix:semicolon
DECL|member|registrationMode
r_volatile
id|u_char
id|registrationMode
suffix:semicolon
DECL|member|registrationFill
r_volatile
id|u_char
id|registrationFill
suffix:semicolon
DECL|member|pollPeriod
r_volatile
id|u_short
id|pollPeriod
suffix:semicolon
DECL|member|refreshPeriod
r_volatile
id|u_short
id|refreshPeriod
suffix:semicolon
DECL|member|name
r_volatile
id|u_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|NID
r_volatile
id|u_char
id|NID
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|localTalkAddress
r_volatile
id|u_char
id|localTalkAddress
suffix:semicolon
DECL|member|codeFormat
r_volatile
id|u_char
id|codeFormat
suffix:semicolon
DECL|member|numChannels
r_volatile
id|u_char
id|numChannels
suffix:semicolon
DECL|member|channel1
r_volatile
id|u_char
id|channel1
suffix:semicolon
DECL|member|channel2
r_volatile
id|u_char
id|channel2
suffix:semicolon
DECL|member|channel3
r_volatile
id|u_char
id|channel3
suffix:semicolon
DECL|member|channel4
r_volatile
id|u_char
id|channel4
suffix:semicolon
DECL|member|SSCode
r_volatile
id|u_char
id|SSCode
(braket
l_int|59
)braket
suffix:semicolon
DECL|member|_16
r_volatile
id|u_char
id|_16
(braket
l_int|0xC0
)braket
suffix:semicolon
DECL|member|auxCmd
r_volatile
id|u_short
id|auxCmd
suffix:semicolon
DECL|member|dumpPtr
r_volatile
id|u_char
id|dumpPtr
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|dumpVal
r_volatile
id|u_char
id|dumpVal
suffix:semicolon
DECL|member|_17
r_volatile
id|u_char
id|_17
(braket
l_int|0x6A
)braket
suffix:semicolon
DECL|member|wireTest
r_volatile
id|u_char
id|wireTest
suffix:semicolon
DECL|member|_18
r_volatile
id|u_char
id|_18
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* Statistics Block - 0x0300 */
DECL|member|hostcpuLock
r_volatile
id|u_char
id|hostcpuLock
suffix:semicolon
DECL|member|lancpuLock
r_volatile
id|u_char
id|lancpuLock
suffix:semicolon
DECL|member|resetTime
r_volatile
id|u_char
id|resetTime
(braket
l_int|18
)braket
suffix:semicolon
DECL|member|numDatagramsTransmitted
r_volatile
id|u_char
id|numDatagramsTransmitted
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numReTransmissions
r_volatile
id|u_char
id|numReTransmissions
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numFramesDiscarded
r_volatile
id|u_char
id|numFramesDiscarded
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numDatagramsReceived
r_volatile
id|u_char
id|numDatagramsReceived
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numDuplicateReceivedFrames
r_volatile
id|u_char
id|numDuplicateReceivedFrames
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numDatagramsDiscarded
r_volatile
id|u_char
id|numDatagramsDiscarded
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|maxNumReTransmitDatagram
r_volatile
id|u_short
id|maxNumReTransmitDatagram
suffix:semicolon
DECL|member|maxNumReTransmitFrames
r_volatile
id|u_short
id|maxNumReTransmitFrames
suffix:semicolon
DECL|member|maxNumConsecutiveDuplicateFrames
r_volatile
id|u_short
id|maxNumConsecutiveDuplicateFrames
suffix:semicolon
multiline_comment|/* misaligned here so we have to go to characters */
DECL|member|numBytesTransmitted
r_volatile
id|u_char
id|numBytesTransmitted
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numBytesReceived
r_volatile
id|u_char
id|numBytesReceived
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numCRCErrors
r_volatile
id|u_char
id|numCRCErrors
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numLengthErrors
r_volatile
id|u_char
id|numLengthErrors
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numAbortErrors
r_volatile
id|u_char
id|numAbortErrors
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numTXUnderruns
r_volatile
id|u_char
id|numTXUnderruns
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numRXOverruns
r_volatile
id|u_char
id|numRXOverruns
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numHoldOffs
r_volatile
id|u_char
id|numHoldOffs
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numFramesTransmitted
r_volatile
id|u_char
id|numFramesTransmitted
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numFramesReceived
r_volatile
id|u_char
id|numFramesReceived
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numReceiveFramesLost
r_volatile
id|u_char
id|numReceiveFramesLost
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numRXBufferOverflows
r_volatile
id|u_char
id|numRXBufferOverflows
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numFramesDiscardedAddrMismatch
r_volatile
id|u_char
id|numFramesDiscardedAddrMismatch
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numFramesDiscardedSIDMismatch
r_volatile
id|u_char
id|numFramesDiscardedSIDMismatch
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numPollsTransmistted
r_volatile
id|u_char
id|numPollsTransmistted
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numPollAcknowledges
r_volatile
id|u_char
id|numPollAcknowledges
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numStatusTimeouts
r_volatile
id|u_char
id|numStatusTimeouts
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|numNACKReceived
r_volatile
id|u_char
id|numNACKReceived
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|_19
r_volatile
id|u_char
id|_19
(braket
l_int|0x86
)braket
suffix:semicolon
DECL|member|txBuffer
r_volatile
id|u_char
id|txBuffer
(braket
l_int|0x800
)braket
suffix:semicolon
DECL|member|rxBuffer
r_volatile
id|u_char
id|rxBuffer
(braket
l_int|0x800
)braket
suffix:semicolon
DECL|member|_20
r_volatile
id|u_char
id|_20
(braket
l_int|0x800
)braket
suffix:semicolon
DECL|member|_21
r_volatile
id|u_char
id|_21
(braket
l_int|0x3fb
)braket
suffix:semicolon
DECL|member|configStatus
r_volatile
id|u_char
id|configStatus
suffix:semicolon
DECL|member|_22
r_volatile
id|u_char
id|_22
suffix:semicolon
DECL|member|progIOCtrl
r_volatile
id|u_char
id|progIOCtrl
suffix:semicolon
DECL|member|shareMBase
r_volatile
id|u_char
id|shareMBase
suffix:semicolon
DECL|member|controlRegister
r_volatile
id|u_char
id|controlRegister
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|arlan_conf_stru
r_struct
id|arlan_conf_stru
(brace
DECL|member|spreadingCode
r_int
id|spreadingCode
suffix:semicolon
DECL|member|channelSet
r_int
id|channelSet
suffix:semicolon
DECL|member|channelNumber
r_int
id|channelNumber
suffix:semicolon
DECL|member|scramblingDisable
r_int
id|scramblingDisable
suffix:semicolon
DECL|member|txAttenuation
r_int
id|txAttenuation
suffix:semicolon
DECL|member|systemId
r_int
id|systemId
suffix:semicolon
DECL|member|maxDatagramSize
r_int
id|maxDatagramSize
suffix:semicolon
DECL|member|maxFrameSize
r_int
id|maxFrameSize
suffix:semicolon
DECL|member|maxRetries
r_int
id|maxRetries
suffix:semicolon
DECL|member|receiveMode
r_int
id|receiveMode
suffix:semicolon
DECL|member|priority
r_int
id|priority
suffix:semicolon
DECL|member|rootOrRepeater
r_int
id|rootOrRepeater
suffix:semicolon
DECL|member|SID
r_int
id|SID
suffix:semicolon
DECL|member|radioNodeId
r_int
id|radioNodeId
suffix:semicolon
DECL|member|registrationMode
r_int
id|registrationMode
suffix:semicolon
DECL|member|registrationFill
r_int
id|registrationFill
suffix:semicolon
DECL|member|localTalkAddress
r_int
id|localTalkAddress
suffix:semicolon
DECL|member|codeFormat
r_int
id|codeFormat
suffix:semicolon
DECL|member|numChannels
r_int
id|numChannels
suffix:semicolon
DECL|member|channel1
r_int
id|channel1
suffix:semicolon
DECL|member|channel2
r_int
id|channel2
suffix:semicolon
DECL|member|channel3
r_int
id|channel3
suffix:semicolon
DECL|member|channel4
r_int
id|channel4
suffix:semicolon
DECL|member|txClear
r_int
id|txClear
suffix:semicolon
DECL|member|txRetries
r_int
id|txRetries
suffix:semicolon
DECL|member|txRouting
r_int
id|txRouting
suffix:semicolon
DECL|member|txScrambled
r_int
id|txScrambled
suffix:semicolon
DECL|member|rxParameter
r_int
id|rxParameter
suffix:semicolon
DECL|member|txTimeoutMs
r_int
id|txTimeoutMs
suffix:semicolon
DECL|member|txAckTimeoutMs
r_int
id|txAckTimeoutMs
suffix:semicolon
DECL|member|waitCardTimeout
r_int
id|waitCardTimeout
suffix:semicolon
DECL|member|waitTime
r_int
id|waitTime
suffix:semicolon
DECL|member|lParameter
r_int
id|lParameter
suffix:semicolon
DECL|member|_15
r_int
id|_15
suffix:semicolon
DECL|member|headerSize
r_int
id|headerSize
suffix:semicolon
DECL|member|retries
r_int
id|retries
suffix:semicolon
DECL|member|tx_delay_ms
r_int
id|tx_delay_ms
suffix:semicolon
DECL|member|waitReTransmitPacketMaxSize
r_int
id|waitReTransmitPacketMaxSize
suffix:semicolon
DECL|member|ReTransmitPacketMaxSize
r_int
id|ReTransmitPacketMaxSize
suffix:semicolon
DECL|member|fastReTransCount
r_int
id|fastReTransCount
suffix:semicolon
DECL|member|driverRetransmissions
r_int
id|driverRetransmissions
suffix:semicolon
DECL|member|registrationInterrupts
r_int
id|registrationInterrupts
suffix:semicolon
DECL|member|hardwareType
r_int
id|hardwareType
suffix:semicolon
DECL|member|radioType
r_int
id|radioType
suffix:semicolon
DECL|member|writeRadioType
r_int
id|writeRadioType
suffix:semicolon
DECL|member|writeEEPROM
r_int
id|writeEEPROM
suffix:semicolon
DECL|member|siteName
r_char
id|siteName
(braket
l_int|17
)braket
suffix:semicolon
DECL|member|measure_rate
r_int
id|measure_rate
suffix:semicolon
DECL|member|in_speed
r_int
id|in_speed
suffix:semicolon
DECL|member|out_speed
r_int
id|out_speed
suffix:semicolon
DECL|member|in_speed10
r_int
id|in_speed10
suffix:semicolon
DECL|member|out_speed10
r_int
id|out_speed10
suffix:semicolon
DECL|member|in_speed_max
r_int
id|in_speed_max
suffix:semicolon
DECL|member|out_speed_max
r_int
id|out_speed_max
suffix:semicolon
DECL|member|pre_Command_Wait
r_int
id|pre_Command_Wait
suffix:semicolon
DECL|member|rx_tweak1
r_int
id|rx_tweak1
suffix:semicolon
DECL|member|rx_tweak2
r_int
id|rx_tweak2
suffix:semicolon
DECL|member|tx_queue_len
r_int
id|tx_queue_len
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|arlan_conf_stru
id|arlan_conf
(braket
id|MAX_ARLANS
)braket
suffix:semicolon
DECL|struct|TxParam
r_struct
id|TxParam
(brace
DECL|member|offset
r_volatile
r_int
id|offset
suffix:semicolon
DECL|member|length
r_volatile
r_int
id|length
suffix:semicolon
DECL|member|dest
r_volatile
id|u_char
id|dest
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|clear
r_volatile
r_int
r_char
id|clear
suffix:semicolon
DECL|member|retries
r_volatile
r_int
r_char
id|retries
suffix:semicolon
DECL|member|routing
r_volatile
r_int
r_char
id|routing
suffix:semicolon
DECL|member|scrambled
r_volatile
r_int
r_char
id|scrambled
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TX_RING_SIZE
mdefine_line|#define TX_RING_SIZE 2
multiline_comment|/* Information that need to be kept for each board. */
DECL|struct|arlan_private
r_struct
id|arlan_private
(brace
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|card
r_struct
id|arlan_shmem
id|__iomem
op_star
id|card
suffix:semicolon
DECL|member|conf
r_struct
id|arlan_shmem
op_star
id|conf
suffix:semicolon
DECL|member|Conf
r_struct
id|arlan_conf_stru
op_star
id|Conf
suffix:semicolon
DECL|member|bad
r_int
id|bad
suffix:semicolon
DECL|member|reset
r_int
id|reset
suffix:semicolon
DECL|member|lastReset
r_int
r_int
id|lastReset
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|tx_delay_timer
r_struct
id|timer_list
id|tx_delay_timer
suffix:semicolon
DECL|member|tx_retry_timer
r_struct
id|timer_list
id|tx_retry_timer
suffix:semicolon
DECL|member|rx_check_timer
r_struct
id|timer_list
id|rx_check_timer
suffix:semicolon
DECL|member|registrationLostCount
r_int
id|registrationLostCount
suffix:semicolon
DECL|member|reRegisterExp
r_int
id|reRegisterExp
suffix:semicolon
DECL|member|irq_test_done
r_int
id|irq_test_done
suffix:semicolon
DECL|member|txRing
r_struct
id|TxParam
id|txRing
(braket
id|TX_RING_SIZE
)braket
suffix:semicolon
DECL|member|reTransmitBuff
r_char
id|reTransmitBuff
(braket
l_int|0x800
)braket
suffix:semicolon
DECL|member|txLast
r_int
id|txLast
suffix:semicolon
DECL|member|ReTransmitRequested
r_int
id|ReTransmitRequested
suffix:semicolon
DECL|member|tx_done_delayed
r_int
r_int
id|tx_done_delayed
suffix:semicolon
DECL|member|registrationLastSeen
r_int
r_int
id|registrationLastSeen
suffix:semicolon
DECL|member|tx_last_sent
r_int
r_int
id|tx_last_sent
suffix:semicolon
DECL|member|tx_last_cleared
r_int
r_int
id|tx_last_cleared
suffix:semicolon
DECL|member|retransmissions
r_int
r_int
id|retransmissions
suffix:semicolon
DECL|member|interrupt_ack_requested
r_int
r_int
id|interrupt_ack_requested
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|waiting_command_mask
r_int
r_int
id|waiting_command_mask
suffix:semicolon
DECL|member|card_polling_interval
r_int
r_int
id|card_polling_interval
suffix:semicolon
DECL|member|last_command_buff_free_time
r_int
r_int
id|last_command_buff_free_time
suffix:semicolon
DECL|member|under_reset
r_int
id|under_reset
suffix:semicolon
DECL|member|under_config
r_int
id|under_config
suffix:semicolon
DECL|member|rx_command_given
r_int
id|rx_command_given
suffix:semicolon
DECL|member|tx_command_given
r_int
id|tx_command_given
suffix:semicolon
DECL|member|interrupt_processing_active
r_int
r_int
id|interrupt_processing_active
suffix:semicolon
DECL|member|last_rx_int_ack_time
r_int
r_int
id|last_rx_int_ack_time
suffix:semicolon
DECL|member|in_bytes
r_int
r_int
id|in_bytes
suffix:semicolon
DECL|member|out_bytes
r_int
r_int
id|out_bytes
suffix:semicolon
DECL|member|in_time
r_int
r_int
id|in_time
suffix:semicolon
DECL|member|out_time
r_int
r_int
id|out_time
suffix:semicolon
DECL|member|in_time10
r_int
r_int
id|in_time10
suffix:semicolon
DECL|member|out_time10
r_int
r_int
id|out_time10
suffix:semicolon
DECL|member|in_bytes10
r_int
r_int
id|in_bytes10
suffix:semicolon
DECL|member|out_bytes10
r_int
r_int
id|out_bytes10
suffix:semicolon
DECL|member|init_etherdev_alloc
r_int
id|init_etherdev_alloc
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ARLAN_CLEAR
mdefine_line|#define ARLAN_CLEAR&t;&t;0x00
DECL|macro|ARLAN_RESET
mdefine_line|#define ARLAN_RESET &t;&t;0x01
DECL|macro|ARLAN_CHANNEL_ATTENTION
mdefine_line|#define ARLAN_CHANNEL_ATTENTION 0x02
DECL|macro|ARLAN_INTERRUPT_ENABLE
mdefine_line|#define ARLAN_INTERRUPT_ENABLE &t;0x04
DECL|macro|ARLAN_CLEAR_INTERRUPT
mdefine_line|#define ARLAN_CLEAR_INTERRUPT &t;0x08
DECL|macro|ARLAN_POWER
mdefine_line|#define ARLAN_POWER &t;&t;0x40
DECL|macro|ARLAN_ACCESS
mdefine_line|#define ARLAN_ACCESS&t;&t;0x80
DECL|macro|ARLAN_COM_CONF
mdefine_line|#define ARLAN_COM_CONF                0x01
DECL|macro|ARLAN_COM_RX_ENABLE
mdefine_line|#define ARLAN_COM_RX_ENABLE           0x03
DECL|macro|ARLAN_COM_RX_ABORT
mdefine_line|#define ARLAN_COM_RX_ABORT            0x04
DECL|macro|ARLAN_COM_TX_ENABLE
mdefine_line|#define ARLAN_COM_TX_ENABLE           0x05
DECL|macro|ARLAN_COM_TX_ABORT
mdefine_line|#define ARLAN_COM_TX_ABORT            0x06
DECL|macro|ARLAN_COM_NOP
mdefine_line|#define ARLAN_COM_NOP&t;&t;      0x07
DECL|macro|ARLAN_COM_STANDBY
mdefine_line|#define ARLAN_COM_STANDBY             0x08
DECL|macro|ARLAN_COM_ACTIVATE
mdefine_line|#define ARLAN_COM_ACTIVATE            0x09
DECL|macro|ARLAN_COM_GOTO_SLOW_POLL
mdefine_line|#define ARLAN_COM_GOTO_SLOW_POLL      0x0a
DECL|macro|ARLAN_COM_INT
mdefine_line|#define ARLAN_COM_INT                 0x80
DECL|macro|TXLAST
mdefine_line|#define TXLAST(dev) (((struct arlan_private *)netdev_priv(dev))-&gt;txRing[((struct arlan_private *)netdev_priv(dev))-&gt;txLast])
DECL|macro|TXHEAD
mdefine_line|#define TXHEAD(dev) (((struct arlan_private *)netdev_priv(dev))-&gt;txRing[0])
DECL|macro|TXTAIL
mdefine_line|#define TXTAIL(dev) (((struct arlan_private *)netdev_priv(dev))-&gt;txRing[1])
DECL|macro|TXBuffStart
mdefine_line|#define TXBuffStart(dev) offsetof(struct arlan_shmem, txBuffer)
DECL|macro|TXBuffEnd
mdefine_line|#define TXBuffEnd(dev) offsetof(struct arlan_shmem, xxBuffer)
DECL|macro|READSHM
mdefine_line|#define READSHM(to,from,atype) {&bslash;&n;&t;atype tmp;&bslash;&n;&t;memcpy_fromio(&amp;(tmp),&amp;(from),sizeof(atype));&bslash;&n;&t;to = tmp;&bslash;&n;&t;}
DECL|macro|READSHMEM
mdefine_line|#define READSHMEM(from,atype)&bslash;&n;&t;atype from; &bslash;&n;&t;READSHM(from, arlan-&gt;from, atype);
DECL|macro|WRITESHM
mdefine_line|#define WRITESHM(to,from,atype) &bslash;&n;&t;{ atype tmpSHM = from;&bslash;&n;&t;memcpy_toio(&amp;(to),&amp;tmpSHM,sizeof(atype));&bslash;&n;&t;}
DECL|macro|DEBUGSHM
mdefine_line|#define DEBUGSHM(levelSHM,stringSHM,stuff,atype) &bslash;&n;&t;{&t;atype tmpSHM; &bslash;&n;&t;&t;memcpy_fromio(&amp;tmpSHM,&amp;(stuff),sizeof(atype));&bslash;&n;&t;&t;IFDEBUG(levelSHM) printk(stringSHM,tmpSHM);&bslash;&n;&t;}
DECL|macro|WRITESHMB
mdefine_line|#define WRITESHMB(to, val) &bslash;&n;&t;writeb(val,&amp;(to))
DECL|macro|READSHMB
mdefine_line|#define READSHMB(to) &bslash;&n;&t;readb(&amp;(to))
DECL|macro|WRITESHMS
mdefine_line|#define WRITESHMS(to, val) &bslash;&n;&t;writew(val,&amp;(to))
DECL|macro|READSHMS
mdefine_line|#define READSHMS(to) &bslash;&n;&t;readw(&amp;(to))
DECL|macro|WRITESHMI
mdefine_line|#define WRITESHMI(to, val) &bslash;&n;&t;writel(val,&amp;(to))
DECL|macro|READSHMI
mdefine_line|#define READSHMI(to) &bslash;&n;&t;readl(&amp;(to))
DECL|macro|registrationBad
mdefine_line|#define registrationBad(dev)&bslash;&n;   ( (   READSHMB(((struct arlan_private *)netdev_priv(dev))-&gt;card-&gt;registrationMode)    &gt; 0) &amp;&amp; &bslash;&n;     (   READSHMB(((struct arlan_private *)netdev_priv(dev))-&gt;card-&gt;registrationStatus) == 0)    )
DECL|macro|readControlRegister
mdefine_line|#define readControlRegister(dev)&bslash;&n; &t;READSHMB(((struct arlan_private *)netdev_priv(dev))-&gt;card-&gt;cntrlRegImage)
DECL|macro|writeControlRegister
mdefine_line|#define writeControlRegister(dev, v){&bslash;&n;   WRITESHMB(((struct arlan_private *)netdev_priv(dev))-&gt;card-&gt;cntrlRegImage&t;,((v) &amp;0xF) );&bslash;&n;   WRITESHMB(((struct arlan_private *)netdev_priv(dev))-&gt;card-&gt;controlRegister&t;,(v) &t;);}
DECL|macro|arlan_interrupt_lancpu
mdefine_line|#define arlan_interrupt_lancpu(dev) {&bslash;&n;   int cr;   &bslash;&n;   &bslash;&n;   cr = readControlRegister(dev);&bslash;&n;   if (cr &amp; ARLAN_CHANNEL_ATTENTION){ &bslash;&n;      writeControlRegister(dev, (cr &amp; ~ARLAN_CHANNEL_ATTENTION));&bslash;&n;   }else  &bslash;&n;      writeControlRegister(dev, (cr | ARLAN_CHANNEL_ATTENTION));&bslash;&n;}
DECL|macro|clearChannelAttention
mdefine_line|#define clearChannelAttention(dev){ &bslash;&n;   writeControlRegister(dev,readControlRegister(dev) &amp; ~ARLAN_CHANNEL_ATTENTION);}
DECL|macro|setHardwareReset
mdefine_line|#define setHardwareReset(dev) {&bslash;&n;   writeControlRegister(dev,readControlRegister(dev) | ARLAN_RESET);}
DECL|macro|clearHardwareReset
mdefine_line|#define clearHardwareReset(dev) {&bslash;&n;   writeControlRegister(dev,readControlRegister(dev) &amp; ~ARLAN_RESET);}
DECL|macro|setInterruptEnable
mdefine_line|#define setInterruptEnable(dev){&bslash;&n;   writeControlRegister(dev,readControlRegister(dev) | ARLAN_INTERRUPT_ENABLE)  ;}
DECL|macro|clearInterruptEnable
mdefine_line|#define clearInterruptEnable(dev){&bslash;&n;   writeControlRegister(dev,readControlRegister(dev) &amp; ~ARLAN_INTERRUPT_ENABLE)  ;}
DECL|macro|setClearInterrupt
mdefine_line|#define setClearInterrupt(dev){&bslash;&n;   writeControlRegister(dev,readControlRegister(dev) | ARLAN_CLEAR_INTERRUPT)   ;}
DECL|macro|clearClearInterrupt
mdefine_line|#define clearClearInterrupt(dev){&bslash;&n;   writeControlRegister(dev,readControlRegister(dev) &amp; ~ARLAN_CLEAR_INTERRUPT);}
DECL|macro|setPowerOff
mdefine_line|#define setPowerOff(dev){&bslash;&n;   writeControlRegister(dev,readControlRegister(dev) | (ARLAN_POWER &amp;&amp; ARLAN_ACCESS));&bslash;&n;   writeControlRegister(dev,readControlRegister(dev) &amp; ~ARLAN_ACCESS);}
DECL|macro|setPowerOn
mdefine_line|#define setPowerOn(dev){&bslash;&n;   writeControlRegister(dev,readControlRegister(dev) &amp; ~(ARLAN_POWER));   }
DECL|macro|arlan_lock_card_access
mdefine_line|#define arlan_lock_card_access(dev){&bslash;&n;   writeControlRegister(dev,readControlRegister(dev) &amp; ~ARLAN_ACCESS);}
DECL|macro|arlan_unlock_card_access
mdefine_line|#define arlan_unlock_card_access(dev){&bslash;&n;   writeControlRegister(dev,readControlRegister(dev) | ARLAN_ACCESS ); }  
DECL|macro|ARLAN_COMMAND_RX
mdefine_line|#define ARLAN_COMMAND_RX&t;&t;0x000001
DECL|macro|ARLAN_COMMAND_NOOP
mdefine_line|#define ARLAN_COMMAND_NOOP&t;&t;0x000002
DECL|macro|ARLAN_COMMAND_NOOPINT
mdefine_line|#define ARLAN_COMMAND_NOOPINT&t;&t;0x000004
DECL|macro|ARLAN_COMMAND_TX
mdefine_line|#define ARLAN_COMMAND_TX&t;&t;0x000008
DECL|macro|ARLAN_COMMAND_CONF
mdefine_line|#define ARLAN_COMMAND_CONF&t;&t;0x000010
DECL|macro|ARLAN_COMMAND_RESET
mdefine_line|#define ARLAN_COMMAND_RESET&t;&t;0x000020
DECL|macro|ARLAN_COMMAND_TX_ABORT
mdefine_line|#define ARLAN_COMMAND_TX_ABORT&t;&t;0x000040
DECL|macro|ARLAN_COMMAND_RX_ABORT
mdefine_line|#define ARLAN_COMMAND_RX_ABORT&t;&t;0x000080
DECL|macro|ARLAN_COMMAND_POWERDOWN
mdefine_line|#define ARLAN_COMMAND_POWERDOWN&t;&t;0x000100
DECL|macro|ARLAN_COMMAND_POWERUP
mdefine_line|#define ARLAN_COMMAND_POWERUP&t;&t;0x000200
DECL|macro|ARLAN_COMMAND_SLOW_POLL
mdefine_line|#define ARLAN_COMMAND_SLOW_POLL &t;0x000400
DECL|macro|ARLAN_COMMAND_ACTIVATE
mdefine_line|#define ARLAN_COMMAND_ACTIVATE &t;&t;0x000800
DECL|macro|ARLAN_COMMAND_INT_ACK
mdefine_line|#define ARLAN_COMMAND_INT_ACK&t;&t;0x001000
DECL|macro|ARLAN_COMMAND_INT_ENABLE
mdefine_line|#define ARLAN_COMMAND_INT_ENABLE&t;0x002000
DECL|macro|ARLAN_COMMAND_WAIT_NOW
mdefine_line|#define ARLAN_COMMAND_WAIT_NOW&t;&t;0x004000
DECL|macro|ARLAN_COMMAND_LONG_WAIT_NOW
mdefine_line|#define ARLAN_COMMAND_LONG_WAIT_NOW&t;0x008000
DECL|macro|ARLAN_COMMAND_STANDBY
mdefine_line|#define ARLAN_COMMAND_STANDBY&t;&t;0x010000
DECL|macro|ARLAN_COMMAND_INT_RACK
mdefine_line|#define ARLAN_COMMAND_INT_RACK&t;&t;0x020000
DECL|macro|ARLAN_COMMAND_INT_RENABLE
mdefine_line|#define ARLAN_COMMAND_INT_RENABLE&t;0x040000
DECL|macro|ARLAN_COMMAND_CONF_WAIT
mdefine_line|#define ARLAN_COMMAND_CONF_WAIT&t;&t;0x080000
DECL|macro|ARLAN_COMMAND_TBUSY_CLEAR
mdefine_line|#define ARLAN_COMMAND_TBUSY_CLEAR&t;0x100000
DECL|macro|ARLAN_COMMAND_CLEAN_AND_CONF
mdefine_line|#define ARLAN_COMMAND_CLEAN_AND_CONF&t;(ARLAN_COMMAND_TX_ABORT&bslash;&n;&t;&t;&t;&t;&t;| ARLAN_COMMAND_RX_ABORT&bslash;&n;&t;&t;&t;&t;&t;| ARLAN_COMMAND_CONF)
DECL|macro|ARLAN_COMMAND_CLEAN_AND_RESET
mdefine_line|#define ARLAN_COMMAND_CLEAN_AND_RESET   (ARLAN_COMMAND_TX_ABORT&bslash;&n;&t;&t;&t;&t;&t;| ARLAN_COMMAND_RX_ABORT&bslash;&n;&t;&t;&t;&t;&t;| ARLAN_COMMAND_RESET)
DECL|macro|ARLAN_DEBUG_CHAIN_LOCKS
mdefine_line|#define ARLAN_DEBUG_CHAIN_LOCKS&t;&t;0x00001
DECL|macro|ARLAN_DEBUG_RESET
mdefine_line|#define ARLAN_DEBUG_RESET&t;&t;0x00002
DECL|macro|ARLAN_DEBUG_TIMING
mdefine_line|#define ARLAN_DEBUG_TIMING&t;&t;0x00004
DECL|macro|ARLAN_DEBUG_CARD_STATE
mdefine_line|#define ARLAN_DEBUG_CARD_STATE&t;&t;0x00008
DECL|macro|ARLAN_DEBUG_TX_CHAIN
mdefine_line|#define ARLAN_DEBUG_TX_CHAIN&t;&t;0x00010
DECL|macro|ARLAN_DEBUG_MULTICAST
mdefine_line|#define ARLAN_DEBUG_MULTICAST&t;&t;0x00020
DECL|macro|ARLAN_DEBUG_HEADER_DUMP
mdefine_line|#define ARLAN_DEBUG_HEADER_DUMP&t;&t;0x00040
DECL|macro|ARLAN_DEBUG_INTERRUPT
mdefine_line|#define ARLAN_DEBUG_INTERRUPT&t;&t;0x00080
DECL|macro|ARLAN_DEBUG_STARTUP
mdefine_line|#define ARLAN_DEBUG_STARTUP&t;&t;0x00100
DECL|macro|ARLAN_DEBUG_SHUTDOWN
mdefine_line|#define ARLAN_DEBUG_SHUTDOWN&t;&t;0x00200
eof
