macro_line|#if (!defined(dprintk))
DECL|macro|dprintk
macro_line|# define dprintk(x)
macro_line|#endif
multiline_comment|/*------------------------------------------------------------------------------&n; *              D E F I N E S&n; *----------------------------------------------------------------------------*/
DECL|macro|MAXIMUM_NUM_CONTAINERS
mdefine_line|#define MAXIMUM_NUM_CONTAINERS&t;32
DECL|macro|AAC_NUM_FIB
mdefine_line|#define AAC_NUM_FIB&t;&t;(256 + 64)
DECL|macro|AAC_NUM_IO_FIB
mdefine_line|#define AAC_NUM_IO_FIB&t;&t;100
DECL|macro|AAC_MAX_LUN
mdefine_line|#define AAC_MAX_LUN&t;&t;(8)
DECL|macro|AAC_MAX_HOSTPHYSMEMPAGES
mdefine_line|#define AAC_MAX_HOSTPHYSMEMPAGES (0xfffff)
multiline_comment|/*&n; * These macros convert from physical channels to virtual channels&n; */
DECL|macro|CONTAINER_CHANNEL
mdefine_line|#define CONTAINER_CHANNEL&t;&t;(0)
DECL|macro|ID_LUN_TO_CONTAINER
mdefine_line|#define ID_LUN_TO_CONTAINER(id, lun)&t;(id)
DECL|macro|CONTAINER_TO_CHANNEL
mdefine_line|#define CONTAINER_TO_CHANNEL(cont)&t;(CONTAINER_CHANNEL)
DECL|macro|CONTAINER_TO_ID
mdefine_line|#define CONTAINER_TO_ID(cont)&t;&t;(cont)
DECL|macro|CONTAINER_TO_LUN
mdefine_line|#define CONTAINER_TO_LUN(cont)&t;&t;(0)
DECL|macro|aac_phys_to_logical
mdefine_line|#define aac_phys_to_logical(x)  (x+1)
DECL|macro|aac_logical_to_phys
mdefine_line|#define aac_logical_to_phys(x)  (x?x-1:0)
multiline_comment|/* #define AAC_DETAILED_STATUS_INFO */
DECL|struct|diskparm
r_struct
id|diskparm
(brace
DECL|member|heads
r_int
id|heads
suffix:semicolon
DECL|member|sectors
r_int
id|sectors
suffix:semicolon
DECL|member|cylinders
r_int
id|cylinders
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;DON&squot;T CHANGE THE ORDER, this is set by the firmware&n; */
DECL|macro|CT_NONE
mdefine_line|#define&t;&t;CT_NONE&t;&t;&t;0
DECL|macro|CT_VOLUME
mdefine_line|#define&t;&t;CT_VOLUME&t;&t;1
DECL|macro|CT_MIRROR
mdefine_line|#define&t;&t;CT_MIRROR&t;&t;2
DECL|macro|CT_STRIPE
mdefine_line|#define&t;&t;CT_STRIPE&t;&t;3
DECL|macro|CT_RAID5
mdefine_line|#define&t;&t;CT_RAID5&t;&t;4
DECL|macro|CT_SSRW
mdefine_line|#define&t;&t;CT_SSRW&t;&t;&t;5
DECL|macro|CT_SSRO
mdefine_line|#define&t;&t;CT_SSRO&t;&t;&t;6
DECL|macro|CT_MORPH
mdefine_line|#define&t;&t;CT_MORPH&t;&t;7
DECL|macro|CT_PASSTHRU
mdefine_line|#define&t;&t;CT_PASSTHRU&t;&t;8
DECL|macro|CT_RAID4
mdefine_line|#define&t;&t;CT_RAID4&t;&t;9
DECL|macro|CT_RAID10
mdefine_line|#define&t;&t;CT_RAID10&t;&t;10&t;/* stripe of mirror */
DECL|macro|CT_RAID00
mdefine_line|#define&t;&t;CT_RAID00&t;&t;11&t;/* stripe of stripe */
DECL|macro|CT_VOLUME_OF_MIRRORS
mdefine_line|#define&t;&t;CT_VOLUME_OF_MIRRORS&t;12&t;/* volume of mirror */
DECL|macro|CT_PSEUDO_RAID
mdefine_line|#define&t;&t;CT_PSEUDO_RAID&t;&t;13&t;/* really raid4 */
DECL|macro|CT_LAST_VOLUME_TYPE
mdefine_line|#define&t;&t;CT_LAST_VOLUME_TYPE&t;14
DECL|macro|CT_OK
mdefine_line|#define &t;CT_OK        &t;&t;218
multiline_comment|/*&n; *&t;Types of objects addressable in some fashion by the client.&n; *&t;This is a superset of those objects handled just by the filesystem&n; *&t;and includes &quot;raw&quot; objects that an administrator would use to&n; *&t;configure containers and filesystems.&n; */
DECL|macro|FT_REG
mdefine_line|#define&t;&t;FT_REG&t;&t;1&t;/* regular file */
DECL|macro|FT_DIR
mdefine_line|#define&t;&t;FT_DIR&t;&t;2&t;/* directory */
DECL|macro|FT_BLK
mdefine_line|#define&t;&t;FT_BLK&t;&t;3&t;/* &quot;block&quot; device - reserved */
DECL|macro|FT_CHR
mdefine_line|#define&t;&t;FT_CHR&t;&t;4&t;/* &quot;character special&quot; device - reserved */
DECL|macro|FT_LNK
mdefine_line|#define&t;&t;FT_LNK&t;&t;5&t;/* symbolic link */
DECL|macro|FT_SOCK
mdefine_line|#define&t;&t;FT_SOCK&t;&t;6&t;/* socket */
DECL|macro|FT_FIFO
mdefine_line|#define&t;&t;FT_FIFO&t;&t;7&t;/* fifo */
DECL|macro|FT_FILESYS
mdefine_line|#define&t;&t;FT_FILESYS&t;8&t;/* ADAPTEC&squot;s &quot;FSA&quot;(tm) filesystem */
DECL|macro|FT_DRIVE
mdefine_line|#define&t;&t;FT_DRIVE&t;9&t;/* physical disk - addressable in scsi by bus/id/lun */
DECL|macro|FT_SLICE
mdefine_line|#define&t;&t;FT_SLICE&t;10&t;/* virtual disk - raw volume - slice */
DECL|macro|FT_PARTITION
mdefine_line|#define&t;&t;FT_PARTITION&t;11&t;/* FSA partition - carved out of a slice - building block for containers */
DECL|macro|FT_VOLUME
mdefine_line|#define&t;&t;FT_VOLUME&t;12&t;/* Container - Volume Set */
DECL|macro|FT_STRIPE
mdefine_line|#define&t;&t;FT_STRIPE&t;13&t;/* Container - Stripe Set */
DECL|macro|FT_MIRROR
mdefine_line|#define&t;&t;FT_MIRROR&t;14&t;/* Container - Mirror Set */
DECL|macro|FT_RAID5
mdefine_line|#define&t;&t;FT_RAID5&t;15&t;/* Container - Raid 5 Set */
DECL|macro|FT_DATABASE
mdefine_line|#define&t;&t;FT_DATABASE&t;16&t;/* Storage object with &quot;foreign&quot; content manager */
multiline_comment|/*&n; *&t;Host side memory scatter gather list&n; *&t;Used by the adapter for read, write, and readdirplus operations&n; *&t;We have separate 32 and 64 bit version because even&n; *&t;on 64 bit systems not all cards support the 64 bit version&n; */
DECL|struct|sgentry
r_struct
id|sgentry
(brace
DECL|member|addr
id|u32
id|addr
suffix:semicolon
multiline_comment|/* 32-bit address. */
DECL|member|count
id|u32
id|count
suffix:semicolon
multiline_comment|/* Length. */
)brace
suffix:semicolon
DECL|struct|sgentry64
r_struct
id|sgentry64
(brace
DECL|member|addr
id|u32
id|addr
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 64-bit addr. 2 pieces for data alignment */
DECL|member|count
id|u32
id|count
suffix:semicolon
multiline_comment|/* Length. */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;SGMAP&n; *&n; *&t;This is the SGMAP structure for all commands that use&n; *&t;32-bit addressing.&n; */
DECL|struct|sgmap
r_struct
id|sgmap
(brace
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|sg
r_struct
id|sgentry
id|sg
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sgmap64
r_struct
id|sgmap64
(brace
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|sg
r_struct
id|sgentry64
id|sg
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|creation_info
r_struct
id|creation_info
(brace
DECL|member|buildnum
id|u8
id|buildnum
suffix:semicolon
multiline_comment|/* e.g., 588 */
DECL|member|usec
id|u8
id|usec
suffix:semicolon
multiline_comment|/* e.g., 588 */
DECL|member|via
id|u8
id|via
suffix:semicolon
multiline_comment|/* e.g., 1 = FSU,&n;&t;&t;&t;&t;&t;&t; * &t; 2 = API&n;&t;&t;&t;&t;&t;&t; */
DECL|member|year
id|u8
id|year
suffix:semicolon
multiline_comment|/* e.g., 1997 = 97 */
DECL|member|date
id|u32
id|date
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t; * unsigned &t;Month&t;&t;:4;&t;// 1 - 12&n;&t;&t;&t;&t;&t;&t; * unsigned &t;Day&t;&t;:6;&t;// 1 - 32&n;&t;&t;&t;&t;&t;&t; * unsigned &t;Hour&t;&t;:6;&t;// 0 - 23&n;&t;&t;&t;&t;&t;&t; * unsigned &t;Minute&t;&t;:6;&t;// 0 - 60&n;&t;&t;&t;&t;&t;&t; * unsigned &t;Second&t;&t;:6;&t;// 0 - 60&n;&t;&t;&t;&t;&t;&t; */
DECL|member|serial
id|u32
id|serial
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* e.g., 0x1DEADB0BFAFAF001 */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Define all the constants needed for the communication interface&n; */
multiline_comment|/*&n; *&t;Define how many queue entries each queue will have and the total&n; *&t;number of entries for the entire communication interface. Also define&n; *&t;how many queues we support.&n; *&n; *&t;This has to match the controller&n; */
DECL|macro|NUMBER_OF_COMM_QUEUES
mdefine_line|#define NUMBER_OF_COMM_QUEUES  8   
singleline_comment|// 4 command; 4 response
DECL|macro|HOST_HIGH_CMD_ENTRIES
mdefine_line|#define HOST_HIGH_CMD_ENTRIES  4
DECL|macro|HOST_NORM_CMD_ENTRIES
mdefine_line|#define HOST_NORM_CMD_ENTRIES  8
DECL|macro|ADAP_HIGH_CMD_ENTRIES
mdefine_line|#define ADAP_HIGH_CMD_ENTRIES  4
DECL|macro|ADAP_NORM_CMD_ENTRIES
mdefine_line|#define ADAP_NORM_CMD_ENTRIES  512
DECL|macro|HOST_HIGH_RESP_ENTRIES
mdefine_line|#define HOST_HIGH_RESP_ENTRIES 4
DECL|macro|HOST_NORM_RESP_ENTRIES
mdefine_line|#define HOST_NORM_RESP_ENTRIES 512
DECL|macro|ADAP_HIGH_RESP_ENTRIES
mdefine_line|#define ADAP_HIGH_RESP_ENTRIES 4
DECL|macro|ADAP_NORM_RESP_ENTRIES
mdefine_line|#define ADAP_NORM_RESP_ENTRIES 8
DECL|macro|TOTAL_QUEUE_ENTRIES
mdefine_line|#define TOTAL_QUEUE_ENTRIES  &bslash;&n;    (HOST_NORM_CMD_ENTRIES + HOST_HIGH_CMD_ENTRIES + ADAP_NORM_CMD_ENTRIES + ADAP_HIGH_CMD_ENTRIES + &bslash;&n;&t;    HOST_NORM_RESP_ENTRIES + HOST_HIGH_RESP_ENTRIES + ADAP_NORM_RESP_ENTRIES + ADAP_HIGH_RESP_ENTRIES)
multiline_comment|/*&n; *&t;Set the queues on a 16 byte alignment&n; */
DECL|macro|QUEUE_ALIGNMENT
mdefine_line|#define QUEUE_ALIGNMENT&t;&t;16
multiline_comment|/*&n; *&t;The queue headers define the Communication Region queues. These&n; *&t;are physically contiguous and accessible by both the adapter and the&n; *&t;host. Even though all queue headers are in the same contiguous block&n; *&t;they will be represented as individual units in the data structures.&n; */
DECL|struct|aac_entry
r_struct
id|aac_entry
(brace
DECL|member|size
id|u32
id|size
suffix:semicolon
multiline_comment|/* Size in bytes of Fib which this QE points to */
DECL|member|addr
id|u32
id|addr
suffix:semicolon
multiline_comment|/* Receiver address of the FIB */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;The adapter assumes the ProducerIndex and ConsumerIndex are grouped&n; *&t;adjacently and in that order.&n; */
DECL|struct|aac_qhdr
r_struct
id|aac_qhdr
(brace
DECL|member|header_addr
id|u64
id|header_addr
suffix:semicolon
multiline_comment|/* Address to hand the adapter to access to this queue head */
DECL|member|producer
id|u32
op_star
id|producer
suffix:semicolon
multiline_comment|/* The producer index for this queue (host address) */
DECL|member|consumer
id|u32
op_star
id|consumer
suffix:semicolon
multiline_comment|/* The consumer index for this queue (host address) */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Define all the events which the adapter would like to notify&n; *&t;the host of.&n; */
DECL|macro|HostNormCmdQue
mdefine_line|#define&t;&t;HostNormCmdQue&t;&t;1&t;/* Change in host normal priority command queue */
DECL|macro|HostHighCmdQue
mdefine_line|#define&t;&t;HostHighCmdQue&t;&t;2&t;/* Change in host high priority command queue */
DECL|macro|HostNormRespQue
mdefine_line|#define&t;&t;HostNormRespQue&t;&t;3&t;/* Change in host normal priority response queue */
DECL|macro|HostHighRespQue
mdefine_line|#define&t;&t;HostHighRespQue&t;&t;4&t;/* Change in host high priority response queue */
DECL|macro|AdapNormRespNotFull
mdefine_line|#define&t;&t;AdapNormRespNotFull&t;5
DECL|macro|AdapHighRespNotFull
mdefine_line|#define&t;&t;AdapHighRespNotFull&t;6
DECL|macro|AdapNormCmdNotFull
mdefine_line|#define&t;&t;AdapNormCmdNotFull&t;7
DECL|macro|AdapHighCmdNotFull
mdefine_line|#define&t;&t;AdapHighCmdNotFull&t;8
DECL|macro|SynchCommandComplete
mdefine_line|#define&t;&t;SynchCommandComplete&t;9
DECL|macro|AdapInternalError
mdefine_line|#define&t;&t;AdapInternalError&t;0xfe    /* The adapter detected an internal error shutting down */
multiline_comment|/*&n; *&t;Define all the events the host wishes to notify the&n; *&t;adapter of. The first four values much match the Qid the&n; *&t;corresponding queue.&n; */
DECL|macro|AdapNormCmdQue
mdefine_line|#define&t;&t;AdapNormCmdQue&t;&t;2
DECL|macro|AdapHighCmdQue
mdefine_line|#define&t;&t;AdapHighCmdQue&t;&t;3
DECL|macro|AdapNormRespQue
mdefine_line|#define&t;&t;AdapNormRespQue&t;&t;6
DECL|macro|AdapHighRespQue
mdefine_line|#define&t;&t;AdapHighRespQue&t;&t;7
DECL|macro|HostShutdown
mdefine_line|#define&t;&t;HostShutdown&t;&t;8
DECL|macro|HostPowerFail
mdefine_line|#define&t;&t;HostPowerFail&t;&t;9
DECL|macro|FatalCommError
mdefine_line|#define&t;&t;FatalCommError&t;&t;10
DECL|macro|HostNormRespNotFull
mdefine_line|#define&t;&t;HostNormRespNotFull&t;11
DECL|macro|HostHighRespNotFull
mdefine_line|#define&t;&t;HostHighRespNotFull&t;12
DECL|macro|HostNormCmdNotFull
mdefine_line|#define&t;&t;HostNormCmdNotFull&t;13
DECL|macro|HostHighCmdNotFull
mdefine_line|#define&t;&t;HostHighCmdNotFull&t;14
DECL|macro|FastIo
mdefine_line|#define&t;&t;FastIo&t;&t;&t;15
DECL|macro|AdapPrintfDone
mdefine_line|#define&t;&t;AdapPrintfDone&t;&t;16
multiline_comment|/*&n; *&t;Define all the queues that the adapter and host use to communicate&n; *&t;Number them to match the physical queue layout.&n; */
DECL|enum|aac_queue_types
r_enum
id|aac_queue_types
(brace
DECL|enumerator|HostNormCmdQueue
id|HostNormCmdQueue
op_assign
l_int|0
comma
multiline_comment|/* Adapter to host normal priority command traffic */
DECL|enumerator|HostHighCmdQueue
id|HostHighCmdQueue
comma
multiline_comment|/* Adapter to host high priority command traffic */
DECL|enumerator|AdapNormCmdQueue
id|AdapNormCmdQueue
comma
multiline_comment|/* Host to adapter normal priority command traffic */
DECL|enumerator|AdapHighCmdQueue
id|AdapHighCmdQueue
comma
multiline_comment|/* Host to adapter high priority command traffic */
DECL|enumerator|HostNormRespQueue
id|HostNormRespQueue
comma
multiline_comment|/* Adapter to host normal priority response traffic */
DECL|enumerator|HostHighRespQueue
id|HostHighRespQueue
comma
multiline_comment|/* Adapter to host high priority response traffic */
DECL|enumerator|AdapNormRespQueue
id|AdapNormRespQueue
comma
multiline_comment|/* Host to adapter normal priority response traffic */
DECL|enumerator|AdapHighRespQueue
id|AdapHighRespQueue
multiline_comment|/* Host to adapter high priority response traffic */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Assign type values to the FSA communication data structures&n; */
DECL|macro|FIB_MAGIC
mdefine_line|#define&t;&t;FIB_MAGIC&t;0x0001
multiline_comment|/*&n; *&t;Define the priority levels the FSA communication routines support.&n; */
DECL|macro|FsaNormal
mdefine_line|#define&t;&t;FsaNormal&t;1
DECL|macro|FsaHigh
mdefine_line|#define&t;&t;FsaHigh&t;&t;2
multiline_comment|/*&n; * Define the FIB. The FIB is the where all the requested data and&n; * command information are put to the application on the FSA adapter.&n; */
DECL|struct|aac_fibhdr
r_struct
id|aac_fibhdr
(brace
DECL|member|XferState
id|u32
id|XferState
suffix:semicolon
singleline_comment|// Current transfer state for this CCB
DECL|member|Command
id|u16
id|Command
suffix:semicolon
singleline_comment|// Routing information for the destination
DECL|member|StructType
id|u8
id|StructType
suffix:semicolon
singleline_comment|// Type FIB
DECL|member|Flags
id|u8
id|Flags
suffix:semicolon
singleline_comment|// Flags for FIB
DECL|member|Size
id|u16
id|Size
suffix:semicolon
singleline_comment|// Size of this FIB in bytes
DECL|member|SenderSize
id|u16
id|SenderSize
suffix:semicolon
singleline_comment|// Size of the FIB in the sender (for response sizing)
DECL|member|SenderFibAddress
id|u32
id|SenderFibAddress
suffix:semicolon
singleline_comment|// Host defined data in the FIB
DECL|member|ReceiverFibAddress
id|u32
id|ReceiverFibAddress
suffix:semicolon
singleline_comment|// Logical address of this FIB for the adapter
DECL|member|SenderData
id|u32
id|SenderData
suffix:semicolon
singleline_comment|// Place holder for the sender to store data
r_union
(brace
r_struct
(brace
DECL|member|_ReceiverTimeStart
id|u32
id|_ReceiverTimeStart
suffix:semicolon
singleline_comment|// Timestamp for receipt of fib
DECL|member|_ReceiverTimeDone
id|u32
id|_ReceiverTimeDone
suffix:semicolon
singleline_comment|// Timestamp for completion of fib
DECL|member|_s
)brace
id|_s
suffix:semicolon
DECL|member|_u
)brace
id|_u
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FIB_DATA_SIZE_IN_BYTES
mdefine_line|#define FIB_DATA_SIZE_IN_BYTES (512 - sizeof(struct aac_fibhdr))
DECL|struct|hw_fib
r_struct
id|hw_fib
(brace
DECL|member|header
r_struct
id|aac_fibhdr
id|header
suffix:semicolon
DECL|member|data
id|u8
id|data
(braket
id|FIB_DATA_SIZE_IN_BYTES
)braket
suffix:semicolon
singleline_comment|// Command specific data
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;FIB commands&n; */
DECL|macro|TestCommandResponse
mdefine_line|#define &t;TestCommandResponse&t;&t;1
DECL|macro|TestAdapterCommand
mdefine_line|#define&t;&t;TestAdapterCommand&t;&t;2
multiline_comment|/*&n; *&t;Lowlevel and comm commands&n; */
DECL|macro|LastTestCommand
mdefine_line|#define&t;&t;LastTestCommand&t;&t;&t;100
DECL|macro|ReinitHostNormCommandQueue
mdefine_line|#define&t;&t;ReinitHostNormCommandQueue&t;101
DECL|macro|ReinitHostHighCommandQueue
mdefine_line|#define&t;&t;ReinitHostHighCommandQueue&t;102
DECL|macro|ReinitHostHighRespQueue
mdefine_line|#define&t;&t;ReinitHostHighRespQueue&t;&t;103
DECL|macro|ReinitHostNormRespQueue
mdefine_line|#define&t;&t;ReinitHostNormRespQueue&t;&t;104
DECL|macro|ReinitAdapNormCommandQueue
mdefine_line|#define&t;&t;ReinitAdapNormCommandQueue&t;105
DECL|macro|ReinitAdapHighCommandQueue
mdefine_line|#define&t;&t;ReinitAdapHighCommandQueue&t;107
DECL|macro|ReinitAdapHighRespQueue
mdefine_line|#define&t;&t;ReinitAdapHighRespQueue&t;&t;108
DECL|macro|ReinitAdapNormRespQueue
mdefine_line|#define&t;&t;ReinitAdapNormRespQueue&t;&t;109
DECL|macro|InterfaceShutdown
mdefine_line|#define&t;&t;InterfaceShutdown&t;&t;110
DECL|macro|DmaCommandFib
mdefine_line|#define&t;&t;DmaCommandFib&t;&t;&t;120
DECL|macro|StartProfile
mdefine_line|#define&t;&t;StartProfile&t;&t;&t;121
DECL|macro|TermProfile
mdefine_line|#define&t;&t;TermProfile&t;&t;&t;122
DECL|macro|SpeedTest
mdefine_line|#define&t;&t;SpeedTest&t;&t;&t;123
DECL|macro|TakeABreakPt
mdefine_line|#define&t;&t;TakeABreakPt&t;&t;&t;124
DECL|macro|RequestPerfData
mdefine_line|#define&t;&t;RequestPerfData&t;&t;&t;125
DECL|macro|SetInterruptDefTimer
mdefine_line|#define&t;&t;SetInterruptDefTimer&t;&t;126
DECL|macro|SetInterruptDefCount
mdefine_line|#define&t;&t;SetInterruptDefCount&t;&t;127
DECL|macro|GetInterruptDefStatus
mdefine_line|#define&t;&t;GetInterruptDefStatus&t;&t;128
DECL|macro|LastCommCommand
mdefine_line|#define&t;&t;LastCommCommand&t;&t;&t;129
multiline_comment|/*&n; *&t;Filesystem commands&n; */
DECL|macro|NuFileSystem
mdefine_line|#define&t;&t;NuFileSystem&t;&t;&t;300
DECL|macro|UFS
mdefine_line|#define&t;&t;UFS&t;&t;&t;&t;301
DECL|macro|HostFileSystem
mdefine_line|#define&t;&t;HostFileSystem&t;&t;&t;302
DECL|macro|LastFileSystemCommand
mdefine_line|#define&t;&t;LastFileSystemCommand&t;&t;303
multiline_comment|/*&n; *&t;Container Commands&n; */
DECL|macro|ContainerCommand
mdefine_line|#define&t;&t;ContainerCommand&t;&t;500
DECL|macro|ContainerCommand64
mdefine_line|#define&t;&t;ContainerCommand64&t;&t;501
multiline_comment|/*&n; *&t;Cluster Commands&n; */
DECL|macro|ClusterCommand
mdefine_line|#define&t;&t;ClusterCommand&t; &t;&t;550
multiline_comment|/*&n; *&t;Scsi Port commands (scsi passthrough)&n; */
DECL|macro|ScsiPortCommand
mdefine_line|#define&t;&t;ScsiPortCommand&t;&t;&t;600
DECL|macro|ScsiPortCommand64
mdefine_line|#define&t;&t;ScsiPortCommand64&t;&t;601
multiline_comment|/*&n; *&t;Misc house keeping and generic adapter initiated commands&n; */
DECL|macro|AifRequest
mdefine_line|#define&t;&t;AifRequest&t;&t;&t;700
DECL|macro|CheckRevision
mdefine_line|#define&t;&t;CheckRevision&t;&t;&t;701
DECL|macro|FsaHostShutdown
mdefine_line|#define&t;&t;FsaHostShutdown&t;&t;&t;702
DECL|macro|RequestAdapterInfo
mdefine_line|#define&t;&t;RequestAdapterInfo&t;&t;703
DECL|macro|IsAdapterPaused
mdefine_line|#define&t;&t;IsAdapterPaused&t;&t;&t;704
DECL|macro|SendHostTime
mdefine_line|#define&t;&t;SendHostTime&t;&t;&t;705
DECL|macro|LastMiscCommand
mdefine_line|#define&t;&t;LastMiscCommand&t;&t;&t;706
singleline_comment|//
singleline_comment|// Commands that will target the failover level on the FSA adapter
singleline_comment|//
DECL|enum|fib_xfer_state
r_enum
id|fib_xfer_state
(brace
DECL|enumerator|HostOwned
id|HostOwned
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
DECL|enumerator|AdapterOwned
id|AdapterOwned
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
DECL|enumerator|FibInitialized
id|FibInitialized
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
DECL|enumerator|FibEmpty
id|FibEmpty
op_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
comma
DECL|enumerator|AllocatedFromPool
id|AllocatedFromPool
op_assign
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
DECL|enumerator|SentFromHost
id|SentFromHost
op_assign
(paren
l_int|1
op_lshift
l_int|5
)paren
comma
DECL|enumerator|SentFromAdapter
id|SentFromAdapter
op_assign
(paren
l_int|1
op_lshift
l_int|6
)paren
comma
DECL|enumerator|ResponseExpected
id|ResponseExpected
op_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
comma
DECL|enumerator|NoResponseExpected
id|NoResponseExpected
op_assign
(paren
l_int|1
op_lshift
l_int|8
)paren
comma
DECL|enumerator|AdapterProcessed
id|AdapterProcessed
op_assign
(paren
l_int|1
op_lshift
l_int|9
)paren
comma
DECL|enumerator|HostProcessed
id|HostProcessed
op_assign
(paren
l_int|1
op_lshift
l_int|10
)paren
comma
DECL|enumerator|HighPriority
id|HighPriority
op_assign
(paren
l_int|1
op_lshift
l_int|11
)paren
comma
DECL|enumerator|NormalPriority
id|NormalPriority
op_assign
(paren
l_int|1
op_lshift
l_int|12
)paren
comma
DECL|enumerator|Async
id|Async
op_assign
(paren
l_int|1
op_lshift
l_int|13
)paren
comma
DECL|enumerator|AsyncIo
id|AsyncIo
op_assign
(paren
l_int|1
op_lshift
l_int|13
)paren
comma
singleline_comment|// rpbfix: remove with new regime
DECL|enumerator|PageFileIo
id|PageFileIo
op_assign
(paren
l_int|1
op_lshift
l_int|14
)paren
comma
singleline_comment|// rpbfix: remove with new regime
DECL|enumerator|ShutdownRequest
id|ShutdownRequest
op_assign
(paren
l_int|1
op_lshift
l_int|15
)paren
comma
DECL|enumerator|LazyWrite
id|LazyWrite
op_assign
(paren
l_int|1
op_lshift
l_int|16
)paren
comma
singleline_comment|// rpbfix: remove with new regime
DECL|enumerator|AdapterMicroFib
id|AdapterMicroFib
op_assign
(paren
l_int|1
op_lshift
l_int|17
)paren
comma
DECL|enumerator|BIOSFibPath
id|BIOSFibPath
op_assign
(paren
l_int|1
op_lshift
l_int|18
)paren
comma
DECL|enumerator|FastResponseCapable
id|FastResponseCapable
op_assign
(paren
l_int|1
op_lshift
l_int|19
)paren
comma
DECL|enumerator|ApiFib
id|ApiFib
op_assign
(paren
l_int|1
op_lshift
l_int|20
)paren
singleline_comment|// Its an API Fib.
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;The following defines needs to be updated any time there is an&n; *&t;incompatible change made to the aac_init structure.&n; */
DECL|macro|ADAPTER_INIT_STRUCT_REVISION
mdefine_line|#define ADAPTER_INIT_STRUCT_REVISION&t;&t;3
DECL|struct|aac_init
r_struct
id|aac_init
(brace
DECL|member|InitStructRevision
id|u32
id|InitStructRevision
suffix:semicolon
DECL|member|MiniPortRevision
id|u32
id|MiniPortRevision
suffix:semicolon
DECL|member|fsrev
id|u32
id|fsrev
suffix:semicolon
DECL|member|CommHeaderAddress
id|u32
id|CommHeaderAddress
suffix:semicolon
DECL|member|FastIoCommAreaAddress
id|u32
id|FastIoCommAreaAddress
suffix:semicolon
DECL|member|AdapterFibsPhysicalAddress
id|u32
id|AdapterFibsPhysicalAddress
suffix:semicolon
DECL|member|AdapterFibsVirtualAddress
id|u32
id|AdapterFibsVirtualAddress
suffix:semicolon
DECL|member|AdapterFibsSize
id|u32
id|AdapterFibsSize
suffix:semicolon
DECL|member|AdapterFibAlign
id|u32
id|AdapterFibAlign
suffix:semicolon
DECL|member|printfbuf
id|u32
id|printfbuf
suffix:semicolon
DECL|member|printfbufsiz
id|u32
id|printfbufsiz
suffix:semicolon
DECL|member|HostPhysMemPages
id|u32
id|HostPhysMemPages
suffix:semicolon
singleline_comment|// number of 4k pages of host physical memory
DECL|member|HostElapsedSeconds
id|u32
id|HostElapsedSeconds
suffix:semicolon
singleline_comment|// number of seconds since 1970.
)brace
suffix:semicolon
DECL|enum|aac_log_level
r_enum
id|aac_log_level
(brace
DECL|enumerator|LOG_AAC_INIT
id|LOG_AAC_INIT
op_assign
l_int|10
comma
DECL|enumerator|LOG_AAC_INFORMATIONAL
id|LOG_AAC_INFORMATIONAL
op_assign
l_int|20
comma
DECL|enumerator|LOG_AAC_WARNING
id|LOG_AAC_WARNING
op_assign
l_int|30
comma
DECL|enumerator|LOG_AAC_LOW_ERROR
id|LOG_AAC_LOW_ERROR
op_assign
l_int|40
comma
DECL|enumerator|LOG_AAC_MEDIUM_ERROR
id|LOG_AAC_MEDIUM_ERROR
op_assign
l_int|50
comma
DECL|enumerator|LOG_AAC_HIGH_ERROR
id|LOG_AAC_HIGH_ERROR
op_assign
l_int|60
comma
DECL|enumerator|LOG_AAC_PANIC
id|LOG_AAC_PANIC
op_assign
l_int|70
comma
DECL|enumerator|LOG_AAC_DEBUG
id|LOG_AAC_DEBUG
op_assign
l_int|80
comma
DECL|enumerator|LOG_AAC_WINDBG_PRINT
id|LOG_AAC_WINDBG_PRINT
op_assign
l_int|90
)brace
suffix:semicolon
DECL|macro|FSAFS_NTC_GET_ADAPTER_FIB_CONTEXT
mdefine_line|#define FSAFS_NTC_GET_ADAPTER_FIB_CONTEXT&t;0x030b
DECL|macro|FSAFS_NTC_FIB_CONTEXT
mdefine_line|#define FSAFS_NTC_FIB_CONTEXT&t;&t;&t;0x030c
r_struct
id|aac_dev
suffix:semicolon
DECL|struct|adapter_ops
r_struct
id|adapter_ops
(brace
DECL|member|adapter_interrupt
r_void
(paren
op_star
id|adapter_interrupt
)paren
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|member|adapter_notify
r_void
(paren
op_star
id|adapter_notify
)paren
(paren
r_struct
id|aac_dev
op_star
id|dev
comma
id|u32
id|event
)paren
suffix:semicolon
DECL|member|adapter_sync_cmd
r_int
(paren
op_star
id|adapter_sync_cmd
)paren
(paren
r_struct
id|aac_dev
op_star
id|dev
comma
id|u32
id|command
comma
id|u32
id|p1
comma
id|u32
op_star
id|status
)paren
suffix:semicolon
DECL|member|adapter_check_health
r_int
(paren
op_star
id|adapter_check_health
)paren
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Define which interrupt handler needs to be installed&n; */
DECL|struct|aac_driver_ident
r_struct
id|aac_driver_ident
(brace
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|vname
r_char
op_star
id|vname
suffix:semicolon
DECL|member|model
r_char
op_star
id|model
suffix:semicolon
DECL|member|channels
id|u16
id|channels
suffix:semicolon
DECL|member|quirks
r_int
id|quirks
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Some adapter firmware needs communication memory &n; * below 2gig. This tells the init function to set the&n; * dma mask such that fib memory will be allocated where the&n; * adapter firmware can get to it.&n; */
DECL|macro|AAC_QUIRK_31BIT
mdefine_line|#define AAC_QUIRK_31BIT&t;1
multiline_comment|/*&n; *&t;The adapter interface specs all queues to be located in the same&n; *&t;physically contigous block. The host structure that defines the&n; *&t;commuication queues will assume they are each a separate physically&n; *&t;contigous memory region that will support them all being one big&n; *&t;contigous block. &n; *&t;There is a command and response queue for each level and direction of&n; *&t;commuication. These regions are accessed by both the host and adapter.&n; */
DECL|struct|aac_queue
r_struct
id|aac_queue
(brace
DECL|member|logical
id|u64
id|logical
suffix:semicolon
multiline_comment|/*address we give the adapter */
DECL|member|base
r_struct
id|aac_entry
op_star
id|base
suffix:semicolon
multiline_comment|/*system virtual address */
DECL|member|headers
r_struct
id|aac_qhdr
id|headers
suffix:semicolon
multiline_comment|/*producer,consumer q headers*/
DECL|member|entries
id|u32
id|entries
suffix:semicolon
multiline_comment|/*Number of queue entries */
DECL|member|qfull
id|wait_queue_head_t
id|qfull
suffix:semicolon
multiline_comment|/*Event to wait on if q full */
DECL|member|cmdready
id|wait_queue_head_t
id|cmdready
suffix:semicolon
multiline_comment|/*Cmd ready from the adapter */
multiline_comment|/* This is only valid for adapter to host command queues. */
DECL|member|lock
id|spinlock_t
op_star
id|lock
suffix:semicolon
multiline_comment|/* Spinlock for this queue must take this lock before accessing the lock */
DECL|member|lockdata
id|spinlock_t
id|lockdata
suffix:semicolon
multiline_comment|/* Actual lock (used only on one side of the lock) */
DECL|member|SavedIrql
r_int
r_int
id|SavedIrql
suffix:semicolon
multiline_comment|/* Previous IRQL when the spin lock is taken */
DECL|member|padding
id|u32
id|padding
suffix:semicolon
multiline_comment|/* Padding - FIXME - can remove I believe */
DECL|member|cmdq
r_struct
id|list_head
id|cmdq
suffix:semicolon
multiline_comment|/* A queue of FIBs which need to be prcessed by the FS thread. This is */
multiline_comment|/* only valid for command queues which receive entries from the adapter. */
DECL|member|pendingq
r_struct
id|list_head
id|pendingq
suffix:semicolon
multiline_comment|/* A queue of outstanding fib&squot;s to the adapter. */
DECL|member|numpending
id|u32
id|numpending
suffix:semicolon
multiline_comment|/* Number of entries on outstanding queue. */
DECL|member|dev
r_struct
id|aac_dev
op_star
id|dev
suffix:semicolon
multiline_comment|/* Back pointer to adapter structure */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Message queues. The order here is important, see also the &n; *&t;queue type ordering&n; */
DECL|struct|aac_queue_block
r_struct
id|aac_queue_block
(brace
DECL|member|queue
r_struct
id|aac_queue
id|queue
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;SaP1 Message Unit Registers&n; */
DECL|struct|sa_drawbridge_CSR
r_struct
id|sa_drawbridge_CSR
(brace
singleline_comment|//&t; Offset |&t;Name
DECL|member|reserved
id|u32
id|reserved
(braket
l_int|10
)braket
suffix:semicolon
singleline_comment|//&t;00h-27h |   Reserved
DECL|member|LUT_Offset
id|u8
id|LUT_Offset
suffix:semicolon
singleline_comment|//&t;28h&t;|&t;Looup Table Offset
DECL|member|reserved1
id|u8
id|reserved1
(braket
l_int|3
)braket
suffix:semicolon
singleline_comment|// &t;29h-2bh&t;|&t;Reserved
DECL|member|LUT_Data
id|u32
id|LUT_Data
suffix:semicolon
singleline_comment|//&t;2ch&t;|&t;Looup Table Data&t;
DECL|member|reserved2
id|u32
id|reserved2
(braket
l_int|26
)braket
suffix:semicolon
singleline_comment|//&t;30h-97h&t;|&t;Reserved
DECL|member|PRICLEARIRQ
id|u16
id|PRICLEARIRQ
suffix:semicolon
singleline_comment|//&t;98h&t;|&t;Primary Clear Irq
DECL|member|SECCLEARIRQ
id|u16
id|SECCLEARIRQ
suffix:semicolon
singleline_comment|//&t;9ah&t;|&t;Secondary Clear Irq
DECL|member|PRISETIRQ
id|u16
id|PRISETIRQ
suffix:semicolon
singleline_comment|//&t;9ch&t;|&t;Primary Set Irq
DECL|member|SECSETIRQ
id|u16
id|SECSETIRQ
suffix:semicolon
singleline_comment|//&t;9eh&t;|&t;Secondary Set Irq
DECL|member|PRICLEARIRQMASK
id|u16
id|PRICLEARIRQMASK
suffix:semicolon
singleline_comment|//&t;a0h&t;|&t;Primary Clear Irq Mask
DECL|member|SECCLEARIRQMASK
id|u16
id|SECCLEARIRQMASK
suffix:semicolon
singleline_comment|//&t;a2h&t;|&t;Secondary Clear Irq Mask
DECL|member|PRISETIRQMASK
id|u16
id|PRISETIRQMASK
suffix:semicolon
singleline_comment|//&t;a4h&t;|&t;Primary Set Irq Mask
DECL|member|SECSETIRQMASK
id|u16
id|SECSETIRQMASK
suffix:semicolon
singleline_comment|//&t;a6h&t;|&t;Secondary Set Irq Mask
DECL|member|MAILBOX0
id|u32
id|MAILBOX0
suffix:semicolon
singleline_comment|//&t;a8h&t;|&t;Scratchpad 0
DECL|member|MAILBOX1
id|u32
id|MAILBOX1
suffix:semicolon
singleline_comment|//&t;ach&t;|&t;Scratchpad 1
DECL|member|MAILBOX2
id|u32
id|MAILBOX2
suffix:semicolon
singleline_comment|//&t;b0h&t;|&t;Scratchpad 2
DECL|member|MAILBOX3
id|u32
id|MAILBOX3
suffix:semicolon
singleline_comment|//&t;b4h&t;|&t;Scratchpad 3
DECL|member|MAILBOX4
id|u32
id|MAILBOX4
suffix:semicolon
singleline_comment|//&t;b8h&t;|&t;Scratchpad 4
DECL|member|MAILBOX5
id|u32
id|MAILBOX5
suffix:semicolon
singleline_comment|//&t;bch&t;|&t;Scratchpad 5
DECL|member|MAILBOX6
id|u32
id|MAILBOX6
suffix:semicolon
singleline_comment|//&t;c0h&t;|&t;Scratchpad 6
DECL|member|MAILBOX7
id|u32
id|MAILBOX7
suffix:semicolon
singleline_comment|//&t;c4h&t;|&t;Scratchpad 7
DECL|member|ROM_Setup_Data
id|u32
id|ROM_Setup_Data
suffix:semicolon
singleline_comment|//&t;c8h | &t;Rom Setup and Data
DECL|member|ROM_Control_Addr
id|u32
id|ROM_Control_Addr
suffix:semicolon
singleline_comment|//&t;cch | &t;Rom Control and Address
DECL|member|reserved3
id|u32
id|reserved3
(braket
l_int|12
)braket
suffix:semicolon
singleline_comment|//&t;d0h-ffh&t;| &t;reserved
DECL|member|LUT
id|u32
id|LUT
(braket
l_int|64
)braket
suffix:semicolon
singleline_comment|// 100h-1ffh|&t;Lookup Table Entries
singleline_comment|//
singleline_comment|//  TO DO
singleline_comment|//&t;need to add DMA, I2O, UART, etc registers form 80h to 364h
singleline_comment|//
)brace
suffix:semicolon
DECL|macro|Mailbox0
mdefine_line|#define Mailbox0&t;SaDbCSR.MAILBOX0
DECL|macro|Mailbox1
mdefine_line|#define Mailbox1&t;SaDbCSR.MAILBOX1
DECL|macro|Mailbox2
mdefine_line|#define Mailbox2&t;SaDbCSR.MAILBOX2
DECL|macro|Mailbox3
mdefine_line|#define Mailbox3&t;SaDbCSR.MAILBOX3
DECL|macro|Mailbox4
mdefine_line|#define Mailbox4&t;SaDbCSR.MAILBOX4
DECL|macro|Mailbox5
mdefine_line|#define Mailbox5&t;SaDbCSR.MAILBOX5
DECL|macro|Mailbox7
mdefine_line|#define Mailbox7&t;SaDbCSR.MAILBOX7
DECL|macro|DoorbellReg_p
mdefine_line|#define DoorbellReg_p SaDbCSR.PRISETIRQ
DECL|macro|DoorbellReg_s
mdefine_line|#define DoorbellReg_s SaDbCSR.SECSETIRQ
DECL|macro|DoorbellClrReg_p
mdefine_line|#define DoorbellClrReg_p SaDbCSR.PRICLEARIRQ
DECL|macro|DOORBELL_0
mdefine_line|#define&t;DOORBELL_0&t;cpu_to_le16(0x0001)
DECL|macro|DOORBELL_1
mdefine_line|#define DOORBELL_1&t;cpu_to_le16(0x0002)
DECL|macro|DOORBELL_2
mdefine_line|#define DOORBELL_2&t;cpu_to_le16(0x0004)
DECL|macro|DOORBELL_3
mdefine_line|#define DOORBELL_3&t;cpu_to_le16(0x0008)
DECL|macro|DOORBELL_4
mdefine_line|#define DOORBELL_4&t;cpu_to_le16(0x0010)
DECL|macro|DOORBELL_5
mdefine_line|#define DOORBELL_5&t;cpu_to_le16(0x0020)
DECL|macro|DOORBELL_6
mdefine_line|#define DOORBELL_6&t;cpu_to_le16(0x0040)
DECL|macro|PrintfReady
mdefine_line|#define PrintfReady&t;DOORBELL_5
DECL|macro|PrintfDone
mdefine_line|#define PrintfDone&t;DOORBELL_5
DECL|struct|sa_registers
r_struct
id|sa_registers
(brace
DECL|member|SaDbCSR
r_struct
id|sa_drawbridge_CSR
id|SaDbCSR
suffix:semicolon
multiline_comment|/* 98h - c4h */
)brace
suffix:semicolon
DECL|macro|Sa_MINIPORT_REVISION
mdefine_line|#define Sa_MINIPORT_REVISION&t;&t;&t;1
DECL|macro|sa_readw
mdefine_line|#define sa_readw(AEP, CSR)&t;&t;readl(&amp;((AEP)-&gt;regs.sa-&gt;CSR))
DECL|macro|sa_readl
mdefine_line|#define sa_readl(AEP,  CSR)&t;&t;readl(&amp;((AEP)-&gt;regs.sa-&gt;CSR))
DECL|macro|sa_writew
mdefine_line|#define sa_writew(AEP, CSR, value)&t;writew(value, &amp;((AEP)-&gt;regs.sa-&gt;CSR))
DECL|macro|sa_writel
mdefine_line|#define sa_writel(AEP, CSR, value)&t;writel(value, &amp;((AEP)-&gt;regs.sa-&gt;CSR))
multiline_comment|/*&n; *&t;Rx Message Unit Registers&n; */
DECL|struct|rx_mu_registers
r_struct
id|rx_mu_registers
(brace
singleline_comment|//&t; Local&t;|   PCI*&t;|&t;Name
singleline_comment|//&t;&t;&t;|&t;&t;|
DECL|member|ARSR
id|u32
id|ARSR
suffix:semicolon
singleline_comment|//&t;1300h&t;|&t;00h&t;|&t;APIC Register Select Register
DECL|member|reserved0
id|u32
id|reserved0
suffix:semicolon
singleline_comment|//&t;1304h&t;|&t;04h&t;|&t;Reserved
DECL|member|AWR
id|u32
id|AWR
suffix:semicolon
singleline_comment|//&t;1308h&t;|&t;08h&t;|&t;APIC Window Register
DECL|member|reserved1
id|u32
id|reserved1
suffix:semicolon
singleline_comment|//&t;130Ch&t;|&t;0Ch&t;|&t;Reserved
DECL|member|IMRx
id|u32
id|IMRx
(braket
l_int|2
)braket
suffix:semicolon
singleline_comment|//&t;1310h&t;|&t;10h&t;|&t;Inbound Message Registers
DECL|member|OMRx
id|u32
id|OMRx
(braket
l_int|2
)braket
suffix:semicolon
singleline_comment|//&t;1318h&t;|&t;18h&t;|&t;Outbound Message Registers
DECL|member|IDR
id|u32
id|IDR
suffix:semicolon
singleline_comment|//&t;1320h&t;|&t;20h&t;|&t;Inbound Doorbell Register
DECL|member|IISR
id|u32
id|IISR
suffix:semicolon
singleline_comment|//&t;1324h&t;|&t;24h&t;|&t;Inbound Interrupt Status Register
DECL|member|IIMR
id|u32
id|IIMR
suffix:semicolon
singleline_comment|//&t;1328h&t;|&t;28h&t;|&t;Inbound Interrupt Mask Register
DECL|member|ODR
id|u32
id|ODR
suffix:semicolon
singleline_comment|//&t;132Ch&t;|&t;2Ch&t;|&t;Outbound Doorbell Register
DECL|member|OISR
id|u32
id|OISR
suffix:semicolon
singleline_comment|//&t;1330h&t;|&t;30h&t;|&t;Outbound Interrupt Status Register
DECL|member|OIMR
id|u32
id|OIMR
suffix:semicolon
singleline_comment|//&t;1334h&t;|&t;34h&t;|&t;Outbound Interrupt Mask Register
singleline_comment|// * Must access through ATU Inbound Translation Window
)brace
suffix:semicolon
DECL|struct|rx_inbound
r_struct
id|rx_inbound
(brace
DECL|member|Mailbox
id|u32
id|Mailbox
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|InboundMailbox0
mdefine_line|#define&t;InboundMailbox0&t;&t;IndexRegs.Mailbox[0]
DECL|macro|InboundMailbox1
mdefine_line|#define&t;InboundMailbox1&t;&t;IndexRegs.Mailbox[1]
DECL|macro|InboundMailbox2
mdefine_line|#define&t;InboundMailbox2&t;&t;IndexRegs.Mailbox[2]
DECL|macro|InboundMailbox3
mdefine_line|#define&t;InboundMailbox3&t;&t;IndexRegs.Mailbox[3]
DECL|macro|InboundMailbox4
mdefine_line|#define&t;InboundMailbox4&t;&t;IndexRegs.Mailbox[4]
DECL|macro|InboundMailbox5
mdefine_line|#define&t;InboundMailbox5&t;&t;IndexRegs.Mailbox[5]
DECL|macro|InboundMailbox6
mdefine_line|#define&t;InboundMailbox6&t;&t;IndexRegs.Mailbox[6]
DECL|macro|InboundMailbox7
mdefine_line|#define&t;InboundMailbox7&t;&t;IndexRegs.Mailbox[7]
DECL|macro|INBOUNDDOORBELL_0
mdefine_line|#define&t;INBOUNDDOORBELL_0&t;cpu_to_le32(0x00000001)
DECL|macro|INBOUNDDOORBELL_1
mdefine_line|#define INBOUNDDOORBELL_1&t;cpu_to_le32(0x00000002)
DECL|macro|INBOUNDDOORBELL_2
mdefine_line|#define INBOUNDDOORBELL_2&t;cpu_to_le32(0x00000004)
DECL|macro|INBOUNDDOORBELL_3
mdefine_line|#define INBOUNDDOORBELL_3&t;cpu_to_le32(0x00000008)
DECL|macro|INBOUNDDOORBELL_4
mdefine_line|#define INBOUNDDOORBELL_4&t;cpu_to_le32(0x00000010)
DECL|macro|INBOUNDDOORBELL_5
mdefine_line|#define INBOUNDDOORBELL_5&t;cpu_to_le32(0x00000020)
DECL|macro|INBOUNDDOORBELL_6
mdefine_line|#define INBOUNDDOORBELL_6&t;cpu_to_le32(0x00000040)
DECL|macro|OUTBOUNDDOORBELL_0
mdefine_line|#define&t;OUTBOUNDDOORBELL_0&t;cpu_to_le32(0x00000001)
DECL|macro|OUTBOUNDDOORBELL_1
mdefine_line|#define OUTBOUNDDOORBELL_1&t;cpu_to_le32(0x00000002)
DECL|macro|OUTBOUNDDOORBELL_2
mdefine_line|#define OUTBOUNDDOORBELL_2&t;cpu_to_le32(0x00000004)
DECL|macro|OUTBOUNDDOORBELL_3
mdefine_line|#define OUTBOUNDDOORBELL_3&t;cpu_to_le32(0x00000008)
DECL|macro|OUTBOUNDDOORBELL_4
mdefine_line|#define OUTBOUNDDOORBELL_4&t;cpu_to_le32(0x00000010)
DECL|macro|InboundDoorbellReg
mdefine_line|#define InboundDoorbellReg&t;MUnit.IDR
DECL|macro|OutboundDoorbellReg
mdefine_line|#define OutboundDoorbellReg&t;MUnit.ODR
DECL|struct|rx_registers
r_struct
id|rx_registers
(brace
DECL|member|MUnit
r_struct
id|rx_mu_registers
id|MUnit
suffix:semicolon
singleline_comment|// 1300h - 1334h
DECL|member|reserved1
id|u32
id|reserved1
(braket
l_int|6
)braket
suffix:semicolon
singleline_comment|// 1338h - 134ch
DECL|member|IndexRegs
r_struct
id|rx_inbound
id|IndexRegs
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|rx_readb
mdefine_line|#define rx_readb(AEP, CSR)&t;&t;readb(&amp;((AEP)-&gt;regs.rx-&gt;CSR))
DECL|macro|rx_readl
mdefine_line|#define rx_readl(AEP, CSR)&t;&t;readl(&amp;((AEP)-&gt;regs.rx-&gt;CSR))
DECL|macro|rx_writeb
mdefine_line|#define rx_writeb(AEP, CSR, value)&t;writeb(value, &amp;((AEP)-&gt;regs.rx-&gt;CSR))
DECL|macro|rx_writel
mdefine_line|#define rx_writel(AEP, CSR, value)&t;writel(value, &amp;((AEP)-&gt;regs.rx-&gt;CSR))
multiline_comment|/*&n; *&t;Rkt Message Unit Registers (same as Rx, except a larger reserve region)&n; */
DECL|macro|rkt_mu_registers
mdefine_line|#define rkt_mu_registers rx_mu_registers
DECL|macro|rkt_inbound
mdefine_line|#define rkt_inbound rx_inbound
DECL|struct|rkt_registers
r_struct
id|rkt_registers
(brace
DECL|member|MUnit
r_struct
id|rkt_mu_registers
id|MUnit
suffix:semicolon
multiline_comment|/* 1300h - 1334h */
DECL|member|reserved1
id|u32
id|reserved1
(braket
l_int|1010
)braket
suffix:semicolon
multiline_comment|/* 1338h - 22fch */
DECL|member|IndexRegs
r_struct
id|rkt_inbound
id|IndexRegs
suffix:semicolon
multiline_comment|/* 2300h - */
)brace
suffix:semicolon
DECL|macro|rkt_readb
mdefine_line|#define rkt_readb(AEP, CSR)&t;&t;readb(&amp;((AEP)-&gt;regs.rkt-&gt;CSR))
DECL|macro|rkt_readl
mdefine_line|#define rkt_readl(AEP, CSR)&t;&t;readl(&amp;((AEP)-&gt;regs.rkt-&gt;CSR))
DECL|macro|rkt_writeb
mdefine_line|#define rkt_writeb(AEP, CSR, value)&t;writeb(value, &amp;((AEP)-&gt;regs.rkt-&gt;CSR))
DECL|macro|rkt_writel
mdefine_line|#define rkt_writel(AEP, CSR, value)&t;writel(value, &amp;((AEP)-&gt;regs.rkt-&gt;CSR))
r_struct
id|fib
suffix:semicolon
DECL|typedef|fib_callback
r_typedef
r_void
(paren
op_star
id|fib_callback
)paren
(paren
r_void
op_star
id|ctxt
comma
r_struct
id|fib
op_star
id|fibctx
)paren
suffix:semicolon
DECL|struct|aac_fib_context
r_struct
id|aac_fib_context
(brace
DECL|member|type
id|s16
id|type
suffix:semicolon
singleline_comment|// used for verification of structure&t;
DECL|member|size
id|s16
id|size
suffix:semicolon
DECL|member|unique
id|u32
id|unique
suffix:semicolon
singleline_comment|// unique value representing this context
DECL|member|jiffies
id|ulong
id|jiffies
suffix:semicolon
singleline_comment|// used for cleanup - dmb changed to ulong
DECL|member|next
r_struct
id|list_head
id|next
suffix:semicolon
singleline_comment|// used to link context&squot;s into a linked list
DECL|member|wait_sem
r_struct
id|semaphore
id|wait_sem
suffix:semicolon
singleline_comment|// this is used to wait for the next fib to arrive.
DECL|member|wait
r_int
id|wait
suffix:semicolon
singleline_comment|// Set to true when thread is in WaitForSingleObject
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
singleline_comment|// total number of FIBs on FibList
DECL|member|fib_list
r_struct
id|list_head
id|fib_list
suffix:semicolon
singleline_comment|// this holds fibs and their attachd hw_fibs
)brace
suffix:semicolon
DECL|struct|sense_data
r_struct
id|sense_data
(brace
DECL|member|error_code
id|u8
id|error_code
suffix:semicolon
multiline_comment|/* 70h (current errors), 71h(deferred errors) */
DECL|member|valid
id|u8
id|valid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A valid bit of one indicates that the information  */
multiline_comment|/* field contains valid information as defined in the&n;&t;&t;&t;&t; * SCSI-2 Standard.&n;&t;&t;&t;&t; */
DECL|member|segment_number
id|u8
id|segment_number
suffix:semicolon
multiline_comment|/* Only used for COPY, COMPARE, or COPY AND VERIFY Commands */
DECL|member|sense_key
id|u8
id|sense_key
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Sense Key */
DECL|member|reserved
id|u8
id|reserved
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ILI
id|u8
id|ILI
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Incorrect Length Indicator */
DECL|member|EOM
id|u8
id|EOM
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* End Of Medium - reserved for random access devices */
DECL|member|filemark
id|u8
id|filemark
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Filemark - reserved for random access devices */
DECL|member|information
id|u8
id|information
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* for direct-access devices, contains the unsigned &n;&t;&t;&t;&t; * logical block address or residue associated with &n;&t;&t;&t;&t; * the sense key &n;&t;&t;&t;&t; */
DECL|member|add_sense_len
id|u8
id|add_sense_len
suffix:semicolon
multiline_comment|/* number of additional sense bytes to follow this field */
DECL|member|cmnd_info
id|u8
id|cmnd_info
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* not used */
DECL|member|ASC
id|u8
id|ASC
suffix:semicolon
multiline_comment|/* Additional Sense Code */
DECL|member|ASCQ
id|u8
id|ASCQ
suffix:semicolon
multiline_comment|/* Additional Sense Code Qualifier */
DECL|member|FRUC
id|u8
id|FRUC
suffix:semicolon
multiline_comment|/* Field Replaceable Unit Code - not used */
DECL|member|bit_ptr
id|u8
id|bit_ptr
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* indicates which byte of the CDB or parameter data&n;&t;&t;&t;&t; * was in error&n;&t;&t;&t;&t; */
DECL|member|BPV
id|u8
id|BPV
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* bit pointer valid (BPV): 1- indicates that &n;&t;&t;&t;&t; * the bit_ptr field has valid value&n;&t;&t;&t;&t; */
DECL|member|reserved2
id|u8
id|reserved2
suffix:colon
l_int|2
suffix:semicolon
DECL|member|CD
id|u8
id|CD
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* command data bit: 1- illegal parameter in CDB.&n;&t;&t;&t;&t; * 0- illegal parameter in data.&n;&t;&t;&t;&t; */
DECL|member|SKSV
id|u8
id|SKSV
suffix:colon
l_int|1
suffix:semicolon
DECL|member|field_ptr
id|u8
id|field_ptr
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* byte of the CDB or parameter data in error */
)brace
suffix:semicolon
DECL|struct|fsa_dev_info
r_struct
id|fsa_dev_info
(brace
DECL|member|last
id|u64
id|last
suffix:semicolon
DECL|member|size
id|u64
id|size
suffix:semicolon
DECL|member|type
id|u32
id|type
suffix:semicolon
DECL|member|queue_depth
id|u16
id|queue_depth
suffix:semicolon
DECL|member|valid
id|u8
id|valid
suffix:semicolon
DECL|member|ro
id|u8
id|ro
suffix:semicolon
DECL|member|locked
id|u8
id|locked
suffix:semicolon
DECL|member|deleted
id|u8
id|deleted
suffix:semicolon
DECL|member|devname
r_char
id|devname
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|sense_data
r_struct
id|sense_data
id|sense_data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fib
r_struct
id|fib
(brace
DECL|member|next
r_void
op_star
id|next
suffix:semicolon
multiline_comment|/* this is used by the allocator */
DECL|member|type
id|s16
id|type
suffix:semicolon
DECL|member|size
id|s16
id|size
suffix:semicolon
multiline_comment|/*&n;&t; *&t;The Adapter that this I/O is destined for.&n;&t; */
DECL|member|dev
r_struct
id|aac_dev
op_star
id|dev
suffix:semicolon
multiline_comment|/*&n;&t; *&t;This is the event the sendfib routine will wait on if the&n;&t; *&t;caller did not pass one and this is synch io.&n;&t; */
DECL|member|event_wait
r_struct
id|semaphore
id|event_wait
suffix:semicolon
DECL|member|event_lock
id|spinlock_t
id|event_lock
suffix:semicolon
DECL|member|done
id|u32
id|done
suffix:semicolon
multiline_comment|/* gets set to 1 when fib is complete */
DECL|member|callback
id|fib_callback
id|callback
suffix:semicolon
DECL|member|callback_data
r_void
op_star
id|callback_data
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
singleline_comment|// u32 dmb was ulong
multiline_comment|/*&n;&t; *&t;The following is used to put this fib context onto the &n;&t; *&t;Outstanding I/O queue.&n;&t; */
DECL|member|queue
r_struct
id|list_head
id|queue
suffix:semicolon
multiline_comment|/*&n;&t; *&t;And for the internal issue/reply queues (we may be able&n;&t; *&t;to merge these two)&n;&t; */
DECL|member|fiblink
r_struct
id|list_head
id|fiblink
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|hw_fib
r_struct
id|hw_fib
op_star
id|hw_fib
suffix:semicolon
multiline_comment|/* Actual shared object */
DECL|member|hw_fib_pa
id|dma_addr_t
id|hw_fib_pa
suffix:semicolon
multiline_comment|/* physical address of hw_fib*/
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Adapter Information Block&n; *&n; *&t;This is returned by the RequestAdapterInfo block&n; */
DECL|struct|aac_adapter_info
r_struct
id|aac_adapter_info
(brace
DECL|member|platform
id|u32
id|platform
suffix:semicolon
DECL|member|cpu
id|u32
id|cpu
suffix:semicolon
DECL|member|subcpu
id|u32
id|subcpu
suffix:semicolon
DECL|member|clock
id|u32
id|clock
suffix:semicolon
DECL|member|execmem
id|u32
id|execmem
suffix:semicolon
DECL|member|buffermem
id|u32
id|buffermem
suffix:semicolon
DECL|member|totalmem
id|u32
id|totalmem
suffix:semicolon
DECL|member|kernelrev
id|u32
id|kernelrev
suffix:semicolon
DECL|member|kernelbuild
id|u32
id|kernelbuild
suffix:semicolon
DECL|member|monitorrev
id|u32
id|monitorrev
suffix:semicolon
DECL|member|monitorbuild
id|u32
id|monitorbuild
suffix:semicolon
DECL|member|hwrev
id|u32
id|hwrev
suffix:semicolon
DECL|member|hwbuild
id|u32
id|hwbuild
suffix:semicolon
DECL|member|biosrev
id|u32
id|biosrev
suffix:semicolon
DECL|member|biosbuild
id|u32
id|biosbuild
suffix:semicolon
DECL|member|cluster
id|u32
id|cluster
suffix:semicolon
DECL|member|clusterchannelmask
id|u32
id|clusterchannelmask
suffix:semicolon
DECL|member|serial
id|u32
id|serial
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|battery
id|u32
id|battery
suffix:semicolon
DECL|member|options
id|u32
id|options
suffix:semicolon
DECL|member|OEM
id|u32
id|OEM
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Battery platforms&n; */
DECL|macro|AAC_BAT_REQ_PRESENT
mdefine_line|#define AAC_BAT_REQ_PRESENT&t;(1)
DECL|macro|AAC_BAT_REQ_NOTPRESENT
mdefine_line|#define AAC_BAT_REQ_NOTPRESENT&t;(2)
DECL|macro|AAC_BAT_OPT_PRESENT
mdefine_line|#define AAC_BAT_OPT_PRESENT&t;(3)
DECL|macro|AAC_BAT_OPT_NOTPRESENT
mdefine_line|#define AAC_BAT_OPT_NOTPRESENT&t;(4)
DECL|macro|AAC_BAT_NOT_SUPPORTED
mdefine_line|#define AAC_BAT_NOT_SUPPORTED&t;(5)
multiline_comment|/*&n; * cpu types&n; */
DECL|macro|AAC_CPU_SIMULATOR
mdefine_line|#define AAC_CPU_SIMULATOR&t;(1)
DECL|macro|AAC_CPU_I960
mdefine_line|#define AAC_CPU_I960&t;&t;(2)
DECL|macro|AAC_CPU_STRONGARM
mdefine_line|#define AAC_CPU_STRONGARM&t;(3)
multiline_comment|/*&n; * Supported Options&n; */
DECL|macro|AAC_OPT_SNAPSHOT
mdefine_line|#define AAC_OPT_SNAPSHOT&t;&t;cpu_to_le32(1)
DECL|macro|AAC_OPT_CLUSTERS
mdefine_line|#define AAC_OPT_CLUSTERS&t;&t;cpu_to_le32(1&lt;&lt;1)
DECL|macro|AAC_OPT_WRITE_CACHE
mdefine_line|#define AAC_OPT_WRITE_CACHE&t;&t;cpu_to_le32(1&lt;&lt;2)
DECL|macro|AAC_OPT_64BIT_DATA
mdefine_line|#define AAC_OPT_64BIT_DATA&t;&t;cpu_to_le32(1&lt;&lt;3)
DECL|macro|AAC_OPT_HOST_TIME_FIB
mdefine_line|#define AAC_OPT_HOST_TIME_FIB&t;&t;cpu_to_le32(1&lt;&lt;4)
DECL|macro|AAC_OPT_RAID50
mdefine_line|#define AAC_OPT_RAID50&t;&t;&t;cpu_to_le32(1&lt;&lt;5)
DECL|macro|AAC_OPT_4GB_WINDOW
mdefine_line|#define AAC_OPT_4GB_WINDOW&t;&t;cpu_to_le32(1&lt;&lt;6)
DECL|macro|AAC_OPT_SCSI_UPGRADEABLE
mdefine_line|#define AAC_OPT_SCSI_UPGRADEABLE &t;cpu_to_le32(1&lt;&lt;7)
DECL|macro|AAC_OPT_SOFT_ERR_REPORT
mdefine_line|#define AAC_OPT_SOFT_ERR_REPORT&t;&t;cpu_to_le32(1&lt;&lt;8)
DECL|macro|AAC_OPT_SUPPORTED_RECONDITION
mdefine_line|#define AAC_OPT_SUPPORTED_RECONDITION &t;cpu_to_le32(1&lt;&lt;9)
DECL|macro|AAC_OPT_SGMAP_HOST64
mdefine_line|#define AAC_OPT_SGMAP_HOST64&t;&t;cpu_to_le32(1&lt;&lt;10)
DECL|macro|AAC_OPT_ALARM
mdefine_line|#define AAC_OPT_ALARM&t;&t;&t;cpu_to_le32(1&lt;&lt;11)
DECL|macro|AAC_OPT_NONDASD
mdefine_line|#define AAC_OPT_NONDASD&t;&t;&t;cpu_to_le32(1&lt;&lt;12)
DECL|struct|aac_dev
r_struct
id|aac_dev
(brace
DECL|member|entry
r_struct
id|list_head
id|entry
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|irq_mask
id|u16
id|irq_mask
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Map for 128 fib objects (64k)&n;&t; */
DECL|member|hw_fib_pa
id|dma_addr_t
id|hw_fib_pa
suffix:semicolon
DECL|member|hw_fib_va
r_struct
id|hw_fib
op_star
id|hw_fib_va
suffix:semicolon
DECL|member|aif_base_va
r_struct
id|hw_fib
op_star
id|aif_base_va
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Fib Headers&n;&t; */
DECL|member|fibs
r_struct
id|fib
op_star
id|fibs
suffix:semicolon
DECL|member|free_fib
r_struct
id|fib
op_star
id|free_fib
suffix:semicolon
DECL|member|timeout_fib
r_struct
id|fib
op_star
id|timeout_fib
suffix:semicolon
DECL|member|fib_lock
id|spinlock_t
id|fib_lock
suffix:semicolon
DECL|member|queues
r_struct
id|aac_queue_block
op_star
id|queues
suffix:semicolon
multiline_comment|/*&n;&t; *&t;The user API will use an IOCTL to register itself to receive&n;&t; *&t;FIBs from the adapter.  The following list is used to keep&n;&t; *&t;track of all the threads that have requested these FIBs.  The&n;&t; *&t;mutex is used to synchronize access to all data associated &n;&t; *&t;with the adapter fibs.&n;&t; */
DECL|member|fib_list
r_struct
id|list_head
id|fib_list
suffix:semicolon
DECL|member|a_ops
r_struct
id|adapter_ops
id|a_ops
suffix:semicolon
DECL|member|fsrev
r_int
r_int
id|fsrev
suffix:semicolon
multiline_comment|/* Main driver&squot;s revision number */
DECL|member|init
r_struct
id|aac_init
op_star
id|init
suffix:semicolon
multiline_comment|/* Holds initialization info to communicate with adapter */
DECL|member|init_pa
id|dma_addr_t
id|init_pa
suffix:semicolon
multiline_comment|/* Holds physical address of the init struct */
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
multiline_comment|/* Our PCI interface */
DECL|member|printfbuf
r_void
op_star
id|printfbuf
suffix:semicolon
multiline_comment|/* pointer to buffer used for printf&squot;s from the adapter */
DECL|member|comm_addr
r_void
op_star
id|comm_addr
suffix:semicolon
multiline_comment|/* Base address of Comm area */
DECL|member|comm_phys
id|dma_addr_t
id|comm_phys
suffix:semicolon
multiline_comment|/* Physical Address of Comm area */
DECL|member|comm_size
r_int
id|comm_size
suffix:semicolon
DECL|member|scsi_host_ptr
r_struct
id|Scsi_Host
op_star
id|scsi_host_ptr
suffix:semicolon
DECL|member|maximum_num_containers
r_int
id|maximum_num_containers
suffix:semicolon
DECL|member|fsa_dev
r_struct
id|fsa_dev_info
op_star
id|fsa_dev
suffix:semicolon
DECL|member|thread_pid
id|pid_t
id|thread_pid
suffix:semicolon
DECL|member|cardtype
r_int
id|cardtype
suffix:semicolon
multiline_comment|/*&n;&t; *&t;The following is the device specific extension.&n;&t; */
r_union
(brace
DECL|member|sa
r_struct
id|sa_registers
id|__iomem
op_star
id|sa
suffix:semicolon
DECL|member|rx
r_struct
id|rx_registers
id|__iomem
op_star
id|rx
suffix:semicolon
DECL|member|rkt
r_struct
id|rkt_registers
id|__iomem
op_star
id|rkt
suffix:semicolon
DECL|member|regs
)brace
id|regs
suffix:semicolon
DECL|member|OIMR
id|u32
id|OIMR
suffix:semicolon
multiline_comment|/* Mask Register Cache */
multiline_comment|/*&n;&t; *&t;AIF thread states&n;&t; */
DECL|member|aif_thread
id|u32
id|aif_thread
suffix:semicolon
DECL|member|aif_completion
r_struct
id|completion
id|aif_completion
suffix:semicolon
DECL|member|adapter_info
r_struct
id|aac_adapter_info
id|adapter_info
suffix:semicolon
multiline_comment|/* These are in adapter info but they are in the io flow so&n;&t; * lets break them out so we don&squot;t have to do an AND to check them&n;&t; */
DECL|member|nondasd_support
id|u8
id|nondasd_support
suffix:semicolon
DECL|member|dac_support
id|u8
id|dac_support
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|aac_adapter_interrupt
mdefine_line|#define aac_adapter_interrupt(dev) &bslash;&n;&t;(dev)-&gt;a_ops.adapter_interrupt(dev)
DECL|macro|aac_adapter_notify
mdefine_line|#define aac_adapter_notify(dev, event) &bslash;&n;&t;(dev)-&gt;a_ops.adapter_notify(dev, event)
DECL|macro|aac_adapter_check_health
mdefine_line|#define aac_adapter_check_health(dev) &bslash;&n;&t;(dev)-&gt;a_ops.adapter_check_health(dev)
DECL|macro|FIB_CONTEXT_FLAG_TIMED_OUT
mdefine_line|#define FIB_CONTEXT_FLAG_TIMED_OUT&t;&t;(0x00000001)
multiline_comment|/*&n; *&t;Define the command values&n; */
DECL|macro|Null
mdefine_line|#define&t;&t;Null&t;&t;&t;0
DECL|macro|GetAttributes
mdefine_line|#define &t;GetAttributes&t;&t;1
DECL|macro|SetAttributes
mdefine_line|#define &t;SetAttributes&t;&t;2
DECL|macro|Lookup
mdefine_line|#define &t;Lookup&t;&t;&t;3
DECL|macro|ReadLink
mdefine_line|#define &t;ReadLink&t;&t;4
DECL|macro|Read
mdefine_line|#define &t;Read&t;&t;&t;5
DECL|macro|Write
mdefine_line|#define &t;Write&t;&t;&t;6
DECL|macro|Create
mdefine_line|#define&t;&t;Create&t;&t;&t;7
DECL|macro|MakeDirectory
mdefine_line|#define&t;&t;MakeDirectory&t;&t;8
DECL|macro|SymbolicLink
mdefine_line|#define&t;&t;SymbolicLink&t;&t;9
DECL|macro|MakeNode
mdefine_line|#define&t;&t;MakeNode&t;&t;10
DECL|macro|Removex
mdefine_line|#define&t;&t;Removex&t;&t;&t;11
DECL|macro|RemoveDirectoryx
mdefine_line|#define&t;&t;RemoveDirectoryx&t;12
DECL|macro|Rename
mdefine_line|#define&t;&t;Rename&t;&t;&t;13
DECL|macro|Link
mdefine_line|#define&t;&t;Link&t;&t;&t;14
DECL|macro|ReadDirectory
mdefine_line|#define&t;&t;ReadDirectory&t;&t;15
DECL|macro|ReadDirectoryPlus
mdefine_line|#define&t;&t;ReadDirectoryPlus&t;16
DECL|macro|FileSystemStatus
mdefine_line|#define&t;&t;FileSystemStatus&t;17
DECL|macro|FileSystemInfo
mdefine_line|#define&t;&t;FileSystemInfo&t;&t;18
DECL|macro|PathConfigure
mdefine_line|#define&t;&t;PathConfigure&t;&t;19
DECL|macro|Commit
mdefine_line|#define&t;&t;Commit&t;&t;&t;20
DECL|macro|Mount
mdefine_line|#define&t;&t;Mount&t;&t;&t;21
DECL|macro|UnMount
mdefine_line|#define&t;&t;UnMount&t;&t;&t;22
DECL|macro|Newfs
mdefine_line|#define&t;&t;Newfs&t;&t;&t;23
DECL|macro|FsCheck
mdefine_line|#define&t;&t;FsCheck&t;&t;&t;24
DECL|macro|FsSync
mdefine_line|#define&t;&t;FsSync&t;&t;&t;25
DECL|macro|SimReadWrite
mdefine_line|#define&t;&t;SimReadWrite&t;&t;26
DECL|macro|SetFileSystemStatus
mdefine_line|#define&t;&t;SetFileSystemStatus&t;27
DECL|macro|BlockRead
mdefine_line|#define&t;&t;BlockRead&t;&t;28
DECL|macro|BlockWrite
mdefine_line|#define&t;&t;BlockWrite&t;&t;29
DECL|macro|NvramIoctl
mdefine_line|#define&t;&t;NvramIoctl&t;&t;30
DECL|macro|FsSyncWait
mdefine_line|#define&t;&t;FsSyncWait&t;&t;31
DECL|macro|ClearArchiveBit
mdefine_line|#define&t;&t;ClearArchiveBit&t;&t;32
DECL|macro|SetAcl
mdefine_line|#define&t;&t;SetAcl&t;&t;&t;33
DECL|macro|GetAcl
mdefine_line|#define&t;&t;GetAcl&t;&t;&t;34
DECL|macro|AssignAcl
mdefine_line|#define&t;&t;AssignAcl&t;&t;35
DECL|macro|FaultInsertion
mdefine_line|#define&t;&t;FaultInsertion&t;&t;36&t;/* Fault Insertion Command */
DECL|macro|CrazyCache
mdefine_line|#define&t;&t;CrazyCache&t;&t;37&t;/* Crazycache */
DECL|macro|MAX_FSACOMMAND_NUM
mdefine_line|#define&t;&t;MAX_FSACOMMAND_NUM&t;38
multiline_comment|/*&n; *&t;Define the status returns. These are very unixlike although&n; *&t;most are not in fact used&n; */
DECL|macro|ST_OK
mdefine_line|#define&t;&t;ST_OK&t;&t;0
DECL|macro|ST_PERM
mdefine_line|#define&t;&t;ST_PERM&t;&t;1
DECL|macro|ST_NOENT
mdefine_line|#define&t;&t;ST_NOENT&t;2
DECL|macro|ST_IO
mdefine_line|#define&t;&t;ST_IO&t;&t;5
DECL|macro|ST_NXIO
mdefine_line|#define&t;&t;ST_NXIO&t;&t;6
DECL|macro|ST_E2BIG
mdefine_line|#define&t;&t;ST_E2BIG&t;7
DECL|macro|ST_ACCES
mdefine_line|#define&t;&t;ST_ACCES&t;13
DECL|macro|ST_EXIST
mdefine_line|#define&t;&t;ST_EXIST&t;17
DECL|macro|ST_XDEV
mdefine_line|#define&t;&t;ST_XDEV&t;&t;18
DECL|macro|ST_NODEV
mdefine_line|#define&t;&t;ST_NODEV&t;19
DECL|macro|ST_NOTDIR
mdefine_line|#define&t;&t;ST_NOTDIR&t;20
DECL|macro|ST_ISDIR
mdefine_line|#define&t;&t;ST_ISDIR&t;21
DECL|macro|ST_INVAL
mdefine_line|#define&t;&t;ST_INVAL&t;22
DECL|macro|ST_FBIG
mdefine_line|#define&t;&t;ST_FBIG&t;&t;27
DECL|macro|ST_NOSPC
mdefine_line|#define&t;&t;ST_NOSPC&t;28
DECL|macro|ST_ROFS
mdefine_line|#define&t;&t;ST_ROFS&t;&t;30
DECL|macro|ST_MLINK
mdefine_line|#define&t;&t;ST_MLINK&t;31
DECL|macro|ST_WOULDBLOCK
mdefine_line|#define&t;&t;ST_WOULDBLOCK&t;35
DECL|macro|ST_NAMETOOLONG
mdefine_line|#define&t;&t;ST_NAMETOOLONG&t;63
DECL|macro|ST_NOTEMPTY
mdefine_line|#define&t;&t;ST_NOTEMPTY&t;66
DECL|macro|ST_DQUOT
mdefine_line|#define&t;&t;ST_DQUOT&t;69
DECL|macro|ST_STALE
mdefine_line|#define&t;&t;ST_STALE&t;70
DECL|macro|ST_REMOTE
mdefine_line|#define&t;&t;ST_REMOTE&t;71
DECL|macro|ST_BADHANDLE
mdefine_line|#define&t;&t;ST_BADHANDLE&t;10001
DECL|macro|ST_NOT_SYNC
mdefine_line|#define&t;&t;ST_NOT_SYNC&t;10002
DECL|macro|ST_BAD_COOKIE
mdefine_line|#define&t;&t;ST_BAD_COOKIE&t;10003
DECL|macro|ST_NOTSUPP
mdefine_line|#define&t;&t;ST_NOTSUPP&t;10004
DECL|macro|ST_TOOSMALL
mdefine_line|#define&t;&t;ST_TOOSMALL&t;10005
DECL|macro|ST_SERVERFAULT
mdefine_line|#define&t;&t;ST_SERVERFAULT&t;10006
DECL|macro|ST_BADTYPE
mdefine_line|#define&t;&t;ST_BADTYPE&t;10007
DECL|macro|ST_JUKEBOX
mdefine_line|#define&t;&t;ST_JUKEBOX&t;10008
DECL|macro|ST_NOTMOUNTED
mdefine_line|#define&t;&t;ST_NOTMOUNTED&t;10009
DECL|macro|ST_MAINTMODE
mdefine_line|#define&t;&t;ST_MAINTMODE&t;10010
DECL|macro|ST_STALEACL
mdefine_line|#define&t;&t;ST_STALEACL&t;10011
multiline_comment|/*&n; *&t;On writes how does the client want the data written.&n; */
DECL|macro|CACHE_CSTABLE
mdefine_line|#define&t;CACHE_CSTABLE&t;&t;1
DECL|macro|CACHE_UNSTABLE
mdefine_line|#define CACHE_UNSTABLE&t;&t;2
multiline_comment|/*&n; *&t;Lets the client know at which level the data was commited on&n; *&t;a write request&n; */
DECL|macro|CMFILE_SYNCH_NVRAM
mdefine_line|#define&t;CMFILE_SYNCH_NVRAM&t;1
DECL|macro|CMDATA_SYNCH_NVRAM
mdefine_line|#define&t;CMDATA_SYNCH_NVRAM&t;2
DECL|macro|CMFILE_SYNCH
mdefine_line|#define&t;CMFILE_SYNCH&t;&t;3
DECL|macro|CMDATA_SYNCH
mdefine_line|#define CMDATA_SYNCH&t;&t;4
DECL|macro|CMUNSTABLE
mdefine_line|#define CMUNSTABLE&t;&t;5
DECL|struct|aac_read
r_struct
id|aac_read
(brace
DECL|member|command
id|u32
id|command
suffix:semicolon
DECL|member|cid
id|u32
id|cid
suffix:semicolon
DECL|member|block
id|u32
id|block
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|sg
r_struct
id|sgmap
id|sg
suffix:semicolon
singleline_comment|// Must be last in struct because it is variable
)brace
suffix:semicolon
DECL|struct|aac_read64
r_struct
id|aac_read64
(brace
DECL|member|command
id|u32
id|command
suffix:semicolon
DECL|member|cid
id|u16
id|cid
suffix:semicolon
DECL|member|sector_count
id|u16
id|sector_count
suffix:semicolon
DECL|member|block
id|u32
id|block
suffix:semicolon
DECL|member|pad
id|u16
id|pad
suffix:semicolon
DECL|member|flags
id|u16
id|flags
suffix:semicolon
DECL|member|sg
r_struct
id|sgmap64
id|sg
suffix:semicolon
singleline_comment|// Must be last in struct because it is variable
)brace
suffix:semicolon
DECL|struct|aac_read_reply
r_struct
id|aac_read_reply
(brace
DECL|member|status
id|u32
id|status
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aac_write
r_struct
id|aac_write
(brace
DECL|member|command
id|u32
id|command
suffix:semicolon
DECL|member|cid
id|u32
id|cid
suffix:semicolon
DECL|member|block
id|u32
id|block
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|stable
id|u32
id|stable
suffix:semicolon
singleline_comment|// Not used
DECL|member|sg
r_struct
id|sgmap
id|sg
suffix:semicolon
singleline_comment|// Must be last in struct because it is variable
)brace
suffix:semicolon
DECL|struct|aac_write64
r_struct
id|aac_write64
(brace
DECL|member|command
id|u32
id|command
suffix:semicolon
DECL|member|cid
id|u16
id|cid
suffix:semicolon
DECL|member|sector_count
id|u16
id|sector_count
suffix:semicolon
DECL|member|block
id|u32
id|block
suffix:semicolon
DECL|member|pad
id|u16
id|pad
suffix:semicolon
DECL|member|flags
id|u16
id|flags
suffix:semicolon
DECL|member|sg
r_struct
id|sgmap64
id|sg
suffix:semicolon
singleline_comment|// Must be last in struct because it is variable
)brace
suffix:semicolon
DECL|struct|aac_write_reply
r_struct
id|aac_write_reply
(brace
DECL|member|status
id|u32
id|status
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|committed
id|u32
id|committed
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aac_srb
r_struct
id|aac_srb
(brace
DECL|member|function
id|u32
id|function
suffix:semicolon
DECL|member|channel
id|u32
id|channel
suffix:semicolon
DECL|member|id
id|u32
id|id
suffix:semicolon
DECL|member|lun
id|u32
id|lun
suffix:semicolon
DECL|member|timeout
id|u32
id|timeout
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
singleline_comment|// Data xfer size
DECL|member|retry_limit
id|u32
id|retry_limit
suffix:semicolon
DECL|member|cdb_size
id|u32
id|cdb_size
suffix:semicolon
DECL|member|cdb
id|u8
id|cdb
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|sg
r_struct
id|sgmap
id|sg
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|AAC_SENSE_BUFFERSIZE
mdefine_line|#define&t;&t;AAC_SENSE_BUFFERSIZE&t; 30
DECL|struct|aac_srb_reply
r_struct
id|aac_srb_reply
(brace
DECL|member|status
id|u32
id|status
suffix:semicolon
DECL|member|srb_status
id|u32
id|srb_status
suffix:semicolon
DECL|member|scsi_status
id|u32
id|scsi_status
suffix:semicolon
DECL|member|data_xfer_length
id|u32
id|data_xfer_length
suffix:semicolon
DECL|member|sense_data_size
id|u32
id|sense_data_size
suffix:semicolon
DECL|member|sense_data
id|u8
id|sense_data
(braket
id|AAC_SENSE_BUFFERSIZE
)braket
suffix:semicolon
singleline_comment|// Can this be SCSI_SENSE_BUFFERSIZE
)brace
suffix:semicolon
multiline_comment|/*&n; * SRB Flags&n; */
DECL|macro|SRB_NoDataXfer
mdefine_line|#define&t;&t;SRB_NoDataXfer&t;&t; 0x0000
DECL|macro|SRB_DisableDisconnect
mdefine_line|#define&t;&t;SRB_DisableDisconnect&t; 0x0004
DECL|macro|SRB_DisableSynchTransfer
mdefine_line|#define&t;&t;SRB_DisableSynchTransfer 0x0008
DECL|macro|SRB_BypassFrozenQueue
mdefine_line|#define &t;SRB_BypassFrozenQueue&t; 0x0010
DECL|macro|SRB_DisableAutosense
mdefine_line|#define&t;&t;SRB_DisableAutosense&t; 0x0020
DECL|macro|SRB_DataIn
mdefine_line|#define&t;&t;SRB_DataIn&t;&t; 0x0040
DECL|macro|SRB_DataOut
mdefine_line|#define &t;SRB_DataOut&t;&t; 0x0080
multiline_comment|/*&n; * SRB Functions - set in aac_srb-&gt;function&n; */
DECL|macro|SRBF_ExecuteScsi
mdefine_line|#define&t;SRBF_ExecuteScsi&t;0x0000
DECL|macro|SRBF_ClaimDevice
mdefine_line|#define&t;SRBF_ClaimDevice&t;0x0001
DECL|macro|SRBF_IO_Control
mdefine_line|#define&t;SRBF_IO_Control&t;&t;0x0002
DECL|macro|SRBF_ReceiveEvent
mdefine_line|#define&t;SRBF_ReceiveEvent&t;0x0003
DECL|macro|SRBF_ReleaseQueue
mdefine_line|#define&t;SRBF_ReleaseQueue&t;0x0004
DECL|macro|SRBF_AttachDevice
mdefine_line|#define&t;SRBF_AttachDevice&t;0x0005
DECL|macro|SRBF_ReleaseDevice
mdefine_line|#define&t;SRBF_ReleaseDevice&t;0x0006
DECL|macro|SRBF_Shutdown
mdefine_line|#define&t;SRBF_Shutdown&t;&t;0x0007
DECL|macro|SRBF_Flush
mdefine_line|#define&t;SRBF_Flush&t;&t;0x0008
DECL|macro|SRBF_AbortCommand
mdefine_line|#define&t;SRBF_AbortCommand&t;0x0010
DECL|macro|SRBF_ReleaseRecovery
mdefine_line|#define&t;SRBF_ReleaseRecovery&t;0x0011
DECL|macro|SRBF_ResetBus
mdefine_line|#define&t;SRBF_ResetBus&t;&t;0x0012
DECL|macro|SRBF_ResetDevice
mdefine_line|#define&t;SRBF_ResetDevice&t;0x0013
DECL|macro|SRBF_TerminateIO
mdefine_line|#define&t;SRBF_TerminateIO&t;0x0014
DECL|macro|SRBF_FlushQueue
mdefine_line|#define&t;SRBF_FlushQueue&t;&t;0x0015
DECL|macro|SRBF_RemoveDevice
mdefine_line|#define&t;SRBF_RemoveDevice&t;0x0016
DECL|macro|SRBF_DomainValidation
mdefine_line|#define&t;SRBF_DomainValidation&t;0x0017
multiline_comment|/* &n; * SRB SCSI Status - set in aac_srb-&gt;scsi_status&n; */
DECL|macro|SRB_STATUS_PENDING
mdefine_line|#define SRB_STATUS_PENDING                  0x00
DECL|macro|SRB_STATUS_SUCCESS
mdefine_line|#define SRB_STATUS_SUCCESS                  0x01
DECL|macro|SRB_STATUS_ABORTED
mdefine_line|#define SRB_STATUS_ABORTED                  0x02
DECL|macro|SRB_STATUS_ABORT_FAILED
mdefine_line|#define SRB_STATUS_ABORT_FAILED             0x03
DECL|macro|SRB_STATUS_ERROR
mdefine_line|#define SRB_STATUS_ERROR                    0x04
DECL|macro|SRB_STATUS_BUSY
mdefine_line|#define SRB_STATUS_BUSY                     0x05
DECL|macro|SRB_STATUS_INVALID_REQUEST
mdefine_line|#define SRB_STATUS_INVALID_REQUEST          0x06
DECL|macro|SRB_STATUS_INVALID_PATH_ID
mdefine_line|#define SRB_STATUS_INVALID_PATH_ID          0x07
DECL|macro|SRB_STATUS_NO_DEVICE
mdefine_line|#define SRB_STATUS_NO_DEVICE                0x08
DECL|macro|SRB_STATUS_TIMEOUT
mdefine_line|#define SRB_STATUS_TIMEOUT                  0x09
DECL|macro|SRB_STATUS_SELECTION_TIMEOUT
mdefine_line|#define SRB_STATUS_SELECTION_TIMEOUT        0x0A
DECL|macro|SRB_STATUS_COMMAND_TIMEOUT
mdefine_line|#define SRB_STATUS_COMMAND_TIMEOUT          0x0B
DECL|macro|SRB_STATUS_MESSAGE_REJECTED
mdefine_line|#define SRB_STATUS_MESSAGE_REJECTED         0x0D
DECL|macro|SRB_STATUS_BUS_RESET
mdefine_line|#define SRB_STATUS_BUS_RESET                0x0E
DECL|macro|SRB_STATUS_PARITY_ERROR
mdefine_line|#define SRB_STATUS_PARITY_ERROR             0x0F
DECL|macro|SRB_STATUS_REQUEST_SENSE_FAILED
mdefine_line|#define SRB_STATUS_REQUEST_SENSE_FAILED     0x10
DECL|macro|SRB_STATUS_NO_HBA
mdefine_line|#define SRB_STATUS_NO_HBA                   0x11
DECL|macro|SRB_STATUS_DATA_OVERRUN
mdefine_line|#define SRB_STATUS_DATA_OVERRUN             0x12
DECL|macro|SRB_STATUS_UNEXPECTED_BUS_FREE
mdefine_line|#define SRB_STATUS_UNEXPECTED_BUS_FREE      0x13
DECL|macro|SRB_STATUS_PHASE_SEQUENCE_FAILURE
mdefine_line|#define SRB_STATUS_PHASE_SEQUENCE_FAILURE   0x14
DECL|macro|SRB_STATUS_BAD_SRB_BLOCK_LENGTH
mdefine_line|#define SRB_STATUS_BAD_SRB_BLOCK_LENGTH     0x15
DECL|macro|SRB_STATUS_REQUEST_FLUSHED
mdefine_line|#define SRB_STATUS_REQUEST_FLUSHED          0x16
DECL|macro|SRB_STATUS_DELAYED_RETRY
mdefine_line|#define SRB_STATUS_DELAYED_RETRY&t;    0x17
DECL|macro|SRB_STATUS_INVALID_LUN
mdefine_line|#define SRB_STATUS_INVALID_LUN              0x20
DECL|macro|SRB_STATUS_INVALID_TARGET_ID
mdefine_line|#define SRB_STATUS_INVALID_TARGET_ID        0x21
DECL|macro|SRB_STATUS_BAD_FUNCTION
mdefine_line|#define SRB_STATUS_BAD_FUNCTION             0x22
DECL|macro|SRB_STATUS_ERROR_RECOVERY
mdefine_line|#define SRB_STATUS_ERROR_RECOVERY           0x23
DECL|macro|SRB_STATUS_NOT_STARTED
mdefine_line|#define SRB_STATUS_NOT_STARTED&t;&t;    0x24
DECL|macro|SRB_STATUS_NOT_IN_USE
mdefine_line|#define SRB_STATUS_NOT_IN_USE&t;&t;    0x30
DECL|macro|SRB_STATUS_FORCE_ABORT
mdefine_line|#define SRB_STATUS_FORCE_ABORT&t;&t;    0x31
DECL|macro|SRB_STATUS_DOMAIN_VALIDATION_FAIL
mdefine_line|#define SRB_STATUS_DOMAIN_VALIDATION_FAIL   0x32
multiline_comment|/*&n; * Object-Server / Volume-Manager Dispatch Classes&n; */
DECL|macro|VM_Null
mdefine_line|#define&t;&t;VM_Null&t;&t;&t;0
DECL|macro|VM_NameServe
mdefine_line|#define&t;&t;VM_NameServe&t;&t;1
DECL|macro|VM_ContainerConfig
mdefine_line|#define&t;&t;VM_ContainerConfig&t;2
DECL|macro|VM_Ioctl
mdefine_line|#define&t;&t;VM_Ioctl&t;&t;3
DECL|macro|VM_FilesystemIoctl
mdefine_line|#define&t;&t;VM_FilesystemIoctl&t;4
DECL|macro|VM_CloseAll
mdefine_line|#define&t;&t;VM_CloseAll&t;&t;5
DECL|macro|VM_CtBlockRead
mdefine_line|#define&t;&t;VM_CtBlockRead&t;&t;6
DECL|macro|VM_CtBlockWrite
mdefine_line|#define&t;&t;VM_CtBlockWrite&t;&t;7
DECL|macro|VM_SliceBlockRead
mdefine_line|#define&t;&t;VM_SliceBlockRead&t;8&t;/* raw access to configured &quot;storage objects&quot; */
DECL|macro|VM_SliceBlockWrite
mdefine_line|#define&t;&t;VM_SliceBlockWrite&t;9
DECL|macro|VM_DriveBlockRead
mdefine_line|#define&t;&t;VM_DriveBlockRead&t;10&t;/* raw access to physical devices */
DECL|macro|VM_DriveBlockWrite
mdefine_line|#define&t;&t;VM_DriveBlockWrite&t;11
DECL|macro|VM_EnclosureMgt
mdefine_line|#define&t;&t;VM_EnclosureMgt&t;&t;12&t;/* enclosure management */
DECL|macro|VM_Unused
mdefine_line|#define&t;&t;VM_Unused&t;&t;13&t;/* used to be diskset management */
DECL|macro|VM_CtBlockVerify
mdefine_line|#define&t;&t;VM_CtBlockVerify&t;14
DECL|macro|VM_CtPerf
mdefine_line|#define&t;&t;VM_CtPerf&t;&t;15&t;/* performance test */
DECL|macro|VM_CtBlockRead64
mdefine_line|#define&t;&t;VM_CtBlockRead64&t;16
DECL|macro|VM_CtBlockWrite64
mdefine_line|#define&t;&t;VM_CtBlockWrite64&t;17
DECL|macro|VM_CtBlockVerify64
mdefine_line|#define&t;&t;VM_CtBlockVerify64&t;18
DECL|macro|VM_CtHostRead64
mdefine_line|#define&t;&t;VM_CtHostRead64&t;&t;19
DECL|macro|VM_CtHostWrite64
mdefine_line|#define&t;&t;VM_CtHostWrite64&t;20
DECL|macro|MAX_VMCOMMAND_NUM
mdefine_line|#define&t;&t;MAX_VMCOMMAND_NUM&t;21&t;/* used for sizing stats array - leave last */
multiline_comment|/*&n; *&t;Descriptive information (eg, vital stats)&n; *&t;that a content manager might report.  The&n; *&t;FileArray filesystem component is one example&n; *&t;of a content manager.  Raw mode might be&n; *&t;another.&n; */
DECL|struct|aac_fsinfo
r_struct
id|aac_fsinfo
(brace
DECL|member|fsTotalSize
id|u32
id|fsTotalSize
suffix:semicolon
multiline_comment|/* Consumed by fs, incl. metadata */
DECL|member|fsBlockSize
id|u32
id|fsBlockSize
suffix:semicolon
DECL|member|fsFragSize
id|u32
id|fsFragSize
suffix:semicolon
DECL|member|fsMaxExtendSize
id|u32
id|fsMaxExtendSize
suffix:semicolon
DECL|member|fsSpaceUnits
id|u32
id|fsSpaceUnits
suffix:semicolon
DECL|member|fsMaxNumFiles
id|u32
id|fsMaxNumFiles
suffix:semicolon
DECL|member|fsNumFreeFiles
id|u32
id|fsNumFreeFiles
suffix:semicolon
DECL|member|fsInodeDensity
id|u32
id|fsInodeDensity
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* valid iff ObjType == FT_FILESYS &amp;&amp; !(ContentState &amp; FSCS_NOTCLEAN) */
DECL|union|aac_contentinfo
r_union
id|aac_contentinfo
(brace
DECL|member|filesys
r_struct
id|aac_fsinfo
id|filesys
suffix:semicolon
multiline_comment|/* valid iff ObjType == FT_FILESYS &amp;&amp; !(ContentState &amp; FSCS_NOTCLEAN) */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Query for Container Configuration Status&n; */
DECL|macro|CT_GET_CONFIG_STATUS
mdefine_line|#define CT_GET_CONFIG_STATUS 147
DECL|struct|aac_get_config_status
r_struct
id|aac_get_config_status
(brace
DECL|member|command
id|u32
id|command
suffix:semicolon
multiline_comment|/* VM_ContainerConfig */
DECL|member|type
id|u32
id|type
suffix:semicolon
multiline_comment|/* CT_GET_CONFIG_STATUS */
DECL|member|parm1
id|u32
id|parm1
suffix:semicolon
DECL|member|parm2
id|u32
id|parm2
suffix:semicolon
DECL|member|parm3
id|u32
id|parm3
suffix:semicolon
DECL|member|parm4
id|u32
id|parm4
suffix:semicolon
DECL|member|parm5
id|u32
id|parm5
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
multiline_comment|/* sizeof(((struct aac_get_config_status_resp *)NULL)-&gt;data) */
)brace
suffix:semicolon
DECL|macro|CFACT_CONTINUE
mdefine_line|#define CFACT_CONTINUE 0
DECL|macro|CFACT_PAUSE
mdefine_line|#define CFACT_PAUSE    1
DECL|macro|CFACT_ABORT
mdefine_line|#define CFACT_ABORT    2
DECL|struct|aac_get_config_status_resp
r_struct
id|aac_get_config_status_resp
(brace
DECL|member|response
id|u32
id|response
suffix:semicolon
multiline_comment|/* ST_OK */
DECL|member|dummy0
id|u32
id|dummy0
suffix:semicolon
DECL|member|status
id|u32
id|status
suffix:semicolon
multiline_comment|/* CT_OK */
DECL|member|parm1
id|u32
id|parm1
suffix:semicolon
DECL|member|parm2
id|u32
id|parm2
suffix:semicolon
DECL|member|parm3
id|u32
id|parm3
suffix:semicolon
DECL|member|parm4
id|u32
id|parm4
suffix:semicolon
DECL|member|parm5
id|u32
id|parm5
suffix:semicolon
r_struct
(brace
DECL|member|action
id|u32
id|action
suffix:semicolon
multiline_comment|/* CFACT_CONTINUE, CFACT_PAUSE or CFACT_ABORT */
DECL|member|flags
id|u16
id|flags
suffix:semicolon
DECL|member|count
id|s16
id|count
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Accept the configuration as-is&n; */
DECL|macro|CT_COMMIT_CONFIG
mdefine_line|#define CT_COMMIT_CONFIG 152
DECL|struct|aac_commit_config
r_struct
id|aac_commit_config
(brace
DECL|member|command
id|u32
id|command
suffix:semicolon
multiline_comment|/* VM_ContainerConfig */
DECL|member|type
id|u32
id|type
suffix:semicolon
multiline_comment|/* CT_COMMIT_CONFIG */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Query for Container Configuration Count&n; */
DECL|macro|CT_GET_CONTAINER_COUNT
mdefine_line|#define CT_GET_CONTAINER_COUNT 4
DECL|struct|aac_get_container_count
r_struct
id|aac_get_container_count
(brace
DECL|member|command
id|u32
id|command
suffix:semicolon
multiline_comment|/* VM_ContainerConfig */
DECL|member|type
id|u32
id|type
suffix:semicolon
multiline_comment|/* CT_GET_CONTAINER_COUNT */
)brace
suffix:semicolon
DECL|struct|aac_get_container_count_resp
r_struct
id|aac_get_container_count_resp
(brace
DECL|member|response
id|u32
id|response
suffix:semicolon
multiline_comment|/* ST_OK */
DECL|member|dummy0
id|u32
id|dummy0
suffix:semicolon
DECL|member|MaxContainers
id|u32
id|MaxContainers
suffix:semicolon
DECL|member|ContainerSwitchEntries
id|u32
id|ContainerSwitchEntries
suffix:semicolon
DECL|member|MaxPartitions
id|u32
id|MaxPartitions
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Query for &quot;mountable&quot; objects, ie, objects that are typically&n; *&t;associated with a drive letter on the client (host) side.&n; */
DECL|struct|aac_mntent
r_struct
id|aac_mntent
(brace
DECL|member|oid
id|u32
id|oid
suffix:semicolon
DECL|member|name
id|u8
id|name
(braket
l_int|16
)braket
suffix:semicolon
singleline_comment|// if applicable
DECL|member|create_info
r_struct
id|creation_info
id|create_info
suffix:semicolon
singleline_comment|// if applicable
DECL|member|capacity
id|u32
id|capacity
suffix:semicolon
DECL|member|vol
id|u32
id|vol
suffix:semicolon
singleline_comment|// substrate structure
DECL|member|obj
id|u32
id|obj
suffix:semicolon
singleline_comment|// FT_FILESYS, FT_DATABASE, etc.
DECL|member|state
id|u32
id|state
suffix:semicolon
singleline_comment|// unready for mounting, readonly, etc.
DECL|member|fileinfo
r_union
id|aac_contentinfo
id|fileinfo
suffix:semicolon
singleline_comment|// Info specific to content manager (eg, filesystem)
DECL|member|altoid
id|u32
id|altoid
suffix:semicolon
singleline_comment|// != oid &lt;==&gt; snapshot or broken mirror exists
)brace
suffix:semicolon
DECL|macro|FSCS_NOTCLEAN
mdefine_line|#define FSCS_NOTCLEAN&t;0x0001  /* fsck is neccessary before mounting */
DECL|macro|FSCS_READONLY
mdefine_line|#define FSCS_READONLY&t;0x0002&t;/* possible result of broken mirror */
DECL|macro|FSCS_HIDDEN
mdefine_line|#define FSCS_HIDDEN&t;0x0004&t;/* should be ignored - set during a clear */
DECL|struct|aac_query_mount
r_struct
id|aac_query_mount
(brace
DECL|member|command
id|u32
id|command
suffix:semicolon
DECL|member|type
id|u32
id|type
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aac_mount
r_struct
id|aac_mount
(brace
DECL|member|status
id|u32
id|status
suffix:semicolon
DECL|member|type
id|u32
id|type
suffix:semicolon
multiline_comment|/* should be same as that requested */
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|mnt
r_struct
id|aac_mntent
id|mnt
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CT_READ_NAME
mdefine_line|#define CT_READ_NAME 130
DECL|struct|aac_get_name
r_struct
id|aac_get_name
(brace
DECL|member|command
id|u32
id|command
suffix:semicolon
multiline_comment|/* VM_ContainerConfig */
DECL|member|type
id|u32
id|type
suffix:semicolon
multiline_comment|/* CT_READ_NAME */
DECL|member|cid
id|u32
id|cid
suffix:semicolon
DECL|member|parm1
id|u32
id|parm1
suffix:semicolon
DECL|member|parm2
id|u32
id|parm2
suffix:semicolon
DECL|member|parm3
id|u32
id|parm3
suffix:semicolon
DECL|member|parm4
id|u32
id|parm4
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
multiline_comment|/* sizeof(((struct aac_get_name_resp *)NULL)-&gt;data) */
)brace
suffix:semicolon
DECL|macro|CT_OK
mdefine_line|#define CT_OK        218
DECL|struct|aac_get_name_resp
r_struct
id|aac_get_name_resp
(brace
DECL|member|dummy0
id|u32
id|dummy0
suffix:semicolon
DECL|member|dummy1
id|u32
id|dummy1
suffix:semicolon
DECL|member|status
id|u32
id|status
suffix:semicolon
multiline_comment|/* CT_OK */
DECL|member|parm1
id|u32
id|parm1
suffix:semicolon
DECL|member|parm2
id|u32
id|parm2
suffix:semicolon
DECL|member|parm3
id|u32
id|parm3
suffix:semicolon
DECL|member|parm4
id|u32
id|parm4
suffix:semicolon
DECL|member|parm5
id|u32
id|parm5
suffix:semicolon
DECL|member|data
id|u8
id|data
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The following command is sent to shut down each container.&n; */
DECL|struct|aac_close
r_struct
id|aac_close
(brace
DECL|member|command
id|u32
id|command
suffix:semicolon
DECL|member|cid
id|u32
id|cid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aac_query_disk
r_struct
id|aac_query_disk
(brace
DECL|member|cnum
id|s32
id|cnum
suffix:semicolon
DECL|member|bus
id|s32
id|bus
suffix:semicolon
DECL|member|id
id|s32
id|id
suffix:semicolon
DECL|member|lun
id|s32
id|lun
suffix:semicolon
DECL|member|valid
id|u32
id|valid
suffix:semicolon
DECL|member|locked
id|u32
id|locked
suffix:semicolon
DECL|member|deleted
id|u32
id|deleted
suffix:semicolon
DECL|member|instance
id|s32
id|instance
suffix:semicolon
DECL|member|name
id|s8
id|name
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|unmapped
id|u32
id|unmapped
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aac_delete_disk
r_struct
id|aac_delete_disk
(brace
DECL|member|disknum
id|u32
id|disknum
suffix:semicolon
DECL|member|cnum
id|u32
id|cnum
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fib_ioctl
r_struct
id|fib_ioctl
(brace
DECL|member|fibctx
id|u32
id|fibctx
suffix:semicolon
DECL|member|wait
id|s32
id|wait
suffix:semicolon
DECL|member|fib
r_char
id|__user
op_star
id|fib
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|revision
r_struct
id|revision
(brace
DECL|member|compat
id|u32
id|compat
suffix:semicolon
DECL|member|version
id|u32
id|version
suffix:semicolon
DECL|member|build
id|u32
id|build
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * &t;Ugly - non Linux like ioctl coding for back compat.&n; */
DECL|macro|CTL_CODE
mdefine_line|#define CTL_CODE(function, method) (                 &bslash;&n;    (4&lt;&lt; 16) | ((function) &lt;&lt; 2) | (method) &bslash;&n;)
multiline_comment|/*&n; *&t;Define the method codes for how buffers are passed for I/O and FS &n; *&t;controls&n; */
DECL|macro|METHOD_BUFFERED
mdefine_line|#define METHOD_BUFFERED                 0
DECL|macro|METHOD_NEITHER
mdefine_line|#define METHOD_NEITHER                  3
multiline_comment|/*&n; *&t;Filesystem ioctls&n; */
DECL|macro|FSACTL_SENDFIB
mdefine_line|#define FSACTL_SENDFIB                  &t;CTL_CODE(2050, METHOD_BUFFERED)
DECL|macro|FSACTL_SEND_RAW_SRB
mdefine_line|#define FSACTL_SEND_RAW_SRB               &t;CTL_CODE(2067, METHOD_BUFFERED)
DECL|macro|FSACTL_DELETE_DISK
mdefine_line|#define FSACTL_DELETE_DISK&t;&t;&t;0x163
DECL|macro|FSACTL_QUERY_DISK
mdefine_line|#define FSACTL_QUERY_DISK&t;&t;&t;0x173
DECL|macro|FSACTL_OPEN_GET_ADAPTER_FIB
mdefine_line|#define FSACTL_OPEN_GET_ADAPTER_FIB&t;&t;CTL_CODE(2100, METHOD_BUFFERED)
DECL|macro|FSACTL_GET_NEXT_ADAPTER_FIB
mdefine_line|#define FSACTL_GET_NEXT_ADAPTER_FIB&t;&t;CTL_CODE(2101, METHOD_BUFFERED)
DECL|macro|FSACTL_CLOSE_GET_ADAPTER_FIB
mdefine_line|#define FSACTL_CLOSE_GET_ADAPTER_FIB&t;&t;CTL_CODE(2102, METHOD_BUFFERED)
DECL|macro|FSACTL_MINIPORT_REV_CHECK
mdefine_line|#define FSACTL_MINIPORT_REV_CHECK               CTL_CODE(2107, METHOD_BUFFERED)
DECL|macro|FSACTL_GET_PCI_INFO
mdefine_line|#define FSACTL_GET_PCI_INFO               &t;CTL_CODE(2119, METHOD_BUFFERED)
DECL|macro|FSACTL_FORCE_DELETE_DISK
mdefine_line|#define FSACTL_FORCE_DELETE_DISK&t;&t;CTL_CODE(2120, METHOD_NEITHER)
DECL|macro|FSACTL_GET_CONTAINERS
mdefine_line|#define FSACTL_GET_CONTAINERS&t;&t;&t;2131
DECL|struct|aac_common
r_struct
id|aac_common
(brace
multiline_comment|/*&n;&t; *&t;If this value is set to 1 then interrupt moderation will occur &n;&t; *&t;in the base commuication support.&n;&t; */
DECL|member|irq_mod
id|u32
id|irq_mod
suffix:semicolon
DECL|member|peak_fibs
id|u32
id|peak_fibs
suffix:semicolon
DECL|member|zero_fibs
id|u32
id|zero_fibs
suffix:semicolon
DECL|member|fib_timeouts
id|u32
id|fib_timeouts
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Statistical counters in debug mode&n;&t; */
macro_line|#ifdef DBG
DECL|member|FibsSent
id|u32
id|FibsSent
suffix:semicolon
DECL|member|FibRecved
id|u32
id|FibRecved
suffix:semicolon
DECL|member|NoResponseSent
id|u32
id|NoResponseSent
suffix:semicolon
DECL|member|NoResponseRecved
id|u32
id|NoResponseRecved
suffix:semicolon
DECL|member|AsyncSent
id|u32
id|AsyncSent
suffix:semicolon
DECL|member|AsyncRecved
id|u32
id|AsyncRecved
suffix:semicolon
DECL|member|NormalSent
id|u32
id|NormalSent
suffix:semicolon
DECL|member|NormalRecved
id|u32
id|NormalRecved
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
r_extern
r_struct
id|aac_common
id|aac_config
suffix:semicolon
multiline_comment|/*&n; *&t;The following macro is used when sending and receiving FIBs. It is&n; *&t;only used for debugging.&n; */
macro_line|#ifdef DBG
DECL|macro|FIB_COUNTER_INCREMENT
mdefine_line|#define&t;FIB_COUNTER_INCREMENT(counter)&t;&t;(counter)++
macro_line|#else
DECL|macro|FIB_COUNTER_INCREMENT
mdefine_line|#define&t;FIB_COUNTER_INCREMENT(counter)&t;&t;
macro_line|#endif
multiline_comment|/*&n; *&t;Adapter direct commands&n; *&t;Monitor/Kernel API&n; */
DECL|macro|BREAKPOINT_REQUEST
mdefine_line|#define&t;BREAKPOINT_REQUEST&t;&t;cpu_to_le32(0x00000004)
DECL|macro|INIT_STRUCT_BASE_ADDRESS
mdefine_line|#define&t;INIT_STRUCT_BASE_ADDRESS&t;cpu_to_le32(0x00000005)
DECL|macro|READ_PERMANENT_PARAMETERS
mdefine_line|#define READ_PERMANENT_PARAMETERS&t;cpu_to_le32(0x0000000a)
DECL|macro|WRITE_PERMANENT_PARAMETERS
mdefine_line|#define WRITE_PERMANENT_PARAMETERS&t;cpu_to_le32(0x0000000b)
DECL|macro|HOST_CRASHING
mdefine_line|#define HOST_CRASHING&t;&t;&t;cpu_to_le32(0x0000000d)
DECL|macro|SEND_SYNCHRONOUS_FIB
mdefine_line|#define&t;SEND_SYNCHRONOUS_FIB&t;&t;cpu_to_le32(0x0000000c)
DECL|macro|COMMAND_POST_RESULTS
mdefine_line|#define&t;COMMAND_POST_RESULTS&t;&t;cpu_to_le32(0x00000014)
DECL|macro|GET_ADAPTER_PROPERTIES
mdefine_line|#define GET_ADAPTER_PROPERTIES&t;&t;cpu_to_le32(0x00000019)
DECL|macro|RE_INIT_ADAPTER
mdefine_line|#define RE_INIT_ADAPTER&t;&t;&t;cpu_to_le32(0x000000ee)
multiline_comment|/*&n; *&t;Adapter Status Register&n; *&n; *  Phase Staus mailbox is 32bits:&n; *&t;&lt;31:16&gt; = Phase Status&n; *&t;&lt;15:0&gt;  = Phase&n; *&n; *&t;The adapter reports is present state through the phase.  Only&n; *&t;a single phase should be ever be set.  Each phase can have multiple&n; *&t;phase status bits to provide more detailed information about the &n; *&t;state of the board.  Care should be taken to ensure that any phase &n; *&t;status bits that are set when changing the phase are also valid&n; *&t;for the new phase or be cleared out.  Adapter software (monitor,&n; *&t;iflash, kernel) is responsible for properly maintining the phase &n; *&t;status mailbox when it is running.&n; *&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&n; *&t;MONKER_API Phases&t;&t;&t;&t;&t;&t;&t;&n; *&n; *&t;Phases are bit oriented.  It is NOT valid  to have multiple bits set&t;&t;&t;&t;&t;&t;&n; */
DECL|macro|SELF_TEST_FAILED
mdefine_line|#define&t;SELF_TEST_FAILED&t;&t;(cpu_to_le32(0x00000004))
DECL|macro|MONITOR_PANIC
mdefine_line|#define MONITOR_PANIC&t;&t;&t;(cpu_to_le32(0x00000020))
DECL|macro|KERNEL_UP_AND_RUNNING
mdefine_line|#define&t;KERNEL_UP_AND_RUNNING&t;&t;(cpu_to_le32(0x00000080))
DECL|macro|KERNEL_PANIC
mdefine_line|#define&t;KERNEL_PANIC&t;&t;&t;(cpu_to_le32(0x00000100))
multiline_comment|/*&n; *&t;Doorbell bit defines&n; */
DECL|macro|DoorBellSyncCmdAvailable
mdefine_line|#define DoorBellSyncCmdAvailable&t;cpu_to_le32(1&lt;&lt;0)&t;
singleline_comment|// Host -&gt; Adapter
DECL|macro|DoorBellPrintfDone
mdefine_line|#define DoorBellPrintfDone&t;&t;cpu_to_le32(1&lt;&lt;5)&t;
singleline_comment|// Host -&gt; Adapter
DECL|macro|DoorBellAdapterNormCmdReady
mdefine_line|#define DoorBellAdapterNormCmdReady&t;cpu_to_le32(1&lt;&lt;1)&t;
singleline_comment|// Adapter -&gt; Host
DECL|macro|DoorBellAdapterNormRespReady
mdefine_line|#define DoorBellAdapterNormRespReady&t;cpu_to_le32(1&lt;&lt;2)&t;
singleline_comment|// Adapter -&gt; Host
DECL|macro|DoorBellAdapterNormCmdNotFull
mdefine_line|#define DoorBellAdapterNormCmdNotFull&t;cpu_to_le32(1&lt;&lt;3)&t;
singleline_comment|// Adapter -&gt; Host
DECL|macro|DoorBellAdapterNormRespNotFull
mdefine_line|#define DoorBellAdapterNormRespNotFull&t;cpu_to_le32(1&lt;&lt;4)&t;
singleline_comment|// Adapter -&gt; Host
DECL|macro|DoorBellPrintfReady
mdefine_line|#define DoorBellPrintfReady&t;&t;cpu_to_le32(1&lt;&lt;5)&t;
singleline_comment|// Adapter -&gt; Host
multiline_comment|/*&n; *&t;For FIB communication, we need all of the following things&n; *&t;to send back to the user.&n; */
DECL|macro|AifCmdEventNotify
mdefine_line|#define &t;AifCmdEventNotify&t;1&t;/* Notify of event */
DECL|macro|AifEnConfigChange
mdefine_line|#define&t;&t;&t;AifEnConfigChange&t;3&t;/* Adapter configuration change */
DECL|macro|AifEnContainerChange
mdefine_line|#define&t;&t;&t;AifEnContainerChange&t;4&t;/* Container configuration change */
DECL|macro|AifEnDeviceFailure
mdefine_line|#define&t;&t;&t;AifEnDeviceFailure&t;5&t;/* SCSI device failed */
DECL|macro|AifEnAddContainer
mdefine_line|#define&t;&t;&t;AifEnAddContainer&t;15&t;/* A new array was created */
DECL|macro|AifEnDeleteContainer
mdefine_line|#define&t;&t;&t;AifEnDeleteContainer&t;16&t;/* A container was deleted */
DECL|macro|AifEnExpEvent
mdefine_line|#define&t;&t;&t;AifEnExpEvent&t;&t;23&t;/* Firmware Event Log */
DECL|macro|AifExeFirmwarePanic
mdefine_line|#define&t;&t;&t;AifExeFirmwarePanic&t;3&t;/* Firmware Event Panic */
DECL|macro|AifHighPriority
mdefine_line|#define&t;&t;&t;AifHighPriority&t;&t;3&t;/* Highest Priority Event */
DECL|macro|AifCmdJobProgress
mdefine_line|#define&t;&t;AifCmdJobProgress&t;2&t;/* Progress report */
DECL|macro|AifJobCtrZero
mdefine_line|#define&t;&t;&t;AifJobCtrZero&t;101&t;/* Array Zero progress */
DECL|macro|AifJobStsSuccess
mdefine_line|#define&t;&t;&t;AifJobStsSuccess 1&t;/* Job completes */
DECL|macro|AifCmdAPIReport
mdefine_line|#define&t;&t;AifCmdAPIReport&t;&t;3&t;/* Report from other user of API */
DECL|macro|AifCmdDriverNotify
mdefine_line|#define&t;&t;AifCmdDriverNotify&t;4&t;/* Notify host driver of event */
DECL|macro|AifDenMorphComplete
mdefine_line|#define&t;&t;&t;AifDenMorphComplete 200&t;/* A morph operation completed */
DECL|macro|AifDenVolumeExtendComplete
mdefine_line|#define&t;&t;&t;AifDenVolumeExtendComplete 201 /* A volume extend completed */
DECL|macro|AifReqJobList
mdefine_line|#define&t;&t;AifReqJobList&t;&t;100&t;/* Gets back complete job list */
DECL|macro|AifReqJobsForCtr
mdefine_line|#define&t;&t;AifReqJobsForCtr&t;101&t;/* Gets back jobs for specific container */
DECL|macro|AifReqJobsForScsi
mdefine_line|#define&t;&t;AifReqJobsForScsi&t;102&t;/* Gets back jobs for specific SCSI device */ 
DECL|macro|AifReqJobReport
mdefine_line|#define&t;&t;AifReqJobReport&t;&t;103&t;/* Gets back a specific job report or list of them */ 
DECL|macro|AifReqTerminateJob
mdefine_line|#define&t;&t;AifReqTerminateJob&t;104&t;/* Terminates job */
DECL|macro|AifReqSuspendJob
mdefine_line|#define&t;&t;AifReqSuspendJob&t;105&t;/* Suspends a job */
DECL|macro|AifReqResumeJob
mdefine_line|#define&t;&t;AifReqResumeJob&t;&t;106&t;/* Resumes a job */ 
DECL|macro|AifReqSendAPIReport
mdefine_line|#define&t;&t;AifReqSendAPIReport&t;107&t;/* API generic report requests */
DECL|macro|AifReqAPIJobStart
mdefine_line|#define&t;&t;AifReqAPIJobStart&t;108&t;/* Start a job from the API */
DECL|macro|AifReqAPIJobUpdate
mdefine_line|#define&t;&t;AifReqAPIJobUpdate&t;109&t;/* Update a job report from the API */
DECL|macro|AifReqAPIJobFinish
mdefine_line|#define&t;&t;AifReqAPIJobFinish&t;110&t;/* Finish a job from the API */
multiline_comment|/*&n; *&t;Adapter Initiated FIB command structures. Start with the adapter&n; *&t;initiated FIBs that really come from the adapter, and get responded&n; *&t;to by the host.&n; */
DECL|struct|aac_aifcmd
r_struct
id|aac_aifcmd
(brace
DECL|member|command
id|u32
id|command
suffix:semicolon
multiline_comment|/* Tell host what type of notify this is */
DECL|member|seqnum
id|u32
id|seqnum
suffix:semicolon
multiline_comment|/* To allow ordering of reports (if necessary) */
DECL|member|data
id|u8
id|data
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Undefined length (from kernel viewpoint) */
)brace
suffix:semicolon
multiline_comment|/**&n; * &t;Convert capacity to cylinders&n; *  &t;accounting for the fact capacity could be a 64 bit value&n; *&n; */
DECL|function|cap_to_cyls
r_static
r_inline
id|u32
id|cap_to_cyls
c_func
(paren
id|sector_t
id|capacity
comma
id|u32
id|divisor
)paren
(brace
id|sector_div
c_func
(paren
id|capacity
comma
id|divisor
)paren
suffix:semicolon
r_return
(paren
id|u32
)paren
id|capacity
suffix:semicolon
)brace
r_struct
id|scsi_cmnd
suffix:semicolon
r_const
r_char
op_star
id|aac_driverinfo
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_struct
id|fib
op_star
id|fib_alloc
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|fib_setup
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|fib_map_free
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|fib_free
c_func
(paren
r_struct
id|fib
op_star
id|context
)paren
suffix:semicolon
r_void
id|fib_init
c_func
(paren
r_struct
id|fib
op_star
id|context
)paren
suffix:semicolon
r_void
id|fib_dealloc
c_func
(paren
r_struct
id|fib
op_star
id|context
)paren
suffix:semicolon
r_void
id|aac_printf
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
comma
id|u32
id|val
)paren
suffix:semicolon
r_int
id|fib_send
c_func
(paren
id|u16
id|command
comma
r_struct
id|fib
op_star
id|context
comma
r_int
r_int
id|size
comma
r_int
id|priority
comma
r_int
id|wait
comma
r_int
id|reply
comma
id|fib_callback
id|callback
comma
r_void
op_star
id|ctxt
)paren
suffix:semicolon
r_int
id|aac_consumer_get
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
comma
r_struct
id|aac_queue
op_star
id|q
comma
r_struct
id|aac_entry
op_star
op_star
id|entry
)paren
suffix:semicolon
r_int
id|aac_consumer_avail
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
comma
r_struct
id|aac_queue
op_star
id|q
)paren
suffix:semicolon
r_void
id|aac_consumer_free
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
comma
r_struct
id|aac_queue
op_star
id|q
comma
id|u32
id|qnum
)paren
suffix:semicolon
r_int
id|fib_complete
c_func
(paren
r_struct
id|fib
op_star
id|context
)paren
suffix:semicolon
DECL|macro|fib_data
mdefine_line|#define fib_data(fibctx) ((void *)(fibctx)-&gt;hw_fib-&gt;data)
r_struct
id|aac_dev
op_star
id|aac_init_adapter
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|aac_get_config_status
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|aac_get_containers
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|aac_scsi_cmd
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_int
id|aac_dev_ioctl
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
comma
r_int
id|cmd
comma
r_void
id|__user
op_star
id|arg
)paren
suffix:semicolon
r_int
id|aac_do_ioctl
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
comma
r_int
id|cmd
comma
r_void
id|__user
op_star
id|arg
)paren
suffix:semicolon
r_int
id|aac_rx_init
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|aac_rkt_init
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|aac_sa_init
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
r_int
id|aac_response_normal
c_func
(paren
r_struct
id|aac_queue
op_star
id|q
)paren
suffix:semicolon
r_int
r_int
id|aac_command_normal
c_func
(paren
r_struct
id|aac_queue
op_star
id|q
)paren
suffix:semicolon
r_int
id|aac_command_thread
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|aac_close_fib_context
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
comma
r_struct
id|aac_fib_context
op_star
id|fibctx
)paren
suffix:semicolon
r_int
id|fib_adapter_complete
c_func
(paren
r_struct
id|fib
op_star
id|fibptr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_struct
id|aac_driver_ident
op_star
id|aac_get_driver_ident
c_func
(paren
r_int
id|devtype
)paren
suffix:semicolon
r_int
id|aac_get_adapter_info
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|aac_send_shutdown
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
suffix:semicolon
eof
