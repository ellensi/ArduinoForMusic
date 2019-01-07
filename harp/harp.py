import RPi.GPIO as GPIO
import fluidsynth
import time

#SENSORS = [ 2,3,17,27,22,10,9,11,6,13,19,26 ]
SENSORS = [ 26,19,13,6,11,9,10,22,27,17,3,2 ]

GPIO.setmode(GPIO.BCM)
for sensor in SENSORS:
    GPIO.setup(sensor, GPIO.IN)

tone_file = None
with open('neverenough.notes','r') as f:
    tone_file = f.readlines()

tone_list = []
length = len(SENSORS)
prev = [1 for x in range(length)]
row = 0
for line in tone_file:
    l = line.split(',')
    tone = []
    for t in l:
        tone.append(int(t))
    tone[1] = tone[2]
    tone[11] = tone[10]
    tone_list.append(tone)
row = -1
changechordtime = time.time()
playtonic = True

fs = fluidsynth.Synth()
fs.start('alsa')
sffluid = fs.sfload('/usr/share/sounds/sf2/FluidR3_GM.sf2')
fs.program_select(0, sffluid, 0, 46)
print('Ready!')

while 1:
    for i in range(length):
        reading = GPIO.input(SENSORS[i])
        #print("%i:%i" % (SENSORS[i], reading))
        if prev[i] and not reading:
            if i == 0:
                currenttime = time.time()
                if currenttime - changechordtime > 0.5:
                    row = (row + 1) % len(tone_list)
                    changechordtime = currenttime
                    playtonic = True
                else:
                    playtonic = False
                #print("Change chord")
            if playtonic or i > 0:
                fs.noteon(0, tone_list[row][i], 127)
        prev[i] = reading
    time.sleep(0.01)












