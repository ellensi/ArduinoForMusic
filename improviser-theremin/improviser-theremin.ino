#include <Tone.h>

#define improviserOut 2
#define improviserVcc 3
#define improviserGnd 4

#define thereminOut 5
#define thereminVcc 6
#define thereminGnd 7
#define averageCount 10

#define sensorTriggerPin 12
#define sensorEchoPin 13

Tone improviserTone;
Tone thereminTone;

int lastTickTime = 0;
int freq = 440;
long queue[averageCount] = {0};

void setup() {
  pinMode(sensorEchoPin, INPUT);
  pinMode(sensorTriggerPin, OUTPUT);
  pinMode(improviserOut, OUTPUT);
  pinMode(thereminOut, OUTPUT);

  pinMode(improviserVcc, OUTPUT); digitalWrite(improviserVcc, HIGH);
  pinMode(improviserGnd, OUTPUT); digitalWrite(improviserGnd, LOW);
  pinMode(thereminVcc, OUTPUT); digitalWrite(thereminVcc, HIGH);
  pinMode(thereminGnd, OUTPUT); digitalWrite(thereminGnd, LOW);

  improviserTone.begin(improviserOut);
  thereminTone.begin(thereminOut);

  digitalWrite(sensorTriggerPin, LOW);
  delay(2);
}

void loop() {
  long duration;
  int note;
  float noteApprox, freq;

  digitalWrite(sensorTriggerPin, HIGH);
  delay(10);
  digitalWrite(sensorTriggerPin, LOW);

  duration = pulseIn(sensorEchoPin, HIGH);

  /* Improviser */
  if ((millis() - 200) > lastTickTime) {
    noteApprox = log(duration / 12000.0) * 39.86313714;
    note = round(noteApprox);
    freq = 128 * 440.0 * pow(1.059463094, note);

    if (freq < 2000) {
      improviserTone.play(freq);
    } else {
      improviserTone.stop();
    }
    lastTickTime = millis();
  }

  /* Theremin */
  if (duration < 5000) {
    for (int i = averageCount - 1; i > 0; i--) {
      queue[i] = queue[i - 1];
    }
    queue[0] = 758714 / duration;
  } else {
    thereminTone.stop();
    return;
  }

  float average = 0; int qcount = 0;
  for (int i = averageCount - 1; i >= 0; i--) {
    average += queue[i];
    qcount++;
  }
  average /= qcount;
  thereminTone.play(average);
}

