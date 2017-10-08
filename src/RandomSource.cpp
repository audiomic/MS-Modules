#include "MS_modules.hpp"
#include "GreenBlueSmall.cpp"


#define DTRIG 7000.0


struct RandomSource : Module {
		enum ParamIds {
			RANGE_PARAM,
			NUM_PARAMS
		};
		
		enum InputIds {
			TRIG_INPUT,
			CV_INPUT,
			SH_INPUT,
			NUM_INPUTS
		};
		
		enum OutputIds {
			SH_OUTPUT,
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
	
	//CV
	float range = getf(inputs[TRIG_INPUT]) * getf(inputs[CV_INPUT]) * params[RANGE_PARAM] / 15;
	
		
	//SH
	float clock = getf(inputs[TRIG_INPUT]) + range;
	float dtrig = (clock - lastTrig) * gSampleRate;
	if (dtrig > DTRIG) {
		sample = getf(inputs[SH_INPUT]);
	}
	lastTrig = clock;
	
	
	float SHOut = sample * params[RANGE_PARAM] * getf(inputs[CV_INPUT], 10.0) / 10.0;
	
	//Output
	setf(outputs[SH_OUTPUT], SHOut); //S&H 
		

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
			
		addParam(createParam<GreenBlueSmallKnob>(Vec(7, 100), module, RandomSource::RANGE_PARAM, 0.0, 1.0, 0.0));

		addInput(createInput<PJ3410Port>(Vec(15, 165), module, RandomSource::CV_INPUT));
		addInput(createInput<PJ3410Port>(Vec(15, 210), module, RandomSource::SH_INPUT));
		addInput(createInput<PJ3410Port>(Vec(15, 255), module, RandomSource::TRIG_INPUT));
		
		addOutput(createOutput<PJ3410Port>(Vec(15, 300), module, RandomSource::SH_OUTPUT));
				
}

