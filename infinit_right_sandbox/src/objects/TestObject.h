#pragma once

IR_OBJECT_NEW(TestObject)
private:
	TestObject(const IR::IRUUID& uuid)
		: IR::InfinitRightObject(uuid),
			IR_INIT_PROPERTY_A1(Number, 32)
	{

	}

	IR_DEFINE_PROPERTY(Number, i32);
IR_END_OBJECT

