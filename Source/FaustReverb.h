//----------------------------------------------------------
//
// Code generated with Faust 0.9.81 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
template <int N> inline float faustpower(float x)            { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline float faustpower<0>(float x)          { return 1; }
template <> 	 inline float faustpower<1>(float x)          { return x; }
template <> 	 inline float faustpower<2>(float x)          { return x*x; }
#endif
// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple Faust architecture file to easily integrate a Faust DSP module
// in a JUCE project

// needed by any Faust arch file
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __misc__
#define __misc__

#include <algorithm>
#include <map>
#include <string.h>
#include <stdlib.h>

/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __meta__
#define __meta__

struct Meta
{
    virtual void declare(const char* key, const char* value) = 0;
    virtual ~Meta() {};
};

#endif

using std::max;
using std::min;

struct XXXX_Meta : std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

inline int lsr(int x, int n)	{ return int(((unsigned int)x) >> n); }

inline int int2pow2(int x)		{ int r = 0; while ((1<<r) < x) r++; return r; }

inline long lopt(char* argv[], const char* name, long def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}

inline bool isopt(char* argv[], const char* name)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
	return false;
}

inline const char* lopts(char* argv[], const char* name, const char* def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
	return def;
}

#endif


// allows to control a Faust DSP module in a simple manner by using parameter's path
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <vector>
#include <map>
#include <string>

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/
 
#ifndef FAUST_UI_H
#define FAUST_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust User Interface
 * This abstract class contains only the method that the faust compiler can
 * generate to describe a DSP interface.
 ******************************************************************************/

class UI
{

    public:

        UI() {}

        virtual ~UI() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
};

//----------------------------------------------------------------
//  Generic decorator
//----------------------------------------------------------------

class DecoratorUI : public UI
{
    protected:
    
        UI* fUI;

    public:
    
        DecoratorUI(UI* ui = 0):fUI(ui)
        {}

        virtual ~DecoratorUI() { delete fUI; }

        // -- widget's layouts
        virtual void openTabBox(const char* label)          { fUI->openTabBox(label); }
        virtual void openHorizontalBox(const char* label)   { fUI->openHorizontalBox(label); }
        virtual void openVerticalBox(const char* label)     { fUI->openVerticalBox(label); }
        virtual void closeBox()                             { fUI->closeBox(); }

        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)         { fUI->addButton(label, zone); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)    { fUI->addCheckButton(label, zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
            { fUI->addVerticalSlider(label, zone, init, min, max, step); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 	
            { fUI->addHorizontalSlider(label, zone, init, min, max, step); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 			
            { fUI->addNumEntry(label, zone, init, min, max, step); }

        // -- passive widgets	
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
            { fUI->addHorizontalBargraph(label, zone, min, max); }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
            { fUI->addVerticalBargraph(label, zone, min, max); }

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) { fUI->declare(zone, key, val); }

};

#endif
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
};

#endif  // FAUST_PATHBUILDER_H

/*******************************************************************************
 * MapUI : Faust User Interface
 * This class creates a map of complete hierarchical path and zones for each UI items.
 ******************************************************************************/

class MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Complete path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
    public:
        
        MapUI() {};
        virtual ~MapUI() {};
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openHorizontalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openVerticalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void closeBox()
        {
            fControlsLevel.pop_back();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // set/get
        void setParamValue(const std::string& path, float value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            }
        }
        
        float getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                return 0.;
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getMap() { return fPathZoneMap; }
        
        int getParamsCount() { return fPathZoneMap.size(); }
        
        std::string getParamAdress(int index) 
        { 
            std::map<std::string, FAUSTFLOAT*>::iterator it = fPathZoneMap.begin();
            while (index-- > 0 && it++ != fPathZoneMap.end()) {}
            return (*it).first;
        }
};

#endif // FAUST_MAPUI_H

// needed by any Faust arch file
/************************************************************************
    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.

 ************************************************************************
 ************************************************************************/
 
/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/

#ifndef __dsp__
#define __dsp__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class UI;
struct Meta;

//----------------------------------------------------------------
//  Signal processor definition
//----------------------------------------------------------------

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        virtual int getNumInputs() = 0;
        virtual int getNumOutputs() = 0;
        virtual void buildUserInterface(UI* ui_interface) = 0;
        virtual int getSampleRate() = 0;
        virtual void init(int samplingRate) = 0;
        virtual void instanceInit(int samplingRate) = 0;
        virtual dsp* clone() = 0;
        virtual void metadata(Meta* m) = 0;
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

//----------------------------------------------------------------
//  Generic decorator
//----------------------------------------------------------------

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = 0):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int samplingRate) { fDSP->init(samplingRate); }
        virtual void instanceInit(int samplingRate) { fDSP->instanceInit(samplingRate); }
        virtual dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { return fDSP->metadata(m); }
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
       
};

//----------------------------------------------------------------
// On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
// flags to avoid costly denormals
//----------------------------------------------------------------

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif

// tags used by the Faust compiler to paste the generated c++ code
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  


