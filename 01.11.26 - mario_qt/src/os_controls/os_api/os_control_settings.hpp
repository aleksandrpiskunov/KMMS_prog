#pragma once

namespace biv {
	class OSControlSettings {
		public:
			virtual ~OSControlSettings() = default;
			virtual void init() = 0;
			virtual void set_cursor_start_position() = 0;
	};
}
