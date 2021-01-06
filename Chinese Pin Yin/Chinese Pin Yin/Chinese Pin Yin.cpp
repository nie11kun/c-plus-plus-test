// Chinese Pin Yin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

using namespace System;
using namespace Microsoft::International::Converters::PinYinConverter;

int main(array<System::String ^> ^args)
{
	ChineseChar ^chineseChar1 = gcnew ChineseChar(L'΢');
	Console::WriteLine("stroke number of ΢ in Chinese is {0}.", chineseChar1->StrokeNumber);
	Console::WriteLine("{0} characters' pinyin is \"wei1\".", ChineseChar::GetHomophoneCount("wei1"));
	if (ChineseChar::IsHomophone(L'΢', L'ޱ'))
	{
		Console::WriteLine("΢ and ޱ have the same pinyin.");
	}
	else
	{
		Console::WriteLine("΢ and ޱ have different pinyins.");
	}

	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
