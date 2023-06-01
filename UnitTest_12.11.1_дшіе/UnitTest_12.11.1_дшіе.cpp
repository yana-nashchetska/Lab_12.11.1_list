#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12.11.1_list/Lab_12.11.1_list.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest12111дшіе
{
	TEST_CLASS(UnitTest12111дшіе)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int expectedAge = 25;
			std::string expectedGender = "man";
			Respondent* head = nullptr;
			Respondent respondent1;
			respondent1.age = 25;
			respondent1.gender = "man";
			respondent1.education = "primary";
			respondent1.answer = "Yes";

			addRespondent(head, respondent1);

			
			Assert::IsNotNull(head);
			Assert::AreEqual(expectedAge, head->age);

		}
	};
}
