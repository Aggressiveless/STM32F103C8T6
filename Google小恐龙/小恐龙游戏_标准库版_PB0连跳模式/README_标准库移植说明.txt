小恐龙游戏 HAL -> STM32F10x 标准库移植说明

已经完成的转换：
1. User/main.c：原 HAL 版 main.c 改为标准库版本。
2. Hardware/OLED.c / OLED.h / OLED_Font.h：原 HAL 版 oled12864 驱动和小恐龙字模已移入标准库工程。
3. User/stm32f10x_conf.h：补齐标准库配置头文件。
4. User/stm32f10x_it.c / .h：补齐中断文件，保证 Keil 工程引用的文件存在。
5. Project.uvprojx：预处理宏已改为 USE_STDPERIPH_DRIVER,STM32F10X_MD。

默认硬件连接保持原 HAL 工程不变：
- OLED SCL：PB3
- OLED SDA：PB4
- 开始/重新开始按键：PB0，低电平有效
- 跳跃按键：PB1，低电平有效

重要提醒：
PB3/PB4 默认是 JTAG 复用脚，所以 main.c 里已经加入：
GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
它会关闭 JTAG，保留 SWD 下载/调试。

使用方法：
1. 用 Keil 打开 Project.uvprojx。
2. Rebuild。
3. 如果 OLED 没反应，优先检查 OLED 实际接线是否是 PB3/PB4。
   如果你的板子是 PB8/PB9，需要同时修改 Hardware/OLED.h 里的 OLED_SCL_PIN/OLED_SDA_PIN，
   以及 User/main.c 里 GPIO_Config() 的 OLED 引脚初始化。


本次新增：PB0 连跳模式
1. 封面界面：按 PB0 开始游戏。
2. 游戏中：PB0 不再只是开始键，每短按一次会加入 1 次待跳次数。
3. 小恐龙落地后，如果还有待跳次数，会自动继续跳。
4. 屏幕左上角 J: 后面的数字表示当前剩余待跳次数，最大为 9。
5. PB1 仍然保留为普通单次跳跃键。

注意：B0/B1 按键仍然是低电平有效，按键另一端接 GND。
修改位置：User/main.c
关键变量：chain_jump_count
关键宏：CHAIN_JUMP_MAX_COUNT
