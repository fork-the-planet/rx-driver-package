/*
* Copyright (c) 2014(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : r_usb_extern.h
 * Description  : USB common header
 *********************************************************************************************************************/
/**********************************************************************************************************************
* History   : DD.MM.YYYY Version Description
*           : 01.09.2014 1.00    First Release
*           : 01.06.2015 1.01    Added RX231.
*           : 30.11.2018 1.10    Supporting Smart Configurator
*           : 31.05.2019 1.11    Added support for GNUC and ICCRX.
*           : 30.06.2019 1.12    RX23W is added.
*           : 30.06.2020 1.20    Added support for RTOS.
*           : 30.04.2024 1.30    Added support for RX261.
*           : 20.03.2025 1.31    Changed the disclaimer.
 ***********************************************************************************************************************/

#ifndef R_USB_EXTERN_H
#define R_USB_EXTERN_H

/*****************************************************************************
 Exported global variables
 ******************************************************************************/
/* r_usb_usbif_api.c */
extern uint16_t         g_usb_cstd_usb_mode;                        /* USB mode HOST/PERI */
extern uint16_t         g_usb_cstd_open_class;

#if (BSP_CFG_RTOS_USED != 0)                                        /* RT-OS */
extern usb_ctrl_t       g_usb_cstd_event[];
extern usb_callback_t   *g_usb_apl_callback;
extern rtos_task_id_t   g_usb_default_apl_task_id;
#else /* (BSP_CFG_RTOS_USED != 0) */
extern usb_event_t      g_usb_cstd_event;
#endif /* (BSP_CFG_RTOS_USED != 0) */

/* r_usb_cdataio.c */
extern usb_pipe_table_t g_usb_cstd_pipe_tbl[USB_MAXPIPE_NUM+1];
extern uint16_t     g_usb_cstd_bemp_skip[USB_MAX_PIPE_NO + 1u];

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
/* r_usb_usbif_api.c */
extern usb_putr_t   g_usb_pstd_data[USB_MAXPIPE_NUM + 1];
extern uint16_t     g_usb_pstd_speed;

/* r_usb_cdataio.c */
extern usb_putr_t   *gp_usb_pstd_pipe[USB_MAX_PIPE_NO + 1u];
extern uint32_t     g_usb_pstd_data_cnt[USB_MAX_PIPE_NO + 1u]; /* PIPEn Buffer counter */
extern uint8_t      *gp_usb_pstd_data[USB_MAX_PIPE_NO + 1u];    /* PIPEn Buffer pointer(8bit) */

/* r_usb_pdriver.c */
extern uint16_t     g_usb_pstd_is_stall_pipe[USB_MAX_PIPE_NO + 1u]; /* Stall Pipe info */
extern usb_cb_t     g_usb_pstd_stall_cb;      /* Stall Callback function */
extern uint16_t     g_usb_pstd_config_no;     /* Configuration Number */
extern uint16_t     g_usb_pstd_alt_no[];      /* Alternate */
extern uint16_t     g_usb_pstd_remote_wakeup; /* Remote Wake up Enable Flag */
extern uint16_t     g_usb_pstd_remote_wakeup_state;                /* Result for Remote wake up */
extern uint16_t     g_usb_pstd_eptbl_index[2][USB_MAX_EP_NO + 1u]; /* Index of Endpoint Information table */
extern uint16_t     g_usb_pstd_req_type;     /* Request type */
extern uint16_t     g_usb_pstd_req_value;    /* Value */
extern uint16_t     g_usb_pstd_req_index;    /* Index */
extern uint16_t     g_usb_pstd_req_length;   /* Length */
extern usb_pcdreg_t g_usb_pstd_driver;       /* Driver registration */
extern usb_setup_t  g_usb_pstd_req_reg;      /* Request variable */
extern usb_int_t    g_usb_pstd_usb_int;
extern uint16_t     g_usb_pstd_pipe0_request;
extern uint16_t     g_usb_pstd_std_request;
extern uint16_t     g_usb_pstd_is_connected; /* Peri CDC application enable */

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST
#if (BSP_CFG_RTOS_USED != 0)                                    /* RTOS */
/* r_usb_hdriver.c */
extern usb_utr_t *gp_usb_hstd_pipe[USB_MAX_PIPE_NO + 1u];       /* Message pipe */
extern uint8_t  *gp_usb_hstd_data_ptr[USB_MAX_PIPE_NO + 1u];    /* PIPEn Buffer pointer(8bit) */
extern uint32_t g_usb_hstd_data_cnt[USB_MAX_PIPE_NO + 1u];      /* PIPEn Buffer counter */
extern uint16_t g_usb_hstd_ignore_cnt[USB_MAX_PIPE_NO + 1u];    /* Ignore count */
extern usb_hcdreg_t g_usb_hstd_device_drv;                      /* Device driver (registration) */
extern uint8_t  g_usb_hcd_remote_wakeup;
extern uint16_t g_usb_hstd_ctsq;                                /* Control transfer stage management */
extern uint16_t g_usb_hstd_mgr_mode;                            /* Manager mode */
extern uint16_t g_usb_hstd_dcp_register;                        /* DEVSEL & DCPMAXP (Multiple device) */
extern uint16_t g_usb_hstd_device_speed;                        /* Reset handshake result */
extern usb_hcddevinf_t  g_usb_hcd_dev_info;                     /* device address, status, config, speed, */
extern usb_hcdreg_t     g_usb_hcd_driver;                       /* Device driver (registration) */
extern rtos_task_id_t   g_usb_hstd_change_device_state_task_id;

