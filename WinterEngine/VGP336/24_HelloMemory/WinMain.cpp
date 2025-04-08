#include <WinterEngine/Inc/WinterEngine.h>

using namespace WinterEngine;
using namespace WinterEngine::Core;

static int sUniqueId = 0;
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

int WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	TypedAllocator studentPool = TypedAllocator<Student>("StudentPool", 200);

	std::vector<Student*> students;
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

	//clear all
	for (Student* student : students)
	{
		studentPool.Delete(student);
	}
	students.clear();

	return 0;
}