#include <array>
#include <iostream>


std::array<int, 2> coordinates_translator(int x, int y)
{
    std::array<int, 2>result = { (x/200),(y/200) };
    std::cout << result[0]<<" and "<<result[1]<<"\n";
	return result;
}

bool verification(std::array<int, 2>player_choice,std::array<int, 2>answer)
{
	if (player_choice[0]==answer[0] and player_choice[1]==answer[1])
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::array<int, 5>  Memory(std::array<int, 5> memory, int attempts, std::array<int, 2> attempt)
{
	memory[attempts] = attempt[0] * 10 + attempt[1];
	return memory;
}