#ifndef FAUSTCLASS 
#define FAUSTCLASS FaustReverb
#endif

class FaustReverb : public dsp {
  private:
	FAUSTFLOAT 	fslider0;
	float 	fRec0[2];
	int 	IOTA;
	float 	fVec0[8192];
	FAUSTFLOAT 	fslider1;
	float 	fRec1[2];
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	float 	fConst2;
	FAUSTFLOAT 	fslider4;
	float 	fConst3;
	FAUSTFLOAT 	fslider5;
	float 	fConst4;
	float 	fConst5;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fslider7;
	float 	fConst6;
	FAUSTFLOAT 	fslider8;
	float 	fRec14[2];
	float 	fRec13[2];
	float 	fVec1[8192];
	float 	fConst7;
	int 	iConst8;
	float 	fVec2[1024];
	int 	iConst9;
	float 	fRec11[2];
	float 	fConst10;
	float 	fConst11;
	float 	fRec18[2];
	float 	fRec17[2];
	float 	fVec3[8192];
	float 	fConst12;
	int 	iConst13;
	float 	fVec4[2048];
	int 	iConst14;
	float 	fRec15[2];
	float 	fConst15;
	float 	fConst16;
	float 	fRec22[2];
	float 	fRec21[2];
	float 	fVec5[8192];
	float 	fConst17;
	int 	iConst18;
	float 	fVec6[2048];
	int 	iConst19;
	float 	fRec19[2];
	float 	fConst20;
	float 	fConst21;
	float 	fRec26[2];
	float 	fRec25[2];
	float 	fVec7[8192];
	float 	fConst22;
	int 	iConst23;
	float 	fVec8[1024];
	int 	iConst24;
	float 	fRec23[2];
	float 	fConst25;
	float 	fConst26;
	float 	fRec30[2];
	float 	fRec29[2];
	float 	fVec9[16384];
	float 	fConst27;
	int 	iConst28;
	float 	fVec10[2048];
	int 	iConst29;
	float 	fRec27[2];
	float 	fConst30;
	float 	fConst31;
	float 	fRec34[2];
	float 	fRec33[2];
	float 	fVec11[8192];
	float 	fConst32;
	int 	iConst33;
	float 	fVec12[2048];
	int 	iConst34;
	float 	fRec31[2];
	float 	fConst35;
	float 	fConst36;
	float 	fRec38[2];
	float 	fRec37[2];
	float 	fVec13[16384];
	float 	fConst37;
	int 	iConst38;
	float 	fVec14[2048];
	int 	iConst39;
	float 	fRec35[2];
	float 	fConst40;
	float 	fConst41;
	float 	fRec42[2];
	float 	fRec41[2];
	float 	fVec15[16384];
	float 	fConst42;
	int 	iConst43;
	float 	fVec16[1024];
	int 	iConst44;
	float 	fRec39[2];
	float 	fRec3[3];
	float 	fRec4[3];
	float 	fRec5[3];
	float 	fRec6[3];
	float 	fRec7[3];
	float 	fRec8[3];
	float 	fRec9[3];
	float 	fRec10[3];
	float 	fRec2[3];
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	float 	fRec43[3];
	float 	fRec44[3];
	float 	fRec45[3];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) 	{ 
		m->declare("delay.lib/name", "Faust Delay Library");
		m->declare("delay.lib/version", "0.0");
		m->declare("math.lib/name", "Faust Math Library");
		m->declare("math.lib/version", "2.0");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("signal.lib/name", "Faust Signal Routing Library");
		m->declare("signal.lib/version", "0.0");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/version", "2.0");
		m->declare("reverb.lib/name", "Faust Reverb Library");
		m->declare("reverb.lib/version", "0.0");
		m->declare("basic.lib/name", "Faust Basic Element Library");
		m->declare("basic.lib/version", "0.0");
		m->declare("route.lib/name", "Faust Signal Routing Library");
		m->declare("route.lib/version", "0.0");
	}

	virtual int getNumInputs() 	{ return 1; }
	virtual int getNumOutputs() 	{ return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fslider0 = -2e+01f;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		IOTA = 0;
		for (int i=0; i<8192; i++) fVec0[i] = 0;
		fslider1 = 0.0f;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		fConst0 = min(1.92e+05f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (6.2831855f / fConst0);
		fslider2 = 315.0f;
		fslider3 = 0.0f;
		fConst2 = (0.001f * fConst0);
		fslider4 = 6e+01f;
		fConst3 = (6.2831855f / float(fConst0));
		fslider5 = 6e+03f;
		fConst4 = floorf((0.5f + (0.153129f * fConst0)));
		fConst5 = ((0 - (6.9077554f * fConst4)) / fConst0);
		fslider6 = 2.0f;
		fslider7 = 3.0f;
		fConst6 = (3.1415927f / fConst0);
		fslider8 = 2e+02f;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<8192; i++) fVec1[i] = 0;
		fConst7 = floorf((0.5f + (0.020346f * fConst0)));
		iConst8 = int((int((fConst4 - fConst7)) & 8191));
		for (int i=0; i<1024; i++) fVec2[i] = 0;
		iConst9 = int((int((fConst7 - 1)) & 1023));
		for (int i=0; i<2; i++) fRec11[i] = 0;
		fConst10 = floorf((0.5f + (0.174713f * fConst0)));
		fConst11 = ((0 - (6.9077554f * fConst10)) / fConst0);
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<8192; i++) fVec3[i] = 0;
		fConst12 = floorf((0.5f + (0.022904f * fConst0)));
		iConst13 = int((int((fConst10 - fConst12)) & 8191));
		for (int i=0; i<2048; i++) fVec4[i] = 0;
		iConst14 = int((int((fConst12 - 1)) & 2047));
		for (int i=0; i<2; i++) fRec15[i] = 0;
		fConst15 = floorf((0.5f + (0.127837f * fConst0)));
		fConst16 = ((0 - (6.9077554f * fConst15)) / fConst0);
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<8192; i++) fVec5[i] = 0;
		fConst17 = floorf((0.5f + (0.031604f * fConst0)));
		iConst18 = int((int((fConst15 - fConst17)) & 8191));
		for (int i=0; i<2048; i++) fVec6[i] = 0;
		iConst19 = int((int((fConst17 - 1)) & 2047));
		for (int i=0; i<2; i++) fRec19[i] = 0;
		fConst20 = floorf((0.5f + (0.125f * fConst0)));
		fConst21 = ((0 - (6.9077554f * fConst20)) / fConst0);
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<8192; i++) fVec7[i] = 0;
		fConst22 = floorf((0.5f + (0.013458f * fConst0)));
		iConst23 = int((int((fConst20 - fConst22)) & 8191));
		for (int i=0; i<1024; i++) fVec8[i] = 0;
		iConst24 = int((int((fConst22 - 1)) & 1023));
		for (int i=0; i<2; i++) fRec23[i] = 0;
		fConst25 = floorf((0.5f + (0.210389f * fConst0)));
		fConst26 = ((0 - (6.9077554f * fConst25)) / fConst0);
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<16384; i++) fVec9[i] = 0;
		fConst27 = floorf((0.5f + (0.024421f * fConst0)));
		iConst28 = int((int((fConst25 - fConst27)) & 16383));
		for (int i=0; i<2048; i++) fVec10[i] = 0;
		iConst29 = int((int((fConst27 - 1)) & 2047));
		for (int i=0; i<2; i++) fRec27[i] = 0;
		fConst30 = floorf((0.5f + (0.192303f * fConst0)));
		fConst31 = ((0 - (6.9077554f * fConst30)) / fConst0);
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<8192; i++) fVec11[i] = 0;
		fConst32 = floorf((0.5f + (0.029291f * fConst0)));
		iConst33 = int((int((fConst30 - fConst32)) & 8191));
		for (int i=0; i<2048; i++) fVec12[i] = 0;
		iConst34 = int((int((fConst32 - 1)) & 2047));
		for (int i=0; i<2; i++) fRec31[i] = 0;
		fConst35 = floorf((0.5f + (0.256891f * fConst0)));
		fConst36 = ((0 - (6.9077554f * fConst35)) / fConst0);
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<16384; i++) fVec13[i] = 0;
		fConst37 = floorf((0.5f + (0.027333f * fConst0)));
		iConst38 = int((int((fConst35 - fConst37)) & 16383));
		for (int i=0; i<2048; i++) fVec14[i] = 0;
		iConst39 = int((int((fConst37 - 1)) & 2047));
		for (int i=0; i<2; i++) fRec35[i] = 0;
		fConst40 = floorf((0.5f + (0.219991f * fConst0)));
		fConst41 = ((0 - (6.9077554f * fConst40)) / fConst0);
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<2; i++) fRec41[i] = 0;
		for (int i=0; i<16384; i++) fVec15[i] = 0;
		fConst42 = floorf((0.5f + (0.019123f * fConst0)));
		iConst43 = int((int((fConst40 - fConst42)) & 16383));
		for (int i=0; i<1024; i++) fVec16[i] = 0;
		iConst44 = int((int((fConst42 - 1)) & 1023));
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<3; i++) fRec3[i] = 0;
		for (int i=0; i<3; i++) fRec4[i] = 0;
		for (int i=0; i<3; i++) fRec5[i] = 0;
		for (int i=0; i<3; i++) fRec6[i] = 0;
		for (int i=0; i<3; i++) fRec7[i] = 0;
		for (int i=0; i<3; i++) fRec8[i] = 0;
		for (int i=0; i<3; i++) fRec9[i] = 0;
		for (int i=0; i<3; i++) fRec10[i] = 0;
		for (int i=0; i<3; i++) fRec2[i] = 0;
		fslider9 = 1.5e+03f;
		fslider10 = 0.0f;
		for (int i=0; i<3; i++) fRec43[i] = 0;
		for (int i=0; i<3; i++) fRec44[i] = 0;
		for (int i=0; i<3; i++) fRec45[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual dsp* clone() {
		return new FaustReverb();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* interface) {
		interface->declare(0, "0", "");
		interface->declare(0, "tooltip", "~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER      ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverb.lib for documentation and      references");
		interface->openHorizontalBox("Zita_Rev1");
		interface->declare(0, "1", "");
		interface->openHorizontalBox("Input");
		interface->declare(&fslider4, "1", "");
		interface->declare(&fslider4, "style", "knob");
		interface->declare(&fslider4, "tooltip", "Delay in ms   before reverberation begins");
		interface->declare(&fslider4, "unit", "ms");
		interface->addVerticalSlider("In Delay", &fslider4, 6e+01f, 2e+01f, 1e+02f, 1.0f);
		interface->closeBox();
		interface->declare(0, "2", "");
		interface->openHorizontalBox("Decay Times in Bands (see tooltips)");
		interface->declare(&fslider8, "1", "");
		interface->declare(&fslider8, "scale", "log");
		interface->declare(&fslider8, "style", "knob");
		interface->declare(&fslider8, "tooltip", "Crossover frequency (Hz) separating low and middle frequencies");
		interface->declare(&fslider8, "unit", "Hz");
		interface->addVerticalSlider("LF X", &fslider8, 2e+02f, 5e+01f, 1e+03f, 1.0f);
		interface->declare(&fslider7, "2", "");
		interface->declare(&fslider7, "scale", "log");
		interface->declare(&fslider7, "style", "knob");
		interface->declare(&fslider7, "tooltip", "T60 = time (in seconds) to decay 60dB in low-frequency band");
		interface->declare(&fslider7, "unit", "s");
		interface->addVerticalSlider("Low RT60", &fslider7, 3.0f, 1.0f, 8.0f, 0.1f);
		interface->declare(&fslider6, "3", "");
		interface->declare(&fslider6, "scale", "log");
		interface->declare(&fslider6, "style", "knob");
		interface->declare(&fslider6, "tooltip", "T60 = time (in seconds) to decay 60dB in middle band");
		interface->declare(&fslider6, "unit", "s");
		interface->addVerticalSlider("Mid RT60", &fslider6, 2.0f, 1.0f, 8.0f, 0.1f);
		interface->declare(&fslider5, "4", "");
		interface->declare(&fslider5, "scale", "log");
		interface->declare(&fslider5, "style", "knob");
		interface->declare(&fslider5, "tooltip", "Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60");
		interface->declare(&fslider5, "unit", "Hz");
		interface->addVerticalSlider("HF Damping", &fslider5, 6e+03f, 1.5e+03f, 2.352e+04f, 1.0f);
		interface->closeBox();
		interface->declare(0, "3", "");
		interface->openHorizontalBox("RM Peaking Equalizer 1");
		interface->declare(&fslider2, "1", "");
		interface->declare(&fslider2, "scale", "log");
		interface->declare(&fslider2, "style", "knob");
		interface->declare(&fslider2, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 1");
		interface->declare(&fslider2, "unit", "Hz");
		interface->addVerticalSlider("Eq1 Freq", &fslider2, 315.0f, 4e+01f, 2.5e+03f, 1.0f);
		interface->declare(&fslider3, "2", "");
		interface->declare(&fslider3, "style", "knob");
		interface->declare(&fslider3, "tooltip", "Peak level   in dB of second-order Regalia-Mitra peaking equalizer section 1");
		interface->declare(&fslider3, "unit", "dB");
		interface->addVerticalSlider("Eq1 Level", &fslider3, 0.0f, -15.0f, 15.0f, 0.1f);
		interface->closeBox();
		interface->declare(0, "4", "");
		interface->openHorizontalBox("RM Peaking Equalizer 2");
		interface->declare(&fslider9, "1", "");
		interface->declare(&fslider9, "scale", "log");
		interface->declare(&fslider9, "style", "knob");
		interface->declare(&fslider9, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 2");
		interface->declare(&fslider9, "unit", "Hz");
		interface->addVerticalSlider("Eq2 Freq", &fslider9, 1.5e+03f, 1.6e+02f, 1e+04f, 1.0f);
		interface->declare(&fslider10, "2", "");
		interface->declare(&fslider10, "style", "knob");
		interface->declare(&fslider10, "tooltip", "Peak level   in dB of second-order Regalia-Mitra peaking equalizer section 2");
		interface->declare(&fslider10, "unit", "dB");
		interface->addVerticalSlider("Eq2 Level", &fslider10, 0.0f, -15.0f, 15.0f, 0.1f);
		interface->closeBox();
		interface->declare(0, "5", "");
		interface->openHorizontalBox("Output");
		interface->declare(&fslider1, "1", "");
		interface->declare(&fslider1, "style", "knob");
		interface->declare(&fslider1, "tooltip", "-1 = dry, 1 = wet");
		interface->addVerticalSlider("Dry/Wet Mix", &fslider1, 0.0f, -1.0f, 1.0f, 0.01f);
		interface->declare(&fslider0, "2", "");
		interface->declare(&fslider0, "style", "knob");
		interface->declare(&fslider0, "tooltip", "Output scale   factor");
		interface->declare(&fslider0, "unit", "dB");
		interface->addVerticalSlider("Level", &fslider0, -2e+01f, -7e+01f, 4e+01f, 0.1f);
		interface->closeBox();
		interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = (0.001f * powf(10,(0.05f * float(fslider0))));
		float 	fSlow1 = (0.001f * float(fslider1));
		float 	fSlow2 = float(fslider2);
		float 	fSlow3 = powf(10,(0.05f * float(fslider3)));
		float 	fSlow4 = (fConst1 * (fSlow2 / sqrtf(max((float)0, fSlow3))));
		float 	fSlow5 = ((1.0f - fSlow4) / (1.0f + fSlow4));
		float 	fSlow6 = ((0 - cosf((fConst1 * fSlow2))) * (1 + fSlow5));
		int 	iSlow7 = int((int((fConst2 * float(fslider4))) & 8191));
		float 	fSlow8 = cosf((fConst3 * float(fslider5)));
		float 	fSlow9 = float(fslider6);
		float 	fSlow10 = expf((fConst5 / fSlow9));
		float 	fSlow11 = faustpower<2>(fSlow10);
		float 	fSlow12 = (1.0f - (fSlow8 * fSlow11));
		float 	fSlow13 = (1.0f - fSlow11);
		float 	fSlow14 = (fSlow12 / fSlow13);
		float 	fSlow15 = sqrtf(max((float)0, ((faustpower<2>(fSlow12) / faustpower<2>(fSlow13)) - 1.0f)));
		float 	fSlow16 = (fSlow14 - fSlow15);
		float 	fSlow17 = (fSlow10 * ((1.0f + fSlow15) - fSlow14));
		float 	fSlow18 = float(fslider7);
		float 	fSlow19 = ((expf((fConst5 / fSlow18)) / fSlow10) - 1);
		float 	fSlow20 = (1.0f / tanf((fConst6 * float(fslider8))));
		float 	fSlow21 = (1 + fSlow20);
		float 	fSlow22 = (1.0f / fSlow21);
		float 	fSlow23 = (0 - ((1 - fSlow20) / fSlow21));
		float 	fSlow24 = expf((fConst11 / fSlow9));
		float 	fSlow25 = faustpower<2>(fSlow24);
		float 	fSlow26 = (1.0f - (fSlow8 * fSlow25));
		float 	fSlow27 = (1.0f - fSlow25);
		float 	fSlow28 = (fSlow26 / fSlow27);
		float 	fSlow29 = sqrtf(max((float)0, ((faustpower<2>(fSlow26) / faustpower<2>(fSlow27)) - 1.0f)));
		float 	fSlow30 = (fSlow28 - fSlow29);
		float 	fSlow31 = (fSlow24 * ((1.0f + fSlow29) - fSlow28));
		float 	fSlow32 = ((expf((fConst11 / fSlow18)) / fSlow24) - 1);
		float 	fSlow33 = expf((fConst16 / fSlow9));
		float 	fSlow34 = faustpower<2>(fSlow33);
		float 	fSlow35 = (1.0f - (fSlow8 * fSlow34));
		float 	fSlow36 = (1.0f - fSlow34);
		float 	fSlow37 = (fSlow35 / fSlow36);
		float 	fSlow38 = sqrtf(max((float)0, ((faustpower<2>(fSlow35) / faustpower<2>(fSlow36)) - 1.0f)));
		float 	fSlow39 = (fSlow37 - fSlow38);
		float 	fSlow40 = (fSlow33 * ((1.0f + fSlow38) - fSlow37));
		float 	fSlow41 = ((expf((fConst16 / fSlow18)) / fSlow33) - 1);
		float 	fSlow42 = expf((fConst21 / fSlow9));
		float 	fSlow43 = faustpower<2>(fSlow42);
		float 	fSlow44 = (1.0f - (fSlow8 * fSlow43));
		float 	fSlow45 = (1.0f - fSlow43);
		float 	fSlow46 = (fSlow44 / fSlow45);
		float 	fSlow47 = sqrtf(max((float)0, ((faustpower<2>(fSlow44) / faustpower<2>(fSlow45)) - 1.0f)));
		float 	fSlow48 = (fSlow46 - fSlow47);
		float 	fSlow49 = (fSlow42 * ((1.0f + fSlow47) - fSlow46));
		float 	fSlow50 = ((expf((fConst21 / fSlow18)) / fSlow42) - 1);
		float 	fSlow51 = expf((fConst26 / fSlow9));
		float 	fSlow52 = faustpower<2>(fSlow51);
		float 	fSlow53 = (1.0f - (fSlow8 * fSlow52));
		float 	fSlow54 = (1.0f - fSlow52);
		float 	fSlow55 = (fSlow53 / fSlow54);
		float 	fSlow56 = sqrtf(max((float)0, ((faustpower<2>(fSlow53) / faustpower<2>(fSlow54)) - 1.0f)));
		float 	fSlow57 = (fSlow55 - fSlow56);
		float 	fSlow58 = (fSlow51 * ((1.0f + fSlow56) - fSlow55));
		float 	fSlow59 = ((expf((fConst26 / fSlow18)) / fSlow51) - 1);
		float 	fSlow60 = expf((fConst31 / fSlow9));
		float 	fSlow61 = faustpower<2>(fSlow60);
		float 	fSlow62 = (1.0f - (fSlow8 * fSlow61));
		float 	fSlow63 = (1.0f - fSlow61);
		float 	fSlow64 = (fSlow62 / fSlow63);
		float 	fSlow65 = sqrtf(max((float)0, ((faustpower<2>(fSlow62) / faustpower<2>(fSlow63)) - 1.0f)));
		float 	fSlow66 = (fSlow64 - fSlow65);
		float 	fSlow67 = (fSlow60 * ((1.0f + fSlow65) - fSlow64));
		float 	fSlow68 = ((expf((fConst31 / fSlow18)) / fSlow60) - 1);
		float 	fSlow69 = expf((fConst36 / fSlow9));
		float 	fSlow70 = faustpower<2>(fSlow69);
		float 	fSlow71 = (1.0f - (fSlow8 * fSlow70));
		float 	fSlow72 = (1.0f - fSlow70);
		float 	fSlow73 = (fSlow71 / fSlow72);
		float 	fSlow74 = sqrtf(max((float)0, ((faustpower<2>(fSlow71) / faustpower<2>(fSlow72)) - 1.0f)));
		float 	fSlow75 = (fSlow73 - fSlow74);
		float 	fSlow76 = (fSlow69 * ((1.0f + fSlow74) - fSlow73));
		float 	fSlow77 = ((expf((fConst36 / fSlow18)) / fSlow69) - 1);
		float 	fSlow78 = expf((fConst41 / fSlow9));
		float 	fSlow79 = faustpower<2>(fSlow78);
		float 	fSlow80 = (1.0f - (fSlow79 * fSlow8));
		float 	fSlow81 = (1.0f - fSlow79);
		float 	fSlow82 = (fSlow80 / fSlow81);
		float 	fSlow83 = sqrtf(max((float)0, ((faustpower<2>(fSlow80) / faustpower<2>(fSlow81)) - 1.0f)));
		float 	fSlow84 = (fSlow82 - fSlow83);
		float 	fSlow85 = (fSlow78 * ((1.0f + fSlow83) - fSlow82));
		float 	fSlow86 = ((expf((fConst41 / fSlow18)) / fSlow78) - 1);
		float 	fSlow87 = float(fslider9);
		float 	fSlow88 = powf(10,(0.05f * float(fslider10)));
		float 	fSlow89 = (fConst1 * (fSlow87 / sqrtf(max((float)0, fSlow88))));
		float 	fSlow90 = ((1.0f - fSlow89) / (1.0f + fSlow89));
		float 	fSlow91 = ((0 - cosf((fConst1 * fSlow87))) * (1 + fSlow90));
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		for (int i=0; i<count; i++) {
			fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
			float fTemp0 = (float)input0[i];
			fVec0[IOTA&8191] = fTemp0;
			fRec1[0] = (fSlow1 + (0.999f * fRec1[1]));
			float fTemp1 = (1.0f + fRec1[0]);
			float fTemp2 = (fVec0[IOTA&8191] * fTemp1);
			float fTemp3 = (1.0f - (0.5f * fTemp1));
			float fTemp4 = (fSlow6 * fRec2[1]);
			float fTemp5 = (0.3f * fVec0[(IOTA-iSlow7)&8191]);
			fRec14[0] = ((fSlow22 * (fRec3[1] + fRec3[2])) + (fSlow23 * fRec14[1]));
			fRec13[0] = ((fSlow16 * fRec13[1]) + (fSlow17 * (fRec3[1] + (fSlow19 * fRec14[0]))));
			fVec1[IOTA&8191] = (1e-20f + (0.35355338f * fRec13[0]));
			float fTemp6 = ((fTemp5 + fVec1[(IOTA-iConst8)&8191]) - (0.6f * fRec11[1]));
			fVec2[IOTA&1023] = fTemp6;
			fRec11[0] = fVec2[(IOTA-iConst9)&1023];
			float 	fRec12 = (0.6f * fVec2[IOTA&1023]);
			fRec18[0] = ((fSlow22 * (fRec7[1] + fRec7[2])) + (fSlow23 * fRec18[1]));
			fRec17[0] = ((fSlow30 * fRec17[1]) + (fSlow31 * (fRec7[1] + (fSlow32 * fRec18[0]))));
			fVec3[IOTA&8191] = (1e-20f + (0.35355338f * fRec17[0]));
			float fTemp7 = ((fTemp5 + fVec3[(IOTA-iConst13)&8191]) - (0.6f * fRec15[1]));
			fVec4[IOTA&2047] = fTemp7;
			fRec15[0] = fVec4[(IOTA-iConst14)&2047];
			float 	fRec16 = (0.6f * fVec4[IOTA&2047]);
			fRec22[0] = ((fSlow22 * (fRec5[1] + fRec5[2])) + (fSlow23 * fRec22[1]));
			fRec21[0] = ((fSlow39 * fRec21[1]) + (fSlow40 * (fRec5[1] + (fSlow41 * fRec22[0]))));
			fVec5[IOTA&8191] = (1e-20f + (0.35355338f * fRec21[0]));
			float fTemp8 = (fVec5[(IOTA-iConst18)&8191] - (fTemp5 + (0.6f * fRec19[1])));
			fVec6[IOTA&2047] = fTemp8;
			fRec19[0] = fVec6[(IOTA-iConst19)&2047];
			float 	fRec20 = (0.6f * fVec6[IOTA&2047]);
			fRec26[0] = ((fSlow22 * (fRec9[1] + fRec9[2])) + (fSlow23 * fRec26[1]));
			fRec25[0] = ((fSlow48 * fRec25[1]) + (fSlow49 * (fRec9[1] + (fSlow50 * fRec26[0]))));
			fVec7[IOTA&8191] = (1e-20f + (0.35355338f * fRec25[0]));
			float fTemp9 = (fVec7[(IOTA-iConst23)&8191] - (fTemp5 + (0.6f * fRec23[1])));
			fVec8[IOTA&1023] = fTemp9;
			fRec23[0] = fVec8[(IOTA-iConst24)&1023];
			float 	fRec24 = (0.6f * fVec8[IOTA&1023]);
			fRec30[0] = ((fSlow22 * (fRec4[1] + fRec4[2])) + (fSlow23 * fRec30[1]));
			fRec29[0] = ((fSlow57 * fRec29[1]) + (fSlow58 * (fRec4[1] + (fSlow59 * fRec30[0]))));
			fVec9[IOTA&16383] = (1e-20f + (0.35355338f * fRec29[0]));
			float fTemp10 = (fVec9[(IOTA-iConst28)&16383] + (fTemp5 + (0.6f * fRec27[1])));
			fVec10[IOTA&2047] = fTemp10;
			fRec27[0] = fVec10[(IOTA-iConst29)&2047];
			float 	fRec28 = (0 - (0.6f * fVec10[IOTA&2047]));
			fRec34[0] = ((fSlow22 * (fRec8[1] + fRec8[2])) + (fSlow23 * fRec34[1]));
			fRec33[0] = ((fSlow66 * fRec33[1]) + (fSlow67 * (fRec8[1] + (fSlow68 * fRec34[0]))));
			fVec11[IOTA&8191] = (1e-20f + (0.35355338f * fRec33[0]));
			float fTemp11 = (fVec11[(IOTA-iConst33)&8191] + (fTemp5 + (0.6f * fRec31[1])));
			fVec12[IOTA&2047] = fTemp11;
			fRec31[0] = fVec12[(IOTA-iConst34)&2047];
			float 	fRec32 = (0 - (0.6f * fVec12[IOTA&2047]));
			fRec38[0] = ((fSlow22 * (fRec6[1] + fRec6[2])) + (fSlow23 * fRec38[1]));
			fRec37[0] = ((fSlow75 * fRec37[1]) + (fSlow76 * (fRec6[1] + (fSlow77 * fRec38[0]))));
			fVec13[IOTA&16383] = (1e-20f + (0.35355338f * fRec37[0]));
			float fTemp12 = (((0.6f * fRec35[1]) + fVec13[(IOTA-iConst38)&16383]) - fTemp5);
			fVec14[IOTA&2047] = fTemp12;
			fRec35[0] = fVec14[(IOTA-iConst39)&2047];
			float 	fRec36 = (0 - (0.6f * fVec14[IOTA&2047]));
			fRec42[0] = ((fSlow22 * (fRec10[1] + fRec10[2])) + (fSlow23 * fRec42[1]));
			fRec41[0] = ((fSlow84 * fRec41[1]) + (fSlow85 * (fRec10[1] + (fSlow86 * fRec42[0]))));
			fVec15[IOTA&16383] = (1e-20f + (0.35355338f * fRec41[0]));
			float fTemp13 = (((0.6f * fRec39[1]) + fVec15[(IOTA-iConst43)&16383]) - fTemp5);
			fVec16[IOTA&1023] = fTemp13;
			fRec39[0] = fVec16[(IOTA-iConst44)&1023];
			float 	fRec40 = (0 - (0.6f * fVec16[IOTA&1023]));
			float fTemp14 = (fRec39[1] + fRec40);
			float fTemp15 = (fRec36 + (fRec35[1] + fTemp14));
			float fTemp16 = (fRec28 + (fRec27[1] + (fRec32 + (fRec31[1] + fTemp15))));
			fRec3[0] = (fRec12 + (fRec11[1] + (fRec16 + (fRec15[1] + (fRec20 + (fRec19[1] + (fRec24 + (fRec23[1] + fTemp16))))))));
			fRec4[0] = (0 - (fTemp16 - (fRec12 + (fRec11[1] + (fRec16 + (fRec15[1] + (fRec20 + (fRec19[1] + (fRec23[1] + fRec24)))))))));
			float fTemp17 = (fRec28 + (fRec27[1] + (fRec31[1] + fRec32)));
			fRec5[0] = (0 - ((fRec20 + (fRec19[1] + (fRec24 + (fRec23[1] + fTemp15)))) - (fRec12 + (fRec11[1] + (fRec16 + (fRec15[1] + fTemp17))))));
			fRec6[0] = (0 - ((fRec20 + (fRec19[1] + (fRec24 + (fRec23[1] + fTemp17)))) - (fRec12 + (fRec11[1] + (fRec16 + (fRec15[1] + fTemp15))))));
			float fTemp18 = (fRec32 + (fRec31[1] + fTemp14));
			float fTemp19 = (fRec35[1] + fRec36);
			float fTemp20 = (fRec28 + (fRec27[1] + fTemp19));
			fRec7[0] = (0 - ((fRec16 + (fRec15[1] + (fRec24 + (fRec23[1] + fTemp18)))) - (fRec12 + (fRec11[1] + (fRec20 + (fRec19[1] + fTemp20))))));
			fRec8[0] = (0 - ((fRec16 + (fRec15[1] + (fRec24 + (fRec23[1] + fTemp20)))) - (fRec12 + (fRec11[1] + (fRec20 + (fRec19[1] + fTemp18))))));
			float fTemp21 = (fRec32 + (fRec31[1] + fTemp19));
			float fTemp22 = (fRec28 + (fRec27[1] + fTemp14));
			fRec9[0] = (0 - ((fRec16 + (fRec15[1] + (fRec20 + (fRec19[1] + fTemp21)))) - (fRec12 + (fRec11[1] + (fRec24 + (fRec23[1] + fTemp22))))));
			fRec10[0] = (0 - ((fRec16 + (fRec15[1] + (fRec20 + (fRec19[1] + fTemp22)))) - (fRec12 + (fRec11[1] + (fRec24 + (fRec23[1] + fTemp21))))));
			float fTemp23 = (0.37f * (fRec4[0] + fRec5[0]));
			fRec2[0] = (0 - ((fTemp4 + (fSlow5 * fRec2[2])) - fTemp23));
			float fTemp24 = (fSlow5 * fRec2[0]);
			float fTemp25 = (fTemp4 + fRec2[2]);
			float fTemp26 = (0.5f * ((fTemp24 + (fTemp23 + fTemp25)) + (fSlow3 * ((fTemp24 + fTemp25) - fTemp23))));
			float fTemp27 = (fSlow91 * fRec43[1]);
			fRec43[0] = (0 - ((fTemp27 + (fSlow90 * fRec43[2])) - fTemp26));
			float fTemp28 = ((fSlow90 * fRec43[0]) + (fTemp27 + fRec43[2]));
			output0[i] = (FAUSTFLOAT)(0.5f * (fRec0[0] * (fTemp2 + (fTemp3 * ((fTemp26 + fTemp28) + (fSlow88 * (fTemp28 - fTemp26)))))));
			float fTemp29 = (fSlow6 * fRec44[1]);
			float fTemp30 = (0.37f * (fRec4[0] - fRec5[0]));
			fRec44[0] = (0 - ((fTemp29 + (fSlow5 * fRec44[2])) - fTemp30));
			float fTemp31 = (fSlow5 * fRec44[0]);
			float fTemp32 = (fTemp29 + fRec44[2]);
			float fTemp33 = (0.5f * ((fTemp31 + (fTemp30 + fTemp32)) + (fSlow3 * ((fTemp31 + fTemp32) - fTemp30))));
			float fTemp34 = (fSlow91 * fRec45[1]);
			fRec45[0] = (0 - ((fTemp34 + (fSlow90 * fRec45[2])) - fTemp33));
			float fTemp35 = ((fSlow90 * fRec45[0]) + (fTemp34 + fRec45[2]));
			output1[i] = (FAUSTFLOAT)(0.5f * (fRec0[0] * (fTemp2 + (fTemp3 * ((fTemp33 + fTemp35) + (fSlow88 * (fTemp35 - fTemp33)))))));
			// post processing
			fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
			fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
			fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
			fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
			fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
			fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
			fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
			fRec39[1] = fRec39[0];
			fRec41[1] = fRec41[0];
			fRec42[1] = fRec42[0];
			fRec35[1] = fRec35[0];
			fRec37[1] = fRec37[0];
			fRec38[1] = fRec38[0];
			fRec31[1] = fRec31[0];
			fRec33[1] = fRec33[0];
			fRec34[1] = fRec34[0];
			fRec27[1] = fRec27[0];
			fRec29[1] = fRec29[0];
			fRec30[1] = fRec30[0];
			fRec23[1] = fRec23[0];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			fRec19[1] = fRec19[0];
			fRec21[1] = fRec21[0];
			fRec22[1] = fRec22[0];
			fRec15[1] = fRec15[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fRec11[1] = fRec11[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fRec1[1] = fRec1[0];
			IOTA = IOTA+1;
			fRec0[1] = fRec0[0];
		}
	}
};


