#include "MS_modules.hpp"


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
		
		SchmittTrigger trigger;
		float sample = 0.0;
		float lights[1] = {};
				
		RandomSource() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {
			trigger.setThresholds(0.0,0.7);
		}
		void step();
};

void RandomSource::step() {
	
	//sample and hold
	float range_knob = params[RANGE_PARAM].value * 6.0;
    float range_cv = inputs[CV_INPUT].value * 24.0 / 12.0; 
    float range_cv_amt = params[CV_PARAM].value;
    float range = range_knob + range_cv_amt * range_cv;
		
	if (trigger.process(inputs[TRIG_INPUT].value)) {
		sample = inputs[SH_INPUT].normalize(range);
			
	float SHOut = sample * params[RANGE_PARAM].value / 1.5;
	
	//light
	lights[1] = sample;
		
	//Output
	outputs[SH_OUTPUT].value = SHOut;
		
	}
}

RandomSourceWidget::RandomSourceWidget() {
		RandomSource *module = new RandomSource();
		setModule(module);
		box.size = Vec(60, 380);
				
		{
			SVGPanel *panel = new SVGPanel();
			panel->box.size = box.size;
			panel->setBackground(SVG::load(assetPlugin(plugin, "/res/Random Source.svg")));
			addChild(panel);
		}
		
		//Screw
		addChild(createScrew<ScrewSilver>(Vec(15, 0)));
		addChild(createScrew<ScrewSilver>(Vec(15, 365)));
		
		//Param
		addParam(createParam<GreyLargeKnob>(Vec(7, 90), module, RandomSource::RANGE_PARAM, 0.0, 1.0, 0.0));
		addParam(createParam<GreySmallKnob>(Vec(5, 146), module, RandomSource::CV_PARAM, 0.0, 1.0, 0.0));
		//Inputs
		addInput(createInput<SilverSixPort>(Vec(29, 192), module, RandomSource::CV_INPUT));
		addInput(createInput<SilverSixPort>(Vec(29, 237), module, RandomSource::SH_INPUT));
		addInput(createInput<SilverSixPort>(Vec(29, 283), module, RandomSource::TRIG_INPUT));
		
		//Outputs
		addOutput(createOutput<SilverSixPort>(Vec(29, 328), module, RandomSource::SH_OUTPUT));
		
		//Light
		addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(44, 156), &module->lights[1]));
		
};
