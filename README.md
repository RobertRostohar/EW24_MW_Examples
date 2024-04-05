# Embedded World 2024 MDK Middleware Examples

**MDK-Middleware v8** examples in CMSIS Solution Project Format.

Prepared for **Keil Studio Desktop**, an extension pack for Microsoft Visual Studio Code (VS Code) which provides an integrated development environment (IDE) for Cortex-M based microcontrollers. Can be used to edit, build, run and debug. 

Examples for STMicroelectronics STM32 based microcontrollers feature the **STM32CubeMX** code generator and common STM32Cube HAL based CMSIS Drivers.


## Prerequisites

### Tools
- Visual Studio Code with Arm Keil Studio Pack extension
- CMSIS-Toolbox 2.3.0 (manged though vcpkg)
- Arm Compiler for Embedded (managed through vcpkg)
- Arm Debugger (when debugging, managed through vcpkg)
- [STM32CubeMX 6.11](https://www.st.com/en/development-tools/stm32cubemx.html) (for STMicroelectronics STM32 based microcontrollers)

### CMSIS [packs](https://armh-my.sharepoint.com/:f:/g/personal/robert_rostohar_arm_com/EnuIWjnKcVNDg-VG2W-FkV0BRFODClMq-mO1Gtbj1rOlTw?e=uXoBFR) (test versions): not yet published, require manual installation
 - [Keil.MDK-Middleware.8.0.0-dev26+g8f55aaa.pack](https://armh-my.sharepoint.com/:u:/g/personal/robert_rostohar_arm_com/Ef7cifJiWnFFmxRWs5M5vucBSnkRwP7RuFETqE-CGNhX5w?e=hZfkpW)
 - [ARM.CMSIS-Driver_STM32.1.0.0-dev39+gbd9215b.pack](https://armh-my.sharepoint.com/:u:/g/personal/robert_rostohar_arm_com/EcsBeFeCkwVEkXtx8W_aJnoByDo6QQARAVmzXC5AmL4LPw?e=yyI52p) for STM32 based microcontrollers
 - [Keil.STM32U5xx_DFP.3.0.0-extgen0.pack](https://armh-my.sharepoint.com/:u:/g/personal/robert_rostohar_arm_com/EVCZ53IRbz9BnrILt3T2XSYBX2v9ikAyFIaj6rFFUl-exA?e=YkyzK8) when using  B-U585I-IOT02A Board
 - [Keil.B-U585I-IOT02A_BSP.2.0.0-dev4.pack](https://armh-my.sharepoint.com/:u:/g/personal/robert_rostohar_arm_com/ESRk-C_g9jlGlrXXJe0fElUBePTFI3jXfWoa_XjfABoI5g?e=s4ASlP) when using  B-U585I-IOT02A Board or Generic examples and layer detection
 - [Keil.STM32H7RSxx_DFP.1.0.0-dev0.pack](https://armh-my.sharepoint.com/:u:/g/personal/robert_rostohar_arm_com/ET9w8HJ8AxdPlqpMyO82sAwBKizJPJkq1Db12c4-BPM9xQ?e=gZeJfV) when using STM32H7S78-DK Board
 - [Keil.STM32H7S78-DK_BSP.1.0.0-dev3.pack](https://armh-my.sharepoint.com/:u:/g/personal/robert_rostohar_arm_com/EZraNUUBXZRHp0NU8UwT40ABea8Dz530qYuqqqcQ8ivoMA?e=t5lJEG) when using STM32H7S78-DK Board
 - [Keil.STM32H7xx_DFP.4.0.0-extgen2.pack](https://armh-my.sharepoint.com/:u:/g/personal/robert_rostohar_arm_com/EXfv6wVPUjtCu7fIhewq-xoBDCQzXRRU-bWjgLdh6lCaOg?e=RN6htz) when using STM32H743I-EVAL Board
 - [Keil.IMXRT1050-EVKB_BSP.1.2.0-dev0.pack](https://armh-my.sharepoint.com/:u:/g/personal/robert_rostohar_arm_com/EX8EXdmI_8pOhcdwAY3zjNkB4pkjCSKxS-OGopE03Xvj6w?e=eKQUhv) when using Generic examples and layer detection


## Workflow
 - Open example base directory which contains the vcpkg configuration file (`vcpkg-configuration.json`) in VS Code. Available example base directories are listed below.
 - `Arm Environment Manager` extension will activate the environment with the required Arm Tools (configured with `vcpkg-configuration.json`).
 - Scripts for running (with flashing) and debugging are provided (`.vscode` sub-directory) for out of box experience.
 - `Arm CMSIS csoluton` extension
   - Shows the solution with project files (including components) and provides shortcuts to commands for managing the project.
   - Use `Manage Software Components` to view selected Software Components.
     >Current limitation: Software Components not shown correctly after build (incompatibility with cmsis-toolbox 2.3.0).
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
       `csolution <solution_name>.csolution.yml run -g CubeMX -c <context>`  
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

Compatible board layers (test packs)
 - File System examples
   - NXP EVKB-IMXRT1050 board
 - Network examples
   - NXP EVKB-IMXRT1050 board
 - USB Device examples
   - STMicroelectronics B-U585I-IOT02A board

### Workflow
 - Open example base directory in VS Code.
 - Open `<solution_name>.csolution.yml` in Editor.
 - Specify Board under `target-types`.
   - Example for STMicroelectronics B-U585I-IOT02A board
     ```yaml
     target-types:
       # Step 1: Specify your board
       - type: B-U585I-IOT02A
         board: STMicroelectronics::B-U585I-IOT02A
     ```
   - Example for NXP EVKB-IMXRT1050 board
     ```yaml
     target-types:
       # Step 1: Specify your board
       - type: EVKB-IMXRT1050
         board: NXP::EVKB-IMXRT1050_MDK
     ```
 - Use the following command (in VS Code Terminal) which also detects compatible layers:  
   `cbuild setup <solution_name>.csolution.yml -l latest --update-rte`
 - Open `<solution_name>.cbuild-idx.yml` and examine detected `target-configurations` and their `Board-layer` variables.
 - Copy desired `Board-Layer` variable to `<solution_name>.csolution.yml` under `target-types`.
   >In case `.cproject.yml` is nested in sub-directories relative to the `.csolution.yml` file,
    adjust the path by adding an additional `../` for each nesting level.
 - Layers are now configured, select desired solution with `Open CMSIS Solution` and continue with typical workflow as described above.
