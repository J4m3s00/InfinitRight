#pragma once

IR_BEGIN_OBJECT(TestObject)
private:
	TestObject(const IR::IRUUID& uuid)
		: IR::InfinitRightObject(uuid),
		fNumber("Number", this, 32)
	{

	}

	IR::InfinitRightValueProperty<i32> fNumber;
IR_END_OBJECT