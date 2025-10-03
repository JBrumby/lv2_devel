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
    // # void* plugin = calloc(1, 1); einfach 1 byte u testzwecken    
    ScaleQuantizer* plugin = (ScaleQuantizer*) calloc(1, sizeof(ScaleQuantizer));
    fprintf(stderr, "DEBUG: Plugin allocated at %p\n", plugin);
    
    // filln data
    //plugin.
    
    return plugin;
}




static void connect_port(LV2_Handle instance, uint32_t port, void* data) {
    fprintf(stderr, "DEBUG: connect_port(%d) called\n", port);
    ScaleQuantizer* plugin = (ScaleQuantizer*)instance;

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