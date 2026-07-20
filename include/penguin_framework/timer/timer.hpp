
#pragma once 

#pragma once

#include <penguin_api.hpp>
#include <memory>

namespace penguin::internal::timer {
    class TimerImpl;
}

namespace penguin::input {

    class PENGUIN_API Timer {
    public:
        Timer(double dt = 1.0 / 60.0, bool limit_fps = false, double target_fps = 60.0);
        ~Timer();

        Timer(const Timer&) = delete;
        Timer& operator=(const Timer&) = delete;

        Timer(Timer&&) noexcept = default;
        Timer& operator=(Timer&&) noexcept = default;

        [[nodiscard]] static bool is_valid() noexcept;

        // General functions 

        void tick(); // works exactly like update_frame_time

        void update_fps(); // same as update_fps

        bool can_update() const; // same as should_update
        void consume(); // same as consume_time

        double alpha() const; // same as get_alpha
        double delta_time() const; // same as get_delta_time
        double fps() const; // same as get_fps

        void set_frame_rate_limit(bool enabled, double fps = 60.0); // same as set_fps_cap
        void limit_frame_rate() const; // same as cap_frame_rate

        void sleep(double ms); // same as delay

        /* 
        void TimerImpl::tick() {
            auto current = penguin_clock::now();

            double delta =
                std::chrono::duration<double>(current - prev_time).count();

            delta = std::min(delta, 0.25);

            prev_time = current;
            accumulator += delta;
        }
        
        */
    private:
        static std::unique_ptr<penguin::internal::timer::TimerImpl> pimpl_;
    };

}