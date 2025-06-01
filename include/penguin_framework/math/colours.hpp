#pragma once

#include <penguin_framework/math/colour.hpp>

// Inspired by HTML Colour codes: https://htmlcolorcodes.com/color-names/

namespace Colours {

	// Basic shades

	constexpr penguin::math::Colour NoTint{ 1.0000000f, 1.0000000f, 1.0000000f, 1.0000000f };
	constexpr penguin::math::Colour White{ 1.0000000f, 1.0000000f, 1.0000000f, 1.0000000f };
	constexpr penguin::math::Colour Grey{ 0.5019608f, 0.5019608f, 0.5019608f, 1.0000000f };
	constexpr penguin::math::Colour Black{ 0.0000000f, 0.0000000f, 0.0000000f, 1.0000000f };
	constexpr penguin::math::Colour Transparent{ 0.0000000f, 0.0000000f, 0.0000000f, 0.0000000f }; // Transparent Black

	// Grey shades

	constexpr penguin::math::Colour LightGrey{ 0.8274510f, 0.8274510f, 0.8274510f, 1.0000000f };
	constexpr penguin::math::Colour Silver{ 0.7529412f, 0.7529412f, 0.7529412f, 1.0000000f };
	constexpr penguin::math::Colour DarkGrey{ 0.6627451f, 0.6627451f, 0.6627451f, 1.0000000f };
	constexpr penguin::math::Colour SlateGrey{ 0.4392157f, 0.5019608f, 0.5647059f, 1.0000000f };
	constexpr penguin::math::Colour LightSlateGrey{ 0.5333333f, 0.5764706f, 0.6352941f, 1.0000000f };
	constexpr penguin::math::Colour DimGrey{ 0.4117647f, 0.4117647f, 0.4117647f, 1.0000000f };

	// Reds

	constexpr penguin::math::Colour Red{ 1.0000000f, 0.0000000f, 0.0000000f, 1.0000000f };
	constexpr penguin::math::Colour LightRed{ 1.0000000f, 0.5019608f, 0.5019608f, 1.0000000f };
	constexpr penguin::math::Colour DarkRed{ 0.5019608f, 0.0000000f, 0.0000000f, 1.0000000f };
	constexpr penguin::math::Colour Crimson{ 0.8627451f, 0.0784314f, 0.2352941f, 1.0000000f };
	constexpr penguin::math::Colour Maroon{ 0.5019608f, 0.0000000f, 0.0000000f, 1.0000000f };
	constexpr penguin::math::Colour Scarlet{ 0.9921569f, 0.0549020f, 0.2078431f, 1.0000000f };
	constexpr penguin::math::Colour Firebrick{ 0.6980392f, 0.1333333f, 0.1333333f, 1.0000000f };
	constexpr penguin::math::Colour Salmon{ 0.9803922f, 0.5019608f, 0.4470588f, 1.0000000f };
	constexpr penguin::math::Colour Coral{ 1.0000000f, 0.4980392f, 0.3137255f, 1.0000000f };

	// Yellows

	constexpr penguin::math::Colour Ivory{ 1.0000000f, 1.0000000f, 0.9411765f, 1.0000000f };
	constexpr penguin::math::Colour Yellow{ 1.0000000f, 1.0000000f, 0.0000000f, 1.0000000f };
	constexpr penguin::math::Colour LightYellow{ 1.0000000f, 1.0000000f, 0.5019608f, 1.0000000f };
	constexpr penguin::math::Colour DarkYellow{ 0.5019608f, 0.5019608f, 0.0000000f, 1.0000000f };
	constexpr penguin::math::Colour Gold{ 1.0000000f, 0.8431373f, 0.0000000f, 1.0000000f };
	constexpr penguin::math::Colour Cream{ 1.0000000f, 0.9803922f, 0.8039216f, 1.0000000f };
	constexpr penguin::math::Colour Lemon{ 1.0000000f, 0.9803922f, 0.2000000f, 1.0000000f };
	constexpr penguin::math::Colour CandyCorn{ 0.9960784f, 0.9450980f, 0.3764706f, 1.0000000f };
	constexpr penguin::math::Colour PastelYellow{ 0.9803922f, 0.9803922f, 0.6274510f, 1.0000000f };
	constexpr penguin::math::Colour Vanilla{ 0.9529412f, 0.9000000f, 0.6705882f, 1.0000000f };
	constexpr penguin::math::Colour Banana{ 0.8901961f, 0.8117647f, 0.3411765f, 1.0000000f };
	constexpr penguin::math::Colour Peach{ 1.0000000f, 0.8980392f, 0.7058824f, 1.0000000f };

