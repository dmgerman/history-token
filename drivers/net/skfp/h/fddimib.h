multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * FDDI MIB&n; */
multiline_comment|/*&n; * typedefs&n; */
DECL|typedef|Counter
r_typedef
id|u_long
id|Counter
suffix:semicolon
DECL|typedef|TimeStamp
r_typedef
id|u_char
id|TimeStamp
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|LongAddr
r_typedef
r_struct
id|fddi_addr
id|LongAddr
suffix:semicolon
DECL|typedef|Timer_2
r_typedef
id|u_long
id|Timer_2
suffix:semicolon
DECL|typedef|Timer
r_typedef
id|u_long
id|Timer
suffix:semicolon
DECL|typedef|ResId
r_typedef
id|u_short
id|ResId
suffix:semicolon
DECL|typedef|SMTEnum
r_typedef
id|u_short
id|SMTEnum
suffix:semicolon
DECL|typedef|SMTFlag
r_typedef
id|u_char
id|SMTFlag
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|count
id|Counter
id|count
suffix:semicolon
DECL|member|timestamp
id|TimeStamp
id|timestamp
suffix:semicolon
DECL|typedef|SetCountType
)brace
id|SetCountType
suffix:semicolon
multiline_comment|/*&n; * bits for bit string &quot;available_path&quot;&n; */
DECL|macro|MIB_PATH_P
mdefine_line|#define MIB_PATH_P&t;(1&lt;&lt;0)
DECL|macro|MIB_PATH_S
mdefine_line|#define MIB_PATH_S&t;(1&lt;&lt;1)
DECL|macro|MIB_PATH_L
mdefine_line|#define MIB_PATH_L&t;(1&lt;&lt;2)
multiline_comment|/*&n; * bits for bit string PermittedPaths &amp; RequestedPaths (SIZE(8))&n; */
DECL|macro|MIB_P_PATH_LOCAL
mdefine_line|#define MIB_P_PATH_LOCAL&t;(1&lt;&lt;0)
DECL|macro|MIB_P_PATH_SEC_ALTER
mdefine_line|#define MIB_P_PATH_SEC_ALTER&t;(1&lt;&lt;1)
DECL|macro|MIB_P_PATH_PRIM_ALTER
mdefine_line|#define MIB_P_PATH_PRIM_ALTER&t;(1&lt;&lt;2)
DECL|macro|MIB_P_PATH_CON_ALTER
mdefine_line|#define MIB_P_PATH_CON_ALTER&t;(1&lt;&lt;3)
DECL|macro|MIB_P_PATH_SEC_PREFER
mdefine_line|#define MIB_P_PATH_SEC_PREFER&t;(1&lt;&lt;4)
DECL|macro|MIB_P_PATH_PRIM_PREFER
mdefine_line|#define MIB_P_PATH_PRIM_PREFER&t;(1&lt;&lt;5)
DECL|macro|MIB_P_PATH_CON_PREFER
mdefine_line|#define MIB_P_PATH_CON_PREFER&t;(1&lt;&lt;6)
DECL|macro|MIB_P_PATH_THRU
mdefine_line|#define MIB_P_PATH_THRU&t;&t;(1&lt;&lt;7)
multiline_comment|/*&n; * enum current path&n; */
DECL|macro|MIB_PATH_ISOLATED
mdefine_line|#define MIB_PATH_ISOLATED&t;0
DECL|macro|MIB_PATH_LOCAL
mdefine_line|#define MIB_PATH_LOCAL&t;&t;1
DECL|macro|MIB_PATH_SECONDARY
mdefine_line|#define MIB_PATH_SECONDARY&t;2
DECL|macro|MIB_PATH_PRIMARY
mdefine_line|#define MIB_PATH_PRIMARY&t;3
DECL|macro|MIB_PATH_CONCATENATED
mdefine_line|#define MIB_PATH_CONCATENATED&t;4
DECL|macro|MIB_PATH_THRU
mdefine_line|#define MIB_PATH_THRU&t;&t;5
multiline_comment|/*&n; * enum PMDClass&n; */
DECL|macro|MIB_PMDCLASS_MULTI
mdefine_line|#define MIB_PMDCLASS_MULTI&t;0
DECL|macro|MIB_PMDCLASS_SINGLE1
mdefine_line|#define MIB_PMDCLASS_SINGLE1&t;1
DECL|macro|MIB_PMDCLASS_SINGLE2
mdefine_line|#define MIB_PMDCLASS_SINGLE2&t;2
DECL|macro|MIB_PMDCLASS_SONET
mdefine_line|#define MIB_PMDCLASS_SONET&t;3
DECL|macro|MIB_PMDCLASS_LCF
mdefine_line|#define MIB_PMDCLASS_LCF&t;4
DECL|macro|MIB_PMDCLASS_TP
mdefine_line|#define MIB_PMDCLASS_TP&t;&t;5
DECL|macro|MIB_PMDCLASS_UNKNOWN
mdefine_line|#define MIB_PMDCLASS_UNKNOWN&t;6
DECL|macro|MIB_PMDCLASS_UNSPEC
mdefine_line|#define MIB_PMDCLASS_UNSPEC&t;7
multiline_comment|/*&n; * enum SMTStationStatus&n; */
DECL|macro|MIB_SMT_STASTA_CON
mdefine_line|#define MIB_SMT_STASTA_CON&t;0
DECL|macro|MIB_SMT_STASTA_SEPA
mdefine_line|#define MIB_SMT_STASTA_SEPA&t;1
DECL|macro|MIB_SMT_STASTA_THRU
mdefine_line|#define MIB_SMT_STASTA_THRU&t;2
DECL|struct|fddi_mib
r_struct
id|fddi_mib
(brace
multiline_comment|/*&n;&t; * private&n;&t; */
DECL|member|fddiPRPMFPasswd
id|u_char
id|fddiPRPMFPasswd
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|fddiPRPMFStation
r_struct
id|smt_sid
id|fddiPRPMFStation
suffix:semicolon
macro_line|#ifdef&t;ESS
multiline_comment|/*&n;&t; * private variables for static allocation of the&n;&t; * End Station Support&n;&t; */
DECL|member|fddiESSPayload
id|u_long
id|fddiESSPayload
suffix:semicolon
multiline_comment|/* payload for static alloc */
DECL|member|fddiESSOverhead
id|u_long
id|fddiESSOverhead
suffix:semicolon
multiline_comment|/* frame ov for static alloc */
DECL|member|fddiESSMaxTNeg
id|u_long
id|fddiESSMaxTNeg
suffix:semicolon
multiline_comment|/* maximum of T-NEG */
DECL|member|fddiESSMinSegmentSize
id|u_long
id|fddiESSMinSegmentSize
suffix:semicolon
multiline_comment|/* min size of the sync frames */
DECL|member|fddiESSCategory
id|u_long
id|fddiESSCategory
suffix:semicolon
multiline_comment|/* category for the Alloc req */
DECL|member|fddiESSSynchTxMode
r_int
id|fddiESSSynchTxMode
suffix:semicolon
multiline_comment|/* send all LLC frames as sync */
macro_line|#endif&t;/* ESS */
macro_line|#ifdef&t;SBA
multiline_comment|/*&n;&t; * private variables for the Synchronous Bandwidth Allocator&n;&t; */
DECL|member|fddiSBACommand
r_char
id|fddiSBACommand
suffix:semicolon
multiline_comment|/* holds the parsed SBA cmd */
DECL|member|fddiSBAAvailable
id|u_char
id|fddiSBAAvailable
suffix:semicolon
multiline_comment|/* SBA allocatable value */
macro_line|#endif&t;/* SBA */
multiline_comment|/*&n;&t; * SMT standard mib&n;&t; */
DECL|member|fddiSMTStationId
r_struct
id|smt_sid
id|fddiSMTStationId
suffix:semicolon
DECL|member|fddiSMTOpVersionId
id|u_short
id|fddiSMTOpVersionId
suffix:semicolon
DECL|member|fddiSMTHiVersionId
id|u_short
id|fddiSMTHiVersionId
suffix:semicolon
DECL|member|fddiSMTLoVersionId
id|u_short
id|fddiSMTLoVersionId
suffix:semicolon
DECL|member|fddiSMTManufacturerData
id|u_char
id|fddiSMTManufacturerData
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|fddiSMTUserData
id|u_char
id|fddiSMTUserData
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|fddiSMTMIBVersionId
id|u_short
id|fddiSMTMIBVersionId
suffix:semicolon
multiline_comment|/*&n;&t; * ConfigGrp&n;&t; */
DECL|member|fddiSMTMac_Ct
id|u_char
id|fddiSMTMac_Ct
suffix:semicolon
DECL|member|fddiSMTNonMaster_Ct
id|u_char
id|fddiSMTNonMaster_Ct
suffix:semicolon
DECL|member|fddiSMTMaster_Ct
id|u_char
id|fddiSMTMaster_Ct
suffix:semicolon
DECL|member|fddiSMTAvailablePaths
id|u_char
id|fddiSMTAvailablePaths
suffix:semicolon
DECL|member|fddiSMTConfigCapabilities
id|u_short
id|fddiSMTConfigCapabilities
suffix:semicolon
DECL|member|fddiSMTConfigPolicy
id|u_short
id|fddiSMTConfigPolicy
suffix:semicolon
DECL|member|fddiSMTConnectionPolicy
id|u_short
id|fddiSMTConnectionPolicy
suffix:semicolon
DECL|member|fddiSMTTT_Notify
id|u_short
id|fddiSMTTT_Notify
suffix:semicolon
DECL|member|fddiSMTStatRptPolicy
id|u_char
id|fddiSMTStatRptPolicy
suffix:semicolon
DECL|member|fddiSMTTrace_MaxExpiration
id|u_long
id|fddiSMTTrace_MaxExpiration
suffix:semicolon
DECL|member|fddiSMTPORTIndexes
id|u_short
id|fddiSMTPORTIndexes
(braket
id|NUMPHYS
)braket
suffix:semicolon
DECL|member|fddiSMTMACIndexes
id|u_short
id|fddiSMTMACIndexes
suffix:semicolon
DECL|member|fddiSMTBypassPresent
id|u_char
id|fddiSMTBypassPresent
suffix:semicolon
multiline_comment|/*&n;&t; * StatusGrp&n;&t; */
DECL|member|fddiSMTECMState
id|SMTEnum
id|fddiSMTECMState
suffix:semicolon
DECL|member|fddiSMTCF_State
id|SMTEnum
id|fddiSMTCF_State
suffix:semicolon
DECL|member|fddiSMTStationStatus
id|SMTEnum
id|fddiSMTStationStatus
suffix:semicolon
DECL|member|fddiSMTRemoteDisconnectFlag
id|u_char
id|fddiSMTRemoteDisconnectFlag
suffix:semicolon
DECL|member|fddiSMTPeerWrapFlag
id|u_char
id|fddiSMTPeerWrapFlag
suffix:semicolon
multiline_comment|/*&n;&t; * MIBOperationGrp&n;&t; */
DECL|member|fddiSMTTimeStamp
id|TimeStamp
id|fddiSMTTimeStamp
suffix:semicolon
DECL|member|fddiSMTTransitionTimeStamp
id|TimeStamp
id|fddiSMTTransitionTimeStamp
suffix:semicolon
DECL|member|fddiSMTSetCount
id|SetCountType
id|fddiSMTSetCount
suffix:semicolon
DECL|member|fddiSMTLastSetStationId
r_struct
id|smt_sid
id|fddiSMTLastSetStationId
suffix:semicolon
DECL|struct|fddi_mib_m
r_struct
id|fddi_mib_m
(brace
DECL|member|fddiMACFrameStatusFunctions
id|u_short
id|fddiMACFrameStatusFunctions
suffix:semicolon
DECL|member|fddiMACT_MaxCapabilitiy
id|Timer_2
id|fddiMACT_MaxCapabilitiy
suffix:semicolon
DECL|member|fddiMACTVXCapabilitiy
id|Timer_2
id|fddiMACTVXCapabilitiy
suffix:semicolon
multiline_comment|/* ConfigGrp */
DECL|member|fddiMACMultiple_N
id|u_char
id|fddiMACMultiple_N
suffix:semicolon
multiline_comment|/* private */
DECL|member|fddiMACMultiple_P
id|u_char
id|fddiMACMultiple_P
suffix:semicolon
multiline_comment|/* private */
DECL|member|fddiMACDuplicateAddressCond
id|u_char
id|fddiMACDuplicateAddressCond
suffix:semicolon
multiline_comment|/* private */
DECL|member|fddiMACAvailablePaths
id|u_char
id|fddiMACAvailablePaths
suffix:semicolon
DECL|member|fddiMACCurrentPath
id|u_short
id|fddiMACCurrentPath
suffix:semicolon
DECL|member|fddiMACUpstreamNbr
id|LongAddr
id|fddiMACUpstreamNbr
suffix:semicolon
DECL|member|fddiMACDownstreamNbr
id|LongAddr
id|fddiMACDownstreamNbr
suffix:semicolon
DECL|member|fddiMACOldUpstreamNbr
id|LongAddr
id|fddiMACOldUpstreamNbr
suffix:semicolon
DECL|member|fddiMACOldDownstreamNbr
id|LongAddr
id|fddiMACOldDownstreamNbr
suffix:semicolon
DECL|member|fddiMACDupAddressTest
id|SMTEnum
id|fddiMACDupAddressTest
suffix:semicolon
DECL|member|fddiMACRequestedPaths
id|u_short
id|fddiMACRequestedPaths
suffix:semicolon
DECL|member|fddiMACDownstreamPORTType
id|SMTEnum
id|fddiMACDownstreamPORTType
suffix:semicolon
DECL|member|fddiMACIndex
id|ResId
id|fddiMACIndex
suffix:semicolon
multiline_comment|/* AddressGrp */
DECL|member|fddiMACSMTAddress
id|LongAddr
id|fddiMACSMTAddress
suffix:semicolon
multiline_comment|/* OperationGrp */
DECL|member|fddiMACT_Min
id|Timer_2
id|fddiMACT_Min
suffix:semicolon
multiline_comment|/* private */
DECL|member|fddiMACT_ReqMIB
id|Timer_2
id|fddiMACT_ReqMIB
suffix:semicolon
DECL|member|fddiMACT_Req
id|Timer_2
id|fddiMACT_Req
suffix:semicolon
multiline_comment|/* private */
DECL|member|fddiMACT_Neg
id|Timer_2
id|fddiMACT_Neg
suffix:semicolon
DECL|member|fddiMACT_MaxMIB
id|Timer_2
id|fddiMACT_MaxMIB
suffix:semicolon
DECL|member|fddiMACT_Max
id|Timer_2
id|fddiMACT_Max
suffix:semicolon
multiline_comment|/* private */
DECL|member|fddiMACTvxValueMIB
id|Timer_2
id|fddiMACTvxValueMIB
suffix:semicolon
DECL|member|fddiMACTvxValue
id|Timer_2
id|fddiMACTvxValue
suffix:semicolon
multiline_comment|/* private */
DECL|member|fddiMACT_Pri0
id|Timer_2
id|fddiMACT_Pri0
suffix:semicolon
DECL|member|fddiMACT_Pri1
id|Timer_2
id|fddiMACT_Pri1
suffix:semicolon
DECL|member|fddiMACT_Pri2
id|Timer_2
id|fddiMACT_Pri2
suffix:semicolon
DECL|member|fddiMACT_Pri3
id|Timer_2
id|fddiMACT_Pri3
suffix:semicolon
DECL|member|fddiMACT_Pri4
id|Timer_2
id|fddiMACT_Pri4
suffix:semicolon
DECL|member|fddiMACT_Pri5
id|Timer_2
id|fddiMACT_Pri5
suffix:semicolon
DECL|member|fddiMACT_Pri6
id|Timer_2
id|fddiMACT_Pri6
suffix:semicolon
multiline_comment|/* CountersGrp */
DECL|member|fddiMACFrame_Ct
id|Counter
id|fddiMACFrame_Ct
suffix:semicolon
DECL|member|fddiMACCopied_Ct
id|Counter
id|fddiMACCopied_Ct
suffix:semicolon
DECL|member|fddiMACTransmit_Ct
id|Counter
id|fddiMACTransmit_Ct
suffix:semicolon
DECL|member|fddiMACToken_Ct
id|Counter
id|fddiMACToken_Ct
suffix:semicolon
DECL|member|fddiMACError_Ct
id|Counter
id|fddiMACError_Ct
suffix:semicolon
DECL|member|fddiMACLost_Ct
id|Counter
id|fddiMACLost_Ct
suffix:semicolon
DECL|member|fddiMACTvxExpired_Ct
id|Counter
id|fddiMACTvxExpired_Ct
suffix:semicolon
DECL|member|fddiMACNotCopied_Ct
id|Counter
id|fddiMACNotCopied_Ct
suffix:semicolon
DECL|member|fddiMACRingOp_Ct
id|Counter
id|fddiMACRingOp_Ct
suffix:semicolon
DECL|member|fddiMACSMTCopied_Ct
id|Counter
id|fddiMACSMTCopied_Ct
suffix:semicolon
multiline_comment|/* private */
DECL|member|fddiMACSMTTransmit_Ct
id|Counter
id|fddiMACSMTTransmit_Ct
suffix:semicolon
multiline_comment|/* private */
multiline_comment|/* private for delta ratio */
DECL|member|fddiMACOld_Frame_Ct
id|Counter
id|fddiMACOld_Frame_Ct
suffix:semicolon
DECL|member|fddiMACOld_Copied_Ct
id|Counter
id|fddiMACOld_Copied_Ct
suffix:semicolon
DECL|member|fddiMACOld_Error_Ct
id|Counter
id|fddiMACOld_Error_Ct
suffix:semicolon
DECL|member|fddiMACOld_Lost_Ct
id|Counter
id|fddiMACOld_Lost_Ct
suffix:semicolon
DECL|member|fddiMACOld_NotCopied_Ct
id|Counter
id|fddiMACOld_NotCopied_Ct
suffix:semicolon
multiline_comment|/* FrameErrorConditionGrp */
DECL|member|fddiMACFrameErrorThreshold
id|u_short
id|fddiMACFrameErrorThreshold
suffix:semicolon
DECL|member|fddiMACFrameErrorRatio
id|u_short
id|fddiMACFrameErrorRatio
suffix:semicolon
multiline_comment|/* NotCopiedConditionGrp */
DECL|member|fddiMACNotCopiedThreshold
id|u_short
id|fddiMACNotCopiedThreshold
suffix:semicolon
DECL|member|fddiMACNotCopiedRatio
id|u_short
id|fddiMACNotCopiedRatio
suffix:semicolon
multiline_comment|/* StatusGrp */
DECL|member|fddiMACRMTState
id|SMTEnum
id|fddiMACRMTState
suffix:semicolon
DECL|member|fddiMACDA_Flag
id|SMTFlag
id|fddiMACDA_Flag
suffix:semicolon
DECL|member|fddiMACUNDA_Flag
id|SMTFlag
id|fddiMACUNDA_Flag
suffix:semicolon
DECL|member|fddiMACFrameErrorFlag
id|SMTFlag
id|fddiMACFrameErrorFlag
suffix:semicolon
DECL|member|fddiMACNotCopiedFlag
id|SMTFlag
id|fddiMACNotCopiedFlag
suffix:semicolon
DECL|member|fddiMACMA_UnitdataAvailable
id|SMTFlag
id|fddiMACMA_UnitdataAvailable
suffix:semicolon
DECL|member|fddiMACHardwarePresent
id|SMTFlag
id|fddiMACHardwarePresent
suffix:semicolon
DECL|member|fddiMACMA_UnitdataEnable
id|SMTFlag
id|fddiMACMA_UnitdataEnable
suffix:semicolon
DECL|member|m
)brace
id|m
(braket
id|NUMMACS
)braket
suffix:semicolon
DECL|macro|MAC0
mdefine_line|#define MAC0&t;0
DECL|struct|fddi_mib_a
r_struct
id|fddi_mib_a
(brace
DECL|member|fddiPATHIndex
id|ResId
id|fddiPATHIndex
suffix:semicolon
DECL|member|fddiPATHSbaPayload
id|u_long
id|fddiPATHSbaPayload
suffix:semicolon
DECL|member|fddiPATHSbaOverhead
id|u_long
id|fddiPATHSbaOverhead
suffix:semicolon
multiline_comment|/* fddiPATHConfiguration is built on demand */
multiline_comment|/* u_long&t;&t;fddiPATHConfiguration ; */
DECL|member|fddiPATHT_Rmode
id|Timer
id|fddiPATHT_Rmode
suffix:semicolon
DECL|member|fddiPATHSbaAvailable
id|u_long
id|fddiPATHSbaAvailable
suffix:semicolon
DECL|member|fddiPATHTVXLowerBound
id|Timer_2
id|fddiPATHTVXLowerBound
suffix:semicolon
DECL|member|fddiPATHT_MaxLowerBound
id|Timer_2
id|fddiPATHT_MaxLowerBound
suffix:semicolon
DECL|member|fddiPATHMaxT_Req
id|Timer_2
id|fddiPATHMaxT_Req
suffix:semicolon
DECL|member|a
)brace
id|a
(braket
id|NUMPATHS
)braket
suffix:semicolon
DECL|macro|PATH0
mdefine_line|#define PATH0&t;0
DECL|struct|fddi_mib_p
r_struct
id|fddi_mib_p
(brace
multiline_comment|/* ConfigGrp */
DECL|member|fddiPORTMy_Type
id|SMTEnum
id|fddiPORTMy_Type
suffix:semicolon
DECL|member|fddiPORTNeighborType
id|SMTEnum
id|fddiPORTNeighborType
suffix:semicolon
DECL|member|fddiPORTConnectionPolicies
id|u_char
id|fddiPORTConnectionPolicies
suffix:semicolon
r_struct
(brace
DECL|member|T_val
id|u_char
id|T_val
suffix:semicolon
DECL|member|R_val
id|u_char
id|R_val
suffix:semicolon
DECL|member|fddiPORTMacIndicated
)brace
id|fddiPORTMacIndicated
suffix:semicolon
DECL|member|fddiPORTCurrentPath
id|SMTEnum
id|fddiPORTCurrentPath
suffix:semicolon
multiline_comment|/* must be 4: is 32 bit in SMT format&n;&t;&t; * indices :&n;&t;&t; *&t;1&t;none&n;&t;&t; *&t;2&t;tree&n;&t;&t; *&t;3&t;peer&n;&t;&t; */
DECL|member|fddiPORTRequestedPaths
id|u_char
id|fddiPORTRequestedPaths
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|fddiPORTMACPlacement
id|u_short
id|fddiPORTMACPlacement
suffix:semicolon
DECL|member|fddiPORTAvailablePaths
id|u_char
id|fddiPORTAvailablePaths
suffix:semicolon
DECL|member|fddiPORTConnectionCapabilities
id|u_char
id|fddiPORTConnectionCapabilities
suffix:semicolon
DECL|member|fddiPORTPMDClass
id|SMTEnum
id|fddiPORTPMDClass
suffix:semicolon
DECL|member|fddiPORTIndex
id|ResId
id|fddiPORTIndex
suffix:semicolon
multiline_comment|/* OperationGrp */
DECL|member|fddiPORTMaint_LS
id|SMTEnum
id|fddiPORTMaint_LS
suffix:semicolon
DECL|member|fddiPORTPC_LS
id|SMTEnum
id|fddiPORTPC_LS
suffix:semicolon
DECL|member|fddiPORTBS_Flag
id|u_char
id|fddiPORTBS_Flag
suffix:semicolon
multiline_comment|/* ErrorCtrsGrp */
DECL|member|fddiPORTLCTFail_Ct
id|Counter
id|fddiPORTLCTFail_Ct
suffix:semicolon
DECL|member|fddiPORTEBError_Ct
id|Counter
id|fddiPORTEBError_Ct
suffix:semicolon
DECL|member|fddiPORTOldEBError_Ct
id|Counter
id|fddiPORTOldEBError_Ct
suffix:semicolon
multiline_comment|/* LerGrp */
DECL|member|fddiPORTLem_Reject_Ct
id|Counter
id|fddiPORTLem_Reject_Ct
suffix:semicolon
DECL|member|fddiPORTLem_Ct
id|Counter
id|fddiPORTLem_Ct
suffix:semicolon
DECL|member|fddiPORTLer_Estimate
id|u_char
id|fddiPORTLer_Estimate
suffix:semicolon
DECL|member|fddiPORTLer_Cutoff
id|u_char
id|fddiPORTLer_Cutoff
suffix:semicolon
DECL|member|fddiPORTLer_Alarm
id|u_char
id|fddiPORTLer_Alarm
suffix:semicolon
multiline_comment|/* StatusGrp */
DECL|member|fddiPORTConnectState
id|SMTEnum
id|fddiPORTConnectState
suffix:semicolon
DECL|member|fddiPORTPCMState
id|SMTEnum
id|fddiPORTPCMState
suffix:semicolon
multiline_comment|/* real value */
DECL|member|fddiPORTPCMStateX
id|SMTEnum
id|fddiPORTPCMStateX
suffix:semicolon
multiline_comment|/* value for MIB */
DECL|member|fddiPORTPC_Withhold
id|SMTEnum
id|fddiPORTPC_Withhold
suffix:semicolon
DECL|member|fddiPORTHardwarePresent
id|SMTFlag
id|fddiPORTHardwarePresent
suffix:semicolon
DECL|member|fddiPORTLerFlag
id|u_char
id|fddiPORTLerFlag
suffix:semicolon
DECL|member|fddiPORTMultiple_U
id|u_char
id|fddiPORTMultiple_U
suffix:semicolon
multiline_comment|/* private */
DECL|member|fddiPORTMultiple_P
id|u_char
id|fddiPORTMultiple_P
suffix:semicolon
multiline_comment|/* private */
DECL|member|fddiPORTEB_Condition
id|u_char
id|fddiPORTEB_Condition
suffix:semicolon
multiline_comment|/* private */
DECL|member|p
)brace
id|p
(braket
id|NUMPHYS
)braket
suffix:semicolon
r_struct
(brace
DECL|member|fddiPRIVECF_Req_Rx
id|Counter
id|fddiPRIVECF_Req_Rx
suffix:semicolon
multiline_comment|/* ECF req received */
DECL|member|fddiPRIVECF_Reply_Rx
id|Counter
id|fddiPRIVECF_Reply_Rx
suffix:semicolon
multiline_comment|/* ECF repl received */
DECL|member|fddiPRIVECF_Req_Tx
id|Counter
id|fddiPRIVECF_Req_Tx
suffix:semicolon
multiline_comment|/* ECF req transm */
DECL|member|fddiPRIVECF_Reply_Tx
id|Counter
id|fddiPRIVECF_Reply_Tx
suffix:semicolon
multiline_comment|/* ECF repl transm */
DECL|member|fddiPRIVPMF_Get_Rx
id|Counter
id|fddiPRIVPMF_Get_Rx
suffix:semicolon
multiline_comment|/* PMF Get rec */
DECL|member|fddiPRIVPMF_Set_Rx
id|Counter
id|fddiPRIVPMF_Set_Rx
suffix:semicolon
multiline_comment|/* PMF Set rec */
DECL|member|fddiPRIVRDF_Rx
id|Counter
id|fddiPRIVRDF_Rx
suffix:semicolon
multiline_comment|/* RDF received */
DECL|member|fddiPRIVRDF_Tx
id|Counter
id|fddiPRIVRDF_Tx
suffix:semicolon
multiline_comment|/* RDF transmitted */
DECL|member|priv
)brace
id|priv
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * OIDs for statistics&n; */
DECL|macro|SMT_OID_CF_STATE
mdefine_line|#define&t;SMT_OID_CF_STATE&t;1&t;/* fddiSMTCF_State */
DECL|macro|SMT_OID_PCM_STATE_A
mdefine_line|#define&t;SMT_OID_PCM_STATE_A&t;2&t;/* fddiPORTPCMState port A */
DECL|macro|SMT_OID_PCM_STATE_B
mdefine_line|#define&t;SMT_OID_PCM_STATE_B&t;17&t;/* fddiPORTPCMState port B */
DECL|macro|SMT_OID_RMT_STATE
mdefine_line|#define&t;SMT_OID_RMT_STATE&t;3&t;/* fddiMACRMTState */
DECL|macro|SMT_OID_UNA
mdefine_line|#define&t;SMT_OID_UNA&t;&t;4&t;/* fddiMACUpstreamNbr */
DECL|macro|SMT_OID_DNA
mdefine_line|#define&t;SMT_OID_DNA&t;&t;5&t;/* fddiMACOldDownstreamNbr */
DECL|macro|SMT_OID_ERROR_CT
mdefine_line|#define&t;SMT_OID_ERROR_CT&t;6&t;/* fddiMACError_Ct */
DECL|macro|SMT_OID_LOST_CT
mdefine_line|#define&t;SMT_OID_LOST_CT&t;&t;7&t;/* fddiMACLost_Ct */
DECL|macro|SMT_OID_LEM_CT
mdefine_line|#define&t;SMT_OID_LEM_CT&t;&t;8&t;/* fddiPORTLem_Ct */
DECL|macro|SMT_OID_LEM_CT_A
mdefine_line|#define&t;SMT_OID_LEM_CT_A&t;11&t;/* fddiPORTLem_Ct port A */
DECL|macro|SMT_OID_LEM_CT_B
mdefine_line|#define&t;SMT_OID_LEM_CT_B&t;12&t;/* fddiPORTLem_Ct port B */
DECL|macro|SMT_OID_LCT_FAIL_CT
mdefine_line|#define&t;SMT_OID_LCT_FAIL_CT&t;9&t;/* fddiPORTLCTFail_Ct */
DECL|macro|SMT_OID_LCT_FAIL_CT_A
mdefine_line|#define&t;SMT_OID_LCT_FAIL_CT_A&t;13&t;/* fddiPORTLCTFail_Ct port A */
DECL|macro|SMT_OID_LCT_FAIL_CT_B
mdefine_line|#define&t;SMT_OID_LCT_FAIL_CT_B&t;14&t;/* fddiPORTLCTFail_Ct port B */
DECL|macro|SMT_OID_LEM_REJECT_CT
mdefine_line|#define&t;SMT_OID_LEM_REJECT_CT&t;10&t;/* fddiPORTLem_Reject_Ct */
DECL|macro|SMT_OID_LEM_REJECT_CT_A
mdefine_line|#define&t;SMT_OID_LEM_REJECT_CT_A&t;15&t;/* fddiPORTLem_Reject_Ct port A */
DECL|macro|SMT_OID_LEM_REJECT_CT_B
mdefine_line|#define&t;SMT_OID_LEM_REJECT_CT_B&t;16&t;/* fddiPORTLem_Reject_Ct port B */
multiline_comment|/*&n; * SK MIB&n; */
DECL|macro|SMT_OID_ECF_REQ_RX
mdefine_line|#define SMT_OID_ECF_REQ_RX&t;20&t;/* ECF requests received */
DECL|macro|SMT_OID_ECF_REPLY_RX
mdefine_line|#define SMT_OID_ECF_REPLY_RX&t;21&t;/* ECF replies received */
DECL|macro|SMT_OID_ECF_REQ_TX
mdefine_line|#define SMT_OID_ECF_REQ_TX&t;22&t;/* ECF requests transmitted */
DECL|macro|SMT_OID_ECF_REPLY_TX
mdefine_line|#define SMT_OID_ECF_REPLY_TX&t;23&t;/* ECF replies transmitted */
DECL|macro|SMT_OID_PMF_GET_RX
mdefine_line|#define SMT_OID_PMF_GET_RX&t;24&t;/* PMF get requests received */
DECL|macro|SMT_OID_PMF_SET_RX
mdefine_line|#define SMT_OID_PMF_SET_RX&t;25&t;/* PMF set requests received */
DECL|macro|SMT_OID_RDF_RX
mdefine_line|#define SMT_OID_RDF_RX&t;&t;26&t;/* RDF received */
DECL|macro|SMT_OID_RDF_TX
mdefine_line|#define SMT_OID_RDF_TX&t;&t;27&t;/* RDF transmitted */
eof
