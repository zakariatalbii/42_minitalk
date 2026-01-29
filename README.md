# 📡 minitalk

## 📌 Overview

**minitalk** is a small client–server communication project written in **C**, developed as part of the 42 cursus.  
The goal is to transmit a string from a **client process** to a **server process** using only **UNIX signals** (`SIGUSR1` and `SIGUSR2`).

This project focuses on:
- Inter-process communication (IPC)
- Signal handling and synchronization
- Bitwise operations
- Reliable data transmission under strict constraints

---

## 🧠 General Concept

The communication channel between the client and the server is implemented using **signals only**.

- `SIGUSR1` represents bit **1**
- `SIGUSR2` represents bit **0**
- Each character is sent **bit by bit**
- The server reconstructs characters and prints them in real time

---

## ⚙️ Mandatory Part — How It Works

### 🖥️ Server Initialization

- The server prints its **PID**
- Installs a `sigaction` handler for `SIGUSR1` and `SIGUSR2`
- Enters an infinite loop waiting for signals

The handler:
- Accumulates bits
- Rebuilds characters
- Prints characters once a full byte is received

---

### 💻 Client Message Encoding

The client:
1. Takes the server PID and a string as arguments
2. Iterates over each character
3. Sends **8 signals per character** (1 bit at a time)
4. Sends bits **from MSB to LSB**

Each bit:
- `1` → `SIGUSR1`
- `0` → `SIGUSR2`

A small delay (`usleep`) is used to prevent signal loss.

---

### 🔁 Bit Reconstruction (Server Side)

On the server:
- A static counter tracks the current bit position
- A static variable accumulates bits into a character
- Once 8 bits are received:
	- The character is printed
	- Internal state is reset

This ensures deterministic decoding.

---

### 🧩 Synchronization Model

- Communication is **unidirectional**
- The server processes one bit at a time
- Timing control ensures reliability
- No busy waiting or polling

This keeps the implementation simple and robust.

---

## ⭐ Bonus Part — Acknowledged Communication

The bonus version improves reliability by introducing **acknowledgements**.

### 🔄 Acknowledgement System

- After receiving a bit, the server sends a signal back to the client
- The client waits for confirmation before sending the next bit
- This guarantees:
	- No signal loss
	- Proper synchronization between processes

---

### 🧠 Bonus Message Flow

1. Client sends one bit
2. Server receives and processes it
3. Server sends an acknowledgment signal
4. Client continues with the next bit

This turns the communication into a **handshaked protocol**.

---

## 🚀 Compilation & Usage

```bash
git clone git@github.com:zakariatalbii/42_minitalk.git
cd 42_minitalk
```

🔨 Compile

```bash
make
```

▶️ Run Server

```bash
./server
```

▶️ Run Client

```bash
./client <SERVER_PID> "Hello World!"
```

---

## 🧪 Error Handling

The project safely handles:
- Invalid PID
- Missing arguments
- Signal errors
- Unexpected termination

Errors are handled gracefully without undefined behavior.

---

## 📊 Technical Notes

- Uses sigaction instead of signal
- Uses static variables inside signal handlers
- Carefully manages timing (usleep)
- Respects async-signal-safe behavior

---

## 📚 What This Project Demonstrates

- Deep understanding of UNIX signals
- Low-level IPC implementation
- Bitwise data encoding
- Signal synchronization techniques
- Writing reliable concurrent logic in C

---

## 🌲 Project Structure

```
.
├── Makefile
├── include/minitalk.h
├── src/
│  ├── server.c
│  ├── client.c
│  └── tools.c
├── bonus/
│  ├── include/minitalk_bonus.h
│  └── src/
│     ├── server_bonus.c
│     ├── client_bonus.c
│     └── tools_bonus.c
└── en.subject.pdf
```

The logic is clearly separated between:
- signal handling
- message encoding/decoding
- utility functions

---

## 👤 Author

**Zakaria Talbi**
- GitHub: [@zakariatalbii](https://github.com/zakariatalbii)

---

## 📜 License

This project is part of the 42 School cursus.