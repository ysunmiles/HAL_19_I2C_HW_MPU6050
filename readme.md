# HAL_19_I2C_SW_MPU6050

## 项目简介

这是一个基于 STM32F103xB 的嵌入式项目，展示如何在 STM32 上使用软件 I2C 驱动两种外设：

- MPU6050 6 轴运动传感器
- SSD1306 OLED 显示屏

项目使用 STM32 HAL + CubeMX 生成的基础工程模板，并在此基础上增加了自定义的软件 I2C 驱动和传感器读取逻辑。

主程序会：

- 初始化 GPIO
- 初始化 MPU6050
- 读取设备 ID
- 读取加速度、陀螺仪和温度数据
- 通过 OLED 显示数值

---

## 硬件连接

目标 MCU：STM32F103 系列

本工程中使用软件 I2C 模拟 I2C 总线，GPIO 定义如下：

- MPU SCL -> PB10
- MPU SDA -> PB11
- OLED SCL -> PB9
- OLED SDA -> PB8

对应定义可见：

- [Core/Inc/main.h](Core/Inc/main.h)
- [Core/Src/gpio.c](Core/Src/gpio.c)

---

## 功能概述

### 1. MPU6050

- 初始化 MPU6050 相关寄存器
- 读取 WHO_AM_I
- 读取加速度值（AccX / AccY / AccZ）
- 读取陀螺仪值（GyroX / GyroY / GyroZ）
- 读取温度值（Temp）

相关代码：

- [Core/Inc/MPU6050.h](Core/Inc/MPU6050.h)
- [Core/Src/MPU6050.c](Core/Src/MPU6050.c)
- [Core/Inc/MPU6050_Reg.h](Core/Inc/MPU6050_Reg.h)

### 2. 软件 I2C

自定义软件 I2C 驱动实现了以下功能：

- 起始信号
- 停止信号
- 发送字节
- 接收字节
- 发送 ACK / NACK
- 接收 ACK

相关代码：

- [Core/Inc/SWI2C.h](Core/Inc/SWI2C.h)
- [Core/Src/SWI2C.c](Core/Src/SWI2C.c)

### 3. OLED 显示

通过 SSD1306 驱动实现如下功能：

- 初始化 OLED
- 显示字符串
- 显示数字
- 显示十六进制数
- 显示有符号数

相关代码：

- [Core/Inc/OLED.h](Core/Inc/OLED.h)
- [Core/Src/OLED.c](Core/Src/OLED.c)
- [Core/Inc/OLED_Font.h](Core/Inc/OLED_Font.h)

---

## 项目结构

```text
HAL_19_I2C_SW_MPU6050/
├── CMakeLists.txt
├── CMakePresets.json
├── config.ioc
├── readme.md
├── startup_stm32f103xb.s
├── STM32F103XX_FLASH.ld
├── cmake/
│   ├── gcc-arm-none-eabi.cmake
│   ├── user_sources.cmake
│   └── stm32cubemx/
├── Core/
│   ├── Inc/
│   │   ├── main.h
│   │   ├── gpio.h
│   │   ├── OLED.h
│   │   ├── OLED_Font.h
│   │   ├── MPU6050.h
│   │   ├── MPU6050_Reg.h
│   │   └── SWI2C.h
│   └── Src/
│       ├── main.c
│       ├── gpio.c
│       ├── OLED.c
│       ├── MPU6050.c
│       ├── SWI2C.c
│       ├── stm32f1xx_it.c
│       ├── stm32f1xx_hal_msp.c
│       └── system_stm32f1xx.c
├── Drivers/
│   ├── CMSIS/
│   └── STM32F1xx_HAL_Driver/
└── build/
```

---

## 构建方式

本项目使用 CMake + Ninja 构建，适合 VS Code 中使用 CMake Tools 直接编译。

### 方式 1：VS Code + CMake Tools

1. 打开项目目录
2. 确认已安装 ARM GCC 工具链
3. 在 VS Code 中打开 CMake Tools
4. 选择 `Debug` 预设
5. 运行 Build

### 方式 2：命令行

```bash
cd d:/Electronics/HAL_Projects/HAL_19_I2C_SW_MPU6050
cmake --preset Debug
cmake --build --preset Debug
```

如果当前环境使用的是 STM32 Cube 的 `cube-cmake`，也可以直接用 Cube 提供的 CMake 工具链进行构建。

---

## 烧录方式

生成的固件可通过 ST-LINK 下载到 STM32 开发板中。

常见步骤：

1. 编译生成 ELF / HEX / BIN 文件
2. 使用 ST-LINK Utility、STM32CubeProgrammer 或 VS Code 扩展烧录
3. 上电运行
4. OLED 上显示 MPU6050 的设备 ID、加速度值等信息

---

## 运行效果

程序启动后，OLED 屏幕通常会显示类似信息：

- Device ID
- AccX / AccY / AccZ
- 读取的传感器数据会持续刷新

如果连接正常，`WHO_AM_I` 应该返回 MPU6050 的标准设备 ID（通常为 0x68）。

---

## 代码说明

本项目的核心是“软件 I2C + HAL + 自定义传感器驱动”的组合方式，适合学习以下内容：

- MCU GPIO 控制
- 软件 I2C 实现
- STM32 HAL 的初始化流程
- 传感器寄存器读写
- OLED 字符显示

---

## 注意事项

- 软件 I2C 的时序对 GPIO 速度和延时比较敏感
- 若接线错误或上拉不足，MPU6050 可能无法正常通信
- OLED 和 MPU6050 共用软件 I2C 逻辑时，需注意时序与总线占用
- 该工程适合学习和调试，不作为工业级高可靠 I2C 驱动直接使用

---

## 许可证

本项目用于学习和开发实验，具体许可证以仓库中实际文件声明为准。
