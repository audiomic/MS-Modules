#include "MS_modules.hpp"
#include "dsp/digital.hpp"

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
		NUM_OUTPUTS
	};
		
		SchmittTrigger trigger;
		float sample = 0.0;
		float SH_Light = {};
				
		RandomSource() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {
			trigger.setThresholds(0.0,0.7);
		}
		void step();
};

void RandomSource::step() {
	
	//sample and hold
	float range = params[RANGE_PARAM].value;
 		
	if (trigger.process(inputs[TRIG_INPUT].value)) {
		sample = inputs[SH_INPUT].normalize(range);
	}
	
	float SHOut = sample * params[RANGE_PARAM].value;
	
	//light
	SH_Light = sample;
		
	//Output
	outputs[SH_OUTPUT].value = SHOut;

};

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
				
		//Inputs
		addInput(createInput<SilverSixPort>(Vec(29, 237), module, RandomSource::SH_INPUT));
		addInput(createInput<SilverSixPort>(Vec(29, 283), module, RandomSource::TRIG_INPUT));
		
		//Outputs
		addOutput(createOutput<SilverSixPort>(Vec(29, 328), module, RandomSource::SH_OUTPUT));
		
		//Light
		addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(26, 156), &module->SH_Light));
		
};
