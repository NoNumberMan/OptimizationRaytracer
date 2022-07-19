#pragma once
#include <chrono>
#include <functional>

namespace raytracer {
	struct timer {
		private:
		std::chrono::time_point<std::chrono::system_clock> _startTime;
		std::chrono::time_point<std::chrono::system_clock> _endTime;
		bool _running;

		public:
		timer();
		~timer();

		void reset();
		void start();
		void stop();
		int get_elapsed_ms() const;
	};

	struct scoped_timer {
		private:
		std::chrono::time_point<std::chrono::system_clock> _startTime;
		std::function<void(int)> _onClose;

		public:
		explicit scoped_timer(const std::function<void(int)>& closeFunc);
		~scoped_timer();
	};

	int lamda_timer(const std::function<void()>& lambda);
}
