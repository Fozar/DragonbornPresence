#include "DragonbornPresence.h"

namespace MyPluginNamespace {
	float MyTest(StaticFunctionTag *base) {
		_MESSAGE("MyTest() will return %f", 3.3);
		return 3.3;
	}

	bool RegisterFuncs(VMClassRegistry* registry) {
		registry->RegisterFunction(
			new NativeFunction0 <StaticFunctionTag, float>("MyTest", "MyPluginScript", MyPluginNamespace::MyTest, registry));

		return true;
	}
}
