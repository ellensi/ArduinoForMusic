note_dict = {
    "C" : 0,
    "C#": 1,
    "Db": 1,
    "D" : 2,
    "D#": 3,
    "Eb": 3,
    "E" : 4,
    "F" : 5,
    "F#": 6,
    "Gb": 6,
    "G" : 7,
    "G#": 8,
    "Ab": 8,
    "A" : 9,
    "A#": 10,
    "Bb": 10,
    "B" : 11
}

song_file = None
with open('neverenough.chords','r') as f:
    song_file = f.readlines()

processed_song = []
row = 0
for line in song_file:
    tokens = line.rstrip("\r\n").split(',')
    harmony = len(tokens) - 1
    chords = []
    notes = []
    octave = int(tokens[0])
    for c in tokens[1:-1]:
        chords.append(c)
    for i in range(12):
        note = note_dict[tokens[1 + i % harmony]] + 12 * octave
        while (i > 0) and (note < notes[i-1]):
            note += 12
        notes.append(note)
    processed_line = ",".join(str(x) for x in notes)
    processed_song.append(processed_line + '\n')

with open('neverenough.notes','w') as f:
    f.writelines(processed_song)
