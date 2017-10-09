#include "MS_modules.hpp"
#include "GreenBlueKnob.cpp"


#define DTRIG 7000.0


struct RandomSource : Module {
		enum ParamIds {
			RANGE_PARAM,
			CV_PARAM,
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
		float lights[1] = {};
				
		RandomSource();
		void step();
};


RandomSource::RandomSource() {
	params.resize(NUM_PARAMS);
	inputs.resize(NUM_INPUTS);
	outputs.resize(NUM_OUTPUTS);
}

	
void RandomSource::step() {
	
	//sample and hold
	float range_knob = params[RANGE_PARAM] * 24.0;
   	float range_cv = getf(inputs[CV_INPUT]) * 12.0;
	float range_amt = params[CV_PARAM];
	float range = range_knob + range_amt * range_cv;
	float clock = getf(inputs[TRIG_INPUT]) ;
	float dtrig = (clock - lastTrig) * gSampleRate;
	if (dtrig > DTRIG) {
		sample = getf(inputs[SH_INPUT]) + range; // + CV;
	}
	lastTrig = clock;
	
	//light
	lights[1] = sample;
	
	float SHOut = sample * params[RANGE_PARAM] / 10.0;
	
	//Output
	setf(outputs[SH_OUTPUT], SHOut); //sample and hold
		

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
		
		//Screw
		addChild(createScrew<ScrewSilver>(Vec(15, 0)));
		addChild(createScrew<ScrewSilver>(Vec(15, 365)));
		
		//Param
		addParam(createParam<GreenBlueLargeKnob>(Vec(7, 90), module, RandomSource::RANGE_PARAM, 0.0, 1.0, 0.0));
		addParam(createParam<GreenBlueSmallKnob>(Vec(5, 146), module, RandomSource::CV_PARAM, 0.0, 1.0, 0.0));
		//Inputs
		addInput(createInput<PJ3410Port>(Vec(25, 189), module, RandomSource::CV_INPUT));
		addInput(createInput<PJ3410Port>(Vec(25, 233), module, RandomSource::SH_INPUT));
		addInput(createInput<PJ3410Port>(Vec(25, 279), module, RandomSource::TRIG_INPUT));
		
		//Outputs
		addOutput(createOutput<PJ3410Port>(Vec(25, 324), module, RandomSource::SH_OUTPUT));
		
		//Light
		addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(48, 156), &module->lights[1]));
		
}

