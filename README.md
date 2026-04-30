# UltraTrack-Live-visualization.iot

Ultrasonic Distance Monitoring System (ESP32 + Flask Project)
## Overview

This project is an IoT-based Distance Monitoring System that uses an ultrasonic sensor connected to an ESP32 to measure distance in real time. The measured data is sent to a Flask backend server, stored in a database, and displayed on a web dashboard with a live graph.

The system also includes a simple alert mechanism when an object comes too close.

## Features

Real-time distance measurement using ultrasonic sensor
ESP32 to Flask communication using HTTP POST
Database storage using SQLite
Live dashboard with dynamic graph (Chart.js)
Threshold-based alert for close objects
Continuous data monitoring

## Technologies Used

ESP32
Arduino (C++)
Python Flask
Flask SQLAlchemy
HTML, CSS, JavaScript
Chart.js

## Project Structure

ultrTrack-live-visualization.iot/
│
├── src/main.cpp
├── app.py
├── templates/
│ └── index.html
├── iot.db
└── README.md

## How to Run

1. Setup ESP32
Connect ultrasonic sensor (TRIG → GPIO 4, ECHO → GPIO 2)
Update WiFi credentials
Update server IP address in code
Upload code using Arduino IDE or PlatformIO
2. Setup Flask Server

Install dependencies:
pip install flask flask_sqlalchemy

Run server:
python app.py

Server runs on:
http://0.0.0.0:5000

3. Run System
Power ESP32
Ensure ESP32 and PC are on same network
Open browser:
http://localhost:5000
View live distance values and graph

## How It Works

The ultrasonic sensor measures distance using echo time.
ESP32 calculates the distance and sends it to the Flask server.
Flask stores the data in a database.
Frontend fetches the data and displays it in real time using a graph.
If distance is below a threshold (e.g., 10 cm), an alert is triggered in the backend.

## API Endpoints

POST /distance
Receives distance data from ESP32

GET /distance
Returns stored distance data for dashboard

## Future Improvements

Add buzzer or LED alert for hardware notification
Integrate Telegram or mobile alerts
Use WebSockets for faster real-time updates
Add object detection classification
Deploy system to cloud server

## Author

Harsha G
Learning Python | Embedded Systems | IoT
