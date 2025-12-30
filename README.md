# 🚀 FreeRTOS System Manager on TM4C1294

## 📌 Overview
This project is a **FreeRTOS-based embedded system** developed on the **TM4C1294 Cortex-M4F LaunchPad** using **TI Code Composer Studio (CCS)**.

It demonstrates **real-time multitasking**, **interrupt handling**, **inter-task communication**, and **runtime system diagnostics**, following an **industry-style modular firmware architecture**.

> ⚠️ This project focuses on *real RTOS integration and debugging*, not just basic LED blinking.

---

## 🎯 Key Features
- ✅ Manual FreeRTOS kernel integration (no auto-generated code)
- ✅ Multiple concurrent RTOS tasks
- ✅ GPIO interrupt → RTOS task notification
- ✅ UART Command Line Interface via **ICDI Virtual COM**
- ✅ ISR-safe inter-task communication using queues
- ✅ Runtime task monitoring using `vTaskList()`
- ✅ RTOS fault hooks (stack overflow, malloc failure, assert)
- ✅ Clean, scalable folder structure

---

## 🧱 System Architecture

![System Architecture](images/RTOS_System_Manager_TM4C1294_flowhart.png)

---

## 📂 Project Folder Structure

```
RTOS_System_Manager_TM4C1294/
│
├── app/ # Application-level RTOS tasks
│ ├── heartbeat_task.c/h
│ ├── button_task.c/h
│ ├── uart_cli_task.c/h
│ └── monitor_task.c/h
│
├── drivers/ # Hardware drivers (RTOS-agnostic)
│ └── uart_drv.c/h
│
├── rtos/ # RTOS hooks
│ └── rtos_hooks.c/h
│
├── lib/
│ └── FreeRTOS/ # FreeRTOS kernel (manual integration)
│ ├── include/
│ │ └── FreeRTOSConfig.h
│ └── Source/
│
├── main.c # System entry point
└── README.md
```

---

## 🛠️ Build Environment

- **Host OS:** Ubuntu Linux
- **IDE:** Code Composer Studio (CCS v12.x)
- **Target MCU:** TM4C1294 (ARM Cortex-M4F)
- **RTOS Kernel:** FreeRTOS (manually integrated)

---

## ⚙️ Hardware & Software Setup

### 🔹 Hardware
- **Board:** TM4C1294 LaunchPad
- **MCU:** ARM Cortex-M4F
- **UART:** ICDI Virtual COM (UART0)
- **Button:** SW1 (PJ0)
- **LED:** PN1

### 🔹 Software
- **IDE:** Code Composer Studio (CCS v12+)
- **RTOS:** FreeRTOS
- **Compiler:** TI ARM (CCS default)
- **Terminal:** PuTTY / TeraTerm / `screen`

---

## 🚀 Functional Description

### 1️⃣ Heartbeat Task

- Toggles onboard LED (PN1)
- Verifies scheduler timing and RTOS startup

### 2️⃣ Button Task

- Button interrupt on **Port J (PJ0)**
- ISR notifies task using `xTaskNotifyFromISR()`
- Demonstrates **interrupt-to-task synchronization**

### 3️⃣ UART CLI Task

- UART0 connected via ICDI (USB virtual COM port)
- Interrupt-driven RX
- Queue-based ISR → task communication
- Supported commands:

status   → System health check
tasks    → Task list (printed by monitor task)

### 4️⃣ Monitor Task

- Periodically prints RTOS task information  
- Uses:
  - `vTaskList()`
- Displays:
  - Task state
  - Priority
  - Stack high-water mark

### 5️⃣ RTOS Hook Functions

Implemented for system robustness:

- `vApplicationMallocFailedHook()`
- `vApplicationStackOverflowHook()`
- `vAssertCalled()`

---

## 🧪 How to Run the Project

1. Open the project in **Code Composer Studio**
2. Build the project:
   ```text
   Project → Build
3. Flash the code to **TM4C1294 LaunchPad**
4. Open a serial terminal with the following settings:
   - **Baudrate:** 115200  
   - **Data bits:** 8  
   - **Parity:** None  
   - **Stop bits:** 1  
   - **Flow control:** None  
5. Press **RESET** on the board
   
### ✅ Expected Output

> RTOS CLI Ready

---

## 💻 Example Commands
status
> System OK

tasks
> (Task list printed every 5 seconds by monitor task)

---

## 🧠 RTOS Concepts Demonstrated
- Preemptive scheduling
- Task priorities & stack sizing
- ISR-safe APIs
- Task notifications vs queues
- FreeRTOS configuration & hooks
- Runtime diagnostics & debugging

---

## 📌 Why This Project Matters

This project demonstrates how RTOS is used in real embedded products, including:

- Manual FreeRTOS kernel integration
- Debugging linker & configuration issues
- Correct ISR design
- Scalable firmware architecture

---

## 👤 Author

**Darshak Vaghela**  
Embedded Software Engineer  

**Skills:**  
Embedded C, FreeRTOS, ARM Cortex-M, UART, GPIO, Interrupts, Code Composer Studio

---

## 📄 License

This project is provided for learning and demonstration purposes.

