#pragma once

namespace biv {
	class GameMap {
		protected:
			const int height;
			const int width;
			
		protected:
			GameMap(const int height, const int width);
		
		public:
			bool is_below_map(const int y) const noexcept;
			bool is_on_map(const int x, const int y) const noexcept;
			
			virtual void clear() noexcept = 0;
			virtual void refresh() noexcept = 0;
			virtual void remove_objs() = 0;
			virtual void show() const noexcept = 0;
	};
}
