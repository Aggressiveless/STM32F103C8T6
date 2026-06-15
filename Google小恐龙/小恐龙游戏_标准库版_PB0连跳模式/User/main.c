/*
 * main.c - STM32F103C8T6 Standard Peripheral Library version
 * Converted from the original HAL DinoGames project.
 *
 * Hardware mapping in this project:
 *   - PB0: start / restart / chain-jump queue key, active low
 *   - PB1: normal jump key, active low
 *   - PB3 / PB4: OLED software I2C, output
 *
 * Chain-jump mode:
 *   During gameplay, each short press of PB0 adds 1 pending jump.
 *   When the dino lands, one pending jump is consumed and the next jump starts.
 */

#include "main.h"
#include "Delay.h"
#include "OLED.h"
#include <stdlib.h>

#define CHAIN_JUMP_MAX_COUNT 9

static void GPIO_Config(void);
static unsigned char Key_B0_PressedOnce(void);
static unsigned char Key_B1_PressedOnce(void);

/* Rising/holding will not be counted repeatedly; only one falling edge is counted. */
static unsigned char Key_B0_PressedOnce(void)
{
    static unsigned char last_state = 1;
    unsigned char now_state;
    unsigned char pressed = 0;

    now_state = (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == Bit_RESET) ? 0 : 1;

    if ((last_state == 1) && (now_state == 0))
    {
        Delay_ms(15);       /* simple debounce */
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == Bit_RESET)
        {
            pressed = 1;
            now_state = 0;
        }
        else
        {
            now_state = 1;
        }
    }

    last_state = now_state;
    return pressed;
}

static unsigned char Key_B1_PressedOnce(void)
{
    static unsigned char last_state = 1;
    unsigned char now_state;
    unsigned char pressed = 0;

    now_state = (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == Bit_RESET) ? 0 : 1;

    if ((last_state == 1) && (now_state == 0))
    {
        Delay_ms(15);       /* simple debounce */
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == Bit_RESET)
        {
            pressed = 1;
            now_state = 0;
        }
        else
        {
            now_state = 1;
        }
    }

    last_state = now_state;
    return pressed;
}

int main(void)
{
    unsigned char cactus_category = 0;
    unsigned char cactus_length = 8;
    unsigned int score = 0;
    unsigned int highest_score = 0;
    int height = 0;
    int cactus_pos = 128;
    unsigned char cur_speed = 30;
    char failed = 0;
    char reset = 0;

    unsigned char chain_jump_count = 0;     /* PB0 pending jumps */
    unsigned char jump_request = 0;

    /* SystemInit() in Start/system_stm32f10x.c has configured the system clock
       to 72 MHz for STM32F103 medium-density devices. */
    GPIO_Config();

    OLED_Init();
    OLED_DrawCover();

    /* PB0 starts the game. */
    while (!Key_B0_PressedOnce())
    {
    }
    Delay_ms(100);
    OLED_Clear();

    while (1)
    {
        if (failed == 1)
        {
            OLED_DrawRestart();

            /* PB0 restarts the game after GAME OVER. */
            if (Key_B0_PressedOnce())
            {
                if (score > highest_score)
                {
                    highest_score = score;
                }
                score = 0;
                failed = 0;
                height = 0;
                chain_jump_count = 0;
                reset = 1;
                OLED_DrawDinoJump(reset);
                OLED_DrawCactusRandom(cactus_category, reset);
                OLED_Clear();
            }
            continue;
        }

        score++;

        /* During gameplay, PB0 adds pending chain jumps. */
        if (Key_B0_PressedOnce())
        {
            if (chain_jump_count < CHAIN_JUMP_MAX_COUNT)
            {
                chain_jump_count++;
            }
        }

        /* PB1 still works as a normal single jump key. */
        jump_request = Key_B1_PressedOnce();

        OLED_DrawGround();
        OLED_DrawCloud();

        if (height > 0)
        {
            /* Continue the current jump. */
            height = OLED_DrawDinoJump(reset);
        }
        else if (jump_request)
        {
            /* PB1: immediate single jump. */
            height = OLED_DrawDinoJump(reset);
        }
        else if (chain_jump_count > 0)
        {
            /* PB0 chain-jump: consume one queued jump after landing. */
            chain_jump_count--;
            height = OLED_DrawDinoJump(reset);
        }
        else
        {
            OLED_DrawDino();
        }

        cactus_pos = OLED_DrawCactusRandom(cactus_category, reset);
        if (cactus_category == 0)
        {
            cactus_length = 8;
        }
        else if (cactus_category == 1)
        {
            cactus_length = 16;
        }
        else
        {
            cactus_length = 24;
        }

        if (cactus_pos + cactus_length < 0)
        {
            cactus_category = rand() % 4;
            OLED_DrawCactusRandom(cactus_category, 1);
        }

        if ((height < 16) &&
            ((cactus_pos >= 16 && cactus_pos <= 32) ||
             (cactus_pos + cactus_length >= 16 && cactus_pos + cactus_length <= 32)))
        {
            failed = 1;
        }

        /* Left top: queued chain jumps. Right top: score. */
        OLED_ShowString(0, 0, (u8 *)"J:", 12);
        OLED_ShowNum(12, 0, chain_jump_count, 1, 12);
        OLED_ShowString(35, 0, (u8 *)"HI:", 12);
        OLED_ShowNum(58, 0, highest_score, 5, 12);
        OLED_ShowNum(98, 0, score, 5, 12);

        reset = 0;

        cur_speed = score / 20;
        if (cur_speed > 29)
        {
            cur_speed = 29;
        }
        Delay_ms(30 - cur_speed);
    }
}

static void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO |
                           RCC_APB2Periph_GPIOA |
                           RCC_APB2Periph_GPIOB |
                           RCC_APB2Periph_GPIOD, ENABLE);

    /* PB3/PB4 are used by JTAG by default. Disable JTAG, keep SWD. */
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    GPIO_ResetBits(GPIOB, GPIO_Pin_3 | GPIO_Pin_4);

    /* Keys: PB0/PB1 input pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* OLED software I2C: PB3/PB4 output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}
