multiline_comment|/*&n; * board initialization should put one of these into dev-&gt;platform_data&n; * and place the sl811hs onto platform_bus named &quot;sl811-hcd&quot;.&n; */
DECL|struct|sl811_platform_data
r_struct
id|sl811_platform_data
(brace
DECL|member|can_wakeup
r_int
id|can_wakeup
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* given port_power, msec/2 after power on till power good */
DECL|member|potpg
id|u8
id|potpg
suffix:semicolon
multiline_comment|/* mA/2 power supplied on this port (max = default = 250) */
DECL|member|power
id|u8
id|power
suffix:semicolon
multiline_comment|/* sl811 relies on an external source of VBUS current */
DECL|member|port_power
r_void
(paren
op_star
id|port_power
)paren
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|is_on
)paren
suffix:semicolon
multiline_comment|/* pulse sl811 nRST (probably with a GPIO) */
DECL|member|reset
r_void
(paren
op_star
id|reset
)paren
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
singleline_comment|// some boards need something like these:
singleline_comment|// int &t;&t;(*check_overcurrent)(struct device *dev);
singleline_comment|// void &t;(*clock_enable)(struct device *dev, int is_on);
)brace
suffix:semicolon
eof