	// Blues

	constexpr penguin::math::Colour Azure{ 0.9411765f, 1.0000000f, 1.0000000f, 1.0000000f };
	constexpr penguin::math::Colour Blue{ 0.0000000f, 0.0000000f, 1.0000000f, 1.0000000f };
	constexpr penguin::math::Colour LightBlue{ 0.5019608f, 0.5019608f, 1.0000000f, 1.0000000f };
	constexpr penguin::math::Colour DarkBlue{ 0.0000000f, 0.0000000f, 0.5019608f, 1.0000000f };
	constexpr penguin::math::Colour SkyBlue{ 0.5294118f, 0.8078431f, 0.9215686f, 1.0000000f };
	constexpr penguin::math::Colour RoyalBlue{ 0.2549020f, 0.4117647f, 0.8823529f, 1.0000000f };
	constexpr penguin::math::Colour NavyBlue{ 0.0000000f, 0.0000000f, 0.5019608f, 1.0000000f };
	constexpr penguin::math::Colour Turquoise{ 0.2509804f, 0.8784314f, 0.8156863f, 1.0000000f };
	constexpr penguin::math::Colour Teal{ 0.0000000f, 0.5019608f, 0.5019608f, 1.0000000f };
	constexpr penguin::math::Colour Aqua{ 0.0000000f, 1.0000000f, 1.0000000f, 1.0000000f };
	constexpr penguin::math::Colour Cyan{ 0.0000000f, 1.0000000f, 1.0000000f, 1.0000000f };
	constexpr penguin::math::Colour LightCyan{ 0.8784314f, 1.0000000f, 1.0000000f, 1.0000000f };
	constexpr penguin::math::Colour Aquamarine{ 0.4980392f, 1.0000000f, 0.8313726f, 1.0000000f };
	constexpr penguin::math::Colour PowderBlue{ 0.6901961f, 0.8784314f, 0.9019608f, 1.0000000f };

	// Greens

	constexpr penguin::math::Colour MintCream{ 0.9607843f, 1.0000000f, 0.9803922f, 1.0000000f };
	constexpr penguin::math::Colour Honeydew{ 0.9411765f, 1.0000000f, 0.9411765f, 1.0000000f };
	constexpr penguin::math::Colour Green{ 0.0000000f, 0.5019608f, 0.0000000f, 1.0000000f };
	constexpr penguin::math::Colour GreenYellow{ 0.6784314f, 1.0000000f, 0.1843137f, 1.0000000f };
	constexpr penguin::math::Colour LightGreen{ 0.5647059f, 0.9333333f, 0.5647059f, 1.0000000f };
	constexpr penguin::math::Colour DarkGreen{ 0.0000000f, 0.3921569f, 0.0000000f, 1.0000000f };
	constexpr penguin::math::Colour SpringGreen{ 0.0000000f, 1.0000000f, 0.4980392f, 1.0000000f };
	constexpr penguin::math::Colour Lime{ 0.0000000f, 1.0000000f, 0.0000000f, 1.0000000f };
	constexpr penguin::math::Colour LimeGreen{ 0.1960784f, 0.8039216f, 0.1960784f, 1.0000000f };
	constexpr penguin::math::Colour Olive{ 0.5019608f, 0.5019608f, 0.0000000f, 1.0000000f };
	constexpr penguin::math::Colour ForestGreen{ 0.1333333f, 0.5450980f, 0.1333333f, 1.0000000f };
	constexpr penguin::math::Colour Mint{ 0.7411765f, 0.9882353f, 0.7882353f, 1.0000000f };

	// Oranges

	constexpr penguin::math::Colour Orange{ 1.0000000f, 0.6470588f, 0.0000000f, 1.0000000f };
	constexpr penguin::math::Colour LightOrange{ 1.0000000f, 0.7529412f, 0.7960784f, 1.0000000f };
	constexpr penguin::math::Colour DarkOrange{ 1.0000000f, 0.5490196f, 0.0000000f, 1.0000000f };
	constexpr penguin::math::Colour Pumpkin{ 1.0000000f, 0.4588235f, 0.0941176f, 1.0000000f };
	constexpr penguin::math::Colour Tangerine{ 0.9490196f, 0.5215686f, 0.0000000f, 1.0000000f };
	constexpr penguin::math::Colour Carrot{ 0.9294118f, 0.5686275f, 0.1294118f, 1.0000000f };
	constexpr penguin::math::Colour Tomato{ 1.0000000f, 0.3882353f, 0.2784314f, 1.0000000f };
	constexpr penguin::math::Colour OrangeRed{ 1.0000000f, 0.2705882f, 0.0000000f, 1.0000000f };

