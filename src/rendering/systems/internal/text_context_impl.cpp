#include <rendering/systems/internal/text_context_impl.hpp>

namespace penguin::internal::rendering::systems {

	TextContextImpl::TextContextImpl(NativeRendererPtr renderer) : context(TTF_CreateRendererTextEngine(renderer.as<SDL_Renderer>()), &TTF_DestroyRendererTextEngine) {
		penguin::internal::error::InternalError::throw_if(
			!context,
			"Failed to create the text context.",
			penguin::internal::error::ErrorCode::Text_Context_Init_Failed
		);
	}
}