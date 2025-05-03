# importing libraries
import tkinter as tk 
import serial
import threading
import time

#serial port setup 

serial_port = serial.Serial('COM6', 9600)
print("accessing ", serial_port.port)

running = True

# initalizing values
tc_labels = ["1", "2", "3", "4", "5"]
pt_labels = ["PT1", "PT2", "PT3", "PT4", "PT5", "PT6"]

tc_values = [0, 0, 0, 0, 0]
pt_values = [0, 0, 0, 0, 0, 0]



# GUI Style Setup 
#BACKGROUND_COLOR = "#121212" # Charcol Grey
#FOREGROUND_COLOR =  "#228B22"  # Forest Green

# brat mode
BACKGROUND_COLOR = "#8ACE00" # Lime Green
FOREGROUND_COLOR =  "#121212"  # Charcol Grey

# fonts 
HEADER_FONT = ("Helvetica", 18, "bold")
LABEL_FONT = ("Helvetica", 14)
VALUE_FONT = ("Helvetica", 14, "bold")
FUNNI_FONT = ("Helvetica", 12, "italic")


#reading serial port data

def read_serial():  
    while running:
        try:
            if serial_port.in_waiting:
                line = serial_port.readline().decode().strip()
                if line.startswith("TC:"):
                    data = line.replace("TC:", "").split(",")
                    for i in range(min(5,len(data))):
                        tc_values[i] = data[i]
                elif line.startswith("PT:"):
                    data = line.replace("PT:", "").split(",")
                    for i in range(min(6,len(data))):
                        pt_values[i] = data[i]
            time.sleep(0.05)  #  sleep for 50 ms to reduce CPU usage
        except Exception as e:
            print("Serial Read Error: ", e)

#updating GUI
def update_gui():
    for i in range(5):
        tc_value_labels[i].config(text=f"{tc_values[i]} °C")
    for i in range(6):
        pt_value_labels[i].config(text=f"{pt_values[i]} psi") 
    root.after(250, update_gui) #refresh gui every 250 ms

def on_closing():
    global running
    running = False
    serial_port.close()
    root.destroy()

#creating gui
root = tk.Tk()
root.title("CPP LRL Academy DAQ GUI")
root.configure(bg=BACKGROUND_COLOR)

# Set window size and center it
window_width = 800
window_height = 400
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()
center_x = int(screen_width/2 - window_width/2)
center_y = int(screen_height/2 - window_height/2)
root.geometry(f"{window_width}x{window_height}+{center_x}+{center_y}")


#TC table
tk.Label(root, text="Wall", font=HEADER_FONT, bg=BACKGROUND_COLOR, fg=FOREGROUND_COLOR).grid(row=0, column=0, padx=10)
tk.Label(root, text="Temp (°C)", font=HEADER_FONT, bg=BACKGROUND_COLOR, fg=FOREGROUND_COLOR).grid(row=0, column=1, padx=10)


tc_value_labels = []
for i, label in enumerate(tc_labels):
    tk.Label(root, text=label, font=LABEL_FONT, bg=BACKGROUND_COLOR, fg=FOREGROUND_COLOR).grid(row=i+1, column=0, sticky="w", padx=10)
    value_label = tk.Label(root, text="-- °C", font=VALUE_FONT, bg=BACKGROUND_COLOR, fg=FOREGROUND_COLOR)
    value_label.grid(row=i+1, column=1, padx=10)
    tc_value_labels.append(value_label)

#PT table
tk.Label(root, text="PT #", font=HEADER_FONT, bg=BACKGROUND_COLOR, fg=FOREGROUND_COLOR).grid(row=0, column=2, padx=40)
tk.Label(root, text="Pressure (psi)", font=HEADER_FONT, bg=BACKGROUND_COLOR, fg=FOREGROUND_COLOR).grid(row=0, column=3, padx=10)

pt_value_labels = []
for i, label in enumerate(pt_labels):
    tk.Label(root, text=label, font=LABEL_FONT, bg=BACKGROUND_COLOR, fg=FOREGROUND_COLOR).grid(row=i+1, column=2, sticky="w", padx=40) 
    value_label = tk.Label(root, text="-- psi", font=VALUE_FONT, bg=BACKGROUND_COLOR, fg=FOREGROUND_COLOR)
    value_label.grid(row=i+1, column=3, padx=10)
    pt_value_labels.append(value_label)

# Add meme text at bottom
meme_text = tk.Label(root, text="it's giving... data", font=FUNNI_FONT, bg=BACKGROUND_COLOR, fg=FOREGROUND_COLOR)
meme_text.place(x=300, y=370)  # Adjust position if needed


#handle window closing
#root.protocol("WM_DELETE_WINDOW", on_closing)


# multithreading 
thread = threading.Thread(target = read_serial)
thread.daemon = True
thread.start()


# GUI updates
update_gui()
root.mainloop()