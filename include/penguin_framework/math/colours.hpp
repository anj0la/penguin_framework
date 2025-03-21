#pragma once

# include "penguin_framework/math/colours.hpp"

namespace Colours {

	// Basic shades

	constexpr Colour WHITE{ 255, 255, 255, 255 };
	constexpr Colour GREY{ 128, 128, 128, 255 };
	constexpr Colour BLACK{ 0, 0, 0, 255 };
	constexpr Colour TRANSPARENT{ 0, 0, 0, 0 };

	// Grey shades

	constexpr Colour LIGHT_GREY{ 192, 192, 192, 255 };
	constexpr Colour DARK_GREY{ 64, 64, 64, 255 };
	constexpr Colour SILVER{ 192, 192, 192, 255 };
	constexpr Colour SLATE_GREY{ 112, 128, 144, 255 };
	constexpr Colour LIGHT_SLATE_GREY{ 119, 136, 153, 255 };
	constexpr Colour DIM_GREY{ 105, 105, 105, 255 };

	// Reds

	constexpr Colour RED{ 255, 0, 0, 255 };
	constexpr Colour LIGHT_RED{ 255, 128, 128, 255 };
	constexpr Colour DARK_RED{ 128, 0, 0, 255 };
	constexpr Colour CRIMSON{ 220, 20, 60, 255 };
	constexpr Colour MAROON{ 128, 0, 0, 255 };
	constexpr Colour SCARLET{ 253, 14, 53, 255 };
	constexpr Colour FIREBRICK{ 178, 34, 34, 255 };

	// Yellows

	constexpr Colour YELLOW{ 255, 255, 0, 255 };
	constexpr Colour LIGHT_YELLOW{ 255, 255, 128, 255 };
	constexpr Colour DARK_YELLOW{ 128, 128, 0, 255 };
	constexpr Colour GOLD{ 255, 215, 0, 255 };
	constexpr Colour LEMON{ 255, 250, 205, 255 };

	// Blues

	constexpr Colour BLUE{ 0, 0, 255, 255 };
	constexpr Colour LIGHT_BLUE{ 128, 128, 255, 255 };
	constexpr Colour DARK_BLUE{ 0, 0, 128, 255 };
	constexpr Colour SKY_BLUE{ 135, 206, 235, 255 };
	constexpr Colour ROYAL_BLUE{ 65, 105, 225, 255 };
	constexpr Colour NAVY_BLUE{ 0, 0, 128, 255 };
	constexpr Colour TURQUOISE{ 64, 224, 208, 255 };
	constexpr Colour TEAL{ 0, 128, 128, 255 };
	constexpr Colour AQUA{ 0, 255, 255, 255 };
	constexpr Colour CYAN{ 0, 255, 255, 255 };

	// Greens

	constexpr Colour GREEN{ 0, 255, 0, 255 };
	constexpr Colour LIGHT_GREEN{ 128, 255, 128, 255 };
	constexpr Colour DARK_GREEN{ 0, 128, 0, 255 };
	constexpr Colour LIME{ 0, 255, 0, 255 };
	constexpr Colour OLIVE{ 128, 128, 0, 255 };
	constexpr Colour FOREST_GREEN{ 34, 139, 34, 255 };
	constexpr Colour MINT{ 189, 252, 201, 255 };
	constexpr Colour LIME_GREEN{ 50, 205, 50, 255 };

	// Oranges

	constexpr Colour ORANGE{ 255, 165, 0, 255 };
	constexpr Colour LIGHT_ORANGE{ 255, 192, 203, 255 };
	constexpr Colour DARK_ORANGE{ 255, 140, 0, 255 };
	constexpr Colour PEACH{ 255, 218, 185, 255 };
	constexpr Colour PUMPKIN{ 255, 117, 24, 255 };
	constexpr Colour TANGERINE{ 242, 133, 0, 255 };
	constexpr Colour CARROT{ 237, 145, 33, 255 };

	// Purples

	constexpr Colour PURPLE{ 128, 0, 128, 255 };
	constexpr Colour LIGHT_PURPLE{ 192, 128, 192, 255 };
	constexpr Colour DARK_PURPLE{ 64, 0, 64, 255 };
	constexpr Colour VIOLET{ 238, 130, 238, 255 };
	constexpr Colour LAVENDER{ 230, 230, 250, 255 };
	constexpr Colour INDIGO{ 75, 0, 130, 255 };
	constexpr Colour PLUM{ 221, 160, 221, 255 };
	constexpr Colour ORCHID{ 218, 112, 214, 255 };
	constexpr Colour GRAPE{ 114, 84, 147, 255 };
	constexpr Colour VIOLET_RED{ 208, 32, 144, 255 };

	// Pinks

	constexpr Colour PINK{ 255, 192, 203, 255 };
	constexpr Colour LIGHT_PINK{ 255, 182, 193, 255 };
	constexpr Colour DARK_PINK{ 255, 105, 180, 255 };
	constexpr Colour HOT_PINK{ 255, 105, 180, 255 };
	constexpr Colour DEEP_PINK{ 255, 20, 147, 255 };
	constexpr Colour PALE_PINK{ 219, 112, 147, 255 };
	constexpr Colour ROSE{ 255, 0, 127, 255 };
	constexpr Colour SALMON{ 250, 128, 114, 255 };
	constexpr Colour CORAL{ 255, 127, 80, 255 };
	constexpr Colour MAGENTA{ 255, 0, 255, 255 };

	// Browns

	constexpr Colour BROWN{ 165, 42, 42, 255 };
	constexpr Colour LIGHT_BROWN{ 222, 184, 135, 255 };
	constexpr Colour DARK_BROWN{ 101, 67, 33, 255 };
	constexpr Colour CHOCOLATE{ 210, 105, 30, 255 };
	constexpr Colour SIENNA{ 160, 82, 45, 255 };
	constexpr Colour TAN{ 210, 180, 140, 255 };
	constexpr Colour BEIGE{ 245, 245, 220, 255 };

}