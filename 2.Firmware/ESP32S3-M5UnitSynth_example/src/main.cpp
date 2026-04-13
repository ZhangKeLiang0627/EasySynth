#include <Arduino.h>
#include "M5UnitSynth.h"

M5UnitSynth synth;

// Define the drum notes for a basic drum pattern
int kick = 36;  // Kick drum note
int snare = 38; // Snare drum note
int hiHat = 42; // Closed hi-hat note

// Define the chord progression (Cmaj7, Dm7, Em7, Fmaj7)
int chords[4][4] = {
    {64, 67, 71, 74}, // Em7 (E G B D)
    {65, 69, 72, 76}, // Fmaj7 (F A C E)
    {62, 65, 69, 72}, // Dm7 (D F A C)
    {60, 64, 67, 71}, // Cmaj7 (C E G B)
};

TaskHandle_t _drum_loop_handler;

void chord_loop_handler(void *param)
{
    for (;;)
    {
        // Play each chord for one bar (4 beats)
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                synth.setNoteOn(0, chords[i][j], 65);
            }
            delay(1000); // Delay for 2 seconds (1 bar)
            synth.setAllNotesOff(0);
        }
    }
}

void drum_loop_handler(void *param)
{
    for (;;)
    {
        synth.setNoteOn(9, kick, 127);
        delay(167);
        synth.setNoteOn(9, hiHat, 127);
        delay(137);
        synth.setNoteOn(9, kick, 127);
        delay(197);
        synth.setNoteOn(9, snare, 127);
        delay(167);
        synth.setNoteOn(9, hiHat, 127);
        delay(167);
        synth.setNoteOn(9, kick, 127);
        delay(167);
        synth.setNoteOn(9, hiHat, 127);
        delay(167);
        synth.setNoteOn(9, kick, 127);
        delay(167);
        synth.setNoteOn(9, hiHat, 127);
        delay(167);
        synth.setNoteOn(9, hiHat, 127);
        delay(167);
        synth.setNoteOn(9, snare, 127);
        delay(167);
        synth.setNoteOn(9, hiHat, 127);
        delay(167);

        synth.setNoteOn(9, kick, 127);
        delay(200);
        synth.setNoteOn(9, hiHat, 127);
        delay(100);
        synth.setNoteOn(9, snare, 127);
        delay(600);
        synth.setNoteOn(9, hiHat, 127);
        delay(100);
        synth.setNoteOn(9, kick, 127);
        delay(100);
        synth.setNoteOn(9, hiHat, 127);
        delay(100);
        synth.setNoteOn(9, kick, 127);
        delay(300);
        synth.setNoteOn(9, snare, 127);
        delay(400);
        synth.setNoteOn(9, hiHat, 127);
        delay(100);
    }
}

void setup()
{
    Serial.begin(115200);
    synth.begin(&Serial2, UNIT_SYNTH_BAUD, 16, 17);
    Serial.println("M5Unit Synth");

    synth.setInstrument(0, 0, Gunshot);
    synth.setChorus(0, 0, 80, 127, 40);
    synth.setVolume(0, 127); // 0-127
    synth.setVolume(9, 127); // 0-127

    xTaskCreate(drum_loop_handler, "drum", 1024 * 2, nullptr, 5, &_drum_loop_handler);
    vTaskSuspend(_drum_loop_handler);
    xTaskCreate(chord_loop_handler, "chord", 1024 * 2, nullptr, 5, nullptr);
    delay(12000);
    vTaskResume(_drum_loop_handler);
}

void loop()
{
    


}
