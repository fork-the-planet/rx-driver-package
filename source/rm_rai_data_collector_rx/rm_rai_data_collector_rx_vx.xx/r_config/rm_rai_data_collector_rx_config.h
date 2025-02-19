/* Generated configuration header file - do not edit */
/* generated configuration header file - do not edit */
#ifndef RM_RAI_DATA_COLLECTOR_CFG_H_
#define RM_RAI_DATA_COLLECTOR_CFG_H_
#ifdef __cplusplus
extern "C" {
#endif

/* Common */
#define RM_RAI_DATA_COLLECTOR_CFG_PARAM_CHECKING_ENABLE                 (BSP_CFG_PARAM_CHECKING_ENABLE)
#define RM_RAI_DATA_COLLECTOR_CFG_MAX_CHANNELS                          (16)

/* Device 0 */
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_ID                                (0)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_FRAME_BUF_LEN                     (50)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DATA_READY_CALLBACK               (rai_data_collector0_callback)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_ERROR_CALLBACK                    (rai_data_collector0_error_callback)

#define RM_RAI_DATA_COLLECTOR_CFG_DC0_SNAPSHOT_CHANNEL0_NAME            (NULL)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_SNAPSHOT_CHANNEL0_DATA_TYPE       (1)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_SNAPSHOT_CHANNEL1_NAME            (NULL)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_SNAPSHOT_CHANNEL1_DATA_TYPE       (1)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_SNAPSHOT_CHANNEL2_NAME            (NULL)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_SNAPSHOT_CHANNEL2_DATA_TYPE       (1)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_SNAPSHOT_CHANNEL3_NAME            (NULL)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_SNAPSHOT_CHANNEL3_DATA_TYPE       (1)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_SNAPSHOT_CHANNEL4_NAME            (NULL)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_SNAPSHOT_CHANNEL4_DATA_TYPE       (1)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_SNAPSHOT_CHANNEL5_NAME            (NULL)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_SNAPSHOT_CHANNEL5_DATA_TYPE       (1)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_SNAPSHOT_CHANNEL6_NAME            (NULL)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_SNAPSHOT_CHANNEL6_DATA_TYPE       (1)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_SNAPSHOT_CHANNEL7_NAME            (NULL)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_SNAPSHOT_CHANNEL7_DATA_TYPE       (1)

#define RM_RAI_DATA_COLLECTOR_CFG_DC0_SNAPSHOT_CHANNELS                 (1)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_SNAPSHOT_COUNT                    (1)

#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DATA_FEED_CHANNEL0_NAME           (NULL)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DATA_FEED_CHANNEL0_DATA_TYPE      (1)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DATA_FEED_CHANNEL1_NAME           (NULL)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DATA_FEED_CHANNEL1_DATA_TYPE      (1)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DATA_FEED_CHANNEL2_NAME           (NULL)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DATA_FEED_CHANNEL2_DATA_TYPE      (1)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DATA_FEED_CHANNEL3_NAME           (NULL)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DATA_FEED_CHANNEL3_DATA_TYPE      (1)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DATA_FEED_CHANNEL4_NAME           (NULL)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DATA_FEED_CHANNEL4_DATA_TYPE      (1)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DATA_FEED_CHANNEL5_NAME           (NULL)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DATA_FEED_CHANNEL5_DATA_TYPE      (1)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DATA_FEED_CHANNEL6_NAME           (NULL)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DATA_FEED_CHANNEL6_DATA_TYPE      (1)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DATA_FEED_CHANNEL7_NAME           (NULL)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DATA_FEED_CHANNEL7_DATA_TYPE      (1)

#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DATA_FEED_CHANNELS                (1)

#define RM_RAI_DATA_COLLECTOR_CFG_DC0_TIMER_CHANNEL                     (0)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_TIMER_FREQUENCY                   (100)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_TIMER_PRIORITY                    (CMT_PRIORITY_10)

#if   (0 == RM_RAI_DATA_COLLECTOR_CFG_DC0_TIMER_CHANNEL)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DTC_ACT_SOURCE                    (DTCE_CMT0_CMI0)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_TIMER_IEN                         (IEN(CMT0,CMI0))
#elif (1 == RM_RAI_DATA_COLLECTOR_CFG_DC0_TIMER_CHANNEL)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_DTC_ACT_SOURCE                    (DTCE_CMT1_CMI1)
#define RM_RAI_DATA_COLLECTOR_CFG_DC0_TIMER_IEN                         (IEN(CMT1,CMI1))
#endif


#ifdef __cplusplus
}
#endif
#endif /* RM_RAI_DATA_COLLECTOR_CFG_H_ */
