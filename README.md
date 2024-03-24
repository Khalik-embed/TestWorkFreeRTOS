# STM32F103C6 UART Bridge Project

## Overview
This project implements a UART bridge using the STM32F103C6 microcontroller. It is designed to facilitate communication between two UART peripherals by acting as a middleman to parse, log, and relay commands.

## Features
The project utilizes four main tasks to achieve its functionality:

1. **Logger Task**:
   - Function: Responsible for logging activities.
   - Hardware: Utilizes UART0 for logging operations.

2. **Dispatcher Task**:
   - Function: Manages interrupts and parses commands.
   - Hardware: Operates using UART0.

3. **LeftUart Task**:
   - Function: Controls the left arm of the bridge, receiving input signals and forwarding them to the right arm.
   - Hardware: Uses UART2 and UART3 for operations.

4. **RightUart Task**:
   - Function: Manages the right arm of the bridge, receiving input signals and sending them to the left arm.
   - Hardware: Employs UART3 and UART2 for its functionality.

## Inter-Task Communication
To ensure smooth data flow between tasks, queues and signals are utilized:

- **Queues**: Employed for transferring received bytes from one side of the bridge to the other.
- **Signals**: Used as flags to signify the completion of data transmission.

## Project Structure
The project leverages the STM32CubeIDE-generated structure for organized and efficient development:

- Peripheral control functions are located within `CORE/BSP`.
- Logging functions are situated in `CORE/LOG`.
- Command parsing functions are found in `middleware`.

## Getting Started
To get started with the project, ensure you have STM32CubeIDE installed and set up for STM32F103C6 development. Clone the project and open it within STM32CubeIDE to browse the code and project structure. Follow the project-specific setup instructions documented within the code to configure your development environment.

## Contributing
Contributions to the UART bridge project are welcome. Whether it's feature improvements, bug fixes, or documentation updates, feel free to fork the repository and submit a pull request.

## License
The project is released under the [MIT License](LICENSE). See the LICENSE file for more details.