multiline_comment|/*&n; *&t; Aironet 4500 Pcmcia driver&n; *&n; *&t;&t;Elmer Joandi, Januar 1999&n; *&t;Copyright Elmer Joandi, all rights restricted&n; *&t;&n; *&n; *&t;Revision 0.1 ,started  30.12.1998&n; *&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &quot;aironet4500.h&quot;
DECL|macro|awc_RID_gen_RidLen
mdefine_line|#define awc_RID_gen_RidLen &t;&t;&t;&t;{(const struct aironet4500_rid_selector *)&amp;aironet4500_RID_Select_General_Config,0x0000, 8,1,1,1,0, 0xffffffff,0x0000, &quot;Length of RID&quot; }
DECL|macro|awc_RID_gen_OperatingMode_adhoc
mdefine_line|#define awc_RID_gen_OperatingMode_adhoc &t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0002,16,1,1,0,0, 0x00000003,0x0000,&quot;Opmode IBSS Adhoc operation&quot; } 
singleline_comment|// Without AP
DECL|macro|awc_RID_gen_OperatingMode_Infrastructure
mdefine_line|#define awc_RID_gen_OperatingMode_Infrastructure &t;{&amp;aironet4500_RID_Select_General_Config,0x0002,16,1,1,0,0, 0x00000003,0x0001,&quot;Opmode Infrastructure Station operation&quot; }
singleline_comment|// With AP
DECL|macro|awc_RID_gen_OperatingMode_AP
mdefine_line|#define awc_RID_gen_OperatingMode_AP&t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0002,16,1,1,0,0, 0x00000003,0x0002,&quot;Opmode Access Point&quot; } 
singleline_comment|// Aironet doesnt release info on use 
DECL|macro|awc_RID_gen_OperatingMode_AP_and_repeater
mdefine_line|#define awc_RID_gen_OperatingMode_AP_and_repeater &t;{&amp;aironet4500_RID_Select_General_Config,0x0002,16,1,1,0,0, 0x00000003,0x0003,&quot;Opmode Access Point and Repeater&quot; } 
singleline_comment|// no info
DECL|macro|awc_RID_gen_OperatingMode_No_payload_modify
mdefine_line|#define awc_RID_gen_OperatingMode_No_payload_modify&t;{&amp;aironet4500_RID_Select_General_Config,0x0002,16,1,1,0,0, 0x00000100,0x0100,&quot;Opmode Payload without modify&quot; } 
DECL|macro|awc_RID_gen_OperatingMode_LLC_802_3_convert
mdefine_line|#define awc_RID_gen_OperatingMode_LLC_802_3_convert&t;{&amp;aironet4500_RID_Select_General_Config,0x0002,16,1,1,0,0, 0x00000100,0x0000,&quot;Opmode LLC -&gt; 802.3 convert&quot; }
DECL|macro|awc_RID_gen_OperatingMode_proprietary_ext
mdefine_line|#define awc_RID_gen_OperatingMode_proprietary_ext &t;{&amp;aironet4500_RID_Select_General_Config,0x0002,16,1,1,0,0, 0x00000200,0x0200,&quot;Opmode Aironet Extentsions enabled&quot; } 
singleline_comment|// neened for 11Mbps
DECL|macro|awc_RID_gen_OperatingMode_no_proprietary_ext
mdefine_line|#define awc_RID_gen_OperatingMode_no_proprietary_ext &t;{&amp;aironet4500_RID_Select_General_Config,0x0002,16,1,1,0,0,0x00000200,0x0000,&quot;Opmode Aironet Extentsions disabled&quot; }
DECL|macro|awc_RID_gen_OperatingMode_AP_ext
mdefine_line|#define awc_RID_gen_OperatingMode_AP_ext &t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0002,16,1,1,0,0, 0x00000400,0x0400,&quot;Opmode AP Extentsions enabled&quot; }&t;
singleline_comment|// no info
DECL|macro|awc_RID_gen_OperatingMode_no_AP_ext
mdefine_line|#define awc_RID_gen_OperatingMode_no_AP_ext&t; &t;{&amp;aironet4500_RID_Select_General_Config,0x0002,16,1,1,0,0, 0x00000400,0x0000,&quot;Opmode AP Extentsions disabled&quot; }
DECL|macro|awc_RID_gen_ReceiveMode
mdefine_line|#define awc_RID_gen_ReceiveMode &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0004,16,1,1,0,0,0x0000ffff,0x0000,&quot;RX Mode&quot;}
DECL|macro|awc_RID_gen_ReceiveMode_BMA
mdefine_line|#define awc_RID_gen_ReceiveMode_BMA &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0004,16,1,1,0,0,0x0000000f,0x0000,&quot;RX Mode BC MC ADDR&quot;}
DECL|macro|awc_RID_gen_ReceiveMode_BA
mdefine_line|#define awc_RID_gen_ReceiveMode_BA &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0004,16,1,1,0,0,0x0000000f,0x0001,&quot;RX Mode BC ADDR&quot;}
DECL|macro|awc_RID_gen_ReceiveMode_A
mdefine_line|#define awc_RID_gen_ReceiveMode_A &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0004,16,1,1,0,0,0x0000000f,0x0002,&quot;RX Mode ADDR&quot;}
DECL|macro|awc_RID_gen_ReceiveMode_802_11_monitor
mdefine_line|#define awc_RID_gen_ReceiveMode_802_11_monitor&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0004,16,1,1,0,0,0x0000000f,0x0003,&quot;RX Mode 802.11 Monitor current BSSID&quot;}
DECL|macro|awc_RID_gen_ReceiveMode_802_11_any_monitor
mdefine_line|#define awc_RID_gen_ReceiveMode_802_11_any_monitor &t;{&amp;aironet4500_RID_Select_General_Config,0x0004,16,1,1,0,0,0x0000000f,0x0004,&quot;RX Mode 802.11 Monitor any BSSID&quot;}
DECL|macro|awc_RID_gen_ReceiveMode_LAN_monitor
mdefine_line|#define awc_RID_gen_ReceiveMode_LAN_monitor &t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0004,16,1,1,0,0,0x0000000f,0x0005,&quot;RX Mode LAN Monitor current BSSID&quot;}
DECL|macro|awc_RID_gen_ReceiveMode_802_3_hdr_disable
mdefine_line|#define awc_RID_gen_ReceiveMode_802_3_hdr_disable &t;{&amp;aironet4500_RID_Select_General_Config,0x0004,16,1,1,0,0,0x00000100,0x0100,&quot;RX Mode Disable RX 802.3 Header&quot;}
DECL|macro|awc_RID_gen_ReceiveMode_802_3_hdr_enable
mdefine_line|#define awc_RID_gen_ReceiveMode_802_3_hdr_enable &t;{&amp;aironet4500_RID_Select_General_Config,0x0004,16,1,1,0,0,0x00000100,0x0000,&quot;RX Mode Enable RX 802.3 header&quot;}
DECL|macro|awc_RID_gen_Fragmentation_threshold
mdefine_line|#define awc_RID_gen_Fragmentation_threshold&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0006,16,1,1,0,0,0x0000ffff,0x0000,&quot;Fragmentation Threshold&quot;}&t;&t;
singleline_comment|// treshold of packet size starting to be fragmented
DECL|macro|awc_RID_gen_RTS_threshold
mdefine_line|#define awc_RID_gen_RTS_threshold &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0008,16,1,1,0,0,0xffff,0x0000,&quot;RTS Threshold&quot;}&t;
singleline_comment|// packet size, larger ones get sent with RTS/CTS
DECL|macro|awc_RID_gen_Station_Mac_Id
mdefine_line|#define awc_RID_gen_Station_Mac_Id &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x000A, 8,6,1,0,0,0xff,0,&quot;Station MAC Id&quot;}
DECL|macro|awc_RID_gen_Supported_rates
mdefine_line|#define awc_RID_gen_Supported_rates &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0010, 8,8,1,0,1,0xff,0x00,&quot;Supported Rates&quot;}&t;
singleline_comment|// Hex encoded 500kbps 
DECL|macro|awc_RID_gen_Basic_Rate
mdefine_line|#define awc_RID_gen_Basic_Rate &t;&t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0010, 8,1,1,0,1,0x80,0x80,&quot;Basic Rate&quot;}&t;
singleline_comment|// if 0x80 bit is set
DECL|macro|awc_RID_gen_Rate_500kbps
mdefine_line|#define awc_RID_gen_Rate_500kbps &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0010, 8,1,1,0,1,0x7f,0x01,&quot;Rate 500kbps&quot;}
DECL|macro|awc_RID_gen_Rate_1Mbps
mdefine_line|#define awc_RID_gen_Rate_1Mbps &t;&t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0010, 8,1,1,0,1,0x7f,0x02,&quot;Rate 1Mbps&quot;}
DECL|macro|awc_RID_gen_Rate_2Mbps
mdefine_line|#define awc_RID_gen_Rate_2Mbps &t;&t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0010, 8,1,1,0,1,0x7f,0x04,&quot;Rate 2Mbps&quot;}
DECL|macro|awc_RID_gen_Rate_4Mbps
mdefine_line|#define awc_RID_gen_Rate_4Mbps &t;&t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0010, 8,1,1,0,1,0x7f,0x08,&quot;Rate 4Mbps&quot;}
DECL|macro|awc_RID_gen_Rate_5Mbps
mdefine_line|#define awc_RID_gen_Rate_5Mbps &t;&t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0010, 8,1,1,0,1,0x7f,0x0B,&quot;Rate 5.5Mbps&quot;}
DECL|macro|awc_RID_gen_Rate_10Mbps
mdefine_line|#define awc_RID_gen_Rate_10Mbps &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0010, 8,1,1,0,1,0x7f,0x14,&quot;Rate 10Mbps&quot;}
DECL|macro|awc_RID_gen_Rate_11Mbps
mdefine_line|#define awc_RID_gen_Rate_11Mbps &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0010, 8,1,1,0,1,0x7f,0x16,&quot;Rate 11Mbps&quot;}
DECL|macro|awc_RID_gen_BasicRate_500kbps
mdefine_line|#define awc_RID_gen_BasicRate_500kbps &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0010, 8,1,1,0,1,0xff,0x81,&quot;BasicRate 500kbps&quot;}
DECL|macro|awc_RID_gen_BasicRate_1Mbps
mdefine_line|#define awc_RID_gen_BasicRate_1Mbps &t;&t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0010, 8,1,1,0,1,0xff,0x82,&quot;BasicRate 1Mbps&quot;}
DECL|macro|awc_RID_gen_BasicRate_2Mbps
mdefine_line|#define awc_RID_gen_BasicRate_2Mbps &t;&t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0010, 8,1,1,0,1,0xff,0x84,&quot;BasicRate 2Mbps&quot;}
DECL|macro|awc_RID_gen_BasicRate_4Mbps
mdefine_line|#define awc_RID_gen_BasicRate_4Mbps &t;&t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0010, 8,1,1,0,1,0xff,0x88,&quot;BasicRate 4Mbps&quot;}
DECL|macro|awc_RID_gen_BasicRate_5Mbps
mdefine_line|#define awc_RID_gen_BasicRate_5Mbps &t;&t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0010, 8,1,1,0,1,0xff,0x8B,&quot;BasicRate 5.5Mbps&quot;}
DECL|macro|awc_RID_gen_BasicRate_10Mbps
mdefine_line|#define awc_RID_gen_BasicRate_10Mbps &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0010, 8,1,1,0,1,0xff,0x94,&quot;BasicRate 10Mbps&quot;}
DECL|macro|awc_RID_gen_BasicRate_11Mbps
mdefine_line|#define awc_RID_gen_BasicRate_11Mbps &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0010, 8,1,1,0,1,0xff,0x96,&quot;BasicRate 11Mbps&quot;}
DECL|macro|awc_RID_gen_Long_retry_limit
mdefine_line|#define awc_RID_gen_Long_retry_limit &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0018,16, 1,1,0,0,0xffff,0,&quot;Short Retry Limit&quot;}
DECL|macro|awc_RID_gen_Short_retry_limit
mdefine_line|#define awc_RID_gen_Short_retry_limit &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x001A,16, 1,1,0,0,0xffff,0,&quot;Long Retry Limit&quot;}
DECL|macro|awc_RID_gen_Tx_MSDU_lifetime
mdefine_line|#define awc_RID_gen_Tx_MSDU_lifetime &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x001C,16, 1,1000,0,0,0xffff,0,&quot;TX MSDU Lifetime&quot;}
DECL|macro|awc_RID_gen_Rx_MSDU_lifetime
mdefine_line|#define awc_RID_gen_Rx_MSDU_lifetime &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x001E,16, 1,1000,0,0,0xffff,0,&quot;RX MSDU Lifetime&quot;}
DECL|macro|awc_RID_gen_Stationary
mdefine_line|#define awc_RID_gen_Stationary &t;&t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0020,16, 1,1,0,0,0xffff,0,&quot;Stationary&quot;}
DECL|macro|awc_RID_gen_BC_MC_Ordering
mdefine_line|#define awc_RID_gen_BC_MC_Ordering &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0022,16, 1,1,0,0,0xffff,0,&quot;Strictly order Bcast and Mcast&quot;}
DECL|macro|awc_RID_gen_Device_type
mdefine_line|#define awc_RID_gen_Device_type &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0024,16, 1,1,1,0,0xffff,0x00,&quot;Radio Type&quot;}
DECL|macro|awc_RID_gen_Reserved_0x0026
mdefine_line|#define awc_RID_gen_Reserved_0x0026 &t;&t;&t;{&amp;aironet4500_RID_Select_General_Config,0x0026, 8,10,1,0,0,0xff,0,&quot;Reserved0x28&quot;}
singleline_comment|//SCANNING/ASSOCIATING
DECL|macro|awc_RID_gen_ScanMode
mdefine_line|#define awc_RID_gen_ScanMode&t;&t;&t;&t;awc_def_gen_RID(0x0030,&quot;ScanMode&quot;,&t;&t;16,0xf,0, NULL)
DECL|macro|awc_RID_gen_ScanMode_Active
mdefine_line|#define awc_RID_gen_ScanMode_Active &t;&t;&t;awc_def_gen_RID(0x0030,&quot;ScanMode Active&quot;,&t;&t;16,0xf,0, &quot;Active&quot;)
DECL|macro|awc_RID_gen_ScanMode_Passive
mdefine_line|#define awc_RID_gen_ScanMode_Passive &t;&t;&t;awc_def_gen_RID(0x0030,&quot;ScanMode Passive&quot;,&t;&t;16,0xf,1, &quot;Passive&quot;)
DECL|macro|awc_RID_gen_ScanMode_Aironet_ext
mdefine_line|#define awc_RID_gen_ScanMode_Aironet_ext&t;&t;awc_def_gen_RID(0x0030,&quot;ScanMode Aironet Ext&quot;,&t;&t;16,0xf,2, &quot;Aironet Ext&quot;)
DECL|macro|awc_RID_gen_ProbeDelay
mdefine_line|#define awc_RID_gen_ProbeDelay &t;&t;&t;&t;awc_def_gen_RID(0x0032,&quot;ProbeDelay&quot;,&t;&t;16,0xffff,0,&quot; msek&quot;) &t;&t;
singleline_comment|//                 Time ms to wait after switching to a channel for clear channel assessment.
DECL|macro|awc_RID_gen_ProbeEnergyTimeout
mdefine_line|#define awc_RID_gen_ProbeEnergyTimeout &t;&t;&t;awc_def_gen_RID(0x0034,&quot;ProbeEnergyTimeout&quot;,&t;16,0xffff,0,&quot;msek&quot;) &t;
singleline_comment|//          Time to wait for energy after an active probe.
DECL|macro|awc_RID_gen_ProbeResponseTimeout
mdefine_line|#define awc_RID_gen_ProbeResponseTimeout&t;&t;awc_def_gen_RID(0x0036,&quot;ProbeResponseTimeout&quot;,&t;16,0xffff,0,&quot;msek&quot;) &t;
singleline_comment|// Time to wait for a probe response after energy detected.
DECL|macro|awc_RID_gen_BeaconListenTimeout
mdefine_line|#define awc_RID_gen_BeaconListenTimeout &t;&t;awc_def_gen_RID(0x0038,&quot;BeaconListenTimeout&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//    0 default    40          Time to listen for a beacon on each channel.
DECL|macro|awc_RID_gen_IbssJoinNetTimeout
mdefine_line|#define awc_RID_gen_IbssJoinNetTimeout &t;&t;&t;awc_def_gen_RID(0x003A,&quot;IbssJoinNetTimeout&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//       0 default    10000       IBSS: Time to scan for an IBSS before forming a
DECL|macro|awc_RID_gen_AuthenticationTimeout
mdefine_line|#define awc_RID_gen_AuthenticationTimeout &t;&t;awc_def_gen_RID(0x003C,&quot;AuthenticationTimeout&quot;,16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//       0 default    2000        Time limit after which an authentication sequence will
DECL|macro|awc_RID_gen_AuthenticationType
mdefine_line|#define awc_RID_gen_AuthenticationType &t;&t;&t;awc_def_gen_RID(0x003E,&quot;AuthenticationType&quot;,&t;16,0xffff,0,NULL)&t;
singleline_comment|//       0 default    1 (open) //    Selects the desired authentication and privacy methods.&t;&t; 
DECL|macro|awc_RID_gen_AuthenticationType_None
mdefine_line|#define awc_RID_gen_AuthenticationType_None &t;&t;awc_def_gen_RID(0x003E,&quot;AuthenticationType None&quot;,&t;16,0xffff,0,&quot;None&quot;) &t;
singleline_comment|//   0x00 = None&t;
DECL|macro|awc_RID_gen_AuthenticationType_Open
mdefine_line|#define awc_RID_gen_AuthenticationType_Open&t;&t;awc_def_gen_RID(0x003E,&quot;AuthenticationType Open&quot;,&t;16,0xffff,1,&quot;Open&quot;) &t;
singleline_comment|//             0x01 = Open
DECL|macro|awc_RID_gen_AuthenticationType_Shared
mdefine_line|#define awc_RID_gen_AuthenticationType_Shared&t;&t;awc_def_gen_RID(0x003E,&quot;AuthenticationType Shared-Key&quot;,&t;16,0xffff,2,&quot;Shared-Key&quot;)  &t;
singleline_comment|//     0x02 = Shared-Key
DECL|macro|awc_RID_gen_AuthenticationType_Exclude_Open
mdefine_line|#define awc_RID_gen_AuthenticationType_Exclude_Open &t;awc_def_gen_RID(0x003E,&quot;AuthenticationType Exclude Open&quot;,&t;16,0xffff,4,&quot;Exclude Open&quot;)   &t;
singleline_comment|//              0x04 = Exclude Unencrypted
DECL|macro|awc_RID_gen_AssociationTimeout
mdefine_line|#define awc_RID_gen_AssociationTimeout &t;&t;&t;awc_def_gen_RID(0x0040,&quot;AssociationTimeout&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//       0 default    2000        ESS: Time limit after which an association sequence
DECL|macro|awc_RID_gen_SpecifiedAPtimeout
mdefine_line|#define awc_RID_gen_SpecifiedAPtimeout &t;&t;&t;awc_def_gen_RID(0x0042,&quot;SpecifiedAPtimeout&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//       0 default    10000       0 selects the factory default [~10 sec].
DECL|macro|awc_RID_gen_OfflineScanInterval
mdefine_line|#define awc_RID_gen_OfflineScanInterval &t;&t;awc_def_gen_RID(0x0044,&quot;OfflineScanInterval&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//       0            0           0 disables offline scanning.(kus)        The time period between offline scans.
DECL|macro|awc_RID_gen_OfflineScanDuration
mdefine_line|#define awc_RID_gen_OfflineScanDuration &t;&t;awc_def_gen_RID(0x0046,&quot;OfflineScanDuration&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//       0            0           0 disables offline scanning. //    (kus)        The duration of an offline scan.
DECL|macro|awc_RID_gen_LinkLossDelay
mdefine_line|#define awc_RID_gen_LinkLossDelay &t;&t;&t;awc_def_gen_RID(0x0048,&quot;LinkLossDelay&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//       0  0 Time to delay before reporting a loss of association
DECL|macro|awc_RID_gen_MaxBeaconLostTime
mdefine_line|#define awc_RID_gen_MaxBeaconLostTime &t;&t;&t;awc_def_gen_RID(0x004A,&quot;MaxBeaconLostTime&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//      0 default    500        If no beacons are received for this time period, the unit
DECL|macro|awc_RID_gen_RefreshInterval
mdefine_line|#define awc_RID_gen_RefreshInterval &t;&t;&t;awc_def_gen_RID(0x004C,&quot;RefreshInterval&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;&t;
singleline_comment|//      0 default    10000      At the specified interval, the station will send a refresh
singleline_comment|//POWER SAVE OPERATION
DECL|macro|awc_RID_gen_PowerSaveMode
mdefine_line|#define awc_RID_gen_PowerSaveMode &t;&t;&t;awc_def_gen_RID(0x0050,&quot;PowerSaveMode&quot;,&t;16,0xffff,0,NULL) &t;&t;
singleline_comment|//      0  0Note, for IBSS there is only one PSP mode and it is only enabled if the ATIMwindow is non-zero.
DECL|macro|awc_RID_gen_PowerSaveMode_CAM
mdefine_line|#define awc_RID_gen_PowerSaveMode_CAM &t;&t;awc_def_gen_RID(0x0050,&quot;PowerSaveMode CAM&quot;,&t;16,0x000f,0,&quot;CAM&quot;) &t;
singleline_comment|// 0 = CAM
DECL|macro|awc_RID_gen_PowerSaveMode_PSP
mdefine_line|#define awc_RID_gen_PowerSaveMode_PSP &t;&t;awc_def_gen_RID(0x0050,&quot;PowerSaveMode PSP&quot;,&t;16,0x000f,1,&quot;PSP&quot;) &t;
singleline_comment|// 1 = PSP
DECL|macro|awc_RID_gen_PowerSaveMode_Fast_PSP
mdefine_line|#define awc_RID_gen_PowerSaveMode_Fast_PSP&t;&t;awc_def_gen_RID(0x0050,&quot;PowerSaveMode Fast PSP&quot;,&t;16,0x000f,2,&quot;Fast PSP&quot;)&t;
singleline_comment|//2 = PSP-CAM [FASTPSP]
DECL|macro|awc_RID_gen_SleepForDTIMs
mdefine_line|#define awc_RID_gen_SleepForDTIMs &t;&t;&t;awc_def_gen_RID(0x0052,&quot;SleepForDTIMs&quot;,&t;16,0xffff,0,&quot;DTIMs&quot;)&t;
singleline_comment|//      0  0If non-zero, the station may sleep through DTIMs; this
DECL|macro|awc_RID_gen_ListenInterval
mdefine_line|#define awc_RID_gen_ListenInterval &t;&t;&t;awc_def_gen_RID(0x0054,&quot;ListenInterval&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;&t;
singleline_comment|//      0 default    200 kus    Maximum time to awaken for TIMs. 0 selects factory
DECL|macro|awc_RID_gen_FastListenInterval
mdefine_line|#define awc_RID_gen_FastListenInterval &t;&t;awc_def_gen_RID(0x0056,&quot;FastListenInterval&quot;,&t;16,0xffff,0,&quot;msek&quot;)     
singleline_comment|// 0 default    100 kus    The listen interval to be used immediately after
DECL|macro|awc_RID_gen_ListenDecay
mdefine_line|#define awc_RID_gen_ListenDecay &t;&t;&t;awc_def_gen_RID(0x0058,&quot;ListenDecay&quot;,&t;&t;16,0xffff,0,&quot;times&quot;)&t;
singleline_comment|//      0 default    2Number of times to use the current listen interval
DECL|macro|awc_RID_gen_FastListenDelay
mdefine_line|#define awc_RID_gen_FastListenDelay &t;&t;awc_def_gen_RID(0x005A,&quot;FastListenDelay&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//      0 default    200 kus    Time interval to delay before going to fast listen
DECL|macro|awc_RID_gen_Reserved0x005C
mdefine_line|#define awc_RID_gen_Reserved0x005C &t;&t;&t;awc_def_gen_RID(0x005C,&quot;Reserved0x005C&quot;,&t;32,0xffffffff,0,&quot;&quot;)&t;
singleline_comment|//
singleline_comment|//ADHOC (or AP) OPERATION
DECL|macro|awc_RID_gen_BeaconPeriod
mdefine_line|#define awc_RID_gen_BeaconPeriod &t;&t;&t;awc_def_gen_RID(0x0060,&quot;BeaconPeriod&quot;,&t;&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//      0 default    100        0 selects the factory default of [~100 ms].  (kus)
DECL|macro|awc_RID_gen_AtimDuration
mdefine_line|#define awc_RID_gen_AtimDuration &t;&t;&t;awc_def_gen_RID(0x0062,&quot;AtimDuration&quot;,&t;&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//      0 default    5 kus      The time period reserved for ATIMs immediately after (kus)      the beacon. 0xFFFF will disable the ATIM window; power save mode will not operate.This parameter only applies to adhoc/IBSS.
DECL|macro|awc_RID_gen_Reserved0x0064
mdefine_line|#define awc_RID_gen_Reserved0x0064 &t;&t;&t;awc_def_gen_RID(0x0064,&quot;Reserved64&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//      0  0Reserved for future use
DECL|macro|awc_RID_gen_DSChannel
mdefine_line|#define awc_RID_gen_DSChannel &t;&t;&t;awc_def_gen_RID(0x0066,&quot;DSChannel&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//      0 default    1The desired operating channel.  ()refer to 802.11)       For North America, a Channel of 0 is 2412 MHz.
DECL|macro|awc_RID_gen_Reserved0x0068
mdefine_line|#define awc_RID_gen_Reserved0x0068 &t;&t;&t;awc_def_gen_RID(0x0068,&quot;Reserved68&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//      0  0Reserved for future use
DECL|macro|awc_RID_gen_DTIM_Period
mdefine_line|#define awc_RID_gen_DTIM_Period &t;&t;&t;awc_def_gen_RID(0x006A,&quot;DTIM Period&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//      0 default    1Selects how often a beacon is a DTIM for APs
DECL|macro|awc_RID_gen_Reserved0x0006C
mdefine_line|#define awc_RID_gen_Reserved0x0006C &t;&t;awc_def_gen_RID(0x006C,&quot;Reserved6C&quot;,&t;&t;32,0xffffffff,0,&quot;&quot;)&t;
singleline_comment|//    0&squot;s0&squot;s        Reserved for future use
singleline_comment|//RADIO OPERATION
DECL|macro|awc_RID_gen_RadioSpreadType
mdefine_line|#define awc_RID_gen_RadioSpreadType &t;&t;awc_def_gen_RID(0x0070,&quot;RadioSpreadType&quot;,&t;16,0xffff,0,NULL)&t;
singleline_comment|//      0 default    0Selects the radio operational mode. By default, this will
DECL|macro|awc_RID_gen_RadioSpreadType_FH
mdefine_line|#define awc_RID_gen_RadioSpreadType_FH &t;&t;awc_def_gen_RID(0x0070,&quot;RadioSpreadType FH&quot;,&t;16,0xffff,0,&quot;FH&quot;)&t;
singleline_comment|//0 = 802.11 FH Radio (Default)
DECL|macro|awc_RID_gen_RadioSpreadType_DS
mdefine_line|#define awc_RID_gen_RadioSpreadType_DS &t;&t;awc_def_gen_RID(0x0070,&quot;RadioSpreadType DS&quot;,&t;16,0xffff,1,&quot;DS&quot;)&t;
singleline_comment|//1 = 802.11 DS Radio
DECL|macro|awc_RID_gen_RadioSpreadType_LM
mdefine_line|#define awc_RID_gen_RadioSpreadType_LM &t;&t;awc_def_gen_RID(0x0070,&quot;RadioSpreadType LM2000&quot;,&t;16,0xffff,2,&quot;LM2000&quot;)&t;
singleline_comment|//2 = LM2000 (Legacy) DS Radio
DECL|macro|awc_RID_gen_TX_antenna_Diversity
mdefine_line|#define awc_RID_gen_TX_antenna_Diversity &t;&t;awc_def_gen_RID(0x0072,&quot;TX antenna Diversity&quot;,&t;16,0xff00,0,NULL)&t;
singleline_comment|//       0 default    0x0303    This field is bit-mapped to select the operational
DECL|macro|awc_RID_gen_TX_antenna_Diversity_default
mdefine_line|#define awc_RID_gen_TX_antenna_Diversity_default&t;awc_def_gen_RID(0x0072,&quot;TX antenna Diversity Default&quot;,&t;16,0xff00,0x0000,&quot;Default&quot;)&t;
singleline_comment|//  0 = Diversity as programmed at the factory
DECL|macro|awc_RID_gen_TX_antenna_Diversity_1
mdefine_line|#define awc_RID_gen_TX_antenna_Diversity_1 &t;&t;awc_def_gen_RID(0x0072,&quot;TX antenna Diversity Antenna 1&quot;,&t;16,0xff00,0x0100,&quot;Antenna 1&quot;)&t;
singleline_comment|//  1 = Antenna 1 only
DECL|macro|awc_RID_gen_TX_antenna_Diversity_2
mdefine_line|#define awc_RID_gen_TX_antenna_Diversity_2 &t;&t;awc_def_gen_RID(0x0072,&quot;TX antenna Diversity Antenna 2&quot;,&t;16,0xff00,0x0200,&quot;Antenna 2&quot;)&t;
singleline_comment|//  2 = Antenna 2 only
DECL|macro|awc_RID_gen_TX_antenna_Diversity_both
mdefine_line|#define awc_RID_gen_TX_antenna_Diversity_both &t;awc_def_gen_RID(0x0072,&quot;TX antenna Diversity both antennas&quot;,&t;16,0xff00,0x0300,&quot;both antennas&quot;)&t;
singleline_comment|//  3 = Antennas 1 and 2 are active
DECL|macro|awc_RID_gen_RX_antenna_Diversity
mdefine_line|#define awc_RID_gen_RX_antenna_Diversity&t;&t;awc_def_gen_RID(0x0072,&quot;RX antenna Diversity&quot;,&t;16,0x00ff,0,NULL)&t;
singleline_comment|//       0 default    0x0303    This field is bit-mapped to select the operational
DECL|macro|awc_RID_gen_RX_antenna_Diversity_default
mdefine_line|#define awc_RID_gen_RX_antenna_Diversity_default&t;awc_def_gen_RID(0x0072,&quot;RX antenna Diversity Default&quot;,&t;16,0x00ff,0,&quot;Default&quot;)&t;
singleline_comment|//  0 = Diversity as programmed at the factory
DECL|macro|awc_RID_gen_RX_antenna_Diversity_1
mdefine_line|#define awc_RID_gen_RX_antenna_Diversity_1&t;&t;awc_def_gen_RID(0x0072,&quot;RX antenna Diversity Antenna 1&quot;,&t;16,0x00ff,1,&quot;Antenna 1&quot;)&t;
singleline_comment|//  1 = Antenna 1 only
DECL|macro|awc_RID_gen_RX_antenna_Diversity_2
mdefine_line|#define awc_RID_gen_RX_antenna_Diversity_2 &t;&t;awc_def_gen_RID(0x0072,&quot;RX antenna Diversity Antenna 2&quot;,&t;16,0x00ff,2,&quot;Antenna 2&quot;)&t;
singleline_comment|//  2 = Antenna 2 only
DECL|macro|awc_RID_gen_RX_antenna_Diversity_both
mdefine_line|#define awc_RID_gen_RX_antenna_Diversity_both&t;awc_def_gen_RID(0x0072,&quot;RX antenna Diversity both antennas&quot;,&t;16,0x00ff,3,&quot;both antennas&quot;)&t;
singleline_comment|//
DECL|macro|awc_RID_gen_TransmitPower
mdefine_line|#define awc_RID_gen_TransmitPower &t;&t;&t;awc_def_gen_RID(0x0074,&quot;TransmitPower&quot;,&t;16,0xffff,0,&quot;mW (rounded up, btw)&quot;)&t;
singleline_comment|//       0 default    250 or    0 selects the default (maximum power allowed for the
DECL|macro|awc_RID_gen_RSSIthreshold
mdefine_line|#define awc_RID_gen_RSSIthreshold &t;&t;&t;awc_def_gen_RID(0x0076,&quot;RSSIthreshold&quot;,&t;16,0xffff,0,&quot;units&quot;)&t;
singleline_comment|//       0 default    0         RSSI threshold. 0 selects factory default.
DECL|macro|awc_RID_gen_Modulation
mdefine_line|#define awc_RID_gen_Modulation &t;&t;&t;&t;awc_def_gen_RID(0x0078,&quot;Modulation&quot;,&t;8,0xff,0,&quot;&quot;)&t;
singleline_comment|//     modulation type
DECL|macro|awc_RID_gen_Reserved0x0079
mdefine_line|#define awc_RID_gen_Reserved0x0079 &t;&t;&t;awc_def_gen_RID(0x0079,&quot;Reserved0x0079&quot;,&t;56,0xff,0,&quot;&quot;)&t;
singleline_comment|//     0&squot;s0&squot;s       reserved for future radio specific parameters
singleline_comment|//AIRONET EXTENSIONS
DECL|macro|awc_RID_gen_NodeName
mdefine_line|#define awc_RID_gen_NodeName &t;&t;&t;awc_def_gen_RID(0x0080,&quot;NodeName&quot;,&t;&t;128,0,0,&quot;&quot;)&t;
singleline_comment|//    0  0         Station name.
DECL|macro|awc_RID_gen_ARLThreshold
mdefine_line|#define awc_RID_gen_ARLThreshold &t;&t;&t;awc_def_gen_RID(0x0090,&quot;ARLThreshold&quot;,&t;&t;16,0xffff,0,&quot;times&quot;)&t;
singleline_comment|//       0 default    0xFFFF    0 selects the factory defaults. (which for now is
DECL|macro|awc_RID_gen_ARLDecay
mdefine_line|#define awc_RID_gen_ARLDecay &t;&t;&t;awc_def_gen_RID(0x0092,&quot;ARLDecay&quot;,&t;&t;16,0xffff,0,&quot;times&quot;)&t;
singleline_comment|//       0 default    0xFFFF    0 selects the factory defaults. (which for now is
DECL|macro|awc_RID_gen_ARLDelay
mdefine_line|#define awc_RID_gen_ARLDelay &t;&t;&t;awc_def_gen_RID(0x0094,&quot;ARLDelay&quot;,&t;&t;16,0xffff,0,&quot;times&quot;)&t;
singleline_comment|//       0 default    0xFFFF    0 selects the factory defaults. (which for now is
DECL|macro|awc_RID_gen_Unused0x0096
mdefine_line|#define awc_RID_gen_Unused0x0096 &t;&t;&t;awc_def_gen_RID(0x0096,&quot;Reserved0x96&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//
DECL|macro|awc_RID_gen_MagicPacketAction
mdefine_line|#define awc_RID_gen_MagicPacketAction &t;&t;awc_def_gen_RID(0x0098,&quot;MagicPacketAction&quot;,&t;8,0xff,0,&quot; hell knows what&quot;)&t;
singleline_comment|//        0  0         0 selects no action to be taken on a magic packet and&quot;
DECL|macro|awc_RID_gen_MagicPacketControl
mdefine_line|#define awc_RID_gen_MagicPacketControl &t;&t;awc_def_gen_RID(0x0099,&quot;MagicPacketControl&quot;,&t;8,0xff,0,&quot; hell know what&quot;)&t;
singleline_comment|//        0  0         0 will disable the magic packet mode command&quot;
DECL|macro|awc_RID_act_RidLen
mdefine_line|#define awc_RID_act_RidLen &t;&t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0000, 8,1,1,1,0, 0xffffffff,0x0000, &quot;Length of RID&quot; }
DECL|macro|awc_RID_act_OperatingMode_adhoc
mdefine_line|#define awc_RID_act_OperatingMode_adhoc &t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0002,16,1,1,0,0, 0x00000003,0x0000,&quot;Opmode IBSS Adhoc operation&quot; }
DECL|macro|awc_RID_act_OperatingMode_Infrastructure
mdefine_line|#define awc_RID_act_OperatingMode_Infrastructure &t;{&amp;aironet4500_RID_Select_Active_Config,0x0002,16,1,1,0,0, 0x00000003,0x0001,&quot;Opmode Infrastructure Station operation&quot; }
DECL|macro|awc_RID_act_OperatingMode_AP
mdefine_line|#define awc_RID_act_OperatingMode_AP&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0002,16,1,1,0,0, 0x00000003,0x0002,&quot;Opmode Access Point&quot; }
DECL|macro|awc_RID_act_OperatingMode_AP_and_repeater
mdefine_line|#define awc_RID_act_OperatingMode_AP_and_repeater &t;{&amp;aironet4500_RID_Select_Active_Config,0x0002,16,1,1,0,0, 0x00000003,0x0003,&quot;Opmode Access Point and Repeater&quot; }
DECL|macro|awc_RID_act_OperatingMode_No_payload_modify
mdefine_line|#define awc_RID_act_OperatingMode_No_payload_modify&t;{&amp;aironet4500_RID_Select_Active_Config,0x0002,16,1,1,0,0, 0x00000100,0x0100,&quot;Opmode Payload without modify&quot; }
DECL|macro|awc_RID_act_OperatingMode_LLC_802_3_convert
mdefine_line|#define awc_RID_act_OperatingMode_LLC_802_3_convert&t;{&amp;aironet4500_RID_Select_Active_Config,0x0002,16,1,1,0,0, 0x00000100,0x0000,&quot;Opmode LLC -&gt; 802.3 convert&quot; }
DECL|macro|awc_RID_act_OperatingMode_proprietary_ext
mdefine_line|#define awc_RID_act_OperatingMode_proprietary_ext &t;{&amp;aironet4500_RID_Select_Active_Config,0x0002,16,1,1,0,0, 0x00000200,0x0200,&quot;Opmode Aironet Extentsions enabled&quot; }
DECL|macro|awc_RID_act_OperatingMode_no_proprietary_ext
mdefine_line|#define awc_RID_act_OperatingMode_no_proprietary_ext {&amp;aironet4500_RID_Select_Active_Config,0x0002,16,1,1,0,0,0x00000200,0x0000,&quot;Opmode Aironet Extentsions disabled&quot; }
DECL|macro|awc_RID_act_OperatingMode_AP_ext
mdefine_line|#define awc_RID_act_OperatingMode_AP_ext &t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0002,16,1,1,0,0, 0x00000400,0x0400,&quot;Opmode AP Extentsions enabled&quot; }
DECL|macro|awc_RID_act_OperatingMode_no_AP_ext
mdefine_line|#define awc_RID_act_OperatingMode_no_AP_ext&t; &t;{&amp;aironet4500_RID_Select_Active_Config,0x0002,16,1,1,0,0, 0x00000400,0x0000,&quot;Opmode AP Extentsions disabled&quot; }
DECL|macro|awc_RID_act_ReceiveMode
mdefine_line|#define awc_RID_act_ReceiveMode &t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0004,16,1,1,0,0,0xffffffff,0x0000,&quot;RX Mode&quot;}
DECL|macro|awc_RID_act_ReceiveMode_BMA
mdefine_line|#define awc_RID_act_ReceiveMode_BMA &t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0004,16,1,1,0,0,0x0000000f,0x0000,&quot;RX Mode BC MC ADDR&quot;}
DECL|macro|awc_RID_act_ReceiveMode_BA
mdefine_line|#define awc_RID_act_ReceiveMode_BA &t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0004,16,1,1,0,0,0x0000000f,0x0001,&quot;RX Mode BC ADDR&quot;}
DECL|macro|awc_RID_act_ReceiveMode_A
mdefine_line|#define awc_RID_act_ReceiveMode_A &t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0004,16,1,1,0,0,0x0000000f,0x0002,&quot;RX Mode ADDR&quot;}
DECL|macro|awc_RID_act_ReceiveMode_802_11_monitor
mdefine_line|#define awc_RID_act_ReceiveMode_802_11_monitor&t;{&amp;aironet4500_RID_Select_Active_Config,0x0004,16,1,1,0,0,0x0000000f,0x0003,&quot;RX Mode 802.11 Monitor current BSSID&quot;}
DECL|macro|awc_RID_act_ReceiveMode_802_11_any_monitor
mdefine_line|#define awc_RID_act_ReceiveMode_802_11_any_monitor &t;{&amp;aironet4500_RID_Select_Active_Config,0x0004,16,1,1,0,0,0x0000000f,0x0004,&quot;RX Mode 802.11 Monitor any BSSID&quot;}
DECL|macro|awc_RID_act_ReceiveMode_LAN_monitor
mdefine_line|#define awc_RID_act_ReceiveMode_LAN_monitor &t;{&amp;aironet4500_RID_Select_Active_Config,0x0004,16,1,1,0,0,0x0000000f,0x0005,&quot;RX Mode LAN Monitor current BSSID&quot;}
DECL|macro|awc_RID_act_ReceiveMode_802_3_hdr_disable
mdefine_line|#define awc_RID_act_ReceiveMode_802_3_hdr_disable &t;{&amp;aironet4500_RID_Select_Active_Config,0x0004,16,1,1,0,0,0x00000100,0x0100,&quot;RX Mode Disable RX 802.3 Header&quot;}
DECL|macro|awc_RID_act_ReceiveMode_802_3_hdr_enable
mdefine_line|#define awc_RID_act_ReceiveMode_802_3_hdr_enable &t;{&amp;aironet4500_RID_Select_Active_Config,0x0004,16,1,1,0,0,0x00000100,0x0000,&quot;RX Mode Enable RX 802.3 header&quot;}
DECL|macro|awc_RID_act_Fragmentation_threshold
mdefine_line|#define awc_RID_act_Fragmentation_threshold&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0006,16,1,1,0,0,0x0000ffff,0x0000,&quot;Fragmentation Threshold&quot;}
DECL|macro|awc_RID_act_RTS_threshold
mdefine_line|#define awc_RID_act_RTS_threshold &t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0008,16,1,1,0,0,0xffff,0x0000,&quot;RTS Threshold&quot;}
DECL|macro|awc_RID_act_Station_Mac_Id
mdefine_line|#define awc_RID_act_Station_Mac_Id &t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x000A, 8,6,1,0,0,0xff,0,&quot;Station MAC Id&quot;}
DECL|macro|awc_RID_act_Supported_rates
mdefine_line|#define awc_RID_act_Supported_rates &t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0010, 8,8,1,0,1,0xff,0x00,&quot;Supported Rates&quot;}
DECL|macro|awc_RID_act_Basic_Rate
mdefine_line|#define awc_RID_act_Basic_Rate &t;&t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0010, 8,1,1,0,1,0x80,0x80,&quot;Basic Rate&quot;}
DECL|macro|awc_RID_act_Rate_500kbps
mdefine_line|#define awc_RID_act_Rate_500kbps &t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0010, 8,1,1,0,1,0x7f,0x01,&quot;Rate 500kbps&quot;}
DECL|macro|awc_RID_act_Rate_1Mbps
mdefine_line|#define awc_RID_act_Rate_1Mbps &t;&t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0010, 8,1,1,0,1,0x7f,0x02,&quot;Rate 1Mbps&quot;}
DECL|macro|awc_RID_act_Rate_2Mbps
mdefine_line|#define awc_RID_act_Rate_2Mbps &t;&t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0010, 8,1,1,0,1,0x7f,0x04,&quot;Rate 2Mbps&quot;}
DECL|macro|awc_RID_act_Rate_4Mbps
mdefine_line|#define awc_RID_act_Rate_4Mbps &t;&t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0010, 8,1,1,0,1,0x7f,0x08,&quot;Rate 4Mbps&quot;}
DECL|macro|awc_RID_act_Rate_5Mbps
mdefine_line|#define awc_RID_act_Rate_5Mbps &t;&t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0010, 8,1,1,0,1,0x7f,0x0B,&quot;Rate 5.5Mbps&quot;}
DECL|macro|awc_RID_act_Rate_10Mbps
mdefine_line|#define awc_RID_act_Rate_10Mbps &t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0010, 8,1,1,0,1,0x7f,0x14,&quot;Rate 10Mbps&quot;}
DECL|macro|awc_RID_act_Rate_11Mbps
mdefine_line|#define awc_RID_act_Rate_11Mbps &t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0010, 8,1,1,0,1,0x7f,0x16,&quot;Rate 11Mbps&quot;}
DECL|macro|awc_RID_act_BasicRate_500kbps
mdefine_line|#define awc_RID_act_BasicRate_500kbps &t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0010, 8,1,1,0,1,0xff,0x81,&quot;BasicRate 500kbps&quot;}
DECL|macro|awc_RID_act_BasicRate_1Mbps
mdefine_line|#define awc_RID_act_BasicRate_1Mbps &t;&t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0010, 8,1,1,0,1,0xff,0x82,&quot;BasicRate 1Mbps&quot;}
DECL|macro|awc_RID_act_BasicRate_2Mbps
mdefine_line|#define awc_RID_act_BasicRate_2Mbps &t;&t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0010, 8,1,1,0,1,0xff,0x84,&quot;BasicRate 2Mbps&quot;}
DECL|macro|awc_RID_act_BasicRate_4Mbps
mdefine_line|#define awc_RID_act_BasicRate_4Mbps &t;&t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0010, 8,1,1,0,1,0xff,0x88,&quot;BasicRate 4Mbps&quot;}
DECL|macro|awc_RID_act_BasicRate_5Mbps
mdefine_line|#define awc_RID_act_BasicRate_5Mbps &t;&t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0010, 8,1,1,0,1,0xff,0x8B,&quot;BasicRate 5.5Mbps&quot;}
DECL|macro|awc_RID_act_BasicRate_10Mbps
mdefine_line|#define awc_RID_act_BasicRate_10Mbps &t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0010, 8,1,1,0,1,0xff,0x94,&quot;BasicRate 10Mbps&quot;}
DECL|macro|awc_RID_act_BasicRate_11Mbps
mdefine_line|#define awc_RID_act_BasicRate_11Mbps &t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0010, 8,1,1,0,1,0xff,0x96,&quot;BasicRate 11Mbps&quot;}
DECL|macro|awc_RID_act_Long_retry_limit
mdefine_line|#define awc_RID_act_Long_retry_limit &t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0018,16, 1,1,0,0,0xffff,0,&quot;Short Retry Limit&quot;}
DECL|macro|awc_RID_act_Short_retry_limit
mdefine_line|#define awc_RID_act_Short_retry_limit &t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x001A,16, 1,1,0,0,0xffff,0,&quot;Long Retry Limit&quot;}
DECL|macro|awc_RID_act_Tx_MSDU_lifetime
mdefine_line|#define awc_RID_act_Tx_MSDU_lifetime &t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x001C,16, 1,1000,0,0,0xffff,0,&quot;TX MSDU Lifetime&quot;}
DECL|macro|awc_RID_act_Rx_MSDU_lifetime
mdefine_line|#define awc_RID_act_Rx_MSDU_lifetime &t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x001E,16, 1,1000,0,0,0xffff,0,&quot;RX MSDU Lifetime&quot;}
DECL|macro|awc_RID_act_Stationary
mdefine_line|#define awc_RID_act_Stationary &t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0020,16, 1,1,0,0,0xffff,0,&quot;Stationary&quot;}
DECL|macro|awc_RID_act_BC_MC_Ordering
mdefine_line|#define awc_RID_act_BC_MC_Ordering &t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0022,16, 1,1,0,0,0xffff,0,&quot;Strictly order Bcast and Mcast&quot;}
DECL|macro|awc_RID_act_Device_type
mdefine_line|#define awc_RID_act_Device_type &t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0024,16, 1,1,1,0,0xffff,0x0065,&quot;Radio Type PC4500&quot;}
DECL|macro|awc_RID_act_Reserved_0x0026
mdefine_line|#define awc_RID_act_Reserved_0x0026 &t;&t;&t;{&amp;aironet4500_RID_Select_Active_Config,0x0026, 8,10,1,0,0,0xff,0,&quot;Reserved0x28&quot;}
singleline_comment|//SCANNING/ASSOCIATING
DECL|macro|awc_RID_act_ScanMode
mdefine_line|#define awc_RID_act_ScanMode&t;&t;&t;awc_def_act_RID(0x0030,&quot;ScanMode&quot;,&t;&t;16,0xf,0, NULL)
DECL|macro|awc_RID_act_ScanMode_Active
mdefine_line|#define awc_RID_act_ScanMode_Active &t;&t;awc_def_act_RID(0x0030,&quot;ScanMode Active&quot;,&t;&t;16,0xf,0, &quot;Active&quot;)
DECL|macro|awc_RID_act_ScanMode_Passive
mdefine_line|#define awc_RID_act_ScanMode_Passive &t;&t;awc_def_act_RID(0x0030,&quot;ScanMode Passive&quot;,&t;&t;16,0xf,1, &quot;Passive&quot;)
DECL|macro|awc_RID_act_ScanMode_Aironet_ext
mdefine_line|#define awc_RID_act_ScanMode_Aironet_ext&t;&t;awc_def_act_RID(0x0030,&quot;ScanMode Aironet Ext&quot;,&t;16,0xf,2, &quot;Aironet Ext&quot;)
DECL|macro|awc_RID_act_ProbeDelay
mdefine_line|#define awc_RID_act_ProbeDelay &t;&t;&t;awc_def_act_RID(0x0032,&quot;ProbeDelay&quot;,&t;&t;16,0xffff,0,&quot; msek&quot;) &t;&t;
singleline_comment|//                 Time ms to wait after switching to a channel for clear channel assessment.
DECL|macro|awc_RID_act_ProbeEnergyTimeout
mdefine_line|#define awc_RID_act_ProbeEnergyTimeout &t;&t;awc_def_act_RID(0x0034,&quot;ProbeEnergyTimeout&quot;,&t;16,0xffff,0,&quot;msek&quot;) &t;
singleline_comment|//          Time to wait for energy after an active probe.
DECL|macro|awc_RID_act_ProbeResponseTimeout
mdefine_line|#define awc_RID_act_ProbeResponseTimeout&t;&t;awc_def_act_RID(0x0036,&quot;ProbeResponseTimeout&quot;,&t;16,0xffff,0,&quot;msek&quot;) &t;
singleline_comment|// Time to wait for a probe response after energy detected.
DECL|macro|awc_RID_act_BeaconListenTimeout
mdefine_line|#define awc_RID_act_BeaconListenTimeout &t;&t;awc_def_act_RID(0x0038,&quot;BeaconListenTimeout&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//    0 default    40          Time to listen for a beacon on each channel.
DECL|macro|awc_RID_act_IbssJoinNetTimeout
mdefine_line|#define awc_RID_act_IbssJoinNetTimeout &t;&t;awc_def_act_RID(0x003A,&quot;IbssJoinNetTimeout&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//       0 default    10000       IBSS: Time to scan for an IBSS before forming a
DECL|macro|awc_RID_act_AuthenticationTimeout
mdefine_line|#define awc_RID_act_AuthenticationTimeout &t;&t;awc_def_act_RID(0x003C,&quot;AuthenticationTimeout&quot;,16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//       0 default    2000        Time limit after which an authentication sequence will
DECL|macro|awc_RID_act_AuthenticationType
mdefine_line|#define awc_RID_act_AuthenticationType &t;&t;awc_def_act_RID(0x003E,&quot;AuthenticationType&quot;,&t;16,0xffff,0,NULL)&t;
singleline_comment|//       0 default    1 (open) //    Selects the desired authentication and privacy methods.&t;&t; 
DECL|macro|awc_RID_act_AuthenticationType_None
mdefine_line|#define awc_RID_act_AuthenticationType_None &t;awc_def_act_RID(0x003E,&quot;AuthenticationType None&quot;,&t;16,0xffff,0,&quot;None&quot;) &t;
singleline_comment|//   0x00 = None&t;
DECL|macro|awc_RID_act_AuthenticationType_Open
mdefine_line|#define awc_RID_act_AuthenticationType_Open&t;&t;awc_def_act_RID(0x003E,&quot;AuthenticationType Open&quot;,&t;16,0xffff,1,&quot;Open&quot;) &t;
singleline_comment|//             0x01 = Open
DECL|macro|awc_RID_act_AuthenticationType_Shared
mdefine_line|#define awc_RID_act_AuthenticationType_Shared&t;awc_def_act_RID(0x003E,&quot;AuthenticationType Shared-Key&quot;,&t;16,0xffff,2,&quot;Shared-Key&quot;)  &t;
singleline_comment|//     0x02 = Shared-Key
DECL|macro|awc_RID_act_AuthenticationType_Exclude_Open
mdefine_line|#define awc_RID_act_AuthenticationType_Exclude_Open awc_def_act_RID(0x003E,&quot;AuthenticationType Exclude Open&quot;,&t;16,0xffff,4,&quot;Exclude Open&quot;)   &t;
singleline_comment|//              0x04 = Exclude Unencrypted
DECL|macro|awc_RID_act_AssociationTimeout
mdefine_line|#define awc_RID_act_AssociationTimeout &t;&t;awc_def_act_RID(0x0040,&quot;AssociationTimeout&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//       0 default    2000        ESS: Time limit after which an association sequence
DECL|macro|awc_RID_act_SpecifiedAPtimeout
mdefine_line|#define awc_RID_act_SpecifiedAPtimeout &t;&t;awc_def_act_RID(0x0042,&quot;SpecifiedAPtimeout&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//       0 default    10000       0 selects the factory default [~10 sec].
DECL|macro|awc_RID_act_OfflineScanInterval
mdefine_line|#define awc_RID_act_OfflineScanInterval &t;&t;awc_def_act_RID(0x0044,&quot;OfflineScanInterval&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//       0            0           0 disables offline scanning.(kus)        The time period between offline scans.
DECL|macro|awc_RID_act_OfflineScanDuration
mdefine_line|#define awc_RID_act_OfflineScanDuration &t;&t;awc_def_act_RID(0x0046,&quot;OfflineScanDuration&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//       0            0           0 disables offline scanning. //    (kus)        The duration of an offline scan.
DECL|macro|awc_RID_act_LinkLossDelay
mdefine_line|#define awc_RID_act_LinkLossDelay &t;&t;&t;awc_def_act_RID(0x0048,&quot;LinkLossDelay&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//       0  0 Time to delay before reporting a loss of association
DECL|macro|awc_RID_act_MaxBeaconLostTime
mdefine_line|#define awc_RID_act_MaxBeaconLostTime &t;&t;awc_def_act_RID(0x004A,&quot;MaxBeaconLostTime&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//      0 default    500        If no beacons are received for this time period, the unit
DECL|macro|awc_RID_act_RefreshInterval
mdefine_line|#define awc_RID_act_RefreshInterval &t;&t;awc_def_act_RID(0x004C,&quot;RefreshInterval&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;&t;
singleline_comment|//      0 default    10000      At the specified interval, the station will send a refresh
singleline_comment|//POWER SAVE OPERATION
DECL|macro|awc_RID_act_PowerSaveMode
mdefine_line|#define awc_RID_act_PowerSaveMode &t;&t;&t;awc_def_act_RID(0x0050,&quot;PowerSaveMode&quot;,&t;16,0xffff,0,NULL) &t;&t;
singleline_comment|//      0  0Note, for IBSS there is only one PSP mode and it is only enabled if the ATIMwindow is non-zero.
DECL|macro|awc_RID_act_PowerSaveMode_CAM
mdefine_line|#define awc_RID_act_PowerSaveMode_CAM &t;&t;awc_def_act_RID(0x0050,&quot;PowerSaveMode CAM&quot;,&t;16,0x000f,0,&quot;CAM&quot;) &t;
singleline_comment|// 0 = CAM
DECL|macro|awc_RID_act_PowerSaveMode_PSP
mdefine_line|#define awc_RID_act_PowerSaveMode_PSP &t;&t;awc_def_act_RID(0x0050,&quot;PowerSaveMode PSP&quot;,&t;16,0x000f,1,&quot;PSP&quot;) &t;
singleline_comment|// 1 = PSP
DECL|macro|awc_RID_act_PowerSaveMode_Fast_PSP
mdefine_line|#define awc_RID_act_PowerSaveMode_Fast_PSP&t;&t;awc_def_act_RID(0x0050,&quot;PowerSaveMode Fast PSP&quot;,&t;16,0x000f,2,&quot;Fast PSP&quot;)&t;
singleline_comment|//2 = PSP-CAM [FASTPSP]
DECL|macro|awc_RID_act_SleepForDTIMs
mdefine_line|#define awc_RID_act_SleepForDTIMs &t;&t;&t;awc_def_act_RID(0x0052,&quot;SleepForDTIMs&quot;,&t;16,0xffff,0,&quot;DTIMs&quot;)&t;
singleline_comment|//      0  0If non-zero, the station may sleep through DTIMs; this
DECL|macro|awc_RID_act_ListenInterval
mdefine_line|#define awc_RID_act_ListenInterval &t;&t;&t;awc_def_act_RID(0x0054,&quot;ListenInterval&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;&t;
singleline_comment|//      0 default    200 kus    Maximum time to awaken for TIMs. 0 selects factory
DECL|macro|awc_RID_act_FastListenInterval
mdefine_line|#define awc_RID_act_FastListenInterval &t;&t;awc_def_act_RID(0x0056,&quot;FastListenInterval&quot;,&t;16,0xffff,0,&quot;msek&quot;)  
singleline_comment|//    0 default    100 kus    The listen interval to be used immediately after
DECL|macro|awc_RID_act_ListenDecay
mdefine_line|#define awc_RID_act_ListenDecay &t;&t;&t;awc_def_act_RID(0x0058,&quot;ListenDecay&quot;,&t;&t;16,0xffff,0,&quot;times&quot;)&t;
singleline_comment|//      0 default    2Number of times to use the current listen interval
DECL|macro|awc_RID_act_FastListenDelay
mdefine_line|#define awc_RID_act_FastListenDelay &t;&t;awc_def_act_RID(0x005A,&quot;FastListenDelay&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//      0 default    200 kus    Time interval to delay before going to fast listen
DECL|macro|awc_RID_act_Reserved0x005C
mdefine_line|#define awc_RID_act_Reserved0x005C &t;&t;&t;awc_def_act_RID(0x005C,&quot;Reserved0x005C&quot;,&t;32,0,0,&quot;&quot;)&t;
singleline_comment|//
singleline_comment|//ADHOC (or AP) OPERATION
DECL|macro|awc_RID_act_BeaconPeriod
mdefine_line|#define awc_RID_act_BeaconPeriod &t;&t;&t;awc_def_act_RID(0x0060,&quot;BeaconPeriod&quot;,&t;&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//      0 default    100        0 selects the factory default of [~100 ms].  (kus)
DECL|macro|awc_RID_act_AtimDuration
mdefine_line|#define awc_RID_act_AtimDuration &t;&t;&t;awc_def_act_RID(0x0062,&quot;AtimDuration&quot;,&t;&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|//      0 default    5 kus      The time period reserved for ATIMs immediately after (kus)      the beacon. 0xFFFF will disable the ATIM window; power save mode will not operate.This parameter only applies to adhoc/IBSS.
DECL|macro|awc_RID_act_Reserved0x0064
mdefine_line|#define awc_RID_act_Reserved0x0064 &t;&t;&t;awc_def_act_RID(0x0064,&quot;Reserved64&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//      0  0Reserved for future use
DECL|macro|awc_RID_act_DSChannel
mdefine_line|#define awc_RID_act_DSChannel &t;&t;&t;awc_def_act_RID(0x0066,&quot;DSChannel&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//      0 default    1The desired operating channel.  ()refer to 802.11)       For North America, a Channel of 0 is 2412 MHz.
DECL|macro|awc_RID_act_Reserved0x0068
mdefine_line|#define awc_RID_act_Reserved0x0068 &t;&t;&t;awc_def_act_RID(0x0068,&quot;Reserved68&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//      0  0Reserved for future use
DECL|macro|awc_RID_act_DTIM_Period
mdefine_line|#define awc_RID_act_DTIM_Period &t;&t;&t;awc_def_act_RID(0x006A,&quot;DTIM Period&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//      0 default    1Selects how often a beacon is a DTIM for APs
DECL|macro|awc_RID_act_Reserved0x0006C
mdefine_line|#define awc_RID_act_Reserved0x0006C &t;&t;awc_def_act_RID(0x006C,&quot;Reserved6C&quot;,&t;&t;32,0xffffffff,0,&quot;&quot;)&t;
singleline_comment|//    0&squot;s0&squot;s        Reserved for future use
singleline_comment|//RADIO OPERATION
DECL|macro|awc_RID_act_RadioSpreadType
mdefine_line|#define awc_RID_act_RadioSpreadType &t;&t;awc_def_act_RID(0x0070,&quot;RadioSpreadType&quot;,&t;16,0xffff,0,NULL)&t;
singleline_comment|//      0 default    0Selects the radio operational mode. By default, this will
DECL|macro|awc_RID_act_RadioSpreadType_FH
mdefine_line|#define awc_RID_act_RadioSpreadType_FH &t;&t;awc_def_act_RID(0x0070,&quot;RadioSpreadType FH&quot;,&t;16,0xffff,0,&quot;FH&quot;)&t;
singleline_comment|//0 = 802.11 FH Radio (Default)
DECL|macro|awc_RID_act_RadioSpreadType_DS
mdefine_line|#define awc_RID_act_RadioSpreadType_DS &t;&t;awc_def_act_RID(0x0070,&quot;RadioSpreadType DS&quot;,&t;16,0xffff,1,&quot;DS&quot;)&t;
singleline_comment|//1 = 802.11 DS Radio
DECL|macro|awc_RID_act_RadioSpreadType_LM
mdefine_line|#define awc_RID_act_RadioSpreadType_LM &t;&t;awc_def_act_RID(0x0070,&quot;RadioSpreadType LM2000&quot;,&t;16,0xffff,2,&quot;LM2000&quot;)&t;
singleline_comment|//2 = LM2000 (Legacy) DS Radio
DECL|macro|awc_RID_act_TX_antenna_Diversity
mdefine_line|#define awc_RID_act_TX_antenna_Diversity &t;&t;awc_def_act_RID(0x0072,&quot;TX antenna Diversity&quot;,&t;16,0xff00,0,NULL)&t;
singleline_comment|//       0 default    0x0303    This field is bit-mapped to select the operational
DECL|macro|awc_RID_act_TX_antenna_Diversity_default
mdefine_line|#define awc_RID_act_TX_antenna_Diversity_default&t;awc_def_act_RID(0x0072,&quot;TX antenna Diversity Default&quot;,&t;16,0xff00,0x0000,&quot;Default&quot;)&t;
singleline_comment|//  0 = Diversity as programmed at the factory
DECL|macro|awc_RID_act_TX_antenna_Diversity_1
mdefine_line|#define awc_RID_act_TX_antenna_Diversity_1 &t;&t;awc_def_act_RID(0x0072,&quot;TX antenna Diversity Antenna 1&quot;,&t;16,0xff00,0x0100,&quot;Antenna 1&quot;)&t;
singleline_comment|//  1 = Antenna 1 only
DECL|macro|awc_RID_act_TX_antenna_Diversity_2
mdefine_line|#define awc_RID_act_TX_antenna_Diversity_2 &t;&t;awc_def_act_RID(0x0072,&quot;TX antenna Diversity Antenna 2&quot;,&t;16,0xff00,0x0200,&quot;Antenna 2&quot;)&t;
singleline_comment|//  2 = Antenna 2 only
DECL|macro|awc_RID_act_TX_antenna_Diversity_both
mdefine_line|#define awc_RID_act_TX_antenna_Diversity_both &t;awc_def_act_RID(0x0072,&quot;TX antenna Diversity both antennas&quot;,&t;16,0xff00,0x0300,&quot;both antennas&quot;)&t;
singleline_comment|//  3 = Antennas 1 and 2 are active
DECL|macro|awc_RID_act_RX_antenna_Diversity
mdefine_line|#define awc_RID_act_RX_antenna_Diversity&t;&t;awc_def_act_RID(0x0072,&quot;RX antenna Diversity&quot;,&t;16,0x00ff,0,NULL)&t;
singleline_comment|//       0 default    0x0303    This field is bit-mapped to select the operational
DECL|macro|awc_RID_act_RX_antenna_Diversity_default
mdefine_line|#define awc_RID_act_RX_antenna_Diversity_default&t;awc_def_act_RID(0x0072,&quot;RX antenna Diversity Default&quot;,&t;16,0x00ff,0,&quot;Default&quot;)&t;
singleline_comment|//  0 = Diversity as programmed at the factory
DECL|macro|awc_RID_act_RX_antenna_Diversity_1
mdefine_line|#define awc_RID_act_RX_antenna_Diversity_1&t;&t;awc_def_act_RID(0x0072,&quot;RX antenna Diversity Antenna 1&quot;,&t;16,0x00ff,1,&quot;Antenna 1&quot;)&t;
singleline_comment|//  1 = Antenna 1 only
DECL|macro|awc_RID_act_RX_antenna_Diversity_2
mdefine_line|#define awc_RID_act_RX_antenna_Diversity_2 &t;&t;awc_def_act_RID(0x0072,&quot;RX antenna Diversity Antenna 2&quot;,&t;16,0x00ff,2,&quot;Antenna 2&quot;)&t;
singleline_comment|//  2 = Antenna 2 only
DECL|macro|awc_RID_act_RX_antenna_Diversity_both
mdefine_line|#define awc_RID_act_RX_antenna_Diversity_both&t;awc_def_act_RID(0x0072,&quot;RX antenna Diversity both antennas&quot;,&t;16,0x00ff,3,&quot;both antennas&quot;)&t;
singleline_comment|//
DECL|macro|awc_RID_act_TransmitPower
mdefine_line|#define awc_RID_act_TransmitPower &t;&t;&t;awc_def_act_RID(0x0074,&quot;TransmitPower&quot;,&t;16,0xffff,0,&quot;mW (rounded up, btw)&quot;)&t;
singleline_comment|//       0 default    250 or    0 selects the default (maximum power allowed for the
DECL|macro|awc_RID_act_RSSIthreshold
mdefine_line|#define awc_RID_act_RSSIthreshold &t;&t;&t;awc_def_act_RID(0x0076,&quot;RSSIthreshold&quot;,&t;16,0xffff,0,&quot;units&quot;)&t;
singleline_comment|//       0 default    0         RSSI threshold. 0 selects factory default.
DECL|macro|awc_RID_act_Reserved0x0078
mdefine_line|#define awc_RID_act_Reserved0x0078 &t;&t;&t;awc_def_act_RID(0x0078,&quot;Reserved0x0078&quot;,&t;64,0,0,&quot;&quot;)&t;
singleline_comment|//     0&squot;s0&squot;s       reserved for future radio specific parameters
DECL|macro|awc_RID_act_Modulation
mdefine_line|#define awc_RID_act_Modulation &t;&t;&t;&t;awc_def_act_RID(0x0078,&quot;Modulation&quot;,&t;8,0xff,0,&quot;&quot;)&t;
singleline_comment|//     modulation type
DECL|macro|awc_RID_act_Reserved0x0079
mdefine_line|#define awc_RID_act_Reserved0x0079 &t;&t;&t;awc_def_act_RID(0x0079,&quot;Reserved0x0079&quot;,&t;56,0xff,0,&quot;&quot;)&t;
singleline_comment|//     0&squot;s0&squot;s       reserved for future radio specific parameters
singleline_comment|//AIRONET EXTENSIONS
DECL|macro|awc_RID_act_NodeName
mdefine_line|#define awc_RID_act_NodeName &t;&t;&t;awc_def_act_RID(0x0080,&quot;NodeName&quot;,&t;&t;128,0,0,&quot;&quot;)&t;
singleline_comment|//    0  0         Station name.
DECL|macro|awc_RID_act_ARLThreshold
mdefine_line|#define awc_RID_act_ARLThreshold &t;&t;awc_def_act_RID(0x0090,&quot;ARLThreshold&quot;,&t;&t;16,0xffff,0,&quot;times&quot;)&t;
singleline_comment|//       0 default    0xFFFF    0 selects the factory defaults. (which for now is
DECL|macro|awc_RID_act_ARLDecay
mdefine_line|#define awc_RID_act_ARLDecay &t;&t;&t;awc_def_act_RID(0x0092,&quot;ARLDecay&quot;,&t;&t;16,0xffff,0,&quot;times&quot;)&t;
singleline_comment|//       0 default    0xFFFF    0 selects the factory defaults. (which for now is
DECL|macro|awc_RID_act_ARLDelay
mdefine_line|#define awc_RID_act_ARLDelay &t;&t;&t;awc_def_act_RID(0x0094,&quot;ARLDelay&quot;,&t;&t;16,0xffff,0,&quot;times&quot;)&t;
singleline_comment|//       0 default    0xFFFF    0 selects the factory defaults. (which for now is
DECL|macro|awc_RID_act_Unused0x0096
mdefine_line|#define awc_RID_act_Unused0x0096 &t;&t;awc_def_act_RID(0x0096,&quot;Reserved0x96&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//
DECL|macro|awc_RID_act_MagicPacketAction
mdefine_line|#define awc_RID_act_MagicPacketAction &t;&t;awc_def_act_RID(0x0098,&quot;MagicPacketAction&quot;,&t;8,0xff,0,&quot; hell knows what&quot;)&t;
singleline_comment|//        0  0         0 selects no action to be taken on a magic packet and&quot;
DECL|macro|awc_RID_act_MagicPacketControl
mdefine_line|#define awc_RID_act_MagicPacketControl &t;&t;awc_def_act_RID(0x0099,&quot;MagicPacketControl&quot;,&t;8,0xff,0,&quot; hell know what&quot;)&t;
singleline_comment|//        0  0         0 will disable the magic packet mode command&quot;
singleline_comment|// ***************************        SSID  RID
DECL|macro|awc_RID_SSID_RidLen
mdefine_line|#define awc_RID_SSID_RidLen &t;&t;&t;&t;awc_def_SSID_RID(0x0000,&quot;RidLen&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//RidLen     &quot;,16,0xffff,,&quot;&quot;)&t;//      read-only        Length of this RID including the length field 0x68
DECL|macro|awc_RID_SSID_Accept_any
mdefine_line|#define awc_RID_SSID_Accept_any &t;&t;awc_def_SSID_RID(0x0002,&quot;Accept Any SSID&quot;,&t;16,0xffff,0,&quot;Accept ANY SSID&quot;)&t;
singleline_comment|//
DECL|macro|awc_RID_SSIDlen1
mdefine_line|#define awc_RID_SSIDlen1 &t;&t;&t;awc_def_SSID_RID(0x0002,&quot;SSIDlen1&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//      7      The length of the SSID1 byte string.
DECL|macro|awc_RID_SSID1
mdefine_line|#define awc_RID_SSID1 &t;&t;&t;&t;awc_def_SSID_RID(0x0004,&quot;SSID1&quot;,&t;&t;255,0,0,&quot;&quot;)&t;
singleline_comment|//    &quot;tsunami&quot;        The identifier uniquely identifying the wireless system.
DECL|macro|awc_RID_SSIDlen2
mdefine_line|#define awc_RID_SSIDlen2 &t;&t;&t;awc_def_SSID_RID(0x0024,&quot;SSIDlen2&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//      0      The length of the SSID2 byte string.
DECL|macro|awc_RID_SSID2
mdefine_line|#define awc_RID_SSID2 &t;&t;&t;&t;awc_def_SSID_RID(0x0026,&quot;SSID2&quot;,&t;&t;255,0,0,&quot;&quot;) &t;
singleline_comment|//   
DECL|macro|awc_RID_SSIDlen3
mdefine_line|#define awc_RID_SSIDlen3 &t;&t;&t;awc_def_SSID_RID(0x0046,&quot;SSIDlen3&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//      0      The length of the SSID3 byte string.
DECL|macro|awc_RID_SSID3
mdefine_line|#define awc_RID_SSID3 &t;&t;&t;&t;awc_def_SSID_RID(0x0048,&quot;SSID3&quot;,&t;&t;255,0,0,&quot;&quot;)&t;
singleline_comment|//    
DECL|macro|awc_RID_SSID1hex
mdefine_line|#define awc_RID_SSID1hex &t;&t;&t;&t;awc_def_SSID_RID(0x0004,&quot;SSID1hex&quot;,&t;&t;255,0xff,0,&quot;&quot;)&t;
DECL|macro|awc_RID_SSID2hex
mdefine_line|#define awc_RID_SSID2hex &t;&t;&t;&t;awc_def_SSID_RID(0x0026,&quot;SSID2hex&quot;,&t;&t;255,0xff,0,&quot;&quot;) &t;
DECL|macro|awc_RID_SSID3hex
mdefine_line|#define awc_RID_SSID3hex &t;&t;&t;&t;awc_def_SSID_RID(0x0048,&quot;SSID3hex&quot;,&t;&t;255,0xff,0,&quot;&quot;)&t;
singleline_comment|// AP list
DECL|macro|awc_RID_AP_List_RidLen
mdefine_line|#define awc_RID_AP_List_RidLen &t;&t;&t;awc_def_AP_List_RID(0x0000,&quot;RidLen&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;&t;
singleline_comment|//      read-only     Length of this RID including the length field
DECL|macro|awc_RID_AP_List_SpecifiedAP1
mdefine_line|#define awc_RID_AP_List_SpecifiedAP1 &t;&t;awc_def_AP_List_RID(0x0002,&quot;SpecifiedAP1&quot;,&t;&t;48,0xff,0,&quot;&quot;)&t;
singleline_comment|//    0   Specifies the MAC address of an access point to attempt to associate to first, before looking for other Access Points
DECL|macro|awc_RID_AP_List_SpecifiedAP2
mdefine_line|#define awc_RID_AP_List_SpecifiedAP2 &t;&t;awc_def_AP_List_RID(0x0008,&quot;SpecifiedAP2&quot;,&t;&t;48,0xff,0,&quot;&quot;)&t;
singleline_comment|//    0   Allows for a secondary AP to associate to if the radio cannot associate to the primary AP.
DECL|macro|awc_RID_AP_List_SpecifiedAP3
mdefine_line|#define awc_RID_AP_List_SpecifiedAP3 &t;&t;awc_def_AP_List_RID(0x000E,&quot;SpecifiedAP3&quot;,&t;&t;48,0xff,0,&quot;&quot;)&t;
singleline_comment|//    0   Allows for a third option when specifying a list of APs.
DECL|macro|awc_RID_AP_List_SpecifiedAP4
mdefine_line|#define awc_RID_AP_List_SpecifiedAP4 &t;&t;awc_def_AP_List_RID(0x0014,&quot;SpecifiedAP4&quot;,&t;&t;48,0xff,0,&quot;&quot;)&t;
singleline_comment|//    0   Allows for a fourth option when specifying a list of  APs.
singleline_comment|//   Driver Name
DECL|macro|awc_RID_Dname_RidLen
mdefine_line|#define awc_RID_Dname_RidLen &t;&t;&t;awc_def_Dname_RID(0x0000,&quot;RidLen&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//      read-only     Length of this RID including the length field
DECL|macro|awc_RID_Dname_DriverName
mdefine_line|#define awc_RID_Dname_DriverName &t;&t;awc_def_Dname_RID(0x0002,&quot;DriverName&quot;,&t;&t;128,0,0,&quot;&quot;)&t;
singleline_comment|// The driver name and version can be written here for  debugging support
singleline_comment|//       Encapsulation Transformations RID
DECL|macro|awc_RID_Enc_RidLen
mdefine_line|#define awc_RID_Enc_RidLen &t;&t;&t;awc_def_Enc_RID(0x0000,&quot;RidLen&quot;,&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//       read-only     Length of this RID including the length field
DECL|macro|awc_RID_Enc_EtherType1
mdefine_line|#define awc_RID_Enc_EtherType1 &t;&t;&t;awc_def_Enc_RID(0x0002,&quot;EtherType1&quot;,&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//       0   Note, the ethertype values are in network transmission order.  So IP (0x800) is actually (0x0008). Zero ends the list and selects the default action.
DECL|macro|awc_RID_Enc_Action_RX_1
mdefine_line|#define awc_RID_Enc_Action_RX_1 &t;&t;awc_def_Enc_RID(0x0004,&quot;RX Action 1&quot;,&t;16,0x0001,0,NULL)&t;
singleline_comment|//       0   This field is bit encoded as follows:
DECL|macro|awc_RID_Enc_Action_RX_1_RFC_1042
mdefine_line|#define awc_RID_Enc_Action_RX_1_RFC_1042 &t;awc_def_Enc_RID(0x0004,&quot;RX Action 1&quot;,&t;16,0x0001,1,&quot;RX RFC1042&quot;)&t;
singleline_comment|//  bit 0   (0x0001)  1=RFC1042 is kept for receive packets.
DECL|macro|awc_RID_Enc_Action_RX_1_802_11
mdefine_line|#define awc_RID_Enc_Action_RX_1_802_11 &t;&t;awc_def_Enc_RID(0x0004,&quot;RX Action 1&quot;,&t;16,0x0001,0,&quot;RX 802.11&quot;)&t;
singleline_comment|//  bit 0   (0x0001)  1=RFC1042 is kept for receive packets.
DECL|macro|awc_RID_Enc_Action_TX_1
mdefine_line|#define awc_RID_Enc_Action_TX_1 &t;&t;awc_def_Enc_RID(0x0004,&quot;TX Action 1&quot;,&t;16,0x0002,0,NULL)&t;
singleline_comment|//
DECL|macro|awc_RID_Enc_Action_TX_1_RFC_1042
mdefine_line|#define awc_RID_Enc_Action_TX_1_RFC_1042 &t;awc_def_Enc_RID(0x0004,&quot;TX Action 1&quot;,&t;16,0x0002,1,&quot;TX 802.11&quot; )&t;
singleline_comment|//  bit 1   (0x0002)  0=RFC1042 is used for transmit encapsulation.  1=802.1H is used for transmit encapsulation.
DECL|macro|awc_RID_Enc_Action_TX_1_802_11
mdefine_line|#define awc_RID_Enc_Action_TX_1_802_11 &t;&t;awc_def_Enc_RID(0x0004,&quot;Tx Action 1&quot;,&t;16,0x0002,0,&quot;TX RFC1042&quot;)&t;
singleline_comment|//  bit 1   (0x0002)  0=RFC1042 is used for transmit encapsulation.  1=802.1H is used for transmit encapsulation.
DECL|macro|awc_RID_Enc_EtherType2
mdefine_line|#define awc_RID_Enc_EtherType2 &t;&t;&t;awc_def_Enc_RID(0x0006,&quot;EtherType2&quot;,&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//       0   Note, the ethertype values are in network transmission order.  So IP (0x800) is actually (0x0008). Zero ends the list and selects the default action.
DECL|macro|awc_RID_Enc_Action_RX_2
mdefine_line|#define awc_RID_Enc_Action_RX_2 &t;&t;awc_def_Enc_RID(0x0008,&quot;RX Action 2&quot;,&t;16,0x0001,0,NULL)&t;
singleline_comment|//       0   This field is bit encoded as follows:
DECL|macro|awc_RID_Enc_Action_RX_2_RFC_1042
mdefine_line|#define awc_RID_Enc_Action_RX_2_RFC_1042 &t;awc_def_Enc_RID(0x0008,&quot;RX Action 2&quot;,&t;16,0x0001,1,&quot;RX RFC1042&quot;)&t;
singleline_comment|//  bit 0   (0x0001)  1=RFC1042 is kept for receive packets.
DECL|macro|awc_RID_Enc_Action_RX_2_802_11
mdefine_line|#define awc_RID_Enc_Action_RX_2_802_11 &t;&t;awc_def_Enc_RID(0x0008,&quot;RX Action 2&quot;,&t;16,0x0001,0,&quot;RX 802.11&quot;)&t;
singleline_comment|//  bit 0   (0x0001)  1=RFC1042 is kept for receive packets.
DECL|macro|awc_RID_Enc_Action_TX_2
mdefine_line|#define awc_RID_Enc_Action_TX_2 &t;&t;awc_def_Enc_RID(0x0008,&quot;TX Action 2&quot;,&t;16,0x0002,0,NULL)&t;
singleline_comment|//
DECL|macro|awc_RID_Enc_Action_TX_2_RFC_1042
mdefine_line|#define awc_RID_Enc_Action_TX_2_RFC_1042 &t;awc_def_Enc_RID(0x0008,&quot;TX Action 2&quot;,&t;16,0x0002,1,&quot;TX 802.11&quot; )&t;
singleline_comment|//  bit 1   (0x0002)  0=RFC1042 is used for transmit encapsulation.  1=802.1H is used for transmit encapsulation.
DECL|macro|awc_RID_Enc_Action_TX_2_802_11
mdefine_line|#define awc_RID_Enc_Action_TX_2_802_11 &t;&t;awc_def_Enc_RID(0x0008,&quot;Tx Action 2&quot;,&t;16,0x0002,0,&quot;TX RFC1042&quot;)&t;
singleline_comment|//  bit 1   (0x0002)  0=RFC1042 is used for transmit encapsulation.  1=802.1H is used for transmit encapsulation.
DECL|macro|awc_RID_Enc_EtherType3
mdefine_line|#define awc_RID_Enc_EtherType3 &t;&t;&t;awc_def_Enc_RID(0x000A,&quot;EtherType3&quot;,&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//       0   Note, the ethertype values are in network transmission order.  So IP (0x800) is actually (0x0008). Zero ends the list and selects the default action.
DECL|macro|awc_RID_Enc_Action_RX_3
mdefine_line|#define awc_RID_Enc_Action_RX_3 &t;&t;awc_def_Enc_RID(0x000C,&quot;RX Action 3&quot;,&t;16,0x0001,0,NULL)&t;
singleline_comment|//       0   This field is bit encoded as follows:
DECL|macro|awc_RID_Enc_Action_RX_3_RFC_1042
mdefine_line|#define awc_RID_Enc_Action_RX_3_RFC_1042 &t;awc_def_Enc_RID(0x000C,&quot;RX Action 3&quot;,&t;16,0x0001,1,&quot;RX RFC1042&quot;)&t;
singleline_comment|//  bit 0   (0x0001)  1=RFC1042 is kept for receive packets.
DECL|macro|awc_RID_Enc_Action_RX_3_802_11
mdefine_line|#define awc_RID_Enc_Action_RX_3_802_11 &t;&t;awc_def_Enc_RID(0x000C,&quot;RX Action 3&quot;,&t;16,0x0001,0,&quot;RX 802.11&quot;)&t;
singleline_comment|//  bit 0   (0x0001)  1=RFC1042 is kept for receive packets.
DECL|macro|awc_RID_Enc_Action_TX_3_
mdefine_line|#define awc_RID_Enc_Action_TX_3_ &t;&t;awc_def_Enc_RID(0x000C,&quot;TX Action 3&quot;,&t;16,0x0002,0,NULL)&t;
singleline_comment|//
DECL|macro|awc_RID_Enc_Action_TX_3_RFC_1042
mdefine_line|#define awc_RID_Enc_Action_TX_3_RFC_1042 &t;awc_def_Enc_RID(0x000C,&quot;TX Action 3&quot;,&t;16,0x0002,1,&quot;TX 802.11&quot; )&t;
singleline_comment|//  bit 1   (0x0002)  0=RFC1042 is used for transmit encapsulation.  1=802.1H is used for transmit encapsulation.
DECL|macro|awc_RID_Enc_Action_TX_3_802_11
mdefine_line|#define awc_RID_Enc_Action_TX_3_802_11 &t;&t;awc_def_Enc_RID(0x000C,&quot;Tx Action 3&quot;,&t;16,0x0002,0,&quot;TX RFC1042&quot;)&t;
singleline_comment|//  bit 1   (0x0002)  0=RFC1042 is used for transmit encapsulation.  1=802.1H is used for transmit encapsulation.
DECL|macro|awc_RID_Enc_EtherType4
mdefine_line|#define awc_RID_Enc_EtherType4&t;&t;&t;awc_def_Enc_RID(0x000E,&quot;EtherType4&quot;,&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//       0   Note, the ethertype values are in network transmission order.  So IP (0x800) is actually (0x0008). Zero ends the list and selects the default action.
DECL|macro|awc_RID_Enc_Action_RX_4
mdefine_line|#define awc_RID_Enc_Action_RX_4&t;&t;&t;awc_def_Enc_RID(0x0010,&quot;RX Action 4&quot;,&t;16,0x0001,0,NULL)&t;
singleline_comment|//       0   This field is bit encoded as follows:
DECL|macro|awc_RID_Enc_Action_RX_4_RFC_1042
mdefine_line|#define awc_RID_Enc_Action_RX_4_RFC_1042 &t;awc_def_Enc_RID(0x0010,&quot;RX Action 4&quot;,&t;16,0x0001,1,&quot;RX RFC1042&quot;)&t;
singleline_comment|//  bit 0   (0x0001)  1=RFC1042 is kept for receive packets.
DECL|macro|awc_RID_Enc_Action_RX_4_802_11
mdefine_line|#define awc_RID_Enc_Action_RX_4_802_11 &t;&t;awc_def_Enc_RID(0x0010,&quot;RX Action 4&quot;,&t;16,0x0001,0,&quot;RX 802.11&quot;)&t;
singleline_comment|//  bit 0   (0x0001)  1=RFC1042 is kept for receive packets.
DECL|macro|awc_RID_Enc_Action_TX_4
mdefine_line|#define awc_RID_Enc_Action_TX_4 &t;&t;awc_def_Enc_RID(0x0010,&quot;TX Action 4&quot;,&t;16,0x0002,0,NULL)&t;
singleline_comment|//
DECL|macro|awc_RID_Enc_Action_TX_4_RFC_1042
mdefine_line|#define awc_RID_Enc_Action_TX_4_RFC_1042 &t;awc_def_Enc_RID(0x0010,&quot;TX Action 4&quot;,&t;16,0x0002,1,&quot;TX 802.11&quot; )&t;
singleline_comment|//  bit 1   (0x0002)  0=RFC1042 is used for transmit encapsulation.  1=802.1H is used for transmit encapsulation.
DECL|macro|awc_RID_Enc_Action_TX_4_802_11
mdefine_line|#define awc_RID_Enc_Action_TX_4_802_11 &t;&t;awc_def_Enc_RID(0x0010,&quot;Tx Action 4&quot;,&t;16,0x0002,0,&quot;TX RFC1042&quot;)&t;
singleline_comment|//  bit 1   (0x0002)  0=RFC1042 is used for transmit encapsulation.  1=802.1H is used for transmit encapsulation.
DECL|macro|awc_RID_Enc_EtherType5
mdefine_line|#define awc_RID_Enc_EtherType5 &t;&t;&t;awc_def_Enc_RID(0x0012,&quot;EtherType5&quot;,&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//       0   Note, the ethertype values are in network transmission order.  So IP (0x800) is actually (0x0008). Zero ends the list and selects the default action.
DECL|macro|awc_RID_Enc_Action_RX_5
mdefine_line|#define awc_RID_Enc_Action_RX_5 &t;&t;awc_def_Enc_RID(0x0014,&quot;RX Action 5&quot;,&t;16,0x0001,0,NULL)&t;
singleline_comment|//       0   This field is bit encoded as follows:
DECL|macro|awc_RID_Enc_Action_RX_5_RFC_1042
mdefine_line|#define awc_RID_Enc_Action_RX_5_RFC_1042 &t;awc_def_Enc_RID(0x0014,&quot;RX Action 5&quot;,&t;16,0x0001,1,&quot;RX RFC1042&quot;)&t;
singleline_comment|//  bit 0   (0x0001)  1=RFC1042 is kept for receive packets.
DECL|macro|awc_RID_Enc_Action_RX_5_802_11
mdefine_line|#define awc_RID_Enc_Action_RX_5_802_11 &t;&t;awc_def_Enc_RID(0x0014,&quot;RX Action 5&quot;,&t;16,0x0001,0,&quot;RX 802.11&quot;)&t;
singleline_comment|//  bit 0   (0x0001)  1=RFC1042 is kept for receive packets.
DECL|macro|awc_RID_Enc_Action_TX_5
mdefine_line|#define awc_RID_Enc_Action_TX_5 &t;&t;awc_def_Enc_RID(0x0014,&quot;TX Action 5&quot;,&t;16,0x0002,0,NULL)&t;
singleline_comment|//
DECL|macro|awc_RID_Enc_Action_TX_5_RFC_1042
mdefine_line|#define awc_RID_Enc_Action_TX_5_RFC_1042 &t;awc_def_Enc_RID(0x0014,&quot;TX Action 5&quot;,&t;16,0x0002,1,&quot;TX 802.11&quot; )&t;
singleline_comment|//  bit 1   (0x0002)  0=RFC1042 is used for transmit encapsulation.  1=802.1H is used for transmit encapsulation.
DECL|macro|awc_RID_Enc_Action_TX_5_802_11
mdefine_line|#define awc_RID_Enc_Action_TX_5_802_11 &t;&t;awc_def_Enc_RID(0x0014,&quot;Tx Action 5&quot;,&t;16,0x0002,0,&quot;TX RFC1042&quot;)&t;
singleline_comment|//  bit 1   (0x0002)  0=RFC1042 is used for transmit encapsulation.  1=802.1H is used for transmit encapsulation.
DECL|macro|awc_RID_Enc_EtherType6
mdefine_line|#define awc_RID_Enc_EtherType6 &t;&t;&t;awc_def_Enc_RID(0x0016,&quot;EtherType6&quot;,&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//       0   Note, the ethertype values are in network transmission order.  So IP (0x800) is actually (0x0008). Zero ends the list and selects the default action.
DECL|macro|awc_RID_Enc_Action_RX_6
mdefine_line|#define awc_RID_Enc_Action_RX_6 &t;&t;awc_def_Enc_RID(0x0018,&quot;RX Action 6&quot;,&t;16,0x0001,0,NULL)&t;
singleline_comment|//       0   This field is bit encoded as follows:
DECL|macro|awc_RID_Enc_Action_RX_6_RFC_1042
mdefine_line|#define awc_RID_Enc_Action_RX_6_RFC_1042 &t;awc_def_Enc_RID(0x0018,&quot;RX Action 6&quot;,&t;16,0x0001,1,&quot;RX RFC1042&quot;)&t;
singleline_comment|//  bit 0   (0x0001)  1=RFC1042 is kept for receive packets.
DECL|macro|awc_RID_Enc_Action_RX_6_802_11
mdefine_line|#define awc_RID_Enc_Action_RX_6_802_11 &t;&t;awc_def_Enc_RID(0x0018,&quot;RX Action 6&quot;,&t;16,0x0001,0,&quot;RX 802.11&quot;)&t;
singleline_comment|//  bit 0   (0x0001)  1=RFC1042 is kept for receive packets.
DECL|macro|awc_RID_Enc_Action_TX_6
mdefine_line|#define awc_RID_Enc_Action_TX_6 &t;&t;awc_def_Enc_RID(0x0018,&quot;TX Action 6&quot;,&t;16,0x0002,0,NULL)&t;
singleline_comment|//
DECL|macro|awc_RID_Enc_Action_TX_6_RFC_1042
mdefine_line|#define awc_RID_Enc_Action_TX_6_RFC_1042 &t;awc_def_Enc_RID(0x0018,&quot;TX Action 6&quot;,&t;16,0x0002,1,&quot;TX 802.11&quot; )&t;
singleline_comment|//  bit 1   (0x0002)  0=RFC1042 is used for transmit encapsulation.  1=802.1H is used for transmit encapsulation.
DECL|macro|awc_RID_Enc_Action_TX_6_802_11
mdefine_line|#define awc_RID_Enc_Action_TX_6_802_11 &t;&t;awc_def_Enc_RID(0x0018,&quot;Tx Action 6&quot;,&t;16,0x0002,0,&quot;TX RFC1042&quot;)&t;
singleline_comment|//  bit 1   (0x0002)  0=RFC1042 is used for transmit encapsulation.  1=802.1H is used for transmit encapsulation.
DECL|macro|awc_RID_Enc_EtherType7
mdefine_line|#define awc_RID_Enc_EtherType7 &t;&t;&t;awc_def_Enc_RID(0x001A,&quot;EtherType7&quot;,&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//       0   Note, the ethertype values are in network transmission order.  So IP (0x800) is actually (0x0008). Zero ends the list and selects the default action.
DECL|macro|awc_RID_Enc_Action_RX_7
mdefine_line|#define awc_RID_Enc_Action_RX_7 &t;&t;awc_def_Enc_RID(0x001C,&quot;RX Action 8&quot;,&t;16,0x0001,0,NULL)&t;
singleline_comment|//       0   This field is bit encoded as follows:
DECL|macro|awc_RID_Enc_Action_RX_7_RFC_1042
mdefine_line|#define awc_RID_Enc_Action_RX_7_RFC_1042 &t;awc_def_Enc_RID(0x001C,&quot;RX Action 7&quot;,&t;16,0x0001,1,&quot;RX RFC1042&quot;)&t;
singleline_comment|//  bit 0   (0x0001)  1=RFC1042 is kept for receive packets.
DECL|macro|awc_RID_Enc_Action_RX_7_802_11
mdefine_line|#define awc_RID_Enc_Action_RX_7_802_11 &t;&t;awc_def_Enc_RID(0x001C,&quot;RX Action 7&quot;,&t;16,0x0001,0,&quot;RX 802.11&quot;)&t;
singleline_comment|//  bit 0   (0x0001)  1=RFC1042 is kept for receive packets.
DECL|macro|awc_RID_Enc_Action_TX_7
mdefine_line|#define awc_RID_Enc_Action_TX_7 &t;&t;awc_def_Enc_RID(0x001C,&quot;TX Action 7&quot;,&t;16,0x0002,0,NULL)&t;
singleline_comment|//
DECL|macro|awc_RID_Enc_Action_TX_7_RFC_1042
mdefine_line|#define awc_RID_Enc_Action_TX_7_RFC_1042 &t;awc_def_Enc_RID(0x001C,&quot;TX Action 7&quot;,&t;16,0x0002,1,&quot;TX 802.11&quot; )&t;
singleline_comment|//  bit 1   (0x0002)  0=RFC1042 is used for transmit encapsulation.  1=802.1H is used for transmit encapsulation.
DECL|macro|awc_RID_Enc_Action_TX_7_802_11
mdefine_line|#define awc_RID_Enc_Action_TX_7_802_11 &t;&t;awc_def_Enc_RID(0x001C,&quot;Tx Action 7&quot;,&t;16,0x0002,0,&quot;TX RFC1042&quot;)&t;
singleline_comment|//  bit 1   (0x0002)  0=RFC1042 is used for transmit encapsulation.  1=802.1H is used for transmit encapsulation.
DECL|macro|awc_RID_Enc_EtherType8
mdefine_line|#define awc_RID_Enc_EtherType8 &t;&t;&t;awc_def_Enc_RID(0x001E,&quot;EtherType7&quot;,&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//       0   Note, the ethertype values are in network transmission order.  So IP (0x800) is actually (0x0008). Zero ends the list and selects the default action.
DECL|macro|awc_RID_Enc_Action_RX_8
mdefine_line|#define awc_RID_Enc_Action_RX_8 &t;&t;awc_def_Enc_RID(0x0020,&quot;RX Action 8&quot;,&t;16,0x0001,0,NULL)&t;
singleline_comment|//       0   This field is bit encoded as follows:
DECL|macro|awc_RID_Enc_Action_RX_8_RFC_1042
mdefine_line|#define awc_RID_Enc_Action_RX_8_RFC_1042 &t;awc_def_Enc_RID(0x0020,&quot;RX Action 8&quot;,&t;16,0x0001,1,&quot;RX RFC1042&quot;)&t;
singleline_comment|//  bit 0   (0x0001)  1=RFC1042 is kept for receive packets.
DECL|macro|awc_RID_Enc_Action_RX_8_802_11
mdefine_line|#define awc_RID_Enc_Action_RX_8_802_11 &t;&t;awc_def_Enc_RID(0x0020,&quot;RX Action 8&quot;,&t;16,0x0001,0,&quot;RX 802.11&quot;)&t;
singleline_comment|//  bit 0   (0x0001)  1=RFC1042 is kept for receive packets.
DECL|macro|awc_RID_Enc_Action_TX_8
mdefine_line|#define awc_RID_Enc_Action_TX_8 &t;&t;awc_def_Enc_RID(0x0020,&quot;TX Action 8&quot;,&t;16,0x0002,0,NULL)&t;
singleline_comment|//
DECL|macro|awc_RID_Enc_Action_TX_8_RFC_1042
mdefine_line|#define awc_RID_Enc_Action_TX_8_RFC_1042 &t;awc_def_Enc_RID(0x0020,&quot;TX Action 8&quot;,&t;16,0x0002,1,&quot;TX 802.11&quot; )&t;
singleline_comment|//  bit 1   (0x0002)  0=RFC1042 is used for transmit encapsulation.  1=802.1H is used for transmit encapsulation.
DECL|macro|awc_RID_Enc_Action_TX_8_802_11
mdefine_line|#define awc_RID_Enc_Action_TX_8_802_11 &t;&t;awc_def_Enc_RID(0x0020,&quot;Tx Action 8&quot;,&t;16,0x0002,0,&quot;TX RFC1042&quot;)&t;
singleline_comment|//  bit 1   (0x0002)  0=RFC1042 is used for transmit encapsulation.  1=802.1H is used for transmit encapsulation.
singleline_comment|// WEP Key volatile
DECL|macro|awc_RID_WEPv_RidLen
mdefine_line|#define awc_RID_WEPv_RidLen &t;&t;&t;awc_def_WEPv_RID(0x0000,&quot;RidLen&quot;,&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//       read-only     Length of this RID including the length field
DECL|macro|awc_RID_WEPv_KeyIndex
mdefine_line|#define awc_RID_WEPv_KeyIndex &t;&t;&t;awc_def_WEPv_RID(0x0002,&quot;KeyIndex&quot;,&t;16,0xffff,0,&quot;Index to list of keys&quot;)&t;
DECL|macro|awc_RID_WEPv_Address
mdefine_line|#define awc_RID_WEPv_Address &t;&t;&t;awc_def_WEPv_RID(0x0004,&quot;Address&quot;,&t;48,0xff,0,&quot;mac address related to keys&quot;)&t;
DECL|macro|awc_RID_WEPv_KeyLen
mdefine_line|#define awc_RID_WEPv_KeyLen &t;&t;&t;awc_def_WEPv_RID(0x000A,&quot;KeyLen&quot;,&t;16,0xffff,0,&quot;Key Length (0 and 5 are valid)&quot;)&t;
DECL|macro|awc_RID_WEPv_Key
mdefine_line|#define awc_RID_WEPv_Key &t;&t;&t;awc_def_WEPv_RID(0x000C,&quot;Key&quot;,&t;&t;128,0xff,0,&quot;Key itself in hex coding&quot;)
DECL|macro|awc_RID_WEPv_KeyAscii
mdefine_line|#define awc_RID_WEPv_KeyAscii &t;&t;&t;awc_def_WEPv_RID(0x000C,&quot;KeyAscii&quot;,&t;128,0,0,&quot;Key itself in ascii coding&quot;)
singleline_comment|// WEP Key non-volatile
DECL|macro|awc_RID_WEPnv_RidLen
mdefine_line|#define awc_RID_WEPnv_RidLen &t;&t;&t;awc_def_WEPnv_RID(0x0000,&quot;RidLen&quot;,&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//       read-only     Length of this RID including the length field
DECL|macro|awc_RID_WEPnv_KeyIndex
mdefine_line|#define awc_RID_WEPnv_KeyIndex &t;&t;&t;awc_def_WEPnv_RID(0x0002,&quot;KeyIndex&quot;,&t;16,0xffff,0,&quot;Index to list of keys&quot;)&t;
DECL|macro|awc_RID_WEPnv_Address
mdefine_line|#define awc_RID_WEPnv_Address &t;&t;&t;awc_def_WEPnv_RID(0x0004,&quot;Address&quot;,&t;48,0xff,0,&quot;mac address related to keys&quot;)&t;
DECL|macro|awc_RID_WEPnv_KeyLen
mdefine_line|#define awc_RID_WEPnv_KeyLen &t;&t;&t;awc_def_WEPnv_RID(0x000A,&quot;KeyLen&quot;,&t;16,0xffff,0,&quot;Key Length (0 and 5 are valid)&quot;)&t;
DECL|macro|awc_RID_WEPnv_Key
mdefine_line|#define awc_RID_WEPnv_Key &t;&t;&t;awc_def_WEPnv_RID(0x000C,&quot;Key&quot;,&t;&t;128,0xff,0,&quot;Key itself in hex coding&quot;)
DECL|macro|awc_RID_WEPnv_KeyAscii
mdefine_line|#define awc_RID_WEPnv_KeyAscii &t;&t;&t;awc_def_WEPnv_RID(0x000C,&quot;KeyAscii&quot;,&t;128,0,0,&quot;Key itself in ascii coding&quot;)
singleline_comment|// Modulation
DECL|macro|awc_RID_Modulation_RidLen
mdefine_line|#define awc_RID_Modulation_RidLen &t;&t;awc_def_Modulation_RID(0x0000,&quot;RidLen&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//       read-only     Length of this RID including the length field
DECL|macro|awc_RID_Modulation_Modulation
mdefine_line|#define awc_RID_Modulation_Modulation &t;&t;awc_def_Modulation_RID(0x0002,&quot;Modulation&quot;,&t;16,0xffff,0,&quot;Modulation&quot;)&t;
singleline_comment|//   Capabilities RID
DECL|macro|awc_RID_Cap_RidLen
mdefine_line|#define awc_RID_Cap_RidLen &t;&t;awc_def_Cap_RID(0x0000,&quot;RidLen&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//        read-only      Length of this RID including the length field
DECL|macro|awc_RID_Cap_OUI
mdefine_line|#define awc_RID_Cap_OUI &t;&t;awc_def_Cap_RID(0x0002,&quot;OUI&quot;,&t;&t;&t;24,0xffff,0,&quot;&quot;)&t;
singleline_comment|//      0x00 0x40      This field will give the manufacturer OUI (fourth byte   always zero).
DECL|macro|awc_RID_Cap_ProductNum
mdefine_line|#define awc_RID_Cap_ProductNum &t;&t;awc_def_Cap_RID(0x0006,&quot;ProductNum&quot;,&t;&t;24,0xffff,0,&quot;&quot;)&t;
singleline_comment|//      0x0004         This field will give the product number.
DECL|macro|awc_RID_Cap_ManufacturerName
mdefine_line|#define awc_RID_Cap_ManufacturerName &t;awc_def_Cap_RID(0x0008,&quot;ManufacturerName&quot;,&t;255,0,0,&quot;&quot;)&t;
singleline_comment|//      ASCIIz encoding of manufacturer name.
DECL|macro|awc_RID_Cap_ProductName
mdefine_line|#define awc_RID_Cap_ProductName &t;awc_def_Cap_RID(0x0028,&quot;ProductName&quot;,&t;&t;128,0,0,&quot;&quot;)&t;
singleline_comment|//     PC4500         ASCIIz encoding of product name.
DECL|macro|awc_RID_Cap_ProductVersion
mdefine_line|#define awc_RID_Cap_ProductVersion &t;awc_def_Cap_RID(0x0038,&quot;ProductVersion&quot;,&t;64,0,0,&quot;&quot;)&t;
singleline_comment|//      .    ASCIIz encoding of product (firmware?) version.
DECL|macro|awc_RID_Cap_FactoryAddress
mdefine_line|#define awc_RID_Cap_FactoryAddress &t;awc_def_Cap_RID(0x0040,&quot;FactoryAddress&quot;,&t;48,0xff,0,&quot;&quot;)&t;
singleline_comment|// This field will contain the OEM assigned IEEE address. If there is no OEM address assigned, the Aironet assigned  IEEE Address will be returned in this field.
DECL|macro|awc_RID_Cap_AironetAddress
mdefine_line|#define awc_RID_Cap_AironetAddress &t;awc_def_Cap_RID(0x0046,&quot;AironetAddress&quot;,&t;48,0xff,0,&quot;&quot;)&t;
singleline_comment|// This field will contain the Aironet factory assigned    IEEE address.
DECL|macro|awc_RID_Cap_RadioSpreadType_DS
mdefine_line|#define awc_RID_Cap_RadioSpreadType_DS &t;awc_def_Cap_RID(0x004C,&quot;RadioType_FH&quot;,&t;&t;16,0x0001,1,&quot;&quot;)&t;
singleline_comment|//&t;  0x01 = 802.11 FH
DECL|macro|awc_RID_Cap_RadioSpreadType_FH
mdefine_line|#define awc_RID_Cap_RadioSpreadType_FH &t;awc_def_Cap_RID(0x004C,&quot;RadioType_DS&quot;,&t;&t;16,0x0002,2,&quot;&quot;)&t;
singleline_comment|//&t;  0x02 = 802.11 DS
DECL|macro|awc_RID_Cap_RadioSpreadType_Legacy
mdefine_line|#define awc_RID_Cap_RadioSpreadType_Legacy awc_def_Cap_RID(0x004C,&quot;RadioType_Legacy&quot;,&t;16,0x0004,4,&quot;&quot;)&t;
singleline_comment|//&t;  0x04 = LM2000 (Legacy) DS //  Note, more than one bit may be set for radios     supporting multiple modes of operation.
DECL|macro|awc_RID_Cap_RegDomain
mdefine_line|#define awc_RID_Cap_RegDomain &t;&t;awc_def_Cap_RID(0x004E,&quot;RegDomain&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|// This field indicates the registration domain/country   The values as assigned by 802.11 will be used.
DECL|macro|awc_RID_Cap_Callid
mdefine_line|#define awc_RID_Cap_Callid &t;&t;awc_def_Cap_RID(0x0050,&quot;Callid&quot;,&t;&t;48,0xff,0,&quot;&quot;)&t;
singleline_comment|// This field indicates the callid assigned to the unit (if  RegDomain is Japan) Each nibble will contain one decimal digit of the 12 digit callid. (Note, this is not the encoded format).
DECL|macro|awc_RID_Cap_SupportedRates
mdefine_line|#define awc_RID_Cap_SupportedRates &t;awc_def_Cap_RID(0x0056,&quot;SupportedRates&quot;,&t;64,0xff,0,&quot;&quot;)&t;
singleline_comment|//      0x02, 0x04,    This field will indicate the 802.11 supported rates as  specified in the rates.
DECL|macro|awc_RID_Cap_RxDiversity
mdefine_line|#define awc_RID_Cap_RxDiversity &t;awc_def_Cap_RID(0x005E,&quot;RxDiversity&quot;,&t;&t;8 ,0xff,0,&quot;&quot;)&t;
singleline_comment|//         0x03 This field will indicate the number of antennas  supported as a bit mask.
DECL|macro|awc_RID_Cap_TxDiversity
mdefine_line|#define awc_RID_Cap_TxDiversity &t;awc_def_Cap_RID(0x005F,&quot;TxDiversity&quot;,&t;&t;8 ,0xff,0,&quot;&quot;)&t;
singleline_comment|//         0x03 This field will indicate the number of antennas supported as a bit mask.
DECL|macro|awc_RID_Cap_TxPowerLevels
mdefine_line|#define awc_RID_Cap_TxPowerLevels &t;awc_def_Cap_RID(0x0060,&quot;TxPowerLevels&quot;,&t;128,0xff,0,&quot;&quot;)&t;
singleline_comment|//     250  This table indicates the supported transmit power  levels. (values are in mW)  Zero terminates the list. Note, this may be further restricted depending on   country selected.
DECL|macro|awc_RID_Cap_HardwareVersion
mdefine_line|#define awc_RID_Cap_HardwareVersion &t;awc_def_Cap_RID(0x0070,&quot;HardwareVersion&quot;,&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//        0    This indicates the revision of hardware.
DECL|macro|awc_RID_Cap_HardwareCapabilit
mdefine_line|#define awc_RID_Cap_HardwareCapabilit &t;awc_def_Cap_RID(0x0072,&quot;HardwareCapabilit&quot;,&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//        0    This is a bit-mapped field indicating harware  capabilities. No bits have been assigned yet. Initially this is zero.
DECL|macro|awc_RID_Cap_TemperatureRange
mdefine_line|#define awc_RID_Cap_TemperatureRange &t;awc_def_Cap_RID(0x0074,&quot;TemperatureRange&quot;,&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//        0    This indicates the temperature range capability.
DECL|macro|awc_RID_Cap_SoftwareVersion
mdefine_line|#define awc_RID_Cap_SoftwareVersion &t;awc_def_Cap_RID(0x0076,&quot;SoftwareVersion&quot;,&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//        0    This indicates the revision of software.
DECL|macro|awc_RID_Cap_SoftwareVersion_major
mdefine_line|#define awc_RID_Cap_SoftwareVersion_major &t;awc_def_Cap_RID(0x0076,&quot;SoftwareVersion major&quot;,&t;16,0xff00,0,&quot;&quot;)&t;
singleline_comment|//  The upper byte indicates the major version and the
DECL|macro|awc_RID_Cap_SoftwareVersion_minor
mdefine_line|#define awc_RID_Cap_SoftwareVersion_minor &t;awc_def_Cap_RID(0x0076,&quot;SoftwareVersion minor&quot;,&t;16,0x00ff,0,&quot;&quot;)&t;
singleline_comment|//  lower byte the minor version.
DECL|macro|awc_RID_Cap_SoftwareSubVersion
mdefine_line|#define awc_RID_Cap_SoftwareSubVersion &t;awc_def_Cap_RID(0x0078,&quot;SoftwareSubVersio&quot;,&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//        0    This indicates the sub-revision of software.
DECL|macro|awc_RID_Cap_InterfaceVersion
mdefine_line|#define awc_RID_Cap_InterfaceVersion&t;awc_def_Cap_RID(0x007A,&quot;InterfaceVersion&quot;,&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//        0    This indicates the revision of the interface. This will be bumped whenever there are incompatible  modifications made to the interfac  This may be bumped on first release to ensure that  &quot;unreleased&quot; utilities/drivers become unusable.
DECL|macro|awc_RID_Cap_SoftwareCapabilities
mdefine_line|#define awc_RID_Cap_SoftwareCapabilities awc_def_Cap_RID(0x007C,&quot;SoftwareCapabiliti&quot;,&t;160,0xff,0,&quot;&quot;)&t;
singleline_comment|//    0    This field gives a bit mapped indication of capabilities. No capability bits have yet been assigned.
DECL|macro|awc_RID_Cap_BootBlockVersion
mdefine_line|#define awc_RID_Cap_BootBlockVersion &t;awc_def_Cap_RID(0x007E,&quot;BootBlockVersion &quot;,&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|// This indicates the revision of bootblock software. The upper byte indicates the major version and the lower byte the minor version.  Note, BCD encoding is used. (version 2.11 would be  0x0211.)
singleline_comment|// Status RID 
DECL|macro|awc_RID_Status_RidLen
mdefine_line|#define awc_RID_Status_RidLen &t;&t;awc_def_Stat_RID( 0x0000,&quot;RidLen&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;&t;
singleline_comment|//    Length of this RID including the length field
DECL|macro|awc_RID_Status_MacAddress
mdefine_line|#define awc_RID_Status_MacAddress &t;awc_def_Stat_RID( 0x0002,&quot;MacAddress&quot;,&t;&t;48,0xff,0,&quot;&quot;)&t;&t;
singleline_comment|//  The MAC address in use by the station.
DECL|macro|awc_RID_Status_OperationalMode
mdefine_line|#define awc_RID_Status_OperationalMode &t;awc_def_Stat_RID( 0x0008,&quot;OperationalMode&quot;,&t;16,0xffff,0,NULL)&t;
singleline_comment|//    Bit-mapped.
DECL|macro|awc_RID_Status_Configured
mdefine_line|#define awc_RID_Status_Configured &t;awc_def_Stat_RID( 0x0008,&quot;OperationalMode Configured&quot;,&t;16,0x0001,1,&quot;Configured&quot;)&t;
singleline_comment|//
DECL|macro|awc_RID_Status_MAC_Enabled
mdefine_line|#define awc_RID_Status_MAC_Enabled &t;awc_def_Stat_RID( 0x0008,&quot;OperationalMode MAC Enabled&quot;,&t;16,0x0002,2,&quot;MAC Enabled&quot;)&t;
singleline_comment|//
DECL|macro|awc_RID_Status_Receive_Enabled
mdefine_line|#define awc_RID_Status_Receive_Enabled &t;awc_def_Stat_RID( 0x0008,&quot;OperationalMode Receive Enabled&quot;,&t;16,0x0004,4,&quot;Receive Enabled&quot;)&t;
singleline_comment|//
DECL|macro|awc_RID_Status_In_Sync
mdefine_line|#define awc_RID_Status_In_Sync &t;&t;awc_def_Stat_RID( 0x0008,&quot;OperationalMode In Sync with cell&quot;,&t;16,0x0010,10,&quot;In Sync with cell&quot;)&t;
singleline_comment|//
DECL|macro|awc_RID_Status_Associated
mdefine_line|#define awc_RID_Status_Associated &t;awc_def_Stat_RID( 0x0008,&quot;OperationalMode Associated&quot;,&t;16,0x0020,20,&quot;Associated&quot;)&t;
singleline_comment|//
DECL|macro|awc_RID_Status_Error
mdefine_line|#define awc_RID_Status_Error &t;&t;awc_def_Stat_RID( 0x0008,&quot;OperationalMode Error&quot;,&t;16,0x8000,0x8000,&quot;Error&quot;)&t;
singleline_comment|//
DECL|macro|awc_RID_Status_ErrorCode
mdefine_line|#define awc_RID_Status_ErrorCode &t;awc_def_Stat_RID( 0x000A,&quot;ErrorCode&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;&t;
singleline_comment|//    Non-zero if an error state has been entered
DECL|macro|awc_RID_Status_CurrentSignalQuality
mdefine_line|#define awc_RID_Status_CurrentSignalQuality awc_def_Stat_RID( 0x000C,&quot;CurrentSignalQuality&quot;,16,0xffff,0,&quot;&quot;)&t;&t;
singleline_comment|//    A measure of the current signal quality.
DECL|macro|awc_RID_Status_SSIDlength
mdefine_line|#define awc_RID_Status_SSIDlength &t;awc_def_Stat_RID( 0x000E,&quot;SSIDlength&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;&t;
singleline_comment|//    This length of the following SSID.
DECL|macro|awc_RID_Status_SSID
mdefine_line|#define awc_RID_Status_SSID &t;&t;awc_def_Stat_RID( 0x0010,&quot;SSID&quot;,&t;&t;255,0,0,&quot;&quot;)&t;&t;
singleline_comment|// The SSID that is currently in effect.
DECL|macro|awc_RID_Status_ApName
mdefine_line|#define awc_RID_Status_ApName &t;&t;awc_def_Stat_RID( 0x0030,&quot;ApName&quot;,&t;&t;128,0,0,&quot;&quot;)&t;&t;
singleline_comment|// The name of the current BSSID (ESS mode only)
DECL|macro|awc_RID_Status_CurrentBssid
mdefine_line|#define awc_RID_Status_CurrentBssid &t;awc_def_Stat_RID( 0x0040,&quot;CurrentBssid&quot;,&t;48,0xff,0,&quot;&quot;)&t;&t;
singleline_comment|// BSSID that is currently in effect.
DECL|macro|awc_RID_Status_PreviousBssid1
mdefine_line|#define awc_RID_Status_PreviousBssid1 &t;awc_def_Stat_RID( 0x0046,&quot;PreviousBssid1&quot;,&t;48,0xff,0,&quot;&quot;)&t;&t;
singleline_comment|// A former BSSID.
DECL|macro|awc_RID_Status_PreviousBssid2
mdefine_line|#define awc_RID_Status_PreviousBssid2 &t;awc_def_Stat_RID( 0x004C,&quot;PreviousBssid2&quot;,&t;48,0xff,0,&quot;&quot;)&t;&t;
singleline_comment|//  A former BSSID.
DECL|macro|awc_RID_Status_PreviousBssid3
mdefine_line|#define awc_RID_Status_PreviousBssid3 &t;awc_def_Stat_RID( 0x0052,&quot;PreviousBssid3&quot;,&t;48,0xff,0,&quot;&quot;)&t;&t;
singleline_comment|//  A former BSSID.
DECL|macro|awc_RID_Status_BeaconPeriod
mdefine_line|#define awc_RID_Status_BeaconPeriod &t;awc_def_Stat_RID( 0x0058,&quot;BeaconPeriod&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|// (kus)        The current beacon period.
DECL|macro|awc_RID_Status_DtimPeriod
mdefine_line|#define awc_RID_Status_DtimPeriod &t;awc_def_Stat_RID( 0x005A,&quot;DtimPeriod&quot;,&t;&t;16,0xffff,0,&quot;units&quot;)&t;
singleline_comment|//    The current DTIM period (number of beacons between DTIMs).
DECL|macro|awc_RID_Status_AtimDuration
mdefine_line|#define awc_RID_Status_AtimDuration &t;awc_def_Stat_RID( 0x005C,&quot;AtimDuration&quot;,&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|// (kus)        The current ATIM window duration. Adhoc/Ibss only
DECL|macro|awc_RID_Status_HopPeriod
mdefine_line|#define awc_RID_Status_HopPeriod &t;awc_def_Stat_RID( 0x005E,&quot;HopPeriod&quot;,&t;&t;16,0xffff,0,&quot;msek&quot;)&t;
singleline_comment|// (kus)        The current hopping period.
DECL|macro|awc_RID_Status_ChannelSet
mdefine_line|#define awc_RID_Status_ChannelSet &t;awc_def_Stat_RID( 0x0060,&quot;ChannelSet&quot;,&t;&t;16,0xffff,0,&quot;Set&quot;)&t;
singleline_comment|//    The current channel set.
DECL|macro|awc_RID_Status_Channel
mdefine_line|#define awc_RID_Status_Channel&t;&t;awc_def_Stat_RID( 0x0062,&quot;Channel&quot;,&t;&t;16,0xffff,0,&quot; &quot;)&t;
singleline_comment|//    The current operating channel.
DECL|macro|awc_RID_Status_HopsToBackbone
mdefine_line|#define awc_RID_Status_HopsToBackbone &t;awc_def_Stat_RID( 0x0064,&quot;HopsToBackbone&quot;,&t;16,0xffff,0,&quot;hops&quot;)&t;
singleline_comment|//    0 indicates a backbone association.
DECL|macro|awc_RID_Status_ApTotalLoad
mdefine_line|#define awc_RID_Status_ApTotalLoad &t;awc_def_Stat_RID( 0x0066,&quot;ApTotalLoad&quot;,&t;16,0xffff,0,&quot;units&quot;)&t;
singleline_comment|//    Total load including broadcast/multicast from backbone.  This is the value extracted from the Aironet element.
DECL|macro|awc_RID_Status_OurGeneratedLoad
mdefine_line|#define awc_RID_Status_OurGeneratedLoad awc_def_Stat_RID( 0x0068,&quot;OurGeneratedLoad&quot;,&t;16,0xffff,0,&quot;units&quot;)&t;
singleline_comment|//   Total load generated by our station (transmitted and received). Excludes received broadcast/multicast traffic.
DECL|macro|awc_RID_Status_AccumulatedArl
mdefine_line|#define awc_RID_Status_AccumulatedArl &t;awc_def_Stat_RID( 0x006A,&quot;AccumulatedArl&quot;,&t;16,0xffff,0,&quot;units&quot;)&t;
singleline_comment|//
singleline_comment|// AP RID
DECL|macro|awc_RID_AP_16RidLen
mdefine_line|#define awc_RID_AP_16RidLen &t;&t;awc_def_AP_RID(0x0000,&quot;RidLen&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//        0x06, read-only Length of this RID including the length field
DECL|macro|awc_RID_AP_TIM_addr
mdefine_line|#define awc_RID_AP_TIM_addr &t;&t;awc_def_AP_RID(0x0002,&quot;TIM Addr&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//        Read only       The &quot;Traffic Indication Map&quot; is updated by the host via
DECL|macro|awc_RID_AP_Airo_addr
mdefine_line|#define awc_RID_AP_Airo_addr &t;&t;awc_def_AP_RID(0x0004,&quot;Airo Addr&quot;,&t;&t;16,0xffff,0,&quot;&quot;)&t;
singleline_comment|//        Read only       The &quot;Aironet Information Element&quot; is updated by the host via the AUX I/O ports. This is the address of the Aironet Element.
singleline_comment|// Statistics RID
DECL|macro|awc_RID_Stats_RidLen
mdefine_line|#define awc_RID_Stats_RidLen &t;&t;awc_def_Stats_RID(0x0000,0x0000,&quot;RidLen&quot;,&t;&t;&quot;Length of the RID including the length field.&quot;)
DECL|macro|awc_RID_Stats_RxOverrunErr
mdefine_line|#define awc_RID_Stats_RxOverrunErr &t;awc_def_Stats_RID(0x0002,0x0004,&quot;Stats_RxOverrunErr&quot;,&t;&quot;Receive overruns -- No buffer available to handle the receive. (result is that the packet is never received)&quot;)
DECL|macro|awc_RID_Stats_RxPlcpCrcErr
mdefine_line|#define awc_RID_Stats_RxPlcpCrcErr &t;awc_def_Stats_RID(0x0004,0x0008,&quot;Stats_RxPlcpCrcErr&quot;,&t;&quot;PLCP header checksum errors (CRC16).&quot;)
DECL|macro|awc_RID_Stats_RxPlcpFormat
mdefine_line|#define awc_RID_Stats_RxPlcpFormat &t;awc_def_Stats_RID(0x0006,0x000C,&quot;Stats_RxPlcpFormat&quot;,&t;&quot;PLCP format errors.&quot;)
DECL|macro|awc_RID_Stats_RxPlcpLength
mdefine_line|#define awc_RID_Stats_RxPlcpLength &t;awc_def_Stats_RID(0x0008,0x0010,&quot;Stats_RxPlcpLength&quot;,&t;&quot;PLCP length is incorrect.&quot;)
DECL|macro|awc_RID_Stats_RxMacCrcErr
mdefine_line|#define awc_RID_Stats_RxMacCrcErr &t;awc_def_Stats_RID(0x000A,0x0014,&quot;Stats_RxMacCrcErr&quot;,&t;&quot;Count of MAC CRC32 errors.&quot;)
DECL|macro|awc_RID_Stats_RxMacCrcOk
mdefine_line|#define awc_RID_Stats_RxMacCrcOk &t;awc_def_Stats_RID(0x000C,0x0018,&quot;Stats_RxMacCrcOk&quot;,&t;&quot;Count of MAC CRC32 received correctly.&quot;)
DECL|macro|awc_RID_Stats_RxWepErr
mdefine_line|#define awc_RID_Stats_RxWepErr &t;&t;awc_def_Stats_RID(0x000E,0x001C,&quot;Stats_RxWepErr&quot;,&t;&quot;Count of all WEP ICV checks that failed. (this value is included in Stats_RxMacCrcOk)&quot;)
DECL|macro|awc_RID_Stats_RxWepOk
mdefine_line|#define awc_RID_Stats_RxWepOk &t;&t;awc_def_Stats_RID(0x0010,0x0020,&quot;Stats_RxWepOk&quot;,&t;&quot;Count of all WEP ICV checks that passed. (this value is  included in Stats_RxMacCrcOk)&quot;)
DECL|macro|awc_RID_Stats_RetryLong
mdefine_line|#define awc_RID_Stats_RetryLong &t;awc_def_Stats_RID(0x0012,0x0024,&quot;Stats_RetryLongCount&quot;,&t;&quot;of all long retries. (Does not include first attempt for a packet).&quot;)
DECL|macro|awc_RID_Stats_RetryShort
mdefine_line|#define awc_RID_Stats_RetryShort &t;awc_def_Stats_RID(0x0014,0x0028,&quot;Stats_RetryShort&quot;,&t;&quot;Count of all short retries. (Does not include first attempt for   a packet).&quot;)
DECL|macro|awc_RID_Stats_MaxRetries
mdefine_line|#define awc_RID_Stats_MaxRetries &t;awc_def_Stats_RID(0x0016,0x002C,&quot;Stats_MaxRetries&quot;,&t;&quot;Count of number of packets that max-retried -- ie were  never ACK-d.&quot;)
DECL|macro|awc_RID_Stats_NoAck
mdefine_line|#define awc_RID_Stats_NoAck &t;&t;awc_def_Stats_RID(0x0018,0x0030,&quot;Stats_NoAck&quot;,&t;&t;&quot;Count of number of times that ACK was not received.&quot;)
DECL|macro|awc_RID_Stats_NoCts
mdefine_line|#define awc_RID_Stats_NoCts &t;&t;awc_def_Stats_RID(0x001A,0x0034,&quot;Stats_NoCts&quot;,&t;&t;&quot;Count of number of timer that CTS was not received.&quot;)
DECL|macro|awc_RID_Stats_RxAck
mdefine_line|#define awc_RID_Stats_RxAck &t;&t;awc_def_Stats_RID(0x001C,0x0038,&quot;Stats_RxAck&quot;,&t;&t;&quot;Count of number of expected ACKs that were received.&quot;)
DECL|macro|awc_RID_Stats_RxCts
mdefine_line|#define awc_RID_Stats_RxCts &t;&t;awc_def_Stats_RID(0x001E,0x003C,&quot;Stats_RxCts&quot;,&t;&t;&quot;Count of number of expected CTSs that were received.&quot;)
DECL|macro|awc_RID_Stats_TxAck
mdefine_line|#define awc_RID_Stats_TxAck &t;&t;awc_def_Stats_RID(0x0020,0x0040,&quot;Stats_TxAck&quot;,&t;&t;&quot;Count of number of ACKs transmitted.&quot;)
DECL|macro|awc_RID_Stats_TxRts
mdefine_line|#define awc_RID_Stats_TxRts &t;&t;awc_def_Stats_RID(0x0022,0x0044,&quot;Stats_TxRts&quot;,&t;&t;&quot;Count of number of RTSs transmitted.&quot;)
DECL|macro|awc_RID_Stats_TxCts
mdefine_line|#define awc_RID_Stats_TxCts &t;&t;awc_def_Stats_RID(0x0024,0x0048,&quot;Stats_TxCts&quot;,&t;&t;&quot;Count of number of CTSs transmitted.&quot;)
DECL|macro|awc_RID_Stats_TxMc
mdefine_line|#define awc_RID_Stats_TxMc &t;&t;awc_def_Stats_RID(0x0026,0x004C,&quot;Stats_TxMc&quot;,&t;&t;&quot; LMAC count of multicast packets sent (uses 802.11  Address1).&quot;)
DECL|macro|awc_RID_Stats_TxBc
mdefine_line|#define awc_RID_Stats_TxBc &t;&t;awc_def_Stats_RID(0x0028,0x0050,&quot;Stats_TxBc&quot;,&t;&t;&quot; LMAC count of broadcast packets sent (uses 802.11&quot;)
DECL|macro|awc_RID_Stats_TxUcFrags
mdefine_line|#define awc_RID_Stats_TxUcFrags &t;awc_def_Stats_RID(0x002A,0x0054,&quot;Stats_TxUcFragsLMAC&quot;,&t;&quot; count of ALL unicast fragments and whole packets sent (uses 802.11 Address1).&quot;)
DECL|macro|awc_RID_Stats_TxUcPackets
mdefine_line|#define awc_RID_Stats_TxUcPackets &t;awc_def_Stats_RID(0x002C,0x0058,&quot;Stats_TxUcPackets&quot;,&t;&quot;LMAC count of unicast packets that were ACKd (uses   802.11 Address 1).&quot;)
DECL|macro|awc_RID_Stats_TxBeacon
mdefine_line|#define awc_RID_Stats_TxBeacon &t;&t;awc_def_Stats_RID(0x002E,0x005C,&quot;Stats_TxBeacon&quot;,&t;&quot; Count of beacon packets transmitted.&quot;)
DECL|macro|awc_RID_Stats_RxBeacon
mdefine_line|#define awc_RID_Stats_RxBeacon &t;&t;awc_def_Stats_RID(0x0030,0x0060,&quot;Stats_RxBeacon&quot;,&t;&quot; Count of beacon packets received matching our BSSID.&quot;)
DECL|macro|awc_RID_Stats_TxSinColl
mdefine_line|#define awc_RID_Stats_TxSinColl &t;awc_def_Stats_RID(0x0032,0x0064,&quot;Stats_TxSinCollTransmit&quot;,&quot; single collisions. **&quot;)
DECL|macro|awc_RID_Stats_TxMulColl
mdefine_line|#define awc_RID_Stats_TxMulColl &t;awc_def_Stats_RID(0x0034,0x0068,&quot;Stats_TxMulCollTransmit&quot;,&quot; multiple collisions. **&quot;)
DECL|macro|awc_RID_Stats_DefersNo
mdefine_line|#define awc_RID_Stats_DefersNo &t;&t;awc_def_Stats_RID(0x0036,0x006C,&quot;Stats_DefersNo Transmit&quot;,&quot; frames sent with no deferral. **&quot;)
DECL|macro|awc_RID_Stats_DefersProt
mdefine_line|#define awc_RID_Stats_DefersProt &t;awc_def_Stats_RID(0x0038,0x0070,&quot;Stats_DefersProt&quot;,&t;&quot; Transmit frames deferred due to protocol.&quot;)
DECL|macro|awc_RID_Stats_DefersEngy
mdefine_line|#define awc_RID_Stats_DefersEngy &t;awc_def_Stats_RID(0x003A,0x0074,&quot;Stats_DefersEngy&quot;,&t;&quot; Transmit frames deferred due to energy detect.&quot;)
DECL|macro|awc_RID_Stats_DupFram
mdefine_line|#define awc_RID_Stats_DupFram &t;&t;awc_def_Stats_RID(0x003C,0x0078,&quot;Stats_DupFram&quot;,&t;&quot;  Duplicate receive frames and fragments.&quot;)
DECL|macro|awc_RID_Stats_RxFragDisc
mdefine_line|#define awc_RID_Stats_RxFragDisc &t;awc_def_Stats_RID(0x003E,0x007C,&quot;Stats_RxFragDisc&quot;,&t;&quot; Received partial frames. (each tally could indicate the  discarding of one or more fragments)&quot;)
DECL|macro|awc_RID_Stats_TxAged
mdefine_line|#define awc_RID_Stats_TxAged &t;&t;awc_def_Stats_RID(0x0040,0x0080,&quot;Stats_TxAged&quot;,&t;&t;&quot;   Transmit packets exceeding maximum transmit lifetime. **&quot;)
DECL|macro|awc_RID_Stats_RxAged
mdefine_line|#define awc_RID_Stats_RxAged &t;&t;awc_def_Stats_RID(0x0042,0x0084,&quot;Stats_RxAgedReceive&quot;,&t;&quot; packets exceeding maximum receive lifetime. **&quot;)
DECL|macro|awc_RID_Stats_LostSync_Max
mdefine_line|#define awc_RID_Stats_LostSync_Max &t;awc_def_Stats_RID(0x0044,0x0088,&quot;Stats_LostSync_Max&quot;,&t;&quot; Lost sync with our cell due to maximum retries occuring. Retry&quot;)
DECL|macro|awc_RID_Stats_LostSync_Mis
mdefine_line|#define awc_RID_Stats_LostSync_Mis &t;awc_def_Stats_RID(0x0046,0x008C,&quot;Stats_LostSync_Mis&quot;,&t;&quot;Lost sync with our cell due to missing too many beacons. sedBeacons&quot;)
DECL|macro|awc_RID_Stats_LostSync_Arl
mdefine_line|#define awc_RID_Stats_LostSync_Arl &t;awc_def_Stats_RID(0x0048,0x0090,&quot;Stats_LostSync_Arl&quot;,&t;&quot;Lost sync with our cell due to Average Retry Level being  Exceeded  exceeded.&quot;)
DECL|macro|awc_RID_Stats_LostSync_Dea
mdefine_line|#define awc_RID_Stats_LostSync_Dea &t;awc_def_Stats_RID(0x004A,0x0094,&quot;Stats_LostSync_Dea&quot;,&t;&quot;Lost sync with our cell due to being deauthenticated.,thed&quot;)
DECL|macro|awc_RID_Stats_LostSync_Disa
mdefine_line|#define awc_RID_Stats_LostSync_Disa &t;awc_def_Stats_RID(0x004C,0x0098,&quot;Stats_LostSync_Disa&quot;,&t;&quot; Lost sync with our cell due to being disassociated. ssoced&quot;)
DECL|macro|awc_RID_Stats_LostSync_Tsf
mdefine_line|#define awc_RID_Stats_LostSync_Tsf &t;awc_def_Stats_RID(0x004E,0x009C,&quot;Stats_LostSync_Tsf&quot;,&t;&quot;Lost sync with our cell due to excessive change in TSF  Timingtiming.&quot;)
DECL|macro|awc_RID_Stats_HostTxMc
mdefine_line|#define awc_RID_Stats_HostTxMc &t;&t;awc_def_Stats_RID(0x0050,0x00A0,&quot;Stats_HostTxMc&quot;,&t;&quot;Count of multicast packets sent by the host.&quot;)
DECL|macro|awc_RID_Stats_HostTxBc
mdefine_line|#define awc_RID_Stats_HostTxBc &t;&t;awc_def_Stats_RID(0x0052,0x00A4,&quot;Stats_HostTxBc&quot;,&t;&quot;Count of broadcast packets sent by the host.&quot;)
DECL|macro|awc_RID_Stats_HostTxUc
mdefine_line|#define awc_RID_Stats_HostTxUc &t;&t;awc_def_Stats_RID(0x0054,0x00A8,&quot;Stats_HostTxUc&quot;,&t;&quot;Count of unicast packets sent by the host.&quot;)
DECL|macro|awc_RID_Stats_HostTxFail
mdefine_line|#define awc_RID_Stats_HostTxFail &t;awc_def_Stats_RID(0x0056,0x00AC,&quot;Stats_HostTxFail&quot;,&t;&quot;  Count of host transmitted packets which failed.&quot;)
DECL|macro|awc_RID_Stats_HostRxMc
mdefine_line|#define awc_RID_Stats_HostRxMc &t;&t;awc_def_Stats_RID(0x0058,0x00B0,&quot;Stats_HostRxMc&quot;,&t;&quot;Count of host received multicast packets.&quot;)
DECL|macro|awc_RID_Stats_HostRxBc
mdefine_line|#define awc_RID_Stats_HostRxBc &t;&t;awc_def_Stats_RID(0x005A,0x00B4,&quot;Stats_HostRxBc&quot;,&t;&quot;Count of host received broadcast packets.&quot;)
DECL|macro|awc_RID_Stats_HostRxUc
mdefine_line|#define awc_RID_Stats_HostRxUc &t;&t;awc_def_Stats_RID(0x005C,0x00B8,&quot;Stats_HostRxUc&quot;,&t;&quot;Count of host received unicast packets.&quot;)
DECL|macro|awc_RID_Stats_HostRxDiscar
mdefine_line|#define awc_RID_Stats_HostRxDiscar &t;awc_def_Stats_RID(0x005E,0x00BC,&quot;Stats_HostRxDiscar&quot;,&t;&quot;Count of host received packets discarded due to:&bslash;n  Host not enabling receive.&bslash;n  Host failing to dequeue receive packets quickly.&bslash;n Packets being discarded due to magic packet mode.&quot;)
DECL|macro|awc_RID_Stats_HmacTxMc
mdefine_line|#define awc_RID_Stats_HmacTxMc &t;&t;awc_def_Stats_RID(0x0060,0x00C0,&quot;Stats_HmacTxMc&quot;,&t;&quot;Count of internally generated multicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats_HmacTxBc
mdefine_line|#define awc_RID_Stats_HmacTxBc &t;&t;awc_def_Stats_RID(0x0062,0x00C4,&quot;Stats_HmacTxBc&quot;,&t;&quot;Count of internally generated broadcast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats_HmacTxUc
mdefine_line|#define awc_RID_Stats_HmacTxUc &t;&t;awc_def_Stats_RID(0x0064,0x00C8,&quot;Stats_HmacTxUc&quot;,&t;&quot;Count of internally generated unicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats_HmacTxFail
mdefine_line|#define awc_RID_Stats_HmacTxFail &t;awc_def_Stats_RID(0x0066,0x00CC,&quot;Stats_HmacTxFail&quot;,&t;&quot;  Count of internally generated transmit packets that failed.&quot;)
DECL|macro|awc_RID_Stats_HmacRxMc
mdefine_line|#define awc_RID_Stats_HmacRxMc &t;&t;awc_def_Stats_RID(0x0068,0x00D0,&quot;Stats_HmacRxMc&quot;,&t;&quot;Count of internally received multicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats_HmacRxBc
mdefine_line|#define awc_RID_Stats_HmacRxBc &t;&t;awc_def_Stats_RID(0x006A,0x00D4,&quot;Stats_HmacRxBc&quot;,&t;&quot;Count of internally received broadcast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats_HmacRxUc
mdefine_line|#define awc_RID_Stats_HmacRxUc &t;&t;awc_def_Stats_RID(0x006C,0x00D8,&quot;Stats_HmacRxUc&quot;,&t;&quot;Count of internally received multicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats_HmacRxDisca
mdefine_line|#define awc_RID_Stats_HmacRxDisca &t;awc_def_Stats_RID(0x006E,0x00DC,&quot;Stats_HmacRxDisca&quot;,&t;&quot; Count of internally received packets that were discarded  (usually because the destination address is not for the host).&quot;)
DECL|macro|awc_RID_Stats_HmacRxAcce
mdefine_line|#define awc_RID_Stats_HmacRxAcce &t;awc_def_Stats_RID(0x0070,0x00E0,&quot;Stats_HmacRxAcce&quot;,&t;&quot;  Count of internally received packets that were accepted&quot;)
DECL|macro|awc_RID_Stats_SsidMismatch
mdefine_line|#define awc_RID_Stats_SsidMismatch &t;awc_def_Stats_RID(0x0072,0x00E4,&quot;Stats_SsidMismatch&quot;,&t;&quot; Count of SSID mismatches.&quot;)
DECL|macro|awc_RID_Stats_ApMismatch
mdefine_line|#define awc_RID_Stats_ApMismatch &t;awc_def_Stats_RID(0x0074,0x00E8,&quot;Stats_ApMismatch&quot;,&t;&quot;  Count of specified AP mismatches.&quot;)
DECL|macro|awc_RID_Stats_RatesMismatc
mdefine_line|#define awc_RID_Stats_RatesMismatc &t;awc_def_Stats_RID(0x0076,0x00EC,&quot;Stats_RatesMismatc&quot;,&t;&quot; Count of rate mismatches.&quot;)
DECL|macro|awc_RID_Stats_AuthReject
mdefine_line|#define awc_RID_Stats_AuthReject &t;awc_def_Stats_RID(0x0078,0x00F0,&quot;Stats_AuthReject&quot;,&t;&quot;  Count of authentication rejections.&quot;)
DECL|macro|awc_RID_Stats_AuthTimeout
mdefine_line|#define awc_RID_Stats_AuthTimeout &t;awc_def_Stats_RID(0x007A,0x00F4,&quot;Stats_AuthTimeout&quot;,&t;&quot; Count of authentication timeouts.&quot;)
DECL|macro|awc_RID_Stats_AssocReject
mdefine_line|#define awc_RID_Stats_AssocReject &t;awc_def_Stats_RID(0x007C,0x00F8,&quot;Stats_AssocReject&quot;,&t;&quot; Count of association rejections.&quot;)
DECL|macro|awc_RID_Stats_AssocTimeout
mdefine_line|#define awc_RID_Stats_AssocTimeout &t;awc_def_Stats_RID(0x007E,0x00FC,&quot;Stats_AssocTimeout&quot;,&t;&quot; Count of association timeouts.&quot;)
DECL|macro|awc_RID_Stats_NewReason
mdefine_line|#define awc_RID_Stats_NewReason &t;awc_def_Stats_RID(0x0080,0x0100,&quot;Stats_NewReason&quot;,&t;&quot;Count of reason/status codes of greater than 19.  (Values of 0 = successful are not counted)&quot;)
DECL|macro|awc_RID_Stats_AuthFail_1
mdefine_line|#define awc_RID_Stats_AuthFail_1 &t;awc_def_Stats_RID(0x0082,0x0104,&quot;Stats_AuthFail_1&quot;,&t;&quot;Unspecified reason.&quot;)
DECL|macro|awc_RID_Stats_AuthFail_2
mdefine_line|#define awc_RID_Stats_AuthFail_2 &t;awc_def_Stats_RID(0x0084,0x0108,&quot;Stats_AuthFail_2&quot;,&t;&quot;Previous authentication no longer valid.&quot;)
DECL|macro|awc_RID_Stats_AuthFail_3
mdefine_line|#define awc_RID_Stats_AuthFail_3 &t;awc_def_Stats_RID(0x0086,0x010C,&quot;Stats_AuthFail_3&quot;,&t;&quot;Deauthenticated because sending station is leaving (has left) IBSS or ESS.&quot;)
DECL|macro|awc_RID_Stats_AuthFail_4
mdefine_line|#define awc_RID_Stats_AuthFail_4 &t;awc_def_Stats_RID(0x0088,0x0110,&quot;Stats_AuthFail_4&quot;,&t;&quot;Disassociated due to inactivity&quot;)
DECL|macro|awc_RID_Stats_AuthFail_5
mdefine_line|#define awc_RID_Stats_AuthFail_5 &t;awc_def_Stats_RID(0x008A,0x0114,&quot;Stats_AuthFail_5&quot;,&t;&quot;Disassociated because AP is unable to handle all currently  associated stations.&quot;)
DECL|macro|awc_RID_Stats_AuthFail_6
mdefine_line|#define awc_RID_Stats_AuthFail_6 &t;awc_def_Stats_RID(0x008C,0x0118,&quot;Stats_AuthFail_6&quot;,&t;&quot;Class 2 Frame received from non-Authenticated station.&quot;)
DECL|macro|awc_RID_Stats_AuthFail_7
mdefine_line|#define awc_RID_Stats_AuthFail_7 &t;awc_def_Stats_RID(0x008E,0x011C,&quot;Stats_AuthFail_7&quot;,&t;&quot;Class 3 Frame received from non-Associated station.&quot;)
DECL|macro|awc_RID_Stats_AuthFail_8
mdefine_line|#define awc_RID_Stats_AuthFail_8 &t;awc_def_Stats_RID(0x0090,0x0120,&quot;Stats_AuthFail_8&quot;,&t;&quot;Disassociated because sending station is leaving (has left)&quot;)
DECL|macro|awc_RID_Stats_AuthFail_9
mdefine_line|#define awc_RID_Stats_AuthFail_9 &t;awc_def_Stats_RID(0x0092,0x0124,&quot;Stats_AuthFail_9&quot;,&t;&quot;Station requesting (Re)Association is not Authenticated&quot;)
DECL|macro|awc_RID_Stats_AuthFail_10
mdefine_line|#define awc_RID_Stats_AuthFail_10 &t;awc_def_Stats_RID(0x0094,0x0128,&quot;Stats_AuthFail_10&quot;,&t;&quot;Cannot support all requested capabilities in the Capability&quot;)
DECL|macro|awc_RID_Stats_AuthFail_11
mdefine_line|#define awc_RID_Stats_AuthFail_11 &t;awc_def_Stats_RID(0x0096,0x012C,&quot;Stats_AuthFail_11&quot;,&t;&quot;Reassociation denied due to inability to confirm&quot;)
DECL|macro|awc_RID_Stats_AuthFail_12
mdefine_line|#define awc_RID_Stats_AuthFail_12 &t;awc_def_Stats_RID(0x0098,0x0130,&quot;Stats_AuthFail_12&quot;,&t;&quot;Association denied due to reason outside the scope of the 802.11&quot;)
DECL|macro|awc_RID_Stats_AuthFail_13
mdefine_line|#define awc_RID_Stats_AuthFail_13 &t;awc_def_Stats_RID(0x009A,0x0134,&quot;Stats_AuthFail_13&quot;,&t;&quot;Responding station does not support the specified Auth Alogorithm&quot;)
DECL|macro|awc_RID_Stats_AuthFail_14
mdefine_line|#define awc_RID_Stats_AuthFail_14 &t;awc_def_Stats_RID(0x009C,0x0138,&quot;Stats_AuthFail_14&quot;,&t;&quot;Received an out of sequence Authentication Frame.&quot;)
DECL|macro|awc_RID_Stats_AuthFail_15
mdefine_line|#define awc_RID_Stats_AuthFail_15 &t;awc_def_Stats_RID(0x009E,0x013C,&quot;Stats_AuthFail_15&quot;,&t;&quot;Authentication rejected due to challenge failure.&quot;)
DECL|macro|awc_RID_Stats_AuthFail_16
mdefine_line|#define awc_RID_Stats_AuthFail_16 &t;awc_def_Stats_RID(0x00A0,0x0140,&quot;Stats_AuthFail_16&quot;,&t;&quot;Authentication rejected due to timeout waiting for next  frame in sequence.&quot;)
DECL|macro|awc_RID_Stats_AuthFail_17
mdefine_line|#define awc_RID_Stats_AuthFail_17 &t;awc_def_Stats_RID(0x00A2,0x0144,&quot;Stats_AuthFail_17&quot;,&t;&quot;Association denied because AP is unable to handle  additional associated stations.&quot;)
DECL|macro|awc_RID_Stats_AuthFail_18
mdefine_line|#define awc_RID_Stats_AuthFail_18 &t;awc_def_Stats_RID(0x00A4,0x0148,&quot;Stats_AuthFail_18&quot;,&t;&quot;Association denied due to requesting station not supportingall basic rates.&quot;)
DECL|macro|awc_RID_Stats_AuthFail_19
mdefine_line|#define awc_RID_Stats_AuthFail_19 &t;awc_def_Stats_RID(0x00A6,0x014C,&quot;Stats_AuthFail_19&quot;,&t;&quot;Reserved&quot;)
DECL|macro|awc_RID_Stats_RxMan
mdefine_line|#define awc_RID_Stats_RxMan &t;&t;awc_def_Stats_RID(0x00A8,0x0150,&quot;Stats_RxMan&quot;,&t;&t;&quot; Count of management packets received and handled.&quot;)
DECL|macro|awc_RID_Stats_TxMan
mdefine_line|#define awc_RID_Stats_TxMan &t;&t;awc_def_Stats_RID(0x00AA,0x0154,&quot;Stats_TxMan&quot;,&t;&t;&quot; Count of management packets transmitted.&quot;)
DECL|macro|awc_RID_Stats_RxRefresh
mdefine_line|#define awc_RID_Stats_RxRefresh &t;awc_def_Stats_RID(0x00AC,0x0158,&quot;Stats_RxRefresh&quot;,&t;&quot; Count of null data packets received.&quot;)
DECL|macro|awc_RID_Stats_TxRefresh
mdefine_line|#define awc_RID_Stats_TxRefresh &t;awc_def_Stats_RID(0x00AE,0x015C,&quot;Stats_TxRefresh&quot;,&t;&quot; Count of null data packets transmitted.&quot;)
DECL|macro|awc_RID_Stats_RxPoll
mdefine_line|#define awc_RID_Stats_RxPoll &t;&t;awc_def_Stats_RID(0x00B0,0x0160,&quot;Stats_RxPoll&quot;,&t;&t;&quot;Count of PS-Poll packets received.&quot;)
DECL|macro|awc_RID_Stats_TxPoll
mdefine_line|#define awc_RID_Stats_TxPoll &t;&t;awc_def_Stats_RID(0x00B2,0x0164,&quot;Stats_TxPoll&quot;,&t;&t;&quot;Count of PS-Poll packets transmitted.&quot;)
DECL|macro|awc_RID_Stats_HostRetries
mdefine_line|#define awc_RID_Stats_HostRetries &t;awc_def_Stats_RID(0x00B4,0x0168,&quot;Stats_HostRetries&quot;,&t;&quot; Count of long and short retries used to transmit host packets  (does not include first attempt).&quot;)
DECL|macro|awc_RID_Stats_LostSync_HostReq
mdefine_line|#define awc_RID_Stats_LostSync_HostReq &t;awc_def_Stats_RID(0x00B6,0x016C,&quot;Stats_LostSync_HostReq&quot;,&quot;Lost sync with our cell due to host request.&quot;)
DECL|macro|awc_RID_Stats_HostTxBytes
mdefine_line|#define awc_RID_Stats_HostTxBytes &t;awc_def_Stats_RID(0x00B8,0x0170,&quot;Stats_HostTxBytes&quot;,&t;&quot; Count of bytes transferred from the host.&quot;)
DECL|macro|awc_RID_Stats_HostRxBytes
mdefine_line|#define awc_RID_Stats_HostRxBytes &t;awc_def_Stats_RID(0x00BA,0x0174,&quot;Stats_HostRxBytes&quot;,&t;&quot; Count of bytes transferred to the host.&quot;)
DECL|macro|awc_RID_Stats_ElapsedUsec
mdefine_line|#define awc_RID_Stats_ElapsedUsec &t;awc_def_Stats_RID(0x00BC,0x0178,&quot;Stats_ElapsedUsec&quot;,&t;&quot; Total time since power up (or clear) in microseconds.&quot;)
DECL|macro|awc_RID_Stats_ElapsedSec
mdefine_line|#define awc_RID_Stats_ElapsedSec &t;awc_def_Stats_RID(0x00BE,0x017C,&quot;Stats_ElapsedSec&quot;,&t;&quot; Total time since power up (or clear) in seconds.&quot;)
DECL|macro|awc_RID_Stats_LostSyncBett
mdefine_line|#define awc_RID_Stats_LostSyncBett &t;awc_def_Stats_RID(0x00C0,0x0180,&quot;Stats_LostSyncBett&quot;,&t;&quot;Lost Sync to switch to a better access point&quot;)
DECL|macro|awc_RID_Stats_delta_RidLen
mdefine_line|#define awc_RID_Stats_delta_RidLen &t;&t;awc_def_Stats_delta_RID(0x0000,0x0000,&quot;RidLen&quot;,&t;&t;&quot;Length of the RID including the length field.&quot;)
DECL|macro|awc_RID_Stats_delta_RxOverrunErr
mdefine_line|#define awc_RID_Stats_delta_RxOverrunErr &t;awc_def_Stats_delta_RID(0x0002,0x0004,&quot;Stats_RxOverrunErr&quot;,&t;&quot;Receive overruns -- No buffer available to handle the receive. (result is that the packet is never received)&quot;)
DECL|macro|awc_RID_Stats_delta_RxPlcpCrcErr
mdefine_line|#define awc_RID_Stats_delta_RxPlcpCrcErr &t;awc_def_Stats_delta_RID(0x0004,0x0008,&quot;Stats_RxPlcpCrcErr&quot;,&t;&quot;PLCP header checksum errors (CRC16).&quot;)
DECL|macro|awc_RID_Stats_delta_RxPlcpFormat
mdefine_line|#define awc_RID_Stats_delta_RxPlcpFormat &t;awc_def_Stats_delta_RID(0x0006,0x000C,&quot;Stats_RxPlcpFormat&quot;,&t;&quot;PLCP format errors.&quot;)
DECL|macro|awc_RID_Stats_delta_RxPlcpLength
mdefine_line|#define awc_RID_Stats_delta_RxPlcpLength &t;awc_def_Stats_delta_RID(0x0008,0x0010,&quot;Stats_RxPlcpLength&quot;,&t;&quot;PLCP length is incorrect.&quot;)
DECL|macro|awc_RID_Stats_delta_RxMacCrcErr
mdefine_line|#define awc_RID_Stats_delta_RxMacCrcErr &t;awc_def_Stats_delta_RID(0x000A,0x0014,&quot;Stats_RxMacCrcErr&quot;,&t;&quot;Count of MAC CRC32 errors.&quot;)
DECL|macro|awc_RID_Stats_delta_RxMacCrcOk
mdefine_line|#define awc_RID_Stats_delta_RxMacCrcOk &t;&t;awc_def_Stats_delta_RID(0x000C,0x0018,&quot;Stats_RxMacCrcOk&quot;,&t;&quot;Count of MAC CRC32 received correctly.&quot;)
DECL|macro|awc_RID_Stats_delta_RxWepErr
mdefine_line|#define awc_RID_Stats_delta_RxWepErr &t;&t;awc_def_Stats_delta_RID(0x000E,0x001C,&quot;Stats_RxWepErr&quot;,&t;&quot;Count of all WEP ICV checks that failed. (this value is included in Stats_RxMacCrcOk)&quot;)
DECL|macro|awc_RID_Stats_delta_RxWepOk
mdefine_line|#define awc_RID_Stats_delta_RxWepOk &t;&t;awc_def_Stats_delta_RID(0x0010,0x0020,&quot;Stats_RxWepOk&quot;,&t;&quot;Count of all WEP ICV checks that passed. (this value is  included in Stats_RxMacCrcOk)&quot;)
DECL|macro|awc_RID_Stats_delta_RetryLong
mdefine_line|#define awc_RID_Stats_delta_RetryLong &t;&t;awc_def_Stats_delta_RID(0x0012,0x0024,&quot;Stats_RetryLongCount&quot;,&t;&quot;of all long retries. (Does not include first attempt for a packet).&quot;)
DECL|macro|awc_RID_Stats_delta_RetryShort
mdefine_line|#define awc_RID_Stats_delta_RetryShort &t;&t;awc_def_Stats_delta_RID(0x0014,0x0028,&quot;Stats_RetryShort&quot;,&t;&quot;Count of all short retries. (Does not include first attempt for   a packet).&quot;)
DECL|macro|awc_RID_Stats_delta_MaxRetries
mdefine_line|#define awc_RID_Stats_delta_MaxRetries &t;&t;awc_def_Stats_delta_RID(0x0016,0x002C,&quot;Stats_MaxRetries&quot;,&t;&quot;Count of number of packets that max-retried -- ie were  never ACKd.&quot;)
DECL|macro|awc_RID_Stats_delta_NoAck
mdefine_line|#define awc_RID_Stats_delta_NoAck &t;&t;awc_def_Stats_delta_RID(0x0018,0x0030,&quot;Stats_NoAck&quot;,&t;&t;&quot;Count of number of times that ACK was not received.&quot;)
DECL|macro|awc_RID_Stats_delta_NoCts
mdefine_line|#define awc_RID_Stats_delta_NoCts &t;&t;awc_def_Stats_delta_RID(0x001A,0x0034,&quot;Stats_NoCts&quot;,&t;&t;&quot;Count of number of timer that CTS was not received.&quot;)
DECL|macro|awc_RID_Stats_delta_RxAck
mdefine_line|#define awc_RID_Stats_delta_RxAck &t;&t;awc_def_Stats_delta_RID(0x001C,0x0038,&quot;Stats_RxAck&quot;,&t;&t;&quot;Count of number of expected ACKs that were received.&quot;)
DECL|macro|awc_RID_Stats_delta_RxCts
mdefine_line|#define awc_RID_Stats_delta_RxCts &t;&t;awc_def_Stats_delta_RID(0x001E,0x003C,&quot;Stats_RxCts&quot;,&t;&t;&quot;Count of number of expected CTSs that were received.&quot;)
DECL|macro|awc_RID_Stats_delta_TxAck
mdefine_line|#define awc_RID_Stats_delta_TxAck &t;&t;awc_def_Stats_delta_RID(0x0020,0x0040,&quot;Stats_TxAck&quot;,&t;&t;&quot;Count of number of ACKs transmitted.&quot;)
DECL|macro|awc_RID_Stats_delta_TxRts
mdefine_line|#define awc_RID_Stats_delta_TxRts &t;&t;awc_def_Stats_delta_RID(0x0022,0x0044,&quot;Stats_TxRts&quot;,&t;&t;&quot;Count of number of RTSs transmitted.&quot;)
DECL|macro|awc_RID_Stats_delta_TxCts
mdefine_line|#define awc_RID_Stats_delta_TxCts &t;&t;awc_def_Stats_delta_RID(0x0024,0x0048,&quot;Stats_TxCts&quot;,&t;&t;&quot;Count of number of CTSs transmitted.&quot;)
DECL|macro|awc_RID_Stats_delta_TxMc
mdefine_line|#define awc_RID_Stats_delta_TxMc &t;&t;awc_def_Stats_delta_RID(0x0026,0x004C,&quot;Stats_TxMc&quot;,&t;&t;&quot; LMAC count of multicast packets sent (uses 802.11  Address1).&quot;)
DECL|macro|awc_RID_Stats_delta_TxBc
mdefine_line|#define awc_RID_Stats_delta_TxBc &t;&t;awc_def_Stats_delta_RID(0x0028,0x0050,&quot;Stats_TxBc&quot;,&t;&t;&quot; LMAC count of broadcast packets sent (uses 802.11&quot;)
DECL|macro|awc_RID_Stats_delta_TxUcFrags
mdefine_line|#define awc_RID_Stats_delta_TxUcFrags &t;&t;awc_def_Stats_delta_RID(0x002A,0x0054,&quot;Stats_TxUcFragsLMAC&quot;,&t;&quot; count of ALL unicast fragments and whole packets sent (uses 802.11 Address1).&quot;)
DECL|macro|awc_RID_Stats_delta_TxUcPackets
mdefine_line|#define awc_RID_Stats_delta_TxUcPackets &t;awc_def_Stats_delta_RID(0x002C,0x0058,&quot;Stats_TxUcPackets&quot;,&t;&quot;LMAC count of unicast packets that were ACKd (uses   802.11 Address 1).&quot;)
DECL|macro|awc_RID_Stats_delta_TxBeacon
mdefine_line|#define awc_RID_Stats_delta_TxBeacon &t;&t;awc_def_Stats_delta_RID(0x002E,0x005C,&quot;Stats_TxBeacon&quot;,&t;&quot; Count of beacon packets transmitted.&quot;)
DECL|macro|awc_RID_Stats_delta_RxBeacon
mdefine_line|#define awc_RID_Stats_delta_RxBeacon &t;&t;awc_def_Stats_delta_RID(0x0030,0x0060,&quot;Stats_RxBeacon&quot;,&t;&quot; Count of beacon packets received matching our BSSID.&quot;)
DECL|macro|awc_RID_Stats_delta_TxSinColl
mdefine_line|#define awc_RID_Stats_delta_TxSinColl &t;&t;awc_def_Stats_delta_RID(0x0032,0x0064,&quot;Stats_TxSinCollTransmit&quot;,&quot; single collisions. **&quot;)
DECL|macro|awc_RID_Stats_delta_TxMulColl
mdefine_line|#define awc_RID_Stats_delta_TxMulColl &t;&t;awc_def_Stats_delta_RID(0x0034,0x0068,&quot;Stats_TxMulCollTransmit&quot;,&quot; multiple collisions. **&quot;)
DECL|macro|awc_RID_Stats_delta_DefersNo
mdefine_line|#define awc_RID_Stats_delta_DefersNo &t;&t;awc_def_Stats_delta_RID(0x0036,0x006C,&quot;Stats_DefersNo Transmit&quot;,&quot; frames sent with no deferral. **&quot;)
DECL|macro|awc_RID_Stats_delta_DefersProt
mdefine_line|#define awc_RID_Stats_delta_DefersProt &t;&t;awc_def_Stats_delta_RID(0x0038,0x0070,&quot;Stats_DefersProt&quot;,&t;&quot; Transmit frames deferred due to protocol.&quot;)
DECL|macro|awc_RID_Stats_delta_DefersEngy
mdefine_line|#define awc_RID_Stats_delta_DefersEngy &t;&t;awc_def_Stats_delta_RID(0x003A,0x0074,&quot;Stats_DefersEngy&quot;,&t;&quot; Transmit frames deferred due to energy detect.&quot;)
DECL|macro|awc_RID_Stats_delta_DupFram
mdefine_line|#define awc_RID_Stats_delta_DupFram &t;&t;awc_def_Stats_delta_RID(0x003C,0x0078,&quot;Stats_DupFram&quot;,&t;&quot;  Duplicate receive frames and fragments.&quot;)
DECL|macro|awc_RID_Stats_delta_RxFragDisc
mdefine_line|#define awc_RID_Stats_delta_RxFragDisc &t;&t;awc_def_Stats_delta_RID(0x003E,0x007C,&quot;Stats_RxFragDisc&quot;,&t;&quot; Received partial frames. (each tally could indicate the  discarding of one or more fragments)&quot;)
DECL|macro|awc_RID_Stats_delta_TxAged
mdefine_line|#define awc_RID_Stats_delta_TxAged &t;&t;awc_def_Stats_delta_RID(0x0040,0x0080,&quot;Stats_TxAged&quot;,&t;&t;&quot;   Transmit packets exceeding maximum transmit lifetime. **&quot;)
DECL|macro|awc_RID_Stats_delta_RxAged
mdefine_line|#define awc_RID_Stats_delta_RxAged &t;&t;awc_def_Stats_delta_RID(0x0042,0x0084,&quot;Stats_RxAgedReceive&quot;,&t;&quot; packets exceeding maximum receive lifetime. **&quot;)
DECL|macro|awc_RID_Stats_delta_LostSync_Max
mdefine_line|#define awc_RID_Stats_delta_LostSync_Max &t;awc_def_Stats_delta_RID(0x0044,0x0088,&quot;Stats_LostSync_Max&quot;,&t;&quot; Lost sync with our cell due to maximum retries occuring. Retry&quot;)
DECL|macro|awc_RID_Stats_delta_LostSync_Mis
mdefine_line|#define awc_RID_Stats_delta_LostSync_Mis &t;awc_def_Stats_delta_RID(0x0046,0x008C,&quot;Stats_LostSync_Mis&quot;,&t;&quot;Lost sync with our cell due to missing too many beacons. sedBeacons&quot;)
DECL|macro|awc_RID_Stats_delta_LostSync_Arl
mdefine_line|#define awc_RID_Stats_delta_LostSync_Arl &t;awc_def_Stats_delta_RID(0x0048,0x0090,&quot;Stats_LostSync_Arl&quot;,&t;&quot;Lost sync with our cell due to Average Retry Level being  Exceeded  exceeded.&quot;)
DECL|macro|awc_RID_Stats_delta_LostSync_Dea
mdefine_line|#define awc_RID_Stats_delta_LostSync_Dea &t;awc_def_Stats_delta_RID(0x004A,0x0094,&quot;Stats_LostSync_Dea&quot;,&t;&quot;Lost sync with our cell due to being deauthenticated.,thed&quot;)
DECL|macro|awc_RID_Stats_delta_LostSync_Disa
mdefine_line|#define awc_RID_Stats_delta_LostSync_Disa &t;awc_def_Stats_delta_RID(0x004C,0x0098,&quot;Stats_LostSync_Disa&quot;,&t;&quot; Lost sync with our cell due to being disassociated. ssoced&quot;)
DECL|macro|awc_RID_Stats_delta_LostSync_Tsf
mdefine_line|#define awc_RID_Stats_delta_LostSync_Tsf &t;awc_def_Stats_delta_RID(0x004E,0x009C,&quot;Stats_LostSync_Tsf&quot;,&t;&quot;Lost sync with our cell due to excessive change in TSF  Timingtiming.&quot;)
DECL|macro|awc_RID_Stats_delta_HostTxMc
mdefine_line|#define awc_RID_Stats_delta_HostTxMc &t;&t;awc_def_Stats_delta_RID(0x0050,0x00A0,&quot;Stats_HostTxMc&quot;,&t;&quot;Count of multicast packets sent by the host.&quot;)
DECL|macro|awc_RID_Stats_delta_HostTxBc
mdefine_line|#define awc_RID_Stats_delta_HostTxBc &t;&t;awc_def_Stats_delta_RID(0x0052,0x00A4,&quot;Stats_HostTxBc&quot;,&t;&quot;Count of broadcast packets sent by the host.&quot;)
DECL|macro|awc_RID_Stats_delta_HostTxUc
mdefine_line|#define awc_RID_Stats_delta_HostTxUc &t;&t;awc_def_Stats_delta_RID(0x0054,0x00A8,&quot;Stats_HostTxUc&quot;,&t;&quot;Count of unicast packets sent by the host.&quot;)
DECL|macro|awc_RID_Stats_delta_HostTxFail
mdefine_line|#define awc_RID_Stats_delta_HostTxFail &t;&t;awc_def_Stats_delta_RID(0x0056,0x00AC,&quot;Stats_HostTxFail&quot;,&t;&quot;  Count of host transmitted packets which failed.&quot;)
DECL|macro|awc_RID_Stats_delta_HostRxMc
mdefine_line|#define awc_RID_Stats_delta_HostRxMc &t;&t;awc_def_Stats_delta_RID(0x0058,0x00B0,&quot;Stats_HostRxMc&quot;,&t;&quot;Count of host received multicast packets.&quot;)
DECL|macro|awc_RID_Stats_delta_HostRxBc
mdefine_line|#define awc_RID_Stats_delta_HostRxBc &t;&t;awc_def_Stats_delta_RID(0x005A,0x00B4,&quot;Stats_HostRxBc&quot;,&t;&quot;Count of host received broadcast packets.&quot;)
DECL|macro|awc_RID_Stats_delta_HostRxUc
mdefine_line|#define awc_RID_Stats_delta_HostRxUc &t;&t;awc_def_Stats_delta_RID(0x005C,0x00B8,&quot;Stats_HostRxUc&quot;,&t;&quot;Count of host received unicast packets.&quot;)
DECL|macro|awc_RID_Stats_delta_HostRxDiscar
mdefine_line|#define awc_RID_Stats_delta_HostRxDiscar &t;awc_def_Stats_delta_RID(0x005E,0x00BC,&quot;Stats_HostRxDiscar&quot;,&t;&quot;Count of host received packets discarded due to:&bslash;n  Host not enabling receive.&bslash;n  Host failing to dequeue receive packets quickly.&bslash;n Packets being discarded due to magic packet mode.&quot;)
DECL|macro|awc_RID_Stats_delta_HmacTxMc
mdefine_line|#define awc_RID_Stats_delta_HmacTxMc &t;&t;awc_def_Stats_delta_RID(0x0060,0x00C0,&quot;Stats_HmacTxMc&quot;,&t;&quot;Count of internally generated multicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats_delta_HmacTxBc
mdefine_line|#define awc_RID_Stats_delta_HmacTxBc &t;&t;awc_def_Stats_delta_RID(0x0062,0x00C4,&quot;Stats_HmacTxBc&quot;,&t;&quot;Count of internally generated broadcast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats_delta_HmacTxUc
mdefine_line|#define awc_RID_Stats_delta_HmacTxUc &t;&t;awc_def_Stats_delta_RID(0x0064,0x00C8,&quot;Stats_HmacTxUc&quot;,&t;&quot;Count of internally generated unicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats_delta_HmacTxFail
mdefine_line|#define awc_RID_Stats_delta_HmacTxFail &t;&t;awc_def_Stats_delta_RID(0x0066,0x00CC,&quot;Stats_HmacTxFail&quot;,&t;&quot;  Count of internally generated transmit packets that failed.&quot;)
DECL|macro|awc_RID_Stats_delta_HmacRxMc
mdefine_line|#define awc_RID_Stats_delta_HmacRxMc &t;&t;awc_def_Stats_delta_RID(0x0068,0x00D0,&quot;Stats_HmacRxMc&quot;,&t;&quot;Count of internally received multicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats_delta_HmacRxBc
mdefine_line|#define awc_RID_Stats_delta_HmacRxBc &t;&t;awc_def_Stats_delta_RID(0x006A,0x00D4,&quot;Stats_HmacRxBc&quot;,&t;&quot;Count of internally received broadcast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats_delta_HmacRxUc
mdefine_line|#define awc_RID_Stats_delta_HmacRxUc &t;&t;awc_def_Stats_delta_RID(0x006C,0x00D8,&quot;Stats_HmacRxUc&quot;,&t;&quot;Count of internally received multicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats_delta_HmacRxDisca
mdefine_line|#define awc_RID_Stats_delta_HmacRxDisca &t;awc_def_Stats_delta_RID(0x006E,0x00DC,&quot;Stats_HmacRxDisca&quot;,&t;&quot; Count of internally received packets that were discarded  (usually because the destination address is not for the host).&quot;)
DECL|macro|awc_RID_Stats_delta_HmacRxAcce
mdefine_line|#define awc_RID_Stats_delta_HmacRxAcce &t;&t;awc_def_Stats_delta_RID(0x0070,0x00E0,&quot;Stats_HmacRxAcce&quot;,&t;&quot;  Count of internally received packets that were accepted&quot;)
DECL|macro|awc_RID_Stats_delta_SsidMismatch
mdefine_line|#define awc_RID_Stats_delta_SsidMismatch &t;awc_def_Stats_delta_RID(0x0072,0x00E4,&quot;Stats_SsidMismatch&quot;,&t;&quot; Count of SSID mismatches.&quot;)
DECL|macro|awc_RID_Stats_delta_ApMismatch
mdefine_line|#define awc_RID_Stats_delta_ApMismatch &t;&t;awc_def_Stats_delta_RID(0x0074,0x00E8,&quot;Stats_ApMismatch&quot;,&t;&quot;  Count of specified AP mismatches.&quot;)
DECL|macro|awc_RID_Stats_delta_RatesMismatc
mdefine_line|#define awc_RID_Stats_delta_RatesMismatc &t;awc_def_Stats_delta_RID(0x0076,0x00EC,&quot;Stats_RatesMismatc&quot;,&t;&quot; Count of rate mismatches.&quot;)
DECL|macro|awc_RID_Stats_delta_AuthReject
mdefine_line|#define awc_RID_Stats_delta_AuthReject &t;&t;awc_def_Stats_delta_RID(0x0078,0x00F0,&quot;Stats_AuthReject&quot;,&t;&quot;  Count of authentication rejections.&quot;)
DECL|macro|awc_RID_Stats_delta_AuthTimeout
mdefine_line|#define awc_RID_Stats_delta_AuthTimeout &t;awc_def_Stats_delta_RID(0x007A,0x00F4,&quot;Stats_AuthTimeout&quot;,&t;&quot; Count of authentication timeouts.&quot;)
DECL|macro|awc_RID_Stats_delta_AssocReject
mdefine_line|#define awc_RID_Stats_delta_AssocReject &t;awc_def_Stats_delta_RID(0x007C,0x00F8,&quot;Stats_AssocReject&quot;,&t;&quot; Count of association rejections.&quot;)
DECL|macro|awc_RID_Stats_delta_AssocTimeout
mdefine_line|#define awc_RID_Stats_delta_AssocTimeout &t;awc_def_Stats_delta_RID(0x007E,0x00FC,&quot;Stats_AssocTimeout&quot;,&t;&quot; Count of association timeouts.&quot;)
DECL|macro|awc_RID_Stats_delta_NewReason
mdefine_line|#define awc_RID_Stats_delta_NewReason &t;&t;awc_def_Stats_delta_RID(0x0080,0x0100,&quot;Stats_NewReason&quot;,&t;&quot;Count of reason/status codes of greater than 19.  (Values of 0 = successful are not counted)&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_1
mdefine_line|#define awc_RID_Stats_delta_AuthFail_1 &t;&t;awc_def_Stats_delta_RID(0x0082,0x0104,&quot;Stats_AuthFail_1&quot;,&t;&quot;Unspecified reason.&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_2
mdefine_line|#define awc_RID_Stats_delta_AuthFail_2 &t;&t;awc_def_Stats_delta_RID(0x0084,0x0108,&quot;Stats_AuthFail_2&quot;,&t;&quot;Previous authentication no longer valid.&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_3
mdefine_line|#define awc_RID_Stats_delta_AuthFail_3 &t;&t;awc_def_Stats_delta_RID(0x0086,0x010C,&quot;Stats_AuthFail_3&quot;,&t;&quot;Deauthenticated because sending station is leaving (has left) IBSS or ESS.&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_4
mdefine_line|#define awc_RID_Stats_delta_AuthFail_4 &t;&t;awc_def_Stats_delta_RID(0x0088,0x0110,&quot;Stats_AuthFail_4&quot;,&t;&quot;Disassociated due to inactivity&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_5
mdefine_line|#define awc_RID_Stats_delta_AuthFail_5 &t;&t;awc_def_Stats_delta_RID(0x008A,0x0114,&quot;Stats_AuthFail_5&quot;,&t;&quot;Disassociated because AP is unable to handle all currently  associated stations.&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_6
mdefine_line|#define awc_RID_Stats_delta_AuthFail_6 &t;&t;awc_def_Stats_delta_RID(0x008C,0x0118,&quot;Stats_AuthFail_6&quot;,&t;&quot;Class 2 Frame received from non-Authenticated station.&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_7
mdefine_line|#define awc_RID_Stats_delta_AuthFail_7 &t;&t;awc_def_Stats_delta_RID(0x008E,0x011C,&quot;Stats_AuthFail_7&quot;,&t;&quot;Class 3 Frame received from non-Associated station.&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_8
mdefine_line|#define awc_RID_Stats_delta_AuthFail_8 &t;&t;awc_def_Stats_delta_RID(0x0090,0x0120,&quot;Stats_AuthFail_8&quot;,&t;&quot;Disassociated because sending station is leaving (has left)&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_9
mdefine_line|#define awc_RID_Stats_delta_AuthFail_9 &t;&t;awc_def_Stats_delta_RID(0x0092,0x0124,&quot;Stats_AuthFail_9&quot;,&t;&quot;Station requesting (Re)Association is not Authenticated&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_10
mdefine_line|#define awc_RID_Stats_delta_AuthFail_10 &t;awc_def_Stats_delta_RID(0x0094,0x0128,&quot;Stats_AuthFail_10&quot;,&t;&quot;Cannot support all requested capabilities in the Capability&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_11
mdefine_line|#define awc_RID_Stats_delta_AuthFail_11 &t;awc_def_Stats_delta_RID(0x0096,0x012C,&quot;Stats_AuthFail_11&quot;,&t;&quot;Reassociation denied due to inability to confirm&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_12
mdefine_line|#define awc_RID_Stats_delta_AuthFail_12 &t;awc_def_Stats_delta_RID(0x0098,0x0130,&quot;Stats_AuthFail_12&quot;,&t;&quot;Association denied due to reason outside the scope of the 802.11&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_13
mdefine_line|#define awc_RID_Stats_delta_AuthFail_13 &t;awc_def_Stats_delta_RID(0x009A,0x0134,&quot;Stats_AuthFail_13&quot;,&t;&quot;Responding station does not support the specified Auth Alogorithm&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_14
mdefine_line|#define awc_RID_Stats_delta_AuthFail_14 &t;awc_def_Stats_delta_RID(0x009C,0x0138,&quot;Stats_AuthFail_14&quot;,&t;&quot;Received an out of sequence Authentication Frame.&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_15
mdefine_line|#define awc_RID_Stats_delta_AuthFail_15 &t;awc_def_Stats_delta_RID(0x009E,0x013C,&quot;Stats_AuthFail_15&quot;,&t;&quot;Authentication rejected due to challenge failure.&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_16
mdefine_line|#define awc_RID_Stats_delta_AuthFail_16 &t;awc_def_Stats_delta_RID(0x00A0,0x0140,&quot;Stats_AuthFail_16&quot;,&t;&quot;Authentication rejected due to timeout waiting for next  frame in sequence.&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_17
mdefine_line|#define awc_RID_Stats_delta_AuthFail_17 &t;awc_def_Stats_delta_RID(0x00A2,0x0144,&quot;Stats_AuthFail_17&quot;,&t;&quot;Association denied because AP is unable to handle  additional associated stations.&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_18
mdefine_line|#define awc_RID_Stats_delta_AuthFail_18 &t;awc_def_Stats_delta_RID(0x00A4,0x0148,&quot;Stats_AuthFail_18&quot;,&t;&quot;Association denied due to requesting station not supportingall basic rates.&quot;)
DECL|macro|awc_RID_Stats_delta_AuthFail_19
mdefine_line|#define awc_RID_Stats_delta_AuthFail_19 &t;awc_def_Stats_delta_RID(0x00A6,0x014C,&quot;Stats_AuthFail_19&quot;,&t;&quot;Reserved&quot;)
DECL|macro|awc_RID_Stats_delta_RxMan
mdefine_line|#define awc_RID_Stats_delta_RxMan &t;&t;awc_def_Stats_delta_RID(0x00A8,0x0150,&quot;Stats_RxMan&quot;,&t;&t;&quot; Count of management packets received and handled.&quot;)
DECL|macro|awc_RID_Stats_delta_TxMan
mdefine_line|#define awc_RID_Stats_delta_TxMan &t;&t;awc_def_Stats_delta_RID(0x00AA,0x0154,&quot;Stats_TxMan&quot;,&t;&t;&quot; Count of management packets transmitted.&quot;)
DECL|macro|awc_RID_Stats_delta_RxRefresh
mdefine_line|#define awc_RID_Stats_delta_RxRefresh &t;&t;awc_def_Stats_delta_RID(0x00AC,0x0158,&quot;Stats_RxRefresh&quot;,&t;&quot; Count of null data packets received.&quot;)
DECL|macro|awc_RID_Stats_delta_TxRefresh
mdefine_line|#define awc_RID_Stats_delta_TxRefresh &t;&t;awc_def_Stats_delta_RID(0x00AE,0x015C,&quot;Stats_TxRefresh&quot;,&t;&quot; Count of null data packets transmitted.&quot;)
DECL|macro|awc_RID_Stats_delta_RxPoll
mdefine_line|#define awc_RID_Stats_delta_RxPoll &t;&t;awc_def_Stats_delta_RID(0x00B0,0x0160,&quot;Stats_RxPoll&quot;,&t;&t;&quot;Count of PS-Poll packets received.&quot;)
DECL|macro|awc_RID_Stats_delta_TxPoll
mdefine_line|#define awc_RID_Stats_delta_TxPoll &t;&t;awc_def_Stats_delta_RID(0x00B2,0x0164,&quot;Stats_TxPoll&quot;,&t;&t;&quot;Count of PS-Poll packets transmitted.&quot;)
DECL|macro|awc_RID_Stats_delta_HostRetries
mdefine_line|#define awc_RID_Stats_delta_HostRetries &t;awc_def_Stats_delta_RID(0x00B4,0x0168,&quot;Stats_HostRetries&quot;,&t;&quot; Count of long and short retries used to transmit host packets  (does not include first attempt).&quot;)
DECL|macro|awc_RID_Stats_delta_LostSync_HostReq
mdefine_line|#define awc_RID_Stats_delta_LostSync_HostReq &t;awc_def_Stats_delta_RID(0x00B6,0x016C,&quot;Stats_LostSync_HostReq&quot;,&quot;Lost sync with our cell due to host request.&quot;)
DECL|macro|awc_RID_Stats_delta_HostTxBytes
mdefine_line|#define awc_RID_Stats_delta_HostTxBytes &t;awc_def_Stats_delta_RID(0x00B8,0x0170,&quot;Stats_HostTxBytes&quot;,&t;&quot; Count of bytes transferred from the host.&quot;)
DECL|macro|awc_RID_Stats_delta_HostRxBytes
mdefine_line|#define awc_RID_Stats_delta_HostRxBytes &t;awc_def_Stats_delta_RID(0x00BA,0x0174,&quot;Stats_HostRxBytes&quot;,&t;&quot; Count of bytes transferred to the host.&quot;)
DECL|macro|awc_RID_Stats_delta_ElapsedUsec
mdefine_line|#define awc_RID_Stats_delta_ElapsedUsec &t;awc_def_Stats_delta_RID(0x00BC,0x0178,&quot;Stats_ElapsedUsec&quot;,&t;&quot; Total time since power up (or clear) in microseconds.&quot;)
DECL|macro|awc_RID_Stats_delta_ElapsedSec
mdefine_line|#define awc_RID_Stats_delta_ElapsedSec &t;&t;awc_def_Stats_delta_RID(0x00BE,0x017C,&quot;Stats_ElapsedSec&quot;,&t;&quot; Total time since power up (or clear) in seconds.&quot;)
DECL|macro|awc_RID_Stats_delta_LostSyncBett
mdefine_line|#define awc_RID_Stats_delta_LostSyncBett &t;awc_def_Stats_delta_RID(0x00C0,0x0180,&quot;Stats_LostSyncBett&quot;,&t;&quot;Lost Sync to switch to a better access point&quot;)
DECL|macro|awc_RID_Stats_clear_RidLen
mdefine_line|#define awc_RID_Stats_clear_RidLen &t;&t;awc_def_Stats_clear_RID(0x0000,0x0000,&quot;RidLen&quot;,&t;&t;&quot;Length of the RID including the length field.&quot;)
DECL|macro|awc_RID_Stats_clear_RxOverrunErr
mdefine_line|#define awc_RID_Stats_clear_RxOverrunErr &t;awc_def_Stats_clear_RID(0x0002,0x0004,&quot;Stats_RxOverrunErr&quot;,&t;&quot;Receive overruns -- No buffer available to handle the receive. (result is that the packet is never received)&quot;)
DECL|macro|awc_RID_Stats_clear_RxPlcpCrcErr
mdefine_line|#define awc_RID_Stats_clear_RxPlcpCrcErr &t;awc_def_Stats_clear_RID(0x0004,0x0008,&quot;Stats_RxPlcpCrcErr&quot;,&t;&quot;PLCP header checksum errors (CRC16).&quot;)
DECL|macro|awc_RID_Stats_clear_RxPlcpFormat
mdefine_line|#define awc_RID_Stats_clear_RxPlcpFormat &t;awc_def_Stats_clear_RID(0x0006,0x000C,&quot;Stats_RxPlcpFormat&quot;,&t;&quot;PLCP format errors.&quot;)
DECL|macro|awc_RID_Stats_clear_RxPlcpLength
mdefine_line|#define awc_RID_Stats_clear_RxPlcpLength &t;awc_def_Stats_clear_RID(0x0008,0x0010,&quot;Stats_RxPlcpLength&quot;,&t;&quot;PLCP length is incorrect.&quot;)
DECL|macro|awc_RID_Stats_clear_RxMacCrcErr
mdefine_line|#define awc_RID_Stats_clear_RxMacCrcErr &t;awc_def_Stats_clear_RID(0x000A,0x0014,&quot;Stats_RxMacCrcErr&quot;,&t;&quot;Count of MAC CRC32 errors.&quot;)
DECL|macro|awc_RID_Stats_clear_RxMacCrcOk
mdefine_line|#define awc_RID_Stats_clear_RxMacCrcOk &t;&t;awc_def_Stats_clear_RID(0x000C,0x0018,&quot;Stats_RxMacCrcOk&quot;,&t;&quot;Count of MAC CRC32 received correctly.&quot;)
DECL|macro|awc_RID_Stats_clear_RxWepErr
mdefine_line|#define awc_RID_Stats_clear_RxWepErr &t;&t;awc_def_Stats_clear_RID(0x000E,0x001C,&quot;Stats_RxWepErr&quot;,&t;&quot;Count of all WEP ICV checks that failed. (this value is included in Stats_RxMacCrcOk)&quot;)
DECL|macro|awc_RID_Stats_clear_RxWepOk
mdefine_line|#define awc_RID_Stats_clear_RxWepOk &t;&t;awc_def_Stats_clear_RID(0x0010,0x0020,&quot;Stats_RxWepOk&quot;,&t;&quot;Count of all WEP ICV checks that passed. (this value is  included in Stats_RxMacCrcOk)&quot;)
DECL|macro|awc_RID_Stats_clear_RetryLong
mdefine_line|#define awc_RID_Stats_clear_RetryLong &t;&t;awc_def_Stats_clear_RID(0x0012,0x0024,&quot;Stats_RetryLongCount&quot;,&t;&quot;of all long retries. (Does not include first attempt for a packet).&quot;)
DECL|macro|awc_RID_Stats_clear_RetryShort
mdefine_line|#define awc_RID_Stats_clear_RetryShort &t;&t;awc_def_Stats_clear_RID(0x0014,0x0028,&quot;Stats_RetryShort&quot;,&t;&quot;Count of all short retries. (Does not include first attempt for   a packet).&quot;)
DECL|macro|awc_RID_Stats_clear_MaxRetries
mdefine_line|#define awc_RID_Stats_clear_MaxRetries &t;&t;awc_def_Stats_clear_RID(0x0016,0x002C,&quot;Stats_MaxRetries&quot;,&t;&quot;Count of number of packets that max-retried -- ie were  never ACKd.&quot;)
DECL|macro|awc_RID_Stats_clear_NoAck
mdefine_line|#define awc_RID_Stats_clear_NoAck &t;&t;awc_def_Stats_clear_RID(0x0018,0x0030,&quot;Stats_NoAck&quot;,&t;&t;&quot;Count of number of times that ACK was not received.&quot;)
DECL|macro|awc_RID_Stats_clear_NoCts
mdefine_line|#define awc_RID_Stats_clear_NoCts &t;&t;awc_def_Stats_clear_RID(0x001A,0x0034,&quot;Stats_NoCts&quot;,&t;&t;&quot;Count of number of timer that CTS was not received.&quot;)
DECL|macro|awc_RID_Stats_clear_RxAck
mdefine_line|#define awc_RID_Stats_clear_RxAck &t;&t;awc_def_Stats_clear_RID(0x001C,0x0038,&quot;Stats_RxAck&quot;,&t;&t;&quot;Count of number of expected ACKs that were received.&quot;)
DECL|macro|awc_RID_Stats_clear_RxCts
mdefine_line|#define awc_RID_Stats_clear_RxCts &t;&t;awc_def_Stats_clear_RID(0x001E,0x003C,&quot;Stats_RxCts&quot;,&t;&t;&quot;Count of number of expected CTSs that were received.&quot;)
DECL|macro|awc_RID_Stats_clear_TxAck
mdefine_line|#define awc_RID_Stats_clear_TxAck &t;&t;awc_def_Stats_clear_RID(0x0020,0x0040,&quot;Stats_TxAck&quot;,&t;&t;&quot;Count of number of ACKs transmitted.&quot;)
DECL|macro|awc_RID_Stats_clear_TxRts
mdefine_line|#define awc_RID_Stats_clear_TxRts &t;&t;awc_def_Stats_clear_RID(0x0022,0x0044,&quot;Stats_TxRts&quot;,&t;&t;&quot;Count of number of RTSs transmitted.&quot;)
DECL|macro|awc_RID_Stats_clear_TxCts
mdefine_line|#define awc_RID_Stats_clear_TxCts &t;&t;awc_def_Stats_clear_RID(0x0024,0x0048,&quot;Stats_TxCts&quot;,&t;&t;&quot;Count of number of CTSs transmitted.&quot;)
DECL|macro|awc_RID_Stats_clear_TxMc
mdefine_line|#define awc_RID_Stats_clear_TxMc &t;&t;awc_def_Stats_clear_RID(0x0026,0x004C,&quot;Stats_TxMc&quot;,&t;&t;&quot; LMAC count of multicast packets sent (uses 802.11  Address1).&quot;)
DECL|macro|awc_RID_Stats_clear_TxBc
mdefine_line|#define awc_RID_Stats_clear_TxBc &t;&t;awc_def_Stats_clear_RID(0x0028,0x0050,&quot;Stats_TxBc&quot;,&t;&t;&quot; LMAC count of broadcast packets sent (uses 802.11&quot;)
DECL|macro|awc_RID_Stats_clear_TxUcFrags
mdefine_line|#define awc_RID_Stats_clear_TxUcFrags &t;&t;awc_def_Stats_clear_RID(0x002A,0x0054,&quot;Stats_TxUcFragsLMAC&quot;,&t;&quot; count of ALL unicast fragments and whole packets sent (uses 802.11 Address1).&quot;)
DECL|macro|awc_RID_Stats_clear_TxUcPackets
mdefine_line|#define awc_RID_Stats_clear_TxUcPackets &t;awc_def_Stats_clear_RID(0x002C,0x0058,&quot;Stats_TxUcPackets&quot;,&t;&quot;LMAC count of unicast packets that were ACKd (uses   802.11 Address 1).&quot;)
DECL|macro|awc_RID_Stats_clear_TxBeacon
mdefine_line|#define awc_RID_Stats_clear_TxBeacon &t;&t;awc_def_Stats_clear_RID(0x002E,0x005C,&quot;Stats_TxBeacon&quot;,&t;&quot; Count of beacon packets transmitted.&quot;)
DECL|macro|awc_RID_Stats_clear_RxBeacon
mdefine_line|#define awc_RID_Stats_clear_RxBeacon &t;&t;awc_def_Stats_clear_RID(0x0030,0x0060,&quot;Stats_RxBeacon&quot;,&t;&quot; Count of beacon packets received matching our BSSID.&quot;)
DECL|macro|awc_RID_Stats_clear_TxSinColl
mdefine_line|#define awc_RID_Stats_clear_TxSinColl &t;&t;awc_def_Stats_clear_RID(0x0032,0x0064,&quot;Stats_TxSinCollTransmit&quot;,&quot; single collisions. **&quot;)
DECL|macro|awc_RID_Stats_clear_TxMulColl
mdefine_line|#define awc_RID_Stats_clear_TxMulColl &t;&t;awc_def_Stats_clear_RID(0x0034,0x0068,&quot;Stats_TxMulCollTransmit&quot;,&quot; multiple collisions. **&quot;)
DECL|macro|awc_RID_Stats_clear_DefersNo
mdefine_line|#define awc_RID_Stats_clear_DefersNo &t;&t;awc_def_Stats_clear_RID(0x0036,0x006C,&quot;Stats_DefersNo Transmit&quot;,&quot; frames sent with no deferral. **&quot;)
DECL|macro|awc_RID_Stats_clear_DefersProt
mdefine_line|#define awc_RID_Stats_clear_DefersProt &t;&t;awc_def_Stats_clear_RID(0x0038,0x0070,&quot;Stats_DefersProt&quot;,&t;&quot; Transmit frames deferred due to protocol.&quot;)
DECL|macro|awc_RID_Stats_clear_DefersEngy
mdefine_line|#define awc_RID_Stats_clear_DefersEngy &t;&t;awc_def_Stats_clear_RID(0x003A,0x0074,&quot;Stats_DefersEngy&quot;,&t;&quot; Transmit frames deferred due to energy detect.&quot;)
DECL|macro|awc_RID_Stats_clear_DupFram
mdefine_line|#define awc_RID_Stats_clear_DupFram &t;&t;awc_def_Stats_clear_RID(0x003C,0x0078,&quot;Stats_DupFram&quot;,&t;&quot;  Duplicate receive frames and fragments.&quot;)
DECL|macro|awc_RID_Stats_clear_RxFragDisc
mdefine_line|#define awc_RID_Stats_clear_RxFragDisc &t;&t;awc_def_Stats_clear_RID(0x003E,0x007C,&quot;Stats_RxFragDisc&quot;,&t;&quot; Received partial frames. (each tally could indicate the  discarding of one or more fragments)&quot;)
DECL|macro|awc_RID_Stats_clear_TxAged
mdefine_line|#define awc_RID_Stats_clear_TxAged &t;&t;awc_def_Stats_clear_RID(0x0040,0x0080,&quot;Stats_TxAged&quot;,&t;&t;&quot;   Transmit packets exceeding maximum transmit lifetime. **&quot;)
DECL|macro|awc_RID_Stats_clear_RxAged
mdefine_line|#define awc_RID_Stats_clear_RxAged &t;&t;awc_def_Stats_clear_RID(0x0042,0x0084,&quot;Stats_RxAgedReceive&quot;,&t;&quot; packets exceeding maximum receive lifetime. **&quot;)
DECL|macro|awc_RID_Stats_clear_LostSync_Max
mdefine_line|#define awc_RID_Stats_clear_LostSync_Max &t;awc_def_Stats_clear_RID(0x0044,0x0088,&quot;Stats_LostSync_Max&quot;,&t;&quot; Lost sync with our cell due to maximum retries occuring. Retry&quot;)
DECL|macro|awc_RID_Stats_clear_LostSync_Mis
mdefine_line|#define awc_RID_Stats_clear_LostSync_Mis &t;awc_def_Stats_clear_RID(0x0046,0x008C,&quot;Stats_LostSync_Mis&quot;,&t;&quot;Lost sync with our cell due to missing too many beacons. sedBeacons&quot;)
DECL|macro|awc_RID_Stats_clear_LostSync_Arl
mdefine_line|#define awc_RID_Stats_clear_LostSync_Arl &t;awc_def_Stats_clear_RID(0x0048,0x0090,&quot;Stats_LostSync_Arl&quot;,&t;&quot;Lost sync with our cell due to Average Retry Level being  Exceeded  exceeded.&quot;)
DECL|macro|awc_RID_Stats_clear_LostSync_Dea
mdefine_line|#define awc_RID_Stats_clear_LostSync_Dea &t;awc_def_Stats_clear_RID(0x004A,0x0094,&quot;Stats_LostSync_Dea&quot;,&t;&quot;Lost sync with our cell due to being deauthenticated.,thed&quot;)
DECL|macro|awc_RID_Stats_clear_LostSync_Disa
mdefine_line|#define awc_RID_Stats_clear_LostSync_Disa &t;awc_def_Stats_clear_RID(0x004C,0x0098,&quot;Stats_LostSync_Disa&quot;,&t;&quot; Lost sync with our cell due to being disassociated. ssoced&quot;)
DECL|macro|awc_RID_Stats_clear_LostSync_Tsf
mdefine_line|#define awc_RID_Stats_clear_LostSync_Tsf &t;awc_def_Stats_clear_RID(0x004E,0x009C,&quot;Stats_LostSync_Tsf&quot;,&t;&quot;Lost sync with our cell due to excessive change in TSF  Timingtiming.&quot;)
DECL|macro|awc_RID_Stats_clear_HostTxMc
mdefine_line|#define awc_RID_Stats_clear_HostTxMc &t;&t;awc_def_Stats_clear_RID(0x0050,0x00A0,&quot;Stats_HostTxMc&quot;,&t;&quot;Count of multicast packets sent by the host.&quot;)
DECL|macro|awc_RID_Stats_clear_HostTxBc
mdefine_line|#define awc_RID_Stats_clear_HostTxBc &t;&t;awc_def_Stats_clear_RID(0x0052,0x00A4,&quot;Stats_HostTxBc&quot;,&t;&quot;Count of broadcast packets sent by the host.&quot;)
DECL|macro|awc_RID_Stats_clear_HostTxUc
mdefine_line|#define awc_RID_Stats_clear_HostTxUc &t;&t;awc_def_Stats_clear_RID(0x0054,0x00A8,&quot;Stats_HostTxUc&quot;,&t;&quot;Count of unicast packets sent by the host.&quot;)
DECL|macro|awc_RID_Stats_clear_HostTxFail
mdefine_line|#define awc_RID_Stats_clear_HostTxFail &t;&t;awc_def_Stats_clear_RID(0x0056,0x00AC,&quot;Stats_HostTxFail&quot;,&t;&quot;  Count of host transmitted packets which failed.&quot;)
DECL|macro|awc_RID_Stats_clear_HostRxMc
mdefine_line|#define awc_RID_Stats_clear_HostRxMc &t;&t;awc_def_Stats_clear_RID(0x0058,0x00B0,&quot;Stats_HostRxMc&quot;,&t;&quot;Count of host received multicast packets.&quot;)
DECL|macro|awc_RID_Stats_clear_HostRxBc
mdefine_line|#define awc_RID_Stats_clear_HostRxBc &t;&t;awc_def_Stats_clear_RID(0x005A,0x00B4,&quot;Stats_HostRxBc&quot;,&t;&quot;Count of host received broadcast packets.&quot;)
DECL|macro|awc_RID_Stats_clear_HostRxUc
mdefine_line|#define awc_RID_Stats_clear_HostRxUc &t;&t;awc_def_Stats_clear_RID(0x005C,0x00B8,&quot;Stats_HostRxUc&quot;,&t;&quot;Count of host received unicast packets.&quot;)
DECL|macro|awc_RID_Stats_clear_HostRxDiscar
mdefine_line|#define awc_RID_Stats_clear_HostRxDiscar &t;awc_def_Stats_clear_RID(0x005E,0x00BC,&quot;Stats_HostRxDiscar&quot;,&t;&quot;Count of host received packets discarded due to:&bslash;n  Host not enabling receive.&bslash;n  Host failing to dequeue receive packets quickly.&bslash;n Packets being discarded due to magic packet mode.&quot;)
DECL|macro|awc_RID_Stats_clear_HmacTxMc
mdefine_line|#define awc_RID_Stats_clear_HmacTxMc &t;&t;awc_def_Stats_clear_RID(0x0060,0x00C0,&quot;Stats_HmacTxMc&quot;,&t;&quot;Count of internally generated multicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats_clear_HmacTxBc
mdefine_line|#define awc_RID_Stats_clear_HmacTxBc &t;&t;awc_def_Stats_clear_RID(0x0062,0x00C4,&quot;Stats_HmacTxBc&quot;,&t;&quot;Count of internally generated broadcast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats_clear_HmacTxUc
mdefine_line|#define awc_RID_Stats_clear_HmacTxUc &t;&t;awc_def_Stats_clear_RID(0x0064,0x00C8,&quot;Stats_HmacTxUc&quot;,&t;&quot;Count of internally generated unicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats_clear_HmacTxFail
mdefine_line|#define awc_RID_Stats_clear_HmacTxFail &t;&t;awc_def_Stats_clear_RID(0x0066,0x00CC,&quot;Stats_HmacTxFail&quot;,&t;&quot;  Count of internally generated transmit packets that failed.&quot;)
DECL|macro|awc_RID_Stats_clear_HmacRxMc
mdefine_line|#define awc_RID_Stats_clear_HmacRxMc &t;&t;awc_def_Stats_clear_RID(0x0068,0x00D0,&quot;Stats_HmacRxMc&quot;,&t;&quot;Count of internally received multicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats_clear_HmacRxBc
mdefine_line|#define awc_RID_Stats_clear_HmacRxBc &t;&t;awc_def_Stats_clear_RID(0x006A,0x00D4,&quot;Stats_HmacRxBc&quot;,&t;&quot;Count of internally received broadcast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats_clear_HmacRxUc
mdefine_line|#define awc_RID_Stats_clear_HmacRxUc &t;&t;awc_def_Stats_clear_RID(0x006C,0x00D8,&quot;Stats_HmacRxUc&quot;,&t;&quot;Count of internally received multicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats_clear_HmacRxDisca
mdefine_line|#define awc_RID_Stats_clear_HmacRxDisca &t;awc_def_Stats_clear_RID(0x006E,0x00DC,&quot;Stats_HmacRxDisca&quot;,&t;&quot; Count of internally received packets that were discarded  (usually because the destination address is not for the host).&quot;)
DECL|macro|awc_RID_Stats_clear_HmacRxAcce
mdefine_line|#define awc_RID_Stats_clear_HmacRxAcce &t;&t;awc_def_Stats_clear_RID(0x0070,0x00E0,&quot;Stats_HmacRxAcce&quot;,&t;&quot;  Count of internally received packets that were accepted&quot;)
DECL|macro|awc_RID_Stats_clear_SsidMismatch
mdefine_line|#define awc_RID_Stats_clear_SsidMismatch &t;awc_def_Stats_clear_RID(0x0072,0x00E4,&quot;Stats_SsidMismatch&quot;,&t;&quot; Count of SSID mismatches.&quot;)
DECL|macro|awc_RID_Stats_clear_ApMismatch
mdefine_line|#define awc_RID_Stats_clear_ApMismatch &t;&t;awc_def_Stats_clear_RID(0x0074,0x00E8,&quot;Stats_ApMismatch&quot;,&t;&quot;  Count of specified AP mismatches.&quot;)
DECL|macro|awc_RID_Stats_clear_RatesMismatc
mdefine_line|#define awc_RID_Stats_clear_RatesMismatc &t;awc_def_Stats_clear_RID(0x0076,0x00EC,&quot;Stats_RatesMismatc&quot;,&t;&quot; Count of rate mismatches.&quot;)
DECL|macro|awc_RID_Stats_clear_AuthReject
mdefine_line|#define awc_RID_Stats_clear_AuthReject &t;&t;awc_def_Stats_clear_RID(0x0078,0x00F0,&quot;Stats_AuthReject&quot;,&t;&quot;  Count of authentication rejections.&quot;)
DECL|macro|awc_RID_Stats_clear_AuthTimeout
mdefine_line|#define awc_RID_Stats_clear_AuthTimeout &t;awc_def_Stats_clear_RID(0x007A,0x00F4,&quot;Stats_AuthTimeout&quot;,&t;&quot; Count of authentication timeouts.&quot;)
DECL|macro|awc_RID_Stats_clear_AssocReject
mdefine_line|#define awc_RID_Stats_clear_AssocReject &t;awc_def_Stats_clear_RID(0x007C,0x00F8,&quot;Stats_AssocReject&quot;,&t;&quot; Count of association rejections.&quot;)
DECL|macro|awc_RID_Stats_clear_AssocTimeout
mdefine_line|#define awc_RID_Stats_clear_AssocTimeout &t;awc_def_Stats_clear_RID(0x007E,0x00FC,&quot;Stats_AssocTimeout&quot;,&t;&quot; Count of association timeouts.&quot;)
DECL|macro|awc_RID_Stats_clear_NewReason
mdefine_line|#define awc_RID_Stats_clear_NewReason &t;&t;awc_def_Stats_clear_RID(0x0080,0x0100,&quot;Stats_NewReason&quot;,&t;&quot;Count of reason/status codes of greater than 19.  (Values of 0 = successful are not counted)&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_1
mdefine_line|#define awc_RID_Stats_clear_AuthFail_1 &t;&t;awc_def_Stats_clear_RID(0x0082,0x0104,&quot;Stats_AuthFail_1&quot;,&t;&quot;Unspecified reason.&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_2
mdefine_line|#define awc_RID_Stats_clear_AuthFail_2 &t;&t;awc_def_Stats_clear_RID(0x0084,0x0108,&quot;Stats_AuthFail_2&quot;,&t;&quot;Previous authentication no longer valid.&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_3
mdefine_line|#define awc_RID_Stats_clear_AuthFail_3 &t;&t;awc_def_Stats_clear_RID(0x0086,0x010C,&quot;Stats_AuthFail_3&quot;,&t;&quot;Deauthenticated because sending station is leaving (has left) IBSS or ESS.&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_4
mdefine_line|#define awc_RID_Stats_clear_AuthFail_4 &t;&t;awc_def_Stats_clear_RID(0x0088,0x0110,&quot;Stats_AuthFail_4&quot;,&t;&quot;Disassociated due to inactivity&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_5
mdefine_line|#define awc_RID_Stats_clear_AuthFail_5 &t;&t;awc_def_Stats_clear_RID(0x008A,0x0114,&quot;Stats_AuthFail_5&quot;,&t;&quot;Disassociated because AP is unable to handle all currently  associated stations.&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_6
mdefine_line|#define awc_RID_Stats_clear_AuthFail_6 &t;&t;awc_def_Stats_clear_RID(0x008C,0x0118,&quot;Stats_AuthFail_6&quot;,&t;&quot;Class 2 Frame received from non-Authenticated station.&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_7
mdefine_line|#define awc_RID_Stats_clear_AuthFail_7 &t;&t;awc_def_Stats_clear_RID(0x008E,0x011C,&quot;Stats_AuthFail_7&quot;,&t;&quot;Class 3 Frame received from non-Associated station.&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_8
mdefine_line|#define awc_RID_Stats_clear_AuthFail_8 &t;&t;awc_def_Stats_clear_RID(0x0090,0x0120,&quot;Stats_AuthFail_8&quot;,&t;&quot;Disassociated because sending station is leaving (has left)&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_9
mdefine_line|#define awc_RID_Stats_clear_AuthFail_9 &t;&t;awc_def_Stats_clear_RID(0x0092,0x0124,&quot;Stats_AuthFail_9&quot;,&t;&quot;Station requesting (Re)Association is not Authenticated&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_10
mdefine_line|#define awc_RID_Stats_clear_AuthFail_10 &t;awc_def_Stats_clear_RID(0x0094,0x0128,&quot;Stats_AuthFail_10&quot;,&t;&quot;Cannot support all requested capabilities in the Capability&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_11
mdefine_line|#define awc_RID_Stats_clear_AuthFail_11 &t;awc_def_Stats_clear_RID(0x0096,0x012C,&quot;Stats_AuthFail_11&quot;,&t;&quot;Reassociation denied due to inability to confirm&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_12
mdefine_line|#define awc_RID_Stats_clear_AuthFail_12 &t;awc_def_Stats_clear_RID(0x0098,0x0130,&quot;Stats_AuthFail_12&quot;,&t;&quot;Association denied due to reason outside the scope of the 802.11&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_13
mdefine_line|#define awc_RID_Stats_clear_AuthFail_13 &t;awc_def_Stats_clear_RID(0x009A,0x0134,&quot;Stats_AuthFail_13&quot;,&t;&quot;Responding station does not support the specified Auth Alogorithm&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_14
mdefine_line|#define awc_RID_Stats_clear_AuthFail_14 &t;awc_def_Stats_clear_RID(0x009C,0x0138,&quot;Stats_AuthFail_14&quot;,&t;&quot;Received an out of sequence Authentication Frame.&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_15
mdefine_line|#define awc_RID_Stats_clear_AuthFail_15 &t;awc_def_Stats_clear_RID(0x009E,0x013C,&quot;Stats_AuthFail_15&quot;,&t;&quot;Authentication rejected due to challenge failure.&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_16
mdefine_line|#define awc_RID_Stats_clear_AuthFail_16 &t;awc_def_Stats_clear_RID(0x00A0,0x0140,&quot;Stats_AuthFail_16&quot;,&t;&quot;Authentication rejected due to timeout waiting for next  frame in sequence.&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_17
mdefine_line|#define awc_RID_Stats_clear_AuthFail_17 &t;awc_def_Stats_clear_RID(0x00A2,0x0144,&quot;Stats_AuthFail_17&quot;,&t;&quot;Association denied because AP is unable to handle  additional associated stations.&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_18
mdefine_line|#define awc_RID_Stats_clear_AuthFail_18 &t;awc_def_Stats_clear_RID(0x00A4,0x0148,&quot;Stats_AuthFail_18&quot;,&t;&quot;Association denied due to requesting station not supportingall basic rates.&quot;)
DECL|macro|awc_RID_Stats_clear_AuthFail_19
mdefine_line|#define awc_RID_Stats_clear_AuthFail_19 &t;awc_def_Stats_clear_RID(0x00A6,0x014C,&quot;Stats_AuthFail_19&quot;,&t;&quot;Reserved&quot;)
DECL|macro|awc_RID_Stats_clear_RxMan
mdefine_line|#define awc_RID_Stats_clear_RxMan &t;&t;awc_def_Stats_clear_RID(0x00A8,0x0150,&quot;Stats_RxMan&quot;,&t;&t;&quot; Count of management packets received and handled.&quot;)
DECL|macro|awc_RID_Stats_clear_TxMan
mdefine_line|#define awc_RID_Stats_clear_TxMan &t;&t;awc_def_Stats_clear_RID(0x00AA,0x0154,&quot;Stats_TxMan&quot;,&t;&t;&quot; Count of management packets transmitted.&quot;)
DECL|macro|awc_RID_Stats_clear_RxRefresh
mdefine_line|#define awc_RID_Stats_clear_RxRefresh &t;&t;awc_def_Stats_clear_RID(0x00AC,0x0158,&quot;Stats_RxRefresh&quot;,&t;&quot; Count of null data packets received.&quot;)
DECL|macro|awc_RID_Stats_clear_TxRefresh
mdefine_line|#define awc_RID_Stats_clear_TxRefresh &t;&t;awc_def_Stats_clear_RID(0x00AE,0x015C,&quot;Stats_TxRefresh&quot;,&t;&quot; Count of null data packets transmitted.&quot;)
DECL|macro|awc_RID_Stats_clear_RxPoll
mdefine_line|#define awc_RID_Stats_clear_RxPoll &t;&t;awc_def_Stats_clear_RID(0x00B0,0x0160,&quot;Stats_RxPoll&quot;,&t;&t;&quot;Count of PS-Poll packets received.&quot;)
DECL|macro|awc_RID_Stats_clear_TxPoll
mdefine_line|#define awc_RID_Stats_clear_TxPoll &t;&t;awc_def_Stats_clear_RID(0x00B2,0x0164,&quot;Stats_TxPoll&quot;,&t;&t;&quot;Count of PS-Poll packets transmitted.&quot;)
DECL|macro|awc_RID_Stats_clear_HostRetries
mdefine_line|#define awc_RID_Stats_clear_HostRetries &t;awc_def_Stats_clear_RID(0x00B4,0x0168,&quot;Stats_HostRetries&quot;,&t;&quot; Count of long and short retries used to transmit host packets  (does not include first attempt).&quot;)
DECL|macro|awc_RID_Stats_clear_LostSync_HostReq
mdefine_line|#define awc_RID_Stats_clear_LostSync_HostReq &t;awc_def_Stats_clear_RID(0x00B6,0x016C,&quot;Stats_LostSync_HostReq&quot;,&quot;Lost sync with our cell due to host request.&quot;)
DECL|macro|awc_RID_Stats_clear_HostTxBytes
mdefine_line|#define awc_RID_Stats_clear_HostTxBytes &t;awc_def_Stats_clear_RID(0x00B8,0x0170,&quot;Stats_HostTxBytes&quot;,&t;&quot; Count of bytes transferred from the host.&quot;)
DECL|macro|awc_RID_Stats_clear_HostRxBytes
mdefine_line|#define awc_RID_Stats_clear_HostRxBytes &t;awc_def_Stats_clear_RID(0x00BA,0x0174,&quot;Stats_HostRxBytes&quot;,&t;&quot; Count of bytes transferred to the host.&quot;)
DECL|macro|awc_RID_Stats_clear_ElapsedUsec
mdefine_line|#define awc_RID_Stats_clear_ElapsedUsec &t;awc_def_Stats_clear_RID(0x00BC,0x0178,&quot;Stats_ElapsedUsec&quot;,&t;&quot; Total time since power up (or clear) in microseconds.&quot;)
DECL|macro|awc_RID_Stats_clear_ElapsedSec
mdefine_line|#define awc_RID_Stats_clear_ElapsedSec &t;&t;awc_def_Stats_clear_RID(0x00BE,0x017C,&quot;Stats_ElapsedSec&quot;,&t;&quot; Total time since power up (or clear) in seconds.&quot;)
DECL|macro|awc_RID_Stats_clear_LostSyncBett
mdefine_line|#define awc_RID_Stats_clear_LostSyncBett &t;awc_def_Stats_clear_RID(0x00C0,0x0180,&quot;Stats_LostSyncBett&quot;,&t;&quot;Lost Sync to switch to a better access point&quot;)
DECL|macro|awc_RID_Stats16_RidLen
mdefine_line|#define awc_RID_Stats16_RidLen &t;&t;awc_def_Stats16_RID(0x0000,0x0000,&quot;RidLen&quot;,&t;&t;&quot;Length of the RID including the length field.&quot;)
DECL|macro|awc_RID_Stats16_RxOverrunErr
mdefine_line|#define awc_RID_Stats16_RxOverrunErr &t;awc_def_Stats16_RID(0x0002,0x0004,&quot;Stats_RxOverrunErr&quot;,&t;&quot;Receive overruns -- No buffer available to handle the receive. (result is that the packet is never received)&quot;)
DECL|macro|awc_RID_Stats16_RxPlcpCrcErr
mdefine_line|#define awc_RID_Stats16_RxPlcpCrcErr &t;awc_def_Stats16_RID(0x0004,0x0008,&quot;Stats_RxPlcpCrcErr&quot;,&t;&quot;PLCP header checksum errors (CRC16).&quot;)
DECL|macro|awc_RID_Stats16_RxPlcpFormat
mdefine_line|#define awc_RID_Stats16_RxPlcpFormat &t;awc_def_Stats16_RID(0x0006,0x000C,&quot;Stats_RxPlcpFormat&quot;,&t;&quot;PLCP format errors.&quot;)
DECL|macro|awc_RID_Stats16_RxPlcpLength
mdefine_line|#define awc_RID_Stats16_RxPlcpLength &t;awc_def_Stats16_RID(0x0008,0x0010,&quot;Stats_RxPlcpLength&quot;,&t;&quot;PLCP length is incorrect.&quot;)
DECL|macro|awc_RID_Stats16_RxMacCrcErr
mdefine_line|#define awc_RID_Stats16_RxMacCrcErr &t;awc_def_Stats16_RID(0x000A,0x0014,&quot;Stats_RxMacCrcErr&quot;,&t;&quot;Count of MAC CRC32 errors.&quot;)
DECL|macro|awc_RID_Stats16_RxMacCrcOk
mdefine_line|#define awc_RID_Stats16_RxMacCrcOk &t;awc_def_Stats16_RID(0x000C,0x0018,&quot;Stats_RxMacCrcOk&quot;,&t;&quot;Count of MAC CRC32 received correctly.&quot;)
DECL|macro|awc_RID_Stats16_RxWepErr
mdefine_line|#define awc_RID_Stats16_RxWepErr &t;awc_def_Stats16_RID(0x000E,0x001C,&quot;Stats_RxWepErr&quot;,&t;&quot;Count of all WEP ICV checks that failed. (this value is included in Stats_RxMacCrcOk)&quot;)
DECL|macro|awc_RID_Stats16_RxWepOk
mdefine_line|#define awc_RID_Stats16_RxWepOk &t;awc_def_Stats16_RID(0x0010,0x0020,&quot;Stats_RxWepOk&quot;,&t;&quot;Count of all WEP ICV checks that passed. (this value is  included in Stats_RxMacCrcOk)&quot;)
DECL|macro|awc_RID_Stats16_RetryLong
mdefine_line|#define awc_RID_Stats16_RetryLong &t;awc_def_Stats16_RID(0x0012,0x0024,&quot;Stats_RetryLongCount&quot;,&t;&quot;of all long retries. (Does not include first attempt for a packet).&quot;)
DECL|macro|awc_RID_Stats16_RetryShort
mdefine_line|#define awc_RID_Stats16_RetryShort &t;awc_def_Stats16_RID(0x0014,0x0028,&quot;Stats_RetryShort&quot;,&t;&quot;Count of all short retries. (Does not include first attempt for   a packet).&quot;)
DECL|macro|awc_RID_Stats16_MaxRetries
mdefine_line|#define awc_RID_Stats16_MaxRetries &t;awc_def_Stats16_RID(0x0016,0x002C,&quot;Stats_MaxRetries&quot;,&t;&quot;Count of number of packets that max-retried -- ie were  never ACKd.&quot;)
DECL|macro|awc_RID_Stats16_NoAck
mdefine_line|#define awc_RID_Stats16_NoAck &t;&t;awc_def_Stats16_RID(0x0018,0x0030,&quot;Stats_NoAck&quot;,&t;&t;&quot;Count of number of times that ACK was not received.&quot;)
DECL|macro|awc_RID_Stats16_NoCts
mdefine_line|#define awc_RID_Stats16_NoCts &t;&t;awc_def_Stats16_RID(0x001A,0x0034,&quot;Stats_NoCts&quot;,&t;&t;&quot;Count of number of timer that CTS was not received.&quot;)
DECL|macro|awc_RID_Stats16_RxAck
mdefine_line|#define awc_RID_Stats16_RxAck &t;&t;awc_def_Stats16_RID(0x001C,0x0038,&quot;Stats_RxAck&quot;,&t;&t;&quot;Count of number of expected ACKs that were received.&quot;)
DECL|macro|awc_RID_Stats16_RxCts
mdefine_line|#define awc_RID_Stats16_RxCts &t;&t;awc_def_Stats16_RID(0x001E,0x003C,&quot;Stats_RxCts&quot;,&t;&t;&quot;Count of number of expected CTSs that were received.&quot;)
DECL|macro|awc_RID_Stats16_TxAck
mdefine_line|#define awc_RID_Stats16_TxAck &t;&t;awc_def_Stats16_RID(0x0020,0x0040,&quot;Stats_TxAck&quot;,&t;&t;&quot;Count of number of ACKs transmitted.&quot;)
DECL|macro|awc_RID_Stats16_TxRts
mdefine_line|#define awc_RID_Stats16_TxRts &t;&t;awc_def_Stats16_RID(0x0022,0x0044,&quot;Stats_TxRts&quot;,&t;&t;&quot;Count of number of RTSs transmitted.&quot;)
DECL|macro|awc_RID_Stats16_TxCts
mdefine_line|#define awc_RID_Stats16_TxCts &t;&t;awc_def_Stats16_RID(0x0024,0x0048,&quot;Stats_TxCts&quot;,&t;&t;&quot;Count of number of CTSs transmitted.&quot;)
DECL|macro|awc_RID_Stats16_TxMc
mdefine_line|#define awc_RID_Stats16_TxMc &t;&t;awc_def_Stats16_RID(0x0026,0x004C,&quot;Stats_TxMc&quot;,&t;&t;&quot; LMAC count of multicast packets sent (uses 802.11  Address1).&quot;)
DECL|macro|awc_RID_Stats16_TxBc
mdefine_line|#define awc_RID_Stats16_TxBc &t;&t;awc_def_Stats16_RID(0x0028,0x0050,&quot;Stats_TxBc&quot;,&t;&t;&quot; LMAC count of broadcast packets sent (uses 802.11&quot;)
DECL|macro|awc_RID_Stats16_TxUcFrags
mdefine_line|#define awc_RID_Stats16_TxUcFrags &t;awc_def_Stats16_RID(0x002A,0x0054,&quot;Stats_TxUcFragsLMAC&quot;,&t;&quot; count of ALL unicast fragments and whole packets sent (uses 802.11 Address1).&quot;)
DECL|macro|awc_RID_Stats16_TxUcPackets
mdefine_line|#define awc_RID_Stats16_TxUcPackets &t;awc_def_Stats16_RID(0x002C,0x0058,&quot;Stats_TxUcPackets&quot;,&t;&quot;LMAC count of unicast packets that were ACKd (uses   802.11 Address 1).&quot;)
DECL|macro|awc_RID_Stats16_TxBeacon
mdefine_line|#define awc_RID_Stats16_TxBeacon &t;awc_def_Stats16_RID(0x002E,0x005C,&quot;Stats_TxBeacon&quot;,&t;&quot; Count of beacon packets transmitted.&quot;)
DECL|macro|awc_RID_Stats16_RxBeacon
mdefine_line|#define awc_RID_Stats16_RxBeacon &t;awc_def_Stats16_RID(0x0030,0x0060,&quot;Stats_RxBeacon&quot;,&t;&quot; Count of beacon packets received matching our BSSID.&quot;)
DECL|macro|awc_RID_Stats16_TxSinColl
mdefine_line|#define awc_RID_Stats16_TxSinColl &t;awc_def_Stats16_RID(0x0032,0x0064,&quot;Stats_TxSinCollTransmit&quot;,&quot; single collisions. **&quot;)
DECL|macro|awc_RID_Stats16_TxMulColl
mdefine_line|#define awc_RID_Stats16_TxMulColl &t;awc_def_Stats16_RID(0x0034,0x0068,&quot;Stats_TxMulCollTransmit&quot;,&quot; multiple collisions. **&quot;)
DECL|macro|awc_RID_Stats16_DefersNo
mdefine_line|#define awc_RID_Stats16_DefersNo &t;awc_def_Stats16_RID(0x0036,0x006C,&quot;Stats_DefersNo Transmit&quot;,&quot; frames sent with no deferral. **&quot;)
DECL|macro|awc_RID_Stats16_DefersProt
mdefine_line|#define awc_RID_Stats16_DefersProt &t;awc_def_Stats16_RID(0x0038,0x0070,&quot;Stats_DefersProt&quot;,&t;&quot; Transmit frames deferred due to protocol.&quot;)
DECL|macro|awc_RID_Stats16_DefersEngy
mdefine_line|#define awc_RID_Stats16_DefersEngy &t;awc_def_Stats16_RID(0x003A,0x0074,&quot;Stats_DefersEngy&quot;,&t;&quot; Transmit frames deferred due to energy detect.&quot;)
DECL|macro|awc_RID_Stats16_DupFram
mdefine_line|#define awc_RID_Stats16_DupFram &t;awc_def_Stats16_RID(0x003C,0x0078,&quot;Stats_DupFram&quot;,&t;&quot;  Duplicate receive frames and fragments.&quot;)
DECL|macro|awc_RID_Stats16_RxFragDisc
mdefine_line|#define awc_RID_Stats16_RxFragDisc &t;awc_def_Stats16_RID(0x003E,0x007C,&quot;Stats_RxFragDisc&quot;,&t;&quot; Received partial frames. (each tally could indicate the  discarding of one or more fragments)&quot;)
DECL|macro|awc_RID_Stats16_TxAged
mdefine_line|#define awc_RID_Stats16_TxAged &t;&t;awc_def_Stats16_RID(0x0040,0x0080,&quot;Stats_TxAged&quot;,&t;&t;&quot;   Transmit packets exceeding maximum transmit lifetime. **&quot;)
DECL|macro|awc_RID_Stats16_RxAged
mdefine_line|#define awc_RID_Stats16_RxAged &t;&t;awc_def_Stats16_RID(0x0042,0x0084,&quot;Stats_RxAgedReceive&quot;,&t;&quot; packets exceeding maximum receive lifetime. **&quot;)
DECL|macro|awc_RID_Stats16_LostSync_Max
mdefine_line|#define awc_RID_Stats16_LostSync_Max &t;awc_def_Stats16_RID(0x0044,0x0088,&quot;Stats_LostSync_Max&quot;,&t;&quot; Lost sync with our cell due to maximum retries occuring. Retry&quot;)
DECL|macro|awc_RID_Stats16_LostSync_Mis
mdefine_line|#define awc_RID_Stats16_LostSync_Mis &t;awc_def_Stats16_RID(0x0046,0x008C,&quot;Stats_LostSync_Mis&quot;,&t;&quot;Lost sync with our cell due to missing too many beacons. sedBeacons&quot;)
DECL|macro|awc_RID_Stats16_LostSync_Arl
mdefine_line|#define awc_RID_Stats16_LostSync_Arl &t;awc_def_Stats16_RID(0x0048,0x0090,&quot;Stats_LostSync_Arl&quot;,&t;&quot;Lost sync with our cell due to Average Retry Level being  Exceeded  exceeded.&quot;)
DECL|macro|awc_RID_Stats16_LostSync_Dea
mdefine_line|#define awc_RID_Stats16_LostSync_Dea &t;awc_def_Stats16_RID(0x004A,0x0094,&quot;Stats_LostSync_Dea&quot;,&t;&quot;Lost sync with our cell due to being deauthenticated.,thed&quot;)
DECL|macro|awc_RID_Stats16_LostSync_Disa
mdefine_line|#define awc_RID_Stats16_LostSync_Disa &t;awc_def_Stats16_RID(0x004C,0x0098,&quot;Stats_LostSync_Disa&quot;,&t;&quot; Lost sync with our cell due to being disassociated. ssoced&quot;)
DECL|macro|awc_RID_Stats16_LostSync_Tsf
mdefine_line|#define awc_RID_Stats16_LostSync_Tsf &t;awc_def_Stats16_RID(0x004E,0x009C,&quot;Stats_LostSync_Tsf&quot;,&t;&quot;Lost sync with our cell due to excessive change in TSF  Timingtiming.&quot;)
DECL|macro|awc_RID_Stats16_HostTxMc
mdefine_line|#define awc_RID_Stats16_HostTxMc &t;awc_def_Stats16_RID(0x0050,0x00A0,&quot;Stats_HostTxMc&quot;,&t;&quot;Count of multicast packets sent by the host.&quot;)
DECL|macro|awc_RID_Stats16_HostTxBc
mdefine_line|#define awc_RID_Stats16_HostTxBc &t;awc_def_Stats16_RID(0x0052,0x00A4,&quot;Stats_HostTxBc&quot;,&t;&quot;Count of broadcast packets sent by the host.&quot;)
DECL|macro|awc_RID_Stats16_HostTxUc
mdefine_line|#define awc_RID_Stats16_HostTxUc &t;awc_def_Stats16_RID(0x0054,0x00A8,&quot;Stats_HostTxUc&quot;,&t;&quot;Count of unicast packets sent by the host.&quot;)
DECL|macro|awc_RID_Stats16_HostTxFail
mdefine_line|#define awc_RID_Stats16_HostTxFail &t;awc_def_Stats16_RID(0x0056,0x00AC,&quot;Stats_HostTxFail&quot;,&t;&quot;  Count of host transmitted packets which failed.&quot;)
DECL|macro|awc_RID_Stats16_HostRxMc
mdefine_line|#define awc_RID_Stats16_HostRxMc &t;awc_def_Stats16_RID(0x0058,0x00B0,&quot;Stats_HostRxMc&quot;,&t;&quot;Count of host received multicast packets.&quot;)
DECL|macro|awc_RID_Stats16_HostRxBc
mdefine_line|#define awc_RID_Stats16_HostRxBc &t;awc_def_Stats16_RID(0x005A,0x00B4,&quot;Stats_HostRxBc&quot;,&t;&quot;Count of host received broadcast packets.&quot;)
DECL|macro|awc_RID_Stats16_HostRxUc
mdefine_line|#define awc_RID_Stats16_HostRxUc &t;awc_def_Stats16_RID(0x005C,0x00B8,&quot;Stats_HostRxUc&quot;,&t;&quot;Count of host received unicast packets.&quot;)
DECL|macro|awc_RID_Stats16_HostRxDiscar
mdefine_line|#define awc_RID_Stats16_HostRxDiscar &t;awc_def_Stats16_RID(0x005E,0x00BC,&quot;Stats_HostRxDiscar&quot;,&t;&quot;Count of host received packets discarded due to:&bslash;n  Host not enabling receive.&bslash;n  Host failing to dequeue receive packets quickly.&bslash;n Packets being discarded due to magic packet mode.&quot;)
DECL|macro|awc_RID_Stats16_HmacTxMc
mdefine_line|#define awc_RID_Stats16_HmacTxMc &t;awc_def_Stats16_RID(0x0060,0x00C0,&quot;Stats_HmacTxMc&quot;,&t;&quot;Count of internally generated multicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats16_HmacTxBc
mdefine_line|#define awc_RID_Stats16_HmacTxBc &t;awc_def_Stats16_RID(0x0062,0x00C4,&quot;Stats_HmacTxBc&quot;,&t;&quot;Count of internally generated broadcast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats16_HmacTxUc
mdefine_line|#define awc_RID_Stats16_HmacTxUc &t;awc_def_Stats16_RID(0x0064,0x00C8,&quot;Stats_HmacTxUc&quot;,&t;&quot;Count of internally generated unicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats16_HmacTxFail
mdefine_line|#define awc_RID_Stats16_HmacTxFail &t;awc_def_Stats16_RID(0x0066,0x00CC,&quot;Stats_HmacTxFail&quot;,&t;&quot;  Count of internally generated transmit packets that failed.&quot;)
DECL|macro|awc_RID_Stats16_HmacRxMc
mdefine_line|#define awc_RID_Stats16_HmacRxMc &t;awc_def_Stats16_RID(0x0068,0x00D0,&quot;Stats_HmacRxMc&quot;,&t;&quot;Count of internally received multicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats16_HmacRxBc
mdefine_line|#define awc_RID_Stats16_HmacRxBc &t;awc_def_Stats16_RID(0x006A,0x00D4,&quot;Stats_HmacRxBc&quot;,&t;&quot;Count of internally received broadcast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats16_HmacRxUc
mdefine_line|#define awc_RID_Stats16_HmacRxUc &t;awc_def_Stats16_RID(0x006C,0x00D8,&quot;Stats_HmacRxUc&quot;,&t;&quot;Count of internally received multicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats16_HmacRxDisca
mdefine_line|#define awc_RID_Stats16_HmacRxDisca &t;awc_def_Stats16_RID(0x006E,0x00DC,&quot;Stats_HmacRxDisca&quot;,&t;&quot; Count of internally received packets that were discarded  (usually because the destination address is not for the host).&quot;)
DECL|macro|awc_RID_Stats16_HmacRxAcce
mdefine_line|#define awc_RID_Stats16_HmacRxAcce &t;awc_def_Stats16_RID(0x0070,0x00E0,&quot;Stats_HmacRxAcce&quot;,&t;&quot;  Count of internally received packets that were accepted&quot;)
DECL|macro|awc_RID_Stats16_SsidMismatch
mdefine_line|#define awc_RID_Stats16_SsidMismatch &t;awc_def_Stats16_RID(0x0072,0x00E4,&quot;Stats_SsidMismatch&quot;,&t;&quot; Count of SSID mismatches.&quot;)
DECL|macro|awc_RID_Stats16_ApMismatch
mdefine_line|#define awc_RID_Stats16_ApMismatch &t;awc_def_Stats16_RID(0x0074,0x00E8,&quot;Stats_ApMismatch&quot;,&t;&quot;  Count of specified AP mismatches.&quot;)
DECL|macro|awc_RID_Stats16_RatesMismatc
mdefine_line|#define awc_RID_Stats16_RatesMismatc &t;awc_def_Stats16_RID(0x0076,0x00EC,&quot;Stats_RatesMismatc&quot;,&t;&quot; Count of rate mismatches.&quot;)
DECL|macro|awc_RID_Stats16_AuthReject
mdefine_line|#define awc_RID_Stats16_AuthReject &t;awc_def_Stats16_RID(0x0078,0x00F0,&quot;Stats_AuthReject&quot;,&t;&quot;  Count of authentication rejections.&quot;)
DECL|macro|awc_RID_Stats16_AuthTimeout
mdefine_line|#define awc_RID_Stats16_AuthTimeout &t;awc_def_Stats16_RID(0x007A,0x00F4,&quot;Stats_AuthTimeout&quot;,&t;&quot; Count of authentication timeouts.&quot;)
DECL|macro|awc_RID_Stats16_AssocReject
mdefine_line|#define awc_RID_Stats16_AssocReject &t;awc_def_Stats16_RID(0x007C,0x00F8,&quot;Stats_AssocReject&quot;,&t;&quot; Count of association rejections.&quot;)
DECL|macro|awc_RID_Stats16_AssocTimeout
mdefine_line|#define awc_RID_Stats16_AssocTimeout &t;awc_def_Stats16_RID(0x007E,0x00FC,&quot;Stats_AssocTimeout&quot;,&t;&quot; Count of association timeouts.&quot;)
DECL|macro|awc_RID_Stats16_NewReason
mdefine_line|#define awc_RID_Stats16_NewReason &t;awc_def_Stats16_RID(0x0080,0x0100,&quot;Stats_NewReason&quot;,&t;&quot;Count of reason/status codes of greater than 19.  (Values of 0 = successful are not counted)&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_1
mdefine_line|#define awc_RID_Stats16_AuthFail_1 &t;awc_def_Stats16_RID(0x0082,0x0104,&quot;Stats_AuthFail_1&quot;,&t;&quot;Unspecified reason.&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_2
mdefine_line|#define awc_RID_Stats16_AuthFail_2 &t;awc_def_Stats16_RID(0x0084,0x0108,&quot;Stats_AuthFail_2&quot;,&t;&quot;Previous authentication no longer valid.&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_3
mdefine_line|#define awc_RID_Stats16_AuthFail_3 &t;awc_def_Stats16_RID(0x0086,0x010C,&quot;Stats_AuthFail_3&quot;,&t;&quot;Deauthenticated because sending station is leaving (has left) IBSS or ESS.&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_4
mdefine_line|#define awc_RID_Stats16_AuthFail_4 &t;awc_def_Stats16_RID(0x0088,0x0110,&quot;Stats_AuthFail_4&quot;,&t;&quot;Disassociated due to inactivity&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_5
mdefine_line|#define awc_RID_Stats16_AuthFail_5 &t;awc_def_Stats16_RID(0x008A,0x0114,&quot;Stats_AuthFail_5&quot;,&t;&quot;Disassociated because AP is unable to handle all currently  associated stations.&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_6
mdefine_line|#define awc_RID_Stats16_AuthFail_6 &t;awc_def_Stats16_RID(0x008C,0x0118,&quot;Stats_AuthFail_6&quot;,&t;&quot;Class 2 Frame received from non-Authenticated station.&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_7
mdefine_line|#define awc_RID_Stats16_AuthFail_7 &t;awc_def_Stats16_RID(0x008E,0x011C,&quot;Stats_AuthFail_7&quot;,&t;&quot;Class 3 Frame received from non-Associated station.&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_8
mdefine_line|#define awc_RID_Stats16_AuthFail_8 &t;awc_def_Stats16_RID(0x0090,0x0120,&quot;Stats_AuthFail_8&quot;,&t;&quot;Disassociated because sending station is leaving (has left)&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_9
mdefine_line|#define awc_RID_Stats16_AuthFail_9 &t;awc_def_Stats16_RID(0x0092,0x0124,&quot;Stats_AuthFail_9&quot;,&t;&quot;Station requesting (Re)Association is not Authenticated&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_10
mdefine_line|#define awc_RID_Stats16_AuthFail_10 &t;awc_def_Stats16_RID(0x0094,0x0128,&quot;Stats_AuthFail_10&quot;,&t;&quot;Cannot support all requested capabilities in the Capability&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_11
mdefine_line|#define awc_RID_Stats16_AuthFail_11 &t;awc_def_Stats16_RID(0x0096,0x012C,&quot;Stats_AuthFail_11&quot;,&t;&quot;Reassociation denied due to inability to confirm&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_12
mdefine_line|#define awc_RID_Stats16_AuthFail_12 &t;awc_def_Stats16_RID(0x0098,0x0130,&quot;Stats_AuthFail_12&quot;,&t;&quot;Association denied due to reason outside the scope of the 802.11&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_13
mdefine_line|#define awc_RID_Stats16_AuthFail_13 &t;awc_def_Stats16_RID(0x009A,0x0134,&quot;Stats_AuthFail_13&quot;,&t;&quot;Responding station does not support the specified Auth Alogorithm&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_14
mdefine_line|#define awc_RID_Stats16_AuthFail_14 &t;awc_def_Stats16_RID(0x009C,0x0138,&quot;Stats_AuthFail_14&quot;,&t;&quot;Received an out of sequence Authentication Frame.&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_15
mdefine_line|#define awc_RID_Stats16_AuthFail_15 &t;awc_def_Stats16_RID(0x009E,0x013C,&quot;Stats_AuthFail_15&quot;,&t;&quot;Authentication rejected due to challenge failure.&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_16
mdefine_line|#define awc_RID_Stats16_AuthFail_16 &t;awc_def_Stats16_RID(0x00A0,0x0140,&quot;Stats_AuthFail_16&quot;,&t;&quot;Authentication rejected due to timeout waiting for next  frame in sequence.&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_17
mdefine_line|#define awc_RID_Stats16_AuthFail_17 &t;awc_def_Stats16_RID(0x00A2,0x0144,&quot;Stats_AuthFail_17&quot;,&t;&quot;Association denied because AP is unable to handle  additional associated stations.&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_18
mdefine_line|#define awc_RID_Stats16_AuthFail_18 &t;awc_def_Stats16_RID(0x00A4,0x0148,&quot;Stats_AuthFail_18&quot;,&t;&quot;Association denied due to requesting station not supportingall basic rates.&quot;)
DECL|macro|awc_RID_Stats16_AuthFail_19
mdefine_line|#define awc_RID_Stats16_AuthFail_19 &t;awc_def_Stats16_RID(0x00A6,0x014C,&quot;Stats_AuthFail_19&quot;,&t;&quot;Reserved&quot;)
DECL|macro|awc_RID_Stats16_RxMan
mdefine_line|#define awc_RID_Stats16_RxMan &t;&t;awc_def_Stats16_RID(0x00A8,0x0150,&quot;Stats_RxMan&quot;,&t;&t;&quot; Count of management packets received and handled.&quot;)
DECL|macro|awc_RID_Stats16_TxMan
mdefine_line|#define awc_RID_Stats16_TxMan &t;&t;awc_def_Stats16_RID(0x00AA,0x0154,&quot;Stats_TxMan&quot;,&t;&t;&quot; Count of management packets transmitted.&quot;)
DECL|macro|awc_RID_Stats16_RxRefresh
mdefine_line|#define awc_RID_Stats16_RxRefresh &t;awc_def_Stats16_RID(0x00AC,0x0158,&quot;Stats_RxRefresh&quot;,&t;&quot; Count of null data packets received.&quot;)
DECL|macro|awc_RID_Stats16_TxRefresh
mdefine_line|#define awc_RID_Stats16_TxRefresh &t;awc_def_Stats16_RID(0x00AE,0x015C,&quot;Stats_TxRefresh&quot;,&t;&quot; Count of null data packets transmitted.&quot;)
DECL|macro|awc_RID_Stats16_RxPoll
mdefine_line|#define awc_RID_Stats16_RxPoll &t;&t;awc_def_Stats16_RID(0x00B0,0x0160,&quot;Stats_RxPoll&quot;,&t;&t;&quot;Count of PS-Poll packets received.&quot;)
DECL|macro|awc_RID_Stats16_TxPoll
mdefine_line|#define awc_RID_Stats16_TxPoll &t;&t;awc_def_Stats16_RID(0x00B2,0x0164,&quot;Stats_TxPoll&quot;,&t;&t;&quot;Count of PS-Poll packets transmitted.&quot;)
DECL|macro|awc_RID_Stats16_HostRetries
mdefine_line|#define awc_RID_Stats16_HostRetries &t;awc_def_Stats16_RID(0x00B4,0x0168,&quot;Stats_HostRetries&quot;,&t;&quot; Count of long and short retries used to transmit host packets  (does not include first attempt).&quot;)
DECL|macro|awc_RID_Stats16_LostSync_HostReq
mdefine_line|#define awc_RID_Stats16_LostSync_HostReq awc_def_Stats16_RID(0x00B6,0x016C,&quot;Stats_LostSync_HostReq&quot;,&quot;Lost sync with our cell due to host request.&quot;)
DECL|macro|awc_RID_Stats16_HostTxBytes
mdefine_line|#define awc_RID_Stats16_HostTxBytes &t;awc_def_Stats16_RID(0x00B8,0x0170,&quot;Stats_HostTxBytes&quot;,&t;&quot; Count of bytes transferred from the host.&quot;)
DECL|macro|awc_RID_Stats16_HostRxBytes
mdefine_line|#define awc_RID_Stats16_HostRxBytes &t;awc_def_Stats16_RID(0x00BA,0x0174,&quot;Stats_HostRxBytes&quot;,&t;&quot; Count of bytes transferred to the host.&quot;)
DECL|macro|awc_RID_Stats16_ElapsedUsec
mdefine_line|#define awc_RID_Stats16_ElapsedUsec &t;awc_def_Stats16_RID(0x00BC,0x0178,&quot;Stats_ElapsedUsec&quot;,&t;&quot; Total time since power up (or clear) in microseconds.&quot;)
DECL|macro|awc_RID_Stats16_ElapsedSec
mdefine_line|#define awc_RID_Stats16_ElapsedSec &t;awc_def_Stats16_RID(0x00BE,0x017C,&quot;Stats_ElapsedSec&quot;,&t;&quot; Total time since power up (or clear) in seconds.&quot;)
DECL|macro|awc_RID_Stats16_LostSyncBett
mdefine_line|#define awc_RID_Stats16_LostSyncBett &t;awc_def_Stats16_RID(0x00C0,0x0180,&quot;Stats_LostSyncBett&quot;,&t;&quot;Lost Sync to switch to a better access point&quot;)
DECL|macro|awc_RID_Stats16_delta_RidLen
mdefine_line|#define awc_RID_Stats16_delta_RidLen &t;&t;awc_def_Stats16_delta_RID(0x0000,0x0000,&quot;RidLen&quot;,&t;&t;&quot;Length of the RID including the length field.&quot;)
DECL|macro|awc_RID_Stats16_delta_RxOverrunErr
mdefine_line|#define awc_RID_Stats16_delta_RxOverrunErr &t;awc_def_Stats16_delta_RID(0x0002,0x0004,&quot;Stats_RxOverrunErr&quot;,&t;&quot;Receive overruns -- No buffer available to handle the receive. (result is that the packet is never received)&quot;)
DECL|macro|awc_RID_Stats16_delta_RxPlcpCrcErr
mdefine_line|#define awc_RID_Stats16_delta_RxPlcpCrcErr &t;awc_def_Stats16_delta_RID(0x0004,0x0008,&quot;Stats_RxPlcpCrcErr&quot;,&t;&quot;PLCP header checksum errors (CRC16).&quot;)
DECL|macro|awc_RID_Stats16_delta_RxPlcpFormat
mdefine_line|#define awc_RID_Stats16_delta_RxPlcpFormat &t;awc_def_Stats16_delta_RID(0x0006,0x000C,&quot;Stats_RxPlcpFormat&quot;,&t;&quot;PLCP format errors.&quot;)
DECL|macro|awc_RID_Stats16_delta_RxPlcpLength
mdefine_line|#define awc_RID_Stats16_delta_RxPlcpLength &t;awc_def_Stats16_delta_RID(0x0008,0x0010,&quot;Stats_RxPlcpLength&quot;,&t;&quot;PLCP length is incorrect.&quot;)
DECL|macro|awc_RID_Stats16_delta_RxMacCrcErr
mdefine_line|#define awc_RID_Stats16_delta_RxMacCrcErr &t;awc_def_Stats16_delta_RID(0x000A,0x0014,&quot;Stats_RxMacCrcErr&quot;,&t;&quot;Count of MAC CRC32 errors.&quot;)
DECL|macro|awc_RID_Stats16_delta_RxMacCrcOk
mdefine_line|#define awc_RID_Stats16_delta_RxMacCrcOk &t;awc_def_Stats16_delta_RID(0x000C,0x0018,&quot;Stats_RxMacCrcOk&quot;,&t;&quot;Count of MAC CRC32 received correctly.&quot;)
DECL|macro|awc_RID_Stats16_delta_RxWepErr
mdefine_line|#define awc_RID_Stats16_delta_RxWepErr &t;&t;awc_def_Stats16_delta_RID(0x000E,0x001C,&quot;Stats_RxWepErr&quot;,&t;&quot;Count of all WEP ICV checks that failed. (this value is included in Stats_RxMacCrcOk)&quot;)
DECL|macro|awc_RID_Stats16_delta_RxWepOk
mdefine_line|#define awc_RID_Stats16_delta_RxWepOk &t;&t;awc_def_Stats16_delta_RID(0x0010,0x0020,&quot;Stats_RxWepOk&quot;,&t;&quot;Count of all WEP ICV checks that passed. (this value is  included in Stats_RxMacCrcOk)&quot;)
DECL|macro|awc_RID_Stats16_delta_RetryLong
mdefine_line|#define awc_RID_Stats16_delta_RetryLong &t;awc_def_Stats16_delta_RID(0x0012,0x0024,&quot;Stats_RetryLongCount&quot;,&t;&quot;of all long retries. (Does not include first attempt for a packet).&quot;)
DECL|macro|awc_RID_Stats16_delta_RetryShort
mdefine_line|#define awc_RID_Stats16_delta_RetryShort &t;awc_def_Stats16_delta_RID(0x0014,0x0028,&quot;Stats_RetryShort&quot;,&t;&quot;Count of all short retries. (Does not include first attempt for   a packet).&quot;)
DECL|macro|awc_RID_Stats16_delta_MaxRetries
mdefine_line|#define awc_RID_Stats16_delta_MaxRetries &t;awc_def_Stats16_delta_RID(0x0016,0x002C,&quot;Stats_MaxRetries&quot;,&t;&quot;Count of number of packets that max-retried -- ie were  never ACKd.&quot;)
DECL|macro|awc_RID_Stats16_delta_NoAck
mdefine_line|#define awc_RID_Stats16_delta_NoAck &t;&t;awc_def_Stats16_delta_RID(0x0018,0x0030,&quot;Stats_NoAck&quot;,&t;&t;&quot;Count of number of times that ACK was not received.&quot;)
DECL|macro|awc_RID_Stats16_delta_NoCts
mdefine_line|#define awc_RID_Stats16_delta_NoCts &t;&t;awc_def_Stats16_delta_RID(0x001A,0x0034,&quot;Stats_NoCts&quot;,&t;&t;&quot;Count of number of timer that CTS was not received.&quot;)
DECL|macro|awc_RID_Stats16_delta_RxAck
mdefine_line|#define awc_RID_Stats16_delta_RxAck &t;&t;awc_def_Stats16_delta_RID(0x001C,0x0038,&quot;Stats_RxAck&quot;,&t;&t;&quot;Count of number of expected ACKs that were received.&quot;)
DECL|macro|awc_RID_Stats16_delta_RxCts
mdefine_line|#define awc_RID_Stats16_delta_RxCts &t;&t;awc_def_Stats16_delta_RID(0x001E,0x003C,&quot;Stats_RxCts&quot;,&t;&t;&quot;Count of number of expected CTSs that were received.&quot;)
DECL|macro|awc_RID_Stats16_delta_TxAck
mdefine_line|#define awc_RID_Stats16_delta_TxAck &t;&t;awc_def_Stats16_delta_RID(0x0020,0x0040,&quot;Stats_TxAck&quot;,&t;&t;&quot;Count of number of ACKs transmitted.&quot;)
DECL|macro|awc_RID_Stats16_delta_TxRts
mdefine_line|#define awc_RID_Stats16_delta_TxRts &t;&t;awc_def_Stats16_delta_RID(0x0022,0x0044,&quot;Stats_TxRts&quot;,&t;&t;&quot;Count of number of RTSs transmitted.&quot;)
DECL|macro|awc_RID_Stats16_delta_TxCts
mdefine_line|#define awc_RID_Stats16_delta_TxCts &t;&t;awc_def_Stats16_delta_RID(0x0024,0x0048,&quot;Stats_TxCts&quot;,&t;&t;&quot;Count of number of CTSs transmitted.&quot;)
DECL|macro|awc_RID_Stats16_delta_TxMc
mdefine_line|#define awc_RID_Stats16_delta_TxMc &t;&t;awc_def_Stats16_delta_RID(0x0026,0x004C,&quot;Stats_TxMc&quot;,&t;&t;&quot; LMAC count of multicast packets sent (uses 802.11  Address1).&quot;)
DECL|macro|awc_RID_Stats16_delta_TxBc
mdefine_line|#define awc_RID_Stats16_delta_TxBc &t;&t;awc_def_Stats16_delta_RID(0x0028,0x0050,&quot;Stats_TxBc&quot;,&t;&t;&quot; LMAC count of broadcast packets sent (uses 802.11&quot;)
DECL|macro|awc_RID_Stats16_delta_TxUcFrags
mdefine_line|#define awc_RID_Stats16_delta_TxUcFrags &t;awc_def_Stats16_delta_RID(0x002A,0x0054,&quot;Stats_TxUcFragsLMAC&quot;,&t;&quot; count of ALL unicast fragments and whole packets sent (uses 802.11 Address1).&quot;)
DECL|macro|awc_RID_Stats16_delta_TxUcPackets
mdefine_line|#define awc_RID_Stats16_delta_TxUcPackets &t;awc_def_Stats16_delta_RID(0x002C,0x0058,&quot;Stats_TxUcPackets&quot;,&t;&quot;LMAC count of unicast packets that were ACKd (uses   802.11 Address 1).&quot;)
DECL|macro|awc_RID_Stats16_delta_TxBeacon
mdefine_line|#define awc_RID_Stats16_delta_TxBeacon &t;&t;awc_def_Stats16_delta_RID(0x002E,0x005C,&quot;Stats_TxBeacon&quot;,&t;&quot; Count of beacon packets transmitted.&quot;)
DECL|macro|awc_RID_Stats16_delta_RxBeacon
mdefine_line|#define awc_RID_Stats16_delta_RxBeacon &t;&t;awc_def_Stats16_delta_RID(0x0030,0x0060,&quot;Stats_RxBeacon&quot;,&t;&quot; Count of beacon packets received matching our BSSID.&quot;)
DECL|macro|awc_RID_Stats16_delta_TxSinColl
mdefine_line|#define awc_RID_Stats16_delta_TxSinColl &t;awc_def_Stats16_delta_RID(0x0032,0x0064,&quot;Stats_TxSinCollTransmit&quot;,&quot; single collisions. **&quot;)
DECL|macro|awc_RID_Stats16_delta_TxMulColl
mdefine_line|#define awc_RID_Stats16_delta_TxMulColl &t;awc_def_Stats16_delta_RID(0x0034,0x0068,&quot;Stats_TxMulCollTransmit&quot;,&quot; multiple collisions. **&quot;)
DECL|macro|awc_RID_Stats16_delta_DefersNo
mdefine_line|#define awc_RID_Stats16_delta_DefersNo &t;&t;awc_def_Stats16_delta_RID(0x0036,0x006C,&quot;Stats_DefersNo Transmit&quot;,&quot; frames sent with no deferral. **&quot;)
DECL|macro|awc_RID_Stats16_delta_DefersProt
mdefine_line|#define awc_RID_Stats16_delta_DefersProt &t;awc_def_Stats16_delta_RID(0x0038,0x0070,&quot;Stats_DefersProt&quot;,&t;&quot; Transmit frames deferred due to protocol.&quot;)
DECL|macro|awc_RID_Stats16_delta_DefersEngy
mdefine_line|#define awc_RID_Stats16_delta_DefersEngy &t;awc_def_Stats16_delta_RID(0x003A,0x0074,&quot;Stats_DefersEngy&quot;,&t;&quot; Transmit frames deferred due to energy detect.&quot;)
DECL|macro|awc_RID_Stats16_delta_DupFram
mdefine_line|#define awc_RID_Stats16_delta_DupFram &t;&t;awc_def_Stats16_delta_RID(0x003C,0x0078,&quot;Stats_DupFram&quot;,&t;&quot;  Duplicate receive frames and fragments.&quot;)
DECL|macro|awc_RID_Stats16_delta_RxFragDisc
mdefine_line|#define awc_RID_Stats16_delta_RxFragDisc &t;awc_def_Stats16_delta_RID(0x003E,0x007C,&quot;Stats_RxFragDisc&quot;,&t;&quot; Received partial frames. (each tally could indicate the  discarding of one or more fragments)&quot;)
DECL|macro|awc_RID_Stats16_delta_TxAged
mdefine_line|#define awc_RID_Stats16_delta_TxAged &t;&t;awc_def_Stats16_delta_RID(0x0040,0x0080,&quot;Stats_TxAged&quot;,&t;&t;&quot;   Transmit packets exceeding maximum transmit lifetime. **&quot;)
DECL|macro|awc_RID_Stats16_delta_RxAged
mdefine_line|#define awc_RID_Stats16_delta_RxAged &t;&t;awc_def_Stats16_delta_RID(0x0042,0x0084,&quot;Stats_RxAgedReceive&quot;,&t;&quot; packets exceeding maximum receive lifetime. **&quot;)
DECL|macro|awc_RID_Stats16_delta_LostSync_Max
mdefine_line|#define awc_RID_Stats16_delta_LostSync_Max &t;awc_def_Stats16_delta_RID(0x0044,0x0088,&quot;Stats_LostSync_Max&quot;,&t;&quot; Lost sync with our cell due to maximum retries occuring. Retry&quot;)
DECL|macro|awc_RID_Stats16_delta_LostSync_Mis
mdefine_line|#define awc_RID_Stats16_delta_LostSync_Mis &t;awc_def_Stats16_delta_RID(0x0046,0x008C,&quot;Stats_LostSync_Mis&quot;,&t;&quot;Lost sync with our cell due to missing too many beacons. sedBeacons&quot;)
DECL|macro|awc_RID_Stats16_delta_LostSync_Arl
mdefine_line|#define awc_RID_Stats16_delta_LostSync_Arl &t;awc_def_Stats16_delta_RID(0x0048,0x0090,&quot;Stats_LostSync_Arl&quot;,&t;&quot;Lost sync with our cell due to Average Retry Level being  Exceeded  exceeded.&quot;)
DECL|macro|awc_RID_Stats16_delta_LostSync_Dea
mdefine_line|#define awc_RID_Stats16_delta_LostSync_Dea &t;awc_def_Stats16_delta_RID(0x004A,0x0094,&quot;Stats_LostSync_Dea&quot;,&t;&quot;Lost sync with our cell due to being deauthenticated.,thed&quot;)
DECL|macro|awc_RID_Stats16_delta_LostSync_Disa
mdefine_line|#define awc_RID_Stats16_delta_LostSync_Disa &t;awc_def_Stats16_delta_RID(0x004C,0x0098,&quot;Stats_LostSync_Disa&quot;,&t;&quot; Lost sync with our cell due to being disassociated. ssoced&quot;)
DECL|macro|awc_RID_Stats16_delta_LostSync_Tsf
mdefine_line|#define awc_RID_Stats16_delta_LostSync_Tsf &t;awc_def_Stats16_delta_RID(0x004E,0x009C,&quot;Stats_LostSync_Tsf&quot;,&t;&quot;Lost sync with our cell due to excessive change in TSF  Timingtiming.&quot;)
DECL|macro|awc_RID_Stats16_delta_HostTxMc
mdefine_line|#define awc_RID_Stats16_delta_HostTxMc &t;&t;awc_def_Stats16_delta_RID(0x0050,0x00A0,&quot;Stats_HostTxMc&quot;,&t;&quot;Count of multicast packets sent by the host.&quot;)
DECL|macro|awc_RID_Stats16_delta_HostTxBc
mdefine_line|#define awc_RID_Stats16_delta_HostTxBc &t;&t;awc_def_Stats16_delta_RID(0x0052,0x00A4,&quot;Stats_HostTxBc&quot;,&t;&quot;Count of broadcast packets sent by the host.&quot;)
DECL|macro|awc_RID_Stats16_delta_HostTxUc
mdefine_line|#define awc_RID_Stats16_delta_HostTxUc &t;&t;awc_def_Stats16_delta_RID(0x0054,0x00A8,&quot;Stats_HostTxUc&quot;,&t;&quot;Count of unicast packets sent by the host.&quot;)
DECL|macro|awc_RID_Stats16_delta_HostTxFail
mdefine_line|#define awc_RID_Stats16_delta_HostTxFail &t;awc_def_Stats16_delta_RID(0x0056,0x00AC,&quot;Stats_HostTxFail&quot;,&t;&quot;  Count of host transmitted packets which failed.&quot;)
DECL|macro|awc_RID_Stats16_delta_HostRxMc
mdefine_line|#define awc_RID_Stats16_delta_HostRxMc &t;&t;awc_def_Stats16_delta_RID(0x0058,0x00B0,&quot;Stats_HostRxMc&quot;,&t;&quot;Count of host received multicast packets.&quot;)
DECL|macro|awc_RID_Stats16_delta_HostRxBc
mdefine_line|#define awc_RID_Stats16_delta_HostRxBc &t;&t;awc_def_Stats16_delta_RID(0x005A,0x00B4,&quot;Stats_HostRxBc&quot;,&t;&quot;Count of host received broadcast packets.&quot;)
DECL|macro|awc_RID_Stats16_delta_HostRxUc
mdefine_line|#define awc_RID_Stats16_delta_HostRxUc &t;&t;awc_def_Stats16_delta_RID(0x005C,0x00B8,&quot;Stats_HostRxUc&quot;,&t;&quot;Count of host received unicast packets.&quot;)
DECL|macro|awc_RID_Stats16_delta_HostRxDiscar
mdefine_line|#define awc_RID_Stats16_delta_HostRxDiscar &t;awc_def_Stats16_delta_RID(0x005E,0x00BC,&quot;Stats_HostRxDiscar&quot;,&t;&quot;Count of host received packets discarded due to:&bslash;n  Host not enabling receive.&bslash;n  Host failing to dequeue receive packets quickly.&bslash;n Packets being discarded due to magic packet mode.&quot;)
DECL|macro|awc_RID_Stats16_delta_HmacTxMc
mdefine_line|#define awc_RID_Stats16_delta_HmacTxMc &t;&t;awc_def_Stats16_delta_RID(0x0060,0x00C0,&quot;Stats_HmacTxMc&quot;,&t;&quot;Count of internally generated multicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats16_delta_HmacTxBc
mdefine_line|#define awc_RID_Stats16_delta_HmacTxBc &t;&t;awc_def_Stats16_delta_RID(0x0062,0x00C4,&quot;Stats_HmacTxBc&quot;,&t;&quot;Count of internally generated broadcast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats16_delta_HmacTxUc
mdefine_line|#define awc_RID_Stats16_delta_HmacTxUc &t;&t;awc_def_Stats16_delta_RID(0x0064,0x00C8,&quot;Stats_HmacTxUc&quot;,&t;&quot;Count of internally generated unicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats16_delta_HmacTxFail
mdefine_line|#define awc_RID_Stats16_delta_HmacTxFail &t;awc_def_Stats16_delta_RID(0x0066,0x00CC,&quot;Stats_HmacTxFail&quot;,&t;&quot;  Count of internally generated transmit packets that failed.&quot;)
DECL|macro|awc_RID_Stats16_delta_HmacRxMc
mdefine_line|#define awc_RID_Stats16_delta_HmacRxMc &t;&t;awc_def_Stats16_delta_RID(0x0068,0x00D0,&quot;Stats_HmacRxMc&quot;,&t;&quot;Count of internally received multicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats16_delta_HmacRxBc
mdefine_line|#define awc_RID_Stats16_delta_HmacRxBc &t;&t;awc_def_Stats16_delta_RID(0x006A,0x00D4,&quot;Stats_HmacRxBc&quot;,&t;&quot;Count of internally received broadcast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats16_delta_HmacRxUc
mdefine_line|#define awc_RID_Stats16_delta_HmacRxUc &t;&t;awc_def_Stats16_delta_RID(0x006C,0x00D8,&quot;Stats_HmacRxUc&quot;,&t;&quot;Count of internally received multicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats16_delta_HmacRxDisca
mdefine_line|#define awc_RID_Stats16_delta_HmacRxDisca &t;awc_def_Stats16_delta_RID(0x006E,0x00DC,&quot;Stats_HmacRxDisca&quot;,&t;&quot; Count of internally received packets that were discarded  (usually because the destination address is not for the host).&quot;)
DECL|macro|awc_RID_Stats16_delta_HmacRxAcce
mdefine_line|#define awc_RID_Stats16_delta_HmacRxAcce &t;awc_def_Stats16_delta_RID(0x0070,0x00E0,&quot;Stats_HmacRxAcce&quot;,&t;&quot;  Count of internally received packets that were accepted&quot;)
DECL|macro|awc_RID_Stats16_delta_SsidMismatch
mdefine_line|#define awc_RID_Stats16_delta_SsidMismatch &t;awc_def_Stats16_delta_RID(0x0072,0x00E4,&quot;Stats_SsidMismatch&quot;,&t;&quot; Count of SSID mismatches.&quot;)
DECL|macro|awc_RID_Stats16_delta_ApMismatch
mdefine_line|#define awc_RID_Stats16_delta_ApMismatch &t;awc_def_Stats16_delta_RID(0x0074,0x00E8,&quot;Stats_ApMismatch&quot;,&t;&quot;  Count of specified AP mismatches.&quot;)
DECL|macro|awc_RID_Stats16_delta_RatesMismatc
mdefine_line|#define awc_RID_Stats16_delta_RatesMismatc &t;awc_def_Stats16_delta_RID(0x0076,0x00EC,&quot;Stats_RatesMismatc&quot;,&t;&quot; Count of rate mismatches.&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthReject
mdefine_line|#define awc_RID_Stats16_delta_AuthReject &t;awc_def_Stats16_delta_RID(0x0078,0x00F0,&quot;Stats_AuthReject&quot;,&t;&quot;  Count of authentication rejections.&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthTimeout
mdefine_line|#define awc_RID_Stats16_delta_AuthTimeout &t;awc_def_Stats16_delta_RID(0x007A,0x00F4,&quot;Stats_AuthTimeout&quot;,&t;&quot; Count of authentication timeouts.&quot;)
DECL|macro|awc_RID_Stats16_delta_AssocReject
mdefine_line|#define awc_RID_Stats16_delta_AssocReject &t;awc_def_Stats16_delta_RID(0x007C,0x00F8,&quot;Stats_AssocReject&quot;,&t;&quot; Count of association rejections.&quot;)
DECL|macro|awc_RID_Stats16_delta_AssocTimeout
mdefine_line|#define awc_RID_Stats16_delta_AssocTimeout &t;awc_def_Stats16_delta_RID(0x007E,0x00FC,&quot;Stats_AssocTimeout&quot;,&t;&quot; Count of association timeouts.&quot;)
DECL|macro|awc_RID_Stats16_delta_NewReason
mdefine_line|#define awc_RID_Stats16_delta_NewReason &t;awc_def_Stats16_delta_RID(0x0080,0x0100,&quot;Stats_NewReason&quot;,&t;&quot;Count of reason/status codes of greater than 19.  (Values of 0 = successful are not counted)&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_1
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_1 &t;awc_def_Stats16_delta_RID(0x0082,0x0104,&quot;Stats_AuthFail_1&quot;,&t;&quot;Unspecified reason.&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_2
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_2 &t;awc_def_Stats16_delta_RID(0x0084,0x0108,&quot;Stats_AuthFail_2&quot;,&t;&quot;Previous authentication no longer valid.&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_3
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_3 &t;awc_def_Stats16_delta_RID(0x0086,0x010C,&quot;Stats_AuthFail_3&quot;,&t;&quot;Deauthenticated because sending station is leaving (has left) IBSS or ESS.&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_4
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_4 &t;awc_def_Stats16_delta_RID(0x0088,0x0110,&quot;Stats_AuthFail_4&quot;,&t;&quot;Disassociated due to inactivity&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_5
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_5 &t;awc_def_Stats16_delta_RID(0x008A,0x0114,&quot;Stats_AuthFail_5&quot;,&t;&quot;Disassociated because AP is unable to handle all currently  associated stations.&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_6
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_6 &t;awc_def_Stats16_delta_RID(0x008C,0x0118,&quot;Stats_AuthFail_6&quot;,&t;&quot;Class 2 Frame received from non-Authenticated station.&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_7
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_7 &t;awc_def_Stats16_delta_RID(0x008E,0x011C,&quot;Stats_AuthFail_7&quot;,&t;&quot;Class 3 Frame received from non-Associated station.&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_8
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_8 &t;awc_def_Stats16_delta_RID(0x0090,0x0120,&quot;Stats_AuthFail_8&quot;,&t;&quot;Disassociated because sending station is leaving (has left)&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_9
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_9 &t;awc_def_Stats16_delta_RID(0x0092,0x0124,&quot;Stats_AuthFail_9&quot;,&t;&quot;Station requesting (Re)Association is not Authenticated&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_10
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_10 &t;awc_def_Stats16_delta_RID(0x0094,0x0128,&quot;Stats_AuthFail_10&quot;,&t;&quot;Cannot support all requested capabilities in the Capability&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_11
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_11 &t;awc_def_Stats16_delta_RID(0x0096,0x012C,&quot;Stats_AuthFail_11&quot;,&t;&quot;Reassociation denied due to inability to confirm&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_12
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_12 &t;awc_def_Stats16_delta_RID(0x0098,0x0130,&quot;Stats_AuthFail_12&quot;,&t;&quot;Association denied due to reason outside the scope of the 802.11&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_13
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_13 &t;awc_def_Stats16_delta_RID(0x009A,0x0134,&quot;Stats_AuthFail_13&quot;,&t;&quot;Responding station does not support the specified Auth Alogorithm&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_14
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_14 &t;awc_def_Stats16_delta_RID(0x009C,0x0138,&quot;Stats_AuthFail_14&quot;,&t;&quot;Received an out of sequence Authentication Frame.&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_15
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_15 &t;awc_def_Stats16_delta_RID(0x009E,0x013C,&quot;Stats_AuthFail_15&quot;,&t;&quot;Authentication rejected due to challenge failure.&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_16
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_16 &t;awc_def_Stats16_delta_RID(0x00A0,0x0140,&quot;Stats_AuthFail_16&quot;,&t;&quot;Authentication rejected due to timeout waiting for next  frame in sequence.&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_17
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_17 &t;awc_def_Stats16_delta_RID(0x00A2,0x0144,&quot;Stats_AuthFail_17&quot;,&t;&quot;Association denied because AP is unable to handle  additional associated stations.&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_18
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_18 &t;awc_def_Stats16_delta_RID(0x00A4,0x0148,&quot;Stats_AuthFail_18&quot;,&t;&quot;Association denied due to requesting station not supportingall basic rates.&quot;)
DECL|macro|awc_RID_Stats16_delta_AuthFail_19
mdefine_line|#define awc_RID_Stats16_delta_AuthFail_19 &t;awc_def_Stats16_delta_RID(0x00A6,0x014C,&quot;Stats_AuthFail_19&quot;,&t;&quot;Reserved&quot;)
DECL|macro|awc_RID_Stats16_delta_RxMan
mdefine_line|#define awc_RID_Stats16_delta_RxMan &t;&t;awc_def_Stats16_delta_RID(0x00A8,0x0150,&quot;Stats_RxMan&quot;,&t;&t;&quot; Count of management packets received and handled.&quot;)
DECL|macro|awc_RID_Stats16_delta_TxMan
mdefine_line|#define awc_RID_Stats16_delta_TxMan &t;&t;awc_def_Stats16_delta_RID(0x00AA,0x0154,&quot;Stats_TxMan&quot;,&t;&t;&quot; Count of management packets transmitted.&quot;)
DECL|macro|awc_RID_Stats16_delta_RxRefresh
mdefine_line|#define awc_RID_Stats16_delta_RxRefresh &t;awc_def_Stats16_delta_RID(0x00AC,0x0158,&quot;Stats_RxRefresh&quot;,&t;&quot; Count of null data packets received.&quot;)
DECL|macro|awc_RID_Stats16_delta_TxRefresh
mdefine_line|#define awc_RID_Stats16_delta_TxRefresh &t;awc_def_Stats16_delta_RID(0x00AE,0x015C,&quot;Stats_TxRefresh&quot;,&t;&quot; Count of null data packets transmitted.&quot;)
DECL|macro|awc_RID_Stats16_delta_RxPoll
mdefine_line|#define awc_RID_Stats16_delta_RxPoll &t;&t;awc_def_Stats16_delta_RID(0x00B0,0x0160,&quot;Stats_RxPoll&quot;,&t;&t;&quot;Count of PS-Poll packets received.&quot;)
DECL|macro|awc_RID_Stats16_delta_TxPoll
mdefine_line|#define awc_RID_Stats16_delta_TxPoll &t;&t;awc_def_Stats16_delta_RID(0x00B2,0x0164,&quot;Stats_TxPoll&quot;,&t;&t;&quot;Count of PS-Poll packets transmitted.&quot;)
DECL|macro|awc_RID_Stats16_delta_HostRetries
mdefine_line|#define awc_RID_Stats16_delta_HostRetries &t;awc_def_Stats16_delta_RID(0x00B4,0x0168,&quot;Stats_HostRetries&quot;,&t;&quot; Count of long and short retries used to transmit host packets  (does not include first attempt).&quot;)
DECL|macro|awc_RID_Stats16_delta_LostSync_HostReq
mdefine_line|#define awc_RID_Stats16_delta_LostSync_HostReq &t;awc_def_Stats16_delta_RID(0x00B6,0x016C,&quot;Stats_LostSync_HostReq&quot;,&quot;Lost sync with our cell due to host request.&quot;)
DECL|macro|awc_RID_Stats16_delta_HostTxBytes
mdefine_line|#define awc_RID_Stats16_delta_HostTxBytes &t;awc_def_Stats16_delta_RID(0x00B8,0x0170,&quot;Stats_HostTxBytes&quot;,&t;&quot; Count of bytes transferred from the host.&quot;)
DECL|macro|awc_RID_Stats16_delta_HostRxBytes
mdefine_line|#define awc_RID_Stats16_delta_HostRxBytes &t;awc_def_Stats16_delta_RID(0x00BA,0x0174,&quot;Stats_HostRxBytes&quot;,&t;&quot; Count of bytes transferred to the host.&quot;)
DECL|macro|awc_RID_Stats16_delta_ElapsedUsec
mdefine_line|#define awc_RID_Stats16_delta_ElapsedUsec &t;awc_def_Stats16_delta_RID(0x00BC,0x0178,&quot;Stats_ElapsedUsec&quot;,&t;&quot; Total time since power up (or clear) in microseconds.&quot;)
DECL|macro|awc_RID_Stats16_delta_ElapsedSec
mdefine_line|#define awc_RID_Stats16_delta_ElapsedSec &t;awc_def_Stats16_delta_RID(0x00BE,0x017C,&quot;Stats_ElapsedSec&quot;,&t;&quot; Total time since power up (or clear) in seconds.&quot;)
DECL|macro|awc_RID_Stats16_delta_LostSyncBett
mdefine_line|#define awc_RID_Stats16_delta_LostSyncBett &t;awc_def_Stats16_delta_RID(0x00C0,0x0180,&quot;Stats_LostSyncBett&quot;,&t;&quot;Lost Sync to switch to a better access point&quot;)
DECL|macro|awc_RID_Stats16_clear_RidLen
mdefine_line|#define awc_RID_Stats16_clear_RidLen &t;&t;awc_def_Stats16_clear_RID(0x0000,0x0000,&quot;RidLen&quot;,&t;&t;&quot;Length of the RID including the length field.&quot;)
DECL|macro|awc_RID_Stats16_clear_RxOverrunErr
mdefine_line|#define awc_RID_Stats16_clear_RxOverrunErr &t;awc_def_Stats16_clear_RID(0x0002,0x0004,&quot;Stats_RxOverrunErr&quot;,&t;&quot;Receive overruns -- No buffer available to handle the receive. (result is that the packet is never received)&quot;)
DECL|macro|awc_RID_Stats16_clear_RxPlcpCrcErr
mdefine_line|#define awc_RID_Stats16_clear_RxPlcpCrcErr &t;awc_def_Stats16_clear_RID(0x0004,0x0008,&quot;Stats_RxPlcpCrcErr&quot;,&t;&quot;PLCP header checksum errors (CRC16).&quot;)
DECL|macro|awc_RID_Stats16_clear_RxPlcpFormat
mdefine_line|#define awc_RID_Stats16_clear_RxPlcpFormat &t;awc_def_Stats16_clear_RID(0x0006,0x000C,&quot;Stats_RxPlcpFormat&quot;,&t;&quot;PLCP format errors.&quot;)
DECL|macro|awc_RID_Stats16_clear_RxPlcpLength
mdefine_line|#define awc_RID_Stats16_clear_RxPlcpLength &t;awc_def_Stats16_clear_RID(0x0008,0x0010,&quot;Stats_RxPlcpLength&quot;,&t;&quot;PLCP length is incorrect.&quot;)
DECL|macro|awc_RID_Stats16_clear_RxMacCrcErr
mdefine_line|#define awc_RID_Stats16_clear_RxMacCrcErr &t;awc_def_Stats16_clear_RID(0x000A,0x0014,&quot;Stats_RxMacCrcErr&quot;,&t;&quot;Count of MAC CRC32 errors.&quot;)
DECL|macro|awc_RID_Stats16_clear_RxMacCrcOk
mdefine_line|#define awc_RID_Stats16_clear_RxMacCrcOk &t;awc_def_Stats16_clear_RID(0x000C,0x0018,&quot;Stats_RxMacCrcOk&quot;,&t;&quot;Count of MAC CRC32 received correctly.&quot;)
DECL|macro|awc_RID_Stats16_clear_RxWepErr
mdefine_line|#define awc_RID_Stats16_clear_RxWepErr &t;&t;awc_def_Stats16_clear_RID(0x000E,0x001C,&quot;Stats_RxWepErr&quot;,&t;&quot;Count of all WEP ICV checks that failed. (this value is included in Stats_RxMacCrcOk)&quot;)
DECL|macro|awc_RID_Stats16_clear_RxWepOk
mdefine_line|#define awc_RID_Stats16_clear_RxWepOk &t;&t;awc_def_Stats16_clear_RID(0x0010,0x0020,&quot;Stats_RxWepOk&quot;,&t;&quot;Count of all WEP ICV checks that passed. (this value is  included in Stats_RxMacCrcOk)&quot;)
DECL|macro|awc_RID_Stats16_clear_RetryLong
mdefine_line|#define awc_RID_Stats16_clear_RetryLong &t;awc_def_Stats16_clear_RID(0x0012,0x0024,&quot;Stats_RetryLongCount&quot;,&t;&quot;of all long retries. (Does not include first attempt for a packet).&quot;)
DECL|macro|awc_RID_Stats16_clear_RetryShort
mdefine_line|#define awc_RID_Stats16_clear_RetryShort &t;awc_def_Stats16_clear_RID(0x0014,0x0028,&quot;Stats_RetryShort&quot;,&t;&quot;Count of all short retries. (Does not include first attempt for   a packet).&quot;)
DECL|macro|awc_RID_Stats16_clear_MaxRetries
mdefine_line|#define awc_RID_Stats16_clear_MaxRetries &t;awc_def_Stats16_clear_RID(0x0016,0x002C,&quot;Stats_MaxRetries&quot;,&t;&quot;Count of number of packets that max-retried -- ie were  never ACKd.&quot;)
DECL|macro|awc_RID_Stats16_clear_NoAck
mdefine_line|#define awc_RID_Stats16_clear_NoAck &t;&t;awc_def_Stats16_clear_RID(0x0018,0x0030,&quot;Stats_NoAck&quot;,&t;&t;&quot;Count of number of times that ACK was not received.&quot;)
DECL|macro|awc_RID_Stats16_clear_NoCts
mdefine_line|#define awc_RID_Stats16_clear_NoCts &t;&t;awc_def_Stats16_clear_RID(0x001A,0x0034,&quot;Stats_NoCts&quot;,&t;&t;&quot;Count of number of timer that CTS was not received.&quot;)
DECL|macro|awc_RID_Stats16_clear_RxAck
mdefine_line|#define awc_RID_Stats16_clear_RxAck &t;&t;awc_def_Stats16_clear_RID(0x001C,0x0038,&quot;Stats_RxAck&quot;,&t;&t;&quot;Count of number of expected ACKs that were received.&quot;)
DECL|macro|awc_RID_Stats16_clear_RxCts
mdefine_line|#define awc_RID_Stats16_clear_RxCts &t;&t;awc_def_Stats16_clear_RID(0x001E,0x003C,&quot;Stats_RxCts&quot;,&t;&t;&quot;Count of number of expected CTSs that were received.&quot;)
DECL|macro|awc_RID_Stats16_clear_TxAck
mdefine_line|#define awc_RID_Stats16_clear_TxAck &t;&t;awc_def_Stats16_clear_RID(0x0020,0x0040,&quot;Stats_TxAck&quot;,&t;&t;&quot;Count of number of ACKs transmitted.&quot;)
DECL|macro|awc_RID_Stats16_clear_TxRts
mdefine_line|#define awc_RID_Stats16_clear_TxRts &t;&t;awc_def_Stats16_clear_RID(0x0022,0x0044,&quot;Stats_TxRts&quot;,&t;&t;&quot;Count of number of RTSs transmitted.&quot;)
DECL|macro|awc_RID_Stats16_clear_TxCts
mdefine_line|#define awc_RID_Stats16_clear_TxCts &t;&t;awc_def_Stats16_clear_RID(0x0024,0x0048,&quot;Stats_TxCts&quot;,&t;&t;&quot;Count of number of CTSs transmitted.&quot;)
DECL|macro|awc_RID_Stats16_clear_TxMc
mdefine_line|#define awc_RID_Stats16_clear_TxMc &t;&t;awc_def_Stats16_clear_RID(0x0026,0x004C,&quot;Stats_TxMc&quot;,&t;&t;&quot; LMAC count of multicast packets sent (uses 802.11  Address1).&quot;)
DECL|macro|awc_RID_Stats16_clear_TxBc
mdefine_line|#define awc_RID_Stats16_clear_TxBc &t;&t;awc_def_Stats16_clear_RID(0x0028,0x0050,&quot;Stats_TxBc&quot;,&t;&t;&quot; LMAC count of broadcast packets sent (uses 802.11&quot;)
DECL|macro|awc_RID_Stats16_clear_TxUcFrags
mdefine_line|#define awc_RID_Stats16_clear_TxUcFrags &t;awc_def_Stats16_clear_RID(0x002A,0x0054,&quot;Stats_TxUcFragsLMAC&quot;,&t;&quot; count of ALL unicast fragments and whole packets sent (uses 802.11 Address1).&quot;)
DECL|macro|awc_RID_Stats16_clear_TxUcPackets
mdefine_line|#define awc_RID_Stats16_clear_TxUcPackets &t;awc_def_Stats16_clear_RID(0x002C,0x0058,&quot;Stats_TxUcPackets&quot;,&t;&quot;LMAC count of unicast packets that were ACKd (uses   802.11 Address 1).&quot;)
DECL|macro|awc_RID_Stats16_clear_TxBeacon
mdefine_line|#define awc_RID_Stats16_clear_TxBeacon &t;&t;awc_def_Stats16_clear_RID(0x002E,0x005C,&quot;Stats_TxBeacon&quot;,&t;&quot; Count of beacon packets transmitted.&quot;)
DECL|macro|awc_RID_Stats16_clear_RxBeacon
mdefine_line|#define awc_RID_Stats16_clear_RxBeacon &t;&t;awc_def_Stats16_clear_RID(0x0030,0x0060,&quot;Stats_RxBeacon&quot;,&t;&quot; Count of beacon packets received matching our BSSID.&quot;)
DECL|macro|awc_RID_Stats16_clear_TxSinColl
mdefine_line|#define awc_RID_Stats16_clear_TxSinColl &t;awc_def_Stats16_clear_RID(0x0032,0x0064,&quot;Stats_TxSinCollTransmit&quot;,&quot; single collisions. **&quot;)
DECL|macro|awc_RID_Stats16_clear_TxMulColl
mdefine_line|#define awc_RID_Stats16_clear_TxMulColl &t;awc_def_Stats16_clear_RID(0x0034,0x0068,&quot;Stats_TxMulCollTransmit&quot;,&quot; multiple collisions. **&quot;)
DECL|macro|awc_RID_Stats16_clear_DefersNo
mdefine_line|#define awc_RID_Stats16_clear_DefersNo &t;&t;awc_def_Stats16_clear_RID(0x0036,0x006C,&quot;Stats_DefersNo Transmit&quot;,&quot; frames sent with no deferral. **&quot;)
DECL|macro|awc_RID_Stats16_clear_DefersProt
mdefine_line|#define awc_RID_Stats16_clear_DefersProt &t;awc_def_Stats16_clear_RID(0x0038,0x0070,&quot;Stats_DefersProt&quot;,&t;&quot; Transmit frames deferred due to protocol.&quot;)
DECL|macro|awc_RID_Stats16_clear_DefersEngy
mdefine_line|#define awc_RID_Stats16_clear_DefersEngy &t;awc_def_Stats16_clear_RID(0x003A,0x0074,&quot;Stats_DefersEngy&quot;,&t;&quot; Transmit frames deferred due to energy detect.&quot;)
DECL|macro|awc_RID_Stats16_clear_DupFram
mdefine_line|#define awc_RID_Stats16_clear_DupFram &t;&t;awc_def_Stats16_clear_RID(0x003C,0x0078,&quot;Stats_DupFram&quot;,&t;&quot;  Duplicate receive frames and fragments.&quot;)
DECL|macro|awc_RID_Stats16_clear_RxFragDisc
mdefine_line|#define awc_RID_Stats16_clear_RxFragDisc &t;awc_def_Stats16_clear_RID(0x003E,0x007C,&quot;Stats_RxFragDisc&quot;,&t;&quot; Received partial frames. (each tally could indicate the  discarding of one or more fragments)&quot;)
DECL|macro|awc_RID_Stats16_clear_TxAged
mdefine_line|#define awc_RID_Stats16_clear_TxAged &t;&t;awc_def_Stats16_clear_RID(0x0040,0x0080,&quot;Stats_TxAged&quot;,&t;&t;&quot;   Transmit packets exceeding maximum transmit lifetime. **&quot;)
DECL|macro|awc_RID_Stats16_clear_RxAged
mdefine_line|#define awc_RID_Stats16_clear_RxAged &t;&t;awc_def_Stats16_clear_RID(0x0042,0x0084,&quot;Stats_RxAgedReceive&quot;,&t;&quot; packets exceeding maximum receive lifetime. **&quot;)
DECL|macro|awc_RID_Stats16_clear_LostSync_Max
mdefine_line|#define awc_RID_Stats16_clear_LostSync_Max &t;awc_def_Stats16_clear_RID(0x0044,0x0088,&quot;Stats_LostSync_Max&quot;,&t;&quot; Lost sync with our cell due to maximum retries occuring. Retry&quot;)
DECL|macro|awc_RID_Stats16_clear_LostSync_Mis
mdefine_line|#define awc_RID_Stats16_clear_LostSync_Mis &t;awc_def_Stats16_clear_RID(0x0046,0x008C,&quot;Stats_LostSync_Mis&quot;,&t;&quot;Lost sync with our cell due to missing too many beacons. sedBeacons&quot;)
DECL|macro|awc_RID_Stats16_clear_LostSync_Arl
mdefine_line|#define awc_RID_Stats16_clear_LostSync_Arl &t;awc_def_Stats16_clear_RID(0x0048,0x0090,&quot;Stats_LostSync_Arl&quot;,&t;&quot;Lost sync with our cell due to Average Retry Level being  Exceeded  exceeded.&quot;)
DECL|macro|awc_RID_Stats16_clear_LostSync_Dea
mdefine_line|#define awc_RID_Stats16_clear_LostSync_Dea &t;awc_def_Stats16_clear_RID(0x004A,0x0094,&quot;Stats_LostSync_Dea&quot;,&t;&quot;Lost sync with our cell due to being deauthenticated.,thed&quot;)
DECL|macro|awc_RID_Stats16_clear_LostSync_Disa
mdefine_line|#define awc_RID_Stats16_clear_LostSync_Disa &t;awc_def_Stats16_clear_RID(0x004C,0x0098,&quot;Stats_LostSync_Disa&quot;,&t;&quot; Lost sync with our cell due to being disassociated. ssoced&quot;)
DECL|macro|awc_RID_Stats16_clear_LostSync_Tsf
mdefine_line|#define awc_RID_Stats16_clear_LostSync_Tsf &t;awc_def_Stats16_clear_RID(0x004E,0x009C,&quot;Stats_LostSync_Tsf&quot;,&t;&quot;Lost sync with our cell due to excessive change in TSF  Timingtiming.&quot;)
DECL|macro|awc_RID_Stats16_clear_HostTxMc
mdefine_line|#define awc_RID_Stats16_clear_HostTxMc &t;&t;awc_def_Stats16_clear_RID(0x0050,0x00A0,&quot;Stats_HostTxMc&quot;,&t;&quot;Count of multicast packets sent by the host.&quot;)
DECL|macro|awc_RID_Stats16_clear_HostTxBc
mdefine_line|#define awc_RID_Stats16_clear_HostTxBc &t;&t;awc_def_Stats16_clear_RID(0x0052,0x00A4,&quot;Stats_HostTxBc&quot;,&t;&quot;Count of broadcast packets sent by the host.&quot;)
DECL|macro|awc_RID_Stats16_clear_HostTxUc
mdefine_line|#define awc_RID_Stats16_clear_HostTxUc &t;&t;awc_def_Stats16_clear_RID(0x0054,0x00A8,&quot;Stats_HostTxUc&quot;,&t;&quot;Count of unicast packets sent by the host.&quot;)
DECL|macro|awc_RID_Stats16_clear_HostTxFail
mdefine_line|#define awc_RID_Stats16_clear_HostTxFail &t;awc_def_Stats16_clear_RID(0x0056,0x00AC,&quot;Stats_HostTxFail&quot;,&t;&quot;  Count of host transmitted packets which failed.&quot;)
DECL|macro|awc_RID_Stats16_clear_HostRxMc
mdefine_line|#define awc_RID_Stats16_clear_HostRxMc &t;&t;awc_def_Stats16_clear_RID(0x0058,0x00B0,&quot;Stats_HostRxMc&quot;,&t;&quot;Count of host received multicast packets.&quot;)
DECL|macro|awc_RID_Stats16_clear_HostRxBc
mdefine_line|#define awc_RID_Stats16_clear_HostRxBc &t;&t;awc_def_Stats16_clear_RID(0x005A,0x00B4,&quot;Stats_HostRxBc&quot;,&t;&quot;Count of host received broadcast packets.&quot;)
DECL|macro|awc_RID_Stats16_clear_HostRxUc
mdefine_line|#define awc_RID_Stats16_clear_HostRxUc &t;&t;awc_def_Stats16_clear_RID(0x005C,0x00B8,&quot;Stats_HostRxUc&quot;,&t;&quot;Count of host received unicast packets.&quot;)
DECL|macro|awc_RID_Stats16_clear_HostRxDiscar
mdefine_line|#define awc_RID_Stats16_clear_HostRxDiscar &t;awc_def_Stats16_clear_RID(0x005E,0x00BC,&quot;Stats_HostRxDiscar&quot;,&t;&quot;Count of host received packets discarded due to:&bslash;n  Host not enabling receive.&bslash;n  Host failing to dequeue receive packets quickly.&bslash;n Packets being discarded due to magic packet mode.&quot;)
DECL|macro|awc_RID_Stats16_clear_HmacTxMc
mdefine_line|#define awc_RID_Stats16_clear_HmacTxMc &t;&t;awc_def_Stats16_clear_RID(0x0060,0x00C0,&quot;Stats_HmacTxMc&quot;,&t;&quot;Count of internally generated multicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats16_clear_HmacTxBc
mdefine_line|#define awc_RID_Stats16_clear_HmacTxBc &t;&t;awc_def_Stats16_clear_RID(0x0062,0x00C4,&quot;Stats_HmacTxBc&quot;,&t;&quot;Count of internally generated broadcast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats16_clear_HmacTxUc
mdefine_line|#define awc_RID_Stats16_clear_HmacTxUc &t;&t;awc_def_Stats16_clear_RID(0x0064,0x00C8,&quot;Stats_HmacTxUc&quot;,&t;&quot;Count of internally generated unicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats16_clear_HmacTxFail
mdefine_line|#define awc_RID_Stats16_clear_HmacTxFail &t;awc_def_Stats16_clear_RID(0x0066,0x00CC,&quot;Stats_HmacTxFail&quot;,&t;&quot;  Count of internally generated transmit packets that failed.&quot;)
DECL|macro|awc_RID_Stats16_clear_HmacRxMc
mdefine_line|#define awc_RID_Stats16_clear_HmacRxMc &t;&t;awc_def_Stats16_clear_RID(0x0068,0x00D0,&quot;Stats_HmacRxMc&quot;,&t;&quot;Count of internally received multicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats16_clear_HmacRxBc
mdefine_line|#define awc_RID_Stats16_clear_HmacRxBc &t;&t;awc_def_Stats16_clear_RID(0x006A,0x00D4,&quot;Stats_HmacRxBc&quot;,&t;&quot;Count of internally received broadcast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats16_clear_HmacRxUc
mdefine_line|#define awc_RID_Stats16_clear_HmacRxUc &t;&t;awc_def_Stats16_clear_RID(0x006C,0x00D8,&quot;Stats_HmacRxUc&quot;,&t;&quot;Count of internally received multicast (DA) packets.&quot;)
DECL|macro|awc_RID_Stats16_clear_HmacRxDisca
mdefine_line|#define awc_RID_Stats16_clear_HmacRxDisca &t;awc_def_Stats16_clear_RID(0x006E,0x00DC,&quot;Stats_HmacRxDisca&quot;,&t;&quot; Count of internally received packets that were discarded  (usually because the destination address is not for the host).&quot;)
DECL|macro|awc_RID_Stats16_clear_HmacRxAcce
mdefine_line|#define awc_RID_Stats16_clear_HmacRxAcce &t;awc_def_Stats16_clear_RID(0x0070,0x00E0,&quot;Stats_HmacRxAcce&quot;,&t;&quot;  Count of internally received packets that were accepted&quot;)
DECL|macro|awc_RID_Stats16_clear_SsidMismatch
mdefine_line|#define awc_RID_Stats16_clear_SsidMismatch &t;awc_def_Stats16_clear_RID(0x0072,0x00E4,&quot;Stats_SsidMismatch&quot;,&t;&quot; Count of SSID mismatches.&quot;)
DECL|macro|awc_RID_Stats16_clear_ApMismatch
mdefine_line|#define awc_RID_Stats16_clear_ApMismatch &t;awc_def_Stats16_clear_RID(0x0074,0x00E8,&quot;Stats_ApMismatch&quot;,&t;&quot;  Count of specified AP mismatches.&quot;)
DECL|macro|awc_RID_Stats16_clear_RatesMismatc
mdefine_line|#define awc_RID_Stats16_clear_RatesMismatc &t;awc_def_Stats16_clear_RID(0x0076,0x00EC,&quot;Stats_RatesMismatc&quot;,&t;&quot; Count of rate mismatches.&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthReject
mdefine_line|#define awc_RID_Stats16_clear_AuthReject &t;awc_def_Stats16_clear_RID(0x0078,0x00F0,&quot;Stats_AuthReject&quot;,&t;&quot;  Count of authentication rejections.&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthTimeout
mdefine_line|#define awc_RID_Stats16_clear_AuthTimeout &t;awc_def_Stats16_clear_RID(0x007A,0x00F4,&quot;Stats_AuthTimeout&quot;,&t;&quot; Count of authentication timeouts.&quot;)
DECL|macro|awc_RID_Stats16_clear_AssocReject
mdefine_line|#define awc_RID_Stats16_clear_AssocReject &t;awc_def_Stats16_clear_RID(0x007C,0x00F8,&quot;Stats_AssocReject&quot;,&t;&quot; Count of association rejections.&quot;)
DECL|macro|awc_RID_Stats16_clear_AssocTimeout
mdefine_line|#define awc_RID_Stats16_clear_AssocTimeout &t;awc_def_Stats16_clear_RID(0x007E,0x00FC,&quot;Stats_AssocTimeout&quot;,&t;&quot; Count of association timeouts.&quot;)
DECL|macro|awc_RID_Stats16_clear_NewReason
mdefine_line|#define awc_RID_Stats16_clear_NewReason &t;awc_def_Stats16_clear_RID(0x0080,0x0100,&quot;Stats_NewReason&quot;,&t;&quot;Count of reason/status codes of greater than 19.  (Values of 0 = successful are not counted)&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthFail_1
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_1 &t;awc_def_Stats16_clear_RID(0x0082,0x0104,&quot;Stats_AuthFail_1&quot;,&t;&quot;Unspecified reason.&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthFail_2
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_2 &t;awc_def_Stats16_clear_RID(0x0084,0x0108,&quot;Stats_AuthFail_2&quot;,&t;&quot;Previous authentication no longer valid.&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthFail_3
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_3 &t;awc_def_Stats16_clear_RID(0x0086,0x010C,&quot;Stats_AuthFail_3&quot;,&t;&quot;Deauthenticated because sending station is leaving (has left) IBSS or ESS.&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthFail_4
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_4 &t;awc_def_Stats16_clear_RID(0x0088,0x0110,&quot;Stats_AuthFail_4&quot;,&t;&quot;Disassociated due to inactivity&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthFail_5
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_5 &t;awc_def_Stats16_clear_RID(0x008A,0x0114,&quot;Stats_AuthFail_5&quot;,&t;&quot;Disassociated because AP is unable to handle all currently  associated stations.&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthFail_6
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_6 &t;awc_def_Stats16_clear_RID(0x008C,0x0118,&quot;Stats_AuthFail_6&quot;,&t;&quot;Class 2 Frame received from non-Authenticated station.&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthFail_7
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_7 &t;awc_def_Stats16_clear_RID(0x008E,0x011C,&quot;Stats_AuthFail_7&quot;,&t;&quot;Class 3 Frame received from non-Associated station.&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthFail_8
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_8 &t;awc_def_Stats16_clear_RID(0x0090,0x0120,&quot;Stats_AuthFail_8&quot;,&t;&quot;Disassociated because sending station is leaving (has left) &quot; )
DECL|macro|awc_RID_Stats16_clear_AuthFail_9
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_9 &t;awc_def_Stats16_clear_RID(0x0092,0x0124,&quot;Stats_AuthFail_9&quot;,&t;&quot;Station requesting (Re)Association is not Authenticated&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthFail_10
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_10 &t;awc_def_Stats16_clear_RID(0x0094,0x0128,&quot;Stats_AuthFail_10&quot;,&t;&quot;Cannot support all requested capabilities in the Capability&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthFail_11
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_11 &t;awc_def_Stats16_clear_RID(0x0096,0x012C,&quot;Stats_AuthFail_11&quot;,&t;&quot;Reassociation denied due to inability to confirm&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthFail_12
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_12 &t;awc_def_Stats16_clear_RID(0x0098,0x0130,&quot;Stats_AuthFail_12&quot;,&t;&quot;Association denied due to reason outside the scope of the 802.11&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthFail_13
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_13 &t;awc_def_Stats16_clear_RID(0x009A,0x0134,&quot;Stats_AuthFail_13&quot;,&t;&quot;Responding station does not support the specified Auth Alogorithm&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthFail_14
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_14 &t;awc_def_Stats16_clear_RID(0x009C,0x0138,&quot;Stats_AuthFail_14&quot;,&t;&quot;Received an out of sequence Authentication Frame.&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthFail_15
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_15 &t;awc_def_Stats16_clear_RID(0x009E,0x013C,&quot;Stats_AuthFail_15&quot;,&t;&quot;Authentication rejected due to challenge failure.&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthFail_16
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_16 &t;awc_def_Stats16_clear_RID(0x00A0,0x0140,&quot;Stats_AuthFail_16&quot;,&t;&quot;Authentication rejected due to timeout waiting for next  frame in sequence.&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthFail_17
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_17 &t;awc_def_Stats16_clear_RID(0x00A2,0x0144,&quot;Stats_AuthFail_17&quot;,&t;&quot;Association denied because AP is unable to handle  additional associated stations.&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthFail_18
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_18 &t;awc_def_Stats16_clear_RID(0x00A4,0x0148,&quot;Stats_AuthFail_18&quot;,&t;&quot;Association denied due to requesting station not supportingall basic rates.&quot;)
DECL|macro|awc_RID_Stats16_clear_AuthFail_19
mdefine_line|#define awc_RID_Stats16_clear_AuthFail_19 &t;awc_def_Stats16_clear_RID(0x00A6,0x014C,&quot;Stats_AuthFail_19&quot;,&t;&quot;Reserved&quot;)
DECL|macro|awc_RID_Stats16_clear_RxMan
mdefine_line|#define awc_RID_Stats16_clear_RxMan &t;&t;awc_def_Stats16_clear_RID(0x00A8,0x0150,&quot;Stats_RxMan&quot;,&t;&t;&quot; Count of management packets received and handled.&quot;)
DECL|macro|awc_RID_Stats16_clear_TxMan
mdefine_line|#define awc_RID_Stats16_clear_TxMan &t;&t;awc_def_Stats16_clear_RID(0x00AA,0x0154,&quot;Stats_TxMan&quot;,&t;&t;&quot; Count of management packets transmitted.&quot;)
DECL|macro|awc_RID_Stats16_clear_RxRefresh
mdefine_line|#define awc_RID_Stats16_clear_RxRefresh &t;awc_def_Stats16_clear_RID(0x00AC,0x0158,&quot;Stats_RxRefresh&quot;,&t;&quot; Count of null data packets received.&quot;)
DECL|macro|awc_RID_Stats16_clear_TxRefresh
mdefine_line|#define awc_RID_Stats16_clear_TxRefresh &t;awc_def_Stats16_clear_RID(0x00AE,0x015C,&quot;Stats_TxRefresh&quot;,&t;&quot; Count of null data packets transmitted.&quot;)
DECL|macro|awc_RID_Stats16_clear_RxPoll
mdefine_line|#define awc_RID_Stats16_clear_RxPoll &t;&t;awc_def_Stats16_clear_RID(0x00B0,0x0160,&quot;Stats_RxPoll&quot;,&t;&t;&quot;Count of PS-Poll packets received.&quot;)
DECL|macro|awc_RID_Stats16_clear_TxPoll
mdefine_line|#define awc_RID_Stats16_clear_TxPoll &t;&t;awc_def_Stats16_clear_RID(0x00B2,0x0164,&quot;Stats_TxPoll&quot;,&t;&t;&quot;Count of PS-Poll packets transmitted.&quot;)
DECL|macro|awc_RID_Stats16_clear_HostRetries
mdefine_line|#define awc_RID_Stats16_clear_HostRetries &t;awc_def_Stats16_clear_RID(0x00B4,0x0168,&quot;Stats_HostRetries&quot;,&t;&quot; Count of long and short retries used to transmit host packets  (does not include first attempt).&quot;)
DECL|macro|awc_RID_Stats16_clear_LostSync_HostReq
mdefine_line|#define awc_RID_Stats16_clear_LostSync_HostReq &t;awc_def_Stats16_clear_RID(0x00B6,0x016C,&quot;Stats_LostSync_HostReq&quot;,&quot;Lost sync with our cell due to host request.&quot;)
DECL|macro|awc_RID_Stats16_clear_HostTxBytes
mdefine_line|#define awc_RID_Stats16_clear_HostTxBytes &t;awc_def_Stats16_clear_RID(0x00B8,0x0170,&quot;Stats_HostTxBytes&quot;,&t;&quot; Count of bytes transferred from the host.&quot;)
DECL|macro|awc_RID_Stats16_clear_HostRxBytes
mdefine_line|#define awc_RID_Stats16_clear_HostRxBytes &t;awc_def_Stats16_clear_RID(0x00BA,0x0174,&quot;Stats_HostRxBytes&quot;,&t;&quot; Count of bytes transferred to the host.&quot;)
DECL|macro|awc_RID_Stats16_clear_ElapsedUsec
mdefine_line|#define awc_RID_Stats16_clear_ElapsedUsec &t;awc_def_Stats16_clear_RID(0x00BC,0x0178,&quot;Stats_ElapsedUsec&quot;,&t;&quot; Total time since power up (or clear) in microseconds.&quot;)
DECL|macro|awc_RID_Stats16_clear_ElapsedSec
mdefine_line|#define awc_RID_Stats16_clear_ElapsedSec &t;awc_def_Stats16_clear_RID(0x00BE,0x017C,&quot;Stats_ElapsedSec&quot;,&t;&quot; Total time since power up (or clear) in seconds.&quot;)
DECL|macro|awc_RID_Stats16_clear_LostSyncBett
mdefine_line|#define awc_RID_Stats16_clear_LostSyncBett &t;awc_def_Stats16_clear_RID(0x00C0,0x0180,&quot;Stats_LostSyncBett&quot;,&t;&quot;Lost Sync to switch to a better access point&quot;)
multiline_comment|/*&n;const struct aironet4500_rid_selector  aironet4500_RID_Select_General_Config&t;=(const struct aironet4500_rid_selector){ 0xFF10, 1,0,0, &quot;General Configuration&quot; }; //        See notes General Configuration        Many configuration items.&n;const struct aironet4500_rid_selector  aironet4500_RID_Select_SSID_list&t;&t;=(const struct aironet4500_rid_selector){ 0xFF11, 1,0,0, &quot;Valid SSID list&quot; }; //          See notes Valid SSID list              List of SSIDs which the station may associate to.&n;const struct aironet4500_rid_selector  aironet4500_RID_Select_AP_list&t;&t;=(const struct aironet4500_rid_selector){ 0xFF12, 1,0,0, &quot;Valid AP list&quot; }; //          See notes Valid AP list                List of APs which the station may associate to.&n;const struct aironet4500_rid_selector  aironet4500_RID_Select_Driver_name&t;=(const struct aironet4500_rid_selector){ 0xFF13, 1,0,0, &quot;Driver name&quot; }; //          See notes Driver name                  The name and version of the driver (for debugging)&n;const struct aironet4500_rid_selector  aironet4500_RID_Select_Encapsulation&t;=(const struct aironet4500_rid_selector){ 0xFF14, 1,0,0, &quot;Ethernet Protocol&quot; }; //          See notes Ethernet Protocol            Rules for encapsulating ethernet payloads onto 802.11.&n;const struct aironet4500_rid_selector  aironet4500_RID_Select_WEP_volatile&t;=(const struct aironet4500_rid_selector){ 0xFF15, 1,0,0, &quot;WEP key volatile&quot; }; //          &n;const struct aironet4500_rid_selector  aironet4500_RID_Select_WEP_nonvolatile&t;=(const struct aironet4500_rid_selector){ 0xFF16, 1,0,0, &quot;WEP key non-volatile&quot; }; //&n;const struct aironet4500_rid_selector  aironet4500_RID_Select_Modulation&t;=(const struct aironet4500_rid_selector){ 0xFF17, 1,0,0, &quot;Modulation&quot; }; //&n;const struct aironet4500_rid_selector  aironet4500_RID_Select_Active_Config&t;=(const struct aironet4500_rid_selector){ 0xFF20, 0,1,1, &quot;Actual Configuration&quot; }; //          Read only      Actual Configuration    This has the same format as the General Configuration.&n;const struct aironet4500_rid_selector  aironet4500_RID_Select_Capabilities&t;=(const struct aironet4500_rid_selector){ 0xFF00, 0,1,0, &quot;Capabilities&quot; }; //          Read Only      Capabilities            PC4500 Information&n;const struct aironet4500_rid_selector  aironet4500_RID_Select_AP_Info&t;&t;=(const struct aironet4500_rid_selector){ 0xFF01, 0,1,1, &quot;AP Info&quot; }; //          Read Only      AP Info                 Access Point Information&n;const struct aironet4500_rid_selector  aironet4500_RID_Select_Radio_Info&t;=(const struct aironet4500_rid_selector){ 0xFF02, 0,1,1, &quot;Radio Info&quot; }; //          Read Only      Radio Info              Radio Information -- note radio specific&n;const struct aironet4500_rid_selector  aironet4500_RID_Select_Status&t;&t;=(const struct aironet4500_rid_selector){ 0xFF50, 0,1,1, &quot;Status&quot; }; //          Read Only      Status                  PC4500 Current Status Information&n;const struct aironet4500_rid_selector  aironet4500_RID_Select_16_stats&t;&t;=(const struct aironet4500_rid_selector){ 0xFF60, 0,1,1, &quot;Cumulative 16-bit Statistics&quot; }; //          Read Only      16-bit Statistics       Cumulative 16-bit Statistics&n;const struct aironet4500_rid_selector  aironet4500_RID_Select_16_stats_delta&t;=(const struct aironet4500_rid_selector){ 0xFF61, 0,1,1, &quot;Delta 16-bit Statistics&quot; }; //          Read Only      16-bit Statistics       Delta 16-bit Statistics (since last clear)&n;const struct aironet4500_rid_selector  aironet4500_RID_Select_16_stats_clear&t;=(const struct aironet4500_rid_selector){ 0xFF62, 0,1,1, &quot;Delta 16-bit Statistics and Clear&quot; }; //          Read Only /    16-bit Statistics       Delta 16-bit Statistics and Clear&n;const struct aironet4500_rid_selector  aironet4500_RID_Select_32_stats      &t;=(const struct aironet4500_rid_selector){ 0xFF68, 0,1,1, &quot;Cumulative 32-bit Statistics&quot; }; //          Read Only      32-bit Statistics       Cumulative 32-bit Statistics&n;const struct aironet4500_rid_selector  aironet4500_RID_Select_32_stats_delta&t;=(const struct aironet4500_rid_selector){ 0xFF69, 0,1,1, &quot;Delta 32-bit Statistics&quot;  }; //          Read Only      32-bit Statistics       Delta 32-bit Statistics (since last clear)&n;const struct aironet4500_rid_selector  aironet4500_RID_Select_32_stats_clear&t;=(const struct aironet4500_rid_selector){ 0xFF6A, 0,1,1, &quot;Delta 32-bit Statistics and Clear&quot; }; //          Read Only /    32-bit Statistics       Delta 32-bit Statistics and Clear&n;*/
DECL|variable|awc_gen_RID
r_struct
id|aironet4500_RID
id|awc_gen_RID
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|awc_act_RID
r_struct
id|aironet4500_RID
id|awc_act_RID
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|awc_SSID_RID
r_struct
id|aironet4500_RID
id|awc_SSID_RID
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|awc_AP_List_RID
r_struct
id|aironet4500_RID
id|awc_AP_List_RID
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|awc_Dname_RID
r_struct
id|aironet4500_RID
id|awc_Dname_RID
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|awc_enc_RID
r_struct
id|aironet4500_RID
id|awc_enc_RID
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|awc_WEPv_RID
r_struct
id|aironet4500_RID
id|awc_WEPv_RID
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|awc_WEPnv_RID
r_struct
id|aironet4500_RID
id|awc_WEPnv_RID
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|awc_Modulation_RID
r_struct
id|aironet4500_RID
id|awc_Modulation_RID
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|awc_Cap_RID
r_struct
id|aironet4500_RID
id|awc_Cap_RID
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|awc_Status_RID
r_struct
id|aironet4500_RID
id|awc_Status_RID
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|awc_AP_RID
r_struct
id|aironet4500_RID
id|awc_AP_RID
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|awc_Stats_RID
r_struct
id|aironet4500_RID
id|awc_Stats_RID
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|awc_Stats_delta_RID
r_struct
id|aironet4500_RID
id|awc_Stats_delta_RID
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|awc_Stats_clear_RID
r_struct
id|aironet4500_RID
id|awc_Stats_clear_RID
(braket
)braket
op_assign
initialization_block
suffix:semicolon
macro_line|#ifdef AWC_USE_16BIT_STATS
DECL|variable|awc_Stats16_RID
r_struct
id|aironet4500_RID
id|awc_Stats16_RID
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|awc_Stats16_delta_RID
r_struct
id|aironet4500_RID
id|awc_Stats16_delta_RID
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|awc_Stats16_clear_RID
r_struct
id|aironet4500_RID
id|awc_Stats16_clear_RID
(braket
)braket
op_assign
initialization_block
suffix:semicolon
macro_line|#endif
DECL|variable|awc_rids
r_struct
id|awc_rid_dir
id|awc_rids
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|awc_nof_rids
r_int
id|awc_nof_rids
op_assign
(paren
r_sizeof
(paren
id|awc_rids
)paren
op_div
r_sizeof
(paren
r_struct
id|awc_rid_dir
)paren
)paren
op_minus
l_int|1
suffix:semicolon
DECL|function|awc_rids_setup
r_int
(def_block
id|awc_rids_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|awc_private
op_star
id|priv
op_assign
(paren
r_struct
id|awc_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|AWC_NOF_RIDS
)paren
(brace
r_if
c_cond
(paren
id|awc_rids
(braket
id|i
)braket
dot
id|selector
)paren
id|memcpy
c_func
(paren
op_amp
id|priv-&gt;rid_dir
(braket
id|i
)braket
comma
op_amp
id|awc_rids
(braket
id|i
)braket
comma
r_sizeof
(paren
id|priv-&gt;rid_dir
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
r_else
id|priv-&gt;rid_dir
(braket
id|i
)braket
dot
id|selector
op_assign
l_int|NULL
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|AWC_NOF_RIDS
op_logical_and
id|i
OL
id|awc_nof_rids
suffix:semicolon
id|i
op_increment
)paren
(brace
id|priv-&gt;rid_dir
(braket
id|i
)braket
dot
id|dev
op_assign
id|dev
suffix:semicolon
)brace
suffix:semicolon
singleline_comment|// following MUST be consistent with awc_rids !!!
id|priv-&gt;rid_dir
(braket
l_int|0
)braket
dot
id|buff
op_assign
op_amp
id|priv-&gt;config
suffix:semicolon
singleline_comment|// card RID mirrors
id|priv-&gt;rid_dir
(braket
l_int|1
)braket
dot
id|buff
op_assign
op_amp
id|priv-&gt;SSIDs
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|2
)braket
dot
id|buff
op_assign
op_amp
id|priv-&gt;fixed_APs
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|3
)braket
dot
id|buff
op_assign
op_amp
id|priv-&gt;driver_name
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|4
)braket
dot
id|buff
op_assign
op_amp
id|priv-&gt;enc_trans
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|5
)braket
dot
id|buff
op_assign
op_amp
id|priv-&gt;general_config
suffix:semicolon
singleline_comment|//      &t;
id|priv-&gt;rid_dir
(braket
l_int|6
)braket
dot
id|buff
op_assign
op_amp
id|priv-&gt;capabilities
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|7
)braket
dot
id|buff
op_assign
op_amp
id|priv-&gt;status
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|8
)braket
dot
id|buff
op_assign
op_amp
id|priv-&gt;AP
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|9
)braket
dot
id|buff
op_assign
op_amp
id|priv-&gt;statistics
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|10
)braket
dot
id|buff
op_assign
op_amp
id|priv-&gt;statistics_delta
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|11
)braket
dot
id|buff
op_assign
op_amp
id|priv-&gt;statistics_delta_clear
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|12
)braket
dot
id|buff
op_assign
op_amp
id|priv-&gt;wep_volatile
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|13
)braket
dot
id|buff
op_assign
op_amp
id|priv-&gt;wep_nonvolatile
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|14
)braket
dot
id|buff
op_assign
op_amp
id|priv-&gt;modulation
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|15
)braket
dot
id|buff
op_assign
op_amp
id|priv-&gt;statistics16
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|16
)braket
dot
id|buff
op_assign
op_amp
id|priv-&gt;statistics16_delta
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|17
)braket
dot
id|buff
op_assign
op_amp
id|priv-&gt;statistics16_delta_clear
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|0
)braket
dot
id|bufflen
op_assign
r_sizeof
(paren
id|priv-&gt;config
)paren
suffix:semicolon
singleline_comment|// card RID mirrors
id|priv-&gt;rid_dir
(braket
l_int|1
)braket
dot
id|bufflen
op_assign
r_sizeof
(paren
id|priv-&gt;SSIDs
)paren
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|2
)braket
dot
id|bufflen
op_assign
r_sizeof
(paren
id|priv-&gt;fixed_APs
)paren
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|3
)braket
dot
id|bufflen
op_assign
r_sizeof
(paren
id|priv-&gt;driver_name
)paren
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|4
)braket
dot
id|bufflen
op_assign
r_sizeof
(paren
id|priv-&gt;enc_trans
)paren
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|5
)braket
dot
id|bufflen
op_assign
r_sizeof
(paren
id|priv-&gt;general_config
)paren
suffix:semicolon
singleline_comment|//
id|priv-&gt;rid_dir
(braket
l_int|6
)braket
dot
id|bufflen
op_assign
r_sizeof
(paren
id|priv-&gt;capabilities
)paren
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|7
)braket
dot
id|bufflen
op_assign
r_sizeof
(paren
id|priv-&gt;status
)paren
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|8
)braket
dot
id|bufflen
op_assign
r_sizeof
(paren
id|priv-&gt;AP
)paren
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|9
)braket
dot
id|bufflen
op_assign
r_sizeof
(paren
id|priv-&gt;statistics
)paren
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|10
)braket
dot
id|bufflen
op_assign
r_sizeof
(paren
id|priv-&gt;statistics_delta
)paren
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|11
)braket
dot
id|bufflen
op_assign
r_sizeof
(paren
id|priv-&gt;statistics_delta_clear
)paren
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|12
)braket
dot
id|bufflen
op_assign
r_sizeof
(paren
id|priv-&gt;wep_volatile
)paren
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|13
)braket
dot
id|bufflen
op_assign
r_sizeof
(paren
id|priv-&gt;wep_nonvolatile
)paren
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|14
)braket
dot
id|bufflen
op_assign
r_sizeof
(paren
id|priv-&gt;modulation
)paren
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|15
)braket
dot
id|bufflen
op_assign
r_sizeof
(paren
id|priv-&gt;statistics16
)paren
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|16
)braket
dot
id|bufflen
op_assign
r_sizeof
(paren
id|priv-&gt;statistics16_delta
)paren
suffix:semicolon
id|priv-&gt;rid_dir
(braket
l_int|17
)braket
dot
id|bufflen
op_assign
r_sizeof
(paren
id|priv-&gt;statistics16_delta_clear
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)def_block
suffix:semicolon
eof
