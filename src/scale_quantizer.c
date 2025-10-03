#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <stdlib.h>
#include <stdio.h>
#include "scale_quantizer.h"

static LV2_Handle instantiate(
    const LV2_Descriptor* descriptor,
    double rate,
    const char* bundle_path,
    const LV2_Feature* const* features)
{
    fprintf(stderr, "DEBUG: instantiate() called\n");
    // # void* plugin = calloc(1, 1); just 1 byte for testing    
    ScaleQuantizer* plugin = (ScaleQuantizer*) calloc(1, sizeof(ScaleQuantizer));
    // fprintf(stderr, "DEBUG: Plugin allocated at %p\n", plugin);

    // URID Maping
    LV2_URID_Map* map = NULL;
    for (int i = 0; features[i]; i++) {
        if (strcmp(features[i]->URI, LV2_URID__map) == 0) {
            map = (LV2_URID_Map*)features[i]->data;
        }
    }
    
    if (!map) {
        free(plugin);
        return NULL;
    }

    plugin->map = map;
    plugin->midi_Event = map->map(map->handle, LV2_MIDI__MidiEvent);

    // copy scale _IO_wide_data
    memcpy( (void*)plugin->MODES, MODES, sizeof(MODES) );
    memcpy( (void*)plugin->MODE_LENGTHS, MODE_LENGTHS, sizeof(MODE_LENGTHS));
    return (LV2_Handle)plugin;
}




static void connect_port(LV2_Handle instance, uint32_t port, void* data) {
    fprintf(stderr, "DEBUG: connect_port(%d) called\n", port);
    ScaleQuantizer* plugin = (ScaleQuantizer*)instance;

    switch ((PortIndex)port) {
        case PORT_SCALE_MODE:
            plugin->scale_mode = (const float*)data;
            break;
        case PORT_ROOT_NOTE:
            plugin->root_note = (float*)data;
            break;
        case PORT_INPUT:
            plugin->input = (const float*)data;
            break;
        case PORT_OUTPUT:
            plugin->output = (float*)data;
            break;
  }


}

static void run(LV2_Handle instance, uint32_t sample_count) {
    // fprintf(stderr, "DEBUG: run() called - PLUGIN WORKS!\n"); / comenting this, makes cmd line available and usablemon
    ScaleQuantizer* plugin = (ScaleQuantizer*)instance;

}

static void cleanup(LV2_Handle instance) {
    fprintf(stderr, "DEBUG: cleanup() called\n");
    free(instance);
}

static const LV2_Descriptor descriptor = {
    //"https://github.com/JBrumby/scale-quantizer",
    SCALE_QUANTIZER_URI, // now with var from header_file
    instantiate,
    connect_port,
    NULL,
    run,
    NULL,
    cleanup,
    NULL
};

// LV2 Entry Point
LV2_SYMBOL_EXPORT const LV2_Descriptor* lv2_descriptor(uint32_t index) {
    fprintf(stderr, "DEBUG: lv2_descriptor(%d) called\n", index);
    return index == 0 ? &descriptor : NULL;
}