/* r_usb_hmanager.c */
extern uint16_t g_usb_hstd_config_descriptor[USB_CONFIGSIZE / 2u];
extern uint8_t  g_usb_hstd_class_data[CLSDATASIZE];
extern uint16_t g_usb_hstd_setup_data[5];

#else /* (BSP_CFG_RTOS_USED != 0) */
/* r_usb_hstdfunction.c */
extern usb_pipe_no_t    g_usb_hstd_current_pipe;               /* Pipe number */
extern usb_hutr_t      *gp_usb_hstd_pipe[];                    /* Message pipe */
extern usb_leng_t       g_usb_hstd_data_cnt[];                 /* PIPEn Buffer counter */
extern uint8_t         *gp_usb_hstd_data_ptr[];                /* PIPEn Buffer pointer(8bit) */
extern usb_intinfo_t    g_usb_hstd_int_msg[];
extern uint8_t          g_usb_hstd_int_msg_cnt;
extern usb_msg_t       *g_usb_hstd_msg_tbl_sch[][USB_TABLEMAX];
extern uint8_t          g_usb_hstd_read_sch[];
extern uint8_t          g_usb_hstd_write_sch[];
extern usb_tskinfo_t    g_usb_hstd_block[];
extern usb_waitinfo_t   g_usb_hstd_wait_msg_sch[];
extern usb_waitque_t    g_usb_hstd_wait_que_sch[];
extern usb_msg_t       *gp_usb_hstd_next_addr_sch;
extern uint8_t          g_usb_hstd_next_id_sch;                /* Priority Counter */
extern uint8_t          g_usb_next_read_ptr_sch;               /* Priority Table Reading pointer */
extern uint8_t          g_usb_hstd_device_descriptor[USB_DEVICESIZE];

/* r_usb_hdriver.c */
extern uint8_t          g_usb_hstd_devspd;                     /* Reset handshake result */
extern uint8_t          g_usb_hstd_cfg_descriptor[USB_CONFIGSIZE];
extern usb_addr_t       g_usb_hcd_devaddr;                     /* Device address */
extern uint8_t          g_usb_hstd_ctsq;                        /* Control transfer stage management */
extern usb_port_t       g_usb_hstd_hcd_port;
extern usb_hcdreg_t     g_usb_hcd_driver;                      /* Device driver (registration) */
extern usb_hcddevinf_t  g_usb_hcd_dev_info;                    /* device address, status, config, speed, */
extern uint8_t          g_usb_hcd_remote_wakeup;
extern usb_tskinfo_t   *gp_usb_hstd_hcd_message;               /* Hcd Task receive message */
extern uint16_t         g_usb_hstd_hcd_dcp_mxps[USB_MAXDEVADDR+1u];    /* DEVSEL & DCPMAXP (Multiple device) */

/* r_usb_hmanager.c */
extern usb_addr_t       g_usb_mgr_devaddr;                     /* Device address */
extern uint8_t          g_usb_mgr_seq;
extern uint8_t          g_usb_mgr_seq_mode;
extern usb_port_t       g_usb_mgr_port;
extern usb_hutr_t       g_usb_mgr_ctrl_msg;
extern usb_tskinfo_t   *gp_usb_mgr_msg;                        /* Mgr Task receive message */

/* r_usb_usbif_api.c */
extern uint16_t         g_usb_hstd_is_susp_resm;
extern usb_hutr_t       g_usb_hstd_data[USB_MAXPIPE_NUM + 1];

/* r_usb_cdataio.c */
extern uint16_t         g_usb_hstd_pipe_request[USB_MAX_PIPE_NO + 1u];

#if defined(USB_CFG_HHID_USE)
extern uint8_t         *gp_usb_hstd_interface_tbl;
#endif /* defined(USB_CFG_HHID_USE) */

#endif /* (BSP_CFG_RTOS_USED != 0) */

/* r_usb_hsignal.c */
#if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
extern uint16_t         g_usb_hstd_response_counter;
#endif /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

#if defined(USB_CFG_HMSC_USE)
extern uint8_t          g_usb_hmsc_sub_class;
#endif /* defined(USB_CFG_HMSC_USE) */

