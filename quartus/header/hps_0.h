#ifndef _ALTERA_HPS_0_H_
#define _ALTERA_HPS_0_H_

/*
 * This file was automatically generated by the swinfo2header utility.
 * 
 * Created from SOPC Builder system 'base_hps' in
 * file 'base_hps.sopcinfo'.
 */

/*
 * This file contains macros for module 'hps_0' and devices
 * connected to the following masters:
 *   h2f_axi_master
 *   h2f_lw_axi_master
 * 
 * Do not include this header file and another header file created for a
 * different module or master group at the same time.
 * Doing so may result in duplicate macro names.
 * Instead, use the system header file which has macros with unique names.
 */

/*
 * Macros for device 'adc_0', class 'altera_up_avalon_adc'
 * The macros are prefixed with 'ADC_0_'.
 * The prefix is the slave descriptor.
 */
#define ADC_0_COMPONENT_TYPE altera_up_avalon_adc
#define ADC_0_COMPONENT_NAME adc_0
#define ADC_0_BASE 0x0
#define ADC_0_SPAN 32
#define ADC_0_END 0x1f

/*
 * Macros for device 'sw_pio', class 'altera_avalon_pio'
 * The macros are prefixed with 'SW_PIO_'.
 * The prefix is the slave descriptor.
 */
#define SW_PIO_COMPONENT_TYPE altera_avalon_pio
#define SW_PIO_COMPONENT_NAME sw_pio
#define SW_PIO_BASE 0x0
#define SW_PIO_SPAN 16
#define SW_PIO_END 0xf
#define SW_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define SW_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SW_PIO_CAPTURE 0
#define SW_PIO_DATA_WIDTH 4
#define SW_PIO_DO_TEST_BENCH_WIRING 0
#define SW_PIO_DRIVEN_SIM_VALUE 0
#define SW_PIO_EDGE_TYPE NONE
#define SW_PIO_FREQ 50000000
#define SW_PIO_HAS_IN 1
#define SW_PIO_HAS_OUT 0
#define SW_PIO_HAS_TRI 0
#define SW_PIO_IRQ_TYPE NONE
#define SW_PIO_RESET_VALUE 0

/*
 * Macros for device 'pb_pio', class 'altera_avalon_pio'
 * The macros are prefixed with 'PB_PIO_'.
 * The prefix is the slave descriptor.
 */
#define PB_PIO_COMPONENT_TYPE altera_avalon_pio
#define PB_PIO_COMPONENT_NAME pb_pio
#define PB_PIO_BASE 0x10
#define PB_PIO_SPAN 16
#define PB_PIO_END 0x1f
#define PB_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define PB_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PB_PIO_CAPTURE 0
#define PB_PIO_DATA_WIDTH 2
#define PB_PIO_DO_TEST_BENCH_WIRING 0
#define PB_PIO_DRIVEN_SIM_VALUE 0
#define PB_PIO_EDGE_TYPE NONE
#define PB_PIO_FREQ 50000000
#define PB_PIO_HAS_IN 1
#define PB_PIO_HAS_OUT 0
#define PB_PIO_HAS_TRI 0
#define PB_PIO_IRQ_TYPE NONE
#define PB_PIO_RESET_VALUE 0

/*
 * Macros for device 'led_pio', class 'altera_avalon_pio'
 * The macros are prefixed with 'LED_PIO_'.
 * The prefix is the slave descriptor.
 */
#define LED_PIO_COMPONENT_TYPE altera_avalon_pio
#define LED_PIO_COMPONENT_NAME led_pio
#define LED_PIO_BASE 0x20
#define LED_PIO_SPAN 16
#define LED_PIO_END 0x2f
#define LED_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define LED_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LED_PIO_CAPTURE 0
#define LED_PIO_DATA_WIDTH 8
#define LED_PIO_DO_TEST_BENCH_WIRING 0
#define LED_PIO_DRIVEN_SIM_VALUE 0
#define LED_PIO_EDGE_TYPE NONE
#define LED_PIO_FREQ 50000000
#define LED_PIO_HAS_IN 0
#define LED_PIO_HAS_OUT 1
#define LED_PIO_HAS_TRI 0
#define LED_PIO_IRQ_TYPE NONE
#define LED_PIO_RESET_VALUE 85

/*
 * Macros for device 'sysid', class 'altera_avalon_sysid_qsys'
 * The macros are prefixed with 'SYSID_'.
 * The prefix is the slave descriptor.
 */
#define SYSID_COMPONENT_TYPE altera_avalon_sysid_qsys
#define SYSID_COMPONENT_NAME sysid
#define SYSID_BASE 0x30
#define SYSID_SPAN 8
#define SYSID_END 0x37
#define SYSID_ID 3405688028
#define SYSID_TIMESTAMP 1597422831

/*
 * Macros for device 'sonar_0', class 'altera_avalon_pio'
 * The macros are prefixed with 'SONAR_0_'.
 * The prefix is the slave descriptor.
 */
#define SONAR_0_COMPONENT_TYPE altera_avalon_pio
#define SONAR_0_COMPONENT_NAME sonar_0
#define SONAR_0_BASE 0x100
#define SONAR_0_SPAN 16
#define SONAR_0_END 0x10f
#define SONAR_0_BIT_CLEARING_EDGE_REGISTER 0
#define SONAR_0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SONAR_0_CAPTURE 0
#define SONAR_0_DATA_WIDTH 32
#define SONAR_0_DO_TEST_BENCH_WIRING 0
#define SONAR_0_DRIVEN_SIM_VALUE 0
#define SONAR_0_EDGE_TYPE NONE
#define SONAR_0_FREQ 50000000
#define SONAR_0_HAS_IN 1
#define SONAR_0_HAS_OUT 0
#define SONAR_0_HAS_TRI 0
#define SONAR_0_IRQ_TYPE NONE
#define SONAR_0_RESET_VALUE 0

