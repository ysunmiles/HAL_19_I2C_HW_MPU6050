# HAL_2_OLED

## 简介

本项目基于 STM32F103 系列 MCU 和 STM32 HAL 库，演示了通过软件 I2C 控制 OLED 屏幕的显示。
主程序在 OLED 上输出字符串，并使用 STM32CubeMX 生成的 CMake 构建配置。

## 主要功能

- 初始化并使用 STM32 HAL 驱动 STM32F103 MCU
- 软件 I2C 方式驱动 OLED 显示屏（PB8=SCL，PB9=SDA）
- OLED 清屏、显示字符、显示字符串、显示二进制/十进制/十六进制数、显示浮点数、显示数组
- 使用 STM32CubeMX 生成的 Cube HAL 驱动代码与自定义 OLED 模块组合

## 关键文件

- `CMakeLists.txt`：项目根 CMake 构建脚本
- `CMakePresets.json`：配置和构建预设，支持 `Debug` 和 `Release`
- `config.ioc`：STM32CubeMX 项目配置
- `Core/Src/main.c`：主程序入口
- `Core/Src/OLED.c`：OLED 控制逻辑与软件 I2C 实现
- `Core/Inc/OLED.h`：OLED 功能接口声明
- `Core/Inc/OLED_Font.h`：OLED 字库数据
- `cmake/user_sources.cmake`：自定义源文件和 include 路径注册
- `Drivers/`：STM32 HAL 库源文件和 CMSIS 头文件

## 构建环境与依赖

- CMake 3.22 及以上
- Ninja 构建器
- ARM GCC 交叉编译器（如 `arm-none-eabi-gcc`）
- STM32 HAL 库（包含在 `Drivers/` 目录中）

## 构建步骤

推荐使用 VS Code 的 CMake 工具或命令行：

```bash
cd d:/Electronics/HAL_Projects/HAL_2_OLED
cmake --preset Debug
cmake --build --preset Debug
```

## 运行与下载

1. 生成固件之后，使用 ST-Link 或其他支持的下载工具烧录生成的 ELF/HEX/BIN 文件到目标板。
2. 重新上电后，OLED 屏幕应显示主程序中指定的字符串。

## 硬件说明

- 目标 MCU：STM32F103 系列
- OLED 使用软件 I2C 模拟，默认引脚：
  - `PB8`：SCL
  - `PB9`：SDA

## 许可

MIT License
