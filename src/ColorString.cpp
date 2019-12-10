#include "ColorString.h"
using namespace std;
ColorString::ColorString()
{ 
	this->s = "";
	color=vector<Color>();
}
ColorString::ColorString(const string& str_,Color color_)
{
	this->s = str_;
	color = vector<Color>(str_.size(),color_);
}
ColorString::ColorString(const char* str_, Color color_)
{
	this->s = str_;
	color = vector<Color>(strlen(str_),color_);
}
ColorString& ColorString::operator=(const std::string& str_)
{
	this->s = str_;
	color.resize(str_.size());
	return *this;
}
ColorString& ColorString::operator=(const char* str_)
{
	this->s = str_;
	color.resize(strlen(str_));
	return *this;
}
ColorString& ColorString::operator+=(const ColorString& str_)
{
	this->s += str_.str();
	const std::vector<Color>& color_=str_.getColor();
	color.insert(color.end(), color_.begin(), color_.end());
	return *this;
}
ColorString ColorString::operator+(const ColorString& str_)
{
	ColorString res = (*this);
	return (res += str_);
}