# 🤖 ROVER – Smart Welcome Bot

ROVER (Smart Welcome Bot) is an autonomous, low-cost mobile robot designed to detect human presence, approach the person, and greet them using voice interaction. The project demonstrates **embedded systems, robotics, and rule-based AI concepts** using simple and budget-friendly hardware.

---

## 📌 Project Overview

In many colleges and public places, welcoming visitors is handled manually or through static systems. This project aims to provide an **automated and interactive solution** that works independently without continuous human involvement.

The robot uses an **ultrasonic sensor** to detect human presence, intelligently controls its movement using an **ESP32 microcontroller**, and plays a greeting message through a **DFPlayer Mini audio module**.

---

## ✨ Key Features

- Autonomous human presence detection  
- Intelligent movement with speed adaptation  
- Voice-based greeting using audio playback  
- Rule-based AI decision-making  
- Low-cost and easy-to-build design  
- Suitable for indoor environments  

---

## 🧠 AI Concept Used

This project implements **rule-based Artificial Intelligence**, where the robot:
- Analyzes sensor data
- Confirms consistent human presence
- Makes autonomous decisions for movement and interaction

> *No machine learning is used; intelligence is achieved through optimized logic and decision rules.*

---

## 🧰 Hardware Components

- ESP32 Development Board  
- HC-SR04 Ultrasonic Sensor  
- L298N Motor Driver  
- DC Geared Motors with Wheels  
- DFPlayer Mini Audio Module  
- Speaker  
- microSD Card (FAT32)  
- Battery & Power Supply  
- Chassis (Foam board / Sunboard with vinyl finish)

---

## 💻 Software & Tools

- Arduino IDE  
- ESP32 Board Package  
- Embedded C/C++  
- Serial Communication (UART)  

---

## 🔌 Working Principle

1. The ultrasonic sensor continuously measures distance.  
2. ESP32 processes sensor data and confirms human presence using multiple readings.  
3. The robot approaches the detected person with adaptive speed control.  
4. When the person is close enough, the robot stops and plays a greeting audio.  
5. After greeting, the robot resumes searching for the next person.

---

## ▶️ How to Run the Project

1. Install **Arduino IDE**
2. Add **ESP32 board support**
3. Connect ESP32 via USB
4. Upload `main.ino`
5. Insert microSD card with audio file:
/mp3/001.mp3
6. Power ON the robot

---

## 🚀 Applications

- College & department reception  
- Exhibitions and project demos  
- Smart campus assistance  
- Educational robotics learning  

---

## 🔮 Future Enhancements

- Camera-based face detection  
- Voice recognition  
- PIR + ultrasonic hybrid detection  
- IoT-based visitor analytics  
- Emotion-based greeting  

---

## 🎓 Academic Context

This project was developed as a **Mini Project** and is planned to be extended into a **Major Project** with advanced AI and IoT capabilities.

---

## 🙏 Acknowledgement

I sincerely thank my project guide for the guidance and support, and my project team for their continuous cooperation and hard work throughout this project.

---

## 📜 License

This project is intended for **educational and learning purposes**.

---

⭐ *If you find this project interesting, feel free to star the repository and share feedback!*
---

## 📂 Project Structure
