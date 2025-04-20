#pragma once

#include <penguin_framework/penguin_api.hpp>
#include <penguin_framework/core/math/colours.hpp>

// Inspired by HTML colour codes: https://htmlcolorcodes.com/color-names/

namespace Colours {

	// Basic shades

	PENGUIN_API constexpr Colour WHITE{ 255, 255, 255, 255 };
	PENGUIN_API constexpr Colour GREY{ 128, 128, 128, 255 };
	PENGUIN_API constexpr Colour BLACK{ 0, 0, 0, 255 };
	PENGUIN_API constexpr Colour TRANSPARENT{ 0, 0, 0, 0 };

	// Grey shades

	PENGUIN_API constexpr Colour LIGHT_GREY{ 211, 211, 211, 255 };
	PENGUIN_API constexpr Colour SILVER{ 192, 192, 192, 255 };
	PENGUIN_API constexpr Colour DARK_GREY{ 169, 169, 169, 255 };
	PENGUIN_API constexpr Colour SLATE_GREY{ 112, 128, 144, 255 };
	PENGUIN_API constexpr Colour LIGHT_SLATE_GREY{ 136, 147, 162, 255 };
	PENGUIN_API constexpr Colour DIM_GREY{ 105, 105, 105, 255 };

	// Reds

	PENGUIN_API constexpr Colour RED{ 255, 0, 0, 255 };
	PENGUIN_API constexpr Colour LIGHT_RED{ 255, 128, 128, 255 };
	PENGUIN_API constexpr Colour DARK_RED{ 128, 0, 0, 255 };
	PENGUIN_API constexpr Colour CRIMSON{ 220, 20, 60, 255 };
	PENGUIN_API constexpr Colour MAROON{ 128, 0, 0, 255 };
	PENGUIN_API constexpr Colour SCARLET{ 253, 14, 53, 255 };
	PENGUIN_API constexpr Colour FIREBRICK{ 178, 34, 34, 255 };
	PENGUIN_API constexpr Colour SALMON{ 250, 128, 114, 255 };
	PENGUIN_API constexpr Colour CORAL{ 255, 127, 80, 255 };

	// Yellows

	PENGUIN_API constexpr Colour IVORY{ 255, 255, 240, 255 };
	PENGUIN_API constexpr Colour YELLOW{ 255, 255, 0, 255 };
	PENGUIN_API constexpr Colour LIGHT_YELLOW{ 255, 255, 128, 255 };
	PENGUIN_API constexpr Colour DARK_YELLOW{ 128, 128, 0, 255 };
	PENGUIN_API constexpr Colour GOLD{ 255, 215, 0, 255 };
	PENGUIN_API constexpr Colour CREAM{ 255, 250, 205, 255 };
	PENGUIN_API constexpr Colour LEMON{ 255, 250, 51, 255 };
	PENGUIN_API constexpr Colour CANDY_CORN{ 254, 241, 96, 255 };
	PENGUIN_API constexpr Colour PASTEL_YELLOW{ 250, 250, 160, 255 }; 
	PENGUIN_API constexpr Colour VANILLA{ 243, 229, 171, 255 };
	PENGUIN_API constexpr Colour BANANA{ 227, 207, 87, 255 };
	PENGUIN_API constexpr Colour PEACH{ 255, 229, 180, 255 };

	// Blues

	PENGUIN_API constexpr Colour AZURE{ 240, 255, 255, 255 };
	PENGUIN_API constexpr Colour BLUE{ 0, 0, 255, 255 };
	PENGUIN_API constexpr Colour LIGHT_BLUE{ 128, 128, 255, 255 };
	PENGUIN_API constexpr Colour DARK_BLUE{ 0, 0, 128, 255 };
	PENGUIN_API constexpr Colour SKY_BLUE{ 135, 206, 235, 255 };
	PENGUIN_API constexpr Colour ROYAL_BLUE{ 65, 105, 225, 255 };
	PENGUIN_API constexpr Colour NAVY_BLUE{ 0, 0, 128, 255 };
	PENGUIN_API constexpr Colour TURQUOISE{ 64, 224, 208, 255 };
	PENGUIN_API constexpr Colour TEAL{ 0, 128, 128, 255 };
	PENGUIN_API constexpr Colour AQUA{ 0, 255, 255, 255 };
	PENGUIN_API constexpr Colour CYAN{ 0, 255, 255, 255 };
	PENGUIN_API constexpr Colour LIGHT_CYAN{ 224, 255, 255, 255 };
	PENGUIN_API constexpr Colour AQUAMARINE{ 127, 255, 212, 255 };
	PENGUIN_API constexpr Colour POWDER_BLUE{ 176, 224, 230, 255 };

	// Greens

