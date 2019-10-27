#pragma once
#include <imgui.h>
#include <unordered_map>
#include <string>

class Stylesheet
{
private:
	static inline std::unordered_map<std::string, Stylesheet> sheets;
	static inline std::string currentSheetName;
	static inline Stylesheet* currentSheet = nullptr;
	std::string name = "default";

public:
	ImVec4 eventColor = {1, 0, 0, 1};
	float anchorOffset = 7;
	float linkThickness = 2;

public:
	Stylesheet(std::string name = "default")
		: name(name)
	{

	}
	Stylesheet(Stylesheet&&) = default;
	Stylesheet(Stylesheet const&) = default;
	Stylesheet& operator=(Stylesheet&&) = default;
	Stylesheet& operator=(Stylesheet const&) = default;
	~Stylesheet() = default;

public:
	static void addSheet(Stylesheet&& sheet)
	{
		assert(sheets.find(sheet.getName()) == sheets.end());
		sheets[sheet.getName()] = std::move(sheet); 
		if(currentSheet == nullptr)
			setCurrentSheet(sheets.begin()->first);
	}

	static Stylesheet& getSheet(std::string name)
	{
		assert(sheets.find(name) != sheets.end());
		return sheets[name];
	}

	static void setCurrentSheet(std::string name)
	{
		currentSheetName = name;
		currentSheet = &getSheet(name);
	}

	static Stylesheet& getCurrentSheet()
	{
		assert(currentSheet != nullptr);
		return *currentSheet;
	}

	std::string getName() const
	{
		return name;
	}

};