import tkinter as tk
import serial
import time

# Remplace 'COM3' par le port de ton Arduino
arduino = serial.Serial('COM3', 9600)
time.sleep(2)  # Attente que l’Arduino démarre

def led_on():
    arduino.write(b'1')

def led_off():
    arduino.write(b'0')

# Fenêtre principale
root = tk.Tk()
root.title("Contrôle LED Arduino")

# Boutons
btn_on = tk.Button(root, text="Allumer la LED 🔆", command=led_on, bg="green", fg="white", font=("Arial", 16))
btn_on.pack(pady=10, padx=20)

btn_off = tk.Button(root, text="Éteindre la LED 🌑", command=led_off, bg="red", fg="white", font=("Arial", 16))
btn_off.pack(pady=10, padx=20)

# Lancer la fenêtre
root.mainloop()