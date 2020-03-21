#pragma once

namespace IR {

	class InfinitRightDrawing : public InfinitRightObject
	{
	public:
		InfinitRightDrawing(const IRString& name);
		~InfinitRightDrawing();
	private:
		TObjectMap				fObjects;
	public:
		InfinitRightObject*			CreateNewObject(InfinitRightObject* object);
		void						DeleteObject(const IRUUID& uuid);

		InfinitRightObject*			GetObjectByUuid(const IRUUID& uuid);
	};

}