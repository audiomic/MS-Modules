#include "MS_modules.hpp"

#define DTRIG 7000.0

struct RandomSource : Module {
		enum ParamIds {
			RANGE_PARAM,
			NUM_PARAMS
		};
		
		enum InputIds {
			TRIG_INPUT,
			SH_INPUT,
			NUM_INPUTS
		};
		
		enum OutputIds {
			SH_OUTPUT,
			NOISE_OUTPUT,
			NUM_OUTPUTS
		};
		
		float lastTrig = 0.0;
		float sample = 0.0;
				
		RandomSource();
		void step();
};


RandomSource::RandomSource() {
	params.resize(NUM_PARAMS);
	inputs.resize(NUM_INPUTS);
	outputs.resize(NUM_OUTPUTS);
}


void RandomSource::step() {
	
	//Gaussian Noise Gen
	float noise = 2.0 * randomNormal(); 
	
	//add noise internally
	float range = noise * params[RANGE_PARAM] / 15;
		
	//SH
	float clock = getf(inputs[TRIG_INPUT]) + range;
	float dtrig = (clock - lastTrig) * gSampleRate;
	if (dtrig > DTRIG) {
		sample = getf(inputs[SH_INPUT]);
	}
	lastTrig = clock;
	
	
	
	//Output
	setf(outputs[SH_OUTPUT], sample); //S&H
	setf(outputs[NOISE_OUTPUT], noise); //Gaussian Noise
			

}

RandomSourceWidget::RandomSourceWidget() {
		RandomSource *module = new RandomSource();
		setModule(module);
		box.size = Vec(60, 380);
		
		{
			SVGPanel *panel = new SVGPanel();
			panel->box.size = box.size;
			panel->setBackground(SVG::load("plugins/MS_modules/res/Random Source.svg"));
			addChild(panel);
		}
		
		addChild(createScrew<ScrewSilver>(Vec(15, 0)));
		addChild(createScrew<ScrewSilver>(Vec(15, 365)));
			
		addParam(createParam<Davies1900hBlackKnob>(Vec(12, 100), module, RandomSource::RANGE_PARAM, 0.0, 1.0, 0.0));
		
		addInput(createInput<PJ3410Port>(Vec(15, 165), module, RandomSource::SH_INPUT));
		addInput(createInput<PJ3410Port>(Vec(15, 210), module, RandomSource::TRIG_INPUT));
		
		addOutput(createOutput<PJ3410Port>(Vec(15, 255), module, RandomSource::SH_OUTPUT));
		addOutput(createOutput<PJ3410Port>(Vec(15, 300), module, RandomSource::NOISE_OUTPUT));
		
}

