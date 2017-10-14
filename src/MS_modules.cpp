#include "MS_modules.hpp"

Plugin *plugin;


void init(rack::Plugin *p) {
	plugin = p;		
	plugin->slug = "MS-Modules";
	plugin->name = "MS-Modules";
	plugin->homepageUrl = "https://github.com/Phal-anx/MS-Modules";
	createModel<RandomSourceWidget>(plugin, "Random Source", "Random Source");
	createModel<MultWidget>(plugin, "Mult", "Mult");
	
}
