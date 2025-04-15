#include <WinterEngine/Inc/WinterEngine.h>

using namespace WinterEngine;
using namespace WinterEngine::Core;

static int sUniqueId = 0;
static int sItemUniqueId = 0;
static int sBuildingUniqueId = 0;
class Student
{
public:
	Student()
	{
		mId = ++sUniqueId;
		mName = "NoName" + std::to_string(mId);
	}

	Student(const std::string& name)
		: mName(name)
		, mId(++sUniqueId)
	{

	}

	void Log()
	{
		LOG("Name: %s - Id: %d", mName.c_str(), mId);
	}

private:
	int mId = 0;
	std::string mName;
};

class Item
{
public:
	Item()
	{
		mId = ++sItemUniqueId;
		mName = "Item " + std::to_string(mId);
	}
	
	Item(const std::string& name)
		:mName(name)
		,mId(++sItemUniqueId)
	{ }

	void Log()
	{
		LOG("Item Name: %s - Id: %d", mName.c_str(), mId);
	}
private:
	int mId = 0;
	std::string mName;
};

class Building
{
public:
	Building()
	{
		mId = ++sBuildingUniqueId;
		mStreetName = "Building" + std::to_string(mId);
	}

	Building(const std::string& name)
		:mStreetName(name)
		,mId(++sBuildingUniqueId)
	{ }

	void Log()
	{
		LOG("Building Name:%s - Id: %d", mStreetName.c_str(), mId);
	}
private:
	int mId = 0;
	std::string mStreetName;
};

int WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	TypedAllocator studentPool = TypedAllocator<Student>("StudentPool", 200);
	TypedAllocator itemPool = TypedAllocator<Item>("ItemPool", 200);
	TypedAllocator buildingPool = TypedAllocator<Building>("BuildingPool", 200);

	std::vector<Student*> students;
	std::vector<Item*> items;
	std::vector<Building*> buildings;

	//test new
	for (uint32_t i = 0; i < 100; ++i)
	{
		std::string newStudentName = "New_Student" + std::to_string(i);
		Student* newStudent = studentPool.New(newStudentName);
		newStudent->Log();
		students.push_back(newStudent);
	}

	//test deletion
	for (uint32_t i = 0; i < 60; ++i)
	{
		Student* student = students.back();
		studentPool.Delete(student);
		students.pop_back();
	}

	//test adding more
	for (uint32_t i = 0; i < 55; ++i)
	{
		std::string newStudentName = "New_Student" + std::to_string(i);
		Student* newStudent = studentPool.New(newStudentName);
		newStudent->Log();
		students.push_back(newStudent);
	}

	for (uint32_t i = 0; i < 50; ++i)
	{
		std::string newItemName = "New_Item" + std::to_string(i);
		Item* newItem = itemPool.New(newItemName);
		newItem->Log();
		items.push_back(newItem);
	}

	for (uint32_t i = 0; i < 20; ++i)
	{
		Item* item = items.back();
		itemPool.Delete(item);
		items.pop_back();
	}

	for (uint32_t i = 0; i < 10; ++i)
	{
		std::string newBuildingName = "New_Building" + std::to_string(i);
		Building* newBuilding = buildingPool.New(newBuildingName);
		newBuilding->Log();
		buildings.push_back(newBuilding);
	}

	for (uint32_t i = 0; i < 5; ++i)
	{
		Building* building = buildings.back();
		buildingPool.Delete(building);
		buildings.pop_back();
	}

	//clear all
	for (Student* student : students)
	{
		studentPool.Delete(student);
	}
	students.clear();

	for (Item* item : items)
	{
		itemPool.Delete(item);
	}
	items.clear();

	for (Building* building : buildings)
	{
		buildingPool.Delete(building);
	}
	buildings.clear();

	return 0;
}