#pragma once
#include<string>
#include<vector>
#include<Windows.h>
#include"Color.h"
//using Color = unsigned short;
class ColorString
{
private:
	std::vector<Color> color;
	std::string s;
public:
	ColorString& operator=(const std::string& str_);
	ColorString& operator=(const char* str_);
	ColorString& operator+=(const ColorString& str_);
	ColorString operator+(const ColorString& str_);
	ColorString();
	ColorString(const std::string& str_,Color color_= Color::BLACK);
	ColorString(const char* str_, Color color_= Color::BLACK);
	void setColor(int index_,Color color_) { color[index_]= color_; };
	Color getColor(int index_)const { return color[index_]; }
	std::vector<Color> getColor()const { return color; }
	size_t size()const { return this->s.size(); };
	size_t length()const { return this->s.length(); };
	const std::string& str()const { return this->s; };
};