#endif /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if USB_CFG_BC == USB_CFG_ENABLE
#if (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI
/* r_usb_pbc.c */
extern uint16_t        g_usb_pstd_bc_detect;
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
/* r_usb_hbc.c */
extern usb_bc_status_t  g_usb_hstd_bc;
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
extern void       (*gp_usb_hstd_bc_func[USB_BC_STATE_MAX][USB_BC_EVENT_MAX])(void);
#endif  /* USB_CFG_BC == USB_CFG_ENABLE */

/*****************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/
/* r_usb_rx_mcu.c */
usb_err_t usb_module_start (void);
usb_err_t usb_module_stop (void);
void      usb_cpu_delay_xms (uint16_t time);
void      usb_cpu_delay_1us (uint16_t time);
void      usb_cpu_usbint_init (void);
uint16_t  usb_chattaring (uint16_t *p_syssts);
void      usb_cpu_int_enable(void);
void      usb_cpu_int_disable(void);

/* r_usb_cdataio.c */
void      usb_cstd_debug_hook (uint16_t error_code);
usb_er_t  usb_cstd_ctrl_receive (usb_ctrl_t *p_ctrl, uint8_t  *p_buf, uint32_t size);
usb_er_t  usb_cstd_ctrl_send (usb_ctrl_t *p_ctrl, uint8_t  *p_buf, uint32_t size);
usb_er_t  usb_cstd_ctrl_stop (void);
usb_er_t  usb_cstd_data_read (usb_ctrl_t *p_ctrl, uint8_t  *p_buf, uint32_t size);
usb_er_t  usb_cstd_data_write (usb_ctrl_t *p_ctrl, uint8_t  *p_buf, uint32_t size);
usb_er_t  usb_cstd_data_stop (usb_ctrl_t *p_ctrl, uint16_t type);
uint8_t   usb_cstd_get_usepipe (usb_ctrl_t *p_ctrl, uint8_t dir);
uint16_t  usb_cstd_pipe_to_fport (uint16_t pipe);
void      usb_cstd_pipe_table_clear (void);
void      usb_cstd_pipe_reg_set (void);
void      usb_cstd_pipe_reg_clear (void);

/* r_usb_clibusbip.c */
void      usb_cstd_nrdy_enable (uint16_t pipe);
uint16_t  usb_cstd_get_pid (uint16_t pipe);
uint16_t  usb_cstd_get_pipe_dir (uint16_t pipe);
uint16_t  usb_cstd_get_pipe_type (uint16_t pipe);
void      usb_cstd_do_aclrm (uint16_t pipe);
void      usb_cstd_set_buf (uint16_t pipe);
void      usb_cstd_clr_stall (uint16_t pipe);
uint16_t  usb_cstd_port_speed (void);
void      usb_cstd_set_event (usb_status_t event, usb_ctrl_t *p_ctrl);
void      usb_cstd_usb_task (void);
void      usb_rtos_delete_msg_submbx (usb_utr_t *p_ptr, uint16_t usb_mode);
void      usb_rtos_resend_msg_to_submbx (uint16_t pipe, uint16_t usb_mode);
void      usb_rtos_send_msg_to_submbx (usb_utr_t *p_ptr, uint16_t pipe_no, uint16_t usb_mode);

#if (BSP_CFG_RTOS_USED != 0)    /* RTOS */
/* r_usb_hdriver_rtos.c */
usb_er_t    usb_hstd_transfer_start_req (usb_utr_t *ptr);
void        usb_hstd_device_resume (uint16_t devaddr);
usb_er_t    usb_hstd_hcd_snd_mbx (uint16_t msginfo, uint16_t dat, uint16_t *adr, usb_cb_t callback);
void        usb_hstd_mgr_snd_mbx (uint16_t msginfo, uint16_t dat, uint16_t res);
void        usb_hstd_hcd_rel_mpl (usb_utr_t *ptr, uint16_t n);
void        usb_hstd_suspend (usb_utr_t *ptr);
usb_er_t    usb_hstd_clr_stall (uint16_t pipe, usb_cb_t complete);
void        usb_hstd_hcd_task (usb_vp_int_t stacd);
usb_er_t    usb_hstd_transfer_end (uint16_t pipe, uint16_t status);
void        usb_hstd_driver_registration (usb_hcdreg_t *callback);
void        usb_hstd_driver_release (uint8_t devclass);
usb_er_t    usb_hstd_change_device_state (usb_cb_t complete, uint16_t msginfo, uint16_t member);
usb_err_t   usb_hstd_hcd_open (void);
void        usb_host_registration (void);
usb_er_t    usb_hstd_transfer_start (usb_utr_t *ptr);
void        usb_hstd_connect_err_event_set(void);
#if defined(USB_CFG_HVND_USE)
void        usb_hvnd_registration (void);
void        usb_hvnd_read_complete (usb_utr_t *ptr, uint16_t data1, uint16_t data2);
void        usb_hvnd_write_complete (usb_utr_t *ptr, uint16_t data1, uint16_t data2);

