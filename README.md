# Embedded World 2024 MDK Middleware Examples

**MDK-Middleware v8** examples in CMSIS Solution Project Format.

Prepared for **Keil Studio Desktop**, an extension pack for Microsoft Visual Studio Code (VS Code) which provides an integrated development environment (IDE) for Cortex-M based microcontrollers. Can be used to edit, build, run and debug. 

Examples for STMicroelectronics STM32 based microcontrollers feature the **STM32CubeMX** code generator and common STM32Cube HAL based CMSIS Drivers.


## Prerequisites

### Tools
- Visual Studio Code with Arm Keil Studio Pack extension
- [CMSIS-Toolbox 2.3.0-dev0](https://github.com/Open-CMSIS-Pack/cmsis-toolbox/releases/tag/2.3.0-dev0) (not manged though vcpkg)
- Arm Compiler for Embedded (managed through vcpkg)
- Arm Debugger (when debugging, managed through vcpkg)
- [STM32CubeMX 6.11](https://www.st.com/en/development-tools/stm32cubemx.html) (for STMicroelectronics STM32 based microcontrollers)

### CMSIS [packs](https://armh-my.sharepoint.com/:f:/g/personal/robert_rostohar_arm_com/EnuIWjnKcVNDg-VG2W-FkV0BRFODClMq-mO1Gtbj1rOlTw?e=R0bK0f) (test versions): not yet published, require manual installation
 - [Keil.MDK-Middleware.8.0.0-dev26+g8f55aaa.pack](https://armh-my.sharepoint.com/:u:/r/personal/robert_rostohar_arm_com/Documents/Share/Packs/Keil.MDK-Middleware.8.0.0-dev26+g8f55aaa.pack?csf=1&web=1&e=JWfcsU)
 - [ARM.CMSIS-Driver_STM32.1.0.0-dev39+gbd9215b.pack](https://armh-my.sharepoint.com/:u:/r/personal/robert_rostohar_arm_com/Documents/Share/Packs/ARM.CMSIS-Driver_STM32.1.0.0-dev39+gbd9215b.pack?csf=1&web=1&e=5da3pg) for STM32 based microcontrollers
 - [Keil.STM32U5xx_DFP.3.0.0-extgen0.pack](https://armh-my.sharepoint.com/:u:/r/personal/robert_rostohar_arm_com/Documents/Share/Packs/Keil.STM32U5xx_DFP.3.0.0-extgen0.pack?csf=1&web=1&e=eNGhij) when using  B-U585I-IOT02A Board
 - [Keil.B-U585I-IOT02A_BSP.2.0.0-dev3.pack](https://armh-my.sharepoint.com/:u:/r/personal/robert_rostohar_arm_com/Documents/Share/Packs/Keil.B-U585I-IOT02A_BSP.2.0.0-dev3.pack?csf=1&web=1&e=miebXe) when using  B-U585I-IOT02A Board
 - [Keil.STM32H7RSxx_DFP.1.0.0-dev0.pack](https://armh-my.sharepoint.com/:u:/r/personal/robert_rostohar_arm_com/Documents/Share/Packs/Keil.STM32H7RSxx_DFP.1.0.0-dev0.pack?csf=1&web=1&e=6fptvF) when using STM32H7S78-DK Board
 - [Keil.STM32H7S78-DK_BSP.1.0.0-dev2.pack](https://armh-my.sharepoint.com/:u:/r/personal/robert_rostohar_arm_com/Documents/Share/Packs/Keil.STM32H7S78-DK_BSP.1.0.0-dev2.pack?csf=1&web=1&e=I1WDkL) when using STM32H7S78-DK Board
 - [Keil.STM32H7xx_DFP.4.0.0-extgen2.pack](https://armh-my.sharepoint.com/:u:/r/personal/robert_rostohar_arm_com/Documents/Share/Packs/Keil.STM32H7xx_DFP.4.0.0-extgen2.pack?csf=1&web=1&e=LyHPLS) when using STM32H743I-EVAL Board


## Workflow
 - Open example base directory which contains the vcpkg configuration file (`vcpkg-configuration.json`). Available example base directories are listed below.
 - `Arm Environment Manager` extension will activate the environment with the required Arm Tools (configured with `vcpkg-configuration.json`).
 - Scripts for runnung (with flashing) and debugging are provided (`.vscode` sub-directory) for out of box experience.
 - `Arm CMSIS csoluton` extension
   - Shows the solution with project files (including components) and provides shortcuts to commands for managing the project.
   - Use `Manage Software Components` to view selected Software Components.
     >Current limitation: Software Components not shown correctly after build (incompatibility with cmsis-toolbox 2.3.0-dev0).
   - Use `Select a Context for the Solution` to select the active context set.
   - Use `Build` to build the selected context set.
   - Use `Run` to flash and run the application.
   - Use `Debug` to debug the application.
     >Some devices require explicit flashing (`Run`) before debugging.
 - `Arm Device Manager` extension
   - Shows the connected devices (or debug probe).
   - Use `Open Serial` to view the serial terminal: select the correct serial port and baud rate (typically 115200).
 - **STM32CubeMX** code generator
   - Examples for STM32 based microcontrollers are pre-configured using STM32CubeMX code generator.
   - In order to change the configuration
     - Use the following command (in VS Code Terminal) to run the generator:  
       `csolution <solution_name>.csolution.yml -g CubeMX -c <context>`  
       Example:  
       ```
       csolution Blinky.csolution.yml run -g CubeMX -c Blinky.Debug+B-U585I-IOT02A
       ```
     - Change the configuration in STM32CubeMX as required.
     - Use `GENERATE CODE` in STM32CubeMX to generate the updated code.


## STMicroelectronics B-U585I-IOT02A Board

Blinky and MDK-Middleware examples for B-U585I-IOT02A board.

 - [Blinky](./Boards/B-U585I-IOT02A/Blinky)
 - [MDK-Middleware USB Device](./Boards/B-U585I-IOT02A/USB/Device)
   - HID
   - Mass Storage

>Requires explicit flashing (`Run`) before debugging.


## STMicroelectronics STM32H7S78-DK Board

Blinky and MDK-Middleware examples for STM32H7S78-DK board.

 - [Blinky](./Boards/STM32H7S78-DK/Blinky)
 - [MDK-Middleware USB Device HID](./Boards/STM32H7S78-DK/USB/Device/HID)
 - [MDK-Middleware USB Device Mass Storage](./Boards/STM32H7S78-DK/USB/Device/MassStorage)

>Examples for STM32H7S78-DK Board do not yet support the STM32CubeMX code generator integration.

>Flashing (`Run') does not yet work. Use uVision with preliminary support for STM32H7RSxx to flash the boot loader and application.


## STMicroelectronics STM32H743I-EVAL Board

Blinky and MDK-Middleware examples for STM32H743I-EVAL board.

 - [Blinky](./Boards/STM32H743I-EVAL/Blinky)
 - [MDK-Middleware File System](./Boards/STM32H743I-EVAL/FileSystem)
   - File Demo
 - [MDK-Middleware Network](./Boards/STM32H743I-EVAL/Network)
   - BSD Client
   - BSD Server
   - FTP Server
   - HTTP Server
   - HTTP Upload
   - SMTP Client
   - SNMP Agent
   - Telnet Server
 - [MDK-Middleware USB Device](./Boards/STM32H743I-EVAL/USB/Device)
   - HID
   - Mass Storage


## Generic board independent examples

MDK-Middleware generic examples using board layers.

[MDK-Middleware](./Generic)
 - File System
   - File Demo
 - Network
   - BSD Client
   - BSD Server
   - FTP Server
   - HTTP Server
   - HTTP Upload
   - SMTP Client
   - SNMP Agent
   - Telnet Server
 - USB Device
   - HID
   - Mass Storage
   - Virtual COM
