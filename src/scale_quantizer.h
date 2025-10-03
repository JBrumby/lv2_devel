#ifndef SCALE_QUANTIZER_H
#define SCALE_QUANTIZER_H

#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/atom/util.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>
#include <lv2/lv2plug.in/ns/ext/midi/midi.h>

// URIs definieren
#define SCALE_QUANTIZER_URI "https://github.com/JBrumby/scale-quantizer"


// Skalen Enum
typedef enum {
    CHROMATIC,
    MAJOR, 
    MINOR,
    DORIAN,
    MIXOLYDIAN,
    LYDIAN,
    PHRYGIAN,
    LOCRIAN,
    DIMINISHED,
    WHOLE_HALF,
    WHOLE_TONE,
    MINOR_BLUES,
    MINOR_PENTATONIC,
    MAJOR_PENTATONIC,
    HARMONIC_MINOR,
    MELODIC_MINOR,
    SUPER_LOCRIAN,
    BHAIRAV,
    HUNGARIAN_MINOR,
    MINOR_GYPSY,
    HIROJOSHI,
    IN_SEN,
    IWATO,
    KUMOI,
    PELOG,
    SPANISH,
    NUM_MODES
} scale_mode_t;

static const uint8_t MODES[NUM_MODES][12] = {
    [CHROMATIC] = {0,1,2,3,4,5,6,7,8,9,10,11},
    [MAJOR]     = {0,2,4,5,7,9,11},
    [MINOR]     = {0, 2, 3, 5, 7, 8, 10},
    [DORIAN]    = {0, 2, 3, 5, 7, 9, 10},
    [MIXOLYDIAN]= {0, 2, 4, 5, 7, 9, 10},
    [LYDIAN]    = {0, 2, 4, 6, 7, 9, 11},
    [PHRYGIAN]  = {0, 1, 3, 5, 7, 8, 10},
    [LOCRIAN]   = {0, 1, 3, 4, 7, 8, 10},
    [DIMINISHED]= {0, 1, 3, 4, 6, 7, 9, 10}, 
    [WHOLE_HALF]        = {0, 2, 3, 5, 6, 8, 9, 11}, 
    [WHOLE_TONE]        = {0, 2, 4, 6, 8, 10},
    [MINOR_BLUES]       = {0, 3, 5, 6, 7, 10},
    [MINOR_PENTATONIC]  = {0, 3, 5, 7, 10},
    [MAJOR_PENTATONIC]  = {0, 2, 4, 7, 9},
    [HARMONIC_MINOR]    = {0, 2, 3, 5, 7, 8, 11},
    [MELODIC_MINOR]     = {0, 2, 3, 5, 7, 9, 11},
    [SUPER_LOCRIAN]     = {0, 1, 3, 4, 6, 8, 10},
    [BHAIRAV]           = {0, 1, 4, 5, 7, 8, 11},
    [HUNGARIAN_MINOR]   = {0, 2, 3, 6, 7, 8, 11},
    [MINOR_GYPSY]       = {0, 1, 4, 5, 7, 8, 10},
    [HIROJOSHI]         = {0, 2, 3, 7, 8},
    [IN_SEN]            = {0, 1, 5, 7, 10},
  "Iwato":              [0, 1, 5, 6, 10],
  "Kumoi":              [0, 2, 3, 7, 9],
  "Pelog":              [0, 1, 3, 4, 7, 8],
  "Spanish":            [0, 1, 3, 4, 5, 6, 8, 10]
};



typedef enum {
    PORT_INPUT = 0,
    PORT_OUTPU = 1,
    PORT_SCALE_MODE = 2,
    PORT_ROT_NOTE = 3
} PortIndex;

// Plugin Struct
typedef struct {
    // in and out ports
    const void* input;
    void* output;

    // Control Ports
    const float* scale_mode;
    const float* root_note;
} ScaleQuantizer;


#endif