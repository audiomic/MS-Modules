#include "MS_Modules.hpp"

struct Mult : Module 
{
		enum ParamIds {
			MODE1_PARAM,
			MODE2_PARAM,
			MODE3_PARAM,
			NUM_PARAMS
		};
		
		enum InputIds {
			IN_1_INPUT,
			IN_2_INPUT,
			IN_3_INPUT,
			IN_4_INPUT,
			IN_5_INPUT,
			IN_6_INPUT,
			NUM_INPUTS
		};
		
		enum OutputIds {
			OUT_11_OUTPUT,
			OUT_12_OUTPUT,
			OUT_13_OUTPUT,
			OUT_14_OUTPUT,
			OUT_15_OUTPUT,
			OUT_16_OUTPUT,
			OUT_21_OUTPUT,
			OUT_22_OUTPUT,
			OUT_23_OUTPUT,
			OUT_24_OUTPUT,
			OUT_25_OUTPUT,
			OUT_26_OUTPUT,
			OUT_31_OUTPUT,
			OUT_32_OUTPUT,
			OUT_33_OUTPUT,
			OUT_34_OUTPUT,
			OUT_35_OUTPUT,
			OUT_36_OUTPUT,
			NUM_OUTPUTS
			
		};
		
		float lights[2] = {};
			
		Mult() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {}
		void step();
};
		
void Mult::step() {

	float IN_1, IN_2, IN_3;
	
	bool IN_1Mode = params[MODE1_PARAM].value > 0.0;
	bool IN_2Mode = params[MODE2_PARAM].value > 0.0;
	bool IN_3Mode = params[MODE3_PARAM].value > 0.0;
	
	if(IN_1Mode) {
	IN_1 = inputs[IN_1_INPUT].value + inputs[IN_2_INPUT].value;
	}
	else {
	IN_1 = inputs[IN_1_INPUT].value - inputs[IN_2_INPUT].value;
	}
	
	if(IN_2Mode) {
	IN_2 = inputs[IN_3_INPUT].value + inputs[IN_4_INPUT].value;
	}
	else {
	IN_2 = inputs[IN_3_INPUT].value - inputs[IN_4_INPUT].value;
	}
	if(IN_3Mode) {
	IN_3 = inputs[IN_5_INPUT].value + inputs[IN_6_INPUT].value;
	}
	else {
	IN_3 = inputs[IN_5_INPUT].value - inputs[IN_6_INPUT].value;
	}
	
	//Mult1	
	outputs[OUT_11_OUTPUT].value = IN_1;
	outputs[OUT_12_OUTPUT].value = IN_1;
	outputs[OUT_13_OUTPUT].value = IN_1;
	outputs[OUT_14_OUTPUT].value = IN_1;
	outputs[OUT_15_OUTPUT].value = IN_1;
	outputs[OUT_16_OUTPUT].value = IN_1;
	
	//Mult2	
	outputs[OUT_21_OUTPUT].value = IN_2;
	outputs[OUT_22_OUTPUT].value = IN_2;
	outputs[OUT_23_OUTPUT].value = IN_2;
	outputs[OUT_24_OUTPUT].value = IN_2;
	outputs[OUT_25_OUTPUT].value = IN_2;
	outputs[OUT_26_OUTPUT].value = IN_2;
	
	//Mult3	
	outputs[OUT_31_OUTPUT].value = IN_3;
	outputs[OUT_32_OUTPUT].value = IN_3;
	outputs[OUT_33_OUTPUT].value = IN_3;
	outputs[OUT_34_OUTPUT].value = IN_3;
	outputs[OUT_35_OUTPUT].value = IN_3;
	outputs[OUT_36_OUTPUT].value = IN_3;
	
	lights[0] = IN_1 / 5.0;
    lights[1] = IN_2 / 5.0;
	lights[2] = IN_3 / 5.0;
	
};

