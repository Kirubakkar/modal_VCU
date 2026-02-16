/**
 ******************************************************************************
 * @file           : vcu.c
 * @brief          : VCU application implementation
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "vcu.h"
#include "canOpen.h"
#include "cmsis_os.h"
#include "steering.h"


/* External variables --------------------------------------------------------*/
extern CAN_HandleTypeDef hcan1;

/* Private variables ---------------------------------------------------------*/
static osThreadId_t telems100msTaskHandle;
static osThreadId_t telems1000msTaskHandle;

static const osThreadAttr_t telems100msTask_attributes = {
    .name = "vTaskTelems100ms",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

static const osThreadAttr_t telems1000msTask_attributes = {
    .name = "vTaskTelems1000ms",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
static void vTaskTelems100ms(void *argument);
static void vTaskTelems1000ms(void *argument);

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  Initialize VCU - runs steering homing sequence.
 *         Must be called from a FreeRTOS task context (uses osDelay).
 */
void initVCU(void) {
  /* Initialize steering subsystem (homing sequence) */
  if (initSteering() == 0) {
    initTelems();
  }
}

/**
 * @brief  Initialize telemetry - creates periodic telemetry tasks.
 *         Must be called from a FreeRTOS task context.
 */
void initTelems(void) {
  telems100msTaskHandle =
      osThreadNew(vTaskTelems100ms, NULL, &telems100msTask_attributes);

  telems1000msTaskHandle =
      osThreadNew(vTaskTelems1000ms, NULL, &telems1000msTask_attributes);
}

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Telemetry task - runs every 100ms.
 */
static void vTaskTelems100ms(void *argument) {
  (void)argument;

  for (;;) {
    /* TODO: Add 100ms telemetry operations here */

    osDelay(100);
  }
}

/**
 * @brief  Telemetry task - runs every 1000ms.
 */
static void vTaskTelems1000ms(void *argument) {
  (void)argument;

  for (;;) {
    /* TODO: Add 1000ms telemetry operations here */

    osDelay(1000);
  }
}