#endif /* defined(USB_CFG_HVND_USE) */

/* r_usb_hlibusbip_rtos.c */
void        usb_hstd_bchg_enable (void);
void        usb_hstd_bchg_disable (void);
void        usb_hstd_set_uact (void);
void        usb_hstd_ovrcr_disable (void);
void        usb_hstd_attch_disable (void);
void        usb_hstd_detach_enable (void);
void        usb_hstd_detach_disable (void);
void        usb_hstd_bus_int_disable (void);
void        usb_hstd_send_start (uint16_t pipe);
void        usb_hstd_receive_start (uint16_t pipe);
void        usb_hstd_data_end (uint16_t pipe, uint16_t status);
void        usb_hstd_brdy_pipe_process(uint16_t bitsts);
void        usb_hstd_nrdy_pipe_process(uint16_t bitsts);
void        usb_hstd_bemp_pipe_process(uint16_t bitsts);
uint16_t    usb_hstd_devaddr_to_speed (uint16_t addr);
uint16_t    usb_hstd_pipe_to_devsel (uint16_t pipe);
uint8_t     usb_cstd_pipe_table_set (uint16_t usb_class, uint8_t *p_descriptor);
uint8_t     usb_hstd_get_pipe_no (uint16_t usb_class, uint8_t type, uint8_t dir);
uint16_t    usb_hstd_get_pipe_peri_value (uint8_t binterval);

/* r_usb_hmanager_rtos.c */
void       usb_hstd_submit_result (usb_utr_t *ptr, uint16_t data1, uint16_t data2);
void       usb_hstd_enum_set_address (uint16_t addr, uint16_t setaddr);
void       usb_hstd_enum_get_descriptor (uint16_t addr, uint16_t cnt_value);
void       usb_hstd_enum_set_configuration (uint16_t addr, uint16_t confnum);
void       usb_hstd_enum_dummy_request (uint16_t addr, uint16_t CntValue);
void       usb_hstd_mgr_suspend (usb_utr_t *ptr, uint16_t info);
void       usb_hstd_mgr_reset (usb_utr_t *ptr, uint16_t addr);
void       usb_hstd_mgr_resume (usb_utr_t *ptr, uint16_t info);
uint16_t   usb_hstd_get_config_desc (uint16_t addr, uint16_t length);
void       usb_hstd_mgr_task (usb_vp_int_t stacd);
usb_er_t   usb_hstd_mgr_open (void);

/* r_usb_hsignal_rtos.c */
void        usb_hstd_interrupt_process (usb_utr_t *ptr);
void        usb_hstd_detach_control (void);
void        usb_hstd_attach_control (uint16_t result);
void        usb_hstd_bchg_process (void);
void        usb_hstd_vbus_control_on(void);
void        usb_hstd_vbus_control_off(void);
void        usb_hstd_suspend_process (void);

/* r_usb_hstdfunction_rtos.c */
void        usb_hstd_buf_to_fifo (uint16_t pipe, uint16_t  useport);
uint16_t    usb_cstd_buf_to_cfifo (uint16_t pipe, uint16_t pipemode);
void        usb_hstd_fifo_to_buf (uint16_t pipe, uint16_t  useport);
uint16_t    usb_hstd_cfifo_to_buf (uint16_t pipe, uint16_t  useport);
uint16_t    usb_hstd_control_write_start (uint32_t bsize, uint8_t  *table);
void        usb_hstd_control_read_start (uint32_t bsize, uint8_t  *table);
void        usb_hstd_status_start (void);
void        usb_hstd_control_end (uint16_t status);
void        usb_hstd_setup_start (void);
void        usb_hstd_brdy_pipe (uint16_t bitsts);
void        usb_hstd_nrdy_pipe (uint16_t bitsts);
void        usb_hstd_bemp_pipe (uint16_t bitsts);
uint16_t    usb_hstd_check_attach (void);
uint16_t    usb_hstd_set_feature (uint16_t addr, uint16_t epnum);
usb_er_t    usb_hstd_clear_feature (uint16_t epnum, usb_cb_t complete);
uint8_t     usb_hstd_pipe_to_epadr (uint16_t pipe);
void        usb_hstd_status_notification (uint16_t result);
void        usb_hstd_status_result (usb_utr_t *ptr, uint16_t data1, uint16_t result);
void        usb_hclass_request_complete (usb_utr_t *mess, uint16_t devadr, uint16_t data2);
void        usb_hstd_suspend_complete (usb_utr_t *ptr, uint16_t data1, uint16_t data2);
void        usb_hstd_resume_complete (usb_utr_t *ptr, uint16_t data1, uint16_t data2);
uint16_t    usb_hstd_get_string_desc (uint16_t string);
void        usb_hstd_dummy_function (usb_utr_t *ptr, uint16_t data1, uint16_t data2);
void        usb_hstd_ls_connect_function (void);
void        usb_hstd_ovrcr0function (void);
void        usb_hstd_driver_init (void);
void        usb_class_driver_start (void);
void        class_trans_result(usb_utr_t *ptr, uint16_t data1, uint16_t data2);
uint16_t    class_trans_wait_tmo(uint16_t tmo);
uint16_t    usb_hstd_do_command (void);

