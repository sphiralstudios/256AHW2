// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple sawtooth synthesizer

import("stdfaust.lib");

// smoo = smooth(0.999) which is just a "normalized one pole filter" configured as a lowpass
freq = nentry("freq",440,20,20000,0.01) : si.smoo;
gain = nentry("gain",1,0,1,0.01) : si.smoo;
gate = button("gate") : si.smoo;

process = hgroup("saw",os.sawtooth(freq) * gain * gate);