	// Purples

	constexpr penguin::math::Colour Purple{ 0.5019608f, 0.0000000f, 0.5019608f, 1.0000000f };
	constexpr penguin::math::Colour LightPurple{ 0.7529412f, 0.5019608f, 0.7529412f, 1.0000000f };
	constexpr penguin::math::Colour DarkPurple{ 0.2509804f, 0.0000000f, 0.2509804f, 1.0000000f };
	constexpr penguin::math::Colour Violet{ 0.9333333f, 0.5098039f, 0.9333333f, 1.0000000f };
	constexpr penguin::math::Colour DarkViolet{ 0.5803922f, 0.0000000f, 0.8274510f, 1.0000000f };
	constexpr penguin::math::Colour Lavender{ 0.9019608f, 0.9019608f, 0.9803922f, 1.0000000f };
	constexpr penguin::math::Colour Indigo{ 0.2941176f, 0.0000000f, 0.5098039f, 1.0000000f };
	constexpr penguin::math::Colour Plum{ 0.8666667f, 0.6274510f, 0.8666667f, 1.0000000f };
	constexpr penguin::math::Colour Orchid{ 0.8549020f, 0.4392157f, 0.8392157f, 1.0000000f };
	constexpr penguin::math::Colour Grape{ 0.4470588f, 0.3294118f, 0.5764706f, 1.0000000f };
	constexpr penguin::math::Colour VioletRed{ 0.5019608f, 0.0000000f, 0.2509804f, 1.0000000f };

	// Pinks

	constexpr penguin::math::Colour Snow{ 1.0000000f, 0.9803922f, 0.9803922f, 1.0000000f };
	constexpr penguin::math::Colour LavenderBlush{ 1.0000000f, 0.9411765f, 0.9607843f, 1.0000000f };
	constexpr penguin::math::Colour CottonCandy{ 1.0000000f, 0.7176471f, 0.8352941f, 1.0000000f };
	constexpr penguin::math::Colour Pink{ 1.0000000f, 0.7529412f, 0.7960784f, 1.0000000f };
	constexpr penguin::math::Colour LightPink{ 1.0000000f, 0.8313726f, 0.8549020f, 1.0000000f };
	constexpr penguin::math::Colour DarkPink{ 0.6666667f, 0.2000000f, 0.4156863f, 1.0000000f };
	constexpr penguin::math::Colour HotPink{ 1.0000000f, 0.4117647f, 0.7058824f, 1.0000000f };
	constexpr penguin::math::Colour DeepPink{ 1.0000000f, 0.0784314f, 0.5764706f, 1.0000000f };
	constexpr penguin::math::Colour PalePink{ 0.8588235f, 0.4392157f, 0.5764706f, 1.0000000f };
	constexpr penguin::math::Colour Rose{ 1.0000000f, 0.0000000f, 0.4980392f, 1.0000000f };
	constexpr penguin::math::Colour Magenta{ 1.0000000f, 0.0000000f, 1.0000000f, 1.0000000f };

	// Browns

	constexpr penguin::math::Colour Almond{ 0.9176471f, 0.8666667f, 0.7921569f, 1.0000000f };
	constexpr penguin::math::Colour Brown{ 0.6470588f, 0.1647059f, 0.1647059f, 1.0000000f };
	constexpr penguin::math::Colour LightBrown{ 0.8705882f, 0.7215686f, 0.5294118f, 1.0000000f };
	constexpr penguin::math::Colour DarkBrown{ 0.3960784f, 0.2627451f, 0.1294118f, 1.0000000f };
	constexpr penguin::math::Colour Chocolate{ 0.4431373f, 0.2117647f, 0.0000000f, 1.0000000f };
	constexpr penguin::math::Colour Sienna{ 0.6274510f, 0.3215686f, 0.1764706f, 1.0000000f };
	constexpr penguin::math::Colour Tan{ 0.8235294f, 0.7058824f, 0.5490196f, 1.0000000f };
	constexpr penguin::math::Colour Beige{ 0.9607843f, 0.9607843f, 0.8627451f, 1.0000000f };

}