/* r_usb_hreg_abs_rtos.c */
void      usb_hstd_check_interrupt_source (usb_utr_t *ptr);
void      usb_hstd_interrupt_handler (void);
void      usb_hstd_chk_clk (void);
void      usb_hstd_detach_process (void);
void      usb_hstd_read_lnst (uint16_t *buf);
void      usb_hstd_attach_process (void);
void      usb_hstd_bus_reset (void);
void      usb_hstd_resume_process (void);
uint8_t  *usb_hstd_write_fifo (uint16_t count, uint16_t pipemode, uint8_t  *write_p);
uint8_t  *usb_hstd_read_fifo (uint16_t count, uint16_t pipemode, uint8_t  *read_p);
void      usb_hstd_forced_termination (uint16_t pipe, uint16_t status);
void      usb_hstd_set_devaddx_register (uint16_t addr, uint16_t speed);
void      usb_hstd_nrdy_endprocess (uint16_t pipe);

#else  /* (BSP_CFG_RTOS_USED != 0) */

/* r_usb_hdriver.c */
usb_er_t    usb_hstd_transfer_start(usb_hutr_t *p_utr_table);
void        usb_hstd_hcd_task(void);
void        usb_hstd_driver_registration(usb_hcdreg_t *p_registinfo);
void        usb_hstd_driver_release(uint8_t devclass);
usb_er_t    usb_hstd_change_device_state(usb_cbinfo_t complete, usb_strct_t msginfo, usb_strct_t keyword);
#if defined(USB_CFG_HVND_USE)
void        usb_hvnd_registration (void);
uint16_t    usb_hvnd_pipe_info(uint8_t *table, uint16_t length);
#endif /* defined(USB_CFG_HVND_USE) */

/* r_usb_hlibusbip.c */
void        usb_hstd_bchg_enable(void);
void        usb_hstd_bchg_disable(void);
void        usb_hstd_set_uact(void);
void        usb_hstd_ovrcr_disable(void);
void        usb_hstd_attch_disable(void);
void        usb_hstd_detach_enable(void);
void        usb_hstd_detach_disable(void);
void        usb_hstd_bus_int_disable(void);
void        usb_hstd_send_start(void);
void        usb_hstd_receive_start(void);
void        usb_hstd_data_end(uint16_t status);
void        usb_hstd_brdy_pipe_process(uint16_t bitsts);
void        usb_hstd_nrdy_pipe_process(uint16_t bitsts);
void        usb_hstd_bemp_pipe_process(uint16_t bitsts);
uint8_t     usb_cstd_pipe_table_set (uint16_t usb_class, uint8_t *p_descriptor);
uint8_t     usb_hstd_get_pipe_no (uint16_t usb_class, uint8_t type, uint8_t dir);
uint16_t    usb_hstd_get_pipe_peri_value (uint8_t binterval);

/* r_usb_hmanager.c */
void             usb_hstd_mgr_task(void);
void        usb_hstd_return_enu_mgr(uint16_t cls_result);

/* r_usb_hscheduler.c */
uint8_t     usb_hstd_scheduler(void);
usb_er_t    usb_hstd_rec_msg( uint8_t id, usb_msg_t** pp_mess );
usb_er_t    usb_hstd_snd_msg( uint8_t id, usb_msg_t* p_mess );
usb_er_t    usb_hstd_isnd_msg( uint8_t id, usb_msg_t* p_mess );
usb_er_t    usb_hstd_wai_msg( uint8_t id, usb_msg_t* p_mess, uint16_t count );
usb_er_t    usb_hstd_pget_send( uint8_t id, usb_strct_t msginfo, usb_cbinfo_t complete, usb_strct_t keyword );
usb_er_t    usb_hstd_rel_blk( uint8_t blk_num );

/* r_usb_hsignal.c */
void        usb_hstd_interrupt_process(void);
void        usb_hstd_detach_control(void);
void        usb_hstd_attach_control(void);
void        usb_hstd_vbus_control_on(void);
void        usb_hstd_vbus_control_off(void);
void        usb_hstd_suspend_process(void);

