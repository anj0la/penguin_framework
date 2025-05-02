#pragma once

#include <penguin_framework/penguin_api.hpp>
#include <penguin_framework/core/math/colour.hpp>

// Inspired by HTML colour codes: https://htmlcolorcodes.com/color-names/

namespace Colours {

	// Basic shades

	PENGUIN_API const Colour White{ 255, 255, 255, 255 };
	PENGUIN_API const Colour Grey{ 128, 128, 128, 255 };
	PENGUIN_API const Colour Black{ 0, 0, 0, 255 };
	PENGUIN_API const Colour Transparent{ 0, 0, 0, 0 };

	// Grey shades

	PENGUIN_API const Colour LightGrey{ 211, 211, 211, 255 };
	PENGUIN_API const Colour Silver{ 192, 192, 192, 255 };
	PENGUIN_API const Colour DarkGrey{ 169, 169, 169, 255 };
	PENGUIN_API const Colour SlateGrey{ 112, 128, 144, 255 };
	PENGUIN_API const Colour LightSlateGrey{ 136, 147, 162, 255 };
	PENGUIN_API const Colour DimGrey{ 105, 105, 105, 255 };

	// Reds

	PENGUIN_API const Colour Red{ 255, 0, 0, 255 };
	PENGUIN_API const Colour LightRed{ 255, 128, 128, 255 };
	PENGUIN_API const Colour DarkRed{ 128, 0, 0, 255 };
	PENGUIN_API const Colour Crimson{ 220, 20, 60, 255 };
	PENGUIN_API const Colour Maroon{ 128, 0, 0, 255 };
	PENGUIN_API const Colour Scarlet{ 253, 14, 53, 255 };
	PENGUIN_API const Colour Firebrick{ 178, 34, 34, 255 };
	PENGUIN_API const Colour Salmon{ 250, 128, 114, 255 };
	PENGUIN_API const Colour Coral{ 255, 127, 80, 255 };

	// Yellows

	PENGUIN_API const Colour Ivory{ 255, 255, 240, 255 };
	PENGUIN_API const Colour Yellow{ 255, 255, 0, 255 };
	PENGUIN_API const Colour LightYellow{ 255, 255, 128, 255 };
	PENGUIN_API const Colour DarkYellow{ 128, 128, 0, 255 };
	PENGUIN_API const Colour Gold{ 255, 215, 0, 255 };
	PENGUIN_API const Colour Cream{ 255, 250, 205, 255 };
	PENGUIN_API const Colour Lemon{ 255, 250, 51, 255 };
	PENGUIN_API const Colour CandyCorn{ 254, 241, 96, 255 };
	PENGUIN_API const Colour PastelYellow{ 250, 250, 160, 255 }; 
	PENGUIN_API const Colour Vanilla{ 243, 229, 171, 255 };
	PENGUIN_API const Colour Banana{ 227, 207, 87, 255 };
	PENGUIN_API const Colour Peach{ 255, 229, 180, 255 };

	// Blues

	PENGUIN_API const Colour Azure{ 240, 255, 255, 255 };
	PENGUIN_API const Colour Blue{ 0, 0, 255, 255 };
	PENGUIN_API const Colour LightBlue{ 128, 128, 255, 255 };
	PENGUIN_API const Colour DarkBlue{ 0, 0, 128, 255 };
	PENGUIN_API const Colour SkyBlue{ 135, 206, 235, 255 };
	PENGUIN_API const Colour RoyalBlue{ 65, 105, 225, 255 };
	PENGUIN_API const Colour NavyBlue{ 0, 0, 128, 255 };
	PENGUIN_API const Colour Turquoise{ 64, 224, 208, 255 };
	PENGUIN_API const Colour Teal{ 0, 128, 128, 255 };
	PENGUIN_API const Colour Aqua{ 0, 255, 255, 255 };
	PENGUIN_API const Colour Cyan{ 0, 255, 255, 255 };
	PENGUIN_API const Colour LightCyan{ 224, 255, 255, 255 };
	PENGUIN_API const Colour Aquamarine{ 127, 255, 212, 255 };
	PENGUIN_API const Colour PowderBlue{ 176, 224, 230, 255 };

	// Greens

