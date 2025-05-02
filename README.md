# Automatic Door Lock System with QR Code Authentication

## Overview
This project implements an automated door lock system that uses QR code authentication for access control. When a person scans the QR code posted on the door using the web interface, the system checks their credentials against a database and controls the door lock accordingly.

## System Components
- Flask web server
- Arduino-controlled door lock mechanism
- QR code authentication
- JSON database for user verification

## How It Works
1. A QR code is mounted on the door
2. Users scan the QR code which opens the web interface
3. The web interface prompts for name and roll number
4. System verifies credentials against the database
5. If authorized:
   - Displays "Welcome to ACPS LAB"
   - Signals Arduino to unlock the door
6. If unauthorized:
   - Displays access denied message
   - Door remains locked

## Setup Requirements
1. Python dependencies:
   ```
   flask
   pyserial
   ```
2. Arduino setup:
   - Connect Arduino to USB port
   - Upload the appropriate sketch
   - Update serial port in main.py if needed

## Configuration
1. Create a `DB.json` file with authorized users:
   ```json
   {
       "roll123": {"name": "John Doe"},
       "roll456": {"name": "Jane Smith"}
   }
   ```
2. Ensure Arduino is connected to the correct port (default: /dev/ttyUSB0)

## Running the System
1. Connect the Arduino
2. Start the Flask server:
   ```
   python main.py
   ```
3. Access the system through the QR code or directly via http://[server-ip]:5000

## Security Notes
- Keep the DB.json file secure and regularly updated
- Monitor access logs
- Regularly update authorized user list
