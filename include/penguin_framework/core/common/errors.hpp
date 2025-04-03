#pragma once

namespace pf {

	namespace common {

		enum class PF_Error {
			Unknown = -1,
			Window,
			Renderer,
			Init,
			Input,
			Text,
			Runtime
		};
	}
}