/*
 * Macros for device 'sonar_1', class 'altera_avalon_pio'
 * The macros are prefixed with 'SONAR_1_'.
 * The prefix is the slave descriptor.
 */
#define SONAR_1_COMPONENT_TYPE altera_avalon_pio
#define SONAR_1_COMPONENT_NAME sonar_1
#define SONAR_1_BASE 0x110
#define SONAR_1_SPAN 16
#define SONAR_1_END 0x11f
#define SONAR_1_BIT_CLEARING_EDGE_REGISTER 0
#define SONAR_1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SONAR_1_CAPTURE 0
#define SONAR_1_DATA_WIDTH 32
#define SONAR_1_DO_TEST_BENCH_WIRING 0
#define SONAR_1_DRIVEN_SIM_VALUE 0
#define SONAR_1_EDGE_TYPE NONE
#define SONAR_1_FREQ 50000000
#define SONAR_1_HAS_IN 1
#define SONAR_1_HAS_OUT 0
#define SONAR_1_HAS_TRI 0
#define SONAR_1_IRQ_TYPE NONE
#define SONAR_1_RESET_VALUE 0

/*
 * Macros for device 'gpio_output', class 'altera_avalon_pio'
 * The macros are prefixed with 'GPIO_OUTPUT_'.
 * The prefix is the slave descriptor.
 */
#define GPIO_OUTPUT_COMPONENT_TYPE altera_avalon_pio
#define GPIO_OUTPUT_COMPONENT_NAME gpio_output
#define GPIO_OUTPUT_BASE 0x1000
#define GPIO_OUTPUT_SPAN 16
#define GPIO_OUTPUT_END 0x100f
#define GPIO_OUTPUT_BIT_CLEARING_EDGE_REGISTER 0
#define GPIO_OUTPUT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define GPIO_OUTPUT_CAPTURE 0
#define GPIO_OUTPUT_DATA_WIDTH 2
#define GPIO_OUTPUT_DO_TEST_BENCH_WIRING 0
#define GPIO_OUTPUT_DRIVEN_SIM_VALUE 0
#define GPIO_OUTPUT_EDGE_TYPE NONE
#define GPIO_OUTPUT_FREQ 50000000
#define GPIO_OUTPUT_HAS_IN 0
#define GPIO_OUTPUT_HAS_OUT 1
#define GPIO_OUTPUT_HAS_TRI 0
#define GPIO_OUTPUT_IRQ_TYPE NONE
#define GPIO_OUTPUT_RESET_VALUE 0

/*
 * Macros for device 'motor_left', class 'altera_avalon_pio'
 * The macros are prefixed with 'MOTOR_LEFT_'.
 * The prefix is the slave descriptor.
 */
#define MOTOR_LEFT_COMPONENT_TYPE altera_avalon_pio
#define MOTOR_LEFT_COMPONENT_NAME motor_left
#define MOTOR_LEFT_BASE 0x10000
#define MOTOR_LEFT_SPAN 16
#define MOTOR_LEFT_END 0x1000f
#define MOTOR_LEFT_BIT_CLEARING_EDGE_REGISTER 0
#define MOTOR_LEFT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define MOTOR_LEFT_CAPTURE 0
#define MOTOR_LEFT_DATA_WIDTH 9
#define MOTOR_LEFT_DO_TEST_BENCH_WIRING 0
#define MOTOR_LEFT_DRIVEN_SIM_VALUE 0
#define MOTOR_LEFT_EDGE_TYPE NONE
#define MOTOR_LEFT_FREQ 50000000
#define MOTOR_LEFT_HAS_IN 0
#define MOTOR_LEFT_HAS_OUT 1
#define MOTOR_LEFT_HAS_TRI 0
#define MOTOR_LEFT_IRQ_TYPE NONE
#define MOTOR_LEFT_RESET_VALUE 0

/*
 * Macros for device 'motor_right', class 'altera_avalon_pio'
 * The macros are prefixed with 'MOTOR_RIGHT_'.
 * The prefix is the slave descriptor.
 */
#define MOTOR_RIGHT_COMPONENT_TYPE altera_avalon_pio
#define MOTOR_RIGHT_COMPONENT_NAME motor_right
#define MOTOR_RIGHT_BASE 0x100000
#define MOTOR_RIGHT_SPAN 16
#define MOTOR_RIGHT_END 0x10000f
#define MOTOR_RIGHT_BIT_CLEARING_EDGE_REGISTER 0
#define MOTOR_RIGHT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define MOTOR_RIGHT_CAPTURE 0
#define MOTOR_RIGHT_DATA_WIDTH 9
#define MOTOR_RIGHT_DO_TEST_BENCH_WIRING 0
#define MOTOR_RIGHT_DRIVEN_SIM_VALUE 0
#define MOTOR_RIGHT_EDGE_TYPE NONE
#define MOTOR_RIGHT_FREQ 50000000
#define MOTOR_RIGHT_HAS_IN 0
#define MOTOR_RIGHT_HAS_OUT 1
#define MOTOR_RIGHT_HAS_TRI 0
#define MOTOR_RIGHT_IRQ_TYPE NONE
#define MOTOR_RIGHT_RESET_VALUE 0


#endif /* _ALTERA_HPS_0_H_ */