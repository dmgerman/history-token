macro_line|#ifndef&t;__HPET__
DECL|macro|__HPET__
mdefine_line|#define&t;__HPET__ 1
multiline_comment|/*&n; * Offsets into HPET Registers&n; */
DECL|struct|hpet
r_struct
id|hpet
(brace
DECL|member|hpet_cap
id|u64
id|hpet_cap
suffix:semicolon
multiline_comment|/* capabilities */
DECL|member|res0
id|u64
id|res0
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|hpet_config
id|u64
id|hpet_config
suffix:semicolon
multiline_comment|/* configuration */
DECL|member|res1
id|u64
id|res1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|hpet_isr
id|u64
id|hpet_isr
suffix:semicolon
multiline_comment|/* interrupt status reg */
DECL|member|res2
id|u64
id|res2
(braket
l_int|25
)braket
suffix:semicolon
multiline_comment|/* reserved */
r_union
(brace
multiline_comment|/* main counter */
DECL|member|_hpet_mc64
id|u64
id|_hpet_mc64
suffix:semicolon
DECL|member|_hpet_mc32
id|u32
id|_hpet_mc32
suffix:semicolon
DECL|member|_hpet_mc
r_int
r_int
id|_hpet_mc
suffix:semicolon
DECL|member|_u0
)brace
id|_u0
suffix:semicolon
DECL|member|res3
id|u64
id|res3
suffix:semicolon
multiline_comment|/* reserved */
DECL|struct|hpet_timer
r_struct
id|hpet_timer
(brace
DECL|member|hpet_config
id|u64
id|hpet_config
suffix:semicolon
multiline_comment|/* configuration/cap */
r_union
(brace
multiline_comment|/* timer compare register */
DECL|member|_hpet_hc64
id|u64
id|_hpet_hc64
suffix:semicolon
DECL|member|_hpet_hc32
id|u32
id|_hpet_hc32
suffix:semicolon
DECL|member|_hpet_compare
r_int
r_int
id|_hpet_compare
suffix:semicolon
DECL|member|_u1
)brace
id|_u1
suffix:semicolon
DECL|member|hpet_fsb
id|u64
id|hpet_fsb
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* FSB route */
DECL|member|hpet_timers
)brace
id|hpet_timers
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|hpet_mc
mdefine_line|#define&t;hpet_mc&t;&t;_u0._hpet_mc
DECL|macro|hpet_compare
mdefine_line|#define&t;hpet_compare&t;_u1._hpet_compare
DECL|macro|HPET_MAX_TIMERS
mdefine_line|#define&t;HPET_MAX_TIMERS&t;(32)
multiline_comment|/*&n; * HPET general capabilities register&n; */
DECL|macro|HPET_COUNTER_CLK_PERIOD_MASK
mdefine_line|#define&t;HPET_COUNTER_CLK_PERIOD_MASK&t;(0xffffffff00000000ULL)
DECL|macro|HPET_COUNTER_CLK_PERIOD_SHIFT
mdefine_line|#define&t;HPET_COUNTER_CLK_PERIOD_SHIFT&t;(32UL)
DECL|macro|HPET_VENDOR_ID_MASK
mdefine_line|#define&t;HPET_VENDOR_ID_MASK&t;&t;(0x00000000ffff0000ULL)
DECL|macro|HPET_VENDOR_ID_SHIFT
mdefine_line|#define&t;HPET_VENDOR_ID_SHIFT&t;&t;(16ULL)
DECL|macro|HPET_LEG_RT_CAP_MASK
mdefine_line|#define&t;HPET_LEG_RT_CAP_MASK&t;&t;(0x8000)
DECL|macro|HPET_COUNTER_SIZE_MASK
mdefine_line|#define&t;HPET_COUNTER_SIZE_MASK&t;&t;(0x2000)
DECL|macro|HPET_NUM_TIM_CAP_MASK
mdefine_line|#define&t;HPET_NUM_TIM_CAP_MASK&t;&t;(0x1f00)
DECL|macro|HPET_NUM_TIM_CAP_SHIFT
mdefine_line|#define&t;HPET_NUM_TIM_CAP_SHIFT&t;&t;(8ULL)
multiline_comment|/*&n; * HPET general configuration register&n; */
DECL|macro|HPET_LEG_RT_CNF_MASK
mdefine_line|#define&t;HPET_LEG_RT_CNF_MASK&t;&t;(2UL)
DECL|macro|HPET_ENABLE_CNF_MASK
mdefine_line|#define&t;HPET_ENABLE_CNF_MASK&t;&t;(1UL)
multiline_comment|/*&n; * HPET interrupt status register&n; */
DECL|macro|HPET_ISR_CLEAR
mdefine_line|#define&t;HPET_ISR_CLEAR(HPET, TIMER)&t;&t;&t;&t;&bslash;&n;&t;&t;(HPET)-&gt;hpet_isr |= (1UL &lt;&lt; TIMER)
multiline_comment|/*&n; * Timer configuration register&n; */
DECL|macro|Tn_INT_ROUTE_CAP_MASK
mdefine_line|#define&t;Tn_INT_ROUTE_CAP_MASK&t;&t;(0xffffffff00000000ULL)
DECL|macro|Tn_INI_ROUTE_CAP_SHIFT
mdefine_line|#define&t;Tn_INI_ROUTE_CAP_SHIFT&t;&t;(32UL)
DECL|macro|Tn_FSB_INT_DELCAP_MASK
mdefine_line|#define&t;Tn_FSB_INT_DELCAP_MASK&t;&t;(0x8000UL)
DECL|macro|Tn_FSB_INT_DELCAP_SHIFT
mdefine_line|#define&t;Tn_FSB_INT_DELCAP_SHIFT&t;&t;(15)
DECL|macro|Tn_FSB_EN_CNF_MASK
mdefine_line|#define&t;Tn_FSB_EN_CNF_MASK&t;&t;(0x4000UL)
DECL|macro|Tn_FSB_EN_CNF_SHIFT
mdefine_line|#define&t;Tn_FSB_EN_CNF_SHIFT&t;&t;(14)
DECL|macro|Tn_INT_ROUTE_CNF_MASK
mdefine_line|#define&t;Tn_INT_ROUTE_CNF_MASK&t;&t;(0x3e00UL)
DECL|macro|Tn_INT_ROUTE_CNF_SHIFT
mdefine_line|#define&t;Tn_INT_ROUTE_CNF_SHIFT&t;&t;(9)
DECL|macro|Tn_32MODE_CNF_MASK
mdefine_line|#define&t;Tn_32MODE_CNF_MASK&t;&t;(0x0100UL)
DECL|macro|Tn_VAL_SET_CNF_MASK
mdefine_line|#define&t;Tn_VAL_SET_CNF_MASK&t;&t;(0x0040UL)
DECL|macro|Tn_SIZE_CAP_MASK
mdefine_line|#define&t;Tn_SIZE_CAP_MASK&t;&t;(0x0020UL)
DECL|macro|Tn_PER_INT_CAP_MASK
mdefine_line|#define&t;Tn_PER_INT_CAP_MASK&t;&t;(0x0010UL)
DECL|macro|Tn_TYPE_CNF_MASK
mdefine_line|#define&t;Tn_TYPE_CNF_MASK&t;&t;(0x0008UL)
DECL|macro|Tn_INT_ENB_CNF_MASK
mdefine_line|#define&t;Tn_INT_ENB_CNF_MASK&t;&t;(0x0004UL)
DECL|macro|Tn_INT_TYPE_CNF_MASK
mdefine_line|#define&t;Tn_INT_TYPE_CNF_MASK&t;&t;(0x0002UL)
multiline_comment|/*&n; * Timer FSB Interrupt Route Register&n; */
DECL|macro|Tn_FSB_INT_ADDR_MASK
mdefine_line|#define&t;Tn_FSB_INT_ADDR_MASK&t;&t;(0xffffffff00000000ULL)
DECL|macro|Tn_FSB_INT_ADDR_SHIFT
mdefine_line|#define&t;Tn_FSB_INT_ADDR_SHIFT&t;&t;(32UL)
DECL|macro|Tn_FSB_INT_VAL_MASK
mdefine_line|#define&t;Tn_FSB_INT_VAL_MASK&t;&t;(0x00000000ffffffffULL)
DECL|struct|hpet_info
r_struct
id|hpet_info
(brace
DECL|member|hi_ireqfreq
r_int
r_int
id|hi_ireqfreq
suffix:semicolon
multiline_comment|/* Hz */
DECL|member|hi_flags
r_int
r_int
id|hi_flags
suffix:semicolon
multiline_comment|/* information */
DECL|member|hi_hpet
r_int
r_int
id|hi_hpet
suffix:semicolon
DECL|member|hi_timer
r_int
r_int
id|hi_timer
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HPET_INFO_PERIODIC
mdefine_line|#define&t;HPET_INFO_PERIODIC&t;0x0001&t;/* timer is periodic */
DECL|macro|HPET_IE_ON
mdefine_line|#define&t;HPET_IE_ON&t;_IO(&squot;h&squot;, 0x01)&t;/* interrupt on */
DECL|macro|HPET_IE_OFF
mdefine_line|#define&t;HPET_IE_OFF&t;_IO(&squot;h&squot;, 0x02)&t;/* interrupt off */
DECL|macro|HPET_INFO
mdefine_line|#define&t;HPET_INFO&t;_IOR(&squot;h&squot;, 0x03, struct hpet_info)
DECL|macro|HPET_EPI
mdefine_line|#define&t;HPET_EPI&t;_IO(&squot;h&squot;, 0x04)&t;/* enable periodic */
DECL|macro|HPET_DPI
mdefine_line|#define&t;HPET_DPI&t;_IO(&squot;h&squot;, 0x05)&t;/* disable periodic */
DECL|macro|HPET_IRQFREQ
mdefine_line|#define&t;HPET_IRQFREQ&t;_IOW(&squot;h&squot;, 0x6, unsigned long)&t;/* IRQFREQ usec */
multiline_comment|/*&n; * exported interfaces&n; */
DECL|struct|hpet_task
r_struct
id|hpet_task
(brace
DECL|member|ht_func
r_void
(paren
op_star
id|ht_func
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|ht_data
r_void
op_star
id|ht_data
suffix:semicolon
DECL|member|ht_opaque
r_void
op_star
id|ht_opaque
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HD_STATE
mdefine_line|#define&t;HD_STATE(HD, TIMER)&t;(HD)-&gt;hd_state |= (1 &lt;&lt; TIMER)
DECL|struct|hpet_data
r_struct
id|hpet_data
(brace
DECL|member|hd_address
r_int
r_int
id|hd_address
suffix:semicolon
DECL|member|hd_nirqs
r_int
r_int
id|hd_nirqs
suffix:semicolon
DECL|member|hd_flags
r_int
r_int
id|hd_flags
suffix:semicolon
DECL|member|hd_state
r_int
r_int
id|hd_state
suffix:semicolon
multiline_comment|/* timer allocated */
DECL|member|hd_irq
r_int
r_int
id|hd_irq
(braket
id|HPET_MAX_TIMERS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HPET_DATA_PLATFORM
mdefine_line|#define&t;HPET_DATA_PLATFORM&t;0x0001&t;/* platform call to hpet_alloc */
r_int
id|hpet_alloc
c_func
(paren
r_struct
id|hpet_data
op_star
)paren
suffix:semicolon
r_int
id|hpet_register
c_func
(paren
r_struct
id|hpet_task
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|hpet_unregister
c_func
(paren
r_struct
id|hpet_task
op_star
)paren
suffix:semicolon
r_int
id|hpet_control
c_func
(paren
r_struct
id|hpet_task
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* !__HPET__ */
eof