	PENGUIN_API const Colour MintCream{ 245, 255, 250, 255 };
	PENGUIN_API const Colour Honeydew{ 240, 255, 240, 255 };
	PENGUIN_API const Colour Green{ 0, 128, 0, 255 };
	PENGUIN_API const Colour GreenYellow{ 173, 255, 47, 255 };
	PENGUIN_API const Colour LightGreen{ 144, 238, 144, 255 };
	PENGUIN_API const Colour DarkGreen{ 0, 100, 0, 255 };
	PENGUIN_API const Colour SpringGreen{ 0, 255, 127, 255 };
	PENGUIN_API const Colour Lime{ 0, 255, 0, 255 };
	PENGUIN_API const Colour LimeGreen{ 50, 205, 50, 255 };
	PENGUIN_API const Colour Olive{ 128, 128, 0, 255 };
	PENGUIN_API const Colour ForestGreen{ 34, 139, 34, 255 };
	PENGUIN_API const Colour Mint{ 189, 252, 201, 255 };

	// Oranges

	PENGUIN_API const Colour Orange{ 255, 165, 0, 255 };
	PENGUIN_API const Colour LightOrange{ 255, 192, 203, 255 };
	PENGUIN_API const Colour DarkOrange{ 255, 140, 0, 255 };
	PENGUIN_API const Colour Pumpkin{ 255, 117, 24, 255 };
	PENGUIN_API const Colour Tangerine{ 242, 133, 0, 255 };
	PENGUIN_API const Colour Carrot{ 237, 145, 33, 255 };
	PENGUIN_API const Colour Tomato{ 255, 99, 71, 255 };
	PENGUIN_API const Colour OrangeRed{ 255, 69, 0, 255 };

	// Purples

	PENGUIN_API const Colour Purple{ 128, 0, 128, 255 };
	PENGUIN_API const Colour LightPurple{ 192, 128, 192, 255 };
	PENGUIN_API const Colour DarkPurple{ 64, 0, 64, 255 };
	PENGUIN_API const Colour Violet{ 238, 130, 238, 255 };
	PENGUIN_API const Colour DarkViolet{ 148, 0, 211, 255 };
	PENGUIN_API const Colour Lavender{ 230, 230, 250, 255 };
	PENGUIN_API const Colour Indigo{ 75, 0, 130, 255 };
	PENGUIN_API const Colour Plum{ 221, 160, 221, 255 };
	PENGUIN_API const Colour Orchid{ 218, 112, 214, 255 };
	PENGUIN_API const Colour Grape{ 114, 84, 147, 255 };
	PENGUIN_API const Colour VioletRed{ 128, 0, 64, 255 };

	// Pinks

	PENGUIN_API const Colour Snow{ 255, 250, 250, 255 };
	PENGUIN_API const Colour LavenderBlush{ 255, 240, 245, 255 };
	PENGUIN_API const Colour Pink{ 255, 192, 203, 255 };
	PENGUIN_API const Colour LightPink{ 255, 212, 218, 255 };
	PENGUIN_API const Colour DarkPink{ 255, 105, 180, 255 };
	PENGUIN_API const Colour HotPink{ 255, 105, 180, 255 };
	PENGUIN_API const Colour DeepPink{ 255, 20, 147, 255 };
	PENGUIN_API const Colour PalePink{ 219, 112, 147, 255 };
	PENGUIN_API const Colour Rose{ 255, 0, 127, 255 };
	PENGUIN_API const Colour Magenta{ 255, 0, 255, 255 };

	// Browns

	PENGUIN_API const Colour Almond{ 234, 221, 202, 255 };
	PENGUIN_API const Colour Brown{ 165, 42, 42, 255 };
	PENGUIN_API const Colour LightBrown{ 222, 184, 135, 255 };
	PENGUIN_API const Colour DarkBrown{ 101, 67, 33, 255 };
	PENGUIN_API const Colour Chocolate{ 113, 54, 0, 255 };
	PENGUIN_API const Colour Sienna{ 160, 82, 45, 255 };
	PENGUIN_API const Colour Tan{ 210, 180, 140, 255 };
	PENGUIN_API const Colour Beige{ 245, 245, 220, 255 };

}