	PENGUIN_API constexpr Colour MINT_CREAM{ 245, 255, 250, 255 };
	PENGUIN_API constexpr Colour HONEYDEW{ 240, 255, 240, 255 };
	PENGUIN_API constexpr Colour GREEN{ 0, 128, 0, 255 };
	PENGUIN_API constexpr Colour GREEN_YELLOW{ 173, 255, 47, 255 };
	PENGUIN_API constexpr Colour LIGHT_GREEN{ 144, 238, 144, 255 };
	PENGUIN_API constexpr Colour DARK_GREEN{ 0, 100, 0, 255 };
	PENGUIN_API constexpr Colour SPRING_GREEN{ 0, 255, 127, 255 };
	PENGUIN_API constexpr Colour LIME{ 0, 255, 0, 255 };
	PENGUIN_API constexpr Colour LIME_GREEN{ 50, 205, 50, 255 };
	PENGUIN_API constexpr Colour OLIVE{ 128, 128, 0, 255 };
	PENGUIN_API constexpr Colour FOREST_GREEN{ 34, 139, 34, 255 };
	PENGUIN_API constexpr Colour MINT{ 189, 252, 201, 255 };

	// Oranges

	PENGUIN_API constexpr Colour ORANGE{ 255, 165, 0, 255 };
	PENGUIN_API constexpr Colour LIGHT_ORANGE{ 255, 192, 203, 255 };
	PENGUIN_API constexpr Colour DARK_ORANGE{ 255, 140, 0, 255 };
	PENGUIN_API constexpr Colour PUMPKIN{ 255, 117, 24, 255 };
	PENGUIN_API constexpr Colour TANGERINE{ 242, 133, 0, 255 };
	PENGUIN_API constexpr Colour CARROT{ 237, 145, 33, 255 };
	PENGUIN_API constexpr Colour TOMATO{ 255, 99, 71, 255 };
	PENGUIN_API constexpr Colour ORANGE_RED{ 255, 69, 0, 255 };

	// Purples

	PENGUIN_API constexpr Colour PURPLE{ 128, 0, 128, 255 };
	PENGUIN_API constexpr Colour LIGHT_PURPLE{ 192, 128, 192, 255 };
	PENGUIN_API constexpr Colour DARK_PURPLE{ 64, 0, 64, 255 };
	PENGUIN_API constexpr Colour VIOLET{ 238, 130, 238, 255 };
	PENGUIN_API constexpr Colour DARK_VIOLET{ 148, 0, 211, 255 };
	PENGUIN_API constexpr Colour LAVENDER{ 230, 230, 250, 255 };
	PENGUIN_API constexpr Colour INDIGO{ 75, 0, 130, 255 };
	PENGUIN_API constexpr Colour PLUM{ 221, 160, 221, 255 };
	PENGUIN_API constexpr Colour ORCHID{ 218, 112, 214, 255 };
	PENGUIN_API constexpr Colour GRAPE{ 114, 84, 147, 255 };
	PENGUIN_API constexpr Colour VIOLET_RED{ 128, 0, 64 255 };

	// Pinks

	PENGUIN_API constexpr Colour SNOW{ 255, 250, 250, 255 };
	PENGUIN_API constexpr Colour LAVENDER_BLUSH{ 255, 240, 245, 255 };
	PENGUIN_API constexpr Colour PINK{ 255, 192, 203, 255 };
	PENGUIN_API constexpr Colour LIGHT_PINK{ 255, 212, 218, 255 };
	PENGUIN_API constexpr Colour DARK_PINK{ 255, 105, 180, 255 };
	PENGUIN_API constexpr Colour HOT_PINK{ 255, 105, 180, 255 };
	PENGUIN_API constexpr Colour DEEP_PINK{ 255, 20, 147, 255 };
	PENGUIN_API constexpr Colour PALE_PINK{ 219, 112, 147, 255 };
	PENGUIN_API constexpr Colour ROSE{ 255, 0, 127, 255 };
	PENGUIN_API constexpr Colour MAGENTA{ 255, 0, 255, 255 };

	// Browns

	PENGUIN_API constexpr Colour ALMOND{ 234, 221, 202, 255 };
	PENGUIN_API constexpr Colour BROWN{ 165, 42, 42, 255 };
	PENGUIN_API constexpr Colour LIGHT_BROWN{ 222, 184, 135, 255 };
	PENGUIN_API constexpr Colour DARK_BROWN{ 101, 67, 33, 255 };
	PENGUIN_API constexpr Colour CHOCOLATE{ 113, 54, 0, 255 };
	PENGUIN_API constexpr Colour SIENNA{ 160, 82, 45, 255 };
	PENGUIN_API constexpr Colour TAN{ 210, 180, 140, 255 };
	PENGUIN_API constexpr Colour BEIGE{ 245, 245, 220, 255 };

}