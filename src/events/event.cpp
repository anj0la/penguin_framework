#include <penguin_framework/events/events.hpp>
#include <events/internal/events_impl.hpp>
#include <penguin_framework/logger/logger.hpp>

namespace penguin::events {

	Events::Events() = default;
	Events::~Events() = default;

	void Events::subscribe(const std::function<void(const InputEvent&)>& callback) {
		pimpl_->subscribe(callback);
	}

	void Events::poll() {
		pimpl_->poll();
	}

	bool Events::should_quit() {
		return pimpl_->should_quit();
	}

}