/* r_usb_hstdfunction.c */
void        usb_cstd_init_library(void);
void        usb_hstd_buf_to_fifo(uint16_t useport);
void        usb_hstd_fifo_to_buf(void);
usb_port_t  usb_hstd_devaddr_to_port(void);
usb_er_t    usb_hstd_get_descriptor(uint16_t CntValue);
usb_er_t    usb_hstd_set_configuration(void);
void        usb_hstd_clr_device_info(void);     /* Initialized g_usb_HcdDevInfo */
void        usb_hstd_update_devinfo(uint8_t state);
void        usb_hstd_update_devstate(uint8_t state);
uint16_t    usb_hstd_control_write_start(void);
void        usb_hstd_control_read_start(void);
void        usb_hstd_status_start(void);
void        usb_hstd_control_end(usb_strct_t status);
void        usb_hstd_setup_start(void);
void        usb_hstd_brdy_pipe(void);
void        usb_hstd_nrdy_pipe(void);
void        usb_hstd_bemp_pipe(void);
uint8_t     usb_hstd_devaddr_to_speed(void);
uint8_t     usb_hstd_check_attach(void);
usb_er_t    usb_hstd_set_feature(uint16_t epnum);
usb_er_t    usb_hstd_clear_feature(uint16_t epnum);
uint8_t     usb_hstd_pipe_to_epadr (uint16_t pipe);
void        usb_hstd_pipe_to_hcddevaddr(void);
usb_addr_t  usb_hstd_pipe_to_addr(void);
void        usb_hstd_status_notification(usb_strct_t msginfo, usb_strct_t keyword);
usb_er_t    usb_hstd_status_change(usb_strct_t msginfo, usb_strct_t keyword);
void        usb_hstd_status_result(usb_strct_t status);
void        usb_hstd_transferend_check(usb_strct_t status);
void        usb_hstd_driver_reg_init(void);  /* Initialized g_usb_HcdDriver */
void        usb_hstd_setup_disable(void);
void        usb_hstd_port_enable(void);
void        usb_hclass_request_complete (usb_hutr_t *p_mess);
void        usb_hstd_suspend_complete (uint16_t data1, uint16_t data2);
void        usb_hstd_resume_complete (uint16_t data1, uint16_t data2);
void        usb_hstd_read_complete (usb_hutr_t *p_mess);
void        usb_hstd_write_complete (usb_hutr_t *p_mess);
void        usb_hstd_host_registration (void);
void        usb_hstd_class_check(uint8_t **pp_table);
void        usb_hstd_class_enumeration(usb_tskinfo_t *p_mess);
void        usb_hstd_class_task (void);
void        usb_hstd_connect_err_event_set(void);
void        usb_hstd_dummy_function(usb_hutr_t *p_utr, uint16_t data1, uint16_t data2);
void        usb_hstd_hw_start(void);
void        usb_hstd_class_driver_start (void);
void        usb_hstd_driver_init(void);
usb_er_t    usb_hstd_set_asddress(void);

/* r_usb_hreg_abs.c */
void      usb_hstd_check_interrupt_source(usb_strct_t *p_inttype, uint16_t *p_bitsts);
void      usb_hstd_interrupt_handler(void);
void      usb_hstd_detach_process(void);
void      usb_hstd_read_lnst(uint16_t *p_buf);
void      usb_hstd_attach_process(void);
void      usb_hstd_bus_reset(void);
void      usb_hstd_resume_process(void);
void      usb_hstd_forced_termination(uint16_t status);
void      usb_hstd_set_devaddx_register(uint8_t usbspd);
uint16_t  usb_hstd_get_devaddx_register(void);

#endif /* (BSP_CFG_RTOS_USED != 0) */

/* r_usb_creg_abs.c */
uint16_t  usb_cstd_get_maxpacket_size (uint16_t pipe);
void      usb_cstd_set_pipe_config (uint16_t pipe);
void      usb_cstd_clr_pipe_config (uint16_t pipeno);
void      usb_cstd_set_nak (uint16_t pipe);
uint16_t  usb_cstd_is_set_frdy (uint16_t pipe, uint16_t fifosel, uint16_t isel);
void      usb_cstd_chg_curpipe (uint16_t pipe, uint16_t fifosel, uint16_t isel);
void      usb_cstd_set_transaction (uint16_t pipe, uint16_t trncnt);
void      usb_cstd_clr_transaction (uint16_t pipe);

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

/* r_usb_plibusbip.c */
void      usb_pstd_send_start (uint16_t pipe);
void      usb_pstd_buf_to_fifo (uint16_t pipe, uint16_t  useport);
uint16_t  usb_pstd_write_data (uint16_t pipe, uint16_t pipemode);
void      usb_pstd_receive_start (uint16_t pipe);
void      usb_pstd_fifo_to_buf (uint16_t pipe, uint16_t  useport);
uint16_t  usb_pstd_read_data (uint16_t pipe, uint16_t pipemode);
void      usb_pstd_data_end (uint16_t pipe, uint16_t status);
uint8_t   usb_pstd_set_pipe_table (uint8_t  *p_descriptor, uint8_t class);
void      usb_pstd_set_pipe_reg (void);
uint8_t   usb_pstd_get_pipe_no (uint8_t type, uint8_t dir, uint8_t class);
uint16_t  usb_pstd_epadr_to_pipe (uint16_t dir_ep);
void      usb_pstd_bemp_pipe_process(uint16_t bitsts);
void      usb_pstd_brdy_pipe_process(uint16_t bitsts);
void      usb_pstd_nrdy_pipe_process(uint16_t bitsts);


