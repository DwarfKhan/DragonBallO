#include "MyMath.h"
#include <random>
#include <time.h>


int MyMath::Abs(int num) {
	return num < 0 ? -num : num;
}

float MyMath::Abs(float num) {
	return num < 0.0f ? -num : num;
}

float MyMath::Lerp(float start, float end, float time) {
	if (time > 1) {
		return end;
	}

	float value = start + ((end - start) * time);
	return value;
}

//returns a random int between min and max
int MyMath::DiceRoll(int min, int max)
{
	if (min > max)
	{
		return 0;
	}
	if (min == max)
	{
		return min;
	}

	srand(time(0));
	return rand() % ((max - min) + 1) + min;
}

int MyMath::Max(int leftNum, int rightNum) {
	return leftNum > rightNum ? leftNum : rightNum;
}
float MyMath::Max(float leftNum, float rightNum) {
	return leftNum > rightNum ? leftNum : rightNum;
}

int MyMath::Min(int leftNum, int rightNum) {
	return leftNum < rightNum ? leftNum : rightNum;
}
float MyMath::Min(float leftNum, float rightNum) {
	return leftNum < rightNum ? leftNum : rightNum;
}

int MyMath::Clamp(int value, int min, int max) {
	return value > max ? max :
		value < min ? min : value;
}
float MyMath::Clamp(float value, float min, float max) {
	return value > max ? max :
		value < min ? min : value;
}