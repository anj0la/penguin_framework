//#include "core/events/pf_windowevent.hpp"
//
//using pf::events::PF_WindowEventIndex;
//using PF_EventCallback = std::function<void()>;
//
//void PF_WindowEvent::handle_events(const SDL_Event& p_event) {
//	switch (p_event.type) {
//		// Resizable event
//		case SDL_EVENT_WINDOW_RESIZED:
//			trigger_event(PF_WindowEventIndex::Resized);
//			break;
//
//		// Hidden event
//		case SDL_EVENT_WINDOW_HIDDEN:
//			trigger_event(PF_WindowEventIndex::Hidden);
//			break;
//
//		// Shown event
//		case SDL_EVENT_WINDOW_SHOWN:
//			trigger_event(PF_WindowEventIndex::Shown);
//			break;
//
//		// Minimized event
//		case SDL_EVENT_WINDOW_MINIMIZED:
//			trigger_event(PF_WindowEventIndex::Minimized);
//			break;
//
//		// Maximized event
//		case SDL_EVENT_WINDOW_MAXIMIZED:
//			trigger_event(PF_WindowEventIndex::Maximized);
//			break;
//
//		// Restored event
//		case SDL_EVENT_WINDOW_RESTORED:
//			trigger_event(PF_WindowEventIndex::Restored);
//			break;
//
//		// Fullscreen events
//		case SDL_EVENT_WINDOW_ENTER_FULLSCREEN:
//			trigger_event(PF_WindowEventIndex::FullscreenEntered);
//			break;
//		case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN:
//			trigger_event(PF_WindowEventIndex::FullscreenExited);
//			break;
//
//		// Mouse grabbed events
//		case SDL_EVENT_WINDOW_MOUSE_ENTER:
//			trigger_event(PF_WindowEventIndex::MouseGrabbed);
//			break;
//		case SDL_EVENT_WINDOW_MOUSE_LEAVE:
//			trigger_event(PF_WindowEventIndex::MouseReleased);
//			break;
//
//		// Focus events
//		case SDL_EVENT_WINDOW_FOCUS_GAINED:
//			trigger_event(PF_WindowEventIndex::FocusGained);
//			break;
//		case SDL_EVENT_WINDOW_FOCUS_LOST:
//			trigger_event(PF_WindowEventIndex::FocusLost);
//			break;
//
//		// Close event
//		case SDL_EVENT_QUIT:
//		case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
//			trigger_event(PF_WindowEventIndex::Close);
//			break;
//	};
//}
//
//void PF_WindowEvent::register_callback(PF_WindowEventIndex index, const PF_EventCallback& callback) {
//	callbacks[index] = callback;
//}
//
//void PF_WindowEvent::trigger_event(PF_WindowEventIndex index) {
//	auto& callback = callbacks[index];
//
//	// Call the connected callback function (if it exists)
//	if (callback) {
//		callback();
//	}
//}