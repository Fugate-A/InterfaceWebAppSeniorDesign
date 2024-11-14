#ifndef TAGOG_H
#define TAGOG_H

#include <Arduino.h>
#include "link.h"

// External declaration of the global variable uwb_data
extern struct MyLink* uwb_data;

// Function declarations for Tag operations
void setupTag();
void loopTag();

// Function declaration for generating JSON payload
void make_link_json(struct MyLink* p, String* s);

#endif
