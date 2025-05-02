from flask import Flask, request, render_template
import json
import serial
import sys

app = Flask(__name__)

# Load the database
DB = {}
try:
    with open('DB.json', 'r') as file:
        DB = json.load(file)
    print("Active Database:\n", DB)
except FileNotFoundError:
    print("Database file DB.json not found.")
except json.JSONDecodeError:
    print("Database file DB.json is corrupted or not a valid JSON.")

# Establish serial connection to Arduino
try:
    arduino = serial.Serial('/dev/ttyUSB0', 9600)  # Update to your Arduino's serial port
except serial.SerialException:
    print("Could not open serial port. Make sure Arduino is connected.")
    sys.exit(1)

@app.route('/')
def home():
    return render_template('form.html')  # Ensure form.html exists in the templates folder

@app.route('/submit', methods=['POST'])
def submit():
    name = request.form.get('name', '').lower().strip()
    roll = request.form.get('roll', '').lower().strip()

    if not name or not roll:
        return "Name or Roll Number is missing. Please provide both."

    try:
        if roll in DB:
            arduino.write(b'open_gate\n')
            response = arduino.readline().decode().strip()
            if response == "DOOR_OPENED":
                return "Welcome to ACPS LAB"
            else:
                return "Error: Door mechanism not responding properly"
        else:
            arduino.write(b'close_gate\n')
            response = arduino.readline().decode().strip()
            return f"Access denied, please {name} try again"
    except serial.SerialException as e:
        return f"Error communicating with door: {str(e)}"

@app.errorhandler(Exception)
def handle_exception(e):
    return f"An error occurred: {str(e)}", 500

if __name__ == '__main__':
    app.run(host="0.0.0.0", port=5000, debug=True)
