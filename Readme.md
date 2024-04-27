# 项目名称

此项目基于硬件平台SSD202，并使用U-Boot和Linux Kernel 4.9.84，以及Buildroot作为软件平台。它采用LVGL作为GUI库，使用SquareLine作为GUI设计工具。

## 硬件平台

- **平台型号**：SSD202

## 核心参数

- 双核CortexA7 1.2GHz  
- 128MB DDR2  
- 256MB SPI Nand Flash  
- 支持RGB888,MIPI屏

## 软件平台

- **Bootloader**：U-Boot
- **Kernel**：Linux 4.9.84
- **Build System**：Buildroot

## GUI设计

本项目GUI使用LVGL库进行设计和实现，具体包括：

- **GUI库**：LVGL，一个开源的图形库，适用于嵌入式系统。
- **GUI设计工具**：SquareLine，一个用于设计LVGL GUI的工具。

### SquareLine工作流程

1. 使用SquareLine设计GUI界面。
2. 将设计导出生成代码。
3. 生成的代码会被放置在`generate`文件夹内。

## 如何使用

### 准备工作

确保你的开发环境满足以下要求：

- 已安装U-Boot和Linux Kernel 4.9.84的编译环境。
- 已安装Buildroot，用于创建根文件系统。
- 已安装LVGL库和SquareLine。

### 构建项目

1. **导入GUI代码**：首先，将SquareLine生成的代码从`generate`文件夹复制到项目中。
   ```bash
   cp -r generate/* your_project_directory/
2. **编译项目**：在项目根目录下，使用Make工具构建项目。首先，确保Makefile已经正确设置，以包含所有必要的编译指令和依赖关系。然后，运行以下命令进行编译
   ```bash
   make
3. **生成可执行文件**：编译完成后，在build文件夹中会生成最终的可执行文件。你可以使用以下命令查看生成的可执行文件lvgl_demo
   ```bash
   ls ./build/bin/

### LVGL源码改动
1. evdev.c click事件 audio_start("/honoka/audio/pizzicato.wav");