/* r_usb_pinthandler_usbip0.c */
void      usb_pstd_usb_handler (void);

/* r_usb_pdriver.c */
#if (BSP_CFG_RTOS_USED == 4)    /* Renesas RI600V4 & RI600PX */
/* r_usb_pdriver.c */
void usb_pstd_pcd_task( VP_INT );
#else /* (BSP_CFG_RTOS_USED == 4) */
void      usb_pstd_pcd_task (void);
#endif /* (BSP_CFG_RTOS_USED == 4) */
usb_er_t  usb_pstd_set_submitutr (usb_putr_t * p_utrmsg);
void      usb_pstd_clr_alt (void);
void      usb_pstd_clr_mem (void);
void      usb_pstd_set_config_no (uint16_t Value);
void      usb_pstd_clr_eptbl_index (void);
uint16_t  usb_pstd_get_interface_no (void);
uint16_t  usb_pstd_get_alternate_no (uint16_t int_num);
void      usb_pstd_set_eptbl_index (uint16_t int_num, uint16_t alt_num);
uint16_t  usb_pstd_chk_remote (void);
uint8_t   usb_pstd_get_current_power (void);
usb_er_t  usb_pstd_transfer_start (usb_putr_t *p_utr);
usb_er_t  usb_pstd_transfer_end (uint16_t pipe);
void      usb_pstd_change_device_state (uint16_t state, uint16_t keyword, usb_cb_t complete);
void      usb_pstd_driver_registration (usb_pcdreg_t *p_callback);
void      usb_pstd_driver_release (void);
void      usb_pstd_dummy_function (usb_putr_t *p_utr, uint16_t data1, uint16_t data2);
void      usb_pstd_dummy_trn (usb_setup_t * p_req, uint16_t ctsq);

/* r_usb_pcontrolrw.c */
uint16_t  usb_pstd_ctrl_read (uint32_t bsize, uint8_t  *p_table);
void      usb_pstd_ctrl_write (uint32_t bsize, uint8_t  *p_table);
void      usb_pstd_ctrl_end (uint16_t status);

/* r_usb_pintfifo.c */
void      usb_pstd_brdy_pipe (uint16_t bitsts);
void      usb_pstd_nrdy_pipe (uint16_t bitsts);
void      usb_pstd_bemp_pipe (uint16_t bitsts);

/* r_usb_pstdfunction.c */
void      usb_pstd_busreset_function (void);
void      usb_pstd_suspend_function (void);
void      usb_pstd_driver_init(usb_cfg_t *p_cfg);
uint8_t   usb_pstd_get_open_class (void);

/* r_usb_preg_abs.c */
void      usb_pstd_interrupt_handler (uint16_t * p_type, uint16_t * p_status);
void      usb_pstd_save_request (void);
uint16_t  usb_pstd_chk_configured (void);
void      usb_pstd_bus_reset (void);
void      usb_pstd_remote_wakeup (void);
void      usb_pstd_attach_process (void);
void      usb_pstd_detach_process (void);
void      usb_pstd_suspend_process (void);
void      usb_pstd_resume_process (void);
uint16_t  usb_pstd_chk_vbsts (void);
void      usb_pstd_set_stall (uint16_t pipe);
void      usb_pstd_set_stall_pipe0 (void);

/* r_usb_pstdrequest.c */
void      usb_pstd_stand_req0 (void);
void      usb_pstd_stand_req1 (void);
void      usb_pstd_stand_req2 (void);
void      usb_pstd_stand_req3 (void);
void      usb_pstd_stand_req4 (void);
void      usb_pstd_stand_req5 (void);
void      usb_pstd_set_feature_function (void);

/* peri_processing.c */
void      usb_pstd_registration(usb_cfg_t *p_cfg);
void      usb_pstd_devdefault (usb_putr_t *p_utr, uint16_t mode, uint16_t data2);
uint16_t  usb_pstd_pipe_info (uint8_t  *p_table, uint16_t length);
void      usb_pstd_configured (usb_putr_t *p_utr, uint16_t data1, uint16_t data2);
void      usb_pstd_detach (usb_putr_t *p_utr, uint16_t data1, uint16_t data2);
void      usb_pstd_suspended(usb_putr_t *p_utr, uint16_t data1, uint16_t data2);
void      usb_pstd_resume(usb_putr_t *p_utr, uint16_t data1, uint16_t data2);
void      usb_pstd_interface(usb_putr_t *p_utr, uint16_t data1, uint16_t data2);
void      usb_pstd_class_request(usb_setup_t *p_req, uint16_t ctsq);
void      usb_pstd_class_request_ioss (usb_setup_t *p_req);
void      usb_pstd_class_request_rwds (usb_setup_t * p_req);
void      usb_pstd_other_request (usb_setup_t *p_req);
void      usb_pstd_class_request_wnss (usb_setup_t *p_req);
void      usb_pstd_class_request_rss (usb_setup_t *p_req);
void      usb_pstd_class_request_wss (usb_setup_t *p_req);

