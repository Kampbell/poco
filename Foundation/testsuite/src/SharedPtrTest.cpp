//
// SharedPtrTest.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "SharedPtrTest.h"
#include "Poco/CppUnit/TestCaller.h"
#include "Poco/CppUnit/TestSuite.h"
#include "Poco/SharedPtr.h"
#include "Poco/Exception.h"


using Poco::SharedPtr;
using Poco::NullPointerException;


namespace
{
	class TestObject
	{
	public:
		TestObject(const std::string& rData): _data(rData)
		{
			++_count;
		}

		virtual ~TestObject()
		{
			--_count;
		}

		const std::string& data()
		{
			return _data;
		}

		static int count()
		{
			return _count;
		}

	private:
		std::string _data;
		static int _count;
	};

	int TestObject::_count = 0;

	class DerivedObject: public TestObject
	{
	public:
		DerivedObject(const std::string& s, int i): TestObject(s), _number(i)
		{
		}

		int number() const
		{
			return _number;
		}

	private:
		int _number;
	};
}


SharedPtrTest::SharedPtrTest(const std::string& rName): CppUnit::TestCase(rName)
{
}


SharedPtrTest::~SharedPtrTest()
{
}


void SharedPtrTest::testSharedPtr()
{
	SharedPtr<TestObject> ptr1;
	assertNull(ptr1.get());
	TestObject* pTO1 = new TestObject("one");
	TestObject* pTO2 = new TestObject("two");
	if (pTO2 < pTO1)
	{
		TestObject* pTmp = pTO1;
		pTO1 = pTO2;
		pTO2 = pTmp;
	}
	assertTrue (pTO1 < pTO2);
	ptr1 = pTO1;
	assertTrue (ptr1.referenceCount() == 1);
	SharedPtr<TestObject> ptr2 = pTO2;
	SharedPtr<TestObject> ptr3 = ptr1;
	assertTrue (ptr1.referenceCount() == 2);
	SharedPtr<TestObject> ptr4;
	assertTrue (ptr1.get() == pTO1);
	assertTrue (ptr1 == pTO1);
	assertTrue (ptr2.get() == pTO2);
	assertTrue (ptr2 == pTO2);
	assertTrue (ptr3.get() == pTO1);
	assertTrue (ptr3 == pTO1);

	assertTrue (ptr1 == pTO1);
	assertTrue (ptr1 != pTO2);
	assertTrue (ptr1 < pTO2);
	assertTrue (ptr1 <= pTO2);
	assertTrue (ptr2 > pTO1);
	assertTrue (ptr2 >= pTO1);

	assertTrue (ptr1 == ptr3);
	assertTrue (ptr1 != ptr2);
	assertTrue (ptr1 < ptr2);
	assertTrue (ptr1 <= ptr2);
	assertTrue (ptr2 > ptr1);
	assertTrue (ptr2 >= ptr1);

	ptr1.swap(ptr2);
	assertTrue (ptr2 < ptr1);
	ptr2.swap(ptr1);

	assertTrue ((ptr1->data() == "one" && ptr2->data() == "two") || (ptr1->data() == "two" && ptr2->data() == "one"));

	try
	{
		assertTrue (ptr4->data() == "four");
		fail ("must throw NullPointerException");
	}
	catch (NullPointerException&)
	{
	}

	assertTrue (!(ptr4 == ptr1));
	assertTrue (!(ptr4 == ptr2));
	assertTrue (ptr4 != ptr1);
	assertTrue (ptr4 != ptr2);

	ptr4 = ptr2;
	assertTrue (ptr4 == ptr2);
	assertTrue (!(ptr4 != ptr2));

	assertTrue (TestObject::count() == 2);
	ptr1 = 0;
	ptr2 = 0;
	ptr3 = 0;
	ptr4 = 0;
	assertTrue (TestObject::count() == 0);

	{
		SharedPtr<TestObject> ptr = new TestObject("");
		assertTrue (TestObject::count() == 1);
	}
	assertTrue (TestObject::count() == 0);

	std::shared_ptr<TestObject> stdp(std::make_shared<TestObject>(""));
	Poco::SharedPtr<TestObject> ptr5(stdp);
	std::shared_ptr<TestObject> stdp2 = ptr5;

	assertTrue (stdp == stdp2);

	std::shared_ptr<TestObject> stdp3(std::make_shared<TestObject>(""));
	TestObject* rptr = stdp3.get();
	Poco::SharedPtr<TestObject> ptr6(std::move(stdp3));

	assertTrue (!stdp3);
	assertTrue (ptr6.get() == rptr);

	std::shared_ptr<TestObject> stdp4(std::make_shared<TestObject>(""));
	rptr = stdp4.get();
	ptr6 = std::move(stdp4);

	assertTrue (!stdp4);
	assertTrue (ptr6.get() == rptr);
}


void SharedPtrTest::testImplicitCast()
{
	{
		// null assign test
		SharedPtr<DerivedObject> ptr2;
		assertNull(ptr2.get());
		SharedPtr<TestObject> ptr1 = ptr2;
	}
	{
		SharedPtr<DerivedObject> ptr2(new DerivedObject("test", 666));
		assertTrue (TestObject::count() == 1);
		SharedPtr<TestObject> ptr1 = ptr2;
		assertTrue (TestObject::count() == 1);
	}
	assertTrue (TestObject::count() == 0);
	SharedPtr<TestObject> ptr1 = new DerivedObject("test", 666);
	assertTrue (TestObject::count() == 1);
	ptr1 = 0;
	assertTrue (TestObject::count() == 0);
}


void SharedPtrTest::testExplicitCast()
{
	SharedPtr<TestObject> ptr1 = new DerivedObject("test", 666);
	SharedPtr<DerivedObject> ptr2 = ptr1.cast<DerivedObject>();
	assertTrue (ptr2.get() != 0);

	// cast the other way round must fail
	ptr1 = new TestObject("test");
	assertTrue (TestObject::count() == 2);
	ptr2 = ptr1.cast<DerivedObject>();
	assertTrue (TestObject::count() == 1);
	assertTrue (ptr2.get() == 0);
}


void SharedPtrTest::setUp()
{
}


void SharedPtrTest::tearDown()
{
}


CppUnit::Test* SharedPtrTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("SharedPtrTest");

	CppUnit_addTest(pSuite, SharedPtrTest, testSharedPtr);
	CppUnit_addTest(pSuite, SharedPtrTest, testImplicitCast);
	CppUnit_addTest(pSuite, SharedPtrTest, testExplicitCast);

	return pSuite;
}
