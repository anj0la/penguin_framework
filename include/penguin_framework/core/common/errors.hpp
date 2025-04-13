#pragma once

namespace pf::core::common {

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