/* r_usb_preg_abs.c */
uint8_t  *usb_pstd_write_fifo (uint16_t count, uint16_t pipemode, uint8_t  * p_buff);
uint8_t  *usb_pstd_read_fifo (uint16_t count, uint16_t pipemode, uint8_t  * p_buff);
void      usb_pstd_forced_termination (uint16_t pipe, uint16_t status);
void      usb_pstd_stop_clock (void);

#endif/* ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */

#if defined(USB_CFG_HCDC_USE)
void      usb_hcdc_registration (void);     /* driver registration */
#if (BSP_CFG_RTOS_USED != 0)    /* RTOS */
void      usb_hcdc_read_complete (usb_utr_t *mess, uint16_t devadr, uint16_t data2);
void      usb_hcdc_write_complete (usb_utr_t *mess, uint16_t devadr, uint16_t data2);
void      usb_hcdc_driver_start (void);
#else  /* (BSP_CFG_RTOS_USED != 0) */
uint16_t  usb_hcdc_pipe_info(uint8_t *table, uint16_t length);
#endif /* (BSP_CFG_RTOS_USED != 0) */
#endif /* defined(USB_CFG_HCDC_USE) */

#if defined(USB_CFG_HHID_USE)
void      usb_hhid_registration (void);
#if (BSP_CFG_RTOS_USED != 0)    /* RTOS */
void      usb_hhid_read_complete(usb_utr_t *mess, uint16_t devadr, uint16_t data2);
void      usb_hhid_write_complete(usb_utr_t *mess, uint16_t devadr, uint16_t data2);
void      usb_hhid_driver_start (void);
#else  /* (BSP_CFG_RTOS_USED != 0) */
uint16_t  usb_hhid_pipe_info(uint8_t *table, uint16_t length);
#endif /* (BSP_CFG_RTOS_USED != 0) */
#endif /* defined(USB_CFG_HHID_USE) */

#if defined(USB_CFG_HMSC_USE)
void      usb_hmsc_registration(void);
void      usb_hmsc_strg_drive_task (void);
uint16_t  usb_hmsc_pipe_info(uint8_t *table, uint16_t length);
#if (BSP_CFG_RTOS_USED != 0)    /* RTOS */
void      usb_hmsc_driver_start (void);
void      usb_hmsc_storage_driver_start (void);
void      usb_hmsc_task (void);
#else  /* (BSP_CFG_RTOS_USED != 0) */
void      usb_hmsc_process (usb_tskinfo_t *mess);
#endif /* (BSP_CFG_RTOS_USED != 0) */
#endif /* defined(USB_CFG_HMSC_USE) */

#if defined(USB_CFG_PVND_USE)
void        usb_pstd_read_complete(usb_putr_t *p_mess, uint16_t data1, uint16_t data2);
void        usb_pstd_write_complete(usb_putr_t *p_mess, uint16_t data1, uint16_t data2);
#endif /* defined(USB_CFG_PVND_USE) */

#if defined(USB_CFG_PCDC_USE)
void        usb_pcdc_read_complete( usb_putr_t *p_mess, uint16_t data1, uint16_t data2);
void        usb_pcdc_write_complete( usb_putr_t *p_mess, uint16_t data1, uint16_t data2);
#endif /* defined(USB_CFG_PCDC_USE) */

#if defined(USB_CFG_PHID_USE)
void        usb_phid_read_complete(usb_putr_t *p_mess, uint16_t data1, uint16_t data2);
void        usb_phid_write_complete(usb_putr_t *p_mess, uint16_t data1, uint16_t data2);
#endif /* defined(USB_CFG_PHID_USE) */

#if defined(USB_CFG_PMSC_USE)
#if (BSP_CFG_RTOS_USED == 4)    /* Renesas RI600V4 & RI600PX */
 void usb_pmsc_task (VP_INT b);
#else  /* (BSP_CFG_RTOS_USED == 4) */
void        usb_pmsc_task (void);
#endif /* (BSP_CFG_RTOS_USED == 4) */

void      usb_pmsc_receive_cbw (void);
void      usb_pmsc_get_max_lun (uint16_t value, uint16_t index, uint16_t length);
void      usb_pmsc_mass_strage_reset (uint16_t value, uint16_t index, uint16_t length);
#endif

#if USB_CFG_BC == USB_CFG_ENABLE
/* r_usb_hbc.c */
   void      usb_hstd_pddetint_process(void);
/* r_usb_pbc.c */
   void      usb_pstd_bc_detect_process(void);
#endif /* USB_CFG_BC == USB_CFG_ENABLE */

#if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
void      usb_compliance_disp (void *);

#endif /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

#endif  /* R_USB_EXTERN_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
