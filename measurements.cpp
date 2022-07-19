#include "measurements.h"
#include <chrono>

namespace raytracer {

	timer::timer() : _startTime(std::chrono::system_clock::now()), _endTime(std::chrono::system_clock::now()), _running(true) { }

	timer::~timer() { }

	void timer::start() {
		if (_running) return;

		_startTime = std::chrono::system_clock::now();
		_running = true;
	}

	void timer::stop() {
		if (!_running) return;

		_endTime = std::chrono::system_clock::now();
		_running = false;
	}

	void timer::reset() {
		_startTime = std::chrono::system_clock::now();
		_endTime = std::chrono::system_clock::now();
		_running = false;
	}

	int timer::get_elapsed_ms() const {
		const std::chrono::time_point<std::chrono::system_clock> now =
			_running ? std::chrono::system_clock::now() : _endTime;

		return (int) std::chrono::duration_cast<std::chrono::milliseconds>(now - _startTime).count();
	}


	scoped_timer::scoped_timer( const std::function<void(int)>& closeFunc ) :
		_startTime(std::chrono::system_clock::now()), _onClose( closeFunc ) { }

	scoped_timer::~scoped_timer() {
		const std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
		_onClose((int)std::chrono::duration_cast<std::chrono::milliseconds>(now - _startTime).count());
	}


	int lamda_timer(const std::function<void()>& lambda) {
		const std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
		lambda();
		const std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

		return (int)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	}
}
