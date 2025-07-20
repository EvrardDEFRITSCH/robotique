import tkinter as tk
import serial
import time

# Remplace 'COM3' par le port de ton Arduino
arduino = serial.Serial('COM7', 9600)
time.sleep(2)  # Attente que l’Arduino démarre

def led_on():
    arduino.write(b'1')

def led_off():
    arduino.write(b'0')

def led_cli():
    arduino.write(b'3')  # Envoie la commande pour clignoter la LED

# Fenêtre principale
fenetre = tk.Tk()
fenetre.title("IHM Arduino")    # Titre de la fenêtre
fenetre.configure(bg='#252525')  # Couleur de fond de la fenêtre
fenetre.geometry("1000x600")    # Taille de la fenêtre

cadreTest = tk.Frame(fenetre, bg="#252525") # Cadre pour les boutons test de la led
cadreTest.place(x=10, y=100, width=150,height=150) # Positionnement du cadre 


# Boutons
text = tk.Label(cadreTest, text="Test LED interne", bg="#252525", fg="White", font=("Arial", 12),justify="left")
text.pack(pady=0, padx=0)
btn_on = tk.Button(cadreTest, text="ON ", command=led_on, bg="grey", fg="white", font=("Arial", 9),justify="left",width=15)
btn_on.pack(pady=0, padx=0)

btn_off = tk.Button(cadreTest, text="OFF ", command=led_off, bg="grey", fg="white", font=("Arial", 9),justify="left",width=15)
btn_off.pack(pady=0, padx=0)

# Lectur capteur ultrason
cadreUltrason = tk.Frame(fenetre, bg="#4D4D4D") 
cadreUltrason.place(x=200, y=100, width=150, height=150)  # Positionnement du cadre


def distance():
    valeur = arduino.readline().decode('utf-8').strip()  # Lecture de la valeur depuis l'Arduino
    distance_label.config(text=f"Distance: {valeur} cm")  # Mise à jour de l'étiquette avec la distance
    fenetre.after(100, distance)  # Appel de la fonction toutes les 100 ms
    
distance_label = tk.Label(cadreUltrason, text="Distance : ??? cm", font=("Arial", 18))
distance_label.pack(padx=20, pady=20)
distance()  # Démarrer la lecture de la distance

btn_distance = tk.Button(cadreUltrason, text="ON ", command=distance, bg="grey", fg="white", font=("Arial", 9),justify="center",width=15)
btn_distance.pack(pady=0, padx=0)


# Lancer la fenêtre
fenetre.mainloop()