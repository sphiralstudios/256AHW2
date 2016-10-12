# Faust Based Basic Synth

This example project demonstrates how Faust (<http://faust.grame.fr>) can be used with JUCE to create audio synthesizers.

## Instructions

The C++ code corresponding to `Source/faust/saw.dsp` is `Source/faust/Saw.h`. It was generated using the following command:

```
faust -a arch.cpp -i -cn Saw saw.dsp -o Saw.h
```

where:

* `-a` designates the Faust architecture file (C++ wrapper)
* `-i` indicates to inline the C++ code of `arch.cpp` in the resulting C++ file (check `arch.cpp` for more information)
* `-cn` designates the name of the generated C++ class

Thus, if changes are made to `saw.dsp`, this command needs to be run in order for them to be reflected to `Saw.h`.

---

Implemented by Romain Michon (rmichonATccrmaDOTstanfordDOTedu) for Music 256a / CS 476a (fall 2016).