MultWidget::MultWidget()
{
    Mult *module = new Mult();
    setModule(module);
    box.size = Vec(135, 380);

    {
        SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "/res/Mult.svg")));
		addChild(panel);
    }

    addChild(createScrew<ScrewSilver>(Vec(15, 0)));
    addChild(createScrew<ScrewSilver>(Vec(box.size.x - 35, 0)));
    addChild(createScrew<ScrewSilver>(Vec(15, 365)));
    addChild(createScrew<ScrewSilver>(Vec(box.size.x - 35, 365)));

	addInput(createInput<SilverSixPort>(Vec(15, 30), module, Mult::IN_1_INPUT));
	addInput(createInput<SilverSixPort>(Vec(15, 60), module, Mult::IN_2_INPUT));
	addInput(createInput<SilverSixPort>(Vec(55, 30), module, Mult::IN_3_INPUT));
	addInput(createInput<SilverSixPort>(Vec(55, 60), module, Mult::IN_4_INPUT));
	addInput(createInput<SilverSixPort>(Vec(95, 30), module, Mult::IN_5_INPUT));
	addInput(createInput<SilverSixPort>(Vec(95, 60), module, Mult::IN_6_INPUT));
	
	addParam(createParam<CKSS>(Vec(20, 94), module, Mult::MODE1_PARAM, 0.0, 1.0, 1.0));
	addParam(createParam<CKSS>(Vec(60, 94), module, Mult::MODE2_PARAM, 0.0, 1.0, 1.0));
	addParam(createParam<CKSS>(Vec(100, 94), module, Mult::MODE3_PARAM, 0.0, 1.0, 1.0));
	
	addOutput(createOutput<SilverSixPort>(Vec(15, 120), module, Mult::OUT_11_OUTPUT));
	addOutput(createOutput<SilverSixPort>(Vec(15, 160), module, Mult::OUT_12_OUTPUT));
	addOutput(createOutput<SilverSixPort>(Vec(15, 200), module, Mult::OUT_13_OUTPUT));
	addOutput(createOutput<SilverSixPort>(Vec(15, 240), module, Mult::OUT_14_OUTPUT));
	addOutput(createOutput<SilverSixPort>(Vec(15, 280), module, Mult::OUT_15_OUTPUT));
	addOutput(createOutput<SilverSixPort>(Vec(15, 320), module, Mult::OUT_16_OUTPUT));

	addOutput(createOutput<SilverSixPort>(Vec(55, 120), module, Mult::OUT_21_OUTPUT));
	addOutput(createOutput<SilverSixPort>(Vec(55, 160), module, Mult::OUT_22_OUTPUT));
	addOutput(createOutput<SilverSixPort>(Vec(55, 200), module, Mult::OUT_23_OUTPUT));
	addOutput(createOutput<SilverSixPort>(Vec(55, 240), module, Mult::OUT_24_OUTPUT));
	addOutput(createOutput<SilverSixPort>(Vec(55, 280), module, Mult::OUT_25_OUTPUT));
	addOutput(createOutput<SilverSixPort>(Vec(55, 320), module, Mult::OUT_26_OUTPUT));
	
	addOutput(createOutput<SilverSixPort>(Vec(95, 120), module, Mult::OUT_31_OUTPUT));
	addOutput(createOutput<SilverSixPort>(Vec(95, 160), module, Mult::OUT_32_OUTPUT));
	addOutput(createOutput<SilverSixPort>(Vec(95, 200), module, Mult::OUT_33_OUTPUT));
	addOutput(createOutput<SilverSixPort>(Vec(95, 240), module, Mult::OUT_34_OUTPUT));
	addOutput(createOutput<SilverSixPort>(Vec(95, 280), module, Mult::OUT_35_OUTPUT));
	addOutput(createOutput<SilverSixPort>(Vec(95, 320), module, Mult::OUT_36_OUTPUT));
	
	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(23, 19), &module->lights[0]));
	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(63, 19), &module->lights[1]));
	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(103, 19), &module->lights[2]));
	
	
};	