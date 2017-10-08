#include "MS_modules.hpp"

Plugin *plugin;

struct MS_modulesPlugin : Plugin {
	MS_modulesPlugin() {
		slug = "MS-Modules";
		name = "MS-Modules";
		createModel<RandomSourceWidget>(this, "Random Source", "Random Source");
	}
};


Plugin *init() {
	return new MS_modulesPlugin();
}
